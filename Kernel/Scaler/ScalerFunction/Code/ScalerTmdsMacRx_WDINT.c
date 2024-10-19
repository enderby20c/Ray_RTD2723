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
// ID Code      : ScalerTmdsMacRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSMAC_WDINT__

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
#if(_HDMI20_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Read Request Timer Event Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHdmiReadRequestTimerEnable_WDINT(void)
{
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
    {
        // FW Manual Enable Read Request
        ScalerSetBit_EXINT(P72_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);
    }
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI20_RR_ENABLE() == _TRUE)
    {
        // FW Manual Enable Read Request
        ScalerSetBit_EXINT(P73_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);
    }
#endif
}
#endif

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : BED Detect When Unstable
// Input Value  : enumRx
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRxHdmiUnstableBedCheck_WDINT(EnumRx enumRx)
{
    switch(enumRx)
    {
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _RX3:

            // Read BED Value
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_AF_PORT_PAGE72_HDMI_BED_FUNC_0, ~_BIT5, _BIT5);

            if((ScalerGetDataPortSingleByte_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_B9_PORT_PAGE72_HDMI_BED_FUNC_10) >= 0x7F) ||
               (ScalerGetDataPortSingleByte_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_BA_PORT_PAGE72_HDMI_BED_FUNC_11) >= 0x7F) ||
               (ScalerGetDataPortSingleByte_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_BB_PORT_PAGE72_HDMI_BED_FUNC_12) >= 0x7F))
            {
                // Set D Domain Region Free run/ Force to Background
                ScalerDDomainResetDDomainRgn(GET_TMDS_MAC_RX3_FORCE_BCKGRD_PATH());

                // Disable RGB/clock Output to avoid garbage
                ScalerSetBit_EXINT(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                // Reset FIFO
                ScalerTmdsPhyRxUnstableFifoReset_EXINT0(ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3));

                // SET BED error Flag
                SET_TMDS_MAC_RX3_BED_ERROR();
            }
            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _RX4:

            // Read BED Value
            ScalerSetDataPortBit_EXINT0(P73_C9_HDMI_AP, _P73_CA_PT_AF_PORT_PAGE73_HDMI_BED_FUNC_0, ~_BIT5, _BIT5);

            if((ScalerGetDataPortSingleByte_EXINT0(P73_C9_HDMI_AP, _P73_CA_PT_B9_PORT_PAGE73_HDMI_BED_FUNC_10) >= 0x7F) ||
               (ScalerGetDataPortSingleByte_EXINT0(P73_C9_HDMI_AP, _P73_CA_PT_BA_PORT_PAGE73_HDMI_BED_FUNC_11) >= 0x7F) ||
               (ScalerGetDataPortSingleByte_EXINT0(P73_C9_HDMI_AP, _P73_CA_PT_BB_PORT_PAGE73_HDMI_BED_FUNC_12) >= 0x7F))
            {
                // Set D Domain Region Free run/ Force to Background
                ScalerDDomainResetDDomainRgn(GET_TMDS_MAC_RX4_FORCE_BCKGRD_PATH());

                // Disable RGB/clock Output to avoid garbage
                ScalerSetBit_EXINT(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                // Reset FIFO
                ScalerTmdsPhyRxUnstableFifoReset_EXINT0(ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4));

                // SET BED Error Flag
                SET_TMDS_MAC_RX4_BED_ERROR();
            }
            break;
#endif


        default:
            break;
    }
}
#endif
#endif
