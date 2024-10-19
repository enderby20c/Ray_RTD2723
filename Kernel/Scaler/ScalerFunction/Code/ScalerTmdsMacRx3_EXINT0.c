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
// ID Code      : ScalerTmdsMacRx3_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSMACRX3_EXINT0__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx3/ScalerTmdsMacRx3.h"



#if(_TMDS_MAC_RX3_SUPPORT == _ON)
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
// Description  : Check CDR Locked (EXINT0 Only)
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
BYTE ScalerTmdsMacRx3CheckCDRStable_EXINT0(WORD usClkCount)
{
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HIGH_SPEED_MODE() == _TRUE)
    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - (ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - (ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - (ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 6))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_RED)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
        {
            return _FALSE;
        }
    }
    return _TRUE;
}

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Description  : GET HDR10+ VSIF From RSV
// Input Value  : RSV number, struct for PKT
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3GetAdvancedHdr10Vsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata)
{
    BYTE ucRsvStartAddr = 0;
    BYTE ucI = 0;
    BYTE ucKp1 = 0;
    BYTE ucKp2 = 0;
    BYTE ucKp3 = 0;

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ucRsvStartAddr = 0x4E;
            break;

        case _HDMI_RSV_1:
            ucRsvStartAddr = 0x6D;
            break;

        case _HDMI_RSV_2:
            ucRsvStartAddr = 0x8C;
            break;

        case _HDMI_RSV_3:
            ucRsvStartAddr = 0xAB;
            break;

        default:

            break;
    }

    // Get HDR10+ VSIF pkt
    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 1));
    pstSyncAdvancedHDR10Metadata->ucVersion = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 4));
    for(ucI = 0; ucI < 3; ucI++)
    {
        pstSyncAdvancedHDR10Metadata->pucOUICode[ucI] = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    }

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 7));
    pstSyncAdvancedHDR10Metadata->ucTargetDisplayLv = ((ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & 0x3F) >> 1);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 13));
    pstSyncAdvancedHDR10Metadata->ucDistribution50 = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 17));
    pstSyncAdvancedHDR10Metadata->ucDistribution99 = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 21));
    for(ucI = 0; ucI < 9; ucI++)
    {
        pstSyncAdvancedHDR10Metadata->pucBezierAnchor[ucI] = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    }

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 18));
    ucKp1 = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    ucKp2 = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    ucKp3 = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    pstSyncAdvancedHDR10Metadata->pusKneePoint[0] = ((ucKp1 & 0x0F) << 6) + ((ucKp2 & 0xFC) >> 2);
    pstSyncAdvancedHDR10Metadata->pusKneePoint[1] = (((ucKp2 & 0x03) << 8) + ucKp3);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 30));
    pstSyncAdvancedHDR10Metadata->ucGraphicOverlayFlag = (ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) >> 7);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, (ucRsvStartAddr + 30));
    pstSyncAdvancedHDR10Metadata->ucNoDelayFlag = ((ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & 0x40) >> 6);
}

#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : GET DM VSIF From RSV
// Input Value  : RSV number, MetaData pointer
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3GetDmVsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, BYTE *pucDmMetaData)
{
    BYTE ucRsvStartAddr = 0;
    BYTE ucMdOffset = 4;

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ucRsvStartAddr = 0x4E + ucMdOffset;
            break;

        case _HDMI_RSV_1:
            ucRsvStartAddr = 0x6D + ucMdOffset;
            break;

        case _HDMI_RSV_2:
            ucRsvStartAddr = 0x8C + ucMdOffset;
            break;

        case _HDMI_RSV_3:
            ucRsvStartAddr = 0xAB + ucMdOffset;
            break;

        default:

            break;
    }

    ScalerGetDataPortByte_EXINT0(P72_CD_HDMI_PSAP, ucRsvStartAddr, 27, pucDmMetaData, _AUTOINC);
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable ALLM
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3AllmProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    bit bAllm = 0;

#if(_DM_FUNCTION == _ON)
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);
#endif

    // Get ALLM bit
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x56);
            bAllm = (((ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x75);
            bAllm = (((ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x94);
            bAllm = (((ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0xB3);
            bAllm = (((ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    // Enable/Disable ALLM
    if(bAllm == _TRUE)
    {
        SET_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxSetDmAllmStatus_EXINT0(enumInputPort);
#endif
    }
    else
    {
        CLR_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxClrDmAllmStatus_EXINT0(enumInputPort);
#endif
    }
}
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get CCBPC Value
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3CcbpcProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucCcbpcValue = 0;

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x56);
            ucCcbpcValue = (ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x75);
            ucCcbpcValue = (ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x94);
            ucCcbpcValue = (ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0xB3);
            ucCcbpcValue = (ScalerGetByte_EXINT(P72_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        default:

            break;
    }

    if((ucCcbpcValue != 0) && ((ucCcbpcValue + 7) <= GET_COLOR_DEPTH(enumMappingPort)))
    {
        SET_COLOR_HDMI21_CCBPC_VALUE(enumMappingPort, ucCcbpcValue + 7);
    }
    else
    {
        SET_COLOR_HDMI21_CCBPC_VALUE(enumMappingPort, 0);
    }
}
#endif

//--------------------------------------------------
// Description  : Check High Priority Irq
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3HighPriorityIntHandler_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);
    BYTE pucBackUp[8];

    pucBackUp[0] = ScalerGetByte_EXINT(P72_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);

    pucBackUp[2] = ScalerGetByte_EXINT(P72_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P72_38_HDMI_CTRL_38) & 0x01);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Backup DFF #1 & #2
    pucBackUp[4] = ScalerGetByte_EXINT(P72_CD_HDMI_PSAP);
    pucBackUp[5] = ScalerGetByte_EXINT(P72_D0_HDMI_PSAP2);

    pucBackUp[6] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);
    pucBackUp[7] = (ScalerGetByte_EXINT(P72_C2_HDCP_PCR) & 0x01);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    ScalerTmdsMacRx3ClearHighPriorityIrqFlag_EXINT0();
#endif

    // Freq. Unstable Into IRQ
    if((ScalerGetByte_EXINT(P72_E6_HDMI_FREQDET_CTRL) & 0x06) == 0x06)
    {
#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
        bit bBedCheck = _TRUE;
#endif

        ScalerTmdsMacRxPhyDrcrFifoReset_EXINT0(enumMappingPort);

        // Clear Unstable IRQ Flag
        ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

        // Ensure Freq really unstable
        if((abs(g_usTmdsMacRx3ClkCount - ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (g_usTmdsMacRx3ClkCount >> 6)) ||
           (abs(ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) - ((GET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK() << 3) / ((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) ? _COLOR_DEPTH_8_BITS : GET_COLOR_DEPTH(enumMappingPort)))) > (ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) >> 6)))
        {
            // Set D Domain Region Free run/ Force to Background
            ScalerDDomainResetDDomainRgn(GET_TMDS_MAC_RX3_FORCE_BCKGRD_PATH());

            // Disable RGB/clock Output to avoid garbage
            ScalerSetBit_EXINT(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
            bBedCheck = _FALSE;
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH);
#endif

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
            // Disable TMDS CED Function & Lock Transition
            ScalerTmdsMacRx3SetCedLockTransition_EXINT0(_DISABLE);

            // Clear SCDC Port Status Update Flag & CED Update Flag
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~(_BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Lock Flag
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Reset HDMI/DVI Format
            ScalerSetBit_EXINT(P72_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
#endif
            // Disable Freq. Unstable IRQ
            ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), 0x00);

            // Set HDMI/DVI switch to Auto Mode
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

            // Set Upper Bound
            ScalerSetByte_EXINT(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
            ScalerSetByte_EXINT(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));

            // Set Lower Bound
            ScalerSetByte_EXINT(P72_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte_EXINT(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), 0x00);
            ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
            // Avoid Freq. Stable IRQ happened during HPD toggling, or Z0 would be ON unexpectedly in Stable IRQ Handler
            if(GET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING() == _FALSE)
#endif
            {
                // Enable Freq. Stable IRQ
                ScalerSetBit_EXINT(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            }

            ScalerTmdsPhyRxFifoAutoResetEnable_EXINT0(enumMappingPort, _DISABLE);

            CLR_TMDS_MAC_RX3_PHY_SET();

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
            // clr Retry to Set Phy Flag
            CLR_TMDS_MAC_RX3_RETRY_SET_PHY();

            // Cancel WD Timer Event
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX3_TMDS_RETRY_SET_PHY);
#endif

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
            CLR_TMDS_MAC_RX3_HIGH_SPEED_MODE();
#endif

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_MAC_RX3_SUPPORT == _ON))
            // Reset Authenticated FSM
            ScalerSetByte_EXINT(P2E_28_HDCP_I2C_CTRL_2, 0x01);
            ScalerSetBit_EXINT(P2E_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

            // Cancel HDCP 2.2 Re-Auth Timer Event
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH);
#endif
        }

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
        if((bBedCheck == _TRUE) && (ScalerTmdsPhyRxCheckDcdr_EXINT0(enumMappingPort) == _TRUE))
        {
            // Enable BED Detect(Check 1 frame)
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_AF_PORT_PAGE72_HDMI_BED_FUNC_0, ~_BIT3, _BIT3);

            ScalerTimerWDActivateTimerEvent_EXINT0(90, _SCALER_WD_TIMER_EVENT_RX3_HDMI_UNSTABLE_BED_CHECK);
        }
#endif
    }

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    // SCDC 0x20 Change IRQ
    if((ScalerGetBit_EXINT(P72_26_HDMI_CTRL_26, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(P72_25_HDMI_CTRL_25, _BIT4) == _BIT4))
    {
        // Clear SCDC 0x20 Change Flag
        ScalerSetByte_EXINT(P72_25_HDMI_CTRL_25, _BIT4);

        // Check Scramble_en bit
        ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_CA_PT_20_PORT_PAGE72_HDMI_ICTPSR0);
        if(ScalerGetBit_EXINT(P72_3A_HDMI_CTRL_3A, _BIT0) == _BIT0)
        {
            // Set Scramble Detect Auto Mode
            ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT4 | _BIT2 | _BIT1), _BIT4);

            // Disable SCDC 0x20 Change IRQ
            ScalerSetBit_EXINT(P72_26_HDMI_CTRL_26, ~_BIT4, 0x00);
        }
    }
