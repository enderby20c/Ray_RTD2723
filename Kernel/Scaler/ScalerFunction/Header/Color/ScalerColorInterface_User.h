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
// ID Code      : ScalerColorInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#define _OGC_FLASH_PAGE                                0

//--------------------------------------------------
// Definitions of OGC/OCC Calibration Checksum Address
// Max OGC/OCC Checksum Address 80
// Max FreesyncII Checksum address 16
//--------------------------------------------------
#define _OGC_CHKSUM_ADDRESS                            (_OGC_FLASH_PAGE * _FLASH_PAGE_SIZE)
#define _OGC_RGB_GAIN_CHKSUM_ADDRESS                   (_OGC_CHKSUM_ADDRESS + 1)
#define _OGC_HEADER_CHKSUM_ADDRESS                     (_OGC_CHKSUM_ADDRESS + 2)
#define _OCC_CHKSUM_ADDRESS                            (_OGC_CHKSUM_ADDRESS + 3)
#define _OCC_HDR_CHKSUM_ADDRESS                        (_OGC_CHKSUM_ADDRESS + 4)
#define _OCC_COLOR_MATRIX_CHKSUM_ADDRESS               (_OGC_CHKSUM_ADDRESS + 5)
#define _OCC_COLOR_MATRIX2_CHKSUM_ADDRESS              (_OGC_CHKSUM_ADDRESS + 6)
#define _OGC_DICOM_CHKSUM_ADDRESS                      (_OGC_CHKSUM_ADDRESS + 7)
#define _OGC_FINISH_ADDRESS                            (_OGC_CHKSUM_ADDRESS + 8)
#define _OCC_FINISH_ADDRESS                            (_OGC_CHKSUM_ADDRESS + 9)
#define _OGC_DICOM_FINISH_ADDRESS                      (_OGC_CHKSUM_ADDRESS + 10)
#define _HDR_CHKSUM_ADDRESS                            (_OGC_CHKSUM_ADDRESS + 11)
#define _HDR_FINISH_ADDRESS                            (_OGC_CHKSUM_ADDRESS + 12)
#define _DIMMING_OCC_CHKSUM_ADDRESS                    (_OGC_CHKSUM_ADDRESS + 13)
#define _DIMMING_IG_CHKSUM_ADDRESS                     (_OGC_CHKSUM_ADDRESS + 14)
#define _EDID_INFO_CHKSUM_ADDRESS                      (_OGC_CHKSUM_ADDRESS + 15)
#define _HDR_NOTM_BOUND_CHKSUM_ADDRESS                 (_OGC_CHKSUM_ADDRESS + 16)
#define _ADVANCED_HDR10_CHKSUM_ADDRESS                 (_OGC_CHKSUM_ADDRESS + 17)
#define _OGC_MAX_BRI_CHKSUM_ADDRESS                    (_OGC_CHKSUM_ADDRESS + 18)
#define _OGC_RGB_GAIN_MAX_BRI_CHKSUM_ADDRESS           (_OGC_CHKSUM_ADDRESS + 19)
#define _OCC_COLOR_MATRIX_MAX_BRI_CHKSUM_ADDRESS       (_OGC_CHKSUM_ADDRESS + 20)
#define _OCC_COLOR_MATRIX2_MAX_BRI_CHKSUM_ADDRESS      (_OGC_CHKSUM_ADDRESS + 21)
#define _DIMMING_NOTM_DCR_THD_CHKSUM_ADDRESS           (_OGC_CHKSUM_ADDRESS + 22)
#define _HDR_HLG_YMAPPING_CHKSUM_ADDRESS               (_OGC_CHKSUM_ADDRESS + 23)
#define _OCC_OGC_CALIBRATION_FINISH_ADDRESS            (_OGC_CHKSUM_ADDRESS + 24)
#define _HDR_BACKLIGHT_ADAPTIVE_CHKSUM_ADDRESS         (_OGC_CHKSUM_ADDRESS + 25)
#define _HDR_MASTERING_LV_STEPLESS_CHKSUM_ADDRESS      (_OGC_CHKSUM_ADDRESS + 26)
#define _HDR_USER_DEFINE_FIXED_POINT_CHKSUM_ADDRESS    (_OGC_CHKSUM_ADDRESS + 27)
#define _OCC_MULTI_BRI_3_CHKSUM_ADDRESS                (_OGC_CHKSUM_ADDRESS + 28)
#define _OCC_MULTI_BRI_4_CHKSUM_ADDRESS                (_OGC_CHKSUM_ADDRESS + 29)
#define _OCC_COLOR_MATRIX_MULTI_BRI_3_CHKSUM_ADDRESS   (_OGC_CHKSUM_ADDRESS + 30)
#define _OCC_COLOR_MATRIX2_MULTI_BRI_3_CHKSUM_ADDRESS  (_OGC_CHKSUM_ADDRESS + 31)
#define _OCC_COLOR_MATRIX_MULTI_BRI_4_CHKSUM_ADDRESS   (_OGC_CHKSUM_ADDRESS + 32)
#define _OCC_COLOR_MATRIX2_MULTI_BRI_4_CHKSUM_ADDRESS  (_OGC_CHKSUM_ADDRESS + 33)
#define _OGC_RGB_GAIN_MULTI_BRI_3_CHKSUM_ADDRESS       (_OGC_CHKSUM_ADDRESS + 34)
#define _OGC_RGB_GAIN_MULTI_BRI_4_CHKSUM_ADDRESS       (_OGC_CHKSUM_ADDRESS + 35)
#define _GD_PWMLUT_CHKSUM_ADDRESS                      (_OGC_CHKSUM_ADDRESS + 36)
#define _GD_FINISH_ADDRESS                             (_OGC_CHKSUM_ADDRESS + 37)
#define _OCC_VERIFY_CHECKSUM_ADDRESS                   (_OGC_CHKSUM_ADDRESS + 38)
#define _OGC_USER_INFO_ADDRESS                         (_OGC_CHKSUM_ADDRESS + 64)

#define _FREESYNC_II_CHKSUM_ADDRESS                    (_FREESYNC_II_FLASH_PAGE * _FLASH_PAGE_SIZE)
#define _FREESYNC_II_FINISH_ADDRESS                    (_FREESYNC_II_CHKSUM_ADDRESS + 1)
#define _FREESYNC_II_IG_CHKSUM_ADDRESS                 (_FREESYNC_II_CHKSUM_ADDRESS + 2)
#define _FREESYNC_II_IG_PQ_CHKSUM_ADDRESS              (_FREESYNC_II_CHKSUM_ADDRESS + 3)
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
//--------------------------------------------------
// Definitions of CCT Transfer Matrix
//--------------------------------------------------
#define _COLORIMETRY_TRANSFER_MATRIX_SIZE              9
#endif


#define _MRCM_SETTING_NUM                              6

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Digital Functions On/Off/Clock Gated
//--------------------------------------------------
typedef enum
{
    _FUNCTION_OFF,
    _FUNCTION_ON,
} EnumFunctionOnOFF;

//--------------------------------------------------
// Enumerations of Digital Functions Double Buffer
//--------------------------------------------------
typedef enum
{
    _DB_APPLY_NONE,
    _DB_APPLY_NO_POLLING,
    _DB_APPLY_POLLING,
} EnumDBApply;

typedef enum
{
    _DB_VS_TRIGGER,
    _DB_ENA_STOP_TRIGGER,
} EnumDBTriggerEvent;

//--------------------------------------------------
// Enumerations of Color Space
//--------------------------------------------------
typedef enum
{
    _COLOR_SPACE_RGB,
    _COLOR_SPACE_YCBCR422,
    _COLOR_SPACE_YCBCR444,
    _COLOR_SPACE_YCBCR420,
    _COLOR_SPACE_YPBPR,
    _COLOR_SPACE_Y_ONLY,
    _COLOR_SPACE_RAW,
} EnumColorSpace;

//--------------------------------------------------
// Enumerations of Colorimetry
//--------------------------------------------------
typedef enum
{
    _COLORIMETRY_RGB_SRGB,
    _COLORIMETRY_RGB_ADOBERGB,
    _COLORIMETRY_RGB_XRRGB,
    _COLORIMETRY_RGB_SCRGB,
    _COLORIMETRY_RGB_DCI_P3,
    _COLORIMETRY_RGB_COLOR_PROFILE,
    _COLORIMETRY_YCC_SMPTE_170M,
    _COLORIMETRY_YCC_ITUR_BT601,
    _COLORIMETRY_YCC_ITUR_BT709,
    _COLORIMETRY_YCC_XVYCC601,
    _COLORIMETRY_YCC_XVYCC709,
    _COLORIMETRY_Y_ONLY,
    _COLORIMETRY_RAW,
    _COLORIMETRY_EXT,
    _COLORMETRY_RESERVED,
}EnumColorimetry;

typedef enum
{
    _COLORIMETRY_EXT_RGB_SRGB,
    _COLORIMETRY_EXT_RGB_XRRGB,
    _COLORIMETRY_EXT_RGB_SCRGB,
    _COLORIMETRY_EXT_RGB_ADOBERGB,
    _COLORIMETRY_EXT_RGB_DCI_P3,
    _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE,
    _COLORIMETRY_EXT_RGB_ITUR_BT2020,
    _COLORIMETRY_EXT_YCC_ITUR_BT601,
    _COLORIMETRY_EXT_YCC_ITUR_BT709,
    _COLORIMETRY_EXT_YCC_XVYCC601,
    _COLORIMETRY_EXT_YCC_XVYCC709,
    _COLORIMETRY_EXT_YCC_SYCC601,
    _COLORIMETRY_EXT_YCC_ADOBEYCC601,
    _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL,
    _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL,
    _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14,
    _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE,
    _COLORIMETRY_EXT_ADD,
    _COLORIMETRY_EXT_RESERVED,
}EnumColorimetryExt;

typedef enum
{
    _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3D65,
    _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3DCI,
    _COLORIMETRY_ADD_EXT_YCC_ITUR_BT2100,
    _COLORIMETRY_ADD_EXT_RGB_SRGB,
    _COLORIMETRY_ADD_EXT_RGB_DEFAULTRGB,
    _COLORIMETRY_ADD_EXT_RESERVED,
}EnumColorimetryAddExt;


//--------------------------------------------------
// Enumerations of Quantization Range (YCC)
//--------------------------------------------------
typedef enum
{
    _YCC_QUANTIZATION_LIMIT_RANGE = 0x00,
    _YCC_QUANTIZATION_FULL_RANGE = 0x01,
    _YCC_QUANTIZATION_RESERVED = 0x02,
} EnumColorYCCQuantization;

//--------------------------------------------------
// Enumerations of Quantization Range (RGB)
//--------------------------------------------------
typedef enum
{
    _RGB_QUANTIZATION_FULL_RANGE = 0x00,
    _RGB_QUANTIZATION_LIMIT_RANGE = 0x01,
    _RGB_QUANTIZATION_DEFAULT_RANGE = 0x02,
    _RGB_QUANTIZATION_RESERVED = 0x03,
} EnumColorRGBQuantization;

//--------------------------------------------------
// Enumerations of User RGB Format
//--------------------------------------------------
typedef enum
{
    _RGB_FORMAT_FALSE = _FALSE,
    _RGB_FORMAT_TRUE = _TRUE,
} EnumRGBFormatStatus;

//--------------------------------------------------
// Enumerations of User Quantization Limit Range Status
//--------------------------------------------------
typedef enum
{
    _RGB_QUANT_LIMIT_RANGE_FALSE = _FALSE,
    _RGB_QUANT_LIMIT_RANGE_TRUE = _TRUE,
} EnumRGBQuantLimitRangeStatus;

//--------------------------------------------------
// Enumerations of User Quantization Limit Range Status
//--------------------------------------------------
typedef enum
{
    _YCC_QUANT_FULL_RANGE_FALSE = _FALSE,
    _YCC_QUANT_FULL_RANGE_TRUE = _TRUE,
} EnumYccQuantFullRangeStatus;

//--------------------------------------------------
// Enumerations of Highlight Window Type
//--------------------------------------------------
typedef enum
{
    _HLW_FULL_WINDOW,
    _HLW_INSIDE_WINDOW,
    _HLW_OUTSIDE_WINDOW,
} EnumHLWType;

//--------------------------------------------------
// Enumerations of Highlight Window Set Selection
//--------------------------------------------------
typedef enum
{
    _HLW_ALLSETA,
    _HLW_INSIDEA_OUTSIDEB,
    _HLW_INSIDEB_OUTSIDEA,
    _HLW_ALLSETB,
} EnumHLWSetSel;

//--------------------------------------------------
// Enumerations of Border Window
//--------------------------------------------------
typedef enum
{
    _BORDER_WIN1,
    _BORDER_WIN2,
} EnumBorderWin;

//--------------------------------------------------
// Definitions of Demo Mode Type
//--------------------------------------------------
typedef enum
{
    _DEMO_MODE_INSIDE,
    _DEMO_MODE_OUTSIDE,
    _DEMO_MODE_BOTH,
    _DEMO_OFF,
} EnumDemoModeType;

//--------------------------------------------------
// Enumerations of DCR Measure Select
//--------------------------------------------------
typedef enum
{
    _MEASURE_AVERAGE,      // R+G+B
    _MEASURE_R,            // R
    _MEASURE_G,            // G
    _MEASURE_B,            // B
    _MEASURE_Y,            // 2R+5G+B
} EnumDCRMeasureSel;

//--------------------------------------------------
// Enumerations of DCR Adjust Option
//--------------------------------------------------
typedef enum
{
    _DCR_ABOVE_TH1_NUM,
    _DCR_ABOVE_TH1_VAL,
#if(_HW_DCR_TH2_OPTION_SUPPORT == _ON)
    _DCR_ABOVE_TH2_NUM,
    _DCR_ABOVE_TH2_VAL,
#endif
#if(_HW_DCR_LV_NUM_OPTION_SUPPORT == _ON)
    _DCR_HIGH_LV_NUM_R,
    _DCR_LOW_LV_NUM_R,
#endif
    _DCR_HIGH_LV_VAL_R,
    _DCR_LOW_LV_VAL_R,
#if(_HW_DCR_LV_NUM_OPTION_SUPPORT == _ON)
    _DCR_HIGH_LV_NUM_G,
    _DCR_LOW_LV_NUM_G,
#endif
    _DCR_HIGH_LV_VAL_G,
    _DCR_LOW_LV_VAL_G,
#if(_HW_DCR_LV_NUM_OPTION_SUPPORT == _ON)
    _DCR_HIGH_LV_NUM_B,
    _DCR_LOW_LV_NUM_B,
#endif
    _DCR_HIGH_LV_VAL_B,
    _DCR_LOW_LV_VAL_B,
#if(_HW_DCR_YMAXMIN_OPTION_SUPPORT == _ON)
    _DCR_Y_MAX_VAL,
    _DCR_Y_MIN_VAL,
#endif
    _DCR_ABOVE_TH1_VAL_HIGH,
#if(_HW_DCR_TH2_OPTION_SUPPORT == _ON)
    _DCR_ABOVE_TH2_VAL_HIGH,
#endif
#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
    _DCR_MAX_CLL,
    _DCR_MAX_FALL,
    _DCR_MAX_FALL_HIGH,
#endif
} EnumDCRAdjOption;

//--------------------------------------------------
// Enumerations for DCR Get Average
//--------------------------------------------------
typedef enum
{
    _DCR_ABOVE_TH1_VAL_TOTAL,
#if(_HW_DCR_TH2_OPTION_SUPPORT == _ON)
    _DCR_ABOVE_TH2_VAL_TOTAL,
#endif
} EnumDCRAverageOption;

//--------------------------------------------------
// Enumerations of DCC Read Histo Info Result Option
//--------------------------------------------------
typedef enum
{
    _DCC_S0 = 0,
    _DCC_S1,
    _DCC_S2,
    _DCC_S3,
    _DCC_S4,
    _DCC_S5,
    _DCC_S6,
    _DCC_Y_MAX,
    _DCC_Y_MIN,
} EnumDCCReadOption;

//--------------------------------------------------
// Enumerations of DCC Auto Mode On Off
//--------------------------------------------------
typedef enum
{
    _DCC_AUTOMODE_ON,
    _DCC_AUTOMODE_OFF,
} EnumDCCAutoModeEnable;

//--------------------------------------------------
// Enumerations of DCC Auto Mode Setting Region
//--------------------------------------------------
typedef enum
{
    _DCC_SETTING_FULL,
    _DCC_SETTING_INSIDE,
    _DCC_SETTING_OUTSIDE,
    _DCC_SETTING_OTHER,
} EnumDccSettingType;

//--------------------------------------------------
// Define Color Effect Six Color
//--------------------------------------------------
typedef enum
{
    _SIXCOLOR_R,
    _SIXCOLOR_Y,
    _SIXCOLOR_G,
    _SIXCOLOR_C,
    _SIXCOLOR_B,
    _SIXCOLOR_M,
    _SIXCOLOR_AMOUNT = _SIXCOLOR_M,
}EnumSixColorType;

//--------------------------------------------------
// Define Night Sniper Mode
//--------------------------------------------------
typedef enum
{
    _NIGHT_SNIPER_OFF,
    _NIGHT_SNIPER_ON,
}EnumNightSniperType;

//--------------------------------------------------
// Enumerations of LocalContrast Temporal Type
//--------------------------------------------------
typedef enum
{
    _LOCALCONTRAST_BLENDING_DISABLE,
    _LOCALCONTRAST_BLENDING_ENABLE,
} EnumLocalContrastBlendingStatus;
//--------------------------------------------------
// Enumerations of Contrast Type
//--------------------------------------------------
typedef enum
{
    _CONTRAST_COEF_A,
    _CONTRAST_COEF_B,
} EnumCtsCoefType;

//--------------------------------------------------
// Enumerations of Brightness Type
//--------------------------------------------------
typedef enum
{
    _BRIGHTNESS_COEF_A,
    _BRIGHTNESS_COEF_B,
} EnumBriCoefType;

//--------------------------------------------------
// Enumerations of OCC Options
//--------------------------------------------------
typedef enum
{
    _PCM_SRGB,
    _PCM_ADOBE_RGB,
    _PCM_USER_DEFINE,
    _PCM_EBU_MODE,
    _PCM_SOFT_PROFT,
    _PCM_REC_709,
    _PCM_DCI_P3,
    _PCM_SMPTE_C,
    _PCM_USER_DEFINE_2,
    _PCM_USER_DEFINE_3,
    _PCM_USER_DEFINE_4,
    _PCM_USER_DEFINE_5,
    _PCM_USER_DEFINE_6,
    _PCM_DISPLAY_P3,
    _PCM_STANDARD, // Gamma2.2 + sRGB
    _PCM_HDR_2084, // _PCM_IG_BYPASS
    _PCM_HLG,
    _TOTAL_COLORSPACE_NUM,
    _PCM_USER_MODE = _TOTAL_COLORSPACE_NUM,
    _PCM_BYPASS,
    _PCM_OFF,
} EnumPCMType;

//--------------------------------------------------
// Enumerations of PCM Mode
//--------------------------------------------------
typedef enum
{
    _OGC_MODE = 0,
    _PCM_MODE,
} EnumPCMModeSelect;

//--------------------------------------------------
// Enumerations of PCM Node Type
//--------------------------------------------------
typedef enum
{
    _PCM_NODE_129 = 0,
    _PCM_NODE_1025,
} EnumPCMNodeType;

//--------------------------------------------------
// Enumerations of Global Dimming
//--------------------------------------------------
typedef enum
{
    _GLOBAL_DIMMING_DISABLE,
    _GLOBAL_DIMMING_ENABLE,
} EnumGlobalDimmingStatus;

