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

#if(_PANEL_TYPE == _INNOLUX_LED_VBO_16X9_144ZONE)
//----------------------------------------------------------------------------------------------------
// ID Code      : _INNOLUX_LED_VBO_16X9_144ZONE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_VBO
#define _PANEL_PIXEL_TYPE                       _PANEL_PIXEL_LCD

//--------------------------------------------------
// Definitions for VBO Panel Configuration
//--------------------------------------------------
#define _PANEL_VBO_BYTE_MODE                    _VBO_DISP_4_BYTE_MODE
#define _PANEL_VBO_OUTPUT_PORT                  _VBO_8_DATA_LANE
#define _PANEL_VBO_BIT_MODE                     _VBO_DISP_30_BIT
#define _PANEL_VBO_PANEL_SECTION                _VBO_PANEL_4_SECTION
#define _PANEL_VBO_HS_CONTROL                   _VBO_HS_NORMAL
#define _PANEL_VBO_VS_CONTROL                   _VBO_VS_NORMAL
#define _PANEL_VBO_VIDEO_TRANSFER_TYPE          _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK
#define _PANEL_CDR_TRANSFER_ALN_LATENCY         9

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_INNOLUX

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_30_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       1440
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       590

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     1440
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     590

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        1440
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        590

///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         80
#define _PANEL_DH_WIDTH                         3840
#define _PANEL_DH_END                           3920

#define _PANEL_DH_TOTAL                         4400
#define _PANEL_DH_TOTAL_MAX                     4800
#define _PANEL_DH_TOTAL_MIN                     4240

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        2160
#define _PANEL_DV_END                           2166

#define _PANEL_DV_TOTAL                         2250
#define _PANEL_DV_TOTAL_MAX                     3000
#define _PANEL_DV_TOTAL_MIN                     2218

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      594
#define _PANEL_PIXEL_CLOCK_MAX                  610
#define _PANEL_PIXEL_CLOCK_MIN                  552 // 560

#define _PANEL_POWER_ON_T1                      5
#define _PANEL_POWER_ON_T2                      200
#define _PANEL_POWER_ON_T3                      1500

#define _PANEL_POWER_OFF_T4                     100
#define _PANEL_POWER_OFF_T5                     50
#define _PANEL_POWER_OFF_T6                     500


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    (_PANEL_DH_TOTAL - 200)
#define _PANEL_LAST_LINE_MIN                    (_PANEL_DH_TOTAL - 400)

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
#define _PANEL_MAX_LUMINANCE                    0x62 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x62 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool
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
#define _LOCAL_DIMMING_BACKLIGHT_TYPE           _LOCAL_DIMMING_DIRECT_BACKLIGHT
#define _LOCAL_DIMMING_PANEL_REGION_VERTICAL    9
#define _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL  16
#define _LOCAL_DIMMING_HISTO_COVERRATE          995
#define _LOCAL_DIMMING_TM_HISTO_COVERRATE       995
#define _LOCAL_DIMMING_SOFTCLAMP_SLOP           5
#define _LOCAL_DIMMING_DEEP_BLACK_TH1           16
#define _LOCAL_DIMMING_DEEP_BLACK_DELTA         5

//--------------------------------------------------
// Gen from Local Dimming Tool
//--------------------------------------------------
#include <RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/LDPwm2SpiConfig.h>
#define _LOCAL_DIMMING_PWM2SPI_DEV_ADDR         "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLDPwmToSpiDevAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM    "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLDPwmToSpiDataByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR   "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLDPwmToSpiPwmStartAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM   "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLDPwmToSpiDummyByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0     "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLDPwmToSpiRemapTable0.h"
#define _LED_SPI_DEV_ADDR                       "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLedSpiDevAddr.h"
#define _LED_SPI_PWM_START_ADDR                 "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLedSpiPwmStartAddr.h"
#define _LED_SPI_DATA_BYTE_NUM                  "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLedSpiDataByteNum.h"
#define _LED_SPI_DUMMY_BYTE_NUM                 "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLedSpiDummyByteNum.h"
#define _LOCAL_DIMMING_LVMAX_ADDR               "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLvMaxTable.h"
#define _LOCAL_DIMMING_PWMGAIN_ADDR             "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tPWMGainTable.h"
#define _LOCAL_DIMMING_LVGAIN_ADDR              "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLVGainTable.h"
#define _LOCAL_DIMMING_LVLUT_ADDR               "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLVLUTTable.h"
#define _LOCAL_DIMMING_LEDSETTING_ADDR          "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tLedSettingTable.h"
#define _LOCAL_DIMMING_HISTO_SDRLUT_ADDR        "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tHistoSDRLUT.h"
#define _LOCAL_DIMMING_HISTO_HDRLUT_ADDR        "./RTDLocalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tHistoHDRLUT.h"

//--------------------------------------------------
// Definitions for Global Dimming
//--------------------------------------------------
// #include <RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/GDPanelPara.h>
#define _GLOBAL_DIMMING_STEP_R_TABLE            "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tStepRTable.h"
#define _GLOBAL_DIMMING_PWM_LUT_TABLE           "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tPWMLUT.h"

#define _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540  "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tHDRToneMappingLv540.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_22_LV         "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDRGamma22Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_24_LV         "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDRGamma24Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_26_LV         "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDRGamma26Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV       "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDROGCCase1Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV       "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDROGCCase2Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV       "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDROGCCase3Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV       "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDROGCCase4Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV       "./RTDGlobalDimmingTable/34_INNOLUX_LED_VBO_16X9_144ZONE/tSDROGCCase5Lv.h"
//--------------------------------------------------
// Definitions for Driver IC
//--------------------------------------------------

#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820
#include <User_LedDriver_Include.h>

#define _DEVICE_LED_DRIVER_PWM_MAX              (256)
#define _DEVICE_LED_DRIVER_PWM_MIN              (0)
#define _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS   _ON

/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _LG_LED_DP_17_QHD)
