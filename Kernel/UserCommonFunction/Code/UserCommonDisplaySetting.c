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
// ID Code      : UserCommonDisplaySetting.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "DisplaySetting/UserCommonDisplaySetting.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_EAGLE_SIGHT_SUPPORT == _ON)
StructEagleSightSetting g_stMDomainEagleSightSetting;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User adjust target display mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayModeAdjust(EnumDisplayMode enumDisplayMode)
{
    EnumDisplayRegion enumAutoSearchTargetRegion = UserCommonSourceGetAutoSearchTarget();
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = 0;

    EnumInputPort penumRegionPortInfo[_MULTI_DISPLAY_MAX];

    penumRegionPortInfo[0] = UserCommonSourceGetInputPort0();
#if(_MULTI_DISPLAY_MAX >= 0x02)
    penumRegionPortInfo[1] = UserCommonSourceGetInputPort1();
#endif
#if(_MULTI_DISPLAY_MAX >= 0x03)
    penumRegionPortInfo[2] = UserCommonSourceGetInputPort2();
#endif
#if(_MULTI_DISPLAY_MAX >= 0x04)
    penumRegionPortInfo[3] = UserCommonSourceGetInputPort3();
#endif

    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);

    // Reset select region info
    SysRegionResetInfo();

    // Update display mode
    SysModeSetDisplayMode(enumDisplayMode);
    UserCommonNVRamSetSystemData(_DISPLAY_MODE, enumDisplayMode);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    SysModeSetEagleSightSupport();
#endif

    // Update auto search target
    SysSourceSetMultiAutoSearchTarget(enumAutoSearchTargetRegion);

#if(_FREESYNC_SUPPORT == _ON)
    UserCommonFreeSyncSupportSwitch();
#endif // End of #if(_FREESYNC_SUPPORT == _ON)

#if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))
    UserCommonDpAdaptiveSyncSupportSwitch();
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))

#if(_DSC_DECODER_SUPPORT == _ON)
    // Switch Capability of DSC with Display Mode
    UserCommonDscSwitchDisplayModeCapability();
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    ScalerDscDecoderSyncDpMstToSstSupportSwitch(UserCommonDscDecoderMst2sstGetEnable());
#endif

    // Update region count after display mode updated
    ucRegionCount = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);
    if(ucRegionCount >= _MULTI_DISPLAY_MAX)
    {
        ucRegionCount = _MULTI_DISPLAY_MAX;
    }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        ucRegionCount = 1;
    }
#endif

    // Assign port/region mapping for each region
    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        EnumDisplayRegion enumDisplayRegion = SysRegionGetDisplayRegion(ucRegionIndex);
        SysRegionUpdateInterface(enumDisplayRegion, penumRegionPortInfo[ucRegionIndex]);
        UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, penumRegionPortInfo[ucRegionIndex]);
    }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        SysRegionUpdateInterface(_DISPLAY_RGN_EAGLE_SIGHT_SUB, penumRegionPortInfo[_REGION_INDEX_0]);
    }
#endif

    if(enumAutoSearchTargetRegion != _DISPLAY_RGN_NONE)
    {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
        // Switch to auto target region, If InputPort is D3/D4, need to check it is D3/D4, D12/D14 or D13/D15?
        SysSourceSwitchInputPort(penumRegionPortInfo[ScalerRegionGetIndex(enumAutoSearchTargetRegion)]);
#else
        // Switch to auto target region
        SysSourceSwitchInputPort(SysRegionGetInputPort(enumAutoSearchTargetRegion));
#endif
    }
    else
    {
        // Switch to region 0
        SysSourceSwitchInputPort(penumRegionPortInfo[0]);
    }

    // Save system data
    UserCommonNVRamSaveSystemData();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    SysDpRxPxpPortNumSwapJudge();
#endif

#if(_DDCCI_CODE_REDUCTION == _OFF)
    if(UserInterfaceDdcciGetStatus() == _DDCCI_STATUS_ON)
    {
        UserCommonDdcciSwitchPort(_DDCCI_MODE);
    }
    else
#endif
    {
        UserCommonDdcciSwitchPort(_DEBUG_MODE);
    }

    UserCommonDdcciMapping();

    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_DISPLAY_INITIAL:
        case _MODE_STATUS_DISPLAY_SETTING:
        case _MODE_STATUS_DISPLAY_CHECK:
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
        case _MODE_STATUS_FACTORY:
#endif

            // Reset to display initial
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
            SET_FREE_RUN_DDOMAIN_SETTING(_DEFAULT_FREERUN_DDOMAIN_SETTING);
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User adjust input port of target display region
// Input Value  : enumDisplayRegion --> adjust target region
//                enumInputPort --> adjust target port
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayRegionInputPortAdjust(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    bit bHpCurrentRegionReadyToDisplay = _FALSE;

    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) &&
       ((SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE) || (SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_OOR)))
    {
        bHpCurrentRegionReadyToDisplay = _TRUE;
    }
#endif

    // Reset to display initial under power saving
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
    }
    else
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            // Reset path
            SysModeResetDataPath(ScalerRegionGetIndex(_DISPLAY_RGN_EAGLE_SIGHT_MAIN));
            SysModeResetDataPath(ScalerRegionGetIndex(_DISPLAY_RGN_EAGLE_SIGHT_SUB));
        }
        else
#endif
        {
            // Reset path
            SysModeResetDataPath(ScalerRegionGetIndex(enumDisplayRegion));

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
#if(_DP_MST_PXP_FIXED_MODE_SUPPORT == _ON)
            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_MODE() == _DP_MST_PXP_ON_FIXED_MODE))
            {
                if((enumInputPort != _D9_INPUT_PORT) && (SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP))
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D9_INPUT_PORT));
                }
            }
#endif
#endif
        }
    }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        // Update region/port mapping
        SysRegionUpdateInterface(_DISPLAY_RGN_EAGLE_SIGHT_MAIN, enumInputPort);
        SysRegionUpdateInterface(_DISPLAY_RGN_EAGLE_SIGHT_SUB, enumInputPort);
    }
    else
#endif
    {
        // Update region/port mapping
        SysRegionUpdateInterface(enumDisplayRegion, enumInputPort);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
#if(_DP_MST_PXP_FIXED_MODE_SUPPORT == _ON)
        if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_MODE() == _DP_MST_PXP_ON_FIXED_MODE))
        {
            if((enumInputPort != _D9_INPUT_PORT) && (SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP))
            {
                // Update region/port mapping
                SysRegionUpdateInterface(SysRegionConvertPortToRegion(_D9_INPUT_PORT), _D9_INPUT_PORT);
            }
        }
#endif
#endif
    }

    // Update auto search target
    SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    if(bHpCurrentRegionReadyToDisplay == _FALSE)
#endif
    {
        // Update system data in NVRAM
        UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, enumInputPort);
    }

    // Switch source handler search port
    SysSourceSwitchInputPort(enumInputPort);

    // Save system data
    UserCommonNVRamSaveSystemData();
}

//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : Current Input Timing Info
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserCommonDisplayAdjustInputTiming(EnumDisplayRegion enumDisplayRegion)
{
    UserInterfaceDisplayAdjustInputTiming(enumDisplayRegion);

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    UserCommonDisplayAdjustRotationInputSize();
#endif

#if(_OVERSCAN_SUPPORT == _ON)
    UserCommonDisplayAdjustOverScan(enumDisplayRegion);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    SysModeEagleSightInputCapture();
#endif
}

//--------------------------------------------------
// Description  : Modify Display Timing Based on User Requirement
// Input Value  : Display region
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion)
{
#if(_ASPECT_RATIO_SUPPORT == _ON)
    UserCommonDisplayAdjustAspectRatio(enumDisplayRegion);
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    UserCommonDisplayAdjustRotationDisplaySize();
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    SysModeEagleSightDisplayCapture();
#endif

    UserInterfaceDisplayAdjustDisplayTiming(enumDisplayRegion);

#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
    if(enumDisplayRegion == _DISPLAY_RGN_PIP_SUB)
    {
        SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HSTART());
        SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH());
        SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());
        SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT());
    }
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
    ScalerMDomainSetESOriginalModeHVStart(enumDisplayRegion);
#endif
#endif
}

//--------------------------------------------------
// Description  : Get Max or Min H-Position
// Input Value  : ucPar--> Max or Min paramater
// Output Value : Max or Min H-Position
//--------------------------------------------------
WORD UserCommonDisplayGetHPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion)
{
    WORD usDeltaIHWidthOverScan = 0;
#if((_VGA_SUPPORT == _ON) || (_OVERSCAN_SUPPORT == _ON) || (_DISPLAY_ROTATION_SUPPORT == _ON))
    WORD usIHWidth = GET_INPUT_TIMING_HWIDTH();
#endif

#if(_OVERSCAN_SUPPORT == _ON)
    EnumOverScanStatus enumOverScanStatus = UserInterfaceDisplayGetOverScanStatus(enumDisplayRegion);
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IHWIDTH);
    }
    else
#endif
    {
#if(_OVERSCAN_SUPPORT == _ON)
        if(enumOverScanStatus == _OVERSCAN_TRUE)
        {
            if(usIHWidth >= ScalerVgipGetCaptureHWidth())
            {
                if(ScalerFmtCnvFtoPGetStatus(ScalerRegionGetInputDataPath(enumDisplayRegion)) == _FALSE)
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()) / 2);
                }
                else
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()));
                }
            }
        }
#endif
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_OVERSCAN_SUPPORT == _ON)
    if(enumOverScanStatus == _OVERSCAN_FALSE)
#endif
    {
        if((ScalerRotationCheckStatus(GET_ROT_TYPE(), SysRegionGetInputPort(enumDisplayRegion)) == _TRUE) && (GET_ROT_DISP_SIZE() == _ROT_PIXEL_BY_PIXEL))
        {
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
            if(ScalerRotationCheckVerticalStatus() == _TRUE)
            {
                if(_PANEL_DV_HEIGHT < usIHWidth)
                {
                    usDeltaIHWidthOverScan = (usIHWidth - _PANEL_DV_HEIGHT);
                }
            }
            else
#endif
            {
                if(GET_ROT_TYPE() == _ROT_CW180)
                {
                    // Calculate / Set H
                    if(_PANEL_DH_WIDTH < usIHWidth)
                    {
                        usDeltaIHWidthOverScan = (usIHWidth - _PANEL_DH_WIDTH);
                    }
                }
            }
        }
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        if(ucPar == _GET_HPOSITIONRANGE_MAX)
        {
            return (g_stVgaModeUserData.usCenterHPosition + _HPOSITION_BIAS);
        }
        else if(ucPar == _GET_HPOSITIONRANGE_MIN)
        {
            return (g_stVgaModeUserData.usCenterHPosition - _HPOSITION_BIAS);
        }
        else
        {
            return (g_stVgaModeUserData.usCenterHPosition);
        }
    }
    else
#endif
    {
        if(ucPar == _GET_HPOSITIONRANGE_MAX)
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan + _HPOSITION_BIAS);
        }
        else if(ucPar == _GET_HPOSITIONRANGE_MIN)
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - _HPOSITION_BIAS);
        }
        else
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan);
        }
    }
}

//--------------------------------------------------
// Description  : Get HPosition H Bias Value
// Input Value  : None
// Output Value : H Bias Value
//--------------------------------------------------
WORD UserCommonDisplayGetHPositionHBiasValue(EnumDisplayRegion enumDisplayRegion)
{
    WORD usHBias = 0;
    WORD usDeltaIHWidthOverScan = 0;

#if((_VGA_SUPPORT == _ON) || (_OVERSCAN_SUPPORT == _ON))
    WORD usIHWidth = 0;
#endif

    enumDisplayRegion = enumDisplayRegion;

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IHWIDTH);

        usHBias = ((g_stVgaModeUserData.usCenterHPosition - ScalerVgaTopGetCaptureHStartPosition()) <= (_MAX_H_POSITION_RANGE / 2)) ?
                  (g_stVgaModeUserData.usCenterHPosition - ScalerVgaTopGetCaptureHStartPosition() - 1) : (_MAX_H_POSITION_RANGE / 2);
    }
    else
#endif
    {
#if(_OVERSCAN_SUPPORT == _ON)
        usIHWidth = GET_INPUT_TIMING_HWIDTH();

        if(UserInterfaceDisplayGetOverScanStatus(enumDisplayRegion) == _OVERSCAN_TRUE)
        {
            if(usIHWidth >= ScalerVgipGetCaptureHWidth())
            {
                usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()) / 2);
            }
        }
#endif

        usHBias = ((GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - ScalerVgipGetCaptureHStartPosition()) <= (_MAX_H_POSITION_RANGE / 2)) ?
                  (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - ScalerVgipGetCaptureHStartPosition() - 1) : (_MAX_H_POSITION_RANGE / 2);
    }

    return usHBias;
}

//--------------------------------------------------
// Description  : Get Max or Min V-Position
// Input Value  : ucPar--> Max or Min paramater
// Output Value : Max or Min V-Position
//--------------------------------------------------
WORD UserCommonDisplayGetVPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion)
{
    WORD usDeltaIVHeightOverScan = 0;
    WORD usDeltaIVHeightUnderScan = 0;
    WORD usIVHeight = 0;
#if(_OVERSCAN_SUPPORT == _ON)
    EnumOverScanStatus enumOverScanStatus = UserInterfaceDisplayGetOverScanStatus(enumDisplayRegion);
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIVHeight = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVHEIGHT);

#if(_OVERSCAN_SUPPORT == _ON)
        if(enumOverScanStatus == _OVERSCAN_TRUE)
        {
            if(usIVHeight >= ScalerVgaTopGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgaTopGetCaptureVHeight()) / 2);
            }
        }
#endif
    }
    else
#endif
    {
        usIVHeight = GET_INPUT_TIMING_VHEIGHT();

#if(_OVERSCAN_SUPPORT == _ON)
        if(enumOverScanStatus == _OVERSCAN_TRUE)
        {
            if(usIVHeight >= ScalerVgipGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgipGetCaptureVHeight()) / 2);
            }
        }
#endif
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_OVERSCAN_SUPPORT == _ON)
    if(enumOverScanStatus == _OVERSCAN_FALSE)
