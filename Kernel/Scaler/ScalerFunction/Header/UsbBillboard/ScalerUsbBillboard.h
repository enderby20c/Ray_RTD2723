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
// ID Code      : ScalerUsbBillboard.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB_BILLBOARD_H__
#define __SCALER_USB_BILLBOARD_H__

//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************
#define _USB_EP0_DATA_BUF_SIZE                           0x40
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
#define _USB_HID_ACCESS_32B_ADDRESS                      0x20
#define _USB_HID_ACCESS_08B_ADDRESS                      0x08
#endif

#define _USB_31_SS_SUPPORT                               _OFF

#define _USB_HUB_SS_PID_H_                               0x04
#define _USB_HUB_SS_PID_L_                               0x00
#define _USB_HUB_HS_PID_H_                               0x54
#define _USB_HUB_HS_PID_L_                               0x00

#define _USB_FW_MAIN_VER_                                0x01
#define _USB_FW_SUB_VER_                                 0x00
#define _USB_DESC_SIZE_DEV                               0x12
#define _USB_DESC_SIZE_CONF                              0x09
#define _USB_DESC_SIZE_INTF                              0x09
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
#define _USB_DESC_SIZE_HID                               0x09
#endif
#define _USB_DESC_SIZE_EP                                0x07
#define _USB_DESC_SIZE_EP_COMPANION                      0x06
#define _USB_DESC_SIZE_CPLS                              0x04
#define _USB_DESC_SIZE_BOS                               0x05
#define _USB_DESC_SIZE_USB2_EXTENSION                    0x07

#if(_USB_31_SS_SUPPORT == _ON)
#define _USB_DESC_SIZE_SUPERSPEED_USB                    0x0A
#define _USB_BOS_DEVICEACPS_NUM                          0x04
#define _USB_BB_CAP_LEN_OFFSEET_IN_BOS                   0x2A
#define _USB_BB_CAP_ALTMODE_NUM_OFFSET_IN_BOS            0x2E
#define _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_1_4     0x32
#define _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_5_8     0x33
#else
#define _USB_DESC_SIZE_SUPERSPEED_USB                    0x00
#define _USB_BOS_DEVICEACPS_NUM                          0x03
#define _USB_BB_CAP_LEN_OFFSEET_IN_BOS                   0x20 // 0x2A - 0x0A(_USB_DESC_SIZE_SUPERSPEED_USB)
#define _USB_BB_CAP_ALTMODE_NUM_OFFSET_IN_BOS            0x24 // 0x2e - 0x0A(_USB_DESC_SIZE_SUPERSPEED_USB)
#define _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_1_4     0x28 // 0x32 - 0x0A(_USB_DESC_SIZE_SUPERSPEED_USB)
#define _USB_BB_CAP_ALTMODE_STATUS_OFFSET_IN_BOS_5_8     0x29 // 0x33 - 0x0A(_USB_DESC_SIZE_SUPERSPEED_USB)
#endif

#define _USB_DESC_SIZE_CONTAINER_ID                      0x14
#define _USB_DESC_SIZE_BILLBOARD_CAP                     0x2C
#define _USB_DESC_SIZE_ALTERNATE_MODE                    0x04
#define _USB_DESC_SIZE_BILLBOARD_ALTMODE_CAP             0x08

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
#define _USB_DESC_SIZE_CONF_TOTAL                        (_USB_DESC_SIZE_CONF + _USB_DESC_SIZE_INTF + _USB_DESC_SIZE_HID + _USB_DESC_SIZE_EP)
#else
#define _USB_DESC_SIZE_CONF_TOTAL                        (_USB_DESC_SIZE_CONF + _USB_DESC_SIZE_INTF)
#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)

// Could Support (Dp AltMode + Lenovo AltMode) so far
#define _USB_MAX_ALTERNATE_MODE_NUM                      ((_DX_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) +\
                                                          (_DX_TYPE_C_EXT_DP_ALT_MODE_SUPPORT == _ON) +\
                                                          (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))

#define _USB_BB_BOS_DESC_FIRST_PART_LEN                  (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_SUPERSPEED_USB + _USB_DESC_SIZE_CONTAINER_ID + _USB_DESC_SIZE_BILLBOARD_CAP)
#define _USB_BB_BOS_DESC_TOTAL_LEN_INIT                  (_USB_BB_BOS_DESC_FIRST_PART_LEN + _USB_MAX_ALTERNATE_MODE_NUM * (_USB_DESC_SIZE_ALTERNATE_MODE + _USB_DESC_SIZE_BILLBOARD_ALTMODE_CAP))

#define _USB_CTRL_XFER_NO_DATA                           0x00
#define _USB_CTRL_XFER_READ                              0x01
#define _USB_CTRL_XFER_WRITE_DATA_STAGE                  0x02
#define _USB_CTRL_XFER_WRITE_STATUS_STAGE                0x03

// Standard Request based on the USB 1.0 specification
#define _USB_REQUEST_GET_STATUS                          0x00
#define _USB_REQUEST_CLEAR_FEATURE                       0x01
#define _USB_REQUEST_SET_FEATURE                         0x03
#define _USB_REQUEST_SET_ADDRESS                         0x05
#define _USB_REQUEST_GET_DESCRIPTOR                      0x06
#define _USB_REQUEST_SET_DESCRIPTOR                      0x07
#define _USB_REQUEST_GET_CONFIGURATION                   0x08
#define _USB_REQUEST_SET_CONFIGURATION                   0x09
#define _USB_REQUEST_GET_INTERFACE                       0x0A
#define _USB_REQUEST_SET_INTERFACE                       0x0B
#define _USB_REQUEST_SYNC_FRAME                          0x0C
#define _USB_REQUEST_SET_SEL                             0x30
#define _USB_REQUEST_ISOCH_DELAY                         0x31


// Define the 8-bytes Data location of Setup Packet
#define _USB_REQUEST_TYPE_MASK                           0x60
#define _USB_STANDARD_REQUEST                            0x00
#define _USB_CLASS_REQUEST                               0x20
#define _USB_VENDOR_REQUEST                              0x40
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
#define _USB_CLASS_DESCRIPTOR_TYPE_MASK                  0x0F
#define _USB_CLASS_DESCRIPTOR_TYPE_HID                   0x01
// #define _USB_CLASS_DESCRIPTOR_TYPE_REPORT                0x02
// #define _USB_CLASS_DESCRIPTOR_TYPE_PHYSICAL              0x03
#endif
#define _USB_REQUEST_RECIPIENT_MASK                      0x1F
#define _USB_REQUEST_RECIPIENT_DEVICE                    0x00
#define _USB_REQUEST_RECIPIENT_INTERFACE                 0x01
#define _USB_REQUEST_RECIPIENT_ENDPOINT                  0x02
#define _USB_REQUEST_RECIPIENT_PORT                      0x03

#define _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_IN         0x80
#define _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_OUT        0x00
#define _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN          0x81

// standard feature selectors
#define _USB_ENDPOINT_HALT                               0x00   // endpoint
#define _USB_DEVICE_REMOTE_WAKEUP                        0x01   // device
#define _USB_TEST_STATE                                  0x02   // device

// HS_EP0_IRQ           --  0x9800
#define _HS_EP0_SETUP_PKT_RECEIVE_INT                    0x01
#define _HS_EP0_VENDOR_CMD_PKT_RECEIVE_INT               0x02
#define _HS_EP0_GET_DESCRI_PKT_RECEIVE_INT               0x04
#define _HS_EP0_SEND_PKT_DONE_INT                        0x08
#define _HS_EP0_RECEIVE_PKT_DONE_INT                     0x10

