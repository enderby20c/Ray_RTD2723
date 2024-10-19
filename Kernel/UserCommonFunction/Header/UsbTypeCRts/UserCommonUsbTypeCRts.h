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
// ID Code      : UserCommonUsbTypeCRts.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_USB_TYPE_CRTS_H__
#define __USER_COMMON_USB_TYPE_CRTS_H__

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definition of Type-C RTS Port Controller Related Macro
//--------------------------------------------------
#define GET_TYPE_C_RTS_I2C_ENABLED_FLG(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1I2CEnabledFlag)
#define SET_TYPE_C_RTS_I2C_ENABLED_FLG(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1I2CEnabledFlag = _TRUE)
#define CLR_TYPE_C_RTS_I2C_ENABLED_FLG(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1I2CEnabledFlag = _FALSE)

#define GET_TYPE_C_RTS_DATA_ROLE(x)                         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].enumDataRole)
#define SET_TYPE_C_RTS_DATA_ROLE(x, y)                      (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].enumDataRole = (y))

#define GET_TYPE_C_RTS_POWER_ROLE(x)                        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].enumPowerRole)
#define SET_TYPE_C_RTS_POWER_ROLE(x, y)                     (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].enumPowerRole = (y))

#define GET_TYPE_C_RTS_PORT_PARTNER_FLAG(x)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucPortPartnerFlag)
#define SET_TYPE_C_RTS_PORT_PARTNER_FLAG(x, y)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucPortPartnerFlag = (y))

#define GET_TYPE_C_RTS_DETECT_STATUS(x)                     (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectStatusFlag)
#define SET_TYPE_C_RTS_DETECT_STATUS(x)                     (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectStatusFlag = _TRUE)
#define CLR_TYPE_C_RTS_DETECT_STATUS(x)                     (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectStatusFlag = _FALSE)

// Rts I2C Write Cmd Extend Info
#define GET_TYPE_C_RTS_I2C_WR_EXTEND_INFO(x)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucI2CWrExtendInfo)
#define SET_TYPE_C_RTS_I2C_WR_EXTEND_INFO(x, y)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucI2CWrExtendInfo = (y))
#define CLR_TYPE_C_RTS_I2C_WR_EXTEND_INFO(x)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucI2CWrExtendInfo = 0)

// Rts Cable Information for DPCD Macro
#define GET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(x)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.enumTypeCCableActiveComponent)
#define SET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(x, y)           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.enumTypeCCableActiveComponent = (y))

#define GET_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(x)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.b1CableUhbr13p5Support)
#define SET_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(x)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.b1CableUhbr13p5Support = _TRUE)
#define CLR_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(x)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.b1CableUhbr13p5Support = _FALSE)

#define GET_TYPE_C_RTS_CBL_MAX_DP_RATE(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.enumTypeCCableMaxDpRate)
#define SET_TYPE_C_RTS_CBL_MAX_DP_RATE(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stCableInfo.enumTypeCCableMaxDpRate = (y))

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
// RTS Port Operation Mode Macro
#define GET_TYPE_C_RTS_PORT_OPERATION_MODE(x)               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3PortOpMode)
#define SET_TYPE_C_RTS_PORT_OPERATION_MODE(x, y)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3PortOpMode = (y))
#define CLR_TYPE_C_RTS_PORT_OPERATION_MODE(x)               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3PortOpMode = 0)

// Currently Negotiated Request Info Macro
#define GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(x)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b4ReqObjPos)
#define SET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(x, y)         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b4ReqObjPos = (y))
#define CLR_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(x)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b4ReqObjPos = 0)

#define GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(x)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo0)
#define SET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(x, y)          (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo0 = (y))
#define CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(x)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo0 = 0)

#define GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(x)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo1)
#define SET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(x, y)          (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo1 = (y))
#define CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(x)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo1 = 0)

#define GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(x)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo2)
#define SET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(x, y)          (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo2 = (y))
#define CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(x)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucReqInfo2 = 0)

