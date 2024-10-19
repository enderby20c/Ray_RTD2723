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
// ID Code      : ScalerGosdInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GOSD_NULL_ADDRESS                      _MAX_ADDRESS_OF_32BIT

#define _SCPU_SWIRQ_TIMEOUT_GOSD_DECOMPRESS     100

#define _GOSD_INDEX8_PALETTE_LENGTH             1024
#define _GOSD_INDEX4_PALETTE_LENGTH             64

#define _GOSD_SURFACE_UNCREATED_ADDRESS         0x00000000UL

#define _GOSD_SURFACE_SIZE_LIMIT                8192

#define GOSD_SET_SURFACE_ADDRESS(x, y)          (g_pstGosdSurfaceList[(x)].ulSurfaceDdrAddress = (y))
#define GOSD_GET_SURFACE_ADDRESS(x)             (g_pstGosdSurfaceList[(x)].ulSurfaceDdrAddress)
#define GOSD_SET_SURFACE_STATUS(x, y)           (g_pstGosdSurfaceList[(x)].enumSurfaceStatus = (y))
#define GOSD_GET_SURFACE_STATUS(x)              (g_pstGosdSurfaceList[(x)].enumSurfaceStatus)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD b4Status : 4;
    DWORD b3PixelFormat : 3;
    DWORD b15Pitch : 15;

    DWORD b13Width : 13;
    DWORD b13Height : 13;

    DWORD ulLength;

    DWORD ulAddress;
} StructGosdSurfaceHeader;

typedef struct
{
    DWORD ulSurfaceId;
    EnumGosdPixelFormat enumPixelFormat;
    WORD usWidth;
    WORD usHeight;
    DWORD ulLength;
    DWORD ulAddress; // address of surface
    WORD usPitch;
    // EnumGosdRGBOrder enumRGBOrder;
    EnumGosdARGBOrder enumARGBOrder;
    DWORD ulClutAddress;
    // BYTE ucByteSwap;
    BYTE b1BigEndian                 : 1;
} StructGosdSurfaceInfo;

typedef struct
{
    DWORD ulSurfaceId;
    BYTE *pucInPtr; // Source address
    BYTE *pucInendPtr; // Source End address
    BYTE *pucInblockendPtr; // Source Block End address
    BYTE *pucOutPtr; // Destination address
    BYTE *pucOp; // fixed Destination address for check _GOSD_LOADIMAGE_ERROR_REF_OFFSET_UNDERFLOW
} StructGosdDecompressInfo;

typedef enum
{
    _GOSD_LOADIMAGE_OK,
    _GOSD_LOADIMAGE_PAUSE,
    _GOSD_LOADIMAGE_ERROR
} EnumGosdLoadImageResult;

typedef struct
{
    StructGosdDecompressInfo *pstQueueBuffer;
    WORD usQueueFront;
    WORD usQueueRear;
    bit bQueueFull;
} StructGosdCircularQueue;

typedef struct
{
    DWORD ulSurfaceDdrAddress;
    EnumGosdSurfaceStatus enumSurfaceStatus;
} StructGosdSurfaceHandler;

typedef struct
{
    EnumGosdDisplayOSD enumDispPlane;
    BYTE ucGosdContinuousStep;
    BYTE ucGosdContinuousTotalStep;
    WORD usGosdContinuousTimer;
    EnumGosdContinuousType enumGosdContinuousType;
    bit bGosdContinuousPause;
} StructGosdContinuousParam;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructGosdSurfaceHandler g_pstGosdSurfaceList[_GOSD_SURFACE_NUMBER];
extern volatile StructGosdContinuousParam g_pstGosdContinuousParam[_GOSD_PLANE_MAXNUM];
extern volatile DWORD g_ulGosdMainCpuUrgentIRQFlag;

#if(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
extern volatile StructCpuSyncGosdCmdReply g_stGosdCmdReply;
extern volatile StructCpuSyncGosdContinuousSetStepCmd g_stGosdContinuousSetStepCmd;
extern volatile StructCpuSyncGosdContinuousStepChangePositionCmd g_stGosdContinuousChangePositionCmd;
extern volatile StructCpuSyncGosdContinuousCmd g_stGosdContinuousCmd;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGosdContinuousDisable(EnumGosdDisplayOSD enumDispPlane);

#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
extern void ScalerGosdContinuousEnable(BYTE ucTimerMs, EnumGosdDisplayOSD enumDispPlane, EnumGosdContinuousType enumType, BYTE ucTotalStepNumber);
#endif

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern void ScalerGosdPowerOnInitial(void);
extern void ScalerGosdReset(void);
extern EnumGosdSyncCmdFeedBack ScalerGosdSetLoadImageInfo(DWORD ulSurfaceId, WORD usImageSourceStartFlashBank, WORD usIndex);
extern EnumGosdLoadImageResult ScalerGosdDecompress(StructGosdDecompressInfo *pstDecompressInfo, DWORD *pulDecompressedTime, DWORD ulLoadTimeOut);
extern void ScalerGosdCircularQueueAdvanceFront(void);
extern bit ScalerGosdCircularQueueGetFront(StructGosdDecompressInfo *pstTarget);
extern void ScalerGosdDecompressPollingDoneProc(DWORD ulWaitTimeout);

extern bit ScalerGosdContinuousProc(void);
extern void ScalerGosdContinuousSetStepProc(void);
extern void ScalerGosdContinuousStepChangePositionProc(void);

extern void ScalerGosdSetSurfaceHeader(DWORD ulSurfaceId, StructGosdSurfaceHeader *pstSurfaceHeader);
extern StructGosdSurfaceHeader *ScalerGosdGetSurfaceHeader(DWORD ulSurfaceId);
extern StructGosdSurfaceInfo ScalerGosdGetSurfaceInfo(DWORD ulSurfaceId);

extern void ScalerGosdMemoryAllocatorInit(void);
extern DWORD ScalerGosdMemoryAllocate(DWORD ulRequestSize, DWORD ulSpecifiedAddress);
extern void ScalerGosdMemoryFree(DWORD ulDataAddress);
extern void ScalerGosdMemoryFreeMultiBlocks(DWORD ulStartDataAddress);
extern bit ScalerGosdCheckSurface(DWORD ulSurfaceId);
#endif

#endif // #if(_GOSD_SUPPORT == _ON)
