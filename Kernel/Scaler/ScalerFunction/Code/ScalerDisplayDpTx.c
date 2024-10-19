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
// ID Code      : ScalerDisplayDpTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_DP_TX__

#include "ScalerFunctionInclude.h"
#include "DisplayDpTx/ScalerDisplayDpTx.h"

#if(_DISPLAY_DP_TX_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bDisplayDpTxSscEn = 0;
DWORD g_ulDisplayDpTxPortOffset;
DWORD g_ulDisplayDpTxMacOffset;

//****************************************************************************
// FUNCTION DEFINITIONS

//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Power Sequence Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxPowerSequenceProc(bit bLevel)
{
    bLevel = bLevel;

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        PCB_DPTX0_POWER_SEQUENCE(bLevel);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        PCB_DPTX1_POWER_SEQUENCE(bLevel);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        PCB_DPTX2_POWER_SEQUENCE(bLevel);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        PCB_DPTX3_POWER_SEQUENCE(bLevel);
    }
#else

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        PCB_DPTX3_POWER_SEQUENCE(bLevel);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        PCB_DPTX2_POWER_SEQUENCE(bLevel);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        PCB_DPTX1_POWER_SEQUENCE(bLevel);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        PCB_DPTX0_POWER_SEQUENCE(bLevel);
    }
#endif
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Link Sequence
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDisplayDpTxLinkSequence(void)
{
    bit bLTCheck = _SUCCESS;
    BYTE ucLTRetryNum = 0;

    do
    {
        bLTCheck = _SUCCESS;

        // Check DPTx Link Config
        ScalerDisplayDpTxLinkConfigCheck();

        // Check DPTx SSCG Status
        ScalerDisplayDpTxCheckSSC();

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
        if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
        {
            // Set Dptx0 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_0);
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
        {
            // Set Dptx1 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_1);
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
        {
            // Set Dptx2 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_2);
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
        {
            // Set Dptx3 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_3);
        }
#else
        if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
        {
            // Set Dptx3 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_3);
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
        {
            // Set Dptx2 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_2);
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
        {
            // Set Dptx1 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_1);
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
        {
            // Set Dptx0 Link Training
            bLTCheck &= ScalerDisplayDpTxLinkTraining(_DISPLAY_DP_TX_PORT_0);
        }
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
        ucLTRetryNum += 1;

        ScalerTimerDelayXms(5);
    }
    while((ucLTRetryNum < 5) && (bLTCheck != _SUCCESS));

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_3);
    }
#endif

    return bLTCheck;
}

//--------------------------------------------------
// Description  : Check for Dp Tx Link Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxLinkConfigCheck(void)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_3);
    }
#else
    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_3);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxLinkConfig(_DISPLAY_DP_TX_PORT_0);
    }
#endif
}

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxLinkSignalForceOutput(void)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_3);
    }
#else
    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_3);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxLinkForceOutput(_DISPLAY_DP_TX_PORT_0);
    }
#endif

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxTraininPatternEndSequence(_DISPLAY_DP_TX_PORT_3);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Settings for Dp Tx Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxStreamHanlder(bit bOutput)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_0, bOutput);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_1, bOutput);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_2, bOutput);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_3, bOutput);
    }
#else
    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_3, bOutput);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_2, bOutput);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_1, bOutput);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxVideoStreamOutput(_DISPLAY_DP_TX_PORT_0, bOutput);
    }
#endif
}

#if(_PANEL_DPTX_HPD_DETECT == _ON)
//--------------------------------------------------
// Description  : Display DP Tx Stable Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDisplayDpTxStableDetect(void)
{
    bit bStableCheck = _TRUE;

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        bStableCheck &= ScalerDisplayDpTxStableDetectCheck(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        bStableCheck &= ScalerDisplayDpTxStableDetectCheck(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        bStableCheck &= ScalerDisplayDpTxStableDetectCheck(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        bStableCheck &= ScalerDisplayDpTxStableDetectCheck(_DISPLAY_DP_TX_PORT_3);
    }

    return bStableCheck;
}
#endif

//--------------------------------------------------
// Description  : Setting for eDp Tx SSCG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxCheckSSC(void)
{
    bit bDpTxSscEn = _ENABLE;

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_3);
    }
#else
    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_3);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        bDpTxSscEn &= ScalerDisplayDpTxGetDownSpread(_DISPLAY_DP_TX_PORT_0);
    }
