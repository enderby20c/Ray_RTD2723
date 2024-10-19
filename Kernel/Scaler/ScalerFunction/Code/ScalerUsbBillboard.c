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
// ID Code      : ScalerUsbBillboard.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "UsbBillboard/ScalerUsbBillboard.h"

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_EIZO_CUSTOMIZED_BB_SUPPORT == _ON)
#warning "NOTE: TypeC and BB VID/PID are different , AE should check with PM"
#endif
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tBillboardUrl_DP[] =
{
#if (_USER_TYPE_C_BB_STRING_DP_SUPPORT == _ON)
#include _USER_TYPE_C_BB_STRING_DP
#else
    72, 3,
    'h',0,'t',0,'t',0,'p',0,
    ':',0,'/',0,'/',0,'h',0,
    'e',0,'l',0,'p',0,'.',0,
    'v',0,'e',0,'s',0,'a',0,
    '.',0,'o',0,'r',0,'g',0,
    '/',0,'d',0,'p',0,'-',0,
    'u',0,'s',0,'b',0,'-',0,
    't',0,'y',0,'p',0,'e',0,
    '-',0,'c',0,'/',0
#endif
};

BYTE code tBillboardUrl_Lenovo[] =
{
#if (_USER_TYPE_C_BB_STRING_LENOVO_SUPPORT == _ON)
#include _USER_TYPE_C_BB_STRING_LENOVO
#else
    50, 3,
    'h',0,'t',0,'t',0,'p',0,
    ':',0,'/',0,'/',0,'w',0,
    'w',0,'w',0,'.',0,'l',0,
    'e',0,'n',0,'o',0,'v',0,
    'o',0,'.',0,'c',0,'o',0,
    'm',0,'.',0,'c',0,'n',0
#endif
};

BYTE code tBillboardUrl_iAddtionalInfo[] =
{
#if (_USER_TYPE_C_BB_STRING_IADDTIONALINFO_SUPPORT == _ON)
#include _USER_TYPE_C_BB_STRING_IADDTIONALINFO
#else
    46, 3,
    'h',0,'t',0,'t',0,'p',0,
    ':',0,'/',0,'/',0,'w',0,
    'w',0,'w',0,'.',0,'r',0,
    'e',0,'a',0,'l',0,'t',0,
    'e',0,'k',0,'.',0,'c',0,
    'o',0,'m',0
#endif
};

BYTE code tUsbBillboardUsbDeviceDescriptor[_USB_DESC_SIZE_DEV] =
{
    _USB_DESC_SIZE_DEV,                                  // bLength
    _USB_DEVICE_DESCRIPTOR_TYPE,                         // bDescriptorType (Device Desc 0x01)
    0x01, 0x02,                                          // bcdUSB (LSB, MSB), USB3.0
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x00,                                                // bDeviceClass => Test For HID
#else
    0x11,                                                // bDeviceClass ( Billboard Class 0x11)
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x00,                                                // bDeviceSubClass
    0x00,                                                // bDeviceProtocol
    0x40,                                                // bMaxPacketSize0, 64 bytes
#if(_EIZO_CUSTOMIZED_BB_SUPPORT == _ON)
    _USB_EIZO_VENDOR_ID_L,                               // Vendor ID FOR EIZO
    _USB_EIZO_VENDOR_ID_H,
    _USB_EIZO_PRODUCT_ID_L,                              // PID FOR EIZO
    _USB_EIZO_PRODUCT_ID_H,
#else
    _USB_VENDOR_ID_L,                                    // Vendor ID
    _USB_VENDOR_ID_H,
    _USB_PRODUCT_ID_L,                                   // PID
    _USB_PRODUCT_ID_H,
#endif
    _USB_FW_SUB_VER_,                                    // bcdDevice
    _USB_FW_MAIN_VER_,
    _USB_BB_INDEX1,                                      // iManufacturer - idx of Manf Str Desc.
    _USB_BB_INDEX2,                                      // iProduct - idx of Prod String Descriptor
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x00,                                                // Test For HID
#else
    _USB_BB_INDEX3,                                      // iSerialNumber - Idx of Serial Num String
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x01                                                 // bNumConfigurations
};

BYTE code tUsbBillboardUsbConfigDescriptor[_USB_DESC_SIZE_CONF_TOTAL] =
{
    // --------- Configuration Descriptor Type ---------
    _USB_DESC_SIZE_CONF,                             // bLength
    _USB_CONFIGURATION_DESCRIPTOR_TYPE,              // bDescriptorType
    ((_USB_DESC_SIZE_CONF_TOTAL) % 256),
    ((_USB_DESC_SIZE_CONF_TOTAL) / 256),             // wTotalLength
    0x01,                                            // bNumInterfaces
    0x01,                                            // bConfigurationValue
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x00,                                            // Test For HID
#else
    _USB_BB_INDEX2,                                  // iConfiguration
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0xC0,                                            // bmAttributes,
    0x00,                                            // bMaxPower

    // --------- Interface Descriptor Type ------------
    _USB_DESC_SIZE_INTF,                             // bLength
    _USB_INTERFACE_DESCRIPTOR_TYPE,                  // bDescriptorType
    0x00,                                            // bInterfaceNumber
    0x00,                                            // bAlternateSetting
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x01,                                            // bNumEndpoints (the status change endpoint: interrupt endpoint)
    0x03,                                            // bInterfaceClass(HID == 0x03, USB_DEVICE_CLASS_HUMAN_INTERFACE)
#else
    0x00,                                            // bNumEndpoints (the status change endpoint: interrupt endpoint)
    0x11,                                            // bInterfaceClass(Hub Class == 0x09)
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x00,                                            // bInterfaceSubClass
    0x00,                                            // bInterfaceProtocol, single-TT
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    0x00,                                            // For HID
#else
    _USB_BB_INDEX2,                                  // ilInterface (Idx of this intf str desc.)
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
    // Add HID Description
    _USB_DESC_SIZE_HID,                              // bLength
    0x21,                                            // bDescriptorType (HID_DESCRIPTOR Descriptor Type)
    0x11,                                            // Identifying the HID Class Specification release(LSB)
    0x01,                                            // Identifying the HID Class Specification release(MSB)
    0x00,                                            // bCountryCode
    0x01,                                            // Number of class descriptors
    0x22,                                            // REPORT_DESCRIPTOR
    ((sizeof(StructHidReportDescriptor)) % 256),     // The total size of the Report descriptor(LSB)
    ((sizeof(StructHidReportDescriptor)) / 256),     // The total size of the Report descriptor(MSB)
    // Add End Point Description
    0x07,                                            // bLength
    0x05,                                            // bDescriptorType
    0x81,                                            // bEndpointAddress
    0x03,                                            // bmAttributes
    0x40,                                            // wMaxPacketSize_Lsb
    0x00,                                            // wMaxPacketSize_Msb
    0x10,                                            // bInterval
#endif
};

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
BYTE code tUsbBillboardHidReportDescriptor[(sizeof(StructHidReportDescriptor))] =
{
    0x06,0xDA,0xFF,                                                     // Usage Page (vender define)
    0x09,0xDA,                                                          // Usage
    0xA1,0x01,                                                          // Collection
    0x15,0x80,                                                          // Logical min
    0x25,0x7F,                                                          // Logical Max
    // Vendor CMD Output
    0x75,0x08,                                                          // Report size (bits)
    0x96,_USB_HID_REPORT_COUNT_LO_BYTE,_USB_HID_REPORT_COUNT_HI_BYTE,   // Report Count bSize: 0x10, bType: Global(0x01), bTag: Report Count
    0x09,0xD1,                                                          //
    0x91,0x02,                                                          //
    // Vendor CMD Input
    0x75,0x08,                                                          // Report size (bits)
    0x96,_USB_HID_REPORT_COUNT_LO_BYTE,_USB_HID_REPORT_COUNT_HI_BYTE,   // Report Count bSize: 0x10, bType: Global(0x01), bTag: Report Count
    0x09,0xD2,                                                          //
    0x81,0x02,                                                          //
    // HID collection end
    0xC0,
};

BYTE code tUsbBillboardHidBosDescriptor[(sizeof(StructHidBosDescriptor))] =
{
    // USB BOS Description
    0x05,           // ucLength
    0x0F,           // ucDescriptorType
    0x0C,           // ucSizeLsb
    0x00,           // ucSizeMsb
    0x01,           // ucNumDeviceCaps
    // USB DEVCAP USB2 EXTENSION DESCRIPTOR
    0x07,           // ucLength
    0x10,           // ucDescriptorType
    0x02,           // ucDescriptorCapType
    0x00,           // ucData0
    0x00,           // ucData1
    0x00,           // ucData3
    0x00,
};
#endif

BYTE code tUsbBillboardUsbStringDescriptor[_USB_DESC_SIZE_CPLS] =
{
    _USB_DESC_SIZE_CPLS,                                 // bLength
    _USB_STRING_DESCRIPTOR_TYPE,                         // bDescriptorType
    0x09, 0x04
};

BYTE code tUsbBillboardBOSDeviceCapabilityDescriptor[_USB_BB_BOS_DESC_FIRST_PART_LEN] =
{
    // ----------- BOS Descriptor Type ---------------
    _USB_DESC_SIZE_BOS,                                 // bLength
    _USB_BOS_DESCRIPTOR_TYPE,                           // bDescriptorType
    // lint -e572 :Excessive shift value (precision 7 shifted right by 8)
    (_USB_BB_BOS_DESC_TOTAL_LEN_INIT % 256),            // wTotalLength(LSB),need to be reconfirmed in FW
    (_USB_BB_BOS_DESC_TOTAL_LEN_INIT / 256),            // wTotalLength(MSB),need to be reconfirmed in FW
    // lint +e572 :Excessive shift value (precision 7 shifted right by 8)
    _USB_BOS_DEVICEACPS_NUM,                            // bNumDeviceCaps,need to be reconfirmed in FW(_USB_BOS_DEVICEACPS_NUM + x BBAltModeCaps)

    // ----- Device Capability Descriptor Type - USB2.0 Extension
    _USB_DESC_SIZE_USB2_EXTENSION,                      // bLength
    _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,             // bDescriptorType
    _USB_EXTENSION_TYPE,                                // bDevCapabilityType
#ifdef _WIN8P1_LPM_L1_
    0x1E, 0xF4, 0x00, 0x00,                             // bmAttributes, SS device shall support LPM (LSB~MSB)
#else
    0x00, 0x00, 0x00, 0x00,                             // bmAttributes, SS device shall support LPM (LSB~MSB)
#endif

#if(_USB_31_SS_SUPPORT == _ON)
    // ---- Device Capability Descriptor - SuperSpeed USB
    _USB_DESC_SIZE_SUPERSPEED_USB,                      // bLength
    _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,             // bDescriptorType
    _USB_SUPERSPEED_USB_TYPE,                           // bDevCapabilityType
    0x00,                                               // bmAttributes, Do not support LTM
    0x0E, 0x00,                                         // wSpeedsSupported, Support HS/FS, (LSB,MSB)
    0x01,                                               // bFunctionalitySupport, Lowest Speed of function is FS
    0x0A,                                               // bU1DevExitLat, Less than 10us for U1->U0
    0xFF, 0x03,                                         // wU2DevExitLat, less than 1024us for U2->U0, (LSB,MSB)
#endif

    // ---- Device ContainID descriptor
    _USB_DESC_SIZE_CONTAINER_ID,                        // bLength
    _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,             // bDescriptorType
    _USB_CONTAINER_ID_TYPE,                             // bDevCapabilityType
    0x00,
    0xAF, 0x4F, 0xAC, 0x0D,                             // ContainID
    0x00, 0x87, 0x40, 0xEE,                             // This is a 128-bit number that is unique to a device instance
    0xB7, 0x58, 0x26, 0xA1,                             // that is used to uniquely identify the device instance accross
    0x07, 0xD7, 0x6C, 0x6B,                             // all mode of operation.

    // ---- BillBoard Capability descriptor
    _USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_MAX_ALTERNATE_MODE_NUM,  // bLength,need to be reconfirmed in FW
    _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,             // bDescriptorType
    _USB_BILLBOARD_TYPE,                                // bDevCapabilityType
    _TYPE_C_BILLBOARD_URL_INDEX_IADDTIONALINFO,         // iAdditionalInfoURL (TBD)
    _USB_MAX_ALTERNATE_MODE_NUM,                        // bNumberOfAlternateModes
    0x00,                                               // bPreferredAlternateModes
    0x00,                                               // bVconnPower(LSB) bit 0~2: Vconn Power  000b=1W, 001b=1.5W, 010b=2W, 011b=3W
    // 100b=4W, 101b=5W, 110b=6W, 111b=reserved
    0x00,
    0x03,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,                 // bmConfigured
                                                        // total 32 byte(256 bit) for 128 altenate modes(spec 0x34)
                                                        // 00b:Unspecified Error, 01b:Alternate Mode configuration
                                                        // 10b:Alternate Mode configuration attempted but unsuccessful
                                                        // 11b:Alternate Mode configuration successful
    0x21, 0x01,                                         // bcdVersion
    0x00,                                               // bAdditonalFailureInfo
    0x00                                                // bReserved

    // Concatenate USB_DEVCAP_BILLBOARD_CAP_DESCRIPTOR_ALTERNATE_MODE in FW
};

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructUsbBBAltModeCapabilityDescriptor code g_stUsbBillboardAltModeCapabilityDescriptor =
{
    _USB_DESC_SIZE_BILLBOARD_ALTMODE_CAP,                // bLength
    _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,              // bDescriptorType
    _USB_BILLBOARD_ALTMODE_TYPE,                         // bDevCapabilityType
    0x00,                                                // need to be reconfirmed in FW, refer g_pstUsbBillboardAltModeInfo ucStringIndex
    {
        0x00,0x00,0x00,0x00                              // need to be reconfirmed in FW, refer g_pstUsbBillboardAltModeInfo ucdwAlternateModeVdo_Byte0-4
    }
};

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tManufacturer[] =
{
    // MID = 1111 "Generic"
    16,  3, 'G', 0, 'e',  0, 'n', 0,
    'e', 0, 'r', 0, 'i',  0, 'c', 0
};

BYTE code tProduct[] =
{
    28,  3, 'U', 0, 'S',  0, 'B', 0,
    '-', 0, 'C', 0, ' ',  0, 'A', 0,
    'D', 0, 'A', 0, 'P',  0, 'T', 0,
    'O', 0, 'R', 0
};

BYTE code tSerialNumber[] =
{
    36, 3, '2', 0, '0', 0, '0', 0, '9', 0,
    '0', 0, '7', 0, '0', 0, '3', 0, '8', 0,
    '1', 0, '9', 0, '9', 0, '0', 0, '0', 0,
    '0', 0, '0', 0, '0', 0
};

BYTE code tUsbBillboardManufacturer_Custom[_IMANUFACTUR_SIZE] = {0};

BYTE code tUsbBillboardManufacturer[] =
{
#if (_USER_TYPE_C_BB_STRING_MANFAC_SUPPORT == _ON)
#include _USER_TYPE_C_BB_STRING_MANFAC
#else
    // MID = 1111 "Generic"
    16,  3, 'R', 0, 'e',  0, 'a', 0,
    'l', 0, 't', 0, 'e',  0, 'k', 0
#endif
};

BYTE code tUsbBillboardProduct_Custom[_IPRODUCT_SIZE] = {0};

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
BYTE code tUsbBillboardProduct[] =
{
    16,  3, 'H', 0, 'i',  0, 'd', 0,
    ' ', 0, 'M', 0, 'M',  0, '1', 0
};
#else
BYTE code tUsbBillboardProduct[] =
{
    34,  3, 'B', 0, 'i',  0, 'l', 0,
    'l', 0, 'B', 0, 'o',  0, 'a', 0,
    'r', 0, 'd', 0, ' ',  0, 'D', 0,
    'e', 0, 'v', 0, 'i',  0, 'c', 0,
    'e', 0
};
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

BYTE code tBBSerialNumber[] =
{
    36, 3, '0', 0, '0', 0, '0', 0, '0', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '0', 0,
    '0', 0, '0', 0, '0', 0, '0', 0, '0', 0,
    '0', 0, '0', 0, '0', 0
};

BYTE code tRTString[] =
{
    0x0E, 0x03, 'R', 0x00, 'T', 0x00, ' ', 0x00,
    'H',  0x00, 'u', 0x00, 'b', 0x00
};

BYTE code tBBDeviceQualifier[] =
{
    0x0A,   // bLength
    0x06,   // bDescriptorType
    0x10,   // bcdUSB (LSB)
    0x02,   // bcdUSB (MSB)
    0x11,   // bDeviceClass
    0x00,   // bDeviceSubClass
    0x00,   // bDeviceProtocol
    0x40,   // bMaxPacketSixe0
    0x01,   // bNumberConfigurations
    0x00    // bReserved
};

BYTE g_pucUsbBillboardRTHandshake[] =
{
    0xA, 'R', 'E', 'A', 'L', 'T', 'E',
    'K',  'L', 'C', 'D'
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
EnumUsbBillboardMacMuxSwitch g_enumUsbBillboardMacMuxSwitch = _U2_PHY_PORT_TO_BB;
#endif

BYTE g_ucUsbBillboardUsbHostEnableRemoteWakeup;
BYTE g_ucUsbBillboardUsbConfigurationValue;
BYTE g_ucUsbBillboardUsbVendorComEnb;

bit g_bUsbBillboardLoadCustomManufactory = _FALSE;
bit g_bUsbBillboardLoadCustomProduct = _FALSE;
bit g_bUsbBillboardInitial = _FALSE;
bit g_bUsbBillboardIspEn = _FALSE;
//bit g_bBBDebugMessageEven;
//WORD g_usBBFilterPro;
//bit g_bBBDebugMessageStart;
BYTE g_ucUsbBillboardMuxSelPort = _NO_TYPE_C_PORT;

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
BYTE g_pucUsbBillboardGetISPinfo[16];
bit g_bUsbBillboardIspInfoReadyFlag = _FALSE;
bit g_bUsbBillboardProgramUserEnableFlag = _FALSE;
bit g_bUsbBillboardIspProcessing = _FALSE;
bit g_bUsbBillboardIspProcessingDone = _FALSE;
bit g_bUsbBillboardIspProcessingUpdate = _FALSE;
StructUsbBillboardCustomCommandInfo g_stUsbBillboardCustomCommandInfo = {0, 0, 0, 0, 0, 0};
EnumBillboardCustomEvent g_enumUsbBillboardCustomEventChange = _BB_CUSTOM_EVENT_NONE;

StructUsbBillboardIspCommandInfo g_stUsbBillboardIspCommandInfo;
// USB TypeC BB Background Progrma Support
// Background Program Flag
WORD g_usUsbBillboardBackgroundProgramPauseTime;
WORD g_usUsbBillboardBackgroundProgramExcuteTime;
bit g_bUsbBillboardBackgroundProgramReleaseFlag = _FALSE;
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)

