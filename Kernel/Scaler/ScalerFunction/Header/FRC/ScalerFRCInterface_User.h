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
// ID Code      : ScalerFRCInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#define GET_DISP_LATENCY_RATIO()                            (g_ucFRCDispLatencyRatio)
#define SET_DISP_LATENCY_RATIO(x)                           (g_ucFRCDispLatencyRatio = (x))
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
#define GET_FRC_ALLM_LATENCY_RATIO()                        (g_ucFRCAllmInfoLatencyRatio)
#define SET_FRC_ALLM_LATENCY_RATIO(x)                       (g_ucFRCAllmInfoLatencyRatio = (x))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE g_ucFRCDispLatencyRatio;
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern BYTE g_ucFRCAllmInfoLatencyRatio;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

