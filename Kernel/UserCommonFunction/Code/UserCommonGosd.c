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

//----------------------- -----------------------------------------------------------------------------
// ID Code      : UserCommonGosd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_GOSD__

#include "UserCommonInclude.h"
#include "Gosd/UserCommonGosd.h"

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructGosdKcpuToScpuSyncCmd g_stGosdKcpuToScpuSyncCmd;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)
//--------------------------------------------------
// Description  : Polling Sync FeedBack
// Input Value  : pulTimeCount : Count time passed
//                ulWaitTimeout --> wait timeout (unit: ms)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdPollingSyncFeedBack(DWORD *pulTimeCount, DWORD ulWaitTimeout)
{
    pulTimeCount = pulTimeCount;
    ulWaitTimeout = ulWaitTimeout;

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
    UserCommonGosdFunctionHandler();
    return GET_GOSD_SYNC_FEEDBACK();
#else
    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

    while(*pulTimeCount + ulTimeElapsed <= ulWaitTimeout)
    {
        EnumGosdSyncCmdFeedBack enumRes = GET_GOSD_SYNC_FEEDBACK();

        if(enumRes != _GOSD_SYNC_FEEDBACK_BUSY)
        {
            *pulTimeCount += ulTimeElapsed;
            return enumRes;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }

    *pulTimeCount += ulTimeElapsed;
    DebugMessageGOSD("PollingSyncTimeOut", 0);
    return _GOSD_SYNC_FEEDBACK_BUSY;
#endif
}

//--------------------------------------------------
// Description  : Check Sync Function setting done
// Input Value  : pulTimeCount : Count time passed
//                ulWaitTimeout --> wait timeout (unit: ms)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
bit UserCommonGosdCheckCmdDone(DWORD *pulTimeCount, DWORD ulWaitTimeout)
{
    pulTimeCount = pulTimeCount;
    ulWaitTimeout = ulWaitTimeout;

#if(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
    return _TRUE;
#else
    DWORD ulTimeCount = *pulTimeCount;

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
    *pulTimeCount = ulTimeCount;

    return (enumReturn == _GOSD_SYNC_FEEDBACK_BUSY) ? (_FAIL) : (_SUCCESS);
#endif
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Reset
// Input Value  : ulWaitTimeout
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdResetSync(DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_RESET);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Get Surface Status
// Input Value  : penumStatus : output Surface Status
//                ulSurfaceId : Surface Index
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdGetSurfaceStatusSync(EnumGosdSurfaceStatus *penumStatus, DWORD ulSurfaceId, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    g_stGosdKcpuToScpuSyncCmd.unCmdBody.stGetSurfaceStatus.ulSurfaceId = ulSurfaceId;
    g_stGosdKcpuToScpuSyncCmd.unCmdBody.stGetSurfaceStatus.enumStatus = _GOSD_SURFACE_UNCREATED;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_GET_SURFACE_STATUS);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        *penumStatus = g_stGosdKcpuToScpuSyncCmd.unCmdBody.stGetSurfaceStatus.enumStatus;
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Polling Surface Status
// Input Value  : enumTargetStatus : target Surface Status
//                ulSurfaceId : Surface Index
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
bit UserCommonGosdPollingSurfaceStatusSync(EnumGosdSurfaceStatus enumTargetStatus, DWORD ulSurfaceId, DWORD ulWaitTimeout)
{
    EnumGosdSurfaceStatus enumStatus = _GOSD_SURFACE_UNCREATED;
    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

#if((_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE) && (_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE))
    if(enumTargetStatus != _GOSD_SURFACE_LOADING)
    {
        // targat status != _LOADING && current status == _LOADING
        if(GOSD_GET_SURFACE_STATUS(ulSurfaceId) == _GOSD_SURFACE_LOADING)
        {
            // Load Image
            ulWaitTimeout -= UserCommonGosdLoadImageProcess(ulWaitTimeout);
        }
    }
#endif

    while(ulTimeElapsed <= ulWaitTimeout)
    {
        UserCommonGosdGetSurfaceStatusSync(&enumStatus, ulSurfaceId, ulWaitTimeout);

        if(enumStatus == enumTargetStatus)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }

    DebugMessageGOSD("Polling Surface Status TimeOut", 0);
    DebugMessageGOSD("  Surface ID:", ulSurfaceId);
    DebugMessageGOSD("  Target Status:", enumTargetStatus);
    return _FALSE;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Memory controller Reset
// Input Value  : ulWaitTimeout
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdMemoryResetSync(DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_MEMORY_RESET);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Create Surface
// Input Value  : ulSurfaceId : Surface Index
//                enumFormat : Pixel Format
//                usWidth : Full Width
//                usHeight : Full Height
//                ulAddr : destination address
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdCreateSurfaceSync(DWORD ulSurfaceId, EnumGosdPixelFormat enumFormat, WORD usWidth, WORD usHeight, DWORD ulAddr, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    if((usWidth == 0) || (usWidth > _GOSD_SURFACE_SIZE_LIMIT) ||
       (usHeight == 0) || (usHeight > _GOSD_SURFACE_SIZE_LIMIT))
    {
        DebugMessageGOSD("Gosd Create Surface ERROR : Size out of 1~8192", 0x00);
        DebugMessageGOSD("  Surface ID =", ulSurfaceId);
        DebugMessageGOSD("  Width =", usWidth);
        DebugMessageGOSD("  Height =", usHeight);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    WORD usBpp = 0;
    WORD usPitch = 0;

    // get Bpp by format
    switch(enumFormat)
    {
        case _GOSD_PIXEL_FORMAT_ARGB8888:
            usBpp = 4;
            break;
        case _GOSD_PIXEL_FORMAT_RGB888:
            usBpp = 3;
            break;
        case _GOSD_PIXEL_FORMAT_ARGB4444:
        case _GOSD_PIXEL_FORMAT_ARGB1555:
        case _GOSD_PIXEL_FORMAT_RGB565:
            usBpp = 2;
            break;
        case _GOSD_PIXEL_FORMAT_INDEX8:
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_PIXEL_FORMAT_AFBC4U8:
        case _GOSD_PIXEL_FORMAT_AFBC3U8:
#endif
            usBpp = 1;
            break;
        default:
            DebugMessageGOSD("Gosd Create Surface ERROR : Unknown Pixel Format.", 0x00);
            return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    usPitch = usWidth * usBpp;

    StructGosdSurfaceHeader stOutputSurfaceHeader = {0};
    stOutputSurfaceHeader.b3PixelFormat = enumFormat;
    stOutputSurfaceHeader.b13Width = (usWidth == _GOSD_SURFACE_SIZE_LIMIT) ? 0 : usWidth;
    stOutputSurfaceHeader.b13Height = (usHeight == _GOSD_SURFACE_SIZE_LIMIT) ? 0 : usHeight;
    stOutputSurfaceHeader.ulAddress = ulAddr;
    stOutputSurfaceHeader.b15Pitch = (usPitch == (1UL << 15)) ? 0 : usPitch;

    // get Length by format
    switch(enumFormat)
    {
        case _GOSD_PIXEL_FORMAT_INDEX8:
            stOutputSurfaceHeader.ulLength = (DWORD)usPitch * usHeight + _GOSD_INDEX8_PALETTE_LENGTH;
            break;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_PIXEL_FORMAT_AFBC4U8:
            stOutputSurfaceHeader.ulLength = (DWORD)usWidth * usHeight * 9 / 2;
            break;
        case _GOSD_PIXEL_FORMAT_AFBC3U8:
            stOutputSurfaceHeader.ulLength = (DWORD)usWidth * usHeight * 7 / 2;
            break;
#endif
        default:
            stOutputSurfaceHeader.ulLength = (DWORD)usPitch * usHeight;
            break;
    }

    g_stGosdKcpuToScpuSyncCmd.unCmdBody.stCreateSurface.ulSurfaceId = ulSurfaceId;
    memcpy(&g_stGosdKcpuToScpuSyncCmd.unCmdBody.stCreateSurface.stSurfaceHeader, &stOutputSurfaceHeader, sizeof(StructGosdSurfaceHeader));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_CREATE_SURFACE);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Release Surface
// Input Value  : ulSurfaceId : Surface Index
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdReleaseSurfaceSync(DWORD ulSurfaceId, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    g_stGosdKcpuToScpuSyncCmd.unCmdBody.stReleaseSurface.ulSurfaceId = ulSurfaceId;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_RELEASE_SURFACE);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : Release multi Surface Sync
// Input Value  : ulSurfaceId : Release form this surface index to last
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdReleaseMultiSurfaceSync(DWORD ulSurfaceId, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    g_stGosdKcpuToScpuSyncCmd.unCmdBody.stReleaseSurface.ulSurfaceId = ulSurfaceId;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_RELEASE_MULTI_SURFACE);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdSetLoadImageInfo
// Input Value  : ulSurfaceId : Surface Index
//                pstSrc : LoadImageInfo
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdSetLoadImageInfoSync(DWORD ulSurfaceId, StructGosdLoadImageInfo *pstSrc, EnumGosdLoadPolling enumPolling, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    if(pstSrc->usImageIndex >= _GOSD_IMAGE_SOURCE_NUMBER)
    {
        // ImageIndex out of range
        DebugMessageGOSD("LoadImage Error: ImageIndex bigger than _GOSD_IMAGE_SOURCE_NUMBER", pstSrc->usImageIndex);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    g_stGosdKcpuToScpuSyncCmd.unCmdBody.stSetLoadImageInfo.ulSurfaceId = ulSurfaceId;
    StructGosdLoadImageInfo *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stSetLoadImageInfo.stLoadImageInfo);
    memcpy(pstDest, pstSrc, sizeof(StructGosdLoadImageInfo));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_SET_LOAD_IMAGE_INFO);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(enumPolling == _GOSD_LOAD_POLLING)
        {
            if(UserCommonGosdPollingSurfaceStatusSync(_GOSD_SURFACE_IDLE, ulSurfaceId, ulWaitTimeout) != _TRUE)
            {
                return _GOSD_SYNC_FEEDBACK_BUSY_LOAD;
            }
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd polling draw done
// Input Value  : ulWaitTimeout
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonGosdDrawPollingDone(DWORD ulWaitTimeout)
{
    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

    while(ulTimeElapsed <= ulWaitTimeout)
    {
        if(UserCommonGosdGetDrawing() == _FALSE)
        {
            // Executing == false => Draw is Done
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }

    DebugMessageGOSD("Polling Draw Done TimeOut", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdImageConvert
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdResult : rslt surface index
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdImageConvertSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyImageConvert *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stImageConvert);

    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_IMAGE_CONVERT);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdCopyPaste
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdResult : rslt surface index
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdCopyPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyCopyPaste *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stCopyPaste);

    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stSourceRect), &(stSrcRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stOutPosition), &(stOutPosition), sizeof(StructGosdPosition));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_COPY_PASTE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdRotate
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdResult : rslt surface index
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
//                enumRotateSel : 0: none, 1: 90 degree, 2: 270 degree, 3: 180 degree, clockwise
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdRotateSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, EnumOsdRotateType enumRotateSel, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    // check rotate select
    if(enumRotateSel > _OSD_ROTATE_DEGREE_180)
    {
        DebugMessageGOSD("Osd Rotate select not support.", enumRotateSel);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSyncCmdBodyRotate *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stRotate);

    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stSourceRect), &(stSrcRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stOutPosition), &(stOutPosition), sizeof(StructGosdPosition));
    pstDest->enumRotateSel = enumRotateSel;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_ROTATE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdMirror
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdResult : rslt surface index
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
//                enumMirrorSel : 0: none, 1: 90 degree, 2: 180 degree, 3: 270 degree
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdMirrorSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, EnumGosdSeMirrorMode enumMirrorSel, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    // check rotate select
    if(enumMirrorSel > _GOSD_SEINFO_MIRROR_XY)
    {
        DebugMessageGOSD("Gosd Mirror select not support.", enumMirrorSel);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSyncCmdBodyMirror *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stMirror);

    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stSourceRect), &(stSrcRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stOutPosition), &(stOutPosition), sizeof(StructGosdPosition));
    pstDest->enumMirrorSel = enumMirrorSel;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_MIRROR);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdDrawRectangle
// Input Value  : ulSurfaceIdResult : rslt surface index
//                stRect : draw rectangle (x, y, w, h)
//                ulColor : draw color
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDrawRectangleSync(DWORD ulSurfaceIdResult, StructGosdRectangle stRect, DWORD ulColor, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyDrawRectangle *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDrawRectangle);
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    pstDest->ulColor = ulColor;
    memcpy(&(pstDest->stRect), &(stRect), sizeof(StructGosdRectangle));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_DRAW_RECTANGLE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdDrawLinearGradientRectangle
// Input Value  : ulSurfaceIdResult : rslt surface index
//                stRect : fill rectangle (x, y, w, h)
//                stOutPosition : out start point on result surface (x, y)
//                enumLinearGradientMode : Linear gradient direction 1:x-only; 2:y-only; 3:x&y
//                ulStartColor : start color A8R8G8B8
//                ulEndColor : end color A8R8G8B8
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDrawLinearGradientRectangleSync(DWORD ulSurfaceIdResult, StructGosdRectangle stRect, EnumGosdSeLinearGradientMode enumLinearGradientMode, DWORD ulStartColor, DWORD ulEndColor, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyDrawLinearGradientRectangle *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDrawLinearGradientRectangle);
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stRect), &(stRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->enumLinearGradientMode), &(enumLinearGradientMode), sizeof(EnumGosdSeLinearGradientMode));
    pstDest->ulStartColor = ulStartColor;
    pstDest->ulEndColor = ulEndColor;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_DRAW_LINEARGRADIENT_RECTANGLE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}


//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdBitBlitPaste
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdDestination : dest surface index
//                ulSurfaceIdResult : rslt surface index
//                stRect : draw rectangle (x, y, w, h)
//                ulColor : draw color
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdBitBlitPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdDestination, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stDestPosition, StructGosdPosition stOutPosition, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyBitBlitPaste *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stBitBlitPaste);
    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdDestination = ulSurfaceIdDestination;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stSourceRect), &(stSrcRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stDestinationPosition), &(stDestPosition), sizeof(StructGosdPosition));
    memcpy(&(pstDest->stOutPosition), &(stOutPosition), sizeof(StructGosdPosition));
    pstDest->ulBlitFlags = ulBlitFlags;
    memcpy(&(pstDest->stBlitSettings), pstBlitSettings, sizeof(StructGosdSeBitBlitSettings));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_BITBLIT_PASTE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        enumReturn = (UserCommonGosdDrawPollingDone(ulWaitTimeout) == _TRUE) ? (_GOSD_SYNC_FEEDBACK_SUCCESS) : (_GOSD_SYNC_FEEDBACK_BUSY_DRAW);
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdStretchPaste
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdResult : rslt surface index
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutRect : paste position (x, y, w, h)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdStretchPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdRectangle stOutRect, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyStretchPaste *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stStretchPaste);
    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stSourceRect), &(stSrcRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stOutRect), &(stOutRect), sizeof(StructGosdRectangle));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_STRETCH_PASTE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd 2 cpu sync cmd setting : UserCommonGosdBitBlitPaste
// Input Value  : ulSurfaceIdSource : src surface index
//                ulSurfaceIdDestination : dest surface index
//                ulSurfaceIdResult : rslt surface index
//                stRect : draw rectangle (x, y, w, h)
//                ulColor : draw color
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdSretchBitBlitPasteSync(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdDestination, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stDestPosition, StructGosdRectangle stOutRect, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    StructGosdSyncCmdBodyStretchBitBlitPaste *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stStretchBitBlitPaste);
    pstDest->ulSurfaceIdSource = ulSurfaceIdSource;
    pstDest->ulSurfaceIdDestination = ulSurfaceIdDestination;
    pstDest->ulSurfaceIdResult = ulSurfaceIdResult;
    memcpy(&(pstDest->stSourceRect), &(stSrcRect), sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stDestinationPosition), &(stDestPosition), sizeof(StructGosdPosition));
    memcpy(&(pstDest->stOutRect), &(stOutRect), sizeof(StructGosdRectangle));
    pstDest->ulBlitFlags = ulBlitFlags;
    memcpy(&(pstDest->stBlitSettings), pstBlitSettings, sizeof(StructGosdSeBitBlitSettings));

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_STRETCHBITBLIT_PASTE);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);

    // polling Draw Finish
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        if(UserCommonGosdDrawPollingDone(ulWaitTimeout) != _TRUE)
        {
            enumReturn = _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
        }
    }

    return enumReturn;
}

//--------------------------------------------------
// Description  : Gosd Get Draw executing Status
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonGosdGetDrawing(void)
{
    return ScalerGosdSeGetExecute();
}

//--------------------------------------------------
// Description  : check DispOsd Support
// Input Value  : enumOsd
//                bSupportAll: support _GOSD_PLANE_ALL or not
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonGosdCheckDispOSDSupport(EnumGosdDisplayOSD enumOsd, bit bSupportAll)
{
    switch(enumOsd)
    {
        case _GOSD_PLANE_OSD1:
            return _TRUE;
        case _GOSD_PLANE_OSD2:
            return _TRUE;
        case _GOSD_PLANE_OSD3:
            return _TRUE;
        case _GOSD_PLANE_ALL:
            if(bSupportAll == _TRUE)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Reset Display Osd FW settings
// Input Value  : enumOsd : OSD1, OSD2, OSD3, OSD_All
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDisplayOsdResetSync(EnumGosdDisplayOSD enumOsd, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _TRUE) == _FALSE)
    {
        DebugMessageGOSD("DisplayOsdResetSync error: OSD not support", enumOsd);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSyncCmdBodyDispOsdReset *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDispOsdReset);
    pstDest->enumOSD = enumOsd;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_DISP_OSD_RESET);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Display Gosd Surface
// Input Value  : enumOsd : OSD1, OSD2, OSD3
//                ulSurfaceId : Surface index
//                pstWinRect : Window Rectangle (W/H/X/Y)
//                pstDispRect : Display Rectangle (W/H/X/Y)
//                enumDBApply
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDisplaySurfaceSync(EnumGosdDisplayOSD enumOsd, DWORD ulSurfaceId, StructGosdRectangle *pstWinRect, StructGosdRectangle *pstDispRect, EnumDBApply enumDBApply, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("DisplaySurfaceSync error: OSD not support", enumOsd);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSyncCmdBodyDispOsdDisplaySurface *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDispOsdDisplaySurface);
    pstDest->enumOSD = enumOsd;
    pstDest->ulSurfaceId = ulSurfaceId;
    memcpy(&(pstDest->stWinRect), pstWinRect, sizeof(StructGosdRectangle));
    memcpy(&(pstDest->stDispRect), pstDispRect, sizeof(StructGosdRectangle));
    pstDest->enumDBApply = enumDBApply;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_DISP_OSD_DISPLAY_SURFACE);

    return UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
}

//--------------------------------------------------
// Description  : Set OSD Disable
// Input Value  : enumOsd : OSD1, OSD2, OSD3, OSD_All
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayDisable(EnumGosdDisplayOSD enumOsd, EnumDBApply enumDBApply)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _TRUE) == _FALSE)
    {
        DebugMessageGOSD("DisplayDisable error: OSD not support", enumOsd);
        return;
    }

    ScalerGosdDispOsdSetGdmaOsdDisable(enumOsd, enumDBApply);

    if(enumOsd == _GOSD_PLANE_ALL)
    {
        g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_OSD1] = _GOSD_SURFACE_NUMBER;
        g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_OSD2] = _GOSD_SURFACE_NUMBER;
        g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_OSD3] = _GOSD_SURFACE_NUMBER;
    }
    else
    {
        g_pulGosdDispOsdDisplayingSurfaceId[enumOsd] = _GOSD_SURFACE_NUMBER;
    }
}

//--------------------------------------------------
// Description  : Get Gosd Displaying status
// Input Value  : enumOsd : OSD1, OSD2, OSD3, OSD_All
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonGosdGetDisplaying(EnumGosdDisplayOSD enumOsd)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _TRUE) == _FALSE)
    {
        DebugMessageGOSD("GetDisplaying error: OSD not support", enumOsd);
        return _FALSE;
    }

    return ScalerGosdDispOsdGetDisplaying(enumOsd);
}

//--------------------------------------------------
// Description  : Get Gosd Displaying Param
// Input Value  : enumOsd : OSD1, OSD2, OSD3
//              : pstOsdParam [out] : Displaying Param
//              : ulWaitTimeout
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDisplayGetOsdParamSync(EnumGosdDisplayOSD enumOsd, StructGosdDisplayOsdParam *pstOsdParam, DWORD ulWaitTimeout)
{
    DWORD ulTimeCount = 0;

    if(UserCommonGosdCheckCmdDone(&ulTimeCount, ulWaitTimeout) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_BUSY;
    }

    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("GetOsdParamSync error: OSD not support", enumOsd);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSyncCmdBodyDispOsdGetOsdParam *pstDest = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDispOsdGetOsdParam);
    pstDest->enumOSD = enumOsd;

    SET_GOSD_SYNC_FEEDBACK(_GOSD_SYNC_FEEDBACK_BUSY);
    SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_DISP_OSD_GET_OSD_PARAM);

    EnumGosdSyncCmdFeedBack enumReturn = UserCommonGosdPollingSyncFeedBack(&ulTimeCount, ulWaitTimeout);
    if(enumReturn == _GOSD_SYNC_FEEDBACK_SUCCESS)
    {
        // copy Osd Param
        memcpy(pstOsdParam, &(pstDest->stOsdParam), sizeof(StructGosdDisplayOsdParam));
    }

    return enumReturn;
}


