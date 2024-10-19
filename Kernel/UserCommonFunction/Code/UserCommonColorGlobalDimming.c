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
// ID Code      : UserCommonColorGlobalDimming.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_GLOBAL_DIMMING__

#include "UserCommonInclude.h"
#include "ColorGlobalDimming/UserCommonColorGlobalDimming.h"

#if(_GLOBAL_DIMMING_FUNCTION == _ON)

#ifdef __C51__
#pragma OT(8)
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
WORD code tGDHDRToneMappingLv540[256] =
{
#include _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540
};

WORD code tGDHDR2084Lv[256] =
{
#include _GLOBAL_DIMMING_HDR_2084_LV
};

#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
WORD code tGDHDR2084Lv_PWM[256] =
{
#include _GLOBAL_DIMMING_HDR_2084_LV_PWM
};

WORD code tGDHDRToneMappingLv540_PWM[256] =
{
#include _GLOBAL_DIMMING_HDR_TM_LV540_PWM
};
#endif

WORD code tGDSDRGamma22Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_GAMMA_22_LV
};

WORD code tGDSDRGamma24Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_GAMMA_24_LV
};

WORD code tGDSDRGamma26Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_GAMMA_26_LV
};

WORD code tGDSDROGCCase1Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV
};

WORD code tGDSDROGCCase2Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV
};

WORD code tGDSDROGCCase3Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV
};

WORD code tGDSDROGCCase4Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV
};

WORD code tGDSDROGCCase5Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV
};

WORD code tGDSDROGCCase6Lv[256] =
{
#include _GLOBAL_DIMMING_SDR_OGC_CASE_6_LV
};

WORD code tStepRTable[256] =
{
#include _GLOBAL_DIMMING_STEP_R_TABLE
};


