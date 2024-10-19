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
// ID Code      : ScalerTmdsPhyRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TMDS_PHY_RX4_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TMDS_PHY_RX4_LANE_COUNT                    ((_HDMI21_PHY_RX4_SUPPORT == _ON) ? 4 : 3)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern bit ScalerTmdsPhyRx4CheckDFE(void);
extern void ScalerTmdsPhyRx4PhyInitial(void);
extern void ScalerTmdsPhyRx4DisableDFE(void);

extern void ScalerTmdsPhyRx4SetAdaptArea(bit bDeInverse, bit bDeBrankEn);
extern void ScalerTmdsPhyRx4SetRxEn(BYTE ucRxENStatus);
extern void ScalerTmdsPhyRx4SetRxEn_EXINT0(BYTE ucRxENStatus);
extern void ScalerTmdsPhyRx4SetZ0Status(bit bEnable);
extern void ScalerTmdsPhyRx4SetZ0Status_EXINT0(bit bEnable);
extern BYTE ScalerTmdsPhyRx4SaveZ0Status(void);
extern void ScalerTmdsPhyRx4RestoreZ0Status(BYTE ucZ0Status);
extern void ScalerTmdsPhyRx4SelectMode(BYTE ucHdmiVersion);
extern void ScalerTmdsPhyRx4CdrMeasureClkSelect(BYTE ucLane);
extern void ScalerTmdsPhyRx4Cdr2xClkEnable(bit bEnable);
extern void ScalerTmdsPhyRx4TransitionDataLaneSelect(BYTE ucLane);
extern void ScalerTmdsPhyRx4TransitionDataEnable(bit bEnable);
extern void ScalerTmdsPhyRx4CdrMeasureClkSelect_EXINT0(BYTE ucLane);
extern void ScalerTmdsPhyRx4Cdr2xClkEnable_EXINT0(bit bEnable);
extern void ScalerTmdsPhyRx4TransitionDataLaneSelect_EXINT0(BYTE ucLane);
extern void ScalerTmdsPhyRx4TransitionDataEnable_EXINT0(bit bEnable);
extern void ScalerTmdsPhyRx4FifoAutoResetEnable_EXINT0(bit bEnable);
extern void ScalerTmdsPhyRx4FifoAutoResetEnable(bit bEnable);
extern void ScalerTmdsPhyRx4FifoAutoClearFlag_EXINT0(void);
extern void ScalerTmdsPhyRx4FifoAutoClearFlag(void);
extern BYTE ScalerTmdsPhyRx4FifoAutoResetDone_EXINT0(void);
extern BYTE ScalerTmdsPhyRx4FifoAutoResetDone(void);
extern void ScalerTmdsPhyRx4UnstableFifoReset_EXINT0(void);
extern void ScalerTmdsPhyRx4FifoReset(BYTE ucLane);
extern void ScalerTmdsPhyRx4UnstableFifoReset(void);
extern void ScalerTmdsPhyRx4SetPhy(void);
extern void ScalerTmdsPhyRx4SetPhy_EXINT0(void);
extern void ScalerTmdsPhyRx4RDCTestMode(void);

#if(_HDMI21_PHY_RX4_SUPPORT == _ON)
extern void ScalerTmdsPhyRx4FrlSetPhy_EXINT0(BYTE ucLane, BYTE ucFRLrate);
extern void ScalerTmdsPhyRx4FrlSetAcdr(void);
extern void ScalerTmdsPhyRx4FrlRebuildPhyInitial(void);
extern void ScalerTmdsPhyRx4FrlRebuildPhyOff(void);
extern void ScalerTmdsPhyRx4FrlSetPhy(BYTE ucLane, BYTE ucFRLrate);
#endif
#endif // End of #if(_TMDS_PHY_RX4_SUPPORT == _ON)
