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
// ID Code      : UserCommonDisplaySetting.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_DISPLAY_SETTING_H__
#define __USER_COMMON_DISPLAY_SETTING_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                                (UserCommonDisplayGetHPositionHBiasValue(enumDisplayRegion))
#define _GET_HPOSITIONRANGE_MAX                        (0)
#define _GET_HPOSITIONRANGE_MIN                        (1)

//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                                (UserCommonDisplayGetVPositionVBiasValue(enumDisplayRegion))
#define _GET_VPOSITIONRANGE_MAX                        (0)
#define _GET_VPOSITIONRANGE_MIN                        (1)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_ASPECT_RATIO_SUPPORT == _ON)
typedef struct
{
    WORD usHstart;
    WORD usVstart;
    WORD usHwidth;
    WORD usVheight;
} StructTimingDataInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern WORD UserCommonDisplayGetHPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonDisplayGetHPositionHBiasValue(EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonDisplayGetVPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonDisplayGetVPositionVBiasValue(EnumDisplayRegion enumDisplayRegion);

#if(_OVERSCAN_SUPPORT == _ON)
extern void UserCommonDisplayAdjustOverScan(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern void UserCommonDisplayAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion);
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
extern void UserCommonDisplayAdjustRotationInputSize(void);
extern void UserCommonDisplayAdjustRotationDisplaySize(void);
#endif


#endif // End of #ifndef __USER_COMMON_DISPLAY_SETTING_H__
