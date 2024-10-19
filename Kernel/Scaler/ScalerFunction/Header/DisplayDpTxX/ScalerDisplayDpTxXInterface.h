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
// ID Code      : ScalerDisplayDpTxXInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DISPLAY_DP_TXX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_DPTX_HPD_DETECT == _ON)
#define GET_DISPLAY_DP_TX_FORCE_TO_LT()                     (GET_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_0) || GET_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_1) || GET_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_2) || GET_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_3))
#define CLR_DISPLAY_DP_TX_FORCE_TO_LT()                     {\
                                                                CLR_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_0);\
                                                                CLR_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_1);\
                                                                CLR_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_2);\
                                                                CLR_DISPLAY_DP_TXX_FORCE_TO_LT(_DISPLAY_DP_TX_PORT_3);\
                                                            }

#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
#define GET_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(x)              (g_pstDisplayDpTxXInputInfo[x].b1IrqHpdDetected)
#define SET_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(x)              (g_pstDisplayDpTxXInputInfo[x].b1IrqHpdDetected = _TRUE)
#define CLR_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(x)              (g_pstDisplayDpTxXInputInfo[x].b1IrqHpdDetected = _FALSE)
#endif

#define GET_DISPLAY_DP_TXX_FORCE_TO_LT(x)                   (g_pstDisplayDpTxXInputInfo[x].b1ForceLT)
#define SET_DISPLAY_DP_TXX_FORCE_TO_LT(x)                   (g_pstDisplayDpTxXInputInfo[x].b1ForceLT = _TRUE)
#define CLR_DISPLAY_DP_TXX_FORCE_TO_LT(x)                   (g_pstDisplayDpTxXInputInfo[x].b1ForceLT = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3ColorDepth : 3;
    BYTE b3ColorSpace : 3;
    WORD usInputPixelClk;
    BYTE b1LinkConfig : 1;
    BYTE b1StremOutput : 1;
    BYTE b1IrqHpdDetected : 1;
    BYTE b1ForceLT : 1;
} StructDisplayDPTxInputInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDisplayDPTxInputInfo g_pstDisplayDpTxXInputInfo[_DISPLAY_DP_TX_PORT_MAX];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif
