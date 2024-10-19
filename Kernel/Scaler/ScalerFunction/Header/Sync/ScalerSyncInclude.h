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
// ID Code      : ScalerSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definition of Margin Link Parameter
//--------------------------------------------------
#if(_DP_MARGIN_LINK_SUPPORT == _ON)
#define _DP_MARGIN_LINK_TIME_CRITERIA                       30
#define _DP_MARGIN_LINK_ERROR_CRITERIA                      10
#endif
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define _INPUT_H_PORCH_EXTEND                               88
#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Measure Clk Source
//--------------------------------------------------
#define _CLK_SOURCE_RED                                     0
#define _CLK_SOURCE_BLUE                                    1
#define _CLK_SOURCE_GREEN                                   2
#define _CLK_SOURCE_TMDS                                    3

//--------------------------------------------------
// Define for Clk Freq Detection
//--------------------------------------------------
#define _TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND            (WORD)((DWORD)600 * 1040 / ((_GDIPHY_RX_GDI_CLK_KHZ * _HW_TMDS_MEASURE_CLOCK_DIVIDER) / _HW_TMDS_MEASURE_CLOCK_COUNTER)) // (600 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)
#define _TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND             (WORD)((DWORD)340 * 1040 / ((_GDIPHY_RX_GDI_CLK_KHZ * _HW_TMDS_MEASURE_CLOCK_DIVIDER) / _HW_TMDS_MEASURE_CLOCK_COUNTER)) // (340 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)
#define _TMDS_FREQ_NORMAL_LOWER_BOUND                       (WORD)((DWORD)_TMDS_CLOCK_MEASURE_LOWER_BOUNDARY * 960 / ((_GDIPHY_RX_GDI_CLK_KHZ * _HW_TMDS_MEASURE_CLOCK_DIVIDER) / _HW_TMDS_MEASURE_CLOCK_COUNTER)) // (25 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)

#define _TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND                (WORD)((DWORD)600 * 1040 * 10 / ((_HW_INTERNAL_OSC_XTAL * _HW_TMDS_MEASURE_CLOCK_DIVIDER) / _HW_TMDS_MEASURE_CLOCK_COUNTER * 9)) // (600 / _TMDS_MEASURE_CLOCK_DIVIDER) * 1.04 * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9)
#define _TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND                 (WORD)((DWORD)340 * 1040 * 10 / ((_HW_INTERNAL_OSC_XTAL * _HW_TMDS_MEASURE_CLOCK_DIVIDER) / _HW_TMDS_MEASURE_CLOCK_COUNTER * 9)) // (340 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9)
#define _TMDS_FREQ_PS_LOWER_BOUND                           (WORD)((DWORD)_TMDS_CLOCK_MEASURE_LOWER_BOUNDARY * 960 * 10 / ((_HW_INTERNAL_OSC_XTAL * _HW_TMDS_MEASURE_CLOCK_DIVIDER) / _HW_TMDS_MEASURE_CLOCK_COUNTER * 11)) // (25 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 1.1)

//--------------------------------------------------
// Define for Video Detect
//--------------------------------------------------
#define _TMDS_VIDEO_DATA_NONE                               0
#define _TMDS_VIDEO_DATA_DE_ONLY                            1
#define _TMDS_VIDEO_DATA_RGBHV                              2

//--------------------------------------------------
// Define for Watch Dog Type
//--------------------------------------------------
#define _HDMI_AVI_INFO_VARIATION_WD                         _BIT0
#define _HDMI_AV_MUTE_WD                                    _BIT1
#define _HDMI_FRL_DPF_FIFO_WD                               _BIT2
#define _HDMI_EMP_TIMEOUT_WD                                _BIT3
#define _TMDS_NO_CLK_WD                                     _BIT4

//--------------------------------------------------
// Define for Packet Type
//--------------------------------------------------
#define _HDMI_3D_FORMAT                                     0x81
#define _HDMI_AVI_INFO_TYPE                                 0x82
#define _HDMI_AUDIO_INFO_TYPE                               0x84
#define _HDMI_GENERAL_CONTROL_TYPE                          0x03

//--------------------------------------------------
// Definitions of MHL Mode for Physical Settings
//--------------------------------------------------
#define _TMDS_24BIT_PHY_SETTING                             0x00
#define _TMDS_MHL_PPMODE_PHY_SETTING                        0x01
#define _TMDS_MHL_ECBUS_PHY_SETTING                         0x02

#if(_HDMI20_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDMI 2.0 SCDC Read Request Done Outcome
//--------------------------------------------------
#define _HDMI20_READ_REQUEST_ACK_DONE                       0x00
#define _HDMI20_READ_REQUEST_ACK_STOP                       0x10
#define _HDMI20_READ_REQUEST_NACK1                          0x20
#define _HDMI20_READ_REQUEST_NACK2                          0x30
#define _HDMI20_READ_REQUEST_NONE                           0x70
#endif // #if(_HDMI20_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of TMDS HPD Time
//--------------------------------------------------
#define _TMDS_HPD_TIME_NONE                                 0
#define _TMDS_HDCP_2_2_HPD_TIME                             1000
#define _TMDS_ACER_HPD_TIME                                 130

//--------------------------------------------------
// TMDS Set Phy delay & retry option
//--------------------------------------------------
#define _TMDS_RETRY_SET_PHY_SUPPORT                         _OFF
#define _TMDS_RETRY_SET_PHY_TIME                            30

//--------------------------------------------------
// Definitions of D only mode H/V front porch
//--------------------------------------------------
#define _TMDS_D_ONLY_MODE_H_FRONT_PORCH                     11
#define _TMDS_D_ONLY_MODE_V_FRONT_PORCH                     1

//--------------------------------------------------
// Define for VSIF Packet Type
//--------------------------------------------------
#define _HDMI_VSIF_TYPE                                     0x81
#endif // #if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Define for HDR Packet Type
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#define _HDR_INFO_TYPE                                      0x87
#endif

//--------------------------------------------------
// Define for Audio Time Stamp Packet Type
//--------------------------------------------------
#define _DP_AUDIO_TIMESTAMP                                 0x01

//--------------------------------------------------
// Definition of DP Measure Polling Time
//--------------------------------------------------
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
#define _DP_MEASURE_POLLING_TIMEOUT                         250   // OOR LOWER_BOUND for V_FREQ >= 5Hz
#else
#define _DP_MEASURE_POLLING_TIMEOUT                         100
#endif

//--------------------------------------------------
// Definition of DP Display Format Parameter
//--------------------------------------------------
#define _DP_SYNC_POLARITY_NEGATIVE                          1
#define _DP_VSYNC_FRONT_PORCH                               4
#define _DP_HSYNC_FRONT_PORCH                               8
#define _DP_VSYNC_FRONT_PORCH_MST2SST                       (WORD)((((WORD)ScalerGetByte(P35_10_MSA_VTTE_0) << 8) | ScalerGetByte(P35_11_MSA_VTTE_1)) - (((WORD)ScalerGetByte(P35_14_MSA_VST_0) << 8) | ScalerGetByte(P35_15_MSA_VST_1)) - (((WORD)ScalerGetByte(P35_16_MSA_VHT_0) << 8) | ScalerGetByte(P35_17_MSA_VHT_1)))
#define _DP_VSYNC_WIDTH                                     3
#define _DP_VSYNC_WIDTH_MST2SST                             (WORD)(((WORD)ScalerGetByte(P35_18_MSA_VSW_0) << 8) | ScalerGetByte(P35_19_MSA_VSW_1))
#define _DP_HSYNC_WIDTH_MEASURE_COUNTER                     2 // = HSW msa * Measure clk / Pixel clk
#define _DP_ONE_FRAME_TIME_MAX                              45 // in ms @ 23Hz
#define _DP_TWO_FRAME_TIME_MAX                              (_DP_ONE_FRAME_TIME_MAX * 2) // in ms @ 23Hz

//--------------------------------------------------
// Definition of DRR mode Display Format Parameter
//--------------------------------------------------
#define _SYNC_POLARITY_POSITIVE                             0
#define _DE_ONLY_MODE_HSW_MEASURE_COUNTER                   2 // = DE only HSW * Measure clk / Pixel clk
#define _DE_ONLY_MODE_HSW                                   20
#define _DE_ONLY_MODE_HSTART                                32
#define _DE_ONLY_MODE_VSW                                   2
#define _DE_ONLY_MODE_VSTART                                8

//--------------------------------------------------
// Definitions of DP Link Training Stage
//--------------------------------------------------
#define _DP_TRAINING_PATTERN_END                            0
#define _DP_TRAINING_PATTERN_1                              1
#define _DP_TRAINING_PATTERN_2                              2
#define _DP_TRAINING_PATTERN_3                              3
#define _DP_TRAINING_PATTERN_4                              7

//--------------------------------------------------
// Definitions of DP Link Traiinng Status
//--------------------------------------------------
#define _DP_LINK_TRAINING_NONE                              0
#define _DP_NORMAL_TRAINING_PATTERN_1_PASS                  1
#define _DP_NORMAL_TRAINING_PATTERN_1_FAIL                  2
#define _DP_FAKE_TRAINING_PATTERN_1_PASS                    3
#define _DP_FAKE_TRAINING_PATTERN_1_FAIL                    4
#define _DP_NORMAL_TRAINING_PATTERN_2_PASS                  5
#define _DP_NORMAL_TRAINING_PATTERN_2_FAIL                  6
#define _DP_FAKE_TRAINING_PATTERN_2_PASS                    7
#define _DP_FAKE_TRAINING_PATTERN_2_FAIL                    8
#define _DP_NORMAL_TRAINING_PATTERN_3_PASS                  9
#define _DP_NORMAL_TRAINING_PATTERN_3_FAIL                  10
#define _DP_FAKE_TRAINING_PATTERN_3_PASS                    11
#define _DP_FAKE_TRAINING_PATTERN_3_FAIL                    12
#define _DP_NORMAL_LINK_TRAINING_PASS                       13
#define _DP_FAKE_LINK_TRAINING_PASS                         14
#define _DP_FAKE_LINK_TRAINING_PASS_VBIOS                   15
#define _DP_LINK_TRAINING_FAIL                              16
#define _DP_LINK_STATUS_FAIL                                17
#define _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY         18

//--------------------------------------------------
// Macro of Link Training Status
//--------------------------------------------------
#define GET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH()     ((bit)g_bSyncDpRx0NormalLTSetPhyFinish)
#define SET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH()     (g_bSyncDpRx0NormalLTSetPhyFinish = _TRUE)
#define CLR_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH()     (g_bSyncDpRx0NormalLTSetPhyFinish = _FALSE)

#define GET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH()     ((bit)g_bSyncDpRx1NormalLTSetPhyFinish)
#define SET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH()     (g_bSyncDpRx1NormalLTSetPhyFinish = _TRUE)
#define CLR_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH()     (g_bSyncDpRx1NormalLTSetPhyFinish = _FALSE)

#define GET_DP_RX2_NORMAL_LINK_TRAINING_SETPHY_FINISH()     ((bit)g_bSyncDpRx2NormalLTSetPhyFinish)
#define SET_DP_RX2_NORMAL_LINK_TRAINING_SETPHY_FINISH()     (g_bSyncDpRx2NormalLTSetPhyFinish = _TRUE)
#define CLR_DP_RX2_NORMAL_LINK_TRAINING_SETPHY_FINISH()     (g_bSyncDpRx2NormalLTSetPhyFinish = _FALSE)

//--------------------------------------------------
// Definitions of DP Aux Setting Initial Value
//--------------------------------------------------
#define _DP_AUX_INITIAL_DIFF_MODE                           1

//--------------------------------------------------
// Definitions of DP HDCP Info
//--------------------------------------------------
#define _DP_HDCP_SHA1_INPUT_SIZE                            64

//--------------------------------------------------
// Macro of Input Pixel Clk (Unit in 0.1MHz)
//--------------------------------------------------
#define GET_A0_INPUT_PIXEL_CLK()                            (g_usSyncA0PixelClk)
#define SET_A0_INPUT_PIXEL_CLK(x)                           (g_usSyncA0PixelClk = (x))
#define CLR_A0_INPUT_PIXEL_CLK()                            (g_usSyncA0PixelClk = 0)

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#define GET_D0_INPUT_PIXEL_CLK()                            (g_usSyncD0PixelClk)
#define SET_D0_INPUT_PIXEL_CLK(x)                           (g_usSyncD0PixelClk = (x))
#define CLR_D0_INPUT_PIXEL_CLK()                            (g_usSyncD0PixelClk = 0)

#define GET_D0_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD0NativePixelClk)
#define SET_D0_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD0NativePixelClk = (x))
#define CLR_D0_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD0NativePixelClk = 0)
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#define GET_D1_INPUT_PIXEL_CLK()                            (g_usSyncD1PixelClk)
#define SET_D1_INPUT_PIXEL_CLK(x)                           (g_usSyncD1PixelClk = (x))
#define CLR_D1_INPUT_PIXEL_CLK()                            (g_usSyncD1PixelClk = 0)

#define GET_D1_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD1NativePixelClk)
#define SET_D1_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD1NativePixelClk = (x))
#define CLR_D1_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD1NativePixelClk = 0)
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#define GET_D2_INPUT_PIXEL_CLK()                            (g_usSyncD2PixelClk)
#define SET_D2_INPUT_PIXEL_CLK(x)                           (g_usSyncD2PixelClk = (x))
#define CLR_D2_INPUT_PIXEL_CLK()                            (g_usSyncD2PixelClk = 0)

#define GET_D2_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD2NativePixelClk)
#define SET_D2_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD2NativePixelClk = (x))
#define CLR_D2_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD2NativePixelClk = 0)
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#define GET_D3_INPUT_PIXEL_CLK()                            (g_usSyncD3PixelClk)
#define SET_D3_INPUT_PIXEL_CLK(x)                           (g_usSyncD3PixelClk = (x))
#define CLR_D3_INPUT_PIXEL_CLK()                            (g_usSyncD3PixelClk = 0)

#define GET_D3_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD3NativePixelClk)
#define SET_D3_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD3NativePixelClk = (x))
#define CLR_D3_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD3NativePixelClk = 0)
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#define GET_D4_INPUT_PIXEL_CLK()                            (g_usSyncD4PixelClk)
#define SET_D4_INPUT_PIXEL_CLK(x)                           (g_usSyncD4PixelClk = (x))
#define CLR_D4_INPUT_PIXEL_CLK()                            (g_usSyncD4PixelClk = 0)

#define GET_D4_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD4NativePixelClk)
#define SET_D4_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD4NativePixelClk = (x))
#define CLR_D4_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD4NativePixelClk = 0)
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#define GET_D5_INPUT_PIXEL_CLK()                            (g_usSyncD5PixelClk)
#define SET_D5_INPUT_PIXEL_CLK(x)                           (g_usSyncD5PixelClk = (x))
#define CLR_D5_INPUT_PIXEL_CLK()                            (g_usSyncD5PixelClk = 0)

#define GET_D5_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD5NativePixelClk)
#define SET_D5_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD5NativePixelClk = (x))
#define CLR_D5_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD5NativePixelClk = 0)
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
#define GET_D9_INPUT_PIXEL_CLK()                            (g_usSyncD9PixelClk)
#define SET_D9_INPUT_PIXEL_CLK(x)                           (g_usSyncD9PixelClk = (x))
#define CLR_D9_INPUT_PIXEL_CLK()                            (g_usSyncD9PixelClk = 0)

#define GET_D9_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD9NativePixelClk)
#define SET_D9_NATIVE_INPUT_PIXEL_CLK(x)                    (g_usSyncD9NativePixelClk = (x))
#define CLR_D9_NATIVE_INPUT_PIXEL_CLK()                     (g_usSyncD9NativePixelClk = 0)
#endif
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Digital Input Port Switch
//--------------------------------------------------
/*
#define GET_D0_PORT_DIGITAL_SWITCH()                         ((g_ucDigitalSwitch & _BIT7) >> 7)
#define SET_D0_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch |= _BIT7)
#define CLR_D0_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch &= ~_BIT7)

#define GET_D1_PORT_DIGITAL_SWITCH()                         ((g_ucDigitalSwitch & _BIT6) >> 6)
#define SET_D1_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch |= _BIT6)
#define CLR_D1_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch &= ~_BIT6)
*/

#define GET_DIGITAL_PORT_SWITCH_TO_D0()                     ((g_ucSyncDigitalSwitch & _BIT5) >> 5)
#define SET_DIGITAL_PORT_SWITCH_TO_D0()                     (g_ucSyncDigitalSwitch |= _BIT5)
#define CLR_DIGITAL_PORT_SWITCH_TO_D0()                     (g_ucSyncDigitalSwitch &= ~_BIT5)

#define GET_DIGITAL_PORT_SWITCH_TO_D1()                     ((g_ucSyncDigitalSwitch & _BIT4) >> 4)
#define SET_DIGITAL_PORT_SWITCH_TO_D1()                     (g_ucSyncDigitalSwitch |= _BIT4)
#define CLR_DIGITAL_PORT_SWITCH_TO_D1()                     (g_ucSyncDigitalSwitch &= ~_BIT4)

#define GET_DIGITAL_PORT_SWITCH_TO_D2()                     ((g_ucSyncDigitalSwitch & _BIT3) >> 3)
#define SET_DIGITAL_PORT_SWITCH_TO_D2()                     (g_ucSyncDigitalSwitch |= _BIT3)
#define CLR_DIGITAL_PORT_SWITCH_TO_D2()                     (g_ucSyncDigitalSwitch &= ~_BIT3)

#define GET_DIGITAL_PORT_SWITCH_TO_D3()                     ((g_ucSyncDigitalSwitch & _BIT2) >> 2)
#define SET_DIGITAL_PORT_SWITCH_TO_D3()                     (g_ucSyncDigitalSwitch |= _BIT2)
#define CLR_DIGITAL_PORT_SWITCH_TO_D3()                     (g_ucSyncDigitalSwitch &= ~_BIT2)

#define GET_DIGITAL_PORT_SWITCH_TO_D4()                     ((g_ucSyncDigitalSwitch & _BIT1) >> 1)
#define SET_DIGITAL_PORT_SWITCH_TO_D4()                     (g_ucSyncDigitalSwitch |= _BIT1)
#define CLR_DIGITAL_PORT_SWITCH_TO_D4()                     (g_ucSyncDigitalSwitch &= ~_BIT1)

#define GET_DIGITAL_PORT_SWITCH_TO_D5()                     ((g_ucSyncDigitalSwitch & _BIT0) >> 0)
#define SET_DIGITAL_PORT_SWITCH_TO_D5()                     (g_ucSyncDigitalSwitch |= _BIT0)
#define CLR_DIGITAL_PORT_SWITCH_TO_D5()                     (g_ucSyncDigitalSwitch &= ~_BIT0)

#define GET_DIGITAL_PORT_SWITCH_TO_D6()                     ((g_ucSyncDigitalSwitch & _BIT6) >> 0)
#define SET_DIGITAL_PORT_SWITCH_TO_D6()                     (g_ucSyncDigitalSwitch |= _BIT6)
#define CLR_DIGITAL_PORT_SWITCH_TO_D6()                     (g_ucSyncDigitalSwitch &= ~_BIT6)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP Marginal Link
//--------------------------------------------------
#if(_DP_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D0_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D0MarginLink)
#define SET_DP_RX_D0_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D0MarginLink = _TRUE)
#define CLR_DP_RX_D0_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D0MarginLink = _FALSE)
#endif

#define GET_DP_RX_D0_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane0MarginLinkTP1)
#define SET_DP_RX_D0_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane0MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D0_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane0MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D0_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane1MarginLinkTP1)
#define SET_DP_RX_D0_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane1MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D0_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane1MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D0_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane2MarginLinkTP1)
#define SET_DP_RX_D0_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane2MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D0_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane2MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D0_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane3MarginLinkTP1)
#define SET_DP_RX_D0_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane3MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D0_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D0Lane3MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D0_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane0MarginLinkTP2)
#define SET_DP_RX_D0_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane0MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D0_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane0MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D0_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane1MarginLinkTP2)
#define SET_DP_RX_D0_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane1MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D0_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane1MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D0_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane2MarginLinkTP2)
#define SET_DP_RX_D0_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane2MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D0_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane2MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D0_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane3MarginLinkTP2)
#define SET_DP_RX_D0_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane3MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D0_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D0Lane3MarginLinkTP2 = _FALSE)

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D1_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D1MarginLink)
#define SET_DP_RX_D1_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D1MarginLink = _TRUE)
#define CLR_DP_RX_D1_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D1MarginLink = _FALSE)
#endif

#define GET_DP_RX_D1_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane0MarginLinkTP1)
#define SET_DP_RX_D1_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane0MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D1_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane0MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D1_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane1MarginLinkTP1)
#define SET_DP_RX_D1_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane1MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D1_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane1MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D1_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane2MarginLinkTP1)
#define SET_DP_RX_D1_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane2MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D1_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane2MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D1_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane3MarginLinkTP1)
#define SET_DP_RX_D1_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane3MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D1_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D1Lane3MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D1_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane0MarginLinkTP2)
#define SET_DP_RX_D1_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane0MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D1_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane0MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D1_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane1MarginLinkTP2)
#define SET_DP_RX_D1_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane1MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D1_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane1MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D1_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane2MarginLinkTP2)
#define SET_DP_RX_D1_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane2MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D1_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane2MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D1_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane3MarginLinkTP2)
#define SET_DP_RX_D1_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane3MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D1_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D1Lane3MarginLinkTP2 = _FALSE)

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D2_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D2MarginLink)
#define SET_DP_RX_D2_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D2MarginLink = _TRUE)
#define CLR_DP_RX_D2_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D2MarginLink = _FALSE)
#endif

#define GET_DP_RX_D2_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane0MarginLinkTP1)
#define SET_DP_RX_D2_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane0MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane0MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D2_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane1MarginLinkTP1)
#define SET_DP_RX_D2_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane1MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D2_LANE1_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane1MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D2_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane2MarginLinkTP1)
#define SET_DP_RX_D2_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane2MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D2_LANE2_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane2MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D2_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane3MarginLinkTP1)
#define SET_DP_RX_D2_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane3MarginLinkTP1 = _TRUE)
#define CLR_DP_RX_D2_LANE3_MARGIN_LINK_TP1()                (g_stSyncDpMarginLink.b1D2Lane3MarginLinkTP1 = _FALSE)

#define GET_DP_RX_D2_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane0MarginLinkTP2)
#define SET_DP_RX_D2_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane0MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D2_LANE0_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane0MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D2_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane1MarginLinkTP2)
#define SET_DP_RX_D2_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane1MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D2_LANE1_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane1MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D2_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane2MarginLinkTP2)
#define SET_DP_RX_D2_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane2MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D2_LANE2_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane2MarginLinkTP2 = _FALSE)

