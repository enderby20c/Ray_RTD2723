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
// ID Code      : ScalerDpHdcp14RxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP14_RX_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Struct for Rx Hdcp 1.4 Authentication
//--------------------------------------------------
typedef struct
{
    EnumDPRxHDCPAuthState b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1AuthRepeaterProcTimeout : 1;
    BYTE b1AuthReadIrqTimeout : 1;
    BYTE ucAuthUpstreamEvent;
    BYTE b1AuthCpIrqTimer : 1;
    BYTE b1AuthRepeaterAuth1Start : 1;
}StructDPMacRxHDCPAuthInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern void ScalerDpHdcp14RxUnplugResetProc(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxResetProc(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxResetDpcd(EnumInputPort enumInputPort, EnumDPRxHDCPResetDpcdField enumDPRxHDCPResetDpcdField);
#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpHdcp14RxGetRepeaterCaps_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxSetRepeaterProcTimeout(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxSetReadIrqTimeout(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxChangeAuthState(EnumInputPort enumInputPort, EnumDPRxHDCPAuthState enumHDCPAuthState);
extern void ScalerDpHdcp14RxClrAuthAksvWritten(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxSetAuthAksvWritten_EXINT0(EnumInputPort enumInputPort);
#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpHdcp14RxCancelHdcpCpIRQ(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxCancelHdcpRepeaterProcTimeout(EnumInputPort enumInputPort);
extern void ScalerDpHdcp14RxCancelHdcpReadIRQTimeout(EnumInputPort enumInputPort);
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif
