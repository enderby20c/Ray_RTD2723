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
// ID Code      : ScalerColorBrightness.c
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
#if(_COLOR_IP_BRIGHTNESS == _ON)
//--------------------------------------------------
// Description  : Adjust Brightness
// Input Value  : EnumBriConCoefTypem, Coefficient
//                10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void ScalerColorBrightnessAdjust(EnumSelRegion enumSelRegion, WORD *pusData)
{
    WORD usPage = _REG_MAIN1_PAGE;

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetDDomainAfterBlendingRegisterPage(enumSelRegion);
#else
    if(enumSelRegion == _DEMO_INSIDE)
    {
        usPage = _REG_MAIN2_PAGE;
    }
#endif

    switch(usPage)
    {
        case _REG_MAIN1_PAGE:
            ScalerColorBrightnessCoefAdjust(_BRIGHTNESS_COEF_A, pusData);

            if(enumSelRegion == _FULL_REGION)
            {
                ScalerColorBrightnessCoefAdjust(_BRIGHTNESS_COEF_B, pusData);
            }

            break;

        case _REG_MAIN2_PAGE:
            ScalerColorBrightnessCoefAdjust(_BRIGHTNESS_COEF_B, pusData);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Brightness
// Input Value  : EnumBriCoefType, enumBriCoefType
//                10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void ScalerColorBrightnessCoefAdjust(EnumBriCoefType enumBriCoefType, WORD *pusData)
{
    switch(enumBriCoefType)
    {
        case _BRIGHTNESS_COEF_A:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_00_BRI_RED_COE_SETA_H, (pusData[0] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_01_BRI_GRN_COE_SETA_H, (pusData[1] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_02_BRI_BLU_COE_SETA_H, (pusData[2] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_20_BRI_COE_SETA_L, ((pusData[0] & 0x0003) << 6) | ((pusData[1] & 0x0003) << 4) | ((pusData[2] & 0x0003) << 2));
            break;

        case _BRIGHTNESS_COEF_B:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_06_BRI_RED_COE_SETB_H, (pusData[0] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_07_BRI_GRN_COE_SETB_H, (pusData[1] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_08_BRI_BLU_COE_SETB_H, (pusData[2] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_23_BRI_COE_SETB_L, ((pusData[0] & 0x0003) << 6) | ((pusData[1] & 0x0003) << 4) | ((pusData[2] & 0x0003) << 2));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Brightness function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorBrightnessEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
#if(_HW_BRI_ENABLE_BIT_ADDR_TYPE == _BRI_EN_ADDR_P0_62)
        ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT0), _BIT0);
#else
        ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, ~_BIT0, _BIT0);
#endif
    }
    else
    {
#if(_HW_BRI_ENABLE_BIT_ADDR_TYPE == _BRI_EN_ADDR_P0_62)
        ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT6 | _BIT0), 0x00);
#else
        ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, ~_BIT0, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Get Brightness Setting
// Input Value  : EnumBriConCoefTypem, Coefficient
// Output Value : Brightness Setting
//--------------------------------------------------
void ScalerColorBrightnessGetSetting(EnumBriCoefType enumBriCoefType, WORD *pusData)
{
    BYTE ucTempH = 0;
#if(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
    BYTE ucTempL = 0;
#endif

    switch(enumBriCoefType)
    {
        case _BRIGHTNESS_COEF_A:
            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_00_BRI_RED_COE_SETA_H);
#if(_HW_BRI_TYPE == _BRI_GEN_0_8BIT)
            pusData[0] = ucTempH;
#elif(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
            ucTempL = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_20_BRI_COE_SETA_L);
            pusData[0] = (((WORD)ucTempH) << 2) | ((ucTempL & 0xC0) >> 6);
#endif
            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_01_BRI_GRN_COE_SETA_H);
#if(_HW_BRI_TYPE == _BRI_GEN_0_8BIT)
            pusData[1] = ucTempH;
#elif(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
            pusData[1] = (((WORD)ucTempH) << 2) | ((ucTempL & 0x30) >> 4);
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_02_BRI_BLU_COE_SETA_H);
#if(_HW_BRI_TYPE == _BRI_GEN_0_8BIT)
            pusData[2] = ucTempH;
#elif(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
            pusData[2] = (((WORD)ucTempH) << 2) | ((ucTempL & 0x0C) >> 2);
#endif
            break;

        case _BRIGHTNESS_COEF_B:
            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_06_BRI_RED_COE_SETB_H);
#if(_HW_BRI_TYPE == _BRI_GEN_0_8BIT)
            pusData[0] = ucTempH;
#elif(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
            ucTempL = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_23_BRI_COE_SETB_L);
            pusData[0] = (((WORD)ucTempH) << 2) | ((ucTempL & 0xC0) >> 6);
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_07_BRI_GRN_COE_SETB_H);
#if(_HW_BRI_TYPE == _BRI_GEN_0_8BIT)
            pusData[1] = ucTempH;
#elif(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
            pusData[1] = (((WORD)ucTempH) << 2) | ((ucTempL & 0x30) >> 4);
#endif

            ucTempH = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_08_BRI_BLU_COE_SETB_H);
#if(_HW_BRI_TYPE == _BRI_GEN_0_8BIT)
            pusData[2] = ucTempH;
#elif(_HW_BRI_TYPE == _BRI_GEN_1_10BIT)
            pusData[2] = (((WORD)ucTempH) << 2) | ((ucTempL & 0x0C) >> 2);
#endif
            break;

        default:
            break;
    }
}
#endif  // End of #if(_COLOR_IP_BRIGHTNESS == _ON)

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
//--------------------------------------------------
// Description  : Adjust CtsBri Region Enable
// Input Value  : enumSelRegion --> OSD Select region
//                enumDBApply
//                bOn --> Enable/Disable the CtsBri of the OSD select region
// Output Value : None
//--------------------------------------------------
void ScalerColorBrightnessContrastHLWRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    EnumHLWType enumHLWType = ScalerRegionGetSelectRegionHLWArea(enumSelRegion);
    BYTE ucHlwSetting = ScalerGetDataPortSingleByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_28_CTS_BRI_HLW_CONTROL);
    BYTE ucMask = 0;

    switch(enumHLWType)
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

    ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_28_CTS_BRI_HLW_CONTROL, ucHlwSetting);

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust SetA and SetB of Different region
// Input Value  : enumSelRegion,  enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorBrightnessContrastHLWSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    // SetA/B settings will still exist when _HW_D_DOMAIN_RGN_COUNT_MAX = 1
    ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_29_CTS_BRI_HLW_SETSEL, ~(_BIT3 | _BIT2), ((BYTE)enumSetSel << 2));
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif

