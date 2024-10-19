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
// ID Code      : ScalerBW32Interface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_CPU32_BW32_SUPPORT == _ON)
#define _BURST_WRITE32_DATA_ALIGNMENT                           sizeof(StructBW32DataFormat)
#else
#define _BURST_WRITE32_DATA_ALIGNMENT                           4
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HW_CPU32_BW32_SUPPORT == _ON)
typedef struct
{
    DWORD ulBW32_ADDRESS_0;   /*!< Offset: 0x00  BurstWrite Reg Address#0   */
    DWORD ulBW32_DATA_0;      /*!< Offset: 0x04  BurstWrite Reg Data#0      */
    DWORD ulBW32_ADDRESS_1;   /*!< Offset: 0x08  BurstWrite Reg Address#1   */
    DWORD ulBW32_DATA_1;      /*!< Offset: 0x0C  BurstWrite Reg Data#1      */
    DWORD ulBW32_ADDRESS_2;   /*!< Offset: 0x10  BurstWrite Reg Address#2   */
    DWORD ulBW32_DATA_2;      /*!< Offset: 0x14  BurstWrite Reg Data#2      */
    DWORD ulBW32_ADDRESS_3;   /*!< Offset: 0x18  BurstWrite Reg Address#3   */
    DWORD ulBW32_DATA_3;      /*!< Offset: 0x1C  BurstWrite Reg Data#3      */
} StructBW32CmdFormat;

typedef struct
{
    DWORD ulBW32_DATA_0;      /*!< Offset: 0x00  BurstWrite Reg Data#0      */
    DWORD ulBW32_DATA_1;      /*!< Offset: 0x04  BurstWrite Reg Data#1      */
    DWORD ulBW32_DATA_2;      /*!< Offset: 0x08  BurstWrite Reg Data#2      */
    DWORD ulBW32_DATA_3;      /*!< Offset: 0x0C  BurstWrite Reg Data#3      */
    DWORD ulBW32_DATA_4;      /*!< Offset: 0x10  BurstWrite Reg Data#4      */
    DWORD ulBW32_DATA_5;      /*!< Offset: 0x14  BurstWrite Reg Data#5      */
    DWORD ulBW32_DATA_6;      /*!< Offset: 0x18  BurstWrite Reg Data#6      */
    DWORD ulBW32_DATA_7;      /*!< Offset: 0x1C  BurstWrite Reg Data#7      */
} StructBW32DataFormat;

typedef enum
{
    _BW32_EXE_SYNC = 0x00,    /*!< BW32 Cmd execute Sync  */
    _BW32_EXE_ASYNC = 0x01,   /*!< BW32 Cmd execute ASync */
}EnumBW32ExeMode;

typedef enum
{
    _BW32_CMD_FORMAT = 0x00,    /*!< BW32 Cmd Mode  */
    _BW32_DATA_FORMAT = 0x01,   /*!< BW32 Data Mode */
}EnumBW32CmdFormat;

typedef enum
{
    _BW32_CMD0 = 0x00,          /*!< BW32 Cmd0 */
    _BW32_CMD1 = 0x01,          /*!< BW32 Cmd1 */
    _BW32_CMD2 = 0x02,          /*!< BW32 Cmd2 */
    _BW32_CMD_INVALID = 0xFF,   /*!< BW32 Invalid Cmd */
}EnumBW32CmdX;

typedef enum
{
    _BW32_TRIGGER_MANUAL = 0x00,    /*!< BW32 Cmd execute Now  */
    _BW32_TRIGGER_DVS = 0x01,       /*!< BW32 Cmd execute at Next DVS */
    _BW32_TRIGGER_DEN_START = 0x02, /*!< BW32 Cmd execute at Next DEN_START */
    _BW32_TRIGGER_DEN_STOP = 0x04,  /*!< BW32 Cmd execute at Next DEN_STOP */
}EnumBW32TriggerSource;

typedef struct
{
    EnumBW32CmdFormat enumBW32CmdFormat;            /*!< BW32 Command Format(Cmd/Data)      */
    DWORD ulDdrSrcAddr;                             /*!< BW32 Source Table DDR Address      */
    DWORD ulDestRBusdRegAddr;                       /*!< BW32 Dest RBUSD Reg Address        */
    DWORD ulTotalCmdNum;                            /*!< BW32 Total Command Number          */
    bit bAddrAutoInc;                               /*!< Data Mode Address auto increase    */
} StructBW32BaseInfo;

typedef struct
{
    StructBW32BaseInfo stBW32BaseInfo;
    EnumBW32TriggerSource enumBW32TriggerSource;    /*!< BW32 Trigger Source(manual/dvs...) */
} StructBW32CmdInfo;

typedef struct
{
    StructBW32BaseInfo stBW32BaseInfo;
    EnumWaitIDomainEventType enumWaitIDomainEvent;  /*!< I-Domain Specified event           */
    EnumInputDataPath enumInputDataPath;            /*!< I-Domain Data Path                 */
} StructBW32IDomainCmdInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif  // End of #if(_HW_CPU32_BW32_SUPPORT == _ON)
