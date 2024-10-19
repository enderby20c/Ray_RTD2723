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
// ID Code      : Scaler_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OPTION_H__
#define __SCALER_OPTION_H__

//--------------------------------------------------
// Input Path Option
//--------------------------------------------------
#define _HW_I_DOMAIN_M1_M2_PATH_SUPPORT             ((_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON) &&\
                                                     (_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON))

#define _HW_I_DOMAIN_S1_S2_PATH_SUPPORT             ((_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) &&\
                                                     (_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON))

#define _HW_I_DOMAIN_S3_S4_PATH_SUPPORT             ((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) &&\
                                                     (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))

//--------------------------------------------------
// Memory Type Option
//--------------------------------------------------
#if(_HW_MEMORY_TYPE == _EMBEDDED_MEMORY)

#define _MEMORY_TYPE_CONFIG                         (_EMBEDDED_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                         _EMBEDDED_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#define _SDRAM_PHASE_ON_LINE_ADDRESS                (0x1FFDF7) // 2047 row, Bank1, 248 column (remain 8 cell)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_FRC_MODE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_FRC_MODE
#define _EMBEDDED_DDR3_PWR                          (_EMBEDDED_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_POWWER_CONFIG_MASK)
#endif

#endif // End of #if(_MEMORY_TYPE == _EMBEDDED_MEMORY)

#if(_MEMORY_TYPE_CONFIG != _MEMORY_SDRAM)
#define _SDRAM_PHASE_CALIBRATION                    _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                     _OFF
#endif

//--------------------------------------------------
// D Domain 4 Path for FrameSync Line Buffer Option
//--------------------------------------------------
// #if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
// #undef _FRAME_SYNC_LINE_BUFFER_SUPPORT
// #define _FRAME_SYNC_LINE_BUFFER_SUPPORT             _ON
// #endif

//--------------------------------------------------
// Extension Related limit
//--------------------------------------------------
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define _MDOMAIN_MIN_EXTENSION                      (2)
#define _DDOMAIN_MIN_HFRONT_PORCH_SIZE              (6)
#define _DDOMAIN_MAX_EXTENSION                      (30)
#endif

//--------------------------------------------------
// CEC Related Define
//--------------------------------------------------
#define _HDMI_CEC_SUPPORT                           ((_HW_HDMI_CEC_GEN != _HW_CEC_GEN_NONE) &&\
                                                     ((_D1_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D2_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D3_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D4_HDMI_CEC_PIN == _HDMI_CEC_0)))

//--------------------------------------------------
// HDMI ARC Tx Related Define
//--------------------------------------------------
#define _HDMI_ARC_TX_MAC_SUPPORT                    ((_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP) &&\
                                                     (((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) && ((_D1_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D1_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))) ||\
                                                      ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) && ((_D2_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D2_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))) ||\
                                                      ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) && ((_D3_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D3_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))) ||\
                                                      ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) && ((_D4_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D4_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)))))

#define _HDMI_EARC_TX_MAC_SUPPORT                   ((_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP) &&\
                                                     (((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) && (_D1_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)) ||\
                                                     (((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) && (_D2_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)) ||\
                                                      ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) && (_D3_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)) ||\
                                                      ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) && (_D4_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)))))

//--------------------------------------------------
// AUDIO Related Define
//--------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
#define _AUDIO_FW_TRACKING_MODE_SUPPORT             (_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#endif

//--------------------------------------------------
// HDMI2.0 YCbCr420 Option
//--------------------------------------------------
#define _HDMI20_YCBCR420_SUPPORT                    ((_HDMI20_SUPPORT == _ON) &&\
                                                     ((_SCALER_TYPE == _RL6829_SERIES) || (_SCALER_TYPE == _RL6952_SERIES) || (_SCALER_TYPE == _RL6978_SERIES)))

//--------------------------------------------------
// TMDS Rx Mac Circuit Exist Macro Option
//--------------------------------------------------
#define _HW_TMDS_MAC_RX3_EXIST                      ((_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) ||\
                                                     (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) ||\
                                                     (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) ||\
                                                     (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) ||\
                                                     (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) ||\
                                                     (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3))

#define _HW_TMDS_MAC_RX4_EXIST                      ((_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) ||\
                                                     (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) ||\
                                                     (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) ||\
                                                     (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) ||\
                                                     (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) ||\
                                                     (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4))

//--------------------------------------------------
// TMDS Rx Mac TMDS/ HDMI/ HDMI20 Support Macro Option
//--------------------------------------------------
#define _TMDS_MAC_RX3_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)))

#define _TMDS_MAC_RX4_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)))

#define _HDMI_MAC_RX3_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)))

#define _HDMI_MAC_RX4_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)))

#define _HDMI20_MAC_RX3_SUPPORT                     (((_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) && (_D0_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) && (_D1_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) && (_D2_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) && (_D3_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) && (_D4_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3) && (_D5_HDMI20_SUPPORT == _ON)))

#define _HDMI20_MAC_RX4_SUPPORT                     (((_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) && (_D0_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) && (_D1_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) && (_D2_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) && (_D3_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) && (_D4_HDMI20_SUPPORT == _ON)) ||\
                                                     ((_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4) && (_D5_HDMI20_SUPPORT == _ON)))

#define _HDMI_FRL_MAC_RX3_SUPPORT                   (((_D1_HDMI_FRL_SUPPORT == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_HDMI_FRL_SUPPORT == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_HDMI_FRL_SUPPORT == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)))

#define _HDMI_FRL_MAC_RX4_SUPPORT                   ((_D4_HDMI_FRL_SUPPORT == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4))

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#define _RX3_TMDS_BR_SWAP                           ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (((_D0_TMDS_BR_SWAP == _OFF) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D1_TMDS_BR_SWAP == _OFF) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D2_TMDS_BR_SWAP == _OFF) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D3_TMDS_BR_SWAP == _OFF) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D4_TMDS_BR_SWAP == _OFF) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D5_TMDS_BR_SWAP == _OFF) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3))) :\
                                                                                                        (((_D0_TMDS_BR_SWAP == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D1_TMDS_BR_SWAP == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D2_TMDS_BR_SWAP == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D3_TMDS_BR_SWAP == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D4_TMDS_BR_SWAP == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                                                                         ((_D5_TMDS_BR_SWAP == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3))))

#define _RX3_TMDS_PN_SWAP                           (((_D0_TMDS_PN_SWAP == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D1_TMDS_PN_SWAP == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_TMDS_PN_SWAP == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_TMDS_PN_SWAP == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D4_TMDS_PN_SWAP == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D5_TMDS_PN_SWAP == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)))

#define _RX4_TMDS_BR_SWAP                           ((_HW_TMDS_LANE_MAPPING == _TMDS_LANE_SWAP_NONE) ? (((_D0_TMDS_BR_SWAP == _OFF) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D1_TMDS_BR_SWAP == _OFF) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D2_TMDS_BR_SWAP == _OFF) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D3_TMDS_BR_SWAP == _OFF) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D4_TMDS_BR_SWAP == _OFF) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D5_TMDS_BR_SWAP == _OFF) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4))) :\
                                                                                                        (((_D0_TMDS_BR_SWAP == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D1_TMDS_BR_SWAP == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D2_TMDS_BR_SWAP == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D3_TMDS_BR_SWAP == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D4_TMDS_BR_SWAP == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                                                                         ((_D5_TMDS_BR_SWAP == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4))))

#define _RX4_TMDS_PN_SWAP                           (((_D0_TMDS_PN_SWAP == _ON) && (_HW_D0_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D1_TMDS_PN_SWAP == _ON) && (_HW_D1_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D2_TMDS_PN_SWAP == _ON) && (_HW_D2_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D3_TMDS_PN_SWAP == _ON) && (_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D4_TMDS_PN_SWAP == _ON) && (_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D5_TMDS_PN_SWAP == _ON) && (_HW_D5_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)))

//--------------------------------------------------
// TMDS Rx PHY TMDS/ HDMI/ HDMI20 Support Macro Option
//--------------------------------------------------
#define _TMDS_PHY_RX0_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)))

#define _TMDS_PHY_RX1_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)))

#define _TMDS_PHY_RX2_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)))

#define _TMDS_PHY_RX3_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)))

#define _TMDS_PHY_RX4_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)))

#define _TMDS_PHY_RX5_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)))

#define _HDMI_PHY_RX0_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX0)))

#define _HDMI_PHY_RX1_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX1)))

#define _HDMI_PHY_RX2_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX2)))

#define _HDMI_PHY_RX3_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX3)))

#define _HDMI_PHY_RX4_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX4)))

#define _HDMI_PHY_RX5_SUPPORT                       (((_D0_HDMI_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D1_HDMI_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D2_HDMI_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D3_HDMI_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D4_HDMI_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D5_HDMI_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX5)))

#define _HDMI20_PHY_RX0_SUPPORT                     (((_D0_HDMI20_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX0) && (_D0_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D1_HDMI20_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX0) && (_D1_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D2_HDMI20_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX0) && (_D2_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D3_HDMI20_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX0) && (_D3_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D4_HDMI20_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX0) && (_D4_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D5_HDMI20_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX0) && (_D5_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)))

#define _HDMI20_PHY_RX1_SUPPORT                     (((_D0_HDMI20_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX1) && (_D0_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D1_HDMI20_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX1) && (_D1_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D2_HDMI20_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX1) && (_D2_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D3_HDMI20_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX1) && (_D3_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D4_HDMI20_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX1) && (_D4_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D5_HDMI20_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX1) && (_D5_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)))

#define _HDMI20_PHY_RX2_SUPPORT                     (((_D0_HDMI20_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D0_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D1_HDMI20_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D1_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D2_HDMI20_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D2_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D3_HDMI20_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D3_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D4_HDMI20_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D4_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D5_HDMI20_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D5_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)))

#define _HDMI20_PHY_RX3_SUPPORT                     (((_D0_HDMI20_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D0_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D1_HDMI20_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D1_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D2_HDMI20_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D2_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D3_HDMI20_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D3_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D4_HDMI20_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D4_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D5_HDMI20_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D5_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)))

#define _HDMI20_PHY_RX4_SUPPORT                     (((_D0_HDMI20_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D0_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D1_HDMI20_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D1_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D2_HDMI20_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D2_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D3_HDMI20_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D3_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D4_HDMI20_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D4_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D5_HDMI20_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D5_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)))

#define _HDMI20_PHY_RX5_SUPPORT                     (((_D0_HDMI20_SUPPORT == _ON) && (_HW_D0_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D0_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D1_HDMI20_SUPPORT == _ON) && (_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D1_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D2_HDMI20_SUPPORT == _ON) && (_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D2_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D3_HDMI20_SUPPORT == _ON) && (_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D3_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D4_HDMI20_SUPPORT == _ON) && (_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D4_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)) ||\
                                                     ((_D5_HDMI20_SUPPORT == _ON) && (_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D5_HDMI_LINK_CLK_RATE >= _HDMI_LINK_SPEED_340MHZ)))

#define _HDMI21_PHY_RX2_SUPPORT                     (((_D2_HDMI_FRL_SUPPORT == _ON) && (_HW_D2_HDMI21_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D3_HDMI_FRL_SUPPORT == _ON) && (_HW_D3_HDMI21_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D4_HDMI_FRL_SUPPORT == _ON) && (_HW_D4_HDMI21_PHY_RX_MAPPING == _MAPPING_RX2)))

#define _HDMI21_PHY_RX3_SUPPORT                     (((_D1_HDMI_FRL_SUPPORT == _ON) && (_HW_D1_HDMI21_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_HDMI_FRL_SUPPORT == _ON) && (_HW_D2_HDMI21_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D3_HDMI_FRL_SUPPORT == _ON) && (_HW_D3_HDMI21_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D4_HDMI_FRL_SUPPORT == _ON) && (_HW_D4_HDMI21_PHY_RX_MAPPING == _MAPPING_RX3)))

#define _HDMI21_PHY_RX4_SUPPORT                     (((_D2_HDMI_FRL_SUPPORT == _ON) && (_HW_D2_HDMI21_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D3_HDMI_FRL_SUPPORT == _ON) && (_HW_D3_HDMI21_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D4_HDMI_FRL_SUPPORT == _ON) && (_HW_D4_HDMI21_PHY_RX_MAPPING == _MAPPING_RX4)))

#define _RX2_PHY_HDMI_PORT                          (((_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)) ||\
                                                     ((_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)) ||\
                                                     ((_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)) ||\
                                                     ((_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX2) && (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)))

#define _RX3_PHY_HDMI_PORT                          (((_HW_D1_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)) ||\
                                                     ((_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)) ||\
                                                     ((_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)) ||\
                                                     ((_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)) ||\
                                                     ((_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX3) && (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)))

#define _RX4_PHY_HDMI_PORT                          (((_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)) ||\
                                                     ((_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)) ||\
                                                     ((_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)) ||\
                                                     ((_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX4) && (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)))

#define _RX5_PHY_HDMI_PORT                          (((_HW_D2_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)) ||\
                                                     ((_HW_D3_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)) ||\
                                                     ((_HW_D4_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)) ||\
                                                     ((_HW_D5_TMDS_PHY_RX_MAPPING == _MAPPING_RX5) && (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)))

//-------------------------------------------------
// RSV Pkt Round Robin Option
//-------------------------------------------------
#define _HDMI_VSIF_RCV_BY_RR                        ((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || ((_HDMI21_ALLM_SUPPORT == _ON) ||\
                                                     (_HDMI21_CCBPC_SUPPORT == _ON)) || (_DM_FUNCTION == _ON) || (_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON))

#define _HDMI_SPD_IF_RCV_BY_RR                      ((_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _ON) || ((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)))

#define _HDMI21_DHDR_SUPPORT                        (_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)

//--------------------------------------------------
// HDMI Power on control
//--------------------------------------------------
#define _HDMI_ON_POWER_CONTROL                      ((_HW_HDMI_ON_POWER_CONTROL == _ON) && (_HDMI_ON_POWER_CONTROL_BY_CABLE_DETECT == _ON))

//--------------------------------------------------
// DP Tx Option
//--------------------------------------------------
#define _DP_TX_SUPPORT                              (_P0_OUTPUT_TYPE == _P0_DP_PORT)

//--------------------------------------------------
// DP MST
//--------------------------------------------------
#if(_DP_SUPPORT == _OFF)
#undef _DP_MST_SUPPORT
#define _DP_MST_SUPPORT                             _OFF

#undef _D0_DP_MST_PORT_SUPPORT
#undef _D1_DP_MST_PORT_SUPPORT
#undef _D2_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                     _OFF
#define _D1_DP_MST_PORT_SUPPORT                     _OFF
#define _D2_DP_MST_PORT_SUPPORT                     _OFF

#undef _DP_TX_LOOP_BACK_DPRX_SUPPORT
#define _DP_TX_LOOP_BACK_DPRX_SUPPORT               _OFF
#else

#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
#undef _D0_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                     _OFF
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
#undef _D1_DP_MST_PORT_SUPPORT
#define _D1_DP_MST_PORT_SUPPORT                     _OFF
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_DP_PORT)
#undef _D2_DP_MST_PORT_SUPPORT
#define _D2_DP_MST_PORT_SUPPORT                     _OFF
#endif
#endif

#if(_DP_MST_SUPPORT == _OFF)
#undef _DP_MST_PXP_MODE_SUPPORT
#define _DP_MST_PXP_MODE_SUPPORT                    _OFF
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _OFF)
#undef _DP_MST_PXP_FIXED_MODE_SUPPORT
#define _DP_MST_PXP_FIXED_MODE_SUPPORT              _OFF

#undef _DP_MST_PXP_SELECT_MODE_SUPPORT
#define _DP_MST_PXP_SELECT_MODE_SUPPORT             _OFF

#undef _DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT
#define _DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT      _OFF
#endif

#define _DP_MST2SST_SUPPORT                         ((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#if(_DP_MST2SST_SUPPORT == _OFF)
#undef _DP_TX_DSC_PASSTHROUGH_SUPPORT
#define _DP_TX_DSC_PASSTHROUGH_SUPPORT              _OFF
#endif

#if(!((_DP_MST2SST_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON)))
#undef _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT
#define _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT      _OFF
#else
#ifndef _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT
#define _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT      _OFF
#endif
#endif

#if(!((_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON)))
#undef _BACKGROUND_DETECTION_DSC_DECODER_SUPPORT
#define _BACKGROUND_DETECTION_DSC_DECODER_SUPPORT   _OFF
#else
#ifndef _BACKGROUND_DETECTION_DSC_DECODER_SUPPORT
#define _BACKGROUND_DETECTION_DSC_DECODER_SUPPORT   _OFF
#endif
#endif

//--------------------------------------------------
// DP 128b132b Coding Support
//--------------------------------------------------
#define _D0_DP_128B132B_CODING_TYPE_SUPPORT         ((_D0_DP_SUPPORT == _ON) && (_D0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ))
#define _D1_DP_128B132B_CODING_TYPE_SUPPORT         ((_D1_DP_SUPPORT == _ON) && (_D1_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ))
#define _D2_DP_128B132B_CODING_TYPE_SUPPORT         ((_D2_DP_SUPPORT == _ON) && (_D2_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ))

#define _DP_RX_128B132B_CODING_TYPE_SUPPORT         ((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) || (_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) || (_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON))

#define _DP_MST_RX_128B132B_CODING_TYPE_SUPPORT     (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON)) ||\
                                                      ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON)) ||\
                                                      ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_D2_DP_MST_PORT_SUPPORT == _ON)))

//--------------------------------------------------
// DP Rx Mac Dphy Support Macro Option
//--------------------------------------------------
#define _DP_MAC_DPHY_RX0_SUPPORT                    (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)))

#define _DP_MAC_DPHY_RX1_SUPPORT                    (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)))

#define _DP_MAC_DPHY_RX2_SUPPORT                    (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)))


#if((_D7_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX0_SUPPORT == _ON) && (_DP_MAC_DPHY_RX1_SUPPORT == _ON))
#define _DUAL_DP_MAC_DPHY_USE                       _DUAL_DP_MAC_DPHY_RX0RX1
#elif((_D8_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX1_SUPPORT == _ON) && (_DP_MAC_DPHY_RX2_SUPPORT == _ON))
#define _DUAL_DP_MAC_DPHY_USE                       _DUAL_DP_MAC_DPHY_RX1RX2
#else
#define _DUAL_DP_MAC_DPHY_USE                       _DUAL_DP_MAC_DPHY_NONE
#endif

//--------------------------------------------------
// DP Rx Mac Stream Arbiter Option
//--------------------------------------------------
#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
#if(_DP_MST2SST_SUPPORT == _ON)
#define _DP_RX_MAC_STREAM_MST2SST_ASSIGN            (_MAPPING_RX2)
#elif(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
#define _DP_RX_MAC_STREAM_BG_ASSIGN                 (_MAPPING_RX2)
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
#ifndef _DP_RX_MAC_STREAM_BG_ASSIGN
#define _DP_RX_MAC_STREAM_BG_ASSIGN                 (_MAPPING_RX1)
#endif
#endif
#endif

// Avoid Compile Error
#ifndef _DP_RX_MAC_STREAM_MST2SST_ASSIGN
#define _DP_RX_MAC_STREAM_MST2SST_ASSIGN            (_MAPPING_RX_MAP_NONE)
#endif

#ifndef _DP_RX_MAC_STREAM_BG_ASSIGN
#define _DP_RX_MAC_STREAM_BG_ASSIGN                 (_MAPPING_RX_MAP_NONE)
#endif

//--------------------------------------------------
// DP Rx Mac Support Macro Option
//--------------------------------------------------
#define _DP_MAC_RX0_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && ((_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) || (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && ((_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) || (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && ((_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) || (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) ||\
                                                     ((_DP_SUPPORT == _ON) && ((_DP_MST2SST_SUPPORT == _ON) && (_DP_RX_MAC_STREAM_MST2SST_ASSIGN == _MAPPING_RX0))) ||\
                                                     ((_DP_SUPPORT == _ON) && ((_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON) && (_DP_RX_MAC_STREAM_BG_ASSIGN == _MAPPING_RX0))))

#define _DP_MAC_RX1_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) >= 2) ||\
                                                     ((_DP_SUPPORT == _ON) && ((_DP_MST2SST_SUPPORT == _ON) && (_DP_RX_MAC_STREAM_MST2SST_ASSIGN == _MAPPING_RX1))) ||\
                                                     ((_DP_SUPPORT == _ON) && ((_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON) && (_DP_RX_MAC_STREAM_BG_ASSIGN == _MAPPING_RX1))))

#define _DP_MAC_RX2_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) +\
                                                       ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) >= 3) ||\
                                                     ((_DP_SUPPORT == _ON) && ((_DP_MST2SST_SUPPORT == _ON) && (_DP_RX_MAC_STREAM_MST2SST_ASSIGN == _MAPPING_RX2))) ||\
                                                     ((_DP_SUPPORT == _ON) && ((_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON) && (_DP_RX_MAC_STREAM_BG_ASSIGN == _MAPPING_RX2))))

#define _DP_MAC_RX3_SUPPORT                         ((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX3))

#define _DP_MAC_RX4_SUPPORT                         ((_DP_SUPPORT == _ON) && (_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX4))

#define _DP_MAC_AVAILABLE_NUMBER                    ((_DP_MAC_RX0_SUPPORT == _ON) + (_DP_MAC_RX1_SUPPORT == _ON) + (_DP_MAC_RX2_SUPPORT == _ON) + (_DP_MAC_RX3_SUPPORT == _ON) + (_DP_MAC_RX4_SUPPORT == _ON))

#if((_D7_DP_SUPPORT == _ON) && (_DP_MAC_RX0_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
#define _DUAL_DP_MAC_USE                            _DUAL_DP_MAC_RX0RX1
#elif((_D8_DP_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON) && (_DP_MAC_RX2_SUPPORT == _ON))
#define _DUAL_DP_MAC_USE                            _DUAL_DP_MAC_RX1RX2
#else
#define _DUAL_DP_MAC_USE                            _DUAL_DP_MAC_NONE
#endif

//--------------------------------------------------
// DP MAC Rx 128b132b Coding Support
//--------------------------------------------------
#define _DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && ((_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) || (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && ((_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) || (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && ((_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) || (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))))

