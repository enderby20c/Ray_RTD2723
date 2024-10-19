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
// ID Code      : ScalerHdmiFrlMacRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIFRLMACRX__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx/ScalerHdmiFrlMacRx.h"

#if(_HDMI_FRL_SUPPORT == _ON)

#if((_INPUTCLOCK_RANG_HDMI21 >= 12000) && (_INPUTCLOCK_RANG_HDMI < 12000))
#warning "NOTE: If Necessary, Set _INPUTCLOCK_RANG_HDMI as 12000 for Supporting TMDS 4K2K@120 420!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_D1_HDMI_FRL_SUPPORT == _ON)
volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD1LinkTrainingInfo;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD2LinkTrainingInfo;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD3LinkTrainingInfo;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
volatile StructHdmiFrlLinkTrainingInfo g_stHdmiFrlMacRxD4LinkTrainingInfo;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : FRL MAC Reset Process
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerHdmiFrlMacRxResetProc(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerHdmiFrlMacRx3ResetProc();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerHdmiFrlMacRx4ResetProc();
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : FRL Clear FLT_Ready
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerHdmiFrlMacRxClrFltReady(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerHdmiFrlMacRx3ClrFltReady();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerHdmiFrlMacRx4ClrFltReady();
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get FRL MAC Dpf Pixel Mode
// Input Value  :
// Output Value : 1/2/4 Pixel Mode
//--------------------------------------------------
EnumHdmiFrlMacRxDpfPixelMode ScalerHdmiFrlMacRxGetDpfPixelMode(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerHdmiFrlMacRx3GetDpfPixelMode();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerHdmiFrlMacRx4GetDpfPixelMode();
            break;
#endif

        default:
            break;
    }

    return _HDMI_FRL_MAC_RX_DPF_PIXEL_MODE_NONE;
}

//--------------------------------------------------
// Description  : HDMI Enter Power saving check
// Input Value  : None
// Output Value : _TRUE means can enter power saving
//                _FALSE means during FRL CTS test
//--------------------------------------------------
bit ScalerHdmiFrlMacRxEnterPowerSavingCheck(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerHdmiFrlMacRx3EnterPowerSavingCheck();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerHdmiFrlMacRx4EnterPowerSavingCheck();
            break;
#endif

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDMI Enter Fake Power saving check
// Input Value  : None
// Output Value : _TRUE means can enter Fake power saving
//--------------------------------------------------
bit ScalerHdmiFrlMacRxEnterFakePowerSavingCheck(void)
{
#if(_HDMI21_FRL_CTS_FAKE_POWER_SAVING_SUPPORT == _ON)
    return _TRUE;
#else
    return _FALSE;
#endif
}
//--------------------------------------------------
// Description  : Check FRL interlace Mode
// Input Value  :
// Output Value : _TRUE is interlace mode
//--------------------------------------------------
bit ScalerHdmiFrlMacRxInterlaceModeCheck(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerHdmiFrlMacRx3InterlaceModeCheck();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerHdmiFrlMacRx4InterlaceModeCheck();
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : FRL Link Training Disable
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxLinkTrainingDisable(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerHdmiFrlMacRx3LinkTrainingDisable();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerHdmiFrlMacRx4LinkTrainingDisable();
            break;
#endif

        default:
            break;
    }
}

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Clear CVTEM PKT Receive
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxClrCvtemReceived(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            CLR_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            CLR_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();
            break;
#endif

        default:

            break;
    }
}

#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
//--------------------------------------------------
// Description  : Set SCDC Decode Fail staus
// Input Value  : EnumInputPort
// Output Value :
//--------------------------------------------------
void ScalerHdmiFrlMacRxSetDscDecodeFailStatus(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerHdmiFrlMacRx3SetDscDecodeFailStatus();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerHdmiFrlMacRx4SetDscDecodeFailStatus();
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Check CVTEM PKT Receive
// Input Value  : EnumInputPort
// Output Value :
//--------------------------------------------------
bit ScalerHdmiFrlMacRxGetCvtemReceived(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Measure CDR Clk
// Input Value  : CDR CLK to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerHdmiFrlMacRxCdrOffMeasureClk(EnumInputPort enumInputPort, BYTE ucLane)
{
    enumInputPort = enumInputPort;
    ucLane = ucLane;

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerHdmiFrlMacRx3OffMeasureClk(ucLane);
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerHdmiFrlMacRx4OffMeasureClk(ucLane);
#endif

        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Set FRL Rate
// Input Value  : enumInputPort, ucFrlRate
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxSetDxFrlRate(EnumInputPort enumInputPort, BYTE ucFrlRate)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_HDMI_FRL_D1_FRL_RATE(ucFrlRate);
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_HDMI_FRL_D2_FRL_RATE(ucFrlRate);
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_HDMI_FRL_D3_FRL_RATE(ucFrlRate);
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_HDMI_FRL_D4_FRL_RATE(ucFrlRate);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get FRL Rate
// Input Value  : enumInputPort
// Output Value : FRL Rate
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRxGetDxFrlRate(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_HDMI_FRL_D1_FRL_RATE();
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_HDMI_FRL_D2_FRL_RATE();
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_HDMI_FRL_D3_FRL_RATE();
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_HDMI_FRL_D4_FRL_RATE();
#endif

        default:
            break;
    }

    return _HDMI_FRL_RATE_NONE;
}

//--------------------------------------------------
// Description  : Clear FRL Rate
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxClrDxFrlRate(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            CLR_HDMI_FRL_D1_FRL_RATE();
            break;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            CLR_HDMI_FRL_D2_FRL_RATE();
            break;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            CLR_HDMI_FRL_D3_FRL_RATE();
            break;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            CLR_HDMI_FRL_D4_FRL_RATE();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Max FRL Rate
// Input Value  : enumInputPort
// Output Value : Max FRL Rate
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRxGetDxMaxFrlRate(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return _D1_HDMI_FRL_MAX_LINK_RATE;
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return _D2_HDMI_FRL_MAX_LINK_RATE;
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return _D3_HDMI_FRL_MAX_LINK_RATE;
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return _D4_HDMI_FRL_MAX_LINK_RATE;
#endif

        default:
            break;
    }

    return _HDMI_FRL_RATE_NONE;
}

//--------------------------------------------------
// Description  : Get FRL Rate
// Input Value  : enumInputPort
// Output Value : EnumHdmiFrlRate
//--------------------------------------------------
EnumHdmiFrlRate ScalerHdmiFrlMacRxGetFrlRate(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if(GET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE() == _HDMI_FRL_LT_LTSEND)
            {
                return ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_31_PORT_PAGE72_HDMI_SCDC_31, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if(GET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE() == _HDMI_FRL_LT_LTSEND)
            {
                return ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
            break;
#endif

        default:
            return _HDMI_FRLRATE_NONE;
    }

    return _HDMI_FRLRATE_NONE;
}

//--------------------------------------------------
// Description  : Restore IRQ Status After Z0 on
// Input Value  : Input Port
// Output Value :
//--------------------------------------------------
void ScalerHdmiFrlMacRxIrqRestoreAfterZ0On(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            // Restore Main link related IRQ After Z0 on
            ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            // Restore Main link related IRQ After Z0 on
            ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : SCDC Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRxScdcReset(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    switch(ScalerTmdsMacRxDxRxMapping(enumInputPort))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            if((ScalerGetBit(P72_25_HDMI_CTRL_25, _BIT2) == _BIT2) || (ScalerGetBit(P72_25_HDMI_CTRL_25, _BIT0) == _BIT0))
            {
                ScalerSetBit(P72_19_HDMI_CTRL_19, ~_BIT7, 0x00);
                ScalerSetBit(P72_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            }
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            if((ScalerGetBit(P73_25_HDMI_CTRL_25, _BIT2) == _BIT2) || (ScalerGetBit(P73_25_HDMI_CTRL_25, _BIT0) == _BIT0))
            {
                ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, 0x00);
                ScalerSetBit(P73_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            }
            break;
#endif

        default:
            break;
    }
}
#endif // End for #if(_HDMI_FRL_SUPPORT == _ON)

