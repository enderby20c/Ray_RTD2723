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
// ID Code      : UserCommonUsb.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_TYPEC__

#include "UserCommonInclude.h"
#include "Usb/UserCommonUsb.h"

#if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
UnionSMBusRDCommandStrct g_unUsbSMBusRdDataPool;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get OSD U3 Mode Selection
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : _USB_HUB_MODE_U3 / _USB_HUB_MODE_U2 / _USB_HUB_MODE_NONE
//--------------------------------------------------
EnumUsbHubMode UserCommonUsbGetOsdU3Mode(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumUsbHubMode enumUsbMode = _USB_HUB_MODE_NONE;
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);
#endif
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
    EnumOutputPort enumOutputPort = SysUsbTypeCConvertToPxPort(enumTypeCPcbPort);
#endif
    enumUsbMode = enumUsbMode;

    if(enumTypeCPcbPort <= _D6_TYPE_C_PORT)
    {
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
        enumUsbMode = UserInterfaceUsbGetOsdU3Mode(enumInputPort);
#endif
    }
    else if((enumTypeCPcbPort >= _P0_TYPE_C_PORT) && (enumTypeCPcbPort <= _P4_TYPE_C_PORT))
    {
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
        enumUsbMode = UserInterfaceUsbGetOsdTxU3Mode(enumOutputPort);
#endif
    }

    return enumUsbMode;
}

#if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
//--------------------------------------------------
// Description  : SM Bus Arbitration Handle
// Input Value  : None
// Output Value : result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbCommunicationSMBArbitration(void)
{
#if(_SMBUS_ARBITRATION_MODE_SEL == _SMBUS_ARBITRATION_DELAY_MODE)

    bit bStatus = _SMBUS_IDLE;

    PCB_CHECK_SMBUS_BUSY_STATUS(bStatus)

    // Check SM Bus Status
    if(bStatus == _SMBUS_BUSY)
    {
        return _FAIL;
    }
    else
    {
        // Drive Abitation Pin Busy
        PCB_SET_SMBUS_BUSY();
    }

#elif(_SMBUS_ARBITRATION_MODE_SEL == _SMBUS_ARBITRATION_HANDSHAKE_MODE)

    bit bStatus = _SMBUS_IDLE;

    // Step 1.
    PCB_CHECK_SMBUS_BUSY_STATUS(bStatus);

    // Check SM Bus Status
    if(bStatus == _SMBUS_BUSY)
    {
        return _FAIL;
    }

    // Step 2.
    // Drive Abitation Pin Busy
    PCB_SET_SMBUS_BUSY();

    // Step 3.
    // Delay 5us
    DELAY_5US();

    // Step 4.
    // Release Abitation Pin Busy
    PCB_RELEASE_SMBUS_BUSY();

    // Step 5.
    // Check Abitation Pin Idle ?
    PCB_CHECK_SMBUS_BUSY_STATUS(bStatus);

    // Check SM Bus Status
    if(bStatus == _SMBUS_IDLE)
    {
        // Step 5-1.
        // Drive Abitation Pin Busy For Obtaining The Right of Control
        PCB_SET_SMBUS_BUSY();
    }
    else
    {
        // Step 5-2.
        // Not Obtain The Right of Control, Maybe Hub is Using SM Bus Now
        return _FAIL;
    }

#endif

    return _SUCCESS; // Do Nothing, Return _SUCCESS Directly
}

//--------------------------------------------------
// Description  : SM Bus Arbitration Status Release
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonUsbCommunicationReleaseSMbusCtlPin(void)
{
#if(_SMBUS_ARBITRATION_MODE_SEL != _SMBUS_ARBITRATION_NONE)
    // Release Abitation Pin Busy
    PCB_RELEASE_SMBUS_BUSY();
#endif
}

//--------------------------------------------------
// Description  : Write data to the target device address by SMBus
// Input Value  : ucSlaveAddr       --> Device Address
//                usSubAddr         --> Start address of selected device
//                ucSubAddrLength   --> Sub address length
//                usLength          --> Numbers of data we want to write
//                pReadArray        --> Result array
//                enumTypeCPcbPort       --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#ifdef __C51__
#pragma save
#pragma OT(8)
#endif
bit UserCommonUsbCommunicationWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bStatus = _SUCCESS;
    BYTE ucSWIICStatus = _IIC_NONE;
    BYTE ucHwIICPinNum = _NO_IIC_PIN;

    ucSlaveAddr = ucSlaveAddr;
    usSubAddr = usSubAddr;
    ucSubAddrLength = ucSubAddrLength;
    usLength = usLength;
    pucWriteArray = pucWriteArray;
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(UserCommonUsbCommunicationSMBArbitration() == _FAIL)
    {
        return _FAIL;
    }

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

#if(_D0_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D0;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D0_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _D1_TYPE_C_PORT:

#if(_D1_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D1;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D1_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _D2_TYPE_C_PORT:

#if(_D2_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D2;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D2_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _P0_TYPE_C_PORT:

#if(_P0_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS_P0, _P0_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_NONE, _P0_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P1_TYPE_C_PORT:

