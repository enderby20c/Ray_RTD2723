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
// ID Code      : ScalerHdmiFrlMacRx4.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIFRLMACRX4__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx4/ScalerHdmiFrlMacRx4.h"


#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructHdmiFrlCtrlInfo g_stHdmiFrlMacRx4CtrlInfo;

WORD g_usHdmiFrlMacRx4Hfront;
WORD g_usHdmiFrlMacRx4Hsync;
WORD g_usHdmiFrlMacRx4Hback;
WORD g_usHdmiFrlMacRx4Hactive;
WORD g_usHdmiFrlMacRx4Htotal;
WORD g_usHdmiFrlMacRx4Vfront;
WORD g_usHdmiFrlMacRx4Vsync;
WORD g_usHdmiFrlMacRx4Vback;
WORD g_usHdmiFrlMacRx4Vactive;
WORD g_usHdmiFrlMacRx4Vtotal;
WORD g_usHdmiFrlMacRx4FrameRate;

DWORD g_ulHdmiFrlMacRx4PixelClkValue; // Unit:kHz

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
DWORD g_ulHdmiFrlMacRx4DSCClkValue; // Unit:0.1MHz
#endif

BYTE g_ucHdmiFrlMacRx4AviInfo;

WORD g_usHdmiFrlMacRx4NativeHtotal;

StructHdmiFrlIrqStatus g_stHdmiFrlMacRx4IrqStatus;

WORD g_usHdmiFrlMacRx4OffMeasureCount;

BYTE g_ucHdmiFrlMacRx4ScdcStatusFlag;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial for FRL Port
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ScanInitial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    ScalerHdmiFrlMacRx4Initial(enumInputPort);

    ScalerHdmiFrlMacRx4InterruptInitial();

    DebugMessageRx4("FRL Rx4: initial", 0);
}

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Config EMP SRAM
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4EmpSramSetting(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // [7] VS Enable; [6] DHDR Enable; [4] Share mode
        BYTE ucEmpConfig = 0x00;

        // set share mode
        ucEmpConfig = _BIT4;

#if((_DM_FUNCTION == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        // Enable VS IRQ & w1c all flag
        ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if(_HDMI_SBTM_SUPPORT == _ON)
        // Detect VS EMP w/ org_id and tag
        ScalerSetBit(P1E_B9_VS_EMP_1A, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // org id & tag
        ScalerSetByte(P1E_BC_VS_ORG_ID, _HDMI21);

        ScalerSetByte(P1E_BA_VS_EMP_1B, 0x00);
        ScalerSetByte(P1E_BB_VS_EMP_1C, 0x03);
#elif(_DM_FUNCTION == _ON)
        // Detect VS EMP w/ org_id only
        ScalerSetBit(P1E_B9_VS_EMP_1A, ~(_BIT7 | _BIT6), _BIT6);

        // org id
        ScalerSetByte(P1E_BC_VS_ORG_ID, _VENDOR_SPECIFIC);
#endif
        // Enable VS EMP stored
        ucEmpConfig |= _BIT7;
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
        // Enable D-HDR IRQ & w1c all flag
        ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Enable D-HDR EMP stored
        ucEmpConfig |= _BIT6;
#endif
        // Set EMP Config
        ScalerSetBit(P1E_C8_HDMI_EMP_SRAM_CTRL0, ~(_BIT7 | _BIT6 | _BIT4), ucEmpConfig);
    }
    else
    {
        // Disable EMP stored
        ScalerSetBit(P1E_C8_HDMI_EMP_SRAM_CTRL0, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P1E_B9_VS_EMP_1A, ~(_BIT7 | _BIT6), 0x00);

        // [7] Disable VS/ D-HDR IRQ
        ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Enable/Disable RSV IRQ_en
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4RoundRobinIrqEnable(bit bEnable)
{
    bEnable = bEnable;

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
    BYTE ucRsv = 0;

    for(ucRsv = 0; ucRsv < 4; ucRsv++)
    {
        ScalerHdmiFrlMacRx4RsvIrqEnable(ucRsv, bEnable);
    }
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable RSV IRQ_en
// Input Value  : RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4RsvIrqEnable(EnumHdmiRsvNumber enumRsvNumber, bit bEnable)
{
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            if(bEnable == _ENABLE)
            {
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT5);
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT5);
            }
            break;

        case _HDMI_RSV_1:
            if(bEnable == _ENABLE)
            {
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT6);
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT1, _BIT1);
            }
            else
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT1, 0x00);
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT6);
            }
            break;

        case _HDMI_RSV_2:
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT2, _BIT2);
            }
            else
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT2, 0x00);
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
            }
            break;

        case _HDMI_RSV_3:
            if(bEnable == _ENABLE)
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~_BIT3, 0x00);
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
            }
            break;

        case _HDMI_RSV_4:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            }
            else
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            }
            break;

        case _HDMI_RSV_5:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }
            else
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            break;

        case _HDMI_RSV_6:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }
            else
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }
            break;

        case _HDMI_RSV_7:
            if(bEnable == _ENABLE)
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
            }
            else
            {
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
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
void ScalerHdmiFrlMacRx4RsvInitial(void)
{
    // Specify Packet Detect Type
    ScalerSetByte(P78_D4_PORT_PAGE78_HDMI_PTRSV6, _HDMI_AVI_INFO_TYPE);

    ScalerSetByte(P78_D3_PORT_PAGE78_HDMI_PTRSV5, _HDMI_GENERAL_CONTROL_TYPE);

#if(_HDMI_HDR10_SUPPORT == _ON)
    ScalerSetByte(P78_D2_PORT_PAGE78_HDMI_PTRSV4, _HDR_INFO_TYPE);
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    ScalerSetByte(P78_CF_HDMI_PTRSV7, _SPD_INFO_TYPE);
    ScalerSetBit(P78_D7_HDMI_SHDR_IE_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

    // Freesync Replay disable
    ScalerSetBit(P78_D6_HDMI_SHDR_IE, ~_BIT4, 0x00);

    // PR6 = 2b'10 is Replay, Other is Live Capture
    ScalerSetBit(P78_D6_HDMI_SHDR_IE, ~(_BIT3 | _BIT2), _BIT3);
#endif

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) && (_HDMI_VSIF_RCV_BY_RR == _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_43_PORT_PAGE78_HDMI_PTRSV0, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_44_PORT_PAGE78_HDMI_PTRSV1, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_A4_PORT_PAGE78_HDMI_PTRSV_2, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_A5_PORT_PAGE78_HDMI_PTRSV_3, _SPD_INFO_TYPE);

    // write Round Robin tag
    ScalerSetByte(P78_DD_PKT_ROUND_ROBIN_PT0, _HDMI_VSIF_TYPE);
    ScalerSetByte(P78_DE_PKT_ROUND_ROBIN_PT1, _HDMI_VSIF_TYPE);
    ScalerSetByte(P78_DF_PKT_ROUND_ROBIN_PT2, _SPD_INFO_TYPE);
#elif((_HDMI_SPD_IF_RCV_BY_RR == _ON) && (_HDMI_VSIF_RCV_BY_RR != _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_43_PORT_PAGE78_HDMI_PTRSV0, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_44_PORT_PAGE78_HDMI_PTRSV1, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_A4_PORT_PAGE78_HDMI_PTRSV_2, _SPD_INFO_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_A5_PORT_PAGE78_HDMI_PTRSV_3, _SPD_INFO_TYPE);

    // write Round Robin tag
    ScalerSetByte(P78_DD_PKT_ROUND_ROBIN_PT0, _SPD_INFO_TYPE);
    ScalerSetByte(P78_DE_PKT_ROUND_ROBIN_PT1, _SPD_INFO_TYPE);
    ScalerSetByte(P78_DF_PKT_ROUND_ROBIN_PT2, _SPD_INFO_TYPE);
#elif((_HDMI_SPD_IF_RCV_BY_RR != _ON) && (_HDMI_VSIF_RCV_BY_RR == _ON))
    // write RSV0-2 tag
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_43_PORT_PAGE78_HDMI_PTRSV0, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_44_PORT_PAGE78_HDMI_PTRSV1, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_A4_PORT_PAGE78_HDMI_PTRSV_2, _HDMI_VSIF_TYPE);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_A5_PORT_PAGE78_HDMI_PTRSV_3, _HDMI_VSIF_TYPE);

    // write Round Robin tag
    ScalerSetByte(P78_DD_PKT_ROUND_ROBIN_PT0, _HDMI_VSIF_TYPE);
    ScalerSetByte(P78_DE_PKT_ROUND_ROBIN_PT1, _HDMI_VSIF_TYPE);
    ScalerSetByte(P78_DF_PKT_ROUND_ROBIN_PT2, _HDMI_VSIF_TYPE);
#endif

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
    // ENABLE Round Robin
    ScalerSetBit(P78_B2_TMDS_DBB2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : Initialize FRL MAC setting for search
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4Initial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // Set Lane swap and PN swap
    ScalerHdmiFrlMacRx4PnSwapConfig(enumInputPort);

#if(_HDMI_FRL_MAC_RX4_LINK_TRAINING_BYPASS == _ON)
    // Set MAC RX4 is FRL
    ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, _BIT6);

    // Set FRL Rate
    ScalerHdmiFrlMacRxSetDxFrlRate(enumInputPort, ScalerHdmiFrlMacRxGetDxMaxFrlRate(enumInputPort));

    if(ScalerHdmiFrlMacRxGetDxFrlRate(enumInputPort) >= _HDMI_FRL_RATE_6G_4LANES)
    {
        // set 4 lane mode and FRL
        ScalerSetBit(P1E_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P69_10_HDMI21_RS_0, ~_BIT2, _BIT2);
    }
    else
    {
        // set 3 lane mode and FRL
        ScalerSetBit(P1E_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P69_10_HDMI21_RS_0, ~_BIT2, 0x00);
    }
#endif

    ScalerHdmiFrlMacRx4RoundRobinIrqEnable(_DISABLE);

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
    // Inactive EMP SRAM
    ScalerHdmiFrlMacRx4EmpSramSetting(_DISABLE);
#endif

    // If FLT_Ready = 0, Set Link Training Initial State = LTS2
    if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, _BIT6) == 0x00)
    {
        SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);
    }

    // Disable DPF output
    SET_HDMI_FRL_RX4_DPF_RGB_CLK_OUTPUT_DISABLE();

    // Disable DPF format gen
    ScalerSetBit(P69_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // Disable DPF CLK
    ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Enable DPF VS/HS Synchronize(C version ECO)
    ScalerSetBit(P69_70_DPF_CTRL_0, ~(_BIT6 | _BIT3), _BIT3);

    // Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P69_26_HDMI21_DI_0, ~(_BIT5 | _BIT4), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P78_C8_HDMI_APC, ~_BIT0, 0x00);

    ScalerHdmiFrlMacRx4WatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD | _HDMI_FRL_DPF_FIFO_WD | _HDMI_EMP_TIMEOUT_WD), _DISABLE);

    // Deep Color Mode detection auto
    ScalerSetBit(P78_B8_TMDS_DPC1, ~_BIT2, _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_02_PORT_PAGE78_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2), (_BIT6 | _BIT3));

    // Enable BCH ACC(C version ECO)
    ScalerSetBit(P69_31_HDMI21_FRL_1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1), _BIT1);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_32_PORT_PAGE78_HDMI_WDCR1, ~_BIT5, _BIT5);

    // RSV Assignment
    ScalerHdmiFrlMacRx4RsvInitial();

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_45_PORT_PAGE78_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_46_PORT_PAGE78_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_47_PORT_PAGE78_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_AA_PORT_PAGE78_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_AB_PORT_PAGE78_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Enable HDMI 2.1 SCDC Module
    ScalerSetBit(P73_31_HDMI_CTRL_31, ~_BIT7, _BIT7);

    // Set Unlock when continue 2 super block has no SR/SSB
    ScalerSetBit(P78_16_HDMI21_FRL_CED_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT0);

    // Set CED checksum calculated by HW after ver. E
    ScalerSetBit(P73_28_HDMI_CTRL_28, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

    // Disable DSC EMP IRQ
    ScalerSetBit(P1E_52_EMP_DSC, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set EMP time out 10 MTWs
    ScalerSetBit(P1E_55_EMP_TIMEOUT_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

    // Source hasn't send out video before timeout, Sink enter no signal then switch port,
    // So Sink need check FRL signal in HDMI21Initial.
    if((ScalerHdmiFrlMacRxGetDxFrlRate(enumInputPort) != _HDMI_FRL_RATE_NONE) && (ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00))
    {
        // turn on ACDR
        ScalerTmdsPhyRxFrlSetAcdr(enumInputPort);

        // if SCDC 0x40 changed, set status update bit
        if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, _BIT6) == 0x00)
        {
            // Set FLT_ready
            ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT6, _BIT6);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
            // Clear SCDC 0x40[7] DSC dec fail
            ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
            // Set Status update
            ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
        }

        // Clear Set PHY flag
        CLR_HDMI_FRL_MAC_RX4_PHY_SET();

        // Set Rebuild PHY event
        SET_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT();
    }

    // Enable HDMI HPD IRQ Enable
    // ScalerSetBit(P73_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Initialize FRL Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4InterruptInitial(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Enable link training related IRQ
    ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT2));

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    // Enable "w1c of status update" IRQ
    ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT0);
#endif

    if((GET_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_PHY_SET() == _FALSE))
    {
        // Sel Lane0 to measure transition as default
        ScalerTmdsPhyRxTransitionDataLaneSelect(enumMappingPort, 0);

        // turn on transition detection IRQ
        ScalerSetBit(P78_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

        // Enable transition data from PHY
        ScalerTmdsPhyRxTransitionDataEnable(enumMappingPort, _ENABLE);

        // turn on transition detection
        ScalerSetBit(P78_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, _BIT7);
    }

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
    // Clear IRQ Pending Flag
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_60_PORT_PAGE78_HDMI_INTCR, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
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
void ScalerHdmiFrlMacRx4RDCHdmi21Test(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(ScalerGetByte(P1E_2A_HDMI21_DPHY_D1) == 0x00)
    {
        ScalerTmdsPhyRxFrlSetPhy(enumMappingPort, 4, 6);

        // ScalerSetByte(P7C_50_DIG_00, 0xFF);
        // ScalerSetBit(P7C_52_DIG_02, ~_BIT4, _BIT4);

        ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, _BIT6);
        ScalerSetBit(P78_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);
        ScalerSetBit(P1E_28_HDMI21_DPHY_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        ScalerSetByte(P1E_2A_HDMI21_DPHY_D1, 0x10);

        DebugMessageRx4("FRL Rx4: PHY initial", 0);

        while(1)
        {
            ScalerHdmiFrlMacRx4LtpCheck();

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
bit ScalerHdmiFrlMacRx4NormalPreDetect(void)
{
#if(_HDMI_FRL_MAC_RX4_LINK_TRAINING_BYPASS == _ON)
    BYTE ucTemp = 0;
    BYTE ucSetPhyLoop = 0;
    BYTE ucFreqCorrect = 0;
#endif

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if(_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1)
    ScalerHdmiFrlMacRx4RDCHdmi21Test();
#endif

#if(_HDMI_FRL_MAC_RX4_LINK_TRAINING_BYPASS == _OFF)

    switch(GET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE())
    {
        case _HDMI_FRL_LT_LTSL:
        case _HDMI_FRL_LT_LTS2:

            // if FLT_ready = 0
            if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, _BIT6) == 0x00)
            {
                // Set FLT_ready
                ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT6, _BIT6);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
                // Clear SCDC 0x40[7] DSC dec fail
                ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
                // Set Status update
                ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
            }

            SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS3);
            break;

        case _HDMI_FRL_LT_LTS3:

            break;

        case _HDMI_FRL_LT_LTS3_LFSR:

            break;

        case _HDMI_FRL_LT_LTSP_GAP:

            if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)))
            {
                // Switch to HDMI 2.1 SCDC Module
                ScalerSetBit(P73_31_HDMI_CTRL_31, ~_BIT7, _BIT7);

                // Start CED count
                ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Set CED Valid
                ScalerSetBit(P78_08_HDMI21_FRL_CED_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

                if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
                {
                    // Set Lane3 CED Valid
                    ScalerSetBit(P78_08_HDMI21_FRL_CED_0, ~_BIT0, _BIT0);
                }

                // Enable RS count and set valid and enable RS_update flag
                ScalerSetBit(P69_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));
                ScalerSetBit(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));

                // Clear FW RS err flag
                ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

                // Enable FW RS count
                ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT1));

                CLR_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT();

                // Set HDMI2.1 Reactive time
                SET_HDMI_FRL_MAC_RX4_REACTIVE_SEARCH_TIME();

                SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSP_FRL_START);
            }
            else
            {
                DebugMessageRx4("FRL Rx4: Lane Lock error", ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort));
            }
            break;

        case _HDMI_FRL_LT_LTSP_FRL_START:

            // check CED error and channel lock.
            if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
               ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) &&
               (ScalerHdmiFrlMacRx4CedCheck() == _TRUE))
            {
            }

            // check RSED error
            if(ScalerHdmiFrlMacRx4RsedCheck() == _TRUE)
            {
            }

            if((GET_HDMI_FRL_MAC_RX4_FRL_START_EVENT() == _TRUE) || (GET_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT() == _TRUE))
            {
                CLR_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT();

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
                // Clear Signal Detection flag
                CLR_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING();
#endif

                SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTSEND);

                g_usHdmiFrlMacRx4OffMeasureCount = ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE0);

                DebugMessageRx4("FRL Rx4: F_R =", ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort));

                return _TRUE;
            }

            break;

        case _HDMI_FRL_LT_LTSEND:

            // check CED error
            if(ScalerHdmiFrlMacRx4CedCheck() == _TRUE)
            {
                DebugMessageRx4("FRL Rx4: CED pass", 0);
            }

            // check RSED error
            if(ScalerHdmiFrlMacRx4RsedCheck() == _TRUE)
            {
                DebugMessageRx4("FRL Rx4: RSED pass", 0);
            }

            return _TRUE;

            break;

        default:
            break;
    }

#else // else of #if(_HDMI_FRL_MAC_RX4_LINK_TRAINING_BYPASS == _OFF)

    if(ScalerGetByte(P1E_2A_HDMI21_DPHY_D1) == 0x00)
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
            ScalerSetBit(P78_E9_HDMI_TRANSDET_CTRL5, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P78_E2_HDMI_TRANSDET_CTRL0, ~_BIT7, _BIT7);

            ucFreqCorrect = 0;

            for(ucTemp = 0; ucTemp < 4; ucTemp++)
            {
                ScalerTmdsPhyRxTransitionDataLaneSelect(enumMappingPort, ucTemp);

                // Pop result
                ScalerSetBit(P78_E8_HDMI_TRANSDET_CTRL4, ~_BIT7, _BIT7);

                DELAY_XUS(100);

                if(ScalerGetByte(P78_FE_HDMI_TRANSDET_RESULT_M) == 0x30)
                {
                    ucFreqCorrect++;
                }
            }

            if(ucFreqCorrect == 4)
            {
                DebugMessageRx4("FRL Rx4: Set PHY ucSetPhyLoop", ucSetPhyLoop);
                break;
            }

            ucSetPhyLoop ++;
        }

        SET_INTERRUPT_ENABLE_STATUS(_INT_TMDS, _ENABLE);

        // Enable HDCP2.2 & Disable HDCP 1.4 Module
        ScalerSetBit(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, _BIT7);
        ScalerSetBit(P73_C0_HDCP_CR, ~_BIT0, 0x00);

        // Reset PHY -> MAC Interface
        ScalerSetBit(P78_A7_TMDS_PWDCTL, ~_BIT4, 0x00);
        ScalerSetBit(P78_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

        ScalerSetByte(P1E_2A_HDMI21_DPHY_D1, 0x80);

        DebugMessageRx4("FRL Rx4: PHY initial", 0);

        // Enable disparity
        if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            // Start disparity calculation 4 lanes
            ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Start disparity calculation 3 lanes
            ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
        }

        // Disable CED and RS error count
        ScalerSetBit(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit(P69_10_HDMI21_RS_0, ~_BIT5, 0x00);
        ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

        ScalerTimerDelayXms(2);

        // Enable CED and RSED
        if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES)
        {
            // Start CED 4 lanes
            ScalerSetBit(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Enable lock transition IRQ, need 3 super blocks ~37us@3G
            ScalerSetByte(P78_17_HDMI21_FRL_CED_15, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // DebugMessageRx4("CED enable", ScalerGetByte(P78_08_HDMI21_FRL_CED_0));
        }
        else
        {
            // Start CED 3 lanes
            ScalerSetBit(P78_08_HDMI21_FRL_CED_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

            // Enable lock transition IRQ, need 3 super blocks ~37us@3G
            ScalerSetByte(P78_17_HDMI21_FRL_CED_15, (_BIT2 | _BIT1 | _BIT0));
        }

        // Start CED count
        ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable RS count and set valid
        ScalerSetBit(P69_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));
        ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT1));

        // check CED error and channel lock.
        if((GET_HDMI_FRL_MAC_RX4_LANE0_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE1_LOCK() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_LANE2_LOCK() == _TRUE) &&
           ((GET_HDMI_FRL_MAC_RX4_LANE3_LOCK() == _TRUE) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) < _HDMI_FRL_RATE_6G_4LANES)) &&
           (ScalerHdmiFrlMacRx4CedCheck() == _TRUE))
        {
            DebugMessageRx4("FRL Rx4: LTSEND", ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_31_PORT_PAGE73_HDMI_SCDC_31, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            return _TRUE;
        }
    }
#endif

    if(GET_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT() == _TRUE)
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
void ScalerHdmiFrlMacRx4FirstActiveProc(EnumSourceType enumSourceType)
{
    enumSourceType = enumSourceType;
}

//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4HdmiAVMuteProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    enumMappingPort = enumMappingPort;

    // if AVMute Has been triggered
    if(ScalerGetBit(P78_CB_HDMI_SR, (_BIT7 | _BIT6)) == _BIT7)
    {
        // Clear AVMute Flag
        ScalerSetBit(P78_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT7);

        // Disable HDMI AVMute WD
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, ~_BIT7, 0x00);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
        {
            // Disable DSC force background
            ScalerDscDecoderForceBackgroundSetting(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4), _DISABLE);
        }