#endif

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P72_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P72_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetByte_EXINT(P72_25_HDMI_CTRL_25, _BIT3);

        // Set Read Request Enable
        SET_TMDS_MAC_RX3_HDMI20_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P72_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P72_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P72_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Detect CED Channel 2 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P72_17_HDMI_CTRL_17, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P72_18_HDMI_CTRL_18, _BIT2) == _BIT2))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P72_17_HDMI_CTRL_17, _BIT5) == _BIT5)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT3, _BIT3);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT3, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P72_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P72_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P72_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 1 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P72_17_HDMI_CTRL_17, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P72_18_HDMI_CTRL_18, _BIT1) == _BIT1))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P72_17_HDMI_CTRL_17, _BIT4) == _BIT4)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT2, _BIT2);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT2, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P72_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P72_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P72_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 0 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P72_17_HDMI_CTRL_17, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P72_18_HDMI_CTRL_18, _BIT0) == _BIT0))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P72_17_HDMI_CTRL_17, _BIT3) == _BIT3)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT1, _BIT1);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT1, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P72_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P72_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P72_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P72_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P72_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P72_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

        // Read Request Outcome Processing
        ScalerTmdsMacRx3ReadRequestProc_EXINT0(ScalerGetByte_EXINT(P72_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P72_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P72_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            ScalerTmdsMacRxSetScdcInfo_EXINT0(enumMappingPort);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
            if(ScalerTmdsMacRxGetFreeSyncSupport_EXINT0(enumMappingPort) == _FREESYNC_SUPPORT_ON)
            {
                ScalerTmdsMacRxSetAmdAupiScdcInfo_EXINT0(enumMappingPort, _ENABLE);
            }
            else
            {
                ScalerTmdsMacRxSetAmdAupiScdcInfo_EXINT0(enumMappingPort, _DISABLE);
            }
#endif
            // Clear HDMI 2.0 Read Request Enable
            CLR_TMDS_MAC_RX3_HDMI20_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P72_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P72_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P72_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P72_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTmdsMacRx3CheckCDRStable_EXINT(g_usTMDSRx3ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P72_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P72_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P72_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
        }
    }
#elif((_AUDIO_EARC_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP))
    // TODO: Should consider OSD eARC/ARC/Off mode change in future
    if(ScalerGetBit_EXINT(P72_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        // HPD H -> L
        if(ScalerGetBit_EXINT(P72_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
            ScalerHdmiArcTxEarcResetDiscovery_EXINT0();
#endif

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
        }
        // HPD L -> H
        else
        {
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
            if(GET_HDMI_ARC_TX_OSD_ARC_MODE() == _EARC_MODE)
            {
                ScalerHdmiArcTxEarcStartDiscovery_EXINT0();
            }
#endif

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
        }
    }
#endif // End of #if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)

#endif // End of #if(_HDMI20_MAC_RX3_SUPPORT == _ON)

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P72_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P72_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV & Ri flag
        ScalerSetBit_EXINT(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT6));

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P72_AE_TMDS_RPS, ~_BIT1, _BIT1);

        SET_TMDS_MAC_RX3_BACKUP_HDCP_TYPE(_HDCP_14);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P72_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        ScalerTmdsHdcp2Rx3ResetProc_EXINT0();
#endif
    }

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, pucBackUp[0]);

    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, pucBackUp[2]);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, pucBackUp[4]);
    ScalerSetByte_EXINT(P72_D0_HDMI_PSAP2, pucBackUp[5]);

    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[7]);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, pucBackUp[6]);
}

//--------------------------------------------------
// Description  : Check Low Priority Irq
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3LowPriorityIntHandler_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);
    WORD usCount = 0;
    BYTE pucBackUp[8];
#if((_HDMI_MAC_RX3_SUPPORT == _ON) & (_AUDIO_SUPPORT == _ON) & (_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF))
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;
#endif
    pucBackUp[0] = ScalerGetByte_EXINT(P72_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);

    pucBackUp[2] = ScalerGetByte_EXINT(P72_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P72_38_HDMI_CTRL_38) & 0x01);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Backup DFF #1 & #2
    pucBackUp[4] = ScalerGetByte_EXINT(P72_CD_HDMI_PSAP);
    pucBackUp[5] = ScalerGetByte_EXINT(P72_D0_HDMI_PSAP2);

    pucBackUp[6] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);
    pucBackUp[7] = (ScalerGetByte_EXINT(P72_C2_HDCP_PCR) & 0x01);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    ScalerTmdsMacRx3ClearLowPriorityIrqFlag_EXINT0();
