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
// ID Code      : ScalerRotationInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
#define _ROTATION_VERTICAL_MAX_SUPPORT_HWIDTH            (2560)
#define _ROTATION_VERTICAL_DDR_INPUT_BITS_MAX_NUM        (128)
#define _ROTATION_VERTICAL_DDR_INPUT_BITS_MARGIN_NUM     (120)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerRotationCheckVideoCompensation(void);
extern void ScalerRotationInitial(void);
extern void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize);
extern void ScalerRotationReset(void);
extern void ScalerRotationSetRotationEnable(void);
extern void ScalerRotationInputCtrl(EnumFRCPageSelect enumPageSelect, StructMemoryLineBlockStep *pstStep);
extern void ScalerRotationDisplayCtrl(EnumFRCPageSelect enumPageSelect, StructMemoryLineBlockStep *pstStep);
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
extern void ScalerRotationSetControl(EnumFRCPageSelect enumPageSelect, EnumRotationType enumRotationType);
extern DWORD ScalerRotationCalculateCaptureBW(DWORD ulPixelclk, WORD usCaphwidth);
extern bit ScalerRotationCheckVFrontPorch(bit bDigitalCapture);
#endif
#endif

