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
// ID Code      : ScalerIDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IDOMAIN__

#include "ScalerFunctionInclude.h"
#include "IDomain/ScalerIDomain.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usIDomainVgipVDelayInitial;

StructIDomainPathInfo g_pstIDomainPathInfo[_HW_I_DOMAIN_PATH_COUNT] =
{
#if(_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON)
    {_INPUT_PATH_M1, 0x00, _HW_PAGED_M1_ON_LINE_MEAS, 0x00, _VGIP_M1_DB_ENABLE, _I_M1_DB_ENABLE, _BIT0, _BIT3, 0x00, _BIT7},
#endif

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
    {_INPUT_PATH_M2, 0x40, _HW_PAGED_M2_ON_LINE_MEAS, 0x03, _VGIP_M2_DB_ENABLE, _I_M2_DB_ENABLE, _BIT1, _BIT2, 0x01, _BIT6},
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S1, 0x80, _HW_PAGED_S1_ON_LINE_MEAS, 0x06, _VGIP_S1_DB_ENABLE, _I_S1_DB_ENABLE, _BIT2, _BIT1, 0x02, _BIT5},
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S2, 0xC0, _HW_PAGED_S2_ON_LINE_MEAS, 0x09, _VGIP_S2_DB_ENABLE, _I_S2_DB_ENABLE, _BIT3, _BIT0, 0x03, _BIT4},

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S3, 0x17, _HW_PAGED_S2_ON_LINE_MEAS, 0x0C, _VGIP_S3_DB_ENABLE, _I_S3_DB_ENABLE, _BIT4, _BIT4, 0x04, _BIT3},
#endif
#if(_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON)
    {_INPUT_PATH_S4, 0xDC, _HW_PAGED_S2_ON_LINE_MEAS, 0x0F, _VGIP_S4_DB_ENABLE, _I_S4_DB_ENABLE, _BIT5, _BIT5, 0x05, _BIT2},
#endif
#endif
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check if to enable VGIP digital capture
// Input Value  : N/A
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerIDomainCheckDigitalCapture(void)
{
#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
    {
        return _TRUE;
    }
#endif

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
#if(_HDMI_FRL_SUPPORT == _ON)
    if((GET_MDOMAIN_SOURCE_TYPE() == _SOURCE_HDMI) && (ScalerTmdsMacRxGetHdmiVer(GET_MDOMAIN_INPUT_PORT()) != _FROM_HDMI_TMDS_MAC))
    {
        return _TRUE;
    }
#endif
#endif

#if((_PIXEL_SHIFT_SUPPORT == _ON) &&\
    (_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN))
    if(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
        {
            return _FALSE;
        }
#else
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            return _FALSE;
        }
#endif
    }
#endif

#if(_COLOR_IP_3DDI == _ON)
    if((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2) && (GET_3DDI_STATUS(GET_MDOMAIN_INPUT_DATA_PATH()) == _ON))
    {
        return _TRUE;
    }
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_EAGLE_SIGHT_SUB) &&
       (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2))
    {
        if((GET_INPUT_TIMING_HSTART() + GET_INPUT_TIMING_HWIDTH()) >= _VGIP_IH_START_MAX_VALUE)
        {
            return _FALSE;
        }
    }
#endif

#if(_PBP_LR_FRAME_SYNC_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_EQUAL) ||
       (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_L_LARGE) ||
       (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_R_LARGE))
    {
        return _TRUE;
    }
#endif

    return (ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE);
}

