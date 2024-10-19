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
// ID Code      : ScalerDpMacDphyRx2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX2__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx2/ScalerDpMacDphyRx2.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX2_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
bit g_bDpMacDphyRx2SignaldetectINTHappened;
#endif

BYTE g_ucDpMacDphyRx2Temp;
BYTE g_ucDpMacDphyRx2EQCRC;

#if(_DP_MST_SUPPORT == _ON)
StructDPMacRxMiscInfo g_stDpMacDphyRx2MiscInfo;
BYTE g_pucDpMacDphyRx2MstTimeSlotBackup[_HW_DP_MST_ST_SOURCE_COUNT * 2];
BYTE g_pucDpMacDphyRx2MstStMuxBackup[_HW_DP_MST_ST_SOURCE_COUNT];
#endif

StructDpMacDphyRxHdcpCipherBackupInfo g_stDpMacDphyRx2HdcpCipherBackupInfo;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : DP MAC DPHY power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2PowerProc(EnumPowerAction enumPowerAction)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:

            if(GET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS() == _OFF)
            {
                DebugMessageDpRx("DP MAC DPHY Rx2 Power Off", 0);

                ScalerDpAuxRxSetManualMode(enumInputPort);

                // Set DPRX SRAM CLK Gate Disable
                ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                // DP MAC2 Power Cut Enable
                if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP14_DPHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE) == _SUCCESS)
                {
                    SET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS(_ON);

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP20_DPHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                }
                else
                {
                    // Set DPRX SRAM CLK Gate Enable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            if(GET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS() == _ON)
            {
                DebugMessageDpRx("DP MAC DPHY Rx2 Power On", 0);

                // DP MAC2 Power Cut Disable
                if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP14_DPHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS) == _SUCCESS)
                {
                    SET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS(_OFF);

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP20_DPHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif

                    // Recover Data from Power Cut State
                    ScalerDpMacDphyRxPowerDataRecover(enumInputPort);
                }
            }

            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpMacDphyRx2NormalPreDetect(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // For Dp PHY CTS Test
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) == _BIT7)
    {
        DebugMessageDpRx("DP MAC Rx2 --> PHY CTS Auto Mode", 0);

        ScalerDpPhyRxPhyCtsAutoMode(enumInputPort);

        return _FALSE;
    }
    else if(ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) == _TRUE)
    {
        DebugMessageDpRx("DP MAC Rx2 --> PHY CTS Manual Mode", 0);

        ScalerDpPhyRxPhyCts(enumInputPort);

        return _FALSE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpAuxRxGetAuxChPowerOnWakeUp(enumInputPort) == _TRUE)
    {
        ScalerDpAuxRxClrAuxChPowerOnWakeUp(enumInputPort);
    }

#endif

    if(ScalerDpAuxRxGetAssrModeEnable(enumInputPort) == _TRUE)
    {
        // ASSR Mode Setting
        ScalerDpMacDphyRx2ASSRModeSetting();
    }

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    ScalerDpMacStreamRxClrSourceTypeJudge(enumInputPort);
#endif

    switch(ScalerDpAuxRxGetLTStatus(enumInputPort))
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            ScalerDpAuxRxClrValidVideoCheck(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMacDphyRx2MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            if((ScalerDpMacDphyRx2CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) || (ScalerDpMacDphyRx2SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpMacDphyRx2MarginLinkCheck() == _TRUE) &&
               (ScalerDpMacDphyRx2AlignCheck() == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeCheck() == _TRUE))
            {
                DebugMessageDpRx("DP MAC RX2: Normal LT Pass", 0);
                /*
                DebugMessageDpRx("9. DP MAC RX2: Lane0 LE Diff", (g_pucDpMacRx2LEMaxTemp[0] - g_pucDpMacRx2LEMinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX2: Lane1 LE Diff", (g_pucDpMacRx2LEMaxTemp[1] - g_pucDpMacRx2LEMinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX2: Lane2 LE Diff", (g_pucDpMacRx2LEMaxTemp[2] - g_pucDpMacRx2LEMinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX2: Lane3 LE Diff", (g_pucDpMacRx2LEMaxTemp[3] - g_pucDpMacRx2LEMinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 LE Min", g_pucDpMacRx2LEMinTemp[0]);
                DebugMessageDpRx("9. DP MAC RX2: Lane1 LE Min", g_pucDpMacRx2LEMinTemp[1]);
                DebugMessageDpRx("9. DP MAC RX2: Lane2 LE Min", g_pucDpMacRx2LEMinTemp[2]);
                DebugMessageDpRx("9. DP MAC RX2: Lane3 LE Min", g_pucDpMacRx2LEMinTemp[3]);
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[0] - g_pucDpMacRx2Tap0MinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[1] - g_pucDpMacRx2Tap0MinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[2] - g_pucDpMacRx2Tap0MinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[3] - g_pucDpMacRx2Tap0MinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[0]);
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[1]);
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[2]);
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[3]);
                DebugMessageDpRx("9. DP MAC RX2: FLD Band", ScalerGetByte(PC5_BF_LANE0_A_CDR_02));
                DebugMessageDpRx("9. DP MAC RX2: Best FLD Band", ScalerGetByte(PC5_BE_LANE0_A_CDR_01));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[0] - g_pucDpMacRx2Tap0MinTemp2[0]));
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[1] - g_pucDpMacRx2Tap0MinTemp2[1]));
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[2] - g_pucDpMacRx2Tap0MinTemp2[2]));
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[3] - g_pucDpMacRx2Tap0MinTemp2[3]));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[0]);
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[1]);
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[2]);
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[3]);
                DebugMessageDpRx("9. DP MAC RX2: TP2 Check Result", g_ucDpMacRx2EQCRC);
                */

                ScalerDpAuxRxCancelLinkStatusIRQ(enumInputPort);

                if(ScalerDpAuxRxGetLinkTrainingSetPhyFinishFlag(enumInputPort) == _TRUE)
                {
                    // Mac Secondary Data Block Reset
                    ScalerDpMacStreamRxSecDataReset(enumInputPort);

                    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                    ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag(enumInputPort, _FALSE);
                }

                ScalerDpAuxRxSetManualMode(enumInputPort);

                if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_STATUS_FAIL)
                {
                    ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_NORMAL_LINK_TRAINING_PASS);

                    ScalerDpMacDphyRx2ScrambleSetting();
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);

                if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
                ScalerDpRxClearMarginLink(enumInputPort);
#endif

                ScalerDpAuxRxSetManualMode(enumInputPort);

                if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    ScalerDpAuxRxLinkStatusReload(enumInputPort);
                }

#if(_DP_RX_FEC_SUPPORT == _TRUE)
                if(ScalerDpMacDphyRx2FecDecodeCheck() == _TRUE)
                {
                    ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x80, ~_BIT2, _BIT2);
                }
#endif
                ScalerDpAuxRxSetAutoMode(enumInputPort);

                return _TRUE;
            }
            else
            {
                DebugMessageDpRx("7. DP MAC RX2: Link Status Fail IRQ", 0);

                ScalerDpAuxRxSetManualMode(enumInputPort);

                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS) ||
                   (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_STATUS_FAIL))
                {
                    ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_LINK_STATUS_FAIL);

                    ScalerDpAuxRxActiveLinkStatusIRQ(enumInputPort);
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;

        case _DP_LINK_TRAINING_FAIL:

            ScalerDpAuxRxCancelLinkStatusIRQ(enumInputPort);

            ScalerDpAuxRxActiveLinkStatusIRQ(enumInputPort);

            break;

        case _DP_FAKE_LINK_TRAINING_PASS:
        case _DP_FAKE_LINK_TRAINING_PASS_VBIOS:

            ScalerDpAuxRxClrValidVideoCheck(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMacDphyRx2MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            ScalerTimerDelayXms(30);

            DebugMessageDpRx("7. DP MAC RX2: Rebuild PHY", ScalerDpAuxRxGetLTStatus(enumInputPort));

            ScalerDpAuxRxCancelLinkStatusIRQ(enumInputPort);

            ScalerDpAuxRxSetManualMode(enumInputPort);

            if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS) ||
               (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpPhyRxRebuildPhy(enumInputPort, ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01));
            }

            ScalerDpAuxRxSetAutoMode(enumInputPort);

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpMacDphyRx2FecDetectStart(enumInputPort);
#endif
            // Mac Reset After Link Clock Stable
            ScalerDpMacDphyRx2Reset(enumInputPort);

            if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS)
            {
                ScalerDpMacDphyRx2DecodeErrorCountReset(_DP_MAC_DECODE_METHOD_8B10B);
            }

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpMacDphyRx2FecDetectEnd(enumInputPort);

            ScalerDpAuxRxSetFecStatusW1cProtectEnable(enumInputPort, _DISABLE);
