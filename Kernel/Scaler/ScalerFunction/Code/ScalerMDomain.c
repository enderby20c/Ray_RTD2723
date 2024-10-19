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
// ID Code      : ScalerMDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MDOMAIN__

#include "ScalerFunctionInclude.h"
#include "MDomain/ScalerMDomain.h"

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(((_PANEL_PIXEL_CLOCK + (_PANEL_PIXEL_CLOCK / 100)) >= _PANEL_PIXEL_CLOCK_MAX) ||\
    ((_PANEL_PIXEL_CLOCK - (_PANEL_PIXEL_CLOCK / 100)) <= _PANEL_PIXEL_CLOCK_MIN))
#warning "NOTE: Panel Typ is under 1% from Panel Max/min !!!"
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_MN_FRAME_SYNC_SUPPORT == _ON)
#warning "NOTE: MN frame sync timing when Eagle sight enable, main/ sub display maybe async !!!"
#endif

#if(_EAGLE_SIGHT_FREERUN_SUPPORT == _ON)
#warning "NOTE: _EAGLE_SIGHT_FREERUN_SUPPORT Could Be _ON Only for SD test"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
DWORD g_ulMDomainDClkFreq;

StructMDomainInfo g_stMDomainInfo;
StructTimingInfo g_stMDomainInputData;
StructDisplayInfo g_stMDomainOutputData;
StructMDomainBackupInfo g_pstMDomainBackupInfo[_MULTI_DISPLAY_MAX];

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
bit g_bMDomainAspectOriginMode = 0;
#endif

WORD g_usMDomainDVFreq;

#if(_OD_FUNCTION == _ON)
DWORD g_ulMDomainFRCMemoryRemainBW;
#endif

#if(_FRC_SUPPORT == _ON)
StructFRCInfo g_pstMDomainFRCInfo[_HW_I_DOMAIN_PATH_COUNT];
#endif

StructFifoInfo g_pstMDomainFifoInfo[_HW_I_DOMAIN_PATH_COUNT];

StructMDomainFSActiveInfo g_stMDomainFSActiveInfo;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : M Domain Main Process
// Input Value  : None
// Output Value : M domain check pass or fail
//--------------------------------------------------
bit ScalerMDomainControl(void)
{
    StructSDRAMDataInfo stFIFOScaling = {0};

#if(_HDMI21_ALLM_SUPPORT == _ON)
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE)) // frame sync main clear allm
#endif
    {
        CLR_FRC_ALLM_ON_STATUS();
        CLR_FRC_ALLM_INPUT_PORT();
    }
#endif

    SET_MEMORY_DVF_SELECT(ScalerDisplaySelectDVFMode());
    ScalerDisplaySetDVFreq();

    SET_MEMORY_WORK_TYPE(ScalerMDomainMemoryConfig());

    // Select Memory Configuration Type
    SET_MEMORY_CONFIG_SELECT(ScalerMDomainMemorySelectConfirm());

    // Calculate Dclk and DVtotal
    ScalerMDomainCalculateDclkDVtotal(GET_MEMORY_CONFIG_SELECT());

    // Disable Spread Spectrum
    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        // Disable Spread Spectrum
        ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _OFF);
    }

    // Get Scaling size in FIFO
    if(ScalerScalingGetFIFOScalingSize(&stFIFOScaling) == _FAIL)
    {
        DebugMessageScaler("Fail : Calculate FIFO Size", stFIFOScaling.usInputHWidth);
        return _FALSE;
    }

    // Scaling Down Setting
    ScalerScalingSetScalingDown(&stFIFOScaling);

    DebugMessageScaler("Memory Work Select", GET_MEMORY_CONFIG_SELECT());

#if(_M_DOMAIN_FRAMESYNC_ACTIVE_TIMING_INFO_SUPPORT == _ON)
    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        SET_MDOMAIN_FRAMESYNC_ACTIVE_INFO();
    }
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Set Memory Utilization
    switch(GET_MEMORY_CONFIG_SELECT())
    {
        case _FRAME_SYNC_LINE_BUFFER:

            // Initial M Domain Block
            ScalerMemoryInitial();

            // Set FIFO freq.
            ScalerMemorySetFIFOFreq(_HW_FIFO_FREQ_LINE_BUFFER_SEL);

            // Set D-domain blocks: SU, fifo & display format
            ScalerMDomainSetDDomain(&stFIFOScaling);

            // Fine Tune DClk Offset
            ScalerDPLLFineTuneFrameSyncLineBuffer();

            // Adjust IVS/IHS for Position Range
            ScalerIDomainVgipAdjustIHVDelay();
            break;

#if(_FRC_SUPPORT == _ON)

        case _FRAME_SYNC_MEMORY:
        case _FREE_RUN_MEMORY:
        case _MN_FRAME_SYNC_MEMORY:

            // Adjust IVS/IHS for Position Range
            ScalerIDomainVgipAdjustIHVDelay();

            // Set D-domain blocks: SU, fifo & display format
            ScalerMDomainSetDDomain(&stFIFOScaling);

            // Initial M Domain Block
            if(ScalerMemoryCheckScreenCoverStatus() == _TRUE)
            {
                ScalerMemoryInitial();

                // Set FIFO freq.
                ScalerMemorySetFIFOFreq(_HW_FIFO_FREQ_FRAME_BUFFER_SEL);
            }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            // Get Rotation status
            if(GET_ROT_TYPE() != _ROT_DISABLE)
            {
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
                if(GET_ROT_TYPE() == _ROT_VER_MIRROR)
                {
                    // Set FRC control
                    ScalerFRCControl(&stFIFOScaling);
                }
                else
#endif
                {
                    // Set Rotation
                    ScalerRotationControl(&stFIFOScaling);
                }
            }
            else
#endif
            {
                // Set FRC control
                ScalerFRCControl(&stFIFOScaling);
            }

#if(_PANEL_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
            if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)
            {
                ScalerDPLLFineTuneFrameSyncFrameBuffer();
            }
#endif

            break;

#endif // End of #if(_FRC_SUPPORT == _ON)

        default:

            // Initial M Domain Block
            ScalerMemoryInitial();

            break;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Enable double buffer
    ScalerMDomainControlDBApply();

#if(_FRC_SUPPORT == _ON)
    if((ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) & _I_DB_ENABLE) != 0x00)
    {
        ScalerFRCWaitIVSAdjust(GET_MEMORY_FRAME_BUFFER(), GET_MDOMAIN_INPUT_DATA_PATH());
    }

    ScalerFRCChannelMuteDTGEnable(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_OUTPUT_RGN(), GET_MODE_DISPLAY_TARGET_REGION(), _ENABLE);
#endif
    // Enable Spread Spectrum
    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _DCLK_SPREAD_RANGE);
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

#if(_OD_FUNCTION == _ON)
    // Check OD use bit
    ScalerMDomainODConfig();
    ScalerODInitial();

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
    ScalerODSetThreeBlockAddress();
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    ScalerRotationSetRotationEnable();
    ScalerRotationReset();
#endif

#if(_FRC_SUPPORT == _ON)
    ScalerFRCSetMemoryBoundary(_FRC_BOUNDARY_NORMAL);
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    ScalerMemoryReset();
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    ScalerMDomainClearStatus(GET_MDOMAIN_INPUT_DATA_PATH());

    // Clear Display Vsync timeout flag
    ScalerGlobalClrDvsTimeoutFlag();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
    SET_MBR_DVTOTAL(GET_MDOMAIN_OUTPUT_VTOTAL());
#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
    ScalerMbrUpdateBlackFrameInsertAvailableMode();
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
    // Before Color Process
    ScalerColorAntiAliasingInitialSetting();
#endif

#if(_DOLBY_CERTIFICATION_SUPPORT == _OFF)
    if((ScalerMDomainMemoryCheck(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) ||
       (ScalerMDomainDisplayTimingGenCheck(GET_MDOMAIN_INPUT_PORT()) == _FALSE))
    {
        DebugMessageScaler("MemoryCheck Fail in Display Setting", GET_MEMORY_CONFIG_SELECT());

        return _FALSE;
    }
#endif

    // If M domain setup success, set I domain DB trigger event to IEN_STOP
    ScalerGlobalIDDomainDBSetTriggerEvent(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_TRIGGER_EVENT_IEN_STOP);

#if(_DT_RANGE_TEST_SUPPORT == _ON)
    if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        ScalerMemoryDtRangeTest(stFIFOScaling.usOutputVHeight);
    }
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    SET_I_DB_APPLY_POINT(_GLOBAL_APPLY_I_MI);
    SET_IDEN_DDEN_RELATION(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()), ScalerMDomainCheckFrameSyncIdenDdenRelation());
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Special Double Buffer Apply Procedure for FS
// Input Value  : None
// Output Value : None
// Note : Only for Frame Sync case
//--------------------------------------------------
void ScalerMDomainControlDBApply(void)
{
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    SET_I_DB_APPLY_POINT(_GLOBAL_APPLY_I_MI);
#endif

    if(ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _DB_DISABLE)
    {
        return;
    }

    if(ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_RGN()) == _FALSE)
    {
        ScalerMDomainIDDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);
    }
    else
    {
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
        if(ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _I_D_DB_ENABLE)
        {
            ScalerGlobalDoubleBufferMdomainForceApplyEnable(_ENABLE);
        }
#endif
        // Apply double buffer
        if((GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER) || (GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY) || (GET_MEMORY_CONFIG_SELECT() == _MN_FRAME_SYNC_MEMORY))
        {
            ScalerMDomainFSVgipDoubleBufferApply();
        }
        else
        {
            ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);
        }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        // Set FC Eagle Sight Capture DB Apply
        ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
        ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()), _DB_APPLY_POLLING);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
        if(ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _I_D_DB_ENABLE)
        {
            ScalerGlobalDoubleBufferMdomainForceApplyEnable(_DISABLE);
        }
#endif
    }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    // Clr FC Eagle Sight Capture DB Apply
    ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_CLR);
#endif
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    SET_I_DB_APPLY_POINT(_GLOBAL_APPLY_I);
#endif
}

//--------------------------------------------------
// Description  : Clear top status
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainClearStatus(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumChkPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if(CHK_FRC_PATH(enumInputDataPath, GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), _BIT4);
            SET_PAGED_BIT(GET_FRC_PAGE_SELECT(ucIndex), _REG_FRC_CAP_FIFO_STATUS, ~(_BIT4), 0x00);
        }

        if((enumInputDataPath & enumChkPath) == enumChkPath)
        {
            BYTE ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);
            BYTE ucOvfUdfOffset = GET_OVF_UDF_OFFSET(ucIndex);

            // Clear HV error Status
            ScalerSetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

            // Clear Buffer Status
            ScalerSetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
    }
}

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
//
// The actual I_DB-applied path will be determined
// by both selected path and display mode.
//
// * In 1P Mode:
//      I_DB apply on M1 & M2, regardless of selected path.
//
// * In PIP, PBP_LR and PBP_TB Mode:
//      I_DB apply on M1 & M2 as long as at least one of them is selected.
//      I_DB apply on S1 & S2 as long as at least one of them is selected.
//
// * In 4P Mode:
//      I_DB apply on each selected path.
//
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerMDomainIDDomainDBApply(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply)
{
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    bit bFtearPrevent = (bit)GET_PAGED_BIT(ScalerFRCDispGetPageSelect(enumSelectedDataPath), P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, _BIT6);
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(enumSelectedDataPath);

    if(enumDBApply == _DB_APPLY_NONE)
    {
        return;
    }

    // Check IMD Doube Buffer Enable
    switch(ScalerGlobalGetDBStatus(enumSelectedDataPath))
    {
        case _IMD_DB_ENABLE:

            if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
            {
                // Clr MI and MD DB flag
                ScalerSetBit(PD7_D1_IMD_DB_STATUS, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Set DB apply
                ScalerSetBit(PD7_D0_I_DB_CTRL, ~_BIT6, _BIT6);

                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, PD7_D1_IMD_DB_STATUS, _BIT7, 1);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
                // Set FC Eagle Sight Capture DB Apply
                ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif

                ScalerIDomainSettingAfterIDB();

                if(enumDBApply == _DB_APPLY_POLLING)
                {
                    ScalerGlobalWaitDDomainDBApplyFinish();
                }
            }
            else
            {
                ScalerGlobalIDomainDBApply(enumSelectedDataPath, enumDBApply);
                ScalerIDomainSettingAfterIDB();
            }
            break;

        case _I_D_DB_ENABLE:
        case _VGIP_DTG_DB_ENABLE:

            for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
                {
                    enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

                    // Disable ftear prevent
                    SET_PAGED_BIT(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, ~_BIT6, 0x00);
                }
            }

            if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
            {
                BYTE ucIDomainPage = ScalerIDomainGetInputPathPage(enumSelectedDataPath);
                BYTE ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(enumSelectedDataPath);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                WORD usESSubivstart = GET_MDOMAIN_INPUT_VSTART() + ScalerVgipGetCaptureVDelay();
#endif
                // Set D-domain DB trigger event,0: DENA Stop (_GLOBAL_DB_GEN_IV)
                ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, 0x00);

                // Clr I and MI Double Buffer Happen Flag
                ScalerGlobalClrIDoubleBufferHappenFlag();

                // Clr MD Double Buffer Happen Flag
                ScalerGlobalClrDDoubleBufferHappenFlag();

                // Check if VGIP is enabled before polling
                if(GET_PAGED_BIT(ucIDomainPage, P0_10_M1_VGIP_CTRL, _BIT0) == 0)
                {
                    return;
                }

                if((GET_IDEN_DDEN_RELATION(ScalerRegionGetIndexFromInputDataPath(enumSelectedDataPath)) & _IDEN_START_LAG_DDEN_STOP) == _IDEN_START_LAG_DDEN_STOP)
                {
                    // Wait Main DDen Start
                    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

                    // I-domain double buffer apply
                    ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
                    // Set FC Eagle Sight Capture DB Apply
                    ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
                }
                else
                {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    // special case for _EAGLE_SIGHT_CAP_TOP_LEFT, _EAGLE_SIGHT_CAP_TOP_RIGHT
                    if((GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB) && (usESSubivstart < (GET_MDOMAIN_INPUT_VTOTAL() / 4)))
                    {
                        // Wait Main IDen Stop
                        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, enumSelectedDataPath);

                        // I-domain double buffer apply
                        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

                        // special case for select cap position from bottom_left to top_right
                        if((GET_MDOMAIN_ES_SUB_VSTART(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH())) > usESSubivstart) &&
                           (GET_MDOMAIN_ES_SUB_VSTART(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH())) - usESSubivstart > (GET_MDOMAIN_INPUT_VTOTAL() / 2)))
                        {
                            // due to the reduction of ivs delay and interrupt, den start may later than the next two ivs, wait ivs to apply fc cap in this case
                            // Wait Main Ivs for FC Eagle Sight Capture DB
                            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumSelectedDataPath);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
                            // Set FC Eagle Sight Capture DB Apply
                            ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
                        }
                        else
                        {
                            // to avoid iden end happen before dden start
                            if((GET_IDEN_DDEN_RELATION(ScalerRegionGetIndexFromInputDataPath(enumSelectedDataPath)) & _IDEN_STOP_LEAD_DDEN_START) == _IDEN_STOP_LEAD_DDEN_START)
                            {
                                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                            }

                            // considering for interrupt case, wait only one event for fc capture (only ivs, not both ivs, dden start)
                            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
                            // Set FC Eagle Sight Capture DB Apply
                            ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
                        }
                    }
                    else
#endif
                    {
                        // Wait Main IDen Start
                        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, enumSelectedDataPath);

                        // I-domain double buffer apply
                        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
                        // Set FC Eagle Sight Capture DB Apply
                        ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
                        // Wait DDen Start
                        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                    }
                }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
                {
                    SET_MDOMAIN_ES_SUB_VSTART(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()), usESSubivstart);
                }

                if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
                {
                    EnumFRCChannelPageSelect enumChannelPage = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(enumSelectedDataPath));
                    // for Eagle sight SUB 2blk
                    if((ScalerFRCGetChannelFRCCapBlkNum(enumChannelPage) == _FRC_CH_2_BLK) &&
                       (ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH()) == _REGION_INDEX_1))
                    {
                        enumPageSelect = ScalerFRCCapGetPageSelect(GET_MDOMAIN_INPUT_DATA_PATH());
                        pData[0] = GET_PAGED_BIT(enumPageSelect, P5_2A_CAP_M1_STATUS, (_BIT7 | _BIT6));
                        pData[1] = GET_PAGED_BIT(enumPageSelect, P5_AD_DISP_M1_STATUS, (_BIT7 | _BIT6));

                        if(pData[0] != pData[1])
                        {
                            // Wait DDen Start
                            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                        }
                    }
                }
#endif
                ScalerIDomainSettingAfterIDB();

                // Set D apply bit
                ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

                if(enumDBApply == _DB_APPLY_POLLING)
                {
                    // Check D domain status before polling
                    if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
                       (GET_DPLL_POWER_STATUS() == _FALSE))
                    {
                        // Clr D apply bit
                        ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, 0x00);

                        return;
                    }

                    // Wait D double buffer
                    if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, (_BIT6), 0) == _FALSE)
                    {
                        // Disable Display format gen when D domain double buffer timeout
                        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT0, 0x00);

                        // Clr D apply bit
                        ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, 0x00);
                    }
                }
            }
            else
            {
                // I-domain double buffer apply
                ScalerGlobalIDomainDBApply(enumSelectedDataPath, enumDBApply);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
                // Set FC Eagle Sight Capture DB Apply
                ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
                ScalerIDomainSettingAfterIDB();

                // Display timing gen double buffer apply
                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
            }

            if(bFtearPrevent == _TRUE)
            {
                for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
                {
                    if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
                    {
                        enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

                        // Disable ftear prevent
                        SET_PAGED_BIT(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, ~_BIT6, _BIT6);
                    }
                }
            }

            break;

        default:
            break;
    }

#elif(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)

    BYTE ucDBctrl = 0;

    // Set D-domain DB trigger event,1: DENA Stop
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Check I/D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }
    }

    ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(enumSelectedDataPath);

    if(enumDBApply == _DB_APPLY_POLLING)
    {
#if(_FRC_SUPPORT == _ON)
        if(ScalerGlobalIDDomainDBApplyFRCModeCheck(enumSelectedDataPath) == _TRUE)
        {
            ScalerMDomainIDDomainDBApplyFRCModeSetDB(enumSelectedDataPath);
        }
        else
#endif
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

            // Set I apply bit
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
            // Set FC Eagle Sight Capture DB Apply
            ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif
            ScalerIDomainSettingAfterIDB();

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

#if(_FRC_SUPPORT == _ON)
            if(GET_FRC_CAP_EN_RESET() == _TRUE)
            {
                // Wait I double buffer
                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucDBctrl, 0);

                // Reset FRC Cap enable
                ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
                ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
            }
#endif

            // Wait D double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);
        }
    }
    else if(enumDBApply == _DB_APPLY_NO_POLLING)
    {
        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        // Set FC Eagle Sight Capture DB Apply
        ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif

        ScalerIDomainSettingAfterIDB();

        // Set D apply bit
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));
    }

#endif
}

//--------------------------------------------------
// Description  : Get Accuracy IVF
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
void ScalerMDomainUpdateInputInfo(void)
{
    DWORD ulIPixelCnt = 0;
    DWORD ulIVF = 0;
    DWORD ulIHF = 0;

    // I active region pixel count
    ulIPixelCnt = ScalerMeasureGetAdjustedActiveRegionCount(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_VHEIGHT());

    ulIHF = GET_DWORD_MUL_DIV(_MEASURE_CLK, ((DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * 100), ulIPixelCnt);

    ulIHF = (ulIHF + 5) / 10;

    SET_MDOMAIN_INPUT_HFREQ(ulIHF);

    DebugMessageScaler("Accuracy IHF", ulIHF);

    // Adjust IVF
    if(GET_MDOMAIN_INPUT_INTERLACE_FLG() == _FALSE)
    {
#if(_DRR_SUPPORT == _ON)
        if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) == _DRR_NONE_TYPE)
#endif
        {
#if(_HDMI21_FVA_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmi21VtemReceived(GET_MDOMAIN_INPUT_PORT()) == _TRUE)
            {
                // case of FVA only
                return;
            }
#endif

            // I whole frame pixel count
            ulIPixelCnt = GET_DWORD_MUL_DIV(ulIPixelCnt, GET_MDOMAIN_INPUT_VTOTAL(), GET_MDOMAIN_INPUT_VHEIGHT());

            // IVF = measure_clk / measure_count, unit: 0.01Hz
            ulIVF = GET_DWORD_MUL_DIV(_MEASURE_CLK, 100000, ulIPixelCnt);

            // IVF round to 0.1Hz
            ulIVF = (ulIVF + 5) / 10;

            SET_MDOMAIN_INPUT_VFREQ(ulIVF);

            DebugMessageScaler("Accuracy IVF", ulIVF);
        }
    }

    if((GET_MDOMAIN_INPUT_VHEIGHT_ODD() == _TRUE) &&
       (ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) >= _INPUT_PATH_2))
    {
        SET_MDOMAIN_INPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() - 2);
    }
}

//--------------------------------------------------
// Description  : Get Mdomain display path count
// Input Value  : EnumMDomainDisplayDataPath enumMDispPath
// Output Value : Path count
//--------------------------------------------------
BYTE ScalerMDomainGetInputPathCount(EnumInputDataPath enumInputDataPath)
{
    BYTE ucPathCnt = 0;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ucIndex++)
    {
        if((enumInputDataPath & GET_FRC_INPUT_DATA_PATH(ucIndex)) == GET_FRC_INPUT_DATA_PATH(ucIndex))
        {
            ucPathCnt += 1;
        }
    }
    return ucPathCnt;
}