//--------------------------------------------------
// Description  : Set VGIP Capture Window
// Input Value  : Capture Type, H/V Active and Start
// Output Value : None
//--------------------------------------------------
void ScalerIDomainVgipSetInputCapture(void)
{
    bit bDigitalCapture = _FALSE;

    ScalerVgipSetInputPath(GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerVgipCaptureEnable(_ENABLE);
    SET_VGIP_INITIAL_VDELAY(0);
    bDigitalCapture = ScalerIDomainCheckDigitalCapture();
#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV))
    bDigitalCapture = ScalerRotationCheckVFrontPorch(bDigitalCapture);
#endif

    if(bDigitalCapture == _TRUE)
    {
        WORD usInputHstart = ScalerIDomainGetInputHorTimingAfterFmtCnv(GET_INPUT_TIMING_HSTART(), GET_MDOMAIN_INPUT_DATA_PATH());

#if(_HW_FORMAT_CONVERSION_SUPPORT == _TRUE)
        // Disable format conversion background color
        ScalerFmtCnvSetBackgroundStatus(GET_MDOMAIN_INPUT_DATA_PATH(), _FALSE);
#endif

        // Enable digital capture
        ScalerVgipSetDigitalCaptureStatus(_ENABLE);

        // Set VGIP H Capture Width
        ScalerVgipSetCaptureHWidth(GET_MDOMAIN_INPUT_HWIDTH());

        // Set VGIP V Capture Heigth
        ScalerVgipSetCaptureVHeight(GET_MDOMAIN_INPUT_VHEIGHT());

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        if((ScalerFmtCnvEagleSightEnableStatus() == _TRUE) && (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S3_S4))
        {
            ScalerVgipSetCaptureHStartPosition(0x00);
        }
        else
#endif
        {
            // Set VGIP H capture start position
            if(GET_MDOMAIN_INPUT_HSTART() > usInputHstart)
            {
                ScalerVgipSetCaptureHStartPosition(GET_MDOMAIN_INPUT_HSTART() - usInputHstart);
            }
            else
            {
                ScalerVgipSetCaptureHStartPosition(0x00);
            }
        }

        // Set VGIP V capture start position
        ScalerIDomainSetDigitalCaptureIVstart(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_INPUT_VSTART(), GET_INPUT_TIMING_VSTART());

        // Set VGIP capture delay
        ScalerVgipSetCaptureHDelay(0);
        ScalerVgipSetCaptureVDelay(0);
    }
    else
    {
        WORD usIHDelay = 0;
        WORD usIHStart = 0;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _TRUE)
        // Enable format conversion background color
        if(GET_COLOR_SPACE_RGB(GET_MDOMAIN_COLOR_SPACE()) == _TRUE)
        {
            ScalerFmtCnvSetBackgroundColor(GET_MDOMAIN_INPUT_DATA_PATH(), 0x00, 0x00, 0x00);
        }
        else
        {
            ScalerFmtCnvSetBackgroundColor(GET_MDOMAIN_INPUT_DATA_PATH(), 0x80, 0x00, 0x80);
        }
        ScalerFmtCnvSetBackgroundStatus(GET_MDOMAIN_INPUT_DATA_PATH(), _TRUE);
#endif

        // Disable digital capture
        ScalerVgipSetDigitalCaptureStatus(_DISABLE);

        // Set VGIP H Capture Width
        ScalerVgipSetCaptureHWidth(GET_MDOMAIN_INPUT_HWIDTH());

        // Set VGIP V Capture Heigth
        ScalerVgipSetCaptureVHeight(GET_MDOMAIN_INPUT_VHEIGHT());

        if(GET_MDOMAIN_INPUT_HSTART() <= _VGIP_IH_CAPTURE_MIN_VALUE)
        {
            GET_MDOMAIN_INPUT_HSTART() = _VGIP_IH_CAPTURE_MIN_VALUE + 1;
        }

        usIHStart = ScalerIDomainVgipIHCaptureMaxEstimate(GET_MDOMAIN_INPUT_HSTART());

        usIHDelay = (GET_MDOMAIN_INPUT_HSTART() > usIHStart) ? (GET_MDOMAIN_INPUT_HSTART() - usIHStart) : 0;

        SET_MDOMAIN_INPUT_HSTART(usIHStart);

        // Set VGIP H Capture Start Position
        ScalerVgipSetCaptureHStartPosition(GET_MDOMAIN_INPUT_HSTART());

        // Front Porch is Not Enough
        if(GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT() + 3 >= GET_MDOMAIN_INPUT_VTOTAL())
        {
            // Increase Front Porch by VDelay
            SET_VGIP_INITIAL_VDELAY(GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VHEIGHT() + 3 - GET_MDOMAIN_INPUT_VTOTAL());
            SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() - GET_VGIP_INITIAL_VDELAY());
        }
        else
        {
            SET_VGIP_INITIAL_VDELAY(0);
        }

        // Check if V capture start exceeds maximum value
        if(GET_MDOMAIN_INPUT_VSTART() > _VGIP_IV_CAPTURE_MAX_VALUE)
        {
            SET_VGIP_INITIAL_VDELAY(GET_VGIP_INITIAL_VDELAY() + (GET_MDOMAIN_INPUT_VSTART() - _VGIP_IV_CAPTURE_MAX_VALUE));
            SET_MDOMAIN_INPUT_VSTART(_VGIP_IV_CAPTURE_MAX_VALUE);
        }

        // Set VGIP capture delay
        ScalerVgipSetCaptureHDelay(usIHDelay);

        switch(ScalerMDomainGetFrameSyncMode())
        {
#if(_FRC_SUPPORT == _ON)
            case _MN_FRAME_SYNC_MODE:

                break;
#endif

            case _FRAME_SYNC_MODE:

                if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
                {
                    ScalerIDomainVgipIVDelayIVstStepAdjust(GET_VGIP_INITIAL_VDELAY());
                }

                break;

            default:

                // Set VGIP V Capture  Start Position
                ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());

                ScalerVgipSetCaptureVDelay(GET_VGIP_INITIAL_VDELAY());

                break;
        }
    }

    DebugMessageScaler("9. Set Capture usHWidth", GET_MDOMAIN_INPUT_HWIDTH());
    DebugMessageScaler("9. Set Capture usHStart", GET_MDOMAIN_INPUT_HSTART());
    DebugMessageScaler("9. Set Capture usVHeight", GET_MDOMAIN_INPUT_VHEIGHT());
    DebugMessageScaler("9. Set Capture usVStart", GET_MDOMAIN_INPUT_VSTART());
}