typedef enum
{
    _GLOBAL_DIMMING_SUB_FORCE_MAIN,
    _GLOBAL_DIMMING_SUB_USER,
} EnumGlobalDimmingSubStatus;
//--------------------------------------------------
// Definitions of HDR10 Status
//--------------------------------------------------
typedef enum
{
    _HDR10_OFF,
    _HDR10_ON,
#if(_HLG_SUPPORT == _ON)
    _HLG_ON,
#endif
} EnumHDR10Status;

//--------------------------------------------------
// Definitions of HDR Demo Mode
//--------------------------------------------------
typedef enum
{
    _HDR_DEMO_OFF,
    _HDR_DEMO_ON,
} EnumHDRDemoStatus;

//--------------------------------------------------
// Definitions of HDR Color Matrix
//--------------------------------------------------
typedef enum
{
    _HDR10_COLOR_MATRIX_SRGB,
    _HDR10_COLOR_MATRIX_ADOBE,
    _HDR10_COLOR_MATRIX_DCIP3_D65,
    _HDR10_COLOR_MATRIX_BT2020,
} EnumHDR10ColorMatrix;

//--------------------------------------------------
// Definitions of HDR SBTM Color Matrix
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_COLOR_MATRIX_USER_DEFINE,
    _HDR10_SBTM_COLOR_MATRIX_BT_709,
    _HDR10_SBTM_COLOR_MATRIX_DCIP3_D65,
    _HDR10_SBTM_COLOR_MATRIX_BT2020,
} EnumHDR10SBTMColorMatrix;

//--------------------------------------------------
// Definitions of DM Color Matrix
//--------------------------------------------------
typedef enum
{
    _DM_COLOR_MATRIX_SRGB,
    _DM_COLOR_MATRIX_ADOBE,
    _DM_COLOR_MATRIX_DCIP3_D65,
    _DM_COLOR_MATRIX_BT2020,
    _DM_COLOR_MATRIX_NATIVE,
} EnumDMColorMatrix;

//--------------------------------------------------
// Definitions of HDR Dark Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_DARK_ENHANCE_OFF,
    _HDR10_DARK_ENHANCE_ON,
} EnumHDR10DarkEnhanceStatus;

//--------------------------------------------------
// Definitions of HDR10 Max Mastering Lv Type
//--------------------------------------------------
typedef enum
{
    _HDR10_MAX_MASTERING_LV_TYPE_540, // 540 nits
    _HDR10_MAX_MASTERING_LV_TYPE_1200, // 1200 nits, or 1000nit when _HDR10_EETF_TONEMAPPING_SUPPORT is On!!
    _HDR10_MAX_MASTERING_LV_TYPE_4000, // 4000 nits
    _HDR10_MAX_MASTERING_LV_TYPE_10000, // 10000 nits
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
    _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM,
#endif
    _HDR10_MAX_MASTERING_LV_TYPE_NOTM, // Tone Mapping by source based on peak lv
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
    _HDR10_MAX_MASTERING_LV_TYPE_NOTM_FRAME_AVERAGE_LV, // Tone Mapping by source based on frame average lv
    _HDR10_MAX_MASTERING_LV_TYPE_NOTM_USER_DEFINE_LV, // Tone Mapping by source based on User Define lv
#endif
} EnumHDR10MaxMasteringLvType;

//--------------------------------------------------
// Definitions of HDR10 Fixed Point Tone Mapping
//--------------------------------------------------
typedef enum
{
    _HDR10_FIXED_POINT_TM_OFF,
    _HDR10_FIXED_POINT_TM_ON,
#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
    _HDR10_FIXED_POINT_TM_USER,
#endif
} EnumHDR10FixedPointToneMappingStatus;

//--------------------------------------------------
// Definitions of HDR10 Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_MODE_OFF,
    _HDR10_MODE_AUTO,
    _HDR10_MODE_FORCE_2084,
    _HDR10_HLG_MODE_AUTO,
    _HDR10_HLG_MODE_FORCE_HLG,
}EnumHDR10ModeDef;

//--------------------------------------------------
// Definitions of HDR10 SBTM Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_MODE_OFF,
    _HDR10_SBTM_MODE_G_RDM,
    _HDR10_SBTM_MODE_D_RDM,
} EnumHDR10SBTMMode;

//--------------------------------------------------
// Definitions of HDR10 SBTM GRDM Lum Max Type
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_GRDM_LV_TYPE_OFF,
    _HDR10_SBTM_GRDM_LV_TYPE_300,
    _HDR10_SBTM_GRDM_LV_TYPE_1000,
} EnumHDR10SBTMGRDMLumMaxType;

//--------------------------------------------------
// Definitions of HDR10 SBTM GRDM Min Type
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_GRDM_MIN_OFF,
    _HDR10_SBTM_GRDM_MIN_LV_0_0,
    _HDR10_SBTM_GRDM_MIN_LV_0_1,
} EnumHDR10SBTMGRDMMinType;

//--------------------------------------------------
// Definitions of HDR10 SBTM Type
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_TYPE_OFF,
    _HDR10_SBTM_TYPE_GRAPHICS_OVERLAY,
    _HDR10_SBTM_TYPE_GAME_COMPUTER,
    _HDR10_SBTM_TYPE_VIDEO_MOVIE,
} EnumHDR10SBTMType;

//--------------------------------------------------
// Enumerations of SRGB Options
//--------------------------------------------------
typedef enum
{
    _SRGB_BYPASS = 0,
    _SRGB_HALF,
} EnumSrgbBypassLut;

typedef enum
{
    _SRGB_1_BIT_SHIFT_LEFT,
    _SRGB_2_BIT_SHIFT_LEFT,
    _SRGB_3_BIT_SHIFT_LEFT,
    _SRGB_0_BIT_SHIFT_LEFT,
}EnumSrgbPrecision;

//--------------------------------------------------
// Enumerations of Uniformity Mode Select
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_OGC_MODE = 0,
    _UNIFORMITY_PCM_MODE,
} EnumUniformityModeSelect;

//--------------------------------------------------
// Enumerations of Uniformity Mode Select
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_1LEVEL_MODE = 1,
    _UNIFORMITY_4LEVEL_MODE = 4,
    _UNIFORMITY_5LEVEL_MODE = 5,
} EnumUniformityLevelSelect;

//--------------------------------------------------
// Enumerations of Uniformity Mode
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_OFF,
    _UNIFORMITY_PCM,
    _UNIFORMITY_OGC,
    _UNIFORMITY_USER,
} EnumUniformityMode;

//--------------------------------------------------
// Enumerations of Local dimming
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_DISABLE,
    _LOCAL_DIMMING_ENABLE,
} EnumLocalDimmingStatus;

//--------------------------------------------------
// Enumerations of Gamma Channel
//--------------------------------------------------
typedef enum
{
    _GAMMA_RED_CHANNEL,
    _GAMMA_GREEN_CHANNEL,
    _GAMMA_BLUE_CHANNEL,
} EnumGammaChannel;

//--------------------------------------------------
// Enumerations of OGC Options
//--------------------------------------------------
typedef enum
{
    _OGC_MODE1,
    _OGC_MODE2,
    _OGC_MODE3,
    _OGC_MODE4,
    _OGC_MODE5,
    _OGC_MODE6,
    _OGC_OFF,
} EnumOGCType;

//--------------------------------------------------
// Enumerations of PCM Gamma Options
//--------------------------------------------------
typedef enum
{
    _OCC_PCM_GAMMA_05,
    _OCC_PCM_GAMMA_06,
    _OCC_PCM_GAMMA_07,
    _OCC_PCM_GAMMA_08,
    _OCC_PCM_GAMMA_09,
    _OCC_PCM_GAMMA_10,
    _OCC_PCM_GAMMA_11,
    _OCC_PCM_GAMMA_12,
    _OCC_PCM_GAMMA_13,
    _OCC_PCM_GAMMA_14,
    _OCC_PCM_GAMMA_15,
    _OCC_PCM_GAMMA_16,
    _OCC_PCM_GAMMA_17,
    _OCC_PCM_GAMMA_18,
    _OCC_PCM_GAMMA_19,
    _OCC_PCM_GAMMA_20,
    _OCC_PCM_GAMMA_21,
    _OCC_PCM_GAMMA_22,
    _OCC_PCM_GAMMA_23,
    _OCC_PCM_GAMMA_24,
    _OCC_PCM_GAMMA_25,
    _OCC_PCM_GAMMA_26,
    _OCC_PCM_GAMMA_27,
    _OCC_PCM_GAMMA_28,
    _OCC_PCM_GAMMA_29,
    _OCC_PCM_GAMMA_30,
    _OCC_PCM_GAMMA_31,
    _OCC_PCM_GAMMA_32,
    _OCC_PCM_GAMMA_33,
    _OCC_PCM_GAMMA_34,
    _OCC_PCM_GAMMA_35,
    _OCC_PCM_GAMMA_36,
    _OCC_PCM_GAMMA_37,
    _OCC_PCM_GAMMA_38,
    _OCC_PCM_GAMMA_39,
    _OCC_PCM_GAMMA_40,
    _OCC_PCM_GAMMA_OFF,
} EnumOCCPCMGammaType;

typedef enum
{
    _OCC_PCM_GAMMA_CT_MODE1,
    _OCC_PCM_GAMMA_CT_MODE2,
    _OCC_PCM_GAMMA_CT_MODE3,
    _OCC_PCM_GAMMA_CT_MODE4,
    _OCC_PCM_GAMMA_CT_MODE5,
    _OCC_PCM_GAMMA_CT_MODE6,
    _OCC_PCM_GAMMA_CT_OFF,
} EnumOCCPCMGammaCTMatrix;

//--------------------------------------------------
// Structure of HLW
//--------------------------------------------------
typedef enum
{
    _HLW_KERNEL,
    _HLW_USER,
} EnumHLWMode;

