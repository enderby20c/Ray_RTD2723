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
// ID Code      : ScalerMeasure.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MEASURE__

#include "ScalerFunctionInclude.h"
#include "Measure/ScalerMeasure.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructRegionTimingInfo g_pstMeasureRegionTimingInfo[_MULTI_DISPLAY_MAX];
StructRegionTimingInfo *g_pstMeasureRegionTimingInfoPointer = &(g_pstMeasureRegionTimingInfo[0]);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Assign measure timing info pointer to specified region
//                @#macro like GET_INPUT_TIMING_HWIDTH() is only valid after calling this function.
// Input Value  : enumRegionIndex -> region index
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetRegionIndex(EnumRegionIndex enumRegionIndex)
{
    if(enumRegionIndex < _MULTI_DISPLAY_MAX)
    {
        // Set measure result pointer
        g_pstMeasureRegionTimingInfoPointer = &(g_pstMeasureRegionTimingInfo[enumRegionIndex]);
    }
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumDisplayRegion --> select measure region
// Output Value : None
//--------------------------------------------------
EnumDisplayRegion ScalerMeasureGetResultPointerRegion(void)
{
    return GET_RGN_DISPLAY_REGION(g_pstMeasureRegionTimingInfoPointer - g_pstMeasureRegionTimingInfo);
}

//--------------------------------------------------
// Description  : Assign input data path for current measure target.
//                Most path mapping during measure flow relies on this variable.
// Input Value  : enumInputDataPath -> input data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetInputPath(EnumInputDataPath enumInputDataPath)
{
    // Set measure input source
    SET_MEASURE_INPUT_PATH(enumInputDataPath);
}

//--------------------------------------------------
// Description  : Clear all timing info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMeasureResetAllTimingInfo(void)
{
    BYTE ucIndex = 0x00;

    for(; ucIndex < _MULTI_DISPLAY_MAX; ++ucIndex)
    {
        memset(&(g_pstMeasureRegionTimingInfo[ucIndex].stTimingInfo), 0x00, sizeof(StructTimingInfo));
    }
}

//--------------------------------------------------
// Description  : Clear timing info for specified path
// Input Value  : enumInputDataPath -> input data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureResetTimingInfo(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIndex = ScalerRegionGetIndexFromInputDataPath(enumInputDataPath);

    if(ucIndex < _MULTI_DISPLAY_MAX)
    {
        CLR_MDOMAIN_REF_INPUT_HSTART(ucIndex);
        memset(&(g_pstMeasureRegionTimingInfo[ucIndex].stTimingInfo), 0x00, sizeof(StructTimingInfo));
    }
}

//--------------------------------------------------
// Description  : Update measure timing index by source
// Input Value  : enumFormatConversionSourceType --> format conversion source type
// Output Value : _TRUE if enumFormatConversionSourceType is valid
//--------------------------------------------------
bit ScalerMeasureSetSourceResultIndex(EnumFormatConversionSourceType enumFormatConversionSourceType)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < _MULTI_DISPLAY_MAX; ++ucRegionIndex)
    {
        if(ScalerFmtCnvGetSourceType(g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.enumInputDataPath) == enumFormatConversionSourceType)
        {
            g_pstMeasureRegionTimingInfoPointer = &(g_pstMeasureRegionTimingInfo[ucRegionIndex]);
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Convert input data path to I-domain register page
// Input Value  : enumInputDataPath -> input data path
// Output Value : I-domain register page recorded in #g_pstIDomainPathInfo
//--------------------------------------------------
BYTE ScalerMeasureGetIDomainPage(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0x00)
        {
            return ucIdomainPage;
        }
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Convert input data path to on-line measure register page
// Input Value  : enumInputDataPath -> input data path
// Output Value : on-line measure register page
//--------------------------------------------------
BYTE ScalerMeasureGetOnlineMeasurePage(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucMeasurePage = GET_ONLINE_MEASURE_REG_PAGE(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0x00)
        {
            return ucMeasurePage;
        }
    }

    return GET_ONLINE_MEASURE_REG_PAGE(0);
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return HDMI port page
// Input Value  : enumInputPort --> input port
// Output Value : HDMI page
//--------------------------------------------------
BYTE ScalerMeasureGetTmdsPage(EnumInputPort enumInputPort)
{
    WORD usHdmiAddress = 0;

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            usHdmiAddress = P72_70_IVHS_CTRL_0;
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            usHdmiAddress = P73_70_IVHS_CTRL_0;
            break;
#endif

        default:

            break;
    }

    return HIBYTE(usHdmiAddress);
}
#endif

//--------------------------------------------------
// Description  : Measure Input Timing
// Input Value  : enumSourceType --> Input source type
//                enumInputPort --> Input port type
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
EnumMeasureResult ScalerMeasureInputInfo(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial the interface to be measured
    ScalerMeasureInterfaceInitial(enumSourceType, &enumInputPort);

    // Initial measure & auto-function
    ScalerMeasureInitialSetting(enumSourceType, enumInputPort);

    // Initial Interlace Check Block
    ScalerMeasureInterlaceInitial(enumSourceType, enumInputPort);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _MEASURE_RESULT_FAIL;
    }
#endif

    // check Interface Pixel Mode Limit OOR
    if(ScalerMeasureCheckInterfaceNoSupport(enumInputPort) == _TRUE)
    {
        return _MEASURE_RESULT_OOR;
    }

    //===========================================================================================
    // 1. Start measure block & pop-out result
    //===========================================================================================

    // Wait for 2 raw IVS for digital; Pop out measure result
    if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerMeasureGetOfflineMeasureResult(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), enumInputPort) == _FALSE))
    {
        DebugMessageMeasure("Digital off-line measure fail", 0x00);
        return _MEASURE_RESULT_FAIL;
    }

    // check I-domain Path Limit OOR
    if(ScalerMeasureCheckIDomainNoSupport(enumInputPort) == _TRUE)
    {
        return _MEASURE_RESULT_OOR;
    }

    //===========================================================================================
    // 2. Check VGIP HS/VS polarity
    //===========================================================================================

    // Update input timing polarity
    ScalerMeasureUpdateInputTimingPolarity(enumSourceType, enumInputPort, &(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData));

#if(_COLOR_IP_3DDI == _ON)
#if(_HDMI_SUPPORT == _ON)
    if(((enumSourceType == _SOURCE_DVI) || (enumSourceType == _SOURCE_HDMI)) && (ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_TMDS_MAC))
    {
        // check DE-only mode enable or not
        if(GET_PAGED_BIT(ScalerMeasureGetTmdsPage(enumInputPort), P72_A7_TMDS_PWDCTL, _BIT7) == 0x00)
        {
            StructMeasureSyncData stMeasureSyncData = {0};
            WORD usVheight = g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVHeight;

            // Wait for 2 raw IVS for digital; Pop out measure result
            if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
               (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
               (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
               (ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncData, enumInputPort) == _FALSE))
            {
                DebugMessageMeasure("3DDI Digital off-line measure fail", 0x00);
                return _MEASURE_RESULT_FAIL;
            }

            if(stMeasureSyncData.usVHeight != usVheight)
            {
                SET_PAGED_BIT(ScalerMeasureGetTmdsPage(enumInputPort), P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                DebugMessageMeasure("interlace vheight 1", usVheight);
                DebugMessageMeasure("interlace vheight 2", stMeasureSyncData.usVHeight);
                DebugMessageMeasure("enable de-only mode", 0);
            }
            DebugMessageMeasure("3DDI Digital off-line measure againnnnnnnnnnnnn", 0x00);

            // save off-line measure data
            g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData = stMeasureSyncData;
        }
    }
#endif
#endif

    // Modify VGIP sync polarity
    ScalerVgipModifyPolarity(enumSourceType);

    // Update input timing data from variable "g_stMeasureSyncHV"
    ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), enumSourceType, enumInputPort);

    //===========================================================================================
    // 3. Start auto-function
    //===========================================================================================
    if(ScalerMeasureUpdateAutoPosition(enumSourceType, enumInputPort) == _FALSE)
    {
        return _MEASURE_RESULT_FAIL;
    }

    if(ScalerMeasureCheckAutoBoundaryResult(&(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        return _MEASURE_RESULT_FAIL;
    }

    //===========================================================================================
    // 4. Detect interlace format
    //===========================================================================================

    // Check interlace by flag
    if(ScalerMeasureInterlaceCheck(enumSourceType, enumInputPort) == _TRUE)
    {
        DebugMessageMeasure("Interlace: detect by flag", 0x00);
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        // Update video field
        if(ScalerGetBit(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()), _BIT6) == _BIT6)
        {
            g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VideoField = _TRUE;
        }
#endif
    }

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), enumSourceType, enumInputPort);

    //===========================================================================================
    // 5. Double-check current timing
    //===========================================================================================

    // Check consistency between different measure results
    if(ScalerMeasureCheckInputInfoConsistency(enumSourceType, enumInputPort) == _FALSE)
    {
        return _MEASURE_RESULT_FAIL;
    }

    //===========================================================================================
    // 6. Measure final settings
    //===========================================================================================

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_420_SUPPORT == _ON)
    ScalerColor420To422FinalSettingByPath(GET_MEASURE_INPUT_PATH(), enumInputPort);
#endif
#endif

#if(_COLOR_IP_3DDI == _ON)
    //===========================================================================================
    // Set 3DDI
    //===========================================================================================
    if(Scaler3DDIEnableDecision(GET_MEASURE_INPUT_PATH(), enumInputPort) == _TRUE)
    {
        SET_3DDI_STATUS(GET_MEASURE_INPUT_PATH(), _ON);

        ScalerMeasureSetInputPath(ScalerRegionGetInputDataPath(ScalerMeasureGetResultPointerRegion()));
        ScalerVgipSetInputPath(GET_MEASURE_INPUT_PATH());

        Scaler3DDISettingProc(GET_MEASURE_INPUT_PATH());

        // HSWidth will be 3 after 3DDI
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHSWidth = 3;

        // Repeat auto func measure
        if(ScalerMeasureUpdateAutoPosition(enumSourceType, enumInputPort) == _FALSE)
        {
            return _MEASURE_RESULT_FAIL;
        }

        // Update input timing data
        ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), enumSourceType, enumInputPort);

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
#if(_HDMI_SUPPORT == _ON)
        // 3DDI HW measure Vstart FC set even/odd line
        if(Scaler3DDIModifyTiming(GET_MEASURE_INPUT_PATH()) == _FALSE)
        {
            return _MEASURE_RESULT_FAIL;
        }
#endif
#endif
    }
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _MEASURE_RESULT_FAIL;
    }
#endif

    // Start on-line measure
    ScalerMeasureSetOnlineMeasure(enumSourceType, enumInputPort, GET_MEASURE_INPUT_PATH(), GET_INPUT_TIMING_VFREQ());

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    // Decide I-domain path setting in format conversion
    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        // Final format conversion setting
        ScalerFmtCnvFinalSetting(enumInputPort, GET_MEASURE_INPUT_PATH(), _WAIT);

        // Check VS bypass
        if(ScalerMeasureCheckVsBypass(enumSourceType, enumInputPort) == _TRUE)
        {
            ScalerVgipSetVsBypassEnable(GET_MEASURE_INPUT_PATH(), _ENABLE);
        }
    }

    // Double-cheeck auto-function again when timing is affected
    if(ScalerFmtCnvCheckIDomainTimingAffected(GET_MEASURE_INPUT_PATH(), enumInputPort) == _TRUE)
    {
        // Update auto-funciton position result
        if(ScalerMeasureUpdateAutoPosition(enumSourceType, enumInputPort) == _FALSE)
        {
            return _MEASURE_RESULT_FAIL;
        }
    }

#if(_DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE == _ON)
    // Set Format Conversion Background Color
    if(GET_COLOR_SPACE_RGB(ScalerColorGetColorSpace(enumInputPort)) == _TRUE)
    {
        ScalerFmtCnvSetBackgroundColor(GET_MEASURE_INPUT_PATH(), 0x00, 0x00, 0x00);
    }
    else
    {
        ScalerFmtCnvSetBackgroundColor(GET_MEASURE_INPUT_PATH(), 0x80, 0x00, 0x80);
    }
#endif
#endif

    // Perform measure final setting
    if(ScalerMeasureFinalSetting(enumSourceType, enumInputPort) == _FALSE)
    {
        DebugMessageMeasure("Final setting in measure fail", 0x00);
        return _MEASURE_RESULT_FAIL;
    }

    return _MEASURE_RESULT_PASS;
}

//--------------------------------------------------
// Description  : Initialzation for measure flow
// Input Value  : enumSourceType -> source type
//              : enumInputPort -> port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInitialSetting(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(GET_MEASURE_INPUT_PATH());

#if(_COLOR_IP_3DDI == _ON)
    // Reset 3DDI
    Scaler3DDIReset(GET_MEASURE_INPUT_PATH());
    // Reset Measure input path
    ScalerMeasureSetInputPath(ScalerRegionGetInputDataPath(ScalerMeasureGetResultPointerRegion()));
#endif

    DebugMessageMeasure("Measure input path", GET_MEASURE_INPUT_PATH());

    // Set VGIP input path
    ScalerVgipSetInputPath(GET_MEASURE_INPUT_PATH());

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    // Initial format conversion
    ScalerFmtCnvInitialSetting(enumSourceType, enumInputPort, GET_MEASURE_INPUT_PATH());
#endif

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    // Disable Shift One Line Before VGIP ivrun_en Disable
    // Avoid Lost IVS Event
    ScalerMemorySetShiftOneLine(_DISABLE, GET_VGIP_INPUT_PATH());
#endif

    // Initial VGIP for input signal pass through
    ScalerVgipInputInitial(enumSourceType, enumInputPort);

    // Reset interlace flag
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = _FALSE;
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1DpInterlaceVBID = _FALSE;
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VideoField = _FALSE;

    // Reset Vtotal Odd
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1InputVheightOdd = _FALSE;

    // Set off-line measure target
    ScalerMeasureSetOfflineMeasure(enumInputPort);

    // On-line measure(M1 & M2 & S1 & S2) clock divider disable
    SET_PAGED_BIT(ucMeasurePage, P3_00_SYNC_SELECT, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Initialzation for interface in measure flow
// Input Value  : enumSourceType ->  source type
//              : penumSourceSearchPort -> input port; Would be changed for dual-dvi port
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInterfaceInitial(EnumSourceType enumSourceType, EnumInputPort *penumSourceSearchPort)
{
    enumSourceType = enumSourceType;

    switch(*penumSourceSearchPort)
    {
#if(_VGA_SUPPORT == _ON)
        case _A0_INPUT_PORT:

            // Special case for small DVS width
            if(ScalerGetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
            {
                if(ScalerVgaSyncProcGetDeVsyncWidth() >= 4)
                {
                    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, ~(_BIT7 | _BIT6), 0x00);
                }
            }

            // Hsync Measure Source from SeHS or DeHS by CR49[6]
            ScalerSetBit(P0_49_SYNC_CTRL, ~_BIT2, _BIT2);

            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D1_INPUT_PORT) == _FROM_HDMI_TMDS_MAC)
            {
                // Tmds Mac ctrl HV polarity by Measure; FRL Mac ctrl by itself
                ScalerTmdsMacRxHVPolarityReset(_D1_INPUT_PORT);

                // reset Tmds De only mode Hs = 72
                ScalerTmdsMacRxSetDeOnlyModeConfig(_D1_INPUT_PORT, _DE_ONLY_HS_72T);
            }
#endif

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D2_INPUT_PORT) == _FROM_HDMI_TMDS_MAC)
            {
                // Tmds Mac ctrl HV polarity by Measure; FRL Mac ctrl by itself
                ScalerTmdsMacRxHVPolarityReset(_D2_INPUT_PORT);

                // reset Tmds De only mode Hs = 72
                ScalerTmdsMacRxSetDeOnlyModeConfig(_D2_INPUT_PORT, _DE_ONLY_HS_72T);
            }
#endif

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D3_INPUT_PORT) == _FROM_HDMI_TMDS_MAC)
            {
                // Tmds Mac ctrl HV polarity by Measure; FRL Mac ctrl by itself
                ScalerTmdsMacRxHVPolarityReset(_D3_INPUT_PORT);

                // reset Tmds De only mode Hs = 72
                ScalerTmdsMacRxSetDeOnlyModeConfig(_D3_INPUT_PORT, _DE_ONLY_HS_72T);
            }
#endif

            break;
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D4_INPUT_PORT) == _FROM_HDMI_TMDS_MAC)
            {
                // Tmds Mac ctrl HV polarity by Measure; FRL Mac ctrl by itself
                ScalerTmdsMacRxHVPolarityReset(_D4_INPUT_PORT);

                // reset Tmds De only mode Hs = 72
                ScalerTmdsMacRxSetDeOnlyModeConfig(_D4_INPUT_PORT, _DE_ONLY_HS_72T);
            }
#endif

            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_HDMI_SUPPORT == _ON)
            // Tmds Mac ctrl HV polarity by Measure; FRL Mac ctrl by itself
            ScalerTmdsMacRxHVPolarityReset(_D5_INPUT_PORT);

            // reset Tmds De only mode Hs = 72
            ScalerTmdsMacRxSetDeOnlyModeConfig(_D5_INPUT_PORT, _DE_ONLY_HS_72T);
#endif

            break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            break;