#define GET_DP_RX_D2_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane3MarginLinkTP2)
#define SET_DP_RX_D2_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane3MarginLinkTP2 = _TRUE)
#define CLR_DP_RX_D2_LANE3_MARGIN_LINK_TP2()                (g_stSyncDpMarginLink.b1D2Lane3MarginLinkTP2 = _FALSE)

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D6_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D6MarginLink)
#define SET_DP_RX_D6_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D6MarginLink = _TRUE)
#define CLR_DP_RX_D6_MARGIN_LINK()                          (g_stSyncDpMarginLink.b1D6MarginLink = _FALSE)
#endif
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
#define GET_RX3_COLOR_SPACE_PREVALUE()                      (g_stSyncD3ColorInfo.ucDigitalColorSpacePreValue)
#define SET_RX3_COLOR_SPACE_PREVALUE(X)                     (g_stSyncD3ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_RX3_COLOR_DEPTH_PREVALUE()                      (g_stSyncD3ColorInfo.b3DigitalColorDepthPreValue)
#define SET_RX3_COLOR_DEPTH_PREVALUE(X)                     (g_stSyncD3ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_RX3_CONTENT_TYPE()                              (g_stSyncD3ColorInfo.b3DigitalContentType)
#define SET_RX3_CONTENT_TYPE(X)                             (g_stSyncD3ColorInfo.b3DigitalContentType = (X))

#define GET_RX3_COLORIMETRY_PREVALUE()                      (g_stSyncD3ColorInfo.b4DigitalColorimetryPreValue)
#define SET_RX3_COLORIMETRY_PREVALUE(X)                     (g_stSyncD3ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_RX3_COLORIMETRY_EXT_PREVALUE()                  (g_stSyncD3ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_RX3_COLORIMETRY_EXT_PREVALUE(X)                 (g_stSyncD3ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_RX3_COLORIMETRY_ADD_EXT_PREVALUE()              (g_stSyncD3ColorInfo.b4DigitalColorimetryAddExtPreValue)
#define SET_RX3_COLORIMETRY_ADD_EXT_PREVALUE(X)             (g_stSyncD3ColorInfo.b4DigitalColorimetryAddExtPreValue = (X))

#define GET_RX3_QUANTIZATION_PREVALUE()                     (g_stSyncD3ColorInfo.b2DigitalQuantizationPreValue)
#define SET_RX3_QUANTIZATION_PREVALUE(X)                    (g_stSyncD3ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_RX3_COLORIMETRY_CHANGED()                       (g_stSyncD3ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_RX3_COLORIMETRY_CHANGED()                       (g_stSyncD3ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_RX3_COLORIMETRY_CHANGED()                       (g_stSyncD3ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_RX3_COLORIMETRY_EXT_CHANGED()                   (g_stSyncD3ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_RX3_COLORIMETRY_EXT_CHANGED()                   (g_stSyncD3ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_RX3_COLORIMETRY_EXT_CHANGED()                   (g_stSyncD3ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_RX3_QUANTIZATION_CHANGED()                      (g_stSyncD3ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_RX3_QUANTIZATION_CHANGED()                      (g_stSyncD3ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_RX3_QUANTIZATION_CHANGED()                      (g_stSyncD3ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
#define GET_RX4_COLOR_SPACE_PREVALUE()                      (g_stSyncD4ColorInfo.ucDigitalColorSpacePreValue)
#define SET_RX4_COLOR_SPACE_PREVALUE(X)                     (g_stSyncD4ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_RX4_COLOR_DEPTH_PREVALUE()                      (g_stSyncD4ColorInfo.b3DigitalColorDepthPreValue)
#define SET_RX4_COLOR_DEPTH_PREVALUE(X)                     (g_stSyncD4ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_RX4_CONTENT_TYPE()                              (g_stSyncD4ColorInfo.b3DigitalContentType)
#define SET_RX4_CONTENT_TYPE(X)                             (g_stSyncD4ColorInfo.b3DigitalContentType = (X))

#define GET_RX4_COLORIMETRY_PREVALUE()                      (g_stSyncD4ColorInfo.b4DigitalColorimetryPreValue)
#define SET_RX4_COLORIMETRY_PREVALUE(X)                     (g_stSyncD4ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_RX4_COLORIMETRY_EXT_PREVALUE()                  (g_stSyncD4ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_RX4_COLORIMETRY_EXT_PREVALUE(X)                 (g_stSyncD4ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_RX4_COLORIMETRY_ADD_EXT_PREVALUE()              (g_stSyncD4ColorInfo.b4DigitalColorimetryAddExtPreValue)
#define SET_RX4_COLORIMETRY_ADD_EXT_PREVALUE(X)             (g_stSyncD4ColorInfo.b4DigitalColorimetryAddExtPreValue = (X))

#define GET_RX4_QUANTIZATION_PREVALUE()                     (g_stSyncD4ColorInfo.b2DigitalQuantizationPreValue)
#define SET_RX4_QUANTIZATION_PREVALUE(X)                    (g_stSyncD4ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_RX4_COLORIMETRY_CHANGED()                       (g_stSyncD4ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_RX4_COLORIMETRY_CHANGED()                       (g_stSyncD4ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_RX4_COLORIMETRY_CHANGED()                       (g_stSyncD4ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_RX4_COLORIMETRY_EXT_CHANGED()                   (g_stSyncD4ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_RX4_COLORIMETRY_EXT_CHANGED()                   (g_stSyncD4ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_RX4_COLORIMETRY_EXT_CHANGED()                   (g_stSyncD4ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_RX4_QUANTIZATION_CHANGED()                      (g_stSyncD4ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_RX4_QUANTIZATION_CHANGED()                      (g_stSyncD4ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_RX4_QUANTIZATION_CHANGED()                      (g_stSyncD4ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if((_DM_FUNCTION == _ON) && (_HDMI21_ALLM_SUPPORT == _ON))

#if(_D3_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI D3 ALLM Enable (DM Use for Gaming mode)
//--------------------------------------------------
#define GET_D3_DM_ALLM_ENABLED()                            ((g_stSyncHdmiDmAllmEnabled.ucD3HdmiDmAllmEnabled) != _DISABLE)
#define SET_D3_DM_ALLM_ENABLED()                            (g_stSyncHdmiDmAllmEnabled.ucD3HdmiDmAllmEnabled = _ENABLE)
#define CLR_D3_DM_ALLM_ENABLED()                            (g_stSyncHdmiDmAllmEnabled.ucD3HdmiDmAllmEnabled = _DISABLE)
#endif

#if(_D4_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI D3 ALLM Enable (DM Use for Gaming mode)
//--------------------------------------------------
#define GET_D4_DM_ALLM_ENABLED()                            ((g_stSyncHdmiDmAllmEnabled.ucD4HdmiDmAllmEnabled) != _DISABLE)
#define SET_D4_DM_ALLM_ENABLED()                            (g_stSyncHdmiDmAllmEnabled.ucD4HdmiDmAllmEnabled = _ENABLE)
#define CLR_D4_DM_ALLM_ENABLED()                            (g_stSyncHdmiDmAllmEnabled.ucD4HdmiDmAllmEnabled = _DISABLE)
#endif
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX_HDCP_UPSTREAM_PORT()                      (g_stSyncDpTxStatus.b2HdcpUpstreamPort)
#define SET_DP_RX_HDCP_UPSTREAM_PORT(x)                     (g_stSyncDpTxStatus.b2HdcpUpstreamPort = (x))

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_RX_HDCP2_UPSTREAM_PORT()                     (g_stSyncDpTxStatus.b2Hdcp2UpstreamPort)
#define SET_DP_RX_HDCP2_UPSTREAM_PORT(x)                    (g_stSyncDpTxStatus.b2Hdcp2UpstreamPort = (x))
#endif
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
#define GET_URGENT_EVENT_OCCUR_FLG()                        (g_ucSyncCheckUrgentEventOccured)
#define SET_URGENT_EVENT_OCCUR_FLG()                        (g_ucSyncCheckUrgentEventOccured = _TRUE)
#define CLR_URGENT_EVENT_OCCUR_FLG()                        (g_ucSyncCheckUrgentEventOccured = _FALSE)
#endif

