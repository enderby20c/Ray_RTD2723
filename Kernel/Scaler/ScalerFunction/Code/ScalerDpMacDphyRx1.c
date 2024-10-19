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
// ID Code      : ScalerDpMacDphyRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX1__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx1/ScalerDpMacDphyRx1.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX1_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
bit g_bDpMacDphyRx1SignaldetectINTHappened;
#endif

BYTE g_ucDpMacDphyRx1Temp;
BYTE g_ucDpMacDphyRx1EQCRC;

#if(_DP_MST_SUPPORT == _ON)
StructDPMacRxMiscInfo g_stDpMacDphyRx1MiscInfo;
BYTE g_pucDpMacDphyRx1MstTimeSlotBackup[_HW_DP_MST_ST_SOURCE_COUNT * 2];
BYTE g_pucDpMacDphyRx1MstStMuxBackup[_HW_DP_MST_ST_SOURCE_COUNT];
#endif

StructDpMacDphyRxHdcpCipherBackupInfo g_stDpMacDphyRx1HdcpCipherBackupInfo;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : DP MAC DPHY power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1PowerProc(EnumPowerAction enumPowerAction)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:

            if(GET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS() == _OFF)
            {
                DebugMessageDpRx("DP MAC DPHY Rx1 Power Off", 0);

                ScalerDpAuxRxSetManualMode(enumInputPort);

                // Set DPRX SRAM CLK Gate Disable
                ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                // DP MAC1 Power Cut Enable
                if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP14_DPHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE) == _SUCCESS)
                {
                    SET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS(_ON);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_DPHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
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

            if(GET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS() == _ON)
            {
                DebugMessageDpRx("DP MAC DPHY Rx1 Power On", 0);

                // DP MAC1 Power Cut Disable
                if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP14_DPHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS) == _SUCCESS)
                {
                    SET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS(_OFF);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_DPHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
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
bit ScalerDpMacDphyRx1NormalPreDetect(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // For Dp PHY CTS Test
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) == _BIT7)
    {
        DebugMessageDpRx("DP MAC RX1 -> PHY CTS Auto Mode", 0);

        ScalerDpPhyRxPhyCtsAutoMode(enumInputPort);

        return _FALSE;
    }
    else if(ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) == _TRUE)
    {
        DebugMessageDpRx("DP MAC RX1 -> PHY CTS Manual Mode", 0);

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
        ScalerDpMacDphyRx1ASSRModeSetting();
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
            ScalerDpMacDphyRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            if((ScalerDpMacDphyRx1CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) || (ScalerDpMacDphyRx1SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpMacDphyRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpMacDphyRx1AlignCheck() == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeCheck() == _TRUE))
            {
                DebugMessageDpRx("DP MAC RX1: Normal LT Pass", 0);
                /*
                DebugMessageDpRx("9. DP MAC RX1: Lane0 LE Diff", (g_pucDpMacRx1LEMaxTemp[0] - g_pucDpMacRx1LEMinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX1: Lane1 LE Diff", (g_pucDpMacRx1LEMaxTemp[1] - g_pucDpMacRx1LEMinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX1: Lane2 LE Diff", (g_pucDpMacRx1LEMaxTemp[2] - g_pucDpMacRx1LEMinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX1: Lane3 LE Diff", (g_pucDpMacRx1LEMaxTemp[3] - g_pucDpMacRx1LEMinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 LE Min", g_pucDpMacRx1LEMinTemp[0]);
                DebugMessageDpRx("9. DP MAC RX1: Lane1 LE Min", g_pucDpMacRx1LEMinTemp[1]);
                DebugMessageDpRx("9. DP MAC RX1: Lane2 LE Min", g_pucDpMacRx1LEMinTemp[2]);
                DebugMessageDpRx("9. DP MAC RX1: Lane3 LE Min", g_pucDpMacRx1LEMinTemp[3]);
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[0] - g_pucDpMacRx1Tap0MinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[1] - g_pucDpMacRx1Tap0MinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[2] - g_pucDpMacRx1Tap0MinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[3] - g_pucDpMacRx1Tap0MinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[0]);
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[1]);
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[2]);
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[3]);
                DebugMessageDpRx("9. DP MAC RX1: FLD Band", ScalerGetByte(PB0_BF_LANE0_A_CDR_02));
                DebugMessageDpRx("9. DP MAC RX1: Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[0] - g_pucDpMacRx1Tap0MinTemp2[0]));
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[1] - g_pucDpMacRx1Tap0MinTemp2[1]));
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[2] - g_pucDpMacRx1Tap0MinTemp2[2]));
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[3] - g_pucDpMacRx1Tap0MinTemp2[3]));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[0]);
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[1]);
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[2]);
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[3]);
                DebugMessageDpRx("9. DP MAC RX1: TP2 Check Result", g_ucDpMacRx1EQCRC);
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

                    ScalerDpMacDphyRx1ScrambleSetting();
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
                if(ScalerDpMacDphyRx1FecDecodeCheck() == _TRUE)
                {
                    ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x80, ~_BIT2, _BIT2);
                }
#endif
                ScalerDpAuxRxSetAutoMode(enumInputPort);

                return _TRUE;
            }
            else
            {
                DebugMessageDpRx("7. DP MAC RX1: Link Status Fail IRQ", 0);

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
            ScalerDpMacDphyRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            ScalerTimerDelayXms(30);

            DebugMessageDpRx("7. DP MAC RX1: Rebuild PHY", ScalerDpAuxRxGetLTStatus(enumInputPort));

            ScalerDpAuxRxCancelLinkStatusIRQ(enumInputPort);

            ScalerDpAuxRxSetManualMode(enumInputPort);

            if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS) ||
               (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpPhyRxRebuildPhy(enumInputPort, ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01));
            }

            ScalerDpAuxRxSetAutoMode(enumInputPort);

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpMacDphyRx1FecDetectStart(enumInputPort);
#endif
            // Mac Reset After Link Clock Stable
            ScalerDpMacDphyRx1Reset(enumInputPort);

            if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS)
            {
                ScalerDpMacDphyRx1DecodeErrorCountReset(_DP_MAC_DECODE_METHOD_8B10B);
            }

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpMacDphyRx1FecDetectEnd(enumInputPort);

            ScalerDpAuxRxSetFecStatusW1cProtectEnable(enumInputPort, _DISABLE);
#endif

            if((ScalerDpMacDphyRx1CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) || (ScalerDpMacDphyRx1SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpMacDphyRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpMacDphyRx1AlignCheck() == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeCheck() == _TRUE))
            {
                DebugMessageDpRx("7. DP MAC RX1: Rebuild Phy Pass", 0);

                /*
                DebugMessageDpRx("9. DP MAC RX1: Lane0 LE Diff", (g_pucDpMacRx1LEMaxTemp[0] - g_pucDpMacRx1LEMinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX1: Lane1 LE Diff", (g_pucDpMacRx1LEMaxTemp[1] - g_pucDpMacRx1LEMinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX1: Lane2 LE Diff", (g_pucDpMacRx1LEMaxTemp[2] - g_pucDpMacRx1LEMinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX1: Lane3 LE Diff", (g_pucDpMacRx1LEMaxTemp[3] - g_pucDpMacRx1LEMinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 LE Min", g_pucDpMacRx1LEMinTemp[0]);
                DebugMessageDpRx("9. DP MAC RX1: Lane1 LE Min", g_pucDpMacRx1LEMinTemp[1]);
                DebugMessageDpRx("9. DP MAC RX1: Lane2 LE Min", g_pucDpMacRx1LEMinTemp[2]);
                DebugMessageDpRx("9. DP MAC RX1: Lane3 LE Min", g_pucDpMacRx1LEMinTemp[3]);
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[0] - g_pucDpMacRx1Tap0MinTemp[0]));
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[1] - g_pucDpMacRx1Tap0MinTemp[1]));
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[2] - g_pucDpMacRx1Tap0MinTemp[2]));
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Diff", (g_pucDpMacRx1Tap0MaxTemp[3] - g_pucDpMacRx1Tap0MinTemp[3]));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[0]);
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[1]);
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[2]);
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Max", g_pucDpMacRx1Tap0MaxTemp[3]);
                DebugMessageDpRx("9. DP MAC RX1: FLD Band", ScalerGetByte(PB0_BF_LANE0_A_CDR_02));
                DebugMessageDpRx("9. DP MAC RX1: Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageDpRx("9. DP MAC RX1: D10.2 Counter", g_usDpMacRx1ClockCount);
                DebugMessageDpRx("9. DP MAC RX1: D10.2 Counter1", g_usDpMacRx1ClockCount1);
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[0] - g_pucDpMacRx1Tap0MinTemp2[0]));
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[1] - g_pucDpMacRx1Tap0MinTemp2[1]));
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[2] - g_pucDpMacRx1Tap0MinTemp2[2]));
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Diff 2", (g_pucDpMacRx1Tap0MaxTemp2[3] - g_pucDpMacRx1Tap0MinTemp2[3]));
                DebugMessageDpRx("9. DP MAC RX1: Lane0 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[0]);
                DebugMessageDpRx("9. DP MAC RX1: Lane1 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[1]);
                DebugMessageDpRx("9. DP MAC RX1: Lane2 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[2]);
                DebugMessageDpRx("9. DP MAC RX1: Lane3 Tap0 Max 2", g_pucDpMacRx1Tap0MaxTemp2[3]);
                DebugMessageDpRx("9. DP MAC RX1: Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageDpRx("9. DP MAC RX1: TP2 Check Result", g_ucDpMacRx1EQCRC);
                */

                ScalerDpAuxRxSetManualMode(enumInputPort);

                if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS) ||
                   (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
                {
                    ScalerDpAuxRxLinkStatusReload(enumInputPort);

                    ScalerDpAuxRxSetLTStatus(enumInputPort, _DP_NORMAL_LINK_TRAINING_PASS);

                    ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag(enumInputPort, _FALSE);

                    ScalerDpMacDphyRx1ScrambleSetting();

#if(_DP_RX_FEC_SUPPORT == _ON)
                    if(ScalerDpMacDphyRx1FecDecodeCheck() == _TRUE)
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

                SET_DP_MAC_DPHY_RX1_LOAD_NEW_STREAM_PAYLOAD();

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
                DebugMessageDpRx("7. DP MAC RX1: Rebuild PHY Fail", 0);

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
                ScalerDpMacDphyRx1ValidSignalDetection();

                DebugMessageDpRx("7. DP MAC RX1: VBIOS Check !!!!!!!", ScalerDpAuxRxGetFakeLT(enumInputPort));
            }

            break;

        default:

            break;
    }

    if(ScalerDpAuxRxGetValidVideoCheck(enumInputPort) == _TRUE)
    {
        ScalerDpAuxRxClrValidVideoCheck(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpMacDphyRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
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
bit ScalerDpMacDphyRx1PSPreDetect(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if((ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, _BIT7) == _BIT7) || (ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) == _TRUE))
    {
        DebugMessageDpRx("DP MAC Rx1 --> PHY CTS", 0);

        return _TRUE;
    }

    if(ScalerDpAuxRxGetValidVideoCheck(enumInputPort) == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Valid Video Check", 0);

        return _TRUE;
    }

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    if(ScalerDebugCheckDebugPort(enumInputPort) == _FALSE)
#endif
    {
        if(ScalerDpAuxRxGetToggle(enumInputPort) == _TRUE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Power Saving Aux Handshake", 0);

            return _TRUE;
        }
    }

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageDpRx("7. DP MAC RX1: Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort)) != _DP_ST_NONE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Stream Allocate", 0);

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
        DebugMessageDpRx("7. DP MAC RX1: Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1DigitalPhyInitial(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Set Digital Phy to Normal
    ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT2 | _BIT1), 0x00);

    // Enable CDI removal
    ScalerSetBit(P1F_CE_CDI_REMOVAL_DP20_1, ~_BIT7, _BIT7);

    // Enable FEC FIFO
    ScalerSetBit(P1F_80_FEC_DECODE_CTL, ~(_BIT6 | _BIT0), _BIT0);
#endif

    // Set Digital Phy to Normal
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // Enable K28.1 Detection
    ScalerSetBit(PB0_4B_DP_COMMA_DET_MANU, ~(_BIT2 | _BIT1), _BIT2);

    // err_8b10b_ctrl_gate = 1'b1 --> Avoid 8b10b Error Decode to FS
    ScalerSetBit(PB0_00_HD_DP_SEL, ~(_BIT1 | _BIT0), _BIT1);

    // alpm_wake_reset = 1'b1
    ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT6, _BIT6);

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _ON)
    // Enable FEC Weak Mode
    ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, _BIT2);

    // Enable FEC Weak Mode Gated
    ScalerSetBit(PB0_E1_FEC_ERROR_CONTROL, ~_BIT0, _BIT0);