//--------------------------------------------------
// Description  : IVSdelay need to setting several times
// Input Value  : Initial IVS delay
// Output Value : N.A.
//--------------------------------------------------
void ScalerIDomainVgipIVDelayIVstStepAdjust(WORD usInitialIVDelay)
{
    WORD usIVDelayStep = 1;
    WORD usIVDelayTemp = 0;
    WORD usDVtotal = 0;
    BYTE ucSettingCounter = 0;


    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

    usDVtotal = ScalerMDomainGetDVtotalLastline();
    SET_MDOMAIN_OUTPUT_VTOTAL(usDVtotal);

    if(GET_MDOMAIN_OUTPUT_VTOTAL() > (GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT() + _PANEL_FRONT_PORCH_LIMIT))
    {
        usIVDelayStep = (GET_MDOMAIN_OUTPUT_VTOTAL() - GET_MDOMAIN_OUTPUT_VBSTART() - GET_MDOMAIN_OUTPUT_VBHEIGHT() - _PANEL_FRONT_PORCH_LIMIT);
        usIVDelayStep = GET_DWORD_MUL_DIV(usIVDelayStep, GET_MDOMAIN_INPUT_VTOTAL(), GET_MDOMAIN_OUTPUT_VTOTAL());

        if(usIVDelayStep < 1)
        {
            usIVDelayStep = 1;
        }
    }
    else
    {
        DebugMessageFS("warning !!! Aspect ratio/ overscan maybe have garbage", 0);
    }

    ucSettingCounter = (abs(usInitialIVDelay - ScalerVgipGetCaptureVDelay()) / usIVDelayStep) + 1;

    do
    {
        if(usInitialIVDelay > ScalerVgipGetCaptureVDelay())
        {
            // Set VGIP V delay
            ScalerVgipSetCaptureVDelay(usInitialIVDelay);

            // Set VGIP V Capture  Start Position
            ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());
        }
        else
        {
            if((ScalerVgipGetCaptureVDelay() - usInitialIVDelay) <= usIVDelayStep)
            {
                // Set VGIP V delay
                ScalerVgipSetCaptureVDelay(usInitialIVDelay);

                // Set VGIP V Capture  Start Position
                ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());
            }
            else
            {
                usIVDelayTemp = ScalerVgipGetCaptureVDelay() - usIVDelayStep;

                // Step adjust IVdelay
                ScalerVgipSetCaptureVDelay(usIVDelayTemp);

                // Step adjust IVstart
                ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART() + usInitialIVDelay - usIVDelayTemp);
            }

            DebugMessageFS("IVDelay step step", ScalerVgipGetCaptureVDelay());
        }

        ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

        ucSettingCounter--;
    }
    while((usInitialIVDelay != ScalerVgipGetCaptureVDelay()) && (ucSettingCounter > 0));
}

