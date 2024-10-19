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
// ID Code      : ScalerTypeC0Pd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TYPEC0_PD_H__
#define __SCALER_TYPEC0_PD_H__


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

// Status Setting Macros
#define GET_TYPE_C_0_PD_FW_STATE()                      (g_stTypeC0PdStatus.b8PDState)
#define SET_TYPE_C_0_PD_FW_STATE(x)                     (g_stTypeC0PdStatus.b8PDState = (x))

#define GET_TYPE_C_0_PD_SUB_STATE()                     (g_stTypeC0PdStatus.b8PDSubState)
#define SET_TYPE_C_0_PD_SUB_STATE(x)                    (g_stTypeC0PdStatus.b8PDSubState = (x))

#define GET_TYPE_C_0_PD_CBL_STATE()                     (g_stTypeC0PdCableInfo.b4CableState)
#define SET_TYPE_C_0_PD_CBL_STATE(x)                    (g_stTypeC0PdCableInfo.b4CableState = (x))

#define GET_TYPE_C_0_PD_DP_ALT_STATE()                  (g_stTypeC0PdStatus.b8PDDpAltState)
#define SET_TYPE_C_0_PD_DP_ALT_STATE(x)                 (g_stTypeC0PdStatus.b8PDDpAltState = (x))

#define GET_TYPE_C_0_PD_LENOVO_ALT_STATE()              (g_stTypeC0PdStatus.b6PDLenovoAltState)
#define SET_TYPE_C_0_PD_LENOVO_ALT_STATE(x)             (g_stTypeC0PdStatus.b6PDLenovoAltState = (x))

#define GET_TYPE_C_0_PD_AMS_STATUS()                    (g_stTypeC0PdStatus.b2PDAmsStatus)
#define SET_TYPE_C_0_PD_AMS_STATUS(x)                   (g_stTypeC0PdStatus.b2PDAmsStatus = (x))

#define GET_TYPE_C_0_PD_EXPLICIT_CONTRACT()             (g_stTypeC0PdStatus.b1PDPowerContract)
#define SET_TYPE_C_0_PD_EXPLICIT_CONTRACT()             (g_stTypeC0PdStatus.b1PDPowerContract = _TRUE)
#define CLR_TYPE_C_0_PD_EXPLICIT_CONTRACT()             (g_stTypeC0PdStatus.b1PDPowerContract = _FALSE)

#define GET_TYPE_C_0_PD_UNCONSTRAIN_POWER()             (g_stTypeC0PdStatus.b1UnconstrainedPower)
#define SET_TYPE_C_0_PD_UNCONSTRAIN_POWER(x)            (g_stTypeC0PdStatus.b1UnconstrainedPower = (x))

#define GET_TYPE_C_0_PD_HANDLER_ONGOING()               (g_stTypeC0PdStatus.b1PDHandlerOngoing)
#define SET_TYPE_C_0_PD_HANDLER_ONGOING()               (g_stTypeC0PdStatus.b1PDHandlerOngoing = _TRUE)
#define CLR_TYPE_C_0_PD_HANDLER_ONGOING()               (g_stTypeC0PdStatus.b1PDHandlerOngoing = _FALSE)

// Cable Info Related Macro
#define GET_TYPE_C_0_PD_CBL_SPEC_VER()                  ((BYTE)(g_stTypeC0PdCableInfo.b2CableSpecVer))
#define SET_TYPE_C_0_PD_CBL_SPEC_VER(x)                 (g_stTypeC0PdCableInfo.b2CableSpecVer = (x))

#define GET_TYPE_C_0_PD_CBL_MAX_CUR()                   ((WORD)(g_stTypeC0PdCableInfo.b10CableMaxCur))
#define SET_TYPE_C_0_PD_CBL_MAX_CUR(x)                  (g_stTypeC0PdCableInfo.b10CableMaxCur = (x))

#define GET_TYPE_C_0_PD_CBL_PD_CAPABILITY()             (g_stTypeC0PdCableInfo.enumTypeCCablePdCap)
#define SET_TYPE_C_0_PD_CBL_PD_CAPABILITY(x)            (g_stTypeC0PdCableInfo.enumTypeCCablePdCap = (x))

#define GET_TYPE_C_0_PD_CBL_PRODUCT_TYPE()              (g_stTypeC0PdCableInfo.enumTypeCCableProductType)
#define SET_TYPE_C_0_PD_CBL_PRODUCT_TYPE(x)             (g_stTypeC0PdCableInfo.enumTypeCCableProductType = (x))

#define GET_TYPE_C_0_PD_CBL_MODAL_OPERATION_SUPPORT()   (g_stTypeC0PdCableInfo.b1CableModalOperation)
#define SET_TYPE_C_0_PD_CBL_MODAL_OPERATION_SUPPORT()   (g_stTypeC0PdCableInfo.b1CableModalOperation = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_MODAL_OPERATION_SUPPORT()   (g_stTypeC0PdCableInfo.b1CableModalOperation = _FALSE)

#define GET_TYPE_C_0_PD_CBL_CONNECTOR_TYPE()            (g_stTypeC0PdCableInfo.enumTypeCCableConnectorType)
#define SET_TYPE_C_0_PD_CBL_CONNECTOR_TYPE(x)           (g_stTypeC0PdCableInfo.enumTypeCCableConnectorType = (x))

#define GET_TYPE_C_0_PD_CBL_EPR_MODE_CAPABLE()          (g_stTypeC0PdCableInfo.b1CableEprModeCapable)
#define SET_TYPE_C_0_PD_CBL_EPR_MODE_CAPABLE()          (g_stTypeC0PdCableInfo.b1CableEprModeCapable = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_EPR_MODE_CAPABLE()          (g_stTypeC0PdCableInfo.b1CableEprModeCapable = _FALSE)

#define GET_TYPE_C_0_PD_CBL_TERMINATION_TYPE()          (g_stTypeC0PdCableInfo.enumTypeCCableTerminationType)
#define SET_TYPE_C_0_PD_CBL_TERMINATION_TYPE(x)         (g_stTypeC0PdCableInfo.enumTypeCCableTerminationType = (x))

#define GET_TYPE_C_0_PD_CBL_VCONN_REQUIRED()            (g_stTypeC0PdCableInfo.b1CableVconnRequired)
#define SET_TYPE_C_0_PD_CBL_VCONN_REQUIRED()            (g_stTypeC0PdCableInfo.b1CableVconnRequired = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_VCONN_REQUIRED()            (g_stTypeC0PdCableInfo.b1CableVconnRequired = _FALSE)

#define GET_TYPE_C_0_PD_CBL_MAX_VOL()                   (g_stTypeC0PdCableInfo.b10CableMaxVol)
#define SET_TYPE_C_0_PD_CBL_MAX_VOL(x)                  (g_stTypeC0PdCableInfo.b10CableMaxVol = (x))

#define GET_TYPE_C_0_PD_CBL_SBU_SUPPORT()               (g_stTypeC0PdCableInfo.b1CableSbuSupport)
#define SET_TYPE_C_0_PD_CBL_SBU_SUPPORT()               (g_stTypeC0PdCableInfo.b1CableSbuSupport = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_SBU_SUPPORT()               (g_stTypeC0PdCableInfo.b1CableSbuSupport = _FALSE)

#define GET_TYPE_C_0_PD_CBL_SBU_TYPE()                  (g_stTypeC0PdCableInfo.enumTypeCCableSbuType)
#define SET_TYPE_C_0_PD_CBL_SBU_TYPE(x)                 (g_stTypeC0PdCableInfo.enumTypeCCableSbuType = (x))

#define GET_TYPE_C_0_PD_CBL_USB_HIGHEST_SPEED()         (g_stTypeC0PdCableInfo.enumTypeCCableUsbHighestSpeed)
#define SET_TYPE_C_0_PD_CBL_USB_HIGHEST_SPEED(x)        (g_stTypeC0PdCableInfo.enumTypeCCableUsbHighestSpeed = (x))

#define GET_TYPE_C_0_PD_CBL_VBUS_THROUGH()              (g_stTypeC0PdCableInfo.b1CableVbusThrough)
#define SET_TYPE_C_0_PD_CBL_VBUS_THROUGH()              (g_stTypeC0PdCableInfo.b1CableVbusThrough = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_VBUS_THROUGH()              (g_stTypeC0PdCableInfo.b1CableVbusThrough = _FALSE)

#define GET_TYPE_C_0_PD_CBL_SOP_PP_SUPPORT()            (g_stTypeC0PdCableInfo.b1CableSopPP)
#define SET_TYPE_C_0_PD_CBL_SOP_PP_SUPPORT()            (g_stTypeC0PdCableInfo.b1CableSopPP = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_SOP_PP_SUPPORT()            (g_stTypeC0PdCableInfo.b1CableSopPP = _FALSE)

#define GET_TYPE_C_0_PD_CBL_U3_TO_U0_TRANSITION_MODE()  (g_stTypeC0PdCableInfo.enumTypeCCableU3ToU0TransitionMode)
#define SET_TYPE_C_0_PD_CBL_U3_TO_U0_TRANSITION_MODE(x) (g_stTypeC0PdCableInfo.enumTypeCCableU3ToU0TransitionMode = (x))

#define GET_TYPE_C_0_PD_CBL_USB_4_SUPPORT()             (g_stTypeC0PdCableInfo.b1CableUSB4)
#define SET_TYPE_C_0_PD_CBL_USB_4_SUPPORT()             (g_stTypeC0PdCableInfo.b1CableUSB4 = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_USB_4_SUPPORT()             (g_stTypeC0PdCableInfo.b1CableUSB4 = _FALSE)

#define GET_TYPE_C_0_PD_CBL_USB_3_2_SUPPORT()           (g_stTypeC0PdCableInfo.b1CableUSB3_2)
#define SET_TYPE_C_0_PD_CBL_USB_3_2_SUPPORT()           (g_stTypeC0PdCableInfo.b1CableUSB3_2 = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_USB_3_2_SUPPORT()           (g_stTypeC0PdCableInfo.b1CableUSB3_2 = _FALSE)

#define GET_TYPE_C_0_PD_CBL_LANES_SUPPORT()             (g_stTypeC0PdCableInfo.enumTypeCCableUsbLanesSupport)
#define SET_TYPE_C_0_PD_CBL_LANES_SUPPORT(x)            (g_stTypeC0PdCableInfo.enumTypeCCableUsbLanesSupport = (x))

#define GET_TYPE_C_0_PD_CBL_CHARGE_THROUGH_SUPPORT()    (g_stTypeC0PdCableInfo.b1ChargeThroughSupport)
#define SET_TYPE_C_0_PD_CBL_CHARGE_THROUGH_SUPPORT()    (g_stTypeC0PdCableInfo.b1ChargeThroughSupport = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_CHARGE_THROUGH_SUPPORT()    (g_stTypeC0PdCableInfo.b1ChargeThroughSupport = _FALSE)

#define GET_TYPE_C_0_PD_CBL_SOFT_RESET_REQUIRED()       (g_stTypeC0PdCableInfo.b1CableSoftRstReq)
#define SET_TYPE_C_0_PD_CBL_SOFT_RESET_REQUIRED()       (g_stTypeC0PdCableInfo.b1CableSoftRstReq = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_SOFT_RESET_REQUIRED()       (g_stTypeC0PdCableInfo.b1CableSoftRstReq = _FALSE)

#define GET_TYPE_C_0_PD_CBL_ENTER_DP_MODE_SUPPORT()     (g_stTypeC0PdCableInfo.b1CableDpEnterDpModeSupport)
#define SET_TYPE_C_0_PD_CBL_ENTER_DP_MODE_SUPPORT()     (g_stTypeC0PdCableInfo.b1CableDpEnterDpModeSupport = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_ENTER_DP_MODE_SUPPORT()     (g_stTypeC0PdCableInfo.b1CableDpEnterDpModeSupport = _FALSE)

#define GET_TYPE_C_0_PD_CBL_SVID_SEARCH_FINISH()        (g_stTypeC0PdCableInfo.b1CableSvidSearchFinish)
#define SET_TYPE_C_0_PD_CBL_SVID_SEARCH_FINISH()        (g_stTypeC0PdCableInfo.b1CableSvidSearchFinish = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_SVID_SEARCH_FINISH()        (g_stTypeC0PdCableInfo.b1CableSvidSearchFinish = _FALSE)

#define GET_TYPE_C_0_PD_CBL_DP_SVID_SUPPORT()           (g_stTypeC0PdCableInfo.b1CableDpSvidSupport)
#define SET_TYPE_C_0_PD_CBL_DP_SVID_SUPPORT()           (g_stTypeC0PdCableInfo.b1CableDpSvidSupport = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_DP_SVID_SUPPORT()           (g_stTypeC0PdCableInfo.b1CableDpSvidSupport = _FALSE)

#define GET_TYPE_C_0_PD_CBL_DP_MODE_INFO_RECEIVED()     (g_stTypeC0PdCableInfo.b1CableDpModeInfoReceived)
#define SET_TYPE_C_0_PD_CBL_DP_MODE_INFO_RECEIVED()     (g_stTypeC0PdCableInfo.b1CableDpModeInfoReceived = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_DP_MODE_INFO_RECEIVED()     (g_stTypeC0PdCableInfo.b1CableDpModeInfoReceived = _FALSE)

#define GET_TYPE_C_0_PD_CBL_TBT3_SVID_SUPPORT()         (g_stTypeC0PdCableInfo.b1CableTbt3SvidSupport)
#define SET_TYPE_C_0_PD_CBL_TBT3_SVID_SUPPORT()         (g_stTypeC0PdCableInfo.b1CableTbt3SvidSupport = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_TBT3_SVID_SUPPORT()         (g_stTypeC0PdCableInfo.b1CableTbt3SvidSupport = _FALSE)

#define GET_TYPE_C_0_PD_CBL_SVDM_VERSION()              (g_stTypeC0PdCableInfo.enumTypeCCableSvdmVersion)
#define SET_TYPE_C_0_PD_CBL_SVDM_VERSION(x)             (g_stTypeC0PdCableInfo.enumTypeCCableSvdmVersion = (x))

#define GET_TYPE_C_0_PD_CBL_DPAM_VERSION()              (g_stTypeC0PdCableInfo.enumTypeCCableDpamVersion)
#define SET_TYPE_C_0_PD_CBL_DPAM_VERSION(x)             (g_stTypeC0PdCableInfo.enumTypeCCableDpamVersion = (x))

#define GET_TYPE_C_0_PD_CBL_PIN_ASSIGNMENT()            (g_stTypeC0PdCableInfo.enumTypeCCablePinAssignment)
#define SET_TYPE_C_0_PD_CBL_PIN_ASSIGNMENT(x)           (g_stTypeC0PdCableInfo.enumTypeCCablePinAssignment = (x))

