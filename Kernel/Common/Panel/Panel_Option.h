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
// ID Code      : Panel_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_OPTION_H__
#define __PANEL_OPTION_H__

//--------------------------------------------------
// Panel Option for DCLK Unit
//--------------------------------------------------
#if(_PANEL_PIXEL_CLOCK_UNIT == _PANEL_CLOCK_KHZ)
#define _PANEL_PIXEL_CLOCK_KHZ                      (_PANEL_PIXEL_CLOCK)
#define _PANEL_PIXEL_CLOCK_MAX_KHZ                  (_PANEL_PIXEL_CLOCK_MAX)
#define _PANEL_PIXEL_CLOCK_MIN_KHZ                  (_PANEL_PIXEL_CLOCK_MIN)
#elif(_PANEL_PIXEL_CLOCK_UNIT == _PANEL_CLOCK_MHZ)
#define _PANEL_PIXEL_CLOCK_KHZ                      (_PANEL_PIXEL_CLOCK * 1000UL)
#define _PANEL_PIXEL_CLOCK_MAX_KHZ                  (_PANEL_PIXEL_CLOCK_MAX * 1000UL)
#define _PANEL_PIXEL_CLOCK_MIN_KHZ                  (_PANEL_PIXEL_CLOCK_MIN * 1000UL)
#endif

//--------------------------------------------------
// Pixel per N.F DPLL offset
//--------------------------------------------------
#define _PANEL_N_F_DPLL_PIXEL_PER_OFFSET            ((DWORD)_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 1048576)

//----------------------------------------------------------------------------------------------------
// Panel DP Tx Option
//----------------------------------------------------------------------------------------------------
#define _DISPLAY_DP_TX_SUPPORT                      (_PANEL_STYLE == _PANEL_DPTX)

#if(_PANEL_STYLE == _PANEL_DPTX)
#if(_SCALER_TYPE == _RL6829_SERIES)
#define GET_PANEL_DISPLAY_DP_TX_PORT_0()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX0_PORT))

#define GET_PANEL_DISPLAY_DP_TX_PORT_1()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16) ||\
                                                     (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT))

#define GET_PANEL_DISPLAY_DP_TX_PORT_2()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16) ||\
                                                     (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT))

#define GET_PANEL_DISPLAY_DP_TX_PORT_3()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX3_PORT))

#define _DISPLAY_DP_TX_PORT_VALID                   (GET_PANEL_DISPLAY_DP_TX_PORT_0() +\
                                                     GET_PANEL_DISPLAY_DP_TX_PORT_1() +\
                                                     GET_PANEL_DISPLAY_DP_TX_PORT_2() +\
                                                     GET_PANEL_DISPLAY_DP_TX_PORT_3())

#define GET_PANEL_DPTX_MSO_MODE()                   ((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_8_SECTION) &&\
                                                     (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16))
#elif(_SCALER_TYPE == _RL6952_SERIES)
#define GET_PANEL_DISPLAY_DP_TX_PORT_0()            _OFF
#define GET_PANEL_DISPLAY_DP_TX_PORT_1()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT))

#define GET_PANEL_DISPLAY_DP_TX_PORT_2()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT))
#define GET_PANEL_DISPLAY_DP_TX_PORT_3()            _OFF

#define _DISPLAY_DP_TX_PORT_VALID                   (GET_PANEL_DISPLAY_DP_TX_PORT_1() +\
                                                     GET_PANEL_DISPLAY_DP_TX_PORT_2())

#define GET_PANEL_DPTX_MSO_MODE()                   ((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_4_SECTION) &&\
                                                     (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8))

#elif(_SCALER_TYPE == _RL6978_SERIES)
#define GET_PANEL_DISPLAY_DP_TX_PORT_0()            _OFF
#define GET_PANEL_DISPLAY_DP_TX_PORT_1()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT))

#define GET_PANEL_DISPLAY_DP_TX_PORT_2()            ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ||\
                                                     (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT))
#define GET_PANEL_DISPLAY_DP_TX_PORT_3()            _OFF

#define _DISPLAY_DP_TX_PORT_VALID                   (GET_PANEL_DISPLAY_DP_TX_PORT_1() +\
                                                     GET_PANEL_DISPLAY_DP_TX_PORT_2())

#define GET_PANEL_DPTX_MSO_MODE()                   ((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_4_SECTION) &&\
                                                     (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8))
#endif

#define GET_PANEL_DPTX_SWING_LEVEL()                (_PANEL_DPTX_SWING_LEVEL)
#define GET_PANEL_DPTX_PREEMPHASIS_LEVEL()          (_PANEL_DPTX_PREEMPHASIS_LEVEL)
#define GET_PANEL_DPTX_SPREAD_RANGE()               (_PANEL_DPTX_SPREAD_RANGE)
#define GET_PANEL_DPTX_SPREAD_SPEED()               (_PANEL_DPTX_SPREAD_SPEED)

//--------------------------------------------------
// Panel DPTx Lane/FB Swap Option
//--------------------------------------------------
#define GET_PANEL_DPTX_PORT_MIRROR()                (_PANEL_DPTX_PORT_MIRROR)
#define GET_PANEL_DPTX_PORT_0_LANE_SWAP()           (_PANEL_DPTX_PORT_0_LANE_SWAP)
#define GET_PANEL_DPTX_PORT_1_LANE_SWAP()           (_PANEL_DPTX_PORT_1_LANE_SWAP)
#define GET_PANEL_DPTX_PORT_2_LANE_SWAP()           (_PANEL_DPTX_PORT_2_LANE_SWAP)
#define GET_PANEL_DPTX_PORT_3_LANE_SWAP()           (_PANEL_DPTX_PORT_3_LANE_SWAP)
#define GET_PANEL_DPTX_PORT_0_LANE_PN_SWAP()        (_PANEL_DPTX_PORT_0_LANE_PN_SWAP)
#define GET_PANEL_DPTX_PORT_1_LANE_PN_SWAP()        (_PANEL_DPTX_PORT_1_LANE_PN_SWAP)
#define GET_PANEL_DPTX_PORT_2_LANE_PN_SWAP()        (_PANEL_DPTX_PORT_2_LANE_PN_SWAP)
#define GET_PANEL_DPTX_PORT_3_LANE_PN_SWAP()        (_PANEL_DPTX_PORT_3_LANE_PN_SWAP)

#define _DISPLAY_DP_TX0_SUPPORT                     (_HW_DISPLAY_DPTX0_SUPPORT == _ON)
#define _DISPLAY_DP_TX1_SUPPORT                     (_HW_DISPLAY_DPTX1_SUPPORT == _ON)
#define _DISPLAY_DP_TX2_SUPPORT                     (_HW_DISPLAY_DPTX2_SUPPORT == _ON)
#define _DISPLAY_DP_TX3_SUPPORT                     (_HW_DISPLAY_DPTX3_SUPPORT == _ON)

#else

#define _DISPLAY_DP_TX0_SUPPORT                     _OFF
#define _DISPLAY_DP_TX1_SUPPORT                     _OFF
#define _DISPLAY_DP_TX2_SUPPORT                     _OFF
#define _DISPLAY_DP_TX3_SUPPORT                     _OFF

#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

#define _DISPLAY_DP_TXX_SUPPORT                     ((_DISPLAY_DP_TX0_SUPPORT == _ON) ||\
                                                     (_DISPLAY_DP_TX1_SUPPORT == _ON) ||\
                                                     (_DISPLAY_DP_TX2_SUPPORT == _ON) ||\
                                                     (_DISPLAY_DP_TX3_SUPPORT == _ON))

#if(_PANEL_STYLE == _PANEL_VBO)
//--------------------------------------------------
// Panel VBO Option
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#define GET_PANEL_VBO_PIXEL_MODE()                  (((_PANEL_PIXEL_CLOCK_MAX_KHZ > 1400000) || (_DUAL_DP_SUPPORT == _ON) || (_PANEL_VBO_OUTPUT_PORT >= _VBO_16_DATA_LANE)) ? _VBO_4_PIXEL_MODE :\
                                                     ((_PANEL_DH_WIDTH > _HW_IP_SINGLE_PATH_HWIDTH_LIMITED) ? _VBO_4_PIXEL_MODE :\
                                                     (_VBO_2_PIXEL_MODE)))
#endif

#if(_SCALER_TYPE == _RL6952_SERIES)
#define GET_PANEL_VBO_PIXEL_MODE()                  (_VBO_2_PIXEL_MODE)
#endif

#if(_SCALER_TYPE == _RL6978_SERIES)
#define GET_PANEL_VBO_PIXEL_MODE()                  (_VBO_2_PIXEL_MODE)
#endif

#endif

//--------------------------------------------------
// D Domain 1/2/4 Path Option
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#define GET_D_DOMAIN_PATH()                         (((_PANEL_PIXEL_CLOCK_MAX_KHZ > 1400000) || (_DUAL_DP_SUPPORT == _ON)) ? _D_DOMAIN_4_PATH :\
                                                     ((_PANEL_DH_WIDTH > _HW_IP_SINGLE_PATH_HWIDTH_LIMITED) ? _D_DOMAIN_4_PATH :\
                                                     (_D_DOMAIN_2_PATH)))

#define _PANEL_DPTX_DCLK_DIV                        ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16) ? 4 :\
                                                     ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ? 2 : (1)))

#define _PANEL_DPTX_MSO_DIV                         (((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_8_SECTION) && (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16)) ? 2 : (1))
#endif

#if(_SCALER_TYPE == _RL6952_SERIES)
#define GET_D_DOMAIN_PATH()                         (_D_DOMAIN_2_PATH)

#define _PANEL_DPTX_DCLK_DIV                        ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ? 2 : (1))

#define _PANEL_DPTX_MSO_DIV                         (((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_4_SECTION) && (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)) ? 2 : (1))
#endif

#if(_SCALER_TYPE == _RL6978_SERIES)
#define GET_D_DOMAIN_PATH()                         (_D_DOMAIN_1_PATH)

#define _PANEL_DPTX_DCLK_DIV                        ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) ? 2 : (1))

#define _PANEL_DPTX_MSO_DIV                         (((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_4_SECTION) && (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)) ? 2 : (1))
#endif

//--------------------------------------------------
// Panel output number
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_NONE)
#define _PANEL_OUTPUT_NUM                           (1)

#elif(_PANEL_STYLE == _PANEL_LVDS)
#define _PANEL_OUTPUT_NUM                           (1 << _PANEL_LVDS_OUTPUT_PORT)

#elif(_PANEL_STYLE == _PANEL_DPTX)
#define _PANEL_OUTPUT_NUM                           (1 << _PANEL_DPTX_PANEL_SECTION)

#elif(_PANEL_STYLE == _PANEL_VBO)
#define _PANEL_OUTPUT_NUM                           ((GET_PANEL_VBO_PIXEL_MODE() == _VBO_4_PIXEL_MODE) ? ((_PANEL_VBO_OUTPUT_PORT < _VBO_16_DATA_LANE) ? _VBO_16_DATA_LANE : _PANEL_VBO_OUTPUT_PORT) : _PANEL_VBO_OUTPUT_PORT)

#elif(_PANEL_STYLE == _PANEL_TTL)
#define _PANEL_OUTPUT_NUM                           (1 << _PANEL_TTL_OUTPUT_PORT)

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

//--------------------------------------------------
// Definitions for Uniformity Setting
//--------------------------------------------------
#if((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_7TH_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_8TH_TABLE_LEVEL == _UNIFORMITY_5LEVEL) ||\
    (_UNIFORMITY_9TH_TABLE_LEVEL == _UNIFORMITY_5LEVEL))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_5LEVEL
#elif((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_7TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_8TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
      (_UNIFORMITY_9TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_4LEVEL
#elif((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_7TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_8TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_9TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_1LEVEL
#elif((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_7TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_8TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_9TH_TABLE_LEVEL == _UNIFORMITY_NONE))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_NONE
#endif

#define _PANEL_UNIFORMITY_HOR_INTERVAL              64
#define _PANEL_UNIFORMITY_VER_INTERVAL              _PANEL_UNIFORMITY_HOR_INTERVAL
#define _PANEL_UNIFORMITY_HOR_GRIDS                 (WORD)((_PANEL_DH_WIDTH / _PANEL_UNIFORMITY_HOR_INTERVAL) + 2)
#define _PANEL_UNIFORMITY_VER_GRIDS                 (WORD)((_PANEL_DV_HEIGHT / _PANEL_UNIFORMITY_VER_INTERVAL) + 2)
#define _PANEL_UNIFORMITY_HOR_OFFSET                (WORD)(((_PANEL_UNIFORMITY_HOR_GRIDS - 1) * _PANEL_UNIFORMITY_HOR_INTERVAL - _PANEL_DH_WIDTH) / 2)
#define _PANEL_UNIFORMITY_VER_OFFSET                (WORD)(((_PANEL_UNIFORMITY_VER_GRIDS - 1) * _PANEL_UNIFORMITY_VER_INTERVAL - _PANEL_DV_HEIGHT) / 2)
#define _PANEL_UNIFORMITY_1LEVEL_SIZE               ((WORD)_PANEL_UNIFORMITY_HOR_GRIDS * _PANEL_UNIFORMITY_VER_GRIDS * 5)
#define _PANEL_UNIFORMITY_OFFSET_LUT_SIZE           ((WORD)_PANEL_UNIFORMITY_HOR_GRIDS * _PANEL_UNIFORMITY_VER_GRIDS * 6)
#define _PANEL_UNIFORMITY_DECAY_LUT_SIZE            896

//--------------------------------------------------
// Definitions for Local Dimming Gen 2 Setting
//--------------------------------------------------
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
#define _LOCAL_DIMMING_HOR_INTERVAL                 64
#define _LOCAL_DIMMING_VER_INTERVAL                 64
#else
#define _LOCAL_DIMMING_HOR_INTERVAL                 (((_PANEL_DH_WIDTH / 32) <= 128) ? 32 : 64)
#define _LOCAL_DIMMING_VER_INTERVAL                 _LOCAL_DIMMING_HOR_INTERVAL
#endif
#define _LOCAL_DIMMING_HOR_GRIDS                    (WORD)((_PANEL_DH_WIDTH / _LOCAL_DIMMING_HOR_INTERVAL) + 2)
#define _LOCAL_DIMMING_VER_GRIDS                    (WORD)((_PANEL_DV_HEIGHT / _LOCAL_DIMMING_VER_INTERVAL) + 2)
#define _LOCAL_DIMMING_HOR_OFFSET                   (WORD)(((_LOCAL_DIMMING_HOR_GRIDS - 1) * _LOCAL_DIMMING_HOR_INTERVAL - _PANEL_DH_WIDTH) / 2)
#define _LOCAL_DIMMING_VER_OFFSET                   (WORD)(((_LOCAL_DIMMING_VER_GRIDS - 1) * _LOCAL_DIMMING_VER_INTERVAL - _PANEL_DV_HEIGHT) / 2)
#define _LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP      _OFF

#if(_LOCAL_DIMMING_PWM2SPI_PATTERN_OF_DUMMY_BYTE == 0)
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_PATTERN   0x00
#else
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_PATTERN   0xFF
#endif

#if((_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON) && (_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON))
#define _SPI_PWM_VALID_CMD_TOTAL_BYTES              (2 + 1 + _LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES + _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM)
#define _DEVICE_LED_DRIVER_UPDSYNC_METHOD           _SMODE_UPDSYNC_USE_SPI
#else
#define _DEVICE_LED_DRIVER_UPDSYNC_METHOD           _SMODE_UPDSYNC_USE_VSYNC
#endif
#define _LOCAL_DIMMING_TRUE_DIRECT_REGION           384


#if(_SCALER_TYPE == _RL6978_SERIES)

#if((_EMBEDDED_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_2PCS) && (_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION))
#define _LD_GLOBAL_VARIABLE_DEFAULT_DATA_SECTION_BY_CONFIG\
                                                    ".ddr_data."
#define _LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION_BY_CONFIG\
                                                    ".ddr_bss."
#else
#define _LD_GLOBAL_VARIABLE_DEFAULT_DATA_SECTION_BY_CONFIG\
                                                    ".data."
#define _LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION_BY_CONFIG\
                                                    ".bss."
#endif

#endif

//--------------------------------------------------
// Definitions for multiple of DHtotal
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_LVDS_OUTPUT_PORT >= _LVDS_8_PORT)
#define _PANEL_DHTOTAL_MULTIPLE                     (1 << _PANEL_LVDS_OUTPUT_PORT)
#else
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define _PANEL_DHTOTAL_MULTIPLE                     ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? (8) : (4))
#else
#define _PANEL_DHTOTAL_MULTIPLE                     (4)
#endif
#endif

