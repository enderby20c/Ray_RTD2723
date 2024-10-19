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
// ID Code      : ScalerColorDCC.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
bit g_bColorDCCReadyStatus = _FALSE;
#endif

QWORD g_uqColorNF = (QWORD)255 << (_DCC_HISTO_NF);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : Clear DCC Data Ready Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCClrDataReadyStatus(void)
{
    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_1E_PORT_PAGE0_READY_TO_READ);
    ScalerSetBit(P7_CA_DCC_DATA_PORT, ~(_BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Get DCC Data Ready Status
// Input Value  : None
// Output Value : _TRUE/_FLASE
//--------------------------------------------------
bit ScalerColorDCCGetDataReadyStatus(void)
{
    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_1E_PORT_PAGE0_READY_TO_READ);

    return ((bit)(ScalerGetByte(P7_CA_DCC_DATA_PORT) & _BIT0));
}

//--------------------------------------------------
// Description  : Get DCC Histogram Information
// Input Value  : pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCGetHistoInfo(BYTE *pucReadArray)
{
    BYTE ucI = 0;

    if(GET_DCC_READY_STATUS() == _FALSE)
    {
        memset(pucReadArray, 0, 11);
        return;
    }

    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);

    // Pop out result
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_0C_PORT_PAGE0_POPUP_CTRL);
    // Read 0x07C9_0C to freeze DCC infomation
    ScalerGetByte(P7_CA_DCC_DATA_PORT);

    // Get Histogram Info
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_0E_PORT_PAGE0_Y_MAX_VAL_H);

    for(ucI = 0; ucI < 9; ucI++)
    {
        pucReadArray[ucI] = ScalerGetByte(P7_CA_DCC_DATA_PORT);
    }

    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_1C_PORT_PAGE0_Y_MAX_VAL_L);
    pucReadArray[9] = ScalerGetByte(P7_CA_DCC_DATA_PORT);
    pucReadArray[10] = ScalerGetByte(P7_CA_DCC_DATA_PORT);
}

//--------------------------------------------------
// Description  : Set Y_MAX_LB, Y_MIN_HB
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCHistoSetting(void)
{
    // Set Y max lower bound and Y min higher bound
    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_07_PORT_PAGE0_Y_MAX_LB_H);
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(_DCC_HISTO_YMAX_LB >> 2));
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(_DCC_HISTO_YMIN_HB >> 2));
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_1A_PORT_PAGE0_Y_MAX_LB_L);
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(_DCC_HISTO_YMAX_LB & (_BIT1 | _BIT0)));
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(_DCC_HISTO_YMIN_HB & (_BIT1 | _BIT0)));

    // Enable DCC
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
// Notice : Under _DCC_GEN_0, all result are one byte. Under _DCC_GEN_0, S0~S6 are one byte, but Y_MAX and Y_MIN are one word.
//--------------------------------------------------
BYTE ScalerColorDCCReadS0toS6(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    BYTE ucResult = 0;

    if(pucReadArray == _NULL_POINTER)
    {
        return 0;
    }

    switch(enumDCCReadOption)
    {
        case _DCC_S0:
            ucResult = pucReadArray[2];
            break;

        case _DCC_S1:
            ucResult = pucReadArray[3];
            break;

        case _DCC_S2:
            ucResult = pucReadArray[4];
            break;

        case _DCC_S3:
            ucResult = pucReadArray[5];
            break;

        case _DCC_S4:
            ucResult = pucReadArray[6];
            break;

        case _DCC_S5:
            ucResult = pucReadArray[7];
            break;

        case _DCC_S6:
            ucResult = pucReadArray[8];
            break;

        default:
            break;
    }

    return ucResult;
}

