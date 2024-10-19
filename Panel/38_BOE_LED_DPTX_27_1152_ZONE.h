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

#if(_PANEL_TYPE == _BOE_LED_DPTX_27_1152_ZONE)

//----------------------------------------------------------------------------------------------------
// ID Code      : _BOE_LED_DPTX_27_1152_ZONE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                                    _PANEL_DPTX
#define _PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE            _PANEL_DPTX_LT_NORMAL_MODE
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT                _ON
#define _PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER             _OFF
#define _PANEL_PIXEL_TYPE                               _PANEL_PIXEL_LCD

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                           _PANEL_DPTX_LINK_HBR2            // Panel spec link per lane 2.7G is HBR
#define _PANEL_DPTX_LANE_NUMBER                         _PANEL_DPTX_LANE_NUMBER_4


#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING           _DISABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD               _DISABLE
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP            _DISABLE
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP              _DISABLE


#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT                _ON

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                         _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                             _PANEL_AUO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                            _PANEL_DISP_24_BIT

//--------------------------------------------------
// Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                           600
#define _PANEL_MAX_FRAME_RATE                           610
#define _PANEL_MIN_FRAME_RATE                           590


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                                 78
#define _PANEL_DH_WIDTH                                 3840
#define _PANEL_DH_END                                   3918

#define _PANEL_DH_TOTAL                                 4200
#define _PANEL_DH_TOTAL_MAX                             7040
#define _PANEL_DH_TOTAL_MIN                             4000

#define _PANEL_DV_START                                 7
#define _PANEL_DV_HEIGHT                                2160
#define _PANEL_DV_END                                   2167

#define _PANEL_DV_TOTAL                                 2200
#define _PANEL_DV_TOTAL_MAX                             4500
#define _PANEL_DV_TOTAL_MIN                             2180

#define _PANEL_DH_SYNC_WIDTH                            8
#define _PANEL_DV_SYNC_HEIGHT                           2

#define _PANEL_PIXEL_CLOCK                              554
#define _PANEL_PIXEL_CLOCK_MAX                          574
#define _PANEL_PIXEL_CLOCK_MIN                          160


#define _PANEL_POWER_ON_T1                              100
#define _PANEL_POWER_ON_T2                              50
#define _PANEL_POWER_ON_T3                              550 // 210

#define _PANEL_POWER_OFF_T4                             210
#define _PANEL_POWER_OFF_T5                             20
#define _PANEL_POWER_OFF_T6                             1200


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                            (_PANEL_DH_TOTAL - 400)
#define _PANEL_LAST_LINE_MIN                            (_PANEL_DH_TOTAL - 400)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                        20

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#define _PANEL_DV_LINE_CHG_LIMIT                        (260)

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                         _PANEL_CLOCK_MHZ


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                          (0)
#define _PANEL_ADC_GAIN_BIAS                            (0)


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Definitions for Display HDR
//--------------------------------------------------
#define _PANEL_MAX_LUMINANCE                            0x98 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE              0x98 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE                0x98 // from OGC Tool
#define _PANEL_MIN_LUMINANCE                            0x27 // from OGC Tool

//--------------------------------------------------
// Definitions for SPI
//--------------------------------------------------
#define _PANEL_SPI0_CLK_PRE_DIV                         _DIV_11             // SPI CLK PreDivider
#define _PANEL_SPI0_CLK_DIV                             _DIV_4              // SPI CLK Divider
#define _PANEL_SPI0_ENUM_PROTOCOL_SEL                   _SPI_NORMAL_MODE    // SPI Protocol Select
#define _PANEL_SPI0_ENUM_CLK_SRC_SEL                    _SPI_M2PLL_CLK      // SPI CLK Source
#define _PANEL_SPI0_MOSI_IDLE_STATE                     _LOW                // 0:low ; 1:high
#define _PANEL_SPI0_SCLK_IDLE_STATE                     _LOW                // 0:low ; 1:high
#define _PANEL_SPI0_CS_SEL                              0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _PANEL_SPI0_CS_POLARITY                         0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active

#define _PANEL_SPI1_CLK_PRE_DIV                         _DIV_9              // SPI CLK PreDivider
#define _PANEL_SPI1_CLK_DIV                             _DIV_4              // SPI CLK Divider
#define _PANEL_SPI1_ENUM_PROTOCOL_SEL                   _SPI_NORMAL_MODE    // SPI Protocol Select
#define _PANEL_SPI1_ENUM_CLK_SRC_SEL                    _SPI_M2PLL_CLK      // SPI CLK Source
#define _PANEL_SPI1_MOSI_IDLE_STATE                     _LOW                // 0:low ; 1:high
#define _PANEL_SPI1_SCLK_IDLE_STATE                     _LOW                // 0:low ; 1:high
#define _PANEL_SPI1_CS_SEL                              0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _PANEL_SPI1_CS_POLARITY                         0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active

