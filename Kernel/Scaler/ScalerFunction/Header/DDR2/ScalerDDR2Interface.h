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
// ID Code      : ScalerDDR2Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

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
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_MEMORY_DDR2_2PC_SEPARATE_SUPPORT == _ON))
extern void ScalerDDR2RotationSetClientMux(void);
#endif
#endif // endif #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

