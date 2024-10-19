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
// ID Code      : ScalerDpPhyRx0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_PHY_RX0_H__
#define __SCALER_DP_PHY_RX0_H__

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX0_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_PHY_RX0_ICP_KP_RBR()                                         (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_RBR)
#define SET_DP_PHY_RX0_ICP_KP_RBR(x)                                        (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_RBR = (x))
#define GET_DP_PHY_RX0_ICP_KP_HBR()                                         (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_HBR)
#define SET_DP_PHY_RX0_ICP_KP_HBR(x)                                        (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_HBR = (x))
#define GET_DP_PHY_RX0_ICP_KP_HBR2()                                        (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_HBR2)
#define SET_DP_PHY_RX0_ICP_KP_HBR2(x)                                       (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_HBR2 = (x))
#define GET_DP_PHY_RX0_ICP_KP_HBR3()                                        (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_HBR3)
#define SET_DP_PHY_RX0_ICP_KP_HBR3(x)                                       (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_HBR3 = (x))
#define GET_DP_PHY_RX0_ICP_KP_UHBR10()                                      (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_UHBR10)
#define SET_DP_PHY_RX0_ICP_KP_UHBR10(x)                                     (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_UHBR10 = (x))
#define GET_DP_PHY_RX0_ICP_KP_UHBR13P5()                                    (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_UHBR13p5)
#define SET_DP_PHY_RX0_ICP_KP_UHBR13P5(x)                                   (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_UHBR13p5 = (x))
#define GET_DP_PHY_RX0_ICP_KP_UHBR20()                                      (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_UHBR20)
#define SET_DP_PHY_RX0_ICP_KP_UHBR20(x)                                     (g_stDpPhyRx0IcpKp.ucDpPhyRxIcpKp_UHBR20 = (x))

#define GET_DP_PHY_RX0_ICP_RBR()                                            (g_stDpPhyRx0Icp.ucDpPhyRxIcp_RBR)
#define SET_DP_PHY_RX0_ICP_RBR(x)                                           (g_stDpPhyRx0Icp.ucDpPhyRxIcp_RBR = (x))
#define GET_DP_PHY_RX0_ICP_HBR()                                            (g_stDpPhyRx0Icp.ucDpPhyRxIcp_HBR)
#define SET_DP_PHY_RX0_ICP_HBR(x)                                           (g_stDpPhyRx0Icp.ucDpPhyRxIcp_HBR = (x))
#define GET_DP_PHY_RX0_ICP_HBR2()                                           (g_stDpPhyRx0Icp.ucDpPhyRxIcp_HBR2)
#define SET_DP_PHY_RX0_ICP_HBR2(x)                                          (g_stDpPhyRx0Icp.ucDpPhyRxIcp_HBR2 = (x))
#define GET_DP_PHY_RX0_ICP_HBR3()                                           (g_stDpPhyRx0Icp.ucDpPhyRxIcp_HBR3)
#define SET_DP_PHY_RX0_ICP_HBR3(x)                                          (g_stDpPhyRx0Icp.ucDpPhyRxIcp_HBR3 = (x))
#define GET_DP_PHY_RX0_ICP_UHBR10()                                         (g_stDpPhyRx0Icp.ucDpPhyRxIcp_UHBR10)
#define SET_DP_PHY_RX0_ICP_UHBR10(x)                                        (g_stDpPhyRx0Icp.ucDpPhyRxIcp_UHBR10 = (x))
#define GET_DP_PHY_RX0_ICP_UHBR13P5()                                       (g_stDpPhyRx0Icp.ucDpPhyRxIcp_UHBR13p5)
#define SET_DP_PHY_RX0_ICP_UHBR13P5(x)                                      (g_stDpPhyRx0Icp.ucDpPhyRxIcp_UHBR13p5 = (x))
#define GET_DP_PHY_RX0_ICP_UHBR20()                                         (g_stDpPhyRx0Icp.ucDpPhyRxIcp_UHBR20)
#define SET_DP_PHY_RX0_ICP_UHBR20(x)                                        (g_stDpPhyRx0Icp.ucDpPhyRxIcp_UHBR20 = (x))

