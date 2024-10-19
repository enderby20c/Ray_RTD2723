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
// ID Code      : ScalerDpMstTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPTXMST_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMstTx/ScalerDpMstTx.h"



//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Position Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxResetDaisyStreamPositionReg_EXINT0(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)

    // Reset Stream 1-6 enable
    ScalerSetBit_EXINT(P2B_D3_SOURCE_CTRL_0, ~0x3F, 0x00);

    // Reset Stream 1-6 start, end 8b10b

    // st1
    ScalerSetBit_EXINT(P2B_D4_SOURCE_CTRL_1, ~0x3F, 0x00);
    ScalerSetBit_EXINT(P2B_D5_SOURCE_CTRL_2, ~0x3F, 0x00);
    // st2
    ScalerSetBit_EXINT(P2B_D6_SOURCE_CTRL_3, ~0x3F, 0x00);
    ScalerSetBit_EXINT(P2B_D7_SOURCE_CTRL_4, ~0x3F, 0x00);
    // st3
    ScalerSetBit_EXINT(P2B_D8_SOURCE_CTRL_5, ~0x3F, 0x00);
    ScalerSetBit_EXINT(P2B_D9_SOURCE_CTRL_6, ~0x3F, 0x00);
    // st4
    ScalerSetBit_EXINT(P2B_DA_SOURCE_CTRL_7, ~0x3F, 0x00);
    ScalerSetBit_EXINT(P2B_DB_SOURCE_CTRL_8, ~0x3F, 0x00);
    // st5
    ScalerSetBit_EXINT(P2B_90_SOURCE_CTRL_11, ~0x3F, 0x00);
    ScalerSetBit_EXINT(P2B_91_SOURCE_CTRL_12, ~0x3F, 0x00);
    // st6
    ScalerSetBit_EXINT(P2B_92_SOURCE_CTRL_13, ~0x3F, 0x00);
    ScalerSetBit_EXINT(P2B_93_SOURCE_CTRL_14, ~0x3F, 0x00);
#endif

    // Reset st 1-6 start, end 8b10b

    // st1
    ScalerSetBit_EXINT(PA_06_DAISY_CTRL_1, ~0x3F, 0x00);
    ScalerSetBit_EXINT(PA_07_DAISY_CTRL_2, ~0x3F, 0x00);
    // st2
    ScalerSetBit_EXINT(PA_08_DAISY_CTRL_3, ~0x3F, 0x00);
    ScalerSetBit_EXINT(PA_09_DAISY_CTRL_4, ~0x3F, 0x00);
    // st3
    ScalerSetBit_EXINT(PA_0A_DAISY_CTRL_5, ~0x3F, 0x00);
    ScalerSetBit_EXINT(PA_0B_DAISY_CTRL_6, ~0x3F, 0x00);
    // st4
    ScalerSetBit_EXINT(PA_0C_DAISY_CTRL_7, ~0x3F, 0x00);
    ScalerSetBit_EXINT(PA_0D_DAISY_CTRL_8, ~0x3F, 0x00);
    // st5
    ScalerSetBit_EXINT(PA_12_DAISY_CTRL_9, ~0x3F, 0x00);
    ScalerSetBit_EXINT(PA_13_DAISY_CTRL_10, ~0x3F, 0x00);
    // st6
    ScalerSetBit_EXINT(PA_14_DAISY_CTRL_11, ~0x3F, 0x00);
    ScalerSetBit_EXINT(PA_15_DAISY_CTRL_12, ~0x3F, 0x00);
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Source Mux Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxResetDaisySourceMuxReg_EXINT0(void)
{
    // Reset Tx Daisy Source Mux to Default nth Source to nth stream
    ScalerSetBit_EXINT(PA_17_SOURCE_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit_EXINT(PA_17_SOURCE_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit_EXINT(PA_18_SOURCE_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit_EXINT(PA_18_SOURCE_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit_EXINT(PA_19_SOURCE_CTRL_2, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit_EXINT(PA_19_SOURCE_CTRL_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Reset Tx Daisy Source Mux to Default nth Source to nth stream
    ScalerSetBit_EXINT(P2B_DC_SOURCE_CTRL_9, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit_EXINT(P2B_DC_SOURCE_CTRL_9, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit_EXINT(P2B_DD_SOURCE_CTRL_10, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit_EXINT(P2B_DD_SOURCE_CTRL_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit_EXINT(P2B_94_SOURCE_CTRL_15, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit_EXINT(P2B_94_SOURCE_CTRL_15, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
#endif
}

//--------------------------------------------------
// Description  : Reset DP Tx MST Daisy Source Mux Backup
// Input Value  : Void
// Output Value : Void
//--------------------------------------------------
void ScalerDpMstTxResetDaisySourceMuxBackup_EXINT0(void)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    for(enumSourceNum = _DP_ST_SOURCE_DAISY_START; enumSourceNum <= _DP_ST_SOURCE_DAISY_END; enumSourceNum++)
    {
        SET_DP_MAC_TX_ST_SOURCE_BACKUP(enumSourceNum, _DP_ST_NONE);
    }
}


#endif // End for #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
