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
// ID Code      : ScalerDpRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Macro of DP Main Input Port
//--------------------------------------------------
#define GET_DP_RX_MAIN_PORT()                                           (g_enumDpRxMainPort)
#define SET_DP_RX_MAIN_PORT(x)                                          (g_enumDpRxMainPort = (x))

//--------------------------------------------------
// Definitions of DP Base Port
//--------------------------------------------------
#define GET_DP_RX_BASE_PORT()                                           (g_enumDpRxBaseInputPort)
#define SET_DP_RX_BASE_PORT(x)                                          (g_enumDpRxBaseInputPort = (x))

//--------------------------------------------------
//  DP LEQ RELOAD Define
//--------------------------------------------------
#define _DP_RX_RELOAD_LEQ_INITIAL                                       0
#define _DP_RX_RELOAD_LEQ_LARGE                                         1
#define _DP_RX_RELOAD_LEQ_DEFAULT                                       2

//--------------------------------------------------
// Definitions of Signal Detection Target Value
//--------------------------------------------------
#define _DP_RX_VCO_TARGET_COUNT_1000_RBR                                (WORD)(((DWORD)(_DP_LINK_RBR * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR                                (WORD)(((DWORD)(_DP_LINK_HBR * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR2                               (WORD)(((DWORD)(_DP_LINK_HBR2 * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR3                               (WORD)(((DWORD)(_DP_LINK_HBR3 * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G                            (WORD)(((DWORD)(_DP_LINK_HBR3_9G * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)

#define _DP_RX_VCO_TARGET_COUNT_2000_RBR                                (WORD)(((DWORD)(_DP_LINK_RBR * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR                                (WORD)(((DWORD)(_DP_LINK_HBR * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR2                               (WORD)(((DWORD)(_DP_LINK_HBR2 * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR3                               (WORD)(((DWORD)(_DP_LINK_HBR3 * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G                            (WORD)(((DWORD)(_DP_LINK_HBR3_9G * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)

#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_RBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_RBR * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR2                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR2 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR3                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR3_9G               (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G * 65) / 100)

#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_RBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_RBR * 55) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR * 55) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR2                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR2 * 55) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR3                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3 * 55) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR3_9G               (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G * 55) / 100)

#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_RBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_RBR * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR2                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR2 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR3                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR3_9G               (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G * 65) / 100)

#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_RBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_RBR * 40) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR                   (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR * 40) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR2                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR2 * 40) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR3                  (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3 * 40) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR3_9G               (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G * 40) / 100)

#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR                 (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_RBR * 102) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR                 (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR * 102) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR2 * 102) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3 * 102) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_9G             (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G * 102) / 100)

#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR                 (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_RBR * 98) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR                 (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR * 98) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR2 * 98) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3 * 98) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_9G             (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G * 98) / 100)

#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_RBR                           (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_RBR * 106) / 100)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR                           (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR * 106) / 100)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR2                          (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR2 * 106) / 100)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3                          (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3 * 106) / 100)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_9G                       (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G * 106) / 100)

#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_RBR                           (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_RBR * 94) / 100)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR                           (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR * 94) / 100)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR2                          (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR2 * 94) / 100)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3                          (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3 * 94) / 100)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_9G                       (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G * 94) / 100)

#define _DP_RX_VCO_TARGET_COUNT_1000_RBR_SAVED                          (g_usDpRxVcoCount1000RBR)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR_SAVED                          (g_usDpRxVcoCount1000HBR)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR2_SAVED                         (g_usDpRxVcoCount1000HBR2)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR3_SAVED                         (g_usDpRxVcoCount1000HBR3)
#define _DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G_SAVED                      (g_usDpRxVcoCount1000HBR3_9G)

#define _DP_RX_VCO_TARGET_COUNT_2000_RBR_SAVED                          (g_usDpRxVcoCount2000RBR)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR_SAVED                          (g_usDpRxVcoCount2000HBR)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR2_SAVED                         (g_usDpRxVcoCount2000HBR2)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR3_SAVED                         (g_usDpRxVcoCount2000HBR3)
#define _DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G_SAVED                      (g_usDpRxVcoCount2000HBR3_9G)

#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED                     (g_usDpRxCountSSTUpperBound2000RBR)
#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED                     (g_usDpRxCountSSTUpperBound2000HBR)
#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED                    (g_usDpRxCountSSTUpperBound2000HBR2)
#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR3_SAVED                    (g_usDpRxCountSSTUpperBound2000HBR3)
#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR3_9G_SAVED                 (g_usDpRxCountSSTUpperBound2000HBR3_9G)

#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED                     (g_usDpRxCountSSTLowerBound2000RBR)
#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED                     (g_usDpRxCountSSTLowerBound2000HBR)
#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED                    (g_usDpRxCountSSTLowerBound2000HBR2)
#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR3_SAVED                    (g_usDpRxCountSSTLowerBound2000HBR3)
#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR3_9G_SAVED                 (g_usDpRxCountSSTLowerBound2000HBR3_9G)

#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_RBR_SAVED                     (g_usDpRxCountMSTUpperBound2000RBR)
#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_HBR_SAVED                     (g_usDpRxCountMSTUpperBound2000HBR)
#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_HBR2_SAVED                    (g_usDpRxCountMSTUpperBound2000HBR2)
#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_HBR3_SAVED                    (g_usDpRxCountMSTUpperBound2000HBR3)
#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_HBR3_9G_SAVED                 (g_usDpRxCountMSTUpperBound2000HBR3_9G)

#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_RBR_SAVED                     (g_usDpRxCountMSTLowerBound2000RBR)
#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_HBR_SAVED                     (g_usDpRxCountMSTLowerBound2000HBR)
#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_HBR2_SAVED                    (g_usDpRxCountMSTLowerBound2000HBR2)
#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_HBR3_SAVED                    (g_usDpRxCountMSTLowerBound2000HBR3)
#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_HBR3_9G_SAVED                 (g_usDpRxCountMSTLowerBound2000HBR3_9G)

#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_RBR_SAVED                   (g_usDpRxCountD10P2UpperBound1000RBR)
#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_HBR_SAVED                   (g_usDpRxCountD10P2UpperBound1000HBR)
#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_HBR2_SAVED                  (g_usDpRxCountD10P2UpperBound1000HBR2)
#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_HBR3_SAVED                  (g_usDpRxCountD10P2UpperBound1000HBR3)
#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_HBR3_9G_SAVED               (g_usDpRxCountD10P2UpperBound1000HBR3_9G)

#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_RBR_SAVED                   (g_usDpRxCountD10P2LowerBound1000RBR)
#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_HBR_SAVED                   (g_usDpRxCountD10P2LowerBound1000HBR)
#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_HBR2_SAVED                  (g_usDpRxCountD10P2LowerBound1000HBR2)
#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_HBR3_SAVED                  (g_usDpRxCountD10P2LowerBound1000HBR3)
#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_HBR3_9G_SAVED               (g_usDpRxCountD10P2LowerBound1000HBR3_9G)

#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_RBR_SAVED                     (g_usDpRxCountUpperBound1000RBR)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR_SAVED                     (g_usDpRxCountUpperBound1000HBR)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR2_SAVED                    (g_usDpRxCountUpperBound1000HBR2)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_SAVED                    (g_usDpRxCountUpperBound1000HBR3)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_9G_SAVED                 (g_usDpRxCountUpperBound1000HBR3_9G)

#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_RBR_SAVED                     (g_usDpRxCountLowerBound1000RBR)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR_SAVED                     (g_usDpRxCountLowerBound1000HBR)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR2_SAVED                    (g_usDpRxCountLowerBound1000HBR2)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_SAVED                    (g_usDpRxCountLowerBound1000HBR3)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_9G_SAVED                 (g_usDpRxCountLowerBound1000HBR3_9G)

#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR_EXINT0          (g_usDpPhyRxD10p2CountCriteriaUpperBoundRBR)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR_EXINT0          (g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2_EXINT0         (g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR2)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_EXINT0         (g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_9G_EXINT0      (g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3_9G)

#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_RBR_EXINT0                    (g_usDpPhyRxVCOCountCriteriaUpperBoundRBR)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR_EXINT0                    (g_usDpPhyRxVCOCountCriteriaUpperBoundHBR)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR2_EXINT0                   (g_usDpPhyRxVCOCountCriteriaUpperBoundHBR2)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_EXINT0                   (g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_9G_EXINT0                (g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3_9G)

#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR_EXINT0          (g_usDpPhyRxD10p2CountCriteriaLowerBoundRBR)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR_EXINT0          (g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2_EXINT0         (g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR2)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_EXINT0         (g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_9G_EXINT0      (g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3_9G)

