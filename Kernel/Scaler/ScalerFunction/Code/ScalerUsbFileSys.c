/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerUsbFileSys.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerFunctionInclude.h"
#include "UsbFileSys/ScalerUsbFileSys.h"

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************************************
WORD g_usUsbFileSysU2HostEHCIMaxDataLen = _U2HOST_BULK_DATA_EHCI_BUFFER_SIZE;

BYTE g_ucUsbFileSysType = _USB_FILE_SYS_NONE;
BYTE g_ucUsbFileSysCurPartitionNum;
StructUsbFileSysMbrPartitionTable g_pstUsbFileSysMbrPartitionEntry[_SUPPORT_PARTITION_NUM];
StructUsbFileSysGptHeader g_stUsbFileSysGptHeader;
StructUsbFileSysGptEntry g_pstUsbFileSysGptEntry[_SUPPORT_PARTITION_NUM];
StructUsbFileSysDbrTable g_stUsbFileSysDbrTable;
StructUsbFileSysFileInfo g_stUsbFileSysFileInfo;

DWORD g_ulUsbFileSysCurLBA;
DWORD g_ulUsbFileSysCurClusStartLBA;

bit g_bUsbFileSysEhciConnect = _FALSE;
bit g_bUsbFileSysNtfsFileNotFoundFlag = _FALSE;
BYTE g_ucUsbFileSysSrchFileNameState = _USB_FILE_SYS_SRCH_NAME_NONE;

// for FAT32 application
StructUsbFileSysFatInfo g_stUsbFileSysFatInfo;
EnumUsbFileSysFat32FileNameType g_enumUsbFileSysFat32FileNameType;

// for FAT32 & exFAT application
EnumUsbFileSysSrchType g_enumUsbFileSysSrchFrom;

// for NTFS application
#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
StructUsbFileSysNtfsInfo g_stUsbFileSysNtfsInfo;
#endif

// for DB Dump Data application
DWORD g_ulUsbFileSysDBFileDumpLBA;
BYTE g_pucUsbFileSysGoldenFileName[64];

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
BYTE code tUsbFat32GoldenLongFileNameReplace[16] =
{
    0x30, 0x31, 0x32, 0x33, // 0 ,1, 2, 3
    0x34, 0x35, 0x36, 0x37, // 4, 5, 6, 7
    0x38, 0x39,             // 8, 9
    0x61, 0x62, 0x63, 0x64, // a, b, c, d
    0x65, 0x66              // e, f
};
#endif

BYTE code tUsb2HostFwUpdateFileName[] =
{
#include _USER_USB2_FILE_NAME_STRING
};

BYTE code tUsb2HostFwUpdateFolderName[] =
{
#include _USER_USB2_FOLDER_NAME_STRING
};

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
BYTE code tUsb2HostDBDumpFileName[] =
{
    // Test_01_01_0.txt => [Test_Offset(46+48)_Offset(52+54)_Offset(60).txt]
    0x42, 0x74, 0x00, 0x78, 0x00, 0x74, 0x00, 0x00,
    0x00, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    0x01, 0x54, 0x00, 0x65, 0x00, 0x73, 0x00, 0x74,
    0x00, 0x5f, 0x00, 0x0f, 0x00, 0x00, 0x30, 0x00,
    0x31, 0x00, 0x5f, 0x00, 0x30, 0x00, 0x31, 0x00,
    0x5f, 0x00, 0x00, 0x00, 0x30, 0x00, 0x2e, 0x00

};
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : File System Related Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysInitial(void)
{
    CLR_U2HOST_NTFS_FILE_NOT_FOUND();
    SET_U2HOST_SEARCH_NAME_STATUS(_USB_FILE_SYS_SRCH_NAME_NONE);

    SET_U2HOST_CUR_PARTITION_TYPE(_USB_FILE_SYS_NONE);
    SET_U2HOST_CUR_PARTITION_NUM(0);
    SET_U2HOST_CUR_LBA(0);
    SET_U2HOST_CUR_CLUS_START_LBA(0);

    SET_U2HOST_FAT32_DB_FILE_DUMP_LBA(0);

    memset(&g_pstUsbFileSysMbrPartitionEntry, 0, sizeof(g_pstUsbFileSysMbrPartitionEntry));
    memset(&g_stUsbFileSysGptHeader, 0, sizeof(g_stUsbFileSysGptHeader));
    memset(&g_pstUsbFileSysGptEntry, 0, sizeof(g_pstUsbFileSysGptEntry));
    memset(&g_stUsbFileSysDbrTable, 0, sizeof(g_stUsbFileSysDbrTable));
    memset(&g_stUsbFileSysFatInfo, 0, sizeof(g_stUsbFileSysFatInfo));
    memset(&g_stUsbFileSysFileInfo, 0, sizeof(g_stUsbFileSysFileInfo));

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
    memset(&g_stUsbFileSysNtfsInfo, 0, sizeof(g_stUsbFileSysNtfsInfo));
#endif

#if(_USB2_HOST_1ST_SUB_FOLDER_SUPPORT == _ON)
    SET_U2HOST_SRCH_FROM_DIR_TYPE(_SRCH_1ST_SUB_DIR_FROM_ROOT);
#else
    SET_U2HOST_SRCH_FROM_DIR_TYPE(_SRCH_FILE_FROM_ROOT);
#endif

    ScalerUsbFileSysFat32ChkGoldenFileName(GET_U2HOST_SRCH_FROM_DIR_TYPE());
}

//--------------------------------------------------
// Description  : Store Partition Entry Info. from MBR Table
// Input Value  : MBR content
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysGetMbrEntry(BYTE *pucData)
{
    BYTE ucTmp = 0;
    SBYTE pchDebugMsg[49] = "[FileSys][MBR] Partition Num x, DBR Start Addr \0";

    pchDebugMsg[0] = pchDebugMsg[0];

    for(BYTE ucLoopIdx = 0; ucLoopIdx < _SUPPORT_PARTITION_NUM; ucLoopIdx++)
    {
        // Set AddrStart to Current Partition Entry Start
        ucTmp = 16 * ucLoopIdx;

        // Definition of Partition IDs:
        // - 0x00: Empty Partition Entry
        // - 0x07: NTFS / exFAT / IFS / HPFS (can be further classified by DBR)
        // - 0x0B: FAT32 with CHS
        // - 0x0C: FAT32 with LBA
        // - 0xEE: GPT protective-MBR
        // - Other: Not Supported
        g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ucSystemID = pucData[ucTmp + 4];

        // Check if the Nth PartitionEntry isn't Empty
        if(g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ucSystemID != 0x00)
        {
            pchDebugMsg[29] = 48 + (ucLoopIdx % 10);

            g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ucBootflag = pucData[ucTmp + 0];
            g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ulStartCHS = TO_DWORD(0x00, pucData[ucTmp + 3], pucData[ucTmp + 2], pucData[ucTmp + 1]);

            g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ulEndCHS = TO_DWORD(0x00, pucData[ucTmp + 7], pucData[ucTmp + 6], pucData[ucTmp + 5]);

            // DBR Start Addr
            g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ulDbrStartLBA = TO_DWORD(pucData[ucTmp + 11], pucData[ucTmp + 10], pucData[ucTmp + 9], pucData[ucTmp + 8]);
            DebugMessageU2Host(pchDebugMsg, g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ulDbrStartLBA);

            g_pstUsbFileSysMbrPartitionEntry[ucLoopIdx].ulTotalSecCnt = TO_DWORD(pucData[ucTmp + 15], pucData[ucTmp + 14], pucData[ucTmp + 13], pucData[ucTmp + 12]);
        }
    }
}

//--------------------------------------------------
// Description  : Get GPT Header
// Input Value  : GPT IN1 Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysGetGptHeader(BYTE *pucData)
{
    g_stUsbFileSysGptHeader.ulSignatureL = TO_DWORD(pucData[3], pucData[2], pucData[1], pucData[0]);
    g_stUsbFileSysGptHeader.ulSignatureH = TO_DWORD(pucData[7], pucData[6], pucData[5], pucData[4]);

    g_stUsbFileSysGptHeader.ulMyLBA = TO_DWORD(pucData[27], pucData[26], pucData[25], pucData[24]);

    g_stUsbFileSysGptHeader.ulGptEntryStartLBA = TO_DWORD(pucData[75], pucData[74], pucData[73], pucData[72]);
}

//--------------------------------------------------
// Description  : Get GPT Partition Entry
// Input Value  : GPT Entry Content
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysGetGptEntry(BYTE *pucData)
{
    WORD usTmp = 0;
    SBYTE pchDebugMsg[49] = "[FileSys][GPT] Partition Num x, DBR Start Addr \0";

    pchDebugMsg[0] = pchDebugMsg[0];

    for(BYTE ucLoopIdx = 0; ucLoopIdx < _SUPPORT_PARTITION_NUM; ucLoopIdx++)
    {
        // Set AddrStart to Current Partition Entry Start
        usTmp = 128 * ucLoopIdx;

        g_pstUsbFileSysGptEntry[ucLoopIdx].ulPartitionTypeLL = TO_DWORD(pucData[usTmp + 3], pucData[usTmp + 2], pucData[usTmp + 1], pucData[usTmp + 0]);

        // Check if the Nth PartitionEntry isn't Empty
        if(g_pstUsbFileSysGptEntry[ucLoopIdx].ulPartitionTypeLL != 0x00)
        {
            pchDebugMsg[29] = 48 + (ucLoopIdx % 10);

            // g_pstUsbFileSysGptEntry[ucLoopIdx].ulPartitionTypeLH = TO_DWORD(pucData[usTmp + 7], pucData[usTmp + 6], pucData[usTmp + 5], pucData[usTmp + 4]);
            // g_pstUsbFileSysGptEntry[ucLoopIdx].ulPartitionTypeHL = TO_DWORD(pucData[usTmp + 11], pucData[usTmp + 10], pucData[usTmp + 9], pucData[usTmp + 8]);
            // g_pstUsbFileSysGptEntry[ucLoopIdx].ulPartitionTypeHH = TO_DWORD(pucData[usTmp + 15], pucData[usTmp + 14], pucData[usTmp + 13], pucData[usTmp + 12]);

            // DBR Start Addr
            g_pstUsbFileSysGptEntry[ucLoopIdx].ulDbrStartLBA = TO_DWORD(pucData[usTmp + 35], pucData[usTmp + 34], pucData[usTmp + 33], pucData[usTmp + 32]);
            DebugMessageU2Host(pchDebugMsg, g_pstUsbFileSysGptEntry[ucLoopIdx].ulDbrStartLBA);
        }
    }
}

