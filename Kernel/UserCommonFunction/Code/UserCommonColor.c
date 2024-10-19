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
// ID Code      : UserCommonColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_COLOR__

#include "UserCommonInclude.h"
#include "Color/UserCommonColor.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_UNIFORMITY_FUNCTION == _ON)

BYTE code tUniformityType[] =
{
    _UNIFORMITY_1ST_TABLE_LEVEL,
    _UNIFORMITY_2ND_TABLE_LEVEL,
    _UNIFORMITY_3RD_TABLE_LEVEL,
    _UNIFORMITY_4TH_TABLE_LEVEL,
    _UNIFORMITY_5TH_TABLE_LEVEL,
    _UNIFORMITY_6TH_TABLE_LEVEL,
    _UNIFORMITY_7TH_TABLE_LEVEL,
    _UNIFORMITY_8TH_TABLE_LEVEL,
    _UNIFORMITY_9TH_TABLE_LEVEL,
};
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
#if(_DM_FUNCTION == _ON)
#if((_HW_HSU_128TAPS_SUPPORT == _ON) || (_HW_VSU_128TAPS_SUPPORT == _ON))
BYTE code tSCALE_128TAPS_DM_COEF_TABLE[] =
{
    // If Dolby ON, user can use this table to bypass sharpness
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif

#if((_HW_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
BYTE code tSCALE_96TAPS_DM_COEF_TABLE[] =
{
    // If Dolby ON, user can use this table to bypass sharpness
    0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00,
    0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00,
    0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03,
    0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03, 0x64, 0x03,
    0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00,
    0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00, 0x4E, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif
#endif
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
BYTE code tCOLOR_LOCALCONTRAST_INITIAL_SETTING[] =
{
#include <Color/LocalContrast/LocalContrastTable_Initial_SDR.h>
};

#if(_HDR10_SUPPORT == _ON)
BYTE code tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_540[] =
{
#include <Color/LocalContrast/LocalContrastTable_Initial_HDR_540nits.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_1200[] =
{
#include <Color/LocalContrast/LocalContrastTable_Initial_HDR_1200nits.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_4000[] =
{
#include <Color/LocalContrast/LocalContrastTable_Initial_HDR_4000nits.h>
};

BYTE code tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_10000[] =
{
#include <Color/LocalContrast/LocalContrastTable_Initial_HDR_10000nits.h>
};
#endif
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructColorFunctionRegionEnable g_pstColorFunctionRegionEnable[3];
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
StructColorDynamicLowBlueSetting g_stColorDynamicLowBlueSetting;
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Quantization Range at HDR support
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
EnumRGBQuantLimitRangeStatus UserCommonColorGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization)
{
    enumDisplayRegion = enumDisplayRegion;

    switch(enumColorRGBQuantization)
    {
        case _RGB_QUANTIZATION_FULL_RANGE:
        case _RGB_QUANTIZATION_DEFAULT_RANGE:
        case _RGB_QUANTIZATION_RESERVED:
        default:

            return _RGB_QUANT_LIMIT_RANGE_FALSE;

        case _RGB_QUANTIZATION_LIMIT_RANGE:

            return _RGB_QUANT_LIMIT_RANGE_TRUE;
    }
}

//--------------------------------------------------
// Description  : Set RGB Quantization Range
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorRGBQuantizationRangeAdjust(EnumDisplayRegion enumDisplayRegion)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
    EnumColorRGBQuantization enumColorRGBQuantization = ScalerColorSpaceGetRGBQuantizationRange(enumInputPort);

#if(_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)
    EnumRGBQuantLimitRangeStatus enumRGBLimitRange = UserInterfaceColorGetRGBQuantizationLimitRangeStatus(enumDisplayRegion, enumColorRGBQuantization);
#else
    EnumRGBQuantLimitRangeStatus enumRGBLimitRange = UserCommonColorGetRGBQuantizationLimitRangeStatus(enumDisplayRegion, enumColorRGBQuantization);
#endif

    // Mapping to real Dx port
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
    enumInputPort = ScalerTmdsMacRxExternalHdmiPortMapping(enumInputPort);
#endif

    ScalerColorSpaceSetRGBLimitRange(enumInputPort, enumRGBLimitRange);
}
#endif // End of #if(_RGB_QUATIZATION_RANGE_SUPPORT == _ON)

#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Quantization Range at HDR support
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
EnumYccQuantFullRangeStatus UserCommonColorGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization)
{
    enumDisplayRegion = enumDisplayRegion;

    switch(enumColorYCCQuantization)
    {
        case _YCC_QUANTIZATION_FULL_RANGE:
        case _YCC_QUANTIZATION_RESERVED:
        default:

            return _YCC_QUANT_FULL_RANGE_TRUE;

        case _YCC_QUANTIZATION_LIMIT_RANGE:

            return _YCC_QUANT_FULL_RANGE_FALSE;
    }
}

//--------------------------------------------------
// Description  : Set YCC Quantization Range
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorYCCQuantizationRangeAdjust(EnumDisplayRegion enumDisplayRegion)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
    EnumColorYCCQuantization enumColorYCCQuantization = ScalerColorSpaceGetYCCQuantizationRange(enumInputPort);

#if(_YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)
    EnumYccQuantFullRangeStatus enumYCCFullRange = UserInterfaceColorGetYCCQuantizationFullRangeStatus(enumDisplayRegion, enumColorYCCQuantization);
#else
    EnumYccQuantFullRangeStatus enumYCCFullRange = UserCommonColorGetYCCQuantizationFullRangeStatus(enumDisplayRegion, enumColorYCCQuantization);
#endif

    // Mapping to real Dx port
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
    enumInputPort = ScalerTmdsMacRxExternalHdmiPortMapping(enumInputPort);
#endif

    ScalerColorSpaceSetYCCFullRange(enumInputPort, enumYCCFullRange);
}
#endif // End of #if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)

#if(_COLOR_IP_COLOR_CONVERT == _ON)
//--------------------------------------------------
// Description  : Specify Which Color Space is used
// Input Value  : Target Color Space, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorFormatConvert(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply)
{
#if(_VGA_SUPPORT == _ON)
    if(enumInputPort == _A0_INPUT_PORT)
    {
        ScalerVgaAdcClampMode(enumColorSpace);

        // Download adc data from NVRam
        UserCommonNVRamLoadADCSetting(enumColorSpace);

        // Gain Offset Adjust.
        UserCommonVgaAdcDataAdjust();
    }
#endif
#if(_COLOR_IP_DM == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
    {
        UserCommonColorSetColorFormatConvertDM(enumDisplayRegion, enumDBApply);
    }
    else
#endif
#endif
    {
        UserCommonColorSetColorFormatConvert(enumDisplayRegion, enumInputPort, enumColorSpace, enumDBApply);
    }
}

//--------------------------------------------------
// Description  : Return Color Format by User or Not
// Input Value  : display Region
// Output Value : Color Format
//--------------------------------------------------
EnumColorSpace UserCommonColorGetColorFormat(EnumDisplayRegion enumDisplayRegion)
{
    if(UserInterfaceColorGetColorRGBFormat(enumDisplayRegion) == _RGB_FORMAT_TRUE)
    {
        return _COLOR_SPACE_RGB;
    }
    else
    {
        return _COLOR_SPACE_YPBPR;
    }
}

//--------------------------------------------------
// Description  : Color Conversion Process Load D Domain Table
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorLoadYuv2RgbTable(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    ScalerColorSpaceLoadYuv2RgbTable(enumDisplayRegion, enumDBApply);
}

//--------------------------------------------------
// Description  : Color Conversion Process
// Input Value  : Target Color Space, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorSetColorFormatConvert(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply)
{
#if(_COLOR_IP_DM == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
    {
        return;
    }
#endif
#endif

    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    ScalerColorSpaceConvert(enumDisplayRegion, enumInputPort, enumColorSpace, enumDBApply);

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    EnumSelRegion enumSelRegion = UserCommonColorSpaceConvertNightSniperGetSelRegion(enumDisplayRegion);
    if(enumSelRegion != _NON_REGION)
    {
        ScalerColorSpaceConvertNightSniperEnable(enumSelRegion, UserCommonColorGetNightSniperEnableStatus(enumSelRegion), UserCommonColorGetNightSniperEnableStatus(UserCommonRegionGetInverse(enumSelRegion)), _OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : D Color Conversion Status
// Input Value  : Display Region
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
EnumFunctionOnOFF UserCommonColorSpaceConvertDDomainCheckEnableStatus(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerColorSpaceConvertDDomainCheckEnableStatus(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Color Space Conversion function On/Off
// Input Value  : Display Region, On/Off
// Output Value : None
//--------------------------------------------------
void UserCommonColorSpaceConvertDDomainEnable(EnumDisplayRegion enumDisplayRegion, bit bOn)
{
    ScalerColorSpaceConvertDDomainEnable(enumDisplayRegion, bOn);
}


#if(_COLOR_IP_DM == _ON)
//--------------------------------------------------
// Description  : Color Conversion Process for DM ON
// Input Value  : Target Color Space, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorSetColorFormatConvertDM(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    ScalerColorSpaceConvertDM(enumDisplayRegion, enumDBApply);
}
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Night Sniper EnumDisplayRegion transfer to EnumSelRegion
// Input Value  : enumDisplayRegion
// Output Value : EnumSelRegion
//--------------------------------------------------
EnumSelRegion UserCommonColorSpaceConvertNightSniperGetSelRegion(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumSelRegion = UserInterfaceColorGetOSDSystemSelRegion();

    switch(enumDisplayRegion)
    {
        // Night Sniper only support 1P/ES/PIP/PBPLR
        case _DISPLAY_RGN_1P:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PIP_MAIN:
        case _DISPLAY_RGN_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
        case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
        case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
        case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
        case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
#endif

            if((enumSelRegion != _DEMO_INSIDE) && (enumSelRegion != _DEMO_OUTSIDE))
            {
                return (EnumSelRegion)enumDisplayRegion;
            }
            else
            {
                return _NON_REGION;
            }

        default:
            return _NON_REGION;
    }
}

//--------------------------------------------------
// Description  : Set Night Sniper
// Input Value  : enumSelRegion, bOn
// Output Value : None
//--------------------------------------------------
void UserCommonColorSpaceConvertNightSniperEnable(EnumSelRegion enumSelRegion, bit bOn)
{
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE)
    {
        return;
    }
#endif
#endif

    bit bOn_Inverse = UserCommonColorGetNightSniperEnableStatus(UserCommonRegionGetInverse(enumSelRegion));

    if(enumSelRegion == _FULL_REGION) // _FULL_REGION always follow _FULL_REGION status
    {
        ScalerColorSpaceConvertNightSniperEnable(enumSelRegion, bOn, bOn, _ON);
    }
    else if((enumSelRegion == _DEMO_INSIDE) || (enumSelRegion == _DEMO_OUTSIDE)) // Not support demo inside/demo outside, always _OFF
    {
        ScalerColorSpaceConvertNightSniperEnable(enumSelRegion, _OFF, _OFF, _ON);
    }
    else if(GET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion) == _OFF) // multi-function flow _ON case should check inverse selregion
    {
        ScalerColorSpaceConvertNightSniperEnable(enumSelRegion, bOn, bOn_Inverse, _ON);
    }
    else // Non-multi-function flow
    {
        ScalerColorSpaceConvertNightSniperEnable(enumSelRegion, bOn, bOn_Inverse, _OFF);
    }
}
#endif

//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : enumInputPort -> input port
// Output Value : Input Color Depth
//--------------------------------------------------
BYTE UserCommonColorSpaceGetColorDepth(EnumInputPort enumInputPort)
{
    return ScalerColorGetColorDepth(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Colorimetry
// Input Value  : enumInputPort -> input port
// Output Value : EnumColorimetry
//--------------------------------------------------
EnumColorimetry UserCommonColorSpaceGetColorimetry(EnumInputPort enumInputPort)
{
    return ScalerColorSpaceGetColorimetry(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Ext Colorimetry
// Input Value  : enumInputPort -> input port
// Output Value : EnumColorimetryExt
//--------------------------------------------------
EnumColorimetryExt UserCommonColorSpaceGetExtColorimetry(EnumInputPort enumInputPort)
{
    return ScalerColorSpaceGetExtColorimetry(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Add Ext Colorimetry
// Input Value  : enumInputPort -> input port
// Output Value : EnumColorimetryAddExt
//--------------------------------------------------
EnumColorimetryAddExt UserCommonColorSpaceGetAddExtColorimetry(EnumInputPort enumInputPort)
{
    return ScalerColorSpaceGetAddExtColorimetry(enumInputPort);
}

//--------------------------------------------------
// Description  : Get RGB Quantization Limit Range
// Input Value  : enumInputPort -> input port
// Output Value : EnumColorRGBQuantization
//--------------------------------------------------
EnumColorRGBQuantization UserCommonColorSpaceGetRGBQuantizationRange(EnumInputPort enumInputPort)
{
    return ScalerColorSpaceGetRGBQuantizationRange(enumInputPort);
}

//--------------------------------------------------
// Description  : Get YCC Quantization Limit Range
// Input Value  : enumInputPort -> input port
// Output Value : EnumColorYCCQuantization
//--------------------------------------------------
EnumColorYCCQuantization UserCommonColorSpaceGetYCCQuantizationRange(EnumInputPort enumInputPort)
{
    return ScalerColorSpaceGetYCCQuantizationRange(enumInputPort);
}
#endif // End of #if(_COLOR_IP_COLOR_CONVERT == _ON)

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Let User Specify Which Color Space is used
// Input Value  : Target Color Space, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorColorFormatConvertAdjust(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply)
{
    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

#if(_3DDI_FUNCTION == _ON)
    Scaler3DDISetRGB2YUV(enumDisplayRegion, enumInputPort, enumColorSpace);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
    UserCommonColorFormatConvert(enumDisplayRegion, enumInputPort, enumColorSpace, _DB_APPLY_NONE);
    UserCommonColorDColorConvertAdjust((EnumSelRegion) enumDisplayRegion, _DB_APPLY_NONE);
    UserCommonColorColorConvertDBApply(enumDisplayRegion, enumDBApply);
#else
    UserCommonColorFormatConvert(enumDisplayRegion, enumInputPort, enumColorSpace, enumDBApply);
#endif
}
#endif

#if(_ULTRA_VIVID_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorUltraVividAdjust(EnumSelRegion enumSelRegion)
{
    StructColorUltraVividSetting stUltraVividData = {0};

    UserCommonColorGetUltraVividData(enumSelRegion, &stUltraVividData);

    if(GET_LSR_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    ScalerColorIPUltraVividAdjust(enumSelRegion, &stUltraVividData);

    if(stUltraVividData.stUltraVividSetting.enumUltraVividMode != _ULTRAVIVID_OFF)
    {
        if(GET_LSR_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorUltraVividRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
        else    // During Multi Function
        {
            UserCommonColorUltraVividRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }
    }
    else
    {
        if(GET_LSR_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorUltraVividRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
        }
    }
}
//--------------------------------------------------
// Description  : Set UltraVivid Region Enable
// Input Value  : enumSelRegion, enumDBApply, and bOn
// Output Value : None
//--------------------------------------------------
void UserCommonColorUltraVividEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorUltraVividRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
//--------------------------------------------------
// Description  : User Common function Adjust for UltraVivid
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetUltraVividData(EnumSelRegion enumSelRegion, StructColorUltraVividSetting *pstUltraVividData)
{
    UserInterfaceColorGetUltraVividData(enumSelRegion, &(pstUltraVividData->stUltraVividSetting));
}

//--------------------------------------------------
// Description  : Set UltraVivid Region Enable
// Input Value  : enumSelRegion, enumDBApply, and bOn
// Output Value : None
//--------------------------------------------------
void UserCommonColorUltraVividRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColorUltraVividRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif

#if(_COLOR_IP_DCR == _ON)
//--------------------------------------------------
// Description  : User Common DCR Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCRRegionAdjust(void)
{
    StructColorDCRSetting stDCR = {0};

    UserCommonColorGetDCRData(&stDCR);
    ScalerColorIPDCRAdjust(&stDCR);
}

//--------------------------------------------------
// Description  : DCR UserCommon function
// Input Value  : StructDCRSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetDCRData(StructColorDCRSetting *pstDCRData)
{
    UserInterfaceColorGetDCRData(&pstDCRData->stDCRSetting);

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
    if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
    {
        WORD usHDR10MaxLvCode = 0;

        pstDCRData->stDCRSetting.enumDCRMode = _DCR_LOCAL_DIMMING;
        pstDCRData->stDCRSetting.unDCRData.stDCRLocalDimmingData.enumDCRUserMeasureRegion = _FULL_REGION;
        pstDCRData->stDCRSetting.unDCRData.stDCRLocalDimmingData.enumDCRMeasureSel = _MEASURE_Y;

#if(_HDR10_SUPPORT == _ON)
        if(UserCommonColorHDRGetHDR10Status(_DISPLAY_RGN_1P) == _HDR10_ON)
        {
            switch(UserCommonColorHDRGetHDR10ApplyLvType(_DISPLAY_RGN_1P))
            {
                case _HDR10_MAX_MASTERING_LV_TYPE_540:
                    usHDR10MaxLvCode = _LOCAL_DIMMING_HDR10_540NIT;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                    usHDR10MaxLvCode = _LOCAL_DIMMING_HDR10_1200NIT;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                    usHDR10MaxLvCode = _LOCAL_DIMMING_HDR10_4000NIT;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                    usHDR10MaxLvCode = _LOCAL_DIMMING_HDR10_10000NIT;
                    break;
#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_ADDRESS), 2, pData);
                    usHDR10MaxLvCode = (((TO_WORD(pData[0], pData[1]) >> 6) >> 2) - _LOCAL_DIMMING_NOTM_CODE_TOLERANCE) << 2;
                    break;
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_FRAME_AVERAGE_LV:
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_FRAME_AVG_LV_ADDRESS), 2, pData);
                    usHDR10MaxLvCode = (((TO_WORD(pData[0], pData[1]) >> 6) >> 2) - _LOCAL_DIMMING_NOTM_CODE_TOLERANCE) << 2;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_USER_DEFINE_LV:
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_USER_DEF_LV_ADDRESS), 2, pData);
                    usHDR10MaxLvCode = (((TO_WORD(pData[0], pData[1]) >> 6) >> 2) - _LOCAL_DIMMING_NOTM_CODE_TOLERANCE) << 2;
                    break;
#endif
#endif
                default:
                    usHDR10MaxLvCode = 1023;
            }
        }
        else
#endif
        {
            usHDR10MaxLvCode = _LOCAL_DIMMING_SDR_NATIVE_NIT;
        }
        pstDCRData->stDCRSetting.unDCRData.stDCRLocalDimmingData.usThreshold1 = _LOCAL_DIMMING_BLACK_COLOR_CODE;
        pstDCRData->stDCRSetting.unDCRData.stDCRLocalDimmingData.usThreshold2 = usHDR10MaxLvCode;
    }
#endif
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
    {
        pstDCRData->stDCRSetting.enumDCRMode = _DCR_GLOBAL_DIMMING;
        pstDCRData->unKernelDCRData.stKernelDCRGlobalDimmingData.enumDCRUserMeasureRegion = _FULL_REGION;
        pstDCRData->unKernelDCRData.stKernelDCRGlobalDimmingData.enumDCRMeasureSel = _MEASURE_Y;
        pstDCRData->unKernelDCRData.stKernelDCRGlobalDimmingData.usThreshold2 = _GLOBAL_DIMMING_WHITE_THD;
    }
#endif
}

#if(_HW_DCR_BIT == _DCR_8BIT)
//--------------------------------------------------
// Description  : Read DCR Histogram Result
// Input Value  : DCR Histogram Information Option
// Output Value : DCR Histogram Information
// Note         : When get _DCR_ABOVE_TH_VAL(8bit), should get _DCR_ABOVE_TH_VAL_HIGH / _DCR_ABOVE_TH_VAL_10BIT_HIGH first
//              : then get _DCR_ABOVE_TH_VAL / _DCR_ABOVE_TH_VAL_10BIT
//--------------------------------------------------
DWORD UserCommonColorDCRReadResult_8BIT(EnumDCRAdjOption enumDCRReadOption)
{
    return ScalerColorDCRReadResult_8BIT(enumDCRReadOption);
}

//--------------------------------------------------
// Description  : Get DCR Average Result
// Input Value  : enumDCRAverageOption : DCR Measure Result Option
//                ulDivider   : GET_MDOMAIN_OUTPUT_HWIDTH() * GET_MDOMAIN_OUTPUT_VHEIGHT() * n(3 or 8)
//                              n = 3; when DCR Measure _MEASURE_AVERAGE(R+G+B)
//                              n = 8; when DCR Measure _MEASURE_Y(2R+5G+B)
// Output Value : None
//--------------------------------------------------
WORD UserCommonColorDCRGetAverage_8BIT(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider)
{
    return ScalerColorDCRGetAverage_8BIT(enumDCRAverageOption, ulDivider);
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
DWORD UserCommonColorDCRReadResult_10BIT(EnumDCRAdjOption enumDCRReadOption)
{
    return ScalerColorDCRReadResult_10BIT(enumDCRReadOption);
}

//--------------------------------------------------
// Description  : Get DCR Average Result
// Input Value  : enumDCRAverageOption : DCR Measure Result Option
//                ulDivider   : GET_MDOMAIN_OUTPUT_HWIDTH() * GET_MDOMAIN_OUTPUT_VHEIGHT() * n(3 or 8)
//                              n = 3; when DCR Measure _MEASURE_AVERAGE(R+G+B)
//                              n = 8; when DCR Measure _MEASURE_Y(2R+5G+B)
// Output Value : None
//--------------------------------------------------
WORD UserCommonColorDCRGetAverage_10BIT(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider)
{
    return ScalerColorDCRGetAverage_10BIT(enumDCRAverageOption, ulDivider);
}

//--------------------------------------------------
// Description  : Get DCR Max RGB
// Input Value  : None
// Output Value : Max RGB
//--------------------------------------------------
WORD UserCommonColorDCRGetMaxRGB_10BIT(void)
{
    return ScalerColorDCRGetMaxRGB_10BIT();
}
#endif

//--------------------------------------------------
// Description  : Get DCR Measure Region Size
// Input Value  : DCR Measure Region
// Output Value : DCR Measure Region Size
//--------------------------------------------------
DWORD UserCommonColorDCRGetMeasureRegionSize(EnumSelRegion enumDCRMeasureRegion)
{
    return ScalerColorDCRGetMeasureRegionSize(enumDCRMeasureRegion);
}

#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset DCR Max CLL & Max FALL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCRResetCLLResult(void)
{
    ScalerColorDCRResetCLLResult();
}
#endif
#if(_HW_DCR_SET_BACKGROUND_OPTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DCR Background Color R, G, B
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCRSetBackgroundColor(WORD usRValue, WORD usGValue, WORD usBValue)
{
    ScalerColorDCRSetBackgroundColor(usRValue, usGValue, usBValue);
}

//--------------------------------------------------
// Description  : Set DCR Background Enable
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCRSetBackgroundEnable(EnumFunctionOnOFF enumOn)
{
    ScalerColorDCRSetBackgroundEnable(enumOn);
}
#endif

//--------------------------------------------------
// Description  : Set DCR Measure Region
// Input Value  : enumDCCAutoModeRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCRSetMeasureRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    ScalerColorDCRSetMeasureRegion(enumSelRegion, enumDBApply);
}
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set NightSniper Adjust
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorNightSniperAdjust(EnumSelRegion enumSelRegion)
{
    StructColorLocalContrastSetting stLocalContrast = {0};
    StructColorICMSetting stICM = {0};

    UserCommonColorGetLocalContrastData(enumSelRegion, &stLocalContrast);
    UserCommonColorGetICMData(enumSelRegion, &stICM);

    if(GET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion) != _OFF)   // Not in multi-function
    {
        UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);

#if(_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_0)
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);

        UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, _OFF);
#else
        // D_Color_Conv with DB
        UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, _OFF);
        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
#endif
    }

    ScalerColorIPICMAdjust(enumSelRegion, &stICM);
    ScalerColorIPLocalContrastAdjust(enumSelRegion, &stLocalContrast);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    // LocalContrast Temporal data
    StructColorLocalContrastTemporalSetting stLocalContrastTemporal = {0};

    UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

    UserCommonColorGetLocalContrastTemporalData(enumSelRegion, &stLocalContrastTemporal);

    // Load Temporal Table
    ScalerColorIPLocalContrastTemporalAdjust(enumSelRegion, &stLocalContrastTemporal, UserCommonColorLocalContrastReadYavgStatus());
#endif

    // Not LocalContrast _OFF case, set the local db apply
    if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode != _LOCALCONTRAST_OFF)
    {
        ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_ALL_APPLY, _DB_APPLY_NO_POLLING);
    }

    if(UserCommonColorGetNightSniperEnableStatus(enumSelRegion) == _ON)
    {
        UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);

        if(GET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion) != _OFF)   // Not Multi-Function
        {
#if(_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_0)
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);

            UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, _ON);
