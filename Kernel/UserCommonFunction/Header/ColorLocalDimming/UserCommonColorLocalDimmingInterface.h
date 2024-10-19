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
// ID Code      : UserCommonColorLocalDimmingInterface.h No.0000
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
#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern void UserCommonColorLocalDimmingHandler(void);
extern void UserCommonColorLocalDimmingEnable(EnumFunctionOnOFF enumOn);
extern void UserCommonColorLocalDimmingHistoLUTAdjust(EnumLocalDimmingType enumLDHisType);
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
extern void UserCommonColorLocalDimmingSyncToScpuHandler(void);
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_SCPU_SUPPORT == _ON))
extern void UserCommonColorLocalDimmingSyncToKcpuHandler(void);
extern void UserCommonColorLocalDimmingMainCpuPendSVCallback(void);
#endif

#if((_HW_CPU32_IS_BOOT_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
extern void UserCommonColorLocalDimmingGetKCPUStage(void);
#endif

#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

