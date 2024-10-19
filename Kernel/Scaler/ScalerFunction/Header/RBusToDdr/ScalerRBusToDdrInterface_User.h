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
// ID Code      : ScalerRBusToDdrInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define RBUS2DDR_DDR_ARRAY_SIZE(ulTotalRegNum)     ((((ulTotalRegNum) + 7) / 8) * 8)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulRBUS2DDR_DATA_0;      /*!< Offset: 0x00  RBUS to DDR Reg Data#0      */
    DWORD ulRBUS2DDR_DATA_1;      /*!< Offset: 0x04  RBUS to DDR Reg Data#1      */
    DWORD ulRBUS2DDR_DATA_2;      /*!< Offset: 0x08  RBUS to DDR Reg Data#2      */
    DWORD ulRBUS2DDR_DATA_3;      /*!< Offset: 0x0C  RBUS to DDR Reg Data#3      */
    DWORD ulRBUS2DDR_DATA_4;      /*!< Offset: 0x10  RBUS to DDR Reg Data#4      */
    DWORD ulRBUS2DDR_DATA_5;      /*!< Offset: 0x14  RBUS to DDR Reg Data#5      */
    DWORD ulRBUS2DDR_DATA_6;      /*!< Offset: 0x18  RBUS to DDR Reg Data#6      */
    DWORD ulRBUS2DDR_DATA_7;      /*!< Offset: 0x1C  RBUS to DDR Reg Data#7      */
} StructRBus2DdrDataFormat;

typedef enum
{
    _RBUS2DDR_EXE_SYNC = 0x00,    /*!< RBUS2DDR Cmd execute Sync  */
    _RBUS2DDR_EXE_ASYNC = 0x01,   /*!< RBUS2DDR Cmd execute ASync */
}EnumRBus2DdrExeMode;

typedef enum
{
    _RBUS2DDR_CMD0 = 0x00,  /*!< RBUS2DDR Cmd0 */
    _RBUS2DDR_CMD1 = 0x01,  /*!< RBUS2DDR Cmd1 */
    _RBUS2DDR_CMD2 = 0x02,  /*!< RBUS2DDR Cmd2 */
}EnumRBus2DdrCmdX;

typedef enum
{
    _RBUS2DDR_TRIGGER_MANUAL = 0x00,    /*!< RBUS2DDR Cmd execute Now  */
    _RBUS2DDR_TRIGGER_DVS = 0x01,       /*!< RBUS2DDR Cmd execute at Next DVS */
    _RBUS2DDR_TRIGGER_DEN_START = 0x02, /*!< RBUS2DDR Cmd execute at Next DEN_START */
    _RBUS2DDR_TRIGGER_DEN_STOP = 0x04,  /*!< RBUS2DDR Cmd execute at Next DEN_STOP */
}EnumRBus2DdrTriggerSource;

typedef struct
{
    StructRBus2DdrDataFormat * pstRbus2DdrDestAddr;         /*!< DDR Address of RBUS2DDR Destination Address  */
    DWORD ulRBusSrcStartAddress;                            /*!< RBUS2DDR RBUSD Sourec Reg Start Address      */
    DWORD ulTotalRegNum;                                    /*!< Total 32bits Reg Number want to read out     */
    bit bAddrAutoInc;                                       /*!< is Address Auto Increase                     */
} StructRBus2DdrBaseInfo;

typedef struct
{
    StructRBus2DdrBaseInfo stRBus2DdrBaseInfo;
    EnumRBus2DdrTriggerSource enumRBus2DdrTriggerSource;    /*!< RBUS2DDR trigger source(manual/dvs...)       */
} StructRBus2DdrCmdInfo;

typedef struct
{
    StructRBus2DdrBaseInfo stRBus2DdrBaseInfo;
    EnumWaitIDomainEventType enumWaitIDomainEvent;          /*!< I-Domain Specified event           */
    EnumInputDataPath enumInputDataPath;                    /*!< I-Domain Data Path                 */
} StructRBus2DdrIDomainCmdInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
