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
// ID Code      : ScalerBusSb2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "BusSb2/ScalerBusSb2.h"

#if(_SCPU_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Add SB2 Bus Error information
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2TrapError_AddDebugInfo(void)
{
    // SB2_KCPU_RBUS_PROTECT_VIOLATION(Handle By SCPU)
    // SB2_RBUS_WRT_PROTECT_VIOLATION(Handle By SCPU)
    if(ScalerBusSb2RbusWrtProtectSectionIntGetStatus() != 0)
    {
        // Access Write Protection Address Range
        g_pulDebugSysBusErrorInfo[0] = _DBG_SYSBUS_ERR_SB2_ACCESS_WRT_PROTECT_SECTION;
        g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA2001A_60_BL_CPU);
        g_pulDebugSysBusErrorInfo[9] = ScalerBusSb2RbusWrtProtectSectionIntGetTrapAddress();
        return;
    }

    if(ScalerBusSb2ScpuInvalidAccessIntGetStatus() != 0)
    {
        // SCPU access invalid address
        g_pulDebugSysBusErrorInfo[0] = _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_INVALID_ADDR;
        g_pulDebugSysBusErrorInfo[8] = ScalerBusSb2GetInvalidAccessAddress();
    }
}
#endif
//--------------------------------------------------
// Description  : SB2 Bus Error Handler.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerBusSb2TrapError_IRQHandler(void)
{
    // SB2_KCPU_RBUS_PROTECT_VIOLATION(Handle By SCPU)
    // SB2_RBUS_WRT_PROTECT_VIOLATION(Handle By SCPU)
    if(ScalerBusSb2RbusWrtProtectSectionIntGetStatus() != 0)
    {
        // Access Write Protection Address Range
        // Ack Flag
        ScalerBusSb2RbusWrtProtectSectionIntAckStatus();
        return _TRUE;
    }

    // SB2_SCPU_RW_RBUS_TIMEOUT
    // SB2_SCPU_RW_RBUSD_TIMEOUT
    if(ScalerBusSb2ScpuInvalidAccessIntGetStatus() != 0)
    {
        // SCPU access invalid address
        ScalerBusSb2ScpuInvalidAccessIntAckStatus();
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Init SB2 related Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2Initial(void)
{
    // RBUS/RBUSD timeout Switch Option
    // RBUS
    ScalerBusSb2RBusSetTimeoutThreshold(_RBUS_TO_TH_16384);
    ScalerBusSb2RBusEnableTimeout();
    // RBUSD
    ScalerBusSb2RBusdSetTimeoutThreshold(_RBUS_TO_TH_16384);
    ScalerBusSb2RBusdEnableTimeout();

    // Invalid Address Access Option
    // SCPU
    ScalerBusSb2ScpuInvalidAccessIntAckStatus();
    ScalerBusSb2ScpuInvalidAccessIntEnable();
    // KCPU (must be setup by KCPU)
    // ScalerBusSb2KcpuInvalidAccessIntAckStatus();
    // ScalerBusSb2KcpuInvalidAccessIntEnable();

    // Debug Trap Address Option
    // SCPU
    ScalerBusSb2ScpuTrapAddressLatchFirstOne();
    ScalerBusSb2ScpuTrapAddressNegIntDisable();
    ScalerBusSb2ScpuTrapAddressIntEnable();
    // KCPU
    ScalerBusSb2KcpuTrapAddressLatchFirstOne();
    ScalerBusSb2KcpuTrapAddressNegIntDisable();
    ScalerBusSb2KcpuTrapAddressIntEnable();

    // RBUS Blocking
    ScalerBusSb2RbusWrtProtectSectionIntDisable();
}

//--------------------------------------------------
// Description  : Acquire HW Binary Semaphore on SB2 (this is a hw support test and set operation)
// Input Value  : None
// Output Value : 0:failed ; 1:success
//--------------------------------------------------
DWORD ScalerBusSb2AcquireHwBinarySemaphore(EnumCpuBusSB2SemaphoreIdx enumIdx)
{
    if(enumIdx == _SEMAPHORE_8)
    {
        return Scaler32GetBit(PA20010_00_HD_SEM, _BIT0);
    }
    else
    {
        return Scaler32GetBit((PA20016_20_HD_SEM_NEW + (enumIdx << 2)), _BIT0);
    }
}

//--------------------------------------------------
// Description  : Release HW Binary Semaphore on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ReleaseHwBinarySemaphore(EnumCpuBusSB2SemaphoreIdx enumIdx)
{
    if(enumIdx == _SEMAPHORE_8)
    {
        Scaler32SetBit(PA20010_00_HD_SEM, ~(_BIT0), (0));
    }
    else
    {
        Scaler32SetBit((PA20016_20_HD_SEM_NEW + (enumIdx << 2)), ~(_BIT0), (0));
    }
}

//--------------------------------------------------
// Description  : Set HW Binary Semaphore's Data on SB2(assume already got control on this semaphore)
// Input Value  : enumIdx --> Semaphore Index
//                ulSemValue --> new Semaphore's Data value(Only[31:1] is valid)
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2SetHwBinarySemaphoreValue(EnumCpuBusSB2SemaphoreIdx enumIdx, DWORD ulSemValue)
{
    // after write,keep locking
    if(enumIdx == _SEMAPHORE_8)
    {
        Scaler32SetDWord(PA20010_00_HD_SEM, (ulSemValue | _BIT0));
    }
    else
    {
        Scaler32SetDWord((PA20016_20_HD_SEM_NEW + (enumIdx << 2)), (ulSemValue | _BIT0));
    }
}

//--------------------------------------------------
// Description  : Get HW Binary Semaphore's Data on SB2(assume already got control on this semaphore)
// Input Value  : None
// Output Value : HW Binary Semaphore's Data value
//--------------------------------------------------
DWORD ScalerBusSb2GetHwBinarySemaphoreValue(EnumCpuBusSB2SemaphoreIdx enumIdx)
{
    // after read,keep locking
    if(enumIdx == _SEMAPHORE_8)
    {
        return Scaler32GetDWord(PA20010_00_HD_SEM);
    }
    else
    {
        return Scaler32GetDWord((PA20016_20_HD_SEM_NEW + (enumIdx << 2)));
    }
}

//--------------------------------------------------
// Description  : Enable RBUS timeout function on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusEnableTimeout(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT4 | _BIT0));
}

//--------------------------------------------------
// Description  : Enable RBUS1 timeout function on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBus1EnableTimeout(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT5 | _BIT0));
}

