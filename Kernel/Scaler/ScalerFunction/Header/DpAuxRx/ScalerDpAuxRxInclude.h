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
// ID Code      : ScalerDpAuxRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DP Aux Auto Calibration Support
//--------------------------------------------------
#define _DP_AUX_AUTO_CALIBRATION_VTH                                                            15

//--------------------------------------------------
// DP AUX Global IRQ Flag
//--------------------------------------------------
#if(_DP_AUX_RX0_SUPPORT == _ON)
#define GET_DP_AUX_RX0_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()                                          (ScalerGetBit_EXINT(P6F_15_ADI_DP_IRQ3, _BIT3) == _BIT3)
#define GET_DP_AUX_RX0_GLOBAL_LOW_PRIORITY_IRQ_FLAG()                                           (ScalerGetBit_EXINT(P6F_15_ADI_DP_IRQ3, _BIT0) == _BIT0)
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
#define GET_DP_AUX_RX1_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()                                          (ScalerGetBit_EXINT(P6F_15_ADI_DP_IRQ3, _BIT4) == _BIT4)
#define GET_DP_AUX_RX1_GLOBAL_LOW_PRIORITY_IRQ_FLAG()                                           (ScalerGetBit_EXINT(P6F_15_ADI_DP_IRQ3, _BIT1) == _BIT1)
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
#define GET_DP_AUX_RX2_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()                                          (ScalerGetBit_EXINT(P6F_15_ADI_DP_IRQ3, _BIT5) == _BIT5)
#define GET_DP_AUX_RX2_GLOBAL_LOW_PRIORITY_IRQ_FLAG()                                           (ScalerGetBit_EXINT(P6F_15_ADI_DP_IRQ3, _BIT2) == _BIT2)
#endif

//--------------------------------------------------
// Definitions of AUX Mac Related Register Macro
//--------------------------------------------------
#define CLR_DP_AUX_RX_REG_CLEAR_PAYLOAD_ID_TABLE()                                              (ScalerDpAuxRxClearPayload(GET_DP_RX_BASE_PORT()))
#define CLR_DP_AUX_RX_REG_CLEAR_PAYLOAD_ID_TABLE_EXINT()                                        (ScalerDpAuxRxClearPayload_EXINT0(GET_DP_RX_BASE_PORT()))

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define SET_DP_AUX_RX_REG_111_IRQ_EN()                                                          {ScalerDpAuxRxSetDpcdIntEnable(GET_DP_RX_BASE_PORT(), 0x00, 0x01, 0x11, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);}
#define CLR_DP_AUX_RX_REG_111_IRQ_EN()                                                          {ScalerDpAuxRxSetDpcdIntEnable(GET_DP_RX_BASE_PORT(), 0x00, 0x01, 0x11, 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);}

#define CLR_DP_AUX_RX_REG_111_IRQ_FLAG()                                                        {}
#define CLR_DP_AUX_RX_REG_111_IRQ_FLAG_EXINT()                                                  {}

#define SET_DP_AUX_RX_REG_1C2_IRQ_EN()                                                          {ScalerDpAuxRxSetDpcdIntEnable(GET_DP_RX_BASE_PORT(), 0x00, 0x01, 0xC2, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);}
#define CLR_DP_AUX_RX_REG_1C2_IRQ_EN()                                                          {ScalerDpAuxRxSetDpcdIntEnable(GET_DP_RX_BASE_PORT(), 0x00, 0x01, 0xC2, 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);}

#define CLR_DP_AUX_RX_REG_1C2_IRQ_FLAG()                                                        {}
#define CLR_DP_AUX_RX_REG_1C2_IRQ_FLAG_EXINT()                                                  {}

#define CLR_DP_AUX_RX_REG_2C0_IRQ_EN()                                                          {ScalerDpAuxRxSetDpcdIntEnable(GET_DP_RX_BASE_PORT(), 0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_READ, _DISABLE);}
#define CLR_DP_AUX_RX_REG_2C0_IRQ_EN_EXINT()                                                    {ScalerDpAuxRxSetDpcdIntEnable_EXINT0(GET_DP_RX_BASE_PORT(), 0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_READ, _DISABLE);}
#define SET_DP_AUX_RX_REG_2C0_IRQ_EN_EXINT()                                                    {ScalerDpAuxRxSetDpcdIntEnable_EXINT0(GET_DP_RX_BASE_PORT(), 0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);}

#define CLR_DP_AUX_RX_REG_2C0_IRQ_FLAG_EXINT()                                                  {}
#else
#define SET_DP_AUX_RX_REG_111_IRQ_EN()                                                          {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT7, _BIT7);}
#define CLR_DP_AUX_RX_REG_111_IRQ_EN()                                                          {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT7, 0x00);}

#define CLR_DP_AUX_RX_REG_111_IRQ_FLAG()                                                        {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _REG8TO32_BYTE_0, _BIT7);}
#define CLR_DP_AUX_RX_REG_111_IRQ_FLAG_EXINT()                                                  {SCALER32_DP_SET_OFFSET_BYTE_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _REG8TO32_BYTE_0, _BIT7);}

#define SET_DP_AUX_RX_REG_1C2_IRQ_EN()                                                          {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT4, _BIT4);}
#define CLR_DP_AUX_RX_REG_1C2_IRQ_EN()                                                          {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT4, 0x00);}

#define CLR_DP_AUX_RX_REG_1C2_IRQ_FLAG()                                                        {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _REG8TO32_BYTE_0, _BIT4);}
#define CLR_DP_AUX_RX_REG_1C2_IRQ_FLAG_EXINT()                                                  {SCALER32_DP_SET_OFFSET_BYTE_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _REG8TO32_BYTE_0, _BIT4);}

#define CLR_DP_AUX_RX_REG_2C0_IRQ_EN()                                                          {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT3, 0x00);}
#define CLR_DP_AUX_RX_REG_2C0_IRQ_EN_EXINT()                                                    {SCALER32_DP_SET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT3, 0x00);}
#define SET_DP_AUX_RX_REG_2C0_IRQ_EN_EXINT()                                                    {SCALER32_DP_SET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT3, _BIT3);}

#define CLR_DP_AUX_RX_REG_2C0_IRQ_FLAG_EXINT()                                                  {SCALER32_DP_SET_OFFSET_BYTE_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _REG8TO32_BYTE_0, _BIT3);}
#endif
//--------------------------------------------------
// Definitions of DPCD 111 Mst Enable Backup
//--------------------------------------------------
#define GET_DP_AUX_RX_DPCD111_MST_ENABLE_BACKUP()                                               (g_pbDpAuxRxDpcdMstEnBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS])
#define SET_DP_AUX_RX_DPCD111_MST_ENABLE_BACKUP(x)                                              (g_pbDpAuxRxDpcdMstEnBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS] = (x))

//--------------------------------------------------
// Definitions of AUX Get DPCD Macro
//--------------------------------------------------
#define GET_DP_AUX_RX_REG_DPCD_INFO(x, y, z)                                                    (ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_BASE_PORT(), (x), (y), (z)))
#define SET_DP_AUX_RX_REG_DPCD_INFO(x, y, z, w)                                                 {ScalerDpAuxRxSetDpcdValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w));}
#define SET_DP_AUX_RX_REG_WR_DPCD_INFO(x, y, z, w)                                              {ScalerDpAuxRxSetDpcdWriteValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w));}
#define SET_DP_AUX_RX_REG_W1C_DPCD_INFO(x, y, z, w)                                             {ScalerDpAuxRxSetDpcdWrite1ClearValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w));}
#define GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(x, y, z)                                             (ScalerDpAuxRxGetDpcdInfo_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z)))
#define SET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(x, y, z, w)                                          {ScalerDpAuxRxSetDpcdValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w));}
#define SET_DP_AUX_RX_REG_WR_DPCD_INFO_EXINT0(x, y, z, w)                                       {ScalerDpAuxRxSetDpcdWriteValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w));}
#define SET_DP_AUX_RX_REG_W1C_DPCD_INFO_EXINT0(x, y, z, w)                                      {ScalerDpAuxRxSetDpcdWrite1ClearValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w));}
#define SET_DP_AUX_RX_REG_DPCD_BIT_INFO_EXINT0(x, y, z, w, u)                                   {ScalerDpAuxRxSetDpcdBitValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w), (u));}