// HS_EP0_IRQ_EN        --  0x9801
#define _HS_EP0_SETUP_PKT_RECEIVE_INT_EN                 0x01
#define _HS_EP0_VENDOR_CMD_PKT_RECEIVE_INT_EN            0x02
#define _HS_EP0_GET_DESCRI_PKT_RECEIVE_INT_EN            0x04
#define _HS_EP0_SEND_PKT_DONE_INT_EN                     0x08
#define _HS_EP0_RECEIVE_PKT_DONE_INT_EN                  0x10

// HS_EP0_CTRL          --  0x9804
#define _USB_EP0_AUTO_TX_STATUS_HS                       0x10
#define _USB_EP0_REC_PKT_EN                              0x08
#define _USB_EP0_SEND_PKT_EN                             0x04
#define _USB_EP0_STALL                                   0x02
#define _USB_EP0_STATUS_HS_EN                            0x01

// HS_USP_STS           --  0x6404
#define _USB_HS_USP_SPEED                                0x01
#define _USB_HS_USP_SUSPEND                              0x02
#define _USB_HS_USP_RESUME                               0x04
#define _USB_HS_USP_CONFIG                               0x08

// HS_DEV_STATUS        --  0x6452
#define _USB_DEV_REMOTE_WAKEUP_EN                        0x01
#define _USB_DEV_EPB_STALL                               0x02
#define _USB_DEV_SELF_POWER                              0x04

// HS_USP_TEST          --  0x6453
#define _USB_TEST_J                                      0x01
#define _USB_TEST_K                                      0x02
#define _USB_TEST_PACKET                                 0x04
#define _USB_TEST_SE0_NAK                                0x08
#define _USB_TEST_MODE                                   0x10

// HS_DEV_ADDR          --  0x6454
#define _USB_DEV_ADDR_VALID                              0x80
#define _USB_DEV_ADDR_MASK                               0x7F

// Standard Descriptor Type (Table 9-5)
#define _USB_DEVICE_DESCRIPTOR_TYPE                      0x01
#define _USB_CONFIGURATION_DESCRIPTOR_TYPE               0x02
#define _USB_STRING_DESCRIPTOR_TYPE                      0x03
#define _USB_INTERFACE_DESCRIPTOR_TYPE                   0x04
#define _USB_ENDPOINT_DESCRIPTOR_TYPE                    0x05
#define _USB_INTERFACE_POWER_DESCRIPTOR_TYPE             0x08
#define _USB_OTG_DESCRIPTOR_TYPE                         0x09
#define _USB_DEBUG_DESCRIPTOR_TYPE                       0x0A
#define _USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE       0x0B
#define _USB_BOS_DESCRIPTOR_TYPE                         0x0F
#define _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE           0x10
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
#define _USB_REPORT_DESCRIPTOR_TYPE                      0x22
#endif
#define _USB_EP_COMPANION_DESCRIPTOR_TYPE                0x30


#define _USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE            0x06
#define _USB_OTHER_SPEED_CONFIGURATION_TYPE              0x07
#define _USB_POWER_DESCRIPTOR_TYPE                       0x08

// Device Capability Type defintion for BOS Descriptor
#define _USB_EXTENSION_TYPE                              0x02
#define _USB_SUPERSPEED_USB_TYPE                         0x03
#define _USB_CONTAINER_ID_TYPE                           0x04
#define _USB_BILLBOARD_TYPE                              0x0D
#define _USB_BILLBOARD_ALTMODE_TYPE                      0x0F

// string descriptor index
#define _USB_INDEX0                                      0x00

#define _USB_INDEX1                                      0x21
#define _USB_INDEX2                                      0x22
#define _USB_INDEX3                                      0x23
#define _USB_INDEX4                                      0x24
#define _USB_INDEX5                                      0x25

#define _USB_BB_INDEX0                                   0x10
#define _USB_BB_INDEX1                                   0x11
#define _USB_BB_INDEX2                                   0x12
#define _USB_BB_INDEX3                                   0x13

