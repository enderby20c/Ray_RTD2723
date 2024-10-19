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
// ID Code      : MultiCpuHandshake.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enum Def in MultiCpu Handshake Command Type
//--------------------------------------------------
typedef enum
{
    // scaler cpu sync command
    // color
    _SCALER_CPU_SYNC_COLOR_START = 0x00,
    _SCALER_CPU_SYNC_COLOR_LOCAL_DIMMING = 0x01,
    _SCALER_CPU_SYNC_COLOR_ADVANCED_HDR10 = 0x02,
    _SCALER_CPU_SYNC_COLOR_SPI_DIMMING = 0x03,

    _SCALER_CPU_SYNC_COLOR_MAX = 0x1F,

    // gosd
    _SCALER_CPU_SYNC_GOSD_CONTINUOUS = 0x20,
    _SCALER_CPU_SYNC_GOSD_CONTINUOUS_SET_STEP = 0x21,
    _SCALER_CPU_SYNC_GOSD_CONTINUOUS_STEP_CHANGE_POSITION = 0x22,
    _SCALER_CPU_SYNC_GOSD_SET_STATUS = 0x23,

    _SCALER_CPU_SYNC_GOSD_MAX = 0x2F,

    // data access
    _SCALER_CPU_SYNC_READ_DWORD = 0x40,
    _SCALER_CPU_SYNC_WRITE_DWORD = 0x41,
    _SCALER_CPU_SYNC_FLASH_WRITE = 0x42,
    _SCALER_CPU_SYNC_FLASH_PAGE_ERASE = 0x43,

    _SCALER_CPU_SYNC_MAX = 0x5F,

    // system cpu sync command
    _SYSTEM_CPU_SYNC_SHUTDOWN = 0x80,
    _SYSTEM_CPU_SYNC_WD_EVENT = 0x81,
    _SYSTEM_CPU_SYNC_MAX = 0x9F,
} EnumCpuSyncCommand;

typedef enum
{
    // scaler command timeout
    _SCALER_CPU_SYNC_TIMEOUT_NO_WAIT = 0,
    _SCALER_CPU_SYNC_TIMEOUT_INFINITY = 65535,

    // color
    _SCALER_CPU_SYNC_TIMEOUT_COLOR_LOCAL_DIMMING = 100,
    _SCALER_CPU_SYNC_TIMEOUT_COLOR_LOCAL_DIMMING_BACKLIGHT_RESTORE = 10,
    _SCALER_CPU_SYNC_TIMEOUT_COLOR_ADVANCED_HDR10 = 100,
    _SCALER_CPU_SYNC_TIMEOUT_COLOR_ADVANCED_HDR10_APPLY = 5,
    _SCALER_CPU_SYNC_TIMEOUT_COLOR_SPI_DIMMING = 100,

    // gosd
    _SCALER_CPU_SYNC_TIMEOUT_GOSD = 10,

    // data access
    _SCALER_CPU_SYNC_TIMEOUT_READ_DWORD = 10,
    _SCALER_CPU_SYNC_TIMEOUT_WRITE_DWORD = 10,
    _SCALER_CPU_SYNC_TIMEOUT_FLASH_WRITE = 100,

    // system command timeout
    _SYSTEM_CPU_SYNC_TIMEOUT_SHUT_DOWN = 100,
    _SYSTEM_CPU_SYNC_TIMEOUT_WDT_EVENT = 10,
} EnumCpuSyncCommandTimeOut;

//****************************************************************************
// STRUCT
//****************************************************************************
//============================================================================
// CPU Handshake Body Struct Definition
//============================================================================
//--------------------------------------------------
// Write Request Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE pucAddr[4];       // pucAddr[0] : Addr Bit[31:24] , ucAddr[3] : Addr Bit[7:0]
    BYTE pucWriteData[9];  // ucWriteData[0] : Data Bit[31:24], ucAddr[3] : Data Bit[7:0], ucWriteData[4:7] : For Set Bit Use
}StructCpuSyncWriteCmd;

