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
// ID Code      : ScalerTmdsPhyRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDMI_FRL_SUPPORT == _ON)
#define _6G_TIMING_FREQ                         6000
#define _FLD_FINE_TUNE_RANGE                    2
#endif

#define _TARGET_KVCO_SLOPE                      1100

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumInputPort ScalerTmdsPhyRxRxDxMapping(EnumRx enumRx);
extern EnumRx ScalerTmdsPhyRxDxRxMapping(EnumInputPort enumInputPort);
extern EnumInputPort ScalerTmdsPhyRxRxDxMapping_EXINT0(EnumRx enumRx);
extern EnumRx ScalerTmdsPhyRxDxRxMapping_EXINT0(EnumInputPort enumInputPort);
extern EnumRx ScalerTmdsPhyRxDxRxMapping_EXINT1(EnumInputPort enumInputPort);

extern bit ScalerTmdsPhyRxCheckDFE(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxPhyInitial(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxDisableDFE(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxSetPhy_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxSetRxEn(EnumInputPort enumInputPort, BYTE ucRxENStatus);
extern void ScalerTmdsPhyRxCdrMeasureClkSelect(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerTmdsPhyRxCdr2xClkEnable(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsPhyRxTransitionDataLaneSelect(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerTmdsPhyRxTransitionDataEnable(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsPhyRxFifoReset(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerTmdsPhyRxSetRxEn_EXINT0(EnumInputPort enumInputPort, BYTE ucRxENStatus);
extern void ScalerTmdsPhyRxCdrMeasureClkSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerTmdsPhyRxCdr2xClkEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsPhyRxTransitionDataLaneSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucLane);
extern void ScalerTmdsPhyRxTransitionDataEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsPhyRxUnstableFifoReset_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerTmdsPhyRxCheckDcdr_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxSetZ0Status(EnumInputPort enumInputPort, bit bEnable);
extern BYTE ScalerTmdsPhyRxSaveZ0Status(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxRestoreZ0Status(EnumInputPort enumInputPort, BYTE ucZ0Status);
extern bit ScalerTmdsPhyRxCheckDcdr(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxFifoAutoResetEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsPhyRxFifoAutoResetEnable(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerTmdsPhyRxFifoAutoClearFlag_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxFifoAutoClearFlag(EnumInputPort enumInputPort);
extern BYTE ScalerTmdsPhyRxFifoAutoResetDone_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerTmdsPhyRxFifoAutoResetDone(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxUnstableFifoReset(EnumInputPort enumInputPort);

#if(_HDMI_FRL_SUPPORT == _ON)
extern void ScalerTmdsPhyRxFrlSetPhy(EnumInputPort enumInputPort, BYTE ucLane, BYTE ucFRLrate);
extern void ScalerTmdsPhyRxFrlSetPhy_EXINT0(EnumInputPort enumInputPort, BYTE ucLane, BYTE ucFRLrate);
extern void ScalerTmdsPhyRxFrlSetAcdr(EnumInputPort enumInputPort);

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
extern void ScalerTmdsPhyRxFrlRebuildPhyInitial(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxFrlRebuildPhyOff(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxGdiClkSelect(EnumClkSel enumClock);
#endif

extern void ScalerTmdsPhyRxSelectMode(EnumInputPort enumInputPort, BYTE ucHdmiVersion);
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
extern void ScalerTmdsPhyRxClkLaneZ0StartToggle(void);
extern void ScalerTmdsPhyRxClkLaneZ0LowProc(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxClkLaneZ0HighProc(EnumInputPort enumInputPort);
extern void ScalerTmdsPhyRxClkLaneZ0StopToggle(EnumInputPort enumInputPort);
#endif
#endif