#define _USB_RT_HUB_STRING_INDEX0                        0x34   // "R"
#define _USB_RT_HUB_STRING_INDEX1                        0x36   // "T"

// BB Capability Descriptor
#define _TYPE_C_BILLBOARD_URL_INDEX_IADDTIONALINFO       0x40

// Device status
#define _USB_DEV_STATUS_BUS_POWERED                      0x00
#define _USB_DEV_STATUS_SELF_POWERED                     0x01
#define _USB_DEV_STATUS_REMOTE_WAKEUP                    0x02
#define _USB_DEV_STATUS_U1_EN                            0x04
#define _USB_DEV_STATUS_U2_EN                            0x08
#define _USB_DEV_STATUS_LTM_EN                           0x10

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
#define _USB_HID_REQUEST_REPORT_TYPE_INPUT               0x01
#define _USB_HID_REQUEST_REPORT_TYPE_OUTPUT              0x02
#define _USB_HID_REQUEST_REPORT_TYPE_FEATURE             0x03
#endif

/////////////////////////////
////////Vendor Request///////
/////////////////////////////

//Scaler Debug
#define _USB_VENDOR_SET_REGISTER_VALUE                   0x01
#define _USB_VENDOR_GET_REGISTER_VALUE                   0x02
#define _USB_VENDOR_WRITE_SYSEEPROM                      0x03
#define _USB_VENDOR_READ_SYSEEPROM                       0x04

//Scaler Debug Message
#define _USB_VENDOR_DEBUGMSG_EVENT_START                 0x30
#define _USB_VENDOR_DEBUGMSG_EVENT_FINISH                0x31
#define _USB_VENDOR_DEBUGMSG_START                       0x32
#define _USB_VENDOR_DEBUGMSG_END                         0x33
#define _USB_VENDOR_DEBUGMSG_GET_VALUE                   0x34
#define _USB_VENDOR_DEBUGMSG_GET_STRING                  0x35

//ISP
#define _USB_VENDOR_WRITE_TO_FLASH                       0x40
#define _USB_VENDOR_READ_FROM_FLASH                      0x41
#define _USB_VENDOR_FLASH_SECTOR_ERASE                   0x42
#define _USB_VENDOR_FLASH_BANK_ERASE                     0x43
#define _USB_VENDOR_ISP_ENABLE                           0x44
// #define _USB_VENDOR_DUAL_BANK_PROCESS                 0x45
#define _USB_VENDOR_GET_HW_CRC                           0x4B

//Relatek Handshake
#define _USB_VENDOR_REALTEK_BB_HANDSHAKE                 0x50

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
/////////////////////////////
//////HID Class Request//////
/////////////////////////////

// HID Requset
#define _USB_HID_REQUEST_GET_REPORT                      0x01
#define _USB_HID_REQUEST_GET_IDLE                        0x02 // No Used
#define _USB_HID_REQUEST_GET_PROTOCOL                    0x03 // No Used
// Device Class Definition for HID Spec.Reserved            0x04 ~ 0x08
#define _USB_HID_REQUEST_SET_REPORT                      0x09
#define _USB_HID_REQUEST_SET_IDLE                        0x0A // No Used - But Can Be Test
#define _USB_HID_REQUEST_SET_PROTOCOL                    0x0B // No Used