//--------------------------------------------------
// Definitions of Get HDR10 Data
//--------------------------------------------------
#if((_HDMI_HDR10_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
#define GET_TMDSRX3_HDR10_DATA(x)                           (ScalerTmdsMacRx3GetHDR10Data(x))
#define GET_TMDSRX4_HDR10_DATA(x)                           (ScalerTmdsMacRx4GetHDR10Data(x))
#endif

//--------------------------------------------------
// Definitions of Get HDR10 SBTM Data
//--------------------------------------------------
#if(_HDMI_SBTM_SUPPORT == _ON)
#define GET_TMDSRX3_HDR10_SBTM_DATA(x)                      (ScalerTmdsMacRx3GetSBTMData(x))
#define GET_TMDSRX4_HDR10_SBTM_DATA(x)                      (ScalerTmdsMacRx4GetSBTMData(x))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Struct of Interface Vertical Timing Info
//--------------------------------------------------
typedef struct
{
    WORD usVStart;
    WORD usVActive;
    WORD usVTotal;
} StructInterfaceTimingInfo;

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of AVI Info Content Types
//--------------------------------------------------
typedef enum
{
    _AVI_COLOR_SPACE_RGB = 0x00,
    _AVI_COLOR_SPACE_YCC_422 = 0x01,
    _AVI_COLOR_SPACE_YCC_444 = 0x02,
    _AVI_COLOR_SPACE_YCC_420 = 0x03,
    _AVI_COLOR_SPACE_RESERVED = 0x04,
} EnumAviInfoColorSpace;

typedef enum
{
    _AVI_COLORIMETRY_NONE = 0x00,
    _AVI_COLORIMETRY_ITU601 = 0x01,
    _AVI_COLORIMETRY_ITU709 = 0x02,
    _AVI_COLORIMETRY_EXTENDED = 0x03,
} EnumAviInfoColorimetry;


typedef enum
{
    _AVI_COLORIMETRY_EXT_XVYCC601 = 0x00,
    _AVI_COLORIMETRY_EXT_XVYCC709 = 0x01,
    _AVI_COLORIMETRY_EXT_SYCC601 = 0x02,
    _AVI_COLORIMETRY_EXT_ADOBEYCC601 = 0x03,
    _AVI_COLORIMETRY_EXT_ADOBERGB = 0x04,
    _AVI_COLORIMETRY_EXT_ITUR_BT2020_1 = 0x05,
    _AVI_COLORIMETRY_EXT_ITUR_BT2020_2 = 0x06,
    _AVI_COLORIMETRY_EXT_ADD_EXTENDED = 0x07,
} EnumAviInfoColorimetryExt;

typedef enum
{
    _AVI_COLORIMETRY_ADD_EXT_SMPTE_ST2113_P3D65 = 0x00,
    _AVI_COLORIMETRY_ADD_EXT_SMPTE_ST2113_P3DCI = 0x01,
    _AVI_COLORIMETRY_ADD_EXT_ITUR_BT2100 = 0x02,
} EnumAviInfoColorimetryAddExt;

typedef struct
{
    WORD usFramRate;
    BYTE b5AviRateIdx : 5;
    BYTE b3FrameRateGroup : 3;
} StructHdmiCtaFrTableParas;

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Structure of TMDS Control Definitions
//--------------------------------------------------
typedef struct
{
    BYTE b1RGBHVDetecting : 1;
    BYTE b1PacketDetecting : 1;
    BYTE b1AdvancedHdr10Detecting : 1;
    BYTE b1DhdrEmpType40Received : 1;
    BYTE b1AdvancedHdr10VsifReceived : 1;
    BYTE b1HFVsifReceived : 1;
    BYTE b1AVIInfoFrameReceived : 1;
    BYTE b1GCPReceived : 1;
    BYTE b1Z0Asserted : 1;
#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
    BYTE b1BedError : 1;
#endif

    BYTE b1TMDSPhySet : 1;
#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
    BYTE b1TmdsRetrySetPhy : 1;
#endif
    BYTE b1TMDSHpdResetSearchEvent : 1;

#if(_HDMI20_SUPPORT == _ON)
    BYTE b1HDMI2FormatResetWaiting : 1;
    BYTE b1HDMI2RREnable : 1;
    BYTE b1HDMI2HighSpeedMode : 1;
#endif

#if((_HDR10_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
    BYTE b1HDRInfoFrameReceived : 1;
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
    BYTE b1Hdmi21AllmEnable : 1;
#endif

    EnumTMDSHpdEventType enumHpdEvent;

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
    BYTE b1HdmiInterfaceSwitching : 1;
#endif

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    BYTE b1HdmiAcOnHpdToggleEvent : 1;
#endif

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
    BYTE b1HdmiHpdToggling : 1;
#endif

#if((_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON) || (_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON))
    BYTE b1HdmiHpdTogglingCableOn : 1;
#endif

#if(_DM_FUNCTION == _ON)
    BYTE b1DmVsifReceived : 1;
    BYTE b1DmInfoDetecting : 1;
    BYTE b1DmEmpReceived : 1;
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
    BYTE b1HdmiVsifReceived : 1;
    BYTE b13dVideoValid : 1;
    // BYTE b13dVideoType : 1;
#endif
} StructTMDSCtrlInfo;

#if((_DM_FUNCTION == _ON) && (_HDMI21_ALLM_SUPPORT == _ON))
typedef struct
{
#if(_D3_HDMI_SUPPORT == _ON)
    BYTE ucD3HdmiDmAllmEnabled;
#endif
#if(_D4_HDMI_SUPPORT == _ON)
    BYTE ucD4HdmiDmAllmEnabled;
#endif
} StructHdmiDmAllmEnableStatus;
#endif

#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Struct of HDMI Rx PS Wakeup HPD Toggle
//--------------------------------------------------
typedef struct
{
    BYTE b1Rx2PsWakeupHpd : 1;
    BYTE b1Rx3PsWakeupHpd : 1;
    BYTE b1Rx4PsWakeupHpd : 1;
    BYTE b1Rx5PsWakeupHpd : 1;
} StructHdmiRxPsWakeupHpd;

//--------------------------------------------------
// Definitions of AVI Info Content Types
//--------------------------------------------------
typedef enum
{
    _AVI_COLOR_SPACE_00 = _AVI_COLOR_SPACE_RGB,
    _AVI_COLOR_SPACE_01 = _AVI_COLOR_SPACE_YCC_422,
    _AVI_COLOR_SPACE_10 = _AVI_COLOR_SPACE_YCC_444,
    _AVI_COLOR_SPACE_11 = _AVI_COLOR_SPACE_YCC_420,
    _AVI_COLOR_SPACE_KERNEL_RESERVED = 0x04,
} EnumAviInfoColorSpaceKernel;

typedef enum
{
    _AVI_COLORIMETRY_00 = _AVI_COLORIMETRY_NONE,
    _AVI_COLORIMETRY_01 = _AVI_COLORIMETRY_ITU601,
    _AVI_COLORIMETRY_10 = _AVI_COLORIMETRY_ITU709,
    _AVI_COLORIMETRY_11 = _AVI_COLORIMETRY_EXTENDED,
} EnumAviInfoColorimetryKernel;

