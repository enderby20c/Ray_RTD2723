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
// ID Code      : ScalerGosdInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// Function
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    // finished
    _GOSD_SYNC_FEEDBACK_SUCCESS = 0,
    // FW not finished
    _GOSD_SYNC_FEEDBACK_BUSY,
    // HW not finished
    _GOSD_SYNC_FEEDBACK_BUSY_LOAD,
    _GOSD_SYNC_FEEDBACK_BUSY_DRAW,
    // error
    _GOSD_SYNC_FEEDBACK_ERROR
} EnumGosdSyncCmdFeedBack;

typedef enum
{
    _GOSD_PIXEL_FORMAT_ARGB8888 = 0,
    _GOSD_PIXEL_FORMAT_RGB888,
    _GOSD_PIXEL_FORMAT_ARGB4444,
    _GOSD_PIXEL_FORMAT_ARGB1555,
    _GOSD_PIXEL_FORMAT_RGB565,
    _GOSD_PIXEL_FORMAT_INDEX8,
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
    _GOSD_PIXEL_FORMAT_AFBC4U8,
    _GOSD_PIXEL_FORMAT_AFBC3U8
#endif
} EnumGosdPixelFormat;

typedef enum
{
    _GOSD_ARGB = 0,
    _GOSD_ARBG = 1,
    _GOSD_AGRB = 2,
    _GOSD_AGBR = 3,
    _GOSD_ABRG = 4,
    _GOSD_ABGR = 5,
    _GOSD_RAGB = 8,
    _GOSD_RABG = 9,
    _GOSD_RGAB = 10,
    _GOSD_RGBA = 11,
    _GOSD_RBAG = 12,
    _GOSD_RBGA = 13,
    _GOSD_GARB = 16,
    _GOSD_GABR = 17,
    _GOSD_GRAB = 18,
    _GOSD_GRBA = 19,
    _GOSD_GBAR = 20,
    _GOSD_GBRA = 21,
    _GOSD_BARG = 24,
    _GOSD_BAGR = 25,
    _GOSD_BRAG = 26,
    _GOSD_BRGA = 27,
    _GOSD_BGAR = 28,
    _GOSD_BGRA = 29,
} EnumGosdARGBOrder;

typedef enum
{
    _GOSD_1BYTE = 1,
    _GOSD_2BYTE = 2,
    _GOSD_4BYTE = 4,
    _GOSD_8BYTE = 8
} EnumGosdByteSwap;

typedef enum
{
    _GOSD_SURFACE_UNCREATED,
    _GOSD_SURFACE_UNDEFINED,
    _GOSD_SURFACE_LOADING,
    _GOSD_SURFACE_SE_WORKING_READ,
    _GOSD_SURFACE_SE_WORKING_WRITE,
    _GOSD_SURFACE_DISPOSD_SHOWING,
    _GOSD_SURFACE_IDLE,
} EnumGosdSurfaceStatus;

typedef enum
{
    _GOSD_CONTINUOUS_INFINITE_LOOP,
    _GOSD_CONTINUOUS_ONCE,
    _GOSD_CONTINUOUS_NONE,
} EnumGosdContinuousType;

typedef struct
{
    WORD usX;
    WORD usY;
} StructGosdPosition;

typedef struct
{
    WORD usW;
    WORD usH;
} StructGosdSize;

typedef struct
{
    StructGosdPosition stPosition;
    StructGosdSize stSize;
} StructGosdRectangle;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif // #if(_GOSD_SUPPORT == _ON)
