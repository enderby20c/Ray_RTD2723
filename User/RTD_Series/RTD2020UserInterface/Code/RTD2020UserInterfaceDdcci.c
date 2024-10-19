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
// ID Code      : RTD2020UserInterfaceDdcci.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DDCCI__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceDdcci.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DDCCI_CODE_REDUCTION == _OFF)
//--------------------------------------------------
// Description  : DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDdcciHandler(void)
{
    RTDDdcciHandler();
}

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get Data from DDCCI Buffer defined by user
// Input Value  : None
// Output Value : User defined DDC-CI Status
//--------------------------------------------------
EnumDdcciStatus UserInterfaceDdcciGetFactoryCommand(void)
{
    return _DDCCI_STATUS_OFF;
}

#if((_HDMI_FREESYNC_SUPPORT == _ON) &&\
    (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Check Source Opcode is HDMI freesync
// Input Value  : ucOpcode from DDC-CI buffer
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
EnumDdcciStatus UserInterfaceDdcciCheckHDMIFreesyncOpcode(BYTE ucOpcode)
{
    if(ucOpcode == _HDMI_FREESYNC_MCCS_VCP)
    {
        return _DDCCI_STATUS_ON;
    }
    else
    {
        return _DDCCI_STATUS_OFF;
    }
}
#endif // #if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get DDC-CI Status
// Input Value  : None
// Output Value : User DDC-CI Status
//--------------------------------------------------
EnumDdcciStatus UserInterfaceDdcciGetStatus(void)
{
    if(GET_OSD_DDCCI_STATUS() == _TRUE)
    {
        return _DDCCI_STATUS_ON;
    }
    else
    {
        return _DDCCI_STATUS_OFF;
    }
}

//--------------------------------------------------
// Description  : Get DDC-CI Int Put String
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDdcciGetInputMsg(void)
{
    RTDDdcciGetInputMsg();
}

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle DDCCI Command In Debug Mode
// Input Value  : RecvData : Ddcci Data
//                  ucReplyLen:Reply Len
//                  ucReplyData: Reply Data
// Output Value : None
//--------------------------------------------------
void UserInterfaceDdcciCustomerDebugHandler(BYTE *pucRecvData, BYTE *pucReplyLen, BYTE *pucReplyData)
{
    // Recv Data
    // add for Test
    *pucReplyLen = 2;
    pucReplyData[0] = pucRecvData[0] + 1;
    pucReplyData[1] = pucRecvData[1] + 2;
}
#endif

#endif // End of #if(_DDCCI_CODE_REDUCTION == _OFF)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
