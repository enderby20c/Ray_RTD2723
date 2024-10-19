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
// ID Code      : ScalerDpHdcpRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcpRx/ScalerDpHdcpRx.h"

#if(_DP_HDCP_RX_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_HDCP_RX0_SUPPORT == _ON)
volatile EnumHDCPType g_enumDpHdcpRx0HdcpMode;
volatile bit g_bDpHdcpRx0HdcpCpirqFlag = _FALSE;
BYTE g_pucDpHdcpRx0ECFBackup[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif
#if(_DP_HDCP_RX1_SUPPORT == _ON)
volatile EnumHDCPType g_enumDpHdcpRx1HdcpMode;
volatile bit g_bDpHdcpRx1HdcpCpirqFlag = _FALSE;
BYTE g_pucDpHdcpRx1ECFBackup[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif
#if(_DP_HDCP_RX2_SUPPORT == _ON)
volatile EnumHDCPType g_enumDpHdcpRx2HdcpMode;
volatile bit g_bDpHdcpRx2HdcpCpirqFlag = _FALSE;
BYTE g_pucDpHdcpRx2ECFBackup[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Port Rx mapping to Dx
// Input Value  : Rx
// Output Value : Dx
//--------------------------------------------------
EnumInputPort ScalerDpHdcpRxRxDxMapping(EnumRx enumRx)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumRx)
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            if(_HW_D0_DP_HDCP_RX_MAPPING == _RX0)
            {
                enumInputPort = _D0_INPUT_PORT;
            }

            break;
#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            if(_HW_D1_DP_HDCP_RX_MAPPING == _RX1)
            {
                enumInputPort = _D1_INPUT_PORT;
            }

            break;
#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            if(_HW_D2_DP_HDCP_RX_MAPPING == _RX2)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

        default:

            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx0 or Rx1 or Rx2
//--------------------------------------------------
EnumRx ScalerDpHdcpRxDxRxMapping(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            enumRx = _HW_D0_DP_HDCP_RX_MAPPING;

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            enumRx = _HW_D1_DP_HDCP_RX_MAPPING;

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            enumRx = _HW_D2_DP_HDCP_RX_MAPPING;

            break;
#endif

        default:

            break;
    }

    return enumRx;
}

//--------------------------------------------------
// Description  : Dp Rx HDCP Get Valid Mode
// Input Value  : EnumInputPort
// Output Value : EnumHDCPType
//--------------------------------------------------
EnumHDCPType ScalerDpHdcpRxGetValidMode(EnumInputPort enumInputPort)
{
    if(ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE)
    {
#if(_DUAL_DP_SUPPORT == _ON)
        if(enumInputPort == _DUAL_DP_INPUT_PORT)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22
            if((ScalerDpHdcpRxGetHdcpMode(_DUAL_DP_MAIN_PORT) == _HDCP_22) &&
               (ScalerDpHdcpRxGetHdcpMode(_DUAL_DP_SUB_PORT) == _HDCP_22))
            {
#if(_DP_TX_SUPPORT == _ON)
                if((ScalerDpHdcp2GetRepeaterSupport(_DUAL_DP_MAIN_PORT) == _TRUE) &&
                   (ScalerDpHdcp2GetRepeaterSupport(_DUAL_DP_SUB_PORT) == _TRUE))
                {
                    return _HDCP_22_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_22;
                }
            }
            else
#endif
            {
#if(_DP_TX_SUPPORT == _ON)
                if((ScalerDpAuxRxGetHdcpRepeaterSupport(_DUAL_DP_MAIN_PORT) == _TRUE) &&
                   (ScalerDpAuxRxGetHdcpRepeaterSupport(_DUAL_DP_SUB_PORT) == _TRUE))
                {
                    return _HDCP_14_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
        }
        else
#endif
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22
            if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
            {
#if(_DP_TX_SUPPORT == _ON)
                if(ScalerDpHdcp2GetRepeaterSupport(enumInputPort) == _TRUE)
                {
                    return _HDCP_22_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_22;
                }
            }
            else
#endif
            {
#if(_DP_TX_SUPPORT == _ON)
                if(ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _TRUE)
                {
                    return _HDCP_14_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
        }
    }

    return _HDCP_NONE;
}

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx HDCP Get Enabled Mode
// Input Value  : EnumInputPort
// Output Value : EnumHDCPType
//--------------------------------------------------
EnumHDCPType ScalerDpHdcpRxGetEnabledMode(EnumInputPort enumInputPort)
{
    if(ScalerDpHdcpRxGetHandshakeDone(enumInputPort) == _TRUE)
    {
#if(_DUAL_DP_SUPPORT == _ON)
        if(enumInputPort == _DUAL_DP_INPUT_PORT)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22
            if((ScalerDpHdcpRxGetHdcpMode(_DUAL_DP_MAIN_PORT) == _HDCP_22) &&
               (ScalerDpHdcpRxGetHdcpMode(_DUAL_DP_SUB_PORT) == _HDCP_22))
            {
#if(_DP_TX_SUPPORT == _ON)
                if((ScalerDpHdcp2GetRepeaterSupport(_DUAL_DP_MAIN_PORT) == _TRUE) &&
                   (ScalerDpHdcp2GetRepeaterSupport(_DUAL_DP_SUB_PORT) == _TRUE))
                {
                    return _HDCP_22_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_22;
                }
            }
            else
#endif
            {
#if(_DP_TX_SUPPORT == _ON)
                if((ScalerDpAuxRxGetHdcpRepeaterSupport(_DUAL_DP_MAIN_PORT) == _TRUE) &&
                   (ScalerDpAuxRxGetHdcpRepeaterSupport(_DUAL_DP_SUB_PORT) == _TRUE))
                {
                    return _HDCP_14_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
        }
        else
#endif
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22
            if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
            {
#if(_DP_TX_SUPPORT == _ON)
                if(ScalerDpHdcp2GetRepeaterSupport(enumInputPort) == _TRUE)
                {
                    return _HDCP_22_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_22;
                }
            }
            else
#endif
            {
#if(_DP_TX_SUPPORT == _ON)
                if(ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _TRUE)
                {
                    return _HDCP_14_REPEATER;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
        }
    }

    return _HDCP_NONE;
}
#endif

//--------------------------------------------------
// Description  : Set Hdcp Mode Backup
// Input Value  : enumInputPort, EnumHDCPType
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcpRxSetHdcpMode(EnumInputPort enumInputPort, EnumHDCPType enumHDCPType)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            SET_DP_HDCP_RX0_HDCP_MODE(enumHDCPType);

            break;
#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            SET_DP_HDCP_RX1_HDCP_MODE(enumHDCPType);

            break;
#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            SET_DP_HDCP_RX2_HDCP_MODE(enumHDCPType);

            break;
#endif

        default:

            break;
    }

    ScalerDpMacDphyRxSetHdcpMode(enumInputPort, enumHDCPType);
}

//--------------------------------------------------
// Description  : Get Hdcp Mode Backup
// Input Value  : enumInputPort
// Output Value : EnumHDCPType
//--------------------------------------------------
EnumHDCPType ScalerDpHdcpRxGetHdcpMode(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            return GET_DP_HDCP_RX0_HDCP_MODE();
#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            return GET_DP_HDCP_RX1_HDCP_MODE();
#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            return GET_DP_HDCP_RX2_HDCP_MODE();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get HDCP CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcpRxGetHdcpCpirqFlag(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            return GET_DP_HDCP_RX0_HDCP_CPIRQ();

#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            return GET_DP_HDCP_RX1_HDCP_CPIRQ();

#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            return GET_DP_HDCP_RX2_HDCP_CPIRQ();

#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set HDCP CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcpRxSetHdcpCpirqFlag(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            SET_DP_HDCP_RX0_HDCP_CPIRQ();

            break;

#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            SET_DP_HDCP_RX1_HDCP_CPIRQ();

            break;

#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            SET_DP_HDCP_RX2_HDCP_CPIRQ();

            break;

#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear HDCP CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcpRxClrHdcpCpirqFlag(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP_RX0_SUPPORT == _ON)

        case _RX0:

            CLR_DP_HDCP_RX0_HDCP_CPIRQ();

            break;

#endif

#if(_DP_HDCP_RX1_SUPPORT == _ON)

        case _RX1:

            CLR_DP_HDCP_RX1_HDCP_CPIRQ();

            break;

#endif

#if(_DP_HDCP_RX2_SUPPORT == _ON)

        case _RX2:

            CLR_DP_HDCP_RX2_HDCP_CPIRQ();

            break;

#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Initial Setting for HDCP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcpRxInitial(EnumInputPort enumInputPort)
{
    ScalerDpMacDphyRxLinkIntegrityEnable();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_22);
    }
    else
#endif
    {
        ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_14);
    }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear HDCP2 Backup Info
    ScalerDpMacDphyRxClrHdcp2CipherBackupInfo(enumInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpHdcp14RxClrAuthAksvWritten(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Get Hdcp2 Authentication Done
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpHdcpRxGetAuthDone(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            if(GET_DP_HDCP2_RX0_AUTHENTICATION_DONE() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            if(GET_DP_HDCP2_RX1_AUTHENTICATION_DONE() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            if(GET_DP_HDCP2_RX2_AUTHENTICATION_DONE() == _TRUE)
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

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Record Source Start Hdcp2 HandShake
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpHdcpRxHandshakeStartCheck(void)
{
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
    if(GET_DP_HDCP2_RX0_HANDSHAKE_START() == _TRUE)
    {
        CLR_DP_HDCP2_RX0_HANDSHAKE_START();

        if(GET_DP_HDCP2_RX0_AUTHENTICATION_DONE() == _FALSE)
        {
            return _TRUE;
        }
    }
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
    if(GET_DP_HDCP2_RX1_HANDSHAKE_START() == _TRUE)
    {
        CLR_DP_HDCP2_RX1_HANDSHAKE_START();

        if(GET_DP_HDCP2_RX1_AUTHENTICATION_DONE() == _FALSE)
        {
            return _TRUE;
        }
    }
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
    if(GET_DP_HDCP2_RX2_HANDSHAKE_START() == _TRUE)
    {
        CLR_DP_HDCP2_RX2_HANDSHAKE_START();

        if(GET_DP_HDCP2_RX2_AUTHENTICATION_DONE() == _FALSE)
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Record Source Start Hdcp2 HandShake
// Input Value  : EnumInputPort
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpHdcpRxHandshakeStartInputPortCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            if(GET_DP_HDCP2_RX0_HANDSHAKE_START() == _TRUE)
            {
                CLR_DP_HDCP2_RX0_HANDSHAKE_START();

                if(GET_DP_HDCP2_RX0_AUTHENTICATION_DONE() == _FALSE)
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            if(GET_DP_HDCP2_RX1_HANDSHAKE_START() == _TRUE)
            {
                CLR_DP_HDCP2_RX1_HANDSHAKE_START();

                if(GET_DP_HDCP2_RX1_AUTHENTICATION_DONE() == _FALSE)
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            if(GET_DP_HDCP2_RX2_HANDSHAKE_START() == _TRUE)
            {
                CLR_DP_HDCP2_RX2_HANDSHAKE_START();

                if(GET_DP_HDCP2_RX2_AUTHENTICATION_DONE() == _FALSE)
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
// Description  : Check Not Fix Port Occur Hdcp Handshake
// Input Value  : EnumInputPort
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpHdcpRxHandshakeStartActiveTimerCheck(EnumInputPort enumFixSearchPort)
{
    // No Hdcp Handshake Port ==> return _FALSE
    // Any One Current Hdcp Handshake Port == Fix Search Port  ==> return _FALSE
    // Hdcp Handshake Port != Fix Search Port ==> return _TURE

    bit bFlag = _FALSE;

    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        if(ScalerSyncGetPortType(enumInputPort) == _PORT_DP)
        {
            if(ScalerDpHdcpRxHandshakeStartInputPortCheck(enumInputPort) == _TRUE)
            {
                if(enumInputPort == enumFixSearchPort)
                {
                    return _FALSE;
                }
                else
                {
                    bFlag = _TRUE;
                }
            }
        }
    }

    return bFlag;
}

//--------------------------------------------------
// Description  : Hand Shake Start No Change Check
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpHdcpRxGetHandshakeDone(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            if(GET_DP_HDCP_RX0_HDCP_MODE() == _HDCP_22)
            {
                if(GET_DP_HDCP2_RX0_AUTHENTICATION_DONE() == _TRUE)
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            if(GET_DP_HDCP_RX1_HDCP_MODE() == _HDCP_22)
            {
                if(GET_DP_HDCP2_RX1_AUTHENTICATION_DONE() == _TRUE)
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            if(GET_DP_HDCP_RX2_HDCP_MODE() == _HDCP_22)
            {
                if(GET_DP_HDCP2_RX2_AUTHENTICATION_DONE() == _TRUE)
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
#endif
#endif