//--------------------------------------------------
// Definitions of AUX MSG MACRO
//--------------------------------------------------
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
#define SET_DP_AUX_RX0_DPCD_IRQ_VECTOR(x)                                                       (g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[0] = (x))
#define SET_DP_AUX_RX1_DPCD_IRQ_VECTOR(x)                                                       (g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[1] = (x))
#define SET_DP_AUX_RX2_DPCD_IRQ_VECTOR(x)                                                       (g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[2] = (x))
#define GET_DP_AUX_RX0_MSG_IRQ_HANDLE()                                                         ((bit)(g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[0] & (_BIT5 | _BIT4)) && (g_stDpAuxRxMsgFlag.pbDpAuxRxMsgDownRepIrqEnable[0] || g_stDpAuxRxMsgFlag.pbDpAuxRxMsgUpReqIrqEnable[0]))
#define GET_DP_AUX_RX1_MSG_IRQ_HANDLE()                                                         ((bit)(g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[1] & (_BIT5 | _BIT4)) && (g_stDpAuxRxMsgFlag.pbDpAuxRxMsgDownRepIrqEnable[1] || g_stDpAuxRxMsgFlag.pbDpAuxRxMsgUpReqIrqEnable[1]))
#define GET_DP_AUX_RX2_MSG_IRQ_HANDLE()                                                         ((bit)(g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[2] & (_BIT5 | _BIT4)) && (g_stDpAuxRxMsgFlag.pbDpAuxRxMsgDownRepIrqEnable[2] || g_stDpAuxRxMsgFlag.pbDpAuxRxMsgUpReqIrqEnable[2]))
#endif
#endif

//--------------------------------------------------
// DP Aux DPCD 128B132B Training Read Interval
//--------------------------------------------------
#define _DP_AUX_RX_DPCD_128B132B_TRAINING_AUX_RD_INTERVAL                                       0x8F

//--------------------------------------------------
// DP Aux IIC SCL Clock Rate
//--------------------------------------------------
#define _DP_AUX_IIC_SCL_CLK_SETTING                                                             0x00 // Default: 875KHz
#define _DP_AUX_IIC_SCL_CLK_KHZ                                                                 (_HW_INTERNAL_OSC_XTAL / 32 / (_DP_AUX_IIC_SCL_CLK_SETTING + 1))

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// DP Aux Rx msg flag length
//--------------------------------------------------
#define _DP_AUX_RX_MAG_FLAG_LENGTH                                                              0x03
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DP_AUX_RX_REQ_NATIVE_READ = (_BIT7 | _BIT4),
    _DP_AUX_RX_REQ_NATIVE_WRITE = (_BIT7),
    _DP_AUX_RX_REQ_I2C_READ = (_BIT4),
    _DP_AUX_RX_REQ_I2C_READ_MOT = (_BIT6 | _BIT4),
    _DP_AUX_RX_REQ_I2C_WRITE = 0x00,
    _DP_AUX_RX_REQ_I2C_WRITE_MOT = (_BIT6),
    _DP_AUX_RX_REQ_I2C_WRITE_STATUS_REQUEST = (_BIT5),
    _DP_AUX_RX_REQ_NONE = 0xFF,
} EnumDpAuxRxReqCmd;

typedef enum
{
    _AUX_RX_DPCD_WILDCARD_MASK_NONE = 0x00,
    _AUX_RX_DPCD_WILDCARD_MASK_BIT3_0 = 0x10,                                 // discard DPCD[3:0] : 0x0000x
    _AUX_RX_DPCD_WILDCARD_MASK_BIT7_0 = 0x30,                                 // discard DPCD[7:0] : 0x000xx
    _AUX_RX_DPCD_WILDCARD_MASK_BIT11_0 = 0x70,                                // discard DPCD[11:0] : 0x00xxx
    _AUX_RX_DPCD_WILDCARD_MASK_BIT15_0 = 0xF0,                                // discard DPCD[15:12] : 0x0xxxx
} EnumDpAuxRxDpcdWildCardBitMask;

typedef enum
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
    _AUX_RX_FEC_DECODE_EN_DETECTED,
#endif
#endif

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
#if(_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON)
    _AUX_RX_CABLE_ID_UPDATE,
#endif
#endif
#else
#if(_DP_AUX_RX_DPCD_WILDCARD_00210_SUPPORT == _ON)
    _AUX_RX_DPCD_WILDCARD_210,
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_00281_SUPPORT == _ON)
    _AUX_RX_DPCD_WILDCARD_281,
#endif
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT == _ON)
    _AUX_RX_DPCD_WILDCARD_2003,
