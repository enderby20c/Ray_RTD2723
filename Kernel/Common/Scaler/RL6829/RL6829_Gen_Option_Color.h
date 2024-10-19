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
// ID Code      : RL6829_Gen_Option_Color.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


////////
// HW //
////////
//-------------------------------------------------
// Color Conversion
//-------------------------------------------------
#define _HW_COLOR_CONVERSION_TYPE                               _COLOR_CONVERSION_GEN_4
#define _HW_COLOR_CONVERSION_DB_TYPE                            _COLOR_CONVERSION_DB_GEN_0

//-------------------------------------------------
// IDither Gen
//-------------------------------------------------
#define _HW_IDITHER_TYPE                                        _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT
#define _HW_IDITHER_SD_MASK_SUPPORT                             _ON
#define _HW_IDITHER_M1_PATH_SUPPORT                             _ON
#define _HW_IDITHER_M2_PATH_SUPPORT                             _ON
#define _HW_IDITHER_S1_PATH_SUPPORT                             _ON
#define _HW_IDITHER_S2_PATH_SUPPORT                             _ON
#define _HW_IDITHER_S3_PATH_SUPPORT                             _ON
#define _HW_IDITHER_S4_PATH_SUPPORT                             _ON
#define _HW_IDITHER_SUPER_PIXEL_SUPPORT                         _ON

//-------------------------------------------------
// Scale Down Gen
//-------------------------------------------------
#define _HW_VSD_MAX_RATIO                                       (15)
#define _HW_HSD_MAX_RATIO                                       (15)
#define _HW_SCALING_DOWN_TYPE                                   _SD_GEN_0

//--------------------------------------------------
// Drop Extension Generation
//--------------------------------------------------
#define _HW_DROP_EXTENSION_GEN                                  _DROP_EXTENSION_GEN_1

//-------------------------------------------------
// Display Timing Gen Bit
//-------------------------------------------------
#define _HW_DIS_TIMING_GEN_HTOTAL_BIT                           (_14_BIT)
#define _HW_DIS_TIMING_GEN_VTOTAL_BIT                           (_15_BIT)

#define _HW_DIS_TIMING_GEN_H_ACTIVE_BIT                         (_14_BIT)
#define _HW_DIS_TIMING_GEN_V_ACTIVE_BIT                         (_14_BIT)

//-------------------------------------------------
// DVTotal/Lastline Measure Gen Bit
//-------------------------------------------------
#define _HW_DVTOTAL_LASTLINE_MEAS_GEN_BIT                       (_15_BIT)

//-------------------------------------------------
// Fifo Gen Bit
//-------------------------------------------------
#define _HW_FIFO_GEN_HTOTAL_BIT                                 (_14_BIT)
#define _HW_FIFO_GEN_VTOTAL_BIT                                 (_14_BIT)

//-------------------------------------------------
// UltraVivid Gen
//-------------------------------------------------
#define _HW_ULTRA_VIVID_TABLE_TYPE                              _ULTRA_VIVID_GEN_6

//-------------------------------------------------
// 3DDI Gen
//-------------------------------------------------
#define _HW_3DDI_1ST_PATH                                       _HW_3DDI_PATH_0
#define _HW_3DDI_2ND_PATH                                       _HW_3DDI_PATH_3

//-------------------------------------------------
// Scale Up Gen
//-------------------------------------------------
#define _HW_SCALING_UP_TYPE                                     _SU_GEN_0 // H_SU: 128 taps, V_SU: 128 taps
#define _HW_HSU_128TAPS_SUPPORT                                 _ON
#define _HW_HSU_96TAPS_SUPPORT                                  _OFF
#define _HW_VSU_128TAPS_SUPPORT                                 _ON
#define _HW_SU_LINE_BUFFER_SIZE                                 (4096) // Compare R1/R2/R3
#define _HW_SCALING_UP_VIDEO_COMPENSATION_TYPE                  _SU_VIDEO_COMPENSATION_GEN_1 // SU sample interlace field info. delay 1 frame
#define _HW_SCALING_UP_HSUI_GEN_TYPE                            _SU_HSUI_GEN_0 // HSUI: 22 bit

//-------------------------------------------------
// OSD Blending BG Color Insert Gen
//-------------------------------------------------
#define _HW_OSD_BLENDING_BG_COLOR_INSERT_GEN                    _OSD_BLENDING_BG_COLOR_INSERT_GEN_0

