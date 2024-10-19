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
// ID Code      : ScalerColorDCR.c
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
#if(_COLOR_IP_DCR == _ON)
bit g_bColorDCRReadyStatus = _FALSE;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_DCR == _ON)
//--------------------------------------------------
// Description  : Set DCR Source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRSetSource(void)
{
    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT4 | _BIT0), _DCR_SOURCE);
}

//--------------------------------------------------
// Description  : Set DCR TH1 & TH2
// Input Value  : TH1 & TH2, EnumDCRMeasureSel
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRAdjust(WORD usThreshold1, WORD usThreshold2, EnumDCRMeasureSel enumDCRMeasureSel)
{
#if((_HW_DCR_TYPE == _DCR_GEN_0) ||\
    (_HW_DCR_TYPE == _DCR_GEN_2))

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_00_DCR_THESHOLD1_1 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, (BYTE)(usThreshold1 & 0xFF));

#if(_HW_DCR_TYPE == _DCR_GEN_2)
    usThreshold2 = usThreshold2;
#elif(_HW_DCR_TYPE == _DCR_GEN_0)
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_01_DCR_THESHOLD2_1 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, (BYTE)(usThreshold2 & 0xFF));
#endif

    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT3 | _BIT2 | _BIT1), (enumDCRMeasureSel << 1));

#elif((_HW_DCR_TYPE == _DCR_GEN_1) ||\
      (_HW_DCR_TYPE == _DCR_GEN_3) ||\
      (_HW_DCR_TYPE == _DCR_GEN_4) ||\
      (_HW_DCR_TYPE == _DCR_GEN_5))

#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT7 | _BIT4), 0x00);
#endif

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_00_DCR_THESHOLD1_1 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usThreshold1 >> 2);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_01_DCR_THESHOLD2_1 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usThreshold2 >> 2);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_38_DCR_THESHOLD1_0 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, (usThreshold1 & (_BIT1 | _BIT0)) << 6);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_39_DCR_THESHOLD2_0 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, (usThreshold2 & (_BIT1 | _BIT0)) << 6);

    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (enumDCRMeasureSel << 1));

#endif
}

//--------------------------------------------------
// Description  : Clear DCR Data Ready Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRClrDataReadyStatus(void)
{
    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT4), _BIT4);
}

//--------------------------------------------------
// Description  : Control DCR Data Reflash
// Input Value  : bMode ->
//                _ENABLE : Enable reflash DCR Measure result
//                _DISABLE : Disable reflash DCR Measure result
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRDataRefreshControl(bit bMode)
{
    if(bMode == _ENABLE)
    {
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, _BIT0);
    }
    else
    {
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, _BIT1 | _BIT0);
    }
}

//--------------------------------------------------
// Description  : DCR ON or OFF
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerColorDCREnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // Set DCR enable
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, _BIT0);
    }
    else
    {
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, 0x00);
    }
}

#if(_HW_DCR_BIT == _DCR_8BIT)
//--------------------------------------------------
// Description  : Get DCR Average Result
// Input Value  : enumDCRAverageOption : DCR Measure Result Option
//                ulDivider   : GET_MDOMAIN_OUTPUT_HWIDTH() * GET_MDOMAIN_OUTPUT_VHEIGHT() * n(3 or 8)
//                              n = 3; when DCR Measure _MEASURE_AVERAGE(R+G+B)
//                              n = 8; when DCR Measure _MEASURE_Y(2R+5G+B)
// Output Value : None
//--------------------------------------------------
WORD ScalerColorDCRGetAverage_8BIT(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider)
{
    WORD usResult = 0;

    if(ulDivider == 0)
    {
        return 0;
    }

    if(GET_DCR_READY_STATUS() == _FALSE)
    {
        return 0;
    }

    switch(enumDCRAverageOption)
    {
        case _DCR_ABOVE_TH1_VAL_TOTAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);

            usResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]) / ulDivider;
            break;

#if(_HW_DCR_TYPE == _DCR_GEN_0)
        case _DCR_ABOVE_TH2_VAL_TOTAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);

            usResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]) / ulDivider;
            break;
#endif

        default:
            break;
    }

    return usResult;
}
#endif

