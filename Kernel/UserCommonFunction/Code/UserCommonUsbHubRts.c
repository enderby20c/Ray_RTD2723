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
// ID Code      : UserCommonUsbHubRts.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBHUBRTS__

#include "UserCommonInclude.h"
#include "UsbHubRts/UserCommonUsbHubRts.h"

#if(_USB_HUB_RTS_SUPPORT == _ON)
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command
code StructSMBusWrSetSSMode tUsbHubRtsSMBusWrSetSSMode[1] = {{0x31, 0x01, 0x01}};
code StructSMBusWRDetectDSPSSMode tUsbHubRtsSMBusWDetectDspSSMode[1] = {{0x30, 0x03, 0x00, 0x00, 0x04}};

// Read Command
code StructSMBusRDDetectDSPSSMode tUsbHubRtsSMBusRdDetectDspSSDevice[1] = {{0x80, 0x05, 0x50, 0x50, 0x50, 0x50}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucUsbHubRtsU2InfoByDsp;
BYTE g_ucUsbHubRtsU3InfoByDsp;
BYTE g_ucUsbHubRtsDSP0RawInfo;
BYTE g_ucUsbHubRtsDSP1RawInfo;
BYTE g_ucUsbHubRtsDSP2RawInfo;
BYTE g_ucUsbHubRtsDSP3RawInfo;
bit g_bUsbHubRtsDspU2Change;
bit g_bUsbHubRtsDspU3Change;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Usb Hub Controller Slave Address
// Input Value  : enumInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonUsbHubRtsGetHubAddr(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            return _D0_USB_HUB_RTS_SLAVE_ADDR;

            break;

        case _D1_TYPE_C_PORT:

            return _D1_USB_HUB_RTS_SLAVE_ADDR;

            break;

        case _D2_TYPE_C_PORT:

            return _D2_USB_HUB_RTS_SLAVE_ADDR;

            break;

        default:
            break;
    }

    return _D0_USB_HUB_RTS_SLAVE_ADDR;
}

//--------------------------------------------------
// Description  : Set RTS Hub into SS Mode
// Input Value  : None
// Output Value : Operation result (_USB_HUB_SET_U3_MODE_FAIL / _USB_HUB_SET_U3_MODE_SUCCESS)
//--------------------------------------------------
EnumUsbHubSetU3ModeFailureType UserCommonUsbHubRtsSetSSMode(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn)
{
    StructSMBusWrSetSSMode stWrSSMode;
    BYTE ucSlaveAddr = UserCommonUsbHubRtsGetHubAddr(enumTypeCPcbPort);

    if(UserCommonUsbHubGetControlMode(enumTypeCPcbPort) == _USB_HUB_CTR_BY_USER)
    {
        return UserCommonUsbHubSetSSModeByUser(enumTypeCPcbPort, bEn);
    }

    memcpy(&stWrSSMode, &tUsbHubRtsSMBusWrSetSSMode[0], tUsbHubRtsSMBusWrSetSSMode[0].ucDataLength + 2);

    if(bEn == _ENABLE)
    {
        // Enable SS Mode
        stWrSSMode.ucByte0 = 0x01;
    }
    else
    {
        // Disable SS Mode
        stWrSSMode.ucByte0 = 0x02;
    }

    // Execute Write Command
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, stWrSSMode.ucCommandCode, 1, stWrSSMode.ucDataLength + 1, &stWrSSMode.ucDataLength, enumTypeCPcbPort) == _FAIL)
    {
        return _USB_HUB_SET_U3_MODE_FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
    {
        return _USB_HUB_SET_U3_MODE_FAIL;
    }

    return _USB_HUB_SET_U3_MODE_SUCCESS;
}