#endif

        // Enable Audio Output
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_30_PORT_PAGE78_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Enable HDMI AVMute WD
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, ~_BIT7, _BIT7);
    }
}

#if(_3DDI_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get 3DDI available
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4GetInterlace3ddiAvaible(void)
{
    // 3DDI Check for 2x clk from Mac
    if((ScalerGetBit(P69_4A_FRL_MEASURE_A, _BIT4) == _BIT4) && (g_ulHdmiFrlMacRx4PixelClkValue < (_3DDI_PCLK_LIMIT + 10000)))
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
bit ScalerHdmiFrlMacRx4CedCheck(void)
{
    WORD usLane0CedCounter = 0;
    WORD usLane1CedCounter = 0;
    WORD usLane2CedCounter = 0;
    WORD usLane3CedCounter = 0;
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // CED is enable?
    if(ScalerGetBit(P78_09_HDMI21_FRL_CED_1, _BIT6) == _BIT6)
    {
        // Pop CED counter
        ScalerSetByte(P78_0A_HDMI21_FRL_CED_2, 0x80);
        usLane0CedCounter = (((ScalerGetByte(P78_0A_HDMI21_FRL_CED_2) & 0x7F) << 8) | (ScalerGetByte(P78_0B_HDMI21_FRL_CED_3)));
        usLane1CedCounter = (((ScalerGetByte(P78_0C_HDMI21_FRL_CED_4) & 0x7F) << 8) | (ScalerGetByte(P78_0D_HDMI21_FRL_CED_5)));
        usLane2CedCounter = (((ScalerGetByte(P78_0E_HDMI21_FRL_CED_6) & 0x7F) << 8) | (ScalerGetByte(P78_0F_HDMI21_FRL_CED_7)));
        usLane3CedCounter = (((ScalerGetByte(P78_10_HDMI21_FRL_CED_8) & 0x7F) << 8) | (ScalerGetByte(P78_11_HDMI21_FRL_CED_9)));

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
bit ScalerHdmiFrlMacRx4RsedCheck(void)
{
    // RSED is enable?
    if(ScalerGetBit(P69_19_HDMI21_FW_RS_5, _BIT7) == _BIT7)
    {
        if((ScalerGetByte(P69_14_HDMI21_FW_RS_0) == 0x00) && (ScalerGetByte(P69_15_HDMI21_FW_RS_1) == 0x00) && (ScalerGetByte(P69_16_HDMI21_FW_RS_2) == 0x00) && (ScalerGetByte(P69_17_HDMI21_FW_RS_3) == 0x00))
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
EnumSourceType ScalerHdmiFrlMacRx4ScanInputPort(EnumPortType enumPortType)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
    bit bFreeSyncReceive = _TRUE;
#endif

    enumPortType = enumPortType;

    // if has HPD event, Link Training not finsih, PHY not set or FRL_rate changed, it will skip ScanInputPort
#if(_HDMI_FRL_MAC_RX4_LINK_TRAINING_BYPASS == _OFF)
    if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() != _TMDS_MAC_RX_HPD_NONE) || (GET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE() != _HDMI_FRL_LT_LTSEND) || (GET_HDMI_FRL_MAC_RX4_PHY_SET() != _TRUE) || (GET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    // CTS is testing
    if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_30_PORT_PAGE73_HDMI_SCDC_30, _BIT1) == _BIT1)
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
    ScalerSetBit(P78_D6_HDMI_SHDR_IE, ~_BIT4, 0x00);
#endif

    // FRL format check
    if(ScalerHdmiFrlMacRx4FrlVideoCheck() == _FALSE)
    {
        DebugMessageRx4("FRL Rx4: Video fail", 0);
        return _SOURCE_NONE;
    }

    // Measure check
    if(ScalerHdmiFrlMacRx4MeasureCheck() == _FALSE)
    {
        DebugMessageRx4("FRL Rx4: Measure fail", 0);
        return _SOURCE_NONE;
    }

    // Clear Info Packet SRAM
    ScalerSetBit(P78_AD_TMDS_CPS, ~_BIT3, _BIT3);
    ScalerSetBit(P78_AD_TMDS_CPS, ~_BIT3, 0x00);

    // Reset All Pkt Received Flag (EMP & RSV)
    ScalerHdmiFrlMacRx4ResetAllPacketReceiveStatus();

    ScalerHdmiFrlMacRx4RoundRobinIrqEnable(_ENABLE);

    // HDMI packet detect
    ScalerHdmiFrlMacRx4PacketDetect(_WAIT);

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
    // Active EMP SRAM
    ScalerHdmiFrlMacRx4EmpSramSetting(_ENABLE);
#endif

    ScalerHdmiFrlMacRx4VideoSetting();

    SET_COLOR_DEPTH(enumMappingPort, ScalerHdmiFrlMacRx4GetColorDepth());

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
    // Get EMP packet
    ScalerHdmiFrlMacRx4EmpPacketDetect(_WAIT);
#endif

    // DPF Setting
    if(ScalerHdmiFrlMacRx4DisplayFormatSetting() == _FALSE)
    {
        return _SOURCE_NONE;
    }

    // DPLL and Tracking setting
    if(ScalerHdmiFrlMacRx4StreamClkRegenerate() == _FALSE)
    {
        return _SOURCE_NONE;
    }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
    if(bFreeSyncReceive == _TRUE)
#else
    if(GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
#endif
    {
        ScalerTmdsMacRxSetFreesyncProc(enumMappingPort, _ENABLE);

        // Get SPD Free Sync Vfreq Max
        SET_DRR_VFREQ_MAX(GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10);    // 0.1Hz
        SET_DRR_VFREQ_MIN(GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10);
    }
    else
#endif
    {
#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
        if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
        {
#if(_HDMI21_VRR_SUPPORT == _ON)
            WORD usSourceBrr = 0x00;

            // Get Base Frame Rate from SRC
            if((GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_VIC) != 0x00))
            {
                usSourceBrr = ((WORD)ScalerTmdsMacRxGetVicVfreqParameter(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_VIC)) * 10);
                DebugMessageRx4("VRR BRR (AVI IF VIC)", usSourceBrr);
            }
            else if((GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerHdmiFrlMacRx4Rsv6GetAviInfo(_AVI_INFO_FR) != 0x00))
            {
                usSourceBrr = (ScalerTmdsMacRxGetOvtVfreqParameter(ScalerHdmiFrlMacRx4Rsv6GetAviInfo(_AVI_INFO_FR)) * 10);
                DebugMessageRx4("VRR BRR (AVI IF OVT)", usSourceBrr);
            }
            else if(ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_BASE_REFRESH_RATE) != 0x00)
            {
                usSourceBrr = ((WORD)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_BASE_REFRESH_RATE) * 10);
                DebugMessageRx4("VRR BRR (VTEM)", usSourceBrr);
            }
            else
            {
                DebugMessageRx4("VRR BRR Error!!", 0x00);
            }

            // Get max Vfmax from SRC BRR
            SET_DRR_VFREQ_MAX(usSourceBrr);

            if(((bit)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _ENABLE)
            {
                SET_TMDS_MAC_RX4_HDMI21_VRR_EN();
                DebugMessageRx4("FRL Rx4: VRR_EN", 0x00);
            }
            else
            {
                CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
                DebugMessageRx4("FRL Rx4: VRR_DIS", 0x00);
            }

            if(((bit)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _ENABLE)
            {
                SET_TMDS_MAC_RX4_HDMI21_QMS_EN();
                DebugMessageRx4("FRL Rx4: QMS_EN", 0x00);
            }
            else
            {
                CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
                DebugMessageRx4("FRL Rx4: QMS_DIS", 0x00);
            }

#if(_HDMI_FORCE_VRR_SUPPORT == _ON)
            // Get SPD Free Sync Vfreq Max
            SET_DRR_VFREQ_MAX(0);
            SET_DRR_VFREQ_MIN(0);
#endif
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
            SET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR(ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_FVA_FACTOR_M1) + 1);
#endif
        }
#endif
    }

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    if(GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED() == _TRUE)
    {
        ScalerTmdsMacRxSetFreesyncReplayProc(enumMappingPort, _ENABLE);

        // Set Freesync Replay enable
        ScalerSetBit(P78_D6_HDMI_SHDR_IE, ~_BIT4, _BIT4);
    }
#endif

#if(_HDMI_FRL_MAC_RX4_LFSR_TEST_MODE == _ON)
    while(_TRUE)
    {
        // ScalerHdmiFrlMacRx4LtpCheck();
        ScalerHdmiFrlMacRx4LfsrCheck();
        // ScalerHdmiFrlMacRx4GapCheck();

        // pop CED
        ScalerSetByte(P78_0A_HDMI21_FRL_CED_2, 0x80);

        DebugMessageRx4("FRL Rx4: L0 CED", ((ScalerGetByte(P78_0A_HDMI21_FRL_CED_2) & 0x7F) << 8) | (ScalerGetByte(P78_0B_HDMI21_FRL_CED_3)));
        DebugMessageRx4("FRL Rx4: L1 CED", ((ScalerGetByte(P78_0C_HDMI21_FRL_CED_4) & 0x7F) << 8) | (ScalerGetByte(P78_0D_HDMI21_FRL_CED_5)));
        DebugMessageRx4("FRL Rx4: L2 CED", ((ScalerGetByte(P78_0E_HDMI21_FRL_CED_6) & 0x7F) << 8) | (ScalerGetByte(P78_0F_HDMI21_FRL_CED_7)));
        DebugMessageRx4("FRL Rx4: L3 CED", ((ScalerGetByte(P78_10_HDMI21_FRL_CED_8) & 0x7F) << 8) | (ScalerGetByte(P78_11_HDMI21_FRL_CED_9)));
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
EnumSourceType ScalerHdmiFrlMacRx4SeamlessReset(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    DebugMessageRx4("===== FRL Rx4 SDR_DM Seamless flow =====", 0x00);

    // reset for AVI IF WD
    ScalerHdmiFrlMacRx4WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

    // Measure check
    if(ScalerHdmiFrlMacRx4MeasureCheck() == _FALSE)
    {
        DebugMessageRx4("FRL Rx4: Measure fail", 0);
        return _SOURCE_NONE;
    }

    // HDMI packet detect
    ScalerHdmiFrlMacRx4PacketDetect(_NOT_WAIT);

    ScalerHdmiFrlMacRx4VideoSetting();

    SET_COLOR_DEPTH(enumMappingPort, ScalerHdmiFrlMacRx4GetColorDepth());

    // Precheck for (422, 12bpc) <-> (RGB, 8bpc) case
    if(ScalerHdmiFrlMacRx4CheckSeamlessCondition() == _FALSE)
    {
        DebugMessageRx4("FRL Rx4: NOT Seamless condition", 0x00);
        return _SOURCE_NONE;
    }

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
    // Get EMP packet
    ScalerHdmiFrlMacRx4EmpPacketDetect(_NOT_WAIT);
#endif

    return _SOURCE_HDMI;
}

//--------------------------------------------------
// Description  : Check seamless video format that is avaiable for SRC
// Input Value  : None
// Output Value : _TRUE(seamless case)
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4CheckSeamlessCondition(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    switch(GET_COLOR_SPACE(enumMappingPort))
    {
        case _COLOR_SPACE_RGB:
        case _COLOR_SPACE_YCBCR444:

            // check GCP CD field to ensure 8bpc
            if(ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x42, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) < 0x05)
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
bit ScalerHdmiFrlMacRx4FrlVideoCheck(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Clear Vsync and Hsync invert before check source's polarity
    ScalerSetBit(P69_26_HDMI21_DI_0, ~(_BIT5 | _BIT4), 0x00);

    // Disable FRL formate detection
    ScalerSetBit(P69_30_HDMI21_FRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Clear FRL format flag
    ScalerSetBit(P69_30_HDMI21_FRL_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(P69_31_HDMI21_FRL_1, ~(_BIT6 | _BIT4 | _BIT2), (_BIT6 | _BIT4 | _BIT2));

    // Enable FRL format detection
    ScalerSetBit(P69_30_HDMI21_FRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Wait at least 1 frame for HW update FRL flag
    ScalerTimerDelayXms(45);

    // Check Video-GB, Video-packet, Vsync and data island, MAP type/length no error
    if((ScalerGetBit(P69_30_HDMI21_FRL_0, (_BIT6 | _BIT5 | _BIT3)) == (_BIT6 | _BIT5 | _BIT3)) && (ScalerGetBit(P69_31_HDMI21_FRL_1, (_BIT6 | _BIT4 | _BIT2)) == 0x00))
    {
        // Enable RS fw error count
        // ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);

        return _TRUE;
    }
    else if((ScalerGetBit(P69_30_HDMI21_FRL_0, (_BIT6 | _BIT5 | _BIT3)) == (_BIT6 | _BIT5 | _BIT3)) && (ScalerGetBit(P69_31_HDMI21_FRL_1, _BIT4) == 0x00)) // QD 480p has bug
    {
        // Enable RS fw error count
        // ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);

        DebugMessageRx4("QD980_480P bug", 0);
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
bit ScalerHdmiFrlMacRx4MeasureCheck(void)
{
    WORD usHdmiFrlMacRx4Vtotal1 = 0;
    WORD usHdmiFrlMacRx4Vtotal2 = 0;

    // if has Hsync, use Hsync for measure
    if(ScalerGetBit(P69_30_HDMI21_FRL_0, _BIT4) == _BIT4)
    {
        ScalerSetBit(P69_43_FRL_MEASURE_3, ~(_BIT7 | _BIT6), 0x00);
    }
    // no Hsync(DSC mode), use virtual-hsync for measure
    else
    {
        ScalerSetBit(P69_43_FRL_MEASURE_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    // Skip first 16 lines
    ScalerSetBit(P69_43_FRL_MEASURE_3, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);

    // Measure 256 lines for Htotal/Hactive clock count after E ver.
    ScalerSetBit(P69_5A_FRL_MEASURE_18, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

    // Check Source's Vsync polarity
    if(ScalerGetBit(P69_49_FRL_MEASURE_9, _BIT5) == _BIT5)
    {
        ScalerSetBit(P69_26_HDMI21_DI_0, ~_BIT4, _BIT4);
    }

    // Check Source's Hsync polarity
    if(ScalerGetBit(P69_49_FRL_MEASURE_9, _BIT6) == _BIT6)
    {
        ScalerSetBit(P69_26_HDMI21_DI_0, ~_BIT5, _BIT5);
    }

    // Set HDCP Vsync from Packet Decoder
    ScalerSetBit(P6D_3C_I2C_DUMMY_1, ~_BIT6, 0x00);

    // Clear Interlace flag
    ScalerSetBit(P69_4A_FRL_MEASURE_A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // Start Measure
    ScalerSetBit(P69_40_FRL_MEASURE_0, ~_BIT7, _BIT7);

    // wait 4 frames
    ScalerTimerPollingFlagProc(180, P69_40_FRL_MEASURE_0, _BIT7, _FALSE);

    //////////////////////
    // Interlace Check  //
    //////////////////////

    // Check Interlace
    if(ScalerGetBit(P69_4A_FRL_MEASURE_A, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
    {
        // Interlace mode
    }

    //////////////////////
    // Horizontal Check //
    //////////////////////

    // Get Hsync_width
    g_usHdmiFrlMacRx4Hsync = ((WORD)ScalerGetBit(P69_4B_FRL_MEASURE_B, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ((WORD)ScalerGetByte(P69_4C_FRL_MEASURE_C));

    // Get Hback_porch
    g_usHdmiFrlMacRx4Hback = ((WORD)ScalerGetBit(P69_4D_FRL_MEASURE_D, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ((WORD)ScalerGetByte(P69_4E_FRL_MEASURE_E));

    // Get Hactive
    g_usHdmiFrlMacRx4Hactive = ((WORD)ScalerGetByte(P69_4F_FRL_MEASURE_F) << 8) | ((WORD)ScalerGetByte(P69_50_FRL_MEASURE_10));

    // Get Htotal
    g_usHdmiFrlMacRx4Htotal = ((WORD)ScalerGetByte(P69_51_FRL_MEASURE_11) << 8) | ((WORD)ScalerGetByte(P69_52_FRL_MEASURE_12));

    // Calculate Hfront
    g_usHdmiFrlMacRx4Hfront = g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hactive - g_usHdmiFrlMacRx4Hsync - g_usHdmiFrlMacRx4Hback;

    DebugMessageRx4("FRL Rx4: Hfront", g_usHdmiFrlMacRx4Hfront);
    DebugMessageRx4("FRL Rx4: Hsync", g_usHdmiFrlMacRx4Hsync);
    DebugMessageRx4("FRL Rx4: Hbporch", g_usHdmiFrlMacRx4Hback);
    DebugMessageRx4("FRL Rx4: Hactive", g_usHdmiFrlMacRx4Hactive);
    DebugMessageRx4("FRL Rx4: Htotal", g_usHdmiFrlMacRx4Htotal);

    // if Hfront bigger than Htotal and not DSC mode, measure is not reasonable due to Hfront is by calculation.
    if((g_usHdmiFrlMacRx4Hfront >= g_usHdmiFrlMacRx4Htotal) && (ScalerGetBit(P69_30_HDMI21_FRL_0, _BIT4) == _BIT4))
    {
        DebugMessageRx4("FRL Rx4: measure fail", 0);
        return _FALSE;
    }

    ////////////////////
    // Vertical Check //
    ////////////////////

    // Get Vsync_width
    g_usHdmiFrlMacRx4Vsync = ScalerGetByte(P69_53_FRL_MEASURE_13);

    // Get Vback_porch
    g_usHdmiFrlMacRx4Vback = ((WORD)ScalerGetBit(P69_54_FRL_MEASURE_14, (_BIT2 | _BIT1 | _BIT0)) << 8) | ((WORD)ScalerGetByte(P69_55_FRL_MEASURE_15));

    // Get Vactive
    g_usHdmiFrlMacRx4Vactive = ((WORD)ScalerGetByte(P69_56_FRL_MEASURE_16) << 8) | ((WORD)ScalerGetByte(P69_57_FRL_MEASURE_17));

    // Get Vtotal
    usHdmiFrlMacRx4Vtotal1 = ((WORD)ScalerGetByte(P69_45_FRL_MEASURE_5) << 8) | ((WORD)ScalerGetByte(P69_46_FRL_MEASURE_6));
    usHdmiFrlMacRx4Vtotal2 = ((WORD)ScalerGetByte(P69_47_FRL_MEASURE_7) << 8) | ((WORD)ScalerGetByte(P69_48_FRL_MEASURE_8));

    // Calculate Vstart
    g_usHdmiFrlMacRx4Vtotal = (usHdmiFrlMacRx4Vtotal1 + usHdmiFrlMacRx4Vtotal2) / 2;

    g_usHdmiFrlMacRx4Vfront = (g_usHdmiFrlMacRx4Vtotal - g_usHdmiFrlMacRx4Vsync - g_usHdmiFrlMacRx4Vback - g_usHdmiFrlMacRx4Vactive);

    DebugMessageRx4("FRL Rx4: Vfront", g_usHdmiFrlMacRx4Vfront);
    DebugMessageRx4("FRL Rx4: Vsync", g_usHdmiFrlMacRx4Vsync);
    DebugMessageRx4("FRL Rx4: Vbporch", g_usHdmiFrlMacRx4Vback);
    DebugMessageRx4("FRL Rx4: Vactive", g_usHdmiFrlMacRx4Vactive);
    DebugMessageRx4("FRL Rx4: Vtotal-1", usHdmiFrlMacRx4Vtotal1);
    DebugMessageRx4("FRL Rx4: Vtotal-2", usHdmiFrlMacRx4Vtotal2);

    if((g_usHdmiFrlMacRx4Vsync + g_usHdmiFrlMacRx4Vback + g_usHdmiFrlMacRx4Vactive) >= g_usHdmiFrlMacRx4Vtotal)
    {
        DebugMessageRx4("FRL Rx4: measure fail", 0);
        return _FALSE;
    }

    // Check Measure Result Fail / Error
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // DSC mode, Hsync maybe 0, ECO Version C will fixed this bug.
    if((g_usHdmiFrlMacRx4Hactive == 0x0000) || (g_usHdmiFrlMacRx4Htotal == 0x0000) ||
       (g_usHdmiFrlMacRx4Vsync == 0x0000) || (g_usHdmiFrlMacRx4Vback == 0x0000) || (g_usHdmiFrlMacRx4Vactive == 0x0000) || (usHdmiFrlMacRx4Vtotal1 == 0x0000) ||
       (usHdmiFrlMacRx4Vtotal2 == 0x0000))
#else
    if((g_usHdmiFrlMacRx4Hsync == 0x0000) || (g_usHdmiFrlMacRx4Hback == 0x0000) || (g_usHdmiFrlMacRx4Hactive == 0x0000) || (g_usHdmiFrlMacRx4Htotal == 0x0000) ||
       (g_usHdmiFrlMacRx4Vsync == 0x0000) || (g_usHdmiFrlMacRx4Vback == 0x0000) || (g_usHdmiFrlMacRx4Vactive == 0x0000) || (usHdmiFrlMacRx4Vtotal1 == 0x0000) ||
       (usHdmiFrlMacRx4Vtotal2 == 0x0000))
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
bit ScalerHdmiFrlMacRx4DisplayFormatSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    DWORD ulHdmiFrlMacHtotalClkCount = 0;
    DWORD ulLinkClkValue = 0;
    WORD usHdmiFrlMacRx4DPFHfront = 0;
    WORD usHdmiFrlMacRx4DPFHsync = 0;
    WORD usHdmiFrlMacRx4DPFHstart = 0;
    WORD usHdmiFrlMacRx4DPFHactive = 0;
    WORD usHdmiFrlMacRx4DPFHtotal = 0;
    DWORD ulHdmiFrlMacVstoVsDelay = 0;
    WORD usFifoOffset = 0;


    //////////////////////
    // Deep Color Check //
    //////////////////////

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        // Disable deep color block
        ScalerSetBit(P78_B5_TMDS_UDC0, ~_BIT7, 0x00);
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_80_PORT_PAGE78_HDMI_DPC_SET0, ~_BIT7, 0x00);

        // Set HW auto detect deep color
        ScalerSetBit(P78_B8_TMDS_DPC1, ~_BIT2, _BIT2);

        //////////////////////
        // DSC Check        //
        //////////////////////

        // When virtual-hsync has overlap den(C version ECO) then modify vstart
        if(ScalerGetBit(P69_43_FRL_MEASURE_3, _BIT0) == _BIT0)
        {
            // modify Vstart
            // Vback_porch need add 1
            g_usHdmiFrlMacRx4Vback = g_usHdmiFrlMacRx4Vback + 1;

            // Vfront porch need minus 1 due to Vback_porch add 1
            g_usHdmiFrlMacRx4Vfront = g_usHdmiFrlMacRx4Vfront - 1;

            DebugMessageRx4("FRL Rx4: Vstart changed", g_usHdmiFrlMacRx4Vback);
        }
    }
    else
#endif
    {
        if((GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422))
        {
            DebugMessageRx4("FRL Rx4: Deep Color Detected", GET_COLOR_DEPTH(enumMappingPort));

            // Max. 8K timing
            g_usHdmiFrlMacRx4Hsync = (g_usHdmiFrlMacRx4Hsync * 8) / GET_COLOR_DEPTH(enumMappingPort);
            g_usHdmiFrlMacRx4Hback = (g_usHdmiFrlMacRx4Hback * 8) / GET_COLOR_DEPTH(enumMappingPort);
            g_usHdmiFrlMacRx4Hactive = (WORD)(((DWORD)g_usHdmiFrlMacRx4Hactive * 8) / GET_COLOR_DEPTH(enumMappingPort));
            g_usHdmiFrlMacRx4Htotal = (WORD)(((DWORD)g_usHdmiFrlMacRx4Htotal * 8) / GET_COLOR_DEPTH(enumMappingPort));
            g_usHdmiFrlMacRx4Hfront = g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hsync - g_usHdmiFrlMacRx4Hback - g_usHdmiFrlMacRx4Hactive;

            // Enable deep color block
            ScalerSetBit(P78_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_80_PORT_PAGE78_HDMI_DPC_SET0, ~_BIT7, _BIT7);

            // force default phase, after D version ECO remove default phase
            /*ScalerSetBit(P78_B8_TMDS_DPC1, ~(_BIT2 | _BIT1), _BIT1);

            if(GET_COLOR_DEPTH(enumMappingPort) == _COLOR_DEPTH_10_BITS)
            {
                ScalerSetBit(P78_B4_TMDS_DPC0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            }
            else if(GET_COLOR_DEPTH(enumMappingPort) == _COLOR_DEPTH_12_BITS)
            {
                ScalerSetBit(P78_B4_TMDS_DPC0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }*/

            // HW auto detect deep color, after E version
            ScalerSetBit(P78_B8_TMDS_DPC1, ~_BIT2, _BIT2);
        }
        else
        {
            // Disable deep color block
            ScalerSetBit(P78_B5_TMDS_UDC0, ~_BIT7, 0x00);
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_80_PORT_PAGE78_HDMI_DPC_SET0, ~_BIT7, 0x00);

            // Set HW auto detect deep color
            ScalerSetBit(P78_B8_TMDS_DPC1, ~_BIT2, _BIT2);
        }
    }


    //////////////////////////////////////////////
    // Pixel Repetition Check                   //
    // RLE1039 down sampling before DPF module  //
    //////////////////////////////////////////////
    if(GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
    {
        DebugMessageRx4("FRL Rx4: Pixel Repetition Detected", GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION());

        g_usHdmiFrlMacRx4Hsync = g_usHdmiFrlMacRx4Hsync / (GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx4Hback = g_usHdmiFrlMacRx4Hback / (GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx4Hactive = g_usHdmiFrlMacRx4Hactive / (GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx4Htotal = g_usHdmiFrlMacRx4Htotal / (GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION() + 1);
        g_usHdmiFrlMacRx4Hfront = g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hsync - g_usHdmiFrlMacRx4Hback - g_usHdmiFrlMacRx4Hactive;
    }


    ///////////////////////////////////////////
    // Calculate LinkClk-PixelClk Conversion //
    ///////////////////////////////////////////

    // Get Htotal Clock Count
    ulHdmiFrlMacHtotalClkCount = ((DWORD)ScalerGetBit(P69_40_FRL_MEASURE_0, _BIT0) << 16) | ((DWORD)ScalerGetByte(P69_41_FRL_MEASURE_1) << 8) | ((DWORD)ScalerGetByte(P69_42_FRL_MEASURE_2));

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
    if(GET_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH() == _FALSE)
    {
        g_ulHdmiFrlMacRx4PixelClkValue = ulLinkClkValue / (18 * 2) * (DWORD)g_usHdmiFrlMacRx4Htotal / ulHdmiFrlMacHtotalClkCount * 2;
    }

    g_usHdmiFrlMacRx4FrameRate = (g_ulHdmiFrlMacRx4PixelClkValue * 100 / g_usHdmiFrlMacRx4Htotal) * 10 / g_usHdmiFrlMacRx4Vtotal;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
    {
        if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
        {
            g_ulHdmiFrlMacRx4PixelClkValue = g_ulHdmiFrlMacRx4PixelClkValue * 2;
        }
    }

    DebugMessageRx4("FRL Rx4: ulHdmiFrlMacHtotalClkCount", ulHdmiFrlMacHtotalClkCount);
    DebugMessageRx4("FRL Rx4: g_ulHdmiFrlMacRx4PixelClkValue", g_ulHdmiFrlMacRx4PixelClkValue);
    DebugMessageRx4("FRL Rx4: g_usHdmiFrlMacRx4FrameRate", g_usHdmiFrlMacRx4FrameRate);

    // Check Pixel Clock
    if((g_ulHdmiFrlMacRx4PixelClkValue > 2800000) || (g_ulHdmiFrlMacRx4PixelClkValue < 5000) || (g_usHdmiFrlMacRx4FrameRate == 0))
    {
        DebugMessageRx4("FRL Rx4: Pixel Clk(MHz)", (g_ulHdmiFrlMacRx4PixelClkValue / 1000));

        return _FALSE;
    }


    ////////////////////////////
    // Display Format Setting //
    ////////////////////////////

    // Disable Display Format Generation
    ScalerSetBit(P69_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // force frame sync mode
    ScalerSetBit(P69_70_DPF_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

    // Set DPF input Hwidth(this reg is effective when Hactive div 4 is not 0)
    ScalerSetByte(P69_86_DPF_IN_HWD_M, (BYTE)(g_usHdmiFrlMacRx4Hactive >> 8));
    ScalerSetByte(P69_87_DPF_IN_HWD_L, (BYTE)(g_usHdmiFrlMacRx4Hactive & 0x00FF));

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

        usHdmiFrlMacRx4DPFHactive = ((g_usHdmiFrlMacRx4Hactive % 4) != 0) ? ((g_usHdmiFrlMacRx4Hactive / 4) + 1) : (g_usHdmiFrlMacRx4Hactive / 4);
        usHdmiFrlMacRx4DPFHtotal = ((g_usHdmiFrlMacRx4Htotal % 4) != 0) ? ((g_usHdmiFrlMacRx4Htotal / 4) + 1) : (g_usHdmiFrlMacRx4Htotal / 4);
        usHdmiFrlMacRx4DPFHsync = 8; // assume Hsyncwidth is 8T(5T may lost due to HW force HVsync rising at same edge)
        usHdmiFrlMacRx4DPFHstart = usHdmiFrlMacRx4DPFHtotal - usHdmiFrlMacRx4DPFHactive - 4; // Hfrotnporch is 4T, Hbackporch min is 4T(16-4-8=4)

        // DSC VS to VS delay
        ulHdmiFrlMacVstoVsDelay = (1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 4) *(ulLinkClkValue / 18) / (g_ulHdmiFrlMacRx4PixelClkValue / 4);
        DebugMessageRx4("FRL Rx4: VstoVsDelay", ulHdmiFrlMacVstoVsDelay);

        // In 4P mode, DPF read addr don't need add
        ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);

        DebugMessageRx4("FRL Rx4: DSC mode", 0);
    }
    else
#endif
    {
        if(ScalerGetBit(P69_70_DPF_CTRL_0, _BIT4) == _BIT4)
        {
            //////////////////////
            // Line Sync mode   //
            //////////////////////

            // 4P/2P/1P mode
            if((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ)
            {
                ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

                usHdmiFrlMacRx4DPFHactive = ((g_usHdmiFrlMacRx4Hactive % 4) != 0) ? ((g_usHdmiFrlMacRx4Hactive / 4) + 1) : (g_usHdmiFrlMacRx4Hactive / 4);
                usHdmiFrlMacRx4DPFHsync = ((g_usHdmiFrlMacRx4Hsync % 4) != 0) ? ((g_usHdmiFrlMacRx4Hsync / 4) + 1) : (g_usHdmiFrlMacRx4Hsync / 4);
                usHdmiFrlMacRx4DPFHstart = (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) % 4) != 0) ? (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 4) + 1) : ((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 4);
                usHdmiFrlMacRx4DPFHfront = ((g_usHdmiFrlMacRx4Hfront % 4) != 0) ? ((g_usHdmiFrlMacRx4Hfront / 4) + 1) : (g_usHdmiFrlMacRx4Hfront / 4);
                usHdmiFrlMacRx4DPFHtotal = usHdmiFrlMacRx4DPFHfront + usHdmiFrlMacRx4DPFHstart + usHdmiFrlMacRx4DPFHactive;
                usFifoOffset = _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 4;

                // In 4P mode, DPF read addr don't need add
                ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);

                DebugMessageRx4("FRL Rx4: 4P mode", 0);
            }
            else if((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_FRL_DPF_2P_MODE_FREQ)
            {
                ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT6);

                usHdmiFrlMacRx4DPFHactive = ((g_usHdmiFrlMacRx4Hactive % 2) != 0) ? ((g_usHdmiFrlMacRx4Hactive / 2) + 1) : (g_usHdmiFrlMacRx4Hactive / 2);
                usHdmiFrlMacRx4DPFHsync = ((g_usHdmiFrlMacRx4Hsync % 2) != 0) ? ((g_usHdmiFrlMacRx4Hsync / 2) + 1) : (g_usHdmiFrlMacRx4Hsync / 2);
                usHdmiFrlMacRx4DPFHstart = (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) % 2) != 0) ? (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 2) + 1) : ((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 2);
                usHdmiFrlMacRx4DPFHfront = ((g_usHdmiFrlMacRx4Hfront % 2) != 0) ? ((g_usHdmiFrlMacRx4Hfront / 2) + 1) : (g_usHdmiFrlMacRx4Hfront / 2);
                usHdmiFrlMacRx4DPFHtotal = usHdmiFrlMacRx4DPFHfront + usHdmiFrlMacRx4DPFHstart + usHdmiFrlMacRx4DPFHactive;

                usFifoOffset = _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 2;

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx4Hactive % 4) != 0)
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx4("FRL Rx4: 2P mode", 0);
            }
            else
            {
                ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT7);

                usHdmiFrlMacRx4DPFHactive = g_usHdmiFrlMacRx4Hactive;
                usHdmiFrlMacRx4DPFHsync = g_usHdmiFrlMacRx4Hsync;
                usHdmiFrlMacRx4DPFHstart = (g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback);
                usHdmiFrlMacRx4DPFHfront = g_usHdmiFrlMacRx4Hfront;
                usHdmiFrlMacRx4DPFHtotal = usHdmiFrlMacRx4DPFHfront + usHdmiFrlMacRx4DPFHstart + usHdmiFrlMacRx4DPFHactive;

                if(g_usHdmiFrlMacRx4Hactive / 2 > _HDMI_FRL_DPF_FIFO_HALF_LENGTH)
                {
                    usFifoOffset = _HDMI_FRL_DPF_FIFO_HALF_LENGTH;
                }
                else
                {
                    usFifoOffset = g_usHdmiFrlMacRx4Hactive / 2;
                }

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx4Hactive % 4) != 0)
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx4("FRL Rx4: 1P mode", 0);
            }

            // if Hfront is too small, need extend Htotal??????
            if(g_usHdmiFrlMacRx4Hfront < 300)
            {
                // Calculate DPF Htotal
                usHdmiFrlMacRx4DPFHtotal = g_usHdmiFrlMacRx4Hfront + usHdmiFrlMacRx4DPFHtotal;
            }
        }
        else
        {
            //////////////////////
            // Frame Sync mode  //
            //////////////////////

            // 4P/2P/1P mode, 420 only 1P/2P mode
            if(((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420))
            {
                ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

                usHdmiFrlMacRx4DPFHsync = ((g_usHdmiFrlMacRx4Hsync % 4) != 0) ? ((g_usHdmiFrlMacRx4Hsync / 4) + 1) : (g_usHdmiFrlMacRx4Hsync / 4);
                usHdmiFrlMacRx4DPFHstart = (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) % 4) != 0) ? (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 4) + 1) : ((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 4);
                usHdmiFrlMacRx4DPFHactive = ((g_usHdmiFrlMacRx4Hactive % 4) != 0) ? ((g_usHdmiFrlMacRx4Hactive / 4) + 1) : (g_usHdmiFrlMacRx4Hactive / 4);

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    // Check Hblank must >= 88, due to IMC HW Limitation
                    if((g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hactive) < 88)
                    {
                        usHdmiFrlMacRx4DPFHtotal = (((g_usHdmiFrlMacRx4Hactive + 88) % 4) != 0) ? (((g_usHdmiFrlMacRx4Hactive + 88) / 4) + 1) : ((g_usHdmiFrlMacRx4Hactive + 88) / 4);
                    }
                    else
                    {
                        usHdmiFrlMacRx4DPFHtotal = ((g_usHdmiFrlMacRx4Htotal % 4) != 0) ? ((g_usHdmiFrlMacRx4Htotal / 4) + 1) : (g_usHdmiFrlMacRx4Htotal / 4);
                    }
                }
                else
#endif
                {
                    usHdmiFrlMacRx4DPFHtotal = ((g_usHdmiFrlMacRx4Htotal % 4) != 0) ? ((g_usHdmiFrlMacRx4Htotal / 4) + 1) : (g_usHdmiFrlMacRx4Htotal / 4);
                }

                ulHdmiFrlMacVstoVsDelay = ((1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 4) *(ulLinkClkValue / 18) / (g_ulHdmiFrlMacRx4PixelClkValue / 4));

                // In 4P mode, DPF read addr don't need add
                ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);

                DebugMessageRx4("FRL Rx4: frame 4P mode", 0);
            }
            else if((((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_FRL_DPF_2P_MODE_FREQ) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420)) ||
                    (((g_ulHdmiFrlMacRx4PixelClkValue / 200) > _HW_HDMI_FRL_DPF_2P_MODE_FREQ) && (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)))
            {
                ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT6);

                usHdmiFrlMacRx4DPFHsync = ((g_usHdmiFrlMacRx4Hsync % 2) != 0) ? ((g_usHdmiFrlMacRx4Hsync / 2) + 1) : (g_usHdmiFrlMacRx4Hsync / 2);
                usHdmiFrlMacRx4DPFHstart = (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) % 2) != 0) ? (((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 2) + 1) : ((g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback) / 2);
                usHdmiFrlMacRx4DPFHactive = ((g_usHdmiFrlMacRx4Hactive % 2) != 0) ? ((g_usHdmiFrlMacRx4Hactive / 2) + 1) : (g_usHdmiFrlMacRx4Hactive / 2);

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    // Check Hblank must >= 88, due to IMC HW Limitation
                    if(((g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hactive) < 44) && (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420))
                    {
                        usHdmiFrlMacRx4DPFHtotal = (((g_usHdmiFrlMacRx4Hactive + 44) % 2) != 0) ? (((g_usHdmiFrlMacRx4Hactive + 44) / 2) + 1) : ((g_usHdmiFrlMacRx4Hactive + 44) / 2);
                    }
                    else if((g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hactive) < 88)
                    {
                        usHdmiFrlMacRx4DPFHtotal = (((g_usHdmiFrlMacRx4Hactive + 88) % 2) != 0) ? (((g_usHdmiFrlMacRx4Hactive + 88) / 2) + 1) : ((g_usHdmiFrlMacRx4Hactive + 88) / 2);
                    }
                    else
                    {
                        usHdmiFrlMacRx4DPFHtotal = ((g_usHdmiFrlMacRx4Htotal % 2) != 0) ? ((g_usHdmiFrlMacRx4Htotal / 2) + 1) : (g_usHdmiFrlMacRx4Htotal / 2);
                    }
                }
                else
#endif
                {
                    usHdmiFrlMacRx4DPFHtotal = ((g_usHdmiFrlMacRx4Htotal % 2) != 0) ? ((g_usHdmiFrlMacRx4Htotal / 2) + 1) : (g_usHdmiFrlMacRx4Htotal / 2);
                }

                ulHdmiFrlMacVstoVsDelay = ((1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH / 2) * (ulLinkClkValue / 18) / (g_ulHdmiFrlMacRx4PixelClkValue / 2));

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx4Hactive % 4) != 0)
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx4("FRL Rx4: frame 2P mode", 0);
            }
            // 1366 x 768 can use 1P mode after D version ECO
            else
            {
                ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT7 | _BIT6), _BIT7);

                usHdmiFrlMacRx4DPFHsync = g_usHdmiFrlMacRx4Hsync;
                usHdmiFrlMacRx4DPFHstart = (g_usHdmiFrlMacRx4Hsync + g_usHdmiFrlMacRx4Hback);
                usHdmiFrlMacRx4DPFHactive = g_usHdmiFrlMacRx4Hactive;

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_M_DOMAIN_IMG_CMP_SUPPORT == _ON))
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    // Check Hblank must >= 88, due to IMC HW Limitation
                    if(((g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hactive) < 44) && (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420))
                    {
                        usHdmiFrlMacRx4DPFHtotal = g_usHdmiFrlMacRx4Hactive + 44;
                    }
                    else if((g_usHdmiFrlMacRx4Htotal - g_usHdmiFrlMacRx4Hactive) < 88)
                    {
                        usHdmiFrlMacRx4DPFHtotal = g_usHdmiFrlMacRx4Hactive + 88;
                    }
                    else
                    {
                        usHdmiFrlMacRx4DPFHtotal = g_usHdmiFrlMacRx4Htotal;
                    }
                }
                else
#endif
                {
                    usHdmiFrlMacRx4DPFHtotal = g_usHdmiFrlMacRx4Htotal;
                }

                ulHdmiFrlMacVstoVsDelay = ((1UL * _HDMI_FRL_DPF_FIFO_HALF_LENGTH) * (ulLinkClkValue / 18) / g_ulHdmiFrlMacRx4PixelClkValue);

                // if Hactive mod 4 is not 0, DPF read addr need add 1
                if((g_usHdmiFrlMacRx4Hactive % 4) != 0)
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, _BIT5);
                }
                else
                {
                    ScalerSetBit(P69_71_DPF_CTRL_1, ~_BIT5, 0x00);
                }

                DebugMessageRx4("FRL Rx4: frame 1P mode", 0);
            }
        }
    }

