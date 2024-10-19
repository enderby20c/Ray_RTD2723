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
// ID Code      : ScalerDpPhyRx2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_PHY_RX2_H__
#define __SCALER_DP_PHY_RX2_H__

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_PHY_RX2_ICP_KP_RBR()                                         (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_RBR)
#define SET_DP_PHY_RX2_ICP_KP_RBR(x)                                        (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_RBR = (x))
#define GET_DP_PHY_RX2_ICP_KP_HBR()                                         (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_HBR)
#define SET_DP_PHY_RX2_ICP_KP_HBR(x)                                        (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_HBR = (x))
#define GET_DP_PHY_RX2_ICP_KP_HBR2()                                        (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_HBR2)
#define SET_DP_PHY_RX2_ICP_KP_HBR2(x)                                       (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_HBR2 = (x))
#define GET_DP_PHY_RX2_ICP_KP_HBR3()                                        (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_HBR3)
#define SET_DP_PHY_RX2_ICP_KP_HBR3(x)                                       (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_HBR3 = (x))
#define GET_DP_PHY_RX2_ICP_KP_UHBR10()                                      (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_UHBR10)
#define SET_DP_PHY_RX2_ICP_KP_UHBR10(x)                                     (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_UHBR10 = (x))
#define GET_DP_PHY_RX2_ICP_KP_UHBR13P5()                                    (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_UHBR13p5)
#define SET_DP_PHY_RX2_ICP_KP_UHBR13P5(x)                                   (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_UHBR13p5 = (x))
#define GET_DP_PHY_RX2_ICP_KP_UHBR20()                                      (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_UHBR20)
#define SET_DP_PHY_RX2_ICP_KP_UHBR20(x)                                     (g_stDpPhyRx2IcpKp.ucDpPhyRxIcpKp_UHBR20 = (x))

#define GET_DP_PHY_RX2_ICP_RBR()                                            (g_stDpPhyRx2Icp.ucDpPhyRxIcp_RBR)
#define SET_DP_PHY_RX2_ICP_RBR(x)                                           (g_stDpPhyRx2Icp.ucDpPhyRxIcp_RBR = (x))
#define GET_DP_PHY_RX2_ICP_HBR()                                            (g_stDpPhyRx2Icp.ucDpPhyRxIcp_HBR)
#define SET_DP_PHY_RX2_ICP_HBR(x)                                           (g_stDpPhyRx2Icp.ucDpPhyRxIcp_HBR = (x))
#define GET_DP_PHY_RX2_ICP_HBR2()                                           (g_stDpPhyRx2Icp.ucDpPhyRxIcp_HBR2)
#define SET_DP_PHY_RX2_ICP_HBR2(x)                                          (g_stDpPhyRx2Icp.ucDpPhyRxIcp_HBR2 = (x))
#define GET_DP_PHY_RX2_ICP_HBR3()                                           (g_stDpPhyRx2Icp.ucDpPhyRxIcp_HBR3)
#define SET_DP_PHY_RX2_ICP_HBR3(x)                                          (g_stDpPhyRx2Icp.ucDpPhyRxIcp_HBR3 = (x))
#define GET_DP_PHY_RX2_ICP_UHBR10()                                         (g_stDpPhyRx2Icp.ucDpPhyRxIcp_UHBR10)
#define SET_DP_PHY_RX2_ICP_UHBR10(x)                                        (g_stDpPhyRx2Icp.ucDpPhyRxIcp_UHBR10 = (x))
#define GET_DP_PHY_RX2_ICP_UHBR13P5()                                       (g_stDpPhyRx2Icp.ucDpPhyRxIcp_UHBR13p5)
#define SET_DP_PHY_RX2_ICP_UHBR13P5(x)                                      (g_stDpPhyRx2Icp.ucDpPhyRxIcp_UHBR13p5 = (x))
#define GET_DP_PHY_RX2_ICP_UHBR20()                                         (g_stDpPhyRx2Icp.ucDpPhyRxIcp_UHBR20)
#define SET_DP_PHY_RX2_ICP_UHBR20(x)                                        (g_stDpPhyRx2Icp.ucDpPhyRxIcp_UHBR20 = (x))

#define GET_DP_PHY_RX2_KVCO_RBR()                                           (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_RBR)
#define SET_DP_PHY_RX2_KVCO_RBR(x)                                          (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_RBR = (x))
#define GET_DP_PHY_RX2_KVCO_HBR()                                           (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_HBR)
#define SET_DP_PHY_RX2_KVCO_HBR(x)                                          (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_HBR = (x))
#define GET_DP_PHY_RX2_KVCO_HBR2()                                          (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_HBR2)
#define SET_DP_PHY_RX2_KVCO_HBR2(x)                                         (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_HBR2 = (x))
#define GET_DP_PHY_RX2_KVCO_HBR3()                                          (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_HBR3)
#define SET_DP_PHY_RX2_KVCO_HBR3(x)                                         (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_HBR3 = (x))
#define GET_DP_PHY_RX2_KVCO_UHBR10()                                        (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_UHBR10)
#define SET_DP_PHY_RX2_KVCO_UHBR10(x)                                       (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_UHBR10 = (x))
#define GET_DP_PHY_RX2_KVCO_UHBR13P5()                                      (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_UHBR13p5)
#define SET_DP_PHY_RX2_KVCO_UHBR13P5(x)                                     (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_UHBR13p5 = (x))
#define GET_DP_PHY_RX2_KVCO_UHBR20()                                        (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_UHBR20)
#define SET_DP_PHY_RX2_KVCO_UHBR20(x)                                       (g_stDpPhyRx2Kvco.ucDpPhyRxKvco_UHBR20 = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDpPhyRxIcpKp g_stDpPhyRx2IcpKp;
extern volatile StructDpPhyRxIcp g_stDpPhyRx2Icp;
extern volatile StructDpPhyRxKvco g_stDpPhyRx2Kvco;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyRx2SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpPhyRx2CDRFLDSetting4Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef);
extern WORD ScalerDpPhyRx2EyeMonitorErrorCount(BYTE ucVth, BYTE ucPhase);

extern void ScalerDpPhyRx2Tp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx2CDRFLDSetting4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
extern void ScalerDpPhyRx2Tp1Measure_EXINT0(void);
extern void ScalerDpPhyRx2SetDFEInitial_EXINT0(void);

extern bit ScalerDpPhyRx2GetPhyCtsForDP14Flag(void);
extern bit ScalerDpPhyRx2GetPhyCtsForDP20Flag(void);
extern void ScalerDpPhyRx2PhyCtsManualMode_8b10b(void);


#if(_DP_PHY_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpPhyRx2PhyCtsManualMode_128b132b(void);
#endif

#endif

#endif // End of #ifndef __SCALER_DP_PHY_RX2_H__