#define GET_TYPE_C_0_PD_CBL_TBT3_PRODUCT_TYPE()         (g_stTypeC0PdCableInfo.enumTypeCCableTbt3ProductType)
#define SET_TYPE_C_0_PD_CBL_TBT3_PRODUCT_TYPE(x)        (g_stTypeC0PdCableInfo.enumTypeCCableTbt3ProductType = (x))

#define GET_TYPE_C_0_PD_CBL_TBT3_DIRECTION()            (g_stTypeC0PdCableInfo.enumTypeCCableTbt3Direction)
#define SET_TYPE_C_0_PD_CBL_TBT3_DIRECTION(x)           (g_stTypeC0PdCableInfo.enumTypeCCableTbt3Direction = (x))

#define GET_TYPE_C_0_PD_CBL_TBT3_RETIMER()              (g_stTypeC0PdCableInfo.b1CableTbt3Retimer)
#define SET_TYPE_C_0_PD_CBL_TBT3_RETIMER()              (g_stTypeC0PdCableInfo.b1CableTbt3Retimer = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_TBT3_RETIMER()              (g_stTypeC0PdCableInfo.b1CableTbt3Retimer = _FALSE)

#define GET_TYPE_C_0_PD_CBL_TBT3_OPTICAL()              (g_stTypeC0PdCableInfo.b1CableTbt3Optical)
#define SET_TYPE_C_0_PD_CBL_TBT3_OPTICAL()              (g_stTypeC0PdCableInfo.b1CableTbt3Optical = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_TBT3_OPTICAL()              (g_stTypeC0PdCableInfo.b1CableTbt3Optical = _FALSE)

#define GET_TYPE_C_0_PD_CBL_TBT3_ROUNDED_SUPPORT()      (g_stTypeC0PdCableInfo.enumTypeCCableTbt3RoundedSupport)
#define SET_TYPE_C_0_PD_CBL_TBT3_ROUNDED_SUPPORT(x)     (g_stTypeC0PdCableInfo.enumTypeCCableTbt3RoundedSupport = (x))

#define GET_TYPE_C_0_PD_CBL_TBT3_SPEED()                (g_stTypeC0PdCableInfo.enumTypeCCableTbt3Speed)
#define SET_TYPE_C_0_PD_CBL_TBT3_SPEED(x)               (g_stTypeC0PdCableInfo.enumTypeCCableTbt3Speed = (x))

#define GET_TYPE_C_0_PD_CBL_ACTIVE_COMPONENT()          (g_stTypeC0PdCableInfoForDpcd.enumTypeCCableActiveComponent)
#define SET_TYPE_C_0_PD_CBL_ACTIVE_COMPONENT(x)         (g_stTypeC0PdCableInfoForDpcd.enumTypeCCableActiveComponent = (x))

#define GET_TYPE_C_0_PD_CBL_UHBR13P5_SUPPORT()          (g_stTypeC0PdCableInfoForDpcd.b1CableUhbr13p5Support)
#define SET_TYPE_C_0_PD_CBL_UHBR13P5_SUPPORT()          (g_stTypeC0PdCableInfoForDpcd.b1CableUhbr13p5Support = _TRUE)
#define CLR_TYPE_C_0_PD_CBL_UHBR13P5_SUPPORT()          (g_stTypeC0PdCableInfoForDpcd.b1CableUhbr13p5Support = _FALSE)

#define GET_TYPE_C_0_PD_CBL_MAX_DP_RATE()               (g_stTypeC0PdCableInfoForDpcd.enumTypeCCableMaxDpRate)
#define SET_TYPE_C_0_PD_CBL_MAX_DP_RATE(x)              (g_stTypeC0PdCableInfoForDpcd.enumTypeCCableMaxDpRate = (x))

// Role Setting Macro
#define GET_TYPE_C_0_PD_DATA_ROLE()                     (BYTE)(g_stTypeC0PdStatus.b1PDDataRole)
#define SET_TYPE_C_0_PD_DATA_ROLE(x)                    (g_stTypeC0PdStatus.b1PDDataRole = (x))

#define GET_TYPE_C_0_PD_VCONN_ROLE()                    (BYTE)(g_stTypeC0PdStatus.b1PDVconnRole)
#define SET_TYPE_C_0_PD_VCONN_ROLE(x)                   (g_stTypeC0PdStatus.b1PDVconnRole = (x))

#define GET_TYPE_C_0_PD_SPEC_VER()                      ((BYTE)(g_stTypeC0PdStatus.b2SpecVersion))
#define SET_TYPE_C_0_PD_SPEC_VER(x)                     (g_stTypeC0PdStatus.b2SpecVersion = (x))

// PD EXINT Set Timer Event Macro
#define GET_TYPE_C_0_PD_TIMER_EVENT_VALID()             (g_stTypeC0PdTimerEvent.b1Valid)
#define SET_TYPE_C_0_PD_TIMER_EVENT_VALID()             (g_stTypeC0PdTimerEvent.b1Valid = _TRUE)
#define CLR_TYPE_C_0_PD_TIMER_EVENT_VALID()             (g_stTypeC0PdTimerEvent.b1Valid = _FALSE)

#define GET_TYPE_C_0_PD_TIMER_EVENT_ID()                (g_stTypeC0PdTimerEvent.enumEventID)
#define SET_TYPE_C_0_PD_TIMER_EVENT_ID(x)               (g_stTypeC0PdTimerEvent.enumEventID = (x))

#define GET_TYPE_C_0_PD_TIMER_EVENT_CNT()               (g_stTypeC0PdTimerEvent.usEventTime)
#define SET_TYPE_C_0_PD_TIMER_EVENT_CNT(x)              (g_stTypeC0PdTimerEvent.usEventTime = (x))

// PD WDINT Cancel Source EPR Keep Alive Timer Event Macro
#define GET_TYPE_C_0_PD_CANCEL_SRC_EPR_KEEP_ALIVE()     (g_stTypeC0PdTimerEvent.b1CancelSrcEprKeepAlive)
#define SET_TYPE_C_0_PD_CANCEL_SRC_EPR_KEEP_ALIVE()     (g_stTypeC0PdTimerEvent.b1CancelSrcEprKeepAlive = _TRUE)
#define CLR_TYPE_C_0_PD_CANCEL_SRC_EPR_KEEP_ALIVE()     (g_stTypeC0PdTimerEvent.b1CancelSrcEprKeepAlive = _FALSE)

// Counter Control Macro
#define GET_TYPE_C_0_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT()(g_stTypeC0PdCableInfo.b5DiscoverIdRetryFailCnt)
#define ADD_TYPE_C_0_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT()(g_stTypeC0PdCableInfo.b5DiscoverIdRetryFailCnt += 1)
#define CLR_TYPE_C_0_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT()(g_stTypeC0PdCableInfo.b5DiscoverIdRetryFailCnt = 0)

#define GET_TYPE_C_0_PD_SRC_CAP_CNT()                   (g_stTypeC0PdStatus.b6SrcCapCnt)
#define ADD_TYPE_C_0_PD_SRC_CAP_CNT()                   (g_stTypeC0PdStatus.b6SrcCapCnt += 1)
#define CLR_TYPE_C_0_PD_SRC_CAP_CNT()                   (g_stTypeC0PdStatus.b6SrcCapCnt = 0)

#define GET_TYPE_C_0_PD_HARD_RST_CNT()                  (g_stTypeC0PdStatus.b2HardRstCnt)
#define ADD_TYPE_C_0_PD_HARD_RST_CNT()                  (g_stTypeC0PdStatus.b2HardRstCnt += 1)
#define CLR_TYPE_C_0_PD_HARD_RST_CNT()                  (g_stTypeC0PdStatus.b2HardRstCnt = 0)

#define GET_TYPE_C_0_PD_CHECK_VBUS_CNT()                (g_stTypeC0PdStatus.b4CheckVbusCnt)
#define ADD_TYPE_C_0_PD_CHECK_VBUS_CNT()                (g_stTypeC0PdStatus.b4CheckVbusCnt += 1)
#define CLR_TYPE_C_0_PD_CHECK_VBUS_CNT()                (g_stTypeC0PdStatus.b4CheckVbusCnt = 0)

// Timer Control Macro
#define GET_TYPE_C_0_PD_WD_TIMER_VALUE()                (g_stTypeC0PdStatus.b10WDTimer)
#define SET_TYPE_C_0_PD_WD_TIMER_VALUE(x)               (g_stTypeC0PdStatus.b10WDTimer = (x))
#define CLR_TYPE_C_0_PD_WD_TIMER_VALUE()                (g_stTypeC0PdStatus.b10WDTimer = 0)

// FW Flow Control Macro
#define GET_TYPE_C_0_PD_PRS_REJECT()                    (g_stTypeC0PdStatus.b1PDPRSwapReject)
#define SET_TYPE_C_0_PD_PRS_REJECT()                    (g_stTypeC0PdStatus.b1PDPRSwapReject = _TRUE)
#define CLR_TYPE_C_0_PD_PRS_REJECT()                    (g_stTypeC0PdStatus.b1PDPRSwapReject = _FALSE)

#define GET_TYPE_C_0_PD_DRS_REJECT()                    (g_stTypeC0PdStatus.b1PDDRSwapReject)
#define SET_TYPE_C_0_PD_DRS_REJECT()                    (g_stTypeC0PdStatus.b1PDDRSwapReject = _TRUE)
#define CLR_TYPE_C_0_PD_DRS_REJECT()                    (g_stTypeC0PdStatus.b1PDDRSwapReject = _FALSE)

#define GET_TYPE_C_0_PD_VCS_REJECT()                    (g_stTypeC0PdStatus.b1PDVconnSwapReject)
#define SET_TYPE_C_0_PD_VCS_REJECT()                    (g_stTypeC0PdStatus.b1PDVconnSwapReject = _TRUE)
#define CLR_TYPE_C_0_PD_VCS_REJECT()                    (g_stTypeC0PdStatus.b1PDVconnSwapReject = _FALSE)

#define GET_TYPE_C_0_PD_GET_SNK_CAP_SENT()              (g_stTypeC0PdStatus.b1GetSnkCapSent)
#define SET_TYPE_C_0_PD_GET_SNK_CAP_SENT()              (g_stTypeC0PdStatus.b1GetSnkCapSent = _TRUE)
#define CLR_TYPE_C_0_PD_GET_SNK_CAP_SENT()              (g_stTypeC0PdStatus.b1GetSnkCapSent = _FALSE)

#define GET_TYPE_C_0_PD_GET_SRC_CAP_SENT()              (g_stTypeC0PdStatus.b1GetSrcCapSent)
#define SET_TYPE_C_0_PD_GET_SRC_CAP_SENT()              (g_stTypeC0PdStatus.b1GetSrcCapSent = _TRUE)
#define CLR_TYPE_C_0_PD_GET_SRC_CAP_SENT()              (g_stTypeC0PdStatus.b1GetSrcCapSent = _FALSE)

#define GET_TYPE_C_0_PD_RCV_SNK_CAP()                   (g_stTypeC0PdStatus.b1RcvSnkCap)
#define SET_TYPE_C_0_PD_RCV_SNK_CAP()                   (g_stTypeC0PdStatus.b1RcvSnkCap = _TRUE)
#define CLR_TYPE_C_0_PD_RCV_SNK_CAP()                   (g_stTypeC0PdStatus.b1RcvSnkCap = _FALSE)

#define GET_TYPE_C_0_PD_RCV_SRC_CAP()                   (g_stTypeC0PdStatus.b1RcvSrcCap)
#define SET_TYPE_C_0_PD_RCV_SRC_CAP()                   (g_stTypeC0PdStatus.b1RcvSrcCap = _TRUE)
#define CLR_TYPE_C_0_PD_RCV_SRC_CAP()                   (g_stTypeC0PdStatus.b1RcvSrcCap = _FALSE)

#define GET_TYPE_C_0_PD_HRST_PWR_OFF()                  (g_stTypeC0PdStatus.b1HRST_Pwr_Off)
#define SET_TYPE_C_0_PD_HRST_PWR_OFF()                  (g_stTypeC0PdStatus.b1HRST_Pwr_Off = _TRUE)
#define CLR_TYPE_C_0_PD_HRST_PWR_OFF()                  (g_stTypeC0PdStatus.b1HRST_Pwr_Off = _FALSE)

#define GET_TYPE_C_0_PD_REQ_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1ReqWait)
#define SET_TYPE_C_0_PD_REQ_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1ReqWait = _TRUE)
#define CLR_TYPE_C_0_PD_REQ_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1ReqWait = _FALSE)

#define GET_TYPE_C_0_PD_PRS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1PRSwapWait)
#define SET_TYPE_C_0_PD_PRS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1PRSwapWait = _TRUE)
#define CLR_TYPE_C_0_PD_PRS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1PRSwapWait = _FALSE)

#define GET_TYPE_C_0_PD_DRS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1DRSwapWait)
#define SET_TYPE_C_0_PD_DRS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1DRSwapWait = _TRUE)
#define CLR_TYPE_C_0_PD_DRS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1DRSwapWait = _FALSE)

#define GET_TYPE_C_0_PD_VCS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1VCSwapWait)
#define SET_TYPE_C_0_PD_VCS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1VCSwapWait = _TRUE)
#define CLR_TYPE_C_0_PD_VCS_WAIT_FLAG()                 (g_stTypeC0PdStatus.b1VCSwapWait = _FALSE)

#define GET_TYPE_C_0_PD_VDMMSG_WAIT_FLAG()              (g_stTypeC0PdStatus.b1VdmMsgWait)
#define SET_TYPE_C_0_PD_VDMMSG_WAIT_FLAG()              (g_stTypeC0PdStatus.b1VdmMsgWait = _TRUE)
#define CLR_TYPE_C_0_PD_VDMMSG_WAIT_FLAG()              (g_stTypeC0PdStatus.b1VdmMsgWait = _FALSE)

#define GET_TYPE_C_0_PD_VDM_BUSY_FLAG()                 (g_stTypeC0PdStatus.b1VdmBusy)
#define SET_TYPE_C_0_PD_VDM_BUSY_FLAG()                 (g_stTypeC0PdStatus.b1VdmBusy = _TRUE)
#define CLR_TYPE_C_0_PD_VDM_BUSY_FLAG()                 (g_stTypeC0PdStatus.b1VdmBusy = _FALSE)

#define GET_TYPE_C_0_PD_SRC_CAP_SENT_FLAG()             (g_stTypeC0PdStatus.b1SrcCapSent)
#define SET_TYPE_C_0_PD_SRC_CAP_SENT_FLAG()             (g_stTypeC0PdStatus.b1SrcCapSent = _TRUE)
#define CLR_TYPE_C_0_PD_SRC_CAP_SENT_FLAG()             (g_stTypeC0PdStatus.b1SrcCapSent = _FALSE)