#endif

    // Freq. Stable Into IRQ
    if((ScalerGetByte_EXINT(P72_EF_HDMI_ERROR_TH) & 0xC0) == 0xC0)
    {
        // Disable Freq Stable IRQ
        ScalerSetBit_EXINT(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
        // Disable NO CLK WD
        ScalerSetBit_EXINT(P72_B2_TMDS_DBB2, ~(_BIT5 | _BIT4), 0x00);
#endif

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        // Set SCDC Port Clock Detected
        ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
        ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

        // Disable Reset HDMI/DVI Format
        ScalerSetBit_EXINT(P72_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P72_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P72_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P72_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P72_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
#endif

        // Enable Freq unstable IRQ
        ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Pop up Counter Value
        ScalerSetBit_EXINT(P72_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

        usCount = (WORD)(((ScalerGetByte_EXINT(P72_ED_HDMI_FREQDET_RESULT_M) & 0x7F) << 8) | ScalerGetByte_EXINT(P72_EE_HDMI_FREQDET_RESULT_L));

        // TMDS_FREQ(MHz) = GDI_CLK(MHz) * CLK_COUNT * _TMDS_MEASURE_CLOCK_DIVIDER / _TMDS_MEASURE_CLOCK_COUNTER
        ScalerTmdsMacRxSetInputPixel_EXINT0(enumMappingPort, (((DWORD)_GDIPHY_RX_GDI_CLK_KHZ * usCount + 50000) / 100000));

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
#if(_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_NONE)
        // If SCDC tell 1:40 then set High speed flag
        if((ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) >= 850) && (ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) <= 1500))
        {
            ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, _P72_3A_PT_20_PORT_PAGE72_HDMI_SCDC_20);

            if(ScalerGetBit_EXINT(P72_3A_HDMI_CTRL_3A, _BIT1) == _BIT1)
            {
                SET_TMDS_MAC_RX3_HIGH_SPEED_MODE();
            }
        }
#elif(_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_0)
        SET_TMDS_MAC_RX3_HIGH_SPEED_MODE();
#endif
        if(GET_TMDS_MAC_RX3_HIGH_SPEED_MODE() == _TRUE)
        {
            ScalerTmdsMacRxSetInputPixel_EXINT0(enumMappingPort, (ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) * 4));
        }
#endif

        if(ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) > 3000)
        {
            // Set Input Clock Measure Divider = /2
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0, ~_BIT6, _BIT6);
        }
        else
        {
            // Set Input Clock Measure Divider = /1
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0, ~_BIT6, 0x00);
        }

        if((GET_TMDS_MAC_RX3_PHY_SET() == _FALSE) || ((bit)ScalerTmdsMacRx3CheckCDRStable_EXINT0(g_usTmdsMacRx3ClkCount) == _FALSE))
        {
            g_usTmdsMacRx3ClkCount = ScalerTmdsMacRx3MeasureClk_EXINT0(_CLK_SOURCE_TMDS);

            // If Measure Divider = /2 then CLK x 2
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0);
            if((ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT6) == _BIT6) && (g_usTmdsMacRx3ClkCount != 0))
            {
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 * 2 / g_usTMDSRx3ClkCount
                SET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK(((DWORD)(_GDIPHY_RX_GDI_CLK_KHZ * 1024) * 2 / 100) / g_usTmdsMacRx3ClkCount);
            }
            else if(g_usTmdsMacRx3ClkCount != 0)
            {
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 / g_usTMDSRx3ClkCount
                SET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK(((DWORD)(_GDIPHY_RX_GDI_CLK_KHZ * 1024) / 100) / g_usTmdsMacRx3ClkCount);
            }

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HIGH_SPEED_MODE() == _TRUE)
            {
                SET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK((GET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK() * 4));
            }
#endif
            ScalerTmdsPhyRxSetPhy_EXINT0(enumMappingPort);

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_RETRY_SET_PHY() == _FALSE)
            {
                ScalerTimerWDActivateTimerEvent_EXINT0(_TMDS_RETRY_SET_PHY_TIME, _SCALER_WD_TIMER_EVENT_RX3_TMDS_RETRY_SET_PHY);
            }
#endif

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
            CLR_TMDS_MAC_RX3_BED_ERROR();
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            if(GET_TMDS_HDCP2_RX3_AUTHENTICATION_DONE() == _TRUE)
            {
                ScalerTimerWDActivateTimerEvent_EXINT0(500, _SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH);
            }
#endif
        }

        // Set Upper Bound (allow 1/64 freq shift)
        ScalerSetByte_EXINT(P72_E8_HDMI_FREQDET_UPPER_M, (HIBYTE(usCount + (usCount >> 6)) & 0x7F));
        ScalerSetByte_EXINT(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(usCount + (usCount >> 6)));

        // Set Lower Bound
        ScalerSetByte_EXINT(P72_EA_HDMI_FREQDET_LOWER_M, (HIBYTE(usCount - (usCount >> 6)) & 0x7F));
        ScalerSetByte_EXINT(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(usCount - (usCount >> 6)));

        // Reset Color Depth to 8 Bits
        SET_COLOR_DEPTH(enumMappingPort, _COLOR_DEPTH_8_BITS);

        SET_TMDS_MAC_RX3_PHY_SET();

        ScalerTmdsPhyRxFifoAutoResetEnable_EXINT0(enumMappingPort, _ENABLE);

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        // Set HDMI 2.0 Character Error Detection Function Lock Transition Error Boundary
        ScalerSetBit_EXINT(P72_14_HDMI_CTRL_14, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) / 10) >> 8);
        ScalerSetByte_EXINT(P72_15_HDMI_CTRL_15, (ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort) / 10));

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        // Switch to HDMI 2.0 SCDC Module
        ScalerSetBit_EXINT(P72_31_HDMI_CTRL_31, ~_BIT7, 0x00);
#endif

        // Enable TMDS CED Function & Lock Transition
        ScalerTmdsMacRx3SetCedLockTransition_EXINT0(_ENABLE);
#endif
    }

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
    // --- RSV0 Into IRQ ---
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
    if((ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P72_CC_HDMI_GPVS, _BIT5) == _BIT5))
    {
        ScalerSetByte_EXINT(P72_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
        if(ScalerGetByte_EXINT(P72_F8_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
        {
            ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_0);
        }
        else
#endif
        {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
            ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_0);
#endif
        }
    }

    // --- RSV1 Into IRQ ---
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
    if((ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P72_CC_HDMI_GPVS, _BIT6) == _BIT6))
    {
        ScalerSetByte_EXINT(P72_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
        if(ScalerGetByte_EXINT(P72_F9_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
        {
            ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_1);
        }
        else
#endif
        {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
            ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_1);
#endif
        }
    }

    // --- RSV2 Into IRQ ---
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
    if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT2) == _BIT2)
    {
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR);
        if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT7) == _BIT7)
        {
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P72_FA_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_2);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_2);
#endif
            }
        }
    }

    // --- RSV3 Into IRQ ---
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
    if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT3) == _BIT3)
    {
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR);
        if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT6) == _BIT6)
        {
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P72_FB_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_3);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_3);
#endif
            }
        }
    }
#endif