// RTS Explicit Contract Macro
#define GET_TYPE_C_RTS_EXPLICIT_CONTRACT(x)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1PowerContract)
#define SET_TYPE_C_RTS_EXPLICIT_CONTRACT(x)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1PowerContract = _TRUE)
#define CLR_TYPE_C_RTS_EXPLICIT_CONTRACT(x)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1PowerContract = _FALSE)

// RTS Source Capability Macros
#define GET_TYPE_C_RTS_DRP(x)                               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DualRolePower)
#define SET_TYPE_C_RTS_DRP(x, y)                            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DualRolePower = (y))
#define CLR_TYPE_C_RTS_DRP(x)                               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DualRolePower = _FALSE)

#define GET_TYPE_C_RTS_DRD(x)                               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DualRoleData)
#define SET_TYPE_C_RTS_DRD(x, y)                            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DualRoleData = (y))
#define CLR_TYPE_C_RTS_DRD(x)                               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DualRoleData = _FALSE)

#define GET_TYPE_C_RTS_SUSPEND(x)                           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1SuspendSupport)
#define SET_TYPE_C_RTS_SUSPEND(x, y)                        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1SuspendSupport = (y))
#define CLR_TYPE_C_RTS_SUSPEND(x)                           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1SuspendSupport = _FALSE)

#define GET_TYPE_C_RTS_EXT_PWR(x)                           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1ExtPower)
#define SET_TYPE_C_RTS_EXT_PWR(x, y)                        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1ExtPower = (y))
#define CLR_TYPE_C_RTS_EXT_PWR(x)                           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1ExtPower = _FALSE)

#define GET_TYPE_C_RTS_USB_CAP(x)                           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1UsbCapable)
#define SET_TYPE_C_RTS_USB_CAP(x, y)                        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1UsbCapable = (y))
#define CLR_TYPE_C_RTS_USB_CAP(x)                           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1UsbCapable = _FALSE)

#define GET_TYPE_C_RTS_UNCHK(x)                             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1UnchkSupport)
#define SET_TYPE_C_RTS_UNCHK(x, y)                          (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1UnchkSupport = (y))
#define CLR_TYPE_C_RTS_UNCHK(x)                             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1UnchkSupport = _FALSE)

#define GET_TYPE_C_RTS_MAX_POWER(x)                         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].usMaxPower)
#define SET_TYPE_C_RTS_MAX_POWER(x, y)                      (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].usMaxPower = (y))

#define GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfSPRSrcCap)
#define SET_TYPE_C_RTS_SPR_SRC_CAP_CNT(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfSPRSrcCap = (y))

#define GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfEPRSrcCap)
#define SET_TYPE_C_RTS_EPR_SRC_CAP_CNT(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfEPRSrcCap = (y))

#define GET_TYPE_C_RTS_SRC_CAP_TYPE(x, y)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].enumPdoType)
#define SET_TYPE_C_RTS_SRC_CAP_TYPE(x, y, z)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].enumPdoType = (z))

#define GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].usMaxVoltage)
#define SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(x, y, z)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].usMaxVoltage = (z))

#define GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].usMinVoltage)
#define SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(x, y, z)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].usMinVoltage = (z))

#define GET_TYPE_C_RTS_SRC_CAP_CUR(x, y)                    (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].usMaxCurrent)
#define SET_TYPE_C_RTS_SRC_CAP_CUR(x, y, z)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].usMaxCurrent = (z))

#define GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(x, y)               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].enumPeakCurrent)
#define SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(x, y, z)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSrcPdo[y].enumPeakCurrent = (z))

// RTS Sink Capability Macros
#define GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfSPRSnkCap)
#define SET_TYPE_C_RTS_SPR_SNK_CAP_CNT(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfSPRSnkCap = (y))

#define GET_TYPE_C_RTS_EPR_SNK_CAP_CNT(x)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfEPRSnkCap)
#define SET_TYPE_C_RTS_EPR_SNK_CAP_CNT(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfEPRSnkCap = (y))

#define GET_TYPE_C_RTS_SNK_CAP_TYPE(x, y)                   (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].enumPdoType)
#define SET_TYPE_C_RTS_SNK_CAP_TYPE(x, y, z)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].enumPdoType = (z))

