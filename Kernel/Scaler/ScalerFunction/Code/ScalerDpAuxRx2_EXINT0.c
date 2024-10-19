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
// ID Code      : ScalerDpAuxRx2_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAuxRx2/ScalerDpAuxRx2.h"




#if(_DP_AUX_RX2_SUPPORT == _ON)
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
// Description  : DP Interrupt Rx2 Pre-Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2PreIntHandler_EXINT0(void)
{
/*
#if(_HW_DP_DPCD_NO_PHYSICAL_ADDRESS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P2D_FB_DP2_MANUAL_DPCD_IRQ, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Aux Firmware Control -> Reply Defer
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();

        // Enable Force Defer
        ScalerSetBit_EXINT(P2D_D0_AUX_MODE_SET, ~_BIT4, _BIT4);

        // Reset Aux FIFO
        ScalerSetBit_EXINT(P2D_DA_AUX_FIFO_RST, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT0);
    }
    else
#endif
*/
    {
        if(GET_DP_AUX_RX2_MODE_EXINT() == _DP_RX_AUX_AUTO_MODE)
        {
            // Aux Firmware Control -> Reply Defer
            SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Aux Rx2 Mac High Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2HighPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_AUX_RX2_GLOBAL_HIGH_PRIORITY_IRQ_FLAG() == _TRUE)
    {
#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
        // Fake LT Set DPCD 00280h Enable Sequence
        if((ScalerDpAuxRx2GetDpcdWildCardIntEnable_EXINT0(_AUX_RX_FEC_DECODE_EN_DETECTED) == _ENABLE) &&
           (ScalerDpAuxRx2DpcdWildCardIntCheck_EXINT0(_AUX_RX_FEC_DECODE_EN_DETECTED) == _ENABLE))
        {
            // Clear Flag
            ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_FEC_DECODE_EN_DETECTED);

            ScalerDpAuxRx2DpcdFecStatusW1cProtectHandler_EXINT0();
        }
#endif
#endif

#if((_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
#if(_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON)
        if((ScalerDpAuxRx2GetDpcdWildCardIntEnable_EXINT0(_AUX_RX_CABLE_ID_UPDATE) == _ENABLE) &&
           (ScalerDpAuxRx2DpcdWildCardIntCheck_EXINT0(_AUX_RX_CABLE_ID_UPDATE) == _ENABLE))
        {
            // Clear Flag
            ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_CABLE_ID_UPDATE);

            ScalerDpAuxRx2DpcdCableIDSyncHandler_EXINT0();
        }
#endif
#endif
    }
}
//--------------------------------------------------
// Description  : Dp Aux Rx2 Mac Low Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2LowPriorityIntHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    enumInputPort = enumInputPort;

    if(GET_DP_AUX_RX2_GLOBAL_LOW_PRIORITY_IRQ_FLAG() == _TRUE)
    {
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
        if((Scaler32GetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT8) == _BIT8) && (Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT8) == _BIT8))
        {
            // Clear Flag
            Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT8);

            // Source Write DPCD 0x00160
            ScalerDpAuxRx2DscEnable_EXINT0();
        }
#endif

/*
#if(_HW_DP_DPCD_NO_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        // DPCD 022xxh Into INT
        if(ScalerGetBit_EXINT(P2D_FB_DP2_MANUAL_DPCD_IRQ, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            BYTE ucDPCDAddress = 0;

            // Clear Flag
            ScalerSetBit_EXINT(P2D_FB_DP2_MANUAL_DPCD_IRQ, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            ucDPCDAddress = (ScalerGetByte_EXINT(P2D_D4_AUX_RX_ADDR_L));

            pData_EXINT[1] = (ScalerGetByte_EXINT(P2D_D5_AUX_RXLEN) & 0x0F) + 1;
            ucDPCDAddress -= pData_EXINT[1];

            if(ucDPCDAddress <= 0x0F)
            {
                if(ucDPCDAddress == 0x00)
                {
                    ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, _DP_VERSION_1_4);
                    ucDPCDAddress++;
                    pData_EXINT[1]--;
                }

                if((pData_EXINT[1] > 0) && (ucDPCDAddress == 0x01))
                {
                    ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, g_ucDpAuxRx2CapLinkRate);
                    ucDPCDAddress++;
                    pData_EXINT[1]--;
                }

                if((ucDPCDAddress + pData_EXINT[1]) > 16)
                {
                    // pData_EXINT[2] is The Address of DPCD Table
                    for(pData_EXINT[2] = ucDPCDAddress; pData_EXINT[2] <= 0x0F; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x00, pData_EXINT[2]));
                    }

                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, 0x08);

                    for(pData_EXINT[2] = pData_EXINT[2]; pData_EXINT[2] <= pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, 0x00);
                    }
                }
                else
                {
                    for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x00, (ucDPCDAddress + pData_EXINT[2])));
                    }
                }
            }
            else
            {
                if(ucDPCDAddress == 0x10)
                {
                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, 0x08);

                    ucDPCDAddress++;
                    pData_EXINT[1]--;
                }

                for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                {
                    ScalerSetByte_EXINT(P2D_D9_AUX_TX_DATA, 0x00);
                }
            }

            // Reload The Length of Aux Message
            ScalerSetByte_EXINT(P2D_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(P2D_D5_AUX_RXLEN) & 0x0F));
        }
#endif
*/

#if((_DP_TX_SUPPORT == _ON) && (_D2_DP_MST_PORT_SUPPORT == _ON))
        // Read 6803A into INT0
        if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT10) == _BIT10) &&
           (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT10) == _BIT10))
        {
            CLR_DP_AUX_RX2_HDCP_KSV_FIFO_INT_FLAG_EXINT();

            ScalerDpHdcp14RxSetKsvFifo_EXINT0(enumInputPort);
        }
#endif

        // Write 00270h into INT0
        if(Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT26) == _BIT26)
        {
            // Clear Flag
            Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT26);

            ScalerDpAuxRx2DpcdTestCRCHandler_EXINT0();
        }

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
        // Write 001C2 into INT0
        if((Scaler32GetBit_EXINT0(PB1A001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT4) == _BIT4) &&
           (Scaler32GetBit_EXINT0(PB1A001_C4_AUX_PAYLOAD_IRQ_EN, _BIT4) == _BIT4))
        {
            // Clear Flag
            Scaler32SetDWord_EXINT0(PB1A001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT4);

            ScalerDpAuxRxSyncPayloadIDHandler_EXINT0(enumInputPort);
        }

        // Read 002C0h into INT0
        if((Scaler32GetBit_EXINT0(PB1A001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT3) == _BIT3) &&
           (Scaler32GetBit_EXINT0(PB1A001_C4_AUX_PAYLOAD_IRQ_EN, _BIT3) == _BIT3))
        {
            // Clear Flag
            Scaler32SetDWord_EXINT0(PB1A001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT3);

            ScalerDpAuxRxSyncActHandler_EXINT0(enumInputPort);
        }
#endif

#if(_DP_MST_SUPPORT == _ON)
        // Source Write DPCD 111h
        if((Scaler32GetBit_EXINT0(PB1A001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT7) == _BIT7) &&
           (Scaler32GetBit_EXINT0(PB1A001_C4_AUX_PAYLOAD_IRQ_EN, _BIT7) == _BIT7))
        {
            // Clear Flag
            Scaler32SetDWord_EXINT0(PB1A001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT7);

            ScalerDpAuxRxMstProtocolEnableHandler_EXINT0(enumInputPort);
        }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
        if((Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT10) == _BIT10) &&
           (Scaler32GetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT10) == _BIT10))
        {
            // Clear Flag
            Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT10);

            ScalerDpAuxRx2DpcdPrModeHandler_EXINT0();
        }
#endif

#if(_DP_AUX_RX_DPCD_300_SOURCE_OUI_INT_SUPPORT == _ON)
        if((Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT25) == _BIT25) &&
           (Scaler32GetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT25) == _BIT25))
        {
            // Clr IRQ Flag
            Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT25);

#if(_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)
            SET_DP_RX_USER_INT_EVENT(enumInputPort, _DP_USER_INT_EVENT_SOURCE_WRITE_OUI);
#endif
        }
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(ScalerDpAuxRxCheckLinkRate_EXINT0(enumInputPort) == _FALSE)
    {
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x00);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        return _FALSE;
    }

    ScalerDpAuxRx2ErrorCounterDisable_EXINT0();

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT))
    g_ucDpAuxRx2Tp1PermitSwingLevel0 = _TRUE;

#elif(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
    g_ucDpAuxRx2Tp1PermitSwingLevel0 = ScalerDpAuxRx2CheckSourceOUI_EXINT0(_LT_TP1_PERMIT_SWING_LEVEL_0);

#endif

    if(enumDpLtType == _DP_NORMAL_LT)
    {
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
        {
            ScalerDpPhyRxTp1SetPhy_EXINT0(enumInputPort, _DP_NF_REF_XTAL);
        }
        else
#endif
        {
            if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & (_BIT1 | _BIT0)) >= _BIT0)
            {
                ScalerDpPhyRxTp1SetPhy_EXINT0(enumInputPort, _DP_NF_REF_XTAL);
                ScalerDpAuxRx2ErrorCounterEnable_EXINT0(enumDpLtType);
            }
            else
            {
#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
                if(g_ucDpAuxRx2Tp1PermitSwingLevel0 == _TRUE)
                {
                    ScalerDpPhyRxTp1SetPhy_EXINT0(enumInputPort, _DP_NF_REF_XTAL);
                    ScalerDpAuxRx2ErrorCounterEnable_EXINT0(enumDpLtType);
                }
                else
#endif
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
#if(_DP_LT_TP1_FORCE_MARGINAL_LINK == _OFF)

                        ScalerDpPhyRxTp1SetPhy_EXINT0(enumInputPort, _DP_NF_REF_XTAL);
                        ScalerDpAuxRx2ErrorCounterEnable_EXINT0(enumDpLtType);
#endif
                    }
                }
            }
        }
    }

    if(ScalerDpAuxRx2Tp1Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    ScalerDpAuxRx2ErrorCounterDisable_EXINT0();

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        ScalerDpPhyRxTp2SetPhy_EXINT0(enumInputPort);
    }

    ScalerDpAuxRx2ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpAuxRx2Tp2Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Training Pattern 3
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2TrainingPattern3_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(ScalerDpAuxRx2Tp3Check_EXINT0(enumDpLtType) == _FALSE)
    {
        ScalerDpPhyRxTp3SetPhy_EXINT0(enumInputPort);

        if(ScalerDpAuxRx2Tp3Check_EXINT0(enumDpLtType) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Settings after Link Training Pass
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2TrainingPatternEnd_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
    {
        // Check FEC Decode Status
        if(ScalerDpMacDphyRxFecDecodeCheck_EXINT0(enumInputPort) != _TRUE)
        {
            // FIFO sync
            ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
            DELAY_45US_EXINT();
        }
    }
#endif
#endif

    ScalerDpMacDphyRxLaneCountSet_EXINT0(enumInputPort, g_enumDpAuxRx2LaneCount);

    // De-Skew Circuit Reset
    ScalerDpMacDphyRxDeSkewReset_EXINT0(enumInputPort);

    if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerDpMacDphyRxEnhancementControlMode_EXINT0(enumInputPort, _ENABLE);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerDpMacDphyRxEnhancementControlMode_EXINT0(enumInputPort, _DISABLE);
    }

    if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerDpMacDphyRxScramble_EXINT0(enumInputPort, _DISABLE);
    }
    else
    {
        // Enable Scrambling
        ScalerDpMacDphyRxScramble_EXINT0(enumInputPort, _ENABLE);
    }

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
    {
        DELAY_5US_EXINT();
        ScalerDpMacDphyRxClearFecErrorCount_EXINT0(enumInputPort);
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : Check Dp PHY CTS Training Pattern 1
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2PhyCtsTrainingPattern1_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    ScalerDpAuxRx2ErrorCounterDisable_EXINT0();

    // Link Rate
    ScalerDpPhyRxSetPhyCtsTestLinkRate_EXINT0(enumInputPort, g_enumDpAuxRx2LinkRate);

    // Lane Select
    ScalerDpPhyRxSetPhyCtsTestLane_EXINT0(enumInputPort, ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)));

    // TP1 Setphy
    ScalerDpPhyRxPhyCtsTp1SetPhy_EXINT0(enumInputPort, _DP_NF_REF_XTAL);

    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case (_BIT5 | _BIT4):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x16, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x17, 0x80);

            break;

        case (_BIT5):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x14, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x15, 0x80);

            break;

        case (_BIT4):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x12, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x13, 0x80);

            break;

        default:
        case 0x00:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x10, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x11, 0x80);

            break;
    }

    // Enable 8B/10B Error Counter
    ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B);

    // Enable Read Error Counter IRQ, Clear IRQ Flag
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_210);
    ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
    ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
#else
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, _BIT1);
    Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);
    Scaler32SetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT9, _BIT9);
#endif

    return ScalerDpAuxRx2PhyCtsTp1Check_EXINT0();
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2PhyCtsTrainingPattern2_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    ScalerDpAuxRx2ErrorCounterDisable_EXINT0();

    ScalerDpPhyRxPhyCtsTp2SetPhy_EXINT0(enumInputPort);

    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case (_BIT5 | _BIT4):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x16, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x17, 0x80);

            break;

        case (_BIT5):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x14, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x15, 0x80);

            break;

        case (_BIT4):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x12, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x13, 0x80);

            break;

        default:
        case 0x00:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x10, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x11, 0x80);

            break;
    }

    // Enable 8B/10B Error Counter
    ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B);

    // Enable Read Error Counter IRQ, Clear IRQ Flag
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_210);
    ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
    ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
#else
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, _BIT1);
    Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);
    Scaler32SetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT9, _BIT9);
#endif

    return ScalerDpAuxRx2PhyCtsTp2Check_EXINT0();
}

//--------------------------------------------------
// Description  : Dp Training Pattern End Initial Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2PhyCtsTrainingPatternEnd_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    ScalerDpAuxRx2ErrorCounterDisable_EXINT0();

    // Rebuild phy for pattern switch
    ScalerDpPhyRxPhyCtsTp2SetPhy_EXINT0(enumInputPort);

    // Mac Reset After Link Clock Stable
    ScalerDpMacDphyRxReset_EXINT0(enumInputPort);

    if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x00) == 0x06) ||
       (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x00) == 0x0A))
    {
        // PRBS7 Pattern for RBR/HBR
        ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_PRBS7);
    }
    else
    {
        // HBR2 Compliance Eye Pattern
        ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B_DISPARITY);
    }

    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case (_BIT5 | _BIT4):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x16, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x17, 0x80);

            break;

        case (_BIT5):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x14, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x15, 0x80);

            break;

        case (_BIT4):

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x12, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x13, 0x80);

            break;

        default:
        case 0x00:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x10, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x11, 0x80);

            break;
    }

    // Enable Read Error Counter IRQ, Clear IRQ Flag
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_210);
    ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
    ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
#else
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, _BIT1);
    Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);
    Scaler32SetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT9, _BIT9);
#endif
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
    {
        return ScalerDpAuxRx2Tp1Check_128b132b_EXINT0();
    }
    else
#endif
    {
        return ScalerDpAuxRx2Tp1Check_8b10b_EXINT0(enumDpLtType);
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
    {
        return ScalerDpAuxRx2Tp2Check_128b132b_EXINT0(enumDpLtType);
    }
    else
#endif
    {
        return ScalerDpAuxRx2Tp2Check_8b10b_EXINT0(enumDpLtType);
    }
}

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Training Pattern 3
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp3Check_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    BYTE ucEQCRCStatus = 0;
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if(ScalerDpMacDphyRxTp3DecodeCheck_EXINT0(enumInputPort, _DP_LANE_0) == _TRUE)
        {
            ucEQCRCStatus |= _BIT0;
        }

        if(ScalerDpMacDphyRxTp3DecodeCheck_EXINT0(enumInputPort, _DP_LANE_1) == _TRUE)
        {
            ucEQCRCStatus |= _BIT1;
        }

        if(ScalerDpMacDphyRxTp3DecodeCheck_EXINT0(enumInputPort, _DP_LANE_2) == _TRUE)
        {
            ucEQCRCStatus |= _BIT2;
        }

        if(ScalerDpMacDphyRxTp3DecodeCheck_EXINT0(enumInputPort, _DP_LANE_3) == _TRUE)
        {
            ucEQCRCStatus |= _BIT3;
        }

        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_FOUR_LANE:

                g_ucDpAuxRx2LinkStatus01 = 0x11;
                g_ucDpAuxRx2LinkStatus23 = 0x11;

                // Lane3 EQ-CRC Check
                if((ucEQCRCStatus & _BIT3) == _BIT3)
                {
                    g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x70;
                }

                // Lane2 EQ-CRC Check
                if((ucEQCRCStatus & _BIT2) == _BIT2)
                {
                    g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x07;
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                }

                break;

            case _DP_TWO_LANE:

                g_ucDpAuxRx2LinkStatus01 = 0x11;
                g_ucDpAuxRx2LinkStatus23 = 0x00;

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                }

                break;

            case _DP_ONE_LANE:
            default:

                g_ucDpAuxRx2LinkStatus01 = 0x01;
                g_ucDpAuxRx2LinkStatus23 = 0x00;

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                }

                break;
        }

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & 0x07) == 0x07)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));

                    return _TRUE;
                }
                else
                {
                    g_ucDpAuxRx2PreferPreset++;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & 0x77) == 0x77)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));

                    return _TRUE;
                }
                else
                {
                    g_ucDpAuxRx2PreferPreset++;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpAuxRx2LinkStatus01 & 0x77) == 0x77) && (((g_ucDpAuxRx2LinkStatus23 & 0x77) == 0x77)))
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));

                    return _TRUE;
                }
                else
                {
                    g_ucDpAuxRx2PreferPreset++;
                }

                break;
        }
    }
    else
    {
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x07);
                ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));

                return _TRUE;

            case _DP_TWO_LANE:

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));

                return _TRUE;

            case _DP_FOUR_LANE:
            default:

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x77);
                ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));

                return _TRUE;
        }
    }

    if(g_ucDpAuxRx2PreferPreset >= 20)
    {
        g_ucDpAuxRx2PreferPreset = 0;
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, 0x00);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);
        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT4));
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2PhyCtsTp1Check_EXINT0(void)
{
    BYTE pucDpAuxLinkTrainingLevel[4];
    BYTE pucDpAuxLinkTrainingRequest[4];
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL) &&
       (g_bDpAuxRx2Tp1Initial == _FALSE))
    {
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x03, 0x00);
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x04, 0x00);
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x05, 0x00);
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x06, 0x00);

        g_ucDpAuxRx2LinkRequest01 = 0x00;
        g_ucDpAuxRx2LinkRequest23 = 0x00;

        g_bDpAuxRx2Tp1Initial = _TRUE;
    }

    pucDpAuxLinkTrainingLevel[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
    pucDpAuxLinkTrainingLevel[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
    pucDpAuxLinkTrainingLevel[2] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
    pucDpAuxLinkTrainingLevel[3] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 3; ucLoopIndex++)
    {
        pucDpAuxLinkTrainingRequest[ucLoopIndex] = 0x02;
    }

    g_ucDpAuxRx2LinkStatus01 = 0;
    g_ucDpAuxRx2LinkStatus23 = 0;

    // Source Lane
    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case 0x00: // Lane0 Test

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#else
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, _DP_LANE_0) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#endif
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x00;
            }
            else
            {
                g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
            }

            break;

        case _BIT4: // Lane1 Test

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1)) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#else
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, _DP_LANE_1) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#endif
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x10;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x00;
            }
            else
            {
                g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
            }

            break;

        case _BIT5: // Lane2 Test

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2)) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#else
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, _DP_LANE_2) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#endif
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x00;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x01;
            }
            else if(((pucDpAuxLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
            {
                g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
            }

            break;

        case (_BIT5 | _BIT4): // Lane3 Test

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3)) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#else
            if((ScalerDpMacDphyRxTp1Detect_EXINT0(enumInputPort, _DP_LANE_3) == _TRUE) ||
               (g_enumDpAuxRx2LinkRate >= _DP_LINK_UHBR10))
#endif
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x00;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x10;
            }
            else if(((pucDpAuxLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
            {
                g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
            }

            break;

        default:
            break;
    }

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

    // Source Lane
    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case 0x00:

            if((g_ucDpAuxRx2LinkStatus01 & _BIT0) == _BIT0)
            {
                return _TRUE;
            }

            break;

        case _BIT4:

            if((g_ucDpAuxRx2LinkStatus01 & _BIT4) == _BIT4)
            {
                return _TRUE;
            }

            break;

        case _BIT5:

            if((g_ucDpAuxRx2LinkStatus23 & _BIT0) == _BIT0)
            {
                return _TRUE;
            }

            break;

        case (_BIT5 | _BIT4):

            if((g_ucDpAuxRx2LinkStatus23 & _BIT4) == _BIT4)
            {
                return _TRUE;
            }

            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2PhyCtsTp2Check_EXINT0(void)
{
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
    {
        return ScalerDpAuxRx2PhyCtsTp2Check_128b132b_EXINT0();
    }
    else
#endif
    {
        return ScalerDpAuxRx2PhyCtsTp2Check_8b10b_EXINT0();
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp1Check_8b10b_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    BYTE ucTP1RBRHBRSwingLevel = 2;
    BYTE pucDpAuxLinkTrainingLevel[4];
    BYTE pucDpAuxLinkTrainingRequest[4];
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

#if((_D2_DP_REDRIVER_TYPE == _REDRIVER_NONE) && (_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _OFF))

    BYTE ucTP1HBR2HBR3SwingLevel = 3;
#else
    BYTE ucTP1HBR2HBR3SwingLevel = 2;
#endif

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(0x00, 0x20, 0x0B, 0x00);
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
    if(g_ucDpAuxRx2Tp1PermitSwingLevel0 == _TRUE)
    {
        ucTP1RBRHBRSwingLevel = 0;
        ucTP1HBR2HBR3SwingLevel = 0;
    }
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpMacDphyRxGetFecDecodeStatus_EXINT0(enumInputPort) == _ENABLE)
    {
        ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _DISABLE);
    }
#endif

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
           (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL) &&
           (g_bDpAuxRx2Tp1Initial == _FALSE))
        {
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x06, 0x00);

            g_ucDpAuxRx2LinkRequest01 = 0x00;
            g_ucDpAuxRx2LinkRequest23 = 0x00;

#if(_DP_LT_TP1_FORCE_MARGINAL_LINK == _ON)
            SET_DP_RX_D2_LANE0_MARGIN_LINK_TP1();
            SET_DP_RX_D2_LANE1_MARGIN_LINK_TP1();
            SET_DP_RX_D2_LANE2_MARGIN_LINK_TP1();
            SET_DP_RX_D2_LANE3_MARGIN_LINK_TP1();
#endif
            g_bDpAuxRx2Tp1Initial = _TRUE;
        }

        pucDpAuxLinkTrainingLevel[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpAuxLinkTrainingLevel[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpAuxLinkTrainingLevel[2] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpAuxLinkTrainingLevel[3] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
        for(BYTE ucLoopIndex = 0; ucLoopIndex <= 3; ucLoopIndex++)
        {
            if((pucDpAuxLinkTrainingLevel[ucLoopIndex] & (_BIT1 | _BIT0)) == 2)
            {
                if((pucDpAuxLinkTrainingLevel[ucLoopIndex] & _BIT2) == _BIT2)
                {
                    g_pucDpAuxRx2MaxSwing[ucLoopIndex] = 2;
                }
                else
                {
                    g_pucDpAuxRx2MaxSwing[ucLoopIndex] = 3;
                }
            }
        }
#endif
        for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
        {
            if((pucDpAuxLinkTrainingLevel[2 * ucLoopIndex] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpAuxLinkTrainingRequest[2 * ucLoopIndex] = 0x02;
#else
                pucDpAuxLinkTrainingRequest[2 * ucLoopIndex] = (pucDpAuxLinkTrainingLevel[2 * ucLoopIndex] & (_BIT1 | _BIT0)) + 0x01;
#endif
            }
            else
            {
                pucDpAuxLinkTrainingRequest[2 * ucLoopIndex] = 0x03;
            }

            if((pucDpAuxLinkTrainingLevel[(2 * ucLoopIndex) + 1] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpAuxLinkTrainingRequest[(2 * ucLoopIndex) + 1] = 0x20;
#else
                pucDpAuxLinkTrainingRequest[(2 * ucLoopIndex) + 1] = ((pucDpAuxLinkTrainingLevel[(2 * ucLoopIndex) + 1] << 4) & (_BIT5 | _BIT4)) + 0x10;
#endif
            }
            else
            {
                pucDpAuxLinkTrainingRequest[(2 * ucLoopIndex) + 1] = 0x30;
            }
        }

        g_ucDpAuxRx2LinkStatus01 = 0;
        g_ucDpAuxRx2LinkStatus23 = 0;

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane3 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x10;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x10;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
                }

                // Lane2 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
                }

                // Lane1 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                }

                // Lane0 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                }

#if(_DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL == _ON)
                if(((g_ucDpAuxRx2LinkStatus01 & 0x11) != 0x11) || ((g_ucDpAuxRx2LinkStatus23 & 0x11) != 0x11))
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                    g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
                    g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
                }
#endif
                break;

            case _DP_TWO_LANE:

                // Lane1 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                }

                // Lane0 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                }

#if(_DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL == _ON)
                if((g_ucDpAuxRx2LinkStatus01 & 0x11) != 0x11)
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                }
#endif
                break;

            case _DP_ONE_LANE:
            default:

                // Lane0 Check
                if(ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) == _TRUE)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1RBRHBRSwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1HBR2HBR3SwingLevel))
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                }

                break;
        }

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & _BIT0) == _BIT0)
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpAuxRx2LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0)) && (((g_ucDpAuxRx2LinkStatus23 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))))
                {
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) && (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
        {
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x06, 0x00);
        }

        pucDpAuxLinkTrainingLevel[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpAuxLinkTrainingLevel[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpAuxLinkTrainingLevel[2] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpAuxLinkTrainingLevel[3] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
        for(BYTE ucLoopIndex = 0; ucLoopIndex <= 3; ucLoopIndex++)
        {
            if((pucDpAuxLinkTrainingLevel[ucLoopIndex] & (_BIT1 | _BIT0)) == 2)
            {
                if((pucDpAuxLinkTrainingLevel[ucLoopIndex] & _BIT2) == _BIT2)
                {
                    g_pucDpAuxRx2MaxSwing[ucLoopIndex] = 2;
                }
                else
                {
                    g_pucDpAuxRx2MaxSwing[ucLoopIndex] = 3;
                }
            }
        }
#endif
        for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
        {
            if((pucDpAuxLinkTrainingLevel[2 * ucLoopIndex] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpAuxLinkTrainingRequest[2 * ucLoopIndex] = 0x02;
#else
                pucDpAuxLinkTrainingRequest[2 * ucLoopIndex] = (pucDpAuxLinkTrainingLevel[2 * ucLoopIndex] & (_BIT1 | _BIT0)) + 0x01;
#endif
            }
            else
            {
                pucDpAuxLinkTrainingRequest[2 * ucLoopIndex] = 0x03;
            }

            if((pucDpAuxLinkTrainingLevel[(2 * ucLoopIndex) + 1] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpAuxLinkTrainingRequest[(2 * ucLoopIndex) + 1] = 0x20;
#else
                pucDpAuxLinkTrainingRequest[(2 * ucLoopIndex) + 1] = ((pucDpAuxLinkTrainingLevel[(2 * ucLoopIndex) + 1] << 4) & (_BIT5 | _BIT4)) + 0x10;
#endif
            }
            else
            {
                pucDpAuxLinkTrainingRequest[(2 * ucLoopIndex) + 1] = 0x30;
            }
        }

        g_ucDpAuxRx2LinkRequest01 = (pucDpAuxLinkTrainingLevel[0] & 0x03) | ((pucDpAuxLinkTrainingLevel[1] << 4) & 0x30);
        g_ucDpAuxRx2LinkRequest23 = (pucDpAuxLinkTrainingLevel[2] & 0x03) | ((pucDpAuxLinkTrainingLevel[3] << 4) & 0x30);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                if(g_enumDpAuxRx2LinkRate >= _DP_LINK_HBR2)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    }
                }
                else
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    }
                }

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))))
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x01);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(g_enumDpAuxRx2LinkRate >= _DP_LINK_HBR2)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                    }
                }
                else
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                    }
                }

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0))))) &&
                   (((pucDpAuxLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))))
                {
                    if(((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7) &&
                        ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x22, 0x02) & 0x1F) == _DP_ONE_LANE)) ||
                       ((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == 0x00) &&
                        ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x00, 0x02) & 0x1F) == _DP_ONE_LANE)))
                    {
                        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                    }
                    else
                    {
                        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                        return _TRUE;
                    }
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(g_enumDpAuxRx2LinkRate >= _DP_LINK_HBR2)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < ucTP1HBR2HBR3SwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
                    }
                }
                else
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xFC) | pucDpAuxLinkTrainingRequest[0]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 & 0xCF) | pucDpAuxLinkTrainingRequest[1]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xFC) | pucDpAuxLinkTrainingRequest[2]);
                    }

                    if(((pucDpAuxLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < ucTP1RBRHBRSwingLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 & 0xCF) | pucDpAuxLinkTrainingRequest[3]);
                    }
                }

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

                if((((pucDpAuxLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))) &&
                   (((pucDpAuxLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))) &&
                   (((pucDpAuxLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) == ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT1 | _BIT0)))) &&
                   (((pucDpAuxLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) == (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT5 | _BIT4)) >> 4))))
                {
                    if(((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7) &&
                        ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x22, 0x02) & 0x1F) == _DP_ONE_LANE)) ||
                       ((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == 0x00) &&
                        ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x00, 0x02) & 0x1F) == _DP_ONE_LANE)))
                    {
                        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                    }
                    else if(((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7) &&
                             ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x22, 0x02) & 0x1F) == _DP_TWO_LANE)) ||
                            ((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == 0x00) &&
                             ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x00, 0x02) & 0x1F) == _DP_TWO_LANE)))
                    {
                        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                    }
                    else
                    {
                        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                        return _TRUE;
                    }
                }

                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp2Check_8b10b_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucTp2DecodeCheck = 0;
    BYTE ucLEThresholdTP2 = 31;
    BYTE pucDpAuxLinkTrainingLevel[4];
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    // variable values may vary for experimental purposes and should not be treated as constants.
    // coverity[assignment]
    BYTE ucTP2RBRHBRPreemphasisLevel = 0;

    // coverity[assignment]
    BYTE ucTP2HBR2HBR3PreemphasisLevel = (_D2_DP_REDRIVER_TYPE == _REDRIVER_NONE) ? 0 : 1;

    if(enumDpLtType == _DP_NORMAL_LT)
    {
#if(_DP_LT_TP2_FORCE_MARGINAL_LINK == _ON)

        SET_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
        SET_DP_RX_D2_LANE1_MARGIN_LINK_TP2();
        SET_DP_RX_D2_LANE2_MARGIN_LINK_TP2();
        SET_DP_RX_D2_LANE3_MARGIN_LINK_TP2();
#else

        CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
        CLR_DP_RX_D2_LANE1_MARGIN_LINK_TP2();
        CLR_DP_RX_D2_LANE2_MARGIN_LINK_TP2();
        CLR_DP_RX_D2_LANE3_MARGIN_LINK_TP2();
#endif

        ucTp2DecodeCheck = ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_0);

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
        if((g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_2) ||
           (g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3))
        {
            if((ucTp2DecodeCheck & 0x01) == 0x01)
            {
                if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0)
                {
                    ucEQCRCStatus |= _BIT0;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0)
                {
                    ucEQCRCStatus |= _BIT1;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE0)
                {
                    ucEQCRCStatus |= _BIT2;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE0)
                {
                    ucEQCRCStatus |= _BIT3;
                }
            }

            if((ucTp2DecodeCheck & 0x02) == 0x02)
            {
                if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1)
                {
                    ucEQCRCStatus |= _BIT0;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1)
                {
                    ucEQCRCStatus |= _BIT1;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE1)
                {
                    ucEQCRCStatus |= _BIT2;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE1)
                {
                    ucEQCRCStatus |= _BIT3;
                }
            }

            if((ucTp2DecodeCheck & 0x04) == 0x04)
            {
                if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2)
                {
                    ucEQCRCStatus |= _BIT0;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2)
                {
                    ucEQCRCStatus |= _BIT1;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE2)
                {
                    ucEQCRCStatus |= _BIT2;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE2)
                {
                    ucEQCRCStatus |= _BIT3;
                }
            }

            if((ucTp2DecodeCheck & 0x08) == 0x08)
            {
                if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3)
                {
                    ucEQCRCStatus |= _BIT0;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3)
                {
                    ucEQCRCStatus |= _BIT1;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE3)
                {
                    ucEQCRCStatus |= _BIT2;
                }
                else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE3)
                {
                    ucEQCRCStatus |= _BIT3;
                }
            }
        }
        else
#endif
        {
            ucEQCRCStatus = ucTp2DecodeCheck;
        }

        pucDpAuxLinkTrainingLevel[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpAuxLinkTrainingLevel[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpAuxLinkTrainingLevel[2] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpAuxLinkTrainingLevel[3] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        g_ucDpAuxRx2LinkRequest01 = ((pucDpAuxLinkTrainingLevel[0] & 0x03) |
                                     ((pucDpAuxLinkTrainingLevel[0] >> 1) & 0x0C) |
                                     ((pucDpAuxLinkTrainingLevel[1] << 4) & 0x30) |
                                     ((pucDpAuxLinkTrainingLevel[1] << 3) & 0xC0));

        g_ucDpAuxRx2LinkRequest23 = ((pucDpAuxLinkTrainingLevel[2] & 0x03) |
                                     ((pucDpAuxLinkTrainingLevel[2] >> 1) & 0x0C) |
                                     ((pucDpAuxLinkTrainingLevel[3] << 4) & 0x30) |
                                     ((pucDpAuxLinkTrainingLevel[3] << 3) & 0xC0));

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_FOUR_LANE:

                // reset LinkStatus CR state
                g_ucDpAuxRx2LinkStatus01 = 0x11;
                g_ucDpAuxRx2LinkStatus23 = 0x11;

                // Lane3 EQ-CRC Check
                if((ucEQCRCStatus & _BIT3) == _BIT3)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x70;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[3] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE3_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x40;
                            CLR_DP_RX_D2_LANE3_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x70;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[3] & _BIT5) != _BIT5) &&
                        ((((g_ucDpAuxRx2LinkRequest23 >> 4) & 0x03) + ((g_ucDpAuxRx2LinkRequest23 >> 6) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x40;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[3] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[3] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[3] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[3] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest23 = (0x30 | (g_ucDpAuxRx2LinkRequest23 & 0x0F));
                            g_pucDpAuxRx2MaxSwing[3] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[3] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[3] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest23 = (0x60 | (g_ucDpAuxRx2LinkRequest23 & 0x0F));
                            g_pucDpAuxRx2MaxSwing[3] = 0xFF;
                        }
                    }
                }
#endif
                // Lane2 EQ-CRC Check
                if((ucEQCRCStatus & _BIT2) == _BIT2)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x07;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[2] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE2_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x04;
                            CLR_DP_RX_D2_LANE2_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x07;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[2] & _BIT5) != _BIT5) &&
                        (((g_ucDpAuxRx2LinkRequest23 & 0x03) + ((g_ucDpAuxRx2LinkRequest23 >> 2) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x04;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[2] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[2] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[2] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[2] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest23 = (0x03 | (g_ucDpAuxRx2LinkRequest23 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[2] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[2] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[2] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest23 = (0x06 | (g_ucDpAuxRx2LinkRequest23 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[2] = 0xFF;
                        }
                    }
                }
#endif
                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[1] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE1_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                            CLR_DP_RX_D2_LANE1_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) &&
                        ((((g_ucDpAuxRx2LinkRequest01 >> 4) & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 6) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[1] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[1] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[1] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x30 | (g_ucDpAuxRx2LinkRequest01 & 0x0F));
                            g_pucDpAuxRx2MaxSwing[1] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[1] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x60 | (g_ucDpAuxRx2LinkRequest01 & 0x0F));
                            g_pucDpAuxRx2MaxSwing[1] = 0xFF;
                        }
                    }
                }
#endif
                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE0_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                            CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) &&
                        (((g_ucDpAuxRx2LinkRequest01 & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 2) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[0] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[0] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x03 | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[0] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x06 | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[0] = 0xFF;
                        }
                    }
                }
#endif

#if(_DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL == _ON)
                if(((g_ucDpAuxRx2LinkStatus01 & 0x77) != 0x77) || ((g_ucDpAuxRx2LinkStatus23 & 0x77) != 0x77))
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) &&
                       (((pucDpAuxLinkTrainingLevel[0] & 0x03) + ((pucDpAuxLinkTrainingLevel[0] >> 3) & 0x03)) < 3))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((pucDpAuxLinkTrainingLevel[0] & 0x03) |
                                                     (((pucDpAuxLinkTrainingLevel[0] >> 1) & 0x0C) + 0x04) |
                                                     ((pucDpAuxLinkTrainingLevel[1] << 4) & 0x30) |
                                                     (((pucDpAuxLinkTrainingLevel[1] << 3) & 0xC0) + 0x40));

                        g_ucDpAuxRx2LinkRequest23 = ((pucDpAuxLinkTrainingLevel[2] & 0x03) |
                                                     (((pucDpAuxLinkTrainingLevel[2] >> 1) & 0x0C) + 0x04) |
                                                     ((pucDpAuxLinkTrainingLevel[3] << 4) & 0x30) |
                                                     (((pucDpAuxLinkTrainingLevel[3] << 3) & 0xC0) + 0x40));
                    }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                    else
                    {
                        if(g_pucDpAuxRx2MaxSwing[0] == 0xFF)
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 << 4) | (g_ucDpAuxRx2LinkRequest01 & 0x0F));
                            g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest01;
                        }
                        else if(g_pucDpAuxRx2MaxSwing[1] == 0xFF)
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 >> 4) | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest01;
                        }
                        else if(g_pucDpAuxRx2MaxSwing[2] == 0xFF)
                        {
                            g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 << 4) | (g_ucDpAuxRx2LinkRequest23 & 0x0F));
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest23;
                        }
                        else if(g_pucDpAuxRx2MaxSwing[3] == 0xFF)
                        {
                            g_ucDpAuxRx2LinkRequest23 = ((g_ucDpAuxRx2LinkRequest23 >> 4) | (g_ucDpAuxRx2LinkRequest23 & 0xF0));
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest23;
                        }
                    }
#endif
                }
#endif
                break;

            case _DP_TWO_LANE:

                // reset LinkStatus CR state
                g_ucDpAuxRx2LinkStatus01 = 0x11;
                g_ucDpAuxRx2LinkStatus23 = 0x00;

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[1] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE1_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                            CLR_DP_RX_D2_LANE1_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) &&
                        ((((g_ucDpAuxRx2LinkRequest01 >> 4) & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 6) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[1] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[1] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[1] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x30 | (g_ucDpAuxRx2LinkRequest01 & 0x0F));
                            g_pucDpAuxRx2MaxSwing[1] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[1] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x60 | (g_ucDpAuxRx2LinkRequest01 & 0x0F));
                            g_pucDpAuxRx2MaxSwing[1] = 0xFF;
                        }
                    }
                }
#endif
                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE0_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                            CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) &&
                        (((g_ucDpAuxRx2LinkRequest01 & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 2) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[0] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[0] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x03 | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[0] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x06 | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[0] = 0xFF;
                        }
                    }
                }
#endif

#if(_DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL == _ON)
                if((g_ucDpAuxRx2LinkStatus01 & 0x77) != 0x77)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) &&
                       (((pucDpAuxLinkTrainingLevel[0] & 0x03) + ((pucDpAuxLinkTrainingLevel[0] >> 3) & 0x03)) < 3))
                    {
                        g_ucDpAuxRx2LinkRequest01 = ((pucDpAuxLinkTrainingLevel[0] & 0x03) |
                                                     (((pucDpAuxLinkTrainingLevel[0] >> 1) & 0x0C) + 0x04) |
                                                     ((pucDpAuxLinkTrainingLevel[1] << 4) & 0x30) |
                                                     (((pucDpAuxLinkTrainingLevel[1] << 3) & 0xC0) + 0x40));
                    }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                    else
                    {
                        if(g_pucDpAuxRx2MaxSwing[0] == 0xFF)
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 << 4) | (g_ucDpAuxRx2LinkRequest01 & 0x0F));
                        }
                        else if(g_pucDpAuxRx2MaxSwing[1] == 0xFF)
                        {
                            g_ucDpAuxRx2LinkRequest01 = ((g_ucDpAuxRx2LinkRequest01 >> 4) | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                        }
                    }
#endif
                }
#endif
                break;

            case _DP_ONE_LANE:
            default:

                // reset LinkStatus CR state
                g_ucDpAuxRx2LinkStatus01 = 0x01;
                g_ucDpAuxRx2LinkStatus23 = 0x00;

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_enumDpAuxRx2LinkRate <= _DP_LINK_HBR)
                    {
                        g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                    }
                    else
                    {
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT5 | _BIT4 | _BIT3)) == 0x00) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < 3) &&
                           ((ScalerDpPhyRxGetTp2LE_EXINT0(enumInputPort, ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0)) > ucLEThresholdTP2) || (GET_DP_RX_D2_LANE0_MARGIN_LINK_TP2() == _TRUE)))
                        {
                            g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                            CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
                        }
                        else
                        {
                            g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                        }
                    }
                }
                else if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) &&
                        (((g_ucDpAuxRx2LinkRequest01 & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 2) & 0x03)) < 3))
                {
                    g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                }
#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
                else
                {
                    if(g_pucDpAuxRx2MaxSwing[0] != 0xFF)
                    {
                        // S2P1 -> S3P0
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) == _BIT3) &&
                           (g_pucDpAuxRx2MaxSwing[0] == 3))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x03 | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[0] = 0xFF;
                        }

                        // S3P0 -> S2P1
                        if(((pucDpAuxLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) &&
                           ((pucDpAuxLinkTrainingLevel[0] & (_BIT5 | _BIT4 | _BIT3)) == 0x00))
                        {
                            g_ucDpAuxRx2LinkRequest01 = (0x06 | (g_ucDpAuxRx2LinkRequest01 & 0xF0));
                            g_pucDpAuxRx2MaxSwing[0] = 0xFF;
                        }
                    }
                }
#endif
                break;
        }

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & 0x07) == 0x07)
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & 0x77) == 0x77)
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpAuxRx2LinkStatus01 & 0x77) == 0x77) && (((g_ucDpAuxRx2LinkStatus23 & 0x77) == 0x77)))
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        pucDpAuxLinkTrainingLevel[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpAuxLinkTrainingLevel[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpAuxLinkTrainingLevel[2] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpAuxLinkTrainingLevel[3] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        g_ucDpAuxRx2LinkRequest01 = ((pucDpAuxLinkTrainingLevel[0] & 0x03) |
                                     ((pucDpAuxLinkTrainingLevel[0] >> 1) & 0x0C) |
                                     ((pucDpAuxLinkTrainingLevel[1] << 4) & 0x30) |
                                     ((pucDpAuxLinkTrainingLevel[1] << 3) & 0xC0));

        g_ucDpAuxRx2LinkRequest23 = ((pucDpAuxLinkTrainingLevel[2] & 0x03) |
                                     ((pucDpAuxLinkTrainingLevel[2] >> 1) & 0x0C) |
                                     ((pucDpAuxLinkTrainingLevel[3] << 4) & 0x30) |
                                     ((pucDpAuxLinkTrainingLevel[3] << 3) & 0xC0));

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(g_enumDpAuxRx2LinkRate >= _DP_LINK_HBR2)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                    }
                }
                else
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                    }
                }

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x06, (_BIT3 | _BIT2)) << 1)))
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x07);
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(g_enumDpAuxRx2LinkRate >= _DP_LINK_HBR2)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                    }
                }
                else
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                    }
                }

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pucDpAuxLinkTrainingLevel[0] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x06, (_BIT3 | _BIT2)) << 1))) &&
                   (((pucDpAuxLinkTrainingLevel[1] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x06, (_BIT7 | _BIT6)) >> 3))))
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                if(g_enumDpAuxRx2LinkRate >= _DP_LINK_HBR2)
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                    }

                    if(((pucDpAuxLinkTrainingLevel[2] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[2] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x04;
                    }

                    if(((pucDpAuxLinkTrainingLevel[3] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[3] & (_BIT4 | _BIT3)) >> 3) < ucTP2HBR2HBR3PreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x40;
                    }
                }
                else
                {
                    if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
                    }

                    if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
                    }

                    if(((pucDpAuxLinkTrainingLevel[2] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[2] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x04;
                    }

                    if(((pucDpAuxLinkTrainingLevel[3] & _BIT5) != _BIT5) && (((pucDpAuxLinkTrainingLevel[3] & (_BIT4 | _BIT3)) >> 3) < ucTP2RBRHBRPreemphasisLevel))
                    {
                        g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x40;
                    }
                }

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

                if((((pucDpAuxLinkTrainingLevel[0] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[0] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x06, (_BIT3 | _BIT2)) << 1))) &&
                   (((pucDpAuxLinkTrainingLevel[1] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[1] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x06, (_BIT7 | _BIT6)) >> 3))) &&
                   (((pucDpAuxLinkTrainingLevel[2] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[2] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x07, (_BIT3 | _BIT2)) << 1))) &&
                   (((pucDpAuxLinkTrainingLevel[3] & _BIT5) == _BIT5) || ((pucDpAuxLinkTrainingLevel[3] & (_BIT4 | _BIT3)) == (BYTE)(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x07, (_BIT7 | _BIT6)) >> 3))))
                {
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x77);
                    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2PhyCtsTp2Check_8b10b_EXINT0(void)
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucTp2DecodeCheck = 0;
    BYTE pucDpAuxLinkTrainingLevel[4];
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

#if(_DP_LT_TP2_FORCE_MARGINAL_LINK == _ON)

    SET_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
    SET_DP_RX_D2_LANE1_MARGIN_LINK_TP2();
    SET_DP_RX_D2_LANE2_MARGIN_LINK_TP2();
    SET_DP_RX_D2_LANE3_MARGIN_LINK_TP2();
#else

    CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP2();
    CLR_DP_RX_D2_LANE1_MARGIN_LINK_TP2();
    CLR_DP_RX_D2_LANE2_MARGIN_LINK_TP2();
    CLR_DP_RX_D2_LANE3_MARGIN_LINK_TP2();
#endif

    ucTp2DecodeCheck = ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_0);

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
    if((g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_2) ||
       (g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3))
    {
        if((ucTp2DecodeCheck & 0x01) == 0x01)
        {
            if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0)
            {
                ucEQCRCStatus |= _BIT0;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0)
            {
                ucEQCRCStatus |= _BIT1;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE0)
            {
                ucEQCRCStatus |= _BIT2;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE0)
            {
                ucEQCRCStatus |= _BIT3;
            }
        }

        if((ucTp2DecodeCheck & 0x02) == 0x02)
        {
            if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1)
            {
                ucEQCRCStatus |= _BIT0;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1)
            {
                ucEQCRCStatus |= _BIT1;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE1)
            {
                ucEQCRCStatus |= _BIT2;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE1)
            {
                ucEQCRCStatus |= _BIT3;
            }
        }

        if((ucTp2DecodeCheck & 0x04) == 0x04)
        {
            if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2)
            {
                ucEQCRCStatus |= _BIT0;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2)
            {
                ucEQCRCStatus |= _BIT1;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE2)
            {
                ucEQCRCStatus |= _BIT2;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE2)
            {
                ucEQCRCStatus |= _BIT3;
            }
        }

        if((ucTp2DecodeCheck & 0x08) == 0x08)
        {
            if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3)
            {
                ucEQCRCStatus |= _BIT0;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3)
            {
                ucEQCRCStatus |= _BIT1;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) == _DP_SCALER_LANE3)
            {
                ucEQCRCStatus |= _BIT2;
            }
            else if(ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) == _DP_SCALER_LANE3)
            {
                ucEQCRCStatus |= _BIT3;
            }
        }
    }
    else
#endif
    {
        ucEQCRCStatus = ucTp2DecodeCheck;
    }

    pucDpAuxLinkTrainingLevel[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
    pucDpAuxLinkTrainingLevel[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
    pucDpAuxLinkTrainingLevel[2] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
    pucDpAuxLinkTrainingLevel[3] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    g_ucDpAuxRx2LinkRequest01 = ((pucDpAuxLinkTrainingLevel[0] & 0x03) |
                                 ((pucDpAuxLinkTrainingLevel[0] >> 1) & 0x0C) |
                                 ((pucDpAuxLinkTrainingLevel[1] << 4) & 0x30) |
                                 ((pucDpAuxLinkTrainingLevel[1] << 3) & 0xC0));

    g_ucDpAuxRx2LinkRequest23 = ((pucDpAuxLinkTrainingLevel[2] & 0x03) |
                                 ((pucDpAuxLinkTrainingLevel[2] >> 1) & 0x0C) |
                                 ((pucDpAuxLinkTrainingLevel[3] << 4) & 0x30) |
                                 ((pucDpAuxLinkTrainingLevel[3] << 3) & 0xC0));

    // Source Lane
    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case 0x00:

            // Lane0 EQ-CRC Check
            if((ucEQCRCStatus & _BIT0) == _BIT0)
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x77;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x77;
            }
            else if(((pucDpAuxLinkTrainingLevel[0] & _BIT5) != _BIT5) &&
                    (((g_ucDpAuxRx2LinkRequest01 & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 2) & 0x03)) < 3))
            {
                g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x04;
            }

            break;

        case _BIT4:

            // Lane1 EQ-CRC Check
            if((ucEQCRCStatus & _BIT1) == _BIT1)
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x77;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x77;
            }
            else if(((pucDpAuxLinkTrainingLevel[1] & _BIT5) != _BIT5) &&
                    ((((g_ucDpAuxRx2LinkRequest01 >> 4) & 0x03) + ((g_ucDpAuxRx2LinkRequest01 >> 6) & 0x03)) < 3))
            {
                g_ucDpAuxRx2LinkRequest01 = g_ucDpAuxRx2LinkRequest01 + 0x40;
            }

            break;

        case _BIT5:

            // Lane2 EQ-CRC Check
            if((ucEQCRCStatus & _BIT2) == _BIT2)
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x77;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x77;
            }
            else if(((pucDpAuxLinkTrainingLevel[2] & _BIT5) != _BIT5) &&
                    (((g_ucDpAuxRx2LinkRequest23 & 0x03) + ((g_ucDpAuxRx2LinkRequest23 >> 2) & 0x03)) < 3))
            {
                g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x04;
            }

            break;

        case (_BIT5 | _BIT4):

            // Lane3 EQ-CRC Check
            if((ucEQCRCStatus & _BIT3) == _BIT3)
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x77;
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x77;
            }
            else if(((pucDpAuxLinkTrainingLevel[3] & _BIT5) != _BIT5) &&
                    ((((g_ucDpAuxRx2LinkRequest23 >> 4) & 0x03) + ((g_ucDpAuxRx2LinkRequest23 >> 6) & 0x03)) < 3))
            {
                g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest23 + 0x40;
            }

            break;

        default:
            break;
    }

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

    // Source Lane
    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case 0x00:

            if((g_ucDpAuxRx2LinkStatus01 & 0x07) == 0x07)
            {
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                return _TRUE;
            }

            break;

        case _BIT4:

            if((g_ucDpAuxRx2LinkStatus01 & 0x70) == 0x70)
            {
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                return _TRUE;
            }

            break;

        case _BIT5:

            if((g_ucDpAuxRx2LinkStatus23 & 0x07) == 0x07)
            {
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                return _TRUE;
            }

            break;

        case (_BIT5 | _BIT4):

            if((g_ucDpAuxRx2LinkStatus23 & 0x70) == 0x70)
            {
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                return _TRUE;
            }

            break;

        default:
            break;
    }

    return _FALSE;
}

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp1Check_128b132b_EXINT0(void)
{
    // reset Preset level
    g_ucDpAuxRx2PreferPreset = 0;

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(0x00, 0x20, 0x0B, 0x00);
#endif

    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) && (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
    {
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x03, 0x00);
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x04, 0x00);
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x05, 0x00);
        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x06, 0x00);
    }

    switch(g_enumDpAuxRx2LaneCount)
    {
        case _DP_ONE_LANE:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x01);

            return _TRUE;

        case _DP_TWO_LANE:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);

            return _TRUE;

        case _DP_FOUR_LANE:
        default:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, 0x00);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x11);
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x11);

            return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2Tp2Check_128b132b_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    BYTE ucEQCRCStatus = 0;
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_0) == _TRUE)
        {
            ucEQCRCStatus |= _BIT0;
        }

        if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_1) == _TRUE)
        {
            ucEQCRCStatus |= _BIT1;
        }

        if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_2) == _TRUE)
        {
            ucEQCRCStatus |= _BIT2;
        }

        if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_3) == _TRUE)
        {
            ucEQCRCStatus |= _BIT3;
        }

        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_FOUR_LANE:

                g_ucDpAuxRx2LinkStatus01 = 0x11;
                g_ucDpAuxRx2LinkStatus23 = 0x11;

                // Lane3 EQ-CRC Check
                if((ucEQCRCStatus & _BIT3) == _BIT3)
                {
                    g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x70;
                }

                // Lane2 EQ-CRC Check
                if((ucEQCRCStatus & _BIT2) == _BIT2)
                {
                    g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x07;
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                }

                break;

            case _DP_TWO_LANE:

                g_ucDpAuxRx2LinkStatus01 = 0x11;
                g_ucDpAuxRx2LinkStatus23 = 0x00;

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                }

                break;

            case _DP_ONE_LANE:
            default:

                g_ucDpAuxRx2LinkStatus01 = 0x01;
                g_ucDpAuxRx2LinkStatus23 = 0x00;

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
                }

                break;
        }

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & 0x07) == 0x07)
                {
                    if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                    {
                        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                    }
                    else
                    {
                        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                    }

                    return _TRUE;
                }
                else
                {
                    g_ucDpAuxRx2PreferPreset++;
                    g_ucDpAuxRx2LinkRequest01 = tDpPhyRxDP2PresetSelTable[g_ucDpAuxRx2PreferPreset & 0x0F];
                    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpAuxRx2LinkStatus01 & 0x77) == 0x77)
                {
                    if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                    {
                        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                    }
                    else
                    {
                        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                    }

                    return _TRUE;
                }
                else
                {
                    g_ucDpAuxRx2PreferPreset++;
                    g_ucDpAuxRx2LinkRequest01 = (tDpPhyRxDP2PresetSelTable[g_ucDpAuxRx2PreferPreset & 0x0F] << 4) | (tDpPhyRxDP2PresetSelTable[g_ucDpAuxRx2PreferPreset & 0x0F]);
                    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                }


                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpAuxRx2LinkStatus01 & 0x77) == 0x77) && (((g_ucDpAuxRx2LinkStatus23 & 0x77) == 0x77)))
                {
                    if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                    {
                        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                    }
                    else
                    {
                        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                    }

                    return _TRUE;
                }
                else
                {
                    g_ucDpAuxRx2PreferPreset++;
                    g_ucDpAuxRx2LinkRequest01 = (tDpPhyRxDP2PresetSelTable[g_ucDpAuxRx2PreferPreset & 0x0F] << 4) | (tDpPhyRxDP2PresetSelTable[g_ucDpAuxRx2PreferPreset & 0x0F]);
                    g_ucDpAuxRx2LinkRequest23 = g_ucDpAuxRx2LinkRequest01;
                    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);
                }


                break;
        }
    }
    else
    {
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        g_ucDpAuxRx2LinkRequest01 = 0x55;
        g_ucDpAuxRx2LinkRequest23 = 0x55;

        switch(g_enumDpAuxRx2LaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x07);

                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;

                break;

            case _DP_TWO_LANE:

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x77);

                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;

                break;

            case _DP_FOUR_LANE:
            default:

                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpAuxRx2LinkRequest01);
                ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpAuxRx2LinkRequest23);

                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x77);

                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;

                break;
        }
    }

    if(g_ucDpAuxRx2PreferPreset >= 20)
    {
        g_ucDpAuxRx2PreferPreset = 0;
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x06, 0x00);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);
        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT4));
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpAuxRx2PhyCtsTp2Check_128b132b_EXINT0(void)
{
    BYTE ucEQCRCStatus = 0;
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_0) == _TRUE)
    {
        ucEQCRCStatus |= _BIT0;
    }

    if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_1) == _TRUE)
    {
        ucEQCRCStatus |= _BIT1;
    }

    if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_2) == _TRUE)
    {
        ucEQCRCStatus |= _BIT2;
    }

    if(ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(enumInputPort, _DP_LANE_3) == _TRUE)
    {
        ucEQCRCStatus |= _BIT3;
    }

    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

    // Source Lane
    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case 0x30: // Lane3 Test

            // Lane3 EQ-CRC Check
            if((ucEQCRCStatus & _BIT3) == _BIT3)
            {
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x70;
            }

            break;

        case 0x20: // Lane2 Test

            // Lane2 EQ-CRC Check
            if((ucEQCRCStatus & _BIT2) == _BIT2)
            {
                g_ucDpAuxRx2LinkStatus23 = g_ucDpAuxRx2LinkStatus23 | 0x07;
            }

            break;

        case 0x10: // Lane1 Test

            // Lane1 EQ-CRC Check
            if((ucEQCRCStatus & _BIT1) == _BIT1)
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x70;
            }

            break;

        default:
        case 0x00: // Lane0 Test

            // Lane0 EQ-CRC Check
            if((ucEQCRCStatus & _BIT0) == _BIT0)
            {
                g_ucDpAuxRx2LinkStatus01 = g_ucDpAuxRx2LinkStatus01 | 0x07;
            }

            break;
    }

    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, g_ucDpAuxRx2LinkStatus01);
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, g_ucDpAuxRx2LinkStatus23);

    switch(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
    {
        case 0x30: // Lane3 Test

            if((g_ucDpAuxRx2LinkStatus23 & 0x70) == 0x70)
            {
                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;
            }

            break;

        case 0x20: // Lane2 Test

            if((g_ucDpAuxRx2LinkStatus23 & 0x07) == 0x07)
            {
                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;
            }

            break;

        case 0x10: // Lane1 Test

            if((g_ucDpAuxRx2LinkStatus01 & 0x70) == 0x70)
            {
                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;
            }

            break;

        default:
        case 0x00: // Lane0 Test

            if((g_ucDpAuxRx2LinkStatus01 & 0x07) == 0x07)
            {
                if(g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_3)
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT0));
                }
                else
                {
                    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT0));
                }

                return _TRUE;
            }

            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP Sink Status Setting in EXINT
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT1));
        }
        else if(enumReceiverPort == _DP_STREAM_REGENERATION_STATUS)
        {
            // Set Stream is Being Regenerated
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT2));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT1));
        }
        else if(enumReceiverPort == _DP_STREAM_REGENERATION_STATUS)
        {
            // Set Stream is Not Being Regenerated
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT2));
        }
    }
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetManualMode_EXINT0(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucLoopIndexInAuxMacro = 0;

    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 45)
            {
                break;
            }
        }while(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9);
    }

    // If aux state is xmit_st, wait 5us to handle request data
    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) == _BIT9)
    {
        DELAY_5US_EXINT();
    }

    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT17, 0x00);
#else
    BYTE ucLoopIndexInAuxMacro = 0;

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 100)
            {
                break;
            }
        }while(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8);
    }

    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT17, 0x00);

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetAutoMode_EXINT0(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucLoopIndexInAuxMacro = 0;

    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 45)
            {
                break;
            }
        }while(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) > _BIT9);

        DELAY_5US_EXINT();
    }

    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_MAC_CTRL, ~(_BIT20 | _BIT17), _BIT17);
#else
    BYTE ucLoopIndexInAuxMacro = 0;

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8)
    {
        do
        {
            DELAY_5US_EXINT();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 100)
            {
                break;
            }
        }while(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) != _BIT8);
    }

    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_MAC_CTRL, ~(_BIT20 | _BIT17), _BIT17);

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Addr
// Input Value  : ulDpcdAddr
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(DWORD ulDpcdAddr)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

    // Set Dpcd Addr
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT, ulDpcdAddr);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT2);

    while((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT2) == _BIT2) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Addr
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT, ulDpcdAddr);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Data
// Input Value  : usDpcdData
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(BYTE ucDpcdData)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess = Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _DP_AUX_RX_DPCD_ACCESS_ALL);

    // Avoid Hw Bug
    ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_ALL);

    // Set Dpcd Data Value = Original Data and Set _BITX
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & 0xFF00) | ucDpcdData));
#else
    // Set Dpcd Data Value
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, ucDpcdData);
#endif

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT0);

    while((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT0) == _BIT0) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore Original Setting
    ScalerDpAuxRx2AccessSelect_EXINT0(enumDpAuxRxDpcdAccess);
#endif
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Data Value
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, ucDpcdData);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Data
// Input Value  : usDpcdData
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(WORD usNotDpcdBit, WORD usDpcdBit)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    bit bAutoIncBackUp = (Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3);
#else
    bit bAutoIncBackUp = (Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT, _BIT20) == _BIT20);
#endif

    if(bAutoIncBackUp == _TRUE)
    {
        // Disable Dpcd Auto Inc
        ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(_DISABLE);
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess = Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _DP_AUX_RX_DPCD_ACCESS_ALL);

    // Avoid Hw Bug
    ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_ALL);
#endif

    // Set Dpcd Data Value = Original Data and Set _BITX
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & usNotDpcdBit) | usDpcdBit));

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT0);

    while((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT0) == _BIT0) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore Original Setting
    ScalerDpAuxRx2AccessSelect_EXINT0(enumDpAuxRxDpcdAccess);
#endif
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Data Value = Original Data and Set _BITX
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & usNotDpcdBit) | usDpcdBit));
#endif

    if(bAutoIncBackUp == _TRUE)
    {
        // Enable Dpcd Auto Inc
        ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Get Dpcd Access Data
// Input Value  : none
// Output Value : usDpcdData
//--------------------------------------------------
WORD ScalerDpAuxRx2GetDpcdAccessData_EXINT0(void)
{
    ScalerMcuDelayDot2usPN();

    // Get Dpcd Data
    return Scaler32GetWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_OUTPUT_PORT, 0x00);
}

//--------------------------------------------------
// Description  : DP Aux Auto Inc Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(bit bEnable)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, ~_BIT3, (bEnable << 3));
#else
    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT, ~_BIT20, (bEnable << 20));
#endif
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRx2GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif

    return (BYTE)(ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & _BIT(7, 0));
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif

    return (BYTE)(ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & ucDpcdBit);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    // Set Dpcd Data
    ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(ucDpcdValue);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Set Manual Mode For R/W Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data
    ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(ucDpcdValue);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Set Auto Mode For W1C Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data
    ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(ucDpcdValue);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0((WORD)ulNotDpcdBit, ucDpcdBit);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Set Manual Mode For R/W Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0((WORD)ulNotDpcdBit, ucDpcdBit);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Set Auto Mode For W1C Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0((WORD)ulNotDpcdBit, ucDpcdBit);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    DWORD ulDpcdAddrMirror = ScalerDpAuxRxDpcdGetMirrorAddr_EXINT0((ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    BYTE ucDpcdAddrMirrorH = (ulDpcdAddrMirror >> 16) & 0x0F;
    BYTE ucDpcdAddrMirrorM = (ulDpcdAddrMirror >> 8) & 0xFF;
    BYTE ucDpcdAddrMirrorL = ulDpcdAddrMirror & 0xFF;
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Set Manual Mode to Protect Mirror Addr Mismatch
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    // Set Target Dpcd Addr
    ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

    if(ulDpcdAddrMirror != 0xFFFFFFFF)
    {
        // Set Mirror Dpcd Addr
        ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAddrMirrorH, ucDpcdAddrMirrorM, ucDpcdAddrMirrorL, ucDpcdValue);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#else
    ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdMirrorWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    DWORD ulDpcdAddrMirror = ScalerDpAuxRxDpcdGetMirrorAddr_EXINT0((ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    BYTE ucDpcdAddrMirrorH = (ulDpcdAddrMirror >> 16) & 0x0F;
    BYTE ucDpcdAddrMirrorM = (ulDpcdAddrMirror >> 8) & 0xFF;
    BYTE ucDpcdAddrMirrorL = ulDpcdAddrMirror & 0xFF;
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Set Manual Mode to Protect Mirror Addr Mismatch
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    // Set Target Dpcd Addr
    ScalerDpAuxRx2SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

    if(ulDpcdAddrMirror != 0xFFFFFFFF)
    {
        // Set Mirror Dpcd Addr
        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(ucDpcdAddrMirrorH, ucDpcdAddrMirrorM, ucDpcdAddrMirrorL, ulNotDpcdBit, ucDpcdBit);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#else
    ScalerDpAuxRx2SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdMirrorBitWriteValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    ScalerDpAuxRx2SetDpcdBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Group Reset
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucLen             --> Group Len
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdGroupReset_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    bit bAutoIncBackUp = (Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3);

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(ulDpcdAddr);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    if(bAutoIncBackUp == _FALSE)
    {
        // Enable Dpcd Auto Inc
        ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(_ENABLE);
    }

    while(usLen > 0)
    {
        // Reset Dpcd
        ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(0x00);

        usLen--;
    }

    if(bAutoIncBackUp == _FALSE)
    {
        // Disable Dpcd Auto Inc
        ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(_DISABLE);
    }
#else
    while(usLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(ulDpcdAddr);

        // Reset Dpcd
        ScalerDpAuxRx2SetDpcdAccessByteData_EXINT0(0x00);

        usLen--;
        ulDpcdAddr++;
    }
#endif

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
}

//--------------------------------------------------
// Description  : Set DPCD Link Status Force Defer
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdForceDeferEnable_EXINT0(0x00, 0x02, 0x04, 1, bEnable);
    ScalerDpAuxRx2SetDpcdForceDeferEnable_EXINT0(0x00, 0x20, 0x0E, 1, bEnable);
#else
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT6, (bEnable << 6));
#endif
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Mac Access Select For New Mac
// Input Value  : enumInputPort, enumDpAuxRxDpcdAccess
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2AccessSelect_EXINT0(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    Scaler32SetBit_EXINT0(PB1A006_68_AUX_DPCD_ACCESS_CONTROL, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), enumDpAuxRxDpcdAccess);
#else
    Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT, ~(_BIT(23, 22)), enumDpAuxRxDpcdAccess);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Config in INT0
// Input Value  : ucDpcdAccessPortH   --> High Byte of DPCD Address
//                ucDpcdAccessPortM   --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL   --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig --> Attr : R / RW / Write Block
//                ucDpcdLen           --> Setting N = Len + 1 Dpcd Addr Attr
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdAttribute_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    while(ucDpcdLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(ulDpcdAddr);

        // Set Dpcd Access Config
        ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_CONFIG);

        // Set Dpcd Attr
        ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(~(WORD)_BIT8, enumDpAuxRxDpcdAttr);

        ulDpcdAddr++;

        ucDpcdLen--;
    }

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Config in INT0
// Input Value  : ucDpcdAccessPortH        --> High Byte of DPCD Address
//                ucDpcdAccessPortM        --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL        --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig --> DPCD W / R / WR INT Enable
//                ucDpcdLen                --> Setting N = Len + 1 Dpcd Addr Int Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    while(ucDpcdLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(ulDpcdAddr);

        // Set Dpcd Access Config
        ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_CONFIG);

        // Set Dpcd Int
        if(bEnable == _ENABLE)
        {
            ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(~enumDpAuxRxDpcdInt, enumDpAuxRxDpcdInt);
        }
        else
        {
            ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(~enumDpAuxRxDpcdInt, 0x00);
        }

        ulDpcdAddr++;

        ucDpcdLen--;
    }

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Config in INT0
// Input Value  : ucDpcdAccessPortH        --> High Byte of DPCD Address
//                ucDpcdAccessPortM        --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL        --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig -->DPCD W / R / WR INT Enable
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdIntEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }

    return ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & enumDpAuxRxDpcdInt) == enumDpAuxRxDpcdInt);
}

//--------------------------------------------------
// Description  : Set DPCD Table Config in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                bEnable           --> Force Defer Enable
//                ucDpcdLen         --> Setting N = Len Dpcd Addr Force Defer Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    while(ucDpcdLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(ulDpcdAddr);

        // Set Dpcd Access Config
        ScalerDpAuxRx2AccessSelect_EXINT0(_DP_AUX_RX_DPCD_ACCESS_CONFIG);

        // Set Dpcd Defer
        if(bEnable == _ENABLE)
        {
            ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(~(WORD)_BIT12, _BIT12);
        }
        else
        {
            ScalerDpAuxRx2SetDpcdAccessBitData_EXINT0(~(WORD)_BIT12, 0x00);
        }

        ulDpcdAddr++;

        ucDpcdLen--;
    }

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Config in INT0
// Input Value  : ucDpcdAccessPortH   --> High Byte of DPCD Address
//                ucDpcdAccessPortM   --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL   --> Low Bye of DPCD Adress
// Output Value : Force Defer Enable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdForceDeferEnable_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }

    return ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & _BIT12) == _BIT12);
}

//--------------------------------------------------
// Description  : Clear DPCD Int Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2ClrDpcdIntFlag_EXINT0(void)
{
    Scaler32SetDWord_EXINT0(PB1A006_38_DPCD_IRQ_FLAG, 0xFFFFFFFF);
}

//--------------------------------------------------
// Description  : Source command reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2RequestReset_EXINT0(void)
{
    g_stDpAuxRx2ReceiveBackup.enumDpcdGroupIrq = _DP_AUX_RX_DPCD_NONE;
    g_stDpAuxRx2ReceiveBackup.ulDpcdWildCardIrq = 0x00;
    g_stDpAuxRx2ReceiveBackup.ulDpcdRemapIrq = 0x00;
    g_stDpAuxRx2ReceiveBackup.ulReqAddrStart = 0x00;
    g_stDpAuxRx2ReceiveBackup.ucReqLen = 0x00;
    g_stDpAuxRx2ReceiveBackup.enumReqType = _DP_AUX_RX_REQ_NONE;
    g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd = 0x00;
    g_stDpAuxRx2ReceiveBackup.enumIntCase = _DP_AUX_RX_INT_NONE;
    memset(g_stDpAuxRx2ReceiveBackup.pucFifoBackup, 0, sizeof(g_stDpAuxRx2ReceiveBackup.pucFifoBackup));
}

//--------------------------------------------------
// Description  : Source command backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2RequestAnalyze_EXINT0(void)
{
    DWORD ulDpcdCmd = 0;

    DELAY_5US_EXINT();

    ulDpcdCmd = Scaler32GetDWord_EXINT0(_REG_DP_AUX_RX2_RECIEVE_INT_CMD);
    g_stDpAuxRx2ReceiveBackup.enumDpcdGroupIrq = Scaler32GetDWord_EXINT0(PB1A006_38_DPCD_IRQ_FLAG);
    g_stDpAuxRx2ReceiveBackup.ulDpcdWildCardIrq = (Scaler32GetDWord_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG) & Scaler32GetDWord_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_EN));
    g_stDpAuxRx2ReceiveBackup.ulDpcdRemapIrq = Scaler32GetDWord_EXINT0(PB1A005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG);
    g_stDpAuxRx2ReceiveBackup.ulReqAddrStart = (DWORD)ulDpcdCmd & _BIT(19, 0);
    g_stDpAuxRx2ReceiveBackup.ucReqLen = (BYTE)((ulDpcdCmd >> 24) & 0x0F);
    g_stDpAuxRx2ReceiveBackup.enumReqType = (BYTE)((ulDpcdCmd >> 24) & 0xF0);
    g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd = g_stDpAuxRx2ReceiveBackup.ulReqAddrStart + g_stDpAuxRx2ReceiveBackup.ucReqLen;

    if((g_stDpAuxRx2ReceiveBackup.enumDpcdGroupIrq == 0x00) &&
       (g_stDpAuxRx2ReceiveBackup.ulDpcdWildCardIrq == 0x00) &&
       (g_stDpAuxRx2ReceiveBackup.ulDpcdRemapIrq == 0x00) &&
       (Scaler32GetBit_EXINT0(PB1A006_D8_IIC_STATUS, _BIT8) == _BIT8))
    {
        g_stDpAuxRx2ReceiveBackup.enumIntCase = _DP_AUX_RX_INT_I2C_FIXED_ADDR;

        return;
    }

    // Scan Link Training Addr
    if(ScalerDpAuxRx2ScanLinkTrainingAddr_EXINT0() == _TRUE)
    {
        g_stDpAuxRx2ReceiveBackup.enumIntCase = _DP_AUX_RX_INT_DPCD_LINK_TRAINING;

        return;
    }

    // Scan Link Status Addr
    if(ScalerDpAuxRx2ScanLinkStatusAddr_EXINT0() == _TRUE)
    {
        g_stDpAuxRx2ReceiveBackup.enumIntCase = _DP_AUX_RX_INT_DPCD_LINK_STATUS;

        return;
    }

    g_stDpAuxRx2ReceiveBackup.enumIntCase = _DP_AUX_RX_INT_DPCD_NORMAL;
}

//--------------------------------------------------
// Description  : Backup Tx Write data in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2WriteIntRequestDataBackup_EXINT0(void)
{
    BYTE ucAuxRx2FifoDelay = 100;
    BYTE ucAuxRx2FifoIndex = 0;

    // Rst fifo pointer
    RST_DP_AUX_RX2_INT_FIFO_POINTER_EXINT0();

    for(ucAuxRx2FifoIndex = 0; ucAuxRx2FifoIndex <= g_stDpAuxRx2ReceiveBackup.ucReqLen; ucAuxRx2FifoIndex++)
    {
        while((Scaler32GetBit_EXINT0(PB1A006_18_AUX_RX_ADDR, _BIT25) != 0x00) && (--ucAuxRx2FifoDelay))
        {
            ScalerMcuDelayDot2usPN();
        }

        g_stDpAuxRx2ReceiveBackup.pucFifoBackup[ucAuxRx2FifoIndex] = (BYTE)Scaler32GetByte_EXINT0(PB1A006_1C_AUX_RX_DATA, 0x01);

        Scaler32SetDWord_EXINT0(PB1A006_18_AUX_RX_ADDR, _BIT25);
    }
}

//--------------------------------------------------
// Description  : Scan Request Cmd Dpcd Addr
// Input Value  : Dpcd Addr
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt)
{
    DWORD ulDpcdAddrScanStart = TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
    DWORD ulDpcdAddrScanEnd = ((ucDpcdLen == 0) ? (ulDpcdAddrScanStart) : (ulDpcdAddrScanStart + ucDpcdLen - 1));

    if((ulDpcdAddrScanEnd < g_stDpAuxRx2ReceiveBackup.ulReqAddrStart) || (g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd < ulDpcdAddrScanStart))
    {
        return _FALSE;
    }

    if(((enumDpAuxRxDpcdInt == _DP_AUX_RX_DPCD_INT_READ) && (g_stDpAuxRx2ReceiveBackup.enumReqType != _DP_AUX_RX_REQ_NATIVE_READ)) ||
       ((enumDpAuxRxDpcdInt == _DP_AUX_RX_DPCD_INT_WRITE) && (g_stDpAuxRx2ReceiveBackup.enumReqType != _DP_AUX_RX_REQ_NATIVE_WRITE)))
    {
        return _FALSE;
    }

    return ScalerDpAuxRx2GetDpcdIntEnable_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdInt);
}

//--------------------------------------------------
// Description  : Scan Request Cmd LinkTraining Addr
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2ScanLinkTrainingAddr_EXINT0(void)
{
    if((g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd < 0x00100) ||
       (g_stDpAuxRx2ReceiveBackup.ulReqAddrStart > 0x00108) ||
       (g_stDpAuxRx2ReceiveBackup.enumReqType != _DP_AUX_RX_REQ_NATIVE_WRITE))
    {
        g_ucDpAuxRx2LTPatternSet = 0x00;

        return _FALSE;
    }
    else if(g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd >= 0x00103)
    {
        if(g_stDpAuxRx2ReceiveBackup.ulReqAddrStart >= 0x00103)
        {
            g_ucDpAuxRx2LTPatternSet = _BIT5;

            return _TRUE;
        }
        else if(g_stDpAuxRx2ReceiveBackup.ulReqAddrStart == 0x00102)
        {
            g_ucDpAuxRx2LTPatternSet = (_BIT7 | _BIT5);

            return _TRUE;
        }
        else
        {
            g_ucDpAuxRx2LTPatternSet = (_BIT7 | _BIT6 | _BIT5);

            return _TRUE;
        }
    }
    else if(g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd == 0x00102)
    {
        if(g_stDpAuxRx2ReceiveBackup.ulReqAddrStart == 0x00102)
        {
            g_ucDpAuxRx2LTPatternSet = _BIT7;

            return _TRUE;
        }
        else
        {
            g_ucDpAuxRx2LTPatternSet = (_BIT7 | _BIT6);

            return _TRUE;
        }
    }
    else
    {
        g_ucDpAuxRx2LTPatternSet = _BIT6;

        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Scan Request Cmd LinkStatus Addr
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2ScanLinkStatusAddr_EXINT0(void)
{
    if((g_stDpAuxRx2ReceiveBackup.enumReqType != _DP_AUX_RX_REQ_NATIVE_READ) ||
       (g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd < 0x00204) ||
       ((g_stDpAuxRx2ReceiveBackup.ulReqAddrStart > 0x00204) && (g_stDpAuxRx2ReceiveBackup.ulReqAddrStart < 0x0200E)) ||
       (g_stDpAuxRx2ReceiveBackup.ulReqAddrStart > 0x0200E))
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Dpcd Irq Handler
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdIntCaseHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    bit bDpcdIrqDone = _FALSE;

    switch(g_stDpAuxRx2ReceiveBackup.enumIntCase)
    {
        case _DP_AUX_RX_INT_DPCD_LINK_TRAINING:

            ScalerDpAuxRx2DpcdLinkTrainingHandler_EXINT0();

            g_ucDpAuxRx2LTPatternSet = 0x00;

            return _TRUE;

        case _DP_AUX_RX_INT_DPCD_LINK_STATUS:

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if((g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B) && (g_ucDpAuxRx2TrainingPatternSet == _DP_TRAINING_PATTERN_2))
            {
                BYTE ucDpAuxRx2Timeout = 200;

                // Avoid LLCTS Read 0x02216
                while(ucDpAuxRx2Timeout--)
                {
                    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT(10, 8)) == _BIT9)
                    {
                        if(Scaler32GetDWord_EXINT0(_REG_DP_AUX_RX2_RECIEVE_CMD) == 0x90002216)
                        {
                            // Rst fifo pointer
                            RST_DP_AUX_RX2_FIFO_POINTER_EXINT0();

                            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD, TO_DWORD(0x00, _DP_AUX_RX_DPCD_128B132B_TRAINING_AUX_RD_INTERVAL, 0x00, 0x00));

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
                            // Set tx_data Busy to toggle Hw
                            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD_START, _BIT0);

                            // Wait tx_data Busy = 0
                            if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD_START, _BIT0) == _BIT0)
                            {
                                DELAY_5US_EXINT();
                            }

                            // Set tx_start
                            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD_START, _BIT1);
#endif
                        }

                        break;
                    }

                    DELAY_5US_EXINT();
                }
            }
