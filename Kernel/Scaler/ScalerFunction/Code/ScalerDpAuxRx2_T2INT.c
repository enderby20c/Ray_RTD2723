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
// ID Code      : ScalerDpAuxRx2_T2INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAuxRx2/ScalerDpAuxRx2.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_AUX_RX2_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup Aux Request in Timer2 Interupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdIrqProtect_T2INT(void)
{
    if((GET_DP_AUX_RX2_GLOBAL_IRQ_FLAG_T2INT() == _TRUE) && (g_stDpAuxRx2ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_NONE) &&
       (GET_DP_AUX_RX2_MODE_T2INT() == _DP_RX_AUX_AUTO_MODE) && (GET_DP_AUX_RX2_INT_PROTECT() == _FALSE))
    {
        SET_DP_AUX_RX2_INT_PROTECT();

        SET_DP_AUX_RX2_MODE_BACKUP_EXINT0(_DP_RX_AUX_AUTO_MODE);

        SET_DP_AUX_RX2_MANUAL_MODE_T2INT();
    }
}
#endif

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetManualMode_T2INT(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucLoopIndexInAuxMacro = 0;

    if(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 45)
            {
                break;
            }
        }while(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9);
    }

    // If aux state is xmit_st, wait 5us to handle request data
    if(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) == _BIT9)
    {
        DELAY_5US_EXINT();
    }

    Scaler32SetBit_T2INT(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT17, 0x00);
#else
    BYTE ucLoopIndexInAuxMacro = 0;

    if(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 100)
            {
                break;
            }
        }while(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8);
    }

    Scaler32SetBit_T2INT(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT17, 0x00);
#endif
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetAutoMode_T2INT(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucLoopIndexInAuxMacro = 0;

    if(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 45)
            {
                break;
            }
        }while(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9);

        DELAY_5US_EXINT();
    }

    Scaler32SetBit_T2INT(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT17, _BIT17);
#else
    BYTE ucLoopIndexInAuxMacro = 0;

    if(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 100)
            {
                break;
            }
        }while(Scaler32GetBit_T2INT(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8);
    }

    Scaler32SetBit_T2INT(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT17, _BIT17);
#endif
}
#endif