typedef enum
{
    _AVI_COLORIMETRY_EXT_000 = _AVI_COLORIMETRY_EXT_XVYCC601,
    _AVI_COLORIMETRY_EXT_001 = _AVI_COLORIMETRY_EXT_XVYCC709,
    _AVI_COLORIMETRY_EXT_010 = _AVI_COLORIMETRY_EXT_SYCC601,
    _AVI_COLORIMETRY_EXT_011 = _AVI_COLORIMETRY_EXT_ADOBEYCC601,
    _AVI_COLORIMETRY_EXT_100 = _AVI_COLORIMETRY_EXT_ADOBERGB,
    _AVI_COLORIMETRY_EXT_101 = _AVI_COLORIMETRY_EXT_ITUR_BT2020_1,
    _AVI_COLORIMETRY_EXT_110 = _AVI_COLORIMETRY_EXT_ITUR_BT2020_2,
    _AVI_COLORIMETRY_EXT_111 = _AVI_COLORIMETRY_EXT_ADD_EXTENDED,
} EnumAviInfoColorimetryExtKernel;

typedef enum
{
    _AVI_COLORIMETRY_ADD_EXT_0000 = _AVI_COLORIMETRY_ADD_EXT_SMPTE_ST2113_P3D65,
    _AVI_COLORIMETRY_ADD_EXT_0001 = _AVI_COLORIMETRY_ADD_EXT_SMPTE_ST2113_P3DCI,
    _AVI_COLORIMETRY_ADD_EXT_0010 = _AVI_COLORIMETRY_ADD_EXT_ITUR_BT2100,
} EnumAviInfoColorimetryAddExtKernel;

#endif

//--------------------------------------------------
// Definitions of Digital Color Info Change
//--------------------------------------------------
typedef struct
{
    BYTE b1DigitalColorimetryChanged : 1;
    BYTE b1DigitalColorimetryExtChanged : 1;
    BYTE b1DigitalQuantizationChanged : 1;
} StructDigitalColorInfoChanged;

//--------------------------------------------------
// Definitions of Digital Color Info PreValue
//--------------------------------------------------
typedef struct
{
    BYTE ucDigitalColorSpacePreValue;
    BYTE b4DigitalColorimetryPreValue : 4;
    BYTE b4DigitalColorimetryExtPreValue : 4;
    BYTE b4DigitalColorimetryAddExtPreValue : 4;
    EnumColorSpace enumDigitalColorSpace;
    EnumColorimetry enumDigitalColorimetry;
    EnumColorimetryExt enumDigitalColorimetryExt;
    BYTE b3DigitalColorDepthPreValue : 3;
    BYTE b2DigitalQuantizationPreValue : 2;
    BYTE b3DigitalContentType : 3;
    BYTE ucDigitalColorDepthValue;
    EnumColorYCCQuantization enumDigitalColorYCCQuantization;
    EnumColorRGBQuantization enumDigitalColorRGBQuantization;
} StructDigitalColorInfo;

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of VSC Color Format Types
//--------------------------------------------------
typedef enum
{
    _VSC_COLOR_SPACE_0 = 0x00,
    _VSC_COLOR_SPACE_1 = 0x10,
    _VSC_COLOR_SPACE_2 = 0x20,
    _VSC_COLOR_SPACE_3 = 0x30,
    _VSC_COLOR_SPACE_4 = 0x40,
    _VSC_COLOR_SPACE_5 = 0x50,
} EnumVscColorSpace;

typedef enum
{
    _VSC_COLORIMETRY_0 = 0x00,
    _VSC_COLORIMETRY_1 = 0x01,
    _VSC_COLORIMETRY_2 = 0x02,
    _VSC_COLORIMETRY_3 = 0x03,
    _VSC_COLORIMETRY_4 = 0x04,
    _VSC_COLORIMETRY_5 = 0x05,
    _VSC_COLORIMETRY_6 = 0x06,
    _VSC_COLORIMETRY_7 = 0x07,
} EnumVscColorimetry;

//--------------------------------------------------
// Definitions of DP Color Quantization Types
//--------------------------------------------------
typedef enum
{
    _DP_COLOR_QUANTIZATION_FULL = 0x00,
    _DP_COLOR_QUANTIZATION_LIMIT = 0x01,
} EnumDPColorQuantization;
#endif // End of #if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Enumerations of DP HDCP B Status Type
//--------------------------------------------------
typedef enum
{
    _DP_HDCP_BSTATUS_V_READY = _BIT0,
    _DP_HDCP_BSTATUS_R0_AVAILABLE = _BIT1,
    _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL = _BIT2,
    _DP_HDCP_BSTATUS_REAUTH_REQ = _BIT3,
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    _DP_HDCP2_H_PRIME_AVAILABLE = _BIT4,
    _DP_HDCP2_PARING_AVAILABLE = _BIT5,
    _DP_HDCP2_V_READY = _BIT6,
    _DP_HDCP2_RXSTATUS_REAUTH_REQ = _BIT7,
#endif
} EnumDpRxBStatusType;

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of HDCP Rx Port
//--------------------------------------------------
typedef enum
{
    _HDCP_NO_PORT,
    _HDCP_D0_PORT,
    _HDCP_D1_PORT,
    _HDCP_D2_PORT,
} EnumDpHdcpUpstreamPort;

typedef struct
{
    BYTE b1CloneModeCap : 1;
    BYTE ucCloneDataPath;
    BYTE ucClonePreCheck;
    EnumDpStreamInfoType enumCloneInfoType;
    EnumInputPort enumcCloneInputPort;
    EnumPortType enumPortType;
} StructCloneModeSwitchInfo;

//--------------------------------------------------
// Definitions for DP Tx
//--------------------------------------------------
typedef struct
{
    EnumDpHdcpUpstreamPort b2HdcpUpstreamPort : 2;
    EnumDpHdcpUpstreamPort b2Hdcp2UpstreamPort : 2;
} StructDPTxStatusInfo;

#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

typedef enum
{
    _DP_INFO_RSV0_DB0 = 0x21,
    _DP_INFO_RSV0_DB1 = 0x22,
    _DP_INFO_RSV0_DB2 = 0x23,
    _DP_INFO_RSV0_DB3 = 0x24,
    _DP_INFO_RSV0_DB4 = 0x25,
    _DP_INFO_RSV0_DB5 = 0x26,
    _DP_INFO_RSV0_DB6 = 0x27,
    _DP_INFO_RSV0_DB7 = 0x28,
    _DP_INFO_RSV0_DB8 = 0x29,
    _DP_INFO_RSV0_DB9 = 0x2A,
    _DP_INFO_RSV0_DB10 = 0x2B,
    _DP_INFO_RSV0_DB11 = 0x2C,
    _DP_INFO_RSV0_DB12 = 0x2D,
    _DP_INFO_RSV0_DB13 = 0x2E,
    _DP_INFO_RSV0_DB14 = 0x2F,
    _DP_INFO_RSV0_DB15 = 0x30,
    _DP_INFO_RSV0_DB16 = 0x31,
    _DP_INFO_RSV0_DB17 = 0x32,
    _DP_INFO_RSV0_DB18 = 0x33,
    _DP_INFO_RSV0_DB19 = 0x34,
    _DP_INFO_RSV0_DB20 = 0x35,
    _DP_INFO_RSV0_DB21 = 0x36,
    _DP_INFO_RSV0_DB22 = 0x37,
    _DP_INFO_RSV0_DB23 = 0x38,
    _DP_INFO_RSV0_DB24 = 0x39,
    _DP_INFO_RSV0_DB25 = 0x3A,
    _DP_INFO_RSV0_DB26 = 0x3B,
    _DP_INFO_RSV0_DB27 = 0x3C,
}EnumDPInfoFrameRSV0;

