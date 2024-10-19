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
// ID Code      : ScalerDpAuxRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAuxRx/ScalerDpAuxRx.h"




#if(_DP_SUPPORT == _ON)
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
// Description  : DP Port Dx mapping to Rx
// Input Value  : Rx Port
// Output Value : Dx port
//--------------------------------------------------
EnumInputPort ScalerDpAuxRxRxDxMapping_EXINT0(EnumRx enumRx)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumRx)
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            if(_HW_D0_DP_AUX_RX_MAPPING == _RX0)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_AUX_RX_MAPPING == _RX0)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_AUX_RX_MAPPING == _RX0)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            if(_HW_D0_DP_AUX_RX_MAPPING == _RX1)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_AUX_RX_MAPPING == _RX1)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_AUX_RX_MAPPING == _RX1)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            if(_HW_D0_DP_AUX_RX_MAPPING == _RX2)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_AUX_RX_MAPPING == _RX2)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_AUX_RX_MAPPING == _RX2)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            enumInputPort = _D7_INPUT_PORT;

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            enumInputPort = _D8_INPUT_PORT;

            break;
#endif

        default:

            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerDpAuxRxDxRxMapping_EXINT0(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumRx = _HW_D0_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumRx = _HW_D1_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumRx = _HW_D2_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            enumRx = _HW_D7_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            enumRx = _HW_D8_DP_AUX_RX_MAPPING;
            break;
#endif
        default:

            break;
    }

    return enumRx;
}

//--------------------------------------------------
// Description  : DP Aux High Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHighPriorityIntHandler_EXINT0(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0HighPriorityIntHandler_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1HighPriorityIntHandler_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2HighPriorityIntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : DP Aux Low Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxLowPriorityIntHandler_EXINT0(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0LowPriorityIntHandler_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1LowPriorityIntHandler_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2LowPriorityIntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : DP Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpAuxRxJudgeHandler_EXINT0(void)
{
    bit bReturnValueD0 = _FALSE;
    bit bReturnValueD1 = _FALSE;
    bit bReturnValueD2 = _FALSE;
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    enumInputPort = enumInputPort;

#if(_DP_AUX_RX0_SUPPORT == _ON)

    // D0 DP Global IRQ
    if(GET_DP_AUX_RX0_GLOBAL_IRQ_FLAG() == _TRUE)
    {
        if(ScalerGetBit_EXINT(PFF_ED_MCU_CONTROL, _BIT1) == 0x00)
        {
            ScalerSetBit_EXINT(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _FLASH_CLK_PS_FAST_DIV);
        }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        if(g_stDpAuxRx0ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_NONE)
        {
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

            ScalerDpAuxRx0RequestAnalyze_EXINT0();

            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
        }

        if(g_stDpAuxRx0ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_I2C_FIXED_ADDR)
        {
            bReturnValueD0 = ScalerDpAuxRx0I2cIntCaseHandler_EXINT0();
        }
        else
        {
            bReturnValueD0 = ScalerDpAuxRx0DpcdIntCaseHandler_EXINT0();

            if(bReturnValueD0 != _TRUE)
            {
                if(g_stDpAuxRx0ReceiveBackup.enumReqType == _DP_AUX_RX_REQ_NATIVE_WRITE)
                {
                    bReturnValueD0 = ScalerDpAuxRx0DpcdWrite1ClearHandler_EXINT0();
                }
                else if(g_stDpAuxRx0ReceiveBackup.enumReqType == _DP_AUX_RX_REQ_NATIVE_READ)
                {
                    bReturnValueD0 = ScalerDpAuxRx0DpcdReadClearHandler_EXINT0();
                }
            }

            if(g_stDpAuxRx0ReceiveBackup.ulDpcdWildCardIrq != 0x00)
            {
                bReturnValueD0 |= ScalerDpAuxRx0DpcdWildCardIntHandler_EXINT0(g_stDpAuxRx0ReceiveBackup.ulDpcdWildCardIrq);
            }

            if(g_stDpAuxRx0ReceiveBackup.ulDpcdRemapIrq != 0x00)
            {
                bReturnValueD0 |= ScalerDpAuxRx0DpcdRemapIntHandler_EXINT0(g_stDpAuxRx0ReceiveBackup.ulDpcdRemapIrq);
            }
        }
#else
        // Aux Manual Mode
        if(ScalerDpAuxRx0PreIntHandler_EXINT0() == _TRUE)
        {
            enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX0);

            // If source i2c_over_aux cmd hit slave addr = 50
            if(Scaler32GetBit_EXINT0(PB18002_D8_IIC_STATUS, _BIT8) == _BIT8)
            {
                // Clear flag
                Scaler32SetDWord_EXINT0(PB18002_D8_IIC_STATUS, _BIT8);

                ScalerDpAuxRx0EdidReadAddrOnlyProtect_EXINT0();

                bReturnValueD0 = _TRUE;
            }

            // Symbol Error Count Read IRQ
            if((Scaler32GetBit_EXINT0(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT9) == _BIT9) && (Scaler32GetBit_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9) == _BIT9))
            {
                // Clear IRQ Flag
                Scaler32SetDWord_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);

                ScalerDpAuxRx0DpcdSymbolErrorCountHandler_EXINT0();

                bReturnValueD0 = _TRUE;
            }
            else
            {
                // Reset Read Error Count Flag Beside Symbol Error Count 00210h ~ 00217h
                CLR_DP_AUX_RX0_SOURCE_READ_ERROR_COUNT();
            }

#if(_DP_RX_FEC_SUPPORT == _ON)
            // DPCD Write 00120h IRQ
            if((Scaler32GetBit_EXINT0(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT15) == _BIT15) && (Scaler32GetBit_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT15) == _BIT15))
            {
                // Clear 00120h IRQ
                Scaler32SetDWord_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT15);

                ScalerDpAuxRx0FecHanlder_EXINT0();

                bReturnValueD0 = _TRUE;
            }

            // FEC DCPD 00281h~00282h IRQ
            if((Scaler32GetBit_EXINT0(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT11) == _BIT11) && (Scaler32GetBit_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT11) == _BIT11))
            {
                // Clear FEC DCPD 00281h~00282h IRQ
                Scaler32SetDWord_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT11);

                ScalerDpAuxRx0DpcdFecErrorCount_EXINT0();

                bReturnValueD0 = _TRUE;
            }
#endif

            // Write Link Config Field into INT0
            if(Scaler32GetBit_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT31 | _BIT30 | _BIT29)) != 0x00)
            {
                ScalerDpAuxRx0DpcdLinkTrainingHandler_EXINT0();

                // Clear Flag
                Scaler32SetDWord_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT31 | _BIT30 | _BIT29));

                bReturnValueD0 = _TRUE;
            }

            // Write 00600h into INT0
            if(Scaler32GetBit_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT24) == _BIT24)
            {
                // Clear Flag
                Scaler32SetDWord_EXINT0(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT24);

                ScalerDpAuxRx0DpcdPowerStateHandler_EXINT0();

                bReturnValueD0 = _TRUE;
            }

            // Write 68xxxh into INT0
            if((Scaler32GetBit_EXINT0(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT16) == _BIT16) &&
               (Scaler32GetBit_EXINT0(PB18001_88_AUX_HDCP_IRQ_EN, _BIT16) == _BIT16))
            {
                // Clear Flag
                Scaler32SetDWord_EXINT0(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT16);

                // Clear Integrity Failure Flag
                ScalerDpMacDphyRxClearIntegrityFailureFlag_EXINT0(enumInputPort);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
                if(Scaler32GetBit_EXINT0(PB18001_80_AUX_HDCP_01, _BIT9))
                {
                    // Detect if V'(0x68027) is read by Source
                    if(Scaler32GetWord_EXINT0(PB18002_18_AUX_RX_ADDR, 0x00) == 0x8028)
                    {
                        ScalerDpHdcp14RxResetKsvFifoToFirst_EXINT0(enumInputPort);
                    }
                }
#endif
                if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // DP Mac Clock Select to Xtal Clock
                    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_XTAL_CLOCK);
                }

                bReturnValueD0 = _TRUE;
            }

            // Detect if Aksv(0x6800B) is Written by Source
            if((Scaler32GetBit_EXINT0(PB18001_88_AUX_HDCP_IRQ_EN, _BIT14) == _BIT14) &&
               (Scaler32GetBit_EXINT0(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT14) == _BIT14))
            {
                Scaler32SetDWord_EXINT0(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT14);

                ScalerDpAuxRx0DpcdHdcp14AksvHandler_EXINT0();

                bReturnValueD0 = _TRUE;
            }
        }
#endif
    }
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)

    // D1 DP Global IRQ
    if(GET_DP_AUX_RX1_GLOBAL_IRQ_FLAG() == _TRUE)
    {
        if(ScalerGetBit_EXINT(PFF_ED_MCU_CONTROL, _BIT1) == 0x00)
        {
            ScalerSetBit_EXINT(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _FLASH_CLK_PS_FAST_DIV);
        }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        if(g_stDpAuxRx1ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_NONE)
        {
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

            ScalerDpAuxRx1RequestAnalyze_EXINT0();

            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
        }

        if(g_stDpAuxRx1ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_I2C_FIXED_ADDR)
        {
            bReturnValueD1 = ScalerDpAuxRx1I2cIntCaseHandler_EXINT0();
        }
        else
        {
            bReturnValueD1 = ScalerDpAuxRx1DpcdIntCaseHandler_EXINT0();

            if(bReturnValueD1 != _TRUE)
            {
                if(g_stDpAuxRx1ReceiveBackup.enumReqType == _DP_AUX_RX_REQ_NATIVE_WRITE)
                {
                    bReturnValueD1 = ScalerDpAuxRx1DpcdWrite1ClearHandler_EXINT0();
                }
                else if(g_stDpAuxRx1ReceiveBackup.enumReqType == _DP_AUX_RX_REQ_NATIVE_READ)
                {
                    bReturnValueD1 = ScalerDpAuxRx1DpcdReadClearHandler_EXINT0();
                }
            }

            if(g_stDpAuxRx1ReceiveBackup.ulDpcdWildCardIrq != 0x00)
            {
                bReturnValueD1 |= ScalerDpAuxRx1DpcdWildCardIntHandler_EXINT0(g_stDpAuxRx1ReceiveBackup.ulDpcdWildCardIrq);
            }

            if(g_stDpAuxRx1ReceiveBackup.ulDpcdRemapIrq != 0x00)
            {
                bReturnValueD1 |= ScalerDpAuxRx1DpcdRemapIntHandler_EXINT0(g_stDpAuxRx1ReceiveBackup.ulDpcdRemapIrq);
            }
        }
#else
        // Aux Manual Mode
        if(ScalerDpAuxRx1PreIntHandler_EXINT0() == _TRUE)
        {
            enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX1);

            // If source i2c_over_aux cmd hit slave addr = 50
            if(Scaler32GetBit_EXINT0(PB19002_D8_IIC_STATUS, _BIT8) == _BIT8)
            {
                // Clear flag
                Scaler32SetDWord_EXINT0(PB19002_D8_IIC_STATUS, _BIT8);

                ScalerDpAuxRx1EdidReadAddrOnlyProtect_EXINT0();

                bReturnValueD1 = _TRUE;
            }

            // Symbol Error Count Read IRQ
            if((Scaler32GetBit_EXINT0(PB19002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT9) == _BIT9) && (Scaler32GetBit_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9) == _BIT9))
            {
                // Clear IRQ Flag
                Scaler32SetDWord_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);

                ScalerDpAuxRx1DpcdSymbolErrorCountHandler_EXINT0();

                bReturnValueD1 = _TRUE;
            }
            else
            {
                // Reset Read Error Count Flag Beside Symbol Error Count 00210h ~ 00217h
                CLR_DP_AUX_RX1_SOURCE_READ_ERROR_COUNT();
            }

#if(_DP_RX_FEC_SUPPORT == _ON)
            // DPCD Write 00120h IRQ
            if((Scaler32GetBit_EXINT0(PB19002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT15) == _BIT15) && (Scaler32GetBit_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT15) == _BIT15))
            {
                // Clear 00120h IRQ
                Scaler32SetDWord_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT15);

                ScalerDpAuxRx1FecHanlder_EXINT0();

                bReturnValueD1 = _TRUE;
            }

            // FEC DCPD 00281h~00282h IRQ
            if((Scaler32GetBit_EXINT0(PB19002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT11) == _BIT11) && (Scaler32GetBit_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT11) == _BIT11))
            {
                // Clear FEC DCPD 00281h~00282h IRQ
                Scaler32SetDWord_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT11);

                ScalerDpAuxRx1DpcdFecErrorCount_EXINT0();

                bReturnValueD1 = _TRUE;
            }
#endif

            // Write Link Config Field into INT0
            if(Scaler32GetBit_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT31 | _BIT30 | _BIT29)) != 0x00)
            {
                ScalerDpAuxRx1DpcdLinkTrainingHandler_EXINT0();

                // Clear Flag
                Scaler32SetDWord_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT31 | _BIT30 | _BIT29));

                bReturnValueD1 = _TRUE;
            }

            // Write 00600h into INT0
            if(Scaler32GetBit_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT24) == _BIT24)
            {
                // Clear Flag
                Scaler32SetDWord_EXINT0(PB19002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT24);

                ScalerDpAuxRx1DpcdPowerStateHandler_EXINT0();

                bReturnValueD1 = _TRUE;
            }

            // Write 68xxxh into INT0
            if((Scaler32GetBit_EXINT0(PB19001_8C_AUX_HDCP_IRQ_FLAG, _BIT16) == _BIT16) &&
               (Scaler32GetBit_EXINT0(PB19001_88_AUX_HDCP_IRQ_EN, _BIT16) == _BIT16))
            {
                // Clear Flag
                Scaler32SetDWord_EXINT0(PB19001_8C_AUX_HDCP_IRQ_FLAG, _BIT16);

                // Clear Integrity Failure Flag
                ScalerDpMacDphyRxClearIntegrityFailureFlag_EXINT0(enumInputPort);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                if(Scaler32GetBit_EXINT0(PB19001_80_AUX_HDCP_01, _BIT9))
                {
                    // Detect if V'(0x68027) is read by Source
                    if(Scaler32GetWord_EXINT0(PB19002_18_AUX_RX_ADDR, 0x00) == 0x8028)
                    {
                        ScalerDpHdcp14RxResetKsvFifoToFirst_EXINT0(enumInputPort);
                    }
                }
#endif
                if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // DP Mac Clock Select to Xtal Clock
                    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_XTAL_CLOCK);
                }

                bReturnValueD1 = _TRUE;
            }

            // Detect if Aksv(0x6800B) is Written by Source
            if((Scaler32GetBit_EXINT0(PB19001_88_AUX_HDCP_IRQ_EN, _BIT14) == _BIT14) &&
               (Scaler32GetBit_EXINT0(PB19001_8C_AUX_HDCP_IRQ_FLAG, _BIT14) == _BIT14))
            {
                Scaler32SetDWord_EXINT0(PB19001_8C_AUX_HDCP_IRQ_FLAG, _BIT14);

                ScalerDpAuxRx1DpcdHdcp14AksvHandler_EXINT0();

                bReturnValueD1 = _TRUE;
            }
        }
#endif
    }
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)

    // D2 DP Global IRQ
    if(GET_DP_AUX_RX2_GLOBAL_IRQ_FLAG() == _TRUE)
    {
        if(ScalerGetBit_EXINT(PFF_ED_MCU_CONTROL, _BIT1) == 0x00)
        {
            ScalerSetBit_EXINT(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _FLASH_CLK_PS_FAST_DIV);
        }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        if(g_stDpAuxRx2ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_NONE)
        {
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

            ScalerDpAuxRx2RequestAnalyze_EXINT0();

            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
        }

        if(g_stDpAuxRx2ReceiveBackup.enumIntCase == _DP_AUX_RX_INT_I2C_FIXED_ADDR)
        {
            bReturnValueD2 = ScalerDpAuxRx2I2cIntCaseHandler_EXINT0();
        }
        else
        {
            bReturnValueD2 = ScalerDpAuxRx2DpcdIntCaseHandler_EXINT0();

            if(bReturnValueD2 != _TRUE)
            {
                if(g_stDpAuxRx2ReceiveBackup.enumReqType == _DP_AUX_RX_REQ_NATIVE_WRITE)
                {
                    bReturnValueD2 = ScalerDpAuxRx2DpcdWrite1ClearHandler_EXINT0();
                }
                else if(g_stDpAuxRx2ReceiveBackup.enumReqType == _DP_AUX_RX_REQ_NATIVE_READ)
                {
                    bReturnValueD2 = ScalerDpAuxRx2DpcdReadClearHandler_EXINT0();
                }
            }

            if(g_stDpAuxRx2ReceiveBackup.ulDpcdWildCardIrq != 0x00)
            {
                bReturnValueD2 |= ScalerDpAuxRx2DpcdWildCardIntHandler_EXINT0(g_stDpAuxRx2ReceiveBackup.ulDpcdWildCardIrq);
            }

            if(g_stDpAuxRx2ReceiveBackup.ulDpcdRemapIrq != 0x00)
            {
                bReturnValueD2 |= ScalerDpAuxRx2DpcdRemapIntHandler_EXINT0(g_stDpAuxRx2ReceiveBackup.ulDpcdRemapIrq);
            }
        }
#else
        // Aux Manual Mode
        if(ScalerDpAuxRx2PreIntHandler_EXINT0() == _TRUE)
        {
            enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX2);

            // If source i2c_over_aux cmd hit slave addr = 50
            if(Scaler32GetBit_EXINT0(PB1A002_D8_IIC_STATUS, _BIT8) == _BIT8)
            {
                // Clear flag
                Scaler32SetDWord_EXINT0(PB1A002_D8_IIC_STATUS, _BIT8);

                ScalerDpAuxRx2EdidReadAddrOnlyProtect_EXINT0();

                bReturnValueD2 = _TRUE;
            }

            // Symbol Error Count Read IRQ
            if((Scaler32GetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT9) == _BIT9) && (Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9) == _BIT9))
            {
                // Clear IRQ Flag
                Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT9);

                ScalerDpAuxRx2DpcdSymbolErrorCountHandler_EXINT0();

                bReturnValueD2 = _TRUE;
            }
            else
            {
                // Reset Read Error Count Flag Beside Symbol Error Count 00210h ~ 00217h
                CLR_DP_AUX_RX2_SOURCE_READ_ERROR_COUNT();
            }

#if(_DP_RX_FEC_SUPPORT == _ON)
            // DPCD Write 00120h IRQ
            if((Scaler32GetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT15) == _BIT15) && (Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT15) == _BIT15))
            {
                // Clear 00120h IRQ
                Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT15);

                ScalerDpAuxRx2FecHanlder_EXINT0();

                bReturnValueD2 = _TRUE;
            }

            // FEC DCPD 00281h~00282h IRQ
            if((Scaler32GetBit_EXINT0(PB1A002_50_AUX_DPCD_MISC0_IRQ_EN, _BIT11) == _BIT11) && (Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT11) == _BIT11))
            {
                // Clear FEC DCPD 00281h~00282h IRQ
                Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT11);

                ScalerDpAuxRx2DpcdFecErrorCount_EXINT0();

                bReturnValueD2 = _TRUE;
            }
#endif

            // Write Link Config Field into INT0
            if(Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT31 | _BIT30 | _BIT29)) != 0x00)
            {
                ScalerDpAuxRx2DpcdLinkTrainingHandler_EXINT0();

                // Clear Flag
                Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT31 | _BIT30 | _BIT29));

                bReturnValueD2 = _TRUE;
            }

            // Write 00600h into INT0
            if(Scaler32GetBit_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT24) == _BIT24)
            {
                // Clear Flag
                Scaler32SetDWord_EXINT0(PB1A002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT24);

                ScalerDpAuxRx2DpcdPowerStateHandler_EXINT0();

                bReturnValueD2 = _TRUE;
            }

            // Write 68xxxh into INT0
            if((Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT16) == _BIT16) &&
               (Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT16) == _BIT16))
            {
                // Clear Flag
                Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT16);

                // Clear Integrity Failure Flag
                ScalerDpMacDphyRxClearIntegrityFailureFlag_EXINT0(enumInputPort);

#if((_DP_TX_SUPPORT == _ON) && (_D2_DP_MST_PORT_SUPPORT == _ON))
                if(Scaler32GetBit_EXINT0(PB1A001_80_AUX_HDCP_01, _BIT9))
                {
                    // Detect if V'(0x68027) is read by Source
                    if(Scaler32GetWord_EXINT0(PB1A002_18_AUX_RX_ADDR, 0x00) == 0x8028)
                    {
                        ScalerDpHdcp14RxResetKsvFifoToFirst_EXINT0(enumInputPort);
                    }
                }
#endif
                if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // DP Mac Clock Select to Xtal Clock
                    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_XTAL_CLOCK);
                }

                bReturnValueD2 = _TRUE;
            }

            // Detect if Aksv(0x6800B) is Written by Source
            if((Scaler32GetBit_EXINT0(PB1A001_88_AUX_HDCP_IRQ_EN, _BIT14) == _BIT14) &&
               (Scaler32GetBit_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT14) == _BIT14))
            {
                Scaler32SetDWord_EXINT0(PB1A001_8C_AUX_HDCP_IRQ_FLAG, _BIT14);

                ScalerDpAuxRx2DpcdHdcp14AksvHandler_EXINT0();

                bReturnValueD2 = _TRUE;
            }
        }
#endif
    }
#endif

    if((bReturnValueD0 == _TRUE) || (bReturnValueD1 == _TRUE) || (bReturnValueD2 == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Handle the DP settings when exiting sysint
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxExitIntSetting_EXINT0(void)
{
    ScalerDpAuxRxDpcdPortAccessBackupRestore_EXINT0();

#if(_DP_AUX_RX0_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Clear flag
    ScalerDpAuxRx0ClrDpcdIntFlag_EXINT0();

    ScalerDpAuxRx0RequestReset_EXINT0();

    CLR_DP_AUX_RX0_INT_PROTECT();
#endif

    if((GET_DP_AUX_RX0_MODE_BACKUP_EXINT0() == _DP_RX_AUX_AUTO_MODE) && (GET_DP_AUX_RX0_MODE_EXINT() == _DP_RX_AUX_MANUAL_MODE))
    {
        SET_DP_AUX_RX0_AUTO_MODE_EXINT();
    }
    else if((GET_DP_AUX_RX0_MODE_BACKUP_EXINT0() == _DP_RX_AUX_MANUAL_MODE) && (GET_DP_AUX_RX0_MODE_EXINT() == _DP_RX_AUX_AUTO_MODE))
    {
        SET_DP_AUX_RX0_MANUAL_MODE_EXINT();
    }

    CLR_DP_AUX_RX0_MODE_BACKUP_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Clear flag
    ScalerDpAuxRx1ClrDpcdIntFlag_EXINT0();

    ScalerDpAuxRx1RequestReset_EXINT0();

    CLR_DP_AUX_RX1_INT_PROTECT();
#endif

    if((GET_DP_AUX_RX1_MODE_BACKUP_EXINT0() == _DP_RX_AUX_AUTO_MODE) && (GET_DP_AUX_RX1_MODE_EXINT() == _DP_RX_AUX_MANUAL_MODE))
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
    else if((GET_DP_AUX_RX1_MODE_BACKUP_EXINT0() == _DP_RX_AUX_MANUAL_MODE) && (GET_DP_AUX_RX1_MODE_EXINT() == _DP_RX_AUX_AUTO_MODE))
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }

    CLR_DP_AUX_RX1_MODE_BACKUP_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Clear flag
    ScalerDpAuxRx2ClrDpcdIntFlag_EXINT0();

    ScalerDpAuxRx2RequestReset_EXINT0();

    CLR_DP_AUX_RX2_INT_PROTECT();
#endif

    if((GET_DP_AUX_RX2_MODE_BACKUP_EXINT0() == _DP_RX_AUX_AUTO_MODE) && (GET_DP_AUX_RX2_MODE_EXINT() == _DP_RX_AUX_MANUAL_MODE))
    {
        SET_DP_AUX_RX2_AUTO_MODE_EXINT();
    }
    else if((GET_DP_AUX_RX2_MODE_BACKUP_EXINT0() == _DP_RX_AUX_MANUAL_MODE) && (GET_DP_AUX_RX2_MODE_EXINT() == _DP_RX_AUX_AUTO_MODE))
    {
        SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
    }

    CLR_DP_AUX_RX2_MODE_BACKUP_EXINT0();
#endif

    ScalerDpRxBasePortRestore_EXINT0();
}

//--------------------------------------------------
// Description  : Handle the DP settings when exiting sysint
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxEnterIntSetting_EXINT0(void)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = _DP_RX_AUX_AUTO_MODE;

#if(_DP_AUX_RX0_SUPPORT == _ON)
    enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE_EXINT();

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    if(GET_DP_AUX_RX0_INT_PROTECT() == _FALSE)
#endif
    {
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        SET_DP_AUX_RX0_INT_PROTECT();
#endif
        SET_DP_AUX_RX0_MODE_BACKUP_EXINT0(enumDpAuxRxModeStatus);

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX0_MANUAL_MODE_EXINT();
        }
    }
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    if(GET_DP_AUX_RX1_INT_PROTECT() == _FALSE)
#endif
    {
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        SET_DP_AUX_RX1_INT_PROTECT();
#endif
        SET_DP_AUX_RX1_MODE_BACKUP_EXINT0(enumDpAuxRxModeStatus);

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
        }
    }
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    enumDpAuxRxModeStatus = GET_DP_AUX_RX2_MODE_EXINT();

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    if(GET_DP_AUX_RX2_INT_PROTECT() == _FALSE)
#endif
    {
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        SET_DP_AUX_RX2_INT_PROTECT();
#endif
        SET_DP_AUX_RX2_MODE_BACKUP_EXINT0(enumDpAuxRxModeStatus);

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX2_MANUAL_MODE_EXINT();
        }
    }
#endif

    ScalerDpRxBasePortBackup_EXINT0();

    ScalerDpAuxRxDpcdPortAccessBackup_EXINT0();
}

//--------------------------------------------------
// Description  : Get DP Aux Mode
// Input Value  : None
// Output Value : DP Aux Mode
//--------------------------------------------------
EnumDpAuxRxModeStatus ScalerDpAuxRxGetAuxModeStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_MODE_EXINT();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_MODE_EXINT();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_MODE_EXINT();
#endif
        default:

            return _DP_RX_AUX_AUTO_MODE;
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRxGetDpcdInfo_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdInfo_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdInfo_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdInfo_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRxGetDpcdBitInfo_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdBitInfo_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdBitInfo_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdBitInfo_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitWriteValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitWriteValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DPCD Table Config
// Input Value  : ucDpcdAccessPortH        --> High Byte of DPCD Address
//                ucDpcdAccessPortM        --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL        --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig --> DPCD W / R / WR INT Enable
//                ucDpcdLen                --> Setting N = Len + 1 Dpcd Addr Int Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdIntEnable_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdIntEnable_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdIntEnable_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdIntEnable_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt, bEnable);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Dpcd Mirror Address
// Input Value  : Dpcd Address
// Output Value : Mirror Address
//--------------------------------------------------
DWORD ScalerDpAuxRxDpcdGetMirrorAddr_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    DWORD ulDpcdAddrInput = TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

    // 200-201 = 2002-2003
    if((ulDpcdAddrInput >= 0x00200) && (ulDpcdAddrInput <= 0x00201))
    {
        return (ulDpcdAddrInput + 0x01E02);
    }
    else if((ulDpcdAddrInput >= 0x02002) && (ulDpcdAddrInput <= 0x02003))
    {
        return (ulDpcdAddrInput - 0x01E02);
    }
    // 202-205 = 200C-200F
    else if((ulDpcdAddrInput >= 0x00202) && (ulDpcdAddrInput <= 0x00205))
    {
        return (ulDpcdAddrInput + 0x01E0A);
    }
    else if((ulDpcdAddrInput >= 0x0200C) && (ulDpcdAddrInput <= 0x0200F))
    {
        return (ulDpcdAddrInput - 0x01E0A);
    }
    // 20F-2011
    else if(ulDpcdAddrInput == 0x0020F)
    {
        return 0x02011;
    }
    else if(ulDpcdAddrInput == 0x02011)
    {
        return 0x0020F;
    }
    // 2-F = 2202-220F
    else if((ulDpcdAddrInput >= 0x00002) && (ulDpcdAddrInput <= 0x0000F))
    {
        return (ulDpcdAddrInput + 0x02200);
    }
    else if((ulDpcdAddrInput >= 0x02202) && (ulDpcdAddrInput <= 0x0220F))
    {
        return (ulDpcdAddrInput - 0x02200);
    }
    else
    {
        // Fail Case
        return 0xFFFFFFFF;
    }
}