#if(_HDMI_FRL_DPF_TRACKING_METHOD == _HDMI_FRL_LINE_TRACKING)
    // DPF Htotal should be even due to line tracking limitation
    if(usHdmiFrlMacRx4DPFHtotal % 2 != 0)
    {
        usHdmiFrlMacRx4DPFHtotal = usHdmiFrlMacRx4DPFHtotal - 1;
    }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
    {
        // Check/Adjust DPF Hsync/Hstart
        if(ScalerHdmiFrlMacRx4DPFHsyncHstartAdjust(&usHdmiFrlMacRx4DPFHsync, &usHdmiFrlMacRx4DPFHstart, (usHdmiFrlMacRx4DPFHtotal - usHdmiFrlMacRx4DPFHactive)) == _TRUE)
        {
            DebugMessageRx4("FRL Rx4: Adjust DPF Hsync", usHdmiFrlMacRx4DPFHsync);
            DebugMessageRx4("FRL Rx4: Adjust DPF Hstart", usHdmiFrlMacRx4DPFHstart);
        }
    }

    // Set Hsync width and HSP is positive
    ScalerSetByte(P69_88_DPF_HSW_M, (BYTE)((usHdmiFrlMacRx4DPFHsync >> 8) & ~_BIT7));
    ScalerSetByte(P69_89_DPF_HSW_L, (BYTE)(usHdmiFrlMacRx4DPFHsync & 0x00FF));

    // Set Hstart
    ScalerSetByte(P69_82_DPF_HST_M, (BYTE)(usHdmiFrlMacRx4DPFHstart >> 8));
    ScalerSetByte(P69_83_DPF_HST_L, (BYTE)(usHdmiFrlMacRx4DPFHstart & 0x00FF));

    // Set Hwidth
    ScalerSetByte(P69_84_DPF_HWD_M, (BYTE)(usHdmiFrlMacRx4DPFHactive >> 8));
    ScalerSetByte(P69_85_DPF_HWD_L, (BYTE)(usHdmiFrlMacRx4DPFHactive & 0x00FF));

    // Set Htotal
    ScalerSetByte(P69_80_DPF_HTT_M, (BYTE)(usHdmiFrlMacRx4DPFHtotal >> 8));
    ScalerSetByte(P69_81_DPF_HTT_L, (BYTE)(usHdmiFrlMacRx4DPFHtotal & 0x00FF));

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        // Set Htotal use DPF_gen
        ScalerSetBit(P69_FC_DSC_HTT_0, ~_BIT7, 0x00);
    }
    else
#endif
    {
        // "420" or "3DDI Interlace" need set dsc_htt for DPF
#if(_3DDI_FUNCTION == _ON)
        if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (ScalerHdmiFrlMacRx4GetInterlace3ddiAvaible() == _TRUE))
#else
        if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
#endif
        {
            // Set dsc_htt
            ScalerSetBit(P69_FC_DSC_HTT_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usHdmiFrlMacRx4DPFHtotal >> 8));
            ScalerSetByte(P69_FD_DSC_HTT_1, (BYTE)(usHdmiFrlMacRx4DPFHtotal & 0x00FF));