//--------------------------------------------------
// Description  : Check DVtotal Fine tune
// Input Value  : EnumMemoryConfig enumMemoryConfig
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
bit ScalerMDomainCheckDVtotalFinetune(EnumMemoryConfig enumMemoryConfig)
{
    if(enumMemoryConfig == _FRAME_SYNC_MEMORY)
    {
#if(_PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON)
        // DRR Frame sync DVtotal Consider IVF max +0.5%
        if((ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE) &&
           (((DWORD)GET_MDOMAIN_INPUT_VFREQ() * 1005 / 1000) >= GET_DRR_PANEL_MAX_FRAME_RATE()))
        {
            DebugMessageScaler("[WARNING] Not Do DRR DVtotal Finetune when _PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN is _ON", 0);
            return _FALSE;
        }
#endif

#if(_PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON)
        DebugMessageScaler("[WARNING] Not Do DVtotal Finetune when _PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN is _ON", 0);
        return _FALSE;
#endif
    }

    return _TRUE;
}

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
//--------------------------------------------------
// Description  : Check Frame sync mode Iden and Dden relation
// Input Value  : None
// Output Value : EnumMdomainIdenDdenRelation
//--------------------------------------------------
EnumMDomainIdenDdenRelation ScalerMDomainCheckFrameSyncIdenDdenRelation(void)
{
    EnumMDomainIdenDdenRelation enumMDomainIdenDdenRelation = _IDEN_DDEN_RELATION_CHANGE;

    WORD usIVS2DVSdelay = (ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) / GET_MDOMAIN_INPUT_HTOTAL()) + 1;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON)
    usIVS2DVSdelay = MAXOF(GET_MDOMAIN_IVS2DVSDELAY(_REGION_INDEX_0), GET_MDOMAIN_IVS2DVSDELAY(_REGION_INDEX_1));
#else
    usIVS2DVSdelay = (ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainFSActiveInfo.stMDomainFSActiveInputData) / GET_MDOMAIN_INPUT_HTOTAL()) + 1;
#endif
#endif

    if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
    {
        // IVS2DVS, unit: I domain line, round up
        WORD usIVS2DVSdelay_cmp = usIVS2DVSdelay;

        // DVst + DVheight, unit: D domain line
        WORD usDVBGEnd = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT) + ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);

        // IHFreq, unit: 0.01kHz
        DWORD ulIHFreq = ScalerMeasureGetHFreq(GET_MDOMAIN_INPUT_DATA_PATH());

        // DHFreq, unit: 0.01kHz
        DWORD ulDHFreq = GET_DWORD_MUL_DIV(GET_D_CLK_FREQ(), 100, GET_MDOMAIN_OUTPUT_HTOTAL());

        WORD usIPeriod = GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT();
        WORD usDPeriod = GET_DWORD_MUL_DIV(ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START), ulIHFreq, ulDHFreq);

        // DVst + DVheight, unit: I domain line, round up
        usDVBGEnd = GET_DWORD_MUL_DIV(usDVBGEnd, ulIHFreq, ulDHFreq) + 1;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
        {
            usIVS2DVSdelay_cmp += GET_DWORD_MUL_DIV(GET_MDOMAIN_OUTPUT_VTOTAL(), ulIHFreq, ulDHFreq) + 1;

            // analog capture
            if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
            {
                if(usIVS2DVSdelay_cmp > ScalerVgipGetCaptureVDelay())
                {
                    usIVS2DVSdelay_cmp -= ScalerVgipGetCaptureVDelay();
                }
            }
        }
#endif

        if((GET_MDOMAIN_INPUT_VTOTAL() + GET_MDOMAIN_INPUT_VSTART()) > (usIVS2DVSdelay_cmp + usDVBGEnd))
        {
            DebugMessageScaler("I den start later than D den stop", 0);
            enumMDomainIdenDdenRelation |= _IDEN_START_LAG_DDEN_STOP;
        }
        else
        {
            DebugMessageScaler("I den start earlier than D den stop", 0);
            enumMDomainIdenDdenRelation |= _IDEN_START_LEAD_DDEN_STOP;
        }

        usIVS2DVSdelay_cmp = usIVS2DVSdelay;

        if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
        {
            usIPeriod += ScalerVgipGetCaptureVDelay();
        }

        // check if Iden end lead Dden start
        if(usIPeriod < usIVS2DVSdelay_cmp + usDPeriod)
        {
            DebugMessageScaler("I den stop earlier than D den start", 0);
            enumMDomainIdenDdenRelation |= _IDEN_STOP_LEAD_DDEN_START;
        }
        else
        {
            DebugMessageScaler("I den stop later than D den start", 0);
            enumMDomainIdenDdenRelation |= _IDEN_STOP_LAG_DDEN_START;
        }
    }

    return enumMDomainIdenDdenRelation;
}

#endif

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Compare Reference Timing with Edid Timing List
// Input Value  : pucReadArray: EDID address, usPixelClk: Input pixel clk(0.1M), pstSourceInfo, pstCatchEdidInfo
// Output Value : _TRUE: Get Timing Match
//--------------------------------------------------
EnumGetIVFFromTableSearch ScalerMDomainEdidTimingInfoComparison(BYTE *pucReadArray, const StructTableSearchingSourceInfo *pstSourceInfo, StructEdidInfo *pstCatchEdidInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo)
{
    EnumGetIVFFromTableSearch enumDrrGetIVFFromEdid = _TABLE_SEARCHING_WITHOUT_IVF_MAX;

    // === Misc ===
    DWORD ulCandidatedPixelRate = 0; // 0.1 MHz
    DWORD ulEstablishTiming = 0;

    WORD pusCtaDataBlockAddr[_CTA_TOTAL_DB] = {0};
    WORD pusDidDataBlockAddr[_DID_TOTAL_DB] = {0};

    WORD usStartAddr = 0;
    WORD usIndex = 0;
    BYTE ucCnt = 0;

    // === Edid Info ===
    StructEdidInfo stEdidInfo = {0};
    StructEdidRefInfo stEdidRefInfo = {0};

    ScalerMDomainEdidAnalysisGetRefInfo(&stEdidRefInfo, pstSourceInfo, enumInputPort, pstTimingInfo);

    // Get DB start addr from Edid Data
    ScalerSyncGetCtaExtDbAddress(pusCtaDataBlockAddr, pucReadArray);
    ScalerSyncGetDidExtDbAddress(pusDidDataBlockAddr, pucReadArray);

    // -----------------------------------------------------------
    // EDID: DTD Capture
    // -----------------------------------------------------------
    // Base DTD
    for(ucCnt = 0; ucCnt < 4; ucCnt++)
    {
        // Set Start addr to DTD start location
        usStartAddr = (0x36 + (ucCnt * 18));

        // Check DTD or not
        if((pucReadArray[usStartAddr] != 0x00) && (pucReadArray[usStartAddr + 1] != 0x00))
        {
            // Catch DTD's Hblank/ Hactive/ Vactive
            stEdidInfo.usHwidth = (((WORD)(pucReadArray[usStartAddr + 4] & 0xF0) << 4) | pucReadArray[usStartAddr + 2]);
            stEdidInfo.usHblank = (((WORD)(pucReadArray[usStartAddr + 4] & 0x0F) << 8) | pucReadArray[usStartAddr + 3]);
            stEdidInfo.usVheight = (((WORD)(pucReadArray[usStartAddr + 7] & 0xF0) << 4) | pucReadArray[usStartAddr + 5]);
            stEdidInfo.usPixelClk = ((((DWORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) / 10); // 0.1 MHz
            stEdidInfo.b1Interlace = ((pucReadArray[usStartAddr + 17] & _BIT7) >> 7);

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    stEdidInfo.usVtotal = stEdidInfo.usVheight + (((WORD)(pucReadArray[usStartAddr + 7] & 0x0F) << 8) | pucReadArray[usStartAddr + 6]);
                    stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                    memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(stEdidInfo));

                    DebugMessageScaler("Get Candidated Vfreq from EDID Base DTD", 0);
                }
            }
        }
    }

    // Extension DTD
    if(pucReadArray[0x7E] != 0x00)
    {
        for(usIndex = 0; usIndex < pucReadArray[0x7E]; usIndex++)
        {
            // Stop Extension Analysis if Not CEA Type, Check tag = 0x02
            if(pucReadArray[(usIndex + 1) * 0x80] == 0x02)
            {
                // Set Start addr to DTD start location
                usStartAddr = (0x80 * (usIndex + 1)) + pucReadArray[(0x80 * (usIndex + 1)) + 0x02];

                for(ucCnt = 0; ucCnt < 6; ucCnt++)
                {
                    if(usStartAddr > ((0x80 * (usIndex + 1)) + 0x7E))
                    {
                        break;
                    }

                    // Check DTD or not
                    if((pucReadArray[usStartAddr] != 0x00) && (pucReadArray[usStartAddr + 1] != 0x00))
                    {
                        // Catch DTD's Hblank/ Hactive/ Vactive
                        stEdidInfo.usHwidth = (((WORD)(pucReadArray[usStartAddr + 4] & 0xF0) << 4) | pucReadArray[usStartAddr + 2]);
                        stEdidInfo.usHblank = (((WORD)(pucReadArray[usStartAddr + 4] & 0x0F) << 8) | pucReadArray[usStartAddr + 3]);
                        stEdidInfo.usVheight = (((WORD)(pucReadArray[usStartAddr + 7] & 0xF0) << 4) | pucReadArray[usStartAddr + 5]);
                        stEdidInfo.usPixelClk = ((((WORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) / 10); // 0.1 MHz
                        stEdidInfo.b1Interlace = ((pucReadArray[usStartAddr + 17] & _BIT7) >> 7);

                        // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
                        if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
                        {
                            // Check & take the large Pixel
                            if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                            {
                                stEdidInfo.usVtotal = stEdidInfo.usVheight + (((WORD)(pucReadArray[usStartAddr + 7] & 0x0F) << 8) | pucReadArray[usStartAddr + 6]);
                                stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                                ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                                memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(stEdidInfo));

                                DebugMessageScaler("Get Candidated Vfreq from EDID EXT DTD", 0);
                            }
                        }
                    }

                    usStartAddr += 0x12;
                }
            }
        } // End of Extension Block Analysis For Loop
    }

    // -----------------------------------------------------------
    // EDID: DB Capature
    // -----------------------------------------------------------
    // VDB
    if(pusCtaDataBlockAddr[_CTA_VDB] != 0x00)
    {
        BYTE ucVicIndex = 0;
        BYTE ucDblength = 0;

        // Set Start addr to VDB start location
        usStartAddr = pusCtaDataBlockAddr[_CTA_VDB];
        ucDblength = (pucReadArray[usStartAddr] & 0x1F);

        for(usIndex = 0; usIndex < ucDblength; usIndex++)
        {
            ucVicIndex = pucReadArray[usStartAddr + 1 + usIndex];

            if(ucVicIndex == 0)
            {
                DebugMessageScaler("VIC = 0 of VDB!!", usStartAddr + 1 + usIndex);
                continue;
            }

            // depart native / non-native factor & fit index to Code table below
            if(((1 <= ucVicIndex) && (ucVicIndex <= 64)) ||
               ((129 <= ucVicIndex) && (ucVicIndex <= 192)))
            {
                ucVicIndex = (ucVicIndex & 0x7F) - 1;
            }
            else
            {
                ucVicIndex -= 1;
            }

            stEdidInfo.usHwidth = tVIC_HACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usHblank = tVIC_HBLANK_TABLE[ucVicIndex];
            stEdidInfo.usVheight = tVIC_VACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usPixelClk = tVIC_PIXEL_RATE_TABLE[ucVicIndex]; // 0.1 MHz
            stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;
            stEdidInfo.usVtotal = ((GET_DWORD_MUL_DIV(stEdidInfo.usPixelClk, 100000, stEdidInfo.usHtotal) + (tVIC_VFREQ_TABLE[ucVicIndex] / 2)) / tVIC_VFREQ_TABLE[ucVicIndex]);
            stEdidInfo.b1Interlace = _FALSE;

            for(pData[0] = 0; pData[0] < 21; pData[0]++)
            {
                if(tInterlaceVic[pData[0]] == (ucVicIndex + 1))
                {
                    stEdidInfo.b1Interlace = _TRUE;

                    // VIC Info's V info is frame V info (not field V info)
                    stEdidInfo.usVheight = stEdidInfo.usVheight / 2;
                    break;
                }
            }

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                    memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(stEdidInfo));

                    DebugMessageScaler("Get Candidated Vfreq from EDID VDB", 0);
                }
            }
        }
    }

    // 420 VDB
    if((pusCtaDataBlockAddr[_CTA_420VDB] != 0x00) && (pstSourceInfo->ucColorSapce == _COLOR_SPACE_YCBCR420))
    {
        BYTE ucVicIndex = 0;
        BYTE ucDblength = 0;

        // Set Start addr to 420VDB start location
        usStartAddr = pusCtaDataBlockAddr[_CTA_420VDB];
        ucDblength = (pucReadArray[usStartAddr] & 0x1F);

        for(usIndex = 0; usIndex < ucDblength; usIndex++)
        {
            ucVicIndex = pucReadArray[usStartAddr + 2 + usIndex];

            if(ucVicIndex == 0)
            {
                DebugMessageScaler("VIC = 0 of VDB!!", usStartAddr + 2 + usIndex);
                continue;
            }

            // depart native / non-native factor & fit index to Code table below
            if(((1 <= ucVicIndex) && (ucVicIndex <= 64)) ||
               ((129 <= ucVicIndex) && (ucVicIndex <= 192)))
            {
                ucVicIndex = (ucVicIndex & 0x7F) - 1;
            }
            else
            {
                ucVicIndex -= 1;
            }

            stEdidInfo.usHwidth = tVIC_HACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usHblank = tVIC_HBLANK_TABLE[ucVicIndex];
            stEdidInfo.usVheight = tVIC_VACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usPixelClk = tVIC_PIXEL_RATE_TABLE[ucVicIndex]; // 0.1 MHz
            stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;
            stEdidInfo.usVtotal = ((GET_DWORD_MUL_DIV(stEdidInfo.usPixelClk, 100000, stEdidInfo.usHtotal) + (tVIC_VFREQ_TABLE[ucVicIndex] / 2)) / tVIC_VFREQ_TABLE[ucVicIndex]);
            stEdidInfo.b1Interlace = _FALSE;

            for(pData[0] = 0; pData[0] < 21; pData[0]++)
            {
                if(tInterlaceVic[pData[0]] == (ucVicIndex + 1))
                {
                    stEdidInfo.b1Interlace = _TRUE;

                    // VIC Info's V info is frame V info (not field V info)
                    stEdidInfo.usVheight = stEdidInfo.usVheight / 2;
                    break;
                }
            }

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                    memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(stEdidInfo));

                    DebugMessageScaler("Get Candidated Vfreq from EDID 420VDB", 0);
                }
            }
        }
    }

    // -----------------------------------------------------------
    // DID: Timing I DB
    // -----------------------------------------------------------
    if(pusDidDataBlockAddr[_DID_T1_DB] != 0x00)
    {
        BYTE ucTimingNum = (pucReadArray[pusDidDataBlockAddr[_DID_T1_DB] + 2] / 20);

        // Catch each Timing from Timing1 DB
        for(usIndex = 0; usIndex < ucTimingNum; usIndex++)
        {
            // Set start addr to Timing 1 's Descriptor unit
            usStartAddr = (pusDidDataBlockAddr[_DID_T1_DB] + 3 + (20 * usIndex));

            // Catch Timing1's Hblank/ Hactive/ Vactive  (Timing 1's range is 1~xxx)
            stEdidInfo.usHwidth = (((WORD)pucReadArray[usStartAddr + 5] << 8) | pucReadArray[usStartAddr + 4]) + 1;
            stEdidInfo.usHblank = (((WORD)pucReadArray[usStartAddr + 7] << 8) | pucReadArray[usStartAddr + 6]) + 1;
            stEdidInfo.usVheight = (((WORD)pucReadArray[usStartAddr + 13] << 8) | pucReadArray[usStartAddr + 12]) + 1;
            stEdidInfo.usPixelClk = (((((DWORD)pucReadArray[usStartAddr + 2] << 16) | ((DWORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) + 1) / 10); // 0.1 MHz
            stEdidInfo.usVtotal = stEdidInfo.usVheight + ((((WORD)pucReadArray[usStartAddr + 15] << 8) | pucReadArray[usStartAddr + 14]) + 1);
            stEdidInfo.b1Interlace = ((pucReadArray[usStartAddr + 3] & _BIT4) >> 4);

            if(stEdidInfo.b1Interlace == _TRUE)
            {
                // VIC Info's V info is frame V info (not field V info)
                stEdidInfo.usVheight = stEdidInfo.usVheight / 2;
            }

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                    if(stEdidInfo.b1Interlace == _TRUE)
                    {
                        stEdidInfo.usVtotal = (stEdidInfo.usVtotal / 2);
                    }

                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                    memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(StructEdidInfo));

                    DebugMessageScaler("Get Candidated Vfreq from DID T1", 0);
                }
            }
        }
    }

    // -----------------------------------------------------------
    // DID: Timing 7 DB
    // -----------------------------------------------------------
    if(pusDidDataBlockAddr[_DID_T7_DB] != 0x00)
    {
        BYTE ucEachTimingSize = 20 + ((pucReadArray[pusDidDataBlockAddr[_DID_T7_DB] + 1] & (_BIT6 | _BIT5 | _BIT4)) >> 4);
        BYTE ucTimingNum = (pucReadArray[pusDidDataBlockAddr[_DID_T7_DB] + 2] / ucEachTimingSize);

        // Catch each Timing from Timing1 DB
        for(usIndex = 0; usIndex < ucTimingNum; usIndex++)
        {
            // Set start addr to Timing 1 's Descriptor unit
            usStartAddr = (pusDidDataBlockAddr[_DID_T7_DB] + 3 + (ucEachTimingSize * usIndex));

            // Catch Timing1's Hblank/ Hactive/ Vactive  (Timing 1's range is 1~xxx)
            stEdidInfo.usHwidth = (((WORD)pucReadArray[usStartAddr + 5] << 8) | pucReadArray[usStartAddr + 4]) + 1;
            stEdidInfo.usHblank = (((WORD)pucReadArray[usStartAddr + 7] << 8) | pucReadArray[usStartAddr + 6]) + 1;
            stEdidInfo.usVheight = (((WORD)pucReadArray[usStartAddr + 13] << 8) | pucReadArray[usStartAddr + 12]) + 1;
            stEdidInfo.usPixelClk = (((((DWORD)pucReadArray[usStartAddr + 2] << 16) | ((DWORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) + 1) / 100); // 0.1 MHz
            stEdidInfo.usVtotal = stEdidInfo.usVheight + ((((WORD)pucReadArray[usStartAddr + 15] << 8) | pucReadArray[usStartAddr + 14]) + 1);
            stEdidInfo.b1Interlace = ((pucReadArray[usStartAddr + 3] & _BIT4) >> 4);

            if(stEdidInfo.b1Interlace == _TRUE)
            {
                // VIC Info's V info is frame V info (not field V info)
                stEdidInfo.usVheight = stEdidInfo.usVheight / 2;
            }

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                    if(stEdidInfo.b1Interlace == _TRUE)
                    {
                        stEdidInfo.usVtotal = (stEdidInfo.usVtotal / 2);
                    }

                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                    memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(StructEdidInfo));

                    DebugMessageScaler("Get Candidated Vfreq from DID T7", 0);
                }
            }
        }
    }

    // -----------------------------------------------------------
    // EDID Base Established Timing
    // -----------------------------------------------------------
    // 0x23[7:0] | 0x24[7:0] | 0x25[7]
    ulEstablishTiming = ((((DWORD)pucReadArray[0x23] << 16) | ((DWORD)pucReadArray[0x24] << 8) | (pucReadArray[0x25])) >> 7);

    for(usIndex = 0; usIndex < 17; usIndex++)
    {
        /*
        // Skip !VESA DMP Timing
        if((usIndex == 0) || (usIndex == 1) || (usIndex == 2) || (usIndex == 3) ||
          (usIndex == 10) || (usIndex == 11) || (usIndex == 16))
        {
            continue;
        }
        */

        if(((ulEstablishTiming >> usIndex) & 0x0001) == 1)
        {
            BYTE ucTuneIndex = 16 - usIndex; // ie. index order meet with tEST_TIMING TABLE

            // Establish timing support -> check
            stEdidInfo.usHwidth = tEST_TIMING_HACTIVE_TABLE[ucTuneIndex];
            stEdidInfo.usHblank = tEST_TIMING_HBLANK_TABLE[ucTuneIndex];
            stEdidInfo.usVheight = tEST_TIMING_VACTIVE_TABLE[ucTuneIndex];
            stEdidInfo.usPixelClk = tEST_TIMING_PCLK_TABLE[ucTuneIndex]; // 0.1 MHz
            stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;
            stEdidInfo.usVtotal = stEdidInfo.usVheight + tEST_TIMING_VBLANK_TABLE[ucTuneIndex];

            if(ucTuneIndex == 11)
            {
                stEdidInfo.b1Interlace = _TRUE;
                stEdidInfo.usVheight = stEdidInfo.usVheight / 2;
                stEdidInfo.usVtotal = stEdidInfo.usVtotal / 2;
            }
            else
            {
                stEdidInfo.b1Interlace = _FALSE;
            }

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerMDomainEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;

                    memcpy(pstCatchEdidInfo, &stEdidInfo, sizeof(stEdidInfo));

                    DebugMessageScaler("Get Candidated Vfreq from Establish Timing Area!", 0);
                }
            }
        }
    }

    if(ulCandidatedPixelRate != 0x00)
    {
        enumDrrGetIVFFromEdid = _TABLE_SEARCHING_WITH_IVF_MAX;
    }

    return enumDrrGetIVFFromEdid;
}

