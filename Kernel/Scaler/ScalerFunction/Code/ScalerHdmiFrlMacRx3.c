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
// ID Code      : ScalerHdmiFrlMacRx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIFRLMACRX3__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx3/ScalerHdmiFrlMacRx3.h"


#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructHdmiFrlCtrlInfo g_stHdmiFrlMacRx3CtrlInfo;

WORD g_usHdmiFrlMacRx3Hfront;
WORD g_usHdmiFrlMacRx3Hsync;
WORD g_usHdmiFrlMacRx3Hback;
WORD g_usHdmiFrlMacRx3Hactive;
WORD g_usHdmiFrlMacRx3Htotal;
WORD g_usHdmiFrlMacRx3Vfront;
WORD g_usHdmiFrlMacRx3Vsync;
WORD g_usHdmiFrlMacRx3Vback;
WORD g_usHdmiFrlMacRx3Vactive;
WORD g_usHdmiFrlMacRx3Vtotal;
WORD g_usHdmiFrlMacRx3FrameRate;

DWORD g_ulHdmiFrlMacRx3PixelClkValue; // Unit:kHz

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
DWORD g_ulHdmiFrlMacRx3DSCClkValue; // Unit:0.1MHz
#endif

BYTE g_ucHdmiFrlMacRx3AviInfo;

WORD g_usHdmiFrlMacRx3NativeHtotal;

StructHdmiFrlIrqStatus g_stHdmiFrlMacRx3IrqStatus;

WORD g_usHdmiFrlMacRx3OffMeasureCount;

BYTE g_ucHdmiFrlMacRx3ScdcStatusFlag;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial for FRL Port
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ScanInitial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    ScalerHdmiFrlMacRx3Initial(enumInputPort);

    ScalerHdmiFrlMacRx3InterruptInitial();

    DebugMessageRx3("FRL Rx3: initial", 0);
}

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Config EMP SRAM
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3EmpSramSetting(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // [7] VS Enable; [6] DHDR Enable; [4] Share mode
        BYTE ucEmpConfig = 0x00;

        // set share mode
        ucEmpConfig = _BIT4;

#if((_DM_FUNCTION == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        // Enable VS IRQ & w1c all flag
        ScalerSetBit(P67_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if(_HDMI_SBTM_SUPPORT == _ON)
        // Detect VS EMP w/ org_id and tag
        ScalerSetBit(P67_B9_VS_EMP_1A, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // org id & tag
        ScalerSetByte(P67_BC_VS_ORG_ID, _HDMI21);

        ScalerSetByte(P67_BA_VS_EMP_1B, 0x00);
        ScalerSetByte(P67_BB_VS_EMP_1C, 0x03);
#elif(_DM_FUNCTION == _ON)
        // Detect VS EMP w/ org_id only
        ScalerSetBit(P67_B9_VS_EMP_1A, ~(_BIT7 | _BIT6), _BIT6);

        // org id
        ScalerSetByte(P67_BC_VS_ORG_ID, _VENDOR_SPECIFIC);
#endif
        // Enable VS EMP stored
        ucEmpConfig |= _BIT7;
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
        // Enable D-HDR IRQ & w1c all flag
        ScalerSetBit(P67_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Enable D-HDR EMP stored
        ucEmpConfig |= _BIT6;
#endif
        // Set EMP Config
        ScalerSetBit(P67_C8_HDMI_EMP_SRAM_CTRL0, ~(_BIT7 | _BIT6 | _BIT4), ucEmpConfig);
    }
    else
    {
        // Disable EMP stored
        ScalerSetBit(P67_C8_HDMI_EMP_SRAM_CTRL0, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P67_B9_VS_EMP_1A, ~(_BIT7 | _BIT6), 0x00);

        // [7] Disable VS/ D-HDR IRQ
        ScalerSetBit(P67_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit(P67_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Enable/Disable RSV IRQ_en
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RoundRobinIrqEnable(bit bEnable)
{
    bEnable = bEnable;

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
    BYTE ucRsv = 0;

    for(ucRsv = 0; ucRsv < 4; ucRsv++)
    {
        ScalerHdmiFrlMacRx3RsvIrqEnable(ucRsv, bEnable);
    }
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable RSV IRQ_en
// Input Value  : RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RsvIrqEnable(EnumHdmiRsvNumber enumRsvNumber, bit bEnable)
{
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            if(bEnable == _ENABLE)
            {
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT5);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT5);
            }
            break;

        case _HDMI_RSV_1:
            if(bEnable == _ENABLE)
            {
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT6);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT1, _BIT1);
            }
            else
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT1, 0x00);
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT6);
            }
            break;

        case _HDMI_RSV_2:
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT2, _BIT2);
            }
            else
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT2, 0x00);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
            }
            break;

        case _HDMI_RSV_3:
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~_BIT3, 0x00);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
            }
            break;

        case _HDMI_RSV_4:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            }
            else
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            }
            break;

        case _HDMI_RSV_5:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }
            else
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            break;

        case _HDMI_RSV_6:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }
            else
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }
            break;

        case _HDMI_RSV_7:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
            }
            else
            {
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
            }
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Initialize RSV for HDMI VSIF
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RsvInitial(void)
{
    // Specify Packet Detect Type
    ScalerSetByte(P77_D4_PORT_PAGE77_HDMI_PTRSV6, _HDMI_AVI_INFO_TYPE);

    ScalerSetByte(P77_D3_PORT_PAGE77_HDMI_PTRSV5, _HDMI_GENERAL_CONTROL_TYPE);

#if(_HDMI_HDR10_SUPPORT == _ON)
    ScalerSetByte(P77_D2_PORT_PAGE77_HDMI_PTRSV4, _HDR_INFO_TYPE);
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    ScalerSetByte(P77_CF_HDMI_PTRSV7, _SPD_INFO_TYPE);
    ScalerSetBit(P77_D7_HDMI_SHDR_IE_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

    // Freesync Replay disable
    ScalerSetBit(P77_D6_HDMI_SHDR_IE, ~_BIT4, 0x00);

    // PR6 = 2b'10 is Replay, Other is Live Capture
    ScalerSetBit(P77_D6_HDMI_SHDR_IE, ~(_BIT3 | _BIT2), _BIT3);
#endif

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) && (_HDMI_VSIF_RCV_BY_RR == _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_43_PORT_PAGE77_HDMI_PTRSV0, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_44_PORT_PAGE77_HDMI_PTRSV1, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_A4_PORT_PAGE77_HDMI_PTRSV_2, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_A5_PORT_PAGE77_HDMI_PTRSV_3, _SPD_INFO_TYPE);

    // write Round Robin tag
    ScalerSetByte(P77_DD_PKT_ROUND_ROBIN_PT0, _HDMI_VSIF_TYPE);
    ScalerSetByte(P77_DE_PKT_ROUND_ROBIN_PT1, _HDMI_VSIF_TYPE);
    ScalerSetByte(P77_DF_PKT_ROUND_ROBIN_PT2, _SPD_INFO_TYPE);
#elif((_HDMI_SPD_IF_RCV_BY_RR == _ON) && (_HDMI_VSIF_RCV_BY_RR != _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_43_PORT_PAGE77_HDMI_PTRSV0, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_44_PORT_PAGE77_HDMI_PTRSV1, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_A4_PORT_PAGE77_HDMI_PTRSV_2, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_A5_PORT_PAGE77_HDMI_PTRSV_3, _SPD_INFO_TYPE);

    // write Round Robin tag
    ScalerSetByte(P77_DD_PKT_ROUND_ROBIN_PT0, _SPD_INFO_TYPE);
    ScalerSetByte(P77_DE_PKT_ROUND_ROBIN_PT1, _SPD_INFO_TYPE);
    ScalerSetByte(P77_DF_PKT_ROUND_ROBIN_PT2, _SPD_INFO_TYPE);
#elif((_HDMI_SPD_IF_RCV_BY_RR != _ON) && (_HDMI_VSIF_RCV_BY_RR == _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_43_PORT_PAGE77_HDMI_PTRSV0, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_44_PORT_PAGE77_HDMI_PTRSV1, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_A4_PORT_PAGE77_HDMI_PTRSV_2, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_A5_PORT_PAGE77_HDMI_PTRSV_3, _HDMI_VSIF_TYPE);

    // write Round Robin tag
    ScalerSetByte(P77_DD_PKT_ROUND_ROBIN_PT0, _HDMI_VSIF_TYPE);
    ScalerSetByte(P77_DE_PKT_ROUND_ROBIN_PT1, _HDMI_VSIF_TYPE);
    ScalerSetByte(P77_DF_PKT_ROUND_ROBIN_PT2, _HDMI_VSIF_TYPE);
#endif

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
    // ENABLE Round Robin
    ScalerSetBit(P77_B2_TMDS_DBB2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : Initialize FRL MAC setting for search
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3Initial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // Set Lane swap and PN swap
    ScalerHdmiFrlMacRx3PnSwapConfig(enumInputPort);

#if(_HDMI_FRL_MAC_RX3_LINK_TRAINING_BYPASS == _ON)
    // Set MAC RX3 is FRL
    ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, _BIT6);

    // Set FRL Rate
    ScalerHdmiFrlMacRxSetDxFrlRate(enumInputPort, ScalerHdmiFrlMacRxGetDxMaxFrlRate(enumInputPort));

    if(ScalerHdmiFrlMacRxGetDxFrlRate(enumInputPort) >= _HDMI_FRL_RATE_6G_4LANES)
    {
        // set 4 lane mode and FRL
        ScalerSetBit(P67_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P68_10_HDMI21_RS_0, ~_BIT2, _BIT2);
    }
    else
    {
        // set 3 lane mode and FRL
        ScalerSetBit(P67_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P68_10_HDMI21_RS_0, ~_BIT2, 0x00);
    }
#endif

    ScalerHdmiFrlMacRx3RoundRobinIrqEnable(_DISABLE);

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
    // Inactive EMP SRAM
    ScalerHdmiFrlMacRx3EmpSramSetting(_DISABLE);
#endif

    // If FLT_Ready = 0, Set Link Training Initial State = LTS2
    if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, _BIT6) == 0x00)
    {
        SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);
    }

    // Disable DPF output
    SET_HDMI_FRL_RX3_DPF_RGB_CLK_OUTPUT_DISABLE();

    // Disable DPF format gen
    ScalerSetBit(P68_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // Disable DPF CLK
    ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Enable DPF VS/HS Synchronize(C version ECO)
    ScalerSetBit(P68_70_DPF_CTRL_0, ~(_BIT6 | _BIT3), _BIT3);

    // Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P68_26_HDMI21_DI_0, ~(_BIT5 | _BIT4), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P77_C8_HDMI_APC, ~_BIT0, 0x00);

    ScalerHdmiFrlMacRx3WatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD | _HDMI_FRL_DPF_FIFO_WD | _HDMI_EMP_TIMEOUT_WD), _DISABLE);

    // Deep Color Mode detection auto
    ScalerSetBit(P77_B8_TMDS_DPC1, ~_BIT2, _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_02_PORT_PAGE77_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2), (_BIT6 | _BIT3));

    // Enable BCH ACC(C version ECO)
    ScalerSetBit(P68_31_HDMI21_FRL_1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1), _BIT1);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_32_PORT_PAGE77_HDMI_WDCR1, ~_BIT5, _BIT5);

    // RSV Assignment
    ScalerHdmiFrlMacRx3RsvInitial();

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_45_PORT_PAGE77_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_46_PORT_PAGE77_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_47_PORT_PAGE77_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_AA_PORT_PAGE77_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_AB_PORT_PAGE77_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Enable HDMI 2.1 SCDC Module
    ScalerSetBit(P72_31_HDMI_CTRL_31, ~_BIT7, _BIT7);

    // Set Unlock when continue 2 super block has no SR/SSB
    ScalerSetBit(P77_16_HDMI21_FRL_CED_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT0);

    // Set CED checksum calculated by HW after ver. E
    ScalerSetBit(P72_28_HDMI_CTRL_28, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

    // Disable DSC EMP IRQ
    ScalerSetBit(P67_52_EMP_DSC, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set EMP time out 10 MTWs
    ScalerSetBit(P67_55_EMP_TIMEOUT_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

    // Source hasn't send out video before timeout, Sink enter no signal then switch port,
    // So Sink need check FRL signal in HDMI21Initial.
    if((ScalerHdmiFrlMacRxGetDxFrlRate(enumInputPort) != _HDMI_FRL_RATE_NONE) && (ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == 0x00))
    {
        // turn on ACDR
        ScalerTmdsPhyRxFrlSetAcdr(enumInputPort);

        // if SCDC 0x40 changed, set status update bit
        if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, _BIT6) == 0x00)
        {
            // Set FLT_ready
            ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT6, _BIT6);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
            // Clear SCDC 0x40[7] DSC dec fail
            ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
            // Set Status update
            ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
        }

        // Clear Set PHY flag
        CLR_HDMI_FRL_MAC_RX3_PHY_SET();

        // Set Rebuild PHY event
        SET_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT();
    }

    // Enable HDMI HPD IRQ Enable
    // ScalerSetBit(P72_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Initialize FRL Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3InterruptInitial(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    // Enable link training related IRQ
    ScalerSetBit(P72_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT2));

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    // Enable "w1c of status update" IRQ
    ScalerSetBit(P72_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT0);
#endif

    if((GET_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_PHY_SET() == _FALSE))
    {
        // Sel Lane0 to measure transition as default
        ScalerTmdsPhyRxTransitionDataLaneSelect(enumMappingPort, 0);

        // turn on transition detection IRQ
        ScalerSetBit(P77_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

        // Enable transition data from PHY
        ScalerTmdsPhyRxTransitionDataEnable(enumMappingPort, _ENABLE);

        // turn on transition detection
        ScalerSetBit(P77_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, _BIT7);
    }

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    // Clear IRQ Pending Flag
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_60_PORT_PAGE77_HDMI_INTCR, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
#endif

    SET_INTERRUPT_ENABLE_STATUS(_INT_TMDS, _ENABLE);
}

#if(_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1)
//--------------------------------------------------
// Description  : Signal PreDetection for FRL(Power Normal)
// Input Value  : Input Port
// Output Value : True : FRL Signal Detected
//              : False : No Signal
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RDCHdmi21Test(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if(ScalerGetByte(P67_2A_HDMI21_DPHY_D1) == 0x00)
    {
        ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 4, 6);

        // ScalerSetByte(P7C_50_DIG_00, 0xFF);
        // ScalerSetBit(P7C_52_DIG_02, ~_BIT4, _BIT4);

        ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, _BIT6);
        ScalerSetBit(P77_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);
        ScalerSetBit(P67_28_HDMI21_DPHY_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        ScalerSetByte(P67_2A_HDMI21_DPHY_D1, 0x10);

        DebugMessageRx3("FRL Rx3: PHY initial", 0);

        while(1)
        {
            ScalerHdmiFrlMacRx3LtpCheck();

            ScalerDebug();
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Signal PreDetection for FRL(Power Normal)
// Input Value  : Input Port
// Output Value : True : FRL Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3NormalPreDetect(void)
{
#if(_HDMI_FRL_MAC_RX3_LINK_TRAINING_BYPASS == _ON)
    BYTE ucTemp = 0;
    BYTE ucSetPhyLoop = 0;
    BYTE ucFreqCorrect = 0;
#endif

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

#if(_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1)
    ScalerHdmiFrlMacRx3RDCHdmi21Test();
#endif

#if(_HDMI_FRL_MAC_RX3_LINK_TRAINING_BYPASS == _OFF)

    switch(GET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE())
    {
        case _HDMI_FRL_LT_LTSL:
        case _HDMI_FRL_LT_LTS2:

            // if FLT_ready = 0
            if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, _BIT6) == 0x00)
            {
                // Set FLT_ready
                ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT6, _BIT6);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
                // Clear SCDC 0x40[7] DSC dec fail
                ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
                // Set Status update
                ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
            }

            SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS3);
            break;

        case _HDMI_FRL_LT_LTS3:

            break;

        case _HDMI_FRL_LT_LTS3_LFSR:

            break;

        case _HDMI_FRL_LT_LTSP_GAP:

            if((GET_HDMI_FRL_MAC_RX3_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX3_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)))
            {
                // Switch to HDMI 2.1 SCDC Module
                ScalerSetBit(P72_31_HDMI_CTRL_31, ~_BIT7, _BIT7);

                // Start CED count
                ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Set CED Valid
                ScalerSetBit(P77_08_HDMI21_FRL_CED_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

                if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Set Lane3 CED Valid
                    ScalerSetBit(P77_08_HDMI21_FRL_CED_0, ~_BIT0, _BIT0);
                }

                // Enable RS count and set valid and enable RS_update flag
                ScalerSetBit(P68_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));
                ScalerSetBit(P68_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));

                // Clear FW RS err flag
                ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

                // Enable FW RS count
                ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT1));

                CLR_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT();

                // Set HDMI2.1 Reactive time
                SET_HDMI_FRL_MAC_RX3_REACTIVE_SEARCH_TIME();

                SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSP_FRL_START);
            }
            else
            {
                DebugMessageRx3("FRL Rx3: Lane Lock error", ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort));
            }
            break;

        case _HDMI_FRL_LT_LTSP_FRL_START:

            // check CED error and channel lock.
            if((GET_HDMI_FRL_MAC_RX3_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX3_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) &&
               (ScalerHdmiFrlMacRx3CedCheck() == _TRUE))
            {
            }

            // check RSED error
            if(ScalerHdmiFrlMacRx3RsedCheck() == _TRUE)
            {
            }

            if((GET_HDMI_FRL_MAC_RX3_FRL_START_EVENT() == _TRUE) || (GET_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT() == _TRUE))
            {
                CLR_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT();

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
                // Clear Signal Detection flag
                CLR_HDMI_FRL_MAC_RX3_SIGNAL_DETECTING();
#endif

                SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSEND);

                g_usHdmiFrlMacRx3OffMeasureCount = ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE0);

                DebugMessageRx3("FRL Rx3: F_R =", ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort));

                return _TRUE;
            }

            break;

        case _HDMI_FRL_LT_LTSEND:

            // check CED error
            if(ScalerHdmiFrlMacRx3CedCheck() == _TRUE)
            {
                DebugMessageRx3("FRL Rx3: CED pass", 0);
            }

            // check RSED error
            if(ScalerHdmiFrlMacRx3RsedCheck() == _TRUE)
            {
                DebugMessageRx3("FRL Rx3: RSED pass", 0);
            }

            return _TRUE;

            break;

        default:
            break;
    }

#else // else of #if(_HDMI_FRL_MAC_RX3_LINK_TRAINING_BYPASS == _OFF)

    if(ScalerGetByte(P67_2A_HDMI21_DPHY_D1) == 0x00)
    {
        SET_INTERRUPT_ENABLE_STATUS(_INT_TMDS, _DISABLE);

        while(ucSetPhyLoop < 20)
        {
            // Set PHY
            if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_12G)
            {
                ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 4, 12);
            }
            else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_10G)
            {
                ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 4, 10);
            }
            else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_8G)
            {
                ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 4, 8);
            }
            else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_4LANES)
            {
                ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 4, 6);
            }
            else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_3LANES)
            {
                ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 3, 6);
            }
            else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_3G)
            {
                ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 3, 3);
            }

            // Check CDR Freq.
            ScalerSetBit(P77_E9_HDMI_TRANSDET_CTRL5, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P77_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, _BIT7);

            ucFreqCorrect = 0;

            for(ucTemp = 0; ucTemp < 4; ucTemp++)
            {
                ScalerTmdsPhyRxTransitionDataLaneSelect(enumMappingPort, ucTemp);

                // Pop result
                ScalerSetBit(P77_E8_HDMI_TRANSDET_CTRL4, ~_BIT7, _BIT7);

                DELAY_XUS(100);

                if(ScalerGetByte(P77_FE_HDMI_TRANSDET_RESULT_M) == 0x30)
                {
                    ucFreqCorrect++;
                }
            }

            if(ucFreqCorrect == 4)
            {
                DebugMessageRx3("FRL Rx3: Set PHY ucSetPhyLoop", ucSetPhyLoop);
                break;
            }

            ucSetPhyLoop ++;
        }

        SET_INTERRUPT_ENABLE_STATUS(_INT_TMDS, _ENABLE);

        // Enable HDCP2.2 & Disable HDCP 1.4 Module
        ScalerSetBit(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, _BIT7);
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT0, 0x00);

        // Reset PHY -> MAC Interface
        ScalerSetBit(P77_A7_TMDS_PWDCTL, ~_BIT4, 0x00);
        ScalerSetBit(P77_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

        ScalerSetByte(P67_2A_HDMI21_DPHY_D1, 0x80);

        DebugMessageRx3("FRL Rx3: PHY initial", 0);

        // Enable disparity
        if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            // Start disparity calculation 4 lanes
            ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Start disparity calculation 3 lanes
            ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
        }

        // Disable CED and RS error count
        ScalerSetBit(P77_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit(P68_10_HDMI21_RS_0, ~_BIT5, 0x00);
        ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

        ScalerTimerDelayXms(2);

        // Enable CED and RSED
        if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            // Start CED 4 lanes
            ScalerSetBit(P77_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Enable lock transition IRQ, need 3 super blocks ~37us@3G
            ScalerSetByte(P77_17_HDMI21_FRL_CED_15, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // DebugMessageRx3("CED enable", ScalerGetByte(P77_08_HDMI21_FRL_CED_0));
        }
        else
        {
            // Start CED 3 lanes
            ScalerSetBit(P77_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

            // Enable lock transition IRQ, need 3 super blocks ~37us@3G
            ScalerSetByte(P77_17_HDMI21_FRL_CED_15, (_BIT2 | _BIT1 | _BIT0));
        }

        // Start CED count
        ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable RS count and set valid
        ScalerSetBit(P68_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));
        ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT1));

        // check CED error and channel lock.
        if((GET_HDMI_FRL_MAC_RX3_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_LANE2_LOCK() == _TRUE) &&
           ((GET_HDMI_FRL_MAC_RX3_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) &&
           (ScalerHdmiFrlMacRx3CedCheck() == _TRUE))
        {
            DebugMessageRx3("FRL Rx3: LTSEND", ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_31_PORT_PAGE72_HDMI_SCDC_31, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            return _TRUE;
        }
    }
#endif

    if(GET_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3FirstActiveProc(EnumSourceType enumSourceType)
{
    enumSourceType = enumSourceType;
}

//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3HdmiAVMuteProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    enumMappingPort = enumMappingPort;

    // if AVMute Has been triggered
    if(ScalerGetBit(P77_CB_HDMI_SR, (_BIT7 | _BIT6)) == _BIT7)
    {
        // Clear AVMute Flag
        ScalerSetBit(P77_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT7);

        // Disable HDMI AVMute WD
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT7, 0x00);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
        {
            // Disable DSC force background
            ScalerDscDecoderForceBackgroundSetting(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3), _DISABLE);
        }
#endif

        // Enable Audio Output
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Enable HDMI AVMute WD
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT7, _BIT7);
    }
}

#if(_3DDI_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get 3DDI available
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3GetInterlace3ddiAvaible(void)
{
    // 3DDI Check for 2x clk from Mac
    if((ScalerGetBit(P68_4A_FRL_MEASURE_A, _BIT4) == _BIT4) && (g_ulHdmiFrlMacRx3PixelClkValue < (_3DDI_PCLK_LIMIT + 10000)))
    {
        return _TRUE;
    }

    return _FALSE;
}

#endif

//--------------------------------------------------
// Description  : CED check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3CedCheck(void)
{
    WORD usLane0CedCounter = 0;
    WORD usLane1CedCounter = 0;
    WORD usLane2CedCounter = 0;
    WORD usLane3CedCounter = 0;
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    // CED is enable?
    if(ScalerGetBit(P77_09_HDMI21_FRL_CED_1, _BIT6) == _BIT6)
    {
        // Pop CED counter
        ScalerSetByte(P77_0A_HDMI21_FRL_CED_2, 0x80);
        usLane0CedCounter = (((ScalerGetByte(P77_0A_HDMI21_FRL_CED_2) & 0x7F) << 8) | (ScalerGetByte(P77_0B_HDMI21_FRL_CED_3)));
        usLane1CedCounter = (((ScalerGetByte(P77_0C_HDMI21_FRL_CED_4) & 0x7F) << 8) | (ScalerGetByte(P77_0D_HDMI21_FRL_CED_5)));
        usLane2CedCounter = (((ScalerGetByte(P77_0E_HDMI21_FRL_CED_6) & 0x7F) << 8) | (ScalerGetByte(P77_0F_HDMI21_FRL_CED_7)));
        usLane3CedCounter = (((ScalerGetByte(P77_10_HDMI21_FRL_CED_8) & 0x7F) << 8) | (ScalerGetByte(P77_11_HDMI21_FRL_CED_9)));

        // check CED error and channel lock.
        if((usLane0CedCounter == 0) && (usLane1CedCounter == 0) && (usLane2CedCounter == 0) && ((usLane3CedCounter == 0) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : RSED check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3RsedCheck(void)
{
    // RSED is enable?
    if(ScalerGetBit(P68_19_HDMI21_FW_RS_5, _BIT7) == _BIT7)
    {
        if((ScalerGetByte(P68_14_HDMI21_FW_RS_0) == 0x00) && (ScalerGetByte(P68_15_HDMI21_FW_RS_1) == 0x00) && (ScalerGetByte(P68_16_HDMI21_FW_RS_2) == 0x00) && (ScalerGetByte(P68_17_HDMI21_FW_RS_3) == 0x00))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDMI2.1 Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source Type
//--------------------------------------------------
EnumSourceType ScalerHdmiFrlMacRx3ScanInputPort(EnumPortType enumPortType)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
    bit bFreeSyncReceive = _TRUE;
#endif

    enumPortType = enumPortType;

    // if has HPD event, Link Training not finsih, PHY not set or FRL_rate changed, it will skip ScanInputPort
#if(_HDMI_FRL_MAC_RX3_LINK_TRAINING_BYPASS == _OFF)
    if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) || (GET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE() != _HDMI_FRL_LT_LTSEND) || (GET_HDMI_FRL_MAC_RX3_PHY_SET() != _TRUE) || (GET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    // CTS is testing
    if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_30_PORT_PAGE72_HDMI_SCDC_30, _BIT1) == _BIT1)
    {
        return _SOURCE_NONE;
    }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    // Clear DRR flag
    ScalerTmdsMacRxSetFreesyncProc(enumMappingPort, _DISABLE);
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    // Clear Freesync replay flag
    ScalerTmdsMacRxSetFreesyncReplayProc(enumMappingPort, _DISABLE);

    // Set Freesync Replay disable
    ScalerSetBit(P77_D6_HDMI_SHDR_IE, ~_BIT4, 0x00);
#endif

    // FRL format check
    if(ScalerHdmiFrlMacRx3FrlVideoCheck() == _FALSE)
    {
        DebugMessageRx3("FRL Rx3: Video fail", 0);
        return _SOURCE_NONE;
    }

    // Measure check
    if(ScalerHdmiFrlMacRx3MeasureCheck() == _FALSE)
    {
        DebugMessageRx3("FRL Rx3: Measure fail", 0);
        return _SOURCE_NONE;
    }

    // Clear Info Packet SRAM
    ScalerSetBit(P77_AD_TMDS_CPS, ~_BIT3, _BIT3);
    ScalerSetBit(P77_AD_TMDS_CPS, ~_BIT3, 0x00);

    // Reset All Pkt Received Flag (EMP & RSV)
    ScalerHdmiFrlMacRx3ResetAllPacketReceiveStatus();

    ScalerHdmiFrlMacRx3RoundRobinIrqEnable(_ENABLE);

    // HDMI packet detect
    ScalerHdmiFrlMacRx3PacketDetect(_WAIT);

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
    // Active EMP SRAM
    ScalerHdmiFrlMacRx3EmpSramSetting(_ENABLE);
#endif

    ScalerHdmiFrlMacRx3VideoSetting();

    SET_COLOR_DEPTH(enumMappingPort, ScalerHdmiFrlMacRx3GetColorDepth());

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
    // Get EMP packet
    ScalerHdmiFrlMacRx3EmpPacketDetect(_WAIT);
#endif

    // DPF Setting
    if(ScalerHdmiFrlMacRx3DisplayFormatSetting() == _FALSE)
    {
        return _SOURCE_NONE;
    }

    // DPLL and Tracking setting
    if(ScalerHdmiFrlMacRx3StreamClkRegenerate() == _FALSE)
    {
        return _SOURCE_NONE;
    }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
    if(bFreeSyncReceive == _TRUE)
#else
    if(GET_HDMI_RX3_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
#endif
    {
        ScalerTmdsMacRxSetFreesyncProc(enumMappingPort, _ENABLE);

        // Get SPD Free Sync Vfreq Max
        SET_DRR_VFREQ_MAX(GET_HDMI_RX3_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10);    // 0.1Hz
        SET_DRR_VFREQ_MIN(GET_HDMI_RX3_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10);
    }
    else
#endif
    {
#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
        if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE)
        {
#if(_HDMI21_VRR_SUPPORT == _ON)
            WORD usSourceBrr = 0x00;

            // Get Base Frame Rate from SRC
            if((GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_VIC) != 0x00))
            {
                usSourceBrr = ((WORD)ScalerTmdsMacRxGetVicVfreqParameter(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_VIC)) * 10);
                DebugMessageRx3("VRR BRR (AVI IF VIC)", usSourceBrr);
            }
            else if((GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerHdmiFrlMacRx3Rsv6GetAviInfo(_AVI_INFO_FR) != 0x00))
            {
                usSourceBrr = (ScalerTmdsMacRxGetOvtVfreqParameter(ScalerHdmiFrlMacRx3Rsv6GetAviInfo(_AVI_INFO_FR)) * 10);
                DebugMessageRx3("VRR BRR (AVI IF OVT)", usSourceBrr);
            }
            else if(ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_BASE_REFRESH_RATE) != 0x00)
            {
                usSourceBrr = ((WORD)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_BASE_REFRESH_RATE) * 10);
                DebugMessageRx3("VRR BRR (VTEM)", usSourceBrr);
            }
            else
            {
                DebugMessageRx3("VRR BRR Error!!", 0x00);
            }

            // Get max Vfmax from SRC BRR
            SET_DRR_VFREQ_MAX(usSourceBrr);

            if(((bit)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _ENABLE)
            {
                SET_TMDS_MAC_RX3_HDMI21_VRR_EN();
                DebugMessageRx3("FRL Rx3: VRR_EN", 0x00);
            }
            else
            {
                CLR_TMDS_MAC_RX3_HDMI21_VRR_EN();
                DebugMessageRx3("FRL Rx3: VRR_DIS", 0x00);
            }

            if(((bit)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _ENABLE)
            {
                SET_TMDS_MAC_RX3_HDMI21_QMS_EN();
                DebugMessageRx3("FRL Rx3: QMS_EN", 0x00);
            }
            else
            {
                CLR_TMDS_MAC_RX3_HDMI21_QMS_EN();
                DebugMessageRx3("FRL Rx3: QMS_DIS", 0x00);
            }

#if(_HDMI_FORCE_VRR_SUPPORT == _ON)
            // Get SPD Free Sync Vfreq Max
            SET_DRR_VFREQ_MAX(0);
            SET_DRR_VFREQ_MIN(0);
#endif
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
            SET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR(ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_FVA_FACTOR_M1) + 1);
#endif
        }
#endif
    }

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    if(GET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED() == _TRUE)
    {
        ScalerTmdsMacRxSetFreesyncReplayProc(enumMappingPort, _ENABLE);

        // Set Freesync Replay enable
        ScalerSetBit(P77_D6_HDMI_SHDR_IE, ~_BIT4, _BIT4);
    }
#endif

#if(_HDMI_FRL_MAC_RX3_LFSR_TEST_MODE == _ON)
    while(_TRUE)
    {
        // ScalerHdmiFrlMacRx3LtpCheck();
        ScalerHdmiFrlMacRx3LfsrCheck();
        // ScalerHdmiFrlMacRx3GapCheck();

        // pop CED
        ScalerSetByte(P77_0A_HDMI21_FRL_CED_2, 0x80);

        DebugMessageRx3("FRL Rx3: L0 CED", ((ScalerGetByte(P77_0A_HDMI21_FRL_CED_2) & 0x7F) << 8) | (ScalerGetByte(P77_0B_HDMI21_FRL_CED_3)));
        DebugMessageRx3("FRL Rx3: L1 CED", ((ScalerGetByte(P77_0C_HDMI21_FRL_CED_4) & 0x7F) << 8) | (ScalerGetByte(P77_0D_HDMI21_FRL_CED_5)));
        DebugMessageRx3("FRL Rx3: L2 CED", ((ScalerGetByte(P77_0E_HDMI21_FRL_CED_6) & 0x7F) << 8) | (ScalerGetByte(P77_0F_HDMI21_FRL_CED_7)));
        DebugMessageRx3("FRL Rx3: L3 CED", ((ScalerGetByte(P77_10_HDMI21_FRL_CED_8) & 0x7F) << 8) | (ScalerGetByte(P77_11_HDMI21_FRL_CED_9)));
        ScalerDebug();
    }
#endif

    return _SOURCE_HDMI;
}

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI2.1 Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source Type
//--------------------------------------------------
EnumSourceType ScalerHdmiFrlMacRx3SeamlessReset(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    DebugMessageRx3("===== FRL Rx3 SDR_DM Seamless flow =====", 0x00);

    // reset for AVI IF WD
    ScalerHdmiFrlMacRx3WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

    // Measure check
    if(ScalerHdmiFrlMacRx3MeasureCheck() == _FALSE)
    {
        DebugMessageRx3("FRL Rx3: Measure fail", 0);
        return _SOURCE_NONE;
    }

    // HDMI packet detect
    ScalerHdmiFrlMacRx3PacketDetect(_NOT_WAIT);

    ScalerHdmiFrlMacRx3VideoSetting();

    SET_COLOR_DEPTH(enumMappingPort, ScalerHdmiFrlMacRx3GetColorDepth());

    // Precheck for (422, 12bpc) <-> (RGB, 8bpc) case
    if(ScalerHdmiFrlMacRx3CheckSeamlessCondition() == _FALSE)
    {
        DebugMessageRx3("FRL Rx3: NOT Seamless condition", 0x00);
        return _SOURCE_NONE;
    }

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
    // Get EMP packet
    ScalerHdmiFrlMacRx3EmpPacketDetect(_NOT_WAIT);
#endif

    return _SOURCE_HDMI;
}

//--------------------------------------------------
// Description  : Check seamless video format that is avaiable for SRC
// Input Value  : None
// Output Value : _TRUE(seamless case)
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3CheckSeamlessCondition(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    switch(GET_COLOR_SPACE(enumMappingPort))
    {
        case _COLOR_SPACE_RGB:
        case _COLOR_SPACE_YCBCR444:

            // check GCP CD field to ensure 8bpc
            if(ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x42, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) < 0x05)
            {
                return _TRUE;
            }

            break;

        case _COLOR_SPACE_YCBCR422:

            return _TRUE;
            break;

        default:

            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Detect FRL video Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3FrlVideoCheck(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    // Clear Vsync and Hsync invert before check source's polarity
    ScalerSetBit(P68_26_HDMI21_DI_0, ~(_BIT5 | _BIT4), 0x00);

    // Disable FRL formate detection
    ScalerSetBit(P68_30_HDMI21_FRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Clear FRL format flag
    ScalerSetBit(P68_30_HDMI21_FRL_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(P68_31_HDMI21_FRL_1, ~(_BIT6 | _BIT4 | _BIT2), (_BIT6 | _BIT4 | _BIT2));

    // Enable FRL format detection
    ScalerSetBit(P68_30_HDMI21_FRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Wait at least 1 frame for HW update FRL flag
    ScalerTimerDelayXms(45);

    // Check Video-GB, Video-packet, Vsync and data island, MAP type/length no error
    if((ScalerGetBit(P68_30_HDMI21_FRL_0, (_BIT6 | _BIT5 | _BIT3)) == (_BIT6 | _BIT5 | _BIT3)) && (ScalerGetBit(P68_31_HDMI21_FRL_1, (_BIT6 | _BIT4 | _BIT2)) == 0x00))
    {
        // Enable RS fw error count
        // ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);

        return _TRUE;
    }
    else if((ScalerGetBit(P68_30_HDMI21_FRL_0, (_BIT6 | _BIT5 | _BIT3)) == (_BIT6 | _BIT5 | _BIT3)) && (ScalerGetBit(P68_31_HDMI21_FRL_1, _BIT4) == 0x00)) // QD 480p has bug
    {
        // Enable RS fw error count
        // ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);

        DebugMessageRx3("QD980_480P bug", 0);
        return _TRUE;
    }
    else
    {
        // Reset HDMI21 Small FIFO
        if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            ScalerTmdsPhyRxFifoReset(enumMappingPort, 4);
        }
        else
        {
            ScalerTmdsPhyRxFifoReset(enumMappingPort, 3);
        }

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Detect FRL video Check
// Input Value  : bWait => Whether to wait then read
// Output Value : FRL video type
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3MeasureCheck(void)
{
    WORD usHdmiFrlMacRx3Vtotal1 = 0;
    WORD usHdmiFrlMacRx3Vtotal2 = 0;

    // if has Hsync, use Hsync for measure
    if(ScalerGetBit(P68_30_HDMI21_FRL_0, _BIT4) == _BIT4)
    {
        ScalerSetBit(P68_43_FRL_MEASURE_3, ~(_BIT7 | _BIT6), 0x00);
    }
    // no Hsync(DSC mode), use virtual-hsync for measure
    else
    {
        ScalerSetBit(P68_43_FRL_MEASURE_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    // Skip first 16 lines
    ScalerSetBit(P68_43_FRL_MEASURE_3, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);

    // Measure 256 lines for Htotal/Hactive clock count after E ver.
    ScalerSetBit(P68_5A_FRL_MEASURE_18, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

    // Check Source's Vsync polarity
    if(ScalerGetBit(P68_49_FRL_MEASURE_9, _BIT5) == _BIT5)
    {
        ScalerSetBit(P68_26_HDMI21_DI_0, ~_BIT4, _BIT4);
    }

    // Check Source's Hsync polarity
    if(ScalerGetBit(P68_49_FRL_MEASURE_9, _BIT6) == _BIT6)
    {
        ScalerSetBit(P68_26_HDMI21_DI_0, ~_BIT5, _BIT5);
    }

    // Set HDCP Vsync from Packet Decoder
    ScalerSetBit(P2E_3C_I2C_DUMMY_1, ~_BIT6, 0x00);

    // Clear Interlace flag
    ScalerSetBit(P68_4A_FRL_MEASURE_A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // Start Measure
    ScalerSetBit(P68_40_FRL_MEASURE_0, ~_BIT7, _BIT7);

    // wait 4 frames
    ScalerTimerPollingFlagProc(180, P68_40_FRL_MEASURE_0, _BIT7, _FALSE);

    //////////////////////
    // Interlace Check  //
    //////////////////////

    // Check Interlace
    if(ScalerGetBit(P68_4A_FRL_MEASURE_A, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
    {
        // Interlace mode
    }

    //////////////////////
    // Horizontal Check //
    //////////////////////

    // Get Hsync_width
    g_usHdmiFrlMacRx3Hsync = ((WORD)ScalerGetBit(P68_4B_FRL_MEASURE_B, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ((WORD)ScalerGetByte(P68_4C_FRL_MEASURE_C));

    // Get Hback_porch
    g_usHdmiFrlMacRx3Hback = ((WORD)ScalerGetBit(P68_4D_FRL_MEASURE_D, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ((WORD)ScalerGetByte(P68_4E_FRL_MEASURE_E));

    // Get Hactive
    g_usHdmiFrlMacRx3Hactive = ((WORD)ScalerGetByte(P68_4F_FRL_MEASURE_F) << 8) | ((WORD)ScalerGetByte(P68_50_FRL_MEASURE_10));

    // Get Htotal
    g_usHdmiFrlMacRx3Htotal = ((WORD)ScalerGetByte(P68_51_FRL_MEASURE_11) << 8) | ((WORD)ScalerGetByte(P68_52_FRL_MEASURE_12));

    // Calculate Hfront
    g_usHdmiFrlMacRx3Hfront = g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hactive - g_usHdmiFrlMacRx3Hsync - g_usHdmiFrlMacRx3Hback;

    DebugMessageRx3("FRL Rx3: Hfront", g_usHdmiFrlMacRx3Hfront);
    DebugMessageRx3("FRL Rx3: Hsync", g_usHdmiFrlMacRx3Hsync);
    DebugMessageRx3("FRL Rx3: Hbporch", g_usHdmiFrlMacRx3Hback);
    DebugMessageRx3("FRL Rx3: Hactive", g_usHdmiFrlMacRx3Hactive);
    DebugMessageRx3("FRL Rx3: Htotal", g_usHdmiFrlMacRx3Htotal);

    // if Hfront bigger than Htotal and not DSC mode, measure is not reasonable due to Hfront is by calculation.
    if((g_usHdmiFrlMacRx3Hfront >= g_usHdmiFrlMacRx3Htotal) && (ScalerGetBit(P68_30_HDMI21_FRL_0, _BIT4) == _BIT4))
    {
        DebugMessageRx3("FRL Rx3: measure fail", 0);
        return _FALSE;
    }

    ////////////////////
    // Vertical Check //
    ////////////////////

    // Get Vsync_width
    g_usHdmiFrlMacRx3Vsync = ScalerGetByte(P68_53_FRL_MEASURE_13);

    // Get Vback_porch
    g_usHdmiFrlMacRx3Vback = ((WORD)ScalerGetBit(P68_54_FRL_MEASURE_14, (_BIT2 | _BIT1 | _BIT0)) << 8) | ((WORD)ScalerGetByte(P68_55_FRL_MEASURE_15));

    // Get Vactive
    g_usHdmiFrlMacRx3Vactive = ((WORD)ScalerGetByte(P68_56_FRL_MEASURE_16) << 8) | ((WORD)ScalerGetByte(P68_57_FRL_MEASURE_17));

    // Get Vtotal
    usHdmiFrlMacRx3Vtotal1 = ((WORD)ScalerGetByte(P68_45_FRL_MEASURE_5) << 8) | ((WORD)ScalerGetByte(P68_46_FRL_MEASURE_6));
    usHdmiFrlMacRx3Vtotal2 = ((WORD)ScalerGetByte(P68_47_FRL_MEASURE_7) << 8) | ((WORD)ScalerGetByte(P68_48_FRL_MEASURE_8));

    // Calculate Vstart
    g_usHdmiFrlMacRx3Vtotal = (usHdmiFrlMacRx3Vtotal1 + usHdmiFrlMacRx3Vtotal2) / 2;

    g_usHdmiFrlMacRx3Vfront = (g_usHdmiFrlMacRx3Vtotal - g_usHdmiFrlMacRx3Vsync - g_usHdmiFrlMacRx3Vback - g_usHdmiFrlMacRx3Vactive);

    DebugMessageRx3("FRL Rx3: Vfront", g_usHdmiFrlMacRx3Vfront);
    DebugMessageRx3("FRL Rx3: Vsync", g_usHdmiFrlMacRx3Vsync);
    DebugMessageRx3("FRL Rx3: Vbporch", g_usHdmiFrlMacRx3Vback);
    DebugMessageRx3("FRL Rx3: Vactive", g_usHdmiFrlMacRx3Vactive);
    DebugMessageRx3("FRL Rx3: Vtotal-1", usHdmiFrlMacRx3Vtotal1);
    DebugMessageRx3("FRL Rx3: Vtotal-2", usHdmiFrlMacRx3Vtotal2);

    if((g_usHdmiFrlMacRx3Vsync + g_usHdmiFrlMacRx3Vback + g_usHdmiFrlMacRx3Vactive) >= g_usHdmiFrlMacRx3Vtotal)
    {
        DebugMessageRx3("FRL Rx3: measure fail", 0);
        return _FALSE;
    }

    // Check Measure Result Fail / Error
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // DSC mode, Hsync maybe 0, ECO Version C will fixed this bug.
    if((g_usHdmiFrlMacRx3Hactive == 0x0000) || (g_usHdmiFrlMacRx3Htotal == 0x0000) ||
       (g_usHdmiFrlMacRx3Vsync == 0x0000) || (g_usHdmiFrlMacRx3Vback == 0x0000) || (g_usHdmiFrlMacRx3Vactive == 0x0000) || (usHdmiFrlMacRx3Vtotal1 == 0x0000) ||
       (usHdmiFrlMacRx3Vtotal2 == 0x0000))
#else
    if((g_usHdmiFrlMacRx3Hsync == 0x0000) || (g_usHdmiFrlMacRx3Hback == 0x0000) || (g_usHdmiFrlMacRx3Hactive == 0x0000) || (g_usHdmiFrlMacRx3Htotal == 0x0000) ||
       (g_usHdmiFrlMacRx3Vsync == 0x0000) || (g_usHdmiFrlMacRx3Vback == 0x0000) || (g_usHdmiFrlMacRx3Vactive == 0x0000) || (usHdmiFrlMacRx3Vtotal1 == 0x0000) ||
       (usHdmiFrlMacRx3Vtotal2 == 0x0000))
#endif
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3DisplayFormatSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    DWORD ulHdmiFrlMacHtotalClkCount = 0;
    DWORD ulLinkClkValue = 0;
    WORD usHdmiFrlMacRx3DPFHfront = 0;
    WORD usHdmiFrlMacRx3DPFHsync = 0;
    WORD usHdmiFrlMacRx3DPFHstart = 0;
    WORD usHdmiFrlMacRx3DPFHactive = 0;
    WORD usHdmiFrlMacRx3DPFHtotal = 0;
    DWORD ulHdmiFrlMacVstoVsDelay = 0;
    WORD usFifoOffset = 0;


    //////////////////////
    // Deep Color Check //
    //////////////////////

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        // Disable deep color block
        ScalerSetBit(P77_B5_TMDS_UDC0, ~_BIT7, 0x00);
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_80_PORT_PAGE77_HDMI_DPC_SET0, ~_BIT7, 0x00);

        // Set HW auto detect deep color
        ScalerSetBit(P77_B8_TMDS_DPC1, ~_BIT2, _BIT2);

        //////////////////////
        // DSC Check        //
        //////////////////////

        // When virtual-hsync has overlap den(C version ECO) then modify vstart
        if(ScalerGetBit(P68_43_FRL_MEASURE_3, _BIT0) == _BIT0)
        {
            // modify Vstart
            // Vback_porch need add 1
            g_usHdmiFrlMacRx3Vback = g_usHdmiFrlMacRx3Vback + 1;

            // Vfront porch need minus 1 due to Vback_porch add 1
            g_usHdmiFrlMacRx3Vfront = g_usHdmiFrlMacRx3Vfront - 1;

            DebugMessageRx3("FRL Rx3: Vstart changed", g_usHdmiFrlMacRx3Vback);
        }
    }
    else
#endif
    {
        if((GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422))
        {
            DebugMessageRx3("FRL Rx3: Deep Color Detected", GET_COLOR_DEPTH(enumMappingPort));

            // Max. 8K timing
            g_usHdmiFrlMacRx3Hsync = (g_usHdmiFrlMacRx3Hsync * 8) / GET_COLOR_DEPTH(enumMappingPort);
            g_usHdmiFrlMacRx3Hback = (g_usHdmiFrlMacRx3Hback * 8) / GET_COLOR_DEPTH(enumMappingPort);
            g_usHdmiFrlMacRx3Hactive = (WORD)(((DWORD)g_usHdmiFrlMacRx3Hactive * 8) / GET_COLOR_DEPTH(enumMappingPort));
            g_usHdmiFrlMacRx3Htotal = (WORD)(((DWORD)g_usHdmiFrlMacRx3Htotal * 8) / GET_COLOR_DEPTH(enumMappingPort));
            g_usHdmiFrlMacRx3Hfront = g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hsync - g_usHdmiFrlMacRx3Hback - g_usHdmiFrlMacRx3Hactive;

            // Enable deep color block
            ScalerSetBit(P77_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_80_PORT_PAGE77_HDMI_DPC_SET0, ~_BIT7, _BIT7);

            // force default phase, after D version ECO remove default phase
            /*ScalerSetBit(P77_B8_TMDS_DPC1, ~(_BIT2 | _BIT1), _BIT1);

            if(GET_COLOR_DEPTH(enumMappingPort) == _COLOR_DEPTH_10_BITS)
            {
                ScalerSetBit(P77_B4_TMDS_DPC0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            }
            else if(GET_COLOR_DEPTH(enumMappingPort) == _COLOR_DEPTH_12_BITS)
            {
                ScalerSetBit(P77_B4_TMDS_DPC0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }*/

            // HW auto detect deep color, after E version
            ScalerSetBit(P77_B8_TMDS_DPC1, ~_BIT2, _BIT2);
        }
        else
        {
            // Disable deep color block
            ScalerSetBit(P77_B5_TMDS_UDC0, ~_BIT7, 0x00);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_80_PORT_PAGE77_HDMI_DPC_SET0, ~_BIT7, 0x00);

            // Set HW auto detect deep color
            ScalerSetBit(P77_B8_TMDS_DPC1, ~_BIT2, _BIT2);
        }
    }


    //////////////////////////////////////////////
    // Pixel Repetition Check                   //
    // RLE1039 down sampling before DPF module  //
    //////////////////////////////////////////////
    if(GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
    {
        DebugMessageRx3("FRL Rx3: Pixel Repetition Detected", GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION());

        g_usHdmiFrlMacRx3Hsync = g_usHdmiFrlMacRx3Hsync / (GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx3Hback = g_usHdmiFrlMacRx3Hback / (GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx3Hactive = g_usHdmiFrlMacRx3Hactive / (GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx3Htotal = g_usHdmiFrlMacRx3Htotal / (GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx3Hfront = g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hsync - g_usHdmiFrlMacRx3Hback - g_usHdmiFrlMacRx3Hactive;
    }


    ///////////////////////////////////////////
    // Calculate LinkClk-PixelClk Conversion //
    ///////////////////////////////////////////

    // Get Htotal Clock Count
    ulHdmiFrlMacHtotalClkCount = ((DWORD)ScalerGetBit(P68_40_FRL_MEASURE_0, _BIT0) << 16) | ((DWORD)ScalerGetByte(P68_41_FRL_MEASURE_1) << 8) | ((DWORD)ScalerGetByte(P68_42_FRL_MEASURE_2));

    if(ulHdmiFrlMacHtotalClkCount == 0)
    {
        return _FALSE;
    }

    // Set Link Clock
    if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_12G)
    {
        ulLinkClkValue = 12000000;
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_10G)
    {
        ulLinkClkValue = 10000000;
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_8G)
    {
        ulLinkClkValue = 8000000;
    }
    else if((ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_4LANES) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_3LANES))
    {
        ulLinkClkValue = 6000000;
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_3G)
    {
        ulLinkClkValue = 3000000;
    }

    // Calculate Pixel Clock => PixelClk = (LinkClk / (18 * Htotal_CountByLinkClk) * H Atotal PixelCount) (Unit: kHz)
    // 4K2K@60, link rate 6G, Htotal_CountByLinkClk = 1 / 135KHz * 6G / 18 = 2469 counts
    // PixelClk = 6000000 / (18 * 2469) * 4400 = 594032 (kHz)
    if(GET_HDMI_FRL_MAC_RX3_DPF_PIXEL_MODE_MISMATCH() == _FALSE)
    {
        g_ulHdmiFrlMacRx3PixelClkValue = ulLinkClkValue / (18 * 2) * (DWORD)g_usHdmiFrlMacRx3Htotal / ulHdmiFrlMacHtotalClkCount * 2;
    }

    g_usHdmiFrlMacRx3FrameRate = (g_ulHdmiFrlMacRx3PixelClkValue * 100 / g_usHdmiFrlMacRx3Htotal) * 10 / g_usHdmiFrlMacRx3Vtotal;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
    {
        if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
        {
            g_ulHdmiFrlMacRx3PixelClkValue = g_ulHdmiFrlMacRx3PixelClkValue * 2;
        }
    }

    DebugMessageRx3("FRL Rx3: ulHdmiFrlMacHtotalClkCount", ulHdmiFrlMacHtotalClkCount);
    DebugMessageRx3("FRL Rx3: g_ulHdmiFrlMacRx3PixelClkValue", g_ulHdmiFrlMacRx3PixelClkValue);
    DebugMessageRx3("FRL Rx3: g_usHdmiFrlMacRx3FrameRate", g_usHdmiFrlMacRx3FrameRate);

    // Check Pixel Clock
    if((g_ulHdmiFrlMacRx3PixelClkValue > 2800000) || (g_ulHdmiFrlMacRx3PixelClkValue < 5000) || (g_usHdmiFrlMacRx3FrameRate == 0))
    {
        DebugMessageRx3("FRL Rx3: Pixel Clk(MHz)", (g_ulHdmiFrlMacRx3PixelClkValue / 1000));

        return _FALSE;
    }


    ////////////////////////////
    // Display Format Setting //
    ////////////////////////////

    // Disable Display Format Generation
    ScalerSetBit(P68_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // force frame sync mode
    ScalerSetBit(P68_70_DPF_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

    // Set DPF input Hwidth(this reg is effective when Hactive div 4 is not 0)
    ScalerSetByte(P68_86_DPF_IN_HWD_M, (BYTE)(g_usHdmiFrlMacRx3Hactive >> 8));
    ScalerSetByte(P68_87_DPF_IN_HWD_L, (BYTE)(g_usHdmiFrlMacRx3Hactive & 0x00FF));

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

        usHdmiFrlMacRx3DPFHactive = ((g_usHdmiFrlMacRx3Hactive % 4) != 0) ? ((g_usHdmiFrlMacRx3Hactive / 4) + 1) : (g_usHdmiFrlMacRx3Hactive / 4);
        usHdmiFrlMacRx3DPFHtotal = ((g_usHdmiFrlMacRx3Htotal % 4) != 0) ? ((g_usHdmiFrlMacRx3Htotal / 4) + 1) : (g_usHdmiFrlMacRx3Htotal / 4);
        usHdmiFrlMacRx3DPFHsync = 8; // assume Hsyncwidth is 8T(5T may lost due to HW force HVsync rising at same edge)
        usHdmiFrlMacRx3DPFHstart = usHdmiFrlMacRx3DPFHtotal - usHdmiFrlMacRx3DPFHactive - 4; // Hfrotnporch is 4T, Hbackporch min is 4T(16-4-8=4)

        // DSC VS to VS delay
        ulHdmiFrlMacVstoVsDelay = (1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 4) *(ulLinkClkValue / 18) / (g_ulHdmiFrlMacRx3PixelClkValue / 4);
        DebugMessageRx3("FRL Rx3: VstoVsDelay", ulHdmiFrlMacVstoVsDelay);

        // In 4P mode, DPF read addr don't need add
        ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);

        DebugMessageRx3("FRL Rx3: DSC mode", 0);
    }
    else
#endif
    {
        if(ScalerGetBit(P68_70_DPF_CTRL_0, _BIT4) == _BIT4)
        {
            //////////////////////
            // Line Sync mode   //
            //////////////////////

            // 4P/2P/1P mode
            if((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ)
            {
                ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

                usHdmiFrlMacRx3DPFHactive = ((g_usHdmiFrlMacRx3Hactive % 4) != 0) ? ((g_usHdmiFrlMacRx3Hactive / 4) + 1) : (g_usHdmiFrlMacRx3Hactive / 4);
                usHdmiFrlMacRx3DPFHsync = ((g_usHdmiFrlMacRx3Hsync % 4) != 0) ? ((g_usHdmiFrlMacRx3Hsync / 4) + 1) : (g_usHdmiFrlMacRx3Hsync / 4);
                usHdmiFrlMacRx3DPFHstart = (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) % 4) != 0) ? (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 4) + 1) : ((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 4);
                usHdmiFrlMacRx3DPFHfront = ((g_usHdmiFrlMacRx3Hfront % 4) != 0) ? ((g_usHdmiFrlMacRx3Hfront / 4) + 1) : (g_usHdmiFrlMacRx3Hfront / 4);
                usHdmiFrlMacRx3DPFHtotal = usHdmiFrlMacRx3DPFHfront + usHdmiFrlMacRx3DPFHstart + usHdmiFrlMacRx3DPFHactive;
                usFifoOffset = _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 4;

                // In 4P mode, DPF read addr don't need add
                ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);

                DebugMessageRx3("FRL Rx3: 4P mode", 0);
            }
            else if((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_FRL_DPF_2P_MODE_FREQ)
            {
                ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT6);

                usHdmiFrlMacRx3DPFHactive = ((g_usHdmiFrlMacRx3Hactive % 2) != 0) ? ((g_usHdmiFrlMacRx3Hactive / 2) + 1) : (g_usHdmiFrlMacRx3Hactive / 2);
                usHdmiFrlMacRx3DPFHsync = ((g_usHdmiFrlMacRx3Hsync % 2) != 0) ? ((g_usHdmiFrlMacRx3Hsync / 2) + 1) : (g_usHdmiFrlMacRx3Hsync / 2);
                usHdmiFrlMacRx3DPFHstart = (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) % 2) != 0) ? (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 2) + 1) : ((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 2);
                usHdmiFrlMacRx3DPFHfront = ((g_usHdmiFrlMacRx3Hfront % 2) != 0) ? ((g_usHdmiFrlMacRx3Hfront / 2) + 1) : (g_usHdmiFrlMacRx3Hfront / 2);
                usHdmiFrlMacRx3DPFHtotal = usHdmiFrlMacRx3DPFHfront + usHdmiFrlMacRx3DPFHstart + usHdmiFrlMacRx3DPFHactive;

                usFifoOffset = _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 2;

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx3Hactive % 4) != 0)
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx3("FRL Rx3: 2P mode", 0);
            }
            else
            {
                ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT7);

                usHdmiFrlMacRx3DPFHactive = g_usHdmiFrlMacRx3Hactive;
                usHdmiFrlMacRx3DPFHsync = g_usHdmiFrlMacRx3Hsync;
                usHdmiFrlMacRx3DPFHstart = (g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback);
                usHdmiFrlMacRx3DPFHfront = g_usHdmiFrlMacRx3Hfront;
                usHdmiFrlMacRx3DPFHtotal = usHdmiFrlMacRx3DPFHfront + usHdmiFrlMacRx3DPFHstart + usHdmiFrlMacRx3DPFHactive;

                if(g_usHdmiFrlMacRx3Hactive / 2 > _HDMI_FRL_DPF_FIFO_HALF_LENGTH)
                {
                    usFifoOffset = _HDMI_FRL_DPF_FIFO_HALF_LENGTH;
                }
                else
                {
                    usFifoOffset = g_usHdmiFrlMacRx3Hactive / 2;
                }

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx3Hactive % 4) != 0)
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx3("FRL Rx3: 1P mode", 0);
            }

            // if Hfront is too small, need extend Htotal??????
            if(g_usHdmiFrlMacRx3Hfront < 300)
            {
                // Calculate DPF Htotal
                usHdmiFrlMacRx3DPFHtotal = g_usHdmiFrlMacRx3Hfront + usHdmiFrlMacRx3DPFHtotal;
            }
        }
        else
        {
            //////////////////////
            // Frame Sync mode  //
            //////////////////////

            // 4P/2P/1P mode, 420 only 1P/2P mode
            if(((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420))
            {
                ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

                usHdmiFrlMacRx3DPFHsync = ((g_usHdmiFrlMacRx3Hsync % 4) != 0) ? ((g_usHdmiFrlMacRx3Hsync / 4) + 1) : (g_usHdmiFrlMacRx3Hsync / 4);
                usHdmiFrlMacRx3DPFHstart = (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) % 4) != 0) ? (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 4) + 1) : ((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 4);
                usHdmiFrlMacRx3DPFHactive = ((g_usHdmiFrlMacRx3Hactive % 4) != 0) ? ((g_usHdmiFrlMacRx3Hactive / 4) + 1) : (g_usHdmiFrlMacRx3Hactive / 4);

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    // Check Hblank must >= 88, due to IMC HW Limitation
                    if((g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hactive) < 88)
                    {
                        usHdmiFrlMacRx3DPFHtotal = (((g_usHdmiFrlMacRx3Hactive + 88) % 4) != 0) ? (((g_usHdmiFrlMacRx3Hactive + 88) / 4) + 1) : ((g_usHdmiFrlMacRx3Hactive + 88) / 4);
                    }
                    else
                    {
                        usHdmiFrlMacRx3DPFHtotal = ((g_usHdmiFrlMacRx3Htotal % 4) != 0) ? ((g_usHdmiFrlMacRx3Htotal / 4) + 1) : (g_usHdmiFrlMacRx3Htotal / 4);
                    }
                }
                else
#endif
                {
                    usHdmiFrlMacRx3DPFHtotal = ((g_usHdmiFrlMacRx3Htotal % 4) != 0) ? ((g_usHdmiFrlMacRx3Htotal / 4) + 1) : (g_usHdmiFrlMacRx3Htotal / 4);
                }

                ulHdmiFrlMacVstoVsDelay = ((1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 4) *(ulLinkClkValue / 18) / (g_ulHdmiFrlMacRx3PixelClkValue / 4));

                // In 4P mode, DPF read addr don't need add
                ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);

                DebugMessageRx3("FRL Rx3: frame 4P mode", 0);
            }
            else if((((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_FRL_DPF_2P_MODE_FREQ) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420)) ||
                    (((g_ulHdmiFrlMacRx3PixelClkValue / 200) > _HW_HDMI_FRL_DPF_2P_MODE_FREQ) && (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)))
            {
                ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT6);

                usHdmiFrlMacRx3DPFHsync = ((g_usHdmiFrlMacRx3Hsync % 2) != 0) ? ((g_usHdmiFrlMacRx3Hsync / 2) + 1) : (g_usHdmiFrlMacRx3Hsync / 2);
                usHdmiFrlMacRx3DPFHstart = (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) % 2) != 0) ? (((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 2) + 1) : ((g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback) / 2);
                usHdmiFrlMacRx3DPFHactive = ((g_usHdmiFrlMacRx3Hactive % 2) != 0) ? ((g_usHdmiFrlMacRx3Hactive / 2) + 1) : (g_usHdmiFrlMacRx3Hactive / 2);

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    // Check Hblank must >= 88, due to IMC HW Limitation
                    if(((g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hactive) < 44) && (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420))
                    {
                        usHdmiFrlMacRx3DPFHtotal = (((g_usHdmiFrlMacRx3Hactive + 44) % 2) != 0) ? (((g_usHdmiFrlMacRx3Hactive + 44) / 2) + 1) : ((g_usHdmiFrlMacRx3Hactive + 44) / 2);
                    }
                    else if((g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hactive) < 88)
                    {
                        usHdmiFrlMacRx3DPFHtotal = (((g_usHdmiFrlMacRx3Hactive + 88) % 2) != 0) ? (((g_usHdmiFrlMacRx3Hactive + 88) / 2) + 1) : ((g_usHdmiFrlMacRx3Hactive + 88) / 2);
                    }
                    else
                    {
                        usHdmiFrlMacRx3DPFHtotal = ((g_usHdmiFrlMacRx3Htotal % 2) != 0) ? ((g_usHdmiFrlMacRx3Htotal / 2) + 1) : (g_usHdmiFrlMacRx3Htotal / 2);
                    }
                }
                else
#endif
                {
                    usHdmiFrlMacRx3DPFHtotal = ((g_usHdmiFrlMacRx3Htotal % 2) != 0) ? ((g_usHdmiFrlMacRx3Htotal / 2) + 1) : (g_usHdmiFrlMacRx3Htotal / 2);
                }

                ulHdmiFrlMacVstoVsDelay = ((1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 2) * (ulLinkClkValue / 18) / (g_ulHdmiFrlMacRx3PixelClkValue / 2));

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx3Hactive % 4) != 0)
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx3("FRL Rx3: frame 2P mode", 0);
            }
            // 1366 x 768 can use 1P mode after D version ECO
            else
            {
                ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT7);

                usHdmiFrlMacRx3DPFHsync = g_usHdmiFrlMacRx3Hsync;
                usHdmiFrlMacRx3DPFHstart = (g_usHdmiFrlMacRx3Hsync + g_usHdmiFrlMacRx3Hback);
                usHdmiFrlMacRx3DPFHactive = g_usHdmiFrlMacRx3Hactive;

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    // Check Hblank must >= 88, due to IMC HW Limitation
                    if(((g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hactive) < 44) && (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420))
                    {
                        usHdmiFrlMacRx3DPFHtotal = g_usHdmiFrlMacRx3Hactive + 44;
                    }
                    else if((g_usHdmiFrlMacRx3Htotal - g_usHdmiFrlMacRx3Hactive) < 88)
                    {
                        usHdmiFrlMacRx3DPFHtotal = g_usHdmiFrlMacRx3Hactive + 88;
                    }
                    else
                    {
                        usHdmiFrlMacRx3DPFHtotal = g_usHdmiFrlMacRx3Htotal;
                    }
                }
                else
#endif
                {
                    usHdmiFrlMacRx3DPFHtotal = g_usHdmiFrlMacRx3Htotal;
                }

                ulHdmiFrlMacVstoVsDelay = ((1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH) * (ulLinkClkValue / 18) / g_ulHdmiFrlMacRx3PixelClkValue);

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx3Hactive % 4) != 0)
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P68_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx3("FRL Rx3: frame 1P mode", 0);
            }
        }
    }

#if(_HDMI_FRL_DPF_TRACKING_METHOD == _HDMI_FRL_LINE_TRACKING)
    // DPF Htotal should be even due to line tracking limitation
    if(usHdmiFrlMacRx3DPFHtotal % 2 != 0)
    {
        usHdmiFrlMacRx3DPFHtotal = usHdmiFrlMacRx3DPFHtotal - 1;
    }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
    {
        // Check/Adjust DPF Hsync/Hstart
        if(ScalerHdmiFrlMacRx3DPFHsyncHstartAdjust(&usHdmiFrlMacRx3DPFHsync, &usHdmiFrlMacRx3DPFHstart, (usHdmiFrlMacRx3DPFHtotal - usHdmiFrlMacRx3DPFHactive)) == _TRUE)
        {
            DebugMessageRx3("FRL Rx3: Adjust DPF Hsync", usHdmiFrlMacRx3DPFHsync);
            DebugMessageRx3("FRL Rx3: Adjust DPF Hstart", usHdmiFrlMacRx3DPFHstart);
        }
    }

    // Set Hsync width and HSP is positive
    ScalerSetByte(P68_88_DPF_HSW_M, (BYTE)((usHdmiFrlMacRx3DPFHsync >> 8) & ~_BIT7));
    ScalerSetByte(P68_89_DPF_HSW_L, (BYTE)(usHdmiFrlMacRx3DPFHsync & 0x00FF));

    // Set Hstart
    ScalerSetByte(P68_82_DPF_HST_M, (BYTE)(usHdmiFrlMacRx3DPFHstart >> 8));
    ScalerSetByte(P68_83_DPF_HST_L, (BYTE)(usHdmiFrlMacRx3DPFHstart & 0x00FF));

    // Set Hwidth
    ScalerSetByte(P68_84_DPF_HWD_M, (BYTE)(usHdmiFrlMacRx3DPFHactive >> 8));
    ScalerSetByte(P68_85_DPF_HWD_L, (BYTE)(usHdmiFrlMacRx3DPFHactive & 0x00FF));

    // Set Htotal
    ScalerSetByte(P68_80_DPF_HTT_M, (BYTE)(usHdmiFrlMacRx3DPFHtotal >> 8));
    ScalerSetByte(P68_81_DPF_HTT_L, (BYTE)(usHdmiFrlMacRx3DPFHtotal & 0x00FF));

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        // Set Htotal use DPF_gen
        ScalerSetBit(P68_FC_DSC_HTT_0, ~_BIT7, 0x00);
    }
    else
#endif
    {
        // "420" or "3DDI Interlace" need set dsc_htt for DPF
#if(_3DDI_FUNCTION == _ON)
        if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (ScalerHdmiFrlMacRx3GetInterlace3ddiAvaible() == _TRUE))
#else
        if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
#endif
        {
            // Set dsc_htt
            ScalerSetBit(P68_FC_DSC_HTT_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usHdmiFrlMacRx3DPFHtotal >> 8));
            ScalerSetByte(P68_FD_DSC_HTT_1, (BYTE)(usHdmiFrlMacRx3DPFHtotal & 0x00FF));

#if(_3DDI_FUNCTION == _ON)
            if(((g_ulHdmiFrlMacRx3PixelClkValue / 100) <= _HW_HDMI_VIDEO_PLL_CLK_LIMIT) || (ScalerHdmiFrlMacRx3GetInterlace3ddiAvaible() == _TRUE))
#else
            if((g_ulHdmiFrlMacRx3PixelClkValue / 100) <= _HW_HDMI_VIDEO_PLL_CLK_LIMIT)
#endif
            {
                // Set Htotal use dsc_htt ... 420 w/ 2x clk
                ScalerSetBit(P68_FC_DSC_HTT_0, ~_BIT7, _BIT7);
            }
            else
            {
                // Set Htotal use DPF_gen ... 420 w/ 1x clk
                ScalerSetBit(P68_FC_DSC_HTT_0, ~_BIT7, 0x00);
            }

            // Delay * 2 due to DPF clock is half.
            usFifoOffset = usFifoOffset * 2;
            ulHdmiFrlMacVstoVsDelay = ulHdmiFrlMacVstoVsDelay * 2;
        }
        else
        {
            // Set Htotal use DPF_gen
            ScalerSetBit(P68_FC_DSC_HTT_0, ~_BIT7, 0x00);
        }
    }

    // Set Vsync width  and VSP is positive
    ScalerSetByte(P68_91_DPF_VSW_M, (BYTE)((g_usHdmiFrlMacRx3Vsync >> 8) & ~_BIT7));
    ScalerSetByte(P68_92_DPF_VSW_L, (BYTE)(g_usHdmiFrlMacRx3Vsync & 0x00FF));

    // Set Vstart
    ScalerSetByte(P68_8D_DPF_VST_M, (BYTE)((g_usHdmiFrlMacRx3Vsync + g_usHdmiFrlMacRx3Vback) >> 8));
    ScalerSetByte(P68_8E_DPF_VST_L, (BYTE)((g_usHdmiFrlMacRx3Vsync + g_usHdmiFrlMacRx3Vback) & 0x00FF));

    // Set Vactive
    ScalerSetByte(P68_8F_DPF_VHT_M, (BYTE)(g_usHdmiFrlMacRx3Vactive >> 8));
    ScalerSetByte(P68_90_DPF_VHT_L, (BYTE)(g_usHdmiFrlMacRx3Vactive & 0x00FF));

    // Set Vtotal
    ScalerSetByte(P68_8B_DPF_VTT_M, (BYTE)(g_usHdmiFrlMacRx3Vtotal >> 8));
    ScalerSetByte(P68_8C_DPF_VTT_L, (BYTE)(g_usHdmiFrlMacRx3Vtotal & 0x00FF));

    // Set HS to HS Delay (for DE_Only Mode)
    ScalerSetByte(P68_79_BS2HS_M, (BYTE)(usFifoOffset >> 8));
    ScalerSetByte(P68_7A_BS2HS_L, (BYTE)(usFifoOffset & 0x00FF));


    /////////////////////
    // Interlace check //
    /////////////////////

    // Interlace ----DSC no interlace mode....
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if((ScalerGetBit(P68_4A_FRL_MEASURE_A, _BIT4) == _BIT4) && (GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE))
#else
    if(ScalerGetBit(P68_4A_FRL_MEASURE_A, _BIT4) == _BIT4)
#endif
    {
        // measure result is filed 2, DPF Vst need minus 1
        if(ScalerGetBit(P68_49_FRL_MEASURE_9, (_BIT4 | _BIT3)) == 0x00)
        {
            // DPF Vst minus 1
            WORD usVstModify = (((WORD)ScalerGetByte(P68_8D_DPF_VST_M) << 8) | ScalerGetByte(P68_8E_DPF_VST_L)) - 1;
            ScalerSetByte(P68_8D_DPF_VST_M, HIBYTE(usVstModify));
            ScalerSetByte(P68_8E_DPF_VST_L, LOBYTE(usVstModify));

            g_usHdmiFrlMacRx3Vsync = g_usHdmiFrlMacRx3Vsync - 1;
        }

        // Set Even Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P68_73_EVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P68_74_EVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P68_75_EVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Odd BStoVSDelay = Even BStoVSDelay + 0.5 line;
        ulHdmiFrlMacVstoVsDelay = ulHdmiFrlMacVstoVsDelay + ((1UL * g_usHdmiFrlMacRx3Htotal / 2) * (ulLinkClkValue / 18) / g_ulHdmiFrlMacRx3PixelClkValue);

        // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P68_76_OVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P68_77_OVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P68_78_OVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Enable DPF Interlace
        ScalerSetBit(P68_93_INTERLACE_MODE_CONFIG, ~_BIT7, _BIT7);

        DebugMessageRx3("FRL Rx3: interlace mode", 0);
    }
    // Progressive
    else
    {
        // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P68_76_OVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P68_77_OVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P68_78_OVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Set Even Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P68_73_EVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P68_74_EVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P68_75_EVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Disable DPF Interlace
        ScalerSetBit(P68_93_INTERLACE_MODE_CONFIG, ~_BIT7, 0x00);
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // DSC mode mux
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        // DSC enable
        ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // DSC BR swap
        ScalerSetBit(P68_A1_DPF_OUTPUT_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
    }
    else
#endif
    {
        ScalerSetBit(P68_71_DPF_CTRL_1, ~(_BIT1 | _BIT0), 0x00);

        // No BR swap
        ScalerSetBit(P68_A1_DPF_OUTPUT_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT7);
    }

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(P68_70_DPF_CTRL_0, ~_BIT6, _BIT6);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
    {
        if(ScalerHdmiFrlMacRx3DisplayFormatCheck(enumMappingPort) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust DPF Hsync, Hstart for Measure
// Input Value  : pusDPFHsync, pusDPFHstart, usDPFHblank
// Output Value : False --> Keep origin DPFHsync/Hstart
//                True  --> Adjust DPFHsync/Hstart for Measure
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3DPFHsyncHstartAdjust(WORD *pusDPFHsync, WORD *pusDPFHstart, WORD usDPFHblank)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    WORD usMinHsyncMeasCnt = 2;
    WORD usHfHbReserve = 2;
    WORD usMinMeasHsync = 0;
    WORD usDPFPixMode = 1;

    if(GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420)
    {
        usMinMeasHsync = ((DWORD)usMinHsyncMeasCnt * g_ulHdmiFrlMacRx3PixelClkValue) / _MEASURE_CLK + 1;  // Real Pixel Clock
    }
    else
    {
        usMinMeasHsync = ((DWORD)usMinHsyncMeasCnt * g_ulHdmiFrlMacRx3PixelClkValue / 2) / _MEASURE_CLK + 1;  // Real Pixel Clock / 2 for 420
    }

    if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
    {
        usDPFPixMode = 4;
    }
    else if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6)
    {
        usDPFPixMode = 2;
    }
    else
    {
        usDPFPixMode = 1;
    }

    usMinMeasHsync = (usMinMeasHsync + (usDPFPixMode - 1)) / usDPFPixMode;  // Ceil(usMinMeasHsync, usDPFPixMode)/usDPFPixMode

    if(*pusDPFHsync < usMinMeasHsync)
    {
        // usMinMeasHsync within Hstart Limit
        if(usMinMeasHsync <= (*pusDPFHstart - usHfHbReserve))
        {
            *pusDPFHsync = usMinMeasHsync;  // Enlarge DPF Hsync to usMinMeasHsync
        }
        // usMinMeasHsync over Hstart Limit
        else
        {
            // usMinMeasHsync within Hblank Limit
            if(usMinMeasHsync <= (usDPFHblank - usHfHbReserve * 2))
            {
                *pusDPFHsync = usMinMeasHsync;     // Enlarge DPF Hsync to usMinMeasHsync
            }
            // usMinMeasHsync over Hblank Limit
            else
            {
                *pusDPFHsync = usDPFHblank - usHfHbReserve * 2;  // Enlarge DPF Hsync to Hblank Limit
            }

            *pusDPFHstart = *pusDPFHsync + usHfHbReserve;  // Also Enlarge DPF Hstart
        }

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Pixel Clk PLL Setting
// Input Value  : None
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3StreamClkRegenerate(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    WORD usVCOFreq = 0;
    BYTE ucSelVCODivider = 0;
    WORD usPLLinClkFreq = 0;
    WORD usTrkingLoopMax = 0;
    WORD usTrkingLoopCnt = 0;

#if(_HDMI_FRL_DPF_TRACKING_METHOD == _HDMI_FRL_LINE_TRACKING)
    WORD usHalfBSDelayCnt = 0;
    BYTE ucLastPhaseError = 0xFF;
    BYTE ucCurrentPhaseError = 0;
#else
    WORD usHdmiFrlMacRx3DPFHtotal = 0;
    WORD usVftTotalNumber = 0;
    bit bVftExtendMode = _FALSE;
    BYTE ucVftFinetuneNumber = 0;
    BYTE ucNCode = 0;
    BYTE ucFCodeMSB = 0;
#endif

#if(_3DDI_FUNCTION == _ON)
    bit bInterlace3ddi = ScalerHdmiFrlMacRx3GetInterlace3ddiAvaible();
#else
    bit bInterlace3ddi = _FALSE;
#endif


    /////////////////////////////
    // Calculate DPLL VCO Freq //
    /////////////////////////////

    // VCO band 10: 270~660M, 11: 310~710M
    // Pixel_clk: 25~600M
    usVCOFreq = (WORD)(g_ulHdmiFrlMacRx3PixelClkValue / 100);
    ucSelVCODivider = 0x01;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // DSC always 4p mode, PLL divide 4
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        usVCOFreq = (usVCOFreq >> 2);
    }
    else
#endif
    {
        // 4P mode
        if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
        {
            usVCOFreq = (usVCOFreq >> 2);
        }
        // 2P mode
        else if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6)
        {
            usVCOFreq = (usVCOFreq >> 1);

            // if 420 and pixel clk > 1400MHz, VCO will set 1x clk, then use 420 IP double pixel mode
            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && ((g_ulHdmiFrlMacRx3PixelClkValue / 200) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT))
            {
                usVCOFreq = (usVCOFreq >> 1);
            }
        }
        // 1P mode
        else
        {
            // if 420 and pixel clk > 700MHz, VCO will set 1x clk, then use 420 IP double pixel mode
            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && ((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT))
            {
                usVCOFreq = (usVCOFreq >> 1);
            }
        }
    }

#if(_3DDI_FUNCTION == _ON)
    // 3DDI Check 2x clk from Mac PLL to FC
    if(bInterlace3ddi == _TRUE)
    {
        usVCOFreq = (usVCOFreq << 1);
    }
#endif

    // PLL range 315~770MHz
    while((usVCOFreq <= 3150) && (ucSelVCODivider <= 16))
    {
        usVCOFreq = (usVCOFreq << 1);
        ucSelVCODivider = (ucSelVCODivider << 1);
    }

    DebugMessageRx3("FRL Rx3: usVCOFreq", usVCOFreq);
    DebugMessageRx3("FRL Rx3: ucSelVCODivider", ucSelVCODivider);


    //////////////
    // Set DPLL //
    //////////////

    // PLL Input Clock select to GDI_CLK, [7:6] = 10
    ScalerSetBit(P68_C2_PLL_IN_CONTROL, ~(_BIT7 | _BIT6), _BIT6);

    if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_12G)
    {
        usPLLinClkFreq = (BYTE)(120000 / 18 / 32);

        // Div 32
        ScalerSetBit(P68_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT5);
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_10G)
    {
        usPLLinClkFreq = (BYTE)(100000 / 18 / 26);

        // Div 26
        ScalerSetBit(P68_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT1));
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_8G)
    {
        usPLLinClkFreq = (BYTE)(80000 / 18 / 22);

        // Div 22
        ScalerSetBit(P68_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT2 | _BIT1));
    }
    else if((ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_4LANES) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_3LANES))
    {
        usPLLinClkFreq = (BYTE)(60000 / 18 / 16);

        // Div 16
        ScalerSetBit(P68_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT4);
    }
    else
    {
        usPLLinClkFreq = (BYTE)(30000 / 18 / 8);

        // Div 8
        ScalerSetBit(P68_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT6, 0x00);
    }
    else
#endif
    {
        // 420 and pixel clk <= 700MHz, VCO is 2x clk, need set div2 for MAC
        if(((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && ((g_ulHdmiFrlMacRx3PixelClkValue / 100) <= _HW_HDMI_VIDEO_PLL_CLK_LIMIT)) || (bInterlace3ddi == _TRUE))
        {
            ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT6, _BIT6);
        }
        else
        {
            ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT6, 0x00);
        }
    }

    DebugMessageRx3("FRL Rx3: usPLLinClkFreq", usPLLinClkFreq);

    // Set Ncode clamp, max <= 130% and min >= 70%
    // register valude = actual Ncode - 2
    ScalerSetByte(P68_D6_N_F_MAX, (BYTE)(((DWORD)usVCOFreq * 13 / usPLLinClkFreq / 10) - 2));
    ScalerSetByte(P68_D7_N_F_MIN, (BYTE)((((DWORD)usVCOFreq * 7 / usPLLinClkFreq / 10) + 1) - 2));

    ScalerHdmiFrlMacRx3DPLLOffProc(usVCOFreq, usPLLinClkFreq, ucSelVCODivider);

    ScalerHdmiFrlMacRx3DPLLOnProc(usVCOFreq, usPLLinClkFreq);


    ///////////////////////////////
    // DPPLL Tracking Setting //
    ///////////////////////////////

    // Disable line Tracking
    ScalerSetBit(P68_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

    // Disable Virtual FIFO Tracking
    ScalerSetBit(P68_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT7, 0x00);

    // Tracking - Reset Control Block
    ScalerSetBit(P68_DD_TRACKING_0, ~_BIT7, _BIT7);
    ScalerSetBit(P68_DD_TRACKING_0, ~_BIT7, 0x00);

    // Tracking - Enable PI Control
    // ScalerSetBit(P68_DE_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Disable bypass PI
    ScalerSetBit(P68_DC_SDM_0, ~_BIT7, 0x00);

    /////////////////////////////
    // Tracking - Set P/I Code //
    /////////////////////////////
    // small timing need use I code for accurate pixel clock tracking
    if(g_usHdmiFrlMacRx3Hactive <= 1920)
    {
        // P Gain Clamp = 0x00 40 00 00
        // P Code = 0x00 04 FF FF
        ScalerHdmiFrlMacRx3SetPGainClampValue(0x00, 0x40, 0x00);
        ScalerSetByte(P68_E3_MN_PI_CODE_2, 0x04);

        // I Gain Clamp = 0x00 04 00 00
        // I Code = 0x08
        ScalerSetByte(P68_E7_MN_PI_CODE_6, 0x04);
        ScalerSetByte(P68_E1_MN_PI_CODE_0, 0x08);
    }
    else
    {
        // P Gain Clamp = 0x00 20 00 00
        // P Code = 0x00 02 FF FF(default)
        ScalerHdmiFrlMacRx3SetPGainClampValue(0x00, 0x20, 0x00);
        ScalerSetByte(P68_E3_MN_PI_CODE_2, 0x02);

        // I Gain Clamp = 0x00 02 00 00
        // I Code = 0x04
        ScalerSetByte(P68_E7_MN_PI_CODE_6, 0x02);
        ScalerSetByte(P68_E1_MN_PI_CODE_0, 0x04);
    }

    // Delay 300us
    DELAY_XUS(300);

#if(_HDMI_FRL_DPF_TRACKING_METHOD == _HDMI_FRL_LINE_TRACKING)
    ///////////////////////////////////
    // Line Tracking - Set CK_MN_CLK //
    ///////////////////////////////////

    // set CK_MN_CLK = VCOFreq / 2 / CK_MN_DIVS < 250M
    if(ucSelVCODivider > 8)
    {
        // CK_MN_CLK = Pixel_CLK
        ScalerSetByte(P68_CC_MN_TRACKING_DIVS, (ucSelVCODivider / 4));
    }
    else
    {
        // CK_MN_CLK = VCO div8
        ScalerSetByte(P68_CC_MN_TRACKING_DIVS, 0x02);
    }

    ///////////////////////////
    // Line Tracking Setting //
    ///////////////////////////

    // small timing set tracking per line
    if(g_usHdmiFrlMacRx3Hactive <= 1920)
    {
        // How many lines tracking one time
        ScalerSetByte(P68_F1_VS_TRACK1, 0x01);
    }
    else
    {
        // How many lines tracking one time
        ScalerSetByte(P68_F1_VS_TRACK1, 0x07);
    }

    // Tracking - half HS delay cnt = Htotal/2 * GDI_CLK / Streamclk
    usHalfBSDelayCnt = (WORD)(((DWORD)g_usHdmiFrlMacRx3Htotal) * 270 / (g_ulHdmiFrlMacRx3PixelClkValue / 100) / 2);
    ScalerSetBit(P68_F4_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usHalfBSDelayCnt >> 8));
    ScalerSetByte(P68_F5_HS_TRACKING_NEW_MODE2, (BYTE)(usHalfBSDelayCnt & 0x00FF));

    // Set manual vbid(made by HW), use BE as hsync
    ScalerSetBit(P68_F4_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    // ScalerSetBit(P68_F4_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), (_BIT5));

    // Set Tracking Mode
    // Use fast lock mode
    ScalerSetBit(P68_EF_VS_TRACK_MODE, ~(_BIT3 | _BIT2), _BIT3);

    // DPF enable
    ScalerSetBit(P68_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), _BIT7);

    // Enable Tracking
    ScalerSetBit(P68_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);

    // Tracking - Enable PI Control
    ScalerSetBit(P68_DE_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Find Accurate N.F code
    if(g_usHdmiFrlMacRx3Hactive <= 1920)
    {
        // Wait 2 frames
        ScalerTimerDelayXms((2000 / g_usHdmiFrlMacRx3FrameRate) + 3);

        // Disable Tracking
        ScalerSetBit(P68_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

        // Set Ncode limitation
        ScalerSetByte(P68_D6_N_F_MAX, ScalerGetByte(P68_D8_N_F_REPORT0) + 2);
        ScalerSetByte(P68_D7_N_F_MIN, ScalerGetByte(P68_D8_N_F_REPORT0) - 2);

        // Reload N.F code
        ScalerSetByte(P68_D2_N_F_CODE_1, ScalerGetByte(P68_D8_N_F_REPORT0));
        ScalerSetByte(P68_D3_N_F_CODE_2, ScalerGetByte(P68_D9_N_F_REPORT1));
        ScalerSetBit(P68_D1_N_F_CODE_0, ~_BIT0, _BIT0);

        // Wait for DPLL Stable (300us)
        DELAY_XUS(300);

        // P Gain Clamp = 0x00 20 00 00
        // P Code = 0x00 02 FF FF
        ScalerHdmiFrlMacRx3SetPGainClampValue(0x00, 0x20, 0x00);
        ScalerSetByte(P68_E3_MN_PI_CODE_2, 0x02);

        // I Gain Clamp = 0x00 02 00 00
        // I Code = 0x04
        ScalerSetByte(P68_E7_MN_PI_CODE_6, 0x02);
        ScalerSetByte(P68_E1_MN_PI_CODE_0, 0x04);

        // Delay 300us
        DELAY_XUS(300);

        // How many lines tracking one time
        ScalerSetByte(P68_F1_VS_TRACK1, 0x3F);

        // Enable Tracking
        ScalerSetBit(P68_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);
    }

    // Check Tracking Stable
    usTrkingLoopMax = 20;
    usTrkingLoopCnt = 0;

    do
    {
        if(GET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT() == _TRUE)
        {
            DebugMessageRx3("FRL Rx3: Tracking Fail -- Source set FRL_Rate!! ------------", 0);
            return _FALSE;
        }

        usTrkingLoopCnt++;

        // Clear VS/HS non-lock flag
        ScalerSetBit(P68_EE_VS_TRACK_EN, ~_BIT0, _BIT0);

        // Clear Max Phase Error
        ScalerSetByte(P68_F3_VS_TRACK3, 0xFF);

        ScalerTimerDelayXms((1000 / g_usHdmiFrlMacRx3FrameRate) + 3); // need wait Vsync

        ucCurrentPhaseError = ScalerGetByte(P68_F3_VS_TRACK3);

        // wait tracking stable
        if((abs(ucLastPhaseError - ucCurrentPhaseError) < 10) && (usTrkingLoopCnt >= 3))
        {
            if(ScalerHdmiFrlMacRx3DpfFifoCheck(_WAIT) == _TRUE)
            {
                break;
            }
        }
        else
        {
            ucLastPhaseError = ucCurrentPhaseError;
        }
    }while(usTrkingLoopCnt < usTrkingLoopMax);

    if(usTrkingLoopCnt == usTrkingLoopMax)
    {
        DebugMessageRx3("FRL Rx3: Tracking Fail!!", ScalerGetByte(P68_F3_VS_TRACK3));
        DebugMessageRx3("FRL Rx3: DPF FIFO", ScalerGetByte(P68_AF_DPF_FIFO_CTRL));

        return _FALSE;
    }

#else // Else of #if(_HDMI_FRL_DPF_TRACKING_METHOD == _HDMI_FRL_LINE_TRACKING)

    ///////////////////////////////
    // Virtual FIFO Tracking     //
    ///////////////////////////////

    // P Gain Clamp = 0x00 40 00 00
    ScalerHdmiFrlMacRx3SetPGainClampValue(0x00, 0x40, 0x00);

    // I Gain Clamp = 0x00 04 00 00
    ScalerSetByte(P68_E7_MN_PI_CODE_6, 0x04);

    // Set First Level P/I code
    // I Code = 0x04
    // P Code = 0x00 02 FF FF
    ScalerSetByte(P68_A8_VIRTUAL_FIFO_TRACKING_8, 0x04);
    ScalerSetByte(P68_A9_VIRTUAL_FIFO_TRACKING_9, 0x00);
    ScalerSetByte(P68_AA_VIRTUAL_FIFO_TRACKING_10, 0x04);

    // Set Second Level P/I code
    // I Code = 0x08
    // P Code = 0x00 04 FF FF
    ScalerSetByte(P68_AB_VIRTUAL_FIFO_TRACKING_11, 0x08);
    ScalerSetByte(P68_AC_VIRTUAL_FIFO_TRACKING_12, 0x00);
    ScalerSetByte(P68_AD_VIRTUAL_FIFO_TRACKING_13, 0x08);

    // Set Third Level P/I code
    // I Code = 0x10
    // P Code = 0x00 08 FF FF
    ScalerSetByte(P68_AE_VIRTUAL_FIFO_TRACKING_14, 0x10);
    ScalerSetByte(P68_B3_VIRTUAL_FIFO_TRACKING_15, 0x00);
    ScalerSetByte(P68_B4_VIRTUAL_FIFO_TRACKING_16, 0x10);

    // Set Forth Level P/I code
    // I Code = 0x20
    // P Code = 0x00 10 FF FF
    ScalerSetByte(P68_B5_VIRTUAL_FIFO_TRACKING_17, 0x20);
    ScalerSetByte(P68_B6_VIRTUAL_FIFO_TRACKING_18, 0x00);
    ScalerSetByte(P68_B7_VIRTUAL_FIFO_TRACKING_19, 0x20);

    // Delay 300us
    DELAY_XUS(300);

    //////////////////////////////
    // Tracking - Set CK_MN_CLK //
    //////////////////////////////
    // set CK_MN_CLK = VCOFreq / 2 / CK_MN_DIVS < 250M
    if(ucSelVCODivider > 8)
    {
        // CK_MN_CLK = Pixel_CLK
        ScalerSetByte(P68_CC_MN_TRACKING_DIVS, (ucSelVCODivider / 4));
    }
    else
    {
        // CK_MN_CLK = VCO div8
        ScalerSetByte(P68_CC_MN_TRACKING_DIVS, 0x02);
    }


    ///////////////////////////////////
    // Virtual FIFO Tracking Setting //
    ///////////////////////////////////

    // Set Virtual FIFO Size
    ScalerSetByte(P68_FE_VIRTUAL_FIFO_TRACKING_24, 0x0C);
    ScalerSetByte(P68_FF_VIRTUAL_FIFO_TRACKING_25, 0x00);

    // Reset FIFO water level and R/W pointer
    /*if((GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422))
    {
        ScalerSetBit(P68_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT6, _BIT6);
    }
    else*/
    {
        ScalerSetBit(P68_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT6, 0x00);
    }

    // Initial water level = 368*2*4 / 2 = 1472
    ScalerSetBit(P68_96_VIRTUAL_FIFO_TRACKING_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetByte(P68_97_VIRTUAL_FIFO_TRACKING_1, 0xC0);

    //////////////////////////////////
    // Full = 2900, Empty = 0
    // Boundary = 900, each level is 225.
    // P/I code Level 4 for 0~225 and 2676~2900
    // P/I code Level 3 for 226~450 and 2451~2675
    // P/I code Level 2 for 451~675 and 2226~2450
    // P/I code Level 1 for 676~900 and 2000~2225
    // No P/I code for 900~2000

    // Set Start Tracking boundary = 900 = 0x384
    ScalerSetBit(P68_98_VIRTUAL_FIFO_TRACKING_2, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetByte(P68_99_VIRTUAL_FIFO_TRACKING_3, 0x84);

    // Get DPF Htotal
    usHdmiFrlMacRx3DPFHtotal = ((((WORD)ScalerGetByte(P68_80_DPF_HTT_M)) << 8) | (ScalerGetByte(P68_81_DPF_HTT_L))) * ((ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0) ? 4 : ((ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6) ? 2 : 1));
    DebugMessageRx3("VFT: usHdmiFrlMacRx3DPFHtotal", usHdmiFrlMacRx3DPFHtotal);

    // Need extend or reduce read pointer, when g_usHdmiFrlMacRx3Htotal and usHdmiFrlMacRx3DPFHtotal is different
    if(g_usHdmiFrlMacRx3Htotal >= usHdmiFrlMacRx3DPFHtotal)
    {
        DebugMessageRx3("VFT: reduce", g_usHdmiFrlMacRx3Htotal);

        // DPF reduce mode
        ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, 0x00);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
        {
            // Modify interval
            ScalerSetByte(P68_B9_VIRTUAL_FIFO_TRACKING_21, (BYTE)(((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) + 1) & 0x00FF));

            // Modify number
            ScalerSetByte(P68_BA_VIRTUAL_FIFO_TRACKING_22, (BYTE)((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) & 0x00FF));

            // Modify total
            ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) >> 8));
            ScalerSetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) & 0x00FF));
        }
        else
#endif
        {
            // Modify interval
            ScalerSetByte(P68_B9_VIRTUAL_FIFO_TRACKING_21, (BYTE)((((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) + 1) & 0x00FF));

            // Modify number
            ScalerSetByte(P68_BA_VIRTUAL_FIFO_TRACKING_22, (BYTE)(((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) & 0x00FF));

            // Modify total
            ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)(((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) >> 8));
            ScalerSetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)(((g_usHdmiFrlMacRx3Htotal - usHdmiFrlMacRx3DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) & 0x00FF));
        }
    }
    else
    {
        DebugMessageRx3("VFT: extend", g_usHdmiFrlMacRx3Htotal);

        // DPF extend mode
        ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, _BIT7);

        // Modify interval
        ScalerSetByte(P68_B9_VIRTUAL_FIFO_TRACKING_21, 0x02);

        // Modify number shall set 1 to prevent read pointer is negative
        ScalerSetByte(P68_BA_VIRTUAL_FIFO_TRACKING_22, 0x01);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
        {
            // Modify total
            ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)((usHdmiFrlMacRx3DPFHtotal - g_usHdmiFrlMacRx3Htotal) >> 8));
            ScalerSetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)((usHdmiFrlMacRx3DPFHtotal - g_usHdmiFrlMacRx3Htotal) & 0x00FF));
        }
        else
#endif
        {
            // Modify total
            ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)(((usHdmiFrlMacRx3DPFHtotal - g_usHdmiFrlMacRx3Htotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) >> 8));
            ScalerSetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)(((usHdmiFrlMacRx3DPFHtotal - g_usHdmiFrlMacRx3Htotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) & 0x00FF));
        }
    }

    // DPF enable
    ScalerSetBit(P68_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), _BIT7);

    // Enable Virtual FIFO tracking
    ScalerSetBit(P68_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT7, _BIT7);

    // Tracking - Enable PI Control
    ScalerSetBit(P68_DE_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Check Virtual FIFO Tracking Stable
    usTrkingLoopMax = 100;
    usTrkingLoopCnt = 0;
    usVftTotalNumber = (WORD)(ScalerGetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, (_BIT1 | _BIT0)) << 8) | ScalerGetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23);
    bVftExtendMode = (ScalerGetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, _BIT7)) >> 7;
    ucVftFinetuneNumber = 0;

    do
    {
        if(GET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT() == _TRUE)
        {
            DebugMessageRx3("FRL Rx3: Tracking Fail -- Source set FRL_Rate!! ------------", 0);
            return _FALSE;
        }

        usTrkingLoopCnt++;

        // clear Virtual FIFO full/empty flag
        ScalerSetBit(P68_98_VIRTUAL_FIFO_TRACKING_2, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

        // Record N.F code
        ucNCode = ScalerGetByte(P68_D8_N_F_REPORT0);
        ucFCodeMSB = ScalerGetByte(P68_D9_N_F_REPORT1);

        // wait 1 frame
        ScalerTimerDelayXms((1000 / g_usHdmiFrlMacRx3FrameRate) + 3);

        // Virtual FIFO no full/empty and DPF FIFO no overflow/underflow
        if((usTrkingLoopCnt >= 5) && (ScalerGetBit(P68_98_VIRTUAL_FIFO_TRACKING_2, (_BIT7 | _BIT5)) == 0x00) && (ScalerHdmiFrlMacRx3DpfFifoCheck(_WAIT) == _TRUE))
        {
            // N.F Code is stable
            if((ScalerGetByte(P68_D8_N_F_REPORT0) == ucNCode) && (ScalerGetByte(P68_D9_N_F_REPORT1) == ucFCodeMSB))
            {
                break;
            }
        }

        // fine tune reduce/extend
        if((usTrkingLoopCnt >= 80) && (GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422))
        {
            if(usVftTotalNumber != 0)
            {
                ScalerSetByte(P68_B9_VIRTUAL_FIFO_TRACKING_21, 0x01);
                ScalerSetByte(P68_BA_VIRTUAL_FIFO_TRACKING_22, 0x00);

                ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23, 0x00);
                usVftTotalNumber = 0;
                bVftExtendMode = _FALSE;
                DebugMessageRx3("!!!!!VFT set reduce 0", bVftExtendMode);
            }
            else
            {
                if((bVftExtendMode == _FALSE) && ((usTrkingLoopCnt - ucVftFinetuneNumber) >= 5))
                {
                    ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, 0x00);
                    ScalerSetByte(P68_B9_VIRTUAL_FIFO_TRACKING_21, ScalerGetByte(P68_B9_VIRTUAL_FIFO_TRACKING_21) + 1);
                    ScalerSetByte(P68_BA_VIRTUAL_FIFO_TRACKING_22, ScalerGetByte(P68_BA_VIRTUAL_FIFO_TRACKING_22) + 1);
                    ScalerSetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23, ScalerGetByte(P68_BB_VIRTUAL_FIFO_TRACKING_23) + 1);
                    bVftExtendMode = _TRUE;
                    ucVftFinetuneNumber = usTrkingLoopCnt;
                    DebugMessageRx3("!!!!!VFT set reduce +1", ucVftFinetuneNumber);
                }
                else if((usTrkingLoopCnt - ucVftFinetuneNumber) >= 5)
                {
                    ScalerSetBit(P68_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, _BIT7);
                    bVftExtendMode = _FALSE;
                    ucVftFinetuneNumber = usTrkingLoopCnt;
                    DebugMessageRx3("!!!!!VFT set extend +1", ucVftFinetuneNumber);
                }
            }
        }
    }while(usTrkingLoopCnt < usTrkingLoopMax);

    if(usTrkingLoopCnt == usTrkingLoopMax)
    {
        DebugMessageRx3("FRL Rx3: Virtual fifo Tracking Fail!!", ScalerGetByte(P68_98_VIRTUAL_FIFO_TRACKING_2));
        DebugMessageRx3("FRL Rx3: DPF FIFO", ScalerGetByte(P68_AF_DPF_FIFO_CTRL));
        return _FALSE;
    }
#endif

    // Clear overflow and underflow and protect empty and full flag
    ScalerSetBit(P68_AF_DPF_FIFO_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // DPF output enable
    SET_HDMI_FRL_RX3_DPF_RGB_CLK_OUTPUT_ENABLE();

    // DPF Watch Dog enable
    ScalerHdmiFrlMacRx3WatchDog(_HDMI_FRL_DPF_FIFO_WD, _ENABLE);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        g_ulHdmiFrlMacRx3DSCClkValue = (((DWORD)(ScalerGetByte(P68_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P68_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P68_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq / ucSelVCODivider;
        DebugMessageRx3("FRL Rx3: DSC clk", g_ulHdmiFrlMacRx3DSCClkValue);
    }
    else
#endif
    {
        // Calculate PLL VCO Clock, Unit kHz
        if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
        {
            g_ulHdmiFrlMacRx3PixelClkValue = (((DWORD)(ScalerGetByte(P68_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P68_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P68_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq * 4 / ucSelVCODivider / 10;
        }
        else if(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6)
        {
            g_ulHdmiFrlMacRx3PixelClkValue = (((DWORD)(ScalerGetByte(P68_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P68_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P68_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq * 2 / ucSelVCODivider / 10;
        }
        else
        {
            g_ulHdmiFrlMacRx3PixelClkValue = (((DWORD)(ScalerGetByte(P68_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P68_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P68_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq / ucSelVCODivider / 10;
        }

        // if 420 format and disable div2, pixel clk = VCO clk * 2
        if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && (ScalerGetBit(P68_D0_PLL_OUT_CONTROL, _BIT6) == 0))
        {
            g_ulHdmiFrlMacRx3PixelClkValue = g_ulHdmiFrlMacRx3PixelClkValue * 2;
        }

        if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
        {
            ScalerTmdsMacRxSetInputPixel(enumMappingPort, g_ulHdmiFrlMacRx3PixelClkValue / 200); // Unit:0.1MHz
        }
        else
        {
            ScalerTmdsMacRxSetInputPixel(enumMappingPort, g_ulHdmiFrlMacRx3PixelClkValue / 100); // Unit:0.1MHz
        }
    }

    // Set Nactive Htotal for EDID Table Analysis
    SET_HDMI_FRL_MAC_RX3_NATIVE_HTOTAL(g_usHdmiFrlMacRx3Htotal);

    // Niether 420(only 2p mode) nor DSC(fixed 4p mode), after tracking stable, pixel clk and pixel mode is mismatched
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420) && (GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE) &&
       (((ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00) && ((g_ulHdmiFrlMacRx3PixelClkValue / 100) <= _HW_HDMI_FRL_DPF_4P_MODE_FREQ)) ||
        ((ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6) && ((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ))))
#else
    if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420) &&
       (((ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00) && ((g_ulHdmiFrlMacRx3PixelClkValue / 100) <= _HW_HDMI_FRL_DPF_4P_MODE_FREQ)) ||
        ((ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6) && ((g_ulHdmiFrlMacRx3PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ))))
#endif
    {
        SET_HDMI_FRL_MAC_RX3_DPF_PIXEL_MODE_MISMATCH();

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Deep Color PLL On COntrol.
// Input Value  : ucNcode
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3DPLLOnProc(WORD usVCOFreq, WORD usPLLinClkFreq)
{
    WORD usNFCodeFPart = 0;
    BYTE ucNcode = 0;

    // Power On DPLL
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, 0x00);
    DELAY_XUS(200);

    // Set VCO/4 Enable
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT7, _BIT7);

    // Set N.F Code
    ucNcode = (BYTE)(usVCOFreq / usPLLinClkFreq);
    usNFCodeFPart = (usVCOFreq % usPLLinClkFreq);

    ScalerSetByte(P68_D2_N_F_CODE_1, (ucNcode - 2));
    ScalerSetBit(P68_D3_N_F_CODE_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usNFCodeFPart * 16 / usPLLinClkFreq));
    ScalerSetByte(P68_D4_N_F_CODE_3, (BYTE)(((usNFCodeFPart * 16) % usPLLinClkFreq) * 256 / usPLLinClkFreq));
    ScalerSetByte(P68_D5_N_F_CODE_4, (BYTE)((((usNFCodeFPart * 16) % usPLLinClkFreq) * 256 % usPLLinClkFreq) * 256 / usPLLinClkFreq));

    // Set N.F Double Buffer
    ScalerSetBit(P68_D1_N_F_CODE_0, ~_BIT0, _BIT0);

    // Wait for DPLL Stable (300us)
    DELAY_XUS(300);

    // enable DPF CLK
    ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Set P Gain
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SetPGainClampValue (BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1)
{
    // 1st tracking : 0x0 10 00 00
    // 2nd tracking : 0x0 01 00 00
    ScalerSetByte(P68_EA_MN_PI_CODE_9, ucPGainB3);
    ScalerSetByte(P68_EB_MN_PI_CODE_A, ucPGainB2);
    ScalerSetByte(P68_EC_MN_PI_CODE_B, ucPGainB1);
    ScalerSetByte(P68_ED_MN_PI_CODE_C, 0x00);
}

//--------------------------------------------------
// Description  : DPF Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3DpfFifoCheck(bit bWait)
{
    BYTE ucLoop = 0;

    if(bWait == _WAIT)
    {
        // Clear overflow and underflow and protect empty and full flag
        ScalerSetBit(P68_AF_DPF_FIFO_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

        // Delay 2 frame
        ScalerTimerDelayXms(2 * ((1000 / g_usHdmiFrlMacRx3FrameRate) + 3));

        while(ucLoop < 6)
        {
            ScalerTimerDelayXms(10);

            if(ScalerGetBit(P68_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4)) != 0x00)
            {
                return _FALSE;
            }

            ucLoop++;
        }
    }
    else
    {
        if(ScalerGetBit(P68_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4)) != 0x00)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : On Line Check HDMI2.1 stability
// Input Value  : enumSourceType --> Source Type
// Output Value : True --> Stable
//                False --> Unstable
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3StableDetect(EnumSourceType enumSourceType)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    enumSourceType = enumSourceType;

    // CLR SCL/SDA Toggle Flag
    ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);

    // Check Hpd Event happened
    if(GET_TMDS_MAC_RX3_HPD_RESET_TO_SEARCH_EVENT() == _TRUE)
    {
        DebugMessageRx3("HPD Toggle Event Occur at Frl Stable Detect!!", 0x00);
        CLR_TMDS_MAC_RX3_HPD_RESET_TO_SEARCH_EVENT();
        return _FALSE;
    }

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING() == _TRUE)
    {
        // Keep return false during Active Type HPD is toggling
        DebugMessageRx3("Active HPD Toggle Event is Ongoing at Frl Stable Detect!!", 0x00);
        return _FALSE;
    }
#endif

    // Check DPF FIFO
    if(ScalerHdmiFrlMacRx3DpfFifoCheck(_NOT_WAIT) == _FALSE)
    {
        // CDR unstable, need Link Training
        if((ScalerHdmiFrlMacRx3CheckCdrStable(g_usHdmiFrlMacRx3OffMeasureCount) == _FALSE) && (GET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT() == _FALSE))
        {
            // Set SCDC FLT_update
            ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT5, _BIT5);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH);
#endif
            // clear set phy
            CLR_HDMI_FRL_MAC_RX3_PHY_SET();

            DebugMessageRx3("FRL Rx3: CDR Unstable!!", enumSourceType);
        }
        // CDR stable, bypass Link Training
        else
        {
            // Reset HDMI21 Small FIFO
            if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
            {
                ScalerTmdsPhyRxFifoReset(enumMappingPort, 4);
            }
            else
            {
                ScalerTmdsPhyRxFifoReset(enumMappingPort, 3);
            }

            DebugMessageRx3("FRL Rx3: DPF FIFO Under/Overflow!! ========================", enumSourceType);
        }

        // Turn off DPF output
        SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

        return _FALSE;
    }

    // FRL_Rate Changed
    if(GET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT() == _TRUE)
    {
        DebugMessageRx3("FRL Rx3: FRL_Rate Changed!!", enumSourceType);

        // Turn off DPF output
        SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

        return _FALSE;
    }

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    if((GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON) && (GET_ADVANCED_HDR10_INITIAL_READY() == _TRUE) && (GET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING() == _FALSE))
    {
        bit bAdvancedHDR10VSIFReceive = GET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_VSIF_RECEIVED();
        bit bAdvancedHDR10EMPReceive = _FALSE;

        if(bAdvancedHDR10VSIFReceive == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_VSIF_RECEIVED();
        }
        else
        {
            // Clr HDR10+ data strucr if no received
            CLR_ADVANCED_HDR10_INFO_DATA();
            CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
        }

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
        bAdvancedHDR10EMPReceive = GET_HDMI_FRL_MAC_RX3_DHDR_EMP_TYPE40_RECEIVED();
        if(bAdvancedHDR10EMPReceive == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX3_DHDR_EMP_TYPE40_RECEIVED();
        }
        else
        {
            CLR_ADVANCED_HDR10_DHDR_DATA();
        }
#endif

        if((bAdvancedHDR10VSIFReceive == _TRUE) || (bAdvancedHDR10EMPReceive == _TRUE))
        {
            // when continually receive, TimerEvent to detect HDR10+ (only VSIF/EMP -> No VSIF/EMP transition)
            ScalerTimerActiveTimerEvent(GET_ADVANCED_HDR10_METADATA_DETECT_TIME(), _SCALER_TIMER_EVENT_RX3_HDMI_FRL_ADVANCED_HDR10_DETECT);

            SET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING();
        }
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((GET_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING() == _FALSE) && (ScalerDMGetMetadataSupport(enumMappingPort) == _TRUE))
    {
        if((GET_HDMI_FRL_MAC_RX3_DM_EMP_RECEIVED() == _TRUE) || (GET_HDMI_FRL_MAC_RX3_DM_VSIF_RECEIVED() == _TRUE))
        {
            CLR_HDMI_FRL_MAC_RX3_DM_EMP_RECEIVED();
            CLR_HDMI_FRL_MAC_RX3_DM_VSIF_RECEIVED();

            // when continually receive, TimerEvent to detect DM (only VSIF/EMP -> No VSIF/EMP transition)
            ScalerTimerActiveTimerEvent(100, _SCALER_TIMER_EVENT_RX3_HDMI_FRL_DM_DETECT);

            SET_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING();
        }
        else
        {
            // case for DM packet -> no packet
        }
    }
#endif
#endif

    // To do Packet detection
    if(GET_HDMI_FRL_MAC_RX3_PACKET_DETECTING() == _FALSE)
    {
        // HDMI Packet Detected
        ScalerHdmiFrlMacRx3PacketDetect(_NOT_WAIT);

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
        // PRIORITY TOP to check 3D Video format if HDMI or HF VSIF from 1->0
        if((GET_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED() == _FALSE) && (GET_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED() == _FALSE))
        {
            CLR_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID();
        }

        if(GET_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED() == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED();
        }
#endif

        if(GET_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED() == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED();
        }
        else
        {
#if(_HDMI21_ALLM_SUPPORT == _ON)
            CLR_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();
#endif
        }


        if(GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
        {
            if(ScalerHdmiFrlMacRx3ColorInfoChanged() == _TRUE)
            {
                DebugMessageRx3("FRL Rx3: Color Info Changed", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if(ScalerHdmiFrlMacRx3AviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx3("FRL Rx3: Pixel Repetition Info Changed", enumSourceType);

                    // Turn off DPF output
                    SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }
        else
        {
            if(GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_RGB)
            {
                DebugMessageRx3("FRL Rx3: AVI Info Frame Not Received and not RGB", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }

#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
            if(GET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort) != _RGB_QUANTIZATION_RESERVED)
            {
                DebugMessageRx3("FRL Rx3: No Quantization Range Specified", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if(GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx3("FRL Rx3: Pixel Repetition Not Received and not Pixel repetition 0", enumSourceType);

                    // Turn off DPF output
                    SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            if((ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_41_PORT_PAGE77_HDMI_VWDSR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT0) && (ScalerGetBit(P77_CC_HDMI_GPVS, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT0))
            {
                DebugMessageRx3("FRL Rx3: HDMI AVI info frame has changed", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }
        }

        if(GET_HDMI_FRL_MAC_RX3_GCP_RECEIVED() == _TRUE)
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) && (ScalerHdmiFrlMacRx3GetColorDepth() != GET_COLOR_DEPTH(enumMappingPort)))
                {
                    DebugMessageRx3("FRL Rx3: Color Depth Has Changed", GET_COLOR_DEPTH(enumMappingPort));

                    // Turn off DPF output
                    SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }
        else
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx3("FRL Rx3: HDMI GCP PACKET Not Received and not 8 bit", enumSourceType);

                    // Turn off DPF output
                    SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _OFF)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
        if(GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED() == _TRUE)
        {
            if((bit)GET_HDMI_RX3_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) != ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort))
            {
                DebugMessageRx3("HDMI Freesync Status Change", ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort));
                return _FALSE;
            }
        }
        else
        {
            if(ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort) == _TRUE)
            {
                DebugMessageRx3("HDMI Freesync Status Change", ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort));
                return _FALSE;
            }
        }
#endif
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(GET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED() != ScalerTmdsMacRxGetFreesyncReplayProc(enumMappingPort))
        {
            DebugMessageRx3("AMD SPD Infoframe Status Change", GET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED());
            return _FALSE;
        }
#endif
    }

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
    if(GET_TMDS_MAC_RX3_EMP_DETECTING() == _FALSE)
    {
        ScalerHdmiFrlMacRx3EmpPacketDetect(_NOT_WAIT);

#if(_HDMI_FORCE_VRR_SUPPORT == _OFF)
#if(_HDMI21_VRR_SUPPORT == _ON)
        if((GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG() == _TRUE) && (GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE))
        {
            DebugMessageRx3("FRL Rx3: VTEM from NA(or MLDS) to received", 0x00);
            CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG();

            return _FALSE;
        }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE)
        {
            // FVA factor change
            if(GET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR() != (ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_FVA_FACTOR_M1) + 1))
            {
                // Turn off DPF output
                SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }
        }
#endif
#endif
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // CVTEM Changed
    if(ScalerDscDecoderGetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX3)) == _ENABLE)
    {
        ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX3), _DISABLE);

        DebugMessageRx3("FRL Rx3: DSC Status Change", 0);

        // Turn off DPF output
        SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

        return _FALSE;
    }

    if(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3) != _DSC_MAC_NONE)
    {
        BYTE ucDscMac = ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3);

        if(ScalerHdmiFrlMacRxGetCvtemReceived(enumMappingPort) == _FALSE)
        {
            DebugMessageRx3("FRL Rx3: Video Stream Compression Disable", 0);

            // Turn off DPF output
            SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

            return _FALSE;
        }

        if(ScalerDscDecoderPpsChangeCheck(ucDscMac) == _FALSE)
        {
            DebugMessageRx3("7. DSC PPS Change", 0);

            // Turn off DPF output
            SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

            return _FALSE;
        }

        if(ScalerDscDecoderFifoCheck(ucDscMac, _DSC_FIFO_POLLING_CHECK) == _FALSE)
        {
            DebugMessageRx3("FRL Rx3: DSC Fifo Under/Overflow", 0);

            // Turn off DPF output
            SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

            return _FALSE;
        }
    }
#endif
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : usClkCount
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3CheckCdrStable(WORD usClkCount)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    // Check Current Measured Freq. is the same as previously locked
    if(abs(usClkCount - ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE0)) > (usClkCount >> 6))
    {
        DebugMessageRx3("FRL Rx3: L0 CDR Unstable", ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE0));

        return _FALSE;
    }

    if(abs(usClkCount - ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE1)) > (usClkCount >> 6))
    {
        DebugMessageRx3("FRL Rx3: L1 CDR Unstable", ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE1));

        return _FALSE;
    }

    if(abs(usClkCount - ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE2)) > (usClkCount >> 6))
    {
        DebugMessageRx3("FRL Rx3: L2 CDR Unstable", ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE2));

        return _FALSE;
    }

    if((ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES) && (abs(usClkCount - ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE3)) > (usClkCount >> 6)))
    {
        DebugMessageRx3("FRL Rx3: L3 CDR Unstable", ScalerHdmiFrlMacRx3OffMeasureClk(_HDMI_FRL_LANE3));

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerHdmiFrlMacRx3OffMeasureClk(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;

    // Enable Rx_EN (Lane3)?????????????
    // ScalerSetBit(P7C_1A_CMU_00, ~_BIT7, _BIT7);

    // Set div36
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_28_PORT_PAGE77_HDMI_NTX1024TR0, ~_BIT6, _BIT6);

    // Select reference clk to Xtal Clk and measure clk
    ScalerTmdsPhyRxCdrMeasureClkSelect(ScalerTmdsMacRxRxDxMapping(_RX3), ucMeasureClk);

    // Start Measure
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_28_PORT_PAGE77_HDMI_NTX1024TR0, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US();

        if((ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_28_PORT_PAGE77_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_28_PORT_PAGE77_HDMI_NTX1024TR0, 2, &pData[0], _AUTOINC);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : Clear All Received Status of Packet
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ResetAllPacketReceiveStatus(void)
{
    // Clear AVI infoframe & GCP packet Detection Flag
    ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Clear RSV 0~3 detection Flag
    ScalerSetByte(P77_CC_HDMI_GPVS, (_BIT6 | _BIT5));
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Clear VSIF(RSV7) & RSV 4 detection Flag
    ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // Clear VTEM flag
    ScalerSetBit(P67_50_EMP_HDMI, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Clear CVTEM flag
    ScalerSetBit(P67_52_EMP_DSC, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Clear DHDREM flag
    ScalerSetBit(P67_53_EMP_DHDR, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Clear VS EMP flag
    ScalerSetBit(P67_51_EMP_VS, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
}

//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3PacketDetect(bit bWait)
{
#if(_DM_FUNCTION == _ON)
    EnumInputPort enumDx = ScalerTmdsMacRxRxDxMapping(_RX3);
#endif

    if(bWait == _WAIT)
    {
        BYTE ucRSVColorDepth = 0x00;

        // Polling 3 frame for detect AVI and GCP
        if(ScalerTimerPollingFlagProc(130, P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
            {
                SET_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

                SET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();

                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P77_CC_HDMI_GPVS, 0x01);

                DebugMessageRx3("FRL Rx3: AVI and GCP", 0);
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT0)
            {
                SET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();

                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P77_CC_HDMI_GPVS, 0x01);

                // Polling more time to wait GCP when AVI IF has been received.
                if(ScalerTimerPollingFlagProc(180, P77_D5_HDMI_RSV64_IE, _BIT1, _TRUE) == _TRUE)
                {
                    SET_HDMI_FRL_MAC_RX3_GCP_RECEIVED();
                    DebugMessageRx3("FRL Rx3: AVI and GCP retry", 0);
                }
                else
                {
                    CLR_HDMI_FRL_MAC_RX3_GCP_RECEIVED();
                    DebugMessageRx3("FRL Rx3: Only AVI", 0);
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT1)
            {
                SET_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

                // Polling more time to wait AVI IF when GCP has been received.
                if(ScalerTimerPollingFlagProc(180, P77_D5_HDMI_RSV64_IE, _BIT0, _TRUE) == _TRUE)
                {
                    SET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();

                    // Clear AVI Info Frame Variation flag
                    ScalerSetByte(P77_CC_HDMI_GPVS, 0x01);

                    DebugMessageRx3("FRL Rx3: AVI retry and GCP", 0);
                }
                else
                {
                    CLR_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();
                    DebugMessageRx3("FRL Rx3: Only GCP", 0);
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

            CLR_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
        ScalerHdmiFrlMacRx3RoundRobinDetect(_WAIT);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P77_D5_HDMI_RSV64_IE, (_BIT2), _TRUE) == _TRUE)
        {
            SET_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        // Detect for Deep color
        ucRSVColorDepth = ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x42, (_BIT3 | _BIT2 | _BIT1 | _BIT0));  // 0x42: RSV5 GCP SB1

        if(((GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLOR_SPACE) == _COLOR_SPACE_YCBCR422)) ||
           ((GET_HDMI_FRL_MAC_RX3_GCP_RECEIVED() == _TRUE) && (ScalerGetBit(P77_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != ucRSVColorDepth)))
        {
            // Wait at least 3 frame for HW auto update color depth value
            if(GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                BYTE ucFrameRate = 0x00;

                if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_VIC) != 0x00)
                {
                    ucFrameRate = ScalerTmdsMacRxGetVicVfreqParameter(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_VIC));
                }
                else if(ScalerHdmiFrlMacRx3Rsv6GetAviInfo(_AVI_INFO_FR) != 0x00)
                {
                    ucFrameRate = ScalerTmdsMacRxGetOvtVfreqParameter(ScalerHdmiFrlMacRx3Rsv6GetAviInfo(_AVI_INFO_FR));
                }

                if(ucFrameRate != 0x00)
                {
                    // 3ms to ensure HW apply
                    ScalerTimerDelayXms(3);
                    ScalerTimerDelayXms(3000 / (WORD)ucFrameRate);
                    if(ScalerGetBit(P77_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != ucRSVColorDepth)
                    {
                        // Wait 3 more frame for HW auto update color depth value
                        ScalerTimerDelayXms(3000 / (WORD)ucFrameRate);
                        DebugMessageRx3("FRL Rx3: More delay for GCP DPC HW update", ScalerGetBit(P77_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
                    }
                }
                else
                {
                    ScalerTimerDelayXms(130);
                }
            }
            else
            {
                ScalerTimerDelayXms(130);
            }
        }

        CLR_HDMI_FRL_MAC_RX3_PACKET_DETECTING();

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        CLR_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING();
#endif

#if(_DM_FUNCTION == _ON)
        CLR_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING();
        CLR_DRAM_RECEIVED_FROM_DM_DETECT(enumDx);
#endif
    }
    else
    {
        // Both GCP & AVI infoframe packet have been received
        if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Clear Detection Flag
            ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // GCP received
            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

            // AVI received
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();
        }
        else if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT1)
        {
            // Clear Detection Flag
            ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // GCP received
            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

            // AVI NO received
            // Manual Set Color Space and disable pixel repetition
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_50_PORT_PAGE77_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();
        }
        else if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT0)
        {
            // Clear Detection Flag
            ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // GCP No received
            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

            // AVI received
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();
        }
        else
        {
            // GCP No received
            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX3_GCP_RECEIVED();

            // AVI NO received
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_50_PORT_PAGE77_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerHdmiFrlMacRx3WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
        ScalerHdmiFrlMacRx3RoundRobinDetect(_NOT_WAIT);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
#if(_DM_FUNCTION == _ON)
        if((ScalerGetBit(P77_D5_HDMI_RSV64_IE, _BIT2) == _BIT2) || (GET_DRAM_RECEIVED_FROM_DM_DETECT(enumDx) == _TRUE))
#else
        if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, _BIT2) == _BIT2)
#endif
        {
            SET_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED();

#if(_DM_FUNCTION == _ON)
            // if realtime OSD support DM
            if(ScalerTmdsMacRxGetOsdDmSupport(enumDx) == _ON)
            {
                // clear FW flag only, don't w1c rsv received bit due to DM Detecting need
                CLR_DRAM_RECEIVED_FROM_DM_DETECT(enumDx);
            }
            else
            {
                // w1c RSV received bit
                ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            }
#else
            // w1c RSV received bit
            ScalerSetBit(P77_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#endif
        }
        else
        {
            CLR_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        SET_HDMI_FRL_MAC_RX3_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_RX3_HDMI_FRL_PACKET_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3PacketDetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX3_PACKET_DETECTING();
}

//--------------------------------------------------
// Description  : FRL MAC reset RX3 Timer Event
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3TimerEventReset(void)
{
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDMI_FRL_PACKET_DETECT);
    ScalerHdmiFrlMacRx3WatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD | _HDMI_FRL_DPF_FIFO_WD | _HDMI_EMP_TIMEOUT_WD), _DISABLE);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON))
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDMI_FRL_EMP_DETECT);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDMI_FRL_ADVANCED_HDR10_DETECT);
#endif

    // Clear DPF Pixel Mode Mismatch flag
    CLR_HDMI_FRL_MAC_RX3_DPF_PIXEL_MODE_MISMATCH();
}

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
//--------------------------------------------------
// Description  : RoundRobin Detect
// Input Value  : bWait
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RoundRobinDetect(bit bWait)
{
    if(bWait == _WAIT)
    {
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
        bit bFsPktRvd = _FALSE;
#endif

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        //-----------------------------------------
        // Polling 3 frame for RSV resceive packet
        //-----------------------------------------
        if((ScalerTimerPollingFlagProc(130, P77_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE) || (ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, (_BIT7 | _BIT6)) != 0x00))
        {
            if(ScalerGetBit(P77_CC_HDMI_GPVS, _BIT5) == _BIT5)
            {
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P77_96_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_0);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_0);
#endif
                }
            }

            if(ScalerGetBit(P77_CC_HDMI_GPVS, _BIT6) == _BIT6)
            {
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P77_97_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_1);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_1);
#endif
                }
            }

            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, _BIT7) == _BIT7)
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P77_98_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_2);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_2);
#endif
                }
            }

            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, _BIT6) == _BIT6)
            {
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P77_99_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_3);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_3);
#endif
                }
            }
        }
#endif

        //-----------------------------------------
        // FS PR Flag setting
        //-----------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(ScalerTimerPollingFlagProc(130, P77_D5_HDMI_RSV64_IE, _BIT3, _TRUE) == _TRUE)
        {
            SET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX3_FREESYNC_REPLAY_RECEIVED();
        }
#endif

        //-----------------------------------------
        // FS SPD INFO Flag setting
        //-----------------------------------------
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        bFsPktRvd = GET_TMDS_MAC_RX3_FS_VALUABLE();
#else
        for(BYTE ucCount = 0; ucCount < 65; ucCount++)
        {
            ScalerTimerDelayXms(2);

            if(GET_TMDS_MAC_RX3_FS_VALUABLE() == _TRUE)
            {
                bFsPktRvd = _TRUE;
                break;
            }
        }
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        if((GET_FREESYNC_HDMI_VCP() == 0x01) && (bFsPktRvd == _TRUE))
#else
        if(bFsPktRvd == _TRUE)
#endif
        {
            SET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX3_SPD_INFO_FRAME_RECEIVED();
        }
#endif
    }
    else
    {
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        //-----------------------------------------
        // RSV resceive packet
        //-----------------------------------------
        // Check for RSV0
        if(ScalerGetBit(P77_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            ScalerSetByte(P77_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P77_96_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_0);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_0);
#endif
            }
        }

        // Check for RSV1
        if(ScalerGetBit(P77_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerSetByte(P77_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P77_97_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_1);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_1);
#endif
            }
        }

        // Check for RSV2
        if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, _BIT7) == _BIT7)
        {
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P77_98_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_2);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_2);
#endif
            }
        }

        // Check for RSV3
        if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, _BIT6) == _BIT6)
        {
            ScalerSetDataPortBit_EXINT0(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P77_99_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx3RsvSpdHandler(_HDMI_RSV_3);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx3RsvVsifHandler(_HDMI_RSV_3);
#endif
            }
        }
#endif

        //-----------------------------------------
        // FS PR Flag setting
        //-----------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(ScalerGetBit(P77_D5_HDMI_RSV64_IE, _BIT3) == _BIT3)
        {
            SET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX3_FREESYNC_REPLAY_RECEIVED();
        }
#endif

        //-----------------------------------------
        // FS SPD INFO Flag setting
        //-----------------------------------------
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        if((GET_FREESYNC_HDMI_VCP() == 0x01) && (GET_TMDS_MAC_RX3_FS_VALUABLE() == _TRUE))
#else
        if(GET_TMDS_MAC_RX3_FS_VALUABLE() == _TRUE)
#endif
        {
            SET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED();
            CLR_TMDS_MAC_RX3_FS_VALUABLE();
        }
        else
        {
            CLR_TMDS_RX3_SPD_INFO_FRAME_RECEIVED();
        }
#endif
    }
}

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : Get SPD Info Product Description
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RsvSpdHandler(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucI = 0;
    BYTE ucVnCount = 0;
    BYTE pucHdmiVenderName[4] = {0};

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    for(ucVnCount = 0; ucVnCount < 4; ucVnCount++)
    {
        pucHdmiVenderName[ucVnCount] = ScalerGetByte(P77_CE_HDMI_PSDP);
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
                ScalerSetByte(P77_CD_HDMI_PSAP, 0x5A);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0x79);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0x98);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0xB7);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 16; ucI++)
        {
            g_stTmdsMacRx3SpdInfo.pucHdmiProductDescription[ucI] = ScalerGetByte(P77_CE_HDMI_PSDP);
        }
    }
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    else if((pucHdmiVenderName[0] == 0x1A) && (pucHdmiVenderName[1] == 0x00) && (pucHdmiVenderName[2] == 0x00) && (GET_TMDS_MAC_RX3_FS_VALUABLE() == _FALSE))
    {
        SET_TMDS_MAC_RX3_FS_VALUABLE();

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0x51);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0x70);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0x8F);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte(P77_CD_HDMI_PSAP, 0xBF);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 28; ucI++)
        {
            g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[ucI] = ScalerGetByte(P77_CE_HDMI_PSDP);
        }
    }
#endif
}
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
//--------------------------------------------------
// Description  : RSVx into IRQ Handler
// Input Value  : ulOui, enumRsvNumber
// Output Value : void
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RsvVsifHandler(EnumHdmiRsvNumber enumRsvNumber)
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
            ScalerSetByte_EXINT(P77_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte_EXINT(P77_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte_EXINT(P77_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte_EXINT(P77_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    ulOui = ScalerGetByte_EXINT(P77_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P77_CE_HDMI_PSDP);
    ulOui = (ulOui << 8) + ScalerGetByte_EXINT(P77_CE_HDMI_PSDP);

    switch(ulOui)
    {
#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
        case _HDMI_VSIF_OUI:

            SET_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED();

            ScalerHdmiFrlMacRx3HdmiVsif3dVideoProc(enumRsvNumber);

            break;
#endif

#if((_HDMI21_ALLM_SUPPORT == _ON) || (_HDMI21_CCBPC_SUPPORT == _ON) || (_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON))
        case _HF_VSIF_OUI:

            SET_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED();

#if(_HDMI21_ALLM_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3AllmProc(enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3CcbpcProc(enumRsvNumber);
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3HfVsif3dVideoProc(enumRsvNumber);
#endif
            break;
#endif

        default:
            break;
    }
}
#endif
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Parser 3D Video format from HDMI VSIF
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3HdmiVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit b3dVideo = _FALSE;

    // Get HDMI Video Format (PB4)
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x55);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x74);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x93);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0xB2);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    if(b3dVideo == _TRUE)
    {
        SET_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID();
    }
    else
    {
        CLR_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID();
    }
}

//--------------------------------------------------
// Description  : Parser 3D Video format from HF VSIF
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3HfVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit b3dVideo = _FALSE;

    // Get HDMI Video Format (PB5)
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x56);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x75);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x94);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0xB3);
            b3dVideo = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    if(b3dVideo == _TRUE)
    {
        SET_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID();
    }
    else
    {
        CLR_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID();
    }
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable ALLM
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3AllmProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit bAllm = 0;

#if(_DM_FUNCTION == _ON)
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX3);
#endif

    // Get ALLM bit
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x56);
            bAllm = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x75);
            bAllm = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x94);
            bAllm = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0xB3);
            bAllm = (((ScalerGetByte(P77_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    // Enable/Disable ALLM
    if(bAllm == _TRUE)
    {
        SET_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxSetDmAllmStatus(enumInputPort);
#endif
    }
    else
    {
        CLR_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxClrDmAllmStatus(enumInputPort);
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
void ScalerHdmiFrlMacRx3CcbpcProc(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucCcbpcValue = 0;

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x56);
            ucCcbpcValue = (ScalerGetByte(P77_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x75);
            ucCcbpcValue = (ScalerGetByte(P77_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0x94);
            ucCcbpcValue = (ScalerGetByte(P77_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P77_CD_HDMI_PSAP, 0xB3);
            ucCcbpcValue = (ScalerGetByte(P77_CE_HDMI_PSDP) & 0xF0) >> 4;
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
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Description  : HDR10+ VSIF Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3AdvancedHdr10DetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING();
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : DM Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3HdmiDmDetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING();
}
#endif

//--------------------------------------------------
// Description  : Hdmi2.1 Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3WatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD) && (GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE))
        {
            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_41_PORT_PAGE77_HDMI_VWDSR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P77_CC_HDMI_GPVS, _BIT0);

                // Enable Color Space/ Colorimetry Change Detection
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_45_PORT_PAGE77_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_AA_PORT_PAGE77_HDMI_PVGCR3, ~_BIT7, _BIT7);

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_41_PORT_PAGE77_HDMI_VWDSR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetByte(P77_CB_HDMI_SR, _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }

        if((ucWDType & _HDMI_FRL_DPF_FIFO_WD) == _HDMI_FRL_DPF_FIFO_WD)
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, _BIT6) == 0x00)
                {
                    // Clear DPF overflow and underflow flag
                    ScalerSetByte(P68_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4));

                    // Enable DSC Watch Dog when MAC DPF overflow or underflow
                    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT6, _BIT6);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P68_A0_DPF_OUTPUT_0, _BIT3) == 0x00)
                {
                    // Clear DPF overflow and underflow flag
                    ScalerSetByte(P68_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4));

                    // Enable DPF Watch Dog
                    ScalerSetBit(P68_A0_DPF_OUTPUT_0, ~(_BIT3 | _BIT0), _BIT3);
                }
            }
        }

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON))
        /*if((ucWDType & _HDMI_EMP_TIMEOUT_WD) == _HDMI_EMP_TIMEOUT_WD)
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                if(ScalerGetBit(P67_55_EMP_TIMEOUT_2, _BIT1) == 0x00)
                {
                    // Clear CVTEM Timeout flag
                    ScalerSetBit(P67_54_EMP_TIMEOUT_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT5);

                    // EMP Timeout to enable DSC_DPF WD
                    ScalerSetBit(P67_55_EMP_TIMEOUT_2, ~(_BIT2 | _BIT1), _BIT1);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P67_55_EMP_TIMEOUT_2, _BIT2) == 0x00)
                {
                    // Clear VTEM / VSEM / DHDREM Timeout flag
                    ScalerSetBit(P67_54_EMP_TIMEOUT_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT4));

                    // EMP Timeout to enable DPF WD
                    ScalerSetBit(P67_55_EMP_TIMEOUT_2, ~(_BIT2 | _BIT1), _BIT2);
                }
            }
        }*/
#endif
    }
    else
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            // Disable packet variation Watch Dog
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_41_PORT_PAGE77_HDMI_VWDSR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_45_PORT_PAGE77_HDMI_PVGCR0, 0x00);
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_AA_PORT_PAGE77_HDMI_PVGCR3, 0x00);

            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_46_PORT_PAGE77_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT7, 0x00);
        }

        if((ucWDType & _HDMI_FRL_DPF_FIFO_WD) == _HDMI_FRL_DPF_FIFO_WD)
        {
            // Disable MAC DPF Watch Dog
            ScalerSetBit(P68_A0_DPF_OUTPUT_0, ~(_BIT3 | _BIT0), 0x00);

            // Disable MAC to DSC Watch Dog
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT6, 0x00);
        }

        if((ucWDType & _HDMI_EMP_TIMEOUT_WD) == _HDMI_EMP_TIMEOUT_WD)
        {
            // Disable EMP Timeout Watch Dog (RL6978 not support emp_dsc_to_err wd)
            SET_HDMI_RX3_EMP_TIMEOUT_WD_DISABLE();
        }
    }
}