StructTypeCBillboardInfo g_pstUsbBillboardAltModeInfo[_USB_MAX_ALTERNATE_MODE_NUM];

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
BYTE g_pucUsbBillboardHidReport[_USB_HID_REPORT_COUNT_LENGTH];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Bill Board Device Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardHandler(void)
{
    // Judge USB Setup Packet Received or not
    if(ScalerGetBit(P98_00_HS_EP0_IRQ, _BIT0) == _BIT0)
    {
        // Clear Buf0 for EP0 RX/TX Enable
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT3 | _BIT2), 0x00);

        // Clear USB Setup Packet Received Flag
        ScalerSetBit(P98_00_HS_EP0_IRQ, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        DebugMessageBB("U2 Req Type", ScalerGetByte(P98_08_HS_EP0_SETUP0));

        switch(ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_TYPE_MASK)
        {
            case _USB_STANDARD_REQUEST:
                ScalerUsbBillboardStandardRequest();
                break;

            case _USB_VENDOR_REQUEST:
                ScalerUsbBillboardVendorRequest();
                break;

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
            case _USB_CLASS_REQUEST:

                // Test For HID SetReport:0x21, GetReport:0xA1
                switch(ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_CLASS_DESCRIPTOR_TYPE_MASK)
                {
                    case _USB_CLASS_DESCRIPTOR_TYPE_HID:

                        ScalerUsbBillboardHidClassRequest();

                        break;

                    default:

                        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
                        break;
                }

                break;
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

            default:
                ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
                break;
        }
    }

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
    // BB Reply Info to Tool (Info From UserCommonDualBankHandler)
    if(GET_USB_BB_ISP_READY_FLAG() == _TRUE)
    {
        if(GET_USB_BB_ISP_OPCODE() == _USB_VENDOR_DUAL_BANK_PROCESS)
        {
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
            ScalerUsbBillboardHidVendorDualBankProcess2();
#else
            ScalerUsbBillboardVendorDualBankProcess2();
#endif
        }
        else
        {
            DebugMessageBB("Command error", GET_USB_BB_ISP_OPCODE());
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Bill Board ISR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardIntHandler_EXINT0(void)
{
    volatile BYTE data ucHS_EP0_IRQ = (ScalerGetByte_EXINT(P98_00_HS_EP0_IRQ) & ScalerGetByte_EXINT(P98_01_HS_EP0_IRQ_EN));

    if(ucHS_EP0_IRQ & _HS_EP0_SETUP_PKT_RECEIVE_INT)
    {
        // empty
    }
}

//--------------------------------------------------
// Description  : Standard Request handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardStandardRequest(void)
{
    DebugMessageBB("U2 Std Request", ScalerGetByte(P98_09_HS_EP0_SETUP1));
    DebugMessageBB("U2 Std wVALL", ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    DebugMessageBB("U2 Std wVALH", ScalerGetByte(P98_0B_HS_EP0_SETUP3));
    DebugMessageBB("U2 Std wIDXL", ScalerGetByte(P98_0C_HS_EP0_SETUP4));
    DebugMessageBB("U2 Std wIDXH", ScalerGetByte(P98_0D_HS_EP0_SETUP5));
    DebugMessageBB("U2 Std wLENL", ScalerGetByte(P98_0E_HS_EP0_SETUP6));
    DebugMessageBB("U2 Std wLENH", ScalerGetByte(P98_0F_HS_EP0_SETUP7));

    switch(ScalerGetByte(P98_09_HS_EP0_SETUP1))
    {
        case _USB_REQUEST_GET_DESCRIPTOR:
            ScalerUsbBillboardGetDescriptor();
            break;

        case _USB_REQUEST_SET_ADDRESS:
            ScalerUsbBillboardSetAddr();
            break;

        case _USB_REQUEST_SET_CONFIGURATION:
            ScalerUsbBillboardSetConf();
            break;

        case _USB_REQUEST_GET_INTERFACE:
            // Undefined request for hubs
            // Hubs are allowed to support only one interface.
            ScalerUsbBillboardGetInterface();

            break;

        case _USB_REQUEST_SET_INTERFACE:
            // Undefined request for hubs
            // Hubs are allowed to support only one interface.
            ScalerUsbBillboardSetInterface();

            break;

        case _USB_REQUEST_GET_STATUS:
            ScalerUsbBillboardGetStatus();
            break;

        case _USB_REQUEST_GET_CONFIGURATION:
            ScalerUsbBillboardGetConf();
            break;

        case _USB_REQUEST_SET_FEATURE:
            ScalerUsbBillboardSetFeature();
            break;

        case _USB_REQUEST_CLEAR_FEATURE:
            ScalerUsbBillboardClearFeature();
            break;    // end of USB_REQUEST_CLEAR_FEATURE

        case _USB_REQUEST_SYNC_FRAME:
            // Undefined request for hubs
            // Hubs are not allowed to have isochronous endpoints,
            // thus this request should return STALL
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;

        case _USB_REQUEST_SET_DESCRIPTOR:
            // Optional requests that are not implemented shall return
            // STALL in the Data stage or Status stage of the request.
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//-------------------------------------------------------
// Description  : USB Vendor Request - Set Register Byte
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerUsbBillboardVendorSetRegisterByte(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;
    WORD usRegisterAdd = 0x0000;
    // BYTE xdata *pucFlashData = 0x0000;
    WORD usFlag = 0x0000;
    BYTE ucPageIdx = 0;
    WORD usPageNum = 0;
    WORD usRemainNum = 0;

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    usRegisterAdd = (ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    usFlag = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);
    usPageNum = usLength / _USB_EP0_DATA_BUF_SIZE;
    usRemainNum = usLength % _USB_EP0_DATA_BUF_SIZE;

    // temp buffer for U2 RX test
    for(ucPageIdx = 0; ucPageIdx < usPageNum; ucPageIdx++)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
            {
                if((usFlag & _BIT0) == _BIT0)
                {
                    // pucFlashData[usRegisterAdd++] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                    ScalerSetByte(usRegisterAdd++, ScalerGetByte(P9A_03_BB_BUF0_RD_DATA));
                }
                else
                {
                    // pucFlashData[usRegisterAdd] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                    ScalerSetByte(usRegisterAdd, ScalerGetByte(P9A_03_BB_BUF0_RD_DATA));
                }
            }
            // [TBD]: Write flash...
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }

    // [TBD]: Read the remaining
    if(usRemainNum != 0)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            for(ucIdx = 0; ucIdx < usRemainNum; ucIdx++)
            {
                if((usFlag & _BIT0) == _BIT0)
                {
                    // pucFlashData[usRegisterAdd++] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                    ScalerSetByte(usRegisterAdd++, ScalerGetByte(P9A_03_BB_BUF0_RD_DATA));
                }
                else
                {
                    // pucFlashData[usRegisterAdd] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                    ScalerSetByte(usRegisterAdd, ScalerGetByte(P9A_03_BB_BUF0_RD_DATA));
                }
            }
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }
    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, _FALSE);
}

//-------------------------------------------------------
// Description  : USB Vendor Request - Get Register Byte
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerUsbBillboardVendorGetRegisterByte(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;
    WORD usRegisterAdd = 0x0000;
    WORD usFlag = 0x0000;
    BYTE ucPageIdx = 0;
    WORD usPageNum = 0;
    WORD usRemainNum = 0;

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    usRegisterAdd = (ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    usFlag = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);
    usPageNum = usLength / _USB_EP0_DATA_BUF_SIZE;
    usRemainNum = usLength % _USB_EP0_DATA_BUF_SIZE;

    // [TBD]: limit to one Byte set atm.
    // if(usLength > 1)
    // usLength = 1;
    for(ucPageIdx = 0; ucPageIdx < usPageNum; ucPageIdx++)
    {
        // [TBD]:Read data from flash...
        // Set write fifo to transmit data to host
        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
        {
            if((usFlag & _BIT0) == _BIT0)
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte(usRegisterAdd++));
            }
            else
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte(usRegisterAdd));
            }
        }
        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
    }

    if(usRemainNum == 0)
    {
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
    }
    else
    {
        // [TBD]:Read remaining data from flash...

        // Set write fifo to transmit data to host
        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        for(ucIdx = 0; ucIdx < usRemainNum; ucIdx++)
        {
            if((usFlag & _BIT0) == _BIT0)
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte(usRegisterAdd++));
            }
            else
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte(usRegisterAdd));
            }
        }

        ScalerSetByte(P98_06_HS_EP0_TX_BC, usRemainNum);
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
    }
    DebugMessageBB("U2 Check Get Add", usRegisterAdd);
    DebugMessageBB("U2 Check Get Value", ScalerGetByte(usRegisterAdd));
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Read Flash (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorReadFlash(void)
{
    WORD usLength = 0;
    WORD usBankID = 0;
    WORD usAddr = 0;

    BYTE pucUsbBillboardVendorDataBuf[_USB_VENDOR_CMD_MAX_LEN] = {0};
    // temp buffer for U2 TX test

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    usBankID = (ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    usAddr = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    ScalerFlashRead(usBankID, (BYTE *)(DWORD)usAddr, usLength, pucUsbBillboardVendorDataBuf);
    ScalerUsbBillboardTransmtDataToHost(usLength, pucUsbBillboardVendorDataBuf);
}

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//----------------------------------------------------------------
// Description  : USB Vendor Request - Write Flash (Host->Deivce)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardVendorWriteFlash(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;
    WORD usRemainIdx = 0;
    BYTE ucPageIdx = 0;
    WORD usPageNum = 0;
    WORD usRemainNum = 0;
    WORD usBankID = 0;
    WORD usAddr = 0;

    // temp buffer for U2 RX test
    WORD usPageTmp = 0;

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    usPageNum = usLength / _USB_EP0_DATA_BUF_SIZE;
    usRemainNum = usLength % _USB_EP0_DATA_BUF_SIZE;
    usBankID = (ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    usAddr = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    DebugMessageBB("U2-WT-usLength", usLength);
    DebugMessageBB("U2-WT-usPageNum", usPageNum);
    DebugMessageBB("U2-WT-usRemainNum", usRemainNum);


    // [TBD]: Read the complete 64Byte
    for(ucPageIdx = 0; ucPageIdx < usPageNum; ucPageIdx++)
    {
        usPageTmp = ucPageIdx * _USB_EP0_DATA_BUF_SIZE;
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
            {
                *((volatile BYTE *)(_HW_XRAM_ISP_MAPPING_ADDR_START + (ucIdx + usPageTmp))) = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
            }
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }

    // [TBD]: Read the remaining
    if(usRemainNum != 0)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            usRemainIdx = usPageNum * _USB_EP0_DATA_BUF_SIZE;
            for(ucIdx = 0; ucIdx < usRemainNum; ucIdx++)
            {
                *((volatile BYTE *)(_HW_XRAM_ISP_MAPPING_ADDR_START + usRemainIdx)) = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                usRemainIdx++;
            }
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }
    ScalerFlashWritePageProgram(usBankID, usAddr, usLength, _FALSE, _FALSE);

    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, _FALSE);
}
#endif

//-----------------------------------------------------------------
// Description  : USBVendor Request - Flash sector erase (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorSectorErase(void)
{
    WORD usBankID = 0;
    BYTE ucSectorID = 0;

    usBankID = ((ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    ucSectorID = ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    ScalerFlashErasePage(usBankID, ucSectorID, _FALSE, _FALSE);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT0), (_BIT0));
}
#endif

//-----------------------------------------------------------------
// Description  : USBVendor Request - Flash sector erase (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorBankErase(void)
{
/*
    WORD usBankID = 0;
    usBankID = ScalerGetByte(P98_0A_HS_EP0_SETUP2);

    ScalerFlashEraseBank(usBankID, _FALSE, _FALSE);
*/
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT0), (_BIT0));
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Isp Enable (Host -> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorIspEnable(void)
{
    g_bUsbBillboardIspEn = (ScalerGetByte(P98_0A_HS_EP0_SETUP2) & _BIT0);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
    // Reset Background Flag While Disable ISP_Enable
    if(g_bUsbBillboardIspEn == _FALSE)
    {
        // Reset the flag for the release of BB_ISP_WhileLoop
        g_bUsbBillboardBackgroundProgramReleaseFlag = _FALSE;

        // Reset the BB Processing flag for Release Force Power Normal
        g_bUsbBillboardIspProcessing = _FALSE;
    }
    else
    {
        // Set Flag for Force Power Normal while BB ISP
        g_bUsbBillboardIspProcessing = _TRUE;
    }
#endif
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT0), (_BIT0));
}

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : BillBoard Set User Control BB_Eanble by BB_Program
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsbBillboardSetBBProgramEnable(void)
{
    SET_USB_BB_USER_ENABLE_FLAG();
}

//--------------------------------------------------
// Description  : BillBoard CLean User Control BB_Eanble by BB_Program
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsbBillboardClrBBProgramEnable(void)
{
    CLR_USB_BB_USER_ENABLE_FLAG();
}

