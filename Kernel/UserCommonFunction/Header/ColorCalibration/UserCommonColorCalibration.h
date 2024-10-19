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
// ID Code      : UserCommonColorCalibration.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_CALIBRATION_H__
#define __USER_COMMON_COLOR_CALIBRATION_H__

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of OGC/OCC/DICOM
//--------------------------------------------------
//Calibration Type
#define _OGC_CAL_TYPE               0
#define _OCC_CAL_TYPE               1
#define _DICOM_CAL_TYPE             2
#define _DIMMING_CAL_TYPE           7

#define _FREESYNC_II_CAL_TYPE       0

#define _DISP_CALIB_START           0
#define _DISP_CALIB_PASS            1
#define _DISP_CALIB_ERASE_ERROR     2
#define _DISP_CALIB_FW_ERROR        3
#define _DISP_CALIB_CRC_ERROR       4
#define _DISP_CALIB_FAIL            5
#define _DISP_CALIB_GET_VERSION     6
#define _DISP_CALIB_GET_NOTM_INFO   7
#define _DISP_CALIB_GET_UNI_VERSION 8
#define _DISP_CALIB_GET_FW_SUPPORT  9
#define _DISP_CALIB_GET_PANEL_INFO  10
#define _DISP_CALIB_GET_FW_ADVANCE  11
#define _DISP_CALIB_GET_GD_SET      12
#define _DISP_CALIB_GET_AUTH_VER    13
#define _FREESYNC_II_WHITE          0
#define _LD_BOOST_WHITE             1

#define _BG_PATTERN                 0
#define _PG_PATTERN                 1
#define _PG_BOX_PATTERN             2

#define _PATTERN_TOP                ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? 1023 : 1020)
#define _NOTM_DCR_THD_LENGTH        (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT ? 6 : 2)
#if(_HDR10_SUPPORT == _ON)
#define _NOTM_BOUND_SAVE_LENGTH     (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT ? 13 : 9)
#endif

#if((_DCIP3_NO_COMPRESSION_SUPPORT == _ON) || (_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON))
#define _DCIP3_SRGB_PRECISION       _SRGB_1_BIT_SHIFT_LEFT
#else
#define _DCIP3_SRGB_PRECISION       _SRGB_0_BIT_SHIFT_LEFT
#endif
#if((_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _ON) || (_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON))
#define _USER_DEFINE_PRECISION      _SRGB_1_BIT_SHIFT_LEFT
#else
#define _USER_DEFINE_PRECISION      _SRGB_0_BIT_SHIFT_LEFT
#endif
#define _ADOBE_SRGB_PRECISION       (_OCC_GAMUT_NO_COMPRESSION_SUPPORT ? _SRGB_1_BIT_SHIFT_LEFT : _SRGB_0_BIT_SHIFT_LEFT)
#define _OGC_GAMMA_MAX              (_OGC_TOTAL_GAMMA * _OGC_FUNCTION)
#define _OGC_GAMMA_TABLE_LENGTH     ((_PCM_FULL_TIME_FUNCTION == _ON) ? 2200 : 2052)

//--------------------------------------------------
// Definitions of HDR Input Gamma
//--------------------------------------------------
#define _DISP_CALIB_VERSION         (3 + _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _HDR_TOTAL_IG               (12 + 8 * (_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT ? 1 : 0) + 2 * (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT ? 1 : 0) + ((_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1) ? 1 : 0))

//--------------------------------------------------
// Definitions of 3D Gamma
//--------------------------------------------------
#define _3D_GAMMA_OG_TYPE           1
#define _3D_GAMMA_3D_TYPE           0

//--------------------------------------------------
// Definitions of FW Version
//--------------------------------------------------
#define _DISP_CALIB_FW_VERSION      0x001C
#define _DISP_CALIB_UNI_VERSION     0x000B

