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
// ID Code      : SysDpInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_MAC_MST2SST_APPLY_EVENT()                                    (bit)(g_ucDpRxCtrl & _BIT1)
#define SET_DP_MAC_MST2SST_APPLY_EVENT()                                    (g_ucDpRxCtrl |= _BIT1)
#define CLR_DP_MAC_MST2SST_APPLY_EVENT()                                    (g_ucDpRxCtrl &= ~_BIT1)
#endif

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
#define GET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK()                             (bit)(g_ucDpRxCtrl & _BIT0)
#define SET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK()                             (g_ucDpRxCtrl |= _BIT0)
#define CLR_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK()                             (g_ucDpRxCtrl &= ~_BIT0)

#define GET_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG()                      (bit)(g_ucDpRxCtrl & _BIT1)
#define SET_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG()                      (g_ucDpRxCtrl |= _BIT1)
#define CLR_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG()                      (g_ucDpRxCtrl &= ~_BIT1)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON) || ((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON)))
extern volatile BYTE g_ucDpRxCtrl;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysDpInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, StructPortSwitchedStatus *pstPortStatus);

#if(_DP_SUPPORT == _ON)
extern void SysDpInitial(void);
extern void SysDpRxInitial(void);
extern void SysDpTxInitial(void);
extern void SysDpMacArbiterInitial(void);
extern void SysDpMacArbiter(EnumInputPort enumInputPort);

#if(_DP_MAC_SWITCH_SUPPORT == _ON)
extern void SysDpMacUnjudgedMacMappingReset(void);
#endif

extern BYTE SysDpGetConnectorType(EnumInputPort enumInputPort);

extern void SysDpPowerFakeOffToOffProc(void);

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
extern void SysDpPowerFakeSavingToSavingProc(void);
#endif

extern void SysDpRxHandler(void);
extern void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch);
extern bit SysDpSourceKeepDetectingCheck(void);
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern void SysDpRxPxpPortInitial(void);
extern EnumInputPort SysDpGetPxpInputTargetPort(void);
#endif

#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
extern void SysDpAuxRxPowerOnJudge(void);
extern void SysDpAuxRxPowerOffJudge(void);
extern void SysDpAuxRxPowerOn(EnumInputPort enumInputPort);
extern void SysDpAuxRxPowerOff(EnumInputPort enumInputPort);
extern EnumPowerCut SysDpAuxRxGetPowerStatus(EnumInputPort enumInputPort);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void SysDpTxHandler(void);
extern void SysDpTxSyncPowerStatusProc(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void SysDpMstHandler(void);
#endif

