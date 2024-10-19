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
// ID Code      : RTD2020UserInterfaceColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_COLOR__
#define __USER_PANEL__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColor.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_ULTRA_VIVID_FUNCTION == _ON)

//----------------------------------------------------------------------------------------------------
// ULTRAVIVID TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_ULTRAVIVID_SETTING_L[] =
{
#include "./UltraVivid/UltraVividTableL.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_M[] =
{
#include "./UltraVivid/UltraVividTableM.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_H[] =
{
#include "./UltraVivid/UltraVividTableH.h"
};

BYTE * code tCOLOR_ULTRAVIVID_SETTING_TABLE[] =
{
    tCOLOR_ULTRAVIVID_SETTING_L,
    tCOLOR_ULTRAVIVID_SETTING_M,
    tCOLOR_ULTRAVIVID_SETTING_H,
};

#if(_HDR10_SUPPORT == _ON)
BYTE code tCOLOR_ULTRAVIVID_SETTING_HDR[] =
{
#include "./UltraVivid/UltraVividTableHDR.h"
};
#endif

#if(_DM_FUNCTION == _ON)
BYTE code tCOLOR_ULTRAVIVID_SETTING_TABLE_DM[] =
{
#include "./UltraVivid/UltraVividTableDM.h"
};
#endif

#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DCC_FUNCTION == _ON)
EnumSelRegion g_enumColorDCCMeasureRegion = _NON_REGION;
#endif

#if(_COLOR_DEMO_FUNCTION == _ON)
bit g_bColorHLWinRLMove = _RIGHT;
WORD g_usColorHLWinHPos;
WORD g_usColorHLWinHWidth;
WORD g_usColorHLWinVPos;
WORD g_usColorHLWinVHeight;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_COLOR_CONVERT == _ON)
//--------------------------------------------------
// Description  : Get OSD Color Format
// Input Value  : display Region
// Output Value : Color Format is RGB or not
//--------------------------------------------------
EnumRGBFormatStatus UserInterfaceColorGetColorRGBFormat(EnumDisplayRegion enumDisplayRegion)
{
    EnumColorSpace enumColorSpace = UserCommonColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion));

    switch(SysRegionGetSourceType(enumDisplayRegion))
    {
        case _SOURCE_VGA:
        case _SOURCE_DVI:
            enumColorSpace = GET_OSD_COLOR_FORMAT(SysRegionGetInputPort(enumDisplayRegion));
            break;

        default:
            break;
    }

    if(UserCommonColorGetColorSpaceRGB(enumColorSpace) == _TRUE)
    {
        return _RGB_FORMAT_TRUE;
    }
    else
    {
        return _RGB_FORMAT_FALSE;
    }
}
#endif

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Color Format when specific region not first active
// Input Value  : display Region
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorSetColorFormat(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
    EnumSourceType enumSourceType = SysRegionGetSourceType(enumDisplayRegion);

    if(SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_FIRST_ACTIVE) == _FALSE)
    {
        // Set Color Conversion
        if(enumSourceType == _SOURCE_VGA)
        {
            SET_OSD_COLOR_FORMAT(enumInputPort, GET_VGA_COLOR_FORMAT_STATUS());
        }
        else if(enumSourceType == _SOURCE_DVI)
        {
            SET_OSD_COLOR_FORMAT(enumInputPort, GET_DVI_COLOR_FORMAT_STATUS());
        }
        else
        {
            if(UserCommonColorGetColorSpaceRGB(UserCommonColorGetColorSpace(enumInputPort)) == _TRUE)
            {
                SET_OSD_COLOR_FORMAT(enumInputPort, _COLOR_SPACE_RGB);
            }
            else
            {
                SET_OSD_COLOR_FORMAT(enumInputPort, _COLOR_SPACE_YPBPR);
            }
        }
    }
}
#endif

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
//--------------------------------------------------
// Description  : User Judge if Quantization Range is Full or Limited
// Input Value  : EnumDisplayRegion --> display region
//                ucQuanRange --> quantization status
// Output Value : _RGB_QUANT_LIMIT_RANGE_TRUE
//                _RGB_QUANT_LIMIT_RANGE_FALSE
//--------------------------------------------------
EnumRGBQuantLimitRangeStatus UserInterfaceColorGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) != _HDR10_OFF)
    {
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
    else
#endif
    {
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
}
#endif

#if((_YCC_QUANTIZATION_RANGE_FUNCTION == _ON) && (_YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
//--------------------------------------------------
// Description  : User Judge if YCC Quantization Range is Full or Limited
// Input Value  : EnumDisplayRegion --> display region
//                bQuanRange --> quantization status
// Output Value : _YCC_QUANT_FULL_RANGE_TRUE
//                _YCC_QUANT_FULL_RANGE_FALSE
//--------------------------------------------------
EnumYccQuantFullRangeStatus UserInterfaceColorGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization)
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
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User function Adjust for sRGB
// Input Value  : Select Region, sRGB setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetDColorConvertData(EnumSelRegion enumSelRegion, StructDColorConvertSetting *pstDColorConvertData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);


#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) != _OFF)
    {
        pstDColorConvertData->enumDColorConvertMode = _D_COLOR_CONVERT_STANDARD;
        return;
    }
#endif

#if((_OCC_FUNCTION == _ON) || (_PCM_FUNCTION == _ON))
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        pstDColorConvertData->enumDColorConvertMode = _D_COLOR_CONVERT_HUE_SATURATION;
        pstDColorConvertData->unDColorConvertData.stDColorConvertHueSatData.shHue = _DEFAULT_HUE - GET_OSD_HUE(ucOSDSelectRegion);
        pstDColorConvertData->unDColorConvertData.stDColorConvertHueSatData.usSat = GET_OSD_SATURATION(ucOSDSelectRegion);
        return;
    }
    else
#endif
    {
        ucOSDSelectRegion = ucOSDSelectRegion; // for  compile warring
        pstDColorConvertData->enumDColorConvertMode = _D_COLOR_CONVERT_STANDARD;
    }
}
#endif

#if(_COLOR_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get Demo Mode Status
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDemoModeType UserInterfaceColorGetDemoModeType(void)
{
    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
        return _DEMO_MODE_BOTH;// apply double side color
#else
        switch(GET_OSD_HLWIN_SIDE())
        {
            case _OSD_HLW_OUTSIDE:
                return _DEMO_MODE_OUTSIDE;

            case _OSD_HLW_INSIDE:
            default:
                return _DEMO_MODE_INSIDE;
        }
#endif
    }

    return _DEMO_OFF;
}
#endif

#if(_DCR_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR
// Input Value  : Display Region
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDCRHandler(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_1P)
    {
        if(GET_OSD_DCR_STATUS() == _ON)
        {
#if(_HW_DCR_BIT == _DCR_8BIT)
            PDATA_DWORD(0) = UserCommonColorDCRReadResult_8BIT(_DCR_ABOVE_TH1_NUM);
#elif(_HW_DCR_BIT == _DCR_10BIT)
            PDATA_DWORD(0) = UserCommonColorDCRReadResult_10BIT(_DCR_ABOVE_TH1_NUM);
#else
#warning "_HW_DCR_BIT Not Support!!!"
#endif

#if(_HW_DCR_TH2_OPTION_SUPPORT == _ON)
#if(_HW_DCR_BIT == _DCR_8BIT)
            PDATA_DWORD(0) = UserCommonColorDCRReadResult_8BIT(_DCR_ABOVE_TH2_NUM);
#elif(_HW_DCR_BIT == _DCR_10BIT)
            PDATA_DWORD(0) = UserCommonColorDCRReadResult_10BIT(_DCR_ABOVE_TH2_NUM);
#else
#warning "_HW_DCR_BIT Not Support!!!"
#endif
#else
#warning "_DCR_ABOVE_TH2_NUM Not Support!!!"
#endif
        }
    }
}
#endif // End of #if(_DCR_SUPPORT == _ON)

#if(_DCC_HISTOGRM_INFO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User Adjust DCC Histogram
// Input Value  : Display region
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDCCHistogramHandler(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}
#endif // End of #if(_DCC_HISTOGRM_INFO == _ON)

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
//--------------------------------------------------
// Description  : User function Get Data for UltraVivid
// Input Value  : Select Region, Ultravivid settings struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetUltraVividData(EnumSelRegion enumSelRegion, StructUltraVividSetting *pstUltraVividData)
{
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        if(GET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion(enumSelRegion)) == _OSD_DVISION_PICTURE_USER)
        {
            pstUltraVividData->enumUltraVividMode = _ULTRAVIVID_DM;
            pstUltraVividData->unUltraVividData.stUltraVividDMData.ucBank = GET_CURRENT_BANK_NUMBER();
            pstUltraVividData->unUltraVividData.stUltraVividDMData.pucTable = tCOLOR_ULTRAVIVID_SETTING_TABLE_DM;
        }
        else
        {
            pstUltraVividData->enumUltraVividMode = _ULTRAVIVID_OFF;
        }
        return;
    }
#endif
#endif
#if(_HDR10_SUPPORT == _ON)
    if((UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) != _HDR10_OFF) &&
       (GET_OSD_REGION_HDR_SHARPNESS(UserAdjustGetOSDSelectRegion(enumSelRegion)) == _HDR10_SHARPNESSENHANCE_ON))
    {
        pstUltraVividData->enumUltraVividMode = _ULTRAVIVID_HDR10;
        pstUltraVividData->unUltraVividData.stUltraVividHDR10Data.ucBank = GET_CURRENT_BANK_NUMBER();
        pstUltraVividData->unUltraVividData.stUltraVividHDR10Data.pucTable = tCOLOR_ULTRAVIVID_SETTING_HDR;
    }
    else
#endif
    {
        BYTE ucUltraVividStatus = GET_OSD_ULTRA_VIVID_STATUS(UserAdjustGetOSDSelectRegion(enumSelRegion));

        if(ucUltraVividStatus != _ULTRA_VIVID_OFF)
        {
            pstUltraVividData->enumUltraVividMode = _ULTRAVIVID_SDR;
            pstUltraVividData->unUltraVividData.stUltraVividSDRData.ucBank = GET_CURRENT_BANK_NUMBER();
            pstUltraVividData->unUltraVividData.stUltraVividSDRData.pucTable = tCOLOR_ULTRAVIVID_SETTING_TABLE[ucUltraVividStatus - 1];
        }
        else
        {
            pstUltraVividData->enumUltraVividMode = _ULTRAVIVID_OFF;
        }
    }
}
#endif

#if(_COLOR_IP_DCR == _ON)
//--------------------------------------------------
// Description  : User function Get Data for DCR
// Input Value  : DCR Setting Struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetDCRData(StructDCRSetting *pstDCRData)
{
    pstDCRData->enumDCRMode = _DCR_USER;
    pstDCRData->unDCRData.stDCRUserData.enumDCRUserMeasureRegion = _FULL_REGION;
    pstDCRData->unDCRData.stDCRUserData.enumDCRMeasureSel = _MEASURE_AVERAGE;
    pstDCRData->unDCRData.stDCRUserData.usThreshold1 = _DCR_THESHOLD1;
    pstDCRData->unDCRData.stDCRUserData.usThreshold2 = _DCR_THESHOLD2;
}
#endif

#if(_COLOR_IP_ICM == _ON)
//--------------------------------------------------
// Description  : User function Adjust for ICM
// Input Value  : Select region, ICM setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetICMData(EnumSelRegion enumSelRegion, StructICMSetting *pstICMData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
    BYTE ucOsdSelRegionColorEfct = GET_OSD_COLOR_EFFECT(ucOSDSelectRegion);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstICMData->enumICMMode = _ICM_OFF;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
        if(GET_OSD_HDR_COLOR_ENHANCE(ucOSDSelectRegion) != _HDR10_COLORENHANCE_OFF)
        {
            pstICMData->enumICMMode = _ICM_HDR10_COLORENHANCE;
            pstICMData->unICMData.stICMHDR10ColorEnhanceData.ucBank = GET_CURRENT_BANK_NUMBER();

            switch(GET_OSD_HDR_COLOR_ENHANCE(ucOSDSelectRegion))
            {
                case _HDR10_COLORENHANCE_TYPE_1:
                    pstICMData->unICMData.stICMHDR10ColorEnhanceData.pucTable = tICM_COLORENHANCE_TABLE[0];
                    break;

                case _HDR10_COLORENHANCE_TYPE_2:
                    pstICMData->unICMData.stICMHDR10ColorEnhanceData.pucTable = tICM_COLORENHANCE_TABLE[1];
                    break;

                case _HDR10_COLORENHANCE_TYPE_3:
                    pstICMData->unICMData.stICMHDR10ColorEnhanceData.pucTable = tICM_COLORENHANCE_TABLE[2];
                    break;

                default:
                    pstICMData->unICMData.stICMHDR10ColorEnhanceData.pucTable = tICM_COLORENHANCE_TABLE[0];
                    break;
            }

            return;
        }
        else
#endif
        {
#if(_LOCAL_CONTRAST_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
            if(UserCommonColorGetLocalContrastEnableStatus(enumSelRegion) == _TRUE)
            {
                pstICMData->enumICMMode = _ICM_HDR10_USER;
                pstICMData->unICMData.stICMHDR10UserData.ucBank = GET_CURRENT_BANK_NUMBER();
                pstICMData->unICMData.stICMHDR10UserData.pucTable = tICM_LC_HDR10_TABLE;
                return;
            }
#endif
#endif
        }
    }

    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) != _HDR10_OFF)
    {
#if(_ICM_FUNCTION == _ON)
        if((ucOsdSelRegionColorEfct >= _COLOREFFECT_GAME) && (ucOsdSelRegionColorEfct < _COLOREFFECT_USER))
        {
            pstICMData->enumICMMode = _ICM_HDR10_USER;
            pstICMData->unICMData.stICMHDR10UserData.ucBank = GET_CURRENT_BANK_NUMBER();
            pstICMData->unICMData.stICMHDR10UserData.pucTable = tICM_HDR10_TABLE[ucOsdSelRegionColorEfct];
            return;
        }
#endif

        pstICMData->enumICMMode = _ICM_OFF;
        return;
    }
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
    if((UserCommonColorNightSniperCheckStatus(enumSelRegion) == _TRUE) && (GET_OSD_NIGHT_SNIPER(ucOSDSelectRegion) != _OFF))
    {
        pstICMData->enumICMMode = _ICM_NIGHT_SNIPER;
        pstICMData->unICMData.stICMNightSniperData.ucICMNightSniperSat = GET_OSD_NIGHT_SNIPER_SAT(ucOSDSelectRegion);
        pstICMData->unICMData.stICMNightSniperData.ucICMNightSniperLightness = GET_OSD_NIGHT_SNIPER_LIGHT(ucOSDSelectRegion);
        pstICMData->unICMData.stICMNightSniperData.ucICMNightSniperDarkOffset = _ICM_NIGHT_SNIPER_DARKNESS_OFFSET;
        return;
    }
#endif
#endif

#if(_ICM_CHAMELEON_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
    if(ucOsdSelRegionColorEfct == _COLOREFFECT_CHAMELEON)
    {
        BYTE ucIndex = 0;
        BYTE ucSatPosition = 0;
        BYTE ucLightPosition = 0;
        WORD usHuePosition = 0;
        WORD usHueByAxis = 0;

        usHuePosition = GET_OSD_CHAMELEON_HUE(ucOSDSelectRegion);
        ucSatPosition = GET_OSD_CHAMELEON_SAT(ucOSDSelectRegion);
        ucLightPosition = GET_OSD_CHAMELEON_LIGHTNESS(ucOSDSelectRegion);

        for(ucIndex = 0; ucIndex < 6; ucIndex++)
        {
            // Every axis hue = 0 start with its color. Change every axis to the same Color, need to calculate equivalent deltaHue
            // ex. when Raxis hue change to usHuePosition; Because Yaxis hue delay (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * 1) = 250 from Raxis
            // Yaxis deltaHue = (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * 1) + usHuePosition
            usHueByAxis = (_CHAMELEON_HUE_MAX - (_CHAMELEON_HUE_MAX / 6) * (WORD)ucIndex) + usHuePosition;

            if(usHueByAxis > _CHAMELEON_HUE_MAX)
            {
                usHueByAxis = usHueByAxis - _CHAMELEON_HUE_MAX;
            }


            pstICMData->unICMData.stICMChameleonData.pstAxisData[ucIndex].usICMChameleonHue = usHueByAxis;
            pstICMData->unICMData.stICMChameleonData.pstAxisData[ucIndex].ucICMChameleonSat = ucSatPosition;
            pstICMData->unICMData.stICMChameleonData.pstAxisData[ucIndex].ucICMChameleonLightness = ucLightPosition;
        }

        pstICMData->enumICMMode = _ICM_CHAMELEON;
        pstICMData->unICMData.stICMChameleonData.ucICMChameleonDarkOffset = _ICM_CHAMELEON_DARKNESS_OFFSET;
        return;
    }
#endif
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)

    if(UserCommonColorGetSDRPlusEnableStatus(enumSelRegion) == _TRUE)
    {
        pstICMData->enumICMMode = _ICM_USER;
        pstICMData->unICMData.stICMUserData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstICMData->unICMData.stICMUserData.pucTable = tICM_SDR_PLUS_TABLE;
        return;
    }
#endif
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
#if(_ICM_FUNCTION == _ON)
    if(UserCommonColorGetLocalContrastEnableStatus(enumSelRegion) == _TRUE)
    {
        pstICMData->enumICMMode = _ICM_USER;
        pstICMData->unICMData.stICMUserData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstICMData->unICMData.stICMUserData.pucTable = tICM_LC_TABLE;
        return;
    }
#endif
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) == _ON)
    {
        pstICMData->enumICMMode = _ICM_SDR2HDR;
        pstICMData->unICMData.stICMSDRtoHDRData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstICMData->unICMData.stICMSDRtoHDRData.pucTable = tSDRTOHDR_ICM;
        return;
    }
#endif

#if(_ICM_FUNCTION == _ON)
    if((ucOsdSelRegionColorEfct >= _COLOREFFECT_GAME) &&
       (ucOsdSelRegionColorEfct < _COLOREFFECT_USER))
    {
#if(_SCM_SUPPORT == _ON)
        pstICMData->enumICMMode = _ICM_SCM;
        pstICMData->unICMData.stICMSCMData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstICMData->unICMData.stICMSCMData.pucSCMTable = tSCM_TABLE[ucOsdSelRegionColorEfct];
        pstICMData->unICMData.stICMSCMData.pucICMTable = tICM_TABLE[ucOsdSelRegionColorEfct];
#else
        pstICMData->enumICMMode = _ICM_USER;
        pstICMData->unICMData.stICMUserData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstICMData->unICMData.stICMUserData.pucTable = tICM_TABLE[ucOsdSelRegionColorEfct];
#endif
        return;
    }
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
    if(ucOsdSelRegionColorEfct == _COLOREFFECT_USER)
    {
        BYTE ucIndex = 0;
        pstICMData->enumICMMode = _ICM_SIXCOLOR;

        for(ucIndex = 0; ucIndex < 6; ucIndex++)
        {
            OsdDisplaySixColorGetOneColorData(enumSelRegion, ucIndex, pstICMData);
        }
        return;
    }
#endif

    pstICMData->enumICMMode = _ICM_OFF;
}
#endif

#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
//--------------------------------------------------
// Description  : User function Get histogram Data for DCC
// Input Value  : DCC Setting Struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetDCCHistogramData(StructDCCHistogramSetting *pstDCCHistogramData)
{
    pstDCCHistogramData->enumDCCHistogramMode = _DCC_HISTOGRAM_USER;

#if((_DCC_HISTOGRM_INFO_FUNCTION == _ON) || (_DCC_FUNCTION == _ON))
    pstDCCHistogramData->unDCCHistogramData.stDCCHistogramUserData.enumDCCMeasureRegion = _FULL_REGION;
#else
    pstDCCHistogramData->unDCCHistogramData.stDCCHistogramUserData.enumDCCMeasureRegion = _NON_REGION;
#endif
}
#endif

#if(_COLOR_IP_DCC == _ON)
//--------------------------------------------------
// Description  : User function Get Data for DCC
// Input Value  : Select Region ; DCC Setting Struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetDCCData(EnumSelRegion enumSelRegion, StructDCCSetting *pstDCCData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
    BYTE ucOsdSelRegionColorEfct = GET_OSD_COLOR_EFFECT(ucOSDSelectRegion);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstDCCData->enumDCCMode = _DCC_OFF;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
        if(GET_OSD_HDR_LIGHT_ENHANCE(ucOSDSelectRegion) != _HDR10_LIGHTENHANCE_OFF)
        {
            pstDCCData->enumDCCMode = _DCC_HDR10_LIGHTENHANCE;
            pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.ucBank = GET_CURRENT_BANK_NUMBER();

            switch(GET_OSD_HDR_LIGHT_ENHANCE(ucOSDSelectRegion))
            {
                case _HDR10_LIGHTENHANCE_TYPE_120:
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_540NIT = tDCC_LIGHTENHANCE_120_540_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_1200NIT = tDCC_LIGHTENHANCE_120_1200_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_4000NIT = tDCC_LIGHTENHANCE_120_4000_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_10000NIT = tDCC_LIGHTENHANCE_120_10000_TABLE;
                    break;

                case _HDR10_LIGHTENHANCE_TYPE_140:
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_540NIT = tDCC_LIGHTENHANCE_140_540_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_1200NIT = tDCC_LIGHTENHANCE_140_1200_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_4000NIT = tDCC_LIGHTENHANCE_140_4000_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_10000NIT = tDCC_LIGHTENHANCE_140_10000_TABLE;
                    break;

                case _HDR10_LIGHTENHANCE_TYPE_160:
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_540NIT = tDCC_LIGHTENHANCE_160_540_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_1200NIT = tDCC_LIGHTENHANCE_160_1200_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_4000NIT = tDCC_LIGHTENHANCE_160_4000_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_10000NIT = tDCC_LIGHTENHANCE_160_10000_TABLE;
                    break;

                default:
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_540NIT = tDCC_LIGHTENHANCE_120_540_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_1200NIT = tDCC_LIGHTENHANCE_120_1200_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_4000NIT = tDCC_LIGHTENHANCE_120_4000_TABLE;
                    pstDCCData->unDCCData.stDCCHDR10LightEnhanceData.stDCCHDR10LightEnhanceTableArray.pucLightEnhanceTable_10000NIT = tDCC_LIGHTENHANCE_120_10000_TABLE;
                    break;
            }

            return;
        }
