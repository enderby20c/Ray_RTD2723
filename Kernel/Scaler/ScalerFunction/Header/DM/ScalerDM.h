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
// ID Code      : ScalerDM.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DM_H__
#define __SCALER_DM_H__

#if(_DM_FUNCTION == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SIZE_OF_DM_REG                                          88
#define _SIZE_OF_DM_B0103                                        1536
#define _SIZE_OF_DM_B02                                          1030
#define _SIZE_OF_DM_B0501                                        7804
#define _SIZE_OF_INFOFRAME                                       14

#define _DM_BW32_FW_MODE                                         _ON
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDMHWApplyPathSelect(EnumInputDataPath enumInputDataPath);

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
extern bit ScalerDMSwitchRSV(EnumRegionIndex enumRegionIndex, DWORD *pulRSVAddr, bit bOsdChange);
extern bit ScalerDMSwitchIDK(BYTE ucInbit, EnumColorSpace enumColorSpace, WORD usHWidth, WORD usVHeight, char *pDMArgv[]);
extern void ScalerDMHWApply(EnumDisplayRegion enumDisplayRegion, EnumColorSpace enumColorSpace, DWORD *pulDMRegister, DWORD *pulDMB02, StructBW32CmdUnitFormat *pstDMB0501);
#endif
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
#if(_DP_SUPPORT == _ON)
extern bit ScalerDMDRAMCheckDp_EXINT0(EnumInputPort enumInputPort);
#endif
#if(_HDMI_SUPPORT == _ON)
extern bit ScalerDMDRAMCheckHdmi_EXINT0(EnumInputPort enumInputPort);
#endif
#endif
#endif

#endif // End of #ifndef __SCALER_DM_H__