//--------------------------------------------------
// Description  : Enable RBUSd timeout function on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusdEnableTimeout(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT8 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable RBUS timeout function on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusDisableTimeout(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT4));
}

//--------------------------------------------------
// Description  : Disable RBUS1 timeout function on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBus1DisableTimeout(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT5));
}

//--------------------------------------------------
// Description  : Disable RBUSd timeout function on SB2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusdDisableTimeout(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT8));
}

//--------------------------------------------------
// Description  : Set RBUS timeout threshold on SB2
// Input Value  : th --> Threshold value
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusSetTimeoutThreshold(EnumCpuBusSB2RBusTimeoutTH enumTH)
{
    Scaler32SetBit(PA20010_10_DEBUG_REG, ~(_BIT2 | _BIT1 | _BIT0), enumTH);
}

//--------------------------------------------------
// Description  : Set RBUS1 timeout threshold on SB2
// Input Value  : th --> Threshold value
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBus1SetTimeoutThreshold(EnumCpuBusSB2RBusTimeoutTH enumTH)
{
    Scaler32SetBit(PA20010_10_DEBUG_REG, ~((_BIT2 | _BIT1 | _BIT0) << 3), (enumTH << 3));
}

//--------------------------------------------------
// Description  : Set RBUSd timeout threshold on SB2
// Input Value  : th --> Threshold value
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusdSetTimeoutThreshold(EnumCpuBusSB2RBusTimeoutTH enumTH)
{
    Scaler32SetBit(PA20010_10_DEBUG_REG, ~((_BIT2 | _BIT1 | _BIT0) << 6), (enumTH << 6));
}

//--------------------------------------------------
// Description  : Enable SCPU(CPU32) Invalid Access Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuInvalidAccessIntEnable(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable SCPU(CPU32) Invalid Access Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuInvalidAccessIntDisable(void)
{
    Scaler32SetDWord(PA20010_04_INV_INTEN, (_BIT1));
}