#if(((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE)) || (_HDMI_SBTM_SUPPORT == _ON))
    // "VS EMP" received into IRQ
    if(ScalerGetBit_EXINT(P2E_70_EMP_VS, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        if(ScalerGetByte_EXINT(P2E_7C_VS_ORG_ID) == _VENDOR_SPECIFIC)
        {
#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            ScalerTmdsMacRx3DMSetting_EXINT0(enumMappingPort);
#endif
        }
        else if(ScalerGetByte_EXINT(P2E_7C_VS_ORG_ID) == _HDMI21)
        {
#if(_HDMI_SBTM_SUPPORT == _ON)
            ScalerTmdsMacRx3SbtmSetting_EXINT0();
#endif
        }
    }
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
    // "D-HDR EMP" received into IRQ
    if(ScalerGetBit_EXINT(P2E_71_EMP_DHDR, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        bit bMldsEmp = _FALSE;

        BYTE ucI = 0x00;
        BYTE ucLegalDataSize = 0x00;
        BYTE ucMaxSize = ((ScalerGetBit_EXINT(P2E_88_HDMI_EMP_SRAM_CTRL0, _BIT4) == _BIT4) ? _HDMI_EMP_SRAM_DHDR_SIZE : _HDMI_EMP_SRAM_TOTAL_SIZE); // 7 Byte as 1 unit

        BYTE pucEmpData[7] = {0};
        BYTE pucMetaData[_ADVANCED_HDR10_DHDR_EMP_MD_SIZE * 7] = {0}; // 112

        WORD usDhdrType = 0;
        BYTE ucContryCode = 0;
        WORD usProviderCode = 0;
        WORD usProviderOrientedCode = 0;
        BYTE ucAppIdentifier = 0;
        BYTE ucAppVersion = 0;

        // w1c received flag
        ScalerSetBit_EXINT(P2E_71_EMP_DHDR, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

        // Read EMP SRAM Data
        for(ucI = 0; ucI < ucMaxSize; ucI++)
        {
            if(ScalerTmdsMacRx3GetEmpSramData_EXINT0((0x00 + ucI), pucEmpData) == _TRUE)
            {
                // PB0~6 (EMP Header)
                if(ucI == 0)
                {
                    // Check length
                    if((((pucEmpData[5] << 8) | pucEmpData[6]) % 7) == 0)
                    {
                        ucMaxSize = MINOF((((WORD)(pucEmpData[5] << 8) | pucEmpData[6]) / 7), (_ADVANCED_HDR10_DHDR_EMP_MD_SIZE)) + 1;
                    }
                    else
                    {
                        ucMaxSize = MINOF((((WORD)(pucEmpData[5] << 8) | pucEmpData[6]) / 7 + 1), (_ADVANCED_HDR10_DHDR_EMP_MD_SIZE)) + 1;
                    }

                    usDhdrType = (((WORD)pucEmpData[3] << 8) | pucEmpData[4]);

                    // MLDS Detect
                    if(((((pucEmpData[5] << 8) | pucEmpData[6]) == 0x00) && (pucEmpData[2] != 0x00)) ||
                       ((((pucEmpData[5] << 8) | pucEmpData[6]) == 0x03) && (pucEmpData[2] == 0x00)))
                    {
                        bMldsEmp = _TRUE;
                        break;
                    }
                }
                else
                {
                    __real_memcpy(&pucMetaData[7 * (ucI - 1)], pucEmpData, 7);
                    ucLegalDataSize = ucLegalDataSize + 7;
                }
            }
            else
            {
                // R/W Conflict happened!
                break;
            }
        }

        if(bMldsEmp == _FALSE)
        {
            ucContryCode = pucMetaData[0];
            usProviderCode = TO_WORD(pucMetaData[1], pucMetaData[2]);
            usProviderOrientedCode = TO_WORD(pucMetaData[3], pucMetaData[4]);
            ucAppIdentifier = pucMetaData[5];
            ucAppVersion = pucMetaData[6];

            // Call Related IP FX process
            if((GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON) && (usDhdrType == _ADVANCED_HDR10_DHDR_INFO_TYPE) && (ScalerColorAdvancedHDR10CheckDHDRMetadta_EXINT0(ucContryCode, usProviderCode, usProviderOrientedCode, ucAppIdentifier, ucAppVersion) == _TRUE))
            {
                SET_TMDS_MAC_RX3_DHDR_EMP_TYPE40_RECEIVED();

                // HDR10+ Process
                ScalerColorAdvancedHDR10DHDRHandler_EXINT0(pucMetaData);
            }
        }
    }
#endif

#if((_HDMI_MAC_RX3_SUPPORT == _ON) & (_AUDIO_SUPPORT == _ON))
    // Detect if Auido Sampling is Changed
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET);
    if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Clear Auido Sampling Change Flag
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET);
        ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT1, _BIT1);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
        if(ScalerGetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT6) == 0x00)
        {
            // Set X Value
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_32_PORT_PAGE72_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Set Y Value
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_33_PORT_PAGE72_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // audio hw mode
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT6, _BIT6);

            // manual gain enable
            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT3, _BIT3);

            ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_9F_PORT_PAGE72_PRESET_AFSM_MOD, ~_BIT5, _BIT5);
        }
#endif
        // Disable FIFO Boundary Tracking, Disable Trend Tracking
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR);
        ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT3 | _BIT2), 0x00);

        // Set Double Buffer bit
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
        ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
        // Disable P Code Spread
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0);
        ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT7, 0x00);
#endif

        // Reload NF code
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
        ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, _BIT5);
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
        ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, 0x00);

        // Set FW tracking reset
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() <= _AUDIO_FREQ_48K)
        {
            SET_HDMI_AUDIO_RX3_FW_TRACKING_RESET();
        }
#endif

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        enumAudioFreq = ScalerGetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // ======================================
        // SRC FS > FS Limint by user define
        // ======================================
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        if(enumAudioFreq > GET_HDMI_RX3_SAMPLING_FREQ_LIMIT())
        {
#if(_HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT == _ON)
            // Set Sampling Frequency to maximum value
            SET_HDMI_RX3_TARGET_SAMPLING_FREQ(GET_HDMI_RX3_SAMPLING_FREQ_LIMIT());
#else
            // Disable Audio output
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT6, 0x00);
#endif
        }
#endif
        // ======================================
        // SRC no audio packet
        // ======================================
        if(enumAudioFreq == _AUDIO_FREQ_NO_AUDIO)
        {
            // Set User Define Frequency When No Audio value
            SET_HDMI_RX3_TARGET_SAMPLING_FREQ(GET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE());

            // Enable Audio output when no audio packet
#if((_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON) && (_HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT == _OFF))
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT6, _BIT6);
#endif
        }

        // ======================================
        // Set Audio Output clk when no audio packet or fs > fs Limint by user define
        // ======================================
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        // No Audio Detect Set User Define Frequency When No Audio or fs > fs limint by user define Set User Define Limit Frequency
        if((enumAudioFreq == _AUDIO_FREQ_NO_AUDIO) || (enumAudioFreq > GET_HDMI_RX3_SAMPLING_FREQ_LIMIT()))
#else
        // No Audio Detect Set User Define Frequency When No Audio
        if(enumAudioFreq == _AUDIO_FREQ_NO_AUDIO)
#endif
        {
            // Disable Auto Load S & NF Code
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT6 | _BIT5), 0x00);

            // Set S code User Define
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR);
            ScalerSetByte_EXINT(P72_CA_HDMI_DP, ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ()));

            ScalerTmdsMacRxSetAudioNfCode_EXINT0(_RX3);

            // Set Double Buffer bit
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

            // Reload NF code
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, _BIT5);
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, 0x00);

            // CLR PLL Autoload Status Flag
            CLR_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ();
        }
#endif

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
        // Turn-off FIFO Tracking
        // Todo!!!

        // Set FW Mannual Mode
        // Todo!!!

        // Set TTS Play Error Flag
        SET_TTS_PLAYBACK_ERROR();
#endif

        SET_HDMI_AUDIO_RX3_SAMPLING_FREQ_CHANGE();
    }
#endif

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, pucBackUp[0]);

    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, pucBackUp[2]);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, pucBackUp[4]);
    ScalerSetByte_EXINT(P72_D0_HDMI_PSAP2, pucBackUp[5]);

    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[7]);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, pucBackUp[6]);
}

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
//--------------------------------------------------
// Description  : Check High Priority Irq Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3ClearHighPriorityIrqFlag_EXINT0(void)
{
    // Clear High Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_60_PORT_PAGE72_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT3);
}

//--------------------------------------------------
// Description  : Check Low Priority Irq Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3ClearLowPriorityIrqFlag_EXINT0(void)
{
    // Clear Low Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_60_PORT_PAGE72_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT7);
}

//--------------------------------------------------
// Description  : PS Check High Priority Irq Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3PsClearHighPriorityIrqFlag_EXINT0(void)
{
    // Clear High Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_60_PORT_PAGE72_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT3);
}

//--------------------------------------------------
// Description  : PS Check High Priority Irq Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3PsClearLowPriorityIrqFlag_EXINT0(void)
{
    // Clear High Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_60_PORT_PAGE72_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT7);
}
#endif

