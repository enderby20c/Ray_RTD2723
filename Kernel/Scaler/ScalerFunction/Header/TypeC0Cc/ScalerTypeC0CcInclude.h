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
// ID Code      : ScalerTypeC0CcInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Type C Related Definition
//--------------------------------------------------
#if(_EMB_TYPE_C_0_MAPPING == _VALUE_D0_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _D0_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _D0_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _D0_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _D0_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _D0_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _D0_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _D0_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _D0_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _D0_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _D0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_D1_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _D1_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _D1_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _D1_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _D1_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _D1_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _D1_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _D1_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _D1_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _D1_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _D1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_D2_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _D2_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _D2_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _D2_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _D2_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _D2_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _D2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _D2_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _D2_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _D2_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _D2_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _D2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P0_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _P0_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _P0_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _P0_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _P0_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _P0_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _P0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _P0_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _P0_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _P0_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _P0_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _P0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P1_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _P1_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _P1_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _P1_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _P1_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _P1_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _P1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _P1_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _P1_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _P1_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _P1_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _P1_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _P1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P2_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _P2_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _P2_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _P2_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _P2_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _P2_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _P2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _P2_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _P2_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _P2_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _P2_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _P2_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _P2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P3_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _P3_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _P3_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _P3_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _P3_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _P3_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _P3_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _P3_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _P3_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _P3_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _P3_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _P3_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _P3_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_P4_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _P4_USB_HUB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _P4_USB_SPEED
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _P4_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _P4_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _P4_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _P4_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _P4_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _P4_TYPE_C_EMB_USB_ROLE
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _P4_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _P4_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _P4_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _P4_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF

#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
#define _EMB_TYPE_C_0_USB_TYPE                                  _ADAPTOR_TYPE_C_USB_TYPE
#define _EMB_TYPE_C_0_USB_SPEED                                 _USB_BILLBOARD_ONLY
#define _EMB_TYPE_C_0_SRC_DEF_CUR                               _ADAPTOR_TYPE_C_EMB_SRC_DEF_CUR
#define _EMB_TYPE_C_0_AC_ON_RECONNECT                           _ADAPTOR_TYPE_C_CC_AC_ON_RECONNECT
#define _EMB_TYPE_C_0_PD3_PPS_SUPPORT                           _ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT                        _ADAPTOR_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _EMB_TYPE_C_0_PD3_1_EPR_SUPPORT                         _ADAPTOR_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _EMB_TYPE_C_0_USB_ROLE                                  _TYPE_C_USB_NOT_SUPPORT
#define _EMB_TYPE_C_0_CONNECTOR_TYPE                            _ADAPTOR_TYPE_C_EMB_CONNECTOR_TYPE
#define _EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT                       _ADAPTOR_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT                   _ADAPTOR_TYPE_C_MODAL_OPERATION_SUPPORT
#define _EMB_TYPE_C_0_PD_BEHAVIOR_TYPE                          _ADAPTOR_TYPE_C_EMB_PD_BEHAVIOR_TYPE
#define _EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF                _ADAPTOR_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF
#endif

//--------------------------------------------------
// Type C Related MACRO
//--------------------------------------------------
#define GET_TYPE_C_0_CC_CC1_R()                                 (g_stTypeC0CcInfo.b3CC1Resistor)         // _OPEN / _RA / _RD / _RP_DEF / _RP_1P5A / _RP_3A
#define SET_TYPE_C_0_CC_CC1_R(x)                                (g_stTypeC0CcInfo.b3CC1Resistor = (x))

#define GET_TYPE_C_0_CC_CC2_R()                                 (g_stTypeC0CcInfo.b3CC2Resistor)         // _OPEN / _RA / _RD / _RP_DEF / _RP_1P5A / _RP_3A
#define SET_TYPE_C_0_CC_CC2_R(x)                                (g_stTypeC0CcInfo.b3CC2Resistor = (x))

#define GET_TYPE_C_0_CC_ORIENTATION()                           (g_stTypeC0CcInfo.enumOrientation)  // _TYPE_C_ORIENTATION_FLIP / _TYPE_C_ORIENTATION_UNFLIP
#define SET_TYPE_C_0_CC_ORIENTATION(x)                          (g_stTypeC0CcInfo.enumOrientation = (x))

#define GET_TYPE_C_0_CC_ATTACHED()                              (g_stTypeC0CcInfo.b1CCAttached)
#define SET_TYPE_C_0_CC_ATTACHED()                              (g_stTypeC0CcInfo.b1CCAttached = _TRUE)
#define CLR_TYPE_C_0_CC_ATTACHED()                              (g_stTypeC0CcInfo.b1CCAttached = _FALSE)

#define GET_TYPE_C_0_CC_DEF_CUR()                               ((WORD)(g_stTypeC0CcInfo.b10DefCurrent))
#define SET_TYPE_C_0_CC_DEF_CUR(x)                              (g_stTypeC0CcInfo.b10DefCurrent = (x))

