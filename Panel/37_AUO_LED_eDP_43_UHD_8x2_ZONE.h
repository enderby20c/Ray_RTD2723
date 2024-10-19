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

#if(_PANEL_TYPE == _AUO_LED_EDP_43_UHD_8X2_ZONE)
//----------------------------------------------------------------------------------------------------
// ID Code      : _AUO_LED_EDP_43_UHD_8X2_ZONE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX
#define _PANEL_PIXEL_TYPE                       _PANEL_PIXEL_LCD

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR2
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_8
#define _PANEL_DPTX_PANEL_SECTION               _DPTX_PANEL_2_SECTION
#define _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN    _ON

//--------------------------------------------------
// Definitions for DPTx Panel Force Output Parameters
//--------------------------------------------------
/*
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _ON
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING   _DISABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD       _DISABLE
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP    _DISABLE
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP      _DISABLE
*/

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_AUO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   1200
#define _PANEL_MAX_FRAME_RATE                   1450
#define _PANEL_MIN_FRAME_RATE                   470

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       1440
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       480

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     1440
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     480

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        1440
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        480

///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         80
#define _PANEL_DH_WIDTH                         3840
#define _PANEL_DH_END                           3920

#define _PANEL_DH_TOTAL                         4200
#define _PANEL_DH_TOTAL_MAX                     4280 // 7040
#define _PANEL_DH_TOTAL_MIN                     4024 // 4000

#define _PANEL_DV_START                         16
#define _PANEL_DV_HEIGHT                        2160
#define _PANEL_DV_END                           2176

#define _PANEL_DV_TOTAL                         2200
#define _PANEL_DV_TOTAL_MAX                     6735
#define _PANEL_DV_TOTAL_MIN                     2184 // 2180

#define _PANEL_DH_SYNC_WIDTH                    16
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      1108
#define _PANEL_PIXEL_CLOCK_MAX                  1280 // 1266
#define _PANEL_PIXEL_CLOCK_MIN                  740 // 720

#define _PANEL_POWER_ON_T1                      300
#define _PANEL_POWER_ON_T2                      40
#define _PANEL_POWER_ON_T3                      590 // 500

#define _PANEL_POWER_OFF_T4                     120 // 20
#define _PANEL_POWER_OFF_T5                     40
#define _PANEL_POWER_OFF_T6                     1200

/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    (_PANEL_DH_TOTAL_MIN - 200)
#define _PANEL_LAST_LINE_MIN                    (_PANEL_DH_TOTAL_MIN - 360)

//-------------------------------------------------
// Display PLL Jitter Margin
//-------------------------------------------------
#define _DPLL_JITTER_MARGIN                     _DPLL_NO_JITTER_MARGIN

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Definitions for Display HDR
//--------------------------------------------------
#define _LOCAL_DIMMING_MAXCLL                   1083
#define _LOCAL_DIMMING_MAXFALL                  814

#define _PANEL_MAX_LUMINANCE                    0x7D
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x76

#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x66
#define _PANEL_MIN_LUMINANCE                    0x27 // from OGC Tool

//--------------------------------------------------
// Definitions for SPI
//--------------------------------------------------
#define _PANEL_SPI0_CLK_PRE_DIV                 _DIV_9              // SPI CLK PreDivider
#define _PANEL_SPI0_CLK_DIV                     _DIV_4              // SPI CLK Divider
#define _PANEL_SPI0_ENUM_PROTOCOL_SEL           _SPI_NORMAL_MODE    // SPI Protocol Select
#define _PANEL_SPI0_ENUM_CLK_SRC_SEL            _SPI_M2PLL_CLK      // SPI CLK Source
#define _PANEL_SPI0_MOSI_IDLE_STATE             _LOW                // 0:low ; 1:high
#define _PANEL_SPI0_SCLK_IDLE_STATE             _LOW                // 0:low ; 1:high
#define _PANEL_SPI0_CS_SEL                      0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _PANEL_SPI0_CS_POLARITY                 0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active

//--------------------------------------------------
// Definitions for Local Dimming
//--------------------------------------------------
#define _LOCAL_DIMMING_BACKLIGHT_TYPE           _LOCAL_DIMMING_EDGE_BACKLIGHT
#define _LOCAL_DIMMING_PANEL_REGION_VERTICAL    2
#define _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL  8
#define _LOCAL_DIMMING_HISTO_COVERRATE          950
#define _LOCAL_DIMMING_TM_HISTO_COVERRATE       995
#define _LOCAL_DIMMING_SOFTCLAMP_SLOP           5
#define _LOCAL_DIMMING_DEEP_BLACK_TH1           3500
#define _LOCAL_DIMMING_DEEP_BLACK_DELTA         3

//--------------------------------------------------
// Gen from Local Dimming Tool
//--------------------------------------------------
#include <RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/LDPwm2SpiConfig.h>
#define _LOCAL_DIMMING_PWM2SPI_DEV_ADDR         "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLDPwmToSpiDevAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM    "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLDPwmToSpiDataByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR   "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLDPwmToSpiPwmStartAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM   "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLDPwmToSpiDummyByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0     "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLDPwmToSpiRemapTable0.h"
#define _LED_SPI_DEV_ADDR                       "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLedSpiDevAddr.h"
#define _LED_SPI_PWM_START_ADDR                 "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLedSpiPwmStartAddr.h"
#define _LED_SPI_DATA_BYTE_NUM                  "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLedSpiDataByteNum.h"
#define _LED_SPI_DUMMY_BYTE_NUM                 "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLedSpiDummyByteNum.h"
#define _LOCAL_DIMMING_HDR_2084_LV              "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tHDR2084Lv.h"
#define _LOCAL_DIMMING_FREESYNC_II_LV           "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tFreeSyncIILv.h"
#define _LOCAL_DIMMING_LVMAX_ADDR               "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLvMaxTable.h"
#define _LOCAL_DIMMING_PWMGAIN_ADDR             "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tPWMGainTable.h"
#define _LOCAL_DIMMING_LVGAIN_ADDR              "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLVGainTable.h"
#define _LOCAL_DIMMING_LVLUT_ADDR               "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLVBCurveTable.h"
#define _LOCAL_DIMMING_LEDSETTING_ADDR          "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tLedSettingTable.h"
#define _LOCAL_DIMMING_HISTO_SDRLUT_ADDR        "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tHistoSDRLUT.h"
#define _LOCAL_DIMMING_HISTO_HDRLUT_ADDR        "./RTDLocalDimmingTable/37_AUO_LED_eDP_43_UHD_8x2_ZONE/tHistoHDRLUT.h"
#define _LOCAL_DIMMING_S1LUT_ADDR               "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLVS1CurveTable.h"
#define _LOCAL_DIMMING_S2LUT_ADDR               "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLVS2CurveTable.h"
//--------------------------------------------------
// Definitions for Driver IC
//--------------------------------------------------

#define _LOCAL_DIMMING_BOOST_ADMING             120

#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_04_AUSTRIA_AS3824
#include <User_LedDriver_Include.h>

#define _DEVICE_LED_DRIVER_PWM_MAX              256
#define _DEVICE_LED_DRIVER_PWM_MIN              52
#define _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS   _ON


/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _AUO_LED_EDP_43_UHD_8X2_ZONE)