#define GET_TYPE_C_0_PD_SNK_CAP_WAIT_FLAG()             (g_stTypeC0PdStatus.b1SnkCapWait)
#define SET_TYPE_C_0_PD_SNK_CAP_WAIT_FLAG()             (g_stTypeC0PdStatus.b1SnkCapWait = _TRUE)
#define CLR_TYPE_C_0_PD_SNK_CAP_WAIT_FLAG()             (g_stTypeC0PdStatus.b1SnkCapWait = _FALSE)

#define GET_TYPE_C_0_PD_PRS_PROCESSING()                (g_stTypeC0PdStatus.b1PRS_Processing)
#define SET_TYPE_C_0_PD_PRS_PROCESSING()                (g_stTypeC0PdStatus.b1PRS_Processing = _TRUE)
#define CLR_TYPE_C_0_PD_PRS_PROCESSING()                (g_stTypeC0PdStatus.b1PRS_Processing = _FALSE)

#define GET_TYPE_C_0_PD_INTEROP_S8()                    (g_stTypeC0PdStatus.b1InteropS8)
#define SET_TYPE_C_0_PD_INTEROP_S8()                    (g_stTypeC0PdStatus.b1InteropS8 = _TRUE)
#define CLR_TYPE_C_0_PD_INTEROP_S8()                    (g_stTypeC0PdStatus.b1InteropS8 = _FALSE)

#define GET_TYPE_C_0_PD_ALERT_SENT()                    (g_stTypeC0PdStatus.b1AlertSent)
#define SET_TYPE_C_0_PD_ALERT_SENT()                    (g_stTypeC0PdStatus.b1AlertSent = _TRUE)
#define CLR_TYPE_C_0_PD_ALERT_SENT()                    (g_stTypeC0PdStatus.b1AlertSent = _FALSE)

#define GET_TYPE_C_0_PD_GET_SNK_CAP_WAIT_FLAG()         (g_stTypeC0PdStatus.b1GetSnkCapWait)
#define SET_TYPE_C_0_PD_GET_SNK_CAP_WAIT_FLAG()         (g_stTypeC0PdStatus.b1GetSnkCapWait = _TRUE)
#define CLR_TYPE_C_0_PD_GET_SNK_CAP_WAIT_FLAG()         (g_stTypeC0PdStatus.b1GetSnkCapWait = _FALSE)

// Source Capability Macros
#define GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT()               ((BYTE)g_stTypeC0PdStatus.b3PDNumOfSPRSrcCap)
#define SET_TYPE_C_0_PD_SPR_SRC_PDO_CNT(x)              (g_stTypeC0PdStatus.b3PDNumOfSPRSrcCap = (x))

#define GET_TYPE_C_0_PD_EPR_SRC_PDO_CNT()               ((BYTE)g_stTypeC0PdStatus.b3PDNumOfEPRSrcCap)
#define SET_TYPE_C_0_PD_EPR_SRC_PDO_CNT(x)              (g_stTypeC0PdStatus.b3PDNumOfEPRSrcCap = (x))

#define GET_TYPE_C_0_PD_SRC_PDO_TYPE(x)                 (g_pstTypeC0PdSrcPDO[x].enumPdoType)
#define SET_TYPE_C_0_PD_SRC_PDO_TYPE(x, y)              (g_pstTypeC0PdSrcPDO[x].enumPdoType = (y))

#define GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(x)              (g_pstTypeC0PdSrcPDO[x].usMaxVoltage)
#define SET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(x, y)           (g_pstTypeC0PdSrcPDO[x].usMaxVoltage = (y))

#define GET_TYPE_C_0_PD_SRC_CAP_VOL_MIN(x)              (g_pstTypeC0PdSrcPDO[x].usMinVoltage)
#define SET_TYPE_C_0_PD_SRC_CAP_VOL_MIN(x, y)           (g_pstTypeC0PdSrcPDO[x].usMinVoltage = (y))

#define GET_TYPE_C_0_PD_SRC_CAP_CUR(x)                  ((WORD)(g_pstTypeC0PdSrcPDO[x].b10MaxCurrent))
#define SET_TYPE_C_0_PD_SRC_CAP_CUR(x, y)               (g_pstTypeC0PdSrcPDO[x].b10MaxCurrent = (y))

#define GET_TYPE_C_0_PD_SRC_CAP_PEAK(x)                 (g_pstTypeC0PdSrcPDO[x].b2PeakCurrent)
#define SET_TYPE_C_0_PD_SRC_CAP_PEAK(x, y)              (g_pstTypeC0PdSrcPDO[x].b2PeakCurrent = (y))

// Sink Capability Macros
#define GET_TYPE_C_0_PD_SPR_SNK_PDO_CNT()               ((BYTE)g_stTypeC0PdStatus.b3PDNumOfSPRSnkCap)
#define SET_TYPE_C_0_PD_SPR_SNK_PDO_CNT(x)              (g_stTypeC0PdStatus.b3PDNumOfSPRSnkCap = (x))

#define GET_TYPE_C_0_PD_EPR_SNK_PDO_CNT()               ((BYTE)g_stTypeC0PdStatus.b3PDNumOfEPRSnkCap)
#define SET_TYPE_C_0_PD_EPR_SNK_PDO_CNT(x)              (g_stTypeC0PdStatus.b3PDNumOfEPRSnkCap = (x))

#define GET_TYPE_C_0_PD_SNK_PDO_TYPE(x)                 (g_pstTypeC0PdSnkCap[x].enumPdoType)
#define SET_TYPE_C_0_PD_SNK_PDO_TYPE(x, y)              (g_pstTypeC0PdSnkCap[x].enumPdoType = (y))

#define GET_TYPE_C_0_PD_SNK_CAP_VOL_MAX(x)              (g_pstTypeC0PdSnkCap[x].usMaxVoltage)
#define SET_TYPE_C_0_PD_SNK_CAP_VOL_MAX(x, y)           (g_pstTypeC0PdSnkCap[x].usMaxVoltage = (y))

#define GET_TYPE_C_0_PD_SNK_CAP_VOL_MIN(x)              (g_pstTypeC0PdSnkCap[x].usMinVoltage)
#define SET_TYPE_C_0_PD_SNK_CAP_VOL_MIN(x, y)           (g_pstTypeC0PdSnkCap[x].usMinVoltage = (y))

#define GET_TYPE_C_0_PD_SNK_CAP_CUR(x)                  (g_pstTypeC0PdSnkCap[x].b10MaxCurrent)
#define SET_TYPE_C_0_PD_SNK_CAP_CUR(x, y)               (g_pstTypeC0PdSnkCap[x].b10MaxCurrent = (y))

// Sink Capability Extended Macros
#define GET_TYPE_C_0_PD_SNK_MIN_PDP()                   (g_stTypeC0PdSnkInfo.usSnkMinPDP)
#define SET_TYPE_C_0_PD_SNK_MIN_PDP(x)                  (g_stTypeC0PdSnkInfo.usSnkMinPDP = (x))

#define GET_TYPE_C_0_PD_SNK_OPERATIONAL_PDP()           (g_stTypeC0PdSnkInfo.usSnkOpePDP)
#define SET_TYPE_C_0_PD_SNK_OPERATIONAL_PDP(x)          (g_stTypeC0PdSnkInfo.usSnkOpePDP = (x))

#define GET_TYPE_C_0_PD_SNK_MAX_PDP()                   (g_stTypeC0PdSnkInfo.usSnkMaxPDP)
#define SET_TYPE_C_0_PD_SNK_MAX_PDP(x)                  (g_stTypeC0PdSnkInfo.usSnkMaxPDP = (x))

// Request Macros
#define GET_TYPE_C_0_PD_REQ_TYPE()                      (g_stTypeC0PdStatus.enumReqType)
#define SET_TYPE_C_0_PD_REQ_TYPE(x)                     (g_stTypeC0PdStatus.enumReqType = (x))

#define GET_TYPE_C_0_PD_INIT_REQ_TARGET_VOL()           (g_stTypeC0PdStatus.ucTargetVolRDO)
#define SET_TYPE_C_0_PD_INIT_REQ_TARGET_VOL(x)          (g_stTypeC0PdStatus.ucTargetVolRDO = (x))

#define GET_TYPE_C_0_PD_REQ_OBJ_POS()                   ((BYTE)(g_stTypeC0PdSnkRDO.enumObjPos))
#define SET_TYPE_C_0_PD_REQ_OBJ_POS(x)                  (g_stTypeC0PdSnkRDO.enumObjPos = (x))

#define GET_TYPE_C_0_PD_REQ_CAP_MIS()                   ((BYTE)(g_stTypeC0PdSnkRDO.b1CapMismatch))
#define SET_TYPE_C_0_PD_REQ_CAP_MIS(x)                  (g_stTypeC0PdSnkRDO.b1CapMismatch = (x))

#define GET_TYPE_C_0_PD_REQ_GIVE_BACK()                 ((BYTE)(g_stTypeC0PdSnkRDO.b1GiveBack))
#define SET_TYPE_C_0_PD_REQ_GIVE_BACK(x)                (g_stTypeC0PdSnkRDO.b1GiveBack = (x))

#define GET_TYPE_C_0_PD_REQ_INFO_1()                    ((WORD)(g_stTypeC0PdSnkRDO.usReqInfo1))
#define SET_TYPE_C_0_PD_REQ_INFO_1(x)                   (g_stTypeC0PdSnkRDO.usReqInfo1 = (x))

#define GET_TYPE_C_0_PD_REQ_INFO_2()                    ((WORD)(g_stTypeC0PdSnkRDO.usReqInfo2))
#define SET_TYPE_C_0_PD_REQ_INFO_2(x)                   (g_stTypeC0PdSnkRDO.usReqInfo2 = (x))

// Status Message Macros
#define GET_TYPE_C_0_PD_NEW_POWER_STATE()               (g_stTypeC0PdStatusEvent.b3NewPowerState)
#define SET_TYPE_C_0_PD_NEW_POWER_STATE(x)              (g_stTypeC0PdStatusEvent.b3NewPowerState = (x))

#define GET_TYPE_C_0_PD_NEW_POWER_INDICATOR()           (g_stTypeC0PdStatusEvent.b3NewPSIndicator)
#define SET_TYPE_C_0_PD_NEW_POWER_INDICATOR(x)          (g_stTypeC0PdStatusEvent.b3NewPSIndicator = (x))

// Alert Message Macros
#define GET_TYPE_C_0_PD_TYPE_OF_ALERT()                 (g_stTypeC0PdAlertEvent.enumTypeOfAlert)
#define SET_TYPE_C_0_PD_TYPE_OF_ALERT(x)                (g_stTypeC0PdAlertEvent.enumTypeOfAlert = (g_stTypeC0PdAlertEvent.enumTypeOfAlert | (x)))
#define CLR_TYPE_C_0_PD_TYPE_OF_ALERT(x)                (g_stTypeC0PdAlertEvent.enumTypeOfAlert = (g_stTypeC0PdAlertEvent.enumTypeOfAlert & (EnumTypeCTypeOfAlert)(~(x))))

#define GET_TYPE_C_0_PD_BAT_STATUS()                    (g_stTypeC0PdAlertEvent.enumBatStatus)
#define SET_TYPE_C_0_PD_BAT_STATUS(x)                   (g_stTypeC0PdAlertEvent.enumBatStatus = (g_stTypeC0PdAlertEvent.enumBatStatus | (x)))
#define CLR_TYPE_C_0_PD_BAT_STATUS(x)                   (g_stTypeC0PdAlertEvent.enumBatStatus = (g_stTypeC0PdAlertEvent.enumBatStatus & (EnumTypeCBatteryStatus)(~(x))))

#define GET_TYPE_C_0_PD_EXT_ALERT_EVENT()               (g_stTypeC0PdAlertEvent.enumExtAlertEvent)
#define SET_TYPE_C_0_PD_EXT_ALERT_EVENT(x)              (g_stTypeC0PdAlertEvent.enumExtAlertEvent = (x))

// Port Partner(Other Side) General Info Setting Macros
#define GET_TYPE_C_0_PD_PARTNER_DRP()                   (g_stTypeC0PdPartnerInfo.b1DualRolePower)
#define SET_TYPE_C_0_PD_PARTNER_DRP(x)                  (g_stTypeC0PdPartnerInfo.b1DualRolePower = (x))
#define CLR_TYPE_C_0_PD_PARTNER_DRP()                   (g_stTypeC0PdPartnerInfo.b1DualRolePower = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_DRD()                   (g_stTypeC0PdPartnerInfo.b1DualRoleData)
#define SET_TYPE_C_0_PD_PARTNER_DRD(x)                  (g_stTypeC0PdPartnerInfo.b1DualRoleData = (x))
#define CLR_TYPE_C_0_PD_PARTNER_DRD()                   (g_stTypeC0PdPartnerInfo.b1DualRoleData = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_SUSPEND()               (g_stTypeC0PdPartnerInfo.b1SuspendSupport)
#define SET_TYPE_C_0_PD_PARTNER_SUSPEND(x)              (g_stTypeC0PdPartnerInfo.b1SuspendSupport = (x))
#define CLR_TYPE_C_0_PD_PARTNER_SUSPEND()               (g_stTypeC0PdPartnerInfo.b1SuspendSupport = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_EXT_PWR()               (g_stTypeC0PdPartnerInfo.b1ExtPower)
#define SET_TYPE_C_0_PD_PARTNER_EXT_PWR(x)              (g_stTypeC0PdPartnerInfo.b1ExtPower = (x))
#define CLR_TYPE_C_0_PD_PARTNER_EXT_PWR()               (g_stTypeC0PdPartnerInfo.b1ExtPower = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_USB_CAP()               (g_stTypeC0PdPartnerInfo.b1UsbCapable)
#define SET_TYPE_C_0_PD_PARTNER_USB_CAP(x)              (g_stTypeC0PdPartnerInfo.b1UsbCapable = (x))
#define CLR_TYPE_C_0_PD_PARTNER_USB_CAP()               (g_stTypeC0PdPartnerInfo.b1UsbCapable = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_UNCHK()                 (g_stTypeC0PdPartnerInfo.b1UnchkSupport)
#define SET_TYPE_C_0_PD_PARTNER_UNCHK(x)                (g_stTypeC0PdPartnerInfo.b1UnchkSupport = (x))
#define CLR_TYPE_C_0_PD_PARTNER_UNCHK()                 (g_stTypeC0PdPartnerInfo.b1UnchkSupport = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_EPR_CAP()               (g_stTypeC0PdPartnerInfo.b1PartnerEPRCapable)
#define SET_TYPE_C_0_PD_PARTNER_EPR_CAP(x)              (g_stTypeC0PdPartnerInfo.b1PartnerEPRCapable = (x))

