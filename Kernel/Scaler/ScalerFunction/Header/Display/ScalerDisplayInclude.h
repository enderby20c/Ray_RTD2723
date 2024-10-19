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
// ID Code      : ScalerDisplayInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
#define _D_DOMAIN_ACTIVE_COUNT                                  (4)
#elif(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
#define _D_DOMAIN_ACTIVE_COUNT                                  (3)
#elif(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
#define _D_DOMAIN_ACTIVE_COUNT                                  (2)
#else
#define _D_DOMAIN_ACTIVE_COUNT                                  (1)
#endif

#if(_FRC_SUPPORT == _ON)
#define GET_PANEL_PIXEL_CLOCK_TYPICAL()                         (g_stDisplayCustomizedData.structDVCustomizedFreq.ulPanelClockTypical)
#define GET_PANEL_PIXEL_CLOCK_MAX_SPREAD()                      (g_stDisplayCustomizedData.structDVCustomizedFreq.ulPanelClockMaxSpread)
#define GET_PANEL_PIXEL_CLOCK_MIN_SPREAD()                      (g_stDisplayCustomizedData.structDVCustomizedFreq.ulPanelClockMinSpread)
#else
#define GET_PANEL_PIXEL_CLOCK_TYPICAL()                         (_PANEL_PIXEL_CLOCK_KHZ)
#define GET_PANEL_PIXEL_CLOCK_MAX_SPREAD()                      (_PANEL_PIXEL_CLOCK_MAX_SPREAD)
#define GET_PANEL_PIXEL_CLOCK_MIN_SPREAD()                      (_PANEL_PIXEL_CLOCK_MIN_SPREAD)
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
#define GET_FREE_RUN_DDOMAIN_SETTING()                          (g_stDisplayCustomizedData.enumFreeRunDdomainSetting)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplaySetDVFreq(void);

#if(_PANEL_STYLE == _PANEL_LVDS)
extern bit ScalerDisplayGetLvdsPllPowerStatus(void);
extern void ScalerDisplayLvdsInitialTable(void);
extern void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
extern void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
extern void ScalerDisplayLvdsSetDspcControl(void);
#endif

extern bit ScalerDisplayGetPllPowerStatus(void);

