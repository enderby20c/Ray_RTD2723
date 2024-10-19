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
// ID Code      : ScalerGosdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// memory space order: Scpu -> gosd -> 3ddi -> frc -> od
// keep _GOSDSE_CMD_LENGTH_DEFAULT Byte for SE cmd
#define _GOSD_MEMORY_START_ADDRESS                      (GOSD_MEMORY_ROW_TO_BYTE(_FW_CPU32_DDR_MEMORY_SIZE >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM))
#define _GOSD_MEMORY_END_ADDRESS                        ((_GOSD_MEMORY_START_ADDRESS) + (GOSD_MEMORY_ROW_TO_BYTE(_GOSD_MEMORY_SIZE) - _GOSDSE_CMD_LENGTH_DEFAULT))

#define _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE              (sizeof(StructGosdMemoryAllocatorHeader))
#define _GOSD_MEMORY_ALLOCATOR_BASE_ADDRESS             (_GOSD_MEMORY_START_ADDRESS)
#define _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS             (_GOSD_MEMORY_END_ADDRESS - _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE)

#define GOSD_MEMORY_ROW_TO_BYTE(x)                      ((DWORD)(x) * _MEMORY_BANK * _MEMORY_COL_PER_BANK * _MEMORY_BIT_NUM / 8)

#define _GOSD_MAX_COMPRESSED_DATA                       0x00001000

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD b1Free : 1;
    DWORD ulSize;
    DWORD ulPrev;
    DWORD ulNext;
} StructGosdMemoryAllocatorHeader;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bGosdSeExecuting;
extern StructGosdCircularQueue g_stGosdLoadImageIndexCircularQueue;
extern volatile bit g_bGosdContinuousGlobalPause;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern DWORD ScalerGosdCalMaxMemorySize(void);
extern DWORD ScalerGosdCalMaxMemoryBw(void);

extern void ScalerGosdSetSurfaceStatus(DWORD ulSurfaceId, EnumGosdSurfaceStatus enumStatus);
#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern bit ScalerGosdGetSurfaceId(DWORD ulSurfaceAddress, DWORD *pulSurfaceId);
extern bit ScalerGosdMemoryCheckOverlap(DWORD ulX1, DWORD ulL1, DWORD ulX2, DWORD ulL2);
#endif
#endif // #if(_GOSD_SUPPORT == _ON)