//--------------------------------------------------
// Description  : Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTmdsMacRx3MeasureClk_EXINT0(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;
    WORD usClkCount = 0;
    BYTE ucBackUp = 0;
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);

    // Enable Rx_EN (Lane3)
    ScalerTmdsPhyRxSetRxEn_EXINT0(enumMappingPort, _ENABLE);
    SET_HDMI_RX3_OFF_MEASURE_RESET_EXINT();

    if(ucMeasureClk == _CLK_SOURCE_TMDS)
    {
        // Set ref clk = GDI clk & Switch TMDS Clk to be measure
        ScalerSetBit_EXINT(P72_AD_TMDS_CPS, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
    }
    else
    {
        // Select CDR Clk to be measure from PHY
        ScalerTmdsPhyRxCdrMeasureClkSelect_EXINT0(enumMappingPort, ucMeasureClk);

        // Set ref clk = GDI clk & Switch CDR clk to be measure
        ScalerSetBit_EXINT(P72_AD_TMDS_CPS, ~(_BIT6 | _BIT4), _BIT4);
    }

    ucBackUp = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);

    // Start Measure
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT5 | _BIT3), _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US_EXINT();

        if((ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0);
    usClkCount = ((WORD)(ScalerGetByte_EXINT(P72_CA_HDMI_DP) & 0x07) << 8);

    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_29_PORT_PAGE72_HDMI_NTX1024TR1);
    usClkCount = usClkCount | ScalerGetByte_EXINT(P72_CA_HDMI_DP);

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, ucBackUp);

    return usClkCount;
}

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : RSVx into IRQ Handler
// Input Value  : ulOui, enumRsvNumber
// Output Value : void
//--------------------------------------------------
void ScalerTmdsMacRx3RsvVsifHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    enumRsvNumber = enumRsvNumber;
    DWORD ulOui = 0;

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    StructAdvancedHDR10MetaData stSyncAdvancedHDR10Metadata = {0};
#endif

#if(_DM_FUNCTION == _ON)
    BYTE pucDmMetaData[27] = {0};
    BYTE pucDmHb[3] = {0};
    BYTE ucStartAddr = 0;
#endif

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    ulOui = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);

    switch(ulOui)
    {
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        case _ADVANCED_HDR10_OUI:

            SET_TMDS_MAC_RX3_ADVANCED_HDR10_VSIF_RECEIVED();

            ScalerTmdsMacRx3GetAdvancedHdr10Vsif_EXINT0(enumRsvNumber, &stSyncAdvancedHDR10Metadata);

            ScalerColorAdvancedHDR10VSIFHandler_EXINT0(&stSyncAdvancedHDR10Metadata);

            break;
#endif

#if((_HDMI21_ALLM_SUPPORT == _ON) || (_HDMI21_CCBPC_SUPPORT == _ON))
        case _HF_VSIF_OUI:

            SET_TMDS_MAC_RX3_HF_VSIF_RECEIVED();

#if(_HDMI21_ALLM_SUPPORT == _ON)
            ScalerTmdsMacRx3AllmProc_EXINT0(enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
            ScalerTmdsMacRx3CcbpcProc_EXINT0(enumRsvNumber);
#endif
            break;
#endif

#if(_DM_FUNCTION == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        case ((_DM_OUI_0 << 16) | (_DM_OUI_1 << 8) | _DM_OUI_2):

            switch(enumRsvNumber)
            {
                case _HDMI_RSV_0:
                    ucStartAddr = 0x4E;
                    break;

                case _HDMI_RSV_1:
                    ucStartAddr = 0x6D;
                    break;

                case _HDMI_RSV_2:
                    ucStartAddr = 0x8C;
                    break;

                case _HDMI_RSV_3:
                    ucStartAddr = 0xAB;
                    break;

                default:

                    break;
            }

            ScalerGetDataPortByte_EXINT0(P72_CD_HDMI_PSAP, ucStartAddr, 3, pucDmHb, _AUTOINC);

            if((pucDmHb[1] == 0x01) && ((pucDmHb[2] & 0x1F) == 0x1B))
            {
                ScalerTmdsMacRx3GetDmVsif_EXINT0(enumRsvNumber, pucDmMetaData);

                if(((pucDmMetaData[3] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) == _BIT1) && ((pucDmMetaData[3] & (_BIT0)) == _BIT0)) // VS10=1, LL=1
                {
                    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);

                    SET_TMDS_MAC_RX3_DM_VSIF_RECEIVED();
                    ScalerDMMetadataSourceMapping_EXINT0(pucDmMetaData, _HDMI_DM_PKT_ENTRY, enumMappingPort);
                }
            }
            break;
#endif
#endif
        default:
            break;
    }
}
#endif

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : Get SPD Info Product Description
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3RsvSpdHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucI = 0;
    BYTE ucVnCount = 0;
    BYTE pucHdmiVenderName[4] = {0};

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    for(ucVnCount = 0; ucVnCount < 4; ucVnCount++)
    {
        pucHdmiVenderName[ucVnCount] = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
    }

    if(((pucHdmiVenderName[0] == 'M') && (pucHdmiVenderName[1] == 'S') && (pucHdmiVenderName[2] == 'F') && (pucHdmiVenderName[3] == 'T')) ||
       ((pucHdmiVenderName[0] == 'S') && (pucHdmiVenderName[1] == 'C') && (pucHdmiVenderName[2] == 'E') && (pucHdmiVenderName[3] == 'I')) ||
       ((pucHdmiVenderName[0] == 'N') && (pucHdmiVenderName[1] == 'V') && (pucHdmiVenderName[2] == 'I') && (pucHdmiVenderName[3] == 'D')))
    {
        g_stTmdsMacRx3SpdInfo.b1StructValuable = 0x01;
        __real_memcpy(&g_stTmdsMacRx3SpdInfo.pucHdmiVendorName[0], pucHdmiVenderName, 4);

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x5A);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x79);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x98);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0xB7);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 16; ucI++)
        {
            g_stTmdsMacRx3SpdInfo.pucHdmiProductDescription[ucI] = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
        }
    }
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    else if((pucHdmiVenderName[0] == 0x1A) && (pucHdmiVenderName[1] == 0x00) && (pucHdmiVenderName[2] == 0x00) && (GET_TMDS_MAC_RX3_FS_VALUABLE() == _FALSE))
    {
        SET_TMDS_MAC_RX3_FS_VALUABLE();

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x51);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x70);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0x8F);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, 0xAE);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 28; ucI++)
        {
            g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[ucI] = ScalerGetByte_EXINT(P72_CE_HDMI_PSDP);
        }
    }
#endif
}
#endif

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get EMP SRAM Data
// Input Value  : ucReadAddress, pucEmpData
// Output Value : bit (Correct data read or not)
//--------------------------------------------------
bit ScalerTmdsMacRx3GetEmpSramData_EXINT0(BYTE ucReadAddress, BYTE *pucEmpData)
{
    // Set read pointer & popup data
    ScalerSetByte_EXINT(P2E_80_HDMI_EMPAP0, ucReadAddress);
    ScalerSetBit_EXINT(P2E_80_HDMI_EMPAP0, ~_BIT7, _BIT7);

    if(ScalerGetBit_EXINT(P2E_89_HDMI_EMP_SRAM_CTRL1, _BIT3) == 0x00)
    {
        memcpy(pucEmpData, (volatile BYTE xdata *)P2E_81_HDMI_EMPDP0, 7);
        return _TRUE;
    }
    else
    {
        // [3] Read & Write happened at same time
        ScalerSetBit_EXINT(P2E_89_HDMI_EMP_SRAM_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : On Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTmdsMacRx3OnMeasureClk_EXINT0(BYTE ucLane)
{
    BYTE ucCount = 0;
    WORD usClkCount = 0;

    // Change Measure Count  64=>3
    ScalerSetByte_EXINT(P72_EC_HDMI_FREQDET_STABLE, _BIT1);

    // Read Lane0 Result
    ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), 0x00);
    ScalerTmdsPhyRxCdrMeasureClkSelect_EXINT0(ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3), ucLane);
    ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT5 | _BIT2), _BIT5);
    ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

    // Waiting For Measure Done -> 300us
    for(ucCount = 0; ucCount <= 60; ucCount++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, _BIT6) == _BIT6)
        {
            // POP Result
            ScalerSetBit_EXINT(P72_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

            usClkCount = ((DWORD)((WORD)(ScalerGetByte_EXINT(P72_ED_HDMI_FREQDET_RESULT_M) << 8) | ScalerGetByte_EXINT(P72_EE_HDMI_FREQDET_RESULT_L))*27 / 100);
            break;
        }
    }

    return usClkCount;
}