#if(_P1_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS_P1, _P1_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_NONE, _P1_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P2_TYPE_C_PORT:

#if(_P2_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS_P2, _P2_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_NONE, _P2_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P3_TYPE_C_PORT:

#if(_P3_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS_P3, _P3_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_NONE, _P3_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P4_TYPE_C_PORT:

#if(_P4_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS_P4, _P4_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_NONE, _P4_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:

#if(_ADAPTOR_TYPE_C_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS_ADAPTOR, _ADAPTOR_TYPE_C_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_NONE, _ADAPTOR_TYPE_C_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        default:

            break;
    }

    // Release SM Bus Control
    UserCommonUsbCommunicationReleaseSMbusCtlPin();

    return bStatus;
}
#ifdef __C51__
#pragma restore
#endif

//--------------------------------------------------
// Description  : Read data to the External EEPROM by IIC
// Input Value  : ucSlaveAddr       --> Slave Address
//                usSubAddr         --> Start address of selected device
//                ucSubAddrLength   --> Sub address length, if ucSubAddrLength = 0 represent short read command
//                usLength          --> Numbers of data we want to read
//                pReadArray        --> Result array
//                enumTypeCPcbPort
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbCommunicationRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bStatus = _SUCCESS;
    BYTE ucSWIICStatus = _IIC_NONE;
    BYTE ucHwIICPinNum = _NO_IIC_PIN;

    ucSlaveAddr = ucSlaveAddr;
    usSubAddr = usSubAddr;
    ucSubAddrLength = ucSubAddrLength;
    usLength = usLength;
    pucReadArray = pucReadArray;
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(UserCommonUsbCommunicationSMBArbitration() == _FAIL)
    {
        return _FAIL;
    }

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

#if(_D0_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D0;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D0_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _D1_TYPE_C_PORT:

#if(_D1_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D1;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D1_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _D2_TYPE_C_PORT:

#if(_D2_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D2;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D2_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _P0_TYPE_C_PORT:

#if(_P0_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS_P0, _P0_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_NONE, _P0_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P1_TYPE_C_PORT:

#if(_P1_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS_P1, _P1_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_NONE, _P1_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P2_TYPE_C_PORT:

#if(_P2_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS_P2, _P2_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_NONE, _P2_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P3_TYPE_C_PORT:

#if(_P3_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS_P3, _P3_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_NONE, _P3_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P4_TYPE_C_PORT:

#if(_P4_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS_P4, _P4_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_NONE, _P4_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:

#if(_ADAPTOR_TYPE_C_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS_ADAPTOR, _ADAPTOR_TYPE_C_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_NONE, _ADAPTOR_TYPE_C_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        default:

            break;
    }

    // Release SM Bus Control
    UserCommonUsbCommunicationReleaseSMbusCtlPin();

    return bStatus;
}

//--------------------------------------------------
// Description  : Short Read Command
// Input Value  : ucDeviceAddr --> Device Address
//                pucReadArray --> Result array
//                enumTypeCPcbPort  --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbCommunicationShortRead(BYTE ucDeviceAddr, BYTE *pucReadArray, EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bStatus = _SUCCESS;
    BYTE ucSWIICStatus = _IIC_NONE;
    BYTE ucHwIICPinNum = _NO_IIC_PIN;

    ucDeviceAddr = ucDeviceAddr;
    pucReadArray = pucReadArray;
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(UserCommonUsbCommunicationSMBArbitration() == _FAIL)
    {
        return _FAIL;
    }

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

#if(_D0_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D0;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D0_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _D1_TYPE_C_PORT:

#if(_D1_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D1;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D1_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _D2_TYPE_C_PORT:

#if(_D2_USB_COMMUNICATION_SW_IIC == _ON)
            // SW IIC
            ucSWIICStatus = _IIC_SMBUS_D2;
            ucHwIICPinNum = _SW_IIC_PIN_GPIO;
#else
            // HW IIC
            ucSWIICStatus = _IIC_NONE;
            ucHwIICPinNum = _D2_USB_RTS_SMBUS_IIC;
#endif
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, ucSWIICStatus, ucHwIICPinNum) == _FAIL)
            {
                bStatus = _FAIL;
            }

            break;

        case _P0_TYPE_C_PORT:

#if(_P0_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS_P0, _P0_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_NONE, _P0_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P1_TYPE_C_PORT:

#if(_P1_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS_P1, _P1_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_NONE, _P1_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P2_TYPE_C_PORT:

#if(_P2_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS_P2, _P2_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_NONE, _P2_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P3_TYPE_C_PORT:

#if(_P3_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS_P3, _P3_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_NONE, _P3_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _P4_TYPE_C_PORT:

#if(_P4_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS_P4, _P4_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_NONE, _P4_USB_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:

#if(_ADAPTOR_TYPE_C_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO)
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS_ADAPTOR, _ADAPTOR_TYPE_C_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#else
            if(UserCommonUsbCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_NONE, _ADAPTOR_TYPE_C_RTS_SMBUS_IIC) == _FAIL)
            {
                bStatus = _FAIL;
            }
#endif
            break;

        default:

            break;
    }

    // Release SM Bus Control
    UserCommonUsbCommunicationReleaseSMbusCtlPin();

    return bStatus;
}

