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
// ID Code      : ScalerGosd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GOSD__

#include "ScalerFunctionInclude.h"
#include "Gosd/ScalerGosd.h"

#if(_GOSD_SUPPORT == _ON)

//--------------------------------------------------
// Flash Dual read mode
//--------------------------------------------------
#if(_FLASH_READ_MODE != _FLASH_DUAL_READ)
#warning "NOTE: Please Select _FLASH_READ_MODE == _FLASH_DUAL_READ when _GOSD_SUPPORT == _ON !!!"
#endif

#if(_PANEL_EXIST_MULTIPANEL == _ON)
#if(_OSD_WD_RESET_OVERLAY_DISABLE == _ON)
#warning "NOTE: _OSD_WD_RESET_OVERLAY_DISABLE Should Be _OFF while _GOSD_SUPPORT and _PANEL_EXIST_MULTIPANEL Both _ON!!! Or _PANEL_DH_START/_PANEL_DH_END Should Be the Same in Each Panel!!! "
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_bGosdSeExecuting;

StructGosdCircularQueue g_stGosdLoadImageIndexCircularQueue;

StructGosdDecompressInfo g_pstGosdDecompressInfo[_GOSD_IMAGE_SOURCE_NUMBER];
bit g_bGosdDecompressing = _FALSE;
volatile DWORD g_ulGosdMainCpuUrgentIRQFlag;

volatile StructGosdSurfaceHandler g_pstGosdSurfaceList[_GOSD_SURFACE_NUMBER];

volatile bit g_bGosdContinuousGlobalPause;
volatile StructGosdContinuousParam g_pstGosdContinuousParam[_GOSD_PLANE_MAXNUM];

#if(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
volatile StructCpuSyncGosdCmdReply g_stGosdCmdReply;
volatile StructCpuSyncGosdContinuousSetStepCmd g_stGosdContinuousSetStepCmd;
volatile StructCpuSyncGosdContinuousStepChangePositionCmd g_stGosdContinuousChangePositionCmd;
volatile StructCpuSyncGosdContinuousCmd g_stGosdContinuousCmd;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Gosd Memory Size Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdMemorySizeCheck(void)
{
    static_assert((_GOSD_MEMORY_SIZE > 0), "_GOSD_MEMORY_SIZE Should Be > 0!!!");
    static_assert((_GOSD_MEMORY_SIZE < (_MEMORY_ROW)), "_GOSD_MEMORY_SIZE Should Be < _MEMORY_ROW!!!");
}

//--------------------------------------------------
// Description  : Calculate GOSD max Memory Size
// Input Value  : None
// Output Value : DWORD MemorySize unit: row
//--------------------------------------------------
DWORD ScalerGosdCalMaxMemorySize(void)
{
    return _GOSD_MEMORY_SIZE; // unit: row
}

//--------------------------------------------------
// Description  : Calculate GOSD max Memory Bw
// Input Value  : None
// Output Value : DWORD MemoryBw unit: percent
//--------------------------------------------------
DWORD ScalerGosdCalMaxMemoryBw(void)
{
    return _GOSD_MEMORY_BW; // unit: percent
}

//--------------------------------------------------
// Description  : Disable Continuous
// Input Value  : enumDispPlane : disable plane
// Output Value : None
//--------------------------------------------------
void ScalerGosdContinuousDisable(EnumGosdDisplayOSD enumDispPlane)
{
    if(enumDispPlane == _GOSD_PLANE_ALL)
    {
        g_bGosdContinuousGlobalPause = _FALSE;
        for(BYTE ucPlane = _GOSD_PLANE_OSD1; ucPlane < _GOSD_PLANE_MAXNUM; ucPlane++)
        {
            g_pstGosdContinuousParam[ucPlane].enumGosdContinuousType = _GOSD_CONTINUOUS_NONE;
            g_pstGosdContinuousParam[ucPlane].ucGosdContinuousStep = 0;
            g_pstGosdContinuousParam[ucPlane].ucGosdContinuousTotalStep = 0;
            g_pstGosdContinuousParam[ucPlane].usGosdContinuousTimer = 0;
            g_pstGosdContinuousParam[ucPlane].bGosdContinuousPause = _FALSE;
        }
#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
        ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_GOSD_OSD1_CONTINUOUS_START);
        ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_GOSD_OSD2_CONTINUOUS_START);
        ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_GOSD_OSD3_CONTINUOUS_START);
#endif
    }

    if(enumDispPlane >= _GOSD_PLANE_MAXNUM)
    {
        return;
    }

    g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType = _GOSD_CONTINUOUS_NONE;
    g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousStep = 0;
    g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousTotalStep = 0;
    g_pstGosdContinuousParam[enumDispPlane].usGosdContinuousTimer = 0;
    g_pstGosdContinuousParam[enumDispPlane].bGosdContinuousPause = _FALSE;

#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
    ScalerTimerWDCancelTimerEvent(GET_GOSD_WDTEVENT_BY_DISPLAY_PLANE(enumDispPlane));
#endif
}

