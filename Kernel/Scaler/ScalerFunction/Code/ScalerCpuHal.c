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
// ID Code      : ScalerCpuHal.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "CpuHal/ScalerCpuHal.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
volatile DWORD g_ulCpuHalMainCpuPendSVEventCnt;
#endif

#if(_SCPU_SUPPORT == _ON)
volatile DWORD g_ulCpuHalSecondCpuPendSVEventCnt;
#endif

#if((_HW_CPU32_KCPU_HAVE_DCACHE == _TRUE) && (_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR == _TRUE))
// Defined variable array size of D_Cache_Line imitate writeback operation
__attribute__((aligned(_HW_CPU32_KCPU_DCACHE_LINE_SIZE_IN_BYTE), section(".ddr_data.g_pulCpuHalKcpuDCacheChkBuf")))
volatile DWORD g_pulCpuHalKcpuDCacheChkBuf[(_HW_CPU32_KCPU_DCACHE_LINE_SIZE_IN_BYTE / 4)];

__attribute__((section(".fast_data.g_usCpuHalKcpuDCacheChkCnt")))
WORD g_usCpuHalKcpuDCacheChkCnt;
#endif

#if((_HW_CPU32_SCPU_HAVE_DCACHE == _TRUE) && (_HW_CPU32_SCPU_MEMORYMAP_ACCESS_DDR == _TRUE) && (_SCPU_SUPPORT == _ON))
// Defined variable array size of D_Cache_Line imitate writeback operation
__attribute__((aligned(_HW_CPU32_SCPU_DCACHE_LINE_SIZE_IN_BYTE), section(".ddr_data.g_pulCpuHalScpuDCacheChkBuf")))
volatile DWORD g_pulCpuHalScpuDCacheChkBuf[(_HW_CPU32_SCPU_DCACHE_LINE_SIZE_IN_BYTE / 4)];

__attribute__((section(".fast_data.g_usCpuHalScpuDCacheChkCnt")))
WORD g_usCpuHalScpuDCacheChkCnt;
#endif

volatile BYTE g_pucCpuHalShareResourceFlag[_RESOURCE_LOCK_ID_MAX];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :  Sets the priority grouping field (preemption priority and subpriority)
//                  using the required unlock sequence.
// Input Value  :  ulPrioritygroup: The priority grouping bits length.
//                  This parameter can be one of the following values:
//                  @arg _NVIC_PRIORITYGROUP_0: 0 bits for preemption priority
//                                             4 bits for subpriority
//                  @arg _NVIC_PRIORITYGROUP_1: 1 bits for preemption priority
//                                             3 bits for subpriority
//                  @arg _NVIC_PRIORITYGROUP_2: 2 bits for preemption priority
//                                             2 bits for subpriority
//                  @arg _NVIC_PRIORITYGROUP_3: 3 bits for preemption priority
//                                             1 bits for subpriority
//                  @arg _NVIC_PRIORITYGROUP_4: 4 bits for preemption priority
//                                             0 bits for subpriority
//          NOTE:   When the _NVIC_PRIORITYGROUP_0 is selected, IRQ preemption is no more possible.
//                  The pending IRQ priority will be managed only by the subpriority.
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetPrioritygrouping(DWORD ulPrioritygroup)
{
    // Check the parameters
    ASSERT(IS_NVIC_PRIORITY_GROUP(ulPrioritygroup));

    // Set the PRIGROUP[10:8] bits according to the ulPrioritygroup parameter value
    NVIC_SetPriorityGrouping(ulPrioritygroup);
}

//--------------------------------------------------
// Description  : Sets the priority of an interrupt.
// Input Value  : enumIRQn --> External interrupt number.
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
//                ulPreemptPriority --> The preemption priority for the IRQn channel.
//                  This parameter can be a value between 0 and 15
//                  A lower priority value indicates a higher priority
//                ulSubPriority --> the subpriority level for the IRQ channel.
//                  This parameter can be a value between 0 and 15
//                  A lower priority value indicates a higher priority.
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetPriority(EnumIRQnType enumIRQn, DWORD ulPreemptPriority)
{
    // Check the parameters
    ASSERT(IS_NVIC_PREEMPTION_PRIORITY(ulPreemptPriority));

    NVIC_SetPriority(enumIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), ulPreemptPriority, 0));
    ASM_DSB();
    ASM_ISB();
}

//--------------------------------------------------
// Description  :  Enables a device specific interrupt in the NVIC interrupt controller.
//          NOTE:   To configure interrupts priority correctly, the NVIC_PRIORITYGROUPConfig()
//                  function should be called before.
// Input Value  :  IRQn External interrupt number.
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                 (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalEnableIRQ(EnumIRQnType enumIRQn)
{
    // Check the parameters
    ASSERT(IS_NVIC_DEVICE_IRQ(enumIRQn));

    // Clear Pending Flag of IRQn
    NVIC_ClearPendingIRQ(enumIRQn);

    // Enable interrupt
    NVIC_EnableIRQ(enumIRQn);
}

//--------------------------------------------------
// Description  :  Disables a device specific interrupt in the NVIC interrupt controller.
// Input Value  :  IRQn External interrupt number.
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalDisableIRQ(EnumIRQnType enumIRQn)
{
    // Check the parameters
    ASSERT(IS_NVIC_DEVICE_IRQ(enumIRQn));

    // Disable interrupt
    NVIC_DisableIRQ(enumIRQn);
    ASM_DSB();
    ASM_ISB();
}

//--------------------------------------------------
// Description  :  Initiates a system reset request to reset the MCU.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSystemReset(void)
{
    // System Reset
    NVIC_SystemReset();
}

//--------------------------------------------------
// Description  :  Initializes the System Timer and its interrupt, and starts the System Tick Timer.
//                  Counter is in free running mode to generate periodic interrupts.
// Input Value  :  TicksNumb: Specifies the ticks Number of ticks between two interrupts.
// Output Value : status:  - 0  Function succeeded.
//                           - 1  Function failed.
//--------------------------------------------------
DWORD ScalerCpuHalSystickConfig(DWORD ulCountUS)
{
    DWORD ulTicksNumb = ((ulCountUS * ScalerGlobalCtrlGetEclkClockRate()) / (1000 * _HW_CPU32_TO_SYSTICK_CLK_DIV));
    SET_TARGET_SYSTICK_US(ulCountUS);
    return SYSTICK_CONFIG(ulTicksNumb);
}

//--------------------------------------------------
// Description  :  Invalidate I-Cache
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalResetInstructionCache(void)
{
    RESET_I_CACHE();
}

//--------------------------------------------------
// Description  : clean and Invalidate D-Cache
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalResetDataCache(void)
{
    // clean && invalid data cache
    RESET_D_CACHE();
}

#if(_HW_CPU32_CACHED_DDR == _TRUE)
//--------------------------------------------------
// Description  : wait DDR sync complete
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalWaitDdrSyncDone(void)
{
    DISABLE_D_CACHE();

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    // min mclk = 533M, 8 * 500 * 1.88ns = 7.52us
    // use 10us as timeout count
    g_usCpuHalKcpuDCacheChkCnt = ((WORD)ScalerMcuGet1usDelayCnt() * 10);

    g_pulCpuHalKcpuDCacheChkBuf[0] = 1;

    while((g_pulCpuHalKcpuDCacheChkBuf[0] != 1) && (g_usCpuHalKcpuDCacheChkCnt != 0))
    {
        g_usCpuHalKcpuDCacheChkCnt--;
    }

    g_pulCpuHalKcpuDCacheChkBuf[0] = 0;
#else
    // min mclk = 533M, 8 * 500 * 1.88ns = 7.52us
    // use 10us as timeout count
    g_usCpuHalScpuDCacheChkCnt = ((WORD)ScalerMcuGet1usDelayCnt() * 10);

    g_pulCpuHalScpuDCacheChkBuf[0] = 1;

    while((g_pulCpuHalScpuDCacheChkBuf[0] != 1) && (g_usCpuHalScpuDCacheChkCnt != 0))
    {
        g_usCpuHalScpuDCacheChkCnt--;
    }

    g_pulCpuHalScpuDCacheChkBuf[0] = 0;
#endif

    ENABLE_D_CACHE();
}
#endif


//--------------------------------------------------
// Description  :  Clean D-Cache (force sync Data Cache content to external Memory)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalCleanDataCache(void)
{
#if(_HW_CPU32_CPU_HAVE_DCACHE == _TRUE)

    // sync data cache
    CLEAN_D_CACHE();

#if(_HW_CPU32_CACHED_DDR == _TRUE)
    if(ScalerMemoryGetPowerControlStatus() == _ON)
    {
        if(CPU32_GET_GLOBAL_IRQ_STATUS() == _ENABLE)
        {
            CPU32_DISABLE_GLOBAL_IRQ();

            ScalerCpuHalWaitDdrSyncDone();

            CPU32_ENABLE_GLOBAL_IRQ();
        }
        else
        {
            ScalerCpuHalWaitDdrSyncDone();
        }
    }
#endif
#endif
}

//--------------------------------------------------
// Description  :  Enable and Reset I-Cache && D-Cache (use MPU0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalEnableICacheDCache(void)
{
    // invalid inst. cache
    ScalerCpuHalResetInstructionCache();

    // clean and invalid data cache
    ScalerCpuHalResetDataCache();

    // enable inst. && data cache
    ENABLE_I_D_CACHE();

    MPU_SETUP_CPU32_USE_REGION();
}


//--------------------------------------------------
// Description  : Setup ITCM access attribute  (use MPU2)
// Input Value  : ulMpuRegionRwPermission --> CPU32 MPU Region Permission Attributes (_MPU_REGION_RW_PRIVILEGED_ONLY, _MPU_REGION_RW_ALL, _MPU_REGION_R_ONLY_PRIVILEGED_ONLY, _MPU_REGION_R_ONLY_ALL)
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetupItcmMemoryAttribute(EnumCpu32MpuAccessPermission enumCpu32MpuAccessPermission)
{
    enumCpu32MpuAccessPermission = enumCpu32MpuAccessPermission;
    MPU_SETUP_ITCM_REGION(enumCpu32MpuAccessPermission);
}

//--------------------------------------------------
// Description  : Setup MPU for Application Memory Layout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetupMPUs(void)
{
    CACHE_CONTROL_INIT();

    ScalerCpuHalCleanDataCache();

    // MPU0: Enable I-Cache && D-Cache using Attr0
    ScalerCpuHalEnableICacheDCache();

    // MPU2: Non-Cache && Privileged r/w for ITCM Region
    ScalerCpuHalSetupItcmMemoryAttribute(_MPU_REGION_RW_PRIVILEGED_ONLY);
}

//--------------------------------------------------
// Description  : Gets the priority grouping field from the NVIC Interrupt Controller.
// Input Value  : None
// Output Value : Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
//--------------------------------------------------
DWORD ScalerCpuHalGetPrioritygrouping(void)
{
    // Get the PRIGROUP[10:8] field value
    return NVIC_GetPriorityGrouping();
}

//--------------------------------------------------
// Description  : Gets the priority of an interrupt.
// Input Value  : enumIRQn --> External interrupt number.
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : Pointer on the Preemptive priority value
//--------------------------------------------------
DWORD ScalerCpuHalGetPriority(EnumIRQnType enumIRQn)
{
    DWORD ulSubPriority = 0;
    DWORD ulPriority = 0;
    // Get priority for CPU32 system or device specific interrupts
    NVIC_DecodePriority(NVIC_GetPriority(enumIRQn), NVIC_GetPriorityGrouping(), &ulPriority, &ulSubPriority);
    return ulPriority;
}

//--------------------------------------------------
// Description  :  Sets Pending bit of an external interrupt.
// Input Value  :  enumIRQn --> External interrupt number
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetPendingIRQ(EnumIRQnType enumIRQn)
{
    // Check the parameters
    ASSERT(IS_NVIC_DEVICE_IRQ(enumIRQn));

    // Set interrupt pending
    NVIC_SetPendingIRQ(enumIRQn);
}

//--------------------------------------------------
// Description  :  Gets Pending Interrupt (reads the pending register in the NVIC
//                  and returns the pending bit for the specified interrupt).
// Input Value  :  enumIRQn --> External interrupt number.
//                   This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : status--> - 0  Interrupt status is not pending.
//                          - 1  Interrupt status is pending.
//--------------------------------------------------
DWORD ScalerCpuHalGetPendingIRQ(EnumIRQnType enumIRQn)
{
    // Check the parameters
    ASSERT(IS_NVIC_DEVICE_IRQ(enumIRQn));

    // Return 1 if pending else 0
    return NVIC_GetPendingIRQ(enumIRQn);
}

//--------------------------------------------------
// Description  : Clears the pending bit of an external interrupt.
// Input Value  : enumIRQn External interrupt number.
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalClearPendingIRQ(EnumIRQnType enumIRQn)
{
    // Check the parameters
    ASSERT(IS_NVIC_DEVICE_IRQ(enumIRQn));

    // Clear pending interrupt
    NVIC_ClearPendingIRQ(enumIRQn);
}

//--------------------------------------------------
// Description  : Gets active interrupt ( reads the active register in NVIC and returns the active bit).
// Input Value  : enumIRQn --> External interrupt number
//                  This parameter can be an enumerator of EnumIRQnType enumeration
//                  (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (rtk32tm9xx.h))
// Output Value : status --> - 0  Interrupt status is not pending.
//                           - 1  Interrupt status is pending.
//--------------------------------------------------
DWORD ScalerCpuHalGetActive(EnumIRQnType enumIRQn)
{
    // Check the parameters
    ASSERT(IS_NVIC_DEVICE_IRQ(enumIRQn));

    // Return 1 if active else 0
    return NVIC_GetActive(enumIRQn);
}

//--------------------------------------------------
// Description  : Acquire SyncFlag Access Right
// Input Value  : enumShareResourceID --> Share Resource ID
//                ulTO10usCnt --> wait timeout (count by 10us)
// Output Value : Acquire Status(_TRUE:succerr , _FALSE:Fail)
//--------------------------------------------------
bit ScalerCpuHalResourceAcquire(EnumCpu32ResourceID enumResourceID, DWORD ulTO10usCnt)
{
    EnumCpu32ResourceLockID enumResourceLockID = GET_RESOURCE_LOCK_ID(enumResourceID);

    if(enumResourceLockID >= _RESOURCE_LOCK_ID_MAX)
    {
        return _FALSE;
    }

    do
    {
        if(g_pucCpuHalShareResourceFlag[enumResourceLockID] == 0)
        {
#if(_SCPU_SUPPORT == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(ScalerCpuCtrlCheckScpuActive() != _TRUE)
            {
                g_pucCpuHalShareResourceFlag[enumResourceLockID] = 0xFF;
                return _TRUE;
            }
            else
#endif
            {
                EnumCpuBusSB2SemaphoreIdx enumSemaphoreIdx = GET_RESOURCE_SEMAPHORE(enumResourceID);

                if(ScalerBusSb2AcquireHwBinarySemaphore(enumSemaphoreIdx) != 0)
                {
                    // Double Check if ResourceLock Flag still be 0
                    if(g_pucCpuHalShareResourceFlag[enumResourceLockID] == 0)
                    {
                        // Acquire HW semaphore success
                        g_pucCpuHalShareResourceFlag[enumResourceLockID] = 0xFF;
                        ScalerBusSb2ReleaseHwBinarySemaphore(enumSemaphoreIdx);
                        return _TRUE;
                    }
                    else
                    {
                        // ResourceLock Flag already be qccupied by other CPU/task
                        ScalerBusSb2ReleaseHwBinarySemaphore(enumSemaphoreIdx);
                    }
                }
            }
#else
            g_pucCpuHalShareResourceFlag[enumResourceLockID] = 0xFF;
            return _TRUE;
#endif
        }
        DELAY_10US();
    }
    while(ulTO10usCnt-- != 0);

    return _FALSE;
}

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
//--------------------------------------------------
// Description  : trigger Main CPU SW0 INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetMainCpuSw0IRQ(void)
{
    g_ulCpuHalMainCpuPendSVEventCnt++;
    SET_SW_INT0();
}
#endif

#if(_SCPU_SUPPORT == _ON)
//--------------------------------------------------
// Description  : trigger Second CPU SW0 INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuHalSetSecondCpuSw0IRQ(void)
{
    g_ulCpuHalSecondCpuPendSVEventCnt++;
    SET_SCPU_SW_INT0();
}
#endif

//--------------------------------------------------
// Description  : Convert CPU Flash Address to Absolute Physical Flash Address
// Input Value  : ulCpuFlashAddress --> CPU Virtual Flash Address
//                pulPhyFlashAddrPtrAddress --> pointer to Address of Absolute Physical Flash Address Pointer
// Output Value : convert Status(_TRUE:success , _FALSE:Fail)
//--------------------------------------------------
bit ScalerCpuHalGetPhyFlashAddress(DWORD ulCpuFlashAddress, DWORD *pulPhyFlashAddrPtrAddress)
{
    if(ScalerUtilGetAddressType(ulCpuFlashAddress) != _ADDRESS_TYPE_FLASH)
    {
        return _FALSE;
    }
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    *pulPhyFlashAddrPtrAddress = (ulCpuFlashAddress - _KCPU_FLASH_BASE_ADDR + GET_KCPU_FLASH_BANK_OFFSET());
#else
    *pulPhyFlashAddrPtrAddress = (ulCpuFlashAddress - _SCPU_FLASH_BASE_ADDR + GET_SCPU_FLASH_BANK_OFFSET());
#endif
    return _TRUE;
}

//--------------------------------------------------
// Description  : Convert Absolute Physical Flash Address to CPU Virtual Flash Address
// Input Value  : ulPhyFlashAddress --> Absolute Physical Flash Address
//                pulCpuFlashAddrPtrAddress --> pointer to Address of CPU Virtual Flash Address Pointer
// Output Value : convert Status(_TRUE:success , _FALSE:Fail)
//--------------------------------------------------
bit ScalerCpuHalGetCpuFlashAddress(DWORD ulPhyFlashAddress, DWORD *pulCpuFlashAddrPtrAddress)
{
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    DWORD ulKcpuFlashBankOffset = GET_KCPU_FLASH_BANK_OFFSET();
    if(ulPhyFlashAddress < ulKcpuFlashBankOffset)
    {
        return _FALSE;
    }
    *pulCpuFlashAddrPtrAddress = (ulPhyFlashAddress + _KCPU_FLASH_BASE_ADDR - ulKcpuFlashBankOffset);
#else
    DWORD ulScpuFlashBankOffset = GET_SCPU_FLASH_BANK_OFFSET();
    if(ulPhyFlashAddress < ulScpuFlashBankOffset)
    {
        return _FALSE;
    }
    *pulCpuFlashAddrPtrAddress = (ulPhyFlashAddress + _SCPU_FLASH_BASE_ADDR - ulScpuFlashBankOffset);
#endif
    return _TRUE;
}

#if((_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_SCPU_SUPPORT == _TRUE))
//--------------------------------------------------
// Description  : Convert KCPU 32bits Flash Address Pointer to SCPU 32bits Flash Address Pointer
// Input Value  : ulKcpuFlashAddrPtr --> KCPU 32bits Flash Address Pointer
//                pulScpuFlashAddrPtrAddress --> SCPU 32bits Flash Address Pointer's Address
// Output Value : convert Status(_TRUE:success , _FALSE:Fail)
//--------------------------------------------------
bit ScalerCpuHalGetScpuFlashAddressPointer(DWORD ulKcpuFlashAddrPtr, DWORD *pulScpuFlashAddrPtrAddress)
{
    EnumAddressType enumAddressType = ScalerUtilGetAddressType(ulKcpuFlashAddrPtr);
    if(enumAddressType == _ADDRESS_TYPE_FLASH)
    {
        // Convert KCPU 32bits Flash Address to SCPU 32bits Flash Address
        *pulScpuFlashAddrPtrAddress = ((ulKcpuFlashAddrPtr - _KCPU_FLASH_BASE_ADDR + GET_KCPU_FLASH_BANK_OFFSET()) + _SCPU_FLASH_BASE_ADDR - GET_SCPU_FLASH_BANK_OFFSET());
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
//--------------------------------------------------
// Description  : Check Main CPU SW INT0 Pending Event Count
// Input Value  : None
// Output Value : (_TRUE:May have Pending Event need to be process , _FALSE:No Event)
//--------------------------------------------------
bit ScalerCpuHalCheckMainCpuPendSVEventCnt(void)
{
    if(g_ulCpuHalMainCpuPendSVEventCnt == 0)
    {
        return _FALSE;
    }
    if(g_ulCpuHalMainCpuPendSVEventCnt > 0xFF)
    {
        g_ulCpuHalMainCpuPendSVEventCnt = 0;
        return _TRUE;
    }
    --g_ulCpuHalMainCpuPendSVEventCnt;
    return _TRUE;
}
#endif

#if(_SCPU_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Second CPU SW INT0 Pending Event Count
// Input Value  : None
// Output Value : (_TRUE:May have Pending Event need to be process , _FALSE:No Event)
//--------------------------------------------------
bit ScalerCpuHalCheckSecondCpuPendSVEventCnt(void)
{
    if(g_ulCpuHalSecondCpuPendSVEventCnt == 0)
    {
        return _FALSE;
    }
    if(g_ulCpuHalSecondCpuPendSVEventCnt > 0xFF)
    {
        g_ulCpuHalSecondCpuPendSVEventCnt = 0;
        return _TRUE;
    }
    --g_ulCpuHalSecondCpuPendSVEventCnt;
    return _TRUE;
}
#endif
