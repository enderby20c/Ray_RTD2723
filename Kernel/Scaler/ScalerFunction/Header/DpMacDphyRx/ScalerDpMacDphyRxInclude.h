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
// ID Code      : ScalerDpMacDphyRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of Port Info
//--------------------------------------------------
#define _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS                          3

//--------------------------------------------------
// Definitions of Mst Timeslot Shift Direction
//--------------------------------------------------
#define _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_DOWN                         1
#define _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_UP                           0

//--------------------------------------------------
// DP MAC MAX Bandwidth (MByte/s)
//--------------------------------------------------
#define _DP_MAC_DPHY_RX_MAX_BW_8B10B                                ((DWORD)_HW_DP_MAX_PIXEL_CLOCK * _HW_DP_MAC_MAX_PIXEL_MODE_8B10B * _HW_DP_MAC_MAX_COLOR_DEPTH_8B10B * 3 / 8)
#define _DP_MAC_DPHY_RX_MAX_BW_128B132B                             ((DWORD)_HW_DP_MAX_PIXEL_CLOCK * _HW_DP_MAC_MAX_PIXEL_MODE_128B132B * _HW_DP_MAC_MAX_COLOR_DEPTH_128B132B * 3 / 8)

//--------------------------------------------------
// DP MAC MAX PBN
//--------------------------------------------------
#define _DP_MAC_DPHY_RX_MAX_PBN_8B10B                               ((DWORD)_DP_MAC_DPHY_RX_MAX_BW_8B10B * 64 / 54)
#define _DP_MAC_DPHY_RX_MAX_PBN_128B132B                            ((DWORD)_DP_MAC_DPHY_RX_MAX_BW_128B132B * 64 / 54)

#define GET_DP_MAC_DPHY_RX_PBN_PER_TIME_SLOT(x, y)                  (((x) / 2) * (y))

//--------------------------------------------------
// Definitions of Rx MAC MST Enable Macro
//--------------------------------------------------
#define GET_DP_MAC_DPHY_MST_RX_REG_ENABLE(x)                        (ScalerDpMacDphyRxGetMstProtocolEnable(x))
#define GET_DP_MAC_DPHY_MST_RX_REG_ENABLE_EXINT(x)                  (ScalerDpMacDphyRxGetMstProtocolEnable_EXINT0(x))

//--------------------------------------------------
// DP Rx ACT Set Setting
//--------------------------------------------------
#define GET_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT()                   (g_pbDpMacDphyRxManualForceSetAct[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS])
#define SET_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT()                   (g_pbDpMacDphyRxManualForceSetAct[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS] = _TRUE)
#define CLR_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT()                   (g_pbDpMacDphyRxManualForceSetAct[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS] = _FALSE)

//--------------------------------------------------
// Definitions of MST Load New Stream Payload
//--------------------------------------------------
#define SET_DP_MAC_DPHY_RX_LOAD_NEW_STREAM_PAYLOAD()                (ScalerDpMacDphyRxLoadNewStreamPayload(GET_DP_RX_BASE_PORT()))
#define SET_DP_MAC_DPHY_RX_LOAD_NEW_STREAM_PAYLOAD_EXINT()          (ScalerDpMacDphyRxLoadNewStreamPayload_EXINT0(GET_DP_RX_BASE_PORT()))

//--------------------------------------------------
// DP Rx ID Mapping
//---------------------------------------------
#define GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(x, y)               (g_ppucDpMacDphyRxStreamToIdMapping[((x) - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS][y])
#define SET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(x, y, z)            (g_ppucDpMacDphyRxStreamToIdMapping[((x) - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS][y] = (z))