//--------------------------------------------------
// Description  : TMDS Save On Measure Stable times (EXINT0 Only)
// Input Value  : None
// Output Value : Stable Times
//--------------------------------------------------
BYTE ScalerTmdsMacRx3SaveOnMeasureSettings_EXINT0(void)
{
    return ScalerGetByte_EXINT(P72_EC_HDMI_FREQDET_STABLE);
}

//--------------------------------------------------
// Description  : TMDS Restore On Measure Stable times (EXINT0 Only)
// Input Value  : Stable Times
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3RestoreOnMeasureSettings_EXINT0(BYTE ucStableTimes)
{
    ScalerSetByte_EXINT(P72_EC_HDMI_FREQDET_STABLE, ucStableTimes);

    // Clear Unstable IRQ Flag
    ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Reset PHY to MAC input (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3ResetMacInput_EXINT0(void)
{
    // Reset PHY -> MAC Interface
    ScalerSetBit_EXINT(P72_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P72_A7_TMDS_PWDCTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Clear RGB Data Detection Flags
    ScalerSetBit_EXINT(P72_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3PSHighPriorityIntHandler_EXINT0(void)
{
#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);
#endif

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    BYTE pucBackUp[6];
#else
    BYTE pucBackUp[4];
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P72_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);

    pucBackUp[2] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);
    pucBackUp[3] = (ScalerGetByte_EXINT(P72_C2_HDCP_PCR) & 0x01);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    pucBackUp[4] = ScalerGetByte_EXINT(P72_39_HDMI_CTRL_39);
    pucBackUp[5] = (ScalerGetByte_EXINT(P72_38_HDMI_CTRL_38) & 0x01);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    ScalerTmdsMacRx3PsClearHighPriorityIrqFlag_EXINT0();
#endif

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P72_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P72_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV & Ri flag
        ScalerSetBit_EXINT(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT6));

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P72_AE_TMDS_RPS, ~_BIT1, _BIT1);

        SET_TMDS_MAC_RX3_BACKUP_HDCP_TYPE(_HDCP_14);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P72_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        ScalerTmdsHdcp2Rx3ResetProc_EXINT0();
#endif
    }

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P72_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P72_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetByte_EXINT(P72_25_HDMI_CTRL_25, _BIT3);

        // Set Read Request Enable
        SET_TMDS_MAC_RX3_HDMI20_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P72_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P72_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P72_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P72_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P72_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P72_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

        // Read Request Outcome Processing
        ScalerTmdsMacRx3ReadRequestProc_EXINT0(ScalerGetByte_EXINT(P72_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P72_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P72_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            ScalerTmdsMacRxSetScdcInfo_EXINT0(enumMappingPort);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
            if(ScalerTmdsMacRxGetFreeSyncSupport_EXINT0(enumMappingPort) == _FREESYNC_SUPPORT_ON)
            {
                ScalerTmdsMacRxSetAmdAupiScdcInfo_EXINT0(enumMappingPort, _ENABLE);
            }
            else
            {
                ScalerTmdsMacRxSetAmdAupiScdcInfo_EXINT0(enumMappingPort, _DISABLE);
            }
#endif
            // Clear HDMI 2.0 Read Request Enable
            CLR_TMDS_MAC_RX3_HDMI20_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P72_1C_HDMI_CTRL_1C, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P72_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P72_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P72_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTmdsMacRx3CheckCDRStable_EXINT(g_usTMDSRx3ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P72_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P72_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P72_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P72_23_HDMI_CTRL_23, ~(_BIT6 | _BIT1), _BIT6);
        }
    }
#endif // End of #if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
#endif // End of #if(_HDMI20_MAC_RX3_SUPPORT == _ON)

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, pucBackUp[0]);

    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, pucBackUp[2]);

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[5]);
    ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, pucBackUp[4]);
