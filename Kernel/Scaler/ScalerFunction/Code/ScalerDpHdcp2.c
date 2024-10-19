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
// ID Code      : ScalerDpHdcp2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp2/ScalerDpHdcp2.h"

#if(_DP_HDCP_2_2_SUPPORT == _ON)


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
// Description  : HDCP 2.2 Unplug Reset Proc
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxUnplugResetProc(EnumInputPort enumInputPort)
{
    ScalerDpHdcp2RxResetProc(enumInputPort);

    ScalerDpHdcp2RxResetDpcd(enumInputPort, _DP_RX_HDCP_UNPLUG_RESET);

    ScalerDpHdcp2ClrAuthenticationDone(enumInputPort);

    // Clear HDCP2 Backup Info
    ScalerDpMacDphyRxClrHdcp2CipherBackupInfo(enumInputPort);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxResetProc(EnumInputPort enumInputPort)
{
#if(_DP_HDCP_RX_SUPPORT == _ON)
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpHdcp2Rx0ResetProc();

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpHdcp2Rx1ResetProc();

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpHdcp2Rx2ResetProc();

            break;
#endif
        default:

            break;
    }
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Source Write Dpcd
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxResetDpcd(EnumInputPort enumInputPort, EnumDPRxHDCPResetDpcdField enumDPRxHDCPResetDpcdField)
{
    BYTE ucTemp = 0;

    switch(enumDPRxHDCPResetDpcdField)
    {
        case _DP_RX_HDCP_REAUTH:

            ScalerDpAuxRxSetManualMode(enumInputPort);

            for(ucTemp = 0; ucTemp < 8; ucTemp ++)
            {
                // Clear HDCP 2.2 Riv
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0x28 + ucTemp, 0x00);
            }

            ScalerDpAuxRxSetAutoMode(enumInputPort);

            break;

        case _DP_RX_HDCP_UNPLUG_RESET:

            ScalerDpAuxRxHdcp2HandshakeIRQ(enumInputPort, _DISABLE);

            for(ucTemp = 0; ucTemp < 8; ucTemp ++)
            {
                // Clear HDCP 2.2 Rtx
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x90, 0x00 + ucTemp, 0x00);

                // Clear HDCP 2.2 rn
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x92, 0xF0 + ucTemp, 0x00);

                // Clear HDCP 2.2 Riv
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0x28 + ucTemp, 0x00);
            }

            // Clear HDCP 2.2 TxCaps
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x90, 0x08, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x90, 0x09, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x90, 0x0A, 0x00);

            // Clear HDCP 2.2 Ekpub_km
            for(ucTemp = 0; ucTemp < 128; ucTemp ++)
            {
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x92, 0x20 + ucTemp, 0x00);
            }

            for(ucTemp = 0; ucTemp < 16; ucTemp ++)
            {
                // Clear HDCP 2.2 Ekh_km
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x92, 0xA0 + ucTemp, 0x00);

                // Clear HDCP 2.2 m
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x92, 0xB0 + ucTemp, 0x00);

                // Clear HDCP 2.2 Edkey_ks
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0x18 + ucTemp, 0x00);
            }

#if(_DP_TX_SUPPORT == _ON)
            // Clear HDCP 2.2 V
            for(ucTemp = 0; ucTemp < 16; ucTemp ++)
            {
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xE0 + ucTemp, 0x00);
            }

            // Clear HDCP 2.2 seq_num_M
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xF0, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xF1, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xF2, 0x00);

            // Clear HDCP 2.2 k
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xF3, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xF4, 0x00);

            // Clear HDCP 2.2 Ekpub_km
            for(ucTemp = 0; ucTemp < 126; ucTemp ++)
            {
                ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x93, 0xF5 + ucTemp, 0x00);
            }
#endif

            ScalerDpAuxRxHdcp2HandshakeIRQ(enumInputPort, _ENABLE);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Get Authentication Done
// Input Value  : Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2GetAuthenticationDone(EnumInputPort enumInputPort)
{
#if(_DP_HDCP_RX_SUPPORT == _ON)
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:
            if(GET_DP_HDCP2_RX0_AUTHENTICATION_DONE() != 0)
            {
                return _TRUE;
            }
            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:
            if(GET_DP_HDCP2_RX1_AUTHENTICATION_DONE() != 0)
            {
                return _TRUE;
            }
            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:
            if(GET_DP_HDCP2_RX2_AUTHENTICATION_DONE() != 0)
            {
                return _TRUE;
            }
            break;
#endif

        default:
            break;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Clr Authentication Done
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2ClrAuthenticationDone(EnumInputPort enumInputPort)
{
#if(_DP_HDCP_RX_SUPPORT == _ON)
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_HDCP2_RX0_AUTHENTICATION_DONE();

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_HDCP2_RX1_AUTHENTICATION_DONE();

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_HDCP2_RX2_AUTHENTICATION_DONE();

            break;
#endif
        default:

            break;
    }
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Get V Prime
// Input Value  : ucIndex, Input Port
// Output Value : V Prime Value
//--------------------------------------------------
BYTE ScalerDpHdcp2GetVPrime(EnumInputPort enumInputPort, BYTE ucIndex)
{
#if(_DP_HDCP_RX_SUPPORT == _ON)
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_HDCP2_RX0_V_PRIME(ucIndex);
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_HDCP2_RX1_V_PRIME(ucIndex);
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_HDCP2_RX2_V_PRIME(ucIndex);
#endif
        default:

            break;
    }
#endif

    return 0x00;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Set Upstream Event
// Input Value  : EnumDpHdcp2RxUpstreamAuthStatus, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2SetUpstreamEvent(EnumInputPort enumInputPort, EnumDpHdcp2RxUpstreamAuthStatus enumAuthStatus)
{
#if(_DP_HDCP_RX_SUPPORT == _ON)
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_HDCP2_RX0_UPSTREAM_EVENT(enumAuthStatus);

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_HDCP2_RX1_UPSTREAM_EVENT(enumAuthStatus);

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_HDCP2_RX2_UPSTREAM_EVENT(enumAuthStatus);

            break;
#endif
        default:

            break;
    }
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Get Repeater Capable
// Input Value  : Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2GetRepeaterSupport(EnumInputPort enumInputPort)
{
#if(_DP_HDCP_RX_SUPPORT == _ON)
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_HDCP2_RX0_REPEATER_SUPPORT();
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_HDCP2_RX1_REPEATER_SUPPORT();
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_HDCP2_RX2_REPEATER_SUPPORT();
#endif

        default:

            break;
    }
#endif

    return _FALSE;
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Repeater Lprime Calculate
// Input Value  : pucInputArray, Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2RepeaterLPrimeCalculate(EnumInputPort enumInputPort, BYTE *pucInputArray)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2Rx0dKey0);
            ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2Rx0dKey1);

            return ScalerHdcp2RepeaterLPrimeCalculate(pucTemp1, pucTemp2, pucInputArray);
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2Rx1dKey0);
            ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2Rx1dKey1);

            return ScalerHdcp2RepeaterLPrimeCalculate(pucTemp1, pucTemp2, pucInputArray);
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2Rx2dKey0);
            ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2Rx2dKey1);

            return ScalerHdcp2RepeaterLPrimeCalculate(pucTemp1, pucTemp2, pucInputArray);
#endif
        default:

            break;
    }

    return _FALSE;
}
#endif
#endif

#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
