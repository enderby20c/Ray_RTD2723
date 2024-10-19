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
// ID Code      : ScalerDDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DDOMAIN_OUTPUT_REGION(x)                (g_pstDDomainRegionInfo[x].enumOutputRegion)
#define GET_DDOMAIN_SU_PAGE_ADDR(x)                 (g_pstDDomainRegionInfo[x].usScalingUpPageAddr)
#define GET_DDOMAIN_SF_PAGE_ADDR(x)                 (g_pstDDomainRegionInfo[x].usScalingFactorPageAddr)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumDDomainRegion enumOutputRegion;
    WORD usScalingUpPageAddr;
    WORD usScalingFactorPageAddr;
} StructDDomainRegionInfo;

typedef enum
{
    _PBP_LR_LARGE_FRAME_R1A1 = 0x00,
    _PBP_LR_LARGE_FRAME_R2A1 = 0x01,
    _PBP_LR_LARGE_FRAME_NONE = 0xFF,
} EnumPBPLRLargeFrameMappingDDomainRegion;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerDDomainGetDataPath(void);
extern bit ScalerDDomainBackgroundCheck(EnumSelRegion enumSelRegion);
extern StructDDomainRegionInfo g_pstDDomainRegionInfo[_HW_D_DOMAIN_PATH_COUNT];
extern WORD ScalerDDomainGetScalingUpPageAddr(EnumDDomainRegion enumDDomainRegion);
extern WORD ScalerDDomainGetScalingFactorPageAddr(EnumDDomainRegion enumDDomainRegion);
extern void ScalerDDomainResetDDomainRgn(EnumDDomainRegion enumDDomainRegion);
extern void ScalerDDomainSetFsyncLastlineMultiple(void);
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
extern EnumPBPLRLargeFrameMappingDDomainRegion ScalerDDomainPbpLRLargeFrameMappingRegion(void);
extern void ScalerDDomainSetPbplrSubDisable(void);
#endif
#if(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_2)
extern void ScalerDDomainBackgroundSetColorInsert(bit bEn, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, BYTE ucCycleCnt, BYTE ucBlackmask, EnumDBApply enumDBApply);
#endif
