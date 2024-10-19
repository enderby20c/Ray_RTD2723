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
// ID Code      : ScalerDpHdcp2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP_2_2_SUPPORT == _ON)

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
extern void ScalerDpHdcp2RxUnplugResetProc(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2RxResetProc(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2RxResetDpcd(EnumInputPort enumInputPort, EnumDPRxHDCPResetDpcdField enumDPRxHDCPResetDpcdField);
extern bit ScalerDpHdcp2GetAuthenticationDone(EnumInputPort enumInputPort);
extern void ScalerDpHdcp2ClrAuthenticationDone(EnumInputPort enumInputPort);
extern BYTE ScalerDpHdcp2GetVPrime(EnumInputPort enumInputPort, BYTE ucIndex);
#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpHdcp2SetUpstreamEvent(EnumInputPort enumInputPort, EnumDpHdcp2RxUpstreamAuthStatus enumAuthStatus);
extern bit ScalerDpHdcp2GetRepeaterSupport(EnumInputPort enumInputPort);
#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerDpHdcp2RepeaterLPrimeCalculate(EnumInputPort enumInputPort, BYTE *pucInputArray);
#endif
#endif

#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