//--------------------------------------------------
// Description  : Scan Request Cmd Dpcd Addr
// Input Value  : Dpcd Addr
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxScanReqDpcdAddr_EXINT0(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0ScanReqDpcdAddr_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1ScanReqDpcdAddr_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2ScanReqDpcdAddr_EXINT0(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt);
#endif
        default:

            return _FALSE;
    }
}
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Fec Status W1C Protect
// Input Value  : EnumInputPort, _ENABLE/_DISABLE
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRxSetFecStatusW1cProtectEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetFecStatusW1cProtectEnable_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetFecStatusW1cProtectEnable_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetFecStatusW1cProtectEnable_EXINT0(bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Fec Status W1C Protect
// Input Value  : EnumInputPort
// Output Value : _ENABLE/_DISABLE
//--------------------------------------------------
bit ScalerDpAuxRxGetFecStatusW1cProtectEnable_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetFecStatusW1cProtectEnable_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetFecStatusW1cProtectEnable_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetFecStatusW1cProtectEnable_EXINT0();
#endif
        default:

            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Sink Status Setting in EXINT
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSinkStatusSet_EXINT0(EnumInputPort enumInputPort, EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SinkStatusSet_EXINT0(enumReceiverPort, enumInSync);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SinkStatusSet_EXINT0(enumReceiverPort, enumInSync);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SinkStatusSet_EXINT0(enumReceiverPort, enumInSync);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPortAccessBackup_EXINT0(void)
{
    // Backup the DPCD port access registers
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdPortAccessBackup_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1DpcdPortAccessBackup_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdPortAccessBackup_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup Restore
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPortAccessBackupRestore_EXINT0(void)
{
    // Backup the DPCD port access registers
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdPortAccessBackupRestore_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1DpcdPortAccessBackupRestore_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdPortAccessBackupRestore_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetManualMode_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_MANUAL_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_MANUAL_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_MANUAL_MODE_EXINT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Set Auto Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetAutoMode_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_AUTO_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_AUTO_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_AUTO_MODE_EXINT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Set Auto Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxGetDpcdWildCardIntEnable_EXINT0(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdWildCardIntEnable_EXINT0(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdWildCardIntEnable_EXINT0(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdWildCardIntEnable_EXINT0(enumDpAuxRxDpcdWildCardId);
#endif
        default:

            break;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Get Msg RX Base Address of Input Port
// Input Value  : enumOutputPort
// Output Value : WORD
//--------------------------------------------------
void ScalerDpAuxRxSetBase32AddressOffset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            g_ulDpAuxRxBase32AddressOffset = 0x000000;

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            g_ulDpAuxRxBase32AddressOffset = 0x100000;

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            g_ulDpAuxRxBase32AddressOffset = 0x200000;

            break;
#endif

        default:

            g_ulDpAuxRxBase32AddressOffset = 0x000000;

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int check
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxDpcdWildCardIntCheck_EXINT0(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0DpcdWildCardIntCheck_EXINT0(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1DpcdWildCardIntCheck_EXINT0(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2DpcdWildCardIntCheck_EXINT0(enumDpAuxRxDpcdWildCardId);
#endif
        default:

            return 0;
    }
}

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Dp Aux Rx SyncPayloadID Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSyncPayloadIDHandler_EXINT0(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAuxRxSetActSignalCodingType_EXINT0(enumInputPort);

    // Only set 111 when coding type is 8b10b
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_8B10B)
#endif
    {
        if(!((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x01, 0xC0) == 0x00) &&
             (GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x01, 0xC1) == 0x00) &&
             (GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x01, 0xC2) == 0x3F)))
        {
            BYTE ucTemp = GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x01, 0x11);

            if((ucTemp & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0))
            {
                SET_DP_AUX_RX_REG_WR_DPCD_INFO_EXINT0(0x00, 0x01, 0x11, (ucTemp | _BIT1 | _BIT0));

                SET_DP_AUX_RX_DPCD111_MST_ENABLE_BACKUP(_ENABLE);

                // CLR 0x111 IRQ Flag
                CLR_DP_AUX_RX_REG_111_IRQ_FLAG_EXINT();

                if(ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(enumInputPort) == _FALSE)
                {
                    ScalerDpMacDphyRxConfigMstOrSstMode_EXINT0(enumInputPort);
                }
            }
        }
    }

    ScalerDpAuxRxSyncPayloadIDTable_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : Dp Aux Rx Sync Act Handler
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSyncActHandler_EXINT0(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    BYTE ucTemp = GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0);

    if((GET_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT() == _TRUE) && ((ucTemp & _BIT1) == 0x00))
    {
        SET_DP_AUX_RX_REG_W1C_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0, (ucTemp | _BIT1));

        SET_DP_MAC_DPHY_RX_LOAD_NEW_STREAM_PAYLOAD_EXINT();
    }
}

//--------------------------------------------------
// Description  : Rx Sync Payload ID Table with Upstream uPacket Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSyncPayloadIDTable_EXINT0(EnumInputPort enumInputPort)
{
    BYTE ucPayloadID = ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0xC0);
    BYTE ucIDStartPosition = ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0xC1);
    BYTE ucTimeslotLength = ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0xC2);
    BYTE ucExistedIDLength = 0;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    // To handle the case in 8b10b: when source write start = 0, replacing the start if the ID existed in Payload table
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_8B10B)
#endif
    {
        ucIDStartPosition = ScalerDpAuxRxReplaceStart0IfPayloadIDExisted_8b10b_EXINT0(enumInputPort, ucIDStartPosition, ucPayloadID);
    }

    // Calulate ID length after Replacing Start0
    ucExistedIDLength = ScalerDpAuxRxGetExistedIDLength_EXINT0(enumInputPort, ucPayloadID, ucIDStartPosition);

    // Modify PayloadID Table, Stream to ID Mapping, HW Start, End Position, Enable
    switch(ScalerDpAuxRxGetSyncTableAction_EXINT0(enumInputPort, ucPayloadID))
    {
        case _DP_ADD_PAYLOAD_ID:

            ScalerDpAuxRxAddNewPayloadIDProc_EXINT0(enumInputPort, ucPayloadID, ucIDStartPosition, ucTimeslotLength);

            break;

        case _DP_CLEAR_PAYLOAD_ID_TABLE:

            ScalerDpAuxRxClearPayloadIDProc_EXINT0(enumInputPort);

            break;

        case _DP_MODIFY_PAYLOAD_ID_TABLE:

            ScalerDpAuxRxModifyPayloadIDProc_EXINT0(enumInputPort, ucIDStartPosition, ucExistedIDLength, ucPayloadID, ucTimeslotLength);

            break;

        default:

            break;
    }

    if((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) & _BIT1) == _BIT1)
    {
        if(ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(enumInputPort) == _FALSE)
        {
            // For Dell docking issue, avoid source sending ACT before payload ID table sync done
            SET_DP_MAC_DPHY_RX_LOAD_NEW_STREAM_PAYLOAD_EXINT();
        }
    }
    else
    {
        // Manual Set Allocated Flag (HW may miss ACT sequence)
        SET_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT();
    }

    // VC Payload ID Table Updated
    SET_DP_AUX_RX_REG_W1C_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0, ((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) & ~(_BIT1 | _BIT0)) | _BIT0));

    // Clr 0x002C0 IRQ Flag
    CLR_DP_AUX_RX_REG_2C0_IRQ_FLAG_EXINT();

    // Enable 0x002C0 IRQ
    SET_DP_AUX_RX_REG_2C0_IRQ_EN_EXINT();
}

//--------------------------------------------------
// Description  : Setting StreamX Starting and End Position
// Input Value  : Stream Number and Time Slot Modification
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSortStreamPositionReg_EXINT0(EnumInputPort enumInputPort)
{
    BYTE ucTimeSlot = 0;
    BYTE ucPayloadID = 0;
    EnumDpStreamNum enumStreamNum = _DP_ST_1;

    for(ucTimeSlot = 0; ucTimeSlot <= 63; ucTimeSlot++)
    {
        ucPayloadID = ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, ucTimeSlot);

        if(ucPayloadID != 0)
        {
            for(enumStreamNum = _DP_ST_1; enumStreamNum <= _DP_ST_END; enumStreamNum++)
            {
                if(GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumStreamNum) == ucPayloadID)
                {
                    // Setting Start Position
                    ScalerDpMacDphyRxSetStreamStartBackup_EXINT0(enumInputPort, enumStreamNum, ucTimeSlot);

                    while((ucTimeSlot + 1 <= 63) && (ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, (ucTimeSlot + 1)) == ucPayloadID))
                    {
                        ucTimeSlot++;
                    }

                    // Setting End Position
                    ScalerDpMacDphyRxSetStreamEndBackup_EXINT0(enumInputPort, enumStreamNum, ucTimeSlot);

                    // Setting Stream Enable
                    ScalerDpMacDphyRxSetStreamStatusBackup_EXINT0(enumInputPort, enumStreamNum, _ENABLE);
                }
            }
        }
    }
}


//--------------------------------------------------
// Description  : Calculate Existed ID Length
// Input Value  : None
// Output Value : Existed ID Length
//--------------------------------------------------
BYTE ScalerDpAuxRxGetExistedIDLength_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID, BYTE ucStartPosition)
{
    BYTE ucIndex = 0;
    BYTE ucLength = 0;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    for(ucIndex = ucStartPosition; ucIndex < 64; ucIndex++)
    {
        if(ucIndex == 0)
        {
            if((((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC1) & 0x80) >> 1) | ((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) & 0xFC) >> 2)) == ucPayloadID)
            {
                ucLength++;
            }
        }
        else
        {
            if((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucIndex)) & 0x7F) == ucPayloadID)
            {
                ucLength++;
            }
            else
            {
                break;
            }
        }
    }

    return ucLength;
}

//--------------------------------------------------
// Description  : Decide Payload ID Table Action
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpAuxRxGetSyncTableAction_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID)
{
    if(ucPayloadID == 0)
    {
        return _DP_CLEAR_PAYLOAD_ID_TABLE;
    }
    else if(ScalerDpMacDphyRxCheckIDExisted_EXINT0(enumInputPort, ucPayloadID) == _TRUE)
    {
        return _DP_MODIFY_PAYLOAD_ID_TABLE;
    }
    else
    {
        return _DP_ADD_PAYLOAD_ID;
    }
}