#endif

            if((ScalerDpMacDphyRx2CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) || (ScalerDpMacDphyRx2SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpMacDphyRx2MarginLinkCheck() == _TRUE) &&
               (ScalerDpMacDphyRx2AlignCheck() == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeCheck() == _TRUE))
            {
                DebugMessageDpRx("7. DP MAC RX2: Rebuild Phy Pass", 0);

                /*
                DebugMessageDpRx("9. DP MAC RX2: Lane0 LE Diff", (g_pucDpMacRx2LEMaxTemp[0] - g_pucDpMacRx2LEMinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX2: Lane1 LE Diff", (g_pucDpMacRx2LEMaxTemp[1] - g_pucDpMacRx2LEMinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX2: Lane2 LE Diff", (g_pucDpMacRx2LEMaxTemp[2] - g_pucDpMacRx2LEMinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX2: Lane3 LE Diff", (g_pucDpMacRx2LEMaxTemp[3] - g_pucDpMacRx2LEMinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 LE Min", g_pucDpMacRx2LEMinTemp[0]);
                DebugMessageDpRx("9. DP MAC RX2: Lane1 LE Min", g_pucDpMacRx2LEMinTemp[1]);
                DebugMessageDpRx("9. DP MAC RX2: Lane2 LE Min", g_pucDpMacRx2LEMinTemp[2]);
                DebugMessageDpRx("9. DP MAC RX2: Lane3 LE Min", g_pucDpMacRx2LEMinTemp[3]);
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[0] - g_pucDpMacRx2Tap0MinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[1] - g_pucDpMacRx2Tap0MinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[2] - g_pucDpMacRx2Tap0MinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Diff", (g_pucDpMacRx2Tap0MaxTemp[3] - g_pucDpMacRx2Tap0MinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[0]);
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[1]);
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[2]);
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Max", g_pucDpMacRx2Tap0MaxTemp[3]);
                DebugMessageDpRx("9. DP MAC RX2: FLD Band", ScalerGetByte(PC5_BF_LANE0_A_CDR_02));
                DebugMessageDpRx("9. DP MAC RX2: Best FLD Band", ScalerGetByte(PC5_BE_LANE0_A_CDR_01));
                DebugMessageDpRx("9. DP MAC RX2: D10.2 Counter", g_usDpMacRx2ClockCount);
                DebugMessageDpRx("9. DP MAC RX2: D10.2 Counter1", g_usDpMacRx2ClockCount1);
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[0] - g_pucDpMacRx2Tap0MinTemp2[0]));
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[1] - g_pucDpMacRx2Tap0MinTemp2[1]));
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[2] - g_pucDpMacRx2Tap0MinTemp2[2]));
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Diff 2", (g_pucDpMacRx2Tap0MaxTemp2[3] - g_pucDpMacRx2Tap0MinTemp2[3]));
                DebugMessageDpRx("9. DP MAC RX2: Lane0 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[0]);
                DebugMessageDpRx("9. DP MAC RX2: Lane1 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[1]);
                DebugMessageDpRx("9. DP MAC RX2: Lane2 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[2]);
                DebugMessageDpRx("9. DP MAC RX2: Lane3 Tap0 Max 2", g_pucDpMacRx2Tap0MaxTemp2[3]);
                DebugMessageDpRx("9. DP MAC RX2: Best FLD Band", ScalerGetByte(PC5_BE_LANE0_A_CDR_01));
                DebugMessageDpRx("9. DP MAC RX2: TP2 Check Result", g_ucDpMacRx2EQCRC);
                */

                ScalerDpAuxRxSetManualMode(enumInputPort);

                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS) ||
                   (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
                {
                    ScalerDpAuxRxLinkStatusReload(enumInputPort);

                    ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_NORMAL_LINK_TRAINING_PASS);

                    ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag(enumInputPort, _FALSE);

                    ScalerDpMacDphyRx2ScrambleSetting();

#if(_DP_RX_FEC_SUPPORT == _ON)
                    if(ScalerDpMacDphyRx2FecDecodeCheck() == _TRUE)
                    {
                        ScalerDpMacDphyRxResetFecErrorCount(enumInputPort);
                    }
#endif
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);

                ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
                ScalerDpRxClearMarginLink(enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpAuxRxSetManualMode(enumInputPort);

                SET_DP_MAC_DPHY_RX2_LOAD_NEW_STREAM_PAYLOAD();

                ScalerDpAuxRxSetAutoMode(enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
                if(enumInputPort == GET_DP_RX_MAIN_PORT())
                {
                    // Reset Daisy Chain Async-fifo
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
                }
#endif
#endif
                return _TRUE;
            }
            else
            {
                DebugMessageDpRx("7. DP MAC RX2: Rebuild PHY Fail", 0);

                ScalerDpAuxRxSetManualMode(enumInputPort);

                if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS_VBIOS)
                {
                    ScalerDpAuxRxDpcdLinkStatusReset(enumInputPort, _DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_HDCP14_RX_SUPPORT == _ON)
                    ScalerDpHdcp14RxResetProc(enumInputPort);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    ScalerDpHdcp2RxResetProc(enumInputPort);
#endif
                }
                else if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS)
                {
                    ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_LINK_STATUS_FAIL);
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;

        case _DP_LINK_TRAINING_NONE:

            if(ScalerDpAuxRxGetValidVideoCheck(enumInputPort) == _TRUE)
            {
                ScalerDpMacDphyRx2ValidSignalDetection();

                DebugMessageDpRx("7. DP MAC RX2: VBIOS Check !!!!!!!", ScalerDpAuxRxGetFakeLT(enumInputPort));
            }

            break;

        default:

            break;
    }

    if(ScalerDpAuxRxGetValidVideoCheck(enumInputPort) == _TRUE)
    {
        ScalerDpAuxRxClrValidVideoCheck(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpMacDphyRx2MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpMacDphyRx2PSPreDetect(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, _BIT7) == _BIT7) || (ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) == _TRUE))
    {
        DebugMessageDpRx("DP MAC Rx2 --> PHY CTS", 0);

        return _TRUE;
    }

    if(ScalerDpAuxRxGetValidVideoCheck(enumInputPort) == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX2: Valid Video Check", 0);

        return _TRUE;
    }

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    if(ScalerDebugCheckDebugPort(enumInputPort) == _FALSE)
#endif
    {
        if(ScalerDpAuxRxGetToggle(enumInputPort) == _TRUE)
        {
            DebugMessageDpRx("7. DP MAC RX2: Power Saving Aux Handshake", 0);

            return _TRUE;
        }
    }

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageDpRx("7. DP MAC RX2: Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort)) != _DP_ST_NONE)
    {
        DebugMessageDpRx("7. DP MAC RX2: Stream Allocate", 0);

        return _TRUE;
    }

    if(ScalerDpAuxRxGetAuxChPowerOnWakeUp(enumInputPort) == _TRUE)
    {
        ScalerDpAuxRxClrAuxChPowerOnWakeUp(enumInputPort);

        return _TRUE;
    }
#endif

    if((((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS) ||
         (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_STATUS_FAIL)) &&
        ((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_AUDIO_SUPPORT == _ON) && (_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(enumInputPort) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(enumInputPort));
            return _TRUE;
        }
#endif
        DebugMessageDpRx("7. DP MAC RX2: Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2DigitalPhyInitial(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Set Digital Phy to Normal
    ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT2 | _BIT1), 0x00);

    // Enable CDI removal
    ScalerSetBit(PD2_CE_CDI_REMOVAL_DP20_1, ~_BIT7, _BIT7);

    // Enable FEC FIFO
    ScalerSetBit(PD2_80_FEC_DECODE_CTL, ~(_BIT6 | _BIT0), _BIT0);
#endif

    // Set Digital Phy to Normal
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // Enable K28.1 Detection
    ScalerSetBit(PC5_4B_DP_COMMA_DET_MANU, ~(_BIT2 | _BIT1), _BIT2);

    // err_8b10b_ctrl_gate = 1'b1 --> Avoid 8b10b Error Decode to FS
    ScalerSetBit(PC5_00_HD_DP_SEL, ~(_BIT1 | _BIT0), _BIT1);

    // alpm_wake_reset = 1'b1
    ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT6, _BIT6);

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _ON)
    // Enable FEC Weak Mode
    ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, _BIT2);

    // Enable FEC Weak Mode Gated
    ScalerSetBit(PC5_E1_FEC_ERROR_CONTROL, ~_BIT0, _BIT0);
#endif
    // Flag Clear
    ScalerSetBit(PC5_D2_FEC_SEQUENCE_DET_CTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5));

    // Enable FEC Detect FEC_DECODE_EN and FEC_DECODE_DIS IRQ
    ScalerSetBit(PC5_D2_FEC_SEQUENCE_DET_CTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Enable FEC Error Count Calculate 1lane mode
    ScalerSetBit(PC5_E1_FEC_ERROR_CONTROL, ~_BIT7, 0x00);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Enable ML_PHY_SLEEP Symbol Replacement
    ScalerSetBit(PC5_E3_FEC_ALPM_CTRL_1, ~_BIT7, _BIT7);
#endif
#endif

    // Restore HDCP Mode
    ScalerDpMacDphyRx2HdcpModeRestore();
}

//--------------------------------------------------
// Description  : DP Scramble Setting
// Input Value  : None
// Output Value : None
//              : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ScrambleSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);
    EnumDpAuxRxModeStatus enumBackUpAuxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);
    bit bEnhanceChange = _FALSE;
    bit bScrambleChange = _FALSE;

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(PD2_A7_SCRAMBLE_CTRL_DP20, _BIT5) == _BIT5))
        {
            bScrambleChange = _TRUE;

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5)
            {
                // Disable Scrambling
                ScalerSetBit(PD2_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, _BIT5);
            }
            else
            {
                // Enable Scrambling
                ScalerSetBit(PD2_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, 0x00);
            }
        }
    }
    else