#elif(_PANEL_STYLE == _PANEL_TTL)
#define _PANEL_DHTOTAL_MULTIPLE                     (1 << _PANEL_TTL_OUTPUT_PORT)

#elif(_PANEL_STYLE == _PANEL_VBO)

#define _PANEL_DHTOTAL_MULTIPLE                     ((_PANEL_VBO_OUTPUT_PORT >= _VBO_8_DATA_LANE) ? (_PANEL_VBO_OUTPUT_PORT) :\
                                                     ((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) ? ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? (8) : (4)) :\
                                                     (4)))

#elif(_PANEL_STYLE == _PANEL_DPTX)

#define _PANEL_DHTOTAL_MULTIPLE                     ((_PANEL_DPTX_LANE_NUMBER >= _PANEL_DPTX_LANE_NUMBER_8) ? (1 << _PANEL_DPTX_LANE_NUMBER) :\
                                                     ((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) ? ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? (8) : (4)) :\
                                                     (4)))

#endif

// Real DHtotal Value = DHtotal Register Setting + _DHTOTAL_SETTING_COMPLEMENT
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define _PANEL_DHTOTAL_SETTING_COMPLEMENT           ((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) ? (8) : (4))
#else
#define _PANEL_DHTOTAL_SETTING_COMPLEMENT           (4)
#endif

//--------------------------------------------------
// Definitions for Div of DPLL SSCG Mode
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)
#define _PANEL_DPLL_SSCG_DIV_MODE                   (_DIV_8)
#else
#define _PANEL_DPLL_SSCG_DIV_MODE                   (_DIV_1)
#endif

// 1% margin and spread
#define GET_CLOCK_SPREAD(clk, spread)               (((_DPLL_JITTER_MARGIN == _DPLL_1_PERCENT_JITTER_MARGIN) ? ((clk) / 100UL) : 0) + ((clk) * 5UL * (spread) / 2000UL / _PANEL_DPLL_SSCG_DIV_MODE))

#define _PANEL_PIXEL_CLOCK_MAX_SPREAD               (_PANEL_PIXEL_CLOCK_MAX_KHZ - GET_CLOCK_SPREAD(_PANEL_PIXEL_CLOCK_MAX_KHZ, _DCLK_SPREAD_RANGE_MAX))
#define _PANEL_PIXEL_CLOCK_MIN_SPREAD               (_PANEL_PIXEL_CLOCK_MIN_KHZ + GET_CLOCK_SPREAD(_PANEL_PIXEL_CLOCK_MIN_KHZ, _DCLK_SPREAD_RANGE_MAX))


//--------------------------------------------------
// Definitions for Last Line Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_TARGET                     ((_PANEL_LAST_LINE_MAX + _PANEL_LAST_LINE_MIN) / 2)
#endif // End of #ifndef __PANEL_OPTION_H__