//--------------------------------------------------
// Description  : Add New Payload ID To Rx MST stream
// Input Value  : ucPayloadID, ucIDStartPosition, ucTimeslotLength
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxAddNewPayloadIDProc_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID, BYTE ucIDStartPosition, BYTE ucTimeslotLength)
{
    EnumDpStreamNum enumID2ST = _DP_ST_NONE;

    if(ucTimeslotLength != 0)
    {
        // Find Available StreamX whose ID is 0
        enumID2ST = ScalerDpMacDphyRxSearchMatchStream_EXINT0(enumInputPort, 0);

        // Available Stream to add
        if(enumID2ST != _DP_ST_NONE)
        {
            // Mapping Payload ID to ST to ID Table
            SET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumID2ST, ucPayloadID);

            // Modify Payload ID Table for Add ID
            ScalerDpAuxRxModifyPayloadTable_EXINT0(enumInputPort, 63, ucIDStartPosition, 0, ucTimeslotLength, ucPayloadID, _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_DOWN);
        }
    }

    // Set STx Start and End Position According to 2C0-2FF
    ScalerDpAuxRxSortStreamPositionReg_EXINT0(enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // For Rx 128b132b SST, MSG off case, Set Source Mux here
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x11, _BIT1) == 0x00)
        {
            ScalerDpMacDphyRxSetStreamAllocateInfo_EXINT0(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort), _DP_ST_1);

            if(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort) != _DP_MAC_NONE)
            {
                EnumDpStreamSourceNum enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux_EXINT0(ScalerDpRxDxMacSourceMapping_EXINT0(enumInputPort));
                EnumDpStreamNum enumDpStream = ScalerDpMacDphyRxGetStreamAllocateInfo_EXINT0(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));

                ScalerDpMacDphyRxSetSourceMuxBackup_EXINT0(enumInputPort, enumDpSourceTemp, enumDpStream);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Modify Payload ID Process
// Input Value  : ucPayloadID, ucIDStartPosition, ucTimeslotLength
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxModifyPayloadIDProc_EXINT0(EnumInputPort enumInputPort, BYTE ucIDStartPosition, BYTE ucExistedIDLength, BYTE ucPayloadID, BYTE ucTimeslotLength)
{
    EnumDpStreamNum enumID2ST = _DP_ST_NONE;
    EnumDpStreamSourceNum enumDpSourceTemp = _DP_NO_SOURCE;

    enumDpSourceTemp = enumDpSourceTemp;

    if(ucTimeslotLength == 0)
    {
        // Modify Payload ID Table for Del ID
        ScalerDpAuxRxModifyPayloadTable_EXINT0(enumInputPort, (ucIDStartPosition + ucExistedIDLength), 63, ucPayloadID, ucExistedIDLength, 0, _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_UP);

        enumID2ST = ScalerDpMacDphyRxSearchMatchStream_EXINT0(enumInputPort, ucPayloadID);

        if(enumID2ST != _DP_ST_NONE)
        {
            // Delete Payload ID from ST to ID Table
            SET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumID2ST, 0);

            ScalerDpMacDphyRxSetStreamStatusBackup_EXINT0(enumInputPort, enumID2ST, _DISABLE);
            ScalerDpMacDphyRxSetStreamStartBackup_EXINT0(enumInputPort, enumID2ST, 0);
            ScalerDpMacDphyRxSetStreamEndBackup_EXINT0(enumInputPort, enumID2ST, 0);
        }
    }
    else
    {
        // Increase Time Slots
        if(ucTimeslotLength > ucExistedIDLength)
        {
            // Modify Payload ID Table for Increase ID Time slots
            ScalerDpAuxRxModifyPayloadTable_EXINT0(enumInputPort, 63, ucIDStartPosition, 0, (ucTimeslotLength - ucExistedIDLength), ucPayloadID, _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_DOWN);
        }
        else
        {
            // Modify Payload ID Table for Decrease ID Time slots
            ScalerDpAuxRxModifyPayloadTable_EXINT0(enumInputPort, (ucIDStartPosition + ucTimeslotLength), 63, ucPayloadID, (ucExistedIDLength - ucTimeslotLength), 0, _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_UP);
        }
    }
    // Set STx Start and End Position According to 2C0-2FF
    ScalerDpAuxRxSortStreamPositionReg_EXINT0(enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ucTimeslotLength == 0)
    {
        // For Rx 128b132b SST, MSG off case, Set Source Mux here
        if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
        {
            if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x11, _BIT1) == 0x00)
            {
                for(enumDpSourceTemp = _DP_ST_SOURCE1; enumDpSourceTemp <= _DP_ST_SOURCE_END; enumDpSourceTemp++)
                {
                    if(ScalerDpMacDphyRxGetSourceMuxBackup_EXINT0(enumInputPort, enumDpSourceTemp) == ScalerDpMacDphyRxGetStreamAllocateInfo_EXINT0(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort)))
                    {
                        ScalerDpMacDphyRxSetSourceMuxBackup_EXINT0(enumInputPort, enumDpSourceTemp, _DP_ST_NONE);

                        break;
                    }
                }

                ScalerDpMacDphyRxSetStreamAllocateInfo_EXINT0(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort), _DP_ST_NONE);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Modify Payload ID Process
// Input Value  : ucPayloadID, ucIDStartPosition, ucTimeslotLength
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClearPayloadIDProc_EXINT0(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    CLR_DP_AUX_RX_REG_CLEAR_PAYLOAD_ID_TABLE_EXINT();

    ScalerDpMacDphyRxResetStreamToIDMapping_EXINT0(enumInputPort);
    ScalerDpMacDphyRxResetStreamAllocateInfo_EXINT0(enumInputPort);

    ScalerDpMacDphyRxResetStreamStatusBackup_EXINT0(enumInputPort);
    ScalerDpMacDphyRxResetStreamStartBackup_EXINT0(enumInputPort);
    ScalerDpMacDphyRxResetStreamEndBackup_EXINT0(enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // For Rx 128b132b SST & MSG off, Set Source Mux here
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x11, _BIT1) == 0x00)
    {
        ScalerDpMacDphyRxResetSourceMuxBackup_EXINT0(enumInputPort);
        ScalerDpMacDphyRxResetSourceMuxReg_EXINT0(enumInputPort);
    }
#endif
}

//--------------------------------------------------
// Description  : Check Add Position Overlap
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpAuxRxCheckAddPositionLegal_EXINT0(EnumInputPort enumInputPort, BYTE ucIDStartPosition)
{
    BYTE ucID = 0;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    ucID = ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, ucIDStartPosition);

    // Payload ID existed in Table
    if(ucID != 0)
    {
        EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

        for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
        {
            if(GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum) == ucID)
            {
                if(GET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(enumDpStreamNum) == ucIDStartPosition)
                {
                    return _TRUE;
                }
                else
                {
                    // Add Position Error
                    return _FALSE;
                }
            }
        }
    }
    // Not existed, New Payload case
    else
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Modify Payload ID Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxModifyPayloadTable_EXINT0(EnumInputPort enumInputPort, BYTE ucSearchStartPoint, BYTE ucSearchEndPoint, BYTE ucInitialID, BYTE ucDuplicateNum, BYTE ucPayloadID, bit bShiftDirection)
{
    SBYTE chSlotNumber = 0;
    BYTE ucSlotLength = 0;

    if(bShiftDirection == _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_DOWN)
    {
        if(ScalerDpAuxRxCheckAddPositionLegal_EXINT0(enumInputPort, ucSearchEndPoint) == _TRUE)
        {
            if(ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, ucSearchEndPoint) != 0)
            {
                for(chSlotNumber = ucSearchStartPoint; chSlotNumber >= ucSearchEndPoint; chSlotNumber--)
                {
                    if(ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, chSlotNumber) != ucInitialID)
                    {
                        ucInitialID = ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, chSlotNumber);

                        for(ucSlotLength = 0; ucSlotLength < ucDuplicateNum; ucSlotLength++)
                        {
                            // DPCD [0x002C0 ~ 0x002FF]
                            ScalerDpAuxRxSetSyncTablePayloadID_EXINT0(enumInputPort, (chSlotNumber + ucSlotLength + 1), ucInitialID);
                        }
                    }
                }
            }

            if(ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, ucSearchEndPoint) != ucPayloadID)
            {
                for(ucSlotLength = 0; ucSlotLength < ucDuplicateNum; ucSlotLength++)
                {
                    // DPCD [0x002C0 ~ 0x002FF]
                    ScalerDpAuxRxSetSyncTablePayloadID_EXINT0(enumInputPort, (ucSearchEndPoint + ucSlotLength), ucPayloadID);
                }
            }
        }
    }
    else if(bShiftDirection == _DP_MAC_DPHY_RX_TIMESLOT_SHIFT_UP)
    {
        for(chSlotNumber = ucSearchStartPoint; chSlotNumber <= ucSearchEndPoint; chSlotNumber++)
        {
            if(ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, chSlotNumber) != ucInitialID)
            {
                ucInitialID = ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, chSlotNumber);

                for(ucSlotLength = 0; ucSlotLength < ucDuplicateNum; ucSlotLength++)
                {
                    // DPCD [0x002C0 ~ 0x002FF]
                    ScalerDpAuxRxSetSyncTablePayloadID_EXINT0(enumInputPort, (chSlotNumber + ucSlotLength - ucDuplicateNum), ucInitialID);
                }
            }
        }

        if((chSlotNumber > 63) && (ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(enumInputPort, 63) != 0))
        {
            for(ucSlotLength = 0; ucSlotLength < ucDuplicateNum; ucSlotLength++)
            {
                // DPCD [0x002C0 ~ 0x002FF]
                ScalerDpAuxRxSetSyncTablePayloadID_EXINT0(enumInputPort, (ucSearchEndPoint - ucSlotLength), 0);
            }
        }
    }
}


