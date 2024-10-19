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
// ID Code      : RL6829_Gen_Option_D_Domain.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//-------------------------------------------------
// DPLL Min Pixel Clk Divider
//-------------------------------------------------
#define _HW_DPLL_MIN_PIX_CLK_DIV                                _DPLL_DIV1

//--------------------------------------------------
// DPLL vcorstb setting
//--------------------------------------------------
#define _HW_DPLL_VCORSTB_NORMAL_VALUE                           0
#define GET_N_F_PLL_PREDIVIDER()                                (ScalerGetByte(P1_C9_DPLL_CLK_CTRL_1) + 2)

//-------------------------------------------------
// DPLL Structure
//-------------------------------------------------
#define _HW_DPLL_STRUCT_TYPE                                    _DPLL_STRUCT_N_F

//-------------------------------------------------
// DVS Timeout  IRQ
//-------------------------------------------------
#define _HW_DVS_TIMEOUT_IRQ_SUPPORT                             _ON

//-------------------------------------------------
// LINE BUFFER START ADDRESS
//-------------------------------------------------
#define _HW_ADJ_A1_LB_START_ADDR                                _ON

//--------------------------------------------------
// DDOMAIN ACTIVE REGION
//--------------------------------------------------
#define _HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT                       _ON

#define _HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT                       ((_2P_PBP_TB_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_SKEW_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_SKEW_TB_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON))

#define _HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT                       ((_2P_PIP_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_EAGLE_SIGHT_SUPPORT == _ON) ||\
                                                                 (_2P_PBP_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON))

#define _HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT                       ((_3P_SKEW_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_SKEW_TB_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON))

#define _HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT                       _ON

#define _HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT                       _OFF

#define _HW_D_DOMAIN_R1_BACKGROUND_SUPPORT                      _ON

#define _HW_D_DOMAIN_R2_BACKGROUND_SUPPORT                      ((_2P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON))

#define _HW_D_DOMAIN_R3_BACKGROUND_SUPPORT                      _ON
