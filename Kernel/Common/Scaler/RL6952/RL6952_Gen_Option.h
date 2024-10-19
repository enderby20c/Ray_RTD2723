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
// ID Code      : RL6952_Gen_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_SCALER_TYPE == _RL6952_SERIES)

#ifndef __RL6952_GEN_OPTION__
#define __RL6952_GEN_OPTION__


////////
// HW //
////////
//--------------------------------------------------
// HW Input Port Clock Max
//--------------------------------------------------
#define _HW_A0_INPUT_CLOCK_MAX                                  _INPUT_NONE // Unit: Hz , VGA // Confirm
#define _HW_D0_INPUT_CLOCK_MAX                                  1200000000 // Unit: Hz , DP
#define _HW_D1_INPUT_CLOCK_MAX                                  1200000000 // Unit: Hz , DP
#define _HW_D2_INPUT_CLOCK_MAX                                  1200000000 // Unit: Hz , DP
#define _HW_D3_INPUT_CLOCK_MAX                                  1200000000 // Unit: Hz , HDMI2.1 // Confirm
#define _HW_D4_INPUT_CLOCK_MAX                                  1200000000 // Unit: Hz , HDMI2.1 // Confirm
#define _HW_D5_INPUT_CLOCK_MAX                                  _INPUT_NONE // Confirm

//--------------------------------------------------
// HW Support LC Tank
//--------------------------------------------------
#define _HW_LC_TANK_SUPPORT                                     _OFF

//--------------------------------------------------
// Fuse Support
//--------------------------------------------------
#define _HW_FUSE_TYPE                                           _OTPFUSE_TYPE
#define _HW_FUSE_HDCP_1_4_RXKEY                                 _ON
#define _HW_FUSE_HDCP_1_4_TXKEY                                 _ON
#define _HW_FUSE_HDCP_2_2_RXKEY                                 _ON

//--------------------------------------------------
// IOSC Clock Frequncy Define
//--------------------------------------------------
#define _HW_INTERNAL_OSC_XTAL                                   _IOSC28000K // Confirm

//-------------------------------------------------
// M2PLL Structure
//-------------------------------------------------
#define _HW_M2PLL_STRUCT_TYPE                                   _M2PLL_STRUCT_N_F

//--------------------------------------------------
// NF PLL Struct
//--------------------------------------------------
#define _HW_NF_PLL_STRUCT_TYPE                                  _NF_PLL_GEN_1

//--------------------------------------------------
// Watch Dog Mapping support
//--------------------------------------------------
#define _HW_GLOBAL_WD_MAPPING_SUPPORT                           _ON // Confrim

//-------------------------------------------------
// Global DB Gen
//-------------------------------------------------
#define _HW_GLOBAL_DB_TYPE                                      _GLOBAL_DB_GEN_IV

//--------------------------------------------------
// 5K PIP mode support
//--------------------------------------------------
#define _HW_5K_PIP_SUPPORT                                      _OFF

//--------------------------------------------------
// HW Ddcci buffer size
//--------------------------------------------------
#define _HW_DDCCI_BUF_SIZE                                      32

//-------------------------------------------------
// Thermal Sensor Offset
//-------------------------------------------------
#define _FW_THERMAL_SENSOR_OFFSET_1                             0x37
#define _FW_THERMAL_SENSOR_OFFSET_2                             0x34
#define _FW_THERMAL_SENSOR_OFFSET_3                             0xF2

//-------------------------------------------------
// Thermal Sensor Gain
//-------------------------------------------------
#define _FW_THERMAL_SENSOR_GAIN_1                               0x08
#define _FW_THERMAL_SENSOR_GAIN_2                               0x03
#define _FW_THERMAL_SENSOR_GAIN_3                               0xDF
#define _FW_THERMAL_SENSOR_GAIN_4                               0xF0

//--------------------------------------------------
// HW USB2Host Related Setting
//--------------------------------------------------
#define _HW_USB2_HOST_SUPPORT                                   _ON
#define _HW_DM_CLIENT_SUPPORT                                   _OFF

//--------------------------------------------------
// HW Display Output LVDS Driving Mode
//--------------------------------------------------
#define _HW_LVDS_DRIVE_TRIMMING_SUPPORT                         _ON

//--------------------------------------------------
// HW Audio TTS Support
//--------------------------------------------------
#define _HW_AUDIO_TTS_EMBEDDED_SUPPORT                          _ON

