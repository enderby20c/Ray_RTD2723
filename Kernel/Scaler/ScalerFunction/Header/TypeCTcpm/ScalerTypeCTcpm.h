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
// ID Code      : ScalerTypeCTcpm.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TCPM_H__
#define __SCALER_TCPM_H__

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of TCPM HW
//--------------------------------------------------
#if(_HW_TCPM_SUPPORT == _ON)
#define _HW_TCPM_IIC_BUFFER_SIZE                                36

#define _HW_TCPM_ALERT_UPDATE                                   _ON
#define _HW_TCPM_TX_AUTO_CTRL                                   _ON

#define _HW_TCPM_ALERT_AUTO_CTRL                                _ON
#define _HW_TCPM_CS_AUTO_CTRL                                   _OFF
#define _HW_TCPM_PS_AUTO_CTRL                                   _ON
#define _HW_TCPM_FS_AUTO_CTRL                                   _ON
#define _HW_TCPM_EXT_AUTO_CTRL                                  _ON
#define _HW_TCPM_ALERT_EXT_AUTO_CTRL                            _ON
#define _HW_TCPM_VENDOR_DEF_AUTO_CTRL                           _ON
#define _HW_TCPM_VALM_H_AUTO_CTRL                               _ON
#define _HW_TCPM_VALM_L_AUTO_CTRL                               _ON
#define _HW_TCPM_RX_MSG_AUTO_CTRL                               _ON
#define _HW_TCPM_RX_BGN_AUTO_CTRL                               _ON
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PPS Voltage Adjust Option
//--------------------------------------------------
#define _TCPM_UVP_PPS_THRESHOLD                                 295 // unit: 10mV
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PMIC Test FUNCTION
//--------------------------------------------------
#define _TCPM_PMIC_FORCE_OUTPUT                                 _OFF
#define _TCPM_PMIC_FORCE_VOLTAGE                                1200 // unit: 10mV
#define _TCPM_PMIC_FORCE_CURRENT                                100 // unit: 10mA

//--------------------------------------------------
// Definitions of PMIC Minimum Current
//--------------------------------------------------
#define _TCPM_PMIC_MIN_CURRENT                                  85 // unit: 10mA
#define _TCPM_PMIC_MIN_PPS_CURRENT                              60 // unit: 10mA
#endif

//--------------------------------------------------
// TCPM Voltage MACRO
//--------------------------------------------------
#define GET_TCPCI_VOLTAGE_CODE(x)                               ((WORD)(((DWORD)(x) * 10) / 25))    // Unit = 25mV (Voltage (unit: 10mV) * 10 / 25)

//--------------------------------------------------
// TCPM HW Index MACRO
//--------------------------------------------------
#define GET_TCPM_IIC_HW_SHIFT(x)                                (g_pstTypeCTcpmHwShift[x].enumTcpmIICHwShift)
#define SET_TCPM_IIC_HW_SHIFT(x, y)                             (g_pstTypeCTcpmHwShift[x].enumTcpmIICHwShift = (y))

#define GET_TCPM_TCPC_HW_SHIFT(x)                               (g_pstTypeCTcpmHwShift[x].enumTcpmTcpcHwShift)
#define SET_TCPM_TCPC_HW_SHIFT(x, y)                            (g_pstTypeCTcpmHwShift[x].enumTcpmTcpcHwShift = (y))

//--------------------------------------------------
// TCPM Genral Info Related MACRO
//--------------------------------------------------
#define GET_TCPM_STATE(x)                                       (g_pstTypeCTcpmInfo[x].enumTcpmState)
#define SET_TCPM_STATE(x, y)                                    (g_pstTypeCTcpmInfo[x].enumTcpmState = (y))

#define GET_TCPM_USB_TYPE(x)                                    (g_pstTypeCTcpmInfo[x].b2TcpmUsbType)
#define SET_TCPM_USB_TYPE(x, y)                                 (g_pstTypeCTcpmInfo[x].b2TcpmUsbType = (y))

#define GET_TCPM_USB_SPEED(x)                                   (g_pstTypeCTcpmInfo[x].b2TcpmUsbSpeed)
#define SET_TCPM_USB_SPEED(x, y)                                (g_pstTypeCTcpmInfo[x].b2TcpmUsbSpeed = (y))

#define GET_TCPM_USB_ROLE(x)                                    (g_pstTypeCTcpmInfo[x].b2TcpmUsbRole)
#define SET_TCPM_USB_ROLE(x, y)                                 (g_pstTypeCTcpmInfo[x].b2TcpmUsbRole = (y))

#define GET_TCPM_CONNECTOR_TYPE(x)                              (g_pstTypeCTcpmInfo[x].b1TcpmConnectorType)
#define SET_TCPM_CONNECTOR_TYPE(x, y)                           (g_pstTypeCTcpmInfo[x].b1TcpmConnectorType = (y))

//--------------------------------------------------
// TCPC Related MACRO
//--------------------------------------------------
#define GET_TCPM_TCPC_TYPE(x)                                   (g_pstTypeCTcpmDeviceInfo[x].ucTcpcType)
#define SET_TCPM_TCPC_TYPE(x, y)                                (g_pstTypeCTcpmDeviceInfo[x].ucTcpcType = (y))

#define GET_TCPM_TCPC_SLAVE_ADDR(x)                             (g_pstTypeCTcpmDeviceInfo[x].ucSlaveAddr)
#define SET_TCPM_TCPC_SLAVE_ADDR(x, y)                          (g_pstTypeCTcpmDeviceInfo[x].ucSlaveAddr = (y))

#define GET_TCPM_ALERT_VALID(x)                                 (g_pstTypeCTcpmDeviceInfo[x].usAlertValid)
#define SET_TCPM_ALERT_VALID(x, y)                              (g_pstTypeCTcpmDeviceInfo[x].usAlertValid = (y))

#define GET_TCPM_VENDOR_ID(x)                                   (g_pstTypeCTcpmDeviceInfo[x].usVendorID)
#define SET_TCPM_VENDOR_ID(x, y)                                (g_pstTypeCTcpmDeviceInfo[x].usVendorID = (y))

#define GET_TCPM_PRODUCT_ID(x)                                  (g_pstTypeCTcpmDeviceInfo[x].usProductID)
#define SET_TCPM_PRODUCT_ID(x, y)                               (g_pstTypeCTcpmDeviceInfo[x].usProductID = (y))

#define GET_TCPM_DEVICE_ID(x)                                   (g_pstTypeCTcpmDeviceInfo[x].usDeviceID)
#define SET_TCPM_DEVICE_ID(x, y)                                (g_pstTypeCTcpmDeviceInfo[x].usDeviceID = (y))

#define GET_TCPM_DEVICE_CC_VER(x)                               (g_pstTypeCTcpmDeviceInfo[x].usTypeCVer)
#define SET_TCPM_DEVICE_CC_VER(x, y)                            (g_pstTypeCTcpmDeviceInfo[x].usTypeCVer = (y))

#define GET_TCPM_DEVICE_PD_VER(x)                               (g_pstTypeCTcpmDeviceInfo[x].usPdVer)
#define SET_TCPM_DEVICE_PD_VER(x, y)                            (g_pstTypeCTcpmDeviceInfo[x].usPdVer = (y))

#define GET_TCPM_DEVICE_TCPCI_VER(x)                            (g_pstTypeCTcpmDeviceInfo[x].usInterfaceVer)
#define SET_TCPM_DEVICE_TCPCI_VER(x, y)                         (g_pstTypeCTcpmDeviceInfo[x].usInterfaceVer = (y))

#define GET_TCPM_ALERT_MASK(x)                                  (g_pstTypeCTcpmDeviceInfo[x].usAlertMask)
#define SET_TCPM_ALERT_MASK(x, y)                               (g_pstTypeCTcpmDeviceInfo[x].usAlertMask = (y))

#define GET_TCPM_POWER_STATUS_MASK(x)                           (g_pstTypeCTcpmDeviceInfo[x].ucPowerStatusMask)
#define SET_TCPM_POWER_STATUS_MASK(x, y)                        (g_pstTypeCTcpmDeviceInfo[x].ucPowerStatusMask = (y))

#define GET_TCPM_FAULT_STATUS_MASK(x)                           (g_pstTypeCTcpmDeviceInfo[x].ucFaultStatusMask)
#define SET_TCPM_FAULT_STATUS_MASK(x, y)                        (g_pstTypeCTcpmDeviceInfo[x].ucFaultStatusMask = (y))

#define GET_TCPM_TCPC_CONTROL(x)                                (g_pstTypeCTcpmDeviceInfo[x].ucTcpcControl)
#define SET_TCPM_TCPC_CONTROL(x, y)                             (g_pstTypeCTcpmDeviceInfo[x].ucTcpcControl = (y))

#define GET_TCPM_ROLE_CONTROL(x)                                (g_pstTypeCTcpmDeviceInfo[x].ucRoleControl)
#define SET_TCPM_ROLE_CONTROL(x, y)                             (g_pstTypeCTcpmDeviceInfo[x].ucRoleControl = (y))

#define GET_TCPM_FAULT_CONTROL(x)                               (g_pstTypeCTcpmDeviceInfo[x].ucFaultControl)
#define SET_TCPM_FAULT_CONTROL(x, y)                            (g_pstTypeCTcpmDeviceInfo[x].ucFaultControl = (y))

#define GET_TCPM_POWER_CONTROL(x)                               (g_pstTypeCTcpmDeviceInfo[x].ucPowerControl)
#define SET_TCPM_POWER_CONTROL(x, y)                            (g_pstTypeCTcpmDeviceInfo[x].ucPowerControl = (y))

#define GET_TCPM_CC_STATUS(x)                                   (g_pstTypeCTcpmDeviceInfo[x].ucCcStatus)
#define SET_TCPM_CC_STATUS(x, y)                                (g_pstTypeCTcpmDeviceInfo[x].ucCcStatus = (y))

#define GET_TCPM_FAULT_STATUS(x)                                (g_pstTypeCTcpmDeviceInfo[x].ucFaultStatus)
#define SET_TCPM_FAULT_STATUS(x, y)                             (g_pstTypeCTcpmDeviceInfo[x].ucFaultStatus = (y))

#define GET_TCPM_DEVICE_CAPABILITY_1(x)                         (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1)
#define SET_TCPM_DEVICE_CAPABILITY_1(x, y)                      (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 = (y))

#define GET_TCPM_DEVICE_CAPABILITY_2(x)                         (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2)
#define SET_TCPM_DEVICE_CAPABILITY_2(x, y)                      (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 = (y))

#define GET_TCPM_DEVICE_CAPABILITY_3(x)                         (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap3)
#define SET_TCPM_DEVICE_CAPABILITY_3(x, y)                      (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap3 = (y))

#define GET_TCPM_DEVICE_STD_INPUT_CAP(x)                        (g_pstTypeCTcpmDeviceInfo[x].ucStdInputCap)
#define SET_TCPM_DEVICE_STD_INPUT_CAP(x, y)                     (g_pstTypeCTcpmDeviceInfo[x].ucStdInputCap = (y))

#define GET_TCPM_DEVICE_STD_OUTPUT_CAP(x)                       (g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap)
#define SET_TCPM_DEVICE_STD_OUTPUT_CAP(x, y)                    (g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap = (y))

// Device Cap1 [15] : Source Vbus Nondefault Target (0x7A~0x7Bh) Support
#define GET_TCPM_DEVICE_VBUS_TARGET_CAP(x)                      ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT15) >> 15)
// Device Cap1 [14] : Vbus OCP Reported by TCPC Support
#define GET_TCPM_DEVICE_OCP_REPORT_CAP(x)                       ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT14) >> 14)
// Device Cap1 [13] : Vbus OVP Reported by TCPC Support
#define GET_TCPM_DEVICE_OVP_REPORT_CAP(x)                       ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT13) >> 13)
// Device Cap1 [12] : Bleed Discharge
#define GET_TCPM_DEVICE_BLD_DISCHARGE_CAP(x)                    ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT12) >> 12)
// Device Cap1 [11] : Force Discharge
#define GET_TCPM_DEVICE_FRC_DISCHARGE_CAP(x)                    ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT11) >> 11)
// Device Cap1 [10] : Vbus Measure & Alarm (0x70~0x71h, 0x76~0x79h) Support
#define GET_TCPM_DEVICE_VBUS_MEASURE_CAP(x)                     ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT10) >> 10)
// Device Cap1 [9:8]: Source Rp Value Capability
#define GET_TCPM_DEVICE_RP_CAP(x)                               ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & (_BIT9 | _BIT8)) >> 8)
// Device Cap1 [7:5]: TypeC CC Operation Mode Support
#define GET_TCPM_DEVICE_CC_ROLE_CAP(x)                          ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & (_BIT7 | _BIT6 | _BIT5)) >> 5)
// Device Cap1 [4]  : SOP'/"_Debug Support
#define GET_TCPM_DEVICE_SOPP_DBG_CAP(x)                         ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT4) >> 4)
// Device Cap1 [3]  : Source Vconn Support
#define GET_TCPM_DEVICE_SRC_VCONN_CAP(x)                        ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT3) >> 3)
// Device Cap1 [2]  : Sink Vbus Support
#define GET_TCPM_DEVICE_SNK_VBUS_CAP(x)                         ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT2) >> 2)
// Device Cap1 [1]  : Source > 5V Vbus Support
#define GET_TCPM_DEVICE_SRC_HV_CAP(x)                           ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT1) >> 1)
// Device Cap1 [0]  : Source 5V Vbus Support
#define GET_TCPM_DEVICE_SRC_VBUS_CAP(x)                         (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap1 & _BIT0)

// Device Cap2 [15] : Device Capability 3 Support
#define GET_TCPM_DEVICE_DEVICE_CAP3_CAP(x)                      ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT15) >> 15)

// Device Cap2 [14] : TCPC (Sink) Auto Disabled PD Rx When Disconnect
#define GET_TCPM_DEVICE_RX_AUTO_DISABLE_CAP(x)                  ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT14) >> 14)
// Device Cap2 [13] : Generic Timer Support
#define GET_TCPM_DEVICE_GENERIC_TIMER_CAP(x)                    ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT13) >> 13)
// Device Cap2 [12] : Long Message > 30-Byte Support
#define GET_TCPM_DEVICE_LONG_MSG_CAP(x)                         ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT12) >> 12)
// Device Cap2 [11] : SMBus PEC Support
#define GET_TCPM_DEVICE_SMBUS_PEC_CAP(x)                        ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT11) >> 11)
// Device Cap2 [10] : Source FRS Support
#define GET_TCPM_DEVICE_SRC_FRS_CAP(x)                          ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT10) >> 10)
// Device Cap2 [9]  : Sink FRS Support
#define GET_TCPM_DEVICE_SNK_FRS_CAP(x)                          ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT9) >> 9)
// Device Cap2 [8]  : Watch Dog Timer Support
#define GET_TCPM_DEVICE_WD_TIMER_CAP(x)                         ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT8) >> 8)
// Device Cap2 [7]  : Sink Disconnect Detect (0x72~0x73h) Support
#define GET_TCPM_DEVICE_SNK_DISC_CAP(x)                         ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT7) >> 7)
// Device Cap2 [6]  : Stop Discharge Threshold (0x74~0x75h) Support
#define GET_TCPM_DEVICE_STOP_DISCH_THR_CAP(x)                   ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT6) >> 6)
// Device Cap2 [5:4]: Vbus Alarm Units (affect to 0x72~0x79h)
#define GET_TCPM_DEVICE_VBUS_ALARM_LSB_CAP(x)                   ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & (_BIT5 | _BIT4)) >> 4)
// Device Cap2 [3:1]: Source Vconn Power Support
#define GET_TCPM_DEVICE_VCONN_PWR_CAP(x)                        ((g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & (_BIT3 | _BIT2 | _BIT1)) >> 1)
// Device Cap2 [0]  : Vcoonn OCP Support
#define GET_TCPM_DEVICE_VCONN_OCP_CAP(x)                        (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap2 & _BIT0)

// Device Cap3 [2:0]: Max. Vbus Voltage Support
#define GET_TCPM_DEVICE_VBUS_MAX_CAP(x)                         (g_pstTypeCTcpmDeviceInfo[x].usDeviceCap3 & (_BIT2 | _BIT1 | _BIT0))

// Std. Iuput [4:3] : Src FRS Pin Not Support / Input / In Out
#define GET_TCPM_DEVICE_FRS_IO_CAP(x)                           ((g_pstTypeCTcpmDeviceInfo[x].ucStdInputCap & (_BIT4 | _BIT3)) >> 3)
// Std. Iuput [2]   : Vbus Ext. OVP Input Support
#define GET_TCPM_DEVICE_EXT_OVP_IN_CAP(x)                       ((g_pstTypeCTcpmDeviceInfo[x].ucStdInputCap & _BIT2) >> 2)
// Std. Iuput [1]   : Vbus Ext. OCP Input Support
#define GET_TCPM_DEVICE_EXT_OCP_IN_CAP(x)                       ((g_pstTypeCTcpmDeviceInfo[x].ucStdInputCap & _BIT1) >> 1)
// Std. Iuput [0]   : Force Off Vbus Input Support
#define GET_TCPM_DEVICE_FRC_OFF_VBUS_IN_CAP(x)                  (g_pstTypeCTcpmDeviceInfo[x].ucStdInputCap & _BIT0)