//--------------------------------------------------
// Definitions of DP SDP Packet Type
//--------------------------------------------------
typedef enum
{
    _DP_SDP_TYPE_AUD_TIMESTAMP = 0x01,
    _DP_SDP_TYPE_AUD_STREAM,
    _DP_SDP_TYPE_EXTENSION = 0x04,
    _DP_SDP_TYPE_AUD_COPYMANAGEMENT,
    _DP_SDP_TYPE_ISRC,
    _DP_SDP_TYPE_VSC,
    _DP_SDP_TYPE_CAM_GEN_0,
    _DP_SDP_TYPE_CAM_GEN_1,
    _DP_SDP_TYPE_CAM_GEN_2,
    _DP_SDP_TYPE_CAM_GEN_3,
    _DP_SDP_TYPE_CAM_GEN_4,
    _DP_SDP_TYPE_CAM_GEN_5,
    _DP_SDP_TYPE_CAM_GEN_6,
    _DP_SDP_TYPE_CAM_GEN_7,
    _DP_SDP_TYPE_PPS,
    _DP_SDP_TYPE_VSC_EXT_VESA = 0x20,
    _DP_SDP_TYPE_VSC_EXT_CEA,
    _DP_SDP_TYPE_ADAPTIVESYNC,
    _DP_SDP_TYPE_INFOFRAME_RSV = 0x80,
    _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC,
    _DP_SDP_TYPE_INFOFRAME_AVI,
    _DP_SDP_TYPE_INFOFRAME_SPD,
    _DP_SDP_TYPE_INFOFRAME_AUDIO,
    _DP_SDP_TYPE_INFOFRAME_MPEG,
    _DP_SDP_TYPE_INFOFRAME_NTSC_VBI,
    _DP_SDP_TYPE_INFOFRAME_HDR = 0x87,
}EnumDpSdpType;

//--------------------------------------------------
// Definitions of DP SDP Packet Type
//--------------------------------------------------
typedef enum
{
    _DP_SDP_META_0 = 0x00,
    _DP_SDP_META_1,
    _DP_SDP_META_2,
    _DP_SDP_META_3,
    _DP_SDP_META_4,
}EnumDpSdpMetaIndex;

//--------------------------------------------------
// Enumerations of Infoframe SDP Buff
//--------------------------------------------------
typedef enum
{
    _DP_SDP_BUFF_NONE,
    _DP_SDP_BUFF_SPD,
    _DP_SDP_BUFF_HDR,
    _DP_SDP_BUFF_ISRC,
    _DP_SDP_BUFF_RSV0,
    _DP_SDP_BUFF_RSV1,
    _DP_SDP_BUFF_NUM,
    _DP_SDP_BUFF_VSC,
    _DP_SDP_BUFF_ADAPTIVESYNC,
    _DP_SDP_BUFF_PPS,
} EnumDpSdpRamIndex;

//--------------------------------------------------
// Enumerations of Infoframe SDP Version
//--------------------------------------------------
typedef enum
{
    _INFOFRAME_SDP_VERSION_1_1 = 0x11,
    _INFOFRAME_SDP_VERSION_1_2 = 0x12,
    _INFOFRAME_SDP_VERSION_1_3 = 0x13,
} EnumInfoframeSdpVersion;

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Enum for HDR
//--------------------------------------------------
typedef enum
{
    _HDR10_INFO_HDMI_VERSION = 0x20,
    _HDR10_INFO_HDMI_LENGTH = 0x21,
    _HDR10_INFO_HDMI_CHECKSUM = 0x22,

    // A:chg_
    _HDR10_INFO_HDMI_EOTF = 0x23,

    // B_
    _HDR10_INFO_HDMI_STATIC_METADATA_DESCRIPTOR_ID = 0x24,

    // C:chg
    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB = 0x25,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_Y0_LSB = 0x27,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X1_LSB = 0x29,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_Y1_LSB = 0x2B,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X2_LSB = 0x2D,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_Y2_LSB = 0x2F,

    _HDR10_INFO_HDMI_WHITE_POINT_X_LSB = 0x31,

    _HDR10_INFO_HDMI_WHITE_POINT_Y_LSB = 0x33,

    // D:chg
    _HDR10_INFO_HDMI_MAX_LUMINANCE_LSB = 0x35,

    // E
    _HDR10_INFO_HDMI_MIN_LUMINANCE_LSB = 0x37,

    // F
    _HDR10_INFO_HDMI_MAX_CLL_LSB = 0x39,

    // G
    _HDR10_INFO_HDMI_MAX_FALL_LSB = 0x3B,
}EnumHdr10MasteringInfoFrameTMDSRSV3;
#endif

//--------------------------------------------------
//HDCP RX Reset DPCD Field
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_REAUTH = 0,
    _DP_RX_HDCP_UNPLUG_RESET,
} EnumDPRxHDCPResetDpcdField;

//--------------------------------------------------
//HDCP RX Authentication State
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_STATE_IDLE = 0,
    _DP_RX_HDCP_STATE_AUTH_FAKE,
    _DP_RX_HDCP_STATE_AUTH_1,
    _DP_RX_HDCP_STATE_AUTH_2,
    _DP_RX_HDCP_STATE_AUTH_DONE,
} EnumDPRxHDCPAuthState;

//--------------------------------------------------
//HDCP RX Authentication Upstream Event
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE = 0,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_ECF_CHANGE,
} EnumDPRxHDCPUpstreamAuthStatus;

//--------------------------------------------------
//HDCP RX Authentication State
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP2_REPEATER_STATE_IDLE = 0,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_1,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_2,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE,
} EnumDpHdcp2RxRepeaterAuthState;

//--------------------------------------------------
//HDCP RX Authentication Upstream Event
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_NONE = 0,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_ECF_CHANGE,
} EnumDpHdcp2RxUpstreamAuthStatus;

//--------------------------------------------------
//DP SDP DRAM TYPE
//--------------------------------------------------
typedef enum
{
    _DRAM_DM = 0,
    _DRAM_HDR,
} EnumDRAMType;

#if((_DP_MAC_TX_SUPPORT == _ON) || (_PANEL_STYLE == _PANEL_DPTX))
//--------------------------------------------------
//Down Stream Information
//--------------------------------------------------
typedef struct
{
    BYTE ucDPCDRev;
    BYTE ucLinkRate;
    BYTE ucMaxLinkRate;
    BYTE ucLTTPRNum;
    BYTE ucExtWakeTimeout;
    BYTE ucSinkExWakeTimeOut;
    BYTE ucCurrentSinkCount;
    BYTE ucPreSinkCount;
    BYTE ucScrambleType;
    EnumDpLinkChannelCodingType enumTargetCodingType;
    EnumDpLinkChannelCodingType enumPreCodingType;
    EnumDpLinkChannelCodingType enumCodingType;
//------------------------------------------
    BYTE b3PeerDeviceType : 3;
    EnumDpLaneCount b3LaneNum : 3;
    BYTE b1MSGCapStatus : 1;
    BYTE b1DPPlugStatus : 1;
//------------------------------------------
    BYTE b5MaxLaneNum : 5;
    BYTE b1DPPlugChange : 1;
    BYTE b1LegacyPlugStatus : 1;
    BYTE b1EnhanceFraming : 1;
//------------------------------------------
    BYTE b5MaxLaneNumTemp : 5;
    BYTE b1AlternateSrCapable : 1;
    BYTE b1FramingChangeCapable : 1;
    BYTE b1SSCSupport : 1;
//------------------------------------------
    BYTE b1MsaIgnored : 1;
    BYTE b1TP3Support : 1;
    BYTE b1TP4Support : 1;
    BYTE b1NumberOfSDP : 1;
    BYTE b1NumberOfSDPSink : 1;
    BYTE b1DownStreamInfoReady : 1;
    BYTE b1UpRequestCap : 1;
    BYTE b1DownStreamCapChange : 1;
//------------------------------------------
    BYTE b1DownStreamSinkCountChange : 1;
    BYTE b1DownStreamSink420Support : 1;
    BYTE b1Coding128b132bCap : 1;
    BYTE b1Uhbr10Cap : 1;
    BYTE b1Uhbr13_5Cap : 1;
    BYTE b1Uhbr20Cap : 1;
    BYTE b1SdpSplitSupport : 1;
} StructDownStreamInfo;
#endif // End of #if((_DP_MAC_TX_SUPPORT == _ON) || (_PANEL_STYLE == _PANEL_DPTX))

