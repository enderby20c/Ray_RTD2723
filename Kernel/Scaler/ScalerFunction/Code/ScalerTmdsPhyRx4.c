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
// ID Code      : ScalerTmdsPhyRx4.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSPHYRX4__

#include "ScalerFunctionInclude.h"
#include "TmdsPhyRx4/ScalerTmdsPhyRx4.h"


#if(_TMDS_PHY_RX4_SUPPORT == _ON)
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
// Description  : DFE Adaptation in Normal Signal
// Input Value  : None
// Output Value : True --> DFE Normal
//                False --> DFE Abnormal
//--------------------------------------------------
bit ScalerTmdsPhyRx4CheckDFE(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsPhyRxRxDxMapping_EXINT0(_RX4);
    BYTE ucLane = 0;
    BYTE ucTemp = 0;
    BYTE ucTap1Max = 0;
    BYTE ucLEMax = 0;

    if(ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) <= 2000) // DCDR
    {
        if(ScalerGetBit(P7D_A0_L0_DFE_EN_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) // DFE Mode 3
        {
            ucLEMax = (ScalerGetBit(P7D_A3_L0_INIT_1, _BIT7) >> 3) + (ScalerGetBit(P7D_A2_L0_LIMIT_INIT, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
            ucTap1Max = ScalerGetBit(P7D_E7_LIMIT_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) - ucLEMax;
        }
        else // DFE  Mode 2
        {
            ucTap1Max = ScalerGetBit(P7D_E7_LIMIT_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        }

        for(ucLane = 0; ucLane <= 2; ucLane++)
        {
            // Sel lane
            ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), (ucLane << 6));

            // Read Tap1
            ScalerSetByte(P7D_F0_COEF_1, 0x02);

            ucTemp = (ScalerGetByte(P7D_F1_COEF_2) & 0x1F);
            if(ucTemp >= ucTap1Max)
            {
                DebugMessageRx4("no signal", 0);
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : TMDS Disable Data Lane DFE
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx4DisableDFE(void)
{
    // Disable LE, Vth, Tap0~4 Adaptation
    ScalerSetByte(P7D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P7D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P7D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P7D_D1_L3_DFE_EN_2, 0x00);
}


#endif // End of #if(_TMDS_PHY_RX4_SUPPORT == _ON)

