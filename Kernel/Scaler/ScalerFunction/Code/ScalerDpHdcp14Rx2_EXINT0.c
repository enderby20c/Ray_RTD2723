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
// ID Code      : ScalerDpHdcp14Rx2_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp14Rx2/ScalerDpHdcp14Rx2.h"




#if(_DP_HDCP14_RX2_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx2ResetKsvFifoToFirst_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_EXINT0(_RX2);

    for(g_usDpHdcp14Rx2KsvFifoOffset = 0; g_usDpHdcp14Rx2KsvFifoOffset < 15; g_usDpHdcp14Rx2KsvFifoOffset++)
    {
        if(GET_DP_TX_HDCP_KSV_FIFO_MAX() > g_usDpHdcp14Rx2KsvFifoOffset)
        {
            // DPCD [0x6802C ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x80, (0x2C + g_usDpHdcp14Rx2KsvFifoOffset), g_pucDpMacTxHdcpKsvFifo[g_usDpHdcp14Rx2KsvFifoOffset]);
        }
        else
        {
            // DPCD [0x6802C ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x80, (0x2C + g_usDpHdcp14Rx2KsvFifoOffset), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx2SetKsvFifo_EXINT0(void)
{
    BYTE ucTemp = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_EXINT0(_RX2);

    for(ucTemp = 0; ucTemp < 15; ucTemp++)
    {
        if(GET_DP_TX_HDCP_KSV_FIFO_MAX() > (g_usDpHdcp14Rx2KsvFifoOffset + ucTemp))
        {
            // DPCD [0x6802C ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x80, (0x2C + ucTemp), g_pucDpMacTxHdcpKsvFifo[g_usDpHdcp14Rx2KsvFifoOffset + ucTemp]);
        }
        else
        {
            // DPCD [0x6802C ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x80, (0x2C + ucTemp), 0x00);
        }
    }

    g_usDpHdcp14Rx2KsvFifoOffset += ucTemp;
}
#endif
#endif
