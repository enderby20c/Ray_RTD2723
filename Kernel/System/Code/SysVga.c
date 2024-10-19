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
// ID Code      : SysVga.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_VGA__

#include "SysInclude.h"
#include "Vga/SysVga.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
EnumDisplayRegion g_enumVgaRegion = _DISPLAY_RGN_NONE;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch VGA ports
// Input Value  : Current Input Port, Target Source Type, switch status
// Output Value : None
//--------------------------------------------------
void SysVgaInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, StructPortSwitchedStatus *pstPortStatus)
{
    enumPortType = enumPortType;
    enumInputPort = enumInputPort;
    pstPortStatus = pstPortStatus;

#if(_HW_VGA_ADC_SUPPORT == _ON)
    // Disable APLL
    if((enumInputPort != _A0_INPUT_PORT) && (pstPortStatus->b1A0 == _FALSE))
    {
        ScalerSyncAdcApllPowerDown();
    }
#endif
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get & update VGA display region
// Input Value  : None
// Output Value : display region
//--------------------------------------------------
EnumDisplayRegion SysVgaGetRegion(void)
{
    // Check current VGA region
    if(((EnumDisplayMode)GET_RGN_DISPLAY_MODE(g_enumVgaRegion) == GET_DISPLAY_MODE()) &&
       (GET_RGN_SOURCE_TYPE(ScalerRegionGetIndex(g_enumVgaRegion)) == _SOURCE_VGA))
    {
        return g_enumVgaRegion;
    }
    else
    {
        // Search VGA region
        BYTE ucRegionIndex = 0;
        BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

        g_enumVgaRegion = _DISPLAY_RGN_NONE;

        for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
        {
            if(GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_VGA)
            {
                g_enumVgaRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);
                break;
            }
        }

        return g_enumVgaRegion;
    }
}

//--------------------------------------------------
// Description  : Enable or disable VGA watchdog
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void SysVgaWatchDog(bit bEnable)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if((GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_VGA) &&
           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE))
        {
            ScalerRegionSetWatchDog(GET_RGN_DISPLAY_REGION(ucRegionIndex), bEnable);
        }
    }
}

