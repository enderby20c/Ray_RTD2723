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
// ID Code      : RL6952_Gen_Option_DSC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// HW Input Port Dx MAC MAPPING TO DSC (_DSC_MAC_0 | _DSC_MAC_1)
//--------------------------------------------------
#define _HW_D_MAC_RX_DSC_MAPPING                                (_DSC_MAC_1 | _DSC_MAC_0)

//--------------------------------------------------
// HW DSC MAC Maximum Throughput (Unit is 0.1 M)
//--------------------------------------------------
#define _HW_DSC_MAC_DEC_MAX_BW                                  3400
#define _HW_DSC_PLL_MAX_BOUNDARY                                7000
#define _HW_DSC_DATA_PATH_MAX_BOUNDARY                          MINOF(_HW_DSC_PLL_MAX_BOUNDARY, _HW_DATA_PATH_SPEED_LIMIT)

//--------------------------------------------------
// HW DSC MAC Maximum Slice Information
//--------------------------------------------------
#define _HW_DSC_MAC_MAX_SLICE_CNT                               4
#define _HW_DSC_MAC_MAX_SLICE_WIDTH                             1280
#define _HW_DSC_MAC_SLICE_MERGE_SUPPORT                         _ON
#define _HW_DSC_MAC_CLK_SOURCE                                  _DSC_SRC_DSC_MAC_PLL

//--------------------------------------------------
// HW Input TMDS MAC MAPPING TO DSC
//--------------------------------------------------
#define _HW_TMDS_MAC_RX0_DSC_MAPPING                            _DSC_MAC_NONE
#define _HW_TMDS_MAC_RX1_DSC_MAPPING                            _DSC_MAC_NONE
#define _HW_TMDS_MAC_RX2_DSC_MAPPING                            _DSC_MAC_NONE
#define _HW_TMDS_MAC_RX3_DSC_MAPPING                            (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_TMDS_MAC_RX4_DSC_MAPPING                            (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_TMDS_MAC_RX5_DSC_MAPPING                            _DSC_MAC_NONE

//--------------------------------------------------
// HW Input DP MAC MAPPING TO DSC
//--------------------------------------------------
#define _HW_DP_MAC_RX0_DSC_MAPPING                              (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_DP_MAC_RX1_DSC_MAPPING                              (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_DP_MAC_RX2_DSC_MAPPING                              (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_DP_MAC_RX3_DSC_MAPPING                              _DSC_MAC_NONE
#define _HW_DP_MAC_RX4_DSC_MAPPING                              _DSC_MAC_NONE
#define _HW_DP_MAC_RX5_DSC_MAPPING                              _DSC_MAC_NONE

//--------------------------------------------------
// HW Input DP AUX MAPPING TO DSC
//--------------------------------------------------
#define _HW_DP_AUX_RX0_DSC_MAPPING                              (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_DP_AUX_RX1_DSC_MAPPING                              (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_DP_AUX_RX2_DSC_MAPPING                              (_DSC_MAC_1 | _DSC_MAC_0)
#define _HW_DP_AUX_RX3_DSC_MAPPING                              _DSC_MAC_NONE
#define _HW_DP_AUX_RX4_DSC_MAPPING                              _DSC_MAC_NONE
#define _HW_DP_AUX_RX5_DSC_MAPPING                              _DSC_MAC_NONE

//--------------------------------------------------
// HW Input DP AUX DSC DPCD CAPABILITY
//--------------------------------------------------
#define _HW_DP_AUX_DPCD_DSC_SLICE_CAPABILITY                    0x0B