#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_RBR_EXINT0                    (g_usDpPhyRxVCOCountCriteriaLowerBoundRBR)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR_EXINT0                    (g_usDpPhyRxVCOCountCriteriaLowerBoundHBR)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR2_EXINT0                   (g_usDpPhyRxVCOCountCriteriaLowerBoundHBR2)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_EXINT0                   (g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_9G_EXINT0                (g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3_9G)

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define _DP_RX_VCO_TARGET_COUNT_1000_UHBR10                             (WORD)(((DWORD)(_DP_LINK_UHBR10 * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5                           (WORD)(((DWORD)(_DP_LINK_UHBR13_5 * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_1000_UHBR20                             (WORD)(((DWORD)(_DP_LINK_UHBR20 * 27 / 2) * 1000000) / _GDIPHY_RX_GDI_CLK_KHZ)

#define _DP_RX_VCO_TARGET_COUNT_2000_UHBR10                             (WORD)(((DWORD)(_DP_LINK_UHBR10 * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5                           (WORD)(((DWORD)(_DP_LINK_UHBR13_5 * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)
#define _DP_RX_VCO_TARGET_COUNT_2000_UHBR20                             (WORD)(((DWORD)(_DP_LINK_UHBR20 * 27 / 2) * 1000000 * 2) / _GDIPHY_RX_GDI_CLK_KHZ)

#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_UHBR10                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR10 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_UHBR13_5              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_UPPER_BOUND_2000_UHBR20                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR20 * 65) / 100)

#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_UHBR10                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR10 * 55) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_UHBR13_5              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5 * 55) / 100)
#define _DP_RX_RAWDATA_COUNT_SST_LOWER_BOUND_2000_UHBR20                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR20 * 55) / 100)

#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_UHBR10                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR10 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_UHBR13_5              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5 * 65) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_UPPER_BOUND_2000_UHBR20                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR20 * 65) / 100)

#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_UHBR10                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR10 * 40) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_UHBR13_5              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5 * 40) / 100)
#define _DP_RX_RAWDATA_COUNT_MST_LOWER_BOUND_2000_UHBR20                (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_2000_UHBR20 * 40) / 100)

#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR10              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR10 * 110) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR13_5            (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5 * 110) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR20              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR20 * 110) / 100)

#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR10              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR10 * 90) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR13_5            (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5 * 90) / 100)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR20              (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR20 * 90) / 100)

#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR10                        (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR10 * 106) / 100)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR13_5                      (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5 * 106) / 100)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR20                        (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR20 * 106) / 100)

#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR10                        (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR10 * 94) / 100)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR13_5                      (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5 * 94) / 100)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR20                        (WORD)(((DWORD)_DP_RX_VCO_TARGET_COUNT_1000_UHBR20 * 94) / 100)

#define _DP_RX_VCO_TARGET_COUNT_1000_UHBR10_SAVED                       (g_usDpRxVcoCount1000UHBR10)
#define _DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5_SAVED                     (g_usDpRxVcoCount1000UHBR13_5)
#define _DP_RX_VCO_TARGET_COUNT_1000_UHBR20_SAVED                       (g_usDpRxVcoCount1000UHBR20)

#define _DP_RX_VCO_TARGET_COUNT_2000_UHBR10_SAVED                       (g_usDpRxVcoCount2000UHBR10)
#define _DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5_SAVED                     (g_usDpRxVcoCount2000UHBR13_5)
#define _DP_RX_VCO_TARGET_COUNT_2000_UHBR20_SAVED                       (g_usDpRxVcoCount2000UHBR20)

#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_UHBR10_SAVED                  (g_usDpRxCountSSTUpperBound2000UHBR10)
#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_UHBR13_5_SAVED                (g_usDpRxCountSSTUpperBound2000UHBR13_5)
#define _DP_RX_COUNT_SST_UPPER_BOUND_2000_UHBR20_SAVED                  (g_usDpRxCountSSTUpperBound2000UHBR20)

#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_UHBR10_SAVED                  (g_usDpRxCountSSTLowerBound2000UHBR10)
#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_UHBR13_5_SAVED                (g_usDpRxCountSSTLowerBound2000UHBR13_5)
#define _DP_RX_COUNT_SST_LOWER_BOUND_2000_UHBR20_SAVED                  (g_usDpRxCountSSTLowerBound2000UHBR20)

#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_UHBR10_SAVED                  (g_usDpRxCountMSTUpperBound2000UHBR10)
#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_UHBR13_5_SAVED                (g_usDpRxCountMSTUpperBound2000UHBR13_5)
#define _DP_RX_COUNT_MST_UPPER_BOUND_2000_UHBR20_SAVED                  (g_usDpRxCountMSTUpperBound2000UHBR20)

#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_UHBR10_SAVED                  (g_usDpRxCountMSTLowerBound2000UHBR10)
#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_UHBR13_5_SAVED                (g_usDpRxCountMSTLowerBound2000UHBR13_5)
#define _DP_RX_COUNT_MST_LOWER_BOUND_2000_UHBR20_SAVED                  (g_usDpRxCountMSTLowerBound2000UHBR20)

#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_UHBR10_SAVED                (g_usDpRxCountD10P2UpperBound1000UHBR10)
#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_UHBR13_5_SAVED              (g_usDpRxCountD10P2UpperBound1000UHBR13_5)
#define _DP_RX_COUNT_D10P2_UPPER_BOUND_1000_UHBR20_SAVED                (g_usDpRxCountD10P2UpperBound1000UHBR20)

#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_UHBR10_SAVED                (g_usDpRxCountD10P2LowerBound1000UHBR10)
#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_UHBR13_5_SAVED              (g_usDpRxCountD10P2LowerBound1000UHBR13_5)
#define _DP_RX_COUNT_D10P2_LOWER_BOUND_1000_UHBR20_SAVED                (g_usDpRxCountD10P2LowerBound1000UHBR20)

#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR10_SAVED                  (g_usDpRxCountUpperBound1000UHBR10)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR13_5_SAVED                (g_usDpRxCountUpperBound1000UHBR13_5)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR20_SAVED                  (g_usDpRxCountUpperBound1000UHBR20)

#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR10_SAVED                  (g_usDpRxCountLowerBound1000UHBR10)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR13_5_SAVED                (g_usDpRxCountLowerBound1000UHBR13_5)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR20_SAVED                  (g_usDpRxCountLowerBound1000UHBR20)

#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR10_EXINT0       (g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR10)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR13_5_EXINT0     (g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR13_5)
#define _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR20_EXINT0       (g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR20)

#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR10_EXINT0                 (g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR10)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR13_5_EXINT0               (g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR13_5)
#define _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR20_EXINT0                 (g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR20)

#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR10_EXINT0       (g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR10)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR13_5_EXINT0     (g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR13_5)
#define _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR20_EXINT0       (g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR20)

#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR10_EXINT0                 (g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR10)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR13_5_EXINT0               (g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR13_5)
#define _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR20_EXINT0                 (g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR20)
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
#define GET_DP_PR_MODE_D0_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD0Enable)
#define SET_DP_PR_MODE_D0_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD0Enable = _TRUE)
#define CLR_DP_PR_MODE_D0_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD0Enable = _FALSE)

#define GET_DP_PR_MODE_D1_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD1Enable)
#define SET_DP_PR_MODE_D1_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD1Enable = _TRUE)
#define CLR_DP_PR_MODE_D1_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD1Enable = _FALSE)

#define GET_DP_PR_MODE_D2_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD2Enable)
#define SET_DP_PR_MODE_D2_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD2Enable = _TRUE)
#define CLR_DP_PR_MODE_D2_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD2Enable = _FALSE)

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#define GET_DP_PR_MODE_D9_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD9Enable)
#define SET_DP_PR_MODE_D9_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD9Enable = _TRUE)
#define CLR_DP_PR_MODE_D9_ENABLE()                                      (g_stDpRxPRModeInfo.b1DpD9Enable = _FALSE)
#endif

#define GET_DP_PR_MODE_D0_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD0CapabilitySwitch)
#define SET_DP_PR_MODE_D0_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD0CapabilitySwitch = _TRUE)
#define CLR_DP_PR_MODE_D0_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD0CapabilitySwitch = _FALSE)

#define GET_DP_PR_MODE_D1_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD1CapabilitySwitch)
#define SET_DP_PR_MODE_D1_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD1CapabilitySwitch = _TRUE)
#define CLR_DP_PR_MODE_D1_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD1CapabilitySwitch = _FALSE)

#define GET_DP_PR_MODE_D2_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD2CapabilitySwitch)
#define SET_DP_PR_MODE_D2_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD2CapabilitySwitch = _TRUE)
#define CLR_DP_PR_MODE_D2_CAPABILITY_SWITCH()                           (g_stDpRxPRModeInfo.b1DpD2CapabilitySwitch = _FALSE)
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define GET_DP_AUXLESS_ALPM_D0_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0Enable)
#define SET_DP_AUXLESS_ALPM_D0_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0Enable = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D0_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0Enable = _FALSE)

#define GET_DP_AUXLESS_ALPM_D1_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1Enable)
#define SET_DP_AUXLESS_ALPM_D1_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1Enable = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D1_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1Enable = _FALSE)

#define GET_DP_AUXLESS_ALPM_D2_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2Enable)
#define SET_DP_AUXLESS_ALPM_D2_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2Enable = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D2_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2Enable = _FALSE)

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#define GET_DP_AUXLESS_ALPM_D9_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD9Enable)
#define SET_DP_AUXLESS_ALPM_D9_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD9Enable = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D9_ENABLE()                                 (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD9Enable = _FALSE)
#endif

#define GET_DP_AUXLESS_ALPM_D0_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0CapabilitySwitch)
#define SET_DP_AUXLESS_ALPM_D0_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0CapabilitySwitch = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D0_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0CapabilitySwitch = _FALSE)

#define GET_DP_AUXLESS_ALPM_D1_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1CapabilitySwitch)
#define SET_DP_AUXLESS_ALPM_D1_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1CapabilitySwitch = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D1_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1CapabilitySwitch = _FALSE)

#define GET_DP_AUXLESS_ALPM_D2_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2CapabilitySwitch)
#define SET_DP_AUXLESS_ALPM_D2_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2CapabilitySwitch = _TRUE)
#define CLR_DP_AUXLESS_ALPM_D2_CAPABILITY_SWITCH()                      (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2CapabilitySwitch = _FALSE)

//--------------------------------------------------
// Definitions Auxless ALPM tDRL Time
// tDRL = 7 * ML_PHY_LOCK sequence time
// 8b10b TPS4 = 252 * 10 bit * 7 * Link Rate
// 128b132b TPS2 = 96 * 132 bit * 7 * Link Rate
//--------------------------------------------------
#define _DP_AUXLESS_ALPM_TDRL_TIME_RBR                                  0x498   // 10.89us * 108Mhz = 1176 = 0x498
#define _DP_AUXLESS_ALPM_TDRL_TIME_HBR                                  0x2C1   // 6.53us * 108Mhz = 705 = 0x2C1
#define _DP_AUXLESS_ALPM_TDRL_TIME_HBR2                                 0x160   // 3.267us * 108Mhz = 352 = 0x160
#define _DP_AUXLESS_ALPM_TDRL_TIME_HBR3                                 0xEB    // 2.178us * 108Mhz = 253 = 0xEB

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define _DP_AUXLESS_ALPM_TDRL_TIME_UHBR10                               0x3BE   // 8.87us * 108Mhz = 958 = 0x3BE
#define _DP_AUXLESS_ALPM_TDRL_TIME_UHBR13_5                             0x2C5   // 6.57us * 108Mhz = 709 = 0x2C5
#define _DP_AUXLESS_ALPM_TDRL_TIME_UHBR20                               0x1DF   // 4.435us * 108Mhz = 479 = 0x1DF
#endif
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
#define GET_DP_HDR_D0_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD0CapabilitySwitch)
#define SET_DP_HDR_D0_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD0CapabilitySwitch = _TRUE)
#define CLR_DP_HDR_D0_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD0CapabilitySwitch = _FALSE)

#define GET_DP_HDR_D1_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD1CapabilitySwitch)
#define SET_DP_HDR_D1_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD1CapabilitySwitch = _TRUE)
#define CLR_DP_HDR_D1_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD1CapabilitySwitch = _FALSE)

#define GET_DP_HDR_D2_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD2CapabilitySwitch)
#define SET_DP_HDR_D2_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD2CapabilitySwitch = _TRUE)
#define CLR_DP_HDR_D2_CAPABILITY_SWITCH()                               (g_stDpRxHdrInfo.b1DpD2CapabilitySwitch = _FALSE)
#endif
#endif

//--------------------------------------------------
// Macros of controlling scaler registers with offset address for DP
//--------------------------------------------------
#define SCALER32_DP_GET_OFFSET_DWORD(ulOffset, pulAddr)\
                                                                        (SCALER32_GET_OFFSET_DWORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000)))
#define SCALER32_DP_SET_OFFSET_DWORD(ulOffset, pulAddr, ulValue)\
                                                                        {SCALER32_SET_OFFSET_DWORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ulValue));}
#define SCALER32_DP_GET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex)\
                                                                        (SCALER32_GET_OFFSET_WORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucWordIndex)))