#define GET_TYPE_C_0_PD_PARTNER_ALT_SUPPORT()           (g_stTypeC0PdPartnerInfo.b1ALTSupport)
#define SET_TYPE_C_0_PD_PARTNER_ALT_SUPPORT()           (g_stTypeC0PdPartnerInfo.b1ALTSupport = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_ALT_SUPPORT()           (g_stTypeC0PdPartnerInfo.b1ALTSupport = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_HIGH_CAP()              (g_stTypeC0PdPartnerInfo.b1HigherCap)
#define SET_TYPE_C_0_PD_PARTNER_HIGH_CAP(x)             (g_stTypeC0PdPartnerInfo.b1HigherCap = (x))
#define CLR_TYPE_C_0_PD_PARTNER_HIGH_CAP()              (g_stTypeC0PdPartnerInfo.b1HigherCap = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_FRS_CUR()               (g_stTypeC0PdPartnerInfo.b2FrsCurrent)
#define SET_TYPE_C_0_PD_PARTNER_FRS_CUR(x)              (g_stTypeC0PdPartnerInfo.b2FrsCurrent = (x))
#define CLR_TYPE_C_0_PD_PARTNER_FRS_CUR()               (g_stTypeC0PdPartnerInfo.b2FrsCurrent = 0)

// Port Partner(Other Side) Source Cap Info Setting Macros
#define GET_TYPE_C_0_PD_PARTNER_SRC_CAP_CNT()           (g_stTypeC0PdPartnerInfo.b3NumOfSrcCap)
#define SET_TYPE_C_0_PD_PARTNER_SRC_CAP_CNT(x)          (g_stTypeC0PdPartnerInfo.b3NumOfSrcCap = (x))

#define GET_TYPE_C_0_PD_PARTNER_SRC_CAP_TYPE(x)         (g_pstTypeC0PdPartnerSrcCap[x].enumPdoType)
#define SET_TYPE_C_0_PD_PARTNER_SRC_CAP_TYPE(x, y)      (g_pstTypeC0PdPartnerSrcCap[x].enumPdoType = (y))

#define GET_TYPE_C_0_PD_PARTNER_SRC_CAP_VOL_MAX(x)      (g_pstTypeC0PdPartnerSrcCap[x].usMaxVoltage)
#define SET_TYPE_C_0_PD_PARTNER_SRC_CAP_VOL_MAX(x, y)   (g_pstTypeC0PdPartnerSrcCap[x].usMaxVoltage = (y))

#define GET_TYPE_C_0_PD_PARTNER_SRC_CAP_VOL_MIN(x)      (g_pstTypeC0PdPartnerSrcCap[x].usMinVoltage)
#define SET_TYPE_C_0_PD_PARTNER_SRC_CAP_VOL_MIN(x, y)   (g_pstTypeC0PdPartnerSrcCap[x].usMinVoltage = (y))

#define GET_TYPE_C_0_PD_PARTNER_SRC_CAP_CUR(x)          ((WORD)(g_pstTypeC0PdPartnerSrcCap[x].b10MaxCurrent))
#define SET_TYPE_C_0_PD_PARTNER_SRC_CAP_CUR(x, y)       (g_pstTypeC0PdPartnerSrcCap[x].b10MaxCurrent = (y))

#define GET_TYPE_C_0_PD_PARTNER_SRC_PEAK_CUR(x)         (g_pstTypeC0PdPartnerSrcCap[x].b2PeakCurrent)
#define SET_TYPE_C_0_PD_PARTNER_SRC_PEAK_CUR(x, y)      (g_pstTypeC0PdPartnerSrcCap[x].b2PeakCurrent = (y))

#define GET_TYPE_C_0_PD_PARTNER_SRC_CAP_CHECK_RESULT()  (g_stTypeC0PdPartnerInfo.enumSrcCapValid)
#define SET_TYPE_C_0_PD_PARTNER_SRC_CAP_CHECK_RESULT(x) (g_stTypeC0PdPartnerInfo.enumSrcCapValid = (x))

// Port Partner(Other Side) Sink Cap Info Setting Macros
#define GET_TYPE_C_0_PD_PARTNER_SNK_CAP_CNT()           (g_stTypeC0PdPartnerInfo.b3NumOfSnkCap)
#define SET_TYPE_C_0_PD_PARTNER_SNK_CAP_CNT(x)          (g_stTypeC0PdPartnerInfo.b3NumOfSnkCap = (x))

#define GET_TYPE_C_0_PD_PARTNER_SVDM_VERSION()          (g_stTypeC0PdPartnerInfo.enumSvdmVersion)
#define SET_TYPE_C_0_PD_PARTNER_SVDM_VERSION(x)         (g_stTypeC0PdPartnerInfo.enumSvdmVersion = (x))

#define GET_TYPE_C_0_PD_PARTNER_DPAM_VERSION()          (g_stTypeC0PdPartnerInfo.enumDpamVersion)
#define SET_TYPE_C_0_PD_PARTNER_DPAM_VERSION(x)         (g_stTypeC0PdPartnerInfo.enumDpamVersion = (x))

#define GET_TYPE_C_0_PD_PARTNER_SNK_CAP_TYPE(x)         (g_pstTypeC0PdPartnerSnkCap[x].enumPdoType)
#define SET_TYPE_C_0_PD_PARTNER_SNK_CAP_TYPE(x, y)      (g_pstTypeC0PdPartnerSnkCap[x].enumPdoType = (y))

#define GET_TYPE_C_0_PD_PARTNER_SNK_CAP_VOL_MAX(x)      (g_pstTypeC0PdPartnerSnkCap[x].usMaxVoltage)
#define SET_TYPE_C_0_PD_PARTNER_SNK_CAP_VOL_MAX(x, y)   (g_pstTypeC0PdPartnerSnkCap[x].usMaxVoltage = (y))

#define GET_TYPE_C_0_PD_PARTNER_SNK_CAP_VOL_MIN(x)      (g_pstTypeC0PdPartnerSnkCap[x].usMinVoltage)
#define SET_TYPE_C_0_PD_PARTNER_SNK_CAP_VOL_MIN(x, y)   (g_pstTypeC0PdPartnerSnkCap[x].usMinVoltage = (y))

#define GET_TYPE_C_0_PD_PARTNER_SNK_CAP_CUR(x)          (g_pstTypeC0PdPartnerSnkCap[x].b10MaxCurrent)
#define SET_TYPE_C_0_PD_PARTNER_SNK_CAP_CUR(x, y)       (g_pstTypeC0PdPartnerSnkCap[x].b10MaxCurrent = (y))

// Port Partner(Other Side) Request Info Setting Macros
#define GET_TYPE_C_0_PD_PARTNER_OBJ_POS()               (g_stTypeC0PdPartnerRDO.b4ObjPos)
#define SET_TYPE_C_0_PD_PARTNER_OBJ_POS(x)              (g_stTypeC0PdPartnerRDO.b4ObjPos = (x))
#define CLR_TYPE_C_0_PD_PARTNER_OBJ_POS()               (g_stTypeC0PdPartnerRDO.b4ObjPos = 0)

#define GET_TYPE_C_0_PD_PARTNER_CAP_MIS()               (g_stTypeC0PdPartnerRDO.b1CapMis)
#define SET_TYPE_C_0_PD_PARTNER_CAP_MIS(x)              (g_stTypeC0PdPartnerRDO.b1CapMis = (x))
#define CLR_TYPE_C_0_PD_PARTNER_CAP_MIS()               (g_stTypeC0PdPartnerRDO.b1CapMis = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_GIVE_BACK()             (g_stTypeC0PdPartnerRDO.b1GiveBack)
#define SET_TYPE_C_0_PD_PARTNER_GIVE_BACK(x)            (g_stTypeC0PdPartnerRDO.b1GiveBack = (x))
#define CLR_TYPE_C_0_PD_PARTNER_GIVE_BACK()             (g_stTypeC0PdPartnerRDO.b1GiveBack = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_REQ_VOL()               (g_stTypeC0PdPartnerRDO.usVoltage)
#define SET_TYPE_C_0_PD_PARTNER_REQ_VOL(x)              (g_stTypeC0PdPartnerRDO.usVoltage = (x))

#define GET_TYPE_C_0_PD_PARTNER_OP_CUR()                (g_stTypeC0PdPartnerRDO.b10OpCurrent)
#define SET_TYPE_C_0_PD_PARTNER_OP_CUR(x)               (g_stTypeC0PdPartnerRDO.b10OpCurrent = (x))
#define CLR_TYPE_C_0_PD_PARTNER_OP_CUR()                (g_stTypeC0PdPartnerRDO.b10OpCurrent = 0)

#define GET_TYPE_C_0_PD_PARTNER_MAX_CUR()               (g_stTypeC0PdPartnerRDO.b10MaxCurrent)
#define SET_TYPE_C_0_PD_PARTNER_MAX_CUR(x)              (g_stTypeC0PdPartnerRDO.b10MaxCurrent = (x))
#define CLR_TYPE_C_0_PD_PARTNER_MAX_CUR()               (g_stTypeC0PdPartnerRDO.b10MaxCurrent = 0)

#define GET_TYPE_C_0_PD_REQ_PPS_VOL_SMALL_STEP()        (g_stTypeC0PdPartnerRDO.b1PPSSmallStep)
#define SET_TYPE_C_0_PD_REQ_PPS_VOL_SMALL_STEP(x)       (g_stTypeC0PdPartnerRDO.b1PPSSmallStep = (x))
#define CLR_TYPE_C_0_PD_REQ_PPS_VOL_SMALL_STEP()        (g_stTypeC0PdPartnerRDO.b1PPSSmallStep = 0)

#define GET_TYPE_C_0_PD_REQ_AVS_VOL_SMALL_STEP()        (g_stTypeC0PdPartnerRDO.b1AVSSmallStep)
#define SET_TYPE_C_0_PD_REQ_AVS_VOL_SMALL_STEP(x)       (g_stTypeC0PdPartnerRDO.b1AVSSmallStep = (x))
#define CLR_TYPE_C_0_PD_REQ_AVS_VOL_SMALL_STEP()        (g_stTypeC0PdPartnerRDO.b1AVSSmallStep = 0)

// Port Partner(Other Side) Status Message Macros
#define GET_TYPE_C_0_PD_PARTNER_NEW_POWER_STATE()       (g_stTypeC0PdPartnerStatusEvent.b3NewPowerState)
#define SET_TYPE_C_0_PD_PARTNER_NEW_POWER_STATE(x)      (g_stTypeC0PdPartnerStatusEvent.b3NewPowerState = (x))

#define GET_TYPE_C_0_PD_PARTNER_NEW_POWER_INDICATOR()   (g_stTypeC0PdPartnerStatusEvent.b3NewPSIndicator)
#define SET_TYPE_C_0_PD_PARTNER_NEW_POWER_INDICATOR(x)  (g_stTypeC0PdPartnerStatusEvent.b3NewPSIndicator = (x))

// Port Partner(Other Side) Alert Message Macros
#define GET_TYPE_C_0_PD_PARTNER_TYPE_OF_ALERT()         (g_stTypeC0PdPartnerAlertEvent.enumTypeOfAlert)
#define SET_TYPE_C_0_PD_PARTNER_TYPE_OF_ALERT(x)        (g_stTypeC0PdPartnerAlertEvent.enumTypeOfAlert = (x))

#define GET_TYPE_C_0_PD_PARTNER_BAT_STATUS()            (g_stTypeC0PdPartnerAlertEvent.enumBatStatus)
#define SET_TYPE_C_0_PD_PARTNER_BAT_STATUS(x)           (g_stTypeC0PdPartnerAlertEvent.enumBatStatus = (x))

#define GET_TYPE_C_0_PD_PARTNER_EXT_ALERT_EVENT()       (g_stTypeC0PdPartnerAlertEvent.enumExtAlertEvent)
#define SET_TYPE_C_0_PD_PARTNER_EXT_ALERT_EVENT(x)      (g_stTypeC0PdPartnerAlertEvent.enumExtAlertEvent = (x))

// Power Contract Negotiated Power Status For User
#define GET_TYPE_C_0_PD_PDO_STATUS_VOL()                (g_stTypeC0PdPDOStatus.usVoltage)
#define SET_TYPE_C_0_PD_PDO_STATUS_VOL(x)               (g_stTypeC0PdPDOStatus.usVoltage = (x))

#define GET_TYPE_C_0_PD_PDO_STATUS_CUR()                (g_stTypeC0PdPDOStatus.usCurrent)
#define SET_TYPE_C_0_PD_PDO_STATUS_CUR(x)               (g_stTypeC0PdPDOStatus.usCurrent = (x))

#define GET_TYPE_C_0_PD_PDO_STATUS_OBJ_POS()            (g_stTypeC0PdPDOStatus.b4ObjPos)
#define SET_TYPE_C_0_PD_PDO_STATUS_OBJ_POS(x)           (g_stTypeC0PdPDOStatus.b4ObjPos = (x))
#define CLR_TYPE_C_0_PD_PDO_STATUS_OBJ_POS()            (g_stTypeC0PdPDOStatus.b4ObjPos = 0)

// Extended Message Info Macros For Receive Chunked Message
#define GET_TYPE_C_0_PD_CHUNKED_MESSAGE()               (g_stTypeC0PdExtMsgInfo.b1Chunked)
#define SET_TYPE_C_0_PD_CHUNKED_MESSAGE(x)              (g_stTypeC0PdExtMsgInfo.b1Chunked = (x))

#define GET_TYPE_C_0_PD_CHUNK_NUMBER()                  (g_stTypeC0PdExtMsgInfo.b4ChunkNum)
#define SET_TYPE_C_0_PD_CHUNK_NUMBER(x)                 (g_stTypeC0PdExtMsgInfo.b4ChunkNum = (x))

#define GET_TYPE_C_0_PD_CHUNK_REQUEST()                 (g_stTypeC0PdExtMsgInfo.b1ChunkRequest)
#define SET_TYPE_C_0_PD_CHUNK_REQUEST(x)                (g_stTypeC0PdExtMsgInfo.b1ChunkRequest = (x))

#define GET_TYPE_C_0_PD_EXT_MSG_DATA_SIZE()             (g_stTypeC0PdExtMsgInfo.b9DataSize)
#define SET_TYPE_C_0_PD_EXT_MSG_DATA_SIZE(x)            (g_stTypeC0PdExtMsgInfo.b9DataSize = (x))