#else
            UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, _ON);
            UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif
        }
    }
    else
    {
        if(stICM.stICMSetting.enumICMMode != _ICM_OFF)
        {
            UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }

        if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode != _LOCALCONTRAST_OFF)
        {
            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }

        if(GET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion) != _OFF)   // Not Multi-Function
        {
            UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);
        }
    }
}

//--------------------------------------------------
// Description  : User Common function  for check NightSniper Selregion
// Input Value  : enumSelRegion
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorNightSniperCheckRegionSupport(EnumSelRegion enumSelRegion)
{
    // NightSniper only support 1P/ PIP/PBPLR, Full region
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
            return _TRUE;

        case _FULL_REGION:

            switch (GET_DISPLAY_MODE())
            {
                case _DISPLAY_MODE_1P:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
                    return _TRUE;

                default:
                    return _FALSE;
            }

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : User Common function  for Get NightSniper Status
// Input Value  : enumSelRegion
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
EnumNightSniperType UserCommonColorGetNightSniperEnableStatus(EnumSelRegion enumSelRegion)
{
    if((UserInterfaceColorGetNightSniperEnableStatus(enumSelRegion) == _NIGHT_SNIPER_ON) &&
       (UserCommonColorNightSniperCheckStatus(enumSelRegion) == _TRUE))
    {
        return _NIGHT_SNIPER_ON;
    }

    return _NIGHT_SNIPER_OFF;
}

//--------------------------------------------------
// Description  : User Common function  for Check NightSniper Status
// Input Value  : enumSelRegion
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorNightSniperCheckStatus(EnumSelRegion enumSelRegion)
{
    // Not Support HDR case
#if((_HDR10_SUPPORT == _ON) || (_HLG_SUPPORT == _ON))
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) != _HDR10_OFF)
    {
        return _FALSE;
    }
#endif

    // Not support DM
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE)
    {
        return _FALSE;
    }
#endif
#endif

    if((UserCommonColorNightSniperCheckRegionSupport(enumSelRegion) == _TRUE) &&
       (ScalerColorLocalContrastGetEnableStatus(enumSelRegion) == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

#if(_ICM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorICMAdjust(EnumSelRegion enumSelRegion)
{
    StructColorICMSetting stICM = {0};

    UserCommonColorGetICMData(enumSelRegion, &stICM);

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_0)
    // Six Color & Chameleon case donot wait for DEN_STOP in Non Muti_Function Case
    if((stICM.stICMSetting.enumICMMode != _ICM_SIXCOLOR) && (stICM.stICMSetting.enumICMMode != _ICM_CHAMELEON))
    {
        if(GET_ICM_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        }
    }
#endif

    ScalerColorIPICMAdjust(enumSelRegion, &stICM);

    if(stICM.stICMSetting.enumICMMode != _ICM_OFF)
    {
        if(GET_ICM_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
        else    // During Multi Function
        {
            UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }
    }
    else
    {
        if(GET_ICM_REGION_ENABLE(enumSelRegion) != _OFF)        // Not in Multi Function
        {
#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_0)
            UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
#else
            // Always keep region _ON when ICM _OFF(need to load lc bypass table), so not need to polling region apply
            UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : User Common function Get Data for ICM
// Input Value  : Select Region ; DB Wait Setting ; Region Enable
// Output Value : None
//--------------------------------------------------
void UserCommonColorICMEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorICMRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Set ICM HLW Effective Region
// Input Value  : EnumHLWSetSel, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorICMSCMSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerColorICMSCMSetEffectiveRegion(enumSetSel, enumDBApply);
}

//--------------------------------------------------
// Description  : Get ICM HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel UserCommonColorICMSCMGetEffectiveRegion(void)
{
    return ScalerColorICMSCMGetEffectiveRegion();
}
#endif
#endif

#if(_COLOR_IP_ICM == _ON)
//--------------------------------------------------
// Description  : ICM UserCommon function
// Input Value  : StructICMSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetICMData(EnumSelRegion enumSelRegion, StructColorICMSetting *pstICMData)
{
    UserInterfaceColorGetICMData(enumSelRegion, &(pstICMData->stICMSetting));
}

//--------------------------------------------------
// Description  : User Common function Get Data for ICM
// Input Value  : Select Region ; DB Wait Setting ; Region Enable
// Output Value : None
//--------------------------------------------------
void UserCommonColorICMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColorICMSCMRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif

#if((_DCC_HISTOGRM_INFO_FUNCTION == _ON) || (_DCC_FUNCTION == _ON))
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCCHistogramAdjust(void)
{
    StructColorDCCHistogramSetting stDCCHistogram = {0};

    UserCommonColorGetDCCHistogramData(&stDCCHistogram);
    ScalerColorIPDCCHistogramAdjust(&stDCCHistogram);
}
#endif

#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
//--------------------------------------------------
// Description  : DCC Histogram UserCommon function
// Input Value  : StructDCCHistogramSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetDCCHistogramData(StructColorDCCHistogramSetting *pstDCCHistogramData)
{
    pstDCCHistogramData->stDCCHistogramSetting.enumDCCHistogramMode = _DCC_HISTOGRAM_USER;
    pstDCCHistogramData->stDCCHistogramSetting.unDCCHistogramData.stDCCHistogramUserData.enumDCCMeasureRegion = _FULL_REGION;

    UserInterfaceColorGetDCCHistogramData(&pstDCCHistogramData->stDCCHistogramSetting);
}
#endif

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Common DCC Adjust
// Input Value  : Select Region ; DB Wait Setting
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCCAdjust(EnumSelRegion enumSelRegion)
{
    StructColorDCCSetting stDCC = {0};

    UserCommonColorGetDCCData(enumSelRegion, &stDCC);

    if(GET_DCC_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    ScalerColorIPDCCAdjust(enumSelRegion, &stDCC);

    UserCommonColorDCCHistogramAdjust();

    if(stDCC.stDCCSetting.enumDCCMode != _DCC_OFF)
    {
        if(GET_DCC_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
        else    // During Multi Function
        {
            UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }
    }
    else
    {
        if(GET_DCC_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
        }
    }
}

//--------------------------------------------------
// Description  : User Common function Get Data for DCC
// Input Value  : Select Region ; DB Wait Setting ; Region Enable
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCCEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorDCCRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Set DCC HLW Effective Region
// Input Value  : EnumHLWSetSel, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCCSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerColorDCCSetEffectiveRegion(enumSetSel, enumDBApply);
}

//--------------------------------------------------
// Description  : Get DCC HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel UserCommonColorDCCGetEffectiveRegion(void)
{
    return ScalerColorDCCGetEffectiveRegion();
}
#endif
#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_COLOR_IP_DCC == _ON)
//--------------------------------------------------
// Description  : DCC UserCommon function
// Input Value  : StructDCCSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetDCCData(EnumSelRegion enumSelRegion, StructColorDCCSetting *pstDCCData)
{
    UserInterfaceColorGetDCCData(enumSelRegion, &(pstDCCData->stDCCSetting));

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
    if(pstDCCData->stDCCSetting.enumDCCMode == _DCC_HDR10_LIGHTENHANCE)
    {
        EnumHDR10StaticMasteringLvType enumHDR10StaticMasteringLvType = UserCommonColorHDRGetHDR10LvTypeForStaticMastering(enumSelRegion);

        switch(enumHDR10StaticMasteringLvType)
        {
            case _HDR10_STATIC_MASTERING_LV_TYPE_540:
                pstDCCData->unKernelDCCData.stKernelDCCHDR10LightEnhanceData.pucTable = pstDCCData->stDCCSetting.unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_540NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_1200:
                pstDCCData->unKernelDCCData.stKernelDCCHDR10LightEnhanceData.pucTable = pstDCCData->stDCCSetting.unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_1200NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_4000:
                pstDCCData->unKernelDCCData.stKernelDCCHDR10LightEnhanceData.pucTable = pstDCCData->stDCCSetting.unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_4000NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_10000:
                pstDCCData->unKernelDCCData.stKernelDCCHDR10LightEnhanceData.pucTable = pstDCCData->stDCCSetting.unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_10000NIT;
                break;

            default:
                pstDCCData->unKernelDCCData.stKernelDCCHDR10LightEnhanceData.pucTable = pstDCCData->stDCCSetting.unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_540NIT;
                break;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : User Common function Get Data for DCC
// Input Value  : Select Region ; DB Wait Setting ; Region Enable
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCCRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColorDCCRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif // End of #if(_COLOR_IP_DCC == _ON)

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : Get DCC Histogram Information
// Input Value  : pucReadArray
// Output Value : None
//--------------------------------------------------
void UserCommonColorDCCGetHistoInfo(BYTE *pucReadArray)
{
    ScalerColorDCCGetHistoInfo(pucReadArray);
}

//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
// Notice : Under _DCC_GEN_0, all result are one byte. Under _DCC_GEN_0, S0~S6 are one byte, but Y_MAX and Y_MIN are one word.
//--------------------------------------------------
BYTE UserCommonColorDCCReadS0toS6(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    return ScalerColorDCCReadS0toS6(pucReadArray, enumDCCReadOption);
}

#if(_HW_DCC_Y_BIT_MODE == _DCC_Y_8BIT)
//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
//--------------------------------------------------
BYTE UserCommonColorDCCReadY_8BIT(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    return ScalerColorDCCReadY_8BIT(pucReadArray, enumDCCReadOption);
}
#endif

#if(_HW_DCC_Y_BIT_MODE == _DCC_Y_10BIT)
//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
//--------------------------------------------------
WORD UserCommonColorDCCReadY_10BIT(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    return ScalerColorDCCReadY_10BIT(pucReadArray, enumDCCReadOption);
}
#endif
#endif

#if(_COLOR_IP_IAPS == _ON)
//--------------------------------------------------
// Description  : IAPS UserCommon function
// Input Value  : StructIAPSSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetIAPSData(EnumSelRegion enumSelRegion, StructColorIAPSSetting *pstIAPSData)
{
    UserInterfaceColorGetIAPSData(enumSelRegion, &(pstIAPSData->stIAPSSetting));

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
    if(pstIAPSData->stIAPSSetting.enumIAPSMode == _IAPS_HDR10_LIGHTENHANCE)
    {
        EnumHDR10StaticMasteringLvType enumHDR10StaticMasteringLvType = UserCommonColorHDRGetHDR10LvTypeForStaticMastering(enumSelRegion);

        switch(enumHDR10StaticMasteringLvType)
        {
            case _HDR10_STATIC_MASTERING_LV_TYPE_540:
                pstIAPSData->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.usGainValue = _LIGHTENHANCE_IAPSGAIN_540NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_1200:
                pstIAPSData->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.usGainValue = _LIGHTENHANCE_IAPSGAIN_1200NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_4000:
                pstIAPSData->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.usGainValue = _LIGHTENHANCE_IAPSGAIN_4000NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_10000:
                pstIAPSData->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.usGainValue = _LIGHTENHANCE_IAPSGAIN_10000NIT;
                break;

            default:
                pstIAPSData->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.usGainValue = _LIGHTENHANCE_IAPSGAIN_540NIT;
                break;
        }

        pstIAPSData->unKernelIAPSData.stKernelIAPSHDR10LightEnhanceData.ucSoftClampValue = 0x00;
    }
#endif
}

//--------------------------------------------------
// Description  : User Common function Adjust IAPS Highlight Window Active Region
// Input Value  : Select Region ; DB Wait Setting ; Region Enable
// Output Value : None
//--------------------------------------------------
void UserCommonColorIAPSRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColorIAPSGainRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Set IAPS HLW Effective Region
// Input Value  : EnumHLWSetSel, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorIAPSGainSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerColorIAPSGainSetEffectiveRegion(enumSetSel, enumDBApply);
}

//--------------------------------------------------
// Description  : Get IAPS HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel UserCommonColorIAPSGainGetEffectiveRegion(void)
{
    return ScalerColorIAPSGainGetEffectiveRegion();
}
#endif
#endif

#if(_CONTRAST_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Adjust Contrast
// Input Value  : Select Region
// Output Value : void
//--------------------------------------------------
void UserCommonColorContrastAdjust(EnumSelRegion enumSelRegion)
{
    StructColorCtsSetting stCts = {0};

    UserCommonColorGetContrastData(enumSelRegion, &stCts);

    if(GET_CTS_BRI_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    ScalerColorIPContrastAdjust(enumSelRegion, &stCts);

    if(GET_CTS_BRI_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else    // During Multi Function
    {
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }
}
#endif

#if(_COLOR_IP_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Color data
// Input Value  : None
// Output Value : compensate value
//--------------------------------------------------
void UserCommonColorContrast10bitPanelCompensate(EnumSelRegion enumSelRegion, WORD *pusData)
{
    if(ScalerRegionGetMaxRegionCount() > 2)
    {
        return;
    }
    else
    {
        EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_NONE;

        switch(enumSelRegion)
        {
            case _DEMO_INSIDE:
            case _DEMO_OUTSIDE:
            case _FULL_REGION:
                enumDisplayRegion = (EnumDisplayRegion)GET_DISPLAY_MODE();
                break;

            default:
                enumDisplayRegion = (EnumDisplayRegion)enumSelRegion;
                break;
        }

        if(ScalerColorGetColorDepth(SysRegionGetInputPort(enumDisplayRegion)) == _COLOR_DEPTH_8_BITS)
        {
            pusData[0] = (WORD)(((DWORD)pusData[0] * 1023 / 1020) > 4095) ? 4095 : (WORD)((DWORD)pusData[0] * 1023 / 1020);
            pusData[1] = (WORD)(((DWORD)pusData[1] * 1023 / 1020) > 4095) ? 4095 : (WORD)((DWORD)pusData[1] * 1023 / 1020);
            pusData[2] = (WORD)(((DWORD)pusData[2] * 1023 / 1020) > 4095) ? 4095 : (WORD)((DWORD)pusData[2] * 1023 / 1020);
        }
    }
}

#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
//--------------------------------------------------
// Description  : Output Data
// Input Value  : Input Data
// Output Value : compensate value for 6bit panel
//--------------------------------------------------
void UserCommonColorContrast6bitPanelCompensate(WORD *pusData)
{
    pusData[0] = (DWORD)pusData[0] * 252 / 255;
    pusData[1] = (DWORD)pusData[1] * 252 / 255;
    pusData[2] = (DWORD)pusData[2] * 252 / 255;
}
#endif

//--------------------------------------------------
// Description  : User Common function Adjust for Contrast
// Input Value  : Select Region ; Contrast Setting Struct
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetContrastData(EnumSelRegion enumSelRegion, StructColorCtsSetting *pstCtsData)
{
    UserInterfaceColorGetContrastData(enumSelRegion, &(pstCtsData->stCtsSetting));

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        UserCommonColorContrast10bitPanelCompensate(enumSelRegion, pstCtsData->stCtsSetting.unCtsData.stCtsUserData.pusData);
    }
#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
    else if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
#if(_GAMMA_FUNCTION == _ON)
        StructColorOutGammaSetting stOutGamma = {0};

        UserInterfaceColorGetOutGammaData(enumSelRegion, &(stOutGamma.stOutGammaSetting));
        if(stOutGamma.stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_OFF)
#endif
        {
            UserCommonColorContrast6bitPanelCompensate(pstCtsData->stCtsSetting.unCtsData.stCtsUserData.pusData);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Contrast Setting
// Input Value  : EnumBriConCoefType, Coefficient
// Output Value : Contrast Setting
//--------------------------------------------------
void UserCommonColorContrastGetSetting(EnumCtsCoefType enumCtsCoefType, WORD *pusData)
{
    ScalerColorContrastGetSetting(enumCtsCoefType, pusData);
}
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Adjust Brightness
// Input Value  : Select Region
// Output Value : void
//--------------------------------------------------
void UserCommonColorBrightnessAdjust(EnumSelRegion enumSelRegion)
{
    StructColorBriSetting stBri = {0};

    UserCommonColorGetBrightnessData(enumSelRegion, &stBri);

    if(GET_CTS_BRI_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    ScalerColorIPBrightnessAdjust(enumSelRegion, &stBri);

    if(GET_CTS_BRI_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else    // During Multi Function
    {
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }
}
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
//--------------------------------------------------
// Description  : User Common function Adjust for Brightness
// Input Value  : Select Region ; Brightness Setting Struct
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetBrightnessData(EnumSelRegion enumSelRegion, StructColorBriSetting *pstBriData)
{
    UserInterfaceColorGetBrightnessData(enumSelRegion, &(pstBriData->stBriSetting));
}

//--------------------------------------------------
// Description  : Get Brightness Setting
// Input Value  : EnumBriConCoefTypem, Coefficient
// Output Value : Brightness Setting
//--------------------------------------------------
void UserCommonColorBrightnessGetSetting(EnumBriCoefType enumBriCoefType, WORD *pusData)
{
    ScalerColorBrightnessGetSetting(enumBriCoefType, pusData);
}
#endif

#if((_CONTRAST_FUNCTION == _ON) || (_BRIGHTNESS_FUNCTION == _ON))
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorBRICTSEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorBRICTSRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorBRICTSRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColorBrightnessContrastHLWRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#endif

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorPCMAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorInGammaSetting stInGamma = {0};
    StructColorOutGammaSetting stOutGamma = {0};
    StructColorSRGBSetting stSRGB = {0};
#if(_COLOR_IP_YMAPPING == _ON)
    StructColorYmappingSetting stYmapping = {0};
#endif
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    StructColorPostGammaSetting stPostGamma = {0};
#endif

    UserCommonColorGetInGammaData(enumSelRegion, &stInGamma);
    UserCommonColorGetOutGammaData(enumSelRegion, &stOutGamma);
    UserCommonColorGetsRGBData(enumSelRegion, &stSRGB);
#if(_COLOR_IP_YMAPPING == _ON)
    UserCommonColorGetYmappingData(enumSelRegion, &stYmapping);
#endif
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    UserCommonColorGetPostGammaData(enumSelRegion, &stPostGamma);
#endif

    {
        if(GET_PCM_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
            UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
            UserCommonColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        }

        ScalerColorIPInGammaAdjust(enumSelRegion, &stInGamma, _IG_DB_DISABLE);
#if(_COLOR_IP_YMAPPING == _ON)
        ScalerColorIPYmappingAdjust(enumSelRegion, &stYmapping);
#endif
        ScalerColorIPSRGBAdjust(enumSelRegion, &stSRGB);
        ScalerColorIPOutGammaAdjust(enumSelRegion, &stOutGamma);
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
        ScalerColorIPPostGammaAdjust(enumSelRegion, &stPostGamma);
#endif

        if(stInGamma.stInGammaSetting.enumInGammaMode != _INGAMMA_OFF)
        {
            UserCommonColorPCMRegionEnable(enumSelRegion, enumDBApply, _ON);
        }
        else
        {
#if(_COLOR_IP_SRGB == _ON)
            if(stSRGB.stSRGBSetting.enumSRGBMode != _SRGB_OFF)
            {
                UserCommonColorSRGBRegionEnable(enumSelRegion, enumDBApply, _ON);
            }
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
            if(stOutGamma.stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_OFF)
            {
                UserCommonColorGammaRegionEnable(enumSelRegion, enumDBApply, _ON);
            }
#endif
        }
    }

#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(stOutGamma.stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_HDR10)
    {
        UserCommonColorLocalDimmingHistoLUTAdjust(_LOCAL_DIMMING_SDR);
    }
    else
    {
        UserCommonColorLocalDimmingHistoLUTAdjust(_LOCAL_DIMMING_HDR);
    }
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorPCMEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorPCMRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : Adjust InputGamma. Cannot be used in multi function
// Input Value  : EnumSelRegion, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorInGammaAdjust(EnumSelRegion enumSelRegion)
{
    StructColorInGammaSetting stInGamma = {0};

    UserCommonColorGetInGammaData(enumSelRegion, &stInGamma);

    ScalerColorIPInGammaAdjust(enumSelRegion, &stInGamma, _IG_DB_ENABLE);
}

#if(_OCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Calculate OCC Gamma1 LUT Address
// Input Value  : EnumOCCGamma1Type
// Output Value : pucOCCGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonColorGetOCCGamma1Addr(EnumOCCGamma1Type enumOCCGamma1Type)
{
    BYTE *pucOCCGammaTypeAddr = _NULL_POINTER;

    switch(enumOCCGamma1Type)
    {
        case _GAMMA1_OCC_NORMAL:
        default:
            pucOCCGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS;
            break;

        case _GAMMA1_HDR:
            pucOCCGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS;
            break;

        case _GAMMA1_OCC_MAX_BRI:
            pucOCCGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MAX_BRI_ADDRESS;
            break;

        case _GAMMA1_GLOBAL_DIMMING:
            pucOCCGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS;
            break;

        case _GAMMA1_FS2:
            pucOCCGammaTypeAddr = g_pucColorDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_OCC_GAMMA10_ADDRESS;
            break;

        case _GAMMA1_OCC_MULTI_BRI_3:
            pucOCCGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MULTI_BRI_3_ADDRESS;
            break;

        case _GAMMA1_OCC_MULTI_BRI_4:
            pucOCCGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MULTI_BRI_4_ADDRESS;
            break;
    }

    return pucOCCGammaTypeAddr;
}
#endif // End of #if(_OCC_FUNCTION == _ON)
#endif // End of #if(_PCM_FUNCTION == _ON)

#if(_COLOR_IP_I_GAMMA == _ON)
//--------------------------------------------------
// Description  : Input Gamma UserCommon function
// Input Value  : StructInGammaSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetInGammaData(EnumSelRegion enumSelRegion, StructColorInGammaSetting *pstIgData)
{
#if(_ULTRA_HDR_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

    UserInterfaceColorGetInGammaData(enumSelRegion, &pstIgData->stInGammaSetting);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE)
    {
        pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_DM;
        return;
    }
#endif
#endif

#if(_HLG_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HLG_ON)
    {
        pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_HLG;
    }
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetAdvancedHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _ADVANCED_HDR10_ON)
    {
        pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_ADVANCED_HDR10;
        pstIgData->unKernelInGammaData.stKernelInGammaAdvancedHDR10Data.ucAdvancedHDR10IGLUTIndex = ScalerColorGetAdvancedHDR10InputGammaNorm();
        return;
    }
#endif

#if(_OGC_FUNCTION == _ON)
    if(pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_OGC)
    {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
        {
            pstIgData->unKernelInGammaData.stKernelInGammaOGCData.enumLocalDimmingStatus = _LOCAL_DIMMING_ENABLE;
        }
        else
        {
            pstIgData->unKernelInGammaData.stKernelInGammaOGCData.enumLocalDimmingStatus = _LOCAL_DIMMING_DISABLE;
        }
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
        {
            pstIgData->unKernelInGammaData.stKernelInGammaOGCData.enumGlobalDimmingStatus = _GLOBAL_DIMMING_ENABLE;
        }
        else
        {
            pstIgData->unKernelInGammaData.stKernelInGammaOGCData.enumGlobalDimmingStatus = _GLOBAL_DIMMING_DISABLE;
        }
#endif
        if((pstIgData->unKernelInGammaData.stKernelInGammaOGCData.enumLocalDimmingStatus == _LOCAL_DIMMING_DISABLE) &&
           (pstIgData->unKernelInGammaData.stKernelInGammaOGCData.enumGlobalDimmingStatus == _GLOBAL_DIMMING_DISABLE))
        {
            pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_OFF;
        }
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    if(pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_HDR10_USER)
    {
        return;
    }

#if(_HDMI_SBTM_SUPPORT == _ON)
    if(UserCommonColorHDRGetSBTMStatus(enumDisplayRegion) == _HDR10_SBTM_ON)
    {
        pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_HDR10_SBTM;
        pstIgData->unKernelInGammaData.stKernelInGammaSBTMData.enumHDR10SBTMMode = UserCommonColorHDR10GetSBTMMode(enumDisplayRegion);
        pstIgData->unKernelInGammaData.stKernelInGammaSBTMData.enumHDR10SBTMGRDMLumMaxType = UserCommonColorHDR10GetSBTMGRDMLumType(enumDisplayRegion);
        pstIgData->unKernelInGammaData.stKernelInGammaSBTMData.enumHDR10SBTMGRDMMinType = UserCommonColorHDR10GetSBTMGRDMMinType(enumDisplayRegion);
        DebugMessageHDR("HDR apply SBTM Mode", pstIgData->unKernelInGammaData.stKernelInGammaSBTMData.enumHDR10SBTMMode);
    }
#endif

    if((pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_HDR10_AUTO) ||
       (pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_HDR10_FORCE_2084))
    {
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus = _HDR10_DARK_ENHANCE_OFF;
#endif
        EnumHDR10MaxMasteringLvType enumLvType = UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion);
        DebugMessageHDR("HDR apply parameter", enumLvType);

#if(_HDR10_EETF_TONEMAPPING_SUPPORT == _ON)
        if(enumLvType < _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
        {
#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
            if(pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_OFF)
#endif
            {
                pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus = _HDR10_DARK_ENHANCE_OFF;
            }

#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
            if(pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_OFF)
#endif
            {
                pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus = _HDR10_DARK_ENHANCE_OFF;
            }
        }
#endif

        if(pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_HDR10_AUTO)
        {
            pstIgData->unKernelInGammaData.stKernelInGammaHDR10AutoData.enumHDR10MaxMasteringLvType = enumLvType;
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
            enumHDR10DarkEnhanceStatus = pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus;
#endif
#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
            DebugMessageHDR("Fixed Point ToneMapping status", pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10FixedPointToneMappingStatus);
#endif
            DebugMessageHDR("Dark Enhance status", pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus);
        }
        else
        {
            pstIgData->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.enumHDR10MaxMasteringLvType = enumLvType;
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
            enumHDR10DarkEnhanceStatus = pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus;
#endif
#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
            DebugMessageHDR("Fixed Point ToneMapping status", pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10FixedPointToneMappingStatus);
#endif
            DebugMessageHDR("Dark Enhance status", pstIgData->stInGammaSetting.unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus);
        }

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        if(enumLvType == _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM)
        {
            UserCommonColorHDRGetMasteringLvStepLessTMTable(enumDisplayRegion, UserCommonColorHDRGetHDR10ApplyLv(enumDisplayRegion), enumHDR10DarkEnhanceStatus);
            if(pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_HDR10_AUTO)
            {
                pstIgData->unKernelInGammaData.stKernelInGammaHDR10AutoData.pucHDR10MasteringLvStepLessTMTable = g_pucColorHDR10StepLessTMIGLUT;
            }
            else
            {
                pstIgData->unKernelInGammaData.stKernelInGammaHDR10Force2084Data.pucHDR10MasteringLvStepLessTMTable = g_pucColorHDR10StepLessTMIGLUT;
            }
        }
#endif
        return;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        if(pstIgData->stInGammaSetting.enumInGammaMode == _INGAMMA_FREESYNC2_USER)
        {
            return;
        }
        pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_FREESYNC2;
        pstIgData->unKernelInGammaData.stKernelInGammaFreeSync2Data.enumFreeSyncIIEOTFType = UserCommonColorHDRGetFreeSyncIIEOTFType(enumDisplayRegion);
        return;
    }
#endif

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
    if(UserCommonColor3DGammaCubeGetEnableStatus(enumSelRegion) == _FUNCTION_ON)
    {
        pstIgData->stInGammaSetting.enumInGammaMode = _INGAMMA_OFF;
        return;
    }
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorPCMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColorPCMRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : Set PCM OFF
// Input Value  : SelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorPCMSetPCMOff(EnumSelRegion enumSelRegion)
{
    ScalerColorPCMSetPCMMode(enumSelRegion, _OGC_MODE);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Get PCM HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel UserCommonColorPCMGetEffectiveRegion(void)
{
    return ScalerColorPCMInputGammaGetEffectiveRegion();
}

#if((_ADVANCED_HDR10_SUPPORT == _OFF) && (_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _OFF))
//--------------------------------------------------
// Description  : Adjust PCM HLW Effective Region
// Input Value  : EnumHLWSetSel, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorPCMSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerColorPCMSetEffectiveRegion(enumSetSel, enumDBApply);
}
#endif
#endif
#endif

#if(_COLOR_IP_YMAPPING == _ON)
//--------------------------------------------------
// Description  : Ymapping UserCommon function to get Ymapping Mode and required data.
// Input Value  : EnumSelRegion, StructColorYmappingSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetYmappingData(EnumSelRegion enumSelRegion, StructColorYmappingSetting *pstYmData)
{
#if((_ADVANCED_HDR10_SUPPORT == _ON) || (_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON))
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetAdvancedHDR10Status(enumDisplayRegion) == _ADVANCED_HDR10_ON)
    {
        pstYmData->stYmappingSetting.enumYmappingMode = _YMAPPING_ADVANCED_HDR10;
        return;
    }
#endif

    UserInterfaceColorGetYmappingData(enumSelRegion, &pstYmData->stYmappingSetting);

#if(_HLG_SUPPORT == _ON)
    if(pstYmData->stYmappingSetting.enumYmappingMode == _YMAPPING_HLG)
    {
        if(pstYmData->stYmappingSetting.unYmappingData.stYmappingHLGData.enumHLGOOTFType == _HLG_OOTF_STANDARD_MODE)
        {
            pstYmData->unKernelYmappingData.stKernelYmappingHLGData.pucTable = (BYTE *)_OGC_HLG_YM_STANDARD_MODE_ADDRESS;
            pstYmData->unKernelYmappingData.stKernelYmappingHLGData.ucBank = _OGC_FLASH_BANK;
        }
        return;
    }
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
    if(pstYmData->stYmappingSetting.enumYmappingMode == _YMAPPING_HDR10_BACKLIGHT_ADAPTIVE_TM)
    {
        WORD usBackLight = pstYmData->stYmappingSetting.unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.usBackLight;
        WORD usBackLightMax = pstYmData->stYmappingSetting.unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.usBackLightMax;
        EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus = pstYmData->stYmappingSetting.unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.enumHDR10DarkEnhanceStatus;

        UserCommonColorHDRGetBackLightAdaptiveTMTable(enumDisplayRegion, usBackLight, usBackLightMax, enumHDR10DarkEnhanceStatus, pstYmData);

        if(UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(UserCommonColorHDRGetDisplayRegion(enumSelRegion))) == _HDR10_MODE_FORCE_2084)
        {
            pstYmData->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.enumHDR10ColorMatrix = pstYmData->stYmappingSetting.unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.enumHDR10ColorMatrix;
        }
        else
        {
            pstYmData->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.enumHDR10ColorMatrix = UserCommonColorHDRGetHDR10ColorMatrix(enumDisplayRegion);
        }

        return;
    }
#endif

    pstYmData->stYmappingSetting.enumYmappingMode = _YMAPPING_OFF;
    return;
}
#endif

#if(_GAMMA_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorGammaAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorOutGammaSetting stOutGamma = {0};
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    StructColorPostGammaSetting stPostGamma = {0};
#endif

    UserCommonColorGetOutGammaData(enumSelRegion, &stOutGamma);
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    UserCommonColorGetPostGammaData(enumSelRegion, &stPostGamma);
#endif

    if(GET_GAMMA_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
    }

#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    ScalerColorIPPostGammaAdjust(enumSelRegion, &stPostGamma);
#endif
    ScalerColorIPOutGammaAdjust(enumSelRegion, &stOutGamma);

    if(stOutGamma.stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_OFF)
    {
        UserCommonColorGammaRegionEnable(enumSelRegion, enumDBApply, _ON);
    }
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorGammaEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorGammaRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#if(_OGC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetOGCColorTempGain(BYTE ucColorTemp, BYTE ucGammaMode, BYTE *pucData, EnumOGCModeSelect enumOGCModeSelect)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _DIMMING_OGC_RGB_GAIN_ADDRESS), 6, pucData);
    }
    else
#endif
    {
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
        {
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _DIMMING_OGC_RGB_GAIN_ADDRESS), 6, pucData);
        }
        else
#endif
        {
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pucData);
            }
#if(_TWO_BRI_CALIBRATION_TYPE > _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            else if(enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_3_TYPE)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS), 6, pucData);
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(enumOGCModeSelect == _OGC_MULTI_BACKLIGHT_4_TYPE)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS), 6, pucData);
            }
#endif
#endif
            else
#endif
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pucData);
                enumOGCModeSelect = enumOGCModeSelect;
            }
        }
    }
}
#endif