#if(_3DDI_FUNCTION == _ON)
            if(((g_ulHdmiFrlMacRx4PixelClkValue / 100) <= _HW_HDMI_VIDEO_PLL_CLK_LIMIT) || (ScalerHdmiFrlMacRx4GetInterlace3ddiAvaible() == _TRUE))
#else
            if((g_ulHdmiFrlMacRx4PixelClkValue / 100) <= _HW_HDMI_VIDEO_PLL_CLK_LIMIT)
#endif
            {
                // Set Htotal use dsc_htt ... 420 w/ 2x clk
                ScalerSetBit(P69_FC_DSC_HTT_0, ~_BIT7, _BIT7);
            }
            else
            {
                // Set Htotal use DPF_gen ... 420 w/ 1x clk
                ScalerSetBit(P69_FC_DSC_HTT_0, ~_BIT7, 0x00);
            }

            // Delay * 2 due to DPF clock is half.
            usFifoOffset = usFifoOffset * 2;
            ulHdmiFrlMacVstoVsDelay = ulHdmiFrlMacVstoVsDelay * 2;
        }
        else
        {
            // Set Htotal use DPF_gen
            ScalerSetBit(P69_FC_DSC_HTT_0, ~_BIT7, 0x00);
        }
    }

    // Set Vsync width  and VSP is positive
    ScalerSetByte(P69_91_DPF_VSW_M, (BYTE)((g_usHdmiFrlMacRx4Vsync >> 8) & ~_BIT7));
    ScalerSetByte(P69_92_DPF_VSW_L, (BYTE)(g_usHdmiFrlMacRx4Vsync & 0x00FF));

    // Set Vstart
    ScalerSetByte(P69_8D_DPF_VST_M, (BYTE)((g_usHdmiFrlMacRx4Vsync + g_usHdmiFrlMacRx4Vback) >> 8));
    ScalerSetByte(P69_8E_DPF_VST_L, (BYTE)((g_usHdmiFrlMacRx4Vsync + g_usHdmiFrlMacRx4Vback) & 0x00FF));

    // Set Vactive
    ScalerSetByte(P69_8F_DPF_VHT_M, (BYTE)(g_usHdmiFrlMacRx4Vactive >> 8));
    ScalerSetByte(P69_90_DPF_VHT_L, (BYTE)(g_usHdmiFrlMacRx4Vactive & 0x00FF));

    // Set Vtotal
    ScalerSetByte(P69_8B_DPF_VTT_M, (BYTE)(g_usHdmiFrlMacRx4Vtotal >> 8));
    ScalerSetByte(P69_8C_DPF_VTT_L, (BYTE)(g_usHdmiFrlMacRx4Vtotal & 0x00FF));

    // Set HS to HS Delay (for DE_Only Mode)
    ScalerSetByte(P69_79_BS2HS_M, (BYTE)(usFifoOffset >> 8));
    ScalerSetByte(P69_7A_BS2HS_L, (BYTE)(usFifoOffset & 0x00FF));


    /////////////////////
    // Interlace check //
    /////////////////////

    // Interlace ----DSC no interlace mode....
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if((ScalerGetBit(P69_4A_FRL_MEASURE_A, _BIT4) == _BIT4) && (GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE))
#else
    if(ScalerGetBit(P69_4A_FRL_MEASURE_A, _BIT4) == _BIT4)
#endif
    {
        // measure result is filed 2, DPF Vst need minus 1
        if(ScalerGetBit(P69_49_FRL_MEASURE_9, (_BIT4 | _BIT3)) == 0x00)
        {
            // DPF Vst minus 1
            WORD usVstModify = (((WORD)ScalerGetByte(P69_8D_DPF_VST_M) << 8) | ScalerGetByte(P69_8E_DPF_VST_L)) - 1;
            ScalerSetByte(P69_8D_DPF_VST_M, HIBYTE(usVstModify));
            ScalerSetByte(P69_8E_DPF_VST_L, LOBYTE(usVstModify));

            g_usHdmiFrlMacRx4Vsync = g_usHdmiFrlMacRx4Vsync - 1;
        }

        // Set Even Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P69_73_EVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P69_74_EVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P69_75_EVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Odd BStoVSDelay = Even BStoVSDelay + 0.5 line;
        ulHdmiFrlMacVstoVsDelay = ulHdmiFrlMacVstoVsDelay + ((1UL * g_usHdmiFrlMacRx4Htotal / 2) * (ulLinkClkValue / 18) / g_ulHdmiFrlMacRx4PixelClkValue);

        // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P69_76_OVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P69_77_OVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P69_78_OVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Enable DPF Interlace
        ScalerSetBit(P69_93_INTERLACE_MODE_CONFIG, ~_BIT7, _BIT7);

        DebugMessageRx4("FRL Rx4: interlace mode", 0);
    }
    // Progressive
    else
    {
        // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P69_76_OVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P69_77_OVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P69_78_OVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Set Even Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P69_73_EVBLK2VS_H, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 16)));
        ScalerSetByte(P69_74_EVBLK2VS_M, (LOBYTE(ulHdmiFrlMacVstoVsDelay >> 8)));
        ScalerSetByte(P69_75_EVBLK2VS_L, LOBYTE(ulHdmiFrlMacVstoVsDelay));

        // Disable DPF Interlace
        ScalerSetBit(P69_93_INTERLACE_MODE_CONFIG, ~_BIT7, 0x00);
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // DSC mode mux
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        // DSC enable
        ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // DSC BR swap
        ScalerSetBit(P69_A1_DPF_OUTPUT_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
    }
    else
#endif
    {
        ScalerSetBit(P69_71_DPF_CTRL_1, ~(_BIT1 | _BIT0), 0x00);

        // No BR swap
        ScalerSetBit(P69_A1_DPF_OUTPUT_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT7);
    }

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(P69_70_DPF_CTRL_0, ~_BIT6, _BIT6);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
    {
        if(ScalerHdmiFrlMacRx4DisplayFormatCheck(enumMappingPort) == _FALSE)
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
bit ScalerHdmiFrlMacRx4DPFHsyncHstartAdjust(WORD *pusDPFHsync, WORD *pusDPFHstart, WORD usDPFHblank)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    WORD usMinHsyncMeasCnt = 2;
    WORD usHfHbReserve = 2;
    WORD usMinMeasHsync = 0;
    WORD usDPFPixMode = 1;

    if(GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420)
    {
        usMinMeasHsync = ((DWORD)usMinHsyncMeasCnt * g_ulHdmiFrlMacRx4PixelClkValue) / _MEASURE_CLK + 1;  // Real Pixel Clock
    }
    else
    {
        usMinMeasHsync = ((DWORD)usMinHsyncMeasCnt * g_ulHdmiFrlMacRx4PixelClkValue / 2) / _MEASURE_CLK + 1;  // Real Pixel Clock / 2 for 420
    }

    if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
    {
        usDPFPixMode = 4;
    }
    else if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6)
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
bit ScalerHdmiFrlMacRx4StreamClkRegenerate(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
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
    WORD usHdmiFrlMacRx4DPFHtotal = 0;
    WORD usVftTotalNumber = 0;
    bit bVftExtendMode = _FALSE;
    BYTE ucVftFinetuneNumber = 0;
    BYTE ucNCode = 0;
    BYTE ucFCodeMSB = 0;
#endif

#if(_3DDI_FUNCTION == _ON)
    bit bInterlace3ddi = ScalerHdmiFrlMacRx4GetInterlace3ddiAvaible();
#else
    bit bInterlace3ddi = _FALSE;
#endif


    /////////////////////////////
    // Calculate DPLL VCO Freq //
    /////////////////////////////

    // VCO band 10: 270~660M, 11: 310~710M
    // Pixel_clk: 25~600M
    usVCOFreq = (WORD)(g_ulHdmiFrlMacRx4PixelClkValue / 100);
    ucSelVCODivider = 0x01;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // DSC always 4p mode, PLL divide 4
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        usVCOFreq = (usVCOFreq >> 2);
    }
    else
#endif
    {
        // 4P mode
        if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
        {
            usVCOFreq = (usVCOFreq >> 2);
        }
        // 2P mode
        else if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6)
        {
            usVCOFreq = (usVCOFreq >> 1);

            // if 420 and pixel clk > 1400MHz, VCO will set 1x clk, then use 420 IP double pixel mode
            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && ((g_ulHdmiFrlMacRx4PixelClkValue / 200) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT))
            {
                usVCOFreq = (usVCOFreq >> 1);
            }
        }
        // 1P mode
        else
        {
            // if 420 and pixel clk > 700MHz, VCO will set 1x clk, then use 420 IP double pixel mode
            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && ((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_VIDEO_PLL_CLK_LIMIT))
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

    DebugMessageRx4("FRL Rx4: usVCOFreq", usVCOFreq);
    DebugMessageRx4("FRL Rx4: ucSelVCODivider", ucSelVCODivider);


    //////////////
    // Set DPLL //
    //////////////

    // PLL Input Clock select to GDI_CLK, [7:6] = 10
    ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT7 | _BIT6), _BIT6);

    if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_12G)
    {
        usPLLinClkFreq = (BYTE)(120000 / 18 / 32);

        // Div 32
        ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT5);
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_10G)
    {
        usPLLinClkFreq = (BYTE)(100000 / 18 / 26);

        // Div 26
        ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT1));
    }
    else if(ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_8G)
    {
        usPLLinClkFreq = (BYTE)(80000 / 18 / 22);

        // Div 22
        ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT2 | _BIT1));
    }
    else if((ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_4LANES) || (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) == _HDMI_FRL_RATE_6G_3LANES))
    {
        usPLLinClkFreq = (BYTE)(60000 / 18 / 16);

        // Div 16
        ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT4);
    }
    else
    {
        usPLLinClkFreq = (BYTE)(30000 / 18 / 8);

        // Div 8
        ScalerSetBit(P69_C2_PLL_IN_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT6, 0x00);
    }
    else
#endif
    {
        // 420 and pixel clk <= 700MHz, VCO is 2x clk, need set div2 for MAC
        if(((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && ((g_ulHdmiFrlMacRx4PixelClkValue / 100) <= _HW_HDMI_VIDEO_PLL_CLK_LIMIT)) || (bInterlace3ddi == _TRUE))
        {
            ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT6, _BIT6);
        }
        else
        {
            ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT6, 0x00);
        }
    }

    DebugMessageRx4("FRL Rx4: usPLLinClkFreq", usPLLinClkFreq);

    // Set Ncode clamp, max <= 130% and min >= 70%
    // register valude = actual Ncode - 2
    ScalerSetByte(P69_D6_N_F_MAX, (BYTE)(((DWORD)usVCOFreq * 13 / usPLLinClkFreq / 10) - 2));
    ScalerSetByte(P69_D7_N_F_MIN, (BYTE)((((DWORD)usVCOFreq * 7 / usPLLinClkFreq / 10) + 1) - 2));

    ScalerHdmiFrlMacRx4DPLLOffProc(usVCOFreq, usPLLinClkFreq, ucSelVCODivider);

    ScalerHdmiFrlMacRx4DPLLOnProc(usVCOFreq, usPLLinClkFreq);


    ///////////////////////////////
    // DPPLL Tracking Setting //
    ///////////////////////////////

    // Disable line Tracking
    ScalerSetBit(P69_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

    // Disable Virtual FIFO Tracking
    ScalerSetBit(P69_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT7, 0x00);

    // Tracking - Reset Control Block
    ScalerSetBit(P69_DD_TRACKING_0, ~_BIT7, _BIT7);
    ScalerSetBit(P69_DD_TRACKING_0, ~_BIT7, 0x00);

    // Tracking - Enable PI Control
    // ScalerSetBit(P69_DE_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Disable bypass PI
    ScalerSetBit(P69_DC_SDM_0, ~_BIT7, 0x00);

    /////////////////////////////
    // Tracking - Set P/I Code //
    /////////////////////////////
    // small timing need use I code for accurate pixel clock tracking
    if(g_usHdmiFrlMacRx4Hactive <= 1920)
    {
        // P Gain Clamp = 0x00 40 00 00
        // P Code = 0x00 04 FF FF
        ScalerHdmiFrlMacRx4SetPGainClampValue(0x00, 0x40, 0x00);
        ScalerSetByte(P69_E3_MN_PI_CODE_2, 0x04);

        // I Gain Clamp = 0x00 04 00 00
        // I Code = 0x08
        ScalerSetByte(P69_E7_MN_PI_CODE_6, 0x04);
        ScalerSetByte(P69_E1_MN_PI_CODE_0, 0x08);
    }
    else
    {
        // P Gain Clamp = 0x00 20 00 00
        // P Code = 0x00 02 FF FF(default)
        ScalerHdmiFrlMacRx4SetPGainClampValue(0x00, 0x20, 0x00);
        ScalerSetByte(P69_E3_MN_PI_CODE_2, 0x02);

        // I Gain Clamp = 0x00 02 00 00
        // I Code = 0x04
        ScalerSetByte(P69_E7_MN_PI_CODE_6, 0x02);
        ScalerSetByte(P69_E1_MN_PI_CODE_0, 0x04);
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
        ScalerSetByte(P69_CC_MN_TRACKING_DIVS, (ucSelVCODivider / 4));
    }
    else
    {
        // CK_MN_CLK = VCO div8
        ScalerSetByte(P69_CC_MN_TRACKING_DIVS, 0x02);
    }

    ///////////////////////////
    // Line Tracking Setting //
    ///////////////////////////

    // small timing set tracking per line
    if(g_usHdmiFrlMacRx4Hactive <= 1920)
    {
        // How many lines tracking one time
        ScalerSetByte(P69_F1_VS_TRACK1, 0x01);
    }
    else
    {
        // How many lines tracking one time
        ScalerSetByte(P69_F1_VS_TRACK1, 0x07);
    }

    // Tracking - half HS delay cnt = Htotal/2 * GDI_CLK / Streamclk
    usHalfBSDelayCnt = (WORD)(((DWORD)g_usHdmiFrlMacRx4Htotal) * 270 / (g_ulHdmiFrlMacRx4PixelClkValue / 100) / 2);
    ScalerSetBit(P69_F4_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usHalfBSDelayCnt >> 8));
    ScalerSetByte(P69_F5_HS_TRACKING_NEW_MODE2, (BYTE)(usHalfBSDelayCnt & 0x00FF));

    // Set manual vbid(made by HW), use BE as hsync
    ScalerSetBit(P69_F4_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    // ScalerSetBit(P69_F4_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), (_BIT5));

    // Set Tracking Mode
    // Use fast lock mode
    ScalerSetBit(P69_EF_VS_TRACK_MODE, ~(_BIT3 | _BIT2), _BIT3);

    // DPF enable
    ScalerSetBit(P69_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), _BIT7);

    // Enable Tracking
    ScalerSetBit(P69_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);

    // Tracking - Enable PI Control
    ScalerSetBit(P69_DE_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Find Accurate N.F code
    if(g_usHdmiFrlMacRx4Hactive <= 1920)
    {
        // Wait 2 frames
        ScalerTimerDelayXms((2000 / g_usHdmiFrlMacRx4FrameRate) + 3);

        // Disable Tracking
        ScalerSetBit(P69_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

        // Set Ncode limitation
        ScalerSetByte(P69_D6_N_F_MAX, ScalerGetByte(P69_D8_N_F_REPORT0) + 2);
        ScalerSetByte(P69_D7_N_F_MIN, ScalerGetByte(P69_D8_N_F_REPORT0) - 2);

        // Reload N.F code
        ScalerSetByte(P69_D2_N_F_CODE_1, ScalerGetByte(P69_D8_N_F_REPORT0));
        ScalerSetByte(P69_D3_N_F_CODE_2, ScalerGetByte(P69_D9_N_F_REPORT1));
        ScalerSetBit(P69_D1_N_F_CODE_0, ~_BIT0, _BIT0);

        // Wait for DPLL Stable (300us)
        DELAY_XUS(300);

        // P Gain Clamp = 0x00 20 00 00
        // P Code = 0x00 02 FF FF
        ScalerHdmiFrlMacRx4SetPGainClampValue(0x00, 0x20, 0x00);
        ScalerSetByte(P69_E3_MN_PI_CODE_2, 0x02);

        // I Gain Clamp = 0x00 02 00 00
        // I Code = 0x04
        ScalerSetByte(P69_E7_MN_PI_CODE_6, 0x02);
        ScalerSetByte(P69_E1_MN_PI_CODE_0, 0x04);

        // Delay 300us
        DELAY_XUS(300);

        // How many lines tracking one time
        ScalerSetByte(P69_F1_VS_TRACK1, 0x3F);

        // Enable Tracking
        ScalerSetBit(P69_EE_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);
    }

    // Check Tracking Stable
    usTrkingLoopMax = 20;
    usTrkingLoopCnt = 0;

    do
    {
        if(GET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT() == _TRUE)
        {
            DebugMessageRx4("FRL Rx4: Tracking Fail -- Source set FRL_Rate!! ------------", 0);
            return _FALSE;
        }

        usTrkingLoopCnt++;

        // Clear VS/HS non-lock flag
        ScalerSetBit(P69_EE_VS_TRACK_EN, ~_BIT0, _BIT0);

        // Clear Max Phase Error
        ScalerSetByte(P69_F3_VS_TRACK3, 0xFF);

        ScalerTimerDelayXms((1000 / g_usHdmiFrlMacRx4FrameRate) + 3); // need wait Vsync

        ucCurrentPhaseError = ScalerGetByte(P69_F3_VS_TRACK3);

        // wait tracking stable
        if((abs(ucLastPhaseError - ucCurrentPhaseError) < 10) && (usTrkingLoopCnt >= 3))
        {
            if(ScalerHdmiFrlMacRx4DpfFifoCheck(_WAIT) == _TRUE)
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
        DebugMessageRx4("FRL Rx4: Tracking Fail!!", ScalerGetByte(P69_F3_VS_TRACK3));
        DebugMessageRx4("FRL Rx4: DPF FIFO", ScalerGetByte(P69_AF_DPF_FIFO_CTRL));

        return _FALSE;
    }

#else // Else of #if(_HDMI_FRL_DPF_TRACKING_METHOD == _HDMI_FRL_LINE_TRACKING)

    ///////////////////////////////
    // Virtual FIFO Tracking     //
    ///////////////////////////////

    // P Gain Clamp = 0x00 40 00 00
    ScalerHdmiFrlMacRx4SetPGainClampValue(0x00, 0x40, 0x00);

    // I Gain Clamp = 0x00 04 00 00
    ScalerSetByte(P69_E7_MN_PI_CODE_6, 0x04);

    // Set First Level P/I code
    // I Code = 0x04
    // P Code = 0x00 02 FF FF
    ScalerSetByte(P69_A8_VIRTUAL_FIFO_TRACKING_8, 0x04);
    ScalerSetByte(P69_A9_VIRTUAL_FIFO_TRACKING_9, 0x00);
    ScalerSetByte(P69_AA_VIRTUAL_FIFO_TRACKING_10, 0x04);

    // Set Second Level P/I code
    // I Code = 0x08
    // P Code = 0x00 04 FF FF
    ScalerSetByte(P69_AB_VIRTUAL_FIFO_TRACKING_11, 0x08);
    ScalerSetByte(P69_AC_VIRTUAL_FIFO_TRACKING_12, 0x00);
    ScalerSetByte(P69_AD_VIRTUAL_FIFO_TRACKING_13, 0x08);

    // Set Third Level P/I code
    // I Code = 0x10
    // P Code = 0x00 08 FF FF
    ScalerSetByte(P69_AE_VIRTUAL_FIFO_TRACKING_14, 0x10);
    ScalerSetByte(P69_B3_VIRTUAL_FIFO_TRACKING_15, 0x00);
    ScalerSetByte(P69_B4_VIRTUAL_FIFO_TRACKING_16, 0x10);

    // Set Forth Level P/I code
    // I Code = 0x20
    // P Code = 0x00 10 FF FF
    ScalerSetByte(P69_B5_VIRTUAL_FIFO_TRACKING_17, 0x20);
    ScalerSetByte(P69_B6_VIRTUAL_FIFO_TRACKING_18, 0x00);
    ScalerSetByte(P69_B7_VIRTUAL_FIFO_TRACKING_19, 0x20);

    // Delay 300us
    DELAY_XUS(300);

    //////////////////////////////
    // Tracking - Set CK_MN_CLK //
    //////////////////////////////
    // set CK_MN_CLK = VCOFreq / 2 / CK_MN_DIVS < 250M
    if(ucSelVCODivider > 8)
    {
        // CK_MN_CLK = Pixel_CLK
        ScalerSetByte(P69_CC_MN_TRACKING_DIVS, (ucSelVCODivider / 4));
    }
    else
    {
        // CK_MN_CLK = VCO div8
        ScalerSetByte(P69_CC_MN_TRACKING_DIVS, 0x02);
    }


    ///////////////////////////////////
    // Virtual FIFO Tracking Setting //
    ///////////////////////////////////

    // Set Virtual FIFO Size
    ScalerSetByte(P69_FE_VIRTUAL_FIFO_TRACKING_24, 0x0C);
    ScalerSetByte(P69_FF_VIRTUAL_FIFO_TRACKING_25, 0x00);

    // Reset FIFO water level and R/W pointer
    /*if((GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422))
    {
        ScalerSetBit(P69_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT6, _BIT6);
    }
    else*/
    {
        ScalerSetBit(P69_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT6, 0x00);
    }

    // Initial water level = 368*2*4 / 2 = 1472
    ScalerSetBit(P69_96_VIRTUAL_FIFO_TRACKING_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetByte(P69_97_VIRTUAL_FIFO_TRACKING_1, 0xC0);

    //////////////////////////////////
    // Full = 2900, Empty = 0
    // Boundary = 900, each level is 225.
    // P/I code Level 4 for 0~225 and 2676~2900
    // P/I code Level 3 for 226~450 and 2451~2675
    // P/I code Level 2 for 451~675 and 2226~2450
    // P/I code Level 1 for 676~900 and 2000~2225
    // No P/I code for 900~2000

    // Set Start Tracking boundary = 900 = 0x384
    ScalerSetBit(P69_98_VIRTUAL_FIFO_TRACKING_2, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetByte(P69_99_VIRTUAL_FIFO_TRACKING_3, 0x84);

    // Get DPF Htotal
    usHdmiFrlMacRx4DPFHtotal = ((((WORD)ScalerGetByte(P69_80_DPF_HTT_M)) << 8) | (ScalerGetByte(P69_81_DPF_HTT_L))) * ((ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0) ? 4 : ((ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6) ? 2 : 1));
    DebugMessageRx4("VFT: usHdmiFrlMacRx4DPFHtotal", usHdmiFrlMacRx4DPFHtotal);

    // Need extend or reduce read pointer, when g_usHdmiFrlMacRx4Htotal and usHdmiFrlMacRx4DPFHtotal is different
    if(g_usHdmiFrlMacRx4Htotal >= usHdmiFrlMacRx4DPFHtotal)
    {
        DebugMessageRx4("VFT: reduce", g_usHdmiFrlMacRx4Htotal);

        // DPF reduce mode
        ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, 0x00);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
        {
            // Modify interval
            ScalerSetByte(P69_B9_VIRTUAL_FIFO_TRACKING_21, (BYTE)(((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) + 1) & 0x00FF));

            // Modify number
            ScalerSetByte(P69_BA_VIRTUAL_FIFO_TRACKING_22, (BYTE)((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) & 0x00FF));

            // Modify total
            ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) >> 8));
            ScalerSetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) & 0x00FF));
        }
        else
