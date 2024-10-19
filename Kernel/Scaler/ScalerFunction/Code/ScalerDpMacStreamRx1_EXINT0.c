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
// ID Code      : ScalerDpMacStreamRx1_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_STREAM_RX1_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMacStreamRx1/ScalerDpMacStreamRx1.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
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
// Description  : DP High Priority Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacHighPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_MAC_STREAM_RX1_MAC_GLOBAL_HIGH_PRIORITY_IRQ_FLAG() == _TRUE)
    {
        ScalerDpMacStreamRx1MacBsMissDetectIntHandler_EXINT0();

        ScalerDpMacStreamRx1MacHighPriorityIntHandler_8b10b_EXINT0();

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1MacHighPriorityIntHandler_128b132b_EXINT0();
#endif
    }
}

//--------------------------------------------------
// Description  : DP low Priority Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacLowPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_MAC_STREAM_RX1_MAC_GLOBAL_LOW_PRIORITY_IRQ_FLAG() == _TRUE)
    {
        ScalerDpMacStreamRx1MacLowPriorityIntHandler_8b10b_EXINT0();

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1MacLowPriorityIntHandler_128b132b_EXINT0();
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        ScalerDpAudioRx1LPCMFormatChangeProc_EXINT0();

        ScalerDpAudioRx1FifoTrackingProc_EXINT0();
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : DP BS Miss Detect Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacBsMissDetectIntHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);

    // BS Miss Detect IRQ & flag
    if(ScalerGetBit_EXINT(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());

#if(_AUDIO_SUPPORT == _ON)
        // Disable INT for Auido and Reset Function
        ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

        // Disable Audio FSM
        ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

        // Disable BS Detect IRQ
        ScalerSetBit_EXINT(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~(_BIT7 | _BIT6), 0x00);

        // Disable fifo overflwo/ underflwo IRQ
        ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, 0x00);

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
        // Disable DP MSA Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT7, 0x00);
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Disable fifo overflwo/ underflwo IRQ
        ScalerSetBit_EXINT(P75_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(P75_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
        // Disable DSC VB-ID[6] Change IRQ
        ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Disable DSC VB-ID[6] Change IRQ
        ScalerSetBit_EXINT(P75_3A_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
#endif
#endif

        // Set DP Receive Port0 Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

        // Set DP Stream Regen Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

#if(_DP_TX_SUPPORT == _ON)
        if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (GET_DP_MAC_TX_INPUT_PORT() == enumInputPort))
        {
            // Set DPTx Force Output Idle Pattern
            ScalerDpMacTxForceIdlePattern_EXINT0();
        }
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        SET_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK();
#endif
    }
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetNoVideoStreamIRQ_EXINT0(bit bEn)
{
    // VB-ID[3] Change Flag
    ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    // VB-ID[3] Change IRQ
    ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
}

//--------------------------------------------------
// Description  : Get DP Fifo Watch Dog Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetFifoWDStatus_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return (ScalerGetBit_EXINT(P75_38_DP_WD_CTRL_0, _BIT5) == _BIT5) ? _TRUE : _FALSE;
    }
    else
#endif
    {
        return (ScalerGetBit_EXINT(PB9_3C_DP_WD_CTRL_0, _BIT5) == _BIT5) ? _TRUE : _FALSE;
    }
}

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    enumInputPort = enumInputPort;

    if(bEnable == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b_EXINT0(_ENABLE);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b_EXINT0(_ENABLE);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b_EXINT0(_DISABLE);
#endif
        ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b_EXINT0(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamWD_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    enumInputPort = enumInputPort;

    if(bEnable == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1DscSetStreamWD_128b132b_EXINT0(_ENABLE);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1DscSetStreamWD_8b10b_EXINT0(_ENABLE);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1DscSetStreamWD_128b132b_EXINT0(_DISABLE);
#endif
        ScalerDpMacStreamRx1DscSetStreamWD_8b10b_EXINT0(_DISABLE);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacHighPriorityIntHandler_8b10b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);

    if(ScalerGetBit_EXINT(PFF_ED_MCU_CONTROL, _BIT1) == 0x00)
    {
        ScalerSetBit_EXINT(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _FLASH_CLK_PS_FAST_DIV);
    }

    // Fifo overflow/ underflow IRQ & flag
    if((ScalerGetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PB8_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00))
    {
        // Disable fifo overflwo/ underflwo IRQ
        ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());

        // Disable HS/VS Tracking
        ScalerSetBit_EXINT(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
        // Disable INT for Auido and Reset Function
        ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

        // Disable Audio FSM
        ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
        // Disable DP MSA Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT7, 0x00);
#endif

        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, 0x00);

        // Set DP Receive Port0 Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

        // Set DP Stream Regen Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

        // The Judge Handler take much time, It lead to MacBook 720P @50 <---> @60 Timing changing Issue
        if((ScalerDpMacDphyRxGetMstProtocolEnable_EXINT0(enumInputPort) == _DISABLE) &&
           (ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
           (ScalerDpPhyRxDFECheck_EXINT0(enumInputPort) == _FALSE))
        {
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x02, 0x00);
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x03, 0x00);
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x04, 0x80);
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x05, 0x00);
        }

#if(_DP_TX_SUPPORT == _ON)
        if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (GET_DP_MAC_TX_INPUT_PORT() == enumInputPort))
        {
            // Set DPTx Force Output Idle Pattern
            ScalerDpMacTxForceIdlePattern_EXINT0();
        }
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        SET_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK();
#endif
    }

    // LLCTS 7.2.1.3 Sink Status
    if((ScalerGetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(PB9_3B_DP_GLB_STATUS, _BIT6) == _BIT6))
    {
        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, 0x00);

        // Clear VB-ID[3] Change Flag
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
        // Disable DP MSA Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT7, 0x00);
#endif

        // For LLCTS 5.4.1.4
        if(ScalerGetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == 0x00)
        {
            // Disable HS/VS Tracking
            ScalerSetBit_EXINT(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

            SET_DP_MAC_STREAM_RX1_VBID3_CHANGED();

            // Set DP Receive Port1 Out of Sync
            ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
        }
        else
        {
            if(ScalerGetBit_EXINT(PB9_01_DP_VBID, _BIT3) == _BIT3)
            {
                // Set DP Receive Port1 Out of Sync
                ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
            }
        }
    }

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    if((ScalerGetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(PB9_3B_DP_GLB_STATUS, _BIT1) == _BIT1))
    {
        // Disable DSC VB-ID[6] IRQ Setting
        ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, 0x00);

        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());