//--------------------------------------------------
// Description  : Read data to the External Device by SMBus
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbCommunicationSMBRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    ucSWIICStatus = ucSWIICStatus;

    if(usLength == 0)
    {
        return _FAIL;
    }

#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_USB_HUB_RTS_SUPPORT == _ON))
    //////////////////////////////////////////////////////////////////////
    /////////////////// Prevent dangerous data Series Occurred On SM BUS///
    // If the data series start + 0xD4 + 0x02 was sent on SM bus, it will erase the rom code of 54xx series port controller or 54xx series hub device
    if((ucSlaveAddr == 0xD4) && (usSubAddr == 0x02))
    {
        return _FAIL;
    }
    //////////////////////////////////////////////////////////////////////
#endif

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
            // Receive max _SMBUS_READ_DATA_LEN bytes each time
            ucDataCnt = _SMBUS_READ_DATA_LEN;
        }
        else
        {
            // Receive max _HW_IIC_BUFFER_SIZE bytes each time
            ucDataCnt = _HW_IIC_BUFFER_SIZE;
        }

        // Check if more than 30 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)
        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#ifdef __C51__
#pragma save
#pragma OT(8)
#endif
bit UserCommonUsbCommunicationSMBWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_SMBUS_WRITE_DATA_LEN + 2];

    ucSWIICStatus = ucSWIICStatus;

    if(usLength == 0)
    {
        return _FAIL;
    }

#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_USB_HUB_RTS_SUPPORT == _ON))
    //////////////////////////////////////////////////////////////////////
    /////////////////// Prevent dangerous data Series Occurred On SM BUS///
    // If the data series start + 0xD4 + 0x02 was sent on SM bus, it will erase the rom code of 54xx series port controller or 54xx series hub device
    if((ucSlaveAddr == 0xD4) && (usSubAddr == 0x02))
    {
        return _FAIL;
    }
    //////////////////////////////////////////////////////////////////////
#endif

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max _SMBUS_WRITE_DATA_LEN bytes each time
        ucDataCnt = _SMBUS_WRITE_DATA_LEN;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)
        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}
#ifdef __C51__
#pragma restore
#endif

//--------------------------------------------------
// Description  : Get External Device IC Status
// Input Value  : ucDeviceAddr --> RTS Port Ctrl/Hub Slave Address
//                usTime       --> Polling Time, Unit: ms
//                enumTypeCPcbPort
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbCommunicationPollingPDReady(BYTE ucDeviceAddr, WORD usTime, EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucCmdStatus = 0;

    while(usTime > 0)
    {
        UserCommonUsbCommunicationShortRead(ucDeviceAddr, &ucCmdStatus, enumTypeCPcbPort);

        switch(ucCmdStatus & (_BIT1 | _BIT0))
        {
            case _SMBUS_CMD_STATUS_COMPLETE:

                return _SUCCESS;

            case _SMBUS_CMD_STATUS_ERROR:

                return _FAIL;

            case _SMBUS_CMD_STATUS_DEFER:
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
                if(GET_TYPE_C_RTS_SMBUS_CMD_TYPE(enumTypeCPcbPort) == _TYPE_C_SET_RTS_INFO_SRC_PDO)
                {
                    return _SUCCESS;
                }
#endif
                break;

            default:
            case _SMBUS_CMD_STATUS_NOTPROCEED:
                break;
        }

        usTime--;

        ScalerTimerDelayXms(2);
    }

    return _FAIL;
}
#endif // End of #if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : All Dp Port Lane Count Switch in TypeC U3 Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRxSetLaneCountCapabilitySwitch(void)
{
#if(_D0_TYPE_C_CONNECTOR_SUPPORT == _ON)
    SysUsbTypeCRxSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
#endif

#if(_D1_TYPE_C_CONNECTOR_SUPPORT == _ON)
    SysUsbTypeCRxSetCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
#endif

#if(_D2_TYPE_C_CONNECTOR_SUPPORT == _ON)
    SysUsbTypeCRxSetCapabilityChangeFlag(_D2_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
#endif
}
#endif// End of #if(_DP_SUPPORT == _ON)

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Extern file name to user
// Input Value  : ucUsbFat32UserFileNameOffset
// Output Value : file name
//--------------------------------------------------
BYTE UserCommonUsb2HostGetFileName(BYTE ucUsbUserFileNameOffset)
{
    return ScalerUsbFileSysGetFileName(ucUsbUserFileNameOffset);
}

//--------------------------------------------------
// Description  : Output EHCI Connect Status to User
// Input Value  : None
// Output Value : bEhciIsConnect
//--------------------------------------------------
bit UserCommonUsb2HostGetConnectStatus(void)
{
    return ScalerUsbFileSysGetConnectStatus();
}

//--------------------------------------------------
// Description  : Output USB File Info. to User
// Input Value  : None
// Output Value : stUserUsbInfo
//--------------------------------------------------
StructUsbFileSysUserFileInfo UserCommonUsb2HostGetFileInfo(void)
{
    return ScalerUsbFileSysGetFileInfo();
}

#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#endif // End of #if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

