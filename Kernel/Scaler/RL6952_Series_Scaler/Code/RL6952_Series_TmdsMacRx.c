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
// ID Code      : RL6952_Series_TmdsMacRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TMDSMAC__

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
// Description  : TMDS Port MAC Selection
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxMacSelection(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
}

//--------------------------------------------------
// Description  : SET All Rx ddc mux
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxDDCSwitchCtrl(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)
    ScalerSetBit(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT2 | _BIT1), 0x00);
#endif

#if(_HW_D3_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)
    ScalerSetBit(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT2 | _BIT1), _BIT1);
#endif

#if(_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX3)
    ScalerSetBit(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT2 | _BIT1), 0x00);
#endif

#if(_HW_D4_TMDS_MAC_RX_MAPPING == _MAPPING_RX4)
    ScalerSetBit(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT2 | _BIT1), _BIT1);
#endif
}

//--------------------------------------------------
// Description  : TMDS Mac mapping to Phy
// Input Value  : Mac Rx
// Output Value : Phy Rx
//--------------------------------------------------
EnumRx ScalerTmdsMacRxMacPhyMapping(EnumRx enumMacRxIndex)
{
    EnumRx enumPhyRxIndex = _RX_MAP_NONE;

    switch(enumMacRxIndex)
    {
        case _RX3:

            enumPhyRxIndex = _RX3;
            break;

        case _RX4:

            enumPhyRxIndex = _RX4;
            break;

        default:

            break;
    }

    return enumPhyRxIndex;
}

//--------------------------------------------------
// Description  : TMDS Phy mapping to Mac
// Input Value  : Phy Rx
// Output Value : Mac Rx
//--------------------------------------------------
EnumRx ScalerTmdsMacRxPhyMacMapping(EnumRx enumPhyRxIndex)
{
    EnumRx enumMacRxIndex = _RX_MAP_NONE;

    switch(enumPhyRxIndex)
    {
        case _RX3:

            enumMacRxIndex = _RX3;
            break;

        case _RX4:

            enumMacRxIndex = _RX4;
            break;

        default:

            break;
    }

    return enumMacRxIndex;
}

#if(_HDMI20_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Version Scdc Info Hw Version
// Input Value  : None
// Output Value : HW Version
//--------------------------------------------------
BYTE ScalerTmdsMacRxGetHwVersion(void)
{
    BYTE ucHwVersionMajor = 0x00;
    BYTE ucHwVersionMinor = 0x00;
    BYTE ucHwVersion = 0x00;

    if(_HW_HDMI_FRL_SUPPORT_PORT != _HDMI_FRL_MAC_NONE)
    {
        if(_HW_HDMI21_MAX_LINK_RATE_SUPPORT == _HDMI_FRL_RATE_12G)
        {
            ucHwVersionMajor = 0x05;
        }
        else if(_HW_HDMI21_MAX_LINK_RATE_SUPPORT == _HDMI_FRL_RATE_10G)
        {
            ucHwVersionMajor = 0x04;
        }
        else if(_HW_HDMI21_MAX_LINK_RATE_SUPPORT == _HDMI_FRL_RATE_8G)
        {
            ucHwVersionMajor = 0x03;
        }
        else if(_HW_HDMI21_MAX_LINK_RATE_SUPPORT == _HDMI_FRL_RATE_6G_4LANES)
        {
            ucHwVersionMajor = 0x02;
        }
    }
    else if(_HW_HDMI20_SUPPORT_PORT != _HDMI20_NONE)
    {
        ucHwVersionMajor = 0x01;
    }
    else
    {
        ucHwVersionMajor = 0x00;
    }

    ucHwVersion = (((ucHwVersionMajor & 0x0F) << 4) | (ucHwVersionMinor & 0x0F));

    return ucHwVersion;
}
#endif

//--------------------------------------------------
// Description  : dx mapping to Mac select by hdmi mac ddc select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxPhyDdcMappingAlignInAcOnProc(void)
{
}

//--------------------------------------------------
// Description  : SET All Rx ddc mux
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxDDCSwitchWhenAcOnProc(void)
{
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    ScalerSetBit(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT2 | _BIT1), 0x00);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    ScalerSetBit(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT2 | _BIT1), _BIT1);
#endif
}
#endif

