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
// ID Code      : ScalerUsbU2Host.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_U2HOST__

#include "ScalerFunctionInclude.h"
#include "UsbU2Host/ScalerUsbU2Host.h"

#if(_USB2_HOST_SUPPORT == _ON)
//****************************************************************************************************
// CODE TABLES
//****************************************************************************************************

//****************************************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************************************
BYTE g_ucUsbU2HostDeviceSpeed = _U2HOST_EHCI_DEVICE_SPEED_NONE;

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
BYTE g_ucUsbU2HostColorWriteReqLen = 0;
BYTE g_pucUsbU2HostColorWriteReqData[24] = {0};
BYTE g_ucUsbU2HostColorReadRspLen = 0;
#endif
#endif

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
BYTE g_ucUsbU2HostModeState = _U2HOST_MODE_STATE_POWER_OFF;
BYTE g_ucUsbU2HostCommunicateState = _U2HOST_COMMUNICATE_STATE_NONE;
BYTE g_ucUsbU2HostConnectStatus = _U2HOST_CONNECT_STATUS_NONE;
BYTE g_ucUsbU2HostEnumState = _U2HOST_ENUM_STATE_NONE;

BYTE g_ucUsbU2HostOwner = _U2HOST_OWNER_NONE;

BYTE g_ucUsbU2HostNextStateAfterHalt;
StructUsbU2HostCTSFlowCtrlFlag g_stUsbU2HostCTSFlowCtrlFlag;

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
BYTE g_ucUsbU2HostBulkScsiState = _U2HOST_BULK_SCSI_NONE;
BYTE g_ucUsbU2HostDDRReadyState = _U2HOST_DDR_NONE;
BYTE g_ucUsbU2HostBulkInQTDFlag = _FALSE;
BYTE g_ucUsbU2HostScsiFlowFlag;

// BYTE ucUsbU2HostCurDBPatternIndex = 0;
StructUsbU2HostDBCurPathInfo g_stUsbU2HostDBCurPath;
StructUsbStorageDeviceInfoTable g_stUsbU2HostStorageDeviceInfo;

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
// 48 bit crc - crc only en result
BYTE g_pucUsbU2HostDMCrcResultGolden[6];

// 48 bit crc  crc + xfer both en result
BYTE g_pucUsbU2HostDMCrcResultTBD[6];

BYTE g_ucUsbU2HostCurCrcValueSame = _U2HOST_DB_CRC_NONE;
#endif
bit g_bUsbU2HostFirstUpdateFlag = _FALSE;
bit g_bUsbU2HostDDRFRCClientEnStatus = _TRUE;
#endif // END OF #if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
StructUsbHIDDesInfo g_pstUsbU2HostHIDDesInfo[_U2HOST_OHCI_INT_ED_NUM];
StructUsbIntEDInfo g_pstUsbU2HostIntEDInfo[_U2HOST_OHCI_INT_ED_NUM];
BYTE g_ucUsbU2HostOhci1stInterfaceType = _U2HOST_OHCI_INTERFACE_NONE;
BYTE g_ucUsbU2HostOhci2ndInterfaceType = _U2HOST_OHCI_INTERFACE_NONE;
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
StructUsbU2HostLineCodeInfo g_stUsbU2HostGetLineCodeInfo;
EnumUsbU2HostColorAnalyzerState g_enumUsbU2HostColorAnalyzerState = _U2HOST_COLOR_NONE;
EnumUsbU2HostColorReqStatus g_enumUsbU2HostColorReqStatus = _U2HOST_COLOR_REQ_NONE;
EnumUsbU2HostColorRspStatus g_enumUsbU2HostColorRspStatus = _U2HOST_COLOR_RSP_NONE;
#endif // END OF #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_OHCI_SUPPORT == _ON)

WORD g_pusUsbU2HostBulkInEndpSize[_U2HOST_DEVICE_NUM];
WORD g_pusUsbU2HostBulkOutEndpSize[_U2HOST_DEVICE_NUM];
BYTE g_pucUsbU2HostBulkInEndpAddr[_U2HOST_DEVICE_NUM];
BYTE g_pucUsbU2HostBulkOutEndpAddr[_U2HOST_DEVICE_NUM];

bit g_bUsbU2HostModeStateChangeFlag = _FALSE;
bit g_bUsbU2HostConnectDetReadyFlag = _TRUE;

BYTE g_ucUsbU2HostCurrDeviceNo = _U2HOST_NONE;
BYTE g_ucUsbU2HostCurrDeviceAddr;

// Temp , will be instead of dummy reg from CYChen2
bit g_bUsbU2HostDummyRegBit0 = _FALSE;

BYTE g_ucUsbU2HostPreUsbTestMode;
BYTE g_ucUsbU2HostPreProTestCtrl;
BYTE g_ucUsbU2HostTestIndex;

StructUsbFlowCtrlFlag g_stUsbU2HostFlowCtrlFlag;

StructUsbDeviceInfo g_pstUsbU2HostDeviceInfo[(_U2HOST_DEVICE_ATTACH_INDEX + 1)];

// Descriptor Info.
StructUsbDeviceInfoTable g_stUsbU2HostDeviceInfo;
StructUsbConfigDesInfo g_stUsbU2HostConfigDesInfo;
StructUsbIntfAsocDesInfo g_stUsbU2HostIntfAsocDesInfo;
StructUsbIntfDesInfo g_pstUsbU2HostIntfDesInfo[2];
StructUsbEndptDesInfo g_pstUsbU2HostEndptDesInfo[3];
#endif // END OF #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
BYTE g_pucUsbU2HostColorReadRspData[128] = {0};
BYTE g_ucUsbU2HostColorReadDataLen = 0;
#endif
#endif // END OF #if(_USB2_HOST_OHCI_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
//****************************************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************************************
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
//----------------------------------------------------------------------------------------------------
// Description  : USB Host Judge Handler Process
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostJudgeHandler(void)
{
    if(GET_U2HOST_CONNECT_DET_READY_FLAG() == _TRUE)
    {
        ScalerUsbU2HostConnectHandler(GET_U2HOST_OWENER());
    }

    switch(GET_U2HOST_MODE_STATE())
    {
        case _U2HOST_MODE_STATE_EHCI_RH_PORT_ENABLE:

            if(ScalerUsbU2HostRhPortEnable(_U2HOST_OWNER_EHCI) == _TRUE)   // Device is High Speed
            {
                ScalerUsbU2HostCurOwerInit(_U2HOST_OWNER_EHCI);

                SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_COMMUNICATION);
                DebugMessageU2Host("[Mode State] To_COMMUNICATION", 0);
                SET_U2HOST_MODE_STATE_CHANGE_FLAG();

                SET_U2HOST_COMMUNICATE_STATE(_U2HOST_COMMUNICATE_STATE_ENUMERATION);
                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ADD_CTRL_QH);
            }
            else   // Device is FULL or Low Speed
            {
                SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_OHCI_POWER_ON);
                DebugMessageU2Host("[Mode State] OHCI_POWER_ON", 0);
                SET_U2HOST_MODE_STATE_CHANGE_FLAG();
            }

            break;

        case _U2HOST_MODE_STATE_COMMUNICATION:

            break;

        case _U2HOST_MODE_STATE_OHCI_POWER_ON:

            SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_OHCI_RH_PORT_ENABLE);
            SET_U2HOST_MODE_STATE_CHANGE_FLAG();
            break;

        case _U2HOST_MODE_STATE_OHCI_RH_PORT_ENABLE:

            if(ScalerUsbU2HostRhPortEnable(_U2HOST_OWNER_OHCI) == _TRUE)
            {
                ScalerUsbU2HostCurOwerInit(_U2HOST_OWNER_OHCI);

                SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_COMMUNICATION);
                DebugMessageU2Host("[Mode State] COMMUNICATION", 0);
                SET_U2HOST_MODE_STATE_CHANGE_FLAG();

                SET_U2HOST_COMMUNICATE_STATE(_U2HOST_COMMUNICATE_STATE_ENUMERATION);
                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ADD_CTRL_QH);
            }
            else
            {
                // OHCI Port EN fail/Error Handeling,ex. High speed device attched on Ohci at this moment
                ScalerUsbU2HostMacReset();
                SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_POWER_OFF);
                DebugMessageU2Host("[Mode State] ModeStateOFF", 0);
                // ScalerUsbU2HostPortOwnerSwitch(_U2HOST_OWNER_EHCI);
            }

            break;

        case _U2HOST_MODE_STATE_ROOT_HUB_REMOVE_DEVICE:

            break;

        default:

            break;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Enumeration State Machine
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostEnum(EnumUsbU2HostOwner enumOwner)
{
    switch(GET_U2HOST_ENUM_STATE())
    {
        case _U2HOST_ENUM_STATE_ADD_CTRL_QH:

            ScalerUsbU2HostAddCtrlQH(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            SET_U2HOST_COMPLETE_STATUS();   // Non-Reply from Device

            break;

        case _U2HOST_ENUM_STATE_SET_ADDRESS:

            ScalerUsbU2HostSetAddress(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR:

            ScalerUsbU2HostGetDeviceDescriptor(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;


        case _U2HOST_ENUM_STATE_GET_CONFIG_DESCRIPTOR:

            ScalerUsbU2HostGetConfigDescriptor(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_GET_OTHER_DESCRIPTOR:

            ScalerUsbU2HostGetOtherDescriptor(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_GET_LANGUAGE_ID:

            ScalerUsbU2HostGetLanguageID(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_GET_MANUFACTURE_NAME:

            ScalerUsbU2HostGetManufactureName(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_GET_PRODUCT_NAME:

            ScalerUsbU2HostGetProductName(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_GET_SERIAL_NUMBER:

            ScalerUsbU2HostGetSerialNumber(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_SET_CONFIGURATION:

            ScalerUsbU2HostSetConfiguration(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        case _U2HOST_ENUM_STATE_SET_IDLE:

            ScalerUsbU2HostSetIdle(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);
            break;

        case _U2HOST_ENUM_STATE_GET_HID_REPORT:

            ScalerUsbU2HostGetHIDReport(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);
            break;

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        case _U2HOST_ENUM_STATE_GET_LINE_CODING:

            ScalerUsbU2HostGetLineCoding(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);
            break;

        case _U2HOST_ENUM_STATE_SET_CONTROL_LINE_STATE:

            ScalerUsbU2HostSetControlLineState(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);
            break;

        case _U2HOST_ENUM_STATE_SET_LINE_CODING:

            ScalerUsbU2HostSetLineCoding(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);
            break;
#endif
#endif

        case _U2HOST_ENUM_STATE_GET_MAX_LUN:

            ScalerUsbU2HostGetMaxLun(enumOwner, _U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_ENUM_STATE_ABORT:

            DebugMessageU2Host("[Enum] Abort", 0);
            SET_U2HOST_COMPLETE_STATUS();   // Non-Reply from Device

            break;

        case _U2HOST_ENUM_STATE_FINISH:

            SET_U2HOST_COMPLETE_STATUS();   // Non-Reply from Device

            break;

        default:

            break;
    }
}
//----------------------------------------------------------------------------------------------------
// Description  : USB Enumeration State Data Handler
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostEnumDataHandler(EnumUsbU2HostOwner enumOwner)
{
    BYTE ucValueTemp1 = 0;
    BYTE ucDescriptorType = 0;
    BYTE ucDescriptorType1 = 0;
    WORD usByteOffsetAdjust = 0;
    WORD usByteOffsetAdjust1 = 0;
    BYTE ucCurDesType = 0;
    BYTE ucCurDesLen = 0;
    WORD usCurByteOffset = 0;
    BYTE pucEnum32ByteTmp[32] = {0};

    ucValueTemp1 = ucValueTemp1;
    ucDescriptorType = ucDescriptorType;
    ucDescriptorType1 = ucDescriptorType1;
    usByteOffsetAdjust = usByteOffsetAdjust;
    usByteOffsetAdjust1 = usByteOffsetAdjust1;
    ucCurDesType = ucCurDesType;
    ucCurDesLen = ucCurDesLen;
    usCurByteOffset = usCurByteOffset;
    pucEnum32ByteTmp[0] = pucEnum32ByteTmp[0];

    if(GET_U2HOST_TRANSFER_STATUS() == _TRUE)
    {
        if(ScalerUsbU2HostChkCtrlQueueErrSts(enumOwner) == _TRUE)
        {
            // Error Handling
            DebugMessageU2HostEHCI("[Err] Ctrl transfer Err", 0);
            return;
        }
        else if(ScalerUsbU2HostChkCtrlQueueComplete(enumOwner) == _TRUE)
        {
            // DebugMessageU2HostEHCI("[Data] Ctrl transfer Complete", 0);

            CLR_U2HOST_TRANSFER_STATUS();

            // OHCI Use as 6369 U2host,So OHCI Maintain the way as besfore ,Not Disable it
            if(enumOwner == _U2HOST_OWNER_EHCI)
            {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
                if((GET_U2HOST_ENUM_STATE() & (_BIT4 | _BIT5)) != 0x00)   // Need Spec Defined Command that is not defined by yourself
                {
                    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _DISABLE);
                    DebugMessageU2HostEHCI("[EHCI] Async Schedule Disable", 0);
                }
#endif
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        switch(GET_U2HOST_ENUM_STATE())
        {
            case _U2HOST_ENUM_STATE_ADD_CTRL_QH:

                if((GET_U2HOST_CTS_EN_STATUS() == _TRUE) && (GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_SIGN_GET_DEV_DESC))
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR);
                }
                else
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_ADDRESS);
                }

                break;

            case _U2HOST_ENUM_STATE_SET_ADDRESS:

                // It's necessary ?  - TBD
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));   // Set QH.Device Address

                DebugMessageU2HostEHCI("[Data] Set Address", GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR);

                break;

            case _U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR:

                if(GET_U2HOST_SECOND_PROC_STATUS() == _FALSE)
                {
                    if((GET_U2HOST_CTS_EN_STATUS() == _TRUE) && (GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_SIGN_GET_DEV_DESC))
                    {
                        // SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);
                        SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_POWER_OFF);
                        return;
                    }
                    else
                    {
                        SET_U2HOST_SECOND_PROC_STATUS();
                        g_stUsbU2HostDeviceInfo.ucDeviceDesLen = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_LENGTH);
                        g_stUsbU2HostDeviceInfo.ucMaxPacketSize0 = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_MAX_PACKET_SIZE_0);
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D01_B10_MPL, g_stUsbU2HostDeviceInfo.ucMaxPacketSize0);

                        DebugMessageU2HostEHCI("[Data] Get Device MPS", g_stUsbU2HostDeviceInfo.ucMaxPacketSize0);

                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR);   // Get Device Descriptor again. (Get "Fully" Device Descriptor Data)
                    }
                }
                else
                {
                    CLR_U2HOST_SECOND_PROC_STATUS();

                    g_stUsbU2HostDeviceInfo.usVendorID = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_ID_VENDOR);
                    g_stUsbU2HostDeviceInfo.usProductID = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_ID_PRODUCT);
                    g_stUsbU2HostDeviceInfo.usBcdDevice = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_BCD_DEVICE);
                    g_stUsbU2HostDeviceInfo.ucDeviceClass = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_CLASS);
                    g_stUsbU2HostDeviceInfo.ucDeviceSubClass = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_SUB_CLASS);
                    g_stUsbU2HostDeviceInfo.ucManufacturerIndex = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_I_MANUFACTURER);
                    g_stUsbU2HostDeviceInfo.ucProductIndex = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_I_PRODUCT);
                    g_stUsbU2HostDeviceInfo.ucSerialNumberIndex = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_DEVICE_DES_I_SERIAL_NUMBER);

                    DebugMessageU2HostEHCI("[Data] Device Class", g_stUsbU2HostDeviceInfo.ucDeviceClass);
                    DebugMessageU2HostEHCI("[Data] Device SubClass", g_stUsbU2HostDeviceInfo.ucDeviceSubClass);
                    DebugMessageU2HostEHCI("[Data] Manufacturer Index =", g_stUsbU2HostDeviceInfo.ucManufacturerIndex);
                    DebugMessageU2HostEHCI("[Data] Product Index =", g_stUsbU2HostDeviceInfo.ucProductIndex);
                    DebugMessageU2HostEHCI("[Data] Serial Number Index =", g_stUsbU2HostDeviceInfo.ucSerialNumberIndex);

                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_CONFIG_DESCRIPTOR);
                }

                break;

            case _U2HOST_ENUM_STATE_GET_CONFIG_DESCRIPTOR:

                ucDescriptorType = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CONFIG_DES_TYPE);
                if(ucDescriptorType == 0x02)   // Get Configuration Descriptor
                {
                    g_stUsbU2HostConfigDesInfo.ucConfigValue = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CONFIG_DES_VALUE);
                    DebugMessageU2HostEHCI("[Data] Get bConfigurationValue", g_stUsbU2HostConfigDesInfo.ucConfigValue);

                    g_stUsbU2HostConfigDesInfo.usTotalLength = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CONFIG_DES_TOTAL_LENGTH);
                    DebugMessageU2HostEHCI("[Data] Get Conf.TotalLeng", g_stUsbU2HostConfigDesInfo.usTotalLength);

                    g_stUsbU2HostConfigDesInfo.ucNumInterface = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CONFIG_DES_NUM_INTERFACES);
                    DebugMessageU2HostEHCI("[Data] Get conf.interfaceNum", g_stUsbU2HostConfigDesInfo.ucNumInterface);
                }
                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_OTHER_DESCRIPTOR);

                if((GET_U2HOST_CTS_EN_STATUS() == _TRUE) && (GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_ENUM))
                {
                    // SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);
                    SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_POWER_OFF);

                    ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);
                    return;
                }

                break;

            case _U2HOST_ENUM_STATE_GET_OTHER_DESCRIPTOR:

                //====== (1) Get Configuration Descriptor ======//
                ucDescriptorType = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CONFIG_DES_TYPE);
                if(ucDescriptorType == 0x02)   // Get Configuration Descriptor
                {
                    //====== (2) Get Interface Descriptor ======//
                    usByteOffsetAdjust = 0x0900;

                    ucDescriptorType = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_INTF_DES_TYPE + usByteOffsetAdjust);
                    if(ucDescriptorType == 0x04)   // Get Interface Descriptor
                    {
                        g_pstUsbU2HostIntfDesInfo[0].ucInterfaceClass = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_INTF_DES_CLASS + usByteOffsetAdjust);

                        g_pstUsbU2HostIntfDesInfo[0].ucInterfaceSubClass = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_INTF_DES_SUB_CLASS + usByteOffsetAdjust);

                        g_pstUsbU2HostIntfDesInfo[0].ucInterfaceProtocol = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_INTF_DES_PROTOCOL + usByteOffsetAdjust);

                        if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceClass == 0x08)   // Mass storage Device
                        {
                            if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceSubClass == 0x06)  // SCSI Command
                            {
                                if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceProtocol == 0x50)  // bulk-only
                                {
                                    SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_MASS_STORAGE);

                                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                                    DebugMessageU2HostEHCI("[Data] Mass Storge Device is Supported", 0);
                                }
                                else
                                {
                                    DebugMessageU2HostEHCI("[Data] Mass Storge Device Not Bulk-Only", 0);
                                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                                    return;
                                }
                            }
                            else
                            {
                                DebugMessageU2HostEHCI("[Data] Mass Storge Device Not SCSI", 0);
                                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                                return;
                            }
                        }
                        else
                        {
                            DebugMessageU2HostEHCI("[Data] Not Mass Storge Device", 0);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }

                        //====== (3) Get Endpoint Descriptor ======//
                        if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_MASS_STORAGE)
                        {
                            usByteOffsetAdjust = 0x1200;
                            usByteOffsetAdjust1 = 0x1900;
                        }

                        ucDescriptorType = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_TYPE + usByteOffsetAdjust);
                        ucDescriptorType1 = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_TYPE + usByteOffsetAdjust1);

                        // Get Bulk Endpoint1 Descriptor Info
                        if(ucDescriptorType == 0x05)
                        {
                            g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_ADDRESS + usByteOffsetAdjust); // 0x0F
                            g_pstUsbU2HostEndptDesInfo[0].ucInterval = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_INTERVAL + usByteOffsetAdjust);
                            g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_MAX_PACKET_SIZE + usByteOffsetAdjust);

                            // Check In/Out endpoint :1 : IN /  0: OUT
                            if((g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress & _BIT7) == _BIT7)
                            {
                                SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize);
                                SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);
                                DebugMessageU2HostEHCI("[Data] Bulk In Endpoint MPS", g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize);
                                DebugMessageU2HostEHCI("[Data] Bulk In Endpoint Addr", g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);
                            }
                            else
                            {
                                SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize);
                                SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);

                                DebugMessageU2HostEHCI("[Data] Bulk Out Endpoint MPS", g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize);
                                DebugMessageU2HostEHCI("[Data] Bulk Out Endpoint Addr", g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);
                            }

                            DebugMessageU2HostEHCI("[Data] Endpoint Address", g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);
                            DebugMessageU2HostEHCI("[Data] Endpoint Interval", g_pstUsbU2HostEndptDesInfo[0].ucInterval);
                        }
                        else
                        {
                            DebugMessageU2HostEHCI("[Err] Get Other Descriptor - Endpoint Not Correct", 0);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }

                        // Get Bulk Endpoint2 Descriptor Info
                        if(ucDescriptorType1 == 0x05)
                        {
                            g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_ADDRESS + usByteOffsetAdjust1); // 0x0F
                            g_pstUsbU2HostEndptDesInfo[1].ucInterval = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_INTERVAL + usByteOffsetAdjust1);
                            g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_ENDPT_DES_MAX_PACKET_SIZE + usByteOffsetAdjust1);

                            // Check In/Out endpoint :1 : IN /  0: OUT
                            if((g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress & _BIT7) == _BIT7)
                            {
                                SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize);
                                SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress);
                                DebugMessageU2HostEHCI("[Data] Bulk In Endpoint MPS", g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize);
                                DebugMessageU2HostEHCI("[Data] Bulk In Endpoint Addr", g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress);
                            }
                            else
                            {
                                SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize);
                                SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress);

                                DebugMessageU2HostEHCI("[Data] Bulk Out Endpoint MPS", g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize);
                                DebugMessageU2HostEHCI("[Data] Bulk Out Endpoint Addr", g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress);
                            }

                            DebugMessageU2HostEHCI("[Data] Endpoint Address", g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress);
                            DebugMessageU2HostEHCI("[Data] Endpoint Interval", g_pstUsbU2HostEndptDesInfo[1].ucInterval);
                        }
                        else
                        {
                            DebugMessageU2HostEHCI("[Err] Get Other Descriptor - Endpoint Not Correct", 0);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }
                    }
                    else
                    {
                        DebugMessageU2HostEHCI("[Err] Get Other Descriptor Sequence Not Correct - Interface", 0);

                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }
                }
                else
                {
                    DebugMessageU2HostEHCI("[Err] Get Other Descriptor Sequence Not Correct - Configuration", 0);
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                    return;
                }

                break;

            case _U2HOST_ENUM_STATE_GET_LANGUAGE_ID:
                g_stUsbU2HostDeviceInfo.usLanguageID = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_STRING_DES_STRING);

                DebugMessageU2HostEHCI("[Data] Get Language ID", g_stUsbU2HostDeviceInfo.usLanguageID);

                if(g_stUsbU2HostDeviceInfo.ucManufacturerIndex != 0x00)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_MANUFACTURE_NAME);
                }
                else if(g_stUsbU2HostDeviceInfo.ucProductIndex != 0x00)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_PRODUCT_NAME);
                }
                else if(g_stUsbU2HostDeviceInfo.ucSerialNumberIndex != 0x00)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_SERIAL_NUMBER);
                }
                else
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                }

                break;

            case _U2HOST_ENUM_STATE_GET_MANUFACTURE_NAME:

                g_stUsbU2HostDeviceInfo.ucManufacturerNameSize = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_STRING_DES_LENGTH) - 2;
                ScalerUsbU2HostGetBufferBulkData(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0x02, &g_stUsbU2HostDeviceInfo.pucManufacturerName[0], g_stUsbU2HostDeviceInfo.ucManufacturerNameSize);

                DebugMessageU2HostEHCI("[Data] Manufacturer Name Size =", g_stUsbU2HostDeviceInfo.ucManufacturerNameSize);
                for(ucValueTemp1 = 0; ucValueTemp1 < g_stUsbU2HostDeviceInfo.ucManufacturerNameSize; ucValueTemp1++)
                {
                    DebugMessageU2HostEHCI("[Data] Manufacturer Name Content", g_stUsbU2HostDeviceInfo.pucManufacturerName[ucValueTemp1]);
                }

                if(g_stUsbU2HostDeviceInfo.ucProductIndex != 0x00)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_PRODUCT_NAME);
                }
                else if(g_stUsbU2HostDeviceInfo.ucSerialNumberIndex != 0x00)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_SERIAL_NUMBER);
                }
                else
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                }

                break;

            case _U2HOST_ENUM_STATE_GET_PRODUCT_NAME:

                g_stUsbU2HostDeviceInfo.ucProductNameSize = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_STRING_DES_LENGTH) - 2;
                ScalerUsbU2HostGetBufferBulkData(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0x02, &g_stUsbU2HostDeviceInfo.pucProductName[0], g_stUsbU2HostDeviceInfo.ucProductNameSize);

                DebugMessageU2HostEHCI("[Data] Product Name Size =", g_stUsbU2HostDeviceInfo.ucProductNameSize);
                for(ucValueTemp1 = 0; ucValueTemp1 < g_stUsbU2HostDeviceInfo.ucProductNameSize; ucValueTemp1++)
                {
                    DebugMessageU2HostEHCI("[Data] Product Name Content", g_stUsbU2HostDeviceInfo.pucProductName[ucValueTemp1]);
                }

                if(g_stUsbU2HostDeviceInfo.ucSerialNumberIndex != 0x00)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_SERIAL_NUMBER);
                }
                else
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                }

                break;

            case _U2HOST_ENUM_STATE_GET_SERIAL_NUMBER:

                g_stUsbU2HostDeviceInfo.ucSerialNumberSize = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_STRING_DES_LENGTH) - 2;
                ScalerUsbU2HostGetBufferBulkData(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0x02, &g_stUsbU2HostDeviceInfo.pucSerialNumber[0], g_stUsbU2HostDeviceInfo.ucSerialNumberSize);

                DebugMessageU2HostEHCI("[Data] Serial Number Size =", g_stUsbU2HostDeviceInfo.ucSerialNumberSize);

                for(ucValueTemp1 = 0; ucValueTemp1 < g_stUsbU2HostDeviceInfo.ucSerialNumberSize; ucValueTemp1++)
                {
                    DebugMessageU2HostEHCI("[Data] Serial Number Content", g_stUsbU2HostDeviceInfo.pucSerialNumber[ucValueTemp1]);
                }

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);

                break;

            case _U2HOST_ENUM_STATE_SET_CONFIGURATION:

                DebugMessageU2HostEHCI("[Data] Set Configuration Finish", 0);

                if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_MASS_STORAGE)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_MAX_LUN);
                }
                else
                {
                    // undefined
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                }

                break;

            case _U2HOST_ENUM_STATE_GET_MAX_LUN:

                g_stUsbU2HostStorageDeviceInfo.ucMaxLun = ScalerUsbU2HostGetBufferField(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0x01);

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_FINISH);

                // Current FW flow will access only Lun 0 even if MaxLun > 0
                if(g_stUsbU2HostStorageDeviceInfo.ucMaxLun != 0)
                {
                    DebugMessageU2HostEHCI("[Data] Warning: Max Lun != 0", g_stUsbU2HostStorageDeviceInfo.ucMaxLun);
                }

                break;

            case _U2HOST_ENUM_STATE_ABORT:

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_FINISH);
                DebugMessageU2HostEHCI("[Data] Enum Abort switch to Finish =", 0);

                break;

            case _U2HOST_ENUM_STATE_FINISH:

                if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_MASS_STORAGE)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);

                    SET_U2HOST_COMMUNICATE_STATE(_U2HOST_COMMUNICATE_STATE_BULK_TRANS_OPERATION);

                    SET_U2HOST_BULK_SCSI_STATE(_U2HOST_ADD_BULK_READ_QH);

                    DebugMessageU2HostEHCI("[Data] Enum Finish switch to None", 0);
                    DebugMessageU2HostEHCI("[Data] Commu state switch Bulk&Add Bulk Read QH", 0);
                }
                else
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);
                }

                break;

            default:

                break;
        }
#endif // Endif #if(_USB2_HOST_EHCI_SUPPORT == _ON)
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        switch(GET_U2HOST_ENUM_STATE())
        {
            case _U2HOST_ENUM_STATE_ADD_CTRL_QH:

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_ADDRESS);
                break;

            case _U2HOST_ENUM_STATE_SET_ADDRESS:

                // Set Device Address to Control Endpoint
                ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
                DebugMessageU2HostOHCI("[Data] Set Address", GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR);

                break;

            case _U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR:

                ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0x00, pucEnum32ByteTmp, 0x02);
                ucCurDesLen = pucEnum32ByteTmp[0];
                ucCurDesType = pucEnum32ByteTmp[1];
                ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);

                if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_DEVICE)
                {
                    DebugMessageU2HostOHCI("[OHCI][Enum][Err] GetDeviceDes: bDescriptorType != Deivce", ucCurDesType);
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                    return;
                }

                // the 1st_proc of Device Des. get only 8 bytes, for least MPS0 = 8 bytes (otherwise, a case of DataOverrun/DataUnderrun occurs in ED ConditionCode)
                if(GET_U2HOST_SECOND_PROC_STATUS() == _FALSE)
                {
                    SET_U2HOST_SECOND_PROC_STATUS();

                    g_stUsbU2HostDeviceInfo.ucMaxPacketSize0 = pucEnum32ByteTmp[7];
                    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_OHCI_ED_D00_B10_MPS, g_stUsbU2HostDeviceInfo.ucMaxPacketSize0);

                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR);
                }
                else
                {
                    CLR_U2HOST_SECOND_PROC_STATUS();

                    ScalerUsbU2HostGetDeviceDesInfo(pucEnum32ByteTmp);

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
                    // Check if Device == Konica Minolta: CA410
                    if((g_stUsbU2HostDeviceInfo.usVendorID == _U2HOST_VID_CA410) && (g_stUsbU2HostDeviceInfo.usProductID == _U2HOST_PID_CA410))
                    {
                        SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_CDC_CA410);
                    }
                    // Check if Device == Xrite: i1 Display Pro
                    else if((g_stUsbU2HostDeviceInfo.usVendorID == _U2HOST_VID_XRITE) && ((g_stUsbU2HostDeviceInfo.usProductID == _U2HOST_PID_XRITE) || (g_stUsbU2HostDeviceInfo.usProductID == _U2HOST_PID_XRITE2)))
                    {
                        SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_HID_XRITE);
                    }
#endif

                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_CONFIG_DESCRIPTOR);
                }
                break;

            case _U2HOST_ENUM_STATE_GET_CONFIG_DESCRIPTOR:

                ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0x00, pucEnum32ByteTmp, 0x02);
                ucCurDesLen = pucEnum32ByteTmp[0];
                ucCurDesType = pucEnum32ByteTmp[1];

                if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_CONFIG)
                {
                    DebugMessageU2HostOHCI("[OHCI][Enum][Err] GetConfigDes: bDescriptorType != Config", ucCurDesType);
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                    return;
                }

                ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                ScalerUsbU2HostGetConfigDesInfo(pucEnum32ByteTmp);

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_OTHER_DESCRIPTOR);

                break;

            case _U2HOST_ENUM_STATE_GET_OTHER_DESCRIPTOR:

                // Make sure received data is stored in OHCI Buffer
                ScalerTimerDelayXms(3);

                //====== (1) Get 1st (Config) Descriptor ======//
                usCurByteOffset = 0;
                ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                ucCurDesType = pucEnum32ByteTmp[1];

                // the 1st Descriptor should be Config. Des.
                if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_CONFIG)
                {
                    DebugMessageU2HostOHCI("[OHCI][Enum][Err] GetOtherDes: 1st Des. != Config", ucCurDesType);
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                    return;
                }

                //====== (2) Enter CDC / HID Flow ======//

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
                if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_CDC_CA410)
                {
                    // CDC - 1: Get Interface Association Des. (offset = 9)
                    usCurByteOffset = 0x09;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, _U2HOST_ENUM_DES_LEN_INTF_ASOC);
                    ucCurDesType = pucEnum32ByteTmp[1];

                    if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_INTF_ASOC)
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] CDC GetIntfAsocDes1: bDescriptorType != Intf. Asoc.", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    ScalerUsbU2HostGetIntfAsocDesInfo(pucEnum32ByteTmp);

                    // CDC - 2 - 1: Get Comm. Control Interface Des. (offset = 17, known offset from log)
                    usCurByteOffset = 0x11;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, _U2HOST_ENUM_DES_LEN_INTF);
                    ScalerUsbU2HostGetIntfDesInfo(0, pucEnum32ByteTmp);

                    // Check if CDC Class / SubClass / Protocol field as expected
                    if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceClass == 0x02)
                    {
                        SET_U2HOST_OHCI_1ST_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_CDC_CTRL);
                    }
                    else
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] CDC Comm. Control Interface Not found", pucEnum32ByteTmp[1]);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    // CDC - 2 - 2: Get Comm. Control Endpt Des. (offset = 45, known offset from log)
                    usCurByteOffset = 0x2D;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, _U2HOST_ENUM_DES_LEN_ENDPT);
                    ucCurDesType = pucEnum32ByteTmp[1];

                    if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_ENDPT)
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] CDC GetEndptDes1: bDescriptorType != Endpt", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    ScalerUsbU2HostGetEndptDesInfo(0, pucEnum32ByteTmp);

                    // CDC - 3 - 1: Get Comm. Data Interface Des. (offset = 52, known offset from log)
                    usCurByteOffset = 0x34;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, _U2HOST_ENUM_DES_LEN_INTF);
                    ScalerUsbU2HostGetIntfDesInfo(1, pucEnum32ByteTmp);

                    // Check if CDC Class / SubClass / Protocol field as expected
                    if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceClass == 0x02)
                    {
                        SET_U2HOST_OHCI_1ST_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_CDC_DATA);
                    }
                    else
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] CDC Comm. Data Interface Not found", pucEnum32ByteTmp[1]);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    // CDC - 3 - 2: Get Comm. Data Endpt1 (Bulk Out) Des. (offset = 61, known offset from log)
                    usCurByteOffset = 0x3D;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, _U2HOST_ENUM_DES_LEN_ENDPT);
                    ucCurDesType = pucEnum32ByteTmp[1];

                    ScalerUsbU2HostGetEndptDesInfo(1, pucEnum32ByteTmp);
                    SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress);
                    SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize);

                    if((ucCurDesType != _U2HOST_ENUM_DES_TYPE_ENDPT) || ((g_pstUsbU2HostEndptDesInfo[1].ucEndpointAddress & _BIT7) != 0x00))
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] CDC Bulk Out Endpt", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    // CDC - 3 - 3: Get Comm. Control Endpt1 (Bulk In) Des. (offset = 68, known offset from log)
                    usCurByteOffset = 0x44;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, _U2HOST_ENUM_DES_LEN_ENDPT);
                    ucCurDesType = pucEnum32ByteTmp[1];

                    ScalerUsbU2HostGetEndptDesInfo(2, pucEnum32ByteTmp);
                    SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[2].ucEndpointAddress);
                    SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX, g_pstUsbU2HostEndptDesInfo[2].usMaxPacketSize);

                    if((ucCurDesType != _U2HOST_ENUM_DES_TYPE_ENDPT) || ((g_pstUsbU2HostEndptDesInfo[2].ucEndpointAddress & _BIT7) != _BIT7))
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] CDC Bulk In Endpt", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                }
                else
#endif
                {
                    // HID - 1: Get 1st Interface Des. (offset = 9)
                    usCurByteOffset += _U2HOST_ENUM_DES_LEN_CONFIG;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                    ucCurDesLen = pucEnum32ByteTmp[0];
                    ucCurDesType = pucEnum32ByteTmp[1];

                    if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_INTF)
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetIntfDes1: bDescriptorType != Intf", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                    ScalerUsbU2HostGetIntfDesInfo(0, pucEnum32ByteTmp);

                    // Check if Interface1 is a Supported HID Class / SubClass / Protocol (Keyboard / Mouse)
                    if((g_pstUsbU2HostIntfDesInfo[0].ucInterfaceClass == 0x03) && (g_pstUsbU2HostIntfDesInfo[0].ucInterfaceSubClass == 0x01))
                    {
                        if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceProtocol == 0x01)
                        {
                            SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_HID);
                            SET_U2HOST_OHCI_1ST_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_KEYBOARD);
                        }
                        else if(g_pstUsbU2HostIntfDesInfo[0].ucInterfaceProtocol == 0x02)
                        {
                            SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_HID);
                            SET_U2HOST_OHCI_1ST_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_MOUSE);
                        }
                    }

                    // HID - 2: Get 1st HID Des. (offset = 18)
                    usCurByteOffset += _U2HOST_ENUM_DES_LEN_INTF;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                    ucCurDesLen = pucEnum32ByteTmp[0];
                    ucCurDesType = pucEnum32ByteTmp[1];

                    if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_HID)
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetHIDDes1: bDescriptorType != HID", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                    ScalerUsbU2HostGetHIDDesInfo(0, pucEnum32ByteTmp);

                    // HID - 3: Get 1st Endpt Des. (offset = 27)
                    usCurByteOffset += _U2HOST_ENUM_DES_LEN_HID;
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                    ucCurDesLen = pucEnum32ByteTmp[0];
                    ucCurDesType = pucEnum32ByteTmp[1];

                    if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_ENDPT)
                    {
                        DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetEndptDes1: bDescriptorType != Endpt", ucCurDesType);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                        return;
                    }

                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                    ScalerUsbU2HostGetEndptDesInfo(0, pucEnum32ByteTmp);

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
                    if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_HID_XRITE)
                    {
                        // HID - 4: Get 2nd Endpt Des. (offset = 34)
                        usCurByteOffset += _U2HOST_ENUM_DES_LEN_ENDPT;
                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                        ucCurDesLen = pucEnum32ByteTmp[0];
                        ucCurDesType = pucEnum32ByteTmp[1];

                        if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_ENDPT)
                        {
                            DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetEndptDes2: bDescriptorType != Endpt", ucCurDesType);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }

                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                        ScalerUsbU2HostGetEndptDesInfo(1, pucEnum32ByteTmp);

                        DebugMessageU2HostOHCI("[OHCI][Enum] HID Xrite", ucCurDesType);
                    }
#endif

                    if(g_stUsbU2HostConfigDesInfo.ucNumInterface == 1)
                    {
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                    }
                    else
                    {
                        // get Intf2 / HID2 / Endpt2

                        // HID - 1: Get 2nd Interface Des. (offset = 34)
                        usCurByteOffset += _U2HOST_ENUM_DES_LEN_ENDPT;
                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                        ucCurDesLen = pucEnum32ByteTmp[0];
                        ucCurDesType = pucEnum32ByteTmp[1];

                        if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_INTF)
                        {
                            DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetIntfDes2: bDescriptorType != Intf", ucCurDesType);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }

                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                        ScalerUsbU2HostGetIntfDesInfo(1, pucEnum32ByteTmp);

                        // Check if Interface2 is a Supported HID Class / SubClass / Protocol (Keyboard / Mouse)
                        if((g_pstUsbU2HostIntfDesInfo[1].ucInterfaceClass == 0x03) && (g_pstUsbU2HostIntfDesInfo[1].ucInterfaceSubClass == 0x01))
                        {
                            if(g_pstUsbU2HostIntfDesInfo[1].ucInterfaceProtocol == 0x01)
                            {
                                SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_HID);
                                SET_U2HOST_OHCI_2ND_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_KEYBOARD);
                            }
                            else if(g_pstUsbU2HostIntfDesInfo[1].ucInterfaceProtocol == 0x02)
                            {
                                SET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX, _U2HOST_DEVICE_HID);
                                SET_U2HOST_OHCI_2ND_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_MOUSE);
                            }
                        }

                        // HID - 2: Get 2nd HID Des. (offset = 43)
                        usCurByteOffset += _U2HOST_ENUM_DES_LEN_INTF;
                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                        ucCurDesLen = pucEnum32ByteTmp[0];
                        ucCurDesType = pucEnum32ByteTmp[1];

                        if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_HID)
                        {
                            DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetHIDDes2: bDescriptorType != HID", ucCurDesType);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }

                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                        ScalerUsbU2HostGetHIDDesInfo(1, pucEnum32ByteTmp);

                        // HID - 3: Get 2nd Endpt Des. (offset = 52)
                        usCurByteOffset += _U2HOST_ENUM_DES_LEN_HID;
                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, 0x02);
                        ucCurDesLen = pucEnum32ByteTmp[0];
                        ucCurDesType = pucEnum32ByteTmp[1];

                        if(ucCurDesType != _U2HOST_ENUM_DES_TYPE_ENDPT)
                        {
                            DebugMessageU2HostOHCI("[OHCI][Enum][Err] HID GetEndptDes2: bDescriptorType != Endpt", ucCurDesType);
                            SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                            return;
                        }

                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, usCurByteOffset, pucEnum32ByteTmp, ucCurDesLen);
                        ScalerUsbU2HostGetEndptDesInfo(1, pucEnum32ByteTmp);

                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_CONFIGURATION);
                    }
                }

                break;

            case _U2HOST_ENUM_STATE_GET_LANGUAGE_ID:
                // TBD, Not for the time being
                break;

            case _U2HOST_ENUM_STATE_GET_MANUFACTURE_NAME:
                // TBD, Not for the time being
                break;

            case _U2HOST_ENUM_STATE_GET_PRODUCT_NAME:
                // TBD, Not for the time being
                break;

            case _U2HOST_ENUM_STATE_GET_SERIAL_NUMBER:
                // TBD, Not for the time being
                break;

            case _U2HOST_ENUM_STATE_SET_CONFIGURATION:

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
                if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_CDC_CA410)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_LINE_CODING);
                }
                else if(GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_HID_XRITE)
                {
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_FINISH);
                }
                else
#endif
                // HID Device Case
                {
                    if(g_stUsbU2HostConfigDesInfo.ucNumInterface > 0x01)
                    {
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_IDLE);
                    }
                    else
                    {
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_HID_REPORT);
                    }
                }

                break;

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
            case _U2HOST_ENUM_STATE_GET_LINE_CODING:

                ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0x00, pucEnum32ByteTmp, _U2HOST_ENUM_GET_LINE_CODE);
                ScalerUsbU2HostGetLineCodeInfo(pucEnum32ByteTmp);

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_FINISH);

                break;

            case _U2HOST_ENUM_STATE_SET_CONTROL_LINE_STATE:

                // un-used state for CA-410

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_LINE_CODING);

                break;

            case _U2HOST_ENUM_STATE_SET_LINE_CODING:

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_LINE_CODING);

                break;
#endif
            case _U2HOST_ENUM_STATE_SET_IDLE:

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_GET_HID_REPORT);

                break;

            case _U2HOST_ENUM_STATE_GET_HID_REPORT:

                if(g_stUsbU2HostConfigDesInfo.ucNumInterface > 0x01)
                {
                    if(GET_U2HOST_SEC_REPORT_DESC() == _FALSE)
                    {
                        SET_U2HOST_SEC_REPORT_DESC();

                        // Save 1st interface HID Descriptor to g_pstUsbU2HostHIDDesInfo[0].pucHIDReport[]
                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0x00, g_pstUsbU2HostHIDDesInfo[0].pucHIDReport, g_pstUsbU2HostHIDDesInfo[0].usHIDReportLength);
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_SET_IDLE);
                    }
                    else
                    {
                        CLR_U2HOST_SEC_REPORT_DESC();

                        // Save 2nd interface HID Descriptor to g_pstUsbU2HostHIDDesInfo[1].pucHIDReport[]
                        ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0x00, g_pstUsbU2HostHIDDesInfo[1].pucHIDReport, g_pstUsbU2HostHIDDesInfo[1].usHIDReportLength);

                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);

                        SET_U2HOST_COMMUNICATE_STATE(_U2HOST_COMMUNICATE_STATE_INT_TRANS_OPERATION);

                        DebugMessageU2HostOHCI("[Data] 2HID Ctrl Enum Finish", 0);
                    }
                }
                else // 1 Interface
                {
                    ScalerUsbU2HostGetBufferBulkData(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0x00, g_pstUsbU2HostHIDDesInfo[0].pucHIDReport, g_pstUsbU2HostHIDDesInfo[0].usHIDReportLength);

                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);

                    SET_U2HOST_COMMUNICATE_STATE(_U2HOST_COMMUNICATE_STATE_INT_TRANS_OPERATION);

                    DebugMessageU2HostOHCI("[Data] 1HID Ctrl Enum Finish", 0);
                }

                // Meaning Get Report finished
                if(GET_U2HOST_ENUM_STATE() == _U2HOST_ENUM_STATE_NONE)
                {
                    // Get 1st Interface HID Report
                    if(GET_U2HOST_OHCI_1ST_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_MOUSE)
                    {
                        // For User Use,TBD - MouseHIDReport Info Mapping to g_pstUsbU2HostHIDDesInfo[0].pucHIDReport[];

                        /*
                        // For example
                        for(i = 0; i < g_pstUsbU2HostHIDDesInfo[0].usHIDReportLength; i++)
                        {
                            g_ucMouseHIDReport[i] = g_pstUsbU2HostHIDDesInfo[0].pucHIDReport[i];
                        }
                        */
                    }
                    else if(GET_U2HOST_OHCI_1ST_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_KEYBOARD)
                    {
                        // For User Use,TBD - KeyBoardHIDReport Info Mapping to g_pstUsbU2HostHIDDesInfo[0].pucHIDReport[];

                        /*
                        // For example
                        for(i = 0; i < g_pstUsbU2HostHIDDesInfo[0].usHIDReportLength; i++)
                        {
                            g_ucKeyBoardHIDReport[i] = g_pstUsbU2HostHIDDesInfo[0].pucHIDReport[i];
                        }
                        */
                    }
                    else
                    {
                        // Not define
                    }

                    // Get 2nd Interface HID Report
                    if(GET_U2HOST_OHCI_2ND_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_MOUSE)
                    {
                        // For User Use,TBD - MouseHIDReport Info Mapping to g_pstUsbU2HostHIDDesInfo[1].pucHIDReport;

                        /*
                        // For example
                        for(i = 0; i < g_pstUsbU2HostHIDDesInfo[1].usHIDReportLength; i++)
                        {
                            g_ucMouseHIDReport[i] = g_pstUsbU2HostHIDDesInfo[1].pucHIDReport[i];
                        }
                        */
                    }
                    else if(GET_U2HOST_OHCI_2ND_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_KEYBOARD)
                    {
                        // For User Use,TBD - KeyBoardHIDReport Info Mapping to g_pstUsbU2HostHIDDesInfo[1].pucHIDReport;

                        /*
                        // For example
                        for(i = 0; i < g_pstUsbU2HostHIDDesInfo[1].usHIDReportLength; i++)
                        {
                            g_ucKeyBoardHIDReport[i] = g_pstUsbU2HostHIDDesInfo[1].pucHIDReport[i];
                        }
                        */
                    }
                    else
                    {
                        // Not define
                    }
                }

                break;

            case _U2HOST_ENUM_STATE_ABORT:

                break;

            case _U2HOST_ENUM_STATE_FINISH:

                // Set only DevIndex[0] to 1, since only 1 device at a time in KCPU application
                g_stUsbU2HostDevConnectInfo.ucValidDevIndex = 0x01;
                g_stUsbU2HostDevConnectInfo.pusUsb2HostValidDevVID[0] = g_stUsbU2HostDeviceInfo.usVendorID;
                g_stUsbU2HostDevConnectInfo.pusUsb2HostValidDevPID[0] = g_stUsbU2HostDeviceInfo.usProductID;

                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_NONE);
                DebugMessageU2HostOHCI("[OHCI][ENUM STATE] FINISH -> NONE", 0);

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
                if((GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_CDC_CA410) || (GET_U2HOST_DEVICE_TYPE(_U2HOST_DEVICE_ATTACH_INDEX) == _U2HOST_DEVICE_HID_XRITE))
                {
                    SET_U2HOST_COMMUNICATE_STATE(_U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION);
                    DebugMessageU2HostOHCI("[OHCI][COMM STATE] ENUM -> COLOR ANALYZER", 0);

                    SET_U2HOST_COLOR_STATE(_U2HOST_COLOR_IDLE);
                    DebugMessageU2HostOHCI("[OHCI][COLOR STATE] NONE -> IDLE", 0);
                }
#endif
                break;

            default:

                break;
        }
#endif // Endif #if(_USB2_HOST_OHCI_SUPPORT == _ON)
    }
}


//----------------------------------------------------------------------------------------------------
// Description  : U2Host Check Device Connect or not
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostConnectHandler(EnumUsbU2HostOwner enumMode)
{
    // Check and Update Connect Status
    ScalerUsbU2HostConnectCheck(enumMode);

    // Set in U2HostPortOwnerSwitch(), default OWNER == EHCI
    if(enumMode == _U2HOST_OWNER_EHCI)
    {
        if(GET_U2HOST_CONNECT_STATUS() == _U2HOST_CONNECT_INSERT_DEVICE)
        {
            // Do Remove Flow when Re-insertion (insert->remove->insert) occurs during Communication
            if(GET_U2HOST_MODE_STATE() == _U2HOST_MODE_STATE_COMMUNICATION)
            {
                SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_ROOT_HUB_REMOVE_DEVICE);
                SET_U2HOST_MODE_STATE_CHANGE_FLAG();
                DebugMessageU2Host("[EHCI] Connect Re-insert", 0);
                DebugMessageU2Host("[Mode State] -> ROOT_HUB_REMOVE_DEVICE", 0);

                // Reset Mac for Device compatibility
                ScalerUsbU2HostMacReset();
                return;
            }
            SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_EHCI_RH_PORT_ENABLE);
            SET_U2HOST_MODE_STATE_CHANGE_FLAG();
            DebugMessageU2Host("[EHCI] Connect Insert", 0);
            DebugMessageU2Host("[Mode State] -> EHCI_RH_PORT_ENABLE", 0);

            // Reset Mac for Device compatibility
            ScalerUsbU2HostMacReset();
        }
        else if(GET_U2HOST_CONNECT_STATUS() == _U2HOST_CONNECT_REMOVE_DEVICE)
        {
            SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_ROOT_HUB_REMOVE_DEVICE);
            SET_U2HOST_MODE_STATE_CHANGE_FLAG();
            DebugMessageU2Host("[EHCI] Connect Remove", 0);
            DebugMessageU2Host("[Mode State] -> ROOT_HUB_REMOVE_DEVICE", 0);
        }
        else
        {
            // No Action needed in _U2HOST_CONNECT_NO_CHANGE / _U2HOST_CONNECT_STATUS_NONE
        }
    }
    // Chg to Owner OHCI in ModeState: OHCI_POWER_ON
    else if(enumMode == _U2HOST_OWNER_OHCI)
    {
        if(GET_U2HOST_CONNECT_STATUS() == _U2HOST_CONNECT_INSERT_DEVICE)
        {
            // Do Remove Flow when Re-insertion (insert->remove->insert) occurs during Communication
            if(GET_U2HOST_MODE_STATE() == _U2HOST_MODE_STATE_COMMUNICATION)
            {
                // Note: in ROOT_HUB_REMOVE_DEVICE state, OWNER will be set back to EHCI
                SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_ROOT_HUB_REMOVE_DEVICE);
                SET_U2HOST_MODE_STATE_CHANGE_FLAG();
                DebugMessageU2Host("[OHCI] Connect Re-insert", 0);
                DebugMessageU2Host("[Mode State] -> ROOT_HUB_REMOVE_DEVICE", 0);
                return;
            }

            SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_OHCI_RH_PORT_ENABLE);
            SET_U2HOST_MODE_STATE_CHANGE_FLAG();
            DebugMessageU2Host("[OHCI] Connect Insert", 0);
            DebugMessageU2Host("[Mode State] -> OHCI_RH_PORT_ENABLE", 0);
        }
        else if(GET_U2HOST_CONNECT_STATUS() == _U2HOST_CONNECT_REMOVE_DEVICE)
        {
            // Note: in ROOT_HUB_REMOVE_DEVICE state, OWNER will be set back to EHCI
            SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_ROOT_HUB_REMOVE_DEVICE);
            SET_U2HOST_MODE_STATE_CHANGE_FLAG();
            DebugMessageU2Host("[OHCI] Connect Remove", 0);
            DebugMessageU2Host("[Mode State] -> ROOT_HUB_REMOVE_DEVICE", 0);
        }
        else
        {
            // No Action needed in _U2HOST_CONNECT_NO_CHANGE / _U2HOST_CONNECT_STATUS_NONE
        }
    }
    else
    {
        DebugMessageU2Host("[Connect Handler] U2Host Owner Not define !!!", enumMode);
    }
}

//--------------------------------------------------
// Description  : Get Device Descriptor Info.
// Input Value  : whole Device Descriptor Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetDeviceDesInfo(BYTE *pucData)
{
    g_stUsbU2HostDeviceInfo.ucDeviceDesLen = pucData[0];

    g_stUsbU2HostDeviceInfo.ucDeviceClass = pucData[4];
    g_stUsbU2HostDeviceInfo.ucDeviceSubClass = pucData[5];
    g_stUsbU2HostDeviceInfo.ucDeviceProtocol = pucData[6];

    // the ucMaxPacketSize0 is already updated in 1st_proc of Device Des.
    // g_stUsbU2HostDeviceInfo.ucMaxPacketSize0 = pucData[7];

    g_stUsbU2HostDeviceInfo.usVendorID = TO_WORD(pucData[9], pucData[8]);
    g_stUsbU2HostDeviceInfo.usProductID = TO_WORD(pucData[11], pucData[10]);
    g_stUsbU2HostDeviceInfo.usBcdDevice = TO_WORD(pucData[13], pucData[12]);
    g_stUsbU2HostDeviceInfo.ucManufacturerIndex = pucData[14];
    g_stUsbU2HostDeviceInfo.ucProductIndex = pucData[15];
    g_stUsbU2HostDeviceInfo.ucSerialNumberIndex = pucData[16];

    if(g_stUsbU2HostDeviceInfo.ucDeviceDesLen != _U2HOST_ENUM_DES_LEN_DEVICE)
    {
        DebugMessageU2Host("[Enum][Device] Warning: Device Des Len != 0x12", g_stUsbU2HostDeviceInfo.ucDeviceClass);
    }
    DebugMessageU2Host("[Enum][Device] ucDeviceClass", g_stUsbU2HostDeviceInfo.ucDeviceClass);
    DebugMessageU2Host("[Enum][Device] ucDeviceSubClass", g_stUsbU2HostDeviceInfo.ucDeviceSubClass);
    DebugMessageU2Host("[Enum][Device] usProductID", g_stUsbU2HostDeviceInfo.usProductID);
}

//--------------------------------------------------
// Description  : Get Config. Descriptor Info.
// Input Value  : whole Config. Descriptor Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetConfigDesInfo(BYTE *pucData)
{
    g_stUsbU2HostConfigDesInfo.usTotalLength = TO_WORD(pucData[3], pucData[2]);
    g_stUsbU2HostConfigDesInfo.ucNumInterface = pucData[4];
    g_stUsbU2HostConfigDesInfo.ucConfigValue = pucData[5];
    g_stUsbU2HostConfigDesInfo.ucAttributes = pucData[7];

    if(pucData[0] != _U2HOST_ENUM_DES_LEN_CONFIG)
    {
        DebugMessageU2Host("[Enum][Config] Warning: Config Des Len != 0x09", pucData[0]);
    }
    if(g_stUsbU2HostConfigDesInfo.ucNumInterface > 2)
    {
        DebugMessageU2Host("[Enum][Config] Warning: NumInterface > 2", g_stUsbU2HostConfigDesInfo.ucNumInterface);
    }
    DebugMessageU2Host("[Enum][Config] usTotalLength", g_stUsbU2HostConfigDesInfo.usTotalLength);
}

//--------------------------------------------------
// Description  : Get Interface Association Descriptor Info.
// Input Value  : whole Interface Association Descriptor Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetIntfAsocDesInfo(BYTE *pucData)
{
    g_stUsbU2HostIntfAsocDesInfo.ucFirstInterface = pucData[2];
    g_stUsbU2HostIntfAsocDesInfo.ucInterfaceCnt = pucData[3];
    g_stUsbU2HostIntfAsocDesInfo.ucFuncClass = pucData[4];
    g_stUsbU2HostIntfAsocDesInfo.ucFuncSubClass = pucData[5];
    g_stUsbU2HostIntfAsocDesInfo.ucFuncProtocol = pucData[6];

    if(pucData[0] != _U2HOST_ENUM_DES_LEN_INTF_ASOC)
    {
        DebugMessageU2Host("[Enum][IntfAsoc] Warning: Intf Asoc Des Len != 0x08", pucData[0]);
    }
}

//--------------------------------------------------
// Description  : Get Interface Descriptor Info.
// Input Value  : Interface Index, whole Interface Descriptor Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetIntfDesInfo(BYTE ucIntfIdx, BYTE *pucData)
{
    g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucInterfaceNum = pucData[2];
    g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucNumEndpoint = pucData[4];
    g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucInterfaceClass = pucData[5];
    g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucInterfaceSubClass = pucData[6];
    g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucInterfaceProtocol = pucData[7];

    if(pucData[0] != _U2HOST_ENUM_DES_LEN_INTF)
    {
        DebugMessageU2Host("[Enum][Intf] Warning: Intf Des Len != 0x09", pucData[0]);
    }
    if(g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucNumEndpoint > 2)
    {
        DebugMessageU2Host("[Enum][Intf] Warning: ucNumEndpoint > 2", g_pstUsbU2HostIntfDesInfo[ucIntfIdx].ucNumEndpoint);
    }
}

//--------------------------------------------------
// Description  : Get Endpoint Descriptor Info.
// Input Value  : Endpoint Index, whole Endpoint Descriptor Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetEndptDesInfo(BYTE ucEndptIdx, BYTE *pucData)
{
    g_pstUsbU2HostEndptDesInfo[ucEndptIdx].ucEndpointAddress = pucData[2];
    g_pstUsbU2HostEndptDesInfo[ucEndptIdx].ucAttributes = pucData[3];
    g_pstUsbU2HostEndptDesInfo[ucEndptIdx].usMaxPacketSize = pucData[4];
    g_pstUsbU2HostEndptDesInfo[ucEndptIdx].ucInterval = pucData[5];

    if(pucData[0] != _U2HOST_ENUM_DES_LEN_ENDPT)
    {
        DebugMessageU2Host("[Enum][Endpt] Warning: Endpt Des Len != 0x07", pucData[0]);
    }
}

//----------------------------------------------------------------------------------------------------
// USB Main Flow -- Sub Function -- Initial Function
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// Description  : USB initial device address
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostCurOwerInitDeviceAddr(void)
{
    BYTE ucValueTemp = 0;

    for(ucValueTemp = 0; ucValueTemp < _U2HOST_DEVICE_NUM; ucValueTemp++)
    {
        SET_U2HOST_DEVICE_ADDRESS(ucValueTemp, _U2HOST_DEVICE_ADDRESS_START + ucValueTemp);
    }
}

//****************************************************************************************************
// USB Enumeration Function
//****************************************************************************************************
//----------------------------------------------------------------------------------------------------
// Description  : USB Add Control Queue-Head Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostAddCtrlQH(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    SET_U2HOST_DEVICE_SPEED(ucDeviceNo, g_ucUsbU2HostDeviceSpeed);

    DebugMessageU2Host("[Enum] Add Ctrl Queue", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        // Re-assign CTRL QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo]);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B07_ENDPT, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0B_PID_CODE, 0);   // Get direction from TD
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(ucDeviceNo));   // Must set it before the fisrt process of Enumeration
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0F_FORMAT, 0);   // This is not Isochronous Endpoint
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B10_MPS, 0x08);

        // Re-assign Control Head ED Address
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_120_OHCI_HCCONTROLHEAD_ED_0, tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo]);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Set Device Address Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------

void ScalerUsbU2HostSetAddress(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE pucUsbCtrlCmd[8] =
    {
        0x00,               // Data transfer direction : host-to-device
        0x05,               // Set Address
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00
    };

    // update device address info
    pucUsbCtrlCmd[2] = GET_U2HOST_DEVICE_ADDRESS(ucDeviceNo);
    DebugMessageU2Host("[Enum] Set Address", GET_U2HOST_DEVICE_ADDRESS(ucDeviceNo));

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x00);   // Reveive Data Size = 0-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);          // Set Command using 2*qTD only (Setup & IN Token)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);                 // Issue interrupt for last qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);   // Receive empty packet
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get Device Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetDeviceDescriptor(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = 0x00;
    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // bmRequestType, bit[7]: Data transfer direction = device-to-host
        0x06,               // bRequest: GET_DESCRIPTOR
        0x00, 0x01,         // wValue: DescriptorIndex + DescriptorType(Device)
        0x00, 0x00,         // wIndex
        0x00, 0x00          // wLength
    };

    if(GET_U2HOST_SECOND_PROC_STATUS() == _FALSE)
    {
        ucUsbReceiveDataLen = 0x08;
        DebugMessageU2Host("[Enum] Get Device Descriptor (1st proc)", 0);
    }
    else
    {
        ucUsbReceiveDataLen = _U2HOST_ENUM_DES_LEN_DEVICE;
        DebugMessageU2Host("[Enum] Get Device Descriptor (2nd proc)", 0);
    }

    // Update wLength
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;


    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH


        if((GET_U2HOST_CTS_EN_STATUS() == _TRUE) && (GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_SIGN_GET_DEV_DESC))
        {
            ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);

            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT2) == _BIT2)
            {
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0

                ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT6);

                // Wait until Bit clr by tester manually control
                while((ScalerGetByte(PDF_00_USB_CTR0_REG_1) & _BIT6) != 0x00)
                {
                    DebugMessageU2HostEHCI("[CTS] SINGLE GET DEV DESC STEP - 1", 0);
                    ScalerDebug();
                }
                if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT2) == _BIT2)
                {
                    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1

                    ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT6);

                    // Wait until Bit clr by tester manually control
                    while((ScalerGetByte(PDF_00_USB_CTR0_REG_1) & _BIT6) != 0x00)
                    {
                        DebugMessageU2HostEHCI("[CTS] SINGLE GET DEV DESC STEP - 2", 0);
                        ScalerDebug();
                    }
                    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT2) == _BIT2)
                    {
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2
                    }
                    else
                    {
                        ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT5);
                        DebugMessageU2HostEHCI("[CTS] Port is not enable", 0);
                        CLR_U2HOST_TRANSFER_STATUS();
                        SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                    }
                }
                else
                {
                    ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT5);
                    DebugMessageU2HostEHCI("[CTS] Port is not enable", 0);
                    CLR_U2HOST_TRANSFER_STATUS();
                    SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
                }
            }
            else
            {
                ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT5);
                DebugMessageU2HostEHCI("[CTS] Port is not enable", 0);
                CLR_U2HOST_TRANSFER_STATUS();
                SET_U2HOST_ENUM_STATE(_U2HOST_ENUM_STATE_ABORT);
            }
        }
        else
        {
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

            ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
        }
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)

        // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
#endif // End of #if(_USB2_HOST_OHCI_SUPPORT == _ON)
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get Device Other Descriptor Process --- cai add
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetConfigDescriptor(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = _U2HOST_ENUM_DES_LEN_CONFIG;
    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // bmRequestType, bit[7]: Data transfer direction = device-to-host
        0x06,               // bRequest: GET_DESCRIPTOR
        0x00, 0x02,         // wValue: DescriptorIndex + DescriptorType(Config)
        0x00, 0x00,         // wIndex
        0x00, 0x00          // wLength
    };
    ucDeviceNo = ucDeviceNo;

    // Update wLength
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;

    DebugMessageU2Host("[Enum] Get Configuration Descriptor", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get Device Other Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetOtherDescriptor(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = g_stUsbU2HostConfigDesInfo.usTotalLength;

    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // bmRequestType, bit[7]: Data transfer direction = device-to-host
        0x06,               // bRequest: GET_DESCRIPTOR
        0x00, 0x02,         // wValue: DescriptorIndex + DescriptorType(Config)
        0x00, 0x00,         // wIndex
        0x00, 0x00          // wLength
    };

    // Update Receive Data Length
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;

    DebugMessageU2Host("[Enum] Get Configuration/Interface/Endpoint Descriptor", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get HID Device Language Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetLanguageID(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = 0x04;
    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // Data transfer direction : device-to-host
        0x06,               // Get Descriptor
        0x00, 0x03,         // Get string Descriptor
        0x00, 0x00,
        0x04, 0x00          // fixed 4byte
    };

    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;
    DebugMessageU2Host("[Enum] Get Language ID", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get HID Device Manufacture Name Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetManufactureName(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = 64;// unknow data size : set to max. buffer size

    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // Data transfer direction : device-to-host
        0x06,               // Get Descriptor
        0x00, 0x03,         // Get string Descriptor
        0x00, 0x00,
        0x40, 0x00          // Transfer Len
    };
    pucUsbCtrlCmd[2] = g_stUsbU2HostDeviceInfo.ucManufacturerIndex;
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;

    DebugMessageU2Host("[Enum] Get Manufacture Name", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get HID Device Product Name Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetProductName(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = 64;// unknow data size : set to max. buffer size

    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // Data transfer direction : device-to-host
        0x06,               // Get Descriptor
        0x00, 0x03,         // Get string Descriptor
        0x00, 0x00,
        0x40, 0x00          // Transfer Len
    };
    pucUsbCtrlCmd[2] = g_stUsbU2HostDeviceInfo.ucProductIndex;
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;
    DebugMessageU2Host("[Enum] Get Product Name", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get HID Device Serial Number Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetSerialNumber(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = 64;// unknow data size : set to max. buffer size

    BYTE pucUsbCtrlCmd[8] =
    {
        0x80,               // Data transfer direction : device-to-host
        0x06,               // Get Descriptor
        0x00, 0x03,         // Get string Descriptor
        0x00, 0x00,
        0x40, 0x00          // Transfer Len
    };
    pucUsbCtrlCmd[2] = g_stUsbU2HostDeviceInfo.ucSerialNumberIndex;
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;
    DebugMessageU2Host("[Enum] Get Serial Number", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get HID Device Serial Number Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetMaxLun(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
    BYTE ucUsbReceiveDataLen = 0x01;
    BYTE pucUsbCtrlCmd[8] =
    {
        0xA1,               // Data transfer direction : device-to-host,Type:class,Recipient:Interface
        0xFE,               // Get Descriptor
        0x00, 0x00,         // Get string Descriptor
        0x00, 0x00,
        0x01, 0x00          // Transfer Len
    };

    pucUsbCtrlCmd[4] = g_pstUsbU2HostIntfDesInfo[0].ucInterfaceNum; // Interface num
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;
#endif

    ucDeviceNo = ucDeviceNo;
    DebugMessageU2Host("[Enum] Get Max Lun", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);   // Get Command using 3*qTD

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 2

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        // Not Support
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Set Configuration Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetConfiguration(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = 0x00;// no Data stage

    BYTE pucUsbCtrlCmd[8] =
    {
        0x00,               // Data transfer direction : host-to-device
        0x09,               // Set Configuration
        0x01,               // Configuration Value
        0x00,
        0x00, 0x00,
        0x00, 0x00          // Transfer Len 0
    };

    ucUsbReceiveDataLen = ucUsbReceiveDataLen;
    pucUsbCtrlCmd[2] = g_stUsbU2HostConfigDesInfo.ucConfigValue;

    DebugMessageU2Host("[Enum] Set Configuration", g_stUsbU2HostConfigDesInfo.ucConfigValue);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, ucUsbReceiveDataLen);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1); // Issue interrupt for last qTD
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucDeviceNo], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);   // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);   // Receive empty packet
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
#endif
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Check Control Type Queue Error Status
// Input Value  : Host Controller Type : EHCI / OHCI
// Output Value : _TRUE -> Error Happened ; _FALSE -> Error ot Happened
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostChkCtrlQueueErrSts(EnumUsbU2HostOwner enumOwner)
{
    BYTE ucEnumState = 0;

    ucEnumState = GET_U2HOST_ENUM_STATE();

    if((ucEnumState & (_BIT4 | _BIT5)) == 0x00)   // Non-reply from Device
    {
        return _FALSE;   // no error
    }
    else
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        if(enumOwner == _U2HOST_OWNER_EHCI)
        {
            if(((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00) ||
               ((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x01))
            {
                if(((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00) ||
                   ((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x01))
                {
                    if((ucEnumState & (_BIT4 | _BIT5)) == 0x10)   // Set Command Type
                    {
                        return _FALSE;   // no error
                    }
                    else   // Get Command Type
                    {
                        if(((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00) ||
                           ((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x01))
                        {
                            return _FALSE;   // no error
                        }
                        else
                        {
                            DebugMessageU2HostEHCI("[Err] Ctrl Handshake Status ErrCode", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                            return _TRUE;
                        }
                    }
                }
                else
                {
                    DebugMessageU2HostEHCI("[Err] Ctrl data Status ErrCode", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                    return _TRUE;
                }
            }
            else
            {
                DebugMessageU2HostEHCI("[Err] Ctrl Setup Staus ErrCode", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                return _TRUE;
            }
        }
#endif // end of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        if(enumOwner == _U2HOST_OWNER_OHCI)
        {
            if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_ENUMERATION)
            {
                if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                {
                    if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                    {
                        if((ucEnumState & (_BIT4 | _BIT5)) == 0x10)   // Set Command Type
                        {
                            return _FALSE;   // no error
                        }
                        else   // Get Command Type
                        {
                            if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                            {
                                return _FALSE;   // no error
                            }
                            else
                            {
                                return _TRUE;
                            }
                        }
                    }
                    else
                    {
                        if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x04) // Receive stall
                        {
                            // DebugMessageU2HostOHCI("ohci ed halt bit", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B00_HALTED));

                            // clr halt bit
                            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);

                            return _FALSE;
                        }
                        return _TRUE;
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
            else if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION)
            {
                BYTE ucColorState = GET_U2HOST_COLOR_STATE();

                switch(ucColorState)
                {
                    case _U2HOST_COLOR_CONTROL_OUT:

                        if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                        {
                            return _FALSE;
                        }
                        else
                        {
                            DebugMessageU2HostOHCI("[OHCI][Err] CONTROL_OUT_TD Error", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
                            return _TRUE;
                        }

                        break;

                    case _U2HOST_COLOR_CONTROL_IN:

                        if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                        {
                            return _FALSE;
                        }
                        else
                        {
                            DebugMessageU2HostOHCI("[OHCI][Err] CONTROL_IN_TD Error", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
                            return _TRUE;
                        }

                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        }
#endif // End of #if(_USB2_HOST_OHCI_SUPPORT == _ON)

        // OHCI & EHCI Both Off - No define
        return _TRUE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Check Control Type Queue is Executed Finish or Not
// Input Value  : Host Controller Type : EHCI / OHCI
// Output Value : _TRUE -> Execute Finished ; _FALSE -> Execute not yet Finished
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostChkCtrlQueueComplete(EnumUsbU2HostOwner enumOwner)
{
    BYTE ucEnumState = 0;
    WORD usHccaDoneHead = 0;

    usHccaDoneHead = usHccaDoneHead;

    ucEnumState = GET_U2HOST_ENUM_STATE();

    if((ucEnumState & (_BIT4 | _BIT5)) == 0x00)   // Non-reply from Device
    {
        return _TRUE;   // Command Complete
    }
    else
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        if(enumOwner == _U2HOST_OWNER_EHCI)
        {
            if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
            {
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    if((ucEnumState & (_BIT4 | _BIT5)) == 0x10)   // Set Command Type
                    {
                        return _TRUE;   // Command Complete
                    }
                    else   // Get Command Type
                    {
                        if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                        {
                            return _TRUE;   // Command Complete
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    return _FALSE;
                }
            }
            else
            {
                return _FALSE;
            }
        }
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        if(enumOwner == _U2HOST_OWNER_OHCI)
        {
            usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_D21_B00_DONE_HEAD);

            while(usHccaDoneHead != 0)
            {
                if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_ENUMERATION)
                {
                    if((ucEnumState & (_BIT5 | _BIT4)) == _BIT4)   // Set Command Type
                    {
                        if(usHccaDoneHead == tUSB_OHCI_CTRL_TD_ADDR_TABLE[1])
                        {
                            return _TRUE;
                        }
                    }
                    else
                    {
                        if(usHccaDoneHead == tUSB_OHCI_CTRL_TD_ADDR_TABLE[2])
                        {
                            return _TRUE;
                        }
                    }
                }
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
                else if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION)
                {
                    BYTE ucColorState = GET_U2HOST_COLOR_STATE();

                    if(ucColorState == _U2HOST_COLOR_CONTROL_IN)
                    {
                        if(usHccaDoneHead == tUSB_OHCI_CTRL_TD_ADDR_TABLE[1])
                        {
                            return _TRUE;
                        }
                    }
                    else if(ucColorState == _U2HOST_COLOR_CONTROL_OUT)
                    {
                        if(usHccaDoneHead == tUSB_OHCI_CTRL_TD_ADDR_TABLE[2])
                        {
                            return _TRUE;
                        }
                    }
                }
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)

                usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(usHccaDoneHead, _U2HOST_OHCI_TD_D02_B04_NEXT_TD);
            }
            return _FALSE;
        }
#endif // End of #if(_USB2_HOST_OHCI_SUPPORT == _ON)

        // OHCI & EHCI Both Off - No define
        return _FALSE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Check Bulk Type Queue Error Status
// Input Value  : Host Controller Type : EHCI / OHCI
// Output Value : _TRUE -> Error encountered ; _FALSE -> No Error encountered
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostChkBulkQueueErrSts(EnumUsbU2HostOwner enumOwner)
{
    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        BYTE ucBulkScsiState = GET_U2HOST_BULK_SCSI_STATE();

        // Check if Scsi State in No-Reply State (there will be no error in this case)
        if((ucBulkScsiState & (_BIT7 | _BIT6 | _BIT5)) == 0x00)
        {
            return _FALSE;
        }
        // [Part 1] Check if Error occcured in SCSI Read - BulkOut (CBW Stage)
        else if(ucBulkScsiState <= _U2HOST_BULK_SCSI_READ10_FILE_DATA_OUT_QH)
        {
            // 0x01 Means Host send Ping next out token
            if(((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00) ||
               ((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x01))
            {
                // No error
                return _FALSE;
            }
            else
            {
                DebugMessageU2HostEHCI("[Err] SCSI Read - CBW Error Status Value", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                return _TRUE;
            }
        }
        // [Part 2] Check if Error occured in SCSI Read - BulkIn (Data or CSW Stage)
        else if(ucBulkScsiState <= _U2HOST_BULK_SCSI_READ10_FILE_DATA_IN_QH)  // [Part 2] BULK In QH: 2 qTD or 1 qTD
        {
            // Data Stage
            if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
            {
                // Check Status[6:0] did not asserted (No Error Flag asserted)
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    // No error
                    return _FALSE;
                }
                else
                {
                    // Status[6] asserted, indicating a STALL resp in QTD0 (Data Stage).
                    if(ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) == 0x40)
                    {
                        CLR_U2HOST_TRANSFER_STATUS();

                        // Clear Halt bit in QH
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D06_B00_STATUS, 0x00);
                        // Clear Halt bit in QTD0
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x00);
                        // Reset Data Toggle bit in QH
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D06_B1F_DT, 0x00);
                        // Reset Data Toggle bit in QTD0
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0x00);

                        // Record the BULK_SCSI State which should be executed after CLEAR_HALT operation
                        SET_U2HOST_NEXT_STATE_AFTER_HALT(GET_U2HOST_BULK_SCSI_STATE());

                        SET_U2HOST_BULK_SCSI_STATE(_U2HOST_CLEAR_HALT_DUR_BULK);
                        DebugMessageU2HostEHCI("[Err] HALT in Data Stage", 0);
                    }
                    else
                    {
                        DebugMessageU2HostEHCI("[Err] SCSI Read - Data Error Status Value", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                    }
                    return _TRUE;
                }
            }
            // CSW Stage
            else
            {
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    // No error
                    return _FALSE;
                }
                else
                {
                    // Status[6] asserted, indicating a STALL resp in QTD0 (Data Stage).
                    if(ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) == 0x40)
                    {
                        CLR_U2HOST_TRANSFER_STATUS();

                        // Clear Halt bit in QH
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D06_B00_STATUS, 0x00);
                        // Clear Halt bit in QTD1
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x00);
                        // Reset Data Toggle bit in QH
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D06_B1F_DT, 0x00);
                        // Reset Data Toggle bit in QTD0
                        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 0x00);

                        // Record the BULK_SCSI State which should be executed after CLEAR_HALT operation
                        SET_U2HOST_NEXT_STATE_AFTER_HALT(GET_U2HOST_BULK_SCSI_STATE());

                        SET_U2HOST_BULK_SCSI_STATE(_U2HOST_CLEAR_HALT_DUR_BULK);
                        DebugMessageU2HostEHCI("[Err] HALT in CSW Stage", 0);
                    }
                    else
                    {
                        DebugMessageU2HostEHCI("[Err] SCSI Read - CSW Error Status Value", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                    }
                    return _TRUE;
                }
            }
        }
        // [Part 3] Check if Error occured in SCSI Write - BulkOut (CBW or Data Stage)
        else if(ucBulkScsiState == _U2HOST_BULK_SCSI_WRITE10_DATA_OUT_QH)
        {
            // CBW Stage
            if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
            {
                if(((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00) ||
                   ((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x01))
                {
                    // DebugMessageU2HostEHCI("[Err] Bulk Cond Value", ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS));
                    // No error
                    return _FALSE;
                }
                else
                {
                    return _TRUE;
                }
            }
            // Data Stage
            else
            {
                if(((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00) ||
                   ((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x01))
                {
                    // No error
                    return _FALSE;
                }
                else
                {
                    return _TRUE;
                }
            }
        }
        // [Part 4] Check if Error occured in SCSI Write - BulkIn (CSW Stage)
        else if(ucBulkScsiState == _U2HOST_BULK_SCSI_WRITE10_DATA_IN_QH)
        {
            if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00)
            {
                // No error
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
        // [Part 5] CLEAR HALT DURING BULK (Use Ctrl xfer)
        else
        {
            if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & ~_U2HOST_QTD_STATUS_ACTIVE) == 0x00)
            {
                // No error
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        BYTE ucColorState = GET_U2HOST_COLOR_STATE();

        if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION)
        {
            switch(ucColorState)
            {
                case _U2HOST_COLOR_BULK_OUT:

                    if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                    {
                        return _FALSE;
                    }
                    else
                    {
                        DebugMessageU2HostOHCI("[OHCI][Err] BULK_OUT_TD Error", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
                        return _TRUE;
                    }

                    break;

                case _U2HOST_COLOR_BULK_IN:

                    if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                    {
                        return _FALSE;
                    }
                    else
                    {
                        DebugMessageU2HostOHCI("[OHCI][Err] BULK_IN_TD Error", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
                        return _TRUE;
                    }

                    break;

                default:
                    break;
            }
        }
#endif
#endif
    }
    return _TRUE;
}

//----------------------------------------------------------------------------------------------------
// Description  : Check Bulk Type Queue is Executed Finish or Not
// Input Value  : Host Controller Type : EHCI / OHCI
// Output Value : _TRUE -> Execution Finished ; _FALSE -> Execution not Finished
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostChkBulkQueueComplete(EnumUsbU2HostOwner enumOwner)
{
    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        BYTE ucBulkScsiState = GET_U2HOST_BULK_SCSI_STATE();

        // Check if ScsiState in No-Reply State
        if((ucBulkScsiState & (_BIT7 | _BIT6 | _BIT5)) == 0x00)
        {
            // Command Completed
            return _TRUE;
        }
        else
        {
            if(ucBulkScsiState <= _U2HOST_BULK_SCSI_READ10_FILE_DATA_OUT_QH) // [Part 1] Out QH (1qTD,CBW)
            {
                // if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    // Complete
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else if(ucBulkScsiState <= _U2HOST_BULK_SCSI_READ10_FILE_DATA_IN_QH)  // [Part 2] In QH:2 qTD,except Test Unit State
            {
                // 1qTD[CSW] - No Data IN Stage
                if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
                {
                    if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                    {
                        // No error
                        return _TRUE;
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
                else
                {
                    if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                    {
                        // No error
                        return _TRUE;
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else if(ucBulkScsiState == _U2HOST_BULK_SCSI_WRITE10_DATA_OUT_QH)   // [Part 3] Out QH(2 qTD)
            {
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                    {
                        // No error
                        return _TRUE;
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
                else
                {
                    return _FALSE;
                }
            }
            else if(ucBulkScsiState == _U2HOST_BULK_SCSI_WRITE10_DATA_IN_QH) // [Part 4] BULK Write In QH(1 qTD) // [Part 4] In QH:1 qTD
            {
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    // No error
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else // [Part 5] CLEAR HALT DURING BULK(Use Ctrl xfer)
            {
                if((ScalerUsbU2HostGetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS) & _U2HOST_QTD_STATUS_ACTIVE) == 0x00)
                {
                    // No error
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
        }
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        WORD usHccaDoneHead = 0;
        usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_D21_B00_DONE_HEAD);

        if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION)
        {
            BYTE ucColorState = GET_U2HOST_COLOR_STATE();

            while(usHccaDoneHead != 0)
            {
                if(ucColorState == _U2HOST_COLOR_BULK_OUT)
                {
                    if(usHccaDoneHead == tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0])
                    {
                        return _TRUE;
                    }
                }
                else if(ucColorState == _U2HOST_COLOR_BULK_IN)
                {
                    if(usHccaDoneHead == tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0])
                    {
                        g_ucUsbU2HostColorReadRspLen = ScalerUsbU2HostGetRspDataLen(_U2HOST_OWNER_OHCI);
                        return _TRUE;
                    }
                }
                usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(usHccaDoneHead, _U2HOST_OHCI_TD_D02_B04_NEXT_TD);
            }
            return _FALSE;
        }
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif
    }
    return _FALSE;
}

//----------------------------------------------------------------------------------------------------
// Description  : Get Response Data Len from Buffer Pointer
// Input Value  : Host Controller Type : EHCI / OHCI
// Output Value : Data Len from Last QTD/TD In Queue
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbU2HostGetRspDataLen(EnumUsbU2HostOwner enumOwner)
{
    DWORD ulCurrAddr = 0x00;
    DWORD ulStartAddr = 0x00;
    BYTE ucDataLen = 0x00;

    ulCurrAddr = ulCurrAddr;
    ulStartAddr = ulStartAddr;
    ucDataLen = ucDataLen;

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        // Rsvd
#endif
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)

        switch(GET_U2HOST_COLOR_STATE())
        {
            case _U2HOST_COLOR_BULK_IN:

                ulCurrAddr = ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER);
                // (CURR_BUF_POINTER == 0) indicates that CURR_BUF met BUF_END
                if(ulCurrAddr == 0)
                {
                    ulCurrAddr = ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D03_B00_BUF_END) + 1;
                }

                ulStartAddr = _U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR;
                break;

            case _U2HOST_COLOR_INT_IN:

                ulCurrAddr = ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER);
                // (CURR_BUF_POINTER == 0) indicates that CURR_BUF met BUF_END
                if(ulCurrAddr == 0)
                {
                    ulCurrAddr = ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D03_B00_BUF_END) + 1;
                }

                ulStartAddr = _U2HOST_OHCI_INT0_BUFFER_ST_ADDR;
                break;

            default:
                break;
        }

        if((ulCurrAddr - ulStartAddr) > 0xFF)
        {
            DebugMessageU2HostOHCI("[OHCI] Warning: DataLen > 0xFF !", (ulCurrAddr - ulStartAddr));
        }
        ucDataLen = (BYTE)(ulCurrAddr - ulStartAddr);
#endif
#endif
    }

    return ucDataLen;
}

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Read Operation
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkReadOperation(void)
{
    switch(GET_U2HOST_BULK_SCSI_STATE())
    {
        case _U2HOST_ADD_BULK_READ_QH:

            ScalerUsbU2HostAddBulkReadQH();
            SET_U2HOST_COMPLETE_STATUS();
            break;

        case _U2HOST_IDLE:
        case _U2HOST_JUDGE_PARTITION_ID:
        case _U2HOST_CUR_PARTITION_ABORT:
        case _U2HOST_WAIT_USER_OSD_ENABLE:
        case _U2HOST_WAIT_USER_OSD_REBOOT:

            // No SCSI Cmd send by Host in these case

            SET_U2HOST_COMPLETE_STATUS();
            break;

        case _U2HOST_BULK_SCSI_INQUIRY_OUT_QH:

            ScalerUsbU2HostBulkScsiInquiryOutQh();
            break;

        case _U2HOST_BULK_SCSI_INQUIRY_IN_QH:

            ScalerUsbU2HostBulkScsiInquiryInQh();
            break;

        case _U2HOST_BULK_SCSI_READ_FORMAT_CAP_OUT_QH:

            ScalerUsbU2HostBulkScsiReadFormatCapOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ_FORMAT_CAP_IN_QH:

            ScalerUsbU2HostBulkScsiReadFormatCapInQh();
            break;

        case _U2HOST_BULK_SCSI_REQ_SENSE_OUT_QH:

            ScalerUsbU2HostBulkScsiReqSenseOutQh();
            break;

        case _U2HOST_BULK_SCSI_REQ_SENSE_IN_QH:

            ScalerUsbU2HostBulkScsiReqSenseInQh();
            break;

        case _U2HOST_BULK_SCSI_READ_CAPACITY10_OUT_QH:

            ScalerUsbU2HostBulkScsiReadCapacity10OutQh();
            break;

        case _U2HOST_BULK_SCSI_READ_CAPACITY10_IN_QH:

            ScalerUsbU2HostBulkScsiReadCapacity10InQh();
            break;

        case _U2HOST_BULK_SCSI_MODE_SENSE6_OUT_QH:

            ScalerUsbU2HostBulkScsiModeSense6OutQh();
            break;

        case _U2HOST_BULK_SCSI_MODE_SENSE6_IN_QH:

            ScalerUsbU2HostBulkScsiModeSense6InQh();
            break;

        case _U2HOST_BULK_SCSI_TEST_UNIT_READY_OUT_QH:

            ScalerUsbU2HostBulkScsiTestUnitReadyOutQh();
            break;

        case _U2HOST_BULK_SCSI_TEST_UNIT_READY_IN_QH:

            ScalerUsbU2HostBulkScsiTestUnitReadyInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_MBR_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10MBROutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_MBR_IN_QH:

            ScalerUsbU2HostBulkScsiRead10MBRInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_HDR_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10GPTOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_HDR_IN_QH:

            ScalerUsbU2HostBulkScsiRead10GPTInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_ENT_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10GPTOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_ENT_IN_QH:

            ScalerUsbU2HostBulkScsiRead10GPTInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_DBR_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10DBROutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_DBR_IN_QH:

            ScalerUsbU2HostBulkScsiRead10DBRInQh();
            break;

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
        case _U2HOST_BULK_SCSI_READ10_NTFS_ROOT_ENTRY_OUT_QH:
        case _U2HOST_BULK_SCSI_READ10_NTFS_IDX_RECORD_OUT_QH:
        case _U2HOST_BULK_SCSI_READ10_NTFS_FILE_ENTRY_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10NTFSOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_NTFS_ROOT_ENTRY_IN_QH:
        case _U2HOST_BULK_SCSI_READ10_NTFS_IDX_RECORD_IN_QH:
        case _U2HOST_BULK_SCSI_READ10_NTFS_FILE_ENTRY_IN_QH:

            ScalerUsbU2HostBulkScsiRead10NTFSInQh();
            break;
#endif

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_CLUS_NUM_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirClusNumOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_CLUS_NUM_IN_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirClusNumInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_SRCH_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirDataOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_SRCH_IN_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirDataInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FILE_GET_TGT_OUT_QH:
        case _U2HOST_BULK_SCSI_READ10_FILE_CHK_END_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10FileClusNumOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FILE_GET_TGT_IN_QH:
        case _U2HOST_BULK_SCSI_READ10_FILE_CHK_END_IN_QH:

            ScalerUsbU2HostBulkScsiRead10FileClusNumInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FW_VERSION_CHK_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10FileDataOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FW_VERSION_CHK_IN_QH:

            ScalerUsbU2HostBulkScsiRead10FileDataInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FILE_DATA_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10FileDataOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FILE_DATA_IN_QH:

            ScalerUsbU2HostBulkScsiRead10FileDataInQh();
            break;

        case _U2HOST_CLEAR_HALT_DUR_BULK:

            ScalerUsbU2HostClearHaltFeature(_U2HOST_OWNER_EHCI);
            break;

        case _U2HOST_BULK_SCSI_NONE:

            ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _DISABLE);
            break;

        default:

            break;
    }
}
#endif

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Write Operation
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkWriteOperation(EnumUsbU2HostDDRReadyState enumUsbU2HostDDRReadyState)
{
    enumUsbU2HostDDRReadyState = enumUsbU2HostDDRReadyState;

    switch(GET_U2HOST_BULK_SCSI_STATE())
    {
        // Bulk write contain Bulk read Part(ex.get mass device info)
        case _U2HOST_ADD_BULK_READ_QH:

            ScalerUsbU2HostAddBulkReadQH();
            SET_U2HOST_COMPLETE_STATUS();
            break;

        case _U2HOST_BULK_SCSI_INQUIRY_OUT_QH:

            ScalerUsbU2HostBulkScsiInquiryOutQh();
            break;

        case _U2HOST_BULK_SCSI_INQUIRY_IN_QH:

            ScalerUsbU2HostBulkScsiInquiryInQh();
            break;

        case _U2HOST_BULK_SCSI_READ_CAPACITY10_OUT_QH:

            ScalerUsbU2HostBulkScsiReadCapacity10OutQh();
            break;

        case _U2HOST_BULK_SCSI_READ_CAPACITY10_IN_QH:

            ScalerUsbU2HostBulkScsiReadCapacity10InQh();
            break;

        case _U2HOST_BULK_SCSI_MODE_SENSE6_OUT_QH:

            ScalerUsbU2HostBulkScsiModeSense6OutQh();
            break;

        case _U2HOST_BULK_SCSI_MODE_SENSE6_IN_QH:

            ScalerUsbU2HostBulkScsiModeSense6InQh();
            break;

        case _U2HOST_BULK_SCSI_TEST_UNIT_READY_OUT_QH:

            ScalerUsbU2HostBulkScsiTestUnitReadyOutQh();
            break;

        case _U2HOST_BULK_SCSI_TEST_UNIT_READY_IN_QH:

            ScalerUsbU2HostBulkScsiTestUnitReadyInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_MBR_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10MBROutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_MBR_IN_QH:

            ScalerUsbU2HostBulkScsiRead10MBRInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_HDR_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10GPTOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_HDR_IN_QH:

            ScalerUsbU2HostBulkScsiRead10GPTInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_ENT_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10GPTOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_GPT_ENT_IN_QH:

            ScalerUsbU2HostBulkScsiRead10GPTInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_DBR_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10DBROutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_DBR_IN_QH:

            ScalerUsbU2HostBulkScsiRead10DBRInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_CLUS_NUM_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirClusNumOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_CLUS_NUM_IN_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirClusNumInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_SRCH_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirDataOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FAT_DIR_SRCH_IN_QH:

            ScalerUsbU2HostBulkScsiRead10RootDirDataInQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FILE_CHK_END_OUT_QH:

            ScalerUsbU2HostBulkScsiRead10FileClusNumOutQh();
            break;

        case _U2HOST_BULK_SCSI_READ10_FILE_CHK_END_IN_QH:

            ScalerUsbU2HostBulkScsiRead10FileClusNumInQh();
            break;

        case _U2HOST_CLEAR_HALT_DUR_BULK:
            ScalerUsbU2HostClearHaltFeature(_U2HOST_OWNER_EHCI);
            break;

        // Bulk write contain Bulk write data Part
        case _U2HOST_ADD_BULK_WRITE_QH:

            ScalerUsbU2HostAddBulkWriteQH();
            SET_U2HOST_COMPLETE_STATUS();
            break;

        case _U2HOST_BULK_SCSI_WRITE10_DATA_OUT_QH:

            ScalerUsbU2HostBulkScsiWrite10DataOutQh(enumUsbU2HostDDRReadyState);

            break;

        case _U2HOST_BULK_SCSI_WRITE10_DATA_IN_QH:

            ScalerUsbU2HostBulkScsiWrite10DataInQh();

            break;

        default:

            break;
    }
}

#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _OFF)
//----------------------------------------------------------------------------------------------------
// Description  : Get DM Client addr err flag
// Input Value  : None
// Output Value : _Ture: 60 Byte missed occurs, _False: No error
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostGetDMAddrErrFlag(void)
{
    if(ScalerGetBit(P93_0B_DM_CLIENT_RETRY, _BIT0) == _BIT0)
    {
        ScalerSetByte(P93_26_DM_CLIENT_DUMMY, (ScalerGetByte(P93_26_DM_CLIENT_DUMMY) + 1));
        // error - 60 Byte missed occurs
        return _TRUE;
    }
    else
    {
        // no error
        return _FALSE;
    }

    return _FALSE;
}

//----------------------------------------------------------------------------------------------------
// Description  : DM Client addr err flag - FW Write 1 clr
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostClrDMAddrErrFlag(void)
{
    // Write 1 clr
    ScalerSetBit(P93_0B_DM_CLIENT_RETRY, ~_BIT0, _BIT0);
}
//----------------------------------------------------------------------------------------------------
// Description  : DM Client Initial Setting, Always No change
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDMClientInitial(void)
{
    BYTE ucHwidthH = 0;
    BYTE ucHwidthL = 0;
    BYTE ucVheightH = 0;
    BYTE ucVheightL = 0;

    WORD usLineStep = 0;
    BYTE ucTempResidue = 0;
    // BYTE ucTempQuotient = 0;
    // WORD usDBDumpCurPathCnt = 0;
    DWORD ulDBCurPathTotalLength = 0;

    WORD usTemp1 = 0;
    WORD usTemp2 = 0;
    WORD usTemp3 = 0;
    BYTE ucTemp4 = 0;

    WORD usTempDBCurXferLen = 0;
    BYTE ucTotalByteA = 0;
    BYTE ucTotalByteB = 0;

    CLR_U2HOST_DB_CUR_PATH_FINISH_STATE(); // Diff with ScalerUsbU2HostDMClientDoubleChkInitial(Old FW solution -Before ECO)

    SET_U2HOST_DB_CUR_PATH(_U2HOST_DB_M1);

    ScalerUsbU2HostClrDMAddrErrFlag();

    DebugMessageU2HostEHCI("[DM]M Domain Input Data Path", GET_MDOMAIN_INPUT_DATA_PATH());

    // -- Step_1 -- Get Info & caculate , Settimg DM Client Related Reg
    switch(GET_MDOMAIN_INPUT_DATA_PATH())
    {
        case _INPUT_PATH_M1_M2:

            // line step = even(Hwidth * 36bit / 64)
            ucTempResidue = GET_MDOMAIN_INPUT_HWIDTH() * 36 % 64;
            DebugMessageU2HostEHCI("[DM]M_Hwidth", GET_MDOMAIN_INPUT_HWIDTH());
            DebugMessageU2HostEHCI("[DM]M_Vheight", GET_MDOMAIN_INPUT_VHEIGHT());

            // Hwidth * 36bit / 64 = Hwidth * 9bit / 16
            usLineStep = (GET_MDOMAIN_INPUT_HWIDTH() * 9) >> 4;
            DebugMessageU2HostEHCI("[DM]Linstep_Raw", usLineStep);

            if(ucTempResidue != 0)
            {
                // Line step should be a multiple of 2
                if(usLineStep & _BIT0) // odd
                {
                    usLineStep += 1;
                }
                else // even
                {
                    usLineStep += 2;
                }
            }

            DebugMessageU2HostEHCI("[DM]Linstep_Final", usLineStep);

            // Total Size(CUR path) U2Host Need to move is (LineStep * 64bit * (Vheight/2)/8bit)Byte = (LineStep * Vheight * 4)Byte
            ulDBCurPathTotalLength = (GET_MDOMAIN_INPUT_VHEIGHT() * usLineStep) << 2;
            DebugMessageU2HostEHCI("[DM]DB Cur Path", GET_U2HOST_DB_CUR_PATH());
            DebugMessageU2HostEHCI("[DM]DBCurPath_Total_Length", ulDBCurPathTotalLength);


            // Length/1024 = x Kbyte
            usTemp1 = ulDBCurPathTotalLength >> 10;

            // Residue(<1024)
            // usTemp2 = ulDBCurPathTotalLength - (usTemp1 << 10);
            usTemp2 = ulDBCurPathTotalLength & 0x3ff;

            // Xfer time by _U2HOST_DB_XFER_MAX_LENGTH_ONCE
            usTemp3 = usTemp1 / _U2HOST_DB_XFER_MAX_LENGTH_ONCE;

            // Residue (<_U2HOST_DB_XFER_MAX_LENGTH_ONCE) (Unit KBYTE)
            ucTemp4 = usTemp1 % _U2HOST_DB_XFER_MAX_LENGTH_ONCE;


            if((usTemp2 == 0) && (ucTemp4 == 0))
            {
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt = usTemp3;

                // Last Xfer Length (Unit : BYTE)
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen = _U2HOST_DB_XFER_MAX_LENGTH_ONCE << 10;
            }
            else
            {
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt = usTemp3 + 1;

                // Last Xfer Length (Unit : BYTE)   Also equals to [((usTemp1 - usTemp3 * _U2HOST_DB_XFER_MAX_LENGTH_ONCE) << 10) + usTemp2];
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen = (ucTemp4 << 10) + usTemp2;

                // Make sure it is a multipe of 512 for SCSI Block is 512Byte unit
                if((usTemp2 > 0) && (usTemp2 < 0x200)) // 0<usTemp2<512
                {
                    usTemp2 = 512;
                }
                else if((usTemp2 > 0x200) && (usTemp2 < 0x400)) // 512<usTemp2<1024
                {
                    usTemp2 = 1024;
                }
                else // usTemp2 = 0 / 512
                {
                    // no change
                }

                // U2Host to device Length a multiple of 512 (Unit: Byte)
                g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen = (ucTemp4 << 10) + usTemp2;
            }

            // Shadow use to record How many data are left (to be transmitted)
            g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCntShadow = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt;
            DebugMessageU2HostEHCI("[DM]CurPathXferTotalCnt", g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt);
            DebugMessageU2HostEHCI("[DM]CurPath_Last_XferLen", g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen);
            DebugMessageU2HostEHCI("[DM]CurPath_Last_XferLenToDevice", g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen);

            // line Step
            ScalerSetByte(P93_09_DM_CLIENT_LINE_STEP_H, ((usLineStep >> 8) & 0xff));
            ScalerSetByte(P93_0A_DM_CLIENT_LINE_STEP_L, (usLineStep & 0xff));

            ucHwidthH = (GET_MDOMAIN_INPUT_HWIDTH() >> 8) & 0xff;
            ucHwidthL = GET_MDOMAIN_INPUT_HWIDTH() & 0xff;

            // M1/M2 is EO Mode, So need Divide 2 fisrt[>>9 = ((>>1)>>8)]
            ucVheightH = (GET_MDOMAIN_INPUT_VHEIGHT() >> 9) & 0xff;
            ucVheightL = (GET_MDOMAIN_INPUT_VHEIGHT() >> 1) & 0xff;

            // M1/2 HWidth
            ScalerSetByte(P93_17_FRAME_WIDTH_H, ucHwidthH);
            ScalerSetByte(P93_18_FRAME_WIDTH_L, ucHwidthL);

            // M1/2 Vheight
            ScalerSetByte(P93_19_FRAME_LENGTH_H, ucVheightH);
            ScalerSetByte(P93_1A_FRAME_LENGTH_L, ucVheightL);

            break;

        case _INPUT_PATH_M1_M2_S1_S2:

            // line step = even((Hwidth/2) * 36bit / 64)
            ucTempResidue = (GET_MDOMAIN_INPUT_HWIDTH() >> 1) * 36 % 64;

            // (Hwidth/2) * 36bit / 64 = Hwidth * 9bit / 8
            usLineStep = (GET_MDOMAIN_INPUT_HWIDTH() * 9) >> 3;

            if(ucTempResidue != 0)
            {
                if(usLineStep & _BIT0)
                {
                    usLineStep += 1;
                }
                else
                {
                    usLineStep += 2;
                }
            }

            // Total Size U2Host Need to move is (LineStep * 64bit * Vheight/8bit)Byte = (LineStep * Vheight * 8)Byte
            ulDBCurPathTotalLength = (GET_MDOMAIN_INPUT_VHEIGHT() * usLineStep) << 2; // [(INPUT_VHEIGHT()>>1) * LineStep <<3]

            // Length/1024 = x Kbyte
            usTemp1 = ulDBCurPathTotalLength >> 10;

            // Residue(<1024)
            // usTemp2 = ulDBCurPathTotalLength - (usTemp1 << 10);
            usTemp2 = ulDBCurPathTotalLength & 0x3ff;

            // Xfer time by _U2HOST_DB_XFER_MAX_LENGTH_ONCE
            usTemp3 = usTemp1 / _U2HOST_DB_XFER_MAX_LENGTH_ONCE;

            // Residue (<_U2HOST_DB_XFER_MAX_LENGTH_ONCE) (Unit KBYTE)
            ucTemp4 = usTemp1 % _U2HOST_DB_XFER_MAX_LENGTH_ONCE;


            if((usTemp2 == 0) && (ucTemp4 == 0))
            {
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt = usTemp3;

                // Last Xfer Length (Unit : BYTE)
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen = _U2HOST_DB_XFER_MAX_LENGTH_ONCE << 10;
            }
            else
            {
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt += 1;

                // Last Xfer Length (Unit : BYTE)   Also equals to [((usTemp1 - usTemp3 * _U2HOST_DB_XFER_MAX_LENGTH_ONCE) << 10) + usTemp2];
                g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen = (ucTemp4 << 10) + usTemp2;

                // Make sure it is a multipe of 512 for SCSI Block is 512Byte unit
                if((usTemp2 > 0) && (usTemp2 < 0x200)) // 0<usTemp2<512
                {
                    usTemp2 = 512;
                }
                else if((usTemp2 > 0x200) && (usTemp2 < 0x400)) // 512<usTemp2<1024
                {
                    usTemp2 = 1024;
                }
                else // usTemp2 = 0 / 512
                {
                    // no change
                }

                // U2Host to device Length a multiple of 512 (Unit: Byte)
                g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen = (ucTemp4 << 10) + usTemp2;
            }

            // Shadow use to record How many data are left (to be transmitted)
            g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCntShadow = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt;
            DebugMessageU2HostEHCI("[DM]DBCurPathXferTotalCnt", g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt);
            DebugMessageU2HostEHCI("[DM]DBCurPath_Last_XferLen", g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen);
            DebugMessageU2HostEHCI("[DM]CurPath_Last_XferLenToDevice", g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen);

            // line Step
            ScalerSetByte(P93_09_DM_CLIENT_LINE_STEP_H, ((usLineStep >> 8) & 0xff));
            ScalerSetByte(P93_0A_DM_CLIENT_LINE_STEP_L, (usLineStep & 0xff));


            // S1/S2 is FB Mode, So need Divide 2 fisrt[>>9 = ((>>1)>>8)]
            ucHwidthH = (GET_MDOMAIN_INPUT_HWIDTH() >> 9) & 0xff;
            ucHwidthL = (GET_MDOMAIN_INPUT_HWIDTH() >> 1) & 0xff;

            // M1/M2 is EO Mode, So need Divide 2 fisrt[>>9 = ((>>1)>>8)]
            ucVheightH = (GET_MDOMAIN_INPUT_VHEIGHT() >> 9) & 0xff;
            ucVheightL = (GET_MDOMAIN_INPUT_VHEIGHT() >> 1) & 0xff;

            // M1/2 S1/S2 HWidth
            ScalerSetByte(P93_17_FRAME_WIDTH_H, ucHwidthH);
            ScalerSetByte(P93_18_FRAME_WIDTH_L, ucHwidthL);

            // M1/2 S1/2 Vheight
            ScalerSetByte(P93_19_FRAME_LENGTH_H, ucVheightH);
            ScalerSetByte(P93_1A_FRAME_LENGTH_L, ucVheightL);

            break;

        default:
            break;
    }


    // -- Step_2 -- Setting Xfer Len (Include DM Client and Host To Device)
    // Update Dobly dump data size (Unit Byte), setting in DM Client Fifo HW
    if(g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCntShadow == 1) // Last transation Bytes in cur DB Path
    {
        // usTempDBCurXferLen = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen;
        usTempDBCurXferLen = g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen;
    }
    else
    {
        usTempDBCurXferLen = _U2HOST_DB_XFER_MAX_LENGTH_ONCE << 10;
    }

    // Update Xfer Len each time, (Unit Byte)
    g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen = usTempDBCurXferLen;
    DebugMessageU2HostEHCI("[DM] DBCurXferLen", g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen);

    // ddr xfer length
    ucTotalByteA = usTempDBCurXferLen >> 9; // unit is 512 byte
    ucTotalByteB = (usTempDBCurXferLen & 0x1ff) >> 2; // unit is 4 Byte

    ScalerSetByte(P93_01_DM_CLIENT_CTRL1, ucTotalByteB);
    ScalerSetByte(P93_00_DM_CLIENT_CTRL0, (ucTotalByteA & 0x3f)); // make sure bit7/6 =00

    // Updata Last transation Bytes (Host to device)to make sure 512BYTE Unit
    if(g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCntShadow == 1) // Last transation Bytes Host to Device
    {
        // Update U2Host to Device Last length which will be 512YTE Unit
        g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen = g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen;
    }

    // -- Step_3 -- Setting DDR Addr that DM client will be access
    // Initial Update DDR Addr = M1 Start ADDR
    g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);
    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr;
    DebugMessageU2HostEHCI("[DM]DB Cap M1initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

    // Get M1 Start Address In DDR and Set to DM Client Reg
    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));


    // -- Step_4 -- Setting Other (DM Client Reg)
    // State TimeOut
    ScalerSetByte(P93_04_STATE_TIMEOUT, 0x68); // 0x68/30MHz = 3.467us

    // DDR Burst LEN. Length of data to transimit every time,unit is 64 bit.
    ScalerSetByte(P93_25_DDR_BURST_LEN, 0x08);
}

//----------------------------------------------------------------------------------------------------
// Description  : DM Client Update Setting, need to be changed by diff case
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDMClientUpdate(void)
{
    WORD usTempDBCurXferLen = 0;
    BYTE ucTotalByteA = 0;
    BYTE ucTotalByteB = 0;

    // Update DDR address Where DM Client Should get(M1/2/S1/2 Start Address In DDR)
    if(GET_U2HOST_DB_CUR_PATH_FINISH_STATE() == _TRUE)
    {
        CLR_U2HOST_DB_CUR_PATH_FINISH_STATE();

        // Reload UsbU2HostDBCurPathXferCntShadow = usUsbU2HostDBCurPathXferCnt
        g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCntShadow = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCnt;

        switch(GET_MDOMAIN_INPUT_DATA_PATH())
        {
            case _INPUT_PATH_M1_M2:

                if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M1)
                {
                    // Update DDR Addr = M1 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);
                    DebugMessageU2HostEHCI("[DM]DB Cap M1initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

                    // Get M1 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M2)
                {
                    // Update DDR Addr = M2 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);
                    DebugMessageU2HostEHCI("[DM]DB Cap M2initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

                    // Get M2 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else
                {
                    // Not define
                }
                break;

            case _INPUT_PATH_M1_M2_S1_S2:

                if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M1)
                {
                    // Update DDR Addr = M1 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);

                    // Get M1 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M2)
                {
                    // Update DDR Addr = M2 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);

                    // Get M2 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_S1)
                {
                    // Update DDR Addr = S1 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK);

                    // Get S1 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_S2)
                {
                    // Update DDR Addr = S2 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK);

                    // Get S2 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else
                {
                    // Not Define
                }

                break;

            default:
                break;
        }
    }
    else
    {
        if(ScalerUsbU2HostGetDMAddrErrFlag() == _FALSE) // No error case
        {
            // Update DM Client Access ddr addr, deta = (Byte to Transfer * 8bit/64bit) [<<10 <<3 >>6]=[<< 7]
            g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr += (_U2HOST_DB_XFER_MAX_LENGTH_ONCE << 7);
            DebugMessageU2HostEHCI("[DM]Update DB Cap DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

            // Update CurAddr In DDR
            ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
            ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
            ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
            ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
        }
        else // Missing 60 Byte occured
        {
            // Nothing to update, Keep it the same as last time
            DebugMessageU2HostEHCI("[DM]Update DB Cap DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

            // Update CurAddr In DDR
            ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
            ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
            ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
            ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
        }
    }


    if(g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathXferCntShadow == 1) // Last transation process
    {
        // Update Dobly dump data size (Unit Byte), setting in DM Client Fifo HW
        // usTempDBCurXferLen = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLastXferLen; // Last transation Bytes in cur DB Path
        usTempDBCurXferLen = g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen; // Last transation Bytes in cur DB Path,need align EHCI To Device Length

        // Updata Last transation Bytes (Host to device)to make sure that is multiple of 512Byte
        g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen = g_stUsbU2HostDBCurPath.usUsbU2HostDBtoDeviceLastXferLen; // Last transation Bytes Host to Device
    }
    else
    {
        // Update Dobly dump data size (Unit Byte), setting in DM Client Fifo HW
        usTempDBCurXferLen = _U2HOST_DB_XFER_MAX_LENGTH_ONCE << 10;

        // Update Xfer Len(H - D) each time, value will be multiple of 512Byte
        g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen = usTempDBCurXferLen;
    }

    // ddr xfer length, Setting in DM Client Fifo HW
    ucTotalByteA = usTempDBCurXferLen >> 9; // unit is 512 byte
    ucTotalByteB = (usTempDBCurXferLen & 0x1ff) >> 2; // unit is 4 Byte

    ScalerSetByte(P93_01_DM_CLIENT_CTRL1, ucTotalByteB);
    ScalerSetByte(P93_00_DM_CLIENT_CTRL0, (ucTotalByteA & 0x3f)); // make sure bit7/6 =00
}
#else // _U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON
//----------------------------------------------------------------------------------------------------
// Description  : DM Client Initial Setting, Always No change
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDMClientDoubleChkInitial(void)
{
    BYTE ucHwidthH = 0;
    BYTE ucHwidthL = 0;
    BYTE ucVheightH = 0;
    BYTE ucVheightL = 0;

    WORD usLineStep = 0;
    BYTE ucTempResidue = 0;

    BYTE ucDBXferVHNumCalcCrc = 0;
    WORD usHwidthSetting = 0;
    DWORD ulCrcCalcXferLenTemp = 0; // Unit Byte

    WORD usTemp1 = 0;
    WORD usTemp2 = 0;
    BYTE ucTemp3 = 0;

    BYTE ucSetDDRDataTemp1 = 0;
    WORD usSetDDRDataTemp2 = 0;

    WORD usSetDDRDataTemp4 = 0;
    BYTE ucSetDDRDataTemp3 = 0;

    // Unit 64bit
    DWORD ulCurPathTotalSize = 0;
    DWORD ulSetDDRDataTemp5 = 0;
    DWORD ulM1WriteDataAddr = 0;
    DWORD ulM2WriteDataAddr = 0;

    ucSetDDRDataTemp1 = ucSetDDRDataTemp1;
    SET_U2HOST_DB_CUR_PATH_FINISH_STATE();

    SET_U2HOST_DB_CUR_PATH(_U2HOST_DB_M1);

    // Fisrt xfer VH NO = 1
    g_stUsbU2HostDBCurPath.usUsbU2HostDBNextXferVHNO = 1;

    // Unit(Byte), xfer Len in one ddrxferEn
    g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen = _U2HOST_DB_XFER_LEN_ONCE_BULK_DATA << 10;

    DebugMessageU2HostEHCI("[DM]M Domain Input Data Path", GET_MDOMAIN_INPUT_DATA_PATH());

    switch(GET_MDOMAIN_INPUT_DATA_PATH())
    {
        case _INPUT_PATH_M1_M2:

            // EO Mode M1(M2) Vehight = Frame Vehight/2 - use to check cur path finish or not
            g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathVehight = GET_MDOMAIN_INPUT_VHEIGHT() >> 1;

            // Data Size Max 20KB each time - In order to Caculate Crc, Get the Integer multiple of vehight each time
            if(GET_MDOMAIN_INPUT_HWIDTH() == 1920)
            {
                // 1920*16*36/8/1024=135K,
                // To make sure 16 vehight data all correct, will set to xfer 140kByte+20kByte in fact each DDRXferEn event occurs.
                ucDBXferVHNumCalcCrc = 16;

                // 2000*16*36/8/1024=140.625K > 140K+60Byte (Assume 20K Each DDRxferen)
                // Means HW Caculate crc size is 140.625KB, 140KB will be correct if 140.625KB data crc compare pass. if so, it also proves that 135KB data(16 vehight) is correct.
                usHwidthSetting = 2000;
            }
            else if(GET_MDOMAIN_INPUT_HWIDTH() == 3840)
            {
                // 3840*8*36/8/1024=135K
                ucDBXferVHNumCalcCrc = 8;

                // 4000*8*36/8/1024=140.625K > 140K+60Byte (Assume 20K Each DDRxferen)
                usHwidthSetting = 4000;
            }
            else
            {
                DebugMessageU2HostEHCI("[DM]FW Solution NOT Support Cur timing", 0);
            }

            g_stUsbU2HostDBCurPath.ucUsbU2HostDBXferVHNumCalcCrc = ucDBXferVHNumCalcCrc;

            // line step = even(Hwidth * 36bit / 64)
            ucTempResidue = GET_MDOMAIN_INPUT_HWIDTH() * 36 % 64;
            DebugMessageU2HostEHCI("[DM]M_Hwidth", GET_MDOMAIN_INPUT_HWIDTH());
            DebugMessageU2HostEHCI("[DM]M_Vheight", GET_MDOMAIN_INPUT_VHEIGHT());

            // Hwidth * 36bit / 64 = Hwidth * 9bit / 16
            usLineStep = (GET_MDOMAIN_INPUT_HWIDTH() * 9) >> 4;
            DebugMessageU2HostEHCI("[DM]Linstep_Raw", usLineStep);

            if(ucTempResidue != 0)
            {
                if(usLineStep & _BIT0) // odd
                {
                    usLineStep += 1;
                }
                else // even
                {
                    usLineStep += 2;
                }
            }

            g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep = usLineStep;
            DebugMessageU2HostEHCI("[DM]Linstep_Final", g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep);

            // Calccrc Vehight XferLen Each Time (LineStep * 64bit * (ucUsbU2HostDBXferVHNumCalcCrc)/8bit)Byte = (LineStep * ucUsbU2HostDBXferVHNumCalcCrc * 8)Byte
            ulCrcCalcXferLenTemp = (ucDBXferVHNumCalcCrc * g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep) << 3;
            DebugMessageU2HostEHCI("[DM] Crc confirm Size(Byte)", ulCrcCalcXferLenTemp);
            DebugMessageU2HostEHCI("[DM] Crc confirm vehight cnt", ucDBXferVHNumCalcCrc);


            // Length/1024 = x KByte
            usTemp1 = ulCrcCalcXferLenTemp >> 10; // Total Bytes Xfer to make sure CRC pass. ex: 1920*16*36/8/1024=135KB

            usTemp2 = usTemp1 / _U2HOST_DB_XFER_LEN_ONCE_BULK_DATA;  // ex: 135 / 20 = 6
            ucTemp3 = usTemp1 % _U2HOST_DB_XFER_LEN_ONCE_BULK_DATA; // Last len in cur crc calc (KB)  ex: 135%20 = 15 (!=0)


            if(ucTemp3 != 0)
            {
                usTemp2 += 2; // +2 to make sure last vehight in ucUsbU2HostDBXferVHNumCalcCrc data transfer is ok  ex:1920 *16 vehight case
            }
            else
            {
                usTemp2 += 1;
            }

            g_stUsbU2HostDBCurPath.ulUsbU2HostDBCalcCrcXferLenEachTime = usTemp2 * _U2HOST_DB_XFER_LEN_ONCE_BULK_DATA; // unit (KB)  ex: 1920*16 case, 8*20K=160kB

            g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnce = usTemp2;

            // Shadow use to record How many data are left Dur Crc Calcu (to be transmitted)
            g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnceShadow = g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnce;

            DebugMessageU2HostEHCI("[DM]DBCurCrcCalcXferTotalLen(KB)", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCalcCrcXferLenEachTime);
            DebugMessageU2HostEHCI("[DM]DBCurCrcCalcXferTotalBulkOutCnt", g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnce);


            // DM Client Fifo line Step Setting
            ScalerSetByte(P93_09_DM_CLIENT_LINE_STEP_H, ((usLineStep >> 8) & 0xff));
            ScalerSetByte(P93_0A_DM_CLIENT_LINE_STEP_L, (usLineStep & 0xff));

            // ucHwidthH is not real value (self defined by diff case)
            ucHwidthH = (usHwidthSetting >> 8) & 0xff;
            ucHwidthL = usHwidthSetting & 0xff;

            // Vehight cnt to be xfer once
            ucVheightH = 0x00;
            ucVheightL = g_stUsbU2HostDBCurPath.ucUsbU2HostDBXferVHNumCalcCrc;

            // M1/2 HWidth
            ScalerSetByte(P93_17_FRAME_WIDTH_H, ucHwidthH);
            ScalerSetByte(P93_18_FRAME_WIDTH_L, ucHwidthL);

            // Vheight cnt to be xfer once
            ScalerSetByte(P93_19_FRAME_LENGTH_H, ucVheightH);
            ScalerSetByte(P93_1A_FRAME_LENGTH_L, ucVheightL);

            break;

        case _INPUT_PATH_M1_M2_S1_S2:

            // TBD
            break;

        default:
            break;
    }

    // State TimeOut
    ScalerSetByte(P93_04_STATE_TIMEOUT, 0x68); // 0x68/30MHz = 3.467us

    // DDR Burst LEN. Length of data to transimit every time,unit is 64 bit.
    ScalerSetByte(P93_25_DDR_BURST_LEN, 0x08);


    switch(GET_MDOMAIN_INPUT_DATA_PATH())
    {
        case _INPUT_PATH_M1_M2:

            if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M1)
            {
                // Update DDR Addr = M1 Start ADDR
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr;
                DebugMessageU2HostEHCI("[DM]DB Cap M1initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

                // Get M1 Start Address In DDR
                ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
            }
            else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M2)
            {
                // Update DDR Addr = M2 Start ADDR
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr;
                DebugMessageU2HostEHCI("[DM]DB Cap M2initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

                // Get M2 Start Address In DDR
                ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
            }
            else
            {
                // Not define
            }
            break;

        case _INPUT_PATH_M1_M2_S1_S2:

            if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M1)
            {
                // Update DDR Addr = M1 Start ADDR
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);

                // Get M1 Start Address In DDR
                ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
            }
            else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M2)
            {
                // Update DDR Addr = M2 Start ADDR
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);

                // Get M2 Start Address In DDR
                ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
            }
            else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_S1)
            {
                // Update DDR Addr = S1 Start ADDR
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK);

                // Get S1 Start Address In DDR
                ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
            }
            else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_S2)
            {
                // Update DDR Addr = S2 Start ADDR
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK);

                // Get S2 Start Address In DDR
                ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
            }
            else
            {
                // Not Define
            }

            break;

        default:
            break;
    }


    // set some DDR addr data to make sure last xfer data crc calc correctly
    // ex.540 / 16 = 33
    ucSetDDRDataTemp1 = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathVehight / g_stUsbU2HostDBCurPath.ucUsbU2HostDBXferVHNumCalcCrc;
    DebugMessageU2HostEHCI("[DM]ucSetDDRDataTemp1 ", ucSetDDRDataTemp1);
    // ex.540 % 16 = 12
    usSetDDRDataTemp2 = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathVehight % g_stUsbU2HostDBCurPath.ucUsbU2HostDBXferVHNumCalcCrc;
    DebugMessageU2HostEHCI("[DM]ucSetDDRDataTemp2 ", usSetDDRDataTemp2);

    // ex.101.25K % 20 = 5;   (usUsbU2HostDBCurPathLineStep * 64 / 8 = x BYTE) >> 10 = yKB
    ucSetDDRDataTemp3 = (((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep << 3) * usSetDDRDataTemp2) >> 10) % _U2HOST_DB_XFER_LEN_ONCE_BULK_DATA;
    // ex. 256 + 1024Byte = 1280
    usSetDDRDataTemp4 = (((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep << 3) * usSetDDRDataTemp2) & 0x3ff) + (ucSetDDRDataTemp3 << 10);
    DebugMessageU2HostEHCI("[DM]usSetDDRDataTemp4 ", usSetDDRDataTemp4);

    // unit 64bit ex. 1920*36/64*540 = 583200
    ulCurPathTotalSize = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep * g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathVehight;
    DebugMessageU2HostEHCI("[DM]ulCurPathTotalSize ", ulCurPathTotalSize);

    // deta * 8 / 64 (unit 64bit) ex.[(20480 - 1280)/8 + 583200] = 585600 (64Bit unit)
    ulSetDDRDataTemp5 = ((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen - usSetDDRDataTemp4) >> 3) + ulCurPathTotalSize;
    DebugMessageU2HostEHCI("[DM]ulSetDDRDataTemp5 ", ulSetDDRDataTemp5);

    if(usSetDDRDataTemp2 == 0) //
    {
        if(ucTemp3 != 0)
        {
            ulM1WriteDataAddr = ulSetDDRDataTemp5 + ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);
            ulM2WriteDataAddr = ulSetDDRDataTemp5 + ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);
        }
        else
        {
            ulM1WriteDataAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK) + ulCurPathTotalSize + 4;
            ulM2WriteDataAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK) + ulCurPathTotalSize + 4;
        }
    }
    else
    {
        // ex. 585600(0x8EF80) + 0x1E0200 = 0x26F180
        ulM1WriteDataAddr = ulSetDDRDataTemp5 + ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);
        // ex. 585600(0x8EF80) + 0x2D6A00 = 0x365980
        ulM2WriteDataAddr = ulSetDDRDataTemp5 + ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);
    }
    DebugMessageU2HostEHCI("[DM]ulM1WriteDataAddr ", ulM1WriteDataAddr);
    DebugMessageU2HostEHCI("[DM]ulM2WriteDataAddr ", ulM2WriteDataAddr);

    // set m1 addr
    ScalerSetByte(P37_04_MCU_DC_ADDR_H, ((ulM1WriteDataAddr >> 24) & 0xff));
    ScalerSetByte(P37_05_MCU_DC_ADDR_M, ((ulM1WriteDataAddr >> 16) & 0xff));
    ScalerSetByte(P37_06_MCU_DC_ADDR_L, ((ulM1WriteDataAddr >> 8) & 0xff));
    ScalerSetByte(P37_07_MCU_DC_ADDR, (ulM1WriteDataAddr & 0xff));

    // set data, 2pc can set 32Byte
    ScalerSetByte(P37_10_MCU_DC_DATABUF_W_A_00, 0x11);
    ScalerSetByte(P37_11_MCU_DC_DATABUF_W_A_01, 0x22);
    ScalerSetByte(P37_12_MCU_DC_DATABUF_W_A_02, 0x33);
    ScalerSetByte(P37_13_MCU_DC_DATABUF_W_A_03, 0x44);
    // assign write cmd
    ScalerSetByte(P37_00_MCU_DC_CMD, 0x80);

    // set m2 addr
    ScalerSetByte(P37_04_MCU_DC_ADDR_H, ((ulM2WriteDataAddr >> 24) & 0xff));
    ScalerSetByte(P37_05_MCU_DC_ADDR_M, ((ulM2WriteDataAddr >> 16) & 0xff));
    ScalerSetByte(P37_06_MCU_DC_ADDR_L, ((ulM2WriteDataAddr >> 8) & 0xff));
    ScalerSetByte(P37_07_MCU_DC_ADDR, (ulM2WriteDataAddr & 0xff));

    // set data, 2pc can set 32Byte
    ScalerSetByte(P37_10_MCU_DC_DATABUF_W_A_00, 0x66);
    ScalerSetByte(P37_11_MCU_DC_DATABUF_W_A_01, 0x77);
    ScalerSetByte(P37_12_MCU_DC_DATABUF_W_A_02, 0x88);
    ScalerSetByte(P37_13_MCU_DC_DATABUF_W_A_03, 0x99);
    // assign write cmd
    ScalerSetByte(P37_00_MCU_DC_CMD, 0x80);
}
//----------------------------------------------------------------------------------------------------
// Description  : DM Client Update Setting, need to be changed by diff case
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDMClientDoubleChkUpdate(void)
{
    BYTE ucTotalByteA = 0;
    BYTE ucTotalByteB = 0;

    // Update DDR address Where DM Client Should get(M1/2/S1/2 Start Address In DDR)
    if(GET_U2HOST_DB_CUR_PATH_FINISH_STATE() == _TRUE)
    {
        CLR_U2HOST_DB_CUR_PATH_FINISH_STATE();
        SET_U2HOST_DB_CUR_CRC_SAME_STATE(_U2HOST_DB_CRC_NONE);

        // Reload ucUsbU2HostDBCalcCrcXferCntOnceShadow = ucUsbU2HostDBCalcCrcXferCntOnce
        g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnceShadow = g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnce;

        switch(GET_MDOMAIN_INPUT_DATA_PATH())
        {
            case _INPUT_PATH_M1_M2:

                if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M1)
                {
                    // Update DDR Addr = M1 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr;
                    DebugMessageU2HostEHCI("[DM]DB Cap M1initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

                    // Get M1 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M2)
                {
                    // Update DDR Addr = M2 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr;
                    DebugMessageU2HostEHCI("[DM]DB Cap M2initial DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);

                    // Get M2 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else
                {
                    // Not define
                }
                break;

            case _INPUT_PATH_M1_M2_S1_S2:

                if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M1)
                {
                    // Update DDR Addr = M1 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN1_PAGE, _FRC_1ST_BLOCK);

                    // Get M1 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_M2)
                {
                    // Update DDR Addr = M2 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_MAIN2_PAGE, _FRC_1ST_BLOCK);

                    // Get M2 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_S1)
                {
                    // Update DDR Addr = S1 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_SUB1_PAGE, _FRC_1ST_BLOCK);

                    // Get S1 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else if(GET_U2HOST_DB_CUR_PATH() == _U2HOST_DB_S2)
                {
                    // Update DDR Addr = S2 Start ADDR
                    g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = ScalerFRCGetCapAddress(_FRC_SUB2_PAGE, _FRC_1ST_BLOCK);

                    // Get S2 Start Address In DDR
                    ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
                    ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
                    ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
                    ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
                }
                else
                {
                    // Not Define
                }

                break;

            default:
                break;
        }
    }
    else
    {
        if(GET_U2HOST_DB_CUR_CRC_SAME_STATE() != _U2HOST_DB_CRC_SAME)
        {
            if(GET_U2HOST_DB_CUR_CRC_SAME_STATE() == _U2HOST_DB_CRC_NONE)
            {
                // deta = (Byte to Transfer * 8bit/64bit) [<<10 <<3 >>6]=[<< 7]
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr += (_U2HOST_DB_XFER_LEN_ONCE_BULK_DATA << 7);
            }
            else // (GET_U2HOST_DB_CUR_CRC_SAME_STATE() == _U2HOST_DB_CRC_DIFF)
            {
                SET_U2HOST_DB_CUR_CRC_SAME_STATE(_U2HOST_DB_CRC_NONE);

                // Retry previous calc crc xfer
                g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBStartCapAddrCurCrcCalc;

                // Process in DataHandler
                // SET_U2HOST_FAT32_DB_FILE_DUMP_LBA(g_stUsbU2HostDBCurPath.ulUsbU2HostDBtoDeviceStartAddrCurCrcCalc);
            }
        }
        else // CRC_SAME_STATE() = Same, Not update ulUsbU2HostDBCapAddr
        {
            SET_U2HOST_DB_CUR_CRC_SAME_STATE(_U2HOST_DB_CRC_NONE);

            // deta = (Byte to Transfer * 8bit/64bit) [<<10 <<3 >>6]=[<< 7]
            g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr = g_stUsbU2HostDBCurPath.ulUsbU2HostDBInitCapAddr + (g_stUsbU2HostDBCurPath.usUsbU2HostDBNextXferVHNO - 1) * g_stUsbU2HostDBCurPath.usUsbU2HostDBCurPathLineStep;
        }


        DebugMessageU2HostEHCI("[DM]Update DB Cap DDR addr", g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr);
        // Update CurAddr In DDR
        ScalerSetByte(P93_20_DDR_ADDR_MSB, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 24) & 0xff));
        ScalerSetByte(P93_21_DDR_ADDR_H, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 16) & 0xff));
        ScalerSetByte(P93_22_DDR_ADDR_M, ((g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr >> 8) & 0xff));
        ScalerSetByte(P93_23_DDR_ADDR_L, (g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr & 0xff));
    }

    // Means this is the first bulk out in cur calc crc xfer
    if(g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnceShadow == g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnce)
    {
        // Record cur first xfer Cap DDR ADDR during Calc crc xfer(for retry use)
        g_stUsbU2HostDBCurPath.ulUsbU2HostDBStartCapAddrCurCrcCalc = g_stUsbU2HostDBCurPath.ulUsbU2HostDBCapAddr;

        // Record cur fisrt xfer addr to device during calc crc xfer(for retry use)
        g_stUsbU2HostDBCurPath.ulUsbU2HostDBtoDeviceStartAddrCurCrcCalc = GET_U2HOST_FAT32_DB_FILE_DUMP_LBA();
    }

    // ddr xfer length
    ucTotalByteA = g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 9; // unit is 512 byte
    ucTotalByteB = (g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen & 0x1ff) >> 2; // unit is 4 Byte

    ScalerSetByte(P93_01_DM_CLIENT_CTRL1, ucTotalByteB);
    ScalerSetByte(P93_00_DM_CLIENT_CTRL0, (ucTotalByteA & 0x3f)); // make sure bit7/6 =00
}
//----------------------------------------------------------------------------------------------------
// Description  : Get CRC Only EN Result
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetCurDMOnlyCrcEnResult(void)
{
    WORD usDelayTemp = 10000;
    BYTE ucLoopI = 0;

    // DM Client fifo crc enable, bit[4] is protected for checker warning
    ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7 | _BIT4), _BIT7);

    ucLoopI = ucLoopI;

    // Wait crc caculate Done
    while((ScalerGetBit(P93_10_DM_CLIENT_CRC_CTRL, _BIT4) == 0x00) && (--usDelayTemp != 0))
    {
        DELAY_5US();
    }

    if(usDelayTemp > 0)
    {
        // Record current crc result (H- L)
        g_pucUsbU2HostDMCrcResultGolden[0] = ScalerGetByte(P93_11_DM_CLIENT_CRC_1); // Bit47~40
        g_pucUsbU2HostDMCrcResultGolden[1] = ScalerGetByte(P93_12_DM_CLIENT_CRC_2);
        g_pucUsbU2HostDMCrcResultGolden[2] = ScalerGetByte(P93_13_DM_CLIENT_CRC_3);
        g_pucUsbU2HostDMCrcResultGolden[3] = ScalerGetByte(P93_14_DM_CLIENT_CRC_4);
        g_pucUsbU2HostDMCrcResultGolden[4] = ScalerGetByte(P93_15_DM_CLIENT_CRC_5);
        g_pucUsbU2HostDMCrcResultGolden[5] = ScalerGetByte(P93_16_DM_CLIENT_CRC_6); // Bit7~0
    }
    else // =0
    {
        DebugMessageU2HostEHCI("[DM]CRC Only Caculate Timeout.", 0);
    }

/*
    DebugMessageU2HostEHCI("[DM] CRC Only EN Result finish.", 0);

    for(ucLoopI = 0; ucLoopI < 6; ucLoopI++)
    {
        DebugMessageU2HostEHCI("[DM] CRC Only EN Result.", g_pucUsbU2HostDMCrcResultGolden[ucLoopI]);
    }
*/
    // DM Client fifo crc disable
    ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7 | _BIT4), 0x00);
}
//----------------------------------------------------------------------------------------------------
// Description  : Get CRC EN + Xfer EN Result
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetCurDMCrcAndXferEnResult(void)
{
    WORD usDelayTemp = 10000;
    BYTE ucLoopI = 0;

    ucLoopI = ucLoopI;

    // Wait crc caculate Done
    while((ScalerGetBit(P93_10_DM_CLIENT_CRC_CTRL, _BIT4) == 0x00) && (--usDelayTemp != 0))
    {
        DELAY_5US();
    }

    if(usDelayTemp > 0)
    {
        // Record current crc result (H- L)
        g_pucUsbU2HostDMCrcResultTBD[0] = ScalerGetByte(P93_11_DM_CLIENT_CRC_1); // Bit47~40
        g_pucUsbU2HostDMCrcResultTBD[1] = ScalerGetByte(P93_12_DM_CLIENT_CRC_2);
        g_pucUsbU2HostDMCrcResultTBD[2] = ScalerGetByte(P93_13_DM_CLIENT_CRC_3);
        g_pucUsbU2HostDMCrcResultTBD[3] = ScalerGetByte(P93_14_DM_CLIENT_CRC_4);
        g_pucUsbU2HostDMCrcResultTBD[4] = ScalerGetByte(P93_15_DM_CLIENT_CRC_5);
        g_pucUsbU2HostDMCrcResultTBD[5] = ScalerGetByte(P93_16_DM_CLIENT_CRC_6); // Bit7~0
    }
    else // =0
    {
        DebugMessageU2HostEHCI("[DM]CRC Caculate Timeout.", 0);
    }

/*
    DebugMessageU2HostEHCI("[DM] CRC Only EN Result finish.", 0);

    for(ucLoopI = 0; ucLoopI < 6; ucLoopI++)
    {
        DebugMessageU2HostEHCI("[DM] CRC+Xfer EN Result.", g_pucUsbU2HostDMCrcResultTBD[ucLoopI]);
    }
*/
    // DM Client fifo crc disable
    ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7 | _BIT4), 0x00);
}
//----------------------------------------------------------------------------------------------------
// Description  : DM Client Check the crc Result between crc only en and crc + xfer both enable
// Input Value  : None
// Output Value : True:CRC Same.  False:CRC diff
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostCheckCrcResultSame(void)
{
    BYTE ucLoopI = 0;
    BYTE ucResultCnt = 0;

    for(ucLoopI = 0; ucLoopI < 6; ucLoopI++)
    {
        if(g_pucUsbU2HostDMCrcResultTBD[ucLoopI] == g_pucUsbU2HostDMCrcResultGolden[ucLoopI])
        {
            ucResultCnt++;
        }
        else
        {
            // DebugMessageU2HostEHCI("[DM]Both EN CRC Diff.", g_pucUsbU2HostDMCrcResultTBD[ucLoopI]);
        }
    }

    if(ucResultCnt == 6)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

//----------------------------------------------------------------------------------------------------
// Description  : DB Dump file name update when switch frame
// Input Value  : ucCaseIndex(Hex value), ucFrameIndex(Hex value)
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDBDumpFrameNameUpdate(BYTE ucCaseIndex, BYTE ucFrameIndex)
{
    // Update File name - for Test_xx_yy_z, only need to replace "z" in cur frame.[Test_Offset(46+48)_Offset(52+54)_Offset(60).txt]
    BYTE ucFrameIndex_OnesPlace = 0;
    BYTE ucFrameIndex_tensPlace = 0;
    BYTE ucCaseIndex_OnesPlace = 0;
    BYTE ucCaseIndex_tensPlace = 0;

    // Get cur xx
    ucCaseIndex_tensPlace = ucCaseIndex / 10;
    ucCaseIndex_OnesPlace = ucCaseIndex % 10;

    g_pucUsbFileSysGoldenFileName[46] = tUsbFat32GoldenLongFileNameReplace[ucCaseIndex_tensPlace];
    g_pucUsbFileSysGoldenFileName[48] = tUsbFat32GoldenLongFileNameReplace[ucCaseIndex_OnesPlace];

    // Get cur yy
    ucFrameIndex_tensPlace = ucFrameIndex / 10;
    ucFrameIndex_OnesPlace = ucFrameIndex % 10;

    g_pucUsbFileSysGoldenFileName[52] = tUsbFat32GoldenLongFileNameReplace[ucFrameIndex_tensPlace];
    g_pucUsbFileSysGoldenFileName[54] = tUsbFat32GoldenLongFileNameReplace[ucFrameIndex_OnesPlace];

    // update z
    ScalerUsbU2HostDBDumpSubFrameNameUpdate(_U2HOST_DB_M1_INDEX);


    if(g_bUsbU2HostFirstUpdateFlag == _FALSE)
    {
        g_bUsbU2HostFirstUpdateFlag = _TRUE;
        SET_U2HOST_BULK_SCSI_STATE(_U2HOST_ADD_BULK_READ_QH);
    }
    else
    {
        // Go Back for preparing to Search Next File Name
        SET_U2HOST_BULK_SCSI_STATE(_U2HOST_BULK_SCSI_READ10_MBR_OUT_QH);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : DB Dump file M1/2 S1/2 name update when Last part finished
// Input Value  : enumUsbU2HostDBCurPathIndex(0:M1 1:M2 2:S1 3:S2)
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDBDumpSubFrameNameUpdate(EnumUsbU2HostDBCurPathIndex  enumUsbU2HostDBCurPathIndex)
{
    // Update File name - for Test_xx_yy_z, only need to replace "z" in cur frame.[Test_Offset(46+48)_Offset(52+54)_Offset(60).txt]
    g_pucUsbFileSysGoldenFileName[60] = tUsbFat32GoldenLongFileNameReplace[enumUsbU2HostDBCurPathIndex];
}

#endif // End of #if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Read QH Initial
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostAddBulkReadQH(void)
{
    BYTE ucValueTemp = 0;

    DebugMessageU2HostEHCI("[EHCI] AddBulkReadQH.", 0);

    // Clear All USB Memory
    // ScalerUsbU2HostMemoryClear(_U2HOST_MEMORY_ST_ADDR, _U2HOST_EHCI_MEMORY_SIZE);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _DISABLE);

    // 1.Initial for Bulk Read Out Queue Head
    for(ucValueTemp = 0; ucValueTemp < _U2HOST_EHCI_BULK_OUT_QH_NUM; ucValueTemp++)
    {
        // --------------------- Bulk Read Out QH DWORD0 Setting ---------------------//
        // Set Bulk Out QH sram address at 0x120 (Max = 0x0BFF(3071))
        // T(BIT[0])=1:ignored if QH is in the asynchrounous schedule;
        // Typ=QH(BIT[2:1]=2'b01);
        // QHLP(BIT[31:5]) at 0x0120
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B05_QHLP, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B01_TYP, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B00_T, 1);

        // --------------------- Bulk Read Out QH DWORD1 Setting ---------------------//
        // Device Address(BIT[6:0]=0x00 default);
        // I(BIT[7]=1'b0)-Only valid in Periodic Schedule and the EPS field indicates a FS/LS endpoint.
        // Endpt(BIT[11:8]=?);EPS(BIT[13:12]=?  2'b10->HS)
        // DTC(BIT[14]=0):Host controller initial DT bit in QH instead of Qtd
        // H(BIT[15]=1):Mark a queue head as being the head of the reclamation(the first QH?)
        // Max packet(BIT[26:16]= ?  0x200=512)
        // C(BIT[27]=0): if QH.EPS indicates the endpoint is not a high speed device and not an control endpoint,then fw must set this bit=1;
        // RL(BIT[31:28]=4'b0000):contains a value,used by host controller to reload the nak counter field.0:Not Use NakCounter(Means Infinite?)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B08_ENDPT, GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX)); // Result from Get other descriptor
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0C_EPS, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));   // Must set it before the fisrt process of Enumeration
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0E_DTC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0F_H, 1);   // Head of reclamation List Flag = 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B10_MPL, GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX));// 0x200
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B1B_C, 0);

        // --------------------- Bulk Read Out QH DWORD2 Setting ---------------------//
        // Mult[BIT[31:30]=01]1 transaction count in one uframe
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B1E_MULT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B00_S_MASK, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B08_C_MASK, 0);

        // --------------------- Bulk Read Out QH DWORD3 Setting ---------------------//
        // Default all set 0

        // --------------------- Bulk Read Out QH DWORD4 Setting ---------------------//
        // Next Qtd address at 0x0040
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // --------------------- Bulk Read Out QH DWORD5 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

        // --------------------- Bulk Read Out QH DWORD6-11 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D06_B00_STATUS, 1);
        // Default all set 0
    }


    // 1-1.Initial for Bulk Read qTD : CBW
    // --------------------- Bulk Read CBW QTD DWORD0 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0); // No next qtd in current transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

    // --------------------- Bulk Read CBW QTD DWORD1 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

    // --------------------- Bulk Read CBW QTD DWORD2 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD

    // --------------------- Bulk Read CBW QTD DWORD3 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

    // --------------------- Bulk Read CBW QTD DWORD4-7 Setting ---------------------//
    // Default all set 0

    // 2.Initial for Bulk Read In Queue Head
    for(ucValueTemp = 0; ucValueTemp < _U2HOST_EHCI_BULK_IN_QH_NUM; ucValueTemp++)
    {
        // --------------------- Bulk Read In QH DWORD0 Setting ---------------------//
        // Set Bulk Out QH sram address at 0xA0 (Max = 0x0BFF(3071))
        // T(BIT[0])=1:ignored if QH is in the asynchrounous schedule;
        // Typ=QH(BIT[2:1]=2'b01);
        // QHLP(BIT[31:5]) at 0xA0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B05_QHLP, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B01_TYP, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B00_T, 1);

        // --------------------- Bulk Read In QH DWORD1 Setting ---------------------//
        // Device Address(BIT[6:0]=  default);
        // I(BIT[7]=1'b0)-Only valid in Periodic Schedule and the EPS field indicates a FS/LS endpoint.
        // Endpt(BIT[11:8]=?);EPS(BIT[13:12]=?  2'b10->HS)
        // DTC(BIT[14]=0):Host controller initial DT bit in QH instead of Qtd
        // H(BIT[15]=1):Mark a queue head as being the head of the reclamation(the first QH?)
        // Max packet(BIT[26:16]= ?  0x200=512)
        // C(BIT[27]=0): if QH.EPS indicates the endpoint is not a high speed device and not an control endpoint,then fw must set this bit=1;
        // RL(BIT[31:28]=4'b0000):contains a value,used by host controller to reload the nak counter field
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B08_ENDPT, GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX)); // Result from Get other descriptor
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0C_EPS, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));   // Must set it before the fisrt process of Enumeration
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0E_DTC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0F_H, 1);   // Head of reclamation List Flag = 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B10_MPL, GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX));// 0x200
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B1B_C, 0);

        // --------------------- Bulk Read In QH DWORD2 Setting ---------------------//
        // Mult[BIT[31:30]=01]1 transaction count in one uframe
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B1E_MULT, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B00_S_MASK, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B08_C_MASK, 0);


        // --------------------- Bulk Read In QH DWORD3 Setting ---------------------//
        // Default all set 0

        // --------------------- Bulk Read In QH DWORD4 Setting ---------------------//
        // Next Qtd address at 0x0040
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // --------------------- Bulk Read In QH DWORD5 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

        // --------------------- Bulk Read In QH DWORD6-11 Setting ---------------------//
        // Default all set 0
    }


    // 2-1.Initial for Bulk Read qTD : Data In
    // --------------------- Bulk Read Data In QTD DWORD0 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);

    // --------------------- Bulk Read Data In QTD DWORD1 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

    // --------------------- Bulk Read Data In QTD DWORD2 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);       // Not last qTD

    // --------------------- Bulk Read Data In QTD DWORD3 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

    // --------------------- Bulk Read Data In QTD DWORD4-7 Setting ---------------------//
    // Default all set 0


    // 2-2.Initial for Bulk Read qTD : Csw
    // --------------------- Bulk Read Csw QTD DWORD0 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1); // last qtd

    // --------------------- Bulk Read Csw QTD DWORD1 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

    // --------------------- Bulk Read Csw QTD DWORD2 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD

    // --------------------- Bulk Read Csw QTD DWORD3 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Write QH Initial
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostAddBulkWriteQH(void)
{
    BYTE ucValueTemp = 0;

    // Clear All USB Memory
    // ScalerUsbU2HostMemoryClear(_U2HOST_MEMORY_ST_ADDR, _U2HOST_EHCI_MEMORY_SIZE);

    // ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _DISABLE);

    DebugMessageU2HostEHCI("[EHCI] Add BulkWrite QH.", 0);

    // 1.Initial for Bulk Write Out Queue Head
    for(ucValueTemp = 0; ucValueTemp < _U2HOST_EHCI_BULK_OUT_QH_NUM; ucValueTemp++)
    {
        // --------------------- Bulk Write Out QH DWORD0 Setting ---------------------//
        // Set Bulk Out QH sram address at 0x120 (Max = 0x0BFF(3071))
        // T(BIT[0])=1:ignored if QH is in the asynchrounous schedule;
        // Typ=QH(BIT[2:1]=2'b01);
        // QHLP(BIT[31:5]) at 0x0120
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B05_QHLP, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B01_TYP, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B00_T, 1);

        // --------------------- Bulk Write Out QH DWORD1 Setting ---------------------//
        // Device Address(BIT[6:0]=0x00 default);
        // I(BIT[7]=1'b0)-Only valid in Periodic Schedule and the EPS field indicates a FS/LS endpoint.
        // Endpt(BIT[11:8]=?);EPS(BIT[13:12]=?  2'b10->HS)
        // DTC(BIT[14]=0):Host controller initial DT bit in QH instead of Qtd
        // H(BIT[15]=1):Mark a queue head as being the head of the reclamation(the first QH?)
        // Max packet(BIT[26:16]= ?  0x200=512)
        // C(BIT[27]=0): if QH.EPS indicates the endpoint is not a high speed device and not an control endpoint,then fw must set this bit=1;
        // RL(BIT[31:28]=4'b0000):contains a value,used by host controller to reload the nak counter field
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B08_ENDPT, GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX)); // Result from Get other descriptor
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0C_EPS, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));   // Must set it before the fisrt process of Enumeration
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0E_DTC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0F_H, 1);   // Head of reclamation List Flag = 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B10_MPL, GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX));// 0x200
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B1B_C, 0);

        // --------------------- Bulk Write Out QH DWORD2 Setting ---------------------//
        // Mult[BIT[31:30]=01]1 transaction count in one uframe
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B1E_MULT, 1);

        // --------------------- Bulk Write Out QH DWORD3 Setting ---------------------//
        // Default all set 0

        // --------------------- Bulk Write Out QH DWORD4 Setting ---------------------//
        // Next Qtd address at 0x0040
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // --------------------- Bulk Write Out QH DWORD5 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

        // --------------------- Bulk Write Out QH DWORD6-11 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D06_B00_STATUS, 1);

        // Default all set 0
    }


    // 1-1.Initial for Bulk Write qTD : CBW
    // --------------------- Bulk Write CBW QTD DWORD0 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1]);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);

    // --------------------- Bulk Write CBW QTD DWORD1 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

    // --------------------- Bulk Write CBW QTD DWORD2 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);       // Not last qTD

    // --------------------- Bulk Write CBW QTD DWORD3 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

    // --------------------- Bulk Write CBW QTD DWORD4-7 Setting ---------------------//
    // Default all set 0

    // 2-2.Initial for Bulk Write qTD : Data Out
    // --------------------- Bulk Read Data In QTD DWORD0 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

    // --------------------- Bulk Write Data Out QTD DWORD1 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

    // --------------------- Bulk Write Data Out QTD DWORD2 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD

    // --------------------- Bulk Write Data Out QTD DWORD3 Setting ---------------------//

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B0C_BUFFER_POINTER_PAGE0, 1);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_WRITE_FROM_DM_CLIENT_ST_ADDR);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D08_B0C_BUFFER_POINTER_PAGE1, 1);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D09_B0C_BUFFER_POINTER_PAGE2, 1);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D0A_B0C_BUFFER_POINTER_PAGE3, 1);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D0B_B0C_BUFFER_POINTER_PAGE4, 1);

    // --------------------- Bulk Write Data Out QTD DWORD4-7 Setting ---------------------//
    // Default all set 0


    // 2.Initial for Bulk Write In Queue Head
    for(ucValueTemp = 0; ucValueTemp < _U2HOST_EHCI_BULK_IN_QH_NUM; ucValueTemp++)
    {
        // --------------------- Bulk Write In QH DWORD0 Setting ---------------------//
        // Set Bulk Out QH sram address at 0xA0 (Max = 0x0BFF(3071))
        // T(BIT[0])=1:ignored if QH is in the asynchrounous schedule;
        // Typ=QH(BIT[2:1]=2'b01);
        // QHLP(BIT[31:5]) at 0xA0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B05_QHLP, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B01_TYP, 1);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B00_T, 1);

        // --------------------- Bulk Write In QH DWORD1 Setting ---------------------//
        // Device Address(BIT[6:0]=  default);
        // I(BIT[7]=1'b0)-Only valid in Periodic Schedule and the EPS field indicates a FS/LS endpoint.
        // Endpt(BIT[11:8]=?);EPS(BIT[13:12]=?  2'b10->HS)
        // DTC(BIT[14]=0):Host controller initial DT bit in QH instead of Qtd
        // H(BIT[15]=1):Mark a queue head as being the head of the reclamation(the first QH?)
        // Max packet(BIT[26:16]= ?  0x200=512)
        // C(BIT[27]=0): if QH.EPS indicates the endpoint is not a high speed device and not an control endpoint,then fw must set this bit=1;
        // RL(BIT[31:28]=4'b0000):contains a value,used by host controller to reload the nak counter field
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B08_ENDPT, GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX)); // Result from Get other descriptor
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0C_EPS, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));   // Must set it before the fisrt process of Enumeration
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0E_DTC, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0F_H, 1);   // Head of reclamation List Flag = 1
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B10_MPL, GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(_U2HOST_DEVICE_ATTACH_INDEX));// 0x200
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B1B_C, 0);

        // --------------------- Bulk Write In QH DWORD2 Setting ---------------------//
        // Mult[BIT[31:30]=01]1 transaction count in one uframe
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B1E_MULT, 1);

        // --------------------- Bulk Write In QH DWORD3 Setting ---------------------//
        // Default all set 0

        // --------------------- Bulk Write In QH DWORD4 Setting ---------------------//
        // Next Qtd address at 0x0040
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // --------------------- Bulk Write In QH DWORD5 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

        // --------------------- Bulk Write In QH DWORD6-11 Setting ---------------------//
        // Default all set 0
    }


    // 2-1.Initial for Bulk Write qTD : Csw
    // --------------------- Bulk Read Csw QTD DWORD0 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1); // last qtd

    // --------------------- Bulk Read Csw QTD DWORD1 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

    // --------------------- Bulk Read Csw QTD DWORD2 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD

    // --------------------- Bulk Read Csw QTD DWORD3 Setting ---------------------//
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Inquiry Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiInquiryOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                offset0-3
        0x10, 0x80, 0x87, 0x69, // dCBWTag                      offset4-7
        0x24, 0x00, 0x00, 0x00, // Xfer Length : 0x00 00 00 24  offset8-11
        0x80,                   // Data In                      offset12
        0x00,                   // bCBWLUN                      offset13
        0x06,                   // Cmd Block Length :           offset14
        0x12
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00, 0x00, 0x00, 0x24,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };


    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        DebugMessageU2HostEHCI("[SCSI] Inquiry Out QH.", 0);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

        // assign 31Byte cmd to Host Buffer
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
        ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
        ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Prepared to Enable qTD 0 CBW
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

        // Re-assign BULK OUT QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Inquiry Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiInquiryInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Inquiry In1 DataIn.", 0);

            ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 32 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);       // Not last qTD

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x24); // Data In 36Byte

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Not last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn,  qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Inquiry In2 CSW", 0);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);
            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // Not necessary?
            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR, 0x10); // Clear 16

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi ReadFormatCap Command Out Qh
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiReadFormatCapOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content (15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                offset0-3
        0x22, 0x80, 0x87, 0x69, // dCBWTag                      offset4-7
        0xfc, 0x00, 0x00, 0x00, // Xfer Length : 0x00 00 00 fc  offset8-11
        0x80,                   // Data In                      offset12
        0x00,                   // bCBWLUN                      offset13
        0x0A,                   // Cmd Block Length :           offset14
        0x23
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xfc,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] ReadFormatCap Out QH.", 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
    // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi ReadFormatCap Command In Qh
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiReadFormatCapInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] ReadFormatCap Data In1.", 0);

            ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 8 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0xfc); // Data In 252Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Not last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] ReadFormatCap In2 CSW", 0);

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi ReqSense Command Out Qh
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiReqSenseOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content (15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                offset0-3
        0x21, 0x80, 0x87, 0x69, // dCBWTag                      offset4-7
        0x12, 0x00, 0x00, 0x00, // Xfer Length : 0x00 00 00 12  offset8-11
        0x80,                   // Data In                      offset12
        0x00,                   // bCBWLUN                      offset13
        0x0C,                   // Cmd Block Length :           offset14
        0x03
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00, 0x00, 0x00, 0x12,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] ScsiReqSense Out QH.", 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
    // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi ReqSense Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiReqSenseInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] ScsiReqSense In1 Data In.", 0);

            ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 8 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x12); // Data In 18Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Not last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] ScsiReqSense In2 CSW", 0);

            // Reset QH Status field(bit6:Halted) when Detect Halt at current state


            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read Capacity10 Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiReadCapacity10OutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content (15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                offset0-3
        0x20, 0x80, 0x87, 0x69, // dCBWTag                      offset4-7
        0x08, 0x00, 0x00, 0x00, // Xfer Length : 0x00 00 00 08  offset8-11
        0x80,                   // Data In                      offset12
        0x00,                   // bCBWLUN                      offset13
        0x0A,                   // Cmd Block Length :           offset14
        0x25
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] ReadCapacity 10 Out QH.", 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
    // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi ReadCapacity10 Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiReadCapacity10InQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] ReadCapacity10 In1 Data In.", 0);

            ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 8 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08); // Data In 8Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Not last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] ReadCapacity10 In2 CSW", 0);

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Mode Sense6 Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiModeSense6OutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                offset0-3
        0x30, 0x80, 0x87, 0x69, // dCBWTag                      offset4-7
        0xC0, 0x00, 0x00, 0x00, // Xfer Length : 0x00 00 00 0C  offset8-11
        0x80,                   // Data In                      offset12
        0x00,                   // bCBWLUN                      offset13
        0x06,                   // Cmd Block Length :           offset14
        0x1A
    };
    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00, 0x08, 0x00, 0xC0,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    // pucUsbBulkScsiCmd1[13] =  g_stUsbU2HostStorageDeviceInfo.ucMaxLun;

    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        DebugMessageU2HostEHCI("[SCSI] ModeSense Out QH.", 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
        // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

        // assign 31Byte cmd to Host Buffer
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
        ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
        ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Prepared to Enable qTD 0 CBW
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

        // Re-assign BULK OUT QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Mode Sense6 Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiModeSense6InQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] ModeSense6 In1 Data In.", 0);

            ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 8 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08); // Data In 8Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Not last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] ModeSense6 In2 CSW", 0);

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Test Unit Ready Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiTestUnitReadyOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                offset0-3
        0x40, 0x80, 0x87, 0x69, // dCBWTag                      offset4-7
        0x00, 0x00, 0x00, 0x00, // Xfer Length : 0x00 00 00 00  offset8-11
        0x00,                   // Dir : Data out H to D        offset12
        0x00,                   // bCBWLUN                      offset13
        0x06,                   // Cmd Block Length :           offset14
        0x00
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] TestUnit Out QH.", 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
    // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Test Unit Command In Qh(CSW)- Note: Test Unit Ready with No Data Stage
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiTestUnitReadyInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        DebugMessageU2HostEHCI("[SCSI]TestUnit In2 CSW", 0);

        // Reset QH Status field(bit6:Halted) when Detect Halt at current state
        // Do not Consider Halt case for TestUnit cmd


        // CSW
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);

        // Prepared to Enable qTD1:CSW
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(MBR) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10MBROutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0x00, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x02, 0x00, 0x00, // Xfer Length : 0x00 00 02 00          offset8-11
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x01,             // Specify the block nums to be transferred
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] Read10 MBR Out QH.", 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(MBR) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10MBRInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 MBR In1(Data)", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x200); // Data In 512Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 MBR In2 CSW", 0);

            // Reset QH Status field(bit6:Halted) when Detect Halt at current state
            // Do not Consider Halt case for Read10 cmd

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(GPT) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10GPTOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0xff, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x02, 0x00, 0x00, // Xfer Length : 0x00 00 04 00          offset8-11
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x01,            // Specify the block nums to be transferred
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };
    // DebugMessageU2HostEHCI("[SCSI] Read10 File Data Out.", 0);

    // Update Logical Block Addr
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
    // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(File Data) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10GPTInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            // DebugMessageU2HostEHCI("[SCSI] Read10 File Data In1.", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 2 x 512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x200); // Data In 512 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);        // last qTD Need Assert flag
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);   // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            // DebugMessageU2HostEHCI("[SCSI] Read10 File Data In2 CSW", 0);
            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(DBR) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10DBROutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0x01, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x02, 0x00, 0x00, // Xfer Length : 0x00 00 02 00          offset8-11
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x01,             // Specify the block nums to be transferred
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] Read10 DBR Out QH", 0);

    // Update Logical Block Addr = DBR Start Sector
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(DBR) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10DBRInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 DBR In1(Data)", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x200); // Data In 512Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 DBR In2 CSW", 0);

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(DBR) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10NTFSOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0x01, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x04, 0x00, 0x00, // Xfer Length : 0x00 00 02 00          offset8-11
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x02,             // Specify the block nums to be transferred
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] Read10 NTFS Out QH", 0);

    // Update Logical Block Addr
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(DBR) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10NTFSInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 NTFS In1 (Data)", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 2x512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x400); // Data In 1024 Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 NTFS In2 (CSW)", 0);

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(RootDirectory ClusNum) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10RootDirClusNumOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0x02, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x02, 0x00, 0x00, // Xfer Length : 0x00 00 02 00          offset8-11
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x01,             // Specify the block nums to be transferred
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] Read10 GetRootDirClusNum Out QH", 0);

    // Update Logical Block Addr = DBR Start Sector
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(RootDirectory ClusNum) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10RootDirClusNumInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 RootDir ClusNum In1(Data)", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x200); // Data In 512Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 RootDir ClusNum In2 CSW", 0);

            // Reset QH Status field(bit6:Halted) when Detect Halt at current state
            // Do not Consider Halt case for Read10 cmd

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(RootDirectory Data) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10RootDirDataOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0x03, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x04, 0x00, 0x00, // Xfer Length : 0x00 00 04 00          offset8-11   // 1KByte!
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x02,             // Specify the block nums to be transferred // 1KByte!
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

    DebugMessageU2HostEHCI("[SCSI] Read10 RootDir Data Out(CBW)", 0);

    // Update Logical Block Addr to search RootDir area until file name is founded
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1); // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F); // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(RootDirectory Data) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10RootDirDataInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 RootDir Data In1(Data)", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 2x512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x400); // Data In 1024 Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 RootDir Data In2 CSW", 0);

            // Reset QH Status field(bit6:Halted) when Detect Halt at current state
            // Do not Consider Halt case for Read10 cmd

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(File ClusNum) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10FileClusNumOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0x04, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x04, 0x00, 0x00, // Xfer Length : 0x00 00 04 00          offset8-11 // 1KByte!
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x02,             // Specify the block nums to be transferred // 1KByte!
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };
    DebugMessageU2HostEHCI("[SCSI] Read10 File ClusNum Out QH", 0);

    // Update Logical Block Addr = Flie Start clus LBA
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(File ClusNum) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10FileClusNumInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 File ClusNum In1(Data)", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 2x512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x400); // Data In 1024 Byte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            DebugMessageU2HostEHCI("[SCSI] Read10 File ClusNum In2 CSW", 0);

            // Reset QH Status field(bit6:Halted) when Detect Halt at current state
            // Do not Consider Halt case for Read10 cmd

            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(File Data) Command Out Qh(CBW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10FileDataOutQh(void)
{
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0xff, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x04, 0x00, 0x00, // Xfer Length : 0x00 00 04 00          offset8-11 // 1KByte!
        0x80,                   // Data In                              offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x28                    // Read 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr
        0x00,
        0x00, 0x02,            // Specify the block nums to be transferred // 1KByte!
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };
    // DebugMessageU2HostEHCI("[SCSI] Read10 File Data Out.", 0);

    // Update Logical Block Addr
    pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_CUR_LBA() >> 24) & 0xff);
    pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_CUR_LBA() >> 16) & 0xff);
    pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_CUR_LBA() >> 8) & 0xff);
    pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_CUR_LBA() & 0xff);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);
    // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

    // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

    // assign 31Byte cmd to Host Buffer
    ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
    ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Prepared to Enable qTD 0 CBW
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

    // Re-assign BULK OUT QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Scsi Read10(File Data) Command In Qh(Data In + CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiRead10FileDataInQh(void)
{
    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
        {
            // DebugMessageU2HostEHCI("[SCSI] Read10 File Data In1.", 0);

            // ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D01_B1C_RL, 0); // Not use Reload Nakcnt

            // Data IN - Receive 2 x 512 Bytes
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x400); // Data In 1kByte


            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);        // last qTD Need Assert flag
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);   // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);
            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

            // Prepared to Enable qTD0:DataIn
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }
        else
        {
            // DebugMessageU2HostEHCI("[SCSI] Read10 File Data In2 CSW", 0);
            // CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

            // ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
            // Prepared to Enable qTD1:CSW
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
        }

        // Prepared to Enable QH
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

        // Re-assign BULK IN QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
    }
    else
    {
        DebugMessageU2HostEHCI("[EHCI] Disable Ayns Not yet .", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Write Out QH Setting(CBW + DATA Out)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiWrite10DataOutQh(EnumUsbU2HostDDRReadyState enumUsbU2HostDDRReadyState)
{
    enumUsbU2HostDDRReadyState = enumUsbU2HostDDRReadyState;
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
    // CBW(31Byte) pucUsbBulkScsiCmd1 + pucUsbBulkScsiCmd2 (the 32th Byte Not Use(Total Bytes set 31))

    // (15Byte) + 1Byte Opcode = 16Byte
    // 0-3: CBWSignature fixed 43425355h ;
    // 4-7: CBWTag
    // 8-11: CBWDataTransferLength
    // 12: bmCBWFlags: 0- data from host;1- data to host
    // 13: CBWLUN
    // 14: CBWCBLength: the length of command(range:0-16)
    // 15-30: CBWCB Content(15:Opcode)

    BYTE pucUsbBulkScsiCmd1[16] =
    {
        0x55, 0x53, 0x42, 0x43, // dCBWSignature                        offset0-3
        0xAA, 0x00, 0x00, 0xff, // dCBWTag                              offset4-7
        0x00, 0x40, 0x00, 0x00, // Xfer Length : 0x00 00 40 00          offset8-11 (L->H) // Will be update below
        0x00,                   // Data out                             offset12
        0x00,                   // bCBWLUN                              offset13
        0x0A,                   // Cmd Block Length : 0x0A = 10         offset14
        0x2A                    // Write 10 Opcode
    };

    // Command Data Block(16Byte max) except 1st Byte[(Opcode) Contain in pucUsbBulkScsiCmd1[15]]. The last Byte Not use
    BYTE pucUsbBulkScsiCmd2[16] =
    {
        0x00,
        0x00, 0x00, 0x00, 0x00, // Logical Block Addr(H->L) // Will be update below
        0x00,
        0x00, 0x20,             // Specify the block nums to be transferred(H->L) // Will be update below
        0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00
    };

#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)

    // DebugMessageU2HostEHCI("[DM]enumUsbU2HostDDRReadyState", enumUsbU2HostDDRReadyState);

    if(enumUsbU2HostDDRReadyState == _U2HOST_DDR_READY)
    {
        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
        {
            // DebugMessageU2HostEHCI("[EHCI] Disable Ayns Success .", 0);

            if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
            {
                DebugMessageU2HostEHCI("[SCSI] Bulk Write CBW Stage.", 0);

                if(GET_U2HOST_DM_CLIENT_INITIAL() == _FALSE)
                {
                    ScalerUsbU2HostDMClientDoubleChkInitial();
                    SET_U2HOST_DM_CLIENT_INITIAL();
                }

                ScalerUsbU2HostDMClientDoubleChkUpdate();

                // Note: Initial value should make sure TRUE
                if(GET_U2HOST_DDR_FRC_CLIENT_EN_STATUS() == _TRUE)  // Setting when 1 new frame start
                {
                    // Before Start to Dump 1 new frame, wait 1 IVS to make sure frame data are stored in DDR Ready
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                    // Before Start to Dump 1 new frame, DDR Client should only for u2 client use, so off all Frc client
                    ScalerFRCEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
                    CLR_U2HOST_DDR_FRC_CLIENT_EN_STATUS();
                }


                // Means this is the first bulk out in cur calc crc xfer
                if(g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnceShadow == g_stUsbU2HostDBCurPath.ucUsbU2HostDBCalcCrcXferCntOnce)
                {
                    ScalerUsbU2HostGetCurDMOnlyCrcEnResult();
                }

                // Update xfer Len
                pucUsbBulkScsiCmd1[8] = (BYTE)(g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen & 0xff);
                pucUsbBulkScsiCmd1[9] = (BYTE)((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 8) & 0xff);
                pucUsbBulkScsiCmd1[10] = (BYTE)((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 16) & 0xff);
                pucUsbBulkScsiCmd1[11] = (BYTE)((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 24) & 0xff);

                DebugMessageU2HostEHCI("[FAT]DB File Dump Update LBA", GET_U2HOST_FAT32_DB_FILE_DUMP_LBA());

                // Update Logical Block Addr ; Where to set and How to update!!(SET_U2HOST_FAT32_DB_FILE_DUMP_LBA)
                pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() >> 24) & 0xff);
                pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() >> 16) & 0xff);
                pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() >> 8) & 0xff);
                pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() & 0xff);

                // Update block nums to be transferred,pucUsbBulkScsiCmd2[6](High Byte)for 16KB/20KB Each time, Use pucUsbBulkScsiCmd2[7](Low Byte) is enough)
                pucUsbBulkScsiCmd2[7] = (g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 9);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

                ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

                // assign 31Byte cmd to Host Buffer
                ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
                ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
                ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

                // Prepared to Enable QH
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

                // Prepared to Enable qTD 0 CBW
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
            }
            else
            {
                DebugMessageU2HostEHCI("[SCSI] Bulk write Data Stage", 0);

                // ddr2usb xfer enable
                // ScalerSetBit(P93_00_DM_CLIENT_CTRL0, ~_BIT6, _BIT6);


                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1]);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen); // TBD

                // not use for DM Dump data?
                // ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);


                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B0C_BUFFER_POINTER_PAGE0, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_WRITE_FROM_DM_CLIENT_ST_ADDR);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D08_B0C_BUFFER_POINTER_PAGE1, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D09_B0C_BUFFER_POINTER_PAGE2, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D0A_B0C_BUFFER_POINTER_PAGE3, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D0B_B0C_BUFFER_POINTER_PAGE4, 1);

                // Prepared to Enable qTD 0 CBW
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

                // ddr2usb xfer enable
                ScalerSetBit(P93_00_DM_CLIENT_CTRL0, ~_BIT6, _BIT6);

                if(ScalerGetBit(P93_10_DM_CLIENT_CRC_CTRL, _BIT7) == 0x00)
                {
                    // crc enable
                    ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7 | _BIT4), _BIT7);
                    DebugMessageU2HostEHCI("[DM] CRC Enable", 0);
                }
            }

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

            // Re-assign BULK OUT QH
            ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0]);

            ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
        }
    }
#else

    // DebugMessageU2HostEHCI("[DM]enumUsbU2HostDDRReadyState", enumUsbU2HostDDRReadyState);

    if(enumUsbU2HostDDRReadyState == _U2HOST_DDR_READY)
    {
        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
        {
            // DebugMessageU2HostEHCI("[EHCI] Disable Ayns Success .", 0);

            if(GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG() == _FALSE)
            {
                DebugMessageU2HostEHCI("[SCSI] Bulk Write CBW Stage.", 0);

                if(GET_U2HOST_DM_CLIENT_INITIAL() == _FALSE)
                {
                    ScalerUsbU2HostDMClientInitial();
                    SET_U2HOST_DM_CLIENT_INITIAL();
                }

                // Note: Initial value should make sure TRUE
                if(GET_U2HOST_DDR_FRC_CLIENT_EN_STATUS() == _TRUE)
                {
                    // Before Start to Dump 1 new frame, wait 1 IVS to make sure frame data are stored in DDR Ready
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                    // Before Start to Dump 1 new frame, DDR Client should only for u2 client use, so off all Frc client
                    ScalerFRCEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
                    CLR_U2HOST_DDR_FRC_CLIENT_EN_STATUS();
                }

                // Update xfer Len
                pucUsbBulkScsiCmd1[8] = (BYTE)(g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen & 0xff);
                pucUsbBulkScsiCmd1[9] = (BYTE)((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 8) & 0xff);
                pucUsbBulkScsiCmd1[10] = (BYTE)((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 16) & 0xff);
                pucUsbBulkScsiCmd1[11] = (BYTE)((g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 24) & 0xff);

                DebugMessageU2HostEHCI("[FAT]DB File Dump Update LBA", GET_U2HOST_FAT32_DB_FILE_DUMP_LBA());

                // Update Logical Block Addr ;  Where to set and How to update!!(SET_U2HOST_FAT32_DB_FILE_DUMP_LBA)
                pucUsbBulkScsiCmd2[1] = (BYTE)((GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() >> 24) & 0xff);
                pucUsbBulkScsiCmd2[2] = (BYTE)((GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() >> 16) & 0xff);
                pucUsbBulkScsiCmd2[3] = (BYTE)((GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() >> 8) & 0xff);
                pucUsbBulkScsiCmd2[4] = (BYTE)(GET_U2HOST_FAT32_DB_FILE_DUMP_LBA() & 0xff);

                // Update block nums to be transferred,pucUsbBulkScsiCmd2[6](High Byte)for 16KB/20KB Each time, Use pucUsbBulkScsiCmd2[7](Low Byte) is enough)
                pucUsbBulkScsiCmd2[7] = (g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen >> 9);

                // DebugMessageU2HostEHCI("!!BlockNum", pucUsbBulkScsiCmd2[7]);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0]);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x1F);   // 31 Byte Cmd

                ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0x20); // Clear 32 is enough because CBW Contain 31 Byte

                // assign 31Byte cmd to Host Buffer
                ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);
                ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd1, 16);
                ScalerUsbU2HostSetCmdBufData(pucUsbBulkScsiCmd2, 16);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR);

                // Prepared to Enable QH
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

                // Prepared to Enable qTD 0 CBW
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
            }
            else
            {
                DebugMessageU2HostEHCI("[SCSI] Bulk write Data Stage", 0);

                // ddr2usb xfer enable
                // ScalerSetBit(P93_00_DM_CLIENT_CTRL0, ~_BIT6, _BIT6);


                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1]);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);  // Out Token

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // Last qTD in this transfer
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, g_stUsbU2HostDBCurPath.usUsbU2HostDBCurXferLen); // TBD

                // not use for DM Dump data?
                // ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR, 0);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B0C_BUFFER_POINTER_PAGE0, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_WRITE_FROM_DM_CLIENT_ST_ADDR);

                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D08_B0C_BUFFER_POINTER_PAGE1, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D09_B0C_BUFFER_POINTER_PAGE2, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D0A_B0C_BUFFER_POINTER_PAGE3, 1);
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D0B_B0C_BUFFER_POINTER_PAGE4, 1);

                // Prepared to Enable qTD 0 CBW
                ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);

                if(ScalerUsbU2HostGetDMAddrErrFlag() == _TRUE)
                {
                    ScalerUsbU2HostClrDMAddrErrFlag(); // The only place to clear when FW normal running

                    // Retry enable
                    ScalerSetBit(P93_0B_DM_CLIENT_RETRY, ~(_BIT1 | _BIT0), _BIT1);
                    DebugMessageU2HostEHCI("[Dump]! ! ! Retry ! ! !", 0);
                }


                // ddr2usb xfer enable
                ScalerSetBit(P93_00_DM_CLIENT_CTRL0, ~_BIT6, _BIT6);

                // Do not necessary to caculate crc for ECO Solution
                /*
                if(ScalerGetBit(P93_10_DM_CLIENT_CRC_CTRL, _BIT7) == 0x00)
                {
                    // crc enable
                    // ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7 | _BIT4), _BIT7); // BIT4 Cannot here, otherwise dump fail
                    ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7), _BIT7);
                    DebugMessageU2HostEHCI("[DM] CRC Enable", 0);
                }
                */
            }

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

            // Re-assign BULK OUT QH
            ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[0]);

            ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
        }
    }
#endif
#endif
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Write IN QH Setting(CSW)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkScsiWrite10DataInQh(void)
{
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
    // ddr2usb xfer disable
    // ScalerSetBit(P93_00_DM_CLIENT_CTRL0, ~_BIT6, 0x00);
#endif

    if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00)
    {
        DebugMessageU2HostEHCI("[SCSI] WRITE10 Data In CSW", 0);
        // CSW
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0]);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1);  // In Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);       // last qTD
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x0D); // CSW is 13Byte
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR);
        // Prepared to Enable qTD1:CSW
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);
    }
    // Prepared to Enable QH
    ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

    // Re-assign BULK IN QH
    ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[_U2HOST_DEVICE_ATTACH_INDEX]);

    ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : Perform Reset Recovery when CSW Status Phase error or not valid
// Input Value  : CSW BUFFER DATA
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostBulkCswErrResetRecovery(void)
{
    // TBD
    // Reset recovery flow
    // 1. Mass storge reset
    // 2. a Clear Feature HALT to the Bulk-In endpoint
    // 3. a Clear Feature HALT to the Bulk-Out endpoint
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk CSW Status
// Input Value  : CSW BUFFER DATA
// Output Value : None
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostBulkCheckCswStatus(BYTE *pucData)
{
    // CSW 13BYTE
    // 0-3 dCSWSignature: fixed 53425355h (little endian-> Byte0-3:55 53 42 53)
    // 4-7 uldCSWTag: Device shall set thsi field to the value received in the dCBWTag of the associated CBW.
    // 8-11: dCSWDataResidue: Shall not exceed the value sent in the dCBWDataTransferLength
    // 12: ucbCSWStatus: Indicate the success of fail of the cmd.0->susccess;1->fail;2->phase error
    DWORD uldCSWSignature = 0;
    DWORD uldCSWTag = 0;
    BYTE ucbCSWStatus = 0;

    uldCSWSignature = TO_DWORD(pucData[3], pucData[2], pucData[1], pucData[0]);
    uldCSWTag = TO_DWORD(pucData[7], pucData[6], pucData[5], pucData[4]);
    ucbCSWStatus = pucData[12];

    uldCSWTag = uldCSWTag;

    if(uldCSWSignature == 0x53425355)
    {
        if((ucbCSWStatus == 0) || (ucbCSWStatus == 1))
        {
            return _TRUE;
        }
        else
        {
            DebugMessageU2HostEHCI("CSW status Error", ucbCSWStatus);
            return _FALSE;
        }
    }
    else
    {
        DebugMessageU2HostEHCI("CSW Not valid", uldCSWSignature);
        return _FALSE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Get U2Host EHCI_ASYNC_LIST_ADDR Reg Addr - which will use in sys layer EHCI_ASYNC_LIST_ADDR
// Input Value  : None
// Output Value : U2Host EHCI_ASYNC_LIST_ADDR Reg Addr
//----------------------------------------------------------------------------------------------------
/*
WORD ScalerUsbU2HostGetEHCIAsyncListRegAddr(void)
{
    WORD usU2HostRegAddr = 0;
    usU2HostRegAddr = _PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0;

    return usU2HostRegAddr;
}
*/

#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : USB Intrrupt Transfer Operation Setting
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostIntTransOperation(void)
{
    BYTE ucValueTemp1 = 0;

    BYTE ucInterfaceNumUse = 0;

    if(GET_U2HOST_OHCI_INT_TRAN_ACTIVE() == _FALSE)
    {
        SET_U2HOST_OHCI_INT_TRAN_ACTIVE();

        DebugMessageU2Host("[Enum] Int Transaction Active", 0);

        if(g_stUsbU2HostConfigDesInfo.ucNumInterface == 0x01)
        {
            ucInterfaceNumUse = 0x01;
        }
        else
        {
            ucInterfaceNumUse = 0x02;

            // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D03_B04_NEXT_ED, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
        }

        // Clear Int Related USB Memory
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT_ED_0_ST_ADDR, 0x40);
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_MEMORY_SIZE);


        for(ucValueTemp1 = 0; ucValueTemp1 < ucInterfaceNumUse; ucValueTemp1++)
        {
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable INT ED
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1]);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);   // IN Token
        }

        if(ucInterfaceNumUse == 0x01)
        {
            // Initial HCCA Interrupt Table ( Sampling Rate : 8msec)
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 0, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 8, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 16, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 24, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
        }
        else
        {
            // Initial HCCA Interrupt Table ( Sampling Rate : 8msec)
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 0, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 4, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 8, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 12, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);

            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 16, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 20, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 24, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
            ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 28, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
        }


        for(ucValueTemp1 = 0; ucValueTemp1 < ucInterfaceNumUse; ucValueTemp1++)
        {
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable INT ED
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B07_ENDPT, g_pstUsbU2HostEndptDesInfo[ucValueTemp1].ucEndpointAddress);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));

            // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B10_MPS, 0x14);

            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B10_MPS, GET_U2HOST_DEVICE_INT_DATA_SIZE(ucValueTemp1));
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D02_B01_CARRY, 0);

            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, tUSB_OHCI_INT_BUFFER_ADDR_TABLE[ucValueTemp1]);

            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D03_B00_BUF_END, tUSB_OHCI_INT_BUFFER_ADDR_TABLE[ucValueTemp1] + (GET_U2HOST_DEVICE_INT_DATA_SIZE(ucValueTemp1) - 1));

            // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);   // Enable INT ED
        }

        for(ucValueTemp1 = 0; ucValueTemp1 < ucInterfaceNumUse; ucValueTemp1++)
        {
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);   // Enable INT ED
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Intrrupt Transfer Operation Setting
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostIntTransOperationDataHandler(void)
{
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucInterfaceNumUse = 0;

    // DebugMessageU2HostOHCI("[DATA] Int Transaction", 0);

    if(g_stUsbU2HostConfigDesInfo.ucNumInterface == 0x01)
    {
        ucInterfaceNumUse = 0x01;
    }
    else
    {
        ucInterfaceNumUse = 0x02;
    }

    // Data Process for Interrupt Type Endpoint
    for(ucValueTemp1 = 0; ucValueTemp1 < ucInterfaceNumUse; ucValueTemp1++)
    {
        // DebugMessageU2HostOHCI("WDH Bit of TD1 ", ScalerUsbU2HostGetRegBitField(_PDF_04_PT_10C_OHCI_HCINTERRUPT_STS_0, _BIT1));

        if(ScalerUsbU2HostChkIntQueueComplete(_U2HOST_OWNER_OHCI, tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1]) == _TRUE)
        {
            if(ScalerUsbU2HostChkIntQueueErrSts(_U2HOST_OWNER_OHCI, tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1]) == _TRUE)
            {
                // Error Handling
                DebugMessageU2HostOHCI("[Err] Periodic Data Err , Interface No. = ", ucValueTemp1);

                CLR_U2HOST_OHCI_INT_TRAN_ACTIVE();
                CLR_U2HOST_TRANSFER_STATUS();


                ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable INT ED

                return;
            }
            else
            {
                // Get Data from Buffer
                g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength = GET_U2HOST_DEVICE_INT_DATA_SIZE(ucValueTemp1);
                ScalerUsbU2HostGetBufferBulkData(tUSB_OHCI_INT_BUFFER_ADDR_TABLE[ucValueTemp1], 0x00, g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData, g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength);

                DebugMessageU2HostOHCI("[Data] Detect Periodic Data , Device No. = ", ucValueTemp1);
                DebugMessageU2HostOHCI("[Data] Periodic Data Size = ", g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength);

                for(ucValueTemp2 = 0; ucValueTemp2 < g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength; ucValueTemp2++)
                {
                    DebugMessageU2HostOHCI("[Data] Periodic Data Content", g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[ucValueTemp2]);
                }
            }
        }
    }


    // Prepare for next Int TD Process
    for(ucValueTemp1 = 0; ucValueTemp1 < ucInterfaceNumUse; ucValueTemp1++)
    {
        // Re-Active Interrupt TD
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, tUSB_OHCI_INT_BUFFER_ADDR_TABLE[ucValueTemp1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp1], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp1]);
    }

    // Return HID Reply content to users
    for(ucValueTemp1 = 0; ucValueTemp1 < ucInterfaceNumUse; ucValueTemp1++)
    {
        if(ucValueTemp1 == 0)
        {
            if(GET_U2HOST_OHCI_1ST_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_MOUSE)
            {
                // For User Use,TBD - MouseHIDContent Info Mapping to g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[];

                /*
                // For example,
                for(i = 0; i < g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength; i++)
                {
                    g_ucMouseHIDContent[i] = g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[i];
                }
                */
            }
            else if(GET_U2HOST_OHCI_1ST_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_KEYBOARD)
            {
                // For User Use,TBD - KeyBoardHIDContent Info Mapping to g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[];

                /*
                // For example
                for(i = 0; i < g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength; i++)
                {
                    g_ucKeyBoardHIDContent[i] = g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[i];
                }
                */
            }
            else
            {
                // Not define
            }
        }
        else if(ucValueTemp1 == 1)
        {
            if(GET_U2HOST_OHCI_2ND_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_MOUSE)
            {
                // For User Use,TBD - MouseHIDContent Info Mapping to g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[];

                /*
                // For example,
                for(i = 0; i < g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength; i++)
                {
                    g_ucMouseHIDContent[i] = g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[i];
                }
                */
            }
            else if(GET_U2HOST_OHCI_2ND_INTERFACE_TYPE() == _U2HOST_OHCI_INTERFACE_KEYBOARD)
            {
                // For User Use,TBD - KeyBoardHIDContent Info Mapping to g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[];

                /*
                // For example
                for(i = 0; i < g_pstUsbU2HostIntEDInfo[ucValueTemp1].ucDataLength; i++)
                {
                    g_ucKeyBoardHIDContent[i] = g_pstUsbU2HostIntEDInfo[ucValueTemp1].pucData[i];
                }
                */
            }
            else
            {
                // Not define
            }
        }
        else
        {
            // Not define
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Set Idle Process,ex.Mouse G304(total 3 interface,interfaceindex=1 is mouse) must required,and others are not necessary.-cai add
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetIdle(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE pucUsbCtrlCmd[8] =
    {
        0x21,               // Data transfer direction : host-to-device
        0x0A,               // Set Idle
        0x00,
        0x00,
        0x00,               // interface Index
        0x00,
        0x00, 0x00          // Transfer Len 0
    };

    DebugMessageU2Host("[Enum] Set IDLE", GET_U2HOST_SEC_REPORT_DESC());

    // 1st Interface HID Info
    if(GET_U2HOST_SEC_REPORT_DESC() == _FALSE)
    {
        pucUsbCtrlCmd[4] = 0x00;
    }
    else
    {
        pucUsbCtrlCmd[4] = 0x01; // 0x01
    }

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
        // Not support
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);   // Receive empty packet
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);


        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Get HID Device Report Descriptor Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetHIDReport(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    WORD usUsbReceiveDataLen = 0;

    BYTE pucUsbCtrlCmd[8] =
    {
        0x81,               // Data transfer direction : device-to-host
        0x06,               // Get Descriptor
        0x00,               //
        0x22,               // Get HID Report
        0x00,               // Interface
        0x00,
        0x00, 0x00          // Transfer Len L,H
    };

    DebugMessageU2Host("[Enum] Get HID Report", GET_U2HOST_SEC_REPORT_DESC());

    // 1st Interface HID Info
    if(GET_U2HOST_SEC_REPORT_DESC() == _FALSE)
    {
        pucUsbCtrlCmd[4] = 0x00; // Interface No.

        // Transfer len Low Byte
        pucUsbCtrlCmd[6] = g_pstUsbU2HostHIDDesInfo[0].usHIDReportLength & 0xff;

        // Transfer len High Byte
        pucUsbCtrlCmd[7] = (g_pstUsbU2HostHIDDesInfo[0].usHIDReportLength >> 8) & 0xff;
    }
    else // 2nd Interface HID Info
    {
        pucUsbCtrlCmd[4] = 0x01; // Interface No.

        // Transfer len Low Byte
        pucUsbCtrlCmd[6] = g_pstUsbU2HostHIDDesInfo[1].usHIDReportLength & 0xff;

        // Transfer len High Byte
        pucUsbCtrlCmd[7] = (g_pstUsbU2HostHIDDesInfo[1].usHIDReportLength >> 8) & 0xff;
    }

    usUsbReceiveDataLen = pucUsbCtrlCmd[6] + pucUsbCtrlCmd[7];


    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
        // Not support
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (usUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
    }
    else
    {
        // No defined
    }
}

//--------------------------------------------------
// Description  : Get HID Descriptor Info.
// Input Value  : HID Index, whole HID Descriptor Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetHIDDesInfo(BYTE ucHidIdx, BYTE *pucData)
{
    g_pstUsbU2HostHIDDesInfo[ucHidIdx].ucDescripType1 = pucData[1];
    g_pstUsbU2HostHIDDesInfo[ucHidIdx].usBcdHID = TO_WORD(pucData[3], pucData[2]);
    g_pstUsbU2HostHIDDesInfo[ucHidIdx].ucNumDescriptor = pucData[5];
    g_pstUsbU2HostHIDDesInfo[ucHidIdx].ucDescripType2 = pucData[6];

    if(TO_WORD(pucData[8], pucData[7]) <= 256)
    {
        g_pstUsbU2HostHIDDesInfo[ucHidIdx].usHIDReportLength = TO_WORD(pucData[8], pucData[7]);
    }
    else
    {
        // The current supported Max Ctrl buffer size is 256 Bytes
        g_pstUsbU2HostHIDDesInfo[ucHidIdx].usHIDReportLength = 256;
        DebugMessageU2Host("[Enum][Hid] Warning: HIDReportLength > 256", TO_WORD(pucData[8], pucData[7]));
    }

    if(pucData[0] != _U2HOST_ENUM_DES_LEN_HID)
    {
        DebugMessageU2Host("[Enum][Hid] Warning: HID Des Len != 0x09", pucData[0]);
    }
}


#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : USB2 Host Color Analyzer State Machine
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostColorOperation(void)
{
    switch(GET_U2HOST_COLOR_STATE())
    {
        case _U2HOST_COLOR_ADD_BULK_ED:

            ScalerUsbU2HostAddBulkED();
            SET_U2HOST_COMPLETE_STATUS();   // Non-Reply from Device
            break;

        case _U2HOST_COLOR_ADD_INT_ED:

            ScalerUsbU2HostAddIntED();
            SET_U2HOST_COMPLETE_STATUS();   // Non-Reply from Device
            break;

        case _U2HOST_COLOR_IDLE:

            SET_U2HOST_COMPLETE_STATUS();   // Non-Reply from Device
            break;

        case _U2HOST_COLOR_CONTROL_OUT:

            ScalerUsbU2HostUserControlOut(_U2HOST_DEVICE_ATTACH_INDEX);

            break;

        case _U2HOST_COLOR_CONTROL_IN:

            ScalerUsbU2HostUserControlIn(_U2HOST_DEVICE_ATTACH_INDEX);
            break;

        case _U2HOST_COLOR_BULK_OUT:

            ScalerUsbU2HostUserBulkOut();
            break;

        case _U2HOST_COLOR_BULK_IN:

            ScalerUsbU2HostUserBulkIn();
            break;

        case _U2HOST_COLOR_INT_OUT:

            ScalerUsbU2HostUserIntOut();
            break;

        case _U2HOST_COLOR_INT_IN:

            ScalerUsbU2HostUserIntIn();
            break;

        default:

            break;
    }
}


//----------------------------------------------------------------------------------------------------
// Description  : USB Get Control Line State Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetLineCoding(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = _U2HOST_ENUM_GET_LINE_CODE;
    ucDeviceNo = ucDeviceNo;

    DebugMessageU2Host("[Enum] Get Line Conding", 0);

    BYTE pucUsbCtrlCmd[8] =
    {
        0xA1,               // bmRequestType, bit[7]: Data transfer direction = 1'b1, device-to-host
        0x21,               // bRequest: GET_LINE_CODING
        0x00, 0x00,         // wValue: should be 0x00
        0x00, 0x00,         // wIndex: Interface
        0x00, 0x00,         // wLength
    };


    // Update Receive Data Length
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;

    if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        // Initial for OHCI Control TD 1 : int Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);

        // Initial for OHCI Control TD 2 : out Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        // Clr and Set Cmd Data into Ctrl Setup Buffer (Token)
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 8);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
    }
    else
    {
        // No defined
    }
}

//--------------------------------------------------
// Description  : Get Line Coding Info.
// Input Value  : whole Get_Line_Coding Data
// Output Value : None
//--------------------------------------------------
void ScalerUsbU2HostGetLineCodeInfo(BYTE *pucData)
{
    g_stUsbU2HostGetLineCodeInfo.ulDTERate = TO_DWORD(pucData[3], pucData[2], pucData[1], pucData[0]);
    g_stUsbU2HostGetLineCodeInfo.ucCharFormat = pucData[4];
    g_stUsbU2HostGetLineCodeInfo.ucParityType = pucData[5];
    g_stUsbU2HostGetLineCodeInfo.ucDataBits = pucData[6];
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Set Line Coding Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetLineCoding(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    BYTE ucUsbReceiveDataLen = _U2HOST_ENUM_SET_LINE_CODE;
    ucDeviceNo = ucDeviceNo;

    DebugMessageU2Host("[Enum] Set Line Conding", 0);

    BYTE pucUsbCtrlCmd[8] =
    {
        0x21,                       // bmRequestType, bit[7]: Data transfer direction = 1'b0, host-to-device
        0x20,                       // bRequest: SET_LINE_CODING
        0x00, 0x00,                 // wValue: should be 0x00
        0x00, 0x00,                 // wIndex: Interface
        0x00, 0x00,                 // wLength
    };

    // Update Receive Data Length
    pucUsbCtrlCmd[6] = ucUsbReceiveDataLen;

    BYTE pucLineCodeStr[7] =
    {
        0x00, 0x96, 0x00, 0x00,     // dwDTERate, set to Baud rate 38400 bits/s (as CA-410 spec. requested)
        0x02,                       // bCharFormat, set to 2 Stop bits (as CA-410 spec. requested)
        0x02,                       // bParityType, set to Parity Even (as CA-410 spec. requested)
        0x07,                       // bDataBits, set to Data bits 7 (as CA-410 spec. requested)
    };

    if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        // Initial for OHCI Control TD 1 : Out Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 1);

        // Initial for OHCI Control TD 2 : IN Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2] + _U2HOST_OHCI_TD_SIZE);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (ucUsbReceiveDataLen - 1)));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);   // Receive empty packet
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

        // Clr and Set Cmd Data into Ctrl Setup Buffer (Token)
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 8);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Clr and Set Cmd Data into Ctrl Buffer (Data)
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 8);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0);
        ScalerUsbU2HostSetCmdBufData(pucLineCodeStr, 7);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT1, _BIT1);
    }
    else
    {
        // Not defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Set Control Line State Process
// Input Value  : USB Host Controller Type : EHCI or OHCI , Device Number
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetControlLineState(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo)
{
    ucDeviceNo = ucDeviceNo;
    DebugMessageU2Host("[Enum] Set Control Line State", 0);

    BYTE pucUsbCtrlCmd[8] =
    {
        0x21,               // bmRequestType, bit[7]: Data transfer direction = 1'b0, host-to-device
        0x22,               // Get Descriptor
        0x00, 0x00,         // wValue: Control Signal Bit Map
        0x00, 0x00,         // wIndex: Interface
        0x00, 0x00,         // wLength: should be 0x00
    };

    if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);   // Receive empty packet
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 0);

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, _BIT1);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, (_BIT1 | _BIT0));

        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);

        // Clr and Set Cmd Data into Ctrl Setup Buffer (Token)
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 8);
        ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR, 0);
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        // Enable Control ED
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

        // Enable Control List
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Initial Bulk Out/In ED (OHCI)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostAddBulkED(void)
{
    // 1. Initial Bulk Out ED
    BYTE ucBulkOutEndpt = GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX);
    // Endpt 2 is Bulk Out -> This should be modified
    BYTE ucBulkOutMPS = g_pstUsbU2HostEndptDesInfo[2].usMaxPacketSize;

    // Disable ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B07_ENDPT, ucBulkOutEndpt);

    // Set Direction = 2'b01 (Out)
    // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0B_PID_CODE, 1);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B10_MPS, ucBulkOutMPS);
    // Set ToggleCarry to initial (DATA 0)
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B01_CARRY, 0);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

    // 2. Initial Bulk In ED
    BYTE ucBulkInEndpt = GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX);
    // Endpt 1 is Bulk In -> This should be modified
    BYTE ucBulkInMPS = g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize;

    // Disable ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B07_ENDPT, ucBulkInEndpt);

    // Set Direction = 2'b10 (In)
    // ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0B_PID_CODE, 2);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B10_MPS, ucBulkInMPS);
    // Set ToggleCarry to initial (DATA 0)
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B01_CARRY, 0);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);
}

//----------------------------------------------------------------------------------------------------
// Description  : Initial Int Out/In ED (OHCI)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostAddIntED(void)
{
    // 1. Fill HCCA Interrupt Table (Sampling Rate : 8 ms)
    // Clear Table
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_MEMORY_SIZE);

    // Fill in Table (INT ED0, INT In)
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 0, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 8, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 16, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 24, tUSB_OHCI_INT_ED_ADDR_TABLE[0]);
    // Fill in Table (INT ED1, INT Out)
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 4, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 12, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 20, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);
    ScalerUsbU2HostSetOHCIHccaIntTab(_U2HOST_OHCI_HCCA_MEMORY_ADDR, 28, tUSB_OHCI_INT_ED_ADDR_TABLE[1]);

    // 2. Initial Int Out ED
    // Clear INT ED0 + INT TD0 (INT In)
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT_ED_0_ST_ADDR, _U2HOST_OHCI_ED_SIZE);
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT_TD_0_ST_ADDR, _U2HOST_OHCI_TD_SIZE);

    // Disable INT ED0
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B07_ENDPT, g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B10_MPS, g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);
    // PID: IN Token
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_INT0_BUFFER_ST_ADDR);

    // 3. Initial Int Out ED
    // Clear INT ED1 + INT TD1 (INT Out)
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT_ED_1_ST_ADDR, _U2HOST_OHCI_ED_SIZE);
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT_TD_1_ST_ADDR, _U2HOST_OHCI_TD_SIZE);

    // Disable INT ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[1]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B07_ENDPT, g_pstUsbU2HostEndptDesInfo[0].ucEndpointAddress);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B10_MPS, g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);
    // PID: OUT Token
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 1);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_INT1_BUFFER_ST_ADDR);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB User Control Out Process (from User Interface)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostUserControlOut(BYTE ucDeviceNo)
{
    BYTE ucTransmitDataLen = g_ucUsbU2HostColorWriteReqLen;

    // Disable Control ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[2]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

    // Clear Control Buffer
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, ucTransmitDataLen);
    // Set Control Out content to Control Buffer
    ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(g_pucUsbU2HostColorWriteReqData, ucTransmitDataLen);
    // Set Control Out DataLen to TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D03_B00_BUF_END, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + ucTransmitDataLen - 1);

    // Enable Control ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

    // Enable Control List
    ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB User Control In Process (from User Interface)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostUserControlIn(BYTE ucDeviceNo)
{
    BYTE ucReceiveDataLen = g_stUsbU2HostDeviceInfo.ucMaxPacketSize0;

    // Disable Control ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_CTRL_TD_ADDR_TABLE[1]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + (64 - 1)));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

    // Clear Control Buffer
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR, ucReceiveDataLen);
    // Set Control In DataLen to TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D03_B00_BUF_END, _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + ucReceiveDataLen - 1);

    // Enable Control ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucDeviceNo], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

    // Enable Control List
    ScalerUsbU2HostSetRegBitField(_PDF_04_PT_108_OHCI_HCCOMMAND_STS_0, ~_BIT1, _BIT1);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk Out Process (from User Interface)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostUserBulkOut(void)
{
    BYTE ucTransmitDataLen = g_ucUsbU2HostColorWriteReqLen;

    ScalerUsbU2HostSetRegDword(_PDF_04_PT_128_OHCI_HCBULK_ED_0, tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0]);
    // Endpt 1 is Bulk In -> This should be modified
    BYTE ucBulkInMPS = g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize;

    // Disable Bulk ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B07_ENDPT, GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B10_MPS, ucBulkInMPS);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);
    // Initial for OHCI Control TD 1 : Out Token
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 1);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer
    // MSb = 1'b0: acquires the Data Toggle bit from ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_BULK_OUT_BUFFER_ST_ADDR);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

    // Clear Bulk Out Buffer
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_BULK_OUT_BUFFER_ST_ADDR, ucTransmitDataLen);
    // Set Bulk Out content to Bulk Out Buffer
    ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_BULK_OUT_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(g_pucUsbU2HostColorWriteReqData, ucTransmitDataLen);
    // Set Bulk Out DataLen to TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D03_B00_BUF_END, _U2HOST_OHCI_BULK_OUT_BUFFER_ST_ADDR + ucTransmitDataLen - 1);

    // Enable Bulk ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

    // Enable Bulk List
    ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT2, _BIT2);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Bulk In Process (from User Interface)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostUserBulkIn(void)
{
    BYTE ucReceiveDataLen = 128;
    // Endpt 1 is Bulk In -> This should be modified
    BYTE ucBulkInMPS = g_pstUsbU2HostEndptDesInfo[1].usMaxPacketSize;

    ScalerUsbU2HostSetRegDword(_PDF_04_PT_128_OHCI_HCBULK_ED_0, tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0]);

    // Disable Bulk ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0]);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS, GET_U2HOST_DEVICE_ADDRESS(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B07_ENDPT, GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0D_SPEED, GET_U2HOST_DEVICE_SPEED(_U2HOST_DEVICE_ATTACH_INDEX));
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B10_MPS, ucBulkInMPS);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);
    // Initial for OHCI Control TD 1 : Out Token
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING, 1);   // last data packet maybe smaller than the defined buffer
    // MSb = 1'b0: acquires the Data Toggle bit from ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D02_B04_NEXT_TD, 0);

    // Clear Bulk In Buffer
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR, ucReceiveDataLen);
    // Set Bulk In DataLen to TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D03_B00_BUF_END, _U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR + ucReceiveDataLen - 1);

    // Enable Bulk ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);

    // Enable Bulk List
    ScalerUsbU2HostSetRegBitField(ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(), ~_BIT2, _BIT2);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB User Interrupt Out Process (from User Interface)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostUserIntOut(void)
{
    BYTE ucTransmitDataLen = g_ucUsbU2HostColorWriteReqLen;

    // Disable INT Out ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_INT1_BUFFER_ST_ADDR);

    // Clear INT Out Buffer
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT1_BUFFER_ST_ADDR, ucTransmitDataLen);

    // Set INT Out content to INT Out Buffer
    ScalerUsbU2HostSetOHCIMemoryAddr(_U2HOST_OHCI_INT1_BUFFER_ST_ADDR, 0);
    ScalerUsbU2HostSetCmdBufData(g_pucUsbU2HostColorWriteReqData, ucTransmitDataLen);
    // Set INT Out DataLen to TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_INT1_BUFFER_ST_ADDR + ucTransmitDataLen - 1));

    // Fill in INT Out ED with INT Out TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[1]);
    // Enable INT Out ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB User Interrupt Out Process (from User Interface)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostUserIntIn(void)
{
    // Endpt 0 is Int In -> This should be modified
    BYTE ucReceiveDataLen = g_pstUsbU2HostEndptDesInfo[0].usMaxPacketSize;

    // Disable INT In ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);

    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1A_ERR_CNT, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, _U2HOST_OHCI_INT0_BUFFER_ST_ADDR);

    // Clear INT In Buffer
    ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_INT0_BUFFER_ST_ADDR, ucReceiveDataLen);
    // Set INT In DataLen to TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_INT0_BUFFER_ST_ADDR + ucReceiveDataLen - 1));

    // Fill in INT In ED with INT In TD
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[0]);
    // Enable INT In ED
    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[0], _U2HOST_OHCI_ED_D00_B0E_SKIP, 0);
}

#endif


//----------------------------------------------------------------------------------------------------
// Description  : Check Interrupt Type Queue Error Status
// Input Value  : Host Controller Type : EHCI / OHCI , Int InterfaceNum
// Output Value : _TRUE -> Error Happened ; _FALSE -> Error Not Happened
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostChkIntQueueErrSts(EnumUsbU2HostOwner enumOwner, BYTE ucInterfaceNumUse)
{
    ucInterfaceNumUse = ucInterfaceNumUse;

    if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_INT_TRANS_OPERATION)
        {
            if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucInterfaceNumUse], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) != 0x00)
            {
                DebugMessageU2HostEHCI("[Err] Int transfer Err , Error Code =", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucInterfaceNumUse], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
/*
                if(ScalerUsbU2HostGetOHCIMemoryField(usAddr, _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x05) // no response
                {
                    ScalerUsbU2HostSetOHCIMemoryField(usAddr, _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE, 0);
                    DebugMessageU2HostOHCI("ohci INT ed halt bit", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D02_B00_HALTED));

                    // clr halt bit
                    ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[1], _U2HOST_OHCI_ED_D02_B00_HALTED, 0);

                    // return _FALSE;
                }
*/
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        else if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION)
        {
            BYTE ucColorState = GET_U2HOST_COLOR_STATE();

            switch(ucColorState)
            {
                case _U2HOST_COLOR_INT_OUT:

                    if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                    {
                        return _FALSE;
                    }
                    else
                    {
                        DebugMessageU2HostOHCI("[OHCI][Err] INT_OUT_TD Error", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
                        return _TRUE;
                    }

                    break;

                case _U2HOST_COLOR_INT_IN:

                    if(ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE) == 0x00)
                    {
                        return _FALSE;
                    }
                    else
                    {
                        DebugMessageU2HostOHCI("[OHCI][Err] INT_IN_TD Error", ScalerUsbU2HostGetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE));
                        return _TRUE;
                    }

                    break;

                default:
                    break;
            }
        }
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
    }
    else
    {
        // No define
        return _TRUE;
    }
    return _TRUE;
}

//----------------------------------------------------------------------------------------------------
// Description  : Check Interrupt Type Queue is Executed Finish or Not
// Input Value  : Host Controller Type : EHCI / OHCI , Int InterfaceNum
// Output Value : _TRUE -> Execute Finished ; _FALSE -> Execute not yet Finished
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostChkIntQueueComplete(EnumUsbU2HostOwner enumOwner, BYTE ucInterfaceNumUse)
{
    WORD usHccaDoneHead = 0;
    ucInterfaceNumUse = ucInterfaceNumUse;

    if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_D21_B00_DONE_HEAD);

        if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_INT_TRANS_OPERATION)
        {
            while(usHccaDoneHead != 0)
            {
                if(usHccaDoneHead == tUSB_OHCI_INT_TD_ADDR_TABLE[ucInterfaceNumUse])
                {
                    return _TRUE;
                }
                usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(usHccaDoneHead, _U2HOST_OHCI_TD_D02_B04_NEXT_TD);
            }
            return _FALSE;
        }

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        else if(GET_U2HOST_COMMUNICATE_STATE() == _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION)
        {
            BYTE ucColorState = GET_U2HOST_COLOR_STATE();

            while(usHccaDoneHead != 0)
            {
                if(ucColorState == _U2HOST_COLOR_INT_OUT)
                {
                    if(usHccaDoneHead == tUSB_OHCI_INT_TD_ADDR_TABLE[1])
                    {
                        return _TRUE;
                    }
                }
                else if(ucColorState == _U2HOST_COLOR_INT_IN)
                {
                    if(usHccaDoneHead == tUSB_OHCI_INT_TD_ADDR_TABLE[0])
                    {
                        g_ucUsbU2HostColorReadRspLen = ScalerUsbU2HostGetRspDataLen(_U2HOST_OWNER_OHCI);
                        return _TRUE;
                    }
                }
                usHccaDoneHead = ScalerUsbU2HostGetOHCIMemoryField(usHccaDoneHead, _U2HOST_OHCI_TD_D02_B04_NEXT_TD);
            }
        }
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
    }
    else
    {
        // No define
        return _FALSE;
    }
    return _FALSE;
}
#endif // End of #if(_USB2_HOST_OHCI_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------
// Description  : CLR Content for remove device
// Input Value  : Host Controller Type : EHCI / OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostClrContent(EnumUsbU2HostOwner enumOwner)
{
    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _DISABLE);
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        CLR_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG();
        CLR_U2HOST_NEXT_STATE_AFTER_HALT();
        g_ucUsbU2HostScsiFlowFlag = 0;
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
        CLR_U2HOST_DB_CUR_PATH_FINISH_STATE();
        CLR_U2HOST_DM_CLIENT_INITIAL();
        SET_U2HOST_DB_CUR_PATH(_U2HOST_DB_NONE);

        g_bUsbU2HostDummyRegBit0 = _FALSE;
        g_bUsbU2HostFirstUpdateFlag = _FALSE;

        // ddr2usb xfer Disable
        ScalerSetBit(P93_00_DM_CLIENT_CTRL0, ~_BIT6, 0x00);

        // Make sure initial value flag is True
        SET_U2HOST_DDR_FRC_CLIENT_EN_STATUS();
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
        // crc disble
        ScalerSetBit(P93_10_DM_CLIENT_CRC_CTRL, ~(_BIT7 | _BIT4), 0x00);

        memset(g_pucUsbU2HostDMCrcResultGolden, 0, sizeof(g_pucUsbU2HostDMCrcResultGolden));
        memset(g_pucUsbU2HostDMCrcResultTBD, 0, sizeof(g_pucUsbU2HostDMCrcResultTBD));
#endif // End of #if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
#endif // End of #if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        CLR_U2HOST_SEC_REPORT_DESC();
        CLR_U2HOST_OHCI_INT_TRAN_ACTIVE();
        SET_U2HOST_OHCI_1ST_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_NONE);
        SET_U2HOST_OHCI_2ND_INTERFACE_TYPE(_U2HOST_OHCI_INTERFACE_NONE);

        // Clear All OHCI Memory
        ScalerUsbU2HostMemoryClear(_U2HOST_MEMORY_ST_ADDR, _U2HOST_OHCI_MEMORY_SIZE + _U2HOST_MEMORY_OHCI_ST_ADDR_OFFSET);
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_MEMORY_SIZE);
#endif
    }
}


//----------------------------------------------------------------------------------------------------
// Description  : Reset Mac After Insert
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostMacReset(void)
{
    BYTE ucDelayTemp = 200;

    // Reset USB MAC
    ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT0, 0x00);
    ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT0, _BIT0);

    // USB Clock Enable
    ScalerSetBit(PDF_01_USB_DIVIDER, ~_BIT7, _BIT7);

    DELAY_XUS(300);
    // ScalerTimerDelayXms(30);

    // Host Contorller has port power control switches(EHCI Hub Power On?)
    ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, ~_BIT4, _BIT4);

    // Configuration Flag (CF) set to 1 for port routing control (all ports attached to EHCI) - Make D+ Pull High
    ScalerUsbU2HostSetRegBitField(_PDF_04_PT_050_EHCI_CONFIG_FLAG_0, ~_BIT0, _BIT0);

    // Wait for port owner switch to EHCI or Time-out(1msec)
    while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, _BIT5) == _BIT5) && (--ucDelayTemp != 0))
    {
        DELAY_5US();
    }

    // 0xDF04_0050_0[0] =1 -> D+ High.Need to maintain some time before Port Reset(0xDF04_0054_1[0] = 1,D+ Low. Setting in RhPortEnable()),Test 30ms is OK, 10ms fail
    ScalerTimerDelayXms(100);

    SET_U2HOST_OWENER(_U2HOST_OWNER_EHCI);
    DebugMessageU2Host("[Sys] Port Owner Switch to EHCI", 0);
}


//----------------------------------------------------------------------------------------------------
// Description  : USB Power Control Sequence
// Input Value  : USB Host Controller Type : EHCI or OHCI , Power ON/OFF Action
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostPowerControl(EnumUsbU2HostOwner enumMode, bit bOn)
{
    if(bOn == _ON)
    {
        // General Setting for Power On
        {
            // USB Clock Enable
            ScalerSetBit(PDF_01_USB_DIVIDER, ~_BIT7, _BIT7);

            // Reset USB PHY
            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT1, 0x00);
            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT1, _BIT1);

            // Reset USB MAC
            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT0, 0x00);
            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT0, _BIT0);

            // Need to delay some time After Reset, otherwise, below dphy reg maybe set fail
            DELAY_XUS(300);

            // CAITEST
            // ScalerSetBit(PDF_67_U2HOST_UTMI_STRAP_SIG_REG, ~_BIT0, 0x00);

            // --- Option_1: Z0 auto Calibration - Eye test will fail ---
            // Enable Z0 auto Calibration
            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT7), _BIT7);

            // --- Option_2: Z0 Manual Mode - Eye test passed ---
            // disable Z0 auto Calibration
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT7), 0x00);

            // Z0 Mannaul Mode
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6), 0x00);
            // Z0 ~= 62-2x / Z0 Mannaul Mode _BIT6 = 0
            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5)); // eye fail
            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3));// eye Pass
            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));//eye Pass ,J = 382mv

            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2)); // Function OK but eye little high(fail)
            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3)); // eye Pass Not Stable - J = 414mv

            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3 | _BIT2)); //eye Pass  -  J = 408mv
            // ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3)); // eye Pass J = 389mv

            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT2)); // eye Pass select this J = 393mv

            // HS TX output swing adjustment
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E4_USB_PHY_CTR_REG_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_USB2_HOST_PORT_HSTX_SWING));

            // Host disconnect detect period
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_F7_USB_PHY_CTR_REG_0F, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            DebugMessageU2Host("dis-connect det period", ScalerUsbU2HostGetPhyRegBitField(_PDF_62_PT_F7_USB_PHY_CTR_REG_0F, (_BIT5 | _BIT4)));

            // dis-connect Level 0110->625; 0111 ->656
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E7_USB_PHY_CTR_REG_27, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

            DebugMessageU2Host("dis-connect Level", ScalerUsbU2HostGetPhyRegByte(_PDF_62_PT_E7_USB_PHY_CTR_REG_27));

            // Objective value of sensitivity calibration
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E7_USB_PHY_CTR_REG_27, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);


            // Force To Calibration After Set REG_SENH[3:0] & REG_SEND[3:0]
            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_10, ~(_BIT2), 0x00);
            DebugMessageU2Host("Phy Calibration1", ScalerUsbU2HostGetPhyRegByte(_PDF_62_PT_E0_USB_PHY_CTR_REG_10));

            ScalerUsbU2HostSetPhyRegBitField(_PDF_62_PT_E0_USB_PHY_CTR_REG_10, ~(_BIT2), _BIT2);
            DebugMessageU2Host("Phy Calibration2", ScalerUsbU2HostGetPhyRegByte(_PDF_62_PT_E0_USB_PHY_CTR_REG_10));
        }

        // OHCI Will Also Need (enum Mode = EHCI) first
        if(enumMode == _U2HOST_OWNER_EHCI)
        {
            // Contain Configuration Flag (CF) set to 1 for port routing control (all ports attached to EHCI)
            ScalerUsbU2HostPortOwnerSwitch(_U2HOST_OWNER_EHCI);

            DebugMessageU2Host("[EHCI] Power On", 0);
            DebugMessageU2Host("[EHCI] Connect Detection", 0);
        }
        else if(enumMode == _U2HOST_OWNER_OHCI)
        {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
            // Contain Configuration Flag (CF) set to 0 for port routing control (all ports attached to OHCI)
            ScalerUsbU2HostPortOwnerSwitch(_U2HOST_OWNER_OHCI);

            // Ports are always powered on when he host controller is powered on
            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_148_OHCI_HCRHDESCRIPTORA_1, ~_BIT1, _BIT1);

            // Turn-On the Root Hub Port Power for OHCI
            ScalerUsbU2HostSetOHCIRhStsRegBitField(_PDF_04_PT_150_OHCI_HCRHSTATUS_2, _BIT0);

            // HC Switch to Operational State
            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_104_OHCI_HCCONTROL_0, ~(_BIT7 | _BIT6), _BIT7);

            // DebugMessageU2HostOHCI("[OHCI] Power On", 0);
#endif
        }
        else
        {
            // no defined
        }
    }
    else
    {
        if(enumMode == _U2HOST_OWNER_EHCI)
        {
            DebugMessageU2HostEHCI("[EHCI] Power Off", 0);
        }
        else if(enumMode == _U2HOST_OWNER_OHCI)
        {
            // Turn-Off the Root Hub Port Power for OHCI
            // ScalerUsbU2HostSetRegBitField(_PDF_04_PT_150_OHCI_HCRHSTATUS_0, ~_BIT0, _BIT0);
            DebugMessageU2HostOHCI("[OHCI] Power Off", 0);
        }
        else
        {
            // no defined
        }

        // Reset USB PHY - Close U2Host phy to Save Power
        ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT1, 0x00); // TBD

        // Reset USB MAC - Close U2Host mac to Save Power
        ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~_BIT0, 0x00); // TBD

        SET_U2HOST_MODE_STATE(_U2HOST_MODE_STATE_POWER_OFF);
        DebugMessageU2Host("[Mode State] MODE_STATE_POWER_OFF", 0);
    }
}


//----------------------------------------------------------------------------------------------------
// Description  : USB Connect Status Check
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostConnectCheck(EnumUsbU2HostOwner enumMode)
{
    // Even OHCI mode will meet (enum Mode = EHCI) in first loop, since default OWNER == EHCI
    if(enumMode == _U2HOST_OWNER_EHCI)
    {
        // Check if EHCI Root Hub Connect Status Chg
        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT1) == _BIT1)
        {
            // Clr EHCI Root Hub Connect Status Change flag
            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, ~_BIT1, _BIT1);

            // Check if EHCI Device present (Connected)
            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT0) == _BIT0)
            {
                DebugMessageU2Host("[EHCI] Root Hub Detect Insert Device.", 0);
                SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_INSERT_DEVICE);
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
                // Record EHCI Connect Status for User
                SET_U2HOST_EHCI_CONNECT();
#endif
            }
            else
            {
                DebugMessageU2Host("[EHCI] Root Hub Detect Remove Device.", 0);
                SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_REMOVE_DEVICE);
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
                // Record EHCI Connect Status for User
                CLR_U2HOST_EHCI_CONNECT();
#endif
            }
        }
        else
        {
            // Check if CTS Flow Enable
            if((ScalerGetByte(PDF_01_USB_DIVIDER) & _BIT5) == _BIT5)
            {
                g_ucUsbU2HostTestIndex = 0x00;
                SET_U2HOST_CTS_EN_STATUS();
                DebugMessageU2Host("[CTS] Test Start", 0);

                while((GET_U2HOST_CTS_EN_STATUS() == _TRUE) && (GET_U2HOST_MODE_STATE() == _U2HOST_MODE_STATE_POWER_OFF))
                {
                    ScalerUsbU2HostCtsModeJudge();

                    if(GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_TEST) // Test J/K/SE0_NAK/Packet/Force_Enable
                    {
                        ScalerUsbU2HostCtsTestModeContol();

                        // ScalerSetBit(PDF_01_USB_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0);
                        ScalerSetByte(PDF_01_USB_DIVIDER, (ScalerGetByte(PDF_01_USB_DIVIDER) & 0x70));
                    }
                    else if((GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_ENUM) || (GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_SIGN_GET_DEV_DESC))
                    {
                        // ScalerSetBit(PDF_01_USB_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0); // Clr CTS Mode Status
                        ScalerSetByte(PDF_01_USB_DIVIDER, 0xA0); // Correct operation Flag
                        ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0);

                        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT0) == _BIT0)
                        {
                            g_ucUsbU2HostPreUsbTestMode = 0x00;
                            g_ucUsbU2HostPreProTestCtrl = 0x00;
                            DebugMessageU2Host("[CTS] Enumeration Start", 0);

                            SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_INSERT_DEVICE);
                            return;
                        }
                        else
                        {
                            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT4);
                            DebugMessageU2Host("[CTS] No Device Attached", 0);
                        }
                    }
                    else if(GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_SUSPEND)
                    {
                        // ScalerSetBit(PDF_01_USB_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0);
                        ScalerSetByte(PDF_01_USB_DIVIDER, 0xA0); // Correct operation Flag
                        ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0);

                        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT2) == _BIT2)
                        {
                            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, ~_BIT7, _BIT7);

                            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, (_BIT7 | _BIT6 | _BIT2 | _BIT0)) != (_BIT7 | _BIT2 | _BIT0))
                            {
                                ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
                                DebugMessageU2Host("[CTS] SUSPEND MODE Fail", 0);
                            }
                            else
                            {
                                g_ucUsbU2HostTestIndex |= _BIT5;
                                DebugMessageU2Host("[CTS] SUSPEND MODE Success", 0);
                            }
                        }
                        else
                        {
                            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT5);
                            DebugMessageU2Host("[CTS] Execute Suspend Mode Fail. Port is not enable", 0);
                        }
                    }
                    else if(GET_U2HOST_CTS_MODE_STATUS() == _U2HOST_CTS_MODE_RESUME)
                    {
                        // ScalerSetBit(PDF_01_USB_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0);
                        ScalerSetByte(PDF_01_USB_DIVIDER, 0xA0); // Correct operation Flag
                        ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0);

                        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT2) == _BIT2)
                        {
                            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, ~_BIT6, _BIT6);
                            ScalerTimerDelayXms(20);
                            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, ~_BIT6, 0x00);

                            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, (_BIT7 | _BIT6 | _BIT2 | _BIT0)) != (_BIT2 | _BIT0))
                            {
                                ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);
                                DebugMessageU2Host("[CTS] RESUME MODE Fail", 0);
                            }
                            else
                            {
                                g_ucUsbU2HostTestIndex |= _BIT6;
                                DebugMessageU2Host("[CTS] RESUME MODE Success", 0);
                            }
                        }
                        else
                        {
                            ScalerSetBit(PDF_00_USB_CTR0_REG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT5);
                            DebugMessageU2Host("[CTS] Execute Resume Mode Fail. Port is not enable", 0);
                        }
                    }
                    else
                    {
                        // Nothing to do
                    }

                    if((ScalerGetByte(PDF_01_USB_DIVIDER) & _BIT5) == 0x00)
                    {
                        CLR_U2HOST_CTS_EN_STATUS();
                    }
                    ScalerDebug();
                }


                if(GET_U2HOST_MODE_STATE() == _U2HOST_MODE_STATE_POWER_OFF)
                {
                    g_ucUsbU2HostPreUsbTestMode = 0x00;
                    g_ucUsbU2HostPreProTestCtrl = 0x00;
/*
                    // Reset Host Controller
                    ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);
                    ScalerTimerDelayXms(2);

                    // Configuration Flag (CF) set to 1 for port routing control (all ports attached to EHCI)
                    ScalerUsbU2HostPortOwnerSwitch(_U2HOST_OWNER_EHCI);
*/
                }
                SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_NO_CHANGE);
                DebugMessageU2Host("[CTS] Set_Connect_NoChange", 0);
            }
            else if((ScalerGetByte(PDF_61_USB_WRAPP_REG_1) & _BIT7) == _BIT7)
            {
                // TBD : Self-Loop-Back
            }
            else
            {
                // DebugMessageU2Host("[EHCI] Root Hub Detect No Changed.", 0);
                SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_NO_CHANGE);
            }
        }
    }
    else if(enumMode == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        // Check if OHCI Root Hub Connect Status Chg
        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_2, _BIT0) == _BIT0)
        {
            // Clr OHCI Root Hub Connect Status Change flag
            ScalerUsbU2HostSetOHCIRhStsRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_2, _BIT0);

            // Check if OHCI Device present (Connected)
            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_0, _BIT0) == _BIT0)
            {
                // DebugMessageU2HostOHCI("[OHCI] Root Hub Detect Insert Device.", 0);
                SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_INSERT_DEVICE);
            }
            else
            {
                DebugMessageU2HostOHCI("[OHCI] Root Hub Detect Remove Device.", 0);
                SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_REMOVE_DEVICE);
            }
        }
        else
        {
            // DebugMessageU2HostOHCI("[OHCI] Root Hub Detect No Changed.", 0);
            SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_NO_CHANGE);
        }
#endif
    }
    else
    {
        SET_U2HOST_CONNECT_STATUS(_U2HOST_CONNECT_NO_CHANGE);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Judge USB CTS Test Procedure State
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostCtsModeJudge(void)
{
    BYTE ucUsbTestMode = 0;
    BYTE ucUsbTestMode1 = 0;
    BYTE ucUsbTestMode2 = 0;

    ucUsbTestMode = ScalerGetByte(PDF_01_USB_DIVIDER);
    ucUsbTestMode1 = ucUsbTestMode & (_BIT4 | _BIT3);
    ucUsbTestMode2 = ucUsbTestMode & (_BIT2 | _BIT1 | _BIT0);

    if(ucUsbTestMode == g_ucUsbU2HostPreUsbTestMode)
    {
        DebugMessageU2Host("[CTS] Please assign a Test Mode!", g_ucUsbU2HostTestIndex);
        return;
    }
    else
    {
        g_ucUsbU2HostPreUsbTestMode = ucUsbTestMode;
    }

    if(ucUsbTestMode1 == _BIT3) // Include Test J/K/SE0_NAK/Packet/Force_Enable(5)
    {
        SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_TEST);
    }
    else if(ucUsbTestMode1 == _BIT4) // Include EnumBus/Signal_get_Dev_Des/Suspend/Resume(4)
    {
        if(ucUsbTestMode2 == 0x00)
        {
            SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_ENUM);
        }
        else if(ucUsbTestMode2 == 0x01)
        {
            SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_SIGN_GET_DEV_DESC);
        }
        else if(ucUsbTestMode2 == 0x02)
        {
            SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_SUSPEND);
            return;
        }
        else if(ucUsbTestMode2 == 0x03)
        {
            SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_RESUME);
            return;
        }
        else
        {
            SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_NONE);
            DebugMessageU2Host("[CTS] Please Select Mode", 0);
            return;
        }
        // Reset Host Controller
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);
        ScalerTimerDelayXms(2);

        // Configuration Flag (CF) set to 1 for port routing control (all ports attached to EHCI)
        ScalerUsbU2HostPortOwnerSwitch(_U2HOST_OWNER_EHCI);

        // EHCI Hub Power On
        // ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, ~_BIT4, _BIT4);
        ScalerTimerDelayXms(2);
    }
    else
    {
        SET_U2HOST_CTS_MODE_STATUS(_U2HOST_CTS_MODE_NONE);
        DebugMessageU2Host("[CTS] Please Select Mode", 0);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Judge USB CTS Test Mode Control
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostCtsTestModeContol(void)
{
    BYTE ucPortTestCtrl = 0x00;

    ucPortTestCtrl = (ScalerGetByte(PDF_01_USB_DIVIDER) & 0x07);

    if(ucPortTestCtrl == g_ucUsbU2HostPreProTestCtrl)
    {
        return;
    }
    else
    {
        g_ucUsbU2HostPreProTestCtrl = ucPortTestCtrl;
    }

    // Reset Host Controller
    ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

    ScalerTimerDelayXms(2);

    if(ucPortTestCtrl == 0x01)
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        g_ucUsbU2HostTestIndex |= _BIT0;
        DebugMessageU2Host("[CTS] Test J_STATE", 0);
    }
    else if(ucPortTestCtrl == 0x02)
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
        g_ucUsbU2HostTestIndex |= _BIT1;
        DebugMessageU2Host("[CTS] Test K_STATE", 0);
    }
    else if(ucPortTestCtrl == 0x03)
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        g_ucUsbU2HostTestIndex |= _BIT2;
        DebugMessageU2Host("[CTS] Test SE0_NAK", 0);
    }
    else if(ucPortTestCtrl == 0x04)
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        g_ucUsbU2HostTestIndex |= _BIT3;
        DebugMessageU2Host("[CTS] Test PACKET", 0);
    }
    else if(ucPortTestCtrl == 0x05)
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~_BIT0, _BIT0);
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        g_ucUsbU2HostTestIndex |= _BIT4;
        DebugMessageU2Host("[CTS] Test FORCE_ENABLE", 0);
    }
    else
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0);
        DebugMessageU2Host("[CTS] Test mode not enable", 0);
    }
}
//----------------------------------------------------------------------------------------------------
// Description  : USB Port Enable Process
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : _TRUE -> Device is High Speed ; _FALSE -> Device is not High Speed
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostRhPortEnable(EnumUsbU2HostOwner enumMode)
{
    if(enumMode == _U2HOST_OWNER_EHCI)
    {
        // EHCI Root Hub Speed Check
        if((ScalerUsbU2HostGetRegByte(_PDF_04_PT_054_EHCI_PORTSC_1) & (_BIT3 | _BIT2)) == _BIT2)
        {
            g_ucUsbU2HostDeviceSpeed = _U2HOST_EHCI_DEVICE_SPEED_LOW;
            DebugMessageU2Host("[EHCI] Low Speed Device", 0);
            return _FALSE;
        }
        else if(ScalerUsbU2HostRhPortEnableChk(_U2HOST_OWNER_EHCI) == _TRUE)
        {
            g_ucUsbU2HostDeviceSpeed = _U2HOST_EHCI_DEVICE_SPEED_HIGH;
            DebugMessageU2Host("[EHCI] High Speed Device", 0);

            return _TRUE;
        }
        else
        {
            g_ucUsbU2HostDeviceSpeed = _U2HOST_EHCI_DEVICE_SPEED_FULL;
            DebugMessageU2Host("[EHCI] Full Speed Device", 0);
            return _FALSE;
        }
    }
    else if(enumMode == _U2HOST_OWNER_OHCI)
    {
        if(ScalerUsbU2HostRhPortEnableChk(_U2HOST_OWNER_OHCI) == _TRUE)
        {
            /// if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_1, _BIT1) == _BIT1)
            /// {
            ///    g_ucUsbU2HostDeviceSpeed = _U2HOST_EHCI_DEVICE_SPEED_LOW;
            /// }
            /// else
            /// {
            ///    g_ucUsbU2HostDeviceSpeed = _U2HOST_EHCI_DEVICE_SPEED_FULL;
            /// }
            DebugMessageU2Host("[OHCI] Port Enable Success", 0);
            return _TRUE;
        }
        else   // OHCI Root Hub Port can not enable
        {
            // Error Handling
            DebugMessageU2Host("[OHCI] Port Enable Fail", 0);
            return _FALSE;
        }
    }
    else
    {
        // undefine
        return _FALSE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Host Controller Port Owner Switch Process
// Input Value  : Switch to Host Controller Type : EHCI / OHCI
// Output Value : _TRUE -> Success ; _FALSE -> Fail
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostPortOwnerSwitch(EnumUsbU2HostOwner enumOwner)
{
    BYTE ucDelayTemp = 200;

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
        // Host Contorller has port power control switches(EHCI Hub Power On?)
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, ~_BIT4, _BIT4);

        // Configuration Flag (CF) set to 1 for port routing control (all ports attached to EHCI)
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_050_EHCI_CONFIG_FLAG_0, ~_BIT0, _BIT0);

        // Wait for port owner switch to EHCI or Time-out(1msec)
        while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, _BIT5) == _BIT5) && (--ucDelayTemp != 0))
        {
            DELAY_5US();
        }

        SET_U2HOST_OWENER(_U2HOST_OWNER_EHCI);
        DebugMessageU2Host("[Sys] Port Owner Switch to EHCI", 0);
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
        // Configuration Flag (CF) set to 0 for port routing control (all ports attached to OHCI)
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_050_EHCI_CONFIG_FLAG_0, ~_BIT0, 0x00);

        // Wait for port owner switch to OHCI or Time-out(1msec)
        while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, _BIT5) == 0x00) && (--ucDelayTemp != 0))
        {
            DELAY_5US();
        }

        SET_U2HOST_OWENER(_U2HOST_OWNER_OHCI);
        DebugMessageU2Host("[Sys] Port Owner Switch to OHCI", 0);
    }
    else
    {
        // No defined
    }

    if(ucDelayTemp > 0)
    {
        return _TRUE;
    }
    else
    {
        DebugMessageU2Host("[Sys] Time-out for Port Owner Switch", 0);
        return _FALSE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Transfer Last Transaction Complete status
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostDebugReg(void)
{
/*
    DWORD ulTemp_reg1 = 0;

    // BYTE ucTemp_reg5 = 0;
    // BYTE ucTemp_reg6 = 0;
    // BYTE ucTemp_reg7 = 0;

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_000_EHCI_CAP_LENGTH);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0000 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_004_EHCI_HCS_PARAMS_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0004 H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_008_EHCI_HCC_PARAMS_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0008 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_00C_EHCI_HCSP_PORTROUTE_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_000C H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_010_EHCI_USB_CMD_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0010 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_014_EHCI_USB_STS_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0014 H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_018_EHCI_USB_INTR_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0018 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_01C_EHCI_FRINDEX_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_001C H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_020_EHCI_CTRLDS_SEGMENT_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0020 H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_024_EHCI_PERIODIC_LIST_BASE_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0024 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0028 H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_050_EHCI_CONFIG_FLAG_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0050 H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_054_EHCI_PORTSC_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0054 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_090_EHCI_INSNREG00_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0090 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_094_EHCI_INSNREG01_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0094 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_098_EHCI_INSNREG02_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_0098 H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_09C_EHCI_INSNREG03_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_009C H->L", ulTemp_reg1);


    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_0A0_EHCI_INSNREG04_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_00A0 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_0A4_EHCI_INSNREG05_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_00A4 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_0A8_EHCI_INSNREG06_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_00A8 H->L", ulTemp_reg1);

    ulTemp_reg1 = ScalerUsbU2HostGetRegDword(_PDF_04_PT_0AC_EHCI_INSNREG07_0);
    DebugMessageU2HostEHCI("[Debug]0xDF04_00AC H->L", ulTemp_reg1);
*/
}

//----------------------------------------------------------------------------------------------------
// Description  : Clear Halt Feature
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostClearHaltFeature(EnumUsbU2HostOwner enumOwner)
{
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
    BYTE pucUsbCtrlCmd[8] =
    {
        0x02,               // bmRequestType: Data transfer direction: host-to-device; Recipient: Endpoint
        0x01,               // bRequest: CLEAR_FEATURE
        0x00, 0x00,         // wValue: ENDPOINT_HALT
        0x82,               // wIndex[7]: Direction, 0 for OUT and 1 for IN; [6:4]: rsvd; [3:0]: Endpoint Number
        0x00,               // wIndex[15:8]: rsvd
        0x00, 0x00          // wLength, should set to 0x00
    };
    // Update the endp Addr that Host should Clear
    pucUsbCtrlCmd[4] = GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(_U2HOST_DEVICE_ATTACH_INDEX);
#endif

    DebugMessageU2Host("[SCSI] CLEAR_HALT_DUR_BULK", 0);

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[0], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);            // Enable QH

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x08);   // Request Command Size = 8-bytes

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0x00);   // Reveive Data Size = 0-bytes
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);                 // Issue interrupt for last qTD
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);          // Set Command using 2*qTD only (Setup & IN Token)

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B1F_DT, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B1F_DT, 1);

        ScalerUsbU2HostMemoryClear(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, _U2HOST_CTRL_EHCI_BUFFER_SIZE);
        ScalerUsbU2HostSetEHCIMemoryAddr(_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR, 0);

        // Set ctrl cmd
        ScalerUsbU2HostSetCmdBufData(pucUsbCtrlCmd, 8);

        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 0
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B00_STATUS, 0x80);   // Enable qTD 1

        // Re-assign CTRL QH
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_028_EHCI_ASYNC_LIST_ADDR_0, tUSB_EHCI_CTRL_QH_ADDR_TABLE[0]);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _ENABLE);
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
    }
    else
    {
        // No defined
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Transfer Last Transaction Complete status
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostCheckLastTransactionCompleteStatus(EnumUsbU2HostOwner enumOwner)
{
    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_0, _BIT0) == _BIT0)
        {
            // Write 1 clear for USB Interrupt Status
            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_0, ~_BIT0, _BIT0);

            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_0, _BIT4) == _BIT4)
            {
                // Host System Error
                DebugMessageU2HostEHCI("[Err] System Err", 0);
                return _FALSE;
            }
            return _TRUE;
        }
#endif
        return _FALSE;
    }
    else if(enumOwner == _U2HOST_OWNER_OHCI)
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_10C_OHCI_HCINTERRUPT_STS_0, _BIT1) == _BIT1)
        {
            // Clear for USB Interrupt Status (write 1 clear)
            ScalerUsbU2HostSetRegBitField(_PDF_04_PT_10C_OHCI_HCINTERRUPT_STS_0, ~_BIT1, _BIT1);

            if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_10C_OHCI_HCINTERRUPT_STS_0, _BIT4) == _BIT4)
            {
                // USB Unrecoverable Error
                DebugMessageU2HostOHCI("[Err] Unrecoverable Err", 0);
                return _FALSE;
            }
            return _TRUE;
        }
#endif
        return _FALSE;
    }
    else
    {
        // Not Define
        return _FALSE;
    }
}
#endif // end of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)

//----------------------------------------------------------------------------------------------------
// Description  : USB Port Enable Check
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : _TRUE -> Device is High Speed ; _FALSE -> Device is not High Speed
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostRhPortEnableChk(EnumUsbU2HostOwner enumMode)
{
    BYTE ucDelayTemp = 200;

    ucDelayTemp = ucDelayTemp;

    // OHCI Will Also Need (enum Mode = EHCI) first
    if(enumMode == _U2HOST_OWNER_EHCI)
    {
        // EHCI Host Controller Run
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~_BIT0, _BIT0);

        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, ~_BIT2, 0x00);   // Disable for EHCI Root Hub Port

        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, ~_BIT0, _BIT0);   // Enable Port Reset - Will Drive D+ Low
        ScalerTimerDelayXms(10);
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_1, ~_BIT0, 0x00);   // Disable Port Reset

        ScalerTimerDelayXms(10);   // Need to wait until Xms after fw disbale port reset (defined by EHCI Spec.)

        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_054_EHCI_PORTSC_0, _BIT2) == _BIT2)
        {
            return _TRUE;   // Device is high-speed
        }
        else
        {
            return _FALSE;   // Device is full-speed
        }
    }
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
    else if(enumMode == _U2HOST_OWNER_OHCI)
    {
        // Set Port Reset
        ScalerUsbU2HostSetOHCIRhStsRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_0, _BIT4);

        // wait until (port reset complete & Port Reset Signal is not active) or Time-out(1 sec)
        while((!((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_2, _BIT4) == _BIT4) &&
                 (ScalerUsbU2HostGetRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_0, _BIT4) == 0x00))) &&
              (--ucDelayTemp != 0))
        {
            ScalerTimerDelayXms(5);
        }

        if(ucDelayTemp == 0)
        {
            DebugMessageU2HostOHCI("[Err] Time-out for OHCI Root Hub Port Enable.", 0);
        }

        // clear port reset complete flag
        ScalerUsbU2HostSetOHCIRhStsRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_2, _BIT4);

        if(ScalerUsbU2HostGetRegBitField(_PDF_04_PT_154_OHCI_HCRHPORTSTATUS_0, _BIT1) == _BIT1)   // Check Port is Enable or not
        {
            return _TRUE;
        }
        else
        {
            DebugMessageU2HostOHCI("[Err] OHCI Root Hub Port Can not Enable", 0);
            return _FALSE;
        }
    }
#endif
    else
    {
        return _FALSE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Initialize Process
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostCurOwerInit(EnumUsbU2HostOwner enumOwner)
{
    ScalerUsbU2HostCurOwerInitSchedule(enumOwner);
    ScalerUsbU2HostCurOwerInitHostController(enumOwner);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Initialize Schedule Process
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostCurOwerInitSchedule(EnumUsbU2HostOwner enumOwner)
{
    BYTE ucValueTemp = 0;

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
    ScalerUsbU2HostCurOwerInitDeviceAddr();
#endif

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        DebugMessageU2HostEHCI("[EHCI] InitSchedule.", 0);

        // Clear All USB Memory
        ScalerUsbU2HostMemoryClear(_U2HOST_MEMORY_ST_ADDR, _U2HOST_EHCI_MEMORY_SIZE);

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_ASYNC, _DISABLE);

        // 1.Initial for Control Queue Head
        for(ucValueTemp = 0; ucValueTemp < _U2HOST_EHCI_CTRL_QH_NUM; ucValueTemp++)
        {
            // --------------------- CTRL QH DWORD0 Setting ---------------------//
            // Set ctrl QH sram address at 0x00 (Max = 0x0BFF(3071))
            // T(BIT[0])=1:ignored if QH is in the asynchrounous schedule;
            // Typ=QH(BIT[2:1]=2'b01);
            // QHLP(BIT[31:5]) at 0x00

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B05_QHLP, tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp]);

            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B01_TYP, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D00_B00_T, 1);

            // --------------------- CTRL QH DWORD1 Setting ---------------------//
            // Device Address(BIT[6:0]=0x00 default);
            // I(BIT[7]=1'b0)-Only valid in Periodic Schedule and the EPS field indicates a FS/LS endpoint.
            // Endpt(BIT[11:8]=4'b0000);EPS(BIT[13:12]=2'b10->HS)
            // DTC(BIT[14]=1):Host controller initial DT bit in Qtd
            // H(BIT[15]=1):Mark a queue head as being the head of the reclamation(the first QH?)
            // Max packet(BIT[26:16]=0x040)=64
            // C(BIT[27]=0): if QH.EPS indicates the endpoint is not a high speed device and not an control endpoint,then fw must set this bit=1;
            // RL(BIT[31:28]=4'b0000):contains a value,used by host controller to reload the nak counter field
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B08_ENDPT, 0);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0C_EPS, g_ucUsbU2HostDeviceSpeed);   // Must set it before the fisrt process of Enumeration
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0E_DTC, 1);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B0F_H, 1);   // Head of reclamation List Flag = 1
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B10_MPL, 0x40);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D01_B1B_C, 0);

            // --------------------- CTRL QH DWORD2 Setting ---------------------//
            // Mult[BIT[31:30]=01]1 transaction count in one uframe
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D02_B1E_MULT, 1);

            // --------------------- CTRL QH DWORD3 Setting ---------------------//
            // Default all set 0

            // --------------------- CTRL QH DWORD4 Setting ---------------------//
            // Next Qtd address at 0x0040
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0]);
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T, 0);

            // --------------------- CTRL QH DWORD5 Setting ---------------------//
            ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QH_ADDR_TABLE[ucValueTemp], _U2HOST_EHCI_QH_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

            // --------------------- CTRL QH DWORD6-11 Setting ---------------------//
            // Default all set 0
        }


        // 1-1.Initial for Control qTD 0 : SETUP Token
        // --------------------- CTRL Setup QTD DWORD0 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);

        // --------------------- CTRL Setup QTD DWORD1 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

        // --------------------- CTRL Setup QTD DWORD2 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 2);  // Setup Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0A_CERR, 0x03);   // CERR = 3
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0);       // Not last qTD

        // --------------------- CTRL Setup QTD DWORD3 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[0], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_CTRL_BUFFER_ST_ADDR);


        // 1-2.Initial for Control qTD 1 : IN Token
        // --------------------- CTRL IN QTD DWORD0 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2]);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 0);

        // --------------------- CTRL IN QTD DWORD1 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T, 1);

        // --------------------- CTRL IN QTD DWORD2 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 1); // IN Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D06_B0F_IOC, 0); // Not last qTD (Not must,ex. set addr)

        // --------------------- CTRL IN QTD DWORD3 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[1], _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET, _U2HOST_EHCI_CTRL_BUFFER_ST_ADDR);

        // 1-3.Initial for Control qTD 2 : OUT Token
        // --------------------- CTRL OUT QTD DWORD0 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD, 0);
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T, 1);

        // --------------------- CTRL OUT QTD DWORD1 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B08_PID_CODE, 0);   // OUT Token
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B0F_IOC, 1);   // Issue interrupt for last qTD

        // --------------------- CTRL OUT QTD DWORD2 Setting ---------------------//
        ScalerUsbU2HostSetEHCIMemoryField(tUSB_EHCI_CTRL_QTD_ADDR_TABLE[2], _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES, 0);   // Empty data-out


        // 2.Initial for BULK Out Queue Head

        // 2-1.Initial for Bulk Out qTD 0 : CBW Stage
        // 2-2.Initial for Bulk Out qTD 1 : Data Out Stage

        // 3.Initial for BULK In Queue Head

        // 3-1.Initial for Bulk In qTD 0 : Data In Stage
        // 3-2.Initial for Bulk In qTD 1 : CSW Stage
#endif // End of Endif #if(_USB2_HOST_EHCI_SUPPORT == _ON)
    }
    else
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        // DebugMessageU2HostOHCI("[OHCI] InitSchedule.", 0);

        // Clear All USB Memory
        ScalerUsbU2HostMemoryClear(_U2HOST_MEMORY_ST_ADDR, _U2HOST_OHCI_MEMORY_SIZE + _U2HOST_MEMORY_OHCI_ST_ADDR_OFFSET);
        ScalerUsbU2HostMemoryClear(_U2HOST_OHCI_HCCA_MEMORY_ADDR, _U2HOST_OHCI_HCCA_MEMORY_SIZE);

        // Initial for Control ED
        for(ucValueTemp = 0; ucValueTemp < _U2HOST_OHCI_CTRL_ED_NUM; ucValueTemp++)
        {
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_ED_ADDR_TABLE[ucValueTemp], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable CTRL ED
        }

        for(ucValueTemp = 0; ucValueTemp < _U2HOST_OHCI_INT_ED_NUM; ucValueTemp++)
        {
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp], _U2HOST_OHCI_ED_D00_B0E_SKIP, 1);   // Disable INT ED
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp], _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER, tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp]);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_ED_ADDR_TABLE[ucValueTemp], _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER, 0);
            ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_INT_TD_ADDR_TABLE[ucValueTemp], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);   // IN Token
        }

        // Initial for OHCI Control TD 0 : SETUP Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 0);   // Setup Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[0], _U2HOST_OHCI_TD_D03_B00_BUF_END, (_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR + 7));

        // Initial for OHCI Control TD 1 : IN Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[1], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 2);   // IN Token

        // Initial for OHCI Control TD 2 : OUT Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D00_B13_PID_CODE, 1);   // OUT Token
        ScalerUsbU2HostSetOHCIMemoryField(tUSB_OHCI_CTRL_TD_ADDR_TABLE[2], _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER, 0);   // Empty Packet

#endif // End of Endif #if(_USB2_HOST_OHCI_SUPPORT == _ON)
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB Initialize Host Controller Process
// Input Value  : USB Host Controller Type : EHCI or OHCI
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostCurOwerInitHostController(EnumUsbU2HostOwner enumOwner)
{
    // BYTE ucAddrTemp1 = 0;
    // BYTE ucAddrTemp2 = 0;

    if(enumOwner == _U2HOST_OWNER_EHCI)
    {
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
        DebugMessageU2HostEHCI("[EHCI] InitHC.", 0);

        // Interrupt Threshold Control
        // ScalerUsbU2HostSetRegByte(_PDF_04_PT_010_EHCI_USB_CMD_2, 0x08);   // 1ms

        // Enable USB transaction complete interrupt
        // ScalerUsbU2HostSetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_3, ~_BIT0, _BIT0);

        // List Address Assign
        // ScalerUsbU2HostSetRegDword(_PDF_04_PT_024_EHCI_PERIODIC_LIST_BASE_0, 0x00010000);

        // CAITEST

        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_PERIODIC, _DISABLE);
        // ScalerSetBit(PDF_67_U2HOST_UTMI_STRAP_SIG_REG, ~_BIT0, 0x00); // 60MHZ Mode?
        // ScalerUsbU2HostSetRegDword(_PDF_04_PT_090_EHCI_INSNREG00_0, 0x00001D0D);
        // ScalerUsbU2HostSetRegDword(_PDF_04_PT_090_EHCI_INSNREG00_0, 0x00000E87);
/*
        // Periodic Frame List Address Mapping
        ScalerSetByte(PDF_20_U2HOST_ADDR_MAP_CTRL0, 0x70);   // INT0 located at Periodic Frame List Number = 0 (0x000)
        ScalerSetByte(PDF_21_U2HOST_ADDR_MAP_ADDR0, 0x00);
        ucAddrTemp1 = (BYTE)((tUSB_EHCI_INT_QH_ADDR_TABLE[0] & 0x0700) >> 8);
        ucAddrTemp2 = (BYTE)(tUSB_EHCI_INT_QH_ADDR_TABLE[0] & 0x00FF) | 0x02;
        ScalerSetByte(PDF_22_U2HOST_ADDR_DEST_MSB0, ucAddrTemp1);
        ScalerSetByte(PDF_23_U2HOST_ADDR_DEST_LSB0, ucAddrTemp2);

        ScalerSetByte(PDF_24_U2HOST_ADDR_MAP_CTRL1, 0x71);   // INT1 located at Periodic Frame List Number = 341 (0x155)
        ScalerSetByte(PDF_25_U2HOST_ADDR_MAP_ADDR1, 0x55);
        ucAddrTemp1 = (BYTE)((tUSB_EHCI_INT_QH_ADDR_TABLE[1] & 0x0700) >> 8);
        ucAddrTemp2 = (BYTE)(tUSB_EHCI_INT_QH_ADDR_TABLE[1] & 0x00FF) | 0x02;
        ScalerSetByte(PDF_26_U2HOST_ADDR_DEST_MSB1, ucAddrTemp1);
        ScalerSetByte(PDF_27_U2HOST_ADDR_DEST_LSB1, ucAddrTemp2);

        ScalerSetByte(PDF_28_U2HOST_ADDR_MAP_CTRL2, 0x72);   // INT2 located at Periodic Frame List Number = 682 (0x2AA)
        ScalerSetByte(PDF_29_U2HOST_ADDR_MAP_ADDR2, 0xAA);
        ucAddrTemp1 = (BYTE)((tUSB_EHCI_INT_QH_ADDR_TABLE[2] & 0x0700) >> 8);
        ucAddrTemp2 = (BYTE)(tUSB_EHCI_INT_QH_ADDR_TABLE[2] & 0x00FF) | 0x02;
        ScalerSetByte(PDF_2A_U2HOST_ADDR_DEST_MSB2, ucAddrTemp1);
        ScalerSetByte(PDF_2B_U2HOST_ADDR_DEST_LSB2, ucAddrTemp2);

        // disable the else section of address map control
        ScalerSetByte(PDF_2C_U2HOST_ADDR_DEST_ELSE_MSB, 0x00);
        ScalerSetByte(PDF_2D_U2HOST_ADDR_DEST_ELSE_LSB0, 0x03);

        // Enable Periodic Schedule
        ScalerUsbU2HostScheduleEnable(_U2HOST_SCHEDULE_PERIODIC, _ENABLE);
*/
#endif
    }
    else
    {
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
        // Note: Debugmessage seems cannot be placed here according to the test.(otherwise mouse will no response),I Dont know Why.

        // HCCA Area Address
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_118_OHCI_HCCA_0, _U2HOST_OHCI_HCCA_MEMORY_ADDR);

        // Assign Control Head ED Address
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_120_OHCI_HCCONTROLHEAD_ED_0, tUSB_OHCI_CTRL_ED_ADDR_TABLE[0]);

        // Periodic Start
        ScalerUsbU2HostSetRegDword(_PDF_04_PT_140_OHCI_HCPERIODICSTART_0, 0x2EDF);

        // Frame Interval
        // ScalerUsbU2HostSetRegByte(_PDF_04_PT_134_OHCI_HCFMINTERVAL_1, 0x2E);
        // ScalerUsbU2HostSetRegByte(_PDF_04_PT_134_OHCI_HCFMINTERVAL_0, 0xDF);

        // Largest Data Packet Counter
        ScalerUsbU2HostSetRegByte(_PDF_04_PT_134_OHCI_HCFMINTERVAL_3, 0x2E);
        ScalerUsbU2HostSetRegByte(_PDF_04_PT_134_OHCI_HCFMINTERVAL_2, 0xDF);

        // It seems that fix the wireless mouse issue(full speed),but why? (11999 - 210)*6/7
        ScalerUsbU2HostSetRegByte(_PDF_04_PT_134_OHCI_HCFMINTERVAL_3, 0x27);
        ScalerUsbU2HostSetRegByte(_PDF_04_PT_134_OHCI_HCFMINTERVAL_2, 0x78);

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
        // Host Controller Switch to Operational Mode & Enable Control, Periodic, Bulk
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_104_OHCI_HCCONTROL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT5 | _BIT4 | _BIT2));
#else
        // Host Controller Switch to Operational Mode & Enable Control, Periodic
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_104_OHCI_HCCONTROL_0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2), (_BIT7 | _BIT4 | _BIT2));
#endif
        DebugMessageU2HostOHCI("[OHCI] InitHC", 0);
#endif
    }

    // Auto Suspend Mode Disable
    ScalerUsbU2HostSetRegBitField(PDF_60_USB_WRAPP_REG_0, ~_BIT6, _BIT6);
}


#if(_USB2_HOST_EHCI_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// USB EHCI Memory Access Function
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// Description  : Set USB EHCI Memory Address Process
// Input Value  : Memory Address , Memory Field
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetEHCIMemoryAddr(WORD usAddr, WORD usFieldAddr)
{
    WORD usByteAddr = 0;
    BYTE ucWordNo = 0;
    BYTE ucByteAddrLsb = 0;
    BYTE ucByteAddrMsb = 0;

    ucWordNo = (BYTE)((usFieldAddr & 0x0F00) >> 8);

    if((usFieldAddr & _BIT15) == _BIT15)   // qTD Element
    {
        ucWordNo = ucWordNo - 4;
    }

    usByteAddr = usAddr + (ucWordNo * 4);

// RL6829 Support 2K SRAM(0x7FF), RL6952 Support 3K SRAM(0xBFF)
#if(_HW_USB2_HOST_SRAM_SIZE_SUPPORT == _HW_USB2_HOST_SRAM_SIZE_2K)
    ucByteAddrMsb = (BYTE)((usByteAddr & 0x0700) >> 8);
#else
    ucByteAddrMsb = (BYTE)((usByteAddr & 0x0F00) >> 8);

    if(ucByteAddrMsb > 0xB0)
    {
        DebugMessageU2HostOHCI("Error: SRAM Addr. exceed 3K!", ucByteAddrMsb);
    }
#endif
    ucByteAddrLsb = (BYTE)(usByteAddr & 0x00FC);   // 32-bit Addressing

    // the Bit[1:0] in usByteAddr will not be set (the unit of BUF_ADR is DWORD)
    ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucByteAddrMsb);
    ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucByteAddrLsb);
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB EHCI Memory Field Data
// Input Value  : Memory Address , Memory Field Address , Memory Field Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetEHCIMemoryField(WORD usAddr, WORD usFieldAddr, DWORD ulValue)
{
    BYTE ucWordNo = 0;
    BYTE ucBitNo = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;
    DWORD ulValueTemp = 0;

    ucWordNo = (BYTE)((usFieldAddr & 0x0F00) >> 8);
    ucBitNo = (BYTE)(usFieldAddr & 0x001F);

    ScalerUsbU2HostSetEHCIMemoryAddr(usAddr, usFieldAddr);

    ucValueTemp1 = ScalerGetByte(PDF_14_USB_BUF_DATA0);
    ucValueTemp2 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
    ucValueTemp3 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
    ucValueTemp4 = ScalerGetByte(PDF_17_USB_BUF_DATA3);

    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | (DWORD)ucValueTemp1;

    switch(ucWordNo)
    {
        case 0x00:
            if(ucBitNo == 0x00)   // T : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFFFE) | (ulValue & 0x00000001);
            }
            else if(ucBitNo == 0x01)   // Typ : 2-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFFF9) | ((ulValue & 0x00000003) << 1);
            }
            else if(ucBitNo == 0x05)   // Queue Head Horizontal Link Pointer : 27-bits
            {
                ulValueTemp = (ulValueTemp & 0x0000001F) | (ulValue & 0xFFFFFFE0);
            }
            else
            {
                // Address is not defined.
            }
            break;

        case 0x01:
            if(ucBitNo == 0x00)   // Device Address : 7-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFF80) | (ulValue & 0x0000007F);
            }
            else if(ucBitNo == 0x07)   // I-bit (Inactivate on Next Transaction) : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFF7F) | ((ulValue & 0x00000001) << 7);
            }
            else if(ucBitNo == 0x08)   // EndPt (Endpoint Number) : 4-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFF0FF) | ((ulValue & 0x0000000F) << 8);
            }
            else if(ucBitNo == 0x0C)   // EPS (Endpoint Speed) : 2-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFCFFF) | ((ulValue & 0x00000003) << 12);
            }
            else if(ucBitNo == 0x0E)   // dtc (Data Toggle Control) : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFFBFFF) | ((ulValue & 0x00000001) << 14);
            }
            else if(ucBitNo == 0x0F)   // H-bit (Head of Reclamation List Flag) : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFF7FFF) | ((ulValue & 0x00000001) << 15);
            }
            else if(ucBitNo == 0x10)   // Maximum Packet Length : 11-bits
            {
                ulValueTemp = (ulValueTemp & 0xF800FFFF) | ((ulValue & 0x000007FF) << 16);
            }
            else if(ucBitNo == 0x1B)   // C-bit (Control Endpoint Flag) : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xF7FFFFFF) | ((ulValue & 0x00000001) << 27);
            }
            else if(ucBitNo == 0x1C)   // RL (Nak Count Reload) : 4-bits
            {
                ulValueTemp = (ulValueTemp & 0x0FFFFFFF) | ((ulValue & 0x0000000F) << 28);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x02:
            if(ucBitNo == 0x00)   // uFrame S-mask : 8-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFF00) | (ulValue & 0x000000FF);
            }
            else if(ucBitNo == 0x08)   // uFrame C-mask* : 8-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFF00FF) | ((ulValue & 0x000000FF) << 8);
            }
            else if(ucBitNo == 0x10)   // Hub Addr* : 7-bits
            {
                ulValueTemp = (ulValueTemp & 0xFF80FFFF) | ((ulValue & 0x0000007F) << 16);
            }
            else if(ucBitNo == 0x17)   // Port Number* : 7-bits
            {
                ulValueTemp = (ulValueTemp & 0xC07FFFFF) | ((ulValue & 0x0000007F) << 23);
            }
            else if(ucBitNo == 0x1E)   // Mult (High-Bandwidth Pipe Multiplier) : 2-bits
            {
                ulValueTemp = (ulValueTemp & 0x3FFFFFFF) | ((ulValue & 0x00000003) << 30);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x03:
            if(ucBitNo == 0x05)   // Current qTD Pointer : 27-bits
            {
                ulValueTemp = (ulValueTemp & 0x0000001F) | (ulValue & 0xFFFFFFE0);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x04:
            if(ucBitNo == 0x00)   // Next qTD Pointer T-bit : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFFFE) | (ulValue & 0x00000001);
            }
            else if(ucBitNo == 0x05)   // Next qTD Pointer : 27-bits
            {
                ulValueTemp = (ulValueTemp & 0x0000001F) | (ulValue & 0xFFFFFFE0);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x05:
            if(ucBitNo == 0x00)   // Alternate Next qTD Pointer T-bit : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFFFE) | (ulValue & 0x00000001);
            }
            /// else if(ucBitNo == 0x01)   // Nak Counter (FW Read Only) : 4-bits
            /// {
            ///    ulValueTemp = (ulValueTemp & 0xFFFFFFE1) | ((ulValue & 0x0000000F) << 1);
            /// }
            else if(ucBitNo == 0x05)   // Alternate Next qTD Pointer : 27-bits
            {
                ulValueTemp = (ulValueTemp & 0x0000001F) | (ulValue & 0xFFFFFFE0);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x06:
            if(ucBitNo == 0x00)   // Status : 8-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFF00) | (ulValue & 0x000000FF);
            }
            else if(ucBitNo == 0x08)   // PID_Code : 2-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFCFF) | ((ulValue & 0x00000003) << 8);
            }
            else if(ucBitNo == 0x0A)   // Cerr : 2-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFF3FF) | ((ulValue & 0x00000003) << 10);
            }
            else if(ucBitNo == 0x0C)   // C_Page : 3-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFF8FFF) | ((ulValue & 0x00000007) << 12);
            }
            else if(ucBitNo == 0x0F)   // ioc : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0xFFFF7FFF) | ((ulValue & 0x00000001) << 15);
            }
            else if(ucBitNo == 0x10)   // Total Bytes to Transfer : 15-bits
            {
                ulValueTemp = (ulValueTemp & 0x8000FFFF) | ((ulValue & 0x00007FFF) << 16);
            }
            else if(ucBitNo == 0x1F)   // dt : 1-bit
            {
                ulValueTemp = (ulValueTemp & 0x7FFFFFFF) | ((ulValue & 0x00000001) << 31);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x07:
            if(ucBitNo == 0x00)   // Current Offset : 12-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFF000) | (ulValue & 0x00000FFF);
            }
            else if(ucBitNo == 0x0C)   // Buffer Pointer (Page 0) : 20-bits
            {
                ulValueTemp = (ulValueTemp & 0x00000FFF) | ((ulValue & 0x000FFFFF) << 12);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x08:
            if(ucBitNo == 0x00)   // C-prog-mask* : 8-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFF00) | (ulValue & 0x000000FF);
            }
            else if(ucBitNo == 0x0C)   // Buffer Pointer (Page 1) : 20-bits
            {
                ulValueTemp = (ulValueTemp & 0x00000FFF) | ((ulValue & 0x000FFFFF) << 12);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x09:
            if(ucBitNo == 0x00)   // FrameTag* : 5-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFFFE0) | (ulValue & 0x0000001F);
            }
            else if(ucBitNo == 0x05)   // S-bytes : 7-bits
            {
                ulValueTemp = (ulValueTemp & 0xFFFFF01F) | ((ulValue & 0x0000007F) << 5);
            }
            else if(ucBitNo == 0x0C)   // Buffer Pointer (Page 2) : 20-bits
            {
                ulValueTemp = (ulValueTemp & 0x00000FFF) | ((ulValue & 0x000FFFFF) << 12);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x0A:
            if(ucBitNo == 0x0C)   // Buffer Pointer (Page 3) : 20-bits
            {
                ulValueTemp = (ulValueTemp & 0x00000FFF) | ((ulValue & 0x000FFFFF) << 12);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x0B:
            if(ucBitNo == 0x0C)   // Buffer Pointer (Page 4) : 20-bits
            {
                ulValueTemp = (ulValueTemp & 0x00000FFF) | ((ulValue & 0x000FFFFF) << 12);
            }
            else
            {
                // Address is not define
            }
            break;

        default:
            break;
    }

    ucValueTemp1 = (BYTE)(ulValueTemp & 0x000000FF);
    ucValueTemp2 = (BYTE)((ulValueTemp & 0x0000FF00) >> 8);
    ucValueTemp3 = (BYTE)((ulValueTemp & 0x00FF0000) >> 16);
    ucValueTemp4 = (BYTE)((ulValueTemp & 0xFF000000) >> 24);

    ScalerUsbU2HostSetEHCIMemoryAddr(usAddr, usFieldAddr);
    ScalerSetByte(PDF_14_USB_BUF_DATA0, ucValueTemp1);
    ScalerSetByte(PDF_15_USB_BUF_DATA1, ucValueTemp2);
    ScalerSetByte(PDF_16_USB_BUF_DATA2, ucValueTemp3);
    ScalerSetByte(PDF_17_USB_BUF_DATA3, ucValueTemp4);   // write data to buffer
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB EHCI Memory Field Data
// Input Value  : Memory Address , Memory Field Address
// Output Value : Memory Field Data
//----------------------------------------------------------------------------------------------------
DWORD ScalerUsbU2HostGetEHCIMemoryField(WORD usAddr, WORD usFieldAddr)
{
    BYTE ucWordNo = 0;
    BYTE ucBitNo = 0;
    DWORD ulValueTemp = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;

    ucWordNo = (BYTE)((usFieldAddr & 0x0F00) >> 8);
    ucBitNo = (BYTE)(usFieldAddr & 0x001F);

    ScalerUsbU2HostSetEHCIMemoryAddr(usAddr, usFieldAddr);

    ucValueTemp1 = ScalerGetByte(PDF_14_USB_BUF_DATA0);
    ucValueTemp2 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
    ucValueTemp3 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
    ucValueTemp4 = ScalerGetByte(PDF_17_USB_BUF_DATA3);

    switch(ucWordNo)
    {
        case 0x00:
            if(ucBitNo == 0x00)   // T : Bit[0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0x01);
            }
            else if(ucBitNo == 0x01)   // Typ : Bit[2:1]
            {
                ulValueTemp = (DWORD)((ucValueTemp1 & 0x06) >> 1);
            }
            else if(ucBitNo == 0x05)   // Queue Head Horizontal Link Pointer : Bit[31:5]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xE0);
            }
            else
            {
                // Address is not defined.
            }
            break;

        case 0x01:
            if(ucBitNo == 0x00)   // Device Address : Bit[6:0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0x7F);
            }
            else if(ucBitNo == 0x07)   // I-bit (Inactivate on Next Transaction) : Bit[7]
            {
                ulValueTemp = (DWORD)((ucValueTemp1 & 0x80) >> 7);
            }
            else if(ucBitNo == 0x08)   // EndPt (Endpoint Number) : Bit[11:8]
            {
                ulValueTemp = (DWORD)(ucValueTemp2 & 0x0F);
            }
            else if(ucBitNo == 0x0C)   // EPS (Endpoint Speed) : Bit[13:12]
            {
                ulValueTemp = (DWORD)((ucValueTemp2 & 0x30) >> 4);
            }
            else if(ucBitNo == 0x0E)   // dtc (Data Toggle Control) : Bit[14]
            {
                ulValueTemp = (DWORD)((ucValueTemp2 & 0x40) >> 6);
            }
            else if(ucBitNo == 0x0F)   // H-bit (Head of Reclamation List Flag) : Bit[15]
            {
                ulValueTemp = (DWORD)((ucValueTemp2 & 0x80) >> 7);
            }
            else if(ucBitNo == 0x10)   // Maximum Packet Length : 11-bits
            {
                ulValueTemp = (((DWORD)ucValueTemp4 & 0x07) << 8) | (ucValueTemp3 & 0xFF);
            }
            else if(ucBitNo == 0x1B)   // C-bit (Control Endpoint Flag) : Bit[17]
            {
                ulValueTemp = (DWORD)((ucValueTemp4 & 0x08) >> 3);
            }
            else if(ucBitNo == 0x1C)   // RL (Nak Count Reload) : Bit[31:28]
            {
                ulValueTemp = (DWORD)((ucValueTemp4 & 0xF0) >> 4);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x02:
            if(ucBitNo == 0x00)   // uFrame S-mask : Bit[7:0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0xFF);
            }
            else if(ucBitNo == 0x08)   // uFrame C-mask* : Bit[15:8]
            {
                ulValueTemp = (DWORD)(ucValueTemp2 & 0xFF);
            }
            else if(ucBitNo == 0x10)   // Hub Addr* : Bit[22:16]
            {
                ulValueTemp = (DWORD)(ucValueTemp3 & 0x7F);
            }
            else if(ucBitNo == 0x17)   // Port Number* : Bit[29:23]
            {
                ulValueTemp = (((DWORD)ucValueTemp4 & 0x3F) << 1) | ((ucValueTemp3 & 0x80) >> 7);
            }
            else if(ucBitNo == 0x1E)   // Mult (High-Bandwidth Pipe Multiplier) : Bit[31:30]
            {
                ulValueTemp = (DWORD)((ucValueTemp4 & 0xC0) >> 6);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x03:
            if(ucBitNo == 0x05)   // Current qTD Pointer : Bit[31:5]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xE0);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x04:
            if(ucBitNo == 0x00)   // Next qTD Pointer T-bit : Bit[0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0x01);
            }
            else if(ucBitNo == 0x05)   // Next qTD Pointer : Bit[31:5]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xE0);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x05:
            if(ucBitNo == 0x00)   // Alternate Next qTD Pointer T-bit : Bit[0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0x01);
            }
            else if(ucBitNo == 0x01)   // Nak Counter : Bit[4:1]
            {
                ulValueTemp = (DWORD)((ucValueTemp1 & 0x1E) >> 1);
            }
            else if(ucBitNo == 0x05)   // Alternate Next qTD Pointer : Bit[31:5]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xE0);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x06:
            if(ucBitNo == 0x00)   // Status : Bit[7:0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0xFF);
            }
            else if(ucBitNo == 0x08)   // PID_Code : Bit[9:8]
            {
                ulValueTemp = (DWORD)(ucValueTemp2 & 0x03);
            }
            else if(ucBitNo == 0x0A)   // Cerr : Bit[11:10]
            {
                ulValueTemp = (DWORD)((ucValueTemp2 & 0x0C) >> 2);
            }
            else if(ucBitNo == 0x0C)   // C_Page : Bit[14:12]
            {
                ulValueTemp = (DWORD)((ucValueTemp2 & 0x70) >> 4);
            }
            else if(ucBitNo == 0x0F)   // ioc : Bit[15]
            {
                ulValueTemp = (DWORD)((ucValueTemp2 & 0x80) >> 7);
            }
            else if(ucBitNo == 0x10)   // Total Bytes to Transfer : Bit[30:16]
            {
                ulValueTemp = (((DWORD)ucValueTemp4 & 0x7F) << 8) | ucValueTemp3;
            }
            else if(ucBitNo == 0x1F)   // dt : Bit[31]
            {
                ulValueTemp = (DWORD)(ucValueTemp4 & 0x80) >> 7;
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x07:
            if(ucBitNo == 0x00)   // Current Offset : Bit[11:0]
            {
                ulValueTemp = (((DWORD)ucValueTemp2 & 0x0F) << 8) | ucValueTemp1;
            }
            else if(ucBitNo == 0x0C)   // Buffer Pointer (Page 0) : Bit[31:12]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 12) | ((DWORD)ucValueTemp3 << 4) | (((DWORD)ucValueTemp2 & 0xF0) >> 4);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x08:
            if(ucBitNo == 0x00)   // C-prog-mask* : Bit[7:0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0xFF);
            }
            else if(ucBitNo == 0x0C)   // Buffer Pointer (Page 1) : Bit[31:12]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 12) | ((DWORD)ucValueTemp3 << 4) | (((DWORD)ucValueTemp2 & 0xF0) >> 4);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x09:
            if(ucBitNo == 0x00)   // FrameTag* : Bit[4:0]
            {
                ulValueTemp = (DWORD)(ucValueTemp1 & 0x1F);
            }
            else if(ucBitNo == 0x05)   // S-bytes : Bit[11:5]
            {
                ulValueTemp = (((DWORD)ucValueTemp2 & 0x0F) << 3) | ((ucValueTemp1 & 0xE0) >> 5);
            }
            else if(ucBitNo == 0x0C)   // Buffer Pointer (Page 2) : Bit[31:12]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 12) | ((DWORD)ucValueTemp3 << 4) | (((DWORD)ucValueTemp2 & 0xF0) >> 4);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x0A:
            if(ucBitNo == 0x0C)   // Buffer Pointer (Page 3) : Bit[31:12]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 12) | ((DWORD)ucValueTemp3 << 4) | (((DWORD)ucValueTemp2 & 0xF0) >> 4);
            }
            else
            {
                // Address is not define
            }
            break;

        case 0x0B:
            if(ucBitNo == 0x0C)   // Buffer Pointer (Page 4) : Bit[31:12]
            {
                ulValueTemp = ((DWORD)ucValueTemp4 << 12) | ((DWORD)ucValueTemp3 << 4) | (((DWORD)ucValueTemp2 & 0xF0) >> 4);
            }
            else
            {
                // Address is not define
            }
            break;

        default:
            break;
    }

    return ulValueTemp;
}
#endif // end of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : Set USB OHCI Memory Address Process
// Input Value  : Memory Address (BYTE), Memory Field Address
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetOHCIMemoryAddr(WORD usAddr, WORD usFieldAddr)
{
    WORD usByteAddr = 0;
    BYTE ucDWordNo = 0;
    BYTE ucByteAddrLsb = 0;
    BYTE ucByteAddrMsb = 0;

    // the Bit[13:8] in Memory Field Address indicated the DWORD No.
    ucDWordNo = (BYTE)((usFieldAddr & 0x3F00) >> 8);

    usByteAddr = usAddr + (ucDWordNo * 4);
    ucByteAddrLsb = (BYTE)(usByteAddr & 0x00FC);

    // RL6829 Support 2K SRAM(0x7FF), RL6952 Support 3K SRAM(0xBFF)
#if(_HW_USB2_HOST_SRAM_SIZE_SUPPORT == _HW_USB2_HOST_SRAM_SIZE_2K)
    ucByteAddrMsb = (BYTE)((usByteAddr & 0x0700) >> 8);
#else
    ucByteAddrMsb = (BYTE)((usByteAddr & 0x0F00) >> 8);

    if(ucByteAddrMsb > 0xB0)
    {
        DebugMessageU2HostEHCI("Error: SRAM Addr. exceed 3K!", ucByteAddrMsb);
    }
#endif

    // the Bit[1:0] in usByteAddr will not be set (the unit of BUF_ADR is DWORD)
    ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucByteAddrLsb);
    ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucByteAddrMsb);
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB OHCI Memory Field Data
// Input Value  : Memory Address , Memory Field Address , Memory Field Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetOHCIMemoryField(WORD usAddr, WORD usFieldAddr, DWORD ulValue)
{
    BYTE ucWordNo = 0;
    BYTE ucBitNo = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;
    DWORD ulValueTemp = 0;

    ucWordNo = (BYTE)((usFieldAddr & 0x3F00) >> 8);
    ucBitNo = (BYTE)(usFieldAddr & 0x001F);

    ScalerUsbU2HostSetOHCIMemoryAddr(usAddr, usFieldAddr);

    ucValueTemp1 = ScalerGetByte(PDF_14_USB_BUF_DATA0);
    ucValueTemp2 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
    ucValueTemp3 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
    ucValueTemp4 = ScalerGetByte(PDF_17_USB_BUF_DATA3);

    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | (DWORD)ucValueTemp1;

    if((usFieldAddr & _BIT15) == 0x00)   // ED Element
    {
        switch(ucWordNo)
        {
            case 0x00:
                if(ucBitNo == 0x00)   // Device Address : 7-bit
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFFF80) | (ulValue & 0x0000007F);
                }
                else if(ucBitNo == 0x07)   // EndPt (Endpoint Number) : 4-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFF87F) | ((ulValue & 0x0000000F) << 7);
                }
                else if(ucBitNo == 0x0B)   // Token Direction : 2-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFE7FF) | ((ulValue & 0x00000003) << 11);
                }
                else if(ucBitNo == 0x0D)   // Endpoint Speed : 1-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFDFFF) | ((ulValue & 0x00000001) << 13);
                }
                else if(ucBitNo == 0x0E)   // Skip : 1-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFBFFF) | ((ulValue & 0x00000001) << 14);
                }
                else if(ucBitNo == 0x0F)   // Format : 1-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFF7FFF) | ((ulValue & 0x00000001) << 15);
                }
                else if(ucBitNo == 0x10)   // Maximum Packet Length : 11-bits
                {
                    ulValueTemp = (ulValueTemp & 0xF800FFFF) | ((ulValue & 0x000007FF) << 16);
                }
                else
                {
                    // Address is not defined.
                }
                break;

            case 0x01:
                if(ucBitNo == 0x04)   // TD Queue Tail Pointer : 28-bits
                {
                    ulValueTemp = (ulValueTemp & 0x0000000F) | (ulValue & 0xFFFFFFF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x02:
                if(ucBitNo == 0x00)   // Halted : 1-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFFFFE) | (ulValue & 0x00000001);
                }
                else if(ucBitNo == 0x01)   // toggle carry bit : 1-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFFFFFFD) | ((ulValue & 0x00000001) << 1);
                }
                else if(ucBitNo == 0x04)   // TD Queue Head Pointer : 28-bits
                {
                    ulValueTemp = (ulValueTemp & 0x0000000F) | (ulValue & 0xFFFFFFF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x03:
                if(ucBitNo == 0x04)   // Next Endpoint Descriptor : 28-bits
                {
                    ulValueTemp = (ulValueTemp & 0x0000000F) | (ulValue & 0xFFFFFFF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            default:
                break;
        }
    }
    else   // TD Element
    {
        switch(ucWordNo)
        {
            case 0x00:
                if(ucBitNo == 0x12)   // Buffer Rounding : 1-bit
                {
                    ulValueTemp = (ulValueTemp & 0xFFFBFFFF) | ((ulValue & 0x00000001) << 18);
                }
                else if(ucBitNo == 0x13)   // PID Direction : 2-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFFE7FFFF) | ((ulValue & 0x00000003) << 19);
                }
                else if(ucBitNo == 0x15)   // Delay Interrupt : 3-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFF1FFFFF) | ((ulValue & 0x00000007) << 21);
                }
                else if(ucBitNo == 0x18)   // Data Toggle : 2-bits
                {
                    ulValueTemp = (ulValueTemp & 0xFCFFFFFF) | ((ulValue & 0x00000003) << 24);
                }
                else if(ucBitNo == 0x1A)   // Error Count : 2-bits
                {
                    ulValueTemp = (ulValueTemp & 0xF3FFFFFF) | ((ulValue & 0x00000003) << 26);
                }
                else if(ucBitNo == 0x1C)   // Condition Code : 4-bits
                {
                    ulValueTemp = (ulValueTemp & 0x0FFFFFFF) | ((ulValue & 0x0000000F) << 28);
                }
                else
                {
                    // Address is not defined.
                }
                break;

            case 0x01:
                if(ucBitNo == 0x00)   // Current Buffer Pointer : 32-bits
                {
                    ulValueTemp = ulValue;
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x02:
                if(ucBitNo == 0x04)   // Next TD : 28-bits
                {
                    ulValueTemp = (ulValueTemp & 0x0000000F) | (ulValue & 0xFFFFFFF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x03:
                if(ucBitNo == 0x00)   // Buffer End : 32-bits
                {
                    ulValueTemp = ulValue;
                }
                else
                {
                    // Address is not define
                }
                break;

            default:
                break;
        }
    }

    ucValueTemp1 = (BYTE)(ulValueTemp & 0x000000FF);
    ucValueTemp2 = (BYTE)((ulValueTemp & 0x0000FF00) >> 8);
    ucValueTemp3 = (BYTE)((ulValueTemp & 0x00FF0000) >> 16);
    ucValueTemp4 = (BYTE)((ulValueTemp & 0xFF000000) >> 24);

    ScalerUsbU2HostSetOHCIMemoryAddr(usAddr, usFieldAddr);
    ScalerSetByte(PDF_14_USB_BUF_DATA0, ucValueTemp1);
    ScalerSetByte(PDF_15_USB_BUF_DATA1, ucValueTemp2);
    ScalerSetByte(PDF_16_USB_BUF_DATA2, ucValueTemp3);
    ScalerSetByte(PDF_17_USB_BUF_DATA3, ucValueTemp4);   // write data to buffer
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB OHCI Memory Field Data
// Input Value  : Memory Address , Memory Field Address
// Output Value : Memory Field Data
//----------------------------------------------------------------------------------------------------
DWORD ScalerUsbU2HostGetOHCIMemoryField(WORD usAddr, WORD usFieldAddr)
{
    BYTE ucWordNo = 0;
    BYTE ucBitNo = 0;
    DWORD ulValueTemp = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;

    ucWordNo = (BYTE)((usFieldAddr & 0x3F00) >> 8);
    ucBitNo = (BYTE)(usFieldAddr & 0x001F);

    ScalerUsbU2HostSetOHCIMemoryAddr(usAddr, usFieldAddr);

    ucValueTemp1 = ScalerGetByte(PDF_14_USB_BUF_DATA0);
    ucValueTemp2 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
    ucValueTemp3 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
    ucValueTemp4 = ScalerGetByte(PDF_17_USB_BUF_DATA3);

    if((usFieldAddr & _BIT14) == _BIT14)   // HCCA Element
    {
        switch(ucWordNo)
        {
            case 0x20:
                if(ucBitNo == 0x00)   // Frame Number : 16-bit
                {
                    ulValueTemp = ((DWORD)ucValueTemp2 << 8) | ucValueTemp1;
                }
                else if(ucBitNo == 0x10)    // Pad1 : 16-bit
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 8) | ucValueTemp3;
                }
                else
                {
                    // Address is not defined.
                }
                break;

            case 0x21:
                if(ucBitNo == 0x00)   // Done Head : 32-bit
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | (DWORD)ucValueTemp1;
                }
                else
                {
                    // Address is not defined.
                }
                break;

            default:
                break;
        }
    }
    else if((usFieldAddr & _BIT15) == 0x00)   // ED Element
    {
        switch(ucWordNo)
        {
            case 0x00:
                if(ucBitNo == 0x00)   // Device Address : 7-bit
                {
                    ulValueTemp = (DWORD)(ucValueTemp1 & 0x7F);
                }
                else if(ucBitNo == 0x07)   // EndPt (Endpoint Number) : 4-bits
                {
                    ulValueTemp = (((DWORD)ucValueTemp2 & 0x07) << 1) | (((DWORD)ucValueTemp1 & 0x80) >> 7);
                }
                else if(ucBitNo == 0x0B)   // Token Direction : 2-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp2 & 0x18) >> 3);
                }
                else if(ucBitNo == 0x0D)   // Endpoint Speed : 1-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp2 & 0x20) >> 5);
                }
                else if(ucBitNo == 0x0E)   // Skip : 1-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp2 & 0x40) >> 6);
                }
                else if(ucBitNo == 0x0F)   // Format : 1-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp2 & 0x80) >> 7);
                }
                else if(ucBitNo == 0x10)   // Maximum Packet Length : 11-bits
                {
                    ulValueTemp = (((DWORD)ucValueTemp4 & 0x07) << 8) | (DWORD)ucValueTemp3;
                }
                else
                {
                    // Address is not defined.
                }
                break;

            case 0x01:
                if(ucBitNo == 0x04)   // TD Queue Tail Pointer : 28-bits
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x02:
                if(ucBitNo == 0x00)   // Halted : 1-bits
                {
                    ulValueTemp = (DWORD)(ucValueTemp1 & 0x01);
                }
                else if(ucBitNo == 0x01)   // toggle carry bit : 1-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp1 & 0x02) >> 1);
                }
                else if(ucBitNo == 0x04)   // TD Queue Head Pointer : 28-bits
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x03:
                if(ucBitNo == 0x04)   // Next Endpoint Descriptor : 28-bits
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            default:
                break;
        }
    }
    else   // TD Element
    {
        switch(ucWordNo)
        {
            case 0x00:
                if(ucBitNo == 0x12)   // Buffer Rounding : 1-bit
                {
                    ulValueTemp = (DWORD)((ucValueTemp3 & 0x04) >> 2);
                }
                else if(ucBitNo == 0x13)   // PID Direction : 2-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp3 & 0x18) >> 3);
                }
                else if(ucBitNo == 0x15)   // Delay Interrupt : 3-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp3 & 0xE0) >> 5);
                }
                else if(ucBitNo == 0x18)   // Data Toggle : 2-bits
                {
                    ulValueTemp = (DWORD)(ucValueTemp4 & 0x03);
                }
                else if(ucBitNo == 0x1A)   // Error Count : 2-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp4 & 0x0C) >> 2);
                }
                else if(ucBitNo == 0x1C)   // Condition Code : 4-bits
                {
                    ulValueTemp = (DWORD)((ucValueTemp4 & 0xF0) >> 4);
                }
                else
                {
                    // Address is not defined.
                }
                break;

            case 0x01:
                if(ucBitNo == 0x00)   // Current Buffer Pointer : 32-bits
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | (DWORD)ucValueTemp1;
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x02:
                if(ucBitNo == 0x04)   // Next TD : 28-bits
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | ((DWORD)ucValueTemp1 & 0xF0);
                }
                else
                {
                    // Address is not define
                }
                break;

            case 0x03:
                if(ucBitNo == 0x00)   // Buffer End : 32-bits
                {
                    ulValueTemp = ((DWORD)ucValueTemp4 << 24) | ((DWORD)ucValueTemp3 << 16) | ((DWORD)ucValueTemp2 << 8) | (DWORD)ucValueTemp1;
                }
                else
                {
                    // Address is not define
                }
                break;

            default:
                break;
        }
    }

    return ulValueTemp;
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB OHCI HCCA Interrupt Table
// Input Value  : HCCA Table Address , HCCA Table Number , HCCA Table Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetOHCIHccaIntTab(WORD usAddr, BYTE ucTabNo, DWORD ulValue)
{
    WORD usAddrTemp = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;

    usAddrTemp = usAddr + (ucTabNo * 4);

    ucValueTemp1 = (BYTE)(ulValue & 0x000000FF);
    ucValueTemp2 = (BYTE)((ulValue & 0x0000FF00) >> 8);
    ucValueTemp3 = (BYTE)((ulValue & 0x00FF0000) >> 16);
    ucValueTemp4 = (BYTE)((ulValue & 0xFF000000) >> 24);

    ScalerUsbU2HostSetOHCIMemoryAddr(usAddrTemp, 0);
    ScalerSetByte(PDF_14_USB_BUF_DATA0, ucValueTemp1);
    ScalerSetByte(PDF_15_USB_BUF_DATA1, ucValueTemp2);
    ScalerSetByte(PDF_16_USB_BUF_DATA2, ucValueTemp3);
    ScalerSetByte(PDF_17_USB_BUF_DATA3, ucValueTemp4);   // write data to buffer
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB OHCI Root Hub Status Register Data by Bit Mode
// Input Value  : Register Address , Register Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetOHCIRhStsRegBitField(WORD usAddr, BYTE ucValue)
{
    BYTE ucAddrTemp1 = 0;
    BYTE ucAddrTemp2 = 0;

    if((usAddr & _BIT12) == _BIT12)
    {
        ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT3, _BIT3);   // select OHCI register
    }
    else
    {
        return;   // select EHCI register
    }

    ucAddrTemp1 = (BYTE)((usAddr & 0x0FF0) >> 4);
    ucAddrTemp2 = (BYTE)(usAddr & 0x000F);

    ScalerSetByte(PDF_03_USB_REG_ADDR, ucAddrTemp1);   // Set register address for read
    ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT1, _BIT1);   // apply usb read
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready

    if(ucAddrTemp2 == 0x00)
    {
        ScalerSetByte(PDF_04_USB_REG_DATA0, ucValue);
        ScalerSetByte(PDF_05_USB_REG_DATA1, 0x00);
        ScalerSetByte(PDF_06_USB_REG_DATA2, 0x00);
        ScalerSetByte(PDF_07_USB_REG_DATA3, 0x00);
    }
    else if(ucAddrTemp2 == 0x01)
    {
        ScalerSetByte(PDF_04_USB_REG_DATA0, 0x00);
        ScalerSetByte(PDF_05_USB_REG_DATA1, ucValue);
        ScalerSetByte(PDF_06_USB_REG_DATA2, 0x00);
        ScalerSetByte(PDF_07_USB_REG_DATA3, 0x00);
    }
    else if(ucAddrTemp2 == 0x02)
    {
        ScalerSetByte(PDF_04_USB_REG_DATA0, 0x00);
        ScalerSetByte(PDF_05_USB_REG_DATA1, 0x00);
        ScalerSetByte(PDF_06_USB_REG_DATA2, ucValue);
        ScalerSetByte(PDF_07_USB_REG_DATA3, 0x00);
    }
    else if(ucAddrTemp2 == 0x03)
    {
        ScalerSetByte(PDF_04_USB_REG_DATA0, 0x00);
        ScalerSetByte(PDF_05_USB_REG_DATA1, 0x00);
        ScalerSetByte(PDF_06_USB_REG_DATA2, 0x00);
        ScalerSetByte(PDF_07_USB_REG_DATA3, ucValue);
    }
    else
    {
        // undefined address
    }
    ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT0, _BIT0);   // apply usb write
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready
}

/*
//----------------------------------------------------------------------------------------------------
// Description  : Get U2Host OHCI_HCCONTROLHEAD_ED Reg Addr - which will use in sys layer OHCI_HCCONTROLHEAD_ED
// Input Value  : None
// Output Value : U2Host OHCI_HCCONTROLHEAD_ED Reg Addr
//----------------------------------------------------------------------------------------------------
WORD ScalerUsbU2HostGetOHCIHcCtrlHeadEdRegAddr(void)
{
    WORD usU2HostRegAddr = 0;
    usU2HostRegAddr = _PDF_04_PT_120_OHCI_HCCONTROLHEAD_ED_0;

    return usU2HostRegAddr;
}
*/

//----------------------------------------------------------------------------------------------------
// Description  : Get U2Host OHCI_HCCOMMAND_STS Reg Addr - which will use in sys layer OHCI_HCCOMMAND_STS
// Input Value  : None
// Output Value : U2Host OHCI_HCCOMMAND_STS Reg Addr
//----------------------------------------------------------------------------------------------------
WORD ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(void)
{
    WORD usU2HostRegAddr = 0;
    usU2HostRegAddr = _PDF_04_PT_108_OHCI_HCCOMMAND_STS_0;

    return usU2HostRegAddr;
}
#endif // end of #if(_USB2_HOST_OHCI_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------
// Description  : Set USB PHY Register Address Process
// Input Value  : Register Address
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetPhyRegAddr(WORD usAddr)
{
    BYTE ucAddrTemp = 0;
    BYTE ucValueTemp = 0;

    // Select EHCI register
    ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT3, 0x00);
    // Select 0xDF04_00A4
    ScalerSetByte(PDF_03_USB_REG_ADDR, 0xA4);

    ScalerSetByte(PDF_04_USB_REG_DATA0, 0x00);
    ScalerSetByte(PDF_06_USB_REG_DATA2, 0x00);
    ScalerSetByte(PDF_07_USB_REG_DATA3, 0x00);

    for(ucValueTemp = 0; ucValueTemp < 4; ucValueTemp++)
    {
        if(ucValueTemp == 0)
        {
            ucAddrTemp = (BYTE)(usAddr & 0x000F);
            ScalerSetByte(PDF_05_USB_REG_DATA1, (0x20 | ucAddrTemp));// |0x20: let bit5 = 1 .bit4(vcontrolloadm) 1-0 + Address[3:0]Ready
        }
        else if(ucValueTemp == 1)
        {
            ucAddrTemp = (BYTE)(usAddr & 0x000F);
            ScalerSetByte(PDF_05_USB_REG_DATA1, (0x30 | ucAddrTemp));// |0x30: let bit5:4 = 11. bit4(vcontrolloadm) 0-1 + Address[3:0]Ready
        }
        else if(ucValueTemp == 2)
        {
            ucAddrTemp = (BYTE)(usAddr & 0x00F0) >> 4;
            ScalerSetByte(PDF_05_USB_REG_DATA1, (0x20 | ucAddrTemp));// |0x20: let bit5 = 1. bit4(vcontrolloadm) 1-0 + Address[7:4]Ready
        }
        else
        {
            ucAddrTemp = (BYTE)(usAddr & 0x00F0) >> 4;
            ScalerSetByte(PDF_05_USB_REG_DATA1, (0x30 | ucAddrTemp));// |0x30: let bit5:4 = 11 bit4(vcontrolloadm) 0-1 + Address[7:4]Ready
        }

        ScalerSetByte(PDF_02_USB_REGIF_CTRL, 0x01);   // apply usb regif write
        ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB PHY Register Page Process
// Input Value  : Register Address
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetPhyRegPage(WORD usAddr)
{
    BYTE ucValueTemp = 0x00;

    ScalerUsbU2HostSetPhyRegAddr(((BYTE)(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C) & (~_BIT5)));   // BIT5=0 for read register ; BIT5=1 for write register
    ScalerSetByte(PDF_03_USB_REG_ADDR, 0xA4);   // select 0xDF04_00A4
    ScalerSetByte(PDF_02_USB_REGIF_CTRL, 0x02); // apply read
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready
    ucValueTemp = ScalerGetByte(PDF_04_USB_REG_DATA0); // read 0xDF04_00A4_0:vstatus (It's value of _PDF_62_PT_F4_USB_PHY_CTR_REG_0C)

    // Set USB PHY Register Page
    if(((ucValueTemp & (_BIT6 | _BIT5)) == 0x00) && ((usAddr & (_BIT9 | _BIT8)) == _BIT8))   // current page=0,target page=1
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT5);   // select USB PHY Page1
        ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
        ScalerUsbU2HostSetPhyRegAddr(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == 0x00) && ((usAddr & (_BIT9 | _BIT8)) == _BIT9))   // current page=0,target page=2
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT6);   // select USB PHY Page2
        ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
        ScalerUsbU2HostSetPhyRegAddr(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT5) && ((usAddr & (_BIT9 | _BIT8)) == 0x0000))   // current page=1,target page=0
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5)));   // select USB PHY Page0
        ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
        ScalerUsbU2HostSetPhyRegAddr(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT5) && ((usAddr & (_BIT9 | _BIT8)) == _BIT9))   // current page=1,target page=2
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT6);   // select USB PHY Page2
        ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
        ScalerUsbU2HostSetPhyRegAddr(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT6) && ((usAddr & (_BIT9 | _BIT8)) == 0x0000))   // current page=2,target page=0
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5)));   // select USB PHY Page0
        ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
        ScalerUsbU2HostSetPhyRegAddr(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT6) && ((usAddr & (_BIT9 | _BIT8)) == _BIT8))   // current page=2,target page=1
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT5);   // select USB PHY Page1
        ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
        ScalerUsbU2HostSetPhyRegAddr(_PDF_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else
    {
        // Don't need to change PHY page
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Read USB PHY Register Data by Byte Mode
// Input Value  : Register Address
// Output Value : Register Data
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbU2HostGetPhyRegByte(WORD usAddr)
{
    BYTE ucAddrTemp = 0x00;
    BYTE ucValueTemp = 0x00;

    ScalerUsbU2HostSetPhyRegPage(usAddr);

    // Get USB PHY Register Value
    ucAddrTemp = (BYTE)(usAddr & (~_BIT5));
    ScalerUsbU2HostSetPhyRegAddr(ucAddrTemp);
    ScalerSetByte(PDF_03_USB_REG_ADDR, 0xA4);   // set read register address
    ScalerSetByte(PDF_02_USB_REGIF_CTRL, 0x02);   // apply usb regif read
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready
    ucValueTemp = ScalerGetByte(PDF_04_USB_REG_DATA0);

    return ucValueTemp;
}

//----------------------------------------------------------------------------------------------------
// Description  : Write USB PHY Register Data by Byte Mode
// Input Value  : Register Address , Register Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetPhyRegByte(WORD usAddr, BYTE ucValue)
{
    // Page select/change
    ScalerUsbU2HostSetPhyRegPage(usAddr);

    // Set USB PHY Register Value
    ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValue);   // data prepare
    ScalerUsbU2HostSetPhyRegAddr(usAddr);   // set address & write data to register
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB PHY Register Data by Bit Mode
// Input Value  : Register Address , "AND" Bit No. , "OR" Bit No.
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetPhyRegBitField(WORD usAddr, DWORD ulAnd, BYTE ucOr)
{
    BYTE ucValueTemp = 0;

    // Set USB PHY Register Value
    ucValueTemp = ScalerUsbU2HostGetPhyRegByte(usAddr);
    ucValueTemp = (ucValueTemp & (BYTE)ulAnd) | (ucOr);
    ScalerSetByte(PDF_62_USB_VSTATUS_REG, ucValueTemp);   // data prepare
    ScalerUsbU2HostSetPhyRegAddr(usAddr);   // set address & write data to register
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB PHY Register Data by Bit Mode
// Input Value  : Register Address, ucAnd
// Output Value : None
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbU2HostGetPhyRegBitField(WORD usAddr, BYTE ucAnd)
{
    BYTE ucValueTemp = 0;

    // Set USB PHY Register Value
    ucValueTemp = ScalerUsbU2HostGetPhyRegByte(usAddr);
    ucValueTemp = (ucValueTemp & ucAnd);
    return ucValueTemp;
}

//----------------------------------------------------------------------------------------------------
// USB EHCI/OHCI Operational Register Access Function
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// Description  : Get USB Data Port Register by Byte Mode
// Input Value  : Register Address
// Output Value : Register Data
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbU2HostGetDataPortByte(WORD usAddr)
{
    BYTE ucAddrTemp1 = 0;
    BYTE ucAddrTemp2 = 0;
    BYTE ucValueTemp = 0;

    if((usAddr & _BIT12) == _BIT12)
    {
        ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT3, _BIT3);   // select OHCI register
    }
    else
    {
        ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT3, 0x00);   // select EHCI register
    }

    ucAddrTemp1 = (BYTE)((usAddr & 0x0FF0) >> 4);
    ucAddrTemp2 = (BYTE)(usAddr & 0x000F);

    ScalerSetByte(PDF_03_USB_REG_ADDR, ucAddrTemp1);   // Set register address for read
    ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT1, _BIT1);   // apply usb read
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready

    if(ucAddrTemp2 == 0x00)
    {
        ucValueTemp = ScalerGetByte(PDF_04_USB_REG_DATA0);
    }
    else if(ucAddrTemp2 == 0x01)
    {
        ucValueTemp = ScalerGetByte(PDF_05_USB_REG_DATA1);
    }
    else if(ucAddrTemp2 == 0x02)
    {
        ucValueTemp = ScalerGetByte(PDF_06_USB_REG_DATA2);
    }
    else if(ucAddrTemp2 == 0x03)
    {
        ucValueTemp = ScalerGetByte(PDF_07_USB_REG_DATA3);
    }
    else
    {
        // undefined address
    }
    return ucValueTemp;
}

//----------------------------------------------------------------------------------------------------
// Note : This function can't execute individually.
//        ScalerUsbU2HostGetDataPortByte() must execute firstly.
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// Description  : Set USB Data Port by Byte Mode
// Input Value  : Register Address , Register Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetDataPortByte(WORD usAddr, BYTE ucValue)
{
    BYTE ucAddrTemp = 0;

    ucAddrTemp = (BYTE)(usAddr & 0x000F);

    if(ucAddrTemp == 0x00)
    {
        ScalerSetByte(PDF_04_USB_REG_DATA0, ucValue);
    }
    else if(ucAddrTemp == 0x01)
    {
        ScalerSetByte(PDF_05_USB_REG_DATA1, ucValue);
    }
    else if(ucAddrTemp == 0x02)
    {
        ScalerSetByte(PDF_06_USB_REG_DATA2, ucValue);
    }
    else if(ucAddrTemp == 0x03)
    {
        ScalerSetByte(PDF_07_USB_REG_DATA3, ucValue);
    }
    else
    {
        // undefined address
    }
    ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT0, _BIT0);   // apply usb write
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB Register Data by Byte Mode
// Input Value  : Register Address
// Output Value : Register Data
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbU2HostGetRegByte(WORD usAddr)
{
    BYTE ucValueTemp = 0;

    ucValueTemp = ScalerUsbU2HostGetDataPortByte(usAddr);
    return ucValueTemp;
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB Register Data by DWORD Mode
// Input Value  : Register Address
// Output Value : Register Data
//----------------------------------------------------------------------------------------------------
DWORD ScalerUsbU2HostGetRegDword(WORD usAddr)
{
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;
    DWORD ulValueTempResult = 0;

    ucValueTemp1 = ScalerUsbU2HostGetDataPortByte(usAddr);
    ucValueTemp2 = ScalerUsbU2HostGetDataPortByte(usAddr + 1);
    ucValueTemp3 = ScalerUsbU2HostGetDataPortByte(usAddr + 2);
    ucValueTemp4 = ScalerUsbU2HostGetDataPortByte(usAddr + 3);

    ulValueTempResult = TO_DWORD(ucValueTemp4, ucValueTemp3, ucValueTemp2, ucValueTemp1);

    return ulValueTempResult;
}
//----------------------------------------------------------------------------------------------------
// Description  : Set USB Register Data by Byte Mode
// Input Value  : Register Address , Register Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetRegByte(WORD usAddr, BYTE ucValue)
{
    BYTE ucValueTemp = 0;

    ucValueTemp = ScalerUsbU2HostGetDataPortByte(usAddr);
    ucValueTemp = ucValueTemp;
    ScalerUsbU2HostSetDataPortByte(usAddr, ucValue);   // Note : This function can't execute individually.
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB Register Data by Bit Mode
// Input Value  : Register Address , Bit No.
// Output Value : Register Data
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbU2HostGetRegBitField(WORD usAddr, BYTE ucAnd)
{
    BYTE ucValueTemp = 0;

    ucValueTemp = ScalerUsbU2HostGetDataPortByte(usAddr);
    ucValueTemp = (ucValueTemp & ucAnd);
    return ucValueTemp;
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB Register Data by Bit Mode
// Input Value  : Register Address, "AND" Bit No. , "OR" Bit No
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetRegBitField(WORD usAddr, DWORD ulAnd, BYTE ucOr)
{
    BYTE ucValueTemp = 0;

    ucValueTemp = ScalerUsbU2HostGetDataPortByte(usAddr);
    ucValueTemp = (ucValueTemp & (BYTE)ulAnd) | (ucOr);
    ScalerUsbU2HostSetDataPortByte(usAddr, ucValueTemp);   // Note : This function can't execute individually.
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB Register Data by DWORD Mode
// Input Value  : Register Address , Register Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetRegDword(WORD usAddr, DWORD ulValue)
{
    BYTE ucAddrTemp = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;

    if((usAddr & _BIT12) == _BIT12)
    {
        ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT3, _BIT3);   // select OHCI register
    }
    else
    {
        ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT3, 0x00);   // select EHCI register
    }

    ucAddrTemp = (BYTE)((usAddr & 0x0FF0) >> 4);
    ucValueTemp1 = (BYTE)(ulValue & 0x000000FF);
    ucValueTemp2 = (BYTE)((ulValue & 0x0000FF00) >> 8);
    ucValueTemp3 = (BYTE)((ulValue & 0x00FF0000) >> 16);
    ucValueTemp4 = (BYTE)((ulValue & 0xFF000000) >> 24);

    ScalerSetByte(PDF_03_USB_REG_ADDR, ucAddrTemp);   // Set register address for write
    ScalerSetByte(PDF_04_USB_REG_DATA0, ucValueTemp1);
    ScalerSetByte(PDF_05_USB_REG_DATA1, ucValueTemp2);
    ScalerSetByte(PDF_06_USB_REG_DATA2, ucValueTemp3);
    ScalerSetByte(PDF_07_USB_REG_DATA3, ucValueTemp4);

    ScalerSetBit(PDF_02_USB_REGIF_CTRL, ~_BIT0, _BIT0);   // apply usb write
    ScalerUsbU2HostWaitRegRdy();   // wait for reg access ready
}

//----------------------------------------------------------------------------------------------------
// USB Memory Access Function
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// Description  : Clear USB Memory Space
// Input Value  : Memory Address , Memory Size
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostMemoryClear(WORD usAddr, WORD usSize)
{
    BYTE ucAddrTemp1 = 0;
    BYTE ucAddrTemp2 = 0;
    WORD usSizeTemp = 0;
    WORD usByteNum = 0;

    // RL6829 Support 2K SRAM(0x7FF), RL6952 Support 3K SRAM(0xBFF)
#if(_HW_USB2_HOST_SRAM_SIZE_SUPPORT == _HW_USB2_HOST_SRAM_SIZE_2K)
    ucAddrTemp1 = (BYTE)((usAddr & 0x0700) >> 8);
#else
    ucAddrTemp1 = (BYTE)((usAddr & 0x0B00) >> 8);
#endif
    ucAddrTemp2 = (BYTE)(usAddr & 0x00FF);
    usByteNum = usSize / 4;

    ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp1);
    ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp2);

    for(usSizeTemp = 0; usSizeTemp < usByteNum; usSizeTemp++)
    {
        ScalerSetByte(PDF_14_USB_BUF_DATA0, 0x00);
        ScalerSetByte(PDF_15_USB_BUF_DATA1, 0x00);
        ScalerSetByte(PDF_16_USB_BUF_DATA2, 0x00);
        ScalerSetByte(PDF_17_USB_BUF_DATA3, 0x00);
    }
}

//----------------------------------------------------------------------------------------------------
// USB Buffer Access Function
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
// Description  : Set USB Buffer Field Data
// Input Value  : Buffer Address , Buffer Field Address
// Output Value : Buffer Field Data
// Note : The length of ByteField can not exceed 2-bytes for ScalerUsbU2HostGetBufferField()
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetBufferField(WORD usAddr, DWORD ulByteField, BYTE *pucData)
{
    WORD usAddrTemp = 0;
    WORD usAddrTemp2 = 0;
    BYTE ucAddrTemp1 = 0;
    BYTE ucAddrTemp2 = 0;
    BYTE ucAddrTemp3 = 0;
    BYTE ucAddrTemp4 = 0;
    WORD usWordNoTemp = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;
    BYTE ucValueTemp5 = 0;
    BYTE ucValueTemp6 = 0;
    BYTE ucValueTemp7 = 0;
    BYTE ucValueTemp8 = 0;

    BYTE ucByteNoTemp = 0;
    BYTE ucLengthTemp = 0;

    usWordNoTemp = (WORD)((ulByteField & 0xFFFFFF00) >> 8);
    ucByteNoTemp = usWordNoTemp % 4;
    usWordNoTemp = usWordNoTemp / 4;
    ucLengthTemp = (BYTE)(ulByteField & 0x0000000F);

    usAddrTemp = usAddr + usWordNoTemp * 4;

    ucAddrTemp1 = (BYTE)((usAddrTemp & 0x0F00) >> 8);
    ucAddrTemp2 = (BYTE)(usAddrTemp & 0x00FC);   // 32-bit Addressing
    ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp1);
    ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp2);

    ucValueTemp1 = ScalerGetByte(PDF_14_USB_BUF_DATA0);   // read data from buffer
    ucValueTemp2 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
    ucValueTemp3 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
    ucValueTemp4 = ScalerGetByte(PDF_17_USB_BUF_DATA3);

    if((ucByteNoTemp == 0x03) && (ucLengthTemp == 0x02))
    {
        usAddrTemp2 = usAddr + (usWordNoTemp + 1) * 4;

        ucAddrTemp3 = (BYTE)((usAddrTemp2 & 0x0F00) >> 8);
        ucAddrTemp4 = (BYTE)(usAddrTemp2 & 0x00FC);   // 32-bit Addressing
        ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp3);
        ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp4);

        ucValueTemp5 = ScalerGetByte(PDF_14_USB_BUF_DATA0);   // read data from buffer
        ucValueTemp6 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
        ucValueTemp7 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
        ucValueTemp8 = ScalerGetByte(PDF_17_USB_BUF_DATA3);
    }

    switch(ucByteNoTemp)
    {
        case 0x00:
            if(ucLengthTemp == 0x01)
            {
                // ScalerSetByte(PDF_14_USB_BUF_DATA0, pData[0]);
                ucValueTemp1 = pucData[0];
            }
            else   // ucLenNumTemp == 0x02
            {
                // ScalerSetByte(PDF_14_USB_BUF_DATA0, pData[0]);
                // ScalerSetByte(PDF_15_USB_BUF_DATA1, pData[1]);
                ucValueTemp1 = pucData[0];
                ucValueTemp2 = pucData[1];
            }
            break;

        case 0x01:
            if(ucLengthTemp == 0x01)
            {
                // ScalerSetByte(PDF_15_USB_BUF_DATA1, pData[0]);
                ucValueTemp2 = pucData[0];
            }
            else   // ucLenNumTemp == 0x02
            {
                // ScalerSetByte(PDF_15_USB_BUF_DATA1, pData[0]);
                // ScalerSetByte(PDF_16_USB_BUF_DATA2, pData[1]);
                ucValueTemp2 = pucData[0];
                ucValueTemp3 = pucData[1];
            }
            break;

        case 0x02:
            if(ucLengthTemp == 0x01)
            {
                // ScalerSetByte(PDF_16_USB_BUF_DATA2, pData[0]);
                ucValueTemp3 = pucData[0];
            }
            else   // ucLenNumTemp == 0x02
            {
                // ScalerSetByte(PDF_16_USB_BUF_DATA2, pData[0]);
                // ScalerSetByte(PDF_17_USB_BUF_DATA3, pData[1]);
                ucValueTemp3 = pucData[0];
                ucValueTemp4 = pucData[1];
            }
            break;

        case 0x03:
            if(ucLengthTemp == 0x01)
            {
                // ScalerSetByte(PDF_17_USB_BUF_DATA3, pData[0]);
                ucValueTemp4 = pucData[0];
            }
            else   // ucLenNumTemp == 0x02
            {
                ScalerSetByte(PDF_17_USB_BUF_DATA3, pucData[0]);
                ucValueTemp4 = pucData[0];
                ucValueTemp5 = pucData[1];

                ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp3);
                ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp4);

                ScalerSetByte(PDF_14_USB_BUF_DATA0, ucValueTemp5);
                ScalerSetByte(PDF_15_USB_BUF_DATA1, ucValueTemp6);
                ScalerSetByte(PDF_16_USB_BUF_DATA2, ucValueTemp7);
                ScalerSetByte(PDF_17_USB_BUF_DATA3, ucValueTemp8);
            }
            break;

        default:
            break;
    }

    ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp1);
    ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp2);

    ScalerSetByte(PDF_14_USB_BUF_DATA0, ucValueTemp1);
    ScalerSetByte(PDF_15_USB_BUF_DATA1, ucValueTemp2);
    ScalerSetByte(PDF_16_USB_BUF_DATA2, ucValueTemp3);
    ScalerSetByte(PDF_17_USB_BUF_DATA3, ucValueTemp4);

    return;
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB Buffer Field Data
// Input Value  : Buffer Address , Buffer Field Address
// Output Value : Buffer Field Data
// Note : The length of ByteField can not exceed 2-bytes for ScalerUsbU2HostGetBufferField()
//----------------------------------------------------------------------------------------------------
WORD ScalerUsbU2HostGetBufferField(WORD usAddr, DWORD ulByteField)
{
    WORD usAddrTemp = 0;
    BYTE ucAddrTemp1 = 0;
    BYTE ucAddrTemp2 = 0;
    WORD usWordNoTemp = 0;

    BYTE ucByteNoTemp = 0;
    BYTE ucLengthTemp = 0;
    BYTE ucValueTemp1 = 0;
    BYTE ucValueTemp2 = 0;
    BYTE ucValueTemp3 = 0;
    BYTE ucValueTemp4 = 0;
    BYTE ucValueTemp5 = 0;
    WORD usValueTemp = 0;

    usWordNoTemp = (WORD)((ulByteField & 0xFFFFFF00) >> 8);
    ucByteNoTemp = usWordNoTemp % 4;
    usWordNoTemp = usWordNoTemp / 4;
    ucLengthTemp = (BYTE)(ulByteField & 0x0000000F);

    usAddrTemp = usAddr + usWordNoTemp * 4;

    ucAddrTemp1 = (BYTE)((usAddrTemp & 0x0F00) >> 8);
    ucAddrTemp2 = (BYTE)(usAddrTemp & 0x00FC);   // 32-bit Addressing
    ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp1);
    ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp2);

    ucValueTemp1 = ScalerGetByte(PDF_14_USB_BUF_DATA0);   // read data from buffer
    ucValueTemp2 = ScalerGetByte(PDF_15_USB_BUF_DATA1);
    ucValueTemp3 = ScalerGetByte(PDF_16_USB_BUF_DATA2);
    ucValueTemp4 = ScalerGetByte(PDF_17_USB_BUF_DATA3);

    if((ucByteNoTemp == 0x03) && (ucLengthTemp == 0x02))
    {
        usAddrTemp = usAddr + (usWordNoTemp + 1) * 4;

        ucAddrTemp1 = (BYTE)((usAddrTemp & 0x0F00) >> 8);
        ucAddrTemp2 = (BYTE)(usAddrTemp & 0x00FC);   // 32-bit Addressing
        ScalerSetByte(PDF_12_USB_BUF_ADR_MSB, ucAddrTemp1);
        ScalerSetByte(PDF_13_USB_BUF_ADR_LSB, ucAddrTemp2);

        ucValueTemp5 = ScalerGetByte(PDF_14_USB_BUF_DATA0);   // read data from buffer
    }

    switch(ucByteNoTemp)
    {
        case 0x00:
            if(ucLengthTemp == 0x01)
            {
                usValueTemp = (WORD)ucValueTemp1;
            }
            else   // ucLenNumTemp == 0x02
            {
                usValueTemp = (WORD)((ucValueTemp2 << 8) | ucValueTemp1);
            }
            break;

        case 0x01:
            if(ucLengthTemp == 0x01)
            {
                usValueTemp = (WORD)ucValueTemp2;
            }
            else   // ucLenNumTemp == 0x02
            {
                usValueTemp = (WORD)((ucValueTemp3 << 8) | ucValueTemp2);
            }
            break;

        case 0x02:
            if(ucLengthTemp == 0x01)
            {
                usValueTemp = (WORD)ucValueTemp3;
            }
            else   // ucLenNumTemp == 0x02
            {
                usValueTemp = (WORD)((ucValueTemp4 << 8) | ucValueTemp3);
            }
            break;

        case 0x03:
            if(ucLengthTemp == 0x01)
            {
                usValueTemp = (WORD)ucValueTemp4;
            }
            else   // ucLenNumTemp == 0x02
            {
                usValueTemp = (WORD)((ucValueTemp5 << 8) | ucValueTemp4);
            }
            break;

        default:
            break;
    }

    return usValueTemp;
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB Buffer Bulk Data
// Input Value  : Buffer Address , Start Address , Intput Arry Address , Get Data Length
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetBufferBulkData(WORD usBufAddr, WORD usStartAddr, BYTE *pucArray, WORD usDataLength)
{
    BYTE ucResByteNum = 0;
    WORD usReadNum = 0;
    BYTE ucStartOffsetAddr = 0;
    BYTE ucValueTemp1 = 0;
    WORD usValueTemp2 = 0;
    DWORD ulValueTemp3 = 0;

    DWORD ulValueTemp = 0;
    // BYTE ucloop = 0;

    usReadNum = usDataLength / 4;
    ucValueTemp1 = usDataLength % 4;

    ucStartOffsetAddr = usStartAddr % 4;
    ucResByteNum = 4 - ucStartOffsetAddr;

    if(((ucValueTemp1 == 0x00) && (ucStartOffsetAddr != 0x00)) || (ucValueTemp1 != 0x00))
    {
        usReadNum = usReadNum + 1;
    }

    if(ucValueTemp1 > ucResByteNum)
    {
        usReadNum = usReadNum + 1;
    }

    for(usValueTemp2 = 0; usValueTemp2 < usReadNum; usValueTemp2++)
    {
        if((usValueTemp2 == 0x00) && (ucStartOffsetAddr != 0x00))
        {
            ulValueTemp = ((DWORD)(usStartAddr << 8) | 0x0001);
            *pucArray = ScalerUsbU2HostGetBufferField(usBufAddr, ulValueTemp);
            if(ucStartOffsetAddr == 0x01)
            {
                *(pucArray + 1) = ScalerGetByte(PDF_16_USB_BUF_DATA2);
                *(pucArray + 2) = ScalerGetByte(PDF_17_USB_BUF_DATA3);
            }
            else if(ucStartOffsetAddr == 0x02)
            {
                *(pucArray + 1) = ScalerGetByte(PDF_17_USB_BUF_DATA3);
            }
        }
        else if((usValueTemp2 > 0x00) && (ucStartOffsetAddr != 0x00))
        {
            ulValueTemp3 = usStartAddr + ucResByteNum + (usValueTemp2 - 1) * 4;
            ulValueTemp = ((DWORD)(ulValueTemp3 << 8) | 0x0001);
            *(pucArray + (usValueTemp2 * 4) - ucStartOffsetAddr) = (BYTE)ScalerUsbU2HostGetBufferField(usBufAddr, ulValueTemp);
            *(pucArray + (usValueTemp2 * 4) - ucStartOffsetAddr + 1) = ScalerGetByte(PDF_15_USB_BUF_DATA1);
            *(pucArray + (usValueTemp2 * 4) - ucStartOffsetAddr + 2) = ScalerGetByte(PDF_16_USB_BUF_DATA2);
            *(pucArray + (usValueTemp2 * 4) - ucStartOffsetAddr + 3) = ScalerGetByte(PDF_17_USB_BUF_DATA3);
        }
        else   // if(ucStartOffsetAddr == 0x00)
        {
            ulValueTemp3 = usStartAddr + usValueTemp2 * 4;
            ulValueTemp = ((DWORD)(ulValueTemp3 << 8) | 0x0001);
            *(pucArray + (usValueTemp2 * 4)) = (BYTE)ScalerUsbU2HostGetBufferField(usBufAddr, ulValueTemp);
            *(pucArray + (usValueTemp2 * 4) + 1) = ScalerGetByte(PDF_15_USB_BUF_DATA1);
            *(pucArray + (usValueTemp2 * 4) + 2) = ScalerGetByte(PDF_16_USB_BUF_DATA2);
            *(pucArray + (usValueTemp2 * 4) + 3) = ScalerGetByte(PDF_17_USB_BUF_DATA3);
        }
    }
/*
    for(ucloop = 0; ucloop < usDataLength; ucloop++)
    {
        DebugMessageU2HostEHCI("Get Buffer Data", pucArray[ucloop]);
    }
*/
}


//****************************************************************************************************
// USB Tool Function
//****************************************************************************************************
//----------------------------------------------------------------------------------------------------
// Description  : Wait Ready for USB Register Read/Write Action
// Input Value  : None
// Output Value : _TRUE -> Register Access Finished ; _FALSE -> Register Access Not Finished
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostWaitRegRdy(void)
{
    BYTE ucDelayTemp = 2;

    while((ScalerGetBit(PDF_02_USB_REGIF_CTRL, _BIT2) == _BIT2) && (--ucDelayTemp != 0))   // wait for write ready
    {
        DELAY_5US();
    }

    if(ucDelayTemp > 0)
    {
        return _TRUE;
    }
    else
    {
        DebugMessageU2Host("Time-out Fail for EHCI/OHCI Register Access", 0);

        return _FALSE;
    }
}


//----------------------------------------------------------------------------------------------------
// Description  : USB Enable Schedule Process
// Input Value  : Schedule Type : Asynchronous / Periodic , Enable or Disable
// Output Value : _TRUE -> Success ; _FALSE -> Fail
//----------------------------------------------------------------------------------------------------
bit ScalerUsbU2HostScheduleEnable(EnumUsbScheduleType enumSchType, bit bEnType)
{
    BYTE ucDelayTemp = 200;

    if((enumSchType == _U2HOST_SCHEDULE_ASYNC) && (bEnType == _DISABLE))
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~_BIT5, 0x00);

        while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == _BIT7) && (--ucDelayTemp != 0))   // wait for write ready
        {
            DELAY_5US();
        }
    }
    else if((enumSchType == _U2HOST_SCHEDULE_ASYNC) && (bEnType == _ENABLE))
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~_BIT5, _BIT5);

        while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT7) == 0x00) && (--ucDelayTemp != 0))   // wait for write ready
        {
            DELAY_5US();
        }
    }
    else if((enumSchType == _U2HOST_SCHEDULE_PERIODIC) && (bEnType == _DISABLE))
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~_BIT4, 0x00);

        while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT6) == _BIT6) && (--ucDelayTemp != 0))   // wait for write ready
        {
            DELAY_5US();
        }
    }
    else if((enumSchType == _U2HOST_SCHEDULE_PERIODIC) && (bEnType == _ENABLE))
    {
        ScalerUsbU2HostSetRegBitField(_PDF_04_PT_010_EHCI_USB_CMD_0, ~_BIT4, _BIT4);

        while((ScalerUsbU2HostGetRegBitField(_PDF_04_PT_014_EHCI_USB_STS_1, _BIT6) == 0x00) && (--ucDelayTemp != 0))   // wait for write ready
        {
            DELAY_5US();
        }
    }
    else
    {
        DebugMessageU2Host("Schedule Enable/Disable Format Err", 0);
        return _FALSE;
    }


    if(ucDelayTemp > 0)
    {
        return _TRUE;
    }
    else
    {
        DebugMessageU2Host("Time-out Fail for Schedule Enable/Disable", 0);
        return _FALSE;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Set U2host send cmd
// Input Value  : Array where contain cmd value,array length
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetCmdBufData(BYTE *pucData, BYTE ucLength)
{
    BYTE ucLoop = 0;

    for(ucLoop = 0; ucLoop < (ucLength / 4); ucLoop++)
    {
        ScalerSetByte(PDF_14_USB_BUF_DATA0, pucData[(4 * ucLoop)]);
        ScalerSetByte(PDF_15_USB_BUF_DATA1, pucData[(4 * ucLoop + 1)]);
        ScalerSetByte(PDF_16_USB_BUF_DATA2, pucData[(4 * ucLoop + 2)]);
        ScalerSetByte(PDF_17_USB_BUF_DATA3, pucData[(4 * ucLoop + 3)]);
    }
    if((ucLength % 4) == 0)
    {
        return;
    }
    else
    {
        if((ucLength % 4) == 1)
        {
            ScalerSetByte(PDF_14_USB_BUF_DATA0, pucData[(4 * ucLoop)]);
        }
        else if((ucLength % 4) == 2)
        {
            ScalerSetByte(PDF_14_USB_BUF_DATA0, pucData[(4 * ucLoop)]);
            ScalerSetByte(PDF_15_USB_BUF_DATA1, pucData[(4 * ucLoop + 1)]);
        }
        else if((ucLength % 4) == 3)
        {
            ScalerSetByte(PDF_14_USB_BUF_DATA0, pucData[(4 * ucLoop)]);
            ScalerSetByte(PDF_15_USB_BUF_DATA1, pucData[(4 * ucLoop + 1)]);
            ScalerSetByte(PDF_16_USB_BUF_DATA2, pucData[(4 * ucLoop + 2)]);
        }
        // the Data3 Byte must be written once to trigger HW update Data0/1/2/3 into Buffer
        ScalerSetByte(PDF_17_USB_BUF_DATA3, 0x00);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB Buffer Field Data
// Input Value  : Buffer Address , Length, Buffer Field Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostSetBufferData(WORD usbufferAddr, WORD usLen, BYTE *pucData)
{
    DWORD ulIndex = 0;
    DWORD ulOffset = 0;

    for(ulIndex = 0; ulIndex < usLen; ulIndex++)
    {
        ulOffset = ((DWORD)((DWORD)ulIndex << 8) | 0x0001);
        ScalerUsbU2HostSetBufferField(usbufferAddr, ulOffset, &pucData[ulIndex]);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Get USB Buffer Field Data
// Input Value  : Buffer Address , Length, Buffer Field Data
// Output Value : None
// Note : The length of ByteField can not exceed 2-bytes for ScalerUsbU2HostGetBufferField()
//----------------------------------------------------------------------------------------------------
void ScalerUsbU2HostGetBufferData(WORD usbufferAddr, WORD usLen, BYTE *pucData)
{
    DWORD ulIndex = 0;
    DWORD ulOffset = 0;

    for(ulIndex = 0; ulIndex < usLen; ulIndex++)
    {
        ulOffset = ((DWORD)((DWORD)ulIndex << 8) | 0x0001);
        pucData[ulIndex] = ScalerUsbU2HostGetBufferField(usbufferAddr, ulOffset);
    }
}
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)