#define GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].usMaxVoltage)
#define SET_TYPE_C_RTS_SNK_CAP_VOL_MAX(x, y, z)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].usMaxVoltage = (z))

#define GET_TYPE_C_RTS_SNK_CAP_VOL_MIN(x, y)                (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].usMinVoltage)
#define SET_TYPE_C_RTS_SNK_CAP_VOL_MIN(x, y, z)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].usMinVoltage = (z))

#define GET_TYPE_C_RTS_SNK_CAP_CUR(x, y)                    (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].usMaxCurrent)
#define SET_TYPE_C_RTS_SNK_CAP_CUR(x, y, z)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstSnkPdo[y].usMaxCurrent = (z))

// Port Partner(Other Side) Source Capability Macros
#define GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(x)           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfPartnerSPRSrcCap)
#define SET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(x, y)        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfPartnerSPRSrcCap = (y))

#define GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(x)           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfPartnerEPRSrcCap)
#define SET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(x, y)        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b3NumOfPartnerEPRSrcCap = (y))

#define GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(x, y)           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPdoType)
#define SET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(x, y, z)        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPdoType = (z))

#define GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(x, y)        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMaxVoltage)
#define SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(x, y, z)     (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMaxVoltage = (z))

#define GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(x, y)        (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMinVoltage)
#define SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(x, y, z)     (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMinVoltage = (z))

#define GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(x, y)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMaxCurrent)
#define SET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(x, y, z)         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMaxCurrent = (z))

#define GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(x, y)       (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPeakCurrent)
#define SET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(x, y, z)    (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPeakCurrent = (z))

// Power Contract Negotiated Power Status
#define GET_TYPE_C_RTS_PDO_STATUS_VOL(x)                    (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].usPdoStatusVoltage)
#define SET_TYPE_C_RTS_PDO_STATUS_VOL(x, y)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].usPdoStatusVoltage = (y))

#define GET_TYPE_C_RTS_PDO_STATUS_CUR(x)                    (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].usPdoStatusCurrent)
#define SET_TYPE_C_RTS_PDO_STATUS_CUR(x, y)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].usPdoStatusCurrent = (y))

// Rts Target Request Info Macro
#define GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(x)                ((BYTE)(g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.enumObjPos))
#define SET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(x, y)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.enumObjPos = (y))

#define GET_TYPE_C_RTS_TARGET_REQ_CAP_MIS(x)                ((BYTE)(g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.b1CapMismatch))
#define SET_TYPE_C_RTS_TARGET_REQ_CAP_MIS(x, y)             (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.b1CapMismatch = (y))

#define GET_TYPE_C_RTS_TARGET_REQ_GIVE_BACK(x)              ((BYTE)(g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.b1GiveBack))
#define SET_TYPE_C_RTS_TARGET_REQ_GIVE_BACK(x, y)           (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.b1GiveBack = (y))

#define GET_TYPE_C_RTS_TARGET_REQ_INFO_1(x)                 ((WORD)(g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.usReqInfo1))
#define SET_TYPE_C_RTS_TARGET_REQ_INFO_1(x, y)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.usReqInfo1 = (y))

#define GET_TYPE_C_RTS_TARGET_REQ_INFO_2(x)                 ((WORD)(g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.usReqInfo2))
#define SET_TYPE_C_RTS_TARGET_REQ_INFO_2(x, y)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].stTargetRdo.usReqInfo2 = (y))
#endif

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(x)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectLenovoAltModeFlag)
#define SET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(x)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectLenovoAltModeFlag = _TRUE)
#define CLR_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(x)            (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectLenovoAltModeFlag = _FALSE)

#define GET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(x)         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag)
#define SET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(x)         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag = _TRUE)
#define CLR_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(x)         (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag = _FALSE)

#define GET_TYPE_C_RTS_LENOVO_VDM_RECEIVED(x)               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1LenovoVdmReceived)
#define SET_TYPE_C_RTS_LENOVO_VDM_RECEIVED(x)               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1LenovoVdmReceived = _TRUE)
#define CLR_TYPE_C_RTS_LENOVO_VDM_RECEIVED(x)               (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].b1LenovoVdmReceived = _FALSE)

