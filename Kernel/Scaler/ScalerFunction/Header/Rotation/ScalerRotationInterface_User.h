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

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerRotationInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_ROT_TYPE()                                  (g_stRotationStatus.enumRotationType)
#define SET_ROT_TYPE(x)                                 (g_stRotationStatus.enumRotationType = (x))

#define GET_ROT_DISP_SIZE()                             (g_stRotationStatus.enumRotationDispSize)
#define SET_ROT_DISP_SIZE(x)                            (g_stRotationStatus.enumRotationDispSize = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Rotation Type Status
//--------------------------------------------------
typedef enum
{
    _ROT_DISABLE = 0x00,
    _ROT_CW90,
    _ROT_CW180,
    _ROT_CW270,
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _ROT_HOR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _ROT_VER_MIRROR,
#endif
} EnumRotationType;

//--------------------------------------------------
// Enumerations of Rotation Display Type Status
//--------------------------------------------------
typedef enum
{
    _ROT_FULL = 0x00,
    _ROT_PIXEL_BY_PIXEL,
    _ROT_KEEP_SRC_ASPECT_RATIO,
} EnumRotationDisplayType;

//--------------------------------------------------
// Structure of Rotation Status
//--------------------------------------------------
typedef struct
{
    EnumRotationType enumRotationType;
    EnumRotationDisplayType enumRotationDispSize;
} StructRotationStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructRotationStatus g_stRotationStatus;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif

