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
// ID Code      : UserCommonUsbTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLER_COMMON__

#include "UserCommonInclude.h"
#include "UsbTypeC/UserCommonUsbTypeC.h"

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Return External Port Ctrl CC Attached Status
// Input Value  : enumTypeCPcbPort
// Output Value : CC Attach Enumeration (_TYPE_C_ATTACH / _TYPE_C_UNATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonUsbTypeCGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;

#if(_PORT_CTRL_RTS_SUPPORT == _ON)
    if(UserCommonUsbTypeCRtsGetI2CEnabledFlag(enumTypeCPcbPort) == _FALSE)
    {
        // RTS Port Ctrl : Enable Vender Command
        if(UserCommonUsbTypeCRtsInitializeI2CCommunication(enumTypeCPcbPort) == _SUCCESS)
        {
            // RTS Port Ctrl : Set I2C Communication Enabled Flag
            UserCommonUsbTypeCRtsSetI2CEnabledFlag(enumTypeCPcbPort);

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
            if(UserCommonUsbTypeCSpmOperation() == _TYPE_C_SPM_FIX_DEFAULT_POWER)
            {
                // Update Source Capability and Sink Capability to RTS Port Ctrl
                SysUsbTypeCUpdatePortCtrlSrcPdo(enumTypeCPcbPort);
                SysUsbTypeCUpdatePortCtrlSnkPdo(enumTypeCPcbPort);
            }
#endif
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
#endif

    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D0_TYPE_C_PORT:

#if(_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_D0_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_D0_TYPE_C_PORT);
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_D0_TYPE_C_PORT);
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_D0_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D1_TYPE_C_PORT:

#if(_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_D1_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_D1_TYPE_C_PORT);
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_D1_TYPE_C_PORT);
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_D1_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D2_TYPE_C_PORT:

#if(_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_D2_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_D2_TYPE_C_PORT);
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_D2_TYPE_C_PORT);
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_D2_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P0_TYPE_C_PORT:

#if(_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_P0_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_P0_TYPE_C_PORT);
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_P0_TYPE_C_PORT);
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_P0_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P1_TYPE_C_PORT:

#if(_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_P1_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_P1_TYPE_C_PORT);
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_P1_TYPE_C_PORT);
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_P1_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P2_TYPE_C_PORT:

#if(_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_P2_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_P2_TYPE_C_PORT);
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_P2_TYPE_C_PORT);
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_P2_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P3_TYPE_C_PORT:

#if(_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_P3_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_P3_TYPE_C_PORT);
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_P3_TYPE_C_PORT);
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_P3_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P4_TYPE_C_PORT:

#if(_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_P4_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_P4_TYPE_C_PORT);
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_P4_TYPE_C_PORT);
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_P4_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _ADAPTOR_TYPE_C_PORT:

#if(_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumCcAttach = (PCB_ADAPTOR_CC_ATTACH() == _PCB_DP_TYPE_C_CC_ATTACH_LEVEL ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumCcAttach = UserCommonUsbTypeCRtsGetCcAttachByI2C(_ADAPTOR_TYPE_C_PORT);
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumCcAttach = UserCommonUsbTypeCUserGetCcAttachByI2C(_ADAPTOR_TYPE_C_PORT);
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumCcAttach = UserCommonUsbTypeCRtdGetCcAttachByI2C(_ADAPTOR_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

        default:

            break;
    }

    return enumCcAttach;
}

//--------------------------------------------------
// Description  : Return External Port Ctrl DP Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonUsbTypeCGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAltModeStatus enumAltModeReady = _TYPE_C_ALT_MODE_NOT_READY;

    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D0_TYPE_C_PORT:

#if(_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_D0_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_D0_TYPE_C_PORT);
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_D0_TYPE_C_PORT);
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_D0_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D1_TYPE_C_PORT:

#if(_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_D1_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_D1_TYPE_C_PORT);
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_D1_TYPE_C_PORT);
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_D1_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D2_TYPE_C_PORT:

#if(_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_D2_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_D2_TYPE_C_PORT);
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_D2_TYPE_C_PORT);
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_D2_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P0_TYPE_C_PORT:

#if(_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_P0_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_P0_TYPE_C_PORT);
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_P0_TYPE_C_PORT);
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_P0_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P1_TYPE_C_PORT:

#if(_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_P1_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_P1_TYPE_C_PORT);
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_P1_TYPE_C_PORT);
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_P1_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P2_TYPE_C_PORT:

#if(_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_P2_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_P2_TYPE_C_PORT);
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_P2_TYPE_C_PORT);
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_P2_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P3_TYPE_C_PORT:

#if(_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_P3_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_P3_TYPE_C_PORT);
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_P3_TYPE_C_PORT);
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_P3_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P4_TYPE_C_PORT:

#if(_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_P4_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_P4_TYPE_C_PORT);
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_P4_TYPE_C_PORT);
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_P4_TYPE_C_PORT);
#endif
#endif
            break;
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _ADAPTOR_TYPE_C_PORT:

#if(_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO)
            enumAltModeReady = (PCB_ADAPTOR_ALT_MODE_READY() == _PCB_DP_TYPE_C_ALTMODE_LEVEL ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)