//--------------------------------------------------
// Description  : Get SCPU(CPU32) Invalid Access Interrupt status flag
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2ScpuInvalidAccessIntGetStatus(void)
{
    return Scaler32GetBit(PA20010_08_INV_INTSTAT, _BIT1);
}

//--------------------------------------------------
// Description  : Ack SCPU(CPU32) Invalid Access Interrupt status flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuInvalidAccessIntAckStatus(void)
{
    Scaler32SetDWord(PA20010_08_INV_INTSTAT, _BIT1);
}

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Enable KCPU(8051) Invalid Access Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuInvalidAccessIntEnable(void)
{
    Scaler32SetDWord(PA20019_70_INTEN, (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable KCPU(8051) Invalid Access Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuInvalidAccessIntDisable(void)
{
    Scaler32SetDWord(PA20019_70_INTEN, (_BIT1));
}

//--------------------------------------------------
// Description  : Get KCPU(8051) Invalid Access Interrupt status flag
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2KcpuInvalidAccessIntGetStatus(void)
{
    return Scaler32GetBit(PA20019_74_INTSTAT, _BIT1);
}

//--------------------------------------------------
// Description  : Ack KCPU(8051) Invalid Access Interrupt status flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuInvalidAccessIntAckStatus(void)
{
    Scaler32SetDWord(PA20019_74_INTSTAT, _BIT1);
}
#endif

//--------------------------------------------------
// Description  : Get Address that cause Invalid Access
// Input Value  : None
// Output Value : address of invalid access
//--------------------------------------------------
DWORD ScalerBusSb2GetInvalidAccessAddress(void)
{
    return Scaler32GetDWord(PA20010_0C_INV_ADDR);
}

//--------------------------------------------------
// Description  : Get SCPU(CPU32) Accumulated RBus Request Latency Cycles
// Input Value  : None
// Output Value : AccRBusReqLatencyCycles
//--------------------------------------------------
DWORD ScalerBusSb2ScpuGetAccRBusReqLatencyCycles(void)
{
    return Scaler32GetDWord(PA20014_40_SCPU_RACC);
}

//--------------------------------------------------
// Description  : Get SCPU(CPU32) Maximum RBus Request Latency
// Input Value  : None
// Output Value : Maximum SCPU RBus Request Latency
//--------------------------------------------------
DWORD ScalerBusSb2ScpuGetMaxRBusReqLatency(void)
{
    return (Scaler32GetDWord(PA20014_44_SCPU_RREQ_RLT) >> 24);
}

//--------------------------------------------------
// Description  : Get SCPU(CPU32) Total RBus Request Number
// Input Value  : None
// Output Value : Total SCPU RBus Request Number
//--------------------------------------------------
DWORD ScalerBusSb2ScpuGetTotalRBusReqNum(void)
{
    return (Scaler32GetDWord(PA20014_44_SCPU_RREQ_RLT) & 0x00FFFFFF);
}

//--------------------------------------------------
// Description  : Get KCPU(8051 8to32 Interface) Accumulated RBus Request Latency Cycles
// Input Value  : None
// Output Value : AccRBusReqLatencyCycles
//--------------------------------------------------
DWORD ScalerBusSb2KcpuGetAccRBusReqLatencyCycles(void)
{
    return Scaler32GetDWord(PA20013_20_KCPU_RACC);
}

//--------------------------------------------------
// Description  : Get KCPU(8051 8to32 Interface) Maximum RBus Request Latency
// Input Value  : None
// Output Value : Maximum RBus Request Latency
//--------------------------------------------------
DWORD ScalerBusSb2KcpuGetMaxRBusReqLatency(void)
{
    return (Scaler32GetDWord(PA20013_24_KCPU_RREQ_RLT) >> 24);
}

//--------------------------------------------------
// Description  : Get KCPU(8051 8to32 Interface) Total RBus Request Number
// Input Value  : None
// Output Value : Total RBus Request Number
//--------------------------------------------------
DWORD ScalerBusSb2KcpuGetTotalRBusReqNum(void)
{
    return (Scaler32GetDWord(PA20013_24_KCPU_RREQ_RLT) & 0x00FFFFFF);
}

//--------------------------------------------------
// Description  : Start SCPU(CPU32) RBus Monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuStartRBusMonitor(void)
{
    Scaler32SetDWord(PA20014_00_PC_CTRL, (_BIT9 | _BIT8));
}

//--------------------------------------------------
// Description  : Stop SCPU(CPU32) RBus Monitor (stop acc , num,max related reg update))
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuStopRBusMonitor(void)
{
    Scaler32SetDWord(PA20014_00_PC_CTRL, _BIT9);
}

//--------------------------------------------------
// Description  : Get SCPU(CPU32) RBus Monitor status
// Input Value  : None
// Output Value : 0:stop ; other:started
//--------------------------------------------------
DWORD ScalerBusSb2ScpuGetRBusMonitorStatus(void)
{
    return Scaler32GetBit(PA20014_00_PC_CTRL, _BIT8);
}

//--------------------------------------------------
// Description  : Start KCPU(8051 8to32 Interface) RBus Monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuStartRBusMonitor(void)
{
    Scaler32SetDWord(PA20014_00_PC_CTRL, (_BIT19 | _BIT18));
}

//--------------------------------------------------
// Description  : Stop KCPU(8051 8to32 Interface) RBus Monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuStopRBusMonitor(void)
{
    Scaler32SetDWord(PA20014_00_PC_CTRL, _BIT19);
}

//--------------------------------------------------
// Description  : Get KCPU(8051 8to32 Interface) RBus Monitor status
// Input Value  : None
// Output Value : 0:stop ; other:started
//--------------------------------------------------
DWORD ScalerBusSb2KcpuGetRBusMonitorStatus(void)
{
    return Scaler32GetBit(PA20014_00_PC_CTRL, _BIT18);
}

//--------------------------------------------------
// Description  : Set Debug Address Set
// Input Value  : idx --> index(0~7)
//                addr_start --> start_dbg_address
//                addr_stop --> stop_dbg_address
//                dbg_en --> enable/disable debug
//                dbg_mnt_type --> monitor data/inst/both
//                _DBG_MNT_Rw --> monitor r/w/both
//                dbg_chk_cpu --> check SCPU/KCPU/Both
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2SetDebugAddressSet(EnumCpuBusSB2DbgAddrIdx enumIdx, DWORD ulAddrStart, DWORD ulAddrEnd, EnumCpuBusSB2DbgEnable enumDbgEn, EnumCpuBusSB2DbgMntType enumDbgMntType, EnumCpuBusSB2DbgMntRW enumDbgMntRW, EnumCpuBusSB2DbgChkCpu enumDbgChkCpu)
{
    if(enumIdx < _DBG_ADDR_IDX_8)
    {
        Scaler32SetDWord((PA20014_58_DBG_START + (enumIdx << 2)), ulAddrStart);
        Scaler32SetDWord((PA20014_78_DBG_END + (enumIdx << 2)), ulAddrEnd);
        Scaler32SetDWord((PA20014_98_DBG_CTRL + (enumIdx << 2)), (enumDbgEn | enumDbgMntType | enumDbgMntRW | enumDbgChkCpu));
    }
    else
    {
        DWORD ulIdx = enumIdx - 8;
        Scaler32SetDWord((PA2001A_80_DBG_START2 + (ulIdx << 2)), ulAddrStart);
        Scaler32SetDWord((PA2001A_A0_DBG_END2 + (ulIdx << 2)), ulAddrEnd);
        Scaler32SetDWord((PA2001A_C0_DBG_CTRL3 + (ulIdx << 2)), (enumDbgEn | enumDbgMntType | enumDbgMntRW | enumDbgChkCpu));
    }
}

//--------------------------------------------------
// Description  : Disable Debug Address Set
// Input Value  : idx --> index(0~7)
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2DisableDebugAddressSet(EnumCpuBusSB2DbgAddrIdx enumIdx)
{
    if(enumIdx < _DBG_ADDR_IDX_8)
    {
        Scaler32SetDWord((PA20014_98_DBG_CTRL + (enumIdx << 2)), _DBG_DISABLE);
    }
    else
    {
        Scaler32SetDWord((PA2001A_C0_DBG_CTRL3 + ((enumIdx - 8) << 2)), _DBG_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Enable Debug Address Set
// Input Value  : idx --> index(0~7)
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2EnableDebugAddressSet(EnumCpuBusSB2DbgAddrIdx enumIdx)
{
    if(enumIdx < _DBG_ADDR_IDX_8)
    {
        Scaler32SetDWord((PA20014_98_DBG_CTRL + (enumIdx << 2)), _DBG_ENABLE);
    }
    else
    {
        Scaler32SetDWord((PA2001A_C0_DBG_CTRL3 + ((enumIdx - 8) << 2)), _DBG_ENABLE);
    }
}

//--------------------------------------------------
// Description  : get start Debug Address
// Input Value  : idx --> index(0~7)
// Output Value : start debug address
//--------------------------------------------------
DWORD ScalerBusSb2GetStartDebugAddress(EnumCpuBusSB2DbgAddrIdx enumIdx)
{
    if(enumIdx < _DBG_ADDR_IDX_8)
    {
        return Scaler32GetDWord(PA20014_58_DBG_START + (enumIdx << 2));
    }
    else
    {
        return Scaler32GetDWord(PA2001A_80_DBG_START2 + ((enumIdx - 8) << 2));
    }
}

//--------------------------------------------------
// Description  : get end Debug Address
// Input Value  : idx --> index(0~7)
// Output Value : end debug address
//--------------------------------------------------
DWORD ScalerBusSb2GetEndDebugAddress(EnumCpuBusSB2DbgAddrIdx enumIdx)
{
    if(enumIdx < _DBG_ADDR_IDX_8)
    {
        return Scaler32GetDWord(PA20014_78_DBG_END + (enumIdx << 2));
    }
    else
    {
        return Scaler32GetDWord(PA2001A_A0_DBG_END2 + ((enumIdx - 8) << 2));
    }
}

//--------------------------------------------------
// Description  : get SCPU trap Address
// Input Value  : None
// Output Value : SCPU trap Address
//--------------------------------------------------
DWORD ScalerBusSb2ScpuGetTrapAddress(void)
{
    return Scaler32GetDWord(PA20014_C0_DBG_ADDR);
}

//--------------------------------------------------
// Description  : check SCPU read or write access to trap Address
// Input Value  : None
// Output Value : 1:is write access ; 0:is read access
//--------------------------------------------------
DWORD ScalerBusSb2ScpuIsTrapWriteAccess(void)
{
    return Scaler32GetBit(PA20014_CC_DBG_ADDR1, _BIT3);
}

//--------------------------------------------------
// Description  : check SCPU data or instruction access to trap Address
// Input Value  : None
// Output Value : 1:is data access ; 0:is instruction access
//--------------------------------------------------
DWORD ScalerBusSb2ScpuIsTrapDataAccess(void)
{
    return Scaler32GetBit(PA20014_CC_DBG_ADDR1, _BIT2);
}

//--------------------------------------------------
// Description  : set SCPU only latch first one trap Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressLatchFirstOne(void)
{
    Scaler32SetBit(PA20014_D0_DBG_CTRL2, ~(_BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : set SCPU latch every trap Address (record last one)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressLatchLastOne(void)
{
    Scaler32SetBit(PA20014_D0_DBG_CTRL2, ~(_BIT2), 0);
}

//--------------------------------------------------
// Description  : Enable SCPU trap Address interrupt when address in range SB2_DBG_START[i] ~ SB2_DBG_END[i]-1,i=0~7
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressIntEnable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, (_BIT7 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable SCPU trap Address interrupt when address in range SB2_DBG_START[i] ~ SB2_DBG_END[i]-1,i=0~7
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressIntDisable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT7);
}

//--------------------------------------------------
// Description  : Get SCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2ScpuTrapAddressIntGetStatus(void)
{
    return Scaler32GetBit(PA20014_E0_DBG_INT, _BIT10);
}

//--------------------------------------------------
// Description  : Ack SCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressIntAckStatus(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT10);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Enable SCPU trap Address interrupt when address NOT in range SB2_DBG_START[i] ~ SB2_DBG_END[i]-1,i=0~7
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressNegIntEnable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable SCPU trap Address interrupt when address NOT in range SB2_DBG_START[i] ~ SB2_DBG_END[i]-1,i=0~7
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressNegIntDisable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT1);
}

//--------------------------------------------------
// Description  : Get SCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2ScpuTrapAddressNegIntGetStatus(void)
{
    return Scaler32GetBit(PA20014_E0_DBG_INT, _BIT4);
}

//--------------------------------------------------
// Description  : Ack SCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
void ScalerBusSb2ScpuTrapAddressNegIntAckStatus(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT4);
}

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : get KCPU trap Address
// Input Value  : None
// Output Value : KCPU trap Address
//--------------------------------------------------
DWORD ScalerBusSb2KcpuGetTrapAddress(void)
{
    return Scaler32GetDWord(PA20019_80_DBG_ADDR_KCPU);
}
#endif

//--------------------------------------------------
// Description  : check KCPU read or write access to trap Address
// Input Value  : None
// Output Value : 1:is write access ; 0:is read access
//--------------------------------------------------
DWORD ScalerBusSb2KcpuIsTrapWriteAccess(void)
{
    return Scaler32GetBit(PA20014_CC_DBG_ADDR1, _BIT9);
}

//--------------------------------------------------
// Description  : check KCPU data or instruction access to trap Address
// Input Value  : None
// Output Value : 1:is data access ; 0:is instruction access
//--------------------------------------------------
DWORD ScalerBusSb2KcpuIsTrapDataAccess(void)
{
    return Scaler32GetBit(PA20014_CC_DBG_ADDR1, _BIT8);
}

//--------------------------------------------------
// Description  : set KCPU only latch first one trap Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressLatchFirstOne(void)
{
    Scaler32SetBit(PA20014_D0_DBG_CTRL2, ~(_BIT3), _BIT3);
}

//--------------------------------------------------
// Description  : set KCPU latch every trap Address (record last one)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressLatchLastOne(void)
{
    Scaler32SetBit(PA20014_D0_DBG_CTRL2, ~(_BIT3), 0);
}


//--------------------------------------------------
// Description  : Enable KCPU trap Address interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressIntEnable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, (_BIT19 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable KCPU trap Address interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressIntDisable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT19);
}

//--------------------------------------------------
// Description  : Get KCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2KcpuTrapAddressIntGetStatus(void)
{
    return Scaler32GetBit(PA20014_E0_DBG_INT, _BIT20);
}

//--------------------------------------------------
// Description  : Ack KCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressIntAckStatus(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT20);
}

//--------------------------------------------------
// Description  : Enable KCPU trap Address interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressNegIntEnable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, (_BIT17 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable KCPU trap Address interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressNegIntDisable(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT17);
}

//--------------------------------------------------
// Description  : Get KCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2KcpuTrapAddressNegIntGetStatus(void)
{
    return Scaler32GetBit(PA20014_E0_DBG_INT, _BIT18);
}

//--------------------------------------------------
// Description  : Ack KCPU trap Address interrupt status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
void ScalerBusSb2KcpuTrapAddressNegIntAckStatus(void)
{
    Scaler32SetDWord(PA20014_E0_DBG_INT, _BIT18);
}


//Auto-compare Rbus read data
//--------------------------------------------------
// Description  : Enable RBUS CRC Latch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusCrcLatchEnable(void)
{
    Scaler32SetDWord(PA20016_64_RBUS_CMP_CTRL, _BIT0);
}

//--------------------------------------------------
// Description  : Disable RBUS CRC Latch Function (will auto clear after one read request on RBUS)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusCrcLatchDisable(void)
{
    Scaler32SetDWord(PA20016_64_RBUS_CMP_CTRL, 0);
}

//--------------------------------------------------
// Description  : Set Excepted value when  RBUS CRC Latch read request's return value
// Input Value  : expectedValue --> value we want to get from read request
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusCrcSetExpectedValue(DWORD ulExpectedValue)
{
    Scaler32SetDWord(PA20016_68_RBUS_CMP_DATA, ulExpectedValue);
}

//--------------------------------------------------
// Description  : Get Excepted value we set when  RBUS CRC Latch read request
// Input Value  : None
// Output Value : expect value
//--------------------------------------------------
DWORD ScalerBusSb2RBusCrcGetExpectedValue(void)
{
    return Scaler32GetDWord(PA20016_68_RBUS_CMP_DATA);
}

//--------------------------------------------------
// Description  : check if Excepted value is matched with RBUS CRC Latch read request's return value
// Input Value  : None
// Output Value : 0:Not Matched ; others:Matched
//--------------------------------------------------
DWORD ScalerBusSb2RBusCrcCheckResultMatch(void)
{
    return Scaler32GetDWord(PA20016_6C_RBUS_CMP_RESULT);
}

//--------------------------------------------------
// Description  : Set Mask value of CRC Compare result
// Input Value  : maskValue --> Mask Value
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RBusCrcSetMask(DWORD ulMaskValue)
{
    Scaler32SetDWord(PA20016_70_RBUS_CMP_MASK, ulMaskValue);
}

//--------------------------------------------------
// Description  : Get Mask value of CRC Compare result
// Input Value  : None
// Output Value : Mask Value
//--------------------------------------------------
DWORD ScalerBusSb2RBusCrcGetMask(void)
{
    return Scaler32GetDWord(PA20016_70_RBUS_CMP_MASK);
}

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Enable non-Secure CPU(SCPU) access Secure Region Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuIllegalAccessSecurRegionIntEnable(void)
{
    Scaler32SetBit(PA20019_70_INTEN, ~(_BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : Disable non-Secure CPU(SCPU) access Secure Region Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuIllegalAccessSecurRegionIntDisable(void)
{
    Scaler32SetBit(PA20019_70_INTEN, ~(_BIT2), 0);
}

//--------------------------------------------------
// Description  : Get non-Secure CPU(SCPU) access Secure Region Interrupt status
// Input Value  : None
// Output Value : 0:not happened ; other:happened
//--------------------------------------------------
DWORD ScalerBusSb2ScpuIllegalAccessSecurRegionIntGetStatus(void)
{
    return Scaler32GetBit(PA20019_74_INTSTAT, _BIT2);
}

//--------------------------------------------------
// Description  : Ack non-Secure CPU(SCPU) access Secure Region Interrupt status
// Input Value  : None
// Output Value : 0:not happened ; other:happened
//--------------------------------------------------
void ScalerBusSb2ScpuIllegalAccessSecurRegionIntAckStatus(void)
{
    Scaler32SetDWord(PA20019_74_INTSTAT, _BIT2);
}

//--------------------------------------------------
// Description  : Get non-Secure CPU(SCPU) Trap Address cause Secure Region Interrupt
// Input Value  : None
// Output Value : Trap Address cause Secure Region Interrupt
//--------------------------------------------------
DWORD ScalerBusSb2ScpuIllegalAccessSecurRegionIntGetTrapAddress(void)
{
    return ((_BIT31 | _BIT29) | ((Scaler32GetDWord(PA20019_78_NS_CPU) & 0x07FFFFFF) << 2));
}
#endif

//--------------------------------------------------
// Description  : Enable SCPU RBUS Write Protect Section Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RbusWrtProtectSectionIntEnable(void)
{
    Scaler32SetDWord(PA2001A_64_INTEN_SCPU, (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable SCPU RBUS Write Protect Section Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RbusWrtProtectSectionIntDisable(void)
{
    Scaler32SetDWord(PA2001A_64_INTEN_SCPU, _BIT1);
}

//--------------------------------------------------
// Description  : Get SCPU RBUS Write Protect Section Interrupt Status
// Input Value  : None
// Output Value : 0:not happened ; others:happened
//--------------------------------------------------
DWORD ScalerBusSb2RbusWrtProtectSectionIntGetStatus(void)
{
    return Scaler32GetBit(PA2001A_68_INTSTAT_SCPU, _BIT1);
}

//--------------------------------------------------
// Description  : Ack SCPU RBUS Write Protect Section Interrupt Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2RbusWrtProtectSectionIntAckStatus(void)
{
    Scaler32SetDWord(PA2001A_68_INTSTAT_SCPU, _BIT1);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Check if RBUS Write Protect Section Interrupt Caused by KCPU
// Input Value  : None
// Output Value : 0:no ; others:yes
//--------------------------------------------------
DWORD ScalerBusSb2RbusWrtProtectSectionIntFromKCPU(void)
{
    // KCPU: b'0000
    return ((((Scaler32GetDWord(PA2001A_60_BL_CPU) >> 28) & 0x0F) == 0x00) ? 1 : 0);
}

//--------------------------------------------------
// Description  : Check if RBUS Write Protect Section Interrupt Caused by SCPU
// Input Value  : None
// Output Value : 0:no ; others:yes
//--------------------------------------------------
DWORD ScalerBusSb2RbusWrtProtectSectionIntFromSCPU(void)
{
    // SCPU: b'0101
    return ((((Scaler32GetDWord(PA2001A_60_BL_CPU) >> 28) & 0x0F) == 0x05) ? 1 : 0);
}

//--------------------------------------------------
// Description  : Check if RBUS Write Protect Section Interrupt Caused by BW32 RBUS2DMA
// Input Value  : None
// Output Value : 0:no ; others:yes
//--------------------------------------------------
DWORD ScalerBusSb2RbusWrtProtectSectionIntFromBW32(void)
{
    // BW32: b'1010
    return ((((Scaler32GetDWord(PA2001A_60_BL_CPU) >> 28) & 0x0F) == 0x0A) ? 1 : 0);
}

//--------------------------------------------------
// Description  : Get Trap Address cause  RBUS Write Protect Section Interrupt
// Input Value  : None
// Output Value : Trap Address cause  RBUS Write Protect Section Interrupt
//--------------------------------------------------
DWORD ScalerBusSb2RbusWrtProtectSectionIntGetTrapAddress(void)
{
    return ((_BIT31 | _BIT29) | ((Scaler32GetDWord(PA2001A_60_BL_CPU) & 0x07FFFFFF) << 2));
}

//--------------------------------------------------
// Description  : set SCPU RBUS Write Protect Section1 address range
// Input Value  : ulProtAddrStart --> write protection1 address start
//                ulProtAddrEnd --> write protection1 address end
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuRbusWrtProtectSectionSetRange(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx, DWORD ulProtAddrStart, DWORD ulProtAddrEnd)
{
    switch(enumSectionIdx)
    {
        case _SECTION_IDX_1:
            Scaler32SetDWord(PA2001A_04_RBUS_INVA_ACC_SEC1_START, ulProtAddrStart);
            Scaler32SetDWord(PA2001A_08_RBUS_INVA_ACC_SEC1_END, ulProtAddrEnd);
            break;

        case _SECTION_IDX_2:
            Scaler32SetDWord(PA2001A_0C_RBUS_INVA_ACC_SEC2_START, ulProtAddrStart);
            Scaler32SetDWord(PA2001A_10_RBUS_INVA_ACC_SEC2_END, ulProtAddrEnd);
            break;

        case _SECTION_IDX_3:
            Scaler32SetDWord(PA2001A_14_RBUS_INVA_ACC_SEC3_START, ulProtAddrStart);
            Scaler32SetDWord(PA2001A_18_RBUS_INVA_ACC_SEC3_END, ulProtAddrEnd);
            break;

        case _SECTION_IDX_4:
            Scaler32SetDWord(PA2001A_1C_RBUS_INVA_ACC_SEC4_START, ulProtAddrStart);
            Scaler32SetDWord(PA2001A_20_RBUS_INVA_ACC_SEC4_END, ulProtAddrEnd);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable SCPU RBUS Write Protect Section1 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuRbusWrtProtectSectionEnable(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx)
{
    Scaler32SetBit(PA2001A_00_RBUS_INVA_ACC_CTRL, ~(0), enumSectionIdx);
}

//--------------------------------------------------
// Description  : Disable SCPU RBUS Write Protect Section1 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusSb2ScpuRbusWrtProtectSectionDisable(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx)
{
    Scaler32SetBit(PA2001A_00_RBUS_INVA_ACC_CTRL, ~(enumSectionIdx), 0);
}
#endif
