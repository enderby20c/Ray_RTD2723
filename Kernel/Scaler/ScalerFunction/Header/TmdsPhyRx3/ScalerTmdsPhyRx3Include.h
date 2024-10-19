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
// ID Code      : ScalerTmdsPhyRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TMDS_PHY_RX3_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TMDS_PHY_RX3_LANE_COUNT                    ((_HDMI21_PHY_RX3_SUPPORT == _ON) ? 4 : 3)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern bit ScalerTmdsPhyRx3CheckDFE(void);
extern void ScalerTmdsPhyRx3PhyInitial(void);
extern void ScalerTmdsPhyRx3DisableDFE(void);

extern void ScalerTmdsPhyRx3SetAdaptArea(bit bDeInverse, bit bDeBrankEn);
extern void ScalerTmdsPhyRx3SetRxEn(BYTE ucRxENStatus);
extern void ScalerTmdsPhyRx3SetRxEn_EXINT0(BYTE ucRxENStatus);
extern void ScalerTmdsPhyRx3SetZ0Sel(BYTE ucZ0sel);
extern void ScalerTmdsPhyRx3SetZ0Sel_EXINT0(BYTE ucZ0sel);
extern void ScalerTmdsPhyRx3SetZ0Code(BYTE ucZ0Code);
extern void ScalerTmdsPhyRx3SetZ0Code_EXINT0(BYTE ucZ0Code);
extern void ScalerTmdsPhyRx3SetZ0Status(bit bEnable);
extern void ScalerTmdsPhyRx3SetZ0Status_EXINT0(bit bEnable);
extern BYTE ScalerTmdsPhyRx3SaveZ0Status(void);
extern void ScalerTmdsPhyRx3RestoreZ0Status(BYTE ucZ0Status);
extern void ScalerTmdsPhyRx3SelectMode(BYTE ucHdmiVersion);
extern void ScalerTmdsPhyRx3CdrMeasureClkSelect(BYTE ucLane);
extern void ScalerTmdsPhyRx3Cdr2xClkEnable(bit bEnable);
extern void ScalerTmdsPhyRx3TransitionDataLaneSelect(BYTE ucLane);
extern void ScalerTmdsPhyRx3TransitionDataEnable(bit bEnable);
extern void ScalerTmdsPhyRx3CdrMeasureClkSelect_EXINT0(BYTE ucLane);
extern void ScalerTmdsPhyRx3Cdr2xClkEnable_EXINT0(bit bEnable);
extern void ScalerTmdsPhyRx3TransitionDataLaneSelect_EXINT0(BYTE ucLane);
extern void ScalerTmdsPhyRx3TransitionDataEnable_EXINT0(bit bEnable);
extern void ScalerTmdsPhyRx3FifoAutoResetEnable_EXINT0(bit bEnable);
extern void ScalerTmdsPhyRx3FifoAutoResetEnable(bit bEnable);
extern void ScalerTmdsPhyRx3FifoAutoClearFlag_EXINT0(void);
extern void ScalerTmdsPhyRx3FifoAutoClearFlag(void);
extern BYTE ScalerTmdsPhyRx3FifoAutoResetDone_EXINT0(void);
extern BYTE ScalerTmdsPhyRx3FifoAutoResetDone(void);
extern void ScalerTmdsPhyRx3UnstableFifoReset_EXINT0(void);
extern void ScalerTmdsPhyRx3FifoReset(BYTE ucLane);
extern void ScalerTmdsPhyRx3UnstableFifoReset(void);
extern void ScalerTmdsPhyRx3SetPhy(void);
extern void ScalerTmdsPhyRx3SetPhy_EXINT0(void);
extern void ScalerTmdsPhyRx3RDCTestMode(void);

#if(_HDMI21_PHY_RX3_SUPPORT == _ON)
extern void ScalerTmdsPhyRx3FrlSetPhy_EXINT0(BYTE ucLane, BYTE ucFRLrate);
extern void ScalerTmdsPhyRx3FrlSetAcdr(void);
extern void ScalerTmdsPhyRx3FrlRebuildPhyInitial(void);
extern void ScalerTmdsPhyRx3FrlRebuildPhyOff(void);
extern void ScalerTmdsPhyRx3FrlSetPhy(BYTE ucLane, BYTE ucFRLrate);
#endif
#endif // End of #if(_TMDS_PHY_RX3_SUPPORT == _ON)