#endif

#if(_DEBUG_MESSAGE_CHECK_DISP_SETTING == _ON)
    if(bDpTxSscEn == _ENABLE)
    {
        DebugMessageCheck("eDP Panel DPCD support SSCG", 0x00);
    }
    else
    {
        DebugMessageCheck("eDP Panel DPCD might not support SSCG", 0x00);
    }
#endif

    bDpTxSscEn = (GET_PANEL_DPTX_SPREAD_RANGE() != 0) ? ((_PANEL_DPTX_FORCE_SSCG_SUPPORT == _ON) ? _ENABLE : bDpTxSscEn) : _DISABLE;

    SET_DISPLAY_DP_TX_SSCG_CONFIG(bDpTxSscEn);
}

//--------------------------------------------------
// Description  : Wait for Dp Tx Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPollingHotPlug(WORD usNum)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    bit bHPCheck = _FALSE;
    usPreviousTime = g_usTimerCounter;

    do
    {
        bHPCheck = _SUCCESS;

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
        if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_0) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_0, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                bHPCheck &= _FALSE;
            }
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_1) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_1, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
                {
                    if(_PANEL_DPTX_VENDOR_SPECIFIC_TYPE == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H)
                    {
                        ScalerDisplayDpTxVendorSpecific004F1hAuxWrite(_DISPLAY_DP_TX_PORT_2);
                    }
                }

                bHPCheck &= _FALSE;
            }
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_2) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_2, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
                {
                    if(_PANEL_DPTX_VENDOR_SPECIFIC_TYPE == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H)
                    {
                        ScalerDisplayDpTxVendorSpecific004F1hAuxWrite(_DISPLAY_DP_TX_PORT_1);
                    }
                }

                bHPCheck &= _FALSE;
            }
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_3) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_3, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                bHPCheck &= _FALSE;
            }
        }
