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
// ID Code      : ScalerTconInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _BEFORE_TCON_GATED_BY_PWM,
    _AFTER_TCON_GATED_BY_PWM,
} EnumTconLogicalOpPwmGatedSel;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTcon0Enable(bit bEnable);
extern void ScalerTcon0Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon0InvEnable(bit bEnable);

extern void ScalerTcon1Enable(bit bEnable);
extern void ScalerTcon1Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon1InvEnable(bit bEnable);

extern void ScalerTcon2Enable(bit bEnable);
extern void ScalerTcon2Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon2InvEnable(bit bEnable);

extern void ScalerTcon3Enable(bit bEnable);
extern void ScalerTcon3Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon3InvEnable(bit bEnable);

extern void ScalerTcon4Enable(bit bEnable);
extern void ScalerTcon4Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon4InvEnable(bit bEnable);

extern void ScalerTcon5Enable(bit bEnable);
extern void ScalerTcon5Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon5InvEnable(bit bEnable);

extern void ScalerTcon6Enable(bit bEnable);
extern void ScalerTcon6Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon6InvEnable(bit bEnable);

extern void ScalerTcon7Enable(bit bEnable);
extern void ScalerTcon7Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon7InvEnable(bit bEnable);

extern void ScalerTcon8Enable(bit bEnable);
extern void ScalerTcon8Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon8InvEnable(bit bEnable);

extern void ScalerTcon9Enable(bit bEnable);
extern void ScalerTcon9Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon9InvEnable(bit bEnable);

extern void ScalerTcon10Enable(bit bEnable);
extern void ScalerTcon10Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon10InvEnable(bit bEnable);

extern void ScalerTcon11Enable(bit bEnable);
extern void ScalerTcon11Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon11InvEnable(bit bEnable);

extern void ScalerTcon12Enable(bit bEnable);
extern void ScalerTcon12Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon12InvEnable(bit bEnable);

extern void ScalerTcon13Enable(bit bEnable);
extern void ScalerTcon13Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon13InvEnable(bit bEnable);

extern void ScalerTconEnable(bit bEnable);
extern void ScalerTconGatedByPwmEnable(EnumTconGatedByPwmSet enumTconGatedByPWM, BYTE ucPWM, bit bEnable);
extern void ScalerTconEnableByIndex(BYTE ucTconIndex, bit bEnable);
extern void ScalerTconAdjustByIndex(BYTE ucTconIndex, WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTconDBEnable(bit bEnable);
extern void ScalerTconDBApply(EnumDBApply enumDBApply);
extern void ScalerTconLogicalOpWithGatedByPwmSel(EnumTconLogicalOpPwmGatedSel enumTconPWMGated);
extern void ScalerTconLogicalOpEnable(EnumTconLogicalOpSet enumTconLogicalOpSet, EnumTconLogicalOp enumTconLogicalOp, bit bEnable);
extern void ScalerTconCompensationAdjust(WORD usHCompensate);

#if(_PWM_RST_SIGNAL_SEL == _TCON)
extern void ScalerTconAdjust(BYTE ucArea);
#endif