#endif
    {
        if((ScalerRotationCheckStatus(GET_ROT_TYPE(), SysRegionGetInputPort(enumDisplayRegion)) == _TRUE) && (GET_ROT_DISP_SIZE() == _ROT_PIXEL_BY_PIXEL))
        {
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
            if(ScalerRotationCheckVerticalStatus() == _TRUE)
            {
                // Calculate / Set V
                if(_PANEL_DH_WIDTH < usIVHeight)
                {
                    usDeltaIVHeightOverScan = ((usIVHeight - _PANEL_DH_WIDTH) / 2);
                }
            }
            else
#endif
            {
                if(GET_ROT_TYPE() == _ROT_CW180)
                {
                    if(_PANEL_DV_HEIGHT < usIVHeight)
                    {
                        usDeltaIVHeightOverScan = ((usIVHeight - _PANEL_DV_HEIGHT) / 2);
                    }
                }
            }
        }
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        if(usIVHeight <= ScalerVgaTopGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgaTopGetCaptureVHeight() - usIVHeight) / 2);
        }

        if(ucPar == _GET_VPOSITIONRANGE_MAX)
        {
            return (g_stVgaModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan + _VPOSITION_BIAS);
        }
        else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        {
            return (g_stVgaModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - _VPOSITION_BIAS);
        }
        else
        {
            return (g_stVgaModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan);
        }
    }
    else
#endif
    {
        if(usIVHeight <= ScalerVgipGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgipGetCaptureVHeight() - usIVHeight) / 2);
        }

        if(ucPar == _GET_VPOSITIONRANGE_MAX)
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan + _VPOSITION_BIAS);
        }
        else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - _VPOSITION_BIAS);
        }
        else
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan);
        }
    }
}

//--------------------------------------------------
// Description  : Get VPosition V Bias Value
// Input Value  : None
// Output Value : V Bias Value
//--------------------------------------------------
WORD UserCommonDisplayGetVPositionVBiasValue(EnumDisplayRegion enumDisplayRegion)
{
    WORD usVBias = 0;
    WORD usDeltaIVHeightOverScan = 0;
    WORD usDeltaIVHeightUnderScan = 0;
    WORD usIVHeight = 0;
#if(_OVERSCAN_SUPPORT == _ON)
    EnumOverScanStatus enumOverScanStatus = UserInterfaceDisplayGetOverScanStatus(enumDisplayRegion);
#endif

    enumDisplayRegion = enumDisplayRegion;

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIVHeight = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVHEIGHT);

#if(_OVERSCAN_SUPPORT == _ON)
        if(enumOverScanStatus == _OVERSCAN_TRUE)
        {
            if(usIVHeight >= ScalerVgaTopGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgaTopGetCaptureVHeight()) / 2);
            }
        }
#endif

        if(usIVHeight <= ScalerVgaTopGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgaTopGetCaptureVHeight() - usIVHeight) / 2);
        }

        usVBias = ((g_stVgaModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgaTopGetCaptureVStartPosition()) < (_MAX_V_POSITION_RANGE / 2)) ?
                  (g_stVgaModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgaTopGetCaptureVStartPosition()) : (_MAX_V_POSITION_RANGE / 2);
    }
    else
#endif
    {
        usIVHeight = GET_INPUT_TIMING_VHEIGHT();

#if(_OVERSCAN_SUPPORT == _ON)
        if(enumOverScanStatus == _OVERSCAN_TRUE)
        {
            if(usIVHeight >= ScalerVgipGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgipGetCaptureVHeight()) / 2);
            }
        }
#endif

        if(usIVHeight <= ScalerVgipGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgipGetCaptureVHeight() - usIVHeight) / 2);
        }

        usVBias = ((GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgipGetCaptureVStartPosition()) < (_MAX_V_POSITION_RANGE / 2)) ?
                  (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgipGetCaptureVStartPosition()) : (_MAX_V_POSITION_RANGE / 2);
    }

    return usVBias;
}

//--------------------------------------------------
// Description  : Adjust picture position.
// Input Value  : ucUserHPosition --> Current percentage of H position associate to OSD bar
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayHPositionAdjust(BYTE ucUserHPosition, EnumDisplayRegion enumDisplayRegion)
{
    WORD usTargetIHStart = 0;
    WORD usHPositionRangeMax = 0;
    WORD usHPositionRangeMin = 0;
    SWORD shHDelay = 0;
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);

    ScalerVgipSetInputRegion(enumDisplayRegion);
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    usHPositionRangeMax = UserCommonDisplayGetHPositionRange(_GET_HPOSITIONRANGE_MAX, enumDisplayRegion);
    usHPositionRangeMin = UserCommonDisplayGetHPositionRange(_GET_HPOSITIONRANGE_MIN, enumDisplayRegion);

    usTargetIHStart = UserCommonDisplayPercentToRealValueAdjust((100 - ucUserHPosition), usHPositionRangeMax, usHPositionRangeMin, (((usHPositionRangeMax - usHPositionRangeMin) / 2) + usHPositionRangeMin));

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        // Disable Wach dog
        SysVgaWatchDog(_DISABLE);

        shHDelay = (SWORD)usTargetIHStart - (SWORD)ScalerVgaTopGetCaptureHStartPosition();

        if((ScalerColorGetColorSpace(enumInputPort) == _COLOR_SPACE_YCBCR422) || (ScalerColorGetColorSpace(enumInputPort) == _COLOR_SPACE_YCBCR420))
        {
            shHDelay += ((shHDelay - ScalerVgaTopGetCaptureHDelay()) % 2);
        }

        // Can't set IH delay to 0 by HW limit
        shHDelay = (shHDelay < 1) ? 1 : shHDelay;

        // Compensate IHS delay
        ScalerVgaTopSetCaptureHDelay(shHDelay);

        // Apply the above setting by setting Double Buffer Ready in VGIP
        ScalerVgaTopDoubleBufferApply();

        // Enable Wach dog
        SysVgaWatchDog(_ENABLE);
    }
    else
#endif
    {
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            // Disable Wach dog
            ScalerRegionSetWatchDog(enumDisplayRegion, _DISABLE);

            shHDelay = (SWORD)usTargetIHStart - (SWORD)ScalerVgipGetCaptureHStartPosition();

            if((ScalerColorGetColorSpace(enumInputPort) == _COLOR_SPACE_YCBCR422) || (ScalerColorGetColorSpace(enumInputPort) == _COLOR_SPACE_YCBCR420))
            {
                shHDelay += ((shHDelay - ScalerVgipGetCaptureHDelay()) % 2);
            }

            // Can't set IH delay to 0 by HW limit
            shHDelay = (shHDelay < 1) ? 1 : shHDelay;

            // Compensate IHS delay
            ScalerVgipSetCaptureHDelay(shHDelay);

            // Apply the above setting by setting Double Buffer Ready in VGIP
            ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

            // Enable Wach dog
            ScalerRegionSetWatchDog(enumDisplayRegion, _ENABLE);
        }
    }
}

//--------------------------------------------------
// Description  : Adjust picture position.
// Input Value  : ucUserVPosition --> Current percentage of V position associate to OSD bar
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayVPositionAdjust(BYTE ucUserVPosition, EnumDisplayRegion enumDisplayRegion)
{
    WORD usTargetIVStart = 0;
    WORD usVDelayAdjustDeltaLimit = 0;
    WORD usVPositionRangeMax = 0;
    WORD usVPositionRangeMin = 0;
    SWORD shVDelay = 0;
    BYTE ucTimeoutCounter = 0;

    ScalerVgipSetInputRegion(enumDisplayRegion);
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    usVPositionRangeMax = UserCommonDisplayGetVPositionRange(_GET_VPOSITIONRANGE_MAX, enumDisplayRegion);
    usVPositionRangeMin = UserCommonDisplayGetVPositionRange(_GET_VPOSITIONRANGE_MIN, enumDisplayRegion);

    usTargetIVStart = UserCommonDisplayPercentToRealValueAdjust(ucUserVPosition, usVPositionRangeMax, usVPositionRangeMin, (((usVPositionRangeMax - usVPositionRangeMin) / 2) + usVPositionRangeMin));

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        SysVgaWatchDog(_DISABLE);

        shVDelay = (SWORD)usTargetIVStart - (SWORD)ScalerVgaTopGetCaptureVStartPosition();

        shVDelay = (shVDelay < 0) ? 0 : shVDelay;

        // Get current V adjust limit
        usVDelayAdjustDeltaLimit = ScalerMDomainGetVerticalAdjustLimit(_SOURCE_VGA);

        ucTimeoutCounter = (abs(shVDelay - ScalerVgaTopGetCaptureVDelay()) / usVDelayAdjustDeltaLimit) + 1;

        do
        {
            if(shVDelay > ScalerVgaTopGetCaptureVDelay())
            {
                ScalerVgaTopSetCaptureVDelay(shVDelay);
            }
            else
            {
                if((ScalerVgaTopGetCaptureVDelay() - shVDelay) <= usVDelayAdjustDeltaLimit)
                {
                    ScalerVgaTopSetCaptureVDelay(shVDelay);
                }
                else
                {
                    ScalerVgaTopSetCaptureVDelay(ScalerVgaTopGetCaptureVDelay() - usVDelayAdjustDeltaLimit);
                }
            }

            ScalerVgaTopDoubleBufferApply();

            ucTimeoutCounter--;
        }
        while((shVDelay != ScalerVgaTopGetCaptureVDelay()) && (ucTimeoutCounter > 0));

        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, ScalerRegionGetInputDataPath(enumDisplayRegion));
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, ScalerRegionGetInputDataPath(enumDisplayRegion));

        SysVgaWatchDog(_ENABLE);
    }
    else
#endif
    {
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            ScalerRegionSetWatchDog(enumDisplayRegion, _DISABLE);

            shVDelay = (SWORD)usTargetIVStart - (SWORD)ScalerVgipGetCaptureVStartPosition();

            shVDelay = (shVDelay < 0) ? 0 : shVDelay;

            // Get current V adjust limit
            usVDelayAdjustDeltaLimit = ScalerMDomainGetVerticalAdjustLimit(SysRegionGetSourceType(enumDisplayRegion));

            ucTimeoutCounter = (abs(shVDelay - ScalerVgipGetCaptureVDelay()) / usVDelayAdjustDeltaLimit) + 1;

            do
            {
                if(shVDelay > ScalerVgipGetCaptureVDelay())
                {
                    ScalerVgipSetCaptureVDelay(shVDelay);
                }
                else
                {
                    if((ScalerVgipGetCaptureVDelay() - shVDelay) <= usVDelayAdjustDeltaLimit)
                    {
                        ScalerVgipSetCaptureVDelay(shVDelay);
                    }
                    else
                    {
                        ScalerVgipSetCaptureVDelay(ScalerVgipGetCaptureVDelay() - usVDelayAdjustDeltaLimit);
                    }
                }

                ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

                ucTimeoutCounter--;
            }
            while((shVDelay != ScalerVgipGetCaptureVDelay()) && (ucTimeoutCounter > 0));

            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, ScalerRegionGetInputDataPath(enumDisplayRegion));

            ScalerRegionSetWatchDog(enumDisplayRegion, _ENABLE);
        }
    }
}

//--------------------------------------------------
// Description  :  Calculate value to percent for input range for 2 Sectors
// Input Value  :  usRealValue --> input real value
//                 usMax       --> the max value
//                 usMin       --> the min value
//                 usCenter    --> the Center Value
// Output Value :  Percent
//--------------------------------------------------
BYTE UserCommonDisplayRealValueToPercentAdjust(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter)
{
    WORD usTemp = 0;
    usRealValue = MINOF(usRealValue, usMax);
    usRealValue = MAXOF(usRealValue, usMin);

    if((usMax <= usMin) || (usCenter <= usMin) || (usCenter >= usMax))
    {
        usTemp = 0;
    }
    else
    {
        if(usRealValue < usCenter)
        {
            usTemp = (((DWORD)(usRealValue - usMin) * 10000) / (usCenter - usMin)) / 2;
        }
        else if(usRealValue > usCenter)
        {
            usTemp = (((DWORD)(usRealValue - usCenter) * 10000) / (usMax - usCenter)) / 2 + 5000;
        }
        else
        {
            return 50;
        }
    }

    if((usTemp % 100) > 49)
    {
        usTemp = usTemp + 100;
    }

    usTemp = usTemp / 100;

    return ((BYTE)usTemp);
}

//--------------------------------------------------
// Description  :  Calculate percent to real value for input range for 2 Sectors
// Input Value  :  ucPercentValue --> input percent value
//                 usMax          --> the max value
//                 usMin          --> the min value
//                 usCenter       --> the Center Value
// Output Value :  Real value
//--------------------------------------------------
WORD UserCommonDisplayPercentToRealValueAdjust(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter)
{
    DWORD ulTemp = 0;

    ucPercentValue = MINOF(100, ucPercentValue);

    if(ucPercentValue > 50)
    {
        ulTemp = (((DWORD)(ucPercentValue - 50) * (usMax - usCenter) * 10) / 50);
    }
    else if(ucPercentValue < 50)
    {
        ulTemp = (((DWORD)ucPercentValue * (usCenter - usMin) * 10) / 50);
    }
    else
    {
        return usCenter;
    }

    if((ulTemp % 10) > 5)
    {
        ulTemp = ulTemp + 10;
    }

    if(ucPercentValue > 50)
    {
        return (WORD)((ulTemp / 10) + usCenter);
    }
    else
    {
        return (WORD)((ulTemp / 10) + usMin); // <= 50
    }
}

