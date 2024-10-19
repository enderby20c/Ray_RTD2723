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
// ID Code      : RL6829_Gen_Option_M_Domain.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// M-Domain Data Bit Max
//--------------------------------------------------
#define _HW_M_DOMAIN_DATA_BIT_MAX                               (_COLOR_DEPTH_10_BITS * 3)

//--------------------------------------------------
// Memory Device PLL Type
//--------------------------------------------------
#define _HW_MEMORY_DEVICE_PLL_GEN_TYPE                          _MEMORY_DEVICE_PLL_GEN_3

//--------------------------------------------------
// Select Fifo Frequency Reference Clk
//--------------------------------------------------
#define _HW_FIFO_FREQ_LINE_BUFFER_SEL                           _SCALER_FIFO_FREQ_MPLL
#define _HW_FIFO_FREQ_FRAME_BUFFER_SEL                          _SCALER_FIFO_FREQ_MPLL

//--------------------------------------------------
// Fifo Clk Sel Type
//--------------------------------------------------
#define _HW_FIFO_CLK_SEL_TYPE                                   _FIFO_CLK_SEL_GEN_0

//--------------------------------------------------
// Memory Type
//--------------------------------------------------
#define _HW_MEMORY_TYPE                                         _EMBEDDED_MEMORY
#define _HW_MEMORY_DDR3_DPIDLL_GEN_TYPE                         _MEMORY_DDR3_DPIDLL_GEN_1
#define _HW_MEMORY_DDR3_GEN_TYPE                                _MEMORY_DDR3_GEN_2
#define _HW_MEMORY_DEVICE_MAX_COUNT                             2
#define _HW_MEMORY_DDR2_DPIDLL_GEN_TYPE                         _GEN_NONE
#define _HW_MEMORY_DDR2_GEN_TYPE                                _GEN_NONE
#define _HW_MEMORY_DDR2_2PC_SEPARATE_SUPPORT                    _OFF

//-------------------------------------------------
// MPLL Structure
//-------------------------------------------------
#define _HW_MPLL_STRUCT_TYPE                                    _MPLL_STRUCT_N_F // For No MPLL Case

//--------------------------------------------------
// HW Shift One line Type
//--------------------------------------------------
#define _HW_SHIFT_ONE_LINE_TYPE                                 _VSD_SHIFT_ONE_LINE

//--------------------------------------------------
// FRC 3 Block Toggle Option
//--------------------------------------------------
#define _HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT                   _OFF

//-------------------------------------------------
// Display Rotation Gen
//-------------------------------------------------
#define _HW_DISPLAY_ROTATION_TYPE                               _DISPLAY_ROTATION_GEN_III

//-------------------------------------------------
// Display Rotation
//-------------------------------------------------
#define _HW_DISPLAY_ROTATION_90_SUPPORT                         _OFF
#define _HW_DISPLAY_ROTATION_180_SUPPORT                        _ON
#define _HW_DISPLAY_ROTATION_270_SUPPORT                        _OFF

//--------------------------------------------------
// Display Rotation Control Type
//--------------------------------------------------
#define _HW_DISPLAY_ROTATION_CTRL_TYPE                          _DISPLAY_ROTATION_CTRL_GEN_0

//-------------------------------------------------
// FB To EO
//-------------------------------------------------
#define _HW_FB2EO_HWIDTH_SETTING_TYPE                           _FB2EO_HWIDTH_SETTING_GEN_0
#define _HW_FB2EO_INDEPENDENT_OF_IMC_DEC                        _FALSE

//--------------------------------------------------
// HW M-Domain Image Compression TYPE
//--------------------------------------------------
#define _HW_M_DOMAIN_IMG_CMP_TYPE                               _M_DOMAIN_IMG_CMP_GEN_1
#define _HW_M_DOMAIN_IMG_CMP_HPORCH_LIMIT                       22
#define _HW_M_DOMAIN_IMG_DECMP_HPORCH_LIMIT                     22

#define _HW_M_DOMAIN_IMG_CMP_PATH_COUNT                         6

#define _HW_M_DOMAIN_IMG_CMP_ALL_PATH                           (_INPUT_PATH_M1_M2 | _INPUT_PATH_S1_S2 | _INPUT_PATH_S3_S4)
#define _HW_M_DOMAIN_IMG_DECMP_ALL_PATH                         (_MDOMAIN_DISP_PATH_M1_M2 | _MDOMAIN_DISP_PATH_S1_S2 | _MDOMAIN_DISP_PATH_S3_S4)

#define _REG_PAGE_M1_M_DOMAIN_IMG_CMP                           0x4B
#define _REG_PAGE_M1_M_DOMAIN_IMG_DECMP                         0x4B
#define _REG_PAGE_M2_M_DOMAIN_IMG_CMP                           0x4C
#define _REG_PAGE_M2_M_DOMAIN_IMG_DECMP                         0x4C
#define _REG_PAGE_S1_M_DOMAIN_IMG_CMP                           0x4D
#define _REG_PAGE_S1_M_DOMAIN_IMG_DECMP                         0x4D
#define _REG_PAGE_S2_M_DOMAIN_IMG_CMP                           0x4E
#define _REG_PAGE_S2_M_DOMAIN_IMG_DECMP                         0x4E
#define _REG_PAGE_S3_M_DOMAIN_IMG_CMP                           0xBE
#define _REG_PAGE_S3_M_DOMAIN_IMG_DECMP                         0xBE
#define _REG_PAGE_S4_M_DOMAIN_IMG_CMP                           0xDA
#define _REG_PAGE_S4_M_DOMAIN_IMG_DECMP                         0xDA

//--------------------------------------------------
// HW IP Single Path Hwidth Limited
//--------------------------------------------------
#define _HW_IP_SINGLE_PATH_HWIDTH_LIMITED                       (5120) // Linebuffer Size of IP.(PQC, PQDC, SD, SU, LSR, ,DSHP, DisplayConversion)

//--------------------------------------------------
// HW Memory BW Ctrl
//--------------------------------------------------
#define _HW_MEMORY_BW_CTRL_FRC_SUPPORT                          _ON
#define _HW_MEMORY_BW_CTRL_OD_SUPPORT                           _ON
#define _HW_MEMORY_BW_CTRL_3DDI_SUPPORT                         _ON
#define _HW_MEMORY_BW_CTRL_GOSD_SUPPORT                         _ON

#define _HW_BW_CTRL_LEN_MODE_REQ_THR_UNIT_BIT                   (128)
#define _HW_BW_CTRL_LEN_MODE_SB_CLIENT_REQ_THR_REG_GAIN         (16)
#define _HW_BW_CTRL_SB_CLIENT_TIME_THR_REG_GAIN                 (16)

//--------------------------------------------------
// HW IMD Power Cut independent
//--------------------------------------------------
#define _HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT                   _ON

//--------------------------------------------------
// HW PR Mode Type
//--------------------------------------------------
#define _HW_M_DOMAIN_PR_MODE_TYPE                               _M_DOMAIN_PR_MODE_GEN_0

//--------------------------------------------------
// FRC Supports Dynamic Space Calculation
//--------------------------------------------------
#define _FW_FRC_DYNAMIC_SPACE_ALLOCATION                        _ON

//-------------------------------------------------
// OD Memory Space allocation
//-------------------------------------------------
#define _FW_OD_PATH_START_ADDR_DESCENDING                       _TRUE

//-------------------------------------------------
// FW Memory Related Setting
//-------------------------------------------------
#define _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM                          ((GET_MEMORY_PIECE() == _MEMORY_2PCS) ? 12 : 11)
#define _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM                         ((GET_MEMORY_PIECE() == _MEMORY_2PCS) ? 9 : 8)
#define _FW_MEM_CLIENT_SHARE_ADDR_SPACE                         _TRUE
#define _FW_MEM_CLIENT_MEMORY_BIT_NUM                           _MEMORY_BIT_NUM

//-------------------------------------------------
// FW Memory BW Ctrl Related Constant
//-------------------------------------------------
#define _FW_BW_CTRL_LEN_MODE_SB_CLIENT_REQ_THR_UNIT_BIT         (_HW_BW_CTRL_LEN_MODE_REQ_THR_UNIT_BIT * _HW_BW_CTRL_LEN_MODE_SB_CLIENT_REQ_THR_REG_GAIN)

//-------------------------------------------------
// HW FRC Length Setting
//-------------------------------------------------
#define _HW_FRC_LENGTH_TYPE                                     _FRC_LENGTH_7BIT