//--------------------------------------------------
// Definitions of MST Stream Backup Infomation
//--------------------------------------------------
#define SET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(x, y)                   (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_Source[x] = (y))
#define GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(x)                      (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_Source[x])
#define CLR_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE()                       (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1SourceChange = _FALSE)
#define SET_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE()                       (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1SourceChange = _TRUE)
#define GET_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE()                       (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1SourceChange)
#define SET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(x, y)           (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_Start[x] = (y))
#define GET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(x)              (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_Start[x])
#define SET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(x, y)             (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_End[x] = (y))
#define GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(x)                (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_End[x])
#define SET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(x, y)                   (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_Status[x] = (y))
#define GET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(x)                      (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].pucSTx_Status[x])
#define CLR_DP_MAC_DPHY_RX_ST_POSITION_CHANGE()                     (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1TimeSlotChange = _FALSE)
#define SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE()                     (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1TimeSlotChange = _TRUE)
#define GET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE()                     (g_pstDpMacDphyRxStreamInfoBackup[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1TimeSlotChange)
//--------------------------------------------------
// Definitions of MST Stream Related Macro
//--------------------------------------------------

// 8B10B 128B132B: For Reset use
#define GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_8B10B()                (ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_BASE_PORT(), PB5_02_STHD_CTRL_2))
#define GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_8B10B_EXINT()          (ScalerDpMacDphyRxGetPagedAddress_EXINT0(GET_DP_RX_BASE_PORT(), PB5_02_STHD_CTRL_2))
#define GET_DP_MAC_DPHY_RX_REG_ST_SOURCE_ADDR_8B10B()               (ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_BASE_PORT(), PB5_12_SOURCE_SEL_0))
#define GET_DP_MAC_DPHY_RX_REG_ST_SOURCE_ADDR_8B10B_EXINT()         (ScalerDpMacDphyRxGetPagedAddress_EXINT0(GET_DP_RX_BASE_PORT(), PB5_12_SOURCE_SEL_0))
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B()             (ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_BASE_PORT(), P9D_02_STHD_CTRL_2))
#define GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B_EXINT()       (ScalerDpMacDphyRxGetPagedAddress_EXINT0(GET_DP_RX_BASE_PORT(), P9D_02_STHD_CTRL_2))
#define GET_DP_MAC_DPHY_RX_REG_ST_SOURCE_ADDR_128B132B()            (ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_BASE_PORT(), P9D_12_SOURCE_SEL_0))
#define GET_DP_MAC_DPHY_RX_REG_ST_SOURCE_ADDR_128B132B_EXINT()      (ScalerDpMacDphyRxGetPagedAddress_EXINT0(GET_DP_RX_BASE_PORT(), P9D_12_SOURCE_SEL_0))
#endif

#define GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR()                      (ScalerDpMacDphyRxGetStreamRegAddress(GET_DP_RX_BASE_PORT()))
#define GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_EXINT()                (ScalerDpMacDphyRxGetStreamRegAddress_EXINT0(GET_DP_RX_BASE_PORT()))
#define GET_DP_MAC_DPHY_RX_REG_ST_SOURCE_ADDR()                     (ScalerDpMacDphyRxGetSourceRegAddress(GET_DP_RX_BASE_PORT()))
#define GET_DP_MAC_DPHY_RX_REG_ST_SOURCE_ADDR_EXINT()               (ScalerDpMacDphyRxGetSourceRegAddress_EXINT0(GET_DP_RX_BASE_PORT()))

#define GET_DP_MAC_DPHY_RX_REG_ST_START_POSITION(x)                 (ScalerGetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR() + ((x) << 1)), 0x3F))
#define GET_DP_MAC_DPHY_RX_REG_ST_START_POSITION_EXINT(x)           (ScalerGetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_EXINT() + ((x) << 1)), 0x3F))
#define SET_DP_MAC_DPHY_RX_REG_ST_START_POSITION(x, y)              {ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR() + ((x) << 1)), ~0x3F, (y));}
#define SET_DP_MAC_DPHY_RX_REG_ST_START_POSITION_EXINT(x, y)        {ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_EXINT() + ((x) << 1)), ~0x3F, (y));}