#define SCALER32_DP_SET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                                        {SCALER32_SET_OFFSET_WORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucWordIndex), (ulValue));}
#define SCALER32_DP_GET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex)\
                                                                        (SCALER32_GET_OFFSET_BYTE((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucIndex)))
#define SCALER32_DP_SET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex, ucValue)\
                                                                        {SCALER32_SET_OFFSET_BYTE((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucIndex), (ucValue));}
#define SCALER32_DP_GET_OFFSET_BIT(ulOffset, pulAddr, ulAnd)\
                                                                        (SCALER32_GET_OFFSET_BIT((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ulAnd)))
#define SCALER32_DP_SET_OFFSET_BIT(ulOffset, pulAddr, ulAnd, ulOr)\
                                                                        {SCALER32_SET_OFFSET_BIT((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ulAnd), (ulOr));}

#define SCALER32_DP_GET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr)\
                                                                        (SCALER32_GET_OFFSET_DWORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000)))
#define SCALER32_DP_SET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr, ulValue)\
                                                                        {SCALER32_SET_OFFSET_DWORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ulValue));}
#define SCALER32_DP_GET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex)\
                                                                        (SCALER32_GET_OFFSET_WORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucWordIndex)))
#define SCALER32_DP_SET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                                        {SCALER32_SET_OFFSET_WORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucWordIndex), (ulValue));}
#define SCALER32_DP_GET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex)\
                                                                        (SCALER32_GET_OFFSET_BYTE_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucIndex)))
#define SCALER32_DP_SET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex, ucValue)\
                                                                        {SCALER32_SET_OFFSET_BYTE_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ucIndex), (ucValue));}
#define SCALER32_DP_GET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd)\
                                                                        (SCALER32_GET_OFFSET_BIT_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ulAnd)))
#define SCALER32_DP_SET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd, ulOr)\
                                                                        {SCALER32_SET_OFFSET_BIT_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB1800000), (ulAnd), (ulOr));}