#endif // End of #if(_DUAL_DP_SUPPORT == _ON)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Final setting for measure flow
// Input Value  : enumSourceType -> source type
//              : enumInputPort -> input port
// Output Value : _TRUE if setting passed
//--------------------------------------------------
bit ScalerMeasureFinalSetting(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    // Double check off-line measure result
    if(ScalerMeasureOfflineMeasureDoubleCheck(enumSourceType, enumInputPort) == _FALSE)
    {
        DebugMessageMeasure("Digital off-line double check fail", 0x00);
        return _FALSE;
    }

    // Pop out on-line measure result
    if(ScalerMeasureGetOnlineMeasureResult(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        DebugMessageMeasure("Digital on-line measure fail", 0x00);
        return _FALSE;
    }

    // Check timing validity
    if((GET_INPUT_TIMING_HWIDTH() >= GET_INPUT_TIMING_HTOTAL()) ||
       (GET_INPUT_TIMING_VHEIGHT() >= GET_INPUT_TIMING_VTOTAL()))
    {
        return _FALSE;
    }

    // if VGIP VS Latched / by pass, set HSW = 16 / (EO Path)8
    SET_INPUT_TIMING_HSYNCWIDTH(_VGIP_LATCHED_HSYNCWIDTH);
    if(ScalerVgipGetVsBypassEnable(GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        SET_INPUT_TIMING_VSYNCWIDTH(_VGIP_LATCHED_VSYNCWIDTH);
    }

    // Update active region count
    ScalerMeasureUpdateActiveRegion();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check for I-Domain OOR in measure flow
// Input Value  : void
// Output Value : _TRUE if not supported
//--------------------------------------------------
bit ScalerMeasureCheckIDomainNoSupport(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_COLOR_IP_420_SUPPORT == _ON)
    if(GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420)
    {
        EnumFormatConversionPath enumFmtCnvPath = ScalerFmtCnvPathMapping(GET_MEASURE_INPUT_PATH());
        WORD usHwidth = GET_SYNC_H_WIDTH() * 2;

        if((enumFmtCnvPath & _FORMAT_CONVERSION_P0) != 0x00)
        {
            if(usHwidth > _HW_420_PATH0_BUFFER_WIDTH)
            {
                DebugMessageSystem("[warning] Measure Check for Input Hwidth over _HW_420_PATH0_BUFFER_WIDTH", usHwidth);
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
        if((enumFmtCnvPath & _FORMAT_CONVERSION_P1) != 0x00)
        {
            if(usHwidth > _HW_420_PATH1_BUFFER_WIDTH)
            {
                DebugMessageSystem("[warning] Measure Check for Input Hwidth over _HW_420_PATH1_BUFFER_WIDTH", usHwidth);
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
        if((enumFmtCnvPath & _FORMAT_CONVERSION_P2) != 0x00)
        {
            if(usHwidth > _HW_420_PATH2_BUFFER_WIDTH)
            {
                DebugMessageSystem("[warning] Measure Check for Input Hwidth over _HW_420_PATH2_BUFFER_WIDTH", usHwidth);
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
        if((enumFmtCnvPath & _FORMAT_CONVERSION_P3) != 0x00)
        {
            if(usHwidth > _HW_420_PATH3_BUFFER_WIDTH)
            {
                DebugMessageSystem("[warning] Measure Check for Input Hwidth over _HW_420_PATH3_BUFFER_WIDTH", usHwidth);
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
#endif
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check internal consistency for input timing info structure
// Input Value  : enumSourceType --> input source Type
//                enumInputPort --> input port type
// Output Value : _TRUE if timing info is consistent
//--------------------------------------------------
bit ScalerMeasureCheckInputInfoConsistency(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    BYTE ucHwidthFactor = 0x01;

    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

#if(_HDMI_SUPPORT == _ON)
    if(((enumSourceType == _SOURCE_DVI) || (enumSourceType == _SOURCE_HDMI)) && (ScalerTmdsMacRxGetDeOnlyModeConfig(enumInputPort) == (EnumDeOnlyConfig)(_DE_ONLY_ENABLE | _DE_ONLY_HS_72T)))
    {
        if(GET_INPUT_TIMING_HSTART() <= 8)
        {
            DebugMessageMeasure("Digital check H start <= 8 fail", 0x00);
            return _FALSE;
        }
        else if(GET_INPUT_TIMING_HSTART() <= 72)
        {
            // No need to return FALSE!
            ScalerTmdsMacRxSetDeOnlyModeConfig(enumInputPort, _DE_ONLY_HS_8T);
        }
    }
#endif

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Apply horizontal factor between measure & I-domain info
    ucHwidthFactor *= ScalerFmtCnvGetPixelModeTargetFactor(GET_MEASURE_INPUT_PATH());
    ucHwidthFactor /= ScalerFmtCnvGetPixelModeFactor(GET_MEASURE_INPUT_PATH());
#endif
#endif

    if((GET_INPUT_TIMING_VHEIGHT() % 2) != 0x00)
    {
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1InputVheightOdd = _TRUE;
    }

    // Check digital measure result
    if(abs(GET_SYNC_V_HEIGHT() - GET_INPUT_TIMING_VHEIGHT()) > 2)
    {
        DebugMessageMeasure("Digital check V height fail", 0x00);
        return _FALSE;
    }

#if(_HDMI_SUPPORT == _ON)
    if((enumSourceType == _SOURCE_DVI) || (enumSourceType == _SOURCE_HDMI))
    {
        // Check HDMI Special Timing
        if((ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_TMDS_MAC) &&
           (ScalerMeasureCheckTmdsDeOnlyTiming(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreq)) == _FALSE))
        {
            // check DE-only mode enable or not
            if((ScalerTmdsMacRxGetDeOnlyModeConfig(enumInputPort) & _DE_ONLY_ENABLE) == _BIT1)
            {
                // Disable DE-only mode
                ScalerTmdsMacRxSetDeOnlyModeConfig(enumInputPort, _DE_ONLY_DISABLE);

                DebugMessageMeasure("Measure Check for HDMI DE-only mode Timing", 0x00);
                return _FALSE;
            }
        }
    }
#endif

    if(abs(GET_SYNC_H_WIDTH() - (GET_INPUT_TIMING_HWIDTH() / ucHwidthFactor)) > 2)
    {
#if(_HDMI_SUPPORT == _ON)
        if((enumSourceType == _SOURCE_DVI) || (enumSourceType == _SOURCE_HDMI))
        {
            // Check first line width for DVI/HDMI
            ScalerMeasureCheckFirstLineShift(enumInputPort, GET_SYNC_H_WIDTH());
        }
#endif

        DebugMessageMeasure("Digital check H width fail", 0x00);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Timing double check before display setting to prevent un-detected timing change before active.
// Input Value  : enumSourceType --> input source Type
//                enumInputPort --> input port type
//                enumRegionIndex --> target region index
// Output Value : _TRUE if double check passed
//--------------------------------------------------
bit ScalerMeasureDoubleCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex)
{
    bit bDoubleCheckStatus = _FALSE;

    bDoubleCheckStatus = (ScalerMeasureInterlaceDoubleCheck(enumSourceType, enumInputPort, enumRegionIndex) ==
                          g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.b1Interlace);

    return bDoubleCheckStatus;
}

//--------------------------------------------------
// Description  : Check if input timing is changed by comparing with input timing info
// Input Value  : enumSourceType --> source type
//                enumInputPort --> check port
//                ucRegionIndex --> retion index
// Output Value : _TRUE if timing Changed
//--------------------------------------------------
bit ScalerMeasureCheckTimingChange(EnumSourceType enumSourceType, EnumInputPort enumInputPort, BYTE ucRegionIndex)
{
    // Check on-line measure results
    bit bTimingChangeStatus = ((ScalerMeasureCheckOnlineMeasureChange(enumSourceType, enumInputPort, ucRegionIndex) == _TRUE) ||
                               (ScalerMeasureCheckWDTriggerStatus(ucRegionIndex) == _TRUE));

    return bTimingChangeStatus;
}

//--------------------------------------------------
// Description  : Check on-line measure result to detect timing change
// Input Value  : enumInputPort --> target input port
//                ucRegionIndex --> target region index
// Output Value : _TRUE if on-line measure result changed
//--------------------------------------------------
bit ScalerMeasureCheckOnlineMeasureChange(EnumSourceType enumSourceType, EnumInputPort enumInputPort, BYTE ucRegionIndex)
{
    bit bTimingChangeStatus = _FALSE;
    EnumInputDataPath enumInputDataPath = g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.enumInputDataPath;
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumInputDataPath);
    StructMeasureSyncData stMeasureSyncHV = {0};

    enumInputPort = enumInputPort;
    enumSourceType = enumSourceType;

    // Pop up if on-line measure complete
    if(GET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, _BIT7) == 0x00)
    {
        BYTE ucMeasureHSPeriodMaxChange = 2;

        if(ScalerMeasureGetOnlineMeasureResult(&stMeasureSyncHV, enumInputDataPath) == _FALSE)
        {
            return _TRUE;
        }

#if(_DP_SUPPORT == _ON)
        if(enumSourceType == _SOURCE_DP)
        {
            ucMeasureHSPeriodMaxChange = _MEASURE_DP_H_PERIOD_MAX_CHANGE;
        }
#endif

#if(_VGA_SUPPORT == _ON)
        if(enumInputPort == _A0_INPUT_PORT)
        {
            // Check on-line measure result
            bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1HSP) ||
                                   (abs(stMeasureSyncHV.usHSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usHSPeriod) > 2));

            if(g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.b1Interlace == _TRUE)
            {
                bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVSPeriod) > 3);
            }
            else
            {
                bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVSPeriod) > 2);
            }
        }
        else
#endif
        {
#if(_DRR_SUPPORT == _ON)
            if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
            {
                // Check off-line measure result
                bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1HSP) ||
                                       (stMeasureSyncHV.b1VSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1VSP) ||
                                       (abs(stMeasureSyncHV.usHWidth - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usHWidth) > 2) ||
                                       (abs(stMeasureSyncHV.usVHeight - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVHeight) > 2));

#if((_DP_SUPPORT == _ON) && (_FW_ONESHOT_MODE_SUPPORT == _OFF))
                // DP Frame sync BE Mode case
                if((ScalerSyncGetPortType(enumInputPort) == _PORT_DP) &&
                   (ScalerDpMacStreamRxGetDPFRegenMode(enumInputPort) == _DPF_MODE_FRAME_SYNC_BE))
                {
                    g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVTotal = ScalerDpMacStreamRxGetVSPeriod(enumInputPort);
                    g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVFreq = ScalerDpMacStreamRxGetVFreq(enumInputPort);
                }
                else
#endif
                {
                    if((g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.b1Interlace == _FALSE) &&
                       (ucRegionIndex == _REGION_INDEX_0))
                    {
                        // Check input active region measure type & source select
                        if(((ScalerMeasureGetInputRegionSourceSelect() & enumInputDataPath) == 0x00) ||
                           (ScalerMeasureGetInputRegionType() != _WHOLE_FRAME_TYPE))
                        {
                            ScalerMeasureSetInputRegionCount(enumInputDataPath, _WHOLE_FRAME_TYPE);
                        }
                        else
                        {
                            g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVTotal = stMeasureSyncHV.usVSPeriod;

                            // Update DRR Accuracy IVF
                            g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVFreq = ((GET_DWORD_MUL_DIV(_MEASURE_CLK, 100000, ScalerMeasureGetInputRegionCountResult(_NOT_WAIT)) + 5) / 10);
                        }
                    }
                    else
                    {
                        if(abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVTotal) > 2)
                        {
                            g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVTotal = stMeasureSyncHV.usVSPeriod;

                            // Other region, Update IVF calculated by on-line measure result
                            g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / stMeasureSyncHV.usHSPeriod / stMeasureSyncHV.usVSPeriod + 1) / 2;
                        }
                    }
                }
            }
            else
#endif
            {
#if(_HDMI_FRL_SUPPORT == _ON)
                if((enumSourceType == _SOURCE_HDMI) &&
                   (ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC))
                {
                    // FRL mode don't check HS period
                    bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1HSP) ||
                                           (stMeasureSyncHV.b1VSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1VSP) ||
                                           (abs(stMeasureSyncHV.usHWidth - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usHWidth) > 2) ||
                                           (abs(stMeasureSyncHV.usVHeight - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVHeight) > 2));
                }
                else
#endif
                {
                    // Check on-line measure result
                    bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1HSP) ||
                                           (stMeasureSyncHV.b1VSP != g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.b1VSP) ||
                                           (abs(stMeasureSyncHV.usHSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usHSPeriod) > ucMeasureHSPeriodMaxChange) ||
                                           (abs(stMeasureSyncHV.usHTotal - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usHTotal) > 2) ||
                                           (abs(stMeasureSyncHV.usHWidth - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usHWidth) > 2) ||
                                           (abs(stMeasureSyncHV.usVHeight - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVHeight) > 2));

                    if(g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.b1Interlace == _TRUE)
                    {
                        bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVSPeriod) > 3);
                    }
                    else
                    {
                        bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfo[ucRegionIndex].stMeasureSyncData.usVSPeriod) > 2);
                    }
                }
            }
        }
    }

    return bTimingChangeStatus;
}

//--------------------------------------------------
// Description  : Check if VGIP VS is bypassed
// Input Value  : enumSourceType -> source type
//                enumInputPort -> port type
// Output Value : _TRUE if VGIP VS is bypassed
//--------------------------------------------------
bit ScalerMeasureCheckVsBypass(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    if(ScalerDrrIVSProduceByBE(enumSourceType, enumInputPort) == _TRUE)
    {
        // When DRR IVS produce by BE, skip VS bypass check
        return _FALSE;
    }
#endif

#if(_HDMI_SUPPORT == _ON)
    EnumDeOnlyConfig enumDeOnlyConfig = ScalerTmdsMacRxGetDeOnlyModeConfig(enumInputPort);
#endif

    enumInputPort = enumInputPort;

    switch(enumSourceType)
    {
#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:
            return ScalerDpMacStreamRxCheckVgipVsBypass(enumInputPort);
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
            if((enumDeOnlyConfig & _DE_ONLY_ENABLE) == _DE_ONLY_ENABLE)
            {
                if((GET_INPUT_TIMING_HTOTAL() > GET_INPUT_TIMING_HWIDTH()) &&
                   (GET_INPUT_TIMING_VTOTAL() > GET_INPUT_TIMING_VHEIGHT()))
                {
                    if(((GET_INPUT_TIMING_HTOTAL() - GET_INPUT_TIMING_HWIDTH()) < _VGIP_IH_CAPTURE_MIN_VALUE + _TMDS_D_ONLY_MODE_H_FRONT_PORCH) ||
                       ((GET_INPUT_TIMING_VTOTAL() - GET_INPUT_TIMING_VHEIGHT()) <= _VGIP_IV_CAPTURE_MIN_VALUE + _TMDS_D_ONLY_MODE_V_FRONT_PORCH))
                    {
                        DebugMessageMeasure("DVI/HDMI: VGIP VS Bypass Mode", 0);
                        return _TRUE;
                    }
                }
                else
                {
                    DebugMessageMeasure("DVI/HDMI: VGIP VS Bypass Mode", 0);
                    return _TRUE;
                }
            }

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check on-line measure watchdog status
// Input Value  : ucRegionIndex --> region index
// Output Value : _TRUE if watchdog is triggered
//--------------------------------------------------
bit ScalerMeasureCheckWDTriggerStatus(BYTE ucRegionIndex)
{
    EnumInputDataPath enumTargetPath = g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.enumInputDataPath;
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumTargetPath);

    // Check over-range watchdog
    BYTE ucTriggered = ((GET_PAGED_BIT(ucMeasurePage, P3_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
                        (GET_PAGED_BIT(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))));

    if(ucTriggered != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Setting for off-line measure in measure flow
// Input Value  : enumInputPort --> target input port
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetOfflineMeasure(EnumInputPort enumInputPort)
{
#if(_HW_IDOMAIN_OFFLINE_MEASURE_CLK_DIV_SUPPORT == _ON)
    // Reset off-line measure clock divider
    ScalerSetBit(P30_00_SYNC_SELECT, ~_BIT7, 0x00);
#endif

    // Power up off-line measure; Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
    ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT0), (_BIT7 | _BIT6));

    // Disable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Set Off-line measure source
    ScalerMeasureSetOfflineMeasureSource(enumInputPort);

#if((_DP_SUPPORT == _ON) && (_FW_ONESHOT_MODE_SUPPORT == _ON))
    // DP Frame sync BE Mode case
    if((ScalerSyncGetPortType(enumInputPort) == _PORT_DP) &&
       (ScalerDpMacStreamRxGetDPFRegenMode(enumInputPort) == _DPF_MODE_FRAME_SYNC_BE))
    {
        // Enable Off-line measure oneshot mode
        ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }
    else
    {
        // Disable Off-line measure oneshot mode
        ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT2 | _BIT1), 0x00);
    }
#endif

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
    // Enable off-line Hstart/Vstart measure & Clear error flag
    ScalerSetBit(_MEASURE_OFFLINE_START_REG, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
#endif
}

//--------------------------------------------------
// Description  : Get off-line measure result from target input data path
// Input Value  : pstMeasureSyncHV --> measure result pointer
//                enumInputPort --> input port
// Output Value : _TRUE if measure passed
//--------------------------------------------------
bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, P30_02_MEAS_CTL1, _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
    if(ScalerGetBit(_MEASURE_OFFLINE_START_REG, _BIT6) == _BIT6)
    {
        // Clear Hstart change flag
        ScalerSetBit(_MEASURE_OFFLINE_START_REG, ~_BIT6, _BIT6);
    }
#endif

    // Check measure result status
#if(_VGA_SUPPORT == _ON)
    if(ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT1 | _BIT0))
    {
        if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4)) != 0x00)
        {
            return _FALSE;
        }
    }
    else
#endif
    {
#if(_DRR_SUPPORT == _ON)
        if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
        {
            // Check measure result status
            if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check measure result status
            if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
            {
                return _FALSE;
            }
        }
    }

    // Pop up measurement result
    ScalerSetBit(P30_02_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P30_04_MEAS_ERROR_FLG1, _BIT6);
    pstMeasureSyncHV->b1VSP = (bit)ScalerGetBit(P30_04_MEAS_ERROR_FLG1, _BIT7);

#if((_DP_SUPPORT == _ON) && (_FW_ONESHOT_MODE_SUPPORT == _OFF))
    if((ScalerSyncGetPortType(enumInputPort) == _PORT_DP) &&
       (ScalerDpMacStreamRxGetDPFRegenMode(enumInputPort) == _DPF_MODE_FRAME_SYNC_BE))
    {
        // HSync Period
        pstMeasureSyncHV->usHSPeriod = ((DWORD)ScalerDpMacStreamRxGetHSPeriod(enumInputPort) * _MEASURE_CLK / 1000000);

        // HSync Pulse Width
        pstMeasureSyncHV->usHSWidth = ScalerDpMacStreamRxGetHSW(enumInputPort);

        // VSync Period
        pstMeasureSyncHV->usVSPeriod = ScalerDpMacStreamRxGetVSPeriod(enumInputPort);

        if((pstMeasureSyncHV->usHSPeriod == 0x00) ||
           (pstMeasureSyncHV->usHSWidth == 0x00) ||
           (pstMeasureSyncHV->usVSPeriod == 0x00))
        {
            // Get DP HSPeriod/HSWidth/VSPeriod info fail
            return _FALSE;
        }
    }
    else