#endif
    }

    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) != _HDR10_OFF)
    {
#if(_DCC_FUNCTION == _ON)
        if((ucOsdSelRegionColorEfct >= _COLOREFFECT_GAME) &&
           (ucOsdSelRegionColorEfct < _COLOREFFECT_USER))
        {
            pstDCCData->enumDCCMode = _DCC_HDR10_USER;
            pstDCCData->unDCCData.stDCCHDR10USERData.ucBank = GET_CURRENT_BANK_NUMBER();
            pstDCCData->unDCCData.stDCCHDR10USERData.pucTable = tDCC_HDR10_TABLE[ucOsdSelRegionColorEfct];
            return;
        }
#endif

        pstDCCData->enumDCCMode = _DCC_OFF;
        return;
    }
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) == _ON)
    {
        pstDCCData->enumDCCMode = _DCC_SDR2HDR;
        pstDCCData->unDCCData.stDCCSDRtoHDRData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstDCCData->unDCCData.stDCCSDRtoHDRData.pucTable = tSDRTOHDR_DCC;
        return;
    }
#endif

#if(_DCC_FUNCTION == _ON)
    if((ucOsdSelRegionColorEfct >= _COLOREFFECT_GAME) &&
       (ucOsdSelRegionColorEfct < _COLOREFFECT_USER))
    {
        pstDCCData->enumDCCMode = _DCC_USER;
        pstDCCData->unDCCData.stDCCUserData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstDCCData->unDCCData.stDCCUserData.pucTable = tDCC_TABLE[GET_OSD_COLOR_EFFECT(ucOSDSelectRegion)];
        pstDCCData->unDCCData.stDCCUserData.enumDCCAutoModeEnable = _DCC_AUTOMODE_OFF;
        return;
    }
#endif

    pstDCCData->enumDCCMode = _DCC_OFF;
}
#endif

#if(_COLOR_IP_IAPS == _ON)
//--------------------------------------------------
// Description  : User function Get Data for IAPS
// Input Value  : Select Region ; IAPS Setting Struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetIAPSData(EnumSelRegion enumSelRegion, StructIAPSSetting *pstIAPSData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstIAPSData->enumIAPSMode = _IAPS_OFF;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
        if(GET_OSD_HDR_LIGHT_ENHANCE(ucOSDSelectRegion) != _HDR10_LIGHTENHANCE_OFF)
        {
            pstIAPSData->enumIAPSMode = _IAPS_HDR10_LIGHTENHANCE;
            return;
        }
#endif
    }
#endif

    pstIAPSData->enumIAPSMode = _IAPS_OFF;
}
#endif

#if(_COLOR_IP_CONTRAST == _ON)
//--------------------------------------------------
// Description  : User function Get Data for Contrast
// Input Value  : Select Region ; Contrast Setting Struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetContrastData(EnumSelRegion enumSelRegion, StructCtsSetting *pstCtsData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

#if(_ULTRA_HDR_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstCtsData->enumCtsMode = _CONTRAST_OFF;
        return;
    }
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        pstCtsData->enumCtsMode = _CONTRAST_OFF;
        return;
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) != _HDR10_OFF)
    {
        pstCtsData->unCtsData.stCtsHDR10Data.pusData[0] = MINOF(4095U, (WORD)((DWORD)0x800 * (GET_OSD_REGION_HDR_CONTRAST(ucOSDSelectRegion) + 200) / 200));
        pstCtsData->unCtsData.stCtsHDR10Data.pusData[1] = pstCtsData->unCtsData.stCtsHDR10Data.pusData[0];
        pstCtsData->unCtsData.stCtsHDR10Data.pusData[2] = pstCtsData->unCtsData.stCtsHDR10Data.pusData[0];
        pstCtsData->enumCtsMode = _CONTRAST_HDR10_USER;
    }
    else
#endif
    {
#if(_SDR_TO_HDR_FUNCTION == _ON)
        if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) != _OFF)
        {
            pstCtsData->enumCtsMode = _CONTRAST_OFF;
            return;
        }
#endif

#if(_PCM_FUNCTION == _ON)
        if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
        {
            pstCtsData->enumCtsMode = _CONTRAST_OFF;
            return;
        }
#endif
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
        if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
        {
            pstCtsData->enumCtsMode = _CONTRAST_OFF;
            return;
        }
#endif
        pstCtsData->unCtsData.stCtsUserData.pusData[0] = MINOF(4095U, (WORD)((DWORD)g_stColorProcData.usColorTempR * GET_OSD_CONTRAST(ucOSDSelectRegion) / 2048));
        pstCtsData->unCtsData.stCtsUserData.pusData[1] = MINOF(4095U, (WORD)((DWORD)g_stColorProcData.usColorTempG * GET_OSD_CONTRAST(ucOSDSelectRegion) / 2048));
        pstCtsData->unCtsData.stCtsUserData.pusData[2] = MINOF(4095U, (WORD)((DWORD)g_stColorProcData.usColorTempB * GET_OSD_CONTRAST(ucOSDSelectRegion) / 2048));
        pstCtsData->enumCtsMode = _CONTRAST_USER;
    }
}
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
//--------------------------------------------------
// Description  : User function Get Data for Contrast
// Input Value  : Select Region ; Contrast Setting Struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetBrightnessData(EnumSelRegion enumSelRegion, StructBriSetting *pstBriData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

#if(_ULTRA_HDR_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstBriData->enumBriMode = _BRIGHTNESS_OFF;
        return;
    }
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        pstBriData->enumBriMode = _BRIGHTNESS_OFF;
        return;
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) != _HDR10_OFF)
    {
        pstBriData->enumBriMode = _BRIGHTNESS_OFF;
    }
    else
#endif
    {
        WORD usBrightnessData = GET_OSD_BRIGHTNESS(ucOSDSelectRegion);

#if(_SDR_TO_HDR_FUNCTION == _ON)
        if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) != _OFF)
        {
            pstBriData->enumBriMode = _BRIGHTNESS_OFF;
            return;
        }
#endif

#if(_PCM_FUNCTION == _ON)
        if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
        {
            pstBriData->enumBriMode = _BRIGHTNESS_OFF;
            return;
        }
#endif

        pstBriData->unBriData.stBriUserData.pusData[0] = usBrightnessData;
        pstBriData->unBriData.stBriUserData.pusData[1] = usBrightnessData;
        pstBriData->unBriData.stBriUserData.pusData[2] = usBrightnessData;

        pstBriData->enumBriMode = _BRIGHTNESS_USER;
    }
}
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Input Gamma
// Input Value  : Select Region, Input Gamma setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetInGammaData(EnumSelRegion enumSelRegion, StructInGammaSetting *pstIgData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstIgData->unInGammaData.stInGammaDMData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstIgData->unInGammaData.stInGammaDMData.pucTable = tDM_INPUTGAMMA;
        pstIgData->enumInGammaMode = _INGAMMA_DM;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
#if(_HDMI_SBTM_SUPPORT == _ON)
        if(UserCommonColorHDR10GetSBTMMode(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_SBTM_MODE_D_RDM)
        {
            pstIgData->enumInGammaMode = _INGAMMA_HDR10_USER;
            pstIgData->unInGammaData.stInGammaHDR10UserData.ucBank = GET_CURRENT_BANK_NUMBER();
            pstIgData->unInGammaData.stInGammaHDR10UserData.pucTable = tHDR10_SBTM_TABLE;
            return;
        }
#endif
        if(UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(UserCommonColorHDRGetDisplayRegion(enumSelRegion))) == _HDR10_MODE_FORCE_2084)
        {
            pstIgData->enumInGammaMode = _INGAMMA_HDR10_FORCE_2084;
            pstIgData->unInGammaData.stInGammaHDR10Force2084Data.enumHDR10DarkEnhanceStatus = GET_OSD_REGION_DARK_ENHANCE(ucOSDSelectRegion);
#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
            pstIgData->unInGammaData.stInGammaHDR10Force2084Data.enumHDR10FixedPointToneMappingStatus = _HDR10_FIXED_POINT_TM_OFF;
#endif
            return;
        }
        else
        {
#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
            pstIgData->enumInGammaMode = _INGAMMA_HDR10_USER;
            pstIgData->unInGammaData.stInGammaHDR10UserData.ucBank = UserAdjustGetHDRUserTableBank(UserCommonColorHDRGetDisplayRegion(enumSelRegion));
            pstIgData->unInGammaData.stInGammaHDR10UserData.pucTable = UserAdjustGetHDRUserTableAddress(UserCommonColorHDRGetDisplayRegion(enumSelRegion), GET_OSD_REGION_DARK_ENHANCE(ucOSDSelectRegion));
            return;
#else
            pstIgData->enumInGammaMode = _INGAMMA_HDR10_AUTO;
            pstIgData->unInGammaData.stInGammaHDR10AutoData.enumHDR10DarkEnhanceStatus = GET_OSD_REGION_DARK_ENHANCE(ucOSDSelectRegion);
#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
            pstIgData->unInGammaData.stInGammaHDR10AutoData.enumHDR10FixedPointToneMappingStatus = _HDR10_FIXED_POINT_TM_OFF;
#endif
            return;
#endif
        }
    }
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) != _OFF)
    {
        pstIgData->unInGammaData.stInGammaSDRtoHDRData.ucBank = GET_CURRENT_BANK_NUMBER();
        pstIgData->unInGammaData.stInGammaSDRtoHDRData.pucTable = tSDRTOHDR_INPUTGAMMA;
        pstIgData->enumInGammaMode = _INGAMMA_SDRTOHDR;
        return;
    }
#endif

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) == _PCM_OSD_USER)
    {
        pstIgData->enumInGammaMode = _INGAMMA_PCM_USER;
        pstIgData->unInGammaData.stInGammaPCMUserData.ucBank = UserAdjustGetPCMUserModeTableBank();
        pstIgData->unInGammaData.stInGammaPCMUserData.pucTable = UserAdjustGetPCMUserModeTableAddress(0);
#if(_INPUT_GAMMA_NODE_1025_SUPPORT == _ON)
        pstIgData->unInGammaData.stInGammaPCMUserData.enumPCMNodeType = _PCM_NODE_129;
#endif
        return;
    }
#endif
#if(_OCC_FUNCTION == _ON)
    else if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        pstIgData->enumInGammaMode = _INGAMMA_PCM;
        pstIgData->unInGammaData.stInGammaPCMData.enumPCMMode = UserAdjustPCMOSDMapping(GET_OSD_PCM_STATUS(ucOSDSelectRegion));
        return;
    }
#endif

#if(_OGC_FUNCTION == _ON)
    if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
    {
        pstIgData->unInGammaData.stInGammaOGCData.enumOGCType = UserAdjustOGCOSDMapping(GET_OSD_GAMMA(ucOSDSelectRegion));
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
        {
            pstIgData->enumInGammaMode = _INGAMMA_OGC;
            return;
        }
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorGlobalDimmingGetEnableStatus() == _GLOBAL_DIMMING_ENABLE)
        {
            pstIgData->enumInGammaMode = _INGAMMA_OGC;
            return;
        }
#endif
    }
#endif
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
    if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
    {
        pstIgData->unInGammaData.stInGammaOCCPCMGammaData.enumOCCPCMGammaType = UserAdjustOCCPCMGammaOSDMapping(GET_OSD_GAMMA(ucOSDSelectRegion));
        pstIgData->enumInGammaMode = _INGAMMA_OCC_PCM_GAMMA;
        return;
    }
#endif
    pstIgData->enumInGammaMode = _INGAMMA_OFF;
}
#endif

#if(_COLOR_IP_YMAPPING == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Ymapping
// Input Value  : Select Region, Ymapping setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetYmappingData(EnumSelRegion enumSelRegion, StructYmappingSetting *pstIYmData)
{
#if(_HLG_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HLG_ON)
    {
        pstIYmData->enumYmappingMode = _YMAPPING_HLG;
        pstIYmData->unYmappingData.stYmappingHLGData.enumHLGOOTFType = _HLG_OOTF_STANDARD_MODE;
        return;
    }
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
    if(UserCommonColorHDRGetBackLightAdaptiveTMStatus(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _BACKLIGHT_ADAPTIVE_TM_ON)
    {
        pstIYmData->enumYmappingMode = _YMAPPING_HDR10_BACKLIGHT_ADAPTIVE_TM;
        pstIYmData->unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.usBackLight = GET_OSD_BACKLIGHT();
        pstIYmData->unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.usBackLightMax = _BACKLIGHT_MAX;

        if(UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(UserCommonColorHDRGetDisplayRegion(enumSelRegion))) == _HDR10_MODE_FORCE_2084)
        {
            pstIYmData->unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.enumHDR10ColorMatrix = _HDR10_COLOR_MATRIX_BT2020;
            pstIYmData->unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.enumHDR10DarkEnhanceStatus = GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetOSDSelectRegion(enumSelRegion));
        }
        else
        {
            pstIYmData->unYmappingData.stYmappingHDR10BackLightAdaptiveTMData.enumHDR10DarkEnhanceStatus = GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetOSDSelectRegion(enumSelRegion));
        }
        return;
    }
#endif

    enumSelRegion = enumSelRegion;
    pstIYmData->enumYmappingMode = _YMAPPING_OFF;
}
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Post Gamma
// Input Value  : Select Region, Post Gamma setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetPostGammaData(EnumSelRegion enumSelRegion, StructPostGammaSetting *pstPgData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(enumSelRegion) != _OFF)
    {
        pstPgData->enumPostGammaMode = _POSTGAMMA_OFF;
        return;
    }
#endif

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) == _PCM_OSD_USER)
    {
        pstPgData->enumPostGammaMode = _POSTGAMMA_PCM_USER;
        pstPgData->unPostGammaData.stPostGammaPCMUserData.ucBank = UserAdjustGetPCMUserModeTableBank();
        pstPgData->unPostGammaData.stPostGammaPCMUserData.pucTable = UserAdjustGetPCMUserModeTableAddress(1);
        return;
    }
#if(_OCC_FUNCTION == _ON)
    else if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        pstPgData->enumPostGammaMode = _POSTGAMMA_OFF;
        return;
    }
#endif
#endif

#if(_GAMMA_FUNCTION == _ON)
    if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
    {
#if(_OGC_FUNCTION == _ON)
        pstPgData->enumPostGammaMode = _POSTGAMMA_OGC;
        pstPgData->unPostGammaData.stPostGammaOGCData.enumOGCType = UserAdjustOGCOSDMapping(GET_OSD_GAMMA(ucOSDSelectRegion));
        if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_18)
        {
            pstPgData->unPostGammaData.stPostGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA1_TYPE;
        }
        else if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_20)
        {
            pstPgData->unPostGammaData.stPostGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA2_TYPE;
        }
        else if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_22)
        {
            pstPgData->unPostGammaData.stPostGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA3_TYPE;
        }
        else if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_24)
        {
            pstPgData->unPostGammaData.stPostGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA4_TYPE;
        }
#else
        pstPgData->enumPostGammaMode = _POSTGAMMA_USER;
        pstPgData->unPostGammaData.stPostGammaUserData.ucBank = UserAdjustGetGammaTableBank();
        pstPgData->unPostGammaData.stPostGammaUserData.pucTable = UserAdjustGetGammaTableAddress(GET_OSD_GAMMA(ucOSDSelectRegion) - 1);
#endif
        return;
    }
#endif
    pstPgData->enumPostGammaMode = _POSTGAMMA_OFF;
}
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Output Gamma
// Input Value  : Select Region, Output Gamma setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetOutGammaData(EnumSelRegion enumSelRegion, StructOutGammaSetting *pstOgData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstOgData->enumOutGammaMode = _OUTGAMMA_DM;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
        pstOgData->enumOutGammaMode = _OUTGAMMA_HDR10_USER;
        pstOgData->unOutGammaData.stOutGammaHDR10UserData.ucBank = _OGC_FLASH_BANK;
        pstOgData->unOutGammaData.stOutGammaHDR10UserData.pucTable = UserCommonColorGetOCCGamma1Addr(_GAMMA1_OCC_NORMAL);
        return;
    }
#endif
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) != _OFF)
    {
        pstOgData->enumOutGammaMode = _OUTGAMMA_SDRTOHDR;
#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
        pstOgData->unOutGammaData.stOutGammaSDRtoHDRData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif
        return;
    }
#endif

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) == _PCM_OSD_USER)
    {
        pstOgData->enumOutGammaMode = _OUTGAMMA_PCM_USER;
        pstOgData->unOutGammaData.stOutGammaPCMUserData.ucBank = UserAdjustGetPCMUserModeTableBank();
        pstOgData->unOutGammaData.stOutGammaPCMUserData.pucTable = UserAdjustGetPCMUserModeTableAddress(1);
        return;
    }
#endif
#if(_OCC_FUNCTION == _ON)
    else if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
#if(_RGB_3D_GAMMA_FUNCTION == _ON)
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
        if(UserCommonColor3DGammaCubeGetEnableStatus(enumSelRegion) == _FUNCTION_ON)
        {
            pstOgData->enumOutGammaMode = _OUTGAMMA_CUBE_MAPPING;
            pstOgData->unOutGammaData.stOutGammaCubeMappingData.enumTypeSelect = UserAdjustGet3DGammaType(enumSelRegion);
            return;
        }
#endif
#endif
        pstOgData->enumOutGammaMode = _OUTGAMMA_PCM;
        pstOgData->unOutGammaData.stOutGammaPCMData.enumPCMMode = UserAdjustPCMOSDMapping(GET_OSD_PCM_STATUS(ucOSDSelectRegion));
#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
        pstOgData->unOutGammaData.stOutGammaPCMData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif
        return;
    }
#endif

#if(_GAMMA_FUNCTION == _ON)

    if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
    {
#if(_OGC_FUNCTION == _ON)
        pstOgData->enumOutGammaMode = _OUTGAMMA_OGC;
        pstOgData->unOutGammaData.stOutGammaOGCData.enumOGCType = UserAdjustOGCOSDMapping(GET_OSD_GAMMA(ucOSDSelectRegion));
        if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_18)
        {
            pstOgData->unOutGammaData.stOutGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA1_TYPE;
        }
        else if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_20)
        {
            pstOgData->unOutGammaData.stOutGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA2_TYPE;
        }
        else if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_22)
        {
            pstOgData->unOutGammaData.stOutGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA3_TYPE;
        }
        else if(GET_OSD_GAMMA(ucOSDSelectRegion) == _GAMMA_24)
        {
            pstOgData->unOutGammaData.stOutGammaOGCData.enumOGCTypeSelect = _OGC_GAMMA4_TYPE;
        }
#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
        pstOgData->unOutGammaData.stOutGammaOGCData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif

#elif(_OCC_PCM_GAMMA_SUPPORT == _ON)
        pstOgData->enumOutGammaMode = _OUTGAMMA_OCC_PCM_GAMMA;
#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
        pstOgData->unOutGammaData.stOutGammaOCCPCMGammaData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif
#else
        pstOgData->enumOutGammaMode = _OUTGAMMA_USER;
        pstOgData->unOutGammaData.stOutGammaUserData.ucBank = UserAdjustGetGammaTableBank();
        pstOgData->unOutGammaData.stOutGammaUserData.pucTable = UserAdjustGetGammaTableAddress(GET_OSD_GAMMA(ucOSDSelectRegion) - 1);
#endif

        return;
    }

#endif

    pstOgData->enumOutGammaMode = _OUTGAMMA_OFF;
}
#endif

#if(_COLOR_IP_SRGB == _ON)
//--------------------------------------------------
// Description  : User function Adjust for sRGB
// Input Value  : Select Region, sRGB setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetsRGBData(EnumSelRegion enumSelRegion, StructSRGBSetting *pstsRGBData)
{
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstsRGBData->unSRGBData.stSRGBDMData.enumDMColorMatrix = _DM_COLOR_MATRIX_DCIP3_D65;
        pstsRGBData->enumSRGBMode = _SRGB_DM;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
    {
        EnumHDR10Status enumHDR10Status = UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion));
        EnumHDR10ModeDef enumHDR10ModeDef = UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(UserCommonColorHDRGetDisplayRegion(enumSelRegion)));

        if(enumHDR10Status == _HDR10_ON)
        {
#if(_HDMI_SBTM_SUPPORT == _ON)
            if(UserCommonColorHDRGetSBTMStatus(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_SBTM_ON)
            {
                pstsRGBData->enumSRGBMode = _SRGB_HDR10_SBTM;
                pstsRGBData->unSRGBData.stSRGBHDR10SBTMData.enumHDR10SBTMColorMatrix = _HDR10_SBTM_COLOR_MATRIX_BT2020;
                return;
            }
#endif
            if(enumHDR10ModeDef == _HDR10_MODE_FORCE_2084)
            {
                pstsRGBData->enumSRGBMode = _SRGB_HDR10_FORCE_2084;
                pstsRGBData->unSRGBData.stSRGBHDR10Force2084Data.enumHDR10ColorMatrix = _HDR10_COLOR_MATRIX_BT2020;
                return;
            }
            else
            {
                pstsRGBData->enumSRGBMode = _SRGB_HDR10_AUTO;
                return;
            }
        }

#if(_HLG_SUPPORT == _ON)
        if(enumHDR10Status == _HLG_ON)
        {
            if(enumHDR10ModeDef == _HDR10_HLG_MODE_FORCE_HLG)
            {
                pstsRGBData->enumSRGBMode = _SRGB_HLG_FORCE;
                pstsRGBData->unSRGBData.stSRGBHLGForceData.enumHLGColorMatrix = _HDR10_COLOR_MATRIX_BT2020;
                return;
            }
            else
            {
                pstsRGBData->enumSRGBMode = _SRGB_HLG_AUTO;
                return;
            }
        }
#endif
    }
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
    if(GET_OSD_SDR_TO_HDR(ucOSDSelectRegion) != _OFF)
    {
        pstsRGBData->enumSRGBMode = _SRGB_SDRTOHDR;
        return;
    }
#endif

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) == _PCM_OSD_USER)
    {
        pstsRGBData->enumSRGBMode = _SRGB_PCM_USER;
        pstsRGBData->unSRGBData.stSRGBPCMUserData.ucBank = UserAdjustGetPCMUserModeTableBank();
        pstsRGBData->unSRGBData.stSRGBPCMUserData.pucTable = UserAdjustGetPCMUserModeTableAddress(2);
        pstsRGBData->unSRGBData.stSRGBPCMUserData.enumSrgbPrecision = _SRGB_1_BIT_SHIFT_LEFT;
        return;
    }
