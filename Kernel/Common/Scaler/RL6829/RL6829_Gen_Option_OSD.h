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
// ID Code      : RL6829_Gen_Option_OSD.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

////////
// HW //
////////

//--------------------------------------------------
// Font OSD Support
//--------------------------------------------------
#define _HW_FOSD_SUPPORT                                        _ON

//--------------------------------------------------
// Graphic OSD Support
//--------------------------------------------------
#define _HW_GOSD_SUPPORT                                        _ON

//--------------------------------------------------
// OSD Register Gen (for osd composer tool)
//--------------------------------------------------
#define _HW_OSD_REG_MAPPING_GEN                                 _USER_OSD_GEN_3

//--------------------------------------------------
// Font OSD SRAM size
//--------------------------------------------------
#define _HW_FOSD_SRAM_SIZE                                      44032

//--------------------------------------------------
// Font OSD SU Line Buffer Size
//--------------------------------------------------
#define _HW_FOSD_SU_LINE_BUF_SIZE                               5120

//--------------------------------------------------
// Font OSD H Delay Max
//--------------------------------------------------
#define _HW_FOSD_H_DELAY_BIT                                    _14_BIT
#define _HW_FOSD_H_DELAY_MAX                                    4091 // avoid HW bug, max hori_delay = 4091

//--------------------------------------------------
// Font OSD SU Factor Max
//--------------------------------------------------
#define _HW_FOSD_SU_H_FACTOR_MIN                                16 // x 4
#define _HW_FOSD_SU_H_FACTOR_MAX                                64 // x 1
#define _HW_FOSD_SU_V_FACTOR_MIN                                16 // x 4
#define _HW_FOSD_SU_V_FACTOR_MAX                                64 // x 1

//--------------------------------------------------
// OSD Round Win 0 Pixel Support
//--------------------------------------------------
#define _HW_OSD_ROUND_WIN_0_PIXEL_SUPPORT                       _OFF

//--------------------------------------------------
// Display Font Base Address Support
//--------------------------------------------------
#define _HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT                     _OFF

//--------------------------------------------------
// 6 Bit Font Support
//--------------------------------------------------
#define _HW_OSD_6_BIT_FONT_SUPPORT                              _ON

//--------------------------------------------------
// 8 Bit Font Support
//--------------------------------------------------
#define _HW_OSD_8_BIT_FONT_SUPPORT                              _OFF

//-------------------------------------------------
// OSD Write Protect
//-------------------------------------------------
#define _HW_WRITE_PEOTECT_GEN_TYPE                              _OSD_WRITE_PROTECT_GEN_0

//-------------------------------------------------
// OSD Font Osd Map_C_D Support
//-------------------------------------------------
#define _HW_FOSD_MAP_C_D_SUPPORT                                _OFF

//-------------------------------------------------
// OSD HW Put String
//-------------------------------------------------
#define _HW_FOSD_HW_PUT_STRING_GEN_TYPE                         _OSD_HW_PUT_STRING_GEN_0

//-------------------------------------------------
// OSD HW Font Library Rotate Start Address
//-------------------------------------------------
#define _HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT          _OFF

//-------------------------------------------------
// OSD New Global Double Buffer Support
//-------------------------------------------------
#define _HW_FOSD_TIMING_GEN_DB_GEN_TYPE                         _OSD_TIMING_GEN_DB_GEN_NONE

//-------------------------------------------------
// Refer Capture Background Window Support
//-------------------------------------------------
#define _HW_FOSD_REFER_CAP_WIN_BACKGROUND_SUPPORT               _OFF


//-------------------------------------------------
// OSD Bit - Register
//-------------------------------------------------
// Row cmd address - map B
#define _HW_OSD_ROW_CMD_BASE_ADDR_B_BIT                         (_10_BIT)
// Font select base address
#define _HW_OSD_FONT_SEL_BASE_ADDR_BIT                          (_14_BIT)
// Font base address
#define _HW_OSD_FONT_BASE_ADDR_BIT                              (_16_BIT)
// Mask function
#define _HW_OSD_MASK_MAP_ROW_BIT                                (_10_BIT)
#define _HW_OSD_MASK_MAP_COLUMN_BIT                             (_10_BIT)
// Palette
#define _HW_OSD_PALETTE_BIT                                     (_6_BIT)
// 2 bit font offset
#define _HW_OSD_2_BIT_OFFSET_BIT                                (_10_BIT)
// 4 bit font offset
#define _HW_OSD_4_BIT_OFFSET_BIT                                (_10_BIT)

//-------------------------------------------------
// OSD Bit - Command
//-------------------------------------------------
// Blank font length
#define _HW_OSD_BLANK_FONT_LEN_BIT                              (_9_BIT)
// 1 bit font char sel
#define _HW_OSD_1BIT_FONT_CHAR_SET_BIT                          (_11_BIT)
// 4 bit font char sel
#define _HW_OSD_4BIT_FONT_CHAR_SET_BIT                          (_9_BIT)

//--------------------------------------------------
// Font OSD D_H_START limit
//--------------------------------------------------
#define _HW_FOSD_SINGLE_D_H_START_MAX                           255 // limit by reg_hporch_misc
#define _HW_FOSD_EO_D_H_START_MAX                               200
#define _HW_FOSD_FB_D_H_START_MAX                               400

//--------------------------------------------------
// Font OSD fb_hor_pre_operation max limit
//--------------------------------------------------
#define _HW_FOSD_FB_H_PRE_OPERATION_MAX                         72
// fb_hor_pre_operation = 18 * 64 / hsu_factor + 4, 4 for roation
// --> _HW_FOSD_FB_H_PRE_OPERATION_MAX = 18 * 64 / hsu_factor + 4
// --> min hsu_factor = 17 (h_porch_min = 176)
#define _HW_FOSD_FB_H_PRE_OPERATION_MAX_H_PORCH                 176

//-------------------------------------------------
// Graphics OSD SE Bitblit OpenGl constant coeff
//-------------------------------------------------
#define _HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT       _OFF

//-------------------------------------------------
// Graphics OSD GDMA max width OSD1
//-------------------------------------------------
#define _HW_GOSD_GDMA_MAX_WIDTH_OSD1                            2048

//-------------------------------------------------
// Graphics OSD AFBC support
//-------------------------------------------------
#define _HW_GOSD_AFBC_FORMAT_SUPPORT                            _ON

////////
// FW //
////////
//--------------------------------------------------
// OSD Initial
//--------------------------------------------------
#define OSD_SET_INITIAL()                                       {\
                                                                }