#if((_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE) || (_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON))
WORD code tGDPWMLUT[_GLOBAL_DIMMING_PANEL_PWM_MAX + 1] =
{
#include _GLOBAL_DIMMING_PWM_LUT_TABLE
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usColorGDLastDCRMaxY = 255;
WORD g_usColorGDDCRToLV;
#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
WORD g_usColorGDDCRToLV_PWM;
#endif
WORD g_usColorGDApplyLV;
WORD g_usColorGDLastApplyLV = _GLOBAL_DIMMING_PANEL_LV_MAX;
WORD g_usColorGDApplyPWM;
WORD g_usColorLastApplyPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;
WORD g_usColorGDLastDeltaPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;
WORD g_usColorGDR;
WORD g_usColorLastGainValue = 0x200;
BYTE g_pucColorSRGBMatrixHalf[24];
WORD g_usColorGDLastBlackPer;
WORD g_usColorGDCurrentBlackPer;
#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
BYTE g_ucColorOnlineTable;
#endif
bit g_bColorSRGBForceMain = _FALSE;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorGlobalDimmingHandler(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

    if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
    {
#if(_GLOBAL_DIMMING_PATTERN_ESTIMATE == _ON)
        ScalerMeasureGlobalDimmingPatternEstimateStart();
#endif

        UserCommonColorGlobalDimmingProcess();
    }
}

//--------------------------------------------------
// Description  : Judge Global Dimming ON or OFF
// Input Value  : None
// Output Value : GD_ENABLE OR GD_DISABLE
//--------------------------------------------------
EnumGlobalDimmingStatus UserCommonColorGlobalDimmingGetEnableStatus(void)
{
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;

    enumDisplayRegion = enumDisplayRegion;

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
    if(GET_ON_LINE_GD_HDR_CALIBRATION_STATUS() == _ON)
    {
        return _GLOBAL_DIMMING_ENABLE;
    }
#endif
#endif

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            break;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
            break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif
        default:
            return _GLOBAL_DIMMING_DISABLE;
    }


#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
    {
        return _GLOBAL_DIMMING_DISABLE;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(enumDisplayRegion) == _ON)
    {
        return _GLOBAL_DIMMING_DISABLE;
    }
#endif

#if(_COLOR_DEMO_FUNCTION == _ON)
    if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
    {
        return _GLOBAL_DIMMING_DISABLE;
    }
#endif

    if((UserInterfaceColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE) &&
       (GET_ON_LINE_CALIBRATION_STATUS() == _CALIBRATION_OFF))
    {
#if(_HDR10_SUPPORT == _ON)
        EnumHDR10Status enumHDR10Status = UserCommonColorHDRGetHDR10Status(enumDisplayRegion);

        if(enumHDR10Status == _HDR10_ON)
        {
            return _GLOBAL_DIMMING_ENABLE;
        }
#if(_HLG_SUPPORT == _ON)
        else if(enumHDR10Status == _HLG_ON)
        {
            return _GLOBAL_DIMMING_DISABLE;
        }
#endif
        else
#endif
        {
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
            if(UserCommonColor3DGammaCubeGetEnableStatus((EnumSelRegion)enumDisplayRegion) == _FUNCTION_ON)
            {
                return _GLOBAL_DIMMING_DISABLE;
            }
#endif
            if(UserInterfaceColorSDROCCOGCMode() == _SDR_CALIBRATION_BY_OGC_TOOL)
            {
                return _GLOBAL_DIMMING_ENABLE;
            }
            else
            {
                return _GLOBAL_DIMMING_DISABLE;
            }
        }
    }
    return _GLOBAL_DIMMING_DISABLE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorGlobalDimmingProcess(void)
{
    WORD usDCRMaxY = 0x0000;
    UserCommonColorGlobalDimmingBlackPerCal();
#if(_GLOBAL_DIMMING_DARK_SENSITIVITY_SUPPORT == _ON)
    if(g_usColorGDCurrentBlackPer < _GLOBAL_DIMMING_ACTIVE_THD)
    {
        usDCRMaxY = 255;
    }
    else
#endif
    {
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_0)
#if(_HW_DCR_BIT == _DCR_8BIT)
        usDCRMaxY = ScalerColorDCRReadResult_8BIT(_DCR_Y_MAX_VAL);
#elif(_HW_DCR_BIT == _DCR_10BIT)
        usDCRMaxY = ScalerColorDCRReadResult_10BIT(_DCR_Y_MAX_VAL);
        usDCRMaxY = (usDCRMaxY >> 2);
#endif
#endif

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
        WORD usDCRMaxR = 0x0000;
        WORD usDCRMaxG = 0x0000;
        WORD usDCRMaxB = 0x0000;

#if(_HW_DCR_BIT == _DCR_8BIT)
        usDCRMaxR = ScalerColorDCRReadResult_8BIT(_DCR_HIGH_LV_VAL_R);
        usDCRMaxG = ScalerColorDCRReadResult_8BIT(_DCR_HIGH_LV_VAL_G);
        usDCRMaxB = ScalerColorDCRReadResult_8BIT(_DCR_HIGH_LV_VAL_B);
        usDCRMaxY = MAXOF(usDCRMaxR, usDCRMaxG);
        usDCRMaxY = MAXOF(usDCRMaxY, usDCRMaxB);
#elif(_HW_DCR_BIT == _DCR_10BIT)
        usDCRMaxR = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_R);
        usDCRMaxG = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_G);
        usDCRMaxB = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_B);
        usDCRMaxY = MAXOF(usDCRMaxR, usDCRMaxG);
        usDCRMaxY = MAXOF(usDCRMaxY, usDCRMaxB);

        usDCRMaxY = (usDCRMaxY >> 2);
#endif
#endif
    }

    UserCommonColorGlobalDimmingDCRToLv(usDCRMaxY, &g_usColorGDDCRToLV);
    DebugMessageHDR("usDCRMaxY", usDCRMaxY);
    DebugMessageHDR("g_usColorGDDCRToLV", g_usColorGDDCRToLV);
    UserCommonColorGlobalDimmingStepToTarget(&g_usColorGDApplyLV, &g_usColorGDDCRToLV, &g_usColorGDLastApplyLV, usDCRMaxY, &g_usColorGDLastDCRMaxY);
    DebugMessageHDR("g_usColorGDApplyLV", g_usColorGDApplyLV);
    UserCommonColorGlobalDimmingSetGainValue();
    UserCommonColorGlobalDimmingCalPWMValue(g_usColorGDApplyLV);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorGlobalDimmingDCRToLv(WORD usDCRMaxY, WORD *pusDCRToLV)
{
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
    if(GET_ON_LINE_GD_HDR_CALIBRATION_STATUS() == _ON)
    {
        *pusDCRToLV = tGDHDR2084Lv[usDCRMaxY];
#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
        g_usColorGDDCRToLV_PWM = tGDHDR2084Lv_PWM[usDCRMaxY];
#endif
        return;
    }
#endif
#endif

    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;


    enumDisplayRegion = enumDisplayRegion;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
        WORD usLightEnhanceCode = 0;
        BYTE ucGainValue = UserInterfaceColorHDRGetHDR10LightEnhanceGain(enumDisplayRegion);

        if(ucGainValue > 160)
        {
            ucGainValue = 160;
        }
        else if(ucGainValue < 100)
        {
            ucGainValue = 100;
        }

        usLightEnhanceCode = (usDCRMaxY * ucGainValue / 100);
        if(usLightEnhanceCode > 255)
        {
            usLightEnhanceCode = 255;
        }
        usDCRMaxY = usLightEnhanceCode;
#endif
        if(UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion) == _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
        {
            *pusDCRToLV = tGDHDR2084Lv[usDCRMaxY];
#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
            g_usColorGDDCRToLV_PWM = tGDHDR2084Lv_PWM[usDCRMaxY];
#endif
        }
        else
        {
            *pusDCRToLV = tGDHDRToneMappingLv540[usDCRMaxY];
#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
            g_usColorGDDCRToLV_PWM = tGDHDRToneMappingLv540_PWM[usDCRMaxY];
#endif
        }
    }
    else