//--------------------------------------------------
// Description  : Estimate Max Allowable H Capture Start
// Input Value  : Current H Start
// Output Value : Max Allowable H Start
//--------------------------------------------------
WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition)
{
    if(usHPosition > _VGIP_IH_START_MAX_VALUE)
    {
        usHPosition = _VGIP_IH_START_MAX_VALUE;
    }
    else
    {
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
        {
            usHPosition = ((usHPosition + 1) & 0xFFFE);
        }
        else
#endif
        {
            if(usHPosition <= (_VGIP_IH_DELAY_MAX_VALUE + _VGIP_IH_CAPTURE_MIN_VALUE - (_MAX_H_POSITION_RANGE / 2)))
            {
                usHPosition = _VGIP_IH_CAPTURE_MIN_VALUE;
            }
            else
            {
                usHPosition -= (_VGIP_IH_DELAY_MAX_VALUE - (_MAX_H_POSITION_RANGE / 2));
            }
        }
    }

    return usHPosition;
}

//--------------------------------------------------
// Description  : Adjust IVS/IHS Delay to Gain Largest Position-Adjusting Range
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIDomainVgipAdjustIHVDelay(void)
{
    DWORD ulIV2DVdelayPixel = 0;
    WORD usIV2DVdelay = 0;
    WORD usIVSdelayExtend = 0;

    // Bypass IHV delay in digital capture
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1))
    {
        usIV2DVdelay = (ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) - (GET_MDOMAIN_INPUT_HTOTAL() / 2)) / GET_MDOMAIN_INPUT_HTOTAL();
    }
    else
    {
        usIV2DVdelay = ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) / GET_MDOMAIN_INPUT_HTOTAL();
    }

#if(_FRC_SUPPORT == _ON)
    if((GET_MEMORY_CONFIG_SELECT() != _FRAME_SYNC_LINE_BUFFER) &&
       (GET_MEMORY_CONFIG_SELECT() != _FREE_RUN_NO_INPUT))
    {
        // Set IVS Delay
        if((GET_MDOMAIN_INPUT_VSTART() + GET_VGIP_INITIAL_VDELAY()) > _VGIP_IV_CAPTURE_MIN_VALUE)
        {
            if(GET_MDOMAIN_INPUT_VSTART() > _HW_VGIP_IV_DELAY_BIT)
            {
                if((GET_MDOMAIN_INPUT_VSTART() - _HW_VGIP_IV_DELAY_BIT) < _VGIP_IV_CAPTURE_MIN_VALUE)
                {
                    ScalerVgipSetCaptureVDelay(GET_MDOMAIN_INPUT_VSTART() - _VGIP_IV_CAPTURE_MIN_VALUE);
                    SET_VGIP_INITIAL_VDELAY(GET_MDOMAIN_INPUT_VSTART() - _VGIP_IV_CAPTURE_MIN_VALUE);
                    SET_MDOMAIN_INPUT_VSTART(_VGIP_IV_CAPTURE_MIN_VALUE);
                }
                else
                {
                    ScalerVgipSetCaptureVDelay(_HW_VGIP_IV_DELAY_BIT);
                    SET_VGIP_INITIAL_VDELAY(_HW_VGIP_IV_DELAY_BIT);
                    SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() - _HW_VGIP_IV_DELAY_BIT);
                }
            }
            else
            {
                ScalerVgipSetCaptureVDelay(GET_MDOMAIN_INPUT_VSTART() - _VGIP_IV_CAPTURE_MIN_VALUE + GET_VGIP_INITIAL_VDELAY());
                SET_VGIP_INITIAL_VDELAY(GET_MDOMAIN_INPUT_VSTART() - _VGIP_IV_CAPTURE_MIN_VALUE + GET_VGIP_INITIAL_VDELAY());
                SET_MDOMAIN_INPUT_VSTART(_VGIP_IV_CAPTURE_MIN_VALUE);
            }
        }
        else
        {
            ScalerVgipSetCaptureVDelay(0);
            SET_VGIP_INITIAL_VDELAY(0);
            SET_MDOMAIN_INPUT_VSTART(_VGIP_IV_CAPTURE_MIN_VALUE);
        }

        // Set V Start
        ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());
    }
    else