// Std. Output [7]  : VBUS Sink Disconnect Detect Output Support
#define GET_TCPM_DEVICE_SNK_DISC_DET_OUT_CAP(x)                 ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT7) >> 7)
// Std. Output [6]  : Debug Accessory Output Support (if 0, TCPC Not Support Debug_Accessory FSM)
#define GET_TCPM_DEVICE_DEBUG_ACC_OUT_CAP(x)                    ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT6) >> 6)
// Std. Output [5]  : VBUS Present Output Support
#define GET_TCPM_DEVICE_VBUS_PRESENT_OUT_CAP(x)                 ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT5) >> 5)
// Std. Output [4]  : Audio Adapter Accessory Output Support
#define GET_TCPM_DEVICE_AUDIO_ACC_OUT_CAP(x)                    ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT4) >> 4)
// Std. Output [3]  : Active Cable Output Support
#define GET_TCPM_DEVICE_ACTIVE_CABLE_OUT_CAP(x)                 ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT3) >> 3)
// Std. Output [2]  : MUX Configuration Control Output Support
#define GET_TCPM_DEVICE_MUX_CTRL_OUT_CAP(x)                     ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT2) >> 2)
// Std. Output [1]  : Connection Present Output Support
#define GET_TCPM_DEVICE_CONNECT_OUT_CAP(x)                      ((g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT1) >> 1)
// Std. Output [0]  : Connector Orientation Output Support
#define GET_TCPM_DEVICE_DEBUG_ORIENT_OUT_CAP(x)                 (g_pstTypeCTcpmDeviceInfo[x].ucStdOutputCap & _BIT0)

//--------------------------------------------------
// TCPM PD/CC Top Info Related MACRO
//--------------------------------------------------
#define GET_TCPM_POWER_ROLE(x)                                  (BYTE)(g_pstTypeCTcpmTopInfo[x].b1PowerRole)
#define SET_TCPM_POWER_ROLE(x, y)                               (g_pstTypeCTcpmTopInfo[x].b1PowerRole = (y))

#define GET_TCPM_DATA_ROLE(x)                                   (BYTE)(g_pstTypeCTcpmTopInfo[x].b1DataRole)
#define SET_TCPM_DATA_ROLE(x, y)                                (g_pstTypeCTcpmTopInfo[x].b1DataRole = (y))

#define GET_TCPM_VCONN_ROLE(x)                                  (BYTE)(g_pstTypeCTcpmTopInfo[x].b1VconnRole)
#define SET_TCPM_VCONN_ROLE(x, y)                               (g_pstTypeCTcpmTopInfo[x].b1VconnRole = (y))

#define GET_TCPM_ORIENTATION(x)                                 (g_pstTypeCTcpmTopInfo[x].enumOrientation)
#define SET_TCPM_ORIENTATION(x, y)                              (g_pstTypeCTcpmTopInfo[x].enumOrientation = (y))

#define GET_TCPM_SRC_VBUS(x)                                    ((bit)(g_pstTypeCTcpmTopInfo[x].b1SrcVbus))
#define SET_TCPM_SRC_VBUS(x)                                    (g_pstTypeCTcpmTopInfo[x].b1SrcVbus = _TRUE)
#define CLR_TCPM_SRC_VBUS(x)                                    (g_pstTypeCTcpmTopInfo[x].b1SrcVbus = _FALSE)

#define GET_TCPM_SRC_VCONN(x)                                   ((bit)(g_pstTypeCTcpmTopInfo[x].b1SrcVconn))
#define SET_TCPM_SRC_VCONN(x)                                   (g_pstTypeCTcpmTopInfo[x].b1SrcVconn = _TRUE)
#define CLR_TCPM_SRC_VCONN(x)                                   (g_pstTypeCTcpmTopInfo[x].b1SrcVconn = _FALSE)

#define GET_TCPM_SNK_VBUS(x)                                    ((bit)(g_pstTypeCTcpmTopInfo[x].b1SnkVbus))
#define SET_TCPM_SNK_VBUS(x)                                    (g_pstTypeCTcpmTopInfo[x].b1SnkVbus = _TRUE)
#define CLR_TCPM_SNK_VBUS(x)                                    (g_pstTypeCTcpmTopInfo[x].b1SnkVbus = _FALSE)

//--------------------------------------------------
// TCPM CC Related MACRO
//--------------------------------------------------
#define GET_TCPM_CC_FW_STATE(x)                                 (g_pstTypeCTcpmCcInfo[x].enumTcpmCcFwState)
#define SET_TCPM_CC_FW_STATE(x, y)                              (g_pstTypeCTcpmCcInfo[x].enumTcpmCcFwState = (y))

#define GET_TCPM_CC_FSM(x)                                      (g_pstTypeCTcpmCcInfo[x].enumTcpmCcFSM)
#define SET_TCPM_CC_FSM(x, y)                                   (g_pstTypeCTcpmCcInfo[x].enumTcpmCcFSM = (y))

#define GET_TCPM_CC_CONNECT_EN(x)                               ((bit)(g_pstTypeCTcpmCcInfo[x].b1ConnectEn))
#define SET_TCPM_CC_CONNECT_EN(x)                               (g_pstTypeCTcpmCcInfo[x].b1ConnectEn = _TRUE)
#define CLR_TCPM_CC_CONNECT_EN(x)                               (g_pstTypeCTcpmCcInfo[x].b1ConnectEn = _FALSE)

#define GET_TCPM_CC_DISCHARGE_COUNT(x)                          (g_pstTypeCTcpmCcInfo[x].ucDischargeCount)
#define SET_TCPM_CC_DISCHARGE_COUNT(x, y)                       (g_pstTypeCTcpmCcInfo[x].ucDischargeCount = (y))

#define GET_TCPM_CC_PORT_ROLE(x)                                (g_pstTypeCTcpmCcInfo[x].b2PortRole)
#define SET_TCPM_CC_PORT_ROLE(x, y)                             (g_pstTypeCTcpmCcInfo[x].b2PortRole = (y))

#define GET_TCPM_CC_DRP_PREFER(x)                               (g_pstTypeCTcpmCcInfo[x].b2DrpPrefer)
#define SET_TCPM_CC_DRP_PREFER(x, y)                            (g_pstTypeCTcpmCcInfo[x].b2DrpPrefer = (y))

#define GET_TCPM_CC_RP_DEF_VALUE(x)                             (g_pstTypeCTcpmCcInfo[x].b2RpDefValue)
#define SET_TCPM_CC_RP_DEF_VALUE(x, y)                          (g_pstTypeCTcpmCcInfo[x].b2RpDefValue = (y))

#define GET_TCPM_CC_ATTACHED(x)                                 (g_pstTypeCTcpmCcInfo[x].b1CCAttached)
#define SET_TCPM_CC_ATTACHED(x)                                 (g_pstTypeCTcpmCcInfo[x].b1CCAttached = _TRUE)
#define CLR_TCPM_CC_ATTACHED(x)                                 (g_pstTypeCTcpmCcInfo[x].b1CCAttached = _FALSE)

#define GET_TCPM_CC_DEF_CUR(x)                                  ((WORD)(g_pstTypeCTcpmCcInfo[x].b10DefCurrent))
#define SET_TCPM_CC_DEF_CUR(x, y)                               (g_pstTypeCTcpmCcInfo[x].b10DefCurrent = (y))

#define GET_TCPM_CC_SRC_DET(x)                                  ((bit)(g_pstTypeCTcpmCcInfo[x].b1SourceDet))
#define SET_TCPM_CC_SRC_DET(x)                                  (g_pstTypeCTcpmCcInfo[x].b1SourceDet = _TRUE)
#define CLR_TCPM_CC_SRC_DET(x)                                  (g_pstTypeCTcpmCcInfo[x].b1SourceDet = _FALSE)

#define GET_TCPM_CC_SNK_DET_5V(x)                               ((bit)(g_pstTypeCTcpmCcInfo[x].b1SinkDet5V))
#define SET_TCPM_CC_SNK_DET_5V(x)                               (g_pstTypeCTcpmCcInfo[x].b1SinkDet5V = _TRUE)
#define CLR_TCPM_CC_SNK_DET_5V(x)                               (g_pstTypeCTcpmCcInfo[x].b1SinkDet5V = _FALSE)

#define GET_TCPM_CC_SNK_UNATTACH_DBC(x)                         ((bit)(g_pstTypeCTcpmCcInfo[x].b1SinkUnattachDbc))
#define SET_TCPM_CC_SNK_UNATTACH_DBC(x)                         (g_pstTypeCTcpmCcInfo[x].b1SinkUnattachDbc = _TRUE)
#define CLR_TCPM_CC_SNK_UNATTACH_DBC(x)                         (g_pstTypeCTcpmCcInfo[x].b1SinkUnattachDbc = _FALSE)

#define GET_TCPM_CC_SNK_DET(x)                                  ((bit)(g_pstTypeCTcpmCcInfo[x].b1SinkDet))
#define SET_TCPM_CC_SNK_DET(x)                                  (g_pstTypeCTcpmCcInfo[x].b1SinkDet = _TRUE)
#define CLR_TCPM_CC_SNK_DET(x)                                  (g_pstTypeCTcpmCcInfo[x].b1SinkDet = _FALSE)

#define GET_TCPM_CC_SRC_DET_0V(x)                               ((bit)(g_pstTypeCTcpmCcInfo[x].b1SourceDet0V))
#define SET_TCPM_CC_SRC_DET_0V(x)                               (g_pstTypeCTcpmCcInfo[x].b1SourceDet0V = _TRUE)
#define CLR_TCPM_CC_SRC_DET_0V(x)                               (g_pstTypeCTcpmCcInfo[x].b1SourceDet0V = _FALSE)

#define GET_TCPM_CC_SRC_DET_5V(x)                               ((bit)(g_pstTypeCTcpmCcInfo[x].b1SourceDet5V))
#define SET_TCPM_CC_SRC_DET_5V(x)                               (g_pstTypeCTcpmCcInfo[x].b1SourceDet5V = _TRUE)
#define CLR_TCPM_CC_SRC_DET_5V(x)                               (g_pstTypeCTcpmCcInfo[x].b1SourceDet5V = _FALSE)

#define GET_TCPM_CC_STATUS_CHG(x)                               ((bit)(g_pstTypeCTcpmCcInfo[x].b1CcStatusChange))
#define SET_TCPM_CC_STATUS_CHG(x)                               (g_pstTypeCTcpmCcInfo[x].b1CcStatusChange = _TRUE)
#define CLR_TCPM_CC_STATUS_CHG(x)                               (g_pstTypeCTcpmCcInfo[x].b1CcStatusChange = _FALSE)

#define GET_TCPM_CC_TCCDEBOUNCE(x)                              ((bit)(g_pstTypeCTcpmCcInfo[x].b1CcDebounce))
#define SET_TCPM_CC_TCCDEBOUNCE(x)                              (g_pstTypeCTcpmCcInfo[x].b1CcDebounce = _TRUE)
#define CLR_TCPM_CC_TCCDEBOUNCE(x)                              (g_pstTypeCTcpmCcInfo[x].b1CcDebounce = _FALSE)

#define GET_TCPM_CC_RA_EXIST(x)                                 ((bit)(g_pstTypeCTcpmCcInfo[x].b1RaExist))
#define SET_TCPM_CC_RA_EXIST(x)                                 (g_pstTypeCTcpmCcInfo[x].b1RaExist = _TRUE)
#define CLR_TCPM_CC_RA_EXIST(x)                                 (g_pstTypeCTcpmCcInfo[x].b1RaExist = _FALSE)

#define GET_TCPM_CC_ERROR_RECOVERY(x)                           ((bit)(g_pstTypeCTcpmCcInfo[x].b1ErrorRecovery))
#define SET_TCPM_CC_ERROR_RECOVERY(x)                           (g_pstTypeCTcpmCcInfo[x].b1ErrorRecovery = _TRUE)
#define CLR_TCPM_CC_ERROR_RECOVERY(x)                           (g_pstTypeCTcpmCcInfo[x].b1ErrorRecovery = _FALSE)

#define GET_TCPM_CC_SNK_DET_UNATTACH(x)                         ((bit)(g_pstTypeCTcpmCcInfo[x].b1SnkDetCcUnattach))
#define SET_TCPM_CC_SNK_DET_UNATTACH(x)                         (g_pstTypeCTcpmCcInfo[x].b1SnkDetCcUnattach = _TRUE)
#define CLR_TCPM_CC_SNK_DET_UNATTACH(x)                         (g_pstTypeCTcpmCcInfo[x].b1SnkDetCcUnattach = _FALSE)

#define GET_TCPM_RESET_FLAG(x)                                  ((bit)(g_pstTypeCTcpmCcInfo[x].b1ResetFlag))
#define SET_TCPM_RESET_FLAG(x)                                  (g_pstTypeCTcpmCcInfo[x].b1ResetFlag = _TRUE)
#define CLR_TCPM_RESET_FLAG(x)                                  (g_pstTypeCTcpmCcInfo[x].b1ResetFlag = _FALSE)

//--------------------------------------------------
// TCPM PD Related MACRO
//--------------------------------------------------
#define GET_TCPM_PD_FUNCTION_EN(x)                              (g_pstTypeCTcpmPdInfo[x].b1FunctionEnable)
#define SET_TCPM_PD_FUNCTION_EN(x)                              (g_pstTypeCTcpmPdInfo[x].b1FunctionEnable = _TRUE)
#define CLR_TCPM_PD_FUNCTION_EN(x)                              (g_pstTypeCTcpmPdInfo[x].b1FunctionEnable = _FALSE)

#define GET_TCPM_PD_FW_STATE(x)                                 (g_pstTypeCTcpmPdInfo[x].enumTcpmPdFwState)
#define SET_TCPM_PD_FW_STATE(x, y)                              (g_pstTypeCTcpmPdInfo[x].enumTcpmPdFwState = (y))

#define GET_TCPM_PD_SUB_STATE(x)                                (g_pstTypeCTcpmPdInfo[x].enumTcpmPdSubState)
#define SET_TCPM_PD_SUB_STATE(x, y)                             (g_pstTypeCTcpmPdInfo[x].enumTcpmPdSubState = (y))

#define GET_TCPM_PD_AMS_STATUS(x)                               (g_pstTypeCTcpmPdInfo[x].enumTcpmPdAmsStatus)
#define SET_TCPM_PD_AMS_STATUS(x, y)                            (g_pstTypeCTcpmPdInfo[x].enumTcpmPdAmsStatus = (y))

#define GET_TCPM_PD_CBL_STATE(x)                                (g_pstTypeCTcpmPdInfo[x].enumTcpmPdCableState)
#define SET_TCPM_PD_CBL_STATE(x, y)                             (g_pstTypeCTcpmPdInfo[x].enumTcpmPdCableState = (y))

#define GET_TCPM_PD_DP_ALT_STATE(x)                             (g_pstTypeCTcpmPdInfo[x].enumTcpmAltModeState)
#define SET_TCPM_PD_DP_ALT_STATE(x, y)                          (g_pstTypeCTcpmPdInfo[x].enumTcpmAltModeState = (y))

#define GET_TCPM_PD_SPEC_VER(x)                                 ((BYTE)g_pstTypeCTcpmPdInfo[x].b2SpecVersion)
#define SET_TCPM_PD_SPEC_VER(x, y)                              (g_pstTypeCTcpmPdInfo[x].b2SpecVersion = (y))

#define GET_TCPM_PD_EXPLICIT_CONTRACT(x)                        (g_pstTypeCTcpmPdInfo[x].b1PDPowerContract)
#define SET_TCPM_PD_EXPLICIT_CONTRACT(x)                        (g_pstTypeCTcpmPdInfo[x].b1PDPowerContract = _TRUE)
#define CLR_TCPM_PD_EXPLICIT_CONTRACT(x)                        (g_pstTypeCTcpmPdInfo[x].b1PDPowerContract = _FALSE)

#define GET_TCPM_PD_UNCONSTRAIN_POWER(x)                        (g_pstTypeCTcpmPdInfo[x].b1UnconstrainedPower)
#define SET_TCPM_PD_UNCONSTRAIN_POWER(x, y)                     (g_pstTypeCTcpmPdInfo[x].b1UnconstrainedPower = (y))

// Counter Control Macro
#define GET_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(x)           (g_pstTypeCTcpmPdInfo[x].b5DiscoverIdRetryFailCnt)
#define ADD_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(x)           (g_pstTypeCTcpmPdInfo[x].b5DiscoverIdRetryFailCnt += 1)
#define CLR_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(x)           (g_pstTypeCTcpmPdInfo[x].b5DiscoverIdRetryFailCnt = 0)

#define GET_TCPM_PD_SRC_CAP_CNT(x)                              (g_pstTypeCTcpmPdInfo[x].b6SrcCapCnt)
#define ADD_TCPM_PD_SRC_CAP_CNT(x)                              (g_pstTypeCTcpmPdInfo[x].b6SrcCapCnt += 1)
#define CLR_TCPM_PD_SRC_CAP_CNT(x)                              (g_pstTypeCTcpmPdInfo[x].b6SrcCapCnt = 0)

#define GET_TCPM_PD_HARD_RST_CNT(x)                             (g_pstTypeCTcpmPdInfo[x].b2HardRstCnt)
#define ADD_TCPM_PD_HARD_RST_CNT(x)                             (g_pstTypeCTcpmPdInfo[x].b2HardRstCnt += 1)
#define CLR_TCPM_PD_HARD_RST_CNT(x)                             (g_pstTypeCTcpmPdInfo[x].b2HardRstCnt = 0)