// Extended Message Info Macros For Transmit Chunked Message
#define GET_TYPE_C_0_PD_TX_CHUNKED_MESSAGE()            (g_stTypeC0PdExtMsgInfo.b1TxChunked)
#define SET_TYPE_C_0_PD_TX_CHUNKED_MESSAGE()            (g_stTypeC0PdExtMsgInfo.b1TxChunked = _TRUE)
#define CLR_TYPE_C_0_PD_TX_CHUNKED_MESSAGE()            (g_stTypeC0PdExtMsgInfo.b1TxChunked = _FALSE)

#define GET_TYPE_C_0_PD_TX_CHUNK_NUMBER()               (g_stTypeC0PdExtMsgInfo.b4TxChunkNum)
#define ADD_TYPE_C_0_PD_TX_CHUNK_NUMBER(x)              (g_stTypeC0PdExtMsgInfo.b4TxChunkNum += 1)
#define CLR_TYPE_C_0_PD_TX_CHUNK_NUMBER()               (g_stTypeC0PdExtMsgInfo.b4TxChunkNum = 0)

// FW Message Transmission Macro
#define GET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT()           (g_stTypeC0PdMsgInfo.b3TxRetryFailEvent)
#define SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(x)          (g_stTypeC0PdMsgInfo.b3TxRetryFailEvent = (x))

#define GET_TYPE_C_0_PD_TRANSMIT_RESULT()               (g_stTypeC0PdMsgInfo.b5TxResult)
#define SET_TYPE_C_0_PD_TRANSMIT_RESULT(x)              (g_stTypeC0PdMsgInfo.b5TxResult = (x))
#define CLR_TYPE_C_0_PD_TRANSMIT_RESULT()               (g_stTypeC0PdMsgInfo.b5TxResult = 0)

#define GET_TYPE_C_0_PD_INT_OVERWRITE()                 (g_stTypeC0PdMsgInfo.b1IntOverWrite)
#define SET_TYPE_C_0_PD_INT_OVERWRITE()                 (g_stTypeC0PdMsgInfo.b1IntOverWrite = _TRUE)
#define CLR_TYPE_C_0_PD_INT_OVERWRITE()                 (g_stTypeC0PdMsgInfo.b1IntOverWrite = _FALSE)

#define GET_TYPE_C_0_PD_FIFO_ERR_STATUS()               (g_stTypeC0PdMsgInfo.b8FifoRcvErrStatus)
#define SET_TYPE_C_0_PD_FIFO_ERR_STATUS(x)              (g_stTypeC0PdMsgInfo.b8FifoRcvErrStatus = (x))

#define GET_TYPE_C_0_PD_FIFO_CLR()                      (g_stTypeC0PdMsgInfo.b1FifoClr)
#define SET_TYPE_C_0_PD_FIFO_CLR()                      (g_stTypeC0PdMsgInfo.b1FifoClr = _TRUE)
#define CLR_TYPE_C_0_PD_FIFO_CLR()                      (g_stTypeC0PdMsgInfo.b1FifoClr = _FALSE)

#define GET_TYPE_C_0_PD_BUS_IDLE()                      (g_stTypeC0PdMsgInfo.b1BusIdle)
#define SET_TYPE_C_0_PD_BUS_IDLE()                      (g_stTypeC0PdMsgInfo.b1BusIdle = _TRUE)
#define CLR_TYPE_C_0_PD_BUS_IDLE()                      (g_stTypeC0PdMsgInfo.b1BusIdle = _FALSE)

#define GET_TYPE_C_0_PD_RCV_MSG()                       (g_stTypeC0PdMsgInfo.b8RcvMsg)
#define SET_TYPE_C_0_PD_RCV_MSG(x)                      (g_stTypeC0PdMsgInfo.b8RcvMsg = (x))
#define CLR_TYPE_C_0_PD_RCV_MSG()                       (g_stTypeC0PdMsgInfo.b8RcvMsg = 0)

#define GET_TYPE_C_0_PD_RCV_NOD_CNT()                   ((BYTE)(g_stTypeC0PdMsgInfo.b3RcvNodCnt))
#define SET_TYPE_C_0_PD_RCV_NOD_CNT(x)                  (g_stTypeC0PdMsgInfo.b3RcvNodCnt = (x))

// BIST Mode Macro
#define GET_TYPE_C_0_PD_BIST_MODE()                     (g_stTypeC0PdStatus.b4BistMode)
#define SET_TYPE_C_0_PD_BIST_MODE(x)                    (g_stTypeC0PdStatus.b4BistMode = (x))

// EPR Mode Macros
#define GET_TYPE_C_0_PD_ENTER_EPR_MODE_FLOW()           (g_stTypeC0PdEPRMode.b1EnterEPRFlow)
#define SET_TYPE_C_0_PD_ENTER_EPR_MODE_FLOW()           (g_stTypeC0PdEPRMode.b1EnterEPRFlow = _TRUE)
#define CLR_TYPE_C_0_PD_ENTER_EPR_MODE_FLOW()           (g_stTypeC0PdEPRMode.b1EnterEPRFlow = _FALSE)

#define GET_TYPE_C_0_PD_EPR_MODE()                      (g_stTypeC0PdEPRMode.b1EPRMode)
#define SET_TYPE_C_0_PD_EPR_MODE()                      (g_stTypeC0PdEPRMode.b1EPRMode = _TRUE)
#define CLR_TYPE_C_0_PD_EPR_MODE()                      (g_stTypeC0PdEPRMode.b1EPRMode = _FALSE)

#define GET_TYPE_C_0_PD_EPR_MODE_ACTION()               (g_stTypeC0PdEPRMode.enumPDEPRModeAction)
#define SET_TYPE_C_0_PD_EPR_MODE_ACTION(x)              (g_stTypeC0PdEPRMode.enumPDEPRModeAction = (x))

#define GET_TYPE_C_0_PD_ENTER_EPR_FAILED_REASON()       (g_stTypeC0PdEPRMode.enumPDEnterEPRFailedReason)
#define SET_TYPE_C_0_PD_ENTER_EPR_FAILED_REASON(x)      (g_stTypeC0PdEPRMode.enumPDEnterEPRFailedReason = (x))

#define GET_TYPE_C_0_PD_EXT_CTRL_TYPE()                 (g_stTypeC0PdEPRMode.enumPDExtCtrlType)
#define SET_TYPE_C_0_PD_EXT_CTRL_TYPE(x)                (g_stTypeC0PdEPRMode.enumPDExtCtrlType = (x))

#define GET_TYPE_C_0_PD_EPR_SRC_CAPABLE()               (g_stTypeC0PdEPRMode.b1EPRSRCCapable)
#define SET_TYPE_C_0_PD_EPR_SRC_CAPABLE()               (g_stTypeC0PdEPRMode.b1EPRSRCCapable = _TRUE)
#define CLR_TYPE_C_0_PD_EPR_SRC_CAPABLE()               (g_stTypeC0PdEPRMode.b1EPRSRCCapable = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_EPR_SINK_PDP()          (g_stTypeC0PdEPRMode.ucPartnerEPRSinkPDP)
#define SET_TYPE_C_0_PD_PARTNER_EPR_SINK_PDP(x)         (g_stTypeC0PdEPRMode.ucPartnerEPRSinkPDP = (x))

// Alt Mode Info Macros
#define GET_TYPE_C_0_PD_ALT_MODE_FUNCTION()             (g_stTypeC0PdAltModeInfo.b1AltModeFunc)
#define SET_TYPE_C_0_PD_ALT_MODE_FUNCTION()             (g_stTypeC0PdAltModeInfo.b1AltModeFunc = _TRUE)
#define CLR_TYPE_C_0_PD_ALT_MODE_FUNCTION()             (g_stTypeC0PdAltModeInfo.b1AltModeFunc = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_INIT_ALT_MODE()         (g_stTypeC0PdAltModeInfo.b1PartnerInitAltMode)
#define SET_TYPE_C_0_PD_PARTNER_INIT_ALT_MODE()         (g_stTypeC0PdAltModeInfo.b1PartnerInitAltMode = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_INIT_ALT_MODE()         (g_stTypeC0PdAltModeInfo.b1PartnerInitAltMode = _FALSE)

#define GET_TYPE_C_0_PD_RCV_VDM_CMD()                   (g_stTypeC0PdAltModeInfo.ucRcvVdmMsg)
#define GET_TYPE_C_0_PD_RCV_VDM_CMD_TYPE()              (g_stTypeC0PdAltModeInfo.ucRcvVdmMsg & (_BIT7 | _BIT6))
#define SET_TYPE_C_0_PD_RCV_VDM_CMD(x)                  (g_stTypeC0PdAltModeInfo.ucRcvVdmMsg = (x))
#define CLR_TYPE_C_0_PD_RCV_VDM_CMD()                   (g_stTypeC0PdAltModeInfo.ucRcvVdmMsg = 0)

#define GET_TYPE_C_0_PD_RCV_VDM_TYPE()                  (g_stTypeC0PdAltModeInfo.b1RcvVdmType)
#define SET_TYPE_C_0_PD_RCV_VDM_TYPE(x)                 (g_stTypeC0PdAltModeInfo.b1RcvVdmType = (x))

#define GET_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT()       (g_stTypeC0PdAltModeInfo.b2PartnerVdmNoRespCnt)
#define ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT()       (g_stTypeC0PdAltModeInfo.b2PartnerVdmNoRespCnt += 1)
#define CLR_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT()       (g_stTypeC0PdAltModeInfo.b2PartnerVdmNoRespCnt = 0)

#define GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT()           (g_stTypeC0PdAltModeInfo.b2CblVdmNoRespCnt)
#define ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT()           (g_stTypeC0PdAltModeInfo.b2CblVdmNoRespCnt += 1)
#define CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT()           (g_stTypeC0PdAltModeInfo.b2CblVdmNoRespCnt = 0)

#define GET_TYPE_C_0_PD_VDM_BUSY_CNT()                  (g_stTypeC0PdAltModeInfo.b3VdmBusyCnt)
#define ADD_TYPE_C_0_PD_VDM_BUSY_CNT()                  (g_stTypeC0PdAltModeInfo.b3VdmBusyCnt += 1)
#define CLR_TYPE_C_0_PD_VDM_BUSY_CNT()                  (g_stTypeC0PdAltModeInfo.b3VdmBusyCnt = 0)

#define GET_TYPE_C_0_PD_UFP_PRODUCT_TYPE()              (g_stTypeC0PdAltModeInfo.enumUFPProductType)
#define SET_TYPE_C_0_PD_UFP_PRODUCT_TYPE(x)             (g_stTypeC0PdAltModeInfo.enumUFPProductType = (x))

#define GET_TYPE_C_0_PD_DFP_PRODUCT_TYPE()              (g_stTypeC0PdAltModeInfo.enumDFPProductType)
#define SET_TYPE_C_0_PD_DFP_PRODUCT_TYPE(x)             (g_stTypeC0PdAltModeInfo.enumDFPProductType = (x))

#define GET_TYPE_C_0_PD_VDM_SVID()                      (((WORD)(g_stTypeC0PdAltModeInfo.ucVdmSVID_H) << 8) | ((WORD)(g_stTypeC0PdAltModeInfo.ucVdmSVID_L)))
#define GET_TYPE_C_0_PD_VDM_SVID_H()                    (g_stTypeC0PdAltModeInfo.ucVdmSVID_H)
#define GET_TYPE_C_0_PD_VDM_SVID_L()                    (g_stTypeC0PdAltModeInfo.ucVdmSVID_L)
#define SET_TYPE_C_0_PD_VDM_SVID_H(x)                   (g_stTypeC0PdAltModeInfo.ucVdmSVID_H = (x))
#define SET_TYPE_C_0_PD_VDM_SVID_L(x)                   (g_stTypeC0PdAltModeInfo.ucVdmSVID_L = (x))

#define GET_TYPE_C_0_PD_VDM_OBJ_POS()                   (g_stTypeC0PdAltModeInfo.b3VdmObjPos)
#define SET_TYPE_C_0_PD_VDM_OBJ_POS(x)                  (g_stTypeC0PdAltModeInfo.b3VdmObjPos = (x))

#define GET_TYPE_C_0_PD_PIN_ASSIGNMENT()                (g_stTypeC0PdAltModeInfo.enumDpRxPinAssignment)
#define SET_TYPE_C_0_PD_PIN_ASSIGNMENT(x)               (g_stTypeC0PdAltModeInfo.enumDpRxPinAssignment = (x))

#define GET_TYPE_C_0_PD_PIN_ASSIGNMENT_CAP()            (g_stTypeC0PdAltModeInfo.enumPinAssignmentCap)
#define SET_TYPE_C_0_PD_PIN_ASSIGNMENT_CAP(x)           (g_stTypeC0PdAltModeInfo.enumPinAssignmentCap = (x))

#define GET_TYPE_C_0_PD_PARTNER_PIN_ASSIGNMENT()        (g_stTypeC0PdAltModeInfo.ucPartnerPinAssignmentCap)
#define SET_TYPE_C_0_PD_PARTNER_PIN_ASSIGNMENT(x)       (g_stTypeC0PdAltModeInfo.ucPartnerPinAssignmentCap = (x))

#define GET_TYPE_C_0_PD_MULTI_FUNCTION_CHANGE()         (g_stTypeC0PdAltModeInfo.b1MultiFunctionChange)
#define SET_TYPE_C_0_PD_MULTI_FUNCTION_CHANGE()         (g_stTypeC0PdAltModeInfo.b1MultiFunctionChange = _TRUE)
#define CLR_TYPE_C_0_PD_MULTI_FUNCTION_CHANGE()         (g_stTypeC0PdAltModeInfo.b1MultiFunctionChange = _FALSE)

#define GET_TYPE_C_0_PD_MULTI_FUNCTION_CHANGE_DONE()    (g_stTypeC0PdAltModeInfo.b1MultiFunctionChangeDone)
#define SET_TYPE_C_0_PD_MULTI_FUNCTION_CHANGE_DONE()    (g_stTypeC0PdAltModeInfo.b1MultiFunctionChangeDone = _TRUE)
#define CLR_TYPE_C_0_PD_MULTI_FUNCTION_CHANGE_DONE()    (g_stTypeC0PdAltModeInfo.b1MultiFunctionChangeDone = _FALSE)

#define GET_TYPE_C_0_PD_ATTENTION_WAIT()                (g_stTypeC0PdAltModeInfo.b1AttentionWait)
#define SET_TYPE_C_0_PD_ATTENTION_WAIT()                (g_stTypeC0PdAltModeInfo.b1AttentionWait = _TRUE)
#define CLR_TYPE_C_0_PD_ATTENTION_WAIT()                (g_stTypeC0PdAltModeInfo.b1AttentionWait = _FALSE)