#endif
#if(_OCC_FUNCTION == _ON)
    else if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        EnumPCMType enumPCMType = UserAdjustPCMOSDMapping(GET_OSD_PCM_STATUS(ucOSDSelectRegion));
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
        if((GET_COLOR_TEMP_TYPE(ucOSDSelectRegion) != _CT_USER) &&
           ((enumPCMType == _PCM_SRGB) ||
            (enumPCMType == _PCM_DCI_P3)))
        {
            pstsRGBData->enumSRGBMode = _SRGB_PCM_USER_CCT;
            // user define osd CCT mapping function.
            pstsRGBData->unSRGBData.stSRGBColorTransferUserData.enumPCMMode = enumPCMType;
            UserAdjustGetColorTransferUserModeTableAddress(pstsRGBData->unSRGBData.stSRGBColorTransferUserData.enumPCMMode,
                                                           GET_COLOR_TEMP_TYPE(ucOSDSelectRegion),
                                                           pstsRGBData->unSRGBData.stSRGBColorTransferUserData.pusTable);

#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
            pstsRGBData->unSRGBData.stSRGBColorTransferUserData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif
        }
        else
#endif
        {
            pstsRGBData->enumSRGBMode = _SRGB_PCM;
            pstsRGBData->unSRGBData.stSRGBPCMData.enumPCMMode = enumPCMType;
#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
            pstsRGBData->unSRGBData.stSRGBPCMData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif
        }
        return;
    }
#endif

#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
    if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
    {
        pstsRGBData->unSRGBData.stSRGBOCCPCMGammaData.enumOCCPCMGammaCTMatrix = UserAdjustOCCPCMGammaCTOSDMapping(GET_COLOR_TEMP_TYPE(ucOSDSelectRegion));
        if(pstsRGBData->unSRGBData.stSRGBOCCPCMGammaData.enumOCCPCMGammaCTMatrix != _OCC_PCM_GAMMA_CT_OFF)
        {
            pstsRGBData->enumSRGBMode = _SRGB_OCC_PCM_GAMMA;
        }
        else
        {
            pstsRGBData->enumSRGBMode = _SRGB_OFF;
        }
#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) || (_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC))
        pstsRGBData->unSRGBData.stSRGBOCCPCMGammaData.enumOGCModeSelect = _OGC_NORMAL_TYPE;
#endif
        return;
    }
#endif

#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)

    pstsRGBData->enumSRGBMode = _SRGB_HUESAT;
    pstsRGBData->unSRGBData.stSRGBHueSatData.shHue = _DEFAULT_HUE - GET_OSD_HUE(ucOSDSelectRegion);
    pstsRGBData->unSRGBData.stSRGBHueSatData.usSat = GET_OSD_SATURATION(ucOSDSelectRegion);

#else

    pstsRGBData->enumSRGBMode = _SRGB_OFF;

#endif
}
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
//--------------------------------------------------
// Description  : User function Adjust for 3D Gamma
// Input Value  : Select Region, 3D Gamma setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGet3DGammaData(EnumSelRegion enumSelRegion, Struct3DGammaSetting *pst3DGammaData)
{
    enumSelRegion = enumSelRegion;

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pst3DGammaData->enum3DGammaMode = _3DGAMMA_OFF;
        return;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
        pst3DGammaData->enum3DGammaMode = _3DGAMMA_GAMUT_COMPRESSION;
        pst3DGammaData->unOutGammaData.st3DGammaGamutCompressionData.ucBank = UserAdjustGet3DGammaGamutCMPTableBank();
        pst3DGammaData->unOutGammaData.st3DGammaGamutCompressionData.pucTable = UserAdjustGet3DGammaGamutCMPTableAddress();
        return;
    }
#endif

#if(_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
        pst3DGammaData->enum3DGammaMode = _3DGAMMA_HDR10_REMAP;
        pst3DGammaData->unOutGammaData.st3DGammaHDR10RemapData.ucBank = UserAdjustGet3DGammaHDR10RemapTableBank();
        pst3DGammaData->unOutGammaData.st3DGammaHDR10RemapData.pucTable = UserAdjustGet3DGammaHDR10RemapTableAddress(0);
#if(_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
        pst3DGammaData->unOutGammaData.st3DGammaHDR10RemapData.ucBank = UserCommonColorGetOCC3DGammaTableBank(_OCC_RGB_3D_GAMMA_TYPE1);
        pst3DGammaData->unOutGammaData.st3DGammaHDR10RemapData.pucTable = UserCommonColorGetOCC3DGammaTableAddress(_OCC_RGB_3D_GAMMA_TYPE1);
#endif
        return;
    }
#endif
#endif


#if((_OCC_FUNCTION == _ON) && (_RGB_3D_GAMMA_FUNCTION == _ON))
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
    if(UserCommonColor3DGammaCubeGetEnableStatus(enumSelRegion) == _FUNCTION_ON)
    {
        pst3DGammaData->enum3DGammaMode = _3DGAMMA_CUBE_MAPPING;
        pst3DGammaData->unOutGammaData.st3DGammaCubeMappingData.enumTypeSelect = UserAdjustGet3DGammaType(enumSelRegion);
        return;
    }
#endif
    switch(GET_OSD_PCM_STATUS(UserAdjustGetOSDSelectRegion(enumSelRegion)))
    {
        case _PCM_OSD_SOFT_PROFT_M1:
        case _PCM_OSD_SOFT_PROFT_M2:
            pst3DGammaData->enum3DGammaMode = _3DGAMMA_USER;
            pst3DGammaData->unOutGammaData.st3DGammaUserData.ucBank = UserAdjustGet3DGammaTableBank();
            pst3DGammaData->unOutGammaData.st3DGammaUserData.pucTable = UserAdjustGet3DGammaTableAddress();
            return;

        default:
            break;
    }
#endif

    pst3DGammaData->enum3DGammaMode = _3DGAMMA_OFF;
}
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Uniformity
// Input Value  : EnumSelRegion, StructUniformitySetting
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetUniformityData(EnumSelRegion enumSelRegion, StructUniformitySetting *pstUniData)
{
    EnumUniformityTypeSelect enumUniformityType = _UNIFORMITY_TYPE1;
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    bit bUniformityOffsetEnable = _OFF;
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstUniData->enumUniformityMode = _UNIFORMITY_OFF;
        return;
    }
#endif
#endif

    if(GET_OSD_PANEL_UNIFORMITY(ucOSDSelectRegion) == _ON)
    {
#if(_OCC_FUNCTION == _ON)
        switch(GET_OSD_PCM_STATUS(ucOSDSelectRegion))
        {
            case _PCM_OSD_SRGB:
                enumUniformityType = _UNIFORMITY_TYPE5;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                bUniformityOffsetEnable = _UNIFORMITY_OFFSET_TYPE4;
#endif
                break;

            case _PCM_OSD_ADOBE_RGB:
                enumUniformityType = _UNIFORMITY_TYPE6;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                bUniformityOffsetEnable = _UNIFORMITY_OFFSET_TYPE5;
#endif
                break;

            default:
                break;
        }

        if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
        {
            pstUniData->enumUniformityMode = _UNIFORMITY_PCM;
            pstUniData->unUniformityData.stUniformityPCMData.enumUniformityType = enumUniformityType;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            pstUniData->unUniformityData.stUniformityPCMData.b1UniformityOffsetEnable = bUniformityOffsetEnable;
#endif
            return;
        }

#endif

#if(_OGC_FUNCTION == _ON)

        switch(UserAdjustOGCOSDMapping(GET_OSD_GAMMA(ucOSDSelectRegion)))
        {
            case _OGC_MODE1:
                enumUniformityType = _UNIFORMITY_TYPE1;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                bUniformityOffsetEnable = _UNIFORMITY_OFFSET_TYPE0;
#endif
                break;

            case _OGC_MODE2:
                enumUniformityType = _UNIFORMITY_TYPE2;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                bUniformityOffsetEnable = _UNIFORMITY_OFFSET_TYPE1;
#endif
                break;


            case _OGC_MODE3:
                enumUniformityType = _UNIFORMITY_TYPE3;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                bUniformityOffsetEnable = _UNIFORMITY_OFFSET_TYPE2;
#endif
                break;

            case _OGC_MODE4:
                enumUniformityType = _UNIFORMITY_TYPE4;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                bUniformityOffsetEnable = _UNIFORMITY_OFFSET_TYPE3;
#endif
                break;

            default:
                break;
        }

        if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
        {
            pstUniData->enumUniformityMode = _UNIFORMITY_OGC;
            pstUniData->unUniformityData.stUniformityOGCData.enumUniformityType = enumUniformityType;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            pstUniData->unUniformityData.stUniformityOGCData.b1UniformityOffsetEnable = bUniformityOffsetEnable;
#endif
            return;
        }
#endif
    }

    pstUniData->enumUniformityMode = _UNIFORMITY_OFF;
}
#if(_UNIFORMITY_CUSTOM_ENABLE_CONDITION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function Uniformity Multi P Enable. Only Multi P are the same color mode, Uniformity can enable.
// Input Value  : None
// Output Value : User Custom Uniformity Enable Condition
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceColorGetUniformityCustomEnableStatus(void)
{
    if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
    {
        if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()))
        {
            return _FUNCTION_ON;
        }
    }
    else
    {
        if(GET_EAGLE_SIGHT_STATUS() == _ON)
        {
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()))
            {
                return _FUNCTION_ON;
            }
        }
    }
    return _FUNCTION_OFF;
}
#endif
#endif

#if(_COLOR_IP_HL_WIN == _ON)
//--------------------------------------------------
// Description  : Get Demo Mode Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetHLWData(StructHLWSetting *pstHLWData)
{
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        pstHLWData->enumHLWMode = _HLW_KERNEL;
        pstHLWData->unHLWData.stHLWKernelData.enumHLWKernelRegion = GET_OSD_SYSTEM_SELECT_REGION();
        pstHLWData->unHLWData.stHLWKernelData.b1TopBorderEn = _OFF;
        pstHLWData->unHLWData.stHLWKernelData.b1BottomBorderEn = _OFF;
        pstHLWData->unHLWData.stHLWKernelData.b1LeftBorderEn = _OFF;
        pstHLWData->unHLWData.stHLWKernelData.b1RightBorderEn = _OFF;
        pstHLWData->unHLWData.stHLWKernelData.ucHLWRed = 255;
        pstHLWData->unHLWData.stHLWKernelData.ucHLWGreen = 0;
        pstHLWData->unHLWData.stHLWKernelData.ucHLWBlue = 0;
        pstHLWData->unHLWData.stHLWKernelData.ucBorderWidth = _HL_WIN_BORDER_SIZE;

#if((_EAGLE_SIGHT_SUPPORT == _ON) && (_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON))
        if((SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) && (GET_EAGLE_SIGHT_STATUS() == _ON) && (GET_EAGLE_SIGHT_CIRCLE_WIN_STATUS() == _ON))
        {
            StructColorCircleWindowSetting stCircleWindow = {0};

            // Get Circle blending Border Information
            UserInterfaceColorGetCircleWindowData(&stCircleWindow.stCircleWindowSetting);
            pstHLWData->unHLWData.stHLWKernelData.ucHLWRed = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowRed;
            pstHLWData->unHLWData.stHLWKernelData.ucHLWGreen = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowGreen;
            pstHLWData->unHLWData.stHLWKernelData.ucHLWBlue = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWinowBlue;
            pstHLWData->unHLWData.stHLWKernelData.ucBorderWidth = stCircleWindow.stCircleWindowSetting.unCircleWindowData.stCircleWindowData.ucBorderWidth;
        }
#endif

#if(_COLOR_DEMO_FUNCTION == _ON)
        // Reset to case:_HL_WIN_MOVE default position
        g_usColorHLWinHWidth = _PANEL_DH_WIDTH / 6;
        g_usColorHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;
        g_usColorHLWinHPos = (_PANEL_DH_WIDTH - _PANEL_DH_WIDTH / 6) / 2;
        g_usColorHLWinVPos = 0;
        g_bColorHLWinRLMove = _RIGHT;
#endif
    }