#endif
    // Flag Clear
    ScalerSetBit(PB0_D2_FEC_SEQUENCE_DET_CTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5));

    // Enable FEC Detect FEC_DECODE_EN and FEC_DECODE_DIS IRQ
    ScalerSetBit(PB0_D2_FEC_SEQUENCE_DET_CTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Enable FEC Error Count Calculate 1lane mode
    ScalerSetBit(PB0_E1_FEC_ERROR_CONTROL, ~_BIT7, 0x00);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Enable ML_PHY_SLEEP Symbol Replacement
    ScalerSetBit(PB0_E3_FEC_ALPM_CTRL_1, ~_BIT7, _BIT7);
#endif
#endif

    // Restore HDCP Mode
    ScalerDpMacDphyRx1HdcpModeRestore();
}

//--------------------------------------------------
// Description  : DP Scramble Setting
// Input Value  : None
// Output Value : None
//              : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ScrambleSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);
    EnumDpAuxRxModeStatus enumBackUpAuxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);
    bit bEnhanceChange = _FALSE;
    bit bScrambleChange = _FALSE;

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(P1F_A7_SCRAMBLE_CTRL_DP20, _BIT5) == _BIT5))
        {
            bScrambleChange = _TRUE;

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5)
            {
                // Disable Scrambling
                ScalerSetBit(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, _BIT5);
            }
            else
            {
                // Enable Scrambling
                ScalerSetBit(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, 0x00);
            }
        }
    }
    else
