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
// ID Code      : ScalerTmdsPhyRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSPHY__

#include "ScalerFunctionInclude.h"
#include "TmdsPhyRx/ScalerTmdsPhyRx.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DFE Adaptation in Normal Signal
// Input Value  : None
// Output Value : True --> DFE Normal
//                False --> DFE Abnormal
//--------------------------------------------------
bit ScalerTmdsPhyRxCheckDFE(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerTmdsPhyRx3CheckDFE();
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerTmdsPhyRx4CheckDFE();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Initialize TMDS PHY
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxPhyInitial(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3PhyInitial();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4PhyInitial();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Disable Data Lane DFE
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxDisableDFE(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3DisableDFE();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4DisableDFE();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Set Rx_EN Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxSetRxEn(EnumInputPort enumInputPort, BYTE ucRxENStatus)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3SetRxEn(ucRxENStatus);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4SetRxEn(ucRxENStatus);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS CLK Measure Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxCdrMeasureClkSelect(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3CdrMeasureClkSelect(ucLane);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4CdrMeasureClkSelect(ucLane);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS CDR2XClk Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxCdr2xClkEnable(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3Cdr2xClkEnable(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4Cdr2xClkEnable(bEnable);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : FRL Mac Transition detect data lane sel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxTransitionDataLaneSelect(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3TransitionDataLaneSelect(ucLane);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4TransitionDataLaneSelect(ucLane);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : FRL Mac Transition detect data Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxTransitionDataEnable(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3TransitionDataEnable(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4TransitionDataEnable(bEnable);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS FIFO Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFifoReset(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3FifoReset(ucLane);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4FifoReset(ucLane);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Set Z0 Status
// Input Value  : ENABLE / DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxSetZ0Status(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3SetZ0Status(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4SetZ0Status(bEnable);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Save Z0 Status
// Input Value  : None
// Output Value : Z0 Status
//--------------------------------------------------
BYTE ScalerTmdsPhyRxSaveZ0Status(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerTmdsPhyRx3SaveZ0Status();
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerTmdsPhyRx4SaveZ0Status();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : TMDS Restore Z0 Status
// Input Value  : Z0 Status
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxRestoreZ0Status(EnumInputPort enumInputPort, BYTE ucZ0Status)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3RestoreZ0Status(ucZ0Status);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4RestoreZ0Status(ucZ0Status);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Dcdr
// Input Value  : enumInputPort
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerTmdsPhyRxCheckDcdr(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            if(ScalerGetBit(P7C_0F_GDI_DCDR_04, _BIT0) == _BIT0)
            {
                return _TRUE;
            }
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            if(ScalerGetBit(P7D_0F_GDI_DCDR_04, _BIT0) == _BIT0)
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
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Enable
// Input Value  : enumInputPort , bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFifoAutoResetEnable(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsPhyRx3FifoAutoResetEnable(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsPhyRx4FifoAutoResetEnable(bEnable);
            break;
#endif

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Flag Clear
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFifoAutoClearFlag(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsPhyRx3FifoAutoClearFlag();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsPhyRx4FifoAutoClearFlag();
            break;
#endif

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Done Check
// Input Value  : enumInputPort
// Output Value : BYTE unstable_flag
//--------------------------------------------------
BYTE ScalerTmdsPhyRxFifoAutoResetDone(EnumInputPort enumInputPort)
{
    // Return Value[0] = 1 -> L0 Done flag=1, [1] = L1, [2] = L2 , [3] = L3
    // Return Value = 0, flag=0
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            return ScalerTmdsPhyRx3FifoAutoResetDone();
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            return ScalerTmdsPhyRx4FifoAutoResetDone();
#endif

        default:
            break;
    }

    return 0;
}
//--------------------------------------------------
// Description  : TMDS FIFO Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxUnstableFifoReset(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsPhyRx3UnstableFifoReset();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsPhyRx4UnstableFifoReset();
            break;
#endif

        default:
            break;
    }
}

#if(_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRL Set PHY Function
// Input Value  : ucLane, ucFRLrate
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFrlSetPhy(EnumInputPort enumInputPort, BYTE ucLane, BYTE ucFRLrate)
{
    ucLane = ucLane;
    ucFRLrate = ucFRLrate;

    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if((_HDMI21_PHY_RX3_SUPPORT == _ON) && (_TMDS_PHY_RX3_SUPPORT == _ON))

        case _RX3:
#if((_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1) || (_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON))
            ScalerTmdsPhyRx3FrlSetPhy(ucLane, ucFRLrate);
#endif
            break;
#endif

#if((_HDMI21_PHY_RX4_SUPPORT == _ON) && (_TMDS_PHY_RX4_SUPPORT == _ON))

        case _RX4:
#if((_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1) || (_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON))
            ScalerTmdsPhyRx4FrlSetPhy(ucLane, ucFRLrate);
#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Trun on ACDR before transition detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFrlSetAcdr(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if((_HDMI21_PHY_RX3_SUPPORT == _ON) && (_TMDS_PHY_RX3_SUPPORT == _ON))
        case _RX3:
            ScalerTmdsPhyRx3FrlSetAcdr();
            break;
#endif

#if((_HDMI21_PHY_RX4_SUPPORT == _ON) && (_TMDS_PHY_RX4_SUPPORT == _ON))
        case _RX4:
            ScalerTmdsPhyRx4FrlSetAcdr();
            break;
#endif

        default:
            break;
    }
}

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PHY Initial before Set PHY
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFrlRebuildPhyInitial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if((_HDMI21_PHY_RX3_SUPPORT == _ON) && (_TMDS_PHY_RX3_SUPPORT == _ON))
        case _RX3:
            ScalerTmdsPhyRx3FrlRebuildPhyInitial();
            break;
#endif

#if((_HDMI21_PHY_RX4_SUPPORT == _ON) && (_TMDS_PHY_RX4_SUPPORT == _ON))
        case _RX4:
            ScalerTmdsPhyRx4FrlRebuildPhyInitial();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : PHY off before turn off power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFrlRebuildPhyOff(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if((_HDMI21_PHY_RX3_SUPPORT == _ON) && (_TMDS_PHY_RX3_SUPPORT == _ON))
        case _RX3:
            ScalerTmdsPhyRx3FrlRebuildPhyOff();
            break;
#endif

#if((_HDMI21_PHY_RX4_SUPPORT == _ON) && (_TMDS_PHY_RX4_SUPPORT == _ON))
        case _RX4:
            ScalerTmdsPhyRx4FrlRebuildPhyOff();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Phy GDI Clk Select
// Input Value  : M2PLL_CLK or XTAL
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxGdiClkSelect(EnumClkSel enumClock)
{
    if(enumClock == _M2PLL_CLK)
    {
        // GDI Clock Select to M2PLL & Set Divider
        ScalerSetBit(P80_06_GDI_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_SYS_DIV));
    }
    else if(enumClock == _EXT_XTAL_CLK)
    {
        // GDI Clock Select to Xtal
        ScalerSetBit(P80_06_GDI_CLK_DIVIDER, ~_BIT4, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Phy Select Mode
// Input Value  : HDMI2.0 or HDMI2.1
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxSelectMode(EnumInputPort enumInputPort, BYTE ucHdmiVersion)
{
    ucHdmiVersion = ucHdmiVersion;

    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if((_HDMI21_PHY_RX3_SUPPORT == _ON) && (_TMDS_PHY_RX3_SUPPORT == _ON))
        case _RX3:
            ScalerTmdsPhyRx3SelectMode(ucHdmiVersion);
            break;
#endif

#if((_HDMI21_PHY_RX4_SUPPORT == _ON) && (_TMDS_PHY_RX4_SUPPORT == _ON))
        case _RX4:
            ScalerTmdsPhyRx4SelectMode(ucHdmiVersion);
            break;
#endif

        default:
            break;
    }
}

#endif // End of #if(_HDMI_FRL_SUPPORT == _ON)

#endif