#if(_HW_DCR_BIT == _DCR_10BIT)
//--------------------------------------------------
// Description  : Get DCR Average Result
// Input Value  : enumDCRAverageOption : DCR Measure Result Option
//                ulDivider   : GET_MDOMAIN_OUTPUT_HWIDTH() * GET_MDOMAIN_OUTPUT_VHEIGHT() * n(3 or 8)
//                              n = 3; when DCR Measure _MEASURE_AVERAGE(R+G+B)
//                              n = 8; when DCR Measure _MEASURE_Y(2R+5G+B)
// Output Value : None
//--------------------------------------------------
WORD ScalerColorDCRGetAverage_10BIT(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider)
{
    DWORD ulTotalSum = 0;
    WORD usResult = 0;

    BYTE ucHighPart = 0;
    DWORD ulLowPart = 0;

    if(ulDivider == 0)
    {
        return 0;
    }

    if(GET_DCR_READY_STATUS() == _FALSE)
    {
        return 0;
    }

#if(_HW_DCR_TYPE == _DCR_GEN_3)
    if(ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == _BIT0)
    {
        return 0;
    }
#endif

    switch(enumDCRAverageOption)
    {
        case _DCR_ABOVE_TH1_VAL_TOTAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ulTotalSum = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            pData[0] = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & _BIT4) << 2);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            pData[1] = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 2);
            ucHighPart = (pData[0] | pData[1] | (((BYTE)(ulTotalSum >> 24) & 0xC0) >> 6));
#else
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            ucHighPart = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6 | _BIT5)) >> 3) | (((BYTE)(ulTotalSum >> 24) & 0xC0) >> 6);
#endif
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            ulLowPart = (ulTotalSum << 2) | ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6)) >> 6);
            break;

        case _DCR_ABOVE_TH2_VAL_TOTAL:
#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
            if(ScalerGetBit(P7_DA_DCR_CTRL, _BIT7) == _BIT7)
            {
                ucHighPart = 0;
                ulLowPart = 0;
            }
            else
#endif
            {
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
                ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
                ulTotalSum = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);
#if(_HW_DCR_TYPE == _DCR_GEN_5)
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
                pData[0] = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & _BIT0) << 6);
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
                pData[1] = (ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2 | _BIT1 | _BIT0) << 2);
                ucHighPart = (pData[0] | pData[1] | (((BYTE)(ulTotalSum >> 24) & 0xC0) >> 6));
#else
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
                ucHighPart = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2 | _BIT1)) << 1) | (((BYTE)(ulTotalSum >> 24) & 0xC0) >> 6);
#endif
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
                ulLowPart = (ulTotalSum << 2) | ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2)) >> 2);
            }
            break;

        default:
            break;
    }

    if(ucHighPart > 63)
    {
        usResult = (((((((DWORD)ucHighPart) << 25) % ulDivider) << 7) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 25) / ulDivider) << 7);
    }
    else if(ucHighPart > 31)
    {
        usResult = (((((((DWORD)ucHighPart) << 26) % ulDivider) << 6) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 26) / ulDivider) << 6);
    }
    else if(ucHighPart > 15)
    {
        usResult = (((((((DWORD)ucHighPart) << 27) % ulDivider) << 5) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 27) / ulDivider) << 5);
    }
    else if(ucHighPart > 7)
    {
        usResult = (((((((DWORD)ucHighPart) << 28) % ulDivider) << 4) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 28) / ulDivider) << 4);
    }
    else if(ucHighPart > 3)
    {
        usResult = (((((((DWORD)ucHighPart) << 29) % ulDivider) << 3) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 29) / ulDivider) << 3);
    }
    else if(ucHighPart > 1)
    {
        usResult = (((((((DWORD)ucHighPart) << 30) % ulDivider) << 2) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 30) / ulDivider) << 2);
    }
    else if(ucHighPart > 0)
    {
        usResult = (((((((DWORD)ucHighPart) << 31) % ulDivider) << 1) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 31) / ulDivider) << 1);
    }
    else
    {
        usResult = ulLowPart / ulDivider;
    }

    return usResult;
}
#endif

