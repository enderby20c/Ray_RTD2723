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
// ID Code      : UserCommonColorLocalDimming.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_COLOR_LOCAL_DIMMING__

#include "UserCommonInclude.h"
#include "ColorLocalDimming/UserCommonColorLocalDimming.h"

#if(_LOCAL_DIMMING_FUNCTION == _ON)

#if(_LOCAL_DIMMING_HISTO_BLACK_LSB_SUPPORT == _ON)
#warning "NOTE: Please Check the ID Code(Contact with SDs) When _LOCAL_DIMMING_HISTO_BLACK_LSB_SUPPORT _ON!!!"
#endif

#if((_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON) && (_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _OFF) && (_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _OFF))
#warning "NOTE: _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS Should be _ON when PWM Period of Driver is not be protected !!! (ex: AMS Seires Driver IC without Dimming PP method)"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON))
WORD code tLDHDR2084Lv[256] =
{
#include _LOCAL_DIMMING_HDR_2084_LV
};
#endif
#if(_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON)
WORD code tFREESYNCIILv[256] =
{
#include _LOCAL_DIMMING_FREESYNC_II_LV
};
#endif

#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
WORD code tLDSDRLv[256] =
{
#include _LOCAL_DIMMING_SDR_LV
};
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
WORD code tBoostAreaData[][_LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE + 1] =
{
#include _LOCAL_DIMMING_REGION_BOOST_TABLE
};

WORD code tMaxRGBBeamCode[] =
{
    16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256
};

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
BYTE code tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[] =
{
#include _LOCAL_DIMMING_PWM2SPI_ADIM_DATA_NUM
};
#endif
#endif

