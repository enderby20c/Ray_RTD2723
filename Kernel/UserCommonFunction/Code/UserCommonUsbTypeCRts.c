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
// ID Code      : UserCommonUsbTypeCRts.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBTYPECRTS__

#include "UserCommonInclude.h"
#include "UsbTypeCRts/UserCommonUsbTypeCRts.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command && Read Command
#if(_TYPE_C_PORT_CTRL_RTS_FW_SPEC_VER >= _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D7)
code StructSMBusWRGetICStatus tUsbTypeCRtsSMBusWrCmdGetICStatus[1] = {{0x3A, 0x03, 0x08, 0x00, 0x01}};
code StructSMBusRDGetICStatus tUsbTypeCRtsSMBusRdCmdGetICStatus[1] = {{0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWRReadDPLanes tUsbTypeCRtsSMBusWrCmdReadDpCapVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0C}};
code StructSMBusWRReadDPLanes tUsbTypeCRtsSMBusWrCmdReadDpCapVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0C}};
code StructSMBusRDReadDPLanesCfg tUsbTypeCRtsSMBusRdCmdDPCapVdo[1] = {{0x80, 0x05, 0x45, 0x04, 0x00, 0x00}};

code StructSMBusWRGetStatus tUsbTypeCRtsSMBusWrGetStatus[1] = {{0x09, 0x03, 0x00, 0x00, 0x0E}};
code StructSMBusRDGetStatus tUsbTypeCRtsSMBusRDGetStatus[1] = {{0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWRReadDPLanes tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0E}};
code StructSMBusWRReadDPLanes tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0E}};
code StructSMBusRDReadDPLanesCfg tUsbTypeCRtsSMBusRdCmdReadDPCfgVdo[1] = {{0x80, 0x05, 0x06, 0x04, 0x00, 0x00}};

code StructSMBusWRGetICStatus tUsbTypeCRtsSMBusWrCmdGetTypeCFwVer[1] = {{0x3A, 0x03, 0x03, 0x00, 0x03}};
code StructSMBusRDGetICStatus tUsbTypeCRtsSMBusRdCmdGetTypeCFwVer[1] = {{0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#else
code StructSMBusWRGetICStatus tUsbTypeCRtsSMBusWrCmdGetICStatus[1] = {{0x3A, 0x01, 0x14}};
code StructSMBusRDGetICStatus tUsbTypeCRtsSMBusRdCmdGetICStatus[1] = {{0x80, 0x15, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRSetDPLanes tUsbTypeCRtsSMBusWrCmdSetDPCapVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0C, 0x45, 0x00, 0x08, 0x00}};

code StructSMBusWRSetDPLanes tUsbTypeCRtsSMBusWrCmdSetDPCfgVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0E, 0x05, 0x04, 0x00, 0x00}};

code StructSMBusWRSetDPMultiFunction tUsbTypeCRtsSMBusWrCmdSetDPMultiFunction[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0D, 0x18, 0x00, 0x00, 0x00}};
code StructSMBusWRReadDPMultiFunction tUsbTypeCRtsSMBusWrCmdReadDPMultiFunction[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0D}};
code StructSMBusRDReadDPMultiFunction tUsbTypeCRtsSMBusRdCmdDPMultiFunction[1] = {{0x80, 0x05, 0x08, 0x00, 0x00, 0x00}};

code StructSMBusWRNotifyEn tUsbTypeCRtsSMBusWrCmdSetNotifyEn[1] = {{0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRReconnect tUsbTypeCRtsSMBusWrCmdSetReconnect[1] = {{0x08, 0x03, 0x1F, 0x00, 0x01}};
code StructSMBusWRDisconnect tUsbTypeCRtsSMBusWrCmdSetDisconnect[1] = {{0x08, 0x02, 0x23, 0x00}};
code StructSMBusWROperation tUsbTypeCRtsSMBusWrCmdSetOperationMode[1] = {{0x08, 0x03, 0x1D, 0x00, 0x00}};

code StructSMBusRDCommandReadyStatus tUsbTypeCRtsSMBusRdCmdCommandReadyStatus[1] = {{0x00, 0x00}};

code StructSMBusRDReadDPLanes tUsbTypeCRtsSMBusRdCmdDPlanes[1] = {{0x80, 0x05, 0x45, 0x00, 0x08, 0x00}};

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
code StructSMBusWRSetPDO tUsbTypeCRtsSMBusWrCmdSetSrcPDO[1] = {{0x08, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSetPDO tUsbTypeCRtsSMBusWrCmdSetSnkPDO[1] = {{0x08, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSetRDO tUsbTypeCRtsSMBusWrCmdSetRDO[1] = {{0x08, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00}};
#if(_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON)
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetSelfEPRSrcPdo[1] = {{0x08, 0x03, 0xAA, 0x00, 0x81}};
code StructSMBusRDGetPdo tUsbTypeCRtsSMBusRdCmdGetEPRPdo[1] = {{0x80, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetPartnerEPRSrcPdo[1] = {{0x08, 0x03, 0xAA, 0x00, 0x83}};
#endif
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[1] = {{0x08, 0x03, 0x83, 0x00, 0xE1}};
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo1st[1] = {{0x08, 0x03, 0x83, 0x00, 0xA1}};
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo2nd[1] = {{0x08, 0x03, 0x83, 0x00, 0x55}};
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[1] = {{0x08, 0x03, 0x83, 0x00, 0xE3}};
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo1st[1] = {{0x08, 0x03, 0x83, 0x00, 0xA3}};
code StructSMBusWRGetPdo tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo2nd[1] = {{0x08, 0x03, 0x83, 0x00, 0x57}};
code StructSMBusRDGetPdo tUsbTypeCRtsSMBusRdCmdGetPdo[1] = {{0x80, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusRDGetPdo tUsbTypeCRtsSMBusRdCmdGetPdo1st[1] = {{0x80, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusRDGetPdo tUsbTypeCRtsSMBusRdCmdGetPdo2nd[1] = {{0x80, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
code StructSMBusWRGetLenovoInfo tUsbTypeCRtsSMBusWrCmdGetLenovoInfo[1] = {{0x08, 0x02, 0xE0, 0x00}};
code StructSMBusRDGetLenovoInfo tUsbTypeCRtsSMBusRdCmdGetLenovoInfo[1] = {{0x80, 0x03, 0x00, 0x00}};

code StructSMBusWRGetLenovoVdm tUsbTypeCRtsSMBusWrCmdGetLenovoVdm[1] = {{0x08, 0x02, 0x99, 0x00}};
code StructSMBusRDGetLenovoVdm tUsbTypeCRtsSMBusRdCmdGetLenovoVdm[1] = {{0x80, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSendLenovoVdmAck tUsbTypeCRtsSMBusWrCmdSendLenovoVdmAck[1] = {{0x08, 0x0E, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSendLenovoVdmReq tUsbTypeCRtsSMBusWrCmdSendLenovoVdmReq[1] = {{0x08, 0x06, 0x19, 0x00, 0x00, 0x00, 0xEF, 0x17}};
#endif

code StructSMBusWRAckCCCI tUsbTypeCRtsSMBusWrCmdAckCCCI[1] = {{0x0A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTypeCRtsInfo g_pstUsbTypeCRtsInfo[_TYPE_C_PORT_VALID];

#if((_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsD0DetectInfo;
#endif
#if((_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsD1DetectInfo;
#endif
#if((_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsD2DetectInfo;
#endif
#if((_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsP0DetectInfo;
#endif
#if((_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsP1DetectInfo;
#endif
#if((_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsP2DetectInfo;
#endif
#if((_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsP3DetectInfo;
#endif
#if((_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsP4DetectInfo;
#endif
#if((_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS) || (_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
StructPortCtrlDetectInfo g_stUsbTypeCRtsAdaptorDetectInfo;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get RTS Port Ctrl I2C Communication Enabled Flag
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonUsbTypeCRtsGetI2CEnabledFlag(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bFlag = _FALSE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_D0_TYPE_C_PORT);

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_D1_TYPE_C_PORT);

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_D2_TYPE_C_PORT);

            break;
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P0_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_P0_TYPE_C_PORT);

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P1_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_P1_TYPE_C_PORT);

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P2_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_P2_TYPE_C_PORT);

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P3_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_P3_TYPE_C_PORT);

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P4_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_P4_TYPE_C_PORT);

            break;
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _ADAPTOR_TYPE_C_PORT:

            bFlag = GET_TYPE_C_RTS_I2C_ENABLED_FLG(_ADAPTOR_TYPE_C_PORT);

            break;
#endif

        default:
            break;
    }

    return bFlag;
}

//--------------------------------------------------
// Description  : Set RTS Port Ctrl I2C Communication Enabled Flag
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetI2CEnabledFlag(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_D0_TYPE_C_PORT);

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_D1_TYPE_C_PORT);

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_D2_TYPE_C_PORT);

            break;
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P0_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_P0_TYPE_C_PORT);

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P1_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_P1_TYPE_C_PORT);

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P2_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_P2_TYPE_C_PORT);

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P3_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_P3_TYPE_C_PORT);

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P4_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_P4_TYPE_C_PORT);

            break;
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _ADAPTOR_TYPE_C_PORT:

            SET_TYPE_C_RTS_I2C_ENABLED_FLG(_ADAPTOR_TYPE_C_PORT);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clr RTS Port Ctrl I2C Communication Enabled Flag
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsClrI2CEnabledFlag(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_D0_TYPE_C_PORT);

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_D1_TYPE_C_PORT);

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_D2_TYPE_C_PORT);

            break;
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P0_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_P0_TYPE_C_PORT);

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P1_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_P1_TYPE_C_PORT);

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P2_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_P2_TYPE_C_PORT);

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P3_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_P3_TYPE_C_PORT);

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P4_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_P4_TYPE_C_PORT);

            break;
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _ADAPTOR_TYPE_C_PORT:

            CLR_TYPE_C_RTS_I2C_ENABLED_FLG(_ADAPTOR_TYPE_C_PORT);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable RTS Port Ctrl I2C Vendor Command Communication
// Input Value  : enumTypeCPcbPort
// Output Value : Operation Result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsInitializeI2CCommunication(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);
    BYTE code tVendCmdTbl[5] = {0x01, 0x03, 0xDA, 0x0B, 0x01};
#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
    StructTypeCRtsNotifyEn stTypeCNotifyEn = {_TYPE_C_RTS_NOTIFY_EN_B0_NONE, _TYPE_C_RTS_NOTIFY_EN_B1_NONE, _TYPE_C_RTS_NOTIFY_EN_B2_NONE, _TYPE_C_RTS_NOTIFY_EN_B3_NONE};
#endif

    // Execute Write Command
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tVendCmdTbl[0], 1, tVendCmdTbl[1] + 1, &tVendCmdTbl[1], enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("8. Enable RTS Port Ctrl Vender Command Write Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("8. Enable RTS Port Ctrl Vender Command Polling Fail", 0);

        return _FAIL;
    }

#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
    // Get Rts Notification Enable From User
    UserCommonUsbTypeCRtsGetUserNotifyEn(enumTypeCPcbPort, &stTypeCNotifyEn);

    // Update Notification Enable to Rts Port Controller
    if(UserCommonUsbTypeCRtsSetNotifyEn(enumTypeCPcbPort, stTypeCNotifyEn) == _FAIL)
    {
        return _FAIL;
    }
#endif

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    // Get Source PDO Info from RTS Port Ctrl
    UserCommonUsbTypeCRtsUpdateSrcPdo(enumTypeCPcbPort);
#endif

    return _SUCCESS;
}

#if(_PORT_CTRL_RTS_DET_CC_ATTACH_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Set CC Attach I2C Detection Flag
// Input Value  : enumTypeCPcbPort, bAction : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsI2CDetCCAttachCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bAction)
{
    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D0_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D1_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D2_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P0_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P0_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_P0_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P1_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P1_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_P1_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P2_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P2_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_P2_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P3_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P3_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_P3_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P4_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P4_DP_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_P4_DP_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _ADAPTOR_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_ADAPTOR_DETECT_CC_ATTACH();
            }
            else
            {
                CLR_USB_TYPE_C_ADAPTOR_DETECT_CC_ATTACH();
            }

            break;
