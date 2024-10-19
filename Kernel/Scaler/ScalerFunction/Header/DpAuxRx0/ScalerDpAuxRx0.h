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
// ID Code      : ScalerDpAuxRx0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_AUX_RX0_H__
#define __SCALER_DP_AUX_RX0_H__

#if(_DP_AUX_RX0_SUPPORT == _ON)

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
extern BYTE g_ucDpAuxRx0PVth;
extern BYTE g_ucDpAuxRx0NVth;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAuxRx0PowerOnInitial(void);
extern void ScalerDpAuxRx0DpcdAddrIrqInitial(void);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRx0DpcdAddrIrqInitial_SramCtrl(void);
#else
extern void ScalerDpAuxRx0DpcdAddrIrqInitial_RegCtrl(void);
#endif
extern void ScalerDpAuxRx0SourceClkSet(void);
extern void ScalerDpAuxRx0DpcdInitial(void);

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern void ScalerDpAuxRx0AutoCalibration(void);
#endif

extern BYTE ScalerDpAuxRx0Tp1Check_8b10b_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx0Tp2Check_8b10b_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx0PhyCtsTp2Check_8b10b_EXINT0(void);

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpAuxRx0Tp1Check_128b132b_EXINT0(void);
extern BYTE ScalerDpAuxRx0Tp2Check_128b132b_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpAuxRx0PhyCtsTp2Check_128b132b_EXINT0(void);
#endif

extern void ScalerDpAuxRx0ErrorCounterDisable_EXINT0(void);
extern void ScalerDpAuxRx0ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern bit ScalerDpAuxRx0FecGetSupport(void);
#endif

extern BYTE ScalerDpAuxRx0CheckSourceOUI_EXINT0(EnumDpAuxRxCheckSourceOUI enumDpAuxRx0CheckSourceOUI);

#endif // End of #if(_DP_AUX_RX0_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_AUX_RX0_H__
