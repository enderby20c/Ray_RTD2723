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
// ID Code      : ScalerTmdsPhyRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSPHY_EXINT0__

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
// Description  : TMDS Set PHY Function (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxSetPhy_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3SetPhy_EXINT0();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4SetPhy_EXINT0();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Set Rx_EN Status (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxSetRxEn_EXINT0(EnumInputPort enumInputPort, BYTE ucRxENStatus)
{
    switch(ScalerTmdsPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3SetRxEn_EXINT0(ucRxENStatus);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4SetRxEn_EXINT0(ucRxENStatus);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS CLK Measure Mux
// Input Value  : Lane0~3
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxCdrMeasureClkSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3CdrMeasureClkSelect_EXINT0(ucLane);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4CdrMeasureClkSelect_EXINT0(ucLane);
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
void ScalerTmdsPhyRxCdr2xClkEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3Cdr2xClkEnable_EXINT0(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4Cdr2xClkEnable_EXINT0(bEnable);
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
void ScalerTmdsPhyRxTransitionDataLaneSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3TransitionDataLaneSelect_EXINT0(ucLane);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4TransitionDataLaneSelect_EXINT0(ucLane);
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
void ScalerTmdsPhyRxTransitionDataEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsPhyRx3TransitionDataEnable_EXINT0(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsPhyRx4TransitionDataEnable_EXINT0(bEnable);
            break;
#endif

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Enable
// Input Value  : enumInputPort , bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFifoAutoResetEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsPhyRx3FifoAutoResetEnable_EXINT0(bEnable);
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsPhyRx4FifoAutoResetEnable_EXINT0(bEnable);
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
void ScalerTmdsPhyRxFifoAutoClearFlag_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsPhyRx3FifoAutoClearFlag_EXINT0();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsPhyRx4FifoAutoClearFlag_EXINT0();
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
BYTE ScalerTmdsPhyRxFifoAutoResetDone_EXINT0(EnumInputPort enumInputPort)
{
    // Return Value[0] = 1 -> L0 Done flag=1, [1] = L1, [2] = L2 , [3] = L3
    // Return Value = 0, flag=0
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            return ScalerTmdsPhyRx3FifoAutoResetDone_EXINT0();
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            return ScalerTmdsPhyRx4FifoAutoResetDone_EXINT0();
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
void ScalerTmdsPhyRxUnstableFifoReset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsPhyRx3UnstableFifoReset_EXINT0();
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsPhyRx4UnstableFifoReset_EXINT0();
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
bit ScalerTmdsPhyRxCheckDcdr_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsPhyRxDxRxMapping(enumInputPort))
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        case _RX3:

            if(ScalerGetBit_EXINT(P7C_0F_GDI_DCDR_04, _BIT0) == _BIT0)
            {
                return _TRUE;
            }
            break;
#endif

#if(_TMDS_PHY_RX4_SUPPORT == _ON)
        case _RX4:

            if(ScalerGetBit_EXINT(P7D_0F_GDI_DCDR_04, _BIT0) == _BIT0)
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

#if(_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRL Set PHY Function (EXINT0 Only)
// Input Value  : ucLane, ucFRLrate
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRxFrlSetPhy_EXINT0(EnumInputPort enumInputPort, BYTE ucLane, BYTE ucFRLrate)
{
    ucLane = ucLane;
    ucFRLrate = ucFRLrate;

    switch(ScalerTmdsPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if((_HDMI21_PHY_RX3_SUPPORT == _ON) && (_TMDS_PHY_RX3_SUPPORT == _ON))
        case _RX3:
            ScalerTmdsPhyRx3FrlSetPhy_EXINT0(ucLane, ucFRLrate);
            break;
#endif

#if((_HDMI21_PHY_RX4_SUPPORT == _ON) && (_TMDS_PHY_RX4_SUPPORT == _ON))
        case _RX4:
            ScalerTmdsPhyRx4FrlSetPhy_EXINT0(ucLane, ucFRLrate);
            break;
#endif

        default:
            break;
    }
}
#endif

#endif
