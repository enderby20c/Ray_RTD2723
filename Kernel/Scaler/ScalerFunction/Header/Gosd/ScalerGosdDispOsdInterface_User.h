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
// ID Code      : ScalerGosdDispOsdInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//***************************************************************
// Function
//***************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of GDMA setting status
//--------------------------------------------------
typedef enum
{
    _GDMA_SUCCESS,
    _GDMA_FAIL,
} EnumGosdGdmaStatus;

//--------------------------------------------------
// Enumerations of DB trigger event
//--------------------------------------------------
typedef enum
{
    _DB_TRIGGER_EVENT_DVS,
    _DB_TRIGGER_EVENT_DEN_STOP,
} EnumGosdGdmaDBTriggerEvent;

//--------------------------------------------------
// Enumerations of Mixer Layer Select
//--------------------------------------------------
typedef enum
{
    _GOSD_C0 = 0,
    _GOSD_C1,
    _GOSD_C2,
    _GOSD_C3,
} EnumGosdMixerOrder;

//--------------------------------------------------
// Enumerations of Mixer Bland Layer
//--------------------------------------------------
typedef enum
{
    _GOSD_B0,
    _GOSD_B1,
    _GOSD_B2,
} EnumGosdMixerLayer;

//--------------------------------------------------
// Enumerations of Output OSD
//--------------------------------------------------
typedef enum
{
    _GOSD_PLANE_OSD1 = 0,
    _GOSD_PLANE_OSD2,
    _GOSD_PLANE_OSD3,
    _GOSD_PLANE_MAXNUM,
    _GOSD_PLANE_ALL,
    _GOSD_PLANE_NONE,
} EnumGosdDisplayOSD;

typedef enum
{
    _GOSD_RGB = 0,
    _GOSD_BGR,
    _GOSD_GRB,
    _GOSD_GBR,
    _GOSD_RBG,
    _GOSD_BRG
} EnumGosdRGBOrder;

typedef struct
{
    BYTE b6K1               : 6;
    BYTE b6K2               : 6;
    BYTE b6K3               : 6;
    BYTE b6K4               : 6;
} StructGosdMixerFactor;

typedef struct
{
    EnumGosdMixerLayer enumLayerSel;
    StructGosdMixerFactor stFactor;
} StructGosdMixerLayerSetting;

typedef struct
{
    WORD b9PlaneAlphaA      : 9;
    WORD b9PlaneAlphaR      : 9;
    WORD b9PlaneAlphaB      : 9;
    WORD b9PlaneAlphaG      : 9;
} StructGosdMixerPlaneAlpha_ARGB;

typedef struct
{
    BYTE ucPlaneOffsetA;
    BYTE ucPlaneOffsetR;
    BYTE ucPlaneOffsetB;
    BYTE ucPlaneOffsetG;
} StructGosdMixerPlaneOffset_ARGB;

typedef struct
{
    WORD b13X_end           : 13;
    WORD b13X_sta           : 13;
} StructGosdGdmaClearX;

typedef struct
{
    WORD b13Y_end           : 13;
    WORD b13Y_sta           : 13;
} StructGosdGdmaClearY;

typedef struct
{
    WORD usX;
    WORD usY;
} StructGosdGdmaWinXY;

typedef struct
{
    WORD usWidth;
    WORD usHeight;
} StructGosdGdmaWinWH;

typedef struct
{
    StructGosdGdmaWinXY stWinXY;
    StructGosdGdmaWinWH stWinWH;
} StructGosdGdmaRectangle;

typedef struct
{
    DWORD ulSurfaceId;
    StructGosdRectangle stWinRect;
    StructGosdRectangle stDispRect;
} StructGosdDisplayOsdParam;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************



#endif // #if(_GOSD_SUPPORT == _ON)