#endif
    {
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            if(GET_MDOMAIN_INPUT_VSTART() > usIV2DVdelay)
            {
                // Remain IVSt = Raw IVSt - IVSDelay
                GET_MDOMAIN_INPUT_VSTART() = GET_MDOMAIN_INPUT_VSTART() - usIV2DVdelay;

                if(GET_MDOMAIN_INPUT_VSTART() <= (_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2))
                {
                    DebugMessageScaler("VStart too Small", GET_MDOMAIN_INPUT_VSTART());

                    // Get Difference of Remain IVSt and _VGIP_IV_CAPTURE_MIN_VALUE
                    usIVSdelayExtend = (_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2) - GET_MDOMAIN_INPUT_VSTART();
                    SET_MDOMAIN_INPUT_VSTART(_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2);
                }
                else
                {
                    usIVSdelayExtend = GET_MDOMAIN_INPUT_VSTART() % 2;
                    SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + GET_MDOMAIN_INPUT_VSTART() % 2);
                }
            }
        }
        else
#endif
        {
            if(GET_MDOMAIN_INPUT_VSTART() > usIV2DVdelay)
            {
                // Remain IVSt = Raw IVSt - IVSDelay
                SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() - usIV2DVdelay);

                if(GET_MDOMAIN_INPUT_VSTART() <= _VGIP_IV_CAPTURE_MIN_VALUE)
                {
                    DebugMessageScaler("VStart too Small", GET_MDOMAIN_INPUT_VSTART());

                    // Get Difference of Remain IVSt and _VGIP_IV_CAPTURE_MIN_VALUE
                    usIVSdelayExtend = _VGIP_IV_CAPTURE_MIN_VALUE - GET_MDOMAIN_INPUT_VSTART();
                    SET_MDOMAIN_INPUT_VSTART(_VGIP_IV_CAPTURE_MIN_VALUE);
                }
                else
                {
                    usIVSdelayExtend = 0;
                }
            }
        }

        // Check if V capture delay exceeds maximum value
        if((usIV2DVdelay - usIVSdelayExtend + GET_VGIP_INITIAL_VDELAY()) > _HW_VGIP_IV_DELAY_BIT)
        {
            // Modify IVSDelay = IVSDelay - IVSDelayExtend
            usIV2DVdelay -= usIVSdelayExtend;

            usIVSdelayExtend = (usIV2DVdelay + GET_VGIP_INITIAL_VDELAY()) - _HW_VGIP_IV_DELAY_BIT;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                usIVSdelayExtend += (usIVSdelayExtend % 2);
            }
#endif
            SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + usIVSdelayExtend);
        }

        // Move Delay to ivs to dvs
        ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART());

        // Set IVS to DVS Delay
        ScalerVgipSetCaptureVDelay((WORD)(usIV2DVdelay - usIVSdelayExtend + GET_VGIP_INITIAL_VDELAY()));

        ulIV2DVdelayPixel = ScalerMemoryGetIVS2DVSDelayPixel(&g_stMDomainInputData) - (DWORD)(usIV2DVdelay - usIVSdelayExtend) * GET_MDOMAIN_INPUT_HTOTAL();

        ScalerMemorySetIVS2DVSDelayPixel(ulIV2DVdelayPixel, &g_stMDomainInputData);
    }
}

//--------------------------------------------------
// Description  : Modify H Capture
// Input Value  : IH Capture Shift
// Output Value : None
//--------------------------------------------------
void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture)
{
    ScalerVgipSetCaptureHStartPosition(usDeltaIHCapture + ScalerVgipGetCaptureHStartPosition() - 2);

// What is this?
//    ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, (ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD) + ((BYTE)(usDeltaIHCapture / 16))));
//    ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, (ScalerGetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN) + ((BYTE)(usDeltaIHCapture / 16))));
}