#endif
#endif
    _AUX_RX_DPCD_WILDCARD_ID_END,
} EnumDpAuxRxDpcdWildCardId;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
typedef enum
{
    // Max = 4(0~3)
    _AUX_RX_DPCD_REMAP_32B_ID_END,
} EnumDpAuxRxDpcdRemap32BId;

typedef enum
{
    // Max = 1(0)
    _AUX_RX_DPCD_REMAP_16B_ID_END,
} EnumDpAuxRxDpcdRemap16BId;

typedef enum
{
    // Max = 4(0~3)
    _AUX_RX_DPCD_REMAP_8B_ID_END,
} EnumDpAuxRxDpcdRemap8BId;

#else
typedef enum
{
    _DP_AUX_RX_INT_NONE,
    _DP_AUX_RX_INT_DPCD_NORMAL,
    _DP_AUX_RX_INT_DPCD_LINK_TRAINING,
    _DP_AUX_RX_INT_DPCD_LINK_STATUS,
    _DP_AUX_RX_INT_I2C_FIXED_ADDR,
} EnumDpAuxRxIntCase;

typedef enum
{
//  DPCD_IRQ_CLEAR
    _DP_AUX_RX_DPCD_NONE = 0,

//  DPCD 00000~000FF
    _DP_AUX_RX_DPCD_00000_000FF = _BIT0,

//  DPCD 00100~001FF
    _DP_AUX_RX_DPCD_00100_001FF = _BIT1,

//  DPCD 00200~002FF
    _DP_AUX_RX_DPCD_00200_002FF = _BIT2,

//  DPCD 00300~0037F
    _DP_AUX_RX_DPCD_00300_0037F = _BIT3,

//  DPCD 00400~0047F
    _DP_AUX_RX_DPCD_00400_0047F = _BIT4,

//  DPCD 00500~005FF
    _DP_AUX_RX_DPCD_00500_005FF = _BIT5,

//  DPCD 00600~0061F
    _DP_AUX_RX_DPCD_00600_0061F = _BIT6,

//  DPCD 00700~0077F
    _DP_AUX_RX_DPCD_00700_0077F = _BIT7,

//  DPCD 02000~020FF
    _DP_AUX_RX_DPCD_02000_020FF = _BIT8,

//  DPCD 02200~022FF
    _DP_AUX_RX_DPCD_02200_022FF = _BIT9,

//  DPCD 02300~0237F
    _DP_AUX_RX_DPCD_02300_0237F = _BIT10,

//  DPCD 03000~030FF
    _DP_AUX_RX_DPCD_03000_030FF = _BIT11,

//  DPCD 03100~031FF
    _DP_AUX_RX_DPCD_03100_031FF = _BIT12,

//  DPCD 60000~6001F
    _DP_AUX_RX_DPCD_60000_6001F = _BIT13,

//  DPCD 68000~6803F
    _DP_AUX_RX_DPCD_68000_6803F = _BIT14,

//  DPCD 69000~6957F
    _DP_AUX_RX_DPCD_69000_6957F = _BIT15,
} EnumDpAuxRxDpcdGroup;

typedef enum
{
    // Rename your dpcd range and insert #if(your support == _ON)
    _AUX_RX_DPCD_REMAP_ID_END,
} EnumDpAuxRxDpcdRemapId;

typedef enum
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    _DP_AUX_RX_DPCD_ACCESS_DATA = _BIT4,
    _DP_AUX_RX_DPCD_ACCESS_CONFIG = _BIT5,
    _DP_AUX_RX_DPCD_ACCESS_ALL = (_BIT5 | _BIT4),
#else
    _DP_AUX_RX_DPCD_ACCESS_DATA = _BIT22,
    _DP_AUX_RX_DPCD_ACCESS_CONFIG = _BIT23,
    _DP_AUX_RX_DPCD_ACCESS_ALL = (_BIT23 | _BIT22),
#endif
} EnumDpAuxRxDpcdAccess;

typedef enum
{
    _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR = (_BIT10 | _BIT9 | _BIT8),
    _DP_AUX_RX_DPCD_INT_WRITE = _BIT10,
    _DP_AUX_RX_DPCD_INT_READ = _BIT11,
    _DP_AUX_RX_DPCD_INT_READ_WRITE = (_BIT11 | _BIT10),
} EnumDpAuxRxDpcdInt;

typedef struct
{
    EnumDpAuxRxDpcdGroup enumDpcdGroupIrq;
    DWORD ulDpcdWildCardIrq;
    DWORD ulDpcdRemapIrq;
    DWORD ulReqAddrStart;
    DWORD ulReqAddrEnd;
    BYTE ucReqLen;
    EnumDpAuxRxReqCmd enumReqType;
    BYTE pucFifoBackup[16];
    EnumDpAuxRxIntCase enumIntCase;
} StructDpAuxRxReceiveBackup;
#endif

typedef enum
{
    _AUX_RX_DPCD_ATTR_R = 0,
    _AUX_RX_DPCD_ATTR_RW = _BIT8,
} EnumDpAuxRxDpcdAttr;

typedef struct
{
    bit bDpAuxRxDpcdUpdate;
    WORD usDpAuxRxDpcdData;
    WORD usDpAuxRxNotDpcdBit;
    WORD usDpAuxRxDpcdBit;
} StructDpAuxRxDpcdUpdateProtect;

//--------------------------------------------------
// Enumerations for DP Maunual Mode Setting
//--------------------------------------------------
typedef enum
{
    _DP_AUX_MANUAL_MODE_SET = 0x00,
    _DP_AUX_MANUAL_MODE_RECOVER = 0x01,
} EnumDpAuxManualModeSetting;

//--------------------------------------------------
// Enumerations for DP Action after Check Source OUI
//--------------------------------------------------
typedef enum
{
    _LT_TP1_PERMIT_SWING_LEVEL_0,
}EnumDpAuxRxCheckSourceOUI;

//--------------------------------------------------
// Definitions of Aux Mode
//--------------------------------------------------
typedef enum
{
    _DP_RX_AUX_MANUAL_MODE = 0x00,
    _DP_RX_AUX_AUTO_MODE = 0x01,
}EnumDpAuxRxModeStatus;

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Enum for DP PR Mode Error Status
//--------------------------------------------------
typedef enum
{
    _DP_PR_MODE_CRC_ERROR = 0x01,
    _DP_PR_MODE_RFB_STORAGE_ERROR = 0x02,
    _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR = 0x04,
} EnumPRModeErrorStatus;

//--------------------------------------------------
// Enum for DP PR Mode Status
//--------------------------------------------------
typedef enum
{
    _DP_PR_MODE_INACTIVE = 0x00,
    _DP_PR_MODE_ENTRY = 0x01,
    _DP_PR_MODE_ACTIVE = 0x02,
    _DP_PR_MODE_INTERNAL_ERROR = 0x07,
} EnumPRModeStatus;
#endif