#define GET_TYPE_C_0_PD_DP_OBJ_POS()                    (g_stTypeC0PdAltModeInfo.b3DpObjPos)
#define SET_TYPE_C_0_PD_DP_OBJ_POS(x)                   (g_stTypeC0PdAltModeInfo.b3DpObjPos = (x))
#define CLR_TYPE_C_0_PD_DP_OBJ_POS()                    (g_stTypeC0PdAltModeInfo.b3DpObjPos = 0)

#define GET_TYPE_C_0_PD_DP_SVID_SEARCH_FINISH()         (g_stTypeC0PdAltModeInfo.b1DpSvidSearchFinish)
#define SET_TYPE_C_0_PD_DP_SVID_SEARCH_FINISH()         (g_stTypeC0PdAltModeInfo.b1DpSvidSearchFinish = _TRUE)
#define CLR_TYPE_C_0_PD_DP_SVID_SEARCH_FINISH()         (g_stTypeC0PdAltModeInfo.b1DpSvidSearchFinish = _FALSE)

#define GET_TYPE_C_0_PD_DP_ALT_MODE_ENTER()             (g_stTypeC0PdAltModeInfo.b1DpAltModeEnter)
#define SET_TYPE_C_0_PD_DP_ALT_MODE_ENTER()             (g_stTypeC0PdAltModeInfo.b1DpAltModeEnter = _TRUE)
#define CLR_TYPE_C_0_PD_DP_ALT_MODE_ENTER()             (g_stTypeC0PdAltModeInfo.b1DpAltModeEnter = _FALSE)

#define GET_TYPE_C_0_PD_DP_ALT_MODE_CONFIG()            (g_stTypeC0PdAltModeInfo.b1DpAltModeConfig)
#define SET_TYPE_C_0_PD_DP_ALT_MODE_CONFIG(x)           (g_stTypeC0PdAltModeInfo.b1DpAltModeConfig = (x))

#define GET_TYPE_C_0_PD_DP_ALT_MODE_TARGET_CONFIG()     (g_stTypeC0PdAltModeInfo.b1DpAltModeTargetConfig)
#define SET_TYPE_C_0_PD_DP_ALT_MODE_TARGET_CONFIG(x)    (g_stTypeC0PdAltModeInfo.b1DpAltModeTargetConfig = (x))

#define GET_TYPE_C_0_PD_DP_ALT_MODE_WAIT_CONFIG()       (g_stTypeC0PdAltModeInfo.b1DpAltModeWaitConfig)
#define SET_TYPE_C_0_PD_DP_ALT_MODE_WAIT_CONFIG()       (g_stTypeC0PdAltModeInfo.b1DpAltModeWaitConfig = _TRUE)
#define CLR_TYPE_C_0_PD_DP_ALT_MODE_WAIT_CONFIG()       (g_stTypeC0PdAltModeInfo.b1DpAltModeWaitConfig = _FALSE)

#define GET_TYPE_C_0_PD_VDM_RESP_CONFLICT_CNT()         (g_stTypeC0PdAltModeInfo.b2VdmRespConflictCnt)
#define ADD_TYPE_C_0_PD_VDM_RESP_CONFLICT_CNT()         (g_stTypeC0PdAltModeInfo.b2VdmRespConflictCnt += 1)
#define CLR_TYPE_C_0_PD_VDM_RESP_CONFLICT_CNT()         (g_stTypeC0PdAltModeInfo.b2VdmRespConflictCnt = 0)

// Self DP_Status Related Macros
#define GET_TYPE_C_0_PD_MULTI_FUNCTION()                (g_stTypeC0PdAltModeInfo.b1MultiFunctionBit)
#define SET_TYPE_C_0_PD_MULTI_FUNCTION()                (g_stTypeC0PdAltModeInfo.b1MultiFunctionBit = _TRUE)
#define CLR_TYPE_C_0_PD_MULTI_FUNCTION()                (g_stTypeC0PdAltModeInfo.b1MultiFunctionBit = _FALSE)

#define GET_TYPE_C_0_PD_DP_ALT_MODE_EXIT_REQ()          (g_stTypeC0PdAltModeInfo.b1DpAltModeExit)
#define SET_TYPE_C_0_PD_DP_ALT_MODE_EXIT_REQ()          (g_stTypeC0PdAltModeInfo.b1DpAltModeExit = _TRUE)
#define CLR_TYPE_C_0_PD_DP_ALT_MODE_EXIT_REQ()          (g_stTypeC0PdAltModeInfo.b1DpAltModeExit = _FALSE)

// Port Partner DP_Status Related Macros
#define GET_TYPE_C_0_PD_PARTNER_DP_CONNECT_STATUS()     (g_stTypeC0PdDpStatusInfo.enumPartnerDpConnectStatus)
#define SET_TYPE_C_0_PD_PARTNER_DP_CONNECT_STATUS(x)    (g_stTypeC0PdDpStatusInfo.enumPartnerDpConnectStatus = (x))

#define GET_TYPE_C_0_PD_PARTNER_DP_POWER_LOW()          (g_stTypeC0PdDpStatusInfo.b1PartnerDpPowerLow)
#define SET_TYPE_C_0_PD_PARTNER_DP_POWER_LOW()          (g_stTypeC0PdDpStatusInfo.b1PartnerDpPowerLow = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_DP_POWER_LOW()          (g_stTypeC0PdDpStatusInfo.b1PartnerDpPowerLow = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_DP_FUNCTION_ENABLE()    (g_stTypeC0PdDpStatusInfo.b1PartnerDpFunctionEnabled)
#define SET_TYPE_C_0_PD_PARTNER_DP_FUNCTION_ENABLE()    (g_stTypeC0PdDpStatusInfo.b1PartnerDpFunctionEnabled = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_DP_FUNCTION_ENABLE()    (g_stTypeC0PdDpStatusInfo.b1PartnerDpFunctionEnabled = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_MULTI_FUNCTION()        (g_stTypeC0PdDpStatusInfo.b1PartnerMultiFunctionBit)
#define SET_TYPE_C_0_PD_PARTNER_MULTI_FUNCTION()        (g_stTypeC0PdDpStatusInfo.b1PartnerMultiFunctionBit = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_MULTI_FUNCTION()        (g_stTypeC0PdDpStatusInfo.b1PartnerMultiFunctionBit = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_USB_CONFIG_REQUEST()    (g_stTypeC0PdDpStatusInfo.b1PartnerUsbConfigRequest)
#define SET_TYPE_C_0_PD_PARTNER_USB_CONFIG_REQUEST()    (g_stTypeC0PdDpStatusInfo.b1PartnerUsbConfigRequest = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_USB_CONFIG_REQUEST()    (g_stTypeC0PdDpStatusInfo.b1PartnerUsbConfigRequest = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_DP_ALT_MODE_EXIT_REQ()  (g_stTypeC0PdDpStatusInfo.b1PartnerDpAltModeExit)
#define SET_TYPE_C_0_PD_PARTNER_DP_ALT_MODE_EXIT_REQ()  (g_stTypeC0PdDpStatusInfo.b1PartnerDpAltModeExit = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_DP_ALT_MODE_EXIT_REQ()  (g_stTypeC0PdDpStatusInfo.b1PartnerDpAltModeExit = _FALSE)

#define GET_TYPE_C_0_PD_PARTNER_HPD_TYPE()              (g_stTypeC0PdDpStatusInfo.enumPartnerHpdType)
#define SET_TYPE_C_0_PD_PARTNER_HPD_TYPE(x)             (g_stTypeC0PdDpStatusInfo.enumPartnerHpdType = (x))

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
#define GET_TYPE_C_0_PD_PARTNER_NO_DP_ALT_SUSPEND()     (g_stTypeC0PdDpStatusInfo.b1PartnerNoDpAltSuspend)
#define SET_TYPE_C_0_PD_PARTNER_NO_DP_ALT_SUSPEND()     (g_stTypeC0PdDpStatusInfo.b1PartnerNoDpAltSuspend = _TRUE)
#define CLR_TYPE_C_0_PD_PARTNER_NO_DP_ALT_SUSPEND()     (g_stTypeC0PdDpStatusInfo.b1PartnerNoDpAltSuspend = _FALSE)
#endif

// Lenovo Alt Mode Related Macros
#define GET_TYPE_C_0_PD_LENOVO_ATTN_SENT_FLAG()         (g_stTypeC0PdAltModeInfo.b1LenovoAttnSent)
#define SET_TYPE_C_0_PD_LENOVO_ATTN_SENT_FLAG()         (g_stTypeC0PdAltModeInfo.b1LenovoAttnSent = _TRUE)
#define CLR_TYPE_C_0_PD_LENOVO_ATTN_SENT_FLAG()         (g_stTypeC0PdAltModeInfo.b1LenovoAttnSent = _FALSE)

#define GET_TYPE_C_0_PD_LENOVO_ATTN_CNT()               (g_stTypeC0PdAltModeInfo.b3LenovoAttnCnt)
#define ADD_TYPE_C_0_PD_LENOVO_ATTN_CNT()               (g_stTypeC0PdAltModeInfo.b3LenovoAttnCnt += 1)
#define CLR_TYPE_C_0_PD_LENOVO_ATTN_CNT()               (g_stTypeC0PdAltModeInfo.b3LenovoAttnCnt = 0)

#define GET_TYPE_C_0_PD_LENOVO_OBJ_POS()                (g_stTypeC0PdAltModeInfo.b3LenovoObjPos)
#define SET_TYPE_C_0_PD_LENOVO_OBJ_POS(x)               (g_stTypeC0PdAltModeInfo.b3LenovoObjPos = (x))
#define CLR_TYPE_C_0_PD_LENOVO_OBJ_POS()                (g_stTypeC0PdAltModeInfo.b3LenovoObjPos = 0)

#define GET_TYPE_C_0_PD_LENOVO_DEVICE_TYPE()            (g_stTypeC0PdAltModeInfo.enumLenovoDeviceType)
#define SET_TYPE_C_0_PD_LENOVO_DEVICE_TYPE(x)           (g_stTypeC0PdAltModeInfo.enumLenovoDeviceType = (x))

#define GET_TYPE_C_0_PD_LENOVO_ALT_MODE_ENTER()         (g_stTypeC0PdAltModeInfo.b1LenovoAltModeEnter)
#define SET_TYPE_C_0_PD_LENOVO_ALT_MODE_ENTER()         (g_stTypeC0PdAltModeInfo.b1LenovoAltModeEnter = _TRUE)
#define CLR_TYPE_C_0_PD_LENOVO_ALT_MODE_ENTER()         (g_stTypeC0PdAltModeInfo.b1LenovoAltModeEnter = _FALSE)

#define GET_TYPE_C_0_PD_LENOVO_DOCK_EVENT()             (g_stTypeC0PdAltModeInfo.ucLenovoDockingEvent)
#define SET_TYPE_C_0_PD_LENOVO_DOCK_EVENT(x)            (g_stTypeC0PdAltModeInfo.ucLenovoDockingEvent = (x))
#define CLR_TYPE_C_0_PD_LENOVO_DOCK_EVENT()             (g_stTypeC0PdAltModeInfo.ucLenovoDockingEvent = 0)

#define GET_TYPE_C_0_PD_LENOVO_SYS_ACKNOWLEDGE()        (g_stTypeC0PdAltModeInfo.ucLenovoSystemAcknowledge)
#define SET_TYPE_C_0_PD_LENOVO_SYS_ACKNOWLEDGE(x)       (g_stTypeC0PdAltModeInfo.ucLenovoSystemAcknowledge = (x))
#define CLR_TYPE_C_0_PD_LENOVO_SYS_ACKNOWLEDGE()        (g_stTypeC0PdAltModeInfo.ucLenovoSystemAcknowledge = 0)

#define GET_TYPE_C_0_PD_LENOVO_SYS_EVENT()              (g_stTypeC0PdAltModeInfo.ucLenovoSystemEvent)
#define SET_TYPE_C_0_PD_LENOVO_SYS_EVENT(x)             (g_stTypeC0PdAltModeInfo.ucLenovoSystemEvent = (x))
#define CLR_TYPE_C_0_PD_LENOVO_SYS_EVENT()              (g_stTypeC0PdAltModeInfo.ucLenovoSystemEvent = 0)

// Acer Alt Mode Related Macros
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#define GET_TYPE_C_0_PD_ACER_ALT_MODE_STATE()           (g_stTypeC0PdAcerAltModeInfo.b6AcerAltModeState)
#define SET_TYPE_C_0_PD_ACER_ALT_MODE_STATE(x)          (g_stTypeC0PdAcerAltModeInfo.b6AcerAltModeState = (x))

#define GET_TYPE_C_0_PD_ACER_ALT_MODE_ENTER()           (g_stTypeC0PdAcerAltModeInfo.b1AcerAltModeEnter)
#define SET_TYPE_C_0_PD_ACER_ALT_MODE_ENTER()           (g_stTypeC0PdAcerAltModeInfo.b1AcerAltModeEnter = _TRUE)
#define CLR_TYPE_C_0_PD_ACER_ALT_MODE_ENTER()           (g_stTypeC0PdAcerAltModeInfo.b1AcerAltModeEnter = _FALSE)

#define GET_TYPE_C_0_PD_ACER_USER_EVENT()               (g_stTypeC0PdAcerUserEvent.enumEvent)
#define SET_TYPE_C_0_PD_ACER_USER_EVENT(x)              (g_stTypeC0PdAcerUserEvent.enumEvent = (g_stTypeC0PdAcerUserEvent.enumEvent | (x)))
#define CLR_TYPE_C_0_PD_ACER_USER_EVENT(x)              (g_stTypeC0PdAcerUserEvent.enumEvent = (g_stTypeC0PdAcerUserEvent.enumEvent & (EnumTypeCAcerUserEvent)(~(x))))

#define GET_TYPE_C_0_PD_ACER_USER_VDM_CNT()             (g_stTypeC0PdAcerUserEvent.b3VdmCnt)
#define SET_TYPE_C_0_PD_ACER_USER_VDM_CNT(x)            (g_stTypeC0PdAcerUserEvent.b3VdmCnt = (x))

#define GET_TYPE_C_0_PD_ACER_USER_VDM_DATA(x)           (g_stTypeC0PdAcerUserEvent.pucVdmData[x])
#define SET_TYPE_C_0_PD_ACER_USER_VDM_DATA(x, y)        (g_stTypeC0PdAcerUserEvent.pucVdmData[x] = (y))

#define GET_TYPE_C_0_PD_ACER_SYS_EVENT()                (g_stTypeC0PdAcerSysEvent.enumEvent)
#define SET_TYPE_C_0_PD_ACER_SYS_EVENT(x)               (g_stTypeC0PdAcerSysEvent.enumEvent = (g_stTypeC0PdAcerSysEvent.enumEvent | (x)))
#define CLR_TYPE_C_0_PD_ACER_SYS_EVENT(x)               (g_stTypeC0PdAcerSysEvent.enumEvent = (g_stTypeC0PdAcerSysEvent.enumEvent & (EnumTypeCAcerSysEvent)(~(x))))