#endif
    {
        StructColorInGammaSetting stInGamma = {0};
        UserCommonColorGetInGammaData(_1P_NORMAL_REGION, &stInGamma);

        if(stInGamma.stInGammaSetting.enumInGammaMode == _INGAMMA_PCM)
        {
            switch(stInGamma.stInGammaSetting.unInGammaData.stInGammaPCMData.enumPCMMode)
            {
                case _PCM_SRGB:
                case _PCM_ADOBE_RGB:

                    *pusDCRToLV = tGDSDRGamma22Lv[usDCRMaxY];
                    break;

                case _PCM_EBU_MODE:
                case _PCM_REC_709:

                    *pusDCRToLV = tGDSDRGamma24Lv[usDCRMaxY];
                    break;

                case _PCM_DCI_P3:

                    *pusDCRToLV = tGDSDRGamma26Lv[usDCRMaxY];
                    break;

                default:
                    break;
            }
        }
        else if(stInGamma.stInGammaSetting.enumInGammaMode == _INGAMMA_OGC)
        {
            switch(stInGamma.stInGammaSetting.unInGammaData.stInGammaOGCData.enumOGCType)
            {
                case _OGC_MODE1:
                    *pusDCRToLV = tGDSDROGCCase1Lv[usDCRMaxY];
                    break;

                case _OGC_MODE2:

                    *pusDCRToLV = tGDSDROGCCase2Lv[usDCRMaxY];
                    break;

                case _OGC_MODE3:

                    *pusDCRToLV = tGDSDROGCCase3Lv[usDCRMaxY];
                    break;

                case _OGC_MODE4:

                    *pusDCRToLV = tGDSDROGCCase4Lv[usDCRMaxY];
                    break;

                case _OGC_MODE5:

                    *pusDCRToLV = tGDSDROGCCase5Lv[usDCRMaxY];
                    break;

                case _OGC_MODE6:
                    *pusDCRToLV = tGDSDROGCCase6Lv[usDCRMaxY];
                    break;

                default:
                    break;
            }
        }
        else
        {
            *pusDCRToLV = tGDSDRGamma22Lv[usDCRMaxY];
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorGlobalDimmingStepToTarget(WORD *pusApplyLv, WORD *pusTargetLv, WORD *pusLastApplyLv, WORD usDCRResult, WORD *pusLastDCRResult)
{
    if(usDCRResult > *pusLastDCRResult)
    {
#if(_GLOBAL_DIMMING_DARK_SENSITIVITY_SUPPORT == _ON)
        if(g_usColorGDLastBlackPer >= _GLOBAL_DIMMING_ONE_STEP_THD)
        {
            g_usColorGDR = 1024;
            DebugMessageHDR("one step", 0x00);
        }
        else
#endif
        {
            if((*pusTargetLv - *pusLastApplyLv) == (tGDHDRToneMappingLv540[255] - tGDHDRToneMappingLv540[0]))
            {
                g_usColorGDR = 1024;
            }
            else
            {
                g_usColorGDR = tStepRTable[usDCRResult - *pusLastDCRResult];
            }
        }
    }
    else
    {
#if(_FREESYNC_II_SUPPORT == _ON)
        if((UserCommonDrrGetType() == _DRR_FREESYNC_TYPE) &&
           (g_usColorGDLastBlackPer >= _GLOBAL_DIMMING_ONE_STEP_THD) &&
           (usDCRResult == 0) &&
           (*pusLastApplyLv == tGDHDR2084Lv[255]))
        {
            g_usColorGDR = 1024;
        }
        else
#endif
        {
            g_usColorGDR = tStepRTable[(*pusLastDCRResult) - usDCRResult];
        }
    }

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
    if(GET_ON_LINE_GD_HDR_CALIBRATION_STATUS() == _ON)
    {
        g_usColorGDR = 1024;
    }
#endif
#endif

    *pusApplyLv = ((((DWORD)g_usColorGDR * *pusTargetLv) + ((DWORD)(1024 - g_usColorGDR) * *pusLastApplyLv)) + 512) / 1024;

    if(*pusApplyLv == *pusLastApplyLv)
    {
        if((*pusApplyLv > *pusTargetLv) && (*pusApplyLv != 0))
        {
            *pusApplyLv = *pusApplyLv - 1;
        }
        else if(*pusApplyLv < *pusTargetLv)
        {
            *pusApplyLv = *pusApplyLv + 1;
        }
    }

    *pusLastApplyLv = *pusApplyLv;
    *pusLastDCRResult = usDCRResult;
}

//--------------------------------------------------
// Description  : Set driver PWM
// Input Value  : Panel Apply PWM
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingCalPWMValue(WORD usApplyLv)
{
    WORD usPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;
    WORD usMaxDelPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;

#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
    enumDisplayRegion = enumDisplayRegion;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif


#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        usApplyLv = g_usColorGDDCRToLV_PWM;
    }
#endif
#endif
#endif

    usPWM = ((DWORD)(usApplyLv) * _GLOBAL_DIMMING_PANEL_PWM_MAX) / _GLOBAL_DIMMING_PANEL_LV_MAX;


    if(usPWM > _GLOBAL_DIMMING_PANEL_PWM_MAX)
    {
        usPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;
    }
    else if(usPWM < _GLOBAL_DIMMING_PANEL_PWM_MIN)
    {
        usPWM = _GLOBAL_DIMMING_PANEL_PWM_MIN;
    }

    usMaxDelPWM = ((((DWORD)g_usColorGDR * usPWM) + ((DWORD)(1024 - g_usColorGDR) * g_usColorLastApplyPWM))) / 1024;

    if(usMaxDelPWM == g_usColorLastApplyPWM)
    {
        if((usMaxDelPWM > usPWM) && (usMaxDelPWM > _GLOBAL_DIMMING_PANEL_PWM_MIN))
        {
            usMaxDelPWM = usMaxDelPWM - 1;
        }
        else if(usMaxDelPWM < usPWM)
        {
            usMaxDelPWM = usMaxDelPWM + 1;
        }
    }

    if(usPWM > g_usColorLastApplyPWM)
    {
        if(usPWM > usMaxDelPWM)
        {
            usPWM = usMaxDelPWM;
        }
    }
    else
    {
        if(usPWM < usMaxDelPWM)
        {
            usPWM = usMaxDelPWM;
        }
    }

    g_usColorLastApplyPWM = usPWM;

    UserCommonColorGlobalDimmingSetPWMValue(UserCommonColorGlobalDimmingGetPWMTableValue(usPWM));
    DebugMessageHDR("usPWM", usPWM);
}

//--------------------------------------------------
// Description  : Global dimming initial setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingInitialSetting(bit bEn)
{
    BYTE pucSRGBMatrixOriginal[18] = {0};
    SWORD shSRGBValueOriginal = 0;
    SWORD shDiagoanlValueHalf = 0;
    BYTE ucI = 0;
    BYTE ucDecimalNum = 0;
    BYTE ucShiftNum = 0;
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;

    StructColorSRGBSetting stSRGB = {0};

    UserCommonColorGetsRGBData(_1P_NORMAL_REGION, &stSRGB);

    // global variable
    g_usColorGDLastDCRMaxY = 255;
    g_usColorGDLastApplyLV = _GLOBAL_DIMMING_PANEL_LV_MAX;
    g_usColorLastApplyPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;
    g_usColorGDLastDeltaPWM = _GLOBAL_DIMMING_PANEL_PWM_MAX;
    g_usColorLastGainValue = _GLOBAL_DIMMING_MIN_GAIN;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif
    switch(ScalerColorSRGBGetPrecision((EnumSelRegion)enumDisplayRegion))
    {
        case _SRGB_0_BIT_SHIFT_LEFT:
            ucDecimalNum = 12;
            break;
        case _SRGB_3_BIT_SHIFT_LEFT:
            ucDecimalNum = 9;
            break;
        case _SRGB_2_BIT_SHIFT_LEFT:
            ucDecimalNum = 10;
            break;
        default:
        case _SRGB_1_BIT_SHIFT_LEFT:
            ucDecimalNum = 11;
            break;
    }
    // SRGB
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        WORD usHDRColorMatrixFlashAddress = UserCommonColorHDRGetHDR10ColorMatrixAddress(UserCommonColorHDRGetHDR10ColorMatrix(enumDisplayRegion));
        UserCommonFlashRead(_OGC_FLASH_BANK, usHDRColorMatrixFlashAddress, 18, pucSRGBMatrixOriginal);
    }
    else
#endif
    {
        StructColorInGammaSetting stInGamma = {0};
        UserCommonColorGetInGammaData(_1P_NORMAL_REGION, &stInGamma);
        if(stInGamma.stInGammaSetting.enumInGammaMode == _INGAMMA_PCM)
        {
            UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_SRGBMATRIX_ADDRESS + (_OCC_COLORMATRIX_TABLE_SIZE * stSRGB.stSRGBSetting.unSRGBData.stSRGBPCMData.enumPCMMode), 18, pucSRGBMatrixOriginal);
        }
    }

