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
// ID Code      : ScalerVgipInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_VGIP_INPUT_PATH()                       (g_enumVgipInputPath)
#define CHK_VGIP_INPUT_PATH(x)                      ((g_enumVgipInputPath & (x)) == (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumInputDataPath g_enumVgipInputPath;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgipSetInputRegion(EnumDisplayRegion enumDisplayRegion);
extern WORD ScalerVgipGetCaptureHStartPosition(void);

extern bit ScalerVgipGetDigitalCaptureStatus(void);

extern WORD ScalerVgipGetCaptureHWidth(void);
extern WORD ScalerVgipGetCaptureHDelay(void);
extern void ScalerVgipSetCaptureHDelay(WORD usIHSDelay);
extern void ScalerVgipSetCaptureHStartPosition(WORD usIHstart);

extern WORD ScalerVgipGetCaptureVDelay(void);
extern void ScalerVgipSetCaptureVDelay(WORD usIVSDelay);
extern WORD ScalerVgipGetCaptureVHeight(void);
extern WORD ScalerVgipGetCaptureVStartPosition(void);

#if(_FRAME_RATE_SLOW_DOWN_SUPPORT == _ON)
extern void ScalerVgipSafeModeEnable(EnumDropIVFAction enumDropIVFAction, EnumInputDataPath enumVgipInputPath);
extern bit ScalerVgipGetSafeModeStatus(EnumInputDataPath enumVgipInputPath);
extern void ScalerVgipResetSafeMode(EnumInputDataPath enumVgipInputPath);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern void ScalerVgipDoubleBufferEnable(EnumInputDataPath enumSelectedDataPath, bit bEnable);
#endif