//--------------------------------------------------
// Description  : Get Payload ID
// Input Value  : Time slot position
// Output Value : BYTE Paylaod ID
//--------------------------------------------------
BYTE ScalerDpAuxRxGetSyncTablePayloadID_EXINT0(EnumInputPort enumInputPort, BYTE ucPosition)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(ucPosition == 0)
    {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
        {
            return ((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC1) & 0x80) >> 1) | ((GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) & 0xFC) >> 2);
        }
        else
#endif
        {
            return 0;
        }
    }
    else if (ucPosition <= 63)
    {
        return GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucPosition)) & 0x7F;
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Set Payload ID
// Input Value  : Time slot position, Payload ID
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetSyncTablePayloadID_EXINT0(EnumInputPort enumInputPort, BYTE ucPosition, BYTE ucPayloadID)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(ucPosition == 0)
    {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
        {
            SET_DP_AUX_RX_REG_W1C_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0, (ucPayloadID & 0x3F) << 2);
            SET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, 0xC1, (ucPayloadID & 0x40) << 1);
        }
#endif
    }
    else if(ucPosition <= 0x3F)
    {
        SET_DP_AUX_RX_REG_DPCD_BIT_INFO_EXINT0(0x00, 0x02, (0xC1 + (ucPosition - 1)), ~(_BIT(6, 0)), (ucPayloadID & 0x7F));
    }
}

//--------------------------------------------------
// Description  : 8b10b coding: When Source write start = 0, replacing start if payload ID existed in Payload Table
// Input Value  : ucIDStartPosition, ucPayloadID
// Output Value : ucIDStartPosistion
//--------------------------------------------------
BYTE ScalerDpAuxRxReplaceStart0IfPayloadIDExisted_8b10b_EXINT0(EnumInputPort enumInputPort, BYTE ucIDStartPosition, BYTE ucPayloadID)
{
    BYTE ucIndex = 0;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if((ucIDStartPosition == 0) && (ucPayloadID != 0))
    {
        for(ucIndex = 0; ucIndex <= 63; ucIndex++)
        {
            if(GET_DP_AUX_RX_REG_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucIndex)) == ucPayloadID)
            {
                ucIDStartPosition = ucIndex;

                break;
            }
        }
    }
    return ucIDStartPosition;
}

//--------------------------------------------------
// Description  : Set DP Mst Rx ACT Signal coding type
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpAuxRxSetActSignalCodingType_EXINT0(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        SCALER32_DP_SET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT5, _BIT5);
    }
    else
#endif
    {
        SCALER32_DP_SET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT5, 0x00);
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Aux Rx Mst Enable Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxMstProtocolEnableHandler_EXINT0(EnumInputPort enumInputPort)
{
    BYTE ucDpcd111 = 0;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(enumInputPort) == _FALSE)
    {
        ScalerDpMacDphyRxConfigMstOrSstMode_EXINT0(enumInputPort);
    }

    ucDpcd111 = ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x11, _BIT0);

    if((ucDpcd111 == _DISABLE) && (GET_DP_AUX_RX_DPCD111_MST_ENABLE_BACKUP() == _ENABLE))
    {
        ScalerDpMstRxResetStream_EXINT0(enumInputPort);
    }

    SET_DP_AUX_RX_DPCD111_MST_ENABLE_BACKUP(ucDpcd111);
}
#endif

//--------------------------------------------------
// Description  : Clear DP Payload ID Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClearPayload_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0xC0, ~(_BIT(7, 2)), 0x00);

            ScalerDpAuxRx0DpcdGroupReset_EXINT0(0x00, 0x02, 0xC1, 63);
#else
            Scaler32SetBit_EXINT0(PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, _BIT6);
            Scaler32SetBit_EXINT0(PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, 0x00);
#endif

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0xC0, ~(_BIT(7, 2)), 0x00);

            ScalerDpAuxRx1DpcdGroupReset_EXINT0(0x00, 0x02, 0xC1, 63);
#else
            Scaler32SetBit_EXINT0(PB19001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, _BIT6);
            Scaler32SetBit_EXINT0(PB19001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, 0x00);
#endif

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue_EXINT0(0x00, 0x02, 0xC0, ~(_BIT(7, 2)), 0x00);

            ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x00, 0x02, 0xC1, 63);
#else
            Scaler32SetBit_EXINT0(PB1A001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, _BIT6);
            Scaler32SetBit_EXINT0(PB1A001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, 0x00);
#endif

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Disable Ignore Rx Error
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxErrorToGated_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            Scaler32SetBit_EXINT0(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT14, 0x00);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            Scaler32SetBit_EXINT0(_REG_DP_AUX_RX1_MAC_CTRL, ~_BIT14, 0x00);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            Scaler32SetBit_EXINT0(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT14, 0x00);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Aux PHY Swap Setting
// Input Value  : EnumInputPort, TypeC PinAssignment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxTypeCPinAssert_EXINT0(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0TypeCPinAssert_EXINT0(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1TypeCPinAssert_EXINT0(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2TypeCPinAssert_EXINT0(enumPinAssignment, enumTypeCOrientation);

            break;
#endif
        default:

            break;
    }
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Type Value Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcp2TypeValueReset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0Hdcp2TypeValueReset_EXINT0();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1Hdcp2TypeValueReset_EXINT0();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2Hdcp2TypeValueReset_EXINT0();

            break;
#endif

        default:

            break;
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Stream ID Type Value Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcp2StreamIDTypeReset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0Hdcp2StreamIDTypeReset_EXINT0();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1Hdcp2StreamIDTypeReset_EXINT0();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2Hdcp2StreamIDTypeReset_EXINT0();

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DP Global IRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxGetGlobalIrq_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_GLOBAL_IRQ_FLAG();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_GLOBAL_IRQ_FLAG();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_GLOBAL_IRQ_FLAG();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get HDCP 2.2 Message ID Code
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpAuxRxHdcp2GetMessageID_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0Hdcp2GetMessageID_EXINT0();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1Hdcp2GetMessageID_EXINT0();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2Hdcp2GetMessageID_EXINT0();
#endif
        default:

            break;
    }

    return _HDCP22_NONE;
}

//--------------------------------------------------
// Description  : Reset Dp Rx HDCP info
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcpResetDpcdInfo_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0HdcpResetDpcdInfo_EXINT0();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1HdcpResetDpcdInfo_EXINT0();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2HdcpResetDpcdInfo_EXINT0();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Reset Dp Rx HDCP info
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxCpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType, EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0CpIRQ_EXINT0(enumBStatusType);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1CpIRQ_EXINT0(enumBStatusType);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2CpIRQ_EXINT0(enumBStatusType);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Read M Prime Force Defer
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetMPrimeReadDefer_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetMPrimeReadDefer_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetMPrimeReadDefer_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetMPrimeReadDefer_EXINT0(bEnable);

            break;
#endif
        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Aux Get Link Training Status
// Input Value  : None
// Output Value : Link Training Status
//--------------------------------------------------
BYTE ScalerDpAuxRxGetLTStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_LINK_TRAINING_STATUS();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_LINK_TRAINING_STATUS();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_LINK_TRAINING_STATUS();
#endif
        default:

            return _DP_LINK_TRAINING_NONE;
    }
}

