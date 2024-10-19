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
// ID Code      : ScalerDpMacDphyRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX_WDINT__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx/ScalerDpMacDphyRx.h"

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
// Description  : Set DP MAC Set Comma Detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetCommaDetect_WDINT(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0SetCommaDetect_WDINT(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1SetCommaDetect_WDINT(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2SetCommaDetect_WDINT(bEn);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxClkSelect_WDINT(EnumInputPort enumInputPort, EnumDpMacClkSelect enumClkSelect)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ClkSelect_WDINT(enumClkSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ClkSelect_WDINT(enumClkSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ClkSelect_WDINT(enumClkSelect);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpMacDphyRxDecodeCheck_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0DecodeCheck_WDINT();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1DecodeCheck_WDINT();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2DecodeCheck_WDINT();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Handle DP Hpd Irq Assert WD Timer Event
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxWDTimerEventHpdIrqAssertProc_WDINT(EnumInputPort enumInputPort)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = _DP_RX_AUX_AUTO_MODE;

    // Backup Aux Mode
    enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);

    // Check if Auto mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
    }

    // Check Link status again
    if(ScalerDpMacDphyRxDecodeCheck_WDINT(enumInputPort) == _FALSE)
    {
        if(ScalerDpAuxRxGetLTStatus_WDINT(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
        {
            ScalerDpAuxRxCancelLinkStatusIRQ_WDINT(enumInputPort);

            ScalerDpAuxRxDpcdLinkStatusReset_WDINT(enumInputPort, _DP_DPCD_LINK_STATUS_IRQ);

            if((ScalerDpAuxRxGetDpcdBitInfo_WDINT(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
               (ScalerDpAuxRxGetDpcdBitInfo_WDINT(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
            {
                ScalerDpAuxRxLinkStatusIRQ_WDINT(enumInputPort);
            }
        }
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Handle DP Related WD Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxWDTimerEventRebuildPhyProc_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0WDTimerEventRebuildPhyProc_WDINT();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1WDTimerEventRebuildPhyProc_WDINT();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2WDTimerEventRebuildPhyProc_WDINT();

            break;
#endif
        default:

            break;
    }
}

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Error Count Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecErrorCountSelect_WDINT(EnumInputPort enumInputPort, BYTE ucFECSelect)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
#if(_HW_DP_RX_FEC_ERROR_COUNT_SEL_DB_SUPPORT == _ON)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            ScalerSetBit_WDINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_WDINT(PB_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_WDINT(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_WDINT(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_WDINT(PC_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit_WDINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_WDINT(PB0_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_WDINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_WDINT(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_WDINT(P1F_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit_WDINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_WDINT(PC5_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_WDINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_WDINT(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_WDINT(PD2_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

        default:

            break;
    }
#else
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_WDINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_WDINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_WDINT(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_WDINT(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_WDINT(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_WDINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_WDINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_WDINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_WDINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_WDINT(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_WDINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_WDINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_WDINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_WDINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_WDINT(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

        default:

            break;
    }
#endif
}

//--------------------------------------------------
// Description  : FEC Error Lane Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecLaneSelect_WDINT(EnumInputPort enumInputPort, BYTE ucFECLane)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerSetBit_WDINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_WDINT(PC_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit_WDINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_WDINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit_WDINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_WDINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : FEC Mac Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecInitial_WDINT(EnumInputPort enumInputPort)
{
    BYTE ucDpFecSettingMainMacInfo = 0;
    EnumDpAuxRxModeStatus enumBackUpAuxModeMainStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);

#if(_DUAL_DP_SUPPORT == _ON)
    BYTE ucDpFecSettingSubMacInfo = 0;
    EnumDpAuxRxModeStatus enumBackUpAuxModeSubStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
            }

            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
            }

            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
            }

            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
            }

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(_D0_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(_D1_INPUT_PORT);
            }

            // Mac0 to D0 port, Mac1 to D1 port
            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(_D0_INPUT_PORT, 0x00, 0x01, 0x20);
            ucDpFecSettingSubMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(_D1_INPUT_PORT, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(_D0_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(_D0_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(_D1_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(_D1_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(_D0_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(_D1_INPUT_PORT);
            }

#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(_D1_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode_WDINT(_D2_INPUT_PORT);
            }

            // Mac1 to D1 port, Mac2 to D2 port
            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(_D1_INPUT_PORT, 0x00, 0x01, 0x20);
            ucDpFecSettingSubMacInfo = ScalerDpAuxRxGetDpcdInfo_WDINT(_D2_INPUT_PORT, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(_D1_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(_D1_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            ScalerDpMacDphyRxFecErrorCountSelect_WDINT(_D2_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect_WDINT(_D2_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(_D1_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode_WDINT(_D2_INPUT_PORT);
            }
#endif

            break;
#endif

        default:

            break;
    }
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx Auxless ALPM tDRL Calculate
// Input Value  : enumInputPort
// Output Value : tDRL time
//--------------------------------------------------
WORD ScalerDpMacDphyRxAuxlessAlpmTdrlTime_WDINT(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpAuxRxGetDpcdLinkRate_WDINT(enumInputPort))
    {
        case _DP_LINK_RBR:
            return _DP_AUXLESS_ALPM_TDRL_TIME_RBR;

        case _DP_LINK_HBR:
            return _DP_AUXLESS_ALPM_TDRL_TIME_HBR;

        case _DP_LINK_HBR2:
            return _DP_AUXLESS_ALPM_TDRL_TIME_HBR2;

        case _DP_LINK_HBR3:
            return _DP_AUXLESS_ALPM_TDRL_TIME_HBR3;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _DP_LINK_UHBR10:
            return _DP_AUXLESS_ALPM_TDRL_TIME_UHBR10;

        case _DP_LINK_UHBR13_5:
            return _DP_AUXLESS_ALPM_TDRL_TIME_UHBR13_5;

        case _DP_LINK_UHBR20:
            return _DP_AUXLESS_ALPM_TDRL_TIME_UHBR20;
#endif

        default:
            return _DP_AUXLESS_ALPM_TDRL_TIME_RBR;
    }
}

//--------------------------------------------------
// Description  : Mac Rx Auxless ALPM Initial
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxAuxlessAlpmEnable_WDINT(EnumInputPort enumInputPort, bit bEn)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0AuxlessAlpmEnable_WDINT(enumInputPort, bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1AuxlessAlpmEnable_WDINT(enumInputPort, bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2AuxlessAlpmEnable_WDINT(enumInputPort, bEn);

            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : bEnable, enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2EnableLinkIntegrityCheck_WDINT(bit bEnable, EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_WDINT(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_WDINT(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_WDINT(bEnable);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2EnableDecryption_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2EnableDecryption_WDINT();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2EnableDecryption_WDINT();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2EnableDecryption_WDINT();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2EnableAuthDone_WDINT(bit bEnable, EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2EnableAuthDone_WDINT(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2EnableAuthDone_WDINT(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2EnableAuthDone_WDINT(bEnable);

            break;
#endif
        default:

            break;
    }
}

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Set AES Type for Repeater
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2SetRepeaterAESType_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_WDINT();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2SetRepeaterAESType_WDINT();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2SetRepeaterAESType_WDINT();

            break;
#endif

        default:

            break;
    }
}
#endif
#endif
#endif