#endif
        {
            // Modify interval
            ScalerSetByte(P69_B9_VIRTUAL_FIFO_TRACKING_21, (BYTE)((((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) + 1) & 0x00FF));

            // Modify number
            ScalerSetByte(P69_BA_VIRTUAL_FIFO_TRACKING_22, (BYTE)(((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) & 0x00FF));

            // Modify total
            ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)(((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) >> 8));
            ScalerSetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)(((g_usHdmiFrlMacRx4Htotal - usHdmiFrlMacRx4DPFHtotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) & 0x00FF));
        }
    }
    else
    {
        DebugMessageRx4("VFT: extend", g_usHdmiFrlMacRx4Htotal);

        // DPF extend mode
        ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, _BIT7);

        // Modify interval
        ScalerSetByte(P69_B9_VIRTUAL_FIFO_TRACKING_21, 0x02);

        // Modify number shall set 1 to prevent read pointer is negative
        ScalerSetByte(P69_BA_VIRTUAL_FIFO_TRACKING_22, 0x01);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
        {
            // Modify total
            ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)((usHdmiFrlMacRx4DPFHtotal - g_usHdmiFrlMacRx4Htotal) >> 8));
            ScalerSetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)((usHdmiFrlMacRx4DPFHtotal - g_usHdmiFrlMacRx4Htotal) & 0x00FF));
        }
        else
#endif
        {
            // Modify total
            ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), (BYTE)(((usHdmiFrlMacRx4DPFHtotal - g_usHdmiFrlMacRx4Htotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) >> 8));
            ScalerSetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23, (BYTE)(((usHdmiFrlMacRx4DPFHtotal - g_usHdmiFrlMacRx4Htotal) * ((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) ? GET_COLOR_DEPTH(enumMappingPort) : 8) / 8) & 0x00FF));
        }
    }

    // DPF enable
    ScalerSetBit(P69_70_DPF_CTRL_0, ~(_BIT7 | _BIT6), _BIT7);

    // Enable Virtual FIFO tracking
    ScalerSetBit(P69_96_VIRTUAL_FIFO_TRACKING_0, ~_BIT7, _BIT7);

    // Tracking - Enable PI Control
    ScalerSetBit(P69_DE_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Check Virtual FIFO Tracking Stable
    usTrkingLoopMax = 100;
    usTrkingLoopCnt = 0;
    usVftTotalNumber = (WORD)(ScalerGetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, (_BIT1 | _BIT0)) << 8) | ScalerGetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23);
    bVftExtendMode = (ScalerGetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, _BIT7)) >> 7;
    ucVftFinetuneNumber = 0;

    do
    {
        if(GET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT() == _TRUE)
        {
            DebugMessageRx4("FRL Rx4: Tracking Fail -- Source set FRL_Rate!! ------------", 0);
            return _FALSE;
        }

        usTrkingLoopCnt++;

        // clear Virtual FIFO full/empty flag
        ScalerSetBit(P69_98_VIRTUAL_FIFO_TRACKING_2, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

        // Record N.F code
        ucNCode = ScalerGetByte(P69_D8_N_F_REPORT0);
        ucFCodeMSB = ScalerGetByte(P69_D9_N_F_REPORT1);

        // wait 1 frame
        ScalerTimerDelayXms((1000 / g_usHdmiFrlMacRx4FrameRate) + 3);

        // Virtual FIFO no full/empty and DPF FIFO no overflow/underflow
        if((usTrkingLoopCnt >= 5) && (ScalerGetBit(P69_98_VIRTUAL_FIFO_TRACKING_2, (_BIT7 | _BIT5)) == 0x00) && (ScalerHdmiFrlMacRx4DpfFifoCheck(_WAIT) == _TRUE))
        {
            // N.F Code is stable
            if((ScalerGetByte(P69_D8_N_F_REPORT0) == ucNCode) && (ScalerGetByte(P69_D9_N_F_REPORT1) == ucFCodeMSB))
            {
                break;
            }
        }

        // fine tune reduce/extend
        if((usTrkingLoopCnt >= 80) && (GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422))
        {
            if(usVftTotalNumber != 0)
            {
                ScalerSetByte(P69_B9_VIRTUAL_FIFO_TRACKING_21, 0x01);
                ScalerSetByte(P69_BA_VIRTUAL_FIFO_TRACKING_22, 0x00);

                ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23, 0x00);
                usVftTotalNumber = 0;
                bVftExtendMode = _FALSE;
                DebugMessageRx4("!!!!!VFT set reduce 0", bVftExtendMode);
            }
            else
            {
                if((bVftExtendMode == _FALSE) && ((usTrkingLoopCnt - ucVftFinetuneNumber) >= 5))
                {
                    ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, 0x00);
                    ScalerSetByte(P69_B9_VIRTUAL_FIFO_TRACKING_21, ScalerGetByte(P69_B9_VIRTUAL_FIFO_TRACKING_21) + 1);
                    ScalerSetByte(P69_BA_VIRTUAL_FIFO_TRACKING_22, ScalerGetByte(P69_BA_VIRTUAL_FIFO_TRACKING_22) + 1);
                    ScalerSetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23, ScalerGetByte(P69_BB_VIRTUAL_FIFO_TRACKING_23) + 1);
                    bVftExtendMode = _TRUE;
                    ucVftFinetuneNumber = usTrkingLoopCnt;
                    DebugMessageRx4("!!!!!VFT set reduce +1", ucVftFinetuneNumber);
                }
                else if((usTrkingLoopCnt - ucVftFinetuneNumber) >= 5)
                {
                    ScalerSetBit(P69_B8_VIRTUAL_FIFO_TRACKING_20, ~_BIT7, _BIT7);
                    bVftExtendMode = _FALSE;
                    ucVftFinetuneNumber = usTrkingLoopCnt;
                    DebugMessageRx4("!!!!!VFT set extend +1", ucVftFinetuneNumber);
                }
            }
        }
    }while(usTrkingLoopCnt < usTrkingLoopMax);

    if(usTrkingLoopCnt == usTrkingLoopMax)
    {
        DebugMessageRx4("FRL Rx4: Virtual fifo Tracking Fail!!", ScalerGetByte(P69_98_VIRTUAL_FIFO_TRACKING_2));
        DebugMessageRx4("FRL Rx4: DPF FIFO", ScalerGetByte(P69_AF_DPF_FIFO_CTRL));
        return _FALSE;
    }
#endif

    // Clear overflow and underflow and protect empty and full flag
    ScalerSetBit(P69_AF_DPF_FIFO_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // DPF output enable
    SET_HDMI_FRL_RX4_DPF_RGB_CLK_OUTPUT_ENABLE();

    // DPF Watch Dog enable
    ScalerHdmiFrlMacRx4WatchDog(_HDMI_FRL_DPF_FIFO_WD, _ENABLE);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        g_ulHdmiFrlMacRx4DSCClkValue = (((DWORD)(ScalerGetByte(P69_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P69_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P69_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq / ucSelVCODivider;
        DebugMessageRx4("FRL Rx4: DSC clk", g_ulHdmiFrlMacRx4DSCClkValue);
    }
    else
#endif
    {
        // Calculate PLL VCO Clock, Unit kHz
        if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
        {
            g_ulHdmiFrlMacRx4PixelClkValue = (((DWORD)(ScalerGetByte(P69_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P69_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P69_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq * 4 / ucSelVCODivider / 10;
        }
        else if(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6)
        {
            g_ulHdmiFrlMacRx4PixelClkValue = (((DWORD)(ScalerGetByte(P69_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P69_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P69_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq * 2 / ucSelVCODivider / 10;
        }
        else
        {
            g_ulHdmiFrlMacRx4PixelClkValue = (((DWORD)(ScalerGetByte(P69_D8_N_F_REPORT0) + 2) * 1000) + (((DWORD)((ScalerGetBit(P69_D9_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | (ScalerGetByte(P69_DA_N_F_REPORT2))) * 1000) >> 12)) * usPLLinClkFreq / ucSelVCODivider / 10;
        }

        // if 420 format and disable div2, pixel clk = VCO clk * 2
        if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) && (ScalerGetBit(P69_D0_PLL_OUT_CONTROL, _BIT6) == 0))
        {
            g_ulHdmiFrlMacRx4PixelClkValue = g_ulHdmiFrlMacRx4PixelClkValue * 2;
        }

        if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420)
        {
            ScalerTmdsMacRxSetInputPixel(enumMappingPort, g_ulHdmiFrlMacRx4PixelClkValue / 200); // Unit:0.1MHz
        }
        else
        {
            ScalerTmdsMacRxSetInputPixel(enumMappingPort, g_ulHdmiFrlMacRx4PixelClkValue / 100); // Unit:0.1MHz
        }
    }

    // Set Nactive Htotal for EDID Table Analysis
    SET_HDMI_FRL_MAC_RX4_NATIVE_HTOTAL(g_usHdmiFrlMacRx4Htotal);

    // Niether 420(only 2p mode) nor DSC(fixed 4p mode), after tracking stable, pixel clk and pixel mode is mismatched
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420) && (GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE) &&
       (((ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00) && ((g_ulHdmiFrlMacRx4PixelClkValue / 100) <= _HW_HDMI_FRL_DPF_4P_MODE_FREQ)) ||
        ((ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6) && ((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ))))
#else
    if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR420) &&
       (((ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00) && ((g_ulHdmiFrlMacRx4PixelClkValue / 100) <= _HW_HDMI_FRL_DPF_4P_MODE_FREQ)) ||
        ((ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == _BIT6) && ((g_ulHdmiFrlMacRx4PixelClkValue / 100) > _HW_HDMI_FRL_DPF_4P_MODE_FREQ))))
#endif
    {
        SET_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH();

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Deep Color PLL On COntrol.
// Input Value  : ucNcode
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4DPLLOnProc(WORD usVCOFreq, WORD usPLLinClkFreq)
{
    WORD usNFCodeFPart = 0;
    BYTE ucNcode = 0;

    // Power On DPLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, 0x00);
    DELAY_XUS(200);

    // Set VCO/4 Enable
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, _BIT7);

    // Set N.F Code
    ucNcode = (BYTE)(usVCOFreq / usPLLinClkFreq);
    usNFCodeFPart = (usVCOFreq % usPLLinClkFreq);

    ScalerSetByte(P69_D2_N_F_CODE_1, (ucNcode - 2));
    ScalerSetBit(P69_D3_N_F_CODE_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usNFCodeFPart * 16 / usPLLinClkFreq));
    ScalerSetByte(P69_D4_N_F_CODE_3, (BYTE)(((usNFCodeFPart * 16) % usPLLinClkFreq) * 256 / usPLLinClkFreq));
    ScalerSetByte(P69_D5_N_F_CODE_4, (BYTE)((((usNFCodeFPart * 16) % usPLLinClkFreq) * 256 % usPLLinClkFreq) * 256 / usPLLinClkFreq));

    // Set N.F Double Buffer
    ScalerSetBit(P69_D1_N_F_CODE_0, ~_BIT0, _BIT0);

    // Wait for DPLL Stable (300us)
    DELAY_XUS(300);

    // enable DPF CLK
    ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Set P Gain
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetPGainClampValue (BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1)
{
    // 1st tracking : 0x0 10 00 00
    // 2nd tracking : 0x0 01 00 00
    ScalerSetByte(P69_EA_MN_PI_CODE_9, ucPGainB3);
    ScalerSetByte(P69_EB_MN_PI_CODE_A, ucPGainB2);
    ScalerSetByte(P69_EC_MN_PI_CODE_B, ucPGainB1);
    ScalerSetByte(P69_ED_MN_PI_CODE_C, 0x00);
}

//--------------------------------------------------
// Description  : DPF Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4DpfFifoCheck(bit bWait)
{
    BYTE ucLoop = 0;

    if(bWait == _WAIT)
    {
        // Clear overflow and underflow and protect empty and full flag
        ScalerSetBit(P69_AF_DPF_FIFO_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

        // Delay 2 frame
        ScalerTimerDelayXms(2 * ((1000 / g_usHdmiFrlMacRx4FrameRate) + 3));

        while(ucLoop < 6)
        {
            ScalerTimerDelayXms(10);

            if(ScalerGetBit(P69_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4)) != 0x00)
            {
                return _FALSE;
            }

            ucLoop++;
        }
    }
    else
    {
        if(ScalerGetBit(P69_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4)) != 0x00)
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
bit ScalerHdmiFrlMacRx4StableDetect(EnumSourceType enumSourceType)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    enumSourceType = enumSourceType;

    // CLR SCL/SDA Toggle Flag
    ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);

    // Check Hpd Event happened
    if(GET_TMDS_MAC_RX4_HPD_RESET_TO_SEARCH_EVENT() == _TRUE)
    {
        DebugMessageRx4("HPD Toggle Event Occur at Frl Stable Detect!!", 0x00);
        CLR_TMDS_MAC_RX4_HPD_RESET_TO_SEARCH_EVENT();
        return _FALSE;
    }

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING() == _TRUE)
    {
        // Keep return false during Active Type HPD is toggling
        DebugMessageRx4("Active HPD Toggle Event is Ongoing at Frl Stable Detect!!", 0x00);
        return _FALSE;
    }
#endif

    // Check DPF FIFO
    if(ScalerHdmiFrlMacRx4DpfFifoCheck(_NOT_WAIT) == _FALSE)
    {
        // CDR unstable, need Link Training
        if((ScalerHdmiFrlMacRx4CheckCdrStable(g_usHdmiFrlMacRx4OffMeasureCount) == _FALSE) && (GET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT() == _FALSE))
        {
            // Set SCDC FLT_update
            ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT5, _BIT5);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX4_HDCP2_SET_REAUTH);
#endif
            // clear set phy
            CLR_HDMI_FRL_MAC_RX4_PHY_SET();

            DebugMessageRx4("FRL Rx4: CDR Unstable!!", enumSourceType);
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

            DebugMessageRx4("FRL Rx4: DPF FIFO Under/Overflow!! ========================", enumSourceType);
        }

        // Turn off DPF output
        SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

        return _FALSE;
    }

    // FRL_Rate Changed
    if(GET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT() == _TRUE)
    {
        DebugMessageRx4("FRL Rx4: FRL_Rate Changed!!", enumSourceType);

        // Turn off DPF output
        SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

        return _FALSE;
    }

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    if((GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON) && (GET_ADVANCED_HDR10_INITIAL_READY() == _TRUE) && (GET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING() == _FALSE))
    {
        bit bAdvancedHDR10VSIFReceive = GET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED();
        bit bAdvancedHDR10EMPReceive = _FALSE;

        if(bAdvancedHDR10VSIFReceive == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED();
        }
        else
        {
            // Clr HDR10+ data strucr if no received
            CLR_ADVANCED_HDR10_INFO_DATA();
            CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
        }

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
        bAdvancedHDR10EMPReceive = GET_HDMI_FRL_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED();
        if(bAdvancedHDR10EMPReceive == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED();
        }
        else
        {
            CLR_ADVANCED_HDR10_DHDR_DATA();
        }
#endif

        if((bAdvancedHDR10VSIFReceive == _TRUE) || (bAdvancedHDR10EMPReceive == _TRUE))
        {
            // when continually receive, TimerEvent to detect HDR10+ (only VSIF/EMP -> No VSIF/EMP transition)
            ScalerTimerActiveTimerEvent(GET_ADVANCED_HDR10_METADATA_DETECT_TIME(), _SCALER_TIMER_EVENT_RX4_HDMI_FRL_ADVANCED_HDR10_DETECT);

            SET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING();
        }
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((GET_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING() == _FALSE) && (ScalerDMGetMetadataSupport(enumMappingPort) == _TRUE))
    {
        if((GET_HDMI_FRL_MAC_RX4_DM_EMP_RECEIVED() == _TRUE) || (GET_HDMI_FRL_MAC_RX4_DM_VSIF_RECEIVED() == _TRUE))
        {
            CLR_HDMI_FRL_MAC_RX4_DM_EMP_RECEIVED();
            CLR_HDMI_FRL_MAC_RX4_DM_VSIF_RECEIVED();

            // when continually receive, TimerEvent to detect DM (only VSIF/EMP -> No VSIF/EMP transition)
            ScalerTimerActiveTimerEvent(100, _SCALER_TIMER_EVENT_RX4_HDMI_FRL_DM_DETECT);

            SET_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING();
        }
        else
        {
            // case for DM packet -> no packet
        }
    }
#endif
#endif

    // To do Packet detection
    if(GET_HDMI_FRL_MAC_RX4_PACKET_DETECTING() == _FALSE)
    {
        // HDMI Packet Detected
        ScalerHdmiFrlMacRx4PacketDetect(_NOT_WAIT);

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
        // PRIORITY TOP to check 3D Video format if HDMI or HF VSIF from 1->0
        if((GET_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED() == _FALSE) && (GET_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED() == _FALSE))
        {
            CLR_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
        }

        if(GET_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED() == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED();
        }
#endif

        if(GET_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED() == _TRUE)
        {
            CLR_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED();
        }
        else
        {
#if(_HDMI21_ALLM_SUPPORT == _ON)
            CLR_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();
#endif
        }


        if(GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
        {
            if(ScalerHdmiFrlMacRx4ColorInfoChanged() == _TRUE)
            {
                DebugMessageRx4("FRL Rx4: Color Info Changed", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if(ScalerHdmiFrlMacRx4AviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx4("FRL Rx4: Pixel Repetition Info Changed", enumSourceType);

                    // Turn off DPF output
                    SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }
        else
        {
            if(GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_RGB)
            {
                DebugMessageRx4("FRL Rx4: AVI Info Frame Not Received and not RGB", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }

#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
            if(GET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort) != _RGB_QUANTIZATION_RESERVED)
            {
                DebugMessageRx4("FRL Rx4: No Quantization Range Specified", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if(GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx4("FRL Rx4: Pixel Repetition Not Received and not Pixel repetition 0", enumSourceType);

                    // Turn off DPF output
                    SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            if((ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_41_PORT_PAGE78_HDMI_VWDSR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT0) && (ScalerGetBit(P78_CC_HDMI_GPVS, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT0))
            {
                DebugMessageRx4("FRL Rx4: HDMI AVI info frame has changed", enumSourceType);

                // Turn off DPF output
                SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }
        }

        if(GET_HDMI_FRL_MAC_RX4_GCP_RECEIVED() == _TRUE)
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) && (ScalerHdmiFrlMacRx4GetColorDepth() != GET_COLOR_DEPTH(enumMappingPort)))
                {
                    DebugMessageRx4("FRL Rx4: Color Depth Has Changed", GET_COLOR_DEPTH(enumMappingPort));

                    // Turn off DPF output
                    SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }
        else
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
#endif
            {
                if((GET_COLOR_SPACE(enumMappingPort) != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH(enumMappingPort) != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx4("FRL Rx4: HDMI GCP PACKET Not Received and not 8 bit", enumSourceType);

                    // Turn off DPF output
                    SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                    return _FALSE;
                }
            }
        }

#if(_HDMI_FORCE_FREESYNC_SUPPORT == _OFF)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
        if(GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED() == _TRUE)
        {
            if((bit)GET_HDMI_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) != ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort))
            {
                DebugMessageRx4("HDMI Freesync Status Change", ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort));
                return _FALSE;
            }
        }
        else
        {
            if(ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort) == _TRUE)
            {
                DebugMessageRx4("HDMI Freesync Status Change", ScalerTmdsMacRxGetFreesyncEnableFlag(enumMappingPort));
                return _FALSE;
            }
        }
#endif
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED() != ScalerTmdsMacRxGetFreesyncReplayProc(enumMappingPort))
        {
            DebugMessageRx4("AMD SPD Infoframe Status Change", GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED());
            return _FALSE;
        }
#endif
    }

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
    if(GET_TMDS_MAC_RX4_EMP_DETECTING() == _FALSE)
    {
        ScalerHdmiFrlMacRx4EmpPacketDetect(_NOT_WAIT);

#if(_HDMI_FORCE_VRR_SUPPORT == _OFF)
#if(_HDMI21_VRR_SUPPORT == _ON)
        if((GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG() == _TRUE) && (GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE))
        {
            DebugMessageRx4("FRL Rx4: VTEM from NA(or MLDS) to received", 0x00);
            CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();

            return _FALSE;
        }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
        {
            // FVA factor change
            if(GET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR() != (ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_FVA_FACTOR_M1) + 1))
            {
                // Turn off DPF output
                SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

                return _FALSE;
            }
        }
#endif
#endif
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    // CVTEM Changed
    if(ScalerDscDecoderGetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX4)) == _ENABLE)
    {
        ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX4), _DISABLE);

        DebugMessageRx4("FRL Rx4: DSC Status Change", 0);

        // Turn off DPF output
        SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

        return _FALSE;
    }

    if(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4) != _DSC_MAC_NONE)
    {
        BYTE ucDscMac = ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4);

        if(ScalerHdmiFrlMacRxGetCvtemReceived(enumMappingPort) == _FALSE)
        {
            DebugMessageRx4("FRL Rx4: Video Stream Compression Disable", 0);

            // Turn off DPF output
            SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

            return _FALSE;
        }

        if(ScalerDscDecoderPpsChangeCheck(ucDscMac) == _FALSE)
        {
            DebugMessageRx4("7. DSC PPS Change", 0);

            // Turn off DPF output
            SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

            return _FALSE;
        }

        if(ScalerDscDecoderFifoCheck(ucDscMac, _DSC_FIFO_POLLING_CHECK) == _FALSE)
        {
            DebugMessageRx4("FRL Rx4: DSC Fifo Under/Overflow", 0);

            // Turn off DPF output
            SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

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
bit ScalerHdmiFrlMacRx4CheckCdrStable(WORD usClkCount)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Check Current Measured Freq. is the same as previously locked
    if(abs(usClkCount - ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE0)) > (usClkCount >> 6))
    {
        DebugMessageRx4("FRL Rx4: L0 CDR Unstable", ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE0));

        return _FALSE;
    }

    if(abs(usClkCount - ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE1)) > (usClkCount >> 6))
    {
        DebugMessageRx4("FRL Rx4: L1 CDR Unstable", ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE1));

        return _FALSE;
    }

    if(abs(usClkCount - ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE2)) > (usClkCount >> 6))
    {
        DebugMessageRx4("FRL Rx4: L2 CDR Unstable", ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE2));

        return _FALSE;
    }

    if((ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) >= _HDMI_FRL_RATE_6G_4LANES) && (abs(usClkCount - ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE3)) > (usClkCount >> 6)))
    {
        DebugMessageRx4("FRL Rx4: L3 CDR Unstable", ScalerHdmiFrlMacRx4OffMeasureClk(_HDMI_FRL_LANE3));

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerHdmiFrlMacRx4OffMeasureClk(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;

    // Enable Rx_EN (Lane3)?????????????
    // ScalerSetBit(P7C_1A_CMU_00, ~_BIT7, _BIT7);

    // Set div36
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, ~_BIT6, _BIT6);

    // Select reference clk to Xtal Clk and measure clk
    ScalerTmdsPhyRxCdrMeasureClkSelect(ScalerTmdsMacRxRxDxMapping(_RX4), ucMeasureClk);

    // Start Measure
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US();

        if((ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_28_PORT_PAGE78_HDMI_NTX1024TR0, 2, &pData[0], _AUTOINC);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : Clear All Received Status of Packet
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ResetAllPacketReceiveStatus(void)
{
    // Clear AVI infoframe & GCP packet Detection Flag
    ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Clear RSV 0~3 detection Flag
    ScalerSetByte(P78_CC_HDMI_GPVS, (_BIT6 | _BIT5));
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Clear VSIF(RSV7) & RSV 4 detection Flag
    ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // Clear VTEM flag
    ScalerSetBit(P1E_50_EMP_HDMI, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Clear CVTEM flag
    ScalerSetBit(P1E_52_EMP_DSC, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Clear DHDREM flag
    ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Clear VS EMP flag
    ScalerSetBit(P1E_51_EMP_VS, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
}

//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PacketDetect(bit bWait)
{
#if(_DM_FUNCTION == _ON)
    EnumInputPort enumDx = ScalerTmdsMacRxRxDxMapping(_RX4);
#endif

    if(bWait == _WAIT)
    {
        BYTE ucRSVColorDepth = 0x00;

        // Polling 3 frame for detect AVI and GCP
        if(ScalerTimerPollingFlagProc(130, P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
            {
                SET_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

                SET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();

                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P78_CC_HDMI_GPVS, 0x01);

                DebugMessageRx4("FRL Rx4: AVI and GCP", 0);
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT0)
            {
                SET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();

                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P78_CC_HDMI_GPVS, 0x01);

                // Polling more time to wait GCP when AVI IF has been received.
                if(ScalerTimerPollingFlagProc(180, P78_D5_HDMI_RSV64_IE, _BIT1, _TRUE) == _TRUE)
                {
                    SET_HDMI_FRL_MAC_RX4_GCP_RECEIVED();
                    DebugMessageRx4("FRL Rx4: AVI and GCP retry", 0);
                }
                else
                {
                    CLR_HDMI_FRL_MAC_RX4_GCP_RECEIVED();
                    DebugMessageRx4("FRL Rx4: Only AVI", 0);
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT1)
            {
                SET_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

                // Polling more time to wait AVI IF when GCP has been received.
                if(ScalerTimerPollingFlagProc(180, P78_D5_HDMI_RSV64_IE, _BIT0, _TRUE) == _TRUE)
                {
                    SET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();

                    // Clear AVI Info Frame Variation flag
                    ScalerSetByte(P78_CC_HDMI_GPVS, 0x01);

                    DebugMessageRx4("FRL Rx4: AVI retry and GCP", 0);
                }
                else
                {
                    CLR_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();
                    DebugMessageRx4("FRL Rx4: Only GCP", 0);
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

            CLR_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
        ScalerHdmiFrlMacRx4RoundRobinDetect(_WAIT);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P78_D5_HDMI_RSV64_IE, (_BIT2), _TRUE) == _TRUE)
        {
            SET_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        // Detect for Deep color
        ucRSVColorDepth = ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x42, (_BIT3 | _BIT2 | _BIT1 | _BIT0));  // 0x42: RSV5 GCP SB1

        if(((GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE) && (ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLOR_SPACE) == _COLOR_SPACE_YCBCR422)) ||
           ((GET_HDMI_FRL_MAC_RX4_GCP_RECEIVED() == _TRUE) && (ScalerGetBit(P78_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != ucRSVColorDepth)))
        {
            // Wait at least 3 frame for HW auto update color depth value
            if(GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                BYTE ucFrameRate = 0x00;

                if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_VIC) != 0x00)
                {
                    ucFrameRate = ScalerTmdsMacRxGetVicVfreqParameter(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_VIC));
                }
                else if(ScalerHdmiFrlMacRx4Rsv6GetAviInfo(_AVI_INFO_FR) != 0x00)
                {
                    ucFrameRate = ScalerTmdsMacRxGetOvtVfreqParameter(ScalerHdmiFrlMacRx4Rsv6GetAviInfo(_AVI_INFO_FR));
                }

                if(ucFrameRate != 0x00)
                {
                    // 3ms to ensure HW apply
                    ScalerTimerDelayXms(3);
                    ScalerTimerDelayXms(3000 / (WORD)ucFrameRate);
                    if(ScalerGetBit(P78_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != ucRSVColorDepth)
                    {
                        // Wait 3 more frame for HW auto update color depth value
                        ScalerTimerDelayXms(3000 / (WORD)ucFrameRate);
                        DebugMessageRx4("FRL Rx4: More delay for GCP DPC HW update", ScalerGetBit(P78_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
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

        CLR_HDMI_FRL_MAC_RX4_PACKET_DETECTING();

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        CLR_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING();
#endif

#if(_DM_FUNCTION == _ON)
        CLR_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING();
        CLR_DRAM_RECEIVED_FROM_DM_DETECT(enumDx);
#endif
    }
    else
    {
        // Both GCP & AVI infoframe packet have been received
        if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Clear Detection Flag
            ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // GCP received
            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

            // AVI received
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_51_PORT_PAGE78_HDMI_ACRCR, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();
        }
        else if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT1)
        {
            // Clear Detection Flag
            ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // GCP received
            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

            // AVI NO received
            // Manual Set Color Space and disable pixel repetition
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_51_PORT_PAGE78_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_50_PORT_PAGE78_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();
        }
        else if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, (_BIT1 | _BIT0)) == _BIT0)
        {
            // Clear Detection Flag
            ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // GCP No received
            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

            // AVI received
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_51_PORT_PAGE78_HDMI_ACRCR, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();
        }
        else
        {
            // GCP No received
            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX4_GCP_RECEIVED();

            // AVI NO received
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_51_PORT_PAGE78_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_50_PORT_PAGE78_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerHdmiFrlMacRx4WatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
        ScalerHdmiFrlMacRx4RoundRobinDetect(_NOT_WAIT);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
#if(_DM_FUNCTION == _ON)
        if((ScalerGetBit(P78_D5_HDMI_RSV64_IE, _BIT2) == _BIT2) || (GET_DRAM_RECEIVED_FROM_DM_DETECT(enumDx) == _TRUE))
#else
        if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, _BIT2) == _BIT2)
#endif
        {
            SET_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();

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
                ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            }
#else
            // w1c RSV received bit
            ScalerSetBit(P78_D5_HDMI_RSV64_IE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#endif
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        SET_HDMI_FRL_MAC_RX4_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_RX4_HDMI_FRL_PACKET_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PacketDetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX4_PACKET_DETECTING();
}

//--------------------------------------------------
// Description  : FRL MAC reset RX4 Timer Event
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4TimerEventReset(void)
{
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI_FRL_PACKET_DETECT);
    ScalerHdmiFrlMacRx4WatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD | _HDMI_FRL_DPF_FIFO_WD | _HDMI_EMP_TIMEOUT_WD), _DISABLE);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON))
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI_FRL_EMP_DETECT);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI_FRL_ADVANCED_HDR10_DETECT);
#endif

    // Clear DPF Pixel Mode Mismatch flag
    CLR_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH();
}

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
//--------------------------------------------------
// Description  : RoundRobin Detect
// Input Value  : bWait
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4RoundRobinDetect(bit bWait)
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
        if((ScalerTimerPollingFlagProc(130, P78_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE) || (ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, (_BIT7 | _BIT6)) != 0x00))
        {
            if(ScalerGetBit(P78_CC_HDMI_GPVS, _BIT5) == _BIT5)
            {
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P78_96_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_0);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_0);
#endif
                }
            }

            if(ScalerGetBit(P78_CC_HDMI_GPVS, _BIT6) == _BIT6)
            {
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P78_97_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_1);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_1);
#endif
                }
            }

            if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, _BIT7) == _BIT7)
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P78_98_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_2);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_2);
#endif
                }
            }

            if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, _BIT6) == _BIT6)
            {
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
                if(ScalerGetByte(P78_99_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
                {
                    ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_3);
                }
                else
#endif
                {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                    ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_3);
#endif
                }
            }
        }
#endif

        //-----------------------------------------
        // FS PR Flag setting
        //-----------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(ScalerTimerPollingFlagProc(130, P78_D5_HDMI_RSV64_IE, _BIT3, _TRUE) == _TRUE)
        {
            SET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
#endif

        //-----------------------------------------
        // FS SPD INFO Flag setting
        //-----------------------------------------
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
        bFsPktRvd = GET_TMDS_MAC_RX4_FS_VALUABLE();
#else
        for(BYTE ucCount = 0; ucCount < 65; ucCount++)
        {
            ScalerTimerDelayXms(2);

            if(GET_TMDS_MAC_RX4_FS_VALUABLE() == _TRUE)
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
            SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
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
        if(ScalerGetBit(P78_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            ScalerSetByte(P78_CC_HDMI_GPVS, _BIT5);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P78_96_HDMI_RECEIVE_TAG_RSV0) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_0);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_0);
#endif
            }
        }

        // Check for RSV1
        if(ScalerGetBit(P78_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerSetByte(P78_CC_HDMI_GPVS, _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P78_97_HDMI_RECEIVE_TAG_RSV1) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_1);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_1);
#endif
            }
        }

        // Check for RSV2
        if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, _BIT7) == _BIT7)
        {
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P78_98_HDMI_RECEIVE_TAG_RSV2) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_2);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_2);
#endif
            }
        }

        // Check for RSV3
        if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, _BIT6) == _BIT6)
        {
            ScalerSetDataPortBit_EXINT0(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
            if(ScalerGetByte(P78_99_HDMI_RECEIVE_TAG_RSV3) == _SPD_INFO_TYPE)
            {
                ScalerHdmiFrlMacRx4RsvSpdHandler(_HDMI_RSV_3);
            }
            else
#endif
            {
#if(_HDMI_VSIF_RCV_BY_RR == _ON)
                ScalerHdmiFrlMacRx4RsvVsifHandler(_HDMI_RSV_3);
#endif
            }
        }
#endif

        //-----------------------------------------
        // FS PR Flag setting
        //-----------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
        if(ScalerGetBit(P78_D5_HDMI_RSV64_IE, _BIT3) == _BIT3)
        {
            SET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_FREESYNC_REPLAY_RECEIVED();
        }
#endif

        //-----------------------------------------
        // FS SPD INFO Flag setting
        //-----------------------------------------
#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        if((GET_FREESYNC_HDMI_VCP() == 0x01) && (GET_TMDS_MAC_RX4_FS_VALUABLE() == _TRUE))
#else
        if(GET_TMDS_MAC_RX4_FS_VALUABLE() == _TRUE)
#endif
        {
            SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
            CLR_TMDS_MAC_RX4_FS_VALUABLE();
        }
        else
        {
            CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
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
void ScalerHdmiFrlMacRx4RsvSpdHandler(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucI = 0;
    BYTE ucVnCount = 0;
    BYTE pucHdmiVenderName[4] = {0};

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x52);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x71);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x90);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0xAF);
            break;

        default:
            break;
    }

    for(ucVnCount = 0; ucVnCount < 4; ucVnCount++)
    {
        pucHdmiVenderName[ucVnCount] = ScalerGetByte(P78_CE_HDMI_PSDP);
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
                ScalerSetByte(P78_CD_HDMI_PSAP, 0x5A);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0x79);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0x98);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0xB7);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 16; ucI++)
        {
            g_stTmdsMacRx4SpdInfo.pucHdmiProductDescription[ucI] = ScalerGetByte(P78_CE_HDMI_PSDP);
        }
    }
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    else if((pucHdmiVenderName[0] == 0x1A) && (pucHdmiVenderName[1] == 0x00) && (pucHdmiVenderName[2] == 0x00) && (GET_TMDS_MAC_RX4_FS_VALUABLE() == _FALSE))
    {
        SET_TMDS_MAC_RX4_FS_VALUABLE();

        switch(enumRsvNumber)
        {
            case _HDMI_RSV_0:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0x51);
                break;

            case _HDMI_RSV_1:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0x70);
                break;

            case _HDMI_RSV_2:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0x8F);
                break;

            case _HDMI_RSV_3:
                ScalerSetByte(P78_CD_HDMI_PSAP, 0xBF);
                break;

            default:
                break;
        }

        for(ucI = 0; ucI < 28; ucI++)
        {
            g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[ucI] = ScalerGetByte(P78_CE_HDMI_PSDP);
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
void ScalerHdmiFrlMacRx4RsvVsifHandler(EnumHdmiRsvNumber enumRsvNumber)
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
#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
        case _HDMI_VSIF_OUI:

            SET_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED();

            ScalerHdmiFrlMacRx4HdmiVsif3dVideoProc(enumRsvNumber);

            break;
#endif

#if((_HDMI21_ALLM_SUPPORT == _ON) || (_HDMI21_CCBPC_SUPPORT == _ON) || (_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON))
        case _HF_VSIF_OUI:

            SET_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED();

#if(_HDMI21_ALLM_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4AllmProc(enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4CcbpcProc(enumRsvNumber);
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4HfVsif3dVideoProc(enumRsvNumber);
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
void ScalerHdmiFrlMacRx4HdmiVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit b3dVideo = _FALSE;

    // Get HDMI Video Format (PB4)
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x55);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x74);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x93);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0xB2);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT(7, 5)) == _BIT6) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    if(b3dVideo == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
}