#if(_HDR10_SUPPORT == _ON)
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
    if(GET_ON_LINE_GD_HDR_CALIBRATION_STATUS() == _ON)
    {
        WORD usHDRColorMatrixFlashAddress = UserCommonColorHDRGetHDR10ColorMatrixAddress(_HDR10_COLOR_MATRIX_BT2020);
        UserCommonFlashRead(_OGC_FLASH_BANK, usHDRColorMatrixFlashAddress, 18, pucSRGBMatrixOriginal);
    }
#endif
#endif
#endif

    ucShiftNum = (ucDecimalNum - 9);

    if(bEn == _ENABLE)
    {
        for(ucI = 0; ucI < 9; ucI++)
        {
            SWORD shValue = (((WORD)(pucSRGBMatrixOriginal[2 * ucI] & 0x01) << 15) |
                             ((WORD)pucSRGBMatrixOriginal[(2 * ucI) + 1] << 7) |
                             ((pucSRGBMatrixOriginal[2 * ucI] & 0xE0) >> 1));
            shValue >>= 4;

            shSRGBValueOriginal = (shValue + (ucShiftNum >> 1)) >> ucShiftNum;

            if((ucI % 4) == 0)
            {
                shDiagoanlValueHalf = ((shSRGBValueOriginal + 0x201) >> 1) - 0x200;
            }
            else
            {
                shDiagoanlValueHalf = (shSRGBValueOriginal + 1) >> 1;
            }
            g_pucColorSRGBMatrixHalf[2 * ucI] = ((shDiagoanlValueHalf & 0x07) << 5) | ((shDiagoanlValueHalf >> 11) & 0x01);
            g_pucColorSRGBMatrixHalf[2 * ucI + 1] = (shDiagoanlValueHalf >> 3) & 0xFF;
        }
        // SRGB
        if(g_bColorSRGBForceMain == _TRUE)
        {
            ScalerColorSRGBAdjust(_FULL_REGION, g_pucColorSRGBMatrixHalf, _SRGB_3_BIT_SHIFT_LEFT);
        }
        else
        {
            ScalerColorSRGBAdjust(_1P_NORMAL_REGION, g_pucColorSRGBMatrixHalf, _SRGB_3_BIT_SHIFT_LEFT);
        }
    }
    else
    {
        ScalerColorIPSRGBAdjust(_1P_NORMAL_REGION, &stSRGB);
    }

    // for Black percentage
    g_usColorGDLastBlackPer = 0;
    g_usColorGDCurrentBlackPer = 0;