#endif
    {
        // HSync Period
        pstMeasureSyncHV->usHSPeriod = (((((WORD)ScalerGetByte(P30_05_MEAS_HS_PERIOD_A_M)) << 8) | (ScalerGetByte(P30_06_MEAS_HS_PERIOD_A_L))) & _HW_MEASURE_H_BIT) + 1;

        // HSync Pulse Width
        pstMeasureSyncHV->usHSWidth = (((((WORD)ScalerGetByte(P30_0A_MEAS_HS_PULSE_A_M)) << 8) | (ScalerGetByte(P30_0B_MEAS_HS_PULSE_A_L))) & _HW_MEASURE_H_BIT) + 1;

        // VSync Period
        pstMeasureSyncHV->usVSPeriod = (((((WORD)ScalerGetByte(P30_08_MEAS_VS_PERIOD_A_M)) << 8) | (ScalerGetByte(P30_09_MEAS_VS_PERIOD_A_L))) & _HW_MEASURE_V_BIT) + 1;
    }

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = (((((WORD)ScalerGetByte(P30_0C_MEAS_VS_PULSE_A_M)) << 8) | (ScalerGetByte(P30_0D_MEAS_VS_PULSE_A_L))) & _HW_MEASURE_V_BIT) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = (((((WORD)ScalerGetByte(P30_0E_MEAS_HS_PERIOD_D_M)) << 8) | (ScalerGetByte(P30_0F_MEAS_HS_PERIOD_D_L))) & _HW_MEASURE_H_BIT) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = (((((WORD)ScalerGetByte(P30_11_MEAS_VS_PERIOD_D_M)) << 8) | (ScalerGetByte(P30_12_MEAS_VS_PERIOD_D_L))) & _HW_MEASURE_V_BIT) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = (((((WORD)ScalerGetByte(P30_13_MEAS_HS_PULSE_D_M)) << 8) | (ScalerGetByte(P30_14_MEAS_HS_PULSE_D_L))) & _HW_MEASURE_H_BIT) + 1;

#if(_HW_IDOMAIN_OFFLINE_MEASURE_CLK_DIV_SUPPORT == _ON)
    // Resume original clock when clock divider enabled
    if(ScalerGetBit(P30_00_SYNC_SELECT, _BIT7) == _BIT7)
    {
        pstMeasureSyncHV->usHTotal = (pstMeasureSyncHV->usHTotal << 1);
        pstMeasureSyncHV->usHWidth = (pstMeasureSyncHV->usHWidth << 1);
    }
#endif

    // HSync Pulse Width (unit: pixel)
    pstMeasureSyncHV->usHSWidth = pstMeasureSyncHV->usHSWidth * pstMeasureSyncHV->usHTotal / pstMeasureSyncHV->usHSPeriod;

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
    // H Start (measure count from 1)
    pstMeasureSyncHV->usHStart = (((((WORD)ScalerGetBit(_MEASURE_OFFLINE_START_REG, 0x1F)) << 8) | (ScalerGetByte(_MEASURE_OFFLINE_HSTART_RESULT_REG))) & _HW_MEASURE_H_BIT);
#endif
#if(_HW_IDOMAIN_OFFLINE_VSTART_MEASURE_SUPPORT == _ON)
    pstMeasureSyncHV->usVStart = (((((WORD)ScalerGetBit(P30_22_MEAS_VSTART_RESULT_H, 0x1F)) << 8) | (ScalerGetByte(P30_23_MEAS_VSTART_RESULT_L))) & _HW_MEASURE_V_BIT);
#endif

#if(_VGA_SUPPORT == _ON)
    if((ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT1 | _BIT0)) ||
       (ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2)))
    {
        if(ScalerMeasureGetVgaStableMeasureResult(pstMeasureSyncHV) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Double check off-line measure result
// Input Value  : enumSourceType --> input source type
//                enumInputPort --> input port
// Output Value : _TRUE if double check passed
//--------------------------------------------------
bit ScalerMeasureOfflineMeasureDoubleCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    StructMeasureSyncData stMeasureSyncHV = {0};

    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

#if(_VGA_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_VGA)
    {
        if((ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncHV, enumInputPort) == _FALSE) ||
           (stMeasureSyncHV.b1HSP != g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.b1HSP) ||
           (abs(stMeasureSyncHV.usHSPeriod - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHSPeriod) > 0x02) ||
           (abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVSPeriod) > 0x02))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        BYTE ucMeasureHSPeriodMaxChange = 2;

#if(_DP_SUPPORT == _ON)
        if(enumSourceType == _SOURCE_DP)
        {
            ucMeasureHSPeriodMaxChange = _MEASURE_DP_H_PERIOD_MAX_CHANGE;
        }
#endif

        if((ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncHV, enumInputPort) == _FALSE) ||
           (stMeasureSyncHV.b1HSP != g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.b1HSP) ||
           (stMeasureSyncHV.b1VSP != g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.b1VSP) ||
           (abs(stMeasureSyncHV.usHWidth - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHWidth) > 0x02) ||
           (abs(stMeasureSyncHV.usVHeight - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVHeight) > 0x02))
        {
            return _FALSE;
        }

#if(_DRR_SUPPORT == _ON)
        if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
        {
            return _TRUE;
        }
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
        if((enumSourceType == _SOURCE_HDMI) &&
           (ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC))
        {
            // HDMI2.1 Line syne mode don't check HS period
            return _TRUE;
        }
#endif

        if((abs(stMeasureSyncHV.usHTotal - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHTotal) > 0x02) ||
           (abs(stMeasureSyncHV.usHSPeriod - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHSPeriod) > ucMeasureHSPeriodMaxChange) ||
           (abs(stMeasureSyncHV.usVSPeriod - g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVSPeriod) > 0x02))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set on-line measure block for target input data path
// Input Value  : enumInputDataPath -> input data path
//                usIVFreq --> measured V frequency for measure timeout setting
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetOnlineMeasure(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath, WORD usIVFreq)
{
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumInputDataPath);

    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

    // Disable on-line measure
    SET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Disable over-range enable bit
    SET_PAGED_BIT(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Clear over-range bit
    SET_PAGED_BIT(ucMeasurePage, P3_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
    {
        // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
        SET_PAGED_BIT(ucMeasurePage, P3_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

        // Set over-range condition: HS = 16, VS = N/A, HSW = 16
        SET_PAGED_BYTE(ucMeasurePage, P3_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT2 | _BIT0));
    }
    else
#endif
    {
        // Calculate measure timeout period
        PDATA_WORD(0) = _MEASURE_CLK / 512 * 10000 / 2048;
        PDATA_WORD(1) = (PDATA_WORD(0) + (PDATA_WORD(0) >> 2)); // 1.5x margin

        if(usIVFreq > PDATA_WORD(1))
        {
            // Measure Time Clock = 2048 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucMeasurePage, P3_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), 0x00);
        }
        else if(usIVFreq > (PDATA_WORD(1) >> 1))
        {
            // Measure Time Clock = 4096 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucMeasurePage, P3_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT6);
        }
        else if(usIVFreq > (PDATA_WORD(1) >> 2))
        {
            // Measure Time Clock = 8192 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucMeasurePage, P3_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT7);
        }
        else
        {
            // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucMeasurePage, P3_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));
        }

#if(_HDMI_FRL_SUPPORT == _ON)
        if((enumSourceType == _SOURCE_HDMI) &&
           (ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC))
        {
            // HDMI2.1 Link sync mode don't check HS period
            // Set over-range condition: HS = don't care, VS = 4, HSW = 16
            SET_PAGED_BYTE(ucMeasurePage, P3_15_MEAS_HS_VS_DELTA_CTL, (_BIT4 | _BIT3 | _BIT2 | _BIT0));
        }
        else
#endif
        {
            // Set over-range condition: HS = 16, VS = 4, HSW = 16
            SET_PAGED_BYTE(ucMeasurePage, P3_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0));
        }
    }

#if((_DP_SUPPORT == _ON) && (_FW_ONESHOT_MODE_SUPPORT == _ON))
    // DP Frame sync BE Mode case
    if((ScalerSyncGetPortType(enumInputPort) == _PORT_DP) &&
       (ScalerDpMacStreamRxGetDPFRegenMode(enumInputPort) == _DPF_MODE_FRAME_SYNC_BE))
    {
        // Enable online measure oneshot mode
        SET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }
    else
    {
        // Disable online measure oneshot mode
        SET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, ~(_BIT2 | _BIT1), 0x00);
    }
#endif

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable on-line measure
    SET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
}

//--------------------------------------------------
// Description  : Get on-line measure result from target input data path
// Input Value  : pstMeasureSyncHV --> measure result pointer
//                enumInputPort --> input port
// Output Value : _TRUE if on-line measure passed
//--------------------------------------------------
bit ScalerMeasureGetOnlineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputDataPath enumInputDataPath)
{
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumInputDataPath);

    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, GET_PAGED_ADDR(ucMeasurePage, P3_02_MEAS_CTL1), _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

#if((_DP_SUPPORT == _ON) && (_FW_ONESHOT_MODE_SUPPORT == _OFF))
    if((ScalerSyncGetPortType(ScalerFmtCnvGetInputPortType(enumInputDataPath)) == _PORT_DP) &&
       (ScalerDpMacStreamRxGetDPFRegenMode(ScalerFmtCnvGetInputPortType(enumInputDataPath)) != _DPF_MODE_FRAME_SYNC_BE))
#endif
    {
        // Check measure result status
        if(GET_PAGED_BIT(ucMeasurePage, P3_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4)) != 0x00)
        {
            return _FALSE;
        }
    }

    // Pop up measurement result
    SET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)GET_PAGED_BIT(ucMeasurePage, P3_04_MEAS_ERROR_FLG1, _BIT6);
    pstMeasureSyncHV->b1VSP = (bit)GET_PAGED_BIT(ucMeasurePage, P3_04_MEAS_ERROR_FLG1, _BIT7);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_05_MEAS_HS_PERIOD_A_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_06_MEAS_HS_PERIOD_A_L))) & _HW_MEASURE_H_BIT) + 1;

    // VSync Period
    pstMeasureSyncHV->usVSPeriod = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_08_MEAS_VS_PERIOD_A_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_09_MEAS_VS_PERIOD_A_L))) & _HW_MEASURE_V_BIT) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_0A_MEAS_HS_PULSE_A_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_0B_MEAS_HS_PULSE_A_L))) & _HW_MEASURE_H_BIT) + 1;

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_0C_MEAS_VS_PULSE_A_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_0D_MEAS_VS_PULSE_A_L))) & _HW_MEASURE_V_BIT) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_0E_MEAS_HS_PERIOD_D_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_0F_MEAS_HS_PERIOD_D_L))) & _HW_MEASURE_H_BIT) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_11_MEAS_VS_PERIOD_D_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_12_MEAS_VS_PERIOD_D_L))) & _HW_MEASURE_V_BIT) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = (((((WORD)GET_PAGED_BYTE(ucMeasurePage, P3_13_MEAS_HS_PULSE_D_M)) << 8) | (GET_PAGED_BYTE(ucMeasurePage, P3_14_MEAS_HS_PULSE_D_L))) & _HW_MEASURE_H_BIT) + 1;

#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType(enumInputDataPath) == _FC_SOURCE_ADC)
    {
        if(ScalerMeasureGetVgaStableMeasureResult(pstMeasureSyncHV) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Initialization for auto-function in measure flow
// Input Value  : enumMeasureFieldSelect --> Measure for Even or Odd Field
//                enumInputDataPath --> auto data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumInputDataPath enumInputDataPath)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

    // Disable auto-function
    SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Set auto VS delay to 0
    SET_PAGED_BYTE(ucIDomainPage, P0_1E_M1_VGIP_HV_DELAY, GET_PAGED_BYTE(ucIDomainPage, P0_1E_M1_VGIP_HV_DELAY) & ~(_BIT5 | _BIT4));

    if(enumFieldSelect == _EVEN_FIELD_MEASURE)
    {
        // Field Select to Even, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        SET_PAGED_BYTE(ucIDomainPage, P0_7A_AUTO_ADJ_CTRL0, 0x80);
    }
    else if(enumFieldSelect == _ODD_FIELD_MEASURE)
    {
        // Field Select to Odd, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        SET_PAGED_BYTE(ucIDomainPage, P0_7A_AUTO_ADJ_CTRL0, 0xC0);
    }
    else
    {
        // Disable Field Select, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        SET_PAGED_BYTE(ucIDomainPage, P0_7A_AUTO_ADJ_CTRL0, 0x00);
    }

    // Set HW auto-phase: step = 32
    SET_PAGED_BYTE(ucIDomainPage, P0_7B_HW_AUTO_PHASE_CTRL0, 0xF8);

    // Set H boundary
    ScalerMeasureSetAutoFuncHBoundary(0x0002, 0x1FFF, enumInputDataPath);

    // Set V Boundary
    ScalerMeasureSetAutoFuncVBoundary(0x0000, 0x1FFF, enumInputDataPath);

    // Digital Measure Mode, Select Auto Balance, Start Auto Function Measure; Start auto-function measure
    SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
}

//--------------------------------------------------
// Description  : Waiting for auto-function to finish
// Input Value  : enumInputDataPath --> auto data path
// Output Value : _TRUE if measure fininshs correctly
//--------------------------------------------------
bit ScalerMeasureAutoFuncWaitFinish(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIvsCnt = 0;
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

    ucIvsCnt = (GET_PAGED_BIT(ucIDomainPage, P0_7A_AUTO_ADJ_CTRL0, _BIT1 | _BIT0) == 0x03) ? 3 : 1;
    ucIvsCnt = (GET_PAGED_BIT(ucIDomainPage, P0_7A_AUTO_ADJ_CTRL0, _BIT7) == _BIT7) ? ucIvsCnt * 2 : ucIvsCnt;
    ucIvsCnt += 2;

    do
    {
        // polling flag check measure finished or not
        if(GET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            return _TRUE;
        }

        // wait for IVS
        if(ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath) == _FALSE)
        {
            return _FALSE;
        }
    }
    while(--ucIvsCnt);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set H boundary for auto-function
// Input Value  : usHBoundStart -> H Boundary start
// Input Value  : usHBoundEnd -> H Boundary end
//                enumInputDataPath --> auto data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetAutoFuncHBoundary(WORD usHBoundStart, WORD usHBoundEnd, EnumInputDataPath enumInputDataPath)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

    // Set H boundary
    SET_PAGED_BYTE(ucIDomainPage, P0_70_H_BOUNDARY_H, (((HIBYTE(usHBoundStart) & 0x0F) << 4) | (HIBYTE(usHBoundEnd) & 0x0F)));
    SET_PAGED_BYTE(ucIDomainPage, P0_71_H_BOUNDARY_STA_L, LOBYTE(usHBoundStart));
    SET_PAGED_BYTE(ucIDomainPage, P0_72_H_BOUNDARY_END_L, LOBYTE(usHBoundEnd));

    SET_PAGED_BIT(ucIDomainPage, P0_77_GRN_NOISE_MARGIN, ~_BIT1, ((HIBYTE(usHBoundStart) >> 3) & _BIT1));
    SET_PAGED_BIT(ucIDomainPage, P0_77_GRN_NOISE_MARGIN, ~_BIT0, ((HIBYTE(usHBoundEnd) >> 4) & _BIT0));
}

//--------------------------------------------------
// Description  : Set V boundary for auto-function
// Input Value  : usVBoundStart -> V Boundary start
// Input Value  : usVBoundEnd -> V Boundary end
//                enumInputDataPath --> auto data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetAutoFuncVBoundary(WORD usVBoundStart, WORD usVBoundEnd, EnumInputDataPath enumInputDataPath)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

    // Set V boundary
    SET_PAGED_BIT(ucIDomainPage, P0_7C_AUTO_DUMMY, ~(_BIT3 | _BIT2), (((HIBYTE(usVBoundStart) & 0x10) >> 1) | ((HIBYTE(usVBoundEnd) & 0x10) >> 2)));
    SET_PAGED_BYTE(ucIDomainPage, P0_73_V_BOUNDARY_H, (((HIBYTE(usVBoundStart) & 0x0F) << 4) | (HIBYTE(usVBoundEnd) & 0x0F)));
    SET_PAGED_BYTE(ucIDomainPage, P0_74_V_BOUNDARY_STA_L, LOBYTE(usVBoundStart));
    SET_PAGED_BYTE(ucIDomainPage, P0_75_V_BOUNDARY_END_L, LOBYTE(usVBoundEnd));
}

//--------------------------------------------------
// Description  : Get auto-function boundary measure result
// Input Value  : pstActiveRegion --> measure result pointer
//                enumInputDataPath --> auto data path
//                bWait --> wait auto-function stop or not
// Output Value : _TRUE if auto-function measure passed
//--------------------------------------------------
bit ScalerMeasureGetAutoBoundaryResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath, bit bWait)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

    if((bWait == _WAIT) || (GET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, _BIT6) == 0x00))
    {
        if(ScalerMeasureAutoFuncWaitFinish(enumInputDataPath) == _FALSE)
        {
            return _FALSE;
        }
    }

    pstActiveRegion->usVActiveStart = (((WORD)GET_PAGED_BIT(ucIDomainPage, P0_7C_AUTO_DUMMY, _BIT1) << 11) |
                                       ((WORD)GET_PAGED_BIT(ucIDomainPage, P0_7E_VER_START_END_H, 0xF0) << 4) |
                                       ((WORD)GET_PAGED_BYTE(ucIDomainPage, P0_7F_VER_START_L)));

    pstActiveRegion->usVActiveEnd = (((WORD)GET_PAGED_BIT(ucIDomainPage, P0_7C_AUTO_DUMMY, _BIT0) << 12) |
                                     ((WORD)GET_PAGED_BIT(ucIDomainPage, P0_7E_VER_START_END_H, 0x0F) << 8) |
                                     ((WORD)GET_PAGED_BYTE(ucIDomainPage, P0_80_VER_END_L)));

    pstActiveRegion->usHActiveStart = (((WORD)GET_PAGED_BIT(ucIDomainPage, P0_78_BLU_NOISE_MARGIN, _BIT1) << 11) |
                                       ((WORD)GET_PAGED_BIT(ucIDomainPage, P0_81_H_START_END_H, 0xF0) << 4) |
                                       ((WORD)GET_PAGED_BYTE(ucIDomainPage, P0_82_H_START_L))) + 1;

    pstActiveRegion->usHActiveEnd = (((WORD)GET_PAGED_BIT(ucIDomainPage, P0_78_BLU_NOISE_MARGIN, _BIT0) << 12) |
                                     ((WORD)GET_PAGED_BIT(ucIDomainPage, P0_81_H_START_END_H, 0x0F) << 8) |
                                     ((WORD)GET_PAGED_BYTE(ucIDomainPage, P0_83_H_END_L))) + 1;

    // Check auto-function measure result
    if(((pstActiveRegion->usVActiveStart == 0x00) &&
        (pstActiveRegion->usVActiveEnd == 0x00)) ||
       (pstActiveRegion->usHActiveStart == 0x00) ||
       (pstActiveRegion->usHActiveEnd == 0x00))
    {
        // No IDEN found.
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check auto-function boundary measure result
// Input Value  : pstActiveRegion --> measure result pointer
//                enumInputDataPath --> auto data path
// Output Value : _TRUE if auto-function measure passed
//--------------------------------------------------
bit ScalerMeasureCheckAutoBoundaryResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath)
{
    BYTE ucHwidthFactor = 0x01;
    BYTE ucVheightFactor = 0x01;
    BYTE ucHwidthFBFactor = 0x01;
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

    WORD usAutoHwidth = GET_INPUT_TIMING_HWIDTH();
    WORD usAutoVheight = GET_INPUT_TIMING_VHEIGHT();

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    BYTE ucHPixelModeTargetFactor = ScalerFmtCnvGetPixelModeTargetFactor(enumInputDataPath);
    BYTE ucHPixelModeFactor = ScalerFmtCnvGetPixelModeFactor(enumInputDataPath);
#endif
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    BYTE ucHSDFactor = ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif
#endif

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Apply horizontal fix for pixel mode
    ucHwidthFactor *= ucHPixelModeTargetFactor;
    ucHwidthFactor /= ucHPixelModeFactor;
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    // Fix vertical resolution for even/odd
    if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
        {
            if(ScalerFmtCnvFBGetFBModeStatus() == _TRUE)
            {
                ucHwidthFBFactor *= 2;
            }
        }
#endif
        ucVheightFactor *= 2;
    }
#endif
#endif

    if((abs(GET_SYNC_H_WIDTH() - (GET_INPUT_TIMING_HWIDTH() / ucHwidthFactor)) > 2) ||
       (abs(GET_SYNC_V_HEIGHT() - GET_INPUT_TIMING_VHEIGHT()) > 2))
    {
        SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~(_BIT0), (_BIT0));

        // Wait for 2 latched IVS; Pop out auto-function result
        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath) == _FALSE) ||
           (ScalerMeasureGetAutoBoundaryResult(pstActiveRegion, enumInputDataPath, _NOT_WAIT) == _FALSE))
        {
            return _FALSE;
        }

        usAutoHwidth = ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1);
        usAutoVheight = ((pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1);

        if((abs(GET_SYNC_H_WIDTH() - (usAutoHwidth / ucHwidthFactor * ucHSDFactor * ucHwidthFBFactor)) > 2) ||
           (abs(GET_SYNC_V_HEIGHT() - (usAutoVheight * ucVheightFactor)) > 2))
        {
            DebugMessageMeasure("[Careful] Auto Boundary Result dismatch Offline Measure Result!!!", usAutoHwidth);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Initialaztion for interlace detection in measure flow
// Input Value  : enumSourceType --> source Type
//                enumInputPort --> input port
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInterlaceInitial(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if((GET_MEASURE_INPUT_PATH() & enumCurrPath) != 0x00)
        {
            // Disable IVS Delay one line; Default field source from interface
            SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucIdomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Clear Interlace toggle flag
            ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            break;
#endif

#if(_HDMI_SUPPORT == _ON)

        case _SOURCE_DVI:
        case _SOURCE_HDMI:
            ScalerTmdsMacRxInterlaceCheckPreset(enumInputPort);

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Detect if current input is interlaced timing
// Input Value  : enumSourceType --> input source Type
//                enumInputPort --> input port type
// Output Value : TRUE for interfaced format
//--------------------------------------------------
bit ScalerMeasureInterlaceCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(GET_MEASURE_INPUT_PATH());
    bit bInterlacedFormat = _FALSE;

    enumInputPort = enumInputPort;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            bInterlacedFormat = (ScalerMeasureVgaInterlaceCheck(enumInputPort) == _TRUE);

            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            bInterlacedFormat = ScalerMeasureTmdsInterlaceCheck(enumInputPort, ucIDomainPage);

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            bInterlacedFormat = ScalerMeasureDpInterlaceCheck(enumInputPort, ucIDomainPage);

            break;
#endif

        default:
            break;
    }

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
    {
        // Align M2 field source with M1
        ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~_BIT0, ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT0));
    }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_M1_M2_S1_S2)
        {
            // Align S1/S2 field source with M1/M2
            ScalerSetByte(P80_13_S1_VGIP_ODD_CTRL, ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL));
            ScalerSetByte(PC0_13_S2_VGIP_ODD_CTRL, ScalerGetByte(P40_13_M2_VGIP_ODD_CTRL));
            ScalerSetByte(PC0_32_SCALE_CONTROL_REG_R3_ACTIVE1, ScalerGetByte(P0_32_SCALE_CONTROL_REG_R1_ACTIVE1));
            ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
    {
        // Align S2 field source with S1
        ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~_BIT0, ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT0));
    }
#endif

#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S3_S4) == _INPUT_PATH_S3_S4)
    {
        // Align S4 field source with S3
        ScalerSetBit(PDC_13_S4_VGIP_ODD_CTRL, ~_BIT0, ScalerGetBit(P17_13_S3_VGIP_ODD_CTRL, _BIT0));
    }
#endif

    return bInterlacedFormat;
}

//--------------------------------------------------
// Description  : Detect if current input is interlaced timing for double-check. Should not change register setting.
// Input Value  : enumSourceType --> input source Type
//                enumInputPort --> input port type
//                enumRegionIndex -> target region index
// Output Value : TRUE for interfaced format
//--------------------------------------------------
bit ScalerMeasureInterlaceDoubleCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex)
{
#if(_HDMI_SUPPORT == _ON)
    BYTE ucHdmiPage = 0;
#endif
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.enumInputDataPath);

    enumInputPort = enumInputPort;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            return g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.b1Interlace;
#endif

#if(_HDMI_SUPPORT == _ON)

        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            ucHdmiPage = ScalerMeasureGetTmdsPage(enumInputPort);

            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Clear Interlace toggle flag
            ScalerSetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.enumInputDataPath);
            ScalerTimerWaitForIDomainEvent(_EVENT_IVS, g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.enumInputDataPath);

#if(_HDMI_FRL_SUPPORT == _ON)
            // HDMI2.1 Interlace
            if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC)
            {
                if(ScalerHdmiFrlMacRxInterlaceModeCheck(enumInputPort) == _TRUE)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            // HDMI2.0 Interlace
            else
#endif
            {
#if(_DVI_DE_ONLY_SUPPORT == _ON)
                if(GET_PAGED_BIT(ucHdmiPage, P72_A4_TMDS_CTRL, (_BIT4 | _BIT3)) != (_BIT4 | _BIT3))
                {
                    // Detect by Vtotal
                    if(GET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                    {
                        // Clear VGIP Interlace Toggle Flag
                        SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                        return _TRUE;
                    }
                }
                else
#endif
                {
                    // Detect by VS Position
                    if(ScalerGetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, _BIT6) == _BIT6)
                    {
                        if(ScalerGetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, _BIT5) == 0x00)
                        {
                            // Clear Interlace toggle flag
                            ScalerSetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));
                            return _TRUE;
                        }
                        else
                        {
                            // Clear Interlace toggle and error flag
                            ScalerSetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));
                        }
                    }
                }
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)

        case _SOURCE_DP:

            if(ScalerDpMacStreamRxInterlaceModeConfig(enumInputPort, _REF_VBID) == _ENABLE)
            {
                return _TRUE;
            }

            if(ScalerDpMacStreamRxInterlaceModeConfig(enumInputPort, _REF_BS_COUNTER) == _ENABLE)
            {
                // Check if field single is from VGIP
                if(GET_PAGED_BIT(ucIDomainPage, P0_13_M1_VGIP_ODD_CTRL, _BIT0) == _BIT0)
                {
                    if(GET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                    {
                        // Clear VGIP Interlace Toggle Flag
                        SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                        return _TRUE;
                    }
                }
                else
                {
                    return _TRUE;
                }
            }

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Update auto-function result to current timing info
// Input Value  : None
// Output Value : _TRUE if update passed
//--------------------------------------------------
bit ScalerMeasureUpdateAutoPosition(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    // Set auto-function digital measure
    ScalerMeasureSetAuto(_NORMAL_MEASURE, GET_MEASURE_INPUT_PATH());

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Wait for 2 latched IVS; Pop out auto-function result
    if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerMeasureGetAutoBoundaryResult(&(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), GET_MEASURE_INPUT_PATH(), _NOT_WAIT) == _FALSE))
    {
        DebugMessageMeasure("Digital auto-function fail", 0x00);
        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), enumSourceType, enumInputPort);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update H timing info from measure
// Input Value  : pstMeasureSyncHV --> measure result
//                pstActiveRegion --> auto-function result
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputHorizontalTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion)
{
    BYTE ucHtotalFactor = 1;
    BYTE ucHwidthFactor = 1;
    BYTE ucHstartFactor = 1;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    BYTE ucHPixelModeTargetFactor = ScalerFmtCnvGetPixelModeTargetFactor(GET_MEASURE_INPUT_PATH());
    BYTE ucHPixelModeFactor = ScalerFmtCnvGetPixelModeFactor(GET_MEASURE_INPUT_PATH());
#endif
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    BYTE ucHSDFactor = ScalerFmtCnvHalfSDGetFactor(GET_MEASURE_INPUT_PATH());
#endif
#endif

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Apply horizontal fix for pixel mode
    ucHtotalFactor *= ucHPixelModeTargetFactor;
    ucHstartFactor *= ucHPixelModeTargetFactor;
    ucHwidthFactor *= ucHPixelModeTargetFactor;

    ucHstartFactor /= ucHPixelModeFactor;
    ucHwidthFactor /= ucHPixelModeFactor;
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    // Apply horizontal fix for 1/2 SD mode
    ucHstartFactor *= ucHSDFactor;
    ucHwidthFactor *= ucHSDFactor;
#endif

#if(_COLOR_IP_420_SUPPORT == _ON)
    // Check 420 cases for H total
    if(ScalerColor420To422GetStatusByPath(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        ucHtotalFactor *= 2;
    }
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        ucHstartFactor *= 2;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_M1_M2_S1_S2)
        {
            if(ScalerFmtCnvFBGetFBModeStatus() == _TRUE)
            {
                ucHwidthFactor *= 2;
            }
        }
#endif
    }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_M1_M2_S1_S2)
    {
        if(ScalerFmtCnvFBGetFBModeStatus() == _TRUE)
        {
            // Update H total for single-to-F/B mode
            if(ScalerFmtCnvFBGetFullToFBStatus() == _FALSE)
            {
                ucHtotalFactor *= 2;
            }
        }
    }
#endif
#endif

    SET_INPUT_TIMING_HTOTAL(ucHtotalFactor * pstMeasureSyncHV->usHTotal);
    SET_INPUT_TIMING_HSYNCWIDTH(ucHtotalFactor * pstMeasureSyncHV->usHSWidth);
    SET_INPUT_TIMING_HSTART(ucHstartFactor * pstActiveRegion->usHActiveStart);
    SET_INPUT_TIMING_HWIDTH(ucHwidthFactor * ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1));

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
    if((ScalerFmtCnvEagleSightEffectStatus(GET_MEASURE_INPUT_PATH()) == _FC_EAGLE_SIGHT_ENABLE) &&
       (ScalerFmtCnvEagleSightGetPixelMode() > _FC_1_PIXEL_MODE))
    {
        SET_INPUT_TIMING_HTOTAL(GET_INPUT_TIMING_HTOTAL() / 2);
        SET_INPUT_TIMING_HSYNCWIDTH(GET_INPUT_TIMING_HSYNCWIDTH() / 2);
    }
#endif
}

//--------------------------------------------------
// Description  : Update V timing info from measure
// Input Value  : pstMeasureSyncHV --> measure result
//                pstActiveRegion --> auto-function result
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputVerticalTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion, EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    BYTE ucVFactor = 1;
    BYTE ucVstartOffset = 0;

    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
    bit bMeasureInfoFromInterface = (ScalerSyncGetVerticalTimingDataFromInterface(enumSourceType, enumInputPort) == _TRUE);
#if(_COLOR_IP_3DDI == _ON)
    bMeasureInfoFromInterface &= (GET_3DDI_STATUS(GET_MEASURE_INPUT_PATH()) == _FALSE);
#endif

    if(bMeasureInfoFromInterface == _TRUE)
    {
        BYTE ucVSDelayLine = 0;
        BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(GET_MEASURE_INPUT_PATH());
        StructInterfaceTimingInfo stInterfaceTimingData;
        memset(&stInterfaceTimingData, 0, sizeof(stInterfaceTimingData));

#if(_HDMI_SUPPORT == _ON)
        if(enumSourceType == _SOURCE_HDMI)
        {
            switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
            {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
                case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_MAC)
                    {
                        stInterfaceTimingData.usVStart = (WORD)(GET_HDMI_FRL_MAC_RX3_VBACK() + GET_HDMI_FRL_MAC_RX3_VSYNC());
                        stInterfaceTimingData.usVActive = (WORD)GET_HDMI_FRL_MAC_RX3_VACTIVE();
                    }
#endif
                    break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
                case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) == _FROM_HDMI_FRL_MAC)
                    {
                        stInterfaceTimingData.usVStart = (WORD)(GET_HDMI_FRL_MAC_RX4_VBACK() + GET_HDMI_FRL_MAC_RX4_VSYNC());
                        stInterfaceTimingData.usVActive = (WORD)GET_HDMI_FRL_MAC_RX4_VACTIVE();
                    }
#endif
                    break;
#endif
                default:
                    break;
            }
        }
#endif

        if(ScalerFmtCnvFtoPGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
        {
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
            switch(GET_MEASURE_INPUT_PATH())
            {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                case _INPUT_PATH_M1_M2_S1_S2:
#endif
                case _INPUT_PATH_M1_M2:

                    if(ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, _BIT1) == _BIT1)
                    {
                        ucVSDelayLine = (((ScalerGetBit(P31_0F_VS_DELAY_CTRL, (_BIT5 | _BIT4)) >> 4) + 1) << 1);
                    }
                    break;

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) &&\
            (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
                case _INPUT_PATH_S1_S2:
                    if(ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, _BIT0) == _BIT0)
                    {
                        ucVSDelayLine = ((ScalerGetBit(P31_0F_VS_DELAY_CTRL, (_BIT1 | _BIT0)) + 1) << 1);
                    }
                    break;
#endif

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) &&\
            (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
                case _INPUT_PATH_S3_S4:
                    if(ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, _BIT0) == _BIT0)
                    {
                        ucVSDelayLine = (((ScalerGetBit(P31_0F_VS_DELAY_CTRL, (_BIT3 | _BIT2)) >> 2) + 1) << 1);
                    }
                    break;
#endif

                default:
                    break;
            }
#endif
            if(stInterfaceTimingData.usVStart > ucVSDelayLine)
            {
                SET_INPUT_TIMING_VSTART(stInterfaceTimingData.usVStart - ucVSDelayLine);
            }
            else
            {
                SET_INPUT_TIMING_VSTART(0);
            }
        }
        else
        {
            if(stInterfaceTimingData.usVStart > 1)
            {
                if(GET_PAGED_BIT(ucIDomainPage, P0_11_M1_VGIP_SIGINV, _BIT6) == 0x00)
                {
                    // After VIGP, Vsync delay 1 line
                    SET_INPUT_TIMING_VSTART(stInterfaceTimingData.usVStart - 1);
                }
                else
                {
                    // VIGP VS by pass enable
                    SET_INPUT_TIMING_VSTART(stInterfaceTimingData.usVStart);
                }
            }
            else
            {
                SET_INPUT_TIMING_VSTART(0);
            }
        }

        SET_INPUT_TIMING_VHEIGHT(stInterfaceTimingData.usVActive);
    }
    else
#endif
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
        // DP Freesync case, IVst = 1
        if(ScalerDrrIVSProduceByBE(enumSourceType, enumInputPort) == _TRUE)
        {
            SET_INPUT_TIMING_VSTART(_IVSTART_PRODUCE_BY_BE);
        }
        else
#endif
        {
            SET_INPUT_TIMING_VSTART(pstActiveRegion->usVActiveStart);
        }

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
        // Fix vertical resolution for even/odd
        if(ScalerFmtCnvFtoPGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
        {
            switch(GET_MEASURE_INPUT_PATH())
            {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                case _INPUT_PATH_M1_M2_S1_S2:
#endif
                case _INPUT_PATH_M1_M2:
                    ucVstartOffset = ((ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT4) == _BIT4) ? 0x00 : 0x01);
                    break;

#if((_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON) &&\
            (_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON))
                case _INPUT_PATH_S1_S2:
                    ucVstartOffset = ((ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT0) == _BIT0) ? 0x00 : 0x01);
                    break;
#endif

#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) &&\
            (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
                case _INPUT_PATH_S3_S4:
                    ucVstartOffset = ((ScalerGetBit(P31_16_FC_EO_LINE_CTRL1, _BIT4) == _BIT4) ? 0x00 : 0x01);
                    break;
#endif
                default:
                    break;
            }
            ucVFactor *= 2;
        }
#endif
        // VGIP Falling Latch (default)
        SET_INPUT_TIMING_VSTART(ucVFactor * GET_INPUT_TIMING_VSTART() + ucVstartOffset);
        SET_INPUT_TIMING_VHEIGHT(ucVFactor * ((pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1));
    }

#if(_COLOR_IP_3DDI == _ON)
    if(GET_3DDI_STATUS(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        SET_INPUT_TIMING_VTOTAL(pstMeasureSyncHV->usVSPeriod * 2);
    }
    else
#endif
    {
        SET_INPUT_TIMING_VTOTAL(pstMeasureSyncHV->usVSPeriod);
    }
}

//--------------------------------------------------
// Description  : Update all timing info from measure
// Input Value  : pstMeasureSyncHV --> measure result
//                pstActiveRegion --> auto-function result
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion, EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    DWORD ulMeasureClock = _MEASURE_CLK;

    ////////////////////////
    // Update H/V freq.
    ////////////////////////
#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType(GET_MEASURE_INPUT_PATH()) == _FC_SOURCE_ADC)
    {
        // Use sync processor clock for VGA
        ulMeasureClock = _SYNC_PROC_CLK;
    }
#endif

    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHFreq = (ulMeasureClock * 10 * 2 / pstMeasureSyncHV->usHSPeriod + 1) / 2;
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreq = (ulMeasureClock * 1000 * 10 * 2 / pstMeasureSyncHV->usHSPeriod / pstMeasureSyncHV->usVSPeriod + 1) / 2;

    // Copy to adjusted H/V freq.
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHFreqAdjusted = g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHFreq;
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreqAdjusted = g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreq;

    ////////////////////////
    // Update HS/VS width (polarity not included)
    ////////////////////////
    if(pstMeasureSyncHV->b1HSP == _TRUE)
    {
        // Positive HS
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHSWidth = pstMeasureSyncHV->usHSWidth;
    }
    else
    {
        // Negative HS
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHSWidth = (pstMeasureSyncHV->usHSPeriod - pstMeasureSyncHV->usHSWidth);
    }

    if(pstMeasureSyncHV->usVSWidth < (pstMeasureSyncHV->usVSPeriod >> 1))
    {
        // Positive VS
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVSWidth = pstMeasureSyncHV->usVSWidth;
    }
    else
    {
        // Negative VS
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVSWidth = (pstMeasureSyncHV->usVSPeriod - pstMeasureSyncHV->usVSWidth);
    }

    // Update H timing
    ScalerMeasureUpdateInputHorizontalTimingData(pstMeasureSyncHV, pstActiveRegion);

    // Update V timing
    ScalerMeasureUpdateInputVerticalTimingData(pstMeasureSyncHV, pstActiveRegion, enumSourceType, enumInputPort);
}

//--------------------------------------------------
// Description  : Update timing info HS/VS polarity
// Input Value  : enumSourceType --> source type
//                enumInputPort --> input port
//                pstMeasureSyncHV --> measured timing data
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputTimingPolarity(EnumSourceType enumSourceType, EnumInputPort enumInputPort, StructMeasureSyncData *pstMeasureSyncHV)
{
#if(_HDMI_SUPPORT == _ON)
    BYTE ucHdmiPage = ScalerMeasureGetTmdsPage(enumInputPort);
#endif

    enumInputPort = enumInputPort;

    pstMeasureSyncHV = pstMeasureSyncHV;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Get Raw HSync Polarity by SyncProcessor Auto Run
            if(ScalerGetBit(P0_47_SYNC_SELECT, _BIT6) == _BIT6)
            {
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = (bit)(pstMeasureSyncHV->b1HSP ^
                                                                                (((bit)ScalerGetBit(P0_48_SYNC_INVERT, _BIT3) ? _BIT0 : 0x00) ^
                                                                                 ((bit)ScalerGetBit(P0_50_STABLE_PERIOD_H, _BIT6) ? _BIT0 : 0x00)));
            }
            else
            {
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = (bit)(pstMeasureSyncHV->b1HSP ^ (((bit)ScalerGetBit(P0_48_SYNC_INVERT, _BIT3) ? _BIT0 : 0x00)));
            }

            // Check if VGATOP VS bypassed
            if(ScalerGetBit(P30_A1_VGATOP_VGIP_SIGINV, _BIT6) == _BIT6)
            {
                // Get VSP from measure result
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = (pstMeasureSyncHV->b1VSP ^ (bit)ScalerGetBit(P30_01_MEAS_CTL0, _BIT3));
            }
            else
            {
                // Get VS polarity from VGATOP setting
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit(P30_A1_VGATOP_VGIP_SIGINV, _BIT3) == 0x00);
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            ScalerDpMacStreamRxPolarity(enumInputPort);

            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:
        case _SOURCE_DVI:

#if(_HDMI_FRL_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC)
            {
                // HDMI2.1 DPF gen always positive
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = pstMeasureSyncHV->b1HSP;
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = pstMeasureSyncHV->b1VSP;

                // measure need set positive
                pstMeasureSyncHV->b1VSP = _TRUE;
                pstMeasureSyncHV->b1HSP = _TRUE;
            }
            else
#endif
            {
                if(GET_PAGED_BIT(ucHdmiPage, P72_A7_TMDS_PWDCTL, _BIT7) == _BIT7)
                {
                    if(GET_PAGED_BIT(ucHdmiPage, P72_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
                    {
                        // Read HS/VS polarity from MAC
                        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = (GET_PAGED_BIT(ucHdmiPage, P72_C0_HDCP_CR, _BIT6) == 0x00);
                        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = (GET_PAGED_BIT(ucHdmiPage, P72_C0_HDCP_CR, _BIT5) == 0x00);
                    }
                    else
                    {
                        // Positive HS/VS under DE-only mode
                        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = _TRUE;
                        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = _TRUE;
                    }
                }
                else
                {
                    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = pstMeasureSyncHV->b1HSP;
                    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = pstMeasureSyncHV->b1VSP;
                }

                if(pstMeasureSyncHV->b1VSP == _FALSE)
                {
                    // Set HDMI VS intert
                    SET_PAGED_BIT(ucHdmiPage, P72_AF_TMDS_WDC, ~_BIT3, _BIT3);
                    pstMeasureSyncHV->b1VSP = _TRUE;
                }

                if(pstMeasureSyncHV->b1HSP == _FALSE)
                {
                    // Set HDMI HS intert
                    SET_PAGED_BIT(ucHdmiPage, P72_AF_TMDS_WDC, ~_BIT2, _BIT2);
                    pstMeasureSyncHV->b1HSP = _TRUE;
                }
            }
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Update active region counter in measure flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateActiveRegion(void)
{
    BYTE ucHFactor = 0x01;
    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    ucHFactor *= ScalerFmtCnvHalfSDGetFactor(GET_MEASURE_INPUT_PATH());
#endif
#endif

    // Apply fix on horizontal resolution
    if(ucHFactor > 0x01)
    {
        usHwidth /= ucHFactor;
    }

    DebugMessageMeasure("VGIP PATH", GET_VGIP_INPUT_PATH());

    // Set VGIP capture to input size
    ScalerVgipSetCaptureHWidth(usHwidth);
    ScalerVgipSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());
    ScalerVgipCaptureEnable(_TRUE);

    // Set active region measure
    ScalerMeasureSetInputRegionCount(GET_MEASURE_INPUT_PATH(), _ACTIVE_REGION_TYPE);
    SET_INPUT_TIMING_ACTIVE_REGION(ScalerMeasureGetInputRegionCountResult(_WAIT));

    DebugMessageMeasure("active region count", GET_INPUT_TIMING_ACTIVE_REGION());

    if(GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE)
    {
        // Set whole frame measure for Accuracy IVF
        ScalerMeasureSetInputRegionCount(GET_MEASURE_INPUT_PATH(), _WHOLE_FRAME_TYPE);

        // Update Accuracy IVF by active measure count
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreq = ((GET_DWORD_MUL_DIV(_MEASURE_CLK, 100000, ScalerMeasureGetInputRegionCountResult(_WAIT)) + 5) / 10);
    }
}

//--------------------------------------------------
// Description  : Set region type for input active region measure
// Input Value  : enumInputDataPath --> input data path
//                enumRegionType --> measure region type: active, whole frame, BP or FP
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetInputRegionCount(EnumInputDataPath enumInputDataPath, EnumActiveRegionType enumRegionType)
{
    // Set region count path
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
            break;

        case _INPUT_PATH_M2:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
            break;

        case _INPUT_PATH_S1:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
            break;

        case _INPUT_PATH_S2:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
            break;

        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1_M2_S1_S2:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7));
            break;

        case _INPUT_PATH_S1_S2:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));
            break;

        case _INPUT_PATH_S3:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
            break;

        case _INPUT_PATH_S3_S4:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
            break;

        default:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
            break;
    }

    // Set source; Set measure option; Disable Input Region Measure;
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT4 | _BIT3 | _BIT0), (enumRegionType & (_BIT4 | _BIT3)));

    // Enable Input Active Region Measure
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Get input region count result
// Input Value  : bWait --> _TRUE to wait for additional frames
// Output Value : measure region count, valid 3 bytes
//--------------------------------------------------
DWORD ScalerMeasureGetInputRegionCountResult(bit bWait)
{
    if(bWait == _WAIT)
    {
        EnumInputDataPath enumInputPath = ScalerMeasureGetInputRegionSourceSelect();

        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputPath);
    }

    // Pop up Measure Results
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

    // Get Active Measure Clk Count
    return (ScalerGetDWord(P30_41_I_ACT_MEAS_ERROR_FLG) & 0xFFFFFF);
}

//--------------------------------------------------
// Description  : Get input active measure mode
// Input Value  : void
// Output Value : enumRegionType
//--------------------------------------------------
EnumActiveRegionType ScalerMeasureGetInputRegionType(void)
{
    switch(ScalerGetBit(P30_40_I_ACT_MEAS_CTRL, (_BIT4 | _BIT3)))
    {
        case 0x00:
        default:
            return _ACTIVE_REGION_TYPE;

        case _BIT3:
            return _WHOLE_FRAME_TYPE;

        case _BIT4:
            return _BACK_PORCH_TYPE;

        case (_BIT4 | _BIT3):
            return _FRONT_PORCH_TYPE;
    }
}

//--------------------------------------------------
// Description  : Get input active measure source select
// Input Value  : void
// Output Value : enumInputPath
//--------------------------------------------------
EnumInputDataPath ScalerMeasureGetInputRegionSourceSelect(void)
{
    EnumInputDataPath enumInputPath = _INPUT_PATH_M1;

    switch(ScalerGetBit(P30_40_I_ACT_MEAS_CTRL, (_BIT7 | _BIT6 | _BIT5)))
    {
        case 0x00:
        case (_BIT7):

            enumInputPath = _INPUT_PATH_M1;
            break;

        case _BIT5:
            enumInputPath = _INPUT_PATH_M2;
            break;

        case _BIT6:
        case (_BIT7 | _BIT5):
            enumInputPath = _INPUT_PATH_S1;
            break;

        case (_BIT6 | _BIT5):
            enumInputPath = _INPUT_PATH_S2;
            break;

        case (_BIT7 | _BIT6):
        case (_BIT7 | _BIT6 | _BIT5):
            enumInputPath = _INPUT_PATH_S3;
            break;

        default:
            break;
    }

    return enumInputPath;
}

//--------------------------------------------------
// Description  : Set region type for display active region measure
// Input Value  : enumDDomainRegion --> measure target in D-domain
//                enumRegionType --> measure region type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetDisplayRegionCount(EnumDDomainRegion enumDDomainRegion, EnumActiveRegionType enumRegionType)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT5);
            break;

        case _DDOMAIN_RGN_R1_A2:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT5 | _BIT2));
            break;

        case _DDOMAIN_RGN_R2_A1:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));
            break;

        case _DDOMAIN_RGN_R2_A2:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5 | _BIT2));
            break;

        case _DDOMAIN_RGN_R3_A1:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT5));
            break;

        case _DDOMAIN_RGN_R3_A2:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT5 | _BIT2));
            break;

        default:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), 0x00);
            break;
    }

    // Select source form M1; Set measure option; Disable Input Region Measure;
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT4 | _BIT3 | _BIT0), (enumRegionType & (_BIT4 | _BIT3)));

    // Enable Display  Active Region Measure
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Get input region count result
// Input Value  : bWait --> _TRUE to wait for additional frames
// Output Value : measure region count, valid 3 bytes
//--------------------------------------------------
DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait)
{
    if(bWait == _WAIT)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }

    // Pop up Measure Results
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

    // Get Active Measure Clk Count
    return (ScalerGetDWord(P30_46_D_ACT_MEAS_ERROR_FLG) & 0xFFFFFF);
}

//--------------------------------------------------
// Description  : Calculate active region area in pixles
// input region cnt calculation:
// single   = IHtotal * (IVheight - 1) + IHwidth
// even/odd = (IHtotal * (IVheight / 2 - 1) + IHwidth) * 2
//          = IHtotal * (IVheight - 2) + IHwidth * 2
// Input Value  : enumInputDataPath --> input data path
//                usHWidth       --> target H width
//                usVHeight      --> target V height
//                usHTotal      --> target H total
// Output Value : active region area in pixel
//--------------------------------------------------
DWORD ScalerMeasureGetdActiveRegionPixels(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight, WORD usHTotal)
{
    enumInputDataPath = enumInputDataPath;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
    {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        // Apply modification from format-conversion extension
        if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
        {
            return (DWORD)(usVHeight - 2) * usHTotal + usHWidth * 2;
        }
#endif

        return (DWORD)(usVHeight - 2) * usHTotal + usHWidth * 2;
    }
#endif

    return (DWORD)(usVHeight - 1) * usHTotal + usHWidth;
}

//--------------------------------------------------
// Description  : Calculate active region measure with adjusted H/V size
// Input Value  : enumInputDataPath --> input data path
//                usNewHWidth       --> target H width
//                usNewVHeight      --> target V height
// Output Value : adjusted active region counter
//--------------------------------------------------
DWORD ScalerMeasureGetAdjustedActiveRegionCount(EnumInputDataPath enumInputDataPath, WORD usNewHWidth, WORD usNewVHeight)
{
    BYTE ucIndex = ScalerRegionGetIndexFromInputDataPath(enumInputDataPath);
    StructRegionTimingInfo *pstTimingInfo = &g_pstMeasureRegionTimingInfo[ucIndex];

    DWORD ulTotalCount = 0;
    DWORD ulNewTotalCount = 0;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    // Restore H Width from 1/2 SD
    usNewHWidth *= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Apply modification from format-conversion extension
    if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
    {
        usNewHWidth += (GET_FMTCNV_EXTENSION_LEN() * 2);
    }
#endif
#endif

    // Calculate pixel count
    ulTotalCount = ScalerMeasureGetdActiveRegionPixels(enumInputDataPath,
                                                       pstTimingInfo->stTimingInfo.usHWidth,
                                                       pstTimingInfo->stTimingInfo.usVHeight,
                                                       pstTimingInfo->stTimingInfo.usHTotal);

    ulNewTotalCount = ScalerMeasureGetdActiveRegionPixels(enumInputDataPath,
                                                          usNewHWidth,
                                                          usNewVHeight,
                                                          pstTimingInfo->stTimingInfo.usHTotal);

    return GET_DWORD_MUL_DIV(pstTimingInfo->ulActiveRegionCount, ulNewTotalCount, ulTotalCount);
}

//--------------------------------------------------
// Description  : Calculate H frequency from active region count
// Input Value  : enumInputDataPath --> input data path
// Output Value : calcuated H freq. (unit: 0.01kHz)
//--------------------------------------------------
DWORD ScalerMeasureGetHFreq(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIndex = ScalerRegionGetIndexFromInputDataPath(enumInputDataPath);
    StructRegionTimingInfo *pstTimingInfo = &g_pstMeasureRegionTimingInfo[ucIndex];

    DWORD ulTotalCount = 0;
    DWORD ulHSPeriod = 0;

    ulTotalCount = ScalerMeasureGetdActiveRegionPixels(enumInputDataPath,
                                                       pstTimingInfo->stTimingInfo.usHWidth,
                                                       pstTimingInfo->stTimingInfo.usVHeight,
                                                       pstTimingInfo->stTimingInfo.usHTotal);

    // Calculate 0.1 counter for H period
    ulHSPeriod = GET_DWORD_MUL_DIV(pstTimingInfo->ulActiveRegionCount,
                                   ((DWORD)pstTimingInfo->stTimingInfo.usHTotal * 10),
                                   ulTotalCount);

    return ((DWORD)_MEASURE_CLK * 1000 / ulHSPeriod);
}

//--------------------------------------------------
// Description  : Transfer D domain to I domain measure H result
// Input Value  : enumInputDataPath --> input data path, D domain Hactive data
// Output Value : I domain Hactive data
//--------------------------------------------------
WORD ScalerMeasureTransDDomainToIDomainHorizonalPosition(WORD usIHWidth, WORD usDDomainHpos)
{
    return (DWORD)usDDomainHpos * usIHWidth / ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_WIDTH);
}

//--------------------------------------------------
// Description  : Transfer D domain to I domain measure V result
// Input Value  : enumInputDataPath --> input data path, D domain Vactive data
// Output Value : I domain Vactive data
//--------------------------------------------------
WORD ScalerMeasureTransDDomainToIDomainVerticalPosition(WORD usIVHeight, WORD usDDomainVpos)
{
    return (DWORD)usDDomainVpos * usIVHeight / ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_V_HEIGHT);
}

#if(_DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE == _ON)
//--------------------------------------------------
// Description  : Measure Image Boundary
// Input Value  : ucNoiseMargin, pstActiveRegion, enumDisplayRegion
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
bit ScalerMeasureImageBoundary(BYTE ucNoiseMargin, StructAutoActiveData *pstActiveRegion, EnumDisplayRegion enumDisplayRegion, EnumColorSpace enumColorSpace, bit bWait)
{
    bit bMeasurePass = _TRUE;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumInputDataPath);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _TRUE)
    BYTE ucFmtCnvBGStatus = ScalerGetByte(P31_50_PORCH_COLOR_CTRL);
#endif

    // Set RGB noise margin
    if(GET_COLOR_SPACE_RGB(enumColorSpace) == _TRUE)
    {
        // bit7:2b
        SET_PAGED_BIT(ucIDomainPage, P0_76_RED_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (ucNoiseMargin << 2));
        SET_PAGED_BIT(ucIDomainPage, P0_77_GRN_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (ucNoiseMargin << 2));
        SET_PAGED_BIT(ucIDomainPage, P0_78_BLU_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (ucNoiseMargin << 2));
    }
    else
    {
        SET_PAGED_BIT(ucIDomainPage, P0_76_RED_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (0x3F << 2));
        SET_PAGED_BIT(ucIDomainPage, P0_77_GRN_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (0x06 << 2));
        SET_PAGED_BIT(ucIDomainPage, P0_78_BLU_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (0x3F << 2));
    }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _TRUE)
    ScalerFmtCnvSetBackgroundStatus(enumInputDataPath, _TRUE);
#endif

    // [6]:software,only measure 1 frame
    SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // Set H boundary
    ScalerMeasureSetAutoFuncHBoundary(0x0002, 0x1FFF, enumInputDataPath);

    // Set V Boundary
    ScalerMeasureSetAutoFuncVBoundary(0x0000, 0x1FFF, enumInputDataPath);

    // Pop up auto result
    SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, (_BIT0));

    if(ScalerMeasureGetAutoBoundaryResult(pstActiveRegion, enumInputDataPath, bWait) == _FALSE)
    {
        DebugMessageScaler("1.ScalerMeasureImageBoundary FAIL ", 0x99);
        bMeasurePass = _FALSE;
    }

#if(_HW_FORMAT_CONVERSION_SUPPORT == _TRUE)
    // Recover Format Conversion Background Status setting
    ScalerSetByte(P31_50_PORCH_COLOR_CTRL, ucFmtCnvBGStatus)
#endif

    if((GET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, _BIT7) == 0x00) &&
       (pstActiveRegion->usHActiveStart > 1) &&
       (pstActiveRegion->usHActiveEnd > 1))
    {
        pstActiveRegion->usHActiveStart -= 1;
        pstActiveRegion->usHActiveEnd -= 1;
    }

    return bMeasurePass;
}

//--------------------------------------------------
// Description  : Update HV timing info from measure
// Input Value  : pstActiveRegion --> auto-function result
//                pstImageRegion --> according auto result, calculate real input HV timing info
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateHVtiming(StructAutoActiveData *pstActiveRegion, StructImageRegion *pstImageRegion, EnumDisplayRegion enumDisplayRegion)
{
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

    BYTE ucHwidthFactor = 1;
    BYTE ucHstartFactor = 1;

    BYTE ucVFactor = 1;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    BYTE ucHPixelModeTargetFactor = ScalerFmtCnvGetPixelModeTargetFactor(enumInputDataPath);
    BYTE ucHPixelModeFactor = ScalerFmtCnvGetPixelModeFactor(enumInputDataPath);
#endif
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    BYTE ucHSDFactor = ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif
#endif

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
    // Apply horizontal fix for pixel mode
    ucHstartFactor *= ucHPixelModeTargetFactor;
    ucHwidthFactor *= ucHPixelModeTargetFactor;

    ucHstartFactor /= ucHPixelModeFactor;
    ucHwidthFactor /= ucHPixelModeFactor;
#endif

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    // Apply horizontal fix for 1/2 SD mode
    ucHstartFactor *= ucHSDFactor;
    ucHwidthFactor *= ucHSDFactor;
#endif

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
    {
        ucHstartFactor *= 2;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
        {
            if(ScalerFmtCnvFBGetFBModeStatus() == _TRUE)
            {
                ucHwidthFactor *= 2;
            }
        }
#endif
    }
#endif

#endif

    pstImageRegion->usImageHWidth = (ucHwidthFactor * ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1));

    if(pstActiveRegion->usHActiveStart > GET_ACTIVE_H_START())
    {
        pstImageRegion->usImageHStart = (ucHstartFactor * GET_ACTIVE_H_START()) + (pstActiveRegion->usHActiveStart - GET_ACTIVE_H_START());
    }
    else
    {
        pstImageRegion->usImageHStart = (ucHstartFactor * pstActiveRegion->usHActiveStart);
    }

#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    // E/O mode, M domain IVst must be 2x
    if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
    {
        ucVFactor *= 2;
    }
#endif

    pstImageRegion->usImageVHeight = (ucVFactor * ((pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1));
    pstImageRegion->usImageVStart = (ucVFactor * pstActiveRegion->usVActiveStart);
}

//--------------------------------------------------
// Description  : Get Measure HW Auto Phase Enable
// Input Value  : enumInputDataPath
// Output Value : _ENABLE: HW mode, _DISABLE: FW mode
//--------------------------------------------------
bit ScalerMeasureGetHwAutoPhaseEnable(EnumInputDataPath enumInputDataPath)
{
    if(GET_PAGED_BIT(ScalerMeasureGetIDomainPage(enumInputDataPath), P0_7D_AUTO_ADJ_CTRL1, _BIT6) == _BIT6)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif


#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Measure flow for VGA
// Input Value  : None
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureVgaInputInfo(void)
{
    DWORD pulActiveRegionCount[2] = {0};
    EnumInputPort enumInputPort = _A0_INPUT_PORT;

    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial the interface to be measured
    ScalerMeasureInterfaceInitial(_SOURCE_VGA, &enumInputPort);

    // Initial Measure
    ScalerMeasureInitialSetting(_SOURCE_VGA, _A0_INPUT_PORT);

    // Initial Interlace Check Block
    ScalerMeasureInterlaceInitial(_SOURCE_VGA, _A0_INPUT_PORT);

    // Enable IVS bypass
    ScalerVgaTopSetVsBypassEnable(_ENABLE);
    ScalerVgipSetVsBypassEnable(GET_MEASURE_INPUT_PATH(), _ENABLE);

    // Wait for 2raw IVS before switch to VS bypass mode
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE))
    {
        DebugMessageMeasure("VGA IVS fail", 0x00);
        return _FALSE;
    }

    // Initial active region count block
    ScalerMeasureSetInputRegionCount(GET_MEASURE_INPUT_PATH(), _WHOLE_FRAME_TYPE);

    //===========================================================================================
    // 1. Start measure block & region count(raw VS); pop-out result
    //===========================================================================================

    // Wait for 3raw IVS for VGA; Pop out measure result
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerMeasureGetOfflineMeasureResult(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), enumInputPort) == _FALSE))
    {
        DebugMessageMeasure("VGA off-line measure fail", 0x00);
        return _FALSE;
    }

    ScalerTimerDelayXms(2);

    // Pop out active region count result (raw)
    if((pulActiveRegionCount[0] = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT)) == 0x00)
    {
        return _FALSE;
    }

    // Restart active region count block;
    ScalerMeasureSetInputRegionCount(GET_MEASURE_INPUT_PATH(), _WHOLE_FRAME_TYPE);

    //===========================================================================================
    // 2. Check VGIP HS/VS polarity
    //===========================================================================================

    // Update input timing polarity (MUST BE HERE)
    ScalerMeasureUpdateInputTimingPolarity(_SOURCE_VGA, _A0_INPUT_PORT, &(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData));

    // Disable IVS bypass
    ScalerVgaTopSetVsBypassEnable(_DISABLE);
    ScalerVgipSetVsBypassEnable(GET_MEASURE_INPUT_PATH(), _DISABLE);

    // Modify VGATOP sync polarity
    ScalerVgaTopModifyPolarity();

    // Modify VGIP sync polarity
    ScalerVgipModifyPolarity(_SOURCE_VGA);

    // Update input timing data from variable "g_stMeasureSyncHV"
    ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), _SOURCE_VGA, enumInputPort);

    //===========================================================================================
    // 3. Start auto-function & check VGIP VS latch edge
    //===========================================================================================

    // Start auto-function measure
    ScalerVgaTopSetAuto(_NORMAL_MEASURE, _FULL_BOUNDARY, ScalerAPLLGetIHTotal());

    // Check IVS latch edge after 1 IVS; Add additional 1 frame if latch edge changed
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       ((ScalerVgaTopModifyVsLatchEdge(_NOT_WAIT) == _TRUE) &&
        (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)))
    {
        return _FALSE;
    }

    // Wait for 1 latched IVS; Pop out auto-function result
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopGetAutoResult(&(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), _NOT_WAIT) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE))
    {
        DebugMessageMeasure("VGA auto-function fail", 0x00);
        return _FALSE;
    }

    //===========================================================================================
    // 4. Detect interlace format
    //===========================================================================================

    // Pop out active region count result (latched) for VGA
    pulActiveRegionCount[1] = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT);

    // Check active region count result; Return _FALSE if the difference is too large
    if(ABSDWORD(pulActiveRegionCount[0], pulActiveRegionCount[1]) > (pulActiveRegionCount[1] >> 6))
    {
        DebugMessageMeasure("VGA active count difference fail", 0x00);
        return _FALSE;
    }

    // Get HS period in measure clock
    PDATA_WORD(1) = (((WORD)ScalerGetBit(P30_05_MEAS_HS_PERIOD_A_M, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) |
                     ((WORD)ScalerGetByte(P30_06_MEAS_HS_PERIOD_A_L)));

    // Calculate difference of V period
    PDATA_WORD(0) = (WORD)(ABSDWORD(pulActiveRegionCount[0], pulActiveRegionCount[1]) % PDATA_WORD(1));

    // Check half line length; flag interlace between [0.25:0.75] * H period
    if(abs(PDATA_WORD(0) - (PDATA_WORD(1) >> 1)) < (PDATA_WORD(1) >> 2))
    {
        DebugMessageScaler("Interlace: detect by half line", PDATA_WORD(0));
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;
    }
    // Check full line length; flag interlace for 0.875 line difference
    else if(PDATA_WORD(0) > (PDATA_WORD(1) - (PDATA_WORD(1) >> 3)))
    {
        DebugMessageScaler("Interlace: detect by full line", PDATA_WORD(1));
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;
    }

    // Check active measure overflow status
    if(ScalerGetBit(P30_41_I_ACT_MEAS_ERROR_FLG, _BIT6) == _BIT6)
    {
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = ScalerMeasureInterlaceCheck(_SOURCE_VGA, _A0_INPUT_PORT);
        DebugMessageScaler("Interlace: detect by flag", g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace);
    }

    // Update VGATOP field source
    ScalerSetBit(P30_A3_VGATOP_VGIP_ODD_CTRL, ~_BIT0, ((GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE) ? _BIT0 : 0x00));

    //===========================================================================================
    // 5. Double-check current timing
    //===========================================================================================

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), _SOURCE_VGA, enumInputPort);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    // Decide I-domain path setting in format conversion
    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        // Final format conversion setting
        ScalerFmtCnvFinalSetting(_A0_INPUT_PORT, GET_MEASURE_INPUT_PATH(), _NOT_WAIT);
    }
#endif

    // Start on-line measure
    ScalerMeasureSetOnlineMeasure(_SOURCE_VGA, enumInputPort, GET_MEASURE_INPUT_PATH(), GET_INPUT_TIMING_VFREQ());

    // Double check off-line measure result
    if(ScalerMeasureOfflineMeasureDoubleCheck(_SOURCE_VGA, _A0_INPUT_PORT) == _FALSE)
    {
        DebugMessageMeasure("VGA off-line double check fail", 0x00);
        return _FALSE;
    }

    // Double-check for timing change
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerMeasureGetOnlineMeasureResult(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), GET_MEASURE_INPUT_PATH()) == _FALSE))
    {
        DebugMessageMeasure("VGA on-line measure fail", 0x00);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get stable measure result for VGA
// Input Value  : pstMeasureSyncHV --> result pointer
// Output Value : _TRUE if HV timing Changed
//--------------------------------------------------
bit ScalerMeasureGetVgaStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV)
{
    if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT3)) != 0x00)
    {
        return _FALSE;
    }

    // Pop up stable measure result
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P0_4F_STABLE_MEASURE, _BIT6);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | (ScalerGetByte(P0_51_STABLE_PERIOD_L))) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P0_4A_STABLE_HIGH_PERIOD_H) & 0x07) << 8) | (ScalerGetByte(P0_4B_STABLE_HIGH_PERIOD_L))) + 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect VGA Interlace format
// Input Value  : enumInputPort --> input port
// Output Value : _TRUE if interlaced format detected
//--------------------------------------------------
bit ScalerMeasureVgaInterlaceCheck(EnumInputPort enumInputPort)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(GET_MEASURE_INPUT_PATH());
    bit bInterlacedFormat = _FALSE;

    enumInputPort = enumInputPort;

    // Check VGA interlace condition: due to overflow or from digital measure?
    if(ScalerGetBit(P30_41_I_ACT_MEAS_ERROR_FLG, _BIT6) == _BIT6)
    {
        // Clear VGIP Interlace Toggle Flag
        SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        ScalerTimerDelayXms(2);

        if((GET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5) ||
           (ScalerGetBit(P0_4A_STABLE_HIGH_PERIOD_H, (_BIT6 | _BIT4)) != 0x00))
        {
            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Clear Sync proc. toggle flag
            ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            bInterlacedFormat = _TRUE;
        }

        // Clear VGIP Interlace Toggle Flag
        SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

        // Clear Sync proc. toggle flag
        ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
    }
    else
    {
        // Check from previous set flag
        bInterlacedFormat = (ScalerGetBit(P30_A3_VGATOP_VGIP_ODD_CTRL, _BIT0) == _BIT0);
    }

    return bInterlacedFormat;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect V start position for interlaced format
// Input Value  : usVstart -> V start
//                usVend -> V end
// Output Value : _TRUE if V start detect passed
//--------------------------------------------------
bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend)
{
    WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());

    if(usVstart == g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
    {
        // For 1035i
        if((usVend - usVstart) == (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd - g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart))
        {
            // Toggle Video Compensation field
            ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), (~(ScalerGetByte(usSUPageAddr)) & _BIT6));
        }
        else if((usVend - usVstart) < 250)
        {
            // For 487i
            ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), (~(ScalerGetByte(usSUPageAddr)) & _BIT6));
        }
    }
    else if(abs(usVstart - g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart) == 0x01)
    {
        StructAutoActiveData stAutoActiveData = {0};

        // Store the smaller Vstart
        if(usVstart < g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
        {
            --(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart);
            --(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd);
        }

        // Enable ODD delay one line
        for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
        {
            EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
            BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

            // Toggle delay-one-line field
            if((GET_MEASURE_INPUT_PATH() & enumCurrPath) != 0)
            {
                SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6), _BIT6);
            }
        }

        // Toggle Video Compensation field
        ScalerSetBit(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()), ~(_BIT6 | _BIT5), (~(ScalerGetByte(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()))) & _BIT6));
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerScalingGetFBFrameStatus((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
        {
            ScalerSetBit(ScalerDDomainGetScalingUpPageAddr(_DDOMAIN_RGN_R3_A1), ~(_BIT6 | _BIT5), (~(ScalerGetByte(ScalerDDomainGetScalingUpPageAddr(_DDOMAIN_RGN_R3_A1))) & _BIT6));
        }
#endif
        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE))
        {
            return _FALSE;
        }

        // Pop up auto-function result
        if(ScalerMeasureGetAutoBoundaryResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _NOT_WAIT) == _FALSE)
        {
            return _FALSE;
        }

        // Double-check delay-one-line field polarity
        if(stAutoActiveData.usVActiveStart != g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
        {
            for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
            {
                EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
                BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

                // Toggle delay-one-line field
                if((GET_MEASURE_INPUT_PATH() & enumCurrPath) != 0)
                {
                    SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT7, (~(GET_PAGED_BYTE(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL)) & _BIT7));
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect H width for the first line shift.
//                For some HDMI source, there will be a one-line shift after DE-only mode is enabled.
//                DE-only mode should be disabled in order to display normally.
// Input Value  : enumInputPort --> port to be checked
//                usFrameHwidth --> H width from measure block
// Output Value : _TRUE if detect passed
//--------------------------------------------------
void ScalerMeasureCheckFirstLineShift(EnumInputPort enumInputPort, WORD usFrameHwidth)
{
    BYTE ucHdmiPage = ScalerMeasureGetTmdsPage(enumInputPort);
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(GET_MEASURE_INPUT_PATH());
    BYTE ucHwidthFactor = 0x01;
    BYTE ucDiffPixel = (ScalerMeasureGetOfflineMeasureDiv2() == _TRUE) ? 2 : 1;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    ucHwidthFactor *= ScalerFmtCnvHalfSDGetFactor(GET_MEASURE_INPUT_PATH());
#endif
#endif
#endif

    // Check under DE-only mode with raw HS/VS
    if((GET_PAGED_BIT(ucHdmiPage, P72_A7_TMDS_PWDCTL, _BIT7) == _BIT7) &&
       (GET_PAGED_BIT(ucHdmiPage, P72_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3)))
    {
        // Stop auto-function
        SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        // Set measure boundary to first line
        ScalerMeasureSetAutoFuncHBoundary(0x0002, 0x1FFF, GET_MEASURE_INPUT_PATH());
        ScalerMeasureSetAutoFuncVBoundary((GET_ACTIVE_V_START() + 1), GET_INPUT_TIMING_VTOTAL(), GET_MEASURE_INPUT_PATH());

        // Start auto-function measure
        SET_PAGED_BIT(ucIDomainPage, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FAIL) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FAIL))
        {
            return;
        }

        // Calculate first H width
        PDATA_WORD(0) = ((((WORD)GET_PAGED_BIT(ucIDomainPage, P0_81_H_START_END_H, 0xF0)) << 4) | GET_PAGED_BYTE(ucIDomainPage, P0_82_H_START_L)); // H st
        PDATA_WORD(1) = ((((WORD)GET_PAGED_BIT(ucIDomainPage, P0_81_H_START_END_H, 0x0F)) << 8) | GET_PAGED_BYTE(ucIDomainPage, P0_83_H_END_L)); // H end
        PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0) + 1) * ucHwidthFactor; // modify H width

        if(abs(PDATA_WORD(2) - usFrameHwidth) <= ucDiffPixel)
        {
            // First line shift detected; Disable DE-only mode
            ScalerTmdsMacRxSetDeOnlyModeConfig(enumInputPort, (EnumDeOnlyConfig)(_DE_ONLY_DISABLE | _DE_ONLY_HS_72T));
        }
    }
}