//--------------------------------------------------
// Description  : Parser 3D Video format from HF VSIF
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4HfVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit b3dVideo = _FALSE;

    // Get HDMI Video Format (PB5)
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x56);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x75);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x94);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0xB3);
            b3dVideo = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT0) == _BIT0) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    if(b3dVideo == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI_3D_VIDEO_VALID();
    }
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable ALLM
// Input Value  : RSV number
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4AllmProc(EnumHdmiRsvNumber enumRsvNumber)
{
    bit bAllm = 0;

#if(_DM_FUNCTION == _ON)
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX4);
#endif

    // Get ALLM bit
    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x56);
            bAllm = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x75);
            bAllm = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x94);
            bAllm = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0xB3);
            bAllm = (((ScalerGetByte(P78_CE_HDMI_PSDP) & _BIT1) == _BIT1) ? _TRUE : _FALSE);
            break;

        default:

            break;
    }

    // Enable/Disable ALLM
    if(bAllm == _TRUE)
    {
        SET_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();

#if(_DM_FUNCTION == _ON)
        ScalerTmdsMacRxSetDmAllmStatus(enumInputPort);
#endif
    }
    else
    {
        CLR_TMDS_MAC_RX4_HDMI21_ALLM_ENABLED();

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
void ScalerHdmiFrlMacRx4CcbpcProc(EnumHdmiRsvNumber enumRsvNumber)
{
    BYTE ucCcbpcValue = 0;

    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    switch(enumRsvNumber)
    {
        case _HDMI_RSV_0:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x56);
            ucCcbpcValue = (ScalerGetByte(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_1:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x75);
            ucCcbpcValue = (ScalerGetByte(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_2:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0x94);
            ucCcbpcValue = (ScalerGetByte(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
            break;

        case _HDMI_RSV_3:
            ScalerSetByte(P78_CD_HDMI_PSAP, 0xB3);
            ucCcbpcValue = (ScalerGetByte(P78_CE_HDMI_PSDP) & 0xF0) >> 4;
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
void ScalerHdmiFrlMacRx4AdvancedHdr10DetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING();
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : DM Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4HdmiDmDetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING();
}
#endif

//--------------------------------------------------
// Description  : Hdmi2.1 Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4WatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD) && (GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE))
        {
            if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_41_PORT_PAGE78_HDMI_VWDSR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetByte(P78_CC_HDMI_GPVS, _BIT0);

                // Enable Color Space/ Colorimetry Change Detection
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_45_PORT_PAGE78_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_AA_PORT_PAGE78_HDMI_PVGCR3, ~_BIT7, _BIT7);

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_41_PORT_PAGE78_HDMI_VWDSR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetByte(P78_CB_HDMI_SR, _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }

        if((ucWDType & _HDMI_FRL_DPF_FIFO_WD) == _HDMI_FRL_DPF_FIFO_WD)
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, _BIT6) == 0x00)
                {
                    // Clear DPF overflow and underflow flag
                    ScalerSetByte(P69_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4));

                    // Enable DSC Watch Dog when MAC DPF overflow or underflow
                    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, ~_BIT6, _BIT6);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P69_A0_DPF_OUTPUT_0, _BIT3) == 0x00)
                {
                    // Clear DPF overflow and underflow flag
                    ScalerSetByte(P69_AF_DPF_FIFO_CTRL, (_BIT5 | _BIT4));

                    // Enable DPF Watch Dog
                    ScalerSetBit(P69_A0_DPF_OUTPUT_0, ~(_BIT3 | _BIT0), _BIT3);
                }
            }
        }

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON))
        /*if((ucWDType & _HDMI_EMP_TIMEOUT_WD) == _HDMI_EMP_TIMEOUT_WD)
        {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                if(ScalerGetBit(P1E_55_EMP_TIMEOUT_2, _BIT1) == 0x00)
                {
                    // Clear CVTEM Timeout flag
                    ScalerSetBit(P1E_54_EMP_TIMEOUT_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT5);

                    // EMP Timeout to enable DSC_DPF WD
                    ScalerSetBit(P1E_55_EMP_TIMEOUT_2, ~(_BIT2 | _BIT1), _BIT1);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P1E_55_EMP_TIMEOUT_2, _BIT2) == 0x00)
                {
                    // Clear VTEM / VSEM / DHDREM Timeout flag
                    ScalerSetBit(P1E_54_EMP_TIMEOUT_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT4));

                    // EMP Timeout to enable DPF WD
                    ScalerSetBit(P1E_55_EMP_TIMEOUT_2, ~(_BIT2 | _BIT1), _BIT2);
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
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_41_PORT_PAGE78_HDMI_VWDSR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_45_PORT_PAGE78_HDMI_PVGCR0, 0x00);
            ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_AA_PORT_PAGE78_HDMI_PVGCR3, 0x00);

            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_46_PORT_PAGE78_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, ~_BIT7, 0x00);
        }

        if((ucWDType & _HDMI_FRL_DPF_FIFO_WD) == _HDMI_FRL_DPF_FIFO_WD)
        {
            // Disable MAC DPF Watch Dog
            ScalerSetBit(P69_A0_DPF_OUTPUT_0, ~(_BIT3 | _BIT0), 0x00);

            // Disable MAC to DSC Watch Dog
            ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0, ~_BIT6, 0x00);
        }

        if((ucWDType & _HDMI_EMP_TIMEOUT_WD) == _HDMI_EMP_TIMEOUT_WD)
        {
            // Disable EMP Timeout Watch Dog (RL6978 not support emp_dsc_to_err wd)
            SET_HDMI_RX4_EMP_TIMEOUT_WD_DISABLE();
        }
    }
}

//--------------------------------------------------
// Description  : HDMI2.1 Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4VideoSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    BYTE ucColorSpace = 0;

    if(GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_51_PORT_PAGE78_HDMI_ACRCR, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

        ucColorSpace = ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(ucColorSpace == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx4("FRL Rx4: Get Color Space RGB", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);
        }
        else if(ucColorSpace == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx4("FRL Rx4: Get Color Space YUV422", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR422);
        }
        else if(ucColorSpace == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx4("FRL Rx4: Get Color Space YUV420", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx4("FRL Rx4: Get Color Space YUV444", ucColorSpace);
            SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 0", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 1", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 2", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 3", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 4", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 5", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 6", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 7", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 8", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition 9", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Pixel Repetition Error", 0x00);
                SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerHdmiFrlMacRx4ColorimetrySetting();

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
        // Set Quantization
        ScalerHdmiFrlMacRx4QuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
        SET_COLOR_SPACE(enumMappingPort, _COLOR_SPACE_RGB);
        SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_RESERVED);

        // Manual Set Color Space to RGB and disable pixel repetition
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_51_PORT_PAGE78_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable down sampling
        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_50_PORT_PAGE78_HDMI_VCR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerHdmiFrlMacRx4SetPorchColor(GET_COLOR_SPACE(enumMappingPort));
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerHdmiFrlMacRx4GetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:
                return ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_CONTENT_TYPE:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x08, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_PIXEL_REPETITION:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:
                return (ScalerGetDataPortBit(P78_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:
                return ScalerGetDataPortSingleByte(P78_CD_HDMI_PSAP, 0x07);

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
BYTE ScalerHdmiFrlMacRx4Rsv6GetAviInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x61, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x62, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x63, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_ADD_EXTENDED_COLORIMETRY:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x6E, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x63, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x65, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:
                return ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x61, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x63, _BIT7) >> 7);

            case _AVI_INFO_CONTENT_TYPE:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x65, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_PIXEL_REPETITION:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x65, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:
                return (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x62, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:
                return ScalerGetDataPortSingleByte(P78_D0_HDMI_PSAP2, 0x64);

            case _AVI_INFO_FR:
                return ((ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x6F, _BIT6) >> 2) | (ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x6E, (_BIT3 | _BIT2 | _BIT1 | _BIT0))));

            case _AVI_INFO_RID:
                return ScalerGetDataPortBit(P78_D0_HDMI_PSAP2, 0x6F, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            default:
                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : FRL Rx4 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ColorimetrySetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("FRL Rx4: Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx4("FRL Rx4: Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx4("FRL Rx4: Get Colorimetry 709", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("FRL Rx4: Get Colorimetry Extended", 0x00);

                SET_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT);

                ScalerHdmiFrlMacRx4ColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX4_COLORIMETRY_PREVALUE(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_RX4_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("FRL Rx4: Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("FRL Rx4: Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT);

                ScalerHdmiFrlMacRx4ColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(enumMappingPort, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ColorimetryExtSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_RX4_COLORIMETRY_EXT_PREVALUE(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_RX4_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            case _AVI_COLORIMETRY_EXT_111:

                DebugMessageRx4("FRL Rx4: Get Colorimetry Additional Extended", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_ADD);

                ScalerHdmiFrlMacRx4ColorimetryAddExtSetting();

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX4_COLORIMETRY_EXT_PREVALUE(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_RX4_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("FRL Rx4: Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            case _AVI_COLORIMETRY_EXT_111:

                DebugMessageRx4("FRL Rx4: Get Colorimetry Additional Extended", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_ADD);

                ScalerHdmiFrlMacRx4ColorimetryAddExtSetting();

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : FRL Rx4 Colorimetry Additional Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ColorimetryAddExtSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        // Get additional extended colorimetry
        SET_RX4_COLORIMETRY_ADD_EXT_PREVALUE(ScalerHdmiFrlMacRx4Rsv6GetAviInfo(_AVI_INFO_ADD_EXTENDED_COLORIMETRY));

        // Get additional extended colorimetry
        switch(GET_RX4_COLORIMETRY_ADD_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_ADD_EXT_0010:

                DebugMessageRx4("FRL Rx4: Get Colorimetry ADD_EXT_YCC_ITUR_BT2100", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_YCC_ITUR_BT2100);

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Colorimetry INTO_DEFAULT", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        SET_RX4_COLORIMETRY_ADD_EXT_PREVALUE(ScalerHdmiFrlMacRx4Rsv6GetAviInfo(_AVI_INFO_ADD_EXTENDED_COLORIMETRY));

        switch(GET_RX4_COLORIMETRY_ADD_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_ADD_EXT_0000:

                DebugMessageRx4("FRL Rx4: Get Colorimetry ADD_EXT_RGB_SMPTE_ST2113_P3D65", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3D65);

                break;

            case _AVI_COLORIMETRY_ADD_EXT_0001:

                DebugMessageRx4("FRL Rx4: Get Colorimetry ADD_EXT_RGB_SMPTE_ST2113_P3DCI", 0x00);

                SET_ADD_EXT_COLORIMETRY(enumMappingPort, _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3DCI);

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get Colorimetry INTO_DEFAULT", 0x00);

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
EnumContentType ScalerHdmiFrlMacRx4GetAviContentType(void)
{
    BYTE ucContentType = ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_CONTENT_TYPE);

    switch(ucContentType)
    {
        case 0x00:

            if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_IT_CONTENT) == 0x01)
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
// Description  : TMDS Rx4 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4QuantizationSetting(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
    {
        SET_RX4_QUANTIZATION_PREVALUE(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_RX4_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx4("FRL Rx4: Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx4("FRL Rx4: Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(enumMappingPort, _YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
    {
        switch(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx4("FRL Rx4: Get RGB LIMIT RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx4("FRL Rx4: Get RGB FULL RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx4("FRL Rx4: Get RGB DEFAULT RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx4("FRL Rx4: Get RGB RESERVED RANGE", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(enumMappingPort, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx4("FRL Rx4: Get RGB RANGE Error", 0x00);

                SET_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

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
BYTE ScalerHdmiFrlMacRx4GetColorDepth(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_HDMI_FRL_MAC_RX4_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P78_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P78_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1))
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P78_B4_TMDS_DPC0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1 | _BIT0))
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
bit ScalerHdmiFrlMacRx4ColorInfoChanged(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    BYTE pucTemp[2] = {0};

    // Check Color Space
    if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(enumMappingPort))
    {
        DebugMessageRx4("FRL Rx4: Color Space Changed", 0x00);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _TRUE;
        }
        else
        {
            if(ScalerHdmiFrlMacRx4SeamlessReset() == _SOURCE_NONE)
            {
                return _TRUE;
            }
        }
#else
        return _TRUE;
#endif
    }

    // Check Colorimetry
    if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_RX4_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx4("FRL Rx4: Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_RX4_COLORIMETRY_PREVALUE();

            ScalerHdmiFrlMacRx4ColorimetrySetting();

            if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_RX4_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_RX4_COLORIMETRY_CHANGED();
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
            if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_RX4_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx4("FRL Rx4: Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_RX4_COLORIMETRY_EXT_PREVALUE();

                    ScalerHdmiFrlMacRx4ColorimetryExtSetting();

                    if((GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_RX4_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE(enumMappingPort) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_RX4_COLORIMETRY_EXT_CHANGED();
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
        if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_RX4_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx4("FRL Rx4: YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_RX4_QUANTIZATION_PREVALUE();

                ScalerHdmiFrlMacRx4QuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_RX4_QUANTIZATION_CHANGED();
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
        if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_RX4_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx4("FRL Rx4: RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerHdmiFrlMacRx4QuantizationSetting();

                SET_RX4_QUANTIZATION_CHANGED();
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
bit ScalerHdmiFrlMacRx4AviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerHdmiFrlMacRx4GetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION())
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
void ScalerHdmiFrlMacRx4SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    SET_HDMI_FRL_RX4_DPF_RGB_OUTPUT_DISABLE();

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P69_A2_DPF_OUTPUT_2, 0x80);
        ScalerSetByte(P69_A3_DPF_OUTPUT_3, 0x00);
        ScalerSetByte(P69_A4_DPF_OUTPUT_4, 0x0F);
        ScalerSetByte(P69_A5_DPF_OUTPUT_5, 0x00);
        ScalerSetByte(P69_A6_DPF_OUTPUT_6, 0x80);
        ScalerSetByte(P69_A7_DPF_OUTPUT_7, 0x00);
    }
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P69_A2_DPF_OUTPUT_2, 0x10);
        ScalerSetByte(P69_A3_DPF_OUTPUT_3, 0x00);
        ScalerSetByte(P69_A4_DPF_OUTPUT_4, 0x10);
        ScalerSetByte(P69_A5_DPF_OUTPUT_5, 0x00);
        ScalerSetByte(P69_A6_DPF_OUTPUT_6, 0x80);
        ScalerSetByte(P69_A7_DPF_OUTPUT_7, 0x00);
    }
    else
    {
        ScalerSetByte(P69_A2_DPF_OUTPUT_2, 0x00);
        ScalerSetByte(P69_A3_DPF_OUTPUT_3, 0x00);
        ScalerSetByte(P69_A4_DPF_OUTPUT_4, 0x00);
        ScalerSetByte(P69_A5_DPF_OUTPUT_5, 0x00);
        ScalerSetByte(P69_A6_DPF_OUTPUT_6, 0x00);
        ScalerSetByte(P69_A7_DPF_OUTPUT_7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Hdmi2.1 Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4ResetProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    // Clear FRL rate
    ScalerHdmiFrlMacRxClrDxFrlRate(enumMappingPort);

    // Clear Rebuild PHY IRQ and flag
    ScalerSetByte(P78_E6_HDMI_TRANSDET_CTRL2, 0x0F);

    // Clear Rebuild PHY Event
    CLR_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT();

    // Clear FRL set PHY flag
    CLR_HDMI_FRL_MAC_RX4_PHY_SET();

    // Clear CED Valid flag
    ScalerSetBit(P78_08_HDMI21_FRL_CED_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Clear RSED Valid flag
    ScalerSetBit(P69_10_HDMI21_RS_0, ~_BIT3, 0x00);

    // Reset SCDC
    ScalerSetBit(P73_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

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
    SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);

    // Disable DPF CLK
    ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // reset MAC selection to MAC2.0
    ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, 0x00);

    // reset PHY to MAC2.0
    ScalerTmdsPhyRxSelectMode(enumMappingPort, _HDMI_VERSION_2_0);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PowerSavingProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, _BIT6) == _BIT6)
    {
        // Clear FLT_ready
        ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT6, 0x00);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        // Clear SCDC 0x40[7] DSC dec fail
        ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
        // Set Status update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
    }

    // Disable DPF CLK
    ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    ScalerHdmiFrlMacRx4LinkTrainingDisable();

    // Reset Link Training State
    SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);

    // reset MAC selection to MAC2.0
    ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, 0x00);

    // reset PHY to MAC2.0
    ScalerTmdsPhyRxSelectMode(enumMappingPort, _HDMI_VERSION_2_0);

    // Clear CED/RSED read flag
    ScalerSetByte(P73_25_HDMI_CTRL_25, (_BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : Hdmi2.1 Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PowerOffProc(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);

    if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, _BIT6) == _BIT6)
    {
        // Clear FLT_ready
        ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT6, 0x00);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        // Clear SCDC 0x40[7] DSC dec fail
        ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, 0x00);
#endif
        // Set Status update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
    }

    // Disable DPF CLK
    ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Power down PLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT7, 0x00);
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    ScalerHdmiFrlMacRx4LinkTrainingDisable();

    // Reset Link Training State
    SET_HDMI_FRL_MAC_RX4_LINK_TRAINING_STATE(_HDMI_FRL_LT_LTS2);

    // reset MAC selection to MAC2.0
    ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, 0x00);

    // reset PHY to MAC2.0
    ScalerTmdsPhyRxSelectMode(enumMappingPort, _HDMI_VERSION_2_0);
}


//--------------------------------------------------
// Description  : Hdmi2.1 Check FLT no retrain bit for PS entering
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4EnterPowerSavingCheck(void)
{
    if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_30_PORT_PAGE73_HDMI_SCDC_30, _BIT1) == _BIT1)
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
void ScalerHdmiFrlMacRx4ClrFltReady(void)
{
    if(ScalerGetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, _BIT6) == _BIT6)
    {
        // Clear FLT_ready
        ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT6, 0x00);

        // Set Status update
        ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
    }

    // reset MAC selection to MAC2.0
    ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Save SCDC Status Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SaveScdcStatus(void)
{
    g_ucHdmiFrlMacRx4ScdcStatusFlag = ScalerGetDataPortSingleByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40);
}

//--------------------------------------------------
// Description  : Hdmi2.1 Restore SCDC FRL_Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4RestoreScdcStatus(void)
{
    ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT6, (g_ucHdmiFrlMacRx4ScdcStatusFlag & _BIT6));
}

//--------------------------------------------------
// Description  : Get Hdmi2.1 Dpf Pixel Mode
// Input Value  :
// Output Value : 1/2/4 Pixel Mode
//--------------------------------------------------
EnumHdmiFrlMacRxDpfPixelMode ScalerHdmiFrlMacRx4GetDpfPixelMode(void)
{
    switch(ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)))
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
bit ScalerHdmiFrlMacRx4InterlaceModeCheck(void)
{
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
    {
        return _FALSE;
    }
    else
#endif
    {
        return ((ScalerGetBit(P69_4A_FRL_MEASURE_A, _BIT4) == _BIT4) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Signal Detection for HDMI2.1(Power Saving)
// Input Value  :
// Output Value : True : HDMI2.1 Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4PSPreDetect(void)
{
    bit bResult = _FALSE;

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
    bResult = ScalerHdmiFrlMacRx4RebuildPhy();
#endif

    // Check Source write SCDC FRL_Rate Register
    if(ScalerGetBit(P73_3D_HDMI21_LT_0, _BIT7) == _BIT7)
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
void ScalerHdmiFrlMacRx4LinkTrainingDisable(void)
{
    // Clear FLT_update and FRL_start
    ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~(_BIT5 | _BIT4), 0x00);

    // Clear link training related IRQ Flag and Disable link training IRQ
    ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT5 | _BIT3));
#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    ScalerSetBit(P73_3D_HDMI21_LT_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT1);
#endif

    // Clear Link Training event
    CLR_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT();
    CLR_HDMI_FRL_MAC_RX4_FRL_START_EVENT();

    // Clear PHY SET flag
    CLR_HDMI_FRL_MAC_RX4_PHY_SET();

    // Disable CED Lock Transition IRQ
    ScalerSetByte(P78_17_HDMI21_FRL_CED_15, 0x00);

    // Disable CED Function and valid
    ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~_BIT6, 0x00);
    ScalerSetByte(P78_08_HDMI21_FRL_CED_0, 0x00);

    // Disable running disparity calculate
    ScalerSetBit(P78_09_HDMI21_FRL_CED_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable RSED update and clear RSED update flag
    ScalerSetBit(P69_13_HDMI21_RS_3, ~(_BIT7 | _BIT1), _BIT1);

    // Disable RSED Function and valid
    ScalerSetBit(P69_19_HDMI21_FW_RS_5, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
    ScalerSetBit(P69_10_HDMI21_RS_0, ~(_BIT5 | _BIT3), 0x00);

    // Disable FRL small FIFO read and write clock
    ScalerSetBit(P78_A7_TMDS_PWDCTL, ~_BIT4, 0x00);

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
    // Clear SCDC 0x40[7] DSC dec fail
    ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, 0x00);

    // Set Status update
    ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
#endif
}

//--------------------------------------------------
// Description  : Set SCDC Update Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetScdcUpdateFlag(DWORD ulAnd, BYTE ucOr)
{
    BYTE ucLoop = 0;

    // Set SCDC update flag addr
    ScalerSetByte(P73_39_HDMI_CTRL_39, _P73_3A_PT_10_PORT_PAGE73_HDMI_SCDC_10);

    // Check I2C not busy before update SCDC
    while(ucLoop < 20)
    {
        ucLoop ++;

        // Clear I2C busy flag
        ScalerSetBit(P73_20_HDMI_CTRL_20, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

        DELAY_XUS(100);

        // Check I2C is busy ot not
        if(ScalerGetBit(P73_20_HDMI_CTRL_20, (_BIT6 | _BIT4)) == 0x00)
        {
            break;
        }
    }

    // Set SCDC update flag value
    ScalerSetBit(P73_3A_HDMI_CTRL_3A, (BYTE)ulAnd, ucOr);
}

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4GetHDR10Data(BYTE *pucHDRData)
{
    BYTE ucAddressportBackup = 0x00;
    bit bBackupStatus = _FALSE;

    if(CPU32_IS_INSIDE_INTERRUPT() == _TRUE)
    {
        ucAddressportBackup = ScalerGetByte(P78_D0_HDMI_PSAP2);
        bBackupStatus = _TRUE;
    }

    ScalerGetDataPortByte(P78_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P78_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P78_D0_HDMI_PSAP2, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);

    if(bBackupStatus == _TRUE)
    {
        ScalerSetByte(P78_D0_HDMI_PSAP2, ucAddressportBackup);
    }
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    memcpy(&pucFreeSyncIIData[0], &g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[0], 11);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)


#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
DWORD ScalerHdmiFrlMacRx4FreeSyncHDMIGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    WORD usFreesyncVfreqmax = 0;
    WORD usFreesyncVfreqmin = 0;
    DWORD ulTargetOutputPixelRate = 0;
    WORD usAmdVfreqMaxBit = 0;
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX4);

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
        return (TO_DWORD(0, g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[3], g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[2], g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[1]));
    }

    if((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[1] == 0x1A) && (g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[2] == 0x00) && (g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[3] == 0x00))
    {
        switch(enumContent)
        {
            case _SPD_INFO_FREESYNC_SUPPORT:

                return (((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x01) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FREESYNC_ENABLE:

                return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x02) >> 1) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FREESYNC_ACTIVE:

                return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[6] & 0x04) >> 2) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FRAME_TYPE:

                return (((ScalerGetBit(P78_D6_HDMI_SHDR_IE, (_BIT1 | _BIT0))) == ((ScalerGetBit(P78_D6_HDMI_SHDR_IE, (_BIT3 | _BIT2))) >> 2)) ? _ON : _OFF);

            case _SPD_INFO_PQ_EOTF_ACTIVE:

                return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[9] & _BIT5) >> 5) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_GAMMA_2_2_EOTF_ACTIVE:

                return ((((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[9] & 0x04) >> 2) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_FIXED_RATE_CONTENT_ACTIVE:

                return (((g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[16] & 0x01) != 0x00) ? _ON : _OFF);

            case _SPD_INFO_TARGET_OUTPUT_PIXEL_RATE:

                ulTargetOutputPixelRate = (((DWORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[13] << 16) | ((DWORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[14] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[15]);

                return ulTargetOutputPixelRate;

            case _SPD_INFO_FREESYNC_MIN_VFREQ:

                if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
                {
                    pData[1] = 0x00;
                    usFreesyncVfreqmin = (((WORD)pData[1] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[7]);
                }
                else
                {
                    usFreesyncVfreqmin = (((WORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[11] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[7]);
                }

                usFreesyncVfreqmin &= usAmdVfreqMaxBit;

                if(((usFreesyncVfreqmin * 10) > _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) || ((usFreesyncVfreqmin * 10) < _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
                {
                    DebugMessageRx4("Freesync SPD info abnormal", 0);
                }

                return usFreesyncVfreqmin;

            case _SPD_INFO_FREESYNC_MAX_VFREQ:

                if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
                {
                    pData[1] = 0x00;
                    usFreesyncVfreqmax = (((WORD)pData[1] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[8]);
                }
                else
                {
                    usFreesyncVfreqmax = (((WORD)g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[12] << 8) | g_stTmdsMacRx4SpdFsInfo.pucHdmiFreesyncInfo[8]);
                }

                usFreesyncVfreqmax &= usAmdVfreqMaxBit;

                if(((usFreesyncVfreqmax * 10) > _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) || ((usFreesyncVfreqmax * 10) < _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
                {
                    DebugMessageRx4("Freesync SPD info abnormal", 0);
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
void ScalerHdmiFrlMacRx4EmpPacketDetect(bit bWait)
{
#if(_HDMI_SBTM_SUPPORT == _ON)
    BYTE ucHdmiSbtmCheckTime = 0;
#endif

    if(bWait == _WAIT)
    {
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
        // Clear VRR flag
        CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
        CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
#endif
#if(_HDMI21_FVA_SUPPORT == _ON)
        SET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR(1);
#endif
        // CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();
#if(_HDMI21_VRR_SUPPORT == _ON)
        CLR_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
        CLR_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
#endif
        // Wait at least 2 frames for HW auto update VTEM flag and Length not 0
        if((ScalerTimerPollingFlagProc(90, P1E_50_EMP_HDMI, _BIT6, _TRUE) == _TRUE) && ((ScalerGetByte(P1E_65_HDMI_EMP_6) != 0x00) || (ScalerGetByte(P1E_66_HDMI_EMP_7) != 0x00)))
        {
            SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        // Wait at least 2 frames for HW auto update CVTEM flag and Length not 0
        if((ScalerTimerPollingFlagProc(90, P1E_52_EMP_DSC, _BIT4, _TRUE) == _TRUE) && ((ScalerGetByte(P1E_75_DSC_EMP_6) != 0x00) || (ScalerGetByte(P1E_76_DSC_EMP_7) != 0x00)))
        {
            SET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();
        }
        else
        {
            CLR_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();
        }
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
        ucHdmiSbtmCheckTime = 18;

        while(ucHdmiSbtmCheckTime != 0)
        {
            if(g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive == _TRUE)
            {
                DebugMessageRx4("HDMI Rx4 SBTM Receive", 0);

                SET_TMDS_MAC_RX4_SBTM_RECEIVE();
                g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive = _FALSE;
                break;
            }
            ScalerTimerDelayXms(5);
            ucHdmiSbtmCheckTime--;
        }

        if((ucHdmiSbtmCheckTime == 0x00) && (g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive == _FALSE))
        {
            DebugMessageRx4("HDMI Rx4 SBTM no Receive", 0);

            CLR_TMDS_MAC_RX4_SBTM_RECEIVE();
        }
#endif

        CLR_TMDS_MAC_RX4_EMP_DETECTING();
    }
    else
    {
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
        // VTEM have been received and Length not 0
        if((ScalerGetBit(P1E_50_EMP_HDMI, _BIT6) == _BIT6) && ((ScalerGetByte(P1E_65_HDMI_EMP_6) != 0x00) || (ScalerGetByte(P1E_66_HDMI_EMP_7) != 0x00)))
        {
            // No Received / MLDS -> Received VTEM
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _FALSE)
            {
                SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();
            }
            else
            {
                // Received VTEM Continually then enable WD
                ScalerHdmiFrlMacRx4WatchDog(_HDMI_EMP_TIMEOUT_WD, _ENABLE);
            }

            SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();

            // Clear VTEM flag
            ScalerSetBit(P1E_50_EMP_HDMI, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_HDMI21_VRR_SUPPORT == _ON)
            if((((bit)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _ENABLE) && (GET_TMDS_MAC_RX4_HDMI21_VRR_EN() != _ENABLE))
            {
                DebugMessageRx4("FRL Rx4: VRR_EN from 0 -> 1", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
                SET_TMDS_MAC_RX4_HDMI21_VRR_EN();
            }
            else if((((bit)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_VRR_EN)) == _DISABLE) && (GET_TMDS_MAC_RX4_HDMI21_VRR_EN() != _DISABLE))
            {
                DebugMessageRx4("FRL Rx4: VRR_EN from 1 -> 0", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
                CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
            }

            if((((bit)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _ENABLE) && (GET_TMDS_MAC_RX4_HDMI21_QMS_EN() != _ENABLE))
            {
                DebugMessageRx4("FRL Rx4: QMS_EN from 0 -> 1", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
                SET_TMDS_MAC_RX4_HDMI21_QMS_EN();
            }
            else if((((bit)ScalerHdmiFrlMacRx4GetVtemInfo(_HDMI21_VTEM_INFO_QMS_EN)) == _DISABLE) && (GET_TMDS_MAC_RX4_HDMI21_QMS_EN() != _DISABLE))
            {
                DebugMessageRx4("FRL Rx4: QMS_EN from 1 -> 0", 0x00);
                SET_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
                CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
            }
#endif
        }
        else
        {
            // Received VTEM -> No Received / MLDS
            if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
            {
                SET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVE_CHG();

#if(_HDMI21_VRR_SUPPORT == _ON)
                if(GET_TMDS_MAC_RX4_HDMI21_VRR_EN() == _TRUE)
                {
                    DebugMessageRx4("FRL Rx4: VTEM -> No Received/MLDS(VRR_EN from 1->0)", 0x00);
                    SET_TMDS_MAC_RX4_HDMI21_VRR_RECEIVE_CHG();
                    CLR_TMDS_MAC_RX4_HDMI21_VRR_EN();
                }

                if(GET_TMDS_MAC_RX4_HDMI21_QMS_EN() == _TRUE)
                {
                    DebugMessageRx4("FRL Rx4: VTEM -> No Received/MLDS(QMS_EN from 1->0)", 0x00);
                    SET_TMDS_MAC_RX4_HDMI21_QMS_RECEIVE_CHG();
                    CLR_TMDS_MAC_RX4_HDMI21_QMS_EN();
                }
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
                SET_TMDS_MAC_RX4_HDMI21_FVA_FACTOR(1);
#endif
                ScalerHdmiFrlMacRx4WatchDog(_HDMI_EMP_TIMEOUT_WD, _DISABLE);
            }

            CLR_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED();
        }
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
        // CVTEM have been received and Not Length = 0
        if((ScalerGetBit(P1E_52_EMP_DSC, _BIT4) == _BIT4) && ((ScalerGetByte(P1E_75_DSC_EMP_6) != 0x00) || (ScalerGetByte(P1E_76_DSC_EMP_7) != 0x00)))
        {
            // No Received -> Received CVTEM
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _FALSE)
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX4), _ENABLE);
            }
            else
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX4), _DISABLE);

                // Received CVTEM Continually then enable WD
                ScalerHdmiFrlMacRx4WatchDog(_HDMI_EMP_TIMEOUT_WD, _ENABLE);
            }

            SET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();

            // Clear CVTEM flag
            ScalerSetBit(P1E_52_EMP_DSC, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Received CVTEM -> No Received
            if(GET_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED() == _TRUE)
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX4), _ENABLE);

                ScalerHdmiFrlMacRx4WatchDog(_HDMI_EMP_TIMEOUT_WD, _DISABLE);
            }
            else
            {
                ScalerDscDecoderSetChange(ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(_RX4), _DISABLE);
            }

            CLR_TMDS_MAC_RX4_HDMI21_CVTEM_RECEIVED();
        }
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
        if(g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive == _TRUE)
        {
            SET_TMDS_MAC_RX4_SBTM_RECEIVE();
            g_stTmdsMacRx4HdmiSbtmInfo.b1SbtmReceive = _FALSE;
        }
        else
        {
            CLR_TMDS_MAC_RX4_SBTM_RECEIVE();
        }
#endif

        SET_TMDS_MAC_RX4_EMP_DETECTING();

        // Activate EMP Detection Event 12 frames = 45ms * 12
        ScalerTimerActiveTimerEvent(540, _SCALER_TIMER_EVENT_RX4_HDMI_FRL_EMP_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI2.1 EMP Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4EmpDetectEvent(void)
{
    CLR_TMDS_MAC_RX4_EMP_DETECTING();
}

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set VRR Max Vf info from Spec Table
// Input Value  : usSourceBrr (unit: 0.1Hz)
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetVrrVfmaxFromTable(WORD usSourceBrr)
{
    // Check VRRmax > 100?
    // if yes, VFmax = VRRmax
    if(g_stTmdsMacRx4Hdmi21EdidVrrCap.usEdidVrrMax >= 100)
    {
        SET_DRR_VFREQ_MAX(g_stTmdsMacRx4Hdmi21EdidVrrCap.usEdidVrrMax * 10);

        return;
    }

    // Check QMS or Gaming
    if(g_stTmdsMacRx4Hdmi21EdidVrrCap.b1EdidQms == 1)
    {
        // QMS case
        if(g_stTmdsMacRx4Hdmi21EdidVrrCap.b1EdidQmsTfrMax == 1)
        {
            SET_DRR_VFREQ_MAX(usSourceBrr);
        }
        else
        {
            if(g_stTmdsMacRx4Hdmi21EdidVrrCap.ucEdidVrrMin > 0)
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
        if(g_stTmdsMacRx4Hdmi21EdidVrrCap.ucEdidVrrMin > 0)
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
WORD ScalerHdmiFrlMacRx4GetVtemInfo(EnumHdmi21VtemInfoContent enumContent)
{
    if(GET_TMDS_MAC_RX4_HDMI21_VTEM_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _HDMI21_VTEM_INFO_VRR_EN:

                return (((ScalerGetByte(P1E_67_HDMI_EMP_8) & _BIT0) == _BIT0) ? _ON : _OFF);

            case _HDMI21_VTEM_INFO_M_CONST:

                return (((ScalerGetByte(P1E_67_HDMI_EMP_8) & _BIT1) == _BIT1) ? _ON : _OFF);

            case _HDMI21_VTEM_INFO_FVA_FACTOR_M1:

                return ((ScalerGetByte(P1E_67_HDMI_EMP_8) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

            case _HDMI21_VTEM_INFO_BASE_VFRONT:

                return (ScalerGetByte(P1E_68_HDMI_EMP_9));


            case _HDMI21_VTEM_INFO_BASE_REFRESH_RATE:

                return (((WORD)(ScalerGetByte(P1E_69_HDMI_EMP_A) & (_BIT1 | _BIT0)) << 8) | (WORD)(ScalerGetByte(P1E_6A_HDMI_EMP_B)));

            case _HDMI21_VTEM_INFO_QMS_EN:

                return (((ScalerGetByte(P1E_67_HDMI_EMP_8) & _BIT2) == _BIT2) ? _ON : _OFF);

            case _HDMI21_VTEM_NEXT_TFR:

                return ((ScalerGetByte(P1E_69_HDMI_EMP_A) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

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
void ScalerHdmiFrlMacRx4SignalDetectEvent(void)
{
    CLR_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING();
}
#endif

#if((_HDMI_FRL_MAC_RX4_LFSR_TEST_MODE == _ON) || (_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1))
//--------------------------------------------------
// Description  : LTP Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx4LtpCheck(void)
{
    // set cycle
    ScalerSetBit(P1E_30_HDMI21_LT_0, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // set L0 LTP5, L1 LTP6
    ScalerSetByte(P1E_31_HDMI21_LT_1, 0x56);

    // set L2 LTP7, L3 LTP8
    ScalerSetByte(P1E_32_HDMI21_LT_2, 0x78);

    // enable LTP check
    ScalerSetBit(P1E_30_HDMI21_LT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    ScalerTimerDelayXms(100);

    if((ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT7) == 0x00) && (ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT7) == _BIT7))
    {
        DebugMessageRx4("FRL Rx4: L0 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT7) != 0x00)
        {
            DebugMessageRx4("FRL Rx4: L0 LTP not finish", 0);
        }
        else if(ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT7) != _BIT7)
        {
            DebugMessageRx4("FRL Rx4: L0 LTP fail, error count=", ScalerGetByte(P1E_34_HDMI21_LT_4));
        }
    }

    if((ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT6) == 0x00) && (ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT6) == _BIT6))
    {
        DebugMessageRx4("FRL Rx4: L1 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT6) != 0x00)
        {
            DebugMessageRx4("FRL Rx4: L1 LTP not finish", 0);
        }
        else if(ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT6) != _BIT6)
        {
            DebugMessageRx4("FRL Rx4: L1 LTP fail, error count=", ScalerGetByte(P1E_35_HDMI21_LT_5));
        }
    }

    if((ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT5) == 0x00) && (ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT5) == _BIT5))

    {
        DebugMessageRx4("FRL Rx4: L2 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT5) != 0x00)
        {
            DebugMessageRx4("FRL Rx4: L2 LTP not finish", 0);
        }
        else if(ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT5) != _BIT5)
        {
            DebugMessageRx4("FRL Rx4: L2 LTP fail, error count=", ScalerGetByte(P1E_36_HDMI21_LT_6));
        }
    }

    if((ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT4) == 0x00) && (ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT4) == _BIT4))
    {
        DebugMessageRx4("FRL Rx4: L3 LTP pass", 0);
    }
    else
    {
        if(ScalerGetBit(P1E_30_HDMI21_LT_0, _BIT4) != 0x00)
        {
            DebugMessageRx4("FRL Rx4: L3 LTP not finish", 0);
        }
        else if(ScalerGetBit(P1E_33_HDMI21_LT_3, _BIT4) != _BIT4)
        {
            DebugMessageRx4("FRL Rx4: L3 LTP fail, error count=", ScalerGetByte(P1E_37_HDMI21_LT_7));
        }
    }
}

#endif

#if(_HDMI_FRL_MAC_RX4_LFSR_TEST_MODE == _ON)
//--------------------------------------------------
// Description  : Gap on FRL format Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx4GapCheck(void)
{
    BYTE ucTemp = 0;
    BYTE ucError = 0;

    // set 4 lane mode and FRL
    // ScalerSetBit(P1E_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), (_BIT6));

    // Enable decode, de-scramble and RS-check
    // ScalerSetBit(P69_05_HDMI21_DESCR_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    // ScalerSetBit(P69_05_HDMI21_DESCR_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    // ScalerSetBit(P69_10_HDMI21_RS_0, ~_BIT7, _BIT7);

    // Reset HDMI21 Small FIFO
    // ScalerTmdsPhyRxFifoReset(ScalerTmdsMacRxRxDxMapping(_RX4), 4);

    ScalerTimerDelayXms(10);

    // enable Gap pattern check
    ScalerSetBit(P1E_39_HDMI21_LT_9, ~(_BIT7 | _BIT6), _BIT7);

    // Wait Gap check
    /*if(ScalerTimerPollingFlagProc(2, P1E_39_HDMI21_LT_9, _BIT6, _FALSE) == _TRUE)
    {
        DebugMessageRx4("FRL Rx4: Gap Pass", 0);
    }
    else
    {
        DebugMessageRx4("FRL Rx4: Gap fail", 0);
    }*/

    DELAY_10US();

    // disable Gap pattern check
    ScalerSetBit(P1E_39_HDMI21_LT_9, ~(_BIT7 | _BIT6), 0x00);

    /*if(ScalerGetBit(P1E_39_HDMI21_LT_9, _BIT6) == 0x00)
    {
        DebugMessageRx4("FRL Rx4: Gap Pass", 0);
    }
    else*/
    {
        // Enable RS SRAM Save
        ScalerSetBit(P69_27_HDMI21_RS_SRAM_0, ~_BIT7, _BIT7);

        ScalerTimerDelayXms(10);

        if(ScalerGetBit(P69_27_HDMI21_RS_SRAM_0, _BIT0) == 0x00)
        {
            DebugMessageRx4("FRL Rx4: SRAM not finish", 0);
        }

        // RS FIFO0
        ScalerSetBit(P69_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), 0x00);

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P69_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P69_29_HDMI21_RS_SRAM_2) != 0x01)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P69_2A_HDMI21_RS_SRAM_3) != 0x01)
            {
                ucError = 1;
            }
        }

        // RS FIFO1
        ScalerSetBit(P69_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), _BIT5);

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P69_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P69_29_HDMI21_RS_SRAM_2) != 0x04)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P69_2A_HDMI21_RS_SRAM_3) != 0x04)
            {
                ucError = 1;
            }
        }

        // RS FIFO2
        ScalerSetBit(P69_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), _BIT6);

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P69_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P69_29_HDMI21_RS_SRAM_2) != 0x01)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P69_2A_HDMI21_RS_SRAM_3) != 0x01)
            {
                ucError = 1;
            }
        }

        // RS FIFO3
        ScalerSetBit(P69_27_HDMI21_RS_SRAM_0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        for(ucTemp = 0; ucTemp < 125; ucTemp ++)
        {
            ScalerSetByte(P69_28_HDMI21_RS_SRAM_1, ucTemp);

            if(ScalerGetByte(P69_29_HDMI21_RS_SRAM_2) != 0x04)
            {
                ucError = 1;
            }

            if(ScalerGetByte(P69_2A_HDMI21_RS_SRAM_3) != 0x04)
            {
                ucError = 1;
            }
        }

        // Disable RS SRAM Save
        ScalerSetBit(P69_27_HDMI21_RS_SRAM_0, ~_BIT7, 0x00);

        if(ucError == 1)
        {
            DebugMessageRx4("FRL Rx4: GAP fail", 0);
        }
        else
        {
            DebugMessageRx4("FRL Rx4: GAP pass", 0);
        }
    }
}

