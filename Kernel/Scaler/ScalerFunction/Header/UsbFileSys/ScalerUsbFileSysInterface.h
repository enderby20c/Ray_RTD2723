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
// ID Code      : ScalerUsbFileSysInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
#define _SUPPORT_PARTITION_NUM                                          4

#define _U2HOST_FILE_SYS_MBR_PTN_ENTRY_OFFSET_ADDR                      0x01BE      // 1st Partition Addr offset in MBR
#define _U2HOST_FILE_SYS_MBR_PTN_ENTRY_SIZE                             16          // MBR Partition Entry Size

#define _U2HOST_FILE_SYS_DBR_TABLE_OFFSET_ADDR                          0x00        // Addr offset in DBR Block
#define _U2HOST_FILE_SYS_DBR_TABLE_SIZE                                 110         // exFAT needs at least 110

#define _U2HOST_FILE_SYS_MBR_DBR_END_OFFSET_ADDR                        0x01FE      // End Signature Addr offset in MBR/DBR

#define _U2HOST_FILE_SYS_GPT_HEADER_OFFSET_ADDR                         0x00        // Signature field offset in GPT Header
#define _U2HOST_FILE_SYS_GPT_ENTRY_SIZE                                 128         // GPT Partition Entry Size

#define _U2HOST_FILE_SYS_FAT_ENTRY_SIZE                                 32          // FAT (exFAT / FAT32) Entry Size

#define GET_U2HOST_EHCI_CONNECT()                                       (g_bUsbFileSysEhciConnect)
#define SET_U2HOST_EHCI_CONNECT()                                       (g_bUsbFileSysEhciConnect = _TRUE)
#define CLR_U2HOST_EHCI_CONNECT()                                       (g_bUsbFileSysEhciConnect = _FALSE)

#define GET_U2HOST_CUR_PARTITION_NUM()                                  (g_ucUsbFileSysCurPartitionNum)
#define SET_U2HOST_CUR_PARTITION_NUM(x)                                 (g_ucUsbFileSysCurPartitionNum = (x))

#define GET_U2HOST_CUR_PARTITION_TYPE()                                 (g_ucUsbFileSysType)
#define SET_U2HOST_CUR_PARTITION_TYPE(x)                                (g_ucUsbFileSysType = (x))

#define GET_U2HOST_SEARCH_NAME_STATUS()                                 (g_ucUsbFileSysSrchFileNameState)
#define SET_U2HOST_SEARCH_NAME_STATUS(x)                                (g_ucUsbFileSysSrchFileNameState = (x))

// EHCI uses to get specified sector where contains bin file clus info
#define GET_U2HOST_CUR_LBA()                                            (g_ulUsbFileSysCurLBA)
#define SET_U2HOST_CUR_LBA(x)                                           (g_ulUsbFileSysCurLBA = (x))

#define GET_U2HOST_CUR_CLUS_START_LBA()                                 (g_ulUsbFileSysCurClusStartLBA)
#define SET_U2HOST_CUR_CLUS_START_LBA(x)                                (g_ulUsbFileSysCurClusStartLBA = (x))

#define GET_U2HOST_NTFS_FILE_NOT_FOUND()                                (g_bUsbFileSysNtfsFileNotFoundFlag)
#define SET_U2HOST_NTFS_FILE_NOT_FOUND()                                (g_bUsbFileSysNtfsFileNotFoundFlag = _TRUE)
#define CLR_U2HOST_NTFS_FILE_NOT_FOUND()                                (g_bUsbFileSysNtfsFileNotFoundFlag = _FALSE)

// EHCI uses this addr to Write DB File data
#define GET_U2HOST_FAT32_DB_FILE_DUMP_LBA()                             (g_ulUsbFileSysDBFileDumpLBA)
#define SET_U2HOST_FAT32_DB_FILE_DUMP_LBA(x)                            (g_ulUsbFileSysDBFileDumpLBA = (x))

// for FAT (exFAT / FAT32) application
#define _U2HOST_FAT_MAX_CLUS_NUM_OCCUPY_BY_DIR                          32

// for FAT32 & exFAT application
#define GET_U2HOST_SRCH_FROM_DIR_TYPE()                                 (g_enumUsbFileSysSrchFrom)
#define SET_U2HOST_SRCH_FROM_DIR_TYPE(x)                                (g_enumUsbFileSysSrchFrom = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _USB_FILE_SYS_NONE = 0x00,
    _USB_FILE_SYS_FAT32,
    _USB_FILE_SYS_NTFS,
    _USB_FILE_SYS_EXFAT,
    _USB_FILE_SYS_NOT_SUPPORTED,
}EnumUsbFileSysType;

typedef enum
{
    _USB_FILE_SYS_SRCH_NAME_NONE = 0x00,
    _USB_FILE_SYS_SRCH_FINISH,
}EnumUsbFileSysSrchNameStatus;

typedef enum
{
    _SRCH_FILE_FROM_ROOT = 0x00,
    _SRCH_FILE_FROM_1ST_SUB_DIR,
    _SRCH_1ST_SUB_DIR_FROM_ROOT,
}EnumUsbFileSysSrchType;

typedef struct
{
    BYTE ucBootflag;                // 1Byte                                                    offset0
    DWORD ulStartCHS;               // 3Byte                                                    offset1-3
    BYTE ucSystemID;                // 1Byte: 0x0C - FAT32 With LBA; 0x0B - FAT32 With CHS      offset4
    DWORD ulEndCHS;                 // 3Byte                                                    offset5-7
    DWORD ulDbrStartLBA;            // 4Byte: DBR Sector Start Num                              offset8-11
    DWORD ulTotalSecCnt;            // 4Byte: Total Sectors Count of this Partition             offset12-15
}StructUsbFileSysMbrPartitionTable;

typedef struct
{
    DWORD ulSignatureL;             // 8Byte, take Lower 4 byte                                 offset0
    DWORD ulSignatureH;             // 8Byte, take Higher 4 byte                                offset4
    DWORD ulMyLBA;                  // 8Byte, take 4 byte LSB since FAT32 is 32-bit system      offset24
    DWORD ulGptEntryStartLBA;       // 8Byte, take 4 byte LSB since FAT32 is 32-bit system      offset80
}StructUsbFileSysGptHeader;

typedef struct
{
    DWORD ulPartitionTypeLL;        // 16Byte GUID, take LL 4 byte                              offset0
    // DWORD ulPartitionTypeLH;     // 16Byte GUID, take LH 4 byte                              offset4
    // DWORD ulPartitionTypeHL;     // 16Byte GUID, take HL 4 byte                              offset8
    // DWORD ulPartitionTypeHH;     // 16Byte GUID, take HH 4 byte                              offset12
    DWORD ulDbrStartLBA;            // 8Byte, take 4 byte LSB since FAT32 is 32-bit system      offset32
}StructUsbFileSysGptEntry;

typedef struct
{
    // General
    QWORD uqOEMName;                // name & version of op system                             offset: 3
    WORD usBytePerSec;              // byte cnts of each sector
    DWORD ulSecPerClus;             // sectors of each clus
    BYTE ucNumFATs;                 // FAT Table cnts

    // FAT32 only
    WORD usRsvdSecCnt;              // reserved sectors cnts                                   offset:14
    DWORD ulFATSz32;                // sectors per FAT table                                   offset:36
    DWORD ulRootClus;               // RootClus NO.                                            offset:44

    // exFAT only
    DWORD ulFATOffset;              // FAT Table Offset                                        offset:80
    DWORD ulFATLength;              // FAT Table Size                                          offset:84
    DWORD ulClusHeapOffset;         // First Clus Offset                                       offset:88
    DWORD ulFirstClusOfRootDir;     // First Clus of RootDir                                   offset:96

    // NTFS only
    DWORD ulSecInVolumeH;           // High DW of sectors in the Volume                        offset: 0x2C
    DWORD ulMftClus;                // VCN of $MFT file                                        offset: 0x30
    BYTE ucClusPerMftRecord;        // Cluster per MFT Record                                  offset: 0x40
    BYTE ucClusPerIdxRecord;        // Cluster per Index Record                                offset: 0x44
}StructUsbFileSysDbrTable;

typedef struct
{
    BYTE ucIndex;
    BYTE ucIndexShadow;
    BYTE ucIndexTarget;             // Record the Target File ClusterNum Idx (Target)
    BYTE ucIndexStrmExt;            // Record the StrmExt ClusterNum Idx (exFAT)

    // Record all cluster numbers occupied by directory
    DWORD pulClusNum[_U2HOST_FAT_MAX_CLUS_NUM_OCCUPY_BY_DIR];
}StructUsbFileSysFatDirInfo;

typedef struct
{                                   // correspond Field Name under exFAT
    DWORD ulFAT1StartLBA;           // ulFATOffset
    DWORD ulClusFieldStartLBA;      // ulClusHeapOffset
    DWORD ulRootDirStartClusNum;    // ulFirstClusOfRootDir
    bit b1stSubDirNoFatChain;
    bit bFileNoFatChain;
    BYTE ucCurMatchEntryCnt;        // Record the matched Enties
    BYTE ucCurEntryOffset;          // Record the next Entry to process
    BYTE ucNxtEntrySetOffset;       // Record the start of next Entry Set (exFAT)
    WORD usSecInClusStrmExt;        // Record the StrmExt SecInClus (exFAT)
    BYTE ucEntryInSecStrmExt;       // Record the StrmExt EntryInSec (exFAT)
    WORD usSecInClusTarget;         // Record the Target File SecInClus (Cluster Size up to 32MB) (Target)
    BYTE ucEntryInSecTarget;        // Record the Target File EntryInSec (Target)

    StructUsbFileSysFatDirInfo stFatDirInfo;
}StructUsbFileSysFatInfo;

typedef struct
{
    WORD  usFileSizeInClus;
    DWORD ulFileStartClusNum;
    DWORD ulFileLastClusNum;
    QWORD uqFileSizeInByte;
    WORD usFileRecLoopCnt;
    DWORD ulFileNameVer;            // _USB2_HOST_FILE_NAME_JUDGE_VERSION
    bit bNot1stFile;                // _USB2_HOST_FILE_NAME_JUDGE_VERSION

    BYTE pucFileNameVerTmp[_USB2_HOST_FILE_NAME_VERSION_CHAR_LEN];      // _USB2_HOST_FILE_NAME_JUDGE_VERSION
    BYTE pucFileNameVer[_USB2_HOST_FILE_NAME_VERSION_CHAR_LEN];         // _USB2_HOST_FILE_NAME_JUDGE_VERSION
}StructUsbFileSysFileInfo;

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
typedef struct
{
    DWORD ulSecPerMftRecord;
    DWORD ulSecPerIdxRecord;
    DWORD ulNtfsRootEntryLBA;
    DWORD ulCurClusNum;
    WORD usCurRootAllocClusIdx;
    BYTE ucCurSecInClus;            // Cluster Size up to 2MB
    BYTE ucCurSecInIdxRecord;
    WORD usByteOffsetInIdxRecord;
    WORD usCurIdxRecordLen;
    DWORD ulFileMftNum;

    // Record current DataRun stream (support DataRun up to 32 Bytes)
    BYTE pucCurDataRun[32];
    // Record current FixUp Num & Array (up to 16 Bytes to support a 4k IdxRecord)
    BYTE pucCurFixUpNum[2];
    BYTE pucCurFixUpArray[16];
}StructUsbFileSysNtfsInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucUsbFileSysSrchFileNameState;
extern WORD g_usUsbFileSysU2HostEHCIMaxDataLen;
extern DWORD g_ulUsbFileSysCurLBA;
extern DWORD g_ulUsbFileSysDBFileDumpLBA;
extern DWORD g_ulUsbFileSysCurClusStartLBA;
extern bit g_bUsbFileSysNtfsFileNotFoundFlag;
extern bit g_bUsbFileSysEhciConnect;

extern BYTE g_ucUsbFileSysType;
extern BYTE g_ucUsbFileSysCurPartitionNum;
extern StructUsbFileSysMbrPartitionTable g_pstUsbFileSysMbrPartitionEntry[_SUPPORT_PARTITION_NUM];
extern StructUsbFileSysGptHeader g_stUsbFileSysGptHeader;
extern StructUsbFileSysGptEntry g_pstUsbFileSysGptEntry[_SUPPORT_PARTITION_NUM];
extern StructUsbFileSysDbrTable g_stUsbFileSysDbrTable;
extern StructUsbFileSysFatInfo g_stUsbFileSysFatInfo;
extern StructUsbFileSysFileInfo g_stUsbFileSysFileInfo;
extern EnumUsbFileSysSrchType g_enumUsbFileSysSrchFrom;

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
extern StructUsbFileSysNtfsInfo g_stUsbFileSysNtfsInfo;
#endif