#endif  // End of #if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Rts Port Ctrl CC Attached Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_UNATTACH / _TYPE_C_ATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonUsbTypeCRtsGetCcAttachByI2C(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAttachStatus enumCcAttachStatus = _TYPE_C_UNATTACH;
    BYTE ucReadInfo = 0x00;
    bit bGetPortCtrlInfoReq = _FALSE;

    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D0_TYPE_C_PORT:

            if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
            {
                // 1. Return _TRUE if D0 Port is Currently Lit Up From DP Source
                enumCcAttachStatus = _TYPE_C_ATTACH;
            }
            else if(GET_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH() == _FALSE)
            {
                // 2. If I2C Debounce(500ms) is FALSE, return Status in Source Handler
                if(SysUsbTypeCGetCcAttach(_D0_TYPE_C_PORT) == _TRUE)
                {
                    enumCcAttachStatus = _TYPE_C_ATTACH;
                }
                else
                {
                    enumCcAttachStatus = _TYPE_C_UNATTACH;
                }
            }
            else
            {
                // 3-1. CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read RTS Port Ctrl Info Via I2C
                CLR_USB_TYPE_C_D0_DP_DETECT_CC_ATTACH();
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CONNECTION_DET);

                // 3-2. Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D1_TYPE_C_PORT:

            if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
            {
                // 1. Return _TRUE if D1 Port is Currently Lit Up From DP Source
                enumCcAttachStatus = _TYPE_C_ATTACH;
            }
            else if(GET_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH() == _FALSE)
            {
                // 2. If I2C Debounce(500ms) is FALSE, return Status in Source Handler
                if(SysUsbTypeCGetCcAttach(_D1_TYPE_C_PORT) == _TRUE)
                {
                    enumCcAttachStatus = _TYPE_C_ATTACH;
                }
                else
                {
                    enumCcAttachStatus = _TYPE_C_UNATTACH;
                }
            }
            else
            {
                // 3-1. CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read RTS Port Ctrl Info Via I2C
                CLR_USB_TYPE_C_D1_DP_DETECT_CC_ATTACH();
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CONNECTION_DET);

                // 3-2. Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D2_TYPE_C_PORT:

            if((SysSourceGetInputPort() == _D2_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
            {
                // 1. Return _TRUE if D2 Port is Currently Lit Up From DP Source
                enumCcAttachStatus = _TYPE_C_ATTACH;
            }
            else if(GET_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH() == _FALSE)
            {
                // 2. If I2C Debounce(500ms) is FALSE, return Status in Source Handler
                if(SysUsbTypeCGetCcAttach(_D2_TYPE_C_PORT) == _TRUE)
                {
                    enumCcAttachStatus = _TYPE_C_ATTACH;
                }
                else
                {
                    enumCcAttachStatus = _TYPE_C_UNATTACH;
                }
            }
            else
            {
                // 3-1. CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read RTS Port Ctrl Info Via I2C
                CLR_USB_TYPE_C_D2_DP_DETECT_CC_ATTACH();
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D2_TYPE_C_CONNECTION_DET);

                // 3-2. Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            // (bGetPortCtrlReq = _FALSE) & (enumCcAttachStatus = _TYPE_C_UNATTACH) => Return _TYPE_C_UNATTACH

            break;
    }

    // "Request = TRUE" Only When "DP Not Display & DETECT Flag = TRUE"
    if(bGetPortCtrlInfoReq == _TRUE)
    {
        // Read Rts Info Via IIC Command
        if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_CC_ATTACH, &ucReadInfo) == _SUCCESS)
        {
            if(ucReadInfo == _TYPE_C_ATTACH)
            {
                enumCcAttachStatus = _TYPE_C_ATTACH;
            }
            else
            {
                enumCcAttachStatus = _TYPE_C_UNATTACH;
            }
        }
        else
        {
            DebugMessageTypeC("8. Read Rts CC Attach By IIC Fail", 0);

            enumCcAttachStatus = _TYPE_C_UNATTACH;
        }
    }

    return enumCcAttachStatus;
}
#endif  // End of #if(_PORT_CTRL_RTS_DET_CC_ATTACH_BY_SMBUS == _ON)

#if(_PORT_CTRL_RTS_DET_ALT_MODE_READY_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Set Alt Mode Ready I2C Detection Flag
// Input Value  : enumTypeCPcbPort, bAction : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsI2CDetAltModeReadyCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bAction)
{
    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D0_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_D0_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_D0_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D1_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_D1_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_D1_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D2_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_D2_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_D2_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P0_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P0_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_P0_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P1_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P1_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_P1_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P2_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P2_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_P2_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P3_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P3_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_P3_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _P4_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_P4_DP_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_P4_DP_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _ADAPTOR_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_USB_TYPE_C_ADAPTOR_DETECT_ALT_MODE();
            }
            else
            {
                CLR_USB_TYPE_C_ADAPTOR_DETECT_ALT_MODE();
            }

            break;
#endif  // End of #if((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Rts Port Ctrl Alt Mode Ready Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonUsbTypeCRtsGetAltModeReadyByI2C(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAltModeStatus enumAltModeStatus = _TYPE_C_ALT_MODE_NOT_READY;
    BYTE ucReadInfo = 0x00;
    bit bGetPortCtrlInfoReq = _FALSE;

    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D0_TYPE_C_PORT:

            if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
            {
                // 1. Return _TRUE if D0 Port is Currently Lit Up From DP Source
                enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
            }
            else if(GET_USB_TYPE_C_D0_DP_DETECT_ALT_MODE() == _FALSE)
            {
                // 2. If I2C Debounce(500ms) is FALSE, return Status in Source Handler
                if(SysUsbTypeCGetAltModeReady(_D0_TYPE_C_PORT) == _TRUE)
                {
                    enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
                }
                else
                {
                    enumAltModeStatus = _TYPE_C_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                // 3-1. CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read Rts Info Via I2C
                CLR_USB_TYPE_C_D0_DP_DETECT_ALT_MODE();
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CONNECTION_DET);

                // 3-2. Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D1_TYPE_C_PORT:

            if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
            {
                // 1. Return _TRUE if D1 Port is Currently Lit Up From DP Source
                enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
            }
            else if(GET_USB_TYPE_C_D1_DP_DETECT_ALT_MODE() == _FALSE)
            {
                // 2. If I2C Debounce(500ms) is FALSE, return Status in Source Handler
                if(SysUsbTypeCGetAltModeReady(_D1_TYPE_C_PORT) == _TRUE)
                {
                    enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
                }
                else
                {
                    enumAltModeStatus = _TYPE_C_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                // 3-1. CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read Rts Info Via I2C
                CLR_USB_TYPE_C_D1_DP_DETECT_ALT_MODE();
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CONNECTION_DET);

                // 3-2. Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))
        case _D2_TYPE_C_PORT:

            if((SysSourceGetInputPort() == _D2_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
            {
                // 1. Return _TRUE if D2 Port is Currently Lit Up From DP Source
                enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
            }
            else if(GET_USB_TYPE_C_D2_DP_DETECT_ALT_MODE() == _FALSE)
            {
                // 2. If I2C Debounce(500ms) is FALSE, return Status in Source Handler
                if(SysUsbTypeCGetAltModeReady(_D2_TYPE_C_PORT) == _TRUE)
                {
                    enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
                }
                else
                {
                    enumAltModeStatus = _TYPE_C_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                // 3-1. CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read Rts Info Via I2C
                CLR_USB_TYPE_C_D2_DP_DETECT_ALT_MODE();
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D2_TYPE_C_CONNECTION_DET);

                // 3-2. Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS))

        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            // (bGetPortCtrlReq = _FALSE) & (enumCcAttachStatus = _TYPE_C_UNATTACH) => Return _TYPE_C_UNATTACH

            break;
    }

    // "Request = TRUE" Only When "DP Not Display & DETECT Flag = TRUE"
    if(bGetPortCtrlInfoReq == _TRUE)
    {
        // Read RTS Port Ctrl Info Via IIC Command
        if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
        {
            if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
            {
                enumAltModeStatus = _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                enumAltModeStatus = _TYPE_C_ALT_MODE_NOT_READY;
            }
        }
        else
        {
            DebugMessageTypeC("8. Read Rts Alt Mode Ready By IIC Fail", enumTypeCPcbPort);

            enumAltModeStatus = _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    return enumAltModeStatus;
}
#endif  // End of #if(_PORT_CTRL_RTS_DET_ALT_MODE_READY_BY_SMBUS == _ON)

//--------------------------------------------------
// Description  : RTS Port Ctrl Info Reset
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    SET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_DATA_ROLE_NONE);
    SET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_ROLE_NONE);
    SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);
    SET_TYPE_C_RTS_PORT_PARTNER_FLAG(enumTypeCPcbPort, 0x00);
    SET_TYPE_C_RTS_DETECT_STATUS(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_I2C_WR_EXTEND_INFO(enumTypeCPcbPort);

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    CLR_TYPE_C_RTS_PORT_OPERATION_MODE(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_EXPLICIT_CONTRACT(enumTypeCPcbPort);
    SET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort, 0);
    SET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort, 0);
    SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, 0);
    SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, 0);
#endif

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    // Reset Lenovo Alt Mode Info
    SET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(enumTypeCPcbPort);
    SET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(enumTypeCPcbPort);
    CLR_TYPE_C_RTS_LENOVO_VDM_RECEIVED(enumTypeCPcbPort);
    SET_TYPE_C_RTS_LENOVO_DOCK_EVENT(enumTypeCPcbPort, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Set RTS Port Ctrl Status I2C Detection Flag
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetStatusDetection(EnumTypeCPcbPort enumTypeCPcbPort)
{
    SET_TYPE_C_RTS_DETECT_STATUS(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Update RTS Port Ctrl Status (Including Power Role, Data Role and PDO Info)
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsUpdateStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bGetPortCtrlInfoReq = _FALSE;

    if((SysUsbTypeCGetCcAttach(enumTypeCPcbPort) == _FALSE) || (UserInterfaceUsbTypeCTurnOnRtsStatusUpdate(enumTypeCPcbPort) == _FALSE))
    {
        return;
    }

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            // Update Rts Status Every _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME (500ms/ 1000ms/ 1500ms/ 2000ms)
            if(GET_TYPE_C_RTS_DETECT_STATUS(_D0_TYPE_C_PORT) == _TRUE)
            {
                // Clr Detect Status Flag, Wait At Least _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME (500ms/ 1000ms/ 1500ms/ 2000ms) to Read 5400 PD Info Via IIC
                CLR_TYPE_C_RTS_DETECT_STATUS(_D0_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_D0_TYPE_C_STATUS_DETECT);

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            // Update Rts Status Every _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME (500ms/ 1000ms/ 1500ms/ 2000ms)
            if(GET_TYPE_C_RTS_DETECT_STATUS(_D1_TYPE_C_PORT) == _TRUE)
            {
                // Clr Detect Status Flag, Wait At Least _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME (500ms/ 1000ms/ 1500ms/ 2000ms) to Read 5400 PD Info Via IIC
                CLR_TYPE_C_RTS_DETECT_STATUS(_D1_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_D1_TYPE_C_STATUS_DETECT);

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            // Update Rts Status Every _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME (500ms/ 1000ms/ 1500ms/ 2000ms)
            if(GET_TYPE_C_RTS_DETECT_STATUS(_D2_TYPE_C_PORT) == _TRUE)
            {
                // Clr Detect Status Flag, Wait At Least _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME (500ms/ 1000ms/ 1500ms/ 2000ms) to Read 5400 PD Info Via IIC
                CLR_TYPE_C_RTS_DETECT_STATUS(_D2_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_D2_TYPE_C_STATUS_DETECT);

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            // bGetPortCtrlReq = _FALSE
            break;
    }

    // "Request = TRUE" Only When "DETECT Flag = TRUE"
    if(bGetPortCtrlInfoReq == _TRUE)
    {
        // 1. Update RTS Data Role / Power Role / Port Partner Flag / Currently Negotiated Request Info and Set to Macro
        if(UserCommonUsbTypeCRtsUpdateRoleInfo(enumTypeCPcbPort) == _FAIL)
        {
            return;
        }

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
        // 2. Update SRC PDO and Set to Macro
        if(GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort) == _TYPE_C_POWER_SRC)
        {
            // Update RTS SRC PDO and Set to Macro
            if(UserCommonUsbTypeCRtsUpdateSrcPdo(enumTypeCPcbPort) == _FAIL)
            {
                return;
            }
        }
        else if(GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort) == _TYPE_C_POWER_SNK)
        {
            // Update Partner SRC PDO and Set to Macro
            if(UserCommonUsbTypeCRtsUpdatePartnerSrcPdo(enumTypeCPcbPort) == _FAIL)
            {
                return;
            }
        }

        // 3. Get Negotiated Voltage & Current and Set to Macro
        UserCommonUsbTypeCRtsUpdatePdoStatus(enumTypeCPcbPort);
#endif
    }
}

//--------------------------------------------------
// Description  : Update RTS Port Ctrl Data Role and Power Role
// Input Value  : enumTypeCPcbPort
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsUpdateRoleInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructSMBusWRGetStatus stGetStatus;
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    memcpy(&stGetStatus, &tUsbTypeCRtsSMBusWrGetStatus[0], tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength + 2);

    stGetStatus.ucOffset = 0x04;
    stGetStatus.ucStatusLen = 0x07;

    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stGetStatus.ucCommandCode, 1, stGetStatus.ucDataLength + 1, &stGetStatus.ucDataLength, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode, 1, stGetStatus.ucStatusLen + 1, &(g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte3), enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    g_unUsbSMBusRdDataPool.stRdGetStatus.ucCommandCode = tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode;

    // 1.1 Get RTS Role Info & Port Partner Flag and Set to Macro
    // Role Info & Port Partner Flag Field Only Valid when Connect Status Field is Set to One
    if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT7)) == _BIT7)
    {
        if(((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT2) || ((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT1))
        {
            SET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_DFP_U);
        }
        else
        {
            SET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_UFP_U);
        }

        if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT6)) == _BIT6)
        {
            SET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_SRC);
        }
        else
        {
            SET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_SNK);
        }

        SET_TYPE_C_RTS_PORT_PARTNER_FLAG(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte5_PortPartnerFlag);
    }
    else
    {
        SET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_DATA_ROLE_NONE);
        SET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_ROLE_NONE);
        SET_TYPE_C_RTS_PORT_PARTNER_FLAG(enumTypeCPcbPort, 0x00);
    }

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    // Byte4[7] Connect Status (Attached:1 / Unattached:0), Byte4[3:1] Port Operation Mode (PD:3)
    if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT7)) == _BIT7)
    {
        // 1.2 Get RTS Port Operation Mode and Set to Macro
        SET_TYPE_C_RTS_PORT_OPERATION_MODE(enumTypeCPcbPort, ((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT3 | _BIT2 | _BIT1)) >> 1));

        // 1.3 Get Currently Negotiated Request Info and Set to Macro
        // RDO Field is Only Valid when Connect Status Field is Set to One and Port Operation Mode Field is Set to PD
        if(GET_TYPE_C_RTS_PORT_OPERATION_MODE(enumTypeCPcbPort) == (_BIT1 | _BIT0))
        {
            SET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort, ((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte9 & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));

            // Request Data Object[7:0]
            SET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte6);

            // Request Data Object[15:8]
            SET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte7);

            // Request Data Object[23:16]
            SET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte8);

            // If (Port Operation Mode == PD), it means there is an Explicit Contract
            // Set RTS Explicit Contract Macro
            SET_TYPE_C_RTS_EXPLICIT_CONTRACT(enumTypeCPcbPort);
        }
        else
        {
            // If (Port Operation Mode != PD), it means there is No Explicit Contract
            // Clear RTS Explicit Contract Macro
            CLR_TYPE_C_RTS_EXPLICIT_CONTRACT(enumTypeCPcbPort);
        }
    }
    else
    {
        CLR_TYPE_C_RTS_PORT_OPERATION_MODE(enumTypeCPcbPort);
        CLR_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort);
        CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort);
        CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort);
        CLR_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort);
        SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, 0);
        SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, 0);

        // If (Connect Status == Unattached), it means there is No Explicit Contract
        // Clear RTS Explicit Contract Macro
        CLR_TYPE_C_RTS_EXPLICIT_CONTRACT(enumTypeCPcbPort);
    }
#endif

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Data Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCDataRole (_TYPE_C_DATA_ROLE_NONE / _TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole UserCommonUsbTypeCRtsGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Power Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC / _TYPE_C_POWER_ROLE_NONE)
//--------------------------------------------------
EnumTypeCPowerRole UserCommonUsbTypeCRtsGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Port Partner Flag (Current Operating Mode)
// Input Value  : enumTypeCPcbPort
// Output Value : Port Partner Flag (BIT0 : USB / BIT1 : Alt Mode)
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtsGetPortPartnerFlag(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // BIT0 : Port Controller is Operating in USB Mode
    // BIT1 : Port Controller is operating in Alt Mode
    return GET_TYPE_C_RTS_PORT_PARTNER_FLAG(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl I2C Pin Number
// Input Value  : enumTypeCPcbPort
// Output Value : I2C Pin Number
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtsGetI2CPinNum(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucI2CPinNum = _NO_IIC_PIN;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            ucI2CPinNum = _D0_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            ucI2CPinNum = _D1_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            ucI2CPinNum = _D2_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P0_TYPE_C_PORT:

            ucI2CPinNum = _P0_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P1_TYPE_C_PORT:

            ucI2CPinNum = _P1_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P2_TYPE_C_PORT:

            ucI2CPinNum = _P2_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P3_TYPE_C_PORT:

            ucI2CPinNum = _P3_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _P4_TYPE_C_PORT:

            ucI2CPinNum = _P4_USB_RTS_SMBUS_IIC;

            break;
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _ADAPTOR_TYPE_C_PORT:

            ucI2CPinNum = _ADAPTOR_TYPE_C_RTS_SMBUS_IIC;

            break;
#endif

        default:

            break;
    }

    return ucI2CPinNum;
}

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Update RTS Port Ctrl Src PDOs
// Input Value  : enumTypeCPcbPort
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsUpdateSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);
    BYTE ucIndex = 0;
    BYTE ucGetDataIndex = 0;
    // Under 3081, the performance of zero initializer is better than using meset
    BYTE pucGetData[2 + (_RTS_MAX_DATA_OBJ_CNT * 4)] = {0}; // Arrary Size = ucCommandCode + ucDataLength + Max Data Objects * 4 Bytes

    if(UserCommonUsbTypeCRtsGetI2CPinNum(enumTypeCPcbPort) == _SW_IIC_PIN_GPIO)
    {
        if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
        if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetPdo[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Set Number Of RTS SRC PDO
        SET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);
        SET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort, 0);

        memcpy(pucGetData, &g_unUsbSMBusRdDataPool.stRdGetPdo, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength + 2);
    }
    else
    {
        // Use HW IIC, Need to use multiple GET_PDO commands to Read all PDOs from RTS Port Ctrl
        // Use Get_PDO Command in the first time to Get PDO 1~5
        if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
        if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetPdo1st[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetPdo1st[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Set Number Of RTS SRC PDO
        // (ucDataLength / 4) is the Number of Actual PDOs in 5450, instead of the Number Required by GET_PDO Command
        SET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);
        SET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort, 0);

        memcpy(pucGetData, &g_unUsbSMBusRdDataPool.stRdGetPdo, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength + 2);

        if(GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort) > 5)
        {
            // Use Get_PDO Command in the second time to Get PDO 6~7
            if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo2nd[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo2nd[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetSelfSrcPdo2nd[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
            {
                return _FAIL;
            }

            if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
            {
                return _FAIL;
            }

            // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
            if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetPdo2nd[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetPdo2nd[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
            {
                return _FAIL;
            }

            // Put PDO 6~7 into pucGetData array
            memcpy(&pucGetData[2 + (5 * 4)], &g_unUsbSMBusRdDataPool.stRdGetPdo.ucByte0, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength);
        }
    }

#if(_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON)
    // Use Get_EPR_PDO Command to Get EPR PDO
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetSelfEPRSrcPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetSelfEPRSrcPdo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetSelfEPRSrcPdo[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
    if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetEPRPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetEPRPdo[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    // Put EPR PDO into pucGetData array
    memcpy(&pucGetData[2 + (GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort) * 4)], &g_unUsbSMBusRdDataPool.stRdGetPdo.ucByte0, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength);

    SET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);
#endif

    // Set RTS General Info
    SET_TYPE_C_RTS_DRP(enumTypeCPcbPort, pucGetData[5] >> 5);
    SET_TYPE_C_RTS_SUSPEND(enumTypeCPcbPort, pucGetData[5] >> 4);
    SET_TYPE_C_RTS_EXT_PWR(enumTypeCPcbPort, pucGetData[5] >> 3);
    SET_TYPE_C_RTS_USB_CAP(enumTypeCPcbPort, pucGetData[5] >> 2);
    SET_TYPE_C_RTS_DRD(enumTypeCPcbPort, pucGetData[5] >> 1);
    SET_TYPE_C_RTS_UNCHK(enumTypeCPcbPort, pucGetData[5] >> 0);

    DebugMessageTypeC("GET_TYPE_C_RTS_DRP()", GET_TYPE_C_RTS_DRP(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_SUSPEND()", GET_TYPE_C_RTS_SUSPEND(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_EXT_PWR()", GET_TYPE_C_RTS_EXT_PWR(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_USB_CAP()", GET_TYPE_C_RTS_USB_CAP(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_DRD()", GET_TYPE_C_RTS_DRD(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_UNCHK()", GET_TYPE_C_RTS_UNCHK(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_SPR_SRC_CAP_CNT()", GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_EPR_SRC_CAP_CNT()", GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort));

    for(ucIndex = 0; ucIndex < _RTS_MAX_DATA_OBJ_CNT; ucIndex++)
    {
        if(((ucIndex >= GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort)) && (ucIndex < 7)) || ((ucIndex >= (GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort) + 7)) && (ucIndex < 11)))
        {
            // If the SPR Source_Cap contains fewer than 7 PDOs, the unused Related Macros Shall be zero filled
            // If the EPR Source_Cap contains fewer than 4 PDOs, the unused Related Macros Shall be zero filled
            SET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, 0x00);

            DebugMessageTypeC("ucIndex", ucIndex);
            DebugMessageTypeC("SPR Source_Cap is fewer than 7 PDOs, the unused Related Macros Shall be zero filled", 0x00);
            DebugMessageTypeC("EPR Source_Cap is fewer than 4 PDOs, the unused Related Macros Shall be zero filled", 0x00);
            DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_TYPE(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_CUR(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex));

            continue;
        }

        if(ucIndex < GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort))
        {
            ucGetDataIndex = ucIndex;
        }
        else
        {
            ucGetDataIndex = ucIndex - (7 - GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort));
        }

        if((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Set APDO Type
            SET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
        }
        else
        {
            // Set PDO Type
            SET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT7 | _BIT6)) >> 6));
        }

        if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_FIX_SUPPLY_PDO)
        {
            // Set Peak Current
            SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 4] & (_BIT5 | _BIT4)) >> 4));

            // Set PDO Voltage (Unit 50mV to 100mV) and Current (Unit 10mA)
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, (((((WORD)(pucGetData[ucGetDataIndex * 4 + 4] & 0x0F)) << 6) | (((WORD)(pucGetData[ucGetDataIndex * 4 + 3] & 0xFC)) >> 2)) / 2));
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex));
            SET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, ((((WORD)(pucGetData[ucGetDataIndex * 4 + 3] & 0x03)) << 8) | ((WORD)pucGetData[ucGetDataIndex * 4 + 2])));
        }
        else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
        {
            SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, 0x00);

            // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, (((pucGetData[ucGetDataIndex * 4 + 5] & 0x01) << 7) | ((pucGetData[ucGetDataIndex * 4 + 4] & 0xFE) >> 1)));
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, pucGetData[ucGetDataIndex * 4 + 3]);
            SET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, pucGetData[ucGetDataIndex * 4 + 2] & 0x7F);
        }
        else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_3_1_ADJUSTABLE_PDO)
        {
            // Set Peak Current
            SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT3 | _BIT2)) >> 2));

            // Set PDO Voltage (Unit 100mV)
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, ((((WORD)(pucGetData[ucGetDataIndex * 4 + 5] & 0x03)) << 7) | (((WORD)(pucGetData[ucGetDataIndex * 4 + 4] & 0xFE)) >> 1)));
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, pucGetData[ucGetDataIndex * 4 + 3]);
            SET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, 0x00);

            // Set PDP (Unit 1W to 0.1W)
            SET_TYPE_C_RTS_MAX_POWER(enumTypeCPcbPort, pucGetData[ucGetDataIndex * 4 + 2] * 10);
        }

        DebugMessageTypeC("ucIndex", ucIndex);
        DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_TYPE(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_SRC_CAP_CUR(ucRealIndex)", GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_MAX_POWER()", GET_TYPE_C_RTS_MAX_POWER(enumTypeCPcbPort));
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Update RTS Port Ctrl Partner Src PDOs
// Input Value  : enumTypeCPcbPort
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsUpdatePartnerSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);
    BYTE ucIndex = 0;
    BYTE ucGetDataIndex = 0;
    // Under 3081, the performance of zero initializer is better than using meset
    BYTE pucGetData[2 + (_RTS_MAX_DATA_OBJ_CNT * 4)] = {0}; // Arrary Size = ucCommandCode + ucDataLength + Max Data Objects * 4 Bytes

    if(UserCommonUsbTypeCRtsGetI2CPinNum(enumTypeCPcbPort) == _SW_IIC_PIN_GPIO)
    {
        if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
        if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetPdo[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Set Number Of RTS SRC PDO
        SET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);
        SET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort, 0);

        memcpy(pucGetData, &g_unUsbSMBusRdDataPool.stRdGetPdo, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength + 2);
    }
    else
    {
        // Use HW IIC, Need to use multiple GET_PDO commands to Read all PDOs from RTS Port Ctrl
        // Use Get_PDO Command in the first time to Get PDO 1~5
        if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
        if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetPdo1st[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetPdo1st[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _FAIL;
        }

        // Set Number Of RTS SRC PDO
        // (ucDataLength / 4) is the Number of Actual PDOs in 5450, instead of the Number Required by GET_PDO Command
        SET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);
        SET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort, 0);

        memcpy(pucGetData, &g_unUsbSMBusRdDataPool.stRdGetPdo, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength + 2);

        if(GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort) > 5)
        {
            // Use Get_PDO Command in the second time to Get PDO 6~7
            if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo2nd[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo2nd[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetPartnerSrcPdo2nd[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
            {
                return _FAIL;
            }

            if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
            {
                return _FAIL;
            }

            // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
            if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetPdo2nd[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetPdo2nd[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
            {
                return _FAIL;
            }

            // Put PDO 6~7 into pucGetData array
            memcpy(&pucGetData[2 + (5 * 4)], &g_unUsbSMBusRdDataPool.stRdGetPdo.ucByte0, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength);
        }
    }

#if(_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON)
    // Use Get_EPR_PDO Command to Get EPR PDO
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetPartnerEPRSrcPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetPartnerEPRSrcPdo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetPartnerEPRSrcPdo[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    // Data Read from 5450 is placed in g_unUsbSMBusRdDataPool
    if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetEPRPdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetEPRPdo[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength), enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    // Put EPR PDO into pucGetData array
    memcpy(&pucGetData[2 + (GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort) * 4)], &g_unUsbSMBusRdDataPool.stRdGetPdo.ucByte0, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength);

    SET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort, g_unUsbSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);
#endif

    DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT()", GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort));
    DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT()", GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort));

    for(ucIndex = 0; ucIndex < _RTS_MAX_DATA_OBJ_CNT; ucIndex++)
    {
        if(((ucIndex >= GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort)) && (ucIndex < 7)) || ((ucIndex >= (GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort) + 7)) && (ucIndex < 11)))
        {
            // If the SPR Source_Cap contains fewer than 7 PDOs, the unused Related Macros Shall be zero filled
            // If the EPR Source_Cap contains fewer than 4 PDOs, the unused Related Macros Shall be zero filled
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, 0x00);
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, 0x00);

            DebugMessageTypeC("ucIndex", ucIndex);
            DebugMessageTypeC("SPR Source_Cap is fewer than 7 PDOs, the unused Related Macros Shall be zero filled", 0x00);
            DebugMessageTypeC("EPR Source_Cap is fewer than 4 PDOs, the unused Related Macros Shall be zero filled", 0x00);
            DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex));
            DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex));

            continue;
        }

        if(ucIndex < GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort))
        {
            ucGetDataIndex = ucIndex;
        }
        else
        {
            ucGetDataIndex = ucIndex - (7 - GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort));
        }

        if((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Set APDO Type
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
        }
        else
        {
            // Set PDO Type
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT7 | _BIT6)) >> 6));
        }

        if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_FIX_SUPPLY_PDO)
        {
            // Set Peak Current
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 4] & (_BIT5 | _BIT4)) >> 4));

            // Set PDO Voltage (Unit 50mV to 100mV) and Current (Unit 10mA)
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, (((((WORD)(pucGetData[ucGetDataIndex * 4 + 4] & 0x0F)) << 6) | (((WORD)(pucGetData[ucGetDataIndex * 4 + 3] & 0xFC)) >> 2)) / 2));
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex));
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, ((((WORD)(pucGetData[ucGetDataIndex * 4 + 3] & 0x03)) << 8) | ((WORD)pucGetData[ucGetDataIndex * 4 + 2])));
        }
        else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
        {
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, 0x00);

            // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, (((pucGetData[ucGetDataIndex * 4 + 5] & 0x01) << 7) | ((pucGetData[ucGetDataIndex * 4 + 4] & 0xFE) >> 1)));
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, pucGetData[ucGetDataIndex * 4 + 3]);
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, pucGetData[ucGetDataIndex * 4 + 2] & 0x7F);
        }
        else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_3_1_ADJUSTABLE_PDO)
        {
            // Set Peak Current
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex, ((pucGetData[ucGetDataIndex * 4 + 5] & (_BIT3 | _BIT2)) >> 2));

            // Set PDO Voltage (Unit 100mV)
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex, ((((WORD)(pucGetData[ucGetDataIndex * 4 + 5] & 0x03)) << 7) | (((WORD)(pucGetData[ucGetDataIndex * 4 + 4] & 0xFE)) >> 1)));
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex, pucGetData[ucGetDataIndex * 4 + 3]);
            SET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex, 0x00);
        }

        DebugMessageTypeC("ucIndex", ucIndex);
        DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucIndex));
        DebugMessageTypeC("GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(ucRealIndex)", GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucIndex));
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Update RTS Port Ctrl PDO Status
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsUpdatePdoStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucTotalPdoCount = 0;

    if(GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort) == _TYPE_C_POWER_SRC)
    {
        if(GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
        {
            ucTotalPdoCount = 7 + GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }
        else
        {
            ucTotalPdoCount = GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }

        // Check if Object Position is Valid
        if((GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) > 0) && (GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) <= ucTotalPdoCount))
        {
            if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // Convert Voltage From 100mV to 10mV
                SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) * 10);

                // Current in 10mA
                SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, ((((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort) & 0x03)) << 8) | ((WORD)GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort))));
            }
            else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Convert Voltage From 20mV to 10mV
                SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, (((((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort) & 0x1F)) << 7) | (((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort) & 0xFE)) >> 1)) * 2));

                // Convert Current From 50mA to 10mA
                SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, ((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort) & 0x7F) * 5));
            }
            else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                // Convert Voltage From 25mV to 10mV
                SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, (((((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort) & 0x1F)) << 7) | (((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort) & 0xFE)) >> 1)) * 5 / 2));

                // Convert Current From 50mA to 10mA
                SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, ((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort) & 0x7F) * 5));
            }
        }
    }
    else if(GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort) == _TYPE_C_POWER_SNK)
    {
        if(GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
        {
            ucTotalPdoCount = 7 + GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }
        else
        {
            ucTotalPdoCount = GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }

        // Check if Object Position is Valid
        if((GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) > 0) && (GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) <= ucTotalPdoCount))
        {
            if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // Convert Voltage From 100mV to 10mV
                SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) * 10);

                // Current in 10mA
                SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, ((((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort) & 0x03)) << 8) | ((WORD)GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort))));
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Convert Voltage From 20mV to 10mV
                SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, (((((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort) & 0x1F)) << 7) | (((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort) & 0xFE)) >> 1)) * 2));

                // Convert Current From 50mA to 10mA
                SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, ((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort) & 0x7F) * 5));
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                // Convert Voltage From 25mV to 10mV
                SET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort, (((((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_2(enumTypeCPcbPort) & 0x1F)) << 7) | (((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_1(enumTypeCPcbPort) & 0xFE)) >> 1)) * 5 / 2));

                // Convert Current From 50mA to 10mA
                SET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort, ((WORD)(GET_TYPE_C_RTS_NEGOTIATED_REQ_INFO_0(enumTypeCPcbPort) & 0x7F) * 5));
            }
        }
    }
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Explicit Contract
// Input Value  : enumTypeCPcbPort
// Output Value : Explicit Contract Result (_TRUE / _FALSE)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsGetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTS_EXPLICIT_CONTRACT(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Max Power
// Input Value  : enumTypeCPcbPort
// Output Value : Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserCommonUsbTypeCRtsGetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTS_MAX_POWER(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Number of Src/Snk PDOs
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
void UserCommonUsbTypeCRtsGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        *pucSPRPdoCnt = GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        *pucEPRPdoCnt = GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        *pucSPRPdoCnt = GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort);
        *pucEPRPdoCnt = GET_TYPE_C_RTS_EPR_SNK_CAP_CNT(enumTypeCPcbPort);
    }
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCRtsGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    BYTE ucTotalPdoCount = 0;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        if(GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
        {
            ucTotalPdoCount = 7 + GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }
        else
        {
            ucTotalPdoCount = GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }

        if((ucPdoIndex >= 1) && (ucPdoIndex <= ucTotalPdoCount))
        {
            stTypeCPdo.enumPdoType = GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1);

            if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPdo.enumPeakCurrent = GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucPdoIndex - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCPdo.usMaxCurrent = GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucPdoIndex - 1);
            }
            else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPdo.usMaxCurrent = (GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucPdoIndex - 1) * 5);
            }
            else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                stTypeCPdo.enumPeakCurrent = GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucPdoIndex - 1);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCPdo.usMaxVoltage = GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucPdoIndex - 1);
            stTypeCPdo.usMinVoltage = GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucPdoIndex - 1);
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // To-Do Daisy : Update RTS SNK PDO if Needed
    }

    return stTypeCPdo;
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Number of Partner Src/Snk PDOs
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
void UserCommonUsbTypeCRtsGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        *pucSPRPdoCnt = GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        *pucEPRPdoCnt = GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // To-Do Kai : Update Number of Port Partner SNK PDO if Needed
        *pucSPRPdoCnt = 0;
        *pucEPRPdoCnt = 0;
    }
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Partner Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCRtsGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    BYTE ucTotalPdoCount = 0;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        if(GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
        {
            ucTotalPdoCount = 7 + GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }
        else
        {
            ucTotalPdoCount = GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }

        if((ucPdoIndex >= 1) && (ucPdoIndex <= ucTotalPdoCount))
        {
            stTypeCPartnerPdo.enumPdoType = GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1);

            if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPartnerPdo.enumPeakCurrent = GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucPdoIndex - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCPartnerPdo.usMaxCurrent = GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucPdoIndex - 1);
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPartnerPdo.usMaxCurrent = (GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, ucPdoIndex - 1) * 5);
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, ucPdoIndex - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                stTypeCPartnerPdo.enumPeakCurrent = GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucPdoIndex - 1);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCPartnerPdo.usMaxVoltage = GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucPdoIndex - 1);
            stTypeCPartnerPdo.usMinVoltage = GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucPdoIndex - 1);
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // To-Do Kai : Update Port Partner SNK PDO if Needed
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl PDO Status
// Input Value  : enumTypeCPcbPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent)
{
    // Voltage in 10mV
    *pusVoltage = GET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort);

    // Current in 10mA
    *pusCurrent = GET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Current Source PDO that Sink Request
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCRtsGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    BYTE ucTotalPdoCount = 0;

    if(GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort) == _TYPE_C_POWER_SRC)
    {
        if(GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
        {
            ucTotalPdoCount = 7 + GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }
        else
        {
            ucTotalPdoCount = GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }

        if((GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) > 0) && (GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) <= ucTotalPdoCount))
        {
            stTypeCSrcPdo.enumPdoType = GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);

            if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCSrcPdo.enumPeakCurrent = GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCSrcPdo.usMaxCurrent = GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
            }
            else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCSrcPdo.usMaxCurrent = (GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) * 5);
            }
            else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                stTypeCSrcPdo.enumPeakCurrent = GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCSrcPdo.usMaxVoltage = GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
            stTypeCSrcPdo.usMinVoltage = GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
        }
    }
    else if(GET_TYPE_C_RTS_POWER_ROLE(enumTypeCPcbPort) == _TYPE_C_POWER_SNK)
    {
        if(GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
        {
            ucTotalPdoCount = 7 + GET_TYPE_C_RTS_PARTNER_EPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }
        else
        {
            ucTotalPdoCount = GET_TYPE_C_RTS_PARTNER_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
        }

        if((GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) > 0) && (GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) <= ucTotalPdoCount))
        {
            stTypeCSrcPdo.enumPdoType = GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);

            if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCSrcPdo.enumPeakCurrent = GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCSrcPdo.usMaxCurrent = GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCSrcPdo.usMaxCurrent = (GET_TYPE_C_RTS_PARTNER_SRC_CAP_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) * 5);
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                stTypeCSrcPdo.enumPeakCurrent = GET_TYPE_C_RTS_PARTNER_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCSrcPdo.usMaxVoltage = GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MAX(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
            stTypeCSrcPdo.usMinVoltage = GET_TYPE_C_RTS_PARTNER_SRC_CAP_VOL_MIN(enumTypeCPcbPort, GET_TYPE_C_RTS_NEGOTIATED_REQ_OBJ_POS(enumTypeCPcbPort) - 1);
        }
    }

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Return RTS Port Ctrl Port Operation Mode
// Input Value  : enumTypeCPcbPort
// Output Value : Port Operation Mode Result
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtsGetPortOperationMode(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTS_PORT_OPERATION_MODE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Set User-Defined Max Power to Rts Port Ctrl
// Input Value  : enumTypeCPcbPort, usMaxPower (Unit = 0.1W)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower)
{
    // Set Max Power
    SET_TYPE_C_RTS_MAX_POWER(enumTypeCPcbPort, usMaxPower);
}

//--------------------------------------------------
// Description  : Set User-Defined Number of PDOs to Rts Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), Number of PDO Counts
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Set Number Of SPR and EPR Source Capabilities (Number Of Data Objects)
        SET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort, ucSPRPdoCnt);
        SET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort, ucEPRPdoCnt);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Number Of SPR and EPR Sink Capabilities (Number Of Data Objects)
        SET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort, ucSPRPdoCnt);
        SET_TYPE_C_RTS_EPR_SNK_CAP_CNT(enumTypeCPcbPort, ucEPRPdoCnt);
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Fix Supply/ PPS PDOs to Rts Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, stTypeCUserPdo
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Set PDO Type
        SET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.enumPdoType);

        if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, (ucPdoIndex - 1)) == _PD_3_PROGRAMMABLE_PDO)
        {
            // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxVoltage);
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMinVoltage);
            SET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, (ucPdoIndex - 1), (stTypeCUserPdo.usMaxCurrent / 5));
        }
        else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, (ucPdoIndex - 1)) == _PD_3_1_ADJUSTABLE_PDO)
        {
            // Set PDO Voltage (Unit 100mV) and Peak Current
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxVoltage);
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMinVoltage);
            SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.enumPeakCurrent);
        }
        else
        {
            SET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.enumPeakCurrent);

            // Set PDO Voltage (Unit 100mV) and Current (Unit 10mA)
            SET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxVoltage);
            SET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, (ucPdoIndex - 1), GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1)));
            SET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxCurrent);
        }

        if(GET_USB_TYPE_C_TOTAL_SRC_PDO_CNT(enumTypeCPcbPort) == ucPdoIndex)
        {
            if(UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_SET_RTS_INFO_SRC_PDO) == _FAIL)
            {
                DebugMessageTypeC("8. Set RTS Port Ctrl Src PDO Fail", 0);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set PDO Type
        SET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.enumPdoType);

        if(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, (ucPdoIndex - 1)) == _PD_3_PROGRAMMABLE_PDO)
        {
            // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
            SET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxVoltage);
            SET_TYPE_C_RTS_SNK_CAP_VOL_MIN(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMinVoltage);
            SET_TYPE_C_RTS_SNK_CAP_CUR(enumTypeCPcbPort, (ucPdoIndex - 1), (stTypeCUserPdo.usMaxCurrent / 5));
        }
        else if(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, (ucPdoIndex - 1)) == _PD_3_1_ADJUSTABLE_PDO)
        {
            // Set PDO Voltage (Unit 100mV)
            SET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxVoltage);
            SET_TYPE_C_RTS_SNK_CAP_VOL_MIN(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMinVoltage);
        }
        else
        {
            // Set PDO Voltage (Unit 100mV) and Current (Unit 10mA)
            SET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxVoltage);
            SET_TYPE_C_RTS_SNK_CAP_VOL_MIN(enumTypeCPcbPort, (ucPdoIndex - 1), GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, (ucPdoIndex - 1)));
            SET_TYPE_C_RTS_SNK_CAP_CUR(enumTypeCPcbPort, (ucPdoIndex - 1), stTypeCUserPdo.usMaxCurrent);
        }

        if(GET_USB_TYPE_C_TOTAL_SNK_PDO_CNT(enumTypeCPcbPort) == ucPdoIndex)
        {
            if(UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_SET_RTS_INFO_SNK_PDO) == _FAIL)
            {
                DebugMessageTypeC("8. Set RTS Port Ctrl Snk PDO Fail", 0);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Set User-Defined RDO to Rts Port Ctrl
// Input Value  : enumTypeCPcbPort, stTypeCUserRdo
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo)
{
    SET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort, stTypeCUserRdo.enumObjPos);
    SET_TYPE_C_RTS_TARGET_REQ_CAP_MIS(enumTypeCPcbPort, stTypeCUserRdo.b1CapMismatch);

    // GB = 1b'0
    SET_TYPE_C_RTS_TARGET_REQ_GIVE_BACK(enumTypeCPcbPort, 0);

    if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_FIX_SUPPLY_PDO)
    {
        // RDO[19:10] : Fix RDO (Op. Cur in 10mA)
        SET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort, (stTypeCUserRdo.usReqInfo1) & 0x3FF);

        // RDO[9:0] : Fix RDO (Max. Cur in 10mA)
        SET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort, (stTypeCUserRdo.usReqInfo2) & 0x3FF);
    }
    else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
    {
        // RDO[20:9] : PPS RDO (Vol in 20mV)
        SET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort, (stTypeCUserRdo.usReqInfo1) & 0xFFF);

        // RDO[6:0] : PPS RDO (Op. Cur in 50mA)
        SET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort, (stTypeCUserRdo.usReqInfo2) & 0x7F);
    }
    else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_1_ADJUSTABLE_PDO)
    {
        // RDO[20:9] : AVS RDO (Vol in 25mV)
        SET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort, (stTypeCUserRdo.usReqInfo1) & 0xFFF);

        // RDO[6:0] : AVS RDO (Op. Cur in 50mA)
        SET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort, (stTypeCUserRdo.usReqInfo2) & 0x7F);
    }

    if(UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_SET_RTS_INFO_RDO) == _FAIL)
    {
        DebugMessageTypeC("8. Set RTS Port Ctrl Src PDO Fail", 0);
    }
}
#endif // End of #if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get RTS Port Ctrl Orientation and Return Result
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCOrientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation UserCommonUsbTypeCRtsGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCOrientation enumOrientation = _TYPE_C_ORIENTATION_NONE;
    BYTE ucReadInfo = 0x00;

    // Get Orientation Info
    if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_ORIENTATION, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ORIENTATION_UNFLIP)
        {
            enumOrientation = _TYPE_C_ORIENTATION_UNFLIP;
        }
        else if(ucReadInfo == _TYPE_C_ORIENTATION_FLIP)
        {
            enumOrientation = _TYPE_C_ORIENTATION_FLIP;
        }

        DebugMessageTypeC("8. Get RTS Port Ctrl Orientation = ", enumOrientation);
    }
    else
    {
        enumOrientation = _TYPE_C_ORIENTATION_NONE;

        DebugMessageTypeC("8. Get RTS Port Ctrl Orientation By IIC Fail", 0);
    }

    return enumOrientation;
}
#endif

//--------------------------------------------------
// Description  : Get RTS Port Ctrl Pin Assignment and Return Result
// Input Value  : enumTypeCPcbPort / penumPinAssignment pointer
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCRtsGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    BYTE ucDataRole = 0x00;
    BYTE ucPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    // Get Data Role Info
    if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_DATA_ROLE, &ucDataRole) == _FAIL)
    {
        return _FAIL;
    }

    // Set Data Role
    DebugMessageTypeC("8. Get RTS Port Ctrl Data Role = ", ucDataRole);

    if(ucDataRole == _TYPE_C_DFP_U)
    {
        SET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_DFP_U);
    }
    else
    {
        SET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_UFP_U);
    }

    // Get Pin Assignment
    if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_PIN_ASSIGNMENT, &ucPinAssignment) == _FAIL)
    {
        return _FAIL;
    }

    *penumPinAssignment = (EnumTypeCPinCfgType)ucPinAssignment;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get RTS Port Ctrl Cable Info for DPCD and Return Result
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : StructTypeCCableInfoForDpcd --> Cable Info for DPCD
//--------------------------------------------------
StructTypeCCableInfoForDpcd UserCommonUsbTypeCRtsGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};

    stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent = GET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(enumTypeCPcbPort);
    stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate = GET_TYPE_C_RTS_CBL_MAX_DP_RATE(enumTypeCPcbPort);
    stTypeCCableInfoForDpcd.b1CableUhbr13p5Support = GET_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(enumTypeCPcbPort);

    DebugMessageTypeC("8. [Cable Info] Get RTS Port Ctrl Active Component = ", stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent);
    DebugMessageTypeC("8. [Cable Info] Get RTS Port Ctrl Max DP Rate = ", stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate);
    DebugMessageTypeC("8. [Cable Info] Get RTS Port Ctrl UHBR13.5 = ", stTypeCCableInfoForDpcd.b1CableUhbr13p5Support);

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : Get RTS Port Ctrl FW Version and Return Result
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//                *pstTypeCFwVersion --> TypeC FW Version
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCRtsGetFwVersion(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion)
{
    BYTE pucFwVersion[3] = {0x00, 0x00, 0x00};

    // Get FW Version
    if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_FW_VERSION, pucFwVersion) == _FAIL)
    {
        return _FAIL;
    }

    pstTypeCFwVersion->ucMainVersion = pucFwVersion[0];
    pstTypeCFwVersion->ucSubVersion1 = pucFwVersion[1];
    pstTypeCFwVersion->ucSubVersion2 = pucFwVersion[2];

    return _SUCCESS;
}

#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
//--------------------------------------------------
// Description  : TypeC Get Notification Enable
// Input Value  : enumTypeCPcbPort, pstTypeCNotifyEn
//                pstTypeCNotifyEn --> Notification Enable
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsGetUserNotifyEn(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCRtsNotifyEn *pstTypeCNotifyEn)
{
    StructTypeCRtsNotifyEn stTypeCNotifyEn = {_TYPE_C_RTS_NOTIFY_EN_B0_NONE, _TYPE_C_RTS_NOTIFY_EN_B1_NONE, _TYPE_C_RTS_NOTIFY_EN_B2_NONE, _TYPE_C_RTS_NOTIFY_EN_B3_NONE};

    // Get Notification Enable from User
    UserInterfaceUsbTypeCRtsGetNotifyEn(enumTypeCPcbPort, &stTypeCNotifyEn);

    *pstTypeCNotifyEn = stTypeCNotifyEn;
}

//--------------------------------------------------
// Description  : Set Notification Enable to RTS Port Controller
// Input Value  : enumTypeCPcbPort, stTypeCNotifyEn
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCRtsSetNotifyEn(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCRtsNotifyEn stTypeCNotifyEn)
{
    StructSMBusWRNotifyEn stSMBusNotifyEn;
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    memcpy(&stSMBusNotifyEn, &tUsbTypeCRtsSMBusWrCmdSetNotifyEn[0], tUsbTypeCRtsSMBusWrCmdSetNotifyEn[0].ucDataLength + 2);

    stSMBusNotifyEn.ucNotifyEnByte0 = stTypeCNotifyEn.enumNotifyEnByte0;
    stSMBusNotifyEn.ucNotifyEnByte1 = stTypeCNotifyEn.enumNotifyEnByte1;
    stSMBusNotifyEn.ucNotifyEnByte2 = stTypeCNotifyEn.enumNotifyEnByte2;
    stSMBusNotifyEn.ucNotifyEnByte3 = stTypeCNotifyEn.enumNotifyEnByte3;

    // Execute Write Command
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stSMBusNotifyEn.ucCommandCode, 1, stSMBusNotifyEn.ucDataLength + 1, &stSMBusNotifyEn.ucDataLength, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("RTS Port Ctrl Notification Enable Write fail", 1);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("RTS Port Ctrl Notification Enable Polling Fail ", 1);

        return _FAIL;
    }

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Update CC Function Control to Rts Port Ctrl (Connect / Disconnect)
// Input Value  : enumTypeCPcbPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction)
{
    if(enumCcFunction == _TYPE_C_CC_FUNCTION_DISABLE)
    {
        if(UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_SET_RTS_INFO_CC_DISCONNECT) == _FAIL)
        {
            DebugMessageTypeC("8. Set RTS Port Ctrl CC Disconnect Fail", 0);
        }
    }
    else if(enumCcFunction == _TYPE_C_CC_FUNCTION_ENABLE)
    {
        if(UserCommonUsbTypeCRtsReconnect(enumTypeCPcbPort) == _FAIL)
        {
            DebugMessageTypeC("8. Set RTS Port Ctrl CC Reconnect Fail", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Set Power Mode to Rts Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetTargetPowerMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    // Use Rts Extend Info Macro to Store Power Status
    SET_TYPE_C_RTS_I2C_WR_EXTEND_INFO(enumTypeCPcbPort, (BYTE)(enumPowerRole));

    if(UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_SET_RTS_INFO_POWER_MODE) == _FAIL)
    {
        DebugMessageTypeC("8. Set RTS Port Ctrl Power Mode Fail", 0);
    }
}

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : enumTypeCPcbPort
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsReconnect(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdSetReconnect[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdSetReconnect[0].ucDataLength + 1, &(tUsbTypeCRtsSMBusWrCmdSetReconnect[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("RTS Port Ctrl Reconnect Write fail", 1);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 500, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("RTS Port Ctrl Reconnect Polling Fail ", 1);

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Config Pin Assignment to RTS Port Controller
// Input Value  : enumTypeCPcbPort / ucPinAssignment / ucDataRole
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsConfigPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    StructSMBusWRSetDPLanes stDpLaneConfigPar;
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    if(GET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort) == _TYPE_C_DFP_U)
    {
        memcpy(&stDpLaneConfigPar, &tUsbTypeCRtsSMBusWrCmdSetDPCfgVdoSelf[0], tUsbTypeCRtsSMBusWrCmdSetDPCfgVdoSelf[0].ucDataLength + 2);

        // Set DP Cfg VDO Byte0
        if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
        {
            // [7:6] Reserved, [5:2] HBR3, [1:0] Set Config for Dp Source Device
            stDpLaneConfigPar.ucDPCapVDOByte0 = 0x05;
        }
        else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
        {
            // [7:6] Reserved, [5:2] HBR3, [1:0] Set Config for Dp Sink Device
            stDpLaneConfigPar.ucDPCapVDOByte0 = 0x06;
        }

        // Set DP Cfg VDO Byte1 : [15:8] the Capability of UFP_U Pin Assignment
        stDpLaneConfigPar.ucDPCapVDOByte1 = enumPinAssignment;

        // [To-Do] Kai
        // [31:26] Belong to Dp Alt Mode V2.1, RTS5450 has not Supported yet. The Value is temporarily Filled with 0.
    }
    else
    {
        memcpy(&stDpLaneConfigPar, &tUsbTypeCRtsSMBusWrCmdSetDPCapVdoSelf[0], tUsbTypeCRtsSMBusWrCmdSetDPCapVdoSelf[0].ucDataLength + 2);

        if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
        {
            // Set DP Cfg VDO Byte2 : [23:16] DP Sink Device Pin Assignments Supported
            stDpLaneConfigPar.ucDPCapVDOByte2 = enumPinAssignment;
        }
        else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
        {
            // Set DP Cfg VDO Byte1 : [15:8] DP Source Device Pin Assignments Supported
            stDpLaneConfigPar.ucDPCapVDOByte1 = enumPinAssignment;
        }
    }

    // Execute Write Command
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stDpLaneConfigPar.ucCommandCode, 1, stDpLaneConfigPar.ucDataLength + 1, &stDpLaneConfigPar.ucDataLength, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Config Multi-Function Bit to RTS Port Controller
// Input Value  : enumTypeCPcbPort / Multi-Function Bit
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsConfigMultiFunction(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    StructSMBusWRSetDPMultiFunction stMultiFunction;
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    memcpy(&stMultiFunction, &tUsbTypeCRtsSMBusWrCmdSetDPMultiFunction[0], tUsbTypeCRtsSMBusWrCmdSetDPMultiFunction[0].ucDataLength + 2);

    // Set DP Cfg VDO Byte0
    if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
    {
        // Only UFP Shoud Set Multi Function Preferred Bit
        // BIT[7:5] Reserved, BIT[6] : Exit Mode, BIT[5] USB Config Req, BIT[4] Multi-Function, BIT[3] DP Enable, BIT[2] Power Low, BIT[1:0] Connect Status (b'10 UFP_D Connected)
        if((GET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort) == _TYPE_C_UFP_U) && (enumMultiFunction == _TYPE_C_MULTI_FUNC_PREFER))
        {
            // Set to Multifunction Prefer
            stMultiFunction.ucDPCapVDOByte0 = 0x1A;
        }
        else
        {
            // Set to Multifunction Not Prefer
            stMultiFunction.ucDPCapVDOByte0 = 0x0A;
        }
    }
    else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
    {
        // BIT[1:0] Connect Status (b'10 DFP_D Connected)
        stMultiFunction.ucDPCapVDOByte0 = 0x01;
    }

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
            {
                stMultiFunction.ucDPCapVDOByte0 = stMultiFunction.ucDPCapVDOByte0 | (_BIT7);
            }

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
            {
                stMultiFunction.ucDPCapVDOByte0 = stMultiFunction.ucDPCapVDOByte0 | (_BIT7);
            }

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
            {
                stMultiFunction.ucDPCapVDOByte0 = stMultiFunction.ucDPCapVDOByte0 | (_BIT7);
            }

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            break;
    }

    // Execute Write Command
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stMultiFunction.ucCommandCode, 1, stMultiFunction.ucDataLength + 1, &stMultiFunction.ucDataLength, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Port Controller Slave Address
// Input Value  : enumTypeCPcbPort
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtsGetSlaveAddr(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = 0x00;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            ucSlaveAddr = _D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _D1_TYPE_C_PORT:

            ucSlaveAddr = _D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _D2_TYPE_C_PORT:

            ucSlaveAddr = _D2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P0_TYPE_C_PORT:

            ucSlaveAddr = _P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P1_TYPE_C_PORT:

            ucSlaveAddr = _P1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P2_TYPE_C_PORT:

            ucSlaveAddr = _P2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P3_TYPE_C_PORT:

            ucSlaveAddr = _P3_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P4_TYPE_C_PORT:

            ucSlaveAddr = _P4_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _ADAPTOR_TYPE_C_PORT:

            ucSlaveAddr = _ADAPTOR_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        default:
            break;
    }

    return ucSlaveAddr;
}

//--------------------------------------------------
// Description  : Write Rts Port Ctrl Info by SMBus
// Input Value  : enumTypeCPcbPort, enumUsbTypeCRtsInfoType
// Output Value : Writing result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsSetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    // Save RTS SMBUS Cmd Type For Polling PD Ready
    SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, enumUsbTypeCRtsInfoType);

    // Write Command to Port Ctrl According to Different Required Info Type
    if(UserCommonUsbTypeCRtsWriteCommand(enumTypeCPcbPort, ucSlaveAddr, enumUsbTypeCRtsInfoType) == _FAIL)
    {
        // RTS SMBUS Cmd Type Macro Reset
        SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

        DebugMessageTypeC("8. IIC Write Command to RTS Port Ctrl Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        // RTS SMBUS Cmd Type Macro Reset
        SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

        DebugMessageTypeC("8. IIC Polling RTS Port Ctrl Fail", 0);

        return _FAIL;
    }

    // RTS SMBUS Cmd Type Macro Reset
    SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read Rts Port Ctrl Info by SMBus
// Input Value  : enumTypeCPcbPort
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType, BYTE *pucReadInfo)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    // Save RTS SMBUS Cmd Type For Polling PD Ready
    SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, enumUsbTypeCRtsInfoType);

    // Write Command to Port Ctrl According to Different Required Info Type
    if(UserCommonUsbTypeCRtsWriteCommand(enumTypeCPcbPort, ucSlaveAddr, enumUsbTypeCRtsInfoType) == _FAIL)
    {
        // RTS SMBUS Cmd Type Macro Reset
        SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

        DebugMessageTypeC("8. IIC Write Command to RTS Port Ctrl Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        // RTS SMBUS Cmd Type Macro Reset
        SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

        DebugMessageTypeC("8. IIC Polling RTS Port Ctrl Fail", 0);

        return _FAIL;
    }

    // Read Info From Port Ctrl According to Different Required Info Type
    if(UserCommonUsbTypeCRtsReadCommand(enumTypeCPcbPort, ucSlaveAddr, enumUsbTypeCRtsInfoType) == _FAIL)
    {
        // RTS SMBUS Cmd Type Macro Reset
        SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

        DebugMessageTypeC("8. IIC Read RTS Port Ctrl Info Fail", 0);

        return _FAIL;
    }

    // RTS SMBUS Cmd Type Macro Reset
    SET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_NONE);

    // Decode Required Info According to Required Info
    switch(enumUsbTypeCRtsInfoType)
    {
        case _TYPE_C_GET_RTS_INFO_CC_ATTACH:

            if((g_unUsbSMBusRdDataPool.stRdGetICStatus.ucPDTypeCStatus & _BIT3) == _BIT3)
            {
                *pucReadInfo = _TYPE_C_ATTACH;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UNATTACH;
            }

            break;

        case _TYPE_C_GET_RTS_INFO_ALT_MODE_READY:

            if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & 0x07) == 0x06)
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_NOT_READY;
            }

            break;

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
        case _TYPE_C_GET_RTS_INFO_ORIENTATION:

            if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte11_Orientation & _BIT5) == _BIT5)
            {
                *pucReadInfo = _TYPE_C_ORIENTATION_UNFLIP;
            }
            else
            {
                *pucReadInfo = _TYPE_C_ORIENTATION_FLIP;
            }

            break;