//--------------------------------------------------
// Description  : Detect RTS Hub DFP Status
// Input Value  : enumInputPort --> Input Port
// Output Value : Return DFP Status Change or Not
//--------------------------------------------------
EnumHubDspDetectStatus UserCommonUsbHubRtsDetectDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = UserCommonUsbHubRtsGetHubAddr(enumTypeCPcbPort);

    if(UserCommonUsbHubGetControlMode(enumTypeCPcbPort) == _USB_HUB_CTR_BY_USER)
    {
        return UserCommonUsbHubGetDFPStatus(enumTypeCPcbPort);
    }
    else
    {
        // Execute Write Command
        if(UserCommonUsbCommunicationWrite(ucSlaveAddr, tUsbHubRtsSMBusWDetectDspSSMode[0].ucCommandCode, 1, tUsbHubRtsSMBusWDetectDspSSMode[0].ucDataLength + 1, &(tUsbHubRtsSMBusWDetectDspSSMode[0].ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }

        // Polling Write Command Operation Status
        if(UserCommonUsbCommunicationPollingPDReady(ucSlaveAddr, 100, enumTypeCPcbPort) == _FAIL)
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }

        // Read Back Device Reply Data
        if(UserCommonUsbCommunicationRead(ucSlaveAddr, tUsbHubRtsSMBusRdDetectDspSSDevice[0].ucCommandCode, 1, tUsbHubRtsSMBusRdDetectDspSSDevice[0].ucDataLength, &(g_unUsbSMBusRdDataPool.stRdDetectDspSSMode.ucDataLength), enumTypeCPcbPort) == _FAIL)
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }

        // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
        g_unUsbSMBusRdDataPool.stRdDetectDspSSMode.ucCommandCode = tUsbHubRtsSMBusRdDetectDspSSDevice[0].ucCommandCode;

        // Warning : Allen Should Fix This to Multi-Ports Raw Data Marcos
        SET_USB_HUB_RTS_DSP0_INFO(g_unUsbSMBusRdDataPool.stRdDetectDspSSMode.ucDSP0);
        SET_USB_HUB_RTS_DSP1_INFO(g_unUsbSMBusRdDataPool.stRdDetectDspSSMode.ucDSP1);
        SET_USB_HUB_RTS_DSP2_INFO(g_unUsbSMBusRdDataPool.stRdDetectDspSSMode.ucDSP2);
        SET_USB_HUB_RTS_DSP3_INFO(g_unUsbSMBusRdDataPool.stRdDetectDspSSMode.ucDSP3);

        UserCommonUsbHubRtsDspU2InfoChange();
        UserCommonUsbHubRtsDspU3InfoChange();

        if((GET_USB_HUB_RTS_DSP_U2_CHANGE() == _TRUE) || (GET_USB_HUB_RTS_DSP_U3_CHANGE() == _TRUE))
        {
            return _HUB_DSP_DEVICE_CHANGE;
        }
    }

    return _HUB_DSP_DEVICE_NO_CHANGE;
}

//--------------------------------------------------
// Description  : Check Hub DSP U3 Device Change
// Input Value  : stRdDetectDspSSMode --> DSP0/1/2/3 Info
// Output Value : Hub DSP U3 Device Change
//--------------------------------------------------
void UserCommonUsbHubRtsDspU2InfoChange(void)
{
    BYTE ucUsb2HubInfo = 0;

    // List U2 device is connectted in DSPx
    if(GET_USB_HUB_RTS_DSP0_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT0;
    }

    if(GET_USB_HUB_RTS_DSP1_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT1;
    }

    if(GET_USB_HUB_RTS_DSP2_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT2;
    }

    if(GET_USB_HUB_RTS_DSP3_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT3;
    }

    if(GET_USB_HUB_RTS_DSP_U2_INFO() != ucUsb2HubInfo)
    {
        SET_USB_HUB_RTS_DSP_U2_CHANGE(_TRUE);
    }
    else
    {
        SET_USB_HUB_RTS_DSP_U2_CHANGE(_FALSE);
    }

    // Updata U2 Hub Info
    SET_USB_HUB_RTS_DSP_U2_INFO(ucUsb2HubInfo);
}

