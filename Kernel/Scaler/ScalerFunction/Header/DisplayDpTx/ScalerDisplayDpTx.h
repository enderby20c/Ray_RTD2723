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
// ID Code      : ScalerDisplayDpTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DISPLAY_DP_TX_H__
#define __SCALER_DISPLAY_DP_TX_H__

#if(_DISPLAY_DP_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#define _DISPLAY_DP_TX_SKEW_LANE0                        0
#define _DISPLAY_DP_TX_SKEW_LANE1                        2
#define _DISPLAY_DP_TX_SKEW_LANE2                        4
#define _DISPLAY_DP_TX_SKEW_LANE3                        6

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerDisplayDpTxCheckSSC(void);
extern void ScalerDisplayDpTxLinkConfigCheck(void);

extern void ScalerDisplayDpTxPLL(bit bOn);
extern void ScalerDisplayDpTxPhy(bit bOn);
extern void ScalerDisplayDpTxPower(bit bOn);
extern void ScalerDisplayDpTxSetZ0(void);
extern void ScalerDisplayDpTxPhyControl(void);
extern void ScalerDisplayDpTxPhyDrivePower(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern bit ScalerDisplayDpTxLinkTraining(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxTraininPatternEndSequence(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxLinkConfig(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
extern void ScalerDisplayDpTxLinkForceOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#endif

extern void ScalerDisplayDpTxVideoStreamOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, bit bOutput);
extern bit ScalerDisplayDpTxGetHpdDebounceLevel(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxVendorSpecific004F1hAuxWrite(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxInitialSetting(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxPhyPowerDomainEnable(EnumPowerCut enumPowerCut);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern bit ScalerDisplayDpTxStableDetectCheck(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
extern void ScalerDisplayDpTxIrqHpdHandler_EXINT0(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#endif
#endif

extern bit ScalerDisplayDpTxGetDownSpread(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)


#endif // End of #ifndef __SCALER_DISPLAY_DP_TX_H__