//--------------------------------------------------
// Description  : HDMI2.1 Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3VideoSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    BYTE ucColorSpace = 0;

    if(GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

        ucColorSpace = ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(ucColorSpace == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx3("FRL Rx3: Get Color Space RGB", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);
        }
        else if(ucColorSpace == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx3("FRL Rx3: Get Color Space YUV422", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR422);
        }
        else if(ucColorSpace == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx3("FRL Rx3: Get Color Space YUV420", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx3("FRL Rx3: Get Color Space YUV444", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 0", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 1", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 2", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 3", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 4", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 5", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 6", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 7", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 8", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition 9", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Pixel Repetition Error", 0x00);
                SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerHdmiFrlMacRx3ColorimetrySetting();

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
        // Set Quantization
        ScalerHdmiFrlMacRx3QuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
        SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);
        SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_RESERVED);

        // Manual Set Color Space to RGB and disable pixel repetition
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable down sampling
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_50_PORT_PAGE77_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerHdmiFrlMacRx3SetPorchColor(GET_COLOR_SPACE(enumMappingPort));
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRx3GetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:
                return ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_CONTENT_TYPE:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x08, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_PIXEL_REPETITION:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:
                return (ScalerGetDataPortBit(P77_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:
                return ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x07);

            default:
                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents From RSV6
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRx3Rsv6GetAviInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x61, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x62, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x63, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_ADD_EXTENDED_COLORIMETRY:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x6E, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x63, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x65, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:
                return ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x61, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x63, _BIT7) >> 7);

            case _AVI_INFO_CONTENT_TYPE:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x65, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_PIXEL_REPETITION:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x65, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:
                return (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x62, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:
                return ScalerGetDataPortSingleByte(P77_D0_HDMI_PSAP2, 0x64);

            case _AVI_INFO_FR:
                return ((ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x6F, _BIT6) >> 2) | (ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x6E, (_BIT3 | _BIT2 | _BIT1 | _BIT0))));

            case _AVI_INFO_RID:
                return ScalerGetDataPortBit(P77_D0_HDMI_PSAP2, 0x6F, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            default:
                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : FRL Rx3 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ColorimetrySetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx3("FRL Rx3: Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx3("FRL Rx3: Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx3("FRL Rx3: Get Colorimetry 709", 0x00);

                SET_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx3("FRL Rx3: Get Colorimetry Extended", 0x00);

                SET_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT);

                ScalerHdmiFrlMacRx3ColorimetryExtSetting();

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX3_COLORIMETRY_PREVALUE(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_RX3_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx3("FRL Rx3: Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx3("FRL Rx3: Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT);

                ScalerHdmiFrlMacRx3ColorimetryExtSetting();

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx3 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ColorimetryExtSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_RX3_COLORIMETRY_EXT_PREVALUE(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_RX3_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            case _AVI_COLORIMETRY_EXT_111:

                DebugMessageRx3("FRL Rx3: Get Colorimetry Additional Extended", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_ADD);

                ScalerHdmiFrlMacRx3ColorimetryAddExtSetting();

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX3_COLORIMETRY_EXT_PREVALUE(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_RX3_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx3("FRL Rx3: Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            case _AVI_COLORIMETRY_EXT_111:

                DebugMessageRx3("FRL Rx3: Get Colorimetry Additional Extended", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_ADD);

                ScalerHdmiFrlMacRx3ColorimetryAddExtSetting();

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : FRL Rx3 Colorimetry Additional Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ColorimetryAddExtSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        // Get additional extended colorimetry
        SET_RX3_COLORIMETRY_ADD_EXT_PREVALUE(ScalerHdmiFrlMacRx3Rsv6GetAviInfo(_AVI_INFO_ADD_EXTENDED_COLORIMETRY));

        // Get additional extended colorimetry
        switch(GET_RX3_COLORIMETRY_ADD_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_ADD_EXT_0010:

                DebugMessageRx3("FRL Rx3: Get Colorimetry ADD_EXT_YCC_ITUR_BT2100", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_YCC_ITUR_BT2100);

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX3_COLORIMETRY_ADD_EXT_PREVALUE(ScalerHdmiFrlMacRx3Rsv6GetAviInfo(_AVI_INFO_ADD_EXTENDED_COLORIMETRY));

        switch(GET_RX3_COLORIMETRY_ADD_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_ADD_EXT_0000:

                DebugMessageRx3("FRL Rx3: Get Colorimetry ADD_EXT_RGB_SMPTE_ST2113_P3D65", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3D65);

                break;

            case _AVI_COLORIMETRY_ADD_EXT_0001:

                DebugMessageRx3("FRL Rx3: Get Colorimetry ADD_EXT_RGB_SMPTE_ST2113_P3DCI", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3DCI);

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RESERVED);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Get Content Type
// Input Value  : None
// Output Value : EnumContentType
//--------------------------------------------------
EnumContentType ScalerHdmiFrlMacRx3GetAviContentType(void)
{
    BYTE ucContentType = ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_CONTENT_TYPE);

    switch(ucContentType)
    {
        case 0x00:

            if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_IT_CONTENT) == 0x01)
            {
                return _CONTENT_TYPE_GRAPHICS;
            }
            else
            {
                return _CONTENT_TYPE_N0_DATA;
            }

        case 0x01:

            return _CONTENT_TYPE_PHOTO;

        case 0x02:

            return _CONTENT_TYPE_CINEMA;

        case 0x03:

            return _CONTENT_TYPE_GAME;

        default:

            return _CONTENT_TYPE_N0_DATA;
    }
}

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
//--------------------------------------------------
// Description  : TMDS Rx3 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3QuantizationSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        SET_RX3_QUANTIZATION_PREVALUE(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_RX3_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx3("FRL Rx3: Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx3("FRL Rx3: Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        switch(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx3("FRL Rx3: Get RGB LIMIT RANGE", 0x00);

                SET_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx3("FRL Rx3: Get RGB FULL RANGE", 0x00);

                SET_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx3("FRL Rx3: Get RGB DEFAULT RANGE", 0x00);

                SET_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx3("FRL Rx3: Get RGB RESERVED RANGE", 0x00);

                SET_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx3("FRL Rx3: Get RGB RANGE Error", 0x00);

                SET_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : Received Color Depth
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRx3GetColorDepth(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_HDMI_FRL_MAC_RX3_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P77_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P77_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1))
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P77_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1 | _BIT0))
        {
            return _COLOR_DEPTH_16_BITS;
        }
    }

    return _COLOR_DEPTH_8_BITS;
}

//--------------------------------------------------
// Description  : HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3ColorInfoChanged(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    BYTE pucTemp[2] = {0};

    // Check Color Space
    if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(enumMappingPort))
    {
        DebugMessageRx3("FRL Rx3: Color Space Changed", 0x00);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _TRUE;
        }
        else
        {
            if(ScalerHdmiFrlMacRx3SeamlessReset() == _SOURCE_NONE)
            {
                return _TRUE;
            }
        }
#else
        return _TRUE;
#endif
    }

    // Check Colorimetry
    if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_RX3_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx3("FRL Rx3: Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_RX3_COLORIMETRY_PREVALUE();

            ScalerHdmiFrlMacRx3ColorimetrySetting();

            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_RX3_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_RX3_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(enumMappingPort) == _COLORIMETRY_EXT)
        {
            if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_RX3_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx3("FRL Rx3: Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_RX3_COLORIMETRY_EXT_PREVALUE();

                    ScalerHdmiFrlMacRx3ColorimetryExtSetting();

                    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_RX3_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_RX3_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_RX3_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx3("FRL Rx3: YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_RX3_QUANTIZATION_PREVALUE();

                ScalerHdmiFrlMacRx3QuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_RX3_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
    if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_RX3_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx3("FRL Rx3: RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerHdmiFrlMacRx3QuantizationSetting();

                SET_RX3_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect HDMI AVI pixel repetition
// Input Value  : None
// Output Value : _TRUE => Current Info is different from previous setting
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3AviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerHdmiFrlMacRx3GetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION())
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    SET_HDMI_FRL_RX3_DPF_RGB_OUTPUT_DISABLE();

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P68_A2_DPF_OUTPUT_2, 0x80);
        ScalerSetByte(P68_A3_DPF_OUTPUT_3, 0x00);
        ScalerSetByte(P68_A4_DPF_OUTPUT_4, 0x0F);
        ScalerSetByte(P68_A5_DPF_OUTPUT_5, 0x00);
        ScalerSetByte(P68_A6_DPF_OUTPUT_6, 0x80);
        ScalerSetByte(P68_A7_DPF_OUTPUT_7, 0x00);
    }
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P68_A2_DPF_OUTPUT_2, 0x10);
        ScalerSetByte(P68_A3_DPF_OUTPUT_3, 0x00);
        ScalerSetByte(P68_A4_DPF_OUTPUT_4, 0x10);
        ScalerSetByte(P68_A5_DPF_OUTPUT_5, 0x00);
        ScalerSetByte(P68_A6_DPF_OUTPUT_6, 0x80);
        ScalerSetByte(P68_A7_DPF_OUTPUT_7, 0x00);
    }
    else
    {
        ScalerSetByte(P68_A2_DPF_OUTPUT_2, 0x00);
        ScalerSetByte(P68_A3_DPF_OUTPUT_3, 0x00);
        ScalerSetByte(P68_A4_DPF_OUTPUT_4, 0x00);
        ScalerSetByte(P68_A5_DPF_OUTPUT_5, 0x00);
        ScalerSetByte(P68_A6_DPF_OUTPUT_6, 0x00);
        ScalerSetByte(P68_A7_DPF_OUTPUT_7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Hdmi2.1 Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ResetProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    // Clear FRL rate
    ScalerHdmiFrlMacRxClrDxFrlRate(enumMappingPort);

    // Clear Rebuild PHY IRQ and flag
    ScalerSetByte(P77_E6_HDMI_TRANSDET_CTRL2, 0x0F);

    // Clear Rebuild PHY Event
    CLR_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT();

    // Clear FRL set PHY flag
    CLR_HDMI_FRL_MAC_RX3_PHY_SET();

    // Clear CED Valid flag
    ScalerSetBit(P77_08_HDMI21_FRL_CED_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Clear RSED Valid flag
    ScalerSetBit(P68_10_HDMI21_RS_0, ~_BIT3, 0x00);

    // Reset SCDC
    ScalerSetBit(P72_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

#if((_HDMI_SUPPORT == _ON) && (_HDMI20_SUPPORT == _ON))
    ScalerTmdsMacRxSetScdcInfo(enumMappingPort);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
    if(ScalerTmdsMacRxGetFreeSyncSupport(enumMappingPort) == _FREESYNC_SUPPORT_ON)
    {
        ScalerTmdsMacRxSetAmdAupiScdcInfo(enumMappingPort, _ENABLE);
    }
    else
    {
        ScalerTmdsMacRxSetAmdAupiScdcInfo(enumMappingPort, _DISABLE);
    }
#endif
#endif

    // Reset Link Training State
    SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);

    // Disable DPF CLK
    ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // reset MAC selection to MAC2.0
    ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, 0x00);

    // reset PHY to MAC2.0
    ScalerTmdsPhyRxSelectMode(enumMappingPort, _HDMI_VERSION_2_0);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3PowerSavingProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, _BIT6) == _BIT6)
    {
        // Clear FLT_ready
        ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT6, 0x00);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        // Clear SCDC 0x40[7] DSC dec fail
        ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
        // Set Status update
        ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
    }

    // Disable DPF CLK
    ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    ScalerHdmiFrlMacRx3LinkTrainingDisable();

    // Reset Link Training State
    SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);

    // reset MAC selection to MAC2.0
    ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, 0x00);

    // reset PHY to MAC2.0
    ScalerTmdsPhyRxSelectMode(enumMappingPort, _HDMI_VERSION_2_0);

    // Clear CED/RSED read flag
    ScalerSetByte(P72_25_HDMI_CTRL_25, (_BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : Hdmi2.1 Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3PowerOffProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, _BIT6) == _BIT6)
    {
        // Clear FLT_ready
        ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT6, 0x00);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        // Clear SCDC 0x40[7] DSC dec fail
        ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
        // Set Status update
        ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
    }

    // Disable DPF CLK
    ScalerSetBit(P68_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    ScalerHdmiFrlMacRx3LinkTrainingDisable();

    // Reset Link Training State
    SET_HDMI_FRL_MAC_RX3_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);

    // reset MAC selection to MAC2.0
    ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, 0x00);

    // reset PHY to MAC2.0
    ScalerTmdsPhyRxSelectMode(enumMappingPort, _HDMI_VERSION_2_0);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Check FLT no retrain bit for PS entering
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3EnterPowerSavingCheck(void)
{
    if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_30_PORT_PAGE72_HDMI_SCDC_30, _BIT1) == _BIT1)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Hdmi2.1 Clear FLT_Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3ClrFltReady(void)
{
    if(ScalerGetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, _BIT6) == _BIT6)
    {
        // Clear FLT_ready
        ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT6, 0x00);

        // Set Status update
        ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
    }

    // reset MAC selection to MAC2.0
    ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Save SCDC Status Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SaveScdcStatus(void)
{
    g_ucHdmiFrlMacRx3ScdcStatusFlag = ScalerGetDataPortSingleByte(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Restore SCDC FRL_Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3RestoreScdcStatus(void)
{
    ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT6, (g_ucHdmiFrlMacRx3ScdcStatusFlag & _BIT6));
}

//--------------------------------------------------
// Description  : Get Hdmi2.1 Dpf Pixel Mode
// Input Value  :
// Output Value : 1/2/4 Pixel Mode
//--------------------------------------------------
EnumHdmiFrlMacRxDpfPixelMode ScalerHdmiFrlMacRx3GetDpfPixelMode(void)
{
    switch(ScalerGetBit(P68_71_DPF_CTRL_1, (_BIT7 | _BIT6)))
    {
        case 0x00:
            return _HDMI_FRL_MAC_RX_DPF_FOUR_PIXEL_MODE;

        case _BIT6:
            return _HDMI_FRL_MAC_RX_DPF_TWO_PIXEL_MODE;

        default:
        case (_BIT7 | _BIT6):
        case _BIT7:
            break;
    }

    return _HDMI_FRL_MAC_RX_DPF_ONE_PIXEL_MODE;
}

//--------------------------------------------------
// Description  : Check Hdmi2.1 interlace Mode
// Input Value  :
// Output Value : _TRUE is interlace mode
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3InterlaceModeCheck(void)
{
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        return _FALSE;
    }
    else
#endif
    {
        return ((ScalerGetBit(P68_4A_FRL_MEASURE_A, _BIT4) == _BIT4) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Signal Detection for HDMI2.1(Power Saving)
// Input Value  :
// Output Value : True : HDMI2.1 Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerHdmiFrlMacRx3PSPreDetect(void)
{
    bit bResult = _FALSE;

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
    bResult = ScalerHdmiFrlMacRx3RebuildPhy();
#endif

    // Check Source write SCDC FRL_Rate Register
    if(ScalerGetBit(P72_3D_HDMI21_LT_0, _BIT7) == _BIT7)
    {
        bResult = _TRUE;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : FRL Link Training Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3LinkTrainingDisable(void)
{
    // Clear FLT_update and FRL_start
    ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~(_BIT5 | _BIT4), 0x00);

    // Clear link training related IRQ Flag and Disable link training IRQ
    ScalerSetBit(P72_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT5 | _BIT3));
#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    ScalerSetBit(P72_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT1);
#endif

    // Clear Link Training event
    CLR_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT();
    CLR_HDMI_FRL_MAC_RX3_FRL_START_EVENT();

    // Clear PHY SET flag
    CLR_HDMI_FRL_MAC_RX3_PHY_SET();

    // Disable CED Lock Transition IRQ
    ScalerSetByte(P77_17_HDMI21_FRL_CED_15, 0x00);

    // Disable CED Function and valid
    ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~_BIT6, 0x00);
    ScalerSetByte(P77_08_HDMI21_FRL_CED_0, 0x00);

    // Disable running disparity calculate
    ScalerSetBit(P77_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable RSED update and clear RSED update flag
    ScalerSetBit(P68_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), _BIT1);

    // Disable RSED Function and valid
    ScalerSetBit(P68_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
    ScalerSetBit(P68_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), 0x00);

    // Disable FRL small FIFO read and write clock
    ScalerSetBit(P77_A7_TMDS_PWDCTL, ~_BIT4, 0x00);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    // Clear SCDC 0x40[7] DSC dec fail
    ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT7, 0x00);

    // Set Status update
    ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
#endif
}

//--------------------------------------------------
// Description  : Set SCDC Update Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SetScdcUpdateFlag(DWORD ulAnd, BYTE ucOr)
{
    BYTE ucLoop = 0;

    // Set SCDC update flag addr
    ScalerSetByte(P72_39_HDMI_CTRL_39, _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10);

    // Check I2C not busy before update SCDC
    while(ucLoop < 20)
    {
        ucLoop ++;

        // Clear I2C busy flag
        ScalerSetBit(P72_20_HDMI_CTRL_20, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

        DELAY_XUS(100);

        // Check I2C is busy ot not
        if(ScalerGetBit(P72_20_HDMI_CTRL_20, (_BIT6 | _BIT4)) == 0x00)
        {
            break;
        }
    }

    // Set SCDC update flag value
    ScalerSetBit(P72_3A_HDMI_CTRL_3A, (BYTE)ulAnd, ucOr);
}

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3GetHDR10Data(BYTE *pucHDRData)
{
    BYTE ucAddressportBackup = 0x00;
    bit bBackupStatus = _FALSE;

    if(CPU32_IS_INSIDE_INTERRUPT() == _TRUE)
    {
        ucAddressportBackup = ScalerGetByte(P77_D0_HDMI_PSAP2);
        bBackupStatus = _TRUE;
    }

    ScalerGetDataPortByte(P77_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P77_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P77_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);

    if(bBackupStatus == _TRUE)
    {
        ScalerSetByte(P77_D0_HDMI_PSAP2, ucAddressportBackup);
    }
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    memcpy(&pucFreeSyncIIData[0], &g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[0], 11);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)


#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
DWORD ScalerHdmiFrlMacRx3FreeSyncHDMIGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    WORD usFreesyncVfreqmax = 0;
    WORD usFreesyncVfreqmin = 0;
    DWORD ulTargetOutputPixelRate = 0;
    WORD usAmdVfreqMaxBit = 0;
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX3);

    if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
    {
        usAmdVfreqMaxBit = _8_BIT;
    }
    else
    {
        usAmdVfreqMaxBit = _10_BIT;
    }

    if(enumContent == _SPD_INFO_OUI)
    {
        return (TO_DWORD(0, g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[3], g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[2], g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[1]));
    }

    if((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[1] == 0x1A) && (g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[2] == 0x00) && (g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[3] == 0x00))
    {
        switch(enumContent)
        {
            case _SPD_INFO_FREESYNC_SUPPORT:

                return (((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x01) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FREESYNC_ENABLE:

                return ((((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x02) >> 1) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FREESYNC_ACTIVE:

                return ((((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x04) >> 2) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FRAME_TYPE:

                return (((ScalerGetBit(P77_D6_HDMI_SHDR_IE, (_BIT1 | _BIT0))) == ((ScalerGetBit(P77_D6_HDMI_SHDR_IE, (_BIT3 | _BIT2))) >> 2)) ? _ON : _OFF);

            case _SPD_INFO_PQ_EOTF_ACTIVE:

                return ((((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[9] & _BIT5) >> 5) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_GAMMA_2_2_EOTF_ACTIVE:

                return ((((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[9] & 0x04) >> 2) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FIXED_RATE_CONTENT_ACTIVE:

                return (((g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[16] & 0x01) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_TARGET_OUTPUT_PIXEL_RATE:

                ulTargetOutputPixelRate = (((DWORD)g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[13] << 16) | ((DWORD)g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[14] << 8) | g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[15]);

                return ulTargetOutputPixelRate;

            case _SPD_INFO_FREESYNC_MIN_VFREQ:

                if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
                {
                    pData[1] = 0x00;
                    usFreesyncVfreqmin = (((WORD)pData[1] << 8) | g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[7]);
                }
                else
                {
                    usFreesyncVfreqmin = (((WORD)g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[11] << 8) | g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[7]);
                }

                usFreesyncVfreqmin &= usAmdVfreqMaxBit;

                if(((usFreesyncVfreqmin * 10) > _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) || ((usFreesyncVfreqmin * 10) < _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
                {
                    DebugMessageRx3("Freesync SPD info abnormal", 0);
                }

                return usFreesyncVfreqmin;

            case _SPD_INFO_FREESYNC_MAX_VFREQ:

                if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
                {
                    pData[1] = 0x00;
                    usFreesyncVfreqmax = (((WORD)pData[1] << 8) | g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[8]);
                }
                else
                {
                    usFreesyncVfreqmax = (((WORD)g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[12] << 8) | g_stTmdsMacRx3SpdFsInfo.pucHdmiFreesyncInfo[8]);
                }

                usFreesyncVfreqmax &= usAmdVfreqMaxBit;

                if(((usFreesyncVfreqmax * 10) > _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) || ((usFreesyncVfreqmax * 10) < _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
                {
                    DebugMessageRx3("Freesync SPD info abnormal", 0);
                }

                return usFreesyncVfreqmax;

            default:
                return 0x00;
        }
    }
    return 0x00;
}
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Detect HDMI2.1 EMP
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3EmpPacketDetect(bit bWait)
{
#if(_HDMI_SBTM_SUPPORT == _ON)
    BYTE ucHdmiSbtmCheckTime = 0;
#endif

    if(bWait == _WAIT)
    {
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
        // Clear VRR flag
        CLR_TMDS_MAC_RX3_HDMI21_VRR_EN();
        CLR_TMDS_MAC_RX3_HDMI21_QMS_EN();
#endif
#if(_HDMI21_FVA_SUPPORT == _ON)
        SET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR(1);
#endif
        // CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED();
        CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG();
#if(_HDMI21_VRR_SUPPORT == _ON)
        CLR_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG();
        CLR_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG();
#endif
        // Wait at least 2 frames for HW auto update VTEM flag and Length not 0
        if((ScalerTimerPollingFlagProc(90, P67_50_EMP_HDMI, _BIT6, _TRUE) == _TRUE) && ((ScalerGetByte(P67_65_HDMI_EMP_6) != 0x00) || (ScalerGetByte(P67_66_HDMI_EMP_7) != 0x00)))
        {
            SET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED();
        }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        // Wait at least 2 frames for HW auto update CVTEM flag and Length not 0
        if((ScalerTimerPollingFlagProc(90, P67_52_EMP_DSC, _BIT4, _TRUE) == _TRUE) && ((ScalerGetByte(P67_75_DSC_EMP_6) != 0x00) || (ScalerGetByte(P67_76_DSC_EMP_7) != 0x00)))
        {
            SET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED();
        }
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
        ucHdmiSbtmCheckTime = 18;

        while(ucHdmiSbtmCheckTime != 0)
        {
            if(g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmReceive == _TRUE)
            {
                DebugMessageRx3("HDMI Rx3 SBTM Receive", 0);

                SET_TMDS_MAC_RX3_SBTM_RECEIVE();
                g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmReceive = _FALSE;
                break;
            }
            ScalerTimerDelayXms(5);
            ucHdmiSbtmCheckTime--;
        }

        if((ucHdmiSbtmCheckTime == 0x00) && (g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmReceive == _FALSE))
        {
            DebugMessageRx3("HDMI Rx3 SBTM no Receive", 0);

            CLR_TMDS_MAC_RX3_SBTM_RECEIVE();
        }
#endif

        CLR_TMDS_MAC_RX3_EMP_DETECTING();
    }
    else
    {
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
        // VTEM have been received and Length not 0
        if((ScalerGetBit(P67_50_EMP_HDMI, _BIT6) == _BIT6) && ((ScalerGetByte(P67_65_HDMI_EMP_6) != 0x00) || (ScalerGetByte(P67_66_HDMI_EMP_7) != 0x00)))
        {
            // No Received / MLDS -> Received VTEM
            if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _FALSE)
            {
                SET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG();
            }
            else
            {
                // Received VTEM Continually then enable WD
                ScalerHdmiFrlMacRx3WatchDog(_HDMI_EMP_TIMEOUT_WD, _ENABLE);
            }

            SET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED();

            // Clear VTEM flag
            ScalerSetBit(P67_50_EMP_HDMI, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_HDMI21_VRR_SUPPORT == _ON)
            if((((bit)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _ENABLE) && (GET_TMDS_MAC_RX3_HDMI21_VRR_EN() != _ENABLE))
            {
                DebugMessageRx3("FRL Rx3: VRR_EN from 0 -> 1", 0x00);
                SET_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG();
                SET_TMDS_MAC_RX3_HDMI21_VRR_EN();
            }
            else if((((bit)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _DISABLE) && (GET_TMDS_MAC_RX3_HDMI21_VRR_EN() != _DISABLE))
            {
                DebugMessageRx3("FRL Rx3: VRR_EN from 1 -> 0", 0x00);
                SET_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG();
                CLR_TMDS_MAC_RX3_HDMI21_VRR_EN();
            }

            if((((bit)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _ENABLE) && (GET_TMDS_MAC_RX3_HDMI21_QMS_EN() != _ENABLE))
            {
                DebugMessageRx3("FRL Rx3: QMS_EN from 0 -> 1", 0x00);
                SET_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG();
                SET_TMDS_MAC_RX3_HDMI21_QMS_EN();
            }
            else if((((bit)ScalerHdmiFrlMacRx3GetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _DISABLE) && (GET_TMDS_MAC_RX3_HDMI21_QMS_EN() != _DISABLE))
            {
                DebugMessageRx3("FRL Rx3: QMS_EN from 1 -> 0", 0x00);
                SET_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG();
                CLR_TMDS_MAC_RX3_HDMI21_QMS_EN();
            }
#endif
        }
        else
        {
            // Received VTEM -> No Received / MLDS
            if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                SET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG();

#if(_HDMI21_VRR_SUPPORT == _ON)
                if(GET_TMDS_MAC_RX3_HDMI21_VRR_EN() == _TRUE)
                {
                    DebugMessageRx3("FRL Rx3: VTEM -> No Received/MLDS(VRR_EN from 1->0)", 0x00);
                    SET_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG();
                    CLR_TMDS_MAC_RX3_HDMI21_VRR_EN();
                }

                if(GET_TMDS_MAC_RX3_HDMI21_QMS_EN() == _TRUE)
                {
                    DebugMessageRx3("FRL Rx3: VTEM -> No Received/MLDS(QMS_EN from 1->0)", 0x00);
                    SET_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG();
                    CLR_TMDS_MAC_RX3_HDMI21_QMS_EN();
                }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
                SET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR(1);
#endif
                ScalerHdmiFrlMacRx3WatchDog(_HDMI_EMP_TIMEOUT_WD, _DISABLE);
            }

            CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED();
        }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        // CVTEM have been received and Not Length = 0
        if((ScalerGetBit(P67_52_EMP_DSC, _BIT4) == _BIT4) && ((ScalerGetByte(P67_75_DSC_EMP_6) != 0x00) || (ScalerGetByte(P67_76_DSC_EMP_7) != 0x00)))
        {
            // No Received -> Received CVTEM
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _FALSE)
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX3), _ENABLE);
            }
            else
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX3), _DISABLE);

                // Received CVTEM Continually then enable WD
                ScalerHdmiFrlMacRx3WatchDog(_HDMI_EMP_TIMEOUT_WD, _ENABLE);
            }

            SET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED();

            // Clear CVTEM flag
            ScalerSetBit(P67_52_EMP_DSC, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Received CVTEM -> No Received
            if(GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX3), _ENABLE);

                ScalerHdmiFrlMacRx3WatchDog(_HDMI_EMP_TIMEOUT_WD, _DISABLE);
            }
            else
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX3), _DISABLE);
            }

            CLR_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED();
        }
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
        if(g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmReceive == _TRUE)
        {
            SET_TMDS_MAC_RX3_SBTM_RECEIVE();
            g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmReceive = _FALSE;
        }
        else
        {
            CLR_TMDS_MAC_RX3_SBTM_RECEIVE();
        }
#endif

        SET_TMDS_MAC_RX3_EMP_DETECTING();

        // Activate EMP Detection Event 12 frames = 45ms * 12
        ScalerTimerActiveTimerEvent(540, _SCALER_TIMER_EVENT_RX3_HDMI_FRL_EMP_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI2.1 EMP Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3EmpDetectEvent(void)
{
    CLR_TMDS_MAC_RX3_EMP_DETECTING();
}

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set VRR Max Vf info from Spec Table
// Input Value  : usSourceBrr (unit: 0.1Hz)
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SetVrrVfmaxFromTable(WORD usSourceBrr)
{
    // Check VRRmax > 100?
    // if yes, VFmax = VRRmax
    if(g_stTmdsMacRx3Hdmi21EdidVrrCap.usEdidVrrMax >= 100)
    {
        SET_DRR_VFREQ_MAX(g_stTmdsMacRx3Hdmi21EdidVrrCap.usEdidVrrMax * 10);

        return;
    }

    // Check QMS or Gaming
    if(g_stTmdsMacRx3Hdmi21EdidVrrCap.b1EdidQms == 1)
    {
        // QMS case
        if(g_stTmdsMacRx3Hdmi21EdidVrrCap.b1EdidQmsTfrMax == 1)
        {
            SET_DRR_VFREQ_MAX(usSourceBrr);
        }
        else
        {
            if(g_stTmdsMacRx3Hdmi21EdidVrrCap.ucEdidVrrMin > 0)
            {
                SET_DRR_VFREQ_MAX(MAXOF(usSourceBrr, 600));
            }
            else
            {
                SET_DRR_VFREQ_MAX(600);
            }
        }
    }
    else
    {
        // Gaming case
        if(g_stTmdsMacRx3Hdmi21EdidVrrCap.ucEdidVrrMin > 0)
        {
            SET_DRR_VFREQ_MAX(usSourceBrr);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Get HDMI21 VTEM Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
WORD ScalerHdmiFrlMacRx3GetVtemInfo(EnumHdmi21VtemInfoContent enumContent)
{
    if(GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _HDMI21_VTEM_INFO_VRR_EN:

                return (((ScalerGetByte(P67_67_HDMI_EMP_8) & _BIT0) == _BIT0) ? _ON : _OFF);

            case _HDMI21_VTEM_INFO_M_CONST:

                return (((ScalerGetByte(P67_67_HDMI_EMP_8) & _BIT1) == _BIT1) ? _ON : _OFF);

            case _HDMI21_VTEM_INFO_FVA_FACTOR_M1:

                return ((ScalerGetByte(P67_67_HDMI_EMP_8) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

            case _HDMI21_VTEM_INFO_BASE_VFRONT:

                return (ScalerGetByte(P67_68_HDMI_EMP_9));


            case _HDMI21_VTEM_INFO_BASE_REFRESH_RATE:

                return (((WORD)(ScalerGetByte(P67_69_HDMI_EMP_A) & (_BIT1 | _BIT0)) << 8) | (WORD)(ScalerGetByte(P67_6A_HDMI_EMP_B)));

            case _HDMI21_VTEM_INFO_QMS_EN:

                return (((ScalerGetByte(P67_67_HDMI_EMP_8) & _BIT2) == _BIT2) ? _ON : _OFF);

            case _HDMI21_VTEM_NEXT_TFR:

                return ((ScalerGetByte(P67_69_HDMI_EMP_A) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

            default:

                break;
        }
    }

    return 0x00;
}
#endif
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SignalDetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX3_SIGNAL_DETECTING();
}
#endif

#if((_HDMI_FRL_MAC_RX3_LFSR_TEST_MODE == _ON) || (_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1))
//--------------------------------------------------
// Description  : LTP Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx3LtpCheck(void)
{
    // set cycle
    ScalerSetBit(P67_30_HDMI21_LT_0, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // set L0 LTP5, L1 LTP6
    ScalerSetByte(P67_31_HDMI21_LT_1, 0x56);

    // set L2 LTP7, L3 LTP8
    ScalerSetByte(P67_32_HDMI21_LT_2, 0x78);

    // enable LTP check
    ScalerSetBit(P67_30_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    ScalerTimerDelayXms(100);

    if((ScalerGetBit(P67_30_HDMI21_LT_0, _BIT7) == 0x00) && (ScalerGetBit(P67_33_HDMI21_LT_3, _BIT7) == _BIT7))
    {
        DebugMessageRx3("FRL Rx3: L0 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P67_30_HDMI21_LT_0, _BIT7) != 0x00)
        {
            DebugMessageRx3("FRL Rx3: L0 LTP not finish", 0);
        }
        else if(ScalerGetBit(P67_33_HDMI21_LT_3, _BIT7) != _BIT7)
        {
            DebugMessageRx3("FRL Rx3: L0 LTP fail, error count=", ScalerGetByte(P67_34_HDMI21_LT_4));
        }
    }

    if((ScalerGetBit(P67_30_HDMI21_LT_0, _BIT6) == 0x00) && (ScalerGetBit(P67_33_HDMI21_LT_3, _BIT6) == _BIT6))
    {
        DebugMessageRx3("FRL Rx3: L1 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P67_30_HDMI21_LT_0, _BIT6) != 0x00)
        {
            DebugMessageRx3("FRL Rx3: L1 LTP not finish", 0);
        }
        else if(ScalerGetBit(P67_33_HDMI21_LT_3, _BIT6) != _BIT6)
        {
            DebugMessageRx3("FRL Rx3: L1 LTP fail, error count=", ScalerGetByte(P67_35_HDMI21_LT_5));
        }
    }

    if((ScalerGetBit(P67_30_HDMI21_LT_0, _BIT5) == 0x00) && (ScalerGetBit(P67_33_HDMI21_LT_3, _BIT5) == _BIT5))

    {
        DebugMessageRx3("FRL Rx3: L2 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P67_30_HDMI21_LT_0, _BIT5) != 0x00)
        {
            DebugMessageRx3("FRL Rx3: L2 LTP not finish", 0);
        }
        else if(ScalerGetBit(P67_33_HDMI21_LT_3, _BIT5) != _BIT5)
        {
            DebugMessageRx3("FRL Rx3: L2 LTP fail, error count=", ScalerGetByte(P67_36_HDMI21_LT_6));
        }
    }

    if((ScalerGetBit(P67_30_HDMI21_LT_0, _BIT4) == 0x00) && (ScalerGetBit(P67_33_HDMI21_LT_3, _BIT4) == _BIT4))
    {
        DebugMessageRx3("FRL Rx3: L3 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P67_30_HDMI21_LT_0, _BIT4) != 0x00)
        {
            DebugMessageRx3("FRL Rx3: L3 LTP not finish", 0);
        }
        else if(ScalerGetBit(P67_33_HDMI21_LT_3, _BIT4) != _BIT4)
        {
            DebugMessageRx3("FRL Rx3: L3 LTP fail, error count=", ScalerGetByte(P67_37_HDMI21_LT_7));
        }
    }
}

#endif

#if(_HDMI_FRL_MAC_RX3_LFSR_TEST_MODE == _ON)
//--------------------------------------------------
// Description  : Gap on FRL format Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx3GapCheck(void)
{
    BYTE ucTemp = 0;
    BYTE ucError = 0;

    // set 4 lane mode and FRL
    // ScalerSetBit(P67_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), (_BIT6));

    // Enable decode, de-scramble and RS-check
    // ScalerSetBit(P68_05_HDMI21_DESCR_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    // ScalerSetBit(P68_05_HDMI21_DESCR_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    // ScalerSetBit(P68_10_HDMI21_RS_0, ~_BIT7, _BIT7);

    // Reset HDMI21 Small FIFO
    // ScalerTmdsPhyRxFifoReset(ScalerTmdsMacRxRxDxMapping(_RX3), 4);

    ScalerTimerDelayXms(10);

    // enable Gap pattern check
    ScalerSetBit(P67_39_HDMI21_LT_9, ~(_BIT7 | _BIT6), _BIT7);

    // Wait Gap check
    /*if(ScalerTimerPollingFlagProc(2, P67_39_HDMI21_LT_9, _BIT6, _FALSE) == _TRUE)
    {
        DebugMessageRx3("FRL Rx3: Gap Pass", 0);
    }
    else
    {
        DebugMessageRx3("FRL Rx3: Gap fail", 0);
    }*/

    DELAY_10US();

    // disable Gap pattern check
    ScalerSetBit(P67_39_HDMI21_LT_9, ~(_BIT7 | _BIT6), 0x00);

    /*if(ScalerGetBit(P67_39_HDMI21_LT_9, _BIT6) == 0x00)
    {
        DebugMessageRx3("FRL Rx3: Gap Pass", 0);
    }
    else*/
    {
        // Enable RS SRAM Save
        ScalerSetBit(P68_27_HDMI21_RS_SRAM_0, ~_BIT7, _BIT7);

        ScalerTimerDelayXms(10);

        if(ScalerGetBit(P68_27_HDMI21_RS_SRAM_0, _BIT0) == 0x00)
        {
            DebugMessageRx3("FRL Rx3: SRAM not finish", 0);
        }

        // RS FIFO0
        ScalerSetBit(P68_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), 0x00);

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P68_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P68_29_HDMI21_RS_SRAM_2) != 0x01)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P68_2A_HDMI21_RS_SRAM_3) != 0x01)
            {
                ucError = 1;
            }
        }

        // RS FIFO1
        ScalerSetBit(P68_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), _BIT5);

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P68_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P68_29_HDMI21_RS_SRAM_2) != 0x04)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P68_2A_HDMI21_RS_SRAM_3) != 0x04)
            {
                ucError = 1;
            }
        }

        // RS FIFO2
        ScalerSetBit(P68_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), _BIT6);

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P68_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P68_29_HDMI21_RS_SRAM_2) != 0x01)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P68_2A_HDMI21_RS_SRAM_3) != 0x01)
            {
                ucError = 1;
            }
        }

        // RS FIFO3
        ScalerSetBit(P68_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P68_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P68_29_HDMI21_RS_SRAM_2) != 0x04)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P68_2A_HDMI21_RS_SRAM_3) != 0x04)
            {
                ucError = 1;
            }
        }

        // Disable RS SRAM Save
        ScalerSetBit(P68_27_HDMI21_RS_SRAM_0, ~_BIT7, 0x00);

        if(ucError == 1)
        {
            DebugMessageRx3("FRL Rx3: GAP fail", 0);
        }
        else
        {
            DebugMessageRx3("FRL Rx3: GAP pass", 0);
        }
    }
}

//--------------------------------------------------
// Description  : LFSR on FRL format Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx3LfsrCheck(void)
{
    WORD usErrorCount = 0;

    // Set MAC RX3 is FRL
    // ScalerSetBit(P67_00_HDMI_TOP_0, ~_BIT6, _BIT6);

    ScalerTimerDelayXms(10);

    // set 4 lane mode and FRL
    ScalerSetBit(P67_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // LFSR check cycle
    ScalerSetBit(P68_1C_HDMI21_LFSR_2, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // LFSR check enable
    ScalerSetBit(P68_1B_HDMI21_LFSR_1, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(100);

    // LFSR pattern pass
    if(ScalerGetBit(P68_1C_HDMI21_LFSR_2, _BIT7) == _BIT7)
    {
        if(ScalerGetBit(P68_1B_HDMI21_LFSR_1, _BIT6) == 0x00)
        {
            DebugMessageRx3("FRL Rx3: LFSR pass", 0);
        }
        else
        {
            usErrorCount = ((WORD) ScalerGetBit(P68_1C_HDMI21_LFSR_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(P68_1D_HDMI21_LFSR_3);
            DebugMessageRx3("FRL Rx3: LFSR fail", usErrorCount);
        }
    }
    else
    {
        DebugMessageRx3("FRL Rx3: LFSR no finish", 0);
    }

    // LFSR check disable
    ScalerSetBit(P68_1B_HDMI21_LFSR_1, ~_BIT7, 0x00);
}
#endif // End for #if(_HDMI21_LFSR_TEST_MODE == _ON)

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
//--------------------------------------------------
// Description  : Set SCDC Decode Fail staus
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerHdmiFrlMacRx3SetDscDecodeFailStatus(void)
{
    // Set SCDC 0x40[7] for Dsc dec fail
    ScalerSetDataPortBit(P72_39_HDMI_CTRL_39, _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40, ~_BIT7, _BIT7);

    // Set SCDC 0x10[0] Status update
    ScalerHdmiFrlMacRx3SetScdcUpdateFlag(~_BIT0, _BIT0);
}
#endif

//--------------------------------------------------
// Description  : LFSR on FRL format Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx3GetTimingInfo(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX3);
    bit bDscNative420 = ScalerDscDecoderGetNative420Mode(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3));
    WORD usInputPixelClk = 0;

    // Get H Width
    pstDscTimingInfo->usHWidth = GET_HDMI_FRL_MAC_RX3_CVTEM_HCACTIVE_BYTES();

    // Get H Front Porch
    pstDscTimingInfo->usHFrontPorch = GET_HDMI_FRL_MAC_RX3_CVTEM_HFRONT();

    // Get HSW
    pstDscTimingInfo->usHSWidth = GET_HDMI_FRL_MAC_RX3_CVTEM_HSYNC();

    // Get HStart
    pstDscTimingInfo->usHStart = pstDscTimingInfo->usHSWidth + GET_HDMI_FRL_MAC_RX3_CVTEM_HBACK();

    // Get H Total
    pstDscTimingInfo->usHTotal = ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3)) + pstDscTimingInfo->usHFrontPorch + pstDscTimingInfo->usHStart;

    // Get H Total After DSC
    pstDscTimingInfo->usHTotalAfterDSC = g_usHdmiFrlMacRx3Htotal;

    // Get V Height
    pstDscTimingInfo->usVHeight = GET_HDMI_FRL_MAC_RX3_VACTIVE();

    // Get V Front Porch
    pstDscTimingInfo->usVFrontPorch = GET_HDMI_FRL_MAC_RX3_VFRONT();

    // Get V Total
    pstDscTimingInfo->usVTotal = GET_HDMI_FRL_MAC_RX3_VTOTAL();

    // Get Compressed Clk
    pstDscTimingInfo->ulCompStreamClockHz = g_ulHdmiFrlMacRx3DSCClkValue * 100;

    // Get Input Pixel Clk
    usInputPixelClk = (ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal * pstDscTimingInfo->usVTotal, (DWORD)pstDscTimingInfo->ulCompStreamClockHz * 4UL, (DWORD)pstDscTimingInfo->usHTotalAfterDSC * pstDscTimingInfo->usVTotal * (1 + bDscNative420)) / 100000);

    // Modify HSW
    pstDscTimingInfo->usHSWidth = ((GET_HDMI_FRL_MAC_RX3_CVTEM_HSYNC() > ScalerSyncGetHSWbyClk(usInputPixelClk)) ? GET_HDMI_FRL_MAC_RX3_CVTEM_HSYNC() : ScalerSyncGetHSWbyClk(usInputPixelClk));

    // Modify HStart
    pstDscTimingInfo->usHStart = ScalerSyncGetHStartbyHSW(pstDscTimingInfo->usHSWidth, usInputPixelClk);
    pstDscTimingInfo->usHStart = (((pstDscTimingInfo->usHSWidth + GET_HDMI_FRL_MAC_RX3_CVTEM_HBACK()) > pstDscTimingInfo->usHStart) ? (pstDscTimingInfo->usHSWidth + GET_HDMI_FRL_MAC_RX3_CVTEM_HBACK()) : pstDscTimingInfo->usHStart);

    // Modify H Total
    pstDscTimingInfo->usHTotal = ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX3)) + pstDscTimingInfo->usHFrontPorch + pstDscTimingInfo->usHStart;

    // Get Interlace Mode
    pstDscTimingInfo->b1InterlaceOddMode = _FALSE;

    if(ScalerDrrIVSProduceByBE(_SOURCE_HDMI, enumInputPort) == _TRUE)
    {
        // Get HS Polarity
        pstDscTimingInfo->b1HSP = _SYNC_POLARITY_POSITIVE;

        // Get VStart
        pstDscTimingInfo->usVStart = _DE_ONLY_MODE_VSTART;

        // Get VSW
        pstDscTimingInfo->usVSWidth = _DE_ONLY_MODE_VSW;

        // Get VS Polarity
        pstDscTimingInfo->b1VSP = _SYNC_POLARITY_POSITIVE;
    }
    else
    {
        // Get HS Polarity
        pstDscTimingInfo->b1HSP = 0;

        // Get VStart
        pstDscTimingInfo->usVStart = GET_HDMI_FRL_MAC_RX3_VBACK() + GET_HDMI_FRL_MAC_RX3_VSYNC();

        // Get VSW
        pstDscTimingInfo->usVSWidth = GET_HDMI_FRL_MAC_RX3_VSYNC();

        // Get VS Polarity
        pstDscTimingInfo->b1VSP = 0;
    }
}
#endif

//--------------------------------------------------
// Description  : Backup and Disable Main link Related IRQ Before Z0 off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3IrqBackupBeforeZ0Off(void)
{
    // Backup CED Lock Transition IRQ
    g_stHdmiFrlMacRx3IrqStatus.b4CedLockIrqBackup = ScalerGetBit(P77_17_HDMI21_FRL_CED_15, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Backup FRL Transition detection IRQ
    g_stHdmiFrlMacRx3IrqStatus.b1TransitionDetectIrqBackup = (ScalerGetBit(P77_E6_HDMI_TRANSDET_CTRL2, _BIT7) >> 7);

    // Backup RSV0~3 received IRQ
    g_stHdmiFrlMacRx3IrqStatus.b4RsvIrqBackup = ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Backup Vs EMP IRQ
    g_stHdmiFrlMacRx3IrqStatus.b1VsEmpIrqBackup = (ScalerGetBit(P67_51_EMP_VS, _BIT7) >> 7);

    // Backup Dhdr EMP IRQ
    g_stHdmiFrlMacRx3IrqStatus.b1DhdrEmpIrqBackup = (ScalerGetBit(P67_53_EMP_DHDR, _BIT7) >> 7);

    // Disable CED Lock Transition IRQ
    ScalerSetByte(P77_17_HDMI21_FRL_CED_15, 0x00);

    // Disable FRL Transition detection IRQ
    ScalerSetBit(P77_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3), 0x00);

    // Disable RSV0~3 received IRQ
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable Vs EMP IRQ
    ScalerSetBit(P67_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Dhdr EMP IRQ
    ScalerSetBit(P67_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : Restore Main link Related IRQ After Z0 on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On(void)
{
    // Clear flag and Restore CED Lock Transition IRQ
    // ScalerSetBit(P77_17_HDMI21_FRL_CED_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    // ScalerSetByte(P77_17_HDMI21_FRL_CED_15, g_stHdmiFrlMacRx3IrqStatus.b4CedLockIrqBackup);

    // Clear flag and Restore FRL Transition detection IRQ
    ScalerSetBit(P77_E6_HDMI_TRANSDET_CTRL2, ~_BIT3, _BIT3);
    ScalerSetBit(P77_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3), (g_stHdmiFrlMacRx3IrqStatus.b1TransitionDetectIrqBackup << 7));

    // Clear flag and Restore RSV0~3 received IRQ
    ScalerSetByte(P77_CC_HDMI_GPVS, (_BIT6 | _BIT5));
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_00_PORT_PAGE77_HDMI_SCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_B5_PORT_PAGE77_HDMI_BED_FUNC_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_stHdmiFrlMacRx3IrqStatus.b4RsvIrqBackup);

    // Clear flag and Restore Vs EMP IRQ
    ScalerSetBit(P67_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(P67_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (g_stHdmiFrlMacRx3IrqStatus.b1VsEmpIrqBackup << 7));

    // Clear flag and Restore Dhdr EMP IRQ
    ScalerSetBit(P67_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(P67_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (g_stHdmiFrlMacRx3IrqStatus.b1DhdrEmpIrqBackup << 7));
}
#endif // End for #if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