#define _USB_HID_REPORT_COUNT_LENGTH                     288 // 0x120
#define _USB_HID_REPORT_COUNT_PAGE_NUM                   (_USB_HID_REPORT_COUNT_LENGTH / _USB_EP0_DATA_BUF_SIZE)
#define _USB_HID_REPORT_COUNT_REMAIN                     (_USB_HID_REPORT_COUNT_LENGTH % _USB_EP0_DATA_BUF_SIZE)
#define _USB_HID_REPORT_COUNT_HI_BYTE                    0x01
#define _USB_HID_REPORT_COUNT_LO_BYTE                    0x20
// Report Header / Data Start Byte
#define _USB_HID_REPORT_START_BYTE_SIGNATURE             0x00
#define _USB_HID_REPORT_START_BYTE_DATA_LEN              0x04
#define _USB_HID_REPORT_START_BYTE_COMMAND_TYPE          0x0C
#define _USB_HID_REPORT_START_BYTE_COMMAND_SUB_TYPE      0x0D
#define _USB_HID_REPORT_START_BYTE_14                    0x0E
#define _USB_HID_REPORT_START_BYTE_15                    0x0F
#define _USB_HID_REPORT_START_BYTE_16                    0x10
#define _USB_HID_REPORT_START_BYTE_17                    0x11
#define _USB_HID_REPORT_START_BYTE_18                    0x12
#define _USB_HID_REPORT_START_BYTE_19                    0x13
#define _USB_HID_REPORT_START_BYTE_20                    0x14
#define _USB_HID_REPORT_START_BYTE_21                    0x15
#define _USB_HID_REPORT_START_BYTE_22                    0x16
#define _USB_HID_REPORT_START_BYTE_23                    0x17
#define _USB_HID_REPORT_START_BYTE_DATA                  0x20

#endif // End of #if(_USB_BB_HID_TYPE_SUPPORT == _ON)
///////////////////////////////////////
////////DUAL BANK PROCESS OPCODE///////
///////////////////////////////////////

#define _USB_SVID_MAX_NUM                                12   // Now default support 12 SVID number
#define _USB_VENDOR_CMD_MAX_LEN                          256  // Now default support 12 SVID number
#define _USB_MCM_FLASH_USB_PIDVID                        0xD000
#define _USB_MCM_FLASH_USB_MANUFACTORY                   0xD008
#define _USB_MCM_FLASH_USB_PRODUCT                       0xD028


#define _IMANUFACTUR_SIZE                                62 // total 31 char
#define _IPRODUCT_SIZE                                   62 // total 31 char

//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************
#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
//--------------------     HID Descriptor    -------------------------//
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType from USB-IF
    BYTE ucHidClassSpecLsb;         // Identifying the HID Class Specification release(LSB)
    BYTE ucHidClassSpecMsb;         // Identifying the HID Class Specification release(MSB)
    BYTE ucCountryCode;             // bCountryCode
    BYTE ucNumDescriptor;           // Number of class descriptors
    BYTE ucReportDescriptorType;    // bDescriptorType from HID spec
    BYTE ucSizeReportDescriptorLsb; // The total size of the Report descriptor(LSB)
    BYTE ucSizeReportDescriptorMsb; // The total size of the Report descriptor(MSB)
} StructUsbHidDescriptor;

//--------------------     EndPoint Descriptor    -------------------------//
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType from USB-IF
    BYTE ucEndpointAddress;         // bEndpointAddress
    BYTE ucAttributes;              // bmAttributes
    BYTE ucPacketSizeLsb;           // wMaxPacketSize_LSB
    BYTE ucPacketSizeMsb;           // wMaxPacketSize_MSB
    BYTE ucInterval;                // bInterval(INT EP, HS is 0x80)
} StructUsbEndpointDescriptor;

//-------------------     String Descriptor     ----------------------------//
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucLangID0_Lo;              // LangID[0] LSB
    BYTE ucLangID0_Hi;              // LangID[0] MSB
} StructUsbStringDescriptor;
#endif

// These descriptors should follow the Billboard Capability Descriptor,
// Adding the N descriptors increases the BOS Descriptor wTotalLength by N*8 and bNumDeviceCaps by N.
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucDevCapabilityType;       // bDevCapabilityType
    BYTE ucIndex;                   // bIndex
    BYTE pucAlternateModeVdo[4];    // bAlternateModeVdo
} StructUsbBBAltModeCapabilityDescriptor;

typedef struct
{
    BYTE ucAltModeStauts;
    BYTE ucSVID_LO;
    BYTE ucSVID_HI;
    BYTE ucMode;
    BYTE ucStringIndex;
    BYTE ucdwAlternateModeVdo_Byte0;
    BYTE ucdwAlternateModeVdo_Byte1;
    BYTE ucdwAlternateModeVdo_Byte2;
    BYTE ucdwAlternateModeVdo_Byte3;
    BYTE ucCurAltModeActive;
} StructTypeCBillboardInfo;

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
typedef struct
{
    BYTE ucLength;
    BYTE ucDescriptorType;
    BYTE ucSizeLsb;
    BYTE ucSizeMsb;
    BYTE ucNumDeviceCaps;
} StructUsbBosDescriptor;

typedef struct
{
    BYTE ucLength;
    BYTE ucDescriptorType;      // 0x10
    BYTE ucDescriptorCapType;   // 0x02
    BYTE ucData0;
    BYTE ucData1;
    BYTE ucData2;
    BYTE ucData3;
} StructUsbU2ExtensionDesp;


typedef struct
{
    BYTE ucUsagePage0;
    BYTE ucUsagePage1;
    BYTE ucUsagePage2;
    // 0x06,0xDA,0xFF,             // Usage Page (vender define)
    BYTE ucUsage0;
    BYTE ucUsage1;
    // 0x09,0xDA,                  // Usage
    BYTE ucHidCollection0;
    BYTE ucHidCollection1;
    // 0xA1,0x01,                  // Collection
    BYTE ucHidMin0;
    BYTE ucHidMin1;
    // 0x15,0x80,                  // Logical min
    BYTE ucHidMax0;
    BYTE ucHidMax1;
    // 0x25,0x7F,                  // Logical Max
    // Vendor CMD Output
    BYTE ucOutReportSize0;
    BYTE ucOutReportSize1;
    // 0x75,0x08,                  // Report size (bits)
    BYTE ucOutReportCount0;
    BYTE ucOutReportCount1;
    BYTE ucOutReportCount2;
    // 0x95,0x01, 0x20,            // Report Count = 288, ucOutReportCount0 / 1 /2
    // Report Count bSize: 0x10, bType: Global(0x01), bTag: Report Count
    BYTE ucOutUsage0;
    BYTE ucOutUsage1;
    // 0x09,0xD1,                  //
    // 0x91,0x02,                  //
    BYTE ucOut0;
    BYTE ucOut1;
    // Vendor CMD Input
    BYTE ucInReportSize0;
    BYTE ucInReportSize1;
    // 0x75,0x08,                  // Report size (bits)
    BYTE ucInReportCount0;
    BYTE ucInReportCount1;
    BYTE ucInReportCount2;
    // 0x95,0x01, 0x20,            // Report Count = 288, ucOutReportCount0 / 1 /2
    // Report Count bSize: 0x10, bType: Global(0x01), bTag: Report Count
    BYTE ucInUsage0;
    BYTE ucInUsage1;
    // 0x09,0xD2,                  //
    BYTE ucIn0;
    BYTE ucIn1;
    // 0x81,0x02,                  //
    BYTE ucEnd;
    // 0xC0                       // HID collection end
} StructHidReportDescriptor;

typedef struct
{
    StructUsbBosDescriptor          stUsbBosDescriptor;
    StructUsbU2ExtensionDesp        stUsbU2ExtensionDesp;
} StructHidBosDescriptor;

//====================     USB Complete Descriptor     =====================//
//No Used in S4
typedef struct
{
    // No Used in S4 // StructUsbConfigDescriptor       stUsbConfigureDescriptor;
    // No Used in S4 // StructUsbInterfaceDescriptor    stUsbInterfaceDescriptor;
    StructUsbHidDescriptor          stUsbHidDescriptor;
    StructUsbEndpointDescriptor     stUsbEndpointDescriptor;
} StructUsbBBConfigDescriptor;
#endif