#define GET_TCPM_PD_CHECK_VBUS_CNT(x)                           (g_pstTypeCTcpmPdInfo[x].b4CheckVbusCnt)
#define ADD_TCPM_PD_CHECK_VBUS_CNT(x)                           (g_pstTypeCTcpmPdInfo[x].b4CheckVbusCnt += 1)
#define CLR_TCPM_PD_CHECK_VBUS_CNT(x)                           (g_pstTypeCTcpmPdInfo[x].b4CheckVbusCnt = 0)

// WD Timer Related Macros
#define GET_TCPM_WD_TIME_LEFT(x)                                (g_pstTypeCTcpmPdInfo[x].b10WDTimeLeft)
#define SET_TCPM_WD_TIME_LEFT(x, y)                             (g_pstTypeCTcpmPdInfo[x].b10WDTimeLeft = (y))

#define GET_TCPM_WD_EVENT_TRIGGERED(x)                          (g_pstTypeCTcpmPdInfo[x].b1WDEventTriggered)
#define SET_TCPM_WD_EVENT_TRIGGERED(x)                          (g_pstTypeCTcpmPdInfo[x].b1WDEventTriggered = _TRUE)
#define CLR_TCPM_WD_EVENT_TRIGGERED(x)                          (g_pstTypeCTcpmPdInfo[x].b1WDEventTriggered = _FALSE)

// BIST Mode Macro
#define GET_TCPM_PD_BIST_MODE(x)                                (g_pstTypeCTcpmPdInfo[x].b4BistMode)
#define SET_TCPM_PD_BIST_MODE(x, y)                             (g_pstTypeCTcpmPdInfo[x].b4BistMode = (y))

// FW Flow Control Macro
#define GET_TCPM_PD_PRS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDPRSwapReject)
#define SET_TCPM_PD_PRS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDPRSwapReject = _TRUE)
#define CLR_TCPM_PD_PRS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDPRSwapReject = _FALSE)

#define GET_TCPM_PD_DRS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDDRSwapReject)
#define SET_TCPM_PD_DRS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDDRSwapReject = _TRUE)
#define CLR_TCPM_PD_DRS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDDRSwapReject = _FALSE)

#define GET_TCPM_PD_VCS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDVconnSwapReject)
#define SET_TCPM_PD_VCS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDVconnSwapReject = _TRUE)
#define CLR_TCPM_PD_VCS_REJECT(x)                               (g_pstTypeCTcpmPdInfo[x].b1PDVconnSwapReject = _FALSE)

#define GET_TCPM_PD_GET_SNK_CAP_SENT(x)                         (g_pstTypeCTcpmPdInfo[x].b1GetSnkCapSent)
#define SET_TCPM_PD_GET_SNK_CAP_SENT(x)                         (g_pstTypeCTcpmPdInfo[x].b1GetSnkCapSent = _TRUE)
#define CLR_TCPM_PD_GET_SNK_CAP_SENT(x)                         (g_pstTypeCTcpmPdInfo[x].b1GetSnkCapSent = _FALSE)

#define GET_TCPM_PD_GET_SRC_CAP_SENT(x)                         (g_pstTypeCTcpmPdInfo[x].b1GetSrcCapSent)
#define SET_TCPM_PD_GET_SRC_CAP_SENT(x)                         (g_pstTypeCTcpmPdInfo[x].b1GetSrcCapSent = _TRUE)
#define CLR_TCPM_PD_GET_SRC_CAP_SENT(x)                         (g_pstTypeCTcpmPdInfo[x].b1GetSrcCapSent = _FALSE)

#define GET_TCPM_PD_RCV_SNK_CAP(x)                              (g_pstTypeCTcpmPdInfo[x].b1RcvSnkCap)
#define SET_TCPM_PD_RCV_SNK_CAP(x)                              (g_pstTypeCTcpmPdInfo[x].b1RcvSnkCap = _TRUE)
#define CLR_TCPM_PD_RCV_SNK_CAP(x)                              (g_pstTypeCTcpmPdInfo[x].b1RcvSnkCap = _FALSE)

#define GET_TCPM_PD_RCV_SRC_CAP(x)                              (g_pstTypeCTcpmPdInfo[x].b1RcvSrcCap)
#define SET_TCPM_PD_RCV_SRC_CAP(x)                              (g_pstTypeCTcpmPdInfo[x].b1RcvSrcCap = _TRUE)
#define CLR_TCPM_PD_RCV_SRC_CAP(x)                              (g_pstTypeCTcpmPdInfo[x].b1RcvSrcCap = _FALSE)

#define GET_TCPM_PD_HRST_PWR_OFF(x)                             (g_pstTypeCTcpmPdInfo[x].b1HRST_Pwr_Off)
#define SET_TCPM_PD_HRST_PWR_OFF(x)                             (g_pstTypeCTcpmPdInfo[x].b1HRST_Pwr_Off = _TRUE)
#define CLR_TCPM_PD_HRST_PWR_OFF(x)                             (g_pstTypeCTcpmPdInfo[x].b1HRST_Pwr_Off = _FALSE)

#define GET_TCPM_PD_REQ_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1ReqWait)
#define SET_TCPM_PD_REQ_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1ReqWait = _TRUE)
#define CLR_TCPM_PD_REQ_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1ReqWait = _FALSE)

#define GET_TCPM_PD_PRS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1PRSwapWait)
#define SET_TCPM_PD_PRS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1PRSwapWait = _TRUE)
#define CLR_TCPM_PD_PRS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1PRSwapWait = _FALSE)

#define GET_TCPM_PD_DRS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1DRSwapWait)
#define SET_TCPM_PD_DRS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1DRSwapWait = _TRUE)
#define CLR_TCPM_PD_DRS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1DRSwapWait = _FALSE)

#define GET_TCPM_PD_VCS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1VCSwapWait)
#define SET_TCPM_PD_VCS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1VCSwapWait = _TRUE)
#define CLR_TCPM_PD_VCS_WAIT_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1VCSwapWait = _FALSE)

#define GET_TCPM_PD_VDMMSG_WAIT_FLAG(x)                         (g_pstTypeCTcpmPdInfo[x].b1VdmMsgWait)
#define SET_TCPM_PD_VDMMSG_WAIT_FLAG(x)                         (g_pstTypeCTcpmPdInfo[x].b1VdmMsgWait = _TRUE)
#define CLR_TCPM_PD_VDMMSG_WAIT_FLAG(x)                         (g_pstTypeCTcpmPdInfo[x].b1VdmMsgWait = _FALSE)

#define GET_TCPM_PD_VDM_BUSY_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1VdmBusy)
#define SET_TCPM_PD_VDM_BUSY_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1VdmBusy = _TRUE)
#define CLR_TCPM_PD_VDM_BUSY_FLAG(x)                            (g_pstTypeCTcpmPdInfo[x].b1VdmBusy = _FALSE)

#define GET_TCPM_PD_PRS_PROCESSING(x)                           (g_pstTypeCTcpmPdInfo[x].b1PRS_Processing)
#define SET_TCPM_PD_PRS_PROCESSING(x)                           (g_pstTypeCTcpmPdInfo[x].b1PRS_Processing = _TRUE)
#define CLR_TCPM_PD_PRS_PROCESSING(x)                           (g_pstTypeCTcpmPdInfo[x].b1PRS_Processing = _FALSE)

#define GET_TCPM_PD_INTEROP_S8(x)                               (g_pstTypeCTcpmPdInfo[x].b1InteropS8)
#define SET_TCPM_PD_INTEROP_S8(x)                               (g_pstTypeCTcpmPdInfo[x].b1InteropS8 = _TRUE)
#define CLR_TCPM_PD_INTEROP_S8(x)                               (g_pstTypeCTcpmPdInfo[x].b1InteropS8 = _FALSE)

#define GET_TCPM_PD_ALERT_SENT(x)                               (g_pstTypeCTcpmPdInfo[x].b1AlertSent)
#define SET_TCPM_PD_ALERT_SENT(x)                               (g_pstTypeCTcpmPdInfo[x].b1AlertSent = _TRUE)
#define CLR_TCPM_PD_ALERT_SENT(x)                               (g_pstTypeCTcpmPdInfo[x].b1AlertSent = _FALSE)

#define GET_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(x)                    (g_pstTypeCTcpmPdInfo[x].b1GetSnkCapWait)
#define SET_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(x)                    (g_pstTypeCTcpmPdInfo[x].b1GetSnkCapWait = _TRUE)
#define CLR_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(x)                    (g_pstTypeCTcpmPdInfo[x].b1GetSnkCapWait = _FALSE)

// PD EXINT Set Timer Event Macro
#define GET_TCPM_PD_TIMER_EVENT_VALID(x)                        (g_pstTypeCTcpmPdInfo[x].b1Valid)
#define SET_TCPM_PD_TIMER_EVENT_VALID(x)                        (g_pstTypeCTcpmPdInfo[x].b1Valid = _TRUE)
#define CLR_TCPM_PD_TIMER_EVENT_VALID(x)                        (g_pstTypeCTcpmPdInfo[x].b1Valid = _FALSE)

#define GET_TCPM_PD_TIMER_EVENT_ID(x)                           (g_pstTypeCTcpmPdInfo[x].enumEventID)
#define SET_TCPM_PD_TIMER_EVENT_ID(x, y)                        (g_pstTypeCTcpmPdInfo[x].enumEventID = (y))

#define GET_TCPM_PD_TIMER_EVENT_CNT(x)                          (g_pstTypeCTcpmPdInfo[x].usEventTime)
#define SET_TCPM_PD_TIMER_EVENT_CNT(x, y)                       (g_pstTypeCTcpmPdInfo[x].usEventTime = (y))

// WD Timer Event Macro
#define GET_TCPM_PD_WD_TIMER_EVENT_VALID(x)                     (g_pstTypeCTcpmPdInfo[x].b1WDEventValid)
#define SET_TCPM_PD_WD_TIMER_EVENT_VALID(x)                     (g_pstTypeCTcpmPdInfo[x].b1WDEventValid = _TRUE)
#define CLR_TCPM_PD_WD_TIMER_EVENT_VALID(x)                     (g_pstTypeCTcpmPdInfo[x].b1WDEventValid = _FALSE)

#define GET_TCPM_PD_WD_TIMER_EVENT_ID(x)                        (g_pstTypeCTcpmPdInfo[x].enumWDEventID)
#define SET_TCPM_PD_WD_TIMER_EVENT_ID(x, y)                     (g_pstTypeCTcpmPdInfo[x].enumWDEventID = (y))

#define GET_TCPM_PD_WD_TIMER_EVENT_CNT(x)                       (g_pstTypeCTcpmPdInfo[x].usWDEventTime)
#define SET_TCPM_PD_WD_TIMER_EVENT_CNT(x, y)                    (g_pstTypeCTcpmPdInfo[x].usWDEventTime = (y))

// Source Capability Macros
#define GET_TCPM_PD_SPR_SRC_PDO_CNT(x)                          ((BYTE)g_pstTypeCTcpmPdInfo[x].b3PDNumOfSPRSrcCap)
#define SET_TCPM_PD_SPR_SRC_PDO_CNT(x, y)                       (g_pstTypeCTcpmPdInfo[x].b3PDNumOfSPRSrcCap = (y))

#define GET_TCPM_PD_EPR_SRC_PDO_CNT(x)                          ((BYTE)g_pstTypeCTcpmPdInfo[x].b3PDNumOfEPRSrcCap)
#define SET_TCPM_PD_EPR_SRC_PDO_CNT(x, y)                       (g_pstTypeCTcpmPdInfo[x].b3PDNumOfEPRSrcCap = (y))

#define GET_TCPM_PD_SRC_PDO_TYPE(x, y)                          (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].enumPdoType)
#define SET_TCPM_PD_SRC_PDO_TYPE(x, y, z)                       (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].enumPdoType = (z))

#define GET_TCPM_PD_SRC_CAP_VOL_MAX(x, y)                       (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].usMaxVoltage)
#define SET_TCPM_PD_SRC_CAP_VOL_MAX(x, y, z)                    (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].usMaxVoltage = (z))

#define GET_TCPM_PD_SRC_CAP_VOL_MIN(x, y)                       (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].usMinVoltage)
#define SET_TCPM_PD_SRC_CAP_VOL_MIN(x, y, z)                    (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].usMinVoltage = (z))

#define GET_TCPM_PD_SRC_CAP_CUR(x, y)                           ((WORD)(g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].b10MaxCurrent))
#define SET_TCPM_PD_SRC_CAP_CUR(x, y, z)                        (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].b10MaxCurrent = (z))

#define GET_TCPM_PD_SRC_CAP_PEAK(x, y)                          (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].b2PeakCurrent)
#define SET_TCPM_PD_SRC_CAP_PEAK(x, y, z)                       (g_pstTypeCTcpmPdInfo[x].pstSrcPDO[y].b2PeakCurrent = (z))

// Sink Capability Macros
#define GET_TCPM_PD_SPR_SNK_PDO_CNT(x)                          ((BYTE)g_pstTypeCTcpmPdInfo[x].b3PDNumOfSPRSnkCap)
#define SET_TCPM_PD_SPR_SNK_PDO_CNT(x, y)                       (g_pstTypeCTcpmPdInfo[x].b3PDNumOfSPRSnkCap = (y))

#define GET_TCPM_PD_EPR_SNK_PDO_CNT(x)                          ((BYTE)g_pstTypeCTcpmPdInfo[x].b3PDNumOfEPRSnkCap)
#define SET_TCPM_PD_EPR_SNK_PDO_CNT(x, y)                       (g_pstTypeCTcpmPdInfo[x].b3PDNumOfEPRSnkCap = (y))

#define GET_TCPM_PD_SNK_PDO_TYPE(x, y)                          (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].enumPdoType)
#define SET_TCPM_PD_SNK_PDO_TYPE(x, y, z)                       (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].enumPdoType = (z))

#define GET_TCPM_PD_SNK_CAP_VOL_MAX(x, y)                       (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].usMaxVoltage)
#define SET_TCPM_PD_SNK_CAP_VOL_MAX(x, y, z)                    (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].usMaxVoltage = (z))

#define GET_TCPM_PD_SNK_CAP_VOL_MIN(x, y)                       (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].usMinVoltage)
#define SET_TCPM_PD_SNK_CAP_VOL_MIN(x, y, z)                    (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].usMinVoltage = (z))

#define GET_TCPM_PD_SNK_CAP_CUR(x, y)                           ((WORD)(g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].b10MaxCurrent))
#define SET_TCPM_PD_SNK_CAP_CUR(x, y, z)                        (g_pstTypeCTcpmPdInfo[x].pstSnkPDO[y].b10MaxCurrent = (z))

// Sink Capability Extended Macros
#define GET_TCPM_PD_SNK_MIN_PDP(x)                              (g_pstTypeCTcpmPdInfo[x].stSnkInfo.usSnkMinPDP)
#define SET_TCPM_PD_SNK_MIN_PDP(x, y)                           (g_pstTypeCTcpmPdInfo[x].stSnkInfo.usSnkMinPDP = (y))

#define GET_TCPM_PD_SNK_OPERATIONAL_PDP(x)                      (g_pstTypeCTcpmPdInfo[x].stSnkInfo.usSnkOpePDP)
#define SET_TCPM_PD_SNK_OPERATIONAL_PDP(x, y)                   (g_pstTypeCTcpmPdInfo[x].stSnkInfo.usSnkOpePDP = (y))

#define GET_TCPM_PD_SNK_MAX_PDP(x)                              (g_pstTypeCTcpmPdInfo[x].stSnkInfo.usSnkMaxPDP)
#define SET_TCPM_PD_SNK_MAX_PDP(x, y)                           (g_pstTypeCTcpmPdInfo[x].stSnkInfo.usSnkMaxPDP = (y))

// Request Macros
#define GET_TCPM_PD_REQ_TYPE(x)                                 (g_pstTypeCTcpmPdInfo[x].enumReqType)
#define SET_TCPM_PD_REQ_TYPE(x, y)                              (g_pstTypeCTcpmPdInfo[x].enumReqType = (y))

#define GET_TCPM_PD_INIT_REQ_TARGET_VOL(x)                      (g_pstTypeCTcpmPdInfo[x].ucTargetVolRDO)
#define SET_TCPM_PD_INIT_REQ_TARGET_VOL(x, y)                   (g_pstTypeCTcpmPdInfo[x].ucTargetVolRDO = (y))

#define GET_TCPM_PD_REQ_OBJ_POS(x)                              ((BYTE)(g_pstTypeCTcpmPdInfo[x].stRDO.enumObjPos))
#define SET_TCPM_PD_REQ_OBJ_POS(x, y)                           (g_pstTypeCTcpmPdInfo[x].stRDO.enumObjPos = (y))

#define GET_TCPM_PD_REQ_CAP_MIS(x)                              ((BYTE)(g_pstTypeCTcpmPdInfo[x].stRDO.b1CapMismatch))
#define SET_TCPM_PD_REQ_CAP_MIS(x, y)                           (g_pstTypeCTcpmPdInfo[x].stRDO.b1CapMismatch = (y))

#define GET_TCPM_PD_REQ_GIVE_BACK(x)                            ((BYTE)(g_pstTypeCTcpmPdInfo[x].stRDO.b1GiveBack))
#define SET_TCPM_PD_REQ_GIVE_BACK(x, y)                         (g_pstTypeCTcpmPdInfo[x].stRDO.b1GiveBack = (y))