#endif

#if(_COLOR_IP_P_GAMMA == _ON)
//--------------------------------------------------
// Description  : Post Gamma UserCommon function
// Input Value  : StructOutGammaSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetPostGammaData(EnumSelRegion enumSelRegion, StructColorPostGammaSetting *pstPgData)
{
#if(_ULTRA_HDR_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        pstPgData->stPostGammaSetting.enumPostGammaMode = _POSTGAMMA_OFF;
        return;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        pstPgData->stPostGammaSetting.enumPostGammaMode = _POSTGAMMA_OFF;
        return;
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE)
    {
        pstPgData->stPostGammaSetting.enumPostGammaMode = _POSTGAMMA_OFF;
        return;
    }
#endif
#endif

    UserInterfaceColorGetPostGammaData(enumSelRegion, &(pstPgData->stPostGammaSetting));

#if(_OGC_FUNCTION == _ON)
    pstPgData->unKernelPostGammaTableAddr.stOutGammaTableAddr.ucOutGammaTableBank = UserCommonColorGetOGCBank(pstPgData->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCTypeSelect, pstPgData->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCModeSelect);
    pstPgData->unKernelPostGammaTableAddr.stOutGammaTableAddr.pucOutGammaTableAddr = UserCommonColorGetOGCAddr(pstPgData->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCTypeSelect, pstPgData->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCModeSelect);
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    if(pstPgData->stPostGammaSetting.enumPostGammaMode == _POSTGAMMA_OGC)
    {
        if(UserInterfaceColorUniformityPlusFunctionStatus(enumSelRegion) == _FUNCTION_ON)
        {
            pstPgData->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCUniformityPlusFunction = _OGC_UNI_PLUS_FUNCTION_ON;
        }
        else
        {
            pstPgData->stPostGammaSetting.unPostGammaData.stPostGammaOGCData.enumOGCUniformityPlusFunction = _OGC_UNI_PLUS_FUNCTION_OFF;
        }
    }
#endif
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    if(pstPgData->stPostGammaSetting.enumPostGammaMode == _POSTGAMMA_OGC)
    {
        pstPgData->unKernelPostGammaData.stKernelPostGammaOGCData.enumGlobalDimmingStatus = UserCommonColorGlobalDimmingGetEnableStatus();
    }
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(pstPgData->stPostGammaSetting.enumPostGammaMode == _POSTGAMMA_OGC)
    {
        pstPgData->unKernelPostGammaData.stKernelPostGammaOGCData.enumLocalDimmingStatus = UserCommonColorLocalDimmingGetEnableStatus();
    }
#endif
}
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
//--------------------------------------------------
// Description  : Output Gamma UserCommon function
// Input Value  : StructOutGammaSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetOutGammaData(EnumSelRegion enumSelRegion, StructColorOutGammaSetting *pstOgData)
{
#if(_ULTRA_HDR_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

    UserInterfaceColorGetOutGammaData(enumSelRegion, &(pstOgData->stOutGammaSetting));

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE)
    {
#if(_DM_CUSTOM_COLOR_SUPPORT == _ON)
        if(pstOgData->stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_HDR10_USER)
#endif
        {
            pstOgData->stOutGammaSetting.enumOutGammaMode = _OUTGAMMA_DM;
        }
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_HDR10_USER)
        {
            return;
        }
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        if(UserCommonColorHDRGetAdvancedHDR10Status(enumDisplayRegion) == _ADVANCED_HDR10_ON)
        {
            pstOgData->stOutGammaSetting.enumOutGammaMode = _OUTGAMMA_ADVANCED_HDR10;
            return;
        }
        else
#endif
        {
            pstOgData->stOutGammaSetting.enumOutGammaMode = _OUTGAMMA_HDR10;
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            pstOgData->unKernelOutGammaData.stKernelOutGammaHDR10Data.enumGlobalDimmingStatus = UserCommonColorGlobalDimmingGetEnableStatus();
#endif
            return;
        }
    }
#endif

#if(_HLG_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HLG_ON)
    {
        pstOgData->stOutGammaSetting.enumOutGammaMode = _OUTGAMMA_HLG;
        return;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_FREESYNC2_USER)
        {
            return;
        }
        pstOgData->stOutGammaSetting.enumOutGammaMode = _OUTGAMMA_FREESYNC2;
        return;
    }
#endif

#if(_OGC_FUNCTION == _ON)
    pstOgData->unKernelOutGammaTableAddr.stOutGammaTableAddr.ucOutGammaTableBank = UserCommonColorGetOGCBank(pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCTypeSelect, pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCModeSelect);
    pstOgData->unKernelOutGammaTableAddr.stOutGammaTableAddr.pucOutGammaTableAddr = UserCommonColorGetOGCAddr(pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCTypeSelect, pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCModeSelect);
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_OGC)
    {
        if(UserInterfaceColorUniformityPlusFunctionStatus(enumSelRegion) == _FUNCTION_ON)
        {
            pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCUniformityPlusFunction = _OGC_UNI_PLUS_FUNCTION_ON;
        }
        else
        {
            pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCUniformityPlusFunction = _OGC_UNI_PLUS_FUNCTION_OFF;
        }
    }
#endif
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_SDRTOHDR)
    {
        if(pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaOGCData.enumOGCModeSelect == _OGC_MAX_BACKLIGHT_TYPE)
        {
            pstOgData->unKernelOutGammaData.stKernelOutGammaSDRtoHDRData.pucTable = g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MAX_BRI_ADDRESS;
        }
        else
        {
            pstOgData->unKernelOutGammaData.stKernelOutGammaSDRtoHDRData.pucTable = g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS;
        }
        return;
    }
#endif

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
    if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_CUBE_MAPPING)
    {
        pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.ucBank = UserCommonColorGet3DGammaOGCTableBank();
        pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.pucTable = UserCommonColorGet3DGammaOGCTableAddress(pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaCubeMappingData.enumTypeSelect);
        return;
    }
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_OGC)
    {
        pstOgData->unKernelOutGammaData.stKernelOutGammaOGCData.enumLocalDimmingStatus = UserCommonColorLocalDimmingGetEnableStatus();
    }
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_OGC)
    {
        pstOgData->unKernelOutGammaData.stKernelOutGammaOGCData.enumGlobalDimmingStatus = UserCommonColorGlobalDimmingGetEnableStatus();
    }
    else if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_PCM)
    {
        pstOgData->unKernelOutGammaData.stKernelOutGammaPCMData.enumGlobalDimmingStatus = UserCommonColorGlobalDimmingGetEnableStatus();
    }
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
    if(pstOgData->stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_DICOM)
    {
        pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.ucBank = UserCommonColorGetDICOMBank(pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.enumDICOMTypeSelect);
        pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.pucTable = UserCommonColorGetDICOMAddr(pstOgData->stOutGammaSetting.unOutGammaData.stOutGammaDICOMData.enumDICOMTypeSelect);
    }
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
#if(_COLOR_IP_I_GAMMA == _ON)
    if(ScalerColorPCMGetPCMMode(enumSelRegion) == _PCM_MODE)
    {
        ScalerColorPCMOutputGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, bOn);
#if(_COLOR_IP_P_GAMMA == _ON)
        ScalerColorPCMPostGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, bOn);
#endif
    }
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
    ScalerColorPostGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, bOn);
#endif

    ScalerColorGammaRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
//--------------------------------------------------
// Description  : Get Ouput Gamma HLW Effective Region
// Input Value  : None
// Output Value : EnumHLWSetSel
//--------------------------------------------------
EnumHLWSetSel UserCommonColorGammaGetEffectiveRegion(void)
{
    return ScalerColorGammaGetEffectiveRegion();
}

//--------------------------------------------------
// Description  : Adjust Ouput Gamma HLW Effective Region
// Input Value  : EnumHLWSetSel, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorGammaSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply)
{
    ScalerColorGammaSetEffectiveRegion(enumSetSel, enumDBApply);
}
#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Bank
// Input Value  : enumOGCTypeSelect, enumOGCModeSelect
// Output Value : usOutputGammaTypeBank
//--------------------------------------------------
BYTE UserCommonColorGetOGCBank(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect)
{
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    BYTE ucGammaNum = 0;

    ucDivisor_HeaderBank = (BYTE)((65536 - _DISP_CALIBRATION_PCM_END) / (DWORD)_OGC_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_OGC_GAMMA_TABLE_SIZE);

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    if(enumOGCModeSelect > _OGC_NORMAL_TYPE)
    {
        ucGammaNum = enumOGCTypeSelect + _OGC_TOTAL_GAMMA;
    }
    else
#endif
    {
        ucGammaNum = enumOGCTypeSelect;
        enumOGCModeSelect = enumOGCModeSelect;
    }


    if(ucGammaNum < ucDivisor_HeaderBank)
    {
        ucQuotient = 0;
    }
    else
    {
        ucQuotient = (ucGammaNum - ucDivisor_HeaderBank) / ucDivisor + 1;
    }

    return ucQuotient + _OGC_FLASH_BANK;
}

