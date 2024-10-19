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
// ID Code      : ScalerDebugInclude.h No.0000
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
extern volatile bit g_bDebugHalt;
extern volatile bit g_bDebugRunCommand;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern volatile bit g_bDebugMessageEven;
#endif

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
extern DWORD g_pulDebugSysBusErrorInfo[15];
extern DWORD g_pulDebugCpuContext[32];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDebugSelectDDCCIDebugMode(EnumDDCCIDebugMode enumMode);

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern bit ScalerDebugCheckDebugPort(EnumInputPort enumInputPort);
#endif
