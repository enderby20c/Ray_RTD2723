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
// ID Code      : UserCommonGosd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_GOSD_H__
#define __USER_COMMON_GOSD_H__

#if(_GOSD_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GOSDSE_MAX_POLLING_MS                  100
#define _GOSD_MAX_COPY_INFO_NUMBER_IN_SYNCCMD   100

#define GET_GOSD_SYNC_FUNCTIONKEY()             (g_stGosdKcpuToScpuSyncCmd.stCmdHeader.enumFunctionKey)
#define SET_GOSD_SYNC_FUNCTIONKEY(x)            (g_stGosdKcpuToScpuSyncCmd.stCmdHeader.enumFunctionKey = (x))

#define GET_GOSD_SYNC_FEEDBACK()                (g_stGosdKcpuToScpuSyncCmd.stFeedBack.enumFeedBack)
#define SET_GOSD_SYNC_FEEDBACK(x)               (g_stGosdKcpuToScpuSyncCmd.stFeedBack.enumFeedBack = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _GOSD_SET_COPY_IMAGE_INFO_SUCCESS = 0,
    _GOSD_SET_COPY_IMAGE_INFO_ERROR
} EnumGosdSetCopyImageInfoResult;

typedef enum
{
    _GOSD_FUNCTION_KEY_IDLE = 0,
    _GOSD_FUNCTION_KEY_RESET,
    _GOSD_FUNCTION_KEY_MEMORY_RESET,
    _GOSD_FUNCTION_KEY_CREATE_SURFACE,
    _GOSD_FUNCTION_KEY_RELEASE_SURFACE,
    _GOSD_FUNCTION_KEY_RELEASE_MULTI_SURFACE,
    _GOSD_FUNCTION_KEY_GET_SURFACE_STATUS,
    _GOSD_FUNCTION_KEY_SET_LOAD_IMAGE_INFO,

    _GOSD_FUNCTION_KEY_IMAGE_CONVERT,
    _GOSD_FUNCTION_KEY_COPY_PASTE,
    _GOSD_FUNCTION_KEY_ROTATE,
    _GOSD_FUNCTION_KEY_MIRROR,
    _GOSD_FUNCTION_KEY_DRAW_RECTANGLE,
    _GOSD_FUNCTION_KEY_DRAW_LINEARGRADIENT_RECTANGLE,
    _GOSD_FUNCTION_KEY_BITBLIT_PASTE,
    _GOSD_FUNCTION_KEY_STRETCH_PASTE,
    _GOSD_FUNCTION_KEY_STRETCHBITBLIT_PASTE,

    _GOSD_FUNCTION_KEY_DISP_OSD_RESET,
    _GOSD_FUNCTION_KEY_DISP_OSD_DISPLAY_SURFACE,
    _GOSD_FUNCTION_KEY_DISP_OSD_GET_OSD_PARAM,
} EnumGosdUserCommonFunctionKey;

typedef struct
{
    EnumGosdUserCommonFunctionKey enumFunctionKey;
} StructGosdKcpuToScpuSyncCmdHeader;

typedef struct
{
    DWORD ulMemoryGosdStartAddress;
    DWORD ulMemoryGosdEndAddress;
} StructGosdSyncCmdBodyMemoryReset;

typedef struct
{
    DWORD ulSurfaceId;
    StructGosdSurfaceHeader stSurfaceHeader;
} StructGosdSyncCmdBodyCreateSurface;

typedef struct
{
    DWORD ulSurfaceId;
} StructGosdSyncCmdBodyReleaseSurface;

typedef struct
{
    EnumGosdSurfaceStatus enumStatus;
    DWORD ulSurfaceId;
} StructGosdSyncCmdBodyGetSurfaceStatus;

typedef struct
{
    DWORD ulSurfaceId;
    StructGosdLoadImageInfo stLoadImageInfo;
} StructGosdSyncCmdBodySetLoadImageInfo;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdResult;
} StructGosdSyncCmdBodyImageConvert;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stSourceRect;
    StructGosdPosition stOutPosition;
} StructGosdSyncCmdBodyCopyPaste;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stSourceRect;
    StructGosdPosition stOutPosition;
    EnumOsdRotateType enumRotateSel;
} StructGosdSyncCmdBodyRotate;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stSourceRect;
    StructGosdPosition stOutPosition;
    EnumGosdSeMirrorMode enumMirrorSel;
} StructGosdSyncCmdBodyMirror;

typedef struct
{
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stRect;
    DWORD ulColor;
} StructGosdSyncCmdBodyDrawRectangle;

typedef struct
{
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stRect;
    EnumGosdSeLinearGradientMode enumLinearGradientMode;
    DWORD ulStartColor;
    DWORD ulEndColor;
} StructGosdSyncCmdBodyDrawLinearGradientRectangle;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdDestination;
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stSourceRect;
    StructGosdPosition stDestinationPosition;
    StructGosdPosition stOutPosition;
    DWORD ulBlitFlags;
    StructGosdSeBitBlitSettings stBlitSettings;
} StructGosdSyncCmdBodyBitBlitPaste;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stSourceRect;
    StructGosdRectangle stOutRect;
} StructGosdSyncCmdBodyStretchPaste;

typedef struct
{
    DWORD ulSurfaceIdSource;
    DWORD ulSurfaceIdDestination;
    DWORD ulSurfaceIdResult;
    StructGosdRectangle stSourceRect;
    StructGosdPosition stDestinationPosition;
    StructGosdRectangle stOutRect;
    DWORD ulBlitFlags;
    StructGosdSeBitBlitSettings stBlitSettings;
} StructGosdSyncCmdBodyStretchBitBlitPaste;

//---------------------------------
// Disp Osd Sync command
//---------------------------------
typedef struct
{
    EnumGosdDisplayOSD enumOSD;
} StructGosdSyncCmdBodyDispOsdReset;

typedef struct
{
    EnumGosdDisplayOSD enumOSD;
    DWORD ulSurfaceId;
    StructGosdRectangle stWinRect;
    StructGosdRectangle stDispRect;
    EnumDBApply enumDBApply;
} StructGosdSyncCmdBodyDispOsdDisplaySurface;

typedef struct
{
    EnumGosdDisplayOSD enumOSD;
    StructGosdDisplayOsdParam stOsdParam;
} StructGosdSyncCmdBodyDispOsdGetOsdParam;

typedef struct
{
    BYTE ucStepIndex;
    StructGosdPosition stDispPosition;
} StructGosdSyncCmdBodyContinuousDisplayChangeDispPosition;
typedef union
{
    // GOSD Sync command
    StructGosdSyncCmdBodyMemoryReset stMemoryReset;
    StructGosdSyncCmdBodyCreateSurface stCreateSurface;
    StructGosdSyncCmdBodyReleaseSurface stReleaseSurface;
    StructGosdSyncCmdBodyGetSurfaceStatus stGetSurfaceStatus;
    StructGosdSyncCmdBodySetLoadImageInfo stSetLoadImageInfo;

    // SE Sync command
    StructGosdSyncCmdBodyImageConvert stImageConvert;
    StructGosdSyncCmdBodyCopyPaste stCopyPaste;
    StructGosdSyncCmdBodyRotate stRotate;
    StructGosdSyncCmdBodyMirror stMirror;
    StructGosdSyncCmdBodyDrawRectangle stDrawRectangle;
    StructGosdSyncCmdBodyDrawLinearGradientRectangle stDrawLinearGradientRectangle;
    StructGosdSyncCmdBodyBitBlitPaste stBitBlitPaste;
    StructGosdSyncCmdBodyStretchPaste stStretchPaste;
    StructGosdSyncCmdBodyStretchBitBlitPaste stStretchBitBlitPaste;

    // Disp Osd Sync command
    StructGosdSyncCmdBodyDispOsdReset stDispOsdReset;
    StructGosdSyncCmdBodyDispOsdDisplaySurface stDispOsdDisplaySurface;
    StructGosdSyncCmdBodyContinuousDisplayChangeDispPosition stContinuousDisplayChangeDispPosition;
    StructGosdSyncCmdBodyDispOsdGetOsdParam stDispOsdGetOsdParam;
} UnionGosdKcpuToScpuSyncCmdBody;

typedef struct
{
    EnumGosdSyncCmdFeedBack enumFeedBack;
} StructGosdKcpuToScpuSyncCmdFeedBack;

typedef struct
{
    StructGosdKcpuToScpuSyncCmdHeader stCmdHeader;
    UnionGosdKcpuToScpuSyncCmdBody unCmdBody;
    StructGosdKcpuToScpuSyncCmdFeedBack stFeedBack;
} StructGosdKcpuToScpuSyncCmd;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructGosdKcpuToScpuSyncCmd g_stGosdKcpuToScpuSyncCmd;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern void UserCommonGosdInitialSurface(DWORD ulSurfaceId);
extern bit UserCommonGosdSetSurfaceHeader(DWORD ulSurfaceId, StructGosdSurfaceHeader *pstSurfaceHeader);
extern bit UserCommonGosdGetSurfaceHeader(StructGosdSurfaceHeader *pstHeader, DWORD ulSurfaceId);
extern bit UserCommonGosdSetSurfaceHeaderStatus(DWORD ulSurfaceId, EnumGosdSurfaceStatus enumStatus);
extern EnumGosdSurfaceStatus UserCommonGosdGetSurfaceHeaderStatus(DWORD ulSurfaceId);
#endif
#endif

#endif // End of #ifndef __USER_COMMON_GOSD_H__
