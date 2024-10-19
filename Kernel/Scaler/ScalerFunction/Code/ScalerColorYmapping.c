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
// ID Code      : ScalerColorYmapping.c
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

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_YMAPPING == _ON)
//--------------------------------------------------
// Description  : Y Mapping M1/M2 Enable/Disable
// Input Value  : EnumSelRegion and EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingEnable(EnumSelRegion enumSelRegion, EnumFunctionOnOFF enumOn)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT7, 0x00);
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        if(enumOn == _FUNCTION_ON)
        {
            ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT7, _BIT7);
        }
        else
        {
            ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT7, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Y Mapping M1/M2 Mode Select -> Y Mode or MaxRGB Mode
// Input Value  : EnumSelRegion and EnumYMappingFunctionMode
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingModeSelect(EnumSelRegion enumSelRegion, EnumYMappingFunctionMode enumYMappingFunctionMode)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(enumYMappingFunctionMode == _YMAPPING_MAXRGB_MODE)
    {
        ScalerSetBit(P9_EF_Y_MAPPING_CTRL2_M1 + usPage, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P9_EF_Y_MAPPING_CTRL2_M1 + usPage, ~_BIT0, 0x00);
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        if(enumYMappingFunctionMode == _YMAPPING_MAXRGB_MODE)
        {
            ScalerSetBit(P49_EF_Y_MAPPING_CTRL2_M2, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(P49_EF_Y_MAPPING_CTRL2_M2, ~_BIT0, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set Y Mapping M1/M2 Gain Precision
// Input Value  : EnumSelRegion and EnumYMappingGainPrecision
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingSetGainPrecision(EnumSelRegion enumSelRegion, EnumYMappingGainPrecision enumYMappingGainPrecision)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~(_BIT5 | _BIT4 | _BIT3), (enumYMappingGainPrecision << 3));

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~(_BIT5 | _BIT4 | _BIT3), (enumYMappingGainPrecision << 3));
    }
#endif
}

//--------------------------------------------------
// Description  : Set Y Mapping M1/M2 Gain Precision
// Input Value  : EnumSelRegion and EnumYMappingGainPrecision
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingSetRGBCoefficient(EnumSelRegion enumSelRegion, WORD usRcoef, WORD usGcoef, WORD usBcoef)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetByte(P9_E6_Y_MAPPING_RGBTOY_R_COEF_H_M1 + usPage, (usRcoef >> 8) & 0x0F);
    ScalerSetByte(P9_E7_Y_MAPPING_RGBTOY_R_COEF_L_M1 + usPage, usRcoef & 0xFF);
    ScalerSetByte(P9_E8_Y_MAPPING_RGBTOY_G_COEF_H_M1 + usPage, (usGcoef >> 8) & 0x0F);
    ScalerSetByte(P9_E9_Y_MAPPING_RGBTOY_G_COEF_L_M1 + usPage, usGcoef & 0xFF);
    ScalerSetByte(P9_EA_Y_MAPPING_RGBTOY_B_COEF_H_M1 + usPage, (usBcoef >> 8) & 0x0F);
    ScalerSetByte(P9_EB_Y_MAPPING_RGBTOY_B_COEF_L_M1 + usPage, usBcoef & 0xFF);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        ScalerSetByte(P49_E6_Y_MAPPING_RGBTOY_R_COEF_H_M2, (usRcoef >> 8) & 0x0F);
        ScalerSetByte(P49_E7_Y_MAPPING_RGBTOY_R_COEF_L_M2, usRcoef & 0xFF);
        ScalerSetByte(P49_E8_Y_MAPPING_RGBTOY_G_COEF_H_M2, (usGcoef >> 8) & 0x0F);
        ScalerSetByte(P49_E9_Y_MAPPING_RGBTOY_G_COEF_L_M2, usGcoef & 0xFF);
        ScalerSetByte(P49_EA_Y_MAPPING_RGBTOY_B_COEF_H_M2, (usBcoef >> 8) & 0x0F);
        ScalerSetByte(P49_EB_Y_MAPPING_RGBTOY_B_COEF_L_M2, usBcoef & 0xFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Y Mapping M1/M2 Soft Clamp Enable/Disable
// Input Value  : EnumSelRegion and EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingSoftClampEnable(EnumSelRegion enumSelRegion, EnumFunctionOnOFF enumOn)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT2, _BIT2);
    }
    else
    {
        ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT2, 0x00);
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        if(enumOn == _FUNCTION_ON)
        {
            ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT2, _BIT2);
        }
        else
        {
            ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT2, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set Y Mapping M1/M2 Soft Clamp Parameter
// Input Value  : EnumSelRegion and ucYMappingSoftClampParam
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingSetSoftClampParam(EnumSelRegion enumSelRegion, BYTE ucYMappingSoftClampParam)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetByte(P9_EC_Y_MAPPING_SOFT_CLAMP_PARA_M1 + usPage, ucYMappingSoftClampParam);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        ScalerSetByte(P49_EC_Y_MAPPING_SOFT_CLAMP_PARA_M2, ucYMappingSoftClampParam);
    }
#endif
}

//--------------------------------------------------
// Description  : Set Y Mapping M1/M2 Offset
// Input Value  : EnumSelRegion and usYMappingOffset
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingSetOffset(EnumSelRegion enumSelRegion, WORD usYMappingOffset)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetByte(P9_E4_Y_MAPPING_GAIN_OFFSET_H_M1 + usPage, (usYMappingOffset >> 8) & 0x3F);
    ScalerSetByte(P9_E5_Y_MAPPING_GAIN_OFFSET_L_M1 + usPage, usYMappingOffset & 0xFF);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        ScalerSetByte(P49_E4_Y_MAPPING_GAIN_OFFSET_H_M2, (usYMappingOffset >> 8) & 0x3F);
        ScalerSetByte(P49_E5_Y_MAPPING_GAIN_OFFSET_L_M2, usYMappingOffset & 0xFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Set YMapping Gain LUT
// Input Value  : EnumSelRegion ,pucYMappingGainLUT ,usYMappingGainLUTSize, ucBankNum and bBurstWriteFrom
// Output Value : None
//--------------------------------------------------
bit ScalerColorYMappingLoadGainTable(EnumSelRegion enumSelRegion, BYTE *pucYMappingGainLUT, WORD usYMappingGainLUTSize, BYTE ucBankNum, bit bBurstWriteFrom)
{
    WORD usPage = _REG_MAIN1_PAGE;
    bit bLoadGainTableStatus = _SUCCESS;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT6, _BIT6);
    ScalerBurstWrite(pucYMappingGainLUT, usYMappingGainLUTSize, ucBankNum, P9_E3_Y_MAPPING_GAIN_ACCESS_PORT_M1 + usPage, _BURSTWRITE_DATA_COMMON, bBurstWriteFrom);
    ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT6, 0x00);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT6, _BIT6);
        ScalerBurstWrite(pucYMappingGainLUT, usYMappingGainLUTSize, ucBankNum, P49_E3_Y_MAPPING_GAIN_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, bBurstWriteFrom);
        ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT6, 0x00);
    }
#endif

    return bLoadGainTableStatus;
}

//--------------------------------------------------
// Description  : Y Mapping M1/M2 Double Buffer Apply, update Y Mapping Gain and offset
// Input Value  : EnumSelRegion, EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingDBApply(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    WORD usPage = _REG_MAIN1_PAGE;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT0, _BIT0);

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        if(ScalerTimerPollingFlagProc(_YM_DOUBLE_BUFFER_WAIT_TIME, P9_E0_Y_MAPPING_CTRL_M1 + usPage, _BIT0, 0) == _FALSE)
        {
            // Disable Apply Bit when Ymapping double buffer timeout
            ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1 + usPage, ~_BIT0, 0x00);
        }
    }

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    if(enumSelRegion == _FULL_REGION)
    {
        ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT0, _BIT0);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            if(ScalerTimerPollingFlagProc(_YM_DOUBLE_BUFFER_WAIT_TIME, P49_E0_Y_MAPPING_CTRL_M2, _BIT0, 0) == _FALSE)
            {
                // Disable Apply Bit when Ymapping double buffer timeout
                ScalerSetBit(P49_E0_Y_MAPPING_CTRL_M2, ~_BIT0, 0x00);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Y Mapping Double Buffer Enable/Disable
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorYMappingDBEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1, ~_BIT1, _BIT1);
    }
    else
    {
        ScalerSetBit(P9_E0_Y_MAPPING_CTRL_M1, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get Y Mapping Double Buffer Enable/Disable status
// Input Value  : None
// Output Value : EnumFunctionOnOFF
//--------------------------------------------------
EnumFunctionOnOFF ScalerColorYMappingGetDBStatus(void)
{
    if(ScalerGetBit(P9_E0_Y_MAPPING_CTRL_M1, _BIT1) == _BIT1)
    {
        return _FUNCTION_ON;
    }
    return _FUNCTION_OFF;
}
#endif