//--------------------------------------------------
// Read Request Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE pucAddr[4];       // pucAddr[0] : Addr Bit[31:24], ucAddr[3] : Addr Bit[7:0]
}StructCpuSyncReadCmd;

typedef struct
{
    BYTE pucReadData[15];  // ucReadData[0] : 1st Data, ucReadData[14] : 15th Data
}StructCpuSyncReadCmdReply;

//--------------------------------------------------
// Flash Write Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE pucAddr[3];       // pucAddr[0] : Addr Bit[23:16], ucAddr[2] : Addr Bit[7:0]
    BYTE ucLength;         // number of write Data
    BYTE pucWriteData[9];  // ucWriteData[0] : 1st Data, ucWriteData[8] : 9th Data
    bit bEnFlashSR;
    bit bDisFlashSR;
}StructCpuSyncFlashWriteCmd;

typedef struct
{
    WORD usBank;
    BYTE ucPage;
}StructCpuSyncFlashErasePageCmd;

typedef struct
{
    BYTE ucWriteStatus;    // _SUCCESS OR _FAIL
}StructCpuSyncFlashWriteCmdReply;

//--------------------------------------------------
// Write XData Request Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE pucAddr[2];       // pucAddr[0]:Addr[15:8]  , ucAddr[1]:Addr[7:0]
    BYTE pucWriteData[11]; // ucWriteData[0] : For Low DWORD Addr, ucWriteData[3] : For High DWORD Addr
}StructCpuSyncWriteXDataCmd;

//--------------------------------------------------
// Read XData Request Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE pucAddr[2];       // pucAddr[0] : Low Byte Addr, ucAddr[1] : High Byte Addr
}StructCpuSyncReadXDataCmd;

//--------------------------------------------------
// Write BIT Request Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE pucAddr[2];       // pucAddr[0] : Addr Bit[15:8], ucAddr[1] : Addr Bit[7:0]
    BYTE ucAssertBit;      // Set bit
    BYTE ucMaskBit;        // Mask bit
}StructCpuSyncWriteXDataBitCmd;

//--------------------------------------------------
// Spi Dimming Base Write Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef enum
{
    _SPI_DIMMING_INIT = 0x01,
    _SPI_DIMMING_BASE_WRITE = 0x02,
    _SPI_DIMMING_MEMCPY = 0x03,
    _SPI_DIMMING_READ_PWM = 0x04,
    _SPI_DIMMING_WRITE_PWM = 0x05,
} EnumSpiDimmingSubCmd;

typedef struct
{
    WORD usUpdSyncTriggerSrc;
}StructCpuSyncSpiDimmingInitCmd;

typedef struct
{
    WORD usPwmToSpiInterface;
    bit bUseDevIndex;
    bit bBypassUpdSyncAsCS;
    WORD usDevIdxOrBcId;
    WORD usSpiStartAddr;
    WORD usSpiWriteByteNum;
    BYTE *pucWriteBuffer;
    WORD usPwmAllZoneValue;
}StructCpuSyncSpiDimmingBaseWriteCmd;

typedef struct
{
    WORD usWriteOffset;
    WORD usWriteByteLength;
}StructCpuSyncSpiDimmingMemcpyCmd;

typedef struct
{
    BYTE ucDevIndex;
    WORD usPwmStartIndex;
    WORD usPwmNum;
}StructCpuSyncSpiDimmingRWPwmCmd;

typedef union
{
    StructCpuSyncSpiDimmingInitCmd stInitCmd;
    StructCpuSyncSpiDimmingBaseWriteCmd stBaseWriteCmd;
    StructCpuSyncSpiDimmingMemcpyCmd stMemcpyCmd;
    StructCpuSyncSpiDimmingRWPwmCmd stRWPwmCmd;
} UnionCpuSyncSpiDimmingSubCmdBody;

typedef struct
{
    BYTE ucSubCmdType;     // SPI Dimming Sub Command Type
    UnionCpuSyncSpiDimmingSubCmdBody unSubCmdBody;
}StructCpuSyncSpiDimmingCmd;



typedef struct
{
    bit bExecuteStatus;    // _SUCCESS OR _FAIL
    DWORD ulMemAddress;
}StructCpuSyncSpiDimmingCmdReply;