//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Address
// Input Value  : enumOGCTypeSelect, enumOGCModeSelect
// Output Value : pucOutputGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonColorGetOGCAddr(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect)
{
    BYTE *pucOutputGammaTypeAddr = _NULL_POINTER;
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucGammaNum = 0;

    ucDivisor_HeaderBank = (BYTE)((65536 - _DISP_CALIBRATION_PCM_END) / (DWORD)_OGC_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_OGC_GAMMA_TABLE_SIZE);

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    if(enumOGCModeSelect > _OGC_NORMAL_TYPE)
    {
        ucGammaNum = enumOGCTypeSelect + _OGC_TOTAL_GAMMA;
    }
    else
#endif
    {
        ucGammaNum = enumOGCTypeSelect;
        enumOGCModeSelect = enumOGCModeSelect;
    }

    if(ucGammaNum < ucDivisor_HeaderBank)
    {
        pucOutputGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _DISP_CALIBRATION_PCM_END + ucGammaNum * _OGC_GAMMA_TABLE_SIZE;
    }
    else
    {
        pucOutputGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + (ucGammaNum - ucDivisor_HeaderBank) % ucDivisor * _OGC_GAMMA_TABLE_SIZE;
    }

    return pucOutputGammaTypeAddr;
}
#endif
#if(_OGC_DICOM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Calculate DICOM LUT Bank
// Input Value  : enumDICOMTypeSelect
// Output Value : usOutputGammaTypeBank
//--------------------------------------------------
BYTE UserCommonColorGetDICOMBank(EnumDICOMTypeSelect enumDICOMTypeSelect)
{
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    BYTE ucGammaNum = 0;
#if(_OGC_TOTAL_DICOM == 1)
    enumDICOMTypeSelect = _DICOM1_TYPE;
#endif
    ucDivisor_HeaderBank = (BYTE)((65536 - _DISP_CALIBRATION_PCM_END) / (DWORD)_OGC_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_OGC_GAMMA_TABLE_SIZE);

    ucGammaNum = enumDICOMTypeSelect + _OGC_TOTAL_GAMMA * (_OGC_FUNCTION) * (1 + (_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0));

    if(ucGammaNum < ucDivisor_HeaderBank)
    {
        ucQuotient = 0;
    }
    else
    {
        ucQuotient = (ucGammaNum - ucDivisor_HeaderBank) / ucDivisor + 1;
    }
    return ucQuotient + _OGC_FLASH_BANK;
}

//--------------------------------------------------
// Description  : Calculate DICOM LUT Address
// Input Value  : enumDICOMTypeSelect
// Output Value : pucOutputGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonColorGetDICOMAddr(EnumDICOMTypeSelect enumDICOMTypeSelect)
{
    BYTE *pucOutputGammaTypeAddr = _NULL_POINTER;
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucGammaNum = 0;
#if(_OGC_TOTAL_DICOM == 1)
    enumDICOMTypeSelect = _DICOM1_TYPE;
#endif
    ucDivisor_HeaderBank = (BYTE)((65536 - _DISP_CALIBRATION_PCM_END) / (DWORD)_OGC_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_OGC_GAMMA_TABLE_SIZE);

    ucGammaNum = enumDICOMTypeSelect + _OGC_TOTAL_GAMMA * (_OGC_FUNCTION) * (1 + (_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0));

    if(ucGammaNum < ucDivisor_HeaderBank)
    {
        pucOutputGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + _DISP_CALIBRATION_PCM_END + ucGammaNum * _OGC_GAMMA_TABLE_SIZE;
    }
    else
    {
        pucOutputGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + (ucGammaNum - ucDivisor_HeaderBank) % ucDivisor * _OGC_GAMMA_TABLE_SIZE;
    }

    return pucOutputGammaTypeAddr;
}
#endif
#endif
#if((_GLOBAL_HUE_SATURATION_FUNCTION == _ON) || (_HDR10_SUPPORT == _ON))
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorSRGBAdjust(EnumSelRegion enumSelRegion)
{
    StructColorSRGBSetting stSRGB = {0};

    UserCommonColorGetsRGBData(enumSelRegion, &stSRGB);
    ScalerColorIPSRGBAdjust(enumSelRegion, &stSRGB);

    if(stSRGB.stSRGBSetting.enumSRGBMode != _SRGB_OFF)
    {
        if(GET_SRGB_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
        else    // During Multi-Function
        {
            UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }
    }
    else
    {
        if(GET_SRGB_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
        }
    }
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorSRGBEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorSRGBRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif

#if(_COLOR_IP_SRGB == _ON)
//--------------------------------------------------
// Description  : sRGB UserCommon function
// Input Value  : StructSRGBSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetsRGBData(EnumSelRegion enumSelRegion, StructColorSRGBSetting *pstsRGBData)
{
#if(_ULTRA_HDR_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

    UserInterfaceColorGetsRGBData(enumSelRegion, &pstsRGBData->stSRGBSetting);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE)
    {
#if(_DM_CUSTOM_COLOR_SUPPORT == _ON)
        if(pstsRGBData->stSRGBSetting.enumSRGBMode != _SRGB_HDR10_USER)
#endif
        {
            pstsRGBData->stSRGBSetting.enumSRGBMode = _SRGB_DM;
        }
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    if(pstsRGBData->stSRGBSetting.enumSRGBMode == _SRGB_HDR10_USER)
    {
        return;
    }

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetAdvancedHDR10Status(enumDisplayRegion) == _ADVANCED_HDR10_ON)
    {
        pstsRGBData->stSRGBSetting.enumSRGBMode = _SRGB_ADVANCED_HDR10;
        return;
    }
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
    if(UserCommonColorHDRGetSBTMStatus(enumDisplayRegion) == _HDR10_SBTM_ON)
    {
        pstsRGBData->stSRGBSetting.enumSRGBMode = _SRGB_HDR10_SBTM;
        if(UserCommonColorHDR10GetSBTMMode(enumDisplayRegion) == _HDR10_SBTM_MODE_G_RDM)
        {
            pstsRGBData->stSRGBSetting.unSRGBData.stSRGBHDR10SBTMData.enumHDR10SBTMColorMatrix = _HDR10_SBTM_COLOR_MATRIX_BT2020;
        }

        return;
    }
#endif

    if(pstsRGBData->stSRGBSetting.enumSRGBMode == _SRGB_HDR10_AUTO)
    {
        pstsRGBData->unKernelSRGBData.stKernelSRGBHDR10AutoData.enumHDR10ColorMatrix = UserCommonColorHDRGetHDR10ColorMatrix(enumDisplayRegion);
        return;
    }
    else if(pstsRGBData->stSRGBSetting.enumSRGBMode == _SRGB_HDR10_FORCE_2084)
    {
        return;
    }

#if(_HLG_SUPPORT == _ON)
    if(pstsRGBData->stSRGBSetting.enumSRGBMode == _SRGB_HLG_AUTO)
    {
        pstsRGBData->unKernelSRGBData.stKernelSRGBHLGAutoData.enumHLGColorMatrix = UserCommonColorHDRGetHDR10ColorMatrix(enumDisplayRegion);
        return;
    }
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        pstsRGBData->stSRGBSetting.enumSRGBMode = _SRGB_FREESYNC2;
        return;
    }
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(pstsRGBData->stSRGBSetting.enumSRGBMode == _SRGB_SDRTOHDR)
    {
#if(_SDR_TO_HDR_ADOBE_RGB_SUPPORT == _ON)
        pstsRGBData->unKernelSRGBData.stKernelSRGBSDRtoHDRData.pucTable = g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS;
#else
        pstsRGBData->unKernelSRGBData.stKernelSRGBSDRtoHDRData.pucTable = g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS;
#endif
        return;
    }
#endif

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
    if(UserCommonColor3DGammaCubeGetEnableStatus(enumSelRegion) == _FUNCTION_ON)
    {
        pstsRGBData->stSRGBSetting.enumSRGBMode = _SRGB_OFF;
        return;
    }
#endif

#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    if(pstsRGBData->stSRGBSetting.enumSRGBMode == _SRGB_PCM_USER_CCT)
    {
        if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
        {
            memset(pstsRGBData->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable, 0, sizeof(pstsRGBData->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable));
            pstsRGBData->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable[0] = 4096;
            pstsRGBData->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable[4] = 4096;
            pstsRGBData->stSRGBSetting.unSRGBData.stSRGBColorTransferUserData.pusTable[8] = 4096;
        }
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorSRGBRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
#if(_COLOR_IP_I_GAMMA == _ON)
    if(ScalerColorPCMGetPCMMode(enumSelRegion) == _PCM_MODE)
    {
        ScalerColorPCMSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, bOn);
    }
#endif
    ScalerColorSRGBRegionEnable(enumSelRegion, enumDBApply, bOn);
}
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Color Convert UserCommon function
// Input Value  : StructColorConvertSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetDColorConvertData(EnumSelRegion enumSelRegion, StructColorDColorConvertSetting *pstDColorConvertData)
{
    UserInterfaceColorGetDColorConvertData(enumSelRegion, &(pstDColorConvertData->stDColorConvertSetting));

#if(_GLOBAL_HUE_SATURATION_HDR_SUPPORT == _OFF)
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) != _HDR10_OFF)
    {
        pstDColorConvertData->stDColorConvertSetting.enumDColorConvertMode = _D_COLOR_CONVERT_STANDARD;
        return;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _ON)
    {
        pstDColorConvertData->stDColorConvertSetting.enumDColorConvertMode = _D_COLOR_CONVERT_STANDARD;
        return;
    }
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetAdvancedHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _ADVANCED_HDR10_ON)
    {
        pstDColorConvertData->stDColorConvertSetting.enumDColorConvertMode = _D_COLOR_CONVERT_STANDARD;
        return;
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _ON)
    {
        pstDColorConvertData->stDColorConvertSetting.enumDColorConvertMode = _D_COLOR_CONVERT_STANDARD;
        return;
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : Use Color Convert to adjust global Hue & Sat
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDColorConvertAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorDColorConvertSetting stDColorConvert = {0};

#if(_COLOR_DEMO_FUNCTION == _ON)
    if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
    {
        // not support in demo mode
        ScalerColorSpaceConvertRecover();
    }
    else
#endif
    {
        UserCommonColorGetDColorConvertData(enumSelRegion, &stDColorConvert);
        ScalerColorIPDColorConvertAdjust(enumSelRegion, &stDColorConvert);
    }
    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, enumDBApply);
}

//--------------------------------------------------
// Description  : format Convert DB flow
// Input Value  : enumDisplayRegion, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorColorConvertDBApply(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);
    ScalerColorSpaceConvertDBApply(enumDisplayRegion, enumDBApply);
}
#endif
#if(_SDR_TO_HDR_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorSDRToHDRAdjust(EnumSelRegion enumSelRegion)
{
    StructColorICMSetting stICM = {0};
    StructColorDCCSetting stDCC = {0};
    StructColorInGammaSetting stInGamma = {0};
    StructColorOutGammaSetting stOutGamma = {0};
    StructColorSRGBSetting stSRGB = {0};

    UserCommonColorGetICMData(enumSelRegion, &stICM);
    UserCommonColorGetDCCData(enumSelRegion, &stDCC);
    UserCommonColorGetInGammaData(enumSelRegion, &stInGamma);
    UserCommonColorGetOutGammaData(enumSelRegion, &stOutGamma);
    UserCommonColorGetsRGBData(enumSelRegion, &stSRGB);

    UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
    UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);

    UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
    UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);

    if(GET_PCM_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
    }

    ScalerColorIPICMAdjust(enumSelRegion, &stICM);
    ScalerColorIPDCCAdjust(enumSelRegion, &stDCC);
    ScalerColorIPInGammaAdjust(enumSelRegion, &stInGamma, _IG_DB_DISABLE);
    ScalerColorIPSRGBAdjust(enumSelRegion, &stSRGB);
    ScalerColorIPOutGammaAdjust(enumSelRegion, &stOutGamma);

    if(stICM.stICMSetting.enumICMMode != _ICM_OFF)
    {
        UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }

    if(stDCC.stDCCSetting.enumDCCMode != _DCC_OFF)
    {
        UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }

    if(stInGamma.stInGammaSetting.enumInGammaMode != _INGAMMA_OFF)
    {
        UserCommonColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }
    else
    {
        if(stSRGB.stSRGBSetting.enumSRGBMode != _SRGB_OFF)
        {
            UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }

        if(stOutGamma.stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_OFF)
        {
            UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        }
    }

    if(GET_PCM_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
    }
}
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColor3DGammaAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColor3DGammaSetting st3DGamma = {0};

    UserCommonColorGet3DGammaData(enumSelRegion, &st3DGamma);

    if(GET_3DGAMMA_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
    }

    ScalerColorIP3DGammaAdjust(&st3DGamma);

    if(st3DGamma.st3DGammaSetting.enum3DGammaMode != _3DGAMMA_OFF)
    {
        UserCommonColor3DGammaRegionEnable(enumSelRegion, enumDBApply, _ON);
    }
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColor3DGammaEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColor3DGammaRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : Enable/Disable 3D Gamma swap for User
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void UserCommonColorRGBGamma3DGammaSwapEnable(EnumFunctionOnOFF enumOn)
{
    ScalerColorRGBGamma3DGammaSwapEnable(enumOn);
}
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
//--------------------------------------------------
// Description  : 3D Gamma UserCommon function
// Input Value  : Struct3DGammaSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGet3DGammaData(EnumSelRegion enumSelRegion, StructColor3DGammaSetting *pst3DGammaData)
{
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetAdvancedHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _ADVANCED_HDR10_ON)
    {
        pst3DGammaData->st3DGammaSetting.enum3DGammaMode = _3DGAMMA_ADVANCED_HDR10;
        return;
    }
#endif

    UserInterfaceColorGet3DGammaData(enumSelRegion, &(pst3DGammaData->st3DGammaSetting));

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
    if(pst3DGammaData->st3DGammaSetting.enum3DGammaMode == _3DGAMMA_CUBE_MAPPING)
    {
#if (_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
        BYTE uc3DGammaTableType = UserCommonColorGetOCC3DGammaStartType();
#else
        BYTE uc3DGammaTableType = 0;
#endif
#if(_HDR10_SUPPORT == _ON)
        if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
        {
            pst3DGammaData->st3DGammaSetting.enum3DGammaMode = _3DGAMMA_OFF;
            return;
        }
#endif
        pst3DGammaData->st3DGammaSetting.unOutGammaData.st3DGammaCubeMappingData.ucBank = UserCommonColorGetOCC3DGammaTableBank(pst3DGammaData->st3DGammaSetting.unOutGammaData.st3DGammaCubeMappingData.enumTypeSelect + uc3DGammaTableType);
        pst3DGammaData->st3DGammaSetting.unOutGammaData.st3DGammaCubeMappingData.pucTable = UserCommonColorGetOCC3DGammaTableAddress(pst3DGammaData->st3DGammaSetting.unOutGammaData.st3DGammaCubeMappingData.enumTypeSelect + uc3DGammaTableType);
        return;
    }
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColor3DGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    ScalerColor3DGammaRegionEnable(enumSelRegion, enumDBApply, bOn);
}

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check 3D Gamma Cube Mapping Status
// Input Value  : enumSelRegion
// Output Value : _FUNCTION_OFF / _FUNCTION_ON
//--------------------------------------------------
EnumFunctionOnOFF UserCommonColor3DGammaCubeGetEnableStatus(EnumSelRegion enumSelRegion)
{
#if(_COLOR_DEMO_FUNCTION == _ON)
    if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
    {
        return _FUNCTION_OFF;
    }
#endif
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            return _FUNCTION_OFF;
        }
#else
        return _FUNCTION_OFF;