//-----------------------------------------------------------------
// Description  : USBVendor Request - Dual Bank Process1 (record steup token packet info)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDualBankProcess1(void)
{
    // Will Be Cleared By UserCommonDualBankUserHandler
    SET_USB_BB_ISP_REV_CMD_STATUS();
    // Will Be Cleared By When Complete a Transfer
    SET_USB_BB_ISP_OPCODE(_USB_VENDOR_DUAL_BANK_PROCESS);

    // Means That Isp Info from UserCommondualBankHandler has not been update During a Given Command
    if(GET_USB_BB_ISP_READY_FLAG() == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
    }

    switch(ScalerGetByte(P98_0A_HS_EP0_SETUP2))
    {
        case _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE);
            break;

        case  _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE);
            break;

        case _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE);
            break;

        case _SCALER_BOOT_SWITCH_CODE_OP_CODE:
            ScalerUsbBillboardVendorSwitchCode();
            break;

        // Set Background Function : Program Flash Write Time Setting
        case _SCALER_BOOT_GET_ISP_BACKGROUND_WRITE_TIME_OP_CODE:
            ScalerUsbBillboardVendorSetBackgroundWriteTime();

            // Set BB Background Puase Timer No Need to Excute UserCommonDualBankUserHandler
            // Clear all the related MACRO
            CLR_USB_BB_ISP_REV_CMD_STATUS();
            CLR_USB_BB_ISP_OPCODE();
            CLR_USB_BB_ISP_SUB_OPCODE();
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//-----------------------------------------------------------------
// Description  : USBVendor Request - Dual Bank Process2 (reply isp info to host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDualBankProcess2(void)
{
    switch(ScalerGetByte(P98_0A_HS_EP0_SETUP2))
    {
        case _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE:
            ScalerUsbBillboardVendorGetIspStartBank();
            break;

        case _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE:
            ScalerUsbBillboardVendorGetIspKeyAddr();
            break;

        case  _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE:
            ScalerUsbBillboardVendorGetIspFalgAddr();
            break;

        case _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE:
            ScalerUsbBillboardVendorGetIspSignatureAddr();
            break;

        case _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE:
            ScalerUsbBillboardVendorGetVerifyCopyResult();
            break;

        case _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE:
            ScalerUsbBillboardVendorGetCurrentKeyAddr();
            break;

        case _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE:
            ScalerUsbBillboardVendorGetFWInfo();
            break;

        case _SCALER_BOOT_SWITCH_CODE_OP_CODE:
            ScalerUsbBillboardVendorSwitchCode();
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}
//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x01 GetIspStartBank (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetIspStartBank(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x02 GetIspKeyAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetIspKeyAddr(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);


    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x03 GetIspFalgAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetIspFalgAddr(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x04 GetIspSignatureAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetIspSignatureAddr(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x05 GetVerifyCopyResult (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetVerifyCopyResult(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x06 GetCurrentKeyAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetCurrentKeyAddr(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);


    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x07 GetFWInfo (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorGetFWInfo(void)
{
    BYTE ucLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    ucLength = ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, ucLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - BootCode Use Only. Dual Bank Process:0x08 SwitchCOde (Host -> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorSwitchCode(void)
{
    if(GET_USB_BB_ISP_READY_FLAG() == _FALSE)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0) == _TRUE)
        {
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_SWITCH_CODE_OP_CODE);
        }
        else
        {
            DebugMessageBB("Complete Command FAIL", GET_USB_BB_ISP_SUB_OPCODE());
        }
    }
    else
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
}

//-----------------------------------------------------------------
// Description  : USB Vendor Request - Dual Bank Process:0x0C Set Background Flash Write Time (Host -> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorSetBackgroundWriteTime(void)
{
    // Set BB Background Puase Timer By Fetching Control_XFer_Byte[4][5]
    g_usUsbBillboardBackgroundProgramPauseTime = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    // Reset Billboard Background Program Excuting Counter
    g_usUsbBillboardBackgroundProgramExcuteTime = 0;

    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0) == _TRUE)
    {
        SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_BACKGROUND_WRITE_TIME_OP_CODE);
    }
    else
    {
        DebugMessageBB("Complete Command FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//----------------------------------------------------------------
// Description  : USB Vendor Request - Check Backgound Program Status
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardVendorCheckBackgroundProgram(void)
{
    //----------------------------------------------------------------
    // g_usUsbBillboardBackgroundProgramPauseTime == 0x00 Means BB ISP Only
    // g_usUsbBillboardBackgroundProgramPauseTime != 0x00 Means BB Background Support ON
    //----------------------------------------------------------------
    // If supporting BB ISP Background Program,
    // the Programming while Loop will release the While Loop after executing g_usUsbBillboardBackgroundProgramPauseTime times,
    // allowing the Main Loop to run once
    if(g_usUsbBillboardBackgroundProgramPauseTime != 0x00)
    {
        // Restart BB ISP While Loop again, after get _USB_VENDOR_WRITE_TO_FLASH again.
        if((g_bUsbBillboardIspEn == _FALSE) && (g_bUsbBillboardBackgroundProgramReleaseFlag == _TRUE))
        {
            // Restarting BB_ISP_WhileLoop.
            g_bUsbBillboardIspEn = _TRUE;

            // Reset the flag for the release of BB_ISP_WhileLoop
            g_bUsbBillboardBackgroundProgramReleaseFlag = _FALSE;

            DebugMessageBB("BB Program Set While Loop Enable", g_bUsbBillboardIspEn);
        }

        // BB ISP executes 256 Bytes costing 2ms.
        // The total execution loop time is equal to 2ms multiplied by g_usUsbBillboardBackgroundProgramPauseTime.
        if((g_bUsbBillboardIspEn == _TRUE) && (g_bUsbBillboardBackgroundProgramReleaseFlag == _FALSE))
        {
            if(g_usUsbBillboardBackgroundProgramExcuteTime != g_usUsbBillboardBackgroundProgramPauseTime)
            {
                // Accumulating Billboard Background Program Counter.
                g_usUsbBillboardBackgroundProgramExcuteTime ++;

                DebugMessageBB("BB Program Time #", g_usUsbBillboardBackgroundProgramExcuteTime);
            }
            else
            {
                // Reset Billboard Background Program Excuting Counter
                g_usUsbBillboardBackgroundProgramExcuteTime = 0;

                // Release BB_ISP_WhileLoop to Process MainLoop 1 Time
                g_bUsbBillboardIspEn = _FALSE;

                // Setting the flag for the release of BB_ISP_WhileLoop
                g_bUsbBillboardBackgroundProgramReleaseFlag = _TRUE;

                DebugMessageBB("BB Program Release to Main Loop", g_bUsbBillboardBackgroundProgramReleaseFlag);
            }
        }
    }
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Customer BB Set Command (Host -> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardCustomSetCommand(void)
{
    // Check None of Custom Event is Busy
    if((GET_USB_BB_CUSTOM_EVENT_CHANGE() & _BB_CUSTOM_EVENT_00) != _BB_CUSTOM_EVENT_00)
    {
        // Set BB Rcv. Command into pststUsbBillboardCustomCommandInfo
        g_stUsbBillboardCustomCommandInfo.ucwValue_Low = ScalerGetByte(P98_0A_HS_EP0_SETUP2);
        g_stUsbBillboardCustomCommandInfo.ucwValue_High = ScalerGetByte(P98_0B_HS_EP0_SETUP3);
        g_stUsbBillboardCustomCommandInfo.ucwIndex_Low = ScalerGetByte(P98_0C_HS_EP0_SETUP4);
        g_stUsbBillboardCustomCommandInfo.ucwIndex_High = ScalerGetByte(P98_0D_HS_EP0_SETUP5);
        g_stUsbBillboardCustomCommandInfo.ucwLength_Low = ScalerGetByte(P98_0E_HS_EP0_SETUP6);
        g_stUsbBillboardCustomCommandInfo.ucwLength_High = ScalerGetByte(P98_0F_HS_EP0_SETUP7);

        // Set Change Flag In  Custom Event_00
        SET_USB_BB_CUSTOM_EVENT_CHANGE(_BB_CUSTOM_EVENT_00);

        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT0, (_BIT0));
    }
    else
    {
        // Set Change Flag In  Custom Event Error
        // Custom Event Handling Conflict
        SET_USB_BB_CUSTOM_EVENT_CHANGE(_BB_CUSTOM_EVENT_ERROR);

        DebugMessageBB("BB : Custom Event Error", (GET_USB_BB_CUSTOM_EVENT_CHANGE()));

        // Set BB STALL
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT1, _BIT1);
    }
}

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
//-----------------------------------------------------------------
// Description  : USB BB Get ISP/DualBank Related Info (Host -> Device)
// Input Value  : Soure Info,Info Length,ReadyFlag
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardCopyISPInfo(BYTE *pucSrcAddr, BYTE ucLength, BYTE ucReadyFlag)
{
    // pulSrcAddr data(from UserCommonDualBankUserHandler) copy to g_pucUsbBillboardGetISPinfo
    memcpy(g_pucUsbBillboardGetISPinfo, pucSrcAddr, (WORD)ucLength);

    SET_USB_BB_ISP_READY_FLAG(ucReadyFlag);
}
#endif
//--------------------------------------------------
// Description  : Bill Board ISP FLAG INITIAL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardIspFlagInitial(void)
{
    CLR_USB_BB_ISP_REV_CMD_STATUS();
    CLR_USB_BB_ISP_READY_FLAG();
    CLR_USB_BB_ISP_OPCODE();
    CLR_USB_BB_ISP_SUB_OPCODE();
    memset(g_pucUsbBillboardGetISPinfo, 0x00, sizeof(g_pucUsbBillboardGetISPinfo));

    // Reset BB ISP Processing Flag
    g_bUsbBillboardIspProcessing = _FALSE;
    g_bUsbBillboardIspProcessingDone = _FALSE;
    g_bUsbBillboardIspProcessingUpdate = _FALSE;

    // Reset BB Background Puase Timer
    g_usUsbBillboardBackgroundProgramPauseTime = 0;

    // Reset Billboard Background Program Excuting Counter
    g_usUsbBillboardBackgroundProgramExcuteTime = 0;

    // Reset the flag for the release of BB_ISP_WhileLoop
    g_bUsbBillboardBackgroundProgramReleaseFlag = _FALSE;

    // Reset the Custom Command Change Flag
    g_enumUsbBillboardCustomEventChange = _BB_CUSTOM_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Billboard Program Check Force Power Done or not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardProgramCheckDone(void)
{
    // Check if the BB ISP Processing Status has been changed in BB_Program.
    if(g_bUsbBillboardIspProcessingUpdate != g_bUsbBillboardIspProcessing)
    {
        // Verify that the Processing Status in BB_Program has been completed.
        if(g_bUsbBillboardIspProcessing == _FALSE)
        {
            g_bUsbBillboardIspProcessingDone = _TRUE;
        }
    }
    else
    {
        // Reset BB_Program Processing Done Flag
        g_bUsbBillboardIspProcessingDone = _FALSE;
    }

    // Update BB_Program Processing Status
    g_bUsbBillboardIspProcessingUpdate = g_bUsbBillboardIspProcessing;
}
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//----------------------------------------------------------------
// Description  : USB Vendor Request - Calculate HW CRC Result
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardVendorCalculateCrc(void)
{
    DWORD ulStartBank = (((DWORD)ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    DWORD ulBankCnt = (((DWORD)ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4));
    BYTE ucCRC = 0;
    DWORD ulStartAddr = (ulStartBank << 16);
    DWORD ulEndAddr = ulStartAddr + ulBankCnt * 65536 - 1;

    DebugMessageBB("ulStartBank", ulStartBank);
    DebugMessageBB("ulBankCnt", ulBankCnt);
    DebugMessageBB("ulStartAddr", ulStartAddr);
    DebugMessageBB("ulEndAddr", ulEndAddr);

    if(ScalerMcuFlashCRCCal(ulStartAddr, ulEndAddr, &ucCRC) == _TRUE)
    {
        DebugMessageBB("ucCRC", ucCRC);

        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucCRC);
        ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x01);
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    }
    else
    {
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//-----------------------------------------------------------------
// Description  : USBVendor Request - Handshake (Host <-> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorHandshake(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    if(usLength != g_pucUsbBillboardRTHandshake[0])
    {
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
        return;
    }
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    for(ucIdx = 0; ucIdx < g_pucUsbBillboardRTHandshake[0]; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardRTHandshake[ucIdx + 1]);
    }
    ScalerSetByte(P98_06_HS_EP0_TX_BC, g_pucUsbBillboardRTHandshake[0]);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Debug Msg
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDebugMsgEventStart(void)
{
// TBD for BB Debug.
/*
    g_bBBDebugMessageEven = _TRUE;
    g_usBBFilterPro = (ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    ScalerSetByte(0x00007, ScalerGetByte(P98_0B_HS_EP0_SETUP3));
    ScalerSetByte(0x00008, ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0xF1);
    ScalerSetByte(P98_06_HS_EP0_TX_BC, 1);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
*/
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Debug Msg
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDebugMsgEventFinish(void)
{
// TBD for BB Debug.
/*
    g_bBBDebugMessageEven = _FALSE;
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0xF5);
    ScalerSetByte(P98_06_HS_EP0_TX_BC, 1);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
*/
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Debug Msg
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDebugMsgStart(void)
{
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P98_06_HS_EP0_TX_BC, 2);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}

//-----------------------------------------------------------------
// Description  : USBVendor Request - Debug Msg
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDebugMsgEnd(void)
{
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P98_06_HS_EP0_TX_BC, 1);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}

//-----------------------------------------------------------------
// Description  : USBVendor Request - Debug Msg
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDebugMsgGetValue(void)
{
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P98_06_HS_EP0_TX_BC, 2);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Debug Msg
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorDebugMsgGetString(void)
{
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
    ScalerSetByte(P98_06_HS_EP0_TX_BC, 2);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Eeprom Write
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardEepromWrite(bit bSysDefualtIICPin, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    ucSubAddrLength = ucSubAddrLength;

#if(_PCB_SYS_EEPROM_IIC == _NO_IIC_PIN)
    ucSlaveAddr = ucSlaveAddr;
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;
#endif

    // Disable EEPROM Write Protect
    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

    if(!bSysDefualtIICPin)
    {
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

        SET_SW_IIC_STATUS(_IIC_SYS_EEPROM);

#if(_EEPROM_TYPE == _EEPROM_24LC16)
        ScalerMcuIICWrite(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
        ScalerMcuIICWrite(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray);
#endif

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)  // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Write(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _VGA_I2C);
// #else
        ScalerMcuHwIICWrite(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _PCB_SYS_EEPROM_IIC);
// #endif
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Write(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray _VGA_I2C);
// #else
        ScalerMcuHwIICWrite(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray, _PCB_SYS_EEPROM_IIC);
// #endif
#endif
#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
    }
    else
    {
#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))

#if(_EEPROM_TYPE == _EEPROM_24LC16)
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Write(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _VGA_I2C);
// #else
        ScalerMcuHwIICWrite(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _NO_IIC_PIN);
// #endif
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Write(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray, _VGA_I2C);
// #else
        ScalerMcuHwIICWrite(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray, _NO_IIC_PIN);
// #endif
#endif

#endif // End of #if(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO)

    }

    // Enable EEPROM Write Protect
    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Eeprom Read
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardEepromRead(bit bSysDefualtIICPin, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    ucSubAddrLength = ucSubAddrLength;

#if(_PCB_SYS_EEPROM_IIC == _NO_IIC_PIN)
    ucSlaveAddr = ucSlaveAddr;
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;
#endif

    if(bSysDefualtIICPin)
    {
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

        SET_SW_IIC_STATUS(_IIC_SYS_EEPROM);

#if(_EEPROM_TYPE == _EEPROM_24LC16)
        ScalerMcuIICRead(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
        ScalerMcuIICRead(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray);
#endif

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)  // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Read(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _VGA_I2C);
// #else
        ScalerMcuHwIICRead(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _PCB_SYS_EEPROM_IIC);
// #endif
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Read(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray _VGA_I2C);
// #else
        ScalerMcuHwIICRead(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray, _PCB_SYS_EEPROM_IIC);
// #endif
#endif
#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
    }
    else
    {
#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))

#if(_EEPROM_TYPE == _EEPROM_24LC16)
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Read(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _VGA_I2C);
// #else
        ScalerMcuHwIICRead(ucSlaveAddr, 1, usSubAddr, usLength, pucWriteArray, _NO_IIC_PIN);
// #endif
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
// #if(_HW_TRANSLATOR_IIC_SUPPORT == _ON)
        // ScalerMcuHwIIC0Read(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray, _VGA_I2C);
// #else
        ScalerMcuHwIICRead(ucSlaveAddr, 2, usSubAddr, usLength, pucWriteArray, _NO_IIC_PIN);
// #endif
#endif

#endif // End of #if(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO)
    }
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Write Sys Eeprom
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorWriteSyseeprom(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;
    BYTE ucPageIdx = 0;
    WORD usPageNum = 0;
    WORD usRemainNum = 0;
    BYTE ucSlaveAddr = 0;
    bit bOterIICPin = 0;
    BYTE ucSubAddeLen = 0;
    WORD usSubAddr = 0;
    WORD usRemainIdx = 0;

    BYTE pucUsbBillboardVendorDataBuf[_USB_VENDOR_CMD_MAX_LEN] = {0};

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    ucSlaveAddr = ScalerGetByte(P98_0A_HS_EP0_SETUP2);

    bOterIICPin = ScalerGetByte(P98_0B_HS_EP0_SETUP3) & _BIT2;
    ucSubAddeLen = ScalerGetByte(P98_0B_HS_EP0_SETUP3) & (_BIT1 | _BIT0);
    usSubAddr = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    usPageNum = usLength / _USB_EP0_DATA_BUF_SIZE;
    usRemainNum = usLength % _USB_EP0_DATA_BUF_SIZE;

    // temp buffer for U2 RX test
    for(ucPageIdx = 0; ucPageIdx < usPageNum; ucPageIdx++)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
            {
                pucUsbBillboardVendorDataBuf[ucIdx + ucPageIdx * _USB_EP0_DATA_BUF_SIZE] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
            }
            // [TBD]: Write flash...
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }

    // [TBD]: Read the remaining
    if(usRemainNum != 0)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            usRemainIdx = usPageNum * _USB_EP0_DATA_BUF_SIZE;
            for(ucIdx = 0; ucIdx < usRemainNum; ucIdx++)
            {
                pucUsbBillboardVendorDataBuf[usRemainIdx] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                usRemainIdx++;
            }
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }
    // start write eeprom
    ScalerUsbBillboardEepromWrite(bOterIICPin, ucSlaveAddr, ucSubAddeLen, usSubAddr, usLength, pucUsbBillboardVendorDataBuf);
    // end write eeprom
    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, _FALSE);
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Read Sys Eeprom
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorReadSyseeprom(void)
{
    WORD usLength = 0;
    BYTE ucSlaveAddr = 0;
    bit bOterIICPin = 0;
    BYTE ucSubAddeLen = 0;
    WORD usSubAddr = 0;

    BYTE pucUsbBillboardVendorDataBuf[_USB_VENDOR_CMD_MAX_LEN] = {0};

    // temp buffer for U2 TX test
    ucSlaveAddr = ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    bOterIICPin = ScalerGetByte(P98_0B_HS_EP0_SETUP3) & _BIT2;
    ucSubAddeLen = ScalerGetByte(P98_0B_HS_EP0_SETUP3) & (_BIT1 | _BIT0);
    usSubAddr = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    usLength = (ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) + ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    ScalerUsbBillboardEepromRead(bOterIICPin, ucSlaveAddr, ucSubAddeLen, usSubAddr, usLength, pucUsbBillboardVendorDataBuf);
    ScalerUsbBillboardTransmtDataToHost(usLength, pucUsbBillboardVendorDataBuf);
}


//-----------------------------------------------------------------
// Description  : USBVendor Request - Transfer Data to Host
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardTransmtDataToHost(WORD usLength, BYTE *pucDataBuf)
{
    WORD usPageNum = 0;
    WORD usRemainNum = 0;
    BYTE ucIdx = 0;
    BYTE ucPageIdx = 0;
    WORD usRemainIdx = 0;

    usPageNum = usLength / _USB_EP0_DATA_BUF_SIZE;
    usRemainNum = usLength % _USB_EP0_DATA_BUF_SIZE;

    for(ucPageIdx = 0; ucPageIdx < usPageNum; ucPageIdx++)
    {
        // [TBD]:Read data from flash...

        // Set write fifo to transmit data to host
        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
        {
            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucDataBuf[ucIdx + ucPageIdx * _USB_EP0_DATA_BUF_SIZE]);
        }
        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
    }

    if(usRemainNum == 0)
    {
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
        if((ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_HID_REQUEST_REPORT_TYPE_INPUT) && (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE] == 0xC0))
        {
            ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x00);
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, _BIT2);
        }
#endif
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
        if((ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_HID_REQUEST_REPORT_TYPE_INPUT) && (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE] == 0xC0))
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT4, _BIT4);
        }
#endif
    }
    else
    {
        // [TBD]:Read remaining data from flash...

        usRemainIdx = usPageNum * _USB_EP0_DATA_BUF_SIZE;
        // Set write fifo to transmit data to host
        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        for(ucIdx = 0; ucIdx < usRemainNum; ucIdx++)
        {
            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucDataBuf[usRemainIdx]);
            usRemainIdx++;
        }
        ScalerSetByte(P98_06_HS_EP0_TX_BC, usRemainNum);
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
    }
}