//--------------------------------------------------
// Macro of Hot Plug Event Assert Type
//--------------------------------------------------
#if(_D0_DP_SUPPORT == _ON)
#define GET_DP_RX0_HOTPLUG_ASSERT_TYPE()                                (g_stDpRxHpdType.enumD0HpdAssertType)
#define SET_DP_RX0_HOTPLUG_ASSERT_TYPE(x)                               (g_stDpRxHpdType.enumD0HpdAssertType = (x))
#define CLR_DP_RX0_HOTPLUG_ASSERT_TYPE()                                (g_stDpRxHpdType.enumD0HpdAssertType = _DP_HPD_NONE)
#endif

#if(_D1_DP_SUPPORT == _ON)
#define GET_DP_RX1_HOTPLUG_ASSERT_TYPE()                                (g_stDpRxHpdType.enumD1HpdAssertType)
#define SET_DP_RX1_HOTPLUG_ASSERT_TYPE(x)                               (g_stDpRxHpdType.enumD1HpdAssertType = (x))
#define CLR_DP_RX1_HOTPLUG_ASSERT_TYPE()                                (g_stDpRxHpdType.enumD1HpdAssertType = _DP_HPD_NONE)
#endif

#if(_D2_DP_SUPPORT == _ON)
#define GET_DP_RX2_HOTPLUG_ASSERT_TYPE()                                (g_stDpRxHpdType.enumD2HpdAssertType)
#define SET_DP_RX2_HOTPLUG_ASSERT_TYPE(x)                               (g_stDpRxHpdType.enumD2HpdAssertType = (x))
#define CLR_DP_RX2_HOTPLUG_ASSERT_TYPE()                                (g_stDpRxHpdType.enumD2HpdAssertType = _DP_HPD_NONE)
#endif

//--------------------------------------------------
// Macro of DP Timer2 IRQ Delay Counter
//--------------------------------------------------
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
#define DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL()                         (g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter = ((WORD)((95 - GET_DP_IRQ_TIME_10US()) * 10) >> 2))
#define DP_RX_HPD_IRQ_ASSERT_T2_DELAY()                                 {\
                                                                           if(g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter > 0)\
                                                                           {\
                                                                               ScalerDpAuxRxManualModeSetting_T2INT(_DP_AUX_MANUAL_MODE_SET);\
                                                                               do\
                                                                               {\
                                                                                   g_ucDpRxHpdIrqAssertT2EventDelay5usI = g_ucMcuDelayXusN_Base;\
                                                                                   while(--g_ucDpRxHpdIrqAssertT2EventDelay5usI) {};\
                                                                               }\
                                                                               while(--g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter);\
                                                                               ScalerDpAuxRxManualModeSetting_T2INT(_DP_AUX_MANUAL_MODE_RECOVER);\
                                                                           }\
                                                                        }
#endif

#define GET_DP_RX_GLOBAL_HIGH_PRIORITY_INT_FLAG()                       (ScalerGetBit_EXINT(P6F_19_ADI_DP_IRQ7, _BIT1) == _BIT1)
#define GET_DP_RX_GLOBAL_LOW_PRIORITY_INT_FLAG()                        (ScalerGetBit_EXINT(P6F_19_ADI_DP_IRQ7, _BIT0) == _BIT0)

#if(_DP_MST_SUPPORT == _ON)
#define GET_DP_RX_GLOBAL_AUX_MSG_INT_FLAG()                             (ScalerGetBit_EXINT(P6F_1B_ADI_DP_IRQ9, _BIT7) == _BIT7)
#endif

#define _DP_RX_SDP_META_SRAM_RESET_FW_MODE                              _OFF

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DP_MEASURE_TARGET_RAW_DATA = 0x00,
    _DP_MEASURE_TARGET_CDR_CLOCK = _BIT5,
} EnumDpMeasureTarget;

typedef enum
{
    _DP_MEASURE_PERIOD_125_CYCLE,
    _DP_MEASURE_PERIOD_250_CYCLE,
    _DP_MEASURE_PERIOD_1000_CYCLE,
    _DP_MEASURE_PERIOD_2000_CYCLE,
} EnumDpMeasurePeriod;

typedef enum
{
    _DP_MAC_CLOCK_SELECT_LINK_CLOCK = 0x00,
    _DP_MAC_CLOCK_SELECT_XTAL_CLOCK = _BIT6,
} EnumDpMacClkSelect;

typedef enum
{
    _DP_MAC_DECODE_METHOD_PRBS7,
    _DP_MAC_DECODE_METHOD_PRBS31,
    _DP_MAC_DECODE_METHOD_8B10B,
    _DP_MAC_DECODE_METHOD_8B10B_DISPARITY,
} EnumDpMacDecodeMethod;

//--------------------------------------------------
// Enumerations for DP training Pattern 1 FLD Reference Clock Select
//--------------------------------------------------
typedef enum
{
    _DP_NF_REF_XTAL = 0x00,
    _DP_NF_REF_D10_2,
} EnumDpNFCodeRef;

//--------------------------------------------------
// Enumerations of DP Link Training Type
//--------------------------------------------------
typedef enum
{
    _DP_NORMAL_LT = 0x00,
    _DP_FAKE_LT,
} EnumDpLinkTrainingType;

//--------------------------------------------------
// Enumerations of DP Fifo Check Condition
//--------------------------------------------------
typedef enum
{
    _DP_FIFO_DELAY_CHECK = 0x00,
    _DP_FIFO_POLLING_CHECK,
} EnumDpFifoCheckCondition;

//--------------------------------------------------
// Enumerations of DP HS Tracking Type
//--------------------------------------------------
typedef enum
{
    _DP_HS_TRACKING_HW_MODE = 0x00,
    _DP_HS_TRACKING_FW_MODE,
} EnumDpHSTrackingType;

//--------------------------------------------------
// Enumerations of DP HS Tracking Select
//--------------------------------------------------
typedef enum
{
    _DP_BS_TRACKING = 0x00,
    _DP_BE_TRACKING,
} EnumDpHSTrackingSelect;