typedef struct
{
    EnumSelRegion enumHLWKernelRegion;
    BYTE b1TopBorderEn : 1;
    BYTE b1BottomBorderEn : 1;
    BYTE b1LeftBorderEn : 1;
    BYTE b1RightBorderEn : 1;
    BYTE ucHLWRed;
    BYTE ucHLWGreen;
    BYTE ucHLWBlue;
    BYTE ucBorderWidth;
} StructHLWKernelData;

typedef struct
{
    BYTE b1TopBorderEn : 1;
    BYTE b1BottomBorderEn : 1;
    BYTE b1LeftBorderEn : 1;
    BYTE b1RightBorderEn : 1;
    WORD usHLWinHPos;
    WORD usHLWinHWidth;
    WORD usHLWinVPos;
    WORD usHLWinVHeight;
    BYTE ucHLWRed;
    BYTE ucHLWGreen;
    BYTE ucHLWBlue;
    BYTE ucBorderWidth;
} StructHLWUserData;

typedef union
{
    StructHLWKernelData stHLWKernelData;
    StructHLWUserData stHLWUserData;
} UnionHLWData;

typedef struct
{
    EnumHLWMode enumHLWMode;
    UnionHLWData unHLWData;
} StructHLWSetting;

//--------------------------------------------------
// Structure of Border Window
//--------------------------------------------------
typedef enum
{
    _BORDER_WINDOW_USER,
} EnumBorderWindowMode;

typedef struct
{
    BYTE b1TopBorderEn_Win1 : 1;
    BYTE b1BottomBorderEn_Win1 : 1;
    BYTE b1LeftBorderEn_Win1 : 1;
    BYTE b1RightBorderEn_Win1 : 1;
    WORD usHStart_Win1;
    WORD usVStart_Win1;
    WORD usHWidth_Win1;
    WORD usVHeight_Win1;
    BYTE b1TopBorderEn_Win2 : 1;
    BYTE b1BottomBorderEn_Win2 : 1;
    BYTE b1LeftBorderEn_Win2 : 1;
    BYTE b1RightBorderEn_Win2 : 1;
    WORD usHStart_Win2;
    WORD usVStart_Win2;
    WORD usHWidth_Win2;
    WORD usVHeight_Win2;
    BYTE ucBorderWinowRed;
    BYTE ucBorderWinowGreen;
    BYTE ucBorderWinowBlue;
    BYTE ucBorderWidth;
} StructBorderWindowUserData;

typedef union
{
    StructBorderWindowUserData stBorderWindowData;
} UnionBorderWindowData;

typedef struct
{
    EnumBorderWindowMode enumBorderWindowMode;
    UnionBorderWindowData unBorderWindowData;
} StructBorderWindowSetting;

//--------------------------------------------------
// Structure of Cirlce Blending
//--------------------------------------------------
typedef enum
{
    _CIRCLE_WINDOW_USER,
} EnumCircleWindowMode;

typedef struct
{
    BYTE b1CircleWindowEn : 1;
    WORD usHCenter;
    WORD usVCenter;
    WORD usHStart;
    WORD usVStart;
    WORD usBorder_HStart;
    WORD usBorder_VStart;
    BYTE ucBorderWinowRed;
    BYTE ucBorderWinowGreen;
    BYTE ucBorderWinowBlue;
    BYTE ucBorderWidth;
} StructCircleWindowUserData;

typedef union
{
    StructCircleWindowUserData stCircleWindowData;
} UnionCircleWindowData;

typedef struct
{
    EnumCircleWindowMode enumCircleWindowMode;
    UnionCircleWindowData unCircleWindowData;
} StructCircleWindowSetting;

typedef struct
{
    StructCircleWindowSetting stCircleWindowSetting;
} StructColorCircleWindowSetting;

//--------------------------------------------------
// Structure of Sharpness
//--------------------------------------------------
typedef enum
{
    _SHARPNESS_USER,
} EnumSharpnessMode;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTableH;
    BYTE *pucTableV;
} StructSharpnessUserData;

typedef union
{
    StructSharpnessUserData stSharpnessUserData;
} UnionSharpnessData;

typedef struct
{
    EnumSharpnessMode enumSharpnessMode;
    UnionSharpnessData unSharpnessData;
} StructSharpnessSetting;

//--------------------------------------------------
// Structure of ScalingDown
//--------------------------------------------------
typedef struct
{
    BYTE *pucTableSD_H;
    BYTE *pucTableSD_V;
} StructScalingDownUserData;

typedef union
{
    StructScalingDownUserData stScalingDownUserData;
} UnionScalingDownData;

typedef struct
{
    UnionScalingDownData unScalingDownData;
} StructScalingDownCoefSetting;

//--------------------------------------------------
// Structure of UltraVivid
//--------------------------------------------------
typedef enum
{
    _ULTRAVIVID_OFF,
    _ULTRAVIVID_SDR,
    _ULTRAVIVID_HDR10,
    _ULTRAVIVID_DM,
} EnumUltraVividMode;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructUltraVividSDRData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructUltraVividHDR10Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructUltraVividDMData;

typedef union
{
    StructUltraVividSDRData stUltraVividSDRData;
    StructUltraVividHDR10Data stUltraVividHDR10Data;
    StructUltraVividDMData stUltraVividDMData;
} UnionUltraVividData;

typedef struct
{
    EnumUltraVividMode enumUltraVividMode;
    UnionUltraVividData unUltraVividData;
} StructUltraVividSetting;

//--------------------------------------------------
// Structure of Local Contrast
//--------------------------------------------------
typedef enum
{
    _LOCALCONTRAST_OFF,
    _LOCALCONTRAST_HDR10_USER,
    _LOCALCONTRAST_USER,
    _LOCALCONTRAST_SDR_PLUS,
    _LOCALCONTRAST_NIGHT_SNIPER,
} EnumLocalContrastMode;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    BYTE *pucTemporalTable;
    EnumLocalContrastBlendingStatus enumLocalContrastBlendingStatus;
    BYTE ucTMFactor;
    BYTE ucYdiffgainFactor;
} StructLocalContrastUserData;

typedef struct
{
    BYTE *pucLocalContrastTable_540NIT;
    BYTE *pucLocalContrastTable_1200NIT;
    BYTE *pucLocalContrastTable_4000NIT;
    BYTE *pucLocalContrastTable_10000NIT;
} StructLocalContrastHDR10TableArray;

typedef struct
{
    BYTE ucBank;
    StructLocalContrastHDR10TableArray stLocalContrastHDR10TableArray;
    BYTE *pucTemporalTable;
    EnumLocalContrastBlendingStatus enumLocalContrastBlendingStatus;
    BYTE ucTMFactor;
    BYTE ucYdiffgainFactor;
} StructLocalContrastHDR10UserData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    BYTE *pucTemporalTable;
    EnumLocalContrastBlendingStatus enumLocalContrastBlendingStatus;
    BYTE ucTMFactor;
    BYTE ucYdiffgainFactor;
} StructLocalContrastSDRPlusData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructLocalContrastNightSniperData;

typedef union
{
    StructLocalContrastHDR10UserData stLocalContrastHDR10UserData;
    StructLocalContrastUserData stLocalContrastUserData;
    StructLocalContrastSDRPlusData stLocalContrastSDRPlusData;
    StructLocalContrastNightSniperData stLocalContrastNightSniperData;
} UnionLocalContrastData;

typedef struct
{
    EnumLocalContrastMode enumLocalContrastMode;
    UnionLocalContrastData unLocalContrastData;
} StructLocalContrastSetting;

//--------------------------------------------------
// Structure of LocalContrast Temporal Data
//--------------------------------------------------
typedef enum
{
    _LOCALCONTRAST_TEMPORAL_OFF,
    _LOCALCONTRAST_TEMPORAL_USER,
} EnumLocalContrastTemporalMode;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTemporalTable_24;
    BYTE *pucTemporalTable_60;
    BYTE *pucTemporalTable_120;
    BYTE *pucTemporalTable_144;
    BYTE *pucTemporalTable_165;
    BYTE *pucTemporalTable_240;
} StructLocalContrastTemporalUserData;

typedef union
{
    StructLocalContrastTemporalUserData stLocalContrastTemporalUserData;
} UnionLocalContrastTemporalData;

typedef struct
{
    EnumLocalContrastTemporalMode enumLocalContrastTemporalMode;
    UnionLocalContrastTemporalData unLocalContrastTemporalData;
} StructLocalContrastTemporalSetting;

//--------------------------------------------------
// Structure of DCR
//--------------------------------------------------
typedef enum
{
    _DCR_USER,
    _DCR_LOCAL_DIMMING,
    _DCR_GLOBAL_DIMMING,
}EnumDCRMode;

typedef struct
{
    EnumSelRegion enumDCRUserMeasureRegion;
    EnumDCRMeasureSel enumDCRMeasureSel;
    WORD usThreshold1;
    WORD usThreshold2;
}StructDCRLocalDimmingData;

typedef struct
{
    EnumSelRegion enumDCRUserMeasureRegion;
    EnumDCRMeasureSel enumDCRMeasureSel;
    WORD usThreshold1;
    WORD usThreshold2;
}StructDCRUserData;

typedef union
{
    StructDCRUserData stDCRUserData;
    StructDCRLocalDimmingData stDCRLocalDimmingData;
}UnionDCRData;

typedef struct
{
    EnumDCRMode enumDCRMode;
    UnionDCRData unDCRData;
}StructDCRSetting;

//--------------------------------------------------
// Structure of DCC Histogram
//--------------------------------------------------
typedef enum
{
    _DCC_HISTOGRAM_USER,
} EnumDCCHistogramMode;

typedef struct
{
    EnumSelRegion enumDCCMeasureRegion;
} StructDCCHistogramUserData;

typedef union
{
    StructDCCHistogramUserData stDCCHistogramUserData;
} UnionDCCHistogramData;