//-------------------------------------------------
// Local Contrast Gen
//-------------------------------------------------
#define _HW_LOCAL_CONTRAST_GEN_SEL                              _LOCAL_CONTRAST_GEN_3
#define _HW_LOCAL_CONTRAST_TABLE_SIZE                           (1773)
#define _HW_LOCAL_CONTRAST_TEMPORAL_TABLE_SIZE                  (46)
#define _HW_LOCAL_CONTRAST_PATH_COUNT_MAIN                      2
#define _HW_LOCAL_CONTRAST_PATH_COUNT_SUB                       2
#define _HW_LOCAL_CONTRAST_TM_BLENDINGFACTOR_START              (1680)
#define _HW_LOCAL_CONTRAST_INITAL_TABLE_SIZE                    (681)
#define _HW_LOCAL_CONTRAST_INITAL_TABLE_OFFSET                  (638)
#define _HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET                    (4)
#define _HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART2_SIZE           (676)
#define _HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART1_SIZE           (773)
#define _HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART1_OFFSET         (_HW_LOCAL_CONTRAST_DEFAULT_R3TABLE_PART2_SIZE + _HW_LOCAL_CONTRAST_TABLE_SIZE_OFFSET * 2)
#define _HW_LOCAL_CONTRAST_DH_PORCH_MIN                         ((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) ?\
                                                                ((_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON) ? 120 : 88) :\
                                                                ((_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON) ? 60 : 40)\
                                                                )
#define _HW_LOCAL_CONTRAST_BY_REGION_PATH_DIFFERENT             _OFF

//--------------------------------------------------
// PIPPBP Blending Generation
//--------------------------------------------------
#define _HW_PIPPBP_BLENDING_GEN                                 _PIPPBP_BLENDING_GEN_1

//-------------------------------------------------
// DCR Gen
//-------------------------------------------------
#define _HW_DCR_TYPE                                            _DCR_GEN_5
#define _HW_DCR_BIT                                             _DCR_10BIT
#define _HW_DCR_TH2_OPTION_SUPPORT                              _ON
#define _HW_DCR_LV_NUM_OPTION_SUPPORT                           _ON
#define _HW_DCR_YMAXMIN_OPTION_SUPPORT                          _ON
#define _HW_DCR_CLL_FALL_OPTION_SUPPORT                         _ON
#define _HW_DCR_SET_BACKGROUND_OPTION_SUPPORT                   _ON

//-------------------------------------------------
// DCC Gen
//-------------------------------------------------
#define _HW_DCC_TABLE_TYPE                                      _DCC_GEN_1
#define _HW_DCC_DB_TYPE                                         _DCC_DB_GEN_0
#define _HW_DCC_Y_BIT_MODE                                      _DCC_Y_10BIT

//-------------------------------------------------
// ICM Gen
//-------------------------------------------------
#define _HW_ICM_TABLE_TYPE                                      _ICM_GEN_3
#define _HW_ICM_DB_TYPE                                         _ICM_DB_GEN_0

//-------------------------------------------------
// Contrast Gen
//-------------------------------------------------
#define _HW_CTS_TYPE                                            _CTS_GEN_1_12BIT
#define _HW_CTS_ENABLE_BIT_ADDR_TYPE                            _CTS_EN_ADDR_P0_65

//-------------------------------------------------
// Brightness Gen
//-------------------------------------------------
#define _HW_BRI_TYPE                                            _BRI_GEN_1_10BIT
#define _HW_BRI_ENABLE_BIT_ADDR_TYPE                            _BRI_EN_ADDR_P0_65

//-------------------------------------------------
// IAPS Gain Gen
//-------------------------------------------------
#define _HW_IAPS_GAIN_COMPENSATION_TYPE                         _IAPS_GAIN_COMPENSATION_GEN_1

//-------------------------------------------------
// RGB 3D Gamma Gen
//-------------------------------------------------
#define _HW_3D_GAMMA_TABLE_TYPE                                 _3D_GAMMA_GEN_1

//-------------------------------------------------
// Input Gamma Gen
//-------------------------------------------------
#define _HW_INPUT_GAMMA_TABLE_TYPE                              _INPUT_GAMMA_GEN_2
#define _HW_INPUT_GAMMA_DB_TYPE                                 _INPUT_GAMMA_DB_GEN_0

//-------------------------------------------------
// Input Gamma Table Node Type
//-------------------------------------------------
#define _HW_INPUT_GAMMA_TABLE_NODE_TYPE                         _INPUT_GAMMA_NODE_1025

//-------------------------------------------------
// Y Mapping DB Type
//-------------------------------------------------
#define _HW_YMAPPING_DB_TYPE                                    _YMAPPING_DB_GEN_0