//--------------------------------------------------
// HW Audio TTS Flash Burst Read Count Option
//--------------------------------------------------
#define _HW_AUDIO_TTS_BWR_COUNT_GEN                             _AUDIO_TTS_BWR_COUNT_GEN_0

//--------------------------------------------------
// HW Audio DAC Gen
//--------------------------------------------------
#define _HW_AUDIO_DAC_GEN                                       _AUDIO_DAC_GEN_1

//--------------------------------------------------
// HW DP Mac Power Cut Gen Option
//--------------------------------------------------
#define _HW_DP_MAC_POWER_CUT_GEN                                _DP_MAC_POWER_CUT_SEPARATE

//--------------------------------------------------
// HW DP TX HPD Detect During Power Off
//--------------------------------------------------
#define _HW_DP_TX_HPD_DETECT_DURING_POWER_OFF                   _ON

//--------------------------------------------------
// HW Internal OSC Gen
//--------------------------------------------------
#define _HW_IOSC_GEN                                            _IOSC_GEN_1

//-------------------------------------------------
// TOP_ON Power Domain Gen
//-------------------------------------------------
#define _HW_TOP_ON_POWER_DOMAIN_GEN                             _TOP_ON_POWER_DOMAIN_GEN_0


////////
// FW //
////////

//-------------------------------------------------
// FW M2PLL Freq
//-------------------------------------------------
#define _FW_M2PLL_FREQ_SEL                                      _M2PLL_FREQ_351M // Confirm
#define _FW_M2PLL_FVCO_SEL                                      _M2PLL_FVCO_702M

//--------------------------------------------------
// FW Underscan
//--------------------------------------------------
#define _FW_UNDERSCAN_SUPPORT                                   _OFF // Confirm

//--------------------------------------------------
// FW Support DP/HDMI Compatible Mode Support for Eizo
//--------------------------------------------------
#define _FW_DP_HDMI_COMPATIBLE_MODE_SUPPORT                     _ON

//--------------------------------------------------
// FW rsa type
//--------------------------------------------------
#define _FW_MAX_DIGITAL_SIGNATURE_RSA                           _DIGITAL_SIGNATURE_RSA_3072

//--------------------------------------------------
// FW 3DDI
//--------------------------------------------------
#define _FW_3DDI_FUNCTION_SUPPORT                               _OFF

//--------------------------------------------------
// DisplayTop Avg Req
//--------------------------------------------------
#define _FW_DISPLAYTOP_AVG_REQ_SUPPORT                          _ON

//--------------------------------------------------
// FW oneshot mode
//--------------------------------------------------
#define _FW_ONESHOT_MODE_SUPPORT                                _OFF

////////
// IP //
////////
#include <Scaler/RL6952/RL6952_Gen_Option_Color.h>
#include <Scaler/RL6952/RL6952_Gen_Option_OSD.h> // Modify
#include <Scaler/RL6952/RL6952_Gen_Option_Data_Path.h>
#include <Scaler/RL6952/RL6952_Gen_Option_VGA.h>
#include <Scaler/RL6952/RL6952_Gen_Option_HDMI.h>
#include <Scaler/RL6952/RL6952_Gen_Option_DP.h>
#include <Scaler/RL6952/RL6952_Gen_Option_GDI_PHY.h>
#include <Scaler/RL6952/RL6952_Gen_Option_I_Domain.h>
#include <Scaler/RL6952/RL6952_Gen_Option_M_Domain.h>
#include <Scaler/RL6952/RL6952_Gen_Option_D_Domain.h>
#include <Scaler/RL6952/RL6952_Gen_Option_DSC.h>
#include <Scaler/RL6952/RL6952_Gen_Option_Display_Tx.h>
#include <Scaler/RL6952/RL6952_Gen_Option_MCU.h>
#include <Scaler/RL6952/RL6952_Gen_Option_32CPU.h>
#include <Scaler/RL6952/RL6952_Gen_Option_TypeC.h>
#include <Scaler/RL6952/RL6952_Gen_Option_USB.h>
#include <Scaler/RL6952/RL6952_Gen_Option_OTP.h>
#include <Scaler/RL6952/RL6952_Gen_Option_HDCP.h>


#include <Scaler/RL6952/RL6952_Gen_Option_Reg_Mapping.h>

#ifndef __ASSEMBLER__
#include <Scaler/RL6952/RL6952_Gen_Option_Typedef.h>
#endif

#endif // End of #ifndef __RL6952_GEN_OPTION__
#endif // End of #if(_SCALER_TYPE == _RL6952_SERIES)

