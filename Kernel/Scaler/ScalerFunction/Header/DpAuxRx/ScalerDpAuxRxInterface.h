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
// ID Code      : ScalerDpAuxRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_DP_SUPPORT == _ON)
extern void ScalerDpAuxRxSet(void);
extern void ScalerDpAuxRxSetLaneMapping(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
extern void ScalerDpAuxRxFakeLTProtect(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetDpcdBitInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern BYTE ScalerDpAuxRxGetDpcdInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void ScalerDpAuxRxSetDpcdValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdBitValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdBitWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdBitWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorBitValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorBitWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxDpcdGroupReset(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLen);
extern void ScalerDpAuxRxHpdIrqAssert(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetHdcp14DpcdBksv(void);
extern void ScalerDpAuxRxDpcdLinkStatusReset(EnumInputPort enumInputPort, EnumDpResetStatus enumDpResetStatus);

extern void ScalerDpAuxRxChPowerStatusCheck(EnumInputPort enumInputPort, bit bCableStatus);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpAuxRxSourceWritePowerUpProc(void);
#endif

extern BYTE ScalerDpAuxRxJudgeHandler_EXINT0(void);
extern void ScalerDpAuxRxExitIntSetting_EXINT0(void);
extern void ScalerDpAuxRxEnterIntSetting_EXINT0(void);
extern EnumDpLaneCount ScalerDpAuxRxGetDpcdLaneCount(EnumInputPort enumInputPort);
extern EnumDpLinkRate ScalerDpAuxRxGetDpcdLinkRate(EnumInputPort enumInputPort);
extern EnumDpLinkRate ScalerDpAuxRxGetDpcdLinkRate_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetLinkTrainingPass(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxMaxLinkRateCapabilitySwitch(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate);
extern bit ScalerDpAuxRxLinkRateCapabilitySwitchProc(EnumInputPort enumInputPort);
extern EnumDpVoltageSwingLevel ScalerDpAuxRxGetLaneVoltageSwingLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern EnumDpPreEmphasisLevel ScalerDpAuxRxGetLanePreEmpLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpAuxRxSinkCountUpdate(EnumInputPort enumInputPort, BYTE ucSinkCount, bit bIrqAssert);
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRxDpcdIrqProtect_T2INT(void);
#endif

#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
extern void ScalerDpAuxRxPowerControl(EnumInputPort enumInputPort, EnumPowerTarget enumPowerTarget);
extern EnumPowerCut ScalerDpAuxRxGetPowerStatus(EnumInputPort enumInputPort);
#endif
#endif
