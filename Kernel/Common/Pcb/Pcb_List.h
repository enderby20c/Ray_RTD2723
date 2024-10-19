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
// ID Code      : Pcb_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_LIST_H__
#define __PCB_LIST_H__

//--------------------------------------------------
// Pcb List
//--------------------------------------------------
#define _RL6829_PCB_EXAMPLE                                     0x40
#define _RL6829_QA_A_BGA_1024_LVDS_2H1TC1DP_TCMST_LVDS          0x41
#define _RL6829_QA_A_BGA_1024_LVDS_LD_1152                      0x42
#define _RL6829_QA_A_BGA_LOCAL_DIMMING_2X8                      0x43
#define _RL6829_QA_B_BGA_1024_LVDS_4TC2H_TCMST_LVDS             0x44  // For QC using
#define _RL6829_DEMO_A_BGA_1024_LVDS_2H2TC1DP_DPTX_LVDS         0x45
#define _RL6829_DEMO_B_BGA_1024_LVDS_2H3TC_TCMST_LVDS           0x46
#define _RL6829_DEMO_C_BGA_1024_eDP_2H2TC1DP_9G_2CHIP_FRONT     0x47
#define _RL6829_DEMO_D_BGA_1024_LVDS_2H2TC1mDP_mDPMST_DPTX_LVDS 0x48

#define _RL6952_BGA4L_PCB_LVDS_EXAMPLE                          0x50
#define _RL6952_BGA2L_PCB_LVDS_EXAMPLE                          0x51
#define _RL6952_QA_A_BGA4L_LVDS_2H2TC1DP_TCMST_LVDS             0x52
#define _RL6952_DEMO_A_BGA4L_LVDS_2H2TC1mDP_TCMST_LVDS          0x53
#define _RL6952_QA_A_BGA2L_LVDS_2H1TC1DP_TCMST_LVDS             0x54
#define _RL6952_DEMO_A_BGA2L_LVDS_2H1TC1mDP_TCMST_LVDS          0x55
#define _RL6952_DEMO_A_V03_BGA4L_LVDS_2H2TC1mDP_TCMST_LVDS      0x56

#define _RL6978_PCB_LQFP_216_4D_USB_DDRx2_eDP_EXAMPLE           0x60
#define _RL6978_QA_A_LQFP_216_1TC2H1DP_USB_DDRx2_eDP            0x61
#define _RL6978_DEMO_A_LQFP_216_1TC2H1DP_USB_DDRx2_eDP          0x62
#define _RL6978_PCB_LQFP_216_3D_USB_DDRx1_LVDS_EXAMPLE          0x63
#define _RL6978_QA_A_LQFP_216_1TC1H1DP_USB_DDRx1_LVDS           0x64
#define _RL6978_DEMO_A_LQFP_216_1TC1H1DP_USB_DDRx1_LVDS         0x65
#define _RL6978_PCB_LQFP_156_2D_DDRx1_LVDS_EXAMPLE              0x66
#define _RL6978_QA_A_LQFP_156_2DP_DDRx1_LVDS                    0x67
#define _RL6978_DEMO_A_LQFP_156_1H1DP_DDRx1_LVDS                0x68

//----------------------------------------------------------------------------------------------------
// Input Port Setting List
//----------------------------------------------------------------------------------------------------
#define _INPUT_VGA                                              0
#define _INPUT_HDMI                                             1
#define _INPUT_DP                                               2
#define _INPUT_NO_PORT                                          3

//--------------------------------------------------
// A0 Port Input Type List
//--------------------------------------------------
#define _A0_NO_PORT                                             ((_VALUE_A0_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _A0_VGA_PORT                                            ((_VALUE_A0_INPUT_PORT << 4) | _VALUE_PORT_VGA)

//--------------------------------------------------
// VGA Connector Type List
//--------------------------------------------------
#define _VGA_CONNECTOR_NORMAL                                   0
#define _VGA_CONNECTOR_YPBPR                                    1

//--------------------------------------------------
// D0 Port Input Type List
//--------------------------------------------------
#define _D0_NO_PORT                                             ((_VALUE_D0_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D0_HDMI_PORT                                           ((_VALUE_D0_INPUT_PORT << 4) | _VALUE_PORT_HDMI)
#define _D0_DP_PORT                                             ((_VALUE_D0_INPUT_PORT << 4) | _VALUE_PORT_DP)
#define _D0_USB_PORT                                            ((_VALUE_D0_INPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// D1 Port Input Type List
//--------------------------------------------------
#define _D1_NO_PORT                                             ((_VALUE_D1_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D1_HDMI_PORT                                           ((_VALUE_D1_INPUT_PORT << 4) | _VALUE_PORT_HDMI)
#define _D1_DP_PORT                                             ((_VALUE_D1_INPUT_PORT << 4) | _VALUE_PORT_DP)
#define _D1_USB_PORT                                            ((_VALUE_D1_INPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// D2 Port Input Type List
//--------------------------------------------------
#define _D2_NO_PORT                                             ((_VALUE_D2_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D2_HDMI_PORT                                           ((_VALUE_D2_INPUT_PORT << 4) | _VALUE_PORT_HDMI)
#define _D2_DP_PORT                                             ((_VALUE_D2_INPUT_PORT << 4) | _VALUE_PORT_DP)
#define _D2_USB_PORT                                            ((_VALUE_D2_INPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// D3 Port Input Type List
//--------------------------------------------------
#define _D3_NO_PORT                                             ((_VALUE_D3_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D3_HDMI_PORT                                           ((_VALUE_D3_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//--------------------------------------------------
// D4 Port Input Type List
//--------------------------------------------------
#define _D4_NO_PORT                                             ((_VALUE_D4_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D4_HDMI_PORT                                           ((_VALUE_D4_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//--------------------------------------------------
// D5 Port Input Type List
//--------------------------------------------------
#define _D5_NO_PORT                                             ((_VALUE_D5_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D5_HDMI_PORT                                           ((_VALUE_D5_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//--------------------------------------------------
// D6 Port Input Type List
//--------------------------------------------------
#define _D6_NO_PORT                                             ((_VALUE_D6_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D6_DP_PORT                                             ((_VALUE_D6_INPUT_PORT << 4) | _VALUE_PORT_DP)

//--------------------------------------------------
// D7 Port Input Type List
//--------------------------------------------------
#define _D7_NO_PORT                                             ((_VALUE_D7_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D7_DP_PORT                                             ((_VALUE_D7_INPUT_PORT << 4) | _VALUE_PORT_DP)