#define GET_DP_MAC_DPHY_RX_REG_ST_END_POSITION(x)                   (ScalerGetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR() + ((x) << 1) + 1), 0x3F))
#define SET_DP_MAC_DPHY_RX_REG_ST_END_POSITION(x, y)                {ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR() + ((x) << 1) + 1), ~0x3F, (y));}
#define SET_DP_MAC_DPHY_RX_REG_ST_END_POSITION_EXINT(x, y)          {ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_EXINT() + ((x) << 1) + 1), ~0x3F, (y));}

#define GET_DP_MAC_DPHY_RX_REG_ST_STATUS(x, y)                      (ScalerDpMacDphyRxGetStreamStatusReg((x), (y)))
#define SET_DP_MAC_DPHY_RX_REG_ST_STATUS(x, y)                      (ScalerDpMacDphyRxSetStreamStatusReg(GET_DP_RX_BASE_PORT(), (x), (y)))
#define SET_DP_MAC_DPHY_RX_REG_ST_STATUS_EXINT(x, y)                (ScalerDpMacDphyRxSetStreamStatusReg_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y)))

#define GET_DP_MAC_DPHY_RX_ST_TIMESLOT_LENGTH(x)                    (GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(x) - GET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(x) + 1)

//--------------------------------------------------
// DP DPHY IRQ Flag
//--------------------------------------------------
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_DPHY_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_1A_ADI_DP_IRQ8, _BIT3) == _BIT3)
#define GET_DP_MAC_DPHY_RX0_DPHY_GLOBAL_LOW_PRIORITY_IRQ_FLAG()     (ScalerGetBit_EXINT(P6F_1A_ADI_DP_IRQ8, _BIT0) == _BIT0)
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_DPHY_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_1A_ADI_DP_IRQ8, _BIT4) == _BIT4)
#define GET_DP_MAC_DPHY_RX1_DPHY_GLOBAL_LOW_PRIORITY_IRQ_FLAG()     (ScalerGetBit_EXINT(P6F_1A_ADI_DP_IRQ8, _BIT1) == _BIT1)
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_DPHY_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_1A_ADI_DP_IRQ8, _BIT5) == _BIT5)
#define GET_DP_MAC_DPHY_RX2_DPHY_GLOBAL_LOW_PRIORITY_IRQ_FLAG()     (ScalerGetBit_EXINT(P6F_1A_ADI_DP_IRQ8, _BIT2) == _BIT2)
#endif

#define GET_DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY_SUPPORT()    (_DISABLE)

//--------------------------------------------------
// DP MAC DPHY Power Cut Status Flag
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX0_POWER_CUT_STATUS()                      (g_stDpMacDphyRxPowerStatus.b1DpMacDphyRx0PowerCutStatus)
#define SET_DP_MAC_DPHY_RX0_POWER_CUT_STATUS(x)                     (g_stDpMacDphyRxPowerStatus.b1DpMacDphyRx0PowerCutStatus = (x))
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS()                      (g_stDpMacDphyRxPowerStatus.b1DpMacDphyRx1PowerCutStatus)
#define SET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS(x)                     (g_stDpMacDphyRxPowerStatus.b1DpMacDphyRx1PowerCutStatus = (x))
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
#define GET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS()                      (g_stDpMacDphyRxPowerStatus.b1DpMacDphyRx2PowerCutStatus)
#define SET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS(x)                     (g_stDpMacDphyRxPowerStatus.b1DpMacDphyRx2PowerCutStatus = (x))
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************



#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP MST Backup Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DpMstEnableBackup : 1;
    BYTE ucDpMacRxLinkRateBackup;
    BYTE ucDpMacRxLaneCountBackup;
    BYTE ucDpMacRxCodingTypeBackup;

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE ucDpMacRxFecReadyBackup;
#endif
} StructDPMacRxMiscInfo;
#endif

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_ADD_PAYLOAD_ID,
    _DP_MODIFY_PAYLOAD_ID_TABLE,
    _DP_CLEAR_PAYLOAD_ID_TABLE,
    _DP_RX_NONE_ACTION,
} EnumSyncPayloadTableAction;