//--------------------------------------------------
// Description  : Get DCR Data Ready Status
// Input Value  : None
// Output Value : DCR Data Ready Status
//--------------------------------------------------
bit ScalerColorDCRGetDataReadyStatus(void)
{
    if(ScalerGetBit(P7_DA_DCR_CTRL, _BIT4) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_HW_DCR_BIT == _DCR_10BIT)
//--------------------------------------------------
// Description  : Get DCR Max RGB
// Input Value  : None
// Output Value : Max RGB
//--------------------------------------------------
WORD ScalerColorDCRGetMaxRGB_10BIT(void)
{
    WORD usResultR = 0;
    WORD usResultG = 0;
    WORD usResultB = 0;

    if(GET_DCR_READY_STATUS() == _FALSE)
    {
        return 0;
    }

#if(_HW_DCR_TYPE == _DCR_GEN_3)
    if(ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == _BIT0)
    {
        return 0;
    }
#endif

    // Get R
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2C_DCR_HIGH_LV_VAL_R_0 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    usResultR = (TO_WORD(pData[0], pData[1]) >> 6);

    // Get G
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2E_DCR_HIGH_LV_VAL_G_0 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    usResultG = (TO_WORD(pData[0], pData[1]) >> 6);

    // Get B
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_30_DCR_HIGH_LV_VAL_B_0 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    usResultB = (TO_WORD(pData[0], pData[1]) >> 6);

    // return max in R/G/B
    PDATA_WORD(0) = MAXOF(usResultR, usResultG);
    PDATA_WORD(0) = MAXOF(PDATA_WORD(0), usResultB);

    return PDATA_WORD(0);
}
#endif

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DCR Max Y
// Input Value  : None
// Output Value : Max Y 8 BIT
//--------------------------------------------------
BYTE ScalerColorDCRMaxYStoreResult(void)
{
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_0)
#if(_HW_DCR_YMAXMIN_OPTION_SUPPORT == _ON)
#if(_HW_DCR_BIT == _DCR_8BIT)
    return ScalerColorDCRReadResult_8BIT(_DCR_Y_MAX_VAL);
#elif(_HW_DCR_BIT == _DCR_10BIT)
    return ((ScalerColorDCRReadResult_10BIT(_DCR_Y_MAX_VAL)) >> 2);
#else
#warning "_HW_DCR_BIT Not Support!!!"
#endif
#else
#warning "_DCR_Y_MAX_VAL Not Support!!!"
#endif


#elif(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    WORD usDCRMaxR = 0x0000;
    WORD usDCRMaxG = 0x0000;
    WORD usDCRMaxB = 0x0000;
    WORD usDCRMaxY = 0x0000;

#if(_HW_DCR_YMAXMIN_OPTION_SUPPORT == _ON)
#if(_HW_DCR_BIT == _DCR_8BIT)
    usDCRMaxR = ScalerColorDCRReadResult_8BIT(_DCR_HIGH_LV_VAL_R);
    usDCRMaxG = ScalerColorDCRReadResult_8BIT(_DCR_HIGH_LV_VAL_G);
    usDCRMaxB = ScalerColorDCRReadResult_8BIT(_DCR_HIGH_LV_VAL_B);
    usDCRMaxY = MAXOF(usDCRMaxR, usDCRMaxG);
    usDCRMaxY = MAXOF(usDCRMaxY, usDCRMaxB);
    return (usDCRMaxY);
#elif(_HW_DCR_BIT == _DCR_10BIT)
    usDCRMaxR = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_R);
    usDCRMaxG = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_G);
    usDCRMaxB = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_B);
    usDCRMaxY = MAXOF(usDCRMaxR, usDCRMaxG);
    usDCRMaxY = MAXOF(usDCRMaxY, usDCRMaxB);
    return ((usDCRMaxY) >> 2);
#else
#warning "_HW_DCR_BIT Not Support!!!"
#endif
#else
#warning "_DCR_Y_MAX_VAL Not Support!!!"
#endif
#endif // end of _DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1
}

#endif

//--------------------------------------------------
// Description  : Get DCR Measure Region Size
// Input Value  : DCR Measure Region
// Output Value : DCR Measure Region Size
//--------------------------------------------------
DWORD ScalerColorDCRGetMeasureRegionSize(EnumSelRegion enumDCRMeasureRegion)
{
    DWORD ulDCRMeasureRegionSize = 0;
    WORD usAHStart = 0;
    WORD usAHEnd = 0;
    WORD usAVStart = 0;
    WORD usAVEnd = 0;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            if(enumDCRMeasureRegion == _1P_NORMAL_REGION)
            {
                if(ScalerDDomainBackgroundCheck(_1P_NORMAL_REGION) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            if((enumDCRMeasureRegion == _FULL_REGION) || (enumDCRMeasureRegion == _2P_PIP_MAIN))
            {
                WORD usSubHStart = 0;
                WORD usSubHEnd = 0;
                WORD usSubVStart = 0;
                WORD usSubVEnd = 0;

                if(ScalerDDomainBackgroundCheck(_2P_PIP_MAIN) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                // Sub1 Active
                usSubHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                usSubHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                usSubVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                usSubVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
#endif

                if((enumDCRMeasureRegion == _FULL_REGION) && (ScalerDDomainBackgroundCheck(_2P_PIP_SUB) == _FALSE)) // FULL + SUB - SUB(below code, overlap region), statistic Full
                {
                    ulDCRMeasureRegionSize += (DWORD)(usSubHEnd - usSubHStart) * (usSubVEnd - usSubVStart);  // + Sub size
                }

                if(ScalerDDomainBackgroundCheck(_2P_PIP_MAIN) == _FALSE) // FULL - SUB = MAIN, statistic Main
                {
                    ulDCRMeasureRegionSize -= (DWORD)(usSubHEnd - usSubHStart) * (usSubVEnd - usSubVStart);   // - Overlap size
                }
            }

            if(enumDCRMeasureRegion == _2P_PIP_SUB) // only statistic sub
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_2P_PIP_SUB) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            if((enumDCRMeasureRegion == _FULL_REGION) || (enumDCRMeasureRegion == _2P_PIP_EAGLE_SIGHT_MAIN))
            {
                WORD usSubHStart = 0;
                WORD usSubHEnd = 0;
                WORD usSubVStart = 0;
                WORD usSubVEnd = 0;

                if(ScalerDDomainBackgroundCheck(_2P_PIP_EAGLE_SIGHT_MAIN) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                // Sub1 Active
                usSubHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                usSubHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                usSubVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                usSubVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
#endif
                if((usSubHStart >= usAHEnd) ||
                   (usSubHEnd <= usAHStart) ||
                   (usSubVStart >= usAVEnd) ||
                   (usSubVEnd <= usAVStart))   // sub out of main
                {
                    usAHStart = 0;
                    usAHEnd = 0;
                    usAVStart = 0;
                    usAVEnd = 0;
                }
                else
                {
                    if(usSubHStart > usAHStart)
                    {
                        usAHStart = usSubHStart;
                    }

                    if(usSubHEnd < usAHEnd)
                    {
                        usAHEnd = usSubHEnd;
                    }

                    if(usSubVStart > usAVStart)
                    {
                        usAVStart = usSubVStart;
                    }

                    if(usSubVEnd < usAVEnd)
                    {
                        usAVEnd = usSubVEnd;
                    }
                }

                if((enumDCRMeasureRegion == _FULL_REGION) && (ScalerDDomainBackgroundCheck(_2P_PIP_EAGLE_SIGHT_SUB) == _FALSE)) // FULL + SUB - SUB(below code, overlap region), statistic Full
                {
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
                    if(ScalerGetBit(P24_35_CIRCLE_BLENDING_CTRL, _BIT7) == _BIT7) // Circle HLW Enable
                    {
                        WORD usShortSideRadius = (MINOF((usSubHEnd - usSubHStart), (usSubVEnd - usSubVStart))) / 2;
                        ulDCRMeasureRegionSize += (DWORD)(((QWORD)(usShortSideRadius)) * usShortSideRadius * 3141 / 1000);  // + Sub size
                    }
                    else
#endif
                    {
                        ulDCRMeasureRegionSize += (DWORD)(usSubHEnd - usSubHStart) * (usSubVEnd - usSubVStart);  // + Sub size
                    }
                }

                if(ScalerDDomainBackgroundCheck(_2P_PIP_EAGLE_SIGHT_MAIN) == _FALSE) // FULL - SUB = MAIN, statistic Main
                {
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
                    if(ScalerGetBit(P24_35_CIRCLE_BLENDING_CTRL, _BIT7) == _BIT7) // Circle HLW Enable
                    {
                        WORD usShortSideRadius = (MINOF((usSubHEnd - usSubHStart), (usSubVEnd - usSubVStart))) / 2;
                        ulDCRMeasureRegionSize -= (DWORD)(((QWORD)(usShortSideRadius)) * usShortSideRadius * 3141 / 1000);  // - Overlap size
                    }
                    else
#endif
                    {
                        ulDCRMeasureRegionSize -= (DWORD)(usSubHEnd - usSubHStart) * (usSubVEnd - usSubVStart);   // - Overlap size
                    }
                }
            }

            if(enumDCRMeasureRegion == _2P_PIP_EAGLE_SIGHT_SUB) // only statistic sub
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_2P_PIP_EAGLE_SIGHT_SUB) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
                    if(ScalerGetBit(P24_35_CIRCLE_BLENDING_CTRL, _BIT7) == _BIT7) // Circle HLW Enable
                    {
                        WORD usShortSideRadius = (MINOF((usAHEnd - usAHStart), (usAVEnd - usAVStart))) / 2;
                        ulDCRMeasureRegionSize += (DWORD)(((QWORD)(usShortSideRadius)) * usShortSideRadius * 3141 / 1000);
                    }
                    else
#endif
                    {
                        ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                    }
                }
#endif
            }
            break;
#endif


#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            if((enumDCRMeasureRegion == _2P_PBP_LR_EQUAL_L) || (enumDCRMeasureRegion == _FULL_REGION)) // HLW outside
            {
                if(ScalerDDomainBackgroundCheck(_2P_PBP_LR_EQUAL_L) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _2P_PBP_LR_EQUAL_R) || (enumDCRMeasureRegion == _FULL_REGION)) // HLW inside
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_2P_PBP_LR_EQUAL_R) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }

            break;

        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            if((enumDCRMeasureRegion == _2P_PBP_LR_L_LARGE_L) || (enumDCRMeasureRegion == _FULL_REGION)) // HLW outside
            {
                if(ScalerDDomainBackgroundCheck(_2P_PBP_LR_L_LARGE_L) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _2P_PBP_LR_L_LARGE_R) || (enumDCRMeasureRegion == _FULL_REGION)) // HLW inside
            {
                if(ScalerDDomainBackgroundCheck(_2P_PBP_LR_L_LARGE_R) == _FALSE)
                {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
#endif
                }
            }
            break;

        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            if((enumDCRMeasureRegion == _2P_PBP_LR_R_LARGE_L) || (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_2P_PBP_LR_R_LARGE_L) == _FALSE)
                {
                    if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R1_A1)
                    {
                        // Main1 Active
                        usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                        usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                        usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                        usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);
                    }
                    else
                    {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                        usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                        usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                        usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                        usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
#endif
                    }
                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _2P_PBP_LR_R_LARGE_R) || (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_2P_PBP_LR_R_LARGE_R) == _FALSE)
                {
                    if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT) == _DDOMAIN_RGN_R1_A1)
                    {
                        // Main1 Active
                        usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                        usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                        usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                        usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);
                    }
                    else
                    {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                        usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                        usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                        usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                        usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);
#endif
                    }
                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            if((enumDCRMeasureRegion == _2P_PBP_TB_T) || (enumDCRMeasureRegion == _FULL_REGION)) // HLW outside
            {
                if(ScalerDDomainBackgroundCheck(_2P_PBP_TB_T) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }

            if((enumDCRMeasureRegion == _2P_PBP_TB_B) || (enumDCRMeasureRegion == _FULL_REGION)) // HLW inside
            {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_2P_PBP_TB_B) == _FALSE)
                {
                    // Main2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            if((enumDCRMeasureRegion == _3P_FLAG_L) ||
               (enumDCRMeasureRegion == _3P_FLAG_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_FLAG_R_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_3P_FLAG_L) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _3P_FLAG_R) ||
               (enumDCRMeasureRegion == _3P_FLAG_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_FLAG_L_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_FLAG_R) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R3a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R3a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R3a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R3a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            if((enumDCRMeasureRegion == _3P_FLAG_M) ||
               (enumDCRMeasureRegion == _3P_FLAG_L_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_FLAG_R_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_FLAG_M) == _FALSE)
                {
                    // Sub2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
            if((enumDCRMeasureRegion == _3P_SKEW_L_M) ||
               (enumDCRMeasureRegion == _3P_SKEW_L_T_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_L_B_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_L_M) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }

            if((enumDCRMeasureRegion == _3P_SKEW_L_T) ||
               (enumDCRMeasureRegion == _3P_SKEW_L_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_L_B_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_L_T) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            if((enumDCRMeasureRegion == _3P_SKEW_L_B) ||
               (enumDCRMeasureRegion == _3P_SKEW_L_T_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_L_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_L_B) == _FALSE)
                {
                    // Sub2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;

        case _DISPLAY_MODE_3P_SKEW_R:
            if((enumDCRMeasureRegion == _3P_SKEW_R_T) ||
               (enumDCRMeasureRegion == _3P_SKEW_R_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_R_B_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_R_T) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _3P_SKEW_R_B) ||
               (enumDCRMeasureRegion == _3P_SKEW_R_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_R_T_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_R_B) == _FALSE)
                {
                    // Main2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            if((enumDCRMeasureRegion == _3P_SKEW_R_M) ||
               (enumDCRMeasureRegion == _3P_SKEW_R_T_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_R_B_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_R_M) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
            if((enumDCRMeasureRegion == _3P_SKEW_T_M) ||
               (enumDCRMeasureRegion == _3P_SKEW_T_L_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_T_R_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_T_M) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _3P_SKEW_T_L) ||
               (enumDCRMeasureRegion == _3P_SKEW_T_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_T_R_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_T_L) == _FALSE)
                {
                    // Main2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            if((enumDCRMeasureRegion == _3P_SKEW_T_R) ||
               (enumDCRMeasureRegion == _3P_SKEW_T_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_T_L_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_T_R) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;

        case _DISPLAY_MODE_3P_SKEW_B:
            if((enumDCRMeasureRegion == _3P_SKEW_B_L) ||
               (enumDCRMeasureRegion == _3P_SKEW_B_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_B_R_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_B_L) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }
            if((enumDCRMeasureRegion == _3P_SKEW_B_M) ||
               (enumDCRMeasureRegion == _3P_SKEW_B_L_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_B_R_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_B_M) == _FALSE)
                {
                    // Main2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            if((enumDCRMeasureRegion == _3P_SKEW_B_R) ||
               (enumDCRMeasureRegion == _3P_SKEW_B_M_OUTSIDE) ||
               (enumDCRMeasureRegion == _3P_SKEW_B_L_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_3P_SKEW_B_R) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            if((enumDCRMeasureRegion == _4P_LT) ||
               (enumDCRMeasureRegion == _4P_LB_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_RT_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_RB_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
                if(ScalerDDomainBackgroundCheck(_4P_LT) == _FALSE)
                {
                    // Main1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
            }

            if((enumDCRMeasureRegion == _4P_LB) ||
               (enumDCRMeasureRegion == _4P_LT_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_RT_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_RB_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_4P_LB) == _FALSE)
                {
                    // Main2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }

            if((enumDCRMeasureRegion == _4P_RT) ||
               (enumDCRMeasureRegion == _4P_LT_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_LB_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_RB_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_4P_RT) == _FALSE)
                {
                    // Sub1 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }

            if((enumDCRMeasureRegion == _4P_RB) ||
               (enumDCRMeasureRegion == _4P_LT_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_LB_OUTSIDE) ||
               (enumDCRMeasureRegion == _4P_RT_OUTSIDE) ||
               (enumDCRMeasureRegion == _FULL_REGION))
            {
#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
                if(ScalerDDomainBackgroundCheck(_4P_RB) == _FALSE)
                {
                    // Sub2 Active
                    usAHStart = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_START);
                    usAHEnd = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_END);
                    usAVStart = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_START);
                    usAVEnd = ScalerDDomainGetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_END);

                    ulDCRMeasureRegionSize += (DWORD)(usAHEnd - usAHStart) * (usAVEnd - usAVStart);
                }
#endif
            }
            break;
#endif
        default:
            break;
    }

    return ulDCRMeasureRegionSize;
}

#if(_HW_DCR_BIT == _DCR_8BIT)
//--------------------------------------------------
// Description  : Read DCR Histogram Result
// Input Value  : DCR Histogram Information Option
// Output Value : DCR Histogram Information
// Note         : When get _DCR_ABOVE_TH_VAL(8bit), should get _DCR_ABOVE_TH_VAL_HIGH / _DCR_ABOVE_TH_VAL_10BIT_HIGH first
//              : then get _DCR_ABOVE_TH_VAL / _DCR_ABOVE_TH_VAL_10BIT
//--------------------------------------------------
DWORD ScalerColorDCRReadResult_8BIT(EnumDCRAdjOption enumDCRReadOption)
{
    DWORD ulResult = 0;

    if(GET_DCR_READY_STATUS() == _FALSE)
    {
        return 0;
    }

    switch(enumDCRReadOption)
    {
        case _DCR_ABOVE_TH1_NUM:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_02_DCR_ABOVE_TH1_NUM_2 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);

            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
            break;

        case _DCR_ABOVE_TH1_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);

            ulResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);
            break;

        case _DCR_ABOVE_TH1_VAL_HIGH:
            ulResult = 0;
            break;

#if(_HW_DCR_TH2_OPTION_SUPPORT == _ON)
        case _DCR_ABOVE_TH2_NUM:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_09_DCR_ABOVE_TH2_NUM_2 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);

            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
            break;

        case _DCR_ABOVE_TH2_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);

            ulResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);
            break;

        case _DCR_ABOVE_TH2_VAL_HIGH:
            ulResult = 0;
            break;
#endif

        case _DCR_HIGH_LV_VAL_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

        case _DCR_LOW_LV_VAL_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_15_DCR_LOW_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

        case _DCR_HIGH_LV_VAL_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

        case _DCR_LOW_LV_VAL_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1B_DCR_LOW_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

        case _DCR_HIGH_LV_VAL_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

        case _DCR_LOW_LV_VAL_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_21_DCR_LOW_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

#if(_HW_DCR_YMAXMIN_OPTION_SUPPORT == _ON)
        case _DCR_Y_MAX_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_28_DCR_Y_MAX_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;

        case _DCR_Y_MIN_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_29_DCR_Y_MIN_1 << 2) | _BIT1 | _BIT0);
            ulResult = ScalerGetByte(P7_D9_DCR_DATA_PORT);
            break;
#endif

        default:
            break;
    }

    return ulResult;
}
#endif

#if(_HW_DCR_BIT == _DCR_10BIT)
//--------------------------------------------------
// Description  : Read DCR Histogram Result
// Input Value  : DCR Histogram Information Option
// Output Value : DCR Histogram Information
// Note         : When get _DCR_ABOVE_TH_VAL(10bit), should get _DCR_ABOVE_TH_VAL_HIGH / _DCR_ABOVE_TH_VAL_10BIT_HIGH first
//              : then get _DCR_ABOVE_TH_VAL / _DCR_ABOVE_TH_VAL_10BIT
//--------------------------------------------------
DWORD ScalerColorDCRReadResult_10BIT(EnumDCRAdjOption enumDCRReadOption)
{
    DWORD ulResult = 0;

    if(GET_DCR_READY_STATUS() == _FALSE)
    {
        return 0;
    }

#if(_HW_DCR_TYPE == _DCR_GEN_3)
    if(ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == _BIT0)
    {
        return 0;
    }
#endif

    switch(enumDCRReadOption)
    {
        case _DCR_ABOVE_TH1_NUM:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_02_DCR_ABOVE_TH1_NUM_2 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_36_DCR_HIGHT_BIT_0 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT7 | _BIT6)) >> 6);
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;

        case _DCR_ABOVE_TH1_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ulResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT7 | _BIT6));

            ulResult = ((ulResult << 2) | (pData[0] >> 6));
            break;

        case _DCR_ABOVE_TH1_VAL_HIGH:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            pData[2] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT4));

            ulResult = (pData[2] << 2) | (pData[0] >> 2) | ((pData[1] & 0xC0) >> 6);
#else
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT7 | _BIT6 | _BIT5));

            ulResult = (pData[0] >> 3) | ((pData[1] & 0xC0) >> 6);
#endif
            break;

        case _DCR_ABOVE_TH2_NUM:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_09_DCR_ABOVE_TH2_NUM_2 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_36_DCR_HIGHT_BIT_0 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT5 | _BIT4)) >> 4);
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;

        case _DCR_ABOVE_TH2_VAL:
#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
            if(ScalerGetBit(P7_DA_DCR_CTRL, _BIT7) == _BIT7)
            {
                ulResult = 0;
            }
            else
#endif
            {
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
                ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
                ulResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);

                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
                pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2));

                ulResult = (ulResult << 2) | (pData[0] >> 2);
            }
            break;

        case _DCR_ABOVE_TH2_VAL_HIGH:
#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
            if(ScalerGetBit(P7_DA_DCR_CTRL, _BIT7) == _BIT7)
            {
                ulResult = 0;
            }
            else
#endif
            {
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
                pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
                pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
                pData[2] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT0));

                ulResult = ((pData[2] << 6) | (pData[0] << 2) | ((pData[1] & 0xC0) >> 6));
#else
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
                pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2 | _BIT1));

                ulResult = ((pData[0] << 1) | ((pData[1] & 0xC0) >> 6));
#endif
            }
            break;

#if(_HW_DCR_LV_NUM_OPTION_SUPPORT == _ON)
        case _DCR_HIGH_LV_NUM_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_10_DCR_HIGH_LV_NUM_R_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, &pData[1], _NON_AUTOINC);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_22_DCR_HIGH_LV_NUM_R_2 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_36_DCR_HIGHT_BIT_0 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2)) >> 2);
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;

        case _DCR_LOW_LV_NUM_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_12_DCR_LOW_LV_NUM_R_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, &pData[1], _NON_AUTOINC);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_23_DCR_LOW_LV_NUM_R_2 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_36_DCR_HIGHT_BIT_0 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT1 | _BIT0)));
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;
#endif

        case _DCR_HIGH_LV_VAL_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2C_DCR_HIGH_LV_VAL_R_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

        case _DCR_LOW_LV_VAL_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_15_DCR_LOW_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2D_DCR_LOW_LV_VAL_R_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

#if(_HW_DCR_LV_NUM_OPTION_SUPPORT == _ON)
        case _DCR_HIGH_LV_NUM_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_16_DCR_HIGH_LV_NUM_G_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, &pData[1], _NON_AUTOINC);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_24_DCR_HIGH_LV_NUM_G_2 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_37_DCR_HIGHT_BIT_1 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT7 | _BIT6)) >> 6);
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;

        case _DCR_LOW_LV_NUM_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_18_DCR_LOW_LV_NUM_G_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, &pData[1], _NON_AUTOINC);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_25_DCR_LOW_LV_NUM_G_2 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_37_DCR_HIGHT_BIT_1 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT5 | _BIT4)) >> 4);
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;
#endif

        case _DCR_HIGH_LV_VAL_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2E_DCR_HIGH_LV_VAL_G_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

        case _DCR_LOW_LV_VAL_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1B_DCR_LOW_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2F_DCR_LOW_LV_VAL_G_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

#if(_HW_DCR_LV_NUM_OPTION_SUPPORT == _ON)
        case _DCR_HIGH_LV_NUM_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1C_DCR_HIGH_LV_NUM_B_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, &pData[1], _NON_AUTOINC);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_26_DCR_HIGH_LV_NUM_B_2 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_37_DCR_HIGHT_BIT_1 << 2) | _BIT1 | _BIT0);
            pData[3] = (ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2)) >> 2);
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;

        case _DCR_LOW_LV_NUM_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1E_DCR_LOW_LV_NUM_B_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, &pData[1], _NON_AUTOINC);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_27_DCR_LOW_LV_NUM_B_2 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_37_DCR_HIGHT_BIT_1 << 2) | _BIT1 | _BIT0);
            pData[3] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT1 | _BIT0));
            ulResult = TO_DWORD(pData[3], pData[0], pData[1], pData[2]);
#else
            ulResult = TO_DWORD(0, pData[0], pData[1], pData[2]);
#endif
            break;
#endif

        case _DCR_HIGH_LV_VAL_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_30_DCR_HIGH_LV_VAL_B_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

        case _DCR_LOW_LV_VAL_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_21_DCR_LOW_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_31_DCR_LOW_LV_VAL_B_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

        case _DCR_Y_MAX_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_28_DCR_Y_MAX_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_32_DCR_Y_MAX_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

        case _DCR_Y_MIN_VAL:

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_29_DCR_Y_MIN_1 << 2) | _BIT1 | _BIT0);
            pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_33_DCR_Y_MIN_0 << 2) | _BIT1 | _BIT0);
            pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
        case _DCR_MAX_CLL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_34_DCR_MAX_CLL_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 2, pData, _NON_AUTOINC);

            ulResult = (TO_WORD(pData[0], pData[1]) >> 6);
            break;

        case _DCR_MAX_FALL:
            if(ScalerGetBit(P7_DA_DCR_CTRL, _BIT7) == 0x00)
            {
                ulResult = 0;
            }
            else
            {
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
                ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
                ulResult = TO_DWORD(pData[0], pData[1], pData[2], pData[3]);

                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
                pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2));

                ulResult = (ulResult << 2) | (pData[0] >> 2);
            }
            break;

        case _DCR_MAX_FALL_HIGH:
            if(ScalerGetBit(P7_DA_DCR_CTRL, _BIT7) == 0x00)
            {
                ulResult = 0;
            }
            else
            {
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
                pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

#if(_HW_DCR_TYPE == _DCR_GEN_5)
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
                pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
                pData[2] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT0));

                ulResult = ((pData[2] << 6) | (pData[0] << 2) | ((pData[1] & 0xC0) >> 6));
#else
                ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
                pData[0] = ScalerGetBit(P7_D9_DCR_DATA_PORT, (_BIT3 | _BIT2 | _BIT1));

                ulResult = ((pData[0] << 1) | ((pData[1] & 0xC0) >> 6));
#endif
            }
            break;
#endif

        default:
            break;
    }

    return ulResult;
}
#endif

#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset DCR Max CLL & Max FALL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRResetCLLResult(void)
{
    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT6 | _BIT4), _BIT6);
}
#endif

#if(_HW_DCR_SET_BACKGROUND_OPTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DCR Background Color R, G, B
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRSetBackgroundColor(WORD usRValue, WORD usGValue, WORD usBValue)
{
    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_P7_D9_PT_3A_DCR_BG_R_VALUE1 << 2));
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usRValue >> 8);
    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_P7_D9_PT_3B_DCR_BG_R_VALUE0 << 2));
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usRValue & 0xFF);

    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_P7_D9_PT_3C_DCR_BG_G_VALUE1 << 2));
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usGValue >> 8);
    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_P7_D9_PT_3D_DCR_BG_G_VALUE0 << 2));
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usGValue & 0xFF);

    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_P7_D9_PT_3E_DCR_BG_B_VALUE1 << 2));
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usBValue >> 8);
    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_P7_D9_PT_3F_DCR_BG_B_VALUE0 << 2));
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usBValue & 0xFF);
}
#endif

#if(_HW_DCR_SET_BACKGROUND_OPTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DCR Background Enable
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRSetBackgroundEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // Set DCR Background enable
        ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT5 | _BIT4), _BIT5);
    }
    else
    {
        ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT5 | _BIT4), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Set DCR Measure Region
// Input Value  : enumDCCAutoModeRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRSetMeasureRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_FULL_WINDOW:
            ScalerSetBit(P7_DB_DCR_HLW_CONTROL, ~(_BIT7 | _BIT6), 0x00); // Measure Full
            break;

        case _HLW_INSIDE_WINDOW:
            ScalerSetBit(P7_DB_DCR_HLW_CONTROL, ~(_BIT7 | _BIT6), _BIT6); // Measure Inside HLW
            break;

        default:
            ScalerSetBit(P7_DB_DCR_HLW_CONTROL, ~(_BIT7 | _BIT6), _BIT7); // Measure Outside HLW
            break;
    }

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#endif // End of #if(_COLOR_IP_DCR == _ON)