#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            enumAltModeReady = UserCommonUsbTypeCRtsGetAltModeReadyByI2C(_ADAPTOR_TYPE_C_PORT);
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            enumAltModeReady = UserCommonUsbTypeCUserGetAltModeReadyByI2C(_ADAPTOR_TYPE_C_PORT);
#elif(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            enumAltModeReady = UserCommonUsbTypeCRtdGetAltModeReadyByI2C(_ADAPTOR_TYPE_C_PORT);
#endif

#endif
            break;
#endif  // End of #if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

        default:

            break;
    }

    return enumAltModeReady;
}

//--------------------------------------------------
// Description  : Update Port Controller Pin Assignment & Multi Function Configuration
// Input Value  : enumTypeCPcbPort
// Output Value : Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit UserCommonUsbTypeCUpdateConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    BYTE ucConfigPinAssignResult = _FAIL;
    BYTE ucConfigMultiFuncResult = _FAIL;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_D0_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_D0_TYPE_C_PORT, enumMultiFunc);
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_D0_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_D0_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_D0_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_D1_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_D1_TYPE_C_PORT, enumMultiFunc);
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_D1_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_D1_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_D1_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_D2_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_D2_TYPE_C_PORT, enumMultiFunc);
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_D2_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_D2_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_D2_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_P0_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_P0_TYPE_C_PORT, enumMultiFunc);
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_P0_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_P0_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_P0_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_P1_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_P1_TYPE_C_PORT, enumMultiFunc);
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_P1_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_P1_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_P1_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_P2_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_P2_TYPE_C_PORT, enumMultiFunc);
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_P2_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_P2_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_P2_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_P3_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_P3_TYPE_C_PORT, enumMultiFunc);
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_P3_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_P3_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_P3_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_TYPE_C_PORT:

            // 1. Config Pin Assignment & Milti-Function Bit
#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtsConfigPinAssignment(_P4_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCRtsConfigMultiFunction(_P4_TYPE_C_PORT, enumMultiFunc);
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
            ucConfigPinAssignResult = UserCommonUsbTypeCRtdSetPinAssignment(_P4_TYPE_C_PORT, enumMultiFunc, enumPinAssignmentCap);
            ucConfigMultiFuncResult = ucConfigPinAssignResult;
#elif(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
            ucConfigPinAssignResult = UserCommonUsbTypeCUserConfigPinAssignment(_P4_TYPE_C_PORT, enumPinAssignmentCap);
            ucConfigMultiFuncResult = UserCommonUsbTypeCUserConfigMultiFunction(_P4_TYPE_C_PORT, enumMultiFunc);
#endif

            break;
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:
            // Adaptor TypeC Port Does Not Support Alt Mode
            DebugMessageTypeC("8. Type-C Reconnect : Update Config with Invalid Input Port", enumTypeCPcbPort);

            break;
    }

    if((ucConfigPinAssignResult == _FAIL) || (ucConfigMultiFuncResult == _FAIL))
    {
        DebugMessageTypeC("8. Config Result : [1] Pin Assignment / [0] Multi-Function (1 Success / 0 Fail) ", ((ucConfigPinAssignResult << 1) | ucConfigMultiFuncResult));
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get Power Off Flag to set Capability Change Flag
// Input Value  : enumTypeCPcbPort, enumSwitch
// Output Value : return _TYPE_C_PORT_CTRL_NO_RECONNECT / _TYPE_C_PORT_CTRL_RECONNECT
//--------------------------------------------------
EnumTypeCPortCtrlReconnectStatus UserCommonUsbTypeCGetPowerOnReconnectStatus(EnumTypeCPcbPort enumTypeCPcbPort, EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            return _TYPE_C_PORT_CTRL_RECONNECT;

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

            return UserInterfaceUsbTypeCGetPowerOnReconnectStatus(enumTypeCPcbPort, _POWER_ACTION_OFF_TO_NORMAL);

            break;

        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_FAKE_PS_TO_NORMAL:

            return UserInterfaceUsbTypeCGetPowerOnReconnectStatus(enumTypeCPcbPort, _POWER_ACTION_PS_TO_NORMAL);

            break;

        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            return _TYPE_C_PORT_CTRL_NO_RECONNECT;

            break;

        default:

            return _TYPE_C_PORT_CTRL_RECONNECT;

            break;
    }

    return _TYPE_C_PORT_CTRL_RECONNECT;
}
#endif  // End of #if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OSD Type-C Pin Assignment E Support Selection
// Input Value  : enumTypeCPcbPort
// Output Value : _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON or _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
//--------------------------------------------------
EnumTypeCPinAssignmentESupportStatus UserCommonUsbTypeCGetOsdPinAssignmentESupportSelection(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);
#endif
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
    EnumOutputPort enumOutputPort = SysUsbTypeCConvertToPxPort(enumTypeCPcbPort);
#endif
    enumPinAssignmentESupportStatus = enumPinAssignmentESupportStatus;

    if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
    {
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
        enumPinAssignmentESupportStatus = UserInterfaceUsbTypeCGetOsdPinAssignmentESupportSelection(enumInputPort);
#endif
    }
    else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
    {
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
        enumPinAssignmentESupportStatus = UserInterfaceUsbTypeCGetOsdTxPinAssignmentESupportSelection(enumOutputPort);
#endif
    }

    return enumPinAssignmentESupportStatus;
}
#endif

