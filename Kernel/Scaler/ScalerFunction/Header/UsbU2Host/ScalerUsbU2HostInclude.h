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
// ID Code      : ScalerUsbU2HostInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// USB OHCI Memory Filed Address define
// Bit[15] : ED or TD
// Bit[14] : HCCA Memory
// Bit[13:8] : DWORD No
// Bit[7:0] : Bit No
//----------------------------------------------------------------------------------------------------
#define _U2HOST_OHCI_ED_D00_B00_DEVICE_ADDRESS                  0x0000
#define _U2HOST_OHCI_ED_D00_B07_ENDPT                           0x0007
#define _U2HOST_OHCI_ED_D00_B0B_PID_CODE                        0x000B
#define _U2HOST_OHCI_ED_D00_B0D_SPEED                           0x000D
#define _U2HOST_OHCI_ED_D00_B0E_SKIP                            0x000E
#define _U2HOST_OHCI_ED_D00_B0F_FORMAT                          0x000F
#define _U2HOST_OHCI_ED_D00_B10_MPS                             0x0010
#define _U2HOST_OHCI_ED_D01_B04_TAIL_POINTER                    0x0104
#define _U2HOST_OHCI_ED_D02_B00_HALTED                          0x0200
#define _U2HOST_OHCI_ED_D02_B01_CARRY                           0x0201
#define _U2HOST_OHCI_ED_D02_B04_HEAD_POINTER                    0x0204
#define _U2HOST_OHCI_ED_D03_B04_NEXT_ED                         0x0304

#define _U2HOST_OHCI_TD_D00_B12_BUFFER_ROUNDING                 0x8012
#define _U2HOST_OHCI_TD_D00_B13_PID_CODE                        0x8013
#define _U2HOST_OHCI_TD_D00_B15_DELAY_INT                       0x8015
#define _U2HOST_OHCI_TD_D00_B18_DATA_TOGGLE                     0x8018
#define _U2HOST_OHCI_TD_D00_B1A_ERR_CNT                         0x801A
#define _U2HOST_OHCI_TD_D00_B1C_CONDITION_CODE                  0x801C
#define _U2HOST_OHCI_TD_D01_B00_CURR_BUF_POINTER                0x8100
#define _U2HOST_OHCI_TD_D02_B04_NEXT_TD                         0x8204
#define _U2HOST_OHCI_TD_D03_B00_BUF_END                         0x8300

#define _U2HOST_OHCI_HCCA_D20_B00_FRAME_NUMBER                  0x6000
#define _U2HOST_OHCI_HCCA_D20_B10_PAD1                          0x6010
#define _U2HOST_OHCI_HCCA_D21_B00_DONE_HEAD                     0x6100
#endif

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// USB EHCI Memory Filed Address define
// Bit[15] : QH or qTD
// Bit[11:8] : DWORD No
// Bit[7:0] : Bit No
//----------------------------------------------------------------------------------------------------
#define _U2HOST_EHCI_QH_D00_B00_T                               0x0000
#define _U2HOST_EHCI_QH_D00_B01_TYP                             0x0001
#define _U2HOST_EHCI_QH_D00_B05_QHLP                            0x0005

#define _U2HOST_EHCI_QH_D01_B00_DEVICE_ADDRESS                  0x0100
#define _U2HOST_EHCI_QH_D01_B07_I                               0x0107
#define _U2HOST_EHCI_QH_D01_B08_ENDPT                           0x0108
#define _U2HOST_EHCI_QH_D01_B0C_EPS                             0x010C
#define _U2HOST_EHCI_QH_D01_B0E_DTC                             0x010E
#define _U2HOST_EHCI_QH_D01_B0F_H                               0x010F
#define _U2HOST_EHCI_QH_D01_B10_MPL                             0x0110
#define _U2HOST_EHCI_QH_D01_B1B_C                               0x011B
#define _U2HOST_EHCI_QH_D01_B1C_RL                              0x011C

#define _U2HOST_EHCI_QH_D02_B00_S_MASK                          0x0200
#define _U2HOST_EHCI_QH_D02_B08_C_MASK                          0x0208
#define _U2HOST_EHCI_QH_D02_B10_HUB_ADDRESS                     0x0210
#define _U2HOST_EHCI_QH_D02_B17_PORT_NUMBER                     0x0217
#define _U2HOST_EHCI_QH_D02_B1E_MULT                            0x021E

#define _U2HOST_EHCI_QH_D03_B05_CURRENT_QTD_POINTER             0x0305

#define _U2HOST_EHCI_QH_D04_B00_NEXT_QTD_T                      0x0400
#define _U2HOST_EHCI_QH_D04_B05_NEXT_QTD                        0x0405

