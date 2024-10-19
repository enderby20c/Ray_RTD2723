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

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerRotationInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
#define _ROTATION_V_FRONT_PORCH_MIN_VALUE                    (6)
#define GET_ROT_V_FRONT_PORCH_MIN_VALUE()                    (g_usRotationVFrontPorchMin)
#define SET_ROT_V_FRONT_PORCH_MIN_VALUE(x)                   (g_usRotationVFrontPorchMin = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
extern WORD g_usRotationVFrontPorchMin;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerRotationCheckStatus(EnumRotationType enumRotationType, EnumInputPort enumInputPort);
extern void ScalerRotationSetEnable(bit bEn);
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
extern bit ScalerRotationCheckVerticalStatus(void);
#endif
#endif

