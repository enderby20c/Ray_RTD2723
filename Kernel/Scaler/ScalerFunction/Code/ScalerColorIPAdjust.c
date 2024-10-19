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
// ID Code      : ScalerColorIPAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_HDR10_SUPPORT == _ON)
WORD code tusHDR10_IG_ADDRESS_INDEX[] =
{
    _OGC_HDR10_IG_540_NOR_ADDRESS,
    _OGC_HDR10_IG_540_DARK_ADDRESS,
    _OGC_HDR10_IG_1200_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_DARK_ADDRESS,
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS, // not used
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS, // not used
#endif
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS, // PANEL MAX PEAK LV
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_NOR_ADDRESS, // PANEL MAX FRAME AVERAGE LV
    _OGC_HDR10_IG_NOTM_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS, // PANEL MAX USER DEFINE LV
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS,
};

#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
WORD code tusHDR10_IG_FIXED_POINT_ADDRESS_INDEX[] =
{
    _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_540_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS, // PANEL MAX PEAK LV
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_NOR_ADDRESS, // PANEL MAX FRAME AVERAGE LV
    _OGC_HDR10_IG_NOTM_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS, // PANEL MAX USER DEFINE LV
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS,
};
#endif

#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
WORD code tusHDR10_IG_USER_DEFINE_FIXED_POINT_ADDRESS_INDEX[] =
{
    _OGC_HDR10_IG_540_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_540_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_1200_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS, // PANEL MAX PEAK LV
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_NOR_ADDRESS, // PANEL MAX FRAME AVERAGE LV
    _OGC_HDR10_IG_NOTM_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS, // PANEL MAX USER DEFINE LV
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS,
};
#endif

WORD code tusHDR10_SRGB_ADDRESS_INDEX[] =
{
    _OCC_HDR10_SRGB_MATRIX_ADDRESS,
    _OCC_HDR10_ADOBE_MATRIX_ADDRESS,
    _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS,
    _OCC_HDR10_BT2020_MATRIX_ADDRESS,
};

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
WORD code tusHDR10_YM_RGB_COEFF_INDEX[][3] =
{
    {871, 2929, 296, }, // SRGB
    {1218, 2570, 308, }, // ADOBE
    {938, 2833, 325, }, // DCIP3_D65
    {1076, 2777, 243, }, // BT2020
};
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
WORD code tusHDR10_SBTM_SRGB_ADDRESS_INDEX[] =
{
    _OCC_HDR10_BT2020_MATRIX_ADDRESS, // User Define
    _OCC_HDR10_SRGB_MATRIX_ADDRESS,
    _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS,
    _OCC_HDR10_BT2020_MATRIX_ADDRESS,
};
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
WORD code tusFREESYNC_II_IG_ADDRESS_INDEX[] =
{
    _FREESYNC_II_IG_SRGB_ADDRESS,
    _FREESYNC_II_IG_BT709_ADDRESS,
    _FREESYNC_II_IG_GAMMA22_ADDRESS,
    _FREESYNC_II_IG_GAMMA26_ADDRESS,
    _FREESYNC_II_IG_PQINTERIM_ADDRESS,
};
#endif