#else
        if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_3) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_3, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                bHPCheck &= _FALSE;
            }
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_2) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_2, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
                {
                    if(_PANEL_DPTX_VENDOR_SPECIFIC_TYPE == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H)
                    {
                        ScalerDisplayDpTxVendorSpecific004F1hAuxWrite(_DISPLAY_DP_TX_PORT_1);
                    }
                }

                bHPCheck &= _FALSE;
            }
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_1) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_1, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
                {
                    if(_PANEL_DPTX_VENDOR_SPECIFIC_TYPE == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H)
                    {
                        ScalerDisplayDpTxVendorSpecific004F1hAuxWrite(_DISPLAY_DP_TX_PORT_2);
                    }
                }

                bHPCheck &= _FALSE;
            }
        }

        if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
        {
            if(ScalerDisplayDpTxGetHpdDebounceLevel(_DISPLAY_DP_TX_PORT_0) == _HIGH)
            {
                bHPCheck &= _SUCCESS;

                // Panel DPTx Power Sequence Check Point
                ScalerDisplayDpTxSetPowerSequenceCheckPoint(_DISPLAY_DP_TX_PORT_0, _DPTX_POWER_SEQUENCE_HPD_ON);
            }
            else
            {
                bHPCheck &= _FALSE;
            }
        }
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while((usTimeElapsed <= usNum) && (bHPCheck != _SUCCESS));

    DebugMessageCheck("eDP HPD Time", usTimeElapsed);
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxInitial(void)
{
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        // Initial DPTx0
        ScalerDisplayDpTxInitialSetting(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        // Initial DPTx1
        ScalerDisplayDpTxInitialSetting(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        // Initial DPTx2
        ScalerDisplayDpTxInitialSetting(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        // Initial DPTx3
        ScalerDisplayDpTxInitialSetting(_DISPLAY_DP_TX_PORT_3);
    }
}

//--------------------------------------------------
// Description  : Dp Tx PLL Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up Dp Tx PLL for LCLK
        Scaler32SetBit(PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT30, _BIT30);
    }
    else
    {
        // Power Down Dp Tx PLL for LCLK
        Scaler32SetBit(PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT30, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get eDPTx Pll Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayDpTxGetPllPowerStatus(void)
{
    if(Scaler32GetBit(PB58050_00_DP14_TX_CMU0, _BIT15) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Display Dp Tx Mac Switch Status
// Input Value  : EnumDisplayDpTxOutputPort
// Output Value : EnumDisplayDpMacSel
//--------------------------------------------------
EnumDisplayDpMacSel ScalerDisplayDpTxGetMacSwitch(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    enumDisplayDpTxOutputPort = enumDisplayDpTxOutputPort;

    if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16)
    {
        switch(enumDisplayDpTxOutputPort)
        {
            case _DISPLAY_DP_TX_PORT_0:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC0 : _DISPLAY_DP_TX_MAC3);

            case _DISPLAY_DP_TX_PORT_1:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC1 : _DISPLAY_DP_TX_MAC2);

            case _DISPLAY_DP_TX_PORT_2:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC2 : _DISPLAY_DP_TX_MAC1);

            case _DISPLAY_DP_TX_PORT_3:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC3 : _DISPLAY_DP_TX_MAC0);

            default:
                break;
        }
        return _DISPLAY_DP_TX_NO_MAC;
    }
    else if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
    {
        switch(enumDisplayDpTxOutputPort)
        {
            case _DISPLAY_DP_TX_PORT_1:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC0 : _DISPLAY_DP_TX_MAC1);

            case _DISPLAY_DP_TX_PORT_2:

                return (GET_PANEL_DPTX_PORT_MIRROR() == _DISABLE ? _DISPLAY_DP_TX_MAC1 : _DISPLAY_DP_TX_MAC0);

            case _DISPLAY_DP_TX_PORT_0:
            case _DISPLAY_DP_TX_PORT_3:
            default:
                break;
        }
        return _DISPLAY_DP_TX_NO_MAC;
    }
    else
    {
        return _DISPLAY_DP_TX_MAC0;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Drive Power
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxPhyControl(void)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_0);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_3);
    }
#else
    if(GET_PANEL_DISPLAY_DP_TX_PORT_3() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_3);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_2() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_2);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_1() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_1);
    }

    if(GET_PANEL_DISPLAY_DP_TX_PORT_0() == _ON)
    {
        ScalerDisplayDpTxPhyDrivePower(_DISPLAY_DP_TX_PORT_0);
    }
#endif
}

//--------------------------------------------------
// Description  : Setting DP Tx Link Training
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : Link Status
//--------------------------------------------------
bit ScalerDisplayDpTxLinkTraining(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    return ScalerDisplayDpTxXLinkTraining(enumDisplayDpTxOutputPort);
}

//--------------------------------------------------
// Description  : DPTX LT Training Pattern End Sequence
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxTraininPatternEndSequence(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    ScalerDisplayDpTxXTraininPatternEndSequence();
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : Link Config flag
//--------------------------------------------------
void ScalerDisplayDpTxLinkConfig(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    ScalerDisplayDpTxXLinkConfig(enumDisplayDpTxOutputPort);
}

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Link Signal Force Output
// Input Value  : enumDisplayDpTxOutputPort
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxLinkForceOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    ScalerDisplayDpTxXLinkForceOutput(enumDisplayDpTxOutputPort);
}
#endif

//--------------------------------------------------
// Description  : Handle Tx0 Output stream
// Input Value  : enumDisplayDpTxOutputPort, bOutput
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxVideoStreamOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, bit bOutput)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    ScalerDisplayDpTxXVideoStreamOutput(enumDisplayDpTxOutputPort, bOutput);
}

#if(_PANEL_DPTX_HPD_DETECT == _ON)
//--------------------------------------------------
// Description  : Display DP Tx HPD Detection
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : True Stable/ False Unstable
//--------------------------------------------------
bit ScalerDisplayDpTxStableDetectCheck(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    return ScalerDisplayDpTxXStableDetectCheck(enumDisplayDpTxOutputPort);
}
#endif