//--------------------------------------------------
// Description  : Set Surface status
// Input Value  : ulSurfaceId : surface
//                enumStatus : status
// Output Value : None
//--------------------------------------------------
void ScalerGosdSetSurfaceStatus(DWORD ulSurfaceId, EnumGosdSurfaceStatus enumStatus)
{
    // check surface is in range
    if(ulSurfaceId < _GOSD_SURFACE_NUMBER)
    {
#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
        GOSD_SET_SURFACE_STATUS(ulSurfaceId, enumStatus);
#elif(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
        // set surface status
        StructCpuSyncGosdSetSurfaceStatus *pstCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncGosdSetSurfaceStatusCmd;
        pstCmd->ulSurfaceId = ulSurfaceId;
        pstCmd->ucStatus = enumStatus;

        ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_GOSD_SET_STATUS, _SCALER_CPU_SYNC_TIMEOUT_GOSD, _NULL_POINTER);
#endif
#endif
    }
}

#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
//--------------------------------------------------
// Description  : Enable Continuous
// Input Value  : ucTimerMs : timer in ms
//                enumDispPlane : display plane
//                enumType : continuous type
//                ucTotalStepNumber : Total Step Number
// Output Value : None
//--------------------------------------------------
void ScalerGosdContinuousEnable(BYTE ucTimerMs, EnumGosdDisplayOSD enumDispPlane, EnumGosdContinuousType enumType, BYTE ucTotalStepNumber)
{
    // check continuous_step is ongoing and not attempt to stop
    if((g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType != _GOSD_CONTINUOUS_NONE) &&
       (enumType != _GOSD_CONTINUOUS_NONE))
    {
        DebugMessageGOSD("GOSD Continuous is ongoing!", 0);
        return;
    }

    g_pstGosdContinuousParam[enumDispPlane].enumDispPlane = enumDispPlane;
    g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType = enumType;
    g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousTotalStep = ucTotalStepNumber;

    if(enumType == _GOSD_CONTINUOUS_NONE)
    {
        // clear Timer
        g_pstGosdContinuousParam[enumDispPlane].usGosdContinuousTimer = 0;
        ScalerTimerWDCancelTimerEvent(GET_GOSD_WDTEVENT_BY_DISPLAY_PLANE(enumDispPlane));
    }
    else
    {
        // active timer
        g_pstGosdContinuousParam[enumDispPlane].usGosdContinuousTimer = ucTimerMs;
        ScalerTimerWDActivateTimerEvent(1, GET_GOSD_WDTEVENT_BY_DISPLAY_PLANE(enumDispPlane));
    }
}
#endif // #if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
//--------------------------------------------------
// Description  : GOSD initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdPowerOnInitial(void)
{
    // SW parameters reset
    ScalerGosdReset();

    // HW setting initial
    ScalerGosdSePowerOnInitial();
    ScalerGosdDispOsdPowerOnInitial();
}

//--------------------------------------------------
// Description  : GOSD SW parameters reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdReset(void)
{
    g_bGosdDecompressing = _FALSE;
    g_ulGosdMainCpuUrgentIRQFlag = 0;
    // Circular Queue Initial
    g_stGosdLoadImageIndexCircularQueue.pstQueueBuffer = g_pstGosdDecompressInfo;
    g_stGosdLoadImageIndexCircularQueue.usQueueFront = 0;
    g_stGosdLoadImageIndexCircularQueue.usQueueRear = 0;
    g_stGosdLoadImageIndexCircularQueue.bQueueFull = _FALSE;

    ScalerGosdMemoryAllocatorInit();

    // Initial SurfaceHandler List
    for(DWORD ulIdx = 0; ulIdx < _GOSD_SURFACE_NUMBER; ulIdx++)
    {
        GOSD_SET_SURFACE_ADDRESS(ulIdx, _GOSD_SURFACE_UNCREATED_ADDRESS);
        GOSD_SET_SURFACE_STATUS(ulIdx, _GOSD_SURFACE_UNCREATED);
    }

    // Initial Continuous Parameters
    ScalerGosdContinuousDisable(_GOSD_PLANE_ALL);

    ScalerGosdSeInitial();
    ScalerGosdDispOsdInitial(_GOSD_PLANE_ALL);
}

//--------------------------------------------------
// Description  : Set Surface Header into Surface Address
// Input Value  : ulSurfaceId : Surface
//                pstSurfaceHeader : Surface Header
// Output Value : None
//--------------------------------------------------
void ScalerGosdSetSurfaceHeader(DWORD ulSurfaceId, StructGosdSurfaceHeader *pstSurfaceHeader)
{
    memcpy((void *)(GET_DDR_32BIT_ADDR(GOSD_GET_SURFACE_ADDRESS(ulSurfaceId))), pstSurfaceHeader, sizeof(StructGosdSurfaceHeader));
}

//--------------------------------------------------
// Description  : Get Surface Header from Surface Address
// Input Value  : ulSurfaceId : Surface
// Output Value : Surface Header
//--------------------------------------------------
StructGosdSurfaceHeader *ScalerGosdGetSurfaceHeader(DWORD ulSurfaceId)
{
    return (StructGosdSurfaceHeader *)(GET_DDR_32BIT_ADDR(GOSD_GET_SURFACE_ADDRESS(ulSurfaceId)));
}

