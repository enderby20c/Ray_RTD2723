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
// ID Code      : UserCommonVgaInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// MACRO for VGA data
//--------------------------------------------------
#define _GET_CLOCKRANGE_MAX                             0
#define _GET_CLOCKRANGE_MIN                             1

//--------------------------------------------------
// // MACRO for VGA Mode Adjust H Position
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_H_POSITION()                (g_stVgaModeUserData.ucUserHPosition)
#define SET_VGA_MODE_ADJUST_H_POSITION(x)               (g_stVgaModeUserData.ucUserHPosition = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust V Position
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_V_POSITION()                (g_stVgaModeUserData.ucUserVPosition)
#define SET_VGA_MODE_ADJUST_V_POSITION(x)               (g_stVgaModeUserData.ucUserVPosition = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust Clock
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_CLOCK()                     (g_stVgaModeUserData.usUserClock)
#define SET_VGA_MODE_ADJUST_CLOCK(x)                    (g_stVgaModeUserData.usUserClock = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust Phase
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_PHASE()                     (g_stVgaModeUserData.ucUserPhase)
#define SET_VGA_MODE_ADJUST_PHASE(x)                    (g_stVgaModeUserData.ucUserPhase = (x))

//--------------------------------------------------
// MACRO for VGA Mode Do Auto
//--------------------------------------------------
#define GET_VGA_MODE_DO_FIRST_AUTO()                    (g_stVgaModeUserData.b1DoFirstAuto)
#define SET_VGA_MODE_DO_FIRST_AUTO(x)                   (g_stVgaModeUserData.b1DoFirstAuto = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User Do AutoConfig Action
//--------------------------------------------------
typedef enum
{
    _DO_AUTO_CONFIG_FALSE = _FALSE,
    _DO_AUTO_CONFIG_TRUE = _TRUE,
} EnumAutoConfigAction;

//--------------------------------------------------
// Enumerations of User Do AutoConfig Action
//--------------------------------------------------
typedef enum
{
    _AUTO_CONFIG_SKIP_FALSE = _FALSE,
    _AUTO_CONFIG_SKIP_TRUE = _TRUE,
} EnumAutoConfigSkip;

//--------------------------------------------------
// Structure of VGA Mode User Data
//--------------------------------------------------
typedef struct
{
    BYTE b1IsPresetMode : 1;
    BYTE b1DoFirstAuto : 1;
    BYTE ucModeNumber;
    BYTE ucUserHPosition;
    BYTE ucUserVPosition;
    WORD usUserClock;
    BYTE ucUserPhase;
    WORD usCenterHPosition;
    WORD usCenterVPosition;
    WORD usCenterClock;
    BYTE ucCenterPhase;
} StructVgaModeUserDataType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructVgaModeUserDataType g_stVgaModeUserData;
extern StructAdcDataType g_stVgaAdcData;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonVgaSyncProcGetSyncPad(void);
extern WORD UserCommonVgaGetAdcClockRange(BYTE ucPar);
extern void UserCommonVgaClockAdjust(WORD usUserIHTotal);
extern void UserCommonVgaPhaseAdjust(BYTE ucPhase);
extern void UserCommonVgaAdcDataAdjust(void);
extern void UserCommonVgaAutoConfig(void);

extern EnumAutoResult UserCommonVgaAutoDoWhiteBalance(EnumAutoColorType enumAutoType);
extern void UserCommonVgaAutoGetAutoColorResult(StructAdcDataType *pstAdcData);
extern EnumAutoResult UserCommonVgaAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult);
#if(_YPBPR_SUPPORT == _ON)
#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA)
extern StructAdcDataType UserCommonVgaAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData);
#endif
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern WORD UserCommonVgaGetCaptureHDelay(void);
extern void UserCommonVgaSetCaptureHDelay(WORD usIHSDelay);
extern WORD UserCommonVgaGetCaptureVDelay(void);
extern void UserCommonVgaSetCaptureVDelay(WORD usIVSDelay);
extern void UserCommonVgaDoubleBufferApply(void);
#endif

#endif