#define GET_TYPE_C_0_PD_ACER_SYS_VDM_CNT()              (g_stTypeC0PdAcerSysEvent.b3VdmCnt)
#define SET_TYPE_C_0_PD_ACER_SYS_VDM_CNT(x)             (g_stTypeC0PdAcerSysEvent.b3VdmCnt = (x))

#define GET_TYPE_C_0_PD_ACER_SYS_VDM_DATA(x)            (g_stTypeC0PdAcerSysEvent.pucVdmData[x])
#define SET_TYPE_C_0_PD_ACER_SYS_VDM_DATA(x, y)         (g_stTypeC0PdAcerSysEvent.pucVdmData[x] = (y))
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

// Hp Alt Mode Related Macros
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#define GET_TYPE_C_0_PD_HP_ALT_MODE_STATE()             (g_stTypeC0PdHpAltModeInfo.b6HpAltModeState)
#define SET_TYPE_C_0_PD_HP_ALT_MODE_STATE(x)            (g_stTypeC0PdHpAltModeInfo.b6HpAltModeState = (x))

#define GET_TYPE_C_0_PD_HP_ALT_MODE_ENTER()             (g_stTypeC0PdHpAltModeInfo.b1HpAltModeEnter)
#define SET_TYPE_C_0_PD_HP_ALT_MODE_ENTER()             (g_stTypeC0PdHpAltModeInfo.b1HpAltModeEnter = _TRUE)
#define CLR_TYPE_C_0_PD_HP_ALT_MODE_ENTER()             (g_stTypeC0PdHpAltModeInfo.b1HpAltModeEnter = _FALSE)

#define GET_TYPE_C_0_PD_HP_I2C_ADDR()                   (g_stTypeC0PdHpAltModeInfo.b7HpI2cAddr)
#define SET_TYPE_C_0_PD_HP_I2C_ADDR(x)                  (g_stTypeC0PdHpAltModeInfo.b7HpI2cAddr = (x))
#define CLR_TYPE_C_0_PD_HP_I2C_ADDR()                   (g_stTypeC0PdHpAltModeInfo.b7HpI2cAddr = 0)

#define GET_TYPE_C_0_PD_HP_OWN_AM_ADDR_H()              (g_stTypeC0PdHpAltModeInfo.b2HpOwnAmAddr_H)
#define SET_TYPE_C_0_PD_HP_OWN_AM_ADDR_H(x)             (g_stTypeC0PdHpAltModeInfo.b2HpOwnAmAddr_H = (x))
#define CLR_TYPE_C_0_PD_HP_OWN_AM_ADDR_H()              (g_stTypeC0PdHpAltModeInfo.b2HpOwnAmAddr_H = 0)

#define GET_TYPE_C_0_PD_HP_OWN_AM_ADDR_M()              (g_stTypeC0PdHpAltModeInfo.ucHpOwnAmAddr_M)
#define SET_TYPE_C_0_PD_HP_OWN_AM_ADDR_M(x)             (g_stTypeC0PdHpAltModeInfo.ucHpOwnAmAddr_M = (x))
#define CLR_TYPE_C_0_PD_HP_OWN_AM_ADDR_M()              (g_stTypeC0PdHpAltModeInfo.ucHpOwnAmAddr_M = 0)

#define GET_TYPE_C_0_PD_HP_OWN_AM_ADDR_L()              (g_stTypeC0PdHpAltModeInfo.ucHpOwnAmAddr_L)
#define SET_TYPE_C_0_PD_HP_OWN_AM_ADDR_L(x)             (g_stTypeC0PdHpAltModeInfo.ucHpOwnAmAddr_L = (x))
#define CLR_TYPE_C_0_PD_HP_OWN_AM_ADDR_L()              (g_stTypeC0PdHpAltModeInfo.ucHpOwnAmAddr_L = 0)

#define GET_TYPE_C_0_PD_HP_VWIRE_OP()                   (g_stTypeC0PdHpAltModeInfo.enumHpVwireOp)
#define SET_TYPE_C_0_PD_HP_VWIRE_OP(x)                  (g_stTypeC0PdHpAltModeInfo.enumHpVwireOp = (x))

#define GET_TYPE_C_0_PD_HP_ATTEN_RETRY_CNT()            (g_stTypeC0PdHpAltModeInfo.b3HpAttenCnt)
#define ADD_TYPE_C_0_PD_HP_ATTEN_RETRY_CNT()            (g_stTypeC0PdHpAltModeInfo.b3HpAttenCnt += 1)
#define CLR_TYPE_C_0_PD_HP_ATTEN_RETRY_CNT()            (g_stTypeC0PdHpAltModeInfo.b3HpAttenCnt = 0)

#define GET_TYPE_C_0_PD_HP_ATTEN_TYPE()                 (((BYTE)g_stTypeC0PdHpAltModeInfo.enumHpAttenType) & (_BIT2 | _BIT1 | _BIT0))
#define SET_TYPE_C_0_PD_HP_ATTEN_TYPE(x)                (g_stTypeC0PdHpAltModeInfo.enumHpAttenType = (x))

#define GET_TYPE_C_0_PD_HP_USER_EVENT()                 (g_stTypeC0PdHpUserEvent.enumEvent)
#define SET_TYPE_C_0_PD_HP_USER_EVENT(x)                (g_stTypeC0PdHpUserEvent.enumEvent = (g_stTypeC0PdHpUserEvent.enumEvent | (x)))
#define CLR_TYPE_C_0_PD_HP_USER_EVENT(x)                (g_stTypeC0PdHpUserEvent.enumEvent = (g_stTypeC0PdHpUserEvent.enumEvent & (EnumTypeCHpUserEvent)(~(x))))

#define GET_TYPE_C_0_PD_HP_USER_VDM_CNT()               (g_stTypeC0PdHpUserEvent.b3VdmCnt)
#define SET_TYPE_C_0_PD_HP_USER_VDM_CNT(x)              (g_stTypeC0PdHpUserEvent.b3VdmCnt = (x))

#define GET_TYPE_C_0_PD_HP_USER_VDM_DATA(x)             (g_stTypeC0PdHpUserEvent.pucVdmData[x])
#define SET_TYPE_C_0_PD_HP_USER_VDM_DATA(x, y)          (g_stTypeC0PdHpUserEvent.pucVdmData[x] = (y))

// HP SysEvent Queue
#define GET_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE(x)           (g_stTypeC0PdHpSysEventQueue.pstSysEvent[x])
#define SET_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE(x, y)        (g_stTypeC0PdHpSysEventQueue.pstSysEvent[x] = (y))
#define CLR_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE(x)           (memset(&g_stTypeC0PdHpSysEventQueue.pstSysEvent[x], 0, sizeof(StructTypeCHpSysEvent)))

#define GET_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_CNT()        (g_stTypeC0PdHpSysEventQueue.b3SysEventCnt)
#define ADD_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_CNT()        (g_stTypeC0PdHpSysEventQueue.b3SysEventCnt += 1)
#define SUB_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_CNT()        (g_stTypeC0PdHpSysEventQueue.b3SysEventCnt -= 1)
#define CLR_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_CNT()        (g_stTypeC0PdHpSysEventQueue.b3SysEventCnt = 0)

#define GET_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_HEAD()       (g_stTypeC0PdHpSysEventQueue.b3SysEventHead)
#define ADD_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_HEAD()       (g_stTypeC0PdHpSysEventQueue.b3SysEventHead = (g_stTypeC0PdHpSysEventQueue.b3SysEventHead + 1) % _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE)
#define CLR_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_HEAD()       (g_stTypeC0PdHpSysEventQueue.b3SysEventHead = 0)

#define GET_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_TAIL()       (g_stTypeC0PdHpSysEventQueue.b3SysEventTail)
#define ADD_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_TAIL()       (g_stTypeC0PdHpSysEventQueue.b3SysEventTail = (g_stTypeC0PdHpSysEventQueue.b3SysEventTail + 1) % _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE)
#define CLR_TYPE_C_0_PD_HP_SYS_EVENT_QUEUE_TAIL()       (g_stTypeC0PdHpSysEventQueue.b3SysEventTail = 0)
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

// Dell Alt Mode Related Macros
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#define GET_TYPE_C_0_PD_DELL_ALT_MODE_STATE()           (g_stTypeC0PdDellAltModeInfo.b6DellAltModeState)
#define SET_TYPE_C_0_PD_DELL_ALT_MODE_STATE(x)          (g_stTypeC0PdDellAltModeInfo.b6DellAltModeState = (x))

#define GET_TYPE_C_0_PD_DELL_ALT_MODE_ENTER()           (g_stTypeC0PdDellAltModeInfo.b1DellAltModeEnter)
#define SET_TYPE_C_0_PD_DELL_ALT_MODE_ENTER()           (g_stTypeC0PdDellAltModeInfo.b1DellAltModeEnter = _TRUE)
#define CLR_TYPE_C_0_PD_DELL_ALT_MODE_ENTER()           (g_stTypeC0PdDellAltModeInfo.b1DellAltModeEnter = _FALSE)

#define GET_TYPE_C_0_PD_DELL_AM_ENTER_TIMEOUT()         (g_stTypeC0PdDellAltModeInfo.b1DellAMTimeout)
#define SET_TYPE_C_0_PD_DELL_AM_ENTER_TIMEOUT()         (g_stTypeC0PdDellAltModeInfo.b1DellAMTimeout = _TRUE)
#define CLR_TYPE_C_0_PD_DELL_AM_ENTER_TIMEOUT()         (g_stTypeC0PdDellAltModeInfo.b1DellAMTimeout = _FALSE)

#define GET_TYPE_C_0_PD_DELL_OBJ_POS()                  (g_stTypeC0PdDellAltModeInfo.b3DellObjPos)
#define SET_TYPE_C_0_PD_DELL_OBJ_POS(x)                 (g_stTypeC0PdDellAltModeInfo.b3DellObjPos = (x))
#define CLR_TYPE_C_0_PD_DELL_OBJ_POS()                  (g_stTypeC0PdDellAltModeInfo.b3DellObjPos = 0)

#define GET_TYPE_C_0_PD_DELL_ATTEN_RETRY_CNT()          (g_stTypeC0PdDellAltModeInfo.b3DellAttenCnt)
#define ADD_TYPE_C_0_PD_DELL_ATTEN_RETRY_CNT()          (g_stTypeC0PdDellAltModeInfo.b3DellAttenCnt += 1)
#define CLR_TYPE_C_0_PD_DELL_ATTEN_RETRY_CNT()          (g_stTypeC0PdDellAltModeInfo.b3DellAttenCnt = 0)

#define GET_TYPE_C_0_PD_DELL_ATTEN_WAIT()               (g_stTypeC0PdDellAltModeInfo.b1DellAttenWait)
#define SET_TYPE_C_0_PD_DELL_ATTEN_WAIT()               (g_stTypeC0PdDellAltModeInfo.b1DellAttenWait = _TRUE)
#define CLR_TYPE_C_0_PD_DELL_ATTEN_WAIT()               (g_stTypeC0PdDellAltModeInfo.b1DellAttenWait = _FALSE)

#define GET_TYPE_C_0_PD_DELL_AM_INIT_COMPLETE()         (g_stTypeC0PdDellAltModeInfo.b1DellInitComplete)
#define SET_TYPE_C_0_PD_DELL_AM_INIT_COMPLETE()         (g_stTypeC0PdDellAltModeInfo.b1DellInitComplete = _TRUE)
#define CLR_TYPE_C_0_PD_DELL_AM_INIT_COMPLETE()         (g_stTypeC0PdDellAltModeInfo.b1DellInitComplete = _FALSE)

#define GET_TYPE_C_0_PD_DELL_USER_EVENT()               (g_stTypeC0PdDellUserEvent.enumEvent)
#define SET_TYPE_C_0_PD_DELL_USER_EVENT(x)              (g_stTypeC0PdDellUserEvent.enumEvent = (g_stTypeC0PdDellUserEvent.enumEvent | (x)))
#define CLR_TYPE_C_0_PD_DELL_USER_EVENT(x)              (g_stTypeC0PdDellUserEvent.enumEvent = (g_stTypeC0PdDellUserEvent.enumEvent & (EnumTypeCDellUserEvent)(~(x))))

#define GET_TYPE_C_0_PD_DELL_USER_VDM_CNT()             (g_stTypeC0PdDellUserEvent.b3VdmCnt)
#define SET_TYPE_C_0_PD_DELL_USER_VDM_CNT(x)            (g_stTypeC0PdDellUserEvent.b3VdmCnt = (x))

#define GET_TYPE_C_0_PD_DELL_USER_VDM_DATA(x)           (g_stTypeC0PdDellUserEvent.pucVdmData[x])
#define SET_TYPE_C_0_PD_DELL_USER_VDM_DATA(x, y)        (g_stTypeC0PdDellUserEvent.pucVdmData[x] = (y))

#define GET_TYPE_C_0_PD_DELL_SYS_EVENT()                (g_stTypeC0PdDellSysEvent.enumEvent)
#define SET_TYPE_C_0_PD_DELL_SYS_EVENT(x)               (g_stTypeC0PdDellSysEvent.enumEvent = (g_stTypeC0PdDellSysEvent.enumEvent | (x)))
#define CLR_TYPE_C_0_PD_DELL_SYS_EVENT(x)               (g_stTypeC0PdDellSysEvent.enumEvent = (g_stTypeC0PdDellSysEvent.enumEvent & (EnumTypeCDellSysEvent)(~(x))))

#define GET_TYPE_C_0_PD_DELL_SYS_VDM_CNT()              (g_stTypeC0PdDellSysEvent.b3VdmCnt)
#define SET_TYPE_C_0_PD_DELL_SYS_VDM_CNT(x)             (g_stTypeC0PdDellSysEvent.b3VdmCnt = (x))

#define GET_TYPE_C_0_PD_DELL_SYS_VDM_DATA(x)            (g_stTypeC0PdDellSysEvent.pucVdmData[x])
#define SET_TYPE_C_0_PD_DELL_SYS_VDM_DATA(x, y)         (g_stTypeC0PdDellSysEvent.pucVdmData[x] = (y))
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

// Alt Mode HPD Queue Control Macros
#define GET_TYPE_C_0_PD_HPD_QUEUE(x)                    (g_stTypeC0PdHpdQueue.penumHpdType[x])
#define SET_TYPE_C_0_PD_HPD_QUEUE(x)                    (g_stTypeC0PdHpdQueue.penumHpdType[g_stTypeC0PdHpdQueue.b2HpdWptr] = (x))
#define CLR_TYPE_C_0_PD_HPD_QUEUE()                     (g_stTypeC0PdHpdQueue.penumHpdType[g_stTypeC0PdHpdQueue.b2HpdRptr] = (_PD_HPD_NONE))