//--------------------------------------------------
// Description  : Reset input data path process
// Input Value  : enumVgipInputPath --> target data path for reset
// Output Value : None
//--------------------------------------------------
void ScalerIDomainResetDataPath(EnumInputDataPath enumVgipInputPath)
{
    BYTE ucMeasurePage = ScalerMeasureGetOnlineMeasurePage(enumVgipInputPath);

    // Disable on-line measure
    SET_PAGED_BIT(ucMeasurePage, P3_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Clear on-line measure flag
    SET_PAGED_BYTE(ucMeasurePage, P3_15_MEAS_HS_VS_DELTA_CTL, 0x00);
    SET_PAGED_BYTE(ucMeasurePage, P3_16_MEAS_HS_VS_DELTA_IRQ, 0xF0);
    SET_PAGED_BYTE(ucMeasurePage, P3_17_MEAS_HS_VS_DELTA_WD, 0x00);
    SET_PAGED_BYTE(ucMeasurePage, P3_18_MEAS_HS_VS_ERROR_WD, 0x00);

    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumVgipInputPath & enumCurrPath) != 0)
        {
            BYTE ucIdomainPage = GET_IDOMAIN_REG_PAGE(ucIndex);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)

            // Reset format conversion
            ScalerFmtCnvFtoPControl(enumCurrPath, _DISABLE);
#endif
#endif

            // Reset VGIP
            ScalerVgipSetInputPath(enumCurrPath);

            // Disable VGIP capture
            ScalerVgipCaptureEnable(_DISABLE);

            // Reset to analog capture
            ScalerVgipSetDigitalCaptureStatus(_DISABLE);

            // Reset capture position
            ScalerVgipSetCaptureHDelay(0);
            ScalerVgipSetCaptureVDelay(0);
            ScalerVgipSetCaptureHStartPosition(0);
            ScalerVgipSetCaptureVStartPosition(0);
            ScalerVgipSetCaptureHWidth(0);
            ScalerVgipSetCaptureVHeight(0);

            // Disable VSD
            SET_PAGED_BIT(ucIdomainPage, P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_1)
            SET_PAGED_BIT(ucIdomainPage, P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT4), 0x00);
#endif
        }
    }

#if(_COLOR_IP_420_SUPPORT == _ON)
    // Reset format conversion 420
    ScalerColor420To422InitialByPath(enumVgipInputPath);
#endif

#if(_FRAME_RATE_SLOW_DOWN_SUPPORT == _ON)
    ScalerVgipResetSafeMode(enumVgipInputPath);
#endif

    // Reset timing info
    ScalerMeasureResetTimingInfo(enumVgipInputPath);

    // Reset global DB I domain trigger event
    ScalerGlobalIDDomainDBSetTriggerEventInitial(enumVgipInputPath, _DB_TRIGGER_EVENT_IVS);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    SET_I_DB_APPLY_POINT(_GLOBAL_APPLY_I);
#endif

    // Apply DB
    ScalerGlobalIDomainDBApply(enumVgipInputPath, _DB_APPLY_NO_POLLING);
}

//--------------------------------------------------
// Description  : Get on-line measure result from target input data path
// Input Value  : enumInputDataPath --> measure input data path
// Output Value : 1 or 2 or 4
//--------------------------------------------------
BYTE ScalerIDomainGetInputPathCount(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        default:
            return 0x01;

        case _INPUT_PATH_M1:
        case _INPUT_PATH_M2:
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S2:
        case _INPUT_PATH_S3:
        case _INPUT_PATH_S4:
            return 0x01;

        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S3_S4:
            return 0x02;

        case _INPUT_PATH_M1_M2_S1_S2:
            return 0x04;
    }
}

//--------------------------------------------------
// Description  : Get I domain double buffer apply bit
// Input Value  : enumInputDataPath --> input data path
// Output Value : Register page
//--------------------------------------------------
BYTE ScalerIDomainGetInputPathPage(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            return GET_IDOMAIN_REG_PAGE(ucIndex);
        }
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get I domain IRQ apply bit
// Input Value  : enumInputDataPath --> input data path
// Output Value : IRQ Register page
//--------------------------------------------------
BYTE ScalerIDomainGetIRQPageOffset(EnumInputDataPath enumInputDataPath)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            return GET_IDOMAIN_IRQ_REG_OFFSET(ucIndex);
        }
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get Input Horizontal Timing info after Format Conversion
// Input Value  : usInputHorizontal: Input Horizontal Timing info, enumInputDataPath
// Output Value : Input Horizontal Timing info after Format Conversion
//--------------------------------------------------
WORD ScalerIDomainGetInputHorTimingAfterFmtCnv(WORD usInputHorizontal, EnumInputDataPath enumInputDataPath)
{
    BYTE ucHFactor = 0x01;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
    ucHFactor *= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif
#endif

    if(ucHFactor > 0x01)
    {
        return (usInputHorizontal / ucHFactor);
    }
    else
    {
        return usInputHorizontal;
    }
}