BYTE code tEntropyTable[101] =
{
    0, 6, 11, 15, 18, 21, 24, 26, 29, 31, 33, 35, 36, 38,
    39, 41, 42, 43, 44, 45, 46, 47, 48, 48, 49, 50, 50, 51,
    51, 51, 52, 52, 52, 52, 52, 53, 53, 53, 53, 52, 52, 52,
    52, 52, 52, 51, 51, 51, 50, 50, 50, 49, 49, 48, 48, 47,
    46, 46, 45, 44, 44, 43, 42, 41, 41, 40, 39, 38, 37, 36,
    36, 35, 34, 33, 32, 31, 30, 29, 27, 26, 25, 24, 23, 22,
    21, 19, 18, 17, 16, 14, 13, 12, 11, 9, 8, 7, 5, 4,
    2, 1, 0,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLastRegionAdim")))
WORD g_pusColorLastRegionAdim[_LOCAL_DIMMING_TOTAL_REGION];

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLastRegionGain")))
WORD g_pusColorLastRegionGain[_LOCAL_DIMMING_TOTAL_REGION];

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pucColorCurrentHistoIndex")))
BYTE g_pucColorCurrentHistoIndex[_LOCAL_DIMMING_TOTAL_REGION];

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pucColorLastHistoIndex")))
BYTE g_pucColorLastHistoIndex[_LOCAL_DIMMING_TOTAL_REGION];
#endif

#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLocalDimmingAvgY")))
WORD g_pusColorLocalDimmingAvgY[_LOCAL_DIMMING_TOTAL_REGION];

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLastLocalDimmingAvgY")))
WORD g_pusColorLastLocalDimmingAvgY[_LOCAL_DIMMING_TOTAL_REGION];
#endif

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorApplyPWM")))
WORD g_pusColorApplyPWM[_LOCAL_DIMMING_TOTAL_REGION];

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLastApplyPWM")))
WORD g_pusColorLastApplyPWM[_LOCAL_DIMMING_TOTAL_REGION];

__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLastHistoPWM")))
WORD g_pusColorLastHistoPWM[_LOCAL_DIMMING_TOTAL_REGION];

#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
__attribute__((section(_FW_LD_GLOBAL_VARIABLE_DEFAULT_BSS_SECTION "g_pusColorLastBlendPWM")))
WORD g_pusColorLastBlendPWM[_LOCAL_DIMMING_TOTAL_REGION];
#endif
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
StructLocalDimmingLocalAdim g_stColorLDRegionBoost;
#endif

#if((_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT) || (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE))
WORD g_pusColorHistoPWM[_LOCAL_DIMMING_TOTAL_REGION];
#endif

StructLocalDimmingFWCtrl g_stColorLocalDimmingFWCtrl;


StructLocalDimmingPerformanceAdjust g_stColorLocalDimmingPerformanceAdjust;
StructLocalDimmingDCRData g_stColorLocalDimmingDCRData;
StructLocalDimmingPictureType g_stColorLocalDimmingPictureType;
StructLocalDimmingPWMType g_stColorLocalDimmingPWMType;
bit g_bColorLocalDimmingBackLightModelFirstON;
StructLocalDimmingBLMSoftClampPara g_stColorLocalDimmingBLMSoftClampPara;
volatile StructLocalDimmingKCPUStateValue g_stColorLocalDimmingKCPUStateValue;

StructLocalDimmingExternInfo g_stColorLocalDimmingExternInfo;

#if((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
volatile BYTE g_ucColorApplyCurrentAdim;
#endif

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
StructLocalDimmingHDR10BoostData g_stColorLocalDimmingHDR10BoostData;
#endif

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
WORD g_pusColorHistoPWM2[_LOCAL_DIMMING_TOTAL_REGION];
EnumColorLocalDimmingHistoStage g_enumColorPWMHistoStage;
#endif

StructLocalDimmingSceneData g_stColorLocalDimmingSceneData;
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
StructLocalDimmingApplyData g_stColorLocalDimmingApplyData;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingHandler(void)
{
    if(g_stColorLocalDimmingKCPUStateValue.enumLocalDimmingStatus == _LOCAL_DIMMING_ENABLE)
    {
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
        // DebugMessageHDR("LD enable", 0);
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
        UserCommonColorLocalDimmingProcess();
#else
        UserCommonColorLocalDimmingMultiTimeApplyProcess();
#endif
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
        if(g_bSpiDimmingSramModeStartTxResult == _FALSE)
        {
            g_bSpiDimmingSramModeStartTxResult = ScalerSpiDimmingLDSramModeStartTX();
        }
#endif
#endif
    }
}
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingProcess(void)
{
    DebugMessageHDR("g_enumColorLocalDimmingProcessStage", GET_LOCAL_DIMMING_FW_PROCESS_STAGE());
    switch(GET_LOCAL_DIMMING_FW_PROCESS_STAGE())
    {
        case _LOCAL_DIMMING_FW_HISTOGRAM:
            if(GET_LOCAL_DIMMING_HISTOGRAM_DONE() == _FALSE)
            {
                if(ScalerColorLDPWMProcSramSwitchStatus(_NOT_WAIT) == _TRUE)
                {
                    // read histogram value
                    UserCommonColorLocalDimmingAdjustFWMode();

#if(_LOCAL_DIMMING_ADIM_MODIFY_SUPPORT == _ON)
                    UserCommonColorLocalDimmingLocalAdimModify();
#endif

                    ScalerColorLDPWMProcSramSwitchApply();
                    SET_LOCAL_DIMMING_HISTOGRAM_DONE(_TRUE);
                }
            }

            if(GET_LOCAL_DIMMING_HISTOGRAM_DONE() == _TRUE)
            {
                if(ScalerColorLDPWMProcSramSwitchStatus(_WAIT) == _TRUE)
                {
                    if((ScalerOsdGetOsdEnable() == _OFF) || (g_stColorLocalDimmingPerformanceAdjust.b1ColorOsdCurrentPWMEnable == _ENABLE))
                    {
                        // FW smooth start
                        UserCommonColorLocalDimmingSmoothFWMode(); // seperated smooth and step
                    }
                    else
                    {
                        UserCommonColorLocalDimmingOSDPWMAdjust();
                        SET_LOCAL_DIMMING_SC_TYPE(_LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL);
                    }
                    ScalerColorLDPWMProcSramSwitchApply();
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
                    // set PWM Regions to more regions
                    UserCommonColorLocalDimmingPWMProcChangeHVRegion(_LOCAL_DIMMING_REGION_TYPE_UP);
#endif
                    // ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
#if((_LOCAL_DIMMING_ADIM_MODIFY_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
                    if(GET_MBR_BACKLIGHT_MODE() == _BACKLIGHT_MODE_CONSTANT)
#endif
                    {
                        UserCommonColorLocalDimmingLocalAdimSendCommand();
                    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_MANUAL_MODE == _ON)
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX == _OFF)
                    // clear apply done flag first
                    ScalerColorLDPwmToSpiAckUpdSyncApplyDone();
                    // Manual Apply UpdSync
                    ScalerColorLDPwmToSpiManualApplyUpdSync();
#endif
#endif
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_PWMSTEP);
                }
                else
                {
                    DebugMessageHDR("smooth polling failed", 0);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_FAIL);
                }
            }
            break;

        case _LOCAL_DIMMING_FW_PWMSTEP:

            if((GET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON() == _TRUE) || (UserCommonColorLocalDimmingPWMStepFW() == _TRUE))
            {
                ScalerColorLDPwmToSpiAckUpdSyncApplyDone();

                ScalerColorLDPwmToSpiAckNewSpiTxDoneFlag();

#if((_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
                UserCommonColorLocalDimmingMBRAdimAdjust();
#endif

#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
                WORD pusPWMAdjustCurve[1] = {256};
                WORD pusApplyPWM[_LOCAL_DIMMING_TOTAL_REGION] = {0};
                WORD pusLastPWM[_LOCAL_DIMMING_TOTAL_REGION] = {0};

                // apply blending
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
                UserCommonColorLocalDimmingBlendPWMUsingYavg(g_pusColorApplyPWM, g_pusColorHistoPWM, pusApplyPWM, g_stColorLocalDimmingPerformanceAdjust.usMinBlendPWMValue);
#else
                UserCommonColorLocalDimmingBlendPWM(g_pusColorApplyPWM, g_pusColorHistoPWM, pusApplyPWM, g_stColorLocalDimmingSceneData, g_stColorLocalDimmingPerformanceAdjust.usMinBlendPWMValue);
#endif
                memcpy(g_pusColorLastBlendPWM, pusApplyPWM, sizeof(g_pusColorHistoPWM));
#else
                memcpy(pusApplyPWM, g_pusColorApplyPWM, sizeof(pusApplyPWM));
#endif

                // apply compensation
#if (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_DDIM)
                UserCommonColorLocalDimmingCompByDdim(pusApplyPWM);
                memcpy(pusLastPWM, pusApplyPWM, sizeof(pusApplyPWM));
#else
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
                memcpy(pusLastPWM, g_pusColorLastBlendPWM, sizeof(pusLastPWM));
#else
                memcpy(pusLastPWM, g_pusColorLastApplyPWM, sizeof(pusLastPWM));
#endif
#endif
                // update SRAM mode data and total PWM ratio
                ScalerSpiDimmingLDUpdateSramModeData(pusApplyPWM, pusLastPWM, pusPWMAdjustCurve, _TRUE);
                SET_LOCAL_DIMMING_PWM_TOTAL_RATIO(ScalerColorLDPWMAbilityRatio(pusApplyPWM, _LOCAL_DIMMING_TOTAL_REGION));
#endif
                if(GET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON() == _FALSE)
                {
                    ScalerColorLDBLModelGainApplyDoneClear();
                }
                ScalerColorLDStepHWDoneClear();
                SET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON(_FALSE);
                if(UserCommonColorLocalDimmingCheckStatusBeforeBLFW() == _TRUE)
                {
                    ScalerColorLDBLModelManualSwitchApply();
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_HISTOGRAM);
                    SET_LOCAL_DIMMING_HISTOGRAM_DONE(_FALSE);
                    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
                }
                else
                {
                    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(1);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_BACKLIGHTMODEL);
                }
            }
            break;

        case _LOCAL_DIMMING_FW_BACKLIGHTMODEL:
            if(UserCommonColorLocalDimmingCheckStatusBeforeBLFW() == _TRUE)
            {
                ScalerColorLDBLModelManualSwitchApply();
                SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_HISTOGRAM);
                SET_LOCAL_DIMMING_HISTOGRAM_DONE(_FALSE);
                SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
            }
            else
            {
                BYTE ucBLModelPollingTime = GET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT();
                SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(ucBLModelPollingTime + 1);
                if(GET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT() > _LOCAL_DIMMING_BLMODEL_POLLING_COUNT_MAX)
                {
                    DebugMessageHDR("BL model polling failed", 0);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_FAIL);
                    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
                }
            }
            break;

        case _LOCAL_DIMMING_FW_FAIL:
            if(g_stColorLocalDimmingKCPUStateValue.enumLocalDimmingStatus == _LOCAL_DIMMING_ENABLE)
            {
                UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
            }
            break;

        default:
            break;
    }
}
#else
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingMultiTimeApplyProcess(void)
{
    DebugMessageHDR("g_enumColorLocalDimmingProcessStage", GET_LOCAL_DIMMING_FW_PROCESS_STAGE());
    switch(GET_LOCAL_DIMMING_FW_PROCESS_STAGE())
    {
        case _LOCAL_DIMMING_FW_HISTOGRAM:
            if(GET_LOCAL_DIMMING_HISTOGRAM_DONE() == _FALSE)
            {
                if(ScalerColorLDPWMProcSramSwitchStatus(_NOT_WAIT) == _TRUE)
                {
                    // read histogram value
                    UserCommonColorLocalDimmingAdjustFWMode();
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
                    UserCommonColorLocalDimmingBoostModify();
#endif
                    ScalerColorLDPWMProcSramSwitchApply();
                    SET_LOCAL_DIMMING_HISTOGRAM_DONE(_TRUE);
                }
            }

            if(GET_LOCAL_DIMMING_HISTOGRAM_DONE() == _TRUE)
            {
                if(ScalerColorLDPWMProcSramSwitchStatus(_WAIT) == _TRUE)
                {
                    if((ScalerOsdGetOsdEnable() == _OFF) || (g_stColorLocalDimmingPerformanceAdjust.b1ColorOsdCurrentPWMEnable == _ENABLE))
                    {
                        // FW smooth start
                        UserCommonColorLocalDimmingSmoothFWMode();
                        // FW smooth end
                    }
                    else
                    {
                        UserCommonColorLocalDimmingOSDPWMAdjust();
                        SET_LOCAL_DIMMING_SC_TYPE(_LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL);
                    }
                    ScalerColorLDPWMProcSramSwitchApply();
                    // ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_PWMSTEP);
                }
                else
                {
                    DebugMessageHDR("smooth polling failed", 0);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_FAIL);
                }
            }
            break;

        case _LOCAL_DIMMING_FW_PWMSTEP:

            if((GET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON() == _TRUE) || (UserCommonColorLocalDimmingPWMStepFW() == _TRUE))
            {
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
                WORD pusPWMAdjustCurve[2] = {128, 256};
                ScalerSpiDimmingLDUpdateSramModeData(g_pusColorApplyPWM, g_pusColorLastApplyPWM, pusPWMAdjustCurve, _TRUE);
#endif
                SET_LOCAL_DIMMING_PWM_TOTAL_RATIO(ScalerColorLDPWMAbilityRatio(g_pusColorApplyPWM, _LOCAL_DIMMING_TOTAL_REGION));
                UserCommonColorLocalDimmingSoftClampAdjust();
                if(GET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON() == _FALSE)
                {
                    ScalerColorLDBLModelGainApplyDoneClear();
                }
                ScalerColorLDStepHWDoneClear();
                SET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON(_FALSE);
                if(UserCommonColorLocalDimmingCheckStatusBeforeBLFW() == _TRUE)
                {
                    ScalerColorLDBLModelManualSwitchApply();
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_HISTOGRAM);
                    SET_LOCAL_DIMMING_HISTOGRAM_DONE(_FALSE);
                    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
                }
                else
                {
                    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(1);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_BACKLIGHTMODEL);
                }
            }
            break;
        case _LOCAL_DIMMING_FW_BACKLIGHTMODEL:
            if(UserCommonColorLocalDimmingCheckStatusBeforeBLFW() == _TRUE)
            {
                ScalerColorLDBLModelManualSwitchApply();
                SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_HISTOGRAM);
                SET_LOCAL_DIMMING_HISTOGRAM_DONE(_FALSE);
                SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
            }
            else
            {
                BYTE ucBLModelPollingTime = GET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT();
                SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(ucBLModelPollingTime + 1);
                if(GET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT() > _LOCAL_DIMMING_BLMODEL_POLLING_COUNT_MAX)
                {
                    DebugMessageHDR("BL model polling failed", 0);
                    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_FAIL);
                    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
                }
            }
            break;
        case _LOCAL_DIMMING_FW_FAIL:
            UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit UserCommonColorLocalDimmingPWMStepFW(void)
{
    if(ScalerColorLDStepHWDone() == _FALSE)
    {
        return _FALSE;
    }
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
    if(ScalerColorLDPwmToSpiCheckUpdSyncApplyDone() == _FALSE)
    {
        return _FALSE;
    }
#endif

    if(ScalerColorLDBLModelGainApplyDone() == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingAdjustFWMode(void)
{
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _OFF)
    // Load Histogram value
    memcpy(g_pusColorLastHistoPWM, g_pusColorHistoPWM, sizeof(g_pusColorHistoPWM));
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
    WORD pusColorHistoPWMUP[_LOCAL_DIMMING_TOTAL_REGION_UP] = {0};
    ScalerColorLDPWMProcReadPWMTable(pusColorHistoPWMUP, _LOCAL_DIMMING_TOTAL_REGION_UP);
    UserCommonColorLocalDimmingPWMProcChangeHVRegion(_LOCAL_DIMMING_REGION_TYPE_NORMAL);
    if(GET_LOCAL_DIMMING_CASE() == _LOCAL_DIMMING_ENERGYSAVER)
    {
        UserCommonColorLocalDimmingLowerPowerPWMEdgeType(pusColorHistoPWMUP, g_pusColorHistoPWM);
    }
    else
    {
        UserCommonColorLocalDimmingCombineHistoPWM(g_pusColorHistoPWM, pusColorHistoPWMUP);
    }
#else
    ScalerColorLDPWMProcReadPWMTable(g_pusColorHistoPWM, _LOCAL_DIMMING_TOTAL_REGION);
#endif
    UserCommonColorLocalDimmingSceneAnalysis(g_pusColorHistoPWM, g_pusColorLastHistoPWM, &g_stColorLocalDimmingSceneData);

    DebugMessageHDR("Etropy", g_stColorLocalDimmingSceneData.usEntropy);
    memcpy(g_pusColorApplyPWM, g_pusColorHistoPWM, sizeof(g_pusColorHistoPWM));
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
    memcpy(g_pusColorLastLocalDimmingAvgY, g_pusColorLocalDimmingAvgY, sizeof(g_pusColorLocalDimmingAvgY));
    UserCommonColorLocalDimmingGetYAVG(g_pusColorLocalDimmingAvgY);
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
    if(GET_LOCAL_DIMMING_CASE() == _LOCAL_DIMMING_ENERGYSAVER)
    {
        UserCommonColorLocalDimmingLowerPowerPWMDirectType(g_pusColorHistoPWM, g_pusColorLocalDimmingAvgY);
        memcpy(g_pusColorApplyPWM, g_pusColorHistoPWM, sizeof(g_pusColorHistoPWM));
    }
    else
#endif
#endif
    {
        UserCommonColorLocalDimmingApplyDegree(g_pusColorApplyPWM, g_stColorLocalDimmingSceneData);
    }
#endif
    ScalerColorLDPWMProcWritePWMTable(g_pusColorApplyPWM, _LOCAL_DIMMING_TOTAL_REGION, GET_CURRENT_BANK_NUMBER());
#else

    if(g_enumColorPWMHistoStage == _LOCAL_DIMMING_HISTO_THD_HIGH)
    {
        // Load Histogram value
        memcpy(g_pusColorLastHistoPWM, g_pusColorHistoPWM, sizeof(g_pusColorHistoPWM));
        ScalerColorLDPWMProcReadPWMTable(g_pusColorHistoPWM, _LOCAL_DIMMING_TOTAL_REGION);
        ScalerColorLDHistoSetTHD(g_ucColorHistoTHdLow);
        memcpy(g_pusColorApplyPWM, g_pusColorHistoPWM, sizeof(g_pusColorHistoPWM));
    }
    else if(g_enumColorPWMHistoStage == _LOCAL_DIMMING_HISTO_THD_LOW)
    {
        ScalerColorLDPWMProcReadPWMTable(g_pusColorHistoPWM2, _LOCAL_DIMMING_TOTAL_REGION);
        ScalerColorLDHistoSetTHD(g_ucColorHistoTHdHigh);
    }
#endif
    EnumLDPictureType enumLDPWMPicutreType = UserCommonColorLocalDimmingGetPictureType(g_pusColorHistoPWM, &g_stColorLocalDimmingSceneData);
    SET_LOCAL_DIMMING_PICTURE_TYPE(enumLDPWMPicutreType);
    g_stColorLocalDimmingPWMType.enumSmoothType = UserCommonColorLocalDimmingSmoothEffectAdjust(enumLDPWMPicutreType);
    g_stColorLocalDimmingPWMType.enumStepChangeType = UserCommonColorLocalDimmingStepChangeEffectAdjust(enumLDPWMPicutreType);
    g_stColorLocalDimmingDCRData.ulColorLastBlackNum = g_stColorLocalDimmingDCRData.ulColorCurrentBlackNum;
    g_stColorLocalDimmingDCRData.ulColorLastWhiteNum = g_stColorLocalDimmingDCRData.ulColorCurrentWhiteNum;
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    g_stColorLocalDimmingDCRData.ulColorLastMaxRNum = g_stColorLocalDimmingDCRData.ulColorMaxRNum;
    g_stColorLocalDimmingDCRData.ulColorLastMaxGNum = g_stColorLocalDimmingDCRData.ulColorMaxGNum;
    g_stColorLocalDimmingDCRData.ulColorLastMaxBNum = g_stColorLocalDimmingDCRData.ulColorMaxBNum;
#endif
}


//--------------------------------------------------
// Description  : Choose smooth effect based on picture, define and so on
//
// Input Value  :
//
// Output Value :
//--------------------------------------------------
EnumLDSmoothType UserCommonColorLocalDimmingSmoothEffectAdjust(EnumLDPictureType enumLDPictureType)
{
    enumLDPictureType = enumLDPictureType;

#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
    if(GET_LOCAL_DIMMING_CASE() == _LOCAL_DIMMING_ENERGYSAVER)
    {
        return _LOCAL_DIMMING_SMOOTH_TYPE_EXCEPT_BLACK;
    }
#endif

#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
    if(enumLDPictureType == _LOCAL_DIMMING_PICTURE_NEARLY_BLACK) // center pattern
    {
        return ((_LOCAL_DIMMING_BLACK_SMOOTH_MODE == _ON) ? _LOCAL_DIMMING_SMOOTH_TYPE_ON : _LOCAL_DIMMING_SMOOTH_TYPE_EXCEPT_BLACK);
    }
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
    if(enumLDPictureType == _LOCAL_DIMMING_PICTURE_CORNER) // corner pattern
    {
        return UserCommonColorLocalDimmingGetCornerSmoothMode();
    }
#endif

    return _LOCAL_DIMMING_SMOOTH_TYPE_ON;
}
//--------------------------------------------------
// Description  : Choose Step change effect based on picture, define and so on
//
// Input Value  :
//
// Output Value :
//--------------------------------------------------
EnumLDStepChangeType UserCommonColorLocalDimmingStepChangeEffectAdjust(EnumLDPictureType enumLDPictureType)
{
    switch(enumLDPictureType)
    {
        case _LOCAL_DIMMING_PICTURE_TOTAL_BLACK:
        case _LOCAL_DIMMING_PICTURE_TOTAL_WHITE:
            if(g_stColorLocalDimmingPerformanceAdjust.b1ColorTotalWorBOneStep == _TRUE)
            {
                return _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP;
            }

            return _LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL;

#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
        case _LOCAL_DIMMING_PICTURE_NEARLY_BLACK:
            return _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP;
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
        case _LOCAL_DIMMING_PICTURE_CORNER:
            return _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP;
#endif
        case _LOCAL_DIMMING_PICTURE_WHITE_AND_BLACK:
#if(_LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT == _ON)
        case _LOCAL_DIMMING_PICTURE_ELSE_ONE_STEP:
#endif
            return _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP;

        default:
            return _LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL;
    }
}

//-----------------------------------------------------
// Description  : Local Dimming Get Smooth type of Corner Pattern
// Input Value  : void
// Output Value : EnumLDSmoothType
//-----------------------------------------------------
EnumLDSmoothType UserCommonColorLocalDimmingGetCornerSmoothMode(void)
{
    if(_LOCAL_DIMMING_BLACK_SMOOTH_MODE == _ON)
    {
        if(_LOCAL_DIMMING_ADAPTIVE_SMOOTH_SUPPORT == _OFF)
        {
            return _LOCAL_DIMMING_SMOOTH_TYPE_ON;
        }
        else
        {
            return _LOCAL_DIMMING_SMOOTH_TYPE_OFF;
        }
    }
    else
    {
        return _LOCAL_DIMMING_SMOOTH_TYPE_EXCEPT_BLACK;
    }
}


//-----------------------------------------------------
// Description  :  Local Dimming get Picture Type based on DCR or Histogram data
// Input Value  :  pusColorHistoPWM
// Output Value :  EnumLDPictureType
//-----------------------------------------------------
EnumLDPictureType UserCommonColorLocalDimmingGetPictureType(WORD *pusColorHistoPWM, const StructLocalDimmingSceneData *pstLocalDimmingSceneData)
{
    DWORD ulpanelsize = ((DWORD)_PANEL_DH_WIDTH) * ((DWORD)_PANEL_DV_HEIGHT);
    DWORD ulCurrentTotalBlack = ulpanelsize - pstLocalDimmingSceneData->ulBlackNum;

    SET_LOCAL_DIMMING_BLACK_RATIO((BYTE)(ulCurrentTotalBlack * 100 / _PANEL_DH_WIDTH / _PANEL_DV_HEIGHT));

    if(UserCommonColorLocalDimmingCheckFullPattern(pstLocalDimmingSceneData) == _TRUE)
    {
        SET_LOCAL_DIMMING_FULL_PATTERN(_TRUE);
    }
    else
    {
        SET_LOCAL_DIMMING_FULL_PATTERN(_FALSE);
    }

    if(pstLocalDimmingSceneData->ulWhiteNum == ulpanelsize)
    {
        return _LOCAL_DIMMING_PICTURE_TOTAL_WHITE;
    }
    else if(pstLocalDimmingSceneData->ulBlackNum == 0)
    {
        return _LOCAL_DIMMING_PICTURE_TOTAL_BLACK;
    }
    else
    {
        DWORD ulLastTotalBlack = ulpanelsize - pstLocalDimmingSceneData->ulLastBlackNum;
        DWORD ulTotalWandBTHD = (ulpanelsize / 1000 * (DWORD)g_stColorLocalDimmingPerformanceAdjust.usColorPictureBNWTH);
        DWORD ulTotalCornerTHD = (ulpanelsize / 1000 * _LOCAL_DIMMING_CORNER_WANDB_THRESHOLD);
        DWORD ulCurrentTotalWandB = ulCurrentTotalBlack + pstLocalDimmingSceneData->ulWhiteNum;
        DWORD ulLastTotalWandB = ulLastTotalBlack + pstLocalDimmingSceneData->ulLastWhiteNum;
        ulTotalCornerTHD = ulTotalCornerTHD;
        pusColorHistoPWM = pusColorHistoPWM;
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
        DWORD ulTotalBlackTHD = (ulpanelsize / 1000 * (DWORD)g_stColorLocalDimmingPerformanceAdjust.usColorPictureBlackTH);
        if((ulCurrentTotalBlack > ulTotalBlackTHD) && (ulLastTotalBlack > ulTotalBlackTHD))
        {
            return _LOCAL_DIMMING_PICTURE_NEARLY_BLACK;
        }
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
        if((ulCurrentTotalWandB > ulTotalCornerTHD) && (ulLastTotalWandB > ulTotalCornerTHD) && (ScalerColorLDGetAdaptiveSmoothPattern(pusColorHistoPWM) == _LOCAL_DIMMING_SMOOTH_CORNER_PATTERN))
        {
            return _LOCAL_DIMMING_PICTURE_CORNER;
        }
#endif

        if((ulCurrentTotalWandB > ulTotalWandBTHD) && (ulLastTotalWandB > ulTotalWandBTHD))
        {
            return _LOCAL_DIMMING_PICTURE_WHITE_AND_BLACK;
        }
    }
#if(_LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT == _ON)
    if(((pstLocalDimmingSceneData->ucMaxR - pstLocalDimmingSceneData->ucMinR) <= 1) &&
       ((pstLocalDimmingSceneData->ucMaxG - pstLocalDimmingSceneData->ucMinG) <= 1) &&
       ((pstLocalDimmingSceneData->ucMaxB - pstLocalDimmingSceneData->ucMinB) <= 1))
    {
        return _LOCAL_DIMMING_PICTURE_ELSE_ONE_STEP;
    }
#endif
    return _LOCAL_DIMMING_PICTURE_NORMAL;
}
//-----------------------------------------------------
// Description  :  Local Dimming get Picture Type based on DCR or Histogram data
// Input Value  :  pusColorHistoPWM
// Output Value :  EnumLDPictureType
//-----------------------------------------------------
bit UserCommonColorLocalDimmingCheckFullPattern(const StructLocalDimmingSceneData *pstLocalDimmingSceneData)
{
    if(((pstLocalDimmingSceneData->ucMaxR - pstLocalDimmingSceneData->ucMinR) <= _LOCAL_DIMMING_FULL_PATTERN_RGB_THD) &&
       ((pstLocalDimmingSceneData->ucMaxG - pstLocalDimmingSceneData->ucMinG) <= _LOCAL_DIMMING_FULL_PATTERN_RGB_THD) &&
       ((pstLocalDimmingSceneData->ucMaxB - pstLocalDimmingSceneData->ucMinB) <= _LOCAL_DIMMING_FULL_PATTERN_RGB_THD))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingSmoothFWMode(void)
{
    BYTE ucLocalDimmingSmoothParaSel = 0;
    ucLocalDimmingSmoothParaSel = g_stColorLocalDimmingPerformanceAdjust.ucLocalDimmingSmoothParaSel;

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _OFF)
    // Smooth
    ScalerColorLDPWMProcReadPWMTable(g_pusColorApplyPWM, _LOCAL_DIMMING_TOTAL_REGION);
    // Smooth modify
    ScalerColorLDSmoothModify(g_pusColorApplyPWM, g_pusColorHistoPWM, ucLocalDimmingSmoothParaSel);
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
    UserCommonColorLocalDimmingApplyAnalysis(g_pusColorApplyPWM, g_pusColorLastApplyPWM, &g_stColorLocalDimmingApplyData);
    // Step Change
    UserCommonColorLocalDimmingStepTrueDirectMode(&g_stColorLocalDimmingSceneData, &g_stColorLocalDimmingApplyData);
#else
    ScalerColorLDStepChangeModify(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_stColorLocalDimmingPerformanceAdjust.ucColorStepLevel, g_ucColorLDHistoLutMin, g_stColorLocalDimmingBLMSoftClampPara, &g_stColorLocalDimmingPWMType);
#endif
#else

    if(g_enumColorPWMHistoStage == _LOCAL_DIMMING_HISTO_THD_HIGH)
    {
        // Smooth
        ScalerColorLDPWMProcReadPWMTable(g_pusColorApplyPWM, _LOCAL_DIMMING_TOTAL_REGION);
        // Smooth modify
        ScalerColorLDSmoothModify(g_pusColorApplyPWM, g_pusColorHistoPWM, ucLocalDimmingSmoothParaSel);
        // Step Change
        if(UserCommonColorLocalDimmingSceneChangeModify(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, g_pusColorHistoPWM2) == _FALSE)
        {
            ScalerColorLDStepChangeModify(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_stColorLocalDimmingPerformanceAdjust.ucColorStepLevel, g_ucColorLDHistoLutMin, g_stColorLocalDimmingBLMSoftClampPara, &g_stColorLocalDimmingPWMType);
        }
    }
#endif

    ScalerColorLDPWMProcWritePWMTable(g_pusColorApplyPWM, _LOCAL_DIMMING_TOTAL_REGION, GET_CURRENT_BANK_NUMBER());
    memcpy(g_pusColorLastApplyPWM, g_pusColorApplyPWM, sizeof(g_pusColorApplyPWM));

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
    if(g_enumColorPWMHistoStage == _LOCAL_DIMMING_HISTO_THD_HIGH)
    {
        g_enumColorPWMHistoStage = _LOCAL_DIMMING_HISTO_THD_LOW;
    }
    else
#endif
    {
        g_enumColorPWMHistoStage = _LOCAL_DIMMING_HISTO_THD_HIGH;
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _ON)
        // ScalerColorLocalContrastClearSceneChangeFlag(_1P_NORMAL_REGION, _LOCAL_CONTRAST_SCENE_CHANGE_BOTH_GLOBAL_BLOCK);
#endif
    }

#endif
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingOSDPWMAdjust(void)
{
    ScalerColorLDOSDStepChange(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_stColorLocalDimmingPerformanceAdjust.ucColorOsdStepLevel);
    ScalerColorLDPWMProcWritePWMTable(g_pusColorApplyPWM, _LOCAL_DIMMING_TOTAL_REGION, GET_CURRENT_BANK_NUMBER());
    memcpy(g_pusColorLastApplyPWM, g_pusColorApplyPWM, sizeof(g_pusColorApplyPWM));
}
//--------------------------------------------------
// Description  : Analysis of Scene
// Input Value  :
// Output Value : void
//--------------------------------------------------
void UserCommonColorLocalDimmingSceneAnalysis(WORD *pusHistoPWM, WORD *pusLastHistoPWM, StructLocalDimmingSceneData *pstLocalDimmingSceneData)
{
    WORD usRegionInd = 0;
    WORD pusGlobalHis[_LOCAL_DIMMING_SCENE_ANALYSIS_STEP] = {0};
    BYTE ucLutInd = 0;
    WORD usEntropy = 0;
    WORD usObiDiffRegion = 0;
    DWORD ulObiBinDiff = 0;
    WORD usMaxHisto = 0;
    WORD pusHistoLut12[_LOCAL_DIMMING_SCENE_ANALYSIS_STEP] = {0};

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    memcpy(g_pucColorLastHistoIndex, g_pucColorCurrentHistoIndex, sizeof(g_pucColorCurrentHistoIndex));
    g_stColorLDRegionBoost.b1HistoIndexFix = _TRUE;
#endif

    for(ucLutInd = 0; ucLutInd < _LOCAL_DIMMING_SCENE_ANALYSIS_STEP; ucLutInd++)
    {
        if(ucLutInd == 0)
        {
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
            pusHistoLut12[ucLutInd] = (((DWORD)(ScalerColorLDHistoGetBlackLUT() + 1) * 4095) + 64) >> 7;
#else
            pusHistoLut12[ucLutInd] = ScalerColorLDHistoGetLUT((EnumLDLUTIndex)(ucLutInd));
#endif
        }
        else
        {
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
            pusHistoLut12[ucLutInd] = ((((DWORD)(ScalerColorLDHistoGetLUT((EnumLDLUTIndex)(ucLutInd - 1)) + 1)) * 4095) + 64) >> 7;
#else
            pusHistoLut12[ucLutInd] = ScalerColorLDHistoGetLUT((EnumLDLUTIndex)((WORD)ucLutInd * 8 - 1));
#endif
        }
    }

    // Global hsito, diff region, diff region change, max histo
    for(usRegionInd = 0; usRegionInd < _LOCAL_DIMMING_TOTAL_REGION; usRegionInd++)
    {
        if(usMaxHisto < g_pusColorHistoPWM[usRegionInd])
        {
            usMaxHisto = g_pusColorHistoPWM[usRegionInd];
        }

        for(ucLutInd = 0; ucLutInd < _LOCAL_DIMMING_SCENE_ANALYSIS_STEP; ucLutInd++) // global histo
        {
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
            if(pusHistoPWM[usRegionInd] == pusHistoLut12[ucLutInd])
#else
            if(pusHistoPWM[usRegionInd] <= pusHistoLut12[ucLutInd])
#endif
            {
                WORD usRegionDiff = abs((pusHistoPWM[usRegionInd] - pusLastHistoPWM[usRegionInd]));
                pusGlobalHis[ucLutInd] = pusGlobalHis[ucLutInd] + 1;
                if(ucLutInd == 0)
                {
                    if(usRegionDiff > pusHistoLut12[0])
                    {
                        usObiDiffRegion += 1;
                        ulObiBinDiff += abs(pusLastHistoPWM[usRegionInd] - pusHistoPWM[usRegionInd]);
                    }
                }
                else if(ucLutInd == (_LOCAL_DIMMING_SCENE_ANALYSIS_STEP - 1))
                {
                    if(usRegionDiff > (pusHistoLut12[_LOCAL_DIMMING_SCENE_ANALYSIS_STEP - 1] - pusHistoLut12[_LOCAL_DIMMING_SCENE_ANALYSIS_STEP - 2]))
                    {
                        usObiDiffRegion += 1;
                        ulObiBinDiff += abs(pusLastHistoPWM[usRegionInd] - pusHistoPWM[usRegionInd]);
                    }
                }
                else
                {
                    if(pusHistoPWM[usRegionInd] > pusLastHistoPWM[usRegionInd])
                    {
                        if(usRegionDiff > (pusHistoLut12[ucLutInd] - pusHistoLut12[ucLutInd - 1]))
                        {
                            usObiDiffRegion += 1;
                            ulObiBinDiff += abs(pusLastHistoPWM[usRegionInd] - pusHistoPWM[usRegionInd]);
                        }
                    }
                    else if(pusHistoPWM[usRegionInd] < pusLastHistoPWM[usRegionInd])
                    {
                        if(usRegionDiff > (pusHistoLut12[ucLutInd + 1] - pusHistoLut12[ucLutInd]))
                        {
                            usObiDiffRegion += 1;
                            ulObiBinDiff += abs(pusLastHistoPWM[usRegionInd] - pusHistoPWM[usRegionInd]);
                        }
                    }
                }

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
                if(g_stColorLocalDimmingPerformanceAdjust.b1BoostContrastModeEnable == _ENABLE)
                {
                    g_pucColorCurrentHistoIndex[usRegionInd] = ucLutInd;
                    if(abs(g_pucColorCurrentHistoIndex[usRegionInd] - g_pucColorLastHistoIndex[usRegionInd]) > 1)
                    {
                        g_stColorLDRegionBoost.b1HistoIndexFix = _FALSE;
                    }
                }
#endif
                break;
            }
        }
    }

    // Bin diff
    if(usObiDiffRegion == 0)
    {
        pstLocalDimmingSceneData->ucObiDiffRegionChange = 0;
    }
    else
    {
        pstLocalDimmingSceneData->ucObiDiffRegionChange = ulObiBinDiff * 100 / (usObiDiffRegion * (pusHistoLut12[_LOCAL_DIMMING_SCENE_ANALYSIS_STEP - 1] - pusHistoLut12[0]));
    }
    pstLocalDimmingSceneData->ucObiDiffRegion = (DWORD)usObiDiffRegion * 100 / _LOCAL_DIMMING_TOTAL_REGION;

    // Maximum  histogram value
    pstLocalDimmingSceneData->usMaxHistoValue = usMaxHisto;

    // Entropy
    for(ucLutInd = 0; ucLutInd < _LOCAL_DIMMING_SCENE_ANALYSIS_STEP; ucLutInd++)
    {
        BYTE ucTableInd = ((DWORD)pusGlobalHis[ucLutInd] * 100 + (_LOCAL_DIMMING_TOTAL_REGION / 2)) / _LOCAL_DIMMING_TOTAL_REGION;
        usEntropy = tEntropyTable[ucTableInd] + usEntropy;
    }
    pstLocalDimmingSceneData->usLastEntropy = pstLocalDimmingSceneData->usEntropy;
    pstLocalDimmingSceneData->usEntropy = usEntropy;

    // DCR
    g_stColorLocalDimmingSceneData.ulLastBlackNum = g_stColorLocalDimmingDCRData.ulColorLastBlackNum;
    g_stColorLocalDimmingSceneData.ulBlackNum = g_stColorLocalDimmingDCRData.ulColorCurrentBlackNum;
    g_stColorLocalDimmingSceneData.ulLastWhiteNum = g_stColorLocalDimmingDCRData.ulColorLastBlackNum;
    g_stColorLocalDimmingSceneData.ulWhiteNum = g_stColorLocalDimmingDCRData.ulColorCurrentWhiteNum;
#if((_LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE))
    g_stColorLocalDimmingSceneData.ucMaxB = g_stColorLocalDimmingDCRData.ucMaxB;
    g_stColorLocalDimmingSceneData.ucMaxG = g_stColorLocalDimmingDCRData.ucMaxG;
    g_stColorLocalDimmingSceneData.ucMaxR = g_stColorLocalDimmingDCRData.ucMaxR;
    g_stColorLocalDimmingSceneData.ucMinB = g_stColorLocalDimmingDCRData.ucMinB;
    g_stColorLocalDimmingSceneData.ucMinG = g_stColorLocalDimmingDCRData.ucMinG;
    g_stColorLocalDimmingSceneData.ucMinR = g_stColorLocalDimmingDCRData.ucMinR;
#endif
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingApplyAnalysis(WORD *pusColorApplyPWM, WORD *pusColorLastApplyPWM, StructLocalDimmingApplyData *pstLocalDimmingApplyData)
{
    WORD usExposureRegion = 0;
    WORD uscnt = 0;
    DWORD ulBinDiff = 0;
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    WORD usBlackLut = (((DWORD)(ScalerColorLDHistoGetBlackLUT() + 1) * 4095) + 64) >> 7;
#else
    WORD usBlackLut = ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT00);
#endif
    WORD usPWMDelta = 4095 - usBlackLut;

    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        if((pusColorLastApplyPWM[uscnt] + 100) < pusColorApplyPWM[uscnt])
        {
            usExposureRegion += 1;
        }
        ulBinDiff += abs(pusColorLastApplyPWM[uscnt] - pusColorApplyPWM[uscnt]);
    }
    pstLocalDimmingApplyData->usExposureRegion = (DWORD)usExposureRegion * 100 / _LOCAL_DIMMING_TOTAL_REGION;
    pstLocalDimmingApplyData->usApplyBinDiff = ulBinDiff * 100 / (_LOCAL_DIMMING_TOTAL_REGION * usPWMDelta);
}
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingLowerPowerPWMDirectType(WORD *pusColorHistoPWM, WORD *pusColorAvgY)
{
    WORD usInd = 0;
    BYTE ucBlendValue = 0;
    ucBlendValue = 75;
#if((_HDR10_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
#endif

#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    WORD usBlackLut = (((DWORD)(ScalerColorLDHistoGetBlackLUT() + 1) * 4095) + 64) >> 7;
#else
    WORD usBlackLut = ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT00);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    EnumHDR10Status enumHDR10Status = UserCommonColorHDRGetHDR10Status(enumDisplayRegion);