//--------------------------------------------------
// Description  : Get DBR Table
// Input Value  : DBR Info From EHCI
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysGetDbrTable(BYTE *pucData, EnumUsbFileSysType enumFileSysType)
{
    switch(enumFileSysType)
    {
        case _USB_FILE_SYS_FAT32:

            // FAT32 fields
            g_stUsbFileSysDbrTable.usBytePerSec = TO_WORD(pucData[12], pucData[11]);
            g_stUsbFileSysDbrTable.ulSecPerClus = TO_DWORD(0x00, 0x00, 0x00, pucData[13]);
            g_stUsbFileSysDbrTable.usRsvdSecCnt = TO_WORD(pucData[15], pucData[14]);
            g_stUsbFileSysDbrTable.ucNumFATs = pucData[16];
            g_stUsbFileSysDbrTable.ulFATSz32 = TO_DWORD(pucData[39], pucData[38], pucData[37], pucData[36]);
            g_stUsbFileSysDbrTable.ulRootClus = TO_DWORD(pucData[47], pucData[46], pucData[45], pucData[44]);

            break;

#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
        case _USB_FILE_SYS_EXFAT:

            // exFAT fields
            g_stUsbFileSysDbrTable.ulFATOffset = TO_DWORD(pucData[83], pucData[82], pucData[81], pucData[80]);
            g_stUsbFileSysDbrTable.ulFATLength = TO_DWORD(pucData[87], pucData[86], pucData[85], pucData[84]);
            g_stUsbFileSysDbrTable.ulClusHeapOffset = TO_DWORD(pucData[91], pucData[90], pucData[89], pucData[88]);
            g_stUsbFileSysDbrTable.ulFirstClusOfRootDir = TO_DWORD(pucData[99], pucData[98], pucData[97], pucData[96]);
            g_stUsbFileSysDbrTable.usBytePerSec = 1 << pucData[108];  // 2 ^ BytePerSec
            g_stUsbFileSysDbrTable.ulSecPerClus = 1 << pucData[109];  // 2 ^ SecPerClusShift
            g_stUsbFileSysDbrTable.ucNumFATs = pucData[110];

            break;
#endif

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
        case _USB_FILE_SYS_NTFS:

            // NTFS fields
            g_stUsbFileSysDbrTable.usBytePerSec = TO_WORD(pucData[12], pucData[11]);
            g_stUsbFileSysDbrTable.ulSecPerClus = TO_DWORD(0x00, 0x00, 0x00, pucData[13]);
            g_stUsbFileSysDbrTable.ulSecInVolumeH = TO_DWORD(pucData[0x2F], pucData[0x2E], pucData[0x2D], pucData[0x2C]);
            g_stUsbFileSysDbrTable.ulMftClus = TO_DWORD(pucData[0x33], pucData[0x32], pucData[0x31], pucData[0x30]);
            g_stUsbFileSysDbrTable.ucClusPerMftRecord = pucData[0x40];
            g_stUsbFileSysDbrTable.ucClusPerIdxRecord = pucData[0x44];

            break;
#endif
        default:
            break;
    }

    DebugMessageU2Host("[FileSys][DBR] SecPerClus", g_stUsbFileSysDbrTable.ulSecPerClus);
}

//--------------------------------------------------
// Description  : Get the first LBA of the indicated Cluster.
// Input Value  : None
// Output Value : ulClusStartLBA
//--------------------------------------------------
DWORD ScalerUsbFileSysGetClusStartLBA(DWORD ulClusNum)
{
    DWORD ulClusStartLBA = 0;
    EnumUsbFileSysType enumFileSysType = GET_U2HOST_CUR_PARTITION_TYPE();

    switch(enumFileSysType)
    {
        case _USB_FILE_SYS_FAT32:
#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
        case _USB_FILE_SYS_EXFAT:
#endif
            // Cluster start sector = RootDirStartLBA + (ulClusNum - 2) * SecPerClus;
            ulClusStartLBA = g_stUsbFileSysFatInfo.ulClusFieldStartLBA + (ulClusNum - 2) * g_stUsbFileSysDbrTable.ulSecPerClus;

            break;

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
        case _USB_FILE_SYS_NTFS:

            if(g_pstUsbFileSysMbrPartitionEntry[0].ucSystemID == 0xEE)
            {
                ulClusStartLBA = g_pstUsbFileSysGptEntry[GET_U2HOST_CUR_PARTITION_NUM()].ulDbrStartLBA + ulClusNum * g_stUsbFileSysDbrTable.ulSecPerClus;
            }
            else
            {
                ulClusStartLBA = g_pstUsbFileSysMbrPartitionEntry[GET_U2HOST_CUR_PARTITION_NUM()].ulDbrStartLBA + ulClusNum * g_stUsbFileSysDbrTable.ulSecPerClus;
            }

            break;
#endif

        default:
            break;
    }
    return ulClusStartLBA;
}

//--------------------------------------------------
// Description  : Judge if GetFwVer is newer than CurFwVer
// Input Value  : pucGetFwVer, The new searched Fw Version
//                pucCurFwVer, The current selected Fw Version (newest so far)
// Output Value : bNewVersionGet
//--------------------------------------------------
bit ScalerUsbFileSysJudgeFwVersion(BYTE *pucCurFwVer, BYTE *pucGetFwVer)
{
    DWORD ulCurVer = 0x00;
    DWORD ulGetVer = 0x00;
    BYTE ucVerLen = _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN;
    bit bNewVersionGet = _FALSE;
    SBYTE pchDebugMsg[40] = "[FileSys] Get FW Version:             \0";

    pucCurFwVer[0] = pucCurFwVer[0];
    pchDebugMsg[0] = pchDebugMsg[0];

    // Note: This function will be maintained by kernal temporarily

    for(BYTE ucLoop = 0; ucLoop < ucVerLen; ucLoop ++)
    {
        pchDebugMsg[26 + ucLoop] = pucGetFwVer[ucLoop];
    }
    if(g_stUsbFileSysFileInfo.bNot1stFile == _FALSE)
    {
        DebugMessageU2Host("[FileSys] Judge FW Version from FileName, standard format: V1.2.3", 0);
    }
    DebugMessageU2Host(pchDebugMsg, 0);

    // Fw Version standard format: V1.2.3
    if((pucGetFwVer[0] != 'V') || (pucGetFwVer[2] != '.') || (pucGetFwVer[4] != '.'))
    {
        DebugMessageU2Host("[FileSys] Version not updated, Format Mismatched.", 0);
    }
    else
    {
        // convert ASCII code to BYTE (numerical value)
        ulGetVer = TO_DWORD(0x00, (pucGetFwVer[1] - 0x30), (pucGetFwVer[3] - 0x30), (pucGetFwVer[5] - 0x30));
        ulCurVer = TO_DWORD(0x00, (pucCurFwVer[1] - 0x30), (pucCurFwVer[3] - 0x30), (pucCurFwVer[5] - 0x30));

        if(g_stUsbFileSysFileInfo.bNot1stFile == _FALSE)
        {
            g_stUsbFileSysFileInfo.bNot1stFile = _TRUE;
            g_stUsbFileSysFileInfo.ulFileNameVer = ulGetVer;
            DebugMessageU2Host("[FileSys] Version updated by 1st Fw Version: ", ulGetVer);

            bNewVersionGet = _TRUE;
        }
        else if(ulGetVer > ulCurVer)
        {
            g_stUsbFileSysFileInfo.ulFileNameVer = ulGetVer;
            DebugMessageU2Host("[FileSys] Version updated by Newer Fw Version: ", ulGetVer);

            bNewVersionGet = _TRUE;
        }
        else
        {
            DebugMessageU2Host("[FileSys] Version not updated, not Newest.", 0);
        }
    }

    return bNewVersionGet;
}

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Output File Name to User
// Input Value  : ucUsbUserFileNameOffset
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerUsbFileSysGetFileName(BYTE ucUsbUserFileNameOffset)
{
    return tUsb2HostFwUpdateFileName[ucUsbUserFileNameOffset];
}

//--------------------------------------------------
// Description  : Output EHCI Connect Status to User
// Input Value  : None
// Output Value : bEhciIsConnect
//--------------------------------------------------
bit ScalerUsbFileSysGetConnectStatus(void)
{
    return (GET_U2HOST_EHCI_CONNECT());
}

//--------------------------------------------------
// Description  : Output USB File Info. to User
// Input Value  : None
// Output Value : stUserUsbInfo
//--------------------------------------------------
StructUsbFileSysUserFileInfo ScalerUsbFileSysGetFileInfo(void)
{
    StructUsbFileSysUserFileInfo stUserUsbInfo;

    memset(&stUserUsbInfo, 0, sizeof(stUserUsbInfo));

    stUserUsbInfo.ucConnected = (BYTE)(GET_U2HOST_EHCI_CONNECT());
    stUserUsbInfo.ulSWVersion = g_stUsbFileSysFileInfo.ulFileNameVer;
    for(BYTE ucLoop = 0; ucLoop < _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN; ucLoop++)
    {
        stUserUsbInfo.pchModelNameStr[ucLoop] = tUsb2HostFwUpdateFileName[ucLoop + 2];
    }
    stUserUsbInfo.pchModelNameStr[_USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN] = '\0';

    return stUserUsbInfo;
}
#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Calculate all the needed LBA info. for FAT32 parsing (from MBR & DBR)
// Input Value  : ucCurPtnNum
// Output Value : bValidBytePerSec
//--------------------------------------------------
bit ScalerUsbFileSysFatCalInfo(BYTE ucCurPtnNum)
{
    bit bValidBytePerSec = 0;
    EnumUsbFileSysType enumFileSysType = GET_U2HOST_CUR_PARTITION_TYPE();

    // Get Fat1 Location
    switch(enumFileSysType)
    {
        case _USB_FILE_SYS_FAT32:
            // FAT1StartLBA = DbrStartLBA + usRsvdSecCnt.
            if(g_pstUsbFileSysMbrPartitionEntry[0].ucSystemID == 0xEE)
            {
                g_stUsbFileSysFatInfo.ulFAT1StartLBA = g_pstUsbFileSysGptEntry[ucCurPtnNum].ulDbrStartLBA + g_stUsbFileSysDbrTable.usRsvdSecCnt;
            }
            else
            {
                g_stUsbFileSysFatInfo.ulFAT1StartLBA = g_pstUsbFileSysMbrPartitionEntry[ucCurPtnNum].ulDbrStartLBA + g_stUsbFileSysDbrTable.usRsvdSecCnt;
            }
            // Get ClusterField Location
            // ClusterFieldStartLBA = FAT1StartLBA + NumOfFAT * ulSectorPerFAT.
            g_stUsbFileSysFatInfo.ulClusFieldStartLBA = g_stUsbFileSysFatInfo.ulFAT1StartLBA + g_stUsbFileSysDbrTable.ulFATSz32 * g_stUsbFileSysDbrTable.ucNumFATs;
            g_stUsbFileSysFatInfo.ulRootDirStartClusNum = g_stUsbFileSysDbrTable.ulRootClus;
            DebugMessageU2Host("[FileSys][FAT32] ulFAT1StartLBA !", g_stUsbFileSysFatInfo.ulFAT1StartLBA);
            DebugMessageU2Host("[FileSys][FAT32] ulClusFieldStartLBA !", g_stUsbFileSysFatInfo.ulClusFieldStartLBA);

            break;

#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
        case _USB_FILE_SYS_EXFAT:
            if(g_pstUsbFileSysMbrPartitionEntry[0].ucSystemID == 0xEE)
            {
                g_stUsbFileSysFatInfo.ulFAT1StartLBA = g_pstUsbFileSysGptEntry[ucCurPtnNum].ulDbrStartLBA + g_stUsbFileSysDbrTable.ulFATOffset;
                g_stUsbFileSysFatInfo.ulClusFieldStartLBA = g_pstUsbFileSysGptEntry[ucCurPtnNum].ulDbrStartLBA + g_stUsbFileSysDbrTable.ulClusHeapOffset;
            }
            else
            {
                g_stUsbFileSysFatInfo.ulFAT1StartLBA = g_pstUsbFileSysMbrPartitionEntry[ucCurPtnNum].ulDbrStartLBA + g_stUsbFileSysDbrTable.ulFATOffset;
                g_stUsbFileSysFatInfo.ulClusFieldStartLBA = g_pstUsbFileSysMbrPartitionEntry[ucCurPtnNum].ulDbrStartLBA + g_stUsbFileSysDbrTable.ulClusHeapOffset;
            }
            // Get ClusterField Location
            g_stUsbFileSysFatInfo.ulRootDirStartClusNum = g_stUsbFileSysDbrTable.ulFirstClusOfRootDir;
            DebugMessageU2Host("[FileSys][exFAT] ulFAT1StartLBA !", g_stUsbFileSysFatInfo.ulFAT1StartLBA);
            DebugMessageU2Host("[FileSys][exFAT] ulClusFieldStartLBA !", g_stUsbFileSysFatInfo.ulClusFieldStartLBA);

            break;
#endif

        default:
            break;
    }

    // Reset index/indexshadow before search name
    g_stUsbFileSysFatInfo.stFatDirInfo.ucIndex = 0;
    g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexShadow = 0;
    g_stUsbFileSysFatInfo.stFatDirInfo.pulClusNum[0] = g_stUsbFileSysFatInfo.ulRootDirStartClusNum;

    // Judge if the FAT32 partition supported
    if(g_stUsbFileSysDbrTable.usBytePerSec != 0x0200)
    {
        DebugMessageU2Host("[FileSys][FAT32] Warning: BytePerSec != 512, not supported !", g_stUsbFileSysDbrTable.usBytePerSec);
    }
    else
    {
        bValidBytePerSec = _TRUE;
    }

    return bValidBytePerSec;
}

//--------------------------------------------------
// Description  : Check if current FAT content represents EOC (end of chain)
// Input Value  : ulFatContent
// Output Value : bValdEndOfChain
//--------------------------------------------------
bit ScalerUsbFileSysFatChkEOC(EnumUsbFileSysType enumFileSysType, DWORD ulFatContent)
{
    bit bIsEOC = _FALSE;

    switch(enumFileSysType)
    {
        case _USB_FILE_SYS_FAT32:

            if(ulFatContent >= 0x0FFFFFF8)
            {
                bIsEOC = _TRUE;
            }

            break;

#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
        case _USB_FILE_SYS_EXFAT:

            if(ulFatContent == 0xFFFFFFFF)
            {
                bIsEOC = _TRUE;
            }

            break;
#endif
        default:
            break;
    }

    return bIsEOC;
}

//--------------------------------------------------
// Description  : Get the LBA of FAT1 Sector which contain the next Cluster Num occupied by RootDir or File.
// Input Value  : Next Cluster Num
// Output Value : LBA of FAT1 Sector where Next Cluster Num is
//--------------------------------------------------
DWORD ScalerUsbFileSysFatGetFAT1ClusNumLBA(DWORD ulClusNum)
{
    DWORD ulFAT1ClusNumLBA = 0;

    // FAT1 Start Sector + (ulClusNum/(512/4)), since there's 512/4 ClusNum in a FAT1 Sector
    ulFAT1ClusNumLBA = g_stUsbFileSysFatInfo.ulFAT1StartLBA + (ulClusNum / 128);

    return ulFAT1ClusNumLBA;
}

