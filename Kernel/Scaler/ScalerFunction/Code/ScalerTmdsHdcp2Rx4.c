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
// ID Code      : ScalerTmdsHdcp2Rx4.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TmdsHdcp2Rx4/ScalerTmdsHdcp2Rx4.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX4_SUPPORT == _ON)

volatile StructHdcp2HDCPAuthInfo g_stTmdsHdcp2Rx4AuthInfo;
volatile BYTE g_ucTmdsHdcp2Rx4Ctrl;

BYTE g_pucTmdsHdcp2Rx4dKey0[16];
BYTE g_pucTmdsHdcp2Rx4dKey1[16];

BYTE g_pucTmdsHdcp2Rx4Km[16];

BYTE g_pucTmdsHdcp2Rx4Rtx[8];
BYTE g_pucTmdsHdcp2Rx4TxCaps[3];
BYTE g_pucTmdsHdcp2Rx4Rn[8];
BYTE g_pucTmdsHdcp2Rx4Rrx[8];

#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for TMDS Rx4
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx4Handler(void)
{
    // Receiver Has Received AKE_INIT
    if(GET_TMDS_HDCP2_RX4_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX4_AKE_INIT_RECEIVED();

        DebugMessageHDCP2("[RX4]AKE_INIT", 0);
    }

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_TMDS_HDCP2_RX4_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX4_AKE_NO_STORED_KM_RECEIVED();
        CLR_TMDS_HDCP2_RX4_AUTHENTICATION_ACTIVE();

        DebugMessageHDCP2("[RX4]AKE_NO_STORED_KM", 0);
    }

    if(GET_TMDS_HDCP2_RX4_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX4_AKE_STORED_KM_RECEIVED();

        DebugMessageHDCP2("[RX4]AKE_STORED_KM", 0);
    }

    if(GET_TMDS_HDCP2_RX4_LC_INIT_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX4_LC_INIT_RECEIVED();

        DebugMessageHDCP2("[RX4]LC_INIT", 0);
    }

    if(GET_TMDS_HDCP2_RX4_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX4_SKE_SEND_EKS_RECEIVED();

        DebugMessageHDCP2("[RX4]SKE_SEND_EKS", 0);
    }

    if(GET_TMDS_HDCP2_RX4_AUTHENTICATION_DONE() == _TRUE)
    {
        // Check BCH Error or Not
        if(ScalerTmdsHdcp2Rx4LinkIntegrityCheckFail() == _TRUE)
        {
            // Clear Authentication Done Flag
            CLR_TMDS_HDCP2_RX4_AUTHENTICATION_DONE();

            DebugMessageHDCP2("[RX4]REAUTH_REQ", 0);

            // Set HDCP 2.2 Authentication State = UnAuthenticated
            SET_TMDS_HDCP2_RX4_AUTH_STATE(_HDCP_2_2_STATE_UNAUTHENTICATED);

            // Set RxStatus REAUTH_REQ
            ScalerSetBit(P6D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_71_PORT_PAGE73_HDCP2_STATUS2, ~_BIT3, _BIT3);
            ScalerSetBit(P6D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

            // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
            ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH);
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : TRUE: Bch error happened!!
//--------------------------------------------------
bit ScalerTmdsHdcp2Rx4LinkIntegrityCheckFail(void)
{
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
    {
        if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_63_PORT_PAGE78_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear BCH Error Flag
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_63_PORT_PAGE78_HDMI_PEAC1, ~_BIT6, _BIT6);
            return _TRUE;
        }
    }
    else
#endif
    {
        if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_63_PORT_PAGE73_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear BCH Error Flag
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_63_PORT_PAGE73_HDMI_PEAC1, ~_BIT6, _BIT6);
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx4Initial(void)
{
    // Enable HDCP 2 Write SRAM Auto Increase Function
    ScalerSetBit(P6D_20_HDCP_MSG_CTRL, ~_BIT0, _BIT0);

    // Enable HDCP 2 Read SRAM Auto Increase Function
    ScalerSetBit(P6D_23_HDCP_MSGRAP_H, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Get HDCP Encryption/ Discryption Data Status
// Input Value  : None
// Output Value : _TRUE (Encryption data)
//--------------------------------------------------
bit ScalerTmdsHdcp2Rx4GetHdcpContentEncStatus(void)
{
    return (ScalerGetBit(P6D_40_HDCP_2PX_ENCRYP_STS, _BIT7) >> 7);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Re-Auth Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx4ReAuthEvent(void)
{
    if(ScalerTmdsHdcp2Rx4LinkIntegrityCheckFail() == _TRUE)
    {
        SET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_HDCP22);

        DebugMessageHDCP2("[RX4]BCH ERR FOR HPD EVENT", 0);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx4ResetProc(void)
{
    // Disable Read Msg Done IRQ
    ScalerSetBit(P6D_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

    // Clear Reading Msg Size & Clear REAUTH_REQ
    ScalerSetBit(P6D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_70_PORT_PAGE73_HDCP2_STATUS1, 0x00);
    ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_71_PORT_PAGE73_HDCP2_STATUS2, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P6D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Disable Link Interity Check
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_63_PORT_PAGE73_HDMI_PEAC1, ~(_BIT7 | _BIT6), 0x00);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_63_PORT_PAGE78_HDMI_PEAC1, ~(_BIT7 | _BIT6), 0x00);
#endif

    // Reset Authenticated FSM
    ScalerSetByte(P6D_28_HDCP_I2C_CTRL_2, 0x01);
    ScalerSetBit(P6D_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH);

    // Cancel HDCP 2.2 RSA Cal Timer Event
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_RSA_CAL_START);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX4_HDCP2_SET_REAUTH);

    CLR_TMDS_HDCP2_RX4_AUTHENTICATION_DONE();
    CLR_TMDS_HDCP2_RX4_AKE_INIT_RECEIVED();
    CLR_TMDS_HDCP2_RX4_AKE_NO_STORED_KM_RECEIVED();
    CLR_TMDS_HDCP2_RX4_AKE_STORED_KM_RECEIVED();
    CLR_TMDS_HDCP2_RX4_LC_INIT_RECEIVED();
    CLR_TMDS_HDCP2_RX4_SKE_SEND_EKS_RECEIVED();
    CLR_TMDS_HDCP2_RX4_AUTHENTICATION_ACTIVE();

    // HDCP disable cause AVMute issue enable 1.4 disable 2.2
    ScalerSetBit(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P73_C0_HDCP_CR, ~_BIT0, _BIT0);

    // clear AKSV/ Bksv/ Ri flag
    ScalerSetBit(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
}
#endif

#endif