#if(_GLOBAL_DIMMING_PATTERN_ESTIMATE == _ON)
    ScalerMeasureGlobalDimmingPatternEstimateInitial();
#endif
#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _GD_FINISH_ADDRESS, 1, &g_ucColorOnlineTable);
#endif
}


//--------------------------------------------------
// Description  :Apply Gain Value
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingSetGainValue(void)
{
    WORD usGainValue = 0;
    WORD usApplyGainValue = 0;
    BYTE pucSRGBMatrix[24] = {0};
    BYTE ucI = 0;

#if(_GLOBAL_DIMMING_DARK_MODE_SUPPORT == _ON)
    if(g_usColorGDApplyLV < _GLOBAL_DIMMING_DARK_MODE_THD)
    {
        WORD usGap = _GLOBAL_DIMMING_DARK_MODE_THD - _GLOBAL_DIMMING_DARK_MODE_MIN;
        if(g_usColorGDApplyLV < _GLOBAL_DIMMING_DARK_MODE_MIN)
        {
            g_usColorGDApplyLV = _GLOBAL_DIMMING_DARK_MODE_MIN;
        }
        usGainValue = (1 + 4 * (g_usColorGDApplyLV - _GLOBAL_DIMMING_DARK_MODE_MIN) / (usGap)) << 9;
    }
    else
#endif
    {
        if(g_usColorGDApplyLV == 0)
        {
            usGainValue = _GLOBAL_DIMMING_MAX_GAIN;
        }
        else
        {
            usGainValue = (((DWORD)_GLOBAL_DIMMING_PANEL_LV_MAX << 9) / g_usColorGDApplyLV);
        }
    }




    usApplyGainValue = ((((DWORD)g_usColorGDR * usGainValue) + ((DWORD)g_usColorLastGainValue * (1024 - g_usColorGDR))) + 512) / 1024;

    if(usApplyGainValue == g_usColorLastGainValue)
    {
        if(usApplyGainValue < usGainValue)
        {
            usApplyGainValue = usApplyGainValue + 1;
        }
        else if((usApplyGainValue > usGainValue) && (usApplyGainValue > 512))
        {
            usApplyGainValue = usApplyGainValue - 1;
        }
    }

    usApplyGainValue = (usApplyGainValue > _GLOBAL_DIMMING_MAX_GAIN) ? _GLOBAL_DIMMING_MAX_GAIN : usApplyGainValue;
    usApplyGainValue = (usApplyGainValue < _GLOBAL_DIMMING_MIN_GAIN) ? _GLOBAL_DIMMING_MIN_GAIN : usApplyGainValue;


    DebugMessageHDR("usApplyGainValue", usApplyGainValue);

    g_usColorLastGainValue = usApplyGainValue;

    for(ucI = 0; ucI < 9; ucI++)
    {
        SDWORD lSRGBApplylValue = 0;
        SWORD shValue = (((WORD)(g_pucColorSRGBMatrixHalf[2 * ucI] & 0x01) << 15) |
                         ((WORD)g_pucColorSRGBMatrixHalf[(2 * ucI) + 1] << 7) |
                         ((g_pucColorSRGBMatrixHalf[2 * ucI] & 0xE0) >> 1));
        shValue >>= 4;

        if((ucI % 4) == 0)
        {
            lSRGBApplylValue = (((SDWORD)shValue * (SDWORD)usApplyGainValue + 0x100) >> 9) +
                               ((((SDWORD)usApplyGainValue * 0x200) + 0x100) >> 9) - 0x200;
        }
        else
        {
            lSRGBApplylValue = ((SDWORD)shValue * (SDWORD)usApplyGainValue + 0x100) >> 9;
        }
        if(lSRGBApplylValue > _GLOBAL_DIMMING_SRGB_MAX)
        {
            DebugMessageHDR("lSRGBApplylValue", lSRGBApplylValue);
            lSRGBApplylValue = _GLOBAL_DIMMING_SRGB_MAX;
        }
        pucSRGBMatrix[2 * ucI] = ((lSRGBApplylValue & 0x07) << 5) | ((lSRGBApplylValue >> 11) & 0x01);
        pucSRGBMatrix[2 * ucI + 1] = (lSRGBApplylValue >> 3) & 0xFF;
    }
    if(g_bColorSRGBForceMain == _TRUE)
    {
        ScalerColorSRGBAdjust(_FULL_REGION, pucSRGBMatrix, _SRGB_3_BIT_SHIFT_LEFT);
    }
    else
    {
        ScalerColorSRGBAdjust(_1P_NORMAL_REGION, pucSRGBMatrix, _SRGB_3_BIT_SHIFT_LEFT);
    }
}

