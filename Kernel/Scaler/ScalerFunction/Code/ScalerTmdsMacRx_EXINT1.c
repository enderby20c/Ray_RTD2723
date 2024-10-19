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
// ID Code      : ScalerTmdsMacRx_EXINT1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSMAC_EXINT1__

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
// Description  : TMDS DDC Debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void ScalerTmdsMacRxDdcDetectDebounce_EXINT1(void)
{
    // Debounce 300us
    DELAY_XUS_EXINT(300);
}


//--------------------------------------------------
// Description  : TMDS Power Saving Detect DDC Handshake
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTmdsMacRxDdcDetect(void)
{
#if((_D1_HDMI_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1))

    // DDC1 Detect SCL Toggle
    if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC1) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC1) == _TRUE))
    {
        // Debounce 300us
        ScalerTmdsMacRxDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(_DDC1);

        // Delay Time us [25,x] for EDID read freq. 100K about 20us
        DELAY_25US_EXINT();

        // Double check SCL Toggle again
        if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC1) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC1) == _TRUE))
        {
            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(_DDC1, _DISABLE);

            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                SET_D1_TMDS_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2))

    // DDC2 Detect SCL Toggle
    if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC2) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC2) == _TRUE))
    {
        // Debounce 300us
        ScalerTmdsMacRxDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(_DDC2);

        // Delay Time us [25,x] for EDID read freq. 100K about 20us
        DELAY_25US_EXINT();

        // Double check SCL Toggle again
        if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC2) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC2) == _TRUE))
        {
            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(_DDC2, _DISABLE);

            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                SET_D2_TMDS_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_D3_DDC_CHANNEL_SEL == _DDC3))

    // DDC3 Detect SCL Toggle
    if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC3) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC3) == _TRUE))
    {
        // Debounce 300us
        ScalerTmdsMacRxDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(_DDC3);

        // Delay Time us [25,x] for EDID read freq. 100K about 20us
        DELAY_25US_EXINT();

        // Double check SCL Toggle again
        if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC3) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC3) == _TRUE))
        {
            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(_DDC3, _DISABLE);

            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                SET_D3_TMDS_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_D4_DDC_CHANNEL_SEL == _DDC4))

    // DDC4 Detect SCL Toggle
    if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC4) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC4) == _TRUE))
    {
        // Debounce 300us
        ScalerTmdsMacRxDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(_DDC4);

        // Delay Time us [25,x] for EDID read freq. 100K about 20us
        DELAY_25US_EXINT();

        // Double check SCL Toggle again
        if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC4) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC4) == _TRUE))
        {
            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(_DDC4, _DISABLE);

            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                SET_D4_TMDS_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_D5_DDC_CHANNEL_SEL == _DDC5))

    // DDC5 Detect SCL Toggle
    if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC5) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC5) == _TRUE))
    {
        // Debounce 300us
        ScalerTmdsMacRxDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        ScalerMcuDdcClearSclToggleIrqStatus_EXINT1(_DDC5);

        // Delay Time us [25,x] for EDID read freq. 100K about 20us
        DELAY_25US_EXINT();

        // Double check SCL Toggle again
        if((ScalerMcuDdcGetSclToggleIrqEnable_EXINT1(_DDC5) == _TRUE) && (ScalerMcuDdcGetSclToggleIrqStatus_EXINT1(_DDC5) == _TRUE))
        {
            // Disable SCL Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable_EXINT1(_DDC5, _DISABLE);

            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
            {
                SET_D5_TMDS_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerTmdsMacRxDxRxMapping_EXINT1(EnumInputPort enumInputPort)
{
    return ScalerTmdsMacRxPhyMacMapping_EXINT1(ScalerTmdsPhyRxDxRxMapping_EXINT1(enumInputPort));
}

#endif
