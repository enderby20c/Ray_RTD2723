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
// ID Code      : UserCommonColorCalibrationInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#define GET_ON_LINE_CALIBRATION_STATUS()               (g_stColorCalibrationInfo.b1CalibrationActiveMode)
#define SET_ON_LINE_CALIBRATION_STATUS(x)              {g_stColorCalibrationInfo.b1CalibrationActiveMode = (x);}
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
#define GET_ON_LINE_GD_HDR_CALIBRATION_STATUS()        (g_stColorCalibrationInfo.b1CalibrationGDActiveHDRMode)
#define SET_ON_LINE_GD_HDR_CALIBRATION_STATUS(x)       {g_stColorCalibrationInfo.b1CalibrationGDActiveHDRMode = (x);}
#endif
#else
#define GET_ON_LINE_CALIBRATION_STATUS()               (_CALIBRATION_OFF)
#define SET_ON_LINE_CALIBRATION_STATUS(x)              {NOP();}
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
#define GET_ON_LINE_GD_HDR_CALIBRATION_STATUS()        (_CALIBRATION_OFF)
#define GET_ON_LINE_GD_HDR_CALIBRATION_STATUS(x)       {NOP();}
#endif
#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))#if(_LOCAL_DIMMING_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of Calibration Checksum Type
//--------------------------------------------------
//CheckSum Type
#define _OGC_TYPE                                      0
#define _OCC_TYPE                                      1
#define _DICOM_TYPE                                    2
#define _RGB_GAIN_TYPE                                 3
#define _COLOR_MATRIX_TYPE                             4
#define _OGC_RGBGAMMA_TYPE                             5
#define _HDR_TYPE                                      6
#define _HEADER_TYPE                                   7
#define _OCC_HDR_TYPE                                  8
#define _DIMMING_OG_TYPE                               9
#define _DIMMING_IG_TYPE                               10
#define _FREESYNC_II_OG_TYPE                           11
#define _EDID_INFO_TYPE                                12
#define _FREESYNC_II_IG_TYPE                           13
#define _HDR10_NOTM_BOUND_TYPE                         14
#define _COLOR_MATRIX_TYPE2                            15
#define _ADVANCED_HDR10_TYPE                           16
#define _RGB_GAIN_MAX_BRI_TYPE                         17
#define _COLOR_MATRIX_MAX_BRI_TYPE                     18
#define _COLOR_MATRIX_MAX_BRI_TYPE2                    19
#define _NOTM_DCR_THD_TYPE                             20
#define _OGC_MAX_BRI_TYPE                              21
#define _HLG_YMAPPING_TYPE                             22
#define _FREESYNC_II_PQ_TYPE                           23
#define _HDR_BACKLIGHT_ADAPTIVE_TYPE                   24
#define _HDR_MASTERING_LV_STEPLESS_TYPE                25
#define _HDR_USER_DEFINE_FIXED_POINT_TYPE              26
#define _OCC_MULTI_BRI_3_TYPE                          27
#define _OCC_MULTI_BRI_4_TYPE                          28
#define _COLOR_MATRIX_MULTI_BRI_3_TYPE                 29
#define _COLOR_MATRIX_MULTI_BRI_3_TYPE2                30
#define _COLOR_MATRIX_MULTI_BRI_4_TYPE                 31
#define _COLOR_MATRIX_MULTI_BRI_4_TYPE2                32
#define _RGB_GAIN_MULTI_BRI_3_TYPE                     33
#define _RGB_GAIN_MULTI_BRI_4_TYPE                     34
#define _OCC_VERIFY_REPORT_TYPE                        35
#define _GD_PWMLUT_TYPE                                36
#define _3D_GAMMA_TYPE                                 37

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Enumerations of Backlight Type
//--------------------------------------------------
typedef enum
{
    _NORMAL_BACKLIGHT_CAL = 0,
    _MAX_BACKLIGHT_CAL = 1,
    _MULTI_BACKLIGHT_3_CAL = 2,
    _MULTI_BACKLIGHT_4_CAL = 3,
    _MULTI_BACKLIGHT_HDR10_PEAK_LV_CHECK = 4,
    _MULTI_BACKLIGHT_HDR10_REMAP_TYPE1 = 5,
    _MULTI_BACKLIGHT_HDR10_REMAP_TYPE2 = 6,
}EnumColorBacklightType;

//--------------------------------------------------
// Enumerations of Display calibration
//--------------------------------------------------
typedef enum
{
    _OGC_CAL,
    _OCC_CAL,
    _DICOM_CAL,
    _UNIFORMITY_CAL,
}EnumCaliType;

typedef enum
{
    _CALIBRATION_OFF,
    _CALIBRATION_ON,
} EnumLDActiveMode;

#if((_OGC_FUNCTION == _ON) ||\
    (_OCC_FUNCTION == _ON) ||\
    (_OGC_DICOM_FUNCTION == _ON) ||\
    (_UNIFORMITY_FUNCTION == _ON))
typedef struct
{
    BYTE b1CalibrationActiveMode                  : 1;
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
    BYTE b1CalibrationGDActiveHDRMode             : 1;
#endif
} StructCalibrationInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_OGC_FUNCTION == _ON) ||\
    (_OCC_FUNCTION == _ON) ||\
    (_OGC_DICOM_FUNCTION == _ON) ||\
    (_UNIFORMITY_FUNCTION == _ON))
extern StructCalibrationInfo g_stColorCalibrationInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
extern void UserCommonColorCalibrationProcess(void);
extern BYTE UserCommonColorCalibrationCalCheckSum(BYTE ucCheckType);
#endif

