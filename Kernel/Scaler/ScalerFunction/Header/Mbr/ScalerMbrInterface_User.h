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
// ID Code      : ScalerMbrInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#define GET_MBR_DVTOTAL()                       (g_usMbrDVTotal)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _RTK_ADV_MBR_USER_DISABLE = _OFF,
    _RTK_ADV_MBR_USER_ENABLE,
} EnumRtkAdvMbrUserStatus;

typedef enum
{
    _BACKLIGHT_MODE_CONSTANT,
    _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR,
    _BACKLIGHT_MODE_STROBE_DRR_MBR,
    _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR,
} EnumMbrBacklightMode;

typedef enum
{
    _BFI_MODE_OFF = _OFF,
    _BFI_MODE_ON,
} EnumMbrBFIMode;

typedef enum
{
    _BACKLIGHT_SEQ_PDIM_ADIM,
    _BACKLIGHT_SEQ_ADIM_PDIM,
} EnumMbrBacklightSeq;

typedef enum
{
    _BACKLIGHT_PDIM_CTRL_BY_TCON,
    _BACKLIGHT_PDIM_CTRL_BY_USER,
} EnumMbrPDimCtrl;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
extern WORD g_usMbrDVTotal;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

