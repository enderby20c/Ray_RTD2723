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
// ID Code      : ScalerBusSb2Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// SB2 Related Enum
//--------------------------------------------------
//R-bus Timeout threshold
typedef enum
{
    _RBUS_TO_TH_128 = 0x00,  /*!< Rbus Timeout threshold 128 cycles    */
    _RBUS_TO_TH_256 = 0x01,  /*!< Rbus Timeout threshold 256 cycles    */
    _RBUS_TO_TH_512 = 0x02,  /*!< Rbus Timeout threshold 512 cycles    */
    _RBUS_TO_TH_1024 = 0x03,  /*!< Rbus Timeout threshold 1024 cycles    */
    _RBUS_TO_TH_2048 = 0x04,  /*!< Rbus Timeout threshold 2048 cycles    */
    _RBUS_TO_TH_4096 = 0x05,  /*!< Rbus Timeout threshold 4096 cycles    */
    _RBUS_TO_TH_8192 = 0x06,  /*!< Rbus Timeout threshold 8192 cycles    */
    _RBUS_TO_TH_16384 = 0x07,  /*!< Rbus Timeout threshold 16384 cycles    */
}EnumCpuBusSB2RBusTimeoutTH;

//Debug
typedef enum
{
    _DBG_ADDR_IDX_0 = 0x00,  /*!< debug address set Index 0    */
    _DBG_ADDR_IDX_1 = 0x01,  /*!< debug address set Index 1    */
    _DBG_ADDR_IDX_2 = 0x02,  /*!< debug address set Index 2    */
    _DBG_ADDR_IDX_3 = 0x03,  /*!< debug address set Index 3    */
    _DBG_ADDR_IDX_4 = 0x04,  /*!< debug address set Index 4    */
    _DBG_ADDR_IDX_5 = 0x05,  /*!< debug address set Index 5    */
    _DBG_ADDR_IDX_6 = 0x06,  /*!< debug address set Index 6    */
    _DBG_ADDR_IDX_7 = 0x07,  /*!< debug address set Index 7    */

    _DBG_ADDR_IDX_8 = 0x08,  /*!< debug address set Index 8    */
    _DBG_ADDR_IDX_9 = 0x09,  /*!< debug address set Index 9    */
    _DBG_ADDR_IDX_10 = 0x0A,  /*!< debug address set Index 10    */
    _DBG_ADDR_IDX_11 = 0x0B,  /*!< debug address set Index 11    */
    _DBG_ADDR_IDX_12 = 0x0C,  /*!< debug address set Index 12    */
    _DBG_ADDR_IDX_13 = 0x0D,  /*!< debug address set Index 13    */
    _DBG_ADDR_IDX_14 = 0x0E,  /*!< debug address set Index 14    */
    _DBG_ADDR_IDX_15 = 0x0F,  /*!< debug address set Index 15    */
}EnumCpuBusSB2DbgAddrIdx;

typedef enum
{
    _DBG_DISABLE = (2UL << 0),  /*!< debug disable    */
    _DBG_ENABLE = (3UL << 0),  /*!< debug enable    */
}EnumCpuBusSB2DbgEnable;

typedef enum
{
    _DBG_MNT_DATA = (5UL << 2),  /*!< debug monitor data    */
    _DBG_MNT_INSTRUCTION = (6UL << 2),  /*!< debug monitor instruction    */
    _DBG_MNT_BOTH_TYPE = (7UL << 2),  /*!< debug monitor both data && instruction    */
}EnumCpuBusSB2DbgMntType;

typedef enum
{
    _DBG_MNT_RD = (5UL << 5),  /*!< debug monitor read    */
    _DBG_MNT_WRT = (6UL << 5),  /*!< debug monitor write    */
    _DBG_MNT_BOTH_RW = (7UL << 5),  /*!< debug monitor both read && write    */
}EnumCpuBusSB2DbgMntRW;

typedef enum
{
    _DBG_CHK_SCPU = (3UL << 8),  /*!< check debug address for SCPU    */
    _DBG_CHK_KCPU = (3UL << 16),  /*!< check debug address for KCPU    */
    _DBG_CHK_SCPU_KCPU = (_DBG_CHK_SCPU | _DBG_CHK_KCPU),  /*!< check debug address for both KCPU && SCPU    */
}EnumCpuBusSB2DbgChkCpu;

typedef enum
{
    _SECTION_IDX_1 = ((1UL) << 0),  /*!< RBus Write Protection Section Index#1    */
    _SECTION_IDX_2 = ((1UL) << 2),  /*!< RBus Write Protection Section Index#2    */
    _SECTION_IDX_3 = ((1UL) << 4),  /*!< RBus Write Protection Section Index#3    */
    _SECTION_IDX_4 = ((1UL) << 6),  /*!< RBus Write Protection Section Index#4    */
}EnumCpuRbusWrtProtectSectionIdx;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
extern void ScalerBusSb2TrapError_AddDebugInfo(void);
#endif
extern bit ScalerBusSb2TrapError_IRQHandler(void);