#if(_OGC_FUNCTION == _ON)
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
WORD code tusDIMMING_GAMMA_ADDRESS_INDEX[] =
{
    _DIMMING_OGC_GAMMA1_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _DIMMING_OGC_GAMMA2_ADDRESS,
#endif
#if(_OGC_TOTAL_GAMMA > 2)
    _DIMMING_OGC_GAMMA3_ADDRESS,
#endif
#if(_OGC_TOTAL_GAMMA > 3)
    _DIMMING_OGC_GAMMA4_ADDRESS,
#endif
#if(_OGC_TOTAL_GAMMA > 4)
    _DIMMING_OGC_GAMMA5_ADDRESS,
#endif
#if(_OGC_TOTAL_GAMMA > 5)
    _DIMMING_OGC_GAMMA6_ADDRESS,
#endif
};
#endif
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_HL_WIN == _ON)
//--------------------------------------------------
// Description  : HLW Adjust
// Input Value  : HLW Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPHLWAdjust(StructColorHLWSetting *pstHLWData, EnumDBApply enumDBApply)
{
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    SET_ADVANCED_HDR10_PCM_HLW_MODE(pstHLWData->stHLWSetting.enumHLWMode);
#endif

    switch(pstHLWData->stHLWSetting.enumHLWMode)
    {
        case _HLW_KERNEL:
            ScalerColorHLWBorderAdjust(pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucBorderWidth, pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWRed, pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWGreen, pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWBlue, _DB_APPLY_NONE);
            ScalerColorHLWBorderEnable(pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1TopBorderEn, pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1BottomBorderEn, pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1LeftBorderEn, pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1RightBorderEn, _DB_APPLY_NONE);
            ScalerColorHLWSetting(pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.enumHLWKernelRegion, enumDBApply);
            break;

        case _HLW_USER:
            ScalerColorHLWBorderAdjust(pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucBorderWidth, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucHLWRed, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucHLWGreen, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucHLWBlue, _DB_APPLY_NONE);
            ScalerColorHLWBorderEnable(pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1TopBorderEn, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1BottomBorderEn, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1LeftBorderEn, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1RightBorderEn, _DB_APPLY_NONE);
            ScalerColorHLWAdjust(pstHLWData->stHLWSetting.unHLWData.stHLWUserData.usHLWinHPos, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.usHLWinHWidth, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.usHLWinVPos, pstHLWData->stHLWSetting.unHLWData.stHLWUserData.usHLWinVHeight, enumDBApply);
            break;

        default:
            break;
    }
}
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
//--------------------------------------------------
// Description  : Border Window Adjust
// Input Value  : Border Window Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPBorderWindowAdjust(StructColorBorderWindowSetting *pstBorderWindowData, EnumDBApply enumDBApply)
{
    ScalerColorBorderAdjust(_BORDER_WIN1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWidth, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWinowRed, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWinowGreen, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWinowBlue, _DB_APPLY_NONE);
    ScalerColorBorderAdjust(_BORDER_WIN2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWidth, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWinowRed, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWinowGreen, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.ucBorderWinowBlue, _DB_APPLY_NONE);

    ScalerColorBorderPositionAdjust(_BORDER_WIN1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usHStart_Win1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usHWidth_Win1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usVStart_Win1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usVHeight_Win1, _DB_APPLY_NONE);
    ScalerColorBorderEnable(_BORDER_WIN1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1, _DB_APPLY_NONE);
    ScalerColorBorderPositionAdjust(_BORDER_WIN2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usHStart_Win2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usHWidth_Win2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usVStart_Win2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.usVHeight_Win2, _DB_APPLY_NONE);
    ScalerColorBorderEnable(_BORDER_WIN2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2, pstBorderWindowData->stBorderWindowSetting.unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2, enumDBApply);
}
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
//--------------------------------------------------
// Description  : LSR & DSHP Adjust
// Input Value  : EnumSelRegion, StructUnionUltraVividSetting
// Output Value : None
//--------------------------------------------------
void ScalerColorIPUltraVividAdjust(EnumSelRegion enumSelRegion, StructColorUltraVividSetting *pstUltraVividSetting)
{
    switch(pstUltraVividSetting->stUltraVividSetting.enumUltraVividMode)
    {
        case _ULTRAVIVID_OFF:
        default:
            break;

        case _ULTRAVIVID_SDR:
            ScalerColorUltraVividAdjust(enumSelRegion, pstUltraVividSetting->stUltraVividSetting.unUltraVividData.stUltraVividSDRData.pucTable, pstUltraVividSetting->stUltraVividSetting.unUltraVividData.stUltraVividSDRData.ucBank);
            break;

        case _ULTRAVIVID_HDR10:
            ScalerColorUltraVividAdjust(enumSelRegion, pstUltraVividSetting->stUltraVividSetting.unUltraVividData.stUltraVividHDR10Data.pucTable, pstUltraVividSetting->stUltraVividSetting.unUltraVividData.stUltraVividHDR10Data.ucBank);
            break;

        case _ULTRAVIVID_DM:
            ScalerColorUltraVividAdjust(enumSelRegion, pstUltraVividSetting->stUltraVividSetting.unUltraVividData.stUltraVividDMData.pucTable, pstUltraVividSetting->stUltraVividSetting.unUltraVividData.stUltraVividDMData.ucBank);
            break;
    }
}
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
//--------------------------------------------------
// Description  : Sharpness Adjust
// Input Value  : Select Region ; Sharpness Setting Struct; DB Apply Type
// Output Value : None
//--------------------------------------------------
void ScalerColorIPSharpnessAdjust(EnumSelRegion enumSelRegion, StructColorSharpnessSetting *pstSharpnessSetting, EnumDBApply enumDBApply)
{
    switch(pstSharpnessSetting->stSharpnessSetting.enumSharpnessMode)
    {
        case _SHARPNESS_USER:

            switch(enumSelRegion)
            {
                case _1P_NORMAL_REGION:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _2P_PIP_MAIN:
                case _2P_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _2P_PIP_EAGLE_SIGHT_MAIN:
                case _2P_PIP_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _2P_PBP_LR_EQUAL_L:
                case _2P_PBP_LR_EQUAL_R:
                case _2P_PBP_LR_L_LARGE_L:
                case _2P_PBP_LR_L_LARGE_R:
                case _2P_PBP_LR_R_LARGE_L:
                case _2P_PBP_LR_R_LARGE_R:
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _2P_PBP_TB_T:
                case _2P_PBP_TB_B:
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _3P_SKEW_R_B:
                case _3P_SKEW_R_M:
                case _3P_SKEW_R_T:
                case _3P_SKEW_L_B:
                case _3P_SKEW_L_M:
                case _3P_SKEW_L_T:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _3P_FLAG_L:
                case _3P_FLAG_M:
                case _3P_FLAG_R:
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _3P_SKEW_T_M:
                case _3P_SKEW_T_L:
                case _3P_SKEW_T_R:
                case _3P_SKEW_B_M:
                case _3P_SKEW_B_L:
                case _3P_SKEW_B_R:
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                case _4P_LT:
                case _4P_LB:
                case _4P_RT:
                case _4P_RB:
#endif
                    ScalerScalingSetScalingCoef(enumSelRegion, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);

                    break;
#if(_4P_DISPLAY_SUPPORT == _ON)
                case _4P_LT_OUTSIDE:
                case _4P_LB_OUTSIDE:
                case _4P_RT_OUTSIDE:
                case _4P_RB_OUTSIDE:

                    if(enumSelRegion != _4P_LT_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_4P_LT, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _4P_LB_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_4P_LB, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _4P_RT_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_4P_RT, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _4P_RB_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_4P_RB, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }
                    break;
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _3P_SKEW_R_B_OUTSIDE:
                case _3P_SKEW_R_M_OUTSIDE:
                case _3P_SKEW_R_T_OUTSIDE:

                    if(enumSelRegion != _3P_SKEW_R_B_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_R_B, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_R_M_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_R_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_R_T_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_R_T, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }
                    break;

                case _3P_SKEW_L_B_OUTSIDE:
                case _3P_SKEW_L_M_OUTSIDE:
                case _3P_SKEW_L_T_OUTSIDE:

                    if(enumSelRegion != _3P_SKEW_L_B_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_L_B, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_L_M_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_L_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_L_T_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_L_T, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }
                    break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                case _3P_SKEW_T_L_OUTSIDE:
                case _3P_SKEW_T_M_OUTSIDE:
                case _3P_SKEW_T_R_OUTSIDE:

                    if(enumSelRegion != _3P_SKEW_T_M_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_T_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_T_L_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_T_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_T_R_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_T_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }
                    break;

                case _3P_SKEW_B_L_OUTSIDE:
                case _3P_SKEW_B_M_OUTSIDE:
                case _3P_SKEW_B_R_OUTSIDE:

                    if(enumSelRegion != _3P_SKEW_B_M_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_B_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_B_L_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_B_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_SKEW_B_R_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_SKEW_B_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }
                    break;
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _3P_FLAG_L_OUTSIDE:
                case _3P_FLAG_M_OUTSIDE:
                case _3P_FLAG_R_OUTSIDE:

                    if(enumSelRegion != _3P_FLAG_L_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_FLAG_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_FLAG_M_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_FLAG_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }

                    if(enumSelRegion != _3P_FLAG_R_OUTSIDE)
                    {
                        ScalerScalingSetScalingCoef(_3P_FLAG_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                    }
                    break;
#endif
                case _FULL_REGION:
                case _DEMO_OUTSIDE:
                case _DEMO_INSIDE:

                    switch(GET_DISPLAY_MODE())
                    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_2P_PIP:
                            ScalerScalingSetScalingCoef(_2P_PIP_MAIN, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_2P_PIP_SUB, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                            ScalerScalingSetScalingCoef(_2P_PIP_EAGLE_SIGHT_MAIN, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_2P_PIP_EAGLE_SIGHT_SUB, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                            ScalerScalingSetScalingCoef(_2P_PBP_LR_EQUAL_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_2P_PBP_LR_EQUAL_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;

                        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                            ScalerScalingSetScalingCoef(_2P_PBP_LR_L_LARGE_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_2P_PBP_LR_L_LARGE_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;

                        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                            ScalerScalingSetScalingCoef(_2P_PBP_LR_R_LARGE_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_2P_PBP_LR_R_LARGE_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_2P_PBP_TB:
                            ScalerScalingSetScalingCoef(_2P_PBP_TB_T, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_2P_PBP_TB_B, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_4P:
                            ScalerScalingSetScalingCoef(_4P_LT, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_4P_LB, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_4P_RT, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_4P_RB, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_3P_FLAG:
                            ScalerScalingSetScalingCoef(_3P_FLAG_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_FLAG_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_FLAG_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_3P_SKEW_L:
                            ScalerScalingSetScalingCoef(_3P_SKEW_L_B, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_L_T, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_L_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;

                        case _DISPLAY_MODE_3P_SKEW_R:
                            ScalerScalingSetScalingCoef(_3P_SKEW_R_B, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_R_T, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_R_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_3P_SKEW_T:
                            ScalerScalingSetScalingCoef(_3P_SKEW_T_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_T_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_T_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;

                        case _DISPLAY_MODE_3P_SKEW_B:
                            ScalerScalingSetScalingCoef(_3P_SKEW_B_M, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_B_R, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            ScalerScalingSetScalingCoef(_3P_SKEW_B_L, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
#endif

                        default:
                            ScalerScalingSetScalingCoef(_1P_NORMAL_REGION, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableH, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.pucTableV, pstSharpnessSetting->stSharpnessSetting.unSharpnessData.stSharpnessUserData.ucBank);
                            break;
                    }

                    break;


                default:

                    break;
            }
            break;

        default:
            break;
    }

    ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion(enumSelRegion), enumDBApply);
}
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
//--------------------------------------------------
// Description  : ScalingDown Coef Adjust
// Input Value  : Select Region ; Sharpness Setting Struct;
// Output Value : None
//--------------------------------------------------
void ScalerColorIPScalingDownCoefAdjust(EnumSelRegion enumSelRegion, StructColorScalingDownCoefSetting *pstScalingDownCoefSetting)
{
    ScalerScalingSetFlexibleScalingDownCoef(enumSelRegion, pstScalingDownCoefSetting->stScalingDownCoefSetting.unScalingDownData.stScalingDownUserData.pucTableSD_H, pstScalingDownCoefSetting->stScalingDownCoefSetting.unScalingDownData.stScalingDownUserData.pucTableSD_V);
}
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Local Contrast Adjust
// Input Value  : Select Region ; Local Contrast Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPLocalContrastAdjust(EnumSelRegion enumSelRegion, StructColorLocalContrastSetting *pstLocalContrastData)
{
    switch(pstLocalContrastData->stLocalContrastSetting.enumLocalContrastMode)
    {
        case _LOCALCONTRAST_HDR10_USER:
            ScalerColorLocalContrastAdjust(enumSelRegion, pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, _HW_LOCAL_CONTRAST_TABLE_SIZE);

            break;

        case _LOCALCONTRAST_USER:
            ScalerColorLocalContrastAdjust(enumSelRegion, pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, _HW_LOCAL_CONTRAST_TABLE_SIZE);

            break;

#if(_SDR_PLUS_FUNCTION == _ON)
        case _LOCALCONTRAST_SDR_PLUS:
            ScalerColorLocalContrastAdjust(enumSelRegion, pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, _HW_LOCAL_CONTRAST_TABLE_SIZE);

            break;
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _LOCALCONTRAST_NIGHT_SNIPER:
            ScalerColorLocalContrastAdjust(enumSelRegion, pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastNightSniperData.pucTable, pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastNightSniperData.ucBank, _HW_LOCAL_CONTRAST_TABLE_SIZE);
            break;
#endif

        case _LOCALCONTRAST_OFF:
        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Local Contrast Adjust
// Input Value  : Select Region ; Local Contrast Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPLocalContrastTemporalAdjust(EnumSelRegion enumSelRegion, StructColorLocalContrastTemporalSetting *pstLocalContrastData, EnumLocalContrastReadYavgData enumLocalContrastReadYavgData)
{
    enumLocalContrastReadYavgData = enumLocalContrastReadYavgData;

    // Temporal Table
    ScalerColorLocalContrastAdjust(enumSelRegion, pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable, pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.ucBank, _HW_LOCAL_CONTRAST_TEMPORAL_TABLE_SIZE);

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
    // LD support ON case Need to reset Blocksc Thd & Globalsc THD
    ScalerColorLocalContrastSetSceneChangeTHD(enumSelRegion);
#endif
#endif

    // Adjust GlobalSC by panel resolution
    ScalerColorLocalContrastGlobalSceneChangeThdAdjust(enumSelRegion);

    // Adjust BlockSC by total Blknum
    ScalerColorLocalContrastBlockSceneChangeThdAdjust(enumSelRegion);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    if(ScalerColorLocalContrastGetEnableStatus(enumSelRegion) == _TRUE)
    {
        if(pstLocalContrastData->unKernelLocalContrastTemporalMode.stKernelLocalContrastTemporalMode.enumLocalContrastTemporalMode != _LOCALCONTRAST_TEMPORAL_OFF)
        {
            ScalerColorLocalContrastEnable(enumSelRegion, _LOCAL_CONTRAST_ALL_FUNCTION_ON);
        }
        else
        {
            if(enumLocalContrastReadYavgData == _LOCALCONTRAST_READYAVG_ENABLE)
            {
                ScalerColorLocalContrastEnable(enumSelRegion, _LOCAL_CONTRAST_HIST_ONLY_ON);
            }
            else
            {
                ScalerColorLocalContrastEnable(enumSelRegion, _LOCAL_CONTRAST_ALL_FUNCTION_ON);
            }
        }
    }

#endif
}
#endif

#if(_COLOR_IP_DCR == _ON)
//--------------------------------------------------
// Description  : DCR Adjust
// Input Value  : Select Region ; DCR Setting Struct
// Output Value : None
//--------------------------------------------------
void ScalerColorIPDCRAdjust(StructColorDCRSetting *pstDCRSetting)
{
    switch(pstDCRSetting->stDCRSetting.enumDCRMode)
    {
        case _DCR_USER:
            ScalerColorDCRSetMeasureRegion(pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.enumDCRUserMeasureRegion, _DB_APPLY_NO_POLLING);

#if(_HW_DCR_BIT == _DCR_10BIT)
            ScalerColorDCRAdjust(pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.usThreshold1,
                                 pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.usThreshold2,
                                 pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.enumDCRMeasureSel);
#elif(_HW_DCR_BIT == _DCR_8BIT)
            ScalerColorDCRAdjust((pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.usThreshold1 >> 2),
                                 (pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.usThreshold2 >> 2),
                                 pstDCRSetting->stDCRSetting.unDCRData.stDCRUserData.enumDCRMeasureSel);
#endif
            break;

        case _DCR_LOCAL_DIMMING:
            ScalerColorDCRSetMeasureRegion(pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.enumDCRUserMeasureRegion, _DB_APPLY_NO_POLLING);

#if(_HW_DCR_BIT == _DCR_10BIT)
            ScalerColorDCRAdjust(pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.usThreshold1,
                                 pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.usThreshold2,
                                 pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.enumDCRMeasureSel);
#elif(_HW_DCR_BIT == _DCR_8BIT)
            ScalerColorDCRAdjust((pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.usThreshold1 >> 2),
                                 (pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.usThreshold2 >> 2),
                                 pstDCRSetting->stDCRSetting.unDCRData.stDCRLocalDimmingData.enumDCRMeasureSel);
#endif
            break;

        case _DCR_GLOBAL_DIMMING:
            ScalerColorDCRSetMeasureRegion(pstDCRSetting->unKernelDCRData.stKernelDCRGlobalDimmingData.enumDCRUserMeasureRegion, _DB_APPLY_NO_POLLING);

#if(_HW_DCR_BIT == _DCR_10BIT)
            ScalerColorDCRAdjust(_GLOBAL_DIMMING_BLACK_THD,
                                 pstDCRSetting->unKernelDCRData.stKernelDCRGlobalDimmingData.usThreshold2,
                                 pstDCRSetting->unKernelDCRData.stKernelDCRGlobalDimmingData.enumDCRMeasureSel);
#elif(_HW_DCR_BIT == _DCR_8BIT)
            ScalerColorDCRAdjust((_GLOBAL_DIMMING_BLACK_THD >> 2),
                                 (pstDCRSetting->unKernelDCRData.stKernelDCRGlobalDimmingData.usThreshold2 >> 2),
                                 pstDCRSetting->unKernelDCRData.stKernelDCRGlobalDimmingData.enumDCRMeasureSel);
#endif
            break;

        default:
            break;
    }
}
#endif

#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
//--------------------------------------------------
// Description  : DCC histogram adjust
// Input Value  : DCC histogram setting
// Output Value : None
//--------------------------------------------------
void ScalerColorIPDCCHistogramAdjust(StructColorDCCHistogramSetting *pstDCCHistogramSetting)
{
    switch(pstDCCHistogramSetting->stDCCHistogramSetting.enumDCCHistogramMode)
    {
        case _DCC_HISTOGRAM_USER:
            ScalerColorDCCSetHistoMeasureRegion(pstDCCHistogramSetting->stDCCHistogramSetting.unDCCHistogramData.stDCCHistogramUserData.enumDCCMeasureRegion);
            break;

        default:
            break;
    }
}
#endif

#if(_COLOR_IP_DCC == _ON)
//--------------------------------------------------
// Description  : DCC Adjust
// Input Value  : Select Region ; DCC Setting Struct
// Output Value : None
//--------------------------------------------------
void ScalerColorIPDCCAdjust(EnumSelRegion enumSelRegion, StructColorDCCSetting *pstDCCSetting)
{
    switch(pstDCCSetting->stDCCSetting.enumDCCMode)
    {
        case _DCC_OFF:
            break;

        case _DCC_HDR10_LIGHTENHANCE:
            ScalerColorDCCAdjust(enumSelRegion, pstDCCSetting->unKernelDCCData.stKernelDCCHDR10LightEnhanceData.pucTable, pstDCCSetting->stDCCSetting.unDCCData.stDCCHDR10LightEnhanceData.ucBank);
            break;

        case _DCC_HDR10_USER:
            ScalerColorDCCAdjust(enumSelRegion, pstDCCSetting->stDCCSetting.unDCCData.stDCCHDR10USERData.pucTable, pstDCCSetting->stDCCSetting.unDCCData.stDCCHDR10USERData.ucBank);
            break;

        case _DCC_SDR2HDR:
            ScalerColorDCCAdjust(enumSelRegion, pstDCCSetting->stDCCSetting.unDCCData.stDCCSDRtoHDRData.pucTable, pstDCCSetting->stDCCSetting.unDCCData.stDCCSDRtoHDRData.ucBank);
            break;

        case _DCC_USER:
            ScalerColorDCCAdjust(enumSelRegion, pstDCCSetting->stDCCSetting.unDCCData.stDCCUserData.pucTable, pstDCCSetting->stDCCSetting.unDCCData.stDCCUserData.ucBank);
            ScalerColorDCCSetAutoModeRegion(enumSelRegion, pstDCCSetting->stDCCSetting.unDCCData.stDCCUserData.enumDCCAutoModeEnable);
            break;

        default:
            break;
    }
}
#endif

#if(_COLOR_IP_ICM == _ON)
//--------------------------------------------------
// Description  : ICM Adjust
// Input Value  : Select Region ; ICM Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPICMAdjust(EnumSelRegion enumSelRegion, StructColorICMSetting *pstICMSetting)
{
    switch(pstICMSetting->stICMSetting.enumICMMode)
    {
        case _ICM_OFF:
#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_1)
            ScalerColorICMDisableAllCM(enumSelRegion, _DB_APPLY_NONE);
#endif
            break;
        case _ICM_HDR10_COLORENHANCE:
            ScalerColorICMLoadTable(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMHDR10ColorEnhanceData.pucTable, pstICMSetting->stICMSetting.unICMData.stICMHDR10ColorEnhanceData.ucBank);
            break;
        case _ICM_HDR10_USER:
            ScalerColorICMLoadTable(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMHDR10UserData.pucTable, pstICMSetting->stICMSetting.unICMData.stICMHDR10UserData.ucBank);
            break;
        case _ICM_SDR2HDR:
            ScalerColorICMLoadTable(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMSDRtoHDRData.pucTable, pstICMSetting->stICMSetting.unICMData.stICMSDRtoHDRData.ucBank);
            break;

#if(_SIX_COLOR_SUPPORT == _ON)
        case _ICM_SIXCOLOR:

            ScalerColorSixColorAdjust(enumSelRegion, _SIXCOLOR_R, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorHueR, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorSaturationR);
            ScalerColorSixColorAdjust(enumSelRegion, _SIXCOLOR_Y, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorHueY, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorSaturationY);
            ScalerColorSixColorAdjust(enumSelRegion, _SIXCOLOR_G, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorHueG, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorSaturationG);
            ScalerColorSixColorAdjust(enumSelRegion, _SIXCOLOR_C, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorHueC, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorSaturationC);
            ScalerColorSixColorAdjust(enumSelRegion, _SIXCOLOR_B, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorHueB, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorSaturationB);
            ScalerColorSixColorAdjust(enumSelRegion, _SIXCOLOR_M, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorHueM, pstICMSetting->stICMSetting.unICMData.stICMSixColorData.ucSixColorSaturationM);

            ScalerColorSixColorInitial(enumSelRegion);
            break;
#endif

#if(_SCM_SUPPORT == _ON)
        case _ICM_SCM:
            ScalerColorSCMLoadTable(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMSCMData.pucSCMTable, pstICMSetting->stICMSetting.unICMData.stICMSCMData.ucBank);
            ScalerColorICMLoadTable(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMSCMData.pucICMTable, pstICMSetting->stICMSetting.unICMData.stICMSCMData.ucBank);
            break;
#endif

        case _ICM_USER:
            ScalerColorICMLoadTable(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMUserData.pucTable, pstICMSetting->stICMSetting.unICMData.stICMUserData.ucBank);
            break;

#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _ICM_CHAMELEON:
            for(EnumSixColorType enumType = _SIXCOLOR_R; enumType <= _SIXCOLOR_M; ++enumType)
            {
                ScalerColorChameleonAdjust(enumSelRegion, enumType, &pstICMSetting->stICMSetting.unICMData.stICMChameleonData.pstAxisData[enumType], pstICMSetting->stICMSetting.unICMData.stICMChameleonData.ucICMChameleonDarkOffset);
            }

            ScalerColorChameleonInitial(enumSelRegion);
            break;

#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _ICM_NIGHT_SNIPER:
            ScalerColorICMNightSniperAdjust(enumSelRegion, pstICMSetting->stICMSetting.unICMData.stICMNightSniperData.ucICMNightSniperSat, pstICMSetting->stICMSetting.unICMData.stICMNightSniperData.ucICMNightSniperLightness, pstICMSetting->stICMSetting.unICMData.stICMNightSniperData.ucICMNightSniperDarkOffset);
            break;

#endif
        default:
            break;
    }

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_1)
    // Apply local db
    ScalerColorICMLocalDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif
}
#endif

#if(_COLOR_IP_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Contrast Adjust
// Input Value  : Select Region ; Contrast Setting Struct
// Output Value : None
//--------------------------------------------------
void ScalerColorIPContrastAdjust(EnumSelRegion enumSelRegion, StructColorCtsSetting *pstCtsSetting)
{
    WORD pusData[3] = {0};

    switch(pstCtsSetting->stCtsSetting.enumCtsMode)
    {
        case _CONTRAST_OFF:
            pusData[0] = 0x800;
            pusData[1] = 0x800;
            pusData[2] = 0x800;
            ScalerColorContrastAdjust(enumSelRegion, pusData);
            break;

        case _CONTRAST_HDR10_USER:
            ScalerColorContrastAdjust(enumSelRegion, pstCtsSetting->stCtsSetting.unCtsData.stCtsHDR10Data.pusData);
            break;

        case _CONTRAST_USER:
        default:
            ScalerColorContrastAdjust(enumSelRegion, pstCtsSetting->stCtsSetting.unCtsData.stCtsUserData.pusData);
            break;
    }
}
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
//--------------------------------------------------
// Description  : Brightness Adjust
// Input Value  : Select Region ; Brightness Setting Struct
// Output Value : None
//--------------------------------------------------
void ScalerColorIPBrightnessAdjust(EnumSelRegion enumSelRegion, StructColorBriSetting *pstBriSetting)
{
    WORD pusData[3] = {0};

    switch(pstBriSetting->stBriSetting.enumBriMode)
    {
        case _BRIGHTNESS_OFF:
            pusData[0] = 0x200;
            pusData[1] = 0x200;
            pusData[2] = 0x200;
            ScalerColorBrightnessAdjust(enumSelRegion, pusData);
            break;

        case _BRIGHTNESS_USER:
        default:
            ScalerColorBrightnessAdjust(enumSelRegion, pstBriSetting->stBriSetting.unBriData.stBriUserData.pusData);
            break;
    }
}
#endif

#if(_COLOR_IP_IAPS == _ON)
//--------------------------------------------------
// Description  : IAPS Adjust
// Input Value  : Select Region ; IAPS Setting Struct
// Output Value : None
//--------------------------------------------------
void ScalerColorIPIAPSAdjust(EnumSelRegion enumSelRegion, StructColorIAPSSetting *pstIAPSSetting)
{
    switch(pstIAPSSetting->stIAPSSetting.enumIAPSMode)
    {
        case _IAPS_HDR10_LIGHTENHANCE:
            ScalerColorIAPSGainSoftClampAdjust(enumSelRegion, pstIAPSSetting->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.ucSoftClampValue);
            ScalerColorIAPSGainValueAdjust(enumSelRegion, pstIAPSSetting->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.usGainValue);
            break;

        case _IAPS_OFF:
        default:
            break;
    }
}
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
//--------------------------------------------------
// Description  : 3D Gamma Adjust
// Input Value  : 3D Gamma Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIP3DGammaAdjust(StructColor3DGammaSetting *pst3DGammaSetting)
{
    switch(pst3DGammaSetting->st3DGammaSetting.enum3DGammaMode)
    {
        case _3DGAMMA_OFF:
            break;

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _3DGAMMA_ADVANCED_HDR10:
            ScalerColorRGBGamma3DGammaSwapEnable(_FUNCTION_ON);
            ScalerColorRGB3DGammaAdjust(ScalerColorRGB3DGammaGetAdvancedHDR10TableAddress(),
                                        ScalerColorRGB3DGammaGetAdvancedHDR10TableBank());
            break;
#endif

#if(_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON)
        case _3DGAMMA_GAMUT_COMPRESSION:
            ScalerColorRGBGamma3DGammaSwapEnable(_FUNCTION_ON);
            ScalerColorRGB3DGammaAdjust(pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaGamutCompressionData.pucTable,
                                        pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaGamutCompressionData.ucBank);
            break;
#endif

#if(_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
        case _3DGAMMA_HDR10_REMAP:
            ScalerColorRGBGamma3DGammaSwapEnable(_FUNCTION_ON);
            ScalerColorRGB3DGammaAdjust(pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaHDR10RemapData.pucTable,
                                        pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaHDR10RemapData.ucBank);
            break;
#endif

        case _3DGAMMA_USER:
            ScalerColorRGB3DGammaAdjust(pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaUserData.pucTable,
                                        pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaUserData.ucBank);
            break;

#if (_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
        case _3DGAMMA_CUBE_MAPPING:
            ScalerColorRGBGamma3DGammaSwapEnable(_FUNCTION_OFF);
            ScalerColorRGB3DGammaAdjust(pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaCubeMappingData.pucTable,
                                        pst3DGammaSetting->st3DGammaSetting.unOutGammaData.st3DGammaCubeMappingData.ucBank);
            break;
#endif


        default:
            break;
    }
}
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
//--------------------------------------------------
// Description  : Input Gamma Adjust
// Input Value  : Select Region ; Input Gamma Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPInGammaAdjust(EnumSelRegion enumSelRegion, StructColorInGammaSetting *pstInGammaSetting, EnumIGDBEnableStatus enumDbEnable)
{
    ScalerColorPCMSetPCMMode(enumSelRegion, _PCM_MODE);

    switch(pstInGammaSetting->stInGammaSetting.enumInGammaMode)
    {
        case _INGAMMA_OFF:
#if(_PCM_FULL_TIME_FUNCTION == _OFF)
            ScalerColorPCMSetPCMMode(enumSelRegion, _OGC_MODE);
#endif
            break;

#if(_OGC_FUNCTION == _ON)
        case _INGAMMA_OGC:
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
            if((pstInGammaSetting->unKernelInGammaData.stKernelInGammaOGCData.enumGlobalDimmingStatus == _GLOBAL_DIMMING_ENABLE) ||
               (pstInGammaSetting->unKernelInGammaData.stKernelInGammaOGCData.enumLocalDimmingStatus == _LOCAL_DIMMING_ENABLE))
            {
                ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                               (BYTE *)(DWORD)tusDIMMING_GAMMA_ADDRESS_INDEX[pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaOGCData.enumOGCType],
                                               _OGC_FLASH_BANK, enumDbEnable);
            }
            else
#endif
            {
#if(_PCM_FULL_TIME_FUNCTION == _OFF)
                ScalerColorPCMSetPCMMode(enumSelRegion, _OGC_MODE);
#endif
            }
            break;
#endif

#if(_OCC_FUNCTION == _ON)
        case _INGAMMA_PCM:
            ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                           ScalerColorPCMGetTableAddress(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaPCMData.enumPCMMode),
                                           ScalerColorPCMGetTableBank(), enumDbEnable);
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _INGAMMA_DM:
            ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                  pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaDMData.pucTable,
                                                  pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaDMData.ucBank, enumDbEnable);
            break;
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _INGAMMA_ADVANCED_HDR10:
            if(GET_ADVANCED_HDR10_COLOR_INITIAL_SETTING() == _FALSE)
            {
                ScalerColorPCMSetPCMMode(_DEMO_INSIDE, _PCM_MODE);
                ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                      (BYTE *)(DWORD)(_OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * pstInGammaSetting->unKernelInGammaData.stKernelInGammaAdvancedHDR10Data.ucAdvancedHDR10IGLUTIndex),
                                                      _OGC_FLASH_BANK, enumDbEnable);
            }

            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _INGAMMA_HDR10_AUTO:
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
            if(pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10AutoData.enumHDR10MaxMasteringLvType == _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM)
            {
                ScalerColorPCMInputGamma129NodeAdjustXRAM(enumSelRegion, pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10AutoData.pucHDR10MasteringLvStepLessTMTable, enumDbEnable);
            }
            else
#endif
            {
#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
                if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_USER)
                {
                    ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                          (BYTE *)(DWORD)tusHDR10_IG_USER_DEFINE_FIXED_POINT_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10AutoData.enumHDR10MaxMasteringLvType * 2 + pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus],
                                                          _OGC_FLASH_BANK, enumDbEnable);
                }
                else
#endif
                {
#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
                    if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON)
                    {
                        ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                              (BYTE *)(DWORD)tusHDR10_IG_FIXED_POINT_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10AutoData.enumHDR10MaxMasteringLvType * 2 + pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus],
                                                              _OGC_FLASH_BANK, enumDbEnable);
                    }
                    else
#endif
                    {
                        ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                                       (BYTE *)(DWORD)tusHDR10_IG_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10AutoData.enumHDR10MaxMasteringLvType * 2 + pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus],
                                                       _OGC_FLASH_BANK, enumDbEnable);
                    }
                }
            }

            break;

        case _INGAMMA_HDR10_FORCE_2084:
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
            if(pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.enumHDR10MaxMasteringLvType == _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM)
            {
                ScalerColorPCMInputGamma129NodeAdjustXRAM(enumSelRegion, pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.pucHDR10MasteringLvStepLessTMTable, enumDbEnable);
            }
            else
#endif
            {
#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
                if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_USER)
                {
                    ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                          (BYTE *)(DWORD)tusHDR10_IG_USER_DEFINE_FIXED_POINT_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.enumHDR10MaxMasteringLvType * 2 + pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus],
                                                          _OGC_FLASH_BANK, enumDbEnable);
                }
                else
#endif
                {
#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
                    if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON)
                    {
                        ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                              (BYTE *)(DWORD)tusHDR10_IG_FIXED_POINT_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.enumHDR10MaxMasteringLvType * 2 + pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus],
                                                              _OGC_FLASH_BANK, enumDbEnable);
                    }
                    else