#if(_HW_DCC_Y_BIT_MODE == _DCC_Y_8BIT)
//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
//--------------------------------------------------
BYTE ScalerColorDCCReadY_8BIT(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    BYTE ucResult = 0;

    if(pucReadArray == _NULL_POINTER)
    {
        return 0;
    }

    switch(enumDCCReadOption)
    {
        case _DCC_Y_MAX:
            ucResult = pucReadArray[0];
            break;

        case _DCC_Y_MIN:
            ucResult = pucReadArray[1];
            break;

        default:
            break;
    }

    return ucResult;
}
#elif(_HW_DCC_Y_BIT_MODE == _DCC_Y_10BIT)
//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
//--------------------------------------------------
WORD ScalerColorDCCReadY_10BIT(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    WORD usResult = 0;

    if(pucReadArray == _NULL_POINTER)
    {
        return 0;
    }

    switch(enumDCCReadOption)
    {
        case _DCC_Y_MAX:
            usResult = (((WORD)pucReadArray[0]) << 2) + (pucReadArray[9] >> 6);
            break;

        case _DCC_Y_MIN:
            usResult = (((WORD)pucReadArray[1]) << 2) + (pucReadArray[10] >> 6);
            break;

        default:
            break;
    }

    return usResult;
}
#endif
#endif

#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
//--------------------------------------------------
// Description  : GET Setting Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDccSettingType ScalerColorDCCGetSettingType(EnumSelRegion enumDCCMeasureRegion)
{
    switch(enumDCCMeasureRegion)
    {
        // Full region
        case _1P_NORMAL_REGION:
        case _FULL_REGION:
            return _DCC_SETTING_FULL;

// Inside window
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_SUB:
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_SUB:
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_R:
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_B:
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
        case _3P_FLAG_L:
        case _3P_FLAG_R:
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_L_T:
        case _3P_SKEW_L_B:
        case _3P_SKEW_R_M:
        case _3P_SKEW_R_T:
        case _3P_SKEW_R_B:
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
        case _3P_SKEW_T_L:
        case _3P_SKEW_T_R:
        case _3P_SKEW_B_M:
        case _3P_SKEW_B_L:
        case _3P_SKEW_B_R:
#endif
        case _DEMO_INSIDE:

            return _DCC_SETTING_INSIDE;

// Outside window
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_R_LARGE_L:
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
#endif
        case _DEMO_OUTSIDE:

            return _DCC_SETTING_OUTSIDE;

        default:
            return _DCC_SETTING_OTHER;
    }
}

//--------------------------------------------------
// Description  : Adjust Normalize Factor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCNormalizeFactorAdjust(EnumSelRegion enumDCCMeasureRegion)
{
    WORD usHWidth = 0;
    WORD usVHeight = 0;
    WORD usHStart = 0;
    WORD usHEnd = 0;
    WORD usVStart = 0;
    WORD usVEnd = 0;
    BYTE ucBorder = 0;
    DWORD ulNormalizedFactor = 0;

    // Panel size
    usHStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START);
    usHEnd = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END);
    usHWidth = usHEnd - usHStart;

    usVStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);
    usVEnd = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END);
    usVHeight = usVEnd - usVStart;

    if((usHWidth == 0) || (usVHeight == 0))
    {
        return;
    }

    // Check if highlight window on
    if(ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, _BIT0) != 0x00)
    {
        // Get highlight window type
        switch(ScalerColorDCCGetSettingType(enumDCCMeasureRegion))
        {
            // Full region
            case _DCC_SETTING_FULL:
                ulNormalizedFactor = (DWORD)((g_uqColorNF / usHWidth / usVHeight) & 0x3ffffff);
                break;

            case _DCC_SETTING_INSIDE:
                ScalerSetByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_00_HLW_HOR_START_H);
                usHStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                usHEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                usVStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                usVEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                ucBorder = ScalerGetByte(P0_61_HLW_DATA_PORT);
                usHWidth = usHEnd + ucBorder - usHStart;
                usVHeight = usVEnd + ucBorder - usVStart;
                if((usHWidth == 0) || (usVHeight == 0))
                {
                    return;
                }
                ulNormalizedFactor = (DWORD)((g_uqColorNF / usHWidth / usVHeight) & 0x3ffffff);
                break;

            case _DCC_SETTING_OUTSIDE:
                ScalerSetByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_00_HLW_HOR_START_H);
                usHStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                usHEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                usVStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                usVEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | ScalerGetByte(P0_61_HLW_DATA_PORT);
                ucBorder = ScalerGetByte(P0_61_HLW_DATA_PORT);

                // Calculate Outside Count
                PDATA_DWORD(1) = ((DWORD)(usHWidth)*(DWORD)(usVHeight)) - (DWORD)(usHEnd + ucBorder - usHStart)*(DWORD)(usVEnd + ucBorder - usVStart);

                if(PDATA_DWORD(1) == 0)
                {
                    return;
                }
                ulNormalizedFactor = (DWORD)((g_uqColorNF / PDATA_DWORD(1)) & 0x3ffffff);
                break;

            case _DCC_SETTING_OTHER:
            default:
                ulNormalizedFactor = (DWORD)((g_uqColorNF / usHWidth / usVHeight) & 0x3ffffff);
                break;
        }
    }
    else
    {
        ulNormalizedFactor = (DWORD)((g_uqColorNF / usHWidth / usVHeight) & 0x3ffffff);
    }

    if(ScalerDDomainBackgroundCheck(enumDCCMeasureRegion) == _FALSE)
    {
        ScalerTimerPollingFlagProc(20, P7_C8_DCC_CTRL_1, _BIT6, 1);
    }

    switch(ScalerColorDCCGetSettingType(enumDCCMeasureRegion))
    {
        case _DCC_SETTING_FULL:
            ScalerColorDCCSetMeasureRegion(_HLW_FULL_WINDOW);
            break;

        case _DCC_SETTING_INSIDE:
            ScalerColorDCCSetMeasureRegion(_HLW_INSIDE_WINDOW);
            break;

        case _DCC_SETTING_OUTSIDE:
            ScalerColorDCCSetMeasureRegion(_HLW_OUTSIDE_WINDOW);
            break;

        case _DCC_SETTING_OTHER:
        default:
            ScalerColorDCCSetMeasureRegion(_HLW_FULL_WINDOW);
            break;
    }

    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);

    // Set normalized factor
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE0_NOR_FACTOR_H);
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(ulNormalizedFactor >> 16));
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(ulNormalizedFactor >> 8));
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(ulNormalizedFactor >> 0));
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_26_PORT_PAGE0_NOR_FACTOR_H1);
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)(ulNormalizedFactor >> 24));
}

