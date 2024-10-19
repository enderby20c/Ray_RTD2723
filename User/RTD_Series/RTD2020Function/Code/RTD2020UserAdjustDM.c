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
// ID Code      : RTD2020UserAdjustDM.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __USER_ADJUST_DM__

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
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : DM PQ Measurement Status
// Input Value  : EnumSelRegion
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
BYTE UserAdjustDMPQMeasure(EnumSelRegion enumSelRegion)
{
    EnumDisplayRegion enumDisplayRegion = UserCommonColorDMGetDisplayRegion(enumSelRegion);
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) != _HDR10_OFF)
    {
        // Recommend return FALSE. If returned TRUE, HDR10 content will be applied to the Dolby Color settings.
        return _FALSE;
    }

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetAdvancedHDR10Status(enumDisplayRegion) == _ADVANCED_HDR10_ON)
    {
        // Recommend return FALSE. If returned TRUE, HDR10+ content will be applied to the Dolby Color settings.
        return _FALSE;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        // Recommend return FALSE. If returned TRUE, FS2 content will be applied to the Dolby Color settings.
        return _FALSE;
    }
#endif

    // Dolby SDR
    return _FALSE;
}
#endif // End of #if(_IS_MAIN_PROCESS_CPU == _TRUE)
#endif // End of #if(_DM_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