#endif

            ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT6), 0x00);

            return _TRUE;

        case _DP_AUX_RX_INT_DPCD_NORMAL:

            switch(g_stDpAuxRx2ReceiveBackup.enumDpcdGroupIrq)
            {
                // DPCD 00000~000FF
                case _DP_AUX_RX_DPCD_00000_000FF:

                    break;

                // DPCD 00100~001FF
                case _DP_AUX_RX_DPCD_00100_001FF:

#if((_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
                    // Cable ID
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x01, 0x10, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRx2DpcdCableIDSyncHandler_EXINT0();

                        bDpcdIrqDone = _TRUE;
                    }
#endif

#if(_DP_MST_SUPPORT == _ON)
                    // Source Write DPCD 111h
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x01, 0x11, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRxMstProtocolEnableHandler_EXINT0(enumInputPort);

                        bDpcdIrqDone = _TRUE;
                    }
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
                    // DPCD Write 00120h IRQ
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x01, 0x20, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRx2FecHanlder_EXINT0();

                        bDpcdIrqDone = _TRUE;
                    }
#endif

#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x01, 0x60, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        // Source Write DPCD 0x00160
                        ScalerDpAuxRx2DscEnable_EXINT0();

                        bDpcdIrqDone = _TRUE;
                    }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
                    // Write 001B0 into INT0
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x01, 0xB0, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRx2DpcdPrModeHandler_EXINT0();

                        bDpcdIrqDone = _TRUE;
                    }
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x01, 0xC2, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRxSyncPayloadIDHandler_EXINT0(enumInputPort);

                        bDpcdIrqDone = _TRUE;
                    }
#endif

                    break;

                // DPCD 00200~002FF
                case _DP_AUX_RX_DPCD_00200_002FF:

                    // Write 00270h into INT0
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x02, 0x70, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRx2DpcdTestCRCHandler_EXINT0();

                        bDpcdIrqDone = _TRUE;
                    }

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpAuxRxSyncActHandler_EXINT0(enumInputPort);

                        bDpcdIrqDone = _TRUE;
                    }
#endif

                    break;

                // DPCD 00300~0037F
                case _DP_AUX_RX_DPCD_00300_0037F:

#if(_DP_AUX_RX_DPCD_300_SOURCE_OUI_INT_SUPPORT == _ON)
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x03, 0x00, 3, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
#if(_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)
                        SET_DP_RX_USER_INT_EVENT(enumInputPort, _DP_USER_INT_EVENT_SOURCE_WRITE_OUI);
#endif
                    }
#endif

                    break;

                // DPCD 00400~0047F
                case _DP_AUX_RX_DPCD_00400_0047F:

                    break;

                // DPCD 00500~005FF
                case _DP_AUX_RX_DPCD_00500_005FF:

                    break;

                // DPCD 00600~0061F
                case _DP_AUX_RX_DPCD_00600_0061F:

                    // Write 00600h into INT0
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x06, 0x00, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRx2DpcdPowerStateHandler_EXINT0();

                        bDpcdIrqDone = _TRUE;
                    }

                    break;

                // DPCD 00700~0077F
                case _DP_AUX_RX_DPCD_00700_0077F:

                    break;

                // DPCD 02000~020FF
                case _DP_AUX_RX_DPCD_02000_020FF:

                    break;

                // DPCD 02200~022FF
                case _DP_AUX_RX_DPCD_02200_022FF:

                    break;

                // DPCD 02300~0237F
                case _DP_AUX_RX_DPCD_02300_0237F:

                    break;

                // DPCD 03000~030FF
                case _DP_AUX_RX_DPCD_03000_030FF:

                    break;

                // DPCD 03100~031FF
                case _DP_AUX_RX_DPCD_03100_031FF:

                    break;

                // DPCD 60000~6001F
                case _DP_AUX_RX_DPCD_60000_6001F:

                    break;

                // DPCD 68000~6803F
                case _DP_AUX_RX_DPCD_68000_6803F:

                    // Clear Integrity Failure Flag
                    ScalerDpMacDphyRxClearIntegrityFailureFlag_EXINT0(enumInputPort);

                    // Read 68006 clear 68029 bit 1
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x80, 0x06, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x06, 0x80, 0x29, ~_BIT1, 0x00);
                    }

                    // Write 68013
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x80, 0x13, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
                        {
                            // DP Mac Clock Select to Xtal Clock
                            ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_XTAL_CLOCK);
                        }
                    }

                    // Read 6802B clear 68029 bit 0
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x80, 0x2B, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x06, 0x80, 0x29, ~_BIT0, 0x00);
                    }

#if((_DP_TX_SUPPORT == _ON) && (_D2_DP_MST_PORT_SUPPORT == _ON))
                    // Detect if V'(0x68027) is read by Source
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x80, 0x27, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpHdcp14RxResetKsvFifoToFirst_EXINT0(enumInputPort);
                    }
#endif

                    // Detect if Aksv(0x6800B) is Written by Source
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x80, 0x0B, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        ScalerDpAuxRx2DpcdHdcp14AksvHandler_EXINT0();
                    }

#if((_DP_TX_SUPPORT == _ON) && (_D2_DP_MST_PORT_SUPPORT == _ON))
                    // Read 6803A into INT0
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpHdcp14RxSetKsvFifo_EXINT0(enumInputPort);
                    }
#endif

                    bDpcdIrqDone = _TRUE;

                    break;

                // DPCD 69000~6957F
                case _DP_AUX_RX_DPCD_69000_6957F:

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    // HW auto Clear 69493 bit0
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x93, 0x31, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x06, 0x94, 0x93, ~_BIT0, 0x00);

                        bDpcdIrqDone = _TRUE;
                    }

                    // HW auto Clear 69493 bit2
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x92, 0xEF, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
                    {
                        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x06, 0x94, 0x93, ~_BIT2, 0x00);

                        bDpcdIrqDone = _TRUE;
                    }
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    // Write k
                    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x93, 0xF4, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
                    {
                        if(g_usDpAuxRx2StreamIdAddrEnd != 0x0000)
                        {
                            ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(0x06, HIBYTE(g_usDpAuxRx2StreamIdAddrEnd), LOBYTE(g_usDpAuxRx2StreamIdAddrEnd), 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);
                        }

                        // Get # of StreamID_Type Length, StreamID_Type = stream_ID1 || Type || stream_ID2 || Type || .....
                        g_usDpAuxRx2StreamIdAddrEnd = 0x93F5 + ((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x06, 0x93, 0xF4) * 2) - 1);

                        ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(0x06, HIBYTE(g_usDpAuxRx2StreamIdAddrEnd), LOBYTE(g_usDpAuxRx2StreamIdAddrEnd), 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

                        // If Source write k and StreamID_Type DPCD cmd in the same native write request, skip interrupt Done
                        if((g_usDpAuxRx2StreamIdAddrEnd) > LOWORD(g_stDpAuxRx2ReceiveBackup.ulReqAddrEnd))
                        {
                            bDpcdIrqDone = _TRUE;
                        }
                    }
#endif

                    break;

                default:

                    break;
            }

            return bDpcdIrqDone;

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : I2c Irq Handler
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2I2cIntCaseHandler_EXINT0(void)
{
    bit bDpcdIrqDone = _FALSE;

    // If source i2c_over_aux cmd hit slave addr = 50
    if(Scaler32GetBit_EXINT0(PB1A006_D8_IIC_STATUS, _BIT8) == _BIT8)
    {
        // Clear flag
        Scaler32SetDWord_EXINT0(PB1A006_D8_IIC_STATUS, _BIT8);

        ScalerDpAuxRx2EdidReadAddrOnlyProtect_EXINT0();

        bDpcdIrqDone = _TRUE;
    }

    return bDpcdIrqDone;
}

//--------------------------------------------------
// Description  : Write1Clear Handler
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdWrite1ClearHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    bit bDpcdWrite1ClearDone = _FALSE;

    enumInputPort = enumInputPort;

    ScalerDpAuxRx2WriteIntRequestDataBackup_EXINT0();

    switch(g_stDpAuxRx2ReceiveBackup.enumDpcdGroupIrq)
    {
        // DPCD 00000~000FF
        case _DP_AUX_RX_DPCD_00000_000FF:

            break;

        // DPCD 00100~001FF
        case _DP_AUX_RX_DPCD_00100_001FF:

            break;

        // DPCD 00200~002FF
        case _DP_AUX_RX_DPCD_00200_002FF:

            // MST Handler & Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x02, 0x01, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
#if(_DP_MST_SUPPORT == _ON)
                // SET IRQ_VECTOR
                SET_DP_AUX_RX2_DPCD_IRQ_VECTOR(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x000201 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart]);

                if(GET_DP_AUX_RX2_MSG_IRQ_HANDLE() == _TRUE)
                {
                    // Mst Handler
                    ScalerDpMstRxIntHandle_EXINT0(enumInputPort);
                }
#endif
                ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x01, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x000201 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart]), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x02, 0x0F, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x0F, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x00020F - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & _BIT(2, 0)), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x02, 0x80, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x000280 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & (_BIT1 | _BIT0)), 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
                if(ScalerDpAuxRx2GetFecStatusW1cProtectEnable_EXINT0() == _ENABLE)
                {
                    ScalerDpAuxRx2DpcdFecStatusW1cProtectHandler_EXINT0();
                }
#endif

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Clear Act Handle & VC Payload Table Updated
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                if((g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x0002C0 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & _BIT0) == _BIT0)
                {
                    ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0xC0, ~(_BIT1 | _BIT0), 0x00);
                }

                bDpcdWrite1ClearDone = _TRUE;
            }

            break;

        // DPCD 00300~0037F
        case _DP_AUX_RX_DPCD_00300_0037F:

            break;

        // DPCD 00400~0047F
        case _DP_AUX_RX_DPCD_00400_0047F:

            break;

        // DPCD 00500~005FF
        case _DP_AUX_RX_DPCD_00500_005FF:

            break;

        // DPCD 00600~0061F
        case _DP_AUX_RX_DPCD_00600_0061F:

            break;

        // DPCD 00700~0077F
        case _DP_AUX_RX_DPCD_00700_0077F:

            break;

        // DPCD 02000~020FF
        case _DP_AUX_RX_DPCD_02000_020FF:

            // MST Handler & Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x03, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
#if(_DP_MST_SUPPORT == _ON)
                // SET IRQ_VECTOR
                SET_DP_AUX_RX2_DPCD_IRQ_VECTOR(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002003 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart]);

                if(GET_DP_AUX_RX2_MSG_IRQ_HANDLE() == _TRUE)
                {
                    // Mst Handler
                    ScalerDpMstRxIntHandle_EXINT0(enumInputPort);
                }
#endif
                ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x03, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002003 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart]), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x04, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x04, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002004 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & _BIT(4, 0)), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x05, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x05, ~g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002005 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart], 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x0B, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x0B, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x00200B - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & (_BIT3 | _BIT1 | _BIT0)), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x11, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x11, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002011 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & _BIT(2, 0)), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x20, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x20, ~(g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002020 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart] & _BIT(2, 0)), 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x20, 0x21, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x21, ~g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x002021 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart], 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            break;

        // DPCD 02200~022FF
        case _DP_AUX_RX_DPCD_02200_022FF:

            break;

        // DPCD 02300~0237F
        case _DP_AUX_RX_DPCD_02300_0237F:

            break;

        // DPCD 03000~030FF
        case _DP_AUX_RX_DPCD_03000_030FF:

            // Write 1 Clear
            if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x00, 0x30, 0x04, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x30, 0x04, ~g_stDpAuxRx2ReceiveBackup.pucFifoBackup[0x003004 - g_stDpAuxRx2ReceiveBackup.ulReqAddrStart], 0x00);

                bDpcdWrite1ClearDone = _TRUE;
            }

            break;

        // DPCD 03100~031FF
        case _DP_AUX_RX_DPCD_03100_031FF:

            break;

        // DPCD 60000~6001F
        case _DP_AUX_RX_DPCD_60000_6001F:

            break;

        // DPCD 68000~6803F
        case _DP_AUX_RX_DPCD_68000_6803F:

            break;

        // DPCD 69000~6957F
        case _DP_AUX_RX_DPCD_69000_6957F:

            break;

        default:

            break;
    }

    return bDpcdWrite1ClearDone;
}

//--------------------------------------------------
// Description  : ReadClear Handler
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdReadClearHandler_EXINT0(void)
{
    bit bDpcdReadClearDone = _FALSE;

    switch(g_stDpAuxRx2ReceiveBackup.enumDpcdGroupIrq)
    {
        // DPCD 00000~000FF
        case _DP_AUX_RX_DPCD_00000_000FF:

            break;

        // DPCD 00100~001FF
        case _DP_AUX_RX_DPCD_00100_001FF:

            break;

        // DPCD 00200~002FF
        case _DP_AUX_RX_DPCD_00200_002FF:

            break;

        // DPCD 00300~0037F
        case _DP_AUX_RX_DPCD_00300_0037F:

            break;

        // DPCD 00400~0047F
        case _DP_AUX_RX_DPCD_00400_0047F:

            break;

        // DPCD 00500~005FF
        case _DP_AUX_RX_DPCD_00500_005FF:

            break;

        // DPCD 00600~0061F
        case _DP_AUX_RX_DPCD_00600_0061F:

            break;

        // DPCD 00700~0077F
        case _DP_AUX_RX_DPCD_00700_0077F:

            break;

        // DPCD 02000~020FF
        case _DP_AUX_RX_DPCD_02000_020FF:

            break;

        // DPCD 02200~022FF
        case _DP_AUX_RX_DPCD_02200_022FF:

            break;

        // DPCD 02300~0237F
        case _DP_AUX_RX_DPCD_02300_0237F:

            break;

        // DPCD 03000~030FF
        case _DP_AUX_RX_DPCD_03000_030FF:

            break;

        // DPCD 03100~031FF
        case _DP_AUX_RX_DPCD_03100_031FF:

            break;

        // DPCD 60000~6001F
        case _DP_AUX_RX_DPCD_60000_6001F:

            break;

        // DPCD 68000~6803F
        case _DP_AUX_RX_DPCD_68000_6803F:

            break;

        // DPCD 69000~6957F
        case _DP_AUX_RX_DPCD_69000_6957F:

            break;

        default:

            break;
    }

    return bDpcdReadClearDone;
}
#endif

//-------------------------------------------------------
// Description  : Edid Read Addr Only Protect Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2EdidReadAddrOnlyProtect_EXINT0(void)
{
    // if cmd is i2c_over_aux read & addr only
    if(((Scaler32GetByte_EXINT0(_REG_DP_AUX_RX2_RECIEVE_CMD, 0x03) & (_BIT7 | _BIT5 | _BIT4)) == _BIT4) &&
       (Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, _BIT16) == _BIT16))
    {
        // Rst fifo pointer
        RST_DP_AUX_RX2_FIFO_POINTER_EXINT0();

        // Force Ack
        if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, (_BIT10 | _BIT9 | _BIT8)) == _BIT9)
        {
            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD, 0x00);

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
            // Set tx_data Busy to toggle Hw
            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD_START, _BIT0);

            // Wait tx_data Busy = 0
            if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD_START, _BIT0) == _BIT0)
            {
                DELAY_5US_EXINT();
            }

            // Set tx_start
            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_REPLY_CMD_START, _BIT1);
#endif
        }
    }
}

//-------------------------------------------------------
// Description  : Symbol Error Count Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdSymbolErrorCountHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(GET_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT() == _FALSE)
    {
        // Reset Aux FIFO
        RST_DP_AUX_RX2_FIFO_POINTER_EXINT0();

        if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
        {
            ScalerDpMacDphyRxPhyCtsErrorCounterUpdate_EXINT0(enumInputPort);
        }
        else
        {
            ScalerDpMacDphyRxErrorCounterUpdate_EXINT0(enumInputPort);
        }

        // Wait for RCV_STANBY, in Order to Reply AUX DEFER
        ScalerDpAuxRx2WaitRcv_EXINT0();

        SET_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT();

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _DISABLE);
#else
        Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, 0x00);
#endif
    }
    else
    {
        // Update Symbol Error Count by HW Auto Reply
        CLR_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT();

        if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
        {
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
            {
                // Reset PRBS31 Error Counter
                ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_PRBS31);
            }
            else
#endif
            {
                if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x00) == 0x06) ||
                   (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x00) == 0x0A))
                {
                    // Reset PRBS7 Error Counter
                    ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_PRBS7);
                }
                else
                {
                    // Reset 8B/10B Error Counter
                    ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B_DISPARITY);
                }
            }
        }
        else
        {
            // Reset 8B/10B Error Counter
            ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B);
        }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
#else
        Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, _BIT1);
#endif
    }
}

#if(_DP_RX_FEC_SUPPORT == _ON)
//-------------------------------------------------------
// Description  : FEC Error Count Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdFecErrorCount_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    WORD usFECErrorCount = 0;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // 281h/282h Read Force Defer
    if(ScalerDpAuxRx2GetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_281) == _ENABLE)
    {
        usFECErrorCount = (((WORD)ScalerDpMacDphyRxFecErrorCountUpdateHighByte_EXINT0(enumInputPort) << 8) | (ScalerDpMacDphyRxFecErrorCountUpdateLowByte_EXINT0(enumInputPort)));

        // FEC Error Count Update
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x81, (BYTE)usFECErrorCount);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x82, (BYTE)(usFECErrorCount >> 8) | _BIT7);

        // Disable 00281h~00282h Force Defer
        ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_281, _DISABLE);
    }
    else
    {
        // Enable 00281h~00282h Force Defer
        ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_281, _ENABLE);
    }