#endif
                    {
                        ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                                       (BYTE *)(DWORD)tusHDR10_IG_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.enumHDR10MaxMasteringLvType * 2 + pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus],
                                                       _OGC_FLASH_BANK, enumDbEnable);
                    }
                }
            }
            break;

        case _INGAMMA_HDR10_USER:
#if(_INPUT_GAMMA_NODE_1025_SUPPORT == _ON)
            if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10UserData.enumPCMNodeType == _PCM_NODE_1025)
            {
                ScalerColorPCMInputGamma1025NodeAdjust(enumSelRegion,
                                                       pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10UserData.pucTable,
                                                       pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10UserData.ucBank, enumDbEnable);
            }
            else
#endif
            {
                ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                      pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10UserData.pucTable,
                                                      pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaHDR10UserData.ucBank, enumDbEnable);
            }
            break;
#endif
#if(_HDMI_SBTM_SUPPORT == _ON)
        case _INGAMMA_HDR10_SBTM:
            if(pstInGammaSetting->unKernelInGammaData.stKernelInGammaSBTMData.enumHDR10SBTMMode == _HDR10_SBTM_MODE_G_RDM)
            {
                if(pstInGammaSetting->unKernelInGammaData.stKernelInGammaSBTMData.enumHDR10SBTMGRDMLumMaxType == _HDR10_SBTM_GRDM_LV_TYPE_1000)
                {
                    ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                                   (BYTE *)(DWORD)tusHDR10_IG_ADDRESS_INDEX[_HDR10_MAX_MASTERING_LV_TYPE_1200 * 2],
                                                   _OGC_FLASH_BANK, enumDbEnable);
                }
                else
                {
                    ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                                   (BYTE *)(DWORD)tusHDR10_IG_ADDRESS_INDEX[_HDR10_MAX_MASTERING_LV_TYPE_NOTM * 2],
                                                   _OGC_FLASH_BANK, enumDbEnable);
                }
            }
            else
            {
                ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                               (BYTE *)(DWORD)tusHDR10_IG_ADDRESS_INDEX[_HDR10_MAX_MASTERING_LV_TYPE_NOTM * 2],
                                               _OGC_FLASH_BANK, enumDbEnable);
            }
            break;
#endif

#if(_HLG_SUPPORT == _ON)
        case _INGAMMA_HLG:
            ScalerColorPCMInputGammaAdjust(enumSelRegion, ScalerColorPCMGetTableAddress(_PCM_HLG), ScalerColorPCMGetTableBank(), enumDbEnable);
            break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        case _INGAMMA_FREESYNC2:
            ScalerColorPCMInputGammaAdjust(enumSelRegion,
                                           (BYTE *)(DWORD)tusFREESYNC_II_IG_ADDRESS_INDEX[pstInGammaSetting->unKernelInGammaData.stKernelInGammaFreeSync2Data.enumFreeSyncIIEOTFType],
                                           _FREESYNC_II_FLASH_BANK, enumDbEnable);
            break;

        case _INGAMMA_FREESYNC2_USER:
#if(_INPUT_GAMMA_NODE_1025_SUPPORT == _ON)
            if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaFreeSync2UserData.enumPCMNodeType == _PCM_NODE_1025)
            {
                ScalerColorPCMInputGamma1025NodeAdjust(enumSelRegion,
                                                       pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaFreeSync2UserData.pucTable,
                                                       pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaFreeSync2UserData.ucBank, enumDbEnable);
            }
            else
#endif
            {
                ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                      pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaFreeSync2UserData.pucTable,
                                                      pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaFreeSync2UserData.ucBank, enumDbEnable);
            }
            break;
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
        case _INGAMMA_SDRTOHDR:
            ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                  pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaSDRtoHDRData.pucTable,
                                                  pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaSDRtoHDRData.ucBank, enumDbEnable);
            break;