//-----------------------------------------------------------------
// Description  : USBVendor Request
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardVendorRequest(void)
{
    DebugMessageBB("U2 Ven Request", ScalerGetByte(P98_09_HS_EP0_SETUP1));
    DebugMessageBB("U2 Ven wVALL", ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    DebugMessageBB("U2 Ven wVALH", ScalerGetByte(P98_0B_HS_EP0_SETUP3));
    DebugMessageBB("U2 Ven wIDXL", ScalerGetByte(P98_0C_HS_EP0_SETUP4));
    DebugMessageBB("U2 Ven wIDXH", ScalerGetByte(P98_0D_HS_EP0_SETUP5));
    DebugMessageBB("U2 Ven wLENL", ScalerGetByte(P98_0E_HS_EP0_SETUP6));
    DebugMessageBB("U2 Ven wLENH", ScalerGetByte(P98_0F_HS_EP0_SETUP7));

    switch(ScalerGetByte(P98_09_HS_EP0_SETUP1))
    {
        case _USB_VENDOR_SET_REGISTER_VALUE:
            ScalerUsbBillboardVendorSetRegisterByte();
            break;

        case _USB_VENDOR_GET_REGISTER_VALUE:
            ScalerUsbBillboardVendorGetRegisterByte();
            break;

        case _USB_VENDOR_WRITE_SYSEEPROM:
            ScalerUsbBillboardVendorWriteSyseeprom();
            break;

        case _USB_VENDOR_READ_SYSEEPROM:
            ScalerUsbBillboardVendorReadSyseeprom();
            break;

        case _USB_VENDOR_WRITE_TO_FLASH:
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
            ScalerUsbBillboardVendorWriteFlash();

            // Background Program Function
            if(g_usUsbBillboardBackgroundProgramPauseTime != 0x00)
            {
                // Check Backgound Program Status
                ScalerUsbBillboardVendorCheckBackgroundProgram();
            }
#endif // End of #if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
            break;

        case _USB_VENDOR_READ_FROM_FLASH:
            ScalerUsbBillboardVendorReadFlash();
            break;

        case _USB_VENDOR_FLASH_SECTOR_ERASE:
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
            ScalerUsbBillboardVendorSectorErase();
#endif
            break;

        case _USB_VENDOR_FLASH_BANK_ERASE:
            ScalerUsbBillboardVendorBankErase();
            break;
        case _USB_VENDOR_ISP_ENABLE:
            ScalerUsbBillboardVendorIspEnable();
            break;

        case _USB_VENDOR_DEBUGMSG_EVENT_START:
            ScalerUsbBillboardVendorDebugMsgEventStart();
            break;

        case _USB_VENDOR_DEBUGMSG_EVENT_FINISH:
            ScalerUsbBillboardVendorDebugMsgEventFinish();
            break;

        case _USB_VENDOR_DEBUGMSG_START:
            ScalerUsbBillboardVendorDebugMsgStart();
            break;

        case _USB_VENDOR_DEBUGMSG_END:
            ScalerUsbBillboardVendorDebugMsgEnd();
            break;

        case _USB_VENDOR_DEBUGMSG_GET_VALUE:
            ScalerUsbBillboardVendorDebugMsgGetValue();
            break;

        case _USB_VENDOR_DEBUGMSG_GET_STRING:
            ScalerUsbBillboardVendorDebugMsgGetString();
            break;

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
        case _USB_VENDOR_DUAL_BANK_PROCESS:
            ScalerUsbBillboardVendorDualBankProcess1();
            break;

        case _USB_VENDOR_SET_CUSTOM_COMMAND:
            ScalerUsbBillboardCustomSetCommand();
            break;
#endif

        case _USB_VENDOR_GET_HW_CRC:
            ScalerUsbBillboardVendorCalculateCrc();
            break;

        case _USB_VENDOR_REALTEK_BB_HANDSHAKE:
            ScalerUsbBillboardVendorHandshake();
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//--------------------------------------------------
// Description  : Bill Board PLL Power
// Input Value  : Action
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardPllPower(EnumBillboardCtrl enumAtion)
{
    if(enumAtion == _USB_BB_ENABLE)
    {
        // Xtal has power down
        if(ScalerGetBit(P80_0E_XTAL_CTRL0, _BIT7) == 0x00)
        {
            // Bit4~3 : 00 --> XI/XO Pad Driving to Strong
            ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), 0x00);

            // Power On External Xtal
            ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, _BIT7);

            // Waiting for xtal stable.
            ScalerTimerDelayXms(6);
        }

        // Bit4~3 : 00 --> XI/XO Pad Driving to weak
        ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
        // Enable AV10 to DV10 Isolation
        ScalerSetBit(P64_7A_USB_PWR_ISO, ~_BIT0, _BIT0);

        // Enable LDO To Generate AV1v0 (AV3V3->AV1V0)
        ScalerSetBit(P64_78_USB_PHY_LDO, ~_BIT0, _BIT0);
#endif
        // Delay Time us [300,x] Waiting for BB PLL Stable
        DELAY_XUS(300);

        // Release Biill Board PHY POR State
        ScalerSetBit(P64_74_HS_USB2_RESET, ~(_BIT1 | _BIT0), 0x00);

#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
        // Disable AV10 to DV10 Isolation
        ScalerSetBit(P64_7A_USB_PWR_ISO, ~_BIT0, 0x00);
#endif
        // Bill Board Connect Enable
        ScalerSetBit(P64_00_HS_USP_CTL, ~_BIT0, _BIT0);

        // Delay Time us [300,x] Waiting for PLL Stable
        DELAY_XUS(300);
    }
    else
    {
#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
        // Enable AV10 to DV10 Isolation
        ScalerSetBit(P64_7A_USB_PWR_ISO, ~_BIT0, _BIT0);

        // Disable LDO
        ScalerSetBit(P64_78_USB_PHY_LDO, ~_BIT0, 0x00);
#endif
        if(ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) == _BIT3)
        {
            // Power down External Xtal
            ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, 0x00);

            // Bit4~3 : 00 --> XI/XO Pad Driving to weak
            ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        }

        // Bill Board PHY goto POR state
        ScalerSetBit(P64_74_HS_USB2_RESET, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Bill Board Connect Disable
        ScalerSetBit(P64_00_HS_USP_CTL, ~_BIT0, 0x00);

        // Reset BB ISP Related Flag while CC unattached
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
        g_bUsbBillboardIspEn = _FALSE;

        // Reset BB ISP Processing Flag
        g_bUsbBillboardIspProcessing = _FALSE;
        g_bUsbBillboardIspProcessingDone = _FALSE;
        g_bUsbBillboardIspProcessingUpdate = _FALSE;

        // Background Program Flag Reset
        // Reset BB Background Puase Timer
        g_usUsbBillboardBackgroundProgramPauseTime = 0;

        // Reset Billboard Background Program Excuting Counter
        g_usUsbBillboardBackgroundProgramExcuteTime = 0;

        // Reset the flag for the release of BB_ISP_WhileLoop
        g_bUsbBillboardBackgroundProgramReleaseFlag = _FALSE;
#endif
    }
}

//--------------------------------------------------
// Description  : USB Standard Request Get Descriptor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetDescriptor(void)
{
    WORD usCount = 0;
    WORD usLoop = 0;
    WORD usData = 0;
    BYTE *pucIndex = NULL;
#if(_USB_BB_HID_TYPE_SUPPORT == _OFF)
    BYTE ucCount = 0;
    BYTE ucCurAltModeNum = 0;
    BYTE ucAltModeNumLoop = 0;
    BYTE ucLoop = 0;
    BYTE ucBmConfigured = 0;
    WORD usBOSCurLength = 0;
    BYTE ucBOSCurNumDeviceCaps = 0;
#endif


#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
    bit bGetExplicitContract = ScalerTypeCRxGetExplicitContract(ScalerTypeCPcbPortConvertToDx(GET_USB_HUB_MUX_SEL_STATUS()));
#endif

    usCount = ScalerGetByte(P98_0E_HS_EP0_SETUP6);

    // Judge Descriptor Type in the high byte
    switch(ScalerGetByte(P98_0B_HS_EP0_SETUP3))
    {
        //=========================================
        case _USB_DEVICE_DESCRIPTOR_TYPE:

            // wLength = valid device descriptor bLength
            if(usCount > 18)
            {
                usCount = 18;
            }

            pucIndex = &tUsbBillboardUsbDeviceDescriptor[0];

            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
            for(PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                // return device descriptor
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
            }

            // When a hub works as full-speed,
            // bDeviceProtocol should be reported as zero
            if(ScalerGetBit(P64_04_HS_USP_STS, _BIT0) == 0x00)
            {
                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x06);
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);

            ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
            // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            break;   // end of USB_DEVICE_DESCRIPTOR_TYPE

        //=========================================
        case _USB_CONFIGURATION_DESCRIPTOR_TYPE:
        case _USB_OTHER_SPEED_CONFIGURATION_TYPE:

            // descriptor index (wValue Low byte) must be checked
            if(usCount > _USB_DESC_SIZE_CONF_TOTAL)
            {
                usCount = _USB_DESC_SIZE_CONF_TOTAL;
            }

            pucIndex = &tUsbBillboardUsbConfigDescriptor[0];

            for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                // for USB_OTHER_SPEED_CONFIGURATION_TYPE Descriptor
                if((PDATA_WORD(0) == 1) && (ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_OTHER_SPEED_CONFIGURATION_TYPE))
                {
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, PDATA_WORD(0));
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, _USB_OTHER_SPEED_CONFIGURATION_TYPE);
                    continue;
                }

#if(_USB_BB_HID_TYPE_SUPPORT == _OFF)
                if(((ScalerGetBit(P64_04_HS_USP_STS, _BIT0) == 0x00) && (ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_CONFIGURATION_DESCRIPTOR_TYPE)) ||
                   ((ScalerGetBit(P64_04_HS_USP_STS, _BIT0) == _BIT0) && (ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_OTHER_SPEED_CONFIGURATION_TYPE)))
                {
                    // bInterval of the first endpoint descriptor
                    if(PDATA_WORD(0) == 0x18)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, PDATA_WORD(0));
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0xFF);
                        continue;
                    }
                }
#endif

                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, PDATA_WORD(0));

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
                // for Type-C CTS TD4.10.2
                if(bGetExplicitContract == _FALSE)
                {
                    if(PDATA_WORD(0) == 0x07)
                    {
                        // Set bmAttributes[6] = 0 (Not Self-Powered)
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x80);
                    }
                    else if(PDATA_WORD(0) == 0x08)
                    {
                        // Set bMaxPower = 500 mA
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0xFA);
                    }
                    else
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
                    }
                }
                else
#endif
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
                }
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
            // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            break;// end of USB_CONFIGURATION_DESCRIPTOR_TYPE

        //=========================================
        case _USB_STRING_DESCRIPTOR_TYPE:

            switch(ScalerGetByte(P98_0A_HS_EP0_SETUP2))    // descriptor index
            {
                case _USB_INDEX0:    // language ID

                    // if(usCount > sizeof(g_stUsbBillboardUsbStringDescriptor))
                    // {
                    // usCount = sizeof(g_stUsbBillboardUsbStringDescriptor);
                    // }

                    // Force to reply 4Byte for [usb cv]Billboard test Fail
                    usCount = _USB_DESC_SIZE_CPLS;

                    pucIndex = &tUsbBillboardUsbStringDescriptor[0];

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                case _TYPE_C_BILLBOARD_URL_INDEX_DP:

                    usData = 0;

                    if((WORD)tBillboardUrl_DP[0] < usCount)
                    {
                        usCount = (WORD)tBillboardUrl_DP[0];
                    }

                    for(usLoop = 0; usLoop < usCount; usLoop++)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBillboardUrl_DP[usLoop]);
                        if(usData == (_USB_EP0_DATA_BUF_SIZE - 1))
                        {
                            ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
                            if(usLoop == (usCount - 1))
                            {
                                ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                            }
                            else
                            {
                                ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                            }
                            usData = 0;
                        }
                        else
                        {
                            usData++;
                        }
                    }

                    if(usData > 0)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, usData);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                    }
                    break;

                case _TYPE_C_BILLBOARD_URL_INDEX_LENOVO:

                    usData = 0;
                    if((WORD)tBillboardUrl_Lenovo[0] < usCount)
                    {
                        usCount = (WORD)tBillboardUrl_Lenovo[0];
                    }

                    for(usLoop = 0; usLoop < usCount; usLoop++)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBillboardUrl_Lenovo[usLoop]);
                        if(usData == (_USB_EP0_DATA_BUF_SIZE - 1))
                        {
                            ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
                            if(usLoop == (usCount - 1))
                            {
                                ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                            }
                            else
                            {
                                ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                            }
                            usData = 0;
                        }
                        else
                        {
                            usData++;
                        }
                    }

                    if(usData > 0)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, usData);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                    }

                    break;

                case _USB_INDEX1:    // iManufacturer

                    if((WORD)tManufacturer[0] < usCount)
                    {
                        usCount = (WORD)tManufacturer[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tManufacturer[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                case _USB_INDEX2:    // iProduct

                    if((WORD)tProduct[0] < usCount)
                    {
                        usCount = (WORD)tProduct[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tProduct[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_INDEX3:

                    if((WORD)tSerialNumber[0] < usCount)
                    {
                        usCount = (WORD)tSerialNumber[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tSerialNumber[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _TYPE_C_BILLBOARD_URL_INDEX_IADDTIONALINFO:    // BB Capability Descriptor iAddtionalInfoURL

                    usData = 0;
                    if((WORD)tBillboardUrl_iAddtionalInfo[0] < usCount)
                    {
                        usCount = (WORD)tBillboardUrl_iAddtionalInfo[0];
                    }

                    for(usLoop = 0; usLoop < usCount; usLoop++)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBillboardUrl_iAddtionalInfo[usLoop]);
                        if(usData == (_USB_EP0_DATA_BUF_SIZE - 1))
                        {
                            ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
                            if(usLoop == (usCount - 1))
                            {
                                ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                            }
                            else
                            {
                                ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                            }
                            usData = 0;
                        }
                        else
                        {
                            usData++;
                        }
                    }

                    if(usData > 0)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, usData);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                    }

                    break;

                case _USB_BB_INDEX1:    // iManufacturer

                    if(g_bUsbBillboardLoadCustomManufactory == _TRUE)
                    {
                        if((WORD)tUsbBillboardManufacturer_Custom[0] < usCount)
                        {
                            usCount = (WORD)tUsbBillboardManufacturer_Custom[0];
                        }

                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                        for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tUsbBillboardManufacturer_Custom[PDATA_WORD(0)]);
                        }
                    }
                    else
                    {
                        if((WORD)tUsbBillboardManufacturer[0] < usCount)
                        {
                            usCount = (WORD)tUsbBillboardManufacturer[0];
                        }

                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                        for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tUsbBillboardManufacturer[PDATA_WORD(0)]);
                        }
                    }


                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_BB_INDEX2:    // iProduct

                    if(g_bUsbBillboardLoadCustomProduct == _TRUE)
                    {
                        if((WORD)tUsbBillboardProduct_Custom[0] < usCount)
                        {
                            usCount = (WORD)tUsbBillboardProduct_Custom[0];
                        }

                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                        for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tUsbBillboardProduct_Custom[PDATA_WORD(0)]);
                        }
                    }
                    else
                    {
                        if((WORD)tUsbBillboardProduct[0] < usCount)
                        {
                            usCount = (WORD)tUsbBillboardProduct[0];
                        }

                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                        for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tUsbBillboardProduct[PDATA_WORD(0)]);
                        }
                    }
                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                case _USB_BB_INDEX3:

                    if((WORD)tBBSerialNumber[0] < usCount)
                    {
                        usCount = (WORD)tBBSerialNumber[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBBSerialNumber[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_RT_HUB_STRING_INDEX0:

                    if((ScalerGetByte(P98_0C_HS_EP0_SETUP4) != 0) || (ScalerGetByte(P98_0D_HS_EP0_SETUP5) != 0))
                    {
                        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
                        break;
                    }

                    if((WORD)tRTString[0] < usCount)
                    {
                        usCount = (WORD)tRTString[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tRTString[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                default:   // undefined string index
                    // NAK if set STALL only. Force to enable handshake.
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL | _USB_EP0_STATUS_HS_EN);
                    ScalerTimerDelayXms(5);
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            }

            break;   // end of USB_STRING_DESCRIPTOR_TYPE


        //=========================================
        case _USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:

            if(usCount > 0x0A)
            {
                usCount = 0x0A;
            }

            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
            for (usLoop = 0; usLoop < usCount; usLoop++)
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBBDeviceQualifier[usLoop]);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
            // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

            break;   // end of USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE

        //===========================================
        case _USB_BOS_DESCRIPTOR_TYPE:

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
            // descriptor index (wValue Low byte) must be checked
            if(usCount > sizeof(tUsbBillboardHidBosDescriptor))
            {
                usCount = sizeof(tUsbBillboardHidBosDescriptor);
            }

            pucIndex = &(tUsbBillboardHidBosDescriptor[0]);

            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

            for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

#else
            // The BCD of High/Full Speed of a supporting super-speed device shall set to "0210".
            // If the BCD of device descriptor is "0210" or higher, the BOS Descriptor need to be replied.
            // So I set the BCD as "0210" and will return the  BOS Descriptor request.

            // Get svid, altmode, altmodestring, Vdo info
            ScalerUsbBillboardGetAltModeInfo();

            // Get current alt mode num
            for(ucCount = 0; ucCount < _USB_MAX_ALTERNATE_MODE_NUM; ucCount++)
            {
                ucCurAltModeNum += g_pstUsbBillboardAltModeInfo[ucCount].ucCurAltModeActive;
            }

            // Indpendent of TypeC to Make/Check BB expose Normally. ex.BB Debug use / Verify / Program...
            if(ucCurAltModeNum == 0)
            {
                ucCurAltModeNum = _USB_MAX_ALTERNATE_MODE_NUM;
            }

            // Update current NumDeviceCaps
            ucBOSCurNumDeviceCaps = tUsbBillboardBOSDeviceCapabilityDescriptor[4] + ucCurAltModeNum;
            DebugMessageBB("ucBOSCurNumDeviceCaps", ucBOSCurNumDeviceCaps);

            // Get current BOS total Length
            usBOSCurLength = (_USB_BB_BOS_DESC_FIRST_PART_LEN + (_USB_DESC_SIZE_ALTERNATE_MODE + _USB_DESC_SIZE_BILLBOARD_ALTMODE_CAP) * ucCurAltModeNum);

            // wLength = valid device descriptor bLength
            if(usCount > usBOSCurLength)
            {
                usCount = usBOSCurLength;
            }

            pucIndex = &tUsbBillboardBOSDeviceCapabilityDescriptor[0];

            // Get current BOS total Length
            usBOSCurLength = (_USB_BB_BOS_DESC_FIRST_PART_LEN + (_USB_DESC_SIZE_ALTERNATE_MODE + _USB_DESC_SIZE_BILLBOARD_ALTMODE_CAP) * ucCurAltModeNum);

            if(usCount == 0x05)
            {
                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                for(usLoop = 0; usLoop < usCount; usLoop++)
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop]);
                }

                ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                ScalerUsbBillboardXferForGetDescriptor(_USB_CTRL_XFER_READ, _TRUE);
                // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            }
            else if(usCount >= usBOSCurLength)
            {
                usData = 0;

                // Step1 : Reply BOS + USB2.0 Extension + SuperSpeed USB + ContainID + BillBoard Capability descriptor(offset0-43)
                for (usLoop = 0; usLoop < _USB_BB_BOS_DESC_FIRST_PART_LEN; usLoop++)
                {
                    // Configure legacy BOS descriptors (USB2 EXT Cap, Superspeed Cap, Container ID) and Billboard Capability Descriptor (Byte 0~43)
                    // We could modify bmConfigured in Billboard Capability Descriptor
                    // i = 50~81 for 128 Alternate modes
                    // usloop = 0x02/0x03:update BOS curruent total length.
                    // usloop = 0x04:update BOS curruent total bNumDeviceCaps.
                    // usloop = 0x2A: update BB CAP CurLength.
                    // usloop = 0x2E: update Support altmode NUM.
                    // usloop = 0x32/0x33: update altmode status
                    // Note:BB can send up to Max 8 valid altmode info if as below(process loop 0x32/0x33)(Cai)
                    if(usLoop == 0x02)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (usBOSCurLength % 256));
                    }
                    else if(usLoop == 0x03)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (usBOSCurLength / 256));
                    }
                    else if(usLoop == 0x04)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBOSCurNumDeviceCaps);
                    }
                    else if(usLoop == _USB_BB_CAP_LEN_OFFSEET_IN_BOS)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (_USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_ALTERNATE_MODE * ucCurAltModeNum));
                    }
                    else if(usLoop == _USB_BB_CAP_ALTMODE_NUM_OFFSET_IN_BOS)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucCurAltModeNum);
                    }
                    else if(usLoop == _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_1_4)
                    {
                        // Reply first 4 bit pair (first Byte) indicating the state of the specified alt mode.
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);

                        ucAltModeNumLoop = ((ucCurAltModeNum > 0x04) ? 0x04 : ucCurAltModeNum);
                        for(ucCount = 0; ucCount < ucAltModeNumLoop; ucCount++)
                        {
                            ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[ucCount].ucAltModeStauts) & 0x03) << (ucCount * 2));
                        }
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBmConfigured);
                        ucBmConfigured = 0;
                    }
                    else if(usLoop == _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_5_8)
                    {
                        // Reply second 4 bit pair (second Byte) indicating the state of the specified alt mode.
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        if(ucCurAltModeNum > 0x04)
                        {
                            ucAltModeNumLoop = ucCurAltModeNum - 4;
                            for(ucCount = 0; ucCount < ucAltModeNumLoop; ucCount++)
                            {
                                // ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[(ucCount + 4)].ucAltModeStauts) & 0x03) << (ucCount * 2));
                                ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[(ucCurAltModeNum - (ucAltModeNumLoop - ucCount))].ucAltModeStauts) & 0x03) << (ucCount * 2));
                            }
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBmConfigured);
                            ucBmConfigured = 0;
                        }
                        else
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                        }
                    }
                    else
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop]);
                    }

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }
                }

                // Step2 : Reply BillBoard Capability descriptor[offset44 -> (44+n*4), n = ucCurAltModeNum]
                for (usLoop = 0; usLoop < ucCurAltModeNum; usLoop++)
                {
                    // Configure Billboard Capability Descriptor (Byte 44~47*(_USB_NUM_ALTERNATE_MODE*4))
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucSVID_LO);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucSVID_HI);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucMode);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucStringIndex);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }
                }

                // Step3:Reply BillBoard AltMode Capability descriptor(Describe additional properties for a given alternate mode)
                for (usLoop = 0; usLoop < ucCurAltModeNum; usLoop++)
                {
                    // -------- BB AltModeCapabilityDescriptor ucLength(Constant) ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_stUsbBillboardAltModeCapabilityDescriptor.ucLength);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- BB AltModeCapabilityDescriptor ucDescriptorType(Constant) ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_stUsbBillboardAltModeCapabilityDescriptor.ucDescriptorType);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- BB AltModeCapabilityDescriptor ucDevCapabilityType(Constant) ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_stUsbBillboardAltModeCapabilityDescriptor.ucDevCapabilityType);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- BB AltModeCapabilityDescriptor ucIndex ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (g_stUsbBillboardAltModeCapabilityDescriptor.ucIndex + usLoop));

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- AlternateModeVdo Byte0 ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucdwAlternateModeVdo_Byte0);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- AlternateModeVdo Byte1 ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucdwAlternateModeVdo_Byte1);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- AlternateModeVdo Byte2 ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucdwAlternateModeVdo_Byte2);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    // -------- AlternateModeVdo Byte3 ---------
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[usLoop].ucdwAlternateModeVdo_Byte3);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        if(usLoop == ucCurAltModeNum - 1)
                        {
                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                        }
                        else
                        {
                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        }
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }
                }

                // Reply last packet(length = usdata) if 0 < remaing data(usdata) < _USB_EP0_DATA_BUF_SIZE Bytes
                if(usData > 0)
                {
                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usData);

                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                }
            }
            else
            {
                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

                // _USB_EP0_DATA_BUF_SIZE = 64 is BB Endpoint Buffer, Reply BOS(5)+U2EXTENSION(7)+CONTAINID(20)+32 of BBCAP(44+4x) at Most
                if(usCount <= _USB_EP0_DATA_BUF_SIZE)
                {
                    for(usLoop = 0; usLoop < usCount; usLoop++)
                    {
                        if(usLoop == 0x02)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (usBOSCurLength % 256));
                        }
                        else if(usLoop == 0x03)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (usBOSCurLength / 256));
                        }
                        else if(usLoop == 0x04)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBOSCurNumDeviceCaps);
                        }
                        else if(usLoop == _USB_BB_CAP_LEN_OFFSEET_IN_BOS)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (_USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_ALTERNATE_MODE * ucCurAltModeNum));
                        }
                        else if(usLoop == _USB_BB_CAP_ALTMODE_NUM_OFFSET_IN_BOS)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucCurAltModeNum);
                        }
                        else if(usLoop == _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_1_4)
                        {
                            // Reply first 4 bit pair (first Byte) indicating the state of the specified alt mode.
                            ucAltModeNumLoop = ((ucCurAltModeNum > 0x04) ? 0x04 : ucCurAltModeNum);
                            for(ucCount = 0; ucCount < ucAltModeNumLoop; ucCount++)
                            {
                                ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[ucCount].ucAltModeStauts) & 0x03) << (ucCount * 2));
                            }
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBmConfigured);
                            ucBmConfigured = 0;
                        }
                        else if(usLoop == _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_5_8)
                        {
                            // Reply second 4 bit pair (second Byte) indicating the state of the specified alt mode.
                            if(ucCurAltModeNum > 0x04)
                            {
                                ucAltModeNumLoop = ucCurAltModeNum - 4;
                                for(ucCount = 0; ucCount < ucAltModeNumLoop; ucCount++)
                                {
                                    // ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[(ucCount + 4)].ucAltModeStauts) & 0x03) << (ucCount * 2));
                                    ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[(ucCurAltModeNum - (ucAltModeNumLoop - ucCount))].ucAltModeStauts) & 0x03) << (ucCount * 2));
                                }
                                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBmConfigured);
                                ucBmConfigured = 0;
                            }
                            else
                            {
                                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                            }
                        }
                        else
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop]);
                        }
                    }

                    // For reply 64B Case,I dont know why Normal Host will indicate stall info if not add the 2nd/3rd line. But below will make CTS Host abnormally
                    // ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
                    // ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
                    // ScalerSetByte(P98_06_HS_EP0_TX_BC, 0);
                    // ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                }
                else // support Max 4 Altmode all ON
                {
                    for(usLoop = 0; usLoop < _USB_EP0_DATA_BUF_SIZE; usLoop++)
                    {
                        if(usLoop == 0x02)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (usBOSCurLength % 256));
                        }
                        else if(usLoop == 0x03)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (usBOSCurLength / 256));
                        }
                        else if(usLoop == 0x04)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBOSCurNumDeviceCaps);
                        }
                        else if(usLoop == _USB_BB_CAP_LEN_OFFSEET_IN_BOS)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (_USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_ALTERNATE_MODE * ucCurAltModeNum));
                        }
                        else if(usLoop == _USB_BB_CAP_ALTMODE_NUM_OFFSET_IN_BOS)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucCurAltModeNum);
                        }
                        else if(usLoop == _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_1_4)
                        {
                            // Reply first 4 bit pair (first Byte) indicating the state of the specified alt mode.
                            ucAltModeNumLoop = ((ucCurAltModeNum > 0x04) ? 0x04 : ucCurAltModeNum);
                            for(ucCount = 0; ucCount < ucAltModeNumLoop; ucCount++)
                            {
                                ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[ucCount].ucAltModeStauts) & 0x03) << (ucCount * 2));
                            }
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBmConfigured);
                            ucBmConfigured = 0;
                        }
                        else if(usLoop == _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_5_8)
                        {
                            // Reply second 4 bit pair (second Byte) indicating the state of the specified alt mode.
                            if(ucCurAltModeNum > 0x04)
                            {
                                ucAltModeNumLoop = ucCurAltModeNum - 4;
                                for(ucCount = 0; ucCount < ucAltModeNumLoop; ucCount++)
                                {
                                    // ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[(ucCount + 4)].ucAltModeStauts) & 0x03) << (ucCount * 2));
                                    ucBmConfigured += (((g_pstUsbBillboardAltModeInfo[(ucCurAltModeNum - (ucAltModeNumLoop - ucCount))].ucAltModeStauts) & 0x03) << (ucCount * 2));
                                }
                                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucBmConfigured);
                                ucBmConfigured = 0;
                            }
                            else
                            {
                                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                            }
                        }
                        else
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop]);
                        }
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);

                    // Reset BB Buf start addr
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

                    // Reply info which exceed _USB_EP0_DATA_BUF_SIZE length _ fixed Part
                    if((usCount - _USB_EP0_DATA_BUF_SIZE) <= (_USB_BB_BOS_DESC_FIRST_PART_LEN - _USB_EP0_DATA_BUF_SIZE))
                    {
                        for(usLoop = 0; usLoop < (usCount - _USB_EP0_DATA_BUF_SIZE); usLoop++)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop + _USB_EP0_DATA_BUF_SIZE]);
                        }
                    }
                    else // Reply info which exceed _USB_EP0_DATA_BUF_SIZE length _ fixed Part + Variable Part
                    {
                        for(usLoop = 0; usLoop < (_USB_BB_BOS_DESC_FIRST_PART_LEN - _USB_EP0_DATA_BUF_SIZE); usLoop++)
                        {
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop + _USB_EP0_DATA_BUF_SIZE]);
                        }

                        for(ucLoop = 0; ucLoop < ucCurAltModeNum; ucLoop++)
                        {
                            // Reply BillBoard Capability descriptor[offset44 -> (44+n*4)  n = ucCurAltModeNum
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucSVID_LO);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucSVID_HI);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucMode);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucStringIndex);
                        }

                        for(ucLoop = 0; ucLoop < ucCurAltModeNum; ucLoop++)
                        {
                            // Reply BillBoard AltMode Capability descriptor(Describe additional properties for a given alternate mode
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_stUsbBillboardAltModeCapabilityDescriptor.ucLength);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_stUsbBillboardAltModeCapabilityDescriptor.ucDescriptorType);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_stUsbBillboardAltModeCapabilityDescriptor.ucDevCapabilityType);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (g_stUsbBillboardAltModeCapabilityDescriptor.ucIndex + ucLoop));
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucdwAlternateModeVdo_Byte0);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucdwAlternateModeVdo_Byte1);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucdwAlternateModeVdo_Byte2);
                            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pstUsbBillboardAltModeInfo[ucLoop].ucdwAlternateModeVdo_Byte3);
                        }
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, (usCount - _USB_EP0_DATA_BUF_SIZE));
                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
                }
            }
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

            break;// end of USB_BOS_DESCRIPTOR_TYPE

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
        case _USB_REPORT_DESCRIPTOR_TYPE:

            DebugMessageTypeC("[HID] Report Description", usCount);

            // descriptor index (wValue Low byte) must be checked
            if(usCount > sizeof(tUsbBillboardHidReportDescriptor))
            {
                usCount = sizeof(tUsbBillboardHidReportDescriptor);
            }

            pucIndex = &(tUsbBillboardHidReportDescriptor[0]);

            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

            for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

            break;
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

        default:// invalid command, Request Error

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardSetAddr(void)
{
    BYTE data ucAddr = 0;

    ucAddr = ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    ucAddr &= _USB_DEV_ADDR_MASK;
    ucAddr |= _USB_DEV_ADDR_VALID;

    // HW doesn't change the device address immediatelly;
    // It will update the device address after the status stage has finished;
    ScalerSetByte(P64_54_HS_DEV_ADDR, ucAddr);
    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Configureation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardSetConf(void)
{
    switch (ScalerGetByte(P98_0A_HS_EP0_SETUP2))    // lower byte of wValue specifies the desired configuration
    {
        case 0x00: // Un-configured

            ScalerUsbBillboardInitCtrlVariable();

            ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, 0x00);
            ScalerSetBit(P64_56_HS_DEV_G_CFG, ~(_BIT1 | _BIT0), _BIT1);

            // Finish Control Transfer
            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

            break;

        case 0x01: // using current configuration, do nothing

            // initialization of interrupt endpoint 1
            g_ucUsbBillboardUsbConfigurationValue = 0x01;

            ScalerSetBit(P64_52_HS_DEV_G_STA, ~(_BIT1 | _BIT0), 0x00);

            // Clear interrupt flag for configuration
            ScalerSetBit(P64_20_HS_USP_IRQ, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            ScalerSetBit(P64_56_HS_DEV_G_CFG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Finish Control Transfer
            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

            break;

        default: // return a Request Error

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Get Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetInterface(void)
{
    // Undefined Request
    // Hubs are allowed to support only one interface
    // alternate setting not supported
    // return 0 to host in the data packet
    WORD data usCount = 0;

    // If the interface specified does not exist, then the device responds with a Request Error.
    usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

    if(usCount != 0)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

    ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x01);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardSetInterface(void)
{
    // Undefined Request
    // Hubs are allowd to support only one interface
    WORD data usCount = 0;

    // If the interface(wIndex) does not exist, then the device responds with a Request Error
    usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

    if(usCount != 0)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }

    // If the alternate setting(wValue) does not exist, then the device responds with a Request Error
    usCount = ((ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) | ScalerGetByte(P98_0A_HS_EP0_SETUP2));

    // alternate setting not supported
    if (usCount == 0)  // interface 0, do nothing
    {
        // The Halt feature is reset to zero after either a SetConfiguration() or SetInterface()
        // request even if the requested configuration or interface is the same as the current
        // configuration or interface.
        ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, 0x00);

        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
    }
    else
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Get Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetStatus(void)
{
    WORD data usCount = 0;
    BYTE data ucTemp = 0;

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
    bit bGetExplicitContract = ScalerTypeCRxGetExplicitContract(ScalerTypeCPcbPortConvertToDx(GET_USB_HUB_MUX_SEL_STATUS()));
#endif

    // If wValue should be 0 and wLength should be two.
    usCount = ((ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) | ScalerGetByte(P98_0A_HS_EP0_SETUP2));

    if(usCount != 0)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
        return;
    }

    usCount = ((ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) | ScalerGetByte(P98_0E_HS_EP0_SETUP6));

    if(usCount != 2)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
        return;
    }

    switch(ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_RECIPIENT_MASK)
    {
        //=========================================
        case _USB_REQUEST_RECIPIENT_DEVICE: // Device

            usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

            // wINDEX must be 0 for a device status request
            if (!usCount)
            {
                // Byte0:
                // bit0: 1b, self powered
                // bit1: 0b, Remote Wakeup
                // bit2~bit7: Reserved
                ucTemp = 0;

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
                // Let GetStatus content aligns Configuration Descriptor
                if(bGetExplicitContract == _TRUE)
#endif
                {
                    ucTemp |= _USB_DEV_STATUS_SELF_POWERED;
                }

                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucTemp);
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);   // Reserved to 0

                ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

                ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            }
            else
            {
                // return a STALL handshake
                ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            }
            break;

        //=========================================
        case _USB_REQUEST_RECIPIENT_INTERFACE: // Interface

            usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

            // A GetStatus() request to any interface except interface0 in a function shall return all zeros.
            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

            ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            break;

        //=========================================
        case _USB_REQUEST_RECIPIENT_ENDPOINT: // Endpoint
            switch (ScalerGetByte(P98_0C_HS_EP0_SETUP4))
            {
                // In USB2 or USB3 Spec 9.3.4, 'Direction' of wIndex Format for control pipe can be '0' or '1'
                case _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_IN:
                case _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_OUT:

                    // HighSpeed devices do not support function stall all the time on control endpoints.
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                case _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN: // Interrtup Endpoint 1


                    if (ScalerGetBit(P64_52_HS_DEV_G_STA, _BIT1) == _BIT1) // endpoint Halt
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x01);
                    }
                    else
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                    }

                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                default:
                    // return a STALL handshake
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
                    break;
            }
            break;// end of switch for endpoint

        //=========================================
        default:    // invalid request type
            // return a STALL handshake
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;

    } // end of switch
}

//--------------------------------------------------
// Description  : USB Standard Request - Get Configuration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetConf(void)
{
    // only two possible configuration values: 0 and 1
    if ((g_ucUsbBillboardUsbConfigurationValue == 0x00) || (g_ucUsbBillboardUsbConfigurationValue == 0x01))
    {
        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_ucUsbBillboardUsbConfigurationValue);

        ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x01);

        ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    }
    else  // undefined Configuration Value
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardSetFeature(void)
{
    switch (ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_RECIPIENT_MASK)
    {
        case _USB_REQUEST_RECIPIENT_DEVICE: // Device
            switch (ScalerGetByte(P98_0A_HS_EP0_SETUP2))
            {
                case _USB_DEVICE_REMOTE_WAKEUP: // Remote Wakeup

                    g_ucUsbBillboardUsbHostEnableRemoteWakeup = 0;

                    // Disable HW Remote Wakeup Function
                    ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT0, 0x00);

                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                case _USB_TEST_STATE: // Test Mode

                    switch (ScalerGetByte(P98_0D_HS_EP0_SETUP5))
                    {
                        case 0x01: // Test_J

                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_J));
                            while(1) {};

                            break;

                        case 0x02: // Test_K

                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_K));
                            while(1) {};

                            break;

                        case 0x03: // Test_SE0_NAK

                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_SE0_NAK));
                            while(1) {};

                            break;

                        case 0x04: // Test_Packet

                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_PACKET));
                            while(1) {};

                            break;

                        case 0x05: // Test_Force_Enable

                            ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            while(1) {};

                            break;

                        default:

                            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                            break;
                    }

                    break;

                default:

                    break;
            } // end of switch HS_SETUP_PKT_wVALUE_L
            break;    // Break of case 0x00

        case _USB_REQUEST_RECIPIENT_INTERFACE: // Interface

            // SetFeature() for Interface is not valid in HS
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;

        case _USB_REQUEST_RECIPIENT_ENDPOINT: // Endpoints

            switch (ScalerGetByte(P98_0C_HS_EP0_SETUP4))
            {
                case _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN: // INT Endpoint 1

                    // Endpoint B (INT endpoint) Halt
                    ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, _BIT1);
                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                default: // invalid command

                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            } // end of switch SETUP_PKT_wINDEX_L

            break;

        default: // invalid command

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;

    } // end of HS_SETUP_PKT_bmREQUST_TYPE
}