#else
    // 281h/282h Read Force Defer
    if(Scaler32GetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, _BIT0) == _BIT0)
    {
        if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
        {
            usFECErrorCount = 0;
        }
        else
        {
            usFECErrorCount = (((WORD)ScalerDpMacDphyRxFecErrorCountUpdateHighByte_EXINT0(enumInputPort) << 8) | (ScalerDpMacDphyRxFecErrorCountUpdateLowByte_EXINT0(enumInputPort)));
        }

        // FEC Error Count Update
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x81, (BYTE)usFECErrorCount);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x82, (BYTE)(usFECErrorCount >> 8) | _BIT7);

        // Disable 00281h~00282h Force Defer
        Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT0, 0x00);
    }
#endif
}

//-------------------------------------------------------
// Description  : Fec Status W1C Protect Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdFecStatusW1cProtectHandler_EXINT0(void)
{
    // Let Source Know We can receive the FEC en seq.
    ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Set Fec Status W1C Protect
// Input Value  : _ENABLE/_DISABLE
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx2SetFecStatusW1cProtectEnable_EXINT0(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    g_bDpAuxRx2FecStatusW1cProtect = bEnable;
#elif(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(_AUX_RX_FEC_DECODE_EN_DETECTED, bEnable);
#endif
}

//--------------------------------------------------
// Description  : Get Fec Status W1C Protect
// Input Value  : none
// Output Value : _ENABLE/_DISABLE
//--------------------------------------------------
bit ScalerDpAuxRx2GetFecStatusW1cProtectEnable_EXINT0(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    return g_bDpAuxRx2FecStatusW1cProtect;
#elif(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
    return ScalerDpAuxRx2GetDpcdWildCardIntEnable_EXINT0(_AUX_RX_FEC_DECODE_EN_DETECTED);
#else
    return _DISABLE;
#endif
}
#endif

//--------------------------------------------------
// Description  : Link Training Handler
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdLinkTrainingHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

#if((_DP_LT_FORCE_FAKE_LT_FOR_TBT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT))
    bit bForceFakeLT = _TRUE;
#else
    bit bForceFakeLT = _FALSE;
#endif

    // Write Link Config Field into INT0
    g_ucDpAuxRx2TrainingPatternSet = (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & 0x0F);

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    g_enumDpAuxRx2CodingType = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x08);
    ScalerDpAuxRx2SetAuxReadInterval_EXINT0();
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    // Backup Source Write Continous 0x102 and 0x103
    g_ucDpAuxRx2LTPatternSet = Scaler32GetByte_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, 0x03);
#endif

    // SVN Record 1167
    if(((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)) &&
       ((g_ucDpAuxRx2LTPatternSet & (_BIT7 | _BIT6 | _BIT5)) == _BIT6) &&
       ((g_enumDpAuxRx2LinkRate != ScalerDpAuxRxGetDpcdLinkRate_EXINT0(enumInputPort)) ||
        (g_enumDpAuxRx2LaneCount != (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F))))
    {
        g_ucDpAuxRx2TrainingPatternSet = _DP_TRAINING_PATTERN_END;

        SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);
    }

    ScalerDpAuxRxSetLinkRate_EXINT0(enumInputPort, ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x00));
    ScalerDpAuxRxSetLaneCount_EXINT0(enumInputPort, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F));

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
    {
        switch(g_ucDpAuxRx2TrainingPatternSet)
        {
            case _DP_TRAINING_PATTERN_1:

                // LT Dpcd Force Defer
                ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_ENABLE);

                // Early return to auto mode for Dpcd 2216
                SET_DP_AUX_RX2_AUTO_MODE_EXINT();

                CLR_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG();

                // clear LT fail IRQ
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX2_DP2_LINK_TRAINING_TIMEOUT);
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX2_DP_HPD_IRQ_ASSERT);
                ScalerTimerWDActivateTimerEvent_EXINT0(400, _SCALER_WD_TIMER_EVENT_RX2_DP2_LINK_TRAINING_TIMEOUT);

                if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
                {
                    if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS)
                    {
                        if(ScalerDpAuxRx2PhyCtsTrainingPattern1_EXINT0() == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                        }
                    }
                }
                else
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS))
                    {
                        if(GET_DP_AUX_RX2_FAKE_LINK_TRAINING() == _FALSE)
                        {
                            if(ScalerDpAuxRx2TrainingPattern1_EXINT0(_DP_NORMAL_LT) == _TRUE)
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                        else
                        {
                            if(ScalerDpAuxRx2TrainingPattern1_EXINT0(_DP_FAKE_LT) == _TRUE)
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                    }
                }

                // LT Dpcd Force Defer Disable
                ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_DISABLE);

                break;

            case _DP_TRAINING_PATTERN_2:

                // LT Dpcd Force Defer
                ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_ENABLE);

                // Early return to auto mode for Dpcd 2216
                SET_DP_AUX_RX2_AUTO_MODE_EXINT();

                g_bDpAuxRx2Tp1Initial = _FALSE;

                // Check Source Write Continous 0x102 and 0x103..It need to break if write 0x102 only
                if((g_ucDpAuxRx2LTPatternSet & (_BIT7 | _BIT5)) == _BIT7)
                {
                    // LT Dpcd Force Defer Disable
                    ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_DISABLE);

                    break;
                }

                if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpAuxRx2PhyCtsTrainingPattern2_EXINT0() == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                }
                else
                {
                    if((GET_DP_AUX_RX2_FAKE_LINK_TRAINING() == _FALSE) &&
                       ((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)))
                    {
                        if(ScalerDpAuxRx2TrainingPattern2_EXINT0(_DP_NORMAL_LT) == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);

                            ScalerDpMacDphyRxLaneCountSet_EXINT0(enumInputPort, _DP_LANE_AUTO_MODE);
#if(_DP_RX_FEC_SUPPORT == _ON)
                            ScalerDpAuxRx2TrainingPatternEnd_EXINT0();

                            ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _ENABLE);

                            // Mac Reset After Link Clock Stable
                            ScalerDpMacDphyRxReset_EXINT0(enumInputPort);
#endif
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                    else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpAuxRx2TrainingPattern2_EXINT0(_DP_FAKE_LT) == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                }

                // LT Dpcd Force Defer Disable
                ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_DISABLE);

                break;

            case _DP_TRAINING_PATTERN_3:

                // LT Dpcd Force Defer
                ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_ENABLE);

                // Early return to auto mode for Dpcd 2216
                SET_DP_AUX_RX2_AUTO_MODE_EXINT();

                g_bDpAuxRx2Tp1Initial = _FALSE;

                if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) ||
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_3_FAIL))
                    {
                        if(ScalerDpAuxRx2PhyCtsTrainingPattern2_EXINT0() == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_3_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_3_FAIL);
                        }
                    }
                }
                else
                {
                    if((GET_DP_AUX_RX2_FAKE_LINK_TRAINING() == _FALSE) &&
                       ((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_3_FAIL)))
                    {
                        if(ScalerDpAuxRx2TrainingPattern3_EXINT0(_DP_NORMAL_LT) == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_3_PASS);
#if(_DP_RX_FEC_SUPPORT == _ON)
                            ScalerDpAuxRx2TrainingPatternEnd_EXINT0();

                            ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _ENABLE);

                            // Mac Reset After Link Clock Stable
                            ScalerDpMacDphyRxReset_EXINT0(enumInputPort);
#endif
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_3_FAIL);
                        }
                    }
                    else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_3_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_3_FAIL))
                    {
                        if(ScalerDpAuxRx2TrainingPattern3_EXINT0(_DP_FAKE_LT) == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_3_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_3_FAIL);
                        }
                    }
                }

                // LT Dpcd Force Defer Disable
                ScalerDpAuxRx2SetDpcdLinkStatusForceDefer_EXINT0(_DISABLE);

                break;

            case _DP_TRAINING_PATTERN_END:

                g_bDpAuxRx2Tp1Initial = _FALSE;

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX2_DP2_LINK_TRAINING_TIMEOUT);

                if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    ScalerDpAuxRx2TrainingPatternEnd_EXINT0();
                }
                else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_3_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_3_PASS))
                {
                    ScalerDpAuxRx2SetDpcdBitWriteValue_EXINT0(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) ||
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_3_PASS))
                    {
                        ScalerDpAuxRx2TrainingPatternEnd_EXINT0();

                        SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
#if(_DP_RX_FEC_SUPPORT == _ON)
                        // Enable FEC Running Indicator
                        ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~_BIT2, _BIT2);
#endif
                    }
                    else
                    {
                        SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
#if(_DP_RX_FEC_SUPPORT == _ON)
                        ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _ENABLE);

                        // Enable FEC Running Indicator
                        ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~_BIT2, _BIT2);
#endif
                    }
#if(_DP_MARGIN_LINK_SUPPORT == _ON)
                    CLR_DP_RX_D2_MARGIN_LINK();
#endif
                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);

                    ScalerDpHdcpRxClrHdcpCpirqFlag_EXINT0(enumInputPort);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
                    ScalerDpHdcp2RxCancelTimerEvent_EXINT0(enumInputPort);
#endif
                }
                else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_3_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_3_FAIL) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS))
                {
                    SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_FAIL);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
                    CLR_DP_RX_D2_MARGIN_LINK();
#endif
                }

                break;

            default:
                break;
        }
    }
    else
#endif
    {
        switch(g_ucDpAuxRx2TrainingPatternSet)
        {
            case _DP_TRAINING_PATTERN_1:

                CLR_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG();

                // clear LT fail IRQ
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX2_DP_HPD_IRQ_ASSERT);

                // Check Source Only Write 0x102 without 0x103~0x106
                if((g_ucDpAuxRx2LTPatternSet & (_BIT7 | _BIT5)) == _BIT7)
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS) &&
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
                    {
                        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x03, 0x00);
                        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x04, 0x00);
                        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x05, 0x00);
                        ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x01, 0x06, 0x00);

                        g_ucDpAuxRx2LinkRequest01 = 0x00;
                        g_ucDpAuxRx2LinkRequest23 = 0x00;

#if(_DP_LT_TP1_FORCE_MARGINAL_LINK == _ON)
                        SET_DP_RX_D2_LANE0_MARGIN_LINK_TP1();
                        SET_DP_RX_D2_LANE1_MARGIN_LINK_TP1();
                        SET_DP_RX_D2_LANE2_MARGIN_LINK_TP1();
                        SET_DP_RX_D2_LANE3_MARGIN_LINK_TP1();
#endif
                        g_bDpAuxRx2Tp1Initial = _TRUE;
                    }
                }

                if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
                {
                    if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS)
                    {
                        if(ScalerDpAuxRx2PhyCtsTrainingPattern1_EXINT0() == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                        }
                    }
                }
                else
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS))
                    {
                        if((GET_DP_AUX_RX2_FAKE_LINK_TRAINING() == _FALSE) && (bForceFakeLT == _FALSE))
                        {
                            if(ScalerDpAuxRx2TrainingPattern1_EXINT0(_DP_NORMAL_LT) == _TRUE)
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                        else
                        {
                            if(ScalerDpAuxRx2TrainingPattern1_EXINT0(_DP_FAKE_LT) == _TRUE)
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                    }
                }

                break;

            case _DP_TRAINING_PATTERN_2:
            case _DP_TRAINING_PATTERN_3:
            case _DP_TRAINING_PATTERN_4:

                g_bDpAuxRx2Tp1Initial = _FALSE;

                if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                       (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpAuxRx2PhyCtsTrainingPattern2_EXINT0() == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                }
                else
                {
                    if((GET_DP_AUX_RX2_FAKE_LINK_TRAINING() == _FALSE) &&
                       (bForceFakeLT == _FALSE) &&
                       ((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)))
                    {
                        if(ScalerDpAuxRx2TrainingPattern2_EXINT0(_DP_NORMAL_LT) == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);

                            ScalerDpMacDphyRxLaneCountSet_EXINT0(enumInputPort, _DP_LANE_AUTO_MODE);
#if(_DP_RX_FEC_SUPPORT == _ON)
                            if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x20, _BIT0) == _BIT0)
                            {
                                ScalerDpAuxRx2TrainingPatternEnd_EXINT0();

                                ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _ENABLE);

                                // Mac Reset After Link Clock Stable
                                ScalerDpMacDphyRxReset_EXINT0(enumInputPort);

                                ScalerDpAuxRx2SetFecStatusW1cProtectEnable_EXINT0(_DISABLE);
                            }
#endif
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                    else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpAuxRx2TrainingPattern2_EXINT0(_DP_FAKE_LT) == _TRUE)
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                }

                break;

            case _DP_TRAINING_PATTERN_END:

                g_bDpAuxRx2Tp1Initial = _FALSE;

                if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT7) == _BIT7)
                {
                    if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS)
                    {
                        ScalerDpAuxRx2PhyCtsTrainingPatternEnd_EXINT0();
                        SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                    }
                }
                else
                {
                    if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
                    {
                        ScalerDpAuxRx2TrainingPatternEnd_EXINT0();
                    }
                    else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) || (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_PASS))
                    {
                        ScalerDpAuxRx2SetDpcdBitWriteValue_EXINT0(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                        if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS)
                        {
                            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX2_DP_LINK_TRAINING_REBUILD_PHY);
#if(_DP_RX_FEC_SUPPORT == _ON)
                            if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x20, _BIT0) == _BIT0)
                            {
                                SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);

                                // Enable FEC Running Indicator
                                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~_BIT2, _BIT2);
                            }
                            else
#endif
                            {
                                ScalerDpAuxRx2TrainingPatternEnd_EXINT0();

                                if(GET_DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY_SUPPORT() == _ENABLE)
                                {
                                    SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY);

                                    ScalerTimerWDActivateTimerEvent_EXINT0(30, _SCALER_WD_TIMER_EVENT_RX2_DP_LINK_TRAINING_REBUILD_PHY);
                                }
                                else
                                {
                                    SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);

                                    ScalerDpMacDphyRxMacResetProc_EXINT0(enumInputPort);
                                }
                            }
                        }
                        else
                        {
                            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
#if(_DP_RX_FEC_SUPPORT == _ON)
                            if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x20, _BIT0) == _BIT0)
                            {
                                ScalerDpAuxRx2SetFecStatusW1cProtectEnable_EXINT0(_ENABLE);

                                // Enable FEC Running Indicator & En sequence received
                                ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));
                            }
#endif
                        }

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
                        CLR_DP_RX_D2_MARGIN_LINK();
#endif
                        // Set DP Receive Port0 In Sync
                        ScalerDpAuxRx2SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);

                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);

                        ScalerDpHdcpRxClrHdcpCpirqFlag_EXINT0(enumInputPort);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
                        ScalerDpHdcp2RxCancelTimerEvent_EXINT0(enumInputPort);
#endif
                    }
                    else if((GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_AUX_RX2_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS))
                    {
                        SET_DP_AUX_RX2_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_FAIL);

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
                        CLR_DP_RX_D2_MARGIN_LINK();
#endif
                    }
                }

                break;

            default:
                break;
        }
    }
}

//-------------------------------------------------------
// Description  : Dpcd Power State Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdPowerStateHandler_EXINT0(void)
{
    if((ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
    {
        // DP Power Down
        if(GET_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG() == _FALSE)
        {
            SET_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG();

            g_pucDpAuxRx2LinkStatusBackup_INT[0] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x02);
            g_pucDpAuxRx2LinkStatusBackup_INT[1] = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x02, 0x03);
            g_pucDpAuxRx2LinkStatusBackup_INT[2] = ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x04, _BIT0);
        }

        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x02, 0x00);
        ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(0x00, 0x02, 0x03, 0x00);
        ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), _BIT7);

#if(_DP_MST_SUPPORT == _ON)
        CLR_DP_AUX_RX2_SOURCE_WRITE_POWER_UP();
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
        ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x80, ~_BIT2, 0x00);
#endif
    }
    else if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
    {
#if(_DP_MST_SUPPORT == _ON)
        SET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TRIGGERED);
#endif
    }
}

//-------------------------------------------------------
// Description  : Hdcp Aksv Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdHdcp14AksvHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(GET_DP_AUX_RX2_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        // DP Mac Clock Select to Xtal Clock
        ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_XTAL_CLOCK);
    }

    bit bDpAuxRxHdcpPowerCutSwitch = _FALSE;

    // Check Power Status
    if(ScalerDpMacRxGetPowerCutCurrentStatus_EXINT0(enumInputPort) == _POWER_CUT_ON)
    {
        // Turn off power cut to calculate R0'
        ScalerDpMacRxPowerProc_EXINT0(enumInputPort, _POWER_ACTION_OFF_TO_NORMAL);

        bDpAuxRxHdcpPowerCutSwitch = _TRUE;
    }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Switch HDCP to 1.4 Module from 2.2 Module as receiving AKsv
    if(ScalerDpHdcpRxGetHdcpMode_EXINT0(enumInputPort) == _HDCP_22)
    {
        // Select to HDCP 1.4 Module
        ScalerDpHdcpRxSetHdcpMode_EXINT0(enumInputPort, _HDCP_14);
    }
#endif

    // Set HDCP An, Aksv, Repeater into Register
    ScalerDpMacDphyRxSetHdcp14Info_EXINT0(enumInputPort);

    // Calculate R0' by manual toggle HDCP 1.4 Module
    ScalerDpMacDphyRxSetHdcp14CalR0_EXINT0(enumInputPort);

#if((_DP_TX_SUPPORT == _ON) && (_D2_DP_MST_PORT_SUPPORT == _ON))
    ScalerDpAuxRx2HdcpResetDpcdInfo_EXINT0();

    ScalerDpHdcp14RxSetAuthAksvWritten_EXINT0(enumInputPort);
#endif

    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x06, 0x80, 0x05, ScalerDpMacDphyRxGetHdcp14R0_EXINT0(enumInputPort, _HDCP_14_R0_LSB));
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x06, 0x80, 0x06, ScalerDpMacDphyRxGetHdcp14R0_EXINT0(enumInputPort, _HDCP_14_R0_MSB));

    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x06, 0x80, 0x29, 0x02);

    // Turn on power cut when turned off
    if(bDpAuxRxHdcpPowerCutSwitch == _TRUE)
    {
        bDpAuxRxHdcpPowerCutSwitch = _FALSE;

        ScalerDpMacRxPowerProc_EXINT0(enumInputPort, _POWER_ACTION_NORMAL_TO_OFF);
    }

#if(_DP_HDCP2_RX_SUPPORT == _ON)
    ScalerDpHdcp2RxCancelTimerEvent_EXINT0(enumInputPort);
#endif
}

//-------------------------------------------------------
// Description  : Test CRC Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdTestCRCHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if((ScalerDpMacStreamRxGetCRCCalculate_EXINT0(enumInputPort) == _FALSE) && (ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT0) == _BIT0))
    {
        ScalerDpMacStreamRxCRCCalculate_EXINT0(enumInputPort);
    }

    if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT0) == 0x00)
    {
        ScalerDpMacStreamRxClrCRCCalculate_EXINT0(enumInputPort);

        // Reset the CRC value of DPCD
        CLR_DP_AUX_RX2_CRC_VALUE_EXINT0();

#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
        // Reset the CRC value of DSC's DPCD
        CLR_DP_AUX_RX2_DSC_CRC_VALUE_EXINT0();
#endif
    }

    // Clear TEST_CRC_COUNT
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x46, 0x20);
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//-------------------------------------------------------
// Description  : Panel Peplay Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdPrModeHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0xB0, _BIT1) == _BIT1)
    {
        SET_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE();
    }
    else
    {
        CLR_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE();

        if(ScalerDpMacStreamRxGetCRCCalculate_EXINT0(enumInputPort) == _FALSE)
        {
            ScalerDpMacStreamRxPRModeCrcCalculateEnable_EXINT0(enumInputPort, _DISABLE);
        }
    }
}
#endif

#if((_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
//-------------------------------------------------------
// Description  : Cable ID Sync Handler
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2DpcdCableIDSyncHandler_EXINT0(void)
{
    // Update DPCD 2217h to Sync DPCD 110h
    ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x00, 0x22, 0x17, ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x10));
}
#endif

