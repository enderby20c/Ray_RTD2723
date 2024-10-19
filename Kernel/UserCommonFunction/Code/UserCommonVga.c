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
// ID Code      : UserCommonVga.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_VGA__

#include "UserCommonInclude.h"
#include "Vga/UserCommonVga.h"

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucVgaAutoConfigStatus;

StructVgaModeUserDataType g_stVgaModeUserData;
StructAdcDataType g_stVgaAdcData;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_YPBPR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get color rimetry
// Input Value  : ucModeNumber --> Target Mode Number
// Output Value : _TRUE --> current mode is HD TV Mode
//--------------------------------------------------
bit UserCommonVgaCheckHDTVMode(BYTE ucModeNumber)
{
    switch(ucModeNumber)
    {
        case _MODE_720x480p_60HZ:
        case _MODE_1440x480i_60HZ:
        case _MODE_720x576p_50HZ:
        case _MODE_1440x576i_50HZ:

            return _FALSE;

        case _MODE_1280x720p_60HZ:
        case _MODE_1920x1080i_50HZ:
        case _MODE_1920x1080i_60HZ:
        case _MODE_1920x1080p_50HZ:
        case _MODE_1920x1080p_60HZ:
        case _MODE_1920x1080i_50HZ_2:
        case _MODE_1280x720p_50HZ:

            return _TRUE;

        default:

            return _FALSE;
    }
}
#endif // End of #if(_YPBPR_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get VGA Sync Pad
// Input Value  : None
// Output Value : _TRUE if sync comes from SOG pag
//--------------------------------------------------
bit UserCommonVgaSyncProcGetSyncPad(void)
{
    return ScalerVgaSyncProcGetSyncPad();
}

//--------------------------------------------------
// Description  : Check if the ADC clock (IHTotal) is out of range. Range = (BackPorch + FrontPorch) * 2 / 5 .
// Input Value  : usClock   --> ADC Clock (IHTotal)
// Output Value : Return _TRUE if not out of range
//--------------------------------------------------
WORD UserCommonVgaGetAdcClockRange(BYTE ucPar)
{
    WORD usDelta1 = 0;
    WORD usDelta2 = 0;
    WORD usDelta = 0;

    usDelta1 = GET_ADC_LIMIT_CLOCK() - g_stVgaModeUserData.usCenterClock;

    usDelta2 = g_stVgaModeUserData.usCenterClock - ScalerVgaTopGetCaptureHStartPosition() - ScalerVgaTopGetCaptureHWidth();

    usDelta = (usDelta1 < usDelta2) ? usDelta1 : usDelta2;

    if(ucPar == _GET_CLOCKRANGE_MAX)
    {
        if(usDelta < _CLOCK_BIAS)
        {
            return (g_stVgaModeUserData.usCenterClock + usDelta);
        }
        else
        {
            return (g_stVgaModeUserData.usCenterClock + _CLOCK_BIAS);
        }
    }
    else if(ucPar == _GET_CLOCKRANGE_MIN)
    {
        if(usDelta < _CLOCK_BIAS)
        {
            return (g_stVgaModeUserData.usCenterClock - usDelta);
        }
        else
        {
            return (g_stVgaModeUserData.usCenterClock - _CLOCK_BIAS);
        }
    }

    return (g_stVgaModeUserData.usCenterClock);
}

//--------------------------------------------------
// Description  : Adjust clock.
// Input Value  : usUserIHTotal --> OSD Value(0~100) or Real Value
// Output Value : None
//--------------------------------------------------
void UserCommonVgaClockAdjust(WORD usUserIHTotal)
{
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)

    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usUserIHTotal = UserCommonDisplayPercentToRealValueAdjust((BYTE)usUserIHTotal, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

#endif

    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    SysVgaWatchDog(_DISABLE);

    ScalerAPLLFastLockAdjust(usUserIHTotal);

    SysVgaWatchDog(_ENABLE);
}

//--------------------------------------------------
// Description  : Adjust phase
// Input Value  : ucPhase --> phase value
// Output Value : None
//--------------------------------------------------
void UserCommonVgaPhaseAdjust(BYTE ucPhase)
{
    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    ucPhase = UserCommonDisplayPercentToRealValueAdjust(ucPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER);

    SysVgaWatchDog(_DISABLE);

    ScalerPLLSetPhase(ucPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVFREQ));

    SysVgaWatchDog(_ENABLE);
}

