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
// ID Code      : ScalerTmdsHdcp2Rx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TmdsHdcp2Rx3/ScalerTmdsHdcp2Rx3.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

volatile StructHdcp2HDCPAuthInfo g_stTmdsHdcp2Rx3AuthInfo;
volatile BYTE g_ucTmdsHdcp2Rx3Ctrl;

BYTE g_pucTmdsHdcp2Rx3dKey0[16];
BYTE g_pucTmdsHdcp2Rx3dKey1[16];

BYTE g_pucTmdsHdcp2Rx3Km[16];

BYTE g_pucTmdsHdcp2Rx3Rtx[8];
BYTE g_pucTmdsHdcp2Rx3TxCaps[3];
BYTE g_pucTmdsHdcp2Rx3Rn[8];
BYTE g_pucTmdsHdcp2Rx3Rrx[8];

#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for TMDS Rx3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3Handler(void)
{
    // Receiver Has Received AKE_INIT
    if(GET_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED();

        DebugMessageHDCP2("[RX3]AKE_INIT", 0);
    }

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED();
        CLR_TMDS_HDCP2_RX3_AUTHENTICATION_ACTIVE();

        DebugMessageHDCP2("[RX3]AKE_NO_STORED_KM", 0);
    }

    if(GET_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED();

        DebugMessageHDCP2("[RX3]AKE_STORED_KM", 0);
    }

    if(GET_TMDS_HDCP2_RX3_LC_INIT_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX3_LC_INIT_RECEIVED();

        DebugMessageHDCP2("[RX3]LC_INIT", 0);
    }

    if(GET_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
        CLR_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED();

        DebugMessageHDCP2("[RX3]SKE_SEND_EKS", 0);
    }

    if(GET_TMDS_HDCP2_RX3_AUTHENTICATION_DONE() == _TRUE)
    {
        // Check BCH Error or Not
        if(ScalerTmdsHdcp2Rx3LinkIntegrityCheckFail() == _TRUE)
        {
            // Clear Authentication Done Flag
            CLR_TMDS_HDCP2_RX3_AUTHENTICATION_DONE();

            DebugMessageHDCP2("[RX3]REAUTH_REQ", 0);

            // Set HDCP 2.2 Authentication State = UnAuthenticated
            SET_TMDS_HDCP2_RX3_AUTH_STATE(_HDCP_2_2_STATE_UNAUTHENTICATED);

            // Set RxStatus REAUTH_REQ
            ScalerSetBit(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_71_PORT_PAGE72_HDCP2_STATUS2, ~_BIT3, _BIT3);
            ScalerSetBit(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

            // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
            ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH);
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : TRUE: Bch error happened!!
//--------------------------------------------------
bit ScalerTmdsHdcp2Rx3LinkIntegrityCheckFail(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
    {
        if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_63_PORT_PAGE77_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear BCH Error Flag
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_63_PORT_PAGE77_HDMI_PEAC1, ~_BIT6, _BIT6);
            return _TRUE;
        }
    }
    else
#endif
    {
        if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear BCH Error Flag
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1, ~_BIT6, _BIT6);
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
void ScalerTmdsHdcp2Rx3Initial(void)
{
    // Enable HDCP 2 Write SRAM Auto Increase Function
    ScalerSetBit(P2E_20_HDCP_MSG_CTRL, ~_BIT0, _BIT0);

    // Enable HDCP 2 Read SRAM Auto Increase Function
    ScalerSetBit(P2E_23_HDCP_MSGRAP_H, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Get HDCP Encryption/ Discryption Data Status
// Input Value  : None
// Output Value : _TRUE (Encryption data)
//--------------------------------------------------
bit ScalerTmdsHdcp2Rx3GetHdcpContentEncStatus(void)
{
    return (ScalerGetBit(P2E_40_HDCP_2PX_ENCRYP_STS, _BIT7) >> 7);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Re-Auth Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3ReAuthEvent(void)
{
    if(ScalerTmdsHdcp2Rx3LinkIntegrityCheckFail() == _TRUE)
    {
        SET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_HDCP22);

        DebugMessageHDCP2("[RX3]BCH ERR FOR HPD EVENT", 0);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3ResetProc(void)
{
    // Disable Read Msg Done IRQ
    ScalerSetBit(P2E_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

    // Clear Reading Msg Size & Clear REAUTH_REQ
    ScalerSetBit(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_70_PORT_PAGE72_HDCP2_STATUS1, 0x00);
    ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_71_PORT_PAGE72_HDCP2_STATUS2, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Disable Link Interity Check
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1, ~(_BIT7 | _BIT6), 0x00);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_63_PORT_PAGE77_HDMI_PEAC1, ~(_BIT7 | _BIT6), 0x00);
#endif

    // Reset Authenticated FSM
    ScalerSetByte(P2E_28_HDCP_I2C_CTRL_2, 0x01);
    ScalerSetBit(P2E_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH);

    // Cancel HDCP 2.2 RSA Cal Timer Event
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_RSA_CAL_START);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH);

    CLR_TMDS_HDCP2_RX3_AUTHENTICATION_DONE();
    CLR_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED();
    CLR_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED();
    CLR_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED();
    CLR_TMDS_HDCP2_RX3_LC_INIT_RECEIVED();
    CLR_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED();
    CLR_TMDS_HDCP2_RX3_AUTHENTICATION_ACTIVE();

    // HDCP disable cause AVMute issue enable 1.4 disable 2.2
    ScalerSetBit(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P72_C0_HDCP_CR, ~_BIT0, _BIT0);

    // clear AKSV/ Bksv/ Ri flag
    ScalerSetBit(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
}
#endif

#endif