#if(_AUDIO_SUPPORT == _ON)
        // Disable INT for Auido and Reset Function
        ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

        // Disable Audio FSM
        ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

        // Set DP Receive Port1 Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

        // Set DP Stream Regen Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

        // Enable DSC Change Flag When DSC Detect VB-ID[6] Change
        ScalerDpMacDscRxDscStreamSetChange_EXINT0(_DP_MAC_1, _ENABLE);

#if(_DP_TX_SUPPORT == _ON)
        if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (GET_DP_MAC_TX_INPUT_PORT() == enumInputPort))
        {
            // Set DPTx Force Output Idle Pattern
            ScalerDpMacTxForceIdlePattern_EXINT0();
        }
#endif
    }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    if((ScalerGetBit_EXINT(PB9_4A_DUMMY_4A, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(PB9_4B_DUMMY_4B, _BIT5) == _BIT5))
    {
        // Disable Pr Sdp Crc Receive IRQ
        ScalerSetBit_EXINT(PB9_4A_DUMMY_4A, ~_BIT5, 0x00);

        // Pr Crc check
        ScalerDpMacStreamRx1PRModeCrcCheck_8b10b_EXINT0(enumInputPort);

        // Clr Pr Sdp Crc Receive Flag
        ScalerSetBit_EXINT(PB9_4B_DUMMY_4B, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Enable Pr Sdp Crc Receive IRQ
        ScalerSetBit_EXINT(PB9_4A_DUMMY_4A, ~_BIT5, _BIT5);
    }

    if((ScalerGetBit_EXINT(PB9_4A_DUMMY_4A, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(PB9_4B_DUMMY_4B, _BIT7) == _BIT7))
    {
        BYTE ucPrSinkStatusTemp = ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x20, 0x22, (_BIT2 | _BIT1 | _BIT0));

        // Check Sourc Pr Function Enable
        if((ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0xB0) & _BIT0) == _BIT0)
        {
            // Check Pr Sink Status
            if((ucPrSinkStatusTemp == _DP_PR_MODE_INACTIVE) || (ucPrSinkStatusTemp == _DP_PR_MODE_INTERNAL_ERROR))
            {
                // Check Vsc Sdp Pr_State = 1
                if(ScalerGetDataPortBit_EXINT0(PB9_47_VSC7, 0x01, _BIT0) == _BIT0)
                {
                    // Check Vsc Sdp Su_valid = 1
                    if(ScalerGetDataPortBit_EXINT0(PB9_47_VSC7, 0x01, _BIT3) == _BIT3)
                    {
                        // Vsc Sdp DB1[0] Pr_state = 1, DB1[3] Su_valid = 1, Set Pr Sink Status Active from Inactive or Internal Error
                        ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_ACTIVE);
                    }
                    else
                    {
                        if(ucPrSinkStatusTemp != _DP_PR_MODE_INTERNAL_ERROR)
                        {
                            // Vsc Sdp DB1[0] Pr_state = 1, DB1[3] Su_valid = 0, Set Pr Sink Status Internal Error
                            ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_INTERNAL_ERROR);
                        }
                    }
                }
                else
                {
                    // Vsc Sdp DB1[0] Pr_state = 0, Set Pr Sink Status Inactive
                    ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_INACTIVE);
                }
            }
            else
            {
                // Check Vsc Sdp Pr_State != 1
                if(ScalerGetDataPortBit_EXINT0(PB9_47_VSC7, 0x01, _BIT0) != _BIT0)
                {
                    // Vsc Sdp DB1[0] Pr_state = 0, Set Pr Sink Status Inactive
                    ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_INACTIVE);
                }
            }
        }

        // Clr Pr Sdp Pr_state Receive Flag
        ScalerSetBit_EXINT(PB9_4B_DUMMY_4B, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Enable bit should be off-on
        ScalerSetBit_EXINT(PB9_4A_DUMMY_4A, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB9_4A_DUMMY_4A, ~_BIT7, _BIT7);
    }
#endif