//--------------------------------------------------
// Description  : USB Standard Request - Clear Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardClearFeature(void)
{
    switch(ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_RECIPIENT_MASK)
    {
        case _USB_REQUEST_RECIPIENT_DEVICE: // Device

            switch (ScalerGetByte(P98_0A_HS_EP0_SETUP2))
            {
                case _USB_DEVICE_REMOTE_WAKEUP: // Remote Wakeup for USB2.0

                    g_ucUsbBillboardUsbHostEnableRemoteWakeup = 0;

                    // Disable HW Remote Wakeup Function
                    ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT0, 0x00);

                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                case _USB_TEST_STATE: // Test mode

                    // Test_Mode feature cannot be cleared by the ClearFeature() request
                    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                default:

                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            }
            break;

        case _USB_REQUEST_RECIPIENT_INTERFACE: // Interface

            // ClearFeature() for Interface is not valid in HS
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;


        case _USB_REQUEST_RECIPIENT_ENDPOINT: // Endpoint

            if (ScalerGetByte(P98_0A_HS_EP0_SETUP2) == _USB_ENDPOINT_HALT)
            {
                switch (ScalerGetByte(P98_0C_HS_EP0_SETUP4))
                {
                    // Clear Endpoint Stall feature;
                    case _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN: // INT Endpoint 1

                        ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, 0x00);

                        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                        break;

                    default:

                        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                        break;

                }    // end of switch SETUP_PKT_wINDEX_L

                break;
            }
            else
            {
                ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                break;
            }

        default:

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;
    } // end of switch HS_SETUP_PKT_bmREQUST_TYPE
}

//--------------------------------------------------
// Description  : Billboard get altmode info from PD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetAltModeInfo(void)
{
    memset(g_pstUsbBillboardAltModeInfo, 0x00, _USB_MAX_ALTERNATE_MODE_NUM * sizeof(StructTypeCBillboardInfo));

    if(GET_USB_HUB_MUX_SEL_STATUS() == _D0_TYPE_C_PORT)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        ScalerTypeCGetAltModeBillboardInfo(_D0_TYPE_C_PORT, (BYTE *)(&g_pstUsbBillboardAltModeInfo));
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        ScalerUsbBillboardGetAltModeRtsInfo(_D0_TYPE_C_PORT, (BYTE *)(&g_pstUsbBillboardAltModeInfo));
#elif(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
        ScalerUsbBillboardGetAltModeUserInfo(_D0_TYPE_C_PORT, (BYTE *)(&g_pstUsbBillboardAltModeInfo));
#endif
    }
    else if(GET_USB_HUB_MUX_SEL_STATUS() == _D1_TYPE_C_PORT)
    {
#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
        ScalerTypeCGetAltModeBillboardInfo(_D1_TYPE_C_PORT, (BYTE *)(&g_pstUsbBillboardAltModeInfo));
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        ScalerUsbBillboardGetAltModeRtsInfo(_D1_TYPE_C_PORT, (BYTE *)(&g_pstUsbBillboardAltModeInfo));
#elif(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
        ScalerUsbBillboardGetAltModeUserInfo(_D1_TYPE_C_PORT, (BYTE *)(&g_pstUsbBillboardAltModeInfo));
#endif
    }

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
    if(GET_USB_BB_USER_ENABLE_FLAG() == _ENABLE)
    {
        BYTE ucCount = 0;

        for(ucCount = 0; ucCount < _USB_MAX_ALTERNATE_MODE_NUM; ucCount++)
        {
            if((g_pstUsbBillboardAltModeInfo[ucCount].ucSVID_LO == (BYTE)(_DP_SID)) && (g_pstUsbBillboardAltModeInfo[ucCount].ucSVID_HI == (BYTE)(_DP_SID >> 8)))
            {
                g_pstUsbBillboardAltModeInfo[ucCount].ucAltModeStauts = 0x03;

                DebugMessageBB("[BB_Program] Do Not Show Notification by Set DP_AltModeStauts to 2'b11(Success) ", g_pstUsbBillboardAltModeInfo[ucCount].ucAltModeStauts);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Initial USB Variable
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerUsbBillboardInitCtrlVariable(void)
{
    g_ucUsbBillboardUsbConfigurationValue = 0;
    g_ucUsbBillboardUsbHostEnableRemoteWakeup = 0;
    g_ucUsbBillboardUsbVendorComEnb = 0;
}

//--------------------------------------------------
// Description  : USB Control Transfer Sequence
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerUsbBillboardCtrlXfer(BYTE ucXferType, BYTE ucIsLastPacket)
{
    // Update by Frank@2017/07/13
    DWORD ulCounter = 200000;

    // Validate data in FIFO.
    if(ucXferType == _USB_CTRL_XFER_READ)
    {
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, _BIT2);

        // In EP0 read data transfer, return 0 if the data stage doesn't finished in 1 seconds
        // Howard temp removed if( !SetupISR_WaitTimeOut(HS_EP0_CTRL, HS_HUB_EP0_SEND_PKT_EN, 0x00, 100, ALL_MASK_BIT_MEET))
        // Howard temp removed {
        // Howard temp removed     // Disable BUF0 for EP0 TX Enable
        // Howard temp removed     ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, 0x00);

        // Howard temp removed     // Timeout occurred, do not STALL and just return 0, let caller determine STALL or not
        // Howard temp removed     return 0;
        // Howard temp removed }

        // TX polling & wait
        while((ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT2) != 0x00) && (ulCounter-- > 0))
        {
            DELAY_5US();
        }

        // 1SEC Time-out
        if(ulCounter == 0)
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, 0x00);
            return _FALSE;
        }

        if(ucIsLastPacket == 1)
        {
            // Clear CONTROL_STATUS_HANDSHAKE
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT0, _BIT0);
        }

        return _TRUE;
    }
    else if(ucXferType == _USB_CTRL_XFER_WRITE_DATA_STAGE)
    {
        // Enable EP0 for FIFO
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT3, _BIT3);

        // In EP0 write data transfer, wait all data already received in the Buf0
        // Howard temp removed if( !SetupISR_WaitTimeOut(HS_EP0_CTRL, HS_HUB_EP0_REC_PKT_EN, 0x00, 100, ALL_MASK_BIT_MEET))
        // Howard temp removed {
        // Howard temp removed     // Disable BUF0 for EP0 RX
        // Howard temp removed     ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT3, 0x00);

        // Howard temp removed     // Timeout occurred, do not STALL and just return 0, let caller determine STALL or not
        // Howard temp removed     return 0;
        // Howard temp removed }

        // RX polling & wait
        while((ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT3) != 0x00) && (ulCounter-- > 0))
        {
            DELAY_5US();
        }

        // 1SEC Time-out
        if(ulCounter == 0)
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT3, 0x00);
            return _FALSE;
        }

        return _TRUE;
    }
    else if(ucXferType == _USB_CTRL_XFER_WRITE_STATUS_STAGE)
    {
        // Empty
    }
    else // _USB_CTRL_XFER_NO_DATA
    {
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
        if((ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_HID_REQUEST_REPORT_TYPE_INPUT) && (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE] == 0xC0))
        {
            while((ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT2) != 0x00) && (ulCounter-- > 0))
            {
                DebugMessageTypeC("WHILE WAIT XFER Tx** NO DATA", ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT2));
                DELAY_5US();
            }

            // 1SEC Time-out
            if(ulCounter == 0)
            {
                ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, 0x00);
                DebugMessageTypeC("[ulCounter] WHILE WAIT XFER Tx** NO DATA", ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT2));
                return _FALSE;
            }
        }
#endif
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT0, _BIT0);

        return _TRUE;
    }

    return _FALSE;
}


//--------------------------------------------------
// Description  : USB Control Transfer for GetDescriptor
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerUsbBillboardXferForGetDescriptor(BYTE ucXferType, BYTE ucIsLastPacket)
{
    // Validate data in FIFO.
    if(ucXferType == _USB_CTRL_XFER_READ)
    {
        if(ucIsLastPacket == 1)
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
        }
        else
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT2), (_BIT2));
        }

        return _TRUE;
    }

    return _FALSE;
}


//--------------------------------------------------
// Description  : Load PID/VID from MCM flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardLoadTrimming(void)
{
/* // TBD for RL6573
#if(_TRIMMING_DATA_FROM_FLASH == _ON)
    BYTE pucUSBPIDVIDData[5];
    BYTE pucUSBInfoData[32];
    BYTE ucCnt = 0;
    BYTE ucIdx = 0;

    if(ScalerFlashRead(_TRIMMING_DATA_FLASH_BANK_MCM_MD, _USB_MCM_FLASH_USB_PIDVID, sizeof(pucUSBPIDVIDData), pucUSBPIDVIDData) == _TRUE)
    {
        if(pucUSBPIDVIDData[0] == 0x55)
        {
            g_stUsbBBDeviceDescriptor.ucPID_Hi = pucUSBPIDVIDData[1];
            g_stUsbBBDeviceDescriptor.ucPID_Lo = pucUSBPIDVIDData[2];
            g_stUsbBBDeviceDescriptor.ucVID_Hi = pucUSBPIDVIDData[3];
            g_stUsbBBDeviceDescriptor.ucVID_Lo = pucUSBPIDVIDData[4];
        }
    }

    if(ScalerFlashRead(_TRIMMING_DATA_FLASH_BANK_MCM_MD, _USB_MCM_FLASH_USB_MANUFACTORY, sizeof(pucUSBInfoData), pucUSBInfoData) == _TRUE)
    {
        if(pucUSBInfoData[0] == 0x55)  // check pUSBInfoData[0] for valid byte
        {
            ucIdx = 0;
            g_bLoadCustomManufactory = _TRUE;
            g_pucBBManufacturer_Custom[0] = sizeof(pucUSBInfoData) * 2;
            g_pucBBManufacturer_Custom[1] = 3;
            for(ucCnt = 2; ucCnt < g_pucBBManufacturer_Custom[0]; ucCnt += 2)
            {
                ucIdx++;  // skip valid byte
                if(pucUSBInfoData[ucIdx] == 0xFF)
                {
                    break;
                }
                g_pucBBManufacturer_Custom[ucCnt] = pucUSBInfoData[ucIdx];
            }
            g_pucBBManufacturer_Custom[0] = ucIdx * 2; // Reasign size, limit to 62Byte at most.
        }
    }

    if(ScalerFlashRead(_TRIMMING_DATA_FLASH_BANK_MCM_MD, _USB_MCM_FLASH_USB_PRODUCT, sizeof(pucUSBInfoData), pucUSBInfoData) == _TRUE)
    {
        if(pucUSBInfoData[0] == 0x55) // check pUSBInfoData[0] for valid byte
        {
            ucIdx = 0;
            g_bLoadCustomProduct = _TRUE;
            g_pucBBProduct_Custom[0] = sizeof(pucUSBInfoData) * 2;
            g_pucBBProduct_Custom[1] = 3;
            for(ucCnt = 2; ucCnt < g_pucBBProduct_Custom[0]; ucCnt += 2)
            {
                ucIdx++;    // skip valid byte
                if(pucUSBInfoData[ucIdx] == 0xFF)
                {
                    break;
                }
                g_pucBBProduct_Custom[ucCnt] = pucUSBInfoData[ucIdx];
            }
            g_pucBBProduct_Custom[0] = ucIdx * 2; // Reasign size, limit to 62Byte at most.
        }
    }
#endif  // End of #if(_TRIMMING_DATA_FROM_FLASH == _ON)
*/
}


#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
//-----------------------------------------------------------------
// Description  : USB HID CLASS Request
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidClassRequest(void)
{
    DebugMessageBB("U2 Ven Request", ScalerGetByte(P98_09_HS_EP0_SETUP1));
    DebugMessageBB("U2 Ven wVALL", ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    DebugMessageBB("U2 Ven wVALH", ScalerGetByte(P98_0B_HS_EP0_SETUP3));
    DebugMessageBB("U2 Ven wIDXL", ScalerGetByte(P98_0C_HS_EP0_SETUP4));
    DebugMessageBB("U2 Ven wIDXH", ScalerGetByte(P98_0D_HS_EP0_SETUP5));
    DebugMessageBB("U2 Ven wLENL", ScalerGetByte(P98_0E_HS_EP0_SETUP6));
    DebugMessageBB("U2 Ven wLENH", ScalerGetByte(P98_0F_HS_EP0_SETUP7));

    switch(ScalerGetByte(P98_09_HS_EP0_SETUP1))
    {
        case _USB_HID_REQUEST_GET_REPORT:
            ScalerUsbBillboardHidRequestGetReport();
            break;

        case _USB_HID_REQUEST_SET_REPORT:
            ScalerUsbBillboardHidRequestSetReport();
            break;

        case _USB_HID_REQUEST_SET_IDLE:
            // Test
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//----------------------------------------------------------------
// Description  : USB HID Class Request - Set Report
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardHidRequestSetReport(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;
    WORD usRemainIdx = 0;
    BYTE ucPageIdx = 0;
    WORD usPageNum = 0;
    WORD usRemainNum = 0;

    // temp buffer for U2 RX test
    WORD usPageTmp = 0;

    BYTE ucReportID = 0;
    BYTE ucReportType = 0;
    WORD usInterface = 0;

    // Reset HID Report Array
    // memset(g_pucUsbBillboardHidReport, 0x00, _USB_HID_REPORT_COUNT_LENGTH);

    ucReportID = ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    ucReportType = ScalerGetByte(P98_0B_HS_EP0_SETUP3);
    usInterface = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    usLength = _USB_HID_REPORT_COUNT_LENGTH;
    usPageNum = _USB_HID_REPORT_COUNT_PAGE_NUM;
    usRemainNum = _USB_HID_REPORT_COUNT_REMAIN;

    DebugMessageBB("U2-WT-ucReportID", ucReportID);
    DebugMessageBB("U2-WT-ucReportType", ucReportType);
    DebugMessageBB("U2-WT-usInterface", usInterface);
    DebugMessageBB("U2-WT-usLength", usLength);
    DebugMessageBB("U2-WT-usPageNum", usPageNum);
    DebugMessageBB("U2-WT-usRemainNum", usRemainNum);

    ucReportID = ucReportID;
    usInterface = usInterface;
    usLength = usLength;

    // [TBD]: Read the complete 64Byte
    for(ucPageIdx = 0; ucPageIdx < usPageNum; ucPageIdx++)
    {
        usPageTmp = ucPageIdx * _USB_EP0_DATA_BUF_SIZE;
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
            {
                g_pucUsbBillboardHidReport[ucIdx + usPageTmp] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
            }
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }

    // [TBD]: Read the remaining
    if(usRemainNum != 0)
    {
        if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_WRITE_DATA_STAGE, _FALSE))
        {
            // Set read fifo to receive host data
            ScalerSetByte(P9A_02_BB_BUF0_RD_ADDR, 0x00);
            usRemainIdx = usPageNum * _USB_EP0_DATA_BUF_SIZE;
            for(ucIdx = 0; ucIdx < usRemainNum; ucIdx++)
            {
                g_pucUsbBillboardHidReport[usRemainIdx] = ScalerGetByte(P9A_03_BB_BUF0_RD_DATA);
                usRemainIdx++;
            }
        }
        else
        {
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            return;
        }
    }

    // Excute HID Report Vendor Define Command
    if((ucReportType == _USB_HID_REQUEST_REPORT_TYPE_OUTPUT) && (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE] == 0x40))
    {
        // Shars Vender Command with BillBoard_Vendor_Request
        ScalerUsbBillboardHidRequestSetReportVendorCommand();
    }
    else if(g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE] == 0xC0)
    {
        // Set_Report handling for pairs preceding Get_Report
        // Leave the Data Array unprocessed and let Get_Report handle its processing.
        // Directly send an ACK No Data response to the Host.
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, _FALSE);
    }
    else
    {
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//----------------------------------------------------------------
// Description  : USB HID Class Request - Get Report
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardHidRequestGetReport(void)
{
    BYTE ucReportID = 0;
    BYTE ucReportType = 0;
    WORD usInterface = 0;

    ucReportID = ScalerGetByte(P98_0A_HS_EP0_SETUP2);
    ucReportType = ScalerGetByte(P98_0B_HS_EP0_SETUP3);
    usInterface = (ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4);

    DebugMessageBB("U2-WT-ucReportID", ucReportID);
    DebugMessageBB("U2-WT-ucReportType", ucReportType);
    DebugMessageBB("U2-WT-usInterface", usInterface);

    ucReportID = ucReportID;
    usInterface = usInterface;

    // Excute HID Report Vendor Define Command
    if((ucReportType == _USB_HID_REQUEST_REPORT_TYPE_INPUT) && (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE] == 0xC0))
    {
        // Shars Vender Command with BillBoard_Vendor_Request
        ScalerUsbBillboardHidRequestGetReportVendorCommand();
    }
    else
    {
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//----------------------------------------------------------------
// Description  : USB HID Class Request - Get Report - Vendor Command Switch Case
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardHidRequestGetReportVendorCommand(void)
{
    DebugMessageBB("U2 Ven Request", g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE]);
    DebugMessageBB("U2 Ven wLENL", g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);
    DebugMessageBB("U2 Ven wLENH", g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1]);

    switch(g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_SUB_TYPE])
    {
        case _USB_VENDOR_GET_REGISTER_VALUE:
            ScalerUsbBillboardHidVendorGetRegisterByte();
            break;

        case _USB_VENDOR_READ_FROM_FLASH:
            ScalerUsbBillboardHidVendorReadFlash();
            break;

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
        case _USB_VENDOR_DUAL_BANK_PROCESS:
            ScalerUsbBillboardHidVendorDualBankProcess1();
            break;
#endif

        case _USB_VENDOR_GET_HW_CRC:
            ScalerUsbBillboardHidVendorCalculateCrc();
            break;

        case _USB_VENDOR_REALTEK_BB_HANDSHAKE:
            ScalerUsbBillboardHidVendorHandshake();
            break;

        // case _USB_VENDOR_READ_SYSEEPROM:
        // ScalerUsbBillboardVendorReadSyseeprom();
        // break;

        // case _USB_VENDOR_DEBUGMSG_EVENT_START:
        // ScalerUsbBillboardVendorDebugMsgEventStart();
        // break;

        // case _USB_VENDOR_DEBUGMSG_EVENT_FINISH:
        // ScalerUsbBillboardVendorDebugMsgEventFinish();
        // break;

        // case _USB_VENDOR_DEBUGMSG_START:
        // ScalerUsbBillboardVendorDebugMsgStart();
        // break;

        // case _USB_VENDOR_DEBUGMSG_END:
        // ScalerUsbBillboardVendorDebugMsgEnd();
        // break;

        // case _USB_VENDOR_DEBUGMSG_GET_VALUE:
        // ScalerUsbBillboardVendorDebugMsgGetValue();
        // break;

        // case _USB_VENDOR_DEBUGMSG_GET_STRING:
        // ScalerUsbBillboardVendorDebugMsgGetString();
        // break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//----------------------------------------------------------------
// Description  : USB HID Class Request - Set Report - Vendor Command Switch Case
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardHidRequestSetReportVendorCommand(void)
{
    DebugMessageBB("U2 Ven Request", g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_TYPE]);
    DebugMessageBB("U2 Ven wLENL", g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);
    DebugMessageBB("U2 Ven wLENH", g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1]);

    switch(g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_COMMAND_SUB_TYPE])
    {
        case _USB_VENDOR_SET_REGISTER_VALUE:
            ScalerUsbBillboardHidVendorSetRegisterByte();
            break;


        case _USB_VENDOR_WRITE_TO_FLASH:
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
            ScalerUsbBillboardHidVendorWriteFlash();

            // Background Program Function
            if(g_usUsbBillboardBackgroundProgramPauseTime != 0x00)
            {
                // Check Backgound Program Status
                ScalerUsbBillboardVendorCheckBackgroundProgram();
            }
#endif // End of #if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
            break;

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
        case _USB_VENDOR_FLASH_SECTOR_ERASE:

            ScalerUsbBillboardHidVendorSectorErase();

            break;
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
        case _USB_VENDOR_FLASH_BANK_ERASE:
            ScalerUsbBillboardHidVendorBankErase();
            break;
#endif
#endif

        case _USB_VENDOR_ISP_ENABLE:
            ScalerUsbBillboardHidVendorIspEnable();
            break;

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
        case _USB_VENDOR_DUAL_BANK_PROCESS:
            ScalerUsbBillboardHidVendorDualBankProcess1();
            break;
#endif

        // case _USB_VENDOR_WRITE_SYSEEPROM:
        // ScalerUsbBillboardVendorWriteSyseeprom();
        // break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//-------------------------------------------------------
// Description  : HID - USB Vendor Request - Set Register Byte
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerUsbBillboardHidVendorSetRegisterByte(void)
{
    BYTE ucIdx = 0;
    BYTE uc32ByteIdx = 0;
    WORD usFlag = 0x0000;

    DWORD ulLength = 0;
    DWORD ulRegisterAdd = 0x000000;
    DWORD ulPageNum = 0;
    DWORD ulRemainNum = 0;

    ulLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);
    ulRegisterAdd = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_16] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_18] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_19]);
    usFlag = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_14]);

    // 8 Bit Address Domain
    if((usFlag & _BIT1) == 0x00)
    {
        ulPageNum = ulLength / _USB_HID_ACCESS_08B_ADDRESS;
        ulRemainNum = ulLength % _USB_HID_ACCESS_08B_ADDRESS;

        for(ucIdx = 0; ucIdx < ulPageNum; ucIdx++)
        {
            if((usFlag & _BIT0) == _BIT0)
            {
                ScalerSetByte((WORD)ulRegisterAdd + ucIdx, g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + ucIdx]);
            }
            else
            {
                ScalerSetByte((WORD)ulRegisterAdd, g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA]);
            }
        }

        // [TBD]: Read the remaining
        if(ulRemainNum != 0)
        {
            ScalerSetByte((WORD)ulRegisterAdd + ulPageNum, g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + ulPageNum]);
        }
    }
    else // if ((usFlag & _BIT1) == _BIT1 : 32 Bit Address Domain
    {
        ulPageNum = ulLength / _USB_HID_ACCESS_32B_ADDRESS;
        ulRemainNum = ulLength % _USB_HID_ACCESS_32B_ADDRESS;

        for(ucIdx = 0; ucIdx < ulPageNum; ucIdx++)
        {
            if((usFlag & _BIT0) == _BIT0)
            {
                for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
                {
                    Scaler32SetByte(ulRegisterAdd, uc32ByteIdx, g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + ucIdx + uc32ByteIdx]);
                }
            }
            else
            {
                for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
                {
                    Scaler32SetByte(ulRegisterAdd, uc32ByteIdx, g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + ucIdx + uc32ByteIdx]);
                }
            }
        }

        // [TBD]: Read the remaining
        if(ulRemainNum != 0)
        {
            for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
            {
                Scaler32SetByte(ulRegisterAdd, uc32ByteIdx, g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + ulPageNum + uc32ByteIdx]);
            }
        }
    }

    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, _FALSE);
}