//--------------------------------------------------
//DP AUX RECEIVE MODE
//--------------------------------------------------
typedef enum
{
    _AUX_DIFF_MODE,
    _AUX_PN_SWAP_MODE,
    _AUX_INPHASE_P_MODE,
    _AUX_INPHASE_N_MODE,
} EnumDpAuxReceiveMode;

//--------------------------------------------------
//DP AUX RX3 AUTO CALIBRATION STATE
//--------------------------------------------------
#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
typedef enum
{
    _AUTO_CALIBRATION_INIT,
    _AUTO_CALIBRATION_DONE,
    _AUTO_CALIBRATION_FAIL,
} EnumDpAuxRxAutoKState;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bSyncDpRx0NormalLTSetPhyFinish;
extern volatile bit g_bSyncDpRx1NormalLTSetPhyFinish;
extern volatile bit g_bSyncDpRx2NormalLTSetPhyFinish;

extern BYTE code tVIC_VFREQ_TABLE[256];
extern StructHdmiCtaFrTableParas code tOVT_FR_TABLE[24];
#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
extern WORD code tVIC_HACTIVE_TABLE[256];
extern WORD code tVIC_HBLANK_TABLE[256];
extern WORD code tVIC_VACTIVE_TABLE[256];
extern WORD code tVIC_PIXEL_RATE_TABLE[256];
extern WORD code tEST_TIMING_HACTIVE_TABLE[];
extern WORD code tEST_TIMING_VACTIVE_TABLE[];
extern BYTE code tEST_TIMING_VBLANK_TABLE[];
extern WORD code tEST_TIMING_HBLANK_TABLE[];
extern WORD code tEST_TIMING_PCLK_TABLE[];
extern BYTE code tEST_TIMING_VFREQ_TABLE[];
extern BYTE code tInterlaceVic[];
#endif

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern WORD g_usSyncA0PixelClk;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern WORD g_usSyncD0PixelClk;
extern WORD g_usSyncD0NativePixelClk;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern WORD g_usSyncD1PixelClk;
extern WORD g_usSyncD1NativePixelClk;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern volatile WORD g_usSyncD2PixelClk;
extern volatile WORD g_usSyncD2NativePixelClk;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern volatile WORD g_usSyncD3PixelClk;
extern volatile WORD g_usSyncD3NativePixelClk;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern volatile WORD g_usSyncD4PixelClk;
extern volatile WORD g_usSyncD4NativePixelClk;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern WORD g_usSyncD5PixelClk;
extern WORD g_usSyncD5NativePixelClk;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
extern volatile WORD g_usSyncD9PixelClk;
extern WORD g_usSyncD9NativePixelClk;
#endif
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern BYTE idata g_pucSyncHdcpBksvBackup[5];
extern BYTE g_ucSyncDigitalSwitch;

#if(_DP_MAC_RX0_SUPPORT == _ON)
extern StructDigitalColorInfo g_stSyncD0ColorInfo;
extern StructDigitalColorInfoChanged g_stSyncD0ColorInfoChanged;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
extern StructDigitalColorInfo g_stSyncD1ColorInfo;
extern StructDigitalColorInfoChanged g_stSyncD1ColorInfoChanged;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
extern StructDigitalColorInfo g_stSyncD2ColorInfo;
extern StructDigitalColorInfoChanged g_stSyncD2ColorInfoChanged;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
extern StructDigitalColorInfo g_stSyncPxpColorInfo;
extern StructDigitalColorInfoChanged g_stSyncPxpColorInfoChanged;
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
extern StructDigitalColorInfo g_stSyncD3ColorInfo;
extern StructDigitalColorInfoChanged g_stSyncD3ColorInfoChanged;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
extern StructDigitalColorInfo g_stSyncD4ColorInfo;
extern StructDigitalColorInfoChanged g_stSyncD4ColorInfoChanged;
#endif

#if((_DM_FUNCTION == _ON) && (_HDMI21_ALLM_SUPPORT == _ON))
extern volatile StructHdmiDmAllmEnableStatus g_stSyncHdmiDmAllmEnabled;
#endif

#endif

#if(_DP_SUPPORT == _ON)
extern StructDPMarginLinkInfo g_stSyncDpMarginLink;
#endif

#if(_DP_TX_SUPPORT == _ON)
extern StructDPTxStatusInfo g_stSyncDpTxStatus;
#endif

#if(_DP_TX_SUPPORT == _ON)
extern BYTE idata g_pucSyncHdcpAksvBackup[5];
#endif

#if(_HDMI_SUPPORT == _ON)
extern StructHdmiRxPsWakeupHpd g_stSyncHdmiPsWakeupHPD;

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
extern bit g_bSyncTmdsRx0Z0Toggle;
extern bit g_bSyncTmdsRx1Z0Toggle;
extern bit g_bSyncTmdsRx2Z0Toggle;
extern bit g_bSyncTmdsRx3Z0Toggle;
extern bit g_bSyncTmdsRx4Z0Toggle;
extern bit g_bSyncTmdsRx5Z0Toggle;
extern bit g_bSyncTmdsRx0GlobalZ0Toggle;
extern bit g_bSyncTmdsRx1GlobalZ0Toggle;
extern bit g_bSyncTmdsRx2GlobalZ0Toggle;
extern bit g_bSyncTmdsRx3GlobalZ0Toggle;
extern bit g_bSyncTmdsRx4GlobalZ0Toggle;
extern bit g_bSyncTmdsRx5GlobalZ0Toggle;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
extern void ScalerSyncDpLowPowerProc(void);

#if(_DUAL_DP_SUPPORT == _ON)
extern bit ScalerSyncDualDpDoubleCheck(EnumInputPort enumInputPort);
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction);
extern void ScalerSyncDpTxHdcpUpstreamSwitchProc(EnumInputPort enumInputPort);
extern EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void);
extern bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void);
extern EnumDPRxHDCPAuthState ScalerSyncDpHdcpGetAuthState(void);
extern bit ScalerSyncDpHdcpRepeaterCheckUrgentEvent(void);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern EnumDpHdcp2RxUpstreamAuthStatus ScalerSyncDpHdcp2GetUpstreamEvent(void);
extern bit ScalerSyncDpHdcp2GetContentStreamManagementStatus(void);
extern EnumHDCPType ScalerSyncDpGetHdcpModeStatus(void);
extern EnumDpHdcp2RxRepeaterAuthState ScalerSyncDpHdcp2GetAuthState(void);
#endif

extern bit ScalerSyncDpHdcpDownstreamReAuthCheck(void);
#endif

#if((_DP_SUPPORT == _ON) || (_DP_TX_SUPPORT == _ON))
extern BYTE ScalerSyncDpGetColorDepthValue(BYTE ucColorDepthPreValue, EnumColorSpace enumColorSpace);
#endif

extern void ScalerSyncResetAllProc(void);
extern WORD ScalerSyncGetHSWbyClk(WORD usInputPixelClk);
extern WORD ScalerSyncGetHStartbyHSW(WORD usHSWidth, WORD usInputPixelClk);

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DRR_SUPPORT == _ON))
extern void ScalerSyncDrrDataExchangeProc(bit bEnable);
#endif
extern EnumPortType ScalerSyncGetPortType(EnumInputPort enumInputPort);
extern void ScalerSyncGetDRAMDataByPort(EnumInputPort enumInputPort, EnumDRAMType enumDRAMType, BYTE *pucSdpInfoData, bit *pbInfoReceive, bit *pbInfoChange);
#if(_HDMI_SBTM_SUPPORT == _ON)
extern void ScalerSyncGetSBTMDataByPort(EnumInputPort enumInputPort, BYTE *pucSBTMInfoData, bit *pbInfoReceive, bit *pbInfoChange);
#endif

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
extern bit ScalerSyncGetVerticalTimingDataFromInterface(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
#endif

