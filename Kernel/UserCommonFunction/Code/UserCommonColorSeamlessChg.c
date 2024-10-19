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
// ID Code      : UserCommonColorSeamlessChg.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_SEAMLESS_CHG__

#include "UserCommonInclude.h"
#include "ColorSeamlessChg/UserCommonColorSeamlessChg.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
StructColorimetrySetting g_pstColorimetrySetting[_MULTI_DISPLAY_MAX];
StructColorimetryUpdate g_pstColorimetryUpdate[_MULTI_DISPLAY_MAX];
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
StructColorFormatSetting g_pstColorFormatSetting[_MULTI_DISPLAY_MAX];
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Seamless Change Adjust
// Input Value  : EnumDisplayRegion, EnumSeamlessFlowStatus
// Output Value : none
//--------------------------------------------------
void UserCommonColorSeamlessChgInitial(EnumDisplayRegion enumDisplayRegion)
{
#if(_DIGITAL_PORT_SUPPORT == _ON)
    if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
    {
        return;
    }
#endif

    SET_COLORIMETRY_SETTING(enumDisplayRegion, ScalerColorSpaceGetColorimetry(SysRegionGetInputPort(enumDisplayRegion)));
    SET_EXT_COLORIMETRY_SETTING(enumDisplayRegion, ScalerColorSpaceGetExtColorimetry(SysRegionGetInputPort(enumDisplayRegion)));

#if(_HDR10_SUPPORT == _ON)
    CLR_HDR10_UPDATE_COLORIMETRY(enumDisplayRegion);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    CLR_FREESYNC_II_UPDATE_COLORIMETRY(enumDisplayRegion);
#endif

    CLR_SDR_UPDATE_COLORIMETRY(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Seamless Change Handler
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorSeamlessChgHandler(EnumDisplayRegion enumDisplayRegion)
{
#if(_DIGITAL_PORT_SUPPORT == _ON)
    if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
    {
        return;
    }
#endif

    if(UserCommonColorSeamlessChgGetChangeStatus(enumDisplayRegion) == _COLORIMETRY_CHANGE)
    {
        EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);

#if(_COLOR_IP_COLOR_CONVERT == _ON)
        UserCommonColorSetColorFormatConvert(enumDisplayRegion, enumInputPort, ScalerColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion)), _DB_APPLY_NO_POLLING);
#endif

#if(_HDR10_SUPPORT == _ON)
        if(GET_HDR10_UPDATE_COLORIMETRY(enumDisplayRegion) == _FALSE)
        {
            EnumHDRTargetStatus enumHDRTargetStatus = GET_HDR_TARGET_STATUS(enumDisplayRegion);

            if((enumHDRTargetStatus == _HDR_TARGET_STATUS_SMPTE_ST_2084) || (enumHDRTargetStatus == _HDR_TARGET_STATUS_AUTO_HLG) || (enumHDRTargetStatus == _HDR_TARGET_STATUS_ADVANCED_HDR10))
            {
                UserCommonColorPCMRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_POLLING, _OFF);
                UserCommonColorSRGBAdjust((EnumSelRegion)enumDisplayRegion);
                UserCommonColorPCMRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NO_POLLING, _ON);

                DebugMessageHDR("color matrix seamless change ", 0x00);
            }
        }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        if(GET_FREESYNC_II_UPDATE_COLORIMETRY(enumDisplayRegion) == _FALSE)
        {
        }
#endif

        if(GET_SDR_UPDATE_COLORIMETRY(enumDisplayRegion) == _FALSE)
        {
        }
    }

#if(_HDR10_SUPPORT == _ON)
    CLR_HDR10_UPDATE_COLORIMETRY(enumDisplayRegion);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    CLR_FREESYNC_II_UPDATE_COLORIMETRY(enumDisplayRegion);