//--------------------------------------------------
// Description  : User Define Pin Assignment According to U3 Mode
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserCommonUsbTypeCGetPinAssignmentConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Default Set Pin Assignment E Support Status to ON
    EnumTypeCU3ModeType enumU3ModeSel = _TYPE_C_U3_OFF;
    EnumTypeCPinCfgCapType enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_NONE;
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);
#endif
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
    EnumOutputPort enumOutputPort = SysUsbTypeCConvertToPxPort(enumTypeCPcbPort);
#endif
    enumU3ModeSel = enumU3ModeSel;
    enumPinAssignmentCap = enumPinAssignmentCap;
    enumPinAssignmentESupportStatus = enumPinAssignmentESupportStatus;

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    // Update Pin Assignment E Support Capability (From User)
    if(UserCommonUsbTypeCGetOsdPinAssignmentESupportSelection(enumTypeCPcbPort) == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF)
    {
        enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF;
    }
#endif

    // Update U3 Mode (From OSD)
    enumU3ModeSel = (UserCommonUsbGetOsdU3Mode(enumTypeCPcbPort) == _USB_HUB_MODE_U3) ? _TYPE_C_U3_ON : _TYPE_C_U3_OFF;

    if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
    {
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
        enumPinAssignmentCap = UserInterfaceUsbTypeCGetPinAssignmentConfig(enumInputPort, enumU3ModeSel, enumPinAssignmentESupportStatus);
#endif
    }
    else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
    {
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
        enumPinAssignmentCap = UserInterfaceUsbTypeCGetTxPinAssignmentConfig(enumOutputPort, enumU3ModeSel, enumPinAssignmentESupportStatus);
#endif
    }

    if(enumPinAssignmentCap == _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT)
    {
        if(SysUsbTypeCGetExtPortCtrlAcOnFlag(enumTypeCPcbPort) == _TRUE)
        {
            // If (Ext Port Ctrl AC ON == _TRUE), Set Pin Assignment Cap to None
            enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_NONE;
        }
        else
        {
            // Use Kernel Default Setting if User Select Follow Kernel Setting
            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportStatus == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportStatus == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }
        }
    }

    return enumPinAssignmentCap;
}

//--------------------------------------------------
// Description  : User Define Multi Function According to U3 Mode
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//                enumPinAssignmentCap --> _TYPE_C_PIN_ASSIGNMENT_CAP_NONE / _TYPE_C_PIN_ASSIGNMENT_CAP_C / ...
// Output Value : Multi Function Status
//--------------------------------------------------
EnumTypeCMultiFuncStatus UserCommonUsbTypeCGetMultiFuncConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    EnumTypeCU3ModeType enumU3ModeSel = _TYPE_C_U3_OFF;
    EnumTypeCMultiFuncStatus enumMultiFunc = _TYPE_C_MULTI_FUNC_NOT_PREFER;
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);
#endif
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
    EnumOutputPort enumOutputPort = SysUsbTypeCConvertToPxPort(enumTypeCPcbPort);
#endif

    enumPinAssignmentCap = enumPinAssignmentCap;

    // Update U3 Mode (From OSD)
    enumU3ModeSel = (UserCommonUsbGetOsdU3Mode(enumTypeCPcbPort) == _USB_HUB_MODE_U3) ? _TYPE_C_U3_ON : _TYPE_C_U3_OFF;

    if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
    {
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
        enumMultiFunc = UserInterfaceUsbTypeCGetMultiFuncConfig(enumInputPort, enumU3ModeSel);
#endif
    }
    else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
    {
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
        enumMultiFunc = UserInterfaceUsbTypeCGetTxMultiFuncConfig(enumOutputPort, enumU3ModeSel);
#endif
    }

    if(enumMultiFunc == _TYPE_C_MULTI_FUNC_DEFAULT)
    {
        // Default Setting, Set Multi-Function Prefer according to Pin Assignment-D Exist or not
        enumMultiFunc = ((enumPinAssignmentCap & _BIT3) == _BIT3) ? _TYPE_C_MULTI_FUNC_PREFER : _TYPE_C_MULTI_FUNC_NOT_PREFER;
    }

    return enumMultiFunc;
}

