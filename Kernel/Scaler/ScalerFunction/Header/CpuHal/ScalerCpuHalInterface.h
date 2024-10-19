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
// ID Code      : ScalerCpuHalInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//force set event flag
//clear event flag and no wait(for confirming wait flag is cleared)
//wait for event
#define CPU32_WAIT_FOR_EVENT()                          {\
                                                            __SEV();\
                                                            __WFE();\
                                                            __WFE();\
                                                        }

#define CPU32_WAIT_FOR_INTERRUPT()                      {\
                                                            __DMB();\
                                                            __WFI();\
                                                        }

#define CPU32_GET_INT_PENDING_STATUS()                  (Scaler32GetDWord(INT_PENDING_STATUS_ADDR))

#define RESOURCE_ACQUIRE(enumResourceID, ulTO10usCnt)   (ScalerCpuHalResourceAcquire((enumResourceID), (ulTO10usCnt)))
#define RESOURCE_RELEASE(enumResourceID)                (g_pucCpuHalShareResourceFlag[((enumResourceID) & 0x00FF)] = 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
// CPU32_MPU_Access_Permission CPU32 MPU Region Permission Attributes
typedef enum
{
    _MPU_REGION_RW_PRIVILEGED_ONLY = 0x00,      // Read/write by privileged code only.
    _MPU_REGION_RW_ALL = 0x01,                  // Read/write by any privilege level.
    _MPU_REGION_R_ONLY_PRIVILEGED_ONLY = 0x02,  // Read-only by privileged code only.
    _MPU_REGION_R_ONLY_ALL = 0x03,              // Read-only by any privilege level.
} EnumCpu32MpuAccessPermission;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile BYTE g_pucCpuHalShareResourceFlag[_RESOURCE_LOCK_ID_MAX];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerCpuHalEnableIRQ(EnumIRQnType enumIRQn);
extern void ScalerCpuHalDisableIRQ(EnumIRQnType enumIRQn);
extern void ScalerCpuHalSystemReset(void);
extern DWORD ScalerCpuHalSystickConfig(DWORD ulCountUS);
extern void ScalerCpuHalResetInstructionCache(void);
extern void ScalerCpuHalResetDataCache(void);
extern void ScalerCpuHalEnableICacheDCache(void);
extern void ScalerCpuHalSetupItcmMemoryAttribute(EnumCpu32MpuAccessPermission enumCpu32MpuAccessPermission);
extern void ScalerCpuHalCleanDataCache(void);
extern void ScalerCpuHalSetupDDRProtectRegion(void);
extern void ScalerCpuHalSetupMPUs(void);

__attribute__((section(".itcm_section.ScalerCpuHalResourceAcquire")))
extern bit ScalerCpuHalResourceAcquire(EnumCpu32ResourceID enumResourceID, DWORD ulTO10usCnt);

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
extern void ScalerCpuHalSetMainCpuSw0IRQ(void);
#endif

#if(_SCPU_SUPPORT == _ON)
extern void ScalerCpuHalSetSecondCpuSw0IRQ(void);
#endif

#if((_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_SCPU_SUPPORT == _TRUE))
extern bit ScalerCpuHalGetScpuFlashAddressPointer(DWORD ulKcpuFlashAddrPtr, DWORD *pulScpuFlashAddrPtrAddress);
#endif

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
extern bit ScalerCpuHalCheckMainCpuPendSVEventCnt(void);
#endif

#if(_SCPU_SUPPORT == _ON)
extern bit ScalerCpuHalCheckSecondCpuPendSVEventCnt(void);
#endif