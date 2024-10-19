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
// ID Code      : ScalerDpPhyRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX0_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_PHY_RX0_PCB_LANE0_MAPPING()              (g_stDpPhyRx0LanesMapping.b2Lane0Mapping)
#define SET_DP_PHY_RX0_PCB_LANE0_MAPPING(x)             (g_stDpPhyRx0LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_PHY_RX0_PCB_LANE1_MAPPING()              (g_stDpPhyRx0LanesMapping.b2Lane1Mapping)
#define SET_DP_PHY_RX0_PCB_LANE1_MAPPING(x)             (g_stDpPhyRx0LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_PHY_RX0_PCB_LANE2_MAPPING()              (g_stDpPhyRx0LanesMapping.b2Lane2Mapping)
#define SET_DP_PHY_RX0_PCB_LANE2_MAPPING(x)             (g_stDpPhyRx0LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_PHY_RX0_PCB_LANE3_MAPPING()              (g_stDpPhyRx0LanesMapping.b2Lane3Mapping)
#define SET_DP_PHY_RX0_PCB_LANE3_MAPPING(x)             (g_stDpPhyRx0LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_PHY_RX0_PCB_LANE0_PN_SWAP()              (g_stDpPhyRx0LanesMapping.b1Lane0PNSwap)
#define SET_DP_PHY_RX0_PCB_LANE0_PN_SWAP(x)             (g_stDpPhyRx0LanesMapping.b1Lane0PNSwap = (x))

#define GET_DP_PHY_RX0_PCB_LANE1_PN_SWAP()              (g_stDpPhyRx0LanesMapping.b1Lane1PNSwap)
#define SET_DP_PHY_RX0_PCB_LANE1_PN_SWAP(x)             (g_stDpPhyRx0LanesMapping.b1Lane1PNSwap = (x))

#define GET_DP_PHY_RX0_PCB_LANE2_PN_SWAP()              (g_stDpPhyRx0LanesMapping.b1Lane2PNSwap)
#define SET_DP_PHY_RX0_PCB_LANE2_PN_SWAP(x)             (g_stDpPhyRx0LanesMapping.b1Lane2PNSwap = (x))

#define GET_DP_PHY_RX0_PCB_LANE3_PN_SWAP()              (g_stDpPhyRx0LanesMapping.b1Lane3PNSwap)
#define SET_DP_PHY_RX0_PCB_LANE3_PN_SWAP(x)             (g_stDpPhyRx0LanesMapping.b1Lane3PNSwap = (x))

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _DP_PHY_RX0_D0_LANE0                            (GET_DP_PHY_RX0_PCB_LANE0_MAPPING())
#define _DP_PHY_RX0_D0_LANE1                            (GET_DP_PHY_RX0_PCB_LANE1_MAPPING())
#define _DP_PHY_RX0_D0_LANE2                            (GET_DP_PHY_RX0_PCB_LANE2_MAPPING())
#define _DP_PHY_RX0_D0_LANE3                            (GET_DP_PHY_RX0_PCB_LANE3_MAPPING())


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDpLanesMapping g_stDpPhyRx0LanesMapping;
extern BYTE g_pucDpPhyRx0LE[4];
extern WORD g_pusDpPhyRx0ClockTarget[4];
extern WORD g_usDpPhyRx0VCOBandDiff;
extern BYTE g_ucDpPhyRx0CtsCtrl;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyRx0PhyInitial(void);
extern void ScalerDpPhyRx0SetAltModeLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern bit ScalerDpPhyRx0DFECheck(void);
extern void ScalerDpPhyRx0RebuildPhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpPhyRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern void ScalerDpPhyRx0SignalDetection(bit bEnable);
extern void ScalerDpPhyRx0PhyCts(void);
extern void ScalerDpPhyRx0PhyCtsAutoMode(void);
extern void ScalerDpPhyRx0SetPhyCtsFlag(bit bFlag);
extern bit ScalerDpPhyRx0GetPhyCtsFlag(void);
extern void ScalerDpPhyRx0EyeMonitor(void);
extern bit ScalerDpPhyRx0GetEyeMonitorEnableFlag(void);
extern BYTE ScalerDpPhyRx0Tp1SignalDetectCheck_EXINT0(BYTE ucDpLaneSel);
extern void ScalerDpPhyRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0Tp2SetPhy_EXINT0(void);
extern void ScalerDpPhyRx0Tp3SetPhy_EXINT0(void);
extern void ScalerDpPhyRx0ResetCDR_EXINT0(BYTE ucTp2Result);
extern void ScalerDpPhyRx0PhyCtsTp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0PhyCtsTp2SetPhy_EXINT0(void);
extern BYTE ScalerDpPhyRx0DFECheck_EXINT0(void);
extern void ScalerDpPhyRx0SignalDetection_EXINT0(bit bEnable);
extern void ScalerDpPhyRx0SetAltModeLaneMapping_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpPhyRx0RebuildPhy_WDINT(EnumDpLinkRate enumDpLinkRate);

#endif