//--------------------------------------------------
// GOSD Continuous Step Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    bit bExecuteStatus;    // _SUCCESS OR _FAIL
}StructCpuSyncGosdCmdReply;

typedef struct
{
    BYTE ucDispPlane;
}StructCpuSyncGosdContinuousCmd;

typedef struct
{
    DWORD ulSurfaceId;
    // stWinRect
    WORD usWinRectW;
    WORD usWinRectH;
    WORD usWinRectX;
    WORD usWinRectY;
    // stDispRect
    WORD usDispRectW;
    WORD usDispRectH;
    WORD usDispRectX;
    WORD usDispRectY;
    // stDispInfo
    BYTE ucDisplayOSD;
    // enumDBApply
    BYTE ucDBApply;
    BYTE ucStepIndex;
}StructCpuSyncGosdContinuousSetStepCmd;

typedef struct
{
    // stDispRect.stPosition
    WORD usPositionX;
    WORD usPositionY;
    BYTE ucStepIndex;
    BYTE ucDisplayOSD;
}StructCpuSyncGosdContinuousStepChangePositionCmd;

typedef struct
{
    DWORD ulSurfaceId;
    BYTE ucStatus;
}StructCpuSyncGosdSetSurfaceStatus;

//--------------------------------------------------
// Enum Def in MultiCpu Handshake Command Type
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_PWM_INITIAL = 0x01,
    _LOCAL_DIMMING_BACKLIGHT_RESTORE = 0x02,
    _LOCAL_DIMMING_BACKLIGHT_SEND_ADIM = 0x03,
} EnumLocalDimmingCpu32Stage;

//--------------------------------------------------
// Local Dimming Request Command Struct for MultiCpu Handshake
//--------------------------------------------------

typedef struct
{
    BYTE ucColorLDHistoLutMin;
    BYTE ucStepChangeMode;
} StructCpuSyncColorLocalDimmingAdjust;

typedef struct
{
    BYTE ucSmoothLevel;
    BYTE ucStepLevel;
    BYTE ucColorLDHistoLutMin;
    BYTE ucStepChangeMode;
} StructCpuSyncColorLocalDimmingSmooth;

typedef struct
{
    BYTE ucOSDStepLevel;
} StructCpuSyncColorLocalDimmingOSDStep;

typedef struct
{
    BYTE ucPwmArrayXramAddrL;
    BYTE ucPwmArrayXramAddrH;
} StructCpuSyncColorLocalDimmingStep;

typedef struct
{
    BYTE ucNodeLvGainByteL;
    BYTE ucNodeLvGainByteH;
} StructCpuSyncColorLocalDimmingBoost;

typedef struct
{
    BYTE ucTHDStage;
    BYTE ucHighTHDValue;
    BYTE ucLowTHDValue;
} StructCpuSyncColorLocalDimmingSceneChange;

typedef union
{
    StructCpuSyncColorLocalDimmingAdjust stAdjustData;
    StructCpuSyncColorLocalDimmingSmooth stSmoothData;
    StructCpuSyncColorLocalDimmingStep stStepData;
    StructCpuSyncColorLocalDimmingOSDStep stOSDStepData;
    StructCpuSyncColorLocalDimmingBoost stBoostData;
    StructCpuSyncColorLocalDimmingSceneChange stSceneChangeData;
} UnionCpuSyncColorLocalDimmingSubCmdBody;

typedef struct
{
    BYTE ucSubCmdType;     // Local Dimming Sub Command Type
    UnionCpuSyncColorLocalDimmingSubCmdBody unSubCmdBody;
}StructCpuSyncColorLocalDimmingCmd;

//--------------------------------------------------
// Local Dimming Reply Command Struct for MultiCpu Handshake
//--------------------------------------------------

typedef struct
{
    BYTE pucReadData[15];    // Local Dimming Sub Command Type
}
StructCpuSyncColorLocalDimmingReply;

//--------------------------------------------------
// Enum Def in MultiCpu Handshake Command Type
//--------------------------------------------------
typedef enum
{
    _ADVANCED_HDR10_APPLY = 0x00,
} EnumAdvancedHDR10Cpu32Stage;