#if(_COLOR_DEMO_FUNCTION == _ON)
    else
    {
        pstHLWData->enumHLWMode = _HLW_USER;
        pstHLWData->unHLWData.stHLWUserData.b1TopBorderEn = _ON;
        pstHLWData->unHLWData.stHLWUserData.b1BottomBorderEn = _ON;
        pstHLWData->unHLWData.stHLWUserData.b1LeftBorderEn = _ON;
        pstHLWData->unHLWData.stHLWUserData.b1RightBorderEn = _ON;
        pstHLWData->unHLWData.stHLWUserData.ucHLWRed = 255;
        pstHLWData->unHLWData.stHLWUserData.ucHLWGreen = 0;
        pstHLWData->unHLWData.stHLWUserData.ucHLWBlue = 0;
        pstHLWData->unHLWData.stHLWUserData.ucBorderWidth = _HL_WIN_BORDER_SIZE;

        switch(GET_OSD_HLWIN_TYPE())
        {
            case _HL_WIN_FULL:

                pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth = _PANEL_DH_WIDTH - _HL_WIN_BORDER_SIZE;
                pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;

                break;

            case _HL_WIN_LEFTSIDE:

                pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth = _PANEL_DH_WIDTH / 2;
                pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;

                break;

            case _HL_WIN_TOPSIDE:

                pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth = _PANEL_DH_WIDTH - _HL_WIN_BORDER_SIZE;
                pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight = _PANEL_DV_HEIGHT / 2;

                break;

            case _HL_WIN_CENTER:

                pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth = _PANEL_DH_WIDTH / 2;
                pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight = _PANEL_DV_HEIGHT / 2;
                pstHLWData->unHLWData.stHLWUserData.usHLWinHPos = ((_PANEL_DH_WIDTH - pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth) / 2) + ((_PANEL_DH_WIDTH - _PANEL_DH_WIDTH) / 2) - 1;
                pstHLWData->unHLWData.stHLWUserData.usHLWinVPos = (_PANEL_DV_HEIGHT - pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight) / 2 - 1;

                break;

            case _HL_WIN_MOVE:

                if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0x00) == _TRUE)
                {
                    pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth = _PANEL_DH_WIDTH / 6;
                    pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;
                    pstHLWData->unHLWData.stHLWUserData.usHLWinHPos = (_PANEL_DH_WIDTH - pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth) / 2;
                    pstHLWData->unHLWData.stHLWUserData.usHLWinVPos = 0;

                    g_usColorHLWinHWidth = pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth;
                    g_usColorHLWinVHeight = pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight;
                    g_usColorHLWinHPos = pstHLWData->unHLWData.stHLWUserData.usHLWinHPos;
                    g_usColorHLWinVPos = pstHLWData->unHLWData.stHLWUserData.usHLWinVPos;
                    g_bColorHLWinRLMove = _RIGHT;
                }
                else
                {
                    pstHLWData->unHLWData.stHLWUserData.usHLWinHWidth = g_usColorHLWinHWidth;
                    pstHLWData->unHLWData.stHLWUserData.usHLWinVHeight = g_usColorHLWinVHeight;
                    pstHLWData->unHLWData.stHLWUserData.usHLWinHPos = g_usColorHLWinHPos;
                    pstHLWData->unHLWData.stHLWUserData.usHLWinVPos = g_usColorHLWinVPos;
                }

                break;

            default:

                break;
        }
    }
#endif
}
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Sharpness
// Input Value  : Select Region, Sharpness setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetSharpnessData(EnumSelRegion enumSelRegion, StructSharpnessSetting *pstSharpnessData)
{
    BYTE ucOsdSelSharpness = GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort());

    pstSharpnessData->enumSharpnessMode = _SHARPNESS_USER;
    pstSharpnessData->unSharpnessData.stSharpnessUserData.ucBank = UserAdjustGetSharpnessCoefBankNum();

    // DM Requires sharpness function bypass
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableH = UserCommonColorGetSharpnessDMCoefH();
        pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableV = UserCommonColorGetSharpnessDMCoefV();
        return;
    }
#endif
#endif

    // 1:1 Mode Use Different Scaling Table
    if((UserCommonColorScalingByPassTableSel(enumSelRegion) == _TRUE) ||
       (UserAdjustSharpnessBypassCheck() == _TRUE))
    {
#if(_HW_HSU_128TAPS_SUPPORT == _ON)
        pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableH = UserAdjustGetSharpness1To1Coef(_H_SU_128TAPS_1_TO_1, enumSelRegion, ucOsdSelSharpness);
#elif(_HW_HSU_96TAPS_SUPPORT == _ON)
        pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableH = UserAdjustGetSharpness1To1Coef(_H_SU_96TAPS_1_TO_1, enumSelRegion, ucOsdSelSharpness);
#endif
    }
    else
    {
#if(_HW_HSU_128TAPS_SUPPORT == _ON)
        pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableH = UserAdjustGetSharpnessNormalCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, ucOsdSelSharpness);
#elif(_HW_HSU_96TAPS_SUPPORT == _ON)
        pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableH = UserAdjustGetSharpnessNormalCoef(_H_V_SU_96TAPS_NORMAL, enumSelRegion, ucOsdSelSharpness);
#endif
    }

#if(_HW_VSU_128TAPS_SUPPORT == _ON)
    pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableV = UserAdjustGetSharpnessNormalCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, ucOsdSelSharpness);
#elif(_VSU_96TAPS_SUPPORT == _ON)
    pstSharpnessData->unSharpnessData.stSharpnessUserData.pucTableV = UserAdjustGetSharpnessNormalCoef(_H_V_SU_96TAPS_NORMAL, enumSelRegion, ucOsdSelSharpness);
#endif
}
#endif// End of #if(_SHARPNESS_SUPPORT == _ON)

#if(_SD_TABLE_SEL_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User function Adjust for ScalingDown Coef
// Input Value  : Select Region, Sharpness setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetScalingDownCoef(EnumSelRegion enumSelRegion, StructScalingDownCoefSetting *pstScalingDownData, EnumByPassEnable enumBypassFSEnable)
{
    enumBypassFSEnable = enumBypassFSEnable;
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
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_R_B_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
#endif
        case _FULL_REGION:
        case _DEMO_OUTSIDE:
        case _DEMO_INSIDE:
#if(_DRR_SUPPORT == _ON)
            if(enumBypassFSEnable != _BYPASS_ENABLE)
            {
                pstScalingDownData->unScalingDownData.stScalingDownUserData.pucTableSD_H = UserAdjustGetScalingDownCoefH(_H_SD_128TAPS_BYPASS_2, enumSelRegion);
                pstScalingDownData->unScalingDownData.stScalingDownUserData.pucTableSD_V = UserAdjustGetScalingDownCoefV(_V_SD_64TAPS_BYPASS_2, enumSelRegion);
            }
            else
#endif
            {
                pstScalingDownData->unScalingDownData.stScalingDownUserData.pucTableSD_H = UserAdjustGetScalingDownCoefH(_H_SD_128TAPS_NORMAL_2, enumSelRegion);
                pstScalingDownData->unScalingDownData.stScalingDownUserData.pucTableSD_V = UserAdjustGetScalingDownCoefV(_V_SD_64TAPS_NORMAL_2, enumSelRegion);
            }
            break;
        default:
            break;
    }
}
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
//--------------------------------------------------
// Description  : User function Adjust for BorderWindow
// Input Value  : BorderWindow setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetBorderWindowData(StructBorderWindowSetting *pstBorderWindowData)
{
    pstBorderWindowData->enumBorderWindowMode = _BORDER_WINDOW_USER;

#if((_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_SYNC)
    {
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
        if((GET_EAGLE_SIGHT_STATUS() == _ON) && (GET_EAGLE_SIGHT_CIRCLE_WIN_STATUS() == _OFF) && (GET_EAGLE_SIGHT_BORDER() != 0x00))
#else
        if((GET_EAGLE_SIGHT_STATUS() == _ON) && (GET_EAGLE_SIGHT_BORDER() != 0x00))
#endif
        {
            StructTimingFormat stTimingFormat;
            memset(&stTimingFormat, 0, sizeof(StructTimingFormat));

            // Get Sub Region Background
            UserCommonDisplayGetPipSubBackground(&stTimingFormat);

            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 1;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 1;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 1;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 1;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = stTimingFormat.usHStart - _PANEL_DH_START;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = stTimingFormat.usHWidth - GET_EAGLE_SIGHT_BORDER();
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = stTimingFormat.usVStart - _PANEL_DV_START;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = stTimingFormat.usVHeight - GET_EAGLE_SIGHT_BORDER();

            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;

            // Border Color : Red
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowRed = 0x80;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowGreen = 0x00;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowBlue = 0x00;

            // Border Width
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWidth = GET_EAGLE_SIGHT_BORDER();
        }
        else
        {
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;

            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
        }
    }
    else
#endif
    {
        if(GET_OSD_SELECT_REGION_WIDTH() == 0x00)
        {
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;

            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
            pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
        }
        else
        {
            StructTimingFormat stTimingFormat;
            memset(&stTimingFormat, 0, sizeof(StructTimingFormat));

            pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWidth = GET_OSD_SELECT_REGION_WIDTH();

            // Set border color
            switch(GET_OSD_SELECT_REGION_COLOR())
            {
                default:
                case _SELECT_REGION_COLOR_R: // Red
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowRed = 0x80;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowGreen = 0x00;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowBlue = 0x00;
                    break;

                case _SELECT_REGION_COLOR_G: // Green
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowRed = 0x00;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowGreen = 0x80;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowBlue = 0x00;
                    break;

                case _SELECT_REGION_COLOR_B: // Blue
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowRed = 0x00;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowGreen = 0x00;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowBlue = 0x80;
                    break;

                case _SELECT_REGION_COLOR_W: // White
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowRed = 0xFF;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowGreen = 0xFF;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.ucBorderWinowBlue = 0xFF;
                    break;
            }

            switch(SysModeGetDisplayMode())
            {
                default:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
                case _DISPLAY_MODE_1P:
                    // Disable border in 1P mode
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;

                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;
                    return;

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                    // Get Right Region Background
                    UserCommonDisplayGetPbplrRightBackground(&stTimingFormat);

                    // Set BW1 on Right Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = stTimingFormat.usHStart - _PANEL_DH_START;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = stTimingFormat.usHWidth;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = stTimingFormat.usVHeight;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;

                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;
                    break;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PBP_TB:
                    // Set BW1 on Bottom Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = _PANEL_DH_WIDTH - 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;

                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;

                    break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_2P_PIP:
                    // Get Sub Region Background
                    UserCommonDisplayGetPipSubBackground(&stTimingFormat);

                    // Set BW1 on Sub Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = stTimingFormat.usHStart - _PANEL_DH_START;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = stTimingFormat.usHWidth - GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = stTimingFormat.usVStart - _PANEL_DV_START;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = stTimingFormat.usVHeight - GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 1;

                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;

                    break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_FLAG:
                    // Get 3P Main Region Background
                    UserCommonDisplayGet3PFlagMainRegionBackground(&stTimingFormat);

                    // Set BW1 on 3P Main Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = stTimingFormat.usHStart - _PANEL_DH_START;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = stTimingFormat.usHWidth - GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = stTimingFormat.usVHeight;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 1;

                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;

                    break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_3P_SKEW_R:
                    // Set BW1 on Left Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = _PANEL_DV_HEIGHT;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 1;
                    // Set BW2 on Left-Top Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;

                    break;

                case _DISPLAY_MODE_3P_SKEW_L:
                    // Set BW1 on Left Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = _PANEL_DV_HEIGHT;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 1;
                    // Set BW2 on Right-Bottom Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = (_PANEL_DH_WIDTH >> 1) - 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = ((_PANEL_DV_HEIGHT >> 1) - 1) + GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;

                    break;

#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)

                case _DISPLAY_MODE_3P_SKEW_T:
                    // Set BW1 on Top Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = _PANEL_DH_WIDTH - 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;
                    // Set BW2 on Right-Bottom Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = (_PANEL_DH_WIDTH >> 1) - 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = ((_PANEL_DV_HEIGHT >> 1) - 1) + GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 0;

                    break;

                case _DISPLAY_MODE_3P_SKEW_B:
                    // Set BW1 on Bottom Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = ((_PANEL_DV_HEIGHT >> 1) - 1) + GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;
                    // Set BW2 on Left-Top Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 1;

                    break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                case _DISPLAY_MODE_4P:
                    // Set BW1 on Right-Bottom Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win1 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win1 = (_PANEL_DH_WIDTH >> 1) - 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win1 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win1 = ((_PANEL_DV_HEIGHT >> 1) - 1) + GET_OSD_SELECT_REGION_WIDTH();
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win1 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win1 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win1 = 0;
                    // Set BW1 on Left-Top Region
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usHWidth_Win2 = (_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVStart_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.usVHeight_Win2 = (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1TopBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1BottomBorderEn_Win2 = 1;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1LeftBorderEn_Win2 = 0;
                    pstBorderWindowData->unBorderWindowData.stBorderWindowData.b1RightBorderEn_Win2 = 1;

                    break;
#endif
            }
        }
    }

#endif // End of #if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
}
#endif // End of #if(_BORDER_WINDOW_SUPPORT == _ON)

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
//--------------------------------------------------
// Description  : User function Adjust for Local Contrat
// Input Value  : Local contrast setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetLocalContrastData(EnumSelRegion enumSelRegion, StructLocalContrastSetting *pstLocalContrastData)
{
#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
    BYTE ucLocalContrastStatus = GET_OSD_LOCAL_CONTRAST(ucOSDSelectRegion);

#if(_SDR_PLUS_FUNCTION == _ON)
    BYTE ucSDRPlusStatus = GET_OSD_SDR_PLUS(ucOSDSelectRegion);
#if(_HDR10_SUPPORT == _ON)
    EnumHDR10Status enumHDR10Status = UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion));
#endif
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(UserCommonColorDMGetDisplayRegion(enumSelRegion)) == _TRUE) || (UserAdjustDMPQMeasure(enumSelRegion) == _TRUE))
    {
        pstLocalContrastData->enumLocalContrastMode = _LOCALCONTRAST_OFF;
        return;
    }