//--------------------------------------------------
// Description  : Display DP Tx HPD Debounce Level
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : DP Tx HPD Debounce Level
//--------------------------------------------------
bit ScalerDisplayDpTxGetHpdDebounceLevel(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

#if(_PANEL_DPTX_SET_HPD_DETECT_SEQUENCE == _HPD_DETECT_AFTER_PANEL_HPD_T2_TIME)
    if(GET_DISPLAY_DP_TXX_HPD_DEBOUNCE_LEVEL() == _HIGH)
    {
        // Clear HPD IRQ Flag
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, 0x00, 0xFE);
    }
#endif

    return GET_DISPLAY_DP_TXX_HPD_DEBOUNCE_LEVEL();
}

//--------------------------------------------------
// Description  : Set Display Dp Tx Vendor Aux Write
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : None SPECIFIC 004F1H
//--------------------------------------------------
void ScalerDisplayDpTxVendorSpecific004F1hAuxWrite(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    ScalerDisplayDpTxXVendorSpecific004F1hAuxWrite();
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxInitialSetting(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    ScalerDisplayDpTxXInitial(enumDisplayDpTxOutputPort);
}

//--------------------------------------------------
// Description  : Get DP Tx Down Spread
// Input Value  : enumDisplayDpTxOutputPort
// Output Value : Get DPCD Down Spread flag
//--------------------------------------------------
bit ScalerDisplayDpTxGetDownSpread(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TX_MAC_OFFSET(ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort));

    return GET_DISPLAY_DP_TXX_DOWN_SPREAD(enumDisplayDpTxOutputPort);
}

//--------------------------------------------------
// Description  : Set Display Dp Tx Power Sequence Check Point
// Input Value  : EnumDisplayDpTxOutputPort, High or Low
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxSetPowerSequenceCheckPoint(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, bit bLevel)
{
    bLevel = bLevel;

    switch(enumDisplayDpTxOutputPort)
    {
        case _DISPLAY_DP_TX_PORT_0:

            PCB_DPTX0_POWER_SEQUENCE(bLevel);
            break;

        case _DISPLAY_DP_TX_PORT_1:

            PCB_DPTX1_POWER_SEQUENCE(bLevel);
            break;

        case _DISPLAY_DP_TX_PORT_2:

            PCB_DPTX2_POWER_SEQUENCE(bLevel);
            break;

        case _DISPLAY_DP_TX_PORT_3:

            PCB_DPTX3_POWER_SEQUENCE(bLevel);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Write
//                ucSubAddress --> SubAddress of I2CoverAux Write
//                ucLength --> Length of I2CoverAux Write
//                pWriteArray --> Data of I2CoverAux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxAuxI2CoverWrite(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    bit bReturnValue = _TRUE;
    EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPortBackup = GET_DISPLAY_DP_TX_PORT_OFFSET();

    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    bReturnValue = ScalerDisplayDpTxXAuxI2CoverWrite(ucSlaveAddress, ucLength, pucDataArray, bMOT);

    if(enumDisplayDpTxOutputPortBackup != enumDisplayDpTxOutputPort)
    {
        SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPortBackup);
    }

    return bReturnValue;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Read
//                ucSubAddress --> SubAddress of I2CoverAux Read
//                ucLength --> Length of I2CoverAux Read
//                pWriteArray --> Data of I2CoverAux Read
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxAuxI2CoverRead(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    bit bReturnValue = _TRUE;
    EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPortBackup = GET_DISPLAY_DP_TX_PORT_OFFSET();

    SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPort);

    bReturnValue = ScalerDisplayDpTxXAuxI2CoverRead(ucSlaveAddress, ucLength, pucDataArray, bMOT);

    if(enumDisplayDpTxOutputPortBackup != enumDisplayDpTxOutputPort)
    {
        SET_DISPLAY_DP_TX_PORT_OFFSET(enumDisplayDpTxOutputPortBackup);
    }

    return bReturnValue;
}
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