//--------------------------------------------------
// Description  : Search File Entry under FAT32 system
// Input Value  : pucData: 512byte array
// Output Value : None
//--------------------------------------------------
bit ScalerUsbFileSysFat32ParseFileEntry(EnumUsbFileSysSrchType enumSrchType, BYTE *pucData, BYTE *pucCurEntryOffset, BYTE *pucCurMatchCnt, bit b2ndLoop)
{
    BYTE ucGoldenFileAttr = 0x00;
    BYTE ucGoldenFileNameLen = 0x00;
    BYTE ucGoldenFileNameLen_SFN = 0x00;
    bit bGoldenIsFile = _TRUE;
    bit bChkNameEnd = _TRUE;
    BYTE *pucGoldenFileName = 0x00;
    BYTE ucGoldenLfnCnt = 0x00;
    BYTE ucVerStartChar = 0x00;

    switch(enumSrchType)
    {
        case _SRCH_1ST_SUB_DIR_FROM_ROOT:

            // Search Type = Search Sub Dir
            ucGoldenFileAttr = 0x10;
            pucGoldenFileName = &tUsb2HostFwUpdateFolderName[0];
            bGoldenIsFile = _FALSE;
            bChkNameEnd = _TRUE;
            ucGoldenFileNameLen = pucGoldenFileName[0];
            // Folders doesn't have file extension
            ucGoldenFileNameLen_SFN = ucGoldenFileNameLen;

            break;

        default:

            // Search Type = Search File
            ucGoldenFileAttr = 0x20;
            pucGoldenFileName = &tUsb2HostFwUpdateFileName[0];
            bGoldenIsFile = _TRUE;

#if(_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON)
            ucGoldenFileNameLen = _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN;
            bChkNameEnd = _FALSE;
            ucVerStartChar = (ucGoldenFileNameLen + 1) % 13;
#else
            ucGoldenFileNameLen = pucGoldenFileName[0];
            bChkNameEnd = _TRUE;
#endif
            // subtract file extension (pucGoldenFileName[0] indicate the whole Len of FileName)
            ucGoldenFileNameLen_SFN = pucGoldenFileName[0] - 4;

            break;
    }

    // Calculate the Entry count of target File / Dir
    ucGoldenLfnCnt = ucGoldenFileNameLen / 13;
    if((ucGoldenFileNameLen % 13) != 0)
    {
        ucGoldenLfnCnt ++;
    }

    // Search
    while(*pucCurEntryOffset < (512 / _U2HOST_FILE_SYS_FAT_ENTRY_SIZE))
    {
        switch(GET_U2HOST_FAT32_FILENAME_TYPE())
        {
            case _ONLY_SFN:

                // Target SFN found
                if(ScalerUsbFileSysFat32SrchSfn(bGoldenIsFile, ucGoldenFileNameLen_SFN, pucData, *pucCurEntryOffset, pucGoldenFileName))
                {
                    // Record Target SFN (Clus / Sec / Entry)
                    g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexTarget = g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexShadow;
                    g_stUsbFileSysFatInfo.usSecInClusTarget = (GET_U2HOST_CUR_LBA() - GET_U2HOST_CUR_CLUS_START_LBA());
                    if(b2ndLoop)
                    {
                        g_stUsbFileSysFatInfo.usSecInClusTarget += 1;
                    }
                    g_stUsbFileSysFatInfo.ucEntryInSecTarget = *pucCurEntryOffset;

                    // _USB2_HOST_FILE_NAME_JUDGE_VERSION shall not be _ON in this case
                    SET_U2HOST_SEARCH_NAME_STATUS(_USB_FILE_SYS_SRCH_FINISH);
                    return _TRUE;
                }

                *pucCurEntryOffset += 1;

                break;

            case _SFN_AND_LFN:

                if(ScalerUsbFileSysFat32SrchLfn(pucData, bChkNameEnd, *pucCurEntryOffset, *pucCurMatchCnt, pucGoldenFileName))
                {
                    *pucCurMatchCnt += 1;

                    if(bChkNameEnd == _FALSE)
                    {
                        // Get Fw Version in Last LFN
                        if(*pucCurMatchCnt == 1)
                        {
                            // Get Fw Ver. in FileName
                            for(BYTE ucLoopI = 0; ucLoopI < _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN; ucLoopI ++)
                            {
                                g_stUsbFileSysFileInfo.pucFileNameVerTmp[ucLoopI] = ScalerUsbFileSysFat32GetLfnChar((ucVerStartChar + ucLoopI), &pucData[(*pucCurEntryOffset * 32)]);
                            }
                        }
                    }
                }
                else
                {
                    // Check if All LFN found, since this is the next Entry (SFN) after all matched LFN
                    if((*pucCurMatchCnt == ucGoldenLfnCnt) && (pucData[(*pucCurEntryOffset * 32) + 11] == ucGoldenFileAttr))
                    {
                        if(bChkNameEnd == _FALSE)
                        {
                            // UserFunc judge if this is a newer version
                            if(ScalerUsbFileSysJudgeFwVersion(g_stUsbFileSysFileInfo.pucFileNameVer, g_stUsbFileSysFileInfo.pucFileNameVerTmp))
                            {
                                // Record Target SFN (Clus / Sec / Entry)
                                g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexTarget = g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexShadow;
                                g_stUsbFileSysFatInfo.usSecInClusTarget = (GET_U2HOST_CUR_LBA() - GET_U2HOST_CUR_CLUS_START_LBA());
                                if(b2ndLoop)
                                {
                                    g_stUsbFileSysFatInfo.usSecInClusTarget += 1;
                                }
                                g_stUsbFileSysFatInfo.ucEntryInSecTarget = *pucCurEntryOffset;

                                // update FileNameVer
                                for(BYTE ucLoopI = 0; ucLoopI < _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN; ucLoopI ++)
                                {
                                    g_stUsbFileSysFileInfo.pucFileNameVer[ucLoopI] = g_stUsbFileSysFileInfo.pucFileNameVerTmp[ucLoopI];
                                }
                            }
                        }
                        else
                        {
                            // Record Target SFN (Clus / Sec / Entry)
                            g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexTarget = g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexShadow;
                            g_stUsbFileSysFatInfo.usSecInClusTarget = (GET_U2HOST_CUR_LBA() - GET_U2HOST_CUR_CLUS_START_LBA());
                            if(b2ndLoop)
                            {
                                g_stUsbFileSysFatInfo.usSecInClusTarget += 1;
                            }
                            g_stUsbFileSysFatInfo.ucEntryInSecTarget = *pucCurEntryOffset;

                            // _USB2_HOST_FILE_NAME_JUDGE_VERSION shall not be _ON in this case
                            SET_U2HOST_SEARCH_NAME_STATUS(_USB_FILE_SYS_SRCH_FINISH);
                            return _TRUE;
                        }
                    }
                    // Target LFN mis-matched, reset MatchCnt
                    *pucCurMatchCnt = 0;
                }

                *pucCurEntryOffset += 1;

                break;

            default:
                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Search SFN under FAT32 system
// Input Value  : pucData: 512byte array
//                ucCurEntryOffset: offset to the Entry to compare
//                pucGoldenName
// Output Value : bSFNMatch
//--------------------------------------------------
bit ScalerUsbFileSysFat32SrchSfn(bit bIsFile, BYTE ucFileNameLen_SFN, BYTE *pucData, BYTE ucCurEntryOffset, code BYTE *pucGoldenName)
{
    BYTE ucFileAttr = 0x00;

    if(bIsFile == _TRUE)
    {
        // subtract File Extension
        ucFileAttr = 0x20;
    }
    else
    {
        ucFileAttr = 0x10;
    }

    // Parse the Entry
    for(BYTE ucLoopI = 0; ucLoopI < 12; ucLoopI++)
    {
        // Check File Name
        if(ucLoopI < ucFileNameLen_SFN)
        {
            if(pucData[ucCurEntryOffset * 32 + ucLoopI] != ScalerUsbFileSysFat32MapSfn((2 + ucLoopI), pucGoldenName))
            {
                return _FALSE;
            }
        }
        // Check Padding (space)
        else if(ucLoopI < 8)
        {
            if(pucData[ucCurEntryOffset * 32 + ucLoopI] != 0x20)
            {
                return _FALSE;
            }
        }
        // Check File Extension
        else if(ucLoopI < 11)
        {
            if(bIsFile == _TRUE)
            {
                if(pucData[ucCurEntryOffset * 32 + ucLoopI] != ScalerUsbFileSysFat32MapSfn((2 + ucFileNameLen_SFN + 1 + (ucLoopI - 8)), pucGoldenName))
                {
                    return _FALSE;
                }
            }
            else
            {
                if(pucData[ucCurEntryOffset * 32 + ucLoopI] != 0x20)
                {
                    return _FALSE;
                }
            }
        }
        // Check Attr
        else if(ucLoopI == 11)
        {
            if(pucData[ucCurEntryOffset * 32 + ucLoopI] != ucFileAttr)
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Search LFN under FAT32 system
// Input Value  : pucData: 512byte array
//                ucCurEntryOffset: offset to the Entry to compare
//                pucGoldenName
// Output Value : bLFNMatch
//--------------------------------------------------
bit ScalerUsbFileSysFat32SrchLfn(BYTE *pucData, bit bChkEnd, BYTE ucCurEntryOffset, BYTE ucCurMatchCnt, code BYTE *pucGoldenName)
{
    BYTE ucGoldenCharCnt = pucGoldenName[0];
    BYTE ucGoldenLfnCnt = 0x00;
    BYTE ucCurNameOffset = 0x00;
    BYTE ucLfnHdr = 0x00;
    BYTE ucOffsetTmp = 0x00;
    DWORD ulCurChar = 0x00;
    bit bLastLfn = _FALSE;

#if(_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON)
    if(bChkEnd == _FALSE)
    {
        ucGoldenCharCnt = _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN;

        if(ucCurMatchCnt == 0x00)
        {
            bLastLfn = _TRUE;
        }
    }
#endif

    // Calculate the Entry count of target File / Dir
    ucGoldenLfnCnt = ucGoldenCharCnt / 13;
    if((ucGoldenCharCnt % 13) != 0)
    {
        ucGoldenLfnCnt ++;
    }
    // 13 char in each FileName Entry
    ucCurNameOffset += (ucGoldenLfnCnt - ucCurMatchCnt - 1) * 13;

    // Entry[0], Header
    ucLfnHdr = pucData[ucCurEntryOffset * 32];
    if(bChkEnd == _TRUE)
    {
        if(ucCurMatchCnt == 0)
        {
            if((ucLfnHdr & 0xF0) != 0x40)
            {
                return _FALSE;
            }
        }
        else
        {
            if((ucLfnHdr & 0xF0) != 0x00)
            {
                return _FALSE;
            }
        }

        if((ucLfnHdr & 0x0F) != (ucGoldenLfnCnt - ucCurMatchCnt))
        {
            return _FALSE;
        }
    }
    else
    {
        // Free or Last Entry, not valid
        if((ucLfnHdr == 0xE5) || (ucLfnHdr == 0x00))
        {
            return _FALSE;
        }
    }

    // Entry[1] - [10]
    ucOffsetTmp = 1;
    for(BYTE ucLoopI = 0; ucLoopI < 5; ucLoopI ++)
    {
        ulCurChar = TO_WORD(pucData[ucCurEntryOffset * 32 + ucOffsetTmp + ucLoopI * 2 + 1], pucData[ucCurEntryOffset * 32 + ucOffsetTmp + ucLoopI * 2]);

        if(ulCurChar != ScalerUsbFileSysFat32MapLfn(ucCurNameOffset, pucGoldenName))
        {
            return _FALSE;
        }
        ucCurNameOffset ++;
        if((bChkEnd == _FALSE) && (bLastLfn) && (ucCurNameOffset == ucGoldenCharCnt))
        {
            return _TRUE;
        }
    }

    // Entry[11], Attr
    if(pucData[ucCurEntryOffset * 32 + 11] != 0x0F)
    {
        return _FALSE;
    }

    // Entry[12], rsvd
    if(pucData[ucCurEntryOffset * 32 + 12] != 0x00)
    {
        return _FALSE;
    }

    // Entry[13], chk-sum (not checked)

    // Entry[14] - [25]
    ucOffsetTmp = 14;
    for(BYTE ucLoopI = 0; ucLoopI < 6; ucLoopI ++)
    {
        ulCurChar = TO_WORD(pucData[ucCurEntryOffset * 32 + ucOffsetTmp + ucLoopI * 2 + 1], pucData[ucCurEntryOffset * 32 + ucOffsetTmp + ucLoopI * 2]);
        if(ulCurChar != ScalerUsbFileSysFat32MapLfn(ucCurNameOffset, pucGoldenName))
        {
            return _FALSE;
        }
        ucCurNameOffset ++;
        if((bChkEnd == _FALSE) && (bLastLfn) && (ucCurNameOffset == ucGoldenCharCnt))
        {
            return _TRUE;
        }
    }

    // Entry[26] - [27], rsvd
    if((pucData[ucCurEntryOffset * 32 + 26] != 0x00) || (pucData[ucCurEntryOffset * 32 + 26] != 0x00))
    {
        return _FALSE;
    }

    // Entry[28] - [31]
    ucOffsetTmp = 28;
    for(BYTE ucLoopI = 0; ucLoopI < 2; ucLoopI ++)
    {
        ulCurChar = TO_WORD(pucData[ucCurEntryOffset * 32 + ucOffsetTmp + ucLoopI * 2 + 1], pucData[ucCurEntryOffset * 32 + ucOffsetTmp + ucLoopI * 2]);
        if(ulCurChar != ScalerUsbFileSysFat32MapLfn(ucCurNameOffset, pucGoldenName))
        {
            return _FALSE;
        }
        ucCurNameOffset ++;
        if((bChkEnd == _FALSE) && (bLastLfn) && (ucCurNameOffset == ucGoldenCharCnt))
        {
            return _TRUE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Short File Directory Entry(32byte), mainly FileStartclusNo and FileSize.
// Input Value  : pucData: 512byte array where the file directory entry is located.
//                usOffset: The location of the short file directory entry in 512byte.
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysFat32GetSfnInfo(BYTE *pucData, BYTE ucCurEntryOffset)
{
    WORD usOffset = ucCurEntryOffset * 32;

    g_stUsbFileSysFileInfo.ulFileStartClusNum = TO_DWORD(pucData[(usOffset + 21)], pucData[(usOffset + 20)], pucData[(usOffset + 27)], pucData[(usOffset + 26)]);
    DebugMessageU2Host("[FileSys][FAT32] Target File Start Clus Num", g_stUsbFileSysFileInfo.ulFileStartClusNum);

    g_stUsbFileSysFileInfo.uqFileSizeInByte = TO_QWORD(TO_DWORD(0x00, 0x00, 0x00, 0x00),
                                                       TO_DWORD(pucData[(usOffset + 31)], pucData[(usOffset + 30)], pucData[(usOffset + 29)], pucData[(usOffset + 28)]));
    DebugMessageU2Host("[FileSys][FAT32] Target File Size (Byte)", g_stUsbFileSysFileInfo.uqFileSizeInByte);

    // Get total clus num occupied by File.TotalClusNum = (FileSize(KB) / BytesPecClus(KB)).
    g_stUsbFileSysFileInfo.usFileSizeInClus = ((g_stUsbFileSysFileInfo.uqFileSizeInByte >> 10) / ((g_stUsbFileSysDbrTable.ulSecPerClus * g_stUsbFileSysDbrTable.usBytePerSec) >> 10));
    if(((g_stUsbFileSysFileInfo.uqFileSizeInByte >> 10) % ((g_stUsbFileSysDbrTable.ulSecPerClus * g_stUsbFileSysDbrTable.usBytePerSec) >> 10)) != 0)
    {
        // Ceiling, since there is a partially occupied Cluster
        g_stUsbFileSysFileInfo.usFileSizeInClus += 1;
    }

    g_stUsbFileSysFileInfo.ulFileLastClusNum = g_stUsbFileSysFileInfo.ulFileStartClusNum + g_stUsbFileSysFileInfo.usFileSizeInClus - 1;
}

//--------------------------------------------------
// Description  : Mapping User File Name to FAT32 File Name
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsbFileSysFat32ChkGoldenFileName(EnumUsbFileSysSrchType enumSrchType)
{
    BYTE ucFileNameCnt = 0;
    BYTE ucFileNameCnt_SFN = 0;
    BYTE *pucGoldenFileName = 0x00;
    bit bSpaceExist = _FALSE;

    switch(enumSrchType)
    {
        case _SRCH_1ST_SUB_DIR_FROM_ROOT:

            // Search Type = Search Sub Dir
            pucGoldenFileName = &tUsb2HostFwUpdateFolderName[0];
            ucFileNameCnt = pucGoldenFileName[0];
            // Folders doesn't have file extension
            ucFileNameCnt_SFN = ucFileNameCnt;

            break;

        default:

            // Search Type = Search File
            pucGoldenFileName = &tUsb2HostFwUpdateFileName[0];

#if(_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON)
            // There will be a '_' between ProjPart and VerPart
            ucFileNameCnt = _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN;
            if((ucFileNameCnt % 13 + _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN) > 13)
            {
                // This case, will need extra process to store the Fw Version
                DebugMessageU2Host("[GoldenName] Warning: in FAT32, Version need an extra process", 0);
            }
#else
            ucFileNameCnt = pucGoldenFileName[0];
#endif
            // subtract file extension (pucGoldenFileName[0] indicate the whole Len of FileName)
            ucFileNameCnt_SFN = pucGoldenFileName[0] - 4;

            break;
    }

    // Check if SPACE exist in UserFileName
    for(BYTE ucLoop = 0; ucLoop < ucFileNameCnt_SFN; ucLoop++)
    {
        if(pucGoldenFileName[2 + ucLoop] == ' ')
        {
            bSpaceExist = _TRUE;
        }
    }

    if((bSpaceExist != 0) && (pucGoldenFileName[1] == 0))
    {
        DebugMessageU2Host("[FAT32][GoldenName] User Define File Name invalid, second byte should present if SPACE exist !!", pucGoldenFileName[1]);
    }

    // Set FAT32 File Directory Structure Type for GetGoldenFileName() & SearchFileName()
    if((ucFileNameCnt_SFN <= 8) && (bSpaceExist == _FALSE))
    {
        SET_U2HOST_FAT32_FILENAME_TYPE(_ONLY_SFN);
    }
    else
    {
        SET_U2HOST_FAT32_FILENAME_TYPE(_SFN_AND_LFN);
    }

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
    // File name Load to Global variable
    for(BYTE ucLoop = 0; ucLoop < 64; ucLoop++)
    {
        g_pucUsbFileSysGoldenFileName[ucLoop] = tUsb2HostDBDumpFileName[ucLoop];
    }
#endif // End of #if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)

    DebugMessageU2Host("[FAT32][GoldenName] Mapping FAT32 Done !!", 0);
}

//--------------------------------------------------
// Description  : Mapping User Short File Name to FAT32 Short File Name
// Input Value  : ucFileNameOffset, pucGoldenName
// Output Value : ucSfnASCIICode
//--------------------------------------------------
BYTE ScalerUsbFileSysFat32MapSfn(BYTE ucFileNameOffset, code BYTE *pucGoldenName)
{
    BYTE ucSfnASCIICode = 0x00;

    if((pucGoldenName[ucFileNameOffset] >= 'a') && (pucGoldenName[ucFileNameOffset] <= 'z'))
    {
        // transfer Lowercase to Uppercase
        ucSfnASCIICode = pucGoldenName[ucFileNameOffset] - 32;
    }
    else
    {
        ucSfnASCIICode = pucGoldenName[ucFileNameOffset];
    }

    return ucSfnASCIICode;
}

//--------------------------------------------------
// Description  : Mapping User File Name to FAT32 Long File Name
// Input Value  : ucFileNameOffset, pucGoldenName
// Output Value : usLfnASCIICode
//--------------------------------------------------
WORD ScalerUsbFileSysFat32MapLfn(BYTE ucFileNameOffset, code BYTE *pucGoldenName)
{
    WORD usLfnASCIICode = 0x00;
    BYTE ucFileNameCount = pucGoldenName[0];

    if(ucFileNameOffset < ucFileNameCount)
    {
        // fill in File Name
        usLfnASCIICode = TO_WORD(0x00, pucGoldenName[ucFileNameOffset + 2]);
    }
    else if(ucFileNameOffset == ucFileNameCount)
    {
        // File Name terminated, fill in NULL
        usLfnASCIICode = 0x0000;
    }
    else
    {
        usLfnASCIICode = 0xFFFF;
    }

    return usLfnASCIICode;
}

//--------------------------------------------------
// Description  : Get Char in LFN
// Input Value  : ucFileNameOffset, pucGoldenName
// Output Value : usLfnASCIICode
//--------------------------------------------------
BYTE ScalerUsbFileSysFat32GetLfnChar(BYTE ucCharOffset, BYTE *pucLfn)
{
    if(ucCharOffset < 5)
    {
        return pucLfn[0x01 + ucCharOffset * 2];
    }
    else if(ucCharOffset < 11)
    {
        return pucLfn[0x0E + (ucCharOffset - 5) * 2];
    }
    else if(ucCharOffset < 13)
    {
        return pucLfn[0x1C + (ucCharOffset - 11) * 2];
    }
    else
    {
        DebugMessageU2Host("[FileSys][FAT32] Warning: only 13 Char in a LFN", ucCharOffset);
        return 0x00;
    }
}

#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Parse File Entry under exFAT system
// Input Value  : pucData: 512byte array
//                enumSrchType
//                ucSrchEntryNum
// Output Value : None
//--------------------------------------------------
bit ScalerUsbFileSysExfatParseFileEntry(EnumUsbFileSysSrchType enumSrchType, BYTE *pucData, BYTE *pucCurEntryOffset, BYTE *pucNxtEntrySetOffset, BYTE *pucCurMatchCnt, bit b2ndLoop)
{
    BYTE ucGoldenFileAttr = 0x00;
    BYTE ucGoldenFileNameLen = 0x00;
    BYTE *pucGoldenFileName = 0x00;
    BYTE ucFileNameLen = 0x00;

    switch(enumSrchType)
    {
        case _SRCH_1ST_SUB_DIR_FROM_ROOT:

            // Search Type = Search Sub Dir
            ucGoldenFileAttr = 0x10;
            pucGoldenFileName = &tUsb2HostFwUpdateFolderName[0];
            break;

        default:

            // Search Type = Search File
            ucGoldenFileAttr = 0x20;
            pucGoldenFileName = &tUsb2HostFwUpdateFileName[0];
            break;
    }

    ucGoldenFileNameLen = pucGoldenFileName[0];

    // Search
    while(*pucCurEntryOffset < (512 / _U2HOST_FILE_SYS_FAT_ENTRY_SIZE))
    {
        // 1. Check EntryType = 0x85 (File & Dir Entry)
        if(*pucCurMatchCnt == 0)
        {
            if(pucData[(*pucCurEntryOffset * 32) + 0] == 0x85)
            {
                *pucNxtEntrySetOffset = *pucCurEntryOffset + (pucData[(*pucCurEntryOffset * 32) + 1] + 1);

                // Check FileAttr (File / Dir)
                if(pucData[(*pucCurEntryOffset * 32) + 4] == ucGoldenFileAttr)
                {
                    // set CurEntryOffset to Stream Ext. Entry
                    *pucCurEntryOffset += 1;

                    *pucCurMatchCnt += 1;
                }
                else
                {
                    // Go to next Entry Set
                    *pucCurEntryOffset = *pucNxtEntrySetOffset;
                    continue;
                }
            }
            else
            {
                // Not File & Dir Entry, go to next Entry
                *pucCurEntryOffset += 1;
                continue;
            }
        }

        // 2. Check EntryType = 0xC0 (Stream Ext. Entry)
        if((*pucCurMatchCnt == 1) && (*pucCurEntryOffset < (512 / _U2HOST_FILE_SYS_FAT_ENTRY_SIZE)))
        {
            if(pucData[(*pucCurEntryOffset * 32) + 0] == 0xC0)
            {
                // Get current FileNameLen from Stream Ext. Dir Entry
                ucFileNameLen = pucData[(*pucCurEntryOffset * 32) + 3];
                // Check FileNameLen
                if(ucFileNameLen == ucGoldenFileNameLen)
                {
                    // Record current StrmExt (Clus / Sec / Entry)
                    g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexStrmExt = g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexShadow;
                    g_stUsbFileSysFatInfo.usSecInClusStrmExt = (GET_U2HOST_CUR_LBA() - GET_U2HOST_CUR_CLUS_START_LBA());
                    if(b2ndLoop)
                    {
                        g_stUsbFileSysFatInfo.usSecInClusStrmExt += 1;
                    }
                    g_stUsbFileSysFatInfo.ucEntryInSecStrmExt = *pucCurEntryOffset;

                    // set CurEntryOffset to 1st FileName Dir Entry
                    *pucCurEntryOffset += 1;
                    *pucCurMatchCnt += 1;
                }
                else
                {
                    // Reset MatchCnt
                    *pucCurMatchCnt = 0;
                    // Go to next Entry Set
                    *pucCurEntryOffset = *pucNxtEntrySetOffset;
                    continue;
                }
            }
            else
            {
                // Reset MatchCnt
                *pucCurMatchCnt = 0;
                // Go to next Entry Set
                *pucCurEntryOffset = *pucNxtEntrySetOffset;
                continue;
            }
        }

        // 3. Check FileName Dir Entry
        if((*pucCurMatchCnt > 1) && (*pucCurEntryOffset < (512 / _U2HOST_FILE_SYS_FAT_ENTRY_SIZE)))
        {
            if(ScalerUsbFileSysExfatSrchFileName(pucData, pucCurEntryOffset, pucCurMatchCnt, pucGoldenFileName) == _TRUE)
            {
                // Target Dir / File found
                if(*pucCurMatchCnt == 0)
                {
                    // Record Target SFN (Clus / Sec / Entry)
                    g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexTarget = g_stUsbFileSysFatInfo.stFatDirInfo.ucIndexStrmExt;
                    g_stUsbFileSysFatInfo.usSecInClusTarget = g_stUsbFileSysFatInfo.usSecInClusStrmExt;
                    g_stUsbFileSysFatInfo.ucEntryInSecTarget = g_stUsbFileSysFatInfo.ucEntryInSecStrmExt;

                    SET_U2HOST_SEARCH_NAME_STATUS(_USB_FILE_SYS_SRCH_FINISH);
                    return _TRUE;
                }
                // Else, other FileName Entry in next Sector
            }
            else
            {
                // Reset MatchCnt
                *pucCurMatchCnt = 0;
                // Go to next Entry Set
                *pucCurEntryOffset = *pucNxtEntrySetOffset;
                continue;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Search File Name under exFAT system
// Input Value  : pucData: 512byte array
//                ucCurEntryOffset: offset to the 1st FileName Entry begins
//                pucGoldenName
// Output Value : bFileNameMatch
//--------------------------------------------------
bit ScalerUsbFileSysExfatSrchFileName(BYTE *pucData, BYTE *pucCurEntryOffset, BYTE *pucCurMatchCnt, code BYTE *pucGoldenName)
{
    BYTE ucGoldenFileNameLen = pucGoldenName[0];
    BYTE ucGoldenEntryCnt = 0x00;
    WORD usCurNameOffset = 0x00;
    BYTE ucLoopJ = 0x00;

    // Calculate the Entry count of target File / Dir
    ucGoldenFileNameLen = pucGoldenName[0];
    ucGoldenEntryCnt = ucGoldenFileNameLen / 15;
    if((ucGoldenFileNameLen % 15) != 0)
    {
        ucGoldenEntryCnt ++;
    }
    // 15 char in each FileName Entry
    usCurNameOffset += (*pucCurMatchCnt - 2) * 15;

    // Search
    while(*pucCurEntryOffset < (512 / _U2HOST_FILE_SYS_FAT_ENTRY_SIZE))
    {
        // Parse each Entry
        for(ucLoopJ = 0; ucLoopJ < 16; ucLoopJ++)
        {
            // 1. Check EntryType / SecondaryFlags = 0xC1 (FileName Dir Entry)
            if(ucLoopJ == 0)
            {
                // EntryType = 0xC1 (FileName Dir Entry)
                if(pucData[(*pucCurEntryOffset * 32) + ucLoopJ] != 0xC1)
                {
                    return _FALSE;
                }
                if(pucData[(*pucCurEntryOffset * 32) + ucLoopJ + 1] != 0x00)
                {
                    return _FALSE;
                }
            }
            // 2. Check FineName
            else
            {
                if(pucData[(*pucCurEntryOffset * 32) + ucLoopJ * 2] == pucGoldenName[2 + usCurNameOffset])
                {
                    usCurNameOffset ++;

                    if(usCurNameOffset == ucGoldenFileNameLen)
                    {
                        *pucCurMatchCnt = 0;
                        return _TRUE;
                    }
                    else if(ucLoopJ == 15)
                    {
                        *pucCurMatchCnt += 1;
                        *pucCurEntryOffset += 1;
                    }
                }
                else
                {
                    return _FALSE;
                }
            }
        }
    }

    // Fragmented FileName (Compare Process on-going)
    return _TRUE;
}

//--------------------------------------------------
// Description  : Get File / Dir info.
// Input Value  : pucData: 512byte array
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysExfatGetStrmExtInfo(BYTE *pucData, BYTE ucCurEntryOffset, EnumUsbFileSysSrchType enumSrchType)
{
    WORD usOffset = ucCurEntryOffset * 32;
    BYTE ucGeneralSecondaryFlags = pucData[usOffset + 1];

    // Check flag: AllocationPossible
    if((ucGeneralSecondaryFlags & _BIT0) != _BIT0)
    {
        DebugMessageU2Host("[FileSys][exFAT] Warning: AllocationPossible != 1'b1 !", ucGeneralSecondaryFlags);
        return;
    }

    // Record flag: NoFatChain
    switch(enumSrchType)
    {
        case _SRCH_1ST_SUB_DIR_FROM_ROOT:

            // Search Type = Search Dir
            g_stUsbFileSysFatInfo.b1stSubDirNoFatChain = (bit)((ucGeneralSecondaryFlags & _BIT1) >> 1);
            break;

        default:

            // Search Type = Search File
            g_stUsbFileSysFatInfo.bFileNoFatChain = (bit)((ucGeneralSecondaryFlags & _BIT1) >> 1);
            break;
    }

    g_stUsbFileSysFileInfo.ulFileStartClusNum = TO_DWORD(pucData[usOffset + 23], pucData[usOffset + 22], pucData[usOffset + 21], pucData[usOffset + 20]);
    DebugMessageU2Host("[FileSys][exFAT] Target File Start Clus Num", g_stUsbFileSysFileInfo.ulFileStartClusNum);
    g_stUsbFileSysFileInfo.uqFileSizeInByte = TO_QWORD(TO_DWORD(pucData[usOffset + 31], pucData[usOffset + 30], pucData[usOffset + 29], pucData[usOffset + 28]),
                                                       TO_DWORD(pucData[usOffset + 27], pucData[usOffset + 26], pucData[usOffset + 25], pucData[usOffset + 24]));
    DebugMessageU2Host("[FileSys][exFAT] Target File Size (Byte)", g_stUsbFileSysFileInfo.uqFileSizeInByte);

    // Get total clus num occupied by File.TotalClusNum = (uqFileSizeInByte(KB) / BytesPecClus(KB)).
    g_stUsbFileSysFileInfo.usFileSizeInClus = ((g_stUsbFileSysFileInfo.uqFileSizeInByte >> 10) / ((g_stUsbFileSysDbrTable.ulSecPerClus * g_stUsbFileSysDbrTable.usBytePerSec) >> 10));
    if(((g_stUsbFileSysFileInfo.uqFileSizeInByte >> 10) % ((g_stUsbFileSysDbrTable.ulSecPerClus * g_stUsbFileSysDbrTable.usBytePerSec) >> 10)) != 0)
    {
        // Ceiling, since there is a partially occupied Cluster
        g_stUsbFileSysFileInfo.usFileSizeInClus += 1;
    }

    g_stUsbFileSysFileInfo.ulFileLastClusNum = g_stUsbFileSysFileInfo.ulFileStartClusNum + g_stUsbFileSysFileInfo.usFileSizeInClus - 1;
}
#endif // End of #if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate all the needed LBA info. for NTFS parsing (from MBR & DBR)
// Input Value  : ucCurPtnNum
// Output Value : bValidNtfs
//--------------------------------------------------
bit ScalerUsbFileSysNtfsCalInfo(BYTE ucCurPtnNum)
{
    bit bValidNtfs = 0;

    // Parse the SecPerMftRecord by 2's complement
    if((g_stUsbFileSysDbrTable.ucClusPerMftRecord >> 7) == 0)
    {
        // unit: cluster
        g_stUsbFileSysNtfsInfo.ulSecPerMftRecord = g_stUsbFileSysDbrTable.ucClusPerMftRecord * g_stUsbFileSysDbrTable.ulSecPerClus;
    }
    else
    {
        // unit: byte
        g_stUsbFileSysNtfsInfo.ulSecPerMftRecord = (1 << (~g_stUsbFileSysDbrTable.ucClusPerMftRecord + 1)) / g_stUsbFileSysDbrTable.usBytePerSec;
    }

    // Parse the SecPerIdxRecord by 2's complement
    if((g_stUsbFileSysDbrTable.ucClusPerIdxRecord >> 7) == 0)
    {
        // unit: cluster
        g_stUsbFileSysNtfsInfo.ulSecPerIdxRecord = g_stUsbFileSysDbrTable.ucClusPerIdxRecord * g_stUsbFileSysDbrTable.ulSecPerClus;
    }
    else
    {
        // unit: byte
        g_stUsbFileSysNtfsInfo.ulSecPerIdxRecord = (1 << (~g_stUsbFileSysDbrTable.ucClusPerIdxRecord + 1)) / g_stUsbFileSysDbrTable.usBytePerSec;
    }

    // ulNtfsRootEntryLBA = ulDbrStartLBA + ulMftClus * ulSecPerClus + 5 * ulSecPerMftRecord
    if(g_pstUsbFileSysMbrPartitionEntry[0].ucSystemID == 0xEE)
    {
        g_stUsbFileSysNtfsInfo.ulNtfsRootEntryLBA = g_pstUsbFileSysGptEntry[ucCurPtnNum].ulDbrStartLBA +
                                                    g_stUsbFileSysDbrTable.ulMftClus * g_stUsbFileSysDbrTable.ulSecPerClus + g_stUsbFileSysNtfsInfo.ulSecPerMftRecord * 5;
    }
    else
    {
        g_stUsbFileSysNtfsInfo.ulNtfsRootEntryLBA = g_pstUsbFileSysMbrPartitionEntry[ucCurPtnNum].ulDbrStartLBA +
                                                    g_stUsbFileSysDbrTable.ulMftClus * g_stUsbFileSysDbrTable.ulSecPerClus + g_stUsbFileSysNtfsInfo.ulSecPerMftRecord * 5;
    }

    // Judge if the NTFS partition supported
    if(g_stUsbFileSysDbrTable.usBytePerSec != 0x0200)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: BytePerSec != 512, not supported !", g_stUsbFileSysDbrTable.usBytePerSec);
    }
    else if(g_stUsbFileSysDbrTable.ulSecInVolumeH != 0x00)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: NTFS volume > 2TB, not supported !", g_stUsbFileSysDbrTable.ulSecInVolumeH);
    }
    else if(g_stUsbFileSysNtfsInfo.ulSecPerMftRecord != 0x02)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: NTFS MFT Record != 1024 Bytes, not supported !", g_stUsbFileSysNtfsInfo.ulSecPerMftRecord);
    }
    else
    {
        DebugMessageU2Host("[FileSys][NTFS] ulNtfsRootEntryLBA", g_stUsbFileSysNtfsInfo.ulNtfsRootEntryLBA);
        bValidNtfs = _TRUE;
    }

    return bValidNtfs;
}

//--------------------------------------------------
// Description  : Parse the File Record Header
// Input Value  : pucData: byte array of File Record
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysNtfsParseMftHdr(BYTE *pucData)
{
    DWORD ulSanityCheck = 0x00;
    WORD usFixUpOffset = 0x00;
    WORD usFixUpLen = 0x00;
    WORD usFileRecordFlags = 0x00;

    ulSanityCheck = TO_DWORD(pucData[0x03], pucData[0x02], pucData[0x01], pucData[0x00]);
    usFixUpOffset = TO_WORD(pucData[0x05], pucData[0x04]);
    usFixUpLen = TO_WORD(pucData[0x07], pucData[0x06]);
    usFileRecordFlags = (TO_WORD(pucData[0x17], pucData[0x16]) & 0x01);

    // Check if the $Root MFT Record is valid (Sanity = "FILE") & used
    if((ulSanityCheck != 0x454C4946) || (usFileRecordFlags != 0x01))
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: MFT Record invalid / not in use !", usFileRecordFlags);
    }
    if(usFixUpOffset > 0xFF)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: FixUp Offset > 255 !", usFixUpOffset);
    }
    if((usFixUpLen * 2) != (2 * 2 + 2))
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: FixUp in MFT != 3 !", usFixUpLen);
    }

    for(BYTE ucLoop = 0; ucLoop < usFixUpLen; ucLoop ++)
    {
        if(ucLoop == 0)
        {
            g_stUsbFileSysNtfsInfo.pucCurFixUpNum[0] = pucData[usFixUpOffset + 0];
            g_stUsbFileSysNtfsInfo.pucCurFixUpNum[1] = pucData[usFixUpOffset + 1];
        }
        else
        {
            g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * (ucLoop - 1)] = pucData[usFixUpOffset + 2 * ucLoop];
            g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * (ucLoop - 1) + 1] = pucData[usFixUpOffset + 2 * ucLoop + 1];
        }
    }
}

//--------------------------------------------------
// Description  : Parse the MFT File Record
// Input Value  : pucData: byte array of MFT File Record
//                ucTargetId: the AttrId of the target Attr.
// Output Value : usOffset
//--------------------------------------------------
WORD ScalerUsbFileSysNtfsSrchMftAttr(BYTE *pucData, BYTE ucTargetId)
{
    WORD usOffset = 0x00;
    WORD usRecordLen = 0x00;
    bit b2nd512 = _FALSE;

    ScalerUsbU2HostGetBufferBulkData(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0, pucData, 512);
    ScalerUsbFileSysNtfsFixUpArray(pucData, 0, 0);

    usOffset = TO_WORD(pucData[0x15], pucData[0x14]);
    usRecordLen = TO_WORD(pucData[0x19], pucData[0x18]);

    // The End of MFT Record is padded with 4 Byte 0xFF + 4 Byte 0x00
    while((usOffset + 8) < usRecordLen)
    {
        // Check if AttrId matches
        if(pucData[usOffset] == ucTargetId)
        {
            if(b2nd512 == _TRUE)
            {
                usOffset += 512;
            }
            return usOffset;
        }
        else
        {
            // set Offset to Next Attr.
            usOffset += TO_WORD(pucData[usOffset + 0x05], pucData[usOffset + 0x04]);

            // Check if the entry size is in next 512 Bytes
            if((usOffset + 6) >= 512)
            {
                b2nd512 = _TRUE;
                usRecordLen -= 512;
                usOffset -= 512;

                ScalerUsbU2HostGetBufferBulkData(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 512, pucData, 512);
                ScalerUsbFileSysNtfsFixUpArray(pucData, 1, 0);
            }
        }
    }

    // Target Attr. Id not found
    DebugMessageU2Host("[FileSys][NTFS] Warning: Target Attr. Id not found !", ucTargetId);
    return 0x00;
}

//--------------------------------------------------
// Description  : Process the FixUp Sequence
// Input Value  : pucData: 512 bytes array of MFT File Record / Index Record
//                ucSecNum: the Sector Number of the current 512 bytes
//              : usOffset: the offset of pucData[0] in the current Sector
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysNtfsFixUpArray(BYTE *pucData, BYTE ucSecNum, WORD usOffset)
{
    bit bFixUpFail = _FALSE;

    // Re-fill the data back from FixUpArray
    if(usOffset <= 510)
    {
        if((pucData[510 - usOffset] == g_stUsbFileSysNtfsInfo.pucCurFixUpNum[0]) && (pucData[511 - usOffset] == g_stUsbFileSysNtfsInfo.pucCurFixUpNum[1]))
        {
            pucData[510 - usOffset] = g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * ucSecNum];
            pucData[511 - usOffset] = g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * ucSecNum + 1];
        }
        else
        {
            bFixUpFail = _TRUE;
        }
    }
    // deal with corner
    else if(usOffset == 511)
    {
        if((pucData[510 - usOffset + 512] == g_stUsbFileSysNtfsInfo.pucCurFixUpNum[0]) && (pucData[511 - usOffset] == g_stUsbFileSysNtfsInfo.pucCurFixUpNum[1]))
        {
            pucData[510 - usOffset + 512] = g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * (ucSecNum + 1)];
            pucData[511 - usOffset] = g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * ucSecNum + 1];
        }
        else
        {
            bFixUpFail = _TRUE;
        }
    }

    if(bFixUpFail)
    {
        DebugMessageU2Host("[FileSys][NTFS] Err: FixUpArray Fail !", usOffset);
    }
}

//--------------------------------------------------
// Description  : Parse the Index Root Attribute (0x90) in MFT Record
// Input Value  : pucData: byte array of Index Root Attr.
// Output Value : bIdxAllocExist
//--------------------------------------------------
bit ScalerUsbFileSysNtfsParseIdxRootAttr(BYTE *pucData)
{
    bit bIdxAllocExist = _FALSE;
    WORD usNodeHdrOffset = 0x00;
    BYTE ucNodeHdrFlags = 0x00;

    // Note: This is a Named, Resident Attr.

    // Offset to Node Header = AttrHdrLen + IdxRootLen(16B)
    usNodeHdrOffset = TO_WORD(pucData[0x15], pucData[0x14]) + 0x10;

    ucNodeHdrFlags = pucData[usNodeHdrOffset + 0x0C];

    if(ucNodeHdrFlags == 0x01)
    {
        bIdxAllocExist = _TRUE;
    }
    return bIdxAllocExist;
}

//--------------------------------------------------
// Description  : Parse the Index Allocation Attribute (0xA0) in MFT Record
// Input Value  : pucData: byte array of Index Allocation Attr.
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysNtfsParseIdxAllocAttr(BYTE *pucData)
{
    // Note: This is a Named, Non-Resident Attr.

    BYTE ucAttrType = pucData[0x00];
    BYTE ucNonResident = pucData[0x08];
    WORD usDataRunOffset = TO_WORD(pucData[0x21], pucData[0x20]);
    DWORD ulAttrLen = TO_DWORD(pucData[0x07], pucData[0x06], pucData[0x05], pucData[0x04]);
    DWORD ulDataRunLen = 0x00;

    // DataRunLen = AttrLen - AttrHdrLen - 2 * NameLen
    ulDataRunLen = ulAttrLen - 0x40 - (2 * pucData[0x09]);

    if((ucAttrType != 0xA0) || (ucNonResident != 0x01))
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: invalid Index Allocation Attr. (0xA0) !", g_stUsbFileSysNtfsInfo.ulSecPerMftRecord);
        return;
    }
    if(ulDataRunLen > 32)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: Index Buffer DataRun > 32 Bytes !", g_stUsbFileSysNtfsInfo.ulSecPerMftRecord);
    }

    // Store the DataRun
    for(BYTE ucLoop = 0; ucLoop < 32; ucLoop++)
    {
        g_stUsbFileSysNtfsInfo.pucCurDataRun[ucLoop] = pucData[usDataRunOffset + ucLoop];

        if(ucLoop == ulDataRunLen)
        {
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Parse the Data Attribute (0x80) in MFT Record
// Input Value  : pucData: byte array of Data Attr.
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysNtfsParseDataAttr(BYTE *pucData)
{
    // Note: This is a un-named, Non-Resident Attr. (Unless it's a very small File)

    BYTE ucAttrType = pucData[0x00];
    BYTE ucNonResident = pucData[0x08];
    WORD usDataRunOffset = TO_WORD(pucData[0x21], pucData[0x20]);
    DWORD ulAttrLen = TO_DWORD(pucData[0x07], pucData[0x06], pucData[0x05], pucData[0x04]);
    DWORD ulDataRunLen = 0x00;

    // DataRunLen = AttrLen - AttrHdrLen - 2 * NameLen
    ulDataRunLen = ulAttrLen - 0x40 - (2 * pucData[0x09]);

    if((ucAttrType != 0x80) || (ucNonResident != 0x01))
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: invalid Data Attr. (0x80) !", 0x00);
        return;
    }
    if(ulDataRunLen > 32)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: Data DataRun > 32 Bytes !", 0x00);
    }

    // Store the Data Size (4 Bytes is enough for a FW bin)
    g_stUsbFileSysFileInfo.uqFileSizeInByte = TO_QWORD(TO_DWORD(0x00, 0x00, 0x00, 0x00),
                                                       TO_DWORD(pucData[0x2B], pucData[0x2A], pucData[0x29], pucData[0x28]));
    DebugMessageU2Host("[FileSys][NTFS] Target File Size (Byte)", g_stUsbFileSysFileInfo.uqFileSizeInByte);

    // Get total clus num occupied by File.TotalClusNum = (FileSize(KB) / BytesPecClus(KB)).
    g_stUsbFileSysFileInfo.usFileSizeInClus = ((g_stUsbFileSysFileInfo.uqFileSizeInByte >> 10) / ((g_stUsbFileSysDbrTable.ulSecPerClus * g_stUsbFileSysDbrTable.usBytePerSec) >> 10));
    if(((g_stUsbFileSysFileInfo.uqFileSizeInByte >> 10) % ((g_stUsbFileSysDbrTable.ulSecPerClus * g_stUsbFileSysDbrTable.usBytePerSec) >> 10)) != 0)
    {
        // Ceiling, since there is a partially occupied Cluster
        g_stUsbFileSysFileInfo.usFileSizeInClus += 1;
    }

    // Store the DataRun
    for(BYTE ucLoop = 0; ucLoop < 32; ucLoop++)
    {
        g_stUsbFileSysNtfsInfo.pucCurDataRun[ucLoop] = pucData[usDataRunOffset + ucLoop];

        if(ucLoop == ulDataRunLen)
        {
            break;
        }
    }

    g_stUsbFileSysFileInfo.ulFileStartClusNum = ScalerUsbFileSysNtfsParseDataRun(g_stUsbFileSysNtfsInfo.pucCurDataRun, 0);
    g_stUsbFileSysFileInfo.ulFileLastClusNum = ScalerUsbFileSysNtfsParseDataRun(g_stUsbFileSysNtfsInfo.pucCurDataRun, (g_stUsbFileSysFileInfo.usFileSizeInClus - 1));
}