//-------------------------------------------------------
// Description  : Wait for Aux Mac State switch to RCV_STANBY
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx2WaitRcv_EXINT0(void)
{
    BYTE ucCntTemp = 0;

    for(ucCntTemp = 0; ucCntTemp < 60; ucCntTemp++)
    {
        DELAY_5US_EXINT();

        if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_STATUS, (_BIT10 | _BIT9 | _BIT8)) == _BIT8)
        {
            break;
        }
    }
}

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2FecHanlder_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    BYTE ucDpAuxRxDpcd120 = ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x20);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Clear Flag
    ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_281);

    // Enable 00281h~00282h Force Defer
    ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_281, _ENABLE);
#else
    // Enable 00281h~00282h Force Defer
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT0, _BIT0);
#endif

    if((BYTE)((ucDpAuxRxDpcd120 & _BIT0) == _BIT0) != ScalerDpMacDphyRxGetFecDecodeStatus_EXINT0(enumInputPort))
    {
        // FEC Ready 00120h[0] IRQ Source FEC Ready
        if((ucDpAuxRxDpcd120 & _BIT0) == _BIT0)
        {
            ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _ENABLE);
        }
        else
        {
            ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _DISABLE);
        }
    }

    // Aggregated Error 120h Bit6 Write IRQ
    if((ucDpAuxRxDpcd120 & _BIT6) == _BIT6)
    {
        // Enable Aggregated Mode
        ScalerDpMacDphyRxFecEnableAggregatedErrorCount_EXINT0(enumInputPort, _ENABLE);
    }
    else
    {
        // Disable Aggregated Mode
        ScalerDpMacDphyRxFecEnableAggregatedErrorCount_EXINT0(enumInputPort, _DISABLE);
    }

    if((ucDpAuxRxDpcd120 & (_BIT3 | _BIT2 | _BIT1)) == 0x00)
    {
        // Clear FEC Error Count
        ScalerDpMacDphyRxResetFecErrorCount_EXINT0(enumInputPort);

        // Clear FEC DPCD Error Count
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x81, 0x00);
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x02, 0x82, 0x00);
    }

    // Error Count Select
    ScalerDpMacDphyRxFecErrorCountSelect_EXINT0(enumInputPort, ((ucDpAuxRxDpcd120 & (_BIT3 | _BIT2 | _BIT1)) << 3));

    // Lane or Decoder Select
    ScalerDpMacDphyRxFecLaneSelect_EXINT0(enumInputPort, ((ucDpAuxRxDpcd120 & (_BIT5 | _BIT4)) >> 2));
}
#endif

//--------------------------------------------------
// Description  : DP Error Counter Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2ErrorCounterDisable_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    // Disable IRQ for Error Counter
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _DISABLE);
    ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _DISABLE);
#else
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, 0x00);
    Scaler32SetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT9, 0x00);
#endif

    // Disable 8B/10B Error Counter
    ScalerDpMacDphyRxDecodeErrorCountOff_EXINT0(enumInputPort);

    // Set DPCD 0x210-0x217 = 0x00
    ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x00, 0x02, 0x10, 8);
}

//--------------------------------------------------
// Description  : DP Error Counter Enable
// Input Value  : DP Link Training Type
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

    // Enable DPCD Error Count Valid Flag
    switch(g_enumDpAuxRx2LaneCount)
    {
        case _DP_ONE_LANE:

            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

            break;

        default:
        case _DP_FOUR_LANE:

            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);
            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~_BIT7, _BIT7);
            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

            break;
    }

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        // Enable 8B/10B Error Counter
        ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B);
    }

    // Enable Read Error Counter IRQ, Clear IRQ Flag
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_210);
    ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
    ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(_AUX_RX_DPCD_WILDCARD_210, _ENABLE);
#else
    Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT1, _BIT1);
    Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);
    Scaler32SetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT9, _BIT9);
#endif
}

//--------------------------------------------------
// Description  : Check DP Source OUI for Specific Action
// Input Value  : Action that Need to Check Specific Source OUI
// Output Value : Whether Specific Source OUI Hit or Not
//--------------------------------------------------
BYTE ScalerDpAuxRx2CheckSourceOUI_EXINT0(EnumDpAuxRxCheckSourceOUI enumDpAuxRx2CheckSourceOUI)
{
    switch(enumDpAuxRx2CheckSourceOUI)
    {
#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
        case _LT_TP1_PERMIT_SWING_LEVEL_0:
        {
            BYTE pucSrcIeeeOuiUser[9] = _SRC_IEEE_OUI_APPLE_2017_PRO_15INCH_IDENTIFY_STRING;

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 9; ucLoopIndex++)
            {
                if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x03, ucLoopIndex)) != (pucSrcIeeeOuiUser[ucLoopIndex]))
                {
                    return _FALSE;
                }
            }

            return _TRUE;
        }
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Aux PHY Swap Setting
// Input Value  : TypeC PinAssignment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2TypeCPinAssert_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Disable Aux DPHY Swap
        Scaler32SetBit_EXINT0(PB1A001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

        SET_DP_AUX_RX2_RECEIVE_MODE(_AUX_DIFF_MODE);
    }
    else if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
    {
        if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Enable Aux DPHY Swap
            Scaler32SetBit_EXINT0(PB1A001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

            SET_DP_AUX_RX2_RECEIVE_MODE(_AUX_PN_SWAP_MODE);
        }
        else
        {
            // Disable Aux DPHY Swap
            Scaler32SetBit_EXINT0(PB1A001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX2_RECEIVE_MODE(_AUX_DIFF_MODE);
        }
    }
    else
    {
        if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Disable Aux DPHY Swap
            Scaler32SetBit_EXINT0(PB1A001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX2_RECEIVE_MODE(_AUX_DIFF_MODE);
        }
        else
        {
            // Enable Aux DPHY Swap
            Scaler32SetBit_EXINT0(PB1A001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

            SET_DP_AUX_RX2_RECEIVE_MODE(_AUX_PN_SWAP_MODE);
        }
    }
}

#if((_D2_DP_MST_PORT_SUPPORT == _ON) || (_DP_HDCP2_RX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Reset Dp Rx HDCP info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2HdcpResetDpcdInfo_EXINT0(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear RxStatus REAUTH_REQ and Link Intergrity Failure for HDCP 2.2
    ScalerDpAuxRx2SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) & 0xE0));
#endif

    if((ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x06, 0x80, 0x2A) != 0x00) || (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x06, 0x80, 0x2B) != 0x00))
    {
        // DPCD [0x68014 ~ 0x68027]
        ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x06, 0x80, 0x14, 20);

        // DPCD [0x68029 ~ 0x6803A]
        ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x06, 0x80, 0x29, 18);
    }
}
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType)
{
    switch(enumBStatusType)
    {
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(0x00, 0x02, 0x01, ~_BIT2, _BIT2);

    ScalerDpAuxRx2HpdIrqAssert_EXINT0();
}

//--------------------------------------------------
// Description  : DP HDCP2.2 M' Read Defer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetMPrimeReadDefer_EXINT0(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    if(bEnable == _ENABLE)
    {
        // Enable 69473h Force Defer
        ScalerDpAuxRx2SetDpcdForceDeferEnable_EXINT0(0x06, 0x94, 0x73, 1, _ENABLE);
    }
    else
    {
        // Disable 69473h Force Defer
        ScalerDpAuxRx2SetDpcdForceDeferEnable_EXINT0(0x06, 0x94, 0x73, 1, _DISABLE);
    }
#else
    if(bEnable == _ENABLE)
    {
        // Enable 69473h Force Defer
        Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Disable 69473h Force Defer
        Scaler32SetBit_EXINT0(PB1A002_40_DPCD_MISC_CTRL, ~_BIT5, 0x00);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2HpdIrqAssert_EXINT0(void)
{
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON)))

    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_EXINT0(enumInputPort);

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    if(ScalerTypeCPcbxTypeCxMapping_EXINT0(enumTypeCPcbPort) != _EMB_TYPE_C_NOT_EXIST)
    {
        if(ScalerDpRxGetHotPlugStatus_EXINT0(enumInputPort) == _HIGH)
        {
            ScalerTypeCPdPushHpd_EXINT0(enumInputPort, _PD_HPD_IRQ, 2);
        }
    }
    else
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
    {
        if(ScalerDpRxGetHotPlugStatus_EXINT0(enumInputPort) == _HIGH)
        {
            ScalerTypeCTcpmPdPushHpd_EXINT0(enumTypeCPcbPort, _PD_HPD_IRQ, 2);
        }
    }
    else
#endif
#endif
    {
        if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
        {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
            SET_DP_AUX_RX2_HPD_IRQ_ASSERT_T2_EVENT();
#else
            EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

#if(_DP_TX_SUPPORT == _ON)
            // Disable IRQs that take too long
            BYTE ucBackUp2 = ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6);
            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
            }

            PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

            // Default = 750us
            switch(GET_DP_IRQ_TIME_10US())
            {
                case 55:
                    DELAY_XUS_EXINT(500);
                    break;

                case 60:
                    DELAY_XUS_EXINT(546);
                    break;

                case 65:
                    DELAY_XUS_EXINT(588);
                    break;

                case 70:
                    DELAY_XUS_EXINT(634);
                    break;

                case 75:
                default:
                    DELAY_XUS_EXINT(682);
                    break;

                case 80:
                    DELAY_XUS_EXINT(728);
                    break;

                case 85:
                    DELAY_XUS_EXINT(768);
                    break;

                case 90:
                    DELAY_XUS_EXINT(816);
                    break;

                case 95:
                    DELAY_XUS_EXINT(862);
                    break;
            }

            PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_AUX_RX2_AUTO_MODE_EXINT();
            }

#if(_DP_TX_SUPPORT == _ON)
            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp2);
#endif
#endif
        }
    }
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Type Value Reset
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2Hdcp2TypeValueReset_EXINT0(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Reset 69494h Type Value
    ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x06, 0x94, 0x94, 0x00);
#else
    // Disable Type INT
    Scaler32SetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, ~_BIT13, 0x00);

    // Reset 69494h Type Value. Be Careful. If Clear this Address which is Writed by Source, Must Disable INT Function First.
    ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(0x06, 0x94, 0x94, 0x00);

    // Clear Type INT Flag
    Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT13);

    // Enable Type INT
    Scaler32SetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, ~_BIT13, _BIT13);
#endif
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Stream ID Type Value Reset
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2Hdcp2StreamIDTypeReset_EXINT0(void)
{
    // Reset Stream ID Type IRQ
    ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(0x06, HIBYTE(g_usDpAuxRx2StreamIdAddrEnd), LOBYTE(g_usDpAuxRx2StreamIdAddrEnd), 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);

    g_usDpAuxRx2StreamIdAddrEnd = 0x0000;
}
#endif

//--------------------------------------------------
// Description  : Get HDCP 2.2 Message ID Code
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
BYTE ScalerDpAuxRx2Hdcp2GetMessageID_EXINT0(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Write Ake Initial
    if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x90, 0x0A, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x06, 0x94, 0x93, ~(_BIT4 | _BIT3), 0x00);

        return _HDCP22_AKE_INIT;
    }
    // Write AKE No Store Km
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x92, 0x9F, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        return _HDCP22_AKE_NO_STORED_KM;
    }
    // Read HPrime
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x92, 0xDF, 1, _DP_AUX_RX_DPCD_INT_READ) == _TRUE)
    {
        ScalerDpAuxRx2SetDpcdBitValue_EXINT0(0x06, 0x94, 0x93, ~_BIT1, 0x00);

        if(GET_DP_HDCP2_RX2_AKE_NO_STORED_KM_DONE() == _TRUE)
        {
            CLR_DP_HDCP2_RX2_AKE_NO_STORED_KM_DONE();

            return _HDCP22_AKE_SEND_PAIRING_INFO;
        }
    }
    // Write AKE Store Km
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x92, 0xBF, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        return _HDCP22_AKE_STORED_KM;
    }
    // Write Locality Check Initial
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x92, 0xF7, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        return _HDCP22_LC_INIT;
    }
    // Write SEK Send
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x93, 0x2F, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        return _HDCP22_SKE_SEND_EKS;
    }
    // Write Cipher Type
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, 0x94, 0x94, 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        return _HDCP22_SKE_TYPE_VALUE;
    }
    // Write Stream ID Type
    else if(ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(0x06, HIBYTE(g_usDpAuxRx2StreamIdAddrEnd), LOBYTE(g_usDpAuxRx2StreamIdAddrEnd), 1, _DP_AUX_RX_DPCD_INT_WRITE) == _TRUE)
    {
        ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(0x06, HIBYTE(g_usDpAuxRx2StreamIdAddrEnd), LOBYTE(g_usDpAuxRx2StreamIdAddrEnd), 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);

        return _HDCP22_REPEATERAUTH_STREAM_MANAGE;
    }

    return _HDCP22_NONE;
#else
    // Write Ake Initial
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT3) == _BIT3) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT3) == _BIT3))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT3);

        return _HDCP22_AKE_INIT;
    }

    // Write AKE No Store Km
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT7) == _BIT7) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT7) == _BIT7))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT7);

        return _HDCP22_AKE_NO_STORED_KM;
    }

    // Read HPrime
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT1) == _BIT1) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT1) == _BIT1))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT1);

        if(GET_DP_HDCP2_RX2_AKE_NO_STORED_KM_DONE() == _TRUE)
        {
            CLR_DP_HDCP2_RX2_AKE_NO_STORED_KM_DONE();

            return _HDCP22_AKE_SEND_PAIRING_INFO;
        }
        else
        {
            return _HDCP22_NONE;
        }
    }

    // Write AKE Store Km
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT6) == _BIT6) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT6) == _BIT6))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT6);

        return _HDCP22_AKE_STORED_KM;
    }

    // Write Locality Check Initial
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT4) == _BIT4) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT4) == _BIT4))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT4);

        return _HDCP22_LC_INIT;
    }

    // Write SEK Send
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT12) == _BIT12) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT12) == _BIT12))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT12);

        return _HDCP22_SKE_SEND_EKS;
    }

    // Write Cipher Type
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT13) == _BIT13) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT13) == _BIT13))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT13);

        return _HDCP22_SKE_TYPE_VALUE;
    }

    // Write Stream ID Type
    if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT5) == _BIT5) && (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT5) == _BIT5))
    {
        // CLR Flag
        Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT5);

        return _HDCP22_REPEATERAUTH_STREAM_MANAGE;
    }

    return _HDCP22_NONE;
#endif
}
#endif

#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DscEnable_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch_EXINT0(enumInputPort);

    if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x60, _BIT0) == _BIT0)
    {
        if((ScalerDpMacStreamRxGetFifoWDStatus_EXINT0(enumInputPort) == _ENABLE) && (ScalerDscDecoderDpMacRxxGetDscDecoderMac_EXINT0(enumDpMacSel) == _DSC_MAC_NONE))
        {
            ScalerDpMacStreamRxDscSetStreamWD_EXINT0(enumInputPort, _ENABLE);

            ScalerDpMacStreamRxDscSetStreamIRQ_EXINT0(enumInputPort, _ENABLE);
        }
    }
    else
    {
        if(ScalerDscDecoderDpMacRxxGetDscDecoderMac_EXINT0(enumDpMacSel) != _DSC_MAC_NONE)
        {
            // Set D Domain Region Free run/ Force to Background
            ScalerDDomainResetDDomainRgn(ScalerDpMacStreamRxGetForceBackgroundPath_EXINT0(enumInputPort));

#if(_AUDIO_SUPPORT == _ON)
            // Disable INT for Auido and Reset Function
            ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

            // Disable Audio FSM
            ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

            // Set DP Receive Port0 Out of Sync
            ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

            // Set DP Stream Regen Out of Sync
            ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

            // Enable DSC Change Flag When DSC Detect VB-ID[6] Change
            ScalerDpMacDscRxDscStreamSetChange_EXINT0(enumDpMacSel, _ENABLE);

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Set DPTx Force Output Idle Pattern
                ScalerDpMacTxForceIdlePattern_EXINT0();
            }
#endif
        }
        else
        {
            ScalerDpMacStreamRxDscSetStreamWD_EXINT0(enumInputPort, _DISABLE);

            ScalerDpMacStreamRxDscSetStreamIRQ_EXINT0(enumInputPort, _DISABLE);
        }
    }
}
#endif // End of #if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DPCD Wildcard function setting
// Input Value  : WildcardId, DPCD address range, address mask or len
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdWildCardSetting_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask)
{
    DWORD ulDpcdWildCard_Addr = 0;

    // Calculate WildCard_Addr
    ulDpcdWildCard_Addr = _REG_DP_AUX_RX2_WILDCARD_ADDR + (BYTE) enumDpAuxRxDpcdWildCardId * 4;

    // Setting len and Dpcd Addr
    Scaler32SetBit_EXINT0(ulDpcdWildCard_Addr, ~(_BIT(31, 24) | _BIT(19, 0)), TO_DWORD(enumDpAuxRxDpcdWildCardBitMask, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));
}

//--------------------------------------------------
// Description  : DPCD Wildcard function Set Force Defer Enable
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable)
{
    DWORD ulDpcdWildCard_Addr = 0;

    // Calculate WildCard_Addr
    ulDpcdWildCard_Addr = _REG_DP_AUX_RX2_WILDCARD_ADDR + (BYTE) enumDpAuxRxDpcdWildCardId * 4;

    // Setting Force Defer Enable
    Scaler32SetBit_EXINT0(ulDpcdWildCard_Addr, ~_BIT23, ((bEnable) ? _BIT23 : 0x00));
}

//--------------------------------------------------
// Description  : DPCD Wildcard function Get Force Defer Enable
// Input Value  : wildcardId
// Output Value : Force Defer Enable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdWildCardForceDeferEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    DWORD ulDpcdWildCard_Addr = 0;

    // Calculate WildCard_Addr
    ulDpcdWildCard_Addr = _REG_DP_AUX_RX2_WILDCARD_ADDR + (BYTE) enumDpAuxRxDpcdWildCardId * 4;

    // Return Force Defer
    return (Scaler32GetBit_EXINT0(ulDpcdWildCard_Addr, _BIT23) == _BIT23);
}

//--------------------------------------------------
// Description  : DPCD Wildcard int enable
// Input Value  : WildcardId, enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    // Clear Wildcard DPCD INT Flag
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG, usDpcdWildCardFlag);

    // Enable/Disable Wildcard DPCD INT
    if(bEnable == _ENABLE)
    {
        Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_EN, ~usDpcdWildCardFlag, usDpcdWildCardFlag);
    }
    else
    {
        Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_EN, ~usDpcdWildCardFlag, 0x00);
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int enable
// Input Value  : WildcardId, enable/disable
// Output Value : WildCard Int Enable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdWildCardIntEnable_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    return (Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_EN, usDpcdWildCardFlag) == usDpcdWildCardFlag);
}

//--------------------------------------------------
// Description  : DPCD Wildcard int check
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdWildCardIntCheck_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    return (Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG, usDpcdWildCardFlag) == usDpcdWildCardFlag);
}