#endif

    CLR_SDR_UPDATE_COLORIMETRY(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Check Colorimetry change status
// Input Value  : EnumDisplayRegion
// Output Value : Colorimetry chagne status
//--------------------------------------------------
EnumColorimetryChangeStatus UserCommonColorSeamlessChgGetChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
    EnumSourceType enumSourceType = SysRegionGetSourceType(enumDisplayRegion);

    if((enumSourceType == _SOURCE_VGA) || (enumSourceType == _SOURCE_DVI))
    {
        return _COLORIMETRY_NO_CHANGE;
    }

    if((GET_COLORIMETRY_SETTING(enumDisplayRegion) != ScalerColorSpaceGetColorimetry(SysRegionGetInputPort(enumDisplayRegion))) ||
       (GET_EXT_COLORIMETRY_SETTING(enumDisplayRegion) != ScalerColorSpaceGetExtColorimetry(SysRegionGetInputPort(enumDisplayRegion))))
    {
        SET_COLORIMETRY_SETTING(enumDisplayRegion, ScalerColorSpaceGetColorimetry(SysRegionGetInputPort(enumDisplayRegion)));
        SET_EXT_COLORIMETRY_SETTING(enumDisplayRegion, ScalerColorSpaceGetExtColorimetry(SysRegionGetInputPort(enumDisplayRegion)));

#if(_DIGITAL_PORT_SUPPORT == _ON)
        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            return _COLORIMETRY_CHANGE;
        }
#endif
    }

    return _COLORIMETRY_NO_CHANGE;
}
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Seamless Change Adjust
// Input Value  : EnumDisplayRegion, EnumSeamlessFlowStatus
// Output Value : none
//--------------------------------------------------
void UserCommonColorDMFormatChgWoResetInitial(EnumDisplayRegion enumDisplayRegion)
{
    SET_COLORSPACE_SETTING(enumDisplayRegion, ScalerColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion)));
    SET_COLORDEPTH_SETTING(enumDisplayRegion, ScalerColorGetColorDepth(SysRegionGetInputPort(enumDisplayRegion)));
}

//--------------------------------------------------
// Description  : Seamless Change Handler
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMFormatChgWoResetHandler(EnumDisplayRegion enumDisplayRegion)
{
#if(_DIGITAL_PORT_SUPPORT == _ON)
    if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _TRUE)
    {
        return;
    }
#endif

    if(UserCommonColorDMFormatChgWoResetGetChangeStatus(enumDisplayRegion) == _COLORFORMAT_CHANGE)
    {
        EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
#if(_DM_FUNCTION == _ON)
        EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
        UserCommonColorSetColorFormatConvert(enumDisplayRegion, enumInputPort, ScalerColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion)), _DB_APPLY_NO_POLLING);
#endif

#if(_COLOR_IP_DM == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
        {
            ScalerColor422To444DM(enumInputPort, enumDisplayRegion, _OFF);
        }
        else
#endif
#endif
        {
            ScalerColor422To444(enumInputPort, enumDisplayRegion);
        }
#if(_DM_FUNCTION == _ON)
        // Reset BEC(TR9) to stand by
        SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

        // Reset DM mute status
        if((GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_MUTE) || (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_UNMUTE_READY))
        {
            SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Check Colorimetry change status
// Input Value  : EnumDisplayRegion
// Output Value : Colorimetry chagne status
//--------------------------------------------------
EnumColorFormatChangeStatus UserCommonColorDMFormatChgWoResetGetChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
    if((GET_COLORSPACE_SETTING(enumDisplayRegion) != ScalerColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion))) ||
       (GET_COLORDEPTH_SETTING(enumDisplayRegion) != ScalerColorGetColorDepth(SysRegionGetInputPort(enumDisplayRegion))))
    {
        SET_COLORSPACE_SETTING(enumDisplayRegion, ScalerColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion)));
        SET_COLORDEPTH_SETTING(enumDisplayRegion, ScalerColorGetColorDepth(SysRegionGetInputPort(enumDisplayRegion)));

#if(_DIGITAL_PORT_SUPPORT == _ON)
        if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            return _COLORFORMAT_CHANGE;
        }
#endif
    }

    return _COLORFORMAT_NO_CHANGE;
}
#endif