//--------------------------------------------------
// Description  : Parse DataRun
// Input Value  : pucDataRun, usClusIdx
// Output Value : ulTargetClusNum: the start Cluster Number of usClusIdx
//--------------------------------------------------
DWORD ScalerUsbFileSysNtfsParseDataRun(BYTE *pucDataRun, WORD usClusIdx)
{
    BYTE ucLenSize = 0x00;
    BYTE ucOffsetSize = 0x00;
    BYTE ucRunOffset = 0x00;
    WORD usLen = 0x00;
    DWORD ulTargetClusNum = 0x00;
    DWORD ulCurClusOffset = 0x00;
    bit bCurClusOffsetNegative = _FALSE;
    BYTE ucLoop = 0x00;

    while(pucDataRun[ucRunOffset] != 0)
    {
        ucLenSize = pucDataRun[ucRunOffset] & 0x0F;
        ucOffsetSize = pucDataRun[ucRunOffset] >> 4;
        ulCurClusOffset = 0x00;
        bCurClusOffsetNegative = _FALSE;

        // Clear usLen for this is a new Run
        usLen = 0;

        // This func is able the support up to 65535 Unfragmented Cluster
        if(ucLenSize > 2)
        {
            DebugMessageU2Host("[FileSys][NTFS] Warning: ucLenSize in DataRun > 2 Byte !", ucLenSize);
        }
        if(ucOffsetSize > 4)
        {
            DebugMessageU2Host("[FileSys][NTFS] Warning: ucOffsetSize in DataRun > 4 Byte !", ucLenSize);
        }

        // Get the Len of this DataRun
        for(ucLoop = ucLenSize; ucLoop > 0; ucLoop--)
        {
            usLen <<= 8;
            usLen |= pucDataRun[ucRunOffset + ucLoop];
        }

        // Get the 1st Cluster Num of this DataRun
        if(ucRunOffset == 0x00)
        {
            // Cluster Num in 1st run is a unsigned num
            for(ucLoop = ucOffsetSize; ucLoop > 0; ucLoop--)
            {
                ulCurClusOffset <<= 8;
                ulCurClusOffset |= pucDataRun[ucRunOffset + ucLenSize + ucLoop];
            }
        }
        else
        {
            // Negative Cluster Offset
            if((pucDataRun[ucRunOffset + ucLenSize + ucOffsetSize] >> 7) != 0)
            {
                bCurClusOffsetNegative = _TRUE;

                for(ucLoop = ucOffsetSize; ucLoop > 0; ucLoop--)
                {
                    ulCurClusOffset <<= 8;
                    ulCurClusOffset |= (BYTE)(~pucDataRun[ucRunOffset + ucLenSize + ucLoop]);
                }
                ulCurClusOffset += 1;
            }
            // Positive Cluster Offset
            else
            {
                for(ucLoop = ucOffsetSize; ucLoop > 0; ucLoop--)
                {
                    ulCurClusOffset <<= 8;
                    ulCurClusOffset |= pucDataRun[ucRunOffset + ucLenSize + ucLoop];
                }
            }
        }

        if(bCurClusOffsetNegative)
        {
            ulTargetClusNum -= ulCurClusOffset;
        }
        else
        {
            ulTargetClusNum += ulCurClusOffset;
        }

        // Check if Target Cluster in this DataRun
        if(usClusIdx < usLen)
        {
            // Get the Target Cluster Num
            ulTargetClusNum += usClusIdx;
            return ulTargetClusNum;
        }
        // Check next DataRun
        else
        {
            usClusIdx -= usLen;
            ucRunOffset += (1 + ucLenSize + ucOffsetSize);
        }
    }

    DebugMessageU2Host("[FileSys][NTFS] Warning: usClusIdx exceed DataRun Size !", usClusIdx);
    return 0x00;
}