//--------------------------------------------------
// Description  : Get Freesync Htotal Margin
// Input Value  : enumInputPort --> Source Search Port
// Output Value : Htotal Margin & Htotal
//--------------------------------------------------
void ScalerMDomainGetSourceInfoForTableSearch(EnumInputPort enumInputPort, StructTableSearchingSourceInfo *pstSourceInfo, StructTimingInfo *pstTimingInfo)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch(enumInputPort);
#endif

    pstSourceInfo->ucColorSapce = GET_COLOR_SPACE(enumInputPort);

    pstSourceInfo->usNativePixelClk = ScalerSyncGetNativeInputPixelClk(enumInputPort);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(enumDpMacSel != _DP_MAC_NONE)
    {
        switch(enumDpMacSel)
        {
#if(_DP_MAC_RX0_SUPPORT == _ON)
            case _DP_MAC_0:
                pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX0_HTOTAL();
                pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX0_HTOTAL_MARGIN();
                break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
            case _DP_MAC_1:

                pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX1_HTOTAL();
                pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN();
                break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
            case _DP_MAC_2:

                pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX2_HTOTAL();
                pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX2_HTOTAL_MARGIN();
                break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
            case _DP_MAC_DUAL:

                enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
                switch(enumDualDpMacSel)
                {
                    case _DP_MAC_0:

                        pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX0_HTOTAL();
                        pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX0_HTOTAL_MARGIN();
                        break;

                    case _DP_MAC_1:

                        pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX1_HTOTAL();
                        pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN();

                        break;

                    case _DP_MAC_DUAL:

                        pstSourceInfo->usHtotal = (GET_DP_MAC_STREAM_RX0_HTOTAL() + GET_DP_MAC_STREAM_RX1_HTOTAL());

                        PDATA_WORD(0) = GET_DP_MAC_STREAM_RX0_HTOTAL_MARGIN() * 2;
                        PDATA_WORD(1) = GET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN() * 2;

                        if(PDATA_WORD(0) > PDATA_WORD(1))
                        {
                            pstSourceInfo->usHtotalMargin = PDATA_WORD(0);
                        }
                        else
                        {
                            pstSourceInfo->usHtotalMargin = PDATA_WORD(1);
                        }

                        break;

                    default:
                        pstSourceInfo->usHtotal = GET_MDOMAIN_INPUT_HTOTAL();
                        pstSourceInfo->usHtotalMargin = ((DWORD)GET_MDOMAIN_INPUT_HTOTAL() * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                        break;
                }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
                switch(enumDualDpMacSel)
                {
                    case _DP_MAC_1:

                        pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX1_HTOTAL();
                        pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN();
                        break;

                    case _DP_MAC_2:

                        pstSourceInfo->usHtotal = GET_DP_MAC_STREAM_RX2_HTOTAL();
                        pstSourceInfo->usHtotalMargin = GET_DP_MAC_STREAM_RX2_HTOTAL_MARGIN();

                        break;

                    case _DP_MAC_DUAL:

                        pstSourceInfo->usHtotal = (GET_DP_MAC_STREAM_RX1_HTOTAL() + GET_DP_MAC_STREAM_RX2_HTOTAL());

                        PDATA_WORD(0) = GET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN() * 2;
                        PDATA_WORD(1) = GET_DP_MAC_STREAM_RX2_HTOTAL_MARGIN() * 2;

                        if(PDATA_WORD(0) > PDATA_WORD(1))
                        {
                            pstSourceInfo->usHtotalMargin = PDATA_WORD(0);
                        }
                        else
                        {
                            pstSourceInfo->usHtotalMargin = PDATA_WORD(1);
                        }

                        break;

                    default:
                        pstSourceInfo->usHtotal = pstTimingInfo->usHTotal;
                        pstSourceInfo->usHtotalMargin = ((DWORD)pstTimingInfo->usHTotal * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                        break;
                }
#endif
                break;
#endif

            default:
                pstSourceInfo->usHtotal = pstTimingInfo->usHTotal;
                pstSourceInfo->usHtotalMargin = ((DWORD)pstTimingInfo->usHTotal * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                break;
        }
    }
    else
#endif
    {
#if(_HDMI_SUPPORT == _ON)
        if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_TMDS_MAC)
        {
            pstSourceInfo->usHtotal = pstTimingInfo->usHTotal;
            pstSourceInfo->usHtotalMargin = ((DWORD)pstTimingInfo->usHTotal * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
        }
        else
        {
            switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
            {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                case _RX3:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_DSC_MAC)
                    {
                        pstSourceInfo->usHtotal = ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3)) + GET_HDMI_FRL_MAC_RX3_CVTEM_HFRONT() + GET_HDMI_FRL_MAC_RX3_CVTEM_HSYNC() + GET_HDMI_FRL_MAC_RX3_CVTEM_HBACK();
                        pstSourceInfo->usHtotalMargin = (((DWORD)ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3)) + GET_HDMI_FRL_MAC_RX3_CVTEM_HFRONT() + GET_HDMI_FRL_MAC_RX3_CVTEM_HSYNC() + GET_HDMI_FRL_MAC_RX3_CVTEM_HBACK()) * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                    }
                    else
#endif
                    {
                        pstSourceInfo->usHtotal = GET_HDMI_FRL_MAC_RX3_NATIVE_HTOTAL();
                        pstSourceInfo->usHtotalMargin = ((DWORD)GET_HDMI_FRL_MAC_RX3_NATIVE_HTOTAL() * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                    }
                    break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                case _RX4:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_DSC_MAC)
                    {
                        pstSourceInfo->usHtotal = ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4)) + GET_HDMI_FRL_MAC_RX4_CVTEM_HFRONT() + GET_HDMI_FRL_MAC_RX4_CVTEM_HSYNC() + GET_HDMI_FRL_MAC_RX4_CVTEM_HBACK();
                        pstSourceInfo->usHtotalMargin = (((DWORD)ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4)) + GET_HDMI_FRL_MAC_RX4_CVTEM_HFRONT() + GET_HDMI_FRL_MAC_RX4_CVTEM_HSYNC() + GET_HDMI_FRL_MAC_RX4_CVTEM_HBACK()) * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                    }
                    else
#endif
                    {
                        pstSourceInfo->usHtotal = GET_HDMI_FRL_MAC_RX4_NATIVE_HTOTAL();
                        pstSourceInfo->usHtotalMargin = ((DWORD)GET_HDMI_FRL_MAC_RX4_NATIVE_HTOTAL() * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
                    }
                    break;
#endif

                default:
                    break;
            }
        }
#endif // End of #if(_HDMI_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : EDID Analysis Get Ref Timing Info
// Input Value  : usPixelClk/ pstHtotalInfo(Htotal & Htotal margin)
// Output Value : pstEdidRefInfo
//--------------------------------------------------
void ScalerMDomainEdidAnalysisGetRefInfo(StructEdidRefInfo *pstEdidRefInfo, const StructTableSearchingSourceInfo *pstSourceInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo)
{
    WORD usClkMargin = ((DWORD)pstSourceInfo->usNativePixelClk * _EDID_ANALYSIS_CLK_MARGIN / 100);  // 0.1MHz
    enumInputPort = enumInputPort;

#if(_HDMI_FRL_SUPPORT == _ON)
    // if Input Timing is FRL w/o DSC, change Pclk margain
    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_MAC)
    {
        usClkMargin = MAXOF(50, ((DWORD)pstSourceInfo->usNativePixelClk * 5 / 100));
    }
#endif

    pstEdidRefInfo->b1RefInterlace = pstTimingInfo->b1Interlace;
    pstEdidRefInfo->usRefHwidth = pstTimingInfo->usHWidth;
    pstEdidRefInfo->usRefVheight = pstTimingInfo->usVHeight;

    pstEdidRefInfo->usRefHblankHBound = (pstSourceInfo->usHtotal - pstTimingInfo->usHWidth + pstSourceInfo->usHtotalMargin);
    pstEdidRefInfo->usRefHblankLBound = (pstSourceInfo->usHtotal - pstTimingInfo->usHWidth - pstSourceInfo->usHtotalMargin);
    pstEdidRefInfo->usPixelClkHBound = (pstSourceInfo->usNativePixelClk + usClkMargin);
    pstEdidRefInfo->usPixelClkLBound = (pstSourceInfo->usNativePixelClk - usClkMargin);
}

//--------------------------------------------------
// Description  : EDID Analysis Check Hwidth/ Vheight/ Hblanking/ Pixel
// Input Value  : Hwidth/ Vheight/ Hblanking/ Pixel
// Output Value : _TRUE: Find
//--------------------------------------------------
bit ScalerMDomainEdidAnalysisCheckBoundry(const StructEdidInfo *pstEdidInfo, const StructEdidRefInfo *pstEdidRefInfo)
{
    WORD usModifyVheight = pstEdidRefInfo->usRefVheight;

    // 3DDI: ex, 1080i->1080p, check 3DDI enable or not
#if(_COLOR_IP_3DDI == _ON)
    if(GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON)
    {
        usModifyVheight /= 2;
    }
#endif

    // Check Interlace Timing/ Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
    if((pstEdidInfo->b1Interlace == pstEdidRefInfo->b1RefInterlace) &&
       (pstEdidInfo->usHwidth == pstEdidRefInfo->usRefHwidth) &&
       (pstEdidInfo->usVheight == usModifyVheight) &&
       ((pstEdidInfo->usHblank <= pstEdidRefInfo->usRefHblankHBound) && (pstEdidInfo->usHblank >= pstEdidRefInfo->usRefHblankLBound)) &&
       ((pstEdidInfo->usPixelClk <= pstEdidRefInfo->usPixelClkHBound) && (pstEdidInfo->usPixelClk >= pstEdidRefInfo->usPixelClkLBound)))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Drr mode Get IVFmax Calculated by CVT
// Input Value  : enumInputPort
// Output Value : _TABLE_SEARCHING_WITH_IVF_MAX: Calculate IVF by CVT, unit: 0.1Hz
//--------------------------------------------------
EnumGetIVFFromTableSearch ScalerMDomainCalculateIVFmaxFromCVT(WORD *pusVfreqMax, const StructTableSearchingSourceInfo *pstSourceInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo)
{
    enumInputPort = enumInputPort;
    pstSourceInfo = pstSourceInfo;
    pstTimingInfo = pstTimingInfo;

#if(_HDMI21_VRR_SUPPORT == _ON)
    if(ScalerDrrGetType(enumInputPort) == _DRR_HDMI21_VRR_TYPE)
    {
        // Htotal of CVT timing
        WORD usHtotalRB1 = (pstTimingInfo->usHWidth + 80);
        WORD usHtotalRB2 = (pstTimingInfo->usHWidth + 160);

        // Htotal margin
        WORD usRefHtotalHBound = (pstSourceInfo->usHtotal + pstSourceInfo->usHtotalMargin);
        WORD usRefHtotalLBound = (pstSourceInfo->usHtotal - pstSourceInfo->usHtotalMargin);

        switch(ScalerSyncGetPortType(enumInputPort))
        {
            case _PORT_HDMI:
            case _PORT_HDMI20:
                // Check if it is CVT timing from Htotal
                if(((usHtotalRB1 <= usRefHtotalHBound) && (usHtotalRB1 >= usRefHtotalLBound)) ||
                   ((usHtotalRB2 <= usRefHtotalHBound) && (usHtotalRB2 >= usRefHtotalLBound)))
                {
                    WORD usPixelClk = pstSourceInfo->usNativePixelClk;

                    // Calculate IVF (0.1Hz)
                    DWORD ulVtotalCalByPixel = ((DWORD)pstSourceInfo->usHtotal * pstTimingInfo->usVHeight) + ((DWORD)usPixelClk * _GET_CVT_MIN_VBLANK_PERIOD / 10);
                    WORD usVfreqMax = ((GET_DWORD_MUL_DIV(usPixelClk, 10000000, ulVtotalCalByPixel) + 5) / 10);

                    // Double Check IVF
                    WORD usIVfreqApproximate = ((DWORD)pstTimingInfo->usHFreq * 1000 / pstTimingInfo->usVHeight);

                    // Check usVfreqMax is under spec, Whether IVFmax is reasonable, Check 30% difference
                    if(((usVfreqMax >= GET_DRR_PANEL_MIN_FRAME_RATE()) && (usVfreqMax <= GET_DRR_PANEL_MAX_FRAME_RATE())) &&
                       ((ABSDWORD(usVfreqMax, usIVfreqApproximate)) < (usIVfreqApproximate * 30 / 100)))
                    {
                        // IVFmax is calculated by CVT timing
                        *pusVfreqMax = usVfreqMax;
                        return _TABLE_SEARCHING_WITH_IVF_MAX;
                    }
                }
                break;

            default:
                break;
        }
    }
#endif

    *pusVfreqMax = 0;
    return _TABLE_SEARCHING_WITHOUT_IVF_MAX;
}
#endif

#if((_FRC_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I))
//--------------------------------------------------
// Description  : Choose DB apply mode when _DB_APPLY_POLLING
// Input Value  : DBctrl, DataPathIndex, DB path select
// Output Value : None
//--------------------------------------------------
void ScalerMDomainIDDomainDBApplyFRCModeSetDB(EnumInputDataPath enumSelectedDataPath)
{
    StructDBDataPathGroup structDataPathGroupInfo = {0};
    EnumFRCPageSelect enumPageSelect = _FRC_MAIN1_PAGE;
    BYTE ucGroupIndex = 0x00;

    // Divide input data path into several groups (e.g. (M1_M2, S1_S2) or (M2, M3, M4))
    ScalerGlobalIDDomainDBGetDataPathGroup(enumSelectedDataPath, &structDataPathGroupInfo);

    // Clear pending I/D domain DB ready bit
    ScalerGlobalIDDomainDBClearReadyBit(enumSelectedDataPath);

    // Set DB buffer start address
    ScalerGlobalIDDomainDBSetBufferAddress(&structDataPathGroupInfo);

    for(ucGroupIndex = 0; ucGroupIndex < (structDataPathGroupInfo.ucGroupNum); ucGroupIndex++)
    {
        BYTE ucDBctrl = ScalerGlobalGetIDomainDBApplyBit(structDataPathGroupInfo.penumGroup[ucGroupIndex]);
        EnumFRCChannelPageSelect enumFRCChPage = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(structDataPathGroupInfo.penumGroup[ucGroupIndex]));
        EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(structDataPathGroupInfo.penumGroup[ucGroupIndex]);

        structDataPathGroupInfo.pucFtearPrevent[ucGroupIndex] = (bit)GET_PAGED_BIT(ScalerFRCDispGetPageSelect(structDataPathGroupInfo.penumGroup[ucGroupIndex]), P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, _BIT6);

        for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
            {
                enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);

                // Disable ftear prevent
                SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, 0x00); // margin = 2
            }
        }

        // Wait Iden_start event
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_START, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
        ScalerTimerDelayXms(2);

        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_I_DOMAIN_DB_MASK, ucDBctrl);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        // Set FC Eagle Sight Capture DB Apply
        ScalerFmtCnvEagleSightSetCaptureDBCtrl(_FC_CAPTURE_DB_APPLY);
#endif
#endif

        // Wait I double buffer
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucDBctrl, 0);

        ScalerIDomainSettingAfterIDB();

        // Enable FRC display freeze mode
        SET_PAGED_BIT(enumFRCChPage, P46_82_M_DISP_BLOCK_SEL, ~(_BIT4), _BIT4);

        // Enable FRC cap block free
        SET_PAGED_BIT(enumFRCChPage, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), _BIT3);

        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);

        switch(GET_MEMORY_FRAME_BUFFER())
        {
            case _MEMORY_1_FRAME_BUFFER:
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                break;

            case _MEMORY_2_FRAME_BUFFER:
            default:
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                break;

            case _MEMORY_3_FRAME_BUFFER:
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                break;
        }

        // Disable FRC cap block free
        SET_PAGED_BIT(enumFRCChPage, P46_03_M_CAP_BLOCK_SEL, ~(_BIT3), 0x00);
    }

    // Check D domain status
    if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == _BIT0) &&
       (GET_DPLL_POWER_STATUS() == _TRUE))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

        // Set D apply bit
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

        // Wait D double buffer
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);

        // Disable FRC disp freeze
        ScalerFRCDisplayFreezeDisable();

        // Wait Iden_stop event
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, enumSelectedDataPath);
    }

    for(ucGroupIndex = 0; ucGroupIndex < (structDataPathGroupInfo.ucGroupNum); ucGroupIndex++)
    {
        EnumMDomainDisplayDataPath enumMDispPath = ScalerFRCGetMDispPath(structDataPathGroupInfo.penumGroup[ucGroupIndex]);

        if(structDataPathGroupInfo.pucFtearPrevent[ucGroupIndex] == _TRUE)
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_D_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                if(CHK_FRC_PATH(enumMDispPath, GET_FRC_OUTPUT_DATA_PATH(ucIndex)) == _TRUE)
                {
                    enumPageSelect = GET_FRC_PAGE_SELECT(ucIndex);
                    SET_PAGED_BYTE(enumPageSelect, P5_C4_DISP_M1_FRAME_TEAR_PREVENTION, (_BIT6 | _FRC_FRAME_TEAR_PREVENT_LINE)); // margin = 2
                }
            }
        }
    }
}
#endif

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON) || (_DRR_SUPPORT == _ON))
#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DCLK & DVtotal margin when frame sync line buffer
// Input Value  : NA
// Output Value : Pass or fail
//--------------------------------------------------
bit ScalerMDomainFSLineBufferDclkDvtotalCheck(void)
{
    DWORD ulPanelClockMaxSpread = MAXOF(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());
    DWORD ulPanelClockMinSpread = MINOF(GET_PANEL_PIXEL_CLOCK_MIN_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());

    // Dclk_max_spread < Dclk_min_spread, not make sense!
    if(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD() < GET_PANEL_PIXEL_CLOCK_MIN_SPREAD())
    {
        return _FALSE;
    }

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI21_FVA_SUPPORT == _ON)
    if(GET_HDMI21_FVA_ENABLE() == _TRUE)
    {
        if(GET_HDMI21_FVA_IVF_INFO() == _TRUE)
        {
            // Frame sync Dvtotal
            PDATA_WORD(0) = GET_MDOMAIN_INPUT_VTOTAL() * (DWORD)g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight;

            if(PDATA_WORD(0) < (_PANEL_DV_TOTAL_MIN + _PANEL_DV_TOTAL_FINE_TUNE_MARGIN))
            {
                return _FALSE;
            }
        }
    }
#endif
#endif

#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
    {
        if(GET_DRR_IVF_INFO() == _TRUE)
        {
            // Frame sync Dvtotal
            PDATA_WORD(0) = GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_VTOTAL(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT());

            if(PDATA_WORD(0) < (_PANEL_DV_TOTAL_MIN + _PANEL_DV_TOTAL_FINE_TUNE_MARGIN))
            {
                return _FALSE;
            }

            // IVTotal_max
            PDATA_WORD(1) = GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_HFREQ(), 1000, GET_DRR_VFREQ_MIN());

            // Frame sync Dvtotal
            PDATA_WORD(1) = GET_DWORD_MUL_DIV(PDATA_WORD(1), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT());

            if(PDATA_WORD(1) > (_PANEL_DV_TOTAL_MAX - _PANEL_DV_TOTAL_FINE_TUNE_MARGIN))
            {
                return _FALSE;
            }
        }
        else
        {
            // If DRR mode, but not get DRR IVF, force frame buffer
            return _FALSE;
        }
    }
    else
#endif
    {
        // Frame sync Dvtotal
        PDATA_WORD(0) = GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_VTOTAL(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT());

        if((PDATA_WORD(0) > (_PANEL_DV_TOTAL_MAX - _PANEL_DV_TOTAL_FINE_TUNE_MARGIN)) || (PDATA_WORD(0) < (_PANEL_DV_TOTAL_MIN + _PANEL_DV_TOTAL_FINE_TUNE_MARGIN)))
        {
            return _FALSE;
        }
    }

    // Dclk_min > (Panel_max_clk - margin - SSCG/2)
    if(GET_FRAME_SYNC_DCLK_FROM_DHTOTAL(_PANEL_DH_TOTAL_MIN) > ulPanelClockMaxSpread)
    {
        return _FALSE;
    }

    // Dclk_max < (Panel_min_clk + margin + SSCG/2)
    if(GET_FRAME_SYNC_DCLK_FROM_DHTOTAL(_PANEL_DH_TOTAL_MAX) < ulPanelClockMinSpread)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif
#endif