typedef struct
{
    EnumDCCHistogramMode enumDCCHistogramMode;
    UnionDCCHistogramData unDCCHistogramData;
} StructDCCHistogramSetting;

//--------------------------------------------------
// Structure of DCC
//--------------------------------------------------
typedef enum
{
    _DCC_OFF,
    _DCC_HDR10_LIGHTENHANCE,
    _DCC_HDR10_USER,
    _DCC_IAPS,
    _DCC_SDR2HDR,
    _DCC_USER,
} EnumDCCMode;

typedef struct
{
    BYTE *pucLightEnhanceTable_540NIT;
    BYTE *pucLightEnhanceTable_1200NIT;
    BYTE *pucLightEnhanceTable_4000NIT;
    BYTE *pucLightEnhanceTable_10000NIT;
} StructDCCHDR10LightEnhanceTableArray;

typedef struct
{
    EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType;
    BYTE ucBank;
    StructDCCHDR10LightEnhanceTableArray stDCCHDR10LightEnhanceTableArray;
} StructDCCHDR10LightEnhanceData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructDCCHDR10USERData;

typedef struct
{
    BYTE ucNoUserData;
} StructDCCIAPSData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructDCCSDR2HDRData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    EnumDCCAutoModeEnable enumDCCAutoModeEnable;
} StructDCCUserData;

typedef union
{
    StructDCCHDR10LightEnhanceData stDCCHDR10LightEnhanceData;
    StructDCCHDR10USERData stDCCHDR10USERData;
    StructDCCIAPSData stDCCIAPSData;
    StructDCCSDR2HDRData stDCCSDRtoHDRData;
    StructDCCUserData stDCCUserData;
} UnionDCCData;

typedef struct
{
    EnumDCCMode enumDCCMode;
    UnionDCCData unDCCData;
} StructDCCSetting;

//--------------------------------------------------
// Structure of ICM
//--------------------------------------------------
typedef enum
{
    _ICM_OFF,
    _ICM_HDR10_COLORENHANCE,
    _ICM_HDR10_USER,
    _ICM_SDR2HDR,
    _ICM_SIXCOLOR,
    _ICM_SCM,
    _ICM_USER,
    _ICM_CHAMELEON,
    _ICM_NIGHT_SNIPER,
} EnumICMMode;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructICMHDR10ColorEnhanceData;
typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructICMHDR10UserData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructICMSDR2HDRData;

typedef struct
{
    BYTE ucSixColorHueR;
    BYTE ucSixColorSaturationR;
    BYTE ucSixColorHueY;
    BYTE ucSixColorSaturationY;
    BYTE ucSixColorHueG;
    BYTE ucSixColorSaturationG;
    BYTE ucSixColorHueC;
    BYTE ucSixColorSaturationC;
    BYTE ucSixColorHueB;
    BYTE ucSixColorSaturationB;
    BYTE ucSixColorHueM;
    BYTE ucSixColorSaturationM;
} StructICMSixColorData;

typedef struct
{
    WORD usICMChameleonHue;
    BYTE ucICMChameleonSat;
    BYTE ucICMChameleonLightness;
} StructICMChameleonAxisData;

typedef struct
{
    StructICMChameleonAxisData pstAxisData[6];
    BYTE ucICMChameleonDarkOffset;
} StructICMChameleonData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucICMTable;
    BYTE *pucSCMTable;
} StructICMSCMData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructICMUserData;

typedef struct
{
    BYTE ucICMNightSniperSat;
    BYTE ucICMNightSniperLightness;
    BYTE ucICMNightSniperDarkOffset;
} StructICMNightSniperData;

typedef union
{
    StructICMHDR10ColorEnhanceData stICMHDR10ColorEnhanceData;
    StructICMHDR10UserData stICMHDR10UserData;
    StructICMSDR2HDRData stICMSDRtoHDRData;
    StructICMSixColorData stICMSixColorData;
    StructICMSCMData stICMSCMData;
    StructICMUserData stICMUserData;
    StructICMChameleonData stICMChameleonData;
    StructICMNightSniperData stICMNightSniperData;
} UnionICMData;

typedef struct
{
    EnumICMMode enumICMMode;
    UnionICMData unICMData;
} StructICMSetting;

//--------------------------------------------------
// Enumerations of Contrast Coefficient Sets
//--------------------------------------------------
typedef enum
{
    _CONTRAST_OFF,
    _CONTRAST_HDR10_USER,
    _CONTRAST_USER,
} EnumCtsMode;

typedef struct
{
    WORD pusData[3];
} StructCtsHDR10Data;

typedef struct
{
    WORD pusData[3];
} StructCtsUserData;

typedef union
{
    StructCtsHDR10Data stCtsHDR10Data;
    StructCtsUserData stCtsUserData;
} UnionCtsData;

typedef struct
{
    EnumCtsMode enumCtsMode;
    UnionCtsData unCtsData;
} StructCtsSetting;

//--------------------------------------------------
// Enumerations of Brightness Coefficient Sets
//--------------------------------------------------
typedef enum
{
    _BRIGHTNESS_OFF,
    _BRIGHTNESS_USER,
} EnumBriMode;

typedef struct
{
    WORD pusData[3];
} StructBriUserData;

typedef union
{
    StructBriUserData stBriUserData;
} UnionBriData;

typedef struct
{
    EnumBriMode enumBriMode;
    UnionBriData unBriData;
} StructBriSetting;

//--------------------------------------------------
// Structure of IAPS
//--------------------------------------------------
typedef enum
{
    _IAPS_OFF,
    _IAPS_HDR10_LIGHTENHANCE,
} EnumIAPSMode;

typedef struct
{
    BYTE ucNoUserData;
} StructIAPSHDR10LightEnhanceData;

typedef union
{
    StructIAPSHDR10LightEnhanceData stIAPSHDR10LightEnhanceData;
} UnionIAPSData;

typedef struct
{
    EnumIAPSMode enumIAPSMode;
    UnionIAPSData unIAPSData;
} StructIAPSSetting;

//--------------------------------------------------
// Structure of HDR10 Port Setting Info
//--------------------------------------------------
typedef struct
{
    EnumHDR10ModeDef enumHDR10RX0Support;
    EnumHDR10ModeDef enumHDR10RX1Support;
    EnumHDR10ModeDef enumHDR10RX2Support;
    EnumHDR10ModeDef enumHDR10RX3Support;
    EnumHDR10ModeDef enumHDR10RX4Support;
    EnumHDR10ModeDef enumHDR10RX5Support;
    EnumHDR10ModeDef enumHDR10RX6Support;
} StructHDR10PortSettingInfo;

//--------------------------------------------------
// Definitions of Advanced HDR10 Status
//--------------------------------------------------
typedef enum
{
    _ADVANCED_HDR10_OFF,
    _ADVANCED_HDR10_ON,
}EnumAdvancedHDR10Status;

typedef enum
{
    _ADVANCED_HDR10_SUPPORT_OFF,
    _ADVANCED_HDR10_SUPPORT_ON,
}EnumAdvancedHDR10Support;

//--------------------------------------------------

// Definitions of HDR10 BackLight Adaptive TM Status
//--------------------------------------------------
typedef enum
{
    _BACKLIGHT_ADAPTIVE_TM_OFF,
    _BACKLIGHT_ADAPTIVE_TM_ON,
}EnumHDR10BackLightAdaptiveTMStatus;

//--------------------------------------------------
// Definitions of HDR10 Mastering Lv StepLess TM Status
//--------------------------------------------------
typedef enum
{
    _MASTERING_LV_STEPLESS_TM_OFF,
    _MASTERING_LV_STEPLESS_TM_ON,
}EnumHDR10MasteringLvStepLessTMStatus;

//--------------------------------------------------
// Definitions of HDR10 User Force Mastering Lv Status
//--------------------------------------------------
typedef enum
{
    _USER_FORCE_MASTERING_LV_OFF,
    _USER_FORCE_MASTERING_LV_ON,
} EnumHDR10UserForceMasteringLvStatus;

//--------------------------------------------------
// Definitions of HDR10 SBTM Status
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_OFF,
    _HDR10_SBTM_ON,
} EnumHDR10SBTMStatus;

//--------------------------------------------------
// Structure of 3D Gamma
//--------------------------------------------------
typedef enum
{
    _OCC_RGB_3D_GAMMA_TYPE1 = 0,  // table 1
    _OCC_RGB_3D_GAMMA_TYPE2,      // table 2
    _OCC_RGB_3D_GAMMA_TYPE3,      // table 3
    _OCC_RGB_3D_GAMMA_TYPE4,      // table 4
    _OCC_RGB_3D_GAMMA_TYPE5,      // table 5
    _OCC_RGB_3D_GAMMA_TYPE6,      // table 6
} Enum3DGammaTypeSelect;

typedef enum
{
    _3DGAMMA_OFF,
    _3DGAMMA_ADVANCED_HDR10,
    _3DGAMMA_USER,
    _3DGAMMA_GAMUT_COMPRESSION,
    _3DGAMMA_HDR10_REMAP,
    _3DGAMMA_CUBE_MAPPING,
} Enum3DGammaMode;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} Struct3DGammaUserData;

typedef struct
{
    BYTE ucNoUserData;
} Struct3DGammaAdvancedHDR10Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} Struct3DGammaGamutCompressionData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} Struct3DGammaHDR10RemapData;

typedef struct
{
    Enum3DGammaTypeSelect enumTypeSelect;
    BYTE ucBank;
    BYTE *pucTable;
} Struct3DGammaCubeMappingData;

typedef union
{
    Struct3DGammaUserData st3DGammaUserData;
    Struct3DGammaAdvancedHDR10Data st3DGammaAdvancedHDR10Data;
    Struct3DGammaGamutCompressionData st3DGammaGamutCompressionData;
    Struct3DGammaHDR10RemapData st3DGammaHDR10RemapData;
    Struct3DGammaCubeMappingData st3DGammaCubeMappingData;
} Union3DGammaData;