//--------------------------------------------------
// D8 Port Input Type List
//--------------------------------------------------
#define _D8_NO_PORT                                             ((_VALUE_D8_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D8_DP_PORT                                             ((_VALUE_D8_INPUT_PORT << 4) | _VALUE_PORT_DP)

//--------------------------------------------------
// D9 Port Input Type List
//--------------------------------------------------
#define _D9_NO_PORT                                             ((_VALUE_D9_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D9_DP_PORT                                             ((_VALUE_D9_INPUT_PORT << 4) | _VALUE_PORT_DP)

//--------------------------------------------------
// D12 Port Input Type List
//--------------------------------------------------
#define _D12_NO_PORT                                            ((_VALUE_D12_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D12_HDMI_PORT                                          ((_VALUE_D12_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//--------------------------------------------------
// D13 Port Input Type List
//--------------------------------------------------
#define _D13_NO_PORT                                            ((_VALUE_D13_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D13_HDMI_PORT                                          ((_VALUE_D13_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//--------------------------------------------------
// D14 Port Input Type List
//--------------------------------------------------
#define _D14_NO_PORT                                            ((_VALUE_D14_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D14_HDMI_PORT                                          ((_VALUE_D14_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//--------------------------------------------------
// D15 Port Input Type List
//--------------------------------------------------
#define _D15_NO_PORT                                            ((_VALUE_D15_INPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _D15_HDMI_PORT                                          ((_VALUE_D15_INPUT_PORT << 4) | _VALUE_PORT_HDMI)

//----------------------------------------------------------------------------------------------------
// Onput Port Setting List
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// P0 Output Type List
//--------------------------------------------------
#define _P0_NO_PORT                                             ((_VALUE_P0_OUTPUT_PORT << 4) | _VALUE_PORT_NONE)
#define _P0_DP_PORT                                             ((_VALUE_P0_OUTPUT_PORT << 4) | _VALUE_PORT_DP)

//--------------------------------------------------
// P1 Output Type List
//--------------------------------------------------
#define _P1_NO_PORT                                             ((_VALUE_P1_OUTPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// P2 Output Type List
//--------------------------------------------------
#define _P2_NO_PORT                                             ((_VALUE_P2_OUTPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// P3 Output Type List
//--------------------------------------------------
#define _P3_NO_PORT                                             ((_VALUE_P3_OUTPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// P4 Output Type List
//--------------------------------------------------
#define _P4_NO_PORT                                             ((_VALUE_P4_OUTPUT_PORT << 4) | _VALUE_PORT_NONE)

//--------------------------------------------------
// DP Connector Type List
//--------------------------------------------------
#define _DP_CONNECTOR_NORMAL                                    0
#define _DP_CONNECTOR_MINI                                      1
#define _DP_CONNECTOR_TYPE_C                                    2
#define _DP_CONNECTOR_TBT                                       3
#define _DP_CONNECTOR_EMBEDDED                                  4

//--------------------------------------------------
// USB Connector Type List
//--------------------------------------------------
#define _USB_CONNECTOR_NONE                                     0
#define _USB_CONNECTOR_TYPE_B                                   1
#define _USB_CONNECTOR_TYPE_C                                   2

//--------------------------------------------------
//  PHY Z0 Impedance Option
//--------------------------------------------------
#define _BY_CONNECTOR                                           0
#define _85_OHM                                                 1
#define _90_OHM                                                 2
#define _100_OHM                                                3

//--------------------------------------------------
// Adaptor Connector Type List
//--------------------------------------------------
#define _ADAPTOR_CONNECTOR_NORMAL                               0
#define _ADAPTOR_CONNECTOR_TYPE_C                               1

//--------------------------------------------------
// DP/Type-C Port External Re-Driver Type List
//--------------------------------------------------
#define _REDRIVER_NONE                                          0
#define _REDRIVER_PERICOM                                       1
#define _REDRIVER_PARADE                                        2

//--------------------------------------------------
// DP Repeater Type List
//--------------------------------------------------
#define _DP_REPEATER_NONE                                       0
#define _DP_REPEATER_RTS_TRANSLATOR                             1

//--------------------------------------------------
// Usb Hub Type List
//--------------------------------------------------
#define _USB_NONE                                               0
#define _USB_HUB_RTS                                            1
#define _USB_HUB_USER                                           2

//--------------------------------------------------
// Usb Hub Trace Type List
//--------------------------------------------------
#define _USB_U3_TRACE_GO_THROUGH_SCALER                         0
#define _USB_U3_TRACE_DIRECT_TO_HUB                             1

#define _USB_U2_TRACE_GO_THROUGH_SCALER                         0
#define _USB_U2_TRACE_DIRECT_TO_HUB                             1

//--------------------------------------------------
//  USB Speed
//--------------------------------------------------
#define _USB_2                                                  0x00
#define _USB_3_GEN1                                             0x01
#define _USB_3_GEN2                                             0x02
#define _USB_BILLBOARD_ONLY                                     0x03

//--------------------------------------------------
//  USB Lane
//--------------------------------------------------
#define _USB_3_LANE_NONE                                        0x00
#define _USB_3_LANE_X1                                          0x01
#define _USB_3_LANE_X2                                          0x02

//--------------------------------------------------
//  USB 2 Host Port Swing Level
//--------------------------------------------------
#define _USB2_HOST_HS_SWING_LEVEL_0                             0x07
#define _USB2_HOST_HS_SWING_LEVEL_1                             0x0A
#define _USB2_HOST_HS_SWING_LEVEL_2                             0x0D
#define _USB2_HOST_HS_SWING_LEVEL_3                             0x10
#define _USB2_HOST_HS_SWING_LEVEL_4                             0x13
#define _USB2_HOST_HS_SWING_LEVEL_5                             0x16
#define _USB2_HOST_HS_SWING_LEVEL_6                             0x19

