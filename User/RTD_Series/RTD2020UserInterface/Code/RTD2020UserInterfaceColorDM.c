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
// ID Code      : RTD2020UserInterfaceColorDM.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DM__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColorDM.h"

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
// Description  : Set DM Entry/Exit OSD Event
// Input Value  : EnumDisplayRegion, enumRegionIndex
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDMSetOsdEvent(EnumDisplayRegion enumDisplayRegion, EnumDMOsdEvent enumDMOsdEvent)
{
    switch(enumDMOsdEvent)
    {
        case _DM_OSD_ENTRY:
            if(GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(enumDisplayRegion)) == _ENABLE)
            {
                EnumRegionIndex enumRegionIndex = UserCommonRegionGetIndex(enumDisplayRegion);
                // Show DM Logo in Main
                if(enumRegionIndex == _REGION_INDEX_0)
                {
                    UserCommonTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_DVISION_SHOW_LOGO_MAIN);
                }
                // Show DM Logo in Sub
                else if(enumRegionIndex == _REGION_INDEX_1)
                {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    if(enumDisplayRegion != _DISPLAY_RGN_EAGLE_SIGHT_SUB)
#endif
                    {
                        UserCommonTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_DVISION_SHOW_LOGO_SUB);
                    }
                }
            }
            break;

        case _DM_OSD_EXIT:
            // Disable all OSD for RTD User
            // User can implement different method to disable DM logo/OSD
            if(GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(enumDisplayRegion)) == _ENABLE)
            {
                if(UserCommonRegionGetIndex(enumDisplayRegion) == _REGION_INDEX_0)
                {
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DVISION_SHOW_LOGO_MAIN);
                }
                else if(UserCommonRegionGetIndex(enumDisplayRegion) == _REGION_INDEX_1)
                {
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DVISION_SHOW_LOGO_SUB);
                }

                OsdDispDisableOsd();
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Decide whether to Enable DM Function
// Input Value  : EnumDisplayRegion
// Output Value : _ON or _OFF
//--------------------------------------------------
EnumDMSupport UserInterfaceColorDMGetEnableStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(GET_OSD_DVISION(SysRegionGetInputPort(enumDisplayRegion)) == _ON)
    {
        return _DM_SUPPORT_ON;
    }
    else
    {
        return _DM_SUPPORT_OFF;
    }
}

//--------------------------------------------------
// Description  : Update DM OSD Picture Mode Setting
// Input Value  : EnumHDRTargetStatus
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDMUpdatePictureMode(EnumDisplayRegion enumDisplayRegion, BYTE ucDMPictureMode)
{
    enumDisplayRegion = enumDisplayRegion;
    ucDMPictureMode = ucDMPictureMode;
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
    // Update Current DM Picture Mode to OSD Data
    // Game -> Non-Game : reset to Bright/Dark/User Mode
    // Non-Game -> Game : set to Game Mode

    if(ucDMPictureMode == _DM_CONFIG_GAME_MODE_INDEX)
    {
        // backup user normal mode (bright/dark/user...)
        switch(GET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion((EnumSelRegion)enumDisplayRegion)))
        {
            case _OSD_DVISION_PICTURE_BRIGHT:
                UserCommonColorDMSetBackupMode(enumDisplayRegion, _DM_CONFIG_BRIGHT_MODE_INDEX);
                break;
            case _OSD_DVISION_PICTURE_DARK:
                UserCommonColorDMSetBackupMode(enumDisplayRegion, _DM_CONFIG_DARK_MODE_INDEX);
                break;
            case _OSD_DVISION_PICTURE_USER:
                UserCommonColorDMSetBackupMode(enumDisplayRegion, _DM_CONFIG_USER_MODE_INDEX);
                break;
            default:
                UserCommonColorDMSetBackupMode(enumDisplayRegion, _DM_CONFIG_BRIGHT_MODE_INDEX);
                break;
        }

        // set to current mode
        SET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion((EnumSelRegion)enumDisplayRegion), _OSD_DVISION_PICTURE_GAME);
    }
    else
    {
        // set to current mode
        switch(ucDMPictureMode)
        {
            case _DM_CONFIG_BRIGHT_MODE_INDEX:
                SET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion((EnumSelRegion)enumDisplayRegion), _OSD_DVISION_PICTURE_BRIGHT);
                break;
            case _DM_CONFIG_DARK_MODE_INDEX:
                SET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion((EnumSelRegion)enumDisplayRegion), _OSD_DVISION_PICTURE_DARK);
                break;
            case _DM_CONFIG_USER_MODE_INDEX:
                SET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion((EnumSelRegion)enumDisplayRegion), _OSD_DVISION_PICTURE_USER);
                break;
            default:
                SET_DVISION_PICTURE(UserAdjustGetOSDSelectRegion((EnumSelRegion)enumDisplayRegion), _OSD_DVISION_PICTURE_BRIGHT);
                break;
        }
    }
#endif

    if((GET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].b7DVisionBacklight) &&
       (GET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionBrightness) &&
       (GET_DVISION_CONTRAST(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionContrast) &&
       (GET_DVISION_SATURATION(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionSaturation))
    {
        SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _OFF);
    }
    else
    {
        SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _ON);
    }

    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
}


//--------------------------------------------------
// Description  : User function Get Data for DM
// Input Value  : Select Region, Ultravivid settings struct
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDMGetData(EnumSelRegion enumSelRegion, Struct3rdPartyDMOsdSetting *pstDMOsdData)
{
    BYTE ucSelRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);

    switch(GET_DVISION_PICTURE(ucSelRegion))
    {
        case _OSD_DVISION_PICTURE_DARK:
            pstDMOsdData->lDMPictureMode = _DM_CONFIG_DARK_MODE_INDEX;
            break;

        case _OSD_DVISION_PICTURE_BRIGHT:
            pstDMOsdData->lDMPictureMode = _DM_CONFIG_BRIGHT_MODE_INDEX;
            break;

        case _OSD_DVISION_PICTURE_GAME:
            pstDMOsdData->lDMPictureMode = _DM_CONFIG_GAME_MODE_INDEX;
            break;

        case _OSD_DVISION_PICTURE_USER:
            pstDMOsdData->lDMPictureMode = _DM_CONFIG_USER_MODE_INDEX;
            break;

        default:
            pstDMOsdData->lDMPictureMode = _DM_PICTURE_MODE_NONE;
            DebugMessageDM("DM_ERROR_PICTURE_MODE", 0);
            break;
    }

    pstDMOsdData->stDMColorData.usBacklightData = GET_DVISION_BACKLIGHT(ucSelRegion);
    pstDMOsdData->stDMColorData.usBrightnessData = GET_DVISION_BRIGHTNESS(ucSelRegion);
    pstDMOsdData->stDMColorData.usContrastData = GET_DVISION_CONTRAST(ucSelRegion);
    pstDMOsdData->stDMColorData.usSaturationData = GET_DVISION_SATURATION(ucSelRegion);
}

//--------------------------------------------------
// Description  : Adjust to DM Mode
// Input Value  : EnumDisplayRegion, EnumHDRTargetStatus
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorDMAdjust(EnumDisplayRegion enumDisplayRegion, EnumHDRTargetStatus enumHDRTargetStatus, EnumDMAdjustType enumAdjustType)
{
    enumDisplayRegion = enumDisplayRegion;
    if((enumHDRTargetStatus == _HDR_TARGET_STATUS_DM) || (enumHDRTargetStatus == _HDR_TARGET_STATUS_DM_GAME))
    {
        // DM need backlight to be maximum
        UserAdjustBacklight(_BACKLIGHT_MAX);
    }

    // if(enumAdjustType == _DM_ADJUST_DM_ONLY), user adjust specified color setting here
    enumAdjustType = enumAdjustType;
}
#endif // End of #if(_IS_MAIN_PROCESS_CPU == _TRUE)
#endif // End of #if(_DM_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
