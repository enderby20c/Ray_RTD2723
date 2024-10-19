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
// ID Code      : UserCommonColorInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define CLR_ALL_COLOR_FUNCTION_REGION_ENABLE()        (memset(&g_pstColorFunctionRegionEnable, 0xFFU, sizeof(g_pstColorFunctionRegionEnable)))

#define GET_LSR_REGION_ENABLE(region)                 (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1LSRRegionEnable)
#define SET_LSR_REGION_ENABLE(region, x)              (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1LSRRegionEnable = (x))

#define GET_DSHP_REGION_ENABLE(region)                (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1DSHPRegionEnable)
#define SET_DSHP_REGION_ENABLE(region, x)             (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1DSHPRegionEnable = (x))

#define GET_LOCALCONTRAST_REGION_ENABLE(region)       (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1LocalCTSRegionEnable)
#define SET_LOCALCONTRAST_REGION_ENABLE(region, x)    (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1LocalCTSRegionEnable = (x))

#define GET_DCC_REGION_ENABLE(region)                 (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1DCCRegionEnable)
#define SET_DCC_REGION_ENABLE(region, x)              (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1DCCRegionEnable = (x))

#define GET_ICM_REGION_ENABLE(region)                 (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1ICMRegionEnable)
#define SET_ICM_REGION_ENABLE(region, x)              (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1ICMRegionEnable = (x))

#define GET_IAPS_REGION_ENABLE(region)                (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1IAPSRegionEnable)
#define SET_IAPS_REGION_ENABLE(region, x)             (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1IAPSRegionEnable = (x))

#define GET_CTS_BRI_REGION_ENABLE(region)             (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1CTSBRIRegionEnable)
#define SET_CTS_BRI_REGION_ENABLE(region, x)          (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1CTSBRIRegionEnable = (x))

#define GET_3DGAMMA_REGION_ENABLE(region)             (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b13DGAMMARegionEnable)
#define SET_3DGAMMA_REGION_ENABLE(region, x)          (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b13DGAMMARegionEnable = (x))

#define GET_PCM_REGION_ENABLE(region)                 (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1PCMRegionEnable)
#define SET_PCM_REGION_ENABLE(region, x)              (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1PCMRegionEnable = (x))

#define GET_SRGB_REGION_ENABLE(region)                (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1SRGBRegionEnable)
#define SET_SRGB_REGION_ENABLE(region, x)             (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1SRGBRegionEnable = (x))

#define GET_UNIFORMITY_REGION_ENABLE(region)          (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1UniformityRegionEnable)
#define SET_UNIFORMITY_REGION_ENABLE(region, x)       (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1UniformityRegionEnable = (x))

#define GET_GAMMA_REGION_ENABLE(region)               (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1GammaRegionEnable)
#define SET_GAMMA_REGION_ENABLE(region, x)            (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1GammaRegionEnable = (x))

#define GET_NIGHT_SNIPER_REGION_ENABLE(region)        (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1NightSniperRegionEnable)
#define SET_NIGHT_SNIPER_REGION_ENABLE(region, x)     (g_pstColorFunctionRegionEnable[UserCommonColorGetSelectRegionHLWArea(region)].b1NightSniperRegionEnable = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1LSRRegionEnable : 1;
    BYTE b1DSHPRegionEnable : 1;
    BYTE b1LocalCTSRegionEnable : 1;
    BYTE b1DCCRegionEnable : 1;
    BYTE b1ICMRegionEnable : 1;
    BYTE b1IAPSRegionEnable : 1;
    BYTE b1CTSBRIRegionEnable : 1;
    BYTE b13DGAMMARegionEnable : 1;
    BYTE b1PCMRegionEnable : 1;
    BYTE b1SRGBRegionEnable : 1;
    BYTE b1UniformityRegionEnable : 1;
    BYTE b1GammaRegionEnable : 1;
    BYTE b1NightSniperRegionEnable : 1;
} StructColorFunctionRegionEnable;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructColorFunctionRegionEnable g_pstColorFunctionRegionEnable[3];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern void UserCommonColorLocalDimmingDCRHandler(EnumDisplayRegion enumDisplayRegion);
#endif
extern void UserCommonColorResetColor(EnumDisplayRegion enumDisplayRegion);