#define GET_TCPM_PD_REQ_INFO_1(x)                               ((WORD)(g_pstTypeCTcpmPdInfo[x].stRDO.usReqInfo1))
#define SET_TCPM_PD_REQ_INFO_1(x, y)                            (g_pstTypeCTcpmPdInfo[x].stRDO.usReqInfo1 = (y))

#define GET_TCPM_PD_REQ_INFO_2(x)                               ((WORD)(g_pstTypeCTcpmPdInfo[x].stRDO.usReqInfo2))
#define SET_TCPM_PD_REQ_INFO_2(x, y)                            (g_pstTypeCTcpmPdInfo[x].stRDO.usReqInfo2 = (y))

// Power Contract Negotiated Power Status For User
#define GET_TCPM_PD_PDO_STATUS_VOL(x)                           (g_pstTypeCTcpmPdInfo[x].stPDOStatus.usVoltage)
#define SET_TCPM_PD_PDO_STATUS_VOL(x, y)                        (g_pstTypeCTcpmPdInfo[x].stPDOStatus.usVoltage = (y))

#define GET_TCPM_PD_PDO_STATUS_CUR(x)                           (g_pstTypeCTcpmPdInfo[x].stPDOStatus.usCurrent)
#define SET_TCPM_PD_PDO_STATUS_CUR(x, y)                        (g_pstTypeCTcpmPdInfo[x].stPDOStatus.usCurrent = (y))

#define GET_TCPM_PD_PDO_STATUS_OBJ_POS(x)                       (g_pstTypeCTcpmPdInfo[x].stPDOStatus.b4ObjPos)
#define SET_TCPM_PD_PDO_STATUS_OBJ_POS(x, y)                    (g_pstTypeCTcpmPdInfo[x].stPDOStatus.b4ObjPos = (y))
#define CLR_TCPM_PD_PDO_STATUS_OBJ_POS(x)                       (g_pstTypeCTcpmPdInfo[x].stPDOStatus.b4ObjPos = 0)

// PPS Macro
#define GET_TCPM_PD_PPS_SUPPORT(x)                              (g_pstTypeCTcpmPdInfo[x].b1PPSSupport)
#define SET_TCPM_PD_PPS_SUPPORT(x, y)                           (g_pstTypeCTcpmPdInfo[x].b1PPSSupport = (y))

// PD Behavior Type Macro
#define GET_TCPM_PD_BEHAVIOR_TYPE(x)                            ((BYTE)(g_pstTypeCTcpmPdInfo[x].b2cBehaviorType))
#define SET_TCPM_PD_BEHAVIOR_TYPE(x, y)                         (g_pstTypeCTcpmPdInfo[x].b2cBehaviorType = (y))

// PD Power Role Options Macros
#define GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(x)                   (g_pstTypeCTcpmPdInfo[x].b1SrcAcceptSwapToSnk)
#define SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(x, y)                (g_pstTypeCTcpmPdInfo[x].b1SrcAcceptSwapToSnk = (y))

#define GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(x)                  (g_pstTypeCTcpmPdInfo[x].b1SrcRequestSwapToSnk)
#define SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(x, y)               (g_pstTypeCTcpmPdInfo[x].b1SrcRequestSwapToSnk = (y))

#define GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(x)                   (g_pstTypeCTcpmPdInfo[x].b1SnkAcceptSwapToSrc)
#define SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(x, y)                (g_pstTypeCTcpmPdInfo[x].b1SnkAcceptSwapToSrc = (y))

#define GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(x)                  (g_pstTypeCTcpmPdInfo[x].b1SnkRequestSwapToSrc)
#define SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(x, y)               (g_pstTypeCTcpmPdInfo[x].b1SnkRequestSwapToSrc = (y))

// PD Data Role Options Macros
#define GET_TCPM_PD_DFP_SWAP_TO_UFP(x)                          (g_pstTypeCTcpmPdInfo[x].b1DfpSwapToUfp)
#define SET_TCPM_PD_DFP_SWAP_TO_UFP(x, y)                       (g_pstTypeCTcpmPdInfo[x].b1DfpSwapToUfp = (y))

#define GET_TCPM_PD_UFP_SWAP_TO_DFP(x)                          (g_pstTypeCTcpmPdInfo[x].b1UfpSwapToDfp)
#define SET_TCPM_PD_UFP_SWAP_TO_DFP(x, y)                       (g_pstTypeCTcpmPdInfo[x].b1UfpSwapToDfp = (y))

// EPR Mode Macros
#define GET_TCPM_PD_ENTER_EPR_MODE_FLOW(x)                      (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EnterEPRFlow)
#define SET_TCPM_PD_ENTER_EPR_MODE_FLOW(x)                      (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EnterEPRFlow = _TRUE)
#define CLR_TCPM_PD_ENTER_EPR_MODE_FLOW(x)                      (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EnterEPRFlow = _FALSE)

#define GET_TCPM_PD_EPR_MODE(x)                                 (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EPRMode)
#define SET_TCPM_PD_EPR_MODE(x)                                 (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EPRMode = _TRUE)
#define CLR_TCPM_PD_EPR_MODE(x)                                 (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EPRMode = _FALSE)

#define GET_TCPM_PD_EPR_MODE_ACTION(x)                          (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.enumPDEPRModeAction)
#define SET_TCPM_PD_EPR_MODE_ACTION(x, y)                       (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.enumPDEPRModeAction = (y))

#define GET_TCPM_PD_ENTER_EPR_FAILED_REASON(x)                  (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.enumPDEnterEPRFailedReason)
#define SET_TCPM_PD_ENTER_EPR_FAILED_REASON(x, y)               (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.enumPDEnterEPRFailedReason = (y))

#define GET_TCPM_PD_EXT_CTRL_TYPE(x)                            (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.enumPDExtCtrlType)
#define SET_TCPM_PD_EXT_CTRL_TYPE(x, y)                         (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.enumPDExtCtrlType = (y))

#define GET_TCPM_PD_EPR_SRC_CAPABLE(x)                          (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EPRSRCCapable)
#define SET_TCPM_PD_EPR_SRC_CAPABLE(x, y)                       (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.b1EPRSRCCapable = (y))

#define GET_TCPM_PD_PARTNER_EPR_SINK_PDP(x)                     (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.ucPartnerEPRSinkPDP)
#define SET_TCPM_PD_PARTNER_EPR_SINK_PDP(x, y)                  (g_pstTypeCTcpmPdInfo[x].stEprModeInfo.ucPartnerEPRSinkPDP = (y))

// System Request Event Macros
#define GET_TCPM_PD_SYS_EVENT(x)                                (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumSystemEvent)
#define SET_TCPM_PD_SYS_EVENT(x, y)                             (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumSystemEvent = (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumSystemEvent | (y)))
#define CLR_TCPM_PD_SYS_EVENT(x, y)                             (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumSystemEvent = (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumSystemEvent & (EnumTypeCPDSysEvent)(~(y))))

// Port Controller Event Macros
#define GET_TCPM_PD_PORT_CTRL_EVENT(x)                          (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumPortCtrlEvent)
#define SET_TCPM_PD_PORT_CTRL_EVENT(x, y)                       (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumPortCtrlEvent = (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumPortCtrlEvent | (y)))
#define CLR_TCPM_PD_PORT_CTRL_EVENT(x, y)                       (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumPortCtrlEvent = (g_pstTypeCTcpmPdInfo[x].stPdEvent.enumPortCtrlEvent & (EnumTypeCPDPortCtrlEvent)(~(y))))

// Status Message Macros
#define GET_TCPM_PD_NEW_POWER_STATE(x)                          (g_pstTypeCTcpmPdStatusEvent[x].b3NewPowerState)
#define SET_TCPM_PD_NEW_POWER_STATE(x, y)                       (g_pstTypeCTcpmPdStatusEvent[x].b3NewPowerState = (y))

#define GET_TCPM_PD_NEW_POWER_INDICATOR(x)                      (g_pstTypeCTcpmPdStatusEvent[x].b3NewPSIndicator)
#define SET_TCPM_PD_NEW_POWER_INDICATOR(x, y)                   (g_pstTypeCTcpmPdStatusEvent[x].b3NewPSIndicator = (y))

// Alert Message Macros
#define GET_TCPM_PD_TYPE_OF_ALERT(x)                            (g_pstTypeCTcpmPdAlertEvent[x].enumTypeOfAlert)
#define SET_TCPM_PD_TYPE_OF_ALERT(x, y)                         (g_pstTypeCTcpmPdAlertEvent[x].enumTypeOfAlert = (g_pstTypeCTcpmPdAlertEvent[x].enumTypeOfAlert | (y)))
#define CLR_TCPM_PD_TYPE_OF_ALERT(x, y)                         (g_pstTypeCTcpmPdAlertEvent[x].enumTypeOfAlert = (g_pstTypeCTcpmPdAlertEvent[x].enumTypeOfAlert & (EnumTypeCTypeOfAlert)(~(y))))

#define GET_TCPM_PD_BAT_STATUS(x)                               (g_pstTypeCTcpmPdAlertEvent[x].enumBatStatus)
#define SET_TCPM_PD_BAT_STATUS(x, y)                            (g_pstTypeCTcpmPdAlertEvent[x].enumBatStatus = (g_pstTypeCTcpmPdAlertEvent[x].enumBatStatus | (y)))
#define CLR_TCPM_PD_BAT_STATUS(x, y)                            (g_pstTypeCTcpmPdAlertEvent[x].enumBatStatus = (g_pstTypeCTcpmPdAlertEvent[x].enumBatStatus & (EnumTypeCBatteryStatus)(~(y))))

#define GET_TCPM_PD_EXT_ALERT_EVENT(x)                          (g_pstTypeCTcpmPdAlertEvent[x].enumExtAlertEvent)
#define SET_TCPM_PD_EXT_ALERT_EVENT(x, y)                       (g_pstTypeCTcpmPdAlertEvent[x].enumExtAlertEvent = (y))

//--------------------------------------------------
// PD Partner Info Related MACRO
//--------------------------------------------------
// Port Partner(Other Side) General Info Setting Macros
#define GET_TCPM_PD_PARTNER_DRP(x)                              (g_pstTypeCTcpmPdPartnerInfo[x].b1DualRolePower)
#define SET_TCPM_PD_PARTNER_DRP(x, y)                           (g_pstTypeCTcpmPdPartnerInfo[x].b1DualRolePower = (y))
#define CLR_TCPM_PD_PARTNER_DRP(x)                              (g_pstTypeCTcpmPdPartnerInfo[x].b1DualRolePower = _FALSE)

#define GET_TCPM_PD_PARTNER_DRD(x)                              (g_pstTypeCTcpmPdPartnerInfo[x].b1DualRoleData)
#define SET_TCPM_PD_PARTNER_DRD(x, y)                           (g_pstTypeCTcpmPdPartnerInfo[x].b1DualRoleData = (y))
#define CLR_TCPM_PD_PARTNER_DRD(x)                              (g_pstTypeCTcpmPdPartnerInfo[x].b1DualRoleData = _FALSE)

#define GET_TCPM_PD_PARTNER_SUSPEND(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1SuspendSupport)
#define SET_TCPM_PD_PARTNER_SUSPEND(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].b1SuspendSupport = (y))
#define CLR_TCPM_PD_PARTNER_SUSPEND(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1SuspendSupport = _FALSE)

#define GET_TCPM_PD_PARTNER_EXT_PWR(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1ExtPower)
#define SET_TCPM_PD_PARTNER_EXT_PWR(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].b1ExtPower = (y))
#define CLR_TCPM_PD_PARTNER_EXT_PWR(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1ExtPower = _FALSE)

#define GET_TCPM_PD_PARTNER_USB_CAP(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1UsbCapable)
#define SET_TCPM_PD_PARTNER_USB_CAP(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].b1UsbCapable = (y))
#define CLR_TCPM_PD_PARTNER_USB_CAP(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1UsbCapable = _FALSE)

#define GET_TCPM_PD_PARTNER_UNCHK(x)                            (g_pstTypeCTcpmPdPartnerInfo[x].b1UnchkSupport)
#define SET_TCPM_PD_PARTNER_UNCHK(x, y)                         (g_pstTypeCTcpmPdPartnerInfo[x].b1UnchkSupport = (y))
#define CLR_TCPM_PD_PARTNER_UNCHK(x)                            (g_pstTypeCTcpmPdPartnerInfo[x].b1UnchkSupport = _FALSE)

#define GET_TCPM_PD_PARTNER_EPR_CAP(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b1PartnerEPRCapable)
#define SET_TCPM_PD_PARTNER_EPR_CAP(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].b1PartnerEPRCapable = (y))

#define GET_TCPM_PD_PARTNER_ALT_SUPPORT(x)                      (g_pstTypeCTcpmPdPartnerInfo[x].b1ALTSupport)
#define SET_TCPM_PD_PARTNER_ALT_SUPPORT(x)                      (g_pstTypeCTcpmPdPartnerInfo[x].b1ALTSupport = _TRUE)
#define CLR_TCPM_PD_PARTNER_ALT_SUPPORT(x)                      (g_pstTypeCTcpmPdPartnerInfo[x].b1ALTSupport = _FALSE)

#define GET_TCPM_PD_PARTNER_HIGH_CAP(x)                         (g_pstTypeCTcpmPdPartnerInfo[x].b1HigherCap)
#define SET_TCPM_PD_PARTNER_HIGH_CAP(x, y)                      (g_pstTypeCTcpmPdPartnerInfo[x].b1HigherCap = (y))
#define CLR_TCPM_PD_PARTNER_HIGH_CAP(x)                         (g_pstTypeCTcpmPdPartnerInfo[x].b1HigherCap = _FALSE)

#define GET_TCPM_PD_PARTNER_FRS_CUR(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b2FrsCurrent)
#define SET_TCPM_PD_PARTNER_FRS_CUR(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].b2FrsCurrent = (y))
#define CLR_TCPM_PD_PARTNER_FRS_CUR(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].b2FrsCurrent = 0)


// Port Partner(Other Side) Source Cap Info Setting Macros
#define GET_TCPM_PD_PARTNER_SRC_CAP_CNT(x)                      (g_pstTypeCTcpmPdPartnerInfo[x].b3NumOfSrcCap)
#define SET_TCPM_PD_PARTNER_SRC_CAP_CNT(x, y)                   (g_pstTypeCTcpmPdPartnerInfo[x].b3NumOfSrcCap = (y))

#define GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(x, y)                  (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].enumPdoType)
#define SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(x, y, z)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].enumPdoType = (z))

#define GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(x, y)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].usMaxVoltage)
#define SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(x, y, z)            (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].usMaxVoltage = (z))

#define GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(x, y)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].usMinVoltage)
#define SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(x, y, z)            (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].usMinVoltage = (z))

#define GET_TCPM_PD_PARTNER_SRC_CAP_CUR(x, y)                   ((WORD)(g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].b10MaxCurrent))
#define SET_TCPM_PD_PARTNER_SRC_CAP_CUR(x, y, z)                (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].b10MaxCurrent = (z))

#define GET_TCPM_PD_PARTNER_SRC_PEAK_CUR(x, y)                  (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].b2PeakCurrent)
#define SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(x, y, z)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSrcPDO[y].b2PeakCurrent = (z))

#define GET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(x)             (g_pstTypeCTcpmPdPartnerInfo[x].enumSrcCapValid)
#define SET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(x, y)          (g_pstTypeCTcpmPdPartnerInfo[x].enumSrcCapValid = (y))

// Port Partner(Other Side) Sink Cap Info Setting Macros
#define GET_TCPM_PD_PARTNER_SNK_CAP_CNT(x)                      (g_pstTypeCTcpmPdPartnerInfo[x].b3NumOfSnkCap)
#define SET_TCPM_PD_PARTNER_SNK_CAP_CNT(x, y)                   (g_pstTypeCTcpmPdPartnerInfo[x].b3NumOfSnkCap = (y))

#define GET_TCPM_PD_PARTNER_SVDM_VERSION(x)                     (g_pstTypeCTcpmPdPartnerInfo[x].enumSvdmVersion)
#define SET_TCPM_PD_PARTNER_SVDM_VERSION(x, y)                  (g_pstTypeCTcpmPdPartnerInfo[x].enumSvdmVersion = (y))

#define GET_TCPM_PD_PARTNER_DPAM_VERSION(x)                     (g_pstTypeCTcpmPdPartnerInfo[x].enumDpamVersion)
#define SET_TCPM_PD_PARTNER_DPAM_VERSION(x, y)                  (g_pstTypeCTcpmPdPartnerInfo[x].enumDpamVersion = (y))

#define GET_TCPM_PD_PARTNER_SNK_CAP_TYPE(x, y)                  (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].enumPdoType)
#define SET_TCPM_PD_PARTNER_SNK_CAP_TYPE(x, y, z)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].enumPdoType = (z))

#define GET_TCPM_PD_PARTNER_SNK_CAP_VOL_MAX(x, y)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].usMaxVoltage)
#define SET_TCPM_PD_PARTNER_SNK_CAP_VOL_MAX(x, y, z)            (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].usMaxVoltage = (z))

#define GET_TCPM_PD_PARTNER_SNK_CAP_VOL_MIN(x, y)               (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].usMinVoltage)
#define SET_TCPM_PD_PARTNER_SNK_CAP_VOL_MIN(x, y, z)            (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].usMinVoltage = (z))

#define GET_TCPM_PD_PARTNER_SNK_CAP_CUR(x, y)                   (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].b10MaxCurrent)
#define SET_TCPM_PD_PARTNER_SNK_CAP_CUR(x, y, z)                (g_pstTypeCTcpmPdPartnerInfo[x].pstSnkPDO[y].b10MaxCurrent = (z))

