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
// ID Code      : RL6952_Series_HdmiFrlMacRx4_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_HDMIFRLMACRX4_EXINT0__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx4/ScalerHdmiFrlMacRx4.h"


#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
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
// Description  : Check FRL Rate is neighter 0 nor over max
// Input Value  : None
// Output Value : _TRUE if satisfied
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRx4CheckFrlRate_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);

    ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31);

    if(ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == _HDMI_FRL_RATE_NONE)
    {
        return _FALSE;
    }

    // RL6952 MacRX4 always connect to PHYRX4
    if(ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) <= ScalerHdmiFrlMacRxGetDxMaxFrlRate_EXINT0(enumMappingPort))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Rx4 HDMI Audio N.F Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetAudioNfCode_EXINT0(void)
{
    ScalerSetBit_EXINT(P73_93_PORT_PAGE73_HDMI_NF_CODE_HD21_1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ())) & 0x1F));
    ScalerSetByte_EXINT(P73_94_PORT_PAGE73_HDMI_NF_CODE_HD21_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ()))));
    ScalerSetByte_EXINT(P73_95_PORT_PAGE73_HDMI_NF_CODE_HD21_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ()))));
}
#endif
#endif // End for #if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