//--------------------------------------------------
// Description  : ADC Parameters Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonVgaAdcDataAdjust(void)
{
    // Adjust Gain
    ScalerVgaAdcGainAdjust(g_stVgaAdcData.pucAdcGainMSB, g_stVgaAdcData.pucAdcGainLSB);

    // Adjust Offset
    ScalerVgaAdcOffsetAdjust(g_stVgaAdcData.pucAdcOffsetMSB, g_stVgaAdcData.pucAdcOffsetLSB);
}

//--------------------------------------------------
// Description  : Picture position/clock/phase auto calibration.
// Input Value  : None
// Output Value : Return Error Status
//--------------------------------------------------
void UserCommonVgaAutoConfig(void)
{
    g_ucVgaAutoConfigStatus = 0;

    ScalerVgipSetInputRegion(SysVgaGetRegion());
    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    if(UserCommonVgaAutoMeasureMultiTimes() == _FALSE)
    {
        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_CHECK_MULTITIMES_FINISH);

    if(UserCommonVgaAutoClock() == _FALSE)
    {
        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    SET_VGA_MODE_ADJUST_CLOCK(50);
#else
    SET_VGA_MODE_ADJUST_CLOCK(g_stVgaModeUserData.usCenterClock);
#endif

    UserCommonVgaClockAdjust(GET_VGA_MODE_ADJUST_CLOCK());

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_FINISH);

    // UserCommonVgaAutoPhaseTestFunction();

    if(UserCommonVgaAutoPhase() == _FALSE)
    {
        SET_VGA_MODE_ADJUST_PHASE(UserCommonDisplayRealValueToPercentAdjust(g_stVgaModeUserData.ucCenterPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER));

        UserCommonVgaPhaseAdjust(GET_VGA_MODE_ADJUST_PHASE());

        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_PHASE_FINISH);

    if(UserCommonVgaAutoVPosition() == _FALSE)
    {
        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_V_POSITION_FINISH);

    if(UserCommonVgaAutoHPosition() == _FALSE)
    {
        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_H_POSITION_FINISH);

    SET_VGA_MODE_DO_FIRST_AUTO(_FALSE);

    UserCommonVgaAutoUpdateUserdata();
}