//--------------------------------------------------
// Description  : Set DCC DCC Histogram Measure Region
// Input Value  : enumDCCHistoMeasureRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCSetHistoMeasureRegion(EnumSelRegion enumDCCHistoMeasureRegion)
{
    ScalerColorDCCNormalizeFactorAdjust(enumDCCHistoMeasureRegion);
}

//--------------------------------------------------
// Description  : Adjust DCC Measure region
// Input Value  : Highlight Window Actvie Region Option
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCSetMeasureRegion(EnumHLWType enumHLWType)
{
    ScalerSetBit(P7_C8_DCC_CTRL_1, ~(_BIT3 | _BIT2), enumHLWType << 2);
}
#endif

#if(_COLOR_IP_DCC == _ON)
//--------------------------------------------------
// Description  : Adjust DCC Parameter
// Input Value  : pDccTable -> DCC control&user_curve register table
//                ucBankAddress -> Bank address
//                ucAdjustOption ->
//                        _BIT7: _BURSTWRITE_FROM_FLASH / _BURSTWRITE_FROM_XRAM
//                        _BIT6: Y_FORMULA -> 0: Y = (2R+5G+B)/8, 1: Y = (5R+8G+3B)/16
//                        _BIT5: SOFT_CLAMP -> 0: Disable, 1: Enable
//                        _BIT4: DCC_MODE -> 0:Auto Mode, 1: Manual Mode
//                        _BIT3: SCENE_CHANGE -> 0: Disable, 1: Enable
//                        _BIT1: Saturation Compensation -> 0: Disable, 1: Enable
//                        _BIT0: BLD_MODE -> 0: old mode, 1: new mode
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCAdjust(EnumSelRegion enumSelRegion, BYTE *pucDccTable, BYTE ucBankAddress)
{
    BYTE ucAdjustOption = 0;
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif
    if(pucDccTable != _NULL_POINTER)
    {
        ScalerFlashRead(ucBankAddress, &pucDccTable[_DCC_ADJOPTION_TABLE_OFFSET], 1, &ucAdjustOption);

        // Load DCC table after DCC Flag Done
        if(ScalerDDomainBackgroundCheck(enumSelRegion) == _FALSE)
        {
            ScalerTimerPollingFlagProc(20, P7_C8_DCC_CTRL_1, _BIT6, 1);
        }
        // page0: 0x07CA_0003~_000B 0x07CA_0017~001B
        ScalerSetBit(P7_CB_DCC_CTRL + usPage, ~(_BIT1 | _BIT0), _PAGE0);
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_03_PORT_PAGE0_BBE_CTRL);
        ScalerBurstWrite(&pucDccTable[_DCC_CONTORL_TABLE_OFFSET], _DCC_TABLE_SIZE_CTRL, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_17_PORT_PAGE0_YHL_THD);
        ScalerBurstWrite(&pucDccTable[_DCC_CONTORL_LSB_TABLE_OFFSET], _DCC_TABLE_SIZE_CTRL_LSB, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));

        // Fill DCC user curve table
        // Select page1
        ScalerSetBit(P7_CB_DCC_CTRL + usPage, ~(_BIT1 | _BIT0), _PAGE1);
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_00_PORT_PAGE1_DEF_CRV01_H);
        ScalerBurstWrite(&pucDccTable[_DCC_CURVE_TABLE_OFFSET], _DCC_TABLE_SIZE_CRV, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_1B_PORT_PAGE1_DEF_CRV00_HALF_H);
        ScalerBurstWrite(&pucDccTable[_DCC_CURVE_LSB_TABLE_OFFSET], _DCC_TABLE_SIZE_CRV_LSB, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
#if(_HW_DCC_DB_TYPE == _DCC_DB_GEN_1)
        // Local DB Apply
        ScalerSetBit(P7_C7_DCC_CTRL_0 + usPage, ~_BIT0, _BIT0);
#endif

        ScalerSetBit(P7_C8_DCC_CTRL_1 + usPage, ~(_BIT5 | _BIT4), ((ucAdjustOption & (_BIT1 | _BIT0)) << 4));
        ScalerSetBit(P7_C7_DCC_CTRL_0 + usPage, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (ucAdjustOption & (_BIT6 | _BIT5 | _BIT4 | _BIT3)));

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        if(enumSelRegion == _FULL_REGION)
        {
            usPage = _REG_MAIN2_PAGE;
            ScalerSetBit(P7_CB_DCC_CTRL + usPage, ~(_BIT1 | _BIT0), _PAGE0);
            ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_03_PORT_PAGE0_BBE_CTRL);
            ScalerBurstWrite(&pucDccTable[_DCC_CONTORL_TABLE_OFFSET], _DCC_TABLE_SIZE_CTRL, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
            ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_17_PORT_PAGE0_YHL_THD);
            ScalerBurstWrite(&pucDccTable[_DCC_CONTORL_LSB_TABLE_OFFSET], _DCC_TABLE_SIZE_CTRL_LSB, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
            ScalerSetBit(P7_CB_DCC_CTRL + usPage, ~(_BIT1 | _BIT0), _PAGE1);
            ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_00_PORT_PAGE1_DEF_CRV01_H);
            ScalerBurstWrite(&pucDccTable[_DCC_CURVE_TABLE_OFFSET], _DCC_TABLE_SIZE_CRV, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
            ScalerSetByte(P7_C9_DCC_ADDRESS_PORT + usPage, _P7_CA_PT_1B_PORT_PAGE1_DEF_CRV00_HALF_H);
            ScalerBurstWrite(&pucDccTable[_DCC_CURVE_LSB_TABLE_OFFSET], _DCC_TABLE_SIZE_CRV_LSB, ucBankAddress, P7_CA_DCC_DATA_PORT + usPage, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
#if(_HW_DCC_DB_TYPE == _DCC_DB_GEN_1)
            // Local DB Apply
            ScalerSetBit(P7_C7_DCC_CTRL_0 + usPage, ~_BIT0, _BIT0);
#endif
            ScalerSetBit(P7_C8_DCC_CTRL_1 + usPage, ~(_BIT5 | _BIT4), ((ucAdjustOption & (_BIT1 | _BIT0)) << 4));
            ScalerSetBit(P7_C7_DCC_CTRL_0 + usPage, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (ucAdjustOption & (_BIT6 | _BIT5 | _BIT4 | _BIT3)));
        }
#endif

        // PS: M1 and M2 DCC share the M1 DCC enable, M2 has no DCC enable.
        // PS: S1 and S2 DCC share the S1 DCC enable, S2 has no DCC enable.
        if((usPage == _REG_MAIN1_PAGE) || (usPage == _REG_MAIN2_PAGE))
        {
            ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT7, _BIT7);
        }
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        else
        {
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
            {
                ScalerSetBit(P87_C7_DCC_CTRL_0_M3, ~_BIT7, _BIT7);
            }
        }
#endif

        // Set to manual mode
        ScalerSetBit(P7_C7_DCC_CTRL_0 + usPage, ~_BIT4, _BIT4);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable DCC Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P7_C8_DCC_CTRL_1, ~_BIT7, _BIT7);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerSetBit(P47_C8_DCC_CTRL_1_M2, ~_BIT7, _BIT7);