#endif
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
    if(ucSDRPlusStatus != _OFF)
    {
#if(_HDR10_SUPPORT == _ON)
        if(enumHDR10Status == _HDR10_OFF)
#endif
        {
            pstLocalContrastData->enumLocalContrastMode = _LOCALCONTRAST_SDR_PLUS;
            pstLocalContrastData->unLocalContrastData.stLocalContrastSDRPlusData.enumLocalContrastBlendingStatus = _LOCALCONTRAST_BLENDING_ENABLE;
            pstLocalContrastData->unLocalContrastData.stLocalContrastSDRPlusData.ucTMFactor = GET_OSD_SDR_PLUS_DARK(ucOSDSelectRegion);
            pstLocalContrastData->unLocalContrastData.stLocalContrastSDRPlusData.ucYdiffgainFactor = GET_OSD_SDR_PLUS_SHARP(ucOSDSelectRegion);
            pstLocalContrastData->unLocalContrastData.stLocalContrastSDRPlusData.ucBank = UserAdjustGetLocalContrastTableBank();
            pstLocalContrastData->unLocalContrastData.stLocalContrastSDRPlusData.pucTable = UserAdjustGetLocalContrastSDRPlusAddress();
            return;
        }
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
        if(ucLocalContrastStatus != _LOCAL_CONTRAST_OFF)
        {
#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
            if(ucLocalContrastStatus == _LOCAL_CONTRAST_USER)
            {
                ucLocalContrastStatus = _LOCAL_CONTRAST_H;
                pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.enumLocalContrastBlendingStatus = _LOCALCONTRAST_BLENDING_ENABLE;
                pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.ucTMFactor = GET_OSD_LOCAL_CONTRAST_BLENDING(ucOSDSelectRegion);
                pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.ucYdiffgainFactor = GET_OSD_LOCAL_CONTRAST_DIFFGAIN(ucOSDSelectRegion);
            }
            else
            {
                pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.enumLocalContrastBlendingStatus = _LOCALCONTRAST_BLENDING_DISABLE;
            }
#endif
            pstLocalContrastData->enumLocalContrastMode = _LOCALCONTRAST_HDR10_USER;
            pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.ucBank = UserAdjustGetLocalContrastTableBank();
            pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_540NIT = UserAdjustGetLocalContrastHDR10TableAddress(enumSelRegion, ucLocalContrastStatus - 1, _HDR10_STATIC_MASTERING_LV_TYPE_540);
            pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_1200NIT = UserAdjustGetLocalContrastHDR10TableAddress(enumSelRegion, ucLocalContrastStatus - 1, _HDR10_STATIC_MASTERING_LV_TYPE_1200);
            pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_4000NIT = UserAdjustGetLocalContrastHDR10TableAddress(enumSelRegion, ucLocalContrastStatus - 1, _HDR10_STATIC_MASTERING_LV_TYPE_4000);
            pstLocalContrastData->unLocalContrastData.stLocalContrastHDR10UserData.stLocalContrastHDR10TableArray.pucLocalContrastTable_10000NIT = UserAdjustGetLocalContrastHDR10TableAddress(enumSelRegion, ucLocalContrastStatus - 1, _HDR10_STATIC_MASTERING_LV_TYPE_10000);

            return;
        }
    }
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    if((UserCommonColorNightSniperCheckStatus(enumSelRegion) == _TRUE) && (GET_OSD_NIGHT_SNIPER(ucOSDSelectRegion) != _OFF))
    {
        pstLocalContrastData->enumLocalContrastMode = _LOCALCONTRAST_NIGHT_SNIPER;
        pstLocalContrastData->unLocalContrastData.stLocalContrastNightSniperData.ucBank = UserAdjustGetLocalContrastTableBank();
        pstLocalContrastData->unLocalContrastData.stLocalContrastNightSniperData.pucTable = UserAdjustGetLocalContrastNightSniperAddress();
        return;
    }
#endif

    if(ucLocalContrastStatus != _LOCAL_CONTRAST_OFF)
    {
#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
        if(ucLocalContrastStatus == _LOCAL_CONTRAST_USER)
        {
            ucLocalContrastStatus = _LOCAL_CONTRAST_H;
            pstLocalContrastData->unLocalContrastData.stLocalContrastUserData.enumLocalContrastBlendingStatus = _LOCALCONTRAST_BLENDING_ENABLE;
            pstLocalContrastData->unLocalContrastData.stLocalContrastUserData.ucTMFactor = GET_OSD_LOCAL_CONTRAST_BLENDING(ucOSDSelectRegion);
            pstLocalContrastData->unLocalContrastData.stLocalContrastUserData.ucYdiffgainFactor = GET_OSD_LOCAL_CONTRAST_DIFFGAIN(ucOSDSelectRegion);
        }
        else
        {
            pstLocalContrastData->unLocalContrastData.stLocalContrastUserData.enumLocalContrastBlendingStatus = _LOCALCONTRAST_BLENDING_DISABLE;
        }
#endif
        pstLocalContrastData->enumLocalContrastMode = _LOCALCONTRAST_USER;
        pstLocalContrastData->unLocalContrastData.stLocalContrastUserData.ucBank = UserAdjustGetLocalContrastTableBank();
        pstLocalContrastData->unLocalContrastData.stLocalContrastUserData.pucTable = UserAdjustGetLocalContrastTableAddress(ucLocalContrastStatus - 1);

        return;
    }
#endif

    enumSelRegion = enumSelRegion;
    pstLocalContrastData->enumLocalContrastMode = _LOCALCONTRAST_OFF;
}

//--------------------------------------------------
// Description  : User function Adjust for Local Contrat
// Input Value  : Local contrast setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetLocalContrastTemporalData(StructLocalContrastTemporalSetting *pstLocalContrastData)
{
    pstLocalContrastData->enumLocalContrastTemporalMode = _LOCALCONTRAST_TEMPORAL_USER;

    // Get Temporal Filter Table
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.ucBank = UserAdjustGetLocalContrastTableBank();
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_24 = UserAdjustGetLocalContrastTemporalTableAddress(_LOCALCONTRAST_TEMPORAL_TYPE_24);
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_60 = UserAdjustGetLocalContrastTemporalTableAddress(_LOCALCONTRAST_TEMPORAL_TYPE_60);
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_120 = UserAdjustGetLocalContrastTemporalTableAddress(_LOCALCONTRAST_TEMPORAL_TYPE_120);
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_144 = UserAdjustGetLocalContrastTemporalTableAddress(_LOCALCONTRAST_TEMPORAL_TYPE_144);
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_165 = UserAdjustGetLocalContrastTemporalTableAddress(_LOCALCONTRAST_TEMPORAL_TYPE_165);
    pstLocalContrastData->unLocalContrastTemporalData.stLocalContrastTemporalUserData.pucTemporalTable_240 = UserAdjustGetLocalContrastTemporalTableAddress(_LOCALCONTRAST_TEMPORAL_TYPE_240);
}
#endif //// End of #if(_COLOR_IP_LOCAL_CONTRAST == _ON)

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get OSD LocalContrast enable status
// Input Value  : None
// Output Value : function enable status
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceColorGetLocalContrastEnableStatus(EnumSelRegion enumSelRegion)
{
    if(GET_OSD_LOCAL_CONTRAST(UserAdjustGetOSDSelectRegion(enumSelRegion)) != _LOCAL_CONTRAST_OFF)
    {
        return _FUNCTION_ON;
    }
    else
    {
        return _FUNCTION_OFF;
    }
}
#endif //// End of #if(_LOCAL_CONTRAST_SUPPORT == _ON)

#if(_SDR_PLUS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get OSD SDR+ enable status
// Input Value  : enumSelRegion
// Output Value : function enable status
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceColorGetSDRPlusEnableStatus(EnumSelRegion enumSelRegion)
{
    if(GET_OSD_SDR_PLUS(UserAdjustGetOSDSelectRegion(enumSelRegion)) != _OFF)
    {
        return _FUNCTION_ON;
    }
    else
    {
        return _FUNCTION_OFF;
    }
}
#endif //// End of #if(_LOCAL_CONTRAST_SUPPORT == _ON)

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get OSD SDR+ enable status
// Input Value  : enumSelRegion
// Output Value : function enable status
//--------------------------------------------------
EnumNightSniperType UserInterfaceColorGetNightSniperEnableStatus(EnumSelRegion enumSelRegion)
{
    if(GET_OSD_NIGHT_SNIPER(UserAdjustGetOSDSelectRegion(enumSelRegion)) != _OFF)
    {
        return _NIGHT_SNIPER_ON;
    }
    else
    {
        return _NIGHT_SNIPER_OFF;
    }
}
#endif //// End of #if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)