#define GET_TYPE_C_0_CC_VCONN_STATUS()                          ((bit)(g_stTypeC0CcInfo.b1VconnStatus))
#define SET_TYPE_C_0_CC_VCONN_STATUS(x)                         (g_stTypeC0CcInfo.b1VconnStatus = (x))

#define GET_TYPE_C_0_CC_ERROR_RECOVERY()                        ((bit)(g_stTypeC0CcInfo.b1Error))
#define SET_TYPE_C_0_CC_ERROR_RECOVERY()                        (g_stTypeC0CcInfo.b1Error = _TRUE)
#define CLR_TYPE_C_0_CC_ERROR_RECOVERY()                        (g_stTypeC0CcInfo.b1Error = _FALSE)

#define GET_TYPE_C_0_CC_PORT_ROLE()                             (g_stTypeC0CcInfo.b2PortRole)
#define SET_TYPE_C_0_CC_PORT_ROLE(x)                            (g_stTypeC0CcInfo.b2PortRole = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructTypeCEmbInfo g_stTypeC0CcInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Main Loop Funtions : ScalerTypeC0Cc.c
extern void ScalerTypeC0CcClkSel(BYTE ucClockSel);
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
extern void ScalerTypeC0CcVbusPoweredSnkInitial(void);
#endif
extern void ScalerTypeC0CcHandler(void);
extern void ScalerTypeC0CcTimerEventProc(EnumScalerTimerEventID enumEventID);
extern void ScalerTypeC0CcSetDischargeCount(BYTE ucDischargeCount);
// extern void ScalerTypeC0CcBackupDataControl(EnumTypeCCCBackupDataControl enumDataControl);
extern void ScalerTypeC0CcFWModeSetResistor(EnumTypeCCCPin enumCCPin, EnumTypeCCCFWModeSetResistor enumFWModeSetResistor);
extern void ScalerTypeC0CcSnkDetRpCtrl(bit bAction);
extern void ScalerTypeC0CcVconnControl(bit bAction);
extern void ScalerTypeC0CcVbusDetCtrl(bit bAction);
extern BYTE ScalerTypeC0CcDetResistor(void);
extern void ScalerTypeC0CcSwitchPowerRole(BYTE ucTargetRole);
extern void ScalerTypeC0CcPowerSwitch(EnumPowerAction enumPowerAction);
extern void ScalerTypeC0CcFunctionControl(EnumTypeCCcFunction enumCcFunction);
extern void ScalerTypeC0CcSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport);
extern void ScalerTypeC0CcSetOperationMode(EnumTypeCOperationMode enumOperationMode);
#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
extern void ScalerTypeC0CcToolWarningUIControl(bit bAction);
#endif  // End of #if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)

// EXINT Funtions : ScalerTypeC0Cc_EXINT.c
extern void ScalerTypeC0CcIntHandler_EXINT0(void);
extern void ScalerTypeC0CcSnkDetRpCtrl_EXINT0(bit bAction);
extern void ScalerTypeC0CcVconnControl_EXINT0(bit bAction);
/*
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
extern void ScalerTypeC0CcFWModeTurnOffVconn_EXINT0(void);
#endif  // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
*/
extern void ScalerTypeC0CcVbusDetCtrl_EXINT0(bit bAction);
extern BYTE ScalerTypeC0CcDetResistor_EXINT0(void);
extern BYTE ScalerTypeC0CcGetHWState_EXINT0(void);
extern bit ScalerTypeC0CcGetTryWaitSNKState_EXINT0(void);
extern void ScalerTypeC0CcFWModeTrySrcAttached_EXINT0(void);
#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
extern void ScalerTypeC0CcToolWarningUIControl_EXINT0(bit bAction);
#endif  // End of #if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
extern void ScalerTypeC0CcWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
extern void ScalerTypeC0CcVconnControl_WDINT(bit bAction);
extern void ScalerTypeC0CcVbusDetCtrl_WDINT(bit bAction);
extern BYTE ScalerTypeC0CcDetResistor_WDINT(void);
extern void ScalerTypeC0CcSwitchPowerRole_WDINT(BYTE ucTargetRole);
#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
extern void ScalerTypeC0CcToolWarningUIControl_WDINT(bit bAction);
#endif  // End of #if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))

#if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)) || ((_TYPE_C_GPIO_MODE_SUPPORT == _ON) && (_HW_EMB_TYPE_C_0_SUPPORT == _ON)))
extern void ScalerTypeC0CcLoadTrimming(void);
#endif

#if((_TYPE_C_GPIO_MODE_SUPPORT == _ON) && (_HW_EMB_TYPE_C_0_SUPPORT == _ON))
extern void ScalerTypeC0CcGpioModeInitialSetting(void);
extern EnumTypeCCcDetectStatus ScalerTypeC0CcGetCcPinStatus(EnumTypeCChannel enumTypeCChannel);
#endif