//--------------------------------------------------
// Description  : Adjust clock.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoClock(void)
{
    WORD usClock = 0;

    // Check picture whether the rate of not full frame of picture is less than 95% of full frame
    if(UserCommonVgaAutoClockCheckPictureRegion() == _FALSE)
    {
        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_CLOCK_ABORT;

        return _TRUE;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_CHECK_WIDTH_FINISH);

    // Find Rough Htotal(clock)
    if(UserCommonVgaAutoClockRoughAdjust(&usClock) == _FALSE)
    {
        return _FALSE;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH);

    // Find Best Htotal(clock)
    if(UserCommonVgaAutoClockFineTuneAdjust(&usClock) == _FALSE)
    {
        return _FALSE;
    }

    UserInterfaceVgaGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_FINETUNE_FINISH);

    g_stVgaModeUserData.usCenterClock = usClock;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust H Position.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoHPosition(void)
{
    WORD usCurrClock = 0;

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usCurrClock = UserCommonDisplayPercentToRealValueAdjust(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
#else
    usCurrClock = GET_VGA_MODE_ADJUST_CLOCK();
#endif

    if(UserInterfaceVgaSkipAutoHpos() == _AUTO_CONFIG_SKIP_TRUE)
    {
        return _TRUE;
    }

#if(_OVERSCAN_SUPPORT == _TRUE)

    if(UserInterfaceDisplayGetOverScanStatus(SysVgaGetRegion()) == _OVERSCAN_TRUE)
    {
        if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, usCurrClock) == _FALSE)
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, usCurrClock) == _FALSE)
        {
            return _FALSE;
        }
    }

    if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
    {
        return _FALSE;
    }

    if(GET_ACTIVE_H_WIDTH() <= UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IHWIDTH))
    {
        if(GET_ACTIVE_H_START() < (ScalerVgaTopGetCaptureHStartPosition() + ScalerVgaTopGetCaptureHDelay()))
        {
            g_stVgaModeUserData.usCenterHPosition = GET_ACTIVE_H_START();
        }
        else if(GET_ACTIVE_H_END() > (ScalerVgaTopGetCaptureHStartPosition() + ScalerVgaTopGetCaptureHDelay() + ScalerVgaTopGetCaptureHWidth() - 1))
        {
            g_stVgaModeUserData.usCenterHPosition = GET_ACTIVE_H_END() - (ScalerVgaTopGetCaptureHWidth()) + 1;
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        g_stVgaModeUserData.usCenterHPosition = GET_ACTIVE_H_START();
    }

    UserCommonDisplayHPositionAdjust(50, SysVgaGetRegion());

    SET_VGA_MODE_ADJUST_H_POSITION(50);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust V Position.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoVPosition(void)
{
    if(UserInterfaceVgaSkipAutoVpos() == _AUTO_CONFIG_SKIP_TRUE)
    {
        return _TRUE;
    }

    DebugMessageAnalog("7. ModeTable VH", UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVHEIGHT));
    DebugMessageAnalog("7. Measure VH", GET_ACTIVE_V_HEIGHT());
    DebugMessageAnalog("7. Measeure V Start", GET_ACTIVE_V_START());
    DebugMessageAnalog("7. IVDelay", ScalerVgaTopGetCaptureVDelay());
    DebugMessageAnalog("7. IVCapture", ScalerVgaTopGetCaptureVStartPosition());
    DebugMessageAnalog("7. CenterVposition", g_stVgaModeUserData.usCenterVPosition);
    DebugMessageAnalog("7. Measure V End", GET_ACTIVE_V_END());

    if(GET_ACTIVE_V_HEIGHT() <= UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVHEIGHT))
    {
        DebugMessageAnalog("7. Picture under Size", 0);

        if(GET_ACTIVE_V_START() < (ScalerVgaTopGetCaptureVDelay() + ScalerVgaTopGetCaptureVStartPosition()))
        {
            DebugMessageAnalog("7. Top Over", 0);

            g_stVgaModeUserData.usCenterVPosition = GET_ACTIVE_V_START();
        }
        else if(GET_ACTIVE_V_END() > (ScalerVgaTopGetCaptureVDelay() + ScalerVgaTopGetCaptureVStartPosition() + (ScalerVgaTopGetCaptureVHeight()) - 1))
        {
            DebugMessageAnalog("7. Botten Over", 0);

            g_stVgaModeUserData.usCenterVPosition = GET_ACTIVE_V_END() - (ScalerVgaTopGetCaptureVHeight()) + 1;
        }
        else
        {
            DebugMessageAnalog("7. Do Nothing", 0);

            return _TRUE;
        }
    }
    else
    {
        DebugMessageAnalog("7. Picture over Size", 0);

        g_stVgaModeUserData.usCenterVPosition = GET_ACTIVE_V_START();
    }

    if((g_stVgaModeUserData.usCenterVPosition + UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVHEIGHT)) > GET_INPUT_TIMING_VTOTAL())
    {
        DebugMessageAnalog("7. Center V Position Error", g_stVgaModeUserData.usCenterVPosition);

        g_stVgaModeUserData.usCenterVPosition = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVSTART);
    }

    UserCommonDisplayVPositionAdjust(50, SysVgaGetRegion());

    SET_VGA_MODE_ADJUST_V_POSITION(50);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust phase.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoPhase(void)
{
    BYTE ucBestPhase = 0;
    BYTE ucRoughPhase = 0;
    BYTE ucTargetPhase = 0;
    BYTE ucCounter = 0;
    DWORD ulSODTemp1 = 0;
    DWORD ulSODTemp2 = 0;
    DWORD ulSODLeft = 0;
    DWORD ulSODCenter = 0;
    DWORD ulSODRight = 0;

    if((GET_ACTIVE_H_WIDTH() > 4) && (GET_ACTIVE_V_HEIGHT() > 4))
    {
        ScalerVgaTopAutoFuncHBoundInitial((GET_ACTIVE_H_START() + 2), (GET_ACTIVE_H_END() - 2));
        ScalerVgaTopAutoFuncVBoundInitial((GET_ACTIVE_V_START() + 2), (GET_ACTIVE_V_END() - 2));
    }

    if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucRoughPhase, &ulSODTemp1, &ulSODTemp2, _PHASE_SEARCH_WSOD, 0x80) == _FALSE)
    {
        return _FALSE;
    }

    if((ulSODTemp1 / 0x80) < 100)
    {
        if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucRoughPhase, &ulSODTemp1, &ulSODTemp2, _PHASE_SEARCH_WSOD, 0x40) == _FALSE)
        {
            return _FALSE;
        }
    }

    ucTargetPhase = ((ucRoughPhase + 64 - 4) % 64);

    ulSODTemp1 = 0;
    ulSODTemp2 = 0;

    do
    {
        SysVgaWatchDog(_DISABLE);

        ScalerPLLSetPhase(ucTargetPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVFREQ));

        SysVgaWatchDog(_ENABLE);

        if(ScalerVgaTopAutoPhaseGetSOD(&ulSODTemp1) == _FALSE)
        {
            return _FALSE;
        }

        ulSODLeft = ulSODCenter;
        ulSODCenter = ulSODRight;
        ulSODRight = ulSODTemp1;

        if(ulSODCenter > (ABSDWORD(ulSODLeft, ulSODCenter) + ABSDWORD(ulSODRight, ulSODCenter)))
        {
            ulSODTemp1 = ulSODCenter - ((ABSDWORD(ulSODLeft, ulSODCenter) + ABSDWORD(ulSODRight, ulSODCenter)));
        }
        else
        {
            ulSODTemp1 = 0;
        }

        if(ulSODTemp1 > ulSODTemp2)
        {
            ulSODTemp2 = ulSODTemp1;
            ucBestPhase = ((ucTargetPhase + 64 - 2) % 64);
        }

        ucTargetPhase = ((ucTargetPhase + 2) % 64);

        ucCounter++;
    }
    while(ucCounter <= 4);

    if(ulSODTemp2 != 0x00)
    {
        g_stVgaModeUserData.ucCenterPhase = ucBestPhase;
    }
    else
    {
        g_ucVgaAutoConfigStatus |= _AUTO_CONFIG_PHASE_ABORT;
    }

    SET_VGA_MODE_ADJUST_PHASE(UserCommonDisplayRealValueToPercentAdjust(g_stVgaModeUserData.ucCenterPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER));

    SysVgaWatchDog(_DISABLE);
    ScalerPLLSetPhase(g_stVgaModeUserData.ucCenterPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVFREQ));
    SysVgaWatchDog(_ENABLE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonVgaAutoUpdateUserdata(void)
{
    // Save user data to NVRam
    UserCommonNVRamSaveModeUserData();
}

//--------------------------------------------------
// Description  : Multi times measurement.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoMeasureMultiTimes(void)
{
    BYTE ucCnt = 0;
    WORD usPreWidth = 0;
    WORD usPreHeight = 0;
    WORD usCurrClock = 0;

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usCurrClock = UserCommonDisplayPercentToRealValueAdjust(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
#else
    usCurrClock = GET_VGA_MODE_ADJUST_CLOCK();
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
#if(_OVERSCAN_SUPPORT == _TRUE)
        if(UserInterfaceDisplayGetOverScanStatus(SysVgaGetRegion()) == _OVERSCAN_TRUE)
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, usCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, usCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }

        if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
        {
            return _FALSE;
        }

        if(ucCnt > 0)
        {
            if(!((abs((GET_ACTIVE_H_WIDTH()) - usPreWidth) <= _AUTO_MULTI_MEASURE_CHECK_TOL_H) && (abs((GET_ACTIVE_V_HEIGHT()) - usPreHeight) <= _AUTO_MULTI_MEASURE_CHECK_TOL_V)))
            {
                return _FALSE;
            }
        }

        usPreWidth = GET_ACTIVE_H_WIDTH();
        usPreHeight = GET_ACTIVE_V_HEIGHT();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rough adjust clock
// Input Value  : IHTotal, Current Clock
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoClockRoughAdjust(WORD *pusCurrClock)
{
    BYTE ucCount = 10;
    WORD usPreHWidth = 0;
    bit bAdjustPhaseResult = 0;

    // Initial Htotal(clock)
    *pusCurrClock = ((GET_INPUT_TIMING_HTOTAL()) >= g_stVgaModeUserData.usCenterClock) ? (GET_INPUT_TIMING_HTOTAL()) : g_stVgaModeUserData.usCenterClock;

    do
    {
        if(UserCommonVgaAutoCheckClock(*pusCurrClock) == _FALSE)
        {
            return _FALSE;
        }

        SysVgaWatchDog(_DISABLE);

        bAdjustPhaseResult = ScalerAPLLFastLockAdjust(*pusCurrClock);

        SysVgaWatchDog(_ENABLE);

        if(bAdjustPhaseResult == _FALSE)
        {
            return _FALSE;
        }

#if(_OVERSCAN_SUPPORT == _TRUE)
        if(UserInterfaceDisplayGetOverScanStatus(SysVgaGetRegion()) == _OVERSCAN_TRUE)
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }

        if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
        {
            return _FALSE;
        }

        // exactly same --> return TRUE
        if(GET_ACTIVE_H_WIDTH() == GET_INPUT_TIMING_HWIDTH())
        {
            return _TRUE;
        }

        // Return Back Case
        if((GET_ACTIVE_H_WIDTH() + usPreHWidth) == (GET_INPUT_TIMING_HWIDTH() * 2))
        {
            return _TRUE;
        }

        usPreHWidth = GET_ACTIVE_H_WIDTH();

        ///////////////////////////////////////////////////////
        //  Measured_Width     ModeTable_Width               //
        // ---------------- = -----------------              //
        //  Current_Clock       Target_Clock                 //
        //                                                   //
        //                 ModeTable_Width * Current_Clock   //
        // Target_Clock = ---------------------------------  //
        //                         Measured_Width            //
        ///////////////////////////////////////////////////////

        PDATA_WORD(0) = ((DWORD)GET_INPUT_TIMING_HWIDTH() * (*pusCurrClock) + GET_ACTIVE_H_WIDTH() / 2) / GET_ACTIVE_H_WIDTH();

        if(PDATA_WORD(0) == *pusCurrClock)
        {
            return _TRUE;
        }
        else
        {
            *pusCurrClock = PDATA_WORD(0);
        }
    }
    while(--ucCount);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Fine tune clock
// Input Value  : IHTotal, Current Clock
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoClockFineTuneAdjust(WORD *pusCurrClock)
{
    WORD usRoughClock = 0;
    WORD usTargetClock = 0;
    WORD usBoundClock = 0;
    DWORD ulSODMax = 0;
    DWORD ulSODMin = 0;
    DWORD ulSODMaxValue = 0;
    DWORD ulSODMaxMinRatio = 0;
    BYTE ucTempPhase = 0;
    bit bAdjustPhaseResult = 0;
    BYTE ucPercentageStep = 0;
    BYTE ucCounter = 0;

    ScalerVgaTopAutoFuncHBoundInitial(GET_ACTIVE_H_START(), GET_ACTIVE_H_END());

    ScalerVgaTopAutoFuncVBoundInitial(GET_ACTIVE_V_START(), GET_ACTIVE_V_END());

    usRoughClock = *pusCurrClock;

    usTargetClock = (*pusCurrClock - ((_AUTO_TOLERANCE_PIXEL * GET_INPUT_TIMING_HTOTAL() / GET_INPUT_TIMING_HWIDTH()) + 1));

    usTargetClock = usTargetClock - ((usTargetClock % _AUTO_CLOCK_STEP));

    usBoundClock = (*pusCurrClock + ((GET_INPUT_TIMING_HTOTAL() / GET_INPUT_TIMING_HWIDTH()) + 2));

    usBoundClock = usBoundClock + ((usBoundClock % _AUTO_CLOCK_STEP));

    ucPercentageStep = ((_AUTO_CONFIG_CLOCK_FINETUNE_FINISH - _AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH) / (((usBoundClock - usTargetClock) / _AUTO_CLOCK_STEP) + 2));

    do
    {
        SysVgaWatchDog(_DISABLE);

        bAdjustPhaseResult = ScalerAPLLFastLockAdjust(usTargetClock);

        SysVgaWatchDog(_ENABLE);

        if(bAdjustPhaseResult == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucTempPhase, &ulSODMax, &ulSODMin, _PHASE_SEARCH_SOD, 0x40) == _FALSE)
        {
            return _FALSE;
        }

        DebugMessageAnalog("7. ====== Target Clock ======", usTargetClock);
        DebugMessageAnalog("7. SOG MAX", ulSODMax);
        DebugMessageAnalog("7. SOG MIN", ulSODMin);
        DebugMessageAnalog("7. SOG Ratio", (ulSODMax / ulSODMin));
        DebugMessageAnalog("7. Valid SOD Threshold", (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0x40) >> 7));

        if((ulSODMax - ulSODMin) > ulSODMaxValue)
        {
            *pusCurrClock = usTargetClock;
            ulSODMaxValue = ulSODMax - ulSODMin;

            if(ulSODMin == 0x00)
            {
                if(ulSODMax > (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0x40) >> 7))
                {
                    ulSODMaxMinRatio = 0xFFFFFFFF;
                }
                else
                {
                    ulSODMaxMinRatio = 0;
                }
            }
            else
            {
                ulSODMaxMinRatio = ulSODMax / ulSODMin;
            }
        }

        usTargetClock = usTargetClock + _AUTO_CLOCK_STEP;

        ucCounter++;

        UserInterfaceVgaGetAutoConfigPercentage((_AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH + (ucPercentageStep * ucCounter)));
    }
    while(usTargetClock <= usBoundClock);

    if(ulSODMaxValue <= (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0x40) >> 8))
    {
        if(usRoughClock == (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)))
        {
            *pusCurrClock = usRoughClock;
        }
        else
        {
            if(((usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)) % 4) == 0x00)
            {
                *pusCurrClock = (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP));
            }
            else
            {
                *pusCurrClock = (usRoughClock - (usRoughClock % _AUTO_CLOCK_STEP));
            }
        }
    }
    else if(ulSODMaxMinRatio < 5)
    {
        SysVgaWatchDog(_DISABLE);

        bAdjustPhaseResult = ScalerAPLLFastLockAdjust(*pusCurrClock);

        SysVgaWatchDog(_ENABLE);

        if(bAdjustPhaseResult == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucTempPhase, &ulSODMax, &ulSODMin, _PHASE_SEARCH_SOD, 0xA0) == _FALSE)
        {
            return _FALSE;
        }

        SysVgaWatchDog(_DISABLE);
        ScalerPLLSetPhase(ucTempPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVFREQ));
        SysVgaWatchDog(_ENABLE);

#if(_OVERSCAN_SUPPORT == _TRUE)
        if(UserInterfaceDisplayGetOverScanStatus(SysVgaGetRegion()) == _OVERSCAN_TRUE)
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }

        if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
        {
            return _FALSE;
        }

        if(ulSODMax == 0x00)
        {
            if(GET_ACTIVE_H_WIDTH() != GET_INPUT_TIMING_HWIDTH())
            {
                if(usRoughClock == (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)))
                {
                    *pusCurrClock = usRoughClock;
                }
                else
                {
                    if(((usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)) % 4) == 0x00)
                    {
                        *pusCurrClock = (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                    else
                    {
                        *pusCurrClock = (usRoughClock - (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                }
            }
        }
        else
        {
            if(ulSODMin == 0x00)
            {
                if(ulSODMax > (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0xA0) >> 9))
                {
                    ulSODMaxMinRatio = 0xFFFFFFFF;
                }
                else
                {
                    ulSODMaxMinRatio = 0;
                }
            }
            else
            {
                ulSODMaxMinRatio = (ulSODMax / ulSODMin);
            }

            DebugMessageAnalog("7. Double Check : Clock", *pusCurrClock);
            DebugMessageAnalog("7. Double Check SODMax", ulSODMax);
            DebugMessageAnalog("7. Double Check SODMin", ulSODMin);
            DebugMessageAnalog("7. Double Check : ulSODMaxMinRatio", ulSODMaxMinRatio);
            DebugMessageAnalog("7. Double Check Threshold", (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0xA0) >> 9));

            if((ulSODMaxMinRatio < 5) && ((GET_ACTIVE_H_WIDTH() != GET_INPUT_TIMING_HWIDTH())))
            {
                if(usRoughClock == (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)))
                {
                    *pusCurrClock = usRoughClock;
                }
                else
                {
                    if(((usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)) % 4) == 0x00)
                    {
                        *pusCurrClock = (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                    else
                    {
                        *pusCurrClock = (usRoughClock - (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check picture region
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoClockCheckPictureRegion(void)
{
    WORD usModeTableHWidth = 0;
    WORD usModeTableHTotal = 0;
    WORD usCurrClock = 0;

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usCurrClock = UserCommonDisplayPercentToRealValueAdjust(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
#else
    usCurrClock = GET_VGA_MODE_ADJUST_CLOCK();
#endif

    usModeTableHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IHWIDTH);
    usModeTableHTotal = UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IHTOTAL);

    /////////////////////////////////////////////////////
    //   Actvie HWidth        ModeTable_Width          //
    // (---------------) >= (----------------- x 95% ) //
    //   Current Clock        ModeTable_HTotal         //
    /////////////////////////////////////////////////////

    if(((DWORD) usModeTableHTotal * GET_ACTIVE_H_WIDTH()) >= (((DWORD)_AUTO_CLOCK_RANGE * usModeTableHWidth * usCurrClock) / 100))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check current Clock(IHTotal) region
// Input Value  : Current Clock (IHTotal)
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonVgaAutoCheckClock(WORD usCurrClock)
{
    WORD usCaptureHStart = 0;

    usCaptureHStart = ScalerVgipGetCaptureHStartPosition();

    if(((usCaptureHStart + GET_INPUT_TIMING_HWIDTH()) <= usCurrClock) && (usCurrClock <= GET_ADC_LIMIT_CLOCK()))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : ADC AutoWhiteBalance
// Input Value  : enumAutoType -> auto color for RGB / YPbPr / Self-calibration
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult UserCommonVgaAutoDoWhiteBalance(EnumAutoColorType enumAutoType)
{
    return ScalerVgaAutoDoWhiteBalance(enumAutoType);
}

//--------------------------------------------------
// Description  : Return the auto-color result
// Input Value  : stAdcData -> ADC data structure pointer
// Output Value : None
//--------------------------------------------------
void UserCommonVgaAutoGetAutoColorResult(StructAdcDataType *pstAdcData)
{
    ScalerVgaAutoGetAutoColorResult(pstAdcData);
}

//--------------------------------------------------
// Description  : Measure color min/max from specific channel
// Input Value  : ucColor --> R/G/B
//                pucResult --> memory to store measure result
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
EnumAutoResult UserCommonVgaAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult)
{
    return ScalerVgaAutoMeasureColorValue(ucColor, bSelectMax, pucResult);
}

#if(_YPBPR_SUPPORT == _ON)
#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA)
//--------------------------------------------------
// Description  : Calculate ADC gain/offset for YPbPr from RGB auto-color result
// Input Value  : stAdcData: balanced gain/offset for RGB
// Output Value : balanced gain/offset for YPbPr from calculation
//--------------------------------------------------
StructAdcDataType UserCommonVgaAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData)
{
    return ScalerVgaAutoBalanceYPbPrFromFormula(pstAdcData);
}
#endif
#endif

/*
void UserCommonVgaAutoPhaseTestFunction(void)
{
    BYTE ucCounter = 0;
    DWORD ulSODValue = 0;

    for(ucCounter=0; ucCounter < 64; ucCounter++)
    {
        ScalerRegionSetWatchDog(_DISABLE);
        ScalerPLLSetPhase(ucCounter, UserCommonModeSearchGetModetableTimingDataItem(g_stVgaModeUserData.ucModeNumber, _IVFREQ));
        ScalerRegionSetWatchDog(_ENABLE);

        ScalerVgaTopAutoPhaseGetSOD(&ulSODValue);

        DebugMessageAnalog("7. SOD", ulSODValue);
    }
}
*/
#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get VGATOP Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD UserCommonVgaGetCaptureHDelay(void)
{
    return ScalerVgaTopGetCaptureHDelay();
}

//--------------------------------------------------
// Description  : Set VGATOP Capture H Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void UserCommonVgaSetCaptureHDelay(WORD usIHSDelay)
{
    ScalerVgaTopSetCaptureHDelay(usIHSDelay);
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD UserCommonVgaGetCaptureVDelay(void)
{
    return ScalerVgaTopGetCaptureVDelay();
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void UserCommonVgaSetCaptureVDelay(WORD usIVSDelay)
{
    ScalerVgaTopSetCaptureVDelay(usIVSDelay);
}

//--------------------------------------------------
// Description  : Apply double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonVgaDoubleBufferApply(void)
{
    ScalerVgaTopDoubleBufferApply();
}
#endif

#endif