#endif
    }
    return UserInterfaceColor3DGammaCubeGetEnableStatus(enumSelRegion);
}
#endif
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate OCC 3DGamma Bank
// Input Value  : Enum3DGammaTypeSelect
// Output Value : uc3DGammaTypeBank
//--------------------------------------------------
BYTE UserCommonColorGetOCC3DGammaTableBank(Enum3DGammaTypeSelect enum3DGammaType)
{
    return (BYTE)(enum3DGammaType / 2) + _OCC_RGB_3D_GAMMA_FLASH_BANK0;
}
//--------------------------------------------------
// Description  : Calculate OCC 3DGamma Table Address
// Input Value  : Enum3DGammaTypeSelect
// Output Value : puc3DGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonColorGetOCC3DGammaTableAddress(Enum3DGammaTypeSelect enum3DGammaType)
{
    BYTE *puc3DGammaTypeAddr = _NULL_POINTER;
    if(enum3DGammaType == _OCC_RGB_3D_GAMMA_TYPE1)
    {
        puc3DGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + 32; // start from address 0x0020
    }
    else if(enum3DGammaType % 2 == 0)
    {
        puc3DGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + 0; // start from address 0x0000
    }
    else
    {
        puc3DGammaTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + 32768; // start from address 0x8000
    }
    return puc3DGammaTypeAddr;
}
#if (_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Start Index of 3DGamma Table
// Input Value  : None
// Output Value : Start Index
//--------------------------------------------------
BYTE UserCommonColorGetOCC3DGammaStartType(void)
{
    BYTE ucStartType = 0;
    UserCommonFlashRead(UserCommonColorGetOCC3DGammaTableBank(0), _RGB_3D_GAMMA_OCC_START_ADDRESS, 1, &ucStartType);
    return ucStartType;
}
#endif
//--------------------------------------------------
// Description  : Calculate OCC 3DGamma OutptGamma Bank
// Input Value  : Enum3DGammaTypeSelect
// Output Value : ucColorGammaBankNum
//--------------------------------------------------
BYTE UserCommonColorGet3DGammaOGCTableBank(void)
{
    return (BYTE)UserCommonColorGetOCC3DGammaTableBank(_OCC_RGB_3D_GAMMA_TOTAL_SET - 1) + 1;
}
//--------------------------------------------------
// Description  : Calculate OCC 3DGamma OutptGamma Table Address
// Input Value  : Enum3DGammaTypeSelect
// Output Value : pucColorGammaBankAddr
//--------------------------------------------------
BYTE *UserCommonColorGet3DGammaOGCTableAddress(Enum3DGammaTypeSelect enum3DGammaType)
{
    BYTE *puc3DGammaOGTypeAddr = _NULL_POINTER;
    puc3DGammaOGTypeAddr = g_pucColorDISP_CALIBRATION_FLASH + (BYTE)(enum3DGammaType) * _OGC_GAMMA_TABLE_SIZE + 32; // start from address 0x0020
    return puc3DGammaOGTypeAddr;
}
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get Uniformity type level mode
// Input Value  : UniformityType Index
// Output Value : Level mode
//--------------------------------------------------
BYTE UserCommonColorGetUniformityType(BYTE ucIndex)
{
    return tUniformityType[ucIndex];
}
//--------------------------------------------------
// Description  : Load gain, offset and decay LUT, turn on/off offset function
// Input Value  : EnumUniformityType, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void UserCommonColorPanelUniformityAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorUniformitySetting stUniData = {0};

    UserCommonColorGetUniformityData(enumSelRegion, &stUniData);

    if(GET_UNIFORMITY_REGION_ENABLE(enumSelRegion) != _OFF)
    {
        UserCommonColorPanelUniformityRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
    }

    ScalerColorIPUniformityAdjust(&stUniData);

    if(stUniData.stUniformitySetting.enumUniformityMode != _UNIFORMITY_OFF)
    {
        UserCommonColorPanelUniformityRegionEnable(enumSelRegion, enumDBApply, _ON);
    }
}
//--------------------------------------------------
// Description  : Calculate Uniformity Gain Bank
// Input Value  : enumUniformityType, ucStartBank, usUNILUTSize
// Output Value : usUniformityTypeBank
//--------------------------------------------------
BYTE UserCommonColorGetPanelUniformityGainBank(EnumUniformityTypeSelect enumUniformityType)
{
    BYTE ucUniformityTypeBank = 0;
    DWORD ulRemainder = 65536;
    BYTE ucUniformityTypeNum = 0;
    DWORD ulUniformityTableSize = 0;
    bit  bOverBankFlag = 0;

    for(ucUniformityTypeNum = 0; ucUniformityTypeNum <= enumUniformityType; ucUniformityTypeNum++)
    {
        ulUniformityTableSize = ((DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeNum) + 1); // +1 checksum address size

        ucUniformityTypeBank = ucUniformityTypeBank + bOverBankFlag;

        if((ulRemainder < ulUniformityTableSize) && (ulRemainder != 65536))
        {
            ulRemainder = 65536;
            ucUniformityTypeBank++;
        }

        if(ulUniformityTableSize > 65536)
        {
            bOverBankFlag = 1;
            ulRemainder = (65536 - (ulUniformityTableSize - 65536));
        }
        else
        {
            bOverBankFlag = 0;
            ulRemainder = (ulRemainder - ulUniformityTableSize);
        }
    }
    return ucUniformityTypeBank + _UNIFORMITY_FLASH_BANK0;
}
//--------------------------------------------------
// Description  : Calculate Panel Uniformity Gain Table Address
// Input Value  : enumUniformityType, usUNILUTSize
// Output Value : usUniformityTypeAddr
//--------------------------------------------------
WORD UserCommonColorGetPanelUniformityGainAddr(EnumUniformityTypeSelect enumUniformityType)
{
    WORD usUniformityTypeAddr = 0;
    DWORD ulRemainder = 0;
    BYTE ucUniformityTypeNum = 0;
    BYTE ucQuotient = 0;
    DWORD ulUniformityTableSize = 0;
    bit  bOverBankFlag = 0;


    for(ucUniformityTypeNum = 0; ucUniformityTypeNum <= enumUniformityType; ucUniformityTypeNum++)
    {
        ulUniformityTableSize = ((DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeNum) + 1);
        if(ulRemainder < ulUniformityTableSize)
        {
            if(ucQuotient == 0)
            {
                ulRemainder = 65536 - _UNIFORMITY_FINISH_ADDRESS - 1;
                usUniformityTypeAddr = _UNIFORMITY_FINISH_ADDRESS + 1;
            }
            else
            {
                ulRemainder = 65536;
                usUniformityTypeAddr = 0;
            }
            ucQuotient++;
        }
        else
        {
            usUniformityTypeAddr += (_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeNum - 1) + 1) - bOverBankFlag * 65536;
        }
        if(ulUniformityTableSize >= 65536)
        {
            ulRemainder = 65536 - (ulUniformityTableSize - ulRemainder);
            bOverBankFlag = 1;
        }
        else
        {
            ulRemainder = (ulRemainder - ulUniformityTableSize);
            bOverBankFlag = 0;
        }
    }
    return usUniformityTypeAddr;
}
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorPanelUniformityEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorPanelUniformityRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : Enable/Disable Panel Uniformity Level0 for User
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void UserCommonColorPanelUniformityOffsetEnable(EnumFunctionOnOFF enumOn)
{
    ScalerColorPanelUniformityOffsetEnable(enumOn);
}

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate Uniformity Offset and Decay Table Bank
// Input Value  : enumUniformityType, ucStartBank, usUNILUTSize, usUNIOffsetLUTSize, usUNIDecayLUTSize
// Output Value : usUniformityTypeOffsetBank
//--------------------------------------------------
BYTE UserCommonColorGetPanelUniformityOffsetBank(EnumUniformityTypeSelect enumUniformityType)
{
    BYTE ucTotalGainBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    DWORD ulRemainder = 65536;
    BYTE ucUniformityTypeNum = 0;
    DWORD ulUniformityTableSize = 0;
    bit  bOverBankFlag = 0;

    ucDivisor = (BYTE)(65536 / ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + (DWORD)_PANEL_UNIFORMITY_DECAY_LUT_SIZE + 2)); // +2 Offset and Decay table checksum address size
    ucQuotient = enumUniformityType / ucDivisor;

    for(ucUniformityTypeNum = 0; ucUniformityTypeNum < _UNIFORMITY_TOTAL_SET; ucUniformityTypeNum++)
    {
        ulUniformityTableSize = ((DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeNum) + 1);

        ucTotalGainBank = ucTotalGainBank + bOverBankFlag;

        if((ulRemainder < ulUniformityTableSize) && (ulRemainder != 65536))
        {
            ulRemainder = 65536;
            ucTotalGainBank++;
        }
        if(ulUniformityTableSize > 65536)
        {
            bOverBankFlag = 1;
            ulRemainder = (65536 - (ulUniformityTableSize - 65536));
        }
        else
        {
            bOverBankFlag = 0;
            ulRemainder = (ulRemainder - ulUniformityTableSize);
        }
    }
    ucTotalGainBank++;
    return ucQuotient + _UNIFORMITY_FLASH_BANK0 + ucTotalGainBank;
}
//--------------------------------------------------
// Description  : Calculate Panel Uniformity Offset Table Address
// Input Value  : enumUniformityType, usUNILUTSize
// Output Value : usUniformityTypeAddr
//--------------------------------------------------
WORD UserCommonColorGetPanelUniformityOffsetAddr(EnumUniformityTypeSelect enumUniformityType)
{
    WORD usUniformityTypeOffsetAddr = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    BYTE ucRemainder = 0;

    ucDivisor = (BYTE)(65536 / ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + (DWORD)_PANEL_UNIFORMITY_DECAY_LUT_SIZE + 2)); // +2 offset and decay checksum address size
    ucQuotient = enumUniformityType / ucDivisor;
    ucRemainder = enumUniformityType % ucDivisor;

    usUniformityTypeOffsetAddr = ucRemainder * (_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + _PANEL_UNIFORMITY_DECAY_LUT_SIZE + 2);

    if(ucQuotient == 0)
    {
        usUniformityTypeOffsetAddr = usUniformityTypeOffsetAddr + _UNIFORMITY_OFFSET_FINISH_ADDRESS + 1;
    }

    return usUniformityTypeOffsetAddr;
}
//--------------------------------------------------
// Description  : Load Panel Uniformity LUT
// Input Value  : enumUniformityType, usUNIOffsetLUTSize, usUNIDecayLUTSize
// Output Value : usUniformityTypeAddr
//--------------------------------------------------
WORD UserCommonColorGetPanelUniformityDecayAddr(EnumUniformityTypeSelect enumUniformityType)
{
    return UserCommonColorGetPanelUniformityOffsetAddr(enumUniformityType) + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1;
}
#endif
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_COLOR_IP_UNIFORMITY == _ON)
//--------------------------------------------------
// Description  : Uniformity UserCommon function
// Input Value  : EnumSelRegion, StructUniformitySetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetUniformityData(EnumSelRegion enumSelRegion, StructColorUniformitySetting *pstUniData)
{
    UserInterfaceColorGetUniformityData(enumSelRegion, &(pstUniData->stUniformitySetting));

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
    if(UserCommonColor3DGammaCubeGetEnableStatus(enumSelRegion) == _FUNCTION_ON)
    {
        pstUniData->stUniformitySetting.enumUniformityMode = _UNIFORMITY_OFF;
    }
#endif
#if(_UNIFORMITY_FUNCTION == _ON)
    EnumUniformityTypeSelect enumUniformityType = _UNIFORMITY_TYPE1;
    switch(pstUniData->stUniformitySetting.enumUniformityMode)
    {
        case _UNIFORMITY_PCM:
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
            if(UserInterfaceColorUniformityPlusFunctionStatus(enumSelRegion) == _FUNCTION_ON)
            {
                pstUniData->stUniformitySetting.unUniformityData.stUniformityPCMData.enumUniformityType = _UNIFORMITY_PLUSMODE_PCM;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                pstUniData->stUniformitySetting.unUniformityData.stUniformityPCMData.b1UniformityOffsetEnable = _OFF;
#endif
            }
#endif
            enumUniformityType = pstUniData->stUniformitySetting.unUniformityData.stUniformityPCMData.enumUniformityType;
            break;
        case _UNIFORMITY_OGC:
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
            if(UserInterfaceColorUniformityPlusFunctionStatus(enumSelRegion) == _FUNCTION_ON)
            {
                pstUniData->stUniformitySetting.unUniformityData.stUniformityOGCData.enumUniformityType = _UNIFORMITY_PLUSMODE_NATIVE;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                pstUniData->stUniformitySetting.unUniformityData.stUniformityOGCData.b1UniformityOffsetEnable = _OFF;
#endif
            }
#endif
            enumUniformityType = pstUniData->stUniformitySetting.unUniformityData.stUniformityOGCData.enumUniformityType;
            break;
        default:
            break;
    }

    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucGainTableBank = UserCommonColorGetPanelUniformityGainBank(enumUniformityType);
    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usGainTableAddr = UserCommonColorGetPanelUniformityGainAddr(enumUniformityType);
    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ulGainTableSize = (DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(enumUniformityType);
    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucUniLevelMode = UserCommonColorGetUniformityType(enumUniformityType);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(enumUniformityType);
    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usOffsetTableAddr = UserCommonColorGetPanelUniformityOffsetAddr(enumUniformityType);
    pstUniData->unKernelUniformityTableAddr.stUniformityTableAddr.usDecayTableAddr = UserCommonColorGetPanelUniformityDecayAddr(enumUniformityType);
#endif
#endif
}

//--------------------------------------------------
// Description  : Enable Specified Region Uniformity
// Input Value  : enumSelRegion, enumDBApply, bOn
// Output Value : None
//--------------------------------------------------
void UserCommonColorPanelUniformityRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(bOn == _ON)
    {
        if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_DISABLE)
        {
            ScalerColorPanelUniformityEnable(_ENABLE);
        }
    }
#endif
    if(UserCommonColorPanelUniformityCheckStatus(enumSelRegion) == _FALSE)
    {
        bOn = _OFF;
        enumSelRegion = _1P_NORMAL_REGION;
    }

    ScalerColorPanelUniformityRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : Check Uniformity Region
// Input Value  : enumSelRegion
// Output Value : return false, uniformity will disable
//--------------------------------------------------
bit UserCommonColorPanelUniformityCheckStatus(EnumSelRegion enumSelRegion)
{
#if(_UNIFORMITY_CUSTOM_ENABLE_CONDITION_SUPPORT == _ON)
    if(UserInterfaceColorGetUniformityCustomEnableStatus() == _FUNCTION_OFF)
#endif
    {
        if((enumSelRegion != _1P_NORMAL_REGION) ||
           (GET_DISPLAY_MODE() != _DISPLAY_MODE_1P))
        {
            return _FALSE;
        }
    }
    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Return Current Color Space for Upper Layer
// Input Value  : None
// Output Value : Current Color Space
//--------------------------------------------------
EnumColorSpace UserCommonColorGetColorSpace(EnumInputPort enumInputPort)
{
#if(_DSC_DECODER_SUPPORT == _ON)
    if(UserCommonDscGetEnable(enumInputPort) == _ENABLE)
    {
        return ScalerDscDecoderGetPpsColorSpaceInfo(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
    }
    else
#endif
    {
        return ScalerColorGetColorSpace(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Return Current Color Space for Upper Layer
// Input Value  : None
// Output Value : Current Color Space
//--------------------------------------------------
bit UserCommonColorGetColorSpaceRGB(EnumColorSpace enumColorSpace)
{
    return ScalerColorGetColorSpaceRGB(enumColorSpace);
}


//--------------------------------------------------
// Description  : Get Scaling By pass
// Input Value  : enumSelRegion
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonColorScalingByPassTableSel(EnumSelRegion enumSelRegion)
{
    return ScalerColorScalingByPassTableSel(enumSelRegion);
}

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Adjust PIPBlending Level
// Input Value  : usLevel, enumDBApply
// Output Value : none
//--------------------------------------------------
void UserCommonColorPIPBlendingLevelAdjust(WORD usLevel, EnumDBApply enumDBApply)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        return;
    }
#endif

    ScalerColorPIPBlendingLevelAdjust(usLevel, enumDBApply);
}
#endif

#if(_SHARPNESS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Sharpness Table
// Input Value  : Request Sharpness Table; DB Apply Type
// Output Value : None
//--------------------------------------------------
void UserCommonColorSharpnessAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorSharpnessSetting stSharpness = {0};

    UserCommonColorGetSharpnessData(enumSelRegion, &stSharpness);
    ScalerColorIPSharpnessAdjust(enumSelRegion, &stSharpness, enumDBApply);
}

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set SHP 1:1 Coef
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *UserCommonColorGetSharpnessDMCoefH(void)
{
#if(_HW_HSU_128TAPS_SUPPORT == _ON)
    return tSCALE_128TAPS_DM_COEF_TABLE;
#elif(_HW_HSU_96TAPS_SUPPORT == _ON)
    return tSCALE_96TAPS_DM_COEF_TABLE;
#else
    return _NULL_POINTER;
#endif
}

//--------------------------------------------------
// Description  : Set SHP 1:1 Coef
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *UserCommonColorGetSharpnessDMCoefV(void)
{
#if(_HW_VSU_128TAPS_SUPPORT == _ON)
    return tSCALE_128TAPS_DM_COEF_TABLE;
#elif(_VSU_96TAPS_SUPPORT == _ON)
    return tSCALE_96TAPS_DM_COEF_TABLE;
#else
    return _NULL_POINTER;
#endif
}
#endif
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set ScalingDownCoef Table
// Input Value  : Request Sharpness Table;
// Output Value : None
//--------------------------------------------------
void UserCommonColorScalingDownCoefAdjust(EnumSelRegion enumSelRegion)
{
    StructColorScalingDownCoefSetting stScalingDownData = {0};
    UserCommonColorGetScalingDownCoef(enumSelRegion, &stScalingDownData);
    ScalerColorIPScalingDownCoefAdjust(enumSelRegion, &stScalingDownData);
}
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
//--------------------------------------------------
// Description  : Sharpness UserCommon function
// Input Value  : StructSharpnessSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetSharpnessData(EnumSelRegion enumSelRegion, StructColorSharpnessSetting *pstSharpnessData)
{
    UserInterfaceColorGetSharpnessData(enumSelRegion, &pstSharpnessData->stSharpnessSetting);
}
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
//--------------------------------------------------
// Description  : ScalingDown UserCommon function
// Input Value  : StructSharpnessSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetScalingDownCoef(EnumSelRegion enumSelRegion, StructColorScalingDownCoefSetting *pstScalingDownData)
{
    UserInterfaceColorGetScalingDownCoef(enumSelRegion, &pstScalingDownData->stScalingDownCoefSetting, ScalerScalingCheckFSBypassEnable(enumSelRegion));
}
#endif

#if(_COLOR_IP_HL_WIN == _ON)
//--------------------------------------------------
// Description  : Set HightLight Window
// Input Value  : Request Select Region
// Output Value : None
//--------------------------------------------------
void UserCommonColorHLWinTypeAdjust(EnumDBApply enumDBApply)
{
    StructColorHLWSetting stHLW = {0};

    UserCommonColorGetHLWData(&stHLW);
    ScalerColorIPHLWAdjust(&stHLW, enumDBApply);
}

//--------------------------------------------------
// Description  : HIGHLIGHT WINDOW UserCommon function
// Input Value  : StructHLWSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetHLWData(StructColorHLWSetting *pstHLWData)
{
    UserInterfaceColorGetHLWData(&pstHLWData->stHLWSetting);

    if(UserCommonColorDemoModeSupportCheck() == _FALSE)
    {
        if(pstHLWData->stHLWSetting.enumHLWMode == _HLW_USER)
        {
            pstHLWData->stHLWSetting.enumHLWMode = _HLW_KERNEL;
            pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.enumHLWKernelRegion = UserInterfaceColorGetOSDSystemSelRegion();
            pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1TopBorderEn = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1TopBorderEn;
            pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1BottomBorderEn = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1BottomBorderEn;
            pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1LeftBorderEn = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1LeftBorderEn;
            pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.b1RightBorderEn = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.b1RightBorderEn;

#if((_EAGLE_SIGHT_SUPPORT == _ON) && (_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON))
            if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) && (GET_EAGLE_SIGHT_USER_ENABLE() == _ON) && (GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE() == _ON))
            {
                StructColorCircleWindowSetting stCircleWindow = {0};

                // Get Circle blending Border Information
                UserInterfaceColorGetCircleWindowData(&stCircleWindow.stCircleWindowSetting);
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWRed = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowRed;
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWGreen = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowGreen;
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWBlue = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowBlue;
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucBorderWidth = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWidth;
            }
            else
#endif
            {
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWRed = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucHLWRed;
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWGreen = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucHLWGreen;
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucHLWBlue = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucHLWBlue;
                pstHLWData->stHLWSetting.unHLWData.stHLWKernelData.ucBorderWidth = pstHLWData->stHLWSetting.unHLWData.stHLWUserData.ucBorderWidth;
            }
        }
    }

#if(_PANEL_ASYMMETRIC == _ON)
    pstHLWData->stHLWSetting.unHLWData.stHLWUserData.usHLWinHPos += _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT;
    pstHLWData->stHLWSetting.unHLWData.stHLWUserData.usHLWinVPos += _PANEL_ASYMMETRIC_DUMMY_NUM_TOP;
#endif
}

//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : enumSelRegion, usHPos, usHWidth, usVPos, usVHeight, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply)
{
    ScalerColorHLWAdjust(usHPos, usHWidth, usVPos, usVHeight, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : None
//--------------------------------------------------
void UserCommonColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    ScalerColorHLWDDomainAdjust(usHPos, usHWidth, usVPos, usVHeight);
}

//--------------------------------------------------
// Description  : Adjust HLW Border Width and Color
// Input Value  : ucBorderWidth, ucRed, ucGreen, ucBlue, enumDBApply
// Output Value : none
//--------------------------------------------------
void UserCommonColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    ScalerColorHLWBorderAdjust(ucBorderWidth, ucRed, ucGreen, ucBlue, enumDBApply);
}

//--------------------------------------------------
// Description  : Adjust HLW Border Enable
// Input Value  : bTopBorderEn, bBottomBorderEn, bLeftBorderEn, bRightBorderEn, enumDBApply
// Output Value : none
//--------------------------------------------------
void UserCommonColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply)
{
    ScalerColorHLWBorderEnable(bTopBorderEn, bBottomBorderEn, bLeftBorderEn, bRightBorderEn, enumDBApply);
}

//--------------------------------------------------
// Description  : Return Demo Mode Support or Not
// Input Value  : none
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit UserCommonColorDemoModeSupportCheck(void)
{
#if((_EAGLE_SIGHT_SUPPORT == _ON) && (_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON))
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) && (GET_EAGLE_SIGHT_USER_ENABLE() == _ON) && (GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE() == _ON))
    {
        return _FALSE;
    }
#endif

#if((_DM_FUNCTION == _ON) && (_IS_MAIN_PROCESS_CPU == _TRUE))
#if(_DM_CUSTOM_COLOR_SUPPORT == _OFF)
    bit bDMEnable = _DISABLE;
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        bDMEnable = UserInterfaceColorDMGetEnableStatus(GET_RGN_DISPLAY_REGION(ucRegionIndex));

        if(bDMEnable == _ENABLE)
        {
            break;
        }
    }

    if(bDMEnable == _ENABLE)
    {
        return _FALSE;
    }
    else
#endif
#endif
    {
        return ScalerColorHLWSupportCheck();
    }
}
#endif // End of #if(_COLOR_IP_HL_WIN == _ON)

#if(_BORDER_WINDOW_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Border Window
// Input Value  : Double Buffer
// Output Value : None
//--------------------------------------------------
void UserCommonColorBorderWindowAdjust(EnumDBApply enumDBApply)
{
    StructColorBorderWindowSetting stBorderWindow = {0};

    UserCommonColorGetBorderWindowData(&stBorderWindow);
    ScalerColorIPBorderWindowAdjust(&stBorderWindow, enumDBApply);
}

//--------------------------------------------------
// Description  : Border Window Disable
// Input Value  : Double Buffer
// Output Value : None
//--------------------------------------------------
void UserCommonColorBorderWindowDisable(EnumDBApply enumDBApply)
{
    ScalerColorBorderEnable(_BORDER_WIN1, _FALSE, _FALSE, _FALSE, _FALSE, _DB_APPLY_NONE);
    ScalerColorBorderEnable(_BORDER_WIN2, _FALSE, _FALSE, _FALSE, _FALSE, enumDBApply);
}
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
//--------------------------------------------------
// Description  : BORDER WINDOW UserCommon function
// Input Value  : StructBorderWindowSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetBorderWindowData(StructColorBorderWindowSetting *pstBorderWindowData)
{
    UserInterfaceColorGetBorderWindowData(&pstBorderWindowData->stBorderWindowSetting);
}
#endif

#if(_OD_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Adjust OD Gain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorODGainAdjust(void)
{
    StructODSetting stOD = {0};

    UserCommonColorGetODData(&stOD);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
    // Send OD setting to Back chip
    UserInterfaceColorDataExchangeSendODGain(stOD.unODData.stODUserData.ucDeltaGain);

    // Inform Back chip OD adjust
    UserCommonDataExchangeSendEvent(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_ADJUST_OD_GAIN);

    // Check Back chip OD adjust done
    if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_ADJUST_OD_GAIN, 30) == _TRUE)
    {
        DebugMessageSystem("Front chip get back chip OD Adjust Gain Done", 1);
    }
    else
    {
        DebugMessageSystem("Front chip get back chip OD Adjust Gain Fail", 1);
    }
#else
    ScalerODAdjust(_OD_ADJUST_GAIN, &stOD);
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : User Adjust OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorODAdjust(void)
{
    StructODSetting stOD = {0};

    UserCommonColorGetODData(&stOD);
    ScalerODEnable(_FUNCTION_OFF);

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
    // Send OD setting to Back chip
    UserInterfaceColorDataExchangeSendODUserData(&stOD);
#else
    switch(stOD.enumODMode)
    {
        case _OD_USER:
            ScalerODAdjust(_OD_ADJUST_GAIN_ODLUT, &stOD);
            ScalerODEnable(_FUNCTION_ON);
            break;

#if(_OD_BY_POSITION_SUPPORT == _ON)
        case _OD_USER_BYPOS:
            ScalerODAdjust(_OD_ADJUST_GAIN_ODLUT_BYPOS, &stOD);
            ScalerODEnable(_FUNCTION_ON);
            break;
#endif
        case _OD_OFF:
        default:
            break;
    }
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : User Adjust OD On/Off
// Input Value  : _ON/_OFF
// Output Value : None
//--------------------------------------------------
void UserCommonColorODEnable(EnumFunctionOnOFF enumOn)
{
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
    // Send enumOn to Back chip
    UserInterfaceColorDataExchangeSendODEnable((BYTE)enumOn);

    // Inform Back chip OD adjust
    UserCommonDataExchangeSendEvent(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_ADJUST_OD_ENABLE);

    // Check Back chip OD adjust done
    if(UserCommonDataExchangeCheckSendEventDone(_DATA_EXCHANGE_KERNEL_EVENT, _DATA_EXCHANGE_KERNEL_EVENT_CHECK_ADJUST_OD_ENABLE, 30) == _TRUE)
    {
        DebugMessageSystem("Front chip get back chip OD Adjust Enable Done", 1);
    }
    else
    {
        DebugMessageSystem("Front chip get back chip OD Adjust Enable Fail", 1);
    }
#else
    if(enumOn == _FUNCTION_ON)
    {
        if(GET_OD_TABLE_VALID_STATUS() == _FALSE)
        {
            UserCommonColorODAdjust();
        }
        else
        {
            ScalerODEnable(_FUNCTION_ON);
        }
    }
    else
    {
        ScalerODEnable(_FUNCTION_OFF);
    }
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Check kernel OD status
// Input Value  : Requested OD status type
// Output Value : _OFF / _ON
//--------------------------------------------------
bit UserCommonColorODGetStatus(EnumODStatusType enumStatusType)
{
    if(enumStatusType == _OD_SUPPORT_STATUS)
    {
        return ScalerODGetSupportStatus();
    }

    return ScalerODGetRealtimeEnableStatus();
}

//--------------------------------------------------
// Description  : Get OD Delta Gain
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE UserCommonColorODGetDeltaGain(void)
{
    return ScalerODGetDeltaGain();
}

//--------------------------------------------------
// Description  : Get OD use param
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
EnumODParamIndex UserCommonColorODGetUseParam(void)
{
    return ScalerODGetUseParam();
}
#endif

#if(_COLOR_IP_OD == _ON)
//--------------------------------------------------
// Description  : OD UserCommon function
// Input Value  : StructODSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetODData(StructODSetting *pstODData)
{
    UserInterfaceColorGetODData(pstODData);
}
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Local Contrast Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    if(UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE)
    {
        StructColorLocalContrastSetting stLocalContrast = {0};

        UserCommonColorGetLocalContrastData(enumSelRegion, &stLocalContrast);

        ScalerColorIPLocalContrastAdjust(enumSelRegion, &stLocalContrast);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
        // LocalContrast Temporal data
        StructColorLocalContrastTemporalSetting stLocalContrastTemporal = {0};

        UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

        UserCommonColorGetLocalContrastTemporalData(enumSelRegion, &stLocalContrastTemporal);

        // Load Temporal Table
        ScalerColorIPLocalContrastTemporalAdjust(enumSelRegion, &stLocalContrastTemporal, UserCommonColorLocalContrastReadYavgStatus());
#endif

#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
        // Calculate new TM Blending Factor & new Ydiff Gain in User mode
        if((stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_HDR10_USER) && (stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.enumLocalContrastBlendingStatus == _LOCALCONTRAST_BLENDING_ENABLE))
        {
            ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucTMFactor);

            stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank);
            ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucYdiffdevisor);
        }
        else if((stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_USER) && (stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.enumLocalContrastBlendingStatus == _LOCALCONTRAST_BLENDING_ENABLE))
        {
            ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucTMFactor);

            stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank);
            ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor);
        }
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
        // Calculate new TM Blending Factor & new Ydiff Gain in SDR+ Adjust mode
        if((stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_SDR_PLUS) && (stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.enumLocalContrastBlendingStatus == _LOCALCONTRAST_BLENDING_ENABLE))
        {
            ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucTMFactor);

            stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank);
            ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor);
        }