//--------------------------------------------------
// Description  : Enable Global Dimming Function in OSD
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingAdjust(void)
{
    StructColorDCRSetting stUnionDCR = {0};
    UserCommonColorGlobalDimmingSetForceMainEffect();
    if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
    {
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
        if(GET_ON_LINE_GD_HDR_CALIBRATION_STATUS() == _ON)
        {
            StructColorInGammaSetting stInGamma = {0};
            StructColorOutGammaSetting stOutGamma = {0};
            StructColorSRGBSetting stSRGB = {0};
            stInGamma.stInGammaSetting.enumInGammaMode = _INGAMMA_HDR10_AUTO;
            stOutGamma.stOutGammaSetting.enumOutGammaMode = _OUTGAMMA_HDR10;
            stSRGB.stSRGBSetting.enumSRGBMode = _SRGB_HDR10_AUTO;
            ScalerColorIPInGammaAdjust(_1P_NORMAL_REGION, &stInGamma, _IG_DB_DISABLE);
            ScalerColorIPSRGBAdjust(_1P_NORMAL_REGION, &stSRGB);
            ScalerColorIPOutGammaAdjust(_1P_NORMAL_REGION, &stOutGamma);
        }
        else
#endif
#endif
        {
            if(g_bColorSRGBForceMain == _TRUE)
            {
                UserCommonColorPCMAdjust(_FULL_REGION, _DB_APPLY_NO_POLLING);
            }
            else
            {
                UserCommonColorPCMAdjust(_1P_NORMAL_REGION, _DB_APPLY_NO_POLLING);
            }
        }
        UserCommonColorGlobalDimmingInitialSetting(_ENABLE);
    }
    else
    {
        if(g_bColorSRGBForceMain == _TRUE)
        {
            UserCommonColorPCMAdjust(_FULL_REGION, _DB_APPLY_NO_POLLING);
            UserInterfaceColorGlobalDimmingRestoreBacklight();
        }
        else
        {
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
#if(_COLOR_DEMO_FUNCTION == _ON)
                switch(UserCommonColorGetDemoModeType())
                {
                    case _DEMO_MODE_BOTH:
                        UserCommonColorPCMAdjust(_DEMO_INSIDE, _DB_APPLY_NO_POLLING);
                        UserCommonColorPCMAdjust(_DEMO_OUTSIDE, _DB_APPLY_NO_POLLING);
                        break;
                    case _DEMO_MODE_OUTSIDE:
                        UserCommonColorPCMAdjust(_DEMO_OUTSIDE, _DB_APPLY_NO_POLLING);
                        break;
                    case _DEMO_MODE_INSIDE:
                        UserCommonColorPCMAdjust(_DEMO_INSIDE, _DB_APPLY_NO_POLLING);
                        break;
                    case _DEMO_OFF:
                        UserCommonColorPCMAdjust(_1P_NORMAL_REGION, _DB_APPLY_NO_POLLING);
                        break;
                    default:
                        break;
                }
#else
                UserCommonColorPCMAdjust(_1P_NORMAL_REGION, _DB_APPLY_NO_POLLING);
#endif
                UserInterfaceColorGlobalDimmingRestoreBacklight();
            }
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            else if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
            {
                UserCommonColorPCMAdjust(_2P_PIP_EAGLE_SIGHT_MAIN, _DB_APPLY_NO_POLLING);
                UserCommonColorPCMAdjust(_2P_PIP_EAGLE_SIGHT_SUB, _DB_APPLY_NO_POLLING);
                UserInterfaceColorGlobalDimmingRestoreBacklight();
            }
#endif
        }
    }

    UserCommonColorGetDCRData(&stUnionDCR);
    ScalerColorIPDCRAdjust(&stUnionDCR);
}

