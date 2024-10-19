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
// ID Code      : ScalerDpMacTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_TX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMacTx/ScalerDpMacTx.h"




#if(_DP_MAC_TX_SUPPORT == _ON)
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
// Description  : Handle Tx Output stream for EXINT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxForceIdlePattern_EXINT0(void)
{
    // Main Link switch to IDLE Pattern
    ScalerSetBit_EXINT(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _DP_TX_OUTPUT_IDLE_PATTERN);

    // Direct Apply Idle Pattern
    ScalerSetBit_EXINT(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PBB_01_DPTX_ML_PAT_SEL, ~_BIT0, _BIT0);

    // Toggle Arbiter to Avoid DPTX MAC FSM Dead Lock
    ScalerSetBit_EXINT(PBB_C9_ARBITER_CTRL, ~(_BIT5 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PBB_C9_ARBITER_CTRL, ~(_BIT5 | _BIT0), _BIT0);

    if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
    {
        ScalerDpMacTxSetStreamSource_EXINT0(_DP_TX_SOURCE_NONE);
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE)
    {
        if(GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE)
        {
            // Reset DSC Pass-Through Setting
            ScalerDpMacTxDscPassThroughReset_EXINT0();
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set DP Tx Stream Source for EXINT
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource)
{
    SET_DP_TX_STREAM_SOURCE(enumStreamSource);
    SET_DP_TX_STREAM_SOURCE_CHANGE();

    if(enumStreamSource == _DP_TX_SOURCE_NONE)
    {
        // Clear Tx Clone Precheck flag
        SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_FALSE);

        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
}

//--------------------------------------------------
// Description  : Tx INT Handle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxIntHandle_EXINT0(void)
{
    // Short HPD IRQ
    if((ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6) == _BIT6) &&
       (ScalerGetBit_EXINT(PBB_71_HPD_IRQ, _BIT6) == _BIT6))
    {
        BYTE pucData[6] = {0};

        ScalerSetBit_EXINT(PBB_71_HPD_IRQ, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

#if((_DP_SUPPORT == _ON) && (_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON))
        EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus_EXINT0(_DP_TX_LOOP_BACK_DPRX_INPUT_PORT);

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
        {
            ScalerDpAuxRxSetAutoMode_EXINT0(_DP_TX_LOOP_BACK_DPRX_INPUT_PORT);
        }
#endif

        if(ScalerDpAuxTxNativeRead_EXINT0(0x00, 0x02, 0x00, 6, pucData) == _TRUE)
        {
            SET_DP_TX_IRQ_HPD_DETECTED();

            if(((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 1) && ((pucData[2] & 0x07) != 0x07)) ||
               ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 2) && ((pucData[2] & 0x77) != 0x77)) ||
               ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 4) && (((pucData[2] & 0x77) != 0x77) || ((pucData[3] & 0x77) != 0x77))) ||
               ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() != 1) && ((pucData[4] & 0x01) != 0x01)))
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
            }

            if((pucData[1] & _BIT2) == _BIT2)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CP_IRQ);
            }

            if((pucData[1] & _BIT1) == _BIT1)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
            }

            if((pucData[4] & _BIT6) == _BIT6)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE);
            }
        }

        if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
        {
            // Get IRQ Event Status Indicator
            if(ScalerDpAuxTxNativeRead_EXINT0(0x00, 0x20, 0x03, 3, pucData) == _TRUE)
            {
                SET_DP_TX_IRQ_HPD_DETECTED();

                if((pucData[0] & _BIT1) == _BIT1)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
                }

                if((pucData[0] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CP_IRQ);
                }

                if((pucData[0] & _BIT3) == _BIT3)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_MCCS_IRQ);
                }

                if(((pucData[0] & _BIT4) == _BIT4) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ) == 0x00))
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);
                }

                if(((pucData[0] & _BIT5) == _BIT5) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ) == 0x00))
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);
                }

                if((pucData[1] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CEC_IRQ);
                }

                if((pucData[1] & _BIT4) == _BIT4)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_DSC_ERROR_STATUS_IRQ);
                }

                if((pucData[2] & _BIT0) == _BIT0)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ);
                }

                if((pucData[2] & _BIT1) == _BIT1)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                }

                if((pucData[2] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
                }
            }
        }

#if((_DP_SUPPORT == _ON) && (_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON))
        if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
        {
            ScalerDpAuxRxSetManualMode_EXINT0(_DP_TX_LOOP_BACK_DPRX_INPUT_PORT);
        }
#endif
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    ScalerDpMacTxDscIntHandle_EXINT0();
#endif
}

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Tx Stream DSC BPP Change for EXINT
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscIntHandle_EXINT0(void)
{
    if(ScalerGetBit_EXINT(PBB_A3_DPTX_IRQ_CTRL, (_BIT7 | _BIT0)) == (_BIT7 | _BIT0))
    {
        // Write Clear The DPTx Irq Flag
        ScalerSetBit_EXINT(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);

        // Check DSC Stream Change
        if(ScalerGetBit_EXINT(PBB_A3_DPTX_IRQ_CTRL, (_BIT6 | _BIT4)) == (_BIT6 | _BIT4))
        {
            // Write Clear The DSC Stream Change Flag, Disable DSC Stream Change IRQ
            ScalerSetBit_EXINT(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT4);

            // Set DPTx Force Output Idle Pattern
            ScalerDpMacTxForceIdlePattern_EXINT0();
        }
    }
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Reset for EXINT
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscPassThroughReset_EXINT0(void)
{
    // Disable VBID[6] DSC Compression Flag
    ScalerSetBit_EXINT(PBB_C7_VBID, ~_BIT3, 0x00);

    // Wirte Clear DPTx Irq Flag
    ScalerSetBit_EXINT(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);

    // Set DPTx Irq Disable
    ScalerSetBit_EXINT(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT7 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // Clear DSC Downstream Pass-through Flag
    CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Reset MST Tx stream to ID array
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetStreamToIdMapping_EXINT0(void)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    // Reset Stream ID Mapping Table
    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        g_pucDpMacTxStreamToIdMapping[enumDpStreamNum] = 0;
    }
}
#endif


#endif // End for #if(_DP_MAC_TX_SUPPORT == _ON)