//--------------------------------------------------
// Description  : Stop and Reset Continuous Step
// Input Value  : enumOsd : OSD1, OSD2, OSD3, OSD_All
// Output Value : None
//--------------------------------------------------
void UserCommonGosdContinuousReset(EnumGosdDisplayOSD enumOsd)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _TRUE) == _FALSE)
    {
        DebugMessageGOSD("ContinuousReset error: OSD not support", enumOsd);
        return;
    }

    ScalerGosdContinuousDisable(enumOsd);
}

//--------------------------------------------------
// Description  : Set Continuous Step : Display Surface
// Input Value  : ucStepIdx : Continuous step index
//                enumOsd : OSD1, OSD2, OSD3
//                ulSurfaceId : Surface index
//                pstWinRect : Window Rectangle (W/H/X/Y)
//                pstDispRect : Display Rectangle (W/H/X/Y)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonGosdContinuousStepDisplay(BYTE ucStepIdx, EnumGosdDisplayOSD enumOsd, DWORD ulSurfaceId, StructGosdRectangle *pstWinRect, StructGosdRectangle *pstDispRect)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("ContinuousStepDisplay error: OSD not support", enumOsd);
        return _FALSE;
    }

    // check step index
    if(ucStepIdx >= _GOSD_CONTINUOUS_STEP_MAX)
    {
        DebugMessageGOSD("Continuous step out of range", ucStepIdx);
        return _FALSE;
    }

#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    StructCpuSyncGosdContinuousSetStepCmd *pstCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncGosdSetStepCmd;
#elif(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
    StructCpuSyncGosdContinuousSetStepCmd *pstCmd = &g_stGosdContinuousSetStepCmd;
#endif

    pstCmd->ucStepIndex = ucStepIdx;

    pstCmd->ulSurfaceId = ulSurfaceId;
    pstCmd->usWinRectW = pstWinRect->stSize.usW;
    pstCmd->usWinRectH = pstWinRect->stSize.usH;
    pstCmd->usWinRectX = pstWinRect->stPosition.usX;
    pstCmd->usWinRectY = pstWinRect->stPosition.usY;

    pstCmd->usDispRectW = pstDispRect->stSize.usW;
    pstCmd->usDispRectH = pstDispRect->stSize.usH;
    pstCmd->usDispRectX = pstDispRect->stPosition.usX;
    pstCmd->usDispRectY = pstDispRect->stPosition.usY;

    pstCmd->ucDisplayOSD = enumOsd;

    // continuous step will execute in interrupt, must set _DB_APPLY_NO_POLLING
    pstCmd->ucDBApply = _DB_APPLY_NO_POLLING;

    g_pstGosdContinuousParam[pstCmd->ucDisplayOSD].bGosdContinuousPause = _TRUE;
#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_GOSD_CONTINUOUS_SET_STEP, _SCALER_CPU_SYNC_TIMEOUT_GOSD, _NULL_POINTER);
#elif((_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE) && (_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE))
    ScalerGosdContinuousSetStepProc();
#endif
    g_pstGosdContinuousParam[pstCmd->ucDisplayOSD].bGosdContinuousPause = _FALSE;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Continuous Step : Change Display Position
// Input Value  : ucStepIdx : Continuous step index
//                enumOsd : OSD1, OSD2, OSD3
//                pstDispPosition : Display Position (X/Y)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonGosdContinuousStepDisplayChangePosition(BYTE ucStepIdx, EnumGosdDisplayOSD enumOsd, StructGosdPosition *pstDispPosition)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("ContinuousStepDisplayChangePosition error: OSD not support", enumOsd);
        return _FALSE;
    }

    // check step index
    if(ucStepIdx >= _GOSD_CONTINUOUS_STEP_MAX)
    {
        DebugMessageGOSD("Continuous step out of range", ucStepIdx);
        return _FALSE;
    }

#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    StructCpuSyncGosdContinuousStepChangePositionCmd *pstCmd = &g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncGosdChangePositionCmd;
#elif(_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE)
    StructCpuSyncGosdContinuousStepChangePositionCmd *pstCmd = &g_stGosdContinuousChangePositionCmd;
#endif
    pstCmd->ucDisplayOSD = enumOsd;
    pstCmd->ucStepIndex = ucStepIdx;
    pstCmd->usPositionX = pstDispPosition->usX;
    pstCmd->usPositionY = pstDispPosition->usY;

    g_pstGosdContinuousParam[enumOsd].bGosdContinuousPause = _TRUE;
#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_GOSD_CONTINUOUS_STEP_CHANGE_POSITION, _SCALER_CPU_SYNC_TIMEOUT_GOSD, _NULL_POINTER);
#elif((_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE) && (_IS_MAIN_PROCESS_CPU == _FALSE))
    ScalerGosdContinuousStepChangePositionProc();
#endif
    g_pstGosdContinuousParam[enumOsd].bGosdContinuousPause = _FALSE;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Enable Continuous
// Input Value  : ucTimerMs : timer in ms
//                enumOsd : OSD1, OSD2, OSD3
//                enumType : continuous type
//                ucTotalStepNumber : Total Step Number
// Output Value : None
//--------------------------------------------------
void UserCommonGosdContinuousEnable(BYTE ucTimerMs, EnumGosdDisplayOSD enumOsd, EnumGosdContinuousType enumType, BYTE ucTotalStepNumber)
{
    if(ucTotalStepNumber > _GOSD_CONTINUOUS_STEP_MAX)
    {
        DebugMessageGOSD("ucTotalStepNumber is out of range", ucTotalStepNumber);
        return;
    }

    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("ContinuousEnable error: OSD not support", enumOsd);
        return;
    }

    ScalerGosdContinuousEnable(ucTimerMs, enumOsd, enumType, ucTotalStepNumber);
}

//--------------------------------------------------
// Description  : Run current Continuous Step immediately
// Input Value  : enumOsd : OSD1, OSD2, OSD3
// Output Value : None
//--------------------------------------------------
void UserCommonGosdContinuousUrgentChange(EnumGosdDisplayOSD enumOsd)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("ContinuousUrgentChange error: OSD not support", enumOsd);
        return;
    }

#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    UnionCpuSyncReplyCmdBody unCpuSyncToScpuCmdReplyBody = {0};
    g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncGosdCmd.ucDispPlane = enumOsd;
    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_GOSD_CONTINUOUS, _SCALER_CPU_SYNC_TIMEOUT_GOSD, &unCpuSyncToScpuCmdReplyBody);
#elif((_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE) && (_IS_MAIN_PROCESS_CPU == _FALSE))
    g_stGosdContinuousCmd.ucDispPlane = enumOsd;
    ScalerGosdContinuousProc();
#endif
}

//--------------------------------------------------
// Description  : Get continuous status
// Input Value  : enumOSD: OSD1, OSD2, OSD3, OSD_All
// Output Value : _TRUE: running / _FALSE: none
//--------------------------------------------------
bit UserCommonGosdGetContinuousStatus(EnumGosdDisplayOSD enumOsd)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _TRUE) == _FALSE)
    {
        DebugMessageGOSD("GetContinuousStatus error: OSD not support", enumOsd);
        return _FALSE;
    }

    if(enumOsd == _GOSD_PLANE_ALL)
    {
        return ((g_pstGosdContinuousParam[_GOSD_PLANE_OSD1].enumGosdContinuousType != _GOSD_CONTINUOUS_NONE) ||
                (g_pstGosdContinuousParam[_GOSD_PLANE_OSD2].enumGosdContinuousType != _GOSD_CONTINUOUS_NONE) ||
                (g_pstGosdContinuousParam[_GOSD_PLANE_OSD3].enumGosdContinuousType != _GOSD_CONTINUOUS_NONE));
    }

    return (g_pstGosdContinuousParam[enumOsd].enumGosdContinuousType != _GOSD_CONTINUOUS_NONE);
}

//--------------------------------------------------
// Description  : Set DispOsd Sharpness params
// Input Value  : enumOsd : GOsd plane
//                *pulSharpnessTable : params
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayOsdSharpnessSetting(EnumGosdDisplayOSD enumOsd, DWORD *pulSharpnessTable, EnumDBApply enumDBApply)
{
    ScalerGosdDispOsdSetRegSharpness(enumOsd, pulSharpnessTable, enumDBApply);
}


//--------------------------------------------------
// Description  : Display OSD Double Buffer Apply
// Input Value  : enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayOsdDBApply(EnumDBApply enumDBApply)
{
    ScalerGosdDispOsdSetGdmaDBApply(enumDBApply);
}

//--------------------------------------------------
// Description  : Display OSD Set Double Buffer Trigger Event
// Input Value  : enumDBEvent: _DB_TRIGGER_EVENT_DVS or _DB_TRIGGER_EVENT_DEN_STOP
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayOsdSetDBTriggerEvent(EnumGosdGdmaDBTriggerEvent enumDBEvent)
{
    ScalerGosdDispOsdSetGdmaSetDBTriggerEvent(enumDBEvent);
}

//--------------------------------------------------
// Description  : Set Clear Region
// Input Value  : enumOsd : OSD1, OSD2, OSD3
//                stClear_x
//                stClear_y
//                ucClearEnable
//                enumDBApply
// Output Value : None
//--------------------------------------------------
EnumGosdGdmaStatus UserCommonGosdDisplayOsdSetClearRegion(EnumGosdDisplayOSD enumOsd, StructGosdGdmaClearX stClear_x, StructGosdGdmaClearY stClear_y, bit bClearEnable, EnumDBApply enumDBApply)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("SetClearRegion error: OSD not support", enumOsd);
        return _GDMA_FAIL;
    }

    return ScalerGosdDispOsdSetGdmaClearRegion(enumOsd, stClear_x, stClear_y, bClearEnable, enumDBApply);
}