#endif

        case _TYPE_C_GET_RTS_INFO_DATA_ROLE:

            if(((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT2) || ((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT1))
            {
                *pucReadInfo = _TYPE_C_DFP_U;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UFP_U;
            }

            break;

        case _TYPE_C_GET_RTS_INFO_PIN_ASSIGNMENT:

            *pucReadInfo = (BYTE)(UserCommonUsbTypeCRtsDecodePinAssignment(g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgPinConfig));

            // If the DPAM Version is Version 2.1 or higher, Save the Read Information from RTS5450
            if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte3 & (_BIT7 | _BIT6)) == (_BIT6))
            {
                // Data Byte3 [5:4] Cable Active Component
                if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte3 & (_BIT5 | _BIT4)) == 0x00)
                {
                    SET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(enumTypeCPcbPort, _PD_CBL_COMPONENT_PASSIVE);
                }
                else if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte3 & (_BIT5 | _BIT4)) == (_BIT4))
                {
                    SET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(enumTypeCPcbPort, _PD_CBL_COMPONENT_ACTIVE_RETIMER);
                }
                else if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte3 & (_BIT5 | _BIT4)) == (_BIT5))
                {
                    SET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(enumTypeCPcbPort, _PD_CBL_COMPONENT_ACTIVE_REDRIVER);
                }
                else if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte3 & (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    SET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(enumTypeCPcbPort, _PD_CBL_COMPONENT_OPTICAL);
                }

                // Data Byte0 [5:2] Cable UHBR10_20 Capability
                if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte0 & _BIT4) == _BIT4)
                {
                    SET_TYPE_C_RTS_CBL_MAX_DP_RATE(enumTypeCPcbPort, _PD_CBL_MAX_UHBR20);
                }
                else if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte0 & _BIT3) == _BIT3)
                {
                    SET_TYPE_C_RTS_CBL_MAX_DP_RATE(enumTypeCPcbPort, _PD_CBL_MAX_UHBR10);
                }
                else if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte0 & _BIT2) == _BIT2)
                {
                    SET_TYPE_C_RTS_CBL_MAX_DP_RATE(enumTypeCPcbPort, _PD_CBL_MAX_HBR3);
                }
                else
                {
                    SET_TYPE_C_RTS_CBL_MAX_DP_RATE(enumTypeCPcbPort, _PD_CBL_MAX_DP_RATE_UNCONFIRMED);
                }

                // Data Byte3 [2] Cable UHBR13.5 Support
                if((g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgVDOByte3 & _BIT2) == _BIT2)
                {
                    SET_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(enumTypeCPcbPort);
                }
                else
                {
                    CLR_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(enumTypeCPcbPort);
                }
            }
            else
            {
                SET_TYPE_C_RTS_CBL_ACTIVE_COMPONENT(enumTypeCPcbPort, _PD_CBL_COMPONENT_PASSIVE);
                SET_TYPE_C_RTS_CBL_MAX_DP_RATE(enumTypeCPcbPort, _PD_CBL_MAX_DP_RATE_UNCONFIRMED);
                CLR_TYPE_C_RTS_CBL_UHBR13P5_SUPPORT(enumTypeCPcbPort);
            }

            if(*pucReadInfo == _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                return _FAIL;
            }

            break;

        case _TYPE_C_GET_RTS_INFO_FW_VERSION:

            *pucReadInfo = g_unUsbSMBusRdDataPool.stRdGetICStatus.ucFWMainVer;
            *(pucReadInfo + 1) = g_unUsbSMBusRdDataPool.stRdGetICStatus.ucFWSubVer1;
            *(pucReadInfo + 2) = g_unUsbSMBusRdDataPool.stRdGetICStatus.ucFWSubVer2;

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        // Required Info Include Lenovo Alt Mode Status and VDM Received Info
        case _TYPE_C_GET_RTS_INFO_LENOVO_ALT_MODE_STATUS:

            // Lenovo Mode Entered or Not
            if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & _BIT7) == _BIT7)
            {
                *pucReadInfo = _TYPE_C_LENOVO_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            // VDM Received or Not
            if((g_unUsbSMBusRdDataPool.stRdGetStatus.ucByte3 & _BIT1) == _BIT1)
            {
                *(pucReadInfo + 1) = _TRUE;
            }
            else
            {
                *(pucReadInfo + 1) = _FALSE;
            }

            break;

        case _TYPE_C_GET_RTS_INFO_LENOVO_DEVICE_TYPE:

            *pucReadInfo = g_unUsbSMBusRdDataPool.stRdGetLenovoInfo.ucByte0_DeviceType;

            break;

        case _TYPE_C_GET_RTS_INFO_LENOVO_SYSTEM_EVENT:

            // Only Response to SOP Get Status Request
            if(((g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucByte0 & 0x03) == 0x00) && (g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader0 == 0x10) && (g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader2 == 0xEF) && (g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader3 == 0x17))
            {
                *pucReadInfo = g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucByte6;
                *(pucReadInfo + 1) = g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucByte7;
            }
            else
            {
                return _FAIL;
            }

            break;
#endif

        default:

            return _FAIL;

            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write SMBus Command to Rts Port Controller
// Input Value  : enumTypeCPcbPort, ucSlaveAddr, enumUsbTypeCRtsInfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsWriteCommand(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType)
{
    bit bResult = _FAIL;
    StructSMBusWROperation stSetOperationMode;
#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    BYTE ucIndex = 0;
    BYTE ucRealIndex = 0;
    BYTE pucData[5 + (_RTS_MAX_DATA_OBJ_CNT * 4)] = {0}; // Arrary Size = CMD + WR_DATA_LEN + SUB_CMD + PORT_NUM + PDO Num + Max Data Objects * 4 Bytes
#endif

    switch(enumUsbTypeCRtsInfoType)
    {
        case _TYPE_C_GET_RTS_INFO_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetICStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetICStatus[0].ucDataLength + 1, &(tUsbTypeCRtsSMBusWrCmdGetICStatus[0].ucDataLength), enumTypeCPcbPort);

            break;

        case _TYPE_C_GET_RTS_INFO_ALT_MODE_READY:
        case _TYPE_C_GET_RTS_INFO_DATA_ROLE:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrGetStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength), enumTypeCPcbPort);

            break;

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
        case _TYPE_C_GET_RTS_INFO_ORIENTATION:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrGetStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength), enumTypeCPcbPort);

            break;
#endif

        case _TYPE_C_GET_RTS_INFO_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            if(GET_TYPE_C_RTS_DATA_ROLE(enumTypeCPcbPort) == _TYPE_C_DFP_U)
            {
                bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoSelf[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength), enumTypeCPcbPort);
            }
            else
            {
                bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoPartner[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength), enumTypeCPcbPort);
            }

            break;

        case _TYPE_C_GET_RTS_INFO_FW_VERSION:

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetTypeCFwVer[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetTypeCFwVer[0].ucDataLength + 1, &(tUsbTypeCRtsSMBusWrCmdGetTypeCFwVer[0].ucDataLength), enumTypeCPcbPort);

            break;

        case _TYPE_C_SET_RTS_INFO_CC_DISCONNECT:

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdSetDisconnect[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdSetDisconnect[0].ucDataLength + 1, &(tUsbTypeCRtsSMBusWrCmdSetDisconnect[0].ucDataLength), enumTypeCPcbPort);

            break;

        case _TYPE_C_SET_RTS_INFO_POWER_MODE:

            memcpy(&stSetOperationMode, &tUsbTypeCRtsSMBusWrCmdSetOperationMode[0], tUsbTypeCRtsSMBusWrCmdSetOperationMode[0].ucDataLength + 2);

            if(GET_TYPE_C_RTS_I2C_WR_EXTEND_INFO(enumTypeCPcbPort) == (BYTE)(_TYPE_C_POWER_SRC))
            {
                // Operation Mode = DRP with Try.SRC
                stSetOperationMode.ucByte2 = 0x09;
            }
            else if(GET_TYPE_C_RTS_I2C_WR_EXTEND_INFO(enumTypeCPcbPort) == (BYTE)(_TYPE_C_POWER_SNK))
            {
                // Operation Mode = Sink Only
                stSetOperationMode.ucByte2 = 0x00;
            }

            CLR_TYPE_C_RTS_I2C_WR_EXTEND_INFO(enumTypeCPcbPort);

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, stSetOperationMode.ucCommandCode, 1, stSetOperationMode.ucDataLength + 1, &(stSetOperationMode.ucDataLength), enumTypeCPcbPort);

            break;

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
        case _TYPE_C_SET_RTS_INFO_SRC_PDO:

            // Get Src PDO Write Cmd Code Table
            pucData[0] = tUsbTypeCRtsSMBusWrCmdSetSrcPDO[0].ucCommandCode;
            pucData[1] = 3 + (4 * (GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort) + GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort)));
            pucData[2] = tUsbTypeCRtsSMBusWrCmdSetSrcPDO[0].ucByte0;
            pucData[3] = tUsbTypeCRtsSMBusWrCmdSetSrcPDO[0].ucByte1;

            if(GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort) != 0)
            {
                pucData[4] = (_BIT3) | ((BYTE)(GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort) << 4)) | ((BYTE)(GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort)));
            }
            else
            {
                pucData[4] = (_BIT3) | GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort);
            }

#if(_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON)
            if(((enumTypeCPcbPort == _D0_TYPE_C_PORT) && (_D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _D1_TYPE_C_PORT) && (_D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _D2_TYPE_C_PORT) && (_D2_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P0_TYPE_C_PORT) && (_P0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P1_TYPE_C_PORT) && (_P1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P2_TYPE_C_PORT) && (_P2_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P3_TYPE_C_PORT) && (_P3_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P4_TYPE_C_PORT) && (_P4_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT) && (_ADAPTOR_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)))
            {
                // [23]: EPR Mode Capable
                pucData[7] = pucData[7] | (_BIT7);
            }
