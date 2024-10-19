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
// ID Code      : RTD2020UserInterfaceVga.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_VGA__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceVga.h"

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
#if(_VGA_SUPPORT == _ON)
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get VGA mode data in flash
// Input Value  : None
// Output Value : VGA mode user data base ID
//--------------------------------------------------
WORD UserInterfaceVgaGetModeFlashIdBase(void)
{
    return _FLASH_ITEMID_MODE_USER_DATA;
}
#endif

//--------------------------------------------------
// Description  : Check ModeIndex
// Input Value  : System ModeIndex
// Output Value : ModeIndex
//--------------------------------------------------
BYTE UserInterfaceVgaGetConfuseMode(BYTE ucModeIndex)
{
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    if((ucModeIndex == _MODE_640x480_60HZ) ||
       (ucModeIndex == _MODE_720x480_60HZ_GTF) ||
       (ucModeIndex == _MODE_720x480p_60HZ))
    {
        if(stTimingInfo.usVSWidth <= 4)
        {
            ucModeIndex = _MODE_640x480_60HZ;

            DebugMessageAnalog("Detected by Special Case to 640x480-60", _MODE_640x480_60HZ);
        }
        else if((stTimingInfo.b1HSP == _FALSE) &&
                (stTimingInfo.b1VSP == _FALSE))
        {
            ucModeIndex = _MODE_720x480_60HZ_GTF;

            DebugMessageAnalog("Detected by Special Case to 720x480-60_GTF", _MODE_720x480_60HZ_GTF);
        }
        else
        {
            ucModeIndex = _MODE_720x480p_60HZ;

            DebugMessageAnalog("Detected by Special Case to 720x480-60", _MODE_720x480p_60HZ);
        }
    }

    if((ucModeIndex == _MODE_720x400_70HZ) ||
       (ucModeIndex == _MODE_640x400_70HZ))
    {
        if((stTimingInfo.b1HSP == _TRUE) &&
           (stTimingInfo.b1VSP == _FALSE))
        {
            ucModeIndex = _MODE_640x350_70HZ;

            DebugMessageAnalog("Detected by Special Case to _MODE_640x350_70HZ", _MODE_640x350_70HZ);
        }
    }

    if((ucModeIndex == _MODE_640x400_85HZ) ||
       (ucModeIndex == _MODE_720x400_85HZ))
    {
        if((stTimingInfo.b1HSP == _TRUE) &&
           (stTimingInfo.b1VSP == _FALSE))
        {
            ucModeIndex = _MODE_640x350_85HZ;
        }

        DebugMessageAnalog("Detected by Special Case to _MODE_640x350_85HZ", _MODE_640x350_85HZ);
    }

    return ucModeIndex;
}

//--------------------------------------------------
// Description  : Check Load Mode Table Value
// Input Value  : None
// Output Value : _TRUE -> Force Load Mode Table Value
//--------------------------------------------------
EnumModeTableStatus UserInterfaceVgaGetLoadModeTableDefaultStatus(void)
{
    return _LOAD_MODE_TABLE_FALSE;
}

//--------------------------------------------------
// Description  : Check VGA First Auto Config
// Input Value  : None
// Output Value : _TRUE => Do Auto Config
//--------------------------------------------------
EnumAutoConfigAction UserInterfaceVgaGetFirstAutoConfigStatus(void)
{
    if(GET_VGA_MODE_DO_FIRST_AUTO() == _TRUE)
    {
        EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
        StructTimingInfo stTimingInfo;

        memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

        // Read timing info
        SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

        if(stTimingInfo.usHWidth > 720)
        {
            return _DO_AUTO_CONFIG_TRUE;
        }
    }

    return _DO_AUTO_CONFIG_FALSE;
}

//--------------------------------------------------
// Description  : Percentage of AutoConfig
// Input Value  : Percentage
// Output Value : None
//--------------------------------------------------
void UserInterfaceVgaGetAutoConfigPercentage(BYTE ucAutoPercentage)
{
    g_usAdjustValue = ucAutoPercentage;
    if(GET_OSD_STATE() != _MENU_NONE)
    {
        OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
    }
}

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for V position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumAutoConfigSkip UserInterfaceVgaSkipAutoVpos(void)
{
    return _AUTO_CONFIG_SKIP_FALSE;
}

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for H position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumAutoConfigSkip UserInterfaceVgaSkipAutoHpos(void)
{
    return _AUTO_CONFIG_SKIP_FALSE;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