//--------------------------------------------------
// Description  : Set OSDx Mixer enable
// Input Value  : enumOsd : OSD1, OSD2, OSD3, OSD_All
//                ucEnable
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayOsdSetMixerOSDEnable(EnumGosdDisplayOSD enumOsd, bit bEnable, EnumDBApply enumDBApply)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _TRUE) == _FALSE)
    {
        DebugMessageGOSD("SetMixerOSDEnable error: OSD not support", enumOsd);
        return;
    }

    ScalerGosdDispOsdSetMixerOSDEnable(enumOsd, bEnable, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Mixer Plane Alpha, Offset
// Input Value  : enumMixerOrder
//                stARGB
//                ucPlaneAlphaEnable
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayOsdSetMixerPlaneAlpha(EnumGosdMixerOrder enumMixerOrder, StructGosdMixerPlaneAlpha_ARGB stAlphaARGB, StructGosdMixerPlaneOffset_ARGB stOffsetARGB, BYTE ucPlaneAlphaEnable, EnumDBApply enumDBApply)
{
    ScalerGosdDispOsdSetMixerPlaneAlpha(enumMixerOrder, stAlphaARGB, stOffsetARGB, ucPlaneAlphaEnable, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Mixer Layer Select
// Input Value  : enumOSD: Osd1, Osd2, Osd3
//                enumMixerOrder: C0, C1, C2
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDispOsdSetMixerLayer(EnumGosdDisplayOSD enumOsd, EnumGosdMixerOrder enumMixerOrder, EnumDBApply enumDBApply)
{
    if(UserCommonGosdCheckDispOSDSupport(enumOsd, _FALSE) == _FALSE)
    {
        DebugMessageGOSD("SetMixerLayer error: OSD not support", enumOsd);
        return;
    }

    ScalerGosdDispOsdSetMixerLayer(enumOsd, enumMixerOrder, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Mixer Blend
// Input Value  : pstMixer
//                enumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonGosdDisplayOsdSetMixerBlend(StructGosdMixerLayerSetting *pstMixer, EnumDBApply enumDBApply)
{
    ScalerGosdDispOsdSetMixerFactor(pstMixer, enumDBApply);
}
#endif // #if(_GOSD_FW_COMPILE_REQUEST_FLOW == _TRUE)

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
//--------------------------------------------------
// Description  : Get Surface Info
// Input Value  : pstSurface : Surface
// Output Value : Surface Info
//--------------------------------------------------
StructGosdSurfaceInfo UserCommonGosdGetSurfaceInfo(DWORD ulSurfaceId)
{
    return ScalerGosdGetSurfaceInfo(ulSurfaceId);
}

//--------------------------------------------------
// Description  : Convert Surface to DrawSurface
// Input Value  : *pstSurface : Surface
//                *pstSeSurface : DrawSurface
// Output Value : None
//--------------------------------------------------
void UserCommonGosdSurfaceInfoToSeSurface(StructGosdSurfaceInfo *pstSurface, StructGosdSeSurfaceInfo *pstSeSurface)
{
    switch(pstSurface->enumPixelFormat)
    {
        case _GOSD_PIXEL_FORMAT_ARGB8888:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_ARGB8888;
            break;
        case _GOSD_PIXEL_FORMAT_RGB888:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_RGB888;
            break;
        case _GOSD_PIXEL_FORMAT_ARGB4444:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_ARGB4444;
            break;
        case _GOSD_PIXEL_FORMAT_ARGB1555:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_ARGB1555;
            break;
        case _GOSD_PIXEL_FORMAT_RGB565:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_RGB565;
            break;
        case _GOSD_PIXEL_FORMAT_INDEX8:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_INDEX8;
            break;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_PIXEL_FORMAT_AFBC4U8:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8;
            break;
        case _GOSD_PIXEL_FORMAT_AFBC3U8:
            pstSeSurface->enumFormat = _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8;
            break;
#endif
        default:
            break;
    }
    pstSeSurface->enumArgbOrder = (EnumGosdSeArgbOrder)pstSurface->enumARGBOrder;
    pstSeSurface->ulAddress = pstSurface->ulAddress;
    pstSeSurface->ulLength = pstSurface->ulLength;
    pstSeSurface->usPitch = pstSurface->usPitch;
    pstSeSurface->usFullWidth = pstSurface->usWidth;
    pstSeSurface->usFullHeight = pstSurface->usHeight;
    pstSeSurface->bBigEndian = pstSurface->b1BigEndian;

#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    if((pstSeSurface->enumFormat == _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8) || (pstSeSurface->enumFormat == _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8))
    {
        pstSeSurface->ulAddressC1 = pstSeSurface->ulAddress + (DWORD)((pstSeSurface->usFullWidth / 32) * (pstSeSurface->usFullHeight / 8) * 16);
        pstSeSurface->usPitchC1 = pstSeSurface->usPitch;
    }
    else
#endif
    {
        pstSeSurface->ulAddressC1 = 0;
        pstSeSurface->usPitchC1 = 0;
    }

    // Index8 Order in DDR fixed at R->G->B->A, this setting convert to A->R->G->B
    if(pstSeSurface->enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        pstSeSurface->enumArgbOrder = _GOSD_SEINFO_ARGB_ORDER_BARG;
    }

    pstSeSurface->ulClutAddress = pstSurface->ulClutAddress;
    pstSeSurface->ulSurfaceId = pstSurface->ulSurfaceId;
}

//--------------------------------------------------
// Description : convert Blend function to Alpha mode
// Input Value : EnumGosdSeBitBlitMode : BitBlit mode
// Output Value : EnumGosdSeBlendingMode
//--------------------------------------------------
EnumGosdSeBlendingMode UserCommonGosdGetBlendingMode(EnumGosdSeBitBlitMode enumMode)
{
    switch(enumMode)
    {
        case _GOSD_BITBLIT_MODE_ROP:
            return _GOSD_SEINFO_BLENDING_ROP;

        case _GOSD_BITBLIT_MODE_FB:
            return _GOSD_SEINFO_BLENDING_FB;

        case _GOSD_BITBLIT_MODE_GL:
            return _GOSD_SEINFO_BLENDING_GL;

        case _GOSD_BITBLIT_MODE_ALPHA:
            return _GOSD_SEINFO_BLENDING_ALPHA;

        default:
            return _GOSD_SEINFO_BLENDING_MAX;
            break;
    }
}

//--------------------------------------------------
// Description : get colorkey mode
// Input Value : ulBlitFlags : BitBlit flag
// Output Value : EnumGosdSeBlendingColorkeyMode : colokey mode
//--------------------------------------------------
EnumGosdSeBlendingColorkeyMode UserCommonGosdGetColorKeyMode(DWORD ulBlitFlags)
{
    if((ulBlitFlags & _GOSD_BITBLIT_SRC_COLORKEY) != 0)
    {
        return _GOSD_SEINFO_BLENDING_COLORKEY_SOURCE;
    }
    else if((ulBlitFlags & _GOSD_BITBLIT_DST_COLORKEY) != 0)
    {
        return _GOSD_SEINFO_BLENDING_COLORKEY_DESTINATION;
    }
    else if((ulBlitFlags & (_GOSD_BITBLIT_SRC_COLORKEY | _GOSD_BITBLIT_DST_COLORKEY)) != 0)
    {
        return _GOSD_SEINFO_BLENDING_COLORKEY_BOTH;
    }
    else
    {
        return _GOSD_SEINFO_BLENDING_COLORKEY_NONE;
    }
}

//--------------------------------------------------
// Description : convert Blend function to Alpha mode
// Input Value : enumBlendFunction : blending function
// Output Value : EnumGosdSeBlendingAlphaMode
//--------------------------------------------------
EnumGosdSeBlendingAlphaMode UserCommonGosdGetAlphaMode(EnumGosdSeBlendFunction enumBlendFunction)
{
    switch(enumBlendFunction)
    {
        case _GOSD_BLEND_ZERO:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONSTANT_0;
        case _GOSD_BLEND_ONE:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONSTANT_1;
        case _GOSD_BLEND_DESTALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_DEST;
        case _GOSD_BLEND_INVDESTALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_DEST;
        case _GOSD_BLEND_SRCALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_SRC;
        case _GOSD_BLEND_INVSRCALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_SRC;
        case _GOSD_BLEND_CONSTALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONST;
        case _GOSD_BLEND_INVCONSTALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_CONST;
        default:
            return _GOSD_SEINFO_BLENDING_DFB_ALPHA_MAX;
    }
}

//--------------------------------------------------
// Description : convert Blend function to Color mode
// Input Value : enumBlendFunction : blending function
// Output Value : EnumGosdSeBlendingColorMode
//--------------------------------------------------
EnumGosdSeBlendingColorMode UserCommonGosdGetColorMode(EnumGosdSeBlendFunction enumBlendFunction)
{
    switch(enumBlendFunction)
    {
        case _GOSD_BLEND_ZERO:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_CONSTANT_0;
        case _GOSD_BLEND_ONE:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_CONSTANT_1;
        case _GOSD_BLEND_DESTALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_DESTALPHA;
        case _GOSD_BLEND_INVDESTALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_1_DESTALPHA;
        case _GOSD_BLEND_SRCALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_SRCALPHA;
        case _GOSD_BLEND_INVSRCALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_1_SRCALPHA;
        case _GOSD_BLEND_SRCCOLOR:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_SRCCLR;
        case _GOSD_BLEND_INVSRCCOLOR:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_1_SRCCLR;
        case _GOSD_BLEND_DESTCOLOR:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_DESTCLR;
        case _GOSD_BLEND_INVDESTCOLOR:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_1_DESTCLR;
        case _GOSD_BLEND_MINALPHA:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_MIN_SRCALPHA_1_DESTALPHA;
        default:
            return _GOSD_SEINFO_BLENDING_DFB_CLR_MAX;
    }
}


//--------------------------------------------------
// Description : set BitBlit blend function
// Input Value : pstBitBlitInfo : blending function set by below arguments
//               ulBlitFlags : BitBlit flag
//               pstBlitSettings : BitBlit settings
// Output Value : None
//--------------------------------------------------
void UserCommonGosdSetBlendFunction(StructGosdSeBitBlitInfo *pstBitBlitInfo, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings)
{
    pstBitBlitInfo->enumModeSel = UserCommonGosdGetBlendingMode(pstBlitSettings->enumMode);

    switch (pstBitBlitInfo->enumModeSel)
    {
        case _GOSD_SEINFO_BLENDING_ROP:
            pstBitBlitInfo->enumRopCode = _GOSD_SEINFO_ROPCODE_COPY;
            break;
        case _GOSD_SEINFO_BLENDING_ALPHA:
            pstBitBlitInfo->enumColorKeyModeSel = UserCommonGosdGetColorKeyMode(ulBlitFlags);
            pstBitBlitInfo->ulSrcColorKeyValue = pstBlitSettings->unBitBlitSettings.stAlphaSettings.ulSrcColorKey;
            pstBitBlitInfo->ulDstColorKeyValue = pstBlitSettings->unBitBlitSettings.stAlphaSettings.ulDestColorKey;
            pstBitBlitInfo->enumSrcAlphaModeSel = UserCommonGosdGetAlphaMode(pstBlitSettings->unBitBlitSettings.stAlphaSettings.enumSrcAlphaBlend);
            pstBitBlitInfo->enumDstAlphaModeSel = UserCommonGosdGetAlphaMode(pstBlitSettings->unBitBlitSettings.stAlphaSettings.enumDestAlphaBlend);
            pstBitBlitInfo->ucSrcAlphaValue = pstBlitSettings->unBitBlitSettings.stAlphaSettings.ucSrcAlpha;
            pstBitBlitInfo->ucDstAlphaValue = pstBlitSettings->unBitBlitSettings.stAlphaSettings.ucDestAlpha;
            break;
        case _GOSD_SEINFO_BLENDING_FB:
            pstBitBlitInfo->enumColorKeyModeSel = UserCommonGosdGetColorKeyMode(ulBlitFlags);
            pstBitBlitInfo->ulSrcColorKeyValue = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ulSrcColorKey;
            pstBitBlitInfo->ulDstColorKeyValue = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ulDestColorKey;
            if((ulBlitFlags & _GOSD_BITBLIT_BLEND_ALPHACHANNEL) != 0)
            {
                pstBitBlitInfo->bEnableAlphaChannel = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_BLEND_COLORALPHA) != 0)
            {
                pstBitBlitInfo->bEnableColorAlpha = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_COLORIZE) != 0)
            {
                pstBitBlitInfo->bEnableColorize = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_SRC_PREMULTIPLY) != 0)
            {
                pstBitBlitInfo->bEnableDstPremultiply = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_DST_PREMULTIPLY) != 0)
            {
                pstBitBlitInfo->bEnableDstPremultiply = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_DEMULTIPLY) != 0)
            {
                pstBitBlitInfo->bEnableDemultiply = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_SRC_PREMULTCOLOR) != 0)
            {
                pstBitBlitInfo->bEnableSrcPremulcolor = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_XOR) != 0)
            {
                pstBitBlitInfo->bEnableXor = _ENABLE;
            }
            pstBitBlitInfo->enumSrcAlphaModeSel = UserCommonGosdGetAlphaMode(pstBlitSettings->unBitBlitSettings.stDirectFbSettings.enumSrcAlphaBlend);
            pstBitBlitInfo->enumDstAlphaModeSel = UserCommonGosdGetAlphaMode(pstBlitSettings->unBitBlitSettings.stDirectFbSettings.enumDestAlphaBlend);
            pstBitBlitInfo->enumSrcClrModeSel = UserCommonGosdGetColorMode(pstBlitSettings->unBitBlitSettings.stDirectFbSettings.enumSrcColorBlend);
            pstBitBlitInfo->enumDstClrModeSel = UserCommonGosdGetColorMode(pstBlitSettings->unBitBlitSettings.stDirectFbSettings.enumDestColorBlend);
            pstBitBlitInfo->ucSrcAlphaValue = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ucSrcAlpha;
            pstBitBlitInfo->ucDstAlphaValue = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ucDestAlpha;
            pstBitBlitInfo->ucConstAlphaValue = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ucConstAlpha;
            pstBitBlitInfo->ucConstAlphaValueForBlendColor = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ucConstAlphaForBlendColor;
            pstBitBlitInfo->ulConstClrValue = pstBlitSettings->unBitBlitSettings.stDirectFbSettings.ulColor;
            break;
        case _GOSD_SEINFO_BLENDING_GL:
            pstBitBlitInfo->enumColorKeyModeSel = UserCommonGosdGetColorKeyMode(ulBlitFlags);
            pstBitBlitInfo->ulSrcColorKeyValue = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ulSrcColorKey;
            pstBitBlitInfo->ulDstColorKeyValue = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ulDestColorKey;
            if((ulBlitFlags & _GOSD_BITBLIT_BLEND_ALPHACHANNEL) != 0)
            {
                pstBitBlitInfo->bEnableAlphaChannel = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_BLEND_COLORALPHA) != 0)
            {
                pstBitBlitInfo->bEnableColorAlpha = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_COLORIZE) != 0)
            {
                pstBitBlitInfo->bEnableColorize = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_SRC_PREMULTIPLY) != 0)
            {
                pstBitBlitInfo->bEnableDstPremultiply = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_DST_PREMULTIPLY) != 0)
            {
                pstBitBlitInfo->bEnableDstPremultiply = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_DEMULTIPLY) != 0)
            {
                pstBitBlitInfo->bEnableDemultiply = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_SRC_PREMULTCOLOR) != 0)
            {
                pstBitBlitInfo->bEnableSrcPremulcolor = _ENABLE;
            }
            if((ulBlitFlags & _GOSD_BITBLIT_XOR) != 0)
            {
                pstBitBlitInfo->bEnableXor = _ENABLE;
            }