//--------------------------------------------------
// Description  : Check Action for Pin Assignment Mismatch
// Input Value  : enumTypeCPcbPort
// Output Value : return _TYPE_C_PIN_ASSIGNMENT_MISMATCH_NO_ACTION / _TYPE_C_PIN_ASSIGNMENT_MISMATCH_RECONNECT
//--------------------------------------------------
EnumTypeCPinMismatchAction UserCommonUsbTypeCGetPinAssignmentMismatchAction(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbTypeCGetPinAssignmentMismatchAction(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : For User Updating Display Config When DP Alt Mode Ready Status Changes
// Input Value  : enumTypeCPcbPort, enumPinAssignment
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUpdateDisplayConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment)
{
    // For User To Update EDID or Other Display Config
    UserInterfaceUsbTypeCUpdateDisplayConfig(enumTypeCPcbPort, enumPinAssignment);
}

//--------------------------------------------------
// Description  : TypeC Get Dp Alt Mode Wait Status
// Input Value  : enumTypeCPcbPort
// Output Value : Dp Alt Mode Wait Status (_TYPE_C_ALT_MODE_WAIT / _TYPE_C_ALT_MODE_NOT_WAIT)
//--------------------------------------------------
EnumTypeCAltModeWaitStatus UserCommonUsbTypeCGetDpAltModeWaitStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbTypeCGetDpAltModeWaitStatus(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Get Type-C Function Support Option
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Function Support Option (_TYPE_C_SUPPORT_NO_FUNCTION / _TYPE_C_SUPPORT_CC_FUNCTION / _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION...)
//--------------------------------------------------
EnumTypeCFunctionSupport UserCommonUsbTypeCGetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCFunctionSupport enumFunctionSupport = _TYPE_C_SUPPORT_DEFAULT_FUNCTION;

    enumFunctionSupport = UserInterfaceUsbTypeCGetFunctionSupport(enumTypeCPcbPort);

    if(enumFunctionSupport == _TYPE_C_SUPPORT_DEFAULT_FUNCTION)
    {
        enumFunctionSupport = _TYPE_C_SUPPORT_FULL_FUNCTION;
    }

    return enumFunctionSupport;
}

//--------------------------------------------------
// Description  : Get Type-C Operation Mode
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Operation Mode (_TYPE_C_SRC_ONLY_MODE / _TYPE_C_SNK_ONLY_MODE / _TYPE_C_DRP_NO_PREFERENCE_MODE...)
//--------------------------------------------------
EnumTypeCOperationMode UserCommonUsbTypeCGetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCOperationMode enumOperationMode = _TYPE_C_DEFAULT_OPERATION_MODE;

    enumOperationMode = UserInterfaceUsbTypeCGetOperationMode(enumTypeCPcbPort);

    if(enumOperationMode == _TYPE_C_DEFAULT_OPERATION_MODE)
    {
        enumOperationMode = SysUsbTypeCGetDefaultOperationMode(enumTypeCPcbPort);
    }

    return enumOperationMode;
}

//--------------------------------------------------
// Description  : Get Type-C Status Event
// Input Value  : enumTypeCPcbPort
//                pstStatusEvent --> Status Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent *pstStatusEvent)
{
    StructTypeCStatusEvent stStatusEvent = {0x00, 0x00};

    UserInterfaceUsbTypeCGetStatusEvent(enumTypeCPcbPort, &stStatusEvent);

    *pstStatusEvent = stStatusEvent;
}

//--------------------------------------------------
// Description  : Get Type-C Alert Event
// Input Value  : enumTypeCPcbPort
//                pstAlertEvent --> Alert Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent *pstAlertEvent)
{
    StructTypeCAlertEvent stAlertEvent = {_TYPE_C_TYPE_OF_ALERT_NONE, _TYPE_C_BAT_NONE, _TYPE_C_EXT_ALERT_EVENT_NONE};

    UserInterfaceUsbTypeCGetAlertEvent(enumTypeCPcbPort, &stAlertEvent);

    *pstAlertEvent = stAlertEvent;

    if((pstAlertEvent->enumTypeOfAlert & _TYPE_C_TYPE_OF_ALERT_EXTALERTEVENT) == _TYPE_C_TYPE_OF_ALERT_EXTALERTEVENT)
    {
        if(((SysUsbTypeCGetDataRole(enumTypeCPcbPort) == _TYPE_C_DFP_U) && ((pstAlertEvent->enumExtAlertEvent == _TYPE_C_EXT_ALERT_EVENT_POWERBUTTON_PRESS) || (pstAlertEvent->enumExtAlertEvent == _TYPE_C_EXT_ALERT_EVENT_POWERBUTTON_RELEASE) || (pstAlertEvent->enumExtAlertEvent == _TYPE_C_EXT_ALERT_EVENT_CTRL_INIT_WAKE))) ||
           ((SysUsbTypeCGetDataRole(enumTypeCPcbPort) == _TYPE_C_UFP_U) && (pstAlertEvent->enumExtAlertEvent == _TYPE_C_EXT_ALERT_EVENT_POWERSTATE_CHG)))
        {
            // If Extended Alert Event Type is Wrong, Set pstAlertEvent->enumTypeOfAlert to _TYPE_C_TYPE_OF_ALERT_NONE
            pstAlertEvent->enumTypeOfAlert = _TYPE_C_TYPE_OF_ALERT_NONE;

            DebugMessageTypeC("8. [TYPE C] Extended Alert Event Type is Wrong, Please Check the Corresponding Data Role", 0x00);
        }
    }
    else
    {
        // If the Extended Alert Event bit is not set, then the Extended Alert Event Type is Reserved and Shall be set to zero.
        pstAlertEvent->enumExtAlertEvent = _TYPE_C_EXT_ALERT_EVENT_NONE;
    }
}

#if(_TYPE_C_EIZO_CUSTOMIZED_DP_LANE_CNT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : For User to Translate Alt. Mode Pin Assignment to DP Lane Count
// Input Value  : enumTypeCPcbPort, enumPinAssignment : _TYPE_C_PIN_ASSIGNMENT_C / _TYPE_C_PIN_ASSIGNMENT_D / _TYPE_C_PIN_ASSIGNMENT_E
// Output Value : EnumDpLaneCount -> _DP_LINK_1_LANE / _DP_LINK_2_LANE / _DP_LINK_4_LANE
//--------------------------------------------------
EnumDpLaneCount UserCommonUsbTypeCGetAltModeLaneCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment)
{
    // For User to Translate Alt. Mode Pin Assignment to DP Lane Count
    return UserInterfaceUsbTypeCGetAltModeLaneCnt(enumTypeCPcbPort, enumPinAssignment);
}
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode Check Lenovo Device Type Valid
// Input Value  : enumTypeCPcbPort, enumLenovoDeviceType
// Output Value : Lenovo Device Type Check Result (_TYPE_C_LENOVO_DEVICE_TYPE_INVALID / _TYPE_C_LENOVO_DEVICE_TYPE_VALID)
//--------------------------------------------------
EnumTypeCLenovoCheckDeviceTypeResult UserCommonUsbTypeCCheckLenovoDeviceTypeValid(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCLenovoDeviceType enumLenovoDeviceType)
{
    return UserInterfaceUsbTypeCCheckLenovoDeviceTypeValid(enumTypeCPcbPort, enumLenovoDeviceType);
}