typedef struct
{
    Enum3DGammaMode enum3DGammaMode;
    Union3DGammaData unOutGammaData;
} Struct3DGammaSetting;

//--------------------------------------------------
// Structure of Input Gamma
//--------------------------------------------------
typedef enum
{
    _INGAMMA_OFF,
    _INGAMMA_PCM,
    _INGAMMA_HDR10_AUTO,
    _INGAMMA_HLG,
    _INGAMMA_HDR10_FORCE_2084,
    _INGAMMA_HDR10_USER,
    _INGAMMA_ADVANCED_HDR10,
    _INGAMMA_SDRTOHDR,
    _INGAMMA_FREESYNC2,
    _INGAMMA_OGC,
    _INGAMMA_PCM_USER,
    _INGAMMA_OCC_PCM_GAMMA,
    _INGAMMA_FREESYNC2_USER,
    _INGAMMA_DM,
    _INGAMMA_HDR10_SBTM,
} EnumInGammaMode;

typedef struct
{
    EnumPCMType enumPCMMode;
} StructInGammaPCMData;

typedef struct
{
    EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus;
    EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus;
} StructInGammaHDR10AutoData;

typedef struct
{
    BYTE ucNoUserData;
} StructInGammaHLGData;

typedef struct
{
    EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus;
    EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus;
} StructInGammaHDR10Force2084Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    EnumPCMNodeType enumPCMNodeType;
} StructInGammaHDR10UserData;

typedef struct
{
    BYTE ucNoUserData;
} StructInGammaAdvancedHDR10Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructInGammaSDRToHDRData;

typedef struct
{
    BYTE ucNoUserData;
} StructInGammaFreeSync2Data;

typedef struct
{
    EnumOGCType enumOGCType;
} StructInGammaOGCData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    EnumPCMNodeType enumPCMNodeType;
} StructInGammaPCMUserData;

typedef struct
{
    EnumOCCPCMGammaType enumOCCPCMGammaType;
} StructInGammaOCCPCMGammaData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    EnumPCMNodeType enumPCMNodeType;
} StructInGammaFreeSync2UserData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructInGammaDMData;

typedef struct
{
    EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus;
    EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus;
} StructInGammaSBTMData;


typedef union
{
    StructInGammaPCMData stInGammaPCMData;
    StructInGammaHDR10AutoData stInGammaHDR10AutoData;
    StructInGammaHLGData stInGammaHLGData;
    StructInGammaHDR10Force2084Data stInGammaHDR10Force2084Data;
    StructInGammaHDR10UserData stInGammaHDR10UserData;
    StructInGammaAdvancedHDR10Data stInGammaAdvancedHDR10Data;
    StructInGammaSDRToHDRData stInGammaSDRtoHDRData;
    StructInGammaFreeSync2Data stInGammaFreeSync2Data;
    StructInGammaOGCData stInGammaOGCData;
    StructInGammaPCMUserData stInGammaPCMUserData;
    StructInGammaOCCPCMGammaData stInGammaOCCPCMGammaData;
    StructInGammaFreeSync2UserData stInGammaFreeSync2UserData;
    StructInGammaDMData stInGammaDMData;
    StructInGammaSBTMData stInGammaSBTMData;
} UnionInGammaData;

typedef struct
{
    EnumInGammaMode enumInGammaMode;
    UnionInGammaData unInGammaData;
} StructInGammaSetting;

//--------------------------------------------------
// Structure of HDR
//--------------------------------------------------
//--------------------------------------------------
// Definitions of HDR Target Status
//--------------------------------------------------
typedef enum
{
    _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR,
    _HDR_TARGET_STATUS_SMPTE_ST_2084,
    _HDR_TARGET_STATUS_FORCE_2084,
    _HDR_TARGET_STATUS_AUTO_HLG,
    _HDR_TARGET_STATUS_FORCE_HLG,
    _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR,
    _HDR_TARGET_STATUS_ADVANCED_HDR10,
    _HDR_TARGET_STATUS_DM,
    _HDR_TARGET_STATUS_DM_GAME,
    _HDR_TARGET_STATUS_SBTM,
} EnumHDRTargetStatus;

//--------------------------------------------------
// Definitions of HDR10 User Define Max Panel Lv
//--------------------------------------------------
typedef enum
{
    _HDR10_PANEL_MAX_PEAK_LV,
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
    _HDR10_PANEL_MAX_FRAME_AVERAGE_LV,
    _HDR10_PANEL_MAX_USER_DEFINE_LV,
#endif
} EnumHDR10UserDefineMaxPanelLvType;

typedef struct
{
    EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLv0Type;
    EnumHDR10MaxMasteringLvType enumHDR10Force2084MasteringLvType;
    EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType;
    EnumHDR10MaxMasteringLvType enumHDR10UserForceMaxMasteringLvType;
    EnumHDR10MasteringLvStepLessTMStatus enumHDR10MasteringLvStepLessTMStatus;
    EnumHDR10UserForceMasteringLvStatus enumHDR10UserForceMasteringLvStatus;
    WORD usHDR10StepLessMaxMasteringLv0;
    WORD usHDR10StepLessForce2084MasteringLv;
} StructHDR10UserData;

//--------------------------------------------------
// Structure of Ymapping
//--------------------------------------------------
typedef enum
{
    _HLG_OOTF_STANDARD_MODE,
    _HLG_OOTF_USER_MODE_1,
    _HLG_OOTF_USER_MODE_2,
    _HLG_OOTF_USER_MODE_3,
} EnumHLGOOTFType;

typedef enum
{
    _YMAPPING_OFF,
    _YMAPPING_HLG,
    _YMAPPING_ADVANCED_HDR10,
    _YMAPPING_HDR10_BACKLIGHT_ADAPTIVE_TM,
} EnumYmappingMode;

typedef struct
{
    EnumHLGOOTFType enumHLGOOTFType;
    BYTE ucBank;
    BYTE *pucTable;
} StructYmappingHLGData;

typedef struct
{
    BYTE ucNoUserData;
} StructYmappingAdvancedHDR10Data;

typedef struct
{
    WORD usBackLight;
    WORD usBackLightMax;
    EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus;
    EnumHDR10ColorMatrix enumHDR10ColorMatrix;
} StructYmappingHDR10BackLightAdaptiveTMData;

typedef union
{
    StructYmappingHLGData stYmappingHLGData;
    StructYmappingAdvancedHDR10Data stYmappingAdvancedHDR10Data;
    StructYmappingHDR10BackLightAdaptiveTMData stYmappingHDR10BackLightAdaptiveTMData;
} UnionYmappingData;

typedef struct
{
    EnumYmappingMode enumYmappingMode;
    UnionYmappingData unYmappingData;
} StructYmappingSetting;

//--------------------------------------------------
// Structure of sRGB
//--------------------------------------------------
typedef enum
{
    _SRGB_OFF,
    _SRGB_HUESAT,
    _SRGB_PCM,
    _SRGB_HDR10_AUTO,
    _SRGB_HLG_AUTO,
    _SRGB_HDR10_FORCE_2084,
    _SRGB_HDR10_USER,
    _SRGB_HLG_FORCE,
    _SRGB_ADVANCED_HDR10,
    _SRGB_SDRTOHDR,
    _SRGB_FREESYNC2,
    _SRGB_PCM_USER,
    _SRGB_OCC_PCM_GAMMA,
    _SRGB_DM,
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
    _SRGB_PCM_USER_CCT,
#endif
    _SRGB_HDR10_SBTM,
} EnumSRGBMode;

typedef struct
{
    SWORD shHue;
    WORD  usSat;
} StructSRGBHueSatData;

typedef enum
{
    _OGC_NORMAL_TYPE = 0,
    _OGC_MAX_BACKLIGHT_TYPE,
    _OGC_MULTI_BACKLIGHT_3_TYPE,
    _OGC_MULTI_BACKLIGHT_4_TYPE,
} EnumOGCModeSelect;

typedef struct
{
    EnumPCMType enumPCMMode;
    EnumOGCModeSelect enumOGCModeSelect;
} StructSRGBPCMData;

typedef struct
{
    EnumHDR10ColorMatrix enumHDR10ColorMatrix;
} StructSRGBHDR10AutoData;

typedef struct
{
    BYTE ucNoUserData;
} StructSRGBHLGAutoData;

typedef struct
{
    EnumHDR10ColorMatrix enumHDR10ColorMatrix;
} StructSRGBHDR10Force2084Data;

typedef struct
{
    EnumHDR10ColorMatrix enumHLGColorMatrix;
} StructSRGBHLGForceData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructSRGBHDR10UserData;

typedef struct
{
    BYTE ucNoUserData;
} StructSRGBAdvancedHDR10Data;

typedef struct
{
    BYTE ucNoUserData;
} StructSRGBSDRToHDRData;

typedef struct
{
    BYTE ucNoUserData;
} StructSRGBFreeSync2Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    EnumSrgbPrecision enumSrgbPrecision;
} StructSRGBPCMUserData;

#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
typedef struct
{
    EnumPCMType enumPCMMode;
    EnumOGCModeSelect enumOGCModeSelect;
    WORD pusTable[_COLORIMETRY_TRANSFER_MATRIX_SIZE];
} StructSRGBColorTransferUserData;
#endif

typedef struct
{
    EnumOCCPCMGammaCTMatrix enumOCCPCMGammaCTMatrix;
    EnumOGCModeSelect enumOGCModeSelect;
} StructSRGBOCCPCMGammaData;

typedef struct
{
    EnumDMColorMatrix enumDMColorMatrix;
} StructSRGBDMData;

typedef struct
{
    EnumHDR10SBTMColorMatrix enumHDR10SBTMColorMatrix;
} StructSRGBHDR10SBTMData;