#if(_HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT == _ON)
            pstBitBlitInfo->ucGLSrcAlphaIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucSrcAlphaBlend;
            pstBitBlitInfo->ucGLDstAlphaIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucDestAlphaBlend;
            pstBitBlitInfo->ucGLSrcClrIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucSrcColorBlend;
            pstBitBlitInfo->ucGLDstClrIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucDestColorBlend;
#else
            pstBitBlitInfo->b6GLSrcAlphaIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.b6SrcAlphaBlend;
            pstBitBlitInfo->b6GLDstAlphaIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.b6DestAlphaBlend;
            pstBitBlitInfo->b6GLSrcClrIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.b6SrcColorBlend;
            pstBitBlitInfo->b6GLDstClrIndex = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.b6DestColorBlend;
#endif
            pstBitBlitInfo->ucSrcAlphaValue = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucSrcAlpha;
            pstBitBlitInfo->ucDstAlphaValue = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucDestAlpha;
            pstBitBlitInfo->ucConstAlphaValue = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucConstAlpha;
            pstBitBlitInfo->ucConstAlphaValueForBlendColor = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ucConstAlphaForBlendColor;
            pstBitBlitInfo->ulConstClrValue = pstBlitSettings->unBitBlitSettings.stOpenGlSettings.ulColor;
            break;
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Create surface
// Input Value  : ulSurfaceId : Surface
//                pstSurfaceHeader : surface header
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdCreateSurface(DWORD ulSurfaceId, StructGosdSurfaceHeader *pstSurfaceHeader)
{
    if(GOSD_GET_SURFACE_STATUS(ulSurfaceId) != _GOSD_SURFACE_UNCREATED)
    {
        DebugMessageGOSD("Surface already created", ulSurfaceId);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    DWORD ulAddress = ScalerGosdMemoryAllocate(sizeof(StructGosdSurfaceHeader) + pstSurfaceHeader->ulLength, pstSurfaceHeader->ulAddress);

    if(ulAddress == _GOSD_NULL_ADDRESS)
    {
        // memory allocate fail
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    else
    {
        GOSD_SET_SURFACE_ADDRESS(ulSurfaceId, ulAddress);
        GOSD_SET_SURFACE_STATUS(ulSurfaceId, _GOSD_SURFACE_UNDEFINED);

        pstSurfaceHeader->ulAddress = ulAddress;
        ScalerGosdSetSurfaceHeader(ulSurfaceId, pstSurfaceHeader);
    }

    return _GOSD_SYNC_FEEDBACK_SUCCESS;
}

//--------------------------------------------------
// Description  : Release surface
// Input Value  : pstSurface
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdReleaseSurface(DWORD ulSurfaceId)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        // surface was not created yet
        return _GOSD_SYNC_FEEDBACK_SUCCESS;
    }

    // check surface status
    EnumGosdSurfaceStatus enumStatus = GOSD_GET_SURFACE_STATUS(ulSurfaceId);
    if((enumStatus != _GOSD_SURFACE_UNCREATED) &&
       (enumStatus != _GOSD_SURFACE_UNDEFINED) &&
       (enumStatus != _GOSD_SURFACE_IDLE))
    {
        DebugMessageGOSD("Surface cannot release", ulSurfaceId);
        DebugMessageGOSD("  Status", enumStatus);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    ScalerGosdMemoryFree(GOSD_GET_SURFACE_ADDRESS(ulSurfaceId));

    GOSD_SET_SURFACE_ADDRESS(ulSurfaceId, _GOSD_SURFACE_UNCREATED_ADDRESS);
    GOSD_SET_SURFACE_STATUS(ulSurfaceId, _GOSD_SURFACE_UNCREATED);

    return _GOSD_SYNC_FEEDBACK_SUCCESS;
}

//--------------------------------------------------
// Description  : Release multi surfaces
// Input Value  : pstSurface : free from this block
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdReleaseMultiSurface(DWORD ulSurfaceId)
{
    for(DWORD ulSurfaceCnt = ulSurfaceId; ulSurfaceCnt < _GOSD_SURFACE_NUMBER; ulSurfaceCnt++)
    {
        UserCommonGosdReleaseSurface(ulSurfaceCnt);
    }

    return _GOSD_SYNC_FEEDBACK_SUCCESS;
}

//--------------------------------------------------
// Description  : set Surface Header
// Input Value  : ulSurfaceId : Surface
//                pstSurfaceHeader : Surface Header Value
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonGosdSetSurfaceHeader(DWORD ulSurfaceId, StructGosdSurfaceHeader *pstSurfaceHeader)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        return _FAIL;
    }

    ScalerGosdSetSurfaceHeader(ulSurfaceId, pstSurfaceHeader);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : get Surface Header
// Input Value  : pstHeader : output surface header
//                ulSurfaceId : Surface
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonGosdGetSurfaceHeader(StructGosdSurfaceHeader *pstHeader, DWORD ulSurfaceId)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        return _FAIL;
    }

    memcpy(pstHeader, ScalerGosdGetSurfaceHeader(ulSurfaceId), sizeof(StructGosdSurfaceHeader));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : set Surface Status
// Input Value  : ulSurfaceId : Surface
//                enumStatus : Status Value
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonGosdSetSurfaceHeaderStatus(DWORD ulSurfaceId, EnumGosdSurfaceStatus enumStatus)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        return _FAIL;
    }

    GOSD_SET_SURFACE_STATUS(ulSurfaceId, enumStatus);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : get Surface Status
// Input Value  : ulSurfaceId : Surface
// Output Value : Status
//--------------------------------------------------
EnumGosdSurfaceStatus UserCommonGosdGetSurfaceHeaderStatus(DWORD ulSurfaceId)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        return _GOSD_SURFACE_UNCREATED;
    }

    return GOSD_GET_SURFACE_STATUS(ulSurfaceId);
}

//--------------------------------------------------
// Description  : set Load Image Info
// Input Value  : ulSurfaceId : Surface
//                pstLoadImageInfo : load image info
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdSetLoadImageInfo(DWORD ulSurfaceId, StructGosdLoadImageInfo *pstLoadImageInfo)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        DebugMessageGOSD("Surface not created", ulSurfaceId);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // check surface status
    EnumGosdSurfaceStatus enumStatus = GOSD_GET_SURFACE_STATUS(ulSurfaceId);

    if((enumStatus != _GOSD_SURFACE_UNDEFINED) &&
       (enumStatus != _GOSD_SURFACE_IDLE))
    {
        DebugMessageGOSD("Surface cannot Load image", 0);
        DebugMessageGOSD("  Surface ID", ulSurfaceId);
        DebugMessageGOSD("  Surface Status", enumStatus);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    return ScalerGosdSetLoadImageInfo(ulSurfaceId, pstLoadImageInfo->usImageSourceStartFlashBank, pstLoadImageInfo->usImageIndex);
}

//--------------------------------------------------
// Description  : set SE full surface convert cmd
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdResult : rslt surface
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdImageConvert(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult)
{
    // check surface status
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrc1Layer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrc1SurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    stSrc1Layer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stSrc1Layer.bSelectConst = _DISABLE;
    stSrc1Layer.usDataWidth = stSrc1SurfaceInfo.usWidth;
    stSrc1Layer.usDataHeight = stSrc1SurfaceInfo.usHeight;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrc1SurfaceInfo, &(stSrc1Layer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataWidth = stRsltSurfaceInfo.usWidth;
    stRsltLayer.usDataHeight = stRsltSurfaceInfo.usHeight;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    return (ScalerGosdSeFormatConversion(&stSrc1Layer, &stRsltLayer));
}

//--------------------------------------------------
// Description  : set SE copy paste cmd, read rect from src, dataconvert and write to rslt OutPosition
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdCopyPaste(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition)
{
    // check surface status
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrc1Layer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrc1SurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    stSrc1Layer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stSrc1Layer.bSelectConst = _DISABLE;
    stSrc1Layer.usDataX = stSrcRect.stPosition.usX;
    stSrc1Layer.usDataY = stSrcRect.stPosition.usY;
    stSrc1Layer.usDataWidth = stSrcRect.stSize.usW;
    stSrc1Layer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrc1SurfaceInfo, &(stSrc1Layer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stOutPosition.usX;
    stRsltLayer.usDataY = stOutPosition.usY;
    stRsltLayer.usDataWidth = stSrcRect.stSize.usW;
    stRsltLayer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    return (ScalerGosdSeFormatConversion(&stSrc1Layer, &stRsltLayer));
}

//--------------------------------------------------
// Description  : set SE rotate cmd, read rect from src, dataconvert & rotate and write to rslt OutPosition
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdResult : rslt surface
//                ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
//                enumRotateSel : 0 degree, 90 degree, 270 degeree, 180 degree clockwise
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdRotate(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, EnumOsdRotateType enumRotateSel)
{
    // check surface status
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrc1Layer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrc1SurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    stSrc1Layer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stSrc1Layer.bSelectConst = _DISABLE;
    stSrc1Layer.usDataX = stSrcRect.stPosition.usX;
    stSrc1Layer.usDataY = stSrcRect.stPosition.usY;
    stSrc1Layer.usDataWidth = stSrcRect.stSize.usW;
    stSrc1Layer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrc1SurfaceInfo, &(stSrc1Layer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stOutPosition.usX;
    stRsltLayer.usDataY = stOutPosition.usY;
    stRsltLayer.usDataWidth = stSrcRect.stSize.usW;
    stRsltLayer.usDataHeight = stSrcRect.stSize.usH;

    stRsltLayer.enumRsltRotateModeSel = enumRotateSel;
    stRsltLayer.enumRsltMirrorModeSel = _GOSD_SEINFO_MIRROR_NONE;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    return (ScalerGosdSeFormatConversion(&stSrc1Layer, &stRsltLayer));
}

//--------------------------------------------------
// Description  : set SE rotate cmd, read rect from src, dataconvert & mirror and write to rslt OutPosition
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdResult : rslt surface
//                ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
//                ucMirrorSel : 0: no, 1: x-only, 2: y-only, 3: x&y
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdMirror(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stOutPosition, EnumGosdSeMirrorMode enumMirrorSel)
{
    // check surface status
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrc1Layer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrc1SurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    stSrc1Layer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stSrc1Layer.bSelectConst = _DISABLE;
    stSrc1Layer.usDataX = stSrcRect.stPosition.usX;
    stSrc1Layer.usDataY = stSrcRect.stPosition.usY;
    stSrc1Layer.usDataWidth = stSrcRect.stSize.usW;
    stSrc1Layer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrc1SurfaceInfo, &(stSrc1Layer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stOutPosition.usX;
    stRsltLayer.usDataY = stOutPosition.usY;
    stRsltLayer.usDataWidth = stSrcRect.stSize.usW;
    stRsltLayer.usDataHeight = stSrcRect.stSize.usH;
    stRsltLayer.enumRsltRotateModeSel = _OSD_ROTATE_DEGREE_0;
    stRsltLayer.enumRsltMirrorModeSel = enumMirrorSel;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    return (ScalerGosdSeFormatConversion(&stSrc1Layer, &stRsltLayer));
}

//--------------------------------------------------
// Description  : set SE draw rectangle cmd
// Input Value  : ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutPosition : paste position (x, y)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDrawRectangle(DWORD ulSurfaceIdResult, StructGosdRectangle stRect, DWORD ulColor)
{
    // check surface status
    if(ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrc1Layer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    stSrc1Layer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stSrc1Layer.bSelectConst = _ENABLE;
    stSrc1Layer.ulConstClrValue = ulColor;
    stSrc1Layer.usDataX = 0;
    stSrc1Layer.usDataY = 0;
    stSrc1Layer.usDataWidth = stRect.stSize.usW;
    stSrc1Layer.usDataHeight = stRect.stSize.usH;

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stRect.stPosition.usX;
    stRsltLayer.usDataY = stRect.stPosition.usY;
    stRsltLayer.usDataWidth = stRect.stSize.usW;
    stRsltLayer.usDataHeight = stRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stSrc1Layer.stSurface));
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    // src1 Format should be ARGB8888 in Draw_Rectangle function
    stSrc1Layer.stSurface.enumFormat = _GOSD_SEINFO_COLOR_FORMAT_ARGB8888;
    stSrc1Layer.stSurface.usPitch = (stSrc1Layer.stSurface.usFullWidth << 2);

    return (ScalerGosdSeFormatConversion(&stSrc1Layer, &stRsltLayer));
}

//--------------------------------------------------
// Description  : set SE draw linear_gradient rectangle cmd
// Input Value  : ulSurfaceIdResult : rslt surface
//                stRect : fill rectangle (x, y, w, h)
//                enumLinearGradientMode : x-only / y-only / x & y
//                ulStartColor
//                ulEndColor
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDrawLinearGradientRectangle(DWORD ulSurfaceIdResult, StructGosdRectangle stRect, EnumGosdSeLinearGradientMode enumLinearGradientMode, DWORD ulStartColor, DWORD ulEndColor)
{
    // check surface status
    if(ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }


    StructGosdSeLayerInfo stSrcLayer = {0};
    StructGosdSeLayerInfo stDestLayer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    StructGosdSeBitBlitInfo stBitBlitInfo = {0};
    DWORD ulAbsDiffValue = 0;
    DWORD ulSquare = 0;
    DWORD pulClrStepX[4];
    DWORD pulClrStepY[4];
    DWORD ulLoopCnt = 0;
    DWORD ulWidth = 0;
    DWORD ulHeight = 0;

    stSrcLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC2;
    stSrcLayer.bSelectConst = _DISABLE;
    stSrcLayer.usDataX = 0;
    stSrcLayer.usDataY = 0;
    stSrcLayer.usDataWidth = stRect.stSize.usW;
    stSrcLayer.usDataHeight = stRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stSrcLayer.stSurface));
    // src2 Format should be ARGB8888 in Linear_Gradient function
    stSrcLayer.stSurface.enumFormat = _GOSD_SEINFO_COLOR_FORMAT_ARGB8888;
    stSrcLayer.stSurface.usPitch = (stSrcLayer.stSurface.usFullWidth << 2);

    stDestLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stDestLayer.bSelectConst = _DISABLE;
    stDestLayer.usDataX = 0;
    stDestLayer.usDataY = 0;
    stDestLayer.usDataWidth = stRect.stSize.usW;
    stDestLayer.usDataHeight = stRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stDestLayer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stRect.stPosition.usX;
    stRsltLayer.usDataY = stRect.stPosition.usY;
    stRsltLayer.usDataWidth = stRect.stSize.usW;
    stRsltLayer.usDataHeight = stRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    stBitBlitInfo.enumSrc2LinearGradientModeSel = enumLinearGradientMode;

    switch(enumLinearGradientMode)
    {
        case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_X:
            ulWidth = (DWORD)stRect.stSize.usW;
            break;

        case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_Y:
            ulHeight = (DWORD)stRect.stSize.usH;
            break;

        case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_XY:
        default:
            ulWidth = (DWORD)stRect.stSize.usW;
            ulHeight = (DWORD)stRect.stSize.usH;
            break;
    }

    stBitBlitInfo.ulStartClrValue = ulStartColor;

    // Calaulate ClrStep s5.7
    ulSquare = ulWidth * ulWidth + ulHeight * ulHeight; // ClrStep Denominator
    for(ulLoopCnt = 0; ulLoopCnt < 4; ulLoopCnt++)
    {
        ulAbsDiffValue = ABSDWORD(((ulStartColor >> (ulLoopCnt * 8)) & 0xff), ((ulEndColor >> (ulLoopCnt * 8)) & 0xff));
        pulClrStepX[ulLoopCnt] = (((ulAbsDiffValue * ulWidth) << 7) / ulSquare) & 0xfff;
        pulClrStepY[ulLoopCnt] = (((ulAbsDiffValue * ulHeight) << 7) / ulSquare) & 0xfff;
        // if ClrStep is Negative
        if(((ulEndColor >> (ulLoopCnt * 8)) & 0xff) < ((ulStartColor >> (ulLoopCnt * 8)) & 0xff))
        {
            pulClrStepX[ulLoopCnt] = ((pulClrStepX[ulLoopCnt] == 0) ? 0 : ((0x1000 - pulClrStepX[ulLoopCnt]) | (_BIT12)));
            pulClrStepY[ulLoopCnt] = ((pulClrStepY[ulLoopCnt] == 0) ? 0 : ((0x1000 - pulClrStepY[ulLoopCnt]) | (_BIT12)));
        }
    }
    stBitBlitInfo.usClrStepXAlpha = pulClrStepX[3];
    stBitBlitInfo.usClrStepXRed = pulClrStepX[2];
    stBitBlitInfo.usClrStepXGreen = pulClrStepX[1];
    stBitBlitInfo.usClrStepXBlue = pulClrStepX[0];
    stBitBlitInfo.usClrStepYAlpha = pulClrStepY[3];
    stBitBlitInfo.usClrStepYRed = pulClrStepY[2];
    stBitBlitInfo.usClrStepYGreen = pulClrStepY[1];
    stBitBlitInfo.usClrStepYBlue = pulClrStepY[0];

    StructGosdSeBitBlitSettings stBlitSettings = {0};
    stBlitSettings.enumMode = _GOSD_BITBLIT_MODE_ROP;

    UserCommonGosdSetBlendFunction(&stBitBlitInfo, _GOSD_BITBLIT_NOFX, &stBlitSettings);

    return (ScalerGosdSeBitBlit(&stDestLayer, &stSrcLayer, &stRsltLayer, &stBitBlitInfo));
}

//--------------------------------------------------
// Description  : set SE bitblit paste cmd
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdDestination : dest surface
//                ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stDestPosition : paste position X
//                stOutPosition : paste position Y
//                ulBlitFlags
//                pstBlitSettings
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdBitBlitPaste(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdDestination, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stDestPosition, StructGosdPosition stOutPosition, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings)
{
    // check surface status
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC2) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdDestination, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrcLayer = {0};
    StructGosdSeLayerInfo stDestLayer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrcSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stDestSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdDestination);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);

    StructGosdSeBitBlitInfo stBitBlitInfo = {0};

    stSrcLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC2;
    stSrcLayer.bSelectConst = _DISABLE;
    stSrcLayer.usDataX = stSrcRect.stPosition.usX;
    stSrcLayer.usDataY = stSrcRect.stPosition.usY;
    stSrcLayer.usDataWidth = stSrcRect.stSize.usW;
    stSrcLayer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrcSurfaceInfo, &(stSrcLayer.stSurface));

    stDestLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stDestLayer.bSelectConst = _DISABLE;
    stDestLayer.usDataX = stDestPosition.usX;
    stDestLayer.usDataY = stDestPosition.usY;
    stDestLayer.usDataWidth = stSrcRect.stSize.usW;
    stDestLayer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stDestSurfaceInfo, &(stDestLayer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stOutPosition.usX;
    stRsltLayer.usDataY = stOutPosition.usY;
    stRsltLayer.usDataWidth = stSrcRect.stSize.usW;
    stRsltLayer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    UserCommonGosdSetBlendFunction(&stBitBlitInfo, ulBlitFlags, pstBlitSettings);

    stBitBlitInfo.bLayerControl = _DISABLE;

    return (ScalerGosdSeBitBlit(&stDestLayer, &stSrcLayer, &stRsltLayer, &stBitBlitInfo));
}