//--------------------------------------------------
//  USB UFP OOBS Threshold Voltage
//--------------------------------------------------
#define _USB_UFP_RX_OOBS_VTH_LEVEL_0                            0x00
#define _USB_UFP_RX_OOBS_VTH_LEVEL_1                            0x01
#define _USB_UFP_RX_OOBS_VTH_LEVEL_2                            0x02
#define _USB_UFP_RX_OOBS_VTH_LEVEL_3                            0x03
#define _USB_UFP_RX_OOBS_VTH_LEVEL_4                            0x04
#define _USB_UFP_RX_OOBS_VTH_LEVEL_5                            0x05
#define _USB_UFP_RX_OOBS_VTH_LEVEL_6                            0x06
#define _USB_UFP_RX_OOBS_VTH_LEVEL_7                            0x07
#define _USB_UFP_RX_OOBS_VTH_LEVEL_8                            0x08
#define _USB_UFP_RX_OOBS_VTH_LEVEL_9                            0x09
#define _USB_UFP_RX_OOBS_VTH_LEVEL_10                           0x0A
#define _USB_UFP_RX_OOBS_VTH_LEVEL_11                           0x0B
#define _USB_UFP_RX_OOBS_VTH_LEVEL_12                           0x0C
#define _USB_UFP_RX_OOBS_VTH_LEVEL_13                           0x0D
#define _USB_UFP_RX_OOBS_VTH_LEVEL_14                           0x0E
#define _USB_UFP_RX_OOBS_VTH_LEVEL_15                           0x0F

//--------------------------------------------------
// Type-C Port Controller Type List
//--------------------------------------------------
#define _PORT_CTRL_NONE                                         0
#define _PORT_CTRL_RTS                                          1
#define _PORT_CTRL_EMBEDDED                                     2
#define _PORT_CTRL_USER                                         3
#define _PORT_CTRL_RTD                                          4
#define _PORT_CTRL_TCPM                                         5

//--------------------------------------------------
// Type-C Extern Port Controller Pin E Aux PN Swap and Lane Swap Option
//--------------------------------------------------
#define _SWAP_BY_SCALER                                         0
#define _SWAP_BY_PORT_CTRL                                      1

//--------------------------------------------------
// Type-C Discrete Port Controller (RTS / User) Status Communication
//--------------------------------------------------
#define _EXT_PORT_CTRL_NOT_EXIST                                0   // For Port Ctrl Embedded Only
#define _EXT_PORT_CTRL_DETECT_BY_SMBUS                          1   // For Port Ctrl RTS Only
#define _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO                      2   // For Port Ctrl RTS/User

//--------------------------------------------------
//  Type-C Port Pin Config
//--------------------------------------------------
#define _TYPE_C_RX1                                             0x00
#define _TYPE_C_TX1                                             0x01
#define _TYPE_C_RX2                                             0x02
#define _TYPE_C_TX2                                             0x03

//--------------------------------------------------
//  Type-C DFP ORIENTATION Setting
//--------------------------------------------------
#define _TYPE_C_DFP_ORIENTATION_NONE                            0x00
#define _TYPE_C_DFP_ORIENTATION_UNFLIP                          0x01
#define _TYPE_C_DFP_ORIENTATION_FLIP                            0x02

//--------------------------------------------------
// Billboard Type List
//--------------------------------------------------
#define _BILLBOARD_NONE                                         0
#define _BILLBOARD_SCALER                                       1
#define _BILLBOARD_HUB                                          2
#define _BILLBOARD_EXT_PORT_CTRL                                3

//--------------------------------------------------
//  Embedded Type-C Port Type
//--------------------------------------------------
#define _TYPE_C_PORT_SRC_ONLY                                   0x00
#define _TYPE_C_PORT_SNK_ONLY                                   0x01
#define _TYPE_C_PORT_DRP                                        0x02

//--------------------------------------------------
//  Embedded Type-C Port USB Role
//--------------------------------------------------
#define _TYPE_C_USB_NOT_SUPPORT                                 0x00
#define _TYPE_C_USB_HOST_ONLY                                   0x01
#define _TYPE_C_USB_DEVICE_ONLY                                 0x02
#define _TYPE_C_USB_HOST_DEVICE                                 0x03

//--------------------------------------------------
//  Embedded Type-C Port Connector Type
//--------------------------------------------------
#define _TYPE_C_PORT_RECEPTACLE                                 0x00
#define _TYPE_C_PORT_PLUG                                       0x01

//--------------------------------------------------
// TCPC Support List
//--------------------------------------------------
#define _TCPC_NONE                                              0
#define _TCPC_ON_SEMI                                           0
#define _TCPC_RLE1109                                           0

//--------------------------------------------------
// TCPM IIC SDA/SCL Pin List
//--------------------------------------------------
#define _TCPM_NO_IIC_PIN                                        0

#if(_SCALER_TYPE == _RL6978_SERIES)
#define _TCPM_IIC_PIN_64_65_0_2                                 10
#define _TCPM_IIC_PIN_80_81_0_0                                 11
#define _TCPM_IIC_PIN_102_103_0_1                               12
#endif

//--------------------------------------------------
// TCPM Alert Pin List
//--------------------------------------------------
#define _TCPM_NO_ALERT_PIN                                      0

#if(_SCALER_TYPE == _RL6978_SERIES)
#define _TCPM_ALERT_PIN_66_67_0_2                               10
#define _TCPM_ALERT_PIN_82_83_0_0                               11
#define _TCPM_ALERT_PIN_148_149_0_1                             12
#endif

//--------------------------------------------------
// PMIC Support List
//--------------------------------------------------
#define _PMIC_NONE                                              0

//--------------------------------------------------
// PMIC IIC SDA/SCL Pin List
//--------------------------------------------------
#define _PMIC_NO_IIC_PIN                                        0

#if(_SCALER_TYPE == _RL6829_SERIES)
#define _PMIC_HW_IIC_PIN_AH1_AJ1_0_0                            10
#define _PMIC_HW_IIC_PIN_AH1_AJ1_1_0                            11
#define _PMIC_HW_IIC_PIN_AF7_AG7_0_1                            12
#define _PMIC_HW_IIC_PIN_AF7_AG7_1_1                            13
#define _PMIC_HW_IIC_PIN_AH3_AJ3_0_2                            14
#define _PMIC_HW_IIC_PIN_AH3_AJ3_1_2                            15
#endif

#if(_SCALER_TYPE == _RL6952_SERIES)
#define _PMIC_HW_IIC_PIN_H12_J8_0_1                             10
#define _PMIC_HW_IIC_PIN_H12_J8_1_1                             11
#define _PMIC_HW_IIC_PIN_E3_H8_0_0                              12
#define _PMIC_HW_IIC_PIN_E3_H8_1_0                              13
#endif

#if(_SCALER_TYPE == _RL6978_SERIES)
// RL6978 No PMIC I2C Pin
#endif

//--------------------------------------------------
// PMIC ADC Channel List
//--------------------------------------------------
#define _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0                   0x00
#define _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1                   0x01
#define _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2                   0x02
#define _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3                   0x03
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0                       0x04
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1                       0x05
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2                       0x06
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3                       0x07
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0                     0x08
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1                     0x09
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2                     0x0A
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3                     0x0B
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0                     0x0C
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1                     0x0D
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2                     0x0E
#define _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3                     0x0F
#define _TYPE_C_PMIC_ADC_MAPPING_NONE                           0xFF

//--------------------------------------------------
// PMIC OCP Method List
//--------------------------------------------------
#define _TYPE_C_PMIC_FW_OCP_NONE                                0
#define _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC                    1
#define _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC                       2
#define _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC                     3

//--------------------------------------------------
// PMIC INT Pin Check Method List
//--------------------------------------------------
#define _TYPE_C_PMIC_INT_PIN_NONE                               0
#define _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING                   1

//--------------------------------------------------
// DP Scaler Side Lane List
//--------------------------------------------------
#define _DP_SCALER_LANE0                                        0
#define _DP_SCALER_LANE1                                        1
#define _DP_SCALER_LANE2                                        2
#define _DP_SCALER_LANE3                                        3

//--------------------------------------------------
// DP Lane Mapping Type
//--------------------------------------------------
#define _DP_LANE_MAPPING_NORMAL_TYPE                            0
#define _DP_LANE_MAPPING_TYPE_C_TYPE                            1
#define _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE               2

//--------------------------------------------------
// D6 DP Port Switch From D0 or D1
// HDMI Switch Port From NATIVE INPUT PORT
//--------------------------------------------------
#define _SWITCH_NONE                                            0
#define _SWITCH_FROM_D0                                         1
#define _SWITCH_FROM_D3                                         2
#define _SWITCH_FROM_D4                                         3

//--------------------------------------------------
// TMDS Scaler Side Lane List
//--------------------------------------------------
#define _TMDS_SCALER_LANE0                                      0
#define _TMDS_SCALER_LANE1                                      1
#define _TMDS_SCALER_LANE2                                      2
#define _TMDS_SCALER_LANE3                                      3

//--------------------------------------------------
// HSync Schimitt Trigger Level List
//--------------------------------------------------
#define _HS_SCHMITT_TRIGGER_LEVEL_00                            0
#define _HS_SCHMITT_TRIGGER_LEVEL_01                            1
#define _HS_SCHMITT_TRIGGER_LEVEL_10                            2
#define _HS_SCHMITT_TRIGGER_LEVEL_11                            3

//--------------------------------------------------
// EEPROM Support List
//--------------------------------------------------
#define _EEPROM_24LC16                                          0
#define _EEPROM_24WC64                                          1 // Slave Addr: 1010 XXX0 (Config pin A0 A1 A2 for multiple 24WC64), Start Addr: WORD Type for 8KByte addressing
#define _EEPROM_CAT24M01                                        2 // Slave Addr: 1010 XXZ0 (Config pin A1 A2 for multiple CAT24M01, Z used for Subaddress MSB), subaddress = [Z, 2byte subaddress] for 1024Kb
#define _EEPROM_24256                                           3 // Slave Addr: 1010 XXX0 (Config pin A0 A1 A2 for multiple 24256), Start Addr: WORD Type for 32KByte addressing

//--------------------------------------------------
// EMBEDDED EDID TABLE LOCATION List
//--------------------------------------------------
#define _EDID_TABLE_LOCATION_CODE                               0
#define _EDID_TABLE_LOCATION_SYSTEM_EEPROM                      1
#define _EDID_TABLE_LOCATION_FLASH                              2
#define _EDID_TABLE_LOCATION_USER                               3

//--------------------------------------------------
// EMBEDDED EDID Size List
//--------------------------------------------------
#define _EDID_SIZE_NONE                                         0
#define _EDID_SIZE_128                                          0x80
#define _EDID_SIZE_256                                          0x100
#define _EDID_SIZE_384                                          0x180
#define _EDID_SIZE_512                                          0x200

//--------------------------------------------------
// EXT EEPROM EDID Size List
//--------------------------------------------------
#define _EDID_EEPROM_SIZE_NONE                                  0
#define _EDID_EEPROM_SIZE_128                                   0x80
#define _EDID_EEPROM_SIZE_256                                   0x100
#define _EDID_EEPROM_SIZE_384                                   0x180
#define _EDID_EEPROM_SIZE_512                                   0x200

//--------------------------------------------------
// AUX DDC Channel Support List
//--------------------------------------------------
#define _NO_AUX                                                 0
#define _D0_AUX_MAP_DDC0_PIN                                    1
#define _D0_AUX_MAP_DDC1_PIN                                    2
#define _D0_AUX_MAP_DDC2_PIN                                    3
#define _D1_AUX_MAP_DDC0_PIN                                    4
#define _D1_AUX_MAP_DDC1_PIN                                    5
#define _D1_AUX_MAP_DDC2_PIN                                    6
#define _D2_AUX_MAP_DDC0_PIN                                    7
#define _D2_AUX_MAP_DDC1_PIN                                    8
#define _D2_AUX_MAP_DDC2_PIN                                    9

//--------------------------------------------------
// LVDS Data Port Power Selection
//--------------------------------------------------
#define _LVDS_1_PORT_A                                          0
#define _LVDS_1_PORT_B                                          1
#define _LVDS_1_PORT_C                                          2
#define _LVDS_1_PORT_D                                          3
#define _LVDS_2_PORT_AB                                         4
#define _LVDS_2_PORT_CD                                         5
#define _LVDS_2_PORT_EF                                         6
#define _LVDS_2_PORT_GH                                         7
#define _LVDS_4_PORT_ABCD                                       8
#define _LVDS_4_PORT_CDEF                                       9
#define _LVDS_4_PORT_EFGH                                       10
#define _LVDS_8_PORT_ABCDEFGH                                   11

//--------------------------------------------------
// LVDS CLK Position Selection
//--------------------------------------------------
#define _NORMAL_MODE                                            0
#define _MODE_1                                                 1
#define _MODE_2                                                 2
#define _MODE_3                                                 3

//--------------------------------------------------
// LVDS Phase Option List
//--------------------------------------------------
#define _LVDS_PI_PHASE_AB0                                      0
#define _LVDS_PI_PHASE_AB1                                      1
#define _LVDS_PI_PHASE_AB2                                      2
#define _LVDS_PI_PHASE_AB3                                      3

#define _LVDS_PI_PHASE_CD0                                      0
#define _LVDS_PI_PHASE_CD1                                      1
#define _LVDS_PI_PHASE_CD2                                      2
#define _LVDS_PI_PHASE_CD3                                      3

#define _LVDS_PI_PHASE_EF0                                      0
#define _LVDS_PI_PHASE_EF1                                      1
#define _LVDS_PI_PHASE_EF2                                      2
#define _LVDS_PI_PHASE_EF3                                      3

#define _LVDS_PI_PHASE_GH0                                      0
#define _LVDS_PI_PHASE_GH1                                      1
#define _LVDS_PI_PHASE_GH2                                      2
#define _LVDS_PI_PHASE_GH3                                      3

//--------------------------------------------------
// LVDS Phase Control List
//--------------------------------------------------
#define _LVDS_PHASE0                                            0
#define _LVDS_PHASE1                                            1
#define _LVDS_PHASE2                                            2
#define _LVDS_PHASE3                                            3
#define _LVDS_PHASE4                                            4
#define _LVDS_PHASE5                                            5
#define _LVDS_PHASE6                                            6
#define _LVDS_PHASE7                                            7
#define _LVDS_PHASE8                                            8
#define _LVDS_PHASE9                                            9
#define _LVDS_PHASE10                                           10
#define _LVDS_PHASE11                                           11
#define _LVDS_PHASE12                                           12
#define _LVDS_PHASE13                                           13
#define _LVDS_PHASE14                                           14
#define _LVDS_PHASE15                                           15
#define _LVDS_PHASE16                                           16
#define _LVDS_PHASE17                                           17
#define _LVDS_PHASE18                                           18
#define _LVDS_PHASE19                                           19
#define _LVDS_PHASE20                                           20
#define _LVDS_PHASE21                                           21
#define _LVDS_PHASE22                                           22
#define _LVDS_PHASE23                                           23
#define _LVDS_PHASE24                                           24
#define _LVDS_PHASE25                                           25
#define _LVDS_PHASE26                                           26
#define _LVDS_PHASE27                                           27
#define _LVDS_PHASE28                                           28
#define _LVDS_PHASE29                                           29
#define _LVDS_PHASE30                                           30
#define _LVDS_PHASE31                                           31

//--------------------------------------------------
// Panel DPTx Lane Port Selection
//--------------------------------------------------
#define _DPTX_TX0_PORT                                          _BIT0
#define _DPTX_TX1_PORT                                          _BIT1
#define _DPTX_TX2_PORT                                          _BIT2
#define _DPTX_TX3_PORT                                          _BIT3

//--------------------------------------------------
// PWM Support List
//--------------------------------------------------
#define _NO_PWM                                                 0x00
#define _PWM0                                                   _BIT0
#define _PWM1                                                   _BIT1
#define _PWM2                                                   _BIT2
#define _PWM3                                                   _BIT3
#define _PWM4                                                   _BIT4
#define _PWM5                                                   _BIT5

//--------------------------------------------------
// PWM Option List
//--------------------------------------------------
#define _PWM_8BIT                                               256U
#define _PWM_12BIT                                              4096U

//--------------------------------------------------
// PWM Support List
//--------------------------------------------------
#define _XTAL27000K                                             27000UL
#define _XTAL24576K                                             24576UL
#define _XTAL24000K                                             24000UL
#define _XTAL14318K                                             14318UL


//--------------------------------------------------
// IIC Application Support List
//--------------------------------------------------
#define _IIC_NONE                                               0
#define _IIC_SYS_EEPROM                                         1
#define _IIC_SMBUS_D0                                           2
#define _IIC_SMBUS_D1                                           3
#define _IIC_SMBUS_D2                                           4
#define _IIC_SMBUS_P0                                           5
#define _IIC_SMBUS_P1                                           6
#define _IIC_SMBUS_P2                                           7
#define _IIC_SMBUS_P3                                           8
#define _IIC_SMBUS_P4                                           9
#define _IIC_SMBUS_ADAPTOR                                      10
#define _IIC_DATA_EXCHANGE                                      11

//--------------------------------------------------
// IIC SDA/SCL Pin List
//--------------------------------------------------
#define _NO_IIC_PIN                                             0
#define _SW_IIC_PIN_GPIO                                        1
#define _HW_IIC_PIN_START                                       10
#define _HW_TYPEC_IIC_PIN_START                                 50

#if(_SCALER_TYPE == _RL6829_SERIES)
#define _HW_IIC_PIN_AC6_AA8_0_3                                 (_HW_IIC_PIN_START + 0)
#define _HW_IIC_PIN_F1_G4_0_0                                   (_HW_IIC_PIN_START + 1)
#define _HW_IIC_PIN_D1_E1_0_1                                   (_HW_IIC_PIN_START + 2)
#define _HW_IIC_PIN_AC6_AA8_1_3                                 (_HW_IIC_PIN_START + 3)
#define _HW_IIC_PIN_AB5_AB6_0_6                                 (_HW_IIC_PIN_START + 4)
#define _HW_IIC_PIN_AJ25_AK21_0_7                               (_HW_IIC_PIN_START + 5)
#define _HW_IIC_PIN_F4_G1_1_2                                   (_HW_IIC_PIN_START + 6)
#define _HW_IIC_PIN_F20_F19_0_4                                 (_HW_IIC_PIN_START + 7)
#define _HW_IIC_PIN_D1_E1_1_1                                   (_HW_IIC_PIN_START + 8)
#define _HW_IIC_PIN_F1_G4_1_0                                   (_HW_IIC_PIN_START + 9)
#define _HW_IIC_PIN_G21_E21_0_5                                 (_HW_IIC_PIN_START + 10)
#define _HW_IIC_PIN_AJ25_AK21_1_7                               (_HW_IIC_PIN_START + 11)
#define _HW_IIC_PIN_AB5_AB6_1_6                                 (_HW_IIC_PIN_START + 12)
#define _HW_IIC_PIN_G21_E21_1_5                                 (_HW_IIC_PIN_START + 13)
#define _HW_IIC_PIN_F20_F19_1_4                                 (_HW_IIC_PIN_START + 14)
#define _HW_IIC_PIN_E3_E2                                       (_HW_IIC_PIN_START + 15)
#define _HW_IIC_PIN_F4_G1_0_2                                   (_HW_IIC_PIN_START + 16)
#define _TYPEC_IIC_PIN_AH3_AJ3_1_2                              (_HW_TYPEC_IIC_PIN_START + 0)
#define _TYPEC_IIC_PIN_AH3_AJ3_0_2                              (_HW_TYPEC_IIC_PIN_START + 1)
#define _TYPEC_IIC_PIN_AF7_AG7_0_1                              (_HW_TYPEC_IIC_PIN_START + 2)
#define _TYPEC_IIC_PIN_AF7_AG7_1_1                              (_HW_TYPEC_IIC_PIN_START + 3)
#define _TYPEC_IIC_PIN_AH1_AJ1_0_0                              (_HW_TYPEC_IIC_PIN_START + 4)
#define _TYPEC_IIC_PIN_AH1_AJ1_1_0                              (_HW_TYPEC_IIC_PIN_START + 5)
#endif