//--------------------------------------------------
// Description  : Perform D-domain related display setting
// Input Value  : FIFO info
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetDDomain(const StructSDRAMDataInfo *pstFIFOScaling)
{
#if(_FRC_SUPPORT == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
    // D domain DB status backup is for SU/ fifo/ DTG set at the same time in specific case. not need to backup DTG DB
    bit bDDomainDBStatus = ScalerGlobalGetDDomainDBStatus();
#endif
#endif

    switch(GET_MEMORY_CONFIG_SELECT())
    {
        case _FRAME_SYNC_LINE_BUFFER:

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Extension Recapture Setting
            ScalerScalingSetExtensionRecapture(pstFIFOScaling->usOutputHWidth, pstFIFOScaling->usOutputVHeight);
#endif
            // Scaling Up Setting
            ScalerScalingSetScalingUp(pstFIFOScaling);

#if(_M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT == _ON)
            ScalerMemoryForceMemoryDataBit10to8();
#endif
            // Set FIFO Capture Window
            ScalerMemorySetFifoCapture(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOScaling->usOutputHWidth, pstFIFOScaling->usOutputVHeight);

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
            if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
            {
                ScalerMemorySetFramesyncFixLastlineEnable(_ENABLE);
            }
#endif
            // Set Initial Dt Value
            ScalerMemoryFrameSyncSetDt(_DT_TARGET_PERCENTAGE, pstFIFOScaling->usOutputVHeight);

            // Set display Format
            ScalerMDomainSetDisplayFormat(_FRAME_SYNC_LINE_BUFFER);

            break;

#if(_FRC_SUPPORT == _ON)
        case _FRAME_SYNC_MEMORY:
        case _FREE_RUN_MEMORY:
        case _MN_FRAME_SYNC_MEMORY:


            ///////////////////////////////////////////////////////////////////////////
            // The following 3 functions should not be delayed or changed in order
            ///////////////////////////////////////////////////////////////////////////

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
            if(bDDomainDBStatus == _DISABLE)
            {
                switch(GET_DISPLAY_MODE())
                {
                    case _DISPLAY_MODE_1P:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_3P_FLAG:
#endif
                        break;

                    default:
                        ScalerGlobalDDomainDoubleBufferEnable(_ENABLE);
                        break;
                }
            }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Extension Recapture Setting
            ScalerScalingSetExtensionRecapture(pstFIFOScaling->usOutputHWidth, pstFIFOScaling->usOutputVHeight);
#endif
            // Scaling Up Setting
            ScalerScalingSetScalingUp(pstFIFOScaling);

            // Set FIFO Capture Window
            ScalerMemorySetFifoCapture(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOScaling->usOutputHWidth, pstFIFOScaling->usOutputVHeight);

            // Set display Format
            ScalerMDomainSetDisplayFormat(GET_MEMORY_CONFIG_SELECT());

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
            // if ddomain db status has been changed, restoration is needed
            if((ScalerGlobalGetDDomainDBStatus() == _ENABLE) && (bDDomainDBStatus == _DISABLE))
            {
                ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()), _DB_APPLY_POLLING);
                ScalerGlobalDDomainDoubleBufferEnable(bDDomainDBStatus);
            }
#endif

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
            {
                if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)
                {
                    ScalerMemorySetFramesyncFixLastlineEnable(_ENABLE);
                }
                else
                {
                    ScalerMemorySetFramesyncFixLastlineEnable(_DISABLE);
                }
            }
#endif


            ///////////////////////////////////////////////////////////////////////////
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set Display Format
// Input Value  : free run/ frame sync line buffer/ frame sync frame buffer /
//                MN frame sync/ free run no input
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayFormat(EnumMemoryConfig enumMemoryConfig)
{
    bit bDispFotmatDoubleBuf = 0;
    bit bDDomainDBApply = _FALSE;
    bit bDclkSetting = _TRUE;
    WORD usFreeRunDVtotal = 0;
    WORD usWatchDogDVtotal = 0;

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
    WORD usDhtotalBackup = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
#endif

    if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) && (GET_MDOMAIN_OUTPUT_VBHEIGHT() == GET_MDOMAIN_OUTPUT_VHEIGHT()))
    {
        SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
       ((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_FORCE_DISPLAY_1P_MODE() == _TRUE)))
    {
        SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
    }
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
    {
        ScalerMDomainSetFrameSyncSource((GET_2P_FRAME_SYNC_MAIN() == _TRUE) ? _FRAME_SYNC_MAIN : _FRAME_SYNC_SUB);
    }
    else
    {
        ScalerMDomainSetFrameSyncSource(_FRAME_SYNC_MAIN);
    }
#endif

    switch(enumMemoryConfig)
    {
        case _FRAME_SYNC_LINE_BUFFER:

#if(_DRR_SUPPORT == _ON)
            if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
            {
                // DVtotal for WD setting
                usWatchDogDVtotal = _PANEL_DV_TOTAL_MAX + 64;

                // DVtotal for free run setting
                usFreeRunDVtotal = (DWORD)GET_MDOMAIN_OUTPUT_VTOTAL() * GET_MDOMAIN_INPUT_VFREQ() / GET_DRR_PANEL_MIN_FRAME_RATE();

                if(usFreeRunDVtotal > _PANEL_DV_TOTAL_MAX)
                {
                    usFreeRunDVtotal = _PANEL_DV_TOTAL_MAX;
                }
            }
            else
#endif
            {
                // DVtotal for WD setting
                usWatchDogDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL() + 64;

                // DVtotal for free run setting
                usFreeRunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();
            }

            // Enable Display Timing, Set Frame sync
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            break;

#if(_FRC_SUPPORT == _ON)

        case _MN_FRAME_SYNC_MEMORY:

            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
            {
                // DVtotal for WD setting
                usWatchDogDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL() + 64;

                if(ScalerMemoryGetFrameTrackingEnable() == _ENABLE)
                {
                    // DVtotal for free run setting
                    usFreeRunDVtotal = GET_FREE_RUN_DVTOTAL();

                    SET_MDOMAIN_OUTPUT_HTOTAL(ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL));
                }
                else
                {
#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
                    // DVtotal for free run setting
                    usFreeRunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();
#else
                    // DVtotal for free run setting
                    usFreeRunDVtotal = usWatchDogDVtotal + 1;
#endif
                }
            }

            break;

        case _FRAME_SYNC_MEMORY:

            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
            {
#if(_DRR_SUPPORT == _ON)
                if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
                {
                    // DVtotal for WD setting
                    usWatchDogDVtotal = _PANEL_DV_TOTAL_MAX + 64;

                    // DVtotal for free run setting
                    usFreeRunDVtotal = ((DWORD)GET_MDOMAIN_OUTPUT_VTOTAL() * GET_MDOMAIN_INPUT_VFREQ() / GET_DRR_PANEL_MIN_FRAME_RATE()) + 1;

                    if(usFreeRunDVtotal > _PANEL_DV_TOTAL_MAX)
                    {
                        usFreeRunDVtotal = _PANEL_DV_TOTAL_MAX;
                    }
                }
                else
#endif
                {
                    // DVtotal for WD setting
                    usWatchDogDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL() + 64;

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
                    // DVtotal for free run setting
                    usFreeRunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();
#else
                    // DVtotal for free run setting
                    usFreeRunDVtotal = usWatchDogDVtotal + 1;
#endif
                }
            }

            break;

        case _FREE_RUN_MEMORY:

            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
            {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
                if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
                   ((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
                {
                    PDATA_WORD(2) = _PANEL_DV_TOTAL;
                }
                else
#endif
                {
                    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) &&
                       (GET_MDOMAIN_OUTPUT_VHEIGHT() == _PANEL_DV_HEIGHT) &&
                       (GET_MDOMAIN_INPUT_VFREQ() > _PANEL_MAX_FRAME_RATE))
                    {
                        PDATA_WORD(2) = ScalerFRCSetOneFrameDVTotal();
                    }
                    else if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) &&
                            (((GET_MDOMAIN_OUTPUT_VHEIGHT() < _PANEL_DV_HEIGHT) && (GET_MDOMAIN_INPUT_VFREQ() > _PANEL_MAX_FRAME_RATE)) || (GET_MDOMAIN_INPUT_VFREQ() < _PANEL_MIN_FRAME_RATE)))
                    {
                        PDATA_WORD(2) = _PANEL_DV_TOTAL_MIN;
                    }
                    else
                    {
                        PDATA_WORD(2) = _PANEL_DV_TOTAL;
                    }
                }

                // DVtotal for WD setting
                usWatchDogDVtotal = PDATA_WORD(2) + 64;

                // DVtotal for free run setting
                usFreeRunDVtotal = PDATA_WORD(2);

                // Dvtotal != _PANEL_DV_TOTAL need to update Dclk when one frame FRC
                if(PDATA_WORD(2) != _PANEL_DV_TOTAL)
                {
                    // Update Dclk
                    SET_D_CLK_FREQ(GET_D_CLK_FRAME_BUFFER(PDATA_WORD(2), 0));
                }
            }
            else if(ScalerMDomainCheckMTPFreerunFinetune() == _TRUE)
            {
                usWatchDogDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL() + 64;

                usFreeRunDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();
            }
            break;

#endif // End of #if(_FRC_SUPPORT == _ON)

        case _FREE_RUN_NO_INPUT:
        default:
            ScalerMDomainSetDisplayTimingGenDHTotalLastline(_PANEL_DH_TOTAL);

            ScalerMDomainSetDisplayTimingGenHVSyncWidth(_PANEL_DH_SYNC_WIDTH, GET_MDOMAIN_OUTPUT_VSYNCHEIGHT());

            if(GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1)
            {
                // Set Background
                ScalerMDomainSetDisplayTimingGenBackground(_DISPLAY_RGN_1P);
            }

            ScalerMDomainSetDisplayTimingGenDisplayMode(GET_DISPLAY_MODE());

            ScalerMDomainSetDisplayTimingGenActiveEnable(GET_MDOMAIN_OUTPUT_RGN(), GET_MODE_DISPLAY_TARGET_REGION(), _ENABLE);
#if((_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
            ScalerDDomainSetBackgroundVerticalChange(GET_DISPLAY_MODE());
#endif
            // Disable Interlaced_FS_Delay_Fine_Tuning
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

            // PDATA_WORD(2): Calculate DVtotal
            PDATA_WORD(2) = GET_MDOMAIN_OUTPUT_VTOTAL();

            // DVtotal for WD setting
            usWatchDogDVtotal = PDATA_WORD(2) + 64;

            // DVtotal for free run setting
            usFreeRunDVtotal = PDATA_WORD(2) + 1;

            // Enable Display Timing, and enable free run mode
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_FRC_SUPPORT == _ON)
            // Disable M:N frame sync mode
            ScalerMemorySetFrameTrackingEnable(_DISABLE);
#endif
            {
#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
                DWORD ulDclkBackup = GET_D_CLK_FREQ();
#endif

                ScalerMDomainCalculateDclkDVtotal(_FREE_RUN_NO_INPUT);

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
                if(GET_DPLL_POWER_STATUS() == _TRUE)
                {
                    if(GET_FREE_RUN_DDOMAIN_SETTING() == _KEEP_FREERUN_DDOMAIN_SETTING)
                    {
                        SET_D_CLK_FREQ(ulDclkBackup);
                    }
                    else
                    {
                        if(ulDclkBackup == GET_D_CLK_FREQ())
                        {
                            bDclkSetting = _FALSE;
                        }
                    }
                }
#endif
            }

            break;
    }

    // If IMD global DB or D global DB off, turn on display double buffer
    if((ScalerGlobalGetDDomainDBStatus() == _DISABLE) && (enumMemoryConfig != _FREE_RUN_NO_INPUT))
    {
        bDispFotmatDoubleBuf = (bit)ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT6);
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT6, _BIT6);
    }

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            switch(GET_MDOMAIN_OUTPUT_RGN())
            {
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
                case _DDOMAIN_RGN_R2_A1:
                    ScalerMDomainSetBackground_R2();
                    break;
#endif
                default:
                    break;
            }
            break;

        default:
            break;
    }
#endif

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
    if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        // Enable Active Region after FRC Display Enable
        ScalerMDomainSetDisplayTimingGenActiveEnable(GET_MDOMAIN_OUTPUT_RGN(), GET_MODE_DISPLAY_TARGET_REGION(), _ENABLE);
    }
#endif

    // Display timing gen setting
    bDDomainDBApply = ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_RGN());

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    ScalerGlobalDoubleBufferSetMDForceApplyFrameEnd(ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END));
#endif

    if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) ||
       (enumMemoryConfig == _FREE_RUN_NO_INPUT) ||
       (ScalerMDomainCheckMTPFreerunFinetune() == _TRUE))
    {
#if(_FRC_SUPPORT == _ON)
        // M:N case reset to display setting, no need to set M:N tracking again
        if((enumMemoryConfig != _MN_FRAME_SYNC_MEMORY) ||
           (ScalerMemoryGetFrameTrackingEnable() == _DISABLE))
#endif
        {
#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
            if((GET_DPLL_POWER_STATUS() == _TRUE) &&
               (enumMemoryConfig == _FREE_RUN_NO_INPUT) &&
               (GET_FREE_RUN_DDOMAIN_SETTING() == _KEEP_FREERUN_DDOMAIN_SETTING))
            {
            }
            else
#endif
            {
                // Set DHtotal and last line
                ScalerMDomainSetDisplayTimingGenDHTotalLastline(GET_MDOMAIN_OUTPUT_HTOTAL());

                // Set Frame Sync Watch Dog
                SET_DIS_TIMING_GEN_WD_VTOTAL(usWatchDogDVtotal);

                // Set DVtotal for free run
                SET_FREE_RUN_DVTOTAL(usFreeRunDVtotal);

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
                if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
                {
                    // Frame sync line buffer need to fine tune Dclk according I-active-region & D-active-region
                    if(usDhtotalBackup != ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL))
                    {
                        bDDomainDBApply = _TRUE;
                    }
                }
#endif
                DebugMessageScaler("DCLK", GET_D_CLK_FREQ());

                if(bDclkSetting == _TRUE)
                {
#if(_GOSD_SUPPORT == _ON)
                    BYTE ucOsdStatus = ScalerGosdDispOsdClkSelectPreProc();
#endif
                    // Set DClk
                    ScalerPLLSetDPLLFreq(GET_D_CLK_FREQ());

#if(_GOSD_SUPPORT == _ON)

                    ScalerGosdDispOsdClkSelectPostProc(ucOsdStatus, _TRUE);
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
                    SET_FREE_RUN_DDOMAIN_SETTING(_DEFAULT_FREERUN_DDOMAIN_SETTING);
#endif
                }
            }
        }
    }

    if(ScalerGlobalGetDDomainDBStatus() == _DISABLE)
    {
        if(enumMemoryConfig != _FREE_RUN_NO_INPUT)
        {
            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
            {
                // for osd timing gen. effect in next frame
                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                // Set OSD Timing Gen.
                ScalerOsdSetTimingGen(GET_MDOMAIN_OUTPUT_VBSTART(), GET_MDOMAIN_OUTPUT_VBHEIGHT(), GET_MDOMAIN_OUTPUT_HBSTART(), _FALSE);
            }

            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
            ScalerTimerPollingFlagProc(20, P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT5, 0);

            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT6, ((BYTE)bDispFotmatDoubleBuf << 6));
        }
        else
        {
            // Set OSD Timing Gen.
            ScalerOsdSetTimingGen(GET_MDOMAIN_OUTPUT_VBSTART(), GET_MDOMAIN_OUTPUT_VBHEIGHT(), GET_MDOMAIN_OUTPUT_HBSTART(), ((_SMART_OSD_DISABLE_IN_ASPECT_RATIO_CHANGE == _ON) ? (_TRUE) : (_FALSE)));
        }
    }
    else
    {
        if(bDDomainDBApply == _TRUE)
        {
            if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) || (enumMemoryConfig == _FREE_RUN_NO_INPUT))
            {
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
                // for osd timing gen. effect in next frame
                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
#endif
                // Set OSD Timing Gen.
                ScalerOsdSetTimingGen(GET_MDOMAIN_OUTPUT_VBSTART(), GET_MDOMAIN_OUTPUT_VBHEIGHT(), GET_MDOMAIN_OUTPUT_HBSTART(), _FALSE);
            }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
            ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()), _DB_APPLY_POLLING);
#endif
        }
        else
        {
            if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) || (enumMemoryConfig == _FREE_RUN_NO_INPUT))
            {
                // Set OSD Timing Gen.
                ScalerOsdSetTimingGen(GET_MDOMAIN_OUTPUT_VBSTART(), GET_MDOMAIN_OUTPUT_VBHEIGHT(), GET_MDOMAIN_OUTPUT_HBSTART(), _FALSE);
            }
        }
    }

    // Adjist OSD by D H Porch
    ScalerOsdSetOsdHPorchAdjust();

#if(_GOSD_SUPPORT == _ON)
    // Set GOSD DispOsd Clk
    ScalerGosdDispOsdClkSelect();
#endif
}