#define _U2HOST_EHCI_QH_D05_B00_ALTERNATE_NEXT_QTD_T            0x0500
#define _U2HOST_EHCI_QH_D05_B01_NAK_CNT                         0x0501
#define _U2HOST_EHCI_QH_D05_B05_ALTERNATE_NEXT_QTD              0x0505
#define _U2HOST_EHCI_QH_D06_B00_STATUS                          0x0600
#define _U2HOST_EHCI_QH_D06_B08_PID_CODE                        0x0608
#define _U2HOST_EHCI_QH_D06_B0A_CERR                            0x060A
#define _U2HOST_EHCI_QH_D06_B0C_C_PAGE                          0x060C
#define _U2HOST_EHCI_QH_D06_B0F_IOC                             0x060F
#define _U2HOST_EHCI_QH_D06_B10_TRANSFER_BYTES                  0x0610
#define _U2HOST_EHCI_QH_D06_B1F_DT                              0x061F

#define _U2HOST_EHCI_QH_D07_B00_CURRENT_OFFSET                  0x0700
#define _U2HOST_EHCI_QH_D07_B0C_BUFFER_POINTER_PAGE0            0x070C

#define _U2HOST_EHCI_QH_D08_B00_C_PROG_MASK                     0x0800
#define _U2HOST_EHCI_QH_D08_B0C_BUFFER_POINTER_PAGE1            0x080C

#define _U2HOST_EHCI_QH_D09_B00_FRAME_TAG                       0x0900
#define _U2HOST_EHCI_QH_D09_B05_S_BYTES                         0x0905
#define _U2HOST_EHCI_QH_D09_B0C_BUFFER_POINTER_PAGE2            0x090C

#define _U2HOST_EHCI_QH_D0A_B0C_BUFFER_POINTER_PAGE3            0x0A0C

#define _U2HOST_EHCI_QH_D0B_B0C_BUFFER_POINTER_PAGE4            0x0B0C

#define _U2HOST_EHCI_QTD_D04_B00_NEXT_QTD_T                     0x8400
#define _U2HOST_EHCI_QTD_D04_B05_NEXT_QTD                       0x8405
#define _U2HOST_EHCI_QTD_D05_B00_ALTERNATE_NEXT_QTD_T           0x8500
#define _U2HOST_EHCI_QTD_D05_B05_ALTERNATE_NEXT_QTD             0x8505
#define _U2HOST_EHCI_QTD_D06_B00_STATUS                         0x8600
#define _U2HOST_EHCI_QTD_D06_B08_PID_CODE                       0x8608
#define _U2HOST_EHCI_QTD_D06_B0A_CERR                           0x860A
#define _U2HOST_EHCI_QTD_D06_B0C_C_PAGE                         0x860C
#define _U2HOST_EHCI_QTD_D06_B0F_IOC                            0x860F
#define _U2HOST_EHCI_QTD_D06_B10_TRANSFER_BYTES                 0x8610
#define _U2HOST_EHCI_QTD_D06_B1F_DT                             0x861F
#define _U2HOST_EHCI_QTD_D07_B00_CURRENT_OFFSET                 0x8700
#define _U2HOST_EHCI_QTD_D07_B0C_BUFFER_POINTER_PAGE0           0x870C
#define _U2HOST_EHCI_QTD_D08_B0C_BUFFER_POINTER_PAGE1           0x880C
#define _U2HOST_EHCI_QTD_D09_B0C_BUFFER_POINTER_PAGE2           0x890C
#define _U2HOST_EHCI_QTD_D0A_B0C_BUFFER_POINTER_PAGE3           0x8A0C
#define _U2HOST_EHCI_QTD_D0B_B0C_BUFFER_POINTER_PAGE4           0x8B0C
#endif

//----------------------------------------------------------------------------------------------------
// Bit definition for Queue Element Status Field
//----------------------------------------------------------------------------------------------------
#define _U2HOST_QTD_STATUS_ERR                                  0x01
#define _U2HOST_QTD_STATUS_SPLIT_TRANSACTION_STATE              0x02
#define _U2HOST_QTD_STATUS_MISSED_MICRO_FRAME                   0x04
#define _U2HOST_QTD_STATUS_TRANSACTION_ERROR                    0x08
#define _U2HOST_QTD_STATUS_BABBLE_DETECTED                      0x10
#define _U2HOST_QTD_STATUS_DATA_BUFFER_ERROR                    0x20
#define _U2HOST_QTD_STATUS_HALTED                               0x40
#define _U2HOST_QTD_STATUS_ACTIVE                               0x80
#define _U2HOST_EHCI_BULK_WRITE_FROM_DM_CLIENT_ST_ADDR          0x00


//----------------------------------------------------------------------------------------------------
// USB Standard Descriptor Address define
// Byte[15:8] : Byte Offset
// Byte[4:0] : Length
//----------------------------------------------------------------------------------------------------
#define _U2HOST_DES_LENGTH                                      0x0001
#define _U2HOST_DES_TYPE                                        0x0101

#define _U2HOST_DEVICE_DES_LENGTH                               0x0001
#define _U2HOST_DEVICE_DES_TYPE                                 0x0101
#define _U2HOST_DEVICE_DES_SUB_BCD_USB                          0x0202
#define _U2HOST_DEVICE_DES_CLASS                                0x0401
#define _U2HOST_DEVICE_DES_SUB_CLASS                            0x0501
#define _U2HOST_DEVICE_DES_PROTOCOL                             0x0601
#define _U2HOST_DEVICE_DES_MAX_PACKET_SIZE_0                    0x0701
#define _U2HOST_DEVICE_DES_ID_VENDOR                            0x0802
#define _U2HOST_DEVICE_DES_ID_PRODUCT                           0x0A02
#define _U2HOST_DEVICE_DES_BCD_DEVICE                           0x0C02
#define _U2HOST_DEVICE_DES_I_MANUFACTURER                       0x0E01
#define _U2HOST_DEVICE_DES_I_PRODUCT                            0x0F01
#define _U2HOST_DEVICE_DES_I_SERIAL_NUMBER                      0x1001
#define _U2HOST_DEVICE_DES_NUM_CONFIGURATIONS                   0x1101

#define _U2HOST_CONFIG_DES_LENGTH                               0x0001
#define _U2HOST_CONFIG_DES_TYPE                                 0x0101
#define _U2HOST_CONFIG_DES_TOTAL_LENGTH                         0x0202
#define _U2HOST_CONFIG_DES_NUM_INTERFACES                       0x0401
#define _U2HOST_CONFIG_DES_VALUE                                0x0501
#define _U2HOST_CONFIG_DES_I_CONFIGURATION                      0x0601
#define _U2HOST_CONFIG_DES_ATTRIBUTES                           0x0701
#define _U2HOST_CONFIG_DES_MAX_POWER                            0x0801

#define _U2HOST_INTF_DES_LENGTH                                 0x0001
#define _U2HOST_INTF_DES_TYPE                                   0x0101
#define _U2HOST_INTF_DES_INTERFACE_NUMBER                       0x0201
#define _U2HOST_INTF_DES_ALTERNATE_SETTING                      0x0301
#define _U2HOST_INTF_DES_NUM_ENDPOINTS                          0x0401
#define _U2HOST_INTF_DES_CLASS                                  0x0501
#define _U2HOST_INTF_DES_SUB_CLASS                              0x0601
#define _U2HOST_INTF_DES_PROTOCOL                               0x0701
#define _U2HOST_INTF_DES_I_INTERFACE                            0x0801

#define _U2HOST_HID_DES_LENGTH                                  0x0001
#define _U2HOST_HID_DES_TYPE_1                                  0x0101
#define _U2HOST_HID_DES_BCD_HID                                 0x0202
#define _U2HOST_HID_DES_COUNTRY_CODE                            0x0401
#define _U2HOST_HID_DES_NUM_DESCRIPTOR                          0x0501
#define _U2HOST_HID_DES_TYPE_2                                  0x0601
#define _U2HOST_HID_DES_REPORT_LENGTH                           0x0702

#define _U2HOST_ENDPT_DES_LENGTH                                0x0001
#define _U2HOST_ENDPT_DES_TYPE                                  0x0101
#define _U2HOST_ENDPT_DES_ADDRESS                               0x0201
#define _U2HOST_ENDPT_DES_ATTRIBUTES                            0x0301
#define _U2HOST_ENDPT_DES_MAX_PACKET_SIZE                       0x0402
#define _U2HOST_ENDPT_DES_INTERVAL                              0x0601

#define _U2HOST_STRING_DES_LENGTH                               0x0001
#define _U2HOST_STRING_DES_TYPE                                 0x0101
#define _U2HOST_STRING_DES_STRING                               0x0202

#define _U2HOST_HUB_DES_LENGTH                                  0x0001
#define _U2HOST_HUB_DES_TYPE                                    0x0101
#define _U2HOST_HUB_DES_NBR_PORTS                               0x0201
#define _U2HOST_HUB_DES_CHARACTERISTICS                         0x0302
#define _U2HOST_HUB_DES_POWER_ON_TO_POWER_GOOD                  0x0501
#define _U2HOST_HUB_DES_CONTR_CURRENT                           0x0601

// #define _U2HOST_HUB_DES_DEVICE_REMOVABLE              // Size : Variable, depending on number of ports on hub
// #define _U2HOST_HUB_DES_PORT_POWER_CTRL_MASK          // Size : Variable, depending on number of ports on hub

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef enum
{
    _U2HOST_EHCI_DEVICE_SPEED_FULL = 0x00,
    _U2HOST_EHCI_DEVICE_SPEED_LOW = 0x01,
    _U2HOST_EHCI_DEVICE_SPEED_HIGH = 0x02,
    _U2HOST_EHCI_DEVICE_SPEED_RESERVED = 0x03,
    _U2HOST_EHCI_DEVICE_SPEED_NOT_LOW = 0x04,
    _U2HOST_EHCI_DEVICE_SPEED_NONE = 0xff,
} EnumUsbEHCIDeviceSpeed;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
extern WORD code tUSB_OHCI_CTRL_ED_ADDR_TABLE[];
extern WORD code tUSB_OHCI_CTRL_TD_ADDR_TABLE[];
extern WORD code tUSB_OHCI_INT_ED_ADDR_TABLE[];
extern WORD code tUSB_OHCI_INT_TD_ADDR_TABLE[];
extern WORD code tUSB_OHCI_INT_BUFFER_ADDR_TABLE[];
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern WORD code tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[];
extern WORD code tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[];
extern WORD code tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[];
extern WORD code tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[];
extern WORD code tUSB_OHCI_BULK_OUT_BUFFER_ADDR_TABLE[];
extern WORD code tUSB_OHCI_BULK_IN_BUFFER_ADDR_TABLE[];
extern WORD code tUSB_OHCI_INT_BUFFER_ADDR_TABLE[];
#endif
#endif
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
extern WORD code tUSB_EHCI_CTRL_QH_ADDR_TABLE[];
extern WORD code tUSB_EHCI_CTRL_QTD_ADDR_TABLE[];
extern WORD code tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[];
extern WORD code tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[];
extern WORD code tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[];
extern WORD code tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[];
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsbU2HostCurOwerInit(EnumUsbU2HostOwner enumOwner);
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
extern void ScalerUsbU2HostSetOHCIMemoryAddr(WORD usAddr, WORD usFieldAddr);
extern void ScalerUsbU2HostSetOHCIMemoryField(WORD usAddr, WORD usFieldAddr, DWORD ulValue);
extern DWORD ScalerUsbU2HostGetOHCIMemoryField(WORD usAddr, WORD usFieldAddr);
extern void ScalerUsbU2HostSetOHCIRhStsRegBitField(WORD usAddr, BYTE ucValue);
extern void ScalerUsbU2HostSetOHCIHccaIntTab(WORD usAddr, BYTE ucTabNo, DWORD ulValue);
#endif
extern BYTE ScalerUsbU2HostGetRegBitField(WORD usAddr, BYTE ucAnd);
extern DWORD ScalerUsbU2HostGetRegDword(WORD usAddr);
extern void ScalerUsbU2HostSetRegDword(WORD usAddr, DWORD ulValue);
extern void ScalerUsbU2HostSetRegBitField(WORD usAddr, DWORD ulAnd, BYTE ucOr);
extern void ScalerUsbU2HostMemoryClear(WORD usAddr, WORD usSize);
extern void ScalerUsbU2HostSetCmdBufData(BYTE *pucData, BYTE ucLength);
extern void ScalerUsbU2HostSetBufferData(WORD usbufferAddr, WORD usLen, BYTE *pucData);
extern void ScalerUsbU2HostGetBufferData(WORD usbufferAddr, WORD usLen, BYTE *pucData);
extern void ScalerUsbU2HostSetPhyRegBitField(WORD usAddr, DWORD ulAnd, BYTE ucOr);
extern void ScalerUsbU2HostSetRegByte(WORD usAddr, BYTE ucValue);
extern BYTE ScalerUsbU2HostGetRegByte(WORD usAddr);
extern bit ScalerUsbU2HostRhPortEnableChk(EnumUsbU2HostOwner enumMode);
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
extern void ScalerUsbU2HostSetEHCIMemoryField(WORD usAddr, WORD usFieldAddr, DWORD ulValue);
extern void ScalerUsbU2HostSetEHCIMemoryAddr(WORD usAddr, WORD usFieldAddr);
extern DWORD ScalerUsbU2HostGetEHCIMemoryField(WORD usAddr, WORD usFieldAddr);
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#endif


