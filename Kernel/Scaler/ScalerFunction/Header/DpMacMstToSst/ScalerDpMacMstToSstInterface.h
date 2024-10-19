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
// ID Code      : ScalerDpMacMstToSstInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_MAC_MST2SST_ENABLE()                                     (g_bDpMacMstToSstEnable)
#define SET_DP_MAC_MST2SST_ENABLE()                                     {\
                                                                            g_bDpMacMstToSstEnable = _TRUE;\
                                                                            SET_DP_MAC_MST2SST_INITIAL();\
                                                                        }
#define CLR_DP_MAC_MST2SST_ENABLE()                                     (g_bDpMacMstToSstEnable = _FALSE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpMacMstToSstEnable;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpMacMstToSstStreamsHandler(void);
extern void ScalerDpMacMstToSstSdpInitial(void);

#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