#if(_DISP_CALIBRATION_PCM_END + _OGC_FUNCTION * _OGC_TOTAL_GAMMA * _OGC_GAMMA_TABLE_SIZE + (_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0) * _OGC_FUNCTION * _OGC_TOTAL_GAMMA * _OGC_GAMMA_TABLE_SIZE > 0xFFFF)
#if((_FREESYNC_II_SUPPORT == _ON) || (_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE))
#warning "NOTE: Please check whether _FREESYNC_II_FLASH_BANK is larger than _OGC_FLASH_BANK + 1!"
#if(_UNIFORMITY_FUNCTION == _ON)
#warning "NOTE: Please check whether _UNIFORMITY_FLASH_BANK0 is larger than _OGC_FLASH_BANK + 2!"
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#warning "NOTE: Please check whether _OCC_RGB_3D_GAMMA_FLASH_BANK0 is larger than _OGC_FLASH_BANK + 3!"
#endif
#else
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#warning "NOTE: Please check whether _OCC_RGB_3D_GAMMA_FLASH_BANK0 is larger than _OGC_FLASH_BANK + 2!"
#endif
#endif
#endif
#else
#if(_UNIFORMITY_FUNCTION == _ON)
#warning "NOTE: Please check whether _UNIFORMITY_FLASH_BANK0 is larger than _OGC_FLASH_BANK + 1!"
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#warning "NOTE: Please check whether _OCC_RGB_3D_GAMMA_FLASH_BANK0 is larger than _OGC_FLASH_BANK + 2!"
#endif
#else
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#warning "NOTE: Please check whether _OCC_RGB_3D_GAMMA_FLASH_BANK0 is larger than _OGC_FLASH_BANK + 1!"
#endif
#endif
#endif

#if(_DISP_CALIBRATION_PCM_END < _OGC_HDR10_IG_1200_NOR_ADDRESS)
#warning "The space of _OGC_FLASH_BANK is not enough!!!"
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
#warning "NOTE: PCM should use Max Backlight table when UNIFORMITY ON!!!"
#endif
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
#warning "NOTE: Please check whether _SYSTEM_EEPROM_EMULATION_FLASH_BANK and _OGC_FLASH_BANK are same!"
#endif
#if(_UNIFORMITY_FUNCTION == _ON)
#warning "NOTE: Please check whether _SYSTEM_EEPROM_EMULATION_FLASH_BANK and _UNIFORMITY_FLASH_BANK0 are same!"
#endif
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#warning "NOTE: Please check whether _SYSTEM_EEPROM_EMULATION_FLASH_BANK and _OCC_RGB_3D_GAMMA_FLASH_BANK0 are same!"
#endif
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#if((_FREESYNC_II_SUPPORT == _ON) || (_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE))
#warning "NOTE: Please check whether _FREESYNC_II_FLASH_BANK is less than _OCC_RGB_3D_GAMMA_FLASH_BANK0 or larger than _OCC_RGB_3D_GAMMA_FLASH_BANK0 + (_OCC_RGB_3D_GAMMA_TOTAL_SET/2) + 1!"
#if(_UNIFORMITY_FUNCTION == _ON)
#warning "NOTE: Please check whether _UNIFORMITY_FLASH_BANK0 is less than _OCC_RGB_3D_GAMMA_FLASH_BANK0 or larger than _OCC_RGB_3D_GAMMA_FLASH_BANK0 + (_OCC_RGB_3D_GAMMA_TOTAL_SET/2) + 2!"
#endif
#endif
#else
#if(_UNIFORMITY_FUNCTION == _ON)
#warning "NOTE: Please check whether _UNIFORMITY_FLASH_BANK0 is less than _OCC_RGB_3D_GAMMA_FLASH_BANK0 or larger than _OCC_RGB_3D_GAMMA_FLASH_BANK0 + (_OCC_RGB_3D_GAMMA_TOTAL_SET/2) + 1!"
#endif
#endif


typedef enum
{
#if(_OGC_FUNCTION == _ON)
    _GAMMA1_POSITION,
#if(_OGC_TOTAL_GAMMA > 1)
    _GAMMA2_POSITION,
#if(_OGC_TOTAL_GAMMA > 2)
    _GAMMA3_POSITION,
#if(_OGC_TOTAL_GAMMA > 3)
    _GAMMA4_POSITION,
#if(_OGC_TOTAL_GAMMA > 4)
    _GAMMA5_POSITION,
#if(_OGC_TOTAL_GAMMA > 5)
    _GAMMA6_POSITION,
#endif
#endif
#endif
#endif
#endif
#endif

#if(_OCC_FUNCTION == _ON)
    _OCC_POSITION,
#endif
#if(_OGC_DICOM_FUNCTION == _ON)
    _DICOM_POSITION,
#if(_OGC_TOTAL_DICOM > 1)
    _DICOM2_POSITION,
#if(_OGC_TOTAL_DICOM > 2)
    _DICOM3_POSITION,
#if(_OGC_TOTAL_DICOM > 3)
    _DICOM4_POSITION,
#endif
#endif
#endif
#endif
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    _DIMMING_POSITION,
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
    _OCC_FREESYNC_II_POSITION,
#endif
#if((_HDR10_SUPPORT == _ON) || (_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR))
    _OCC_HDR_POSITION,
#endif
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
    _OCC_MULTI_BRI_3_POSITION,
#endif
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
    _OCC_MULTI_BRI_4_POSITION,
#endif
    _NONE_VALUE,
} EnumOGCTypePos;

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
typedef enum
{
    _3DGAMMA1_POSITION,
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 1)
    _3DGAMMA2_POSITION,
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 2)
    _3DGAMMA3_POSITION,
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 3)
    _3DGAMMA4_POSITION,
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 4)
    _3DGAMMA5_POSITION,
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 5)
    _3DGAMMA6_POSITION,
