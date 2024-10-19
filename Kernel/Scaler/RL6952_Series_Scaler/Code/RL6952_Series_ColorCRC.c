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
// ID Code      : RL6952_Series_ColorCRC.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Compare D-CRC with IC Read out
// Input Value  : enumICRCPosition: CRC Position, e.g._D_CRC_AFTER_DDITHER
//                ucPathSel: Union of EnumDCRCPath
//                pucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerColorCRCCompareDDomain(EnumDCRCPosition enumDCRCPosition, BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum)
{
    BYTE ucFrameIndex = 0;
    StructCRCInfo stReadCRC = {{0}};
    bit bFlag = _SUCCESS;
    EnumDCRCPath code tenumOrder[3] =
    {
        _D_CRC_M1,
        _D_CRC_M2,
        _D_CRC_S1,
    };

    // Enable CRC function
    ScalerSetByte(P36_C0_D_CRC_CTRL_M1, (((ucPathSelect & _D_CRC_M1) == _D_CRC_M1) ? (_BIT7 | (enumDCRCPosition & 0x03)) : 0x00));
    ScalerSetByte(P36_C8_D_CRC_CTRL_M2, (((ucPathSelect & _D_CRC_M2) == _D_CRC_M2) ? (_BIT7 | (enumDCRCPosition & 0x03)) : 0x00));
    ScalerSetByte(P36_E0_D_CRC_CTRL_S1, (((ucPathSelect & _D_CRC_S1) == _D_CRC_S1) ? _BIT7 : 0x00));

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    for(ucFrameIndex = 0; ucFrameIndex < ucFrameNum; ++ucFrameIndex)
    {
        BYTE ucPathIndex = 0;

        // Wait for CRC update
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerDelayXms(2);

        for(ucPathIndex = 0; ucPathIndex < (sizeof(tenumOrder) / sizeof(tenumOrder[0])); ++ucPathIndex)
        {
            if((ucPathSelect & tenumOrder[ucPathIndex]) != 0)
            {
                WORD usTargetIndex = ucPathIndex + (ucFrameIndex * (sizeof(tenumOrder) / sizeof(tenumOrder[0])));
                WORD usAddress = P36_C1_D_MAIN1_CRC_1;

                // Update target register
                switch(tenumOrder[ucPathIndex])
                {
                    case _D_CRC_M1:
                    default:
                        usAddress = P36_C1_D_MAIN1_CRC_1;
                        break;

                    case _D_CRC_M2:
                        usAddress = P36_C9_D_MAIN2_CRC_1;
                        break;

                    case _D_CRC_S1:
                        usAddress = P36_E1_D_SUB1_CRC_1;
                        break;
                }

                // Read currernt CRC from target register
                ScalerRead(usAddress, 6, stReadCRC.pucValue, _AUTOINC);

                // Compare CRC and return on fail
                if(memcmp(stReadCRC.pucValue, pstTargetCRC[usTargetIndex].pucValue, 6) != 0)
                {
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    ScalerColorCRCPrint(ucFrameIndex, ucPathIndex, &stReadCRC, _CRC_DDOMAIN);
#endif
                    bFlag = _FAIL;
                }
            }
        }

        if(bFlag == _FAIL)
        {
            return _FAIL;
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Compare I-CRC with IC Read out
// Input Value  : enumICRCPosition: CRC Position, e.g._I_CRC_AFTER_VGIP
//                ucPathSel: Union of EnumICRCPath
//                pucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerColorCRCCompareIDomain(EnumICRCPosition enumICRCPosition, BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum)
{
    EnumInputDataPath enumInputDataPath = _INPUT_PATH_M1_M2;
    BYTE ucFrameIndex = 0;
    StructCRCInfo stReadCRC = {{0}};
    bit bFlag = _SUCCESS;
    EnumICRCPath code tenumOrder[3] =
    {
        _I_CRC_M1,
        _I_CRC_M2,
        _I_CRC_S1,
    };

    switch(ucPathSelect)
    {
        case _I_CRC_M1:
            enumInputDataPath = _INPUT_PATH_M1;
            break;

        case _I_CRC_M2:
            enumInputDataPath = _INPUT_PATH_M2;
            break;

        case _I_CRC_M1 | _I_CRC_M2: // (EO)
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _I_CRC_S1:
            enumInputDataPath = _INPUT_PATH_S1;
            break;

        default:
            DebugMessageScaler("Main and Sub should compare seperately!", 0);
            return _FAIL;
    }

    // Enable CRC function
    ScalerSetByte(P36_00_I_CRC_CTRL_M1, (((ucPathSelect & _I_CRC_M1) == _I_CRC_M1) ? (_BIT7 | (enumICRCPosition & 0x03)) : 0x00));
    ScalerSetByte(P36_08_I_CRC_CTRL_M2, (((ucPathSelect & _I_CRC_M2) == _I_CRC_M2) ? (_BIT7 | (enumICRCPosition & 0x03)) : 0x00));
    ScalerSetByte(P36_10_I_CRC_CTRL_S1, (((ucPathSelect & _I_CRC_S1) == _I_CRC_S1) ? (_BIT7 | (enumICRCPosition & 0x03)) : 0x00));

    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);

    for(ucFrameIndex = 0; ucFrameIndex < ucFrameNum; ++ucFrameIndex)
    {
        BYTE ucPathIndex = 0;

        // Wait for CRC update
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerTimerDelayXms(2);

        for(ucPathIndex = 0; ucPathIndex < (sizeof(tenumOrder) / sizeof(tenumOrder[0])); ++ucPathIndex)
        {
            if((ucPathSelect & tenumOrder[ucPathIndex]) != 0)
            {
                WORD usTargetIndex = ucPathIndex + (ucFrameIndex * (sizeof(tenumOrder) / sizeof(tenumOrder[0])));
                WORD usAddress = P36_01_I_MAIN1_CRC_1;

                // Update target register
                switch(tenumOrder[ucPathIndex])
                {
                    case _I_CRC_M1:
                    default:
                        usAddress = P36_01_I_MAIN1_CRC_1;
                        break;

                    case _I_CRC_M2:
                        usAddress = P36_09_I_MAIN2_CRC_1;
                        break;

                    case _I_CRC_S1:
                        usAddress = P36_11_I_SUB1_CRC_1;
                        break;
                }

                // Read currernt CRC from target register
                ScalerRead(usAddress, 6, stReadCRC.pucValue, _AUTOINC);

                // Compare CRC and return on fail
                if(memcmp(stReadCRC.pucValue, pstTargetCRC[usTargetIndex].pucValue, 6) != 0)
                {
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    ScalerColorCRCPrint(ucFrameIndex, ucPathIndex, &stReadCRC, _CRC_IDOMAIN);
#endif
                    bFlag = _FAIL;
                }
            }
        }

        if(bFlag == _FAIL)
        {
            return _FAIL;
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Compare M-CRC-Cap with IC Read out
// Input Value  : ucPathSel: Union of EnumMCRCPath
//                pucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerColorCRCCompareMDomainCap(BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum)
{
    EnumInputDataPath enumInputDataPath = _INPUT_PATH_M1_M2;
    BYTE ucFrameIndex = 0;
    StructCRCInfo stReadCRC = {{0}};
    bit bFlag = _SUCCESS;
    EnumMCRCPath code tenumOrder[3] =
    {
        _M_CRC_M1,
        _M_CRC_M2,
        _M_CRC_S1,
    };

    switch(ucPathSelect)
    {
        case _M_CRC_M1:
            enumInputDataPath = _INPUT_PATH_M1;
            break;

        case _M_CRC_M2:
            enumInputDataPath = _INPUT_PATH_M2;
            break;

        case _M_CRC_M1 | _M_CRC_M2: // (EO)
            enumInputDataPath = _INPUT_PATH_M1_M2;
            break;

        case _M_CRC_S1:
            enumInputDataPath = _INPUT_PATH_S1;
            break;

        default:
            DebugMessageScaler("Main and Sub should compare seperately!", 0);
            return _FAIL;
    }

    // Enable CRC function
    ScalerSetByte(P36_80_M_CAP_CRC_CTRL_M1, (((ucPathSelect & _M_CRC_M1) == _M_CRC_M1) ? _BIT7 : 0x00));
    ScalerSetByte(P36_88_M_CAP_CRC_CTRL_M2, (((ucPathSelect & _M_CRC_M2) == _M_CRC_M2) ? _BIT7 : 0x00));
    ScalerSetByte(P36_A0_M_CAP_CRC_CTRL_S1, (((ucPathSelect & _M_CRC_S1) == _M_CRC_S1) ? _BIT7 : 0x00));

    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);

    for(ucFrameIndex = 0; ucFrameIndex < ucFrameNum; ++ucFrameIndex)
    {
        BYTE ucPathIndex = 0;

        // Wait for CRC update
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerTimerDelayXms(2);

        for(ucPathIndex = 0; ucPathIndex < (sizeof(tenumOrder) / sizeof(tenumOrder[0])); ++ucPathIndex)
        {
            if((ucPathSelect & tenumOrder[ucPathIndex]) != 0)
            {
                WORD usTargetIndex = ucPathIndex + (ucFrameIndex * (sizeof(tenumOrder) / sizeof(tenumOrder[0])));
                WORD usAddress = P36_81_M_MAIN1_CAP_CRC_1;

                // Update target register
                switch(tenumOrder[ucPathIndex])
                {
                    case _I_CRC_M1:
                    default:
                        usAddress = P36_81_M_MAIN1_CAP_CRC_1;
                        break;

                    case _I_CRC_M2:
                        usAddress = P36_89_M_MAIN2_CAP_CRC_1;
                        break;

                    case _I_CRC_S1:
                        usAddress = P36_A1_M_SUB1_CAP_CRC_1;
                        break;
                }

                // Read currernt CRC from target register
                ScalerRead(usAddress, 6, stReadCRC.pucValue, _AUTOINC);

                // Compare CRC and return on fail
                if(memcmp(stReadCRC.pucValue, pstTargetCRC[usTargetIndex].pucValue, 6) != 0)
                {
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    ScalerColorCRCPrint(ucFrameIndex, ucPathIndex, &stReadCRC, _CRC_MDOMAIN_CAP);
#endif
                    bFlag = _FAIL;
                }
            }
        }

        if(bFlag == _FAIL)
        {
            return _FAIL;
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Compare M-CRC-Disp with IC Read out
// Input Value  : ucPathSel: Union of EnumMCRCPath
//                pucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerColorCRCCompareMDomainDisp(EnumMCRCDispPosition enumMCRCDispPosition, BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum)
{
    BYTE ucFrameIndex = 0;
    StructCRCInfo stReadCRC = {{0}};
    bit bFlag = _SUCCESS;
    EnumMCRCPath code tenumOrder[3] =
    {
        _M_CRC_M1,
        _M_CRC_M2,
        _M_CRC_S1,
    };

    // Enable CRC function
    ScalerSetByte(P36_40_M_DISP_CRC_CTRL_M1, (((ucPathSelect & _M_CRC_M1) == _M_CRC_M1) ? (_BIT7 | (enumMCRCDispPosition & 0x01)) : 0x00));
    ScalerSetByte(P36_48_M_DISP_CRC_CTRL_M2, (((ucPathSelect & _M_CRC_M2) == _M_CRC_M2) ? (_BIT7 | (enumMCRCDispPosition & 0x01)) : 0x00));
    ScalerSetByte(P36_50_M_DISP_CRC_CTRL_S1, (((ucPathSelect & _M_CRC_S1) == _M_CRC_S1) ? _BIT7 : 0x00));

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    for(ucFrameIndex = 0; ucFrameIndex < ucFrameNum; ++ucFrameIndex)
    {
        BYTE ucPathIndex = 0;

        // Wait for CRC update
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerDelayXms(2);

        for(ucPathIndex = 0; ucPathIndex < (sizeof(tenumOrder) / sizeof(tenumOrder[0])); ++ucPathIndex)
        {
            if((ucPathSelect & tenumOrder[ucPathIndex]) != 0)
            {
                WORD usTargetIndex = ucPathIndex + (ucFrameIndex * (sizeof(tenumOrder) / sizeof(tenumOrder[0])));
                WORD usAddress = P36_41_M_MAIN1_DISP_CRC_1;

                // Update target register
                switch(tenumOrder[ucPathIndex])
                {
                    case _M_CRC_M1:
                    default:
                        usAddress = P36_41_M_MAIN1_DISP_CRC_1;
                        break;

                    case _M_CRC_M2:
                        usAddress = P36_49_M_MAIN2_DISP_CRC_1;
                        break;

                    case _M_CRC_S1:
                        usAddress = P36_51_M_SUB1_DISP_CRC_1;
                        break;
                }

                // Read currernt CRC from target register
                ScalerRead(usAddress, 6, stReadCRC.pucValue, _AUTOINC);

                // Compare CRC and return on fail
                if(memcmp(stReadCRC.pucValue, pstTargetCRC[usTargetIndex].pucValue, 6) != 0)
                {
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    ScalerColorCRCPrint(ucFrameIndex, ucPathIndex, &stReadCRC, _CRC_MDOMAIN_DISP);
#endif
                    bFlag = _FAIL;
                }
            }
        }

        if(bFlag == _FAIL)
        {
            return _FAIL;
        }
    }

    return _SUCCESS;
}


#if(_DEBUG_MESSAGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Print CRC when not match
// Input Value  : ucCRC: IC CRC, ucNum: CRC Number
// Output Value : None
//--------------------------------------------------
void ScalerColorCRCPrint(BYTE ucFrame, BYTE ucPath, StructCRCInfo *pstCRC, EnumCRCDomain enumCRCDomain)
{
#if(_DEBUG_MESSAGE_QC == _ON)
    DWORD ulCRC = 0;
    SBYTE pchMessage[21] = "5. I-Domain M1_CRC_H";

    switch(enumCRCDomain)
    {
        case _CRC_IDOMAIN:
        default:
            pchMessage[3] = 'I';
            break;

        case _CRC_MDOMAIN_CAP:
            pchMessage[3] = 'M';
            pchMessage[5] = 'C';
            pchMessage[6] = 'a';
            pchMessage[7] = 'p';
            pchMessage[8] = 't';
            pchMessage[9] = '.';
            pchMessage[10] = '.';
            break;

        case _CRC_MDOMAIN_DISP:
            pchMessage[3] = 'M';
            pchMessage[5] = 'D';
            pchMessage[6] = 'i';
            pchMessage[7] = 's';
            pchMessage[8] = 'p';
            pchMessage[9] = '.';
            pchMessage[10] = '.';
            break;

        case _CRC_DDOMAIN:
            pchMessage[3] = 'D';
            break;
    }

    if(enumCRCDomain == _CRC_DDOMAIN)
    {
        switch(ucPath)
        {
            case 0:
            default:
                pchMessage[12] = 'M';
                pchMessage[13] = '1';
                break;

            case 1:
                pchMessage[12] = 'M';
                pchMessage[13] = '2';
                break;

            case 2:
                pchMessage[12] = 'S';
                pchMessage[13] = '1';
                break;
        }
    }
    else
    {
        switch(ucPath)
        {
            case 0:
            default:
                pchMessage[12] = 'M';
                pchMessage[13] = '1';
                break;

            case 1:
                pchMessage[12] = 'M';
                pchMessage[13] = '2';
                break;

            case 2:
                pchMessage[12] = 'S';
                pchMessage[13] = '1';
                break;
        }
    }

    if(ucFrame != 0)
    {
        DebugMessageQC("5.======Frame======", ucFrame);
    }

    ulCRC = ((DWORD)pstCRC->pucValue[0] << 16) | ((DWORD)pstCRC->pucValue[1] << 8) | ((DWORD)pstCRC->pucValue[2]);
    DebugMessageQC(pchMessage, ulCRC);

    pchMessage[19] = 'L';
    ulCRC = ((DWORD)pstCRC->pucValue[3] << 16) | ((DWORD)pstCRC->pucValue[4] << 8) | ((DWORD)pstCRC->pucValue[5]);
    DebugMessageQC(pchMessage, ulCRC);
#endif

    ucFrame = ucFrame;
    ucPath = ucPath;
    pstCRC = pstCRC;
    enumCRCDomain = enumCRCDomain;
}
#endif