#define GET_DP_PHY_RX0_KVCO_RBR()                                           (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_RBR)
#define SET_DP_PHY_RX0_KVCO_RBR(x)                                          (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_RBR = (x))
#define GET_DP_PHY_RX0_KVCO_HBR()                                           (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_HBR)
#define SET_DP_PHY_RX0_KVCO_HBR(x)                                          (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_HBR = (x))
#define GET_DP_PHY_RX0_KVCO_HBR2()                                          (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_HBR2)
#define SET_DP_PHY_RX0_KVCO_HBR2(x)                                         (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_HBR2 = (x))
#define GET_DP_PHY_RX0_KVCO_HBR3()                                          (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_HBR3)
#define SET_DP_PHY_RX0_KVCO_HBR3(x)                                         (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_HBR3 = (x))
#define GET_DP_PHY_RX0_KVCO_UHBR10()                                        (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_UHBR10)
#define SET_DP_PHY_RX0_KVCO_UHBR10(x)                                       (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_UHBR10 = (x))
#define GET_DP_PHY_RX0_KVCO_UHBR13P5()                                      (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_UHBR13p5)
#define SET_DP_PHY_RX0_KVCO_UHBR13P5(x)                                     (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_UHBR13p5 = (x))
#define GET_DP_PHY_RX0_KVCO_UHBR20()                                        (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_UHBR20)
#define SET_DP_PHY_RX0_KVCO_UHBR20(x)                                       (g_stDpPhyRx0Kvco.ucDpPhyRxKvco_UHBR20 = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDpPhyRxIcpKp g_stDpPhyRx0IcpKp;
extern volatile StructDpPhyRxIcp g_stDpPhyRx0Icp;
extern volatile StructDpPhyRxKvco g_stDpPhyRx0Kvco;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyRx0Rebuild4LanePhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _OFF)
extern void ScalerDpPhyRx0KOobs(void);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0RebuildUnFlip2LanePhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpPhyRx0RebuildFlip2LanePhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane);
#endif

extern void ScalerDpPhyRx0APhyFLDSetting4Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0APhyFLDSettingUnFlip2Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0APhyFLDSettingFlip2Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
#endif

extern void ScalerDpPhyRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0SetDFEInitialUnFlip2Lane(EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpPhyRx0SetDFEInitialFlip2Lane(EnumDpLinkRate enumDpLinkRate);
#endif

extern bit ScalerDpPhyRx0GetPhyCtsForDP14Flag(void);
extern bit ScalerDpPhyRx0GetPhyCtsForDP20Flag(void);
extern void ScalerDpPhyRx0PhyCtsManualMode_8b10b(void);
#if(_DP_PHY_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpPhyRx0PhyCtsManualMode_128b132b(void);
#endif

extern void ScalerDpPhyRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0PhyCtsTp1SetPhy4Lane(EnumDpNFCodeRef enumDpNFCodeRef);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0PhyCtsTp1SetPhyUnFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0PhyCtsTp1SetPhyFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef);
#endif

extern void ScalerDpPhyRx0PhyCtsTp2SetPhy(void);
extern void ScalerDpPhyRx0PhyCtsTp2SetPhy4Lane(void);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0PhyCtsTp2SetPhyUnFlip2Lane(void);
extern void ScalerDpPhyRx0PhyCtsTp2SetPhyFlip2Lane(void);
#endif

extern WORD ScalerDpPhyRx0EyeMonitorErrorCount(BYTE ucVth, BYTE ucPhase);
extern void ScalerDpPhyRx0SetDFEInitial_EXINT0(void);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0SetDFEInitialUnFlip2Lane_EXINT0(void);
extern void ScalerDpPhyRx0SetDFEInitialFlip2Lane_EXINT0(void);
#endif

extern void ScalerDpPhyRx0Tp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0Tp1Measure_EXINT0(void);
extern void ScalerDpPhyRx0PhyCtsTp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _OFF)
extern void ScalerDpPhyRx0KOobs_EXINT0(void);
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0Tp1SetPhyUnFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0Tp1SetPhyFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0PhyCtsTp1SetPhyUnFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0PhyCtsTp1SetPhyFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
#endif

extern void ScalerDpPhyRx0Tp2SetPhy4Lane_EXINT0(void);
extern void ScalerDpPhyRx0Tp3SetPhy4Lane_EXINT0(void);
extern void ScalerDpPhyRx0PhyCtsTp2SetPhy4Lane_EXINT0(void);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0Tp2SetPhyUnFlip2Lane_EXINT0(void);
extern void ScalerDpPhyRx0Tp2SetPhyFlip2Lane_EXINT0(void);
extern void ScalerDpPhyRx0Tp3SetPhyUnFlip2Lane_EXINT0(void);
extern void ScalerDpPhyRx0Tp3SetPhyFlip2Lane_EXINT0(void);
extern void ScalerDpPhyRx0PhyCtsTp2SetPhyUnFlip2Lane_EXINT0(void);
extern void ScalerDpPhyRx0PhyCtsTp2SetPhyFlip2Lane_EXINT0(void);
#endif

extern void ScalerDpPhyRx0APhyFLDSetting4Lane_EXINT0(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0APhyFLDSettingUnFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx0APhyFLDSettingFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
#endif

extern void ScalerDpPhyRx0RebuildPhy4Lane_WDINT(EnumDpLinkRate enumDpLinkRate);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpPhyRx0RebuildPhyUnFlip2Lane_WDINT(EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpPhyRx0RebuildPhyFlip2Lane_WDINT(EnumDpLinkRate enumDpLinkRate);
#endif

#endif // End of #if(_DP_PHY_RX0_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_PHY_RX0_H__
