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
// ID Code      : ScalerRegionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DISPLAY_MODE()                              (g_enumRegionDisplayMode)
#define SET_DISPLAY_MODE(x)                             (g_enumRegionDisplayMode = (x))
#define GET_RGN_DISPLAY_REGION(x)                       ((EnumDisplayRegion)(GET_DISPLAY_MODE() + ((x) & 0x03)))

#define GET_MODE_DISPLAY_TARGET_REGION()                (GET_DISPLAY_MODE() + GET_MODE_DISPLAY_TARGET_INDEX())
#define GET_MODE_DISPLAY_TARGET_INDEX()                 (g_stRegionIndexInfo.b2DisplaySettingTargetIndex)
#define SET_MODE_DISPLAY_TARGET_INDEX(index)            (g_stRegionIndexInfo.b2DisplaySettingTargetIndex = (index))

#define SET_RGN_MAX_DISPLAY_REGION(x)                   (g_stRegionIndexInfo.b2RegionCount = (x) - 0x01)
#define GET_RGN_MAX_DISPLAY_REGION()                    (((BYTE)g_stRegionIndexInfo.b2RegionCount % _MULTI_DISPLAY_MAX) + 0x01)

#define GET_PBP_LR_RATIO_TYPE()                         (g_stRegionPbplrRatio.enumPbplrType)
#define SET_PBP_LR_RATIO_TYPE(x)                        (g_stRegionPbplrRatio.enumPbplrType = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b2RegionCount : 2;
    BYTE b2DisplaySettingTargetIndex : 2;
} StructRegionIndexInfo;

typedef enum
{
    _PBP_LR_L_EQUAL_R = 0x00,
    _PBP_LR_L_LARGER_THAN_R,
    _PBP_LR_R_LARGER_THAN_L,
} EnumPbplrType;

typedef struct
{
    EnumPbplrType enumPbplrType;
} StructPbplrRatio;
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumDisplayMode g_enumRegionDisplayMode;
extern StructRegionIndexInfo g_stRegionIndexInfo;
extern StructPbplrRatio g_stRegionPbplrRatio;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerRegionSetWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable);
extern BYTE ScalerRegionGetMaxRegionCount(void);
extern EnumDDomainRegion ScalerRegionGetDDomainRegion(EnumDisplayRegion enumDisplayRegion);
extern EnumHLWType ScalerRegionGetSelectRegionHLWArea(EnumSelRegion enumSelRegion);

extern EnumRegionIndex ScalerRegionGetIndex(EnumDisplayRegion enumDisplayRegion);
extern EnumDDomainDBApplyRegion ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion(EnumSelRegion enumSelRegion);
extern EnumInputDataPath ScalerRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion);
extern EnumSelRegion ScalerRegionGetInverse(EnumSelRegion enumSelRegion);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern EnumDisplayMode ScalerRegionEagleSightTransDisplayMode(EnumDisplayMode enumDisplayMode);
#endif

#if(_FRC_SUPPORT == _ON)
extern EnumRegionIndex ScalerRegionGet2PMainPathRegion(void);
#endif