#endif
    {
        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, _BIT7) == _BIT7) != (ScalerGetBit(PC5_01_PHY_DIG_RESET_CTRL, _BIT2) == _BIT2))
        {
            bEnhanceChange = _TRUE;

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, _BIT7) == _BIT7)
            {
                // Enable Enhancement Control Mode --> MAC
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
            }
            else
            {
                // Disable Enhancement Control Mode --> MAC
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
            }
        }

        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(PC5_07_SCRAMBLE_CTRL, _BIT5) == _BIT5))
        {
            bScrambleChange = _TRUE;

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5)
            {
                // Disable Scrambling
                ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                // Enable Scrambling
                ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
            }
        }
    }

    if((bEnhanceChange == _TRUE) || (bScrambleChange == _TRUE))
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);

        // Delay 2ms for Scramble
        ScalerTimerDelayXms(2);

        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2DecodeErrorCountReset(EnumDpMacDecodeMethod enumDpMacDecodeMethod)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Check if during Symbol Error Cnt Test
    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x02) & 0xC0) != 0x00)
    {
        return _FALSE;
    }

    // Reset 8b10b Error Count Value
    ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    switch(enumDpMacDecodeMethod)
    {
        case _DP_MAC_DECODE_METHOD_PRBS7:

            // Reverse PRBS7 Pattern Gen
            SET_DP_MAC_RX2_PRBS_REVERSE_EN();

            // Select PRBS7
            ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT6 | _BIT5), 0x00);

            // Start Record PRBS7 Error Count Value
            ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            break;

        case _DP_MAC_DECODE_METHOD_PRBS31:

            // Select PRBS31
            ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Start Record PRBS7 Error Count Value
            ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            break;

        case _DP_MAC_DECODE_METHOD_8B10B_DISPARITY:

            // Start Record 8b10b or Disparity Error Count Value
            ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;

        default:
        case _DP_MAC_DECODE_METHOD_8B10B:

            // Start Record 8b10b Error Count Value
            ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Measure 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(WORD usErrorCriteria, BYTE ucDpMacRx2LaneNumber)
{
    WORD usErrorCountLaneMeasure = 0;

    // Select Lane
    ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpMacRx2LaneNumber << 3));

    usErrorCountLaneMeasure = ((((WORD)ScalerGetByte(PC5_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PC5_0C_BIST_PATTERN4));

    if(usErrorCountLaneMeasure > usErrorCriteria)
    {
        DebugMessageDpRx("DP MAC RX2: Lane", ucDpMacRx2LaneNumber);
        DebugMessageDpRx("DP MAC RX2: Lane Burst Error", usErrorCountLaneMeasure);

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Get 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : Error Count
//--------------------------------------------------
WORD ScalerDpMacDphyRx2GetDecodeErrorCount(BYTE ucDpMacRx2LaneNumber)
{
    // Select Lane
    ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpMacRx2LaneNumber << 3));

    return ((((WORD)ScalerGetByte(PC5_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PC5_0C_BIST_PATTERN4));
}

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx2LaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx2LaneSwapSelect_128b132b(enumInputPort, ucClockLaneSelect);
    }
    else
#endif
    {
        ScalerDpMacDphyRx2LaneSwapSelect_8b10b(enumInputPort, ucClockLaneSelect);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRx2GetLaneMuxMapping(EnumDpLane enumDpLane)
{
    switch(enumDpLane)
    {
        case _DP_LANE_0:

            return ScalerGetBit(PC5_03_LANE_MUX, (_BIT1 | _BIT0));

        case _DP_LANE_1:

            return ScalerGetBit(PC5_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2;

        case _DP_LANE_2:

            return ScalerGetBit(PC5_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4;

        case _DP_LANE_3:

            return ScalerGetBit(PC5_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6;

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2LaneCountSet(BYTE ucDpLaneCount)
{
    switch(ucDpLaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT3);
#endif
            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT4);
#endif
            break;

        case _DP_FOUR_LANE:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#endif
            break;

        default:

            // [4:3] DP MAC Select Default
            ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), 0x00);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), 0x00);
#endif
            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Comma Detect
// Input Value  : ON or OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2SetCommaDetect(bit bEn)
{
    if(bEn == _ON)
    {
        // [4] Enable Comma Detection
        ScalerSetBit(PC5_05_SAMPLE_EDGE, ~_BIT4, 0x00);
    }
    else
    {
        // [4] Disable Comma Detection
        ScalerSetBit(PC5_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ClkSelect(EnumDpMacClkSelect enumClkSelect)
{
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT6, enumClkSelect);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT5, enumClkSelect >> 1);
#endif
}

//--------------------------------------------------
// Description  : Reset DP MAC FIFIO
// Input Value  : Inputport
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ChannelFifoReset(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2)) == _CODING_TYPE_128B132B)
    {
        // FIFO sync
        ScalerSetBit(PD2_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
        ScalerSetBit(PD2_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);
    }
    else
#endif
    {
        // FIFO sync
        ScalerSetBit(PC5_10_PHY_CH_FIFO_SYNC0, ~_BIT0, 0x00);
        ScalerSetBit(PC5_10_PHY_CH_FIFO_SYNC0, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpMacDphyRx2AlignCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if((GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE) ||
       (ScalerDpMacStreamRxGetSourceTypeJudgeStatus(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRx2LaneValidCheck() == _FALSE))
    {
        return _TRUE;
    }
#endif

    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F) == _DP_ONE_LANE)
    {
        return _TRUE;
    }
    else
    {
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            if(ScalerGetBit(PD2_F7_DESKEW_PHY, _BIT4) == 0x00)
            {
                DebugMessageDpRx("DP MAC RX2: DP20 align fail warning", ScalerGetByte(PD2_F7_DESKEW_PHY));

                // Phy sync interval = 12672bit @10G 1.26us
                DELAY_5US();

                if(ScalerGetBit(PD2_F7_DESKEW_PHY, _BIT4) == 0x00)
                {
                    DebugMessageDpRx("DP MAC RX2: DP20 align fail", ScalerGetByte(PD2_F7_DESKEW_PHY));

                    return _FALSE;
                }
            }
        }
        else
#endif
        {
            if(ScalerGetBit(PC5_0E_DESKEW_PHY, _BIT4) == 0x00)
            {
                if(ScalerGetBit(PC5_0E_DESKEW_PHY, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
                {
                    ScalerSetBit(PC5_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), (_BIT7 | _BIT6));

                    ScalerTimerDelayXms(3);
                }
                else
                {
                    DebugMessageDpRx("DP MAC RX2: DP14 align fail", ScalerGetByte(PC5_0E_DESKEW_PHY));
                    return _FALSE;
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpMacDphyRx2DecodeCheck(void)
{
    BYTE ucTemp = 3;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if((GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE) ||
       (ScalerDpMacStreamRxGetSourceTypeJudgeStatus(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRx2LaneValidCheck() == _FALSE))
    {
        return _TRUE;
    }
#endif

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Check FEC Decode Status
        if(ScalerGetBit(PD2_80_FEC_DECODE_CTL, _BIT7) != _BIT7)
        {
            DebugMessageDpRx("DP MAC RX2: DP20 FEC Not Enable", ScalerGetByte(PD2_80_FEC_DECODE_CTL));

            return _FALSE;
        }

        while(ucTemp > 0)
        {
            // Disable FEC Accumulated Err Counter
            ScalerSetBit(PD2_96_FEC_ACCUM_ERR_CTRL_7, ~_BIT0, 0x00);

            // Clear 128b/132b FEC Error Flag
            ScalerSetBit(PD2_8F_FEC_ACCUM_ERR_CTRL_0, ~_BIT6, _BIT6);

            // Set FEC Accumulated Error Threshold
            ScalerSetBit(PD2_8F_FEC_ACCUM_ERR_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Enable FEC Accumulated Err Counter
            ScalerSetBit(PD2_96_FEC_ACCUM_ERR_CTRL_7, ~_BIT0, _BIT0);

            // Delay Time us [150,x]
            DELAY_XUS(150);

            // DP20 Decode Check
            if(ScalerGetBit(PD2_8F_FEC_ACCUM_ERR_CTRL_0, _BIT6) == 0x00)
            {
                return _TRUE;
            }

            ucTemp--;
        }

        DebugMessageDpRx("DP MAC RX2: DP20 FEC ACC ERROR Fail", ScalerGetByte(PD2_8F_FEC_ACCUM_ERR_CTRL_0));

        return _FALSE;
    }
    else
#endif
    // dp14 decode check : 8b10b decode check
    {
        while(ucTemp > 0)
        {
            // Clear 8b/10b Decode Error Flag
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // Delay Time us [150,x]
            DELAY_XUS(150);

            switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
            {
                case _DP_ONE_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)
                    if(ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)
#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
                    if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
#endif
                    {
                        return _TRUE;
                    }

                    break;

                case _DP_TWO_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

                    if(ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)
                    {
                        return _TRUE;
                    }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)

                    if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                    {
                        if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3) && (ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                        {
                            return _TRUE;
                        }
                    }
#endif

                    break;

                case _DP_FOUR_LANE:

                    if(ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
                    {
                        return _TRUE;
                    }

                    break;

                default:

                    return _FALSE;

                    break;
            }

            ucTemp--;
        }

        DebugMessageDpRx("7. DP MAC RX2: 8b/10b Decode Error", 0);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 Reset Proc for MAC RX2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp14ResetProc(void)
{
    // Reset HDCP Block
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2HDCPUnplugReset(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

#if(_DP_HDCP14_RX_SUPPORT == _ON)
    ScalerDpHdcp14RxUnplugResetProc(enumInputPort);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2RxUnplugResetProc(enumInputPort);
#endif

    // Clear CPIRQ flag while unplug
    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, 0x00);
}

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2CheckHdcpCpirqStatus(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx2CheckHdcpCpirqStatus_128b132b();
    }
    else
#endif
    {
        ScalerDpMacDphyRx2CheckHdcpCpirqStatus_8b10b();
    }
}

//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpReAuthStatusCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x07) != 0x00) ||
       (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x08) != 0x00) ||
       (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x09) != 0x00) ||
       (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x0A) != 0x00) ||
       (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x0B) != 0x00))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx2CpIRQ_128b132b(enumBStatusType);
    }
    else
#endif
    {
        ScalerDpMacDphyRx2CpIRQ_8b10b(enumBStatusType);
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckValid(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx2HdcpCheckValid_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx2HdcpCheckValid_8b10b();
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckEnabled(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx2HdcpCheckEnabled_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx2HdcpCheckEnabled_8b10b();
    }
}

//--------------------------------------------------
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2HdcpDownLoadKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP Block, HDCP FW Mode and Key download port
        ScalerSetBit(PC5_17_DP_HDCP_CONTROL, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT4 | _BIT0));

        // Set Km Clock to Xtal Clock
        ScalerSetBit(PC5_1A_HDCP_IRQ, ~_BIT3, 0x00);

        // Enable HDCP Sram clk
        ScalerSetBit(PC5_A6_HDCP_DUMMY_1, ~_BIT2, _BIT2);
        ScalerMcuDelayXus(1);
    }
    else
    {
        // Disable HDCP Sram clk
        ScalerSetBit(PC5_A6_HDCP_DUMMY_1, ~_BIT2, 0x00);
        ScalerMcuDelayXus(1);

        // Disable Key download port
        ScalerSetBit(PC5_17_DP_HDCP_CONTROL, ~_BIT0, 0x00);

        // Enable HDCP Sram clk
        ScalerSetBit(PC5_A6_HDCP_DUMMY_1, ~_BIT2, _BIT2);
        ScalerMcuDelayXus(1);
    }
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key to SRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2HdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray)
{
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    WORD usIndex = 0;

    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        ScalerSetByte(PC5_18_DP_HDCP_DOWNLOAD_PORT, pucReadArray[usIndex]);

        // Polling 1ms for Key Sram Write Done
        ScalerTimerPollingFlagProc(1, PC5_17_DP_HDCP_CONTROL, _BIT6, _TRUE);
    }
#else
    ScalerWrite(PC5_18_DP_HDCP_DOWNLOAD_PORT, usLength, pucReadArray, _NON_AUTOINC);
#endif
}

//--------------------------------------------------
// Description  : HDCP Mode Alignment between Variable & Register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2HdcpModeRestore(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
    {
        // Enable HDCP MAC2 for HDCP 2.2 Mode
        ScalerDpMacDphyRx2SetHdcpMode(_HDCP_22);

        if(ScalerDpMacDphyRx2HdcpDetectLvp() == _FALSE)
        {
            ScalerDpMacDphyRx2Hdcp2CipherDataRestore();
        }
    }
    else
#endif
    {
        // Enable HDCP MAC2 for HDCP 1.4 Mode
        ScalerDpMacDphyRx2SetHdcpMode(_HDCP_14);

        if(ScalerDpMacDphyRx2HdcpReAuthStatusCheck() == _TRUE)
        {
            if(ScalerDpMacDphyRx2HdcpDetectLvp_8b10b() == _FALSE)
            {
                bit bDpcdR0Available = 0;

                ScalerDpAuxRxSetManualMode(enumInputPort);

                DELAY_XUS(200);

                // Backup R0' Available Flag
                bDpcdR0Available = (bit)ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x06, 0x80, 0x29, _BIT1);

                // HDCP R0 Calculate
                ScalerSetBit(PC5_63_HDCP_OTHER, ~_BIT7, _BIT7);
                ScalerSetBit(PC5_63_HDCP_OTHER, ~_BIT7, 0x00);

                if(bDpcdR0Available == _FALSE)
                {
                    DELAY_XUS(200);

                    ScalerDpAuxRxSetDpcdBitValue(enumInputPort, 0x06, 0x80, 0x29, ~_BIT1, 0x00);
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Set HDCP Mode
// Input Value  : EnumHDCPType
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2SetHdcpMode(EnumHDCPType enumHDCPType)
{
    enumHDCPType = enumHDCPType;

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_8B10B)
#endif
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if(enumHDCPType == _HDCP_22)
        {
            ScalerSetBit(PC5_1A_HDCP_IRQ, ~_BIT1, _BIT1);
        }
        else
#endif
        {
            ScalerSetBit(PC5_1A_HDCP_IRQ, ~_BIT1, 0x00);
        }
    }
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx2Hdcp2ReAuthStatusCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Check for HDCP 2.2 Riv
    if(((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x28) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x29) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x2A) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x2B) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x2C) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x2D) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x2E) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x2F) != 0x00)) &&
       (ScalerDpHdcp2GetAuthenticationDone(enumInputPort) == _TRUE))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2FecDecode(BYTE ucFECDecode)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ucFECDecode == _ENABLE)
    {
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        ////// DP20 Part //////
        // FEC Enable
        ScalerSetBit(PD2_80_FEC_DECODE_CTL, ~(_BIT6 | _BIT0), _BIT0);

        // Enable FEC error detect
        ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~_BIT7, _BIT7);
#endif
        ////// DP14 Part //////
        // FEC Enable
        ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Enable FEC error detect
        ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~_BIT7, _BIT7);
    }
    else
    {
        // FEC Disable
        ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~(_BIT7 | _BIT0), 0x00);

        // Disable FEC error detect
        ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~_BIT7, 0x00);

        // Clear FEC DPCD Error Count
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x81, 0x00);
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x82, 0x00);
    }
}

//--------------------------------------------------
// Description  : FEC Decode Check
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2FecDecodeCheck(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerGetBit(PD2_80_FEC_DECODE_CTL, _BIT7) == _BIT7)
    {
        return _TRUE;
    }
#endif

    if(((ScalerGetBit(PC5_D0_FEC_DECODE_CTL, _BIT7) == _BIT7) && (ScalerGetBit(PC5_D2_FEC_SEQUENCE_DET_CTL, _BIT7) == _BIT7)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : FEC Detction Setting (Weak mode)
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2FecDetectStart(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx2FecDecode(_ENABLE);
    }
    else
#endif
    {
        // Reset FEC Ready
        ScalerDpMacDphyRx2FecDecode(_DISABLE);

        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0) != GET_DP_MAC_DPHY_RX2_FEC_DECODE_STATUS())
        {
            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
            {
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _OFF)
                // Enable FEC Seq Weak mode
                ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, _BIT2);
#endif
                ScalerDpMacDphyRx2FecDecode(_ENABLE);
            }
            else
            {
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _OFF)
                // Disable FEC Seq Weak mode
                ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
                ScalerDpMacDphyRx2FecDecode(_DISABLE);
            }
        }
    }
}

//--------------------------------------------------
// Description  : FEC Detction End (Weak mode)
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2FecDetectEnd(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) != _CODING_TYPE_128B132B)
#endif
    {
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _OFF)
        // After more than 65536x2x10xLink_Rate, Disable FEC Seq Weak mode
        ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
        if(ScalerDpMacDphyRx2FecDecodeCheck() == _TRUE)
        {
            ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x80, ~_BIT2, _BIT2);
        }
    }
}
#endif

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
DWORD ScalerDpMacDphyRx2SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    DWORD ulDpMeasureCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        ScalerDpPhyRxSignalDetection(enumInputPort, _ENABLE);
    }

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ulDpMeasureCount = (DWORD)ScalerDpMacDphyRx2SignalDetectMeasureCount_128b132b(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
    }
    else