//--------------------------------------------------
// Enumerations of DP Tracking Mode
//--------------------------------------------------
typedef enum
{
    _DP_TRACKING_FAST_LOCK_MODE = 0x00,
    _DP_TRACKING_PRECISION_MODE,
} EnumDpTrackingMode;

//--------------------------------------------------
// Enumerations of DP Sink Reveive Port
//--------------------------------------------------
typedef enum
{
    _DP_SINK_REVEICE_PORT0 = 0x00,
    _DP_SINK_REVEICE_PORT1,
    _DP_SINK_REVEICE_PORT2,
    _DP_STREAM_REGENERATION_STATUS,
} EnumDpSinkReceivePort;

//--------------------------------------------------
// Enumerations of DP Sink Status
//--------------------------------------------------
typedef enum
{
    _DP_SINK_OUT_OF_SYNC = 0x00,
    _DP_SINK_IN_SYNC,
} EnumDpSinkStatus;

//--------------------------------------------------
// Definitions of DP TRAINING_AUX_RD_INTERVAL
//--------------------------------------------------
typedef enum
{
    _DP_LT_AUX_RD_INTVL_EQ_400US = 0x00,
    _DP_LT_AUX_RD_INTVL_EQ_4MS = 0x01,
    _DP_LT_AUX_RD_INTVL_EQ_8MS = 0x02,
    _DP_LT_AUX_RD_INTVL_EQ_12MS = 0x03,
    _DP_LT_AUX_RD_INTVL_EQ_16MS = 0x04,
} EnumDpLTAuxRdIntvlEq;

//--------------------------------------------------
// Definitions of DP VBID Information
//--------------------------------------------------
typedef enum
{
    _DP_VBID_INTERLACE_MODE = 0x00,
    _DP_VBID_VIDEO_STREAM,
    _DP_VBID_DSC_STREAM,
    _DP_VBID_AUDIO_STREAM,
} EnumDpVbidInfo;

//--------------------------------------------------
// Definitions of DP Display Format Information
//--------------------------------------------------
typedef enum
{
    _DP_V_HEIGHT = 0x00,
    _DP_H_WIDTH,
    _DP_H_START,
} EnumDpDisplayFormatInfo;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP Cable Attributes Capability
//--------------------------------------------------
typedef enum
{
    _DP_CABLE_NON_UHBR_CAPABLE = 0x00,
    _DP_CABLE_UHBR10_CAPABLE = _BIT0,
    _DP_CABLE_UHBR20_AND_UHBR10_CAPABLE = _BIT1,
    _DP_CABLE_UHBR135_CAPABLE = _BIT2,
} EnumDpCableIDInfo;

//--------------------------------------------------
// Definitions of DP Cable Types
//--------------------------------------------------
typedef enum
{
    _DP_CABLE_UNKNOW_TYPE = 0x00,
    _DP_CABLE_PASSIVE_TYPE = _BIT3,
    _DP_CABLE_ACTIVE_LRD_TYPE = _BIT4,
    _DP_CABLE_ACCTIVE_RETIMER_TYPE = (_BIT3 | _BIT4),
} EnumDpCableTypeInfo;
#endif

//--------------------------------------------------
// Struct of DP Cable Status
//--------------------------------------------------
typedef struct
{
#if(_D0_DP_SUPPORT == _ON)
    BYTE b1D0Status : 1;
#endif
#if(_D1_DP_SUPPORT == _ON)
    BYTE b1D1Status : 1;
#endif
#if(_D2_DP_SUPPORT == _ON)
    BYTE b1D2Status : 1;
#endif
} StructDpCableStatus;

//--------------------------------------------------
// Structure of DP Port Hot Plug Assert Type
//--------------------------------------------------
typedef struct
{
#if(_D0_DP_SUPPORT == _ON)
    EnumDpHotPlugAssertType enumD0HpdAssertType;
#endif
#if(_D1_DP_SUPPORT == _ON)
    EnumDpHotPlugAssertType enumD1HpdAssertType;
#endif
#if(_D2_DP_SUPPORT == _ON)
    EnumDpHotPlugAssertType enumD2HpdAssertType;
#endif
} StructDpPortHpdAssertType;

typedef enum
{
    _DP_LONG_HPD_TIME = _USER_DP_LONG_HPD_TIME_VALUE,
    _DP_HDCP_LONG_HPD_TIME = _USER_DP_HDCP_LONG_HPD_TIME_VALUE,
    _DP_MST_LONG_HPD_TIME = 800,
    _DP_MARGIN_LINK_HPD_TIME = 800,
    _DP_MST_FORCE_LONG_HPD_TIME = 5000,
    _DP_HPD_ASSERTED_TIME = 0,
    _DP_HPD_TIME_NONE = 0xFFFF,
} EnumDpHotPlugTime;

//--------------------------------------------------
// Structure of DP Port Hot Plug Time
//--------------------------------------------------
typedef struct
{
#if(_D0_DP_SUPPORT == _ON)
    EnumDpHotPlugTime enumD0HpdTime;
#endif
#if(_D1_DP_SUPPORT == _ON)
    EnumDpHotPlugTime enumD1HpdTime;
#endif
#if(_D2_DP_SUPPORT == _ON)
    EnumDpHotPlugTime enumD2HpdTime;
#endif
} StructDpPortHpdTime;

//--------------------------------------------------
// Struct of HPD Sequence for HotPlugHandler
//--------------------------------------------------
typedef struct
{
    EnumInputPort enumInputPort;
    EnumDpHotPlugTime enumHpdTime;
} StructHpdSequence;

//--------------------------------------------------
// Struct of DP HPD Status
//--------------------------------------------------
typedef struct
{
#if(_D0_DP_SUPPORT == _ON)
    BYTE b1D0Status : 1;
#endif
#if(_D1_DP_SUPPORT == _ON)
    BYTE b1D1Status : 1;
#endif
#if(_D2_DP_SUPPORT == _ON)
    BYTE b1D2Status : 1;
#endif
} StructDpRxHpdStatus;