// Port Partner(Other Side) Request Info Setting Macros
#define GET_TCPM_PD_PARTNER_OBJ_POS(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b4ObjPos)
#define SET_TCPM_PD_PARTNER_OBJ_POS(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b4ObjPos = (y))
#define CLR_TCPM_PD_PARTNER_OBJ_POS(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b4ObjPos = 0)

#define GET_TCPM_PD_PARTNER_CAP_MIS(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1CapMis)
#define SET_TCPM_PD_PARTNER_CAP_MIS(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1CapMis = (y))
#define CLR_TCPM_PD_PARTNER_CAP_MIS(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1CapMis = _FALSE)

#define GET_TCPM_PD_PARTNER_GIVE_BACK(x)                        (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1GiveBack)
#define SET_TCPM_PD_PARTNER_GIVE_BACK(x, y)                     (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1GiveBack = (y))
#define CLR_TCPM_PD_PARTNER_GIVE_BACK(x)                        (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1GiveBack = _FALSE)

#define GET_TCPM_PD_PARTNER_REQ_VOL(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.usVoltage)
#define SET_TCPM_PD_PARTNER_REQ_VOL(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.usVoltage = (y))

#define GET_TCPM_PD_PARTNER_OP_CUR(x)                           (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b10OpCurrent)
#define SET_TCPM_PD_PARTNER_OP_CUR(x, y)                        (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b10OpCurrent = (y))
#define CLR_TCPM_PD_PARTNER_OP_CUR(x)                           (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b10OpCurrent = 0)

#define GET_TCPM_PD_PARTNER_MAX_CUR(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b10MaxCurrent)
#define SET_TCPM_PD_PARTNER_MAX_CUR(x, y)                       (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b10MaxCurrent = (y))
#define CLR_TCPM_PD_PARTNER_MAX_CUR(x)                          (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b10MaxCurrent = 0)

#define GET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(x)                   (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1PPSSmallStep)
#define SET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(x, y)                (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1PPSSmallStep = (y))
#define CLR_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(x)                   (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1PPSSmallStep = 0)

#define GET_TCPM_PD_REQ_AVS_VOL_SMALL_STEP(x)                   (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1AVSSmallStep)
#define SET_TCPM_PD_REQ_AVS_VOL_SMALL_STEP(x, y)                (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1AVSSmallStep = (y))
#define CLR_TCPM_PD_REQ_AVS_VOL_SMALL_STEP(x)                   (g_pstTypeCTcpmPdPartnerInfo[x].stRDO.b1AVSSmallStep = 0)

// Port Partner(Other Side) Status Message Macros
#define GET_TCPM_PD_PARTNER_NEW_POWER_STATE(x)                  (g_pstTypeCTcpmPdPartnerInfo[x].stStatusEvent.b3NewPowerState)
#define SET_TCPM_PD_PARTNER_NEW_POWER_STATE(x, y)               (g_pstTypeCTcpmPdPartnerInfo[x].stStatusEvent.b3NewPowerState = (y))

#define GET_TCPM_PD_PARTNER_NEW_POWER_INDICATOR(x)              (g_pstTypeCTcpmPdPartnerInfo[x].stStatusEvent.b3NewPSIndicator)
#define SET_TCPM_PD_PARTNER_NEW_POWER_INDICATOR(x, y)           (g_pstTypeCTcpmPdPartnerInfo[x].stStatusEvent.b3NewPSIndicator = (y))

// Port Partner(Other Side) Alert Message Macros
#define GET_TCPM_PD_PARTNER_TYPE_OF_ALERT(x)                    (g_pstTypeCTcpmPdPartnerInfo[x].stAlertEvent.enumTypeOfAlert)
#define SET_TCPM_PD_PARTNER_TYPE_OF_ALERT(x, y)                 (g_pstTypeCTcpmPdPartnerInfo[x].stAlertEvent.enumTypeOfAlert = (y))

#define GET_TCPM_PD_PARTNER_BAT_STATUS(x)                       (g_pstTypeCTcpmPdPartnerInfo[x].stAlertEvent.enumBatStatus)
#define SET_TCPM_PD_PARTNER_BAT_STATUS(x, y)                    (g_pstTypeCTcpmPdPartnerInfo[x].stAlertEvent.enumBatStatus = (y))

#define GET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(x)                  (g_pstTypeCTcpmPdPartnerInfo[x].stAlertEvent.enumExtAlertEvent)
#define SET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(x, y)               (g_pstTypeCTcpmPdPartnerInfo[x].stAlertEvent.enumExtAlertEvent = (y))

//--------------------------------------------------
// PD Tx Message Related MACRO
//--------------------------------------------------
#define GET_TCPM_PD_TX_MSG_ID_SOP(x)                            (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP)
#define SET_TCPM_PD_TX_MSG_ID_SOP(x, y)                         (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP = (y))
#define ADD_TCPM_PD_TX_MSG_ID_SOP(x)                            (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP = ((g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP + 1) % 8))
#define CLR_TCPM_PD_TX_MSG_ID_SOP(x)                            (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP = 0x00)

#define GET_TCPM_PD_TX_MSG_ID_SOP_P(x)                          (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_P)
#define SET_TCPM_PD_TX_MSG_ID_SOP_P(x, y)                       (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_P = (y))
#define ADD_TCPM_PD_TX_MSG_ID_SOP_P(x)                          (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_P = ((g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_P + 1) % 8))
#define CLR_TCPM_PD_TX_MSG_ID_SOP_P(x)                          (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_P = 0x00)

#define GET_TCPM_PD_TX_MSG_ID_SOP_PP(x)                         (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_PP)
#define SET_TCPM_PD_TX_MSG_ID_SOP_PP(x, y)                      (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_PP = (y))
#define ADD_TCPM_PD_TX_MSG_ID_SOP_PP(x)                         (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_PP = ((g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_PP + 1) % 8))
#define CLR_TCPM_PD_TX_MSG_ID_SOP_PP(x)                         (g_pstTypeCTcpmPdTxInfo[x].b4MsgID_SOP_PP = 0x00)

#define GET_TCPM_PD_TX_RETRY_FAIL_EVENT(x)                      (g_pstTypeCTcpmPdTxInfo[x].enumTxRetryFailEvent)
#define SET_TCPM_PD_TX_RETRY_FAIL_EVENT(x, y)                   (g_pstTypeCTcpmPdTxInfo[x].enumTxRetryFailEvent = (y))

#define GET_TCPM_PD_INT_OVERWRITE(x)                            (g_pstTypeCTcpmPdTxInfo[x].b1IntOverWrite)
#define SET_TCPM_PD_INT_OVERWRITE(x)                            (g_pstTypeCTcpmPdTxInfo[x].b1IntOverWrite = _TRUE)
#define CLR_TCPM_PD_INT_OVERWRITE(x)                            (g_pstTypeCTcpmPdTxInfo[x].b1IntOverWrite = _FALSE)

//--------------------------------------------------
// PD TCPCI Rx Buffer Related MACRO
//--------------------------------------------------
#define GET_TCPM_RX_BYTE_CNT()                                  (g_pucTypeCTcpmRxBuffer_EXINT[0])
#define GET_TCPM_RX_BUF_FRAME_TYPE()                            (g_pucTypeCTcpmRxBuffer_EXINT[1] & (_BIT2 | _BIT1 | _BIT0))
#define GET_TCPM_RX_BUF_MSG_HEADER_L()                          (g_pucTypeCTcpmRxBuffer_EXINT[2])
#define GET_TCPM_RX_BUF_MSG_HEADER_H()                          (g_pucTypeCTcpmRxBuffer_EXINT[3])

//--------------------------------------------------
// PD Rx Message Related MACRO
//--------------------------------------------------
#define GET_TCPM_PD_RCV_MSG(x)                                  (g_pstTypeCTcpmPdRxInfo[x].ucRcvMsg)
#define SET_TCPM_PD_RCV_MSG(x, y)                               (g_pstTypeCTcpmPdRxInfo[x].ucRcvMsg = (y))
#define CLR_TCPM_PD_RCV_MSG(x)                                  (g_pstTypeCTcpmPdRxInfo[x].ucRcvMsg = 0)

#define GET_TCPM_PD_RCV_NOD_CNT(x)                              ((BYTE)g_pstTypeCTcpmPdRxInfo[x].b3RcvNodCnt)
#define SET_TCPM_PD_RCV_NOD_CNT(x, y)                           (g_pstTypeCTcpmPdRxInfo[x].b3RcvNodCnt = (y))

#define GET_TCPM_PD_RX_MSG_ID_SOP(x)                            ((BYTE)(g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP))
#define SET_TCPM_PD_RX_MSG_ID_SOP(x, y)                         (g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP = (y))
#define CLR_TCPM_PD_RX_MSG_ID_SOP(x)                            (g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP = 0x0F)

#define GET_TCPM_PD_RX_MSG_ID_SOP_P(x)                          ((BYTE)(g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP_P))
#define SET_TCPM_PD_RX_MSG_ID_SOP_P(x, y)                       (g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP_P = (y))
#define CLR_TCPM_PD_RX_MSG_ID_SOP_P(x)                          (g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP_P = 0x0F)

#define GET_TCPM_PD_RX_MSG_ID_SOP_PP(x)                         ((BYTE)(g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP_PP))
#define SET_TCPM_PD_RX_MSG_ID_SOP_PP(x, y)                      (g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP_PP = (y))
#define CLR_TCPM_PD_RX_MSG_ID_SOP_PP(x)                         (g_pstTypeCTcpmPdRxInfo[x].b4MsgID_SOP_PP = 0x0F)

// Extended Message Info Macros
#define GET_TCPM_PD_RCV_EXT_CHUNKED(x)                          (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b1Chunked)
#define SET_TCPM_PD_RCV_EXT_CHUNKED(x, y)                       (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b1Chunked = (y))

#define GET_TCPM_PD_RCV_EXT_CHUNK_NUM(x)                        (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b4ChunkNum)
#define SET_TCPM_PD_RCV_EXT_CHUNK_NUM(x, y)                     (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b4ChunkNum = (y))

#define GET_TCPM_PD_RCV_EXT_CHUNK_REQ(x)                        (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b1ChunkRequest)
#define SET_TCPM_PD_RCV_EXT_CHUNK_REQ(x, y)                     (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b1ChunkRequest = (y))

#define GET_TCPM_PD_RCV_EXT_DATA_SIZE(x)                        (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b9DataSize)
#define SET_TCPM_PD_RCV_EXT_DATA_SIZE(x, y)                     (g_pstTypeCTcpmPdRxInfo[x].stExtMsgInfo.b9DataSize = (y))

//--------------------------------------------------
// PD VDM Related MACRO
//--------------------------------------------------
#define GET_TCPM_PD_ALT_MODE_FUNCTION(x)                        (g_pstTypeCTcpmPdVdmInfo[x].b1AltModeFunc)
#define SET_TCPM_PD_ALT_MODE_FUNCTION(x)                        (g_pstTypeCTcpmPdVdmInfo[x].b1AltModeFunc = _TRUE)
#define CLR_TCPM_PD_ALT_MODE_FUNCTION(x)                        (g_pstTypeCTcpmPdVdmInfo[x].b1AltModeFunc = _FALSE)

#define GET_TCPM_PD_RCV_VDM_CMD(x)                              (g_pstTypeCTcpmPdVdmInfo[x].ucRcvVdmMsg)
#define GET_TCPM_PD_RCV_VDM_CMD_TYPE(x)                         (g_pstTypeCTcpmPdVdmInfo[x].ucRcvVdmMsg & (_BIT7 | _BIT6))
#define SET_TCPM_PD_RCV_VDM_CMD(x, y)                           (g_pstTypeCTcpmPdVdmInfo[x].ucRcvVdmMsg = (y))
#define CLR_TCPM_PD_RCV_VDM_CMD(x)                              (g_pstTypeCTcpmPdVdmInfo[x].ucRcvVdmMsg = 0)

#define GET_TCPM_PD_RCV_VDM_SVID(x)                             (((WORD)(g_pstTypeCTcpmPdVdmInfo[x].ucVdmSVID_H) << 8) | ((WORD)(g_pstTypeCTcpmPdVdmInfo[x].ucVdmSVID_L)))
#define GET_TCPM_PD_RCV_VDM_SVID_H(x)                           (g_pstTypeCTcpmPdVdmInfo[x].ucVdmSVID_H)
#define GET_TCPM_PD_RCV_VDM_SVID_L(x)                           (g_pstTypeCTcpmPdVdmInfo[x].ucVdmSVID_L)
#define SET_TCPM_PD_RCV_VDM_SVID_H(x, y)                        (g_pstTypeCTcpmPdVdmInfo[x].ucVdmSVID_H = (y))
#define SET_TCPM_PD_RCV_VDM_SVID_L(x, y)                        (g_pstTypeCTcpmPdVdmInfo[x].ucVdmSVID_L = (y))

#define GET_TCPM_PD_RCV_VDM_TYPE(x)                             (g_pstTypeCTcpmPdVdmInfo[x].b1RcvVdmType)
#define SET_TCPM_PD_RCV_VDM_TYPE(x, y)                          (g_pstTypeCTcpmPdVdmInfo[x].b1RcvVdmType = (y))

#define GET_TCPM_PD_RCV_VDM_OBJ_POS(x)                          (g_pstTypeCTcpmPdVdmInfo[x].b3VdmObjPos)
#define SET_TCPM_PD_RCV_VDM_OBJ_POS(x, y)                       (g_pstTypeCTcpmPdVdmInfo[x].b3VdmObjPos = (y))

#define GET_TCPM_PD_UFP_PRODUCT_TYPE(x)                         (g_pstTypeCTcpmPdVdmInfo[x].enumUFPProductType)
#define SET_TCPM_PD_UFP_PRODUCT_TYPE(x, y)                      (g_pstTypeCTcpmPdVdmInfo[x].enumUFPProductType = (y))

#define GET_TCPM_PD_DFP_PRODUCT_TYPE(x)                         (g_pstTypeCTcpmPdVdmInfo[x].enumDFPProductType)
#define SET_TCPM_PD_DFP_PRODUCT_TYPE(x, y)                      (g_pstTypeCTcpmPdVdmInfo[x].enumDFPProductType = (y))

#define GET_TCPM_PD_VDM_RESP_CONFLICT_CNT(x)                    (g_pstTypeCTcpmPdVdmInfo[x].b2VdmRespConflictCnt)
#define ADD_TCPM_PD_VDM_RESP_CONFLICT_CNT(x)                    (g_pstTypeCTcpmPdVdmInfo[x].b2VdmRespConflictCnt += 1)
#define CLR_TCPM_PD_VDM_RESP_CONFLICT_CNT(x)                    (g_pstTypeCTcpmPdVdmInfo[x].b2VdmRespConflictCnt = 0)

#define GET_TCPM_PD_PARTNER_INIT_ALT_MODE(x)                    (g_pstTypeCTcpmPdVdmInfo[x].b1PartnerInitAltMode)
#define SET_TCPM_PD_PARTNER_INIT_ALT_MODE(x)                    (g_pstTypeCTcpmPdVdmInfo[x].b1PartnerInitAltMode = _TRUE)
#define CLR_TCPM_PD_PARTNER_INIT_ALT_MODE(x)                    (g_pstTypeCTcpmPdVdmInfo[x].b1PartnerInitAltMode = _FALSE)

#define GET_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(x)                  (g_pstTypeCTcpmPdVdmInfo[x].b2PartnerVdmNoRespCnt)
#define ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(x)                  (g_pstTypeCTcpmPdVdmInfo[x].b2PartnerVdmNoRespCnt += 1)
#define CLR_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(x)                  (g_pstTypeCTcpmPdVdmInfo[x].b2PartnerVdmNoRespCnt = 0)

#define GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].b2CblVdmNoRespCnt)
#define ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].b2CblVdmNoRespCnt += 1)
#define CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].b2CblVdmNoRespCnt = 0)

#define GET_TCPM_PD_VDM_BUSY_CNT(x)                             (g_pstTypeCTcpmPdVdmInfo[x].b3VdmBusyCnt)
#define ADD_TCPM_PD_VDM_BUSY_CNT(x)                             (g_pstTypeCTcpmPdVdmInfo[x].b3VdmBusyCnt += 1)
#define CLR_TCPM_PD_VDM_BUSY_CNT(x)                             (g_pstTypeCTcpmPdVdmInfo[x].b3VdmBusyCnt = 0)

// PD VDM (DP Alt Mode) Related Macros
// PD Behavior Type Macro
#define GET_TCPM_PD_DPAM_SUPPORT(x)                             (g_pstTypeCTcpmPdVdmInfo[x].b1DpamSupport)
#define SET_TCPM_PD_DPAM_SUPPORT(x, y)                          (g_pstTypeCTcpmPdVdmInfo[x].b1DpamSupport = (y))

#define GET_TCPM_PD_MODAL_OPERATION_SUPPORT(x)                  (g_pstTypeCTcpmPdVdmInfo[x].b1ModalOperationSupport)
#define SET_TCPM_PD_MODAL_OPERATION_SUPPORT(x, y)               (g_pstTypeCTcpmPdVdmInfo[x].b1ModalOperationSupport = (y))

#define GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.enumPinAssignment)
#define SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(x, y)                   (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.enumPinAssignment = (y))

