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
// ID Code      : ScalerColorIAPS.c
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
#if(_COLOR_IP_IAPS == _ON)
//--------------------------------------------------
// Description  : Enable/Disable IAPS Gain Function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorIAPSGainEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // Enable Soft Clamp and Iaps Gain
        ScalerSetBit(P7_E0_IAPS_GAIN_CTRL_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerSetBit(P7_E0_IAPS_GAIN_CTRL_M1 + _REG_MAIN2_PAGE, ~(_BIT1), _BIT1);
#endif

        // Enable Double Buffer
        ScalerSetBit(P7_E4_IAPS_GAIN_DB_CTRL_M1, ~(_BIT0), _BIT0);
    }
    else
    {
        ScalerSetBit(P7_E0_IAPS_GAIN_CTRL_M1, ~(_BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IAPS Gain Highlight Window Active Region
// Input Value  : enumSelRegion --> OSD Select region
//                enumDBApply
//                bOn --> Enable/Disable the IAPS Gain of the OSD select region
// Output Value : None
//--------------------------------------------------
void ScalerColorIAPSGainRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    BYTE ucHlwSetting = 0;
    BYTE ucMask = 0;

    if(enumSelRegion == _NON_REGION)
    {
        return;
    }

    ucHlwSetting = ScalerGetByte(P7_E0_IAPS_GAIN_CTRL_M1);

    switch(ScalerRegionGetSelectRegionHLWArea(enumSelRegion))
    {
        case _HLW_INSIDE_WINDOW:
            ucMask = _BIT5;
            break;

        case _HLW_OUTSIDE_WINDOW:
            ucMask = _BIT4;
            break;

        case _HLW_FULL_WINDOW:
        default:
            ucMask = (_BIT5 | _BIT4);
            break;
    }

    if(bOn == _ON)
    {
        ucHlwSetting &= ~ucMask;
    }
    else
    {
        ucHlwSetting |= ucMask;
    }

    ScalerSetByte(P7_E0_IAPS_GAIN_CTRL_M1, ucHlwSetting);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Adjust SetA and SetB of Different region
// Input Value  : enumSelRegion,  enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorIAPSGainSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerSetBit(P7_E0_IAPS_GAIN_CTRL_M1, ~(_BIT3 | _BIT2), ((BYTE)enumSetSel << 2));
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get IAPS HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel ScalerColorIAPSGainGetEffectiveRegion(void)
{
    return (EnumHLWSetSel)(ScalerGetBit(P7_E0_IAPS_GAIN_CTRL_M1, (_BIT3 | _BIT2)) >> 2);
}
#endif

//--------------------------------------------------
// Description  : Adjust IAPS Gain Soft clamp parameter
// Input Value  : ucSoftClampFac, when ucSoftClampFac = 0, SoftClamp is disabled
// Output Value : None
//--------------------------------------------------
void ScalerColorIAPSGainSoftClampAdjust(EnumSelRegion enumSelRegion, BYTE ucSoftClampFac)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetByte(P7_E3_SOFT_CLAMP_M1 + usPage, ucSoftClampFac);
}

//--------------------------------------------------
// Description  : Adjust IAPS Gain Value
// Input Value  : usGainValue, 15 bit input,
//                0 (0000h) ~ 1(2000h) ~  4(7FFFh)
// Output Value : None
//--------------------------------------------------
void ScalerColorIAPSGainValueAdjust(EnumSelRegion enumSelRegion, WORD usGainValue)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#endif

    ScalerSetByte(P7_E1_GAIN_VALUE1_M1 + usPage, (BYTE)(usGainValue >> 7));
    ScalerSetByte(P7_E2_GAIN_VALUE0_M1 + usPage, (BYTE)(usGainValue & 0x007F) << 1);

    // Set DoubleBuffer Not Ready
    ScalerSetBit(P7_E4_IAPS_GAIN_DB_CTRL_M1, ~_BIT1, _BIT1);
}
#endif