#endif
#endif
#endif
#endif
#endif
    _3DGAMMA_END_POSITION,
} Enum3DOGCTypePos;
#endif

//--------------------------------------------------
// Definitions of Uniformity
//--------------------------------------------------
#define _UNIFORMITY_GAIN_TYPE       7
#define _UNIFORMITY_OFFSET_TYPE     6
#define _UNIFORMITY_DECAY_TYPE      5


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructCalibrationInfo g_stColorCalibrationInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonColorCalibrationShowPattern(WORD usRed, WORD usGreen, WORD usBlue);
extern void UserCommonColorCalibrationPatternEnable(bit bEnable);
extern bit UserCommonColorCalibrationOGCStart(void);

#if(_OCC_FUNCTION == _ON)
extern BYTE UserCommonColorCalibrationOCCProcess(BYTE ucStep);
#endif
extern void UserCommonColorCalibrationAccessPanelColorMatchingData(BYTE ucCommand);

extern bit UserCommonColorCalibrationInitialCheck(void);
extern void UserCommonColorCalibrationFlashData(bit bReadWrite, BYTE ucBank, BYTE ucIndex, WORD usAddr, WORD usLength, BYTE *pucData);
extern void UserCommonColorCalibrationSaveLUT(BYTE ucTotalLength);
extern void UserCommonColorCalibrationShowGamma(void);
extern BYTE UserCommonColorCalibrationCheckSum(void);

extern BYTE UserCommonColorCalibrationMatrixCheckSum(BYTE ucCheckType);

extern void UserCommonColorCalibrationReplyResult(BYTE ucType);
extern void UserCommonColorCalibrationSaveHeader(void);
extern void UserCommonColorCalibrationSaveEDIDInfo(void);
extern void UserCommonColorCalibrationSaveNoToneMappingDCRTHD(void);
extern void UserCommonColorCalibrationShowDDomainPattern(WORD usRed, WORD usGreen, WORD usBlue, BYTE ucPatternType);
extern void UserCommonColorCalibrationSetBoxPatternGen(BYTE *pucCommand, bit bEnable);

#if(_HDR10_SUPPORT == _ON)
extern void UserCommonColorCalibrationSaveHDR10BoundInfo(void);
#endif

#if((_FREESYNC_II_SUPPORT == _ON) || (_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON))
extern void UserCommonColorCalibrationShowWhite(BYTE ucPatternType);
#endif

#if(_UNIFORMITY_FUNCTION == _ON)

extern void UserCommonColorCalibrationReplyOCCMatrix(BYTE ucPCMType);
extern void UserCommonColorCalibrationReplyOGCHeader(void);
extern void UserCommonColorCalibrationReplyUniformityDefine(void);
extern void UserCommonColorCalibrationReplyCCTGain(void);
extern void UserCommonColorCalibrationReplyFastModeData(void);
extern void UserCommonColorCalibReplyOGCOCCLvRatio(void);
extern void UserCommonColorCalibReplyOGCNEWLvRatio(void);
extern void UserCommonColorCalibrationReplyUniformityLevelMode(void);
extern void UserCommonColorCalibrationReplyUniformityNewLevelMode(void);
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
extern void UserCommonColorCalibrationSetPostGammaTable(BYTE ucColorGammaBankNum, BYTE *pucColorGammaAddr, EnumDBApply enumDBApply);
#endif
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
extern void UserCommonColorCalibrationSave3DGammaOGCLUT(BYTE ucTotalLength);
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void UserCommonColorCalibrationReplyDimmingDefine(void);
extern void UserCommonColorCalibrationSetPWMValue(void);
#endif

#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
extern void UserCommonColorCalibrationSetOCCPCMGamma(void);
#endif
extern BYTE UserCommonColorCalibrationCalGammaCheckSum(BYTE ucColorGammaBankNum, WORD usColorGammaAddr, bit bOCCMode);
extern void UserCommonColorCalibrationSetGammaTable(BYTE ucColorGammaBankNum, BYTE *pucColorGammaAddr, EnumDBApply enumDBApply);
extern void UserCommonColorCalibrationIPBypass(void);
#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))


#endif // End of #ifndef __USER_COMMON_COLOR_CALIBRATION_H__