//--------------------------------------------------
// Definitions of DP Source Write 600h = 0x01 Status
//--------------------------------------------------
typedef enum
{
    _DP_SOURCE_WRITE_POWER_UP_NONE,
    _DP_SOURCE_WRITE_POWER_UP_TRIGGERED,
    _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE,
} EnumDpSourceWritePowerUpState;

//--------------------------------------------------
// AUX Channel Power Status
//--------------------------------------------------
typedef enum
{
    _DP_RX_AUX_POWER_STATUS_NONE,
    _DP_RX_AUX_POWER_STATUS_ON,
    _DP_RX_AUX_POWER_STATUS_OFF,
} EnumDpRxAuxPowerStatus;

//--------------------------------------------------
// Struct for RX Aux Ch Power Detect
//--------------------------------------------------
typedef struct
{
    BYTE b1DpCheckAuxChNoPowerDebounce : 1;
    BYTE b1DpAuxChPowerOnWakeUp : 1;
    EnumDpRxAuxPowerStatus b2DpCheckAuxChPowerStatus : 2;
    BYTE b1DpSourceFirstPowerOn : 1;
    EnumDpSourceWritePowerUpState enumDpSourceWritePowerUp;
} StructDpRxAuxPowerInfo;

//--------------------------------------------------
//  DP Rx Pixel Mode
//--------------------------------------------------
typedef enum
{
    _DP_RX_MAC_PIXEL_MODE_NONE,
    _DP_RX_MAC_ONE_PIXEL_MODE,
    _DP_RX_MAC_TWO_PIXEL_MODE,
    _DP_RX_MAC_FOUR_PIXEL_MODE,
} EnumDpRxMacPixelMode;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDpRxHpdStatus g_stDpRxHpdStatus;
extern EnumInputPort g_enumDpRxMainPort;

extern BYTE g_pucDpRxEN[4];
extern WORD g_pusDpRxST[64];

extern WORD g_usDpRxVcoCount1000RBR;
extern WORD g_usDpRxVcoCount1000HBR;
extern WORD g_usDpRxVcoCount1000HBR2;
extern WORD g_usDpRxVcoCount1000HBR3;
extern WORD g_usDpRxVcoCount1000HBR3_9G;

extern WORD g_usDpRxVcoCount2000RBR;
extern WORD g_usDpRxVcoCount2000HBR;
extern WORD g_usDpRxVcoCount2000HBR2;
extern WORD g_usDpRxVcoCount2000HBR3;
extern WORD g_usDpRxVcoCount2000HBR3_9G;

extern WORD g_usDpRxCountSSTUpperBound2000RBR;
extern WORD g_usDpRxCountSSTUpperBound2000HBR;
extern WORD g_usDpRxCountSSTUpperBound2000HBR2;
extern WORD g_usDpRxCountSSTUpperBound2000HBR3;
extern WORD g_usDpRxCountSSTUpperBound2000HBR3_9G;

extern WORD g_usDpRxCountSSTLowerBound2000RBR;
extern WORD g_usDpRxCountSSTLowerBound2000HBR;
extern WORD g_usDpRxCountSSTLowerBound2000HBR2;
extern WORD g_usDpRxCountSSTLowerBound2000HBR3;
extern WORD g_usDpRxCountSSTLowerBound2000HBR3_9G;

extern WORD g_usDpRxCountMSTUpperBound2000RBR;
extern WORD g_usDpRxCountMSTUpperBound2000HBR;
extern WORD g_usDpRxCountMSTUpperBound2000HBR2;
extern WORD g_usDpRxCountMSTUpperBound2000HBR3;
extern WORD g_usDpRxCountMSTUpperBound2000HBR3_9G;

extern WORD g_usDpRxCountMSTLowerBound2000RBR;
extern WORD g_usDpRxCountMSTLowerBound2000HBR;
extern WORD g_usDpRxCountMSTLowerBound2000HBR2;
extern WORD g_usDpRxCountMSTLowerBound2000HBR3;
extern WORD g_usDpRxCountMSTLowerBound2000HBR3_9G;

extern WORD g_usDpRxCountD10P2UpperBound1000RBR;
extern WORD g_usDpRxCountD10P2UpperBound1000HBR;
extern WORD g_usDpRxCountD10P2UpperBound1000HBR2;
extern WORD g_usDpRxCountD10P2UpperBound1000HBR3;
extern WORD g_usDpRxCountD10P2UpperBound1000HBR3_9G;

extern WORD g_usDpRxCountD10P2LowerBound1000RBR;
extern WORD g_usDpRxCountD10P2LowerBound1000HBR;
extern WORD g_usDpRxCountD10P2LowerBound1000HBR2;
extern WORD g_usDpRxCountD10P2LowerBound1000HBR3;
extern WORD g_usDpRxCountD10P2LowerBound1000HBR3_9G;

extern WORD g_usDpRxCountUpperBound1000RBR;
extern WORD g_usDpRxCountUpperBound1000HBR;
extern WORD g_usDpRxCountUpperBound1000HBR2;
extern WORD g_usDpRxCountUpperBound1000HBR3;
extern WORD g_usDpRxCountUpperBound1000HBR3_9G;

extern WORD g_usDpRxCountLowerBound1000RBR;
extern WORD g_usDpRxCountLowerBound1000HBR;
extern WORD g_usDpRxCountLowerBound1000HBR2;
extern WORD g_usDpRxCountLowerBound1000HBR3;
extern WORD g_usDpRxCountLowerBound1000HBR3_9G;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern WORD g_usDpRxVcoCount1000UHBR10;
extern WORD g_usDpRxVcoCount1000UHBR13_5;
extern WORD g_usDpRxVcoCount1000UHBR20;

extern WORD g_usDpRxVcoCount2000UHBR10;
extern WORD g_usDpRxVcoCount2000UHBR13_5;
extern WORD g_usDpRxVcoCount2000UHBR20;

extern WORD g_usDpRxCountSSTUpperBound2000UHBR10;
extern WORD g_usDpRxCountSSTUpperBound2000UHBR13_5;
extern WORD g_usDpRxCountSSTUpperBound2000UHBR20;

