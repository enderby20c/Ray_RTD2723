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
// ID Code      : ScalerFmtCnvInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FC_CAPTURE_HWIDTH                              (2048)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FB_OFF = 0x00,
    _FB_ON = _BIT7,
    _FB_FULL_TO_FB = (_BIT7 | _BIT6),
} EnumFrontBackMode;

typedef enum
{
    _FC_EAGLE_SIGHT_DISABLE = 0,
    _FC_EAGLE_SIGHT_ENABLE,
    _FC_EAGLE_SIGHT_NONE,
} EnumFCEagleSightStatus;

//--------------------------------------------------
// Enumerations of Data Path Pixel Mode
//--------------------------------------------------
typedef enum
{
    _FC_1_PIXEL_MODE = 0x01,
    _FC_2_PIXEL_MODE = 0x02,
    _FC_4_PIXEL_MODE = 0x04,
} EnumFmtCnvPixelMode;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerFmtCnvFtoPGetStatus(EnumInputDataPath enumInputDataPath);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
extern BYTE ScalerFmtCnvHalfSDGetFactor(EnumInputDataPath enumInputDataPath);
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
extern void ScalerFmtCnvP4P5SetEvenOddHwidth(WORD usHwidth);
#endif
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerFmtCnvFBSetInitialExtension(void);
#endif

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
extern EnumFmtCnvPixelMode ScalerFmtCnvEagleSightGetPixelMode(void);
extern EnumFCEagleSightStatus ScalerFmtCnvEagleSightEffectStatus(EnumInputDataPath enumInputDataPath);
extern bit ScalerFmtCnvEagleSightEnableStatus(void);
extern void ScalerFmtCnvEagleSightSetCaptureStart(WORD usStart);
extern WORD ScalerFmtCnvEagleSightGetCaptureStart(void);
extern void ScalerFmtCnvEagleSightSetCaptureWidth(WORD usWidth);
extern WORD ScalerFmtCnvEagleSightGetCaptureWidth(void);
extern void ScalerFmtCnvEagleSightSetSyncDelay(WORD usDelay);
#endif
#endif