#define _DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT    ((_DP_MAC_RX1_SUPPORT == _ON) &&\
                                                      (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) &&\
                                                         ((_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1) || (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2) ||\
                                                          ((_D0_DP_MST_PORT_SUPPORT == _ON) && (((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) ||\
                                                                                                 ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))) ||\
                                                        ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) &&\
                                                         ((_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1) || (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2) ||\
                                                          ((_D1_DP_MST_PORT_SUPPORT == _ON) && (((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) ||\
                                                                                                  ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))) ||\
                                                         ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) &&\
                                                         ((_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1) || (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2) ||\
                                                          ((_D2_DP_MST_PORT_SUPPORT == _ON) && (((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) ||\
                                                                                                  ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))))))))

#define _DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT    ((_DP_MAC_RX2_SUPPORT == _ON) &&\
                                                      (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) &&\
                                                         ((_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2) || (_HW_D0_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2) ||\
                                                          ((_D0_DP_MST_PORT_SUPPORT == _ON) && (((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) ||\
                                                                                                 ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))) ||\
                                                        ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) &&\
                                                         ((_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2) || (_HW_D1_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2) ||\
                                                          ((_D1_DP_MST_PORT_SUPPORT == _ON) && (((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) ||\
                                                                                                  ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))) ||\
                                                         ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) &&\
                                                         ((_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2) || (_HW_D2_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2) ||\
                                                          ((_D2_DP_MST_PORT_SUPPORT == _ON) && (((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_HW_D9_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)) ||\
                                                                                                  ((_DP_MST2SST_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2))))))))

#define _DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT    ((_DP_MAC_RX3_SUPPORT == _ON) && (_DP_MST_RX_128B132B_CODING_TYPE_SUPPORT == _ON))

#define _DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT    ((_DP_MAC_RX4_SUPPORT == _ON) && (_DP_MST_RX_128B132B_CODING_TYPE_SUPPORT == _ON))

#define _DP_MAC_RX_128B132B_CODING_TYPE_SUPPORT     ((_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON) ||\
                                                     (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON) ||\
                                                     (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON) ||\
                                                     (_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON) ||\
                                                     (_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON))

//--------------------------------------------------
// DP MAC Rx Pixel Mode Support Macro Option
//--------------------------------------------------
#define _DP_MAC_RX_128B132B_FOUR_PIXEL_MODE_SUPPORT (_HW_DP_MAC_MAX_PIXEL_MODE_128B132B == _DP_MAC_STREAM_RX_FOUR_PIXEL_MODE)

//--------------------------------
// DP Rx PHY Support Macro Option
//--------------------------------
#define _DP_PHY_RX0_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX0)))

#define _DP_PHY_RX1_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX1)))

#define _DP_PHY_RX2_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX2)))

#define _DP_PHY_RX3_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX3)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX3)))

#define _DP_PHY_RX4_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX4)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX4)))

#define _DP_PHY_RX5_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX5)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX5)))

//--------------------------------------------------
// DP PHY Rx 128b132b Coding Support
//--------------------------------------------------
#define _DP_PHY_RX0_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX0)))

#define _DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX1)))

#define _DP_PHY_RX2_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D0_DP_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D1_DP_PHY_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D2_DP_PHY_RX_MAPPING == _MAPPING_RX2)))

//--------------------------------
// DP Rx AUX Support Macro Option
//--------------------------------
#define _DP_AUX_RX0_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX0)))

#define _DP_AUX_RX1_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX1)))

#define _DP_AUX_RX2_SUPPORT                         (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX2)))

//--------------------------------------------------
// DP Rx ASSR Support Macro Option
//--------------------------------------------------
#define _DP_AUX_RX0_ASSR_SUPPORT                    (((_D0_DP_SUPPORT == _ON) && (_D0_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_D1_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_D2_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX0)))

#define _DP_AUX_RX1_ASSR_SUPPORT                    (((_D0_DP_SUPPORT == _ON) && (_D0_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_D1_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_D2_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX1)))

#define _DP_AUX_RX2_ASSR_SUPPORT                    (((_D0_DP_SUPPORT == _ON) && (_D0_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_D1_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_D2_DP_ASSR_MODE_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX2)))

//--------------------------------------------------
// DP AUX Rx 128b132b Coding Support
//--------------------------------------------------
#define _DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX0)))

#define _DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX1)))

#define _DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT    (((_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D0_DP_AUX_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D1_DP_AUX_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON) && (_HW_D2_DP_AUX_RX_MAPPING == _MAPPING_RX2)))
//--------------------------------
// DP FEC Define Option
//--------------------------------
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define _DP_RX_FEC_SUPPORT                          _ON
#else
#define _DP_RX_FEC_SUPPORT                          ((_DP_RX_DSC_DECODER_SUPPORT == _ON) ||\
                                                     (_DP_PR_MODE_SUPPORT == _ON) ||\
                                                     ((_DP_TX_SUPPORT == _ON) &&\
                                                      (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)))
#endif

#define _DP_TX_FEC_SUPPORT                          ((_DP_TX_SUPPORT == _ON) &&\
                                                     ((_DP_RX_FEC_SUPPORT == _ON) ||\
                                                      (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)))

#define _DP_RX_FEC_WEAK_MODE_GATED_SUPPORT          ((_DP_RX_FEC_SUPPORT == _ON) && (_HW_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _ON))


//--------------------------------
// DP Mac DM Support
//--------------------------------
#define _DP_MAC_RX0_DM_SUPPORT                      ((_DP_MAC_RX0_SUPPORT == _ON) && (_DM_FUNCTION == _ON))
#define _DP_MAC_RX1_DM_SUPPORT                      ((_DP_MAC_RX1_SUPPORT == _ON) && (_DM_FUNCTION == _ON))
#define _DP_MAC_RX2_DM_SUPPORT                      ((_DP_MAC_RX2_SUPPORT == _ON) && (_DM_FUNCTION == _ON))
#define _DP_MAC_RX3_DM_SUPPORT                      _OFF
#define _DP_MAC_RX4_DM_SUPPORT                      _OFF

//--------------------------------
// DP Mac ADVANCED HDR10 Support
//--------------------------------
#define _DP_MAC_RX0_ADVANCED_HDR10_SUPPORT          ((_DP_MAC_RX0_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE))
#define _DP_MAC_RX1_ADVANCED_HDR10_SUPPORT          ((_DP_MAC_RX1_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE))
#define _DP_MAC_RX2_ADVANCED_HDR10_SUPPORT          ((_DP_MAC_RX2_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE))
#define _DP_MAC_RX3_ADVANCED_HDR10_SUPPORT          _OFF
#define _DP_MAC_RX4_ADVANCED_HDR10_SUPPORT          _OFF

//--------------------------------
// DP Aux-Less ALPM Option
//--------------------------------
#define _D0_DP_AUXLESS_ALPM_SUPPORT                 ((_D0_DP_SUPPORT == _ON) && (_DP_AUXLESS_ALPM_SUPPORT == _ON) && (_HW_DP_D0_AUXLESS_ALPM_SUPPORT == _ON))
#define _D1_DP_AUXLESS_ALPM_SUPPORT                 ((_D1_DP_SUPPORT == _ON) && (_DP_AUXLESS_ALPM_SUPPORT == _ON) && (_HW_DP_D1_AUXLESS_ALPM_SUPPORT == _ON))
#define _D2_DP_AUXLESS_ALPM_SUPPORT                 ((_D2_DP_SUPPORT == _ON) && (_DP_AUXLESS_ALPM_SUPPORT == _ON) && (_HW_DP_D2_AUXLESS_ALPM_SUPPORT == _ON))

//--------------------------------------------------
// DP HDCP Support Macro Option
//--------------------------------------------------
// RX Option -- Layer1
#define _DP_HDCP14_RX0_SUPPORT                      (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_HDCP_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_HDCP_RX_MAPPING == _MAPPING_RX0)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_HDCP_RX_MAPPING == _MAPPING_RX0)))

#define _DP_HDCP14_RX1_SUPPORT                      (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_HDCP_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_HDCP_RX_MAPPING == _MAPPING_RX1)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_HDCP_RX_MAPPING == _MAPPING_RX1)))

#define _DP_HDCP14_RX2_SUPPORT                      (((_D0_DP_SUPPORT == _ON) && (_HW_D0_DP_HDCP_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_HW_D1_DP_HDCP_RX_MAPPING == _MAPPING_RX2)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_HW_D2_DP_HDCP_RX_MAPPING == _MAPPING_RX2)))

#define _DP_HDCP2_RX0_SUPPORT                       ((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_HDCP14_RX0_SUPPORT == _ON))
#define _DP_HDCP2_RX1_SUPPORT                       ((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_HDCP14_RX1_SUPPORT == _ON))
#define _DP_HDCP2_RX2_SUPPORT                       ((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_HDCP14_RX2_SUPPORT == _ON))

#define _DP_HDCP14_RX0_REPEATER_SUPPORT             ((_DP_HDCP14_RX0_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define _DP_HDCP14_RX1_REPEATER_SUPPORT             ((_DP_HDCP14_RX1_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define _DP_HDCP14_RX2_REPEATER_SUPPORT             ((_DP_HDCP14_RX2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#define _DP_HDCP2_RX0_REPEATER_SUPPORT              ((_DP_HDCP2_RX0_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define _DP_HDCP2_RX1_REPEATER_SUPPORT              ((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define _DP_HDCP2_RX2_REPEATER_SUPPORT              ((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

// RX Option -- Layer2
#define _DP_HDCP14_RX_SUPPORT                       ((_DP_HDCP14_RX0_SUPPORT == _ON) ||\
                                                     (_DP_HDCP14_RX1_SUPPORT == _ON) ||\
                                                     (_DP_HDCP14_RX2_SUPPORT == _ON))

#define _DP_HDCP2_RX_SUPPORT                        ((_DP_HDCP2_RX0_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX1_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX2_SUPPORT == _ON))

#define _DP_HDCP14_RX_REPEATER_SUPPORT              ((_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON))

#define _DP_HDCP2_RX_REPEATER_SUPPORT               ((_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON))

#define _DP_HDCP_RX0_SUPPORT                        ((_DP_HDCP2_RX0_SUPPORT == _ON) || (_DP_HDCP14_RX0_SUPPORT == _ON))
#define _DP_HDCP_RX1_SUPPORT                        ((_DP_HDCP2_RX1_SUPPORT == _ON) || (_DP_HDCP14_RX1_SUPPORT == _ON))
#define _DP_HDCP_RX2_SUPPORT                        ((_DP_HDCP2_RX2_SUPPORT == _ON) || (_DP_HDCP14_RX2_SUPPORT == _ON))

#define _DP_HDCP_RX0_REPEATER_SUPPORT               ((_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON))

#define _DP_HDCP_RX1_REPEATER_SUPPORT               ((_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON))

#define _DP_HDCP_RX2_REPEATER_SUPPORT               ((_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON) ||\
                                                     (_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON))

// RX Option -- Layer3
#define _DP_HDCP_RX_SUPPORT                         ((_DP_HDCP2_RX_SUPPORT == _ON) || (_DP_HDCP14_RX_SUPPORT == _ON))

//--------------------------------------------------
// Hdcp Related Define
//--------------------------------------------------
#define _DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT        _ON

//--------------------------------------------------
// DP Sdp Meta Sram Support
//--------------------------------------------------
#define _DP_SDP_META_SRAM_SUPPORT                   (_HW_DP_SDP_META_SRAM_DB_LENGTH != 0x00)

//--------------------------------------------------
// DP SDP META PAYLOAD Length:
// NOTE: SUM < META SRAM LENGTH, MUST TO BE CONFIRM
//--------------------------------------------------
#if(_DP_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
#define _DP_SDP_META_0_PAYLOAD_LENGTH               32
#elif(_DM_FUNCTION == _ON)
#define _DP_SDP_META_0_PAYLOAD_LENGTH               32
#else
#define _DP_SDP_META_0_PAYLOAD_LENGTH               0
#endif
#define _DP_SDP_META_1_PAYLOAD_LENGTH               0
#define _DP_SDP_META_2_PAYLOAD_LENGTH               0
#define _DP_SDP_META_3_PAYLOAD_LENGTH               0
#define _DP_SDP_META_4_PAYLOAD_LENGTH               0


//--------------------------------------------------
// Definitions of Hdcp2.2 Repeater Support
//--------------------------------------------------
#define _DP_AUX_RX0_HDCP22_REPEATER_SUPPORT         ((_DP_AUX_RX0_SUPPORT == _ON) &&\
                                                     (_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#define _DP_AUX_RX2_HDCP22_REPEATER_SUPPORT         ((_DP_AUX_RX1_SUPPORT == _ON) &&\
                                                     (_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#define _DP_AUX_RX1_HDCP22_REPEATER_SUPPORT         ((_DP_AUX_RX2_SUPPORT == _ON) &&\
                                                     (_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

//--------------------------------------------------
// DP Tx Channel Coding Type Support
//--------------------------------------------------
#define _DP_TX_128B132B_CODING_TYPE_SUPPORT         ((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON) && (_P0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ))


//--------------------------------------------------
// DP Tx Dp128b132b to 8b10b Option
//--------------------------------------------------
#define _DP_HW_TX_128B132B_TO_8B10B_ADDR_PORT_AUTO_INC_SUPPORT\
                                                    _ON

//--------------------------------------------------
// DP DownStream Count Option
//--------------------------------------------------
#if(_DP_TX_SUPPORT == _OFF)
#undef _DP_1_1_DOWN_STREAM_PORT_COUNT
#undef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT              0x00
#define _DP_1_2_DOWN_STREAM_PORT_COUNT              0x00

#undef _DP_TX_DSC_PASSTHROUGH_SUPPORT
#define _DP_TX_DSC_PASSTHROUGH_SUPPORT              _OFF

#undef _DP_TX_SST_CLONE_PATH_TYPE
#define _DP_TX_SST_CLONE_PATH_TYPE                  _DP_TX_CLONE_VESA_STREAM_ONLY
#endif

//--------------------------------------------------
// DP Tx Mac/Phy Support Macro Option
//--------------------------------------------------
#define _DP_MAC_TX_SUPPORT                          (_DP_TX_SUPPORT == _ON)
#define _DP_PHY_TX_SUPPORT                          (_DP_TX_SUPPORT == _ON)

//--------------------------------------------------
// DP DPCD No Physical Address Support Option
//--------------------------------------------------
// #define _HW_DP_DPCD_NO_PHYSICAL_ADDRESS_SUPPORT     (_HW_DP_DPCD_NO_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)

//--------------------------------------------------
// Horizontal Blanking Expansion (HBE) and Reduction (HBR) Option
//--------------------------------------------------
#define _DP_HBLANKING_MODIFY_SUPPORT                ((_DP_HBE_SUPPORT == _ON) || (_DP_HBLANKING_REDUCTION_SUPPORT == _ON))

//--------------------------------------------------
// DSC MAC Option
//--------------------------------------------------
#define GET_DSC_MAC_SUPPORT(x)                      (((x) != _DSC_MAC_NONE) ? _ON : _OFF)
#define GET_DSC_MAC0_SUPPORT(x)                     ((((x) & _DSC_MAC_0) == _DSC_MAC_0) ? _ON : _OFF)
#define GET_DSC_MAC1_SUPPORT(x)                     ((((x) & _DSC_MAC_1) == _DSC_MAC_1) ? _ON : _OFF)

#define _DP_PHY_RX0_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_PHY_RX0_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX0_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX0_DSC_MAPPING) == _ON)))

#define _DP_PHY_RX1_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_PHY_RX1_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX1_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX1_DSC_MAPPING) == _ON)))

#define _DP_PHY_RX2_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX2_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX2_DSC_MAPPING) == _ON)))

#define _DP_MAC_RX0_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_MAC_RX0_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX0_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX0_DSC_MAPPING) == _ON)))

#define _DP_MAC_RX1_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX1_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX1_DSC_MAPPING) == _ON)))

#define _DP_MAC_RX2_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_MAC_RX2_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX2_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX2_DSC_MAPPING) == _ON)))

#define _DP_MAC_RX3_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_MAC_RX3_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX3_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX3_DSC_MAPPING) == _ON)))

#define _DP_MAC_RX4_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_MAC_RX4_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX4_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX4_DSC_MAPPING) == _ON)))

#define _DP_AUX_RX0_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_AUX_RX0_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_AUX_RX0_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_AUX_RX0_DSC_MAPPING) == _ON)))

#define _DP_AUX_RX1_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_AUX_RX1_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_AUX_RX1_DSC_MAPPING) == _ON)))

#define _DP_AUX_RX2_DSC_DECODER_SUPPORT             ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_DP_AUX_RX2_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_DP_AUX_RX2_DSC_MAPPING) == _ON)))

#define _DP_AUX_RX7_DSC_DECODER_SUPPORT             ((_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON) && (_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON))

#define _DP_AUX_RX8_DSC_DECODER_SUPPORT             ((_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON) && (_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON))

#define _HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT       ((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_TMDS_MAC_RX3_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_TMDS_MAC_RX3_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_TMDS_MAC_RX3_DSC_MAPPING) == _ON)))

#define _HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT       ((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_TMDS_MAC_RX4_SUPPORT == _ON) &&\
                                                     ((GET_DSC_MAC0_SUPPORT(_HW_TMDS_MAC_RX4_DSC_MAPPING) == _ON) ||\
                                                      (GET_DSC_MAC1_SUPPORT(_HW_TMDS_MAC_RX4_DSC_MAPPING) == _ON)))

#define _DSC_MAC_DECODER_0_SUPPORT                  ((_DSC_DECODER_SUPPORT == _ON) &&\
                                                     (((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX0_DSC_MAPPING) == _ON) && (_DP_MAC_RX0_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX1_DSC_MAPPING) == _ON) && (_DP_MAC_RX1_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC0_SUPPORT(_HW_DP_MAC_RX2_DSC_MAPPING) == _ON) && (_DP_MAC_RX2_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC0_SUPPORT(_HW_TMDS_MAC_RX3_DSC_MAPPING) == _ON) && (_HDMI_FRL_MAC_RX3_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC0_SUPPORT(_HW_TMDS_MAC_RX4_DSC_MAPPING) == _ON) && (_HDMI_FRL_MAC_RX4_SUPPORT == _ON))))

#define _DSC_MAC_DECODER_1_SUPPORT                  ((_DSC_DECODER_SUPPORT == _ON) &&\
                                                     (((GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX0_DSC_MAPPING) == _ON) && (_DP_MAC_RX0_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX1_DSC_MAPPING) == _ON) && (_DP_MAC_RX1_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC1_SUPPORT(_HW_DP_MAC_RX2_DSC_MAPPING) == _ON) && (_DP_MAC_RX2_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC1_SUPPORT(_HW_TMDS_MAC_RX3_DSC_MAPPING) == _ON) && (_HDMI_FRL_MAC_RX3_SUPPORT == _ON)) ||\
                                                      ((GET_DSC_MAC1_SUPPORT(_HW_TMDS_MAC_RX4_DSC_MAPPING) == _ON) && (_HDMI_FRL_MAC_RX4_SUPPORT == _ON))))

#define _DSC_MAC_DECODER_SUPPORT                    ((_DSC_MAC_DECODER_0_SUPPORT == _ON) ||\
                                                     (_DSC_MAC_DECODER_1_SUPPORT == _ON))

#define _DSC_MAC_MAX_COUNT                          (_DSC_MAC_DECODER_0_SUPPORT + _DSC_MAC_DECODER_1_SUPPORT)

//--------------------------------------------------
// DP Mac Switch Support
//--------------------------------------------------
#define _DP_MAC_SWITCH_SUPPORT                      ((_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON) || (_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON))

//--------------------------------------------------
// Embeded TypeC 0 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_EMB_TYPE_C_0_SUPPORT == _ON)
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_D0_TYPE_C_PORT
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_D1_TYPE_C_PORT
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_D2_TYPE_C_PORT
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_P0_TYPE_C_PORT
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_P1_TYPE_C_PORT
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_P2_TYPE_C_PORT
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_P3_TYPE_C_PORT
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_P4_TYPE_C_PORT
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#else
#define _EMB_TYPE_C_0_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_EMB_TYPE_C_0_SUPPORT == _ON)

//--------------------------------------------------
// Embeded TypeC 1 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_EMB_TYPE_C_1_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D0_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_D0_TYPE_C_PORT
#elif((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D1_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_D1_TYPE_C_PORT
#elif((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D2_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_D2_TYPE_C_PORT
#elif((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P0_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_P0_TYPE_C_PORT
#elif((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P1_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_P1_TYPE_C_PORT
#elif((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P2_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_P2_TYPE_C_PORT
#elif((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P3_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_P3_TYPE_C_PORT
#elif((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P4_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_P4_TYPE_C_PORT
#elif((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#else
#define _EMB_TYPE_C_1_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_EMB_TYPE_C_1_SUPPORT == _ON)

//--------------------------------------------------
// Embeded TypeC 2 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_EMB_TYPE_C_2_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_D0_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_D0_TYPE_C_PORT
#elif((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D1_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_D1_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_D1_TYPE_C_PORT
#elif((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D2_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_D2_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_D2_TYPE_C_PORT
#elif((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P0_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P0_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_P0_TYPE_C_PORT
#elif((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P1_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P1_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_P1_TYPE_C_PORT
#elif((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P2_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P2_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_P2_TYPE_C_PORT
#elif((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P3_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P3_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_P3_TYPE_C_PORT
#elif((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P4_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P4_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_P4_TYPE_C_PORT
#elif((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#else
#define _EMB_TYPE_C_2_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_EMB_TYPE_C_2_SUPPORT == _ON)

//--------------------------------------------------
// Embeded TypeC 3 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_EMB_TYPE_C_3_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_D0_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_D0_TYPE_C_PORT
#elif((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D1_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_D1_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_D1_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_D1_TYPE_C_PORT
#elif((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_D2_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_D2_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_D2_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_D2_TYPE_C_PORT
#elif((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P0_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P0_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_P0_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_P0_TYPE_C_PORT
#elif((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P1_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P1_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_P1_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_P1_TYPE_C_PORT
#elif((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P2_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P2_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_P2_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_P2_TYPE_C_PORT
#elif((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P3_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P3_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_P3_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_P3_TYPE_C_PORT
#elif((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_P4_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_P4_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_P4_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_P4_TYPE_C_PORT
#elif((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) && (_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_2_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_D3_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#else
#define _EMB_TYPE_C_3_MAPPING                       _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_EMB_TYPE_C_3_SUPPORT == _ON)

//--------------------------------------------------
// Embeded TypeC 0 Mapping to PMIC
//--------------------------------------------------
#if(_EMB_TYPE_C_0_MAPPING == _VALUE_D0_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _D0_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _D0_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _D0_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _D0_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _D0_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _D0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _D0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _D0_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _D0_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _D0_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _D0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _D0_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _D0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_D1_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _D1_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _D1_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _D1_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _D1_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _D1_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _D1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _D1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _D1_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _D1_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _D1_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _D1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _D1_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _D1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_D2_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _D2_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _D2_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _D2_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _D2_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _D2_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _D2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _D2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _D2_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _D2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _D2_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _D2_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _D2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _D2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _D2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _D2_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _D2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _D2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _D2_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_D2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_D2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P0_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _P0_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _P0_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _P0_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _P0_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _P0_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _P0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _P0_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _P0_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _P0_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _P0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _P0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _P0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _P0_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _P0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P1_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _P1_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _P1_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _P1_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _P1_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _P1_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _P1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _P1_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _P1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _P1_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _P1_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _P1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _P1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _P1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _P1_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _P1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _P1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _P1_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_P1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P2_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _P2_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _P2_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _P2_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _P2_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _P2_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _P2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _P2_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _P2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _P2_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _P2_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _P2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _P2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _P2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _P2_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _P2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _P2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _P2_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_P2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P3_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _P3_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _P3_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _P3_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _P3_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _P3_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _P3_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P3_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _P3_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _P3_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _P3_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _P3_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _P3_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _P3_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _P3_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _P3_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _P3_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _P3_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _P3_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_P3_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P3_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P4_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _P4_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _P4_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _P4_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _P4_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _P4_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _P4_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P4_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _P4_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _P4_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _P4_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _P4_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _P4_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _P4_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _P4_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _P4_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _P4_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _P4_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _P4_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_P4_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P4_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
#define _EMB_TYPE_C_0_PMIC_TYPE                     _ADAPTOR_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_0_PMIC_IIC                      _ADAPTOR_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _ADAPTOR_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _ADAPTOR_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE         _ADAPTOR_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO  _ADAPTOR_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT         _ADAPTOR_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         _ADAPTOR_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         _ADAPTOR_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     _ADAPTOR_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    _ADAPTOR_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _ADAPTOR_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       _ADAPTOR_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    _ADAPTOR_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _ADAPTOR_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            ((_ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#else
#define _EMB_TYPE_C_0_PMIC_TYPE                     _PMIC_NONE
#define _EMB_TYPE_C_0_PMIC_SLAVE_ADDRESS            0x00
#define _EMB_TYPE_C_0_PMIC_IIC                      _PMIC_NO_IIC_PIN
#define _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL         _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL         _TYPE_C_PMIC_ADC_MAPPING_NONE

#define _EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT       _OFF
#define _EMB_TYPE_C_0_PMIC_FW_OVP_THRESHOLD         130
#define _EMB_TYPE_C_0_PMIC_FW_UVP_THRESHOLD         66

#define _EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD    _TYPE_C_PMIC_FW_OCP_NONE
#define _EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE     100
#define _EMB_TYPE_C_0_PMIC_FW_OCP_DELAY_SHUTDOWN    0

#define _EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT   _OFF
#define _EMB_TYPE_C_0_PMIC_SAFETY_POWER_LIMIT       100
#define _EMB_TYPE_C_0_PMIC_SAFETY_DELAY_SHUTDOWN    1000

#define _EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD     _TYPE_C_PMIC_INT_PIN_NONE
#define _EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION     _OFF

#define _EMB_TYPE_C_0_PMIC_CHECK_SUPPORT            _OFF

#endif

//--------------------------------------------------
// Embeded TypeC 1 Mapping to PMIC
//--------------------------------------------------
#if(_EMB_TYPE_C_1_MAPPING == _VALUE_D0_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _D0_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _D0_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _D0_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _D0_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _D0_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _D0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _D0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _D0_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _D0_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _D0_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _D0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _D0_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _D0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_D1_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _D1_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _D1_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _D1_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _D1_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _D1_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _D1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _D1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _D1_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _D1_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _D1_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _D1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _D1_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _D1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_D2_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _D2_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _D2_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _D2_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _D2_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _D2_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _D2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _D2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _D2_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _D2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _D2_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _D2_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _D2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _D2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _D2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _D2_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _D2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _D2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _D2_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_D2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_D2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P0_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _P0_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _P0_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _P0_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _P0_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _P0_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _P0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _P0_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _P0_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _P0_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _P0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _P0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _P0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _P0_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _P0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P1_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _P1_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _P1_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _P1_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _P1_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _P1_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _P1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _P1_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _P1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _P1_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _P1_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _P1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _P1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _P1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _P1_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _P1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _P1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _P1_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_P1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P2_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _P2_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _P2_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _P2_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _P2_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _P2_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _P2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _P2_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _P2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _P2_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _P2_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _P2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _P2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _P2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _P2_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _P2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _P2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _P2_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_P2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P3_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _P3_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _P3_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _P3_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _P3_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _P3_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _P3_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P3_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _P3_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _P3_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _P3_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _P3_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _P3_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _P3_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _P3_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _P3_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _P3_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _P3_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _P3_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_P3_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P3_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_P4_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _P4_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _P4_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _P4_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _P4_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _P4_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _P4_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _P4_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _P4_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _P4_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _P4_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _P4_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _P4_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _P4_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _P4_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _P4_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _P4_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _P4_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _P4_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_P4_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_P4_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
#define _EMB_TYPE_C_1_PMIC_TYPE                     _ADAPTOR_TYPE_C_PMIC_TYPE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS
#define _EMB_TYPE_C_1_PMIC_IIC                      _ADAPTOR_TYPE_C_PMIC_IIC
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _ADAPTOR_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _ADAPTOR_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE         _ADAPTOR_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO  _ADAPTOR_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT         _ADAPTOR_TYPE_C_PMIC_IOUT_MAX_CURRENT

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         _ADAPTOR_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         _ADAPTOR_TYPE_C_PMIC_FW_UVP_THRESHOLD

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     _ADAPTOR_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    _ADAPTOR_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _ADAPTOR_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       _ADAPTOR_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    _ADAPTOR_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _ADAPTOR_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            ((_ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                     (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

#else
#define _EMB_TYPE_C_1_PMIC_TYPE                     _PMIC_NONE
#define _EMB_TYPE_C_1_PMIC_SLAVE_ADDRESS            0x00
#define _EMB_TYPE_C_1_PMIC_IIC                      _PMIC_NO_IIC_PIN
#define _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL         _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL         _TYPE_C_PMIC_ADC_MAPPING_NONE

#define _EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT       _OFF
#define _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD         130
#define _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD         66

#define _EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD    _TYPE_C_PMIC_FW_OCP_NONE
#define _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE     100
#define _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN    0

#define _EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT   _OFF
#define _EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT       100
#define _EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN    1000

#define _EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD     _TYPE_C_PMIC_INT_PIN_NONE
#define _EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION     _OFF

#define _EMB_TYPE_C_1_PMIC_CHECK_SUPPORT            _OFF

#endif

//--------------------------------------------------
// Local Power for Embeded TypeC Mapping to PMIC
//--------------------------------------------------
#if((_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _LOCAL_POWER_VBUS_ADC_CHANNEL               _ADAPTOR_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _LOCAL_POWER_IOUT_ADC_CHANNEL               _ADAPTOR_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _LOCAL_POWER_VBUS_MAX_VOLTAGE               _ADAPTOR_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _LOCAL_POWER_IOUT_MAX_CURRENT               _ADAPTOR_TYPE_C_PMIC_IOUT_MAX_CURRENT

#else

#if(_EMB_TYPE_C_0_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
#define _LOCAL_POWER_VBUS_ADC_CHANNEL               _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL
#define _LOCAL_POWER_IOUT_ADC_CHANNEL               _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL
#define _LOCAL_POWER_VBUS_MAX_VOLTAGE               _EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE
#define _LOCAL_POWER_IOUT_MAX_CURRENT               _EMB_TYPE_C_0_PMIC_IOUT_MAX_CURRENT

#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
#define _LOCAL_POWER_VBUS_ADC_CHANNEL               _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL
#define _LOCAL_POWER_IOUT_ADC_CHANNEL               _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL
#define _LOCAL_POWER_VBUS_MAX_VOLTAGE               _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE
#define _LOCAL_POWER_IOUT_MAX_CURRENT               _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT

#else
#define _LOCAL_POWER_VBUS_ADC_CHANNEL               _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _LOCAL_POWER_IOUT_ADC_CHANNEL               _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#endif


//--------------------------------------------------
// TypeC AC ON RECONNECT Option (For Embedded Port Ctrl)
//--------------------------------------------------
#define _D0_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _D1_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _D2_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_D2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _P0_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_P0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _P1_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_P1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _P2_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_P2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _P3_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_P3_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _P4_TYPE_C_CC_AC_ON_RECONNECT               ((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) &&\
                                                     (_P4_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) &&\
                                                     (_TYPE_C_EMB_CTS_FLOW == _OFF))

#define _ADAPTOR_TYPE_C_CC_AC_ON_RECONNECT          _OFF

//--------------------------------------------------
// TCPM 0 TCPC 0 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_TCPM_0_0_SUPPORT == _ON)
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_D0_TYPE_C_PORT
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_D1_TYPE_C_PORT
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_D2_TYPE_C_PORT
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_P0_TYPE_C_PORT
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_P1_TYPE_C_PORT
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_P2_TYPE_C_PORT
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_P3_TYPE_C_PORT
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_P4_TYPE_C_PORT
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#define _HW_TCPM_0_0_MAPPING                        _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _HW_TCPM_0_0_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
#else
#define _HW_TCPM_0_0_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_TCPM_0_0_SUPPORT == _ON)

//--------------------------------------------------
// TCPM 0 TCPC 1 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_TCPM_0_1_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D0_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_D0_TYPE_C_PORT
#elif((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D1_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_D1_TYPE_C_PORT
#elif((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D2_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_D2_TYPE_C_PORT
#elif((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P0_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_P0_TYPE_C_PORT
#elif((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P1_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_P1_TYPE_C_PORT
#elif((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P2_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_P2_TYPE_C_PORT
#elif((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P3_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_P3_TYPE_C_PORT
#elif((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P4_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_P4_TYPE_C_PORT
#elif((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _HW_TCPM_0_1_MAPPING                        _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _HW_TCPM_0_1_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D0_TYPE_C_PORT))
#else
#define _HW_TCPM_0_1_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_TCPM_0_1_SUPPORT == _ON)

//--------------------------------------------------
// TCPM 1 TCPC 0 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_TCPM_1_0_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D0_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_D0_TYPE_C_PORT
#elif((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D1_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D1_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_D1_TYPE_C_PORT
#elif((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D2_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D2_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_D2_TYPE_C_PORT
#elif((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P0_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P0_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_P0_TYPE_C_PORT
#elif((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P1_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P1_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_P1_TYPE_C_PORT
#elif((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P2_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P2_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_P2_TYPE_C_PORT
#elif((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P3_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P3_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_P3_TYPE_C_PORT
#elif((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P4_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P4_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_P4_TYPE_C_PORT
#elif((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _HW_TCPM_1_0_MAPPING                        _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _HW_TCPM_1_0_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D0_TYPE_C_PORT))
#else
#define _HW_TCPM_1_0_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_TCPM_1_0_SUPPORT == _ON)

//--------------------------------------------------
// TCPM 1 TCPC 1 Mapping to PCB Port
//--------------------------------------------------
#if(_HW_TCPM_1_1_SUPPORT == _ON)
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_D0_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_D0_TYPE_C_PORT
#elif((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D1_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D1_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_D1_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_D1_TYPE_C_PORT
#elif((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D2_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D2_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_D2_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_D2_TYPE_C_PORT
#elif((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P0_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P0_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_P0_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_P0_TYPE_C_PORT
#elif((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P1_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P1_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_P1_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_P1_TYPE_C_PORT
#elif((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P2_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P2_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_P2_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_P2_TYPE_C_PORT
#elif((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P3_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P3_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_P3_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_P3_TYPE_C_PORT
#elif((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_P4_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_P4_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_P4_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_P4_TYPE_C_PORT
#elif((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#define _HW_TCPM_1_1_MAPPING                        _VALUE_ADAPTOR_TYPE_C_PORT
#else
#define _HW_TCPM_1_1_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) && (_HW_TCPM_0_0_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_HW_TCPM_0_1_MAPPING != _VALUE_D0_TYPE_C_PORT) && (_HW_TCPM_1_0_MAPPING != _VALUE_D0_TYPE_C_PORT))
#else
#define _HW_TCPM_1_1_MAPPING                        _VALUE_NO_TYPE_C_PORT
#endif  // End of #if(_HW_TCPM_1_1_SUPPORT == _ON)

//--------------------------------------------------
// TCPM HW Support Definition
//--------------------------------------------------
#define _HW_TCPM_0_SUPPORT                          ((_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
#define _HW_TCPM_1_SUPPORT                          ((_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
#define _HW_TCPM_SUPPORT                            ((_HW_TCPM_0_SUPPORT == _ON) || (_HW_TCPM_1_SUPPORT == _ON))

//--------------------------------------------------
// TypeC Alt Mode Support Option
//--------------------------------------------------
#define _D0_TYPE_C_MODAL_OPERATION_SUPPORT          ((_D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _D1_TYPE_C_MODAL_OPERATION_SUPPORT          ((_D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _D2_TYPE_C_MODAL_OPERATION_SUPPORT          ((_D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _P0_TYPE_C_MODAL_OPERATION_SUPPORT          ((_P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _P1_TYPE_C_MODAL_OPERATION_SUPPORT          ((_P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _P2_TYPE_C_MODAL_OPERATION_SUPPORT          ((_P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _P3_TYPE_C_MODAL_OPERATION_SUPPORT          ((_P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _P4_TYPE_C_MODAL_OPERATION_SUPPORT          ((_P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _ADAPTOR_TYPE_C_MODAL_OPERATION_SUPPORT     ((_ADAPTOR_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

#define _TYPE_C_MODAL_OPERATION_SUPPORT             ((_D0_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_MODAL_OPERATION_SUPPORT == _ON))

//--------------------------------------------------
// Usb Retimer/Redriver UFP PHY Support Definition
//--------------------------------------------------
#define _USB3_UFP_PHY0_SUPPORT                      (((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                      ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                      ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)))

#define _USB3_UFP_PHY1_SUPPORT                      (((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                      ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                      ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)))

#define _USB3_UFP_PHY2_SUPPORT                      (((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                      ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                      ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)))

#define _USB3_RETIMER_UFP_PHY0_SUPPORT              ((((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))) &&\
                                                       (((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_RETIMER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_RETIMER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_RETIMER))))

#define _USB3_RETIMER_UFP_PHY1_SUPPORT              ((((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))) &&\
                                                       (((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_RETIMER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_RETIMER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_RETIMER))))