#if(_SCALER_TYPE == _RL6952_SERIES)
#define _HW_IIC_PIN_E3_E2                                       (_HW_IIC_PIN_START + 0)
#define _HW_IIC_PIN_D13_H9_0_3                                  (_HW_IIC_PIN_START + 1)
#define _HW_IIC_PIN_D5_D4_0_0                                   (_HW_IIC_PIN_START + 2)
#define _HW_IIC_PIN_D3_H7_0_1                                   (_HW_IIC_PIN_START + 3)
#define _HW_IIC_PIN_D13_H9_1_3                                  (_HW_IIC_PIN_START + 4)
#define _HW_IIC_PIN_W23_W22_0_6                                 (_HW_IIC_PIN_START + 5)
#define _HW_IIC_PIN_U4_G8_0_7                                   (_HW_IIC_PIN_START + 6)
#define _HW_IIC_PIN_J9_E5_1_2                                   (_HW_IIC_PIN_START + 7)
#define _HW_IIC_PIN_D3_H7_1_1                                   (_HW_IIC_PIN_START + 8)
#define _HW_IIC_PIN_AE26_AD26_0_4                               (_HW_IIC_PIN_START + 9)
#define _HW_IIC_PIN_D5_D4_1_0                                   (_HW_IIC_PIN_START + 10)
#define _HW_IIC_PIN_AA23_Y24_0_5                                (_HW_IIC_PIN_START + 11)
#define _HW_IIC_PIN_U4_G8_1_7                                   (_HW_IIC_PIN_START + 12)
#define _HW_IIC_PIN_W23_W22_1_6                                 (_HW_IIC_PIN_START + 13)
#define _HW_IIC_PIN_AA23_Y24_1_5                                (_HW_IIC_PIN_START + 14)
#define _HW_IIC_PIN_AE26_AD26_1_4                               (_HW_IIC_PIN_START + 15)
#define _HW_IIC_PIN_AG6_AG7                                     (_HW_IIC_PIN_START + 16)
#define _HW_IIC_PIN_J9_E5_0_2                                   (_HW_IIC_PIN_START + 17)
#define _HW_IIC_BGA_2L_PIN_AG16_AG17                            (_HW_IIC_PIN_START + 18)
#define _TYPEC_IIC_PIN_H12_J8_0_1                               (_HW_TYPEC_IIC_PIN_START + 0)
#define _TYPEC_IIC_PIN_H12_J8_1_1                               (_HW_TYPEC_IIC_PIN_START + 1)
#define _TYPEC_IIC_PIN_E3_H8_0_0                                (_HW_TYPEC_IIC_PIN_START + 2)
#define _TYPEC_IIC_PIN_E3_H8_1_0                                (_HW_TYPEC_IIC_PIN_START + 3)
#endif

