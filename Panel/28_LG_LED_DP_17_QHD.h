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

#if(_PANEL_TYPE == _LG_LED_DP_17_QHD)
//----------------------------------------------------------------------------------------------------
// ID Code      : _LG_LED_DP_17_QHD.h No.0000
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
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#define _PANEL_DPTX_PANEL_SECTION               _DPTX_PANEL_1_SECTION

//--------------------------------------------------
// Definitions for DPTx Panel Force Output Parameters
//--------------------------------------------------
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _OFF
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING   _DISABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD       _DISABLE
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP    _DISABLE
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP      _DISABLE

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_LGD

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         2560
#define _PANEL_DH_END                           2608

#define _PANEL_DH_TOTAL                         2768
#define _PANEL_DH_TOTAL_MAX                     2784
#define _PANEL_DH_TOTAL_MIN                     2752

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1440
#define _PANEL_DV_END                           1446

#define _PANEL_DV_TOTAL                         1481
#define _PANEL_DV_TOTAL_MAX                     1483
#define _PANEL_DV_TOTAL_MIN                     1479

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      246
#define _PANEL_PIXEL_CLOCK_MAX                  257
#define _PANEL_PIXEL_CLOCK_MIN                  235

#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      250
#define _PANEL_POWER_ON_T3                      250

#define _PANEL_POWER_OFF_T4                     250
#define _PANEL_POWER_OFF_T5                     20
#define _PANEL_POWER_OFF_T6                     1100


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
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#define _PANEL_DV_LINE_CHG_LIMIT                (260)

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
#define _LOCAL_DIMMING_PANEL_REGION_VERTICAL    1
#define _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL  8
#define _LOCAL_DIMMING_HISTO_COVERRATE          950
#define _LOCAL_DIMMING_TM_HISTO_COVERRATE       995
#define _LOCAL_DIMMING_SOFTCLAMP_SLOP           5
#define _LOCAL_DIMMING_DEEP_BLACK_TH1           16
#define _LOCAL_DIMMING_DEEP_BLACK_DELTA         5
#define _LOCAL_DIMMING_BOOST_ACTIVE_TIME        10
#define _LOCAL_DIMMING_BOOST_COOLING_TIME       30
#define _LOCAL_DIMMING_BOOST_COOLING_PWM_RATIO  80

//--------------------------------------------------
// Gen from Local Dimming Tool
//--------------------------------------------------
#include <RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/LDPwm2SpiConfig.h>
#define _LOCAL_DIMMING_PWM2SPI_DEV_ADDR         "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLDPwmToSpiDevAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM    "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLDPwmToSpiDataByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLDPwmToSpiPwmStartAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLDPwmToSpiDummyByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0     "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLDPwmToSpiRemapTable0.h"
#define _LED_SPI_DEV_ADDR                       "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLedSpiDevAddr.h"
#define _LED_SPI_PWM_START_ADDR                 "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLedSpiPwmStartAddr.h"
#define _LED_SPI_DATA_BYTE_NUM                  "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLedSpiDataByteNum.h"
#define _LED_SPI_DUMMY_BYTE_NUM                 "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLedSpiDummyByteNum.h"
#define _LOCAL_DIMMING_HDR_2084_LV              "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tHDR2084Lv.h"
#define _LOCAL_DIMMING_LVMAX_ADDR               "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLvMaxTable.h"
#define _LOCAL_DIMMING_PWMGAIN_ADDR             "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tPWMGainTable.h"
#define _LOCAL_DIMMING_LVGAIN_ADDR              "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLVGainTable.h"
#define _LOCAL_DIMMING_LVLUT_ADDR               "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLVBCurveTable.h"
#define _LOCAL_DIMMING_LEDSETTING_ADDR          "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLedSettingTable.h"
#define _LOCAL_DIMMING_HISTO_SDRLUT_ADDR        "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tHistoSDRLUT.h"
#define _LOCAL_DIMMING_HISTO_HDRLUT_ADDR        "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tHistoHDRLUT.h"
#define _LOCAL_DIMMING_S1LUT_ADDR               "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLVS1CurveTable.h"
#define _LOCAL_DIMMING_S2LUT_ADDR               "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLVS2CurveTable.h"

#define _LOCAL_DIMMING_PWM_DECREASE_STEP_TABLE  "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tPWMDecreaseTable.h"
#define _LOCAL_DIMMING_PWM_INCREASE_STEP_TABLE  "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tPWMIncreaseTable.h"



//--------------------------------------------------
// Definitions for Global Dimming
//--------------------------------------------------
#include <RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/GDPanelPara.h>
#define _GLOBAL_DIMMING_STEP_R_TABLE            "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tStepRTable.h"
#define _GLOBAL_DIMMING_PWM_LUT_TABLE           "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tPWMLUT.h"

#define _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540  "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tHDRToneMappingLv540.h"
#define _GLOBAL_DIMMING_HDR_2084_LV             "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tHDR2084Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_22_LV         "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma22Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_24_LV         "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma24Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_26_LV         "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma26Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV       "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase1Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV       "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase2Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV       "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase3Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV       "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase4Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV       "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase5Lv.h"
//--------------------------------------------------
// Definitions for Driver IC
//--------------------------------------------------

#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_01_O2_OZ9913
#include <User_LedDriver_Include.h>

#define _DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS    _ON
#define _DEVICE_LED_DRIVER_PWM_MAX              (383)
#define _DEVICE_LED_DRIVER_PWM_MIN              (0)

#define _LOCAL_DIMMING_MAXCLL                   300
#define _LOCAL_DIMMING_MAXFALL                  182


/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _LG_LED_DP_17_QHD)
