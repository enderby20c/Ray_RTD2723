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
// ID Code      : ScalerDpMacStreamRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
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
extern void ScalerDpMacStreamRxSdpInitial(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSecDataReset(EnumInputPort enumInputPort);
extern EnumSourceType ScalerDpMacStreamRxScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern bit ScalerDpMacStreamRxStableDetect(EnumInputPort enumInputPort, EnumSourceType enumSourceType);

extern void ScalerDpMacStreamRxSetFifoIRQ(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpMacStreamRxDisableFifoIRQ(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSetFifoWD(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpMacStreamRxDisableFifoWD(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetFifoWDStatus(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxCheckNoVideoStreamIRQStatus(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSetNoVideoStreamIRQ(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpMacStreamRxDisableNoVideoStreamIRQ(EnumInputPort enumInputPort);
extern BYTE ScalerDpMacStreamRxGetQuantizationPreValue(EnumInputPort enumInputPort);
extern UnionDpRxMsaValue ScalerDpMacStreamRxGetMsaInfo(EnumInputPort enumInputPort, EnumDpRxMsaType enumDpRxMsaType);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRxUnusedMacPowerOffProc(void);
#endif
#endif