#endif
    {
        // [1:0] freqdet_lane_sel
        ScalerSetBit(PC5_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

        // [5] ln_ck_sel
        ScalerSetBit(PC5_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

        switch(enumDpMeasurePeriod)
        {
            case _DP_MEASURE_PERIOD_125_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00000
                ScalerSetBit(PC5_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                break;

            case _DP_MEASURE_PERIOD_250_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00001
                ScalerSetBit(PC5_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                break;

            case _DP_MEASURE_PERIOD_1000_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00011
                ScalerSetBit(PC5_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                break;

            case _DP_MEASURE_PERIOD_2000_CYCLE:
            default:

                // [4:0] DP_XTAL_CYCLE = 5'b00100
                ScalerSetBit(PC5_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                break;
        }

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PC5_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PC5_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PC5_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Delay Time us [5,150] Polling for Measure Done
        for(pData[0] = 0; pData[0] <= 30; pData[0]++)
        {
            DELAY_5US();

            if(ScalerGetBit(PC5_50_DP_SIG_DET_0, _BIT6) == _BIT6)
            {
                ulDpMeasureCount = (DWORD)((((WORD)ScalerGetByte(PC5_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PC5_54_DP_SIG_DET_4));

                break;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PC5_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    }

    ScalerDpPhyRxSignalDetection(enumInputPort, _DISABLE);

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_32_BIT)
    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        return ulDpMeasureCount;
    }
    else
    {
        return ((ulDpMeasureCount << 3) / 5);
    }
#elif(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_16_BIT)
    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        return ulDpMeasureCount;
    }
    else
    {
        return ((ulDpMeasureCount << 2) / 5);
    }
#else

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ulDpMeasureCount << 1;
    }
    else
#endif
    {
        return ulDpMeasureCount;
    }

#endif
}

//--------------------------------------------------
// Description : Check Valid Signal
// Input Value  : DP Link Rate and Lane Count
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpMacDphyRx2SignalCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    WORD usDataStreamL0 = 0;
    WORD usDataStreamL1 = 0;
    WORD usDataStreamL2 = 0;
    WORD usDataStreamL3 = 0;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Scrambling Disable Check
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5)
    {
        return _TRUE;
    }

    // Transition Check Cannot Reflect 128/132 Decode
    if(enumDpLinkRate > _DP_LINK_HBR3)
    {
        return _TRUE;
    }

#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED();
#endif

    // Measure Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            usDataStreamL0 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        case _DP_TWO_LANE:

            usDataStreamL0 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        default:
        case _DP_FOUR_LANE:

            usDataStreamL0 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL2 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_2), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL3 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_3), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;
    }

    // Data Stream Count Upper Bound = (VCO target count) x 2 x 0.65
    // Data Stream Count Lower Bound = (VCO target count) x 2 x 0.55
    switch(enumDpLinkRate)
    {
        case _DP_LINK_HBR3_9G:

            usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR3_9G_SAVED;
            usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR3_9G_SAVED;

            break;

        case _DP_LINK_HBR3:

            usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR3_SAVED;
            usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR3_SAVED;

            break;

        case _DP_LINK_HBR2:

            usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED;
            usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED;

            break;

        case _DP_LINK_HBR:

            usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED;
            usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED;

            break;

        case _DP_LINK_RBR:

            usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED;
            usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED;

            break;

        default:

            break;
    }

    // Link Rate is a Unreasonable Value
    if((usMeasureUpperBound == 0) || (usMeasureLowerBound == 0))
    {
#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
        if(GET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
        {
            return _FALSE;
        }
    }

    // Check Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound))
            {
#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;

        case _DP_TWO_LANE:

            if(((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound)) ||
               ((usDataStreamL1 > usMeasureUpperBound) || (usDataStreamL1 < usMeasureLowerBound)))
            {
#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;

        default:
        case _DP_FOUR_LANE:

            if(((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound)) ||
               ((usDataStreamL1 > usMeasureUpperBound) || (usDataStreamL1 < usMeasureLowerBound)) ||
               ((usDataStreamL2 > usMeasureUpperBound) || (usDataStreamL2 < usMeasureLowerBound)) ||
               ((usDataStreamL3 > usMeasureUpperBound) || (usDataStreamL3 < usMeasureLowerBound)))
            {
#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Valid Lane CDR
// Input Value  : None
// Output Value : True --> CDR Lock
//--------------------------------------------------
bit ScalerDpMacDphyRx2CDRCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED();
#endif

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if(ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0)) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0)) == _TRUE) &&
               (ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1)) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0)) == _TRUE) &&
               (ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1)) == _TRUE) &&
               (ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_2)) == _TRUE) &&
               (ScalerDpMacDphyRx2MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_3)) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

#if(_HW_DP_GDI_RX2_DFE_TYPE == _PASSIVE_DFE)
    if(GET_DP_MAC_DPHY_RX2_SIGNALDETECT_INT_HAPPENED() == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        DebugMessageDpRx("7. DP MAC RX2: wuzanne test : CDR Unlock", 0);

        return _FALSE;
    }
}

#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx2 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2MstReset(void)
{
    BYTE ucTemp = 0;

    // Reset STx
    for(ucTemp = _DP_ST_1; ucTemp <= _DP_ST_END; ucTemp++)
    {
#if(_DP_MST_SUPPORT == _ON)
        // Reset Start Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_8B10B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Reset End Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX2_STX_END_ADDRESS_8B10B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Reset Start Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_128B132B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Reset End Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX2_STX_END_ADDRESS_128B132B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Reset Stream Enable
        ScalerSetBit(GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_128B132B(ucTemp), ~(_BIT7), 0x00);
#endif
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Rx2 Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2LoadNewStreamPayload(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2)) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(PE4_01_STHD_CTRL_1, ~_BIT7, 0x00);

        // Delay Up to 65537 Timeslots
        // 3.2ns per Timeslot for UHBR10
        // Delay Time  >=  65537 * 3.2ns = 210ns, as 500ns for Insurance Purposes
        DELAY_XUS(500);
        ScalerSetBit(PE4_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        ScalerSetBit(PC6_01_STHD_CTRL_1, ~_BIT7, 0x00);
        DELAY_5US();
        ScalerSetBit(PC6_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
}
#endif // #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DP Mst Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ConfigMstOrSstMode(void)
{
#if(_DP_MST_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT0) == _BIT0)
    {
        // MST to SST block Config MST Mode
        SET_DP_MAC_DPHY_RX2_MST2SST_BLOCK_MST_MODE();

        // Dp Phy Rx MST mode
        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        // MST to SST block Config SST Mode
        SET_DP_MAC_DPHY_RX2_MST2SST_BLOCK_SST_MODE();

        // Dp Phy Rx SST mode
        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);
    }

#if(_DP_MST_SUPPORT == _ON)
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }
#endif
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp2ResetProc(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRx2Hdcp2ResetProc_128b132b();
#endif
    ScalerDpMacDphyRx2Hdcp2ResetProc_8b10b();
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx2Hdcp2CipherDataRestore(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Check Power Status
        if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP20_MAC) == _POWER_CUT_OFF)
        {
            ScalerDpMacDphyRx2Hdcp2CipherDataRestore_128b132b();
        }
    }
    else
#endif
    {
        // Check Power Status
        if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP14_MAC) == _POWER_CUT_OFF)
        {
            ScalerDpMacDphyRx2Hdcp2CipherDataRestore_8b10b();
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Clear Restored Cipher Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ClrHdcp2CipherBackupInfo(void)
{
    // Clear HDCP2 Backup: Riv, AESCipher, Stream Type
    memset(g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxRiv, 0, sizeof(g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxRiv));
    memset(g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxAESCipher, 0, sizeof(g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxAESCipher));
    memset(g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType, 0, sizeof(g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType));
}

//--------------------------------------------------
// Description  : Detect Dp Rx HDCP Link Veriffication Pattern (0x531F)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpDetectLvp(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx2HdcpDetectLvp_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx2HdcpDetectLvp_8b10b();
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP2 Stream Type
// Input Value  : ucStreamId
// Output Value : Type Value
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRx2Hdcp2GetStxType(BYTE ucStreamId)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx2Hdcp2GetStxType_128b132b(ucStreamId);
    }
    else
#endif
    {
        return ScalerDpMacDphyRx2Hdcp2GetStxType_8b10b(ucStreamId);
    }
}
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check HDCP 1.4 Auth1 Process
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp14Sha1DataWrite(void)
{
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    // Enable write 32-bit data to SHA-1 block
    ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT0), _BIT0);

    // Polling 1ms for HDCP Sha Data Write Done
    if(ScalerTimerPollingFlagProc(1, PC5_30_SHA_CONTRL, _BIT5, _TRUE) == _TRUE)
    {
        ScalerSetBit(PC5_30_SHA_CONTRL, ~(_BIT5 | _BIT0), _BIT5);
    }
#else
    // Enable write 32-bit data to SHA-1 block
    ScalerSetBit(PC5_30_SHA_CONTRL, ~_BIT0, _BIT0);

    ScalerMcuDelayXus(1);
#endif
}

//--------------------------------------------------
// Description  : Check HDCP 1.4 Auth1 Process
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx2Hdcp14Auth1Check(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerGetBit(PC5_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)) &&
       ((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x05) != 0x00) ||
        (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x06) != 0x00)) &&
       ((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x29) & _DP_HDCP_BSTATUS_R0_AVAILABLE) == 0x00))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Load KSV FIFO to SHA-1 Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp14WriteShaInput(void)
{
    WORD usKsvFifoLength = 0;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    usKsvFifoLength = (WORD) ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A) * 5;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    SET_DP_MAC_DPHY_RX2_HDCP14_SHA_RESET();
    CLR_DP_MAC_DPHY_RX2_HDCP14_SHA_RESET();

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PC5_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PC5_32_SHA_DATA2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PC5_33_SHA_DATA3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PC5_34_SHA_DATA4, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PC5_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PC5_32_SHA_DATA2, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));
            ScalerSetByte(PC5_33_SHA_DATA3, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_0());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_1());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_2());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_3());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_4());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_5());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_6());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_7());
            ScalerSetByte(PC5_34_SHA_DATA4, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PC5_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PC5_32_SHA_DATA2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PC5_33_SHA_DATA3, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));
            ScalerSetByte(PC5_34_SHA_DATA4, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_0());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_1());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_2());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_3());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_4());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_5());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_6());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_7());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, 0x80);
            ScalerSetByte(PC5_32_SHA_DATA2, 0x00);
            ScalerSetByte(PC5_33_SHA_DATA3, 0x00);
            ScalerSetByte(PC5_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PC5_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PC5_32_SHA_DATA2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PC5_33_SHA_DATA3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PC5_34_SHA_DATA4, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_0());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_1());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_2());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_3());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_4());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_5());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_6());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_7());
            ScalerSetByte(PC5_32_SHA_DATA2, 0x80);
            ScalerSetByte(PC5_33_SHA_DATA3, 0x00);
            ScalerSetByte(PC5_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PC5_31_SHA_DATA1, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));
            ScalerSetByte(PC5_32_SHA_DATA2, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_0());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_1());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_2());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_3());
            ScalerSetByte(PC5_33_SHA_DATA3, GET_DP_MAC_DPHY_RX2_HDCP14_M0_4());
            ScalerSetByte(PC5_34_SHA_DATA4, GET_DP_MAC_DPHY_RX2_HDCP14_M0_5());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PC5_31_SHA_DATA1, GET_DP_MAC_DPHY_RX2_HDCP14_M0_6());
            ScalerSetByte(PC5_32_SHA_DATA2, GET_DP_MAC_DPHY_RX2_HDCP14_M0_7());
            ScalerSetByte(PC5_33_SHA_DATA3, 0x80);
            ScalerSetByte(PC5_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PC5_31_SHA_DATA1, 0x00);
        ScalerSetByte(PC5_32_SHA_DATA2, 0x00);
        ScalerSetByte(PC5_33_SHA_DATA3, 0x00);
        ScalerSetByte(PC5_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PC5_31_SHA_DATA1, 0x00);
            ScalerSetByte(PC5_32_SHA_DATA2, 0x00);
            ScalerSetByte(PC5_33_SHA_DATA3, 0x00);
            ScalerSetByte(PC5_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;
        }

        // The length of SHA-1 input is equal to 2^64(8 bytes)
        ScalerSetByte(PC5_31_SHA_DATA1, 0x00);
        ScalerSetByte(PC5_32_SHA_DATA2, 0x00);
        ScalerSetByte(PC5_33_SHA_DATA3, 0x00);
        ScalerSetByte(PC5_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PC5_31_SHA_DATA1, 0x00);
        ScalerSetByte(PC5_32_SHA_DATA2, 0x00);
        ScalerSetByte(PC5_33_SHA_DATA3, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PC5_34_SHA_DATA4, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();

        usKsvLengthTemp += 8;

        ScalerDpMacDphyRx2HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - Load SHA Result to DPCD table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp14LoadShaToDpcd(void)
{
    BYTE pucTemp[2];
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    ScalerDpAuxRxSetManualMode(enumInputPort);

    for(pucTemp[0] = 0; pucTemp[0] < 5; pucTemp[0]++)
    {
        for(pucTemp[1] = 0; pucTemp[1] < 4; pucTemp[1]++)
        {
            // DPCD [0x68014 ~ 0x68027]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, (0x14 + (pucTemp[0] * 4) + pucTemp[1]), ScalerGetByte(PC5_39_SHA_3 + (pucTemp[0] * 4) - pucTemp[1]));
        }
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp14FakeAuthenProc(void)
{
    BYTE pucSHAInput[64];
    BYTE ucTemp = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Set Device Count and Depth
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x2A, 0x01);
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x2B, 0x01);

    // Load KSV
    memcpy(pucSHAInput, g_pucSyncHdcpAksvBackup, 5);

    // Load Device Count and Depth
    pucSHAInput[5] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A);
    pucSHAInput[6] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B);

    // Load M0'
    pucSHAInput[7] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_0();
    pucSHAInput[8] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_1();
    pucSHAInput[9] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_2();
    pucSHAInput[10] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_3();
    pucSHAInput[11] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_4();
    pucSHAInput[12] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_5();
    pucSHAInput[13] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_6();
    pucSHAInput[14] = GET_DP_MAC_DPHY_RX2_HDCP14_M0_7();

    memset(&pucSHAInput[15], 0, 49);

    pucSHAInput[15] = 0x80;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    pucSHAInput[63] = 0x78;

    // Compute V'
    ScalerDpMacDphyRx2HDCPSha1Calculate(pucSHAInput, 0);

    // Write Ksv to DPCD table
    ScalerDpAuxRxSetManualMode(enumInputPort);

    for(ucTemp = 0; ucTemp < 15; ucTemp++)
    {
        if(ucTemp < 5)
        {
            // DPCD [0x6802C ~ 0x68030]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, (0x2C + ucTemp), g_pucSyncHdcpAksvBackup[ucTemp]);
        }
        else
        {
            // DPCD [0x68031 ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, (0x2C + ucTemp), 0x00);
        }
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);

    // Write V' to DPCD table
    ScalerDpMacDphyRx2Hdcp14LoadShaToDpcd();
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - SHA circuit Run
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2HDCPAuthShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    SET_DP_MAC_DPHY_RX2_HDCP14_SHA_FIRST_CALCULATE(bIsFirst);

    // Run SHA-1 Circuit
    SET_DP_MAC_DPHY_RX2_HDCP14_SHA_CALCULATE_ENABLE();

    ScalerTimerPollingFlagProc(5, PC5_30_SHA_CONTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    CLR_DP_MAC_DPHY_RX2_HDCP14_SHA_FIRST_CALCULATE();
}

//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckLvp(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx2HdcpCheckLvp_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx2HdcpCheckLvp_8b10b();
    }
}
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable Dp 8b10b Decoder Error WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Set8b10bDecErrorWD(bit bEn)
{
    // 8b10b Decoder Error WD Setting
    // _BIT3 set to 0 == Clear Flag 0x0B4A[7:4]
    ScalerSetBit(PC5_10_PHY_CH_FIFO_SYNC0, ~(_BIT5 | _BIT3), ((bEn == _ENABLE) ? (_BIT5 | _BIT3) : 0x00));
}

//--------------------------------------------------
// Description  : Check Dp 8b10b Dec Err Status
// Input Value  : None
// Output Value : _SUCCESS --> No Dec Err
//                _FAIL    --> Dec Err Occur
//--------------------------------------------------
bit ScalerDpMacDphyRx2Check8b10bDecErrorStatus(void)
{
    return ((ScalerGetBit(PC5_4A_DP_LANEX_ACCUMLATED_ERR_COUNT, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00) ? _SUCCESS : _FAIL);
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx2 Auxless ALPM Initial
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2AuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn)
{
    WORD usTdrlTime = 0;

    if(bEn == _ENABLE)
    {
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT7, _BIT7);

            // Enable ALPM mode
            ScalerSetBit(PD2_D7_FRAME_DETECT_ALPM_DP20_2, ~_BIT0, _BIT0);

            // Clear Sleep Pattern INT Flag
            ScalerSetBit(PD2_DC_ALPM_DETECT_DP20, ~_BIT4, _BIT4);

            // Enable Sleep Pattern INT
            ScalerSetBit(PD2_DC_ALPM_DETECT_DP20, ~(_BIT4 | _BIT3), _BIT3);
        }
        else
#endif
        {
            ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT7, 0x00);

            // Clear Sleep Pattern INT Flag
            ScalerSetBit(PC5_4C_ALPM_SLEEP_0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Enable Sleep Pattern Detect and INT
            ScalerSetBit(PC5_4C_ALPM_SLEEP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));
        }

        // Mac LFPS Wake Use DPHY lfps_cnt_vld
        ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT5, 0x00);

        if((ScalerGetBit(PC5_03_LANE_MUX, (_BIT1 | _BIT0)) == _DP_LANE_0) ||
           (ScalerGetBit(PC5_03_LANE_MUX, (_BIT1 | _BIT0)) == _DP_LANE_1))
        {
            // ALPM LFPS Detection Select Lane0
            ScalerSetBit(PC5_BE_ALPM_UFP_14, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            // ALPM LFPS Detection Select Lane2
            ScalerSetBit(PC5_BE_ALPM_UFP_14, ~(_BIT7 | _BIT6), _BIT7);
        }

        // Toggle Reset UFP ALPM FSM
        ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT6, _BIT6);
        ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT6, 0x00);

        // 00116h[3] = 1 => There are no LTTPRs Between DPTx and DPRx
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x16, _BIT3) == _BIT3)
        {
            // lfps_cnt_vld = 0 => tsilence(80~180ns) + t1(50us) => Normal Data
            // eq_start_time = 0xFF => 255/108Mhz = 2.36us
            ScalerSetByte(PC5_B3_ALPM_UFP_03, 0xFF);

            // noisy_area_start_time = tsilence(80~180ns) + 40us = ~40.13us => 40.13us * 108Mhz = 4334 = 0x10EE
            ScalerSetBit(PC5_B4_ALPM_UFP_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
            ScalerSetByte(PC5_B8_ALPM_UFP_08, 0xEE);

            // cds_start_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PC5_B7_ALPM_UFP_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PC5_BB_ALPM_UFP_11, 0x1C);

            // normal_start_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PC5_C0_ALPM_UFP_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PC5_C1_ALPM_UFP_16, 0x1C);

            // start_tps2_err_time = 15us => 15us * 108Mhz = 1620 = 0x654
            ScalerSetBit(PC5_B5_ALPM_UFP_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
            ScalerSetByte(PC5_B9_ALPM_UFP_09, 0x54);

            // retrain_sleep_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PC5_B6_ALPM_UFP_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PC5_BA_ALPM_UFP_10, 0x1C);
        }
        else
        {
            // lfps_cnt_vld = 0 => tsilence(80~180ns) + t1(50us) + tDRL => Normal Data
            // eq_start_time = 0xFF => 255/108Mhz = 2.36us
            ScalerSetByte(PC5_B3_ALPM_UFP_03, 0xFF);

            // noisy_area_start_time = tsilence(80~180ns) + 40us = ~40.13us => 40.13us * 108Mhz = 4334 = 0x10EE
            ScalerSetBit(PC5_B4_ALPM_UFP_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
            ScalerSetByte(PC5_B8_ALPM_UFP_08, 0xEE);

            // cds_start_time = 10us => 10us * 108Mhz = 1080 = 0x438
            ScalerSetBit(PC5_B7_ALPM_UFP_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
            ScalerSetByte(PC5_BB_ALPM_UFP_11, 0x38);

            usTdrlTime = ScalerDpMacDphyRxAuxlessAlpmTdrlTime(enumInputPort);

            // normal_start_time = tDRL =>  tDRL * 108Mhz
            ScalerSetBit(PC5_C0_ALPM_UFP_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usTdrlTime >> 8));
            ScalerSetByte(PC5_C1_ALPM_UFP_16, usTdrlTime);

            // start_tps2_err_time = 15us => 15us * 108Mhz = 1620 = 0x654
            ScalerSetBit(PC5_B5_ALPM_UFP_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
            ScalerSetByte(PC5_B9_ALPM_UFP_09, 0x54);

            // retrain_sleep_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PC5_B6_ALPM_UFP_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PC5_BA_ALPM_UFP_10, 0x1C);
        }
    }
    else
    {
        // alpm_wake_reset = 1'b1
        ScalerSetBit(PC5_B0_ALPM_UFP_00, ~_BIT6, _BIT6);

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Disable ALPM mode
        ScalerSetBit(PD2_D7_FRAME_DETECT_ALPM_DP20_2, ~_BIT0, 0x00);

        // Disable Sleep Pattern INT
        ScalerSetBit(PD2_DC_ALPM_DETECT_DP20, ~(_BIT4 | _BIT3), 0x00);
#endif
        // Disable Sleep Pattern Detect and IRQ
        ScalerSetBit(PC5_4C_ALPM_SLEEP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2CpIRQ_8b10b(EnumDpRxBStatusType enumBStatusType)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

            // Check for HDCP Block work in 1.4
            if(ScalerDpMacDphyRx2HdcpReAuthStatusCheck() == _TRUE)
            {
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
                if(ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _FALSE)
                {
                    // Reset HDCP Block
                    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
                }

                if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT1) == _BIT1)
                {
                    ScalerDpAuxRxSetDpcdWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x05, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x20, 0x05) | _BIT2));
                }
#else
                // Reset HDCP Block
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
#endif

                // Reset HDCP 1.4 Aksv DPCD
                ScalerDpHdcp14RxResetDpcd(enumInputPort, _DP_RX_HDCP_REAUTH);

                // Set B Status
                ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x29, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x29) | enumBStatusType));
            }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            else
            {
                // Disable HDCP 2.2 Module
                ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_14);

                // Disable HDCP2.2 Auth. Done
                ScalerSetBit(PC5_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                // Reset HDCP 2.2 Riv DPCD
                ScalerDpHdcp2RxResetDpcd(enumInputPort, _DP_RX_HDCP_REAUTH);

                ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | _BIT4));

                // Clear Authentication Done Flag
                ScalerDpHdcp2ClrAuthenticationDone(enumInputPort);
            }
#endif
            break;

        case _DP_HDCP_BSTATUS_REAUTH_REQ:

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
            if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT1) == _BIT1)
            {
                ScalerDpAuxRxSetDpcdWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x05, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x20, 0x05) | _BIT2));
            }
#endif

            // Reset HDCP 1.4 Aksv DPCD
            ScalerDpHdcp14RxResetDpcd(enumInputPort, _DP_RX_HDCP_REAUTH);

            // Set B Status Link Integrity Fail CPIRQ
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x29, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x29) | _BIT2));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_RXSTATUS_REAUTH_REQ:

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | _BIT3));

            break;
#endif

        case _DP_HDCP_BSTATUS_V_READY:
        case _DP_HDCP_BSTATUS_R0_AVAILABLE:

            // Set B Status
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x29, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x29) | enumBStatusType));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        case _DP_HDCP2_V_READY:

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | (enumBStatusType >> 6)));

            break;
#endif

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, _BIT2);

    ScalerDpAuxRxHpdIrqAssert(enumInputPort);
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckEnabled_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14)
    {
        if(ScalerGetBit(PC5_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
        {
            if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x07) != 0x00) ||
               (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x08) != 0x00) ||
               (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x09) != 0x00) ||
               (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x0A) != 0x00) ||
               (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x0B) != 0x00))
            {
                return _TRUE;
            }
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PC5_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckValid_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14)
    {
        if(ScalerGetBit(PC5_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PC5_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            if((ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheck_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Check for HDCP 1.4 Aksv
    if(ScalerDpMacDphyRx2HdcpReAuthStatusCheck() == _FALSE)
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Check for HDCP 2.2 Riv
        if(ScalerDpMacDphyRx2Hdcp2ReAuthStatusCheck() == _FALSE)
#endif
        {
            return _TRUE;
        }
    }

    if(((ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    // Check for HDCP Block work in 1.4
    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14)
    {
        if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT2) == 0x00)
        {
            return _FALSE;
        }

        if(ScalerDpMacStreamRxHdcpMeasureCheck(enumInputPort) == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect Dp Rx HDCP Link Veriffication Pattern (0x531F)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpDetectLvp_8b10b(void)
{
    if((ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp2ResetProc_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Disable HDCP2.2 Auth. Done
    ScalerSetBit(PC5_20_HDCP_DEBUG, ~_BIT4, 0x00);

    // Clear Type Value
    ScalerSetByte(PC5_93_HDCP_TYPE_AES_0, 0x00);

    // Clear Type Value
    ScalerSetByte(PC5_94_HDCP_TYPE_AES_1, 0x01);

#if(_DP_MST_SUPPORT == _ON)
    // For MST mode
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        // Clear AES STx Type
        ScalerSetBit(PC5_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    }
    else
#endif
    {
        // Clear AES STx Type
        ScalerSetBit(PC5_95_HDCP_ST_TYPE, ~_BIT7, 0x00);
    }

    // Reset HDCP Block
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    // Disable HDCP2.2
    ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_14);
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacDphyRx2Hdcp2CipherDataRestore_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);
    BYTE ucLoop = 0x00;

    ScalerDpAuxRxSetManualMode(enumInputPort);

    if(ScalerDpHdcpRxGetAuthDone(enumInputPort) == _TRUE)
    {
        // Reset HDCP2.2 Auth. Done
        ScalerSetBit(PC5_20_HDCP_DEBUG, ~_BIT4, 0x00);

        // Recover HDCP MAC2 for HDCP 2.2 Mode
        ScalerSetBit(PC5_1A_HDCP_IRQ, ~_BIT1, _BIT1);

        for(ucLoop = 0; ucLoop < 8; ucLoop++)
        {
            ScalerSetByte((PC5_55_RIV0 + ucLoop), g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxRiv[ucLoop]);
        }

        for(ucLoop = 0; ucLoop < 16; ucLoop++)
        {
            ScalerSetByte((PC5_81_HDCP_AES_CIPHER_KEY_15 + ucLoop), g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxAESCipher[ucLoop]);
        }

#if(_DP_MST_SUPPORT == _ON)
        // For MST mode
        if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
        {
            // Set Stream 1~ Stream 5 Type
            ScalerSetBit(PC5_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType[0] & 0xF8);

            // Set Stream 6 Type
            ScalerSetBit(PC5_96_DUMMY3, ~_BIT7, g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType[1] & 0x80);
        }
        else
#endif
        {
            // Set Stream 1
            ScalerSetBit(PC5_95_HDCP_ST_TYPE, ~_BIT7, g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType[0] & 0x80);
        }

        // Enable HDCP2.2 Auth. Done
        ScalerSetBit(PC5_20_HDCP_DEBUG, ~_BIT4, _BIT4);

        DebugMessageHDCP2("[D2]Recover Hdcp2 Cipher Data", 0);
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP2 Stream Type
// Input Value  : ucStreamId
// Output Value : Type Value
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRx2Hdcp2GetStxType_8b10b(BYTE ucStreamId)
{
    return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)ScalerGetBit(PC5_95_HDCP_ST_TYPE, (_BIT7 >> (ucStreamId))));
}
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckLvp_8b10b(void)
{
    if(((ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP MAC Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Reset(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2)) == _CODING_TYPE_128B132B)
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PD2_F7_DESKEW_PHY, ~(_BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit(PD2_F7_DESKEW_PHY, ~(_BIT6 | _BIT4 | _BIT1), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
        ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

        // Delay for Lane Alignment after Mac Reset
        ScalerTimerDelayXms(2);
    }
    else
#endif
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PC5_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit(PC5_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // Delay for Lane Alignment after Mac Reset
        ScalerTimerDelayXms(2);

        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
        {
            // [4] Disable Comma Detection
            ScalerSetBit(PC5_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
        }
    }

#if(_HW_DP_MAC_DPHY_CTS_FIFO_SUPPORT == _ON)
    // Cts Fifo Must Be Reset After Link Clk Stable, Until DPF Enable
    ScalerDpRxMacDphyCtsFifoReset(enumInputPort);
#endif

    // Mac Secondary Data Block Reset
    ScalerDpMacStreamRxSecDataReset(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpMacDphyRx2MarginLinkCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
    {
        case _DP_LINK_HBR3:
        case _DP_LINK_HBR2:

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
            if((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) &&
               (ScalerDpMacDphyRx2SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               (ScalerDpMacDphyRx2LaneBsCheck() == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeErrorCountCheck(_DP_MARGIN_LINK_TIME_CRITERIA, _DP_MARGIN_LINK_ERROR_CRITERIA) == _FALSE))
            {
                // To Avoid Margin Link Trigger by No Signal
                if((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) &&
                   (ScalerDpMacDphyRx2SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
                   (ScalerDpMacDphyRx2LaneBsCheck() == _TRUE))
                {
                    if(ScalerDpRxCableStatus(enumInputPort) == _TRUE)
                    {
                        ScalerDpRxSetMarginLink(enumInputPort);
                        return _FALSE;
                    }
                }
            }
#else
            return _TRUE;
#endif
            break;

        default:

            break;
    }

    return _TRUE;
}

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check 8b10b Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2DecodeErrorCountCheck(WORD usTimeCriteria, WORD usErrorCriteria)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpMacDphyRx2DecodeErrorCountReset(_DP_MAC_DECODE_METHOD_8B10B) == _FALSE)
    {
        return _TRUE;
    }

    ScalerTimerDelayXms(usTimeCriteria);

    switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_0) == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_0) == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_1) == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_2) == _TRUE) &&
               (ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

    DebugMessageDpRx("7. DP MAC RX2: Error Count Fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : Check Lane BS
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpMacDphyRx2LaneBsCheck(void)
{
    // Detect Enable
    ScalerSetBit(PC5_00_HD_DP_SEL, ~(_BIT3 | _BIT0), 0x00);
    ScalerSetBit(PC5_00_HD_DP_SEL, ~(_BIT3 | _BIT0), _BIT3);

    // Delay for 8192 x 10 x 8 x 2 / 1.62G = 809us
    DELAY_XUS(850);

    // Check Lane Bs
    if(ScalerGetBit(PC5_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Lane Valid
// Input Value  : None
// Output Value : True --> ok, False --> Lane Valid Error
//--------------------------------------------------
bit ScalerDpMacDphyRx2LaneValidCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Enable Lane Valid Detect
    ScalerSetBit(PC5_00_HD_DP_SEL, ~(_BIT3 | _BIT0), 0x00);
    ScalerSetBit(PC5_00_HD_DP_SEL, ~(_BIT3 | _BIT0), _BIT3);

    // Delay Time us [150,x]
    DELAY_XUS(150);

    switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

            if(ScalerGetBit(PC5_00_HD_DP_SEL, _BIT7) == 0x00)
            {
                return _FALSE;
            }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
            if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                return _FALSE;
            }
#endif

            break;

        case _DP_TWO_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

            if(ScalerGetBit(PC5_00_HD_DP_SEL, (_BIT7 | _BIT6)) == 0x00)
            {
                return _FALSE;
            }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)

            if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT7) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT6) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT5) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3) && (ScalerGetBit(PC5_00_HD_DP_SEL, _BIT4) == 0x00)))
                {
                    return _FALSE;
                }
            }
#endif

            break;

        case _DP_FOUR_LANE:

            if(ScalerGetBit(PC5_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Check Valid Video Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ValidSignalDetection(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLaneCount = _DP_FOUR_LANE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

#if(_DP_MST_SUPPORT == _ON)

    if(g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup == _TRUE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);

        if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) != _BIT1))
        {
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x00, g_stDpMacDphyRx2MiscInfo.ucDpMacRxLinkRateBackup);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x01, ((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x60) | (g_stDpMacDphyRx2MiscInfo.ucDpMacRxLaneCountBackup | _BIT7)));

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x20, g_stDpMacDphyRx2MiscInfo.ucDpMacRxFecReadyBackup);
#endif

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x08, g_stDpMacDphyRx2MiscInfo.ucDpMacRxCodingTypeBackup);

            if(g_stDpMacDphyRx2MiscInfo.ucDpMacRxCodingTypeBackup == _CODING_TYPE_128B132B)
            {
                ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_128B132B);
            }
            else
            {
                ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_8B10B);
            }
#endif

            if(g_stDpMacDphyRx2MiscInfo.ucDpMacRxLaneCountBackup == _DP_FOUR_LANE)
            {
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x77);
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x77);
            }
            else if(g_stDpMacDphyRx2MiscInfo.ucDpMacRxLaneCountBackup == _DP_TWO_LANE)
            {
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x77);
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x00);
            }
            else
            {
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x07);
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x00);
            }

            ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x04, 0x01);

            ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_FAKE_LINK_TRAINING_PASS_VBIOS);

            ScalerDpMacDphyRx2MstInfoBackup(_DP_MST_BACKUP_INFO_RESTORE);
        }

        ScalerDpAuxRxSetAutoMode(enumInputPort);

        DebugMessageDpRx("DP MAC RX2: VBIOS_Link_Rate_MST", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00));
        DebugMessageDpRx("DP MAC RX2: VBIOS_Lane_Count_MST", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01));
    }
    else
#endif // End of #if(_DP_MST_SUPPORT == _ON)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
        if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
        if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00))
#endif
        {
            ucDpLinkRate = ScalerDpMacDphyRx2LinkRateDetect();

            ScalerDpAuxRxSetAutoMode(enumInputPort);

            if(ucDpLinkRate == _DP_LINK_NONE)
            {
                return;
            }

            do
            {
                ScalerDpAuxRxSetManualMode(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00) &&
                   (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00))
#endif
                {
                    ScalerDpPhyRxRebuildPhy(enumInputPort, (EnumDpLinkRate)ucDpLinkRate, (ucDpLaneCount | _BIT7));

#if(_DP_RX_FEC_SUPPORT == _ON)
                    // Enable FEC Seq Weak mode
                    ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, _BIT2);

                    ScalerDpMacDphyRx2FecDecode(_ENABLE);
#endif
                    ScalerDpAuxRxSetAutoMode(enumInputPort);

                    if(ScalerDpMacDphyRx2VbiosMsaCheck(_FALSE) == _TRUE)
                    {
                        break;
                    }
                    else
                    {
                        if(ScalerDpMacDphyRx2VbiosMsaCheck(_TRUE) == _TRUE)
                        {
                            break;
                        }
                    }

                    if(ucDpLaneCount == _DP_FOUR_LANE)
                    {
                        ucDpLaneCount = _DP_TWO_LANE;
                    }
                    else if(ucDpLaneCount == _DP_TWO_LANE)
                    {
                        ucDpLaneCount = _DP_ONE_LANE;
                    }
                    else if(ucDpLaneCount == _DP_ONE_LANE)
                    {
                        ucDpLaneCount = 0x00;
                    }
                }
                else
                {
                    ScalerDpAuxRxSetAutoMode(enumInputPort);

#if(_DP_RX_FEC_SUPPORT == _ON)
                    // Disable FEC Seq Weak mode
                    ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
                    return;
                }
            }
            while((ucDpLaneCount == _DP_TWO_LANE) || (ucDpLaneCount == _DP_ONE_LANE));

