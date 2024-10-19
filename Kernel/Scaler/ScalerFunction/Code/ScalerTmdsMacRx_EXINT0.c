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
// ID Code      : ScalerTmdsMacRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSMAC_EXINT0__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx/ScalerTmdsMacRx.h"




#if(_HDMI_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Reset PHY to MAC input (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxResetMacInput_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3ResetMacInput_EXINT0();
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4ResetMacInput_EXINT0();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : On Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTmdsMacRxOnMeasureClk_EXINT0(EnumInputPort enumInputPort, BYTE ucLane)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerTmdsMacRx3OnMeasureClk_EXINT0(ucLane);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerTmdsMacRx4OnMeasureClk_EXINT0(ucLane);
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : TMDS Save On Measure Stable times (EXINT0 Only)
// Input Value  : None
// Output Value : Stable Times
//--------------------------------------------------
BYTE ScalerTmdsMacRxSaveOnMeasureSettings_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return ScalerTmdsMacRx3SaveOnMeasureSettings_EXINT0();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return ScalerTmdsMacRx4SaveOnMeasureSettings_EXINT0();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : TMDS Restore On Measure Stable times (EXINT0 Only)
// Input Value  : Stable Times
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxRestoreOnMeasureSettings_EXINT0(EnumInputPort enumInputPort, BYTE ucStableTimes)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3RestoreOnMeasureSettings_EXINT0(ucStableTimes);
            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4RestoreOnMeasureSettings_EXINT0(ucStableTimes);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetInputPixel_EXINT0(EnumInputPort enumInputPort, WORD usPixel)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_D1_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_D2_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_D3_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_D4_INPUT_PIXEL_CLK(usPixel);
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            SET_D5_INPUT_PIXEL_CLK(usPixel);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : WORD (0.1 MHz)
//--------------------------------------------------
WORD ScalerTmdsMacRxGetInputPixel_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_D1_INPUT_PIXEL_CLK();
#endif
#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_D2_INPUT_PIXEL_CLK();
#endif
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_D3_INPUT_PIXEL_CLK();
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_D4_INPUT_PIXEL_CLK();
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return GET_D5_INPUT_PIXEL_CLK();
#endif
        default:
            return 0x00;
    }
}

//--------------------------------------------------
// Description  : TMDS Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerTmdsMacRxDxRxMapping_EXINT0(EnumInputPort enumInputPort)
{
    return ScalerTmdsMacRxPhyMacMapping_EXINT0(ScalerTmdsPhyRxDxRxMapping_EXINT0(enumInputPort));
}

//--------------------------------------------------
// Description  : TMDS Port Dx mapping to Rx
// Input Value  : Rx Port
// Output Value : Dx port
//--------------------------------------------------
EnumInputPort ScalerTmdsMacRxRxDxMapping_EXINT0(EnumRx enumRx)
{
    return ScalerTmdsPhyRxRxDxMapping_EXINT0(ScalerTmdsMacRxMacPhyMapping_EXINT0(enumRx));
}

#if(_HDMI20_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Read Request Timer Event Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTmdsMacRxGetHighSpeedMode_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            return GET_TMDS_MAC_RX3_HIGH_SPEED_MODE();
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            return GET_TMDS_MAC_RX4_HIGH_SPEED_MODE();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : TMDS Set Scdc Info
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetScdcInfo_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:
            ScalerTmdsMacRx3SetScdcInfo_EXINT0();
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:
            ScalerTmdsMacRx4SetScdcInfo_EXINT0();
            break;
#endif
        default:
            break;
    }
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Set Scdc Info
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetAmdAupiScdcInfo_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            ScalerTmdsMacRx3SetAmdAupiScdcInfo_EXINT0(bEnable);
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            ScalerTmdsMacRx4SetAmdAupiScdcInfo_EXINT0(bEnable);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI FreeSync Support
// Input Value  : enumInputPort
// Output Value : _FREESYNC_SUPPORT_ON/ _FREESYNC_SUPPORT_OFF
//--------------------------------------------------
EnumFreeSyncSupport ScalerTmdsMacRxGetFreeSyncSupport_EXINT0(EnumInputPort enumInputPort)
{
    EnumFreeSyncSupport enumFreeSyncSupport = _FREESYNC_SUPPORT_OFF;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D0();
            break;

        case _D1_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D1();
            break;

        case _D2_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D2();
            break;

        case _D3_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D3();
            break;

        case _D4_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D4();
            break;

        case _D5_INPUT_PORT:
            enumFreeSyncSupport = GET_FREESYNC_SUPPORT_TMDS_D5();
            break;

        default:
            break;
    }

    return enumFreeSyncSupport;
}
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Wait DDC's Scl Status from Busy to Idle
// Input Value  : HDMI Rx Index
// Output Value :
//--------------------------------------------------
void ScalerTmdsMacRxWaitSclStatusIntoIdle_EXINT0(EnumInputPort enumInputPort)
{
    BYTE ucCount = 0;

    ScalerMcuDdcClearSclToggleIrqStatus_EXINT0(enumInputPort);

    // set a check duration = 2ms for cover max time(=500us)of Tx read RxStatus (offset address = 0x70)
    // each loop time = 40us
    for(ucCount = 0; ucCount < 50; ucCount++)
    {
        DELAY_40US_EXINT();

        if(ScalerMcuDdcGetSclToggleIrqStatus_EXINT0(enumInputPort) == _TRUE)
        {
            ScalerMcuDdcClearSclToggleIrqStatus_EXINT0(enumInputPort);
        }
        else
        {
            break;
        }
    }
}
#endif

#if(_DM_FUNCTION == _ON)
#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get ALLM feature Enable Status (DM use)
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerTmdsMacRxGetDmAllmStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_D3_DM_ALLM_ENABLED();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_D4_DM_ALLM_ENABLED();
            break;
#endif

        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Set ALLM feature Enable Status (DM use)
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxSetDmAllmStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_D3_DM_ALLM_ENABLED();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_D4_DM_ALLM_ENABLED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clear ALLM feature Enable Status (DM use)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxClrDmAllmStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            CLR_D3_DM_ALLM_ENABLED();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            CLR_D4_DM_ALLM_ENABLED();
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DMDRAM Received
// Input Value  : enumInputPort
// Output Value : _FALSE/ _TRUE
//--------------------------------------------------
bit ScalerTmdsMacRxGetDMDramReceived_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx3GetDMDramReceived_EXINT0();
            }
            else
#endif
            {
                return ScalerTmdsMacRx3GetDMDramReceived_EXINT0();
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx4GetDMDramReceived_EXINT0();
            }
            else
#endif
            {
                return ScalerTmdsMacRx4GetDMDramReceived_EXINT0();
            }
            break;
#endif

        default:
            return _FALSE;
            break;
    }
}

//--------------------------------------------------
// Description  : DM Recheck InterFace Packet Irq Receive
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxDMPacketReCheck_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerTmdsMacRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx3DMPacketReCheck_EXINT0();
            }
            else
#endif
            {
                return ScalerTmdsMacRx3DMPacketReCheck_EXINT0();
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                return ScalerHdmiFrlMacRx4DMPacketReCheck_EXINT0();
            }
            else
#endif
            {
                return ScalerTmdsMacRx4DMPacketReCheck_EXINT0();
            }
            break;
#endif

        default:
            break;
    }
}
#endif
#endif