#define GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.enumPinAssignmentCap)
#define SET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(x, y)               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.enumPinAssignmentCap = (y))

#define GET_TCPM_PD_DPAM_OBJ_POS(x)                             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b3ObjPos)
#define SET_TCPM_PD_DPAM_OBJ_POS(x, y)                          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b3ObjPos = (y))
#define CLR_TCPM_PD_DPAM_OBJ_POS(x)                             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b3ObjPos = 0)

#define GET_TCPM_PD_DPAM_SVID_SEARCH_FINISH(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1SvidSearchFinish)
#define SET_TCPM_PD_DPAM_SVID_SEARCH_FINISH(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1SvidSearchFinish = _TRUE)
#define CLR_TCPM_PD_DPAM_SVID_SEARCH_FINISH(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1SvidSearchFinish = _FALSE)

#define GET_TCPM_PD_DPAM_ENTER(x)                               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1EnterMode)
#define SET_TCPM_PD_DPAM_ENTER(x)                               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1EnterMode = _TRUE)
#define CLR_TCPM_PD_DPAM_ENTER(x)                               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1EnterMode = _FALSE)

#define GET_TCPM_PD_DPAM_CONFIG(x)                              (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1Config)
#define SET_TCPM_PD_DPAM_CONFIG(x, y)                           (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1Config = (y))

#define GET_TCPM_PD_DPAM_TARGET_CONFIG(x)                       (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1TargetConfig)
#define SET_TCPM_PD_DPAM_TARGET_CONFIG(x, y)                    (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1TargetConfig = (y))

#define GET_TCPM_PD_DPAM_WAIT_CONFIG(x)                         (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1WaitConfig)
#define SET_TCPM_PD_DPAM_WAIT_CONFIG(x)                         (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1WaitConfig = _TRUE)
#define CLR_TCPM_PD_DPAM_WAIT_CONFIG(x)                         (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1WaitConfig = _FALSE)

#define GET_TCPM_PD_DPAM_MULTI_FUNC(x)                          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunction)
#define SET_TCPM_PD_DPAM_MULTI_FUNC(x)                          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunction = _TRUE)
#define CLR_TCPM_PD_DPAM_MULTI_FUNC(x)                          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunction = _FALSE)

#define GET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(x)               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunctionChange)
#define SET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(x)               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunctionChange = _TRUE)
#define CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(x)               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunctionChange = _FALSE)

#define GET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(x)          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunctionChangeDone)
#define SET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(x)          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunctionChangeDone = _TRUE)
#define CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(x)          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1MultiFunctionChangeDone = _FALSE)

#define GET_TCPM_PD_DPAM_ATTENTION_WAIT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1AttentionWait)
#define SET_TCPM_PD_DPAM_ATTENTION_WAIT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1AttentionWait = _TRUE)
#define CLR_TCPM_PD_DPAM_ATTENTION_WAIT(x)                      (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1AttentionWait = _FALSE)

#define GET_TCPM_PD_DPAM_EXIT_REQ(x)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1ExitMode)
#define SET_TCPM_PD_DPAM_EXIT_REQ(x)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1ExitMode = _TRUE)
#define CLR_TCPM_PD_DPAM_EXIT_REQ(x)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1ExitMode = _FALSE)

// Port Partner DP_Status Related Macros
#define GET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(x)              (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.enumPartnerDpConnectStatus)
#define SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(x, y)           (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.enumPartnerDpConnectStatus = (y))

#define GET_TCPM_PD_PARTNER_DPAM_POWER_LOW(x)                   (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpPowerLow)
#define SET_TCPM_PD_PARTNER_DPAM_POWER_LOW(x)                   (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpPowerLow = _TRUE)
#define CLR_TCPM_PD_PARTNER_DPAM_POWER_LOW(x)                   (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpPowerLow = _FALSE)

#define GET_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(x)             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpFunctionEnabled)
#define SET_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(x)             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpFunctionEnabled = _TRUE)
#define CLR_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(x)             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpFunctionEnabled = _FALSE)

#define GET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(x)              (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerMultiFunctionBit)
#define SET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(x)              (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerMultiFunctionBit = _TRUE)
#define CLR_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(x)              (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerMultiFunctionBit = _FALSE)

#define GET_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(x)          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerUsbConfigRequest)
#define SET_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(x)          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerUsbConfigRequest = _TRUE)
#define CLR_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(x)          (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerUsbConfigRequest = _FALSE)

#define GET_TCPM_PD_PARTNER_DPAM_EXIT_REQ(x)                    (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpAltModeExit)
#define SET_TCPM_PD_PARTNER_DPAM_EXIT_REQ(x)                    (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpAltModeExit = _TRUE)
#define CLR_TCPM_PD_PARTNER_DPAM_EXIT_REQ(x)                    (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerDpAltModeExit = _FALSE)

#define GET_TCPM_PD_PARTNER_HPD_TYPE(x)                         (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.enumPartnerHpdType)
#define SET_TCPM_PD_PARTNER_HPD_TYPE(x, y)                      (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.enumPartnerHpdType = (y))

#define GET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(x)              (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.ucPartnerPinAssignmentCap)
#define SET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(x, y)           (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.ucPartnerPinAssignmentCap = (y))

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
#define GET_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerNoDpAltSuspend)
#define SET_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerNoDpAltSuspend = _TRUE)
#define CLR_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(x)                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stDpStatusInfo.b1PartnerNoDpAltSuspend = _FALSE)
#endif

// PD VDM (DP Alt Mode HPD) Related Macros
#define GET_TCPM_PD_HPD_QUEUE(x, y)                             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.penumHpdType[y])
#define SET_TCPM_PD_HPD_QUEUE(x, y)                             (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.penumHpdType[g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdWptr] = (y))
#define CLR_TCPM_PD_HPD_QUEUE(x)                                (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.penumHpdType[g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdRptr] = (_PD_HPD_NONE))

#define GET_TCPM_PD_HPD_SPACE_TIME(x, y)                        (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.pusHpdSpace[y])
#define SET_TCPM_PD_HPD_SPACE_TIME(x, y)                        (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.pusHpdSpace[g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdWptr] = (y))
#define CLR_TCPM_PD_HPD_SPACE_TIME(x)                           (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.pusHpdSpace[g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdRptr] = 0)

#define GET_TCPM_PD_HPD_STATUS(x)                               (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b1HpdStatus)
#define SET_TCPM_PD_HPD_STATUS(x, y)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b1HpdStatus = (y))

#define GET_TCPM_PD_HPD_CNT(x)                                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b3HpdCnt)
#define ADD_TCPM_PD_HPD_CNT(x)                                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b3HpdCnt += 1)
#define SUB_TCPM_PD_HPD_CNT(x)                                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b3HpdCnt -= 1)
#define CLR_TCPM_PD_HPD_CNT(x)                                  (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b3HpdCnt = 0)

#define GET_TCPM_PD_HPD_WPTR(x)                                 (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdWptr)
#define ADD_TCPM_PD_HPD_WPTR(x)                                 (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdWptr = (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdWptr + 1) % 4)
#define CLR_TCPM_PD_HPD_WPTR(x)                                 (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdWptr = 0)

#define GET_TCPM_PD_HPD_RPTR(x)                                 (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdRptr)
#define ADD_TCPM_PD_HPD_RPTR(x)                                 (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdRptr = (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdRptr + 1) % 4)
#define CLR_TCPM_PD_HPD_RPTR(x)                                 (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.stHpdQueue.b2HpdRptr = 0)

// Force Sending HPD IRQ Macros
#define GET_TCPM_PD_FORCE_HPD_IRQ(x)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1ForceHpdIrq)
#define SET_TCPM_PD_FORCE_HPD_IRQ(x)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1ForceHpdIrq = _TRUE)
#define CLR_TCPM_PD_FORCE_HPD_IRQ(x)                            (g_pstTypeCTcpmPdVdmInfo[x].stDpamInfo.b1ForceHpdIrq = _FALSE)

//--------------------------------------------------
// PD Cable Info Related MACRO
//--------------------------------------------------
#define GET_TCPM_PD_CBL_SPEC_VER(x)                             ((BYTE)(g_pstTypeCTcpmPdCableInfo[x].b2CableSpecVer))
#define SET_TCPM_PD_CBL_SPEC_VER(x, y)                          (g_pstTypeCTcpmPdCableInfo[x].b2CableSpecVer = (y))

#define GET_TCPM_PD_CBL_DISC_ID_RETRY_CNT(x)                    ((BYTE)g_pstTypeCTcpmPdCableInfo[x].b5DiscoverIdRetryFailCnt)
#define ADD_TCPM_PD_CBL_DISC_ID_RETRY_CNT(x)                    (g_pstTypeCTcpmPdCableInfo[x].b5DiscoverIdRetryFailCnt += 1)
#define CLR_TCPM_PD_CBL_DISC_ID_RETRY_CNT(x)                    (g_pstTypeCTcpmPdCableInfo[x].b5DiscoverIdRetryFailCnt = 0)

#define GET_TCPM_PD_CBL_MAX_CUR(x)                              ((WORD)(g_pstTypeCTcpmPdCableInfo[x].b10CableMaxCur))
#define SET_TCPM_PD_CBL_MAX_CUR(x, y)                           (g_pstTypeCTcpmPdCableInfo[x].b10CableMaxCur = (y))

#define GET_TCPM_PD_CBL_PD_CAPABILITY(x)                        (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCablePdCap)
#define SET_TCPM_PD_CBL_PD_CAPABILITY(x, y)                     (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCablePdCap = (y))

#define GET_TCPM_PD_CBL_PRODUCT_TYPE(x)                         (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableProductType)
#define SET_TCPM_PD_CBL_PRODUCT_TYPE(x, y)                      (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableProductType = (y))

#define GET_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(x)              (g_pstTypeCTcpmPdCableInfo[x].b1CableModalOperation)
#define SET_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(x)              (g_pstTypeCTcpmPdCableInfo[x].b1CableModalOperation = _TRUE)
#define CLR_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(x)              (g_pstTypeCTcpmPdCableInfo[x].b1CableModalOperation = _FALSE)

#define GET_TCPM_PD_CBL_CONNECTOR_TYPE(x)                       (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableConnectorType)
#define SET_TCPM_PD_CBL_CONNECTOR_TYPE(x, y)                    (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableConnectorType = (y))

#define GET_TCPM_PD_CBL_EPR_MODE_CAPABLE(x)                     (g_pstTypeCTcpmPdCableInfo[x].b1CableEprModeCapable)
#define SET_TCPM_PD_CBL_EPR_MODE_CAPABLE(x)                     (g_pstTypeCTcpmPdCableInfo[x].b1CableEprModeCapable = _TRUE)
#define CLR_TCPM_PD_CBL_EPR_MODE_CAPABLE(x)                     (g_pstTypeCTcpmPdCableInfo[x].b1CableEprModeCapable = _FALSE)

#define GET_TCPM_PD_CBL_TERMINATION_TYPE(x)                     (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTerminationType)
#define SET_TCPM_PD_CBL_TERMINATION_TYPE(x, y)                  (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTerminationType = (y))

#define GET_TCPM_PD_CBL_VCONN_REQUIRED(x)                       (g_pstTypeCTcpmPdCableInfo[x].b1CableVconnRequired)
#define SET_TCPM_PD_CBL_VCONN_REQUIRED(x)                       (g_pstTypeCTcpmPdCableInfo[x].b1CableVconnRequired = _TRUE)
#define CLR_TCPM_PD_CBL_VCONN_REQUIRED(x)                       (g_pstTypeCTcpmPdCableInfo[x].b1CableVconnRequired = _FALSE)

#define GET_TCPM_PD_CBL_MAX_VOL(x)                              (g_pstTypeCTcpmPdCableInfo[x].b10CableMaxVol)
#define SET_TCPM_PD_CBL_MAX_VOL(x, y)                           (g_pstTypeCTcpmPdCableInfo[x].b10CableMaxVol = (y))

#define GET_TCPM_PD_CBL_SBU_SUPPORT(x)                          (g_pstTypeCTcpmPdCableInfo[x].b1CableSbuSupport)
#define SET_TCPM_PD_CBL_SBU_SUPPORT(x)                          (g_pstTypeCTcpmPdCableInfo[x].b1CableSbuSupport = _TRUE)
#define CLR_TCPM_PD_CBL_SBU_SUPPORT(x)                          (g_pstTypeCTcpmPdCableInfo[x].b1CableSbuSupport = _FALSE)

#define GET_TCPM_PD_CBL_SBU_TYPE(x)                             (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableSbuType)
#define SET_TCPM_PD_CBL_SBU_TYPE(x, y)                          (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableSbuType = (y))

#define GET_TCPM_PD_CBL_USB_HIGHEST_SPEED(x)                    (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableUsbHighestSpeed)
#define SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(x, y)                 (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableUsbHighestSpeed = (y))

#define GET_TCPM_PD_CBL_VBUS_THROUGH(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableVbusThrough)
#define SET_TCPM_PD_CBL_VBUS_THROUGH(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableVbusThrough = _TRUE)
#define CLR_TCPM_PD_CBL_VBUS_THROUGH(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableVbusThrough = _FALSE)

#define GET_TCPM_PD_CBL_SOP_PP_SUPPORT(x)                       (g_pstTypeCTcpmPdCableInfo[x].b1CableSopPP)
#define SET_TCPM_PD_CBL_SOP_PP_SUPPORT(x)                       (g_pstTypeCTcpmPdCableInfo[x].b1CableSopPP = _TRUE)
#define CLR_TCPM_PD_CBL_SOP_PP_SUPPORT(x)                       (g_pstTypeCTcpmPdCableInfo[x].b1CableSopPP = _FALSE)

#define GET_TCPM_PD_CBL_U3_TO_U0_TRANSITION_MODE(x)             (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableU3ToU0TransitionMode)
#define SET_TCPM_PD_CBL_U3_TO_U0_TRANSITION_MODE(x, y)          (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableU3ToU0TransitionMode = (y))

#define GET_TCPM_PD_CBL_USB_4_SUPPORT(x)                        (g_pstTypeCTcpmPdCableInfo[x].b1CableUSB4)
#define SET_TCPM_PD_CBL_USB_4_SUPPORT(x)                        (g_pstTypeCTcpmPdCableInfo[x].b1CableUSB4 = _TRUE)
#define CLR_TCPM_PD_CBL_USB_4_SUPPORT(x)                        (g_pstTypeCTcpmPdCableInfo[x].b1CableUSB4 = _FALSE)

#define GET_TCPM_PD_CBL_USB_3_2_SUPPORT(x)                      (g_pstTypeCTcpmPdCableInfo[x].b1CableUSB3_2)
#define SET_TCPM_PD_CBL_USB_3_2_SUPPORT(x)                      (g_pstTypeCTcpmPdCableInfo[x].b1CableUSB3_2 = _TRUE)
#define CLR_TCPM_PD_CBL_USB_3_2_SUPPORT(x)                      (g_pstTypeCTcpmPdCableInfo[x].b1CableUSB3_2 = _FALSE)

#define GET_TCPM_PD_CBL_LANES_SUPPORT(x)                        (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableUsbLanesSupport)
#define SET_TCPM_PD_CBL_LANES_SUPPORT(x, y)                     (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableUsbLanesSupport = (y))

#define GET_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(x)               (g_pstTypeCTcpmPdCableInfo[x].b1ChargeThroughSupport)
#define SET_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(x)               (g_pstTypeCTcpmPdCableInfo[x].b1ChargeThroughSupport = _TRUE)
#define CLR_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(x)               (g_pstTypeCTcpmPdCableInfo[x].b1ChargeThroughSupport = _FALSE)

#define GET_TCPM_PD_CBL_SOFT_RESET_REQUIRED(x)                  (g_pstTypeCTcpmPdCableInfo[x].b1CableSoftRstReq)
#define SET_TCPM_PD_CBL_SOFT_RESET_REQUIRED(x)                  (g_pstTypeCTcpmPdCableInfo[x].b1CableSoftRstReq = _TRUE)
#define CLR_TCPM_PD_CBL_SOFT_RESET_REQUIRED(x)                  (g_pstTypeCTcpmPdCableInfo[x].b1CableSoftRstReq = _FALSE)

#define GET_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(x)                (g_pstTypeCTcpmPdCableInfo[x].b1CableDpEnterDpModeSupport)
#define SET_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(x)                (g_pstTypeCTcpmPdCableInfo[x].b1CableDpEnterDpModeSupport = _TRUE)
#define CLR_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(x)                (g_pstTypeCTcpmPdCableInfo[x].b1CableDpEnterDpModeSupport = _FALSE)

#define GET_TCPM_PD_CBL_SVID_SEARCH_FINISH(x)                   (g_pstTypeCTcpmPdCableInfo[x].b1CableSvidSearchFinish)
#define SET_TCPM_PD_CBL_SVID_SEARCH_FINISH(x)                   (g_pstTypeCTcpmPdCableInfo[x].b1CableSvidSearchFinish = _TRUE)
#define CLR_TCPM_PD_CBL_SVID_SEARCH_FINISH(x)                   (g_pstTypeCTcpmPdCableInfo[x].b1CableSvidSearchFinish = _FALSE)

#define GET_TCPM_PD_CBL_DP_SVID_SUPPORT(x)                      (g_pstTypeCTcpmPdCableInfo[x].b1CableDpSvidSupport)
#define SET_TCPM_PD_CBL_DP_SVID_SUPPORT(x)                      (g_pstTypeCTcpmPdCableInfo[x].b1CableDpSvidSupport = _TRUE)
#define CLR_TCPM_PD_CBL_DP_SVID_SUPPORT(x)                      (g_pstTypeCTcpmPdCableInfo[x].b1CableDpSvidSupport = _FALSE)

