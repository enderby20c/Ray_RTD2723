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
// ID Code      : RTD2020UserInterfaceColorLocalDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_COLORLOCALDIMMING__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColorLocalDimming.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
bit g_bColorLocalDimmingHdrBoost = _TRUE;
BYTE g_ucColorLocalDimmingLastApplyBoostGain = 100;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_LOCAL_DIMMING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : get Local dimming data
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void UserInterfaceColorLocalDimmingGetData(StructLocalDimmingSetting *pstLocalDimmingData)
{
    if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
    {
        pstLocalDimmingData->enumLocalDimmingMode = _LOCAL_DIMMING_ON;
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.ucSmoothLevel = GET_OSD_LD_ADJ();
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.ucStepChangeLevel = 68;
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.ucOSDStepChangeLevel = 30;

        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.b1OSDCurrentPWMEnable = _DISABLE;

#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
        if(GET_OSD_ENERGY_SAVER() == _ON)
        {
            pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.enumLocalDimmingCase = _LOCAL_DIMMING_ENERGYSAVER;
        }
        else
#endif
        {
            pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.enumLocalDimmingCase = _LOCAL_DIMMING_DISPLAYHDR;
        }
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.ucLocalDimmingSmoothParaSel = 0;
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.b1TotalWorBOneStep = _TRUE;
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usPictureBNWTH = 995;
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usPictureBlackTH = 950;
#endif
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usMinBlendPWMValue = 21; // 32; // usMinBlendPWMValue means the lowest PWM value on a scale of 0 to 4095 (0 ~ 4095 map to 0 ~ PWM Max)
#endif
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usAvgStepFrac = 812;  // 0~ 1024
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usPercentileStepFrac = 212; // 0~ 1024
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usAvgBlackValue = 45; // 0~ 4095
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usAvgBlackStep = 600; // 0~ 1024
#endif
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.b1BoostContrastModeEnable = _ENABLE;
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usRegionBoostAdimStep = 10; // Max : 1000
        pstLocalDimmingData->unLocalDimmingData.stLocalDimmingData.usRegionBoostGainStep = 10; // Max : 1000
#endif
    }
    else
    {
        pstLocalDimmingData->enumLocalDimmingMode = _LOCAL_DIMMING_OFF;
    }
}

//--------------------------------------------------
// Description  : Restore backlight
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void UserInterfaceColorLocalDimmingRestoreBacklight(void)
{
#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON))
    ExternalDeviceInterfaceLedDriverBoostAdjust(100);
#endif

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(_DISPLAY_RGN_1P) != _HDR10_OFF)
    {
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
        if(UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus() == _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_MAX)
#endif
        {
            UserAdjustBacklight(_BACKLIGHT_MAX);
            return;
        }
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(_DISPLAY_RGN_1P) == _ON)
    {
        UserAdjustBacklight(_BACKLIGHT_MAX);
        return;
    }
#endif
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
}

//--------------------------------------------------
// Description  : Local Dimming must support in OGC/OCC
// Input Value  : None
// Output Value : _LOCAL_DIMMING_ENABLE/ _LOCAL_DIMMING_DISABLE
//--------------------------------------------------
EnumLocalDimmingStatus UserInterfaceColorLocalDimmingGetEnableStatus(void)
{
    if(GET_OSD_LOCAL_DIMMING() != _ON)
    {
        return _LOCAL_DIMMING_DISABLE;
    }
#if(_SDR_TO_HDR_FUNCTION == _ON)
    // SDRtoHDR can support local dimming
    if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
    {
        return _LOCAL_DIMMING_DISABLE;
    }
#endif

    return _LOCAL_DIMMING_ENABLE;
}

//--------------------------------------------------
// Description  : local dimming mode choose when display 2P
// Input Value  : None
// Output Value : EnumLocalDimmingType
//--------------------------------------------------
EnumLocalDimmingType UserInterfaceColorLocalDimmingMultiPPolicy(void)
{
    return _LOCAL_DIMMING_SDR;
}

#if(_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE)
//--------------------------------------------------
// Description  : decide the compensate value of Adim or Ddim
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE UserInterfaceColorLocalDimmingBoostGetCompADdim(void)
{
    if(GET_LOCAL_DIMMING_FULL_PATTERN() == _TRUE)
    {
        return 100;
    }

    return _LOCAL_DIMMING_MAX_COMPENSATE_GAIN;
}
#endif

#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : When Local Dimming Boost mode active,
//                user need to judge whether need to cooling accirding to total PWM ratio
// Input Value  : ucBoostGain: Kernal recommend boost Gain value
//                ucPWMTotalRatio: 0~ 100, for judge cooling time
// Output Value : BoostGain: Apply Boost Value = (Default A Dim value) * (BoostGain / 100)
//--------------------------------------------------
BYTE UserInterfaceColorLocalDimmingBoostCoolingAdjust(BYTE ucBoostGain, BYTE ucPWMTotalRatio)
{
    g_ucColorLocalDimmingLastApplyBoostGain = UserCommonColorLocalDimmingBoostGetLastKernelBoostValue();
    if(ucPWMTotalRatio > _LOCAL_DIMMING_BOOST_COOLING_PWM_RATIO) // need to cooling
    {
        if(g_bColorLocalDimmingHdrBoost == _TRUE)
        {
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_COOL);

            if(ucBoostGain > 100)
            {
                ucBoostGain = ((g_ucColorLocalDimmingLastApplyBoostGain + 1) > ucBoostGain) ? ucBoostGain : (g_ucColorLocalDimmingLastApplyBoostGain + 1);
                UserCommonTimerActiveTimerEvent(SEC(_LOCAL_DIMMING_BOOST_ACTIVE_TIME), _USER_TIMER_EVENT_HDR_BOOST);
            }
            else
            {
                UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_BOOST);
            }
        }
        else
        {
            ucBoostGain = ((g_ucColorLocalDimmingLastApplyBoostGain - 1) < 100) ? 100 : (g_ucColorLocalDimmingLastApplyBoostGain - 1);
            DebugMessageHDR("cooling", ucBoostGain);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_BOOST);
            UserCommonTimerActiveTimerEvent(SEC(_LOCAL_DIMMING_BOOST_COOLING_TIME), _USER_TIMER_EVENT_HDR_COOL);
        }
    }
    else
    {
        if(ucBoostGain > g_ucColorLocalDimmingLastApplyBoostGain)
        {
            ucBoostGain = ((g_ucColorLocalDimmingLastApplyBoostGain + 1) > ucBoostGain) ? ucBoostGain : (g_ucColorLocalDimmingLastApplyBoostGain + 1);
        }
        else if(ucBoostGain < g_ucColorLocalDimmingLastApplyBoostGain)
        {
            ucBoostGain = ((g_ucColorLocalDimmingLastApplyBoostGain - 1) < 100) ? 100 : (g_ucColorLocalDimmingLastApplyBoostGain - 1);
        }
    }

    return ucBoostGain;
}
#endif

#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