//--------------------------------------------------
// Description  : Judge Timing for TMDS DE Only mode enable or not
// Input Value  : StructMeasureSyncData *pstMeasureSyncHV, usIVFreq
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureCheckTmdsDeOnlyTiming(StructMeasureSyncData *pstMeasureSyncHV, WORD usIVFreq)
{
    // Timing-1 : 1280x1024@120Hz (Source : Apple MacBook Air 13" / ChipSet : Apple M1)
    if((pstMeasureSyncHV->usHWidth == 1280) && (pstMeasureSyncHV->usVHeight == 1024) &&
       ((usIVFreq >= 1190) && (usIVFreq <= 1210)))
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect DP Interlace format
// Input Value  : enumInputPort --> input port
//                ucIDomainPage --> I-Domain page
// Output Value : _TRUE if interlaced format detected
//--------------------------------------------------
bit ScalerMeasureDpInterlaceCheck(EnumInputPort enumInputPort, BYTE ucIDomainPage)
{
    WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());

    if(ScalerDpMacStreamRxInterlaceModeConfig(enumInputPort, _REF_VBID) == _ENABLE)
    {
        // Interlace field signal from interface
        SET_PAGED_BIT(ucIDomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

#if(_HW_SCALING_UP_VIDEO_COMPENSATION_TYPE == _SU_VIDEO_COMPENSATION_GEN_1)
        // Set Video Compensation to ODD Field
        ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), 0x00);
#else
        // Set Video Compensation to EVEN Field
        ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), _BIT6);
#endif
        return _TRUE;
    }

    if(ScalerDpMacStreamRxInterlaceModeConfig(enumInputPort, _REF_BS_COUNTER) == _ENABLE)
    {
        if(GET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
        {
            BYTE ucFieldFromVgip = _TRUE;

            // Check input path count
            // - extra check required for E/O mode
            if(ScalerIDomainGetInputPathCount(GET_MEASURE_INPUT_PATH()) != 0x01)
            {
                BYTE ucIndex = 0;
                WORD pusVtotal[2] = {0};

                // Get V-total for 2 frames
                for(; ucIndex < sizeof(pusVtotal) / sizeof(pusVtotal[0]); ++ucIndex)
                {
                    // Wait until IHV delay change
                    ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());

                    // Pop-out off-line measure result
                    ScalerSetBit(P30_02_MEAS_CTL1, ~_BIT6, _BIT6);

                    pusVtotal[ucIndex] = TO_WORD(
                        ScalerGetByte(P30_08_MEAS_VS_PERIOD_A_M) & 0x7F,
                        ScalerGetByte(P30_09_MEAS_VS_PERIOD_A_L)) + 1;
                }

                // Check whether Vtotal-min is even or odd
                // - EVEN : select field from VGIP
                // - ODD  : select field from DP mac
                pusVtotal[0] = MINOF(pusVtotal[0], pusVtotal[1]);

                if((pusVtotal[0] % 2) == 1)
                {
                    ucFieldFromVgip = _FALSE;
                }
            }

#if(_COLOR_IP_3DDI == _ON)
            if(ucFieldFromVgip == _TRUE)
            {
                // Set interlace flag for 3DDI enable decision
                g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;

                // setting for Input path S2 for 3DDI in E/O panel
                if((Scaler3DDIEnableDecision(GET_MEASURE_INPUT_PATH(), enumInputPort) == _TRUE) &&
                   (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE) &&
                   (GET_MEASURE_INPUT_PATH() == _INPUT_PATH_S1_S2))
                {
                    ucFieldFromVgip = _FALSE;
                }
            }
#endif

            if(ucFieldFromVgip == _TRUE)
            {
                // Select Filed Signal from VGIP
                SET_PAGED_BIT(ucIDomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, _BIT0);

#if(_HW_SCALING_UP_VIDEO_COMPENSATION_TYPE == _SU_VIDEO_COMPENSATION_GEN_1)
                // Set Video Compensation to EVEN Field
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), _BIT6);
#else
                // Set Video Compensation to ODD Field
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), 0x00);
#endif

                // Clear VGIP Interlace Toggle Flag
                SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            }
            else
            {
                // Interlace field signal from interface
                SET_PAGED_BIT(ucIDomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

#if(_HW_SCALING_UP_VIDEO_COMPENSATION_TYPE == _SU_VIDEO_COMPENSATION_GEN_1)
                // Set Video Compensation to ODD Field
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), 0x00);
#else
                // Set Video Compensation to EVEN Field
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), _BIT6);
#endif
            }

            return _TRUE;
        }
    }

    // Special case for interlace detection from VBID
    // - no field toggling
    if(ScalerDpMacStreamRxGetInterlaceMode(enumInputPort) == _TRUE)
    {
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1DpInterlaceVBID = _TRUE;
    }

    // Clear VGIP Interlace Toggle Flag
    SET_PAGED_BIT(ucIDomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

    return _FALSE;
}
#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect TMDS Interlace format
// Input Value  : enumInputPort --> input port
//                ucIDomainPage --> I-Domain page
// Output Value : _TRUE if interlaced format detected
//--------------------------------------------------
bit ScalerMeasureTmdsInterlaceCheck(EnumInputPort enumInputPort, BYTE ucIDomainPage)
{
#if(_HDMI_FRL_SUPPORT == _ON)
    // HDMI2.1 Interlace
    if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC)
    {
        if(ScalerHdmiFrlMacRxInterlaceModeCheck(enumInputPort) == _TRUE)
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    // HDMI2.0 Interlace
    else
#endif
    {
        WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());
        BYTE ucHdmiPage = ScalerMeasureGetTmdsPage(enumInputPort);
        WORD usVstart = 0x0000;
        WORD usVend = 0x0000;

        StructAutoActiveData stAutoActiveData = {0};

        // Clear VGIP Interlace Toggle Flag
        SET_PAGED_BIT(ucHdmiPage, P72_72_IVHS_CTRL_2, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT6);

        // Clear Interlace toggle flag
        ScalerSetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

        // Delay until field stable
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());
        ScalerMeasureGetAutoBoundaryResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _NOT_WAIT);
        g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart = stAutoActiveData.usVActiveStart;
        g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd = stAutoActiveData.usVActiveEnd;

        // Get another V start
        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());
        ScalerMeasureGetAutoBoundaryResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _NOT_WAIT);
        usVstart = stAutoActiveData.usVActiveStart;
        usVend = stAutoActiveData.usVActiveEnd;

#if(_DVI_DE_ONLY_SUPPORT == _ON)
        if(GET_PAGED_BIT(ucHdmiPage, P72_A4_TMDS_CTRL, (_BIT4 | _BIT3)) != (_BIT4 | _BIT3))
        {
            // Detect by Vtotal
            if(GET_PAGED_BIT(ucHdmiPage, P72_72_IVHS_CTRL_2, _BIT6) == _BIT6)
            {
                // Interlace field signal from IHV delay; Odd inverted
                SET_PAGED_BIT(ucHdmiPage, P72_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), (_BIT7 | _BIT2));
                SET_PAGED_BIT(ucHdmiPage, P72_72_IVHS_CTRL_2, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT7);

#if(_HW_SCALING_UP_VIDEO_COMPENSATION_TYPE == _SU_VIDEO_COMPENSATION_GEN_1)
                // Set Video Compensation to EVEN Field
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), _BIT6);
#else
                // Set Video Compensation to ODD Field
                ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), 0x00);
#endif

                // Wait until TMDS IHV delay change
                ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());

                // Check delay one line (with one-mimus Vstart after IHV delay enabled)
                g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart -= 1;
                g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd -= 1;
                usVstart -= 1;
                usVend -= 1;

                ScalerMeasureCheckInterlaceVst(usVstart, usVend);

                // Clear VGIP Interlace Toggle Flag
                SET_PAGED_BIT(ucHdmiPage, P72_72_IVHS_CTRL_2, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT6);

                return _TRUE;
            }
        }
        else
#endif
        {
            // Detect by VS Position
            if(ScalerGetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, _BIT6) == _BIT6)
            {
                if(ScalerGetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, _BIT5) == 0x00)
                {
                    // Interlace field signal from interface
                    SET_PAGED_BIT(ucIDomainPage, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

#if(_HW_SCALING_UP_VIDEO_COMPENSATION_TYPE == _SU_VIDEO_COMPENSATION_GEN_1)
                    // Set Video Compensation to ODD Field
                    ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), 0x00);
#else
                    // Set Video Compensation to EVEN Field
                    ScalerSetBit(usSUPageAddr, ~(_BIT6 | _BIT5), _BIT6);
#endif

                    // Check delay one line
                    ScalerMeasureCheckInterlaceVst(usVstart, usVend);

                    // Clear Interlace toggle flag
                    ScalerSetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

                    return _TRUE;
                }
            }
        }

        // Clear VGIP Interlace Toggle Flag
        SET_PAGED_BIT(ucHdmiPage, P72_72_IVHS_CTRL_2, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT6);

        // Clear Interlace toggle and error flag
        ScalerSetDataPortBit(GET_PAGED_ADDR(ucHdmiPage, P72_C9_HDMI_AP), _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

        return _FALSE;
    }
}
#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Measure flow for duplicated port.
//                Interface setting cannot be changed because it is already displaying.
// Input Value  : ucDuplicateIndex --> duplicate source to be duplicated from
//                enumSourceType --> source type
//                enumInputPort --> input port
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
EnumMeasureResult ScalerMeasureDuplicateInputInfo(BYTE ucDuplicateIndex, EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    EnumInputDataPath enumDuplicatePath = g_pstMeasureRegionTimingInfo[ucDuplicateIndex].stTimingInfo.enumInputDataPath;

    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial measure & auto-function
    ScalerMeasureInitialSetting(enumSourceType, enumInputPort);

    // Duplicate interlace setting
    ScalerMeasureDuplicateInterlaceSetting(enumDuplicatePath);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _MEASURE_RESULT_FAIL;
    }
#endif

    // check Interface Pixel Mode Limit OOR
    if(ScalerMeasureCheckInterfaceNoSupport(enumInputPort) == _TRUE)
    {
        return _MEASURE_RESULT_OOR;
    }

    //===========================================================================================
    // 1. Start measure block & pop-out result
    //===========================================================================================

    // Wait for 2 raw IVS for digital; Pop out measure result
#if(_VGA_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_VGA)
    {
        if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
           (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE))
        {
            DebugMessageMeasure("VGA polling IVS fail", 0x00);
            return _MEASURE_RESULT_FAIL;
        }
    }
    else
#endif
    {
        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE))
        {
            DebugMessageMeasure("Digital polling IVS fail", 0x00);
            return _MEASURE_RESULT_FAIL;
        }
    }

    if(ScalerMeasureGetOfflineMeasureResult(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), enumInputPort) == _FALSE)
    {
        DebugMessageMeasure("Digital off-line measure fail", 0x00);
        return _MEASURE_RESULT_FAIL;
    }

    // check I-domain Path Limit OOR
    if(ScalerMeasureCheckIDomainNoSupport(enumInputPort) == _TRUE)
    {
        return _MEASURE_RESULT_OOR;
    }

#if(_VGA_SUPPORT == _ON)
    if((enumSourceType == _SOURCE_VGA) &&
       (g_ucVgaModeNo == _VGA_MODE_NOSUPPORT))
    {
        // Start on-line measure
        ScalerMeasureSetOnlineMeasure(enumSourceType, enumInputPort, GET_MEASURE_INPUT_PATH(), GET_INPUT_TIMING_VFREQ());

        // Pop out on-line measure result
        if(ScalerMeasureGetOnlineMeasureResult(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), GET_MEASURE_INPUT_PATH()) == _FALSE)
        {
            DebugMessageMeasure("VGA on-line measure fail", 0x00);
            return _MEASURE_RESULT_FAIL;
        }

        // Set width & height to 0 to trigger OOR state
        SET_INPUT_TIMING_HWIDTH(0);
        SET_INPUT_TIMING_VHEIGHT(0);

        return _TRUE;
    }
#endif

    //===========================================================================================
    // 2. Check VGIP HS/VS polarity
    //===========================================================================================

    // Copy timing polarity
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = g_pstMeasureRegionTimingInfo[ucDuplicateIndex].stTimingInfo.b1HSP;
    g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = g_pstMeasureRegionTimingInfo[ucDuplicateIndex].stTimingInfo.b1VSP;

    // Modify VGIP sync polarity
    ScalerVgipModifyPolarity(enumSourceType);

    // Update input timing data from variable "g_stMeasureSyncHV"
    ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), enumSourceType, enumInputPort);

    //===========================================================================================
    // 3. Start auto-function
    //===========================================================================================
    if(ScalerMeasureUpdateAutoPosition(enumSourceType, enumInputPort) == _FALSE)
    {
        return _MEASURE_RESULT_FAIL;
    }

    if(ScalerMeasureCheckAutoBoundaryResult(&(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        return _MEASURE_RESULT_FAIL;
    }

    //===========================================================================================
    // 4. Detect interlace format
    //===========================================================================================

    // Check interlace by flag
    if(ScalerMeasureInterlaceCheck(enumSourceType, enumInputPort) == _TRUE)
    {
        DebugMessageMeasure("Interlace: detect by flag", 0x00);
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        // Update video field
        if(ScalerGetBit(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()), _BIT6) == _BIT6)
        {
            g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VideoField = _TRUE;
        }
#endif
    }

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(
        &(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData),
        &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData),
        enumSourceType,
        enumInputPort);

    //===========================================================================================
    // 5. Double-check current timing
    //===========================================================================================

    // Check consistency between different measure results
    if(ScalerMeasureCheckInputInfoConsistency(enumSourceType, enumInputPort) == _FALSE)
    {
        return _MEASURE_RESULT_FAIL;
    }

    //===========================================================================================
    // 6. Measure final settings
    //===========================================================================================

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_420_SUPPORT == _ON)
    ScalerColor420To422FinalSettingByPath(GET_MEASURE_INPUT_PATH(), enumInputPort);
#endif
#endif

#if(_COLOR_IP_3DDI == _ON)
    //===========================================================================================
    // Set 3DDI
    //===========================================================================================
    if(Scaler3DDIEnableDecision(GET_MEASURE_INPUT_PATH(), enumInputPort) == _TRUE)
    {
        SET_3DDI_STATUS(GET_MEASURE_INPUT_PATH(), _ON);
        ScalerMeasureSetInputPath(ScalerRegionGetInputDataPath(ScalerMeasureGetResultPointerRegion()));
        ScalerVgipSetInputPath(GET_MEASURE_INPUT_PATH());

        Scaler3DDISettingProc(GET_MEASURE_INPUT_PATH());

        // HSWidth will be 3 after 3DDI
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHSWidth = 3;

        // Repeat auto func measure
        if(ScalerMeasureUpdateAutoPosition(enumSourceType, enumInputPort) == _FALSE)
        {
            return _MEASURE_RESULT_FAIL;
        }

        // Update input timing data
        ScalerMeasureUpdateInputTimingData(&(g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData), &(g_pstMeasureRegionTimingInfoPointer->stAutoActiveData), enumSourceType, enumInputPort);

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
#if(_HDMI_SUPPORT == _ON)
        // 3DDI HW measure Vstart FC set even/odd line
        if(Scaler3DDIModifyTiming(GET_MEASURE_INPUT_PATH()) == _FALSE)
        {
            return _MEASURE_RESULT_FAIL;
        }
#endif
#endif
    }
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _MEASURE_RESULT_FAIL;
    }
#endif

    // Start on-line measure
    ScalerMeasureSetOnlineMeasure(enumSourceType, enumInputPort, GET_MEASURE_INPUT_PATH(), GET_INPUT_TIMING_VFREQ());

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    // Decide I-domain path setting in format conversion
    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        // Final format conversion setting
        ScalerFmtCnvFinalSetting(enumInputPort, GET_MEASURE_INPUT_PATH(), _WAIT);

        // Check VS bypass
        if(ScalerMeasureCheckVsBypass(enumSourceType, enumInputPort) == _TRUE)
        {
            ScalerVgipSetVsBypassEnable(GET_MEASURE_INPUT_PATH(), _ENABLE);
        }
    }

    // Double-cheeck auto-function again when timing is affected
    if(ScalerFmtCnvCheckIDomainTimingAffected(GET_MEASURE_INPUT_PATH(), enumInputPort) == _TRUE)
    {
        // Update auto-funciton position result
        if(ScalerMeasureUpdateAutoPosition(enumSourceType, enumInputPort) == _FALSE)
        {
            return _MEASURE_RESULT_FAIL;
        }
    }
#endif

    // Perform measure final setting
    if(ScalerMeasureFinalSetting(enumSourceType, enumInputPort) == _FALSE)
    {
        DebugMessageMeasure("Final setting in measure fail", 0x00);
        return _MEASURE_RESULT_FAIL;
    }

    return _MEASURE_RESULT_PASS;
}

//--------------------------------------------------
// Description  : Duplicate interlace settting for measure
// Input Value  : enumDuplicatePath --> duplicate source path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureDuplicateInterlaceSetting(EnumInputDataPath enumDuplicatePath)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(enumDuplicatePath);
    WORD usSUPageAddr = ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN());

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);
        BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

        if((GET_MEASURE_INPUT_PATH() & enumCurrPath) != 0)
        {
            // Select VGIP field detect latch edge
            SET_PAGED_BIT(ucIdomainPage, P0_11_M1_VGIP_SIGINV, ~_BIT5, GET_PAGED_BIT(ucIDomainPage, P0_11_M1_VGIP_SIGINV, _BIT5));

            // Select VGIP field source; Select Odd delay one line field
            SET_PAGED_BIT(ucIdomainPage, P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), GET_PAGED_BIT(ucIDomainPage, P0_13_M1_VGIP_ODD_CTRL, (_BIT7 | _BIT6 | _BIT0)));

            // Clear interlace detect flag
            SET_PAGED_BIT(ucIdomainPage, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Select video compensation field
            ScalerSetBit(usSUPageAddr, ~(_BIT7 | _BIT6 | _BIT5), ScalerGetBit(usSUPageAddr, (_BIT7 | _BIT6)));
        }
    }
}
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)