#if(_DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE == _ON)
//--------------------------------------------------
// Description  : Get Image Boundary
// Input Value  :
// Output Value :
//--------------------------------------------------
bit UserCommonDisplayGetImageBoundary(BYTE ucNoiseMargin, StructImageRegion *pstImageRegion, EnumDisplayRegion enumDisplayRegion, bit bWait)
{
    bit bMeasurePass = _FALSE;

    if(SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_TIMING_CONFIRMED) == _TRUE)
    {
        StructAutoActiveData stAutoActiveRegion = {0};
        EnumColorSpace enumColorSpace = ScalerColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion));

        SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

        bMeasurePass = ScalerMeasureImageBoundary(ucNoiseMargin, &stAutoActiveRegion, enumDisplayRegion, enumColorSpace, bWait);

        if(bMeasurePass == _TRUE)
        {
            ScalerMeasureUpdateHVtiming(&stAutoActiveRegion, pstImageRegion, enumDisplayRegion);

#if((((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON)) && (_HW_SHIFT_ONE_LINE_TYPE == _VSD_SHIFT_ONE_LINE)) == _TRUE)
            EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
            BYTE ucVstartFineTuneLine = 1;
            bit bIVSProduceByBE = ScalerDrrIVSProduceByBE(SysRegionGetSourceType(enumDisplayRegion), SysRegionGetInputPort(enumDisplayRegion));

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
            // E/O mode, IVst fine tune line = 2 line
            if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
            {
                ucVstartFineTuneLine = 2;
            }
#endif

            if((bIVSProduceByBE == _TRUE) &&
               (ScalerMeasureGetHwAutoPhaseEnable(enumInputDataPath) == _DISABLE) &&
               (pstImageRegion->usImageVStart >= ucVstartFineTuneLine))
            {
                pstImageRegion->usImageVStart -= ucVstartFineTuneLine;
            }
#endif
        }
    }

    return bMeasurePass;
}
#endif

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserCommonDisplayAdjustOverScan(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucDelta = 0;

    if(UserInterfaceDisplayGetOverScanStatus(enumDisplayRegion) == _OVERSCAN_FALSE)
    {
        return;
    }

    // Modify Over Scanned H
    ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_HWIDTH() * _OVERSCAN_H_RATIO / 1000);

    // Let Adjusted Value be 2's multiple
    ucDelta += ucDelta % 2;

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    if(ScalerFmtCnvEagleSightEffectStatus(GET_MDOMAIN_INPUT_DATA_PATH()) != _FC_EAGLE_SIGHT_ENABLE)
#endif
    {
        SET_MDOMAIN_INPUT_HSTART(GET_MDOMAIN_INPUT_HSTART() + ucDelta);
    }

    SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() - 2 * ucDelta);

    // Modify Over Scanned V
    ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * _OVERSCAN_V_RATIO / 1000);

    if(ScalerFmtCnvFtoPGetStatus(ScalerRegionGetInputDataPath(enumDisplayRegion)) == _TRUE)
    {
        // Let Adjusted Value be 2's multiple under E/O mode
        ucDelta += ucDelta % 2;
    }

    SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + ucDelta);
    SET_MDOMAIN_INPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() - 2 * ucDelta);
}
#endif  // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Display Timing For Aspect Ratio
// Input Value  : Current Display Timing and Input H/V
// Output Value : Modified Display Timing
//--------------------------------------------------
void UserCommonDisplayAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion)
{
    WORD usHRatio = 0x0000;
    WORD usVRatio = 0x0000;
    WORD usFixRatioHwidth = 0;
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    WORD usOriginalRatio = 0;
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    StructTimingDataInfo stDisplayTimingData;
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    // No aspect ratio allowed in rotation 90/270
    if(ScalerRotationCheckVerticalStatus() == _TRUE)
    {
        return;
    }
#endif


#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
    SET_ASPECT_RATIO_MIN_DVH(0);
#endif

    switch(UserInterfaceDisplayGetAspectRatioType(enumDisplayRegion))
    {
        case _ASPECT_RATIO_FULL:
        default:

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif
            break;

        case _ASPECT_RATIO_FIXED:

            // Get aspect ratio from user
            UserInterfaceDisplayGetAspectRatio(enumDisplayRegion, &usHRatio, &usVRatio);

            // Check user value
            if((usHRatio == 0) || (usVRatio == 0))
            {
                break;
            }

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif

            // Calculate H Width
            usFixRatioHwidth = (DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * usHRatio / usVRatio;

            // H Width Should be 4x
            usFixRatioHwidth &= 0xFFFC;

            if(abs(GET_MDOMAIN_OUTPUT_HWIDTH() - usFixRatioHwidth) <= 4)
            {
                usFixRatioHwidth = GET_MDOMAIN_OUTPUT_HWIDTH();
            }

            if(usFixRatioHwidth > GET_MDOMAIN_OUTPUT_HWIDTH())
            {
                // Calculate V Height
                PDATA_WORD(0) = (DWORD)GET_MDOMAIN_OUTPUT_HWIDTH() * usVRatio / usHRatio;

                // V Height Should be 4x
                PDATA_WORD(0) &= 0xFFFC;

                // Set V Start, V Height
                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + ((GET_MDOMAIN_OUTPUT_VHEIGHT() - PDATA_WORD(0)) / 2));
                SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(0));
            }
            else if(usFixRatioHwidth < GET_MDOMAIN_OUTPUT_HWIDTH())
            {
                // Calculate H Start
                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HSTART() + ((GET_MDOMAIN_OUTPUT_HWIDTH() - usFixRatioHwidth) / 2);

                // Set H Start, H Width
                SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(1));
                SET_MDOMAIN_OUTPUT_HWIDTH(usFixRatioHwidth);
            }

            break;

        case _ASPECT_RATIO_USER:

            // User defined adjust aspect ratio
            UserInterfaceDisplayAdjustAspectRatio(enumDisplayRegion);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
            SET_ASPECT_RATIO_MIN_DVH(UserInterfaceDisplayGetAspectRatioMinDVHeight());
#endif
            break;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _ASPECT_RATIO_ORIGIN:

            // get original ratio
            usOriginalRatio = UserInterfaceDisplayGetAspectRatioOriginalRatio(enumDisplayRegion);

            ScalerMDomainAspectOriginMode(_TRUE);

            stDisplayTimingData.usHstart = GET_MDOMAIN_OUTPUT_HSTART();
            stDisplayTimingData.usHwidth = GET_MDOMAIN_OUTPUT_HWIDTH();
            stDisplayTimingData.usVstart = GET_MDOMAIN_OUTPUT_VSTART();
            stDisplayTimingData.usVheight = GET_MDOMAIN_OUTPUT_VHEIGHT();

            // Consider Panel Height and Input Height
            if(GET_MDOMAIN_OUTPUT_VHEIGHT() > GET_MDOMAIN_INPUT_VHEIGHT())
            {
                // Double V height for interlaced timing
                if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE) &&
                   (GET_MDOMAIN_INPUT_HWIDTH() > (GET_MDOMAIN_INPUT_VHEIGHT() << 1)))
                {
                    // Check if output V height > (input V height x 2)
                    if(GET_MDOMAIN_OUTPUT_VHEIGHT() > (GET_MDOMAIN_INPUT_VHEIGHT() << 1))
                    {
                        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - (GET_MDOMAIN_INPUT_VHEIGHT() << 1);
                        stDisplayTimingData.usVheight = (GET_MDOMAIN_INPUT_VHEIGHT() << 1);
                    }
                    else
                    {
                        // Output V height unchanged
                        PDATA_WORD(0) = 0x00;
                    }
                }
                else
                {
                    PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT();
                    stDisplayTimingData.usVheight = GET_MDOMAIN_INPUT_VHEIGHT();
                }

                PDATA_WORD(0) &= 0xFFFC; // V start should be even
                stDisplayTimingData.usVstart = (GET_MDOMAIN_OUTPUT_VSTART() + (PDATA_WORD(0) / 2));
            }
            else if(GET_MDOMAIN_OUTPUT_VHEIGHT() == GET_MDOMAIN_INPUT_VHEIGHT())
            {
                usVRatio = 0x01;
            }
            else
            {
                usVRatio = 0x02;
            }

            // Consider Panel Width and Input Width
            if(GET_MDOMAIN_OUTPUT_HWIDTH() > GET_MDOMAIN_INPUT_HWIDTH())
            {
                PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HWIDTH() - GET_MDOMAIN_INPUT_HWIDTH();
                PDATA_WORD(0) &= 0xFFFC; // H start should be even
                stDisplayTimingData.usHstart = (GET_MDOMAIN_OUTPUT_HSTART() + (PDATA_WORD(0) / 2));
                stDisplayTimingData.usHwidth = (GET_MDOMAIN_INPUT_HWIDTH());
            }
            else if(GET_MDOMAIN_OUTPUT_HWIDTH() == GET_MDOMAIN_INPUT_HWIDTH())
            {
                usHRatio = 0x01;
            }
            else
            {
                usHRatio = 0x02;
            }
            // Original
            if(usOriginalRatio == 0xFF)
            {
                SET_MDOMAIN_OUTPUT_VSTART(stDisplayTimingData.usVstart);
                SET_MDOMAIN_OUTPUT_VHEIGHT(stDisplayTimingData.usVheight);

                SET_MDOMAIN_OUTPUT_HSTART(stDisplayTimingData.usHstart);
                SET_MDOMAIN_OUTPUT_HWIDTH(stDisplayTimingData.usHwidth);
            }
            // Enlarge
            else if(usOriginalRatio > 0xFF)
            {
                StructHVBActiveDiff stHVBActiveDiff = {0};

                ScalerDDomainGetHVBActiveDiff(enumDisplayRegion, &stHVBActiveDiff);

                if(usVRatio == 0)
                {
                    WORD usVBHeight = GET_MDOMAIN_OUTPUT_VBHEIGHT();

                    if(stHVBActiveDiff.b1VBHeightDiff == _TRUE)
                    {
                        usVBHeight /= 2;
                    }

                    PDATA_WORD(1) = ((DWORD)stDisplayTimingData.usVheight * usOriginalRatio / 0xFF) - stDisplayTimingData.usVheight;
                    PDATA_WORD(1) &= 0xFFFC; // V start should be even

                    // Enlarge Vertical
                    if(PDATA_WORD(1) != 0)
                    {
                        // Display size should be less than Background active size
                        if((stDisplayTimingData.usVheight + PDATA_WORD(1)) < usVBHeight)
                        {
                            if(stDisplayTimingData.usVstart > PDATA_WORD(1) / 2)
                            {
                                SET_MDOMAIN_OUTPUT_VSTART(stDisplayTimingData.usVstart - PDATA_WORD(1) / 2);
                                SET_MDOMAIN_OUTPUT_VHEIGHT(stDisplayTimingData.usVheight + PDATA_WORD(1));
                            }
                            else
                            {
                                // MDOMAIN_OUTPUT_VSTART should't be less than _PANEL_DV_START
                                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART());
                                SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT());
                            }
                        }
                        else
                        {
                            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() - (usVBHeight - GET_MDOMAIN_OUTPUT_VHEIGHT()) / 2);
                            SET_MDOMAIN_OUTPUT_VHEIGHT(usVBHeight);
                        }
                    }
                }

                if(usHRatio == 0)
                {
                    WORD usHBWidth = GET_MDOMAIN_OUTPUT_HBWIDTH();

                    if(stHVBActiveDiff.b1HBWidthDiff == _TRUE)
                    {
                        usHBWidth = GET_MDOMAIN_OUTPUT_HWIDTH();
                    }

                    PDATA_WORD(1) = ((DWORD)stDisplayTimingData.usHwidth * usOriginalRatio / 0xFF) - stDisplayTimingData.usHwidth;
                    PDATA_WORD(1) &= 0xFFFC; // H start should be even

                    // Enlarge Horizontal
                    if(PDATA_WORD(1) != 0)
                    {
                        // Display size should be less than Background active size
                        if((stDisplayTimingData.usHwidth + PDATA_WORD(1)) < usHBWidth)
                        {
                            if(stDisplayTimingData.usHstart > PDATA_WORD(1) / 2)
                            {
                                SET_MDOMAIN_OUTPUT_HSTART(stDisplayTimingData.usHstart - PDATA_WORD(1) / 2);
                                SET_MDOMAIN_OUTPUT_HWIDTH(stDisplayTimingData.usHwidth + PDATA_WORD(1));
                            }
                            else
                            {
                                // MDOMAIN_OUTPUT_HSTART should't be less than _PANEL_DH_START
                                SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART());
                                SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH());
                            }
                        }
                        else
                        {
                            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() - (usHBWidth - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2);
                            SET_MDOMAIN_OUTPUT_HWIDTH(usHBWidth);
                        }
                    }
                }
            }

            // Reduce
            else if(usOriginalRatio < 0xFF)
            {
                // Vertical
                PDATA_WORD(1) = stDisplayTimingData.usVheight - ((DWORD)stDisplayTimingData.usVheight * usOriginalRatio / 0xFF);
                PDATA_WORD(1) &= 0xFFFC; // V start should be even

                // Reduce Vertical
                if(PDATA_WORD(1) != 0)
                {
                    // Add NO Support Check
                    if(GET_MDOMAIN_INPUT_VHEIGHT() / _HW_VSD_MAX_RATIO < ((DWORD)stDisplayTimingData.usVheight - PDATA_WORD(1)))
                    {
                        SET_MDOMAIN_OUTPUT_VSTART(stDisplayTimingData.usVstart + PDATA_WORD(1) / 2);
                        SET_MDOMAIN_OUTPUT_VHEIGHT(stDisplayTimingData.usVheight - PDATA_WORD(1));
                    }
                    else
                    {
                        DebugMessageMemory("Exceed Minimum Limit", usOriginalRatio);

                        // GET_MDOMAIN_OUTPUT_VHEIGHT() = GET_MDOMAIN_INPUT_VHEIGHT() / _HW_VSD_MAX_RATIO
                        PDATA_WORD(1) = stDisplayTimingData.usVheight - GET_MDOMAIN_INPUT_VHEIGHT() / _HW_VSD_MAX_RATIO;
                        PDATA_WORD(1) &= 0xFFFC; // V start should be even

                        SET_MDOMAIN_OUTPUT_VSTART(stDisplayTimingData.usVstart + PDATA_WORD(1) / 2);
                        SET_MDOMAIN_OUTPUT_VHEIGHT(stDisplayTimingData.usVheight - PDATA_WORD(1));
                    }
                }
                // Horizontal
                PDATA_WORD(1) = stDisplayTimingData.usHwidth - ((DWORD)stDisplayTimingData.usHwidth * usOriginalRatio / 0xFF);
                PDATA_WORD(1) &= 0xFFFC; // H start should be even

                // Reduce  Horizontal
                if(PDATA_WORD(1) != 0)
                {
                    // Add NO Support Check
                    if(GET_MDOMAIN_INPUT_HWIDTH() / _HW_HSD_MAX_RATIO < ((DWORD)stDisplayTimingData.usHwidth - PDATA_WORD(1)))
                    {
                        SET_MDOMAIN_OUTPUT_HSTART(stDisplayTimingData.usHstart + PDATA_WORD(1) / 2);
                        SET_MDOMAIN_OUTPUT_HWIDTH(stDisplayTimingData.usHwidth - PDATA_WORD(1));
                    }
                    else
                    {
                        DebugMessageMemory("Exceed Minimum Limit", usOriginalRatio);

                        // GET_MDOMAIN_OUTPUT_HWIDTH() = GET_MDOMAIN_INPUT_HWIDTH() / _HW_HSD_MAX_RATIO
                        PDATA_WORD(1) = stDisplayTimingData.usHwidth - GET_MDOMAIN_INPUT_HWIDTH() / _HW_HSD_MAX_RATIO;
                        PDATA_WORD(1) &= 0xFFFC; // H start should be even

                        SET_MDOMAIN_OUTPUT_HSTART(stDisplayTimingData.usHstart + PDATA_WORD(1) / 2);
                        SET_MDOMAIN_OUTPUT_HWIDTH(stDisplayTimingData.usHwidth - PDATA_WORD(1));
                    }
                }
            }

            break;
