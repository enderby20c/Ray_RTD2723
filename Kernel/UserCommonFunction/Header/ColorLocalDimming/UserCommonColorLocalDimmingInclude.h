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
// ID Code      : UserCommonColorLocalDimmingInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _LOCAL_DIMMING_EXPOSURE_REGION_THD           80
#define _LOCAL_DIMMING_SCENE_CHANGE_STEP_VALUE       712



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
typedef enum
{
    _LOCAL_DIMMING_HISTO_THD_HIGH = 0,
    _LOCAL_DIMMING_HISTO_THD_LOW = 1,
}EnumColorLocalDimmingHistoStage;
#endif



//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern void UserCommonColorLocalDimmingPWMInitial(void);
extern StructLocalDimmingFWCtrl g_stColorLocalDimmingFWCtrl;
#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