//--------------------------------------------------
// Description  : Get Surface Info from Surface
// Input Value  : ulSurfaceId : Surface
// Output Value : Surface Info
//--------------------------------------------------
StructGosdSurfaceInfo ScalerGosdGetSurfaceInfo(DWORD ulSurfaceId)
{
    StructGosdSurfaceInfo stSurfaceInfo = {0};
    StructGosdSurfaceHeader *pstSurfaceHeader = ScalerGosdGetSurfaceHeader(ulSurfaceId);

    stSurfaceInfo.ulSurfaceId = ulSurfaceId;
    stSurfaceInfo.enumPixelFormat = pstSurfaceHeader->b3PixelFormat;
    stSurfaceInfo.ulAddress = pstSurfaceHeader->ulAddress + sizeof(StructGosdSurfaceHeader);
    stSurfaceInfo.ulLength = pstSurfaceHeader->ulLength;
    stSurfaceInfo.usWidth = (pstSurfaceHeader->b13Width == 0) ? _GOSD_SURFACE_SIZE_LIMIT : pstSurfaceHeader->b13Width;
    stSurfaceInfo.usHeight = (pstSurfaceHeader->b13Height == 0) ? _GOSD_SURFACE_SIZE_LIMIT : pstSurfaceHeader->b13Height;
    stSurfaceInfo.usPitch = (pstSurfaceHeader->b15Pitch == 0) ? (1UL << 15) : pstSurfaceHeader->b15Pitch;
    stSurfaceInfo.enumARGBOrder = _GOSD_ARGB; // default fixed Order = A->R->G->B
    stSurfaceInfo.b1BigEndian = _TRUE; // default fixed BigEndian

    if(stSurfaceInfo.enumPixelFormat == _GOSD_PIXEL_FORMAT_INDEX8)
    {
        stSurfaceInfo.ulClutAddress = stSurfaceInfo.ulAddress;
        stSurfaceInfo.ulAddress += _GOSD_INDEX8_PALETTE_LENGTH;
    }

    return stSurfaceInfo;
}


//--------------------------------------------------
// Description  : Get Surface ID
// Input Value  : ulSurfaceAddress : Surface address
//                *pulSurfaceId [out]: Surface ID
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdGetSurfaceId(DWORD ulSurfaceAddress, DWORD *pulSurfaceId)
{
    for(DWORD ulIdx = 0; ulIdx < _GOSD_SURFACE_NUMBER; ulIdx++)
    {
        if(GOSD_GET_SURFACE_ADDRESS(ulIdx) == ulSurfaceAddress)
        {
            *pulSurfaceId = ulIdx;
            return _TRUE;
        }
    }

    DebugMessageGOSD("GetSurfaceId Error!!!", 0);
    DebugMessageGOSD("  ulSurfaceAddress:", ulSurfaceAddress);
    return _FALSE;
}

//--------------------------------------------------
// Description  : Advance Front Pointer of Circular Queue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdCircularQueueAdvanceFront(void)
{
    // Reset to 0 when the maximum size is reached
    if(g_stGosdLoadImageIndexCircularQueue.usQueueFront + 1 == _GOSD_IMAGE_SOURCE_NUMBER)
    {
        g_stGosdLoadImageIndexCircularQueue.usQueueFront = 0;
    }
    else
    {
        g_stGosdLoadImageIndexCircularQueue.usQueueFront++;
    }

    // Clear Full when any read operation
    g_stGosdLoadImageIndexCircularQueue.bQueueFull = _FALSE;
}

//--------------------------------------------------
// Description  : Advance Rear Pointer of Circular Queue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdCircularQueueAdvanceRear(void)
{
    // Reset to 0 when the maximum size is reached
    if(g_stGosdLoadImageIndexCircularQueue.usQueueRear + 1 == _GOSD_IMAGE_SOURCE_NUMBER)
    {
        g_stGosdLoadImageIndexCircularQueue.usQueueRear = 0;
    }
    else
    {
        g_stGosdLoadImageIndexCircularQueue.usQueueRear++;
    }

    // Set Full when Rear == Front
    g_stGosdLoadImageIndexCircularQueue.bQueueFull = (g_stGosdLoadImageIndexCircularQueue.usQueueRear == g_stGosdLoadImageIndexCircularQueue.usQueueFront);
}

//--------------------------------------------------
// Description  : Check FULL status of Circular Queue
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdCircularQueueIsFull(void)
{
    // Queue is FULL when (bQueueFull == _TRUE)
    return (g_stGosdLoadImageIndexCircularQueue.bQueueFull);
}

//--------------------------------------------------
// Description  : Check EMPTY status of Circular Queue
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdCircularQueueIsEmpty(void)
{
    // Queue is empty when ((bQueueFull == _FALSE) && (Rear == Front))
    return ((g_stGosdLoadImageIndexCircularQueue.bQueueFull == _FALSE) && (g_stGosdLoadImageIndexCircularQueue.usQueueRear == g_stGosdLoadImageIndexCircularQueue.usQueueFront));
}

