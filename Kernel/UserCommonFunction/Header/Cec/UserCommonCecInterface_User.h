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
// ID Code      : UserCommonCecInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User has CEC TX transmit task
//--------------------------------------------------
typedef enum
{
    _NO_CEC_TX_TASK = 0x00,
    _CEC_TX_TASK,
} EnumCecTxTransmitTask;

//--------------------------------------------------
// Enumerations of User has Enable CEC TX/RX Function
//--------------------------------------------------
typedef enum
{
    _CEC_FX_DISABLE = 0x00,
    _CEC_FX_ENABLE,
} EnumCecFunctionEnable;

//--------------------------------------------------
// Enumerations of User OSD has Enable CEC
//--------------------------------------------------
typedef enum
{
    _CEC_OSD_DISABLE = 0x00,
    _CEC_OSD_ENABLE,
} EnumCecOsdEnable;

//--------------------------------------------------
// Enumerations of User CEC Polling Audio Descriptor Result
//--------------------------------------------------
typedef enum
{
    _SINK_AUDIO_DESCRIPTOR_NOT_RECEIVED = 0x00,
    _SINK_AUDIO_DESCRIPTOR_RECEIVED,
} EnumCecPollingAudioDescriptorResult;

//--------------------------------------------------
// Enumerations of User CEC Get Polling Audio Descriptor Info
//--------------------------------------------------
typedef struct
{
    BYTE *pucBufferPtr;
    BYTE ucBufferSize;
    BYTE ucAudioDescriptorLength;
} StructCecAudioDescriptorInfo;

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
// -------------------------------------------------
// Enumerations of CEC Tx Logical Address Polling State
// -------------------------------------------------
typedef enum
{
    _CEC_TX_LA_POLLING_STATE_NONE,
    _CEC_TX_LA_POLLING_STATE_SENT,
    _CEC_TX_LA_POLLING_STATE_NACK,
    _CEC_TX_LA_POLLING_STATE_ACK,
} EnumCecTxLAPollingState;
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonCecFunctionEnable(EnumCecFunctionEnable enumCecEnable);
extern void UserCommonCecRxClrIMsgAnalyzingFlag(void);
extern bit UserCommonCecRxGetMsgAnalyzingFlag(void);
extern bit UserCommonCecCheckFrameLengthIsLegal(EnumCECOpCode enumOpCode, BYTE ucLength);
extern EnumCecTxEvent UserCommonCecTxGetTransmitResult(void);
extern EnumCecTxState UserCommonCecGetTxState(void);
extern void UserCommonCecRequestSendCecMessage(EnumCECOpCode enumOpCode);

#if(_AUDIO_ARC_SUPPORT == _ON)
extern void UserCommonCecSetArcInitiateReceivedEvent(void);
extern bit UserCommonCecGetArcInitiateReceivedEvent(void);
extern void UserCommonCecSetArcTerminateReceivedEvent(void);
extern bit UserCommonCecGetArcTerminateReceivedEvent(void);
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
extern void UserCommonCecHalPushTxMessageSendQueue(EnumCECOpCode enumOpCode);
extern EnumCECOpCode UserCommonCecHalGetTxMessageSendQueue(void);
extern void UserCommonCecHalPopTxMessageSendQueue(void);
extern BYTE UserCommonCecHalGetTxMessageSendQueueDepth(void);
extern BYTE UserCommonCecHalGetDxPortByDeviceLogicalAddress(BYTE ucLogicalAddress);
extern EnumInputPort UserCommonCecHalGetDxPortByPhysicalAddress(WORD usPhysicalAddress);
extern void UserCommonCecHalSetDeviceLogicalAddressByPhysicalAddress(WORD usPhysicalAddress, BYTE ucLogicalAddress);
extern WORD UserCommonCecHalGetPhysicalAddressByDxPort(EnumInputPort enumInputPortType);
extern BYTE UserCommonCecHalGetLogicalAddressByDxPort(EnumInputPort enumInputPortType);
extern void UserCommonCecHalSetOsdNameByDxPort(BYTE ucDxPortIndex, BYTE *pucOsdNameArray, BYTE ucOsdNameArrayLength);
extern void UserCommonCecHalClrOsdNameByDxPort(BYTE ucDxPortIndex);
extern EnumCecTxTransmitTask UserCommonCecHalPollingLogicalAddressHandler(EnumCECOpCode *penumOpCode, BYTE *pucLogicalAddress);
extern bit UserCommonCecHalGetPollingLogicalAddressStart(void);
extern void UserCommonCecHalStopPollingPhysicalAddress(void);
extern bit UserCommonCecHalCheckPollingLogicalAddressFinish(void);
extern EnumCecTxTransmitTask UserCommonCecHalRequestDeviceOsdNameHandler(BYTE *pucLogicalAddr);
extern void UserCommonCecHalTopologyHandler(void);
extern void UserCommonCecHalReceiveAudioDescriptorProc(StructCecRxReceivedInfo *pstCecRxInfo);
extern BYTE UserCommonCecHalGetPollingAudioDescriptorCount(void);
extern void UserCommonCecHalActiveWaitForAudioDescriptorReplyTimer(void);
extern void UserCommonCecHalStartPollingAudioDescriptor(void);
extern void UserCommonCecHalStopPollingAudioDescriptor(void);
extern void UserCommonCecHalPollingAudioDescriptorHandler(void);
extern EnumCecPollingAudioDescriptorResult UserCommonCecHalGetPollingAudioDescriptorResult(void);
extern void UserCommonCecHalGetSinkAudioDescriptorInfo(StructCecAudioDescriptorInfo *pstCecAudioDescriptorInfo);
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)