#define GET_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(x)                (g_pstTypeCTcpmPdCableInfo[x].b1CableDpModeInfoReceived)
#define SET_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(x)                (g_pstTypeCTcpmPdCableInfo[x].b1CableDpModeInfoReceived = _TRUE)
#define CLR_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(x)                (g_pstTypeCTcpmPdCableInfo[x].b1CableDpModeInfoReceived = _FALSE)

#define GET_TCPM_PD_CBL_TBT3_SVID_SUPPORT(x)                    (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3SvidSupport)
#define SET_TCPM_PD_CBL_TBT3_SVID_SUPPORT(x)                    (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3SvidSupport = _TRUE)
#define CLR_TCPM_PD_CBL_TBT3_SVID_SUPPORT(x)                    (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3SvidSupport = _FALSE)

#define GET_TCPM_PD_CBL_SVDM_VERSION(x)                         (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableSvdmVersion)
#define SET_TCPM_PD_CBL_SVDM_VERSION(x, y)                      (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableSvdmVersion = (y))

#define GET_TCPM_PD_CBL_DPAM_VERSION(x)                         (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableDpamVersion)
#define SET_TCPM_PD_CBL_DPAM_VERSION(x, y)                      (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableDpamVersion = (y))

#define GET_TCPM_PD_CBL_PIN_ASSIGNMENT(x)                       (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCablePinAssignment)
#define SET_TCPM_PD_CBL_PIN_ASSIGNMENT(x, y)                    (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCablePinAssignment = (y))

#define GET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(x)                    (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3ProductType)
#define SET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(x, y)                 (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3ProductType = (y))

#define GET_TCPM_PD_CBL_TBT3_DIRECTION(x)                       (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3Direction)
#define SET_TCPM_PD_CBL_TBT3_DIRECTION(x, y)                    (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3Direction = (y))

#define GET_TCPM_PD_CBL_TBT3_RETIMER(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3Retimer)
#define SET_TCPM_PD_CBL_TBT3_RETIMER(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3Retimer = _TRUE)
#define CLR_TCPM_PD_CBL_TBT3_RETIMER(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3Retimer = _FALSE)

#define GET_TCPM_PD_CBL_TBT3_OPTICAL(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3Optical)
#define SET_TCPM_PD_CBL_TBT3_OPTICAL(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3Optical = _TRUE)
#define CLR_TCPM_PD_CBL_TBT3_OPTICAL(x)                         (g_pstTypeCTcpmPdCableInfo[x].b1CableTbt3Optical = _FALSE)

#define GET_TCPM_PD_CBL_TBT3_ROUNDED_SUPPORT(x)                 (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3RoundedSupport)
#define SET_TCPM_PD_CBL_TBT3_ROUNDED_SUPPORT(x, y)              (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3RoundedSupport = (y))

#define GET_TCPM_PD_CBL_TBT3_SPEED(x)                           (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3Speed)
#define SET_TCPM_PD_CBL_TBT3_SPEED(x, y)                        (g_pstTypeCTcpmPdCableInfo[x].enumTypeCCableTbt3Speed = (y))

#define GET_TCPM_PD_CBL_ACTIVE_COMPONENT(x)                     (g_pstTypeCTcpmPdCableInfoForDpcd[x].enumTypeCCableActiveComponent)
#define SET_TCPM_PD_CBL_ACTIVE_COMPONENT(x, y)                  (g_pstTypeCTcpmPdCableInfoForDpcd[x].enumTypeCCableActiveComponent = (y))

#define GET_TCPM_PD_CBL_UHBR13P5_SUPPORT(x)                     (g_pstTypeCTcpmPdCableInfoForDpcd[x].b1CableUhbr13p5Support)
#define SET_TCPM_PD_CBL_UHBR13P5_SUPPORT(x)                     (g_pstTypeCTcpmPdCableInfoForDpcd[x].b1CableUhbr13p5Support = _TRUE)
#define CLR_TCPM_PD_CBL_UHBR13P5_SUPPORT(x)                     (g_pstTypeCTcpmPdCableInfoForDpcd[x].b1CableUhbr13p5Support = _FALSE)

#define GET_TCPM_PD_CBL_MAX_DP_RATE(x)                          (g_pstTypeCTcpmPdCableInfoForDpcd[x].enumTypeCCableMaxDpRate)
#define SET_TCPM_PD_CBL_MAX_DP_RATE(x, y)                       (g_pstTypeCTcpmPdCableInfoForDpcd[x].enumTypeCCableMaxDpRate = (y))

//--------------------------------------------------
// TCPM Power Related Macro
//--------------------------------------------------
#define GET_TCPM_MAX_POWER(x)                                   (g_pstTypeCTcpmPowerInfo[x].usMaxPower)
#define SET_TCPM_MAX_POWER(x, y)                                (g_pstTypeCTcpmPowerInfo[x].usMaxPower = (y))

#define GET_TCPM_VBUS_STATUS(x)                                 ((bit)(g_pstTypeCTcpmPowerInfo[x].b1VbusStatus))
#define SET_TCPM_VBUS_STATUS(x, y)                              (g_pstTypeCTcpmPowerInfo[x].b1VbusStatus = (y))

#define GET_TCPM_REQ_PWR(x)                                     (g_pstTypeCTcpmPowerInfo[x].usReqPower)
#define SET_TCPM_REQ_PWR(x, y)                                  (g_pstTypeCTcpmPowerInfo[x].usReqPower = (y))

#define GET_TCPM_OUTPUT_VOL(x)                                  (g_pstTypeCTcpmPowerInfo[x].usOutputVol)
#define SET_TCPM_OUTPUT_VOL(x, y)                               (g_pstTypeCTcpmPowerInfo[x].usOutputVol = (y))

#define GET_TCPM_OUTPUT_CUR(x)                                  ((WORD)(g_pstTypeCTcpmPowerInfo[x].b10OutputCur))
#define SET_TCPM_OUTPUT_CUR(x, y)                               (g_pstTypeCTcpmPowerInfo[x].b10OutputCur = (y))

#define GET_TCPM_OCP_CURRENT(x)                                 (g_pstTypeCTcpmPowerInfo[x].usOcpCurrent)
#define SET_TCPM_OCP_CURRENT(x, y)                              (g_pstTypeCTcpmPowerInfo[x].usOcpCurrent = (y))

#define GET_TCPM_OCP_RATIO(x, y)                                (g_pstTypeCTcpmPowerInfo[x].pstPowerProtectInfo[y].ucOcpCurRatio)
#define SET_TCPM_OCP_RATIO(x, y, z)                             (g_pstTypeCTcpmPowerInfo[x].pstPowerProtectInfo[y].ucOcpCurRatio = (z))

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
#define GET_TCPM_OCP_PROTECT_BY_TCPC(x)                         (g_pstTypeCTcpmPowerInfo[x].b1OcpProtectByTcpc)
#define SET_TCPM_OCP_PROTECT_BY_TCPC(x, y)                      (g_pstTypeCTcpmPowerInfo[x].b1OcpProtectByTcpc = (y))
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
#define GET_TCPM_OVP_UVP_SUPPORT(x)                             (g_pstTypeCTcpmPowerInfo[x].b1OvpUvpSupport)
#define SET_TCPM_OVP_UVP_SUPPORT(x, y)                          (g_pstTypeCTcpmPowerInfo[x].b1OvpUvpSupport = (y))

#define GET_TCPM_OVP_UVP_CHECK(x)                               (g_pstTypeCTcpmPowerInfo[x].b1OvpUvpCheck)
#define SET_TCPM_OVP_UVP_CHECK(x)                               (g_pstTypeCTcpmPowerInfo[x].b1OvpUvpCheck = _ON)
#define CLR_TCPM_OVP_UVP_CHECK(x)                               (g_pstTypeCTcpmPowerInfo[x].b1OvpUvpCheck = _OFF)

#define GET_TCPM_OVP_THRESHOLD(x)                               (g_pstTypeCTcpmPowerInfo[x].ucOvpThreshold)
#define SET_TCPM_OVP_THRESHOLD(x, y)                            (g_pstTypeCTcpmPowerInfo[x].ucOvpThreshold = (y))

#define GET_TCPM_OVP_VOLTAGE(x)                                 (g_pstTypeCTcpmPowerInfo[x].usOvpVol)
#define SET_TCPM_OVP_VOLTAGE(x, y)                              (g_pstTypeCTcpmPowerInfo[x].usOvpVol = (y))

#define GET_TCPM_OVP_JUDGE_DEBOUNCE(x)                          (g_pstTypeCTcpmPowerInfo[x].ucOvpProtectDebounce)
#define SET_TCPM_OVP_JUDGE_DEBOUNCE(x, y)                       (g_pstTypeCTcpmPowerInfo[x].ucOvpProtectDebounce = (y))

#define GET_TCPM_UVP_THRESHOLD(x)                               (g_pstTypeCTcpmPowerInfo[x].ucUvpThreshold)
#define SET_TCPM_UVP_THRESHOLD(x, y)                            (g_pstTypeCTcpmPowerInfo[x].ucUvpThreshold = (y))

#define GET_TCPM_UVP_VOLTAGE(x)                                 (g_pstTypeCTcpmPowerInfo[x].usUvpVol)
#define SET_TCPM_UVP_VOLTAGE(x, y)                              (g_pstTypeCTcpmPowerInfo[x].usUvpVol = (y))

#define GET_TCPM_UVP_JUDGE_DEBOUNCE(x)                          (g_pstTypeCTcpmPowerInfo[x].ucUvpProtectDebounce)
#define SET_TCPM_UVP_JUDGE_DEBOUNCE(x, y)                       (g_pstTypeCTcpmPowerInfo[x].ucUvpProtectDebounce = (y))
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
//--------------------------------------------------
// TCPM PMIC Related MACRO
//--------------------------------------------------
#define GET_TCPM_PMIC_SUPPORT(x)                                (g_pstTypeCTcpmPmicControl[x].b1PmicSupport)
#define SET_TCPM_PMIC_SUPPORT(x, y)                             (g_pstTypeCTcpmPmicControl[x].b1PmicSupport = (y))

#define GET_TCPM_PMIC_OCP_PROTECT_METHOD(x)                     (g_pstTypeCTcpmPmicControl[x].b2PmicOcpProtectMethod)
#define SET_TCPM_PMIC_OCP_PROTECT_METHOD(x, y)                  (g_pstTypeCTcpmPmicControl[x].b2PmicOcpProtectMethod = (y))

#define GET_TCPM_PMIC_OCP_JUDGE_DEBOUNCE(x)                     (g_pstTypeCTcpmPmicControl[x].ucOcpProtectDebounce)
#define SET_TCPM_PMIC_OCP_JUDGE_DEBOUNCE(x, y)                  (g_pstTypeCTcpmPmicControl[x].ucOcpProtectDebounce = (y))

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
#define GET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(x)                   (g_pstTypeCTcpmPmicControl[x].ucOcpCurrentValue)
#define SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(x, y)                (g_pstTypeCTcpmPmicControl[x].ucOcpCurrentValue = (y))

#define GET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(x)                  (g_pstTypeCTcpmPmicControl[x].ucOcpDelayShutdown)
#define SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(x, y)               (g_pstTypeCTcpmPmicControl[x].ucOcpDelayShutdown = (y))

#define GET_TCPM_PMIC_OCP_CURRENT_VALUE(x)                      (g_pstTypeCTcpmPmicControl[x].b12OcpByPollingCurrent)
#define SET_TCPM_PMIC_OCP_CURRENT_VALUE(x, y)                   (g_pstTypeCTcpmPmicControl[x].b12OcpByPollingCurrent = (y))

#define GET_TCPM_PMIC_OCP_PROTECT_TRIGGER(x)                    (g_pstTypeCTcpmPmicControl[x].b1PollingOcpProtectFlag)
#define SET_TCPM_PMIC_OCP_PROTECT_TRIGGER(x)                    (g_pstTypeCTcpmPmicControl[x].b1PollingOcpProtectFlag = _TRUE)
#define CLR_TCPM_PMIC_OCP_PROTECT_TRIGGER(x)                    (g_pstTypeCTcpmPmicControl[x].b1PollingOcpProtectFlag = _FALSE)
#endif

#if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
#define GET_TCPM_PMIC_OUTPUT_ENABLE(x)                          (g_pstTypeCTcpmPmicControl[x].b1OutputEnable)
#define SET_TCPM_PMIC_OUTPUT_ENABLE(x)                          (g_pstTypeCTcpmPmicControl[x].b1OutputEnable = _ON)
#define CLR_TCPM_PMIC_OUTPUT_ENABLE(x)                          (g_pstTypeCTcpmPmicControl[x].b1OutputEnable = _OFF)

// Macros of PMIC Bi-direction Flag
#define GET_TCPM_PMIC_BIDIR_MODE(x)                             (g_pstTypeCTcpmPmicControl[x].b1BiDirMode)
#define SET_TCPM_PMIC_BIDIR_MODE(x, y)                          (g_pstTypeCTcpmPmicControl[x].b1BiDirMode = (y))

// Macros of PMIC Protection Valid Flag
#define GET_TCPM_PMIC_PROTECT_VALID(x)                          (g_pstTypeCTcpmPmicControl[x].b1ProtectValid)
#define SET_TCPM_PMIC_PROTECT_VALID(x)                          (g_pstTypeCTcpmPmicControl[x].b1ProtectValid = _TRUE)
#define CLR_TCPM_PMIC_PROTECT_VALID(x)                          (g_pstTypeCTcpmPmicControl[x].b1ProtectValid = _FALSE)

// Macros of PMIC Protection Timer Check Flag
#define GET_TCPM_PMIC_PROTECT_TIMER_CHECK(x)                    (g_pstTypeCTcpmPmicControl[x].b1ProtectTimerCheck)
#define SET_TCPM_PMIC_PROTECT_TIMER_CHECK(x)                    (g_pstTypeCTcpmPmicControl[x].b1ProtectTimerCheck = _TRUE)
#define CLR_TCPM_PMIC_PROTECT_TIMER_CHECK(x)                    (g_pstTypeCTcpmPmicControl[x].b1ProtectTimerCheck = _FALSE)

// Macros of PMIC Protection Timer Start Flag
#define GET_TCPM_PMIC_PROTECT_TIMER_START(x)                    (g_pstTypeCTcpmPmicControl[x].b1ProtectTimerStart)
#define SET_TCPM_PMIC_PROTECT_TIMER_START(x)                    (g_pstTypeCTcpmPmicControl[x].b1ProtectTimerStart = _TRUE)
#define CLR_TCPM_PMIC_PROTECT_TIMER_START(x)                    (g_pstTypeCTcpmPmicControl[x].b1ProtectTimerStart = _FALSE)
#endif

// Macros of PMIC Check Operating Status
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
#define GET_TCPM_PMIC_GET_OMF_INFO_START(x)                     (g_pstTypeCTcpmPmicControl[x].b1GetOmfInfoFlag)
#define SET_TCPM_PMIC_GET_OMF_INFO_START(x)                     (g_pstTypeCTcpmPmicControl[x].b1GetOmfInfoFlag = _TRUE)
#define CLR_TCPM_PMIC_GET_OMF_INFO_START(x)                     (g_pstTypeCTcpmPmicControl[x].b1GetOmfInfoFlag = _FALSE)

#define GET_TCPM_PMIC_OMF_INFO(x)                               (g_pstTypeCTcpmPmicControl[x].enumOmfInfo)
#define SET_TCPM_PMIC_OMF_INFO(x, y)                            (g_pstTypeCTcpmPmicControl[x].enumOmfInfo = (y))
#endif

// Macros of PMIC Output Mode Flag
#define GET_TCPM_PMIC_OUTPUT_MODE_STATUS(x)                     (g_pstTypeCTcpmPmicControl[x].enumOutputPdoType)
#define SET_TCPM_PMIC_OUTPUT_MODE_STATUS(x, y)                  (g_pstTypeCTcpmPmicControl[x].enumOutputPdoType = (y))

// Macros of PMIC Check Support
#define GET_TCPM_PMIC_CHECK_SUPPORT(x)                          ((GET_TCPM_PD_PPS_SUPPORT(x) == _ON) ||\
                                                                 (GET_TCPM_PMIC_OCP_PROTECT_METHOD(x) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC))