typedef union
{
    StructSRGBHueSatData stSRGBHueSatData;
    StructSRGBPCMData stSRGBPCMData;
    StructSRGBHDR10AutoData stSRGBHDR10AutoData;
    StructSRGBHLGAutoData stSRGBHLGAutoData;
    StructSRGBHDR10Force2084Data stSRGBHDR10Force2084Data;
    StructSRGBHLGForceData stSRGBHLGForceData;
    StructSRGBHDR10UserData stSRGBHDR10UserData;
    StructSRGBAdvancedHDR10Data stSRGBAdvancedHDR10Data;
    StructSRGBSDRToHDRData stSRGBSDRtoHDRData;
    StructSRGBFreeSync2Data stSRGBFreeSync2Data;
    StructSRGBPCMUserData stSRGBPCMUserData;
    StructSRGBOCCPCMGammaData stSRGBOCCPCMGammaData;
    StructSRGBDMData stSRGBDMData;
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
    StructSRGBColorTransferUserData stSRGBColorTransferUserData;
#endif
    StructSRGBHDR10SBTMData stSRGBHDR10SBTMData;
} UnionSRGBData;

typedef struct
{
    EnumSRGBMode enumSRGBMode;
    UnionSRGBData unSRGBData;
} StructSRGBSetting;

//--------------------------------------------------
// Structure of color convert
//--------------------------------------------------
typedef enum
{
    _D_COLOR_CONVERT_STANDARD,
    _D_COLOR_CONVERT_HUE_SATURATION,
} EnumDColorConvertMode;

typedef struct
{
    SWORD shHue;
    WORD  usSat;
} StructDColorConvertHueSatData;

typedef union
{
    StructDColorConvertHueSatData stDColorConvertHueSatData;
} UnionDColorConvertData;

typedef struct
{
    EnumDColorConvertMode enumDColorConvertMode;
    UnionDColorConvertData unDColorConvertData;
} StructDColorConvertSetting;

//--------------------------------------------------
// Structure of Local Dimming
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_OFF,
    _LOCAL_DIMMING_ON,
} EnumLocalDimmingMode;

typedef enum
{
    _LOCAL_DIMMING_DISPLAYHDR,
    _LOCAL_DIMMING_USER,
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
    _LOCAL_DIMMING_ENERGYSAVER,
#endif
} EnumLocalDimmingCase;

typedef enum
{
    _EXTRO_INFO_Y_AVG,
    _EXTRO_INFO_Y_MAX,
    _EXTRO_INFO_Y_MIN,
    _EXTRO_INFO_BIN0PER,
    _EXTRO_INFO_PERTILE,
} EnumExtroInfo;

typedef struct
{
    BYTE b1OSDCurrentPWMEnable : 1;
    BYTE b1TotalWorBOneStep : 1;
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    BYTE b1BoostContrastModeEnable : 1;
    WORD usRegionBoostAdimStep;
    WORD usRegionBoostGainStep;
#endif
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
    WORD usPictureBlackTH;
#endif
    WORD usPictureBNWTH;
    BYTE ucSmoothLevel;
    BYTE ucStepChangeLevel;
    BYTE ucOSDStepChangeLevel;
    EnumLocalDimmingCase enumLocalDimmingCase;
    BYTE ucLocalDimmingSmoothParaSel;
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
    WORD usMinBlendPWMValue;
#endif
#if(_LOCAL_DIMMING_USING_YAVG_INFO)
    // for LD using Yavg information
    WORD usAvgStepFrac; // 0~ 1024
    WORD usPercentileStepFrac; // 0~ 1024
    WORD usAvgBlackValue; // 0~ 4095
    WORD usAvgBlackStep; // 0~ 1024
#endif
#if(_LOCAL_DIMMING_USING_EXTRO_INFO == _ON)
    EnumExtroInfo enumExtroInfo0;
    EnumExtroInfo enumExtroInfo1;
#endif
}StructLocalDimmingData;

typedef union
{
    StructLocalDimmingData stLocalDimmingData;
} UnionLocalDimmingData;

typedef struct
{
    EnumLocalDimmingMode enumLocalDimmingMode;
    UnionLocalDimmingData unLocalDimmingData;
} StructLocalDimmingSetting;

typedef enum
{
    _UPD_SYNC_BY_LOCAL_DIMMING_GAIN_SYNC = 2,
    _UPD_SYNC_BY_MANUAL = 3,
} EnumUpdSyncTriggerSrc;

typedef enum
{
    _NO_LEFT_SHIFT = 0,
    _LEFT_SHIFT_1BIT,
    _LEFT_SHIFT_2BITS,
    _LEFT_SHIFT_3BITS,
    _LEFT_SHIFT_4BITS,
} EnumPwmDataLeftShift;
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _ON)
//--------------------------------------------------
// Structure of Local dimming Multi BL Model Table
//--------------------------------------------------
typedef struct
{
    BYTE ucTableBank;

    BYTE *pucLvMaxTableAddress;
    WORD usLvMaxTableLength;

    BYTE *pucPWMGainTableAddress;
    WORD usPWMGainTableLength;

    BYTE *pucLVGainTableAddress;
    WORD usLVGainTableLength;

    BYTE *pucLVLUTTableAddress;
    WORD usLVLUTTableLength;

    BYTE *pucLedSettingTableAddress;
    WORD usLedSettingTableLength;
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
    BYTE *pucS1CurveTableAddress;
    WORD usS1CurveTableLength;

    BYTE *pucS2CurveTableAddress;
    WORD usS2CurveTableLength;
#endif
}StructLocalDimmingMultiBLModelTable;
#endif

//--------------------------------------------------
// Structure of Panel Uniformity
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_TYPE2,      // gamma 2.0
    _UNIFORMITY_TYPE3,      // gamma 2.2
    _UNIFORMITY_TYPE4,      // gamma 2.4
    _UNIFORMITY_TYPE5,      // srgb
    _UNIFORMITY_TYPE6,      // adobe rgb
    _UNIFORMITY_TYPE7,      //
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    _UNIFORMITY_PLUSMODE_NATIVE = (_UNIFORMITY_TOTAL_SET - 2), // native
    _UNIFORMITY_PLUSMODE_PCM, // OG1.0
#endif
} EnumUniformityTypeSelect;

typedef struct
{
    EnumUniformityTypeSelect enumUniformityType;
    BYTE b1UniformityOffsetEnable : 1;
} StructUniformityPCMData;

typedef struct
{
    EnumUniformityTypeSelect enumUniformityType;
    BYTE b1UniformityOffsetEnable : 1;
} StructUniformityOGCData;

typedef struct
{
    EnumPCMType enumPCMMode;
} StructUniformityLDPCMData;

typedef struct
{
    EnumOGCType enumOGCType;
} StructUniformityLDOGCData;

typedef struct
{
    BYTE ucNoUserData;
} StructUniformityLDHDR10Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
    BYTE ucDecayBank;
    BYTE *pucDecayTable;
    BYTE ucOffsetBank;
    BYTE *pucOffsetTable;
    BYTE b1UniformityOffsetEnable : 1;
    EnumUniformityModeSelect enumUniformityMode;
    EnumUniformityLevelSelect enumUniformityLevel;
} StructUniformityUserData;

typedef union
{
    StructUniformityPCMData stUniformityPCMData;
    StructUniformityOGCData stUniformityOGCData;
    StructUniformityLDPCMData stUniformityLDPCMData;
    StructUniformityLDOGCData stUniformityLDOGCData;
    StructUniformityLDHDR10Data stUniformityLDHDR10Data;
    StructUniformityUserData stUniformityIUserData;
} UnionUniformityData;

typedef struct
{
    EnumUniformityMode enumUniformityMode;
    UnionUniformityData unUniformityData;
} StructUniformitySetting;

//--------------------------------------------------
// Structure of Output Gamma
//--------------------------------------------------
typedef enum
{
    _OUTGAMMA_OFF,
    _OUTGAMMA_OGC,
    _OUTGAMMA_PCM,
    _OUTGAMMA_HDR10,
    _OUTGAMMA_HLG,
    _OUTGAMMA_HDR10_USER,
    _OUTGAMMA_ADVANCED_HDR10,
    _OUTGAMMA_SDRTOHDR,
    _OUTGAMMA_FREESYNC2,
    _OUTGAMMA_USER_RGBGAMMA,
    _OUTGAMMA_PCM_USER,
    _OUTGAMMA_USER,
    _OUTGAMMA_DICOM,
    _OUTGAMMA_OCC_PCM_GAMMA,
    _OUTGAMMA_FREESYNC2_USER,
    _OUTGAMMA_DM,
    _OUTGAMMA_CUBE_MAPPING,
} EnumOutGammaMode;

typedef enum
{
    _OGC_GAMMA1_TYPE = 0,
    _OGC_GAMMA2_TYPE,
    _OGC_GAMMA3_TYPE,
    _OGC_GAMMA4_TYPE,
    _OGC_GAMMA5_TYPE,
    _OGC_GAMMA6_TYPE,
    _OGC_TOTAL_GAMMA_TYPE,
} EnumOGCTypeSelect;

typedef enum
{
    _GAMMA1_OCC_NORMAL = 0,
    _GAMMA1_HDR,
    _GAMMA1_OCC_MAX_BRI,
    _GAMMA1_GLOBAL_DIMMING,
    _GAMMA1_FS2,
    _GAMMA1_OCC_MULTI_BRI_3,
    _GAMMA1_OCC_MULTI_BRI_4,
} EnumOCCGamma1Type;

typedef enum
{
    _DICOM1_TYPE = 0,
    _DICOM2_TYPE,
    _DICOM3_TYPE,
    _DICOM4_TYPE,
    _OGC_TOTAL_DICOM_TYPE,
} EnumDICOMTypeSelect;

typedef enum
{
    _OGC_UNI_PLUS_FUNCTION_OFF = 0,
    _OGC_UNI_PLUS_FUNCTION_ON,
} EnumOGCUniformityPlusFunction;

typedef struct
{
    EnumOGCType enumOGCType;
    EnumOGCTypeSelect enumOGCTypeSelect;
    EnumOGCModeSelect enumOGCModeSelect;
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
    EnumOGCUniformityPlusFunction enumOGCUniformityPlusFunction;
#endif
} StructOutGammaOGCData;