//--------------------------------------------------
// Description  : DPCD Wildcard int clear
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    // Clear Wildcard DPCD INT Flag
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG, usDpcdWildCardFlag);
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : WildCard Int Handler
// Input Value  : WildCard Flag
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdWildCardIntHandler_EXINT0(DWORD ulDpcdWildCardFlag)
{
    DWORD ulDpcdWildCardId = 0;

    while(ulDpcdWildCardFlag > _BIT0)
    {
        ulDpcdWildCardFlag /= 2;
        ulDpcdWildCardId++;
    }

    switch((EnumDpAuxRxDpcdWildCardId) ulDpcdWildCardId)
    {
#if(_DP_AUX_RX_DPCD_WILDCARD_00210_SUPPORT == _ON)
        case _AUX_RX_DPCD_WILDCARD_210:
            // Clear Flag
            ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_210);

            ScalerDpAuxRx2DpcdSymbolErrorCountHandler_EXINT0();

            return _TRUE;
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_00281_SUPPORT == _ON)
        case _AUX_RX_DPCD_WILDCARD_281:
            // Clear Flag
            ScalerDpAuxRx2DpcdWildCardIntClr_EXINT0(_AUX_RX_DPCD_WILDCARD_281);

            ScalerDpAuxRx2DpcdFecErrorCount_EXINT0();

            return _TRUE;
#endif
#endif

        default:
            // Clear Wildcard DPCD INT Flag
            Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_WILDCARD_ADDR_IRQ_FLAG, 0xFFFFFFFF);

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DPCD Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemapSetting_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen)
{
    DWORD ulDpcdRemap_Addr = 0;

    // Calculate Remap_Addr
    ulDpcdRemap_Addr = PB1A005_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemapId * 4;

    // Setting len and Dpcd Addr
    Scaler32SetBit_EXINT0(ulDpcdRemap_Addr, ~(_BIT(31, 23) | _BIT(19, 0)), (_BIT23 | TO_DWORD(ucDpcdRemapLen, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL)));

    // Reset Remap Dpcd Value
    ScalerDpAuxRx2DpcdGroupReset_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdRemapLen);
}

//--------------------------------------------------
// Description  : Get DPCD Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdRemapEnable_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    DWORD ulDpcdRemap_Addr = 0;

    // Calculate Remap_Addr
    ulDpcdRemap_Addr = PB1A005_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemapId * 4;

    return (Scaler32GetBit_EXINT0(ulDpcdRemap_Addr, _BIT23) == _BIT23);
}

//--------------------------------------------------
// Description  : Clear DPCD Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemapReset_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    DWORD ulDpcdRemapBackup = 0x00;
    BYTE ucDpcdAddrH = 0x00;
    BYTE ucDpcdAddrM = 0x00;
    BYTE ucDpcdAddrL = 0x00;
    BYTE ucDpcdLen = 0x00;
    DWORD ulDpcdRemap_Addr = 0;

    // Calculate Remap_Addr
    ulDpcdRemap_Addr = PB1A005_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemapId * 4;

    // Backup Dpcd Remap Dpcd Addr
    ulDpcdRemapBackup = Scaler32GetDWord_EXINT0(ulDpcdRemap_Addr);
    ucDpcdAddrH = (BYTE)((ulDpcdRemapBackup >> 16) & 0x0F);
    ucDpcdAddrM = (BYTE)((ulDpcdRemapBackup >> 8) & 0xFF);
    ucDpcdAddrL = (BYTE)(ulDpcdRemapBackup & 0xFF);
    ucDpcdLen = (BYTE)(ulDpcdRemapBackup >> 24);

    // Reset Remap Dpcd Value
    ScalerDpAuxRx2DpcdGroupReset_EXINT0(ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL, ucDpcdLen);

    Scaler32SetBit_EXINT0(ulDpcdRemap_Addr, ~(_BIT(31, 23) | _BIT(19, 0)), 0x00);
}

//--------------------------------------------------
// Description  : DPCD Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemapIntCheck_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    WORD usDpcdRemapFlag = 0;

    // Calculate Remap_Addr
    usDpcdRemapFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdRemapId);

    return (Scaler32GetBit_EXINT0(PB1A005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, usDpcdRemapFlag) == usDpcdRemapFlag);
}

//--------------------------------------------------
// Description  : DPCD Remapping int clr
// Input Value  : remapId
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemapIntClr_EXINT0(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    WORD usDpcdRemapFlag = 0;

    // Calculate Remap_Addr
    usDpcdRemapFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdRemapId);

    // Clear Remap DPCD INT Flag
    Scaler32SetDWord_EXINT0(PB1A005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, usDpcdRemapFlag);
}

//--------------------------------------------------
// Description  : Remap Int Handler
// Input Value  : Remap Flag
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemapIntHandler_EXINT0(DWORD ulDpcdRemapFlag)
{
    DWORD ulDpcdRemapId = 0;

    while(ulDpcdRemapFlag > _BIT0)
    {
        ulDpcdRemapFlag /= 2;
        ulDpcdRemapId ++;
    }

    switch((EnumDpAuxRxDpcdRemapId) ulDpcdRemapId)
    {
        default:
            // Clear Remap DPCD INT Flag
            Scaler32SetDWord_EXINT0(PB1A005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, 0xFFFFFFFF);

            return _FALSE;
    }
}
#else
//--------------------------------------------------
// Description  : DPCD 32B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap32BSetting_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcd_Addr = (((DWORD)ucDpcdAccessPortH << 16) | (ucDpcdAccessPortM << 8) | (ucDpcdAccessPortL));
    DWORD ulDpcdRemapOffset_Addr = 0;

    DWORD ulDcpd_Offset = 0;
    DWORD ulDpcdRemapStart_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB1A001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        // Shift Dpcd Addr to your input
        ulDpcdRemapStart_Addr = 0x03100 + (BYTE) enumDpAuxRxDpcdRemap32BId * 32;

        // Calculate Offset
        if(ulDpcd_Addr < ulDpcdRemapStart_Addr)
        {
            ulDcpd_Offset = 0xFFFFF - ulDpcdRemapStart_Addr + ulDpcd_Addr + 1;
        }
        else
        {
            ulDcpd_Offset = ulDpcd_Addr - ulDpcdRemapStart_Addr;
        }

        // Enable Remap & Input Offset & RW Enable
        if(enumDpAuxRxDpcdAttr == _AUX_RX_DPCD_ATTR_RW)
        {
            Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | _BIT22 | ulDcpd_Offset));
        }
        else
        {
            Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | ulDcpd_Offset));
        }
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap16BSetting_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcd_Addr = (((DWORD)ucDpcdAccessPortH << 16) | (ucDpcdAccessPortM << 8) | (ucDpcdAccessPortL));
    DWORD ulDpcdRemapOffset_Addr = PB1A001_50_DP_MANUAL_DPCD_REMAP_ADDR4;

    DWORD ulDcpd_Offset = 0;
    DWORD ulDpcdRemapStart_Addr = 0x694A0;

    if(enumDpAuxRxDpcdRemap16BId < 2)
    {
        // Calculate Offset
        if(ulDpcd_Addr < ulDpcdRemapStart_Addr)
        {
            ulDcpd_Offset = 0xFFFFF - ulDpcdRemapStart_Addr + ulDpcd_Addr + 1;
        }
        else
        {
            ulDcpd_Offset = ulDpcd_Addr - ulDpcdRemapStart_Addr;
        }

        // Enable Remap & Input Offset & RW Enable
        if(enumDpAuxRxDpcdAttr == _AUX_RX_DPCD_ATTR_RW)
        {
            Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | _BIT22 | ulDcpd_Offset));
        }
        else
        {
            Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | ulDcpd_Offset));
        }
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap8BSetting_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcd_Addr = (((DWORD)ucDpcdAccessPortH << 16) | (ucDpcdAccessPortM << 8) | (ucDpcdAccessPortL));
    DWORD ulDpcdRemapOffset_Addr = 0;

    DWORD ulDcpd_Offset = 0;
    DWORD ulDpcdRemapStart_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        if(enumDpAuxRxDpcdRemap8BId < 2)
        {
            // Calculate Remap_Addr
            ulDpcdRemapOffset_Addr = PB1A001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

            // Shift Dpcd Addr to your input
            ulDpcdRemapStart_Addr = 0x694B0 + (BYTE) enumDpAuxRxDpcdRemap8BId * 8;
        }
        else
        {
            // Calculate Remap_Addr
            ulDpcdRemapOffset_Addr = PB1A001_5C_DP_MANUAL_DPCD_REMAP_ADDR7 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

            // Shift Dpcd Addr to your input
            ulDpcdRemapStart_Addr = 0x00320 + (BYTE) enumDpAuxRxDpcdRemap8BId * 8;
        }

        // Calculate Offset
        if(ulDpcd_Addr < ulDpcdRemapStart_Addr)
        {
            ulDcpd_Offset = 0xFFFFF - ulDpcdRemapStart_Addr + ulDpcd_Addr + 1;
        }
        else
        {
            ulDcpd_Offset = ulDpcd_Addr - ulDpcdRemapStart_Addr;
        }

        // Enable Remap & Input Offset & RW Enable
        if(enumDpAuxRxDpcdAttr == _AUX_RX_DPCD_ATTR_RW)
        {
            Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | _BIT22 | ulDcpd_Offset));
        }
        else
        {
            Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | ulDcpd_Offset));
        }
    }
}

//--------------------------------------------------
// Description  : Get DPCD 32B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdRemap32BEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB1A001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        return (Scaler32GetBit_EXINT0(ulDpcdRemapOffset_Addr, _BIT23) == _BIT23);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 16B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdRemap16BEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        return (Scaler32GetBit_EXINT0(PB1A001_50_DP_MANUAL_DPCD_REMAP_ADDR4, _BIT23) == _BIT23);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 8B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx2GetDpcdRemap8BEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB1A001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

        return (Scaler32GetBit_EXINT0(ulDpcdRemapOffset_Addr, _BIT23) == _BIT23);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 32B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap32BReset_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB1A001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        // Reset Remap HW(offset/wr/En/irq_en/irq_offset)
        Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT31 | _BIT(28, 22) | _BIT(19, 0)), 0x00);
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 16B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap16BReset_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        // Reset Remap HW(offset/wr/En/irq_en/irq_offset)
        Scaler32SetBit_EXINT0(PB1A001_50_DP_MANUAL_DPCD_REMAP_ADDR4, ~(_BIT31 | _BIT(28, 22) | _BIT(19, 0)), 0x00);
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 8B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap8BReset_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB1A001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

        // Reset Remap HW(offset/wr/En/irq_en/irq_offset)
        Scaler32SetBit_EXINT0(ulDpcdRemapOffset_Addr, ~(_BIT31 | _BIT(28, 22) | _BIT(19, 0)), 0x00);
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap32BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    BYTE ucDpcdRemapFlag = 0;
    DWORD ulDpcdRemapIrqEn_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapIrqEn_Addr = PB1A001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        // Calculate DpcdRemapFlag
        ucDpcdRemapFlag = ((BYTE)(_BIT0) << enumDpAuxRxDpcdRemap32BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ucDpcdRemapFlag);

        // Enable/Disable dpcd_remap_irq and Set dpcd_remap_irq Bit Offset
        Scaler32SetBit_EXINT0(ulDpcdRemapIrqEn_Addr, ~(_BIT31 | _BIT(28, 24)), TO_DWORD((((BYTE) (bEnable) << 7)) | ucDpcdRemapIrqBitOffset, 0x00, 0x00, 0x00));
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap16BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        // Clear dpcd_remap_irq
        Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, _BIT4);

        // Enable/Disable dpcd_remap_irq and Set dpcd_remap_irq Bit Offset
        Scaler32SetBit_EXINT0(PB1A001_50_DP_MANUAL_DPCD_REMAP_ADDR4, ~(_BIT31 | _BIT(28, 24)), TO_DWORD((((BYTE) (bEnable) << 7)) | ucDpcdRemapIrqBitOffset, 0x00, 0x00, 0x00));
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap8BIntEnable_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    BYTE ucDpcdRemapFlag = 0;
    DWORD ulDpcdRemapIrqEn_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapIrqEn_Addr = PB1A001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

        // Calculate DpcdRemapFlag
        ucDpcdRemapFlag = ((BYTE)(_BIT5) << enumDpAuxRxDpcdRemap8BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ucDpcdRemapFlag);

        // Enable/Disable dpcd_remap_irq and Set dpcd_remap_irq Bit Offset
        Scaler32SetBit_EXINT0(ulDpcdRemapIrqEn_Addr, ~(_BIT31 | _BIT(28, 24)), TO_DWORD((((BYTE) (bEnable) << 7)) | ucDpcdRemapIrqBitOffset, 0x00, 0x00, 0x00));
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemap32BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT0) << enumDpAuxRxDpcdRemap32BId);

        return (Scaler32GetBit_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag) == ulDpcdRemapFlag);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemap16BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        return (Scaler32GetBit_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, _BIT4) == _BIT4);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemap8BIntCheck_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT5) << enumDpAuxRxDpcdRemap8BId);

        return (Scaler32GetBit_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag) == ulDpcdRemapFlag);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap32BIntClr_EXINT0(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT0) << enumDpAuxRxDpcdRemap32BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag);
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap16BIntClr_EXINT0(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 4)
    {
        // Clear dpcd_remap_irq
        Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, _BIT4);
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdRemap8BIntClr_EXINT0(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT5) << enumDpAuxRxDpcdRemap8BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag);
    }
}

//--------------------------------------------------
// Description  : Remap Int Handler
// Input Value  : Remap Flag
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemap32BIntHandler_EXINT0(DWORD ulDpcdRemapFlag)
{
    DWORD ulDpcdRemapId = 0;

    while(ulDpcdRemapFlag > _BIT0)
    {
        ulDpcdRemapFlag /= 2;
        ulDpcdRemapId ++;
    }

    switch((EnumDpAuxRxDpcdRemap32BId) ulDpcdRemapId)
    {
        default:
            // Clear Remap DPCD INT Flag
            Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, 0xFFFFFFFF);

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Remap Int Handler
// Input Value  : Remap Flag
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemap16BIntHandler_EXINT0(DWORD ulDpcdRemapFlag)
{
    DWORD ulDpcdRemapId = 0;

    while(ulDpcdRemapFlag > _BIT0)
    {
        ulDpcdRemapFlag /= 2;
        ulDpcdRemapId ++;
    }

    switch((EnumDpAuxRxDpcdRemap16BId) ulDpcdRemapId)
    {
        default:
            // Clear Remap DPCD INT Flag
            Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, 0xFFFFFFFF);

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Remap Int Handler
// Input Value  : Remap Flag
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx2DpcdRemap8BIntHandler_EXINT0(DWORD ulDpcdRemapFlag)
{
    DWORD ulDpcdRemapId = 0;

    while(ulDpcdRemapFlag > _BIT0)
    {
        ulDpcdRemapFlag /= 2;
        ulDpcdRemapId ++;
    }

    switch((EnumDpAuxRxDpcdRemap8BId) ulDpcdRemapId)
    {
        default:
            // Clear Remap DPCD INT Flag
            Scaler32SetDWord_EXINT0(PB1A001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, 0xFFFFFFFF);

            return _FALSE;
    }
}
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Update PR Mode Error Statu DPCD 02020h
// Input Value  : EnumPRModeErrorStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdPRModeErrorStateUpdate_EXINT0(EnumPRModeErrorStatus enumPRModeErrorStatus)
{
    switch(enumPRModeErrorStatus)
    {
        case _DP_PR_MODE_CRC_ERROR:

            ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(0x00, 0x20, 0x20, _DP_PR_MODE_CRC_ERROR);

            // Set Panel Replay Error Status
            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x04, ~_BIT3, _BIT3);

            if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0xB0, _BIT5) == _BIT5)
            {
                ScalerDpAuxRx2HpdIrqAssert_EXINT0();
            }

            break;

        case _DP_PR_MODE_RFB_STORAGE_ERROR:

            ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(0x00, 0x20, 0x20, _DP_PR_MODE_RFB_STORAGE_ERROR);

            // Set Panel Replay Error Status
            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x04, ~_BIT3, _BIT3);

            if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0xB0, _BIT4) == _BIT4)
            {
                ScalerDpAuxRx2HpdIrqAssert_EXINT0();
            }

            break;

        case _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR:

            ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(0x00, 0x20, 0x20, _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR);

            // Set Panel Replay Error Status
            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x20, 0x04, ~_BIT3, _BIT3);

            if(ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(0x00, 0x01, 0xB0, _BIT3) == _BIT3)
            {
                ScalerDpAuxRx2HpdIrqAssert_EXINT0();
            }

            break;

        default:
            break;
    }
}
#endif

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DPCD update When coding type change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2SetAuxReadInterval_EXINT0(void)
{
    if(ScalerDpAuxRx2GetDpcdInfo_EXINT0(0x00, 0x01, 0x08) != _CODING_TYPE_128B132B)
    {
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x22, 0x16, 0x00);
    }
    else
    {
        ScalerDpAuxRx2SetDpcdValue_EXINT0(0x00, 0x22, 0x16, _DP_AUX_RX_DPCD_128B132B_TRAINING_AUX_RD_INTERVAL);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdPortAccessBackup_EXINT0(void)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

    while((Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT(2, 0)) != 0x00) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

    if(Scaler32GetBit_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3)
    {
        // Backup Addr
        g_ulDpAuxRx2Backup_EXINT0 = Scaler32GetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_OUTPUT_PORT);
    }
    else
#endif
    {
        // Backup Addr, Backup Auto Inc when _HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE = _DP_AUX_RX_MAC_DPCD_ACCESS_NORMAL
        g_ulDpAuxRx2Backup_EXINT0 = Scaler32GetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_ADDR_INPUT_PORT);
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    // Backup Auto Inc / Config & Data Sel
    g_ucDpAuxRx2AccessBackup_EXINT0 = Scaler32GetByte_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, 0x00) & (_BIT5 | _BIT4 | _BIT3);
#endif

    ScalerDpAuxRx2DpcdAutoIncEnable_EXINT0(_DISABLE);
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup Restore
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx2DpcdPortAccessBackupRestore_EXINT0(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }
#endif

    // Restore Addr, Restore Auto Inc when _HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE = _DP_AUX_RX_MAC_DPCD_ACCESS_NORMAL
    ScalerDpAuxRx2SetDpcdAccessAddr_EXINT0(g_ulDpAuxRx2Backup_EXINT0);

    // If WDINT is Set Dpcd Bit, Main Loop Part will process when exiting WDINT
    if(GET_DP_AUX_RX2_DPCD_UPDATE_PROTECT_WDINT() == _TRUE)
    {
        // Set Dpcd Data Value = Original Data and Set _BITX
        g_stDpAuxRx2DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData = ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & g_stDpAuxRx2DpcdUpdateProtect_WDINT.usDpAuxRxNotDpcdBit) | g_stDpAuxRx2DpcdUpdateProtect_WDINT.usDpAuxRxDpcdBit);

        // Set Dpcd Data
        Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, g_stDpAuxRx2DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData);
    }
    // If Main Loop is Set Dpcd Bit
    else if(GET_DP_AUX_RX2_DPCD_UPDATE_PROTECT() == _TRUE)
    {
        // Set Dpcd Data Value = Original Data and Set _BITX
        g_stDpAuxRx2DpcdUpdateProtect.usDpAuxRxDpcdData = ((ScalerDpAuxRx2GetDpcdAccessData_EXINT0() & g_stDpAuxRx2DpcdUpdateProtect.usDpAuxRxNotDpcdBit) | g_stDpAuxRx2DpcdUpdateProtect.usDpAuxRxDpcdBit);

        // Set Dpcd Data
        Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_DATA_INPUT_PORT, g_stDpAuxRx2DpcdUpdateProtect.usDpAuxRxDpcdData);
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    // Restore Auto Inc / Config & Data Sel
    Scaler32SetDWord_EXINT0(_REG_DP_AUX_RX2_DPCD_ACCESS_CONTROL, g_ucDpAuxRx2AccessBackup_EXINT0);
#endif

    ScalerMcuDelayDot2usPN();

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
#endif
}

#endif