//--------------------------------------------------
// Struct for Stream Info Backup
//--------------------------------------------------
typedef struct
{
    BYTE pucSTx_Source[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE pucSTx_Start[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE pucSTx_End[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE pucSTx_Status[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE b1SourceChange : 1;
    BYTE b1TimeSlotChange : 1;
}StructRxStreamInfoBackup;

//--------------------------------------------------
// Enumerations of Multi-Stream Stream Number
//--------------------------------------------------
typedef enum
{
    _DP_ST_1 = 0x00,
    _DP_ST_2 = 0x01,
    _DP_ST_3 = 0x02,
    _DP_ST_4 = 0x03,
    _DP_ST_5 = 0x04,
    _DP_ST_6 = 0x05,
#if(_HW_DP_MST_ST_SOURCE_COUNT == _DP_MST_8_STREAM)
    _DP_ST_7 = 0x06,
    _DP_ST_8 = 0x07,
#endif
    _DP_ST_NONE,
    _DP_ST_END = (_DP_ST_NONE - 1),
    _DP_ST_DAISY_START = _DP_ST_1,
    _DP_ST_DAISY_END = _HW_DP_MST_DAISY_ST_NUM_MAX - 1,
} EnumDpStreamNum;

//--------------------------------------------------
// Enumerations of MST Port
//--------------------------------------------------
typedef enum
{
    _DP_PORT0 = 0x00,
    _DP_PORT1 = 0x01,
    _DP_PORT2 = 0x02,
    _DP_PORT3 = 0x03,
    _DP_PORT4 = 0x04,
    _DP_PORT5 = 0x05,
    _DP_PORT6 = 0x06,
    _DP_PORT7 = 0x07,
    _DP_PORT8 = 0x08,
    _DP_PORT9 = 0x09,
    _DP_PORT10 = 0x0A,
    _DP_PORT11 = 0x0B,
    _DP_PORT12 = 0x0C,
    _DP_PORT13 = 0x0D,
    _DP_PORT14 = 0x0E,
    _DP_PORT15 = 0x0F,
} EnumDpMstPort;

//--------------------------------------------------
// Enumerations of MST Mac Needed Port
//--------------------------------------------------
typedef enum
{
    _DP_RX_PORT8 = 0x00,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    _DP_RX_PORT9,
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
    _DP_TX_PORT1,
#endif
    _DP_TOTAL_MAC_NEEDED_PORT,
} EnumDpMacNeededPort;

//--------------------------------------------------
// Enumerations of Multi-Stream Source Number
//--------------------------------------------------
typedef enum
{
    _DP_ST_SOURCE1 = 0x00,
    _DP_ST_SOURCE2 = 0x01,
    _DP_ST_SOURCE3 = 0x02,
    _DP_ST_SOURCE4 = 0x03,
    _DP_ST_SOURCE5 = 0x04,
    _DP_ST_SOURCE6 = 0x05,
#if(_HW_DP_MST_ST_SOURCE_COUNT == _DP_MST_8_STREAM)
    _DP_ST_SOURCE7 = 0x06,
    _DP_ST_SOURCE8 = 0x07,
#endif
    _DP_NO_SOURCE,
    _DP_ST_SOURCE_END = (_DP_NO_SOURCE - 1),
    _DP_ST_SOURCE_DAISY_START = _DP_ST_SOURCE1,
    _DP_ST_SOURCE_DAISY_END = _HW_DP_MST_DAISY_ST_NUM_MAX - 1,
} EnumDpStreamSourceNum;

//--------------------------------------------------
// Stream AES setting
//--------------------------------------------------
typedef enum
{
    _HDCP2_CIPHER_AES0 = 0x00,                       // 00
    _HDCP2_CIPHER_AES1 = _BIT0,                      // 01
    _HDCP2_CIPHER_AES2 = _BIT1,                      // 10
    _HDCP2_CIPHER_NONE = 0xFF,                       // 11
} EnumDpHdcp2AESCipherSet;

//--------------------------------------------------
// Stream Type setting
//--------------------------------------------------
typedef enum
{
    _HDCP2_TYPE_0 = 0x00,
    _HDCP2_TYPE_1 = 0x01,
    _HDCP2_TYPE_2 = 0x02,
} EnumDpHdcp2AESType;

//--------------------------------------------------
// Enumerations of HDCP1.4 R0 Type
//--------------------------------------------------
typedef enum
{
    _HDCP_14_R0_MSB,
    _HDCP_14_R0_LSB,
} EnumDpHdcp14R0Type;

//--------------------------------------------------
// Struct for DP Hdcp Cipher Backup Info
//--------------------------------------------------
typedef struct
{
    BYTE pucDpMacRxRiv[8];
    BYTE pucDpMacRxAESCipher[16];
    BYTE pucDpMacRxSTType[2];
}
StructDpMacDphyRxHdcpCipherBackupInfo;

//--------------------------------------------------
// Struct for DP MAC DPHY Power Status
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
typedef struct
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    BYTE b1DpMacDphyRx0PowerCutStatus : 1;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    BYTE b1DpMacDphyRx1PowerCutStatus : 1;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    BYTE b1DpMacDphyRx2PowerCutStatus : 1;
#endif
}StructDpMacDphyRxPowerStatus;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
// MST Rx stream
extern volatile BYTE g_ppucDpMacDphyRxStreamToIdMapping[][_HW_DP_MST_ST_SOURCE_COUNT];
extern volatile StructRxStreamInfoBackup g_pstDpMacDphyRxStreamInfoBackup[];
extern volatile bit g_pbDpMacDphyRxManualForceSetAct[];
extern volatile EnumDpStreamNum g_ppenumDpMacDphyRxStreamAllocateInfo[][_DP_TOTAL_MAC_NEEDED_PORT];
#endif

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern StructDpMacDphyRxPowerStatus g_stDpMacDphyRxPowerStatus;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacDphyRxInitial(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacDphyRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);
extern bit ScalerDpMacDphyRxGetPowerCutFlagStatus(EnumInputPort enumInputPort);
#endif

extern void ScalerDpMacDphyRxDigitalPhyInitial(EnumInputPort enumInputPort);

extern bit ScalerDpMacDphyRxPhyCtsTp1Check(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxPhyCtsTp2Check(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxScrambleSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxDecodeErrorCountReset(EnumInputPort enumInputPort, EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern bit ScalerDpMacDphyRxDecodeErrorCountLaneMeasure(EnumInputPort enumInputPort, WORD usErrorCriteria, BYTE ucDpMacLaneNumber);
extern WORD ScalerDpMacDphyRxGetDecodeErrorCount(EnumInputPort enumInputPort, BYTE ucDpMacLaneNumber);
extern void ScalerDpMacDphyRxLaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRxDigitalPhyReset(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLaneCountSet(EnumInputPort enumInputPort, BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRxSetCommaDetect(EnumInputPort enumInputPort, bit bEn);
extern BYTE ScalerDpMacDphyRxGetLaneMuxMapping(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern void ScalerDpMacDphyRxClkSelect(EnumInputPort enumInputPort, EnumDpMacClkSelect enumClkSelect);
extern void ScalerDpMacDphyRxChannelFifoReset(EnumInputPort enumInputPort);

extern WORD ScalerDpMacDphyRxGetPagedAddress(EnumInputPort enumInputPort, WORD usMac0Addr);
extern void ScalerDpMacDphyRxHdcp14ResetProc(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxHdcpReAuthStatusCheck(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLinkIntegrityEnable(void);
extern void ScalerDpMacDphyRxHdcpDownLoadKey(bit bEnable);
extern void ScalerDpMacDphyRxHdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray);
extern void ScalerDpMacDphyRxCheckHdcpCpirqStatus(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxCpIRQ(EnumInputPort enumInputPort, EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpMacDphyRxHdcpCheckValid(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxHdcpCheckEnabled(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxSetHdcpMode(EnumInputPort enumInputPort, EnumHDCPType enumHDCPType);
extern bit ScalerDpMacDphyRxHdcpCheck(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcpSramClkGate(EnumInputPort enumInputPort, bit bEnable);

extern void ScalerDpMacDphyRxConfigMstOrSstMode(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxGetMstProtocolEnable(EnumInputPort enumInputPort);

extern void ScalerDpMacDphyRxPowerDataRecover(EnumInputPort enumInputPort);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRxFecDecode(EnumInputPort enumInputPort, BYTE ucFECDecode);
extern BYTE ScalerDpMacDphyRxGetFecDecodeStatus(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxFecDecodeCheck(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxFecInitial(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxFecLaneSelect(EnumInputPort enumInputPort, BYTE ucFECLane);
extern void ScalerDpMacDphyRxFecErrorCountSelect(EnumInputPort enumInputPort, BYTE ucFECSelect);
extern void ScalerDpMacDphyRxResetFecErrorCount(EnumInputPort enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRxClearMstInfoBackup(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxGetMstInfoBackup(EnumInputPort enumInputPort);
#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpMacDphyRxHdcpStreamStatus(EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort, BYTE ucDaisyStreamCnt);
extern bit ScalerDpMacDphyRxHdcpTimeSlotEncStatus(EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort, BYTE ucTimeSlot);
extern BYTE ScalerDpMacDphyRxHdcpTimeSlotEncValue(EnumInputPort enumInputPort, BYTE ucTimeSlot);
extern WORD ScalerDpMacDphyRxStreamStartAddress(EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort, BYTE ucDaisyStreamCnt);
#endif
#endif  // End of (_DP_MST_SUPPORT == _ON)


extern DWORD ScalerDpMacDphyRxSignalDetectMeasureCount(EnumInputPort enumInputPort, BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern bit ScalerDpMacDphyRxSignalCheck(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxCDRCheck(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxAlignCheck(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxDecodeCheck(EnumInputPort enumInputPort);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRxHdcp2ResetProc(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxClrHdcp2CipherBackupInfo(EnumInputPort enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpMacDphyRxHdcpDetectLvp(EnumInputPort enumInputPort);
extern EnumDpHdcp2AESType ScalerDpMacDphyRxHdcp2GetStxType(EnumInputPort enumInputPort, BYTE ucStreamId);
extern EnumDpHdcp2AESType ScalerDpMacDphyRxHdcp2GetAESCipherType(EnumDpHdcp2AESCipherSet enumDpHdcp2AESCipherSet);
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
extern bit ScalerDpMacDphyRxHdcp14Auth1Check(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp14WriteShaInput(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp14LoadShaToDpcd(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp14FakeAuthenProc(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxHdcpCheckLvp(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHDCPAuthShaRun(EnumInputPort enumInputPort, bit bIsFirst);
extern BYTE ScalerDpMacDphyRxHdcp14GetM0(EnumInputPort enumInputPort, BYTE ucIndex);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
// GENERAL
extern void ScalerDpMacDphyRxMstReset(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxGetPBN(EnumDpLinkRate enumDpLinkRate, EnumDpLaneCount enumDpLaneCount, BYTE ucAvailableTimeSlot);
extern WORD ScalerDpMacDphyRxGetPBNPerTimeSlot(EnumDpLinkRate enumDpLinkRate, EnumDpLaneCount enumDpLaneCount);

// DPRX MST STREAM
extern void ScalerDpMacDphyRxRestoreSourceMuxBackupToReg(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxRestorePositionBackupToRegAndLoad(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxSetSourceMuxReg(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxResetSourceMuxReg(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetStreamPositionReg_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpMacDphyRxCheckIDExisted_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID);
extern EnumDpStreamNum ScalerDpMacDphyRxSearchMatchStream_EXINT0(EnumInputPort enumInputPort, BYTE ucTargetID);
extern void ScalerDpMacDphyRxResetStreamToIDMapping_EXINT0(EnumInputPort enumInputPort);

extern EnumDpMacNeededPort ScalerDpMacDphyRxGetMstPortToMacNeededPort_EXINT0(EnumDpMstPort enumDpMstPort);
extern void ScalerDpMacDphyRxSetStreamAllocateInfo_EXINT0(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort, EnumDpStreamNum enumDpStreamNum);
extern EnumDpStreamNum ScalerDpMacDphyRxGetStreamAllocateInfo_EXINT0(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort);
extern void ScalerDpMacDphyRxResetStreamAllocateInfo_EXINT0(EnumInputPort enumInputPort);

extern EnumDpStreamNum ScalerDpMacDphyRxGetSourceMuxBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumDpStreamSourceNum);
extern void ScalerDpMacDphyRxSetSourceMuxBackup(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum);
extern void ScalerDpMacDphyRxSetSourceMuxBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum);
extern void ScalerDpMacDphyRxSetStreamStartBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue);
extern void ScalerDpMacDphyRxSetStreamEndBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue);
extern void ScalerDpMacDphyRxSetStreamStatusBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEnable);
extern void ScalerDpMacDphyRxResetSourceMuxBackup_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetStreamStartBackup_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetStreamEndBackup_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetStreamStatusBackup_EXINT0(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxGetStreamRegAddress(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxGetSourceRegAddress(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxGetStreamRegAddress_EXINT0(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxGetSourceRegAddress_EXINT0(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxGetLoadStreamPayloadRegAddress_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxGetStreamStatusReg(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxSetStreamStatusReg(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEn);
extern void ScalerDpMacDphyRxSetStreamStatusReg_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEn);
extern void ScalerDpMacDphyRxSetSourceMuxReg_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxResetSourceMuxReg_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLoadNewStreamPayload(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLoadNewStreamPayload_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxSetStreamAllocateInfo(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort, EnumDpStreamNum enumDpStreamNum);
extern EnumDpStreamNum ScalerDpMacDphyRxGetStreamAllocateInfo(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort);
extern void ScalerDpMacDphyRxResetStreamAllocateInfo(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
extern void ScalerDpMacDphyRxSyncSourceMux(EnumDpMacSel enumDpMacSel, EnumInputPort enumInputPort);
#endif

#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpMacDphyRxAuxlessAlpmClrOccurred(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxAuxlessAlpmGetOccurred(EnumInputPort enumInputPort);
extern WORD ScalerDpMacDphyRxAuxlessAlpmTdrlTime(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxAuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn);
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
extern void ScalerDpMacDphyRxSet8b10bDecErrorWD(EnumInputPort enumInputPort, bit bEn);
extern bit ScalerDpMacDphyRxCheck8b10bDecErrorStatus(EnumInputPort enumInputPort);
#endif


//--------------------------------------------------
// EXINT0 For None Postfix
//--------------------------------------------------
extern void ScalerDpMacDphyRxConfigMstOrSstMode_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxGetMstProtocolEnable_EXINT0(EnumInputPort enumInputPort);

extern void ScalerDpMacDphyRxLaneSwapSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect);
extern void ScalerDpMacDphyRxLaneCountSet_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneCount);
extern void ScalerDpMacDphyRxSetCommaDetect_EXINT0(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpMacDphyRxClkSelect_EXINT0(EnumInputPort enumInputPort, EnumDpMacClkSelect enumClkSelect);
extern DWORD ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern BYTE ScalerDpMacDphyRxTp1Detect_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpMacDphyRxTp1DecodeCheck_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLane);
extern BYTE ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern BYTE ScalerDpMacDphyRxTp3DecodeCheck_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane);

extern void ScalerDpMacDphyRxReset_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxChannelFifoReset_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxDeSkewReset_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxEnhancementControlMode_EXINT0(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpMacDphyRxScramble_EXINT0(EnumInputPort enumInputPort, bit bEn);

extern void ScalerDpMacDphyRxMacResetProc_EXINT0(EnumInputPort enumInputPort);

extern void ScalerDpMacDphyRxSetHdcpMode_EXINT0(EnumInputPort enumInputPort, EnumHDCPType enumHdcpType);

extern void ScalerDpMacDphyRxClearIntegrityFailureFlag_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxSetHdcp14CalR0_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxSetHdcp14Info_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpMacDphyRxGetHdcp14R0_EXINT0(EnumInputPort enumInputPort, EnumDpHdcp14R0Type enumDpHdcp14R0Type);

extern void ScalerDpMacDphyRxPowerDataRecover_EXINT0(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern bit ScalerDpMacDphyRxGetPowerCutCurrentStatus_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxPowerProc_EXINT0(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);
#endif

extern void ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(EnumInputPort enumInputPort, EnumDpMacDecodeMethod enumDpMacDecodeMethod);
extern void ScalerDpMacDphyRxDecodeErrorCountOff_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxErrorCounterUpdate_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxPhyCtsErrorCounterUpdate_EXINT0(EnumInputPort enumInputPort);

extern WORD ScalerDpMacDphyRxGetPagedAddress_EXINT0(EnumInputPort enumInputPort, WORD usMac0Addr);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRxHdcp2ResetProc_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp2EnableLinkIntegrityCheck_EXINT0(bit bEnable, EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp2EnableDecryption_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp2EnableAuthDone_EXINT0(bit bEnable, EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp2SetAESType_EXINT0(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRxFecDecode_EXINT0(EnumInputPort enumInputPort, BYTE ucFECDecode);
extern BYTE ScalerDpMacDphyRxGetFecDecodeStatus_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxFecErrorCountSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucFECSelect);
extern void ScalerDpMacDphyRxFecLaneSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucFECLane);
extern BYTE ScalerDpMacDphyRxFecErrorCountUpdateLowByte_EXINT0(EnumInputPort enumInputPort);
extern BYTE ScalerDpMacDphyRxFecErrorCountUpdateHighByte_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxClearFecErrorCount_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetFecErrorCount_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpMacDphyRxFecDecodeCheck_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxFecEnableAggregatedErrorCount_EXINT0(EnumInputPort enumInputPort, bit bEnable);
#endif

//--------------------------------------------------
// WDINT For None Postfix
//--------------------------------------------------
extern void ScalerDpMacDphyRxSetCommaDetect_WDINT(EnumInputPort enumInputPort, bit bEn);
extern void ScalerDpMacDphyRxClkSelect_WDINT(EnumInputPort enumInputPort, EnumDpMacClkSelect enumClkSelect);
extern bit ScalerDpMacDphyRxDecodeCheck_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxWDTimerEventHpdIrqAssertProc_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxWDTimerEventRebuildPhyProc_WDINT(EnumInputPort enumInputPort);

#if(_DP_RX_FEC_SUPPORT == _ON)
extern void ScalerDpMacDphyRxFecErrorCountSelect_WDINT(EnumInputPort enumInputPort, BYTE ucFECSelect);
extern void ScalerDpMacDphyRxFecLaneSelect_WDINT(EnumInputPort enumInputPort, BYTE ucFECLane);
extern void ScalerDpMacDphyRxFecInitial_WDINT(EnumInputPort enumInputPort);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern WORD ScalerDpMacDphyRxAuxlessAlpmTdrlTime_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxAuxlessAlpmEnable_WDINT(EnumInputPort enumInputPort, bit bEn);
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
extern void ScalerDpMacDphyRxHdcp2EnableLinkIntegrityCheck_WDINT(bit bEnable, EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp2EnableDecryption_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxHdcp2EnableAuthDone_WDINT(bit bEnable, EnumInputPort enumInputPort);
#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
extern void ScalerDpMacDphyRxHdcp2SetRepeaterAESType_WDINT(EnumInputPort enumInputPort);
#endif
#endif
#endif