//--------------------------------------------------
// Description  : Parse the Index Record Header
// Input Value  : pucData: byte array of Index Record
// Output Value : None
//--------------------------------------------------
void ScalerUsbFileSysNtfsParseIdxRecordHdr(BYTE *pucData)
{
    DWORD ulSanityCheck = TO_DWORD(pucData[0x03], pucData[0x02], pucData[0x01], pucData[0x00]);
    WORD usFixUpOffset = TO_WORD(pucData[0x05], pucData[0x04]);
    WORD usFixUpLen = TO_WORD(pucData[0x07], pucData[0x06]);
    QWORD uqVcn = TO_QWORD(TO_DWORD(pucData[0x17], pucData[0x16], pucData[0x15], pucData[0x14]), TO_DWORD(pucData[0x13], pucData[0x12], pucData[0x11], pucData[0x10]));
    WORD usOffset = TO_WORD(pucData[0x19], pucData[0x18]);
    WORD usRecordLen = TO_WORD(pucData[0x1D], pucData[0x1C]);
    SBYTE pchDebugMsg[51] = "[FileSys][NTFS] IndexAlloc Cluster Num xx, LBA =  \0";

    // Vcn not checked, since in (IdxRecordSize < ClusterSize) case the Vcn value does not match the cluster num
    uqVcn = uqVcn;
    pchDebugMsg[0] = pchDebugMsg[0];

    pchDebugMsg[39] = 48 + ((g_stUsbFileSysNtfsInfo.usCurRootAllocClusIdx / 10) % 10);
    pchDebugMsg[40] = 48 + (g_stUsbFileSysNtfsInfo.usCurRootAllocClusIdx % 10);
    DebugMessageU2Host(pchDebugMsg, GET_U2HOST_CUR_LBA());

    // Check if the Index Record is valid (Sanity = "INDX")
    if(ulSanityCheck != 0x58444E49)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: Index Record invalid !", uqVcn);
    }
    if(usFixUpOffset > 0xFF)
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: FixUp Offset > 255 !", usFixUpOffset);
    }
    if((usFixUpLen * 2) != (8 * 2 + 2))
    {
        DebugMessageU2Host("[FileSys][NTFS] Warning: FixUp in MFT != 9 !", usFixUpLen);
    }

    // Get Index Buffer Info. from Header
    g_stUsbFileSysNtfsInfo.usCurIdxRecordLen = usRecordLen;
    // The Offset to entries is relative to 0x18 (Node Header)
    g_stUsbFileSysNtfsInfo.usByteOffsetInIdxRecord = usOffset + 0x18;

    for(BYTE ucLoop = 0; ucLoop < usFixUpLen; ucLoop ++)
    {
        if(ucLoop == 0)
        {
            g_stUsbFileSysNtfsInfo.pucCurFixUpNum[0] = pucData[usFixUpOffset + 0];
            g_stUsbFileSysNtfsInfo.pucCurFixUpNum[1] = pucData[usFixUpOffset + 1];
        }
        else
        {
            g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * (ucLoop - 1)] = pucData[usFixUpOffset + 2 * ucLoop];
            g_stUsbFileSysNtfsInfo.pucCurFixUpArray[2 * (ucLoop - 1) + 1] = pucData[usFixUpOffset + 2 * ucLoop + 1];
        }
    }
}