#endif
    }
    else
    {
        ScalerSetBit(P7_C8_DCC_CTRL_1, ~_BIT7, 0x00);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerSetBit(P47_C8_DCC_CTRL_1_M2, ~_BIT7, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Adjust DCC Highlight Window Active Region
// Input Value  : enumSelRegion --> OSD Select region
//                enumDBApply
//                bOn --> Enable/Disable the DCC of the OSD select region
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = 0;
    BYTE ucMask = 0;

    if(enumSelRegion == _NON_REGION)
    {
        return;
    }

    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);

    ucHlwSetting = ScalerGetDataPortSingleByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_25_PORT_PAGE0_HLW_CONTROL);

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT7;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT6;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT7 | _BIT6);
            break;
    }

    if(bOn == _TRUE)
    {
        ucHlwSetting &= ~ucMask;
    }
    else
    {
        ucHlwSetting |= ucMask;
    }

    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetDataPortByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_25_PORT_PAGE0_HLW_CONTROL, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Adjust DCC Highlight Window SetA/SetB Region by Osd select region
// Input Value  : enumSelRegion --> OSD Select region
//                EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    // Select page00
    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_25_PORT_PAGE0_HLW_CONTROL, ~(_BIT5 | _BIT4), ((BYTE)enumSetSel << 4));
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust DCC Highlight Window SetA/SetB Region by Osd select region
// Input Value  : enumSelRegion --> OSD Select region
//                EnumDBApply
// Output Value : None
//--------------------------------------------------
EnumHLWSetSel ScalerColorDCCGetEffectiveRegion(void)
{
    // Select page00
    ScalerSetBit(P7_CB_DCC_CTRL, ~(_BIT1 | _BIT0), _PAGE0);
    return (EnumHLWSetSel)(ScalerGetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_25_PORT_PAGE0_HLW_CONTROL, (_BIT5 | _BIT4)) >> 4);
}
#endif