//--------------------------------------------------
// Description  : Push 1 index in Circular Queue
// Input Value  : Decompress info
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdCircularQueuePush(StructGosdDecompressInfo *pstLoadImageInfo)
{
    if(ScalerGosdCircularQueueIsFull() == _FALSE)
    {
        StructGosdDecompressInfo *pstCopyInfo = g_stGosdLoadImageIndexCircularQueue.pstQueueBuffer + g_stGosdLoadImageIndexCircularQueue.usQueueRear;
        memcpy(pstCopyInfo, pstLoadImageInfo, sizeof(StructGosdDecompressInfo));

        ScalerGosdCircularQueueAdvanceRear();
        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Pop 1 index out Circular Queue
// Input Value  : pstTarget : Decompress info at Front Pointer
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdCircularQueuePop(StructGosdDecompressInfo *pstTarget)
{
    if(ScalerGosdCircularQueueIsEmpty() == _FALSE)
    {
        memcpy(pstTarget, g_stGosdLoadImageIndexCircularQueue.pstQueueBuffer + g_stGosdLoadImageIndexCircularQueue.usQueueFront, sizeof(StructGosdDecompressInfo));

        ScalerGosdCircularQueueAdvanceFront();
        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Read 1 index at Front Pointer, no shift Front Pointer
// Input Value  : pstTarget : Decompress info at Front Pointer
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdCircularQueueGetFront(StructGosdDecompressInfo *pstTarget)
{
    if(ScalerGosdCircularQueueIsEmpty() == _FALSE)
    {
        memcpy(pstTarget, g_stGosdLoadImageIndexCircularQueue.pstQueueBuffer + g_stGosdLoadImageIndexCircularQueue.usQueueFront, sizeof(StructGosdDecompressInfo));

        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : set Load Image Info
// Input Value  : ulSurfaceId : Destination surface
//                usImageSourceStartFlashBank : image source start flash bank = _GOSD_IMAGE_SOURCE_FLASH_START_BANK in RTDxxxxGosdImageSource.h
//                usIndex : image source index
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSetLoadImageInfo(DWORD ulSurfaceId, WORD usImageSourceStartFlashBank, WORD usIndex)
{
    if(ScalerGosdCircularQueueIsFull() == _TRUE)
    {
        // circular queue is full
        DebugMessageGOSD("Set Load Imgae info error: FULL_QUEUE", usIndex);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    DWORD ulPhyDDRAddress = 0;
    DWORD ulVirtualBaseAddress = 0;
    // Convert flash bank to SCPU virtual byte address
    if(ScalerCpuHalGetCpuFlashAddress(((DWORD)usImageSourceStartFlashBank << 16) + GET_FLASH_BANK_OFFSET(), &ulVirtualBaseAddress) != _TRUE)
    {
        DebugMessageGOSD("Load Imgae Phy Flash Addr < FlashBankOffset", usImageSourceStartFlashBank);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    //// Struct of full ImageSource data ////
    // Header | Info0 | Info1 | Info2 | ...InfoN | Image0 | Image1 | Image2 | ... | ImagetN

    // Header
    StructGosdImageSourceFileHeader *pstHeader = (StructGosdImageSourceFileHeader *)ulVirtualBaseAddress;
    if(pstHeader->ulSignature != _GOSD_IMAGE_SOURCE_MAGICNUMBER)
    {
        DebugMessageGOSD("Set Load Imgae info error: INVALID_IMAGESOURCE_MAGIC_NUMBER", usImageSourceStartFlashBank);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    if(pstHeader->ulImageNumber <= usIndex)
    {
        DebugMessageGOSD("Set Load Imgae info error: INDEX_OUTOF_RANGE", usIndex);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    DWORD ulVirtualInfoAddress = ulVirtualBaseAddress + pstHeader->ulHeaderSize + usIndex * pstHeader->ulInfoSize;
    //// Info
    StructGosdImageSourceInfo *pstInfo = (StructGosdImageSourceInfo *)ulVirtualInfoAddress;
    DWORD ulVirtualFileAddress = ulVirtualBaseAddress + pstHeader->ulHeaderSize + pstInfo->ulOffset;

    if(ScalerGosdDecompressCheckMagicNumber(ulVirtualFileAddress) == _FALSE)
    {
        // first 4bytes to check compress magic number
        DebugMessageGOSD("Set Load Imgae info error: INVALID_COMPRESS_MAGIC_NUMBER", ulVirtualFileAddress);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    ulPhyDDRAddress = GOSD_GET_SURFACE_ADDRESS(ulSurfaceId);

    StructGosdMemoryAllocatorHeader *pstMemoryHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(ulPhyDDRAddress);
    if((pstInfo->ulDdrSize <= sizeof(StructGosdSurfaceHeader)) ||
       (pstMemoryHeader->ulSize < pstInfo->ulDdrSize - sizeof(StructGosdSurfaceHeader)))
    {
        DebugMessageGOSD("Set Load Imgae info error: image length > memory length", usIndex);
        DebugMessageGOSD("  Surface ID", ulSurfaceId);
        DebugMessageGOSD("  image length", pstInfo->ulDdrSize);
        DebugMessageGOSD("  memory length", pstMemoryHeader->ulSize);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // pointer of file in flash
    BYTE *pucInp = (BYTE *)ulVirtualFileAddress;

    // full length of a compressed block
    DWORD ulLength = TO_DWORD(pucInp[7], pucInp[6], pucInp[5], pucInp[4]);

    // Set Load Image Info
    StructGosdDecompressInfo stGosdDecompressInfo;
    stGosdDecompressInfo.ulSurfaceId = ulSurfaceId;
    stGosdDecompressInfo.pucInPtr = &pucInp[8];
    stGosdDecompressInfo.pucOutPtr = (BYTE *)(GET_DDR_32BIT_ADDR(ulPhyDDRAddress));
    stGosdDecompressInfo.pucOp = stGosdDecompressInfo.pucOutPtr;
    stGosdDecompressInfo.pucInendPtr = &pucInp[pstInfo->ulFlashSize];
    stGosdDecompressInfo.pucInblockendPtr = &pucInp[8 + ulLength];

    // Push Load Image Info in Circular Queue
    ScalerGosdCircularQueuePush(&stGosdDecompressInfo);

    // Set Surface Status
    GOSD_SET_SURFACE_STATUS(ulSurfaceId, _GOSD_SURFACE_LOADING);

    return _GOSD_SYNC_FEEDBACK_SUCCESS;
}

//--------------------------------------------------
// Description  : GOSD DECOMPRESS data
// Input Value : pstDecompressInfo
//               pulDecompressedTime : total time of compressed pass
//               ulLoadTimeOut : timeout
// Output Value : Error code
//--------------------------------------------------
EnumGosdLoadImageResult ScalerGosdDecompress(StructGosdDecompressInfo *pstDecompressInfo, DWORD *pulDecompressedTime, DWORD ulLoadTimeOut)
{
    EnumGosdLoadImageResult enumResult = _GOSD_LOADIMAGE_OK;

    g_bGosdDecompressing = _TRUE;
#if(_SCPU_SUPPORT == _ON)
    ScalerCpuHalSetSecondCpuSw0IRQ();
#endif
    enumResult = ScalerGosdDecompressAction(pstDecompressInfo, pulDecompressedTime, ulLoadTimeOut);
    g_bGosdDecompressing = _FALSE;

    ScalerCpuHalCleanDataCache();

    return enumResult;
}

//--------------------------------------------------
// Description  : Wait command be executed by CPU32 CPU
// Input Value  : ulWaitTimeout --> wait timeout (unit: ms)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
void ScalerGosdDecompressPollingDoneProc(DWORD ulWaitTimeout)
{
    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

    do
    {
        if((g_bGosdDecompressing == _FALSE) || (g_ulGosdMainCpuUrgentIRQFlag == 0))
        {
            return;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(ulTimeElapsed <= ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Gosd Continuous Process
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdContinuousProc(void)
{
#if(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
    EnumGosdDisplayOSD enumDispPlane = g_stGosdContinuousCmd.ucDispPlane;
#elif((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))
    EnumGosdDisplayOSD enumDispPlane = g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncGosdCmd.ucDispPlane;
    g_stCpuSyncToScpuCmdReply.unCmdBody.stCpuSyncGosdCmdReply.bExecuteStatus = _FALSE;
#endif

    // check continuous type
    if(g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType == _GOSD_CONTINUOUS_NONE)
    {
        return _FALSE;
    }

    // check Total step number
    if(g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousTotalStep == 0)
    {
        // stop continuous step
        g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType = _GOSD_CONTINUOUS_NONE;
        return _FALSE;
    }

    // if Loop at last
    if(g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousStep >= g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousTotalStep)
    {
        g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousStep = 0;
        // if not infinite loop
        if(g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType != _GOSD_CONTINUOUS_INFINITE_LOOP)
        {
            // stop continuous step
            g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType = _GOSD_CONTINUOUS_NONE;
            return _FALSE;
        }
    }

    // check DispOsd prog_done status
    if(Scaler32GetBit(PB004FF_04_CTRL, (_BIT3 | _BIT2 | _BIT1)) != 0)
    {
        // Not ready for next continuous step
        return _FALSE;
    }

    if(ScalerGosdDispOsdDisplaySurface(&(g_ppstGosdDispOsdContinuousArgument[enumDispPlane][g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousStep])) == _GOSD_SYNC_FEEDBACK_ERROR)
    {
        return _FALSE;
    }

    g_pstGosdContinuousParam[enumDispPlane].ucGosdContinuousStep++;
#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))
    g_stCpuSyncToScpuCmdReply.unCmdBody.stCpuSyncGosdCmdReply.bExecuteStatus = _TRUE;
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Gosd Continuous Set Step Argument
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdContinuousSetStepProc(void)
{
#if(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
    StructCpuSyncGosdContinuousSetStepCmd *pstArgument = &g_stGosdContinuousSetStepCmd;
#elif((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))
    StructCpuSyncGosdContinuousSetStepCmd *pstArgument = &(g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncGosdSetStepCmd);
#endif
    StructGosdDispOsdDisplayArgument *pstDisplayArgument = &(g_ppstGosdDispOsdContinuousArgument[pstArgument->ucDisplayOSD][pstArgument->ucStepIndex]);

    pstDisplayArgument->ulSurfaceId = pstArgument->ulSurfaceId;

    pstDisplayArgument->stWinRect.stWinWH.usWidth = pstArgument->usWinRectW;
    pstDisplayArgument->stWinRect.stWinWH.usHeight = pstArgument->usWinRectH;
    pstDisplayArgument->stWinRect.stWinXY.usX = pstArgument->usWinRectX;
    pstDisplayArgument->stWinRect.stWinXY.usY = pstArgument->usWinRectY;

    pstDisplayArgument->stDispRect.stWinWH.usWidth = pstArgument->usDispRectW;
    pstDisplayArgument->stDispRect.stWinWH.usHeight = pstArgument->usDispRectH;
    pstDisplayArgument->stDispRect.stWinXY.usX = pstArgument->usDispRectX;
    pstDisplayArgument->stDispRect.stWinXY.usY = pstArgument->usDispRectY;

    pstDisplayArgument->enumOSD = pstArgument->ucDisplayOSD;

    pstDisplayArgument->enumDBApply = pstArgument->ucDBApply;
}

//--------------------------------------------------
// Description  : Gosd Continuous change Step postion
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdContinuousStepChangePositionProc(void)
{
#if(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
    StructCpuSyncGosdContinuousStepChangePositionCmd *pstArgument = &g_stGosdContinuousChangePositionCmd;
#elif((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))
    StructCpuSyncGosdContinuousStepChangePositionCmd *pstArgument = &(g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncGosdChangePositionCmd);
#endif
    BYTE ucDisplayPlane = pstArgument->ucDisplayOSD;
    BYTE ucStepIndex = pstArgument->ucStepIndex;

    g_ppstGosdDispOsdContinuousArgument[ucDisplayPlane][ucStepIndex].stDispRect.stWinXY.usX = pstArgument->usPositionX;
    g_ppstGosdDispOsdContinuousArgument[ucDisplayPlane][ucStepIndex].stDispRect.stWinXY.usY = pstArgument->usPositionY;
}

//--------------------------------------------------
// Description  : Check 1-Dimension 2 segments OverLap
// Input Value  : X1: Segment1 start point
//                L1: Segment1 length
//                X2: Segmentx start point
//                L2: Segmentx length
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdMemoryCheckOverlap(DWORD ulX1, DWORD ulL1, DWORD ulX2, DWORD ulL2)
{
    return ((ulX1 + ulL1 > ulX2) && (ulX2 + ulL2 > ulX1));
}

//--------------------------------------------------
// Description  : Check 1-Dimension segment_1 contains segments_2
// Input Value  : X1: Segment1 start point
//                L1: Segment1 length
//                X2: Segmentx start point
//                L2: Segmentx length
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdMemoryCheckContain(DWORD ulX1, DWORD ulL1, DWORD ulX2, DWORD ulL2)
{
    return ((ulX1 <= ulX2) && (ulX1 + ulL1 >= ulX2 + ulL2));
}

//--------------------------------------------------
// Description  : Initial Gosd MemoryAllocator
// Input Value :  None
// Output Value : None
//--------------------------------------------------
void ScalerGosdMemoryAllocatorInit(void)
{
    StructGosdMemoryAllocatorHeader *pstLastHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(_GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS);
    StructGosdMemoryAllocatorHeader *pstBaseHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(_GOSD_MEMORY_ALLOCATOR_BASE_ADDRESS);

    pstLastHeader->ulSize = 0;
    pstLastHeader->b1Free = _FALSE;
    pstLastHeader->ulNext = _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS;
    pstLastHeader->ulPrev = _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS;

    pstBaseHeader->ulSize = (_GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS - _GOSD_MEMORY_ALLOCATOR_BASE_ADDRESS) - _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
    pstBaseHeader->b1Free = _TRUE;
    pstBaseHeader->ulNext = _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS;
    pstBaseHeader->ulPrev = _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS;
}

//--------------------------------------------------
// Description  : Find Free Space, by Next Fit Memory Management algo.
// Input Value :  Request Block Size
// Output Value : Address of Block Header
//--------------------------------------------------
DWORD ScalerGosdMemoryFindFreeSpace(DWORD ulAlignedRequestSize)
{
    StructGosdMemoryAllocatorHeader *pstCurrentHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(_GOSD_MEMORY_ALLOCATOR_BASE_ADDRESS);

    while(pstCurrentHeader->ulNext != _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS)
    {
        // Not last block
        if((pstCurrentHeader->b1Free == _TRUE) && (pstCurrentHeader->ulSize >= ulAlignedRequestSize))
        {
            // find free block with enough space
            return GET_PHY_32BIT_DDR_ADDR((DWORD)pstCurrentHeader);
        }
        pstCurrentHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(pstCurrentHeader->ulNext);
    }

    //// Last block ////

    if(pstCurrentHeader->b1Free != _TRUE)
    {
        // Last block not free
        return _GOSD_NULL_ADDRESS;
    }
    if(pstCurrentHeader->ulSize < ulAlignedRequestSize)
    {
        // Last block is free but without enough space
        return _GOSD_NULL_ADDRESS;
    }
    // Last block is free and with enough space
    return GET_PHY_32BIT_DDR_ADDR((DWORD)pstCurrentHeader);
}

//--------------------------------------------------
// Description  : Allocate Block
// Input Value :  Request Block Size
// Output Value : Address of Block, _GOSD_NULL_ADDRESS means allocate fail
//--------------------------------------------------
DWORD ScalerGosdMemoryAllocate(DWORD ulRequestSize, DWORD ulSpecifiedAddress)
{
    if(ulRequestSize == 0)
    {
        DebugMessageGOSD("RequestSize = 0", 0);
        return _GOSD_NULL_ADDRESS;
    }

    bit bFixedAllocate = (ulSpecifiedAddress == _GOSD_NULL_ADDRESS) ? _FALSE : _TRUE;
    StructGosdMemoryAllocatorHeader *pstHeader = _NULL_POINTER;
    StructGosdMemoryAllocatorHeader *pstNewHeader = _NULL_POINTER;
    // FullSize = alinged(memoryheader_size + content_size)
    DWORD ulAlignedFullSize = CEILING(ulRequestSize + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE, _GOSD_SURFACE_ALIGN_UNIT);
    DWORD ulContentSize = ulAlignedFullSize - _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
    DWORD ulAllocateHeaderAddress = _GOSD_NULL_ADDRESS;
    DWORD ulRemainSize = 0;
    DWORD ulNextAddress = 0;

    if(bFixedAllocate == _TRUE)
    {
        if(ulSpecifiedAddress > (GOSD_MEMORY_ROW_TO_BYTE(_GOSD_MEMORY_SIZE) - _GOSDSE_CMD_LENGTH_DEFAULT))
        {
            DebugMessageGOSD("Create Surface error: Address outof _GOSD_MEMORY_SIZE", 0);
            DebugMessageGOSD("  Address", ulSpecifiedAddress);
            DebugMessageGOSD("  _GOSD_MEMORY_SIZE", (GOSD_MEMORY_ROW_TO_BYTE(_GOSD_MEMORY_SIZE) - _GOSDSE_CMD_LENGTH_DEFAULT));
            return _GOSD_NULL_ADDRESS;
        }

        if((ulSpecifiedAddress + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE) % _GOSD_SURFACE_ALIGN_UNIT != 0)
        {
            DebugMessageGOSD("Create Surface error: (ulSpecifiedAddress + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE) must align _GOSD_SURFACE_ALIGN_UNIT", 0);
            DebugMessageGOSD("  Address", ulSpecifiedAddress);
            DebugMessageGOSD("  _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE", _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE);
            DebugMessageGOSD("  _GOSD_SURFACE_ALIGN_UNIT", _GOSD_SURFACE_ALIGN_UNIT);
            return _GOSD_NULL_ADDRESS;
        }

        ulSpecifiedAddress += _GOSD_MEMORY_START_ADDRESS;
        pstHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(_GOSD_MEMORY_ALLOCATOR_BASE_ADDRESS);
        ulAllocateHeaderAddress = ulSpecifiedAddress - _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
        while(_TRUE)
        {
            // check : Is the specified memory occupied by allocated memory
            if(pstHeader->b1Free == _FALSE)
            {
                if(ScalerGosdMemoryCheckOverlap(GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader), pstHeader->ulSize + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE, ulAllocateHeaderAddress, ulAlignedFullSize))
                {
                    DebugMessageGOSD("Specified Memory is Occupied", 0);
                    return _GOSD_NULL_ADDRESS;
                }
            }
            // Find which header contains the specified memory
            else
            {
                if(ScalerGosdMemoryCheckContain(GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader), pstHeader->ulSize, ulAllocateHeaderAddress, ulAlignedFullSize))
                {
                    break;
                }
            }

            if(pstHeader->ulNext != _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS)
            {
                // Not Last block => check next block
                pstHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(pstHeader->ulNext);
            }
            else
            {
                // All block not contain Specified address
                DebugMessageGOSD("Specified Address is not include", 0);
                return _GOSD_NULL_ADDRESS;
            }
        }
    }
    else
    {
        ulAllocateHeaderAddress = ScalerGosdMemoryFindFreeSpace(ulContentSize);
        // Allocate fail
        if(ulAllocateHeaderAddress == _GOSD_NULL_ADDRESS)
        {
            DebugMessageGOSD("No Enough Memory", 0);
            return _GOSD_NULL_ADDRESS;
        }
        pstHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(ulAllocateHeaderAddress);
    }

    // Memory Allocate
    ulRemainSize = pstHeader->ulSize - ulAlignedFullSize;
    ulNextAddress = pstHeader->ulNext;

    // totally fill up
    if(pstHeader->ulSize <= ulAlignedFullSize)
    {
        // allocate block
        pstHeader->b1Free = _FALSE;
    }
    // no space at Prev, but Next is not fill up
    else if(GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader) == ulAllocateHeaderAddress)
    {
        // allocate current block
        pstHeader->ulSize = ulContentSize;
        pstHeader->b1Free = _FALSE;
        pstHeader->ulNext = GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE + pstHeader->ulSize);

        // add new block
        pstNewHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(pstHeader->ulNext);
        pstNewHeader->ulSize = ulRemainSize;
        pstNewHeader->b1Free = _TRUE;
        pstNewHeader->ulPrev = GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader);
        pstNewHeader->ulNext = ulNextAddress;
    }
    // no space at Next, but Prev is not fill up
    else if(pstHeader->ulNext == ulSpecifiedAddress + ulContentSize)
    {
        // change current empty block
        pstHeader->ulSize = ulRemainSize;
        pstHeader->ulNext = GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader) + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE + pstHeader->ulSize;
        pstHeader->b1Free = _TRUE;

        // add fill-up block
        pstNewHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(ulAllocateHeaderAddress);
        pstNewHeader->ulSize = ulContentSize;
        pstNewHeader->b1Free = _FALSE;
        pstNewHeader->ulPrev = GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader);
        pstNewHeader->ulNext = ulNextAddress;
    }
    // Prev and Next both not fill up
    else
    {
        ulRemainSize = pstHeader->ulNext - (ulAllocateHeaderAddress + ulAlignedFullSize);
        // change current empty block
        pstHeader->ulSize = ulAllocateHeaderAddress - (GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader) + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE);
        pstHeader->ulNext = ulAllocateHeaderAddress;

        // add fill-up block
        pstNewHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(ulAllocateHeaderAddress);
        pstNewHeader->ulSize = ulContentSize;
        pstNewHeader->b1Free = _FALSE;
        pstNewHeader->ulPrev = GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader);
        pstNewHeader->ulNext = GET_PHY_32BIT_DDR_ADDR((DWORD)pstNewHeader) + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE + pstNewHeader->ulSize;

        // add new block
        StructGosdMemoryAllocatorHeader *pstNewNextHeader = (StructGosdMemoryAllocatorHeader *)GET_DDR_32BIT_ADDR(pstNewHeader->ulNext);
        pstNewNextHeader->ulSize = ulRemainSize;
        pstNewNextHeader->b1Free = _TRUE;
        pstNewNextHeader->ulPrev = GET_PHY_32BIT_DDR_ADDR((DWORD)pstNewHeader);
        pstNewNextHeader->ulNext = ulNextAddress;
    }

    return ulAllocateHeaderAddress + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
}

//--------------------------------------------------
// Description  : Free allocated Block
// Input Value :  Block Data Address
// Output Value : None
//--------------------------------------------------
void ScalerGosdMemoryFree(DWORD ulDataAddress)
{
    DWORD ulHeaderAddress = ulDataAddress - _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;

    StructGosdMemoryAllocatorHeader *pstHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(ulHeaderAddress));
    StructGosdMemoryAllocatorHeader *pstPrevHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(pstHeader->ulPrev));
    StructGosdMemoryAllocatorHeader *pstNextHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(pstHeader->ulNext));
    StructGosdMemoryAllocatorHeader *pstNextNextHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(pstNextHeader->ulNext));

    if((pstPrevHeader->b1Free == _TRUE) && (pstHeader->ulPrev != _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS))
    {
        if((pstNextHeader->b1Free == _TRUE) && (pstHeader->ulNext != _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS))
        {
            // Next & Prev blocks are both Free, Combine Prev, Current, Next block
            // 0   1   2   3   4
            // |___|___|___|___|

            // F   A   F   A   A

            // Free "1"

            // 0           3   4
            // |___________|___|
            // F           A   A

            pstPrevHeader->ulSize += pstHeader->ulSize + pstNextHeader->ulSize + 2 * _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
            pstPrevHeader->ulNext = pstNextHeader->ulNext;

            pstNextNextHeader->ulPrev = pstHeader->ulPrev;
        }
        else
        {
            // Prev block is Free, Combine Prev, Current block
            // 0   1   2   3   4
            // |___|___|___|___|

            // F   A   A   A   A

            // Free "1"

            // 0       2   3   4
            // |_______|___|___|
            // F       A   A   A

            pstPrevHeader->ulSize += pstHeader->ulSize + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
            pstPrevHeader->ulNext = pstHeader->ulNext;

            pstNextHeader->ulPrev = pstHeader->ulPrev;
        }
    }
    else if((pstNextHeader->b1Free == _TRUE) && (pstHeader->ulNext != _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS))
    {
        // Next block is Free, Combine Current, Next block
        // 0   1   2   3   4
        // |___|___|___|___|

        // A   A   F   A   A

        // Free "1"

        // 0   1       3   4
        // |___|_______|___|
        // A   F       A   A

        pstHeader->ulSize += pstNextHeader->ulSize + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
        pstHeader->b1Free = _TRUE;
        pstHeader->ulNext = pstNextHeader->ulNext;

        pstNextNextHeader->ulPrev = pstNextHeader->ulPrev;
    }
    else
    {
        // Neighbor blocks are both allocated
        pstHeader->b1Free = _TRUE;
    }
}


//--------------------------------------------------
// Description  : Free multi allocated Blocks
// Input Value :  First free Block Data Address
// Output Value : None
//--------------------------------------------------
void ScalerGosdMemoryFreeMultiBlocks(DWORD ulStartDataAddress)
{
    DWORD ulHeaderAddress = ulStartDataAddress - _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE;
    StructGosdMemoryAllocatorHeader *pstHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(ulHeaderAddress));
    StructGosdSurfaceHandler *pstSurface;

    // Reset all surface handler until last block
    do
    {
        pstSurface = (StructGosdSurfaceHandler *)(((DWORD)pstHeader) + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE);
        pstSurface->ulSurfaceDdrAddress = _GOSD_NULL_ADDRESS;

        pstHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(pstHeader->ulNext));
    } while(GET_PHY_32BIT_DDR_ADDR((DWORD)pstHeader) != _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS);

    // First free block => Last and free
    pstHeader = (StructGosdMemoryAllocatorHeader *)(GET_DDR_32BIT_ADDR(ulHeaderAddress));
    pstHeader->b1Free = _TRUE;
    pstHeader->ulNext = _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS;
    pstHeader->ulSize = _GOSD_MEMORY_ALLOCATOR_LAST_ADDRESS - (ulHeaderAddress + _GOSD_MEMORY_ALLOCATOR_HEADER_SIZE);
}

//--------------------------------------------------
// Description  : Check Surface
// Input Value :  ulSurfaceId
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdCheckSurface(DWORD ulSurfaceId)
{
    if(ulSurfaceId >= _GOSD_SURFACE_NUMBER)
    {
        return _FAIL;
    }

    if(GOSD_GET_SURFACE_ADDRESS(ulSurfaceId) == _GOSD_SURFACE_UNCREATED_ADDRESS)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

#endif // #if(_GOSD_FW_COMPILE_RESPONSE_FLOW  == _TRUE)
#endif // #if(_GOSD_SUPPORT == _ON)