//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode System Event or System Acknowledge Handler Process
// Input Value  : enumTypeCPcbPort
//                stLenovoSysEvent --> Lenovo System Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCLenovoAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoSysEvent stLenovoSysEvent)
{
    UserInterfaceUsbTypeCLenovoAltModeHandler(enumTypeCPcbPort, stLenovoSysEvent);
}

//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode Get Docking Event
// Input Value  : enumTypeCPcbPort
//                stLenovoDockEvent --> Lenovo Docking Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent)
{
    StructTypeCLenovoDockEvent stLenovoDockEvent = {_TYPE_C_LENOVO_DOCK_POWER_SWITCH_NONE, _FALSE, _FALSE, 0x00};

    UserInterfaceUsbTypeCGetLenovoDockingEvent(enumTypeCPcbPort, &stLenovoDockEvent);

    *pstLenovoDockEvent = stLenovoDockEvent;
}
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Acer Alt Mode System Event Process
// Input Value  : enumTypeCPcbPort
//                stAcerSysEvent --> Acer System Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCAcerAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerSysEvent stAcerSysEvent)
{
    UserInterfaceUsbTypeCAcerAltModeHandler(enumTypeCPcbPort, stAcerSysEvent);
}

//--------------------------------------------------
// Description  : TypeC Acer Alt Mode Get User Event
// Input Value  : enumTypeCPcbPort
//                stAcerUserEvent --> Acer User Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent *pstAcerUserEvent)
{
    StructTypeCAcerUserEvent stAcerUserEvent = {_TYPE_C_ACER_USER_EVENT_NONE, {0x00}, 0x00};

    UserInterfaceUsbTypeCGetAcerUserEvent(enumTypeCPcbPort, &stAcerUserEvent);

    *pstAcerUserEvent = stAcerUserEvent;
}
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Hp Alt Mode System Event Process
// Input Value  : enumTypeCPcbPort
//                stHpSysEvent --> Hp System Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCHpAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpSysEvent stHpSysEvent)
{
    UserInterfaceUsbTypeCHpAltModeHandler(enumTypeCPcbPort, stHpSysEvent);
}

//--------------------------------------------------
// Description  : TypeC Hp Alt Mode Get User Event
// Input Value  : enumTypeCPcbPort
//                stHpUserEvent --> Hp User Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent *pstHpUserEvent)
{
    StructTypeCHpUserEvent stHpUserEvent = {_TYPE_C_HP_USER_EVENT_NONE, {0x00}, 0x00};

    UserInterfaceUsbTypeCGetHpUserEvent(enumTypeCPcbPort, &stHpUserEvent);

    *pstHpUserEvent = stHpUserEvent;
}
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Get Dell Alt Mode Initial Complete Status
// Input Value  : enumTypeCPcbPort
// Output Value : Dell Alt Mode Initial Complete (_TYPE_C_DELL_INIT_COMPLETE / _TYPE_C_DELL_INIT_NOT_COMPLETE)
//--------------------------------------------------
EnumTypeCDellInitCompleteStatus UserCommonUsbTypeCGetDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbTypeCGetDellAltModeInitComplete(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : TypeC Dell Alt Mode System Event Process
// Input Value  : enumTypeCPcbPort
//                stDellSysEvent --> Dell System Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCDellAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellSysEvent stDellSysEvent)
{
    UserInterfaceUsbTypeCDellAltModeHandler(enumTypeCPcbPort, stDellSysEvent);
}

//--------------------------------------------------
// Description  : TypeC Dell Alt Mode Get User Event
// Input Value  : enumTypeCPcbPort
//                stDellUserEvent --> Dell User Event
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent *pstDellUserEvent)
{
    StructTypeCDellUserEvent stDellUserEvent = {_TYPE_C_DELL_USER_EVENT_NONE, {0x00}, 0x00};

    UserInterfaceUsbTypeCGetDellUserEvent(enumTypeCPcbPort, &stDellUserEvent);

    *pstDellUserEvent = stDellUserEvent;
}
#endif
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Total Available Power
// Input Value  : None
// Output Value : return Available Port Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserCommonUsbTypeCGetAvailablePower(EnumTypeCPcbPort *penumTypeCAltPowerPort)
{
    WORD usAvailablePower = 0;
    WORD usAlternatePower = 0;

    // Get Adaptor Power
    usAvailablePower = GET_USB_TYPE_C_ADAPTOR_POWER();
    *penumTypeCAltPowerPort = _ADAPTOR_TYPE_C_PORT;

    // If Adaptor Unattached
    if(usAvailablePower == 0)
    {
        BYTE ucIndex = 0;

        // Search for alternate power source
        for(ucIndex = 0; ucIndex < (_TYPE_C_PORT_VALID - 1); ++ucIndex)
        {
            if(SysUsbTypeCGetPowerRole(g_penumUsbTypeCPcbPort[ucIndex]) == _TYPE_C_POWER_SNK)
            {
                // Port Device can be a power supply
                usAlternatePower = UserCommonUsbTypeCGetPortPower(g_penumUsbTypeCPcbPort[ucIndex]);

                // Use the higher power source
                if(usAlternatePower > usAvailablePower)
                {
                    usAvailablePower = usAlternatePower;

                    *penumTypeCAltPowerPort = g_penumUsbTypeCPcbPort[ucIndex];
                }
            }
        }
    }

    return usAvailablePower;
}

//--------------------------------------------------
// Description  : Get TypeC PDO Reference
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : _TYPE_C_PDO_FROM_KERNEL / _TYPE_C_PDO_FROM_USER
//--------------------------------------------------
EnumTypeCPdoReference UserCommonUsbTypeCPdoReference(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    return UserInterfaceUsbTypeCPdoReference(enumTypeCPcbPort, enumPowerRole);
}

//--------------------------------------------------
// Description  : Get TypeC RDO Reference
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : _TYPE_C_RDO_FROM_KERNEL / _TYPE_C_RDO_FROM_USER
//--------------------------------------------------
EnumTypeCRdoReference UserCommonUsbTypeCRdoReference(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbTypeCRdoReference(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Get TypeC Source Max Power Defined By User
// Input Value  : enumTypeCPcbPort --> D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserCommonUsbTypeCGetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort)
{
    WORD usAvailablePower = 0x00;
    WORD usMaxPower = UserInterfaceUsbTypeCGetMaxPower(enumTypeCPcbPort);

    // Allocate Available Power
    usAvailablePower = UserInterfaceUsbTypeCGetAvailablePower(enumTypeCPcbPort, usMaxPower);

    return usAvailablePower;
}

//--------------------------------------------------
// Description  : Get TypeC Sink Information Defined By User
// Input Value  : enumTypeCPcbPort --> D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                *pstTypeCSnkInfo --> Sink Information
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo *pstTypeCSnkInfo)
{
    UserInterfaceUsbTypeCGetSnkInfo(enumTypeCPcbPort, pstTypeCSnkInfo);
}

//--------------------------------------------------
// Description  : Get TypeC Number of PDOs Defined By User
// Input Value  : enumTypeCPcbPort --> D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
//              : *pucSPRPdoCount --> SPR PDO Count
//              : *pucEPRPdoCount --> EPR PDO Count
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetPdoCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCount, BYTE *pucEPRPdoCount)
{
    *pucSPRPdoCount = UserInterfaceUsbTypeCGetPdoCount(enumTypeCPcbPort, enumPowerRole);

#if(_PORT_CTRL_PD3_1_EPR_SUPPORT == _ON)
    *pucEPRPdoCount = UserInterfaceUsbTypeCGetEPRPdoCount(enumTypeCPcbPort, enumPowerRole);
#else
    *pucEPRPdoCount = 0;
#endif
}

//--------------------------------------------------
// Description  : Port Controller PDO Info
// Input Value  : enumTypeCPcbPort --> D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserPdo --> PDO Info
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetPdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserPdo)
{
    StructTypeCUserPDO stTypeCUserPdo = {_PD_FIX_SUPPLY_PDO , _PD_PEAK_CUR_NONE , 0x00 , 0x00 , 0x00};

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        UserInterfaceUsbTypeCGetSrcPdoInfo(enumTypeCPcbPort, ucPdoIndex, &stTypeCUserPdo);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Get User Sink PDO Info
        UserInterfaceUsbTypeCGetSnkPdoInfo(enumTypeCPcbPort, ucPdoIndex, &stTypeCUserPdo);
    }

    *pstTypeCUserPdo = stTypeCUserPdo;
}

//--------------------------------------------------
// Description  : Port Controller Initial RDO Info
// Input Value  : enumTypeCPcbPort --> D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                *pstTypeCUserInitRdo --> Initial Request Info
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetInitRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO *pstTypeCUserInitRdo)
{
    UserInterfaceUsbTypeCGetInitRdoInfo(enumTypeCPcbPort, pstTypeCUserInitRdo);
}

//--------------------------------------------------
// Description  : Port Controller RDO Info
// Input Value  : enumTypeCPcbPort --> D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : *stTypeCUserRdo --> RDO Info
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCGetRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO *pstTypeCUserRdo)
{
    UserInterfaceUsbTypeCGetRdoInfo(enumTypeCPcbPort, pstTypeCUserRdo);
}

