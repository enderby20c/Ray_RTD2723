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
// ID Code      : ScalerDpMacDphyRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
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
extern void ScalerDpMacDphyRxLinkStatusIRQAssertCheck(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxNormalPreDetect(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxPSPreDetect(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHDCPUnplugReset(EnumInputPort enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRxMstInfoBackup(EnumInputPort enumInputPort, EnumDpMstBackup enumDpMstBackup);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern bit ScalerDpMacDphyRxGetMstStreamExist(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpMacDphyRxStreamChangeHandler(void);
#endif

#endif