#endif // End of #if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    }
}
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
//--------------------------------------------------
// Description  : Adjust input size for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayAdjustRotationInputSize(void)
{
    if(ScalerRotationCheckVerticalStatus() == _FALSE)
    {
        return;
    }

    switch(GET_ROT_DISP_SIZE())
    {
        case _ROT_PIXEL_BY_PIXEL:

            // Calculate / Set V
            if(_PANEL_DH_WIDTH < GET_INPUT_TIMING_VHEIGHT())
            {
                PDATA_WORD(0) = ((GET_INPUT_TIMING_VHEIGHT() - _PANEL_DH_WIDTH) / 2);
                PDATA_WORD(0) += GET_INPUT_TIMING_VSTART();

                // VStart / VHeight
                SET_MDOMAIN_INPUT_VSTART(PDATA_WORD(0));
                SET_MDOMAIN_INPUT_VHEIGHT(_PANEL_DH_WIDTH);
            }

            // Calculate / Set H
            if(_PANEL_DV_HEIGHT < GET_INPUT_TIMING_HWIDTH())
            {
                PDATA_WORD(0) = (GET_INPUT_TIMING_HWIDTH() - _PANEL_DV_HEIGHT);
                PDATA_WORD(0) += GET_INPUT_TIMING_HSTART();
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);

                // HStart / HWidth
                SET_MDOMAIN_INPUT_HSTART(PDATA_WORD(0));
                SET_MDOMAIN_INPUT_HWIDTH(_PANEL_DV_HEIGHT);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Adjust display size for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayAdjustRotationDisplaySize(void)
{
    if(ScalerRotationCheckVerticalStatus() == _FALSE)
    {
        return;
    }

    switch(GET_ROT_DISP_SIZE())
    {
        default:
        case _ROT_FULL:

            // Set Size
            SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
            SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);

            break;

        case _ROT_PIXEL_BY_PIXEL:

            PDATA_WORD(0) = _PANEL_DH_START;
            PDATA_WORD(1) = _PANEL_DH_WIDTH;
            PDATA_WORD(2) = _PANEL_DV_START;
            PDATA_WORD(3) = _PANEL_DV_HEIGHT;

            // Calculate / Set Display Window H
            if(_PANEL_DH_WIDTH > GET_MDOMAIN_INPUT_VHEIGHT())
            {
                // Underscan
                PDATA_WORD(0) += ((_PANEL_DH_WIDTH - GET_MDOMAIN_INPUT_VHEIGHT()) / 2);
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT();
            }

            // Calculate / Set Display Window V Start
            if(_PANEL_DV_HEIGHT > GET_MDOMAIN_INPUT_HWIDTH())
            {
                // Underscan
                PDATA_WORD(2) += ((_PANEL_DV_HEIGHT - GET_MDOMAIN_INPUT_HWIDTH()) / 2);
                PDATA_WORD(3) = GET_MDOMAIN_INPUT_HWIDTH();
            }

            // Set Display Window H Start/Width
            SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(0));
            SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(1));

            // Set Display Window V Start/Height
            SET_MDOMAIN_OUTPUT_VSTART(PDATA_WORD(2));
            SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(3));

            break;

        case _ROT_KEEP_SRC_ASPECT_RATIO:

            if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE) &&
               (GET_MDOMAIN_INPUT_VHEIGHT() < (GET_MDOMAIN_INPUT_HWIDTH() / 2)))
            {
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT() * 2;
            }
            else
            {
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT();
            }

            // Calculate VHeight
            PDATA_WORD(0) = ((DWORD)_PANEL_DH_WIDTH * GET_MDOMAIN_INPUT_HWIDTH()) / PDATA_WORD(1);

            if(PDATA_WORD(0) > _PANEL_DV_HEIGHT)
            {
                // Calculate HWidth
                PDATA_WORD(0) = ((DWORD)_PANEL_DV_HEIGHT * PDATA_WORD(1)) / GET_MDOMAIN_INPUT_HWIDTH();

                // Set HWidth / VHeight
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(0));
                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);

                // HStart / VStart
                PDATA_WORD(0) = (_PANEL_DH_START + (_PANEL_DH_WIDTH - PDATA_WORD(0)) / 2);
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(0));
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            }
            else
            {
                // HWidth / VHeight
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(0));

                // HStart / VStart
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                SET_MDOMAIN_OUTPUT_VSTART((_PANEL_DV_START + (_PANEL_DV_HEIGHT - PDATA_WORD(0)) / 2));
            }

            break;
    }
}
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common function Get PIP/PBP Sub Background
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
void UserCommonDisplayGetPbplrRightBackground(StructTimingFormat *pstTimingFormat)
{
    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            ScalerMDomainGetBackground_R2(pstTimingFormat);
#endif
            break;
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                // RL6952, RL6829 FB
                pstTimingFormat->usHStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_END);
                pstTimingFormat->usHWidth = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END) - pstTimingFormat->usHStart;
                pstTimingFormat->usVStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);
                pstTimingFormat->usVHeight = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT);
            }
            else
            {
                ScalerMDomainGetBackground_R2(pstTimingFormat);
            }
#endif

            break;
        default:
            break;
    }
}
#endif

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
//--------------------------------------------------
// Description  : User Common function Get PIP/PBP Sub Background
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
void UserCommonDisplayGetPipSubBackground(StructTimingFormat *pstTimingFormat)
{
    switch(GET_DISPLAY_MODE())
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            ScalerMDomainGetBackground_R2(pstTimingFormat);
#endif
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
            ScalerMDomainGetBackground_R2(pstTimingFormat);
#endif
            break;
#endif
        default:
            break;
    }
}
//--------------------------------------------------
// Description  : User Common function Get PIP/PBP Sub ActiveTiming
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
void UserCommonDisplayGetPipSubActiveTiming(StructTimingFormat *pstTimingFormat)
{
    switch(GET_DISPLAY_MODE())
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            ScalerMDomainGetActiveRegion_R2a1(pstTimingFormat);
#endif
#endif
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            ScalerMDomainGetActiveRegion_R2a1(pstTimingFormat);
#endif
#endif
            break;
#endif
        default:
            break;
    }
}
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common function Get 3P Flag Main Region Background
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
void UserCommonDisplayGet3PFlagMainRegionBackground(StructTimingFormat *pstTimingFormat)
{
#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
    ScalerMDomainGetBackground_R3(pstTimingFormat);
#endif
}
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust PIP sub position & size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayPipSubTimingFormatAdjust(void)
{
#if(_2P_PIP_SUB_DISP_POSITION_ADJ_FAST_MODE == _ON)
    bit bPIPAdjustFast = _TRUE;
#endif

    StructTimingFormat stTimingFormat = {0};
    UserInterfaceDisplayGetPipSubTimingFormat(&stTimingFormat);

    // Set output timing info according to user-defined resolution
    SET_MDOMAIN_OUTPUT_HTOTAL(_PANEL_DH_TOTAL);
    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);

    SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
    SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);
    SET_MDOMAIN_OUTPUT_HBWIDTH(stTimingFormat.usHWidth);
    SET_MDOMAIN_OUTPUT_VBHEIGHT(stTimingFormat.usVHeight);

    SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
    SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
    SET_MDOMAIN_OUTPUT_HBSTART(stTimingFormat.usHStart);
    SET_MDOMAIN_OUTPUT_VBSTART(stTimingFormat.usVStart);

#if(_PANEL_ASYMMETRIC == _ON)
    SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT);
    SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP);
#endif

    // Check resoultion constraint
    ScalerMDomainCheckDisplayFormat(_DISPLAY_RGN_PIP_SUB);

    if((SysRegionGetDisplayState(_DISPLAY_RGN_PIP_SUB) == _DISPLAY_STATE_ACTIVE) ||
       (SysRegionGetDisplayState(_DISPLAY_RGN_PIP_SUB) == _DISPLAY_STATE_DISPLAY_READY))
    {
        EnumPIPSubAdjustMute enumPIPSubAdjustMute = UserInterfaceDisplayPIPSubAdjustMute();

        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_1, _DB_APPLY_POLLING);

        if(enumPIPSubAdjustMute == _PIP_SUB_ADJUST_MUTE)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            ScalerDDomainBackgroundSetColor(_DDOMAIN_RGN_R2_A1, 0, 0, 0, _DB_APPLY_POLLING);
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_R2_A1, _ENABLE);

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            ScalerMDomainSetActiveRegion_R2a1();
#endif
        }
        else
        {
#if(_ASPECT_RATIO_SUPPORT == _ON)
            // Calculate PIP sub active size
            UserCommonDisplayAdjustAspectRatio(_DISPLAY_RGN_PIP_SUB);
#endif

            ScalerMDomainCheckDisplayFormat(_DISPLAY_RGN_PIP_SUB);

#if(_2P_PIP_SUB_DISP_POSITION_ADJ_FAST_MODE == _ON)
            {
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
                WORD usHwidth = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);
                WORD usVheight = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_HEIGHT);

                // _PIP_SUB_ADJUST_POSITION_WITHOUT_MUTE_FAST only support when adjust PIP sub display position, not support PIP sub size adjust
                if((GET_MDOMAIN_OUTPUT_HWIDTH() != usHwidth) || (GET_MDOMAIN_OUTPUT_VHEIGHT() != usVheight))
                {
                    bPIPAdjustFast = _FALSE;
                    DebugMessageScaler("_PIP_SUB_ADJUST_POSITION_WITHOUT_MUTE_FAST only support when PIP sub display position adjust !!!", bPIPAdjustFast);
                }
#endif
            }

            if(bPIPAdjustFast == _TRUE)
            {
#if(_FRC_SUPPORT == _ON)
                // FRC pre-read
                ScalerFRCSetPreRead(ScalerRegionGetInputDataPath(_DISPLAY_RGN_PIP_SUB));
#endif
            }
#endif

            // Update active size
            // Set Sub Region : R2a1
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
            ScalerMDomainSetActiveRegion_R2a1();
#endif

            // Set D-domain background size to active size
            SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH());
            SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HSTART());
            SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT());
            SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());
        }

        // Update M-domain back ground timing format
        // Set Sub Region
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
        ScalerMDomainSetBackground_R2();
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
        // Update border position
        {
            StructColorBorderWindowSetting stBorderWindow = {0};

            UserCommonColorGetBorderWindowData(&stBorderWindow);
            ScalerColorIPBorderWindowAdjust(&stBorderWindow, _DB_APPLY_NONE);
        }
#endif

#if(_COLOR_IP_HL_WIN == _ON)
        // Update HLW position
        {
            StructColorHLWSetting stHLW = {0};

            UserCommonColorGetHLWData(&stHLW);
            ScalerColorIPHLWAdjust(&stHLW, _DB_APPLY_NONE);
        }
#endif

        if(enumPIPSubAdjustMute == _PIP_SUB_ADJUST_MUTE)
        {
            // Reset to display setting
            SysModeSetDisplayTarget(_DISPLAY_RGN_PIP_SUB);
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
        }
        else
        {
#if(_2P_PIP_SUB_DISP_POSITION_ADJ_FAST_MODE == _ON)
            if(bPIPAdjustFast == _TRUE)
            {
                // Apply D-domain DB
                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_1, _DB_APPLY_POLLING);
            }
            else
#endif
            {
                // Reset to display setting
                SysModeSetDisplayTarget(_DISPLAY_RGN_PIP_SUB);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
            }
        }
    }
    else
    {
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
        EnumDBEnableStatus enumDBBackup = ScalerGlobalGetDBStatus(_HW_SUB_REGION_INPUT_PATH);

        // Disable Global Double Buffer, Only Enable D Domain DB
        ScalerGlobalResetDoubleBuffer(_HW_SUB_REGION_INPUT_PATH, enumDBBackup, _DISABLE);
#endif

        // Update active size
        // Set Sub Region : R2a1
#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        ScalerMDomainSetActiveRegion_R2a1();
#endif

        // Update M-domain back ground timing format
        // Set Sub Region
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
        ScalerMDomainSetBackground_R2();
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
        // Update border position
        {
            StructColorBorderWindowSetting stBorderWindow = {0};

            UserCommonColorGetBorderWindowData(&stBorderWindow);
            ScalerColorIPBorderWindowAdjust(&stBorderWindow, _DB_APPLY_NONE);
        }
#endif

#if(_COLOR_IP_HL_WIN == _ON)
        // Update HLW position
        {
            StructColorHLWSetting stHLW = {0};

            UserCommonColorGetHLWData(&stHLW);
            ScalerColorIPHLWAdjust(&stHLW, _DB_APPLY_NONE);
        }
#endif

        // Apply D-domain DB
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_1, _DB_APPLY_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
        // Restore settings
        ScalerGlobalResetDoubleBuffer(_HW_SUB_REGION_INPUT_PATH, enumDBBackup, _ENABLE);
#endif
    }
}
#endif