#endif

    for(usInd = 0; usInd < _LOCAL_DIMMING_TOTAL_REGION; usInd++)
    {
        WORD usLinearPWM = 0;
#if(_HDR10_SUPPORT == _ON)
        if(enumHDR10Status == _HDR10_ON)
        {
            usLinearPWM = (DWORD)(((DWORD)tLDHDR2084Lv[pusColorAvgY[usInd] / 16] * 4095) + tLDHDR2084Lv[255] / 2) / tLDHDR2084Lv[255];
        }
        else
#endif
        {
            usLinearPWM = (DWORD)(((DWORD)tLDSDRLv[pusColorAvgY[usInd] / 16] * 4095) + tLDSDRLv[255] / 2) / tLDSDRLv[255];
        }
        if(usLinearPWM < pusColorHistoPWM[usInd])
        {
            pusColorHistoPWM[usInd] = (((DWORD)pusColorHistoPWM[usInd] *  ucBlendValue) + (DWORD)usLinearPWM * (100 - ucBlendValue)) / 100;
            // pusColorHistoPWM[usInd] = (pusColorHistoPWM[usInd] + usLinearPWM) / 2;
        }
        if(pusColorHistoPWM[usInd] > 4095)
        {
            pusColorHistoPWM[usInd] = 4095;
        }
        else if(pusColorHistoPWM[usInd] < usBlackLut)
        {
            pusColorHistoPWM[usInd] = usBlackLut;
        }
    }
}
#else
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingLowerPowerPWMEdgeType(WORD  *pusColorHistoPWMUP, WORD *pusColorHistoPWM)
{
    WORD usRegionInd = 0;
    WORD pusRegionSumPWM[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    BYTE ucHRatio = _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP / _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL;
    BYTE ucVRatio = _LOCAL_DIMMING_PANEL_REGION_VERTICAL_UP / _LOCAL_DIMMING_PANEL_REGION_VERTICAL;
    for(usRegionInd = 0; usRegionInd < _LOCAL_DIMMING_TOTAL_REGION_UP; usRegionInd++)
    {
        BYTE ucOriginalHInd = 0;
        BYTE ucOriginalVInd = 0;
        ucOriginalHInd = (usRegionInd % _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP) / ucHRatio;
        ucOriginalVInd = (usRegionInd / _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP) / ucVRatio;
        pusRegionSumPWM[ucOriginalVInd * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + ucOriginalHInd] += pusColorHistoPWMUP[usRegionInd];
    }
    for(usRegionInd = 0; usRegionInd < _LOCAL_DIMMING_TOTAL_REGION; usRegionInd++)
    {
        pusColorHistoPWM[usRegionInd] = pusRegionSumPWM[usRegionInd] / (_LOCAL_DIMMING_TOTAL_REGION_UP / _LOCAL_DIMMING_TOTAL_REGION);
    }
}
#endif
#endif
//--------------------------------------------------
// Description  : Change apply degree of dimming due to entropy
// Input Value  : applypwm, scene data
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingApplyDegree(WORD *pusApplyPWM, StructLocalDimmingSceneData stLocalDimmingSceneData)
{
    WORD usMaxRatio = 0;
    WORD usInd = 0;
    WORD usMinPWM = 4095;
    if(stLocalDimmingSceneData.usEntropy < _LOCAL_DIMMING_LOW_ENTROPY)
    {
        usMaxRatio = 200;
    }
    else
    {
        usMaxRatio = (DWORD)(stLocalDimmingSceneData.usEntropy - _LOCAL_DIMMING_LOW_ENTROPY) * 600 / (_LOCAL_DIMMING_ENTROPY_THD - _LOCAL_DIMMING_LOW_ENTROPY) + 200;
    }
    if(usMaxRatio > (_LOCAL_DIMMING_BLMODEL_MAX_GAIN * 100))
    {
        usMaxRatio = _LOCAL_DIMMING_BLMODEL_MAX_GAIN * 100;
    }
    DebugMessageHDR("Maximum ratio", usMaxRatio);
    usMinPWM = ((DWORD)stLocalDimmingSceneData.usMaxHistoValue * 100 + (usMaxRatio / 2)) / usMaxRatio;
    for(usInd = 0; usInd < _LOCAL_DIMMING_TOTAL_REGION; usInd++)
    {
        if(pusApplyPWM[usInd] < usMinPWM)
        {
            pusApplyPWM[usInd] = usMinPWM;
        }
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingStepTrueDirectMode(const StructLocalDimmingSceneData *pstColorLocalDimmingSceneData, const StructLocalDimmingApplyData *pstColorLocalDimmingApplyData)
{
    if(pstColorLocalDimmingSceneData->usEntropy < _LOCAL_DIMMING_ALMOST_GRAY_ENTROPY)
    {
        // almost gray pattern
        if((abs(pstColorLocalDimmingSceneData->usEntropy - pstColorLocalDimmingSceneData->usLastEntropy) > _LOCAL_DIMMING_G2G_DELTA_ENTROPY_THD) && (pstColorLocalDimmingSceneData->usLastEntropy > ((pstColorLocalDimmingSceneData->usEntropy * _LOCAL_DIMMING_G2G_GAIN_ENTROPY_THD + 5) / 10)))
        {
            // N2G
            if(pstColorLocalDimmingSceneData->ucObiDiffRegionChange > _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH0)
            {
                DebugMessageHDR("step 1 ", 0);
                DebugMessageHDR("pstColorLocalDimmingApplyData->usApplyBinDiff", pstColorLocalDimmingApplyData->usApplyBinDiff);
                DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegionChange ", pstColorLocalDimmingSceneData->ucObiDiffRegionChange);
                DebugMessageHDR("pstColorLocalDimmingSceneData->usLastEntropy ", pstColorLocalDimmingSceneData->usLastEntropy);
                DebugMessageHDR("pstColorLocalDimmingSceneData->usEntropy ", pstColorLocalDimmingSceneData->usEntropy);
                DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegion ", pstColorLocalDimmingSceneData->ucObiDiffRegion);

                ScalerColorLDStepChangeModifyDirectType(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, 20, _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP);
            }
            else
            {
                BYTE ucStepFactor = 10;
                BYTE ucOSDValue = g_stColorLocalDimmingPerformanceAdjust.ucColorStepLevel;

                if(pstColorLocalDimmingSceneData->ucObiDiffRegionChange > _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH1)
                {
                    ucStepFactor = (pstColorLocalDimmingSceneData->ucObiDiffRegionChange - _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH1) * (_LOCAL_DIMMING_STEP_N2G_MAX_FACTOR - 10) / (_LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH0 - _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH1) + 10;
                }
                else if(pstColorLocalDimmingSceneData->ucObiDiffRegionChange > _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH2)
                {
                    ucStepFactor = (pstColorLocalDimmingSceneData->ucObiDiffRegionChange - _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH2) * (10 - _LOCAL_DIMMING_STEP_N2G_MIN_FACTOR) / (_LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH1 - _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH2) + _LOCAL_DIMMING_STEP_N2G_MIN_FACTOR;
                }

                ucOSDValue = ((WORD)ucOSDValue * ucStepFactor + 5) / 10;
                if(ucOSDValue > 100)
                {
                    ucOSDValue = 100;
                }

                DebugMessageHDR("step 2 ", 0);
                DebugMessageHDR("ucOSDValue ", ucOSDValue);
                DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegionChange ", pstColorLocalDimmingSceneData->ucObiDiffRegionChange);
                DebugMessageHDR("pstColorLocalDimmingSceneData->usLastEntropy ", pstColorLocalDimmingSceneData->usLastEntropy);
                DebugMessageHDR("pstColorLocalDimmingSceneData->usEntropy ", pstColorLocalDimmingSceneData->usEntropy);
                DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegion ", pstColorLocalDimmingSceneData->ucObiDiffRegion);

                ScalerColorLDStepChangeModifyDirectType(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, ucOSDValue, GET_LOCAL_DIMMING_SC_TYPE());
            }
        }
        else
        {
            // G2G
            BYTE ucOSDValue = g_stColorLocalDimmingPerformanceAdjust.ucColorStepLevel;
            BYTE ucStepFactor = 10;
            /*
            diffbin 10: two bin second largetst diff
            diffbin  7: one bin second largetst diff
            */
            if(pstColorLocalDimmingApplyData->usApplyBinDiff > _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD0)
            {
                ucStepFactor = 10;
            }
            else if((pstColorLocalDimmingApplyData->usApplyBinDiff > _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD1) && (pstColorLocalDimmingSceneData->ucObiDiffRegion < _LOCAL_DIMMING_STEP_G2G_OBI_DIFF_REG))
            {
                ucStepFactor = ((pstColorLocalDimmingApplyData->usApplyBinDiff - _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD1) * (10 - _LOCAL_DIMMING_STEP_G2G_MIN_FACTOR) + (_LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD0 - _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD1) / 2) /
                               (_LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD0 - _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD1) + _LOCAL_DIMMING_STEP_G2G_MIN_FACTOR;
            }
            else if(pstColorLocalDimmingSceneData->ucObiDiffRegion < _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD2)
            {
                ucStepFactor = _LOCAL_DIMMING_STEP_G2G_MIN_FACTOR;
            }
            ucOSDValue = ((WORD)ucOSDValue * ucStepFactor + 5) / 10;
            if(ucOSDValue > 100)
            {
                ucOSDValue = 100;
            }
            ScalerColorLDStepChangeModifyDirectType(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, ucOSDValue, _LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL);

            DebugMessageHDR("step 3 ", 0);
            DebugMessageHDR("ucOSDValue ", ucOSDValue);
            DebugMessageHDR("pstColorLocalDimmingApplyData->usApplyBinDiff", pstColorLocalDimmingApplyData->usApplyBinDiff);
            DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegionChange ", pstColorLocalDimmingSceneData->ucObiDiffRegionChange);
            DebugMessageHDR("pstColorLocalDimmingSceneData->usLastEntropy ", pstColorLocalDimmingSceneData->usLastEntropy);
            DebugMessageHDR("pstColorLocalDimmingSceneData->usEntropy ", pstColorLocalDimmingSceneData->usEntropy);
            DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegion ", pstColorLocalDimmingSceneData->ucObiDiffRegion);
        }
    }
    else
    {
        // Normal pattern
        WORD usExpouserTHD = 100;
        if(pstColorLocalDimmingSceneData->usLastEntropy < _LOCAL_DIMMING_ENTROPY_THD)
        {
            usExpouserTHD = (DWORD)(_LOCAL_DIMMING_ENTROPY_THD - pstColorLocalDimmingSceneData->usLastEntropy) * 30 / (_LOCAL_DIMMING_ENTROPY_THD - _LOCAL_DIMMING_LOW_ENTROPY) + 30;
        }
        if((pstColorLocalDimmingApplyData->usExposureRegion > 80) && (pstColorLocalDimmingApplyData->usApplyBinDiff > usExpouserTHD))
        {
            DebugMessageHDR("step 4 ", 0);
            ScalerColorLDStepChangeModifyDirectType(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, 99, GET_LOCAL_DIMMING_SC_TYPE());
        }
        else
        {
            if((pstColorLocalDimmingApplyData->usApplyBinDiff > 20) && (pstColorLocalDimmingSceneData->ucObiDiffRegion > 1))
            {
                DebugMessageHDR("step 5 ", 0);
                DebugMessageHDR("pstColorLocalDimmingApplyData->usApplyBinDiff ", pstColorLocalDimmingApplyData->usApplyBinDiff);
                ScalerColorLDStepChangeModifyDirectType(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, 20, _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP);
            }
            else
            {
                /*
                diffbin 20: two bin second largetst diff
                diffbin  3: half of one bin second largetst diff
                just the same with the osd factor
                */
                BYTE ucOSDValue = g_stColorLocalDimmingPerformanceAdjust.ucColorStepLevel;
                BYTE ucStepFactor = 10;
                if((pstColorLocalDimmingApplyData->usApplyBinDiff > _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD0) && (pstColorLocalDimmingSceneData->ucObiDiffRegion > _LOCAL_DIMMING_STEP_NOR_DIFF_REGION_TH0))
                {
                    ucStepFactor = _LOCAL_DIMMING_STEP_NOR_MAX_FACTOR;
                }
                else if(pstColorLocalDimmingApplyData->usApplyBinDiff > _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD1)
                {
                    ucStepFactor = 10;
                }
                else if(pstColorLocalDimmingApplyData->usApplyBinDiff > _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD2)
                {
                    ucStepFactor = 10;
                }
                else if((pstColorLocalDimmingApplyData->usApplyBinDiff > _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD3) && (pstColorLocalDimmingSceneData->ucObiDiffRegion < _LOCAL_DIMMING_STEP_NOR_DIFF_REGION_TH1))
                {
                    ucStepFactor = ((pstColorLocalDimmingApplyData->usApplyBinDiff - _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR) * (10 - _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR) + (10 - _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR) / 2) /
                                   (10 - _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR) + _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR;
                }
                else if(pstColorLocalDimmingSceneData->ucObiDiffRegion < _LOCAL_DIMMING_STEP_NOR_DIFF_REGION_TH1)
                {
                    ucStepFactor = _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR;
                }
                else if(pstColorLocalDimmingApplyData->usApplyBinDiff < _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD3)
                {
                    ucStepFactor = _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR;
                }
                ucOSDValue = ((WORD)ucOSDValue * ucStepFactor + 5) / 10;
                if(ucOSDValue > 100)
                {
                    ucOSDValue = 100;
                }

                DebugMessageHDR("Step 6", 0);
                DebugMessageHDR("ucOSDValue", ucOSDValue);
                DebugMessageHDR("pstColorLocalDimmingApplyData->usApplyBinDiff", pstColorLocalDimmingApplyData->usApplyBinDiff);
                DebugMessageHDR("pstColorLocalDimmingSceneData->ucObiDiffRegion", pstColorLocalDimmingSceneData->ucObiDiffRegion);
                DebugMessageHDR("pstColorLocalDimmingSceneData->usLastEntropy ", pstColorLocalDimmingSceneData->usLastEntropy);
                DebugMessageHDR("pstColorLocalDimmingSceneData->usEntropy ", pstColorLocalDimmingSceneData->usEntropy);

                ScalerColorLDStepChangeModifyDirectType(g_pusColorApplyPWM, g_pusColorLastApplyPWM, g_pusColorHistoPWM, g_pusColorLastHistoPWM, ucOSDValue, GET_LOCAL_DIMMING_SC_TYPE());
            }
        }
    }
}

#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingGetYAVG(WORD *pusAVGY)
{
    if(g_stColorLocalDimmingKCPUStateValue.bYavgReadEnableStatus == _TRUE)
    {
        memcpy(pusAVGY, g_pusColorLocalContrastYavgArray, sizeof(g_pusColorLocalContrastYavgArray));
    }
    else
    {
        memcpy(pusAVGY, g_pusColorHistoPWM, sizeof(g_pusColorHistoPWM));
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingBlendPWMUsingYavg(WORD *pusSmoothPWM, WORD *pusHistoPWM, WORD *pusApplyBlendPWM, WORD usMinBlendPWMValue)
{
    WORD usInd = 0;
    WORD pusBlendPWM[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    WORD usStepR = _LOCAL_DIMMING_PWM_BLEND_DEFAULT_R;
    WORD usAvgStepFrac = g_stColorLocalDimmingPerformanceAdjust.usAvgStepFrac;
    WORD usPercentileStepFrac = g_stColorLocalDimmingPerformanceAdjust.usPercentileStepFrac;
    WORD usAvgBlackValue = g_stColorLocalDimmingPerformanceAdjust.usAvgBlackValue;
    WORD usAvgBlackStep = g_stColorLocalDimmingPerformanceAdjust.usAvgBlackStep;
    memcpy(pusBlendPWM, pusSmoothPWM, sizeof(g_pusColorHistoPWM));

    ExternalDeviceInterfaceLedDriverModifiedPWM(pusBlendPWM, pusHistoPWM, pusSmoothPWM, g_pusColorLocalDimmingAvgY, usMinBlendPWMValue);

    for(usInd = 0; usInd < _LOCAL_DIMMING_TOTAL_REGION; usInd++)
    {
        WORD usAvgFrac = 0;
        WORD usPercentileFrac = 0;
        WORD usAvgDelta = abs(g_pusColorLastLocalDimmingAvgY[usInd] - g_pusColorLocalDimmingAvgY[usInd]);
        WORD usPercentileDelta = abs(pusBlendPWM[usInd] - g_pusColorLastBlendPWM[usInd]);

        usAvgFrac = ((DWORD)usAvgDelta * usAvgStepFrac) / 4095;
        usPercentileFrac = ((DWORD)usPercentileDelta * usPercentileStepFrac) / 4095;

#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
        if(g_stColorLocalDimmingPerformanceAdjust.enumLocalDimmingCase != _LOCAL_DIMMING_ENERGYSAVER)
#endif
        {
            usStepR = usAvgFrac + usPercentileFrac;
            if(g_pusColorLocalDimmingAvgY[usInd] <= usAvgBlackValue)
            {
                if(usStepR < usAvgBlackStep)
                {
                    usStepR = usAvgBlackStep;
                }
            }
            if(usStepR > 1024)
            {
                usStepR = 1024;
            }
            if(usStepR < 32)
            {
                usStepR = 32;
            }
        }
        pusApplyBlendPWM[usInd] = ((((DWORD)usStepR * pusBlendPWM[usInd]) + ((DWORD)(1024 - usStepR) * g_pusColorLastBlendPWM[usInd])) + 512) / 1024;

        if(pusApplyBlendPWM[usInd] == g_pusColorLastBlendPWM[usInd])
        {
            if((pusApplyBlendPWM[usInd] > pusBlendPWM[usInd]) && (pusApplyBlendPWM[usInd] > 0))
            {
                pusApplyBlendPWM[usInd] = pusApplyBlendPWM[usInd] - 1;
            }
            if((pusApplyBlendPWM[usInd] < pusBlendPWM[usInd]) && (pusApplyBlendPWM[usInd] < 4095))
            {
                pusApplyBlendPWM[usInd] = pusApplyBlendPWM[usInd] + 1;
            }
        }
    }
}
#else
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingBlendPWM(WORD *pusSmoothPWM, WORD *pusHistoPWM, WORD *pusApplyBlendPWM, StructLocalDimmingSceneData stLocalDimmingSceneData, WORD usMinBlendPWMValue)
{
    WORD usInd = 0;
    WORD pusBlendPWM[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    BYTE ucBlackPer = 0;
    WORD usStepR = _LOCAL_DIMMING_PWM_BLEND_DEFAULT_R;
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    WORD usBlackLut = (((DWORD)(ScalerColorLDHistoGetBlackLUT() + 1) * 4095) + 64) >> 7;
#else
    WORD usBlackLut = ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT00);
#endif
    memcpy(pusBlendPWM, pusSmoothPWM, sizeof(g_pusColorHistoPWM));

#if(_LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE == _ON)
    WORD pusExtroInfo0[_LOCAL_DIMMING_TOTAL_REGION];
    WORD pusExtroInfo1[_LOCAL_DIMMING_TOTAL_REGION];
    ScalerColorLDExtroInfoReadInfo0(pusExtroInfo0, _LOCAL_DIMMING_TOTAL_REGION);
    ScalerColorLDExtroInfoReadInfo1(pusExtroInfo1, _LOCAL_DIMMING_TOTAL_REGION);
    ScalerColorLDExtroInfo0PermissionSwitchApply();
    ScalerColorLDExtroInfo1PermissionSwitchApply();
#endif

    ucBlackPer = 100 - (g_stColorLocalDimmingDCRData.ulColorCurrentBlackNum * 100 / _PANEL_DH_WIDTH / _PANEL_DV_HEIGHT);
    // DebugMessageHDR("BlackPer", ucBlackPer);

    if(stLocalDimmingSceneData.usEntropy < _LOCAL_DIMMING_ALMOST_GRAY_ENTROPY) // 80% same bin with 90% percentile min
    {
        if((abs(stLocalDimmingSceneData.usEntropy - stLocalDimmingSceneData.usLastEntropy) > _LOCAL_DIMMING_G2G_DELTA_ENTROPY_THD) && (stLocalDimmingSceneData.usLastEntropy > ((stLocalDimmingSceneData.usEntropy * _LOCAL_DIMMING_G2G_GAIN_ENTROPY_THD + 5) / 10)))
        {
            if(stLocalDimmingSceneData.ucObiDiffRegionChange > _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH0)
            {
                usStepR = 1024;
            }
        }
    }

    for(usInd = 0; usInd < _LOCAL_DIMMING_TOTAL_REGION; usInd++)
    {
        pusBlendPWM[usInd] = ((_LOCAL_DIMMING_PWM_BLEND_GAIN * (DWORD)pusSmoothPWM[usInd]) / 255) +
                             ((255 - _LOCAL_DIMMING_PWM_BLEND_GAIN) * (DWORD)pusHistoPWM[usInd]) / 255;

        if(pusHistoPWM[usInd] <= usBlackLut)
        {
            if(ucBlackPer >= _LOCAL_DIMMING_PWM_DARK_TH0)
            {
                pusBlendPWM[usInd] = usMinBlendPWMValue;
            }
            else if(ucBlackPer >= _LOCAL_DIMMING_PWM_DARK_TH1)
            {
                if(pusBlendPWM[usInd] < usMinBlendPWMValue)
                {
                    pusBlendPWM[usInd] = usMinBlendPWMValue;
                }
                pusBlendPWM[usInd] = pusBlendPWM[usInd] - (DWORD)(ucBlackPer - _LOCAL_DIMMING_PWM_DARK_TH1) * (pusBlendPWM[usInd] - usMinBlendPWMValue) / (_LOCAL_DIMMING_PWM_DARK_TH0 - _LOCAL_DIMMING_PWM_DARK_TH1);
            }
        }
#if(_LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE == _ON)
        ExternalDeviceInterfaceLedDriverModifiedPWMExtroInfo(&pusBlendPWM[usInd], pusHistoPWM[usInd], pusExtroInfo0[usInd], pusExtroInfo1[usInd]);
#endif
        pusApplyBlendPWM[usInd] = ((((DWORD)usStepR * pusBlendPWM[usInd]) + ((DWORD)(1024 - usStepR) * g_pusColorLastBlendPWM[usInd])) + 512) / 1024;

        if(pusApplyBlendPWM[usInd] == g_pusColorLastBlendPWM[usInd])
        {
            if((pusApplyBlendPWM[usInd] > pusBlendPWM[usInd]) && (pusApplyBlendPWM[usInd] > 0))
            {
                pusApplyBlendPWM[usInd] = pusApplyBlendPWM[usInd] - 1;
            }
            if((pusApplyBlendPWM[usInd] < pusBlendPWM[usInd]) && (pusApplyBlendPWM[usInd] < 4095))
            {
                pusApplyBlendPWM[usInd] = pusApplyBlendPWM[usInd] + 1;
            }
        }
    }
}
#endif
#endif
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingCombineHistoPWM(WORD *pusColorHistoPWM, WORD *pusColorHistoPWMUP)
{
    WORD usRegionInd = 0;
    BYTE ucHRatio = _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP / _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL;
    BYTE ucVRatio = _LOCAL_DIMMING_PANEL_REGION_VERTICAL_UP / _LOCAL_DIMMING_PANEL_REGION_VERTICAL;
    memset(pusColorHistoPWM, 0, _LOCAL_DIMMING_TOTAL_REGION * sizeof(WORD));
    for(usRegionInd = 0; usRegionInd < _LOCAL_DIMMING_TOTAL_REGION_UP; usRegionInd++)
    {
        BYTE ucOriginalHInd = 0;
        BYTE ucOriginalVInd = 0;
        ucOriginalHInd = (usRegionInd % _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP) / ucHRatio;
        ucOriginalVInd = (usRegionInd / _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL_UP) / ucVRatio;
        if(pusColorHistoPWM[ucOriginalVInd * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + ucOriginalHInd] < pusColorHistoPWMUP[usRegionInd])
        {
            pusColorHistoPWM[ucOriginalVInd * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + ucOriginalHInd] = pusColorHistoPWMUP[usRegionInd];
        }
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingPWMProcChangeHVRegion(EnumPWMProcRegionType enumPWMProcRegionType)
{
    // ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    ScalerColorLDPWMProcChangeHVRegionType(enumPWMProcRegionType);
}
#endif
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingInitialSetting(void)
{
    // PWM process
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    BYTE pucTemp[5] = {0};
#endif
    // initial stage
    SET_LOCAL_DIMMING_FW_PROCESS_STAGE(_LOCAL_DIMMING_FW_HISTOGRAM);
    SET_LOCAL_DIMMING_HISTOGRAM_DONE(_FALSE);
    SET_LOCAL_DIMMING_SC_TYPE(_LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL);
    SET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON(_TRUE);
    SET_LOCAL_DIMMING_BLMODEL_POLLING_COUNT(0);
    SET_LOCAL_DIMMING_FULL_PATTERN(_FALSE);


    // initial scene data
    g_stColorLocalDimmingSceneData.ucObiDiffRegion = 0;
    g_stColorLocalDimmingSceneData.ucObiDiffRegionChange = 0;
    g_stColorLocalDimmingSceneData.usEntropy = 0;
    g_stColorLocalDimmingSceneData.usLastEntropy = 0;
    g_stColorLocalDimmingSceneData.usMaxHistoValue = 4095;
    /*
    g_stColorLocalDimmingSceneData.ulBlackNum = 0;
    g_stColorLocalDimmingSceneData.ulWhiteNum = 0;
    g_stColorLocalDimmingSceneData.ulLastBlackNum = 0;
    g_stColorLocalDimmingSceneData.ulLastWhiteNum = 0;
    */
#if((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
    g_ucColorApplyCurrentAdim = 100;
#if((_HW_CPU32_IS_BOOT_CPU == _FALSE) && (_SCPU_SUPPORT == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON))
    ScalerCpuSyncColorLDSetScpuAdimStatus(_FALSE);
#endif
#endif
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = 100;
    g_stColorLocalDimmingHDR10BoostData.ucColorLastApplyAdimValue = 100;
    g_stColorLocalDimmingDCRData.ucColorDCRMaxY = 255;
    g_stColorLocalDimmingDCRData.ucColorLastDCRMaxY = 255;
    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingBoostValue = 100;

    ScalerFlashRead(_OGC_FLASH_BANK, (BYTE *)((((WORD)_OGC_FLASH_PAGE) << 12) + _LOCAL_DIMMING_GAIN_ADDRESS), 5, pucTemp);
    if(pucTemp[0] == _LOCAL_DIMMING_NEW_BOOST_MODE)
    {
        g_stColorLocalDimmingHDR10BoostData.ucColorGainValue = (((WORD)pucTemp[1] << 8) + pucTemp[2] + 5) / 10;
        g_stColorLocalDimmingHDR10BoostData.usColorBoostLv = ((WORD)pucTemp[3] << 8) + pucTemp[4];
    }
    else
    {
        g_stColorLocalDimmingHDR10BoostData.ucColorGainValue = (DWORD)_LOCAL_DIMMING_MAXCLL * 100 / _LOCAL_DIMMING_MAXFALL;
        g_stColorLocalDimmingHDR10BoostData.usColorBoostLv = (WORD)_LOCAL_DIMMING_MAXFALL;
    }
#endif

#if(_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE)
    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim = 100;
    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim = 100;
#endif

    // backlight model
    ScalerColorLDBLModelLVLutInitial();

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    for(BYTE ucCnt = 0; ucCnt < _LOCAL_DIMMING_TOTAL_REGION; ucCnt++)
    {
        g_pusColorLastRegionAdim[ucCnt] = 1000;
        g_pusColorLastRegionGain[ucCnt] = 1024;

        g_stColorLDRegionBoost.pusBoostGain[ucCnt] = 1000;
    }
    g_stColorLDRegionBoost.b1HistoIndexFix = _FALSE;
    g_stColorLDRegionBoost.enumLDAdimMode = _LOCAL_DIMMING_TRUE_PQ;
    g_stColorLDRegionBoost.ucCurrentGainIndex = 0;
    g_stColorLDRegionBoost.enumLocalDimmingIGGoal = _LOCAL_DIMMING_LOCAL_ADIM_CLL;

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    g_stColorLDRegionBoost.usGlobalBoostAdim = 100;
    g_stColorLDRegionBoost.usGlobalLedGain = 1024;
#endif
#endif
}
//--------------------------------------------------
// Description  : Judge Local Dimming ON or OFF
// Input Value  : None
// Output Value : _LOCAL_DIMMING_ENABLE/ _LOCAL_DIMMING_DISABLE
//--------------------------------------------------
EnumLocalDimmingStatus UserCommonColorLocalDimmingGetEnableStatus(void)
{
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            break;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
            break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif
        default:
            return _LOCAL_DIMMING_DISABLE;
    }

#if(_COLOR_DEMO_FUNCTION == _ON)
    if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
    {
        switch(GET_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_1P:
                enumDisplayRegion = _DISPLAY_RGN_1P;
                break;
            case _DISPLAY_MODE_2P_PIP:
                enumDisplayRegion = _DISPLAY_RGN_PIP_MAIN;
                break;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
                break;
#endif

            case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                enumDisplayRegion = _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
                break;
            case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                enumDisplayRegion = _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
                break;
            case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                enumDisplayRegion = _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
                break;
            case _DISPLAY_MODE_2P_PBP_TB:
                enumDisplayRegion = _DISPLAY_RGN_TOP;
                break;

            default:
                return _LOCAL_DIMMING_DISABLE;
        }
    }
#endif

    if((GET_ON_LINE_CALIBRATION_STATUS() == _CALIBRATION_OFF) &&
       (UserInterfaceColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE))
    {
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _OFF)
#if(_DRR_SUPPORT == _ON)
        if(UserCommonDrrGetType() != _DRR_NONE_TYPE)
        {
            return _LOCAL_DIMMING_DISABLE;
        }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
        if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) != _HDR10_OFF)
        {
#if((_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON) && (_FREESYNC_II_SUPPORT == _ON))
            if(GET_FREESYNC_II_MODE_STATUS(enumDisplayRegion))
            {
                if(UserCommonColorHDRGetFreeSyncIILDDisable(enumDisplayRegion) == _OFF)
                {
                    return _LOCAL_DIMMING_ENABLE;
                }
            }
            else
#endif
            {
                return _LOCAL_DIMMING_ENABLE;
            }
        }
        else
#endif
        {
#if((_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON) && (_FREESYNC_II_SUPPORT == _ON))
            if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
            {
                if(UserCommonColorHDRGetFreeSyncIILDDisable(enumDisplayRegion) == _OFF)
                {
                    return _LOCAL_DIMMING_ENABLE;
                }
            }
            else
#endif
            {
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
                if(UserCommonColor3DGammaCubeGetEnableStatus((EnumSelRegion)enumDisplayRegion) == _FUNCTION_ON)
                {
                    return _LOCAL_DIMMING_DISABLE;
                }
#endif
                if(UserInterfaceColorSDROCCOGCMode() == _SDR_CALIBRATION_BY_OGC_TOOL)
                {
                    return _LOCAL_DIMMING_ENABLE;
                }
            }
        }
    }

    enumDisplayRegion = enumDisplayRegion; // for compile warning

    return _LOCAL_DIMMING_DISABLE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
#if(_LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE == _ON)
        // extro info
        ScalerColorLDExtroInforEnable(_FUNCTION_ON);
#endif
        // Histogram
        ScalerColorLDHistoEnable(_FUNCTION_ON);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        // smooth
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
        ScalerColorLDSmoothRerangeEnable(_FUNCTION_ON);
#elif(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_DIRECT_BACKLIGHT)
        ScalerColorLDSmoothToMaxDisable(_FUNCTION_ON);
#endif

        ScalerColorLDSmoothEnable(_FUNCTION_ON);

        // Step change
        ScalerColorLDStepEnable(_FUNCTION_ON);

        // PWM process
        ScalerColorLDPWMProcEnable(_FUNCTION_ON);
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

        // Backlight Model
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
        ScalerColorLDBLModelUniqueGainEnable(_FUNCTION_OFF);
#elif(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
        ScalerColorLDBLModelUniqueGainEnable(_FUNCTION_ON);
#endif
        ScalerColorLDBLModelEnable(_FUNCTION_ON);

        // delay
        DELAY_5US();
        // switch
        ScalerColorLDBLModelSetMode(_LOCAL_DIMMING_BLMODEL_PSEUDO_MODE);
        ScalerColorLDBLModelSetMode(_LOCAL_DIMMING_BLMODEL_MANUAL_MODE);

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
        // SPI
        ScalerSpiDimmingSetSpiHwToLD();
#endif

        ScalerColorLDPwmToSpiEnable(_FUNCTION_ON);

        // update K cpu stage
        g_stColorLocalDimmingKCPUStateValue.enumLocalDimmingStatus = _LOCAL_DIMMING_ENABLE;
    }
    else
    {
        // update K cpu stage
        g_stColorLocalDimmingKCPUStateValue.enumLocalDimmingStatus = _LOCAL_DIMMING_DISABLE;

        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        // SPI
        ScalerColorLDPwmToSpiEnable(_FUNCTION_OFF);

        // switch BL Model to FW Mode (force to clean bl_cal_done)
        ScalerColorLDBLModelSetMode(_LOCAL_DIMMING_BLMODEL_FW_MODE);
        DELAY_5US();
        // BLM
        ScalerColorLDBLModelEnable(_FUNCTION_OFF);
        DELAY_5US();
        if(ScalerColorLDBLModelManualSwitchStatus() == _TRUE)
        {
            ScalerColorLDBLModelManualSwitchApply();
        }



        // Adjust
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
        ScalerColorLDAdjustEnable(_FUNCTION_OFF);
#endif
        // Smooth
        ScalerColorLDSmoothEnable(_FUNCTION_OFF);

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
        ScalerColorLDSmoothRerangeEnable(_FUNCTION_OFF);
#elif(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_DIRECT_BACKLIGHT)
        ScalerColorLDSmoothToMaxDisable(_FUNCTION_OFF);
#endif
        // Step
        ScalerColorLDStepEnable(_FUNCTION_OFF);

        // PWM process
        ScalerColorLDPWMProcEnable(_FUNCTION_OFF);

        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerColorLDPWMProcSramSwitchApply();

#if(_LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE == _ON)
        // extro info
        ScalerColorLDExtroInforEnable(_FUNCTION_OFF);
#endif

        // Histogram
        ScalerColorLDHistoEnable(_FUNCTION_OFF);

        // backlight
        UserCommonColorLocalDimmingRestoreBacklight();

        // clear flag
        // clear tx done bit
        g_bSpiDimmingSramModeTxDoneFlag = _FALSE;

        // clear BL Model Gain Apply Done bit
        if(ScalerColorLDBLModelGainApplyDone() == _TRUE)
        {
            ScalerColorLDBLModelGainApplyDoneClear();
        }

        // clear upd synd done
        if(ScalerColorLDPwmToSpiCheckUpdSyncApplyDone() == _TRUE)
        {
            ScalerColorLDPwmToSpiAckUpdSyncApplyDone();
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingAdjust(void)
{
    StructColorLocalDimmingSetting stLocalDimmingData = {0};
    StructColorDCRSetting stUnionDCR = {0};

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    UserCommonColorLocalContrastRestoreSetting();
#endif
#endif
    UserCommonColorGetLocalDimmingData(&stLocalDimmingData);
    UserCommonColorGetDCRData(&stUnionDCR);
    ScalerColorIPDCRAdjust(&stUnionDCR);

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
#if((_PANEL_EXIST_MULTIPANEL == _ON) && (_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON))
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) != ScalerColorLDGetFrontBackStatus())
    {
        UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
        ScalerColorLDHistoInitial(_LOCAL_DIMMING_HISTO_COVERRATE);
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            ScalerColorLDPWMProcFrontBackEnable(_ENABLE);
            ScalerColorLDBLModelFrontBackEnable(_ENABLE);
        }
        else
        {
            ScalerColorLDPWMProcFrontBackEnable(_DISABLE);
            ScalerColorLDBLModelFrontBackEnable(_DISABLE);
        }
    }
#endif
#endif

    g_stColorLocalDimmingPerformanceAdjust.ucColorSmoothLevel = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.ucSmoothLevel;
    g_stColorLocalDimmingPerformanceAdjust.ucColorStepLevel = MINOF(100, stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.ucStepChangeLevel);
    g_stColorLocalDimmingPerformanceAdjust.ucColorOsdStepLevel = MINOF(100, stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.ucOSDStepChangeLevel);
    g_stColorLocalDimmingPerformanceAdjust.b1ColorOsdCurrentPWMEnable = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.b1OSDCurrentPWMEnable;
    g_stColorLocalDimmingPerformanceAdjust.ucLocalDimmingSmoothParaSel = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.ucLocalDimmingSmoothParaSel;
    g_stColorLocalDimmingPerformanceAdjust.b1ColorTotalWorBOneStep = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.b1TotalWorBOneStep;
    g_stColorLocalDimmingPerformanceAdjust.enumLocalDimmingCase = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumLocalDimmingCase;
    SET_LOCAL_DIMMING_CASE(g_stColorLocalDimmingPerformanceAdjust.enumLocalDimmingCase);
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    g_stColorLocalDimmingPerformanceAdjust.b1BoostContrastModeEnable = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.b1BoostContrastModeEnable;
    g_stColorLocalDimmingPerformanceAdjust.usRegionBoostAdimStep = MINOF(1000, stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usRegionBoostAdimStep);
    g_stColorLocalDimmingPerformanceAdjust.usRegionBoostGainStep = MINOF(1000, stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usRegionBoostGainStep);
#endif
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
    g_stColorLocalDimmingPerformanceAdjust.usColorPictureBlackTH = MINOF(1020, stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usPictureBlackTH);
#endif
    g_stColorLocalDimmingPerformanceAdjust.usColorPictureBNWTH = MINOF(1020, stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usPictureBNWTH);

#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
    g_stColorLocalDimmingPerformanceAdjust.usMinBlendPWMValue = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usMinBlendPWMValue;
#endif

#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
    g_stColorLocalDimmingPerformanceAdjust.usAvgStepFrac = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usAvgStepFrac;
    g_stColorLocalDimmingPerformanceAdjust.usPercentileStepFrac = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usPercentileStepFrac;
    g_stColorLocalDimmingPerformanceAdjust.usAvgBlackValue = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usAvgBlackValue;
    g_stColorLocalDimmingPerformanceAdjust.usAvgBlackStep = stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.usAvgBlackStep;
#endif

    if(stLocalDimmingData.stLocalDimmingSetting.enumLocalDimmingMode != _LOCAL_DIMMING_OFF)
    {
        UserCommonColorLocalDimmingSmoothAdjust();
        UserCommonColorLocalDimmingDeepBlackEnable(stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumLocalDimmingCase);
        // backlight model
        if(ScalerColorLDBLModelGetEnableStatus() == _OFF) // LD OFF to ON
        {
            UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
            UserCommonColorLocalDimmingPWMInitial();
            UserCommonColorLocalDimmingInitialSetting();
            UserCommonColorLocalDimmingEnable(_FUNCTION_ON);
            if(stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumLocalDimmingCase == _LOCAL_DIMMING_USER)
            {
                ScalerColorLDBLModelDeepBlackEnable(_FUNCTION_ON);
                ScalerColorLDBLModelBlackTHAdjust(0);
                ScalerColorLDBLModelBlackTHDelta(0);
            }
        }
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
        if(stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumLocalDimmingCase == _LOCAL_DIMMING_ENERGYSAVER)
        {
            ScalerColorLDBLModelSetMaxGain((WORD)_LOCAL_DIMMING_BLMODEL_MAX_GAIN_POWER_SAVER * 1024);
            ScalerColorLDBLModelSoftClampAdjust(_LOCAL_DIMMING_SOFTCLAMP_SLOP_POWER_SAVER);
        }
        else
        {
            ScalerColorLDBLModelSetMaxGain((WORD)_LOCAL_DIMMING_BLMODEL_MAX_GAIN * 1024);
            ScalerColorLDBLModelSoftClampAdjust(_LOCAL_DIMMING_SOFTCLAMP_SLOP);
        }
#endif
#if(_LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE == _ON)
        ScalerColorLDExtroInfo0Select(stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumExtroInfo0);
        ScalerColorLDExtroInfo1Select(stLocalDimmingData.stLocalDimmingSetting.unLocalDimmingData.stLocalDimmingData.enumExtroInfo1);
#endif
    }
    else
    {
        UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingSoftClampAdjust(void)
{
    BYTE ucSoltClampSlop = 0x05;

    ScalerColorLDBLModelSoftClampAdjust(ucSoltClampSlop);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingPWMInitial(void)
{
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    if(ScalerCpuCtrlCheckScpuActive() == _TRUE)
    {
        g_pstCpuSyncToScpuCmd->unCmdBody.stColorLocalDimmingCmd.ucSubCmdType = _LOCAL_DIMMING_PWM_INITIAL;
        ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_LOCAL_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_LOCAL_DIMMING, _NULL_POINTER);
    }
#else
    for(WORD uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        g_pusColorLastApplyPWM[uscnt] = 4095;
        g_pusColorLastHistoPWM[uscnt] = 4095;
        g_pusColorHistoPWM[uscnt] = 4095;
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
        g_pusColorLastBlendPWM[uscnt] = 4095;
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
        g_pusColorLocalDimmingAvgY[uscnt] = 4095;
        g_pusColorLastLocalDimmingAvgY[uscnt] = 4095;
#endif
#endif
    }
    g_stColorLocalDimmingDCRData.ulColorLastBlackNum = ((DWORD)_PANEL_DH_WIDTH) * ((DWORD)_PANEL_DV_HEIGHT); // In the beginning, preventing local dimming flow from case of one step to target PWM
    g_stColorLocalDimmingDCRData.ulColorLastWhiteNum = 0; // In the beginning, preventing local dimming flow from case of one step to target PWM
    SET_LOCAL_DIMMING_PWM_TOTAL_RATIO(100);
#endif
}
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
//--------------------------------------------------
// Description  :
// Input Value  : void
// Output Value : each region pwm value(7 bit value)
//--------------------------------------------------
WORD *UserCommonColorLocalDimmingGetEdgeTypePWMValue(void)
{
    return g_pusColorHistoPWM;
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingSmoothAdjust(void)
{
    BYTE ucMatrixLevel = 0;
    BYTE ucLocalDimmingSmoothParaSel = 0;
    ucMatrixLevel = g_stColorLocalDimmingPerformanceAdjust.ucColorSmoothLevel;
    ucLocalDimmingSmoothParaSel = g_stColorLocalDimmingPerformanceAdjust.ucLocalDimmingSmoothParaSel;
    ScalerColorLDSmoothShrinkGain(ucMatrixLevel);
    ScalerColorLDSmoothMatrixAdjust(ucMatrixLevel, ucLocalDimmingSmoothParaSel);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingDeepBlackEnable(EnumLocalDimmingCase enumLocalDimmingCase)
{
    if(enumLocalDimmingCase == _LOCAL_DIMMING_USER)
    {
        ScalerColorLDBLModelDeepBlackEnable(_FUNCTION_ON);
    }
    else
    {
        ScalerColorLDBLModelDeepBlackEnable(_FUNCTION_OFF);
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingRestoreBacklight(void)
{
#if((_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_HW_CPU32_NOTIFY_INT_SUPPORT == _ON))
    g_pstScpuSyncToKcpuCmd->unCmdBody.stColorLocalDimmingCmd.ucSubCmdType = _LOCAL_DIMMING_BACKLIGHT_RESTORE;
    ScalerScpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_LOCAL_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_COLOR_LOCAL_DIMMING_BACKLIGHT_RESTORE, _NULL_POINTER);
#else
    UserInterfaceColorLocalDimmingRestoreBacklight();
#endif
}


#if(_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM)
//--------------------------------------------------
// Description  : compensate Lv By Adim
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorLocalDimmingCompByAdim(void)
{
    BYTE ucApplyCompGain = g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim;

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _OFF)
    g_ucColorApplyCurrentAdim = 100;
#endif

#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() != _BACKLIGHT_MODE_CONSTANT)
    {
        ucApplyCompGain = 100;
    }
    else
#endif
    {
        WORD usStep = 64;
        if(GET_LOCAL_DIMMING_SC_TYPE() != _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP)
        {
            ucApplyCompGain = (BYTE)(((((DWORD)usStep * (DWORD)ucApplyCompGain) + ((DWORD)(1024 - usStep) * (DWORD)g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim)) + 512) / 1024);

            if(ucApplyCompGain == g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim)
            {
                if(g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim > ucApplyCompGain)
                {
                    ucApplyCompGain += 1;
                }
                else if(g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim < ucApplyCompGain)
                {
                    ucApplyCompGain -= 1;
                }
            }
        }
    }


    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim = ucApplyCompGain;
    g_ucColorApplyCurrentAdim = (BYTE)(((WORD)g_ucColorApplyCurrentAdim * (WORD)ucApplyCompGain + 50) / 100);
}
#endif

#if(_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_DDIM)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingCompByDdim(WORD *pusSmoothPWM)
{
    WORD usInd = 0;
    BYTE ucApplyCompGain = g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim;
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    WORD usBlackLut = (((DWORD)(ScalerColorLDHistoGetBlackLUT() + 1) * 4095) + 64) >> 7;
#else
    WORD usBlackLut = ScalerColorLDHistoGetLUT(_LOCAL_DIMMING_HISTO_LUT00);
#endif

    WORD usStep = 64;

    if(((GET_LOCAL_DIMMING_SC_TYPE() != _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP) && (GET_LOCAL_DIMMING_FULL_PATTERN() == _FALSE)) || (GET_LOCAL_DIMMING_PICTURE_TYPE() == _LOCAL_DIMMING_PICTURE_TOTAL_BLACK))
    {
        ucApplyCompGain = (BYTE)(((((DWORD)usStep * (DWORD)ucApplyCompGain) + ((DWORD)(1024 - usStep) * (DWORD)g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim)) + 512) / 1024);

        if(ucApplyCompGain == g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim)
        {
            if(g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim > ucApplyCompGain)
            {
                ucApplyCompGain += 1;
            }
            else if(g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim < ucApplyCompGain)
            {
                ucApplyCompGain -= 1;
            }
        }
    }

    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingLastCompADdim = ucApplyCompGain;
    if(ucApplyCompGain == _LOCAL_DIMMING_MAX_COMPENSATE_GAIN)
    {
        return;
    }

    for(usInd = 0; usInd < _LOCAL_DIMMING_TOTAL_REGION; usInd++)
    {
        WORD usNewPWM = (WORD)(((DWORD)pusSmoothPWM[usInd] * (DWORD)ucApplyCompGain + (_LOCAL_DIMMING_MAX_COMPENSATE_GAIN / 2)) / _LOCAL_DIMMING_MAX_COMPENSATE_GAIN);
        usNewPWM = MINOF(4095, usNewPWM);

        if(usNewPWM > usBlackLut)
        {
            pusSmoothPWM[usInd] = usNewPWM;
        }
        else
        {
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
            if(pusSmoothPWM[usInd] < usBlackLut)
            {
                pusSmoothPWM[usInd] = g_stColorLocalDimmingPerformanceAdjust.usMinBlendPWMValue;
            }
            else
#endif
            {
                pusSmoothPWM[usInd] = usBlackLut;
            }
        }
    }
}
#endif

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingBoostModify(void)
{
    WORD usNodeLvGain = 1024;

#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() != _BACKLIGHT_MODE_CONSTANT) // disable BL Gain when MBR is _ON
    {
        g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = 100;
        g_ucColorApplyCurrentAdim = g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue;
        usNodeLvGain = 1024;
    }
    else
#endif
    {
        // ideal A dim Value
        BYTE ucIdealAdimValue = 100;
        EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
        }
#endif

        if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _ON)
        {
            if(UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion) == _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
            {
                if(tLDHDR2084Lv[g_stColorLocalDimmingDCRData.ucColorDCRMaxY] > g_stColorLocalDimmingHDR10BoostData.usColorBoostLv)
                {
                    DebugMessageHDR("BOOST_NOTM", 0);
                    ucIdealAdimValue = _LOCAL_DIMMING_BOOST_ADMING;
                }
                else
                {
                    ucIdealAdimValue = 100;
                }
            }
            else if(UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion) == _HDR10_MAX_MASTERING_LV_TYPE_10000)
            {
                if(g_stColorLocalDimmingDCRData.ucColorDCRMaxY >= 254)
                {
                    DebugMessageHDR("BOOST_1000", 0);
                    ucIdealAdimValue = _LOCAL_DIMMING_BOOST_ADMING;
                }
                else
                {
                    ucIdealAdimValue = 100;
                }
            }
        }
#if(_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON)
        else if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
        {
            if(tFREESYNCIILv[g_stColorLocalDimmingDCRData.ucColorDCRMaxY] > g_stColorLocalDimmingHDR10BoostData.usColorBoostLv)
            {
                DebugMessageHDR("BOOST_FSII", 0);
                ucIdealAdimValue = _LOCAL_DIMMING_BOOST_ADMING;
            }
            else
            {
                ucIdealAdimValue = 100;
            }
        }
#endif
        else
        {
            ucIdealAdimValue = 100;
        }

        // step to ideal
        if(GET_LOCAL_DIMMING_SC_TYPE() == _LOCAL_DIMMING_STEP_CHANGE_TYPE_ONE_STEP)
        {
            if((UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _ON) && (tLDHDR2084Lv[g_stColorLocalDimmingDCRData.ucColorDCRMaxY] > g_stColorLocalDimmingHDR10BoostData.usColorBoostLv))
            {
                g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = ucIdealAdimValue;
            }
#if(_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON)
            else if((UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON) && (tFREESYNCIILv[g_stColorLocalDimmingDCRData.ucColorDCRMaxY] > g_stColorLocalDimmingHDR10BoostData.usColorBoostLv))
            {
                g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = ucIdealAdimValue;
            }
#endif
            else
            {
                g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = ((((DWORD)32 * ucIdealAdimValue) + ((DWORD)(1024 - 32) * g_stColorLocalDimmingHDR10BoostData.ucColorLastApplyAdimValue)) + 512) / 1024;
            }
        }
        else
        {
            g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = ((((DWORD)32 * ucIdealAdimValue) + ((DWORD)(1024 - 32) * g_stColorLocalDimmingHDR10BoostData.ucColorLastApplyAdimValue)) + 512) / 1024;
        }


        if(g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue == g_stColorLocalDimmingHDR10BoostData.ucColorLastApplyAdimValue)
        {
            if(g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue > ucIdealAdimValue)
            {
                g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue - 1;
            }
            if(g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue < ucIdealAdimValue)
            {
                g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue = g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue + 1;
            }
        }

        if(UserCommonColorLocalDimmingBoostForceKernalValue() == _FALSE)
        {
            g_ucColorApplyCurrentAdim = g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingBoostValue;
        }
        else
        {
            g_ucColorApplyCurrentAdim = g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue;
        }

        // Gain Value
        if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _ON)
        {
            if(UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion) == _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
            {
                usNodeLvGain = (DWORD)(g_ucColorApplyCurrentAdim - 100) * (g_stColorLocalDimmingHDR10BoostData.ucColorGainValue - 100) / (_LOCAL_DIMMING_BOOST_ADMING - 100) + 100;
                usNodeLvGain = (DWORD)usNodeLvGain * 1024 / g_stColorLocalDimmingHDR10BoostData.ucColorGainValue;
            }
        }
#if(_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON)
        else if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
        {
            usNodeLvGain = (DWORD)(g_ucColorApplyCurrentAdim - 100) * (g_stColorLocalDimmingHDR10BoostData.ucColorGainValue - 100) / (_LOCAL_DIMMING_BOOST_ADMING - 100) + 100;
            usNodeLvGain = (DWORD)usNodeLvGain * 1024 / g_stColorLocalDimmingHDR10BoostData.ucColorGainValue;
        }
#endif
#if(_LOCAL_DIMMING_USER_GLOBAL_BOOST_SUPPORT == _ON)
        else
        {
            usNodeLvGain = (DWORD)(g_ucColorApplyCurrentAdim - 100) * (g_stColorLocalDimmingHDR10BoostData.ucColorGainValue - 100) / (_LOCAL_DIMMING_BOOST_ADMING - 100) + 100;
            usNodeLvGain = (DWORD)usNodeLvGain * 1024 / g_stColorLocalDimmingHDR10BoostData.ucColorGainValue;
        }
#endif
    }

    DebugMessageHDR("g_ucColorApplyCurrentAdim", g_ucColorApplyCurrentAdim);
    DebugMessageHDR("usNodeLvGain", usNodeLvGain);


#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    g_stColorLDRegionBoost.usGlobalBoostAdim = g_ucColorApplyCurrentAdim;
    g_stColorLDRegionBoost.usGlobalLedGain = usNodeLvGain;
#else
    ScalerColorLDBLModelBoostUniqueGainAdjust((((DWORD)usNodeLvGain << 16) + usNodeLvGain));
#endif
    g_stColorLocalDimmingDCRData.ucColorLastDCRMaxY = g_stColorLocalDimmingDCRData.ucColorDCRMaxY;
    g_stColorLocalDimmingHDR10BoostData.ucColorLastApplyAdimValue = g_ucColorApplyCurrentAdim;
}
//--------------------------------------------------
// Description  : Decide whether need to one step to target
// Input Value  : void
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
bit UserCommonColorLocalDimmingBoostForceKernalValue(void)
{
    if(((GET_LOCAL_DIMMING_PICTURE_TYPE() == _LOCAL_DIMMING_PICTURE_WHITE_AND_BLACK) || (GET_LOCAL_DIMMING_PICTURE_TYPE() == _LOCAL_DIMMING_PICTURE_TOTAL_WHITE) || (GET_LOCAL_DIMMING_PICTURE_TYPE() == _LOCAL_DIMMING_PICTURE_CORNER)) &&
       (g_stColorLocalDimmingDCRData.ucColorLastDCRMaxY < _LOCAL_DIMMING_BLACK_COLOR_CODE) && (g_stColorLocalDimmingDCRData.ucColorDCRMaxY >= _LOCAL_DIMMING_BLACK_COLOR_CODE))
    {
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Return the last applied boost vaue to user
// Input Value  : void
// Output Value : boost value
//--------------------------------------------------
BYTE UserCommonColorLocalDimmingBoostGetLastKernelBoostValue(void)
{
    return g_stColorLocalDimmingHDR10BoostData.ucColorLastApplyAdimValue;
}
#endif


#if((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
//--------------------------------------------------
// Description  : Send the boost command
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorLocalDimmingBoostSendCommand(void)
{
#if((_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _OFF))
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    g_bCpuSyncColorLocalDimmingSendAdimCmd = _TRUE;
    g_pstScpuSyncToKcpuCmd->unCmdBody.stColorLocalDimmingCmd.ucSubCmdType = _LOCAL_DIMMING_BACKLIGHT_SEND_ADIM;
    ScalerScpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_LOCAL_DIMMING, _SCALER_CPU_SYNC_TIMEOUT_NO_WAIT, _NULL_POINTER);
    usPreviousTime = g_usTimerCounter;
    do
    {
        ScalerScpuSyncHandler();

        if(g_bCpuSyncColorLocalDimmingSendAdimCmd == _FALSE)
        {
            break;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }while(usTimeElapsed <= _LOCAL_DIMMING_ADIMMING_TIMEOUT);
#else
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))
    ScalerCpuSyncColorLDSetScpuAdimStatus(_TRUE);
#endif
    ExternalDeviceInterfaceLedDriverBoostAdjust(g_ucColorApplyCurrentAdim);
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))
    ScalerCpuSyncColorLDSetScpuAdimStatus(_FALSE);
#endif
#endif
}
#endif

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide whether need to one step to target
// Input Value  : void
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
bit UserCommonColorLocalDimmingSceneChangeModify(WORD *pusColorApplyPWM, WORD *pusColorLastApplyPWM, WORD *pusColorHistoPWM, WORD *pusColorLastHistoPWM, WORD *pusColorHistoPWM2)
{
    WORD uscnt = 0;
    WORD usExposureRegion = 0;
    bit bSceneChange = _FALSE;

#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        if((pusColorLastApplyPWM[uscnt] < pusColorHistoPWM2[uscnt]) &&
           (pusColorLastHistoPWM[uscnt] < pusColorHistoPWM[uscnt]))
        {
            usExposureRegion = usExposureRegion + 1;
        }
    }
    DebugMessageHDR("ExposureRegion", usExposureRegion);
    // DebugMessageHDR("usExposureRegion", usExposureRegion);
    if(usExposureRegion >= (WORD)_LOCAL_DIMMING_TOTAL_REGION * _LOCAL_DIMMING_EXPOSURE_REGION_THD / 100)
    {
        bSceneChange = _TRUE;
    }
#else
    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        if(pusColorLastHistoPWM[uscnt] < pusColorHistoPWM[uscnt])
        {
            usExposureRegion = usExposureRegion + 1;
        }
    }
    DebugMessageHDR("ExposureRegion", usExposureRegion);
    // DebugMessageHDR("usExposureRegion", usExposureRegion);
    if(usExposureRegion >= (WORD)_LOCAL_DIMMING_TOTAL_REGION * _LOCAL_DIMMING_EXPOSURE_REGION_THD / 100)
    {
        if(ScalerColorLocalContrastDetectSceneChangeFlag(_1P_NORMAL_REGION, _LOCAL_CONTRAST_SCENE_CHANGE_BOTH_GLOBAL_BLOCK) == _TRUE)
        {
            bSceneChange = _TRUE;
        }
    }
#endif
    if(bSceneChange == _TRUE)
    {
        for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
        {
            // pusColorApplyPWM[uscnt] = (pusColorHistoPWM[uscnt] + 1) * 32;
            WORD usTargetPWM = pusColorHistoPWM[uscnt];
            // pusColorApplyPWM[uscnt] = 4095;
            pusColorApplyPWM[uscnt] = ((((DWORD)_LOCAL_DIMMING_SCENE_CHANGE_STEP_VALUE * usTargetPWM) + ((DWORD)(1024 - _LOCAL_DIMMING_SCENE_CHANGE_STEP_VALUE) * pusColorLastApplyPWM[uscnt])) + 512) / 1024;
            if(pusColorApplyPWM[uscnt] > 4095)
            {
                pusColorApplyPWM[uscnt] = 4095;
            }
        }
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _ON)
        ScalerColorLocalContrastClearSceneChangeFlag(_1P_NORMAL_REGION, _LOCAL_CONTRAST_SCENE_CHANGE_BOTH_GLOBAL_BLOCK);
#endif
    }
    return bSceneChange;
}
#endif

//--------------------------------------------------
// Description  : Adjust Histo LUT
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorLocalDimmingHistoLUTAdjust(EnumLocalDimmingType enumLDHisType)
{
    EnumLocalDimmingType enumLDHisApplyType = _LOCAL_DIMMING_SDR;
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        enumLDHisApplyType = UserInterfaceColorLocalDimmingMultiPPolicy();
    }
    else
    {
        enumLDHisApplyType = enumLDHisType;
    }
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
    ScalerColorLDHistoSetBlackValue(_LOCAL_DIMMING_LINEAR_BLACK_COLOR_CODE);
    ScalerColorLDHistoSetWhiteValue(_LOCAL_DIMMING_LINEAR_WHITE_COLOR_CODE);
    if(enumLDHisApplyType == _LOCAL_DIMMING_SDR)
    {
        ScalerColorLDHistoSetWhiteLUT(_LOCAL_DIMMING_WHITE_LUT_VALUE_SDR);
        ScalerColorLDHistoSetBlackLUT(_LOCAL_DIMMING_BLACK_LUT_VALUE_SDR);
    }
    else
    {
        ScalerColorLDHistoSetWhiteLUT(_LOCAL_DIMMING_WHITE_LUT_VALUE_HDR);
        ScalerColorLDHistoSetBlackLUT(_LOCAL_DIMMING_BLACK_LUT_VALUE_HDR);
    }
#endif

    ScalerColorLDHistoLutChangeType(enumLDHisApplyType);
}
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalDimmingSyncToScpuHandler(void)
{
    switch(g_stCpuSyncToScpuCmd.unCmdBody.stColorLocalDimmingCmd.ucSubCmdType)
    {
        case _LOCAL_DIMMING_PWM_INITIAL:
            UserCommonColorLocalDimmingPWMInitial();
            DebugMessageHDR("UserCommonColorLocalDimmingPWMInitial", g_pusColorLastApplyPWM[1]);
            break;
        default:
            break;
    }
}

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalDimmingSyncBoostModify(void)
{
    WORD usI = 0;

    __attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
    BYTE pucNodeLvGainTable[_LOCAL_DIMMING_TOTAL_REGION * 2];
    WORD *pusNodeLvGain = (WORD *)pucNodeLvGainTable;
    BYTE ucNodeLvGainH = 0x04;
    BYTE ucNodeLvGainL = 0x00;

    ucNodeLvGainH = g_stCpuSyncToScpuCmd.unCmdBody.stColorLocalDimmingCmd.unSubCmdBody.stBoostData.ucNodeLvGainByteH;
    ucNodeLvGainL = g_stCpuSyncToScpuCmd.unCmdBody.stColorLocalDimmingCmd.unSubCmdBody.stBoostData.ucNodeLvGainByteL;
    for(usI = 0; usI < _LOCAL_DIMMING_TOTAL_REGION; usI++)
    {
        pusNodeLvGain[usI] = TO_WORD(ucNodeLvGainH, ucNodeLvGainL);
    }
    ScalerColorLDBLModelBoostGainAdjust(pucNodeLvGainTable, (_LOCAL_DIMMING_TOTAL_REGION * 2), 0);
}
#endif


#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonColorLocalDimmingSyncSceneChangeModify(WORD *pusColorApplyPWM, WORD *pusColorLastApplyPWM, WORD *pusColorHistoPWM, WORD *pusColorLastHistoPWM, WORD *pusColorHistoPWM2)
{
    WORD uscnt = 0;
    WORD usExposureRegion = 0;
    bit bSceneChange = _FALSE;

    for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
    {
        if((g_pusColorLastApplyPWM[uscnt] < pusColorHistoPWM2[uscnt]) &&
           (pusColorLastHistoPWM[uscnt] < pusColorHistoPWM[uscnt]))
        {
            usExposureRegion = usExposureRegion + 1;
        }
    }
    if(usExposureRegion >= (DWORD)_LOCAL_DIMMING_TOTAL_REGION * _LOCAL_DIMMING_EXPOSURE_REGION_THD / 100)
    {
        bSceneChange = _TRUE;
    }

    if(bSceneChange == _TRUE)
    {
        for(uscnt = 0; uscnt < _LOCAL_DIMMING_TOTAL_REGION; uscnt++)
        {
            // pusColorApplyPWM[uscnt] = (pusColorHistoPWM[uscnt] + 1) * 32;
            WORD usTargetPWM = pusColorHistoPWM[uscnt];
            // pusColorApplyPWM[uscnt] = 4095;
            pusColorApplyPWM[uscnt] = ((((DWORD)_LOCAL_DIMMING_SCENE_CHANGE_STEP_VALUE * usTargetPWM) + ((DWORD)(1024 - _LOCAL_DIMMING_SCENE_CHANGE_STEP_VALUE) * pusColorLastApplyPWM[uscnt])) + 512) / 1024;
            if(pusColorApplyPWM[uscnt] > 4095)
            {
                pusColorApplyPWM[uscnt] = 4095;
            }
        }
    }
    return bSceneChange;
}
#endif

#endif // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE))

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_SCPU_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingSyncToKcpuHandler(void)
{
    switch(g_stCpuSyncToKcpuCmd.unCmdBody.stColorLocalDimmingCmd.ucSubCmdType)
    {
        case _LOCAL_DIMMING_BACKLIGHT_RESTORE:
            g_bCpuSyncColorLocalDimmingRestoreBacklight = _TRUE;
            ScalerCpuHalSetMainCpuSw0IRQ();
            break;
#if(_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _OFF)
        case _LOCAL_DIMMING_BACKLIGHT_SEND_ADIM:
            g_bCpuSyncColorLocalDimmingSendAdimCmd = _TRUE;
            ScalerCpuHalSetMainCpuSw0IRQ();
            break;
#endif
        default:
            break;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingMainCpuPendSVCallback(void)
{
    if(g_bCpuSyncColorLocalDimmingRestoreBacklight == _TRUE)
    {
        g_bCpuSyncColorLocalDimmingRestoreBacklight = _FALSE;
        UserCommonColorLocalDimmingRestoreBacklight();
    }
#if(((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM)) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _OFF))
    if(g_bCpuSyncColorLocalDimmingSendAdimCmd == _TRUE)
    {
        UserCommonColorLocalDimmingBoostSendCommand();
        g_bCpuSyncColorLocalDimmingSendAdimCmd = _FALSE;
    }
#endif
}
#endif

#if((_HW_CPU32_IS_BOOT_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonColorLocalDimmingGetKCPUStage(void)
{
    g_stColorLocalDimmingKCPUStateValue.enumLocalDimmingStatus = UserCommonColorLocalDimmingGetEnableStatus();
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingBoostValue = UserInterfaceColorLocalDimmingBoostCoolingAdjust(g_stColorLocalDimmingHDR10BoostData.ucColorApplyAdimValue, GET_LOCAL_DIMMING_PWM_TOTAL_RATIO());
#endif
#if(_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE)
    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim = UserInterfaceColorLocalDimmingBoostGetCompADdim();
    g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim = MINOF(g_stColorLocalDimmingKCPUStateValue.ucLocalDimmingCompADdim, _LOCAL_DIMMING_MAX_COMPENSATE_GAIN);
#endif
#if((_LOCAL_DIMMING_USING_YAVG_INFO == _ON) && (_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON))
    g_stColorLocalDimmingKCPUStateValue.bYavgReadEnableStatus = UserCommonColorLocalContrastCheckReadYavgSupport();
#endif
}
#endif
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
#if((_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Adjust Local D-dimming PWM to Local A-dimming DAC
// Input Value  : pusColorApplyAdim --> Local Adimmming Target Buffer
//                bPwm2SpiTxNow --> Transmit SPI immediately
// Output Value : None
//--------------------------------------------------
void UserCommonColorLocalDimmingMBRAdimAdjust(void)
{
    if(GET_MBR_BACKLIGHT_MODE() != _BACKLIGHT_MODE_CONSTANT)
    {
        ExternalDeviceInterfaceLedDriverAdimSpiFormat(g_pusColorApplyPWM);
    }
}
#endif
#endif
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit UserCommonColorLocalDimmingCheckStatusBeforeBLFW(void)
{
    if(ScalerColorLDBLModelManualSwitchStatus() == _FALSE)
    {
        return _FALSE;
    }
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
    if(ScalerColorLDPwmToSpiPollingNewSpiTxDoneFlag() == _FALSE)
    {
        return _FALSE;
    }
#endif
    return _TRUE;
}

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Main Function of Region Boost
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingRegionBoostModify(void)
{
    BYTE ucCnt = 0;
    BYTE ucVCnt = 0;
    BYTE ucHCnt = 0;
    WORD usLedGainRegionIndex = 0;

    // Table pointer for now
    WORD *pusNonBoostGainTable = tBoostAreaData[_LOCAL_DIMMING_PQ_NO_BOOST_GAIN];
    WORD *pusBoostGainTable = tBoostAreaData[_LOCAL_DIMMING_PQ_BOOST_GAIN];
    WORD *pusIGCode = tBoostAreaData[_LOCAL_DIMMING_IGCODE_HDR];

    // for fit Adim and led gain value
    WORD usNonBoostGain = 1024;
    WORD usBoostGain = 1024;
    WORD usGainTemp = 1024;
    WORD usIdealAdimValue = 1000;
    WORD usAdimValueTemp = 1000;
    WORD pusCurrentAdim[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    WORD pusCurrentGainTable[_LOCAL_DIMMING_TOTAL_REGION] = {0};

    __attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
    BYTE pucLedGainTable[_LOCAL_DIMMING_PANEL_REGION_VERTICAL * _LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH * 4] = {0};


    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif

    if(UserCommonColorLocalDimmingRegionBoostCheckSource(enumDisplayRegion) == _TRUE)
    {
#if(_FREESYNC_II_SUPPORT == _ON)
        if((g_stColorLocalDimmingPerformanceAdjust.b1BoostContrastModeEnable == _ENABLE) && (UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON))
        {
            pusIGCode = tBoostAreaData[_LOCAL_DIMMING_IGCODE_FSII];
        }
#endif

        // Get Adim Stage
        UserCommonColorLocalDimmingRegionBoostFALLSwitch();

        // choose PQ or contrast mode
        if(g_stColorLocalDimmingPerformanceAdjust.b1BoostContrastModeEnable == _ENABLE)
        {
            if(UserCommonColorLocalDimmingRegionBoostContrastModeCheck(pusIGCode) == _TRUE)
            {
                g_stColorLDRegionBoost.enumLDAdimMode = _LOCAL_DIMMING_TRUE_CONTRAST;
                pusNonBoostGainTable = tBoostAreaData[_LOCAL_DIMMING_CONTRAST_NO_BOOST_GAIN];
                pusBoostGainTable = tBoostAreaData[_LOCAL_DIMMING_CONTRAST_BOOST_GAIN];
            }
            else
            {
                g_stColorLDRegionBoost.enumLDAdimMode = _LOCAL_DIMMING_TRUE_PQ;
            }
            DebugMessageHDR("g_stColorLDRegionBoost.enumLDAdimMode", g_stColorLDRegionBoost.enumLDAdimMode);
            DebugMessageHDR("IGCode", pusIGCode[g_stColorLDRegionBoost.ucCurrentGainIndex]);
        }

        // Apply goal of Adim and led gain
        usNonBoostGain = pusNonBoostGainTable[g_stColorLDRegionBoost.ucCurrentGainIndex];
        usBoostGain = pusBoostGainTable[g_stColorLDRegionBoost.ucCurrentGainIndex];
        usIdealAdimValue = tBoostAreaData[_LOCAL_DIMMING_STAGE_BOOST_ADIM][g_stColorLDRegionBoost.ucCurrentGainIndex];

#if(_FREESYNC_II_SUPPORT == _ON)
        if((UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON) && (g_stColorLDRegionBoost.ucCurrentGainIndex == _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE))
        {
            usNonBoostGain = 1024;
            usBoostGain = 1024;
        }
#endif
        // Calculate Adim and led gain value for each area
        for(ucCnt = 0; ucCnt < _LOCAL_DIMMING_TOTAL_REGION; ucCnt++)
        {
            // boost or non-boost
            if(g_pusColorHistoPWM[ucCnt] >= _LOCAL_DIMMING_BOOST_THD)
            {
                pusCurrentAdim[ucCnt] = usIdealAdimValue;
                pusCurrentGainTable[ucCnt] = usBoostGain;
            }
            else
            {
                pusCurrentAdim[ucCnt] = 1000;
                pusCurrentGainTable[ucCnt] = usNonBoostGain;
            }
        }

        // Led Gain and Adim Smooth
        UserCommonColorLocalDimmingRegionBoostSmooth(pusCurrentAdim, pusCurrentGainTable);
    }
    else
    {
        for(ucCnt = 0; ucCnt < _LOCAL_DIMMING_TOTAL_REGION; ucCnt++)
        {
            pusCurrentAdim[ucCnt] = 1000;
            pusCurrentGainTable[ucCnt] = 1024;
        }
    }

    if((GET_LOCAL_DIMMING_SC_TYPE() == _LOCAL_DIMMING_STEP_CHANGE_TYPE_NORMAL) || (GET_LOCAL_DIMMING_PICTURE_TYPE() == _LOCAL_DIMMING_PICTURE_WHITE_AND_BLACK))
    {
        for(ucCnt = 0; ucCnt < _LOCAL_DIMMING_TOTAL_REGION; ucCnt++)
        {
            // Adim adjust
            usAdimValueTemp = pusCurrentAdim[ucCnt];
            pusCurrentAdim[ucCnt] = (WORD)(((DWORD)g_pusColorLastRegionAdim[ucCnt] * (DWORD)(1000 - (DWORD)(g_stColorLocalDimmingPerformanceAdjust.usRegionBoostAdimStep)) + (DWORD)usAdimValueTemp * (DWORD)(g_stColorLocalDimmingPerformanceAdjust.usRegionBoostAdimStep) + 500) / 1000);
            if(pusCurrentAdim[ucCnt] == g_pusColorLastRegionAdim[ucCnt])
            {
                if(g_pusColorLastRegionAdim[ucCnt] < usAdimValueTemp)
                {
                    pusCurrentAdim[ucCnt] = pusCurrentAdim[ucCnt] + 1;
                }
                else if (g_pusColorLastRegionAdim[ucCnt] > usAdimValueTemp)
                {
                    pusCurrentAdim[ucCnt] = pusCurrentAdim[ucCnt] - 1;
                }
            }

            // led gain adjust
            usGainTemp = pusCurrentGainTable[ucCnt];
            pusCurrentGainTable[ucCnt] = (WORD)(((DWORD)g_pusColorLastRegionGain[ucCnt] * (DWORD)(1000 - (DWORD)(g_stColorLocalDimmingPerformanceAdjust.usRegionBoostGainStep)) + (DWORD)usGainTemp * (DWORD)(g_stColorLocalDimmingPerformanceAdjust.usRegionBoostGainStep) + 500) / 1000);

            if(pusCurrentGainTable[ucCnt] == g_pusColorLastRegionGain[ucCnt])
            {
                if(g_pusColorLastRegionGain[ucCnt] < usGainTemp)
                {
                    pusCurrentGainTable[ucCnt] = pusCurrentGainTable[ucCnt] + 1;
                }
                else if (g_pusColorLastRegionGain[ucCnt] > usGainTemp)
                {
                    pusCurrentGainTable[ucCnt] = pusCurrentGainTable[ucCnt] - 1;
                }
            }
        }
    }

    // save last value for next loop
    memcpy(g_pusColorLastRegionAdim, pusCurrentAdim, sizeof(g_pusColorLastRegionAdim));
    memcpy(g_pusColorLastRegionGain, pusCurrentGainTable, sizeof(g_pusColorLastRegionGain));

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    for(ucCnt = 0; ucCnt < _LOCAL_DIMMING_TOTAL_REGION; ucCnt++)
    {
        pusCurrentGainTable[ucCnt] = (WORD)(((DWORD)pusCurrentGainTable[ucCnt] * (DWORD)g_stColorLDRegionBoost.usGlobalLedGain + 512) / 1024);
        pusCurrentAdim[ucCnt] = (WORD)((DWORD)pusCurrentAdim[ucCnt] * (DWORD)g_stColorLDRegionBoost.usGlobalBoostAdim / (DWORD)100);
    }
#endif

    // Led Gain Adjust
    ucCnt = 0;
    for(ucVCnt = 0; ucVCnt < _LOCAL_DIMMING_PANEL_REGION_VERTICAL; ucVCnt++)
    {
        for(ucHCnt = 0; ucHCnt < _LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH; ucHCnt++)
        {
            if(!((ucHCnt >= _LOCAL_DIMMING_BLMODEL_GAIN_ZERO_PADDING_LEFT) && (ucHCnt < _LOCAL_DIMMING_BLMODEL_GAIN_ZERO_PADDING_RIGHT)))
            {
                // BL Model Top Led Gain
                pucLedGainTable[2 * ucCnt + 1] = (BYTE)((pusCurrentGainTable[usLedGainRegionIndex] & 0xFF00) >> 8);
                pucLedGainTable[2 * ucCnt] = (BYTE)(pusCurrentGainTable[usLedGainRegionIndex] & 0x00FF);

                // BL Model Bottom Led Gain
                pucLedGainTable[2 * (ucCnt + 1) + 1] = (BYTE)((pusCurrentGainTable[usLedGainRegionIndex] & 0xFF00) >> 8);
                pucLedGainTable[2 * (ucCnt + 1)] = (BYTE)(pusCurrentGainTable[usLedGainRegionIndex] & 0x00FF);

                usLedGainRegionIndex++;
            }
            ucCnt += 2;
        }
    }

    ScalerColorLDBLModelBoostGainAdjust(pucLedGainTable, (_LOCAL_DIMMING_PANEL_REGION_VERTICAL * _LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH * 4), 0);
    memcpy(g_stColorLDRegionBoost.pusBoostGain, pusCurrentAdim, sizeof(pusCurrentAdim));
}

//--------------------------------------------------
// Description  : Check Source for Region Boost
// Input Value  : enumDisplayRegion
// Output Value : execute boost bit
//--------------------------------------------------
bit UserCommonColorLocalDimmingRegionBoostCheckSource(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
    if(GET_MBR_BACKLIGHT_MODE() != _BACKLIGHT_MODE_CONSTANT)
    {
        return _FALSE;
    }
#endif
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _ON)
    {
        return _TRUE;
    }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        return _TRUE;
    }
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if there is a need to go Contrast Mode
// Input Value  : saturation IG code of each stage
// Output Value : execute contrast mode bit
//--------------------------------------------------
bit UserCommonColorLocalDimmingRegionBoostContrastModeCheck(WORD *pusIGCode)
{
    if(GET_LOCAL_DIMMING_PICTURE_TYPE() == _LOCAL_DIMMING_PICTURE_TOTAL_BLACK)
    {
        return _FALSE;
    }

#if(_HDR10_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif

    // No Contrast Mode in HDR TM Case
    if((UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _ON) && (UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion) != _HDR10_MAX_MASTERING_LV_TYPE_NOTM))
    {
        return _FALSE;  // HDR Tone Mapping mode
    }
#endif

    if((UserCommonColorLocalDimmingRegionBoostGetMaxRGBRatio(pusIGCode[g_stColorLDRegionBoost.ucCurrentGainIndex], tMaxRGBBeamCode[pusIGCode[g_stColorLDRegionBoost.ucCurrentGainIndex] >> 4]) >= _LOCAL_DIMMING_OVER_EXP) && (g_stColorLDRegionBoost.enumLocalDimmingIGGoal != _LOCAL_DIMMING_LOCAL_ADIM_FALL))
    {
        return _TRUE;
    }
    else if((g_stColorLDRegionBoost.b1HistoIndexFix == _TRUE) && (g_stColorLDRegionBoost.enumLDAdimMode == _LOCAL_DIMMING_TRUE_CONTRAST))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Calculate the ratio of RGB which is over ability
// Input Value  : Max RGB of current stage, DCR Beam Index of current stage
// Output Value : overexposure ratio
//--------------------------------------------------
BYTE UserCommonColorLocalDimmingRegionBoostGetMaxRGBRatio(BYTE ucMaxRGBTHD, WORD usIndexBeam)
{
    if(MAXOF(MAXOF(g_stColorLocalDimmingDCRData.ucMaxR, g_stColorLocalDimmingDCRData.ucMaxG), g_stColorLocalDimmingDCRData.ucMaxB) > ucMaxRGBTHD)
    {
        BYTE ucCnt = 0;
        BYTE ucMaxRGBRatio = 0;
        BYTE ucMaxRGBIndex = 0;
        BYTE pucMaxRGB[3] = {0};
        DWORD pulMaxRGBNum[3] = {0};
        DWORD ulPanelSize = ((DWORD)_PANEL_DH_WIDTH) * ((DWORD)_PANEL_DV_HEIGHT);

        pucMaxRGB[0] = g_stColorLocalDimmingDCRData.ucMaxR;
        pucMaxRGB[1] = g_stColorLocalDimmingDCRData.ucMaxG;
        pucMaxRGB[2] = g_stColorLocalDimmingDCRData.ucMaxB;
        pulMaxRGBNum[0] = g_stColorLocalDimmingDCRData.ulColorMaxRNum;
        pulMaxRGBNum[1] = g_stColorLocalDimmingDCRData.ulColorMaxGNum;
        pulMaxRGBNum[2] = g_stColorLocalDimmingDCRData.ulColorMaxBNum;

        for(ucCnt = 1; ucCnt < 3; ucCnt++)
        {
            if(pucMaxRGB[ucCnt] > pucMaxRGB[ucMaxRGBIndex])
            {
                ucMaxRGBIndex = ucCnt;
            }
            else if(pucMaxRGB[ucCnt] == pucMaxRGB[ucMaxRGBIndex])
            {
                if(pulMaxRGBNum[ucCnt] > pulMaxRGBNum[ucMaxRGBIndex])
                {
                    ucMaxRGBIndex = ucCnt;
                }
            }
        }

        ucMaxRGBRatio = (BYTE)(pulMaxRGBNum[ucMaxRGBIndex] * (DWORD)100 / ulPanelSize);

        if((WORD)pucMaxRGB[ucMaxRGBIndex] > usIndexBeam)
        {
            return _LOCAL_DIMMING_OVER_EXP;
        }
        else
        {
            return ucMaxRGBRatio;
        }
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Smooth Function of Adim and Led gain value
// Input Value  : Adim value array, Led Gain value array
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingRegionBoostSmooth(WORD *pusCurrentAdim, WORD *pusCurrentGainTable)
{
    WORD pusCurrentAdimTemp[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    WORD pusCurrentGainTableTemp[_LOCAL_DIMMING_TOTAL_REGION] = {0};
    WORD pusAreaAdimSmooth[] = {21, 22, 21};

    SWORD shIndex = 0;
    SWORD shAreaIndexH = 0;
    SWORD shAreaIndexV = 0;
    SWORD shAreaIndex = 0;
    SWORD shSpanIndex = 0;

    DWORD ulTemp1 = 0;
    DWORD ulTemp2 = 0;

    memcpy(pusCurrentAdimTemp, pusCurrentAdim, sizeof(pusCurrentAdimTemp));
    memcpy(pusCurrentGainTableTemp, pusCurrentGainTable, sizeof(pusCurrentGainTableTemp));

    for(shAreaIndexV = 0; shAreaIndexV < _LOCAL_DIMMING_PANEL_REGION_VERTICAL; shAreaIndexV++)
    {
        for(shAreaIndexH = 0; shAreaIndexH < _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL; shAreaIndexH++)
        {
            ulTemp1 = 0;
            ulTemp2 = 0;
            for(shSpanIndex = -1; shSpanIndex <= 1; shSpanIndex++)
            {
                shIndex = shAreaIndexH + shSpanIndex;
                shIndex = MAXOF(0, shIndex);
                shIndex = MINOF(_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL - 1, shIndex);
                shIndex = shAreaIndexV * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + shIndex;

                ulTemp1 += pusCurrentAdim[shIndex] * pusAreaAdimSmooth[shSpanIndex + 1];
                ulTemp2 += pusCurrentGainTable[shIndex] * pusAreaAdimSmooth[shSpanIndex + 1];
            }
            shAreaIndex = shAreaIndexV * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + shAreaIndexH;
            pusCurrentAdimTemp[shAreaIndex] = (ulTemp1 + 32) >> 6;
            pusCurrentGainTableTemp[shAreaIndex] = (ulTemp2 + 32) >> 6;

            pusCurrentAdimTemp[shAreaIndex] = MAXOF(pusCurrentAdimTemp[shAreaIndex], pusCurrentAdim[shAreaIndex]);
            pusCurrentGainTableTemp[shAreaIndex] = MAXOF(pusCurrentGainTableTemp[shAreaIndex], pusCurrentGainTable[shAreaIndex]);
        }
    }

    memcpy(pusCurrentAdim, pusCurrentAdimTemp, sizeof(pusCurrentAdimTemp));
    memcpy(pusCurrentGainTable, pusCurrentGainTableTemp, sizeof(pusCurrentGainTableTemp));
}

//--------------------------------------------------
// Description  : distinguish FALL and CLL / decide initial Adim Stage
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingRegionBoostFALLSwitch(void)
{
    static BYTE sucLoopCount = 0;
    static EnumLocalDimmingLocalAdimIG senumLastAdimIGTemp = _LOCAL_DIMMING_LOCAL_ADIM_CLL;
    EnumLocalDimmingLocalAdimIG enumCurrentAdimIGTemp = _LOCAL_DIMMING_LOCAL_ADIM_CLL;

    SWORD shCnt = 0;
    BYTE ucAdimGainIndex = 0;
    WORD usBoostArea = 0;

    // Check IG Mode Based on Current Picture
    BYTE ucMaxR = g_stColorLocalDimmingDCRData.ucMaxR;
    BYTE ucMaxG = g_stColorLocalDimmingDCRData.ucMaxG;
    BYTE ucMaxB = g_stColorLocalDimmingDCRData.ucMaxB;
    BYTE ucMinR = g_stColorLocalDimmingDCRData.ucMinR;
    BYTE ucMinG = g_stColorLocalDimmingDCRData.ucMinG;
    BYTE ucMinB = g_stColorLocalDimmingDCRData.ucMinB;

    if(((ucMaxR - ucMinR) <= 1) &&
       ((ucMaxG - ucMinG) <= 1) &&
       ((ucMaxB - ucMinB) <= 1))
    {
        enumCurrentAdimIGTemp = _LOCAL_DIMMING_LOCAL_ADIM_FALL;
    }
    else
    {
        enumCurrentAdimIGTemp = _LOCAL_DIMMING_LOCAL_ADIM_CLL;
    }

    // Switch IG(CLL/FALL) (if it is stable)
    sucLoopCount = (enumCurrentAdimIGTemp == senumLastAdimIGTemp) ? sucLoopCount + 1 : 0;
    senumLastAdimIGTemp = enumCurrentAdimIGTemp;

    if(sucLoopCount > _LOCAL_DIMMING_LOCAL_ADIM_FRAME_COUNT)
    {
        g_stColorLDRegionBoost.enumLocalDimmingIGGoal = enumCurrentAdimIGTemp;
        sucLoopCount = 0;
    }

    // find Adim Stage
    if(g_stColorLDRegionBoost.enumLocalDimmingIGGoal == _LOCAL_DIMMING_LOCAL_ADIM_FALL)
    {
        ucAdimGainIndex = _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE;
    }
    else
    {
        usBoostArea = UserCommonColorLocalDimmingRegionBoostGetBoostStage();
        for(shCnt = _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE - 1; shCnt >= 0; shCnt--)
        {
            if(usBoostArea <= tBoostAreaData[_LOCAL_DIMMING_AREA_THD][shCnt])
            {
                ucAdimGainIndex = shCnt;
                break;
            }
        }
        DebugMessageHDR("usBoostArea", usBoostArea);
    }
    DebugMessageHDR("ucAdimGainIndex", ucAdimGainIndex);

    // Modify Adim Stage based on Loading
    g_stColorLDRegionBoost.ucCurrentGainIndex = UserCommonColorLocalDimmingRegionBoostLoadingMod(ucAdimGainIndex);
}

//--------------------------------------------------
// Description  : modify Adim Stage based on Loading of PWM and Aim for each area
// Input Value  : initial Adim stage index
// Output Value : none
//--------------------------------------------------
BYTE UserCommonColorLocalDimmingRegionBoostLoadingMod(BYTE ucAdimGainIndex)
{
    DWORD ulSum = 0;
    if((ucAdimGainIndex == _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE - 1) || (ucAdimGainIndex == 0) || (ucAdimGainIndex == _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE))  // no boost
    {
        return ucAdimGainIndex;
    }

    do
    {
        WORD usI = 0;
        WORD usTempAdim = tBoostAreaData[_LOCAL_DIMMING_STAGE_BOOST_ADIM][ucAdimGainIndex];
        ulSum = 0;

        for(usI = 0; usI < _LOCAL_DIMMING_TOTAL_REGION; usI++)
        {
            ulSum += (DWORD)(((g_pusColorHistoPWM[usI] >= _LOCAL_DIMMING_BOOST_THD) ? usTempAdim : 1000) * (g_pusColorApplyPWM[usI] >> 5));
        }
    }
    while((ulSum > ((DWORD)_LOCAL_DIMMING_REGION_BOOST_SUM_THD * 1000)) && (--ucAdimGainIndex > 0));

    return ucAdimGainIndex;
}

//--------------------------------------------------
// Description  : find a suitable Adim Stage
// Input Value  : none
// Output Value : suitable Adim stage
//--------------------------------------------------
WORD UserCommonColorLocalDimmingRegionBoostGetBoostStage(void)
{
    WORD usCnt = 0;
    WORD usBoostStage = 0;

    for(usCnt = 0; usCnt < _LOCAL_DIMMING_TOTAL_REGION; usCnt++)
    {
        usBoostStage += (g_pusColorHistoPWM[usCnt] == _LOCAL_DIMMING_BOOST_THD) ? 1 : 0;
    }
    return usBoostStage;
}


//--------------------------------------------------
// Description  : send Adim data of each region
// Input Value  : Start Address, Adim Data Array, apply upd sync bit
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingSetRegionBoostAdimValue(BYTE ucStartAddr, BYTE *pucDataBuffer, bit bApplyUpdSync)
{
    BYTE ucI = 0;
    BYTE ucICIndex = 0;
    BYTE ucDataIndex = 0;

#if(_LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM != 0)
    for(ucI = 0; ucI < _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM; ucI++)
    {
        UserCommonColorSpiSetCommandRegion(ucICIndex + 1, ucStartAddr, tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[ucICIndex], pucDataBuffer + ucDataIndex, bApplyUpdSync);
        ucDataIndex += tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[ucICIndex];
        ucICIndex++;
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM != 0)
    for(ucI = 0; ucI < _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM; ucI++)
    {
        UserCommonColorSpiSetCommandRegion(ucICIndex + 1, ucStartAddr, tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[ucICIndex], pucDataBuffer + ucDataIndex, bApplyUpdSync);
        ucDataIndex += tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[ucICIndex];
        ucICIndex++;
    }
#endif

#if(_LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM != 0)
    for(ucI = 0; ucI < _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM; ucI++)
    {
        UserCommonColorSpiSetCommandRegion(ucICIndex + 1, ucStartAddr, tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[ucICIndex], pucDataBuffer + ucDataIndex, bApplyUpdSync);
        ucDataIndex += tCOLOR_LOCALDIMMING_ADIM_DATA_NUM[ucICIndex];
        ucICIndex++;
    }
#endif
}
#endif


#if(_LOCAL_DIMMING_ADIM_MODIFY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Adim Value
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingLocalAdimModify(void)
{
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    UserCommonColorLocalDimmingBoostModify();
#endif

#if(_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM)
    UserCommonColorLocalDimmingCompByAdim();
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    UserCommonColorLocalDimmingRegionBoostModify();
#endif
}

//--------------------------------------------------
// Description  : Send Adim Command
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void UserCommonColorLocalDimmingLocalAdimSendCommand(void)
{
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    WORD pusRemapBoostGain[_LOCAL_DIMMING_TOTAL_REGION];
    ScalerSpiDimmingLocalDimmingRegionBoostAdjust(g_stColorLDRegionBoost.pusBoostGain, pusRemapBoostGain);
    ExternalDeviceInterfaceLedDriverRegionBoostAdjust(pusRemapBoostGain);
#elif((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
    UserCommonColorLocalDimmingBoostSendCommand();
#endif
}
#endif

#if(_LOCAL_DIMMING_MULTI_TABLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Change Local Dimming Initial Table for multi-panel case
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorLocalDimmingChangeInitialTable(void)
{
    UserCommonColorLocalDimmingEnable(_FUNCTION_OFF);
    ScalerColorLDHistoInitial(_LOCAL_DIMMING_HISTO_COVERRATE);
    ScalerColorLDPWMProcInitial();
    ScalerColorLDBLModelInitial();
}
#endif
#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)
