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
// ID Code      : UserCommonColorLocalDimmingInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_LOCAL_DIMMING_FUNCTION == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_LOCAL_DIMMING_PWM_TOTAL_RATIO()                   (g_stColorLocalDimmingExternInfo.ucColorPWMTotalRatio)
#define GET_LOCAL_DIMMING_BLACK_RATIO()                       (g_stColorLocalDimmingExternInfo.ucColorBlackRatio)
#define GET_LOCAL_DIMMING_FULL_PATTERN()                      (g_stColorLocalDimmingExternInfo.bColorFullPattern)
#define GET_LOCAL_DIMMING_CASE(x)                             (g_stColorLocalDimmingExternInfo.enumLocalDimmingCase)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    bit bColorFullPattern;
    BYTE ucColorBlackRatio;
    BYTE ucColorPWMTotalRatio;
    EnumLocalDimmingCase enumLocalDimmingCase;
}StructLocalDimmingExternInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructLocalDimmingExternInfo g_stColorLocalDimmingExternInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumLocalDimmingStatus UserCommonColorLocalDimmingGetEnableStatus(void);
extern void UserCommonColorLocalDimmingAdjust(void);
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
extern WORD *UserCommonColorLocalDimmingGetEdgeTypePWMValue(void);
#endif
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
extern bit UserCommonColorLocalDimmingBoostForceKernalValue(void);
extern BYTE UserCommonColorLocalDimmingBoostGetLastKernelBoostValue(void);
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingSetRegionBoostAdimValue(BYTE ucStartAddr, BYTE *pucDataBuffer, bit bApplyUpdSync);
#endif

#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingChangeInitialTable(void);
#endif
#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