#endif // End of #if(_TYPE_C_PMIC_SUPPORT == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Main Loop
extern void ScalerTypeCTcpmDefaultSetting(void);
extern void ScalerTypeCTcpmPinshareSetting(void);
extern BYTE ScalerTypeCTcpmGetPortIndex(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmSetHwShiftIndex(void);
extern void ScalerTypeCTcpmSetPRSwapOption(BYTE ucPortIndex);
extern void ScalerTypeCTcpmSetDRSwapOption(BYTE ucPortIndex);
extern void ScalerTypeCTcpmInitializeTcpc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmGetTcpcInfo(BYTE ucPortIndex);
extern EnumScalerTimerEventID ScalerTypeCTcpmEventIDMapping(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID);
extern EnumScalerWDTimerEventID ScalerTypeCTcpmWDEventIDMapping(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern void ScalerTypeCTcpmActiveTimerEvent(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmReactiveTimerEvent(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmCancelTimerEvent(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmWDCancelTimerEvent(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern void ScalerTypeCTcpmVbusCtrl(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern void ScalerTypeCTcpmVbusDetCtrl(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmVbusDischargeCtrl(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmVbusProtectStart(BYTE ucPortIndex, EnumTypeCPowerRole enumPowerRole);
extern WORD ScalerTypeCTcpmGetVbusVoltage(BYTE ucPortIndex);
extern void ScalerTypeCTcpmVconnCtrl(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmAlertControl(BYTE ucPortIndex, WORD usAlertType, bit bAction);
extern void ScalerTypeCTcpmRxIntControl(BYTE ucPortIndex, bit b1Action);
extern void ScalerTypeCTcpmToolWarningUIControl(bit bAction);
extern void ScalerTypeCTcpmSwitchPowerRole(BYTE ucPortIndex, BYTE ucTargetRole);

// CC Functions
extern void ScalerTypeCTcpmCcInitial(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcHandler(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachSetting(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachReset(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcConnectionSet(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcConnectionStart(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmCcSnkCheckUnattach(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcPowerSwitch(BYTE ucPortIndex, EnumPowerAction enumPowerAction);
extern void ScalerTypeCTcpmCcDisconnect(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcSetFunctionSupport(BYTE ucPortIndex, EnumTypeCFunctionSupport enumFunctionSupport);
extern BYTE ScalerTypeCTcpmCcDetResistor(BYTE ucPortIndex);

// PD Functions
extern void ScalerTypeCTcpmPdInitial(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdReset(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdHandler(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdReadyStateProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSrcReadyProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSnkReadyProc(BYTE ucPortIndex);
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdSrcReadyDpRxProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSnkReadyDpRxProc(BYTE ucPortIndex);
#endif
#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdSrcReadyDpTxProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSnkReadyDpTxProc(BYTE ucPortIndex);
#endif
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdAltModeProc(BYTE ucPortIndex);
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdDpAltModeDfpProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdDpAltModeDfpSendMsg(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdDpAltModeUfpProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdDpAltModeUfpSendMsg(BYTE ucPortIndex);
#endif
#endif
extern void ScalerTypeCTcpmPdSendMsg(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructMsg(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructDataObj(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructVdmDataObj(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdSendSoftRst(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeCTcpmPdConstructSoftRst(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeCTcpmPdSendHardRst(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdProcHardRst(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUpdateGoodCRCInfo(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdPowerSwitch(BYTE ucPortIndex, EnumPowerAction enumPowerAction);
extern void ScalerTypeCTcpmPdOcpOvpProc(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUnattachCancelTimerEvent(BYTE ucPortIndex);
extern bit ScalerTypeCTcpmPdTxAvaliable(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdClrHpd(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSetFunctionSupport(BYTE ucPortIndex, EnumTypeCFunctionSupport enumFunctionSupport);
extern void ScalerTypeCTcpmPdClrInteropS8Flag(BYTE ucPortIndex);

extern BYTE ScalerTypeCTcpmTcpciGetByte(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg);
extern void ScalerTypeCTcpmTcpciSetByte(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, BYTE ucData);
extern WORD ScalerTypeCTcpmTcpciGetWord(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg);
extern void ScalerTypeCTcpmTcpciSetWord(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, WORD usData);
extern void ScalerTypeCTcpmTcpciSetTxBuffer(BYTE ucPortIndex, EnumTypeCPDCmd enumPdCmd, BYTE ucTxByteCnt, WORD usMessageHeader);
extern void ScalerTypeCTcpmTcpciSetTransmit(BYTE ucPortIndex, BYTE ucTransmitInfo);

#if(_HW_TCPM_SUPPORT == _ON)
extern bit ScalerTypeCTcpmHwIICRead(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
extern bit ScalerTypeCTcpmHwIICWrite(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern void ScalerTypeCTcpmAlertAutoCtrlSetting(BYTE ucPortIndex);
extern void ScalerTypeCTcpmAlertDetCtrl(BYTE ucPortIndex, bit bAction);
extern bit ScalerTypeCTcpmFwBusyCtrl(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmAlertIntControl(BYTE ucPortIndex, WORD usAlertType, bit b1Action);
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern void ScalerTypeCTcpmPmicInitial(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPmicReset(BYTE ucPortIndex);
extern bit ScalerTypeCTcpmPmicSetting(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern bit ScalerTypeCTcpmPmicVbusDischarge(BYTE ucPortIndex, bit bEn);
extern bit ScalerTypeCTcpmPmicSwitchControl(BYTE ucPortIndex, bit bEn, bit bPowerDirection);
#if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
extern void ScalerTypeCTcpmPmicHandler(BYTE ucPortIndex);
extern bit ScalerTypeCTcpmPmicProtectTracking(BYTE ucPortIndex);
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern BYTE ScalerTypeCTcpmPmicTrackingPollingOcp(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPmicPollingOcpProtect(BYTE ucPortIndex);
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
#endif // End of #if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PMIC_SUPPORT == _ON)

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
extern void ScalerTypeCTcpmOvpUvpHandler(BYTE ucPortIndex);
#endif

// EXINT0
extern void ScalerTypeCTcpmAlertIntHandler_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmGetPortIndex_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD ScalerTypeCTcpmGetAlertType_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmGetCcStatus_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmGetFaultStatus_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmSetPdSystemEvent_EXINT0(BYTE ucPortIndex, EnumTypeCPDSysEvent enumPdSysEvent);
extern void ScalerTypeCTcpmCheckAlertValid_EXINT0(BYTE ucPortIndex);
extern EnumScalerTimerEventID ScalerTypeCTcpmEventIDMapping_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID);
extern EnumScalerWDTimerEventID ScalerTypeCTcpmWDEventIDMapping_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern void ScalerTypeCTcpmActiveTimerEvent_EXINT0(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmCancelTimerEvent_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern void ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern WORD ScalerTypeCTcpmWDTimeCtrl_EXINT0(BYTE ucPortIndex, WORD usWDTime);
extern void ScalerTypeCTcpmVbusCtrl_EXINT0(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern void ScalerTypeCTcpmVbusDetCtrl_EXINT0(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmVbusDischargeCtrl_EXINT0(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmVbusProtectStart_EXINT0(BYTE ucPortIndex, EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeCTcpmVconnCtrl_EXINT0(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmAlertControl_EXINT0(BYTE ucPortIndex, WORD usAlertType, bit bAction);
extern void ScalerTypeCTcpmRxIntControl_EXINT0(BYTE ucPortIndex, bit b1Action);
extern void ScalerTypeCTcpmToolWarningUIControl_EXINT0(bit bAction);

// CC Functions
extern void ScalerTypeCTcpmCcDrpToggleProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachSnkProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcAttachWaitSnkCheck_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcAttachWaitSnkProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcAttachSnkProc_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmCcSnkAttachSetting_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachSrcProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcAttachWaitSrcCheck_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcAttachWaitSrcProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcAttachSrcProc_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmCcSrcAttachSetting_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachSetting_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachReset_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachVthAdjust_EXINT0(BYTE ucPortIndex, WORD usVoltage);
extern void ScalerTypeCTcpmCcConnectionSet_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcConnectionStart_EXINT0(BYTE ucPortIndex);

// PD Functions
extern void ScalerTypeCTcpmPdReset_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdAttachSetting_EXINT0(BYTE ucPortIndex, bit bPowerRole);
extern void ScalerTypeCTcpmPdStartUpProc_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmPdRxMsgIdCheck_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdRxMsgDecode_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdRxReadDataObj_EXINT0(BYTE ucPortIndex, EnumTypeCPDCmdType enumCmdType);
extern void ScalerTypeCTcpmPdIntRcvMsgProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntSrcRcvMsgNoAmsProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntSnkRcvMsgNoAmsProc_EXINT0(BYTE ucPortIndex);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdIntDfpRcvVdmMsgProc_EXINT0(BYTE ucPortIndex);
#endif
extern void ScalerTypeCTcpmPdIntUfpRcvVdmMsgProc_EXINT0(BYTE ucPortIndex);
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdIntUfpRcvDpVdmMsgProc_EXINT0(BYTE ucPortIndex);
#endif
#endif
extern void ScalerTypeCTcpmPdIntRcvMsgInAmsProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdRcvSoftRstProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntRcvCableMsgProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdPrlErrHandle_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntTxSuccessProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntTxFailProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntTxCableReqSuccessProc_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdIntTxCableReqFailProc_EXINT0(BYTE ucPortIndex);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdIntTxDpVdmReqSuccessProc_EXINT0(BYTE ucPortIndex);
#endif
extern void ScalerTypeCTcpmPdIntTxVdmRespSuccessProc_EXINT0(BYTE ucPortIndex);
#endif
extern void ScalerTypeCTcpmPdSendMsg_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructMsg_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructDataObj_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern BYTE ScalerTypeCTcpmPdSetVdmDataObjCnt_EXINT0(BYTE ucPortIndex, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructVdmDataObj_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdSetProductTypeVDO_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSendSoftRst_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeCTcpmPdConstructSoftRst_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeCTcpmPdSendHardRst_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdProcHardRst_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUnattachCancelTimerEvent_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSaveCableDiscoverIdAckInfo_EXINT0(BYTE ucPortIndex);
extern EnumTypeCPDRequestValid ScalerTypeCTcpmPdCheckRequestValid_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdBackToReadyState_EXINT0(BYTE ucPortIndex);
extern EnumTypeCPDSrcCapValid ScalerTypeCTcpmPdCheckSrcCapValid_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmPdCheckPowerContractValid_EXINT0(BYTE ucPortIndex);
extern EnumTypeCPDRebuildPowerContract ScalerTypeCTcpmPdCheckRebuildPowerContract_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdClrHpd_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdClrInteropS8Flag_EXINT0(BYTE ucPortIndex);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
extern BYTE ScalerTypeCTcpmPdSearchSvid_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSearchMode_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUpdatePortPartnerDpStatus_EXINT0(BYTE ucPortIndex, EnumTypeCVdmDpCmd enumVdmDpCmd);
extern EnumTypeCPDDpStatusCheckResult ScalerTypeCTcpmPdCheckDpStatus_EXINT0(BYTE ucPortIndex);
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
extern EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableId_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSearchCableSvid_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSaveCableDpModeInfo_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSaveCableTbt3ModeInfo_EXINT0(BYTE ucPortIndex);
extern EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(BYTE ucPortIndex);
extern EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableTbt3Mode_EXINT0(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUfpSaveCableInfoForDpcd_EXINT0(BYTE ucPortIndex);
#endif
extern BYTE ScalerTypeCTcpmPdCheckDpConfig_EXINT0(BYTE ucPortIndex);
extern BYTE ScalerTypeCTcpmPdDfpJudgePinAssignment_EXINT0(BYTE ucPortIndex);
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
extern void ScalerTypeCTcpmPdPopHpd_EXINT0(BYTE ucPortIndex);
#endif // End of #if (_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
extern EnumTypeCPDHpdType ScalerTypeCTcpmPdDecodePartnerHpdStatus_EXINT0(void);
#endif // End of #if (_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
#endif // End of #if (_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
#endif // End of #if (_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

extern BYTE ScalerTypeCTcpmTcpciGetByte_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg);
extern void ScalerTypeCTcpmTcpciSetByte_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, BYTE ucData);
extern WORD ScalerTypeCTcpmTcpciGetWord_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg);
extern void ScalerTypeCTcpmTcpciSetWord_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, WORD usData);
extern void ScalerTypeCTcpmTcpciSetTxBuffer_EXINT0(BYTE ucPortIndex, EnumTypeCPDCmd enumPdCmd, BYTE ucTxByteCnt, WORD usMessageHeader);
extern void ScalerTypeCTcpmTcpciSetTransmit_EXINT0(BYTE ucPortIndex, BYTE ucTransmitInfo);
extern void ScalerTypeCTcpmTcpciGetRxBuffer_EXINT0(BYTE ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
extern bit ScalerTypeCTcpmHwIICRead_EXINT0(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
extern bit ScalerTypeCTcpmHwIICWrite_EXINT0(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern void ScalerTypeCTcpmAlertDetCtrl_EXINT0(BYTE ucPortIndex, bit bAction);
extern bit ScalerTypeCTcpmFwBusyCtrl_EXINT0(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmAlertIntControl_EXINT0(BYTE ucPortIndex, WORD usAlertType, bit b1Action);
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern void ScalerTypeCTcpmPmicReset_EXINT0(BYTE ucPortIndex);
extern bit ScalerTypeCTcpmPmicSetting_EXINT0(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern bit ScalerTypeCTcpmPmicVbusDischarge_EXINT0(BYTE ucPortIndex, bit bEn);
extern bit ScalerTypeCTcpmPmicSwitchControl_EXINT0(BYTE ucPortIndex, bit bEn, bit bPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicOperationMode ScalerTypeCTcpmPmicReadPpsOperationModeStatus_EXINT0(BYTE ucPortIndex);
extern bit ScalerTypeCTcpmGetPmicAlertDetectStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif


// WDINT
extern BYTE ScalerTypeCTcpmGetPortIndex_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumScalerTimerEventID ScalerTypeCTcpmEventIDMapping_WDINT(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID);
extern EnumScalerWDTimerEventID ScalerTypeCTcpmWDEventIDMapping_WDINT(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern void ScalerTypeCTcpmActiveTimerEvent_WDINT(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmCancelTimerEvent_WDINT(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmWDActiveTimerEvent_WDINT(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern void ScalerTypeCTcpmWDCancelTimerEvent_WDINT(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID);
extern WORD ScalerTypeCTcpmWDTimeCtrl_WDINT(BYTE ucPortIndex, WORD usWDTime);
extern void ScalerTypeCTcpmVbusCtrl_WDINT(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern void ScalerTypeCTcpmVbusDetCtrl_WDINT(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmVbusDischargeCtrl_WDINT(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmVbusProtectStart_WDINT(BYTE ucPortIndex, EnumTypeCPowerRole enumPowerRole);
extern BYTE ScalerTypeCTcpmCheckVbusReady_WDINT(BYTE ucPortIndex, WORD usVoltage);
extern WORD ScalerTypeCTcpmGetVbusVoltage_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmVconnCtrl_WDINT(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmAlertControl_WDINT(BYTE ucPortIndex, WORD usAlertType, bit bAction);
extern void ScalerTypeCTcpmRxIntControl_WDINT(BYTE ucPortIndex, bit b1Action);
extern void ScalerTypeCTcpmToolWarningUIControl_WDINT(bit bAction);
extern void ScalerTypeCTcpmSwitchPowerRole_WDINT(BYTE ucPortIndex, BYTE ucTargetRole);

// CC Functions
extern void ScalerTypeCTcpmCcUnattachSetting_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcUnattachReset_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcConnectionSet_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmCcConnectionStart_WDINT(BYTE ucPortIndex);

// PD Functions
extern void ScalerTypeCTcpmPdReset_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdWDTimerEventCableProc_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdSendMsg_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructMsg_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructDataObj_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdConstructVdmDataObj_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeCTcpmPdSendSoftRst_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeCTcpmPdConstructSoftRst_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeCTcpmPdSendHardRst_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdProcHardRst_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUpdateGoodCRCInfo_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdBackToReadyState_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdUnattachCancelTimerEvent_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdClrHpd_WDINT(BYTE ucPortIndex);
extern void ScalerTypeCTcpmPdPushHpd_WDINT(BYTE ucPortIndex, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern void ScalerTypeCTcpmPdClrInteropS8Flag_WDINT(BYTE ucPortIndex);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
extern EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableDpFunctionality_WDINT(BYTE ucPortIndex);
#endif
#endif
#endif

extern BYTE ScalerTypeCTcpmTcpciGetByte_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg);
extern void ScalerTypeCTcpmTcpciSetByte_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, BYTE ucData);
extern WORD ScalerTypeCTcpmTcpciGetWord_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg);
extern void ScalerTypeCTcpmTcpciSetWord_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, WORD usData);
extern void ScalerTypeCTcpmTcpciSetTxBuffer_WDINT(BYTE ucPortIndex, EnumTypeCPDCmd enumPdCmd, BYTE ucTxByteCnt, WORD usMessageHeader);
extern void ScalerTypeCTcpmTcpciSetTransmit_WDINT(BYTE ucPortIndex, BYTE ucTransmitInfo);

#if(_HW_TCPM_SUPPORT == _ON)
extern bit ScalerTypeCTcpmHwIICRead_WDINT(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
extern bit ScalerTypeCTcpmHwIICWrite_WDINT(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern void ScalerTypeCTcpmAlertDetCtrl_WDINT(BYTE ucPortIndex, bit bAction);
extern bit ScalerTypeCTcpmFwBusyCtrl_WDINT(BYTE ucPortIndex, bit bAction);
extern void ScalerTypeCTcpmAlertIntControl_WDINT(BYTE ucPortIndex, WORD usAlertType, bit b1Action);
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern void ScalerTypeCTcpmPmicReset_WDINT(BYTE ucPortIndex);
extern bit ScalerTypeCTcpmPmicSetting_WDINT(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern bit ScalerTypeCTcpmPmicVbusDischarge_WDINT(BYTE ucPortIndex, bit bEn);
extern bit ScalerTypeCTcpmPmicSwitchControl_WDINT(BYTE ucPortIndex, bit bEn, bit bPowerDirection);
#endif

#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_TCPM_H__