//--------------------------------------------------
// Description  : Get TypeC Unconstrained Power Status
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST / _TYPE_C_UNCONSTRAIN_POWER_EXIST
//--------------------------------------------------
EnumTypeCUnconstrainPowerExist UserCommonUsbTypeCGetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbTypeCGetUnconstrainedPow(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : System Power Management Operation Behavior
// Input Value  : None
// Output Value : _TYPE_C_SPM_FIX_DEFAULT_POWER / _TYPE_C_SPM_ADJUST_DYNAMIC_POWER
//--------------------------------------------------
EnumTypeCSpmOperation UserCommonUsbTypeCSpmOperation(void)
{
    return UserInterfaceUsbTypeCSpmOperation();
}

//--------------------------------------------------
// Description  : System Power Management Calculation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCSystemPowerManagement(void)
{
    UserInterfaceUsbTypeCSystemPowerManagement();
}

//--------------------------------------------------
// Description  : Get Adaptor Power
// Input Value  : None
// Output Value : return Current Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserCommonUsbTypeCGetAdaptorPower(void)
{
    return UserInterfaceUsbTypeCGetAdaptorPower();
}


//--------------------------------------------------
// Description  : Get Port Power from Port Partner
// Input Value  : enumTypeCPcbPort
// Output Value : ulTypeCPower (Unit: 100mW)
//--------------------------------------------------
WORD UserCommonUsbTypeCGetPortPower(EnumTypeCPcbPort enumTypeCPcbPort)
{
    WORD usVoltage = 0;
    WORD usCurrent = 0;
    DWORD ulTypeCPower = 0;

    // Get Port Power Information
    SysUsbTypeCGetPdoStatus(enumTypeCPcbPort, &usVoltage, &usCurrent);

    // Calculate power with attached state
    if((usVoltage != 0) && (usCurrent != 0))
    {
        ulTypeCPower = (DWORD)(usVoltage) * (DWORD)(usCurrent);
        ulTypeCPower = ulTypeCPower / 1000;
    }

    return (WORD)ulTypeCPower;
}

//--------------------------------------------------
// Description  : Get Hub Controller Power Usage
// Input Value  : None
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserCommonUsbTypeCGetHubPower(void)
{
    return UserInterfaceUsbTypeCGetHubPower();
}

//--------------------------------------------------
// Description  : Get Billboard Support Port
// Input Value  : EnumHubDsp --> _HUB_DSP0 ~ _HUB_DSP3
// Output Value : _USB_BB_ENABLE / _USB_BB_DISABLE
//--------------------------------------------------
EnumBillboardCtrl UserCommonUsbTypeCGetBillboardSupport(EnumHubDsp enumHubDsp)
{
    return UserInterfaceUsbTypeCGetBillboardSupport(enumHubDsp);
}

//--------------------------------------------------
// Description  : Get Minimum Port Power
// Input Value  : enumTypeCPcbPort
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserCommonUsbTypeCGetPortMinPower(EnumTypeCPcbPort enumTypeCPcbPort)
{
    WORD usMinPower = 0;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_D0_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_D0_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_D0_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_D1_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_D1_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_D1_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_D2_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_D2_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_D2_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_P0_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_P0_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_P0_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_P1_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_P1_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_P1_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_P2_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_P2_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_P2_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_P3_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_P3_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_P3_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_P4_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_P4_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_P4_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_ADAPTOR_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
            // Sink Device Need No Power
            usMinPower = 0;
#else
#if(_ADAPTOR_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            // 5V, 900mA
            usMinPower = 45;
#elif(_ADAPTOR_TYPE_C_EMB_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
            // 5V, 1.5A
            usMinPower = 75;
#else
            // 5V, 3A
            usMinPower = 150;
#endif
#endif
#else
            // 5V, 3A
            usMinPower = 150;
#endif
            break;

        default:

            usMinPower = 0;

            break;
    }

    return usMinPower;
}

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User inform Kernel Eanble BB While BB_Program
// Input Value  : enumTypeCPcbPort
// Output Value : _USB_BB_PROGRAM_DISABLE / _USB_BB_PROGRAM_ENABLE
//--------------------------------------------------
EnumBillboardProgramCtrl UserCommonUsbTypeCBBProgramEnable(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB_BB_HID_TYPE_SUPPORT == _OFF)
    return UserInterfaceUsbTypeCBBProgramEnable(enumTypeCPcbPort);
#else
    enumTypeCPcbPort = enumTypeCPcbPort;

    return _USB_BB_PROGRAM_ENABLE;
#endif
}

//--------------------------------------------------
// Description  : User Get BB Custon Event Change
// Input Value  : NONE
// Output Value : EnumBillboardCustomEvent
//--------------------------------------------------
EnumBillboardCustomEvent UserCommonUsbTypeCBBGetCustomEvent(void)
{
    return SysUsbBillboardGetCustomEvent();
}

//--------------------------------------------------
// Description  : UserC Clear BB Custon Event Change
// Input Value  : NONE
// Output Value : EnumBillboardCustomEvent
//--------------------------------------------------
void UserCommonUsbTypeCBBClrCustomEvent(EnumBillboardCustomEvent enumBillboardCustomEvent)
{
    SysUsbBillboardClrCustomEvent(enumBillboardCustomEvent);
}

//--------------------------------------------------
// Description  : User Get Kernel BB Custom Command While BB_Program
// Input Value  : pststUsbBillboardCustomCommandInfo
// Output Value : NONE
//--------------------------------------------------
void UserCommonUsbTypeCBBCustomCommand(StructUsbBillboardCustomCommandInfo *pststUsbBillboardCustomCommandInfo)
{
    UserInterfaceUsbTypeCBBCustomCommand(pststUsbBillboardCustomCommandInfo);
}
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))))
//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCPmicIICRead(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

    return ScalerTypeCTcpmPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);

#elif(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    switch(ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC0PmicIICRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);
#endif
            break;

        case _EMB_TYPE_C_1:
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC1PmicIICRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);
#endif
            break;

        default:
            ucSlaveAddr = ucSlaveAddr;
            usSubAddr = usSubAddr;
            ucSubAddrLength = ucSubAddrLength;
            usLength = usLength;
            pucReadArray = pucReadArray;

            break;
    }