#endif
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3PSLowPriorityIntHandler_EXINT0(void)
{
    BYTE pucBackUp[2];

    pucBackUp[0] = ScalerGetByte_EXINT(P72_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    // Clear Low Priority IRQ Pending Flag
    ScalerTmdsMacRx3PsClearLowPriorityIrqFlag_EXINT0();
#endif

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, pucBackUp[0]);
}

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get SBTM Received
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SbtmSetting_EXINT0(void)
{
    bit bTrueVsEmp = _FALSE;
    bit bSbtmSetTag = _FALSE;
    bit bMldsEmp = _FALSE;
    BYTE ucI = 0x00;
    BYTE ucMaxSize = ((ScalerGetBit_EXINT(P2E_88_HDMI_EMP_SRAM_CTRL0, _BIT4) == _BIT4) ? _HDMI_EMP_SRAM_VS_SIZE : _HDMI_EMP_SRAM_TOTAL_SIZE); // 7 Byte as 1 unit
    BYTE pucEmpData[7] = {0};

    // W1C received flag
    ScalerSetBit_EXINT(P2E_70_EMP_VS, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // Read EMP SRAM Data
    for(ucI = 0; ucI < ucMaxSize; ucI++)
    {
        if(ScalerTmdsMacRx3GetEmpSramData_EXINT0((0x28 + ucI), pucEmpData) == _TRUE)
        {
            // PB0~6 (EMP Header)
            if(ucI == 0)
            {
                // Check length
                if((((pucEmpData[5] << 8) | pucEmpData[6]) % 7) == 0)
                {
                    ucMaxSize = MINOF(((((pucEmpData[5] << 8) | pucEmpData[6]) + 7) / 7), (_SBTM_VS_EMP_MD_SIZE + 1));
                }
                else
                {
                    ucMaxSize = MINOF(((((pucEmpData[5] << 8) | pucEmpData[6]) + 7) / 7 + 1), (_SBTM_VS_EMP_MD_SIZE + 1));
                }

                bTrueVsEmp = (pucEmpData[2] == 0x01);

                bSbtmSetTag = ((((WORD)(pucEmpData[3]) << 8) | pucEmpData[4]) == 0x0003) ? _TRUE : _FALSE;

                // MLDS Detect
                if(((((pucEmpData[5] << 8) | pucEmpData[6]) == 0x00) && (pucEmpData[2] != 0x00)) ||
                   ((((pucEmpData[5] << 8) | pucEmpData[6]) == 0x03) && (pucEmpData[2] == 0x00)))
                {
                    bMldsEmp = _TRUE;
                    break;
                }
            }
            else if(ucI == 1)
            {
                // set SBTM info
                g_stTmdsMacRx3HdmiSbtmInfo.ucSbtmVer = (pucEmpData[0] & 0x0F);
                g_stTmdsMacRx3HdmiSbtmInfo.ucSbtmMode = (pucEmpData[1] & 0x03);
                g_stTmdsMacRx3HdmiSbtmInfo.ucSbtmType = ((pucEmpData[1] & 0x0C) >> 2);
                g_stTmdsMacRx3HdmiSbtmInfo.ucSbtmGrmdMin = ((pucEmpData[1] & 0x30) >> 4);
                g_stTmdsMacRx3HdmiSbtmInfo.ucSbtmGrmdLum = ((pucEmpData[1] & 0xC0) >> 6);
                g_stTmdsMacRx3HdmiSbtmInfo.usFrmPbLimitInt = (((WORD)(pucEmpData[2] & 0x3F) << 8) | pucEmpData[3]);
            }
        }
        else
        {
            // R/W Conflict happened!
            break;
        }
    }

    if((bTrueVsEmp == _TRUE) && (bSbtmSetTag == _TRUE) && (bMldsEmp == _FALSE))
    {
        g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmReceive = _TRUE;
    }
}
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
//--------------------------------------------------
// Description  : Get DM Received
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3DMSetting_EXINT0(EnumInputPort enumMappingPort)
{
    EnumHdmiEmpType enumEmpType = _NONE_EMP;

    bit bTrueVsEmp = _FALSE;
    bit bMldsEmp = _FALSE;
    bit bDMSetTag = _FALSE;

    BYTE ucLegalDataSize = 0x00;
    BYTE ucI = 0x00;
    BYTE ucMaxSize = ((ScalerGetBit_EXINT(P2E_88_HDMI_EMP_SRAM_CTRL0, _BIT4) == _BIT4) ? _HDMI_EMP_SRAM_VS_SIZE : _HDMI_EMP_SRAM_TOTAL_SIZE); // 7 Byte as 1 unit

    BYTE pucEmpData[7] = {0};
    BYTE pucMetaData[_DM_VS_EMP_MD_SIZE * 7] = {0}; // 56 byte

    // W1C received flag
    ScalerSetBit_EXINT(P2E_70_EMP_VS, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // Read EMP SRAM Data
    for(ucI = 0; ucI < ucMaxSize; ucI++)
    {
        if(ScalerTmdsMacRx3GetEmpSramData_EXINT0((0x28 + ucI), pucEmpData) == _TRUE)
        {
            // PB0~6 (EMP Header)
            if(ucI == 0)
            {
                // Select how many times to popup data
                if((((pucEmpData[5] << 8) | pucEmpData[6]) % 7) == 0)
                {
                    ucMaxSize = MINOF(((((pucEmpData[5] << 8) | pucEmpData[6]) + 7) / 7), (_DM_VS_EMP_MD_SIZE + 1));
                }
                else
                {
                    ucMaxSize = MINOF(((((pucEmpData[5] << 8) | pucEmpData[6]) + 7) / 7 + 1), (_DM_VS_EMP_MD_SIZE + 1));
                }

                bTrueVsEmp = (pucEmpData[2] == 0x00);

                bDMSetTag = ((((WORD)(pucEmpData[3]) << 8) | pucEmpData[4]) == 0x0000) ? _TRUE : _FALSE;

                // MLDS Detect
                if(((((pucEmpData[5] << 8) | pucEmpData[6]) == 0x00) && (pucEmpData[2] != 0x00)) ||
                   ((((pucEmpData[5] << 8) | pucEmpData[6]) == 0x03) && (pucEmpData[2] == 0x00)))
                {
                    bMldsEmp = _TRUE;
                    break;
                }
            }
            else if(ucI == 1)
            {
                // Check DM EMP Type (OUI code, VS10, Low Latency, Organization_ID, DataSetTag)
                if((pucEmpData[0] == _DM_OUI_0) && (pucEmpData[1] == _DM_OUI_1) && (pucEmpData[2] == _DM_OUI_2))
                {
                    if(((pucEmpData[6] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) == _BIT1) &&
                       ((pucEmpData[6] & _BIT0) == _BIT0) && (bTrueVsEmp == _TRUE) && (bDMSetTag == _TRUE))
                    {
                        enumEmpType = _DM_VSEMP;
                    }
                }

                __real_memcpy(&pucMetaData[0], pucEmpData, 7);

                ucLegalDataSize = ucLegalDataSize + 7;
            }
            else // ucI: 2 ~ ucfactor
            {
                __real_memcpy(&pucMetaData[7 * (ucI - 1)], pucEmpData, 7);

                ucLegalDataSize = ucLegalDataSize + 7;
            }
        }
        else
        {
            // R/W Conflict happened!
            break;
        }
    }

    if((enumEmpType == _DM_VSEMP) && (bMldsEmp == _FALSE))
    {
        SET_TMDS_MAC_RX3_DM_EMP_RECEIVED();
        ScalerDMMetadataSourceMapping_EXINT0(pucMetaData, _HDMI_DM_EMP_ENTRY, enumMappingPort);
    }
}
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Read Request Outcome Case Processing(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3ReadRequestProc_EXINT0(BYTE ucRROutCome)
{
    // Get Read Request Outcome Case
    switch(ucRROutCome)
    {
        case _HDMI20_READ_REQUEST_ACK_DONE:
        case _HDMI20_READ_REQUEST_ACK_STOP:

            break;

        case _HDMI20_READ_REQUEST_NACK1:

            if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P72_1B_HDMI_CTRL_1B, ~(_BIT7 | _BIT6), _BIT7);
            }

            break;

        case _HDMI20_READ_REQUEST_NACK2:

            if(GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE() == _TRUE)
            {
                // Enable Read Request Retry
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Set SCDC Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetScdcInfo_EXINT0(void)
{
    // Set SCDC Info
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D0_PORT_PAGE72_HDMI_SCDC_D0, g_stTmdsMacRxScdcInfoSet.ucManufactureOuiL);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D1_PORT_PAGE72_HDMI_SCDC_D1, g_stTmdsMacRxScdcInfoSet.ucManufactureOuiM);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D2_PORT_PAGE72_HDMI_SCDC_D2, g_stTmdsMacRxScdcInfoSet.ucManufactureOuiH);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D3_PORT_PAGE72_HDMI_SCDC_D3, g_stTmdsMacRxScdcInfoSet.pucIdstring[0]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D4_PORT_PAGE72_HDMI_SCDC_D4, g_stTmdsMacRxScdcInfoSet.pucIdstring[1]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D5_PORT_PAGE72_HDMI_SCDC_D5, g_stTmdsMacRxScdcInfoSet.pucIdstring[2]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D6_PORT_PAGE72_HDMI_SCDC_D6, g_stTmdsMacRxScdcInfoSet.pucIdstring[3]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D7_PORT_PAGE72_HDMI_SCDC_D7, g_stTmdsMacRxScdcInfoSet.pucIdstring[4]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D8_PORT_PAGE72_HDMI_SCDC_D8, g_stTmdsMacRxScdcInfoSet.pucIdstring[5]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_D9_PORT_PAGE72_HDMI_SCDC_D9, g_stTmdsMacRxScdcInfoSet.pucIdstring[6]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_DA_PORT_PAGE72_HDMI_SCDC_DA, g_stTmdsMacRxScdcInfoSet.pucIdstring[7]);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_DB_PORT_PAGE72_HDMI_SCDC_DB, g_stTmdsMacRxScdcInfoSet.ucHdmiHwVersion);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_DC_PORT_PAGE72_HDMI_SCDC_DC, g_stTmdsMacRxScdcInfoSet.ucHdmiFwVersionMajor);
    ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_DD_PORT_PAGE72_HDMI_SCDC_DD, g_stTmdsMacRxScdcInfoSet.ucHdmiFwVersionMinor);
}