#endif

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_DRP(enumTypeCPcbPort) << 5);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_SUSPEND(enumTypeCPcbPort) << 4);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_EXT_PWR(enumTypeCPcbPort) << 3);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_USB_CAP(enumTypeCPcbPort) << 2);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_DRD(enumTypeCPcbPort) << 1);
            pucData[8] = pucData[8] | GET_TYPE_C_RTS_UNCHK(enumTypeCPcbPort);

            for(ucIndex = 0; ucIndex < (GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort) + GET_TYPE_C_RTS_EPR_SRC_CAP_CNT(enumTypeCPcbPort)); ucIndex++)
            {
                if(ucIndex < GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort))
                {
                    ucRealIndex = ucIndex;
                }
                else
                {
                    ucRealIndex = (ucIndex - GET_TYPE_C_RTS_SPR_SRC_CAP_CNT(enumTypeCPcbPort)) + 7;
                }

                if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) == _PD_3_PROGRAMMABLE_PDO)
                {
                    // [31:28] PDO Type
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) << 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                    // Get PDO Voltage (Unit 100mV) and Current (Unit 50mA)
                    // [24:17] Max Voltage in 100mV
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) >> 7) & (_BIT0));
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    pucData[(ucIndex * 4) + 6] = GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucRealIndex);

                    // [6:0] Max Current in 50mA
                    pucData[(ucIndex * 4) + 5] = GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucRealIndex);
                }
                else if(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) == _PD_3_1_ADJUSTABLE_PDO)
                {
                    // [31:28] PDO Type
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) << 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                    // [27:26] Peak Current
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucRealIndex) << 2) & (_BIT3 | _BIT2));

                    // [25:17] Max Voltage in 100mV
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) >> 7) & (_BIT1 | _BIT0));
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    pucData[(ucIndex * 4) + 6] = GET_TYPE_C_RTS_SRC_CAP_VOL_MIN(enumTypeCPcbPort, ucRealIndex);

                    // [7:0] PDP in 1W (Unit 0.1W to 1W)
                    pucData[(ucIndex * 4) + 5] = (BYTE)(GET_TYPE_C_RTS_MAX_POWER(enumTypeCPcbPort) / 10);
                }
                else
                {
                    // [31:30] PDO Type
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) << 6) & (_BIT7 | _BIT6));

                    // Get PDO Voltage (Unit 100mV to 50mv) and Current (Unit 10mA)
                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // |  Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_RTS_SRC_CAP_PEAK_CUR(enumTypeCPcbPort, ucRealIndex) << 4) & (_BIT5 | _BIT4));
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((((GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex)) * 2) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    pucData[(ucIndex * 4) + 6] = pucData[(ucIndex * 4) + 6] | ((((GET_TYPE_C_RTS_SRC_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex)) * 2) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
                    pucData[(ucIndex * 4) + 6] = pucData[(ucIndex * 4) + 6] | ((GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucRealIndex) >> 8) & (_BIT1 | _BIT0));
                    pucData[(ucIndex * 4) + 5] = pucData[(ucIndex * 4) + 5] | GET_TYPE_C_RTS_SRC_CAP_CUR(enumTypeCPcbPort, ucRealIndex);
                }
            }

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, pucData[0], 1, pucData[1] + 1, ((BYTE *)&pucData[1]), enumTypeCPcbPort);

            break;

        case _TYPE_C_SET_RTS_INFO_SNK_PDO:

            // Get Src PDO Write Cmd Code Table
            pucData[0] = tUsbTypeCRtsSMBusWrCmdSetSnkPDO[0].ucCommandCode;
            pucData[1] = 3 + (4 * (GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort) + GET_TYPE_C_RTS_EPR_SNK_CAP_CNT(enumTypeCPcbPort)));
            pucData[2] = tUsbTypeCRtsSMBusWrCmdSetSnkPDO[0].ucByte0;
            pucData[3] = tUsbTypeCRtsSMBusWrCmdSetSnkPDO[0].ucByte1;

            if(GET_TYPE_C_RTS_EPR_SNK_CAP_CNT(enumTypeCPcbPort) != 0)
            {
                pucData[4] = (~_BIT3) & (((BYTE)(GET_TYPE_C_RTS_EPR_SNK_CAP_CNT(enumTypeCPcbPort) << 4)) | ((BYTE)(GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort))));
            }
            else
            {
                pucData[4] = (~_BIT3) & GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort);
            }

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| HC | UP | UC | DRD| FR |
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_DRP(enumTypeCPcbPort) << 5);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_EXT_PWR(enumTypeCPcbPort) << 3);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_USB_CAP(enumTypeCPcbPort) << 2);
            pucData[8] = pucData[8] | (GET_TYPE_C_RTS_DRD(enumTypeCPcbPort) << 1);

            for(ucIndex = 0; ucIndex < (GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort) + GET_TYPE_C_RTS_EPR_SNK_CAP_CNT(enumTypeCPcbPort)); ucIndex++)
            {
                if(ucIndex < GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort))
                {
                    ucRealIndex = ucIndex;
                }
                else
                {
                    ucRealIndex = (ucIndex - GET_TYPE_C_RTS_SPR_SNK_CAP_CNT(enumTypeCPcbPort)) + 7;
                }

                if(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
                {
                    // [31:28] PDO Type
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) << 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                    // Get PDO Voltage (Unit 100mV) and Current (Unit 50mA)
                    // [24:17] Max Voltage in 100mV
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) >> 7) & (_BIT0));
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    pucData[(ucIndex * 4) + 6] = GET_TYPE_C_RTS_SNK_CAP_VOL_MIN(enumTypeCPcbPort, ucRealIndex);

                    // [6:0] Max Current in 50mA
                    pucData[(ucIndex * 4) + 5] = GET_TYPE_C_RTS_SNK_CAP_CUR(enumTypeCPcbPort, ucRealIndex);
                }
                else if(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) == _PD_3_1_ADJUSTABLE_PDO)
                {
                    // [31:28] PDO Type
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) << 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                    // [25:17] Max Voltage in 100mV
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) >> 7) & (_BIT1 | _BIT0));
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    pucData[(ucIndex * 4) + 6] = GET_TYPE_C_RTS_SNK_CAP_VOL_MIN(enumTypeCPcbPort, ucRealIndex);

                    // [7:0] PDP in 1W (Unit 0.1W to 1W)
                    pucData[(ucIndex * 4) + 5] = (BYTE)(GET_TYPE_C_RTS_MAX_POWER(enumTypeCPcbPort) / 10);
                }
                else
                {
                    // [31:30] PDO Type
                    pucData[(ucIndex * 4) + 8] = pucData[(ucIndex * 4) + 8] | ((BYTE)(GET_TYPE_C_RTS_SNK_CAP_TYPE(enumTypeCPcbPort, ucRealIndex) << 6) & (_BIT7 | _BIT6));

                    // Get PDO Voltage (Unit 100mV to 50mv) and Current (Unit 10mA)
                    // | 23 | 22 | 21 | 20 | 19 .. 16 | 15 .. 10 | 09 | 08 | 07 .. 00 |
                    // | FR | Reserved(0)  | Voltage(50mV)[9:0]  |   Max.Cur [9:0]    |
                    pucData[(ucIndex * 4) + 7] = pucData[(ucIndex * 4) + 7] | ((((GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex)) * 2) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    pucData[(ucIndex * 4) + 6] = pucData[(ucIndex * 4) + 6] | ((((GET_TYPE_C_RTS_SNK_CAP_VOL_MAX(enumTypeCPcbPort, ucRealIndex)) * 2) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
                    pucData[(ucIndex * 4) + 6] = pucData[(ucIndex * 4) + 6] | ((GET_TYPE_C_RTS_SNK_CAP_CUR(enumTypeCPcbPort, ucRealIndex) >> 8) & (_BIT1 | _BIT0));
                    pucData[(ucIndex * 4) + 5] = pucData[(ucIndex * 4) + 5] | GET_TYPE_C_RTS_SNK_CAP_CUR(enumTypeCPcbPort, ucRealIndex);
                }
            }

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, pucData[0], 1, pucData[1] + 1, ((BYTE *)&pucData[1]), enumTypeCPcbPort);

            break;

        case _TYPE_C_SET_RTS_INFO_RDO:

            // Get RDO Write Cmd Code Table
            pucData[0] = tUsbTypeCRtsSMBusWrCmdSetRDO[0].ucCommandCode;
            pucData[1] = tUsbTypeCRtsSMBusWrCmdSetRDO[0].ucDataLength;
            pucData[2] = tUsbTypeCRtsSMBusWrCmdSetRDO[0].ucByte0;
            pucData[3] = tUsbTypeCRtsSMBusWrCmdSetRDO[0].ucByte1;

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |      Obj. Pos     | GB | CM | UC | Sus|
            // UC = 1b'1, Sus = 1b'1
            pucData[7] = pucData[7] | (GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) << 4);
            pucData[7] = pucData[7] | (GET_TYPE_C_RTS_TARGET_REQ_GIVE_BACK(enumTypeCPcbPort) << 3);
            pucData[7] = pucData[7] | (GET_TYPE_C_RTS_TARGET_REQ_CAP_MIS(enumTypeCPcbPort) << 2);
            pucData[7] = pucData[7] | (_BIT1);
            pucData[7] = pucData[7] | (_BIT0);

            // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
            // | UC | EC | Rsvd(0) |   Op. Cur [9:6]   |
#if(_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON)
            if(((enumTypeCPcbPort == _D0_TYPE_C_PORT) && (_D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _D1_TYPE_C_PORT) && (_D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _D2_TYPE_C_PORT) && (_D2_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P0_TYPE_C_PORT) && (_P0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P1_TYPE_C_PORT) && (_P1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P2_TYPE_C_PORT) && (_P2_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P3_TYPE_C_PORT) && (_P3_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _P4_TYPE_C_PORT) && (_P4_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)) ||
               ((enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT) && (_ADAPTOR_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON)))
            {
                // [22]: EPR Mode Capable
                pucData[6] = pucData[6] | (_BIT6);
            }
#endif

            if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // RDO[19:10] : Fix (Op. Cur in 10mA)
                pucData[6] = pucData[6] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                pucData[5] = pucData[5] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                // RDO[9:0] : Fix (Max. Cur in 10mA)
                pucData[5] = pucData[5] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort) >> 8) & (_BIT1 | _BIT0));
                pucData[4] = pucData[4] | (BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort));
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // RDO[20:9] : PPS RDO (Vol in 20mV)
                pucData[6] = pucData[6] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort) >> 7) & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                pucData[5] = pucData[5] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort) << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS RDO (Op. Cur in 50mA)
                pucData[4] = pucData[4] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
            else if(GET_TYPE_C_RTS_PARTNER_SRC_CAP_TYPE(enumTypeCPcbPort, GET_TYPE_C_RTS_TARGET_REQ_OBJ_POS(enumTypeCPcbPort) - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                // RDO[20:9] : AVS RDO (Vol in 25mV)
                pucData[6] = pucData[6] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort) >> 7) & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                pucData[5] = pucData[5] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_1(enumTypeCPcbPort) << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : AVS RDO (Op. Cur in 50mA)
                pucData[4] = pucData[4] | ((BYTE)(GET_TYPE_C_RTS_TARGET_REQ_INFO_2(enumTypeCPcbPort)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, pucData[0], 1, pucData[1] + 1, ((BYTE *)&pucData[1]), enumTypeCPcbPort);

            break;
#endif
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _TYPE_C_GET_RTS_INFO_LENOVO_ALT_MODE_STATUS:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrGetStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrGetStatus[0].ucDataLength), enumTypeCPcbPort);

            break;

        case _TYPE_C_GET_RTS_INFO_LENOVO_DEVICE_TYPE:

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetLenovoInfo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetLenovoInfo[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetLenovoInfo[0].ucDataLength), enumTypeCPcbPort);

            break;

        case _TYPE_C_GET_RTS_INFO_LENOVO_SYSTEM_EVENT:

            bResult = UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbTypeCRtsSMBusWrCmdGetLenovoVdm[0].ucCommandCode, 1, tUsbTypeCRtsSMBusWrCmdGetLenovoVdm[0].ucDataLength + 1, ((BYTE *)&tUsbTypeCRtsSMBusWrCmdGetLenovoVdm[0].ucDataLength), enumTypeCPcbPort);

            break;
#endif

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Read Info From Rts Port Controller
// Input Value  : enumTypeCPcbPort, ucSlaveAddr, enumUsbTypeCRtsInfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtsReadCommand(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType)
{
    bit bResult = _FAIL;

    switch(enumUsbTypeCRtsInfoType)
    {
        case _TYPE_C_GET_RTS_INFO_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetICStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetICStatus[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetICStatus.ucByte7), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetICStatus.ucCommandCode = tUsbTypeCRtsSMBusRdCmdGetICStatus[0].ucCommandCode;

            break;

        case _TYPE_C_GET_RTS_INFO_ALT_MODE_READY:
        case _TYPE_C_GET_RTS_INFO_DATA_ROLE:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRDGetStatus[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetStatus.ucDataLength), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetStatus.ucCommandCode = tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode;

            break;

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
        case _TYPE_C_GET_RTS_INFO_ORIENTATION:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRDGetStatus[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetStatus.ucDataLength), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetStatus.ucCommandCode = tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode;

            break;
#endif

        case _TYPE_C_GET_RTS_INFO_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdReadDPCfgVdo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdReadDPCfgVdo[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucDataLength), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdDPlanesCfg.ucCommandCode = tUsbTypeCRtsSMBusRdCmdReadDPCfgVdo[0].ucCommandCode;

            break;

        case _TYPE_C_GET_RTS_INFO_FW_VERSION:

            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetTypeCFwVer[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetTypeCFwVer[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetICStatus.ucByte2), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetICStatus.ucCommandCode = tUsbTypeCRtsSMBusRdCmdGetTypeCFwVer[0].ucCommandCode;

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _TYPE_C_GET_RTS_INFO_LENOVO_ALT_MODE_STATUS:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRDGetStatus[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetStatus.ucDataLength), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetStatus.ucCommandCode = tUsbTypeCRtsSMBusRDGetStatus[0].ucCommandCode;

            break;

        case _TYPE_C_GET_RTS_INFO_LENOVO_DEVICE_TYPE:

            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetLenovoInfo[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetLenovoInfo[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetLenovoInfo.ucDataLength), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetLenovoInfo.ucCommandCode = tUsbTypeCRtsSMBusRdCmdGetLenovoInfo[0].ucCommandCode;

            break;

        case _TYPE_C_GET_RTS_INFO_LENOVO_SYSTEM_EVENT:

            bResult = UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbTypeCRtsSMBusRdCmdGetLenovoVdm[0].ucCommandCode, 1, tUsbTypeCRtsSMBusRdCmdGetLenovoVdm[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucDataLength), enumTypeCPcbPort);

            g_unUsbSMBusRdDataPool.stRdGetLenovoVdm.ucCommandCode = tUsbTypeCRtsSMBusRdCmdGetLenovoVdm[0].ucCommandCode;

            break;
#endif

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Decode Pin Assignment According to PD Info
// Input Value  : ucPdInfo --> Data Role BYTE From PD Info
// Output Value : EnumTypeCPinCfgtType : _TYPE_C_PIN_ASSIGNMENT_C / D / E
//--------------------------------------------------
EnumTypeCPinCfgType UserCommonUsbTypeCRtsDecodePinAssignment(BYTE ucPdInfo)
{
    // Is it possible to Merge DFP/UFP Flow together, and maybe use "Switch case"
    if((ucPdInfo & _BIT5) == _BIT5) // Pin Assignment F 2 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_F;
    }
    else if((ucPdInfo & _BIT4) == _BIT4) // Pin Assignment E (google cable case)
    {
        return _TYPE_C_PIN_ASSIGNMENT_E;
    }
    else if((ucPdInfo & _BIT3) == _BIT3) // Pin Assignment D 2 lane only, Spec require sink report capability include C  mode
    {
        return _TYPE_C_PIN_ASSIGNMENT_D;
    }
    else if((ucPdInfo & _BIT2) == _BIT2) // Pin Assignment C 4 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_C;
    }
    else
    {
        DebugMessageTypeC("8. Decode RTS Port Ctrl Pin Assignment Info Error", ucPdInfo);
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
//--------------------------------------------------
// Description  : Set RTS Port Controller Lenovo Alt Mode I2C Detection Flag
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetLenovoAltModeDetection(EnumTypeCPcbPort enumTypeCPcbPort)
{
    SET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Set RTS Port Controller Lenovo Device Type I2C Detection Flag
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(EnumTypeCPcbPort enumTypeCPcbPort)
{
    SET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Get RTS Port Controller Lenovo Alt Mode Ready Info
// Input Value  : enumTypeCPcbPort
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus UserCommonUsbTypeCRtsGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCLenovoAltModeStatus enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
    BYTE pucModeInfo[2] = {0x00, 0x00};
    bit bGetPortCtrlInfoReq = _FALSE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(_D0_TYPE_C_PORT) == _FALSE)
            {
                enumLenovoAltModeStatus = SysUsbTypeCGetLenovoAltModeReady(_D0_TYPE_C_PORT);
            }
            else
            {
                // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
                if(GET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
                {
                    // Clr Type-C Detect CC Lenovo Alt Mode Flag, Wait At Least 50ms to Read Rts Info Via I2C
                    CLR_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(_D0_TYPE_C_PORT);
                    ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_ALT_MODE_DETECT);
                }

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(_D1_TYPE_C_PORT) == _FALSE)
            {
                enumLenovoAltModeStatus = SysUsbTypeCGetLenovoAltModeReady(_D1_TYPE_C_PORT);
            }
            else
            {
                // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
                if(GET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
                {
                    // Clr Type-C Detect CC Lenovo Alt Mode Flag, Wait At Least 50ms to Read Rts Info Via I2C
                    CLR_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(_D1_TYPE_C_PORT);
                    ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_ALT_MODE_DETECT);
                }

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(_D2_TYPE_C_PORT) == _FALSE)
            {
                enumLenovoAltModeStatus = SysUsbTypeCGetLenovoAltModeReady(_D2_TYPE_C_PORT);
            }
            else
            {
                // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
                if(GET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
                {
                    // Clr Type-C Detect CC Lenovo Alt Mode Flag, Wait At Least 50ms to Read Rts Info Via I2C
                    CLR_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(_D2_TYPE_C_PORT);
                    ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D2_TYPE_C_LENOVO_ALT_MODE_DETECT);
                }

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            // (bGetPortCtrlReq = _FALSE) & (enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY) => Return _TYPE_C_LENOVO_ALT_MODE_NOT_READY

            break;
    }

    // "Request = TRUE" Only When "DETECT Flag = TRUE"
    if(bGetPortCtrlInfoReq == _TRUE)
    {
        // Read RTS Port Ctrl Info Via IIC Command
        if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
        {
            if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
            {
                if(pucModeInfo[1] == _TRUE)
                {
                    SET_TYPE_C_RTS_LENOVO_VDM_RECEIVED(enumTypeCPcbPort);
                }
                else
                {
                    CLR_TYPE_C_RTS_LENOVO_VDM_RECEIVED(enumTypeCPcbPort);
                }

                enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_READY;
            }
            else
            {
                CLR_TYPE_C_RTS_LENOVO_VDM_RECEIVED(enumTypeCPcbPort);
                SET_TYPE_C_RTS_LENOVO_DOCK_EVENT(enumTypeCPcbPort, 0x00);

                enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }
        }
        else
        {
            DebugMessageTypeC("8. Read Rts Lenovo Alt Mode Ready By IIC Fail", enumTypeCPcbPort);

            enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
        }
    }

    return enumLenovoAltModeStatus;
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from RTS Port Controller
// Input Value  : enumTypeCPcbPort
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType UserCommonUsbTypeCRtsGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCLenovoDeviceType enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
    BYTE ucDeviceType = 0x00;
    bit bGetPortCtrlInfoReq = _FALSE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D0_TYPE_C_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(_D0_TYPE_C_PORT) == _FALSE)
            {
                enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }
            else
            {
                // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(_D0_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D1_TYPE_C_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(_D1_TYPE_C_PORT) == _FALSE)
            {
                enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }
            else
            {
                // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(_D1_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _D2_TYPE_C_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(_D2_TYPE_C_PORT) == _FALSE)
            {
                enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }
            else
            {
                // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_RTS_DETECT_LENOVO_DEVICE_TYPE(_D2_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D2_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

                // Set Request = TRUE to Get Port Ctrl Info via I2C Communication
                bGetPortCtrlInfoReq = _TRUE;
            }

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            // (bGetPortCtrlReq = _FALSE) & (enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY) => Return _TYPE_C_LENOVO_ALT_MODE_NOT_READY

            break;
    }

    // "Request = TRUE" Only When "DETECT Flag = TRUE"
    if(bGetPortCtrlInfoReq == _TRUE)
    {
        // Read RTS Port Ctrl Info Via IIC Command
        if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
        {
            enumLenovoDeviceType = (EnumTypeCLenovoDeviceType)ucDeviceType;
        }
        else
        {
            DebugMessageTypeC("8. Read Rts Lenovo Device Type By IIC Fail", enumTypeCPcbPort);

            enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
        }
    }

    return enumLenovoDeviceType;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent UserCommonUsbTypeCRtsGetLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};
    StructSMBusWRAckCCCI stAckCCCI;
    StructSMBusWRSendLenovoVdmAck stSendGetStatusAck;
    BYTE pucSystemInfo[2] = {0x00, 0x00};
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    if(GET_TYPE_C_RTS_LENOVO_VDM_RECEIVED(enumTypeCPcbPort) == _TRUE)
    {
        if(UserCommonUsbTypeCRtsGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_GET_RTS_INFO_LENOVO_SYSTEM_EVENT, pucSystemInfo) == _SUCCESS)
        {
            if(pucSystemInfo[0] == 0xFF)
            {
                pucSystemInfo[0] = 0x00;
            }

            if(pucSystemInfo[1] == 0xFF)
            {
                pucSystemInfo[1] = 0x00;
            }

            stLenovoSysEvent.b1SystemEvent = (bit)(pucSystemInfo[0] & _BIT0);
            stLenovoSysEvent.enumSystemState = (pucSystemInfo[0] & (_BIT3 | _BIT2 | _BIT1)) >> 1;
            stLenovoSysEvent.enumSystemPowerMode = (pucSystemInfo[0] & _BIT4) >> 4;
            stLenovoSysEvent.b3SystemReserved = (pucSystemInfo[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5;
            stLenovoSysEvent.ucSystemAcknowlegde = pucSystemInfo[1];

            memcpy(&stSendGetStatusAck, &tUsbTypeCRtsSMBusWrCmdSendLenovoVdmAck[0], tUsbTypeCRtsSMBusWrCmdSendLenovoVdmAck[0].ucDataLength + 2);

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] Lenovo VID = 0x17EF
            // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01 , [12:11] Rsv., [10:8] Obj. Pos = b'000, [7:0] VDM CMD = Get Status Acl (0x50)
            stSendGetStatusAck.ucVdmHeader0 = 0x50;
            stSendGetStatusAck.ucVdmHeader1 = 0xA0;
            stSendGetStatusAck.ucVdmHeader2 = 0xEF;
            stSendGetStatusAck.ucVdmHeader3 = 0x17;

            // -------- Data Obj 1 : Get Status Ack VDO1-----
            // [31:24] Docking Event, [23:16] System Acknowledge
            // [15:8] System Event, [7:0] Docking Acknowledge
            stSendGetStatusAck.ucByte4 = pucSystemInfo[0];
            stSendGetStatusAck.ucByte5 = pucSystemInfo[0];
            stSendGetStatusAck.ucByte6 = pucSystemInfo[1] & 0xFE;
            stSendGetStatusAck.ucByte7 = GET_TYPE_C_RTS_LENOVO_DOCK_EVENT(enumTypeCPcbPort);

            // -------- Data Obj 2 : Get Status Ack VDO2-----
            // [31:28] FW Ver. = 0, [27:24] Rsv., [23:16] Power Source
            // [15:12] Function Capability, [11:0] Rsv.
            stSendGetStatusAck.ucByte8 = 0x00;
            stSendGetStatusAck.ucByte9 = 0xC0;
            stSendGetStatusAck.ucByte10 = 0x30;
            stSendGetStatusAck.ucByte11 = 0x00;

            // Ask 5400 to Send Get Status Ack
            // Execute Write Command
            if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stSendGetStatusAck.ucCommandCode, 1, stSendGetStatusAck.ucDataLength + 1, &stSendGetStatusAck.ucDataLength, enumTypeCPcbPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            // Polling Write Command Operation Status
            if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            SET_TYPE_C_RTS_LENOVO_DOCK_EVENT(enumTypeCPcbPort, 0x00);
            CLR_TYPE_C_RTS_LENOVO_VDM_RECEIVED(enumTypeCPcbPort);

            // Cancel Lenovo Alt Mode Urgent Event if System Acknowledge Received
            if((pucSystemInfo[1] & _BIT0) == _BIT0)
            {
                if(GET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT() == _TRUE)
                {
                    CLR_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT();
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT);
                }
            }

            memcpy(&stAckCCCI, &tUsbTypeCRtsSMBusWrCmdAckCCCI[0], tUsbTypeCRtsSMBusWrCmdAckCCCI[0].ucDataLength + 2);

            stAckCCCI.ucByte3 = 0x02;

            // Acknowledge 5400 that VDM Has been Received and Processed
            // Execute Write Command
            if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stAckCCCI.ucCommandCode, 1, stAckCCCI.ucDataLength + 1, &stAckCCCI.ucDataLength, enumTypeCPcbPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            // Polling Write Command Operation Status
            if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }
        }
    }

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : enumTypeCPcbPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtsSetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    StructSMBusWRSendLenovoVdmReq stSendAttn;
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtsGetSlaveAddr(enumTypeCPcbPort);

    if(stLenovoDockEvent.b1DockingEvent == _TRUE)
    {
        SET_TYPE_C_RTS_LENOVO_DOCK_EVENT(enumTypeCPcbPort, (((BYTE)stLenovoDockEvent.b4DockingReserved << 4) | (stLenovoDockEvent.enumDockingPowerSwitch << 2) | ((BYTE)stLenovoDockEvent.b1DockingWolRequest << 1) | (BYTE)stLenovoDockEvent.b1DockingEvent));

        memcpy(&stSendAttn, &tUsbTypeCRtsSMBusWrCmdSendLenovoVdmReq[0], tUsbTypeCRtsSMBusWrCmdSendLenovoVdmReq[0].ucDataLength + 2);

        stSendAttn.ucVdmHeader0 = 0x06;
        stSendAttn.ucVdmHeader1 = 0xA1;

        // Execute Write Command
        if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stSendAttn.ucCommandCode, 1, stSendAttn.ucDataLength + 1, &stSendAttn.ucDataLength, enumTypeCPcbPort) == _FAIL)
        {
            return;
        }

        // Polling Write Command Operation Status
        if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
        {
            return;
        }

        SET_TYPE_C_RTS_DETECT_LENOVO_ALT_MODE(enumTypeCPcbPort);
        SET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT();
        ScalerTimerActiveTimerEvent(300, _SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT);
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumTypeCLenovoCheckBusyResult UserCommonUsbTypeCRtsCheckLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort)
{
    if(GET_TYPE_C_RTS_LENOVO_DOCK_EVENT(enumTypeCPcbPort) == 0x00)
    {
        return _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_LENOVO_DOCK_EVENT_BUSY;
    }
}
#endif // End of #if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_PORT_CTRL_LENOVO_ALT_MODE_SUPPORT == _ON))
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