#if(_DP_RX_FEC_SUPPORT == _ON)
            // Disable FEC Seq Weak mode
            ScalerSetBit(PC5_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
            if(ucDpLaneCount != 0x00)
            {
                ScalerDpAuxRxSetManualMode(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00) &&
                   (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00))
#endif
                {
                    ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x00, ucDpLinkRate);
                    ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x01, ((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x60) | (ucDpLaneCount | _BIT7)));

                    ScalerDpAuxRxSetLinkRate(enumInputPort, ucDpLinkRate);
                    ScalerDpAuxRxSetLaneCount(enumInputPort, ucDpLaneCount);

#if(_DP_RX_FEC_SUPPORT == _ON)
                    if(ScalerDpMacDphyRx2FecDecodeCheck() == _TRUE)
                    {
                        ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x20, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ScalerDpMacDphyRx2FecDecode(_DISABLE);
                    }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDpMacDscRxDscStreamCheck(ScalerDpRxGetMacSwitch(enumInputPort)) == _TRUE)
                    {
                        ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x60, ~_BIT0, _BIT0);
                    }
#endif

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x08, _CODING_TYPE_8B10B);
                    ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_8B10B);
#endif

                    if(ucDpLaneCount == _DP_FOUR_LANE)
                    {
                        ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x77);
                        ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x77);
                    }
                    else if(ucDpLaneCount == _DP_TWO_LANE)
                    {
                        ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x77);
                        ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x00);
                    }
                    else
                    {
                        ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x07);
                        ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x00);
                    }

                    ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x04, 0x01);

                    ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_FAKE_LINK_TRAINING_PASS_VBIOS);
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }
        }

        ScalerDpAuxRxSetAutoMode(enumInputPort);

        DebugMessageDpRx("DP MAC RX2: VBIOS_Link_Rate", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00));
        DebugMessageDpRx("DP MAC RX2: VBIOS_Lane_Count", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01));
    }
}

//--------------------------------------------------
// Description : DP Link Rate Detect
// Input Value  : None
// Output Value : Link Rate
//--------------------------------------------------
BYTE ScalerDpMacDphyRx2LinkRateDetect(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLinkRateDecide = _DP_LINK_NONE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    do
    {
        if(ucDpLinkRate == 0)
        {
            if(_HW_DP_D2_MAX_LINK_RATE_SUPPORT > ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x00, 0x01))
            {
                if(_HW_DP_D2_MAX_LINK_RATE_SUPPORT > _DP_LINK_HBR3)
                {
                    ucDpLinkRate = _DP_LINK_HBR3;
                }
                else
                {
                    ucDpLinkRate = _HW_DP_D2_MAX_LINK_RATE_SUPPORT;
                }
            }
            else
            {
                ucDpLinkRate = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x00, 0x01);
            }
        }
        else if(ucDpLinkRate == _DP_LINK_HBR3)
        {
            ucDpLinkRate = _DP_LINK_HBR2;
        }
        else if(ucDpLinkRate == _DP_LINK_HBR2)
        {
            ucDpLinkRate = _DP_LINK_HBR;
        }
        else if(ucDpLinkRate == _DP_LINK_HBR)
        {
            ucDpLinkRate = _DP_LINK_RBR;
        }

        if(ScalerDpMacDphyRx2LinkRateCheck(ucDpLinkRate) == _TRUE)
        {
            ucDpLinkRateDecide = ucDpLinkRate;

            break;
        }
    }
    while(ucDpLinkRate != _DP_LINK_RBR);

    return ucDpLinkRateDecide;
}

//--------------------------------------------------
// Description : Check Valid Lane
// Input Value  : ucDpLinkRate -> DP Link Rate
// Output Value : _TRUE -> Valid Signal
//--------------------------------------------------
bit ScalerDpMacDphyRx2LinkRateCheck(BYTE ucDpLinkRate)
{
    WORD usDataStreamL0 = 0;
    BYTE ucDpLEQScanValue = _DP_RX_RELOAD_LEQ_INITIAL;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    do
    {
        if(ucDpLEQScanValue == _DP_RX_RELOAD_LEQ_INITIAL)
        {
            ucDpLEQScanValue = _DP_RX_RELOAD_LEQ_LARGE;
        }
        else if(ucDpLEQScanValue == _DP_RX_RELOAD_LEQ_LARGE)
        {
            ucDpLEQScanValue = _DP_RX_RELOAD_LEQ_DEFAULT;
        }

        ScalerDpPhyRxSignalDetectInitial(enumInputPort, ucDpLinkRate, ucDpLEQScanValue);

        usDataStreamL0 = ScalerDpMacDphyRx2SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR3_9G:

                usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR3_9G_SAVED;
                usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR3_9G_SAVED;

                break;

            case _DP_LINK_HBR3:

                usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR3_SAVED;
                usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR3_SAVED;

                break;

            case _DP_LINK_HBR2:

                usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED;
                usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED;

                break;

            case _DP_LINK_HBR:

                usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED;
                usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED;

                break;

            case _DP_LINK_RBR:

                usMeasureUpperBound = _DP_RX_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED;
                usMeasureLowerBound = _DP_RX_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED;

                break;

            default:

                break;
        }

        if((usDataStreamL0 < usMeasureUpperBound) && (usDataStreamL0 > usMeasureLowerBound))
        {
            return _TRUE;
        }
    }
    while(ucDpLEQScanValue != _DP_RX_RELOAD_LEQ_DEFAULT);

    return _FALSE;
}

//--------------------------------------------------
// Description  : VBIOS ASSR Detect
// Input Value  : bMSACheckResult
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx2VbiosAssrCheck(bit bMSACheckResult)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    ScalerDpAuxRxSetManualMode(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
    if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
       (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00) &&
       (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
    if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
       (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00))
#endif
    {
        if(bMSACheckResult == _TRUE)
        {
            if(ScalerGetBit(PC5_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
            {
                ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x0A, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x0A, ~_BIT0, 0x00);
            }
        }
        else
        {
            // Set Scramble Seed = Default 0xFFFF
            ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

            ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x0A, ~_BIT0, 0x00);
        }
    }
    else
    {
        bMSACheckResult = _FALSE;
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);

    return bMSACheckResult;
}

//--------------------------------------------------
// Description  : DP ASSR Mode On/ Off
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2ASSRModeSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x0A) & _BIT0) == _BIT0)
    {
        // Scramble seed equal to 0xFFFE
        ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Scramble seed equal to 0xFFFF
        ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Change Dp Scramble Seed
// Input Value  : None
// Output Value : False --> Change Scrmable Seed Finish
//--------------------------------------------------
bit ScalerDpMacDphyRx2ChangeSrambleSeed(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerDpAuxRxGetAssrModeEnable(enumInputPort) == _TRUE) && (ScalerGetBit(PC5_07_SCRAMBLE_CTRL, _BIT4) == 0x00))
    {
        // Try Scramble Seed = 0xFFFE
        ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description : check DP CDR locked or unlocked
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpMacDphyRx2MeasureLaneCDRClk(EnumDpLinkRate enumDpLinkRate, BYTE ucDpMacRx2LaneNumber)
{
    WORD usCDRClockCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    switch(enumDpLinkRate)
    {
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _DP_LINK_UHBR20:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_UHBR20_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_UHBR20_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_UHBR13_5:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_UHBR10:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_UHBR10_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_UHBR10_SAVED >> 4))
            {
                return _TRUE;
            }

            break;
#endif
        case _DP_LINK_HBR3_9G:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR3:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR3_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR3_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR2:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR2_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR2_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_RBR_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_RBR_SAVED >> 4))
            {
                return _TRUE;
            }

            break;
    }

    usCDRClockCount = ScalerDpMacDphyRx2SignalDetectMeasureCount(ucDpMacRx2LaneNumber, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_1000_CYCLE);

    if(usCDRClockCount == 0)
    {
        return _FALSE;
    }

    if(abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) - usCDRClockCount) > (ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx2LaneNumber) >> 7))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheck(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx2HdcpCheck_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx2HdcpCheck_8b10b();
    }
}

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate SHA-1 Input
// Input Value  : Inpute Array, First Run
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Reset SHA Block counter
    SET_DP_MAC_DPHY_RX2_HDCP14_SHA_RESET();
    CLR_DP_MAC_DPHY_RX2_HDCP14_SHA_RESET();

    // Write SHA-1 Input Data, Total 512 bits
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte(PC5_31_SHA_DATA1, pucInputArray[ucLoopIndex * 4]);
        ScalerSetByte(PC5_32_SHA_DATA2, pucInputArray[1 + ucLoopIndex * 4]);
        ScalerSetByte(PC5_33_SHA_DATA3, pucInputArray[2 + ucLoopIndex * 4]);
        ScalerSetByte(PC5_34_SHA_DATA4, pucInputArray[3 + ucLoopIndex * 4]);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx2Hdcp14Sha1DataWrite();
    }

    ScalerDpMacDphyRx2HDCPAuthShaRun(((ucCalCount == 0x00) ? _TRUE : _FALSE));
}
#endif

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx2LaneSwapSelect_8b10b(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_RTD_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_RTD)
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
#else
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED)
#endif
    {
        // Main-Link Lane Setting Start
        if(ScalerTypeCRxGetPinAssignment(enumInputPort) != _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Pin Assignment C/D PN Swap
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);
        }
        else
        {
            // Pin Assignment E PN Swap
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
            ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);
        }

        switch(ScalerTypeCRxGetPinAssignment(enumInputPort))
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                    ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
                }

                break;

            default:
            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                // DP Lane Swap Setting
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));

                break;
        }
    }
    else if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_RTS) || (ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_USER))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if((ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
            }
        }
        else
        {
            if((ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
            }
        }
    }
    else
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    {
        // DP PN Swap Setting
        ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
        ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
        ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
        ScalerSetBit(PC5_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

        // DP Lane Swap Setting
        ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
        ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
        ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
        ScalerSetBit(PC5_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
    }

    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_3, ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_2, ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_1, ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_0, ScalerGetBit(PC5_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_3, (ScalerGetBit(PC5_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_2, (ScalerGetBit(PC5_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_1, (ScalerGetBit(PC5_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_0, (ScalerGetBit(PC5_03_LANE_MUX, (_BIT1 | _BIT0))));

    if((ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) != _TRUE) && (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) != _BIT7))
    {
        ucClockLaneSelect = (ScalerGetBit(PC5_03_LANE_MUX, (_BIT1 | _BIT0)) << 6);
    }

    // MAC Clock from PHY Lane Selection
    ScalerSetBit(PC5_02_PHY_DIG_RESET2_CTRL, ~(_BIT7 | _BIT6), ucClockLaneSelect);
}

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2CheckHdcpCpirqStatus_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerGetByte(PC5_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PC5_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x02, 0x01) & _BIT2) == _BIT2)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22 decode
            if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
            {
                if(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, 0x00);
                }
            }
            else
#endif
            {
                if(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x29) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, 0x00);
                }
            }
        }
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2MstInfoBackup(EnumDpMstBackup enumDpMstBackup)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    switch(enumDpMstBackup)
    {
        case _DP_MST_BACKUP_INFO:

            if((ScalerGetBit(PC5_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
               (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS))
            {
                // Backup MST Enable
                g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup = _TRUE;

                // Backup Link Config
                g_stDpMacDphyRx2MiscInfo.ucDpMacRxLinkRateBackup = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00);
                g_stDpMacDphyRx2MiscInfo.ucDpMacRxLaneCountBackup = (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F);
                g_stDpMacDphyRx2MiscInfo.ucDpMacRxCodingTypeBackup = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x08);

#if(_DP_RX_FEC_SUPPORT == _ON)
                g_stDpMacDphyRx2MiscInfo.ucDpMacRxFecReadyBackup = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x20);
#endif

                // Backup TimeSlot Info
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
                {
                    memcpy(g_pucDpMacDphyRx2MstTimeSlotBackup, (volatile BYTE xdata *)PE4_02_STHD_CTRL_2, sizeof(g_pucDpMacDphyRx2MstTimeSlotBackup));
                }
                else
#endif
                {
                    memcpy(g_pucDpMacDphyRx2MstTimeSlotBackup, (volatile BYTE xdata *)PC6_02_STHD_CTRL_2, sizeof(g_pucDpMacDphyRx2MstTimeSlotBackup));
                }

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
                {
                    g_pucDpMacDphyRx2MstStMuxBackup[enumSourceNum] = GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum);
                }
            }

            break;

        case _DP_MST_BACKUP_INFO_RESTORE:

            if(((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x00, 0x21) & _BIT0) == _BIT0) && (g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup == _TRUE))
            {
                // Enable MST Decode
                ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);

                // Restore TimeSlot Info
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
                {
                    memcpy((volatile BYTE xdata *)PE4_02_STHD_CTRL_2, g_pucDpMacDphyRx2MstTimeSlotBackup, sizeof(g_pucDpMacDphyRx2MstTimeSlotBackup));
                }
                else