//--------------------------------------------------
// Description  : Search File Name under NTFS system
// Input Value  : pucData: 512byte array
// Output Value : usOffset: point to the next byte to view
//--------------------------------------------------
WORD ScalerUsbFileSysNtfsSrchFileName(BYTE *pucData, WORD usOffset, WORD usRecordLen)
{
    WORD usEntryLen = 0x00;
    WORD usIdxFlag = 0x00;
    BYTE ucFileNameLen = 0x00;
    BYTE ucGoldenFileNameLen = tUsb2HostFwUpdateFileName[0];
    BYTE ucFileNameMatchCnt = 0;
    BYTE ucLoopJ = 0x00;

    while(usOffset < usRecordLen)
    {
        // Get Entry Info.
        usEntryLen = TO_WORD(pucData[usOffset + 0x09], pucData[usOffset + 0x08]);
        usIdxFlag = TO_WORD(pucData[usOffset + 0x0D], pucData[usOffset + 0x0C]);
        ucFileNameLen = pucData[usOffset + 0x50];

        // The 'whole current Entry' exceed current 512 Byte
        if((usOffset + usEntryLen) > 512)
        {
            return usOffset;
        }

        // Check if Target File
        if(ucFileNameLen == ucGoldenFileNameLen)
        {
            for(ucLoopJ = 0; ucLoopJ < ucFileNameLen; ucLoopJ++)
            {
                if(pucData[usOffset + 0x52 + ucLoopJ * 2] == tUsb2HostFwUpdateFileName[2 + ucLoopJ])
                {
                    ucFileNameMatchCnt ++;
                }
                else if(pucData[usOffset + 0x52 + ucLoopJ * 2] > tUsb2HostFwUpdateFileName[2 + ucLoopJ])
                {
                    SET_U2HOST_NTFS_FILE_NOT_FOUND();
                    return 0x00;
                }
                else
                {
                    break;
                }
            }
        }

        if(ucFileNameMatchCnt == ucFileNameLen)
        {
            SET_U2HOST_SEARCH_NAME_STATUS(_USB_FILE_SYS_SRCH_FINISH);
            // Get File Info.
            g_stUsbFileSysNtfsInfo.ulFileMftNum = TO_DWORD(pucData[usOffset + 0x03], pucData[usOffset + 0x02], pucData[usOffset + 0x01], pucData[usOffset + 0x00]);

            return 0x00;
        }
        else if((usIdxFlag & _BIT1) == _BIT1)
        {
            // Last Entry in Node
            SET_U2HOST_NTFS_FILE_NOT_FOUND();
            return 0x00;
        }
        else
        {
            usOffset += usEntryLen;

            // The 'first 10 Byte of next Entry (the info. of size)' exceed current 512 Byte
            if(((usOffset + 10) > 512) && (usOffset <= usRecordLen))
            {
                return usOffset;
            }
        }
    }

    return 0x00;
}
#endif