extern void ScalerBusSb2Initial(void);
// SB2 HAL State Structure definition

// KCPU(security/boot CPU):DW8051
// SCPU(system cpu):CPU32
// Interrupt: connect to NMI

// Page A20010 && A20016
// Hardware Semaphore Ctrl (idx=_SEMAPHORE_0~_SEMAPHORE_8)
extern DWORD ScalerBusSb2AcquireHwBinarySemaphore(EnumCpuBusSB2SemaphoreIdx enumIdx);
extern void ScalerBusSb2ReleaseHwBinarySemaphore(EnumCpuBusSB2SemaphoreIdx enumIdx);
extern void ScalerBusSb2SetHwBinarySemaphoreValue(EnumCpuBusSB2SemaphoreIdx enumIdx, DWORD ulSemValue);
extern DWORD ScalerBusSb2GetHwBinarySemaphoreValue(EnumCpuBusSB2SemaphoreIdx enumIdx);

// RBUS/RBUS1/RBUSD timeout Switch Option
// RBUS
extern void ScalerBusSb2RBusEnableTimeout(void);
extern void ScalerBusSb2RBusDisableTimeout(void);
extern void ScalerBusSb2RBusSetTimeoutThreshold(EnumCpuBusSB2RBusTimeoutTH enumTH);
// RBUS1
extern void ScalerBusSb2RBus1EnableTimeout(void);
extern void ScalerBusSb2RBus1DisableTimeout(void);
extern void ScalerBusSb2RBus1SetTimeoutThreshold(EnumCpuBusSB2RBusTimeoutTH enumTH);
// RBUSD
extern void ScalerBusSb2RBusdEnableTimeout(void);
extern void ScalerBusSb2RBusdDisableTimeout(void);
extern void ScalerBusSb2RBusdSetTimeoutThreshold(EnumCpuBusSB2RBusTimeoutTH enumTH);

// Invalid Address Access Option
// SCPU
extern void ScalerBusSb2ScpuInvalidAccessIntEnable(void);
extern void ScalerBusSb2ScpuInvalidAccessIntDisable(void);
extern DWORD ScalerBusSb2ScpuInvalidAccessIntGetStatus(void);
extern void ScalerBusSb2ScpuInvalidAccessIntAckStatus(void);
// KCPU
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerBusSb2KcpuInvalidAccessIntEnable(void);
extern void ScalerBusSb2KcpuInvalidAccessIntDisable(void);
extern DWORD ScalerBusSb2KcpuInvalidAccessIntGetStatus(void);
extern void ScalerBusSb2KcpuInvalidAccessIntAckStatus(void);
#endif

extern DWORD ScalerBusSb2GetInvalidAccessAddress(void);

// DEBUG

// Page A20013 && A20014
// Performance counters
// SCPU
extern DWORD ScalerBusSb2ScpuGetAccRBusReqLatencyCycles(void);
extern DWORD ScalerBusSb2ScpuGetMaxRBusReqLatency(void);
extern DWORD ScalerBusSb2ScpuGetTotalRBusReqNum(void);
extern void ScalerBusSb2ScpuStartRBusMonitor(void);
extern void ScalerBusSb2ScpuStopRBusMonitor(void);
extern DWORD ScalerBusSb2ScpuGetRBusMonitorStatus(void);
// KCPU
extern DWORD ScalerBusSb2KcpuGetAccRBusReqLatencyCycles(void);
extern DWORD ScalerBusSb2KcpuGetMaxRBusReqLatency(void);
extern DWORD ScalerBusSb2KcpuGetTotalRBusReqNum(void);
extern void ScalerBusSb2KcpuStartRBusMonitor(void);
extern void ScalerBusSb2KcpuStopRBusMonitor(void);
extern DWORD ScalerBusSb2KcpuGetRBusMonitorStatus(void);

// Page A20014
// Software Debug mode
extern void ScalerBusSb2SetDebugAddressSet(EnumCpuBusSB2DbgAddrIdx enumIdx, DWORD ulAddrStart, DWORD ulAddrEnd, EnumCpuBusSB2DbgEnable enumDbgEn, EnumCpuBusSB2DbgMntType enumDbgMntType, EnumCpuBusSB2DbgMntRW enumDbgMntRW, EnumCpuBusSB2DbgChkCpu enumDbgChkCpu);
extern void ScalerBusSb2DisableDebugAddressSet(EnumCpuBusSB2DbgAddrIdx enumIdx);
extern void ScalerBusSb2EnableDebugAddressSet(EnumCpuBusSB2DbgAddrIdx enumIdx);
extern DWORD ScalerBusSb2GetStartDebugAddress(EnumCpuBusSB2DbgAddrIdx enumIdx);
extern DWORD ScalerBusSb2GetEndDebugAddress(EnumCpuBusSB2DbgAddrIdx enumIdx);
// SCPU
extern DWORD ScalerBusSb2ScpuGetTrapAddress(void);
extern DWORD ScalerBusSb2ScpuIsTrapWriteAccess(void);
extern DWORD ScalerBusSb2ScpuIsTrapDataAccess(void);
extern void ScalerBusSb2ScpuTrapAddressLatchFirstOne(void);
extern void ScalerBusSb2ScpuTrapAddressLatchLastOne(void);