#define _USB3_RETIMER_UFP_PHY2_SUPPORT              ((((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))) &&\
                                                       (((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_RETIMER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_RETIMER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_RETIMER))))

#define _USB3_RETIMER_UFP_PHY_SUPPORT               ((_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON) ||\
                                                        (_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON) ||\
                                                        (_USB3_RETIMER_UFP_PHY2_SUPPORT == _ON))

#define _USB3_REDRIVER_UFP_PHY0_SUPPORT             ((((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))) &&\
                                                       (((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_REDRIVER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_REDRIVER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_REDRIVER))))

#define _USB3_REDRIVER_UFP_PHY1_SUPPORT             ((((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))) &&\
                                                       (((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_REDRIVER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_REDRIVER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_REDRIVER))))

#define _USB3_REDRIVER_UFP_PHY2_SUPPORT             ((((_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER)) ||\
                                                        ((_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))) &&\
                                                       (((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_REDRIVER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_REDRIVER)) ||\
                                                        ((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_REDRIVER))))

#define _USB3_REDRIVER_UFP_PHY_SUPPORT              ((_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON) ||\
                                                        (_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON) ||\
                                                        (_USB3_REDRIVER_UFP_PHY2_SUPPORT == _ON))

//--------------------------------------------------
// Usb Retimer/Redriver DFP PHY Support Definition (To Be Modified) => _HW_MACx_USB3_REPEATER_DFP_PHY_MAPPING_TO == _USB3_REPEATER_DFP_PHY_x
//--------------------------------------------------
#define _USB3_RETIMER_DFP_PHY0_SUPPORT              (((_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0) && (_USB3_RETIMER_MAC0_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0) && (_USB3_RETIMER_MAC1_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0) && (_USB3_RETIMER_MAC2_SUPPORT == _ON)))

#define _USB3_RETIMER_DFP_PHY1_SUPPORT              (((_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1) && (_USB3_RETIMER_MAC0_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1) && (_USB3_RETIMER_MAC1_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1) && (_USB3_RETIMER_MAC2_SUPPORT == _ON)))

#define _USB3_RETIMER_DFP_PHY2_SUPPORT              (((_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2) && (_USB3_RETIMER_MAC0_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2) && (_USB3_RETIMER_MAC1_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2) && (_USB3_RETIMER_MAC2_SUPPORT == _ON)))

#define _USB3_RETIMER_DFP_PHY_SUPPORT               ((_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON) ||\
                                                       (_USB3_RETIMER_DFP_PHY1_SUPPORT == _ON) ||\
                                                       (_USB3_RETIMER_DFP_PHY2_SUPPORT == _ON))

#define _USB3_REDRIVER_DFP_PHY0_SUPPORT             (((_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0) && (_USB3_REDRIVER_MAC0_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0) && (_USB3_REDRIVER_MAC1_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0) && (_USB3_REDRIVER_MAC2_SUPPORT == _ON)))

#define _USB3_REDRIVER_DFP_PHY1_SUPPORT             (((_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1) && (_USB3_REDRIVER_MAC0_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1) && (_USB3_REDRIVER_MAC1_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1) && (_USB3_REDRIVER_MAC2_SUPPORT == _ON)))

#define _USB3_REDRIVER_DFP_PHY2_SUPPORT             (((_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2) && (_USB3_REDRIVER_MAC0_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2) && (_USB3_REDRIVER_MAC1_SUPPORT == _ON)) ||\
                                                       ((_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2) && (_USB3_REDRIVER_MAC2_SUPPORT == _ON)))

#define _USB3_REDRIVER_DFP_PHY_SUPPORT              ((_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON) ||\
                                                       (_USB3_REDRIVER_DFP_PHY1_SUPPORT == _ON) ||\
                                                       (_USB3_REDRIVER_DFP_PHY2_SUPPORT == _ON))

//--------------------------------------------------
// Usb Repeater PHY Support Definition
//--------------------------------------------------
#define _USB3_REDRIVER_PHY_SUPPORT                  ((_USB3_REDRIVER_UFP_PHY_SUPPORT == _ON) &&\
                                                     (_USB3_REDRIVER_DFP_PHY_SUPPORT == _ON))

#define _USB3_RETIMER_PHY_SUPPORT                   ((_USB3_RETIMER_UFP_PHY_SUPPORT == _ON) &&\
                                                     (_USB3_RETIMER_DFP_PHY_SUPPORT == _ON))

#define _USB3_REPEATER_PHY_SUPPORT                  (((_USB3_RETIMER_UFP_PHY_SUPPORT == _ON) &&\
                                                     (_USB3_RETIMER_DFP_PHY_SUPPORT == _ON)) ||\
                                                     (_USB3_REDRIVER_PHY_SUPPORT == _ON))

//--------------------------------------------------
// Usb Retimer/Redriver MAC Support Definition (To Be Modified) => _HW_UFP_PHYx_USB3_REPEATER_MAC_MAPPING_TO == _USB3_REPEATER_MAC_x
//--------------------------------------------------
#define _USB3_RETIMER_MAC0_SUPPORT                  ((((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_USB3_UFP_PHY0_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_USB3_UFP_PHY1_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_USB3_UFP_PHY0_SUPPORT == _ON))) &&\
                                                     (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_RETIMER))

#define _USB3_RETIMER_MAC1_SUPPORT                  ((((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_USB3_UFP_PHY0_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_USB3_UFP_PHY1_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_USB3_UFP_PHY0_SUPPORT == _ON))) &&\
                                                     (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_RETIMER))

#define _USB3_RETIMER_MAC2_SUPPORT                  ((((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_USB3_UFP_PHY0_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_USB3_UFP_PHY1_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_USB3_UFP_PHY0_SUPPORT == _ON))) &&\
                                                     (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_RETIMER))

#define _USB3_RETIMER_MAC_SUPPORT                   ((_USB3_RETIMER_MAC0_SUPPORT == _ON) ||\
                                                     (_USB3_RETIMER_MAC1_SUPPORT == _ON) ||\
                                                     (_USB3_RETIMER_MAC2_SUPPORT == _ON))

#define _USB3_REDRIVER_MAC0_SUPPORT                 ((((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_USB3_UFP_PHY0_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_USB3_UFP_PHY1_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_0) && (_USB3_UFP_PHY0_SUPPORT == _ON))) &&\
                                                     (_HW_MAC0_USB3_REPEATER_TYPE == _USB3_REDRIVER))

#define _USB3_REDRIVER_MAC1_SUPPORT                 ((((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_USB3_UFP_PHY0_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_USB3_UFP_PHY1_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_1) && (_USB3_UFP_PHY0_SUPPORT == _ON))) &&\
                                                     (_HW_MAC1_USB3_REPEATER_TYPE == _USB3_REDRIVER))

#define _USB3_REDRIVER_MAC2_SUPPORT                 ((((_HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_USB3_UFP_PHY0_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_USB3_UFP_PHY1_SUPPORT == _ON)) ||\
                                                      ((_HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING == _USB3_REPEATER_MAC_2) && (_USB3_UFP_PHY0_SUPPORT == _ON))) &&\
                                                     (_HW_MAC2_USB3_REPEATER_TYPE == _USB3_REDRIVER))

#define _USB3_REDRIVER_MAC_SUPPORT                  (((_USB3_REDRIVER_MAC0_SUPPORT == _ON) ||\
                                                      (_USB3_REDRIVER_MAC1_SUPPORT == _ON) ||\
                                                      (_USB3_REDRIVER_MAC2_SUPPORT == _ON)))

//--------------------------------------------------
// Usb Repeater MAC Support Definition
//--------------------------------------------------
#define _USB3_REPEATER_MAC_SUPPORT                  ((_USB3_RETIMER_MAC_SUPPORT == _ON) ||\
                                                     (_USB3_REDRIVER_MAC_SUPPORT == _ON))

#define _USB3_REPEATER_SUPPORT                      ((_USB3_REPEATER_PHY_SUPPORT == _ON) &&\
                                                     (_USB3_REPEATER_MAC_SUPPORT == _ON))

//--------------------------------------------------
// Usb Repeater MAC Power Saving Support Option
//--------------------------------------------------
#define _USB3_U3_P3_POWER_SAVING_SUPPORT            ((_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT == _ON) &&\
                                                     (_USB3_LOW_POWER_CONSUME_IN_POWER_SAVING == _ON))

//--------------------------------------------------
// U2Host Option
//--------------------------------------------------
#define _USB2_HOST_EHCI_SUPPORT                     ((_HW_USB2_HOST_SUPPORT == _ON) &&\
                                                     (_USB2_HOST_PORT_SUPPORT == _ON) &&\
                                                     ((_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON) ||\
                                                      (_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)))

#define _USB2_HOST_OHCI_SUPPORT                     ((_HW_USB2_HOST_SUPPORT == _ON) &&\
                                                     (_USB2_HOST_PORT_SUPPORT == _ON) &&\
                                                     ((_USB2_HOST_OHCI_MOUSE_SUPPORT == _ON) ||\
                                                      (_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)))

#define _USB2_HOST_SUPPORT                          ((_USB2_HOST_EHCI_SUPPORT == _ON) ||\
                                                     (_USB2_HOST_OHCI_SUPPORT == _ON))

//--------------------------------------------------
// U2Host FW Support Type
//--------------------------------------------------
#if(_USB2_HOST_SUPPORT == _ON)
#if((_SCPU_SUPPORT == _ON) && (_SCPU_RTOS == _ON))
#define _USB2_HOST_FW_SUPPORT_TYPE                  _FW_FREE_RTOS
#else
#define _USB2_HOST_FW_SUPPORT_TYPE                  _FW_MAIN_LOOP
#endif
#else
#define _USB2_HOST_FW_SUPPORT_TYPE                  _FW_NONE
#endif

//--------------------------------------------------
// USB Related Option
//--------------------------------------------------
#define _D0_USB_SUPPORT                             ((_D0_USB_HUB_SUPPORT == _ON) || (_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _D1_USB_SUPPORT                             ((_D1_USB_HUB_SUPPORT == _ON) || (_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _D2_USB_SUPPORT                             ((_D2_USB_HUB_SUPPORT == _ON) || (_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _P0_USB_SUPPORT                             ((_P0_USB_HUB_SUPPORT == _ON) || (_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _P1_USB_SUPPORT                             ((_P1_USB_HUB_SUPPORT == _ON) || (_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _P2_USB_SUPPORT                             ((_P2_USB_HUB_SUPPORT == _ON) || (_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _P3_USB_SUPPORT                             ((_P3_USB_HUB_SUPPORT == _ON) || (_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _P4_USB_SUPPORT                             ((_P4_USB_HUB_SUPPORT == _ON) || (_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON))
#define _ADAPTOR_USB_SUPPORT                        (_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#define _USB_SUPPORT                                ((_D0_USB_SUPPORT == _ON) ||\
                                                     (_D1_USB_SUPPORT == _ON) ||\
                                                     (_D2_USB_SUPPORT == _ON) ||\
                                                     (_P0_USB_SUPPORT == _ON) ||\
                                                     (_P1_USB_SUPPORT == _ON) ||\
                                                     (_P2_USB_SUPPORT == _ON) ||\
                                                     (_P3_USB_SUPPORT == _ON) ||\
                                                     (_P4_USB_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_USB_SUPPORT == _ON) ||\
                                                     (_USB2_HOST_SUPPORT == _ON))

#define _DOLBY_CERTIFICATION_SUPPORT                ((_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON) &&\
                                                     (_FRC_SUPPORT == _ON) &&\
                                                     (_M_DOMAIN_12BIT_SUPPORT == _ON))

//--------------------------------------------------
// Audio Option
//--------------------------------------------------
#if(_AUDIO_SUPPORT == _OFF)
#undef _AUDIO_COMPRESS_SUPPORT
#define _AUDIO_COMPRESS_SUPPORT                     _OFF
#endif

#define _AUDIO_PATH_VALID                           ((_AUDIO_SUPPORT == _ON) +\
                                                     (_AUDIO_ARC_SUPPORT == _ON))

//--------------------------------------------------
// DP Rx Audio Support Option
//--------------------------------------------------
#define _DP_AUDIO_RX0_SUPPORT                       ((_DP_MAC_RX0_SUPPORT == _ON) && ((_AUDIO_SUPPORT == _ON) || ((_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) && ((_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0) ||\
                                                                                                                                                            (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1) ||\
                                                                                                                                                            (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))

#define _DP_AUDIO_RX1_SUPPORT                       ((_DP_MAC_RX1_SUPPORT == _ON) && ((_AUDIO_SUPPORT == _ON) || ((_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) && ((_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX1) ||\
                                                                                                                                                            (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1) ||\
                                                                                                                                                            (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))

#define _DP_AUDIO_RX2_SUPPORT                       ((_DP_MAC_RX2_SUPPORT == _ON) && ((_AUDIO_SUPPORT == _ON) || ((_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) && ((_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX2) ||\
                                                                                                                                                            (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX0_OR_RX1_OR_RX2)))))

#define _DP_AUDIO_RX3_SUPPORT                       ((_DP_MAC_RX3_SUPPORT == _ON) && ((_AUDIO_SUPPORT == _ON) || ((_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX3))))

#define _DP_AUDIO_RX4_SUPPORT                       ((_DP_MAC_RX4_SUPPORT == _ON) && ((_AUDIO_SUPPORT == _ON) || ((_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) && (_HW_MST2SST_DP_MAC_STREAM_RX_MAPPING == _MAPPING_RX4))))

//--------------------------------------------------
// HDMI Rx Audio Support Option
//--------------------------------------------------
#define _HDMI_AUDIO_RX3_SUPPORT                     ((_HDMI_MAC_RX3_SUPPORT == _ON) & (_AUDIO_SUPPORT == _ON))

#define _HDMI_AUDIO_RX4_SUPPORT                     ((_HDMI_MAC_RX4_SUPPORT == _ON) & (_AUDIO_SUPPORT == _ON))

//--------------------------------------------------
// DP Rx Audio Support Option
//--------------------------------------------------
#define _DP_RX_AUDIO_SUPPORT                        ((_DP_AUDIO_RX0_SUPPORT == _ON) ||\
                                                     (_DP_AUDIO_RX1_SUPPORT == _ON) ||\
                                                     (_DP_AUDIO_RX2_SUPPORT == _ON) ||\
                                                     (_DP_AUDIO_RX3_SUPPORT == _ON) ||\
                                                     (_DP_AUDIO_RX4_SUPPORT == _ON))

//--------------------------------------------------
// DP Tx Audio Support Option
//--------------------------------------------------
#define _DP_TX_AUDIO_SUPPORT                        ((_DP_MAC_TX_SUPPORT == _ON) && ((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)))

//--------------------------------------------------
// Record Timer Option
//--------------------------------------------------
#define _RECORD_TIMER_SUPPORT                       _OFF

//--------------------------------------------------
// Timer Event ID Enumeration & Structure
//--------------------------------------------------
#include _USER_TIMER_INCLUDE

typedef enum
{
    _SCALER_TIMER_EVENT_INVALID = 0x00,

#include _USER_TIMER_EVENT_ID_INCLUDE
    _USER_TIMER_EVENT_END,

#include <TimerEventIDSystem.h>
    _SYSTEM_TIMER_EVENT_END,

#include <TimerEventIDScaler.h>
    _SCALER_TIMER_EVENT_END,
} EnumScalerTimerEventID;


typedef struct
{
    EnumScalerTimerEventID enumEventID;
    WORD usTime;
} StructTimerEventTableType;

//--------------------------------------------------
// HW IIC Speed Parameters Enumeration & Structure
//--------------------------------------------------
#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
#include _USER_HWIIC_INCLUDE
#endif

typedef enum
{
    _KERNAL_PAR_100K = 0x00,
    _KERNAL_PAR_400K,

#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
// Incldue User Paramters Type
#include _USER_HW_IIC_PAR_TYPE
#endif
}EnumHWIICParType;

//--------------------------------------------------
// Flash Item Enumeration
//--------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
#include _USER_FLASH_INCLUDE

typedef enum
{
    _FLASH_ITEMID_VGA_ADC_DATA,
    _FLASH_ITEMID_YPBPR_ADC_DATA,

    // 3 items slots for system data
    _FLASH_ITEMID_SYSTEM_DATA,
    _FLASH_ITEMID_SYSTEM_DATA_END = _FLASH_ITEMID_SYSTEM_DATA + 2,

#include _USER_FLASH_ITEM_ID_INCLUDE
} EnumFlashItemIDType;
#endif

//--------------------------------------------------
// VCCK off setting
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6829_SERIES) ||\
    (_SCALER_TYPE == _RL6952_SERIES) ||\
    (_SCALER_TYPE == _RL6978_SERIES))
#define _POLLING_VCCK_ADDR                          (P39_00_DISP_TYPE)
#define _POLLING_VCCK_VALUE                         (0x01)
#endif


//****************************************************************************
// HW IIC Speed Parameters Structure
//****************************************************************************
typedef struct
{
    BYTE ucSLPC;
    BYTE ucSHPC;
    BYTE ucSTA_SUGPIO_C;
    BYTE ucTOR;
    BYTE ucFTPC;
    BYTE ucFD10;
#if((_HW_HW_IIC_GEN == _HW_IIC_GEN_2) || (_TYPEC_IIC_SUPPORT == _ON))
    BYTE ucTHD_STA_C;
#endif // End of #if((_HW_HW_IIC_GEN == _HW_IIC_GEN_2) || (_TYPEC_IIC_SUPPORT == _ON))
} StructHwI2cSettingDataItem;

typedef struct
{
    StructHwI2cSettingDataItem stXtal;
    StructHwI2cSettingDataItem stIosc;
} StructHwI2cSettingData;

//--------------------------------------------------
// Timer Event Count
//--------------------------------------------------
#if((_HP_SOURCE_SCAN_SUPPORT == _ON) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE) ||\
    (_DUAL_DP_SUPPORT == _ON))
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT            5
#else
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT            4
#endif

#if(_DP_SUPPORT == _ON)
#define _SCALER_DP_EVENT_COUNT                      9
#define _BACKGROUND_FW_UPDATE_DPRX_EVENT_COUNT      1
#else
#define _SCALER_DP_EVENT_COUNT                      0
#define _BACKGROUND_FW_UPDATE_DPRX_EVENT_COUNT      0
#endif

#if(_DP_MST_SUPPORT == _ON)
#define _SCALER_DP_MST_EVENT_COUNT                  (4 + _DP_PORT_VALID)
#else
#define _SCALER_DP_MST_EVENT_COUNT                  0
#endif

#if(_DP_TX_SUPPORT == _ON)
#define _SCALER_DP_TX_EVENT_COUNT                   3
#define _BACKGROUND_FW_UPDATE_DPTX_EVENT_COUNT      1
#else
#define _SCALER_DP_TX_EVENT_COUNT                   0
#define _BACKGROUND_FW_UPDATE_DPTX_EVENT_COUNT      0
#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define _BACKGROUND_FW_UPDATE_TYPEC_EVENT_COUNT     1
#else
#define _BACKGROUND_FW_UPDATE_TYPEC_EVENT_COUNT     0
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#define _BACKGROUND_FW_UPDATE_MCCS_EVENT_COUNT      1
#else
#define _BACKGROUND_FW_UPDATE_MCCS_EVENT_COUNT      0
#endif

#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)
#define _BACKGROUND_FW_UPDATE_HDCP_EVENT_COUNT      1
#define _SCALER_BACKGROUND_FW_UPDATE_EVENT_COUNT    (_BACKGROUND_FW_UPDATE_HDCP_EVENT_COUNT + _BACKGROUND_FW_UPDATE_TYPEC_EVENT_COUNT +\
                                                     _BACKGROUND_FW_UPDATE_DPRX_EVENT_COUNT + _BACKGROUND_FW_UPDATE_DPTX_EVENT_COUNT +\
                                                     _BACKGROUND_FW_UPDATE_MCCS_EVENT_COUNT)
#else
#define _SCALER_BACKGROUND_FW_UPDATE_EVENT_COUNT    0
#endif

#define _SIMULTANEOUS_SCALER_EVENT_COUNT            (_SCALER_DP_EVENT_COUNT +\
                                                     _SCALER_DP_MST_EVENT_COUNT +\
                                                     _SCALER_DP_TX_EVENT_COUNT +\
                                                     _SCALER_BACKGROUND_FW_UPDATE_EVENT_COUNT)

#define _TIMER_EVENT_COUNT                          (_SIMULTANEOUS_USER_EVENT_COUNT +\
                                                     _SIMULTANEOUS_SYSTEM_EVENT_COUNT +\
                                                     _SIMULTANEOUS_SCALER_EVENT_COUNT)

//--------------------------------------------------
// M2PLL is 243M
// Enumerations of Flash / MCU Speed
// Power Normal:        Flash = 40.5M,  MCU = 81M
// Power Normal Flash Low Speed:
//                      Flash = 20.25M, MCU = 40.5M
//
// M2PLL is 351M
// Enumerations of Flash / MCU Speed
// Power Normal:        Flash = 44M,    MCU = 88M
// Power Normal Flash Low Speed:
//                      Flash = 22M,    MCU = 44M
//
// Power Sav/Down 27:   Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving DP:     Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving Precision: Flash = 14.318M,  MCU = 14.318M
// Power Initial:       Flash = 14.3M,  MCU = 14.3M
//--------------------------------------------------
typedef enum
{
#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_3,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_6,
    _FLASH_CLK_FAST_DIV = _DIV_3,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else

#if(_CACHE_PS_SWITCH == _ENABLE)
    _FLASH_CLK_PS_DIV = _DIV_1,
#elif(_CACHE_PS_SWITCH == _DISABLE)
    _FLASH_CLK_PS_DIV = _DIV_4,
#endif

#endif

#elif(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M) // Else Of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_2,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
    _FLASH_CLK_FAST_DIV = _DIV_2,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#endif // End of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

    _FLASH_CLK_IN_DIV = _DIV_1,
    _FLASH_CLK_PS_FAST_DIV = _DIV_1, // for DP
} EnumFlashClkDiv;

typedef enum
{
    _FLASH_2_CLK_IN_DIV = _DIV_1,

    _FLASH_2_CLK_DIV = _DIV_4,

#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_CACHE_PS_SWITCH == _ENABLE)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#elif(_CACHE_PS_SWITCH == _DISABLE)
    _FLASH_2_CLK_PS_DIV = _DIV_1,
#endif

#elif(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#endif

} EnumFlash2ClkDiv;

typedef enum
{
    _MCU_CLK_DIV = _DIV_1,
#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _MCU_CLK_PS_DIV = _DIV_1,
#endif

    _MCU_CLK_IN_DIV = _DIV_1,
} EnumMcuClkDiv;

//--------------------------------------------------
// Timer 0/1 Max Delay Timer(MS)
//--------------------------------------------------
#define _TIMER01_STEP_TIME_MS                       4


//--------------------------------------------------
// Urgent Event Check Mode
//--------------------------------------------------
#define _URGENT_EVENT_CHECK_MODE                    ((_DP_SUPPORT == _ON) ||\
                                                     (_HDCP_2_2_SUPPORT == _ON))

//--------------------------------------------------
// DP MST Multi-function Define
//--------------------------------------------------
#define _DP_MST_MULTI_FUNCTION_SUPPORT              ((_DP_MST_SUPPORT == _ON) &&\
                                                     ((_DP_HBLANKING_MODIFY_SUPPORT == _ON) ||\
                                                      (_DP_FREESYNC_SUPPORT == _ON) ||\
                                                      (_DP_ADAPTIVESYNC_SUPPORT == _ON) ||\
                                                      (_DP_RX_DSC_DECODER_SUPPORT == _ON) ||\
                                                      (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) ||\
                                                      (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)))

//--------------------------------------------------
// Enum for Rx mapping
//--------------------------------------------------
typedef enum
{
    _RX0 = _MAPPING_RX0,
    _RX1 = _MAPPING_RX1,
    _RX2 = _MAPPING_RX2,
    _RX3 = _MAPPING_RX3,
    _RX4 = _MAPPING_RX4,
    _RX5 = _MAPPING_RX5,
    _RX7 = _MAPPING_RX7,
    _RX8 = _MAPPING_RX8,
    _RX0_OR_RX1 = _MAPPING_RX0_OR_RX1,
    _RX_MAP_NONE = _MAPPING_RX_MAP_NONE,
} EnumRx;

//--------------------------------------------------
// Enum for Rx mapping
//--------------------------------------------------
typedef enum
{
    _UFP_NONE = 0,
    _UFP_PHY0 = 1,
    _UFP_PHY1 = 2,
} EnumUsbUfpPhy;

//--------------------------------------------------
// I-Dither Option
//--------------------------------------------------
#define _HW_IDITHER_TABLE_SET_NUM                   (((_HW_IDITHER_M2_PATH_SUPPORT == _OFF) && (_HW_IDITHER_S1_PATH_SUPPORT == _OFF)) ? 1 : 2)

//--------------------------------------------------
// DP HPD Implementation Mode
//--------------------------------------------------
#if(_DP_LONG_HPD_USER_MODE == _DP_LONG_HPD_DEFAULT_MODE)
#if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_DP_MST_SUPPORT == _ON))
#define _DP_LONG_HPD_MODE                           _DP_LONG_HPD_TIMEREVENT_MODE
#else
#define _DP_LONG_HPD_MODE                           _DP_LONG_HPD_DELAY_MODE
#endif
#else
#define _DP_LONG_HPD_MODE                           _DP_LONG_HPD_USER_MODE
#endif

//--------------------------------------------------
// DP Aux Auto Calibration Support
//--------------------------------------------------
#if(_HW_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
#define _DP_AUX_AUTO_CALIBRATION_SUPPORT            _ON
#else
#define _DP_AUX_AUTO_CALIBRATION_SUPPORT            _OFF
#endif

//--------------------------------------------------
// DP AUX WILDCARD SUPPORT
//--------------------------------------------------
/*
Example
#if(_DP_XXX_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_WILDCARD_XXX_SUPPORT        _ON
#else
#define _DP_AUX_RX_DPCD_WILDCARD_XXX_SUPPORT        _OFF
#endif

#define _DP_AUX_RX_DPCD_WILDCARD_USED_COUNT         ((_DP_AUX_RX_DPCD_WILDCARD_XXX_SUPPORT == _ON) +......)
*/
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_WILDCARD_00210_SUPPORT      _ON

#if(_DP_RX_FEC_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_WILDCARD_00281_SUPPORT      _ON
#else
#define _DP_AUX_RX_DPCD_WILDCARD_00281_SUPPORT      _OFF
#endif

#if(_DP_MST_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT      _ON
#else
#define _DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT      _OFF
#endif

#define _DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT      _OFF
#define _DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT      _OFF
#else
#if(_DP_RX_FEC_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT      _ON
#else
#define _DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT      _OFF
#endif

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
#define _DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT      _ON
#else
#define _DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT      _OFF
#endif

#if(_DP_MST_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT      _ON
#else
#define _DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT      _OFF
#endif

#define _DP_AUX_RX_DPCD_WILDCARD_00281_SUPPORT      _OFF
#define _DP_AUX_RX_DPCD_WILDCARD_00210_SUPPORT      _OFF
#endif

#define _DP_AUX_RX_DPCD_WILDCARD_USED_COUNT         (_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT + _DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT +\
                                                     _DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT + _DP_AUX_RX_DPCD_WILDCARD_00210_SUPPORT +\
                                                     _DP_AUX_RX_DPCD_WILDCARD_00281_SUPPORT)

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// DP AUX REMAP SUPPORT
//--------------------------------------------------
/*
Example
#if(_DP_XXX_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_REMAP_XXX_SUPPORT           _ON
#else
#define _DP_AUX_RX_DPCD_REMAP_XXX_SUPPORT           _OFF
#endif

#define _DP_AUX_RX_DPCD_REMAP_USED_COUNT            ((_DP_AUX_RX_DPCD_REMAP_32B_XXX_SUPPORT == _ON) +......)
*/

#define _DP_AUX_RX_DPCD_REMAP_USED_COUNT            (0)

#define _DP_AUX_RX_DPCD_REMAP_32B_USED_COUNT        (0)
#define _DP_AUX_RX_DPCD_REMAP_16B_USED_COUNT        (0)
#define _DP_AUX_RX_DPCD_REMAP_8B_USED_COUNT         (0)
#else
//--------------------------------------------------
// DP AUX REMAP 32B SUPPORT
//--------------------------------------------------
/*
Example
#if(_DP_XXX_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_REMAP_32B_XXX_SUPPORT       _ON
#else
#define _DP_AUX_RX_DPCD_REMAP_32B_XXX_SUPPORT       _OFF
#endif

#define _DP_AUX_RX_DPCD_REMAP_32B_USED_COUNT        ((_DP_AUX_RX_DPCD_REMAP_32B_XXX_SUPPORT == _ON) +......)
*/

#define _DP_AUX_RX_DPCD_REMAP_32B_USED_COUNT        (0)

//--------------------------------------------------
// DP AUX REMAP 16B SUPPORT
//--------------------------------------------------
/*
Example
#if(_DP_XXX_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_REMAP_16B_XXX_SUPPORT       _ON
#else
#define _DP_AUX_RX_DPCD_REMAP_16B_XXX_SUPPORT       _OFF
#endif

#define _DP_AUX_RX_DPCD_REMAP_16B_USED_COUNT        ((_DP_AUX_RX_DPCD_REMAP_16B_XXX_SUPPORT == _ON) +......)
*/

#define _DP_AUX_RX_DPCD_REMAP_16B_USED_COUNT        (0)

//--------------------------------------------------
// DP AUX REMAP 8B SUPPORT
//--------------------------------------------------
/*
Example
#if(_DP_XXX_SUPPORT == _ON)
#define _DP_AUX_RX_DPCD_REMAP_8B_XXX_SUPPORT        _ON
#else
#define _DP_AUX_RX_DPCD_REMAP_8B_XXX_SUPPORT        _OFF
#endif

#define _DP_AUX_RX_DPCD_REMAP_8B_USED_COUNT         ((_DP_AUX_RX_DPCD_REMAP_8B_XXX_SUPPORT == _ON) +......)
*/

#define _DP_AUX_RX_DPCD_REMAP_8B_USED_COUNT         (0)

#define _DP_AUX_RX_DPCD_REMAP_USED_COUNT            (0)
#endif

#endif // End of #ifndef __SCALER_OPTION_H__