#if(_SCALER_TYPE == _RL6978_SERIES)
#define _HW_IIC_PIN_57_58                                       (_HW_IIC_PIN_START + 0)
#define _HW_IIC_PIN_72_73_0_5                                   (_HW_IIC_PIN_START + 1)
#define _HW_IIC_PIN_72_73_1_5                                   (_HW_IIC_PIN_START + 2)
#define _HW_IIC_PIN_80_81_0_6                                   (_HW_IIC_PIN_START + 3)
#define _HW_IIC_PIN_80_81_1_6                                   (_HW_IIC_PIN_START + 4)
#define _HW_IIC_PIN_106_107_0_0                                 (_HW_IIC_PIN_START + 5)
#define _HW_IIC_PIN_106_107_1_0                                 (_HW_IIC_PIN_START + 6)
#define _HW_IIC_PIN_148_149_0_7                                 (_HW_IIC_PIN_START + 7)
#define _HW_IIC_PIN_148_149_1_7                                 (_HW_IIC_PIN_START + 8)
#define _HW_IIC_PIN_161_162_0_4                                 (_HW_IIC_PIN_START + 9)
#define _HW_IIC_PIN_161_162_1_4                                 (_HW_IIC_PIN_START + 10)
#define _HW_IIC_PIN_227_228_0_2                                 (_HW_IIC_PIN_START + 11)
#define _HW_IIC_PIN_227_228_1_2                                 (_HW_IIC_PIN_START + 12)
#define _HW_IIC_PIN_235_236_0_3                                 (_HW_IIC_PIN_START + 13)
#define _HW_IIC_PIN_235_236_1_3                                 (_HW_IIC_PIN_START + 14)
#define _HW_IIC_PIN_248_249_0_8                                 (_HW_IIC_PIN_START + 15)
#define _HW_IIC_PIN_248_249_1_8                                 (_HW_IIC_PIN_START + 16)
#define _HW_IIC_PIN_252_253                                     (_HW_IIC_PIN_START + 17)
#define _HW_IIC_PIN_252_253_0_9                                 (_HW_IIC_PIN_START + 18)
#define _HW_IIC_PIN_252_253_1_9                                 (_HW_IIC_PIN_START + 19)
#define _HW_IIC_PIN_266_267_0_1                                 (_HW_IIC_PIN_START + 20)
#define _HW_IIC_PIN_266_267_1_1                                 (_HW_IIC_PIN_START + 21)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_202_203            (_HW_IIC_PIN_57_58)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_216_1_0_5          (_HW_IIC_PIN_72_73_0_5)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_216_1_1_5          (_HW_IIC_PIN_72_73_1_5)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_7_9_0_6            (_HW_IIC_PIN_80_81_0_6)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_7_9_1_6            (_HW_IIC_PIN_80_81_1_6)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_58_57_0_7          (_HW_IIC_PIN_148_149_0_7)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_58_57_1_7          (_HW_IIC_PIN_148_149_1_7)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_70_69_0_4          (_HW_IIC_PIN_161_162_0_4)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_70_69_1_4          (_HW_IIC_PIN_161_162_1_4)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_111_112_0_2        (_HW_IIC_PIN_227_228_0_2)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_111_112_1_2        (_HW_IIC_PIN_227_228_1_2)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_128_129_0_8        (_HW_IIC_PIN_248_249_0_8)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_128_129_1_8        (_HW_IIC_PIN_248_249_1_8)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_132_133            (_HW_IIC_PIN_252_253)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_132_133_0_9        (_HW_IIC_PIN_252_253_0_9)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_132_133_1_9        (_HW_IIC_PIN_252_253_1_9)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_145_146_0_1        (_HW_IIC_PIN_266_267_0_1)
#define _HW_IIC_LQFP216_4D_USB_DDRx2_eDP_PIN_145_146_1_1        (_HW_IIC_PIN_266_267_1_1)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_202_203           (_HW_IIC_PIN_57_58)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_216_1_0_5         (_HW_IIC_PIN_72_73_0_5)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_216_1_1_5         (_HW_IIC_PIN_72_73_1_5)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_7_9_0_6           (_HW_IIC_PIN_80_81_0_6)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_7_9_1_6           (_HW_IIC_PIN_80_81_1_6)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_27_28_0_0         (_HW_IIC_PIN_106_107_0_0)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_27_28_1_0         (_HW_IIC_PIN_106_107_1_0)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_58_57_0_7         (_HW_IIC_PIN_148_149_0_7)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_58_57_1_7         (_HW_IIC_PIN_148_149_1_7)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_70_69_0_4         (_HW_IIC_PIN_161_162_0_4)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_70_69_1_4         (_HW_IIC_PIN_161_162_1_4)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_114_115_0_2       (_HW_IIC_PIN_227_228_0_2)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_114_115_1_2       (_HW_IIC_PIN_227_228_1_2)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_121_122_0_3       (_HW_IIC_PIN_235_236_0_3)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_121_122_1_3       (_HW_IIC_PIN_235_236_1_3)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_133_134_0_8       (_HW_IIC_PIN_248_249_0_8)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_133_134_1_8       (_HW_IIC_PIN_248_249_1_8)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_137_138           (_HW_IIC_PIN_252_253)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_137_138_0_9       (_HW_IIC_PIN_252_253_0_9)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_137_138_1_9       (_HW_IIC_PIN_252_253_1_9)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_150_151_0_1       (_HW_IIC_PIN_266_267_0_1)
#define _HW_IIC_LQFP216_3D_USB_DDRx1_LVDS_PIN_150_151_1_1       (_HW_IIC_PIN_266_267_1_1)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_29_30                 (_HW_IIC_PIN_57_58)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_43_44_0_5             (_HW_IIC_PIN_72_73_0_5)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_43_44_1_5             (_HW_IIC_PIN_72_73_1_5)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_91_90_0_4             (_HW_IIC_PIN_161_162_0_4)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_91_90_1_4             (_HW_IIC_PIN_161_162_1_4)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_140_141_0_8           (_HW_IIC_PIN_248_249_0_8)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_140_141_1_8           (_HW_IIC_PIN_248_249_1_8)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_144_145               (_HW_IIC_PIN_252_253)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_144_145_0_9           (_HW_IIC_PIN_252_253_0_9)
#define _HW_IIC_LQFP156_2D_DDRx1_LVDS_PIN_144_145_1_9           (_HW_IIC_PIN_252_253_1_9)
#endif

//--------------------------------------------------
// HW IIC Speed List
//--------------------------------------------------
#define _HW_IIC_LOW_SPEED_100K                                  0
#define _HW_IIC_HIGH_SPEED_400K                                 1
#define _HW_IIC_HIGH_SPEED_1M                                   2

//--------------------------------------------------
// IIC Slave Support Option
//--------------------------------------------------
#define _IIC_SLAVE_DET_BY_GPIO                                  0
#define _IIC_SLAVE_DEFAULT_ON                                   1
#define _IIC_SLAVE_DEFAULT_OFF                                  2

//--------------------------------------------------
// DDC Switch GPIO List
//--------------------------------------------------
#define _DDC0_SWITCH_GPIO                                       0
#define _DDC0_SWITCH_DDC                                        1
#define _DDC1_SWITCH_GPIO                                       2
#define _DDC1_SWITCH_DDC                                        3
#define _DDC2_SWITCH_GPIO                                       4
#define _DDC2_SWITCH_DDC                                        5
#define _DDC3_SWITCH_GPIO                                       6
#define _DDC3_SWITCH_DDC                                        7
#define _DDC4_SWITCH_GPIO                                       8
#define _DDC4_SWITCH_DDC                                        9
#define _DDC5_SWITCH_GPIO                                       10
#define _DDC5_SWITCH_DDC                                        11
#define _DDC_VGA_SWITCH_GPIO                                    12
#define _DDC_VGA_SWITCH_DDC                                     13
#define _DDCISP_SWITCH_GPIO                                     14
#define _DDCISP_SWITCH_DDC                                      15
#define _DDC2_SWITCH_GPI                                        16
#define _DDC3_SWITCH_GPI                                        17
#define _DDC4_SWITCH_GPI                                        18
#define _DDC1_SWITCH_GPI                                        19

//--------------------------------------------------
// Spread Spectrum Speed
//--------------------------------------------------
#define _SPEED_33K                                              0
#define _SPEED_66K                                              1
#define _SPEED_30K                                              2
#define _SPEED_27K                                              3

//--------------------------------------------------
// ADC Detect Interrupt ADC Channel List
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0                       0x00
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1                       0x01
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_2                       0x02
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_3                       0x03
#endif

#if(_SCALER_TYPE == _RL6952_SERIES)
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0                     0x04
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_1                     0x05
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_2                     0x06
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3                     0x07
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0                     0x08
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_1                     0x09
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_2                     0x0A
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3                     0x0B
#endif

#if(_SCALER_TYPE == _RL6978_SERIES)
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0                     0x04
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_1                     0x05
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_2                     0x06
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3                     0x07
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0                     0x08
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_1                     0x09
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_2                     0x0A
#define _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3                     0x0B
#endif

#define _ADC_DET_INT_ADC_MAPPING_NONE                           0xFF

//--------------------------------------------------
// PCB Type for DP HBR2
//--------------------------------------------------
#define _DP_HBR2_NORMAL_PCB                                     0
#define _DP_HBR2_AIO_PCB                                        1
#define _DP_HBR2_RE_DRIVER_PCB                                  2

//--------------------------------------------------
// DP Swing Level
//--------------------------------------------------
#define _DP_SWING_400_MV                                        0
#define _DP_SWING_600_MV                                        1
#define _DP_SWING_800_MV                                        2
#define _DP_SWING_1200_MV                                       3

//--------------------------------------------------
// DP Preemphasis Level
//--------------------------------------------------
#define _DP_PREEMPHASIS_0_DB                                    0
#define _DP_PREEMPHASIS_3_5_DB                                  1
#define _DP_PREEMPHASIS_6_DB                                    2
#define _DP_PREEMPHASIS_9_5_DB                                  3

//--------------------------------------------------
// LVDS Driving Current List
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL_2_0                                  0
#define _LVDS_DRIV_CONTROL_2_5                                  1
#define _LVDS_DRIV_CONTROL_3_0                                  2
#define _LVDS_DRIV_CONTROL_3_5                                  3
#define _LVDS_DRIV_CONTROL_1_5                                  4

//--------------------------------------------------
// LVDS Slew Rate Control List
//--------------------------------------------------
#define _LVDS_SR_CONTROL_0                                      0
#define _LVDS_SR_CONTROL_1                                      1
#define _LVDS_SR_CONTROL_2                                      2
#define _LVDS_SR_CONTROL_3                                      3

//--------------------------------------------------
// LVDS Shape Adjustment List
//--------------------------------------------------
#define _LVDS_SHAPE_FAST_TO_SLOW                                0
#define _LVDS_SHAPE_SLOW_TO_FAST                                1

//--------------------------------------------------
// LVDS Common Mode Voltage List
//--------------------------------------------------
#define _LVDS_VCM_LOW                                           0
#define _LVDS_VCM_NORMAL                                        1
#define _LVDS_VCM_HIGH                                          2
#define _LVDS_VCM_USER                                          3

//--------------------------------------------------
// LVDS Pre-emphasis Current List
//--------------------------------------------------
#define _LVDS_PRE_EMPHASIS_0                                    0
#define _LVDS_PRE_EMPHASIS_1                                    1
#define _LVDS_PRE_EMPHASIS_2                                    2
#define _LVDS_PRE_EMPHASIS_3                                    3

//--------------------------------------------------
// Vbyone Driving Current List
//--------------------------------------------------
#define _VBO_DRIV_CONTROL_2_0                                   0
#define _VBO_DRIV_CONTROL_2_5                                   1
#define _VBO_DRIV_CONTROL_3_0                                   2
#define _VBO_DRIV_CONTROL_3_5                                   3

//--------------------------------------------------
// Vbyone Pre-emphasis Current List
//--------------------------------------------------
#define _VBO_PRE_EMPHASIS_0                                     0
#define _VBO_PRE_EMPHASIS_1                                     1
#define _VBO_PRE_EMPHASIS_2                                     2
#define _VBO_PRE_EMPHASIS_3                                     3

//--------------------------------------------------
// Definitions of Type-C CC Attach LEVEL
//--------------------------------------------------
#define _PCB_DP_TYPE_C_CC_ATTACH_LEVEL                          0
#define _PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL                      1

//--------------------------------------------------
// Definitions of Type-C Alt Mode Ready LEVEL
//--------------------------------------------------
#define _PCB_DP_TYPE_C_ALTMODE_LEVEL                            0
#define _PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL                  1

//--------------------------------------------------
// Definitions of Cable Connect LEVEL
//--------------------------------------------------
#define _PCB_CABLE_CONNECT_LEVEL                                0
#define _PCB_CABLE_DISCONNECT_LEVEL                             1

//--------------------------------------------------
// Definations of HDMI-CEC
//--------------------------------------------------
#define _HDMI_CEC_NONE                                          0
#define _HDMI_CEC_0                                             1

//--------------------------------------------------
// Definations of HDMI-ARC Tx
//--------------------------------------------------
#define _HDMI_ARC_TX_NONE                                       0
#define _HDMI_ARC_TX                                            1
#define _HDMI_EARC_TX                                           2

//--------------------------------------------------
// Audio Output Option List
//--------------------------------------------------
#define _I2S                                                    0
#define _SPDIF                                                  1

//--------------------------------------------------
// FLASH DRIVE CURRENT CONTROL LIST
//--------------------------------------------------
#define _SPI_DRIVE_3_0MA                                        2
#define _SPI_DRIVE_3_5MA                                        3
#define _SPI_DRIVE_4_0MA                                        4
#define _SPI_DRIVE_4_5MA                                        5
#define _SPI_DRIVE_5_0MA                                        6
#define _SPI_DRIVE_5_5MA                                        7

//--------------------------------------------------
// FLASH SLEW RATE CONTROL Options
//--------------------------------------------------
#define _SPI_FAST_SLEW_RATE                                     0
#define _SPI_SLOW_SLEW_RATE                                     1

//--------------------------------------------------
// DP AUX Swing Level Options
//--------------------------------------------------
#define _DP_AUX_SWING_900_MV                                    12
#define _DP_AUX_SWING_1000_MV                                   13
#define _DP_AUX_SWING_1100_MV                                   14
#define _DP_AUX_SWING_1300_MV                                   15

//--------------------------------------------------
// Definitions of DCC
//--------------------------------------------------
#define _VGA_DDC                                                0
#define _DDC0                                                   1
#define _DDC1                                                   2
#define _DDC2                                                   3
#define _DDC3                                                   4
#define _DDC4                                                   5
#define _DDC5                                                   6
#define _NO_DDC                                                 7
#define _VGA_DDC2                                               8

//--------------------------------------------------
// Definitions of PACKAGE_TYPE
//--------------------------------------------------
#define _PACKAGE_RL6829_BGA                                     0x00
#define _PACKAGE_RL6952_BGA4L                                   0x01
#define _PACKAGE_RL6952_BGA2L                                   0x02
#define _PACKAGE_RL6978_LQFP216_4D_USB_DDRx2_eDP                0x03
#define _PACKAGE_RL6978_LQFP216_3D_USB_DDRx1_LVDS               0x04
#define _PACKAGE_RL6978_LQFP156_2D_DDRx1_LVDS                   0x05

#endif // End of #ifndef __PCB_LIST_H__