#if((_DP_MAC_RX1_DM_SUPPORT == _ON) || (_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON))
    if(ScalerGetBit_EXINT(PB9_F3_DP_SDP_RSV0_CTRL, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        BYTE pucInfoframeVendorSpecInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
        DWORD ulAdvanceHdr10Oui = 0;
#endif

        // Get Vendor Sdp Data
        ScalerDpMacStreamRx1GetSdpPktData_EXINT0(_DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC, pucInfoframeVendorSpecInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        // Check DM Oui
        if(((pucInfoframeVendorSpecInfoData[2] == _DM_OUI_0) && (pucInfoframeVendorSpecInfoData[3] == _DM_OUI_1) && (pucInfoframeVendorSpecInfoData[4] == _DM_OUI_2)) && // OUI code
           ((pucInfoframeVendorSpecInfoData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
           (pucInfoframeVendorSpecInfoData[0] == 0x01) && // Version
           ((pucInfoframeVendorSpecInfoData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
        {
            SET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE(_SDP_STATE_RECEIVED);

            ScalerDMMetadataSourceMapping_EXINT0(pucInfoframeVendorSpecInfoData, _DP_DM_SDP_ENTRY, enumInputPort);
        }
        else
#endif
#endif
        {
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
            ulAdvanceHdr10Oui = pucInfoframeVendorSpecInfoData[3];
            ulAdvanceHdr10Oui = (ulAdvanceHdr10Oui << 8) + pucInfoframeVendorSpecInfoData[4];
            ulAdvanceHdr10Oui = (ulAdvanceHdr10Oui << 8) + pucInfoframeVendorSpecInfoData[5];

            // Check Advanced Hdr10 Oui
            if((ulAdvanceHdr10Oui == _ADVANCED_HDR10_OUI) && (GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON))
            {
                StructAdvancedHDR10MetaData stSyncAdvancedHDR10Metadata = {0};

                ScalerDpMacStreamRxAdvancedHdr10VsifDataStrcutMapping_EXINT0(pucInfoframeVendorSpecInfoData, &stSyncAdvancedHDR10Metadata);

                SET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE(_SDP_STATE_RECEIVED);

                ScalerColorAdvancedHDR10VSIFHandler_EXINT0(&stSyncAdvancedHDR10Metadata);
            }
#endif
        }

        // Clr Irq Flag and Enable bit should be off-on
        ScalerSetBit_EXINT(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT6);
        ScalerSetBit_EXINT(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT5);
    }
#endif

#if((((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)) || (_DP_MAC_RX1_DM_SUPPORT == _ON)) && (_DP_SDP_META_SRAM_SUPPORT == _ON))
    // Meta VSIF Data Rcv Int
    if(ScalerGetBit_EXINT(P26_DA_META_SDP0_CTRL2, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
        ScalerDpMacStreamRx1Set1stBeIrqEnable_8b10b(_ENABLE);
#endif
        // No timeout
        if(ScalerGetBit_EXINT(P26_DA_META_SDP0_CTRL2, _BIT2) == 0x00)
        {
            BYTE pucMetaVsifData[_DP_SDP_META_0_PAYLOAD_LENGTH] = {0};

            StructDpSdpMetaInfo structDpSdpMetaInfo;
            structDpSdpMetaInfo.enumIndex = _DP_SDP_META_0;
            structDpSdpMetaInfo.ucPacketDBLength = _DP_SDP_META_0_PAYLOAD_LENGTH;

            // Please Check: input ucLength < _DP_SDP_META_x_PAYLOAD_LENGTH
            if(ScalerDpMacStreamRx1GetMetaPktData_EXINT0(structDpSdpMetaInfo, pucMetaVsifData, 0, _DP_SDP_META_0_PAYLOAD_LENGTH) == _TRUE)
            {
#if((_DP_MAC_RX1_DM_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
                if(((pucMetaVsifData[2] == _DM_OUI_0) && (pucMetaVsifData[3] == _DM_OUI_1) && (pucMetaVsifData[4] == _DM_OUI_2)) && // OUI code
                   ((pucMetaVsifData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
                   (pucMetaVsifData[0] == 0x01) && // Version
                   ((pucMetaVsifData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
                {
                    ScalerDMMetadataSourceMapping_EXINT0(pucMetaVsifData, _DP_DM_EXT_SDP_ENTRY, enumInputPort);
                }
#endif
            }
        }

        ScalerSetBit_EXINT(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
    }

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
    // BE_1st Int
    if(ScalerGetBit_EXINT(P26_E0_META_SRAM_CTRL, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        ScalerDpMacStreamRx1Set1stBeIrqEnable_8b10b(_DISABLE);

        // Reset Meta Sram
        ScalerSetBit_EXINT(P26_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT6);

        // Clr Rcv / TimeOut / Rcv_done flag
        ScalerSetBit_EXINT(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P26_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P26_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P26_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P26_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacLowPriorityIntHandler_8b10b_EXINT0(void)
{
#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);

    // DP MSA Change IRQ & Flag
    if((ScalerGetBit_EXINT(PB9_3B_DP_GLB_STATUS, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, _BIT7) == _BIT7))
    {
        // Disable DP MSA Change IRQ
        ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT7, 0x00);

        // Clear DP MSA Change flag
        ScalerSetByte_EXINT(PB9_3B_DP_GLB_STATUS, _BIT4);

        // Pop up Main Stream Attributes
        ScalerSetBit_EXINT(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

        // Color Space Check
        if((ScalerGetByte_EXINT(PB9_02_MN_STRM_ATTR_MISC) & (_BIT2 | _BIT1)) != ((ScalerGetByte_EXINT(PB8_20_PG_CTRL_0) & (_BIT4 | _BIT3)) >> 2))
        {
            // Set D Domain Region Free run/ Force to Background
            ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());

            SET_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL();

            // Disable fifo overflwo/ underflwo IRQ
            ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
            // Disable INT for Auido and Reset Function
            ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

            // Disable Audio FSM
            ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Set DP Receive Port0 Out of Sync
            ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

            // Set DP Stream Regen Out of Sync
            ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

#if(_DP_TX_SUPPORT == _ON)
            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (GET_DP_MAC_TX_INPUT_PORT() == enumInputPort))
            {
                // Set DPTx Force Output Idle Pattern
                ScalerDpMacTxForceIdlePattern_EXINT0();
            }
#endif
        }
    }
#endif
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP PR Mode CRC
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCrcCheck_8b10b_EXINT0(EnumInputPort enumInputPort)
{
    BYTE pucSourceCrc[6] = {0};

    // Get DP SDP RSV0 PR Mode Pr_state DB1[0]
    if(ScalerGetDataPortBit_EXINT0(PB9_47_VSC7, 0x01, _BIT0) == _BIT0)
    {
        if((ScalerGetBit_EXINT(PB9_4B_DUMMY_4B, _BIT5) == _BIT5) && (ScalerDpAuxRxGetPRModeDpcdCrcEnable_EXINT0(enumInputPort) == _TRUE))
        {
            ScalerGetDataPortByte_EXINT0(PB9_47_VSC7, 0x02, 6, &pucSourceCrc[0], _AUTOINC);

            if((ScalerGetByte_EXINT(PB8_72_DP_CRC_R_L) != pucSourceCrc[0]) || (ScalerGetByte_EXINT(PB8_71_DP_CRC_R_M) != pucSourceCrc[1]) || (ScalerGetByte_EXINT(PB8_74_DP_CRC_G_L) != pucSourceCrc[2]) ||
               (ScalerGetByte_EXINT(PB8_73_DP_CRC_G_M) != pucSourceCrc[3]) || (ScalerGetByte_EXINT(PB8_76_DP_CRC_B_L) != pucSourceCrc[4]) || (ScalerGetByte_EXINT(PB8_75_DP_CRC_B_M) != pucSourceCrc[5]))
            {
                // Set PR Error Status CRC Mismatch
                ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(enumInputPort, _DP_PR_MODE_CRC_ERROR);
            }
        }

        if((ScalerGetBit_EXINT(PB9_4B_DUMMY_4B, _BIT5) == _BIT5) && (ScalerDpAuxRxGetPRModeDpcdCrcEnable_EXINT0(enumInputPort) == _FALSE))
        {
            // Set PR Error Status Sdp Uncorrectable
            ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(enumInputPort, _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR);
        }
    }
}

//--------------------------------------------------
// Description  : Enable/Disable DP PR Mode CRC Calculation
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCrcCalculateEnable_8b10b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Start CRC Calculation For Panel Replay CRC Check
        ScalerSetBit_EXINT(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    }
    else
    {
        // Stop CRC Calculation For Panel Replay CRC Check
        ScalerSetBit_EXINT(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Get Sdp Packet Data
// Input Value  : Dp Sdp Ram Index & Sdp Buff
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1GetSdpPktData_EXINT0(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength)
{
    BYTE ucIndex = 0;

    BYTE pucTmepData1[_HW_DP_SDP_PAYLOAD_LENGTH];

    WORD usInfoFrameAddrByte = 0x00;
    WORD usInfoFrameDataByte = 0x00;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);
#endif

    switch(ScalerDpMacStreamRxGetSdpBufferType_EXINT0(enumDpSdpType))
    {
        case _DP_SDP_BUFF_SPD:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_2E_DP_SDP_SPD_ADR;
                usInfoFrameDataByte = P75_2F_DP_SDP_SPD_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_32_DP_SDP_SPD_ADR;
                usInfoFrameDataByte = PB9_33_DP_SDP_SPD_DAT;
            }

            break;

        case _DP_SDP_BUFF_HDR:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_35_DP_SDP_HDR_INFO_ADR;
                usInfoFrameDataByte = P75_36_DP_SDP_HDR_INFO_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_39_DP_SDP_HDR_INFO_ADR;
                usInfoFrameDataByte = PB9_3A_DP_SDP_HDR_INFO_DAT;
            }

            break;

        case _DP_SDP_BUFF_ISRC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_E4_SDP_ISRC_ADR;
                usInfoFrameDataByte = P75_E5_SDP_ISRC_DATA;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_E4_SDP_ISRC_ADR;
                usInfoFrameDataByte = PB9_E5_SDP_ISRC_DATA;
            }

            break;

        case _DP_SDP_BUFF_VSC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_47_VSC7;
                usInfoFrameDataByte = P75_48_VSC8;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_47_VSC7;
                usInfoFrameDataByte = PB9_48_VSC8;
            }

            break;

        case _DP_SDP_BUFF_RSV0:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_F4_DP_SDP_RSV0_ADR;
                usInfoFrameDataByte = P75_F5_DP_SDP_RSV0_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_F4_DP_SDP_RSV0_ADR;
                usInfoFrameDataByte = PB9_F5_DP_SDP_RSV0_DAT;
            }

            break;

        default:
            break;
    }

    if((usInfoFrameAddrByte != 0x00) && (usInfoFrameDataByte != 0x00))
    {
        ucLength = ((ucLength + ucOffset) > _HW_DP_SDP_PAYLOAD_LENGTH) ? (_HW_DP_SDP_PAYLOAD_LENGTH - ucOffset) : ucLength;

        while(ucIndex < ucLength)
        {
            ScalerSetByte_EXINT(usInfoFrameAddrByte, (ucOffset + ucIndex));
            pucTmepData1[ucIndex] = ScalerGetByte_EXINT(usInfoFrameDataByte);

            ucIndex ++;
        }

        __real_memcpy(pucSdpData, pucTmepData1, ucLength);
    }
}

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
//----------------------------------------------------------------
// Description  : Get Sdp Data From Meta Sram
// Input Value  : structDpMetaInfo, ucOffset, ucLength
// Output Value : *pucMetaData
// Please Check : input ucLength < _DP_SDP_META_x_PAYLOAD_LENGTH
//----------------------------------------------------------------
bit ScalerDpMacStreamRx1GetMetaPktData_EXINT0(StructDpSdpMetaInfo structDpSdpMetaInfo, BYTE *pucMetaData, BYTE ucOffset, BYTE ucLength)
{
    WORD usStartAddrReg = 0x00;
    BYTE ucStartAddr = 0x00;
    BYTE ucRcvMode = 0x00;
    BYTE pucTempData[_HW_DP_SDP_META_SRAM_DB_LENGTH] = {0};
    BYTE ucTag = 0x00;
    BYTE ucNumTempLines = 0x00;
    BYTE ucNumTargetLines = 0x00;
    BYTE ucNumPacketLines = 0x00;
    BYTE ucHB2 = 0x00;
    bit bNextHB2Flag = _TRUE;
    BYTE ucIndex0 = 0x00;
    BYTE ucIndex1 = 0x00;
    BYTE ucMetaSramReadAddrBackUp = 0x00;
    BYTE ucMetaSramPortAddrBackUp = 0x00;
    WORD usMaxAccessLength = 0x00;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);
#endif

    ucNumPacketLines = structDpSdpMetaInfo.ucPacketDBLength / _HW_DP_SDP_META_SRAM_DB_WIDTH;

    switch(structDpSdpMetaInfo.enumIndex)
    {
        case _DP_SDP_META_0:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usStartAddrReg = P7E_D5_META_SDP0_CTRL1;
            }
            else
#endif
            {
                usStartAddrReg = P26_D5_META_SDP0_CTRL1;
            }

            usMaxAccessLength = _DP_SDP_META_0_PAYLOAD_LENGTH;
            break;

        case _DP_SDP_META_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usStartAddrReg = P7E_D6_META_SDP1_CTRL1;
            }
            else
#endif
            {
                usStartAddrReg = P26_D6_META_SDP1_CTRL1;
            }

            usMaxAccessLength = _DP_SDP_META_1_PAYLOAD_LENGTH;
            break;

        case _DP_SDP_META_2:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usStartAddrReg = P7E_D7_META_SDP2_CTRL1;
            }
            else
#endif
            {
                usStartAddrReg = P26_D7_META_SDP2_CTRL1;
            }

            usMaxAccessLength = _DP_SDP_META_2_PAYLOAD_LENGTH;
            break;

        case _DP_SDP_META_3:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usStartAddrReg = P7E_D8_META_SDP3_CTRL1;
            }
            else
#endif
            {
                usStartAddrReg = P26_D8_META_SDP3_CTRL1;
            }

            usMaxAccessLength = _DP_SDP_META_3_PAYLOAD_LENGTH;
            break;

        case _DP_SDP_META_4:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usStartAddrReg = P7E_D9_META_SDP4_CTRL1;
            }
            else
#endif
            {
                usStartAddrReg = P26_D9_META_SDP4_CTRL1;
            }

            usMaxAccessLength = _DP_SDP_META_4_PAYLOAD_LENGTH;
            break;

        default:
            break;
    }

    ucStartAddr = ScalerGetBit_EXINT(usStartAddrReg, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ucRcvMode = ScalerGetBit_EXINT(usStartAddrReg, _BIT5) >> 5;

    if((ucLength + ucOffset) > usMaxAccessLength)
    {
        return _FALSE;
    }

    ucNumTargetLines = (ucOffset + ucLength) / _HW_DP_SDP_META_SRAM_DB_WIDTH + ((((ucOffset + ucLength) % _HW_DP_SDP_META_SRAM_DB_WIDTH) == 0) ? 0 : 1);

    // Back Up Current Addr Info
    ucMetaSramReadAddrBackUp = ScalerGetByte_EXINT(P26_E3_META_SRAM_RADDR);
    ucMetaSramPortAddrBackUp = ScalerGetByte_EXINT(P26_E1_META_SRAM_PORT_ADDR);

    // Write startAddr
    ScalerSetByte_EXINT(P26_E3_META_SRAM_RADDR, ucStartAddr);
    ScalerSetByte_EXINT(P26_E4_META_SRAM_RDATA, 0x01);

    // Get target SDP tag
    ScalerSetByte_EXINT(P26_E1_META_SRAM_PORT_ADDR, 0x00);
    ucTag = ScalerGetByte_EXINT(P26_E2_META_SRAM_PORT_DATA);

    // Loop to scan sram from startAddr to end
    for(ucIndex0 = 0; ucIndex0 < (_HW_DP_SDP_META_SRAM_DB_DEPTH - ucStartAddr); ucIndex0++)
    {
        ScalerSetByte_EXINT(P26_E1_META_SRAM_PORT_ADDR, 0x00);

        if(ScalerGetByte_EXINT(P26_E2_META_SRAM_PORT_DATA) == ucTag)
        {
            ucNumTempLines++;

            // Next HB: HB2 --> save; Next HB: HB3 --> discard
            if(bNextHB2Flag == _TRUE)
            {
                ucHB2 = ScalerGetByte_EXINT(P26_E2_META_SRAM_PORT_DATA);
                bNextHB2Flag = _FALSE;
            }
            else
            {
                ScalerGetByte_EXINT(P26_E2_META_SRAM_PORT_DATA);
            }

            // Read and save 16byte data
            for(ucIndex1 = 0; ucIndex1 < _HW_DP_SDP_META_SRAM_DB_WIDTH; ucIndex1++)
            {
                pucTempData[(_HW_DP_SDP_META_SRAM_DB_WIDTH * ucNumTempLines - 1) - ucIndex1] = ScalerGetByte_EXINT(P26_E2_META_SRAM_PORT_DATA);
            }

            // When get a complete packet, Judge break loop or not
            if((ucNumTempLines % ucNumPacketLines) == 0x00)
            {
                if(ucRcvMode == _DP_SDP_META_RCV_NO_CHAIN)
                {
                    break;
                }
                else
                {
                    if((ucHB2 & _BIT7) != _BIT7)
                    {
                        break;
                    }
                    else
                    {
                        bNextHB2Flag = _TRUE;
                    }
                }
            }

            // When get all lines wanted, break
            if((ucNumTempLines >= ucNumTargetLines))
            {
                break;
            }
        }

        // Write to Increase Address
        ScalerSetByte_EXINT(P26_E4_META_SRAM_RDATA, 0x01);
    }

    __real_memcpy(pucMetaData, &pucTempData[ucOffset], ucLength);

    // Restore Addr Info
    ScalerSetByte_EXINT(P26_E3_META_SRAM_RADDR, ucMetaSramReadAddrBackUp - 1);
    ScalerSetByte_EXINT(P26_E4_META_SRAM_RDATA, 0x01);
    ScalerSetByte_EXINT(P26_E1_META_SRAM_PORT_ADDR, ucMetaSramPortAddrBackUp);

    return _TRUE;
}
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamWD_8b10b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit_EXINT(PB9_3C_DP_WD_CTRL_0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit_EXINT(PB9_3C_DP_WD_CTRL_0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit_EXINT(PB9_3E_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DM Re check DM Packet Irq Receive
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DMPacketReCheck_8b10b_EXINT0(EnumInputPort enumInputPort)
{
    if(ScalerGetBit_EXINT(PB9_F3_DP_SDP_RSV0_CTRL, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        BYTE pucInfoframeVendorSpecInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};

        // Get Vendor Sdp Data
        ScalerDpMacStreamRx1GetSdpPktData_EXINT0(_DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC, pucInfoframeVendorSpecInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

        // Check DM Oui
        if(((pucInfoframeVendorSpecInfoData[2] == _DM_OUI_0) && (pucInfoframeVendorSpecInfoData[3] == _DM_OUI_1) && (pucInfoframeVendorSpecInfoData[4] == _DM_OUI_2)) && // OUI code
           ((pucInfoframeVendorSpecInfoData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
           (pucInfoframeVendorSpecInfoData[0] == 0x01) && // Version
           ((pucInfoframeVendorSpecInfoData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
        {
            SET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE(_SDP_STATE_RECEIVED);

            ScalerDMMetadataSourceMapping_EXINT0(pucInfoframeVendorSpecInfoData, _DP_DM_SDP_ENTRY, enumInputPort);

            // If receive Dolby Meta Data Clr Irq Flag and Enable bit should be off-on
            ScalerSetBit_EXINT(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT6);
            ScalerSetBit_EXINT(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT5);
        }
    }

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
    // Meta VSIF Data Rcv Int
    if(ScalerGetBit_EXINT(P26_DA_META_SDP0_CTRL2, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // No timeout
        if(ScalerGetBit_EXINT(P26_DA_META_SDP0_CTRL2, _BIT2) == 0x00)
        {
            BYTE pucMetaVsifData[_DP_SDP_META_0_PAYLOAD_LENGTH] = {0};

            StructDpSdpMetaInfo structDpSdpMetaInfo;
            structDpSdpMetaInfo.enumIndex = _DP_SDP_META_0;
            structDpSdpMetaInfo.ucPacketDBLength = _DP_SDP_META_0_PAYLOAD_LENGTH;

            // Please Check: input ucLength < _DP_SDP_META_x_PAYLOAD_LENGTH
            if(ScalerDpMacStreamRx1GetMetaPktData_EXINT0(structDpSdpMetaInfo, pucMetaVsifData, 0, _DP_SDP_META_0_PAYLOAD_LENGTH) == _TRUE)
            {
                if(((pucMetaVsifData[2] == _DM_OUI_0) && (pucMetaVsifData[3] == _DM_OUI_1) && (pucMetaVsifData[4] == _DM_OUI_2)) && // OUI code
                   ((pucMetaVsifData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
                   (pucMetaVsifData[0] == 0x01) && // Version
                   ((pucMetaVsifData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
                {
                    ScalerDMMetadataSourceMapping_EXINT0(pucMetaVsifData, _DP_DM_EXT_SDP_ENTRY, enumInputPort);

                    // If receive Dolby Meta Data Clr Irq Flag and Enable bit should be off-on
                    ScalerSetBit_EXINT(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
                    // Reset Meta Sram
                    ScalerSetBit_EXINT(P26_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT6);

                    // Clr Rcv / TimeOut / Rcv_done flag
                    ScalerSetBit_EXINT(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P26_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P26_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P26_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P26_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
#endif
                }
            }
        }
    }
#endif
}
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacLowPriorityIntHandler_128b132b_EXINT0(void)
{
}

//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacHighPriorityIntHandler_128b132b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_1);

    if(ScalerGetBit_EXINT(PFF_ED_MCU_CONTROL, _BIT1) == 0x00)
    {
        ScalerSetBit_EXINT(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _FLASH_CLK_PS_FAST_DIV);
    }

    // Fifo overflow/ underflow IRQ & flag
    if((ScalerGetBit_EXINT(P75_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(P70_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00))
    {
        // Disable fifo overflwo/ underflwo IRQ
        ScalerSetBit_EXINT(P75_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());

        // Disable HS/VS Tracking
        ScalerSetBit_EXINT(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
        // Disable INT for Auido and Reset Function
        ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

        // Disable Audio FSM
        ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(P75_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

        // Set DP Receive Port0 Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

        // Set DP Stream Regen Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

        // The Judge Handler take much time, It lead to MacBook 720P @50 <---> @60 Timing changing Issue
        if((ScalerDpMacDphyRxGetMstProtocolEnable_EXINT0(enumInputPort) == _DISABLE) &&
           (ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
           (ScalerDpPhyRxDFECheck_EXINT0(enumInputPort) == _FALSE))
        {
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x02, 0x00);
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x03, 0x00);
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x04, 0x80);
            ScalerDpAuxRxSetDpcdMirrorValue_EXINT0(enumInputPort, 0x00, 0x02, 0x05, 0x00);
        }

#if(_DP_TX_SUPPORT == _ON)
        if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (GET_DP_MAC_TX_INPUT_PORT() == enumInputPort))
        {
            // Set DPTx Force Output Idle Pattern
            ScalerDpMacTxForceIdlePattern_EXINT0();
        }
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        SET_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK();
#endif
    }

    // LLCTS 7.2.1.3 Sink Status
    if((ScalerGetBit_EXINT(P75_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(P75_37_DP_GLB_STATUS, _BIT6) == _BIT6))
    {
        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(P75_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

        // Clear VB-ID[3] Change Flag
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

        // For LLCTS 5.4.1.4
        if(ScalerGetBit_EXINT(P75_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == 0x00)
        {
            // Disable HS/VS Tracking
            ScalerSetBit_EXINT(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

            SET_DP_MAC_STREAM_RX1_VBID3_CHANGED();

            // Set DP Receive Port1 Out of Sync
            ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
        }
        else
        {
            if(ScalerGetBit_EXINT(P75_01_DP_VBID, _BIT3) == _BIT3)
            {
                // Set DP Receive Port1 Out of Sync
                ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
            }
        }
    }

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    if((ScalerGetBit_EXINT(P75_3A_DP_IRQ_CTRL0, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P75_37_DP_GLB_STATUS, _BIT1) == _BIT1))
    {
        // Disable DSC VB-ID[6] IRQ Setting
        ScalerSetBit_EXINT(P75_3A_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // Disable VB-ID[3] Change IRQ
        ScalerSetBit_EXINT(P75_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());

#if(_AUDIO_SUPPORT == _ON)
        // Disable INT for Auido and Reset Function
        ScalerAudioRxDisableSetting_EXINT0(enumInputPort);

        // Disable Audio FSM
        ScalerAudioDpAudioEnable_EXINT0(enumInputPort, _DISABLE);
#endif

        // Set DP Receive Port1 Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

        // Set DP Stream Regen Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

        // Enable DSC Change Flag When DSC Detect VB-ID[6] Change
        ScalerDpMacDscRxDscStreamSetChange_EXINT0(_DP_MAC_1, _ENABLE);

#if(_DP_TX_SUPPORT == _ON)
        if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (GET_DP_MAC_TX_INPUT_PORT() == enumInputPort))
        {
            // Set DPTx Force Output Idle Pattern
            ScalerDpMacTxForceIdlePattern_EXINT0();
        }
#endif
    }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    if((ScalerGetBit_EXINT(P75_4A_VSC10, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(P75_4B_VSC11, _BIT5) == _BIT5))
    {
        // Disable Pr Sdp Crc Receive IRQ
        ScalerSetBit_EXINT(P75_4A_VSC10, ~_BIT5, 0x00);

        // Pr Crc check
        ScalerDpMacStreamRx1PRModeCrcCheck_128b132b_EXINT0(enumInputPort);

        // Clr Pr Sdp Crc Receive Flag
        ScalerSetBit_EXINT(P75_4B_VSC11, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Enable Pr Sdp Crc Receive IRQ
        ScalerSetBit_EXINT(P75_4A_VSC10, ~_BIT5, _BIT5);
    }

    if((ScalerGetBit_EXINT(P75_4A_VSC10, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P75_4B_VSC11, _BIT7) == _BIT7))
    {
        BYTE ucPrSinkStatusTemp = ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x20, 0x22, (_BIT2 | _BIT1 | _BIT0));

        // Check Sourc Pr Function Enable
        if((ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0xB0) & _BIT0) == _BIT0)
        {
            // Check Pr Sink Status
            if((ucPrSinkStatusTemp == _DP_PR_MODE_INACTIVE) || (ucPrSinkStatusTemp == _DP_PR_MODE_INTERNAL_ERROR))
            {
                // Check Vsc Sdp Pr_State = 1
                if(ScalerGetDataPortBit_EXINT0(P75_47_VSC7, 0x01, _BIT0) == _BIT0)
                {
                    // Check Vsc Sdp Su_valid = 1
                    if(ScalerGetDataPortBit_EXINT0(P75_47_VSC7, 0x01, _BIT3) == _BIT3)
                    {
                        // Vsc Sdp DB1[0] Pr_state = 1, DB1[3] Su_valid = 1, Set Pr Sink Status Active from Inactive or Internal Error
                        ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_ACTIVE);
                    }
                    else
                    {
                        if(ucPrSinkStatusTemp != _DP_PR_MODE_INTERNAL_ERROR)
                        {
                            // Vsc Sdp DB1[0] Pr_state = 1, DB1[3] Su_valid = 0, Set Pr Sink Status Internal Error
                            ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_INTERNAL_ERROR);
                        }
                    }
                }
                else
                {
                    // Vsc Sdp DB1[0] Pr_state = 0, Set Pr Sink Status Inactive
                    ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_INACTIVE);
                }
            }
            else
            {
                // Check Vsc Sdp Pr_State != 1
                if(ScalerGetDataPortBit_EXINT0(P75_47_VSC7, 0x01, _BIT0) != _BIT0)
                {
                    // Vsc Sdp DB1[0] Pr_state = 0, Set Pr Sink Status Inactive
                    ScalerDpAuxRxDpcdPRModeStatusUpdate(enumInputPort, _DP_PR_MODE_INACTIVE);
                }
            }
        }

        // Clr Pr Sdp Pr_state Receive Flag
        ScalerSetBit_EXINT(P75_4B_VSC11, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Enable bit should be off-on
        ScalerSetBit_EXINT(P75_4A_VSC10, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P75_4A_VSC10, ~_BIT7, _BIT7);
    }
#endif

#if((_DP_MAC_RX1_DM_SUPPORT == _ON) || (_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON))
    if(ScalerGetBit_EXINT(P75_F3_DP_SDP_RSV0_CTRL, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        BYTE pucInfoframeVendorSpecInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
        DWORD ulAdvanceHdr10Oui = 0;
#endif

        // Get Vendor Sdp Data
        ScalerDpMacStreamRx1GetSdpPktData_EXINT0(_DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC, pucInfoframeVendorSpecInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        // Check DM Oui
        if(((pucInfoframeVendorSpecInfoData[2] == _DM_OUI_0) && (pucInfoframeVendorSpecInfoData[3] == _DM_OUI_1) && (pucInfoframeVendorSpecInfoData[4] == _DM_OUI_2)) && // OUI code
           ((pucInfoframeVendorSpecInfoData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
           (pucInfoframeVendorSpecInfoData[0] == 0x01) && // Version
           ((pucInfoframeVendorSpecInfoData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
        {
            SET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE(_SDP_STATE_RECEIVED);

            ScalerDMMetadataSourceMapping_EXINT0(pucInfoframeVendorSpecInfoData, _DP_DM_SDP_ENTRY, enumInputPort);
        }
        else
#endif
#endif
        {
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
            ulAdvanceHdr10Oui = pucInfoframeVendorSpecInfoData[3];
            ulAdvanceHdr10Oui = (ulAdvanceHdr10Oui << 8) + pucInfoframeVendorSpecInfoData[4];
            ulAdvanceHdr10Oui = (ulAdvanceHdr10Oui << 8) + pucInfoframeVendorSpecInfoData[5];

            // Check Advanced Hdr10 Oui
            if((ulAdvanceHdr10Oui == _ADVANCED_HDR10_OUI) && (GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON))
            {
                StructAdvancedHDR10MetaData stSyncAdvancedHDR10Metadata = {0};

                ScalerDpMacStreamRxAdvancedHdr10VsifDataStrcutMapping_EXINT0(pucInfoframeVendorSpecInfoData, &stSyncAdvancedHDR10Metadata);

                SET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE(_SDP_STATE_RECEIVED);

                ScalerColorAdvancedHDR10VSIFHandler_EXINT0(&stSyncAdvancedHDR10Metadata);
            }
#endif
        }

        // Clr Irq Flag and Enable bit should be off-on
        ScalerSetBit_EXINT(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT6);
        ScalerSetBit_EXINT(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT5);
    }
#endif

#if((((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)) || (_DP_MAC_RX1_DM_SUPPORT == _ON)) && (_DP_SDP_META_SRAM_SUPPORT == _ON))
    // Meta VSIF Data Rcv Int
    if(ScalerGetBit_EXINT(P7E_DA_META_SDP0_CTRL2, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
        ScalerDpMacStreamRx1Set1stBeIrqEnable_128b132b(_ENABLE);
#endif
        // No timeout
        if(ScalerGetBit_EXINT(P7E_DA_META_SDP0_CTRL2, _BIT2) == 0x00)
        {
            BYTE pucMetaVsifData[_DP_SDP_META_0_PAYLOAD_LENGTH] = {0};

            StructDpSdpMetaInfo structDpSdpMetaInfo;
            structDpSdpMetaInfo.enumIndex = _DP_SDP_META_0;
            structDpSdpMetaInfo.ucPacketDBLength = _DP_SDP_META_0_PAYLOAD_LENGTH;

            // Please Check: input ucLength < _DP_SDP_META_x_PAYLOAD_LENGTH
            if(ScalerDpMacStreamRx1GetMetaPktData_EXINT0(structDpSdpMetaInfo, pucMetaVsifData, 0, _DP_SDP_META_0_PAYLOAD_LENGTH) == _TRUE)
            {
#if((_DP_MAC_RX1_DM_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
                if(((pucMetaVsifData[2] == _DM_OUI_0) && (pucMetaVsifData[3] == _DM_OUI_1) && (pucMetaVsifData[4] == _DM_OUI_2)) && // OUI code
                   ((pucMetaVsifData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
                   (pucMetaVsifData[0] == 0x01) && // Version
                   ((pucMetaVsifData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
                {
                    ScalerDMMetadataSourceMapping_EXINT0(pucMetaVsifData, _DP_DM_EXT_SDP_ENTRY, enumInputPort);
                }
#endif
            }
        }

        ScalerSetBit_EXINT(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
    }

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
    // BE_1st Int
    if(ScalerGetBit_EXINT(P7E_E0_META_SRAM_CTRL, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        ScalerDpMacStreamRx1Set1stBeIrqEnable_128b132b(_DISABLE);

        // Reset Meta Sram
        ScalerSetBit_EXINT(P7E_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT6);

        // Clr Rcv / TimeOut / Rcv_done flag
        ScalerSetBit_EXINT(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7E_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7E_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7E_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7E_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
    }
#endif
#endif
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP PR Mode CRC
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCrcCheck_128b132b_EXINT0(EnumInputPort enumInputPort)
{
    BYTE pucSourceCrc[6] = {0};

    // Get DP SDP RSV0 PR Mode Pr_state DB1[0]
    if(ScalerGetDataPortBit_EXINT0(P75_47_VSC7, 0x01, _BIT0) == _BIT0)
    {
        if((ScalerGetBit_EXINT(P75_4B_VSC11, _BIT5) == _BIT5) && (ScalerDpAuxRxGetPRModeDpcdCrcEnable_EXINT0(enumInputPort) == _TRUE))
        {
            ScalerGetDataPortByte_EXINT0(P75_47_VSC7, 0x02, 6, &pucSourceCrc[0], _AUTOINC);

            if((ScalerGetByte_EXINT(P70_52_DP_CRC_R_L) != pucSourceCrc[0]) || (ScalerGetByte_EXINT(P70_51_DP_CRC_R_M) != pucSourceCrc[1]) || (ScalerGetByte_EXINT(P70_54_DP_CRC_G_L) != pucSourceCrc[2]) ||
               (ScalerGetByte_EXINT(P70_53_DP_CRC_G_M) != pucSourceCrc[3]) || (ScalerGetByte_EXINT(P70_56_DP_CRC_B_L) != pucSourceCrc[4]) || (ScalerGetByte_EXINT(P70_55_DP_CRC_B_M) != pucSourceCrc[5]))
            {
                // Set PR Error Status CRC Mismatch
                ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(enumInputPort, _DP_PR_MODE_CRC_ERROR);
            }
        }
        else
        {
            // Set PR Error Status VSC SDP for PR UNCORRECTABLE Error
            ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(enumInputPort, _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR);
        }

        if((ScalerGetBit_EXINT(P75_4B_VSC11, _BIT5) == _BIT5) && (ScalerDpAuxRxGetPRModeDpcdCrcEnable_EXINT0(enumInputPort) == _FALSE))
        {
            // Set PR Error Status Sdp Uncorrectable
            ScalerDpAuxRxDpcdPRModeErrorStateUpdate_EXINT0(enumInputPort, _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR);
        }
    }
}

//--------------------------------------------------
// Description  : Enable/Disable DP PR Mode CRC Calculation
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCrcCalculateEnable_128b132b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Start CRC Calculation For Panel Replay CRC Check
        ScalerSetBit_EXINT(P70_50_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    }
    else
    {
        // Stop CRC Calculation For Panel Replay CRC Check
        ScalerSetBit_EXINT(P70_50_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }
}
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamWD_128b132b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit_EXINT(P75_38_DP_WD_CTRL_0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit_EXINT(P75_38_DP_WD_CTRL_0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit_EXINT(P75_3A_DP_IRQ_CTRL0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit_EXINT(P75_3A_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit_EXINT(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DM Re check DM Packet Irq Receive
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DMPacketReCheck_128b132b_EXINT0(EnumInputPort enumInputPort)
{
    if(ScalerGetBit_EXINT(P75_F3_DP_SDP_RSV0_CTRL, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        BYTE pucInfoframeVendorSpecInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};

        // Get Vendor Sdp Data
        ScalerDpMacStreamRx1GetSdpPktData_EXINT0(_DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC, pucInfoframeVendorSpecInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

        // Check DM Oui
        if(((pucInfoframeVendorSpecInfoData[2] == _DM_OUI_0) && (pucInfoframeVendorSpecInfoData[3] == _DM_OUI_1) && (pucInfoframeVendorSpecInfoData[4] == _DM_OUI_2)) && // OUI code
           ((pucInfoframeVendorSpecInfoData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
           (pucInfoframeVendorSpecInfoData[0] == 0x01) && // Version
           ((pucInfoframeVendorSpecInfoData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
        {
            SET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE(_SDP_STATE_RECEIVED);

            ScalerDMMetadataSourceMapping_EXINT0(pucInfoframeVendorSpecInfoData, _DP_DM_SDP_ENTRY, enumInputPort);

            // If receive Dolby Meta Data Clr Irq Flag and Enable bit should be off-on
            ScalerSetBit_EXINT(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT6);
            ScalerSetBit_EXINT(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT5);
        }
    }

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
    // Meta VSIF Data Rcv Int
    if(ScalerGetBit_EXINT(P7E_DA_META_SDP0_CTRL2, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // No timeout
        if(ScalerGetBit_EXINT(P7E_DA_META_SDP0_CTRL2, _BIT2) == 0x00)
        {
            BYTE pucMetaVsifData[_DP_SDP_META_0_PAYLOAD_LENGTH] = {0};

            StructDpSdpMetaInfo structDpSdpMetaInfo;
            structDpSdpMetaInfo.enumIndex = _DP_SDP_META_0;
            structDpSdpMetaInfo.ucPacketDBLength = _DP_SDP_META_0_PAYLOAD_LENGTH;

            // Please Check: input ucLength < _DP_SDP_META_x_PAYLOAD_LENGTH
            if(ScalerDpMacStreamRx1GetMetaPktData_EXINT0(structDpSdpMetaInfo, pucMetaVsifData, 0, _DP_SDP_META_0_PAYLOAD_LENGTH) == _TRUE)
            {
                if(((pucMetaVsifData[2] == _DM_OUI_0) && (pucMetaVsifData[3] == _DM_OUI_1) && (pucMetaVsifData[4] == _DM_OUI_2)) && // OUI code
                   ((pucMetaVsifData[5] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0)) && // V10 & LL
                   (pucMetaVsifData[0] == 0x01) && // Version
                   ((pucMetaVsifData[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x1B)) // Length
                {
                    ScalerDMMetadataSourceMapping_EXINT0(pucMetaVsifData, _DP_DM_EXT_SDP_ENTRY, enumInputPort);

                    // If receive Dolby Meta Data Clr Irq Flag and Enable bit should be off-on
                    ScalerSetBit_EXINT(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
                    // Reset Meta Sram
                    ScalerSetBit_EXINT(P7E_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT6);

                    // Clr Rcv / TimeOut / Rcv_done flag
                    ScalerSetBit_EXINT(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P7E_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P7E_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P7E_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
                    ScalerSetBit_EXINT(P7E_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
#endif
                }
            }
        }
    }
#endif
}
#endif
#endif // End of (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif
