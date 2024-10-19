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
// ID Code      : ScalerHdmiFrlMacRx4_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIFRLMACRX4_EXINT0__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx4/ScalerHdmiFrlMacRx4.h"


#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Description  : GET HDR10+ VSIF From RSV
// Input Value  : RSV number, struct for PKT
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4GetAdvancedHdr10Vsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata)
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
    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 1));
    pstSyncAdvancedHDR10Metadata->ucVersion = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 4));
    for(ucI = 0; ucI < 3; ucI++)
    {
        pstSyncAdvancedHDR10Metadata->pucOUICode[ucI] = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    }

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 7));
    pstSyncAdvancedHDR10Metadata->ucTargetDisplayLv = ((ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & 0x3F) >> 1);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 13));
    pstSyncAdvancedHDR10Metadata->ucDistribution50 = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 17));
    pstSyncAdvancedHDR10Metadata->ucDistribution99 = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 21));
    for(ucI = 0; ucI < 9; ucI++)
    {
        pstSyncAdvancedHDR10Metadata->pucBezierAnchor[ucI] = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    }

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 18));
    ucKp1 = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    ucKp2 = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    ucKp3 = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    pstSyncAdvancedHDR10Metadata->pusKneePoint[0] = ((ucKp1 & 0x0F) << 6) + ((ucKp2 & 0xFC) >> 2);
    pstSyncAdvancedHDR10Metadata->pusKneePoint[1] = (((ucKp2 & 0x03) << 8) + ucKp3);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 30));
    pstSyncAdvancedHDR10Metadata->ucGraphicOverlayFlag = (ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) >> 7);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, (ucRsvStartAddr + 30));
    pstSyncAdvancedHDR10Metadata->ucNoDelayFlag = ((ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & 0x40) >> 6);
}

#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : GET DM VSIF From RSV
// Input Value  : RSV number, MetaData pointer
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4GetDmVsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, BYTE *pucDmMetaData)
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

    ScalerGetDataPortByte_EXINT0(P78_CD_HDMI_PSAP, ucRsvStartAddr, 27, pucDmMetaData, _AUTOINC);
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable ALLM
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4AllmProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    bit bAllm = 0;

#if(_DM_FUNCTION == _ON)
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);
#endif

    // Get ALLM bit
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x56);
            bAllm = (((ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x75);
            bAllm = (((ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x94);
            bAllm = (((ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0xB3);
            bAllm = (((ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    // Enable/Disable ALLM
    if(bAllm == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxSetDmAllmStatus_EXINT0(enumInputPort);
#endif
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();

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
void ScalerHdmiFrlMacRx4CcbpcProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucCcbpcValue = 0;

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x56);
            ucCcbpcValue = (ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x75);
            ucCcbpcValue = (ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x94);
            ucCcbpcValue = (ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0xB3);
            ucCcbpcValue = (ScalerGetByte_EXINT(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
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
void ScalerHdmiFrlMacRx4HighPriorityIntHandler_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);
    BYTE pucBackUp[8];

    pucBackUp[0] = ScalerGetByte_EXINT(P78_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P78_C8_HDMI_APC) & 0x01);

    pucBackUp[2] = ScalerGetByte_EXINT(P73_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P73_38_HDMI_CTRL_38) & 0x01);

    // Backup DFF #1 & #2
    pucBackUp[4] = ScalerGetByte_EXINT(P78_CD_HDMI_PSAP);
    pucBackUp[5] = ScalerGetByte_EXINT(P78_D0_HDMI_PSAP2);

    pucBackUp[6] = ScalerGetByte_EXINT(P73_C3_HDCP_AP);
    pucBackUp[7] = (ScalerGetByte_EXINT(P73_C2_HDCP_PCR) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, 0x00);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    ScalerHdmiFrlMacRx4ClearHighPriorityIrqFlag_EXINT0();
#endif

    // Source set FRL rate
    if((ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT6) == _BIT6) && (ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT7) == _BIT7))
    {
        // Clear FRL_rate flag and protect BIT5,3,1
        ScalerSetBit_EXINT(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

        // Clear SCDC FRL_start and event
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, 0x00);
        CLR_HDMI_FRL_MAC_RX4_FRL_START_EVENT();

        // Check FRL Rate is neighter 0 nor over max
        if(ScalerHdmiFrlMacRx4CheckFrlRate_EXINT0() == _TRUE)
        {
            // Set D Domain Region Free run/ Force to Background
            ScalerDDomainResetDDomainRgn(GET_TMDS_MAC_RX4_FORCE_BCKGRD_PATH());

            // Disable DPF CLK
            ScalerSetBit_EXINT(P69_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

            // Power down PLL
            ScalerSetBit_EXINT(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

            // Set MAC RX4 is FRL
            ScalerSetBit_EXINT(P1E_00_HDMI_TOP_0, ~_BIT6, _BIT6);

            // Enable HDCP2.2 & Disable HDCP 1.4 Module
            ScalerSetBit_EXINT(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P73_C0_HDCP_CR, ~_BIT0, 0x00);

            // Disable Hdcp 1.4 R0 ready bit
            ScalerSetBit_EXINT(P73_AE_TMDS_RPS, ~_BIT1, 0x00);

            // 4 lanes
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31);
            if(ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) >= _HDMI_FRL_RATE_6G_4LANES)
            {
                // Set FRL 4 lane mode
                ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, _BIT7);
                ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, _BIT2);
            }
            // 3 lanes
            else
            {
                // Set FRL 3 lane mode
                ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, 0x00);
            }

            // Turn off HDMI1.4/2.0 Freq. stable and unstable IRQ and detection
            ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1), 0x00);
            ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), 0x00);

            // Disable TMDS CED Function & Lock Transition
            ScalerTmdsMacRx4SetCedLockTransition_EXINT0(_DISABLE);

            // Clear SCDC Port Status Update Flag & CED Update Flag
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_10_PORT_PAGE73_HDMI_SCDC_10);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~(_BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Lock Flag
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerTmdsPhyRxFifoAutoResetEnable_EXINT0(enumMappingPort, _DISABLE);

            // If FRL_Rate != 0, clear TMDS PHY SET flag after turn off freq. stable IRQ
            CLR_TMDS_MAC_RX4_PHY_SET();

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
            // clr Retry to Set Phy Flag
            CLR_TMDS_MAC_RX4_RETRY_SET_PHY();

            // Cancel WD Timer Event
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY);
#endif

            // If FLT_update = 0 or any lane's LTP = 0, then can change LTP
            if((ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_10_PORT_PAGE73_HDMI_SCDC_10, _BIT5) == 0x00) ||
               (ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00) ||
               (ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00) ||
               (ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00) ||
               ((ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00) &&
                (ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) >= _HDMI_FRL_RATE_6G_4LANES)))
            {
                // Set Link Training pattern
                ScalerSetByte_EXINT(P1E_31_HDMI21_LT_1, 0x56);
                ScalerSetByte_EXINT(P1E_32_HDMI21_LT_2, 0x70);

                ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31);
                if(ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Set Lane3 pattern
                    ScalerSetBit_EXINT(P1E_32_HDMI21_LT_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                }

                // Set SCDC Link training pattern
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));

                // Set SCDC FLT_update and Status_update
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

                // need-check issue RR.
            }

            SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS3);
        }
        // FRL mode change to TMDS mode
        else if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) != _HDMI_FRL_RATE_NONE)
        {
            // Set D Domain Region Free run/ Force to Background
            ScalerDDomainResetDDomainRgn(GET_TMDS_MAC_RX4_FORCE_BCKGRD_PATH());

            // Disable DPF CLK
            ScalerSetBit_EXINT(P69_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

            // Power down PLL
            ScalerSetBit_EXINT(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

            // Set MAC RX4 is FRL
            ScalerSetBit_EXINT(P1E_00_HDMI_TOP_0, ~_BIT6, 0x00);

            // Disable HDCP2.2 & Enable HDCP 1.4 Module
            ScalerSetBit_EXINT(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P73_C0_HDCP_CR, ~_BIT0, _BIT0);

            // clear AKSV/ Bksv/ Ri flag
            ScalerSetBit_EXINT(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT6 | _BIT5));

            // Set link training check pattern
            ScalerSetByte_EXINT(P1E_31_HDMI21_LT_1, 0x00);
            ScalerSetByte_EXINT(P1E_32_HDMI21_LT_2, 0x00);

            // Set SCDC Link training pattern
            ScalerSetDataPortByte_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, 0x00);
            ScalerSetDataPortByte_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, 0x00);

            // Clear Rebuild PHY IRQ and flag
            ScalerSetByte_EXINT(P78_E6_HDMI_TRANSDET_CTRL2, 0x0F);

            // Clear Rebuild PHY Event
            CLR_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT();

            // Set Status_update
            ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~(_BIT5 | _BIT4 | _BIT0), _BIT0);

            SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSL);

            ScalerTmdsPhyRxFifoAutoResetEnable_EXINT0(enumMappingPort, _DISABLE);

            // If FRL_Rate = 0, clear TMDS PHY SET flag before enable freq. stable IRQ
            CLR_TMDS_MAC_RX4_PHY_SET();

#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
            // clr Retry to Set Phy Flag
            CLR_TMDS_MAC_RX4_RETRY_SET_PHY();

            // Cancel WD Timer Event
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY);
#endif

            // Enable Freq. Stable IRQ
            ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Start Freq. Detection
            ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);
        }

        // Clear FRL PHY SET flag
        CLR_HDMI_FRL_MAC_RX4_PHY_SET();

        CLR_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME();

        // Clear DPF Pixel Mode Mismatch flag
        CLR_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH();

        // Reset FFE level
        ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE0);
        ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE1);
        ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE2);
        ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE3);

        // Stop CED error count
        ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~_BIT6, 0x00);
        // ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Clear CED update flag
        ScalerSetBit_EXINT(P78_14_HDMI21_FRL_CED_12, ~_BIT6, _BIT6);

        // Disable RS FW error count and error flag
        ScalerSetBit_EXINT(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        ScalerSetBit_EXINT(P69_1A_HDMI21_FW_RS_6, ~_BIT2, _BIT2);
        ScalerSetBit_EXINT(P69_19_HDMI21_FW_RS_5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

        // Disable RS error count and valid and RS_update flag
        ScalerSetBit_EXINT(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), _BIT1);
        ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT5, 0x00);

        ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31);
        ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Read SCDC FFE max level for current FRL Rate
        ScalerHdmiFrlMacRxSetDxFrlMaxFfeLevel_EXINT0(enumMappingPort, ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

        SET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT();
    }

    // Source clear FRL_Start
    if((ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT5) == _BIT5))
    {
        // Clear FRL_Start flag and protect BIT7,3,1
        ScalerSetBit_EXINT(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

        SET_HDMI_FRL_MAC_RX4_FRL_START_EVENT();

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        if(GET_TMDS_HDCP2_RX4_AUTHENTICATION_DONE() == _TRUE)
        {
            ScalerSetDataPortBit_EXINT0(P73_C3_HDCP_AP, _P73_C4_PT_71_PORT_PAGE73_HDCP2_STATUS2, ~_BIT3, _BIT3);
        }
#endif

        // need-check if need, rebuild phy here
    }

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    // Source clear Status update
    if((ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT1) == _BIT1))
    {
        // Clear status update flag and protect BIT7,5,3
        ScalerSetBit_EXINT(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT1);

        // Clear SCDC 0x40[7] DSC dec fail
        ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, 0x00);
    }
#endif

    // FRL Lane0 SR/SSB Lock/Unlock transition
    if((ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT0) == _BIT0))
    {
        // Clear Lane0 flag and protect BIT7,6,5
        ScalerSetBit_EXINT(P78_17_HDMI21_FRL_CED_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

        // Lock
        if(ScalerGetBit_EXINT(P78_16_HDMI21_FRL_CED_14, _BIT7) == _BIT7)
        {
            // Set SCDC Lane0 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT1, _BIT1);

            SET_HDMI_FRL_MAC_RX4_LANE0_LOCK();

            if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) && (GET_HDMI_FRL_MAC_RX4_FRL_START_EVENT() == _FALSE))
            {
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, _BIT4);
            }
        }
        else
        {
            // Clear SCDC Lane0 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT1, 0x00);

            CLR_HDMI_FRL_MAC_RX4_LANE0_LOCK();
        }

        // set status_update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);
    }

    // FRL Lane1 SR/SSB Lock/Unlock transition
    if((ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT1) == _BIT1))
    {
        // Clear Lane1 flag and protect BIT7,6,4
        ScalerSetBit_EXINT(P78_17_HDMI21_FRL_CED_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // Lock
        if(ScalerGetBit_EXINT(P78_16_HDMI21_FRL_CED_14, _BIT6) == _BIT6)
        {
            // Set SCDC Lane1 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT2, _BIT2);

            SET_HDMI_FRL_MAC_RX4_LANE1_LOCK();

            if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) && (GET_HDMI_FRL_MAC_RX4_FRL_START_EVENT() == _FALSE))
            {
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, _BIT4);
            }
        }
        else
        {
            // Clear SCDC Lane1 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT2, 0x00);

            CLR_HDMI_FRL_MAC_RX4_LANE1_LOCK();
        }

        // set status_update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);
    }

    // FRL Lane2 SR/SSB Lock/Unlock transition
    if((ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT6) == _BIT6) && (ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT2) == _BIT2))
    {
        // Clear Lane2 flag and protect BIT7,5,4
        ScalerSetBit_EXINT(P78_17_HDMI21_FRL_CED_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

        // Lock
        if(ScalerGetBit_EXINT(P78_16_HDMI21_FRL_CED_14, _BIT5) == _BIT5)
        {
            // Set SCDC Lane2 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT3, _BIT3);

            SET_HDMI_FRL_MAC_RX4_LANE2_LOCK();

            if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) && (GET_HDMI_FRL_MAC_RX4_FRL_START_EVENT() == _FALSE))
            {
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, _BIT4);
            }
        }
        else
        {
            // Clear SCDC Lane2 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT3, 0x00);

            CLR_HDMI_FRL_MAC_RX4_LANE2_LOCK();
        }

        // set status_update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);
    }

    // FRL Lane3 SR/SSB Lock/Unlock transition
    if((ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P78_17_HDMI21_FRL_CED_15, _BIT3) == _BIT3))
    {
        // Clear Lane3 flag and protect BIT6,5,4
        ScalerSetBit_EXINT(P78_17_HDMI21_FRL_CED_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

        // Lock
        if(ScalerGetBit_EXINT(P78_16_HDMI21_FRL_CED_14, _BIT4) == _BIT4)
        {
            // Set SCDC Lane3 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT4, _BIT4);

            SET_HDMI_FRL_MAC_RX4_LANE3_LOCK();

            if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) && (GET_HDMI_FRL_MAC_RX4_FRL_START_EVENT() == _FALSE))
            {
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, _BIT4);
            }
        }
        else
        {
            // Clear SCDC Lane3 Lock bit
            ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT4, 0x00);

            CLR_HDMI_FRL_MAC_RX4_LANE3_LOCK();
        }

        // set status_update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);
    }

    // Detect HDMI HPD IRQ
    /*if(ScalerGetBit_EXINT(P73_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT1 | _BIT0), _BIT1);

        if(ScalerGetBit_EXINT(P73_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2F_HDMI_CTRL_2F, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));
            ScalerSetByte_EXINT(P78_12_HDMI21_FRL_CED_10, 0x05);

            // Clear CED Valid flag
            ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P78_17_HDMI21_FRL_CED_15, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable CED count and running disparity
            ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // Clear CED_update
            ScalerSetBit_EXINT(P78_14_HDMI21_FRL_CED_12, ~_BIT6, _BIT6);

            // Disable RS FW count
            ScalerSetBit_EXINT(P69_19_HDMI21_FW_RS_5, ~_BIT7, 0x00);

            // Clear RS FW error
            ScalerSetBit_EXINT(P69_1A_HDMI21_FW_RS_6, ~_BIT2, _BIT2);

            // Disable RS count and RS Valid flag
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), 0x00);

            // Disable RS_update and IRQ and clear RS_update
            ScalerSetBit_EXINT(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT2 | _BIT1), _BIT1);

            // Clear All SCDC Port Register
            ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

#if((_HDMI_SUPPORT == _ON) && (_HDMI20_SUPPORT == _ON))
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
#endif

            // Disable High to Low IRQ and enable Low to High IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Enable Low to High IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2E_HDMI_CTRL_2E, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));

            // Disable CED Update Read Request Auto Mode
            // ScalerSetBit_EXINT(P73_24_HDMI_CTRL_24, ~_BIT0, 0x00);
        }
        else
        {
            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2D_HDMI_CTRL_2D, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));

            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // if(ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, _BIT6) == 0x00)
            // {
                // Enable FLT_Ready
                // ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT6, _BIT6);

                // Set Status update
                //ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);
            // }

            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2C_HDMI_CTRL_2C, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));

            // Disable Low to High IRQ and enable High to Low IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // Enable High to Low IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }*/

    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[7]);
    ScalerSetByte_EXINT(P73_C3_HDCP_AP, pucBackUp[6]);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, pucBackUp[4]);
    ScalerSetByte_EXINT(P78_D0_HDMI_PSAP2, pucBackUp[5]);

    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, pucBackUp[2]);

    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, pucBackUp[0]);
}

//--------------------------------------------------
// Description  : Check Low Priority Irq
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4LowPriorityIntHandler_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);
    BYTE pucBackUp[8];
#if((_AUDIO_SUPPORT == _ON) & (_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF))
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P78_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P78_C8_HDMI_APC) & 0x01);

    pucBackUp[2] = ScalerGetByte_EXINT(P73_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P73_38_HDMI_CTRL_38) & 0x01);

    // Backup DFF #1 & #2
    pucBackUp[4] = ScalerGetByte_EXINT(P78_CD_HDMI_PSAP);
    pucBackUp[5] = ScalerGetByte_EXINT(P78_D0_HDMI_PSAP2);

    pucBackUp[6] = ScalerGetByte_EXINT(P73_C3_HDCP_AP);
    pucBackUp[7] = (ScalerGetByte_EXINT(P73_C2_HDCP_PCR) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, 0x00);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    ScalerHdmiFrlMacRx4ClearLowPriorityIrqFlag_EXINT0();
#endif

    // Source clear FLT_update
    if((ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P73_3D_HDMI21_LT_0, _BIT3) == _BIT3))
    {
        // Clear FLT_update flag and protect BIT7,5,1
        ScalerSetBit_EXINT(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);

        // If FLT_update = 0 and FRL_Rate != 0, then can change LTP
        if((ScalerGetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_10_PORT_PAGE73_HDMI_SCDC_10, _BIT5) == 0x00) && (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) != _HDMI_FRL_RATE_NONE))
        {
            // Check Data link has signal or not
            if((GET_HDMI_FRL_MAC_RX4_PHY_SET() == _FALSE) && (ScalerGetByte_EXINT(P1E_31_HDMI21_LT_1) != 0x00) && (ScalerGetByte_EXINT(P1E_31_HDMI21_LT_1) != 0xFF))
            {
                // Set PHY
                if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) == _HDMI_FRL_RATE_12G)
                {
                    ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 12);
                }
                else if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) == _HDMI_FRL_RATE_10G)
                {
                    ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 10);
                }
                else if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) == _HDMI_FRL_RATE_8G)
                {
                    ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 8);
                }
                else if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) == _HDMI_FRL_RATE_6G_4LANES)
                {
                    ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 6);
                }
                else if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) == _HDMI_FRL_RATE_6G_3LANES)
                {
                    ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 3, 6);
                }
                else if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) == _HDMI_FRL_RATE_3G)
                {
                    ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 3, 3);
                }

                // if(ScalerHdmiFrlPhyRx4PhyCheck_EXINT0() == _TRUE) //need-check, if fail then?
                {
                    // Reset PHY -> MAC Interface
                    ScalerSetBit_EXINT(P78_A7_TMDS_PWDCTL, ~_BIT4, 0x00);

                    // Enable small FIFO read clock
                    ScalerSetBit_EXINT(P78_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

                    SET_HDMI_FRL_MAC_RX4_PHY_SET();

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                    if(GET_TMDS_HDCP2_RX4_AUTHENTICATION_DONE() == _TRUE)
                    {
                        ScalerTimerWDActivateTimerEvent_EXINT0(500, _SCALER_WD_TIMER_EVENT_RX4_HDCP2_SET_REAUTH);
                    }
#endif
                }

                // Clear SCDC FRL_start
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, 0x00);

                ////////////////////////////////
                // Check Link Training Result //
                ////////////////////////////////

                // Set Link training pattern check cycle
                ScalerSetBit_EXINT(P1E_30_HDMI21_LT_0, ~(_BIT3 | _BIT2 | _BIT1), _BIT1);

                // Clear Link training check result
                ScalerSetBit_EXINT(P1E_33_HDMI21_LT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                // 4 lanes mode
                if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Start check
                    ScalerSetBit_EXINT(P1E_30_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
                }
                else
                {
                    // Start check
                    ScalerSetBit_EXINT(P1E_30_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));
                }

                // Wait for checking
                DELAY_XUS_EXINT(150); // 3G is 24.576us * (4 + 1) cycle = 122.88us

                // Link training pass
                if((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) ||
                   ((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5)) && (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)))
                {
                    // Set Lane0~4 pattern
                    ScalerSetByte_EXINT(P1E_31_HDMI21_LT_1, 0x00);
                    ScalerSetByte_EXINT(P1E_32_HDMI21_LT_2, 0x00);

                    // Set SCDC Link training pattern
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                }
                // Link training fail
                else if(((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT7) == 0x00) && (ScalerHdmiFrlMacRxGetDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE0) == ScalerHdmiFrlMacRxGetDxFrlMaxFfeLevel_EXINT0(enumMappingPort))) ||
                        ((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT6) == 0x00) && (ScalerHdmiFrlMacRxGetDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE1) == ScalerHdmiFrlMacRxGetDxFrlMaxFfeLevel_EXINT0(enumMappingPort))) ||
                        ((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT5) == 0x00) && (ScalerHdmiFrlMacRxGetDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE2) == ScalerHdmiFrlMacRxGetDxFrlMaxFfeLevel_EXINT0(enumMappingPort))) ||
                        ((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT4) == 0x00) && (ScalerHdmiFrlMacRxGetDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE3) == ScalerHdmiFrlMacRxGetDxFrlMaxFfeLevel_EXINT0(enumMappingPort)) && (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)))
                {
                    // Set link training check pattern Lane0~2
                    ScalerSetByte_EXINT(P1E_31_HDMI21_LT_1, 0xFF);
                    ScalerSetByte_EXINT(P1E_32_HDMI21_LT_2, 0xF0);

                    if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                    {
                        // Set Lane3 pattern
                        ScalerSetBit_EXINT(P1E_32_HDMI21_LT_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }

                    // Set SCDC Link training pattern
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));

                    CLR_HDMI_FRL_MAC_RX4_PHY_SET();
                }
                else
                {
                    // Add Lane0 FFE
                    if(ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT7) == 0x00)
                    {
                        // Set SCDC Link training pattern request = 0xE
                        ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

                        // Set Status_update
                        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);

                        ScalerHdmiFrlMacRxAddDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE0);

                        CLR_HDMI_FRL_MAC_RX4_PHY_SET();
                    }

                    // Add Lane1 FFE
                    if(ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT6) == 0x00)
                    {
                        // Set SCDC Link training pattern request = 0xE
                        ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

                        // Set Status_update
                        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);

                        ScalerHdmiFrlMacRxAddDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE1);

                        CLR_HDMI_FRL_MAC_RX4_PHY_SET();
                    }

                    // Add Lane2 FFE
                    if(ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT5) == 0x00)
                    {
                        // Set SCDC Link training pattern request = 0xE
                        ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

                        // Set Status_update
                        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);

                        ScalerHdmiFrlMacRxAddDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE2);

                        CLR_HDMI_FRL_MAC_RX4_PHY_SET();
                    }

                    // Add Lane3 FFE
                    if((ScalerGetBit_EXINT(P1E_33_HDMI21_LT_3, _BIT4) == 0x00) && (ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES))
                    {
                        // Set SCDC Link training pattern request = 0xE
                        ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

                        // Set Status_update
                        ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);

                        ScalerHdmiFrlMacRxAddDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE3);

                        CLR_HDMI_FRL_MAC_RX4_PHY_SET();
                    }
                }

                // Set SCDC FLT_update and Status_update
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

                // need-check issue RR.
            }
            // Sink want to Re-Link Training
            else if(GET_HDMI_FRL_MAC_RX4_PHY_SET() == _FALSE)
            {
                // Set Link Training pattern
                ScalerSetByte_EXINT(P1E_31_HDMI21_LT_1, 0x56);
                ScalerSetByte_EXINT(P1E_32_HDMI21_LT_2, 0x70);

                if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Set Lane3 pattern
                    ScalerSetBit_EXINT(P1E_32_HDMI21_LT_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                }

                // Clear SCDC FRL_start
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT4, 0x00);
                CLR_HDMI_FRL_MAC_RX4_FRL_START_EVENT();

                // Reset FFE level
                ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE0);
                ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE1);
                ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE2);
                ScalerHdmiFrlMacRxClrDxFrlFfeLevel_EXINT0(enumMappingPort, _HDMI_FRL_LANE3);

                // Set SCDC Link training pattern
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_41_PORT_PAGE73_HDMI_SCDC_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_31_HDMI21_LT_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                ScalerSetDataPortBit_EXINT0(P73_39_HDMI_CTRL_39, _P73_3A_PT_42_PORT_PAGE73_HDMI_SCDC_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit_EXINT(P1E_32_HDMI21_LT_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));

                // Set SCDC FLT_update and Status_update
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

                // need-check issue RR.

                SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS3);
            }
            else if(GET_HDMI_FRL_MAC_RX4_PHY_SET() == _TRUE)
            {
                // ScalerHdmi21PhyRx4DfeFinetune_EXINT0(); //need-check

                if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Start disparity calculation 4 lanes
                    ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
                else
                {
                    // Start disparity calculation 3 lanes
                    ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
                }

                // Clear Gap err
                ScalerSetBit_EXINT(P1E_39_HDMI21_LT_9, ~_BIT6, _BIT6);

                // enable Gap pattern check
                ScalerSetBit_EXINT(P1E_39_HDMI21_LT_9, ~(_BIT7 | _BIT6), _BIT7);

                DELAY_XUS_EXINT(150); // 4us * 33 super block = 132 us

                // disable Gap pattern check
                ScalerSetBit_EXINT(P1E_39_HDMI21_LT_9, ~(_BIT7 | _BIT6), 0x00);

                // Gap pattern error
                if(ScalerGetBit_EXINT(P1E_39_HDMI21_LT_9, _BIT6) == _BIT6)
                {
                    // ????????????????????
                }

                // bypass GAP pattern check
                if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Start CED 4 lanes
                    ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                    // Enable lock transition IRQ, need 3 super blocks ~37us@3G
                    ScalerSetByte_EXINT(P78_17_HDMI21_FRL_CED_15, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
                else
                {
                    // Start CED 3 lanes
                    ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

                    // Enable lock transition IRQ, need 3 super blocks ~37us@3G
                    ScalerSetByte_EXINT(P78_17_HDMI21_FRL_CED_15, (_BIT2 | _BIT1 | _BIT0));
                }

                SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSP_GAP);
            }
        }
    }

    // Rebuild PHY in PS -> PN @ L0
    if((ScalerGetBit_EXINT(P78_E6_HDMI_TRANSDET_CTRL2, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P78_E6_HDMI_TRANSDET_CTRL2, _BIT3) == _BIT3))
    {
        BYTE ucI = 0x00;
        BYTE pucFrlRate[4] = {0};
        BYTE ucBackupTimes = ScalerGetBit_EXINT(P78_E9_HDMI_TRANSDET_CTRL5, (_BIT7 | _BIT6 | _BIT5));

        // record L0 reseult
        pucFrlRate[0] = (ScalerGetByte_EXINT(P78_E3_HDMI_TRANSDET_LMS0) >> 5);

        // turn off int and clear flag
        ScalerSetBit_EXINT(P78_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3), _BIT3);

        // Set MAC is 2.1
        ScalerSetBit_EXINT(P1E_00_HDMI_TOP_0, ~_BIT6, _BIT6);

        // Enable HDCP2.2 & Disable HDCP 1.4 Module
        ScalerSetBit_EXINT(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P73_C0_HDCP_CR, ~_BIT0, 0x00);

        // Disable Hdcp 1.4 R0 ready bit
        ScalerSetBit_EXINT(P73_AE_TMDS_RPS, ~_BIT1, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        if(GET_TMDS_HDCP2_RX4_AUTHENTICATION_DONE() == _TRUE)
        {
            ScalerTimerWDActivateTimerEvent_EXINT0(500, _SCALER_WD_TIMER_EVENT_RX4_HDCP2_SET_REAUTH);
        }
#endif

        // Turn off HDMI1.4/2.0 Freq. stable and unstable IRQ and detection
        ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1), 0x00);
        ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), 0x00);

        // Disable TMDS CED Function & Lock Transition
        ScalerTmdsMacRx4SetCedLockTransition_EXINT0(_DISABLE);

        // Stop CED error count
        ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~_BIT6, 0x00);
        // ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Clear CED update flag
        ScalerSetBit_EXINT(P78_14_HDMI21_FRL_CED_12, ~_BIT6, _BIT6);

        // Disable RS error count and valid and RS_update flag
        ScalerSetBit_EXINT(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), _BIT1);
        ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT5, 0x00);

        // Measure times set to 2
        ScalerSetBit_EXINT(P78_E9_HDMI_TRANSDET_CTRL5, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        for(ucI = 1; ucI < 4; ucI++)
        {
            // Select which lane to detect & restart measure
            ScalerSetBit_EXINT(P78_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, 0x00);
            ScalerTmdsPhyRxTransitionDataLaneSelect_EXINT0(enumMappingPort, ucI);
            ScalerSetBit_EXINT(P78_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, _BIT7);

            // Delay (HW measure time may be 80us for cycle=1000 & times = 2)
            DELAY_XUS_EXINT(120);

            pucFrlRate[ucI] = (ScalerGetByte_EXINT(P78_E3_HDMI_TRANSDET_LMS0) >> 5);
        }

        // check FRL Rate then set Phy
        if((pucFrlRate[0] == 5) && (pucFrlRate[1] == 5) && (pucFrlRate[2] == 5) && (pucFrlRate[3] == 5))
        {
            // turn on 4 Lane mode
            ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, _BIT2);

            ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, _HDMI_FRL_RATE_12G);

            // Set PHY
            ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 12);
        }
        else if((pucFrlRate[0] == 4) && (pucFrlRate[1] == 4) && (pucFrlRate[2] == 4) && (pucFrlRate[3] == 4))
        {
            // turn on 4 Lane mode
            ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, _BIT2);

            ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, _HDMI_FRL_RATE_10G);

            // Set PHY
            ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 10);
        }
        else if((pucFrlRate[0] == 3) && (pucFrlRate[1] == 3) && (pucFrlRate[2] == 3) && (pucFrlRate[3] == 3))
        {
            // turn on 4 Lane mode
            ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, _BIT2);

            ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, _HDMI_FRL_RATE_8G);

            // Set PHY
            ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 8);
        }
        else if((pucFrlRate[0] == 2) && (pucFrlRate[1] == 2) && (pucFrlRate[2] == 2) && (pucFrlRate[3] == 2))
        {
            // turn on 4 Lane mode
            ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, _BIT2);

            ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, _HDMI_FRL_RATE_6G_4LANES);

            // Set PHY
            ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 4, 6);
        }
        else if((pucFrlRate[0] == 2) && (pucFrlRate[1] == 2) && (pucFrlRate[2] == 2))
        {
            // turn on 3 Lane mode
            ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, 0x00);

            ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, _HDMI_FRL_RATE_6G_3LANES);

            // Set PHY
            ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 3, 6);
        }
        else if((pucFrlRate[0] == 1) && (pucFrlRate[1] == 1) && (pucFrlRate[2] == 1))
        {
            // turn on 3 Lane mode
            ScalerSetBit_EXINT(P1E_38_HDMI21_LT_8, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~_BIT2, 0x00);

            ScalerHdmiFrlMacRxSetDxFrlRate_EXINT0(enumMappingPort, _HDMI_FRL_RATE_3G);

            // Set PHY
            ScalerTmdsPhyRxFrlSetPhy_EXINT0(enumMappingPort, 3, 3);
        }

        // if(ScalerHdmiFrlPhyRx4PhyCheck_EXINT0() == _TRUE) //need-check, if fail then?
        {
            // Reset PHY -> MAC Interface
            ScalerSetBit_EXINT(P78_A7_TMDS_PWDCTL, ~_BIT4, 0x00);

            // Enable small FIFO read clock
            ScalerSetBit_EXINT(P78_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

            SET_HDMI_FRL_MAC_RX4_PHY_SET();

            // turn off transition detection
            ScalerSetBit_EXINT(P78_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, 0x00);
        }

        // switch back measure time = 8 & L0 to measure
        ScalerSetBit_EXINT(P78_E9_HDMI_TRANSDET_CTRL5, ~(_BIT7 | _BIT6 | _BIT5), ucBackupTimes);
        ScalerTmdsPhyRxTransitionDataLaneSelect_EXINT0(enumMappingPort, 0);

        // Disable transition data from PHY
        ScalerTmdsPhyRxTransitionDataEnable_EXINT0(enumMappingPort, _DISABLE);

        if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            // Start disparity calculation 4 lanes
            ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Start disparity calculation 3 lanes
            ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
        }

        DELAY_XUS_EXINT(150); // wait disparity stable

        // bypass GAP pattern check
        if(ScalerHdmiFrlMacRxGetDxFrlRate_EXINT0(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            // Start CED 4 lanes
            ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Enable lock transition IRQ, need 3 super blocks ~37us@3G
            ScalerSetByte_EXINT(P78_17_HDMI21_FRL_CED_15, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Start CED 3 lanes
            ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

            // Enable lock transition IRQ, need 3 super blocks ~37us@3G
            ScalerSetByte_EXINT(P78_17_HDMI21_FRL_CED_15, (_BIT2 | _BIT1 | _BIT0));
        }

        DELAY_XUS_EXINT(150); // wait lane lock, 4us * 33 super block = 132 us

        SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSP_GAP);
    }


#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
    // --- RSV0 Into IRQ ---
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
    if((ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P78_CC_HDMI_GPVS, _BIT5) == _BIT5))
    {
        ScalerSetByte_EXINT(P78_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
        if(ScalerGetByte_EXINT(P78_96_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
        {
            ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_0);
        }
        else
#endif
        {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
            ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_0);
#endif
        }
    }

    // --- RSV1 Into IRQ ---
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
    if((ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P78_CC_HDMI_GPVS, _BIT6) == _BIT6))
    {
        ScalerSetByte_EXINT(P78_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
        if(ScalerGetByte_EXINT(P78_97_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
        {
            ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_1);
        }
        else
#endif
        {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
            ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_1);
#endif
        }
    }

    // --- RSV2 Into IRQ ---
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
    if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT2) == _BIT2)
    {
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR);
        if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT7) == _BIT7)
        {
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P78_98_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_2);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_2);
#endif
            }
        }
    }

    // --- RSV3 Into IRQ ---
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
    if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT3) == _BIT3)
    {
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR);
        if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT6) == _BIT6)
        {
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P78_99_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_3);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_3);
#endif
            }
        }
    }
#endif

#if(((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE)) || (_HDMI_SBTM_SUPPORT == _ON))
    // "VS EMP" received into IRQ
    if(ScalerGetBit_EXINT(P1E_51_EMP_VS, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        if(ScalerGetByte_EXINT(P1E_BC_VS_ORG_ID) == _VENDOR_SPECIFIC)
        {
#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            ScalerHdmiFrlMacRx4DMSetting_EXINT0(enumMappingPort);
#endif
        }
        else if(ScalerGetByte_EXINT(P1E_BC_VS_ORG_ID) == _HDMI21)
        {
#if(_HDMI_SBTM_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4SbtmSetting_EXINT0();
#endif
        }
    }
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
    // "D-HDR EMP" received into IRQ
    if(ScalerGetBit_EXINT(P1E_53_EMP_DHDR, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        bit bMldsEmp = _FALSE;

        BYTE ucI = 0x00;
        BYTE ucLegalDataSize = 0x00;
        BYTE ucMaxSize = ((ScalerGetBit_EXINT(P1E_C8_HDMI_EMP_SRAM_CTRL0, _BIT4) == _BIT4) ? _HDMI_EMP_SRAM_DHDR_SIZE : _HDMI_EMP_SRAM_TOTAL_SIZE); // 7 Byte as 1 unit

        BYTE pucEmpData[7] = {0};
        BYTE pucMetaData[_ADVANCED_HDR10_DHDR_EMP_MD_SIZE * 7] = {0}; // 112

        WORD usDhdrType = 0;
        BYTE ucContryCode = 0;
        WORD usProviderCode = 0;
        WORD usProviderOrientedCode = 0;
        BYTE ucAppIdentifier = 0;
        BYTE ucAppVersion = 0;

        // w1c received flag
        ScalerSetBit_EXINT(P1E_53_EMP_DHDR, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

        // Read EMP SRAM Data
        for(ucI = 0; ucI < ucMaxSize; ucI++)
        {
            if(ScalerHdmiFrlMacRx4GetEmpSramData_EXINT0((0x00 + ucI), pucEmpData) == _TRUE)
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
                SET_HDMI_FRL_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED();

                // HDR10+ Process
                ScalerColorAdvancedHDR10DHDRHandler_EXINT0(pucMetaData);
            }
        }
    }
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
    // Detect if Auido Sampling is Changed
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET);
    if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Clear Auido Sampling Change Flag
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET);
        ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT1, _BIT1);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
        if(ScalerGetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, _BIT6) == 0x00)
        {
            // Set X Value
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_32_PORT_PAGE78_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Set Y Value
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_33_PORT_PAGE78_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // audio hw mode
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, ~_BIT6, _BIT6);

            // manual gain enable
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, ~_BIT3, _BIT3);

            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_9F_PORT_PAGE78_PRESET_AFSM_MOD, ~_BIT5, _BIT5);
        }
#endif
        // Disable FIFO Boundary Tracking, Disable Trend Tracking
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_15_PORT_PAGE78_HDMI_PSCR);
        ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT3 | _BIT2), 0x00);

        // Set Double Buffer bit
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
        ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
        // Disable P Code Spread
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0);
        ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT7, 0x00);
#endif

        // Reload NF code
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
        ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, _BIT5);
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
        ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, 0x00);

        // Set FW tracking reset
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX4_SAMPLING_FREQ() <= _AUDIO_FREQ_48K)
        {
            SET_HDMI_AUDIO_RX4_FW_TRACKING_RESET();
        }
#endif

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        enumAudioFreq = ScalerGetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_8B_PORT_PAGE78_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // ======================================
        // SRC FS > FS Limint by user define
        // ======================================
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        if(enumAudioFreq > GET_HDMI_RX4_SAMPLING_FREQ_LIMIT())
        {
#if(_HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT == _ON)
            // Set Sampling Frequency to maximum value
            SET_HDMI_RX4_TARGET_SAMPLING_FREQ(GET_HDMI_RX4_SAMPLING_FREQ_LIMIT());
#else
            // Disable Audio output
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_30_PORT_PAGE78_HDMI_AVMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT6, 0x00);
#endif
        }
#endif
        // ======================================
        // SRC no audio packet
        // ======================================
        if(enumAudioFreq == _AUDIO_FREQ_NO_AUDIO)
        {
            // Set  User Define Frequency When No Audio value
            SET_HDMI_RX4_TARGET_SAMPLING_FREQ(GET_HDMI_RX4_SAMPLING_FREQ_USER_DEFINE());

            // Enable Audio output when no audio packet
#if((_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON) && (_HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT == _OFF))
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_30_PORT_PAGE78_HDMI_AVMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT6, _BIT6);
#endif
        }

        // ======================================
        // Set Audio Output clk when no audio packet or fs > fs Limint by user define
        // ======================================
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        // No Audio Detect Set User Define Frequency When No Audio or fs > fs limint by user define Set User Define Limit Frequency
        if((enumAudioFreq == _AUDIO_FREQ_NO_AUDIO) || (enumAudioFreq > GET_HDMI_RX4_SAMPLING_FREQ_LIMIT()))
#else
        // No Audio Detect Set User Define Frequency When No Audio
        if(enumAudioFreq == _AUDIO_FREQ_NO_AUDIO)
#endif
        {
            // Disable Auto Load S & NF Code
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT6 | _BIT5), 0x00);

            // Set S code User Define
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D5_PORT_PAGE78_HDMI_SCAPR);
            ScalerSetByte_EXINT(P78_CA_HDMI_DP, ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_HDMI, GET_HDMI_RX4_TARGET_SAMPLING_FREQ()));

            ScalerHdmiFrlMacRx4SetAudioNfCode_EXINT0();

            // Set Double Buffer bit
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

            // Reload NF code
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, _BIT5);
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, 0x00);

            // CLR PLL Autoload Status Flag
            CLR_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ_FOR_FRL();
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

        SET_HDMI_AUDIO_RX4_SAMPLING_FREQ_CHANGE();
    }
#endif

    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[7]);
    ScalerSetByte_EXINT(P73_C3_HDCP_AP, pucBackUp[6]);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, pucBackUp[4]);
    ScalerSetByte_EXINT(P78_D0_HDMI_PSAP2, pucBackUp[5]);

    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, pucBackUp[2]);

    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, pucBackUp[0]);
}

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
//--------------------------------------------------
// Description  : Check High Priority Irq Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ClearHighPriorityIrqFlag_EXINT0(void)
{
    // Clear High Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_60_PORT_PAGE78_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT3);
}

//--------------------------------------------------
// Description  : Check Low Priority Irq Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ClearLowPriorityIrqFlag_EXINT0(void)
{
    // Clear Low Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_60_PORT_PAGE78_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT7);
}
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : RSVx into IRQ Handler
// Input Value  : ulOui, enumRsvNumber
// Output Value : void
//--------------------------------------------------
void ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
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
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    ulOui = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);

    switch(ulOui)
    {
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        case _ADVANCED_HDR10_OUI:

            SET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED();

            ScalerHdmiFrlMacRx4GetAdvancedHdr10Vsif_EXINT0(enumRsvNumber, &stSyncAdvancedHDR10Metadata);

            ScalerColorAdvancedHDR10VSIFHandler_EXINT0(&stSyncAdvancedHDR10Metadata);

            break;
#endif

#if((_HDMI21_ALLM_SUPPORT == _ON) || (_HDMI21_CCBPC_SUPPORT == _ON))
        case _HF_VSIF_OUI:

            SET_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED();

#if(_HDMI21_ALLM_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4AllmProc_EXINT0(enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4CcbpcProc_EXINT0(enumRsvNumber);
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

            ScalerGetDataPortByte_EXINT0(P78_CD_HDMI_PSAP, ucStartAddr, 3, pucDmHb, _AUTOINC);

            if((pucDmHb[1] == 0x01) && ((pucDmHb[2] & 0x1F) == 0x1B))
            {
                ScalerHdmiFrlMacRx4GetDmVsif_EXINT0(enumRsvNumber, pucDmMetaData);

                if(((pucDmMetaData[3] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) == _BIT1) && ((pucDmMetaData[3] & (_BIT0)) == _BIT0)) // VS10=1, LL=1
                {
                    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);

                    SET_HDMI_FRL_MAC_RX4_DM_VSIF_RECEIVED();
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
void ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucI = 0;
    BYTE ucVnCount = 0;
    BYTE pucHdmiVenderName[4] = {0};

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    for(ucVnCount = 0; ucVnCount < 4; ucVnCount++)
    {
        pucHdmiVenderName[ucVnCount] = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
    }

    if(((pucHdmiVenderName[0] == 'M') && (pucHdmiVenderName[1] == 'S') && (pucHdmiVenderName[2] == 'F') && (pucHdmiVenderName[3] == 'T')) ||
       ((pucHdmiVenderName[0] == 'S') && (pucHdmiVenderName[1] == 'C') && (pucHdmiVenderName[2] == 'E') && (pucHdmiVenderName[3] == 'I')) ||
       ((pucHdmiVenderName[0] == 'N') && (pucHdmiVenderName[1] == 'V') && (pucHdmiVenderName[2] == 'I') && (pucHdmiVenderName[3] == 'D')))
    {
        g_stTmdsMacRx4SpdInfo.b1StructValuable = 0x01;
        __real_memcpy(&g_stTmdsMacRx4SpdInfo.pucHdmiVendorName[0], pucHdmiVenderName, 4);

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x5A);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x79);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x98);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0xB7);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 16; ucI++)
        {
            g_stTmdsMacRx4SpdInfo.pucHdmiProductDescription[ucI] = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
        }
    }
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    else if((pucHdmiVenderName[0] == 0x1A) && (pucHdmiVenderName[1] == 0x00) && (pucHdmiVenderName[2] == 0x00) && (GET_TMDS_MAC_RX4_FS_VALUABLE() == _FALSE))
    {
        SET_TMDS_MAC_RX4_FS_VALUABLE();

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x51);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x70);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0x8F);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, 0xAE);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 28; ucI++)
        {
            g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[ucI] = ScalerGetByte_EXINT(P78_CE_HDMI_PSDP);
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
bit ScalerHdmiFrlMacRx4GetEmpSramData_EXINT0(BYTE ucReadAddress, BYTE *pucEmpData)
{
    // Set read pointer & popup data
    ScalerSetByte_EXINT(P1E_C0_HDMI_EMPAP0, ucReadAddress);
    ScalerSetBit_EXINT(P1E_C0_HDMI_EMPAP0, ~_BIT7, _BIT7);

    if(ScalerGetBit_EXINT(P1E_C9_HDMI_EMP_SRAM_CTRL1, _BIT3) == 0x00)
    {
        memcpy(pucEmpData, (volatile BYTE xdata *)P1E_C1_HDMI_EMPDP0, 7);
        return _TRUE;
    }
    else
    {
        // [3] Read & Write happened at same time
        ScalerSetBit_EXINT(P1E_C9_HDMI_EMP_SRAM_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerHdmiFrlMacRx4OffMeasureClk_EXINT0(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;
    BYTE pucResult[2] = {0};

    // Set div36
    ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, ~_BIT6, _BIT6);

    // Select reference clk to Xtal Clk and measure clk
    ScalerTmdsPhyRxCdrMeasureClkSelect_EXINT0(ScalerTmdsMacRxRxDxMapping(_RX4), ucMeasureClk);

    // Start Measure
    ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US_EXINT();

        if((ScalerGetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, 2, &pucResult[0], _AUTOINC);

    return ((WORD)(pucResult[0] & 0x07) << 8) | pucResult[1];
}


//--------------------------------------------------
// Description  : HDMI2.1 PS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PSHighPriorityIntHandler_EXINT0(void)
{
    BYTE pucBackUp[6];
    pucBackUp[0] = ScalerGetByte_EXINT(P78_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P78_C8_HDMI_APC) & 0x01);

    pucBackUp[2] = ScalerGetByte_EXINT(P73_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P73_38_HDMI_CTRL_38) & 0x01);

    pucBackUp[4] = ScalerGetByte_EXINT(P73_C3_HDCP_AP);
    pucBackUp[5] = (ScalerGetByte_EXINT(P73_C2_HDCP_PCR) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, 0x00);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

    // Detect HDMI HPD IRQ
    /*if(ScalerGetBit_EXINT(P73_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT1 | _BIT0), _BIT1);

        if(ScalerGetBit_EXINT(P73_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2F_HDMI_CTRL_2F, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));
            ScalerSetByte_EXINT(P78_12_HDMI21_FRL_CED_10, 0x05);

            // Clear CED Valid flag
            ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P78_17_HDMI21_FRL_CED_15, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable CED count and running disparity
            ScalerSetBit_EXINT(P78_09_HDMI21_FRL_CED_1, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // Clear CED_update
            ScalerSetBit_EXINT(P78_14_HDMI21_FRL_CED_12, ~_BIT6, _BIT6);

            // Disable RS FW count
            ScalerSetBit_EXINT(P69_19_HDMI21_FW_RS_5, ~_BIT7, 0x00);

            // Clear RS FW error
            ScalerSetBit_EXINT(P69_1A_HDMI21_FW_RS_6, ~_BIT2, _BIT2);

            // Disable RS count and RS Valid flag
            ScalerSetBit_EXINT(P69_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), 0x00);

            // Disable RS_update and IRQ and clear RS_update
            ScalerSetBit_EXINT(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT2 | _BIT1), _BIT1);

            // Clear All SCDC Port Register
            ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

#if((_HDMI_SUPPORT == _ON) && (_HDMI20_SUPPORT == _ON))
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
#endif

            // Disable High to Low IRQ and enable Low to High IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Enable Low to High IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2E_HDMI_CTRL_2E, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));

            // Disable CED Update Read Request Auto Mode
            // ScalerSetBit_EXINT(P73_24_HDMI_CTRL_24, ~_BIT0, 0x00);
        }
        else
        {
            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2D_HDMI_CTRL_2D, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));

            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // if(ScalerGetBit_EXINT(P73_3A_HDMI_CTRL_3A, _BIT6) == 0x00)
            // {
                // Enable FLT_Ready
                // ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, ~_BIT6, _BIT6);

                // Set Status update
                //ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(~_BIT0, _BIT0);
            // }

            // ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
            // ScalerSetByte_EXINT(P73_2C_HDMI_CTRL_2C, ScalerGetByte_EXINT(P73_3A_HDMI_CTRL_3A));

            // Disable Low to High IRQ and enable High to Low IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // Enable High to Low IRQ
            ScalerSetBit_EXINT(P73_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }*/

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    // Clear IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_60_PORT_PAGE78_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT3);
#endif

    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[5]);
    ScalerSetByte_EXINT(P73_C3_HDCP_AP, pucBackUp[4]);
    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, pucBackUp[2]);
    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, pucBackUp[0]);
}

//--------------------------------------------------
// Description  : HDMI2.1 PS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PSLowPriorityIntHandler_EXINT0(void)
{
    BYTE pucBackUp[2];

    pucBackUp[0] = ScalerGetByte_EXINT(P78_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P78_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    // Clear Low Priority IRQ Pending Flag
    ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_60_PORT_PAGE78_HDMI_INTCR, ~(_BIT7 | _BIT3), _BIT7);
#endif

    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, pucBackUp[0]);
}

//--------------------------------------------------
// Description  : Set SCDC Update Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(DWORD ulAnd, BYTE ucOr)
{
    BYTE ucLoop = 0;

    // Set SCDC update flag addr
    ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, _P73_3A_PT_10_PORT_PAGE73_HDMI_SCDC_10);

    // Check I2C not busy before update SCDC
    while(ucLoop < 20)
    {
        ucLoop ++;

        // Clear I2C busy flag
        ScalerSetBit_EXINT(P73_20_HDMI_CTRL_20, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

        DELAY_XUS_EXINT(100);

        // Check I2C is busy or not
        if(ScalerGetBit_EXINT(P73_20_HDMI_CTRL_20, (_BIT6 | _BIT4)) == 0x00)
        {
            break;
        }
    }

    // Set SCDC update flag value
    ScalerSetBit_EXINT(P73_3A_HDMI_CTRL_3A, (BYTE)ulAnd, ucOr);
}

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get SBTM Received
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SbtmSetting_EXINT0(void)
{
    bit bTrueVsEmp = _FALSE;
    bit bSbtmSetTag = _FALSE;
    bit bMldsEmp = _FALSE;
    BYTE ucI = 0x00;
    BYTE ucMaxSize = ((ScalerGetBit_EXINT(P1E_C8_HDMI_EMP_SRAM_CTRL0, _BIT4) == _BIT4) ? _HDMI_EMP_SRAM_VS_SIZE : _HDMI_EMP_SRAM_TOTAL_SIZE); // 7 Byte as 1 unit
    BYTE pucEmpData[7] = {0};

    // W1C received flag
    ScalerSetBit_EXINT(P1E_51_EMP_VS, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // Read EMP SRAM Data
    for(ucI = 0; ucI < ucMaxSize; ucI++)
    {
        if(ScalerHdmiFrlMacRx4GetEmpSramData_EXINT0((0x28 + ucI), pucEmpData) == _TRUE)
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
                g_stTmdsMacRx4HdmiSbtmInfo.ucSbtmVer = (pucEmpData[0] & 0x0F);
                g_stTmdsMacRx4HdmiSbtmInfo.ucSbtmMode = (pucEmpData[1] & 0x03);
                g_stTmdsMacRx4HdmiSbtmInfo.ucSbtmType = ((pucEmpData[1] & 0x0C) >> 2);
                g_stTmdsMacRx4HdmiSbtmInfo.ucSbtmGrmdMin = ((pucEmpData[1] & 0x30) >> 4);
                g_stTmdsMacRx4HdmiSbtmInfo.ucSbtmGrmdLum = ((pucEmpData[1] & 0xC0) >> 6);
                g_stTmdsMacRx4HdmiSbtmInfo.usFrmPbLimitInt = (((WORD)(pucEmpData[2] & 0x3F) << 8) | pucEmpData[3]);
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
        g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive = _TRUE;
    }
}
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
//--------------------------------------------------
// Description  : Get DM Received
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4DMSetting_EXINT0(EnumInputPort enumMappingPort)
{
    EnumHdmiEmpType enumEmpType = _NONE_EMP;

    bit bTrueVsEmp = _FALSE;
    bit bMldsEmp = _FALSE;
    bit bDMSetTag = _FALSE;

    BYTE ucLegalDataSize = 0x00;
    BYTE ucI = 0x00;
    BYTE ucMaxSize = ((ScalerGetBit_EXINT(P1E_C8_HDMI_EMP_SRAM_CTRL0, _BIT4) == _BIT4) ? _HDMI_EMP_SRAM_VS_SIZE : _HDMI_EMP_SRAM_TOTAL_SIZE); // 7 Byte as 1 unit

    BYTE pucEmpData[7] = {0};
    BYTE pucMetaData[_DM_VS_EMP_MD_SIZE * 7] = {0}; // 56 byte

    // W1C received flag
    ScalerSetBit_EXINT(P1E_51_EMP_VS, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // Read EMP SRAM Data
    for(ucI = 0; ucI < ucMaxSize; ucI++)
    {
        if(ScalerHdmiFrlMacRx4GetEmpSramData_EXINT0((0x28 + ucI), pucEmpData) == _TRUE)
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
        SET_HDMI_FRL_MAC_RX4_DM_EMP_RECEIVED();
        ScalerDMMetadataSourceMapping_EXINT0(pucMetaData, _HDMI_DM_EMP_ENTRY, enumMappingPort);
    }
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get DMDRAM Received
// Input Value  : enumInputPort
// Output Value : _FALSE/ _TRUE
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4GetDMDramReceived_EXINT0(void)
{
    if(ScalerGetBit_EXINT(P78_D5_HDMI_RSV64_IE, _BIT2) == _BIT2)
    {
        // w1c RSV received bit
        ScalerSetBit_EXINT(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
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
void ScalerHdmiFrlMacRx4DMPacketReCheck_EXINT0(void)
{
    BYTE pucBackUp[8];

    pucBackUp[0] = ScalerGetByte_EXINT(P78_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P78_C8_HDMI_APC) & 0x01);

    pucBackUp[2] = ScalerGetByte_EXINT(P73_39_HDMI_CTRL_39);
    pucBackUp[3] = (ScalerGetByte_EXINT(P73_38_HDMI_CTRL_38) & 0x01);

    // Backup DFF #1 & #2
    pucBackUp[4] = ScalerGetByte_EXINT(P78_CD_HDMI_PSAP);
    pucBackUp[5] = ScalerGetByte_EXINT(P78_D0_HDMI_PSAP2);

    pucBackUp[6] = ScalerGetByte_EXINT(P73_C3_HDCP_AP);
    pucBackUp[7] = (ScalerGetByte_EXINT(P73_C2_HDCP_PCR) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, 0x00);

    // Set 3A Port non-auto increase
    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

    // "VS EMP" received into IRQ
    if(ScalerGetBit_EXINT(P1E_51_EMP_VS, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        if(ScalerGetByte_EXINT(P1E_BC_VS_ORG_ID) == _VENDOR_SPECIFIC)
        {
            EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping_EXINT0(_RX4);

            ScalerHdmiFrlMacRx4DMSetting_EXINT0(enumMappingPort);
        }
    }

    ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_60_PORT_PAGE78_HDMI_INTCR);
    if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT7) == _BIT7)
    {
#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
        ScalerHdmiFrlMacRx4ClearLowPriorityIrqFlag_EXINT0();
#endif

        // --- RSV0 Into IRQ ---
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
        if((ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P78_CC_HDMI_GPVS, _BIT5) == _BIT5))
        {
            ScalerSetByte_EXINT(P78_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P78_96_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_0);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_0);
#endif
            }
        }

        // --- RSV1 Into IRQ ---
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
        if((ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P78_CC_HDMI_GPVS, _BIT6) == _BIT6))
        {
            ScalerSetByte_EXINT(P78_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte_EXINT(P78_97_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_1);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_1);
#endif
            }
        }

        // --- RSV2 Into IRQ ---
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
        if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT2) == _BIT2)
        {
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR);
            if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT7) == _BIT7)
            {
                ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte_EXINT(P78_98_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_2);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_2);
#endif
                }
            }
        }

        // --- RSV3 Into IRQ ---
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6);
        if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT3) == _BIT3)
        {
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR);
            if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, _BIT6) == _BIT6)
            {
                ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte_EXINT(P78_99_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(_HDMI_RSV_3);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(_HDMI_RSV_3);
#endif
                }
            }
        }

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
        // Detect if Auido Sampling is Changed
        ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET);
        if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
        {
            // Clear Auido Sampling Change Flag
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_8A_PORT_PAGE78_AUDIO_FREQDET);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT1, _BIT1);

            // Disable FIFO Boundary Tracking, Disable Trend Tracking
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_15_PORT_PAGE78_HDMI_PSCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT3 | _BIT2), 0x00);

            // Set Double Buffer bit
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
            // Disable P Code Spread
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT7, 0x00);
#endif

            // Reload NF code
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, _BIT5);
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
            ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, 0x00);

            // Set FW tracking reset
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX4_SAMPLING_FREQ() <= _AUDIO_FREQ_48K)
            {
                SET_HDMI_AUDIO_RX4_FW_TRACKING_RESET();
            }
#endif

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            // No Audio Detect Set User Define Frequency When No Audio
            ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_8B_PORT_PAGE78_AUDIO_FREQ_RESULT);
            if(ScalerGetBit_EXINT(P78_CA_HDMI_DP, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
            {
                // Disable Auto Load S & NF Code
                ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
                ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT6 | _BIT5), 0x00);

                // Set S code User Define
                ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D5_PORT_PAGE78_HDMI_SCAPR);
                ScalerSetByte_EXINT(P78_CA_HDMI_DP, ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_HDMI, GET_HDMI_RX4_SAMPLING_FREQ_USER_DEFINE()));

                ScalerHdmiFrlMacRx4SetAudioNfCode_EXINT0();

                // Set Double Buffer bit
                ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
                ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~(_BIT7 | _BIT5), _BIT7);

                // Reload NF code
                ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
                ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, _BIT5);
                ScalerSetByte_EXINT(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
                ScalerSetBit_EXINT(P78_CA_HDMI_DP, ~_BIT5, 0x00);

                // CLR PLL Autoload Status Flag
                CLR_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ_FOR_FRL();
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

            SET_HDMI_AUDIO_RX4_SAMPLING_FREQ_CHANGE();
        }
#endif
    }

    ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[7]);
    ScalerSetByte_EXINT(P73_C3_HDCP_AP, pucBackUp[6]);

    ScalerSetByte_EXINT(P78_CD_HDMI_PSAP, pucBackUp[4]);
    ScalerSetByte_EXINT(P78_D0_HDMI_PSAP2, pucBackUp[5]);

    ScalerSetBit_EXINT(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1 | _BIT0), pucBackUp[3]);
    ScalerSetByte_EXINT(P73_39_HDMI_CTRL_39, pucBackUp[2]);

    ScalerSetBit_EXINT(P78_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P78_C9_HDMI_AP, pucBackUp[0]);
}
#endif
#endif // End for #if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