#endif
                {
                    memcpy((volatile BYTE xdata *)PC6_02_STHD_CTRL_2, g_pucDpMacDphyRx2MstTimeSlotBackup, sizeof(g_pucDpMacDphyRx2MstTimeSlotBackup));
                }

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
                {
                    ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumSourceNum, g_pucDpMacDphyRx2MstStMuxBackup[enumSourceNum]);
                }
            }

            g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;

        case _DP_MST_BACKUP_INFO_RESET:
        default:

            g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
    }
}
#endif

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacDphyRx2PowerDataRecover_128b132b(void)
{
    // Enable DP Link Integrity Enable
    ScalerSetBit(PD2_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT5, _BIT5);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Set Type Value = 1 for AES 1
    ScalerSetByte(PD2_29_HDCP_TYPE_AES_1, 0x01);
#endif
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheck_128b132b(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Check for HDCP 2.2 Riv
    if(ScalerDpMacDphyRx2Hdcp2ReAuthStatusCheck() == _FALSE)
    {
        return _TRUE;
    }
#endif

    if(((ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request in DP2.0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2CpIRQ_128b132b(EnumDpRxBStatusType enumBStatusType)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Disable HDCP 2.2 Module
            ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_22);

            // Disable HDCP2.2 Auth. Done
            ScalerSetBit(PD2_07_HDCP_DEBUG, ~_BIT0, 0x00);

            // Reset HDCP Block
            ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, _BIT0);
            ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, 0x00);

            // Reset HDCP 2.2 Riv DPCD
            ScalerDpHdcp2RxResetDpcd(enumInputPort, _DP_RX_HDCP_REAUTH);

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | _BIT4));

            // Clear Authentication Done Flag
            ScalerDpHdcp2ClrAuthenticationDone(enumInputPort);
#endif
            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_RXSTATUS_REAUTH_REQ:

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | _BIT3));

            break;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        case _DP_HDCP2_V_READY:

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) | (enumBStatusType >> 6)));

            break;
#endif

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, _BIT2);

    ScalerDpAuxRxHpdIrqAssert(enumInputPort);
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled in DP2.0
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckEnabled_128b132b(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(ScalerGetBit(PD2_07_HDCP_DEBUG, _BIT0) == _BIT0)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid in DP2.0
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckValid_128b132b(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(ScalerGetBit(PD2_07_HDCP_DEBUG, _BIT0) == _BIT0)
    {
        if((ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2Hdcp2ResetProc_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    // Disable HDCP2.2 Auth. Done
    ScalerSetBit(PD2_07_HDCP_DEBUG, ~_BIT0, 0x00);

    // Clear Type Value
    ScalerSetByte(PD2_28_HDCP_TYPE_AES_0, 0x00);

    // Clear Type Value
    ScalerSetByte(PD2_29_HDCP_TYPE_AES_1, 0x01);

    // Clear AES STx Type
    ScalerSetByte(PD2_2B_HDCP_ST_TYPE_0, 0x00);
    ScalerSetBit(PD2_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Reset HDCP Block
    ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, _BIT0);
    ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, 0x00);

    // Disable HDCP2.2
    ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_22);
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacDphyRx2Hdcp2CipherDataRestore_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);
    BYTE ucLoop = 0x00;

    ScalerDpAuxRxSetManualMode(enumInputPort);

    if(ScalerDpHdcpRxGetAuthDone(enumInputPort) == _TRUE)
    {
        // Reset HDCP2.2 Auth. Done
        ScalerSetBit(PD2_07_HDCP_DEBUG, ~_BIT0, 0x00);

        for(ucLoop = 0; ucLoop < 8; ucLoop++)
        {
            ScalerSetByte((PD2_08_RIV0 + ucLoop), g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxRiv[ucLoop]);
        }

        for(ucLoop = 0; ucLoop < 16; ucLoop++)
        {
            ScalerSetByte((PD2_18_HDCP_AES_CIPHER_KEY_15 + ucLoop), g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxAESCipher[ucLoop]);
        }

        // Set Stream 1~ Stream 2 Type
        ScalerSetBit(PD2_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType[0] & 0xF0);

        // Set Stream 3~ Stream 6 Type
        ScalerSetByte(PD2_2B_HDCP_ST_TYPE_0, g_stDpMacDphyRx2HdcpCipherBackupInfo.pucDpMacRxSTType[1]);

        // Enable HDCP2.2 Auth. Done
        ScalerSetBit(PD2_07_HDCP_DEBUG, ~_BIT0, _BIT0);

        DebugMessageHDCP2("[D2]Recover Hdcp2 Cipher Data", 0);
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);
}

//--------------------------------------------------
// Description  : Detect Dp Rx HDCP Link Veriffication Pattern (0x531F)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpDetectLvp_128b132b(void)
{
    if((ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP2 Stream Type
// Input Value  : ucStreamId
// Output Value : Type Value
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRx2Hdcp2GetStxType_128b132b(BYTE ucStreamId)
{
    switch(ucStreamId)
    {
        case _DP_ST_SOURCE1:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(PD2_2C_HDCP_ST_TYPE_1, (_BIT7 | _BIT6)) >> 6));

        case _DP_ST_SOURCE2:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(PD2_2C_HDCP_ST_TYPE_1, (_BIT5 | _BIT4)) >> 4));

        case _DP_ST_SOURCE3:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(PD2_2B_HDCP_ST_TYPE_0, (_BIT1 | _BIT0))));

        case _DP_ST_SOURCE4:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(PD2_2B_HDCP_ST_TYPE_0, (_BIT3 | _BIT2)) >> 2));

        case _DP_ST_SOURCE5:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(PD2_2B_HDCP_ST_TYPE_0, (_BIT5 | _BIT4)) >> 4));

        case _DP_ST_SOURCE6:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(PD2_2B_HDCP_ST_TYPE_0, (_BIT7 | _BIT6)) >> 6));

        default:

            break;
    }

    return _HDCP2_TYPE_0;
}
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx2HdcpCheckLvp_128b132b(void)
{
    if(((ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx2LaneSwapSelect_128b132b(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_RTD_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_RTD)
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
#else
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED)
#endif
    {
        // Main-Link Lane Setting Start
        if(ScalerTypeCRxGetPinAssignment(enumInputPort) != _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Pin Assignment C/D PN Swap
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);
        }
        else
        {
            // Pin Assignment E PN Swap
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
            ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);
        }

        switch(ScalerTypeCRxGetPinAssignment(enumInputPort))
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                    ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
                }

                break;

            default:
            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                // DP Lane Swap Setting
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));

                break;
        }
    }
    else if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_RTS) || (ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_USER))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if((ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
            }
        }
        else
        {
            if((ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
            }
        }
    }
    else
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    {
        // DP PN Swap Setting
        ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
        ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
        ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
        ScalerSetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

        // DP Lane Swap Setting
        ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
        ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
        ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
        ScalerSetBit(PD2_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
    }

    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_3, ScalerGetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, _BIT7) >> 7);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_2, ScalerGetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, _BIT6) >> 6);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_1, ScalerGetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, _BIT5) >> 5);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_0, ScalerGetBit(PD2_A6_DECODE_10B8B_ERROR_DP20, _BIT4) >> 4);

    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_3, (ScalerGetBit(PD2_A3_LANE_MUX_DP20, (_BIT7 | _BIT6)) >> 6));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_2, (ScalerGetBit(PD2_A3_LANE_MUX_DP20, (_BIT5 | _BIT4)) >> 4));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_1, (ScalerGetBit(PD2_A3_LANE_MUX_DP20, (_BIT3 | _BIT2)) >> 2));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_0, (ScalerGetBit(PD2_A3_LANE_MUX_DP20, (_BIT1 | _BIT0))));

    if((ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) != _TRUE) && (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) != _BIT7))
    {
        ucClockLaneSelect = (ScalerGetBit(PD2_A3_LANE_MUX_DP20, (_BIT1 | _BIT0)) << 6);
    }

    // MAC Clock from PHY Lane Selection
    ScalerSetBit(PD2_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), ucClockLaneSelect);
}

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx2CheckHdcpCpirqStatus_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    if((ScalerGetByte(PD2_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PD2_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x02, 0x01) & _BIT2) == _BIT2)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22 decode
            if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
            {
                if(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, 0x00);
                }
            }
            else
#endif
            {
                if(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x29) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x01, ~_BIT2, 0x00);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
WORD ScalerDpMacDphyRx2SignalDetectMeasureCount_128b132b(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PD2_F1_DP_SIG_DET_DP20_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
        case _DP_MEASURE_PERIOD_125_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00000
            ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            break;

        case _DP_MEASURE_PERIOD_250_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00001
            ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            break;

        case _DP_MEASURE_PERIOD_1000_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            break;
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PD2_F2_DP_SIG_DET_DP20_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~_BIT7, 0x00);
    ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PD2_F0_DP_SIG_DET_DP20_0, _BIT6) == _BIT6)
        {
            usDpMeasureCount = ((((WORD)ScalerGetByte(PD2_F3_DP_SIG_DET_DP20_3)) << 8) | ScalerGetByte(PD2_F4_DP_SIG_DET_DP20_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PD2_F0_DP_SIG_DET_DP20_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}
#endif // End of (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : VBIOS Lane Adjust
// Input Value  : DP Lane Count
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMacDphyRx2VbiosMsaCheck(bit bDeskewEnhanced)
{
    bit bMSACheckResult = _FALSE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2);

    do
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PC5_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit(PC5_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), (((bDeskewEnhanced == _TRUE) ? _BIT7 : 0x00) | _BIT6));

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // SEC Reset
        ScalerSetBit(PC6_1E_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PC6_1E_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

        // Wait Two Frame Time to Get MSA
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(ScalerDpMacStreamRxVbiosMsaCheck(enumInputPort) == _TRUE)
        {
            bMSACheckResult = _TRUE;

            break;
        }
    }while(ScalerDpMacDphyRx2ChangeSrambleSeed() == _TRUE);

    if(ScalerDpAuxRxGetAssrModeEnable(enumInputPort) == _TRUE)
    {
        bMSACheckResult = ScalerDpMacDphyRx2VbiosAssrCheck(bMSACheckResult);
    }

    return bMSACheckResult;
}

//--------------------------------------------------
// Description  : Set DPRX SRAM CLK Gate
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx2HdcpSramClkGate(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Set DPRX SRAM CLK Gate Enable
        ScalerSetBit(PC5_A6_HDCP_DUMMY_1, ~_BIT2, _BIT2);
    }
    else
    {
        // Set DPRX SRAM CLK Gate Disable
        ScalerSetBit(PC5_A6_HDCP_DUMMY_1, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx2PowerDataRecover(void)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRx2PowerDataRecover_128b132b();
#endif
    ScalerDpMacDphyRx2PowerDataRecover_8b10b();
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx2PowerDataRecover_8b10b(void)
{
#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
    ScalerDpRxSetPhyToMacDphyMux(_DP_MAC_DPHY_RX2, ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX2));
#endif

    // Reset Key download port and Enable HDCP FW Mode
    ScalerSetBit(PC5_17_DP_HDCP_CONTROL, ~(_BIT4 | _BIT0), _BIT4);

    // Set R0' Available HW Mode
    ScalerSetBit(PC5_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PC5_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    // Set DPRX SRAM CLK Gate Enable
    ScalerDpMacDphyRx2HdcpSramClkGate(_ENABLE);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Set Type Value = 1 for AES 1
    ScalerSetByte(PC5_94_HDCP_TYPE_AES_1, 0x01);
#endif
}

#endif