#endif

#if(_PCM_FUNCTION == _ON)
        case _INGAMMA_PCM_USER:
#if(_INPUT_GAMMA_NODE_1025_SUPPORT == _ON)
            if(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaPCMUserData.enumPCMNodeType == _PCM_NODE_1025)
            {
                ScalerColorPCMInputGamma1025NodeAdjust(enumSelRegion,
                                                       pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaPCMUserData.pucTable,
                                                       pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaPCMUserData.ucBank, enumDbEnable);
            }
            else
#endif
            {
                ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                      pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaPCMUserData.pucTable,
                                                      pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaPCMUserData.ucBank, enumDbEnable);
            }
            break;
#endif
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
        case _INGAMMA_OCC_PCM_GAMMA:
            ScalerColorPCMInputGamma129NodeAdjust(enumSelRegion,
                                                  ScalerColorOCCPCMGammaGetTableAddress(pstInGammaSetting->stInGammaSetting.unInGammaData.stInGammaOCCPCMGammaData.enumOCCPCMGammaType),
                                                  ScalerColorPCMGetTableBank(), enumDbEnable);
            break;
#endif
        default:
            break;
    }
}
#endif

#if(_COLOR_IP_YMAPPING == _ON)
//--------------------------------------------------
// Description  : Ymapping Adjust
// Input Value  : Select Region ; Ymapping Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPYmappingAdjust(EnumSelRegion enumSelRegion, StructColorYmappingSetting *pstYmappingSetting)
{
    switch(pstYmappingSetting->stYmappingSetting.enumYmappingMode)
    {
        case _YMAPPING_OFF:
            ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_OFF);
            break;

#if(_HLG_SUPPORT == _ON)
        case _YMAPPING_HLG:
            ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_OFF);
            ScalerColorYMappingModeSelect(enumSelRegion, _YMAPPING_Y_MODE);
            ScalerColorYMappingSoftClampEnable(enumSelRegion, _FUNCTION_OFF);
            ScalerColorYMappingSetOffset(enumSelRegion, 0x0000);
            if(pstYmappingSetting->stYmappingSetting.unYmappingData.stYmappingHLGData.enumHLGOOTFType == _HLG_OOTF_STANDARD_MODE)
            {
                ScalerColorYMappingSetGainPrecision(enumSelRegion, _YMAPPING_GAIN_PRECISION_U212);
                if(ScalerColorYMappingLoadGainTable(enumSelRegion, pstYmappingSetting->unKernelYmappingData.stKernelYmappingHLGData.pucTable, _YMAPPING_GAIN_TABLE_SIZE, pstYmappingSetting->unKernelYmappingData.stKernelYmappingHLGData.ucBank, _BURSTWRITE_FROM_FLASH) == _FAIL)
                {
                    return;
                }
            }
            else
            {
                BYTE ucYMappingGainPrecision = 0;
                BYTE ucBank = pstYmappingSetting->stYmappingSetting.unYmappingData.stYmappingHLGData.ucBank;
                BYTE *pucTable = pstYmappingSetting->stYmappingSetting.unYmappingData.stYmappingHLGData.pucTable;

                ScalerFlashRead(ucBank, &pucTable[_YMAPPING_GAIN_TABLE_SIZE], 1, &ucYMappingGainPrecision);
                ScalerColorYMappingSetGainPrecision(enumSelRegion, (EnumYMappingGainPrecision)ucYMappingGainPrecision);
                if(ScalerColorYMappingLoadGainTable(enumSelRegion, pucTable, _YMAPPING_GAIN_TABLE_SIZE, ucBank, _BURSTWRITE_FROM_FLASH) == _FAIL)
                {
                    return;
                }
            }
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
            if(ScalerColorYMappingGetDBStatus() == _FUNCTION_ON)
            {
                ScalerColorYMappingDBApply(enumSelRegion, _DB_APPLY_POLLING);
            }
#endif
            ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_ON);
            break;
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _YMAPPING_ADVANCED_HDR10:
            if(GET_ADVANCED_HDR10_COLOR_INITIAL_SETTING() == _FALSE)
            {
                ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_OFF);
                ScalerColorYMappingModeSelect(enumSelRegion, _YMAPPING_MAXRGB_MODE);
                ScalerColorYMappingSoftClampEnable(enumSelRegion, _FUNCTION_OFF);
                ScalerColorYMappingSetGainPrecision(enumSelRegion, _YMAPPING_GAIN_PRECISION_U410);
                ScalerColorYMappingSetOffset(enumSelRegion, 0x0000);

                ScalerColorYMappingModeSelect(_DEMO_INSIDE, _YMAPPING_MAXRGB_MODE);
                ScalerColorYMappingSoftClampEnable(_DEMO_INSIDE, _FUNCTION_OFF);
                ScalerColorYMappingSetGainPrecision(_DEMO_INSIDE, _YMAPPING_GAIN_PRECISION_U410);
                ScalerColorYMappingSetOffset(_DEMO_INSIDE, 0x0000);

                if(ScalerTimerPollingXRAMFlagProc(_ADVANCED_HDR10_YM_TABLE_READY_WAIT_TIME, (DWORD)(&g_stSyncAdvancedHDR10SettingInfo.ucYMTableReady), _BIT0, _TRUE) == _TRUE)
                {
                    if(ScalerColorYMappingLoadGainTable(enumSelRegion, g_pucSyncAdvancedHDR10YmTable, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _FAIL)
                    {
                        return;
                    }
                }

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
                if(ScalerColorYMappingGetDBStatus() == _FUNCTION_ON)
                {
                    ScalerColorYMappingDBApply(enumSelRegion, _DB_APPLY_POLLING);
                }
#endif
                ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_ON);
            }

            break;
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
        case _YMAPPING_HDR10_BACKLIGHT_ADAPTIVE_TM:
        {
            EnumHDR10ColorMatrix enumHDR10ColorMatrix = pstYmappingSetting->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.enumHDR10ColorMatrix;
            EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus = pstYmappingSetting->stYmappingSetting.unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.enumHDR10DarkEnhanceStatus;
            BYTE ucLvMatchBound = pstYmappingSetting->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.ucLvMatchBound;
            WORD usLvMatchBoundGain = pstYmappingSetting->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.usLvMatchBoundGain;
            WORD *pusHDRLinearOut = pstYmappingSetting->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.pusHDRLinearOut;
            BYTE pucHDR10BackLightAdaptiveTMLUT[710] = {0};

            ScalerColorYMappingGetHDR10BackLightAdaptiveTMLUT(_OGC_FLASH_BANK, enumHDR10DarkEnhanceStatus, ucLvMatchBound, usLvMatchBoundGain, pusHDRLinearOut, pucHDR10BackLightAdaptiveTMLUT);

            ScalerColorYMappingDBEnable(_FUNCTION_ON);
            if(ScalerColorYMappingLoadGainTable(enumSelRegion, pucHDR10BackLightAdaptiveTMLUT, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _FAIL)
            {
                return;
            }
#if(_HW_YMAPPING_DB_TYPE >= _YMAPPING_DB_GEN_1)
            ScalerColorYMappingSetGainPrecision(enumSelRegion, _YMAPPING_GAIN_PRECISION_U212);
            ScalerColorYMappingSetOffset(enumSelRegion, 0x0000);
#endif
            ScalerColorYMappingDBApply(enumSelRegion, _DB_APPLY_POLLING);

            ScalerColorYMappingSetRGBCoefficient(enumSelRegion, tusHDR10_YM_RGB_COEFF_INDEX[enumHDR10ColorMatrix][0], tusHDR10_YM_RGB_COEFF_INDEX[enumHDR10ColorMatrix][1], tusHDR10_YM_RGB_COEFF_INDEX[enumHDR10ColorMatrix][2]); // BT2020
            ScalerColorYMappingModeSelect(enumSelRegion, _YMAPPING_Y_MODE);
            ScalerColorYMappingSoftClampEnable(enumSelRegion, _FUNCTION_OFF);
#if(_HW_YMAPPING_DB_TYPE < _YMAPPING_DB_GEN_1)
            ScalerColorYMappingSetGainPrecision(enumSelRegion, _YMAPPING_GAIN_PRECISION_U212);
            ScalerColorYMappingSetOffset(enumSelRegion, 0x0000);
#endif
            ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_ON);
            break;
        }
#endif

        default:
            break;
    }
}
#endif

#if(_COLOR_IP_SRGB == _ON)
//--------------------------------------------------
// Description  : sRGB Adjust
// Input Value  : Select Region ; sRGB Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPSRGBAdjust(EnumSelRegion enumSelRegion, StructColorSRGBSetting *pstSRGBSetting)
{
#if(_OCC_FUNCTION == _ON)
    EnumSrgbPrecision enumPrecision = _SRGB_0_BIT_SHIFT_LEFT;
#endif
    enumSelRegion = enumSelRegion;

    switch(pstSRGBSetting->stSRGBSetting.enumSRGBMode)
    {
        case _SRGB_OFF:
#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_0_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_BYPASS), ScalerColorsRGBBypassGetTableBank(), 18);
#endif
            break;

#if(_OCC_FUNCTION == _ON)
        case _SRGB_PCM:
            switch(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumPCMMode)
            {
#if((_DCIP3_NO_COMPRESSION_SUPPORT == _ON) || (_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON))
                case _PCM_DCI_P3:
                case _PCM_DISPLAY_P3:
                    enumPrecision = _SRGB_1_BIT_SHIFT_LEFT;
                    break;
#endif
#if((_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _ON) || (_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON))
                case _PCM_USER_DEFINE:
                case _PCM_USER_DEFINE_2:
                case _PCM_USER_DEFINE_3:
                case _PCM_USER_DEFINE_4:
                case _PCM_USER_DEFINE_5:
                case _PCM_USER_DEFINE_6:
                    enumPrecision = _SRGB_1_BIT_SHIFT_LEFT;
                    break;
#endif
#if(_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON)
                case _PCM_ADOBE_RGB:
                    enumPrecision = _SRGB_1_BIT_SHIFT_LEFT;
                    break;
#endif
                default:
                    break;
            }
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorPCMSRGBGetFlashAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumPCMMode, _OGC_MAX_BACKLIGHT_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
            else if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_3_TYPE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorPCMSRGBGetFlashAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumPCMMode, _OGC_MULTI_BACKLIGHT_3_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_4_TYPE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorPCMSRGBGetFlashAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumPCMMode, _OGC_MULTI_BACKLIGHT_4_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
#endif
#endif
            else
#endif
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorPCMSRGBGetFlashAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMData.enumPCMMode, _OGC_NORMAL_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
            break;
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _SRGB_ADVANCED_HDR10:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                     (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[_HDR10_COLOR_MATRIX_DCIP3_D65],
                                     _OGC_FLASH_BANK, 18);

            ScalerColorPCMSRGBAdjust(_DEMO_INSIDE, _SRGB_1_BIT_SHIFT_LEFT,
                                     (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[_HDR10_COLOR_MATRIX_DCIP3_D65],
                                     _OGC_FLASH_BANK, 18);
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _SRGB_HDR10_AUTO:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                     (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[pstSRGBSetting->unKernelSRGBData.stKernelSRGBHDR10AutoData.enumHDR10ColorMatrix],
                                     _OGC_FLASH_BANK, 18);

            break;

        case _SRGB_HDR10_FORCE_2084:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                     (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHDR10Force2084Data.enumHDR10ColorMatrix],
                                     _OGC_FLASH_BANK, 18);
            break;

        case _SRGB_HDR10_USER:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                     pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHDR10UserData.pucTable,
                                     pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHDR10UserData.ucBank,
                                     18);
            break;

#if(_HDMI_SBTM_SUPPORT == _ON)
        case _SRGB_HDR10_SBTM:
#if(_PCM_FUNCTION == _ON)

            if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHDR10SBTMData.enumHDR10SBTMColorMatrix == _HDR10_SBTM_COLOR_MATRIX_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_0_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_BYPASS), ScalerColorsRGBBypassGetTableBank(), 18);
            }
            else
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                         (BYTE *)(DWORD)tusHDR10_SBTM_SRGB_ADDRESS_INDEX[pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHDR10SBTMData.enumHDR10SBTMColorMatrix],
                                         _OGC_FLASH_BANK, 18);
            }
#endif
            break;
#endif
#endif

#if(_HLG_SUPPORT == _ON)
        case _SRGB_HLG_AUTO:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                     (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[pstSRGBSetting->unKernelSRGBData.stKernelSRGBHLGAutoData.enumHLGColorMatrix],
                                     _OGC_FLASH_BANK, 18);
            break;

        case _SRGB_HLG_FORCE:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                     (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHLGForceData.enumHLGColorMatrix],
                                     _OGC_FLASH_BANK, 18);
            break;
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
        case _SRGB_SDRTOHDR:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_0_BIT_SHIFT_LEFT, pstSRGBSetting->unKernelSRGBData.stKernelSRGBSDRtoHDRData.pucTable, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        case _SRGB_FREESYNC2:
            ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_0_BIT_SHIFT_LEFT, (BYTE *)_FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS, _FREESYNC_II_FLASH_BANK, 18);
            break;
#endif


#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
        case _SRGB_HUESAT:
#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
            ScalerColorSpaceConvertSetGlobalHueSat(enumSelRegion, 0, 100);
#endif
            ScalerColorSRGBSetGlobalHueSat(enumSelRegion, pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHueSatData.shHue, pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBHueSatData.usSat);    // Default Hue = 180
            break;
#endif

#if(_PCM_FUNCTION == _ON)
        case _SRGB_PCM_USER:
            ScalerColorPCMSRGBAdjust(enumSelRegion,
                                     pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMUserData.enumSrgbPrecision,
                                     pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMUserData.pucTable,
                                     pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBPCMUserData.ucBank,
                                     18);
            break;
#endif

#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
        case _SRGB_OCC_PCM_GAMMA:
            enumPrecision = _SRGB_1_BIT_SHIFT_LEFT;
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorOCCPCMGammaGetsRGBCTTableAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOCCPCMGammaCTMatrix, _OGC_MAX_BACKLIGHT_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
            else if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_3_TYPE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorOCCPCMGammaGetsRGBCTTableAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOCCPCMGammaCTMatrix, _OGC_MULTI_BACKLIGHT_3_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_4_TYPE)
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorOCCPCMGammaGetsRGBCTTableAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOCCPCMGammaCTMatrix, _OGC_MULTI_BACKLIGHT_4_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
#endif
#endif
            else
#endif
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, enumPrecision,
                                         (BYTE *)(DWORD)ScalerColorOCCPCMGammaGetsRGBCTTableAddress(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBOCCPCMGammaData.enumOCCPCMGammaCTMatrix, _OGC_NORMAL_TYPE),
                                         _OGC_FLASH_BANK, 18);
            }
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _SRGB_DM:
            if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBDMData.enumDMColorMatrix == _DM_COLOR_MATRIX_NATIVE)
            {
#if(_PCM_FUNCTION == _ON)
                ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_0_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_BYPASS), ScalerColorsRGBBypassGetTableBank(), 18);
#endif
            }
            else
            {
                ScalerColorPCMSRGBAdjust(enumSelRegion, _SRGB_1_BIT_SHIFT_LEFT,
                                         (BYTE *)(DWORD)tusHDR10_SRGB_ADDRESS_INDEX[pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBDMData.enumDMColorMatrix],
                                         _OGC_FLASH_BANK, 18);
            }
            break;
#endif
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
        case _SRGB_PCM_USER_CCT:
            switch(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumPCMMode)
            {
                case _PCM_DCI_P3:
                case _PCM_DISPLAY_P3:
                case _PCM_USER_DEFINE:
                case _PCM_USER_DEFINE_2:
                case _PCM_USER_DEFINE_3:
                case _PCM_USER_DEFINE_4:
                case _PCM_USER_DEFINE_5:
                case _PCM_USER_DEFINE_6:
                case _PCM_ADOBE_RGB:
                    enumPrecision = _SRGB_1_BIT_SHIFT_LEFT;
                    break;
                default:
                    break;
            }
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
            {
                ScalerColorPCMSRGBColorTempTransfer(enumSelRegion,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumPCMMode,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable,
                                                    enumPrecision, _OGC_MAX_BACKLIGHT_TYPE);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
            else if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_3_TYPE)
            {
                ScalerColorPCMSRGBColorTempTransfer(enumSelRegion,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumPCMMode,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable,
                                                    enumPrecision, _OGC_MULTI_BACKLIGHT_3_TYPE);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_4_TYPE)
            {
                ScalerColorPCMSRGBColorTempTransfer(enumSelRegion,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumPCMMode,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable,
                                                    enumPrecision, _OGC_MULTI_BACKLIGHT_4_TYPE);
            }
#endif
#endif
            else
#endif
            {
                ScalerColorPCMSRGBColorTempTransfer(enumSelRegion,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.enumPCMMode,
                                                    pstSRGBSetting->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable,
                                                    enumPrecision, _OGC_NORMAL_TYPE);
            }
            break;
#endif
        default:
            break;
    }
}
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Color Conver Adjust Hue & Sat
// Input Value  : Select Region ; sRGB Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPDColorConvertAdjust(EnumSelRegion enumSelRegion, StructColorDColorConvertSetting *pstDColorConvertSetting)
{
    switch(pstDColorConvertSetting->stDColorConvertSetting.enumDColorConvertMode)
    {
        case _D_COLOR_CONVERT_STANDARD:
            ScalerColorSpaceConvertSetGlobalHueSat(enumSelRegion, 0, 100);
            break;

        case _D_COLOR_CONVERT_HUE_SATURATION:
            ScalerColorSpaceConvertSetGlobalHueSat(enumSelRegion,
                                                   pstDColorConvertSetting->stDColorConvertSetting.unDColorConvertData.stDColorConvertHueSatData.shHue,
                                                   pstDColorConvertSetting->stDColorConvertSetting.unDColorConvertData.stDColorConvertHueSatData.usSat);    // Default Hue = 180
            break;

        default:
            break;
    }
}
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
//--------------------------------------------------
// Description  : Uniformity Adjust
// Input Value  : StructUniformitySetting ; Uniformity Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPUniformityAdjust(StructColorUniformitySetting *pstUniData)
{
#if(_UNIFORMITY_FUNCTION == _ON)
    BYTE ucGainTableBank = 0;
    WORD usGainTableAddr = 0;
    DWORD ulGainTableSize = 0;
    BYTE ucUniLevelMode = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucOffsetTableBank = 0;
    WORD usOffsetTableAddr = 0;
    WORD usDecayTableAddr = 0;

#endif
#endif

    switch(pstUniData->stUniformitySetting.enumUniformityMode)
    {
#if(_UNIFORMITY_FUNCTION == _ON)
        case _UNIFORMITY_PCM:
            ucGainTableBank = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucGainTableBank;
            usGainTableAddr = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usGainTableAddr;
            ulGainTableSize = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ulGainTableSize;
            ucUniLevelMode = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucUniLevelMode;
            ScalerColorPanelUniformityInitial();
            ScalerColorPanelUniformityAdjust((BYTE *)(DWORD)usGainTableAddr,
                                             ulGainTableSize,
                                             ucGainTableBank,
                                             _UNIFORMITY_PCM_MODE,
                                             ucUniLevelMode);

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            ucOffsetTableBank = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucOffsetTableBank;
            usOffsetTableAddr = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usOffsetTableAddr;
            usDecayTableAddr = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usDecayTableAddr;
            if(pstUniData->stUniformitySetting.unUniformityData.stUniformityPCMData.b1UniformityOffsetEnable == _ON)
            {
                ScalerColorPanelUniformityOffsetAdjust((BYTE *)(DWORD)usOffsetTableAddr,
                                                       _PANEL_UNIFORMITY_OFFSET_LUT_SIZE,
                                                       ucOffsetTableBank);
                ScalerColorPanelUniformityDecayAdjust((BYTE *)(DWORD)usDecayTableAddr,
                                                      _PANEL_UNIFORMITY_DECAY_LUT_SIZE,
                                                      ucOffsetTableBank,
                                                      _UNIFORMITY_PCM_MODE,
                                                      ucUniLevelMode);
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_ON);
            }
            else
            {
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
            }
#endif

            break;

        case _UNIFORMITY_OGC:
            ucGainTableBank = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucGainTableBank;
            usGainTableAddr = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usGainTableAddr;
            ulGainTableSize = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ulGainTableSize;
            ucUniLevelMode = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucUniLevelMode;
            ScalerColorPanelUniformityInitial();
            ScalerColorPanelUniformityAdjust((BYTE *)(DWORD)usGainTableAddr,
                                             ulGainTableSize,
                                             ucGainTableBank,
                                             _UNIFORMITY_OGC_MODE,
                                             ucUniLevelMode);

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            ucOffsetTableBank = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucOffsetTableBank;
            usOffsetTableAddr = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usOffsetTableAddr;
            usDecayTableAddr = pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usDecayTableAddr;
            if(pstUniData->stUniformitySetting.unUniformityData.stUniformityOGCData.b1UniformityOffsetEnable == _ON)
            {
                ScalerColorPanelUniformityOffsetAdjust((BYTE *)(DWORD)usOffsetTableAddr,
                                                       _PANEL_UNIFORMITY_OFFSET_LUT_SIZE,
                                                       ucOffsetTableBank);
                ScalerColorPanelUniformityDecayAdjust((BYTE *)(DWORD)usDecayTableAddr,
                                                      _PANEL_UNIFORMITY_DECAY_LUT_SIZE,
                                                      ucOffsetTableBank,
                                                      _UNIFORMITY_OGC_MODE,
                                                      ucUniLevelMode);
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_ON);
            }
            else
            {
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
            }
#endif
            break;
#endif

        case _UNIFORMITY_USER:
            ScalerColorPanelUniformityInitial();
            ScalerColorPanelUniformityAdjust(pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.pucTable,
                                             pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.enumUniformityLevel * _PANEL_UNIFORMITY_1LEVEL_SIZE,
                                             pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.ucBank,
                                             pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.enumUniformityMode,
                                             pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.enumUniformityLevel);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            if(pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.b1UniformityOffsetEnable == _ON)
            {
                ScalerColorPanelUniformityOffsetAdjust(pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.pucOffsetTable,
                                                       _PANEL_UNIFORMITY_OFFSET_LUT_SIZE,
                                                       pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.ucOffsetBank);
                ScalerColorPanelUniformityDecayAdjust(pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.pucDecayTable,
                                                      _PANEL_UNIFORMITY_DECAY_LUT_SIZE,
                                                      pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.ucDecayBank,
                                                      pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.enumUniformityMode,
                                                      pstUniData->stUniformitySetting.unUniformityData.stUniformityIUserData.enumUniformityLevel);
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_ON);
            }
            else
            {
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
            }
#endif
            break;
        case _UNIFORMITY_OFF:
        default:
            break;
    }
}
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
//--------------------------------------------------
// Description  : Post Gamma Adjust
// Input Value  : Select Region ; Post Gamma Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPPostGammaAdjust(EnumSelRegion enumSelRegion, StructColorPostGammaSetting *pstPostGammaSetting)
{
    switch(pstPostGammaSetting->stPostGammaSetting.enumPostGammaMode)
    {
        case _POSTGAMMA_OFF:
            ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_OFF);
            break;

#if(_OGC_FUNCTION == _ON)
        case _POSTGAMMA_OGC:
#if(_LOCAL_DIMMING_FUNCTION == _ON)
            if(pstPostGammaSetting->unKernelPostGammaData.stKernelPostGammaOGCData.enumLocalDimmingStatus == _LOCAL_DIMMING_ENABLE)
            {
                ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_OFF);
                break;
            }
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            if(pstPostGammaSetting->unKernelPostGammaData.stKernelPostGammaOGCData.enumGlobalDimmingStatus == _GLOBAL_DIMMING_ENABLE)
            {
                ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_OFF);
                break;
            }
            else
#endif
            {
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
                if(pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCUniformityPlusFunction == _OGC_UNI_PLUS_FUNCTION_ON)
                {
                    BYTE ucGammaBankNum = pstPostGammaSetting->unKernelPostGammaTableAddr.stOutGammaTableAddr.ucOutGammaTableBank;
                    BYTE *pucGammaBankAddr = pstPostGammaSetting->unKernelPostGammaTableAddr.stOutGammaTableAddr.pucOutGammaTableAddr;
#if(_PCM_FULL_TIME_FUNCTION == _ON)
                    ScalerColorPCMPostGammaAdjust(enumSelRegion, pucGammaBankAddr, ucGammaBankNum);
#else
                    ScalerColorPostGammaAdjust(enumSelRegion, pucGammaBankAddr, ucGammaBankNum);
#endif
                    ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_ON);
                }
                else
                {
                    ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_OFF);
                }
#endif
            }
            break;
#endif

#if(_PCM_FUNCTION == _ON)
        case _POSTGAMMA_PCM_USER:
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
            ScalerColorPCMPostGammaAdjust(enumSelRegion,
                                          pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaPCMUserData.pucTable,
                                          pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaPCMUserData.ucBank);
            ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_ON);
#endif
            break;
#endif

#if(_GAMMA_FUNCTION == _ON)
        case _POSTGAMMA_USER:
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            ScalerColorPCMPostGammaAdjust(enumSelRegion,
                                          pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaUserData.pucTable,
                                          pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaUserData.ucBank);
#else
            ScalerColorPostGammaAdjust(enumSelRegion,
                                       pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaUserData.pucTable,
                                       pstPostGammaSetting->stPostGammaSetting.unPostGammaData.stPostGammaUserData.ucBank);
#endif
            ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_ON);
#endif
            break;
#endif

        default:
            ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_OFF);
            break;
    }
}
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
//--------------------------------------------------
// Description  : Output Gamma Adjust
// Input Value  : Select Region ; Output Gamma Setting Union
// Output Value : None
//--------------------------------------------------
void ScalerColorIPOutGammaAdjust(EnumSelRegion enumSelRegion, StructColorOutGammaSetting *pstOutGammaSetting)
{
    switch(pstOutGammaSetting->stOutGammaSetting.enumOutGammaMode)
    {
        case _OUTGAMMA_OFF:
            break;

#if(_OGC_FUNCTION == _ON)
        case _OUTGAMMA_OGC:
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            if(pstOutGammaSetting->unKernelOutGammaData.stKernelOutGammaOGCData.enumGlobalDimmingStatus == _GLOBAL_DIMMING_ENABLE)
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_DIMMING_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
            else
#endif
            {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
                if(pstOutGammaSetting->unKernelOutGammaData.stKernelOutGammaOGCData.enumLocalDimmingStatus == _LOCAL_DIMMING_ENABLE)
                {
                    ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
                }
                else
#endif
                {
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
                    if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCUniformityPlusFunction == _OGC_UNI_PLUS_FUNCTION_ON)
                    {
#if(_PCM_FULL_TIME_FUNCTION == _ON)
                        ScalerColorPCMOutputGammaAdjust(enumSelRegion, ScalerColorOutputPostGammaBypassGetTableAddress(_PCM_MODE), ScalerColorOutputPostGammaBypassGetTableBank());
#else
                        ScalerColorOutputGammaAdjust(enumSelRegion, ScalerColorOutputPostGammaBypassGetTableAddress(_OGC_MODE), ScalerColorOutputPostGammaBypassGetTableBank());
#endif
                    }
                    else
#endif
                    {
                        BYTE ucGammaBankNum = pstOutGammaSetting->unKernelOutGammaTableAddr.stOutGammaTableAddr.ucOutGammaTableBank;
                        BYTE *pucGammaBankAddr = pstOutGammaSetting->unKernelOutGammaTableAddr.stOutGammaTableAddr.pucOutGammaTableAddr;
#if(_PCM_FULL_TIME_FUNCTION == _ON)
                        ScalerColorPCMOutputGammaAdjust(enumSelRegion, pucGammaBankAddr, ucGammaBankNum);
#else
                        ScalerColorOutputGammaAdjust(enumSelRegion, pucGammaBankAddr, ucGammaBankNum);
#endif
                    }
                }
            }
            break;
#endif

#if(_OCC_FUNCTION == _ON)
        case _OUTGAMMA_PCM:
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            if(pstOutGammaSetting->unKernelOutGammaData.stKernelOutGammaPCMData.enumGlobalDimmingStatus == _GLOBAL_DIMMING_ENABLE)
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_DIMMING_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
            else
#endif
            {
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
                if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaPCMData.enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
                {
                    ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_MAX_BRI_ADDRESS, _OCC_GAMMA_FLASH_BANK);
                }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
                else if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaPCMData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_3_TYPE)
                {
                    ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_MULTI_BRI_3_ADDRESS, _OCC_GAMMA_FLASH_BANK);
                }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
                else if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaPCMData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_4_TYPE)
                {
                    ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_MULTI_BRI_4_ADDRESS, _OCC_GAMMA_FLASH_BANK);
                }
#endif
#endif
                else
#endif
                {
                    ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
                }
            }
            break;
#endif

#if(_PCM_FUNCTION == _ON)
        case _OUTGAMMA_PCM_USER:
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, ScalerColorOutputPostGammaBypassGetTableAddress(_PCM_MODE), ScalerColorOutputPostGammaBypassGetTableBank());
#else
            ScalerColorPCMOutputGammaAdjust(enumSelRegion,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaPCMUserData.pucTable,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaPCMUserData.ucBank);
#endif
            break;
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
        case _OUTGAMMA_SDRTOHDR:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, pstOutGammaSetting->unKernelOutGammaData.stKernelOutGammaSDRtoHDRData.pucTable, _OCC_GAMMA_FLASH_BANK);
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _OUTGAMMA_DM:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            break;
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _OUTGAMMA_ADVANCED_HDR10:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            ScalerColorPCMOutputGammaAdjust(_DEMO_INSIDE, (BYTE *)_OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OUTGAMMA_HDR10:
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            if(pstOutGammaSetting->unKernelOutGammaData.stKernelOutGammaHDR10Data.enumGlobalDimmingStatus == _GLOBAL_DIMMING_ENABLE)
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_DIMMING_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
            else
#endif
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }

            break;

        case _OUTGAMMA_HDR10_USER:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaHDR10UserData.pucTable,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaHDR10UserData.ucBank);
            break;
#endif

#if(_HLG_SUPPORT == _ON)
        case _OUTGAMMA_HLG:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        case _OUTGAMMA_FREESYNC2:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_FREESYNC_II_OCC_GAMMA10_ADDRESS, _FREESYNC_II_FLASH_BANK);
            break;

        case _OUTGAMMA_FREESYNC2_USER:
            ScalerColorPCMOutputGammaAdjust(enumSelRegion,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaFreeSync2UserData.pucTable,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaFreeSync2UserData.ucBank);
            break;
#endif

#if(_GAMMA_FUNCTION == _ON)
        case _OUTGAMMA_USER:

#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            ScalerColorPCMOutputGammaAdjust(enumSelRegion, ScalerColorOutputPostGammaBypassGetTableAddress(_PCM_MODE), ScalerColorOutputPostGammaBypassGetTableBank());
#else
            ScalerColorOutputGammaAdjust(enumSelRegion, ScalerColorOutputPostGammaBypassGetTableAddress(_OGC_MODE), ScalerColorOutputPostGammaBypassGetTableBank());
#endif
#else
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            ScalerColorPCMOutputGammaAdjust(enumSelRegion,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaUserData.pucTable,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaUserData.ucBank);
#else
            ScalerColorOutputGammaAdjust(enumSelRegion,
                                         pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaUserData.pucTable,
                                         pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaUserData.ucBank);
#endif
#endif
            break;
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
        case _OUTGAMMA_DICOM:
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            ScalerColorPCMOutputGammaAdjust(enumSelRegion,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.pucTable,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.ucBank);

#else
            ScalerColorOutputGammaAdjust(enumSelRegion,
                                         pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.pucTable,
                                         pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.ucBank);
#endif
            break;
#endif

#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
        case _OUTGAMMA_OCC_PCM_GAMMA:
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaOCCPCMGammaData.enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_MAX_BRI_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
            else if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaOCCPCMGammaData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_3_TYPE)
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_MULTI_BRI_3_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaOCCPCMGammaData.enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_4_TYPE)
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_MULTI_BRI_4_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
#endif
#endif
            else
#endif
            {
                ScalerColorPCMOutputGammaAdjust(enumSelRegion, (BYTE *)_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            }
            break;
#endif
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
        case _OUTGAMMA_CUBE_MAPPING:
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            ScalerColorPCMOutputGammaAdjust(enumSelRegion,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.pucTable,
                                            pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.ucBank);
#else
            ScalerColorOutputGammaAdjust(enumSelRegion,
                                         pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.pucTable,
                                         pstOutGammaSetting->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.ucBank);
            break;
#endif
#endif
        default:
            break;
    }
}

#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Circle Window Adjust
// Input Value  : pstCircleWindowData, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorIPCircleWindowAdjust(StructColorCircleWindowSetting *pstCircleWindowData, EnumDBApply enumDBApply)
{
    ScalerColorPIPBlendingSetCircleWindow(pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.usHCenter,
                                          pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.usVCenter,
                                          pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.usHStart,
                                          pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.usVStart);
    ScalerColorPIPBlendingSetCircleWindowBorder(pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.usBorder_HStart,
                                                pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.usBorder_VStart);

    // When Circle Window need to turn off border window & turn on hlw
    // Circle window border color refers to hlw border rgb setting, not border window rgb setting.
    if((pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.b1CircleWindowEn == _ON) && (pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWidth != 0))
    {
#if(_COLOR_IP_HL_WIN == _ON)
        ScalerColorHLWBorderAdjust(pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWidth,
                                   pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowRed,
                                   pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowGreen,
                                   pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowBlue, _DB_APPLY_NONE);
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
        ScalerColorBorderEnable(_BORDER_WIN1, 0, 0, 0, 0, _DB_APPLY_NONE);
        ScalerColorBorderEnable(_BORDER_WIN2, 0, 0, 0, 0, _DB_APPLY_NONE);
#endif
    }
    ScalerColorPIPBlendingSetCircleWindowEnable(pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.b1CircleWindowEn,
                                                pstCircleWindowData->stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWidth);

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_1, enumDBApply);
}
#endif
#endif