//--------------------------------------------------
// Definitions for Local Dimming
//--------------------------------------------------
#define _LOCAL_DIMMING_BACKLIGHT_TYPE                   _LOCAL_DIMMING_DIRECT_BACKLIGHT
#define _LOCAL_DIMMING_PANEL_REGION_VERTICAL            24
#define _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL          48
#define _LOCAL_DIMMING_HISTO_COVERRATE                  998
#define _LOCAL_DIMMING_TM_HISTO_COVERRATE               998
#define _LOCAL_DIMMING_SOFTCLAMP_SLOP                   5
#define _LOCAL_DIMMING_DEEP_BLACK_TH1                   3500
#define _LOCAL_DIMMING_DEEP_BLACK_DELTA                 3

//--------------------------------------------------
// Gen from Local Dimming Tool
//--------------------------------------------------
#include <RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/LDPwm2SpiConfig.h>
#define _LOCAL_DIMMING_PWM2SPI_DEV_ADDR                 "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLDPwmToSpiDevAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM            "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLDPwmToSpiDataByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR           "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLDPwmToSpiPwmStartAddr.h"
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM           "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLDPwmToSpiDummyByteNum.h"
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0             "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLDPwmToSpiRemapTable0.h"
#define _LED_SPI_DEV_ADDR                               "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLedSpiDevAddr.h"
#define _LED_SPI_PWM_START_ADDR                         "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLedSpiPwmStartAddr.h"
#define _LED_SPI_DATA_BYTE_NUM                          "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLedSpiDataByteNum.h"
#define _LED_SPI_DUMMY_BYTE_NUM                         "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLedSpiDummyByteNum.h"
#define _LOCAL_DIMMING_LVMAX_ADDR                       "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLvMaxTable.h"
#define _LOCAL_DIMMING_PWMGAIN_ADDR                     "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tPWMGainTable.h"
#define _LOCAL_DIMMING_LVGAIN_ADDR                      "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLVGainTable.h"
#define _LOCAL_DIMMING_LVLUT_ADDR                       "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLVLUTTable.h"
#define _LOCAL_DIMMING_LEDSETTING_ADDR                  "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tLedSettingTable.h"
#define _LOCAL_DIMMING_HISTO_SDRLUT_ADDR                "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tHistoSDRLUT.h"
#define _LOCAL_DIMMING_HISTO_HDRLUT_ADDR                "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tHistoHDRLUT.h"
#define _LOCAL_DIMMING_HDR_2084_LV                      "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tHDR2084Lv.h"
#define _LOCAL_DIMMING_FREESYNC_II_LV                   "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tFreeSyncIILv.h"

#define _LOCAL_DIMMING_PWM_DECREASE_STEP_TABLE          "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tPWMDecreaseTable.h"
#define _LOCAL_DIMMING_PWM_INCREASE_STEP_TABLE          "./RTDLocalDimmingTable/38_BOE_LED_DPTX_27_1152_ZONE/tPWMIncreaseTable.h"


//--------------------------------------------------
// Definitions for Global Dimming
//--------------------------------------------------
// #include <RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/GDPanelPara.h>
#define _GLOBAL_DIMMING_STEP_R_TABLE                    "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tStepRTable.h"
#define _GLOBAL_DIMMING_PWM_LUT_TABLE                   "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tPWMLUT.h"

#define _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540          "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tHDRToneMappingLv540.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_22_LV                 "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDRGamma22Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_24_LV                 "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDRGamma24Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_26_LV                 "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDRGamma26Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV               "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDROGCCase1Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV               "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDROGCCase2Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV               "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDROGCCase3Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV               "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDROGCCase4Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV               "./RTDGlobalDimmingTable/30_AUO_eDP_27_UHD_512ZONE/tSDROGCCase5Lv.h"
//--------------------------------------------------
// Definitions for Driver IC
//--------------------------------------------------

#define _DEVICE_LED_DRIVER_TYPE                         _DEVICE_LED_DRIVER_06_MCU_1152_BOE
#include <User_LedDriver_Include.h>

#define _DEVICE_LED_DRIVER_PWM_MAX                      (4095)
#define _DEVICE_LED_DRIVER_PWM_MIN                      (0)
#define _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS           _OFF


/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _AUO_eDP_27_UHD_LOCAL_DIMMING)