//--------------------------------------------------
// HW Local Dimming Support
//--------------------------------------------------
#define _HW_LOCAL_DIMMING_GEN_SEL                               _HW_LOCAL_DIMMING_GEN1
#define _HW_LOCAL_DIMMING_PWM_TABLE_FORM_SEL                    _HW_LOCAL_DIMMING_PWM_TABLE_FORM0
#define _HW_LOCAL_DIMMING_MAX_REGION                            5184
#define _HW_LOCAL_DIMMING_PWM2SPI_MAX_SPI                       2
#define _HW_LOCAL_DIMMING_PWM2SPI_ALIGN_PWM_PERIOD_CNT          _ON
#define _HW_LOCAL_DIMMING_POWER_DOMAIN                          _POWER_CUT_GROUP_LOCAL_DIMMING_M1M2
#define _HW_LOCAL_DIMMING_EDGE_H_REGION_MAX                     32
#define _HW_LOCAL_DIMMING_DIRECT_H_REGION_MAX                   108
#define _HW_LOCAL_DIMMING_TABLE0_SIZE                           2304
#define _HW_LOCAL_DIMMING_TABLE1_SIZE                           2880
#define _HW_LOCAL_DIMMING_EXTROINFO_SUPPORT                     _OFF

//--------------------------------------------------
// Panel Uniformity Support
//--------------------------------------------------
#define _HW_PANEL_UNIFORMITY_MAX_GAIN_LUT_SIZE                  106600
#define _HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT               _OFF

//-------------------------------------------------
// Output Gamma Gen
//-------------------------------------------------
#define _HW_OUTPUT_GAMMA_TABLE_TYPE                             _OUTPUT_GAMMA_GEN_1

//-------------------------------------------------
// sRGB Gen
//-------------------------------------------------
#define _HW_SRGB_DB_GEN_SEL                                     _SRGB_GEN_0

//-------------------------------------------------
// PCM Gen
//-------------------------------------------------
#define _HW_PCM_TABLE_TYPE                                      _PCM_GEN_2

//-------------------------------------------------
// DDither Gen
//-------------------------------------------------
#define _HW_DDITHER_TYPE                                        _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2

//-------------------------------------------------
// OD Gen
//-------------------------------------------------
#define _HW_OD_TABLE_TYPE                                       _OD_GEN_1
#define _HW_OD_LUT_MODE                                         _OD_8BIT_LUT
#define _HW_OD_BY_POSITION_GEN                                  _OD_BY_POSITION_GEN_0
#define _HW_OD_COMP_GEN                                         _OD_COMP_GEN_0

#define _HW_OD_PATH_COUNT                                       (4)

#define _HW_OD_M1_PAGE                                          (0x03)
#define _HW_OD_M2_PAGE                                          (0x43)
#define _HW_OD_M3_PAGE                                          (0x83)
#define _HW_OD_M4_PAGE                                          (0x50)

#define _HW_OD_MEM_FIFO_MIN_SIZE                                (256) // Unit: 128 bit (M1/M2:320*128 bit, M3/M4:256*128 bit)
#define _HW_OD_MEM_RW_MAX_LENGTH                                (0x7C) // Unit: 64 bit
#define _HW_OD_MEM_RW_MAX_REMAIN                                (0x78) // Unit: 64 bit

//--------------------------------------------------
// HW AdvancedHDR Support
//--------------------------------------------------
#define _HW_ADVANCED_HDR_SUPPORT                                _ON

//--------------------------------------------------
// HW 420 Buffer Width Limitation
//--------------------------------------------------
#define _HW_420_PATH0_BUFFER_WIDTH                              (8192)
#define _HW_420_PATH1_BUFFER_WIDTH                              (5120)
#define _HW_420_PATH2_BUFFER_WIDTH                              (5120)
#define _HW_420_PATH3_BUFFER_WIDTH                              (8192)

//--------------------------------------------------
// TCON Gen
//--------------------------------------------------
#define _HW_TCON_TYPE                                           _TCON_GEN_0
#define _HW_TCON_COMPENSATION                                   (0x00)

//--------------------------------------------------
// MRCM Gen
//--------------------------------------------------
#define _HW_MRCM_DUMMY_READ_SUPPORT                             _GEN_NONE


////////
// FW //
////////
//--------------------------------------------------
// FW Local Dimming Support
//--------------------------------------------------
#if(_HW_CPU32_IS_BOOT_CPU == _OFF)
#define _FW_LD_GLOBAL_VARIABLE_DEFAULT_DATA_SECTION             ".ddr_data."
#define _FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION              ".ddr_bss."
#else
#define _FW_LD_GLOBAL_VARIABLE_DEFAULT_DATA_SECTION             ".data."
#define _FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION              ".bss."
#endif