#if(_OD_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get OSD OD enable status
// Input Value  : None
// Output Value : function enable status
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceColorGetODEnableStatus(void)
{
    if(UserAdjustGetOsdODStatus() == _ENABLE)
    {
        return _FUNCTION_ON;
    }
    else
    {
        return _FUNCTION_OFF;
    }
}

//--------------------------------------------------
// Description  : User function Adjust for OD
// Input Value  : OD structure data
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetODData(StructODSetting *pstODData)
{
    // User select an OD mode (based on OSD for example)
    if(UserAdjustGetOsdODStatus() == _ENABLE)
    {
        pstODData->enumODMode = _OD_USER;
    }
    else
    {
        pstODData->enumODMode = _OD_OFF;
    }

    // User fills in corresponding data
    switch(pstODData->enumODMode)
    {
        case _OD_USER:
            UserAdjustODGetODUserInfo(&(pstODData->unODData.stODUserData));
            break;

#if(_OD_BY_POSITION_SUPPORT == _ON)
        case _OD_USER_BYPOS:
            UserAdjustODGetODUserByPosInfo(&(pstODData->unODData.stODUserByPosData));
            break;
#endif
        case _OD_OFF:
        default:
            break;
    }
}

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Send OD Gain to Back chip
// Input Value  : OD Gain
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDataExchangeSendODGain(BYTE ucODGain)
{
    UserCommonDataExchangeSendByte(_DATA_EXCHANGE_USER_DATA, _DATA_EXCHANGE_USER_DATA_OD_GAIN, ucODGain);
}

//--------------------------------------------------
// Description  : Send OD User Data to Back chip
// Input Value  : OD structure data
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDataExchangeSendODUserData(StructODSetting *pstODData)
{
    if(pstODData->enumODMode == _OD_OFF)
    {
        UserCommonDataExchangeSendByte(_DATA_EXCHANGE_USER_DATA, _DATA_EXCHANGE_USER_DATA_OD_ENABLE, _DISABLE);
    }
    else if(pstODData->enumODMode == _OD_USER)
    {
        BYTE pucBuffer[_DATA_EXCHANGE_USER_DATA_OD_USER_CONTENT_LEN] =
        {
            pstODData->enumODMode,
            pstODData->unODData.stODUserData.ucDeltaGain,
            pstODData->unODData.stODUserData.stODTableInfo.ucTableGroup,
            pstODData->unODData.stODUserData.stODTableInfo.ucTableIndex,
        };

        UserCommonDataExchangeSendData(_DATA_EXCHANGE_USER_DATA, _DATA_EXCHANGE_USER_DATA_OD_USER, _DATA_EXCHANGE_USER_DATA_OD_USER_CONTENT_LEN, pucBuffer);
    }
#if(_OD_BY_POSITION_SUPPORT == _ON)
    else if(pstODData->enumODMode == _OD_USER_BYPOS)
    {
        BYTE pucBuffer[_DATA_EXCHANGE_USER_DATA_OD_USER_BYPOS_CONTENT_LEN] =
        {
            pstODData->enumODMode,
            pstODData->unODData.stODUserByPosData.ucDeltaGain,
            pstODData->unODData.stODUserByPosData.stODTableInfo.ucTableGroup,
            pstODData->unODData.stODUserByPosData.stODTableInfo.ucTableIndex,

            pstODData->unODData.stODUserByPosData.b1ODByPosEnable,
            pstODData->unODData.stODUserByPosData.b2RegionSize,
            pstODData->unODData.stODUserByPosData.stODByPosTableInfo.ucTableIndex,
        };

        UserCommonDataExchangeSendData(_DATA_EXCHANGE_USER_DATA, _DATA_EXCHANGE_USER_DATA_OD_USER_BYPOS, _DATA_EXCHANGE_USER_DATA_OD_USER_BYPOS_CONTENT_LEN, pucBuffer);
    }
#endif
}

//--------------------------------------------------
// Description  : User function - Adjust OD Enable
// Input Value  : OD Enable / Disable
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDataExchangeSendODEnable(BYTE ucEnable)
{
    UserCommonDataExchangeSendByte(_DATA_EXCHANGE_USER_DATA, _DATA_EXCHANGE_USER_DATA_OD_ENABLE, ucEnable);
}
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#endif // End of #if(_OD_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User function for Get Osd System SelRegion
// Input Value  : EnumDisplayRegion
// Output Value : EnumSelRegion
//--------------------------------------------------
EnumSelRegion UserInterfaceColorGetOSDSystemSelRegion(void)
{
    return GET_OSD_SYSTEM_SELECT_REGION();
}

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : whether SDR mode calibrated by OCC/OGC
// Input Value  : void
// Output Value : _SDR_CALIBRATION_BY_OGC_TOOL / _SDR_NONE_CALIBRATION_BY_OGC_TOOL
//--------------------------------------------------
EnumSDRCalibrationType UserInterfaceColorSDROCCOGCMode(void)
{
    if((GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_NATIVE) &&
       (GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_OFF))
    {
        return _SDR_NONE_CALIBRATION_BY_OGC_TOOL;
    }
    else
    {
        return _SDR_CALIBRATION_BY_OGC_TOOL;
    }
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function Adjust for BorderWindow
// Input Value  : BorderWindow setting struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetCircleWindowData(StructCircleWindowSetting *pstCircleWindowData)
{
    if(UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_SYNC)
    {
        if((GET_EAGLE_SIGHT_STATUS() == _ON) && (GET_EAGLE_SIGHT_CIRCLE_WIN_STATUS() == _ON))
        {
            StructTimingFormat stBGTimingFormat = {0};
            StructTimingFormat stActiveTimingFormat = {0};
            bit bHWider = _TRUE;

            // Get Sub Region Background
            UserCommonDisplayGetPipSubBackground(&stBGTimingFormat);
            UserCommonDisplayGetPipSubActiveTiming(&stActiveTimingFormat);

            if(stActiveTimingFormat.usVHeight > stActiveTimingFormat.usHWidth)
            {
                bHWider = _FALSE;
            }

            pstCircleWindowData->unCircleWindowData.stCircleWindowData.b1CircleWindowEn = _TRUE;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usHCenter = stActiveTimingFormat.usHStart + (stActiveTimingFormat.usHWidth / 2) - stBGTimingFormat.usHStart - 1;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVCenter = stActiveTimingFormat.usVStart + (stActiveTimingFormat.usVHeight / 2) - stBGTimingFormat.usVStart - 1;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usHStart = pstCircleWindowData->unCircleWindowData.stCircleWindowData.usHCenter;

            if(bHWider == _TRUE)
            {
                pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVStart = stActiveTimingFormat.usVStart - stBGTimingFormat.usVStart;
            }
            else
            {
                pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVStart = pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVCenter - (stActiveTimingFormat.usHWidth / 2) + 1;
            }

            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usBorder_HStart = pstCircleWindowData->unCircleWindowData.stCircleWindowData.usHStart;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usBorder_VStart = pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVStart + GET_EAGLE_SIGHT_BORDER();

            // Border Color : Red
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWinowRed = 0x80;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWinowGreen = 0x00;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWinowBlue = 0x00;

            // Border Width
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWidth = GET_EAGLE_SIGHT_BORDER();
        }
        else
        {
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.b1CircleWindowEn = _FALSE;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usHCenter = 0;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVCenter = 0;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usHStart = 0;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usVStart = 0;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usBorder_HStart = 0;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.usBorder_VStart = 0;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWinowRed = 0x00;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWinowGreen = 0x00;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWinowBlue = 0x00;
            pstCircleWindowData->unCircleWindowData.stCircleWindowData.ucBorderWidth = 0;
        }
    }
}
#endif
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
//--------------------------------------------------
// Description  : User function Get Anti-Aliasing OSD Data
// Input Value  : StructAntiAliasingSetting
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetAntiAliasingData(StructAntiAliasingSetting *pstAntiAliasingData)
{
    pstAntiAliasingData->stAntiAliasingUserData.ucLevel = GET_ANTI_ALIASING_LEVEL();
    pstAntiAliasingData->stAntiAliasingUserData.ucMode = GET_ANTI_ALIASING_MODE();
}

//--------------------------------------------------
// Description  : User function Get Anti-Aliasing Coef Table
// Input Value  : EnumSelRegion, StructAntiAliasingSetting
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGetAntiAliasingCoefTableData(StructAntiAliasingSetting *pstAntiAliasingData)
{
    BYTE ucAntiAliasingLevelStatus = pstAntiAliasingData->stAntiAliasingUserData.ucLevel;
    BYTE ucAntiAliasingModeStatus = pstAntiAliasingData->stAntiAliasingUserData.ucMode;

    pstAntiAliasingData->stAntiAliasingUserData.pulTable = UserAdjustGetAntiAliasingCoefTableAddress(ucAntiAliasingModeStatus, ucAntiAliasingLevelStatus - 1);
}
#endif

#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : User function Decide Gamma LUT loaded in OutputGamma or PostGamma
// Input Value  : enumSelRegion
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceColorUniformityPlusFunctionStatus(EnumSelRegion enumSelRegion)
{
    EnumFunctionOnOFF enumFunctionOnOFF = _FUNCTION_OFF;
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
#if(_OGC_FUNCTION == _ON)
    if(GET_OSD_GAMMA(ucOSDSelectRegion) != _GAMMA_OFF)
    {
        switch(UserAdjustOGCOSDMapping(GET_OSD_GAMMA(ucOSDSelectRegion)))
        {
            case _OGC_MODE1:
                enumFunctionOnOFF = _FUNCTION_ON;
                break;

            case _OGC_MODE2:
                enumFunctionOnOFF = _FUNCTION_ON;
                break;

            case _OGC_MODE3:
                enumFunctionOnOFF = _FUNCTION_OFF;
                break;

            case _OGC_MODE4:
                enumFunctionOnOFF = _FUNCTION_OFF;
                break;

            default:
                break;
        }
    }
#endif
#if(_OCC_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        switch(GET_OSD_PCM_STATUS(ucOSDSelectRegion))
        {
            case _PCM_OSD_SRGB:
                enumFunctionOnOFF = _FUNCTION_ON;
                break;

            case _PCM_OSD_ADOBE_RGB:
                enumFunctionOnOFF = _FUNCTION_OFF;
                break;

            default:
                break;
        }
    }
#endif
    return enumFunctionOnOFF;
}
#endif // End of #if(_UNIFORMITY_PLUS_FUNCTION == _ON)

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function Decide to Use 3D Gamma Cube Mapping Table
// Input Value  : enumSelRegion
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceColor3DGammaCubeGetEnableStatus(EnumSelRegion enumSelRegion)
{
    EnumFunctionOnOFF enumFunctionOnOFF = _FUNCTION_OFF;
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
#if(_OCC_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        switch(GET_OSD_PCM_STATUS(ucOSDSelectRegion))
        {
            case _PCM_OSD_SRGB:
            case _PCM_OSD_ADOBE_RGB:
                enumFunctionOnOFF = _FUNCTION_ON;
                break;
            default:
                break;
        }
    }
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_EAGLE_SIGHT_STATUS() == _ON)
    {
        if(enumSelRegion == _2P_PIP_EAGLE_SIGHT_SUB)
        {
            enumFunctionOnOFF = _FUNCTION_OFF;
        }
    }
#endif
#endif
    return enumFunctionOnOFF;
}
#endif // End of #if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