//--------------------------------------------------
// Description  : TMDS Set CED Lock Transition
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetCedLockTransition_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Clear CED Lock Transition Flag
        ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Enable Character Error Detction Function Lock Transition IRQ
        ScalerSetBit_EXINT(P72_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Enable Character Error Detection Function & Valid Flag
        ScalerSetBit_EXINT(P72_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
    }
    else
    {
        // Disable CED Function
        ScalerSetBit_EXINT(P72_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

        // Pop Up CED Error For Clear Error Counter
        ScalerSetBit_EXINT(P72_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

        // Disable CED Lock Transition IRQ & Flag
        ScalerSetBit_EXINT(P72_17_HDMI_CTRL_17, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P72_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Set AMD AUPI SCDC Info
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetAmdAupiScdcInfo_EXINT0(bit bEnable)
{
    if(GET_FREESYNC_HDMI_AUPI_INFO() != _TRUE)
    {
        return;
    }

    if(bEnable == _ENABLE)
    {
        // Set SCDC Info
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E0_PORT_PAGE72_HDMI_SCDC_E0, g_stDrrHdmiAmdAupiInfo.ucPanelManufactureIdL);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E1_PORT_PAGE72_HDMI_SCDC_E1, g_stDrrHdmiAmdAupiInfo.ucPanelManufactureIdM);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E2_PORT_PAGE72_HDMI_SCDC_E2, g_stDrrHdmiAmdAupiInfo.ucPanelIdL);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E3_PORT_PAGE72_HDMI_SCDC_E3, g_stDrrHdmiAmdAupiInfo.ucPanelIdM);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E4_PORT_PAGE72_HDMI_SCDC_E4, g_stDrrHdmiAmdAupiInfo.ucFwCheckSumL);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E5_PORT_PAGE72_HDMI_SCDC_E5, g_stDrrHdmiAmdAupiInfo.ucFwCheckSumM);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E6_PORT_PAGE72_HDMI_SCDC_E6, g_stDrrHdmiAmdAupiInfo.ucScalerDeviceIdL);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E7_PORT_PAGE72_HDMI_SCDC_E7, g_stDrrHdmiAmdAupiInfo.ucScalerDeviceIdM);
    }
    else
    {
        // Set SCDC Info
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E0_PORT_PAGE72_HDMI_SCDC_E0, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E1_PORT_PAGE72_HDMI_SCDC_E1, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E2_PORT_PAGE72_HDMI_SCDC_E2, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E3_PORT_PAGE72_HDMI_SCDC_E3, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E4_PORT_PAGE72_HDMI_SCDC_E4, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E5_PORT_PAGE72_HDMI_SCDC_E5, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E6_PORT_PAGE72_HDMI_SCDC_E6, 0x00);
        ScalerSetDataPortByte_EXINT0(P72_39_HDMI_CTRL_39, _P72_3A_PT_E7_PORT_PAGE72_HDMI_SCDC_E7, 0x00);
    }
}
#endif
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get DMDRAM Received
// Input Value  : enumInputPort
// Output Value : _FALSE/ _TRUE
//--------------------------------------------------
bit ScalerTmdsMacRx3GetDMDramReceived_EXINT0(void)
{
    if(ScalerGetBit_EXINT(P72_D5_HDMI_RSV64_IE, _BIT2) == _BIT2)
    {
        // w1c RSV received bit
        ScalerSetBit_EXINT(P72_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DM Packet ReCheck
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3DMPacketReCheck_EXINT0(void)
{
    BYTE pucBackUp[8];

    pucBackUp[0] = ScalerGetByte_EXINT(P72_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);

    pucBackUp[2] = ScalerGetByte_EXINT(P72_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P72_38_HDMI_CTRL_38) & 0x01);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Backup DFF #1 & #2
    pucBackUp[4] = ScalerGetByte_EXINT(P72_CD_HDMI_PSAP);
    pucBackUp[5] = ScalerGetByte_EXINT(P72_D0_HDMI_PSAP2);

    pucBackUp[6] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);
    pucBackUp[7] = (ScalerGetByte_EXINT(P72_C2_HDCP_PCR) & 0x01);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

    // "VS EMP" received into IRQ
    if(ScalerGetBit_EXINT(P2E_70_EMP_VS, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        if(ScalerGetByte_EXINT(P2E_7C_VS_ORG_ID) == _VENDOR_SPECIFIC)
        {
            EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3);

            ScalerTmdsMacRx3DMSetting_EXINT0(enumMappingPort);
        }
    }

    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_60_PORT_PAGE72_HDMI_INTCR);
    if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT7) == _BIT7)
    {
#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
        ScalerTmdsMacRx3ClearLowPriorityIrqFlag_EXINT0();
#endif

        // --- RSV0 Into IRQ ---
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
        if((ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P72_CC_HDMI_GPVS, _BIT5) == _BIT5))
        {
            ScalerSetByte_EXINT(P72_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P72_F8_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_0);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_0);
#endif
            }
        }

        // --- RSV1 Into IRQ ---
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
        if((ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P72_CC_HDMI_GPVS, _BIT6) == _BIT6))
        {
            ScalerSetByte_EXINT(P72_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P72_F9_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
            {
                ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_1);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_1);
#endif
            }
        }

        // --- RSV2 Into IRQ ---
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
        if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT2) == _BIT2)
        {
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR);
            if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT7) == _BIT7)
            {
                ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte_EXINT(P72_FA_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
                {
                    ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_2);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_2);
#endif
                }
            }
        }

        // --- RSV3 Into IRQ ---
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6);
        if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT3) == _BIT3)
        {
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR);
            if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, _BIT6) == _BIT6)
            {
                ScalerSetDataPortBit_EXINT0(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte_EXINT(P72_FB_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
                {
                    ScalerTmdsMacRx3RsvSpdHandler_EXINT0(_HDMI_RSV_3);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerTmdsMacRx3RsvVsifHandler_EXINT0(_HDMI_RSV_3);
#endif
                }
            }
        }

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
        // Detect if Auido Sampling is Changed
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET);
        if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
        {
            // Clear Auido Sampling Change Flag
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT1, _BIT1);

            // Disable FIFO Boundary Tracking, Disable Trend Tracking
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT3 | _BIT2), 0x00);

            // Set Double Buffer bit
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
            // Disable P Code Spread
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT7, 0x00);
#endif

            // Reload NF code
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, _BIT5);
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
            ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, 0x00);

            // Set FW tracking reset
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() <= _AUDIO_FREQ_48K)
            {
                SET_HDMI_AUDIO_RX3_FW_TRACKING_RESET();
            }
#endif

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            // No Audio Detect Set User Define Frequency When No Audio
            ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT);
            if(ScalerGetBit_EXINT(P72_CA_HDMI_DP, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
            {
                // Disable Auto Load S & NF Code
                ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
                ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT6 | _BIT5), 0x00);

                // Set S code User Define
                ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR);
                ScalerSetByte_EXINT(P72_CA_HDMI_DP, ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_HDMI, GET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE()));

                ScalerTmdsMacRxSetAudioNfCode_EXINT0(_RX3);

                // Set Double Buffer bit
                ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
                ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

                // Reload NF code
                ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
                ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, _BIT5);
                ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
                ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~_BIT5, 0x00);

                // CLR PLL Autoload Status Flag
                CLR_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ();
            }
#endif

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
            // Turn-off FIFO Tracking
            // Todo!!!

            // Set FW Mannual Mode
            // Todo!!!

            // Set TTS Play Error Flag
            SET_TTS_PLAYBACK_ERROR();
#endif

            SET_HDMI_AUDIO_RX3_SAMPLING_FREQ_CHANGE();
        }
#endif
    }

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, pucBackUp[0]);

    ScalerSetBit_EXINT(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P72_39_HDMI_CTRL_39, pucBackUp[2]);

    ScalerSetByte_EXINT(P72_CD_HDMI_PSAP, pucBackUp[4]);
    ScalerSetByte_EXINT(P72_D0_HDMI_PSAP2, pucBackUp[5]);

    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[7]);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, pucBackUp[6]);
}
#endif
#endif // End of #if(_HDMI_MAC_RX3_SUPPORT == _ON)
#endif // End of #if(_TMDS_MAC_RX3_SUPPORT == _ON)

