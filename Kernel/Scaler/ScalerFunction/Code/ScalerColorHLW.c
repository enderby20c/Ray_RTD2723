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
// ID Code      : ScalerColorHLW.c
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
#if(_COLOR_IP_HL_WIN == _ON)
//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : enumSelRegion, usHPos, usHWidth, usVPos, usVHeight, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply)
{
    ScalerColorHLWDDomainAdjust(usHPos, usHWidth, usVPos, usVHeight);

#if(_COLOR_IP_LSR == _ON)
    ScalerColorLSRHLWAdjust(usHPos, usHWidth, usVPos, usVHeight);
#endif

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Enable/Disable IDLTI, LSR, Ddomain HLW,
// Input Value  : enumOn, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWEnable(EnumFunctionOnOFF enumOn, EnumDBApply enumDBApply)
{
    ScalerColorHLWDDomainEnable(enumOn);

#if(_ULTRA_VIVID_FUNCTION == _ON)
    ScalerColorLSRHLWEnable(enumOn);
#endif

    // When Highlight Window window_en(0x0061_0C[0]) is disable,
    // whole region belongs to outside, and win_ip_set & win_ip_set_sel
    // will be still effective on outside region.
    // sel & setsel settings should be returned to default value, in order to align for Scaler3 FW.
    // Default set: use on full region (2b'00)
    // Default set_sel: SetA for inside/outside (2b'00)
    if(enumOn == _FUNCTION_OFF)
    {
        // Reset HLW Region Setting
        ScalerColorHLWDDomainAdjustRegister(0x0000, 0x0000, 0x0000, 0x0000);
        ScalerColorHLWBorderEnable(_FALSE, _FALSE, _FALSE, _FALSE, _DB_APPLY_NONE);
        ScalerColorHLWBorderAdjust(0x00, 0x00, 0x00, 0x00, _DB_APPLY_NONE);

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
        ScalerColorLocalContrastRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
        // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_DCC == _ON)
        ScalerColorDCCRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorDCCSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_DCR == _ON)
        ScalerColorDCRSetMeasureRegion(_FULL_REGION, _DB_APPLY_NONE);
        // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_ICM == _ON)
        ScalerColorICMSCMRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorICMSCMSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
        ScalerColorBrightnessContrastHLWRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
        ScalerColorBrightnessContrastHLWSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif

#if(_COLOR_IP_IAPS == _ON)
        ScalerColorIAPSGainRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorIAPSGainSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
        ScalerColor3DGammaRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
        // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
        ScalerColorPCMRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorPCMSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_SRGB == _ON)
        ScalerColorSRGBRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorSRGBSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
        ScalerColorPostGammaRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorPostGammaSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
        ScalerColorGammaRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorGammaSetEffectiveRegion(_HLW_ALLSETA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
        ScalerColorPanelUniformityRegionEnable(_FULL_REGION, _DB_APPLY_NONE, _ON);
        // Only one set, no need to reset set_sel setting.
#endif

#if(_OD_FUNCTION == _ON)
        ScalerODHLWinSetting(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
        // Only one set, no need to reset set_sel setting.
#endif
    }

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_ALL, enumDBApply);
}

//--------------------------------------------------
// Description  : Get HLW Position , Set HLW Position
// Input Value  : enumSelRegion, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWSetting(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    // by enumSelRegion case, get R1's Background or R2's Background or Active size from reference reg
    // becase Background/Active and HLW's reference position aren't the same
    // need to use R1 Background's H/V start to change reference position
    // full region is equal to 1p mode
    // demo mode Movie HLW no deal

    WORD usRefHStart = 0;
    WORD usRefHEnd = 0;
    WORD usRefVStart = 0;
    WORD usHStart = 0;
    WORD usHEnd = 0;
    WORD usVStart = 0;
    WORD usVEnd = 0;
    WORD usCalHStart = 0;
    WORD usCalHEnd = 0;
    WORD usCalVStart = 0;
    WORD usCalVEnd = 0;

    usRefHStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START);
    usRefVStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);
    usRefHEnd = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END);

    // Get R1 Background Size
    usHEnd = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END);
    usVEnd = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END);

    usHStart = usHStart;
    usVStart = usVStart;
    usRefHEnd = usRefHEnd;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        if(((ScalerDDomainBackgroundCheck(_2P_PIP_EAGLE_SIGHT_MAIN) == _ENABLE) &&
            (ScalerDDomainBackgroundCheck(_2P_PIP_EAGLE_SIGHT_SUB) == _ENABLE)) ||
           (ScalerDDomainGetR2DenEnable() == _DISABLE))
        {
            enumSelRegion = _1P_NORMAL_REGION;
        }
    }
#endif

    switch(enumSelRegion)
    {
        case _DEMO_OUTSIDE:
        case _DEMO_INSIDE:
        case _NON_REGION:
            return;

        case _1P_NORMAL_REGION:
            usCalHStart = usHEnd - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart + 1;
            usCalVStart = 0;
            usCalVEnd = usVEnd - usRefVStart;
            break;

        case _FULL_REGION:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
            {
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                // Get R2 Background Size
                usHStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_START);
                usHEnd = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_END);
                usVStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START);
                usVEnd = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_END);
#endif
                usCalHStart = usHStart - usRefHStart;
                usCalHEnd = usHEnd - usRefHStart;
                usCalVStart = usVStart - usRefVStart;
                usCalVEnd = usVEnd - usRefVStart;
            }
            else
#endif
            {
                usCalHStart = usHEnd - usRefHStart;
                usCalHEnd = usHEnd - usRefHStart + 1;
                usCalVStart = 0;
                usCalVEnd = usVEnd - usRefVStart;
            }
            break;

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
        case _2P_PBP_TB_B:
            usCalHStart = 0;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = usVEnd - usRefVStart;
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
        case _4P_LT_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = ((usHEnd - usRefHStart) >> 1);
            usCalVStart = 0;
            usCalVEnd = ((usVEnd - usRefVStart) >> 1);
            break;

        case _4P_LB:
        case _4P_LB_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = ((usHEnd - usRefHStart) >> 1);
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = (usVEnd - usRefVStart);
            break;

        case _4P_RT:
        case _4P_RT_OUTSIDE:
            usCalHStart = ((usHEnd - usRefHStart) >> 1);
            usCalHEnd = (usHEnd - usRefHStart);
            usCalVStart = 0;
            usCalVEnd = ((usVEnd - usRefVStart) >> 1);
            break;

        case _4P_RB:
        case _4P_RB_OUTSIDE:
            usCalHStart = ((usHEnd - usRefHStart) >> 1);
            usCalHEnd = (usHEnd - usRefHStart);
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = (usVEnd - usRefVStart);
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
        case _3P_SKEW_T_M_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = (usHEnd - usRefHStart);
            usCalVStart = 0;
            usCalVEnd = ((usVEnd - usRefVStart) >> 1);
            break;

        case _3P_SKEW_T_L:
        case _3P_SKEW_T_L_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = ((usHEnd - usRefHStart) >> 1);
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = (usVEnd - usRefVStart);
            break;

        case _3P_SKEW_B_M:
        case _3P_SKEW_B_M_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = (usHEnd - usRefHStart);
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = (usVEnd - usRefVStart);
            break;

        case _3P_SKEW_B_L:
        case _3P_SKEW_B_L_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = ((usHEnd - usRefHStart) >> 1);
            usCalVStart = 0;
            usCalVEnd = ((usVEnd - usRefVStart) >> 1);
            break;
#endif

        default:
            break;
    }

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
    // Get R2 Background Size
    usHStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_START);
    usHEnd = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_END);
    usVStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START);
    usVEnd = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_END);

    switch(enumSelRegion)
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
        case _2P_PIP_SUB:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
        case _2P_PIP_EAGLE_SIGHT_SUB:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_L_LARGE_R:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;

        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                usCalHStart = usHEnd - usRefHStart;
                usCalHEnd = usRefHEnd - usHStart;
                usCalVStart = usVStart - usRefVStart;
                usCalVEnd = usVEnd - usRefVStart;
            }
            else
            {
                // RL6829 EO, RL6978
                usCalHStart = usHStart - usRefHStart;
                usCalHEnd = usHEnd - usRefHStart;
                usCalVStart = usVStart - usRefVStart;
                usCalVEnd = usVEnd - usRefVStart;
            }
            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_B_R:
        case _3P_SKEW_B_R_OUTSIDE:
        case _3P_SKEW_T_R:
        case _3P_SKEW_T_R_OUTSIDE:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L:
        case _3P_FLAG_L_OUTSIDE:
            usCalHEnd = usHStart - usRefHStart;
            usCalHStart = 0;
            usCalVEnd = usVEnd - usRefVStart;
            usCalVStart = 0;
            break;

        case _3P_FLAG_M:
        case _3P_FLAG_M_OUTSIDE:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_R_T:
        case _3P_SKEW_R_T_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = usHStart - usRefHStart;
            usCalVStart = 0;
            usCalVEnd = ((usVEnd - usRefVStart) >> 1);
            break;

        case _3P_SKEW_R_B:
        case _3P_SKEW_R_B_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = usHStart - usRefHStart;
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = (usVEnd - usRefVStart);
            break;

        case _3P_SKEW_R_M:
        case _3P_SKEW_R_M_OUTSIDE:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;

        case _3P_SKEW_L_T:
        case _3P_SKEW_L_T_OUTSIDE:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = 0;
            usCalVEnd = ((usVEnd - usRefVStart) >> 1);
            break;

        case _3P_SKEW_L_M:
        case _3P_SKEW_L_M_OUTSIDE:
            usCalHStart = 0;
            usCalHEnd = usHStart - usRefHStart;
            usCalVStart = 0;
            usCalVEnd = (usVEnd - usRefVStart);
            break;

        case _3P_SKEW_L_B:
        case _3P_SKEW_L_B_OUTSIDE:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = ((usVEnd - usRefVStart) >> 1);
            usCalVEnd = (usVEnd - usRefVStart);
            break;
#endif

        default:
            break;
    }
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
    // Get R3 Background Size
    usHStart = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_H_START);
    usHEnd = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_H_END);
    usVStart = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_V_START);
    usVEnd = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_V_END);

    switch(enumSelRegion)
    {
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_R:
        case _3P_FLAG_R_OUTSIDE:
            usCalHStart = usHStart - usRefHStart;
            usCalHEnd = usHEnd - usRefHStart;
            usCalVStart = usVStart - usRefVStart;
            usCalVEnd = usVEnd - usRefVStart;
            break;
#endif

        default:
            break;
    }
#endif

    // write position
    ScalerColorHLWDDomainAdjust(usCalHStart, usCalHEnd - usCalHStart, usCalVStart, usCalVEnd - usCalVStart);
    ScalerColorHLWDDomainEnable(_FUNCTION_ON);

#if(_COLOR_IP_LSR == _ON)
    ScalerColorLSRHLWEnable(_FUNCTION_OFF);
#endif

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    if((usHWidth == 0) || (usVHeight == 0))
    {
        return;
    }

    ScalerColorHLWDDomainAdjustRegister(usHPos, usHWidth, usVPos, usVHeight);
}

//--------------------------------------------------
// Description  : Enable/Disable Ddomain HLW,
// Input Value  : EnumFunctionOnOFF
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWDDomainEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // Ddomain one HLW
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~_BIT0, _BIT0);
    }
    else // bOn == _OFF || bOn == _CLOCK_GATED
    {
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust HLW Border Width and Color
// Input Value  : ucBorderWidth, ucRed, ucGreen, ucBlue, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    // set HLW's Border
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_08_HLW_BORDER_WIDTH, (ucBorderWidth & 0x1F));

    // border color is 10bits,  here still use 8bits
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_09_HLW_BORDER_RED, (ucRed & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0A_HLW_BORDER_GRN, (ucGreen & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0B_HLW_BORDER_BLU, (ucBlue & 0xFF));

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust HLW Border Enable
// Input Value  : bTopBorderEn, bBottomBorderEn, bLeftBorderEn, bRightBorderEn, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply)
{
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((BYTE)(!bLeftBorderEn) << 7) | ((BYTE)(!bRightBorderEn) << 6) | ((BYTE)(!bTopBorderEn) << 5) | ((BYTE)(!bBottomBorderEn) << 4));

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : HLW Region Register Adjust
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWDDomainAdjustRegister(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_00_HLW_HOR_START_H, (BYTE)((usHPos >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_01_HLW_HOR_START_L, (BYTE)(usHPos & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_02_HLW_HOR_END_H, (BYTE)(((usHPos + usHWidth) >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_03_HLW_HOR_END_L, (BYTE)((usHPos + usHWidth) & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_04_HLW_VER_START_H, (BYTE)((usVPos >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_05_HLW_VER_START_L, (BYTE)(usVPos & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_06_HLW_VER_END_H, (BYTE)(((usVPos + usVHeight) >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_07_HLW_VER_END_L, (BYTE)((usVPos + usVHeight) & 0xFF));
}

//--------------------------------------------------
// Description  : Return Demo Mode Support or Not
// Input Value  : none
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerColorHLWSupportCheck(void)
{
    // 3P & 4P mode can not enable Demo mode
    if(ScalerRegionGetMaxRegionCount() >= 3)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