//--------------------------------------------------
// Description  : Get user data related to MDomain
// Input Value  : StructDisplayCustomizedData *pstDisplayCustomizedData
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayGetMDomainCustomInfo(StructDisplayCustomizedData *pstDisplayCustomizedData)
{
    StructDisplayCustomizedData stUserSetting = {0};

    pstDisplayCustomizedData->structCustomizedMdomain.enumMemoryBitSelect = _MEMORY_REF_SOURCE_BIT;
    pstDisplayCustomizedData->structCustomizedMdomain.enumBWCustomeModeType = _BW_DEFAULT_TYPE;

#if(_FRC_SUPPORT == _ON)
    pstDisplayCustomizedData->structDVCustomizedFreq.b1FORCETOFREERUN = _DISABLE;
    pstDisplayCustomizedData->structDVCustomizedFreq.b1DecideMemoryConfig = _MEMORY_CONFIG_AUTO_MODE;

    pstDisplayCustomizedData->structDVCustomizedFreq.usTypFreq = ((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) ? _PANEL_TYP_FRAME_RATE : _MTP_MAIN_PREFER_TIMING_FRAME_RATE);

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(SysRegionGetInputPort(GET_MODE_DISPLAY_TARGET_REGION())) != _DRR_NONE_TYPE)
    {
        pstDisplayCustomizedData->structDVCustomizedFreq.usMaxFreq = GET_DRR_PANEL_MAX_FRAME_RATE();
        pstDisplayCustomizedData->structDVCustomizedFreq.usMinFreq = GET_DRR_PANEL_MIN_FRAME_RATE();
    }
    else
#endif
    {
        pstDisplayCustomizedData->structDVCustomizedFreq.usMaxFreq = _PANEL_MAX_FRAME_RATE;
        pstDisplayCustomizedData->structDVCustomizedFreq.usMinFreq = _PANEL_MIN_FRAME_RATE;
    }

    pstDisplayCustomizedData->structDVCustomizedFreq.ulPanelClockTypical = _PANEL_PIXEL_CLOCK_KHZ;
    pstDisplayCustomizedData->structDVCustomizedFreq.ulPanelClockMaxSpread = _PANEL_PIXEL_CLOCK_MAX_SPREAD;
    pstDisplayCustomizedData->structDVCustomizedFreq.ulPanelClockMinSpread = _PANEL_PIXEL_CLOCK_MIN_SPREAD;
#endif

    memcpy(&stUserSetting, pstDisplayCustomizedData, sizeof(stUserSetting));

    if(GET_MODE_DISPLAY_TARGET_INDEX() == _REGION_INDEX_0)
    {
        UserInterfaceDisplaySelectMDomainSettingForMain(&stUserSetting.structCustomizedMdomain);
    }
#if(_MULTI_DISPLAY_MAX > 0x01)
    else
    {
        UserInterfaceDisplaySelectMDomainSettingForSub(&stUserSetting.structCustomizedMdomain);
    }
#endif

#if(_BW_CUSTOME_MODE == _ENABLE)
    pstDisplayCustomizedData->structCustomizedMdomain.enumMemoryBitSelect = stUserSetting.structCustomizedMdomain.enumMemoryBitSelect;
    pstDisplayCustomizedData->structCustomizedMdomain.enumBWCustomeModeType = stUserSetting.structCustomizedMdomain.enumBWCustomeModeType;
#endif

#if(_FRC_SUPPORT == _ON)
    UserInterfaceDisplayGetDVMaxMinFreq(&stUserSetting.structDVCustomizedFreq);

#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
    pstDisplayCustomizedData->structDVCustomizedFreq.b1FORCETOFREERUN = _ENABLE;
#else
    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        pstDisplayCustomizedData->structDVCustomizedFreq.b1FORCETOFREERUN = stUserSetting.structDVCustomizedFreq.b1FORCETOFREERUN;
    }
#endif

    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        pstDisplayCustomizedData->structDVCustomizedFreq.b1DecideMemoryConfig = stUserSetting.structDVCustomizedFreq.b1DecideMemoryConfig;
        pstDisplayCustomizedData->structDVCustomizedFreq.usMaxFreq = stUserSetting.structDVCustomizedFreq.usMaxFreq;
        pstDisplayCustomizedData->structDVCustomizedFreq.usTypFreq = stUserSetting.structDVCustomizedFreq.usTypFreq;
        pstDisplayCustomizedData->structDVCustomizedFreq.usMinFreq = stUserSetting.structDVCustomizedFreq.usMinFreq;

        pstDisplayCustomizedData->structDVCustomizedFreq.ulPanelClockTypical = stUserSetting.structDVCustomizedFreq.ulPanelClockTypical;
        pstDisplayCustomizedData->structDVCustomizedFreq.ulPanelClockMaxSpread = stUserSetting.structDVCustomizedFreq.ulPanelClockMaxSpread;
        pstDisplayCustomizedData->structDVCustomizedFreq.ulPanelClockMinSpread = stUserSetting.structDVCustomizedFreq.ulPanelClockMinSpread;
    }
#endif
}

//--------------------------------------------------
// Description  : Set DVCustomized Panel Default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplaySetDVCustomizedDefault(void)
{
#if(_FRC_SUPPORT == _ON)
    g_stDisplayCustomizedData.structDVCustomizedFreq.b1FORCETOFREERUN = _DISABLE;
    g_stDisplayCustomizedData.structDVCustomizedFreq.b1DecideMemoryConfig = _MEMORY_CONFIG_AUTO_MODE;
    g_stDisplayCustomizedData.structDVCustomizedFreq.usMaxFreq = _PANEL_MAX_FRAME_RATE;
    g_stDisplayCustomizedData.structDVCustomizedFreq.usTypFreq = _PANEL_TYP_FRAME_RATE;
    g_stDisplayCustomizedData.structDVCustomizedFreq.usMinFreq = _PANEL_MIN_FRAME_RATE;

    g_stDisplayCustomizedData.structDVCustomizedFreq.ulPanelClockTypical = _PANEL_PIXEL_CLOCK_KHZ;
    g_stDisplayCustomizedData.structDVCustomizedFreq.ulPanelClockMaxSpread = _PANEL_PIXEL_CLOCK_MAX_SPREAD;
    g_stDisplayCustomizedData.structDVCustomizedFreq.ulPanelClockMinSpread = _PANEL_PIXEL_CLOCK_MIN_SPREAD;
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
    SET_FREE_RUN_DDOMAIN_SETTING(_DEFAULT_FREERUN_DDOMAIN_SETTING);
#endif

    g_stDisplayCustomizedData.structCustomizedMdomain.enumMemoryBitSelect = _MEMORY_REF_SOURCE_BIT;
    g_stDisplayCustomizedData.structCustomizedMdomain.enumBWCustomeModeType = _BW_DEFAULT_TYPE;
}

#if(_FRAME_RATE_SLOW_DOWN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Slow Down Display frame rate
// Input Value  : ON --> enable VGIP safe mode
// Output Value : None
//--------------------------------------------------
void UserCommonDisplaySetDropIVFAction(EnumDropIVFAction enumDropIVFAction)
{
    EnumDisplayMode enumDisplayMode = SysModeGetDisplayMode();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if(enumDisplayMode != _DISPLAY_MODE_1P)
    {
        return;
    }

    if(SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE)
    {
        StructTimingInfo stTimingInfo;
        memset(&stTimingInfo, 0x00, sizeof(stTimingInfo));

        // Read timing info
        SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(_REGION_INDEX_0), &stTimingInfo);

        if(stTimingInfo.b1Interlace == _TRUE)
        {
            return;
        }

        ScalerVgipSafeModeEnable(enumDropIVFAction, stTimingInfo.enumInputDataPath);
    }
}

//--------------------------------------------------
// Description  : Get Drop IVF Action
// Input Value  : enumVgipInputPath
// Output Value : _true if _DROP_IVF_ENABLE
//--------------------------------------------------
bit UserCommonDisplayGetDropIVFAction(EnumInputDataPath enumVgipInputPath)
{
    return ScalerVgipGetSafeModeStatus(enumVgipInputPath);
}
#endif

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display freeze
// Input Value  : ON --> Display freeze
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayFreeze(bit bEn)
{
    ScalerFRCFixSlowSideBlkSel(GET_MDOMAIN_INPUT_DATA_PATH(), bEn);
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)


#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Drr mode Get IVFmax from table
// Input Value  : enumInputPort
// Output Value : _TABLE_SEARCHING_WITH_IVF_MAX: Get IVF, unit: 0.1Hz
//--------------------------------------------------
EnumGetIVFFromTableSearch UserCommonDisplayDrrGetIVFmax(WORD *pusVfreqMax, EnumInputPort enumInputPort)
{
    WORD usVfreqMax = 0;

    switch(SysSourceGetPortTypeFromInputPort(enumInputPort))
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        case _PORT_DP:

            if(UserInterfaceDisplayDpFreeSyncGetIVFmaxFromLut(&usVfreqMax) == _DP_FREESYNC_WITH_IVF_MAX)
            {
                *pusVfreqMax = usVfreqMax;
                return _TABLE_SEARCHING_WITH_IVF_MAX;
            }

            break;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
        case _PORT_HDMI:
        case _PORT_DVI:
            switch(ScalerDrrGetType(enumInputPort))
            {
#if(_HDMI_FREESYNC_SUPPORT == _ON)
                case _DRR_FREESYNC_TYPE:
                    if(UserInterfaceDisplayHdmiFreeSyncGetIVFmaxFromLut(&usVfreqMax) == _HDMI_FREESYNC_WITH_IVF_MAX)
                    {
                        *pusVfreqMax = usVfreqMax;
                        return _TABLE_SEARCHING_WITH_IVF_MAX;
                    }
                    break;

#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
                case _DRR_HDMI21_VRR_TYPE:
                    if(UserInterfaceDisplayHdmiVrrGetIVFmaxFromLut(&usVfreqMax) == _HDMI21_VRR_WITH_IVF_MAX)
                    {
                        *pusVfreqMax = usVfreqMax;
                        return _TABLE_SEARCHING_WITH_IVF_MAX;
                    }
                    break;

#endif
                default:
                    break;
            }

            break;
#endif

        default:

            *pusVfreqMax = usVfreqMax;
            break;
    }

    return _TABLE_SEARCHING_WITHOUT_IVF_MAX;
}
#endif

#if(_DRR_SUPPORT == _ON)
#if(_SEARCH_DRR_IVF_PRIORITY_BY_USER == _ON)
//--------------------------------------------------
// Description  : Get DRR IVF Priority From User or Kernel
// Input Value  : Input port/ IVFreq
// Output Value : _DRR_GET_IVF_PRIORITY_USER: from user
//--------------------------------------------------
EnumDrrGetIVFPriority UserCommonDisplayGetDrrIVFPriority(EnumInputPort enumInputPort, WORD *pusIVfreq)
{
    WORD usVfreqMax = 0;

    if(ScalerDrrReceiveSourceIVF(enumInputPort, SysSourceGetPortTypeFromInputPort(enumInputPort), &usVfreqMax) == _TRUE)
    {
        DebugMessageScaler("DRR Get IVF from Source info", GET_DRR_VFREQ_MAX());
    }

    if(UserInterfaceDisplayGetDrrIVFByUser(enumInputPort, &usVfreqMax) == _DRR_GET_IVF_PRIORITY_USER)
    {
        *pusIVfreq = usVfreqMax;
        return _DRR_GET_IVF_PRIORITY_USER;
    }

    return _DRR_GET_IVF_PRIORITY_KERNEL;
}
#endif
#endif

//--------------------------------------------------
// Description  : Adjust DPLL Spread Spectrum
// Input Value  : Spread Spectrum Range
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange)
{
    ScalerPLLSetDPLLSSC(ucDclkSpreadSpeed, ucSpreadRange);
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayGlobalDDomainDBApply(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    EnumDDomainDBApplyRegion enumDDomainDBApplyRegion = ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion(enumSelRegion);

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(ScalerColorPCMInputGammaGetHLWDBEventSel() == _PCM_HLW_DB_GLOBAL_IMD)
    {
        ScalerColorPCMHLWDBApply(enumDBApply, _PCM_HLW_DB_A_OR_B);
    }
#endif

    ScalerGlobalDDomainDBApply(enumDDomainDBApplyRegion, enumDBApply);
}

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayGlobalIDomainDBApply(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    ScalerGlobalIDomainDBApply(ScalerRegionGetInputDataPath(enumDisplayRegion), enumDBApply);
}
#endif
#endif

//--------------------------------------------------
// Description  : Enabel Global Watch Dog by Region
// Input Value  : enumDisplayRegion --> system select region
//                bEnable -->_ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonRegionSetWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    ScalerRegionSetWatchDog(enumDisplayRegion, bEnable);
}

