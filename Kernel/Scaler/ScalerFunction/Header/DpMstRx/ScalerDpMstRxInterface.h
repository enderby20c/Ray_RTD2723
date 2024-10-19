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
// ID Code      : ScalerDpMstRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
typedef enum
{
    _DP_MST_PXP_NO_PORT,
    _DP_MST_PXP_RX0_PORT,
    _DP_MST_PXP_RX1_PORT,
    _DP_MST_PXP_RX2_PORT,
    _DP_MST_PXP_AUTO_PORT,
} EnumDpMstPxpPort;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#define GET_DP_MST_RX_PXP_MODE_SUPPORT()                                                        (g_bDpMstRxPxpModeSupprot)
#define SET_DP_MST_RX_PXP_MODE_SUPPORT(x)                                                       (g_bDpMstRxPxpModeSupprot = (x))

#define GET_DP_MST_RX_PXP_MODE()                                                                (g_ucDpMstRxPxpModeType)
#define SET_DP_MST_RX_PXP_MODE(x)                                                               (g_ucDpMstRxPxpModeType = (x))

#define GET_DP_MST_RX_PXP_INPUT_PORT()                                                          (g_ucDpMstRxPxpInputPort)
#define SET_DP_MST_RX_PXP_INPUT_PORT(x)                                                         (g_ucDpMstRxPxpInputPort = (x))

#define GET_DP_MST_RX_PXP_PORT_NUM_SWAP()                                                       (g_enumDpMstRxPxpPortNumSwap)
#define SET_DP_MST_RX_PXP_PORT_NUM_SWAP(x)                                                      (g_enumDpMstRxPxpPortNumSwap = (x))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
extern bit g_bDpMstRxPxpModeSupprot;
extern BYTE g_ucDpMstRxPxpModeType;
extern BYTE g_ucDpMstRxPxpInputPort;
extern EnumDpPxpPortNumSwapStatus g_enumDpMstRxPxpPortNumSwap;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpMstRxInitial(EnumInputPort enumInputPort);
extern void ScalerDpMstRxHandler(void);
extern void ScalerDpMstRxCableUnplugReset(EnumInputPort enumInputPort);
extern void ScalerDpMstRxCapablePortSwitch(EnumDPMSTPort enumMstCapablePort);
extern EnumInputPort ScalerDpMstRxGetInputPort(EnumDPMSTPort enumMstPort);
extern EnumInputPort ScalerDpMstRxGetRxDownRequestMstInputPort(void);
extern void ScalerDpMstRxCapabilitySwitchProc(void);
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
extern void ScalerDpMstRxPxpModeSwitch(EnumDpMstPxpMode enumDpMstPxpMode);
extern EnumDpMstPxpMode ScalerDpMstRxGetPxpMode(void);
#endif
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

#if((_DP_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)))
extern void ScalerDpMstRxPowerOnInitial(EnumInputPort enumInputPort);
extern void ScalerDpMstRxReset(EnumInputPort enumInputPort);
#endif
