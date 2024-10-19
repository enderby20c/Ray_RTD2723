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
// ID Code      : RTD2020UserAdjustLocalContrast.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_LOCAL_CONTRAST__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_LOCAL_CONTRAST_FUNCTION == _ON) || (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON) || (_IP_LOCAL_CONTRAST_ON == _ON) || (_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Get LocalContrast Temporal Table Address
// Input Value  : LocalContrast Table Index
// Output Value : LocalContrast table address
//--------------------------------------------------
BYTE *UserAdjustGetLocalContrastTemporalTableAddress(EnumLocalContrastTemporalType enumLocalContrastTemporalType)
{
    return tCOLOR_LOCALCONTRAST_TEMPORAL_TABLE[enumLocalContrastTemporalType];
}

//--------------------------------------------------
// Description  : Get LocalContrast Table Bank
// Input Value  : None
// Output Value : LocalContrast table bank
//--------------------------------------------------
BYTE UserAdjustGetLocalContrastTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}
#endif // End of #if((_LOCAL_CONTRAST_FUNCTION == _ON) || (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON) || (_IP_LOCAL_CONTRAST_ON == _ON))

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set LocalContrast parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustLocalContrast(EnumSelRegion enumSelRegion)
{
    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, _COLOR_FUNCTION_LOCAL_CONTRAST | _COLOR_FUNCTION_ICM);

    UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);

#if(_ICM_FUNCTION == _ON)
    UserCommonColorICMAdjust(enumSelRegion);
#endif

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, _COLOR_FUNCTION_LOCAL_CONTRAST | _COLOR_FUNCTION_ICM);
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get LocalContrast HDR10 Table Address
// Input Value  : LocalContrast Index
// Output Value : LocalContrast table address
//--------------------------------------------------
BYTE *UserAdjustGetLocalContrastHDR10TableAddress(EnumSelRegion enumSelRegion, BYTE ucLCStatus, EnumHDR10StaticMasteringLvType enumHDR10StaticMasteringLvType)
{
    if(UserCommonColorHDRGetHDR10Status(UserCommonColorHDRGetDisplayRegion(enumSelRegion)) == _HDR10_ON)
    {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
        {
            switch(enumHDR10StaticMasteringLvType)
            {
                case _HDR10_STATIC_MASTERING_LV_TYPE_540:
                    return tCOLOR_LOCALCONTRAST_HDR10_LD_540_TABLE[ucLCStatus];

                case _HDR10_STATIC_MASTERING_LV_TYPE_1200:
                    return tCOLOR_LOCALCONTRAST_HDR10_LD_1200_TABLE[ucLCStatus];

                case _HDR10_STATIC_MASTERING_LV_TYPE_4000:
                    return tCOLOR_LOCALCONTRAST_HDR10_LD_4000_TABLE[ucLCStatus];

                case _HDR10_STATIC_MASTERING_LV_TYPE_10000:
                    return tCOLOR_LOCALCONTRAST_HDR10_LD_10000_TABLE[ucLCStatus];

                default:
                    return tCOLOR_LOCALCONTRAST_HDR10_LD_540_TABLE[ucLCStatus];
            }
        }
        else
#endif
        {
            switch(enumHDR10StaticMasteringLvType)
            {
                case _HDR10_STATIC_MASTERING_LV_TYPE_540:
                    return tCOLOR_LOCALCONTRAST_HDR10_540_TABLE[ucLCStatus];

                case _HDR10_STATIC_MASTERING_LV_TYPE_1200:
                    return tCOLOR_LOCALCONTRAST_HDR10_1200_TABLE[ucLCStatus];

                case _HDR10_STATIC_MASTERING_LV_TYPE_4000:
                    return tCOLOR_LOCALCONTRAST_HDR10_4000_TABLE[ucLCStatus];

                case _HDR10_STATIC_MASTERING_LV_TYPE_10000:
                    return tCOLOR_LOCALCONTRAST_HDR10_10000_TABLE[ucLCStatus];

                default:
                    return tCOLOR_LOCALCONTRAST_HDR10_540_TABLE[ucLCStatus];
            }
        }
    }
    return tCOLOR_LOCALCONTRAST_HDR10_1200_TABLE[ucLCStatus];
}
#endif // End of #if(_HDR10_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get LocalContrast SDR Table Address
// Input Value  : LocalContrast Index
// Output Value : LocalContrast table address
//--------------------------------------------------
BYTE *UserAdjustGetLocalContrastTableAddress(BYTE ucLCStatus)
{
    return tCOLOR_LOCALCONTRAST_SETTING_TABLE[ucLCStatus];
}

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get LocalContrast SDR+ Table Address
// Input Value  : None
// Output Value : LocalContrast SDR+ table address
//--------------------------------------------------
BYTE *UserAdjustGetLocalContrastNightSniperAddress(void)
{
    return tCOLOR_LOCALCONTRAST_NIGHT_SNIPER_TABLE;
}
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get LocalContrast SDR+ Table Address
// Input Value  : None
// Output Value : LocalContrast SDR+ table address
//--------------------------------------------------
BYTE *UserAdjustGetLocalContrastSDRPlusAddress(void)
{
    return tCOLOR_LOCALCONTRAST_SDR_PLUS_TABLE[0];
}
#endif

#endif // End of #if(_LOCAL_CONTRAST_SUPPORT == _ON)
#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)