//--------------------------------------------------
// Description  : Get input data path for select region
// Input Value  : enumSelRegion --> select region
// Output Value : Scaler Data Path
//--------------------------------------------------
EnumDDomainRegion UserCommonRegionGetDDomainRegion(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerRegionGetDDomainRegion(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Get Inverse SelRegion from SelRegion
// Input Value  : EnumSelRegion
// Output Value : EnumSelRegion
//--------------------------------------------------
EnumSelRegion UserCommonRegionGetInverse(EnumSelRegion enumSelRegion)
{
    return ScalerRegionGetInverse(enumSelRegion);
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get front/back mode support; Certain display mode and function should be disabled when returning _TRUE.
// Input Value  : N/A
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit UserCommonRegionGetFrontBackModeSupport(void)
{
    return ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH);
}
#endif

//--------------------------------------------------
// Description  : Convert display region to region index
// Input Value  : enumDisplayRegion --> target region
// Output Value : region index (0 ~ 3) or _REGION_INDEX_NONE
//--------------------------------------------------
EnumRegionIndex UserCommonRegionGetIndex(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerRegionGetIndex(enumDisplayRegion);
}


//--------------------------------------------------
// Description  : Get input data path for select region
// Input Value  : enumSelRegion --> select region
// Output Value : Scaler Data Path
//--------------------------------------------------
EnumInputDataPath UserCommonRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerRegionGetInputDataPath(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Reset input data path process
// Input Value  : enumVgipInputPath --> target data path for reset
// Output Value : None
//--------------------------------------------------
void UserCommonIDomainResetDataPath(EnumInputDataPath enumVgipInputPath)
{
    EnumDBEnableStatus enumDBBackup = ScalerGlobalGetDBStatus(enumVgipInputPath);

    // Disable Global Double Buffer, Only Enable D Domain DB
    ScalerGlobalResetDoubleBuffer(enumVgipInputPath, enumDBBackup, _DISABLE);

    ScalerIDomainResetDataPath(enumVgipInputPath);

    // Restore Double Buffer Status
    ScalerGlobalResetDoubleBuffer(enumVgipInputPath, enumDBBackup, _ENABLE);
}

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable
// Input Value  :
// Output Value : None
//--------------------------------------------------
void UserCommonMDomainAspectOriginMode(bit bOn)
{
    ScalerMDomainAspectOriginMode(bOn);
}
#endif


#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Display Timgin Gen Background
// Input Value  : Timing data
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetEagleSightDisplayActive_Main(EnumDisplayFormatItem enumItem)
{
    return ScalerDDomainGetDisplayFormat_R1a1(enumItem);
}

//--------------------------------------------------
// Description  : Get display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD UserCommonDisplayGetEagleSightDisplayBackground_Main(EnumDisplayBackgroundItem enumItem)
{
    return ScalerDDomainGetDisplayBackground_R1(enumItem);
}

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Sub display format value for specified item
// Input Value  : enumItem --> target format item
// Output Value : display format value
//--------------------------------------------------
WORD UserCommonDisplayGetEagleSightDisplayBackground_Sub(EnumDisplayBackgroundItem enumItem)
{
    return ScalerDDomainGetDisplayBackground_R2(enumItem);
}
#endif
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
//--------------------------------------------------
// Description  : Set Display Timgin Gen Background
// Input Value  : Timing data
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetDisplayTimingGenBackground(EnumDisplayBackgroundItem enumItem, WORD usData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetDisplayBackground_R1(enumItem, usData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen Background
// Input Value  : Timing data
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetDisplayTimingGenBackground(EnumDisplayBackgroundItem enumItem)
{
    return ScalerDDomainGetDisplayBackground_R1(enumItem);
}
//--------------------------------------------------
// Description  : Set Display Timgin Gen Background
// Input Value  : Timing data
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetDisplayTimingGenActiveRegion(EnumDisplayFormatItem enumItem, WORD usData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetDisplayFormat_R1a1(enumItem, usData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen Background
// Input Value  : Timing data
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetDisplayTimingGenActiveRegion(EnumDisplayFormatItem enumItem)
{
    return ScalerDDomainGetDisplayFormat_R1a1(enumItem);
}

//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin Enable
// Input Value  : Enable
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetCaptureWindowEnable(bit bCapWinEnable, EnumDBApply enumDBApply)
{
    // Enable/Disable Capture Window
    ScalerDDomainSetCaptureWindowEnable(bCapWinEnable);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _ON)
    {
        // Enable/Disable Reference CW BG
        ScalerDDomainSetCaptureWindowRefBG(bCapWinEnable);

        // Enable/Disable Back Capture Window
        ScalerDDomainSetCaptureWindowEnable_Back(bCapWinEnable);
    }
#endif

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Set Capture Window Background
// Input Value  : EnumDisplayBackgroundItem, Timing data, EnumDBApply
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem, WORD usData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetCaptureWindowBackground(enumItem, usData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Capture Window Background
// Input Value  : EnumDisplayBackgroundItem
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem)
{
    return ScalerDDomainGetCaptureWindowBackground(enumItem);
}

//--------------------------------------------------
// Description  : Set Capture Window ActiveRegion
// Input Value  : EnumDisplayFormatItem, Timing data, EnumDBApply
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem, WORD usData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetCaptureWindowActiveRegion(enumItem, usData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Capture Window ActiveRegion
// Input Value  : EnumDisplayFormatItem
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem)
{
    return ScalerDDomainGetCaptureWindowActiveRegion(enumItem);
}
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Dspc Den Delay
// Input Value  : Dspc Den Delay
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetDspcDenDelay(BYTE ucData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetDspcDenDelay(ucData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Dspc Den Delay
// Input Value  : NA
// Output Value : Dspc Den Delay
//--------------------------------------------------
BYTE UserCommonDDomainGetDspcDenDelay(void)
{
    return ScalerDDomainGetDspcDenDelay();
}
//--------------------------------------------------
// Description  : Set DDomain Extension Extract Enable
// Input Value  : Enable
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetExtensionExtract(bit bEnable, EnumDBApply enumDBApply)
{
    ScalerDDomainSetExtensionExtract(bEnable);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
//--------------------------------------------------
// Description  : Set Capture Window Background
// Input Value  : EnumDisplayBackgroundItem, Timing data, EnumDBApply
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem, WORD usData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetCaptureWindowBackground_Back(enumItem, usData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Capture Window Background
// Input Value  : EnumDisplayBackgroundItem
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem)
{
    return ScalerDDomainGetCaptureWindowBackground_Back(enumItem);
}

//--------------------------------------------------
// Description  : Set Capture Window ActiveRegion
// Input Value  : EnumDisplayFormatItem, Timing data, EnumDBApply
// Output Value : NA
//--------------------------------------------------
void UserCommonDDomainSetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem, WORD usData, EnumDBApply enumDBApply)
{
    ScalerDDomainSetCaptureWindowActiveRegion_Back(enumItem, usData);
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Capture Window ActiveRegion
// Input Value  : EnumDisplayFormatItem
// Output Value : NA
//--------------------------------------------------
WORD UserCommonDDomainGetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem)
{
    return ScalerDDomainGetCaptureWindowActiveRegion_Back(enumItem);
}
//--------------------------------------------------
// Description  : Get DDomain Extension
// Input Value  : NA
// Output Value : DDomain Extension
//--------------------------------------------------
WORD UserCommonDDomainGetExtension(void)
{
    return ScalerDDomainGetExtension();
}
#endif
#endif

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
//--------------------------------------------------
// Description  : Get VGIP Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD UserCommonIDomainGetCaptureHStartPosition(void)
{
    return ScalerVgipGetCaptureHStartPosition();
}

//--------------------------------------------------
// Description  : Set VGIP Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void UserCommonIDomainSetCaptureHStartPosition(WORD usIHstart)
{
    ScalerVgipSetCaptureHStartPosition(usIHstart);
}

//--------------------------------------------------
// Description  : Get VGIP Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD UserCommonIDomainGetCaptureVDelay(void)
{
    return ScalerVgipGetCaptureVDelay();
}

//--------------------------------------------------
// Description  : Set VGIP Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void UserCommonIDomainSetCaptureVDelay(WORD usIVSDelay)
{
    ScalerVgipSetCaptureVDelay(usIVSDelay);
}

//--------------------------------------------------
// Description  : Set VGIP Capture Input Region
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void UserCommonIDomainSetCaptureInputRegion(EnumDisplayRegion enumDisplayRegion)
{
    ScalerVgipSetInputRegion(enumDisplayRegion);
}
#endif

#endif

//--------------------------------------------------
// Description  : Display Force to Background Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainBackgroundEnableByRegion(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    switch(enumDisplayRegion)
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:

            if(bEnable == _DISABLE)
            {
                if(SysRegionGetDisplayState(_DISPLAY_RGN_EAGLE_SIGHT_SUB) != _DISPLAY_STATE_ACTIVE)
                {
                    // Disable Sub
                    ScalerDDomainSetR2DenEnable(_DISABLE, _DB_APPLY_POLLING);
                }
            }
            else
            {
#if(_COLOR_IP_BORDER_WIN == _ON)
                UserCommonColorBorderWindowDisable(_DB_APPLY_NO_POLLING);
#endif
            }
            break;

        case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
            break;

#endif
        default:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PIP_MAIN:
        case _DISPLAY_RGN_PIP_SUB:
#endif
            break;
    }

    ScalerDDomainBackgroundEnableByRegion(enumDisplayRegion, bEnable);
}

//--------------------------------------------------
// Description  : Display Force to Background Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainBackgroundEnable(EnumDDomainRegion enumDDomainRegion, bit bEnable)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        switch(enumDDomainRegion)
        {
            case _DDOMAIN_RGN_R1_A1:
                if(bEnable == _DISABLE)
                {
                    if(SysRegionGetDisplayState(_DISPLAY_RGN_EAGLE_SIGHT_SUB) != _DISPLAY_STATE_ACTIVE)
                    {
                        // Disable Sub
                        ScalerDDomainSetR2DenEnable(_DISABLE, _DB_APPLY_POLLING);
                    }
                }
                else
                {
#if(_COLOR_IP_BORDER_WIN == _ON)
                    UserCommonColorBorderWindowDisable(_DB_APPLY_NO_POLLING);
#endif
                }
                break;

            case _DDOMAIN_RGN_ALL:
                // In eagle sight case, when BG enable, border win set disable
                if(bEnable == _ENABLE)
                {
#if(_COLOR_IP_BORDER_WIN == _ON)
                    UserCommonColorBorderWindowDisable(_DB_APPLY_NO_POLLING);
#endif
                }
                break;

            default:
                break;
        }
    }
#endif

    ScalerDDomainBackgroundEnable(enumDDomainRegion, bEnable);
}

//--------------------------------------------------
// Description  : Set Display Background Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainBackgroundSetColorByRegion(EnumDisplayRegion enumDisplayRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    ScalerDDomainBackgroundSetColorByRegion(enumDisplayRegion, ucRed, ucGreen, ucBlue, enumDBApply);
}

//--------------------------------------------------
// Description  : Get Display Force to Background Status
// Input Value  : EnumDDomainRegion
// Output Value : None
//--------------------------------------------------
bit UserCommonDDomainGetBackgroundStatus(EnumDDomainRegion enumDDomainRegion)
{
    return ScalerDDomainGetBackgroundStatus(enumDDomainRegion);
}

//--------------------------------------------------
// Description  : Set Display Background Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainBackgroundSetColor(EnumDDomainRegion enumDDomainRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply)
{
    ScalerDDomainBackgroundSetColor(enumDDomainRegion, ucRed, ucGreen, ucBlue, enumDBApply);
}


//--------------------------------------------------
// Description  : Display Pattern Gen Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenEnable(bit bEnable)
{
    ScalerDDomainPatternGenEnable(bEnable);
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenModeAdjust(EnumDPatternGenMode enumDPatternGenMode)
{
    ScalerDDomainPatternGenModeAdjust(enumDPatternGenMode);
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    ScalerDDomainPatternGenAdjustColor(ucRed, ucGreen, ucBlue);
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color
// Input Value  : RGB Color 0~1023
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue)
{
    ScalerDDomainPatternGenAdjustColor10bit(usRed, usGreen, usBlue);
}

//--------------------------------------------------
// Description  : Set Display Inside Box Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenAdjustBoxColor10bit_Inside(WORD usRed, WORD usGreen, WORD usBlue)
{
    ScalerDDomainBoxPatternGenAdjustColor10bit_Inside(usRed, usGreen, usBlue);
}

//--------------------------------------------------
// Description  : Set Display Outside Box Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenAdjustBoxColor10bit_Outside(WORD usRed, WORD usGreen, WORD usBlue)
{
    ScalerDDomainBoxPatternGenAdjustColor10bit_Outside(usRed, usGreen, usBlue);
}

//--------------------------------------------------
// Description  : Setup Box Pattern Gen Width & Height
// Input Value  : usWidth1, usWidth2, usHeight1, usHeight2
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenSetBoxWidthHeight(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2)
{
    // | Width1  | Width2  |
    // ------------------------------- ---
    // |         |         |         |
    // | Region0 | Region1 | Region2 | Height1
    // |         |         |         |
    // ------------------------------- ---
    // |         |         |         |
    // | Region3 | Region4 | Region5 | Height2
    // |         |         |         |
    // ------------------------------- ---
    // |         |         |         |
    // | Region6 | Region7 | Region8 |
    // |         |         |         |
    // -------------------------------
    ScalerDDomainBoxPatternGenSetWidthHeight(usWidth1, usWidth2, usHeight1, usHeight2);
}

//--------------------------------------------------
// Description  : Setup Box Pattern Gen Region Inside/Outside
// Input Value  : bEnable enable box mode or not
//                pstDPatternGenBoxSetting->b1RegionX are Inside (_FALSE) or Outside (_TRUE)
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenSetBoxRegionInOut(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting)
{
    ScalerDDomainBoxPatternGenSetRegionInOut(bEnable, pstDPatternGenBoxSetting);
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Setup Box Pattern Gen Back Width & Height
// Input Value  : usWidth1, usWidth2, usHeight1, usHeight2
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenSetBoxWidthHeight_Back(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2)
{
    ScalerDDomainBoxPatternGenSetWidthHeight_Back(usWidth1, usWidth2, usHeight1, usHeight2);
}

//--------------------------------------------------
// Description  : Setup Box Pattern Gen Back Region Inside/Outside
// Input Value  : bEnable enable box mode or not
//                pstDPatternGenBoxSetting->b1RegionX are Inside (_FALSE) or Outside (_TRUE)
// Output Value : None
//--------------------------------------------------
void UserCommonDDomainPatternGenSetBoxRegionInOut_Back(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting)
{
    ScalerDDomainBoxPatternGenSetRegionInOut_Back(bEnable, pstDPatternGenBoxSetting);
}
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Motion Blur Reduction Backlight Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayMbrStrobeBacklightCtrl(bit bLightCtrl)
{
    EnumMbrBacklightMode enumBacklightMode = _BACKLIGHT_MODE_CONSTANT;
    bit bTurnOffBacklight = _FALSE;
    bit bValidDisplayMode = _FALSE;
    bit bActiveState = _FALSE;
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
    EnumMbrBacklightMode enumBacklightMode_Prev = GET_MBR_BACKLIGHT_MODE();
    BYTE ucBacklightDuty = UserInterfaceDisplayMbrGetBacklightDuty();
    BYTE ucBacklightPos = UserInterfaceDisplayMbrGetBacklightPosition();
#endif

    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    DebugMessageScaler("MBR: Control Start", bLightCtrl);

    bValidDisplayMode = (enumDisplayMode == _DISPLAY_MODE_1P);

    // To prevent MtP backlight flash
    if((bValidDisplayMode == _FALSE) && (GET_PANELPOWERSTATUS() == _BACKLIGHT_ON_ALREADY) && (bLightCtrl == _LIGHT_CONTROL_ON))
    {
        return;
    }

    // ********************************************
    // 1. Check if backlight needs to be turn off first
    // ********************************************
    if((GET_PANELPOWERSTATUS() != _PANEL_BACKLIGHT_OFF) && (GET_PANELPOWERSTATUS() != _PANEL_POWER_OFF_STATE))
    {
        if(bLightCtrl == _LIGHT_CONTROL_OFF)
        {
            bTurnOffBacklight = _TRUE;
        }
        else
        {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
            if((GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR) && (ScalerMbrAdvanceCheckRtkAdvMbrSequenceCtrl() == _TRUE))
            {
                bTurnOffBacklight = _TRUE; // turn off TCON(backlight) before adjust setting
            }
            else
#endif
            {
                bTurnOffBacklight = (_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _OFF);
            }
        }
    }

    DebugMessageScaler("MBR: bTurnOffBacklight", bTurnOffBacklight);

    // ********************************************
    // 2. Turn off backlight
    // ********************************************
    if(bTurnOffBacklight == _TRUE)
    {
        UserCommonDisplayMbrStrobeBacklightEnableSeq(_LIGHT_CONTROL_OFF);
    }


    // ********************************************
    // 3. Adjust PDIM (TCON) Setting
    // ********************************************
    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            bActiveState = (SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE);
            break;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            bActiveState = (SysRegionGetDisplayState(_DISPLAY_RGN_EAGLE_SIGHT_MAIN) == _DISPLAY_STATE_ACTIVE);
            break;
#endif
        default:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif
            bActiveState = _FALSE;
            break;
    }

    // Check if current status allows to apply user(OSD) selected backlight mode
    // if not, remain constant backlight
    if((bValidDisplayMode == _TRUE) && ((bActiveState == _TRUE) || (SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING)))
    {
        // Get backlight mode
        enumBacklightMode = UserCommonDisplayMbrGetBacklightMode();
    }
    SET_MBR_BACKLIGHT_MODE(enumBacklightMode);

    DebugMessageScaler("MBR: DVTotal", GET_MBR_DVTOTAL());


    // Clear TCON Setting in case different mode conflict
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    if((enumBacklightMode_Prev != GET_MBR_BACKLIGHT_MODE()) && (enumBacklightMode_Prev == _BACKLIGHT_MODE_STROBE_DRR_MBR))
    {
        ScalerMbrDrrClearSetting(_PCB_MBR_TCON_PIN);
    }
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    if((enumBacklightMode_Prev != GET_MBR_BACKLIGHT_MODE()) && (enumBacklightMode_Prev == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR))
    {
        ScalerMbrAdvanceClearUnusedSetting(_PCB_MBR_TCON_PIN);
    }
#endif

#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
    switch(GET_MBR_BACKLIGHT_MODE())
    {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR:
#endif
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _BACKLIGHT_MODE_STROBE_DRR_MBR:
#endif
        case _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR:

            ExternalDeviceInterfaceLedDriverModeSwitch(_DEVICE_LED_DRIVER_MBR_MODE);
            break;

        case _BACKLIGHT_MODE_CONSTANT:
        default:
            ExternalDeviceInterfaceLedDriverModeSwitch(_DEVICE_LED_DRIVER_LD_MODE);
            break;
    }
#endif

    switch(GET_MBR_BACKLIGHT_MODE())
    {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR:
            ScalerMbrRtkAdvMbrCtrl(_PCB_MBR_TCON_PIN, ucBacklightDuty, ucBacklightPos, bLightCtrl);
            break;
#endif
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _BACKLIGHT_MODE_STROBE_DRR_MBR:
            ScalerMbrDrrCtrl(_PCB_MBR_TCON_PIN, ucBacklightDuty, ucBacklightPos, bLightCtrl);
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
            ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_DRR_MBR_DVS, (bLightCtrl == _LIGHT_CONTROL_ON));
#endif
            break;
#endif
        case _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR:
        case _BACKLIGHT_MODE_CONSTANT:
        default:
            UserInterfaceDisplayMbrBacklightAdjust(GET_MBR_BACKLIGHT_MODE(), bLightCtrl, GET_MBR_DVTOTAL());
    }

    // ********************************************
    // 4. Turn on backlight
    // ********************************************
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        UserCommonDisplayMbrStrobeBacklightEnableSeq(_LIGHT_CONTROL_ON);
    }
}

//--------------------------------------------------
// Description  : Turn on/off strobe backlight sequence control
// Input Value  : Light Control ON/OFF
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayMbrStrobeBacklightEnableSeq(bit bLightCtrl)
{
    BYTE ucIndex = 0;
    WORD usDelay = 0;
    EnumMbrBacklightSeqEvent penumAction[] = {_BACKLIGHT_SEQ_PDIM, _BACKLIGHT_SEQ_DELAY, _BACKLIGHT_SEQ_ADIM};
    EnumMbrPDimCtrl enumPDimCtrl = _BACKLIGHT_PDIM_CTRL_BY_TCON;

    usDelay = UserInterfaceDisplayMbrGetBacklightSequenceDelay(bLightCtrl);
    enumPDimCtrl = UserInterfaceDisplayMbrGetPdimControl(GET_MBR_BACKLIGHT_MODE(), bLightCtrl);

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR)
    {
        enumPDimCtrl = _BACKLIGHT_PDIM_CTRL_BY_TCON;
    }
#endif

    if(UserInterfaceDisplayMbrGetBacklightSequence(bLightCtrl) == _BACKLIGHT_SEQ_ADIM_PDIM)
    {
        penumAction[0] = _BACKLIGHT_SEQ_ADIM;
        penumAction[2] = _BACKLIGHT_SEQ_PDIM;
    }

    for(ucIndex = 0; ucIndex < sizeof(penumAction) / sizeof(EnumMbrBacklightSeqEvent); ++ucIndex)
    {
        switch(penumAction[ucIndex])
        {
            case _BACKLIGHT_SEQ_PDIM:
                if(bLightCtrl == _LIGHT_CONTROL_OFF)
                {
                    if(enumPDimCtrl == _BACKLIGHT_PDIM_CTRL_BY_TCON)
                    {
                        ScalerTconEnable(_OFF);
                        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
                    }
                    UserInterfaceDisplayMbrPdimAdjust(GET_MBR_BACKLIGHT_MODE(), bLightCtrl);
                }
                else
                {
                    UserInterfaceDisplayMbrPdimAdjust(GET_MBR_BACKLIGHT_MODE(), bLightCtrl);
                    // TCON Global Enable Control
                    if(enumPDimCtrl == _BACKLIGHT_PDIM_CTRL_BY_TCON)
                    {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
                        if(ScalerMbrAdvanceCheckRtkAdvMbrSequenceCtrl() == _TRUE)
                        {
                            DebugMessageScaler("MBR: Sequence Ctrl Enable", 1);
                            ScalerMbrAdvanceRtkAdvMbrSequenceCtrlEnable(bLightCtrl == _LIGHT_CONTROL_ON);
                        }
                        else
#endif
                        {
                            ScalerTconEnable(_ON);
                            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
                        }
                    }
                }
                DebugMessageScaler("MBR: Adjust PDIM", bLightCtrl);
                break;

            case _BACKLIGHT_SEQ_ADIM:
                UserInterfaceDisplayMbrAdimAdjust(GET_MBR_BACKLIGHT_MODE(), bLightCtrl);
                DebugMessageScaler("MBR: Adjust ADIM", bLightCtrl);
                break;

            case _BACKLIGHT_SEQ_DELAY:
                ScalerTimerDelayXms(usDelay);
                break;
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Get user backlight mode & judge by kernel
// Input Value  : None
// Output Value : current backlight mode
//--------------------------------------------------
EnumMbrBacklightMode UserCommonDisplayMbrGetBacklightMode(void)
{
    EnumMbrBacklightMode enumBacklightMode = _BACKLIGHT_MODE_CONSTANT;

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    SET_MBR_DRR_HW_SUPPORT(UserCommonDisplayMbrDrrCheckHW());
#endif

    // Get backlight mode from user
    enumBacklightMode = UserInterfaceDisplayMbrGetBacklightMode();
    DebugMessageScaler("MBR: User Backlight Mode", enumBacklightMode);

    // Kernel check capability again
    enumBacklightMode = ScalerMbrCheckBacklightMode(enumBacklightMode, SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)));
    DebugMessageScaler("MBR: Kernel Adjusted Backlight Mode", enumBacklightMode);

    return enumBacklightMode;
}

//--------------------------------------------------
// Description  : Return current backlight mode
// Input Value  : None
// Output Value : current backlight mode
//--------------------------------------------------
EnumMbrBacklightMode UserCommonDisplayMbrGetCurrentBacklightMode(void)
{
    return GET_MBR_BACKLIGHT_MODE();
}

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : In active mode, decide whether to change backlight mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayMbrDrrHandler(void)
{
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if((enumDisplayMode == _DISPLAY_MODE_1P) && (GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_STROBE_DRR_MBR) && (GET_MBR_DRR_BACKLIGHT_MODE() != _MBR_DRR_MODE_OFF))
    {
        // Judge Framerate
        if(GET_MBR_DRR_BACKLIGHT_MODE() == _MBR_DRR_MODE_STROBE)
        {
            if(GET_MBR_DRR_VFREQ_AVG() < _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO)
            {
                SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_STROBE_TO_CONSTANT);
                SET_MBR_DRR_STEP_CHG_CNT(1);
                DebugMessageScaler("MBR: Strobe to Constant", GET_MBR_DRR_VFREQ_AVG());
            }
        }
        else if(GET_MBR_DRR_BACKLIGHT_MODE() == _MBR_DRR_MODE_CONSTANT)
        {
            if((GET_MBR_DRR_VFREQ_AVG() >= _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI) && (GET_MBR_DRR_SAFE_CNT() > _MBR_DRR_SWITCH_FRAME_COUNT))
            {
                SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_CONSTANT_TO_STROBE);
                SET_MBR_DRR_STEP_CHG_CNT(1);
                DebugMessageScaler("MBR: Constant to Strobe", GET_MBR_DRR_VFREQ_AVG());
            }
        }

        // Check Transition
        if((GET_MBR_DRR_BACKLIGHT_MODE() == _MBR_DRR_MODE_STROBE_TO_CONSTANT) || (GET_MBR_DRR_BACKLIGHT_MODE() == _MBR_DRR_MODE_CONSTANT_TO_STROBE))
        {
            WORD usStrobePeriod = 0;
            if(GET_MBR_DRR_BACKLIGHT_MODE() == _MBR_DRR_MODE_STROBE_TO_CONSTANT)
            {
                usStrobePeriod = (GET_MBR_DVTOTAL() + 1) * (_MBR_DRR_TRANSITION_FRAME_CNT_LO - GET_MBR_DRR_STEP_CHG_CNT()) / _MBR_DRR_TRANSITION_FRAME_CNT_LO;
            }
            else
            {
                usStrobePeriod = (GET_MBR_DVTOTAL() + 1) * GET_MBR_DRR_STEP_CHG_CNT() / _MBR_DRR_TRANSITION_FRAME_CNT_HI;
            }
            DebugMessageScaler("MBR: Transition", GET_MBR_DRR_BACKLIGHT_MODE());
            DebugMessageScaler("MBR: Step Change Count", GET_MBR_DRR_STEP_CHG_CNT());
            ScalerMbrDrrStepChange(_PCB_MBR_TCON_PIN, usStrobePeriod, UserInterfaceDisplayMbrGetBacklightDuty(), UserInterfaceDisplayMbrGetBacklightPosition());

            if(GET_MBR_DRR_BACKLIGHT_MODE() == _MBR_DRR_MODE_STROBE_TO_CONSTANT)
            {
                if(GET_MBR_DRR_STEP_CHG_CNT() == _MBR_DRR_TRANSITION_FRAME_CNT_LO)
                {
                    SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_CONSTANT);
                    SET_MBR_DRR_STEP_CHG_CNT(0);
                }
                else
                {
                    SET_MBR_DRR_STEP_CHG_CNT(GET_MBR_DRR_STEP_CHG_CNT() + 1);
                }
            }
            else
            {
                if(GET_MBR_DRR_STEP_CHG_CNT() == _MBR_DRR_TRANSITION_FRAME_CNT_HI)
                {
                    SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_STROBE);
                    SET_MBR_DRR_STEP_CHG_CNT(0);
                }
                else
                {
                    SET_MBR_DRR_STEP_CHG_CNT(GET_MBR_DRR_STEP_CHG_CNT() + 1);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Check TCON Toggle Time for Division of Frequency is Available
// Input Value  : None
// Output Value : whether HW is supported at current timing
//--------------------------------------------------
bit UserCommonDisplayMbrDrrCheckHW(void)
{
    WORD usHFreq = 0;
    BYTE ucToggleTimeTotal = 0;

    usHFreq = GET_D_CLK_FREQ() / ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
    while(usHFreq > _PCB_MBR_DRIVER_IC_MAX_FREQ)
    {
        ucToggleTimeTotal++;
        usHFreq /= 2;
    }

    DebugMessageScaler("MBR: ucToggleTimeTotal", ucToggleTimeTotal);

    if((_TCON2 + ucToggleTimeTotal + 2) <= _PCB_MBR_TCON_PIN)
    {
        SET_MBR_DRR_TCON_TOGGLE_TIME(ucToggleTimeTotal);
        return _TRUE;
    }
    else
    {
        SET_MBR_DRR_TCON_TOGGLE_TIME(0);
        DebugMessageScaler("MBR: Not Enough TCON for Toggle", 0);
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Return DRR MBR HW Support Status
// Input Value  : None
// Output Value : whether HW is supported at current timing
//--------------------------------------------------
bit UserCommonDisplayMbrDrrGetHWSupport(void)
{
    return GET_MBR_DRR_HW_SUPPORT();
}

#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return RTK MBR enable status
// Input Value  : None
// Output Value : Enable/Disable
//--------------------------------------------------
bit UserCommonDisplayGetAdvMbrStatus(void)
{
    return ScalerMbrAdvanceGetRtkAdvMbrStatus();
}

//--------------------------------------------------
// Description  : Adjust Motion Blur Reduction
//                Function According to User Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayResetRtkAdvMbrStatus(void)
{
    // Reset RTK ADV MBR mode
    ScalerMbrAdvanceClearRtkAdvMbrMode();

    // Get User/OSD MBR enable and set to MBR global variable
    ScalerMbrAdvanceSetRtkAdvMbrUserStatus(UserInterfaceDisplayGetRtkAdvMbrSetting());
}
#endif // end of #if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)

#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Adjust DRR MBR/RTK Adv Mbr Parameters
// Input Value  : ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayMbrAdvAdjust(BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_STROBE_DRR_MBR)
    {
        ScalerMbrDrrAdjust(_PCB_MBR_TCON_PIN, ucBacklightDuty, ucBacklightPos, bLightCtrl);
    }
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR)
    {
        ScalerMbrRtkAdvMbrCtrl(_PCB_MBR_TCON_PIN, ucBacklightDuty, ucBacklightPos, bLightCtrl);
    }
#endif
}
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return current BFI available mode
// Input Value  : None
// Output Value : current BFI mode
//--------------------------------------------------
EnumMbrBFIMode UserCommonDisplayMbrGetBlackFrameInsertAvailable(void)
{
    if(GET_MBR_BFI_AVAILABLE_MODE() == _BFI_KERNEL_OFF)
    {
        return _BFI_MODE_OFF;
    }
    else
    {
        return _BFI_MODE_ON;
    }
}

//--------------------------------------------------
// Description  : Return if current BFI is enable
// Input Value  : None
// Output Value : BFI enable status
//--------------------------------------------------
EnumMbrBFIMode UserCommonDisplayMbrGetBlackFrameInsertEnable(void)
{
    return ScalerMbrGetBlackFrameInsertEnable();
}

//--------------------------------------------------
// Description  : Black Frame Insertion Function Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayMbrBlackFrameInsertAdjust(void)
{
    EnumMbrBFIMode enumMbrBFIUserMode = UserInterfaceDisplayMbrGetBlackFrameInsertMode();

    if(enumMbrBFIUserMode == _BFI_MODE_ON)
    {
        if(GET_MBR_BFI_AVAILABLE_MODE() == _BFI_KERNEL_OFF)
        {
            enumMbrBFIUserMode = _BFI_MODE_OFF;
        }
    }

    if(enumMbrBFIUserMode == _BFI_MODE_ON)
    {
        // enable BFI function
        ScalerMDomainBlackFrameInsertEnable(_FUNCTION_ON, GET_MBR_BFI_AVAILABLE_MODE());

        // user customerized brightness adjustment here
        UserInterfaceDisplayMbrBlackFrameInsertCtrl(_BFI_MODE_ON);
    }
    else if((enumMbrBFIUserMode == _BFI_MODE_OFF) && (UserCommonDisplayMbrGetBlackFrameInsertEnable() != _BFI_MODE_OFF))
    {
        // user customerized brightness adjustment here
        UserInterfaceDisplayMbrBlackFrameInsertCtrl(_BFI_MODE_OFF);

        // disable BFI function
        ScalerMDomainBlackFrameInsertEnable(_FUNCTION_OFF, GET_MBR_BFI_AVAILABLE_MODE());
    }
}
#endif // end of #if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Eagle Sight Sub can display when main is frame sync mode
// Input Value  : None
// Output Value : _EAGLE_SIGHT_MAIN_SUB_SYNC / _EAGLE_SIGHT_MAIN_SUB_ASYNC
//--------------------------------------------------
EnumEagleSightMainSubSynchronous UserCommonDisplayGetEagleSightMainSubSync(void)
{
    return ScalerMDomainGetEagleSightMainSubSync();
}

//--------------------------------------------------
// Description  : Eagle Sight Adjust
// Input Value  : EnumEagleSightSetting
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayEagleSightAdjust(EnumEagleSightSetting enumEagleSightSetting)
{
    if(UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_ASYNC)
    {
        return;
    }

    switch(enumEagleSightSetting)
    {
        case _EAGLE_SIGHT_RATIO:
        case _EAGLE_SIGHT_CAP_POSITION:
        case _EAGLE_SIGHT_DISP_POSITION:
            SysModeEagleSightGetUserSetting();

            if(GET_EAGLE_SIGHT_USER_ENABLE() == _EAGLE_SIGHT_SETTING_DISABLE)
            {
                // Disable Eagle Sight
                ScalerDDomainSetR2DenEnable(_DISABLE, _DB_APPLY_NONE);
                UserCommonDisplayEagleSightTransparencySetting(0xFF);

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
                UserCommonColorCircleWindowAdjust(_DB_APPLY_NO_POLLING);
#else
#if(_COLOR_IP_HL_WIN == _ON)
                UserCommonColorHLWinTypeAdjust(_DB_APPLY_NONE);
#endif
                UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            }
            else
            {
                if(enumEagleSightSetting == _EAGLE_SIGHT_DISP_POSITION)
                {
                    ScalerDDomainSetR2DenEnable(_DISABLE, _DB_APPLY_NONE);
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
                    if(GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE() == _ON)
                    {
                        UserCommonColorSetCircleWindowBorderEnable(_DISABLE, _DB_APPLY_POLLING);
                    }
                    else
#endif
                    {
                        UserCommonColorBorderWindowDisable(_DB_APPLY_POLLING);
                    }
                }
                SysModeSetDisplayTarget(_DISPLAY_RGN_EAGLE_SIGHT_SUB);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
            }

            break;

        case _EAGLE_SIGHT_ENABLE:
        case _EAGLE_SIGHT_TRANSPARENCY:
            // Special OSD Requirement for Eagle Sight
            UserInterfaceOsdForEagleSightModify(_DB_APPLY_NONE);
            SysModeEagleSightGetUserSetting();
            UserCommonDisplayEagleSightTransparencySetting(GET_EAGLE_SIGHT_USER_TRANSPARENCY());

            if(GET_EAGLE_SIGHT_USER_ENABLE() == _EAGLE_SIGHT_SETTING_ENABLE)
            {
                ScalerDDomainSetR2DenEnable(_ENABLE, _DB_APPLY_NONE);
#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
                ScalerFRCEagleSightLowLatency(_FRC_LATENCY_MEDIUM);
#else
                ScalerFRCEagleSightLowLatency(_FRC_LATENCY_LARGE);
#endif
            }
            else
            {
                ScalerDDomainSetR2DenEnable(_DISABLE, _DB_APPLY_NONE);

                if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
                {
                    ScalerFRCEagleSightLowLatency(_FRC_LATENCY_SMALL);
                }
                else
                {
                    ScalerFRCEagleSightLowLatency(_FRC_LATENCY_LARGE);
                }
            }

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
            UserCommonColorCircleWindowAdjust(_DB_APPLY_NO_POLLING);
#else
#if(_COLOR_IP_HL_WIN == _ON)
            UserCommonColorHLWinTypeAdjust(_DB_APPLY_NONE);
#endif
            UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            break;

        case _EAGLE_SIGHT_BORDER:
        case _EAGLE_SIGHT_CIRCLE_WIN:
            SysModeEagleSightGetUserSetting();

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
            UserCommonColorCircleWindowAdjust(_DB_APPLY_NO_POLLING);
#else
#if(_COLOR_IP_HL_WIN == _ON)
            UserCommonColorHLWinTypeAdjust(_DB_APPLY_NONE);
#endif
            UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set Eagle Sight Transparency
// Input Value  : Transparancy setting
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayEagleSightTransparencySetting(BYTE ucLevel)
{
    DebugMessageScaler("Transparency level", ucLevel);
    ScalerColorPIPBlendingLevelAdjust(ucLevel, _DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Eagle Sight Adjust
// Input Value  : EnumEagleSightSetting
// Output Value : None
//--------------------------------------------------
bit UserCommonDisplayGetShowEagleSightWindow(void)
{
    if((GET_EAGLE_SIGHT_USER_ENABLE() == _ON) && (ScalerDDomainGetR2DenEnable() == _ENABLE))
    {
        return _TRUE;
    }
    return _FALSE;
}
#endif

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check R2 Den Enable or not
// Input Value  : None
// Output Value : _ENABLE: R2 Den Enable
//--------------------------------------------------
bit UserCommonDisplayGetSubDenEnable(void)
{
    return ScalerDDomainGetR2DenEnable();
}
//--------------------------------------------------
// Description  : Check R2 Den Enable or not
// Input Value  : None
// Output Value : _ENABLE: R2 Den Enable
//--------------------------------------------------
void UserCommonDisplaySetSubDenEnable(bit bEnable, EnumDBApply enumDBApply)
{
    ScalerDDomainSetR2DenEnable(bEnable, enumDBApply);
}
#endif


#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get 2P frame sync enable
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonDisplayGet2PFrameSyncEnable(void)
{
    return ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE());
}
#endif

//--------------------------------------------------
// Description  : Frame Sync support info for user
// Input Value  : None
// Output Value : _FRAME_SYNC_SUPPORT_ON/ _FRAME_SYNC_SUPPORT_OFF
//--------------------------------------------------
EnumFrameSyncSupport UserCommonDisplayGetFrameSyncSupport(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        return _FRAME_SYNC_SUPPORT_ON;
    }

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
    {
        return _FRAME_SYNC_SUPPORT_ON;
    }
#endif

    return _FRAME_SYNC_SUPPORT_OFF;
}

//--------------------------------------------------
// Description  : Disable all Global Watch Dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayGlobalDisableAllWatchDog(void)
{
    ScalerGlobalDisableAllWatchDog();
}

//--------------------------------------------------
// Description  : Get Scaling Status
// Input Value  : StructScalingStatus
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayGetScalingStatus(StructScalingStatus *pstData)
{
    pstData->b1HSU = GET_H_SCALE_UP();
    pstData->b1HSD = GET_H_SCALE_DOWN();
    pstData->b1VSU = GET_V_SCALE_UP();
    pstData->b1VSD = GET_V_SCALE_DOWN();
}

//--------------------------------------------------
// Description  : Get Memory Config
// Input Value  : None
// Output Value : EnumMemoryWorkMode
//--------------------------------------------------
EnumMemoryWorkMode UserCommonDisplayGetMemoryConfig(void)
{
    return GET_MEMORY_WORK_TYPE();
}

//--------------------------------------------------
// Description  : Check System SelRegion by Kernel
// Input Value  : EnumSelRegion
// Output Value : EnumSelRegion
//--------------------------------------------------
EnumSelRegion UserCommonRegionCheckSystemSelectRegion(EnumSelRegion enumSelRegion)
{
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumSelRegion == _1P_NORMAL_REGION)
    {
        if(UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_SYNC)
        {
            return _FULL_REGION;
        }
    }
#endif
#endif

    return enumSelRegion;
}

//--------------------------------------------------
// Description  : Get Current Frame Sync mode setting (P0_28[3])
// Input Value  : None
// Output Value : _FRAME_SYNC_MODE or _FREE_RUN_MODE
//--------------------------------------------------
EnumFrameSyncModeType UserCommonDisplayGetFrameSyncMode(void)
{
    return ScalerMDomainGetFrameSyncMode();
}

//--------------------------------------------------
// Description  : Get Measure DVtotal (when frame sync mode)
// Input Value  : None
// Output Value : DVtotal (unit: D line)
//--------------------------------------------------
WORD UserCommonDisplayGetMeasureDVtotal(void)
{
    return ScalerMDomainGetDVtotalLastline();
}

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Update Interface Feature IVF
// Input Value  : EnumInputPort, ucDisplayIndex
// Output Value : IVF
//--------------------------------------------------
WORD UserCommonDisplayGetInterfaceSpecificIVFreq(EnumInputPort enumInputPort)
{
#if(_HDMI21_FVA_SUPPORT == _ON)
    BYTE ucFvaFactor = ScalerTmdsMacRxHdmi21GetFvaFactor(enumInputPort);
#endif

    WORD usIVfreq = 0;
    WORD usIVfreqTemp = 0;
    EnumRegionIndex enumRegionIndex = SysRegionConvertPortToRegionIndex(enumInputPort);

    if((enumRegionIndex == _REGION_INDEX_NONE) ||
       (SysRegionCheckDisplayEvent(SysRegionGetDisplayRegion(enumRegionIndex), _DISPLAY_EVENT_TIMING_CONFIRMED) == _FALSE))
    {
        return usIVfreq;
    }
    else
    {
        usIVfreq = g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.usVFreq;
    }

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
    {
        if(ScalerDrrVfreqMaxInfoEnable(enumInputPort, SysSourceGetPortTypeFromInputPort(enumInputPort)) == _TRUE)
        {
            DebugMessageScaler("DRR Get IVF from Source info", GET_DRR_VFREQ_MAX());
            usIVfreqTemp = GET_DRR_VFREQ_MAX();
        }
        else
        {
            usIVfreqTemp = SysModeDrrGetIVFreq(enumInputPort);
        }

        if(usIVfreqTemp != 0x00)
        {
            usIVfreq = usIVfreqTemp;
        }
    }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)

    switch(SysSourceGetPortTypeFromInputPort(enumInputPort))
    {
        case _PORT_HDMI:
        case _PORT_HDMI20:
            // Current HDMI Port with FVA feature incoming
            if(ucFvaFactor > 0x01)
            {
                usIVfreqTemp = SysModeHdmi21GetFvaMaxIVf(enumInputPort);

                if(usIVfreqTemp != 0x00)
                {
                    usIVfreq = usIVfreqTemp;
                }
            }
            break;

        default:
            break;
    }
#endif
    return usIVfreq;
}
#endif

