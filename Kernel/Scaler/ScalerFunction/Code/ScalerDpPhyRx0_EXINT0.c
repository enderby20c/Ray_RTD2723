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
// ID Code      : ScalerDpPhyRx0_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHYRX0_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx0/ScalerDpPhyRx0.h"

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX0_SUPPORT == _ON))
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
// Description  : Signal Detect Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpPhyRx0Tp1SignalDetectCheck_EXINT0(BYTE ucDpLaneSel)
{
    switch(ScalerDpAuxRxGetLinkRate_EXINT0(ScalerDpPhyRxRxDxMapping(_RX0)))
    {
        case _DP_LINK_HBR3_9G:

            if((g_pusDpPhyRx0ClockTarget[ucDpLaneSel] > _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_9G_EXINT0) ||
               (g_pusDpPhyRx0ClockTarget[ucDpLaneSel] < _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_9G_EXINT0))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_HBR3:

            if((g_pusDpPhyRx0ClockTarget[ucDpLaneSel] > _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_EXINT0) ||
               (g_pusDpPhyRx0ClockTarget[ucDpLaneSel] < _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_EXINT0))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_HBR2:

            if((g_pusDpPhyRx0ClockTarget[ucDpLaneSel] > _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2_EXINT0) ||
               (g_pusDpPhyRx0ClockTarget[ucDpLaneSel] < _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2_EXINT0))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_HBR:

            if((g_pusDpPhyRx0ClockTarget[ucDpLaneSel] > _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR_EXINT0) ||
               (g_pusDpPhyRx0ClockTarget[ucDpLaneSel] < _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR_EXINT0))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_RBR:

            if((g_pusDpPhyRx0ClockTarget[ucDpLaneSel] > _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR_EXINT0) ||
               (g_pusDpPhyRx0ClockTarget[ucDpLaneSel] < _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR_EXINT0))
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

#endif // End of #if(_DP_PHY_RX0_SUPPORT == _ON)