#endif

    return _FAIL;
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE UserCommonUsbTypeCPmicIICRead_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

    return ScalerTypeCTcpmPmicIICRead_EXINT0(enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);

#elif(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    switch(ScalerTypeCPcbxTypeCxMapping_EXINT0(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC0PmicIICRead_EXINT0(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);
#endif
            break;

        case _EMB_TYPE_C_1:
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC1PmicIICRead_EXINT0(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);
#endif
            break;

        default:
            ucSlaveAddr = ucSlaveAddr;
            usSubAddr = usSubAddr;
            ucSubAddrLength = ucSubAddrLength;
            usLength = usLength;
            pucReadArray = pucReadArray;

            break;
    }
#endif

    return _FAIL;
}

#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE UserCommonUsbTypeCPmicIICRead_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    return ScalerTypeCTcpmPmicIICRead_WDINT(enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray);
}
#endif // End of #if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCPmicIICWrite(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

    return ScalerTypeCTcpmPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);

#elif(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    switch(ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC0PmicIICWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        case _EMB_TYPE_C_1:
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC1PmicIICWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        default:
            ucSlaveAddr = ucSlaveAddr;
            usSubAddr = usSubAddr;
            ucSubAddrLength = ucSubAddrLength;
            usLength = usLength;
            pucWriteArray = pucWriteArray;

            break;
    }
#endif

    return _FAIL;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE UserCommonUsbTypeCPmicIICWrite_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

    return ScalerTypeCTcpmPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);

#elif(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    switch(ScalerTypeCPcbxTypeCxMapping_EXINT0(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC0PmicIICWrite_EXINT0(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        case _EMB_TYPE_C_1:
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC1PmicIICWrite_EXINT0(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        default:
            ucSlaveAddr = ucSlaveAddr;
            usSubAddr = usSubAddr;
            ucSubAddrLength = ucSubAddrLength;
            usLength = usLength;
            pucWriteArray = pucWriteArray;

            break;
    }
#endif

    return _FAIL;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE UserCommonUsbTypeCPmicIICWrite_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

    return ScalerTypeCTcpmPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);

#elif(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    switch(ScalerTypeCPcbxTypeCxMapping_WDINT(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC0PmicIICWrite_WDINT(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        case _EMB_TYPE_C_1:
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC1PmicIICWrite_WDINT(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        default:
            ucSlaveAddr = ucSlaveAddr;
            usSubAddr = usSubAddr;
            ucSubAddrLength = ucSubAddrLength;
            usLength = usLength;
            pucWriteArray = pucWriteArray;

            break;
    }
#endif

    return _FAIL;
}

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : Get TypeC Local Power Status
// Input Value  : None
// Output Value : _TYPE_C_LOCAL_POWER_NOT_EXIST / _TYPE_C_LOCAL_POWER_EXIST
//--------------------------------------------------
EnumTypeCLocalPowerExist UserCommonUsbTypeCGetLocalPow(void)
{
    return UserInterfaceUsbTypeCGetLocalPow();
}
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
//--------------------------------------------------
// Description  : Set PMIC Vbus Force Off Control Type
// Input Value  : enumTypeCPcbPort --> PCB Port
//                enumForceOffType --> PMIC Vbus Control Type
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCPmicSetForceOffControlType(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicForceOffType enumForceOffType)
{
    switch(ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC0PmicSetForceOffControlType(enumForceOffType);
#endif
            break;

        case _EMB_TYPE_C_1:
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC1PmicSetForceOffControlType(enumForceOffType);
#endif
            break;

        default:
            enumTypeCPcbPort = enumTypeCPcbPort;
            enumForceOffType = enumForceOffType;

            break;
    }
}

//--------------------------------------------------
// Description  : Set data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr --> Slave address
//                ucSubAddrLength --> Start address length of selected device
//                usSubAddr --> Start address of selected device
//                usLength --> Numbers of data we want to write
//                pucWriteArray --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCPmicSetForceOffIIC(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    switch(ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC0PmicIICSetFrsData(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        case _EMB_TYPE_C_1:
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
            return ScalerTypeC1PmicIICSetFrsData(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray);
#endif
            break;

        default:
            ucSlaveAddr = ucSlaveAddr;
            usSubAddr = usSubAddr;
            ucSubAddrLength = ucSubAddrLength;
            usLength = usLength;
            pucWriteArray = pucWriteArray;

            break;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Set Gpio Control Data
// Input Value  : enumTypeCPcbPort --> PCB Port
//                enumPinConfig --> Pin Config
//                ucPinControl --> Pin Control (0/1)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCPmicSetForceOffGpio(EnumTypeCPcbPort enumTypeCPcbPort, EnumPinConfigType enumPinConfig, BYTE ucPinControl)
{
    switch(ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort))
    {
        case _EMB_TYPE_C_0:
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC0PmicSetForceOffGpio(enumPinConfig, ucPinControl);
#endif
            break;

        case _EMB_TYPE_C_1:
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC1PmicSetForceOffGpio(enumPinConfig, ucPinControl);
#endif
            break;

        default:
            enumTypeCPcbPort = enumTypeCPcbPort;
            enumPinConfig = enumPinConfig;
            ucPinControl = ucPinControl;

            break;
    }
}
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))))