#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#define GET_USB_BB_USER_ENABLE_FLAG()                    (g_bUsbBillboardProgramUserEnableFlag)
#define SET_USB_BB_USER_ENABLE_FLAG()                    (g_bUsbBillboardProgramUserEnableFlag = _TRUE)
#define CLR_USB_BB_USER_ENABLE_FLAG()                    (g_bUsbBillboardProgramUserEnableFlag = _FALSE)
#endif
#endif
//****************************************************************************************************
// VARIABLE EXTERN
//****************************************************************************************************


//****************************************************************************************************
// FUNCTION EXTERN
//****************************************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
extern void ScalerUsbBillboardIntHandler_EXINT0(void);
extern void ScalerUsbBillboardStandardRequest(void);
extern void ScalerUsbBillboardVendorSetRegisterByte(void);
extern void ScalerUsbBillboardVendorGetRegisterByte(void);
extern void ScalerUsbBillboardVendorReadFlash(void);

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern void ScalerUsbBillboardVendorWriteFlash(void);
#endif
extern void ScalerUsbBillboardVendorSectorErase(void);
#endif
extern void ScalerUsbBillboardVendorBankErase(void);
extern void ScalerUsbBillboardVendorIspEnable(void);
extern void ScalerUsbBillboardVendorHandshake(void);
extern void ScalerUsbBillboardVendorCalculateCrc(void);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern void ScalerUsbBillboardVendorDualBankProcess1(void);
extern void ScalerUsbBillboardVendorDualBankProcess2(void);

extern void ScalerUsbBillboardVendorGetIspStartBank(void);
extern void ScalerUsbBillboardVendorGetIspKeyAddr(void);
extern void ScalerUsbBillboardVendorGetIspFalgAddr(void);
extern void ScalerUsbBillboardVendorGetIspSignatureAddr(void);
extern void ScalerUsbBillboardVendorGetVerifyCopyResult(void);
extern void ScalerUsbBillboardVendorGetCurrentKeyAddr(void);
extern void ScalerUsbBillboardVendorGetFWInfo(void);
extern void ScalerUsbBillboardVendorSwitchCode(void);
// Background Program Function Define
extern void ScalerUsbBillboardVendorSetBackgroundWriteTime(void);
extern void ScalerUsbBillboardVendorCheckBackgroundProgram(void);
// Custom BillBoard Command For User
extern void ScalerUsbBillboardCustomSetCommand(void);
#endif

extern void ScalerUsbBillboardVendorDebugMsgEventStart(void);
extern void ScalerUsbBillboardVendorDebugMsgEventFinish(void);
extern void ScalerUsbBillboardVendorDebugMsgStart(void);
extern void ScalerUsbBillboardVendorDebugMsgEnd(void);
extern void ScalerUsbBillboardVendorDebugMsgGetValue(void);
extern void ScalerUsbBillboardVendorDebugMsgGetString(void);

extern void ScalerUsbBillboardVendorWriteSyseeprom(void);
extern void ScalerUsbBillboardVendorReadSyseeprom(void);
extern void ScalerUsbBillboardTransmtDataToHost(WORD usLength, BYTE *pucDataBuf);
extern void ScalerUsbBillboardVendorRequest(void);

extern void ScalerUsbBillboardEepromWrite(bit bSysDefualtIICPin, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
extern void ScalerUsbBillboardEepromRead(bit bSysDefualtIICPin, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
extern void ScalerUsbBillboardGetDescriptor(void);
extern void ScalerUsbBillboardSetAddr(void);
extern void ScalerUsbBillboardSetConf(void);
extern void ScalerUsbBillboardGetInterface(void);
extern void ScalerUsbBillboardSetInterface(void);
extern void ScalerUsbBillboardGetStatus(void);
extern void ScalerUsbBillboardGetConf(void);
extern void ScalerUsbBillboardSetFeature(void);
extern void ScalerUsbBillboardClearFeature(void);
extern void ScalerUsbBillboardInitCtrlVariable(void);
extern void ScalerUsbBillboardGetAltModeInfo(void);
extern bit ScalerUsbBillboardCtrlXfer(BYTE ucXferType, BYTE ucIsLastPacket);
extern bit ScalerUsbBillboardXferForGetDescriptor(BYTE ucXferType, BYTE ucIsLastPacket);
extern void ScalerUsbBillboardLoadTrimming(void);

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
extern void ScalerUsbBillboardHidRequestSetReport(void);
extern void ScalerUsbBillboardHidRequestGetReport(void);
extern void ScalerUsbBillboardHidRequestGetReportVendorCommand(void);
extern void ScalerUsbBillboardHidRequestSetReportVendorCommand(void);
// HID Vendor Request Command
extern void ScalerUsbBillboardHidVendorSetRegisterByte(void);
extern void ScalerUsbBillboardHidVendorGetRegisterByte(void);
extern void ScalerUsbBillboardHidVendorReadFlash(void);
extern void ScalerUsbBillboardHidVendorHandshake(void);
extern void ScalerUsbBillboardHidVendorCalculateCrc(void);
extern void ScalerUsbBillboardHidVendorIspEnable(void);
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern void ScalerUsbBillboardHidVendorWriteFlash(void);
#endif
extern void ScalerUsbBillboardHidVendorSectorErase(void);
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern void ScalerUsbBillboardHidVendorBankErase(void);
#endif
#endif
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern void ScalerUsbBillboardHidVendorDualBankProcess1(void);
extern void ScalerUsbBillboardHidVendorDualBankProcess2(void);
extern void ScalerUsbBillboardHidVendorGetIspStartBank(void);
extern void ScalerUsbBillboardHidVendorGetIspKeyAddr(void);
extern void ScalerUsbBillboardHidVendorGetIspFlagAddr(void);
extern void ScalerUsbBillboardHidVendorGetIspSignatureAddr(void);
extern void ScalerUsbBillboardHidVendorGetVerifyCopyResult(void);
extern void ScalerUsbBillboardHidVendorGetCurrentKeyAddr(void);
extern void ScalerUsbBillboardHidVendorGetFWInfo(void);
// Background Program Function Define
extern void ScalerUsbBillboardHidVendorSetBackgroundWriteTime(void);
// extern void ScalerUsbBillboardVendorCheckBackgroundProgram(void);
#endif
#endif

#if(_USB_BB_HID_TYPE_SUPPORT == _ON)
extern void ScalerUsbBillboardHidClassRequest(void);
#endif
#if(_PORT_CTRL_RTS_SUPPORT == _ON)
extern void ScalerUsbBillboardGetAltModeRtsInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE *pucBillboardAltModeInfo);
#endif
#if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)
extern void ScalerUsbBillboardGetAltModeUserInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE *pucBillboardAltModeInfo);
#endif
#endif

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
extern void ScalerUsbBillboardPhyInitial(void);
extern void ScalerUsbBillboardSetPhyRegAddr(WORD usAddr);
extern void ScalerUsbBillboardSetPhyRegPage(WORD usAddr);
extern void ScalerUsbBillboardSetPhyRegByte(WORD usAddr, BYTE ucValue);
extern void ScalerUsbBillboardSetPhyRegBitField(WORD usAddr, DWORD ulAnd, BYTE ucOr);
extern BYTE ScalerUsbBillboardGetPhyRegByte(WORD usAddr);
extern BYTE ScalerUsbBillboardGetPhyRegBitField(WORD usAddr, BYTE ucAnd);
#endif // End of #if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif // End of #ifndef __SCALER_USB_BILLBOARD_H__