#if((_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON) && (_CUSTOMER_FW_VERSION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get File FW Version LBA.
// Input Value  : None
// Output Value : ulFileFwVersionlLBA
//--------------------------------------------------
DWORD ScalerUsbFileSysGetFileFwVersionLBA(void)
{
    DWORD ulFileFwVersionlLBA = 0;

    ulFileFwVersionlLBA = ScalerUsbFileSysGetClusStartLBA(g_stUsbFileSysFileInfo.ulFileStartClusNum) + ((_CUSTOMER_FW_VERSION_LOCATE_BANK * 65536 + _CUSTOMER_FW_VERSION_LOCATE_ADDRESS) / g_stUsbFileSysDbrTable.usBytePerSec);

    return ulFileFwVersionlLBA;
}

//--------------------------------------------------
// Description  : Get File FW Version LBA.
// Input Value  : None
// Output Value : ulFileFwVersionlLBA
//--------------------------------------------------
WORD ScalerUsbFileSysGetFileFwVersionOffset(void)
{
    WORD usFileFwVersionlOffset = 0;

    usFileFwVersionlOffset = (WORD)((_CUSTOMER_FW_VERSION_LOCATE_BANK * 65536 + _CUSTOMER_FW_VERSION_LOCATE_ADDRESS) % g_stUsbFileSysDbrTable.usBytePerSec);

    return usFileFwVersionlOffset;
}

#endif // End of #if((_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON) && (_CUSTOMER_FW_VERSION_SUPPORT == _ON))
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