#endif

        // load bypass table before LocalContrast local DB apply
        if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_OFF)
        {
            // bypass lc bypass table
            ScalerColorLocalContrastBypass(enumSelRegion);

            // lc bypass table not include Tone-mapping curve, use "_LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY"
            ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY, enumDBApply);
        }
        else
        {
            // lc normal table include both Tone-mapping curve and regs, use "_LOCAL_CONTRAST_ALL_APPLY"
            ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_ALL_APPLY, enumDBApply);
        }

        // Always keep region _ON when LocalContrast _OFF(need to load lc bypass table), so not need to polling region apply
        UserCommonColorLocalContrastRegionEnable(enumSelRegion, enumDBApply, _ON);
    }
    else
    {
        if(GET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        }
    }
}

//--------------------------------------------------
// Description  : Set Local Contrast Temporal Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastTemporalAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    if(UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE)
    {
        StructColorLocalContrastTemporalSetting stLocalContrastTemporal = {0};

        UserCommonColorGetLocalContrastTemporalData(enumSelRegion, &stLocalContrastTemporal);

        // Not in Multi Function
        if(GET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        }

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
        ScalerColorIPLocalContrastTemporalAdjust(enumSelRegion, &stLocalContrastTemporal, UserCommonColorLocalContrastReadYavgStatus());
#else
        ScalerColorIPLocalContrastTemporalAdjust(enumSelRegion, &stLocalContrastTemporal, _LOCALCONTRAST_READYAVG_DISABLE);
#endif

        if(UserCommonColorGetLocalContrastEnableStatus(enumSelRegion) != _FALSE)
        {
            if(GET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion) == _OFF)        // During Multi Function
            {
                UserCommonColorLocalContrastRegionEnable(enumSelRegion, enumDBApply, _ON);
            }
            else    // Not During Multi Function
            {
                UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
            }
        }
    }
    else
    {
        if(GET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        }
    }
}

#if((_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON) || (_SDR_PLUS_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Local Contrast Tone-Mapping Factor Adjust
// Input Value  :
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastToneMappingAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    if(UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE)
    {
        StructColorLocalContrastSetting stLocalContrast = {0};

        // Get Current ucTMFactor
        UserCommonColorGetLocalContrastData(enumSelRegion, &stLocalContrast);

        // Calculate new TM Blending Factor
        if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_HDR10_USER)
        {
            ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucTMFactor);
        }
#if(_SDR_PLUS_FUNCTION == _ON)
        else if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_SDR_PLUS)
        {
            ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucTMFactor);
        }
#endif
        else
        {
            ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucTMFactor);
        }

        // After loading TM Blending Factor, not include Tone-mapping curve, use "_LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY"
        ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY, enumDBApply);
    }
    else
    {
        if(GET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        }
    }
}

//--------------------------------------------------
// Description  : Local Contrast Ydiff Gain Adjust
// Input Value  :
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastSharpnessAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    if(UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE)
    {
        StructColorLocalContrastSetting stLocalContrast = {0};

        // Get Current ucYdiffgainFactor
        UserCommonColorGetLocalContrastData(enumSelRegion, &stLocalContrast);

        // Calculate new Ydiff Gain
        if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_HDR10_USER)
        {
            stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank);
            ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucYdiffdevisor);
        }
#if(_SDR_PLUS_FUNCTION == _ON)
        else if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_SDR_PLUS)
        {
            stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank);
            ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor);
        }
#endif
        else
        {
            stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank);
            ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor);
        }

        // After loading TM Blending Factor, not include Tone-mapping curve, use "_LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY"
        ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY, enumDBApply);
    }
    else
    {
        if(GET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion) != _OFF)
        {
            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set Local Contrast Region Enable
// Input Value  : enumSelRegion, enumDBApply, and bOn
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    UserCommonColorLocalContrastRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : User Common function  for Get LocalContrast Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorGetLocalContrastEnableStatus(EnumSelRegion enumSelRegion)
{
    if((UserInterfaceColorGetLocalContrastEnableStatus(enumSelRegion) == _FUNCTION_ON) &&
       (UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_SDR_PLUS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Common function  for Get SDR+ Status
// Input Value  : enumSelRegion
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorGetSDRPlusEnableStatus(EnumSelRegion enumSelRegion)
{
    if((UserInterfaceColorGetSDRPlusEnableStatus(enumSelRegion) == _FUNCTION_ON) &&
       (UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE))
    {
#if(_HDR10_SUPPORT == _ON)
        if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_OFF)
#endif
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif
#endif  // End of #if(_LOCAL_CONTRAST_SUPPORT == _ON)

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Set Local Contrast Table DB Apply
// Input Value  : enumSelRegion, enumDBApplyType, enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorColorLocalContrastTableDBApply(EnumSelRegion enumSelRegion, EnumLocalContrastDBApplyType enumDBApplyType, EnumDBApply enumDBApply)
{
    ScalerColorLocalContrastTableDBApply(enumSelRegion, enumDBApplyType, enumDBApply);
}

//--------------------------------------------------
// Description  : User Common function Adjust for LocalContrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetLocalContrastData(EnumSelRegion enumSelRegion, StructColorLocalContrastSetting *pstLocalContrastData)
{
    UserInterfaceColorGetLocalContrastData(enumSelRegion, &(pstLocalContrastData->stLocalContrastSetting));

#if(_HDR10_SUPPORT == _ON)
    if((pstLocalContrastData->stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_HDR10_USER) && (UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON))
    {
        pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank = pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucBank;

        switch(UserCommonColorHDRGetHDR10LvTypeForStaticMastering(enumSelRegion))
        {
            case _HDR10_STATIC_MASTERING_LV_TYPE_540:
                pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable = pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_540NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_1200:
                pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable = pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_1200NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_4000:
                pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable = pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_4000NIT;
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_10000:
                pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable = pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_10000NIT;
                break;

            default:
                pstLocalContrastData->unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable = pstLocalContrastData->stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_1200NIT;
                break;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : User Common function Adjust for LocalContrast
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastInitalDataAdjust(EnumSelRegion enumSelRegion)
{
    enumSelRegion = enumSelRegion;

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    if(UserCommonColorLocalContrastReadYavgStatus() == _LOCALCONTRAST_READYAVG_ENABLE)
    {
        ScalerColorLocalContrastReadYavgProcEnable(_DISABLE);
    }
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
        switch(UserCommonColorHDRGetHDR10LvTypeForStaticMastering(enumSelRegion))
        {
            case _HDR10_STATIC_MASTERING_LV_TYPE_540:
                ScalerColorLocalContrastAdjust(enumSelRegion, tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_540, GET_CURRENT_BANK_NUMBER(), _HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE);
                ScalerColorLocalContrastAdjust(enumSelRegion, &tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_540[_HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET], GET_CURRENT_BANK_NUMBER(), (_HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE - _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET));
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_1200:
                ScalerColorLocalContrastAdjust(enumSelRegion, tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_1200, GET_CURRENT_BANK_NUMBER(), _HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE);
                ScalerColorLocalContrastAdjust(enumSelRegion, &tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_1200[_HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET], GET_CURRENT_BANK_NUMBER(), (_HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE - _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET));
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_4000:
                ScalerColorLocalContrastAdjust(enumSelRegion, tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_4000, GET_CURRENT_BANK_NUMBER(), _HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE);
                ScalerColorLocalContrastAdjust(enumSelRegion, &tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_4000[_HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET], GET_CURRENT_BANK_NUMBER(), (_HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE - _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET));
                break;

            case _HDR10_STATIC_MASTERING_LV_TYPE_10000:
                ScalerColorLocalContrastAdjust(enumSelRegion, tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_10000, GET_CURRENT_BANK_NUMBER(), _HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE);
                ScalerColorLocalContrastAdjust(enumSelRegion, &tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_10000[_HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET], GET_CURRENT_BANK_NUMBER(), (_HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE - _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET));
                break;

            default:
                ScalerColorLocalContrastAdjust(enumSelRegion, tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_1200, GET_CURRENT_BANK_NUMBER(), _HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE);
                ScalerColorLocalContrastAdjust(enumSelRegion, &tCOLOR_LOCALCONTRAST_HDR10_INITIALTABLE_1200[_HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET], GET_CURRENT_BANK_NUMBER(), (_HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE - _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET));
                break;
        }
    }
    else
#endif
    {
        ScalerColorLocalContrastAdjust(enumSelRegion, tCOLOR_LOCALCONTRAST_INITIAL_SETTING, GET_CURRENT_BANK_NUMBER(), _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET);
        ScalerColorLocalContrastAdjust(enumSelRegion, &tCOLOR_LOCALCONTRAST_INITIAL_SETTING[_HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET], GET_CURRENT_BANK_NUMBER(), (_HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE - _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET));
    }
#endif

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    if(UserCommonColorLocalContrastReadYavgStatus() == _LOCALCONTRAST_READYAVG_ENABLE)
    {
        ScalerColorLocalContrastReadYavgProcEnable(_ENABLE);
    }
#endif
}

//--------------------------------------------------
// Description  : DCC Histogram UserCommon function
// Input Value  : StructDCCHistogramSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetLocalContrastTemporalData(EnumSelRegion enumSelRegion, StructColorLocalContrastTemporalSetting *pstLocalContrastData)
{
    WORD usInputVFreq = UserCommonColorLocalContrastGetInputVFreq(enumSelRegion);

    StructLocalContrastSetting stLocalContrast = {0};
    UserInterfaceColorGetLocalContrastData(enumSelRegion, &stLocalContrast);

    // Get Temporal Data
    UserInterfaceColorGetLocalContrastTemporalData(&(pstLocalContrastData->stLocalContrastTemporalSetting));
    pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.ucBank = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.ucBank;

#if(_DRR_SUPPORT == _ON)
    if(UserCommonDrrGetType() != _DRR_NONE_TYPE)
    {
        // DRR Case Suggest to use the (enumLocalContrastTemporalType - 1) table
        if(usInputVFreq <= (1200 * 11 / 10))            // DRR Max Vreq < 120Hz apply temporal_table_60Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_60;
        }
        else if(usInputVFreq <= (1440 * 11 / 10))       // DRR Max Vfreq = 144Hz apply temporal_table_120Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_120;
        }
        else if(usInputVFreq <= (1650 * 11 / 10))       // DRR Max Vfreq = 165Hz apply temporal_table_144Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_144;
        }
        else                                           // DRR Max Vfreq = 240 Hz apply temporal_table_165Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_165;
        }
    }
    else    // non DRR case
#endif
    {
        // With Input Vreq 10% margin
        if(usInputVFreq <= 300 * 11 / 10)               // Max Vreq = 24Hz, 30Hz for DVD
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_24;
        }
        else if(usInputVFreq <= 750 * 11 / 10)          // Max Vreq = 48Hz, 60Hz, 75Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_60;
        }
        else if(usInputVFreq <= (1200 * 11 / 10))       // Max Vfreq = 120Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_120;
        }
        else if(usInputVFreq <= (1440 * 11 / 10))       // Max Vfreq = 144Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_144;
        }
        else if(usInputVFreq <= (1650 * 11 / 10))       // Max Vfreq = 165Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_165;
        }
        else                                            // Max Vfreq = 240 Hz
        {
            pstLocalContrastData->unKernelLocalContrastTemporalData.stKernelLocalContrastTemporalData.pucTable = pstLocalContrastData->stLocalContrastTemporalSetting.unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_240;
        }
    }

    if(stLocalContrast.enumLocalContrastMode != _LOCALCONTRAST_OFF)
    {
        pstLocalContrastData->unKernelLocalContrastTemporalMode.stKernelLocalContrastTemporalMode.enumLocalContrastTemporalMode = _LOCALCONTRAST_TEMPORAL_USER;
    }
    else
    {
        pstLocalContrastData->unKernelLocalContrastTemporalMode.stKernelLocalContrastTemporalMode.enumLocalContrastTemporalMode = _LOCALCONTRAST_TEMPORAL_OFF;
    }
}
//--------------------------------------------------
// Description  : Get Input VFreq for Local Contrast
// Input Value  : enumSelRegion
// Output Value : Input Vreq for Current enumSelRegion
//--------------------------------------------------
WORD UserCommonColorLocalContrastGetInputVFreq(EnumSelRegion enumSelRegion)
{
    EnumDisplayRegion enumDisplayRegion = UserCommonColorLocalContrastGetDisplayRegion(enumSelRegion);

    return (g_pstMeasureRegionTimingInfo[ScalerRegionGetIndex(enumDisplayRegion)].stTimingInfo.usVFreqAdjusted);
}

//--------------------------------------------------
// Description  : Return LocalContrast Display Region
// Input Value  : EnumSelRegion
// Output Value : EnumDisplayRegion
//--------------------------------------------------
EnumDisplayRegion UserCommonColorLocalContrastGetDisplayRegion(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
        case _FULL_REGION:
            return (EnumDisplayRegion)GET_DISPLAY_MODE();

        // LocalContrast don't support 3P & 4P
        default:
            return (EnumDisplayRegion)enumSelRegion;
    }
}
//--------------------------------------------------
// Description  : Set Local Contrast Region Enable
// Input Value  : enumSelRegion, enumDBApply, and bOn
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    if(UserCommonColorLocalContrastCheckStatus(enumSelRegion) == _TRUE)
    {
        ScalerColorLocalContrastRegionEnable(enumSelRegion, enumDBApply, bOn);
    }
    else
    {
        ScalerColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
    }
}

//--------------------------------------------------
// Description  : User Common function  for Check LocalContrast Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorLocalContrastCheckStatus(EnumSelRegion enumSelRegion)
{
    if((ScalerColorLocalContrastCheckRegionSupport(enumSelRegion) == _TRUE) &&
       (ScalerColorLocalContrastGetEnableStatus(enumSelRegion) == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : User Common function  for Check LocalContrast Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
EnumLocalContrastReadYavgData UserCommonColorLocalContrastReadYavgStatus(void)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
    {
        return _LOCALCONTRAST_READYAVG_ENABLE;
    }
#endif

    return _LOCALCONTRAST_READYAVG_DISABLE;
}

//--------------------------------------------------
// Description  : Check current displaymode support ReadYavg Or Not for LD
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit UserCommonColorLocalContrastCheckReadYavgSupport(void)
{
    EnumSelRegion enumSelRegion = _1P_NORMAL_REGION;
    BYTE ucMaxRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    if(UserCommonColorLocalContrastReadYavgStatus() == _LOCALCONTRAST_READYAVG_DISABLE)
    {
        return _FALSE;
    }
    else if(ScalerColorLocalContrastCheckAspectRatioStatus() != _LOCALCONTRAST_ASPECT_RATIO_OFF)
    {
        // aspect ratio case, LD block position will mismatch with LC
        return _FALSE;
    }
    else
    {
        if(ucMaxRegionCount <= _LOCAL_CONTRAST_MAX_REGION_COUT)
        {
            for(BYTE ucRegionIndex = 0; ucRegionIndex < ucMaxRegionCount; ucRegionIndex++)
            {
                enumSelRegion = (EnumSelRegion)GET_RGN_DISPLAY_REGION(ucRegionIndex);

                if(ScalerColorLocalContrastGetReadYavgSupport(enumSelRegion) == _FALSE)
                {
                    // 2p case, if one of enumSelRegion return FALSE, then return NOT support
                    return _FALSE;
                }
            }
            return _TRUE;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Start /Finish Yavg Read, need to reset Local Contrast Blocknum & Temporal Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastRestoreSetting(void)
{
    BYTE ucRegionIndex = 0;
    EnumSelRegion enumSelRegion = (EnumSelRegion)GET_RGN_DISPLAY_REGION(ucRegionIndex);
    EnumSelRegion enumSelRegion_Inverse = UserCommonRegionGetInverse(enumSelRegion);
    bit bReadYavgStatus = UserCommonColorLocalContrastReadYavgStatus();

    // REGION _OFF
    UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
    UserCommonColorLocalContrastRegionEnable(enumSelRegion_Inverse, _DB_APPLY_NONE, _OFF);

    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion_Inverse, _DB_APPLY_POLLING);

    // Disable LocalContrast First
    ScalerColorLocalContrastEnable(enumSelRegion, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
    ScalerColorLocalContrastEnable(enumSelRegion_Inverse, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);

    ScalerColorLocalContrastBacklightDecision(enumSelRegion, bReadYavgStatus);
    ScalerColorLocalContrastBacklightDecision(enumSelRegion_Inverse, bReadYavgStatus);

    // Load Inital Table
    UserCommonColorLocalContrastInitalDataAdjust(enumSelRegion);
    UserCommonColorLocalContrastInitalDataAdjust(enumSelRegion_Inverse);

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
    UserCommonColorLocalContrastAdjust(enumSelRegion_Inverse, _DB_APPLY_NONE);
#endif

    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion_Inverse, _DB_APPLY_POLLING);
}
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Local Contrast Global/ Block Scene Change THD
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalContrastSetSceneChangeTHD(EnumSelRegion enumSelRegion)
{
    ScalerColorLocalContrastSetSceneChangeTHD(enumSelRegion);
}
#endif
#endif
#endif

#if(_I_DITHER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Enable/Disable Idither function
// Input Value  : EnumDisplayRegion, EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void UserCommonColorIDitherRegionEnable(EnumDisplayRegion enumDisplayRegion, EnumFunctionOnOFF enumOn)
{
    ScalerColorIDitherRegionEnable(enumDisplayRegion, enumOn);
}

//--------------------------------------------------
// Description  : Set IDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorIDitherAdjust(void)
{
#if(_HW_IDITHER_TABLE_SET_NUM > 1)
    ScalerColorIDitherAdjust(_REG_MAIN1_PAGE, _IDITHER_12_TO_8, tIDITHER_TABLE_FIFO8, tIDITHER_SEQ_TABLE, tIDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
    ScalerColorIDitherAdjust(_REG_SUB1_PAGE, _IDITHER_12_TO_10, tIDITHER_TABLE_FIFO10, tIDITHER_SEQ_TABLE, tIDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
#endif
}
//--------------------------------------------------
// Description  : Initial IDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorIDitherDisplayInitialProc(void)
{
    ScalerColorIDitherEnable(_FUNCTION_ON);
}

//--------------------------------------------------
// Description  : Reload IDither Table
// Input Value  : SelRegion, ColorDepth
// Output Value : None
//--------------------------------------------------
void UserCommonColorIDitherReloadTable(EnumSelRegion enumSelRegion, BYTE ucColorDepth)
{
    enumSelRegion = enumSelRegion;
    if(ucColorDepth == _COLOR_DEPTH_8_BITS)
    {
        ScalerColorIDitherAdjust(_REG_MAIN1_PAGE, _IDITHER_12_TO_8, tIDITHER_TABLE_FIFO8, tIDITHER_SEQ_TABLE, tIDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
    }
    else
    {
        ScalerColorIDitherAdjust(_REG_MAIN1_PAGE, _IDITHER_12_TO_10, tIDITHER_TABLE_FIFO10, tIDITHER_SEQ_TABLE, tIDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_I_DITHER_SUPPORT == _ON)

#if(_D_DITHER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set DDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDDitherAdjust(void)
{
#if(_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE)
#if(_PANEL_EXIST_MULTIPANEL == _OFF)
    ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE, tDDITHER_ADVANCE_SETTING_TABLE, GET_CURRENT_BANK_NUMBER());
#else
    switch(_PANEL_DISP_BIT_MODE)
    {
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
        case _PANEL_DISP_18_BIT:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE18Bit, tDDITHER_ADVANCE_SETTING_TABLE18Bit, GET_CURRENT_BANK_NUMBER());
            break;
#endif

        case _PANEL_DISP_24_BIT:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE24Bit, tDDITHER_ADVANCE_SETTING_TABLE24Bit, GET_CURRENT_BANK_NUMBER());
            break;

        case _PANEL_DISP_30_BIT:
        default:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE30Bit, tDDITHER_ADVANCE_SETTING_TABLE30Bit, GET_CURRENT_BANK_NUMBER());
            break;
    }
#endif
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

    ScalerColorDDitherAdjust(tDDITHER_TABLE, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());

#else

    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_18_BIT:
#if(_HW_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
            ScalerColorDDitherAdjust(tDDITHER_TABLE18Bit, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
#else
            ScalerColorDDitherAdjust(_NULL_POINTER, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
#endif
            break;

        case _PANEL_DISP_24_BIT:
            ScalerColorDDitherAdjust(tDDITHER_TABLE24Bit, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
            break;

        case _PANEL_DISP_30_BIT:
        default:
            ScalerColorDDitherAdjust(tDDITHER_TABLE30Bit, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
            break;
    }

#endif
}
#endif // End of #if(_D_DITHER_SUPPORT == _ON)

#if(_COLOR_IP_ANTI_ALIASING == _ON)
//--------------------------------------------------
// Description  : Set Anti-Aliasing Settings
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorAntiAliasingAdjust(EnumSelRegion enumSelRegion)
{
    if(ScalerColorAntiAliasingGetSupport(enumSelRegion) == _FALSE)
    {
        return;
    }

    StructColorAntiAliasingSetting stAntiAliasingData = {0};

    // Get Osd Data
    UserInterfaceColorGetAntiAliasingData(&(stAntiAliasingData.stAntiAliasingSetting));

    if(stAntiAliasingData.stAntiAliasingSetting.stAntiAliasingUserData.ucLevel != 0)
    {
        // Get Coef Table Data
        UserInterfaceColorGetAntiAliasingCoefTableData(&(stAntiAliasingData.stAntiAliasingSetting));

        // Wait IEN Stop
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);

        // AntiAliasing Adjust
        ScalerColorAntiAliasingAdjust(stAntiAliasingData.stAntiAliasingSetting.stAntiAliasingUserData.pulTable);
    }
    else
    {
        // aa_ip_en set off
        ScalerColorAntiAliasingSetIPEnable(_FUNCTION_OFF);
    }

    // I DB
    ScalerGlobalIDomainDBApply(_INPUT_PATH_M1_M2, _DB_APPLY_NO_POLLING);
}

//--------------------------------------------------
// Description  : Get Anti-Aliasing Support
// Input Value  : EnumSelRegion
// Output Value : bit
//--------------------------------------------------
bit UserCommonColorGetAntiAliasingSupport(EnumSelRegion enumSelRegion)
{
    return ScalerColorAntiAliasingGetSupport(enumSelRegion);
}
#endif

#if(_VGA_SUPPORT == _ON)
#if(_DIG_FILTER_ENHANCE_PHASE_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
//--------------------------------------------------
// Description  : Adjust Digital Filter Enhanced Phase Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDigitalFilterEnhancePhaseAdjust(void)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0;
    BYTE ucSpan = 0;
    SWORD shTemp = 0;
    WORD usPixelRate = (ScalerSyncGetInputPixelClk(_A0_INPUT_PORT) + 5) / 10;

    if(usPixelRate <= tDF_ENHANCE_PHASE_SETTING[0])
    {
        pData[0] = tDF_ENHANCE_PHASE_SETTING[1];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[2];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[3];
    }
    else if(usPixelRate >= tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 4])
    {
        pData[0] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 3];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 2];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 1];
    }
    else
    {
        for(ucI = 0; tDF_ENHANCE_PHASE_SETTING[ucI * 4] < usPixelRate; ucI++) {};

        ucI--;

        ucTemp = usPixelRate - tDF_ENHANCE_PHASE_SETTING[ucI * 4];
        ucSpan = tDF_ENHANCE_PHASE_SETTING[(ucI + 1) * 4] - tDF_ENHANCE_PHASE_SETTING[ucI * 4];

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 1] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 1];
        pData[0] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 1] + (SWORD)ucTemp * shTemp / ucSpan;

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 2] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 2];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 2] + (SWORD)ucTemp * shTemp / ucSpan;

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 3] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 3];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 3] + (SWORD)ucTemp * shTemp / ucSpan;
    }

    ScalerColorDigitalFilterEnhancePhaseAdjust(pData);
}
#endif // End of #if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
#endif // End of #if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)