//--------------------------------------------------
// Description  : Check Hub DSP U3 Device Change
// Input Value  : stRdDetectDspSSMode --> DSP0/1/2/3 Info
// Output Value : Hub DSP U3 Device Change
//--------------------------------------------------
void UserCommonUsbHubRtsDspU3InfoChange(void)
{
    BYTE ucUsb3HubInfo = 0;

    // List U3 device is connectted in DSPx
    if((GET_USB_HUB_RTS_DSP0_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP0_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT0;
    }

    if((GET_USB_HUB_RTS_DSP1_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP1_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT1;
    }

    if((GET_USB_HUB_RTS_DSP2_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP2_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT2;
    }

    if((GET_USB_HUB_RTS_DSP3_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP3_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT3;
    }

    if(GET_USB_HUB_RTS_DSP_U3_INFO() != ucUsb3HubInfo)
    {
        SET_USB_HUB_RTS_DSP_U3_CHANGE(_TRUE);
    }
    else
    {
        SET_USB_HUB_RTS_DSP_U3_CHANGE(_FALSE);
    }

    // Updata U3 Hub Info
    SET_USB_HUB_RTS_DSP_U3_INFO(ucUsb3HubInfo);
}

//--------------------------------------------------
// Description  : Check Hub DSP U3 Device Change
// Input Value  : EnumHubDsp : DSP0/1/2/3
// Output Value : EnumHubDspDeviceAttachDetect : _NOT_ATTACH / _ATTACH_BY_U2 / _ATTACH_BY_U3
//--------------------------------------------------
EnumHubDspDeviceAttachDetect UserCommonUsbHubRtsDspGetUsbAttachInfo(EnumHubDsp enumHubDsp)
{
    if(enumHubDsp == _HUB_DSP0)
    {
        // Check U3 Device
        if((GET_USB_HUB_RTS_DSP0_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP0_INFO() == 0x20))
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U3;
        }

        // Check U2 Device
        if(GET_USB_HUB_RTS_DSP0_INFO() == 0x01)
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U2;
        }
    }

    if(enumHubDsp == _HUB_DSP1)
    {
        // Check U3 Device
        if((GET_USB_HUB_RTS_DSP1_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP1_INFO() == 0x20))
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U3;
        }

        // Check U2 Device
        if(GET_USB_HUB_RTS_DSP1_INFO() == 0x01)
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U2;
        }
    }

    if(enumHubDsp == _HUB_DSP2)
    {
        // Check U3 Device
        if((GET_USB_HUB_RTS_DSP2_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP2_INFO() == 0x20))
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U3;
        }

        // Check U2 Device
        if(GET_USB_HUB_RTS_DSP2_INFO() == 0x01)
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U2;
        }
    }

    if(enumHubDsp == _HUB_DSP3)
    {
        // Check U3 Device
        if((GET_USB_HUB_RTS_DSP3_INFO() == 0x10) || (GET_USB_HUB_RTS_DSP3_INFO() == 0x20))
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U3;
        }

        // Check U2 Device
        if(GET_USB_HUB_RTS_DSP3_INFO() == 0x01)
        {
            return _HUB_DSP_DEVICE_ATTACH_BY_U2;
        }
    }

    return _HUB_DSP_DEVICE_NOT_ATTACH;
}
#endif // End of #if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_BILLBOARD_RTS_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : For RTS Hub to Control Billboard
// Input Value  : enumAtion : _USB_BB_DISABLE / _USB_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubRtsBillboardControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumBillboardCtrl enumAtion)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    // Call User Function for User to Enable / Disable Hub Billboard
    UserInterfaceUsbHubBillboardControl(enumInputPort, enumAtion);
}

//--------------------------------------------------
// Description  : For Hub to Execute BillboardHandler
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubRtsBillboardHandler(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    // Call User Function for User to Execute Hub BillboardHandler
    UserInterfaceUsbHubBillboardHandler(enumInputPort);
}
#endif // End of #if(_BILLBOARD_RTS_HUB_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_RTS_SUPPORT == _ON)

