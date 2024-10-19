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
// ID Code      : ScalerDpMacDphyRx0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_DPHY_RX0_H__
#define __SCALER_DP_MAC_DPHY_RX0_H__

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX0_SUPPORT == _ON))
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

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacDphyRx0Reset(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRx0MarginLinkCheck(void);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0DecodeErrorCountCheck(WORD usTimeCriteria, WORD usErrorCriteria);
extern bit ScalerDpMacDphyRx0LaneBsCheck(void);
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0LaneValidCheck(void);
#endif

extern void ScalerDpMacDphyRx0ValidSignalDetection(void);
extern BYTE ScalerDpMacDphyRx0LinkRateDetect(void);
extern bit ScalerDpMacDphyRx0LinkRateCheck(BYTE ucDpLinkRate);
extern bit ScalerDpMacDphyRx0VbiosAssrCheck(bit bMSACheckResult);
extern void ScalerDpMacDphyRx0ASSRModeSetting(void);
extern bit ScalerDpMacDphyRx0ChangeSrambleSeed(void);
extern bit ScalerDpMacDphyRx0MeasureLaneCDRClk(EnumDpLinkRate enumDpLinkRate, BYTE ucDpMacRx0LaneNumber);
extern BYTE ScalerDpMacDphyRx0PhyCtsTp1DecodeLane(BYTE ucTP1PhyLane);
extern BYTE ScalerDpMacDphyRx0PhyCtsTp2DecodeLane(BYTE ucTP2PhyLane);

extern bit ScalerDpMacDphyRx0HdcpCheck(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0Hdcp2ReAuthStatusCheck(void);
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount);
#endif

//--------------------------------------------------
// EXINT0 For None Postfix
//--------------------------------------------------
#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0FecHanlder_EXINT0(void);
#endif

//--------------------------------------------------
// WDINT For None Postfix
//--------------------------------------------------
extern void ScalerDpMacDphyRx0DecodeErrorCountReset_WDINT(void);


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern void ScalerDpMacDphyRx0LaneSwapSelect_8b10b(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRx0CheckHdcpCpirqStatus_8b10b(void);

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacDphyRx0LaneSwapSelect_8b10b_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0FecHanlder_8b10b_EXINT0(void);
extern bit ScalerDpMacDphyRx0FecDecodeCheck_8b10b_EXINT0(void);
#endif

extern BYTE ScalerDpMacDphyRx0Tp1DecodeCheck_8b10b_EXINT0(BYTE ucDpLane);
extern BYTE ScalerDpMacDphyRx0Tp2DecodeCheck_8b10b_EXINT0(EnumDpLane enumDpLane);
//--------------------------------------------------
// WDINT For None Postfix
//--------------------------------------------------


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacDphyRx0LaneSwapSelect_128b132b(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRx0CheckHdcpCpirqStatus_128b132b(void);
extern WORD ScalerDpMacDphyRx0SignalDetectMeasureCount_128b132b(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
extern void ScalerDpMacDphyRx0LaneSwapSelect_128b132b_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern WORD ScalerDpMacDphyRx0SignalDetectMeasureCount128b132b_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern BYTE ScalerDpMacDphyRx0Tp2DecodeCheck_128b132b_EXINT0(EnumDpLane enumDpLane);
extern BYTE ScalerDpMacDphyRx0Tp1DecodeCheck_128b132b_EXINT0(BYTE ucDpLane);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern bit ScalerDpMacDphyRx0FecDecodeCheck_128b132b_EXINT0(void);
#endif
#endif

//--------------------------------------------------
// WDINT For None Postfix
//--------------------------------------------------


///////////////////////////////////////////
// NNNNNeed special treatment
///////////////////////////////////////////
// Dphy + Mac
extern bit ScalerDpMacDphyRx0VbiosMsaCheck(bit bDeskewEnhanced);
#endif

#endif // End of #ifndef __SCALER_DP_MAC_DPHY_RX0_H__