//--------------------------------------------------
// Description  : Scan VGA Port
// Input Value  : None
// Output Value : Source Type
//--------------------------------------------------
EnumSourceType SysVgaScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    BYTE ucRegionIndex = 0;

    enumPortType = enumPortType;

    if(ScalerVgaSyncProcPreDetect(enumInputPort) == _FALSE)
    {
        return _SOURCE_NONE;
    }

    if(ScalerVgaSyncProcTypeAutoRun() != _NO_SYNC_STATE)
    {
        // Backup Double Buffer Status
        EnumDBEnableStatus enumDBBackup = ScalerGlobalGetDBStatus(_INPUT_PATH_ALL); // need to check again!!!

        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_VGA);

        // Initial ADC Clock.
        if(ScalerVgaSyncProcAdcClkInitial() == _FALSE)
        {
            DebugMessageAnalog("Apll initial Fail", 0);

            return _SOURCE_NONE;
        }

        // Search select region for VGA
        ucRegionIndex = SysRegionConvertPortToRegionIndex(_A0_INPUT_PORT);

        if(ucRegionIndex == _REGION_INDEX_NONE)
        {
            DebugMessageSystem("VGA Region Fail", 0);

            return _SOURCE_NONE;
        }

        g_enumVgaRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);

        // Disable Global Double Buffer
        ScalerGlobalDoubleBufferEnable(_DISABLE);

        // Set VGATOP VGIP
        ScalerVgaTopInputInitial();

        // Store source index
        SET_RGN_SOURCE_INDEX(ucRegionIndex, g_ucSourceSearchIndex);

        CLR_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);

        // Set measure region index
        ScalerMeasureSetRegionIndex(ucRegionIndex);
        ScalerMeasureSetInputPath(ScalerRegionGetInputDataPath(g_enumVgaRegion));

        // Get Measure Info.
        if(ScalerMeasureVgaInputInfo() == _FALSE)
        {
            DebugMessageSystem("VGA Measure Fail", 0);

            if(enumDBBackup != _DB_DISABLE)
            {
                // Restore Double Buffer Status
                ScalerGlobalDoubleBufferEnable(_ENABLE);
            }

            return _SOURCE_NONE;
        }

        // Mode No. match
        g_ucVgaModeNo = UserCommonModeSearchModeVGA();

        DebugMessageAnalog("9. g_ucVgaModeNo = ", g_ucVgaModeNo);

        if(g_ucVgaModeNo == _VGA_MODE_NOSUPPORT)
        {
            SET_INPUT_TIMING_HWIDTH(0);
            SET_INPUT_TIMING_VHEIGHT(0);
            SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_OOR);
        }
        else
        {
            // Confirm Clamp Position Setting.
            ScalerVgaSyncProcClampPosCheck(UserCommonModeSearchGetModeVideoType(g_ucVgaModeNo));

            // Color format setting.
            ScalerVgaAdcClampMode(ScalerColorGetColorSpace(_A0_INPUT_PORT));

            if(ScalerVgaSyncProcAdcClkSetting() == _FALSE)
            {
                if(enumDBBackup != _DB_DISABLE)
                {
                    // Restore Double Buffer Status
                    ScalerGlobalDoubleBufferEnable(_ENABLE);
                }

                return _SOURCE_NONE;
            }

            // Set VGATOP capture
            if(ScalerVgaTopSetCapture() == _FALSE)
            {
                if(enumDBBackup != _DB_DISABLE)
                {
                    // Restore Double Buffer Status
                    ScalerGlobalDoubleBufferEnable(_ENABLE);
                }

                return _SOURCE_NONE;
            }

            // SOG0 DC Restore Disable
            ScalerVgaAdcDCRestoreEn(_OFF);

            // SOG Clamp Enable
            ScalerVgaAdcSOGClampEn(_ON);

            // Double-check for VS synchronize edge
            ScalerVgaTopModifyVsLatchEdge(_WAIT);

            // Clear Sync Changed Status flag bit.
            ScalerVgaSyncProcClearSyncChangeStatus();

            // Re-start on-line measure
            ScalerMeasureSetOnlineMeasure(_SOURCE_VGA, enumInputPort, ScalerRegionGetInputDataPath(g_enumVgaRegion), GET_INPUT_TIMING_VFREQ());

#if(_YPBPR_SUPPORT == _ON)
#if(_COLOR_IP_COLOR_CONVERT == _ON)
            if(ScalerColorGetColorSpace(_A0_INPUT_PORT) == _COLOR_SPACE_YPBPR)
            {
                ScalerColorSpaceSetColorimetry(_A0_INPUT_PORT, UserCommonVgaCheckHDTVMode(g_ucVgaModeNo));
            }
#endif
#endif // End of #if(_YPBPR_SUPPORT == _ON)

            // Perform I-domain OOR check here
            if(UserCommonModeCheckNoSupport(g_enumVgaRegion) == _TRUE)
            {
                SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_OOR);
            }

            // Re-start on-line measure after APLL clock adjust
            ScalerMeasureSetOnlineMeasure(_SOURCE_VGA, enumInputPort, ScalerRegionGetInputDataPath(g_enumVgaRegion), GET_INPUT_TIMING_VFREQ());

            DebugMessageSystem("VGA Measure Info", g_enumVgaRegion);
            DebugMessageSystem("Input Timing HP", GET_INPUT_TIMING_H_POLARITY());
            DebugMessageSystem("Input Timing VP", GET_INPUT_TIMING_V_POLARITY());
            DebugMessageSystem("Input Timing InterLace", GET_INPUT_TIMING_INTERLACE_FLG());
            DebugMessageSystem("Input Timing HFreq", GET_INPUT_TIMING_HFREQ());
            DebugMessageSystem("Input Timing HTotal", GET_INPUT_TIMING_HTOTAL());
            DebugMessageSystem("Input Timing HStart", GET_INPUT_TIMING_HSTART());
            DebugMessageSystem("Input Timing HWidth", GET_INPUT_TIMING_HWIDTH());
            DebugMessageSystem("Input Timing HSW", GET_INPUT_TIMING_HSYNCWIDTH());
            DebugMessageSystem("Input Timing VFreq", GET_INPUT_TIMING_VFREQ());
            DebugMessageSystem("Input Timing VTotal", GET_INPUT_TIMING_VTOTAL());
            DebugMessageSystem("Input Timing VStart", GET_INPUT_TIMING_VSTART());
            DebugMessageSystem("Input Timing VHeight", GET_INPUT_TIMING_VHEIGHT());
            DebugMessageSystem("Input Timing VSW", GET_INPUT_TIMING_VSYNCWIDTH());
        }

        // Set Timing Confirm Flag.
        SET_RGN_TIMING_CONFIRM(ucRegionIndex);
        SET_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);

        // Download adc data from NVRam
        UserCommonNVRamLoadADCSetting(_COLOR_SPACE_RGB);

        // Gain Offset Adjust.
        UserCommonVgaAdcDataAdjust();

        if(enumDBBackup != _DB_DISABLE)
        {
            // Restore Double Buffer Status
            ScalerGlobalDoubleBufferEnable(_ENABLE);
        }

        return _SOURCE_VGA;
    }

    // Check sync is invalid
    return _SOURCE_NONE;
}

#endif // End of #if(_VGA_SUPPORT == _ON)