extern BYTE g_pucUsbFileSysGoldenFileName[64];

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
extern BYTE code tUsbFat32GoldenLongFileNameReplace[16];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsbFileSysInitial(void);
extern void ScalerUsbFileSysGetMbrEntry(BYTE *pucData);
extern void ScalerUsbFileSysGetGptHeader(BYTE *pucData);
extern void ScalerUsbFileSysGetGptEntry(BYTE *pucData);
extern void ScalerUsbFileSysGetDbrTable(BYTE *pucData, EnumUsbFileSysType enumFileSysType);
extern DWORD ScalerUsbFileSysGetClusStartLBA(DWORD ulClusNum);

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern BYTE ScalerUsbFileSysGetFileName(BYTE ucUsbUserFileNameOffset);
extern bit ScalerUsbFileSysGetConnectStatus(void);
extern StructUsbFileSysUserFileInfo ScalerUsbFileSysGetFileInfo(void);
#endif

extern bit ScalerUsbFileSysFatCalInfo(BYTE ucCurPtnNum);
extern bit ScalerUsbFileSysFatChkEOC(EnumUsbFileSysType enumFileSysType, DWORD ulFatContent);
extern DWORD ScalerUsbFileSysFatGetFAT1ClusNumLBA(DWORD ulClusNum);
extern bit ScalerUsbFileSysFat32ParseFileEntry(EnumUsbFileSysSrchType enumSrchType, BYTE *pucData, BYTE *pucCurEntryOffset, BYTE *pucCurMatchCnt, bit b2ndLoop);
extern bit ScalerUsbFileSysFat32SrchSfn(bit bIsFile, BYTE ucFileNameLen_SFN, BYTE *pucData, BYTE ucCurEntryOffset, code BYTE *pucGoldenName);
extern bit ScalerUsbFileSysFat32SrchLfn(BYTE *pucData, bit bChkEnd, BYTE ucCurEntryOffset, BYTE ucCurMatchCnt, code BYTE *pucGoldenName);
extern void ScalerUsbFileSysFat32GetSfnInfo(BYTE *pucData, BYTE ucCurEntryOffset);
extern void ScalerUsbFileSysFat32ChkGoldenFileName(EnumUsbFileSysSrchType enumSrchType);

#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
extern bit ScalerUsbFileSysExfatParseFileEntry(EnumUsbFileSysSrchType enumSrchType, BYTE *pucData, BYTE *pucCurEntryOffset, BYTE *pucNxtEntrySetOffset, BYTE *pucCurMatchCnt, bit b2ndLoop);
extern bit ScalerUsbFileSysExfatSrchFileName(BYTE *pucData, BYTE *pucCurEntryOffset, BYTE *pucCurMatchCnt, code BYTE *pucGoldenName);
extern void ScalerUsbFileSysExfatGetStrmExtInfo(BYTE *pucData, BYTE ucCurEntryOffset, EnumUsbFileSysSrchType enumSrchType);
#endif

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
extern bit ScalerUsbFileSysNtfsCalInfo(BYTE ucCurPtnNum);
extern void ScalerUsbFileSysNtfsParseMftHdr(BYTE *pucData);
extern WORD ScalerUsbFileSysNtfsSrchMftAttr(BYTE *pucData, BYTE ucTargetId);
extern void ScalerUsbFileSysNtfsFixUpArray(BYTE *pucData, BYTE ucSecNum, WORD usOffset);
extern bit ScalerUsbFileSysNtfsParseIdxRootAttr(BYTE *pucData);
extern void ScalerUsbFileSysNtfsParseIdxAllocAttr(BYTE *pucData);
extern void ScalerUsbFileSysNtfsParseDataAttr(BYTE *pucData);
extern DWORD ScalerUsbFileSysNtfsParseDataRun(BYTE *pucDataRun, WORD usClusIdx);
extern void ScalerUsbFileSysNtfsParseIdxRecordHdr(BYTE *pucData);
extern WORD ScalerUsbFileSysNtfsSrchFileName(BYTE *pucData, WORD usOffset, WORD usRecordLen);
#endif

#if((_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON) && (_CUSTOMER_FW_VERSION_SUPPORT == _ON))
extern DWORD ScalerUsbFileSysGetFileFwVersionLBA(void);
extern WORD ScalerUsbFileSysGetFileFwVersionOffset(void);
#endif // End of #if(_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON)
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

