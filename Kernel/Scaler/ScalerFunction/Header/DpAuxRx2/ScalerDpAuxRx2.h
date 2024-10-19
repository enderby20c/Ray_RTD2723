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
// ID Code      : ScalerDpAuxRx2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_AUX_RX2_H__
#define __SCALER_DP_AUX_RX2_H__

#if(_DP_AUX_RX2_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern BYTE g_ucDpAuxRx2PVth;
extern BYTE g_ucDpAuxRx2NVth;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAuxRx2PowerOnInitial(void);
extern void ScalerDpAuxRx2DpcdAddrIrqInitial(void);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx2DpcdAddrIrqInitial_SramCtrl(void);
#else
extern void ScalerDpAuxRx2DpcdAddrIrqInitial_RegCtrl(void);
#endif
extern void ScalerDpAuxRx2SourceClkSet(void);
extern void ScalerDpAuxRx2DpcdInitial(void);

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern void ScalerDpAuxRx2AutoCalibration(void);
#endif

extern BYTE ScalerDpAuxRx2Tp1Check_8b10b_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx2Tp2Check_8b10b_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx2PhyCtsTp2Check_8b10b_EXINT0(void);

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpAuxRx2Tp1Check_128b132b_EXINT0(void);
extern BYTE ScalerDpAuxRx2Tp2Check_128b132b_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx2PhyCtsTp2Check_128b132b_EXINT0(void);
#endif

extern void ScalerDpAuxRx2ErrorCounterDisable_EXINT0(void);
extern void ScalerDpAuxRx2ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern bit ScalerDpAuxRx2FecGetSupport(void);
#endif

extern BYTE ScalerDpAuxRx2CheckSourceOUI_EXINT0(EnumDpAuxRxCheckSourceOUI enumDpAuxRx2CheckSourceOUI);

#endif // End of #if(_DP_AUX_RX1_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_AUX_RX2_H__