#endif
    {
        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, _BIT7) == _BIT7) != (ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT2) == _BIT2))
        {
            bEnhanceChange = _TRUE;

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, _BIT7) == _BIT7)
            {
                // Enable Enhancement Control Mode --> MAC
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
            }
            else
            {
                // Disable Enhancement Control Mode --> MAC
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
            }
        }

        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(PB0_07_SCRAMBLE_CTRL, _BIT5) == _BIT5))
        {
            bScrambleChange = _TRUE;

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x02, _BIT5) == _BIT5)
            {
                // Disable Scrambling
                ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
            }
            else
            {
                // Enable Scrambling
                ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
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
bit ScalerDpMacDphyRx1DecodeErrorCountReset(EnumDpMacDecodeMethod enumDpMacDecodeMethod)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // Check if during Symbol Error Cnt Test
    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x02) & 0xC0) != 0x00)
    {
        return _FALSE;
    }

    // Reset 8b10b Error Count Value
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    switch(enumDpMacDecodeMethod)
    {
        case _DP_MAC_DECODE_METHOD_PRBS7:

            // Reverse PRBS7 Pattern Gen
            SET_DP_MAC_RX1_PRBS_REVERSE_EN();

            // Select PRBS7
            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT6 | _BIT5), 0x00);

            // Start Record PRBS7 Error Count Value
            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            break;

        case _DP_MAC_DECODE_METHOD_PRBS31:

            // Select PRBS31
            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Start Record PRBS7 Error Count Value
            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            break;

        case _DP_MAC_DECODE_METHOD_8B10B_DISPARITY:

            // Start Record 8b10b or Disparity Error Count Value
            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;

        default:
        case _DP_MAC_DECODE_METHOD_8B10B:

            // Start Record 8b10b Error Count Value
            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Measure 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(WORD usErrorCriteria, BYTE ucDpMacRx1LaneNumber)
{
    WORD usErrorCountLaneMeasure = 0;

    // Select Lane
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpMacRx1LaneNumber << 3));

    usErrorCountLaneMeasure = ((((WORD)ScalerGetByte(PB0_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB0_0C_BIST_PATTERN4));

    if(usErrorCountLaneMeasure > usErrorCriteria)
    {
        DebugMessageDpRx("DP MAC RX1: Lane", ucDpMacRx1LaneNumber);
        DebugMessageDpRx("DP MAC RX1: Lane Burst Error", usErrorCountLaneMeasure);

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Get 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : Error Count
//--------------------------------------------------
WORD ScalerDpMacDphyRx1GetDecodeErrorCount(BYTE ucDpMacRx1LaneNumber)
{
    // Select Lane
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpMacRx1LaneNumber << 3));

    return ((((WORD)ScalerGetByte(PB0_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB0_0C_BIST_PATTERN4));
}

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx1LaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1LaneSwapSelect_128b132b(enumInputPort, ucClockLaneSelect);
    }
    else
#endif
    {
        ScalerDpMacDphyRx1LaneSwapSelect_8b10b(enumInputPort, ucClockLaneSelect);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1GetLaneMuxMapping(EnumDpLane enumDpLane)
{
    switch(enumDpLane)
    {
        case _DP_LANE_0:

            return ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0));

        case _DP_LANE_1:

            return ScalerGetBit(PB0_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2;

        case _DP_LANE_2:

            return ScalerGetBit(PB0_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4;

        case _DP_LANE_3:

            return ScalerGetBit(PB0_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6;

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1LaneCountSet(BYTE ucDpLaneCount)
{
    switch(ucDpLaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT3);
#endif
            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT4);
#endif
            break;

        case _DP_FOUR_LANE:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#endif
            break;

        default:

            // [4:3] DP MAC Select Default
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), 0x00);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), 0x00);
#endif
            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Comma Detect
// Input Value  : ON or OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1SetCommaDetect(bit bEn)
{
    if(bEn == _ON)
    {
        // [4] Enable Comma Detection
        ScalerSetBit(PB0_05_SAMPLE_EDGE, ~_BIT4, 0x00);
    }
    else
    {
        // [4] Disable Comma Detection
        ScalerSetBit(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ClkSelect(EnumDpMacClkSelect enumClkSelect)
{
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, enumClkSelect);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT5, enumClkSelect >> 1);
#endif
}

//--------------------------------------------------
// Description  : Reset DP MAC FIFIO
// Input Value  : Inputport
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ChannelFifoReset(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        // FIFO sync
        ScalerSetBit(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
        ScalerSetBit(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);
    }
    else
#endif
    {
        // FIFO sync
        ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, 0x00);
        ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpMacDphyRx1AlignCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if((GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE) ||
       (ScalerDpMacStreamRxGetSourceTypeJudgeStatus(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRx1LaneValidCheck() == _FALSE))
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
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            if(ScalerGetBit(P1F_F7_DESKEW_PHY, _BIT4) == 0x00)
            {
                DebugMessageDpRx("DP MAC RX1: DP20 align fail warning", ScalerGetByte(P1F_F7_DESKEW_PHY));

                // Phy sync interval = 12672bit @10G 1.26us
                DELAY_5US();

                if(ScalerGetBit(P1F_F7_DESKEW_PHY, _BIT4) == 0x00)
                {
                    DebugMessageDpRx("DP MAC RX1: DP20 align fail", ScalerGetByte(P1F_F7_DESKEW_PHY));

                    return _FALSE;
                }
            }
        }
        else
#endif
        {
            if(ScalerGetBit(PB0_0E_DESKEW_PHY, _BIT4) == 0x00)
            {
                if(ScalerGetBit(PB0_0E_DESKEW_PHY, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
                {
                    ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), (_BIT7 | _BIT6));

                    ScalerTimerDelayXms(3);
                }
                else
                {
                    DebugMessageDpRx("DP MAC RX1: DP14 align fail", ScalerGetByte(PB0_0E_DESKEW_PHY));
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
bit ScalerDpMacDphyRx1DecodeCheck(void)
{
    BYTE ucTemp = 3;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if((GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE) ||
       (ScalerDpMacStreamRxGetSourceTypeJudgeStatus(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRx1LaneValidCheck() == _FALSE))
    {
        return _TRUE;
    }
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Check FEC Decode Status
        if(ScalerGetBit(P1F_80_FEC_DECODE_CTL, _BIT7) != _BIT7)
        {
            DebugMessageDpRx("DP MAC RX1: DP20 FEC Not enable", ScalerGetByte(P1F_80_FEC_DECODE_CTL));

            return _FALSE;
        }

        while(ucTemp > 0)
        {
            // Disable FEC Accumulated Err Counter
            ScalerSetBit(P1F_96_FEC_ACCUM_ERR_CTRL_7, ~_BIT0, 0x00);

            // Clear 128b/132b FEC Error Flag
            ScalerSetBit(P1F_8F_FEC_ACCUM_ERR_CTRL_0, ~_BIT6, _BIT6);

            // Set FEC Accumulated Error Threshold
            ScalerSetBit(P1F_8F_FEC_ACCUM_ERR_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Enable FEC Accumulated Err Counter
            ScalerSetBit(P1F_96_FEC_ACCUM_ERR_CTRL_7, ~_BIT0, _BIT0);

            // Delay Time us [150,x]
            DELAY_XUS(150);

            // DP20 Decode Check
            if(ScalerGetBit(P1F_8F_FEC_ACCUM_ERR_CTRL_0, _BIT6) == 0x00)
            {
                return _TRUE;
            }

            ucTemp--;
        }

        DebugMessageDpRx("DP MAC RX1: DP20 FEC ACC ERROR Fail", ScalerGetByte(P1F_8F_FEC_ACCUM_ERR_CTRL_0));

        return _FALSE;
    }
    else
#endif
    // dp14 decode check : 8b10b decode check
    {
        while(ucTemp > 0)
        {
            // Clear 8b/10b Decode Error Flag
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // Delay Time us [150,x]
            DELAY_XUS(150);

            switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
            {
                case _DP_ONE_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)
                    if(ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)
#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
                    if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
#endif
                    {
                        return _TRUE;
                    }

                    break;

                case _DP_TWO_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

                    if(ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)
                    {
                        return _TRUE;
                    }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)

                    if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                    {
                        if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                        {
                            return _TRUE;
                        }
                    }
#endif

                    break;

                case _DP_FOUR_LANE:

                    if(ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
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

        DebugMessageDpRx("7. DP MAC RX1: 8b/10b Decode Error", 0);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp14ResetProc(void)
{
    // Reset HDCP Block
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1HDCPUnplugReset(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

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
void ScalerDpMacDphyRx1CheckHdcpCpirqStatus(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1CheckHdcpCpirqStatus_128b132b();
    }
    else
#endif
    {
        ScalerDpMacDphyRx1CheckHdcpCpirqStatus_8b10b();
    }
}

//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpReAuthStatusCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

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
void ScalerDpMacDphyRx1CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1CpIRQ_128b132b(enumBStatusType);
    }
    else
#endif
    {
        ScalerDpMacDphyRx1CpIRQ_8b10b(enumBStatusType);
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpCheckValid(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1HdcpCheckValid_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1HdcpCheckValid_8b10b();
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpCheckEnabled(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1HdcpCheckEnabled_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1HdcpCheckEnabled_8b10b();
    }
}

//--------------------------------------------------
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1HdcpDownLoadKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP Block, HDCP FW Mode and Key download port
        ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT4 | _BIT0));

        // Set Km Clock to Xtal Clock
        ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT3, 0x00);

        // Enable HDCP Sram clk
        ScalerSetBit(PB0_A6_HDCP_DUMMY_1, ~_BIT2, _BIT2);
        ScalerMcuDelayXus(1);
    }
    else
    {
        // Disable HDCP Sram clk
        ScalerSetBit(PB0_A6_HDCP_DUMMY_1, ~_BIT2, 0x00);
        ScalerMcuDelayXus(1);

        // Disable Key download port
        ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~_BIT0, 0x00);

        // Enable HDCP Sram clk
        ScalerSetBit(PB0_A6_HDCP_DUMMY_1, ~_BIT2, _BIT2);
        ScalerMcuDelayXus(1);
    }
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key to SRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1HdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray)
{
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    WORD usIndex = 0;

    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        ScalerSetByte(PB0_18_DP_HDCP_DOWNLOAD_PORT, pucReadArray[usIndex]);

        // Polling 1ms for Key Sram Write Done
        ScalerTimerPollingFlagProc(1, PB0_17_DP_HDCP_CONTROL, _BIT6, _TRUE);
    }
#else
    ScalerWrite(PB0_18_DP_HDCP_DOWNLOAD_PORT, usLength, pucReadArray, _NON_AUTOINC);
#endif
}

//--------------------------------------------------
// Description  : HDCP Mode Alignment between Variable & Register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1HdcpModeRestore(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
    {
        // Enable HDCP MAC1 for HDCP 2.2 Mode
        ScalerDpMacDphyRx1SetHdcpMode(_HDCP_22);

        if(ScalerDpMacDphyRx1HdcpDetectLvp() == _FALSE)
        {
            ScalerDpMacDphyRx1Hdcp2CipherDataRestore();
        }
    }
    else
#endif
    {
        // Enable HDCP MAC1 for HDCP 1.4 Mode
        ScalerDpMacDphyRx1SetHdcpMode(_HDCP_14);

        if(ScalerDpMacDphyRx1HdcpReAuthStatusCheck() == _TRUE)
        {
            if(ScalerDpMacDphyRx1HdcpDetectLvp_8b10b() == _FALSE)
            {
                bit bDpcdR0Available = 0;

                ScalerDpAuxRxSetManualMode(enumInputPort);

                DELAY_XUS(200);

                // Backup R0' Available Flag
                bDpcdR0Available = (bit)ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x06, 0x80, 0x29, _BIT1);

                // HDCP R0 Calculate
                ScalerSetBit(PB0_63_HDCP_OTHER, ~_BIT7, _BIT7);
                ScalerSetBit(PB0_63_HDCP_OTHER, ~_BIT7, 0x00);

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
void ScalerDpMacDphyRx1SetHdcpMode(EnumHDCPType enumHDCPType)
{
    enumHDCPType = enumHDCPType;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_8B10B)
#endif
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if(enumHDCPType == _HDCP_22)
        {
            ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT1, _BIT1);
        }
        else
#endif
        {
            ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT1, 0x00);
        }
    }
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx1Hdcp2ReAuthStatusCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

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
void ScalerDpMacDphyRx1FecDecode(BYTE ucFECDecode)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ucFECDecode == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ////// DP20 Part //////
        // FEC Enable
        ScalerSetBit(P1F_80_FEC_DECODE_CTL, ~(_BIT6 | _BIT0), _BIT0);

        // Enable FEC error detect
        ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~_BIT7, _BIT7);
#endif
        ////// DP14 Part //////
        // FEC Enable
        ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Enable FEC error detect
        ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~_BIT7, _BIT7);
    }
    else
    {
        // FEC Disable
        ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~(_BIT7 | _BIT0), 0x00);

        // Disable FEC error detect
        ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~_BIT7, 0x00);

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
bit ScalerDpMacDphyRx1FecDecodeCheck(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerGetBit(P1F_80_FEC_DECODE_CTL, _BIT7) == _BIT7)
    {
        return _TRUE;
    }
#endif

    if(((ScalerGetBit(PB0_D0_FEC_DECODE_CTL, _BIT7) == _BIT7) && (ScalerGetBit(PB0_D2_FEC_SEQUENCE_DET_CTL, _BIT7) == _BIT7)))
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
void ScalerDpMacDphyRx1FecDetectStart(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1FecDecode(_ENABLE);
    }
    else
#endif
    {
        // Reset FEC Ready
        ScalerDpMacDphyRx1FecDecode(_DISABLE);

        if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0) != GET_DP_MAC_DPHY_RX1_FEC_DECODE_STATUS())
        {
            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
            {
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _OFF)
                // Enable FEC Seq Weak mode
                ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, _BIT2);
#endif
                ScalerDpMacDphyRx1FecDecode(_ENABLE);
            }
            else
            {
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _OFF)
                // Disable FEC Seq Weak mode
                ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
                ScalerDpMacDphyRx1FecDecode(_DISABLE);
            }
        }
    }
}

//--------------------------------------------------
// Description  : FEC Detction End (Weak mode)
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1FecDetectEnd(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) != _CODING_TYPE_128B132B)
#endif
    {
#if(_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT == _OFF)
        // After more than 65536x2x10xLink_Rate, Disable FEC Seq Weak mode
        ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
        if(ScalerDpMacDphyRx1FecDecodeCheck() == _TRUE)
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
DWORD ScalerDpMacDphyRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    DWORD ulDpMeasureCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        ScalerDpPhyRxSignalDetection(enumInputPort, _ENABLE);
    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ulDpMeasureCount = (DWORD)ScalerDpMacDphyRx1SignalDetectMeasureCount_128b132b(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
    }
    else
#endif
    {
        // [1:0] freqdet_lane_sel
        ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

        // [5] ln_ck_sel
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

        switch(enumDpMeasurePeriod)
        {
            case _DP_MEASURE_PERIOD_125_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00000
                ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                break;

            case _DP_MEASURE_PERIOD_250_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00001
                ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                break;

            case _DP_MEASURE_PERIOD_1000_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00011
                ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                break;

            case _DP_MEASURE_PERIOD_2000_CYCLE:
            default:

                // [4:0] DP_XTAL_CYCLE = 5'b00100
                ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                break;
        }

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Delay Time us [5,150] Polling for Measure Done
        for(pData[0] = 0; pData[0] <= 30; pData[0]++)
        {
            DELAY_5US();

            if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
            {
                ulDpMeasureCount = (DWORD)((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                break;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
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

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
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
bit ScalerDpMacDphyRx1SignalCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    WORD usDataStreamL0 = 0;
    WORD usDataStreamL1 = 0;
    WORD usDataStreamL2 = 0;
    WORD usDataStreamL3 = 0;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

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

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    // Measure Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            usDataStreamL0 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        case _DP_TWO_LANE:

            usDataStreamL0 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        default:
        case _DP_FOUR_LANE:

            usDataStreamL0 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL2 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_2), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL3 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_3), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

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
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
        if(GET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
bit ScalerDpMacDphyRx1CDRCheck(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if(ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0)) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0)) == _TRUE) &&
               (ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1)) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0)) == _TRUE) &&
               (ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1)) == _TRUE) &&
               (ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_2)) == _TRUE) &&
               (ScalerDpMacDphyRx1MeasureLaneCDRClk(enumDpLinkRate, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_3)) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    if(GET_DP_MAC_DPHY_RX1_SIGNALDETECT_INT_HAPPENED() == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        DebugMessageDpRx("7. DP MAC RX1: wuzanne test : CDR Unlock", 0);

        return _FALSE;
    }
}

#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx1 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1MstReset(void)
{
    BYTE ucTemp = 0;

    // Reset STx
    for(ucTemp = _DP_ST_1; ucTemp <= _DP_ST_END; ucTemp++)
    {
#if(_DP_MST_SUPPORT == _ON)
        // Reset Start Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_8B10B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Reset End Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX1_STX_END_ADDRESS_8B10B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Reset Start Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_128B132B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Reset End Position
        ScalerSetBit(GET_DP_MAC_DPHY_RX1_STX_END_ADDRESS_128B132B(ucTemp), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Reset Stream Enable
        ScalerSetBit(GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_128B132B(ucTemp), ~(_BIT7), 0x00);
#endif
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Rx1 Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1LoadNewStreamPayload(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P9F_01_STHD_CTRL_1, ~_BIT7, 0x00);

        // Delay Up to 65537 Timeslots
        // 3.2ns per Timeslot for UHBR10
        // Delay Time  >=  65537 * 3.2ns = 210ns, as 500ns for Insurance Purposes
        DELAY_XUS(500);
        ScalerSetBit(P9F_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        ScalerSetBit(PB8_01_STHD_CTRL_1, ~_BIT7, 0x00);
        DELAY_5US();
        ScalerSetBit(PB8_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
}
#endif // #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DP Mst Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ConfigMstOrSstMode(void)
{
#if(_DP_MST_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT0) == _BIT0)
    {
        // MST to SST block Config MST Mode
        SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_MST_MODE();

        // Dp Phy Rx MST mode
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        // MST to SST block Config SST Mode
        SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_SST_MODE();

        // Dp Phy Rx SST mode
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);
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
// Description  : HDCP 2.2 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2ResetProc(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRx1Hdcp2ResetProc_128b132b();
#endif
    ScalerDpMacDphyRx1Hdcp2ResetProc_8b10b();
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2CipherDataRestore(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Check Power Status
        if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP20_MAC) == _POWER_CUT_OFF)
        {
            ScalerDpMacDphyRx1Hdcp2CipherDataRestore_128b132b();
        }
    }
    else
#endif
    {
        // Check Power Status
        if(ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP14_MAC) == _POWER_CUT_OFF)
        {
            ScalerDpMacDphyRx1Hdcp2CipherDataRestore_8b10b();
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Clear Restored Cipher Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ClrHdcp2CipherBackupInfo(void)
{
    // Clear HDCP2 Backup: Riv, AESCipher, Stream Type
    memset(g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxRiv, 0, sizeof(g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxRiv));
    memset(g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxAESCipher, 0, sizeof(g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxAESCipher));
    memset(g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType, 0, sizeof(g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType));
}

//--------------------------------------------------
// Description  : Detect Dp Rx HDCP Link Veriffication Pattern (0x531F)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpDetectLvp(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1HdcpDetectLvp_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1HdcpDetectLvp_8b10b();
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP2 Stream Type
// Input Value  : ucStreamId
// Output Value : Type Value
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRx1Hdcp2GetStxType(BYTE ucStreamId)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1Hdcp2GetStxType_128b132b(ucStreamId);
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1Hdcp2GetStxType_8b10b(ucStreamId);
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
void ScalerDpMacDphyRx1Hdcp14Sha1DataWrite(void)
{
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    // Enable write 32-bit data to SHA-1 block
    ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT0), _BIT0);

    // Polling 1ms for HDCP Sha Data Write Done
    if(ScalerTimerPollingFlagProc(1, PB0_30_SHA_CONTRL, _BIT5, _TRUE) == _TRUE)
    {
        ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT5 | _BIT0), _BIT5);
    }
#else
    // Enable write 32-bit data to SHA-1 block
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

    ScalerMcuDelayXus(1);
#endif
}

//--------------------------------------------------
// Description  : Check HDCP 1.4 Auth1 Process
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRx1Hdcp14Auth1Check(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if((ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)) &&
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
void ScalerDpMacDphyRx1Hdcp14WriteShaInput(void)
{
    WORD usKsvFifoLength = 0;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    usKsvFifoLength = (WORD) ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A) * 5;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    SET_DP_MAC_DPHY_RX1_HDCP14_SHA_RESET();
    CLR_DP_MAC_DPHY_RX1_HDCP14_SHA_RESET();

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PB0_33_SHA_DATA3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PB0_34_SHA_DATA4, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_0());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_1());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_2());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_3());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_4());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_5());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_6());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_7());
            ScalerSetByte(PB0_34_SHA_DATA4, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_0());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_1());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_2());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_3());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_4());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_5());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_6());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_7());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, 0x80);
            ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB0_33_SHA_DATA3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_0());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_1());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_2());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_3());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_4());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_5());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_6());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_7());
            ScalerSetByte(PB0_32_SHA_DATA2, 0x80);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_0());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_1());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_2());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_3());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_MAC_DPHY_RX1_HDCP14_M0_4());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_MAC_DPHY_RX1_HDCP14_M0_5());

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_MAC_DPHY_RX1_HDCP14_M0_6());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_MAC_DPHY_RX1_HDCP14_M0_7());
            ScalerSetByte(PB0_33_SHA_DATA3, 0x80);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
            ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

            usKsvLengthTemp += 4;
        }

        // The length of SHA-1 input is equal to 2^64(8 bytes)
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PB0_34_SHA_DATA4, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();

        usKsvLengthTemp += 8;

        ScalerDpMacDphyRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - Load SHA Result to DPCD table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp14LoadShaToDpcd(void)
{
    BYTE pucTemp[2];
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    ScalerDpAuxRxSetManualMode(enumInputPort);

    for(pucTemp[0] = 0; pucTemp[0] < 5; pucTemp[0]++)
    {
        for(pucTemp[1] = 0; pucTemp[1] < 4; pucTemp[1]++)
        {
            // DPCD [0x68014 ~ 0x68027]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, (0x14 + (pucTemp[0] * 4) + pucTemp[1]), ScalerGetByte(PB0_39_SHA_3 + (pucTemp[0] * 4) - pucTemp[1]));
        }
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp14FakeAuthenProc(void)
{
    BYTE pucSHAInput[64];
    BYTE ucTemp = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // Set Device Count and Depth
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x2A, 0x01);
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x2B, 0x01);

    // Load KSV
    memcpy(pucSHAInput, g_pucSyncHdcpAksvBackup, 5);

    // Load Device Count and Depth
    pucSHAInput[5] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A);
    pucSHAInput[6] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B);

    // Load M0'
    pucSHAInput[7] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_0();
    pucSHAInput[8] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_1();
    pucSHAInput[9] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_2();
    pucSHAInput[10] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_3();
    pucSHAInput[11] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_4();
    pucSHAInput[12] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_5();
    pucSHAInput[13] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_6();
    pucSHAInput[14] = GET_DP_MAC_DPHY_RX1_HDCP14_M0_7();

    memset(&pucSHAInput[15], 0, 49);

    pucSHAInput[15] = 0x80;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    pucSHAInput[63] = 0x78;

    // Compute V'
    ScalerDpMacDphyRx1HDCPSha1Calculate(pucSHAInput, 0);

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
    ScalerDpMacDphyRx1Hdcp14LoadShaToDpcd();
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - SHA circuit Run
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1HDCPAuthShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    SET_DP_MAC_DPHY_RX1_HDCP14_SHA_FIRST_CALCULATE(bIsFirst);

    // Run SHA-1 Circuit
    SET_DP_MAC_DPHY_RX1_HDCP14_SHA_CALCULATE_ENABLE();

    ScalerTimerPollingFlagProc(5, PB0_30_SHA_CONTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    CLR_DP_MAC_DPHY_RX1_HDCP14_SHA_FIRST_CALCULATE();
}

//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpCheckLvp(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1HdcpCheckLvp_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1HdcpCheckLvp_8b10b();
    }
}
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable Dp 8b10b Decoder Error WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Set8b10bDecErrorWD(bit bEn)
{
    // 8b10b Decoder Error WD Setting
    // _BIT3 set to 0 == Clear Flag 0x0B4A[7:4]
    ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~(_BIT5 | _BIT3), ((bEn == _ENABLE) ? (_BIT5 | _BIT3) : 0x00));
}

//--------------------------------------------------
// Description  : Check Dp 8b10b Dec Err Status
// Input Value  : None
// Output Value : _SUCCESS --> No Dec Err
//                _FAIL    --> Dec Err Occur
//--------------------------------------------------
bit ScalerDpMacDphyRx1Check8b10bDecErrorStatus(void)
{
    return ((ScalerGetBit(PB0_4A_DP_LANEX_ACCUMLATED_ERR_COUNT, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00) ? _SUCCESS : _FAIL);
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx1 Auxless ALPM Initial
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1AuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn)
{
    WORD usTdrlTime = 0;

    if(bEn == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT7, _BIT7);

            // Enable ALPM mode
            ScalerSetBit(P1F_D7_FRAME_DETECT_ALPM_DP20_2, ~_BIT0, _BIT0);

            // Clear Sleep Pattern INT Flag
            ScalerSetBit(P1F_DC_ALPM_DETECT_DP20, ~_BIT4, _BIT4);

            // Enable Sleep Pattern INT
            ScalerSetBit(P1F_DC_ALPM_DETECT_DP20, ~(_BIT4 | _BIT3), _BIT3);
        }
        else
#endif
        {
            ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT7, 0x00);

            // Clear Sleep Pattern INT Flag
            ScalerSetBit(PB0_4C_ALPM_SLEEP_0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Enable Sleep Pattern Detect and INT
            ScalerSetBit(PB0_4C_ALPM_SLEEP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));
        }

        // Mac LFPS Wake Use DPHY lfps_cnt_vld
        ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT5, 0x00);

        if((ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0)) == _DP_LANE_0) ||
           (ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0)) == _DP_LANE_1))
        {
            // ALPM LFPS Detection Select Lane0
            ScalerSetBit(PB0_BE_ALPM_UFP_14, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            // ALPM LFPS Detection Select Lane2
            ScalerSetBit(PB0_BE_ALPM_UFP_14, ~(_BIT7 | _BIT6), _BIT7);
        }

        // Toggle Reset UFP ALPM FSM
        ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT6, _BIT6);
        ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT6, 0x00);

        // 00116h[3] = 1 => There are no LTTPRs Between DPTx and DPRx
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x16, _BIT3) == _BIT3)
        {
            // lfps_cnt_vld = 0 => tsilence(80~180ns) + t1(50us) => Normal Data
            // eq_start_time = 0xFF => 255/108Mhz = 2.36us
            ScalerSetByte(PB0_B3_ALPM_UFP_03, 0xFF);

            // noisy_area_start_time = tsilence(80~180ns) + 40us = ~40.13us => 40.13us * 108Mhz = 4334 = 0x10EE
            ScalerSetBit(PB0_B4_ALPM_UFP_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
            ScalerSetByte(PB0_B8_ALPM_UFP_08, 0xEE);

            // cds_start_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PB0_B7_ALPM_UFP_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PB0_BB_ALPM_UFP_11, 0x1C);

            // normal_start_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PB0_C0_ALPM_UFP_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PB0_C1_ALPM_UFP_16, 0x1C);

            // start_tps2_err_time = 15us => 15us * 108Mhz = 1620 = 0x654
            ScalerSetBit(PB0_B5_ALPM_UFP_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
            ScalerSetByte(PB0_B9_ALPM_UFP_09, 0x54);

            // retrain_sleep_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PB0_B6_ALPM_UFP_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PB0_BA_ALPM_UFP_10, 0x1C);
        }
        else
        {
            // lfps_cnt_vld = 0 => tsilence(80~180ns) + t1(50us) + tDRL => Normal Data
            // eq_start_time = 0xFF => 255/108Mhz = 2.36us
            ScalerSetByte(PB0_B3_ALPM_UFP_03, 0xFF);

            // noisy_area_start_time = tsilence(80~180ns) + 40us = ~40.13us => 40.13us * 108Mhz = 4334 = 0x10EE
            ScalerSetBit(PB0_B4_ALPM_UFP_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
            ScalerSetByte(PB0_B8_ALPM_UFP_08, 0xEE);

            // cds_start_time = 10us => 10us * 108Mhz = 1080 = 0x438
            ScalerSetBit(PB0_B7_ALPM_UFP_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
            ScalerSetByte(PB0_BB_ALPM_UFP_11, 0x38);

            usTdrlTime = ScalerDpMacDphyRxAuxlessAlpmTdrlTime(enumInputPort);

            // normal_start_time = tDRL =>  tDRL * 108Mhz
            ScalerSetBit(PB0_C0_ALPM_UFP_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usTdrlTime >> 8));
            ScalerSetByte(PB0_C1_ALPM_UFP_16, usTdrlTime);

            // start_tps2_err_time = 15us => 15us * 108Mhz = 1620 = 0x654
            ScalerSetBit(PB0_B5_ALPM_UFP_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
            ScalerSetByte(PB0_B9_ALPM_UFP_09, 0x54);

            // retrain_sleep_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit(PB0_B6_ALPM_UFP_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte(PB0_BA_ALPM_UFP_10, 0x1C);
        }
    }
    else
    {
        // alpm_wake_reset = 1'b1
        ScalerSetBit(PB0_B0_ALPM_UFP_00, ~_BIT6, _BIT6);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Disable ALPM mode
        ScalerSetBit(P1F_D7_FRAME_DETECT_ALPM_DP20_2, ~_BIT0, 0x00);

        // Disable Sleep Pattern INT
        ScalerSetBit(P1F_DC_ALPM_DETECT_DP20, ~(_BIT4 | _BIT3), 0x00);
#endif
        // Disable Sleep Pattern Detect and IRQ
        ScalerSetBit(PB0_4C_ALPM_SLEEP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1CpIRQ_8b10b(EnumDpRxBStatusType enumBStatusType)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

            // Check for HDCP Block work in 1.4
            if(ScalerDpMacDphyRx1HdcpReAuthStatusCheck() == _TRUE)
            {
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
                if(ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _FALSE)
                {
                    // Reset HDCP Block
                    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
                }

                if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT1) == _BIT1)
                {
                    ScalerDpAuxRxSetDpcdWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x05, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x20, 0x05) | _BIT2));
                }
#else
                // Reset HDCP Block
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
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
                ScalerSetBit(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

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
bit ScalerDpMacDphyRx1HdcpCheckEnabled_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14)
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
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
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT4) == _BIT4)
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
bit ScalerDpMacDphyRx1HdcpCheckValid_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14)
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            if((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
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
bit ScalerDpMacDphyRx1HdcpCheck_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // Check for HDCP 1.4 Aksv
    if(ScalerDpMacDphyRx1HdcpReAuthStatusCheck() == _FALSE)
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Check for HDCP 2.2 Riv
        if(ScalerDpMacDphyRx1Hdcp2ReAuthStatusCheck() == _FALSE)
#endif
        {
            return _TRUE;
        }
    }

    if(((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
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
bit ScalerDpMacDphyRx1HdcpDetectLvp_8b10b(void)
{
    if((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2ResetProc_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // Disable HDCP2.2 Auth. Done
    ScalerSetBit(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);

    // Clear Type Value
    ScalerSetByte(PB0_93_HDCP_TYPE_AES_0, 0x00);

    // Clear Type Value
    ScalerSetByte(PB0_94_HDCP_TYPE_AES_1, 0x01);

#if(_DP_MST_SUPPORT == _ON)
    // For MST mode
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        // Clear AES STx Type
        ScalerSetBit(PB0_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    }
    else
#endif
    {
        // Clear AES STx Type
        ScalerSetBit(PB0_95_HDCP_ST_TYPE, ~_BIT7, 0x00);
    }

    // Reset HDCP Block
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    // Disable HDCP2.2
    ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_14);
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacDphyRx1Hdcp2CipherDataRestore_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);
    BYTE ucLoop = 0x00;

    ScalerDpAuxRxSetManualMode(enumInputPort);

    if(ScalerDpHdcpRxGetAuthDone(enumInputPort) == _TRUE)
    {
        // Reset HDCP2.2 Auth. Done
        ScalerSetBit(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);

        // Recover HDCP MAC1 for HDCP 2.2 Mode
        ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT1, _BIT1);

        for(ucLoop = 0; ucLoop < 8; ucLoop++)
        {
            ScalerSetByte((PB0_55_RIV0 + ucLoop), g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxRiv[ucLoop]);
        }

        for(ucLoop = 0; ucLoop < 16; ucLoop++)
        {
            ScalerSetByte((PB0_81_HDCP_AES_CIPHER_KEY_15 + ucLoop), g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxAESCipher[ucLoop]);
        }

#if(_DP_MST_SUPPORT == _ON)
        // For MST mode
        if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
        {
            // Set Stream 1~ Stream 5 Type
            ScalerSetBit(PB0_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] & 0xF8);

            // Set Stream 6 Type
            ScalerSetBit(PB0_96_DUMMY3, ~_BIT7, g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] & 0x80);
        }
        else
#endif
        {
            // Set Stream 1
            ScalerSetBit(PB0_95_HDCP_ST_TYPE, ~_BIT7, g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] & 0x80);
        }

        // Enable HDCP2.2 Auth. Done
        ScalerSetBit(PB0_20_HDCP_DEBUG, ~_BIT4, _BIT4);

        DebugMessageHDCP2("[D1]Recover Hdcp2 Cipher Data", 0);
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP2 Stream Type
// Input Value  : ucStreamId
// Output Value : Type Value
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRx1Hdcp2GetStxType_8b10b(BYTE ucStreamId)
{
    return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)ScalerGetBit(PB0_95_HDCP_ST_TYPE, (_BIT7 >> (ucStreamId))));
}
#endif
#endif

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpCheckLvp_8b10b(void)
{
    if(((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
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
void ScalerDpMacDphyRx1Reset(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        // De-Skew Circuit Reset
        ScalerSetBit(P1F_F7_DESKEW_PHY, ~(_BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit(P1F_F7_DESKEW_PHY, ~(_BIT6 | _BIT4 | _BIT1), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
        ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

        // Delay for Lane Alignment after Mac Reset
        ScalerTimerDelayXms(2);
    }
    else
#endif
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // Delay for Lane Alignment after Mac Reset
        ScalerTimerDelayXms(2);

        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
        {
            // [4] Disable Comma Detection
            ScalerSetBit(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
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
bit ScalerDpMacDphyRx1MarginLinkCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
    {
        case _DP_LINK_HBR3:
        case _DP_LINK_HBR2:

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
            if((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) &&
               (ScalerDpMacDphyRx1SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               (ScalerDpMacDphyRx1LaneBsCheck() == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeErrorCountCheck(_DP_MARGIN_LINK_TIME_CRITERIA, _DP_MARGIN_LINK_ERROR_CRITERIA) == _FALSE))
            {
                // To Avoid Margin Link Trigger by No Signal
                if((ScalerDpPhyRxDFECheck(enumInputPort) == _TRUE) &&
                   (ScalerDpMacDphyRx1SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
                   (ScalerDpMacDphyRx1LaneBsCheck() == _TRUE))
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
bit ScalerDpMacDphyRx1DecodeErrorCountCheck(WORD usTimeCriteria, WORD usErrorCriteria)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpMacDphyRx1DecodeErrorCountReset(_DP_MAC_DECODE_METHOD_8B10B) == _FALSE)
    {
        return _TRUE;
    }

    ScalerTimerDelayXms(usTimeCriteria);

    switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_0) == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_0) == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_1) == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_2) == _TRUE) &&
               (ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, _DP_LANE_3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

    DebugMessageDpRx("7. DP MAC RX1: Error Count Fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : Check Lane BS
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpMacDphyRx1LaneBsCheck(void)
{
    // Detect Enable
    ScalerSetBit(PB0_00_HD_DP_SEL, ~(_BIT3 | _BIT0), 0x00);
    ScalerSetBit(PB0_00_HD_DP_SEL, ~(_BIT3 | _BIT0), _BIT3);

    // Delay for 8192 x 10 x 8 x 2 / 1.62G = 809us
    DELAY_XUS(850);

    // Check Lane Bs
    if(ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
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
bit ScalerDpMacDphyRx1LaneValidCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // Enable Lane Valid Detect
    ScalerSetBit(PB0_00_HD_DP_SEL, ~(_BIT3 | _BIT0), 0x00);
    ScalerSetBit(PB0_00_HD_DP_SEL, ~(_BIT3 | _BIT0), _BIT3);

    // Delay Time us [150,x]
    DELAY_XUS(150);

    switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

            if(ScalerGetBit(PB0_00_HD_DP_SEL, _BIT7) == 0x00)
            {
                return _FALSE;
            }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
            if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                return _FALSE;
            }
#endif

            break;

        case _DP_TWO_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

            if(ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT6)) == 0x00)
            {
                return _FALSE;
            }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)

            if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                if(((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT7) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT6) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT5) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT4) == 0x00)))
                {
                    return _FALSE;
                }
            }
#endif

            break;

        case _DP_FOUR_LANE:

            if(ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
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
void ScalerDpMacDphyRx1ValidSignalDetection(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLaneCount = _DP_FOUR_LANE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_DP_MST_SUPPORT == _ON)

    if(g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup == _TRUE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);

        if((ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) != _BIT1))
        {
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x00, g_stDpMacDphyRx1MiscInfo.ucDpMacRxLinkRateBackup);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x01, ((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x60) | (g_stDpMacDphyRx1MiscInfo.ucDpMacRxLaneCountBackup | _BIT7)));

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x20, g_stDpMacDphyRx1MiscInfo.ucDpMacRxFecReadyBackup);
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x00, 0x01, 0x08, g_stDpMacDphyRx1MiscInfo.ucDpMacRxCodingTypeBackup);

            if(g_stDpMacDphyRx1MiscInfo.ucDpMacRxCodingTypeBackup == _CODING_TYPE_128B132B)
            {
                ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_128B132B);
            }
            else
            {
                ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_8B10B);
            }
#endif

            if(g_stDpMacDphyRx1MiscInfo.ucDpMacRxLaneCountBackup == _DP_FOUR_LANE)
            {
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x02, 0x77);
                ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x03, 0x77);
            }
            else if(g_stDpMacDphyRx1MiscInfo.ucDpMacRxLaneCountBackup == _DP_TWO_LANE)
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

            ScalerDpMacDphyRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESTORE);
        }

        ScalerDpAuxRxSetAutoMode(enumInputPort);

        DebugMessageDpRx("DP MAC RX1: VBIOS_Link_Rate_MST", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00));
        DebugMessageDpRx("DP MAC RX1: VBIOS_Lane_Count_MST", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01));
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
            ucDpLinkRate = ScalerDpMacDphyRx1LinkRateDetect();

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
                    ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, _BIT2);

                    ScalerDpMacDphyRx1FecDecode(_ENABLE);
#endif
                    ScalerDpAuxRxSetAutoMode(enumInputPort);

                    if(ScalerDpMacDphyRx1VbiosMsaCheck(_FALSE) == _TRUE)
                    {
                        break;
                    }
                    else
                    {
                        if(ScalerDpMacDphyRx1VbiosMsaCheck(_TRUE) == _TRUE)
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
                    ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
#endif
                    return;
                }
            }
            while((ucDpLaneCount == _DP_TWO_LANE) || (ucDpLaneCount == _DP_ONE_LANE));

#if(_DP_RX_FEC_SUPPORT == _ON)
            // Disable FEC Seq Weak mode
            ScalerSetBit(PB0_D0_FEC_DECODE_CTL, ~_BIT2, 0x00);
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
                    if(ScalerDpMacDphyRx1FecDecodeCheck() == _TRUE)
                    {
                        ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x20, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ScalerDpMacDphyRx1FecDecode(_DISABLE);
                    }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                    if(ScalerDpMacDscRxDscStreamCheck(ScalerDpRxGetMacSwitch(enumInputPort)) == _TRUE)
                    {
                        ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, 0x00, 0x01, 0x60, ~_BIT0, _BIT0);
                    }
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
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

        DebugMessageDpRx("DP MAC RX1: VBIOS_Link_Rate", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00));
        DebugMessageDpRx("DP MAC RX1: VBIOS_Lane_Count", ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01));
    }
}

//--------------------------------------------------
// Description : DP Link Rate Detect
// Input Value  : None
// Output Value : Link Rate
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1LinkRateDetect(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLinkRateDecide = _DP_LINK_NONE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    do
    {
        if(ucDpLinkRate == 0)
        {
            if(_HW_DP_D1_MAX_LINK_RATE_SUPPORT > ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x00, 0x01))
            {
                if(_HW_DP_D1_MAX_LINK_RATE_SUPPORT > _DP_LINK_HBR3)
                {
                    ucDpLinkRate = _DP_LINK_HBR3;
                }
                else
                {
                    ucDpLinkRate = _HW_DP_D1_MAX_LINK_RATE_SUPPORT;
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

        if(ScalerDpMacDphyRx1LinkRateCheck(ucDpLinkRate) == _TRUE)
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
bit ScalerDpMacDphyRx1LinkRateCheck(BYTE ucDpLinkRate)
{
    WORD usDataStreamL0 = 0;
    BYTE ucDpLEQScanValue = _DP_RX_RELOAD_LEQ_INITIAL;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

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

        usDataStreamL0 = ScalerDpMacDphyRx1SignalDetectMeasureCount(ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

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
bit ScalerDpMacDphyRx1VbiosAssrCheck(bit bMSACheckResult)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

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
            if(ScalerGetBit(PB0_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
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
            ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

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
void ScalerDpMacDphyRx1ASSRModeSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x0A) & _BIT0) == _BIT0)
    {
        // Scramble seed equal to 0xFFFE
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Scramble seed equal to 0xFFFF
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Change Dp Scramble Seed
// Input Value  : None
// Output Value : False --> Change Scrmable Seed Finish
//--------------------------------------------------
bit ScalerDpMacDphyRx1ChangeSrambleSeed(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if((ScalerDpAuxRxGetAssrModeEnable(enumInputPort) == _TRUE) && (ScalerGetBit(PB0_07_SCRAMBLE_CTRL, _BIT4) == 0x00))
    {
        // Try Scramble Seed = 0xFFFE
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);

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
bit ScalerDpMacDphyRx1MeasureLaneCDRClk(EnumDpLinkRate enumDpLinkRate, BYTE ucDpMacRx1LaneNumber)
{
    WORD usCDRClockCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    switch(enumDpLinkRate)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _DP_LINK_UHBR20:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_UHBR20_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_UHBR20_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_UHBR13_5:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_UHBR13_5_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_UHBR10:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_UHBR10_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_UHBR10_SAVED >> 4))
            {
                return _TRUE;
            }

            break;
#endif
        case _DP_LINK_HBR3_9G:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR3_9G_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR3:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR3_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR3_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR2:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR2_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR2_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_HBR_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_HBR_SAVED >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - _DP_RX_VCO_TARGET_COUNT_1000_RBR_SAVED)) > (_DP_RX_VCO_TARGET_COUNT_1000_RBR_SAVED >> 4))
            {
                return _TRUE;
            }

            break;
    }

    usCDRClockCount = ScalerDpMacDphyRx1SignalDetectMeasureCount(ucDpMacRx1LaneNumber, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_1000_CYCLE);

    if(usCDRClockCount == 0)
    {
        return _FALSE;
    }

    if(abs(ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) - usCDRClockCount) > (ScalerDpPhyRxTargetClock(enumInputPort, ucDpMacRx1LaneNumber) >> 7))
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
bit ScalerDpMacDphyRx1HdcpCheck(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1HdcpCheck_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1HdcpCheck_8b10b();
    }
}

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate SHA-1 Input
// Input Value  : Inpute Array, First Run
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Reset SHA Block counter
    SET_DP_MAC_DPHY_RX1_HDCP14_SHA_RESET();
    CLR_DP_MAC_DPHY_RX1_HDCP14_SHA_RESET();

    // Write SHA-1 Input Data, Total 512 bits
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte(PB0_31_SHA_DATA1, pucInputArray[ucLoopIndex * 4]);
        ScalerSetByte(PB0_32_SHA_DATA2, pucInputArray[1 + ucLoopIndex * 4]);
        ScalerSetByte(PB0_33_SHA_DATA3, pucInputArray[2 + ucLoopIndex * 4]);
        ScalerSetByte(PB0_34_SHA_DATA4, pucInputArray[3 + ucLoopIndex * 4]);

        // Enable write 32-bit data to SHA-1 block
        ScalerDpMacDphyRx1Hdcp14Sha1DataWrite();
    }

    ScalerDpMacDphyRx1HDCPAuthShaRun(((ucCalCount == 0x00) ? _TRUE : _FALSE));
}
#endif

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx1LaneSwapSelect_8b10b(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
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
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);
        }
        else
        {
            // Pin Assignment E PN Swap
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);
        }

        switch(ScalerTypeCRxGetPinAssignment(enumInputPort))
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
                }

                break;

            default:
            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                // DP Lane Swap Setting
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));

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
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
            }
        }
        else
        {
            if((ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
            }
        }
    }
    else
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    {
        // DP PN Swap Setting
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

        // DP Lane Swap Setting
        ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
        ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
        ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
        ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
    }

    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_3, ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_2, ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_1, ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_0, ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_3, (ScalerGetBit(PB0_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_2, (ScalerGetBit(PB0_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_1, (ScalerGetBit(PB0_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_0, (ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0))));

    if((ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) != _TRUE) && (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) != _BIT7))
    {
        ucClockLaneSelect = (ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0)) << 6);
    }

    // MAC Clock from PHY Lane Selection
    ScalerSetBit(PB0_02_PHY_DIG_RESET2_CTRL, ~(_BIT7 | _BIT6), ucClockLaneSelect);
}

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1CheckHdcpCpirqStatus_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
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
void ScalerDpMacDphyRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    switch(enumDpMstBackup)
    {
        case _DP_MST_BACKUP_INFO:

            if((ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
               (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS))
            {
                // Backup MST Enable
                g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup = _TRUE;

                // Backup Link Config
                g_stDpMacDphyRx1MiscInfo.ucDpMacRxLinkRateBackup = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00);
                g_stDpMacDphyRx1MiscInfo.ucDpMacRxLaneCountBackup = (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F);
                g_stDpMacDphyRx1MiscInfo.ucDpMacRxCodingTypeBackup = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x08);

#if(_DP_RX_FEC_SUPPORT == _ON)
                g_stDpMacDphyRx1MiscInfo.ucDpMacRxFecReadyBackup = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x20);
#endif

                // Backup TimeSlot Info
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
                {
                    memcpy(g_pucDpMacDphyRx1MstTimeSlotBackup, (volatile BYTE xdata *)P9F_02_STHD_CTRL_2, sizeof(g_pucDpMacDphyRx1MstTimeSlotBackup));
                }
                else
#endif
                {
                    memcpy(g_pucDpMacDphyRx1MstTimeSlotBackup, (volatile BYTE xdata *)PB8_02_STHD_CTRL_2, sizeof(g_pucDpMacDphyRx1MstTimeSlotBackup));
                }

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
                {
                    g_pucDpMacDphyRx1MstStMuxBackup[enumSourceNum] = GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum);
                }
            }

            break;

        case _DP_MST_BACKUP_INFO_RESTORE:

            if(((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x00, 0x21) & _BIT0) == _BIT0) && (g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup == _TRUE))
            {
                // Enable MST Decode
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);

                // Restore TimeSlot Info
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
                {
                    memcpy((volatile BYTE xdata *)P9F_02_STHD_CTRL_2, g_pucDpMacDphyRx1MstTimeSlotBackup, sizeof(g_pucDpMacDphyRx1MstTimeSlotBackup));
                }
                else
#endif
                {
                    memcpy((volatile BYTE xdata *)PB8_02_STHD_CTRL_2, g_pucDpMacDphyRx1MstTimeSlotBackup, sizeof(g_pucDpMacDphyRx1MstTimeSlotBackup));
                }

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
                {
                    ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumSourceNum, g_pucDpMacDphyRx1MstStMuxBackup[enumSourceNum]);
                }
            }

            g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;

        case _DP_MST_BACKUP_INFO_RESET:
        default:

            g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
    }
}
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacDphyRx1PowerDataRecover_128b132b(void)
{
    // Enable DP Link Integrity Enable
    ScalerSetBit(P1F_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT5, _BIT5);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Set Type Value = 1 for AES 1
    ScalerSetByte(P1F_29_HDCP_TYPE_AES_1, 0x01);
#endif
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpCheck_128b132b(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Check for HDCP 2.2 Riv
    if(ScalerDpMacDphyRx1Hdcp2ReAuthStatusCheck() == _FALSE)
    {
        return _TRUE;
    }
#endif

    if(((ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
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
void ScalerDpMacDphyRx1CpIRQ_128b132b(EnumDpRxBStatusType enumBStatusType)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Disable HDCP 2.2 Module
            ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_22);

            // Disable HDCP2.2 Auth. Done
            ScalerSetBit(P1F_07_HDCP_DEBUG, ~_BIT0, 0x00);

            // Reset HDCP Block
            ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, _BIT0);
            ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, 0x00);

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
bit ScalerDpMacDphyRx1HdcpCheckEnabled_128b132b(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(ScalerGetBit(P1F_07_HDCP_DEBUG, _BIT0) == _BIT0)
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
bit ScalerDpMacDphyRx1HdcpCheckValid_128b132b(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(ScalerGetBit(P1F_07_HDCP_DEBUG, _BIT0) == _BIT0)
    {
        if((ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2ResetProc_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    // Disable HDCP2.2 Auth. Done
    ScalerSetBit(P1F_07_HDCP_DEBUG, ~_BIT0, 0x00);

    // Clear Type Value
    ScalerSetByte(P1F_28_HDCP_TYPE_AES_0, 0x00);

    // Clear Type Value
    ScalerSetByte(P1F_29_HDCP_TYPE_AES_1, 0x01);

    // Clear AES STx Type
    ScalerSetByte(P1F_2B_HDCP_ST_TYPE_0, 0x00);
    ScalerSetBit(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Reset HDCP Block
    ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, _BIT0);
    ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT0, 0x00);

    // Disable HDCP2.2
    ScalerDpHdcpRxSetHdcpMode(enumInputPort, _HDCP_22);
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void  ScalerDpMacDphyRx1Hdcp2CipherDataRestore_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);
    BYTE ucLoop = 0x00;

    ScalerDpAuxRxSetManualMode(enumInputPort);

    if(ScalerDpHdcpRxGetAuthDone(enumInputPort) == _TRUE)
    {
        // Reset HDCP2.2 Auth. Done
        ScalerSetBit(P1F_07_HDCP_DEBUG, ~_BIT0, 0x00);

        for(ucLoop = 0; ucLoop < 8; ucLoop++)
        {
            ScalerSetByte((P1F_08_RIV0 + ucLoop), g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxRiv[ucLoop]);
        }

        for(ucLoop = 0; ucLoop < 16; ucLoop++)
        {
            ScalerSetByte((P1F_18_HDCP_AES_CIPHER_KEY_15 + ucLoop), g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxAESCipher[ucLoop]);
        }

        // Set Stream 1~ Stream 2 Type
        ScalerSetBit(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] & 0xF0);

        // Set Stream 3~ Stream 6 Type
        ScalerSetByte(P1F_2B_HDCP_ST_TYPE_0, g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1]);

        // Enable HDCP2.2 Auth. Done
        ScalerSetBit(P1F_07_HDCP_DEBUG, ~_BIT0, _BIT0);

        DebugMessageHDCP2("[D1]Recover Hdcp2 Cipher Data", 0);
    }

    ScalerDpAuxRxSetAutoMode(enumInputPort);
}

//--------------------------------------------------
// Description  : Detect Dp Rx HDCP Link Veriffication Pattern (0x531F)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1HdcpDetectLvp_128b132b(void)
{
    if((ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
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
EnumDpHdcp2AESType ScalerDpMacDphyRx1Hdcp2GetStxType_128b132b(BYTE ucStreamId)
{
    switch(ucStreamId)
    {
        case _DP_ST_SOURCE1:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(P1F_2C_HDCP_ST_TYPE_1, (_BIT7 | _BIT6)) >> 6));

        case _DP_ST_SOURCE2:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(P1F_2C_HDCP_ST_TYPE_1, (_BIT5 | _BIT4)) >> 4));

        case _DP_ST_SOURCE3:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(P1F_2B_HDCP_ST_TYPE_0, (_BIT1 | _BIT0))));

        case _DP_ST_SOURCE4:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(P1F_2B_HDCP_ST_TYPE_0, (_BIT3 | _BIT2)) >> 2));

        case _DP_ST_SOURCE5:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(P1F_2B_HDCP_ST_TYPE_0, (_BIT5 | _BIT4)) >> 4));

        case _DP_ST_SOURCE6:

            return ScalerDpMacDphyRxHdcp2GetAESCipherType((EnumDpHdcp2AESCipherSet)(ScalerGetBit(P1F_2B_HDCP_ST_TYPE_0, (_BIT7 | _BIT6)) >> 6));

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
bit ScalerDpMacDphyRx1HdcpCheckLvp_128b132b(void)
{
    if(((ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
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
void ScalerDpMacDphyRx1LaneSwapSelect_128b132b(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
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
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);
        }
        else
        {
            // Pin Assignment E PN Swap
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
            ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);
        }

        switch(ScalerTypeCRxGetPinAssignment(enumInputPort))
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                    ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
                }

                break;

            default:
            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                // DP Lane Swap Setting
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));

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
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 6);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 4);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 2);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
            }
        }
        else
        {
            if((ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 4);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 2);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0) << 6);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 4);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 2);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3));
            }
        }
    }
    else
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    {
        // DP PN Swap Setting
        ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_3) << 7);
        ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_2) << 6);
        ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_1) << 5);
        ScalerSetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap(enumInputPort, _DP_LANE_0) << 4);

        // DP Lane Swap Setting
        ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_3) << 6);
        ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_2) << 4);
        ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_1) << 2);
        ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping(enumInputPort, _DP_LANE_0));
    }

    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_3, ScalerGetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT7) >> 7);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_2, ScalerGetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT6) >> 6);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_1, ScalerGetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT5) >> 5);
    ScalerDpPhyRxSetLanePNSwap(enumInputPort, _DP_LANE_0, ScalerGetBit(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT4) >> 4);

    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_3, (ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT7 | _BIT6)) >> 6));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_2, (ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT5 | _BIT4)) >> 4));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_1, (ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT3 | _BIT2)) >> 2));
    ScalerDpPhyRxSetLaneMux(enumInputPort, _DP_LANE_0, (ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0))));

    if((ScalerDpPhyRxGetPhyCtsFlag(enumInputPort) != _TRUE) && (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) != _BIT7))
    {
        ucClockLaneSelect = (ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0)) << 6);
    }

    // MAC Clock from PHY Lane Selection
    ScalerSetBit(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), ucClockLaneSelect);
}

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1CheckHdcpCpirqStatus_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    if((ScalerGetByte(P1F_05_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(P1F_06_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
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
WORD ScalerDpMacDphyRx1SignalDetectMeasureCount_128b132b(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit(P1F_F1_DP_SIG_DET_DP20_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
        case _DP_MEASURE_PERIOD_125_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00000
            ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            break;

        case _DP_MEASURE_PERIOD_250_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00001
            ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            break;

        case _DP_MEASURE_PERIOD_1000_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            break;
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(P1F_F2_DP_SIG_DET_DP20_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT7, 0x00);
    ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(P1F_F0_DP_SIG_DET_DP20_0, _BIT6) == _BIT6)
        {
            usDpMeasureCount = ((((WORD)ScalerGetByte(P1F_F3_DP_SIG_DET_DP20_3)) << 8) | ScalerGetByte(P1F_F4_DP_SIG_DET_DP20_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}
#endif // End of (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : VBIOS Lane Adjust
// Input Value  : DP Lane Count
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMacDphyRx1VbiosMsaCheck(bit bDeskewEnhanced)
{
    bit bMSACheckResult = _FALSE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    do
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), (((bDeskewEnhanced == _TRUE) ? _BIT7 : 0x00) | _BIT6));

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // SEC Reset
        ScalerSetBit(PB8_1E_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PB8_1E_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

        // Wait Two Frame Time to Get MSA
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(ScalerDpMacStreamRxVbiosMsaCheck(enumInputPort) == _TRUE)
        {
            bMSACheckResult = _TRUE;

            break;
        }
    }while(ScalerDpMacDphyRx1ChangeSrambleSeed() == _TRUE);

    if(ScalerDpAuxRxGetAssrModeEnable(enumInputPort) == _TRUE)
    {
        bMSACheckResult = ScalerDpMacDphyRx1VbiosAssrCheck(bMSACheckResult);
    }

    return bMSACheckResult;
}

//--------------------------------------------------
// Description  : Set DPRX SRAM CLK Gate
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx1HdcpSramClkGate(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Set DPRX SRAM CLK Gate Enable
        ScalerSetBit(PB0_A6_HDCP_DUMMY_1, ~_BIT2, _BIT2);
    }
    else
    {
        // Set DPRX SRAM CLK Gate Disable
        ScalerSetBit(PB0_A6_HDCP_DUMMY_1, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx1PowerDataRecover(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRx1PowerDataRecover_128b132b();
#endif
    ScalerDpMacDphyRx1PowerDataRecover_8b10b();
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx1PowerDataRecover_8b10b(void)
{
#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
    ScalerDpRxSetPhyToMacDphyMux(_DP_MAC_DPHY_RX1, ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1));
#endif

    // Reset Key download port and Enable HDCP FW Mode
    ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~(_BIT4 | _BIT0), _BIT4);

    // Set R0' Available HW Mode
    ScalerSetBit(PB0_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    // Set DPRX SRAM CLK Gate Enable
    ScalerDpMacDphyRx1HdcpSramClkGate(_ENABLE);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Set Type Value = 1 for AES 1
    ScalerSetByte(PB0_94_HDCP_TYPE_AES_1, 0x01);
#endif
}

#endif