typedef struct
{
    EnumPCMType enumPCMMode;
    EnumOGCModeSelect enumOGCModeSelect;
} StructOutGammaPCMData;

typedef struct
{
    BYTE ucNoUserData;
} StructOutGammaHDR10Data;

typedef struct
{
    BYTE ucNoUserData;
} StructOutGammaHLGData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructOutGammaHDR10UserData;

typedef struct
{
    BYTE ucNoUserData;
} StructOutGammaAdvancedHDR10Data;

typedef struct
{
    EnumOGCModeSelect enumOGCModeSelect;
} StructOutGammaSDRToHDRData;

typedef struct
{
    BYTE ucNoUserData;
} StructOutGammaFreeSync2Data;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructOutGammaPCMUserData;

typedef struct
{
    BYTE ucBank_WhiteGamma;
    BYTE *pucTable_WhiteGamma;
    BYTE ucBank_RGBGamma;
    BYTE *pucTable_RGBGamma;
} StructOutGammaUserRGBGammaData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructOutGammaUserData;

typedef struct
{
    EnumDICOMTypeSelect enumDICOMTypeSelect;
    BYTE ucBank;
    BYTE *pucTable;
} StructOutGammaDICOMData;

typedef struct
{
    EnumOGCModeSelect enumOGCModeSelect;
} StructOutGammaOCCPCMGammaData;

typedef struct
{
    BYTE ucBank;
    BYTE *pucTable;
} StructOutGammaFreeSync2UserData;

typedef struct
{
    Enum3DGammaTypeSelect enumTypeSelect;
    BYTE ucBank;
    BYTE *pucTable;
} StructOutGammaCubeMappingData;

typedef union
{
    StructOutGammaOGCData stOutGammaOGCData;
    StructOutGammaPCMData stOutGammaPCMData;
    StructOutGammaHDR10Data stOutGammaHDR10Data;
    StructOutGammaHLGData stOutGammaHLGData;
    StructOutGammaHDR10UserData stOutGammaHDR10UserData;
    StructOutGammaAdvancedHDR10Data stOutGammaAdvancedHDR10Data;
    StructOutGammaSDRToHDRData stOutGammaSDRtoHDRData;
    StructOutGammaFreeSync2Data stOutGammaFreeSync2Data;
    StructOutGammaUserRGBGammaData stOutGammaUserRGBGammaData;
    StructOutGammaPCMUserData stOutGammaPCMUserData;
    StructOutGammaUserData stOutGammaUserData;
    StructOutGammaDICOMData stOutGammaDICOMData;
    StructOutGammaOCCPCMGammaData stOutGammaOCCPCMGammaData;
    StructOutGammaFreeSync2UserData stOutGammaFreeSync2UserData;
    StructOutGammaCubeMappingData stOutGammaCubeMappingData;
} UnionOutGammaData;

typedef struct
{
    EnumOutGammaMode enumOutGammaMode;
    UnionOutGammaData unOutGammaData;
} StructOutGammaSetting;

//--------------------------------------------------
// Structure of Post Gamma
//--------------------------------------------------
typedef enum
{
    _POSTGAMMA_OFF,
    _POSTGAMMA_OGC,
    _POSTGAMMA_PCM_USER,
    _POSTGAMMA_USER,
} EnumPostGammaMode;

typedef union
{
    StructOutGammaOGCData stPostGammaOGCData;
    StructOutGammaPCMUserData stPostGammaPCMUserData;
    StructOutGammaUserData stPostGammaUserData;
} UnionPostGammaData;

typedef struct
{
    EnumPostGammaMode enumPostGammaMode;
    UnionPostGammaData unPostGammaData;
} StructPostGammaSetting;

//--------------------------------------------------
// Enumerations of PCM calibrated by OCC/OGC
//--------------------------------------------------
typedef enum
{
    _SDR_CALIBRATION_BY_OGC_TOOL,
    _SDR_NONE_CALIBRATION_BY_OGC_TOOL,
} EnumSDRCalibrationType;

//--------------------------------------------------
// Enumerations of Local Dimming Type
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_SDR,
    _LOCAL_DIMMING_HDR,
} EnumLocalDimmingType;

//--------------------------------------------------
// Enumerations of MRCM
//--------------------------------------------------
typedef enum
{
    _MRCM_OFF,
    _MRCM_ON,

}EnumMRCMCase;

typedef enum
{
    _MRCM_THD1,
    _MRCM_THD2,
}EnumMRCMThdType;

typedef enum
{
    _MRCM_SET_0 = 0x00,
    _MRCM_SET_1,
    _MRCM_SET_2,
    _MRCM_SET_3,
    _MRCM_SET_4,
    _MRCM_SET_5,
    _MRCM_SET_NONE = 0xFF,
}EnumMRCMSet;

typedef enum
{
    _MRCM_ABOVE_TH1_NUM_R,
    _MRCM_ABOVE_TH1_VAL_R,
    _MRCM_ABOVE_TH1_NUM_G,
    _MRCM_ABOVE_TH1_VAL_G,
    _MRCM_ABOVE_TH1_NUM_B,
    _MRCM_ABOVE_TH1_VAL_B,
    _MRCM_ABOVE_TH1_NUM_RGB,
    _MRCM_ABOVE_TH1_VAL_RGB,
    _MRCM_ABOVE_TH2_NUM_R,
    _MRCM_ABOVE_TH2_VAL_R,
    _MRCM_ABOVE_TH2_NUM_G,
    _MRCM_ABOVE_TH2_VAL_G,
    _MRCM_ABOVE_TH2_NUM_B,
    _MRCM_ABOVE_TH2_VAL_B,
    _MRCM_ABOVE_TH2_NUM_RGB,
    _MRCM_ABOVE_TH2_VAL_RGB,
    _MRCM_ABOVE_MAX_CODE_R,
    _MRCM_ABOVE_MIN_CODE_R,
    _MRCM_ABOVE_MAX_CODE_G,
    _MRCM_ABOVE_MIN_CODE_G,
    _MRCM_ABOVE_MAX_CODE_B,
    _MRCM_ABOVE_MIN_CODE_B,
    _MRCM_ABOVE_MAX_CODE_RGB,
    _MRCM_ABOVE_MIN_CODE_RGB,
} EnumMRCMReadResultOption;

//--------------------------------------------------
// Structure of MRCM
//--------------------------------------------------
typedef struct
{
    BYTE ucv_num;
    BYTE uch_num;
    WORD usstart_pixel_v;
    WORD usstart_pixel_h;
    WORD usend_pixel_v;
    WORD usend_pixel_h;
    WORD usv_step;
    WORD ush_step;
    WORD ush_offset_l;
    WORD ush_offset_r;
    WORD usv_offset_t;
    WORD usv_offset_b;
    WORD usg_thd1;
    WORD usb_thd1;
    WORD usr_thd1;
    WORD usrgb_thd1;
    WORD usg_thd2;
    WORD usb_thd2;
    WORD usr_thd2;
    WORD usrgb_thd2;
    BYTE ucbg_g_value;
    BYTE ucbg_b_value;
    BYTE ucbg_r_value;
} StructMRCMData;

typedef struct
{
    BYTE ucMRCMLoopNum;
    StructMRCMData pstMRCMData[_MRCM_SETTING_NUM];
} StructMRCMLoopData;

typedef struct
{
    StructMRCMLoopData stMRCMLoopUserData;
    StructMRCMLoopData stMRCMLoopKernelData;
} StructMRCMSettingData;

typedef struct
{
    EnumMRCMCase enumMRCMCase;
    StructMRCMSettingData stMRCMSettingData;
} StructMRCMSetting;

typedef struct
{
    QWORD uqRedVal;
    QWORD uqGreenVal;
    QWORD uqBlueVal;
    DWORD ulRedNum;
    DWORD ulGreenNum;
    DWORD ulBlueNum;
} StructMRCMRGBResult;

//--------------------------------------------------
// Structure of Anti-Aliasing
//--------------------------------------------------
typedef struct
{
    BYTE ucMode;
    BYTE ucLevel;
    DWORD *pulTable;
} StructAntiAliasingUserData;

typedef struct
{
    bit bVsdEn;
    bit bDrrFlag;
    WORD usHTotal;
    WORD usHWidth;
    WORD usHSyncWidth;
    WORD usVHeight;
} StructAntiAliasingOnSpecKernelData;

typedef struct
{
    StructAntiAliasingUserData stAntiAliasingUserData;
    StructAntiAliasingOnSpecKernelData stAntiAliasingOnSpecKernelData;
} StructAntiAliasingSetting;

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
typedef enum
{
    _LOWBLUE_MODE_OFF = 0,
    _LOWBLUE_MODE_ADAPTIVE,
    _LOWBLUE_MODE_GLOBAL,
    _LOWBLUE_MODE_STATIC_GLOBAL,
}EnumDynamicLowBlueType;

typedef enum
{
    _EYE_PROTECT_LEVEL0,
    _EYE_PROTECT_LEVEL1,
    _EYE_PROTECT_LEVEL2,
    _EYE_PROTECT_LEVEL3,
}EnumEyeProtectLevel;

typedef struct
{
    EnumEyeProtectLevel enumEyeProtectLevel;
    BYTE *pucParaSetting;
    BYTE *pucBlurMatrix;
    BYTE ucBank;
    bit bNightModeEnable;
    BYTE ucNightModeGainPercent; // 0 - 100
} StructColorLowBlueUserSetting;

typedef struct
{
    EnumDynamicLowBlueType enumDynamicLowBlueType;
    StructColorLowBlueUserSetting stColorLowBlueUserSetting;
} StructColorEyeProtectSetting;
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_COLOR_IP_LOCAL_DIMMING == _ON)
#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _ON)
extern StructLocalDimmingMultiBLModelTable g_stColorLocalDimmingMultiTable;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