//--------------------------------------------------
// Definitions of DP Aux Msg Flag
//--------------------------------------------------
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
typedef struct
{
    BYTE pucDpAuxRxDpcdIrqVector[_DP_AUX_RX_MAG_FLAG_LENGTH];
    bit pbDpAuxRxMsgDownRepIrqEnable[_DP_AUX_RX_MAG_FLAG_LENGTH];
    bit pbDpAuxRxMsgUpReqIrqEnable[_DP_AUX_RX_MAG_FLAG_LENGTH];
} StructDpAuxRxMsgFlag;
#endif
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
extern volatile DWORD g_ulDpAuxRxBase32AddressOffset;
extern volatile bit g_pbDpAuxRxDpcdMstEnBackup[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
extern volatile StructDpAuxRxMsgFlag g_stDpAuxRxMsgFlag;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern EnumInputPort ScalerDpAuxRxRxDxMapping(EnumRx enumRx);
extern EnumRx ScalerDpAuxRxDxRxMapping(EnumInputPort enumInputPort);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
extern EnumRx ScalerDpAuxRxMsgFlagMapping(EnumInputPort enumInputPort);
#endif
#endif

extern void ScalerDpAuxRxInitial(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxPowerOn(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxLowPowerProc(void);
extern bit ScalerDpAuxRxVersionChange(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersion);
extern void ScalerDpAuxRxChangeDpcdVersion(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSwitchDpcdAddrIrqSetting(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSinkStatusSet(EnumInputPort enumInputPort, EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRxSetManualMode(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetAutoMode(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxLinkStatusReload(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetAssrModeEnable(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHpdTogglePhyResetProc(EnumInputPort enumInputPort, bit bHpdHighLow);
extern void ScalerDpAuxRxSetDpcdWildCardIntEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable);
extern bit ScalerDpAuxRxDpcdWildCardIntCheck(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRxDpcdWildCardIntClr(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRxSetFecStatusW1cProtectEnable(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDpAuxRxGetFecStatusW1cProtectEnable(EnumInputPort enumInputPort);
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRxSetDpcdIntEnable(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern DWORD ScalerDpAuxRxDpcdGetMirrorAddr(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
#endif

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpAuxRxDscUnplugReset(EnumInputPort enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpAuxRxMstReset(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxMstCapabilitySwitch(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpAuxRxSetBranchDeviceSpecificField(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrBranchDeviceSpecificField(EnumInputPort enumInputPort);
#endif

extern void ScalerDpAuxRxSetDpcdMaxLinkRateCapability(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate);
extern EnumDpLinkRate ScalerDpAuxRxGetDpcdMaxLinkRateCapability(EnumInputPort enumInputPort);
extern EnumDpLaneCount ScalerDpAuxRxGetDpcdMaxLaneCountCapability(EnumInputPort enumInputPort);

extern EnumDpHotPlugTime ScalerDpAuxRxBeforeHpdToggleProc(EnumInputPort enumInputPort, EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpAuxRxDisconnectReset(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxAfterHpdToggleProc(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxLinkStatusIRQ(EnumInputPort enumInputPort);

extern bit ScalerDpAuxRxGetFecStatus(EnumInputPort enumInputPort);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpAuxRxDscDpcdSetting(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxDscDpcdExtendedCapSetting(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxDscIrqCtrl(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRxFecDpcdSetting(EnumInputPort enumInputPort);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern bit ScalerDpAuxRxAudioCapabilitySwitchProc(EnumInputPort enumInputPort);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

extern EnumDpAuxRxModeStatus ScalerDpAuxRxGetAuxModeStatus(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxLinkTrainingOccur(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetLTStatus(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetLTStatus(EnumInputPort enumInputPort, BYTE ucLTStatusSet);
extern bit ScalerDpAuxRxGetFakeLT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetFakeLinkTraining(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClearFakeLinkTraining(EnumInputPort enumInputPort);

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern BYTE ScalerDpAuxRxGetAllPortFakeLT(void);
#endif

extern EnumDpLinkRate ScalerDpAuxRxGetLinkRate(EnumInputPort enumInputPort);
extern EnumDpLaneCount ScalerDpAuxRxGetLaneCount(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetLinkRate(EnumInputPort enumInputPort, BYTE ucLinkRate);
extern void ScalerDpAuxRxSetLaneCount(EnumInputPort enumInputPort, BYTE ucLaneCount);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern EnumDpLinkChannelCodingType ScalerDpAuxRxGetCodingType(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetCodingType(EnumInputPort enumInputPort, EnumDpLinkChannelCodingType enumCodingType);
#endif

extern void ScalerDpAuxRxErrorIgnore(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClearPayload(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxCancelValidSignalDetection(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetValidVideoCheck(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrValidVideoCheck(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxReactiveHdcpLongHotplug(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxCancelHdcpLongHotplug(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxActiveLinkStatusIRQ(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxActiveWDLinkStatusIRQ(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxCancelLinkStatusIRQ(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetCommandNoReply(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClearCommandNoReply(EnumInputPort enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
extern EnumDpRxAuxPowerStatus ScalerDpAuxRxGetAuxChPowerStatus(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetAuxChPowerOnWakeUp(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetSourceFirstPowerOn(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrAuxChPowerOnWakeUp(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrSourceFirstPowerOn(EnumInputPort enumInputPort);
extern EnumDpSourceWritePowerUpState ScalerDpAuxRxGetSourceWritePowerUp(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrSourceWritePowerUp(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrCheckChNoPowerDebounce(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClrCheckChPowerStatus(EnumInputPort enumInputPort);
#endif

extern void ScalerDpAuxRxTypeCPinAssert(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern bit ScalerDpAuxRxGetToggle(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxClearToggle(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxCheckHdcpCapability(EnumInputPort enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpAuxRxGetHdcpRepeaterSupport(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHdcp14EnableReadIrq(bit bEnable, EnumInputPort enumInputPort);
#endif

extern EnumInputPort ScalerDpAuxRxRxDxMapping_EXINT0(EnumRx enumRx);
extern EnumRx ScalerDpAuxRxDxRxMapping_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpAuxRxLowPriorityIntHandler_EXINT0(void);
extern EnumDpAuxRxModeStatus ScalerDpAuxRxGetAuxModeStatus_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetDpcdInfo_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRxGetDpcdBitInfo_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdBitValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdBitWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdBitWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorBitValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorBitWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSinkStatusSet_EXINT0(EnumInputPort enumInputPort, EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpAuxRxSetManualMode_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetAutoMode_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetDpcdWildCardIntEnable_EXINT0(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern bit ScalerDpAuxRxDpcdWildCardIntCheck_EXINT0(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId);
extern void ScalerDpAuxRxClearPayload_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxErrorToGated_EXINT0(EnumInputPort enumInputPort);
#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpAuxRxSetFecStatusW1cProtectEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDpAuxRxGetFecStatusW1cProtectEnable_EXINT0(EnumInputPort enumInputPort);
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRxSetDpcdIntEnable_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable);
extern DWORD ScalerDpAuxRxDpcdGetMirrorAddr_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern bit ScalerDpAuxRxScanReqDpcdAddr_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt);
#endif

extern EnumRx ScalerDpAuxRxDxRxMapping_WDINT(EnumInputPort enumInputPort);
extern EnumDpAuxRxModeStatus ScalerDpAuxRxGetAuxModeStatus_WDINT(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetDpcdInfo_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpAuxRxGetDpcdBitInfo_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdBitValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxSetDpcdMirrorValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpAuxRxSetDpcdMirrorBitValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpAuxRxDpcdPortAccessBackup_WDINT(void);
extern void ScalerDpAuxRxDpcdPortAccessBackupRestore_WDINT(void);
extern BYTE ScalerDpAuxRxGetLTStatus_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetLTStatus_WDINT(EnumInputPort enumInputPort, BYTE ucLTStatusSet);
extern EnumDpLinkRate ScalerDpAuxRxGetLinkRate_WDINT(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetTrainingPatternSet_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag_WDINT(EnumInputPort enumInputPort, bit bSetPhyDone);
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern EnumDpLinkChannelCodingType ScalerDpAuxRxGetCodingType_WDINT(EnumInputPort enumInputPort);
#endif

extern void ScalerDpAuxRxSetLinkRate_EXINT0(EnumInputPort enumInputPort, BYTE ucLinkRate);
extern void ScalerDpAuxRxSetLaneCount_EXINT0(EnumInputPort enumInputPort, BYTE ucLaneCount);
extern BYTE ScalerDpAuxRxTrainingPatternSet_EXINT0(EnumInputPort enumInputPort);
extern EnumDpLinkRate ScalerDpAuxRxGetLinkRate_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetLaneCount_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxCheckLinkRate_EXINT0(EnumInputPort enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern EnumDpLinkChannelCodingType ScalerDpAuxRxGetCodingType_EXINT0(EnumInputPort enumInputPort);
#endif

extern void ScalerDpAuxRxSetAutoMode_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetManualMode_WDINT(EnumInputPort enumInputPort);
extern EnumDpLinkRate ScalerDpAuxRxGetDpcdLinkRate_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxLinkStatusIRQ_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxCancelLinkStatusIRQ_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxDpcdLinkStatusReset_WDINT(EnumInputPort enumInputPort, EnumDpResetStatus enumDpResetStatus);
extern void ScalerDpAuxRxExitIntSetting_WDINT(void);
extern void ScalerDpAuxRxEnterIntSetting_WDINT(void);
extern void ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag(EnumInputPort enumInputPort, bit bSetPhyDone);
extern bit ScalerDpAuxRxGetLinkTrainingSetPhyFinishFlag(EnumInputPort enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpAuxRxWDTimerEventLinkTrainingTimeoutProc_WDINT(EnumInputPort enumInputPort);
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern DWORD ScalerDpAuxRxDpcdGetMirrorAddr_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpAuxRxHdcp2TypeValueReset(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHdcp2TypeValueReset_EXINT0(EnumInputPort enumInputPort);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
extern void ScalerDpAuxRxHdcp2StreamIDTypeReset(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHdcp2StreamIDTypeReset_EXINT0(EnumInputPort enumInputPort);
#endif
extern bit ScalerDpAuxRxGetGlobalIrq_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxHdcp2GetMessageID_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHdcpResetDpcdInfo_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxCpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType, EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetMPrimeReadDefer(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpAuxRxSetMPrimeReadDefer_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpAuxRxHdcp2HandshakeIRQ(EnumInputPort enumInputPort, bit bEnable);
#endif

extern void ScalerDpAuxRxTypeCPinAssert_EXINT0(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation);
extern BYTE ScalerDpAuxRxGetLTStatus_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetTp1Initial_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxGetTp1PermitSwing0_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxHpdIrqAssert_EXINT0(EnumInputPort enumInputPort);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpAuxRxDscPpsTimeOutProc(EnumInputPort enumInputPort);
#endif


// General
extern void ScalerDpAuxRxSetBase32AddressOffset_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSetBase32AddressOffset(EnumInputPort enumInputPort);

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
// SyncPayloadID for MTP format
extern void ScalerDpAuxRxSyncPayloadIDHandler_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSyncActHandler_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxSyncPayloadIDTable_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxAddNewPayloadIDProc_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID, BYTE ucIDStartPosition, BYTE ucTimeslotLength);
extern void ScalerDpAuxRxModifyPayloadIDProc_EXINT0(EnumInputPort enumInputPort, BYTE ucIDStartPosition, BYTE ucExistedIDLength, BYTE ucPayloadID, BYTE ucTimeslotLength);
extern void ScalerDpAuxRxClearPayloadIDProc_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxModifyPayloadTable_EXINT0(EnumInputPort enumInputPort, BYTE ucSearchStartPoint, BYTE ucSearchEndPoint, BYTE ucInitialID, BYTE ucDuplicateNum, BYTE ucPayloadID, bit bShiftDirection);
extern BYTE ScalerDpAuxRxGetSyncTableAction_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID);
extern BYTE ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(EnumInputPort enumInputPort, BYTE ucPosition);
extern void ScalerDpAuxRxSetSyncTablePayloadID_EXINT0(EnumInputPort enumInputPort, BYTE ucPosition, BYTE ucPayloadID);
extern BYTE ScalerDpAuxRxCheckAddPositionLegal_EXINT0(EnumInputPort enumInputPort, BYTE ucIDStartPosition);
extern void ScalerDpAuxRxSortStreamPositionReg_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxReplaceStart0IfPayloadIDExisted_8b10b_EXINT0(EnumInputPort enumInputPort, BYTE ucIDStartPosition, BYTE ucPayloadID);
extern BYTE ScalerDpAuxRxGetExistedIDLength_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID, BYTE ucStartPosition);
extern void ScalerDpAuxRxSetActSignalCodingType_EXINT0(EnumInputPort enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpAuxRxMstProtocolEnableHandler_EXINT0(EnumInputPort enumInputPort);
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern void ScalerDpAuxRxManualModeSetting_T2INT(EnumDpAuxManualModeSetting enumSetting);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpAuxRxPRModeDpcdSetting(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxPRModeFlagStatus(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxDpcdPRModeErrorStateUpdate(EnumInputPort enumInputPort, EnumPRModeErrorStatus enumPRModeErrorStatus);
extern void ScalerDpAuxRxDpcdPRModeStatusUpdate(EnumInputPort enumInputPort, EnumPRModeStatus enumPRModeStatus);
extern void ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(EnumInputPort enumInputPort, EnumPRModeErrorStatus enumPRModeErrorStatus);
extern bit ScalerDpAuxRxGetPRModeDpcdCrcEnable_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpAuxRxPRModeGetDpcd001B0hValue(EnumInputPort enumInputPort);
extern bit ScalerDpAuxRxGetPRModeDpcdCrcEnable(EnumInputPort enumInputPort);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpAuxRxAuxlessAlpmDpcdSetting(EnumInputPort enumInputPort);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern void ScalerDpAuxRxHdrDpcdSetting(EnumInputPort enumInputPort);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRxFreesyncDpcdSetting(EnumInputPort enumInputPort);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpAuxRxAdaptiveSyncDpcdSetting(EnumInputPort enumInputPort);
#endif

extern void ScalerDpAuxRxDpcdSetting_00008h(EnumInputPort enumInputPort);
extern void ScalerDpAuxRxDpcdSetting_00009h(EnumInputPort enumInputPort);

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
extern void ScalerDpAuxRxHblankingModifyDpcdTimingInfoReset(EnumInputPort enumInputPort);
#endif
#endif
