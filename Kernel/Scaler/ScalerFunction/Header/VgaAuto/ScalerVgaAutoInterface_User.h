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
// ID Code      : ScalerVgaAutoInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Auto Function Channel types
//--------------------------------------------------
typedef enum
{
    _AUTO_RED_CHANNEL = 0x00,
    _AUTO_GREEN_CHANNEL = 0x01,
    _AUTO_BLUE_CHANNEL = 0x02,
    _AUTO_RGB_CHANNEL = 0x03,
} EnumAutoChannelType;

//--------------------------------------------------
// Enumerations of auto-color types
//--------------------------------------------------
typedef enum
{
    _AUTO_TUNE_RGB,
    _AUTO_TUNE_RGB_KNOWNWHITE,
    _AUTO_TUNE_YPBPR,
    _AUTO_CALIBRATE_RGB,
    _AUTO_TUNE_RGB_GAIN_ONLY,
    _AUTO_TUNE_YPBPR_GAIN_ONLY,
} EnumAutoColorType;

//--------------------------------------------------
// Structure of Adc Data
//--------------------------------------------------
typedef struct
{
    BYTE ucAdcPGA;
    BYTE pucAdcGainMSB[3];
    BYTE pucAdcGainLSB[3];
    BYTE pucAdcOffsetMSB[3];
    BYTE pucAdcOffsetLSB[3];
} StructAdcDataType;

//--------------------------------------------------
// Enumerations of image auto-function measure result status
//--------------------------------------------------
typedef enum
{
    _AUTO_FAIL = _FAIL,
    _AUTO_SUCCESS = _SUCCESS,
    _AUTO_ABORT,
} EnumAutoResult;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

