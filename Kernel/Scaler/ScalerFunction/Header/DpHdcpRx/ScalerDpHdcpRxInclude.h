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
// ID Code      : ScalerDpHdcpRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if(_DP_HDCP_RX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of HDCP Information
//----------------------------------------------------------------------------
#if(_DP_HDCP_RX0_SUPPORT == _ON)
#define GET_DP_HDCP_RX0_HDCP_MODE()                     (g_enumDpHdcpRx0HdcpMode)
#define SET_DP_HDCP_RX0_HDCP_MODE(x)                    (g_enumDpHdcpRx0HdcpMode = (x))

#define GET_DP_HDCP_RX0_HDCP_CPIRQ()                    (g_bDpHdcpRx0HdcpCpirqFlag)
#define SET_DP_HDCP_RX0_HDCP_CPIRQ()                    (g_bDpHdcpRx0HdcpCpirqFlag = _TRUE)
#define CLR_DP_HDCP_RX0_HDCP_CPIRQ()                    (g_bDpHdcpRx0HdcpCpirqFlag = _FALSE)
#endif
#if(_DP_HDCP_RX1_SUPPORT == _ON)
#define GET_DP_HDCP_RX1_HDCP_MODE()                     (g_enumDpHdcpRx1HdcpMode)
#define SET_DP_HDCP_RX1_HDCP_MODE(x)                    (g_enumDpHdcpRx1HdcpMode = (x))

#define GET_DP_HDCP_RX1_HDCP_CPIRQ()                    (g_bDpHdcpRx1HdcpCpirqFlag)
#define SET_DP_HDCP_RX1_HDCP_CPIRQ()                    (g_bDpHdcpRx1HdcpCpirqFlag = _TRUE)
#define CLR_DP_HDCP_RX1_HDCP_CPIRQ()                    (g_bDpHdcpRx1HdcpCpirqFlag = _FALSE)
#endif
#if(_DP_HDCP_RX2_SUPPORT == _ON)
#define GET_DP_HDCP_RX2_HDCP_MODE()                     (g_enumDpHdcpRx2HdcpMode)
#define SET_DP_HDCP_RX2_HDCP_MODE(x)                    (g_enumDpHdcpRx2HdcpMode = (x))

#define GET_DP_HDCP_RX2_HDCP_CPIRQ()                    (g_bDpHdcpRx2HdcpCpirqFlag)
#define SET_DP_HDCP_RX2_HDCP_CPIRQ()                    (g_bDpHdcpRx2HdcpCpirqFlag = _TRUE)
#define CLR_DP_HDCP_RX2_HDCP_CPIRQ()                    (g_bDpHdcpRx2HdcpCpirqFlag = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_HDCP_RX0_SUPPORT == _ON)
extern volatile EnumHDCPType g_enumDpHdcpRx0HdcpMode;
extern volatile bit g_bDpHdcpRx0HdcpCpirqFlag;
extern BYTE g_pucDpHdcpRx0ECFBackup[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif
#if(_DP_HDCP_RX1_SUPPORT == _ON)
extern volatile EnumHDCPType g_enumDpHdcpRx1HdcpMode;
extern volatile bit g_bDpHdcpRx1HdcpCpirqFlag;
extern BYTE g_pucDpHdcpRx1ECFBackup[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif
#if(_DP_HDCP_RX2_SUPPORT == _ON)
extern volatile EnumHDCPType g_enumDpHdcpRx2HdcpMode;
extern volatile bit g_bDpHdcpRx2HdcpCpirqFlag;
extern BYTE g_pucDpHdcpRx2ECFBackup[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumInputPort ScalerDpHdcpRxRxDxMapping_WDINT(EnumRx enumRx);
extern EnumRx ScalerDpHdcpRxDxRxMapping_WDINT(EnumInputPort enumInputPort);

extern EnumRx ScalerDpHdcpRxDxRxMapping(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpHdcpRxRxDxMapping(EnumRx enumRx);
extern EnumInputPort ScalerDpHdcpRxRxDxMapping_EXINT0(EnumRx enumRx);
extern EnumHDCPType ScalerDpHdcpRxGetValidMode(EnumInputPort enumInputPort);
extern bit ScalerDpHdcpRxGetAuthDone(EnumInputPort enumInputPort);

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
extern EnumHDCPType ScalerDpHdcpRxGetEnabledMode(EnumInputPort enumInputPort);
#endif

extern void ScalerDpHdcpRxSetHdcpMode(EnumInputPort enumInputPort, EnumHDCPType enumHDCPType);
extern EnumHDCPType ScalerDpHdcpRxGetHdcpMode(EnumInputPort enumInputPort);
extern bit ScalerDpHdcpRxGetHdcpCpirqFlag(EnumInputPort enumInputPort);
extern void ScalerDpHdcpRxSetHdcpCpirqFlag(EnumInputPort enumInputPort);
extern void ScalerDpHdcpRxClrHdcpCpirqFlag(EnumInputPort enumInputPort);
extern void ScalerDpHdcpRxClrHdcpCpirqFlag_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpHdcpRxSetHdcpMode_EXINT0(EnumInputPort enumInputPort, EnumHDCPType enumHDCPType);
extern EnumHDCPType ScalerDpHdcpRxGetHdcpMode_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpHdcpRxInitial(EnumInputPort enumInputPort);
#endif