#define GET_TYPE_C_0_PD_HPD_SPACE_TIME(x)               (g_stTypeC0PdHpdQueue.pusHpdSpace[x])
#define SET_TYPE_C_0_PD_HPD_SPACE_TIME(x)               (g_stTypeC0PdHpdQueue.pusHpdSpace[g_stTypeC0PdHpdQueue.b2HpdWptr] = (x))
#define CLR_TYPE_C_0_PD_HPD_SPACE_TIME()                (g_stTypeC0PdHpdQueue.pusHpdSpace[g_stTypeC0PdHpdQueue.b2HpdRptr] = 0)

#define GET_TYPE_C_0_PD_HPD_STATUS()                    (g_stTypeC0PdHpdQueue.b1HpdStatus)
#define SET_TYPE_C_0_PD_HPD_STATUS(x)                   (g_stTypeC0PdHpdQueue.b1HpdStatus = (x))

#define GET_TYPE_C_0_PD_HPD_CNT()                       (g_stTypeC0PdHpdQueue.b3HpdCnt)
#define ADD_TYPE_C_0_PD_HPD_CNT()                       (g_stTypeC0PdHpdQueue.b3HpdCnt += 1)
#define SUB_TYPE_C_0_PD_HPD_CNT()                       (g_stTypeC0PdHpdQueue.b3HpdCnt -= 1)
#define CLR_TYPE_C_0_PD_HPD_CNT()                       (g_stTypeC0PdHpdQueue.b3HpdCnt = 0)

#define GET_TYPE_C_0_PD_HPD_WPTR()                      (g_stTypeC0PdHpdQueue.b2HpdWptr)
#define ADD_TYPE_C_0_PD_HPD_WPTR()                      (g_stTypeC0PdHpdQueue.b2HpdWptr = (g_stTypeC0PdHpdQueue.b2HpdWptr + 1) % 4)
#define CLR_TYPE_C_0_PD_HPD_WPTR()                      (g_stTypeC0PdHpdQueue.b2HpdWptr = 0)

#define GET_TYPE_C_0_PD_HPD_RPTR()                      (g_stTypeC0PdHpdQueue.b2HpdRptr)
#define ADD_TYPE_C_0_PD_HPD_RPTR()                      (g_stTypeC0PdHpdQueue.b2HpdRptr = (g_stTypeC0PdHpdQueue.b2HpdRptr + 1) % 4)
#define CLR_TYPE_C_0_PD_HPD_RPTR()                      (g_stTypeC0PdHpdQueue.b2HpdRptr = 0)

// Force Sending HPD IRQ Macros
#define GET_TYPE_C_0_PD_FORCE_HPD_IRQ()                 (g_stTypeC0PdAltModeInfo.b1ForceHpdIrq)
#define SET_TYPE_C_0_PD_FORCE_HPD_IRQ()                 (g_stTypeC0PdAltModeInfo.b1ForceHpdIrq = _TRUE)
#define CLR_TYPE_C_0_PD_FORCE_HPD_IRQ()                 (g_stTypeC0PdAltModeInfo.b1ForceHpdIrq = _FALSE)

// System Request Event Macros
#define GET_TYPE_C_0_PD_SYS_EVENT()                     (g_stTypeC0PdEvent.enumSystemEvent)
#define SET_TYPE_C_0_PD_SYS_EVENT(x)                    (g_stTypeC0PdEvent.enumSystemEvent = (g_stTypeC0PdEvent.enumSystemEvent | (x)))
#define CLR_TYPE_C_0_PD_SYS_EVENT(x)                    (g_stTypeC0PdEvent.enumSystemEvent = (g_stTypeC0PdEvent.enumSystemEvent & (EnumTypeCPDSysEvent)(~(x))))

// Port Controller Event Macros
#define GET_TYPE_C_0_PD_PORT_CTRL_EVENT()               (g_stTypeC0PdEvent.enumPortCtrlEvent)
#define SET_TYPE_C_0_PD_PORT_CTRL_EVENT(x)              (g_stTypeC0PdEvent.enumPortCtrlEvent = (g_stTypeC0PdEvent.enumPortCtrlEvent | (x)))
#define CLR_TYPE_C_0_PD_PORT_CTRL_EVENT(x)              (g_stTypeC0PdEvent.enumPortCtrlEvent = (g_stTypeC0PdEvent.enumPortCtrlEvent & (EnumTypeCPDPortCtrlEvent)(~(x))))

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
// PD FW Flow
extern void ScalerTypeC0PdReadyStateProc(void);
extern void ScalerTypeC0PdSrcReadyProc(void);
extern void ScalerTypeC0PdSnkReadyProc(void);
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC0PdSrcReadyDpRxProc(void);
extern void ScalerTypeC0PdSnkReadyDpRxProc(void);
#elif(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
extern void ScalerTypeC0PdSrcReadyDpTxProc(void);
extern void ScalerTypeC0PdSnkReadyDpTxProc(void);
#endif  // End of #if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
// PD Alt Mode Flow
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
extern void ScalerTypeC0PdAltModeProc(void);
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeC0PdDpAltModeDfpProc(void);
extern void ScalerTypeC0PdDpAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern void ScalerTypeC0PdLenovoAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void ScalerTypeC0PdAcerAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void ScalerTypeC0PdHpAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern void ScalerTypeC0PdDellAltModeUfpProc(void);
#endif
#endif  // End of #if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
// PD Send Msg. Functions
extern void ScalerTypeC0PdSendMsg(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructMsg(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructDataObj(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructVdmDataObj(EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdSendSoftRst(EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeC0PdConstructSoftReset(EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeC0PdProcHardRst(void);
extern void ScalerTypeC0PdSendCableRst(void);
// PD FW Supplementary Functions
extern void ScalerTypeC0PdOcpOvpProc(void);
extern void ScalerTypeC0PdRxIntControl(bit b1Action);
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
extern void ScalerTypeC0PdUpdateCableRetryCounter(void);
#endif
extern void ScalerTypeC0PdRxFifoClear(EnumTypeCRxFifoIndex enumFifo);
extern void ScalerTypeC0PdUnattachCancelTimerEvent(void);
extern bit ScalerTypeC0PdTxAvaliable(void);
extern void ScalerTypeC0PdClrHpd(void);
extern EnumTypeCPDAltModeUrgentStatus ScalerTypeC0PdAltModeUrgentEvent(void);

// EXINT0
// PD FW Flow
extern void ScalerTypeC0PdStartUpProc_EXINT0(void);
extern void ScalerTypeC0PdStartUpSetting_EXINT0(void);
// PD Receive Message Flow
extern void ScalerTypeC0PdIntRcvMsgProc_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo);
extern void ScalerTypeC0PdIntSrcRcvMsgNoAmsProc_EXINT0(void);
extern void ScalerTypeC0PdIntSnkRcvMsgNoAmsProc_EXINT0(void);
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeC0PdIntDfpRcvVdmMsgProc_EXINT0(void);
#endif
extern void ScalerTypeC0PdIntUfpRcvVdmMsgProc_EXINT0(void);
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeC0PdIntUfpRcvDpVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern void ScalerTypeC0PdIntUfpRcvLenovoVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void ScalerTypeC0PdIntUfpRcvAcerVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void ScalerTypeC0PdIntUfpRcvHpVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern void ScalerTypeC0PdIntUfpRcvDellVdmMsgProc_EXINT0(void);
#endif
#endif  // End of #if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
extern void ScalerTypeC0PdIntRcvMsgInAmsProc_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo);
extern void ScalerTypeC0PdRcvSoftRstProc_EXINT0(void);
extern void ScalerTypeC0PdIntRcvCableMsgProc_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo);
extern void ScalerTypeC0PdPrlErrHandle_EXINT0(void);
// PD FW Send Msg Done Flow
extern void ScalerTypeC0PdIntTxSuccessProc_EXINT0(void);
extern void ScalerTypeC0PdIntTxFailProc_EXINT0(void);
extern void ScalerTypeC0PdIntTxCableReqSuccessProc_EXINT0(void);
extern void ScalerTypeC0PdIntTxCableReqFailProc_EXINT0(void);
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
extern void ScalerTypeC0PdIntTxDpVdmReqSuccessProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern void ScalerTypeC0PdIntTxLenovoVdmReqSuccessProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void ScalerTypeC0PdIntTxAcerVdmReqSuccessProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void ScalerTypeC0PdIntTxHpVdmReqSuccessProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern void ScalerTypeC0PdIntTxDellVdmReqSuccessProc_EXINT0(void);
#endif
extern void ScalerTypeC0PdIntTxVdmRespSuccessProc_EXINT0(void);
#endif  // End of #if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
// PD FW Timer Event Function
extern void ScalerTypeC0PdActiveTimerEvent_EXINT0(WORD usTime, EnumScalerTimerEventID enumEventID);
// PD Send Msg. Functions
extern void ScalerTypeC0PdSendMsg_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructMsg_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructDataObj_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern BYTE ScalerTypeC0PdSetVdmDataObjCnt_EXINT0(EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructVdmDataObj_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdSetProductTypeVDO_EXINT0(void);
extern void ScalerTypeC0PdSendSoftRst_EXINT0(EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeC0PdConstructSoftReset_EXINT0(EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeC0PdProcHardRst_EXINT0(void);
// PD Receive Message Functions
extern void ScalerTypeC0PdRxInvalidPktFilter_EXINT0(void);
extern EnumTypeCRxFifoIndex ScalerTypeC0PdRxFifoSelect_EXINT0(void);
extern void ScalerTypeC0PdRxFifoMsgDecode_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo);
extern void ScalerTypeC0PdRxReadDataObj_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo);
extern void ScalerTypeC0PdRxFifoClear_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo);
extern void ScalerTypeC0PdUnattachCancelTimerEvent_EXINT0(void);
extern EnumTypeCTxCheckResult ScalerTypeC0PdTxAvaliable_EXINT0(void);
// PD FW Supplementary Functions
extern void ScalerTypeC0PdRxIntControl_EXINT0(bit b1Action);
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
extern void ScalerTypeC0PdSetPortPartnerRetryCounter_EXINT0(void);
extern void ScalerTypeC0PdSetCableRetryCounter_EXINT0(void);
#else
extern void ScalerTypeC0PdUpdatePortPartnerRetryCounter_EXINT0(void);
extern void ScalerTypeC0PdUpdateCableRetryCounter_EXINT0(void);
#endif
extern void ScalerTypeC0PdUpdateTxFifoMsgHeader_EXINT0(void);
extern void  ScalerTypeC0PdBackToReadyState_EXINT0(void);
extern BYTE ScalerTypeC0PdCheckPowerContractValid_EXINT0(void);
extern EnumTypeCPDRebuildPowerContract ScalerTypeC0PdCheckRebuildPowerContract_EXINT0(void);
extern void ScalerTypeC0PdSaveCableDiscoverIdAckInfo_EXINT0(void);
extern EnumTypeCPDRequestValid ScalerTypeC0PdCheckRequestValid_EXINT0(void);
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
extern BYTE ScalerTypeC0PdCheckEPRCapable_EXINT0(void);
#endif
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
extern BYTE ScalerTypeC0PdSearchSvid_EXINT0(void);
extern void ScalerTypeC0PdSearchMode_EXINT0(void);
extern void ScalerTypeC0PdUpdatePortPartnerDpStatus_EXINT0(EnumTypeCVdmDpCmd enumVdmDpCmd);
extern EnumTypeCPDDpStatusCheckResult ScalerTypeC0PdCheckDpStatus_EXINT0(void);
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
extern EnumTypeCPDAltModeState ScalerTypeC0PdJudgeCableId_EXINT0(void);
extern void ScalerTypeC0PdSearchCableSvid_EXINT0(void);
extern void ScalerTypeC0PdSaveCableDpModeInfo_EXINT0(void);
extern void ScalerTypeC0PdSaveCableTbt3ModeInfo_EXINT0(void);
extern EnumTypeCPDAltModeState ScalerTypeC0PdJudgeCableDpFunctionality_EXINT0(void);
extern EnumTypeCPDAltModeState ScalerTypeC0PdJudgeCableTbt3Mode_EXINT0(void);
extern void ScalerTypeC0PdUfpSaveCableInfoForDpcd_EXINT0(void);
#endif
extern BYTE ScalerTypeC0PdCheckDpConfig_EXINT0(void);
extern BYTE ScalerTypeC0PdDfpJudgePinAssignment_EXINT0(void);
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC0PdPopHpd_EXINT0(void);
#elif(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
extern EnumTypeCPDHpdType ScalerTypeC0PdDecodePartnerHpdStatus_EXINT0(void);
#endif  // End of #if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#endif  // End of #if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern void ScalerTypeC0PdCheckLenovoDeviceId_EXINT0(void);
extern void ScalerTypeC0PdCheckLenovoStatus_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void ScalerTypeC0PdGetAcerSysStatus_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void ScalerTypeC0PdSetHpOwnAddr_EXINT0(void);
extern BYTE ScalerTypeC0PdCheckHpVdmValid_EXINT0(void);
extern void ScalerTypeC0PdGetHpSysStatus_EXINT0(EnumTypeCHpSysEvent enumSysEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern void ScalerTypeC0PdGetDellSysInfo_EXINT0(void);
#endif
#endif  // End of #if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
extern void ScalerTypeC0PdClrHpd_EXINT0(void);

// WDINT
// PD Send Msg. Functions
extern void ScalerTypeC0PdWDTimerEventCableProc_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
extern void ScalerTypeC0PdActiveTimerEvent_WDINT(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerTypeC0PdSendMsg_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructMsg_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructDataObj_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdConstructVdmDataObj_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd);
extern void ScalerTypeC0PdSendSoftRst_WDINT(EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeC0PdConstructSoftReset_WDINT(EnumTypeCPDPacketType enumPacketType);
extern void ScalerTypeC0PdProcHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
extern EnumTypeCTxCheckResult ScalerTypeC0PdTxAvaliable_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
// PD FW Supplementary Functions
extern void ScalerTypeC0PdRxIntControl_WDINT(bit b1Action);
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
extern void ScalerTypeC0PdUpdateCableRetryCounter_WDINT(void);
#endif
extern void ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT(void);
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
extern EnumTypeCPDAltModeState ScalerTypeC0PdJudgeCableDpFunctionality_WDINT(void);
#endif
#endif
#endif
extern void ScalerTypeC0PdBackToReadyState_WDINT(void);
extern void ScalerTypeC0PdPushHpd_WDINT(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))


#endif // End of #ifndef __SCALER_TYPEC0_PD_H__