//-------------------------------------------------------
// Description  : HID - USB Vendor Request - Get Register Byte
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerUsbBillboardHidVendorGetRegisterByte(void)
{
    BYTE ucIdx = 0;
    BYTE uc32ByteIdx = 0;
    WORD usFlag = 0x0000;

    DWORD ulLength = 0;
    DWORD ulRegisterAdd = 0x000000;

    WORD usBBPageIdx = 0;
    DWORD ulBBPageNum = 0;
    DWORD ulBBRemainNum = 0;

    ulLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);
    ulRegisterAdd = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_16] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_18] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_19]);
    usFlag = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_14]);

    ulBBPageNum = ulLength / _USB_EP0_DATA_BUF_SIZE;
    ulBBRemainNum = ulLength % _USB_EP0_DATA_BUF_SIZE;

    // [TBD]: limit to one Byte set atm.
    // if(usLength > 1)
    // usLength = 1;

    // [TBD]:Read data from flash...
    // Set write fifo to transmit data to host
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(usBBPageIdx = 0; usBBPageIdx < ulBBPageNum; usBBPageIdx++)
    {
        // 8 Bit Address Domain
        if((usFlag & _BIT1) == 0x00)
        {
            for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx++)
            {
                if((usFlag & _BIT0) == _BIT0)
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte((WORD)ulRegisterAdd + usBBPageIdx + ucIdx));
                }
                else
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte((WORD)ulRegisterAdd + usBBPageIdx + ucIdx));
                }
            }
        }
        else // if ((usFlag & _BIT1) == _BIT1 : 32 Bit Address Domain
        {
            for(ucIdx = 0; ucIdx < _USB_EP0_DATA_BUF_SIZE; ucIdx += 4)
            {
                if((usFlag & _BIT0) == _BIT0)
                {
                    for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, Scaler32GetByte(ulRegisterAdd + usBBPageIdx + ucIdx, uc32ByteIdx));
                    }
                }
                else
                {
                    for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, Scaler32GetByte(ulRegisterAdd + usBBPageIdx + ucIdx, uc32ByteIdx));
                    }
                }
            }
        }

        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 0);
    }


    if(ulBBRemainNum == 0)
    {
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
    }
    else
    {
        // 8 Bit Address Domain
        if((usFlag & _BIT1) == 0x00)
        {
            for(ucIdx = 0; ucIdx < ulBBRemainNum; ucIdx++)
            {
                if((usFlag & _BIT0) == _BIT0)
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte((WORD)ulRegisterAdd + usBBPageIdx + ucIdx));
                }
                else
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ScalerGetByte((WORD)ulRegisterAdd + usBBPageIdx + ucIdx));
                }
            }
        }
        else // if ((usFlag & _BIT1) == _BIT1 : 32 Bit Address Domain
        {
            for(ucIdx = 0; ucIdx < ulBBRemainNum; ucIdx += 4)
            {
                if((usFlag & _BIT0) == _BIT0)
                {
                    for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, Scaler32GetByte(ulRegisterAdd + usBBPageIdx + ucIdx, uc32ByteIdx));
                    }
                }
                else
                {
                    for(uc32ByteIdx = 0; uc32ByteIdx < 0x04; uc32ByteIdx++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, Scaler32GetByte(ulRegisterAdd + usBBPageIdx + ucIdx, uc32ByteIdx));
                    }
                }
            }
        }

        ScalerSetByte(P98_06_HS_EP0_TX_BC, (WORD)ulBBRemainNum);
        ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1);
    }

    DebugMessageBB("U2 Check Get Add", ulRegisterAdd);
    DebugMessageBB("U2 Check Get Value", ScalerGetByte((WORD)ulRegisterAdd));
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Read Flash (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorReadFlash(void)
{
    DWORD ulLength = 0;
    WORD usBankID = 0;
    WORD usAddr = 0;

    BYTE pucUsbBillboardVendorDataBuf[_USB_VENDOR_CMD_MAX_LEN] = {0};
    // temp buffer for U2 TX test

    ulLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);
    usBankID = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_16]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17]));
    usAddr = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_18]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_19]));

    if(_USB_HID_REPORT_COUNT_LENGTH <= 288)
    {
        ScalerFlashRead(usBankID, (BYTE *)(DWORD)usAddr, (WORD)ulLength, pucUsbBillboardVendorDataBuf);
        ScalerUsbBillboardTransmtDataToHost((WORD)ulLength, pucUsbBillboardVendorDataBuf);
    }
    else
    {
        // For Read Flash temporarily Solution Report Count Length more than 256 Byte
        ScalerFlashRead(usBankID, (BYTE *)(DWORD)usAddr, ((WORD)ulLength / 4), pucUsbBillboardVendorDataBuf);
        ScalerUsbBillboardTransmtDataToHost(((WORD)ulLength / 4), pucUsbBillboardVendorDataBuf);
    }
}

//----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Calculate HW CRC Result
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardHidVendorCalculateCrc(void)
{
    // DWORD ulStartBank = (((DWORD)ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) + ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    // DWORD ulBankCnt = (((DWORD)ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) + ScalerGetByte(P98_0C_HS_EP0_SETUP4));
    BYTE ucCRC = 0;
    DWORD ulStartAddr = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_16] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_18] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_19]);
    DWORD ulEndAddr = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_20] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_21] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_22] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_23]);

    // DebugMessageBB("ulStartBank", ulStartBank);
    // DebugMessageBB("ulBankCnt", ulBankCnt);
    DebugMessageBB("ulStartAddr", ulStartAddr);
    DebugMessageBB("ulEndAddr", ulEndAddr);

    if(ScalerMcuFlashCRCCal(ulStartAddr, ulEndAddr, &ucCRC) == _TRUE)
    {
        DebugMessageBB("ucCRC", ucCRC);

        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucCRC);
        ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x01);
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    }
    else
    {
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//-----------------------------------------------------------------
// Description  : HID - USBVendor Request - Handshake (Host <-> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorHandshake(void)
{
    DWORD ulLength = 0;
    BYTE ucIdx = 0;

    ulLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    if(ulLength != g_pucUsbBillboardRTHandshake[0])
    {
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
        return;
    }
    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    for(ucIdx = 0; ucIdx < g_pucUsbBillboardRTHandshake[0]; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardRTHandshake[ucIdx + 1]);
    }
    ScalerSetByte(P98_06_HS_EP0_TX_BC, g_pucUsbBillboardRTHandshake[0]);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}

//-----------------------------------------------------------------
// Description  : HID - USBVendor Request - Isp Enable (Host -> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorIspEnable(void)
{
    g_bUsbBillboardIspEn = (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15]);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
    // Reset Background Flag While Disable ISP_Enable
    if(g_bUsbBillboardIspEn == _FALSE)
    {
        // Reset the flag for the release of BB_ISP_WhileLoop
        g_bUsbBillboardBackgroundProgramReleaseFlag = _FALSE;

        // Reset the BB Processing flag for Release Force Power Normal
        g_bUsbBillboardIspProcessing = _FALSE;
    }
    else
    {
        // Set Flag for Force Power Normal while BB ISP
        g_bUsbBillboardIspProcessing = _TRUE;
    }
#endif
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT0), (_BIT0));
}

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Write Flash (Host->Deivce)
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------
void ScalerUsbBillboardHidVendorWriteFlash(void)
{
    DWORD ulLength = 0;
    WORD usBankID = 0;
    WORD usAddr = 0;

    // For Report Count More than 288 Byte
    WORD usIdx = 0;
    WORD usWriteIdx = 0;
    WORD usWriteTimeIdx = 0;
    WORD usResWriteIdx = 0;

    ulLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);
    usBankID = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_16]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17]));
    usAddr = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_18]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_19]));

    DebugMessageBB("U2-WT-ulLength", ulLength);
    DebugMessageBB("U2-WT-usBankID", usBankID);
    DebugMessageBB("U2-WT-usAddr", usAddr);

    if(_USB_HID_REPORT_COUNT_LENGTH <= 288)
    {
        // Using Memory Copy to Reduce Excution Time
        memcpy((volatile BYTE xdata *)_HW_XRAM_ISP_MAPPING_ADDR_START, &g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA], _USB_VENDOR_CMD_MAX_LEN);

        // In HID-Flow, To Reduce Programing Time BB Shall Nor Control Flash SR
        ScalerFlashWritePageProgram(usBankID, usAddr, ulLength, _FALSE, _FALSE);
    }
    else
    {
        usWriteTimeIdx = ulLength / _USB_VENDOR_CMD_MAX_LEN;
        usResWriteIdx = ulLength % _USB_VENDOR_CMD_MAX_LEN;

        for(usWriteIdx = 0; usWriteIdx < usWriteTimeIdx; usWriteIdx++)
        {
            for(usIdx = 0; usIdx < _USB_VENDOR_CMD_MAX_LEN; usIdx++)
            {
                *((volatile BYTE *)(_HW_XRAM_ISP_MAPPING_ADDR_START + ((usWriteIdx * 256) + usIdx))) = g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + (usWriteIdx * 256) + usIdx];
            }

            ScalerFlashWritePageProgram(usBankID, (usAddr + (usWriteIdx * 256)), _USB_VENDOR_CMD_MAX_LEN, _FALSE, _FALSE);
        }

        if(usResWriteIdx != 0x00)
        {
            for(usIdx = 0; usIdx < usResWriteIdx; usIdx++)
            {
                *((volatile BYTE *)(_HW_XRAM_ISP_MAPPING_ADDR_START + ((usWriteTimeIdx * 256) + usIdx))) = g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA + (usWriteTimeIdx * 256) + usIdx];
            }

            ScalerFlashWritePageProgram(usBankID, (usAddr + (usWriteTimeIdx * 256)), usResWriteIdx, _FALSE, _FALSE);
        }
    }

    ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, _FALSE);
}
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)

//-----------------------------------------------------------------
// Description  : HID - USBVendor Request - Flash sector erase (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorSectorErase(void)
{
    WORD usBankID = 0;
    BYTE ucSectorID = 0;

    usBankID = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_14]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15]));
    ucSectorID = (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17]);

    ScalerFlashErasePage(usBankID, ucSectorID, _FALSE, _FALSE);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT0), (_BIT0));
}

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//-----------------------------------------------------------------
// Description  : HID - USBVendor Request - Flash sector erase (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorBankErase(void)
{
    WORD usBankID = 0;
    usBankID = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_14]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15]));

    ScalerFlashEraseBank(usBankID, _FALSE, _FALSE);

    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT0), (_BIT0));
}
#endif
#endif // End of #if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//-----------------------------------------------------------------
// Description  : HID - USBVendor Request - Dual Bank Process1 (record steup token packet info)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorDualBankProcess1(void)
{
    // Will Be Cleared By UserCommonDualBankUserHandler
    SET_USB_BB_ISP_REV_CMD_STATUS();
    // Will Be Cleared By When Complete a Transfer
    SET_USB_BB_ISP_OPCODE(_USB_VENDOR_DUAL_BANK_PROCESS);

    // Means That Isp Info from UserCommondualBankHandler has not been update During a Given Command
    if(GET_USB_BB_ISP_READY_FLAG() == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
    }

    switch((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15]))
    {
        case _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE);
            break;

        case  _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE);
            break;

        case _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE);
            break;

        case _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE:
            SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE);
            break;

        case _SCALER_BOOT_SWITCH_CODE_OP_CODE:
            ScalerUsbBillboardVendorSwitchCode();
            break;

        // Set Background Function : Program Flash Write Time Setting
        case _SCALER_BOOT_GET_ISP_BACKGROUND_WRITE_TIME_OP_CODE:
            ScalerUsbBillboardHidVendorSetBackgroundWriteTime();

            // Set BB Background Puase Timer No Need to Excute UserCommonDualBankUserHandler
            // Clear all the related MACRO
            CLR_USB_BB_ISP_REV_CMD_STATUS();
            CLR_USB_BB_ISP_OPCODE();
            CLR_USB_BB_ISP_SUB_OPCODE();
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//-----------------------------------------------------------------
// Description  : USBVendor Request - Dual Bank Process2 (reply isp info to host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorDualBankProcess2(void)
{
    switch((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_15]))
    {
        case _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE:
            ScalerUsbBillboardHidVendorGetIspStartBank();
            break;

        case _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE:
            ScalerUsbBillboardHidVendorGetIspKeyAddr();
            break;

        case  _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE:
            ScalerUsbBillboardHidVendorGetIspFlagAddr();
            break;

        case _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE:
            ScalerUsbBillboardHidVendorGetIspSignatureAddr();
            break;

        case _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE:
            ScalerUsbBillboardHidVendorGetVerifyCopyResult();
            break;

        case _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE:
            ScalerUsbBillboardHidVendorGetCurrentKeyAddr();
            break;

        case _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE:
            ScalerUsbBillboardHidVendorGetFWInfo();
            break;

        case _SCALER_BOOT_SWITCH_CODE_OP_CODE:
            ScalerUsbBillboardVendorSwitchCode();
            break;

        default:
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x0C Set Background Flash Write Time (Host -> Device)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorSetBackgroundWriteTime(void)
{
    // Set BB Background Puase Timer By Fetching Control_XFer_Byte[4][5]
    g_usUsbBillboardBackgroundProgramPauseTime = (((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_16]) << 8) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_17]));

    // Reset Billboard Background Program Excuting Counter
    g_usUsbBillboardBackgroundProgramExcuteTime = 0;

    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0) == _TRUE)
    {
        SET_USB_BB_ISP_SUB_OPCODE(_SCALER_BOOT_GET_ISP_BACKGROUND_WRITE_TIME_OP_CODE);
    }
    else
    {
        DebugMessageBB("Complete Command FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x01 GetIspStartBank (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetIspStartBank(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);


    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x02 GetIspKeyAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetIspKeyAddr(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x03 GetIspFlagAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetIspFlagAddr(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x04 GetIspSignatureAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetIspSignatureAddr(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x05 GetVerifyCopyResult (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetVerifyCopyResult(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x06 GetCurrentKeyAddr (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetCurrentKeyAddr(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}

//-----------------------------------------------------------------
// Description  : HID - USB Vendor Request - Dual Bank Process:0x07 GetFWInfo (Device -> Host)
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------
void ScalerUsbBillboardHidVendorGetFWInfo(void)
{
    WORD usLength = 0;
    BYTE ucIdx = 0;

    // In dual bank process, tool set (P98_0F_HS_EP0_SETUP7) fixed 0,so ucLength = (P98_0E_HS_EP0_SETUP6).
    // also tool setting ucLength will lower than _USB_EP0_DATA_BUF_SIZE(64)
    usLength = ((g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 3] << 24) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 2] << 16) + (g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN + 1] << 8) + g_pucUsbBillboardHidReport[_USB_HID_REPORT_START_BYTE_DATA_LEN]);

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);

    for(ucIdx = 0; ucIdx < usLength; ucIdx++)
    {
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbBillboardGetISPinfo[ucIdx]);
    }

    // In dual bank process,tool setting ucLength will lower than  _USB_EP0_DATA_BUF_SIZE(64)
    ScalerSetByte(P98_06_HS_EP0_TX_BC, usLength);

    // ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    // BB Send Data Success
    if(ScalerUsbBillboardCtrlXfer(_USB_CTRL_XFER_READ, 1) == _TRUE)
    {
        CLR_USB_BB_ISP_READY_FLAG();
        CLR_USB_BB_ISP_OPCODE();
        CLR_USB_BB_ISP_SUB_OPCODE();
    }
    else
    {
        DebugMessageBB("BB SEND DATA FAIL", GET_USB_BB_ISP_SUB_OPCODE());
    }
}
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

#if(_PORT_CTRL_RTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RTS PortController TypeC Alt Mode Related Info for Billboard Display
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Pointer of Billboard Info
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetAltModeRtsInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE *pucBillboardAltModeInfo)
{
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort);

    // Call Example : ScalerTypeC0PdGetAltModeBillboardInfo((BYTE *)(&Array))
    // Note : Array Size Should be _USB_MAX_ALTERNATE_MODE_NUM
    pucBillboardAltModeInfo = pucBillboardAltModeInfo;

    if(ScalerTypeCRxGetAltModeReady(enumInputPort) == _TRUE)
    {
        *pucBillboardAltModeInfo++ = 0x03;                                      // Alt Mode Status
    }
    else
    {
        *pucBillboardAltModeInfo++ = 0x00;                                      // Alt Mode Status
    }
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID);                               // Alt Mode SVID_Low
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID >> 8);                          // Alt Mode SVID_High
    *pucBillboardAltModeInfo++ = 0x00;                                          // Mode of SVID
    *pucBillboardAltModeInfo++ = _TYPE_C_RTS_DP_ALT_MODE_URL_INDEX;             // URL Index
    *pucBillboardAltModeInfo++ = 0x45;                                          // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = 0x00;                                          // Discover Mode Ack VDO1[15:8] : DP Tx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = ScalerTypeCRxGetPinAssignment(enumInputPort);  // Discover Mode Ack VDO1[23:16] : DP Rx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = 0x00;                                          // Discover Mode Ack VDO1[31:24] : Rsv
    *pucBillboardAltModeInfo++ = _TRUE;                                         // Current altmode active
}
#endif // End of #if(_PORT_CTRL_RTS_SUPPORT == _ON)

#if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User PortController TypeC Alt Mode Related Info for Billboard Display
// Input Value  : enumTypeCPcbPort (_D0_TYPE_C_PORT / _D1_TYPE_C_PORT...), Pointer of Billboard Info
// Output Value : None
//--------------------------------------------------
void ScalerUsbBillboardGetAltModeUserInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE *pucBillboardAltModeInfo)
{
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort);

    // Call Example : ScalerTypeC0PdGetAltModeBillboardInfo((BYTE *)(&Array))
    // Note : Array Size Should be _USB_MAX_ALTERNATE_MODE_NUM
    pucBillboardAltModeInfo = pucBillboardAltModeInfo;

    if(ScalerTypeCRxGetAltModeReady(enumInputPort) == _TRUE)
    {
        *pucBillboardAltModeInfo++ = 0x03;                                      // Alt Mode Status
    }
    else
    {
        *pucBillboardAltModeInfo++ = 0x00;                                      // Alt Mode Status
    }
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID);                               // Alt Mode SVID_Low
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID >> 8);                          // Alt Mode SVID_High
    *pucBillboardAltModeInfo++ = 0x00;                                          // Mode of SVID
    *pucBillboardAltModeInfo++ = _TYPE_C_USER_DP_ALT_MODE_URL_INDEX;            // URL Index
    *pucBillboardAltModeInfo++ = 0x45;                                          // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = 0x00;                                          // Discover Mode Ack VDO1[15:8] : DP Tx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = ScalerTypeCRxGetPinAssignment(enumInputPort);  // Discover Mode Ack VDO1[23:16] : DP Rx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = 0x00;                                          // Discover Mode Ack VDO1[31:24] : Rsv
    *pucBillboardAltModeInfo++ = _TRUE;                                         // Current altmode active
}
#endif // End of #if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)

#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Embbed U2 MAC Mux Switch
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsbBillboardMacMuxSwitch(void)
{
    if(GET_U2_PHY_SWITCH_PORT() == _U2_PHY_PORT_TO_HOST)
    {
        // Align AV10_to_DV10 LDO Isolation Status From BB
        if(ScalerGetBit(P64_7A_USB_PWR_ISO, _BIT0) == _BIT0)
        {
            ScalerSetBit(PDF_73_USB_PHY_LDO, ~_BIT2, _BIT2);
        }
        else
        {
            ScalerSetBit(PDF_73_USB_PHY_LDO, ~_BIT2, 0x00);
        }


        // Align LDO Status From BB
        if(ScalerGetBit(P64_78_USB_PHY_LDO, _BIT0) == _BIT0)
        {
            ScalerSetBit(PDF_73_USB_PHY_LDO, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(PDF_73_USB_PHY_LDO, ~_BIT0, 0x00);
        }

        // Set U2 Phy Port to Host,
        ScalerSetBit(PDF_73_USB_PHY_LDO, ~_BIT7, _BIT7);
    }
    else
    {
        // Align AV10_to_DV10 LDO Isolation Status From BB
        if(ScalerGetBit(PDF_73_USB_PHY_LDO, _BIT2) == _BIT2)
        {
            ScalerSetBit(P64_7A_USB_PWR_ISO, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(P64_7A_USB_PWR_ISO, ~_BIT0, 0x00);
        }

        // Align LDO Status From BB
        if(ScalerGetBit(PDF_73_USB_PHY_LDO, _BIT0) == _BIT0)
        {
            ScalerSetBit(P64_78_USB_PHY_LDO, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(P64_78_USB_PHY_LDO, ~_BIT0, 0x00);
        }

        // Set U2 Phy Port to BB,
        ScalerSetBit(PDF_73_USB_PHY_LDO, ~_BIT7, 0x00);
    }
}


//--------------------------------------------------
// Description  : USB Get Descriptor
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerUsbBillboardPhyInitial(void)
{
    //////////////////////////////////////////////////
    ////////////// Set Page-0 Reg ////////////////////
    //////////////////////////////////////////////////
    // Set 0x6462_00F5 = 0x15
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_F5_USB_PHY_CTR_REG_0D, 0x15);

    // Set 0x6462_00F7 = 0x0A
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_F7_USB_PHY_CTR_REG_0F, 0x0A);

    //////////////////////////////////////////////////
    ////////////// Set Page-1 Reg ////////////////////
    //////////////////////////////////////////////////
    // Set 0x6462_01E1 = 0x1C
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_E1_USB_PHY_CTR_REG_11, 0x1C);

    // Set 0x6462_01E2 = 0x06
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_E2_USB_PHY_CTR_REG_12, 0x06);

    // Set 0x6462_01E3 = 0x80
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_E3_USB_PHY_CTR_REG_13, 0x80);

    // Set 0x6462_01E5 = 0x00
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_E5_USB_PHY_CTR_REG_15, 0x00);

    // Set 0x6462_01E6 = 0x00
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_E6_USB_PHY_CTR_REG_16, 0x00);

    // Set 0x6462_01E7 = 0x00
    ScalerUsbBillboardSetPhyRegByte(_P64_62_PT_E7_USB_PHY_CTR_REG_17, 0x00);

    //////////////////////////////////////////////////
    ////////////// Set Page-2 Reg ////////////////////
    //////////////////////////////////////////////////
    // Set 0x6462_02E0 = 0x00
    // Address does not exist in Billboard
    ScalerUsbBillboardSetPhyRegByte(_PDF_62_PT_E0_USB_PHY_CTR_REG_20, 0x00);

    // Set 0x6462_02E1 = 0x00
    // Address does not exist in Billboard
    ScalerUsbBillboardSetPhyRegByte(_PDF_62_PT_E1_USB_PHY_CTR_REG_21, 0x00);
}


//----------------------------------------------------------------------------------------------------
// Description  : Write USB PHY Register Data by Byte Mode
// Input Value  : Register Address , Register Data
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbBillboardSetPhyRegByte(WORD usAddr, BYTE ucValue)
{
    ///////////////////////////////////////////////////
    // Phy Address Mapping [L/M][5][R/W][4][3][2][1][0]
    // Ex: Write 0x00E4
    // Ex: Read  0x00C4
    // Page Change : 0x00F4
    ///////////////////////////////////////////////////

    // Page select/change
    ScalerUsbBillboardSetPhyRegPage(usAddr);

    // Set USB PHY Register Value
    ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValue);   // data prepare
    ScalerUsbBillboardSetPhyRegAddr(usAddr);   // set address & write data to register
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB PHY Register Page Process
// Input Value  : Register Address
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbBillboardSetPhyRegPage(WORD usAddr)
{
    BYTE ucValueTemp = 0x00;

    ScalerUsbBillboardSetPhyRegAddr(((BYTE)(_P64_62_PT_F4_USB_PHY_CTR_REG_0C) & (~_BIT5)));   // BIT5=0 for read register ; BIT5=1 for write register
    DELAY_5US();
    ucValueTemp = ScalerGetByte(P64_63_BB_PHY_CTR_REG_02); // read 0x6462_00B4_0:vstatus (It's value of _PDF_62_PT_F4_USB_PHY_CTR_REG_0C)

    // Set USB PHY Register Page
    if(((ucValueTemp & (_BIT6 | _BIT5)) == 0x00) && ((usAddr & (_BIT9 | _BIT8)) == _BIT8))   // current page=0,target page=1
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT5);   // select USB PHY Page1
        ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
        ScalerUsbBillboardSetPhyRegAddr(_P64_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == 0x00) && ((usAddr & (_BIT9 | _BIT8)) == _BIT9))   // current page=0,target page=2
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT6);   // select USB PHY Page2
        ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
        ScalerUsbBillboardSetPhyRegAddr(_P64_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT5) && ((usAddr & (_BIT9 | _BIT8)) == 0x0000))   // current page=1,target page=0
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5)));   // select USB PHY Page0
        ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
        ScalerUsbBillboardSetPhyRegAddr(_P64_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT5) && ((usAddr & (_BIT9 | _BIT8)) == _BIT9))   // current page=1,target page=2
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT6);   // select USB PHY Page2
        ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
        ScalerUsbBillboardSetPhyRegAddr(_P64_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT6) && ((usAddr & (_BIT9 | _BIT8)) == 0x0000))   // current page=2,target page=0
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5)));   // select USB PHY Page0
        ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
        ScalerUsbBillboardSetPhyRegAddr(_P64_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else if(((ucValueTemp & (_BIT6 | _BIT5)) == _BIT6) && ((usAddr & (_BIT9 | _BIT8)) == _BIT8))   // current page=2,target page=1
    {
        ucValueTemp = (ucValueTemp & (~(_BIT6 | _BIT5))) | (_BIT5);   // select USB PHY Page1
        ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
        ScalerUsbBillboardSetPhyRegAddr(_P64_62_PT_F4_USB_PHY_CTR_REG_0C);   // set address & write data to register
    }
    else
    {
        // Don't need to change PHY page
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB PHY Register Address Process
// Input Value  : Register Address
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbBillboardSetPhyRegAddr(WORD usAddr)
{
    BYTE ucAddrTemp = 0;
    BYTE ucValueTemp = 0;

    ///////////////////////////////////////////////////////////////////
    // Set U2 Phy Register Example
    // // SetPhyRegAddr
    // 4, _AUTOINC, 0x9F, 0x64,
    // 4, _AUTOINC, 0x62, 0xA5, // Write 0x6462(vstatus) = 0xA5
    // //
    // 4, _AUTOINC, 0x61, 0x14, // set vcontrol = ADDR[3:0]
    // 4, _AUTOINC, 0x61, 0x04, // set vcontrolloadm = LOAD
    // //DELAY(1)
    // 4, _AUTOINC, 0x61, 0x14, // set vcontrolloadm = NOP
    // //
    // 4, _AUTOINC, 0x61, 0x1E, // set vcontrol = ADDR[7:4]
    // 4, _AUTOINC, 0x61, 0x0E, // set vcontrolloadm = LOAD
    // //DELAY(1)
    // 4, _AUTOINC, 0x61, 0x1E, // set vcontrolloadm = NOP
    ///////////////////////////////////////////////////////////////////

    for(ucValueTemp = 0; ucValueTemp < 4; ucValueTemp++)
    {
        if(ucValueTemp == 0)
        {
            ucAddrTemp = (BYTE)(usAddr & 0x000F);
            ScalerSetByte(P64_61_BB_PHY_CTR_REG_00, (0x10 | ucAddrTemp));// |0x10: bit4(vcontrolloadm) 1 (NOP) + Address[3:0]Ready
        }
        else if(ucValueTemp == 1)
        {
            ucAddrTemp = (BYTE)(usAddr & 0x000F);
            ScalerSetByte(P64_61_BB_PHY_CTR_REG_00, (0x00 | ucAddrTemp));// |0x00: bit4(vcontrolloadm) 0 (LOAD) + Address[3:0]Ready
        }
        else if(ucValueTemp == 2)
        {
            ucAddrTemp = (BYTE)(usAddr & 0x00F0) >> 4;
            ScalerSetByte(P64_61_BB_PHY_CTR_REG_00, (0x10 | ucAddrTemp));// |0x10: bit4(vcontrolloadm) 1 (NOP) + Address[7:4]Ready
        }
        else
        {
            ucAddrTemp = (BYTE)(usAddr & 0x00F0) >> 4;
            ScalerSetByte(P64_61_BB_PHY_CTR_REG_00, (0x00 | ucAddrTemp));// |0x00: bit4(vcontrolloadm) 0 (LOAD) + Address[7:4]Ready
        }

        DELAY_5US();   // wait for reg access ready
    }
}


//----------------------------------------------------------------------------------------------------
// Description  : Set USB PHY Register Data by Bit Mode
// Input Value  : Register Address , "AND" Bit No. , "OR" Bit No.
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsbBillboardSetPhyRegBitField(WORD usAddr, DWORD ulAnd, BYTE ucOr)
{
    BYTE ucValueTemp = 0;

    // Set USB PHY Register Value
    ucValueTemp = ScalerUsbBillboardGetPhyRegByte(usAddr);
    ucValueTemp = (ucValueTemp & (BYTE)ulAnd) | (ucOr);
    ScalerSetByte(P64_62_BB_PHY_CTR_REG_01, ucValueTemp);   // data prepare
    ScalerUsbBillboardSetPhyRegAddr(usAddr);   // set address & write data to register
}

//----------------------------------------------------------------------------------------------------
// Description  : Read USB PHY Register Data by Byte Mode
// Input Value  : Register Address
// Output Value : Register Data
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbBillboardGetPhyRegByte(WORD usAddr)
{
    BYTE ucAddrTemp = 0x00;
    BYTE ucValueTemp = 0x00;

    ScalerUsbBillboardSetPhyRegPage(usAddr);

    // Get USB PHY Register Value
    ucAddrTemp = (BYTE)(usAddr & (~_BIT5));
    ScalerUsbBillboardSetPhyRegAddr(ucAddrTemp);
    DELAY_5US();
    ucValueTemp = ScalerGetByte(P64_63_BB_PHY_CTR_REG_02);

    return ucValueTemp;
}


//----------------------------------------------------------------------------------------------------
// Description  : Get USB PHY Register Data by Bit Mode
// Input Value  : Register Address, ucAnd
// Output Value : None
//----------------------------------------------------------------------------------------------------
BYTE ScalerUsbBillboardGetPhyRegBitField(WORD usAddr, BYTE ucAnd)
{
    BYTE ucValueTemp = 0;

    // Set USB PHY Register Value
    ucValueTemp = ScalerUsbBillboardGetPhyRegByte(usAddr);
    ucValueTemp = (ucValueTemp & ucAnd);
    return ucValueTemp;
}
#endif // End of #if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
#endif // End of #if(_BB_SUPPORT == _ON)