//--------------------------------------------------
// Description  : Set DCC Auto Mode Measure Region
// Input Value  : enumDCCAutoModeRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCSetAutoModeRegion(EnumSelRegion enumSelRegion, EnumDCCAutoModeEnable enumDCCAutoModeEnable)
{
    BYTE ucAutoModeOption = (enumDCCAutoModeEnable == _DCC_AUTOMODE_ON) ? 0x00 : _BIT4;
    switch(ScalerColorDCCGetSettingType(enumSelRegion))
    {
        case _DCC_SETTING_FULL:
            ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT4, ucAutoModeOption);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerSetBit(P7_C7_DCC_CTRL_0 + _REG_MAIN2_PAGE, ~_BIT4, ucAutoModeOption);
#endif
            break;

        case _DCC_SETTING_INSIDE:
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerSetBit(P7_C7_DCC_CTRL_0 + _REG_MAIN2_PAGE, ~_BIT4, ucAutoModeOption);
#else
            ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT4, ucAutoModeOption);
#endif
            break;

        case _DCC_SETTING_OUTSIDE:
            ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT4, ucAutoModeOption);
            break;

        case _DCC_SETTING_OTHER:
        default:
            ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT4, _BIT4);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerSetBit(P7_C7_DCC_CTRL_0 + _REG_MAIN2_PAGE, ~_BIT4, _BIT4);
#endif
            break;
    }
}
#endif