extern void ScalerBusSb2ScpuTrapAddressIntEnable(void);
extern void ScalerBusSb2ScpuTrapAddressIntDisable(void);
extern DWORD ScalerBusSb2ScpuTrapAddressIntGetStatus(void);
extern void ScalerBusSb2ScpuTrapAddressIntAckStatus(void);

extern void ScalerBusSb2ScpuTrapAddressNegIntEnable(void);
extern void ScalerBusSb2ScpuTrapAddressNegIntDisable(void);
extern DWORD ScalerBusSb2ScpuTrapAddressNegIntGetStatus(void);
extern void ScalerBusSb2ScpuTrapAddressNegIntAckStatus(void);
// KCPU
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern DWORD ScalerBusSb2KcpuGetTrapAddress(void);
#endif
extern DWORD ScalerBusSb2KcpuIsTrapWriteAccess(void);
extern DWORD ScalerBusSb2KcpuIsTrapDataAccess(void);
extern void ScalerBusSb2KcpuTrapAddressLatchFirstOne(void);
extern void ScalerBusSb2KcpuTrapAddressLatchLastOne(void);

extern void ScalerBusSb2KcpuTrapAddressIntEnable(void);
extern void ScalerBusSb2KcpuTrapAddressIntDisable(void);
extern DWORD ScalerBusSb2KcpuTrapAddressIntGetStatus(void);
extern void ScalerBusSb2KcpuTrapAddressIntAckStatus(void);

extern void ScalerBusSb2KcpuTrapAddressNegIntEnable(void);
extern void ScalerBusSb2KcpuTrapAddressNegIntDisable(void);

// Page A20016
// Auto-compare Rbus read data (like read data value monitor)
extern void ScalerBusSb2RBusCrcLatchEnable(void);
extern void ScalerBusSb2RBusCrcLatchDisable(void);
extern void ScalerBusSb2RBusCrcSetExpectedValue(DWORD ulExpectedValue);
extern DWORD ScalerBusSb2RBusCrcGetExpectedValue(void);
extern DWORD ScalerBusSb2RBusCrcCheckResultMatch(void);
extern void ScalerBusSb2RBusCrcSetMask(DWORD ulMaskValue);
extern DWORD ScalerBusSb2RBusCrcGetMask(void);

// Page A20019
// Security
/*
//Can Only be accessed by KCPU(8to32 via DW8051) interface
void ScalerBusSb2KcpuProtectRegion1Enable(void);
void ScalerBusSb2KcpuProtectRegion1Disable(void);
void ScalerBusSb2KcpuProtectRegion1SetRange(DWORD ulProtAddrStart, DWORD ulProtAddrEnd);

void ScalerBusSb2KcpuProtectRegion2Enable(void);
void ScalerBusSb2KcpuProtectRegion2Disable(void);
void ScalerBusSb2KcpuProtectRegion2SetRange(DWORD ulProtAddrStart, DWORD ulProtAddrEnd);
*/

// Page A20019
// Check if SCPU access ProtectRegion set by KCPU
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerBusSb2ScpuIllegalAccessSecurRegionIntEnable(void);
extern void ScalerBusSb2ScpuIllegalAccessSecurRegionIntDisable(void);
extern DWORD ScalerBusSb2ScpuIllegalAccessSecurRegionIntGetStatus(void);
extern void ScalerBusSb2ScpuIllegalAccessSecurRegionIntAckStatus(void);
extern DWORD ScalerBusSb2ScpuIllegalAccessSecurRegionIntGetTrapAddress(void);
#endif

// Page A2001A
// RBUS Blocking
extern void ScalerBusSb2ScpuRbusWrtProtectSectionEnable(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx);
extern void ScalerBusSb2ScpuRbusWrtProtectSectionDisable(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx);
extern void ScalerBusSb2ScpuRbusWrtProtectSectionSetRange(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx, DWORD ulProtAddrStart, DWORD ulProtAddrEnd);
extern DWORD ScalerBusSb2RbusWrtProtectSectionIntFromSCPU(void);
extern DWORD ScalerBusSb2RbusWrtProtectSectionIntFromKCPU(void);
extern DWORD ScalerBusSb2RbusWrtProtectSectionIntFromBW32(void);
extern DWORD ScalerBusSb2RbusWrtProtectSectionIntGetTrapAddress(void);
extern void ScalerBusSb2RbusWrtProtectSectionIntEnable(void);
extern void ScalerBusSb2RbusWrtProtectSectionIntDisable(void);
extern DWORD ScalerBusSb2RbusWrtProtectSectionIntGetStatus(void);
extern void ScalerBusSb2RbusWrtProtectSectionIntAckStatus(void);
#endif