//--------------------------------------------------
// Description  : Set PWM value
// Input Value  : PWM value, 0~2048
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingSetPWMValue(WORD usPWM)
{
    UserInterfaceColorGlobalDimmingAdjustPWM(usPWM);
}

//--------------------------------------------------
// Description  : Cacualte black percentage for current frame and last frmae
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingBlackPerCal(void)
{
    DWORD ulpanelsize = 0;
    DWORD ulCurrentTotalBlack = 0;
    g_usColorGDLastBlackPer = g_usColorGDCurrentBlackPer;
    ulpanelsize = ((DWORD)_PANEL_DH_WIDTH) * ((DWORD)_PANEL_DV_HEIGHT);

#if(_HW_DCR_BIT == _DCR_10BIT)
    ulCurrentTotalBlack = ulpanelsize - ScalerColorDCRReadResult_10BIT(_DCR_ABOVE_TH1_NUM);
#elif(_HW_DCR_BIT == _DCR_8BIT)
    ulCurrentTotalBlack = ulpanelsize - ScalerColorDCRReadResult_8BIT(_DCR_ABOVE_TH1_NUM);
#endif
    g_usColorGDCurrentBlackPer = GET_DWORD_MUL_DIV(ulCurrentTotalBlack, 1000, ulpanelsize);

    DebugMessageHDR("ulCurrentTotalBlack", ulCurrentTotalBlack);
    DebugMessageHDR("ulpanelsize", ulpanelsize);
    DebugMessageHDR("g_usColorGDCurrentBlackPer", g_usColorGDCurrentBlackPer);
    DebugMessageHDR("g_usColorGDLastBlackPer", g_usColorGDLastBlackPer);
}

