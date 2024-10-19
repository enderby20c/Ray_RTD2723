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
// ID Code      : ScalerDDomainInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DISPLAY_FORMAT_H_TOTAL,
    _DISPLAY_FORMAT_HS_WIDTH,
    _DISPLAY_FORMAT_H_START,
    _DISPLAY_FORMAT_H_END,
    _DISPLAY_FORMAT_H_WIDTH,

    _DISPLAY_FORMAT_V_TOTAL,
    _DISPLAY_FORMAT_VS_WIDTH,
    _DISPLAY_FORMAT_V_START,
    _DISPLAY_FORMAT_V_END,
    _DISPLAY_FORMAT_V_HEIGHT,
} EnumDisplayFormatItem;

typedef enum
{
    _DISPLAY_BACKGROUND_H_START,
    _DISPLAY_BACKGROUND_H_END,
    _DISPLAY_BACKGROUND_H_WIDTH,

    _DISPLAY_BACKGROUND_V_START,
    _DISPLAY_BACKGROUND_V_END,
    _DISPLAY_BACKGROUND_V_HEIGHT,
} EnumDisplayBackgroundItem;

typedef enum
{
    _D_PATTERN_GEN_PROGRAMMABLE_MODE,
    _D_PATTERN_GEN_BOX_MODE,
} EnumDPatternGenMode;

//--------------------------------------------------
// Structure of D-domain Pattern Gen Box Mode
//--------------------------------------------------
typedef struct
{
    BYTE b1Region0 : 1;
    BYTE b1Region1 : 1;
    BYTE b1Region2 : 1;
    BYTE b1Region3 : 1;
    BYTE b1Region4 : 1;
    BYTE b1Region5 : 1;
    BYTE b1Region6 : 1;
    BYTE b1Region7 : 1;
    BYTE b1Region8 : 1;
} StructDPatternGenBoxSetting;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern BYTE g_ucDDomainPanelIndex;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