//--------------------------------------------------
// Description  : set SE Stretch Paste cmd
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stOutRect : out rectangle (x, y, w, h)
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdStretchPaste(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdRectangle stOutRect)
{
    // check surface status
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FALSE) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FALSE))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrc1Layer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrcSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);
    StructGosdSeStretchInfo stStretchInfo = {0};

    stSrc1Layer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stSrc1Layer.bSelectConst = _DISABLE;
    stSrc1Layer.usDataX = stSrcRect.stPosition.usX;
    stSrc1Layer.usDataY = stSrcRect.stPosition.usY;
    stSrc1Layer.usDataWidth = stSrcRect.stSize.usW;
    stSrc1Layer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrcSurfaceInfo, &(stSrc1Layer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stOutRect.stPosition.usX;
    stRsltLayer.usDataY = stOutRect.stPosition.usY;
    stRsltLayer.usDataWidth = stOutRect.stSize.usW;
    stRsltLayer.usDataHeight = stOutRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    if(stSrc1Layer.stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        stStretchInfo.enumAlgoSel = _GOSD_SEINFO_STRETCH_REPEATE_DROP;
    }
    else
    {
        stStretchInfo.enumAlgoSel = _GOSD_SEINFO_STRETCH_FIR;
    }

    return (ScalerGosdSeStretch(&stSrc1Layer, &stRsltLayer, &stStretchInfo));
}

//--------------------------------------------------
// Description  : set SE stretchbitblit paste cmd
// Input Value  : ulSurfaceIdSource : src surface
//                ulSurfaceIdDestination : dest surface
//                ulSurfaceIdResult : rslt surface
//                stSrcRect : copy rectangle (x, y, w, h)
//                stDestPosition : paste position X
//                stOutPosition : paste position Y
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdStretchBitBlitPaste(DWORD ulSurfaceIdSource, DWORD ulSurfaceIdDestination, DWORD ulSurfaceIdResult, StructGosdRectangle stSrcRect, StructGosdPosition stDestPosition, StructGosdRectangle stOutRect, DWORD ulBlitFlags, StructGosdSeBitBlitSettings *pstBlitSettings)
{
    if((ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdSource, _GOSD_SEINFO_LAYERTYPE_SRC2) == _FAIL) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdDestination, _GOSD_SEINFO_LAYERTYPE_SRC1) == _FAIL) ||
       (ScalerGosdSeCheckSurfaceStatus(ulSurfaceIdResult, _GOSD_SEINFO_LAYERTYPE_RSLT) == _FAIL))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdSeLayerInfo stSrcLayer = {0};
    StructGosdSeLayerInfo stDestLayer = {0};
    StructGosdSeLayerInfo stRsltLayer = {0};
    StructGosdSurfaceInfo stSrcSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdSource);
    StructGosdSurfaceInfo stDestSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdDestination);
    StructGosdSurfaceInfo stRsltSurfaceInfo = UserCommonGosdGetSurfaceInfo(ulSurfaceIdResult);
    StructGosdSeBitBlitInfo stBitBlitInfo = {0};
    StructGosdSeStretchInfo stStretchInfo = {0};

    stSrcLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC2;
    stSrcLayer.bSelectConst = _DISABLE;
    stSrcLayer.usDataX = stSrcRect.stPosition.usX;
    stSrcLayer.usDataY = stSrcRect.stPosition.usY;
    stSrcLayer.usDataWidth = stSrcRect.stSize.usW;
    stSrcLayer.usDataHeight = stSrcRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stSrcSurfaceInfo, &(stSrcLayer.stSurface));

    stDestLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_SRC1;
    stDestLayer.bSelectConst = _DISABLE;
    stDestLayer.usDataX = stDestPosition.usX;
    stDestLayer.usDataY = stDestPosition.usY;
    stDestLayer.usDataWidth = stOutRect.stSize.usW;
    stDestLayer.usDataHeight = stOutRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stDestSurfaceInfo, &(stDestLayer.stSurface));

    stRsltLayer.enumLayerType = _GOSD_SEINFO_LAYERTYPE_RSLT;
    stRsltLayer.bSelectConst = _DISABLE;
    stRsltLayer.usDataX = stOutRect.stPosition.usX;
    stRsltLayer.usDataY = stOutRect.stPosition.usY;
    stRsltLayer.usDataWidth = stOutRect.stSize.usW;
    stRsltLayer.usDataHeight = stOutRect.stSize.usH;
    UserCommonGosdSurfaceInfoToSeSurface(&stRsltSurfaceInfo, &(stRsltLayer.stSurface));

    UserCommonGosdSetBlendFunction(&stBitBlitInfo, ulBlitFlags, pstBlitSettings);

    stBitBlitInfo.bLayerControl = _DISABLE;

    if(stSrcLayer.stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        stStretchInfo.enumAlgoSel = _GOSD_SEINFO_STRETCH_REPEATE_DROP;
    }
    else
    {
        stStretchInfo.enumAlgoSel = _GOSD_SEINFO_STRETCH_FIR;
    }

    return (ScalerGosdSeStretchBitBlit(&stDestLayer, &stSrcLayer, &stRsltLayer, &stStretchInfo, &stBitBlitInfo));
}