#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
//--------------------------------------------------
// Description  : Adjust Ringing Filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorRingingFilterAdjust(void)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0;
    BYTE ucSpan = 0;
    SWORD shTemp = 0;
    WORD usPixelRate = (ScalerSyncGetInputPixelClk(_A0_INPUT_PORT) + 5) / 10;

    if(usPixelRate <= tRF_OFFSET_COEF_SETTING[0])
    {
        pData[0] = tRF_OFFSET_COEF_SETTING[1];
    }
    else if(usPixelRate >= tRF_OFFSET_COEF_SETTING[sizeof(tRF_OFFSET_COEF_SETTING) - 2])
    {
        pData[0] = tRF_OFFSET_COEF_SETTING[sizeof(tRF_OFFSET_COEF_SETTING) - 1];
    }
    else
    {
        for(ucI = 0; tRF_OFFSET_COEF_SETTING[ucI * 2] < usPixelRate; ucI++) {};

        ucI--;

        ucTemp = usPixelRate - tRF_OFFSET_COEF_SETTING[ucI * 2];
        ucSpan = tRF_OFFSET_COEF_SETTING[(ucI + 1) * 2] - tRF_OFFSET_COEF_SETTING[ucI * 2];

        shTemp = tRF_OFFSET_COEF_SETTING[((ucI + 1) * 2) + 1] - tRF_OFFSET_COEF_SETTING[(ucI * 2) + 1];
        pData[0] = tRF_OFFSET_COEF_SETTING[(ucI * 2) + 1] + (SWORD)ucTemp * shTemp / ucSpan;
    }

    ScalerColorRingingFilterAdjust(pData);
}

//--------------------------------------------------
// Description  : VGA Ringing Filter Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorRingingFilterOff(void)
{
    ScalerColorRingingFilterOff();
}
#endif // End of #if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
#endif // End of #if(_RINGING_FILTER_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Vga related color process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorVgaProc(void)
{
    if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
    {
#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
        ScalerColorDigitalFilterAdjust();
        ScalerColorDigitalFilterEnable(_FUNCTION_ON);
#endif
#endif

#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
        UserCommonColorRingingFilterAdjust();
#endif
#endif

#if(_DIG_FILTER_ENHANCE_PHASE_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
        UserCommonColorDigitalFilterEnhancePhaseAdjust();
#endif
#endif
    }
    else
    {
#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
        ScalerColorRingingFilterOff();
#endif
#endif

#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
        ScalerColorDigitalFilterEnable(_FUNCTION_OFF);
#endif
#endif
    }
}

#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
//--------------------------------------------------
// Description  : VGA Digital Filter Enable for User
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void UserCommonColorDigitalFilterEnable(EnumFunctionOnOFF enumOn)
{
    ScalerColorDigitalFilterEnable(enumOn);
}
#endif
#endif
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
//--------------------------------------------------
// Description  : Color data
// Input Value  : None
// Output Value : compensate value
//--------------------------------------------------
void UserCommonColorGetLocalDimmingData(StructColorLocalDimmingSetting *pstLocalDimmingData)
{
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usMinBlendPWMValue = 32;
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.b1BoostContrastModeEnable = _ENABLE;
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usRegionBoostAdimStep = 10;
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usRegionBoostGainStep = 10;
#endif

    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usPictureBNWTH = 995;
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usPictureBlackTH = 950;
#endif
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usAvgStepFrac = 812;
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usPercentileStepFrac = 212;
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usAvgBlackValue = 45;
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usAvgBlackStep = 600;
#endif

#if(_LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE == _ON)
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumExtroInfo0 = _EXTRO_INFO_Y_MAX;
    pstLocalDimmingData->stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumExtroInfo1 = _EXTRO_INFO_BIN0PER;
#endif

    UserInterfaceColorLocalDimmingGetData(&pstLocalDimmingData->stLocalDimmingSetting);
    if(UserCommonColorLocalDimmingGetEnableStatus() != _LOCAL_DIMMING_ENABLE)
    {
        pstLocalDimmingData->stLocalDimmingSetting.enumLocalDimmingMode = _LOCAL_DIMMING_OFF;
    }
}
#endif

#if(_SPI_SUPPORT == _ON)
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Write Local Dimming Led Driver's Register to specified region
// Input Value  : enumDeviceLedDriver --> target device
//                usStartAddr --> Start Address of Register Writing
//                usNumofData --> write reg number
//                pucReadBuffer --> buffer for storing read data
//                bApplyUpdSync --> apply UpdSync
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorSpiSetCommandRegion(EnumDeviceLedDriver enumDeviceLedDriver, WORD usStartAddr, WORD usNumofData, BYTE *pucDataBuffer, bit bApplyUpdSync)
{
#if(_LOCAL_DIMMING_FUNCTION == _ON)
    if(ScalerColorLDPwmToSpiCheckSramModeEnable() == _TRUE)
    {
        if(ScalerColorLDPwmToSpiWaitToIdle() == _FALSE)
        {
            DebugMessageHDR("fail to set FW SPI", 0);
            return _FALSE;
        }
#if((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
        if(ScalerCpuSyncColorLDWaitScpuAdimIdle() == _FALSE)
        {
            DebugMessageHDR("fail to set FW SPI", 0);
            return _FALSE;
        }
#endif
#endif
    }
#endif

    if(enumDeviceLedDriver == _DEVICE_LED_DRIVER_ALL)
    {
        if(ScalerSpiDimmingRegWriteAll(usStartAddr, usNumofData, pucDataBuffer, 0) == _FALSE)
        {
            return _FALSE;
        }
    }
    else
    {
        if(((WORD)enumDeviceLedDriver) > (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM))
        {
            return _FALSE;
        }

        if(((WORD)enumDeviceLedDriver) > (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM))
        {
            if(ScalerSpiDimmingRegWrite(_PWMTOSPI_INTERFACE_2, (((WORD)enumDeviceLedDriver) - (_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM + _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM) - 1), usStartAddr, usNumofData, pucDataBuffer) == _FALSE)
            {
                return _FALSE;
            }
        }
        else if(((WORD)enumDeviceLedDriver) > _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM)
        {
            if(ScalerSpiDimmingRegWrite(_PWMTOSPI_INTERFACE_1, (((WORD)enumDeviceLedDriver) - _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM - 1), usStartAddr, usNumofData, pucDataBuffer) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
        {
            if(ScalerSpiDimmingRegWrite(_PWMTOSPI_INTERFACE_0, (((WORD)enumDeviceLedDriver) - 1), usStartAddr, usNumofData, pucDataBuffer) == _FALSE)
            {
                return _FALSE;
            }
        }
    }

    if(bApplyUpdSync == _TRUE)
    {
        ScalerSpiDimmingToggleUpdateSync();
    }

    return _TRUE;
}
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Color data
// Input Value  : None
// Output Value : compensate value
//--------------------------------------------------
void UserCommonColorLocalDimmingDCRHandler(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    g_stColorLocalDimmingDCRData.ucColorDCRMaxY = ScalerColorDCRMaxYStoreResult();
#endif
#if(_HW_DCR_BIT == _DCR_10BIT)
    g_stColorLocalDimmingDCRData.ulColorCurrentBlackNum = ScalerColorDCRReadResult_10BIT(_DCR_ABOVE_TH1_NUM);
    g_stColorLocalDimmingDCRData.ulColorCurrentWhiteNum = ScalerColorDCRReadResult_10BIT(_DCR_ABOVE_TH2_NUM);
#if((_LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE) || (_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON))
    g_stColorLocalDimmingDCRData.ucMaxR = (BYTE)((ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_R)) >> 2);
    g_stColorLocalDimmingDCRData.ucMaxG = (BYTE)((ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_G)) >> 2);
    g_stColorLocalDimmingDCRData.ucMaxB = (BYTE)((ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_VAL_B)) >> 2);
    g_stColorLocalDimmingDCRData.ucMinR = (BYTE)((ScalerColorDCRReadResult_10BIT(_DCR_LOW_LV_VAL_R)) >> 2);
    g_stColorLocalDimmingDCRData.ucMinG = (BYTE)((ScalerColorDCRReadResult_10BIT(_DCR_LOW_LV_VAL_G)) >> 2);
    g_stColorLocalDimmingDCRData.ucMinB = (BYTE)((ScalerColorDCRReadResult_10BIT(_DCR_LOW_LV_VAL_B)) >> 2);
#endif
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    g_stColorLocalDimmingDCRData.ulColorMaxRNum = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_NUM_R);
    g_stColorLocalDimmingDCRData.ulColorMaxGNum = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_NUM_G);
    g_stColorLocalDimmingDCRData.ulColorMaxBNum = ScalerColorDCRReadResult_10BIT(_DCR_HIGH_LV_NUM_B);
#endif
#endif
}
#endif

//--------------------------------------------------
// Description  : Get HLW INSIDE or OUTSIDE
// Input Value  : EnumSelRegion
// Output Value : EnumHLWType
//--------------------------------------------------
EnumHLWType UserCommonColorGetSelectRegionHLWArea(EnumSelRegion enumSelRegion)
{
    return ScalerRegionGetSelectRegionHLWArea(enumSelRegion);
}