//--------------------------------------------------
// Description  : DP Aux Get TP1 Initial
// Input Value  : None
// Output Value : TP1 Initial Flag
//--------------------------------------------------
bit ScalerDpAuxRxGetTp1Initial_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_bDpAuxRx0Tp1Initial;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_bDpAuxRx1Tp1Initial;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_bDpAuxRx2Tp1Initial;
#endif
        default:

            return _DP_LINK_TRAINING_NONE;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : DP Input Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRxGetDpcdLinkRate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00))
    {
        case 0x21:
            return _DP_LINK_HBR3_9G;

        case 0x1E:
            return _DP_LINK_HBR3;

        case 0x14:
            return _DP_LINK_HBR2;

        case 0x0A:
            return _DP_LINK_HBR;

        case 0x06:
            return _DP_LINK_RBR;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        case 0x04:
            return _DP_LINK_UHBR13_5;

        case 0x02:
            return _DP_LINK_UHBR20;

        case 0x01:
            return _DP_LINK_UHBR10;
#endif
        default:
            return _DP_LINK_RBR;
    }
}

//--------------------------------------------------
// Description  : Set Link Training Link Rate
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
void ScalerDpAuxRxSetLinkRate_EXINT0(EnumInputPort enumInputPort, BYTE ucLinkRate)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            switch(ucLinkRate)
            {
                case 0x21:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_HBR3_9G;
                    break;

                case 0x1E:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_HBR3;
                    break;

                case 0x14:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_HBR2;
                    break;

                case 0x0A:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_HBR;
                    break;

                case 0x06:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_RBR;
                    break;
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
                case 0x04:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_UHBR13_5;
                    break;

                case 0x02:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_UHBR20;
                    break;

                case 0x01:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_UHBR10;
                    break;
#endif
                default:
                    g_enumDpAuxRx0LinkRate = _DP_LINK_NONE;
                    break;
            }
            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            switch(ucLinkRate)
            {
                case 0x21:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_HBR3_9G;
                    break;

                case 0x1E:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_HBR3;
                    break;

                case 0x14:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_HBR2;
                    break;

                case 0x0A:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_HBR;
                    break;

                case 0x06:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_RBR;
                    break;
#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                case 0x04:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_UHBR13_5;
                    break;

                case 0x02:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_UHBR20;
                    break;

                case 0x01:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_UHBR10;
                    break;
#endif
                default:
                    g_enumDpAuxRx1LinkRate = _DP_LINK_NONE;
                    break;
            }
            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            switch(ucLinkRate)
            {
                case 0x21:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_HBR3_9G;
                    break;

                case 0x1E:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_HBR3;
                    break;

                case 0x14:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_HBR2;
                    break;

                case 0x0A:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_HBR;
                    break;

                case 0x06:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_RBR;
                    break;
#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                case 0x04:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_UHBR13_5;
                    break;

                case 0x02:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_UHBR20;
                    break;

                case 0x01:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_UHBR10;
                    break;
#endif
                default:
                    g_enumDpAuxRx2LinkRate = _DP_LINK_NONE;
                    break;
            }
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Link Training Lane Count
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
void ScalerDpAuxRxSetLaneCount_EXINT0(EnumInputPort enumInputPort, BYTE ucLaneCount)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            switch(ucLaneCount)
            {
                case 0x01:
                    g_enumDpAuxRx0LaneCount = _DP_LINK_1_LANE;
                    break;

                case 0x02:
                    g_enumDpAuxRx0LaneCount = _DP_LINK_2_LANE;
                    break;

                case 0x04:
                    g_enumDpAuxRx0LaneCount = _DP_LINK_4_LANE;
                    break;

                default:
                    g_enumDpAuxRx0LaneCount = _DP_LINK_NO_LANE;
                    break;
            }
            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            switch(ucLaneCount)
            {
                case 0x01:
                    g_enumDpAuxRx1LaneCount = _DP_LINK_1_LANE;
                    break;

                case 0x02:
                    g_enumDpAuxRx1LaneCount = _DP_LINK_2_LANE;
                    break;

                case 0x04:
                    g_enumDpAuxRx1LaneCount = _DP_LINK_4_LANE;
                    break;

                default:
                    g_enumDpAuxRx1LaneCount = _DP_LINK_NO_LANE;
                    break;
            }
            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            switch(ucLaneCount)
            {
                case 0x01:
                    g_enumDpAuxRx2LaneCount = _DP_LINK_1_LANE;
                    break;

                case 0x02:
                    g_enumDpAuxRx2LaneCount = _DP_LINK_2_LANE;
                    break;

                case 0x04:
                    g_enumDpAuxRx2LaneCount = _DP_LINK_4_LANE;
                    break;

                default:
                    g_enumDpAuxRx2LaneCount = _DP_LINK_NO_LANE;
                    break;
            }
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Link Training Pattern
// Input Value  : SearchPort
// Output Value : Link Training Pattern
//--------------------------------------------------
BYTE ScalerDpAuxRxTrainingPatternSet_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_ucDpAuxRx0TrainingPatternSet;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_ucDpAuxRx1TrainingPatternSet;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_ucDpAuxRx2TrainingPatternSet;
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get Link Training Link Rate
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRxGetLinkRate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_enumDpAuxRx0LinkRate;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_enumDpAuxRx1LinkRate;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_enumDpAuxRx2LinkRate;
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get Link Training Lane Count
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
BYTE ScalerDpAuxRxGetLaneCount_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_enumDpAuxRx0LaneCount;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_enumDpAuxRx1LaneCount;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_enumDpAuxRx2LaneCount;
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Check Link Training Link Rate
// Input Value  : SearchPort
// Output Value : Link Training Pattern
//--------------------------------------------------
BYTE ScalerDpAuxRxCheckLinkRate_EXINT0(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // DP 20 no bit mapping rate is selected
        if((ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) & ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x22, 0x15)) == 0x00)
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x00, 0x0E, _BIT7) == _BIT7)
        {
            if(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) > ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x22, 0x01))
            {
                return _FALSE;
            }
        }
        else
        {
            if(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) > ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x00, 0x01))
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Link Training Coding Type
// Input Value  : SearchPort
// Output Value : Coding Type
//--------------------------------------------------
EnumDpLinkChannelCodingType ScalerDpAuxRxGetCodingType_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX0:

            return g_enumDpAuxRx0CodingType;

#endif

#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX1:

            return g_enumDpAuxRx1CodingType;

#endif

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX2:

            return g_enumDpAuxRx2CodingType;

#endif
        default:

            return _CODING_TYPE_8B10B;
    }
}
#endif
//--------------------------------------------------
// Description  : DP Aux Get TP1 Permit Swing Level 0
// Input Value  : Input Port
// Output Value : TP1 Permit Swing Level 0 Flag
//--------------------------------------------------
BYTE ScalerDpAuxRxGetTp1PermitSwing0_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_ucDpAuxRx0Tp1PermitSwingLevel0;
#endif
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_ucDpAuxRx1Tp1PermitSwingLevel0;
#endif
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_ucDpAuxRx2Tp1PermitSwingLevel0;
#endif
#endif
        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHpdIrqAssert_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0HpdIrqAssert_EXINT0();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1HpdIrqAssert_EXINT0();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2HpdIrqAssert_EXINT0();

            break;
#endif
        default:

            break;
    }
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Update PR Mode Error Statu DPCD 02020h
// Input Value  : EnumInputPort,EnumPRModeErrorStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(EnumInputPort enumInputPort, EnumPRModeErrorStatus enumPRModeErrorStatus)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0DpcdPRModeErrorStateUpdate_EXINT0(enumPRModeErrorStatus);
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1DpcdPRModeErrorStateUpdate_EXINT0(enumPRModeErrorStatus);
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2DpcdPRModeErrorStateUpdate_EXINT0(enumPRModeErrorStatus);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get PR Mode DPCD 001B0h[1] Crc Enable
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxGetPRModeDpcdCrcEnable_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            return GET_DP_AUX_RX0_PR_MODE_DPCD_CRC_ENABLE();
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            return GET_DP_AUX_RX1_PR_MODE_DPCD_CRC_ENABLE();
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            return GET_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE();
#endif
        default:
            return _FALSE;
    }
}
#endif
#endif