//--------------------------------------------------
// Description  : Set Gosd DispOsd display surface
// Input Value  : enumOSD : OSD1, OSD2, OSD3
//                ulSurfaceId : Surface
//                pstWinRect : window size and position
//                pstDispRect : display size and position
//                enumDBApply : wait DB or not
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDisplaySurface(EnumGosdDisplayOSD enumOSD, DWORD ulSurfaceId, StructGosdRectangle *pstWinRect, StructGosdRectangle *pstDispRect, EnumDBApply enumDBApply)
{
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FAIL)
    {
        DebugMessageGOSD("Surface not created", ulSurfaceId);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // check surface status
    EnumGosdSurfaceStatus enumStatus = GOSD_GET_SURFACE_STATUS(ulSurfaceId);
    if((enumStatus != _GOSD_SURFACE_SE_WORKING_READ) &&
       (enumStatus != _GOSD_SURFACE_DISPOSD_SHOWING) &&
       (enumStatus != _GOSD_SURFACE_IDLE))
    {
        DebugMessageGOSD("Surface cannot display", ulSurfaceId);
        DebugMessageGOSD("  Status", enumStatus);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    StructGosdDispOsdDisplayArgument stDest;

    stDest.enumOSD = enumOSD;
    stDest.ulSurfaceId = ulSurfaceId;
    memcpy(&(stDest.stWinRect), pstWinRect, sizeof(StructGosdGdmaRectangle));
    memcpy(&(stDest.stDispRect), pstDispRect, sizeof(StructGosdGdmaRectangle));
    stDest.enumDBApply = enumDBApply;

    return ScalerGosdDispOsdDisplaySurface(&stDest);
}

//--------------------------------------------------
// Description  : Get Gosd Displaying Param
// Input Value  : enumOsd : OSD1, OSD2, OSD3
//              : pstOsdParam [out] : Displaying Param
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack UserCommonGosdDispOsdGetOsdParam(EnumGosdDisplayOSD enumOsd, StructGosdDisplayOsdParam *pstParam)
{
    return (ScalerGosdDispOsdGetOsdParam(enumOsd, pstParam) == _TRUE) ? _GOSD_SYNC_FEEDBACK_SUCCESS : _GOSD_SYNC_FEEDBACK_ERROR;
}

//--------------------------------------------------
// Description  : initial Surface
// Input Value  : ulSurfaceId : Surface
// Output Value : None
//--------------------------------------------------
void UserCommonGosdInitialSurface(DWORD ulSurfaceId)
{
    if(ulSurfaceId < _GOSD_SURFACE_NUMBER)
    {
        GOSD_SET_SURFACE_ADDRESS(ulSurfaceId, _GOSD_SURFACE_UNCREATED_ADDRESS);
        GOSD_SET_SURFACE_STATUS(ulSurfaceId, _GOSD_SURFACE_UNCREATED);
    }
}

//--------------------------------------------------
// Description  : GOSD Load Image Process, executed in the main loop
// Input Value  : ulLoadTimeOut : TimeOut
// Output Value : remain time
//--------------------------------------------------
DWORD UserCommonGosdLoadImageProcess(DWORD ulLoadTimeOut)
{
    StructGosdDecompressInfo stDecompressInfo;
    DWORD ulDecompressedTime = 0;

    // Load Image process when (Circular Queue is not empty) and (image status is COPY_ING)
    while (ScalerGosdCircularQueueGetFront(&stDecompressInfo) == _SUCCESS)
    {
        EnumGosdLoadImageResult enumRes = ScalerGosdDecompress(&stDecompressInfo, &ulDecompressedTime, ulLoadTimeOut);

        switch(enumRes)
        {
            case _GOSD_LOADIMAGE_OK:
            {
                // Copy image done
                // Set SurfaceHeader
                StructGosdSurfaceHeader *pstSurfaceHeader = ScalerGosdGetSurfaceHeader(stDecompressInfo.ulSurfaceId);
                pstSurfaceHeader->ulAddress = GOSD_GET_SURFACE_ADDRESS(stDecompressInfo.ulSurfaceId);
                ScalerGosdSetSurfaceHeader(stDecompressInfo.ulSurfaceId, pstSurfaceHeader);
                GOSD_SET_SURFACE_STATUS(stDecompressInfo.ulSurfaceId, _GOSD_SURFACE_IDLE);
                ScalerGosdCircularQueueAdvanceFront();
                continue;
            }
            case _GOSD_LOADIMAGE_PAUSE:
                // Load image size is more than _GOSD_MAX_COMPRESSED_DATA, pause load operations
                return ulLoadTimeOut;
            case _GOSD_LOADIMAGE_ERROR:
                ScalerGosdCircularQueueAdvanceFront();
                break;
            default:
                break;
        }
    }

    return (ulLoadTimeOut > ulDecompressedTime) ? (ulLoadTimeOut - ulDecompressedTime) : (0);
}

//--------------------------------------------------
// Description  : GOSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonGosdHandler(void)
{
    // load image process
    UserCommonGosdLoadImageProcess(_GOSD_MAINLOOP_DELAY_MAX_MS);

#if(_GOSD_SYNC_BY_INT_NOTIFY == _TRUE)
    UserCommonGosdFunctionHandler();
#endif
}

//--------------------------------------------------
// Description  : GOSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonGosdFunctionHandler(void)
{
    if(GET_GOSD_SYNC_FUNCTIONKEY() != _GOSD_FUNCTION_KEY_IDLE)
    {
        EnumGosdSyncCmdFeedBack enumReturn = _GOSD_SYNC_FEEDBACK_BUSY;

        switch(GET_GOSD_SYNC_FUNCTIONKEY())
        {
            case _GOSD_FUNCTION_KEY_RESET:
            {
                ScalerGosdReset();
                enumReturn = _GOSD_SYNC_FEEDBACK_SUCCESS;
                break;
            }
            case _GOSD_FUNCTION_KEY_MEMORY_RESET:
            {
                ScalerGosdMemoryAllocatorInit();
                enumReturn = _GOSD_SYNC_FEEDBACK_SUCCESS;
                break;
            }
            case _GOSD_FUNCTION_KEY_CREATE_SURFACE:
            {
                StructGosdSyncCmdBodyCreateSurface *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stCreateSurface);
                enumReturn = UserCommonGosdCreateSurface(pstArgument->ulSurfaceId, &(pstArgument->stSurfaceHeader));
                break;
            }
            case _GOSD_FUNCTION_KEY_RELEASE_SURFACE:
            {
                StructGosdSyncCmdBodyReleaseSurface *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stReleaseSurface);
                enumReturn = UserCommonGosdReleaseSurface(pstArgument->ulSurfaceId);
                break;
            }
            case _GOSD_FUNCTION_KEY_RELEASE_MULTI_SURFACE:
            {
                StructGosdSyncCmdBodyReleaseSurface *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stReleaseSurface);
                enumReturn = UserCommonGosdReleaseMultiSurface(pstArgument->ulSurfaceId);
                break;
            }
            case _GOSD_FUNCTION_KEY_GET_SURFACE_STATUS:
            {
                StructGosdSyncCmdBodyGetSurfaceStatus *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stGetSurfaceStatus);
                pstArgument->enumStatus = UserCommonGosdGetSurfaceHeaderStatus(pstArgument->ulSurfaceId);
                enumReturn = _GOSD_SYNC_FEEDBACK_SUCCESS;
                break;
            }
            case _GOSD_FUNCTION_KEY_SET_LOAD_IMAGE_INFO:
            {
                StructGosdSyncCmdBodySetLoadImageInfo *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stSetLoadImageInfo);
                enumReturn = UserCommonGosdSetLoadImageInfo(pstArgument->ulSurfaceId, &(pstArgument->stLoadImageInfo));
                break;
            }
            case _GOSD_FUNCTION_KEY_IMAGE_CONVERT:
            {
                StructGosdSyncCmdBodyImageConvert *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stImageConvert);
                enumReturn = UserCommonGosdImageConvert(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdResult);
                break;
            }
            case _GOSD_FUNCTION_KEY_COPY_PASTE:
            {
                StructGosdSyncCmdBodyCopyPaste *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stCopyPaste);
                enumReturn = UserCommonGosdCopyPaste(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdResult, pstArgument->stSourceRect, pstArgument->stOutPosition);
                break;
            }
            case _GOSD_FUNCTION_KEY_ROTATE:
            {
                StructGosdSyncCmdBodyRotate *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stRotate);
                enumReturn = UserCommonGosdRotate(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdResult, pstArgument->stSourceRect, pstArgument->stOutPosition, pstArgument->enumRotateSel);
                break;
            }
            case _GOSD_FUNCTION_KEY_MIRROR:
            {
                StructGosdSyncCmdBodyMirror *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stMirror);
                enumReturn = UserCommonGosdMirror(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdResult, pstArgument->stSourceRect, pstArgument->stOutPosition, pstArgument->enumMirrorSel);
                break;
            }
            case _GOSD_FUNCTION_KEY_DRAW_RECTANGLE:
            {
                StructGosdSyncCmdBodyDrawRectangle *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDrawRectangle);
                enumReturn = UserCommonGosdDrawRectangle(pstArgument->ulSurfaceIdResult, pstArgument->stRect, pstArgument->ulColor);
                break;
            }
            case _GOSD_FUNCTION_KEY_DRAW_LINEARGRADIENT_RECTANGLE:
            {
                StructGosdSyncCmdBodyDrawLinearGradientRectangle *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDrawLinearGradientRectangle);
                enumReturn = UserCommonGosdDrawLinearGradientRectangle(pstArgument->ulSurfaceIdResult, pstArgument->stRect,
                                                                       pstArgument->enumLinearGradientMode, pstArgument->ulStartColor, pstArgument->ulEndColor);
                break;
            }
            case _GOSD_FUNCTION_KEY_BITBLIT_PASTE:
            {
                StructGosdSyncCmdBodyBitBlitPaste *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stBitBlitPaste);
                enumReturn = UserCommonGosdBitBlitPaste(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdDestination, pstArgument->ulSurfaceIdResult,
                                                        pstArgument->stSourceRect, pstArgument->stDestinationPosition, pstArgument->stOutPosition,
                                                        pstArgument->ulBlitFlags, &(pstArgument->stBlitSettings));
                break;
            }
            case _GOSD_FUNCTION_KEY_STRETCH_PASTE:
            {
                StructGosdSyncCmdBodyStretchPaste *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stStretchPaste);
                enumReturn = UserCommonGosdStretchPaste(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdResult,
                                                        pstArgument->stSourceRect, pstArgument->stOutRect);
                break;
            }
            case _GOSD_FUNCTION_KEY_STRETCHBITBLIT_PASTE:
            {
                StructGosdSyncCmdBodyStretchBitBlitPaste *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stStretchBitBlitPaste);
                enumReturn = UserCommonGosdStretchBitBlitPaste(pstArgument->ulSurfaceIdSource, pstArgument->ulSurfaceIdDestination, pstArgument->ulSurfaceIdResult,
                                                               pstArgument->stSourceRect, pstArgument->stDestinationPosition, pstArgument->stOutRect,
                                                               pstArgument->ulBlitFlags, &(pstArgument->stBlitSettings));
                break;
            }

            case _GOSD_FUNCTION_KEY_DISP_OSD_RESET:
            {
                StructGosdSyncCmdBodyDispOsdReset *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDispOsdReset);
                ScalerGosdDispOsdInitial(pstArgument->enumOSD);
                enumReturn = _GOSD_SYNC_FEEDBACK_SUCCESS;
                break;
            }

            case _GOSD_FUNCTION_KEY_DISP_OSD_DISPLAY_SURFACE:
            {
                StructGosdSyncCmdBodyDispOsdDisplaySurface *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDispOsdDisplaySurface);
                enumReturn = UserCommonGosdDisplaySurface(pstArgument->enumOSD, pstArgument->ulSurfaceId, &(pstArgument->stWinRect), &(pstArgument->stDispRect), pstArgument->enumDBApply);
                break;
            }

            case _GOSD_FUNCTION_KEY_DISP_OSD_GET_OSD_PARAM:
            {
                StructGosdSyncCmdBodyDispOsdGetOsdParam *pstArgument = &(g_stGosdKcpuToScpuSyncCmd.unCmdBody.stDispOsdGetOsdParam);
                enumReturn = UserCommonGosdDispOsdGetOsdParam(pstArgument->enumOSD, &pstArgument->stOsdParam);
                break;
            }

            default:
                enumReturn = _GOSD_SYNC_FEEDBACK_SUCCESS;
                break;
        }

        SET_GOSD_SYNC_FUNCTIONKEY(_GOSD_FUNCTION_KEY_IDLE);
        SET_GOSD_SYNC_FEEDBACK(enumReturn);
    }
}

#endif // #if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
#endif // end of #if(_GOSD_SUPPORT == _ON)