//--------------------------------------------------
// Description  : Set Dclk and DVtotal macro, real DVtotal setting for BW calculate
// Input Value  : free run/ frame sync line buffer/ frame sync frame buffer /
//                MN frame sync/ free run no input
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainCalculateDclkDVtotal(EnumMemoryConfig enumMemoryConfig)
{
    bit bDclkCalculateMethod = _FRAME_BUFFER_METHOD;
    DWORD ulDclk = 0;
    StructDHVtotal stHVTotal;

    switch(enumMemoryConfig)
    {
        case _FRAME_SYNC_LINE_BUFFER:

            bDclkCalculateMethod = _LINE_BUFFER_METHOD;

#if(_DRR_SUPPORT == _ON)
            if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
            {
                if(GET_DRR_IVF_INFO() == _TRUE)
                {
                    SET_MDOMAIN_OUTPUT_VTOTAL(((DWORD)GET_MDOMAIN_INPUT_HFREQ() * (DWORD)(GET_MDOMAIN_OUTPUT_VHEIGHT()) / GET_MDOMAIN_INPUT_VHEIGHT() * 1000) / GET_MDOMAIN_INPUT_VFREQ());
                }
                else
                {
                    SET_MDOMAIN_OUTPUT_VTOTAL(GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_VTOTAL(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT()));
                }
            }
            else
#endif
            {
#if(_HDMI_SUPPORT == _ON)
#if(_HDMI21_FVA_SUPPORT == _ON)
                if(GET_HDMI21_FVA_ENABLE() == _TRUE)
                {
                    // Using GET_INPUT_TIMING_VTOTAL() to get DVtotal in FVA only case
                    SET_MDOMAIN_OUTPUT_VTOTAL(GET_DWORD_MUL_DIV(GET_INPUT_TIMING_VTOTAL(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT()));
                }
                else
#endif
#endif
                {
                    SET_MDOMAIN_OUTPUT_VTOTAL(GET_DWORD_MUL_DIV(GET_MDOMAIN_INPUT_VTOTAL(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT()));
                }
            }

            // Calculate Dclk
            ulDclk = GET_D_CLK_LINE_BUFFER();

            break;

#if(_FRC_SUPPORT == _ON)

        case _MN_FRAME_SYNC_MEMORY:

            // Calculate Dclk
            ulDclk = GET_D_CLK_FRAME_BUFFER(_PANEL_DV_TOTAL, _PANEL_LAST_LINE_TARGET);

            break;

        case _FRAME_SYNC_MEMORY:

#if(_DRR_SUPPORT == _ON)
            if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
            {
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF)
                if((ScalerMDomainFSLineBufferDclkDvtotalCheck() == _TRUE) &&
                   (GET_MDOMAIN_OUTPUT_VBHEIGHT() == GET_MDOMAIN_OUTPUT_VHEIGHT()))
                {
                    bDclkCalculateMethod = _LINE_BUFFER_METHOD;

                    // Set DVTotal
                    SET_MDOMAIN_OUTPUT_VTOTAL((DWORD)GET_MDOMAIN_INPUT_VTOTAL() * (DWORD)(GET_MDOMAIN_OUTPUT_VHEIGHT()) / GET_MDOMAIN_INPUT_VHEIGHT());

                    // Calculate Dclk
                    ulDclk = GET_D_CLK_LINE_BUFFER();
                }
                else
#endif
                {
                    WORD usFrameSyncDVtotal = _PANEL_DV_TOTAL;

#if((_PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON) || (_PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON))
                    WORD usFSDVtotalMargin = usFrameSyncDVtotal;
                    WORD usFSDrrDVtotalMargin = usFrameSyncDVtotal;
#if(_PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON)
                    // Frame sync DVtotal Consider Vfreq margin, roundup DVtotal/ Vfreq
                    usFSDVtotalMargin += (_PANEL_DV_TOTAL / GET_MDOMAIN_INPUT_VFREQ()) + ((_PANEL_DV_TOTAL % GET_MDOMAIN_INPUT_VFREQ()) ? 1 : 0);
#endif

#if(_PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON)
                    // DRR Frame sync DVtotal Consider IVF max +0.5%
                    if(((DWORD)GET_MDOMAIN_INPUT_VFREQ() * 1005 / 1000) >= GET_DRR_PANEL_MAX_FRAME_RATE())
                    {
                        usFSDrrDVtotalMargin += ((_PANEL_DV_TOTAL * 5) / 1000) + (((_PANEL_DV_TOTAL * 5) % 1000) ? 1 : 0);
                    }
#endif
                    usFrameSyncDVtotal = MAXOF(usFSDVtotalMargin, usFSDrrDVtotalMargin);

                    if(usFrameSyncDVtotal > _PANEL_DV_TOTAL_MAX)
                    {
                        usFrameSyncDVtotal = _PANEL_DV_TOTAL_MAX;
                    }
#endif

                    // Calculate Dclk
                    ulDclk = GET_D_CLK_FRAME_BUFFER(usFrameSyncDVtotal, _PANEL_LAST_LINE_TARGET);
                }
            }
            else
#endif
            {
                WORD usFrameSyncDVtotal = _PANEL_DV_TOTAL;

#if(_PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON)
                // Frame sync DVtotal Consider Vfreq margin, roundup DVtotal/ Vfreq
                usFrameSyncDVtotal += (_PANEL_DV_TOTAL / GET_MDOMAIN_INPUT_VFREQ()) + ((_PANEL_DV_TOTAL % GET_MDOMAIN_INPUT_VFREQ()) ? 1 : 0);

                if(usFrameSyncDVtotal > _PANEL_DV_TOTAL_MAX)
                {
                    usFrameSyncDVtotal = _PANEL_DV_TOTAL_MAX;
                }
#endif

                // Calculate Dclk
                ulDclk = GET_D_CLK_FRAME_BUFFER(usFrameSyncDVtotal, _PANEL_LAST_LINE_TARGET);

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
                ScalerMbrAdvanceUpdateRtkAdvMbrDisplayInfo(&ulDclk);
#endif
            }

            break;

        case _FREE_RUN_MEMORY:

            // Calculate Dclk
            ulDclk = GET_D_CLK_FRAME_BUFFER(_PANEL_DV_TOTAL, 0);

            break;

#endif // End of #if(_FRC_SUPPORT == _ON)

        case _FREE_RUN_NO_INPUT:
        default:

            // Calculate Dclk
            ulDclk = GET_D_CLK_TYPICAL();

            break;
    }

    if((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) ||
       (enumMemoryConfig == _FREE_RUN_NO_INPUT) ||
       (ScalerMDomainCheckMTPFreerunFinetune() == _TRUE))
    {
#if(_FRC_SUPPORT == _ON)
        // M:N case reset to display setting, no need to set M:N tracking again
        if((enumMemoryConfig != _MN_FRAME_SYNC_MEMORY) ||
           (ScalerMemoryGetFrameTrackingEnable() == _DISABLE))
#endif
        {
            // If Dclk over panel, fine tune DHtotal, DVtotal and Dclk
            stHVTotal = ScalerMDomainDHVtotalFinetune(ulDclk, enumMemoryConfig, bDclkCalculateMethod);

            if((stHVTotal.usDVtotal != GET_MDOMAIN_OUTPUT_VTOTAL()) || (stHVTotal.usDHtotal != GET_MDOMAIN_OUTPUT_HTOTAL()))
            {
                if(stHVTotal.usDHtotal != GET_MDOMAIN_OUTPUT_HTOTAL())
                {
                    // Calculate Target Dclk
                    ulDclk = GET_DWORD_MUL_DIV(ulDclk, stHVTotal.usDHtotal, GET_MDOMAIN_OUTPUT_HTOTAL());

                    SET_MDOMAIN_OUTPUT_HTOTAL(stHVTotal.usDHtotal);
                }

                if((stHVTotal.usDVtotal != GET_MDOMAIN_OUTPUT_VTOTAL()) &&
                   (ScalerMDomainCheckDVtotalFinetune(enumMemoryConfig) == _TRUE))
                {
                    ulDclk = GET_DWORD_MUL_DIV(((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * stHVTotal.usDVtotal), g_usMDomainDVFreq, 10000);

                    SET_MDOMAIN_OUTPUT_VTOTAL(stHVTotal.usDVtotal);
                }
            }

            SET_D_CLK_FREQ(ulDclk);
        }
    }

    ScalerMDomainSetDclkConfig();

    if(enumMemoryConfig == _FRAME_SYNC_MEMORY)
    {
#if(_DRR_SUPPORT == _ON)
        if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) == _DRR_NONE_TYPE)
#endif
        {
#if(_HDMI_SUPPORT == _ON)
#if(_HDMI21_FVA_SUPPORT == _ON)
            if(GET_HDMI21_FVA_ENABLE() == _TRUE)
            {
                // Update FVA only output Vtotal
                SET_MDOMAIN_OUTPUT_VTOTAL(GET_DWORD_MUL_DIV(GET_MDOMAIN_OUTPUT_VTOTAL(), GET_MDOMAIN_INPUT_VFREQ(), GET_INPUT_TIMING_VFREQ()));
            }
#endif
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Check Display Format
// Input Value  : enumSelRegion
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainCheckDisplayFormat(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if((_EAGLE_SIGHT_SUPPORT == _ON) && (_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON))
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        // Remain Vstart/VHeigth.. at ES Original Mode.
    }
    else
#endif
    {
        // Check display format resolution to be even
        SET_MDOMAIN_OUTPUT_VSTART((GET_MDOMAIN_OUTPUT_VSTART() + 1) & 0xFFFE);
        SET_MDOMAIN_OUTPUT_VBSTART((GET_MDOMAIN_OUTPUT_VBSTART() + 1) & 0xFFFE);
        SET_MDOMAIN_OUTPUT_VHEIGHT((GET_MDOMAIN_OUTPUT_VHEIGHT() + 1) & 0xFFFE);
        SET_MDOMAIN_OUTPUT_VBHEIGHT((GET_MDOMAIN_OUTPUT_VBHEIGHT() + 1) & 0xFFFE);
    }

#if(_PANEL_STYLE == _PANEL_LVDS)
    // Check display format resolution according to LVDS port count
    SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() - (GET_MDOMAIN_OUTPUT_HSTART() % ((BYTE)1 << _PANEL_LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - (GET_MDOMAIN_OUTPUT_HWIDTH() % ((BYTE)1 << _PANEL_LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HBSTART() - (GET_MDOMAIN_OUTPUT_HBSTART() % ((BYTE)1 << _PANEL_LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HBWIDTH() - (GET_MDOMAIN_OUTPUT_HBWIDTH() % ((BYTE)1 << _PANEL_LVDS_OUTPUT_PORT)));
#else
    SET_MDOMAIN_OUTPUT_HSTART((GET_MDOMAIN_OUTPUT_HSTART() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_HBSTART((GET_MDOMAIN_OUTPUT_HBSTART() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_HWIDTH((GET_MDOMAIN_OUTPUT_HWIDTH() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_HBWIDTH((GET_MDOMAIN_OUTPUT_HBWIDTH() + 1) & 0xFFFE);
#endif

    // 1P/PIP main/Eaglesight main FB mode: output hwidth need to be multiple of 4
    if((ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE) &&
       ((enumDisplayRegion == _DISPLAY_RGN_1P) ||
        (enumDisplayRegion == _DISPLAY_RGN_PIP_MAIN) ||
        (enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)))
    {
        if((GET_MDOMAIN_OUTPUT_HWIDTH() % 4) != 0)
        {
            DebugMessageScaler("[Warning]!!!!!! 1P/PIP main/Eaglesight main FB mode output hwidth not multiple of 4", GET_MDOMAIN_OUTPUT_HWIDTH());

            SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() & 0xFFFC);
        }

        if(GET_MDOMAIN_OUTPUT_HBWIDTH() >= GET_MDOMAIN_OUTPUT_HWIDTH())
        {
            if(GET_MDOMAIN_OUTPUT_HSTART() != (GET_MDOMAIN_OUTPUT_HBSTART() + ((GET_MDOMAIN_OUTPUT_HBWIDTH() - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2)))
            {
                DebugMessageScaler("[Warning]!!!!!! 1P/PIP main/Eaglesight main FB mode hactive not central symmetrically", GET_MDOMAIN_OUTPUT_HSTART());

                SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HBSTART() + ((GET_MDOMAIN_OUTPUT_HBWIDTH() - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2));
            }
        }
        else
        {
            DebugMessageScaler("[Warning]!!!!!! Output background hwidth < Output hwidth", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Memory Config
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
EnumMemoryWorkMode ScalerMDomainMemoryConfig(void)
{
#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
    return _MEMORY_WORK_MODE;
#endif

#if(_FRC_SUPPORT == _ON)
    if(g_stDisplayCustomizedData.structDVCustomizedFreq.b1DecideMemoryConfig == _FORCE_FRAME_BUFFER_MODE)
    {
        return _MEMORY_WORK_MODE;
    }
#endif

#if(_MDOMAIN_PR_MODE_SUPPORT == _ON)
    return _MEMORY_WORK_MODE;
#endif

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF)
        return _MEMORY_WORK_MODE;
#else
        BYTE ucMemoryConfig = _LINE_BUFFER_MODE;

#if(_FRC_SUPPORT == _ON)
        if((GET_MEMORY_DVF_SELECT() != _1_IVF) ||
           (GET_MDOMAIN_OUTPUT_VBHEIGHT() > GET_MDOMAIN_OUTPUT_VHEIGHT()) ||
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
           (ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) ||
#endif
           (ScalerMDomainFSLineBufferDclkDvtotalCheck() == _FALSE))
        {
            ucMemoryConfig = _MEMORY_WORK_MODE;
        }

        if(GET_MEMORY_DVF_SELECT() == _PANEL_TYP_FRAME_RATE_FREE_RUN)
        {
            ucMemoryConfig = _MEMORY_WORK_MODE;
        }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(GET_ROT_TYPE() != _ROT_DISABLE)
        {
            ucMemoryConfig = _MEMORY_WORK_MODE;
        }
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
        if(GET_MDOMAIN_SOURCE_TYPE() == _SOURCE_HDMI)
        {
            // if ALLM, then change to _MEMORY_WORK_MODE
            if(ucMemoryConfig == _LINE_BUFFER_MODE)
            {
                WORD usHwidth = MINOF(GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_OUTPUT_HWIDTH());

                // get mdomain input pixel clk
                PDATA_DWORD(0) = (DWORD)GET_MDOMAIN_INPUT_HFREQ() * GET_MDOMAIN_INPUT_HTOTAL() / 10; // kHz

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
                // get frc estimated bw
                PDATA_DWORD(0) = ScalerFRCBWCalUsage(usHwidth, usHwidth, GET_MEMORY_DATA_BIT(), _IMG_CMP_PARAM_LLB_8B_TYP, PDATA_DWORD(0), GET_MDOMAIN_INPUT_DATA_PATH(), _FALSE);
#else
                // get frc estimated bw
                PDATA_DWORD(0) = ScalerFRCBWCalUsage(usHwidth, usHwidth, GET_MEMORY_DATA_BIT(), _IMG_CMP_PARAM_OFF, PDATA_DWORD(0), GET_MDOMAIN_INPUT_DATA_PATH(), _FALSE);
#endif
                if(PDATA_DWORD(0) < GET_MEMORY_REMAIN_BW())
                {
                    ucMemoryConfig = _MEMORY_WORK_MODE;
                }
            }
        }
        else
#endif
        {
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            // if display latency != faster, then change to _MEMORY_WORK_MODE
            if((GET_DISP_LATENCY_RATIO() != 0x00) && (ucMemoryConfig == _LINE_BUFFER_MODE))
            {
                WORD usHwidth = MINOF(GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_OUTPUT_HWIDTH());

                // get mdomain input pixel clk
                PDATA_DWORD(0) = (DWORD)GET_MDOMAIN_INPUT_HFREQ() * GET_MDOMAIN_INPUT_HTOTAL() / 10; // kHz

                // get frc estimated bw
                PDATA_DWORD(0) = ScalerFRCBWCalUsage(usHwidth, usHwidth, GET_MEMORY_DATA_BIT(), _IMG_CMP_PARAM_LLB_8B_TYP, PDATA_DWORD(0), GET_MDOMAIN_INPUT_DATA_PATH(), _FALSE);

                if(PDATA_DWORD(0) < GET_MEMORY_REMAIN_BW())
                {
                    ucMemoryConfig = _MEMORY_WORK_MODE;
                }
                else
                {
                    SET_DISP_LATENCY_RATIO(0x00);
                }
            }
#elif(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _ON)
            if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_FREESYNC_TYPE)
#endif
            {
                if((GET_ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT() == _ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT) && (ucMemoryConfig == _LINE_BUFFER_MODE))
                {
                    ucMemoryConfig = _MEMORY_WORK_MODE;
                }
            }
#endif // End if #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
        }

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        ScalerMbrAdvanceUpdateRtkAdvMbrMemConfig(&ucMemoryConfig);
#endif
#endif

#endif // End of #if(_FRC_SUPPORT == _ON)

        return ucMemoryConfig;

#endif // End of #if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF)
    }
    else
    {
        return _MEMORY_WORK_MODE;
    }
}

//--------------------------------------------------
// Description  : If Dclk over panel spec, finetune DHtotal
// Input Value  : current Dclk/ Dclk max boundary/ Dclk min boundary
// Output Value : Fine tune status/ DHtotal
//--------------------------------------------------
StructDHtotalFTStatus ScalerMDomainDHtotalFinetune(DWORD ulDclk, DWORD ulDclkMaxBoundary, DWORD ulDclkMinBoundary)
{
    StructDHtotalFTStatus stDHtotalFTStatus;

    stDHtotalFTStatus.b1DHtotalFineTuneStatus = _TRUE;
    stDHtotalFTStatus.usDHtotal = GET_MDOMAIN_OUTPUT_HTOTAL();

    if(ulDclk > ulDclkMaxBoundary)
    {
        // Calculate target DHTotal
        stDHtotalFTStatus.usDHtotal = GET_DWORD_MUL_DIV(GET_MDOMAIN_OUTPUT_HTOTAL(), ulDclkMaxBoundary, ulDclk);
        stDHtotalFTStatus.usDHtotal -= (stDHtotalFTStatus.usDHtotal % _PANEL_DHTOTAL_MULTIPLE);

        if(stDHtotalFTStatus.usDHtotal < _PANEL_DH_TOTAL_MIN)
        {
            DebugMessageScaler("_DHTotal_over_panel", stDHtotalFTStatus.usDHtotal);

            stDHtotalFTStatus.b1DHtotalFineTuneStatus = _FALSE;
            stDHtotalFTStatus.usDHtotal = _PANEL_DH_TOTAL_MIN;
        }

        DebugMessageScaler("FS fine tune, Dclk larger than panel spec => Modify Htotal'", stDHtotalFTStatus.usDHtotal);
    }
    else if(ulDclk < ulDclkMinBoundary)
    {
        // Calculate target DHTotal
        stDHtotalFTStatus.usDHtotal = GET_DWORD_MUL_DIV(GET_MDOMAIN_OUTPUT_HTOTAL(), ulDclkMinBoundary, ulDclk);
        stDHtotalFTStatus.usDHtotal = stDHtotalFTStatus.usDHtotal + _PANEL_DHTOTAL_MULTIPLE - (stDHtotalFTStatus.usDHtotal % _PANEL_DHTOTAL_MULTIPLE);

        if(stDHtotalFTStatus.usDHtotal > _PANEL_DH_TOTAL_MAX)
        {
            DebugMessageScaler("_DHTotal_over_panel", stDHtotalFTStatus.usDHtotal);

            stDHtotalFTStatus.b1DHtotalFineTuneStatus = _FALSE;
            stDHtotalFTStatus.usDHtotal = _PANEL_DH_TOTAL_MAX;
        }

        DebugMessageScaler("FS fine tune, Dclk smaller than panel spec => Modify Htotal'", stDHtotalFTStatus.usDHtotal);
    }

    return stDHtotalFTStatus;
}

//--------------------------------------------------
// Description  : If Dclk over panel spec, finetune Display total pixel
// Input Value  : current Dclk/ Dclk max boundary/ Dclk min boundary/ Display total pixel
// Output Value : Display total pixel after fine tune
//--------------------------------------------------
DWORD ScalerMDomainDtotalLastLineFinetune(DWORD ulDclk, DWORD ulDclkMaxBoundary, DWORD ulDclkMinBoundary, DWORD ulDtotal)
{
    if(ulDclk > ulDclkMaxBoundary)
    {
        ulDtotal -= (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();
        DebugMessageFS("_Last_line_Dclk_larger", ulDtotal);
    }
    else if(ulDclk < ulDclkMinBoundary)
    {
        ulDtotal += (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();
        DebugMessageFS("_Last_line_Dclk_smaller", ulDtotal);
    }

    return ulDtotal;
}

//--------------------------------------------------
// Description  : If Dclk over panel spec, finetune DHtotal and DVtotal
// Input Value  : Dclk/ Memory select
// Output Value : ((usDVtotal << 8) | (usDHtotal))
//--------------------------------------------------
StructDHVtotal ScalerMDomainDHVtotalFinetune(DWORD ulDclk, BYTE ucMemorySel, bit bDclkCalculateMethod)
{
#if(_FRC_SUPPORT == _ON)
    DWORD ulDclkNew = 0;
#endif

    DWORD ulPanelClockMaxSpread = MAXOF(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());
    DWORD ulPanelClockMinSpread = MINOF(GET_PANEL_PIXEL_CLOCK_MIN_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());

    StructDHVtotal stHVtotal;
    StructDHtotalFTStatus stDHtotalFTStatus;
    stHVtotal.usDHtotal = GET_MDOMAIN_OUTPUT_HTOTAL();
    stHVtotal.usDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();

    ucMemorySel = ucMemorySel;

#if(_PANEL_HFREQ_FINE_TUNE == _ON)
    if(bDclkCalculateMethod == _FRAME_BUFFER_METHOD)
    {
        WORD usDHF = GET_DWORD_MUL_DIV(g_usMDomainDVFreq, stHVtotal.usDVtotal, 1000);

        if(((ucMemorySel == _FRAME_SYNC_MEMORY) || (ucMemorySel == _MN_FRAME_SYNC_MEMORY)) &&
           ((usDHF > _PANEL_DH_FREQ_MAX) || (usDHF < _PANEL_DH_FREQ_MIN)))
        {
            if(usDHF > _PANEL_DH_FREQ_MAX)
            {
                // Calculate Target DVTotal
                stHVtotal.usDVtotal = GET_DWORD_MUL_DIV(_PANEL_DH_FREQ_MAX, 1000, g_usMDomainDVFreq);
                ulDclk = GET_DWORD_MUL_DIV(ulDclk, stHVtotal.usDVtotal, GET_MDOMAIN_OUTPUT_VTOTAL());
                DebugMessageScaler("Hfreq fine tune, Dhf larger than panel spec => Modify Vtotal'", stHVtotal.usDVtotal);
            }

            else
            {
                // Calculate Target DVTotal
                stHVtotal.usDVtotal = GET_DWORD_MUL_DIV(_PANEL_DH_FREQ_MIN, 1000, g_usMDomainDVFreq) + 1;
                ulDclk = GET_DWORD_MUL_DIV(ulDclk, stHVtotal.usDVtotal, GET_MDOMAIN_OUTPUT_VTOTAL());
                DebugMessageScaler("Hfreq fine tune, Dhf smaller than panel spec => Modify Vtotal'", stHVtotal.usDVtotal);
            }
        }
    }
#endif
    // Dclk_max_spread < Dclk_min_spread, not make sense!
    if(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD() > GET_PANEL_PIXEL_CLOCK_MIN_SPREAD())
    {
        // If DClk Out of Panel Spec => Try Modifying DHTotal
        if((ulDclk > ulPanelClockMaxSpread) || (ulDclk < ulPanelClockMinSpread))
        {
            stDHtotalFTStatus = ScalerMDomainDHtotalFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread);

            stHVtotal.usDHtotal = stDHtotalFTStatus.usDHtotal;

#if(_FRC_SUPPORT == _ON)
            // Calculate Target Dclk
            ulDclkNew = GET_DWORD_MUL_DIV(ulDclk, stHVtotal.usDHtotal, GET_MDOMAIN_OUTPUT_HTOTAL());

            // Check Dclk
            if(bDclkCalculateMethod == _FRAME_BUFFER_METHOD)
            {
                if(((ucMemorySel == _FRAME_SYNC_MEMORY) ||
                    (ucMemorySel == _MN_FRAME_SYNC_MEMORY) ||
                    (ScalerMDomainCheckMTPFreerunFinetune() == _TRUE)) &&
                   ((ulDclkNew > ulPanelClockMaxSpread) || (ulDclkNew < ulPanelClockMinSpread)))
                {
                    if(ulDclkNew > ulPanelClockMaxSpread)
                    {
                        // Calculate Target DVTotal
                        stHVtotal.usDVtotal = GET_DWORD_MUL_DIV(_PANEL_DV_TOTAL, ulPanelClockMaxSpread, ulDclkNew);
                        stHVtotal.usDVtotal = ((stHVtotal.usDVtotal < _PANEL_DV_TOTAL_MIN) ? _PANEL_DV_TOTAL_MIN : stHVtotal.usDVtotal);
                        DebugMessageScaler("FS fine tune, Dclk larger than panel spec => Modify Vtotal'", stHVtotal.usDVtotal);
                    }
                    else
                    {
                        // Calculate Target DVTotal, current DVtotal add 1 for last line
                        stHVtotal.usDVtotal = GET_DWORD_MUL_DIV((_PANEL_DV_TOTAL + 1), ulPanelClockMinSpread, ulDclkNew) + 1;
                        stHVtotal.usDVtotal = ((stHVtotal.usDVtotal > _PANEL_DV_TOTAL_MAX) ? _PANEL_DV_TOTAL_MAX : stHVtotal.usDVtotal);
                        DebugMessageScaler("FS fine tune, Dclk smaller than panel spec => Modify Vtotal'", stHVtotal.usDVtotal);
                    }
                }
            }
#else
            bDclkCalculateMethod = bDclkCalculateMethod;
#endif // End of #if(_FRC_SUPPORT == _ON)
        }
    }
    else
    {
        DebugMessageFS("[WARNING] GET_PANEL_PIXEL_CLOCK_MAX_SPREAD() < GET_PANEL_PIXEL_CLOCK_MIN_SPREAD(), check Dclk range of panel spec!!!", 0);
    }

    return stHVtotal;
}

//--------------------------------------------------
// Description  : Special Double Buffer Apply Procedure for FS
// Input Value  : None
// Output Value : None
// Note : Only for Frame Sync case
//--------------------------------------------------
void ScalerMDomainFSVgipDoubleBufferApply(void)
{
    bit bFreeRunEn = _FALSE;

    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        // Avoid (Current_IVStart + IVHeight) > IVToal + New_IVSDelay in digital capture
        PDATA_WORD(0) = (GET_INPUT_TIMING_VSTART() + ScalerVgipGetCaptureVStartPosition() + GET_MDOMAIN_INPUT_VHEIGHT());
    }
    else
    {
        // Avoid (Current_IVSDelay + IVStart + IVHeight) > IVToal + New_IVSDelay in analog capture
        PDATA_WORD(0) = (ScalerVgipGetCaptureVDelay() + ScalerVgipGetCaptureVStartPosition() + GET_MDOMAIN_INPUT_VHEIGHT());
    }

    bFreeRunEn = (PDATA_WORD(0) > GET_MDOMAIN_INPUT_VTOTAL()) ? (_TRUE) : (_FALSE);

    if(bFreeRunEn == _TRUE)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

        // Set Free run
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

#if(_FRC_SUPPORT == _ON)
        // Disable MN tracking
        ScalerMemorySetFrameTrackingEnable(_DISABLE);
#endif
    }

    ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

#if(_FRC_SUPPORT == _ON)
    if(GET_FRC_CAP_EN_RESET() == _TRUE)
    {
        // Reset FRC Cap enable
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
    }
#endif

    if(bFreeRunEn == _TRUE)
    {
#if(_FRC_SUPPORT == _ON)
        if(GET_MEMORY_DVF_SELECT() == _1_IVF)
#endif
        {
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

            // Set Frame sync
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
        }
#if(_FRC_SUPPORT == _ON)
        else
        {
            WORD usFramesyncDVtotal = 0;
            WORD usFreerunDVtotal = 0;
            BYTE ucNframe = 0;

            if((GET_MEMORY_DVF_SELECT() == _2_IVF) || (GET_MEMORY_DVF_SELECT() == _3_IVF))
            {
                ucNframe = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE);

                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                while(ucNframe > 0)
                {
                    ucNframe --;
                    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                }
                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
                ScalerMemorySetFrameTrackingEnable(_ENABLE);
            }
            else if(GET_MEMORY_DVF_SELECT() == _2_5_IVF)
            {
                // Measure DVtotal in current mode
                ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, _BIT5);
                ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

                // Get N frame
                ucNframe = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE);

                // Get free run DVtotal
                usFreerunDVtotal = GET_FREE_RUN_DVTOTAL();

                ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                usFramesyncDVtotal = ScalerMDomainGetDVtotalLastline();

                if(usFramesyncDVtotal < (usFreerunDVtotal * 7 / 10))
                {
                    while(ucNframe > 0)
                    {
                        ucNframe --;
                        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                    }
                }
                else
                {
                    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                }

                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
                ScalerMemorySetFrameTrackingEnable(_ENABLE);
                ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
            }
        }
#endif // End of #if(_FRC_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Dtotal, Lastline
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenDHTotalLastline(WORD usHTotal)
{
#if((_GOSD_SUPPORT == _ON) && ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
    ScalerGosdDispOsdDisplayDisableWithBackup();
#endif

    PDATA_WORD(0) = usHTotal - (usHTotal % _PANEL_DHTOTAL_MULTIPLE);

    // Set Last line for free run
    SET_FREE_RUN_LAST_LINE(PDATA_WORD(0));

    // Set DHtotal
    ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL, PDATA_WORD(0));

#if((_GOSD_SUPPORT == _ON) && ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
    ScalerGosdDispOsdDisplayEnableByBackup();
#endif
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Hsync & Vsync Width
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenHVSyncWidth(WORD usDHSync, WORD usDVSync)
{
    // Set H sync width, must by 2x in even-odd-mode
    ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_HS_WIDTH, (usDHSync + usDHSync % 2));

    // Set V sync height
    ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_VS_WIDTH, usDVSync);
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Dtotal, Background
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenBackground(EnumDisplayRegion enumDisplayRegion)
{
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);

    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A2:
#endif
        default:
            ScalerMDomainSetBackground_R1();
            break;

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A1:
        case _DDOMAIN_RGN_R2_A2:
            ScalerMDomainSetBackground_R2();
            break;
#endif


#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A1:
        case _DDOMAIN_RGN_R3_A2:
            ScalerMDomainSetBackground_R3();
            break;
#endif
    }
}

//--------------------------------------------------
// Description  : Get Current Frame Sync mode setting (P0_28[3])
// Input Value  : None
// Output Value : _FRAME_SYNC_MODE or _FREE_RUN_MODE
//--------------------------------------------------
EnumFrameSyncModeType ScalerMDomainGetFrameSyncMode(void)
{
    if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT3) == _BIT3)
    {
#if(_FRC_SUPPORT == _ON)
        if(ScalerMemoryGetFrameTrackingEnable() == _ENABLE)
        {
            return _MN_FRAME_SYNC_MODE;
        }
        else
#endif
        {
            return _FRAME_SYNC_MODE;
        }
    }
    else
    {
        return _FREE_RUN_MODE;
    }
}

//--------------------------------------------------
// Description  : Frame Sync switch to Free Run Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainFrameSyncSwitchtoFreeRunMode(void)
{
    if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
    {
        // Set free run mode
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Main background timing format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetBackground_R1(void)
{
    // Set R1 H background st/ ed (Panel size)
    ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START, GET_MDOMAIN_OUTPUT_HBSTART());
    ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END, (GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()));

    // Set R1 V background st/ ed (Panel size)
    ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START, GET_MDOMAIN_OUTPUT_VBSTART());
    ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END, (GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()));
}

//--------------------------------------------------
// Description  : Get min background timing format
// Input Value  : stTimingInfo --> timing format index
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetBackground_R1(StructTimingFormat *pstTimingFormat)
{
    // Get H background start/end
    pstTimingFormat->usHStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START);
    pstTimingFormat->usHWidth = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH);

    // Get V background start/end
    pstTimingFormat->usVStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);
    pstTimingFormat->usVHeight = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT);
}

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetBackground_R2(void)
{
    // Set R2 H background st/ ed (Panel size)
    ScalerDDomainSetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_START, GET_MDOMAIN_OUTPUT_HBSTART());
    ScalerDDomainSetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_END, (GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()));

    // Set R2 V background st/ ed (Panel size)
    ScalerDDomainSetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START, GET_MDOMAIN_OUTPUT_VBSTART());
    ScalerDDomainSetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_END, (GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()));
}

//--------------------------------------------------
// Description  : Get sub background timing format
// Input Value  : stTimingInfo --> timing format index
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetBackground_R2(StructTimingFormat *pstTimingFormat)
{
    // Get H background start/end
    pstTimingFormat->usHStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_START);
    pstTimingFormat->usHWidth = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_H_WIDTH);

    // Get V background start/end
    pstTimingFormat->usVStart = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_START);
    pstTimingFormat->usVHeight = ScalerDDomainGetDisplayBackground_R2(_DISPLAY_BACKGROUND_V_HEIGHT);
}

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get sub background timing format
// Input Value  : stTimingInfo --> timing format index
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetActiveRegion_R2a1(StructTimingFormat *pstTimingFormat)
{
    // Get H background start/end
    pstTimingFormat->usHStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START);
    pstTimingFormat->usHWidth = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_WIDTH);

    // Get V background start/end
    pstTimingFormat->usVStart = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START);
    pstTimingFormat->usVHeight = ScalerDDomainGetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_HEIGHT);
}
#endif
#endif

#if(_HW_D_DOMAIN_R3_BACKGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetBackground_R3(void)
{
    // Set R3 H background st/ ed (Panel size)
    ScalerDDomainSetDisplayBackground_R3(_DISPLAY_BACKGROUND_H_START, GET_MDOMAIN_OUTPUT_HBSTART());
    ScalerDDomainSetDisplayBackground_R3(_DISPLAY_BACKGROUND_H_END, (GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()));

    // Set R3 V background st/ ed (Panel size)
    ScalerDDomainSetDisplayBackground_R3(_DISPLAY_BACKGROUND_V_START, GET_MDOMAIN_OUTPUT_VBSTART());
    ScalerDDomainSetDisplayBackground_R3(_DISPLAY_BACKGROUND_V_END, (GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()));
}

//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : stTimingInfo --> timing format index
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetBackground_R3(StructTimingFormat *pstTimingFormat)
{
    // Get H background start/end
    pstTimingFormat->usHStart = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_H_START);
    pstTimingFormat->usHWidth = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_H_WIDTH);

    // Get V background start/end
    pstTimingFormat->usVStart = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_V_START);
    pstTimingFormat->usVHeight = ScalerDDomainGetDisplayBackground_R3(_DISPLAY_BACKGROUND_V_HEIGHT);
}
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetActiveRegion_R2a2(void)
{
    // Set R2a2 H Active st/ ed (Panel size)
    ScalerDDomainSetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_START, GET_MDOMAIN_OUTPUT_HSTART());
    ScalerDDomainSetDisplayFormat_R2a2(_DISPLAY_FORMAT_H_END, (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

    // Set R2a2 V Active st/ ed (Panel size)
    ScalerDDomainSetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_START, GET_MDOMAIN_OUTPUT_VSTART());
    ScalerDDomainSetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_END, (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
}
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set sub active region format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetActiveRegion_R2a1(void)
{
    // Set R2a1 H Active Start / End
    ScalerDDomainSetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_START, GET_MDOMAIN_OUTPUT_HSTART());
    ScalerDDomainSetDisplayFormat_R2a1(_DISPLAY_FORMAT_H_END, (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

    // Set R2a1 V Active Start / End
    ScalerDDomainSetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_START, GET_MDOMAIN_OUTPUT_VSTART());
    ScalerDDomainSetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END, (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
}
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetActiveRegion_R3a2(void)
{
    // Set R2a2 H Active st/ ed (Panel size)
    ScalerDDomainSetDisplayFormat_R3a2(_DISPLAY_FORMAT_H_START, GET_MDOMAIN_OUTPUT_HSTART());
    ScalerDDomainSetDisplayFormat_R3a2(_DISPLAY_FORMAT_H_END, (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

    // Set R2a2 V Active st/ ed (Panel size)
    ScalerDDomainSetDisplayFormat_R3a2(_DISPLAY_FORMAT_V_START, GET_MDOMAIN_OUTPUT_VSTART());
    ScalerDDomainSetDisplayFormat_R3a2(_DISPLAY_FORMAT_V_END, (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
}
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set sub active region format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetActiveRegion_R3a1(void)
{
    // Set R2a1 H Active Start / End
    ScalerDDomainSetDisplayFormat_R3a1(_DISPLAY_FORMAT_H_START, GET_MDOMAIN_OUTPUT_HSTART());
    ScalerDDomainSetDisplayFormat_R3a1(_DISPLAY_FORMAT_H_END, (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

    // Set R2a1 V Active Start / End
    ScalerDDomainSetDisplayFormat_R3a1(_DISPLAY_FORMAT_V_START, GET_MDOMAIN_OUTPUT_VSTART());
    ScalerDDomainSetDisplayFormat_R3a1(_DISPLAY_FORMAT_V_END, (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
}
#endif

//--------------------------------------------------
// Description  : Set Display Timing Gen V Active End
// Input Value  : D domain region, Vactive end
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetDisplayVerticalActiveEnd(EnumDDomainRegion enumDDomainRegion, WORD usVactiveEnd)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            // Set R1a1 V Active End
            ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END, usVactiveEnd);
            break;

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A2:
            // Set R1a2 V Active End
            ScalerDDomainSetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END, usVactiveEnd);
            break;
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A1:
            // Set R2a1 V Active End
            ScalerDDomainSetDisplayFormat_R2a1(_DISPLAY_FORMAT_V_END, usVactiveEnd);
            break;
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A2:
            // Set R2a2 Active End
            ScalerDDomainSetDisplayFormat_R2a2(_DISPLAY_FORMAT_V_END, usVactiveEnd);
            break;
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A1:
            // Set R3a1 V Active End
            ScalerDDomainSetDisplayFormat_R3a1(_DISPLAY_FORMAT_V_END, usVactiveEnd);
            break;
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A2:
            // Set R3a2 Active End
            ScalerDDomainSetDisplayFormat_R3a2(_DISPLAY_FORMAT_V_END, usVactiveEnd);
            break;
#endif
    }
}

//--------------------------------------------------
// Description  : Select memory confirm
// Input Value  : NA
// Output Value : free run/ frame sync line buffer/ frame sync frame buffer / MN frame sync/ free run no input
//--------------------------------------------------
EnumMemoryConfig ScalerMDomainMemorySelectConfirm(void)
{
#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
    return _FRAME_SYNC_MEMORY;
#endif

    switch(GET_MEMORY_WORK_TYPE())
    {
        case _LINE_BUFFER_MODE:

            return _FRAME_SYNC_LINE_BUFFER;

#if(_FRC_SUPPORT == _ON)
        case _MEMORY_WORK_MODE:

            if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
            {
                switch(GET_MEMORY_DVF_SELECT())
                {
                    case _1_IVF:

                        return _FRAME_SYNC_MEMORY;

                    case _3_IVF:
                    case _2_5_IVF:
                    case _2_IVF:
                        return _MN_FRAME_SYNC_MEMORY;

                    default:
                    case _PANEL_TYP_FRAME_RATE_FREE_RUN:

                        return _FREE_RUN_MEMORY;
                }
            }
            else
            {
                return _FREE_RUN_MEMORY;
            }
#endif

        default:

            return _FRAME_SYNC_LINE_BUFFER;
    }
}

//--------------------------------------------------
// Description  : Set Memory Data Bit
// Input Value  : ucColorDepth
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth)
{
#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
    ucColorDepth = ucColorDepth;
    SET_MEMORY_DATA_BIT(_COLOR_DEPTH_12_BITS * 3);
#else
    if((ucColorDepth * 3) >= _HW_M_DOMAIN_DATA_BIT_MAX)
    {
        SET_MEMORY_DATA_BIT(_HW_M_DOMAIN_DATA_BIT_MAX);
    }
    else
    {
        SET_MEMORY_DATA_BIT(_COLOR_DEPTH_8_BITS * 3);
    }
#endif
}

//--------------------------------------------------
// Description  : Calculate I/D domain V adjust limitation
// Input Value  : input source type
// Output Value : vertical adjust limit for IV delay
//--------------------------------------------------
WORD ScalerMDomainGetVerticalAdjustLimit(EnumSourceType enumSourceType)
{
    WORD usAdjustLimit = 0x0001;

    enumSourceType = enumSourceType;

    // Calculate I-domain limitation; Safe New V-Delay value must larger than DEN falling edge position plus 3 lines
#if(_VGA_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_VGA)
    {
        if(GET_INPUT_TIMING_VTOTAL() > (GET_INPUT_TIMING_VHEIGHT() + ScalerVgaTopGetCaptureVStartPosition() + 3))
        {
            usAdjustLimit = GET_INPUT_TIMING_VTOTAL() - (GET_INPUT_TIMING_VHEIGHT() + ScalerVgaTopGetCaptureVStartPosition() + 3);
        }
    }
    else
#endif
    {
        if(GET_INPUT_TIMING_VTOTAL() > (GET_INPUT_TIMING_VHEIGHT() + ScalerVgipGetCaptureVStartPosition() + 3))
        {
            usAdjustLimit = GET_INPUT_TIMING_VTOTAL() - (GET_INPUT_TIMING_VHEIGHT() + ScalerVgipGetCaptureVStartPosition() + 3);
        }
    }

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
#if((_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_VBO))

        // Check D-domain limitation only for 1P mode and non-free-run case
        if(GET_MEMORY_CONFIG_SELECT() != _FREE_RUN_MEMORY)
        {
            // Calculate D-domain limitation
            WORD usDdomainLimit = (WORD)((DWORD)(GET_MDOMAIN_OUTPUT_VTOTAL() - GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_MDOMAIN_OUTPUT_VSTART()) * GET_MDOMAIN_INPUT_VTOTAL() / GET_MDOMAIN_OUTPUT_VTOTAL() - 1);

            if(usDdomainLimit < usAdjustLimit)
            {
                usAdjustLimit = usDdomainLimit;
            }

#if(_FRC_SUPPORT == _ON)
            // Update adjust limit for MN tracking
            if(GET_MEMORY_CONFIG_SELECT() == _MN_FRAME_SYNC_MEMORY)
            {
                switch(GET_MEMORY_DVF_SELECT())
                {
                    case _3_IVF:
                        usAdjustLimit /= 3;
                        break;

                    case _2_5_IVF:
                        usAdjustLimit = (usAdjustLimit * 2 / 5);

                        // For 2 successive IVS
                        usAdjustLimit /= 2;
                        break;

                    case _2_IVF:
                        usAdjustLimit /= 2;
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_FRC_SUPPORT == _ON)

            // Keep at least one line for adjusting V-Position; otherwise take 2 lines as margin
            if(usAdjustLimit < 0x0003)
            {
                usAdjustLimit = 0x0001;
            }
            else
            {
                usAdjustLimit -= 0x0002;
            }
        }
#endif

        // Avoid Lost Frame-Sync DVS
        if(GET_MEMORY_DVF_SELECT() == _1_IVF)
        {
            WORD usIvs2dvsDelay = ((((WORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) & 0x01F) << 8) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L));
            WORD usIvs2dvsDelayLimit = 0;
            WORD usIvDelay = 0;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                usIvs2dvsDelay = usIvs2dvsDelay << 1;
            }
#endif

#if(_VGA_SUPPORT == _ON)
            if(enumSourceType == _SOURCE_VGA)
            {
                usIvDelay = ScalerVgaTopGetCaptureVDelay();
            }
            else
#endif
            {
                usIvDelay = ScalerVgipGetCaptureVDelay();
            }

            // Check IVS_Delay change from larger to smaller
            if((GET_INPUT_TIMING_VTOTAL() - usIvDelay) < (usIvs2dvsDelay + 4)) // 4 line margin
            {
                usIvs2dvsDelayLimit = ((usIvs2dvsDelay + 4) - (GET_INPUT_TIMING_VTOTAL() - usIvDelay));

                if(usIvDelay > usIvs2dvsDelayLimit)
                {
                    usIvs2dvsDelayLimit = usIvDelay - usIvs2dvsDelayLimit;

                    if(usIvs2dvsDelayLimit < usAdjustLimit)
                    {
                        usAdjustLimit = usIvs2dvsDelayLimit;
                    }
                }
            }
        }
    }

    DebugMessageScaler("V adj. limit", usAdjustLimit);

    return usAdjustLimit;
}

//--------------------------------------------------
// Description  : Measure Display Active Region in Display Setting
// Input Value  : void
// Output Value : Display Avtive Region
//--------------------------------------------------
DWORD ScalerMDomainGetDisplayActiveRegion(void)
{
    bit bChangeDVStartStatus = _FALSE;
    DWORD ulDisplayActiveRegion = 0;

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    if(ScalerMemoryCheckScreenCoverStatus() == _TRUE)
    {
        bChangeDVStartStatus = _TRUE;
    }
    else
#endif
    {
#if(_DRR_SUPPORT == _ON)
        if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
        {
            bChangeDVStartStatus = _TRUE;
        }
        else
#endif
        {
            WORD usDVTotal = 0;
            WORD usIvs2dvsDelay = 0;

            // Measure DVtotal in frame sync mode
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

            // Get DVTotal Result
            usDVTotal = ScalerMDomainGetDVtotalLastline();

            // Get Ivs2dvsdelay
            usIvs2dvsDelay = ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) / GET_MDOMAIN_INPUT_HTOTAL() * GET_MDOMAIN_OUTPUT_VHEIGHT() / GET_MDOMAIN_INPUT_VHEIGHT();

            DebugMessageFS("usIvs2dvsDelay", usIvs2dvsDelay);
            DebugMessageFS("DVT", usDVTotal);
            DebugMessageFS("DVS", GET_MDOMAIN_OUTPUT_VSTART());

            // Check DVT < Ivs2dvsdelay + DVStart + DVHeigth
            bChangeDVStartStatus = ((usDVTotal < (usIvs2dvsDelay + GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT() + 2)) ? (_TRUE) : (_FALSE)); // 2 line margin
        }
    }

    if(bChangeDVStartStatus == _TRUE)
    {
        // Set Main1 VHeight / 2
        ScalerMDomainSetDisplayVerticalActiveEnd(GET_MDOMAIN_OUTPUT_RGN(), (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT() / 2));

        // Apply DB
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);
    }

    // Set Measure Display Active Region
    ScalerMeasureSetDisplayRegionCount(GET_MDOMAIN_OUTPUT_RGN(), _ACTIVE_REGION_TYPE);

    // Read Active Region Result
    ulDisplayActiveRegion = ScalerMeasureGetDisplayRegionCountResult(_WAIT);

    if(bChangeDVStartStatus == _TRUE)
    {
        DWORD ulHalfPixel = 0;
        DWORD ulWholePixel = 0;

        // Half-frame-pixel
        ulHalfPixel = ScalerMeasureGetdActiveRegionPixels(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_OUTPUT_HWIDTH(), (GET_MDOMAIN_OUTPUT_VHEIGHT() / 2), GET_MDOMAIN_OUTPUT_HTOTAL());

        // Whole-frame-pixel
        ulWholePixel = ScalerMeasureGetdActiveRegionPixels(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_OUTPUT_HWIDTH(), GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_OUTPUT_HTOTAL());

        // Calculate full-frame count = half-frame count * Whole-frame-pixel / Half-frame-pixel
        ulDisplayActiveRegion = GET_DWORD_MUL_DIV(ulDisplayActiveRegion, ulWholePixel, ulHalfPixel);

        // Set Main1 V Active st/ ed
        ScalerMDomainSetDisplayVerticalActiveEnd(GET_MDOMAIN_OUTPUT_RGN(), (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));

        // Apply DB
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);
    }

    DebugMessageFS("bChangeDVStartStatus", bChangeDVStartStatus);

    return ulDisplayActiveRegion;
}

//--------------------------------------------------
// Description  : Check Display Timing Gen
// Input Value  : None
// Output Value : TRUE: Pass
//--------------------------------------------------
bit ScalerMDomainDisplayTimingGenCheck(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DRR_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE) &&
       ((GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER) || (GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)))
    {
        WORD usDVtotal = 0;

        // Measure DVtotal in frame sync mode
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

        usDVtotal = ScalerMDomainGetDVtotalLastline();
        SET_MDOMAIN_OUTPUT_VTOTAL(usDVtotal);

        // Check DV_BG_End > DVtotal
        if((GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()) > GET_MDOMAIN_OUTPUT_VTOTAL())
        {
            DebugMessageScaler("DVBG end > DVtotal", usDVtotal);
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : M domain use Color Depth
//--------------------------------------------------
BYTE ScalerMDomainGetColorDepth(void)
{
    return (GET_MEMORY_DATA_BIT() / 3);
}

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerMDomainAspectOriginMode(bit bOn)
{
    SET_ASPECT_ORIGIN_MODE(bOn);
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get maximum bandwidth for current path
// Input Value  : None
// Output Value : Maximum bandwidth
//--------------------------------------------------
DWORD ScalerMDomainGetCurBW(void)
{
    switch(GET_DISPLAY_MODE())
    {
        default: // 1P, _DISPLAY_MODE_2P_PBP_TB, _DISPLAY_MODE_4P
            return GET_FRC_MAIN_BW();

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            // PBP_LR_R_LARGE   fb 6829 / eo 6952 Right=R1, eo 6829/6978 Right=R2
            if(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT) == _DDOMAIN_RGN_R2_A1)
            {
                return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
            }
            else
            {
                return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R2_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
            }
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R2_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();

        case _DISPLAY_MODE_3P_SKEW_R:
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R2_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A1) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();

        case _DISPLAY_MODE_3P_SKEW_B:
            return (GET_MDOMAIN_OUTPUT_RGN() == _DDOMAIN_RGN_R1_A2) ? GET_FRC_MAIN_BW() : GET_FRC_SUB_BW();
#endif
    }
}

//--------------------------------------------------
// Description  : Get reserved BW for OD
// Input Value  : ODUseBit10x (unit: 0.1 bit)
// Output Value : Current region's reserved BW for OD
//--------------------------------------------------
WORD ScalerMDomainGetCurODReservedBW(BYTE ucODBit10x, StructMemoryBWUsageParam *pstMemBWParam)
{
    WORD usODTotalBW = 0;
    ucODBit10x = ucODBit10x;
    pstMemBWParam = pstMemBWParam;

#if(_OD_FUNCTION == _OFF)

    return usODTotalBW;

#else // _OD_SUPPORT == _ON

    if(ucODBit10x == _OFF)
    {
        return 0;
    }

    usODTotalBW = ScalerMDomainODCalculateMemoryUseBW(ucODBit10x, pstMemBWParam);

    switch(pstMemBWParam->enumDisplayMode)
    {
        default: // [1P]
            return usODTotalBW;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            // [PIP] ((Main) ? (Variable BW usage) : (Fixed BW usage))
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R1_A1) ? usODTotalBW : 0);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#if(_2P_PBP_LR_PERFORMANCE_TYPE == _MAIN_EQUAL_TO_SUB)
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R1_A1) ? ((DWORD)usODTotalBW * GET_FRC_MAIN_BW() / GET_MEMORY_FRC_OD_BW()) : ((DWORD)usODTotalBW * GET_FRC_SUB_BW() / GET_MEMORY_FRC_OD_BW()));
#else
            if(GET_FRC_MAIN_BW() == GET_FRC_SUB_BW())
            {
                // [PBP LR] BW usage is variable on each P
                return (usODTotalBW / 2);
            }
            else
            {
                return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R1_A1) ? usODTotalBW : 0);
            }
#endif
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            // [PBP TB] BW usage is variable on each P
            return (usODTotalBW / 2);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            // [4P] BW usage is variable on each P
            return (usODTotalBW / 4);
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            // [3P flag] ((Main) ? (Variable BW usage) : (Fixed BW usage))
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R2_A2) ? usODTotalBW : 0);
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
            // [5K 3P_skew_L/T] ((Main) ? (Variable BW usage) : (Fixed BW usage))
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R1_A1) ? usODTotalBW : 0);


        case _DISPLAY_MODE_3P_SKEW_R:
            // [5K 3P_skew_R] ((Main) ? (Variable BW usage) : (Fixed BW usage))
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R2_A1) ? usODTotalBW : 0);
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
            // [5K 3P_skew_L/T] ((Main) ? (Variable BW usage) : (Fixed BW usage))
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R1_A1) ? usODTotalBW : 0);

        case _DISPLAY_MODE_3P_SKEW_B:
            // [5K 3P_skew_B] ((Main) ? (Variable BW usage) : (Fixed BW usage))
            return ((pstMemBWParam->enumMDomainOutputRgn == _DDOMAIN_RGN_R1_A2) ? usODTotalBW : 0);
#endif
    }

#endif // End of (_OD_SUPPORT == _ON)

}
#endif

#if((_FRC_SUPPORT == _ON) || (_OD_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Fetch MDomain IO infos for BW usage calculation
// Input Value  : Memory BW usage parameter
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetMemBWParam(StructMemoryBWUsageParam *pstMemBWParam)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerMDomainGetInputPathCount(GET_MDOMAIN_INPUT_DATA_PATH()) == _INPUT_PATH_4)
    {
        pstMemBWParam->ucFBCoopEn = _TRUE;
    }
    else
#endif
    {
        pstMemBWParam->ucFBCoopEn = _FALSE;
    }
    pstMemBWParam->ulIHFreq = (DWORD)GET_MDOMAIN_INPUT_HFREQ() * 1000;
    pstMemBWParam->ulDHFreq = GET_DWORD_MUL_DIV((DWORD)GET_D_CLK_FREQ(), 10000, GET_MDOMAIN_OUTPUT_HTOTAL());
    pstMemBWParam->enumDisplayMode = GET_DISPLAY_MODE();
    pstMemBWParam->enumDVFSelect = GET_MEMORY_DVF_SELECT();
    pstMemBWParam->enumMDomainOutputRgn = GET_MDOMAIN_OUTPUT_RGN();
}
#endif

#if(_OD_FUNCTION == _ON)
//--------------------------------------------------
// Description  : If memory is not enough for OD, disable OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainODConfig(void)
{
    DWORD ulRemainSpaseInRow = ((GET_OD_END_ADDRESS() - GET_OD_START_ADDRESS()) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);

    CLR_OD_USE_PARAM();

    // Check available OD use bit
    SET_OD_USE_PARAM(ScalerODGetParamSet(ulRemainSpaseInRow, GET_MEMORY_REMAIN_BW()));

#if(_FRC_SUPPORT == _ON)
    if(GET_MEMORY_WORK_TYPE() == _MEMORY_WORK_MODE)
    {
        DebugMessageFRC("4. FRC used BW", GET_MEMORY_BW(GET_MDOMAIN_INPUT_DATA_PATH()));
        DebugMessageFRC("4. FRC remaining BW2", GET_MEMORY_REMAIN_BW());
    }
#endif

    DebugMessageFRC("4.(GET_OD_USE_BIT())", (GET_OD_USE_BIT()));
}

//--------------------------------------------------
// Description  : OD flags initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainODFlagInitial(void)
{
    CLR_OD_USE_PARAM();
    CLR_OD_TABLE_VALID_STATUS();
}

//--------------------------------------------------
// Description  : Calculate memory use space
// Input Value  : ODUseBit10x (unit: 0.1 bit)
// Output Value : OD memory use space, unit:row
//--------------------------------------------------
WORD ScalerMDomainODCalculateMemoryUseSpace(BYTE ucODBit10x)
{
    WORD usODUseSpacePerPathInRow =
        ScalerODGetMemoryUsagePerPath(ucODBit10x) /
        _FW_MEM_CLIENT_MEMORY_BIT_NUM /
        (_MEMORY_COL_PER_BANK * _MEMORY_BANK) +
        _OD_PATH_MEMORY_SPACE_ROW_MARGIN;

    WORD usODUseSpaceTotalInRow =
        usODUseSpacePerPathInRow *
        _OD_PATH_WIDTH_DIVISOR *
        _OD_PATH_HEIGHT_DIVISOR;

#if(_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _FALSE)
    // Memory clients are assigned to two memory device.
    ulODUseSpaceTotalInRow /= 2;
#endif

    // OD memory size (per memory device), unit : row
    return usODUseSpaceTotalInRow;
}

//--------------------------------------------------
// Description  : Calculate memory use BW
// Input Value  : ODUseBit10x (unit: 0.1 bit), M-domain parameter
// Output Value : OD memory use BW, unit:100k
//--------------------------------------------------
WORD ScalerMDomainODCalculateMemoryUseBW(BYTE ucODBit10x, StructMemoryBWUsageParam *pstMemBWParam)
{
    WORD usOdWidth = 0;
    WORD usBGHwidth = _PANEL_DH_WIDTH;
    DWORD ulOdUsedBw = 0;

#if(_PANEL_ASYMMETRIC == _ON)
    usBGHwidth += _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT + _PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT;
#endif

    // OD effective total width considering path width padding.
    usOdWidth = CEILING((usBGHwidth / _OD_PATH_WIDTH_DIVISOR), _OD_PIXEL_PER_COMP) * _OD_PATH_WIDTH_DIVISOR;

    // Write or Read (unit: 10)
    ulOdUsedBw = GET_DWORD_MUL_DIV(((DWORD)usOdWidth * ucODBit10x), (pstMemBWParam->ulDHFreq), ((DWORD)_MEMORY_BUS_WIDTH * 10 * 10 * 10));
    ulOdUsedBw += GET_DWORD_MUL_DIV(ulOdUsedBw, (((WORD)_DCLK_SPREAD_RANGE / _PANEL_DPLL_SSCG_DIV_MODE) + _DCLK_SPREAD_RANGE_MARGIN), ((WORD)4 * 100));

    // Write + Read
    ulOdUsedBw *= 2;

    ulOdUsedBw = CEILING_OF_INT_DIVISION(ulOdUsedBw, 10000); // unit:100k

#if(_FRC_SUPPORT == _ON)
    if(GET_DYNAMIC_OD_STATUS(pstMemBWParam->enumDisplayMode, pstMemBWParam->enumDVFSelect) == _ENABLE)
    {
        ulOdUsedBw /= 2;
    }
#endif

    DebugMessageFRC("4.OD use BW", ulOdUsedBw);

    return (WORD)ulOdUsedBw;
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset bandwidth
// Input Value  : EnumInputDataPath : Input path
// Output Value : void
//--------------------------------------------------
void ScalerMDomainReleaseFRCMemoryBW(EnumInputDataPath enumInputPath)
{
    DebugMessageFRC("4. FRC BW Reset path", enumInputPath);

    if(enumInputPath == _INPUT_PATH_NONE)
    {
        SET_MEMORY_REMAIN_BW(GET_MEMORY_FRC_OD_BW()); // unit:100k
        memset(g_pstMDomainFRCInfo, 0, sizeof(g_pstMDomainFRCInfo));
    }
    else
    {
        // Release FRC bandwidth
        CLR_PATH_MEMORY_BW_CONFIG(enumInputPath);
        ScalerFRCUpdateCurrentBW();

        // Check available OD param set
        SET_OD_USE_PARAM(ScalerODGetParamSet(((GET_OD_END_ADDRESS() - GET_OD_START_ADDRESS()) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM), GET_MEMORY_REMAIN_BW()));

        DebugMessageFRC("4. FRC remaining BW1", GET_MEMORY_REMAIN_BW());
        DebugMessageFRC("4. OD bit", GET_OD_USE_BIT());
    }
}
#endif // End of #if(_FRC_SUPPORT == _ON)
#endif // End of #if(_OD_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Dtotal, Background, Diaplay active region
// Input Value  : display data path
// Output Value : _TRUE: need to set D Domain DB apply
//--------------------------------------------------
bit ScalerMDomainSetDisplayTimingGen(EnumDDomainRegion enumDDomainRegion)
{
    WORD usVBackStartOld = 0;
    WORD usVHeightOld = 0;
    WORD usHStartOld = 0;

    usVBackStartOld = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);
    usVHeightOld = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);
    usHStartOld = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START);

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
    g_usOsdTgDBCurDdmVSta = usVBackStartOld;
    g_usOsdTgDBCurDdmVEnd = usVBackStartOld + usVHeightOld;
#endif

    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        // Set H sync width, must by 2x in even-odd-mode
        ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_HS_WIDTH, (_PANEL_DH_SYNC_WIDTH + _PANEL_DH_SYNC_WIDTH % 2));

        // Set V sync height
        ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_VS_WIDTH, GET_MDOMAIN_OUTPUT_VSYNCHEIGHT());

        // Set Main H background st/ ed (Panel size)
        ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START, GET_MDOMAIN_OUTPUT_HBSTART());
        ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_END, (GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()));

        // Set Main V background st/ ed (Panel size)
        ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START, GET_MDOMAIN_OUTPUT_VBSTART());
        ScalerDDomainSetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_END, (GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()));
    }

    // Set Main V background st/ ed (Panel size)
    ScalerMDomainSetDisplayTimingGenActiveRegion(enumDDomainRegion);

    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
        // Frame sync line buffer need to fine tune Dclk according I-active-region & D-active-region
        if((GET_MEMORY_CONFIG_SELECT() == _FREE_RUN_NO_INPUT) ||
           (usVBackStartOld != GET_MDOMAIN_OUTPUT_VBSTART()) ||
           (usHStartOld != GET_MDOMAIN_OUTPUT_HSTART()) ||
           ((usVHeightOld != GET_MDOMAIN_OUTPUT_VHEIGHT()) && (GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set current path memory frame buffer type
// Input Value  : Frame buffer type
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetMemoryFrameBuffer(BYTE ucType)
{
    switch (ucType)
    {
        default:
        case 0:
            SET_MEMORY_FRAME_BUFFER(_MEMORY_1_FRAME_BUFFER);
            break;

        case 1:
            SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
            break;

        case 2:
            SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
            break;

        case 3:
            SET_MEMORY_FRAME_BUFFER(_MEMORY_1_5_FRAME_BUFFER);
            break;
    }
}

//--------------------------------------------------
// Description  : Get M-domain output VFreq
// Input Value  : None
// Output Value : M-domain output VFreq
//--------------------------------------------------
WORD ScalerMDomainGetMDomainOutputVFreq(void)
{
    return GET_OUTPUT_VFREQ();
}

//--------------------------------------------------
// Description  : Get current path M-domain output HTotal
// Input Value  : None
// Output Value : current path M-domain output HTotal
//--------------------------------------------------
WORD ScalerMDomainGetMDomainOutputHTotal(void)
{
    return GET_MDOMAIN_OUTPUT_HTOTAL();
}

//--------------------------------------------------
// Description  : Set current path M-domain output VTotal
// Input Value  : VTotal
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetMDomainOutputVTotal(WORD usVTotal)
{
    SET_MDOMAIN_OUTPUT_VTOTAL(usVTotal);
}

//--------------------------------------------------
// Description  : Get EnumMemoryWorkMode
// Input Value  : DestMode, SrcMode
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetEnumMemoryWorkMode(BYTE *pucDestMode, BYTE ucSrcMode)
{
    switch(ucSrcMode)
    {
        default:
        case 0:
            *pucDestMode = _LINE_BUFFER_MODE;
            break;

        case 1:
            *pucDestMode = _MEMORY_WORK_MODE;
            break;
    }
}

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Display Format for FREESYNC OD measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void ScalerMDomainFreeSyncODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq)
{
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);
    ScalerGlobalDisableAllWatchDog();

    // Calculate FREESYNC DVtotal for OD measure
    PDATA_WORD(4) = (DWORD)ulDclk * 1000 / usDHtotal * 10 / usTarFreq;

    if(PDATA_WORD(4) < _PANEL_DV_TOTAL_MIN)
    {
        PDATA_WORD(4) = _PANEL_DV_TOTAL_MIN;
    }

    // DVtotal for WD setting
    PDATA_WORD(3) = PDATA_WORD(4) + 64;

    // Set Frame Sync Watch Dog
    SET_DIS_TIMING_GEN_WD_VTOTAL(PDATA_WORD(3));

    // Set DVtotal for free run
    SET_FREE_RUN_DVTOTAL(PDATA_WORD(4));

    // Set DHtotal and last line
    ScalerMDomainSetDisplayTimingGenDHTotalLastline(usDHtotal);

    SET_D_CLK_FREQ(ulDclk);

    // Set DClk
    ScalerPLLSetDPLLFreq(GET_D_CLK_FREQ());

    // Set Free Run Mode
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

    // Clear fifo flag
    ScalerMDomainClearStatus(GET_MDOMAIN_INPUT_DATA_PATH());

    // Clear Display Vsync timeout flag
    ScalerGlobalClrDvsTimeoutFlag();

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
}
#endif

//--------------------------------------------------
// Description  : Check memory
// Input Value  : None
// Output Value : Memory check pass or fail
//--------------------------------------------------
bit ScalerMDomainMemoryCheck(EnumInputDataPath enumInputDataPath)
{
    // Check fifo underflow and Input HVsync error flag, Display Vsync timeout flag
    if(ScalerGetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT0) != 0x00)
    {
        return _FALSE;
    }
    else
    {
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            EnumInputDataPath enumChkPath = GET_IDOMAIN_DATA_PATH(ucIndex);

            if((enumInputDataPath & enumChkPath) == enumChkPath)
            {
                BYTE ucIRQPageOffset = GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);
                BYTE ucOvfUdfOffset = GET_OVF_UDF_OFFSET(ucIndex);

                // Check fifo underflow and Input HVsync error flag, Display Vsync timeout flag
                if(ScalerGetBit(PC0_04_M1_OVF_UDF_CTRL + ucOvfUdfOffset, (_BIT1 | _BIT0)) != 0x00)
                {
                    return _FALSE;
                }

                if(ScalerGetBit(P0_A1_M1_IRQ_FLAG + ucIRQPageOffset, (_BIT4 | _BIT3)) != 0x00)
                {
                    return _FALSE;
                }

                return _TRUE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Diaplay active region
// Input Value  : display data path
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenActiveRegion(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
#if(_HW_D_DOMAIN_R1_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A1:
            ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_START, GET_MDOMAIN_OUTPUT_HSTART());
            ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_END, (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));
            ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_START, GET_MDOMAIN_OUTPUT_VSTART());
            ScalerDDomainSetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_END, (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
            break;
#endif

#if(_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R1_A2:
            ScalerDDomainSetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_START, GET_MDOMAIN_OUTPUT_HSTART());
            ScalerDDomainSetDisplayFormat_R1a2(_DISPLAY_FORMAT_H_END, (GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));
            ScalerDDomainSetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_START, GET_MDOMAIN_OUTPUT_VSTART());
            ScalerDDomainSetDisplayFormat_R1a2(_DISPLAY_FORMAT_V_END, (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
            break;
#endif

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A1:
            ScalerMDomainSetActiveRegion_R2a1();
            break;
#endif

#if(_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R2_A2:
            ScalerMDomainSetActiveRegion_R2a2();
            break;
#endif

#if(_HW_D_DOMAIN_R3_A1_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A1:
            ScalerMDomainSetActiveRegion_R3a1();
            break;
#endif

#if(_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON)
        case _DDOMAIN_RGN_R3_A2:
            ScalerMDomainSetActiveRegion_R3a2();
            break;
#endif

        default:
            break;
    }
}

#if(_DEBUG_MESSAGE_CHECK_MDOMAIN == _ON)
//--------------------------------------------------
// Description  : Get Display Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainCheckDisplaySetting(void)
{
    WORD usDVtotal = 0;
    WORD usDHtotal = 0;
    WORD usLastLine = 0;
    bit bDisplaySettingCheck = _FALSE;
#if((_OD_FUNCTION == _ON) || (_FRC_SUPPORT == _ON))
    WORD usBWUseEfficiency = 0;
    BYTE uccnt = 0;
#endif

    DebugMessageCheckMDomain("== DISP_CHECK_START ==", 0);

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) == _DRR_NONE_TYPE)
#endif
    {
        if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _FALSE) &&
           ((GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER) || (GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_MEMORY)))
        {
            bDisplaySettingCheck = _TRUE;
        }
    }

    if(bDisplaySettingCheck == _TRUE)
    {
        // Measure DVtotal in frame sync mode
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        usDVtotal = ScalerMDomainGetDVtotalLastline();
        usDHtotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL);
        DebugMessageCheckMDomain("DVtotal", usDVtotal);
        DebugMessageCheckMDomain("DHtotal", usDHtotal);

        // Pop out Last line
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
        usLastLine = ScalerMDomainGetDVtotalLastline();
        usLastLine = (usLastLine << GET_D_DOMAIN_PATH());
        DebugMessageCheckMDomain("LastLine", usLastLine);

#if(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
        if((DWORD)abs(_PANEL_LAST_LINE_TARGET - usLastLine) > (_PANEL_N_F_DPLL_PIXEL_PER_OFFSET * 2))
        {
            DebugMessageCheckMDomain("Measured last-line value away from _LAST_LINE_TARGET !!!", usLastLine);
        }

        if(((DWORD)abs(_PANEL_DH_TOTAL - _PANEL_LAST_LINE_TARGET) < (_PANEL_N_F_DPLL_PIXEL_PER_OFFSET * 2)) ||
           (_PANEL_LAST_LINE_TARGET < (_PANEL_N_F_DPLL_PIXEL_PER_OFFSET * 2)))
        {
            DebugMessageCheckMDomain("_LAST_LINE_TARGET too close to DHtotal boundary !!! Double check _LAST_LINE_TARGET.", 0);
        }
#endif
    }

    switch(GET_MEMORY_CONFIG_SELECT())
    {
        case _FRAME_SYNC_LINE_BUFFER:
        default:
            DebugMessageCheckMDomain("FrameSync Line Buffer", GET_MEMORY_CONFIG_SELECT());
            break;

        case _FRAME_SYNC_MEMORY:
            DebugMessageCheckMDomain("FrameSync Frame Buffer", GET_MEMORY_CONFIG_SELECT());
            break;

        case _FREE_RUN_MEMORY:
            DebugMessageCheckMDomain("Free Run Mode", GET_MEMORY_CONFIG_SELECT());
            break;

        case _MN_FRAME_SYNC_MEMORY:
            DebugMessageCheckMDomain("MN FrameSync Frame Buffer", GET_MEMORY_CONFIG_SELECT());
            break;

        case _FREE_RUN_NO_INPUT:
            DebugMessageCheckMDomain("Free Run No Input", GET_MEMORY_CONFIG_SELECT());
            break;
    }

#if((_OD_FUNCTION == _ON) || (_FRC_SUPPORT == _ON))
#if(_OD_FUNCTION == _ON)
    DebugMessageCheckMDomain("OD use bit", GET_OD_USE_BIT());

    if(GET_OD_USE_BIT() != 0x00)
    {
        StructMemoryBWUsageParam stMemBWParam;
        ScalerMDomainGetMemBWParam(&stMemBWParam);
        usBWUseEfficiency = (DWORD)ScalerMDomainODCalculateMemoryUseBW(GET_OD_USE_BIT(), &stMemBWParam) * 100 / _MEMORY_DATA_RATE_SPEED;
        DebugMessageCheckMDomain("OD Efficiency(0.1%)", usBWUseEfficiency);
    }
    else
    {
        DebugMessageCheckMDomain("[Warning]!!!!!! OD Disable", 0);
    }

#endif

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    if(ScalerFRCImgCmpGetActive(ScalerRegionGetIndexFromInputDataPath(GET_MDOMAIN_INPUT_DATA_PATH())) == _TRUE)
    {
        DebugMessageCheckMDomain("IMC on, databit: ", GET_IMG_CMP_PARAM_LLB(GET_IMG_CMP_PARAM()));
    }
    else
#endif
    {
        DebugMessageCheckMDomain("IMC off, databit: ", GET_MEMORY_DATA_BIT());
    }

#if(_FRC_SUPPORT == _ON)
    if(GET_MEMORY_CONFIG_SELECT() != _FRAME_SYNC_LINE_BUFFER)
    {
        DWORD ulPathBwSum = 0;
        for(uccnt = 0; uccnt < ScalerRegionGetMaxRegionCount(); uccnt++)
        {
            ulPathBwSum += GET_MEMORY_BW(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(uccnt)));
        }
        usBWUseEfficiency += (ulPathBwSum * 100 / _MEMORY_DATA_RATE_SPEED);
        DebugMessageCheckMDomain("FRC Efficiency(0.1%)", (ulPathBwSum * 100 / _MEMORY_DATA_RATE_SPEED));
        DebugMessageCheckMDomain("FRC RemainBW(0.1%)", ((WORD)_MEMORY_EFFICIENCY * 10 - usBWUseEfficiency));

        if((GET_FIFO_INPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH()) < GET_MDOMAIN_INPUT_HWIDTH()) && (GET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH()) < GET_MDOMAIN_OUTPUT_HWIDTH()))
        {
            DebugMessageCheckMDomain("[Warning]!!!!!! HSD for Memory BW/ size", GET_FIFO_INPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH()));
            DebugMessageCheckMDomain("[Warning]!!!!!! HSD for Memory BW/ size", GET_FIFO_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_DATA_PATH()));
        }
    }
#endif

    DebugMessageCheckMDomain("FRC + OD Efficiency(0.1%)", usBWUseEfficiency);

    if(usBWUseEfficiency > ((WORD)(_MEMORY_EFFICIENCY - 2) * 10))
    {
        DebugMessageCheckMDomain("[Warning]!!!!!! Efficiency Utilization near boundry", usBWUseEfficiency);
    }
#endif

    DebugMessageCheckMDomain("== DISP_CHECK_END ==", 0);
}
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
//--------------------------------------------------
// Description  : Set Display Timing Gen Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainDisplayTimingGenDBEnable(bit bEnable)
{
    // Set Display Timing Gen Double Buffer
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT6 | _BIT5), _BIT6);
    }
    else
    {
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT6 | _BIT5), 0x00);
    }
}

//--------------------------------------------------
// Description  : Apply Display Timing Gen Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainDisplayTimingGenDBApply(EnumDBApply enumDBApply)
{
    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Check if Display Timing Gen DB is enabled
        if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT6) == 0x00)
        {
            return;
        }

        // Check D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            // Disable Double Buffer
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT6, 0x00);
            return;
        }

        // Apply Display Timing Gen Double Buffer
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            // Wait Display Timing Gen double buffer
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT5, 0) == _FALSE)
            {
                // Disable Double Buffer
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT6, 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get DisplayTimingGen Double Buffer Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMDomainDisplayTimingGenGetDBStatus(void)
{
    if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT6) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Get DVtotal/Lastline Measure Result
// Input Value  : None
// Output Value : DVtotal or Lastline
//--------------------------------------------------
WORD ScalerMDomainGetDVtotalLastline(void)
{
    WORD usDVtotalLastline = 0x00;

    ScalerSetBit(P0_46_LAST_LINE_H1, ~_BIT7, _BIT7);
    usDVtotalLastline = ((((WORD)(ScalerGetByte(P0_46_LAST_LINE_H1) & 0x03) << 13) | ((WORD)(ScalerGetByte(P0_44_LAST_LINE_H) & 0x1F) << 8) | ScalerGetByte(P0_45_LAST_LINE_L)) & _HW_DVTOTAL_LASTLINE_MEAS_GEN_BIT);
    ScalerSetBit(P0_46_LAST_LINE_H1, ~_BIT7, 0x00);
    return usDVtotalLastline;
}

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
//--------------------------------------------------
// Description  : Get DVtotal For LocalContrast
// Input Value  : None
// Output Value : DVtotal
//--------------------------------------------------
WORD ScalerMDomainLocalContrastGetVtotal(void)
{
    WORD usDVtotal = 0;

    // Measure DVtotal
    if(GET_MEMORY_CONFIG_SELECT() != _FREE_RUN_MEMORY)
    {
        // Measure DVtotal in frame sync mode
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        usDVtotal = ScalerMDomainGetDVtotalLastline();

        if(GET_MEMORY_CONFIG_SELECT() == _FRAME_SYNC_LINE_BUFFER)
        {
            // line-buffer case DVtotal has 1 line diff
            usDVtotal = usDVtotal - 1;
        }
    }
    else
    {
        // Measure DVtotal in free run mode
        usDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();
    }

    return usDVtotal;
}
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get panel info for RTK Advance MBR
// Input Value  : Panel info buffer
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetRtkAdvMbrPanelInfo(StructRtkAdvMbrPanelInfo *pstPanelInfo)
{
    pstPanelInfo->usMaxFreq = g_stDisplayCustomizedData.structDVCustomizedFreq.usMaxFreq;
    pstPanelInfo->usMinFreq = g_stDisplayCustomizedData.structDVCustomizedFreq.usMinFreq;
    pstPanelInfo->ucFrameSyncMargin = _PANEL_FRAME_SYNC_MARGIN;
    pstPanelInfo->ulPixelClock = GET_PANEL_PIXEL_CLOCK_TYPICAL();
    pstPanelInfo->ulPixelClockMax = GET_PANEL_PIXEL_CLOCK_MAX_SPREAD();
    pstPanelInfo->ulPixelClockMin = GET_PANEL_PIXEL_CLOCK_MIN_SPREAD();
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Eagle Sight Sub can display when main is frame sync mode
// Input Value  : None
// Output Value : _EAGLE_SIGHT_MAIN_SUB_SYNC / _EAGLE_SIGHT_MAIN_SUB_ASYNC
//--------------------------------------------------
EnumEagleSightMainSubSynchronous ScalerMDomainGetEagleSightMainSubSync(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        switch(ScalerMDomainGetFrameSyncMode())
        {
#if(_EAGLE_SIGHT_MN_FRAME_SYNC_SUPPORT == _ON)
            case _MN_FRAME_SYNC_MODE:
#endif

#if(_EAGLE_SIGHT_FREERUN_SUPPORT == _ON)
            case _FREE_RUN_MODE:
#endif

            case _FRAME_SYNC_MODE:
#if((_HW_FORMAT_CONVERSION_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE))
                if(ScalerFmtCnvHalfSDGetFactor(ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)) == 0x01)
#endif
                {
                    return _EAGLE_SIGHT_MAIN_SUB_SYNC;
                }
                break;
            default:
                break;
        }
    }

    return _EAGLE_SIGHT_MAIN_SUB_ASYNC;
}
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Frame Sync Source
// Input Value  : enumFrameSyncSource
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetFrameSyncSource(EnumFrameSyncSource enumFrameSyncSource)
{
    if(enumFrameSyncSource == _FRAME_SYNC_MAIN)
    {
        // Set Frame Sync Source: Main
        ScalerSetBit(P0_29_DISPLAY_CONTROL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }
    else
    {
        // Set Frame Sync Source: Sub
        ScalerSetBit(P0_29_DISPLAY_CONTROL, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
}
#endif

#if(_MDOMAIN_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable mdomain pr mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainPRModeInitial(void)
{
#if(_HW_M_DOMAIN_PR_MODE_TYPE == _M_DOMAIN_PR_MODE_GEN_0)
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        if(CHK_FRC_PATH(GET_MDOMAIN_INPUT_DATA_PATH(), GET_FRC_INPUT_DATA_PATH(ucIndex)) == _TRUE)
        {
            SET_PAGED_BYTE(GET_FRC_PAGE_SELECT(ucIndex), P5_4D_CAP_M1_PR_MODE, _BIT0);
        }
    }
    ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

#elif (_HW_M_DOMAIN_PR_MODE_TYPE == _M_DOMAIN_PR_MODE_GEN_1)
    for (BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumFRCChannelPageSelect enumChannelSel = ScalerFRCGetChannelPage(ScalerFRCGetChannelFromInputpath(GET_MDOMAIN_INPUT_DATA_PATH()));
        if(CHK_FRC_PATH(enumChannelSel, ScalerFRCGetChannelPage(ucIndex)) == _TRUE)
        {
            SET_PAGED_BYTE(ScalerFRCGetChannelPage(ucIndex), P46_06_M_CAP_PR_MODE, _BIT0);
        }
    }
    ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);
#endif
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Mdm Output H/VStart for ES Original Mode
// Input Value  : EnumDisplayRegion
// Output Value : none
//--------------------------------------------------
void ScalerMDomainSetESOriginalModeHVStart(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        if(ScalerScalingGetESOriginalModeStatus(GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_VHEIGHT()) == _TRUE)
        {
            DWORD ulDiff_Vstart_Idm = 0;
            DWORD ulDiff_Vstart_Ddm = 0;
            DWORD ulDTGVstart = 0;
            DWORD ulDiff_Hstart_Idm = 0;
            DWORD ulDiff_Hstart_Ddm = 0;
            DWORD ulDTGHstart = 0;

            ulDiff_Vstart_Idm = ScalerScalingGetESOriginalModeMainSubDiffVstart();
            ulDiff_Vstart_Ddm = GET_DWORD_MUL_DIV(ulDiff_Vstart_Idm, GET_MDOMAIN_OUTPUT_VHEIGHT(), GET_MDOMAIN_INPUT_VHEIGHT());
            ulDTGVstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START) + ulDiff_Vstart_Ddm;
            SET_MDOMAIN_OUTPUT_VSTART(ulDTGVstart);
            SET_MDOMAIN_OUTPUT_VBSTART(ulDTGVstart);

            ulDiff_Hstart_Idm = ScalerScalingGetESOriginalModeMainSubDiffHstart();
            ulDiff_Hstart_Ddm = GET_DWORD_MUL_DIV(ulDiff_Hstart_Idm, GET_MDOMAIN_OUTPUT_HWIDTH(), GET_MDOMAIN_INPUT_HWIDTH());
            ulDTGHstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) + ulDiff_Hstart_Ddm;
            SET_MDOMAIN_OUTPUT_HSTART(ulDTGHstart);
            SET_MDOMAIN_OUTPUT_HBSTART(ulDTGHstart);
        }
    }
}
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Insert function control
// Input Value  : EnumFunctionOnOFF, EnumMbrBFIKernelMode
// Output Value : none
//--------------------------------------------------
void ScalerMDomainBlackFrameInsertEnable(EnumFunctionOnOFF enumFunctionOnOFF, EnumMbrBFIKernelMode enumMbrBFIKernelMode)
{
    if(enumFunctionOnOFF == _FUNCTION_OFF)
    {
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT1, 0x00);
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, _DB_APPLY_POLLING);
    }
    else
    {
#if((_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_0) || (_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_1))
        ScalerDDomainBackgroundSetColor(_DDOMAIN_RGN_R1_A1, 0, 0, 0, _DB_APPLY_NONE);
#endif

        switch(enumMbrBFIKernelMode)
        {
#if(_MOTION_BLUR_REDUCTION_BFI_1_IVF_SUPPORT == _ON)
            case _BFI_KERNEL_1X:
#endif
            default:

#if((_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_0) || (_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_1))
                ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT1, _BIT1);
                ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, _DB_APPLY_POLLING);
#elif(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_2)
                // Insert cycle cnt = 2, Insert black at frame idx = 0 (mask = 0x1)
                ScalerDDomainBackgroundSetColorInsert(_ENABLE, 0x00, 0x00, 0x00, 0x02, 0x01, _DB_APPLY_POLLING);
#endif

                break;

            case _BFI_KERNEL_2X:
            {
                EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(_DISPLAY_RGN_1P);
                EnumDBEnableStatus enumDBBackup = ScalerGlobalGetDBStatus(enumInputDataPath);
                BYTE ucMNIdx = 0xFF;

                // Disable Global DB
                if(enumDBBackup != _DB_DISABLE)
                {
                    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, _DB_APPLY_POLLING);
                    ScalerGlobalDoubleBufferEnable(enumInputDataPath, _DISABLE);
                }

#if(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_0)
#if(_COLOR_IP_D_DITHER == _ON)
                // Disable DDither
                ScalerColorDDitherEnable(_FUNCTION_OFF);
#endif

                // Enable DCRC
                ScalerSetByte(P36_C0_D_CRC_CTRL_M1, 0x81);
#if(_HW_D_DOMAIN_M2_PATH_SUPPORT == _ON)
                ScalerSetByte(P36_C8_D_CRC_CTRL_M2, 0x81);
#endif
#if((_HW_D_DOMAIN_M3_PATH_SUPPORT == _ON) && (_HW_D_DOMAIN_M4_PATH_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    ScalerSetByte(P36_D0_D_CRC_CTRL_M3, 0x81);
                    ScalerSetByte(P36_D8_D_CRC_CTRL_M4, 0x81);
                }
#endif

                // I-domain frame:          |______F1_______|______F2_______|______F3_______|______F4_______|______F5_______|
                // D-domain frame:           |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F3___|__F3___|__F4___|__F4___|
                // MN idx:                   |___0___|___1___|___0___|___1___|___0___|___1___|___0___|___1___|___0___|___1___|
                // Insert enable case 0:                       |on
                // Read MN idx & DCRC:                                                 |read
                // Black frame - good:       |_______|_______|_______|___B___|_______|___B___|_______|___B___|_______|___B___|
                // Black frame - adjust:     |_______|_______|_______|_______|___B___|_______|___B___ _______|_______|___B___|
                // Insert enable case 1:                               |on
                // Read MN idx & DCRC:                                                         |read
                // Black frame - adjust:     |_______|_______|_______|_______|___B___|_______|___B___ _______|_______|___B___|
                // Black frame - good:       |_______|_______|_______|_______|_______|___B___|_______|___B___ _______|___B___|

                // Start fine tune MN index and Insert black frame
                ScalerTimerWaitForDDomainEvent(_EVENT_DVS); // Start of Alignment
                ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT1, _BIT1);

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

                ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT, 1, &ucMNIdx, _AUTOINC);
                ScalerMDomainBlackFrameInsertSync(ucMNIdx, ScalerMDomainCheckPreviousBlackFrame());

                // Disable DCRC
                ScalerSetByte(P36_C0_D_CRC_CTRL_M1, 0x00);
#if(_HW_D_DOMAIN_M2_PATH_SUPPORT == _ON)
                ScalerSetByte(P36_C8_D_CRC_CTRL_M2, 0x00);
#endif
#if((_HW_D_DOMAIN_M3_PATH_SUPPORT == _ON) && (_HW_D_DOMAIN_M4_PATH_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    ScalerSetByte(P36_D0_D_CRC_CTRL_M3, 0x00);
                    ScalerSetByte(P36_D8_D_CRC_CTRL_M4, 0x00);
                }
#endif

#if(_COLOR_IP_D_DITHER == _ON)
                // Enable DDither
                ScalerColorDDitherEnable(_FUNCTION_ON);
#endif
#elif(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_1)
                // I-domain frame:          |______F1_______|______F2_______|______F3_______|______F4_______|______F5_______|
                // D-domain frame:           |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F3___|__F3___|__F4___|__F4___|
                // MN idx:                   |___0___|___1___|___0___|___1___|___0___|___1___|___0___|___1___|___0___|___1___|
                // Insert enable:                              |on
                // DVS status flag:          |_______|_______|_______|___1___|___0___|___1___|___0___|___1___|___0___|___1___|
                // bg_color_insert_flag = 1: |_______|_______|_______|___B___|_______|___B___|_______|___B___|_______|___B___|
                // Insert enable:                                      |on
                // DVS status flag:          |_______|_______|_______|_______|___1___|___0___|___1___|___0___|___1___|___0___|
                // bg_color_insert_flag = 0: |_______|_______|_______|_______|_______|___B___|_______|___B___|_______|___B___|

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
                ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT, 1, &ucMNIdx, _AUTOINC);

                if(ucMNIdx == 0)
                {
                    // Set Insert enable and bg_color_insert_flag = 1 to insert dvs status flag == 1 frame
                    ScalerSetBit(P80_A0_OVERLAY_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                }
                else
                {
                    // Set Insert enable and bg_color_insert_flag = 0 to insert dvs status flag == 0 frame
                    ScalerSetBit(P80_A0_OVERLAY_CTRL, ~(_BIT2 | _BIT1), _BIT1);
                }

                // Wait DVS for Insert function effective
                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
#elif(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_2)
                // I-domain frame:          |______F1_______|______F2_______|______F3_______|______F4_______|______F5_______|
                // D-domain frame:           |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F3___|__F3___|__F4___|__F4___|
                // MN idx:                   |___0___|___1___|___0___|___1___|___0___|___1___|___0___|___1___|___0___|___1___|
                // Insert enable:                              |on
                // repeat frame idx:         |_______|_______|_______|___0___|___1___|___0___|___1___|___0___|___1___|___0___|
                // bg_color_insert_flag = 0x1|_______|_______|_______|___B___|_______|___B___|_______|___B___|_______|___B___|
                // Insert enable:                                      |on
                // repeat frame idx:         |_______|_______|_______|_______|___0___|___1___|___0___|___1___|___0___|___1___|
                // bg_color_insert_flag = 0x2|_______|_______|_______|_______|_______|___B___|_______|___B___|_______|___B___|

                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
                ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT, 1, &ucMNIdx, _AUTOINC);

                if(ucMNIdx == 0)
                {
                    // Insert cycle cnt = 2, Insert black at frame idx = 0 (mask = 0x1)
                    ScalerDDomainBackgroundSetColorInsert(_ENABLE, 0x00, 0x00, 0x00, 0x02, 0x01, _DB_APPLY_NONE);
                }
                else
                {
                    // Insert cycle cnt = 2, Insert black at frame idx = 1 (mask = 0x2)
                    ScalerDDomainBackgroundSetColorInsert(_ENABLE, 0x00, 0x00, 0x00, 0x02, 0x02, _DB_APPLY_NONE);
                }

                // Wait DVS for Insert function effective
                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
#endif
                // Restore Global DB
                if(enumDBBackup != _DB_DISABLE)
                {
                    ScalerGlobalDoubleBufferEnable(enumInputDataPath, _ENABLE);
                }

                break;
            }
        }
    }
}

#if(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_0)
//--------------------------------------------------
// Description  : Check if previous frame is black frame
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerMDomainCheckPreviousBlackFrame(void)
{
    BYTE pucCRCValue[6];
    BYTE pucCRCValue_Black[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Read currernt CRC from target register
    ScalerRead(P36_C1_D_MAIN1_CRC_1, 6, pucCRCValue, _AUTOINC);
    if(memcmp(pucCRCValue, pucCRCValue_Black, 6) != 0)
    {
        return _FALSE;
    }

#if(_HW_D_DOMAIN_M2_PATH_SUPPORT == _ON)
    ScalerRead(P36_C9_D_MAIN2_CRC_1, 6, pucCRCValue, _AUTOINC);
    if(memcmp(pucCRCValue, pucCRCValue_Black, 6) != 0)
    {
        return _FALSE;
    }
#endif

#if((_HW_D_DOMAIN_M3_PATH_SUPPORT == _ON) && (_HW_D_DOMAIN_M4_PATH_SUPPORT == _ON))
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerRead(P36_D1_D_MAIN3_CRC_1, 6, pucCRCValue, _AUTOINC);
        if(memcmp(pucCRCValue, pucCRCValue_Black, 6) != 0)
        {
            return _FALSE;
        }

        ScalerRead(P36_D9_D_MAIN4_CRC_1, 6, pucCRCValue, _AUTOINC);
        if(memcmp(pucCRCValue, pucCRCValue_Black, 6) != 0)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Sync Insert black frame and MN frame index
// Input Value  : ucMNIdx, bPreviosBlackFrame
// Output Value : None
//--------------------------------------------------
void ScalerMDomainBlackFrameInsertSync(BYTE ucMNIdx, bit bPreviosBlackFrame)
{
    if((ucMNIdx == 0) && (bPreviosBlackFrame == _FALSE))
    {
        // Disable WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable MN Frame sync
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, 0x00);

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        // Restart MN Frame sync
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, _BIT7);

        // Restart WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else if((ucMNIdx == 1) && (bPreviosBlackFrame == _TRUE))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        // Disable WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable MN Frame sync
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, 0x00);

        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        // Restart MN Frame sync
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, _BIT7);

        // Restart WD
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
        ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : Check MTP free run finetune HVtotal
// Input Value  : None
// Output Value : _TRUE: need to finetune HVtotal
//--------------------------------------------------
bit ScalerMDomainCheckMTPFreerunFinetune(void)
{
#if(_FRC_SUPPORT == _ON)
    if((GET_FORCE_DISPLAY_1P_MODE() == _FALSE) &&
       (g_stDisplayCustomizedData.structDVCustomizedFreq.usTypFreq != _PANEL_TYP_FRAME_RATE))
    {
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
        if(GET_MTP_MEMORY_SELECT() == _SUB_DISPLAY_SETTING_MAIN_NONE)
#endif
        {
            return _TRUE;
        }
    }
#endif
    return _FALSE;
}
