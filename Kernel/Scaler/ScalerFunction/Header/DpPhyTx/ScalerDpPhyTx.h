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
// ID Code      : ScalerDpPhyTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_PHY_TX_H__
#define __SCALER_DP_PHY_TX_H__

#if(_DP_PHY_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//-------------------------------------------------
// Trimming Data
//-------------------------------------------------

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Combo Tx Phy NF Code Setting Option
//--------------------------------------------------
typedef enum
{
    _COMBO_TX_PHY_NF_CODE_TRACKING = 0x00,
    _COMBO_TX_PHY_NF_CODE_BYPASS_TRACKING = 0x01,
} EnumOutputComboTxPhyNFCodeSettingOption;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_TX_XTAL                                         0
#define _DP_TX_27M_LC                                       1
#define _DP_TX_135M_LC                                      2
#define _DP_TX_EMB_IOSC                                     3
#define _DP_TX_DIG_LC                                       4
#define _DP_TX_LINK_CLK                                     5

#define _DP_TX_LCTANK                                       0
#define _DP_TX_RINGOSC                                      1

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyTxLoadTrimmingData(void);
extern void ScalerDpPhyTxLoadBandgap(void);
extern void ScalerDpPhyTxLTInitialSet(void);
extern void ScalerDpPhyTxLTStatusJudge(void);
extern bit ScalerDpPhyTxBandWidthReduce(void);
extern BYTE ScalerDpPhyTxLinkRateSort(EnumDpLinkRate enumLinkRate);
extern BYTE ScalerDpPhyTxLinkRateCheck(BYTE ucBand);
extern EnumDpLinkRate ScalerDpPhyTxLinkRateAna(BYTE ucBand);
extern void ScalerDpPhyTxPreCodingSet(bit bPreCodingEn);
extern bit ScalerDpPhyTxReadDfpDpcd(EnumDpTxLTReadWriteType enumDpTxLTRWType, BYTE ucLength, BYTE *pucReadArray);
extern bit ScalerDpPhyTxWriteDfpDpcd(EnumDpTxLTReadWriteType enumDpTxLTRWType, BYTE ucLength, BYTE *pucWriteArray);
extern void ScalerDpPhyTxGetDfpDpcdAddress(EnumDpTxLTReadWriteType enumDpTxLTRWType, BYTE *pucCommandAddrH, BYTE *pucAddrM, BYTE *pucAddrL);
extern BYTE ScalerDpPhyTxTrainPattern1(void);
extern BYTE ScalerDpPhyTxTrainPattern1_8b10b(void);
extern bit ScalerDpPhyTxTP1Lane0Adjust(void);
extern bit ScalerDpPhyTxTP1Lane1Adjust(void);
extern bit ScalerDpPhyTxTP1Lane2Adjust(void);
extern bit ScalerDpPhyTxTP1Lane3Adjust(void);
extern bit ScalerDpPhyTxTP1Lane0Adjust_8b10b(void);
extern bit ScalerDpPhyTxTP1Lane1Adjust_8b10b(void);
extern bit ScalerDpPhyTxTP1Lane2Adjust_8b10b(void);
extern bit ScalerDpPhyTxTP1Lane3Adjust_8b10b(void);
extern BYTE ScalerDpPhyTxTrainPattern2(void);
extern BYTE ScalerDpPhyTxTrainPattern2_8b10b(void);
extern void ScalerDpPhyTxTP2Lane0Adjust(void);
extern void ScalerDpPhyTxTP2Lane1Adjust(void);
extern void ScalerDpPhyTxTP2Lane2Adjust(void);
extern void ScalerDpPhyTxTP2Lane3Adjust(void);
extern void ScalerDpPhyTxTP2Lane0Adjust_8b10b(void);
extern void ScalerDpPhyTxTP2Lane1Adjust_8b10b(void);
extern void ScalerDpPhyTxTP2Lane2Adjust_8b10b(void);
extern void ScalerDpPhyTxTP2Lane3Adjust_8b10b(void);
extern void ScalerDpPhyTxTrainPatternEnd(void);
extern void ScalerDpPhyTxBandgap(bit bEnable);
extern void ScalerDpPhyTxIbias(bit bEnable);
extern void ScalerDpPhyTxInitialReset(void);
extern void ScalerDpPhyTxMLPHYSet(void);
//extern void ScalerDpPhyTxMLPowerOff(void);
extern void ScalerDpPhyTxCMUPowerOn(void);
//extern void ScalerDpPhyTxCMUPowerOff(void);
extern void ScalerDpPhyTxTerm(void);
extern void ScalerDpPhyTxSignalReset(void);
extern void ScalerDpPhyTxSignalInitialSetting(void);
extern void ScalerDpPhyTxNFCodeSet(DWORD ulCMUFreq);
extern void ScalerDpPhyTxNFCode(void);
extern BYTE ScalerDpPhyTxBitChange(BYTE ucBitChange);
extern void ScalerDpPhyTxSignalLaneSetting(void);
extern void ScalerDpPhyTxSignalLaneSetting_8b10b(void);
extern void ScalerDpPhyTxSetSignalLevel_8b10b(EnumDpLinkRate enumDpLinkRate, EnumDpTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern bit ScalerDpPhyTxAutoTest_8b10b(void);
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpPhyTxSetSignalLevel_128b132b(EnumDpLinkRate enumDpLinkRate, EnumDpTxLane enumLaneX, BYTE ucPreSet);
extern EnumDPTxLTResult ScalerDpPhyTxTrainPattern1_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainPattern2_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainEQPhase_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainEQPhasePolling_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainLTTPREQDoneCheck_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainRxAlignDoneCheck_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainRxCDSDoneCheck_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainCDSPhase_128b132b(void);
extern EnumDPTxLTResult ScalerDpPhyTxTrainCDSPhasePolling_128b132b(void);
extern bit ScalerDpPhyTxTP1Lane0Adjust_128b132b(void);
extern bit ScalerDpPhyTxTP1Lane1Adjust_128b132b(void);
extern bit ScalerDpPhyTxTP1Lane2Adjust_128b132b(void);
extern bit ScalerDpPhyTxTP1Lane3Adjust_128b132b(void);
extern void ScalerDpPhyTxTP2Lane0Adjust_128b132b(void);
extern void ScalerDpPhyTxTP2Lane1Adjust_128b132b(void);
extern void ScalerDpPhyTxTP2Lane2Adjust_128b132b(void);
extern void ScalerDpPhyTxTP2Lane3Adjust_128b132b(void);
extern void ScalerDpPhyTxSignalLaneSetting_128b132b(void);
extern bit ScalerDpPhyTxAutoTest_128b132b(void);
#endif
#endif // End of #if(_DP_PHY_TX_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_PHY_TX_H__
