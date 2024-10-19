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
// ID Code      : ScalerCecInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_CEC_TX_START()                               (g_stCecGeneralCtrl.b1CecTxStart)
#define SET_CEC_TX_START()                               (g_stCecGeneralCtrl.b1CecTxStart = 1)
#define CLR_CEC_TX_START()                               (g_stCecGeneralCtrl.b1CecTxStart = 0)

#define GET_CEC_RX_MSG_ANALYZING()                       (g_stCecGeneralCtrl.b1CecRxInfoAnalyzing)
#define SET_CEC_RX_MSG_ANALYZING()                       (g_stCecGeneralCtrl.b1CecRxInfoAnalyzing = 1)
#define CLR_CEC_RX_MSG_ANALYZING()                       (g_stCecGeneralCtrl.b1CecRxInfoAnalyzing = 0)

#define GET_CEC_RX_READ_DONE()                           (g_stCecGeneralCtrl.b1ReadDone)
#define SET_CEC_RX_READ_DONE()                           (g_stCecGeneralCtrl.b1ReadDone = 1)
#define CLR_CEC_RX_READ_DONE()                           (g_stCecGeneralCtrl.b1ReadDone = 0)

#define GET_CEC_TX_EVENT()                               (g_stCecGeneralCtrl.ucCecTxEvent)
#define SET_CEC_TX_EVENT(x)                              (g_stCecGeneralCtrl.ucCecTxEvent = (x))
#define CLR_CEC_TX_EVENT()                               (g_stCecGeneralCtrl.ucCecTxEvent = _CEC_TX_NONE_EVENT)

#define GET_CEC_TX_STATE()                               (g_stCecGeneralCtrl.b2CecTxState)
#define SET_CEC_TX_STATE(x)                              (g_stCecGeneralCtrl.b2CecTxState = (x))

#define GET_CEC_FUNCTION_ENABLE()                        (g_stCecGeneralCtrl.b1CecFxEnable)
#define SET_CEC_FUNCTION_ENABLE()                        (g_stCecGeneralCtrl.b1CecFxEnable = 1)
#define CLR_CEC_FUNCTION_ENABLE()                        (g_stCecGeneralCtrl.b1CecFxEnable = 0)

#if(_AUDIO_ARC_SUPPORT == _ON)
#define GET_CEC_ARC_INITIATE_RECEIVE_HAPPENED()          (g_stCecEventNotify.b1CecArcInitiateReceived)
#define SET_CEC_ARC_INITIATE_RECEIVE_HAPPENED()          (g_stCecEventNotify.b1CecArcInitiateReceived = _TRUE)
#define CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED()          (g_stCecEventNotify.b1CecArcInitiateReceived = _FALSE)

#define GET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED()         (g_stCecEventNotify.b1CecArcTerminateReceived)
#define SET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED()         (g_stCecEventNotify.b1CecArcTerminateReceived = _TRUE)
#define CLR_CEC_ARC_TERMINATE_RECEIVE_HAPPENED()         (g_stCecEventNotify.b1CecArcTerminateReceived = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of CEC Event Nofity
//--------------------------------------------------
typedef struct
{
    // TODO: After CEC high level porting, CEC must info need to add to kernel
#if(_AUDIO_ARC_SUPPORT == _ON)
    BYTE b1CecArcInitiateReceived : 1;
    BYTE b1CecArcTerminateReceived : 1;
#endif
} StructCecEventNotify;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructCecRxReceivedInfo g_stCecRxReceivedInfo;
extern StructCecTxTransmitInfo g_stCecTxTransmitInfo;
extern volatile BYTE g_ucCecRxTotalQueueMsgIdx;
extern StructCecEventNotify g_stCecEventNotify;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerCecInitial(void);
extern void ScalerCecRxProcess(void);
extern void ScalerCecTxProcess(void);
extern void ScalerCecIntHandler_EXINT0(void);
#endif