#if(_GLOBAL_DIMMING_PATTERN_ESTIMATE == _ON)
//--------------------------------------------------
// Description  : Auto measure initial value for global dimming
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void ScalerMeasureGlobalDimmingPatternEstimateInitial(void)
{
    // FHD box size
    WORD usBoxWidth = 320;
    WORD usBoxHeight = 50;

    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();
    WORD usVheight = GET_INPUT_TIMING_VHEIGHT();

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    BYTE ucFbStatus = ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN);
#endif

    StructAutoActiveData stAutoData = {0};

    // calulate 5% box width
    while((((DWORD)_PANEL_DH_WIDTH) * ((DWORD)_PANEL_DV_HEIGHT) / 20) > ((DWORD)usBoxWidth * usBoxWidth))
    {
        usBoxWidth++;

        // larger than 8K
        if(usBoxWidth > 1400)
        {
            break;
        }
    }

    // add 10% margin
    usBoxWidth += (usBoxWidth / 10);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ucFbStatus == _TRUE)
    {
        usBoxHeight /= 2;
        usVheight /= 2;

        // Set auto-function digital measure for M1
        ScalerMeasureSetAuto(_NORMAL_MEASURE, _INPUT_PATH_M1);

        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1) == _FALSE) ||
           (ScalerMeasureGetAutoBoundaryResult(&stAutoData, _INPUT_PATH_M1, _NOT_WAIT) == _FALSE))
        {
            return;
        }

        // set auto boundary
        ScalerMeasureSetAutoFuncHBoundary(stAutoData.usHActiveStart + usBoxWidth,
                                          stAutoData.usHActiveStart + usHwidth / 2,
                                          _INPUT_PATH_M1);

        ScalerMeasureSetAutoFuncVBoundary(stAutoData.usVActiveStart + usBoxHeight,
                                          stAutoData.usVActiveStart + usVheight - usBoxHeight,
                                          _INPUT_PATH_M1);

        // Set auto-function digital measure for S1
        ScalerMeasureSetAuto(_NORMAL_MEASURE, _INPUT_PATH_S1);

        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_S1) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_S1) == _FALSE) ||
           (ScalerMeasureGetAutoBoundaryResult(&stAutoData, _INPUT_PATH_S1, _NOT_WAIT) == _FALSE))
        {
            return;
        }

        ScalerMeasureSetAutoFuncHBoundary(stAutoData.usHActiveStart,
                                          stAutoData.usHActiveStart + usHwidth / 2 - usBoxWidth,
                                          _INPUT_PATH_S1);

        ScalerMeasureSetAutoFuncVBoundary(stAutoData.usVActiveStart + usBoxHeight,
                                          stAutoData.usVActiveStart + usVheight - usBoxHeight,
                                          _INPUT_PATH_S1);
    }
    else
#endif
    {
        if(ScalerFmtCnvFtoPGetStatus(_INPUT_PATH_M1_M2) == _TRUE)
        {
            usBoxHeight /= 2;
            usVheight /= 2;
        }

        switch(ScalerFmtCnvHalfSDGetFactor(_INPUT_PATH_M1_M2))
        {
            case 2:
                usBoxWidth /= 2;
                usHwidth /= 2;
                break;

            case 4:
                usBoxWidth /= 4;
                usHwidth /= 4;
                break;

            default:
                break;
        }

        // Set auto-function digital measure
        ScalerMeasureSetAuto(_NORMAL_MEASURE, _INPUT_PATH_M1);

        // Wait for 2 latched IVS; Pop out auto-function result
        if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1) == _FALSE) ||
           (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, _INPUT_PATH_M1) == _FALSE) ||
           (ScalerMeasureGetAutoBoundaryResult(&stAutoData, _INPUT_PATH_M1, _NOT_WAIT) == _FALSE))
        {
            return;
        }

        // set auto boundary
        ScalerMeasureSetAutoFuncHBoundary(stAutoData.usHActiveStart + usBoxWidth,
                                          stAutoData.usHActiveStart + usHwidth - usBoxWidth,
                                          _INPUT_PATH_M1_M2);

        ScalerMeasureSetAutoFuncVBoundary(stAutoData.usHActiveStart + usBoxHeight,
                                          stAutoData.usHActiveStart + usVheight - usBoxHeight,
                                          _INPUT_PATH_M1_M2);
    }

    // Auto Balance result mode
    ScalerSetBit(P0_76_RED_NOISE_MARGIN, ~_BIT0, _BIT0);

    // R channel
    ScalerSetByte(P0_7A_AUTO_ADJ_CTRL0, 0x02);

    // digital enable and max value
    ScalerSetByte(P0_7D_AUTO_ADJ_CTRL1, 0xA0);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Set Sub auto
    if(ucFbStatus == _TRUE)
    {
        // Auto Balance result mode
        ScalerSetBit(P80_76_S1_RED_NOISE_MARGIN, ~_BIT0, _BIT0);

        // R channel
        ScalerSetByte(P80_7A_S1_AUTO_ADJ_CTRL0, 0x02);

        // digital enable and max value
        ScalerSetByte(P80_7D_S1_AUTO_ADJ_CTRL1, 0xA0);
    }
#endif
}

//--------------------------------------------------
// Description  : MeasureAuto ready status
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void ScalerMeasureGlobalDimmingPatternEstimateStart(void)
{
    // restart auto-function
    if(ScalerGetBit(P0_7D_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
    {
        ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
    {
        if(ScalerGetBit(P80_7D_S1_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            ScalerSetBit(P80_7D_S1_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Auto measure value for global dimming
// Input Value  : ucColor
// Output Value : 0~255
//--------------------------------------------------
BYTE ScalerMeasureGlobalDimmingPatternEstimateGetResult(BYTE ucColor)
{
    BYTE ucResult = 255;

    switch(ucColor)
    {
        case _AUTO_RED_CHANNEL:
            ucResult = ScalerGetByte(P0_84_AUTO_PHASE_3);
            break;

        case _AUTO_GREEN_CHANNEL:
            ucResult = ScalerGetByte(P0_85_AUTO_PHASE_2);
            break;

        case _AUTO_BLUE_CHANNEL:
            ucResult = ScalerGetByte(P0_86_AUTO_PHASE_1);
            break;

        default:
            break;
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
    {
        BYTE ucResultSub = 255;

        switch(ucColor)
        {
            case _AUTO_RED_CHANNEL:
                ucResultSub = ScalerGetByte(P80_84_S1_AUTO_PHASE_3);
                break;

            case _AUTO_GREEN_CHANNEL:
                ucResultSub = ScalerGetByte(P80_85_S1_AUTO_PHASE_2);
                break;

            case _AUTO_BLUE_CHANNEL:
                ucResultSub = ScalerGetByte(P80_86_S1_AUTO_PHASE_1);
                break;

            default:
                break;
        }

        ucResult = MAXOF(ucResult, ucResultSub);
    }
#endif

    return ucResult;
}
#endif

#if(_DYNAMIC_COLOR_AUTO_MEASURE == _ON)
//--------------------------------------------------
// Description  : Transfer D domain to I domain Path Enable
// Input Value  : usDHStart, usDHEnd
// Output Value : Main or Sub enable
//--------------------------------------------------
EnumMeasureMainSubStatus ScalerMeasureDynamicColorGetMainSubStatus(WORD usDHStart, WORD usDHEnd)
{
    usDHStart = usDHStart;
    usDHEnd = usDHEnd;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_I_DOMAIN) == _TRUE)
    {
        if((usDHStart < (_PANEL_DH_WIDTH / 2)) && (usDHEnd >= (_PANEL_DH_WIDTH / 2)))
        {
            return _MEASURE_MAIN_SUB_ENABLE;
        }
        else if(usDHStart < (_PANEL_DH_WIDTH / 2))
        {
            return _MEASURE_MAIN_ONLY_ENABLE;
        }
        else if(usDHStart >= (_PANEL_DH_WIDTH / 2))
        {
            return _MEASURE_SUB_ONLY_ENABLE;
        }
    }
#endif

    return _MEASURE_MAIN_ONLY_ENABLE;
}

//--------------------------------------------------
// Description  : Auto measure initial value for setting HV boundary
// Input Value  : DHstart, DHend, DVstart, DVend, Main or Sub enable
// Output Value : None
//--------------------------------------------------
void ScalerMeasureDynamicColorInitial(StructTimingInfo *pstTimingInfo, WORD usDHStart, WORD usDHEnd, WORD usDVStart, WORD usDVEnd)
{
    WORD usMainHStart = 0;
    WORD usMainHEnd = 0;
    WORD usSubHStart = 0;
    WORD usSubHEnd = 0;

    WORD usIHStart = 0;
    WORD usIHEnd = 0;
    WORD usIVStart = 0;
    WORD usIVEnd = 0;

    BYTE ucExtension = 0;
    BYTE ucHstartFactor = ScalerFmtCnvHalfSDGetFactor(pstTimingInfo->enumInputDataPath);
    EnumMeasureMainSubStatus enumMeasureMainSubStatus = ScalerMeasureDynamicColorGetMainSubStatus(usDHStart, usDHEnd);

    // Transfer D domain active to I domain active
    usIHStart = ScalerMeasureTransDDomainToIDomainHorizonalPosition(pstTimingInfo->usHWidth, usDHStart);
    usIHEnd = ScalerMeasureTransDDomainToIDomainHorizonalPosition(pstTimingInfo->usHWidth, usDHEnd);
    usIVStart = ScalerMeasureTransDDomainToIDomainVerticalPosition(pstTimingInfo->usVHeight, usDVStart);
    usIVEnd = ScalerMeasureTransDDomainToIDomainVerticalPosition(pstTimingInfo->usVHeight, usDVEnd);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(pstTimingInfo->enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2)
    {
        if(ScalerFmtCnvFBGetFBModeStatus() == _TRUE)
        {
            ucExtension = GET_FMTCNV_EXTENSION_LEN();
        }
    }
#endif

    switch(enumMeasureMainSubStatus)
    {
        case _MEASURE_MAIN_SUB_ENABLE:
            usMainHStart = usIHStart / ucHstartFactor;
            usMainHEnd = (pstTimingInfo->usHWidth / 2) / ucHstartFactor;

            usSubHStart = ucExtension;
            usSubHEnd = (usIHEnd - (pstTimingInfo->usHWidth / 2)) / ucHstartFactor + ucExtension;

            usIVStart /= 2;
            usIVEnd /= 2;
            break;

        case _MEASURE_SUB_ONLY_ENABLE:
            usIVStart /= 2;
            usIVEnd /= 2;

            usSubHStart = (usIHStart - (pstTimingInfo->usHWidth / 2)) / ucHstartFactor + ucExtension;
            usSubHEnd = (usIHEnd - (pstTimingInfo->usHWidth / 2)) / ucHstartFactor + ucExtension;
            break;

        default:
        case _MEASURE_MAIN_ONLY_ENABLE:
            usIVStart /= 2;
            usIVEnd /= 2;

            usMainHStart = usIHStart / ucHstartFactor;
            usMainHEnd = usIHEnd / ucHstartFactor;
            break;
    }

    if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
    {
        // set auto boundary
        ScalerMeasureSetAutoFuncHBoundary(pstTimingInfo->usHStart + usMainHStart,
                                          pstTimingInfo->usHStart + usMainHEnd,
                                          _INPUT_PATH_M1);

        ScalerMeasureSetAutoFuncVBoundary(pstTimingInfo->usVStart + usIVStart,
                                          pstTimingInfo->usVStart + usIVEnd,
                                          _INPUT_PATH_M1);

        // Auto Balance result mode (old mode)
        ScalerSetBit(P0_76_RED_NOISE_MARGIN, ~_BIT0, 0x00);

        // accumulation mode
        ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
    {
        ScalerMeasureSetAutoFuncHBoundary(pstTimingInfo->usHStart + usSubHStart,
                                          pstTimingInfo->usHStart + usSubHEnd,
                                          _INPUT_PATH_S1);

        ScalerMeasureSetAutoFuncVBoundary(pstTimingInfo->usVStart + usIVStart,
                                          pstTimingInfo->usVStart + usIVEnd,
                                          _INPUT_PATH_S1);

        // Auto Balance result mode (old mode)
        ScalerSetBit(P80_76_S1_RED_NOISE_MARGIN, ~_BIT0, 0x00);

        // accumulation mode
        ScalerSetBit(P80_7D_S1_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
    }
#endif
}

//--------------------------------------------------
// Description  : MeasureAuto ready status
// Input Value  : R/G/B Channel, Main or Sub enable
// Output Value : None
//--------------------------------------------------
void ScalerMeasureDynamicColorSetAutoMeasure(WORD usDHStart, WORD usDHEnd, EnumAutoChannelType enumAutoChannelType)
{
    EnumMeasureMainSubStatus enumMeasureMainSubStatus = ScalerMeasureDynamicColorGetMainSubStatus(usDHStart, usDHEnd);

    switch(enumAutoChannelType)
    {
        case _AUTO_RED_CHANNEL:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
            {
                ScalerSetBit(P80_7A_S1_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), _BIT1);
            }
#endif
            if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
            {
                ScalerSetBit(P0_7A_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), _BIT1);
            }
            break;

        case _AUTO_GREEN_CHANNEL:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
            {
                ScalerSetBit(P80_7A_S1_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), _BIT0);
            }
#endif
            if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
            {
                ScalerSetBit(P0_7A_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), _BIT0);
            }
            break;

        case _AUTO_BLUE_CHANNEL:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
            {
                ScalerSetBit(P80_7A_S1_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), 0x00);
            }
#endif
            if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
            {
                ScalerSetBit(P0_7A_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), 0x00);
            }
            break;

        case _AUTO_RGB_CHANNEL:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
            {
                ScalerSetBit(P80_7A_S1_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
#endif
            if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
            {
                ScalerSetBit(P0_7A_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
            break;

        default:
            break;
    }

    if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
    {
        // restart auto-function
        if(ScalerGetBit(P0_7D_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);
        }
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
    {
        if(ScalerGetBit(P80_7D_S1_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            ScalerSetBit(P80_7D_S1_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Auto measure value for dynamic crosshair color
// Input Value  : pstActiveRegion --> measure result pointer
//                main, sub enable or not
//                bWait --> wait auto-function stop or not
// Output Value : _TRUE if auto-function measure passed
//--------------------------------------------------
bit ScalerMeasureDynamicColorGetResult(BYTE *pucColorAverageValue, WORD usDHStart, WORD usDHEnd, bit bWait)
{
    DWORD ulAutoSum = 0;
    DWORD ulArea = 0;
    EnumMeasureMainSubStatus enumMeasureMainSubStatus = ScalerMeasureDynamicColorGetMainSubStatus(usDHStart, usDHEnd);
    StructAutoActiveData stAutoData = {0};

    if((enumMeasureMainSubStatus & _BIT0) == _BIT0)
    {
        if(bWait == _NOT_WAIT)
        {
            if(ScalerGetBit(P0_7D_AUTO_ADJ_CTRL1, _BIT0) != 0x00)
            {
                return _FALSE;
            }
        }

        // pop up H/V start
        ScalerMeasureGetAutoBoundaryResult(&stAutoData, _INPUT_PATH_M1, ((ScalerGetBit(P0_7D_AUTO_ADJ_CTRL1, _BIT0) != 0x00) ? _WAIT : _NOT_WAIT));

        ulAutoSum += (((DWORD)ScalerGetByte(P0_84_AUTO_PHASE_3) << 24) | ((DWORD)ScalerGetByte(P0_85_AUTO_PHASE_2) << 16) | ((DWORD)ScalerGetByte(P0_86_AUTO_PHASE_1) << 8) | (DWORD)ScalerGetByte(P0_87_AUTO_PHASE_0));
        ulArea += ((DWORD)stAutoData.usHActiveEnd - stAutoData.usHActiveStart + 1) * ((DWORD)stAutoData.usVActiveEnd - stAutoData.usVActiveStart + 1);

        if(ScalerGetBit(P0_7A_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            ulAutoSum /= 3;
        }
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if((enumMeasureMainSubStatus & _BIT1) == _BIT1)
    {
        if(bWait == _NOT_WAIT)
        {
            if(ScalerGetBit(P80_7D_S1_AUTO_ADJ_CTRL1, _BIT0) != 0x00)
            {
                return _FALSE;
            }
        }

        // pop up H/V start
        ScalerMeasureGetAutoBoundaryResult(&stAutoData, _INPUT_PATH_S1, ((ScalerGetBit(P80_7D_S1_AUTO_ADJ_CTRL1, _BIT0) != 0x00) ? _WAIT : _NOT_WAIT));

        ulAutoSum += (((DWORD)ScalerGetByte(P80_84_S1_AUTO_PHASE_3) << 24) | ((DWORD)ScalerGetByte(P80_85_S1_AUTO_PHASE_2) << 16) | ((DWORD)ScalerGetByte(P80_86_S1_AUTO_PHASE_1) << 8) | (DWORD)ScalerGetByte(P80_87_S1_AUTO_PHASE_0));
        ulArea += ((DWORD)stAutoData.usHActiveEnd - stAutoData.usHActiveStart + 1) * ((DWORD)stAutoData.usVActiveEnd - stAutoData.usVActiveStart + 1);

        if(ScalerGetBit(P80_7A_S1_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            ulAutoSum /= 3;
        }
    }
#endif

    if(ulArea > 0)
    {
        *pucColorAverageValue = ulAutoSum / ulArea;
    }
    else
    {
        *pucColorAverageValue = 0;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : judge if need HFreq check
// Input Value  : none
// Output Value : _TRUE if ignore HFreq check
//--------------------------------------------------
bit ScalerMeasureIgnoreHFreqCheck(EnumInputPort enumInputPort)
{
    switch(ScalerSyncGetPortType(enumInputPort))
    {
#if(_HDMI21_FVA_SUPPORT == _ON)
        case _PORT_HDMI:

            // SRC sent FVA Content
            if(ScalerTmdsMacRxHdmi21GetFvaFactor(enumInputPort) > 1)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:

            if(ScalerDpMacStreamRxGetDPFRegenMode(enumInputPort) == _DPF_MODE_FRAME_SYNC_BE)
            {
                return _TRUE;
            }

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

