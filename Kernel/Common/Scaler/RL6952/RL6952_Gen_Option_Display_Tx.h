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
// ID Code      : RL6952_Gen_Option_Display_Tx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//-------------------------------------------------
// HW Display DPTX Combo Type
//-------------------------------------------------
#define _HW_DISPLAY_DPTX_COMBO_TYPE                             _DISPLAY_VBO_COMBO_DPTX // Confirm

//-------------------------------------------------
// HW Display DPTX Type
//-------------------------------------------------
#define _HW_DISPLAY_DPTX_MULTI_SST_OPERATION                    _OFF // Modify, To Be Discuss
#define _HW_DISPLAY_DPTX_MAX_LANE_NUM                           _DISPLAY_DPTX_8_LANE

//-------------------------------------------------
// HW Display DPTX Type
//-------------------------------------------------
#define _HW_DISPLAY_DPTX0_SUPPORT                               _OFF
#define _HW_DISPLAY_DPTX1_SUPPORT                               _ON
#define _HW_DISPLAY_DPTX2_SUPPORT                               _ON
#define _HW_DISPLAY_DPTX3_SUPPORT                               _OFF

//-------------------------------------------------
// HW Display DPTX TPS1 BIT MODE
//-------------------------------------------------
#define _HW_DISPLAY_DPTX_TPS1_8_BIT_MODE                        _ON

//-------------------------------------------------
// HW Display VBO Type
//-------------------------------------------------
#define _HW_DISPLAY_VBO_MAX_LANE_NUM                            _VBO_8_DATA_LANE
#define _HW_DISPLAY_VBO_A_PHY_MAPPING_SWAP                      _DISABLE

//--------------------------------------------------
// Definations of VBOTX CMU CCO Range
//--------------------------------------------------
#define _HW_DISPLAY_VBOTX_PLL_BOUNDRY_0                         700000
#define _HW_DISPLAY_VBOTX_PLL_BOUNDRY_1                         1400000
#define _HW_DISPLAY_VBOTX_PLL_BOUNDRY_2                         2100000
#define _HW_DISPLAY_VBOTX_PLL_BOUNDRY_3                         2800000