//--------------------------------------------------
// Description  : Get Kernel apply gain to user
// Input Value  : Kernel apply gain
// Output Value : Apply gain: 100~ 500
//--------------------------------------------------
WORD UserCommonColorGlobalDimmingGetMainApplyGain(void)
{
    WORD usMaxGain = (DWORD)_GLOBAL_DIMMING_MAX_GAIN * 100 / _GLOBAL_DIMMING_MIN_GAIN;
    WORD usMinGain = 100;
    WORD usUserGain = _GLOBAL_DIMMING_MIN_GAIN;

    usUserGain = ((DWORD)(g_usColorLastGainValue - _GLOBAL_DIMMING_MIN_GAIN) * (usMaxGain - usMinGain) / (_GLOBAL_DIMMING_MAX_GAIN - _GLOBAL_DIMMING_MIN_GAIN) + usMinGain);

    return usUserGain;
}

//--------------------------------------------------
// Description  : Judge sub force main parameter by global variable
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorGlobalDimmingSetForceMainEffect(void)
{
    g_bColorSRGBForceMain = _FALSE;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    StructColorSRGBSetting stEagleSightSubSRGB = {0};
    StructColorSRGBSetting stEagleSightMainSRGB = {0};
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        UserCommonColorGetsRGBData(_2P_PIP_EAGLE_SIGHT_MAIN, &stEagleSightSubSRGB);
        UserCommonColorGetsRGBData(_2P_PIP_EAGLE_SIGHT_SUB, &stEagleSightMainSRGB);
        if(stEagleSightSubSRGB.stSRGBSetting.enumSRGBMode != stEagleSightMainSRGB.stSRGBSetting.enumSRGBMode)
        {
            g_bColorSRGBForceMain = _FALSE;
        }
    }
    else
#endif
    {
        if(UserInterfaceColorGlobalDimmingGetForceMainEffect() == _GLOBAL_DIMMING_SUB_FORCE_MAIN)
        {
            g_bColorSRGBForceMain = _TRUE;
        }
    }
}



#if(_GLOBAL_DIMMING_PATTERN_ESTIMATE == _ON)
//--------------------------------------------------
// Description  : Cacualte black percentage for current frame and last frmae
// Input Value  : void
// Output Value : void
//--------------------------------------------------
bit UserCommonColorGlobalDimmingPatternEstimate(EnumGDPatternType enumPatternType)
{
    bit bStatus = _FALSE;

    switch(enumPatternType)
    {
        case _GD_PATTERN_MIDDLE_BLACK:
            if((g_usColorGDCurrentBlackPer > 850) &&
               (g_usColorGDCurrentBlackPer < 950) &&
               (g_usColorGDDCRToLV == tGDHDR2084Lv[255]))
            {
                if(ScalerMeasureGlobalDimmingPatternEstimateGetResult(_AUTO_GREEN_CHANNEL) < 2)
                {
                    bStatus = _TRUE;
                }
            }
            break;

        default:
            break;
    }

    return bStatus;
}
#endif

#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Word from calibration data in flash
// Input Value  : BYTE ucBank, BYTE ucPage, WORD usStartAddress, WORD usIndex, BYTE bSwap
// Output Value : WORD data
//--------------------------------------------------
WORD UserCommonColorGlobalDimmingGetWordFromFlash(BYTE ucBank, BYTE ucPage, WORD usStartAddress, WORD usIndex, BYTE ucSwap)
{
    BYTE pucData[2] = {0};
    WORD usCombineData = 0;
    UserCommonFlashRead(ucBank, ((WORD)ucPage << 12) | (usStartAddress + 2 * usIndex), 2, pucData);
    if(ucSwap == _TRUE)
    {
        usCombineData = (pucData[0] << 8) | pucData[1];
    }
    else
    {
        usCombineData = (pucData[1] << 8) | pucData[0];
    }
    return usCombineData;
}
#endif
//--------------------------------------------------
// Description  : Get PWM LUT value
// Input Value  : WORD usOfflineValue, WORD usIndex
// Output Value : PWM LUT value
//--------------------------------------------------
WORD UserCommonColorGlobalDimmingGetPWMTableValue(WORD usIndex)
{
#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
    if(g_ucColorOnlineTable == _TRUE)
    {
        return UserCommonColorGlobalDimmingGetWordFromFlash(_OGC_FLASH_BANK, _OGC_FLASH_PAGE, _OCC_GLOBAL_DIMMING_PWMLUT_ADDRESS, usIndex, _TRUE);
    }
    else
#endif
    {
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
        return tGDPWMLUT[usIndex];
#else
        return usIndex;
#endif
    }
}
#endif // End of #if(_GLOBAL_DIMMING_SUPPORT == _ON)