#define GET_TYPE_C_RTS_LENOVO_DOCK_EVENT(x)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucLenovoDockingEvent)
#define SET_TYPE_C_RTS_LENOVO_DOCK_EVENT(x, y)              (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].ucLenovoDockingEvent = (y))
#endif

//--------------------------------------------------
// Definition of Type-C RTS SMBUS Detect Debounce Related Macro
//--------------------------------------------------
#if(_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsD0DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsD0DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsD0DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_D0_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsD0DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_D0_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsD0DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_D0_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsD0DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsD1DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsD1DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsD1DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_D1_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsD1DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_D1_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsD1DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_D1_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsD1DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsD2DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsD2DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsD2DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_D2_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsD2DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_D2_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsD2DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_D2_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsD2DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P0_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsP0DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_P0_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP0DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_P0_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP0DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P0_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsP0DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_P0_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP0DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_P0_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP0DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P1_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsP1DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_P1_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP1DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_P1_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP1DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P1_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsP1DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_P1_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP1DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_P1_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP1DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P2_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsP2DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_P2_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP2DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_P2_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP2DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P2_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsP2DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_P2_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP2DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_P2_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP2DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P3_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsP3DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_P3_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP3DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_P3_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP3DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P3_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsP3DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_P3_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP3DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_P3_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP3DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P4_DP_DETECT_CC_ATTACH()             ((bit)g_stUsbTypeCRtsP4DetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_P4_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP4DetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_P4_DP_DETECT_CC_ATTACH()             (g_stUsbTypeCRtsP4DetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_P4_DP_DETECT_ALT_MODE()              ((bit)g_stUsbTypeCRtsP4DetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_P4_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP4DetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_P4_DP_DETECT_ALT_MODE()              (g_stUsbTypeCRtsP4DetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_ADAPTOR_DETECT_CC_ATTACH()           ((bit)g_stUsbTypeCRtsAdaptorDetectInfo.b1DetectCcAttachFlag)
#define SET_USB_TYPE_C_ADAPTOR_DETECT_CC_ATTACH()           (g_stUsbTypeCRtsAdaptorDetectInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_USB_TYPE_C_ADAPTOR_DETECT_CC_ATTACH()           (g_stUsbTypeCRtsAdaptorDetectInfo.b1DetectCcAttachFlag = _FALSE)
#endif
#if(_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#define GET_USB_TYPE_C_ADAPTOR_DETECT_ALT_MODE()            ((bit)g_stUsbTypeCRtsAdaptorDetectInfo.b1DetectAltModeFlag)
#define SET_USB_TYPE_C_ADAPTOR_DETECT_ALT_MODE()            (g_stUsbTypeCRtsAdaptorDetectInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_USB_TYPE_C_ADAPTOR_DETECT_ALT_MODE()            (g_stUsbTypeCRtsAdaptorDetectInfo.b1DetectAltModeFlag = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonUsbTypeCRtsUpdateRoleInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE UserCommonUsbTypeCRtsGetI2CPinNum(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
extern bit UserCommonUsbTypeCRtsUpdateSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCRtsUpdatePartnerSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsUpdatePdoStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
extern void UserCommonUsbTypeCRtsGetUserNotifyEn(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCRtsNotifyEn *pstTypeCNotifyEn);
extern bit UserCommonUsbTypeCRtsSetNotifyEn(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCRtsNotifyEn stTypeCNotifyEn);
#endif
extern bit UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType);
extern bit UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType, BYTE *pucReadInfo);
extern bit UserCommonUsbTypeCRtsWriteCommand(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType);
extern bit UserCommonUsbTypeCRtsReadCommand(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType);
extern EnumTypeCPinCfgType UserCommonUsbTypeCRtsDecodePinAssignment(BYTE ucPdInfo);
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))

#endif // End of #ifndef __USER_COMMON_USB_TYPE_CRTS_H__