//--------------------------------------------------
// Description  : LFSR on FRL format Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx4LfsrCheck(void)
{
    WORD usErrorCount = 0;

    // Set MAC RX4 is FRL
    // ScalerSetBit(P1E_00_HDMI_TOP_0, ~_BIT6, _BIT6);

    ScalerTimerDelayXms(10);

    // set 4 lane mode and FRL
    ScalerSetBit(P1E_38_HDMI21_LT_8, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // LFSR check cycle
    ScalerSetBit(P69_1C_HDMI21_LFSR_2, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // LFSR check enable
    ScalerSetBit(P69_1B_HDMI21_LFSR_1, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(100);

    // LFSR pattern pass
    if(ScalerGetBit(P69_1C_HDMI21_LFSR_2, _BIT7) == _BIT7)
    {
        if(ScalerGetBit(P69_1B_HDMI21_LFSR_1, _BIT6) == 0x00)
        {
            DebugMessageRx4("FRL Rx4: LFSR pass", 0);
        }
        else
        {
            usErrorCount = ((WORD) ScalerGetBit(P69_1C_HDMI21_LFSR_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(P69_1D_HDMI21_LFSR_3);
            DebugMessageRx4("FRL Rx4: LFSR fail", usErrorCount);
        }
    }
    else
    {
        DebugMessageRx4("FRL Rx4: LFSR no finish", 0);
    }

    // LFSR check disable
    ScalerSetBit(P69_1B_HDMI21_LFSR_1, ~_BIT7, 0x00);
}
#endif // End for #if(_HDMI21_LFSR_TEST_MODE == _ON)

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
//--------------------------------------------------
// Description  : Set SCDC Decode Fail staus
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetDscDecodeFailStatus(void)
{
    // Set SCDC 0x40[7] for Dsc dec fail
    ScalerSetDataPortBit(P73_39_HDMI_CTRL_39, _P73_3A_PT_40_PORT_PAGE73_HDMI_SCDC_40, ~_BIT7, _BIT7);

    // Set SCDC 0x10[0] Status update
    ScalerHdmiFrlMacRx4SetScdcUpdateFlag(~_BIT0, _BIT0);
}
#endif

//--------------------------------------------------
// Description  : LFSR on FRL format Check
// Input Value  : None
// Output Value : _TRUE => FRL formate check pass
//--------------------------------------------------
void ScalerHdmiFrlMacRx4GetTimingInfo(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumInputPort enumInputPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    bit bDscNative420 = ScalerDscDecoderGetNative420Mode(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4));
    WORD usInputPixelClk = 0;

    // Get H Width
    pstDscTimingInfo->usHWidth = GET_HDMI_FRL_MAC_RX4_CVTEM_HCACTIVE_BYTES();

    // Get H Front Porch
    pstDscTimingInfo->usHFrontPorch = GET_HDMI_FRL_MAC_RX4_CVTEM_HFRONT();

    // Get HSW
    pstDscTimingInfo->usHSWidth = GET_HDMI_FRL_MAC_RX4_CVTEM_HSYNC();

    // Get HStart
    pstDscTimingInfo->usHStart = pstDscTimingInfo->usHSWidth + GET_HDMI_FRL_MAC_RX4_CVTEM_HBACK();

    // Get H Total
    pstDscTimingInfo->usHTotal = ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4)) + pstDscTimingInfo->usHFrontPorch + pstDscTimingInfo->usHStart;

    // Get H Total After DSC
    pstDscTimingInfo->usHTotalAfterDSC = g_usHdmiFrlMacRx4Htotal;

    // Get V Height
    pstDscTimingInfo->usVHeight = GET_HDMI_FRL_MAC_RX4_VACTIVE();

    // Get V Front Porch
    pstDscTimingInfo->usVFrontPorch = GET_HDMI_FRL_MAC_RX4_VFRONT();

    // Get V Total
    pstDscTimingInfo->usVTotal = GET_HDMI_FRL_MAC_RX4_VTOTAL();

    // Get Compressed Clk
    pstDscTimingInfo->ulCompStreamClockHz = g_ulHdmiFrlMacRx4DSCClkValue * 100;

    // Get Input Pixel Clk
    usInputPixelClk = (ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal * pstDscTimingInfo->usVTotal, (DWORD)pstDscTimingInfo->ulCompStreamClockHz * 4UL, (DWORD)pstDscTimingInfo->usHTotalAfterDSC * pstDscTimingInfo->usVTotal * (1 + bDscNative420)) / 100000);

    // Modify HSW
    pstDscTimingInfo->usHSWidth = ((GET_HDMI_FRL_MAC_RX4_CVTEM_HSYNC() > ScalerSyncGetHSWbyClk(usInputPixelClk)) ? GET_HDMI_FRL_MAC_RX4_CVTEM_HSYNC() : ScalerSyncGetHSWbyClk(usInputPixelClk));

    // Modify HStart
    pstDscTimingInfo->usHStart = ScalerSyncGetHStartbyHSW(pstDscTimingInfo->usHSWidth, usInputPixelClk);
    pstDscTimingInfo->usHStart = (((pstDscTimingInfo->usHSWidth + GET_HDMI_FRL_MAC_RX4_CVTEM_HBACK()) > pstDscTimingInfo->usHStart) ? (pstDscTimingInfo->usHSWidth + GET_HDMI_FRL_MAC_RX4_CVTEM_HBACK()) : pstDscTimingInfo->usHStart);

    // Modify H Total
    pstDscTimingInfo->usHTotal = ScalerDscDecoderGetDscPicWidth(ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(_RX4)) + pstDscTimingInfo->usHFrontPorch + pstDscTimingInfo->usHStart;

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
        pstDscTimingInfo->usVStart = GET_HDMI_FRL_MAC_RX4_VBACK() + GET_HDMI_FRL_MAC_RX4_VSYNC();

        // Get VSW
        pstDscTimingInfo->usVSWidth = GET_HDMI_FRL_MAC_RX4_VSYNC();

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
void ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off(void)
{
    // Backup CED Lock Transition IRQ
    g_stHdmiFrlMacRx4IrqStatus.b4CedLockIrqBackup = ScalerGetBit(P78_17_HDMI21_FRL_CED_15, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Backup FRL Transition detection IRQ
    g_stHdmiFrlMacRx4IrqStatus.b1TransitionDetectIrqBackup = (ScalerGetBit(P78_E6_HDMI_TRANSDET_CTRL2, _BIT7) >> 7);

    // Backup RSV0~3 received IRQ
    g_stHdmiFrlMacRx4IrqStatus.b4RsvIrqBackup = ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Backup Vs EMP IRQ
    g_stHdmiFrlMacRx4IrqStatus.b1VsEmpIrqBackup = (ScalerGetBit(P1E_51_EMP_VS, _BIT7) >> 7);

    // Backup Dhdr EMP IRQ
    g_stHdmiFrlMacRx4IrqStatus.b1DhdrEmpIrqBackup = (ScalerGetBit(P1E_53_EMP_DHDR, _BIT7) >> 7);

    // Disable CED Lock Transition IRQ
    ScalerSetByte(P78_17_HDMI21_FRL_CED_15, 0x00);

    // Disable FRL Transition detection IRQ
    ScalerSetBit(P78_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3), 0x00);

    // Disable RSV0~3 received IRQ
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable Vs EMP IRQ
    ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Dhdr EMP IRQ
    ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : Restore Main link Related IRQ After Z0 on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On(void)
{
    // Clear flag and Restore CED Lock Transition IRQ
    // ScalerSetBit(P78_17_HDMI21_FRL_CED_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    // ScalerSetByte(P78_17_HDMI21_FRL_CED_15, g_stHdmiFrlMacRx4IrqStatus.b4CedLockIrqBackup);

    // Clear flag and Restore FRL Transition detection IRQ
    ScalerSetBit(P78_E6_HDMI_TRANSDET_CTRL2, ~_BIT3, _BIT3);
    ScalerSetBit(P78_E6_HDMI_TRANSDET_CTRL2, ~(_BIT7 | _BIT3), (g_stHdmiFrlMacRx4IrqStatus.b1TransitionDetectIrqBackup << 7));

    // Clear flag and Restore RSV0~3 received IRQ
    ScalerSetByte(P78_CC_HDMI_GPVS, (_BIT6 | _BIT5));
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_00_PORT_PAGE78_HDMI_SCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_B5_PORT_PAGE78_HDMI_BED_FUNC_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_stHdmiFrlMacRx4IrqStatus.b4RsvIrqBackup);

    // Clear flag and Restore Vs EMP IRQ
    ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(P1E_51_EMP_VS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (g_stHdmiFrlMacRx4IrqStatus.b1VsEmpIrqBackup << 7));

    // Clear flag and Restore Dhdr EMP IRQ
    ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(P1E_53_EMP_DHDR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (g_stHdmiFrlMacRx4IrqStatus.b1DhdrEmpIrqBackup << 7));
}
#endif // End for #if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