//--------------------------------------------------
// Description  : I domain pattern generator enable
// Input Value  : enumInputDataPath, enumPGType, enable
// Output Value : None
//--------------------------------------------------
void ScalerIDomainPatternGenEnable(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT7, _BIT7);
            }
            else
            {
                ScalerSetDataPortBit(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT7, 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : I domain pattern generator enable
// Input Value  : enumInputDataPath, ucRed, ucGreen, ucBlue (0x00~0xFF)
// Output Value : None
//--------------------------------------------------
void ScalerIDomainPatternGenAdjustColor(EnumInputDataPath enumInputDataPath, BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    for(BYTE ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        if((enumInputDataPath & enumCurrPath) != 0)
        {
            // adjust PG mode to programmable
            ScalerSetDataPortBit(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_62_I_PG_R_CTRL_M1, ~(_BIT7 | _BIT6), _BIT7);

            // adjust init color
            ScalerSetDataPortByte(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_65_I_PG_R_INITIAL_M1, ucRed);
            ScalerSetDataPortByte(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_66_I_PG_G_INITIAL_M1, ucGreen);
            ScalerSetDataPortByte(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_67_I_PG_B_INITIAL_M1, ucBlue);

            // fix LSBs to 0
            ScalerSetDataPortBit(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_6E_I_PG_INITIAL_M_STEP_L_M1,
                                 ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetDataPortBit(GET_PAGED_ADDR(GET_IDOMAIN_REG_PAGE(ucIndex), P0_24_SD_ADDRESS_PORT_M1), _P0_25_PT_6F_I_PG_INITIAL_L_CTRL_M1,
                                 ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set IVstart when VGIP Digital Capture
// Input Value  : enumInputDataPath, usMdomainIVstart, usInputIVstart
// Output Value : None
//--------------------------------------------------
void ScalerIDomainSetDigitalCaptureIVstart(EnumInputDataPath enumInputDataPath, WORD usMdomainIVstart, WORD usInputIVstart)
{
#if((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    if(ScalerDrrIVSProduceByBE(GET_MDOMAIN_SOURCE_TYPE(), GET_MDOMAIN_INPUT_PORT()) == _TRUE)
    {
        SET_MDOMAIN_VGIP_VSYNC_BY_PASS_AFTER_I_DB(_ENABLE);

        // Set VGIP V capture start position
        if(usMdomainIVstart >= (usInputIVstart + _VGIP_IV_CAPTURE_MIN_VALUE))
        {
            SET_MDOMAIN_VGIP_VSYNC_BY_PASS(_DISABLE);

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
            if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
            {
                usMdomainIVstart -= 2;
            }
            else
#endif
            {
                usMdomainIVstart -= 1;
            }
        }
        else
        {
            SET_MDOMAIN_VGIP_VSYNC_BY_PASS(_ENABLE);
        }
    }
    else
    {
        SET_MDOMAIN_VGIP_VSYNC_BY_PASS(_DISABLE);
        SET_MDOMAIN_VGIP_VSYNC_BY_PASS_AFTER_I_DB(_DISABLE);
    }
#endif

    // Set VGIP V capture start position
    if(usMdomainIVstart > usInputIVstart)
    {
#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(enumInputDataPath) == _TRUE)
        {
            ScalerVgipSetCaptureVStartPosition(usMdomainIVstart - (usInputIVstart - (usInputIVstart % 2)));
        }
        else
#endif
        {
            ScalerVgipSetCaptureVStartPosition(usMdomainIVstart - usInputIVstart);
        }
    }
    else
    {
        ScalerVgipSetCaptureVStartPosition(0x00);
    }
}

//--------------------------------------------------
// Description  : I domain setting without I DB, need to set after I DB apply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIDomainSettingAfterIDB(void)
{
#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    if(GET_MDOMAIN_VGIP_VSYNC_BY_PASS_AFTER_I_DB() == _ENABLE)
    {
        ScalerDrrUpdateVsyncSetting();
    }
#endif
}