extern WORD g_usDpRxCountSSTLowerBound2000UHBR10;
extern WORD g_usDpRxCountSSTLowerBound2000UHBR13_5;
extern WORD g_usDpRxCountSSTLowerBound2000UHBR20;

extern WORD g_usDpRxCountMSTUpperBound2000UHBR10;
extern WORD g_usDpRxCountMSTUpperBound2000UHBR13_5;
extern WORD g_usDpRxCountMSTUpperBound2000UHBR20;

extern WORD g_usDpRxCountMSTLowerBound2000UHBR10;
extern WORD g_usDpRxCountMSTLowerBound2000UHBR13_5;
extern WORD g_usDpRxCountMSTLowerBound2000UHBR20;

extern WORD g_usDpRxCountD10P2UpperBound1000UHBR10;
extern WORD g_usDpRxCountD10P2UpperBound1000UHBR13_5;
extern WORD g_usDpRxCountD10P2UpperBound1000UHBR20;

extern WORD g_usDpRxCountD10P2LowerBound1000UHBR10;
extern WORD g_usDpRxCountD10P2LowerBound1000UHBR13_5;
extern WORD g_usDpRxCountD10P2LowerBound1000UHBR20;

extern WORD g_usDpRxCountUpperBound1000UHBR10;
extern WORD g_usDpRxCountUpperBound1000UHBR13_5;
extern WORD g_usDpRxCountUpperBound1000UHBR20;

extern WORD g_usDpRxCountLowerBound1000UHBR10;
extern WORD g_usDpRxCountLowerBound1000UHBR13_5;
extern WORD g_usDpRxCountLowerBound1000UHBR20;
#endif

extern StructDpPortHpdAssertType g_stDpRxHpdType;

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern volatile BYTE data g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter;
extern BYTE data g_ucDpRxHpdIrqAssertT2EventDelay5usI;
#endif

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
extern EnumInputPort g_penumDpRxMacDphyEntityGroup[_DP_MAC_DPHY_ENTITY_MAX];
#endif

extern EnumDpMacStreamSourceType g_penumDpRxMacEntityGroup[_DP_MAC_ENTITY_MAX];

extern volatile EnumInputPort g_enumDpRxBaseInputPort;

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
extern bit g_bDpRx0LongHpdAllowed;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
extern bit g_bDpRx1LongHpdAllowed;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
extern bit g_bDpRx2LongHpdAllowed;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRxPhyInitial(void);
extern void ScalerDpRxMeasureCountInitial(void);
extern void ScalerDpRxSetInputPixelClock(EnumInputPort enumInputPort, DWORD ulStreamClk);
extern void ScalerDpRxSetNativeInputPixelClock(EnumInputPort enumInputPort, DWORD ulStreamClk);
extern WORD ScalerDpRxGetNativeInputPixelClock(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetHotPlugStatus_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpRxSetHotPlug(EnumInputPort enumInputPort, bit bHighLow, WORD usLongHpdDuration);
extern bit ScalerDpRxCableStatus_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetHotPlugPinDetect(EnumInputPort enumInputPort);
extern BYTE ScalerDpRxPllRsIcpCalculate(BYTE ucNcode);
extern void ScalerDpRxStreamColorimetryInfoSetting(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpRxStreamColorimetryExtInfoSetting(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpRxStreamQuantizationInfoSetting(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpRxConfigPinInitial(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
extern void ScalerDpRxSetPhyToMacDphyMux(EnumDpMacDphySel enumDpMacDphySel, EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern bit ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck(void);
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpRxCableIdProc(EnumInputPort enumInputPort);
#endif

extern void ScalerDpRxStreamExternInfoSetting(EnumInputPort enumInputPort);
extern void ScalerDpRxStreamAfterJudgeSetting(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_DPHY_CTS_FIFO_SUPPORT == _ON)
extern void ScalerDpRxMacDphyCtsFifoReset(EnumInputPort enumInputPort);
#endif

extern void ScalerDpRxHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpRxLowPriorityIntHandler_EXINT0(void);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRxAuxMsgIntHandler_EXINT0(void);
#endif

extern void ScalerDpRxBasePortBackup_EXINT0(void);
extern void ScalerDpRxBasePortRestore_EXINT0(void);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern void ScalerDpRxSetMarginLink(EnumInputPort enumInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRxDfpDeviceDetailConfigReset(EnumInputPort enumInputPort);
extern void ScalerDpRxDfpDeviceDetailConfig(EnumInputPort enumInputPort);
#endif

extern void ScalerDpRxPowerSwitch(EnumPowerAction enumPowerAction);

extern void ScalerDpRxSetBaseInputPort(EnumInputPort enumInputPort);
extern void ScalerDpRxSetBaseInputPort_EXINT0(EnumInputPort enumInputPort);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern EnumDpPRModeSupport ScalerDpRxPRModeGetSupport(EnumInputPort enumInputPort);
extern bit ScalerDpRxPRModepCapabilitySwitchProc(EnumInputPort enumInputPort);
extern bit ScalerDpRxPRModeGetEnable(EnumInputPort enumInputPort);
extern void ScalerDpRxPRModeSetEnable(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern EnumDpAuxlessAlpmSupport ScalerDpRxAuxlessAlpmGetSupport(EnumInputPort enumInputPort);
extern bit ScalerDpRxAuxlessAlpmCapabilitySwitchProc(EnumInputPort enumInputPort);
extern void ScalerDpRxAuxlessAlpmSetEnable(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDpRxAuxlessAlpmGetEnable(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpRxDscCancelPpsTimerEvent(EnumInputPort enumInputPort);
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void ScalerDpRxMacStreamArbiterMst2Sst(EnumInputPort enumMstMainPort);
#endif

#if(_DM_FUNCTION == _ON)
extern bit ScalerDpRxGetOsdDmSupport(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetDramReceiveFromDmDetect(EnumInputPort enumInputPort);
extern void ScalerDpRxClrDramReceiveFromDmDetect(EnumInputPort enumInputPort);
#endif
#endif