//--------------------------------------------------
// Description  : Multi Color Function Region Enable Start
// Input Value  : EnumSelRegion
//                usColorFunction(EnumColorFunction)
//                Ex.(_COLOR_FUNCTION_DCC | _COLOR_FUNCTION_ICM)
// Output Value : None
//--------------------------------------------------
void UserCommonColorMultiFunctionRegionEnableStart(EnumSelRegion enumSelRegion, WORD usColorFunction)
{
    enumSelRegion = enumSelRegion;
    usColorFunction = usColorFunction;

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
    if((usColorFunction & _COLOR_FUNCTION_ULTRA_VIVID) == _COLOR_FUNCTION_ULTRA_VIVID)
    {
        UserCommonColorUltraVividRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#if(_COLOR_IP_LSR == _ON)
        SET_LSR_REGION_ENABLE(enumSelRegion, _OFF);
#endif

#if(_COLOR_IP_DSHP == _ON)
        SET_DSHP_REGION_ENABLE(enumSelRegion, _OFF);
#endif
    }
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
    if((usColorFunction & _COLOR_FUNCTION_LOCAL_CONTRAST) == _COLOR_FUNCTION_LOCAL_CONTRAST)
    {
        UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_DCC == _ON)
    if((usColorFunction & _COLOR_FUNCTION_DCC) == _COLOR_FUNCTION_DCC)
    {
        UserCommonColorDCCRegionEnable (enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_DCC_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_ICM == _ON)
    if((usColorFunction & _COLOR_FUNCTION_ICM) == _COLOR_FUNCTION_ICM)
    {
        UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_ICM_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if((_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) && (_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_1))
    if((usColorFunction & _COLOR_FUNCTION_D_COLOR_CONV) == _COLOR_FUNCTION_D_COLOR_CONV)
    {
        UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, _OFF);
        SET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_IAPS == _ON)
    if((usColorFunction & _COLOR_FUNCTION_IAPS) == _COLOR_FUNCTION_IAPS)
    {
        UserCommonColorIAPSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_IAPS_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
    if((usColorFunction & _COLOR_FUNCTION_CTS_BRI) == _COLOR_FUNCTION_CTS_BRI)
    {
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_CTS_BRI_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
    if((usColorFunction & _COLOR_FUNCTION_3DGAMMA) == _COLOR_FUNCTION_3DGAMMA)
    {
        UserCommonColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_3DGAMMA_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
    if((usColorFunction & _COLOR_FUNCTION_PCM) == _COLOR_FUNCTION_PCM)
    {
        UserCommonColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_PCM_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_SRGB == _ON)
    if((usColorFunction & _COLOR_FUNCTION_SRGB) == _COLOR_FUNCTION_SRGB)
    {
        UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_SRGB_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
    if((usColorFunction & _COLOR_FUNCTION_UNIFORMITY) == _COLOR_FUNCTION_UNIFORMITY)
    {
        UserCommonColorPanelUniformityRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_UNIFORMITY_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
    if((usColorFunction & _COLOR_FUNCTION_GAMMA) == _COLOR_FUNCTION_GAMMA)
    {
        UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        SET_GAMMA_REGION_ENABLE(enumSelRegion, _OFF);
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    ScalerGlobalIDDomainDBApply(UserCommonRegionGetInputDataPath(UserCommonColorDMGetDisplayRegion(enumSelRegion)), _DB_APPLY_POLLING);
#endif
#else
#if((_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) && (_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_0))
    if((usColorFunction & _COLOR_FUNCTION_NIGHT_SNIPER) == _COLOR_FUNCTION_NIGHT_SNIPER)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);

        UserCommonColorSpaceConvertNightSniperEnable(_FULL_REGION, _OFF);
        SET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion, _OFF);
    }
    else
#endif
    {
        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
    }
#endif

    // acquire global D-domain DB lock to prevent DB apply in interrupt
    GET_GLOBAL_D_DB_LOCK();
}

//--------------------------------------------------
// Description  : Multi Color Function Region Enable End
// Input Value  : EnumSelRegion
//                usColorFunction(EnumColorFunction)
//                Ex.(_COLOR_FUNCTION_DCC | _COLOR_FUNCTION_ICM)
// Output Value : None
//--------------------------------------------------
void UserCommonColorMultiFunctionRegionEnableEnd(EnumSelRegion enumSelRegion, WORD usColorFunction)
{
    enumSelRegion = enumSelRegion;
    usColorFunction = usColorFunction;

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
    if((usColorFunction & _COLOR_FUNCTION_ULTRA_VIVID) == _COLOR_FUNCTION_ULTRA_VIVID)
    {
#if(_COLOR_IP_LSR == _ON)
        SET_LSR_REGION_ENABLE(enumSelRegion, _ON);
#endif

#if(_COLOR_IP_DSHP == _ON)
        SET_DSHP_REGION_ENABLE(enumSelRegion, _ON);
#endif
    }
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
    if((usColorFunction & _COLOR_FUNCTION_LOCAL_CONTRAST) == _COLOR_FUNCTION_LOCAL_CONTRAST)
    {
        SET_LOCALCONTRAST_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_DCC == _ON)
    if((usColorFunction & _COLOR_FUNCTION_DCC) == _COLOR_FUNCTION_DCC)
    {
        SET_DCC_REGION_ENABLE(enumSelRegion, _ON);
    }

#endif

#if(_COLOR_IP_ICM == _ON)
    if((usColorFunction & _COLOR_FUNCTION_ICM) == _COLOR_FUNCTION_ICM)
    {
        SET_ICM_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if((_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) && (_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_1))
    if((usColorFunction & _COLOR_FUNCTION_D_COLOR_CONV) == _COLOR_FUNCTION_D_COLOR_CONV)
    {
        UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, UserCommonColorGetNightSniperEnableStatus(enumSelRegion));
        SET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_IAPS == _ON)
    if((usColorFunction & _COLOR_FUNCTION_IAPS) == _COLOR_FUNCTION_IAPS)
    {
        SET_IAPS_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
    if((usColorFunction & _COLOR_FUNCTION_CTS_BRI) == _COLOR_FUNCTION_CTS_BRI)
    {
        SET_CTS_BRI_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
    if((usColorFunction & _COLOR_FUNCTION_3DGAMMA) == _COLOR_FUNCTION_3DGAMMA)
    {
        SET_3DGAMMA_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
    if((usColorFunction & _COLOR_FUNCTION_PCM) == _COLOR_FUNCTION_PCM)
    {
        SET_PCM_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_SRGB == _ON)
    if((usColorFunction & _COLOR_FUNCTION_SRGB) == _COLOR_FUNCTION_SRGB)
    {
        SET_SRGB_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
    if((usColorFunction & _COLOR_FUNCTION_UNIFORMITY) == _COLOR_FUNCTION_UNIFORMITY)
    {
        SET_UNIFORMITY_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
    if((usColorFunction & _COLOR_FUNCTION_GAMMA) == _COLOR_FUNCTION_GAMMA)
    {
        SET_GAMMA_REGION_ENABLE(enumSelRegion, _ON);
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    ScalerGlobalIDDomainDBApply(UserCommonRegionGetInputDataPath(UserCommonColorDMGetDisplayRegion(enumSelRegion)), _DB_APPLY_POLLING);
#endif
#else
#if((_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) && (_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_0))
    if(((usColorFunction & _COLOR_FUNCTION_NIGHT_SNIPER) == _COLOR_FUNCTION_NIGHT_SNIPER) && (UserCommonColorNightSniperCheckStatus(enumSelRegion) == _TRUE))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_NO_POLLING);

        UserCommonColorSpaceConvertNightSniperEnable(enumSelRegion, UserCommonColorGetNightSniperEnableStatus(enumSelRegion));
        SET_NIGHT_SNIPER_REGION_ENABLE(enumSelRegion, _ON);
    }
    else
#endif
    {
        UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
    }
#endif

    // release global D-domain DB lock
    CLR_GLOBAL_D_DB_LOCK();
}

//--------------------------------------------------
// Description  : Bypass Color Function
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorBypassHLWSelRegionColorFunction(EnumSelRegion enumSelRegion)
{
    enumSelRegion = enumSelRegion;

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
    UserCommonColorUltraVividRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
    UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_DCC == _ON)
    UserCommonColorDCCRegionEnable (enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_ICM == _ON)
    UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_IAPS == _ON)
    UserCommonColorIAPSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
    UserCommonColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
    UserCommonColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_SRGB == _ON)
    UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
    UserCommonColorPanelUniformityRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
    UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
    UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
}

#if(_COLOR_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get Demo Mode Status
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDemoModeType UserCommonColorGetDemoModeType(void)
{
#if((_DM_FUNCTION == _ON) && (_IS_MAIN_PROCESS_CPU == _TRUE))
#if(_DM_CUSTOM_COLOR_SUPPORT == _OFF)
    if(UserCommonColorDemoModeSupportCheck() == _FALSE)
    {
        return _DEMO_OFF;
    }
#endif
#endif

    switch(UserInterfaceColorGetDemoModeType())
    {
        case _DEMO_MODE_BOTH:
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
            return _DEMO_MODE_BOTH;// apply double side color
#else
            return _DEMO_MODE_INSIDE;// force to apply Inside color
#endif

        case _DEMO_MODE_INSIDE:
            return _DEMO_MODE_INSIDE;

        case _DEMO_MODE_OUTSIDE:
            return _DEMO_MODE_OUTSIDE;

        case _DEMO_OFF:
        default:
            return _DEMO_OFF;
    }
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set EagleSight Circle Window
// Input Value  : Double Buffer
// Output Value : None
//--------------------------------------------------
void UserCommonColorCircleWindowAdjust(EnumDBApply enumDBApply)
{
    StructColorCircleWindowSetting stCircleWindow = {0};

    if(GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE() == _ON)
    {
        UserCommonColorGetCircleWindowData(&stCircleWindow);
        ScalerColorIPCircleWindowAdjust(&stCircleWindow, enumDBApply);
    }
    else
    {
        UserCommonColorGetCircleWindowData(&stCircleWindow);
        ScalerColorIPCircleWindowAdjust(&stCircleWindow, _DB_APPLY_NONE);
#if(_COLOR_IP_HL_WIN == _ON)
        UserCommonColorHLWinTypeAdjust(_DB_APPLY_NONE);
#endif
        UserCommonColorBorderWindowAdjust(enumDBApply);
    }
}
//--------------------------------------------------
// Description  : BORDER WINDOW UserCommon function
// Input Value  : StructColorCircleWindowSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorGetCircleWindowData(StructColorCircleWindowSetting *pstCircleWindowData)
{
    UserInterfaceColorGetCircleWindowData(&pstCircleWindowData->stCircleWindowSetting);
}
//--------------------------------------------------
// Description  : BORDER WINDOW UserCommon function
// Input Value  : StructColorCircleWindowSetting
// Output Value : None
//--------------------------------------------------
void UserCommonColorSetCircleWindowBorderEnable(bit bEnable, EnumDBApply enumDBApply)
{
    ScalerColorPIPBlendingSetCircleWindowBorderEnable(bEnable);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif
#endif

#if(_DYNAMIC_COLOR_AUTO_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Initial Boundary for dynamic crosshair color
// Input Value  : usDHStart, usDHEnd, usDVStart, usDVEnd
// Output Value : void
//--------------------------------------------------
void UserCommonColorSetDynamicColorInitialBoundary(WORD usDHStart, WORD usDHEnd, WORD usDVStart, WORD usDVEnd)
{
    EnumDisplayMode enumDisplayMode = SysModeGetDisplayMode();
    EnumDisplayRegion enumDisplayRegion = SysRegionGetDisplayRegion(_REGION_INDEX_0);

    StructTimingInfo stTimingInfo;
    memset(&stTimingInfo, 0x00, sizeof(stTimingInfo));

    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumDisplayRegion, &stTimingInfo);

    stTimingInfo.usHStart = (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usHActiveStart);
    stTimingInfo.usVStart = (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if(enumDisplayMode != _DISPLAY_MODE_1P)
    {
        return;
    }

    // Set measure HV boundary
    ScalerMeasureDynamicColorInitial(&stTimingInfo, usDHStart, usDHEnd, usDVStart, usDVEnd);
}

//--------------------------------------------------
// Description  : Start Auto function measure for color value
// Input Value  : usDHStart, usDHEnd, ucColor
// Output Value : void
//--------------------------------------------------
void UserCommonColorSetAutoMeasure(WORD usDHStart, WORD usDHEnd, EnumAutoChannelType enumAutoChannelType)
{
    ScalerMeasureDynamicColorSetAutoMeasure(usDHStart, usDHEnd, enumAutoChannelType);
}

//--------------------------------------------------
// Description  : Get Auto measure value for dynamic crosshair color
// Input Value  : usDHStart, usDHEnd, ucColor, bWait
// Output Value : _TRUE if auto-function measure passed
//--------------------------------------------------
bit UserCommonColorGetDynamicColorMeasureResult(BYTE *pucMeasureResult, WORD usDHStart, WORD usDHEnd, bit bWait)
{
    StructAutoActiveData stAutoData = {0};

    if(ScalerMeasureDynamicColorGetResult(&stAutoData.ucColorAverageValue, usDHStart, usDHEnd, bWait) == _FALSE)
    {
        return _FALSE;
    }

    *pucMeasureResult = stAutoData.ucColorAverageValue;

    return _TRUE;
}
#endif

#if(_3DDI_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Decide if to enable 3DDI or not
// Input Value  : enumInputPort
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit UserCommonColor3DDIEnableDecision(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
    return Scaler3DDIEnableDecision(UserCommonRegionGetInputDataPath(enumDisplayRegion), enumInputPort);
}
#endif

//--------------------------------------------------
// Description  : Reset Advance HDR /HDR10 /DM Color Setting
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorResetColor(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    UserCommonColorAdvancedHDR10Reset();
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    UserCommonColorDMReset(enumDisplayRegion);
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    CLR_HDR10_SETTING_DATA(enumDisplayRegion);
    CLR_HDR10_USER_DATA(enumDisplayRegion);
    SET_HDR10_MODE_STATUS(enumDisplayRegion, _HDR10_MODE_OFF);

#if(_HDMI_SBTM_SUPPORT == _ON)
    CLR_SBTM_INFO_DATA(enumDisplayRegion);
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    CLR_FREESYNC_II_INFO_DATA(enumDisplayRegion);
    CLR_FREESYNC_II_SETTING_DATA(enumDisplayRegion);
    SET_FREESYNC_II_MODE_STATUS(enumDisplayRegion, _FREESYNC_SUPPORT_OFF);
#endif
}
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)

//--------------------------------------------------
// Description  : Low Blue Initial buffers and clear uniformity table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
    if((GET_DISPLAY_MODE() != _DISPLAY_MODE_1P) &&
       (GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT))
    {
        bOn = _OFF;
        enumSelRegion = _1P_NORMAL_REGION;
    }
    ScalerColorPanelUniformityRegionEnable(enumSelRegion, enumDBApply, bOn);
}

//--------------------------------------------------
// Description  : Low Blue Initial buffers and clear uniformity table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueInitial(void)
{
    // clear uniformity sram data
#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _ON)
    ScalerColorPanelUniformityLowBlueLightInitial();
    ScalerColorPanelUniformityLowBlueClearSram(_DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS * _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS);
#endif
    UserCommonColorMRCMLowBlueReset();
}

//--------------------------------------------------
// Description  : Set LowBlue Mode Color Setting
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueAdjust(EnumSelRegion enumSelRegion)
{
    UserCommonColorLowBlueGetData(&g_stColorDynamicLowBlueSetting);
    // Set MRCM to LowBlue Mode case
    UserCommonColorMRCMAdjust();
    switch(UserCommonColorGetLowBlueStatus())
    {
        case _LOWBLUE_MODE_OFF:
            // reset uniformity sram data to 0
#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _ON)
            ScalerColorPanelUniformityDBModeEnable(_FUNCTION_OFF);
#endif
            UserCommonColorLowBlueInitial();
            UserCommonColorLowBlueRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
            break;
        case _LOWBLUE_MODE_STATIC_GLOBAL:
#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _ON)
            ScalerColorPanelUniformityLowBlueLightInitial();
#endif
            UserCommonColorLowBlueStaticGlobalAdjust();
            UserCommonColorLowBlueRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
            break;
        default:
            // Set Panel Uniformity regs
#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _ON)
            ScalerColorPanelUniformityDBModeEnable(_FUNCTION_ON);
            ScalerColorPanelUniformityLowBlueLightInitial();
#endif
            UserCommonColorLowBlueRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
            break;
    }
}

//--------------------------------------------------
// Description  : Get LowBlue Mode
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
EnumDynamicLowBlueType UserCommonColorGetLowBlueStatus(void)
{
    // handle if can enable low blue
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
    if((GET_DISPLAY_MODE() != _DISPLAY_MODE_1P) &&
       (GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT))
    {
        return _LOWBLUE_MODE_OFF;
    }
    if((GET_ON_LINE_CALIBRATION_STATUS() == _CALIBRATION_OFF) &&
       (UserInterfaceColorLowBlueGetEnableStatus() != _LOWBLUE_MODE_OFF))
    {
#if(_COLOR_IP_O_GAMMA == _ON)
        StructColorOutGammaSetting stOutGamma = {0};
        UserCommonColorGetOutGammaData(UserCommonModeDisplaySettingGetSelRegion(enumDisplayRegion), &stOutGamma);
        if((stOutGamma.stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_OFF) ||
           (stOutGamma.stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_OGC) ||
           (stOutGamma.stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_DICOM) ||
           (stOutGamma.stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_DM) ||
           (stOutGamma.stOutGammaSetting.enumOutGammaMode == _OUTGAMMA_USER))
        {
            return _LOWBLUE_MODE_OFF;
        }
#endif
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_DISABLE)
#endif
        {
            return g_stColorDynamicLowBlueSetting.enumDynamicLowBlueType;
        }
    }
    enumDisplayRegion = enumDisplayRegion; // for compile warning
    return _LOWBLUE_MODE_OFF;
}

//--------------------------------------------------
// Description  :UserCommon Get LowBlue setting data
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueGetData(StructColorDynamicLowBlueSetting *pstDynamicLowBlueSetting)
{
    StructColorEyeProtectSetting stColorEyeProtectSetting = {0};
    BYTE pucParaSetting[42] = {0};
    BYTE ucMatrixSize = 0;
    EnumEyeProtectLevel enumEyeProtectLevel = _EYE_PROTECT_LEVEL0;
    UserInterfaceColorLowBlueGetData(&stColorEyeProtectSetting);

    /// Reserved for read from flash
    /// ...
    ///

    // get panel setting table from flash
    ScalerFlashRead(stColorEyeProtectSetting.stColorLowBlueUserSetting.ucBank,
                    stColorEyeProtectSetting.stColorLowBlueUserSetting.pucParaSetting,
                    42, pucParaSetting);
    // get low blue smooth matrix length
    ScalerFlashRead(stColorEyeProtectSetting.stColorLowBlueUserSetting.ucBank,
                    stColorEyeProtectSetting.stColorLowBlueUserSetting.pucBlurMatrix,
                    1, &ucMatrixSize);
    // get low blue smooth matrix
    ScalerFlashRead(stColorEyeProtectSetting.stColorLowBlueUserSetting.ucBank,
                    stColorEyeProtectSetting.stColorLowBlueUserSetting.pucBlurMatrix,
                    ucMatrixSize * ucMatrixSize + 1, pstDynamicLowBlueSetting->pucBlurMatrix);
    // get low blue panel data for algo
    enumEyeProtectLevel = stColorEyeProtectSetting.stColorLowBlueUserSetting.enumEyeProtectLevel;
    pstDynamicLowBlueSetting->enumDynamicLowBlueType = stColorEyeProtectSetting.enumDynamicLowBlueType;
    pstDynamicLowBlueSetting->usHazardRmax = TO_WORD(pucParaSetting[0], pucParaSetting[1]);
    pstDynamicLowBlueSetting->usHazardGmax = TO_WORD(pucParaSetting[2], pucParaSetting[3]);
    pstDynamicLowBlueSetting->usHazardBmax = TO_WORD(pucParaSetting[4], pucParaSetting[5]);

    pstDynamicLowBlueSetting->usRegionPixelThd = TO_WORD(pucParaSetting[6], pucParaSetting[7]);
    pstDynamicLowBlueSetting->usHazardTarget = TO_WORD(pucParaSetting[10 + enumEyeProtectLevel * 8], pucParaSetting[11 + enumEyeProtectLevel * 8]);
    pstDynamicLowBlueSetting->usGainR = TO_WORD(pucParaSetting[12 + enumEyeProtectLevel * 8], pucParaSetting[13 + enumEyeProtectLevel * 8]);
    pstDynamicLowBlueSetting->usGainG = TO_WORD(pucParaSetting[14 + enumEyeProtectLevel * 8], pucParaSetting[15 + enumEyeProtectLevel * 8]);
    pstDynamicLowBlueSetting->usGainB = TO_WORD(pucParaSetting[16 + enumEyeProtectLevel * 8], pucParaSetting[17 + enumEyeProtectLevel * 8]);
    pstDynamicLowBlueSetting->usGainStepB = pstDynamicLowBlueSetting->usGainB / TO_WORD(pucParaSetting[8], pucParaSetting[9]);

    // if user set Nigh Mode on, set usGainOffset
    if(stColorEyeProtectSetting.stColorLowBlueUserSetting.bNightModeEnable)
    {
        pstDynamicLowBlueSetting->usGainOffset = (pstDynamicLowBlueSetting->usGainB * stColorEyeProtectSetting.stColorLowBlueUserSetting.ucNightModeGainPercent) / 100;
    }
    else
    {
        pstDynamicLowBlueSetting->usGainOffset = 0;
    }
}

//--------------------------------------------------
// Description  : DynamicLowBlue Algo
// Input Value  : pusCurrentGainB WORD array
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueLocalAdjust(WORD *pusCurrentGainB)
{
    // WORD pusTempArray[_DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS * _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS] = {0};
    // WORD pusOutArray[_DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS * _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS] = {0};
    WORD pusTempArray[_DYNAMIC_LOWBLUE_UNIFORMITY_NODE_NUM] = {0};
    WORD pusOutArray[_DYNAMIC_LOWBLUE_UNIFORMITY_NODE_NUM] = {0};

    WORD usI = 0;
    WORD usJ = 0;
    BYTE ucUniHorInterval = _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_INTERVAL;
    BYTE ucUniVerInterval = _DYNAMIC_LOWBLUE_UNIFORMITY_VER_INTERVAL;
    BYTE ucUniHorGrids = _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS;
    BYTE ucUniVerGrids = _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS;

    WORD usLowBlueGainR = g_stColorDynamicLowBlueSetting.usGainR;
    WORD usLowBlueGainG = g_stColorDynamicLowBlueSetting.usGainG;
    WORD usLowBlueGainB = g_stColorDynamicLowBlueSetting.usGainB;
    WORD usCurrentIndex = 1;
    WORD usWriteLimitLength = _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS * _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS;

    WORD usTempB = 0;
    // const BYTE ucMatrixSize = 13;
    BYTE ucMatrixSize = *g_stColorDynamicLowBlueSetting.pucBlurMatrix;
    SBYTE chMid = (ucMatrixSize / 2);
    SBYTE chLeft = -(chMid);
    SBYTE chRight = (ucMatrixSize / 2) + 1;
    BYTE *pucMatrix = g_stColorDynamicLowBlueSetting.pucBlurMatrix + 1;
    SBYTE chY = 0;
    SBYTE chX = 0;
    StructColorDynamicLowBluePara stColorDynamicLowBluePara;

    if(true)
    {
        WORD usMrcmHorIndex = 0;
        WORD usMrcmVerIndex = 0;
        WORD usxpixel = ucUniHorInterval - _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_OFFSET;
        WORD usypixel = ucUniVerInterval - _DYNAMIC_LOWBLUE_UNIFORMITY_VER_OFFSET;
        WORD usMRCMHorSize = _PANEL_DH_WIDTH / _LOWBLUE_MRCM_HOR_DIVISION;
        WORD usMRCMVerSize = _PANEL_DV_HEIGHT / _LOWBLUE_MRCM_VER_DIVISION;
        // ======== initial uniformity nodes value with mrcm results ========
        for(usI = 1; usI < ucUniVerGrids - 1; usI++)
        {
            usxpixel = ucUniHorInterval - _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_OFFSET;
            usMrcmHorIndex = 0;
            if(usypixel > usMRCMVerSize)
            {
                ++usMrcmVerIndex;
                usypixel = usypixel - usMRCMVerSize;
            }
            for(usJ = 1; usJ < ucUniHorGrids - 1; usJ++)
            {
                if(usxpixel > usMRCMHorSize)
                {
                    ++usMrcmHorIndex;
                    usxpixel = usxpixel - usMRCMHorSize;
                }
                usMrcmHorIndex = MINOF(usMrcmHorIndex, _LOWBLUE_MRCM_HOR_DIVISION - 1);
                usMrcmVerIndex = MINOF(usMrcmVerIndex, _LOWBLUE_MRCM_VER_DIVISION - 1);
                pusTempArray[(WORD)(usJ + usI * ucUniHorGrids)] = pusCurrentGainB[usMrcmHorIndex + (usMrcmVerIndex * _LOWBLUE_MRCM_HOR_DIVISION)]; // * 8
                usxpixel = usxpixel + ucUniHorInterval;
            }
            usypixel = usypixel + ucUniVerInterval;
        }
    }
    memcpy(pusOutArray, pusTempArray, sizeof(pusTempArray));

    // ========= Blur Matrix ========
    usCurrentIndex = usCurrentIndex + ucUniHorGrids;
    for(usJ = 1; usJ < ucUniVerGrids - 1; usJ++)
    {
        for(usI = 1; usI < ucUniHorGrids - 1; usI++)
        {
            // usCurrentIndex = (ucUniHorGrids * usJ + usI);
            if((pusTempArray[usCurrentIndex + ucUniHorGrids] < pusTempArray[usCurrentIndex]) || (pusTempArray[usCurrentIndex - ucUniHorGrids] < pusTempArray[usCurrentIndex]) ||
               (pusTempArray[usCurrentIndex + 1] < pusTempArray[usCurrentIndex]) || (pusTempArray[usCurrentIndex - 1] < pusTempArray[usCurrentIndex]))// ||
            // (pusTempArray[(ucUniHorGrids * (usJ + 1) + (usI + 1))] != pusTempArray[(ucUniHorGrids * usJ + usI)]) || (pusTempArray[(ucUniHorGrids * (usJ - 1) + (usI + 1))] != pusTempArray[(ucUniHorGrids * usJ + usI)]) ||
            // (pusTempArray[(ucUniHorGrids * (usJ + 1) + (usI - 1))] != pusTempArray[(ucUniHorGrids * usJ + usI)]) || (pusTempArray[(ucUniHorGrids * (usJ - 1) + (usI - 1))] != pusTempArray[(ucUniHorGrids * usJ + usI)]))
            {
                for(chY = chLeft; chY < chRight; chY++)
                {
                    for(chX = chLeft; chX < chRight; chX++)
                    {
                        if(((usJ + chY) > 0) && ((usI + chX) > 0) && ((usJ + chY) < ucUniVerGrids) && ((usI + chX) < ucUniHorGrids))
                        {
                            usTempB = (QWORD)(pusTempArray[usCurrentIndex] * (WORD)(pucMatrix[ucMatrixSize * (chMid + chY) + (chMid + chX)] + 1)) >> 8; // / 255;
                            if(usTempB > pusOutArray[(ucUniHorGrids * (usJ + chY) + (usI + chX))])
                            {
                                pusOutArray[(ucUniHorGrids * (usJ + chY) + (usI + chX))] = usTempB;
                            }
                        }
                    }
                }
            }
            usCurrentIndex = usCurrentIndex + 1;
        }
        usCurrentIndex = usCurrentIndex + 2;
    }
    // ============================ fill out the outer region uniformity nodes =========================
    for(usI = 0; usI < ucUniHorGrids; usI++)
    {
        if(pusOutArray[ucUniHorGrids + usI] != 0)
        {
            pusOutArray[usI] = pusOutArray[ucUniHorGrids + usI]; // uni_gain = 1 - code_gain
        }
        if(pusOutArray[(ucUniHorGrids * (ucUniVerGrids - 2) + usI)] != 0)
        {
            pusOutArray[(ucUniHorGrids * (ucUniVerGrids - 1) + usI)] = pusOutArray[(ucUniHorGrids * (ucUniVerGrids - 2) + usI)]; // uni_gain = 1 - code_gain
        }
    }
    for(usI = 0; usI < ucUniVerGrids; usI++)
    {
        usCurrentIndex = ucUniHorGrids * usI;
        if(pusOutArray[usCurrentIndex + 1] != 0)
        {
            pusOutArray[usCurrentIndex] = pusOutArray[(usCurrentIndex + 1)]; // uni_gain = 1 - code_gain
        }
        if(pusOutArray[(usCurrentIndex + (ucUniHorGrids - 2))] != 0)
        {
            pusOutArray[(usCurrentIndex + (ucUniHorGrids - 1))] = pusOutArray[(usCurrentIndex + (ucUniHorGrids - 2))]; // uni_gain = 1 - code_gain
        }
    }
    // ========= Write to Register ========
    stColorDynamicLowBluePara.pusGainArray = pusOutArray;
    stColorDynamicLowBluePara.usLength = usWriteLimitLength;
    stColorDynamicLowBluePara.usLowBlueGainR = usLowBlueGainR;
    stColorDynamicLowBluePara.usLowBlueGainG = usLowBlueGainG;
    stColorDynamicLowBluePara.usLowBlueGainB = usLowBlueGainB;
    ScalerColorPanelUniformityLowBlueAdjust(stColorDynamicLowBluePara);
}

//--------------------------------------------------
// Description  : DynamicLowBlue Algo for old static Global Mode
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueStaticGlobalAdjust(void)
{
    // WORD pusOutArray[_PANEL_UNIFORMITY_HOR_GRIDS * _PANEL_UNIFORMITY_VER_GRIDS] = {0};
    WORD pusOutArray[_DYNAMIC_LOWBLUE_UNIFORMITY_NODE_NUM] = {0};
    BYTE ucI = 0;
    BYTE ucJ = 0;
    BYTE ucUniHorGrids = _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS;
    BYTE ucUniVerGrids = _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS;
    WORD usLowBlueGainR = g_stColorDynamicLowBlueSetting.usGainR;// 0;
    WORD usLowBlueGainG = g_stColorDynamicLowBlueSetting.usGainG;// 24;
    WORD usLowBlueGainB = g_stColorDynamicLowBlueSetting.usGainB;// 403
    WORD usWriteLimitLength = _DYNAMIC_LOWBLUE_UNIFORMITY_HOR_GRIDS * _DYNAMIC_LOWBLUE_UNIFORMITY_VER_GRIDS;
    StructColorDynamicLowBluePara stColorDynamicLowBluePara;
    // ======== initial uniformity nodes value with mrcm results ========
    if(true)
    {
        for(ucI = 0; ucI < ucUniVerGrids; ucI++)
        {
            for(ucJ = 0; ucJ < ucUniHorGrids; ucJ++)
            {
                pusOutArray[(WORD)(ucJ + ucI * ucUniHorGrids)] = usLowBlueGainB;
            }
        }
    }
    // ========= Write to Register ========
    stColorDynamicLowBluePara.pusGainArray = pusOutArray;
    stColorDynamicLowBluePara.usLength = usWriteLimitLength;
    stColorDynamicLowBluePara.usLowBlueGainR = usLowBlueGainR;
    stColorDynamicLowBluePara.usLowBlueGainG = usLowBlueGainG;
    stColorDynamicLowBluePara.usLowBlueGainB = usLowBlueGainB;
    ScalerColorPanelUniformityLowBlueAdjust(stColorDynamicLowBluePara);
}
#endif