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
// ID Code      : ScalerDpMacTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Load Key Prpcess
//--------------------------------------------------
#define _DP_TX_HDCP2_KEY_SIGNATURE                          1
#define _DP_TX_HDCP2_KEY_RRMODN                             2
#define _DP_TX_HDCP2_KEY_DCP_LLC_N                          3
#define _DP_TX_HDCP2_KEY_EKEY1                              4
#define _DP_TX_HDCP2_KEY_EKEY2                              5
#define _DP_TX_HDCP2_KEY_NPINV                              6

//--------------------------------------------------
// Definitions of Tx Loop Back Rx Input Port
//--------------------------------------------------
#define _DP_TX_LOOP_BACK_DPRX_INPUT_PORT                    (_P0_DP_PCB_LOOP_DX_PORT >> 4)

//--------------------------------------------------
// Define Output Power Info Macro
//--------------------------------------------------
#define GET_DP_TX_POWER_STATUS()                            (g_enumDpMacTxPowerStatus)
#define SET_DP_TX_POWER_STATUS(x)                           (g_enumDpMacTxPowerStatus = (x))
#define CLR_DP_TX_POWER_STATUS()                            (g_enumDpMacTxPowerStatus = _POWER_STATUS_NONE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Tx Input Timing Info Refer
//--------------------------------------------------
typedef enum
{
    _DP_TX_INPUT_TIMING_INFO_REF_MST2SST_MSA = 0x00,
    _DP_TX_INPUT_TIMING_INFO_REF_MEASURE,
} EnumDpTxInputTimingInfoRef;

//--------------------------------------------------
// Enumerations of Audio Play State
//--------------------------------------------------
typedef enum
{
    _DP_TX_AUDIO_PATH_RS_DECODER = 0x00,
    _DP_TX_AUDIO_PATH_I2S,
} EnumDPTxAudioPath;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_MAC_TX_SUPPORT == _ON)
extern EnumPowerStatus g_enumDpMacTxPowerStatus; // Dp Tx Power Status
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_MAC_TX_SUPPORT == _ON)
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacTxLinkEstablishManagement(void);
#endif
extern void ScalerDpMacTxModeHandler(void);
extern void ScalerDpMacTxJudgeHandler(void);
extern void ScalerDpMacTxIntHandle_EXINT0(void);
extern EnumDPTxInputSource ScalerDpMacTxGetStreamSource(void);
extern void ScalerDpMacTxHPDProc(void);
extern void ScalerDpMacTxSinkCountProc(void);
extern void ScalerDpMacTxCloneOutputProc(EnumInputPort enumInputPort, EnumPortType enumPortType, bit bClone);
extern bit ScalerDpMacTxCloneGetSourceSwitchFixedMode(EnumDisplayMode enumDisplayMode);
extern bit ScalerDpMacTxUserGetDownstreamHPDStatus(void);
extern BYTE ScalerDpMacTxGetLttprInitialMode(void);

extern WORD ScalerDpMacTxGetLinkBw(void);
extern bit ScalerDpMacTxGetDfpDeviceDscCap(void);

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern void ScalerDpMacTxDaisyChangeHandler(void);
#endif

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
extern void ScalerDpMacTxCloneModeSwitch(EnumDPCloneOutputStatus enumClone);
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
extern void ScalerDpMacTxSetSleepAudioState(EnumAudioStandAloneStatus enumAudioStandAloneStatus);
#endif
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

extern bit ScalerDpMacTxCableDetect(void);
extern WORD ScalerDpMacTxGetDownStreamEdidBw(void);
#endif