typedef struct
{
    BYTE ucSubCmdType;
}StructCpuSyncColorAdvancedHDR10Cmd;

//--------------------------------------------------
// WDT Event Command Struct for MultiCpu Handshake
//--------------------------------------------------
typedef enum
{
    _WD_TIMER_EVENT_ACTIVATE = 0x01,
    _WD_TIMER_EVENT_CANCEL = 0x02,
} EnumWDTimerEventAction;

typedef struct
{
    bit bExecuteStatus;    // _SUCCESS OR _FAIL
}StructCpuSyncWDTimerEventCmdReply;

typedef struct
{
    EnumWDTimerEventAction enumWDTimerEventAction;
    WORD usEventID;
    WORD usTimeMS;
}StructCpuSyncWDTimerEventCmd;

//============================================================================
// CPU Handshake Header Struct Definition
//============================================================================
//--------------------------------------------------
// Command Header Struct for MultiCpu Handshake
//--------------------------------------------------
typedef struct
{
    BYTE ucCmdType;
    BYTE ucCmdSeqNum;
}StructCpuSyncCmdHeader;

//--------------------------------------------------
// Union for HandShake Request Command Body
//--------------------------------------------------
typedef union
{
    // raw-byte access
    BYTE pucData[13];       // ucData[0] : 1st Data, ucData[12] : 13th Data

    // structure access
    StructCpuSyncWriteCmd stWriteCmd;
    StructCpuSyncReadCmd stReadCmd;
    StructCpuSyncWriteXDataCmd stWriteXDataCmd;
    StructCpuSyncReadXDataCmd stReadXDataCmd;
    StructCpuSyncWriteXDataBitCmd stWriteXDataBitCmd;
    StructCpuSyncFlashWriteCmd stFlashWriteCmd;
    StructCpuSyncFlashErasePageCmd stFlashErasePageCmd;

    StructCpuSyncColorLocalDimmingCmd stColorLocalDimmingCmd;
    StructCpuSyncColorAdvancedHDR10Cmd stColorAdvancedHDR10Cmd;
    StructCpuSyncSpiDimmingCmd stCpuSyncSpiDimmingCmd;

    StructCpuSyncGosdContinuousCmd stCpuSyncGosdCmd;
    StructCpuSyncGosdContinuousSetStepCmd stCpuSyncGosdSetStepCmd;
    StructCpuSyncGosdContinuousStepChangePositionCmd stCpuSyncGosdChangePositionCmd;
    StructCpuSyncGosdSetSurfaceStatus stCpuSyncGosdSetSurfaceStatusCmd;

    StructCpuSyncWDTimerEventCmd stCpuSyncWDTimerEventCmd;
}UnionCpuSyncRequestCmdBody;

//--------------------------------------------------
// Union for HandShake Reply Command Body
//--------------------------------------------------
typedef union
{
    StructCpuSyncReadCmdReply stReadReplyCmd;
    StructCpuSyncFlashWriteCmdReply stFlashWriteReplyCmd;
    StructCpuSyncColorLocalDimmingReply stColorLocalDimmingReplyCmd;
    StructCpuSyncSpiDimmingCmdReply stCpuSyncSpiDimmingCmdReply;
    StructCpuSyncGosdCmdReply stCpuSyncGosdCmdReply;
    StructCpuSyncWDTimerEventCmdReply stCpuSyncWDTimerEventCmdReply;
}UnionCpuSyncReplyCmdBody;

//--------------------------------------------------
// CPU Handshake Request Message Struct Definition
//--------------------------------------------------
typedef struct
{
    StructCpuSyncCmdHeader stCmdHeader;
    UnionCpuSyncRequestCmdBody unCmdBody;
}StructCpuSyncRequestCmd;

//--------------------------------------------------
// CPU Handshake Reply Message Struct Definition
//--------------------------------------------------
typedef struct
{
    UnionCpuSyncReplyCmdBody unCmdBody;
    BYTE ucAckCmdSeqNum;
}StructCpuSyncReplyCmd;

