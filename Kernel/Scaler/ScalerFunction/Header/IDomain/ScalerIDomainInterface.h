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
// ID Code      : ScalerIDomainInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerIDomainVgipSetInputCapture(void);
extern WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition);
extern void ScalerIDomainResetDataPath(EnumInputDataPath enumVgipInputPath);
extern WORD ScalerIDomainGetInputHorTimingAfterFmtCnv(WORD usInputHorizontal, EnumInputDataPath enumInputDataPath);
extern void ScalerIDomainPatternGenEnable(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerIDomainPatternGenAdjustColor(EnumInputDataPath enumInputDataPath, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
