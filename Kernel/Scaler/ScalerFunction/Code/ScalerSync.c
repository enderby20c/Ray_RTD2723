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
// ID Code      : ScalerSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_SYNC__

#include "ScalerFunctionInclude.h"
#include "Sync/ScalerSync.h"

#if(_HDMI_SUPPORT != _ON)
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#warning "Z0 Toggle Solution Is Not Available !!!!"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
// unit: Hz (field unit)
BYTE code tVIC_VFREQ_TABLE[256] =
{
    60, 60, 60, 60, 60, 60, 60, 60, 60, 60,                         // Vic 1~10
    60, 60, 60, 60, 60, 60, 50, 50, 50, 50,                         // Vic 11~20
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,                         // Vic 21~30
    50, 24, 25, 30, 60, 60, 50, 50, 50, 100,                        // Vic 31~40
    100, 100, 100, 100, 100, 120, 120, 120, 120, 120,              // Vic 41~50
    120, 200, 200, 200, 200, 240, 240, 240, 240, 24,               // Vic 51~60
    25, 30, 120, 100, 24, 25, 30, 50, 60, 100,                      // Vic 61~70
    120, 24, 25, 30, 50, 60, 100, 120, 24, 25,                      // Vic 71~80
    30, 50, 60, 100, 120, 24, 25, 30, 50, 60,                       // Vic 81~90
    100, 120, 24, 25, 30, 50, 60, 24, 25, 30,                       // Vic 91~100
    50, 60, 24, 25, 30, 50, 60, 48, 48, 48,                         // Vic 101~110
    48, 48, 48, 48, 48, 48, 100, 120, 100, 120,                     // Vic 111~120
    24, 25, 30, 48, 50, 60, 100, 0, 0, 0,                           // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 181~190
    0, 0, 120, 24, 25, 30, 48, 50, 60, 100,                         // Vic 191~200
    120, 24, 25, 30, 48, 50, 60, 100, 120, 24,                     // Vic 201~210
    25, 30, 48, 50, 60, 100, 120, 100, 120, 0,                     // Vic 211~220
};

// CTA-861-I Table12-AVI InfoFrame Video Format Frame Rate
// FrameRate(1 MHz), AviRateIdx, FrameRateGroup
StructHdmiCtaFrTableParas code tOVT_FR_TABLE[24] =
{
    { 24,  1, 1}, // AviFr = 1
    { 24,  1, 1}, // AviFr = 2
    { 25,  2, 1}, // AviFr = 3
    { 30,  3, 1},
    { 30,  3, 1},
    { 48,  4, 2},
    { 48,  4, 2},
    { 50,  5, 2},
    { 60,  6, 2},
    { 60,  6, 2},
    {100,  7, 3},
    {120,  8, 3},
    {120,  8, 3},
    {144,  9, 4},
    {144,  9, 4},
    {200, 10, 5},
    {240, 11, 5},
    {240, 11, 5},
    {300, 12, 6},
    {360, 13, 6},
    {360, 13, 6},
    {400, 14, 7},
    {480, 15, 7}, // AviFr = 23
    {480, 15, 7}, // AviFr = 24
};

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
WORD code tVIC_HACTIVE_TABLE[256] =
{
    640, 720, 720, 1280, 1920, 1440, 1440, 1440, 1440, 2880,        // Vic 1~10
    2880, 2880, 2880, 1440, 1440, 1920, 720, 720, 1280, 1920,       // Vic 11~20
    1440, 1440, 1440, 1440, 2880, 2880, 2880, 2880, 1440, 1440,     // Vic 21~30
    1920, 1920, 1920, 1920, 2880, 2880, 2880, 2880, 1920, 1920,     // Vic 31~40
    1280, 720, 720, 1440, 1440, 1920, 1280, 720, 720, 1440,         // Vic 41~50
    1440, 720, 720, 1440, 1440, 720, 720, 1440, 1440, 1280,         // Vic 51~60
    1280, 1280, 1920, 1920, 1280, 1280, 1280, 1280, 1280, 1280,    // Vic 61~70
    1280, 1920, 1920, 1920, 1920, 1920, 1920, 1920, 1680, 1680,    // Vic 71~80
    1680, 1680, 1680, 1680, 1680, 2560, 2560, 2560, 2560, 2560,    // Vic 81~90
    2560, 2560, 3840, 3840, 3840, 3840, 3840, 4096, 4096, 4096,    // Vic 91~100
    4096, 4096, 3840, 3840, 3840, 3840, 3840, 1280, 1280, 1680,    // Vic 101~110
    1920, 1920, 2560, 3840, 4096, 3840, 3840, 3840, 3840, 3840,    // Vic 111~120
    5120, 5120, 5120, 5120, 5120, 5120, 5120, 0, 0, 0,              // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 181~190
    0, 0, 5120, 7680, 7680, 7680, 7680, 7680, 7680, 7680,          // Vic 191~200
    7680, 7680, 7680, 7690, 7690, 7680, 7680, 7680, 7680, 10240,  // Vic 201~210
    10240, 10240, 10240, 10240, 10240, 1080, 10240, 4096, 4096, 0, // Vic 211~220
};

WORD code tVIC_HBLANK_TABLE[256] =
{
    160, 138, 138, 370, 280, 276, 276, 276, 276, 552,               // Vic 1~10
    552, 552, 552, 276, 276, 280, 144, 144, 700, 720,               // Vic 11~20
    288, 288, 288, 288, 576, 576, 576, 576, 288, 288,               // Vic 21~30
    720, 830, 720, 280, 552, 552, 576, 576, 384, 720,               // Vic 31~40
    700, 144, 144, 288, 288, 280, 370, 138, 138, 276,               // Vic 41~50
    276, 144, 144, 288, 288, 138, 138, 276, 276, 2020,             // Vic 51~60
    2680, 2020, 280, 720, 2020, 2680, 2020, 700, 370, 700,         // Vic 61~70
    370, 830, 720, 280, 720, 280, 720, 280, 1620, 1488,            // Vic 71~80
    960, 520, 520, 320, 320, 1190, 640, 960, 740, 440,             // Vic 81~90
    410, 740, 1660, 1440, 560, 1440, 560, 1404, 1184, 304,         // Vic 91~100
    1184, 304, 1660, 1440, 560, 1440, 560, 1220, 1220, 1070,       // Vic 101~110
    830, 830, 1190, 1660, 1404, 1660, 1440, 560, 1440, 560,        // Vic 111~120
    2380, 2080, 880, 1130, 1480, 380, 1480, 0, 0, 0,                // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 181~190
    0, 0, 380, 3320, 3120, 1320, 3320, 3120, 1320, 2880,           // Vic 191~200
    1120, 3320, 3120, 1320, 3320, 3120, 1320, 2880, 1120, 2260,   // Vic 201~210
    3260, 760, 2260, 3260, 760, 2960, 760, 1184, 304, 0,           // Vic 211~220
};

// unit: line# (frame unit)
WORD code tVIC_VACTIVE_TABLE[256] =
{
    480, 480, 480, 720, 1080, 480, 480, 240, 240, 480,              // Vic 1~10
    480, 240, 240, 480, 480, 1080, 576, 576, 720, 1080,            // Vic 11~20
    576, 576, 288, 288, 576, 576, 288, 288, 576, 576,               // Vic 21~30
    1080, 1080, 1080, 1080, 480, 480, 576, 576, 1080, 1080,        // Vic 31~40
    720, 576, 576, 576, 576, 1080, 720, 480, 480, 480,              // Vic 41~50
    480, 576, 576, 576, 576, 480, 480, 480, 480, 720,               // Vic 51~60
    720, 720, 1080, 1080, 720, 720, 720, 720, 720, 720,            // Vic 61~70
    720, 1080, 1080, 1080, 1080, 1080, 1080, 1080, 720, 720,        // Vic 71~80
    720, 720, 720, 720, 720, 1080, 1080, 1080, 1080, 1080,          // Vic 81~90
    1080, 1080, 2160, 2160, 2160, 2160, 2160, 2160, 2160, 2160,    // Vic 91~100
    2160, 2160, 2160, 2160, 2160, 2160, 2160, 720, 720, 720,        // Vic 101~110
    1080, 1080, 1080, 2160, 2160, 2160, 2160, 2160, 2160, 2160,    // Vic 111~120
    2160, 2160, 2160, 2160, 2160, 2160, 2160, 0, 0, 0,              // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 181~190
    0, 0, 2160, 4320, 4320, 4320, 4320, 4320, 4320, 4320,          // Vic 191~200
    4320, 4320, 4320, 4320, 4320, 4320, 4320, 4320, 4320, 4320,   // Vic 201~210
    4320, 4320, 4320, 4320, 4320, 4320, 4320, 2160, 2160, 0,      // Vic 211~220
};

// unit: 0.1 MHz (field unit)
WORD code tVIC_PIXEL_RATE_TABLE[256] =
{
    252, 270, 270, 743, 743, 270, 270, 270, 270, 540,                            // Vic 1~10
    540, 540, 540, 540, 540, 1485, 270, 270, 743, 743,                           // Vic 11~20
    270, 270, 270, 270, 540, 540, 540, 540, 540, 540,                            // Vic 21~30
    1485, 743, 743, 743, 1080, 1080, 1080, 1080, 720, 1485,                     // Vic 31~40
    1485, 540, 540, 540, 540, 1485, 1485, 540, 540, 540,                        // Vic 41~50
    540, 1080, 1080, 1080, 1080, 1080, 1080, 1080, 1080, 594,                   // Vic 51~60
    743, 743, 2970, 2970, 594, 743, 743, 743, 743, 1485,                        // Vic 61~70
    1485, 743, 743, 743, 1485, 1485, 2970, 2970, 594, 594,                      // Vic 71~80
    594, 825, 990, 1650, 1980, 990, 990, 1188, 1856, 1980,                      // Vic 81~90
    3713, 4950, 2970, 2970, 2970, 5940, 5940, 2970, 2970, 2970,                 // Vic 91~100
    5940, 5940, 2970, 2970, 2970, 5940, 5940, 900, 900, 990,                    // Vic 101~110
    1485, 1485, 1980, 5940, 5940, 5940, 11880, 11880, 11880, 11880,             // Vic 111~120
    3960, 3960, 3960, 7425, 7425, 7425, 14850, 0, 0, 0,                          // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                    // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                    // Vic 181~190
    0, 0, 14850, 11880, 11880, 11880, 23760, 23760, 23760, 47520,               // Vic 191~200
    47520, 11880, 11880, 11880, 23760, 23760, 23760, 47520, 47520, 14850,      // Vic 201~210
    14850, 14850, 29700, 29700, 29700, 59400, 59400, 11880, 11880, 0,           // Vic 211~220
};

WORD code tEST_TIMING_HACTIVE_TABLE[] =
{
    720, 720, 640, 640, 640, 640, 800, 800,         // EDID 0x23 [7]~[0]
    800, 800, 832, 1024, 1024, 1024, 1024, 1280,   // EDID 0x24 [7]~[0]
    1152,                                             // EDID 0x25 [7]
};

// unit: line# (frame unit)
WORD code tEST_TIMING_VACTIVE_TABLE[] =
{
    400, 400, 480, 480, 480, 480, 600, 600,        // EDID 0x23 [7]~[0]
    600, 600, 624, 768, 768, 768, 768, 1024,       // EDID 0x24 [7]~[0]
    870,                                              // EDID 0x25 [7]
};

// unit: line# (frame unit)
BYTE code tEST_TIMING_VBLANK_TABLE[] =
{
    49, 46, 44, 45, 40, 20, 25, 28,                 // EDID 0x23 [7]~[0]
    66, 25, 23, 49, 38, 38, 32, 42,                 // EDID 0x24 [7]~[0]
    45,                                               // EDID 0x25 [7]
};

WORD code tEST_TIMING_HBLANK_TABLE[] =
{
    180, 216, 160, 224, 192, 200, 224, 256,         // EDID 0x23 [7]~[0]
    240, 256, 320, 240, 320, 304, 288, 408,         // EDID 0x24 [7]~[0]
    304,                                              // EDID 0x25 [7]
};

// unit: 0.1M (field unit)
WORD code tEST_TIMING_PCLK_TABLE[] =
{
    283, 367, 252, 304, 315, 315, 360, 400,         // EDID 0x23 [7]~[0]
    500, 495, 559, 449, 650, 750, 788, 1350,        // EDID 0x24 [7]~[0]
    999,                                              // EDID 0x25 [7]
};

// unit: Hz (field unit)
BYTE code tEST_TIMING_VFREQ_TABLE[] =
{
    70, 88, 60, 67, 73, 75, 56, 60,         // EDID 0x23 [7]~[0]
    72, 75, 75, 87, 60, 70, 75, 75,        // EDID 0x24 [7]~[0]
    75,                                      // EDID 0x25 [7]
};

BYTE code tInterlaceVic[] =
{
    20, 21, 22, 25, 26, 39, 5, 6, 7, 10, 11, 40, 44, 45, 46, 50, 51, 54, 55, 58, 59,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPortCableStatus g_stSyncPortCableStatus;

#if(_DUAL_DP_SUPPORT == _ON)
EnumInputPort g_enumSyncDualDpPortSwitchSelect = _DUAL_DP_INPUT_PORT;
#endif

volatile bit g_bSyncDpRx0NormalLTSetPhyFinish = _FALSE;
volatile bit g_bSyncDpRx1NormalLTSetPhyFinish = _FALSE;
volatile bit g_bSyncDpRx2NormalLTSetPhyFinish = _FALSE;

#if(_D0_DP_SUPPORT == _ON)
bit g_bSyncDpRx0HdcpCheckEnable;
#endif

#if(_D1_DP_SUPPORT == _ON)
bit g_bSyncDpRx1HdcpCheckEnable;
#endif

#if(_D2_DP_SUPPORT == _ON)
bit g_bSyncDpRx2HdcpCheckEnable;
#endif

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
WORD g_usSyncA0PixelClk;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
WORD g_usSyncD0PixelClk;
WORD g_usSyncD0NativePixelClk;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
WORD g_usSyncD1PixelClk;
WORD g_usSyncD1NativePixelClk;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
volatile WORD g_usSyncD2PixelClk;
volatile WORD g_usSyncD2NativePixelClk;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
volatile WORD g_usSyncD3PixelClk;
volatile WORD g_usSyncD3NativePixelClk;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
volatile WORD g_usSyncD4PixelClk;
volatile WORD g_usSyncD4NativePixelClk;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
WORD g_usSyncD5PixelClk;
WORD g_usSyncD5NativePixelClk;
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
volatile WORD g_usSyncD9PixelClk;
WORD g_usSyncD9NativePixelClk;
#endif
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
BYTE idata g_pucSyncHdcpBksvBackup[5];
bit g_bSyncDpDCOffHPDHigh = 0;
BYTE g_ucSyncDigitalSwitch;
BYTE g_ucSyncHdmiHotPlug;
#endif

#if(_DP_TX_SUPPORT == _ON)
BYTE idata g_pucSyncHdcpAksvBackup[5];
#endif

#if(_DP_SUPPORT == _ON)
StructDPCapSwitchInfo g_stSyncDpCapSwitch;
StructDPMarginLinkInfo g_stSyncDpMarginLink;

bit g_pbSyncDpMstDCOffHPDToggleHoldFlag[3];
bit g_bSyncDpDCOffHPDToggleFlag;

StructDpAuxSetting g_stSyncDpAuxSetting =
{
    _DP_AUX_INITIAL_DIFF_MODE,
    _DP_AUX_INITIAL_ADJR,
};

BYTE g_ucSyncDpIrqTime_10us;
bit g_bSyncDpIllegalIdlePatternCheck = _FALSE;
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
StructDPTxStatusInfo g_stSyncDpTxStatus;
#endif

#if(_HDR10_SUPPORT == _ON)
StructHDR10StaticMetaData g_pstSyncHDR10SaticMetadata[_HDR_METADATA_PORT_VALID];
StructHDR10PortSettingInfo g_stSyncHDR10PortSettingInfo;
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
StructHDR10SBTMInfo g_pstSyncHDR10SBTMMetadata[_HDR_METADATA_PORT_VALID];
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
StructFreeSyncIIInfo g_pstSyncFreeIIMetadata[_MULTI_DISPLAY_MAX];
#endif

// Advanced HDR10
#if(_ADVANCED_HDR10_SUPPORT == _ON)
volatile StructAdvancedHDR10SettingInfo g_stSyncAdvancedHDR10SettingInfo;
volatile StructAdvancedHDR10MetaData g_stSyncAdvancedHDR10Metadata;
volatile StructAdvancedHDR10MetaData g_stSyncAdvancedHDR10BackUpMetadata;
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
volatile StructAdvancedHDR10DHDRMetaData g_stSyncAdvancedHDR10DHDRMetaData;
#endif
volatile BYTE g_pucSyncAdvancedHDR10YmTable[710];
#endif



#if(_URGENT_EVENT_CHECK_MODE == _ON)
BYTE g_ucSyncCheckUrgentEventOccured;
#endif

#if(_HDMI_SUPPORT == _ON)
StructHdmiRxPsWakeupHpd g_stSyncHdmiPsWakeupHPD;

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
bit g_bSyncTmdsRx0Z0Toggle = 0;
bit g_bSyncTmdsRx1Z0Toggle = 0;
bit g_bSyncTmdsRx2Z0Toggle = 0;
bit g_bSyncTmdsRx3Z0Toggle = 0;
bit g_bSyncTmdsRx4Z0Toggle = 0;
bit g_bSyncTmdsRx5Z0Toggle = 0;
bit g_bSyncTmdsRx0GlobalZ0Toggle = 0;
bit g_bSyncTmdsRx1GlobalZ0Toggle = 0;
bit g_bSyncTmdsRx2GlobalZ0Toggle = 0;
bit g_bSyncTmdsRx3GlobalZ0Toggle = 0;
bit g_bSyncTmdsRx4GlobalZ0Toggle = 0;
bit g_bSyncTmdsRx5GlobalZ0Toggle = 0;
#endif

#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
volatile bit g_bSyncDigitalColorInfoChangeReset;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
volatile StructDigitalDMColorInfoChange g_stSyncDigitalDMColorInfoChange;
#endif

#if(_DP_MAC_RX0_SUPPORT == _ON)
StructDigitalColorInfo g_stSyncD0ColorInfo;
StructDigitalColorInfoChanged g_stSyncD0ColorInfoChanged;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
StructDigitalColorInfo g_stSyncD1ColorInfo;
StructDigitalColorInfoChanged g_stSyncD1ColorInfoChanged;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
StructDigitalColorInfo g_stSyncD2ColorInfo;
StructDigitalColorInfoChanged g_stSyncD2ColorInfoChanged;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
StructDigitalColorInfo g_stSyncPxpColorInfo;
StructDigitalColorInfoChanged g_stSyncPxpColorInfoChanged;
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
StructDigitalColorInfo g_stSyncD3ColorInfo;
StructDigitalColorInfoChanged g_stSyncD3ColorInfoChanged;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
StructDigitalColorInfo g_stSyncD4ColorInfo;
StructDigitalColorInfoChanged g_stSyncD4ColorInfoChanged;
#endif

#if((_DM_FUNCTION == _ON) && (_HDMI21_ALLM_SUPPORT == _ON))
volatile StructHdmiDmAllmEnableStatus g_stSyncHdmiDmAllmEnabled;
#endif
#endif // #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_DM_FUNCTION == _ON)
StructDMSupportInfo g_stSyncDMSupportInfo;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get DPF Edid Extersion Data Block Start Address
// Input Value  : enumOutputPort (Px), Cta Ext DB Addr Arrary
// Output Value :
//--------------------------------------------------
void ScalerSyncGetCtaExtDbAddress(WORD *pusCtaDataBlockAddr, BYTE *pucDdcRamAddr)
{
    WORD usEDIDDataBlockStartAddress = 0x84;
    WORD usCtaBlockDtdStartAddr = 0x84;

    BYTE ucReadVSDBDataBlockNum = 0x00;
    BYTE ucEDIDBlockBytesNum = 0x00;
    EnumEdidCtaDbTagCode enumTag = _CTA_DBTAG_NONE;

    // With Extension Block
    if(pucDdcRamAddr[0x7E] != 0x00)
    {
        WORD usIndex = 0;
        BYTE ucExtBlockNum = 0;

        // Check HF EEODB
        if(((pucDdcRamAddr[0x84] & 0xE0) == 0xE0) && (pucDdcRamAddr[0x85] == 0x78))
        {
            ucExtBlockNum = pucDdcRamAddr[0x86];
        }
        else
        {
            ucExtBlockNum = pucDdcRamAddr[0x7E];
        }

        for(usIndex = 0; usIndex < ucExtBlockNum; usIndex++)
        {
            // Stop Extension Analysis if Not CEA Type, Check tag = 0x02
            if(pucDdcRamAddr[(usIndex + 1) * 0x80] == _CTA_EXTENSION_TAG)
            {
                usEDIDDataBlockStartAddress = ((usIndex + 1) * 0x80) + 0x04;

                usCtaBlockDtdStartAddr = pucDdcRamAddr[((usIndex + 1) * 0x80) + 0x02] + ((usIndex + 1) * 0x80);

                if((pucDdcRamAddr[((usIndex + 1) * 0x80) + 0x02] == 4) || (pucDdcRamAddr[((usIndex + 1) * 0x80) + 0x02] == 0))
                {
                    // No Data Block Situation => d = 4, Record Cta Extend Block 1st DTD Start Addr, Search other Block.
                    // No DTD & No Data Block Situation => d = 0, Record Cta Extend Block 1st DTD Start Addr, Search other Block.
                    // Generally, the _FIRST_EXT_DTD_ADDR also meaning the last Data Block + 1.
                    pusCtaDataBlockAddr[_FIRST_EXT_DTD_ADDR] = usEDIDDataBlockStartAddress;
                    continue;
                }

                // Data Block Address Scan
                while((usEDIDDataBlockStartAddress < usCtaBlockDtdStartAddr) && (ucReadVSDBDataBlockNum <= 0x0F))
                {
                    ucReadVSDBDataBlockNum = (ucReadVSDBDataBlockNum + 1);
                    enumTag = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0xE0) >> 5;

                    switch(enumTag)
                    {
                        // Extension Data Block, Check Tag Code
                        case _CTA_DBTAG_EXTTAG:

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            // Check Tag Code of Extension Data Block
                            switch(pucDdcRamAddr[usEDIDDataBlockStartAddress + 1])
                            {
                                case _CTA_EXTDBTAG_VCDB:
                                    pusCtaDataBlockAddr[_CTA_VCDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_COLORDB:

                                    pusCtaDataBlockAddr[_CTA_CDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_SHDR_DB:

                                    pusCtaDataBlockAddr[_CTA_SHDR_DB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_420VDB:

                                    pusCtaDataBlockAddr[_CTA_420VDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_420CMDB:

                                    pusCtaDataBlockAddr[_CTA_420CMDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_HFEEODB:

                                    pusCtaDataBlockAddr[_CTA_HF_EEODB] = usEDIDDataBlockStartAddress;
                                    break;

                                // HF-SCDB (same as HF-VSDB)
                                case _CTA_EXTDBTAG_HFSCDB:

                                    pusCtaDataBlockAddr[_CTA_HF_VSDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_T7_VTDB:

                                    pusCtaDataBlockAddr[_CTA_T7_VTDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_RCDB:

                                    pusCtaDataBlockAddr[_CTA_RCDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case _CTA_EXTDBTAG_SLDB:

                                    pusCtaDataBlockAddr[_CTA_SPK_LDB] = usEDIDDataBlockStartAddress;
                                    break;

                                default:
                                    break;
                            }

                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Vender-Specific Data Block
                        case _CTA_DBTAG_VSDB:

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            // HF-VSDB Analysis
                            if((pucDdcRamAddr[usEDIDDataBlockStartAddress + 1] == 0xD8) &&
                               (pucDdcRamAddr[usEDIDDataBlockStartAddress + 2] == 0x5D) &&
                               (pucDdcRamAddr[usEDIDDataBlockStartAddress + 3] == 0xC4))
                            {
                                pusCtaDataBlockAddr[_CTA_HF_VSDB] = usEDIDDataBlockStartAddress;
                            }
                            else  if((pucDdcRamAddr[usEDIDDataBlockStartAddress + 1] == 0x03) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 2] == 0x0C) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 3] == 0x00))
                            {
                                pusCtaDataBlockAddr[_CTA_HDMI_VSDB] = usEDIDDataBlockStartAddress;
                            }
                            else  if((pucDdcRamAddr[usEDIDDataBlockStartAddress + 1] == 0x1A) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 2] == 0x00) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 3] == 0x00))
                            {
                                pusCtaDataBlockAddr[_CTA_FS_DB] = usEDIDDataBlockStartAddress;
                            }

                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Video Data Block
                        case _CTA_DBTAG_VDB:

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            pusCtaDataBlockAddr[_CTA_VDB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Audio Data Block
                        case _CTA_DBTAG_ADB:
                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            pusCtaDataBlockAddr[_CTA_ADB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Spkear Allocation Data Block
                        case _CTA_DBTAG_SADB:
                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            if(ucEDIDBlockBytesNum == 3)
                            {
                                pusCtaDataBlockAddr[_CTA_SPK_ADB] = usEDIDDataBlockStartAddress;

                                usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);
                            }
                            else
                            {
                                DebugMessageSystem("EDID SPK_ADB length over 3 bytes!!!", ucEDIDBlockBytesNum);
                            }

                            break;

                        default:

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);
                            // Not Data Block
                            if(ucEDIDBlockBytesNum == 0)
                            {
                                // Set value to end while
                                ucReadVSDBDataBlockNum = 0x10;
                            }
                            else
                            {
                                usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);
                            }

                            break;
                    }
                }

                // Record first Cta Block DTD Start Addr
                pusCtaDataBlockAddr[_FIRST_EXT_DTD_ADDR] = usEDIDDataBlockStartAddress;
            }
        } // End of Extension Block Analysis For Loop
    }
}

//--------------------------------------------------
// Description  : Get DPF Edid Extersion Data Block Start Address
// Input Value  : enumOutputPort (Px), Cta Ext DB Addr Arrary
// Output Value :
//--------------------------------------------------
void ScalerSyncGetDidExtDbAddress(WORD *pusDidDataBlockAddr, BYTE *pucDdcRamAddr)
{
    WORD usEDIDDataBlockStartAddress = 0x00;
    WORD usEDIDDidChecksumAddress = 0x00;
    BYTE ucReadVSDBDataBlockNum = 0x00;
    BYTE ucEDIDBlockBytesNum = 0x00;

    // With Extension Block
    if(pucDdcRamAddr[0x7E] != 0x00)
    {
        BYTE ucIndex = 0;
        BYTE ucExtBlockNum = 0;

        // Check HF EEODB
        if(((pucDdcRamAddr[0x84] & 0xE0) == 0xE0) && (pucDdcRamAddr[0x85] == 0x78))
        {
            ucExtBlockNum = pucDdcRamAddr[0x86];
        }
        else
        {
            ucExtBlockNum = pucDdcRamAddr[0x7E];
        }

        for(ucIndex = 0; ucIndex < ucExtBlockNum; ucIndex++)
        {
            // Stop Extension Analysis if Not DID Type, Check tag = 0x70
            if(pucDdcRamAddr[((WORD)ucIndex + 1) * 0x80] == _DID_EXTENSION_TAG)
            {
                bit bEndOfDidExt = _FALSE;

                usEDIDDataBlockStartAddress = 0x85 + ((WORD)(ucIndex) * 0x80);
                usEDIDDidChecksumAddress = 0x85 + pucDdcRamAddr[(WORD)ucIndex * 0x80 + 0x82] + ((WORD)(ucIndex) * 0x80);

                // Data Block Address Scan
                while((usEDIDDataBlockStartAddress < usEDIDDidChecksumAddress) && (ucReadVSDBDataBlockNum <= 0x0F))
                {
                    ucReadVSDBDataBlockNum = (ucReadVSDBDataBlockNum + 1);

                    switch(pucDdcRamAddr[usEDIDDataBlockStartAddress])
                    {
                        // Timing 1 DB (20B, Detail)
                        case _DID13_TAG_T1DB:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            pusDidDataBlockAddr[_DID_T1_DB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;

                        // Timing 7 DB (20B, Detail)
                        case _DID2_TAG_T7DB:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            pusDidDataBlockAddr[_DID_T7_DB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;

                        // Timing 10 DTD (CVT3)
                        case _DID2_TAG_T10DB:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            pusDidDataBlockAddr[_DID_T10_DB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;

                        // Timing AS DTD
                        case _DID2_TAG_ASDB:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            pusDidDataBlockAddr[_DID_AS_DB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;

                        // Timing CTA DTD
                        case _DID_TAG_CTADB:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            pusDidDataBlockAddr[_DID_CTA_DB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;

                        default:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            if(((pucDdcRamAddr[usEDIDDataBlockStartAddress]) == 0x00) && (ucEDIDBlockBytesNum == 0x00))
                            {
                                // End of DB Area
                                bEndOfDidExt = _TRUE;
                            }
                            else
                            {
                                usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);
                            }
                            break;
                    }

                    if(bEndOfDidExt == _TRUE)
                    {
                        break;
                    }
                }
            }
        } // End of Extension Block Analysis For Loop
    }
}

//--------------------------------------------------
// Description  : Get Port Type by Input Port
// Input Value  : enumInputPort --> Current port
// Output Value : EnumPortType --> corresponding port type
//--------------------------------------------------
EnumPortType ScalerSyncGetPortType(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _A0_INPUT_PORT:
#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
            return _PORT_VGA;
#endif
            break;
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            return _PORT_DP;
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            return _PORT_HDMI;
#endif
            break;
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            return _PORT_DP;
#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            return _PORT_HDMI;
#endif
            break;
        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            return _PORT_DP;
#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            return _PORT_HDMI;
#endif
            break;
        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            return _PORT_HDMI;
#endif
            break;
        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            return _PORT_HDMI;
#endif
            break;
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            return _PORT_HDMI;
#endif
            break;
        case _D6_INPUT_PORT:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            return _PORT_DP;
#endif
            break;
        case _D7_INPUT_PORT:
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
            return _PORT_DP;
#endif
            break;
        case _D8_INPUT_PORT:
#if(_D8_INPUT_PORT_TYPE == _D8_DP_PORT)
            return _PORT_DP;
#endif
            break;
        case _D9_INPUT_PORT:
        default:
            break;
    }

    return _PORT_NONE;
}


//--------------------------------------------------
// Description  : Get DRAM Data by Port
// Input Value  : enumInputPort --> Current port
//                pucSdpInfoData --> info data array
//                pucInfoReceive --> receive bit(updated in this function)
//                pucInfoChange --> change bit(updated in this function)
// Output Value : None
//--------------------------------------------------
void ScalerSyncGetDRAMDataByPort(EnumInputPort enumInputPort, EnumDRAMType enumDRAMType, BYTE *pucSdpInfoData, bit *pbInfoReceive, bit *pbInfoChange)
{
    enumDRAMType = enumDRAMType;
    pucSdpInfoData = pucSdpInfoData;
    pbInfoReceive = pbInfoReceive;
    pbInfoChange = pbInfoChange;

    switch(ScalerSyncGetPortType(enumInputPort))
    {
#if(_DP_SUPPORT == _ON)
#if(_DP_HDR10_SUPPORT == _ON)
        case _PORT_DP:
#if(_DM_FUNCTION == _ON)
            if(enumDRAMType == _DRAM_DM)
            {
                *pbInfoReceive = _TRUE;
                *pbInfoChange = _TRUE;
                ScalerDpMacStreamRxGetSdpPktData(enumInputPort, _DP_SDP_TYPE_INFOFRAME_HDR, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);
            }
            else if(enumDRAMType == _DRAM_HDR)
#endif
            {
                *pbInfoChange = _TRUE;
                ScalerDpMacStreamRxHDR10GetCurrentStatus(enumInputPort, pbInfoReceive, pucSdpInfoData);
            }

            break;
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
#if((_HDMI_HDR10_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
        case _PORT_HDMI:
            if(ScalerTmdsMacRxHDR10Status(enumInputPort) == _TRUE)
            {
                *pbInfoReceive = _TRUE;
                *pbInfoChange = _TRUE;
                ScalerTmdsMacRxGetHDR10Data(enumInputPort, pucSdpInfoData);
            }
            break;
#endif
#endif
        default:
            break;
    }
}
#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get SBTM Data by Port
// Input Value  : enumInputPort --> Current port
//                pucSdpInfoData --> info data array
//                pucInfoReceive --> receive bit(updated in this function)
//                pucInfoChange --> change bit(updated in this function)
// Output Value : None
//--------------------------------------------------
void ScalerSyncGetSBTMDataByPort(EnumInputPort enumInputPort, BYTE *pucSBTMInfoData, bit *pbInfoReceive, bit *pbInfoChange)
{
#if(_HDMI_SUPPORT == _ON)
    if(ScalerTmdsMacRxHDR10SBTMStatus(enumInputPort) == _TRUE)
    {
        *pbInfoReceive = _TRUE;
        *pbInfoChange = _TRUE;
        ScalerTmdsMacRxGetHDR10SBTMData(enumInputPort, pucSBTMInfoData);
    }
#endif
}
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Secondary Data
// Input Value  : Source Search Port & Display Region
// Output Value : None
//--------------------------------------------------
void ScalerSyncUpdateSecData(EnumInputPort enumInputPort, EnumDisplayRegion enumDisplayRegion, EnumHDRInfoChgPolling enumHDRInfoChgPolling)
{
    enumInputPort = enumInputPort;
    enumDisplayRegion = enumDisplayRegion;

#if(_FREESYNC_II_SUPPORT == _ON)
    ScalerDrrFreeSyncIIGetCurrentStatus(enumInputPort, enumDisplayRegion, enumHDRInfoChgPolling);
#endif

#if(_HDR10_SUPPORT == _ON)
    ScalerSyncHDR10GetCurrentStatus(enumInputPort, enumHDRInfoChgPolling);
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
    ScalerSyncHDR10SBTMGetCurrentStatus(enumInputPort, enumHDRInfoChgPolling);
#endif
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current HDR data enable status
// Input Value  : enumInputPort --> Input port
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSyncHDR10CheckPortStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D0_DP_SUPPORT == _ON)
            if(_DP_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D1_DP_SUPPORT == _ON)
            if(_DP_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif

            break;

        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D2_DP_SUPPORT == _ON)
            if(_DP_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        default:
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Current HDR data
// Input Value  : enumDisplayRegion --> Current Display Region
//                enumInputPort --> Input port
// Output Value : None
//--------------------------------------------------
void ScalerSyncHDR10GetCurrentStatus(EnumInputPort enumInputPort, EnumHDRInfoChgPolling enumHDRInfoChgPolling)
{
    StructHDR10StaticMetaData stHDR10InfoData = {0};

    if(ScalerSyncHDR10CheckPortStatus(enumInputPort) == _TRUE)
    {
        BYTE pucSdpInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
        bit bHDRInfoReceive = _FALSE;
        bit bHDRInfoChange = _FALSE;
        bit bDMMetaDataCheck = _FALSE;

        ScalerSyncGetDRAMDataByPort(enumInputPort, _DRAM_HDR, pucSdpInfoData, &bHDRInfoReceive, &bHDRInfoChange);

#if((_DM_FUNCTION == _ON) && (_IS_MAIN_PROCESS_CPU == _TRUE))
#if(_DM_FUNCTION_BYPASS_HW_APPLY == _OFF)
        bDMMetaDataCheck = ScalerDMJudgeDRAMMetadata(pucSdpInfoData);
#endif
#endif

        // Check HDR Version/ Length & InfoFrame receive bit
        if((bHDRInfoReceive == _TRUE) && (pucSdpInfoData[0] == 0x01) && (pucSdpInfoData[1] == 0x1A) && (bDMMetaDataCheck == _FALSE))
        {
            if((bHDRInfoChange == _TRUE) || (enumHDRInfoChgPolling == _HDR_INFO_CHG_POLLING_CHECK_DISABLE))
            {
                stHDR10InfoData.ucEOTF = pucSdpInfoData[2];
                stHDR10InfoData.ucStaticMetadataID = pucSdpInfoData[3];

                stHDR10InfoData.usDisplayPrimariesX0 = ((WORD)(pucSdpInfoData[5] << 8) | (pucSdpInfoData[4]));
                stHDR10InfoData.usDisplayPrimariesY0 = ((WORD)(pucSdpInfoData[7] << 8) | (pucSdpInfoData[6]));

                stHDR10InfoData.usDisplayPrimariesX1 = ((WORD)(pucSdpInfoData[9] << 8) | (pucSdpInfoData[8]));
                stHDR10InfoData.usDisplayPrimariesY1 = ((WORD)(pucSdpInfoData[11] << 8) | (pucSdpInfoData[10]));

                stHDR10InfoData.usDisplayPrimariesX2 = ((WORD)(pucSdpInfoData[13] << 8) | (pucSdpInfoData[12]));
                stHDR10InfoData.usDisplayPrimariesY2 = ((WORD)(pucSdpInfoData[15] << 8) | (pucSdpInfoData[14]));

                stHDR10InfoData.usWhitePointX = ((WORD)(pucSdpInfoData[17] << 8) | (pucSdpInfoData[16]));
                stHDR10InfoData.usWhitePointY = ((WORD)(pucSdpInfoData[19] << 8) | (pucSdpInfoData[18]));

                stHDR10InfoData.usMaxDisplayMasteringLv = ((WORD)(pucSdpInfoData[21] << 8) | (pucSdpInfoData[20]));
                stHDR10InfoData.usMinDisplayMasteringLv = ((WORD)(pucSdpInfoData[23] << 8) | (pucSdpInfoData[22]));

                stHDR10InfoData.usMaxCLL = ((WORD)(pucSdpInfoData[25] << 8) | (pucSdpInfoData[24]));
                stHDR10InfoData.usMaxFALL = ((WORD)(pucSdpInfoData[27] << 8) | (pucSdpInfoData[26]));

                SET_HDR10_RX_INFO_DATA(enumInputPort, stHDR10InfoData);
            }
        }
        else
        {
            memset(&stHDR10InfoData, 0, sizeof(stHDR10InfoData));

            SET_HDR10_RX_INFO_DATA(enumInputPort, stHDR10InfoData);
        }
    }
    else
    {
        SET_HDR10_RX_INFO_DATA(enumInputPort, stHDR10InfoData);
    }
}

//--------------------------------------------------
// Description  : Convert HDR display Input Port to Intput Port index
// Input Value  : EnumInputPort --> target input port index
// Output Value : input port index
//--------------------------------------------------
BYTE ScalerSyncDxHDRMetadataIndexMapping(EnumInputPort enumInputPort)
{
    EnumHDRMetadataIndex enumHDRMetadataIndex = _HDR_METADATA_INDEX_DEFAULT;

    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

            enumHDRMetadataIndex = _HDR_METADATA_INDEX_0;

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

            enumHDRMetadataIndex = _HDR_METADATA_INDEX_1;

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

            enumHDRMetadataIndex = _HDR_METADATA_INDEX_2;

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

            enumHDRMetadataIndex = _HDR_METADATA_INDEX_3;

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

            enumHDRMetadataIndex = _HDR_METADATA_INDEX_4;

            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

            enumHDRMetadataIndex = _HDR_METADATA_INDEX_5;

            break;
#endif

        default:
            break;
    }

    return (BYTE) enumHDRMetadataIndex;
}
#endif // End of #if(_HDR10_SUPPORT == _ON)
#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current HDR SBTM data enable status
// Input Value  : enumInputPort --> Input port
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSyncHDR10SBTMCheckPortStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
#if(_D0_DP_SUPPORT == _ON)
            return _FALSE;
#endif
            break;

        case _D1_INPUT_PORT:
#if(_D1_DP_SUPPORT == _ON)
            return _FALSE;
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_DP_SUPPORT == _ON)
            return _FALSE;
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if(_HDMI_SBTM_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if(_HDMI_SBTM_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            if(_HDMI_SBTM_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        default:
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Current HDR SBTM data
// Input Value  : enumDisplayRegion --> Current Display Region
//                enumInputPort --> Input port
// Output Value : None
//--------------------------------------------------
void ScalerSyncHDR10SBTMGetCurrentStatus(EnumInputPort enumInputPort, EnumHDRInfoChgPolling enumHDRInfoChgPolling)
{
    if(ScalerSyncHDR10SBTMCheckPortStatus(enumInputPort) == _TRUE)
    {
        BYTE pucSBTMInfoData[8] = {0};
        bit bHDRInfoReceive = _FALSE;
        bit bHDRInfoChange = _FALSE;

        ScalerSyncGetSBTMDataByPort(enumInputPort, pucSBTMInfoData, &bHDRInfoReceive, &bHDRInfoChange);

        // Check HDR Version/ Length & InfoFrame receive bit
        if(bHDRInfoReceive == _TRUE)
        {
            if((bHDRInfoChange == _TRUE) || (enumHDRInfoChgPolling == _HDR_INFO_CHG_POLLING_CHECK_DISABLE))
            {
                StructHDR10SBTMInfo stHDR10SBTMInfoData = {0};
                stHDR10SBTMInfoData.usFrmPbLimitInt = ((WORD)(pucSBTMInfoData[1] << 8) | (pucSBTMInfoData[0]));
                stHDR10SBTMInfoData.ucSBTMVer = pucSBTMInfoData[2];
                stHDR10SBTMInfoData.enumHDR10SBTMType = pucSBTMInfoData[3];
                stHDR10SBTMInfoData.enumHDR10SBTMMode = pucSBTMInfoData[4];
                stHDR10SBTMInfoData.enumHDR10SBTMGRDMLumMaxType = pucSBTMInfoData[5];
                stHDR10SBTMInfoData.enumHDR10SBTMGRDMMinType = pucSBTMInfoData[6];
                SET_HDR10_SBTM_RX_INFO_DATA(enumInputPort, stHDR10SBTMInfoData);
            }
        }
        else
        {
            CLR_HDR10_SBTM_RX_INFO_DATA(enumInputPort);
        }
    }
    else
    {
        CLR_HDR10_SBTM_RX_INFO_DATA(enumInputPort);
    }
}
#endif
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Setting for DP Scanning Port(Power Normal)
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpScanInitial(EnumInputPort enumInputPort)
{
    // Check Whether Inputport Assign Mac
    if(ScalerDpRxGetMacSwitch(enumInputPort) == _DP_MAC_NONE)
    {
        return;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerDrrFreeSyncDpSetEnable(enumInputPort, _DISABLE);
#endif

    ScalerDpPhyRxPhyInitial(enumInputPort);

    ScalerDpAuxRxClearFakeLinkTraining(enumInputPort);

    ScalerDpMacDphyRxDigitalPhyInitial(enumInputPort);

    ScalerDpMacStreamRxMacInitial(enumInputPort);

    ScalerDpMacDphyRxConfigMstOrSstMode(enumInputPort);

    ScalerDpMacStreamRxStreamPreDetectReset(enumInputPort);

#if(_DUAL_DP_SUPPORT == _ON)
    if(enumInputPort == _DUAL_DP_INPUT_PORT)
    {
        SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_INPUT_PORT);
    }
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        // Recover MST Stream Info from Power Cut State
        ScalerDpMacDphyRxRestoreSourceMuxBackupToReg(enumInputPort);
        ScalerDpMacDphyRxRestorePositionBackupToRegAndLoad(enumInputPort);
    }
#endif
}

//--------------------------------------------------
// Description  : DP Low Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpLowPowerProc(void)
{
#if(_D0_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxLowPowerProc(_D0_INPUT_PORT);
    ScalerDpMacDphyRxHdcpSramClkGate(_D0_INPUT_PORT, _DISABLE);
#endif

#if(_D1_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxLowPowerProc(_D1_INPUT_PORT);
    ScalerDpMacDphyRxHdcpSramClkGate(_D1_INPUT_PORT, _DISABLE);
#endif

#if(_D2_DP_SUPPORT == _ON)
    ScalerDpMacStreamRxLowPowerProc(_D2_INPUT_PORT);
    ScalerDpMacDphyRxHdcpSramClkGate(_D2_INPUT_PORT, _DISABLE);
#endif

    ScalerDpAuxRxLowPowerProc();
}

//--------------------------------------------------
// Description  : Dp Rx Fake Power Saving Check
// Input Value  : None
// Output Value : True  --> Fake Power Saving
//                False --> Power Saving
//--------------------------------------------------
bit ScalerSyncDpFakePowerSavingCheck(void)
{
#if(_DP_MST_SUPPORT == _ON)

#if(_D0_DP_MST_PORT_SUPPORT == _ON)
    if(ScalerDpMstRxFakePowerSavingCheck(_D0_INPUT_PORT) == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
    if(ScalerDpMstRxFakePowerSavingCheck(_D1_INPUT_PORT) == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_D2_DP_MST_PORT_SUPPORT == _ON)
    if(ScalerDpMstRxFakePowerSavingCheck(_D2_INPUT_PORT) == _TRUE)
    {
        return _TRUE;
    }
#endif

#endif

#if(_DP_RX_FEC_SUPPORT == _ON)

#if(_D0_DP_SUPPORT == _ON)
    if(ScalerDpMacDphyRxFecDecodeCheck(_D0_INPUT_PORT) == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(ScalerDpMacDphyRxFecDecodeCheck(_D1_INPUT_PORT) == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(ScalerDpMacDphyRxFecDecodeCheck(_D2_INPUT_PORT) == _TRUE)
    {
        return _TRUE;
    }
#endif

#endif

#if(_D0_DP_SUPPORT == _ON)
    if(ScalerDpAuxRxGetLTStatus(_D0_INPUT_PORT) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(ScalerDpAuxRxGetLTStatus(_D1_INPUT_PORT) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(ScalerDpAuxRxGetLTStatus(_D2_INPUT_PORT) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpCapabilitySwitchProc(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    bit bDPRx0DoLongHotPlug = _FALSE;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    bit bDPRx1DoLongHotPlug = _FALSE;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    bit bDPRx2DoLongHotPlug = _FALSE;
#endif

    if(GET_DP_RX_CAPABILITY_SWITCHED() == _TRUE)
    {
        // D0 Port Version Switch
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_AUDIO_SUPPORT == _ON)
        if(ScalerDpAuxRxAudioCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        if(ScalerDrrDpAdaptiveSyncCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(ScalerDrrFreeSyncDpCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDscDecoderDpCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
        if(ScalerDpRxPRModepCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
        if(ScalerDpRxAuxlessAlpmCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
        if(ScalerDpRxHdrCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif
#endif

        if(ScalerDpAuxRxGetDpcdBitInfo(_D0_INPUT_PORT, 0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D0_PORT_TARGET_LANE_COUNT())
        {
            ScalerDpAuxRxSetDpcdMirrorBitValue(_D0_INPUT_PORT, 0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D0_PORT_TARGET_LANE_COUNT());

            bDPRx0DoLongHotPlug = _TRUE;
        }

        if(GET_DP_RX_D0_EDID_SWITCH() == _TRUE)
        {
            CLR_DP_RX_D0_EDID_SWITCH();

            bDPRx0DoLongHotPlug = _TRUE;
        }

#if(_DP_MST_SUPPORT == _ON)
        if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && (GET_DP_RX_D0_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
        {
            SET_DP_RX_D0_PORT_TARGET_VERSION(_DP_VERSION_1_2);
        }
#endif

        if(ScalerDpAuxRxVersionChange(_D0_INPUT_PORT, GET_DP_RX_D0_PORT_TARGET_VERSION()) == _TRUE)
        {
#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRxSetBaseInputPort(_D0_INPUT_PORT);

            if((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
               (GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
               (GET_DP_MST_RX_REPLY_BUF_FREE() == _FALSE))
            {
                if(ScalerDpRxGetMstCapability(_D0_INPUT_PORT) == _FALSE)
                {
                    CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN();
#if(_DP_TX_SUPPORT == _ON)
                    SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);
#endif
                    SET_DP_MST_RX_REPLY_BUF_FREE();
                }
                else
                {
                    return;
                }
            }
#endif

            ScalerDpAuxRxChangeDpcdVersion(_D0_INPUT_PORT);

            bDPRx0DoLongHotPlug = _TRUE;
        }

        if(ScalerDpAuxRxLinkRateCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }

#if(_DP_RX_FEC_SUPPORT == _ON)
        ScalerDpAuxRxFecDpcdSetting(_D0_INPUT_PORT);
#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON))
        if(ScalerDpMacTxBlockStatusCheck(_D0_INPUT_PORT) == _TRUE)
        {
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

        ScalerDpAuxRxSwitchDpcdAddrIrqSetting(_D0_INPUT_PORT);

        if((bDPRx0DoLongHotPlug == _TRUE) && (ScalerDpRxGetHotPlugStatus(_D0_INPUT_PORT) == _HIGH))
        {
#if(_DP_MST_SUPPORT == _ON)
            if(ScalerDpRxGetMstCapability(_D0_INPUT_PORT) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_LONG_HPD_EVENT);
            }
        }

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)


        // D1 Port Version Switch
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_AUDIO_SUPPORT == _ON)
        if(ScalerDpAuxRxAudioCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        if(ScalerDrrDpAdaptiveSyncCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(ScalerDrrFreeSyncDpCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDscDecoderDpCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
        if(ScalerDpRxPRModepCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
        if(ScalerDpRxAuxlessAlpmCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
        if(ScalerDpRxHdrCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif
#endif

        if(ScalerDpAuxRxGetDpcdBitInfo(_D1_INPUT_PORT, 0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D1_PORT_TARGET_LANE_COUNT())
        {
            ScalerDpAuxRxSetDpcdMirrorBitValue(_D1_INPUT_PORT, 0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D1_PORT_TARGET_LANE_COUNT());

            bDPRx1DoLongHotPlug = _TRUE;
        }

        if(GET_DP_RX_D1_EDID_SWITCH() == _TRUE)
        {
            CLR_DP_RX_D1_EDID_SWITCH();

            bDPRx1DoLongHotPlug = _TRUE;
        }

#if(_DP_MST_SUPPORT == _ON)
        if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT) && (GET_DP_RX_D1_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
        {
            SET_DP_RX_D1_PORT_TARGET_VERSION(_DP_VERSION_1_2);
        }
#endif

        if(ScalerDpAuxRxVersionChange(_D1_INPUT_PORT, GET_DP_RX_D1_PORT_TARGET_VERSION()) == _TRUE)
        {
#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRxSetBaseInputPort(_D1_INPUT_PORT);

            if((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
               (GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
               (GET_DP_MST_RX_REPLY_BUF_FREE() == _FALSE))
            {
                if(ScalerDpRxGetMstCapability(_D1_INPUT_PORT) == _FALSE)
                {
                    CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN();
#if(_DP_TX_SUPPORT == _ON)
                    SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);
#endif
                    SET_DP_MST_RX_REPLY_BUF_FREE();
                }
                else
                {
                    return;
                }
            }
#endif

            ScalerDpAuxRxChangeDpcdVersion(_D1_INPUT_PORT);

            bDPRx1DoLongHotPlug = _TRUE;
        }

        if(ScalerDpAuxRxLinkRateCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }

#if(_DP_RX_FEC_SUPPORT == _ON)
        ScalerDpAuxRxFecDpcdSetting(_D1_INPUT_PORT);
#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON))
        if(ScalerDpMacTxBlockStatusCheck(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif

        ScalerDpAuxRxSwitchDpcdAddrIrqSetting(_D1_INPUT_PORT);

        if((bDPRx1DoLongHotPlug == _TRUE) && (ScalerDpRxGetHotPlugStatus(_D1_INPUT_PORT) == _HIGH))
        {
#if(_DP_MST_SUPPORT == _ON)
            if(ScalerDpRxGetMstCapability(_D1_INPUT_PORT) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_LONG_HPD_EVENT);
            }
        }

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)


        // D2 Port Version Switch
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_AUDIO_SUPPORT == _ON)
        if(ScalerDpAuxRxAudioCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        if(ScalerDrrDpAdaptiveSyncCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(ScalerDrrFreeSyncDpCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDscDecoderDpCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
        if(ScalerDpRxPRModepCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
        if(ScalerDpRxAuxlessAlpmCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
        if(ScalerDpRxHdrCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif
#endif

        if(ScalerDpAuxRxGetDpcdBitInfo(_D2_INPUT_PORT, 0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D2_PORT_TARGET_LANE_COUNT())
        {
            ScalerDpAuxRxSetDpcdMirrorBitValue(_D2_INPUT_PORT, 0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D2_PORT_TARGET_LANE_COUNT());

            bDPRx2DoLongHotPlug = _TRUE;
        }

        if(GET_DP_RX_D2_EDID_SWITCH() == _TRUE)
        {
            CLR_DP_RX_D2_EDID_SWITCH();

            bDPRx2DoLongHotPlug = _TRUE;
        }

#if(_DP_MST_SUPPORT == _ON)
        if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX2_PORT) && (GET_DP_RX_D2_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
        {
            SET_DP_RX_D2_PORT_TARGET_VERSION(_DP_VERSION_1_2);
        }
#endif

        if(ScalerDpAuxRxVersionChange(_D2_INPUT_PORT, GET_DP_RX_D2_PORT_TARGET_VERSION()) == _TRUE)
        {
#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRxSetBaseInputPort(_D2_INPUT_PORT);

            if((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
               (GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
               (GET_DP_MST_RX_REPLY_BUF_FREE() == _FALSE))
            {
                if(ScalerDpRxGetMstCapability(_D2_INPUT_PORT) == _FALSE)
                {
                    CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN();
#if(_DP_TX_SUPPORT == _ON)
                    SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);
#endif
                    SET_DP_MST_RX_REPLY_BUF_FREE();
                }
                else
                {
                    return;
                }
            }
#endif

            ScalerDpAuxRxChangeDpcdVersion(_D2_INPUT_PORT);

            bDPRx2DoLongHotPlug = _TRUE;
        }

        if(ScalerDpAuxRxLinkRateCapabilitySwitchProc(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }

#if(_DP_RX_FEC_SUPPORT == _ON)
        ScalerDpAuxRxFecDpcdSetting(_D2_INPUT_PORT);
#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON))
        if(ScalerDpMacTxBlockStatusCheck(_D2_INPUT_PORT) == _TRUE)
        {
            bDPRx2DoLongHotPlug = _TRUE;
        }
#endif

        ScalerDpAuxRxSwitchDpcdAddrIrqSetting(_D2_INPUT_PORT);

        if((bDPRx2DoLongHotPlug == _TRUE) && (ScalerDpRxGetHotPlugStatus(_D2_INPUT_PORT) == _HIGH))
        {
#if(_DP_MST_SUPPORT == _ON)
            if(ScalerDpRxGetMstCapability(_D2_INPUT_PORT) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_LONG_HPD_EVENT);
            }
        }

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)


#if(_DP_MST_SUPPORT == _ON)
        // Mst Port Switch
        ScalerDpMstRxCapabilitySwitchProc();
#endif

        CLR_DP_RX_CAPABILITY_SWITCHED();
    }
}

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Link Rate Set
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpCalculateLinkRate(EnumInputPort enumInputPort)
{
    EnumDpLinkRate enumDpLinkRate = _DP_LINK_NONE;
    WORD usDpInputClkRang = _INPUTCLOCK_RANG_DP;
    BYTE ucBitPerComponent = _DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT;
    DWORD ulDpInputBitRate = (DWORD)usDpInputClkRang * ucBitPerComponent * 3;

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    if(ScalerSyncGetTypeCSupportStatus(enumInputPort) == _TRUE)
    {
        usDpInputClkRang = _INPUTCLOCK_RANG_USBC;
        ulDpInputBitRate = (DWORD)usDpInputClkRang * ucBitPerComponent * 3;
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == 0x00)
            {
                enumDpLinkRate = DP_LINK_RATE_ADJUST(GET_DP_RX_D0_PORT_TARGET_LANE_COUNT(), ulDpInputBitRate);

                if(enumDpLinkRate > GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE())
                {
                    enumDpLinkRate = GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE();
                }
            }
            else
            {
                enumDpLinkRate = GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE();
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == 0x00)
            {
                enumDpLinkRate = DP_LINK_RATE_ADJUST(GET_DP_RX_D1_PORT_TARGET_LANE_COUNT(), ulDpInputBitRate);

                if(enumDpLinkRate > GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE())
                {
                    enumDpLinkRate = GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE();
                }
            }
            else
            {
                enumDpLinkRate = GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE();
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == 0x00)
            {
                enumDpLinkRate = DP_LINK_RATE_ADJUST(GET_DP_RX_D2_PORT_TARGET_LANE_COUNT(), ulDpInputBitRate);

                if(enumDpLinkRate > GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE())
                {
                    enumDpLinkRate = GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE();
                }
            }
            else
            {
                enumDpLinkRate = GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE();
            }

            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            break;
#endif
        default:

            break;
    }

    ScalerDpAuxRxSetDpcdMaxLinkRateCapability(enumInputPort, _DP_VERSION_1_4, enumDpLinkRate);
}
#endif

//--------------------------------------------------
// Description  : Decision DP HPD Toggle Behavior
// Input Value  : Power Action State
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpPowerSwitchHpdToggleProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_D0_DP_SUPPORT == _ON)
            if(ScalerSyncDpPowerSwitchHpdToggleCheck(_D0_INPUT_PORT, enumPowerAction) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_HPD_LOW_RESET_AUX);
            }
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_DP_SUPPORT == _ON)
            if(ScalerSyncDpPowerSwitchHpdToggleCheck(_D1_INPUT_PORT, enumPowerAction) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_HPD_LOW_RESET_AUX);
            }
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_DP_SUPPORT == _ON)
            if(ScalerSyncDpPowerSwitchHpdToggleCheck(_D2_INPUT_PORT, enumPowerAction) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_HPD_LOW_RESET_AUX);
            }
#endif // End of #if(_D2_DP_SUPPORT == _ON)

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

#if(_D0_DP_SUPPORT == _ON)
            if(ScalerSyncDpPowerSwitchHpdToggleCheck(_D0_INPUT_PORT, enumPowerAction) == _TRUE)
            {
                if(ScalerDpRxGetMstCapability(_D0_INPUT_PORT) == _TRUE)
                {
                    // Instead of _DP_HPD_ASSERTED, do the _DP_MST_LONG_HPD_EVENT to prevent the DC off/on toggled quickly.
                    ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
                }
                else
                {
                    // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                    ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_LONG_HPD_EVENT);
                }
            }
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_DP_SUPPORT == _ON)
            if(ScalerSyncDpPowerSwitchHpdToggleCheck(_D1_INPUT_PORT, enumPowerAction) == _TRUE)
            {
                if(ScalerDpRxGetMstCapability(_D1_INPUT_PORT) == _TRUE)
                {
                    // Instead of _DP_HPD_ASSERTED, do the _DP_MST_LONG_HPD_EVENT to prevent the DC off/on toggled quickly.
                    ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
                }
                else
                {
                    // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                    ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_LONG_HPD_EVENT);
                }
            }
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_DP_SUPPORT == _ON)
            if(ScalerSyncDpPowerSwitchHpdToggleCheck(_D2_INPUT_PORT, enumPowerAction) == _TRUE)
            {
                if(ScalerDpRxGetMstCapability(_D2_INPUT_PORT) == _TRUE)
                {
                    // Instead of _DP_HPD_ASSERTED, do the _DP_MST_LONG_HPD_EVENT to prevent the DC off/on toggled quickly.
                    ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
                }
                else
                {
                    // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                    ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_LONG_HPD_EVENT);
                }
            }
#endif // End of #if(_D2_DP_SUPPORT == _ON)

            break;

        case _POWER_ACTION_OFF_TO_FAKE_OFF:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DP DC OFF HPD Toggle
// Input Value  : enumPowerAction
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpPowerSwitchHpdToggleCheck(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_DP_MST_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_NORMAL_TO_FAKE_OFF)
            {
                if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(enumInputPort) == _TRUE)
                {
                    return _FALSE;
                }

#if(_DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT == _ON)
                if(GET_DP_DC_OFF_HPD_HIGH() == _TRUE)
                {
                    return _FALSE;
                }
#endif
            }

            if(ScalerDpRxGetMstCapability(enumInputPort) == _TRUE)
            {
                return _TRUE;
            }
#endif

            if(GET_DP_DC_OFF_HPD_HIGH() == _TRUE)
            {
                return _FALSE;
            }

            return _TRUE;

        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // 2002h Has Been Read and Cancel Rx Mst Msg Finish during PS/ PD
            if(ScalerDpAuxRxGetCommandNoReply(enumInputPort) == _TRUE)
            {
                ScalerDpAuxRxClearCommandNoReply(enumInputPort);

                return _TRUE;
            }

            if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
            {
                if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _LOW)
                {
                    return _TRUE;
                }

#if(_DP_MST_SUPPORT == _ON)
                if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(enumInputPort) == _TRUE)
                {
                    CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(enumInputPort);

                    return _FALSE;
                }
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
                if(GET_DP_DC_ON_HPD_TOGGLE_MODE() == _DP_HPD_TOGGLE_NONE)
                {
                    return _FALSE;
                }
#endif

#if(_DP_MST_SUPPORT == _ON)
                if(ScalerDpRxGetMstCapability(enumInputPort) == _TRUE)
                {
                    return _TRUE;
                }
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                return _FALSE;
#endif

#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
                if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT0)
                {
                    return _FALSE;
                }
#endif

#if(_DP_DC_ON_LONG_HPD_ASSERT_COMPATIBLE_MODE == _ON)
                return _TRUE;
#endif
            }

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Check Hot Plug Event Exist
// Input Value  : None
// Output Value : _TRUE -> Exist; _FALSE -> Not Exist
//--------------------------------------------------
bit ScalerSyncDpCheckUrgentHotPlugEventExist(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if((GET_DP_RX0_HOTPLUG_ASSERT_TYPE() != _DP_HPD_NONE) && (GET_DP_RX0_HOTPLUG_ASSERT_TYPE() > _DP_HPD_LOW))
    {
        return _TRUE;
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if((GET_DP_RX1_HOTPLUG_ASSERT_TYPE() != _DP_HPD_NONE) && (GET_DP_RX1_HOTPLUG_ASSERT_TYPE() > _DP_HPD_LOW))
    {
        return _TRUE;
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if((GET_DP_RX2_HOTPLUG_ASSERT_TYPE() != _DP_HPD_NONE) && (GET_DP_RX2_HOTPLUG_ASSERT_TYPE() > _DP_HPD_LOW))
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Check Hdcp Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpCheckHdcpEnable(void)
{
#if(_D0_DP_SUPPORT == _ON)
    // Check HDCP Enable Status
    if(ScalerDpMacDphyRxHdcpCheckEnabled(_D0_INPUT_PORT) == _TRUE)
    {
        SET_DP_RX0_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX0_HDCP_CHECK_ENABLE();
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    // Check HDCP Enable Status
    if(ScalerDpMacDphyRxHdcpCheckEnabled(_D1_INPUT_PORT) == _TRUE)
    {
        SET_DP_RX1_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX1_HDCP_CHECK_ENABLE();
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    // Check HDCP Enable Status
    if(ScalerDpMacDphyRxHdcpCheckEnabled(_D2_INPUT_PORT) == _TRUE)
    {
        SET_DP_RX2_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX2_HDCP_CHECK_ENABLE();
    }
#endif
}

//--------------------------------------------------
// Description  : DP Port Get Hdcp Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSyncDpGetHdcpEnable(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return GET_DP_RX0_HDCP_CHECK_ENABLE();
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return GET_DP_RX1_HDCP_CHECK_ENABLE();
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return GET_DP_RX2_HDCP_CHECK_ENABLE();
#endif

        default:
            break;
    }

    return _DISABLE;
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Fake Power Off Check
// Input Value  : enumInputPort
// Output Value : True  --> Fake Power Off
//                False --> Power Off
//--------------------------------------------------
bit ScalerSyncDpFakePowerOffCheck(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;
    bit bCheckResult = _FALSE;

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerSyncGetPortType(enumInputPort) != _PORT_DP)
        {
            continue;
        }

        if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(enumInputPort) == _TRUE)
        {
            bCheckResult = _TRUE;

            continue;
        }

        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0)
        {
            // Let MSG keep proccessing
            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT1) == _BIT1)
            {
                // Keep HPD high if upstream is source
                if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT2) == _BIT2)
                {
                    // DP Rx MST DC OFF HPD Toggle Not Process
                    SET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(enumInputPort);
                }

                bCheckResult = _TRUE;

                continue;
            }

#if(_DP_TX_SUPPORT == _ON)
            if(enumInputPort == GET_DP_RX_MAIN_PORT())
            {
                if((GET_DP_MST_RX_GEN_DOWN_REQUEST_MSG() != _DP_MSG_NONE) || (GET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE) || (GET_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE() == _TRUE))
                {
                    bCheckResult = _TRUE;
                }
            }
#endif
        }
    }

    return bCheckResult;
}

//--------------------------------------------------
// Description  : Proc DP HPD Toggle Behavior when MST Fake Off Timer Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpMstFakeOffDoneProc(void)
{
#if(_D0_DP_SUPPORT == _ON)
    CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(_D0_INPUT_PORT);

    if(ScalerDpMacDphyRxHdcpCheckEnabled(_D0_INPUT_PORT) == _TRUE)
    {
        SET_DP_RX0_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX0_HDCP_CHECK_ENABLE();
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(_D1_INPUT_PORT);

    if(ScalerDpMacDphyRxHdcpCheckEnabled(_D1_INPUT_PORT) == _TRUE)
    {
        SET_DP_RX1_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX1_HDCP_CHECK_ENABLE();
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD(_D2_INPUT_PORT);

    if(ScalerDpMacDphyRxHdcpCheckEnabled(_D2_INPUT_PORT) == _TRUE)
    {
        SET_DP_RX2_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX2_HDCP_CHECK_ENABLE();
    }
#endif

    ScalerSyncDpPowerSwitchHpdToggleProc(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
}
#endif

#if(_DUAL_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check whether Current Timing is Reasonable
// Input Value  : Hwidth and VHeight
// Output Value : TRUE => OK
//--------------------------------------------------
bit ScalerSyncDualDpDoubleCheck(EnumInputPort enumInputPort)
{
    EnumDpMacSel enumMac = ScalerDpRxGetMacSwitch(enumInputPort);
    WORD usHwidth = ScalerDpMacStreamRxGetHwidth(enumInputPort);
    WORD usVHeight = ScalerDpMacStreamRxGetVheight(enumInputPort);

    if((usHwidth == 0) || (usVHeight == 0))
    {
        return _FALSE;
    }

    switch(enumMac)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            if(g_stDpMacStreamRx0Info.stDpLinkInfo.b1InterlaceStatus == _TRUE)
            {
                usVHeight *= 2;
            }

            g_pstColorInfo[_DUAL_DP_INPUT_PORT] = g_pstColorInfo[enumInputPort];

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            if(g_stDpMacStreamRx1Info.stDpLinkInfo.b1InterlaceStatus == _TRUE)
            {
                usVHeight *= 2;
            }

            g_pstColorInfo[_DUAL_DP_INPUT_PORT] = g_pstColorInfo[enumInputPort];

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            if(g_stDpMacStreamRx2Info.stDpLinkInfo.b1InterlaceStatus == _TRUE)
            {
                usVHeight *= 2;
            }

            g_pstColorInfo[_DUAL_DP_INPUT_PORT] = g_pstColorInfo[enumInputPort];

            break;
#endif

        default:
        case _DP_MAC_DUAL:

            g_pstColorInfo[_DUAL_DP_INPUT_PORT] = g_pstColorInfo[_DUAL_DP_MAIN_PORT];

            break;
    }

    // Check aspect ratio
    if(usHwidth > usVHeight)
    {
        // For Normal Aspect Ratio
        if((usHwidth >> 1) < usVHeight)
        {
            return _TRUE;
        }
        else
        {
            PDATA_WORD(0) = ((DWORD)usHwidth * 100 / usVHeight);

            // For 21:9 Aspect
            if((PDATA_WORD(0) > 230) && (PDATA_WORD(0) < 240))
            {
                return _TRUE;
            }
        }
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Get Dp Rx Port Edid Bw
// Input Value  : enumDpEdidPort --> Dp Rx EDID port
// Output Value : Edid Native Bw, Unit: 0.01M
//--------------------------------------------------
WORD ScalerSyncGetDpRxPortEdidBw(EnumDpEdidPort enumDpEdidPort)
{
    switch(enumDpEdidPort)
    {
        case _D0_DP_EDID:

#if((_D0_DDC_CHANNEL_SEL == _DDC0) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            return (((WORD)MCU_DDCRAM_D0[0x37] << 8) | MCU_DDCRAM_D0[0x36]);
#endif

        case _D1_DP_EDID:

#if((_D1_DDC_CHANNEL_SEL == _DDC1) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            return (((WORD)MCU_DDCRAM_D1[0x37] << 8) | MCU_DDCRAM_D1[0x36]);
#endif

        case _D2_DP_EDID:

#if((_D2_DDC_CHANNEL_SEL == _DDC2) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            return (((WORD)MCU_DDCRAM_D2[0x37] << 8) | MCU_DDCRAM_D2[0x36]);
#endif

        default:
            break;
    }

    return 0;
}
#endif // #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx PowerProc
// Input Value  : EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            ScalerDpAuxTxInitial();

            ScalerDpMacTxInitial();

            ScalerDpPhyTxPowerControl(enumPowerAction);
            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
            {
                if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                {
                    // Clear Downstream Payload ID table
                    ScalerDpMacTxSyncDownStreamTableSetting(0x00, 0x00, 0x3F);
                }

                // Clear Daisy Source, Stream Info
                ScalerDpMacTxResetDaisySourceMux();
                ScalerDpMacTxResetStreamToIdMapping();
                ScalerDpMacTxResetDaisyStreamPositionReg();
            }
#endif

            // Grant the Extended Wake Timeout For Lttpr
            if(ScalerDpMacTxGetLttprInitialMode() != _DP_TX_LTTPR_NON_LTTPR_MODE)
            {
                ScalerDpMacTxLttprExtWakeTimeOutGrant();
            }

            // Power Down Tx Aux
            ScalerDpAuxTxPowerOffProc();

            // Set DPTx Force To Idle Pattern
            ScalerDpMacTxForceIdlePatternSetting();

            ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

            if((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG) && (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_INITIAL))
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }

            CLR_DP_MAC_TX_DOWNSTREAM_INFO_READY();

            ScalerDpPhyTxPowerControl(enumPowerAction);

            // Power Down ML PHY
            ScalerDpPhyTxMLPowerOff();

            // Power CMU PHY
            ScalerDpPhyTxCMUPowerOff();

            // Clear HPD IRQ Flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

            // Clear IRQ HPD Type Flag
            CLR_DP_TX_IRQ_HPD_TYPE();
            CLR_DP_TX_IRQ_HPD_TYPE_INT();
            CLR_DP_TX_IRQ_HPD_DETECTED();
            CLR_DP_TX_IRQ_HDCP_TYPE();

            CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
            CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();
            CLR_DP_TX_HDCP_AUTH_START();
            CLR_DP_TX_HDCP_AUTH_HOLD();

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Disable HDCP function, Encryption
            ScalerSetBit(P2B_48_DPTX_HDCP_CTRL1, ~(_BIT1 | _BIT0), 0x00);
#endif
            // Disable HDCP function, Encryption and Reset Repeater Flag
            ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~(_BIT4 | _BIT1 | _BIT0), 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            CLR_DP_HDCP2_TX_IRQ_TYPE();
#endif

            // Set DP Tx Default Coding Type
            SET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE(_CODING_TYPE_8B10B);
            SET_DP_TX_LT_PROCESSING(_FALSE);

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if((_DP_MST_SUPPORT == _ON) && (_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON))
#if(_DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT == _ON)
            if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#endif
            {
                ScalerDpMacMstToSstResetSourceMuxReg();
            }
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
#if(_DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT == _ON)
            if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#endif
            {
                if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST) && (GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_8B10B))
                {
                    ScalerDpMacTxForceIdlePatternSetting();
                }

                ScalerDpMacTxResetDaisySourceMuxReg();
            }
#endif

#if((_DP_MST_SUPPORT == _ON) && (_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON))
#if(_DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT == _ON)
            if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#endif
            {
                ScalerDpMacMstToSstResetSourceMuxReg();
            }
#endif

            break;

        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

#if((_DP_MST_SUPPORT == _ON) && (_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON))
            ScalerDpMacMstToSstRestoreSourceMuxBackupToReg();
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
            ScalerDpMacTxRestoreDaisySourceMuxBackupToReg();
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Decide Current Port DPTx whether Can Output or not
// Input Value  : InputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpTxCloneOutputPortCheck(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    enumInputPort = enumInputPort;
    enumPortType = enumPortType;

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(enumPortType == _PORT_DP)
    {
        if(ScalerDpMacTxDrrCloneOutputCheck(enumInputPort) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Hdcp Port Switch
// Input Value  : enumDisplayMode, enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpTxHdcpUpstreamSwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D0_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D0_PORT);
#endif
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D1_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D1_PORT);
#endif
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D2_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D2_PORT);
#endif
            break;
#endif

        default:
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_NO_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_NO_PORT);
#endif
    }
}

//--------------------------------------------------
// Description  : Get Upstream HDCP event
// Input Value  : None
// Output Value : EnumDPRxHDCPUpstreamAuthStatus
//--------------------------------------------------
EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_HDCP14_RX0_UPSTREAM_EVENT();
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_HDCP14_RX1_UPSTREAM_EVENT();
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        return GET_DP_HDCP14_RX2_UPSTREAM_EVENT();
    }
#endif

    return _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return ((ScalerDpMacDphyRxHdcpCheckValid(_D0_INPUT_PORT) == _TRUE) && (ScalerDpMacDphyRxHdcpCheckLvp(_D0_INPUT_PORT) == _TRUE));
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return ((ScalerDpMacDphyRxHdcpCheckValid(_D1_INPUT_PORT) == _TRUE) && (ScalerDpMacDphyRxHdcpCheckLvp(_D1_INPUT_PORT) == _TRUE));
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        return ((ScalerDpMacDphyRxHdcpCheckValid(_D2_INPUT_PORT) == _TRUE) && (ScalerDpMacDphyRxHdcpCheckLvp(_D2_INPUT_PORT) == _TRUE));
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP2 Auth State
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDPRxHDCPAuthState ScalerSyncDpHdcpGetAuthState(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_HDCP14_RX0_AUTH_STATE();
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_HDCP14_RX1_AUTH_STATE();
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        return GET_DP_HDCP14_RX2_AUTH_STATE();
    }
#endif

    return _DP_RX_HDCP_STATE_IDLE;
}

//--------------------------------------------------
// Description  : Check Downstream HDCP Reauth Execute or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcpDownstreamReAuthCheck(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        // In SST mode
        if(ScalerDpAuxRxGetDpcdBitInfo(_D0_INPUT_PORT, 0x00, 0x01, 0x11, _BIT0) == 0x00)
        {
            return ((ScalerDpMacDphyRxHdcpCheckValid(_D0_INPUT_PORT) == _TRUE) && (ScalerDpMacDphyRxHdcpCheckLvp(_D0_INPUT_PORT) == _TRUE));
        }
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        // In SST mode
        if(ScalerDpAuxRxGetDpcdBitInfo(_D1_INPUT_PORT, 0x00, 0x01, 0x11, _BIT0) == 0x00)
        {
            return ((ScalerDpMacDphyRxHdcpCheckValid(_D1_INPUT_PORT) == _TRUE) && (ScalerDpMacDphyRxHdcpCheckLvp(_D1_INPUT_PORT) == _TRUE));
        }
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        // In SST mode
        if(ScalerDpAuxRxGetDpcdBitInfo(_D2_INPUT_PORT, 0x00, 0x01, 0x11, _BIT0) == 0x00)
        {
            return ((ScalerDpMacDphyRxHdcpCheckValid(_D2_INPUT_PORT) == _TRUE) && (ScalerDpMacDphyRxHdcpCheckLvp(_D2_INPUT_PORT) == _TRUE));
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if HDCP Handshake is Urgent Case
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcpRepeaterCheckUrgentEvent(void)
{
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        if(GET_DP_HDCP2_RX0_REPEATER_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP2_RX0_REPEATER_AUTH_1_START() == _TRUE)
            {
                return _TRUE;
            }

            if(GET_DP_HDCP2_RX0_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE)
            {
                return _FALSE;
            }

            if(GET_DP_HDCP2_RX0_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE)
            {
                if(GET_DP_HDCP2_RX0_AUTH_STATE_CHANGE() == _TRUE)
                {
                    if((GET_DP_HDCP2_RX0_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_1) ||
                       (GET_DP_HDCP2_RX0_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_2))
                    {
                        return _TRUE;
                    }
                }

                if(GET_DP_HDCP2_RX0_UPSTREAM_EVENT() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE)
                {
                    return _TRUE;
                }
            }
        }
    }
#endif

    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        if(GET_DP_AUX_RX0_HDCP_REPEATER_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP14_RX0_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE)
            {
                return _FALSE;
            }

            if(GET_DP_HDCP14_RX0_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE)
            {
                if(GET_DP_HDCP14_RX0_AUTH_STATE_CHANGE() == _TRUE)
                {
                    if((GET_DP_HDCP14_RX0_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_1) ||
                       (GET_DP_HDCP14_RX0_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_2))
                    {
                        return _TRUE;
                    }
                }

                if(GET_DP_HDCP14_RX0_UPSTREAM_EVENT() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS)
                {
                    return _TRUE;
                }
            }
        }
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        if(GET_DP_HDCP2_RX1_REPEATER_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP2_RX1_REPEATER_AUTH_1_START() == _TRUE)
            {
                return _TRUE;
            }

            if(GET_DP_HDCP2_RX1_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE)
            {
                return _FALSE;
            }

            if(GET_DP_HDCP2_RX1_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE)
            {
                if(GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE() == _TRUE)
                {
                    if((GET_DP_HDCP2_RX1_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_1) ||
                       (GET_DP_HDCP2_RX1_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_2))
                    {
                        return _TRUE;
                    }
                }

                if(GET_DP_HDCP2_RX1_UPSTREAM_EVENT() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE)
                {
                    return _TRUE;
                }
            }
        }
    }
#endif

    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        if(GET_DP_AUX_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP14_RX1_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE)
            {
                return _FALSE;
            }

            if(GET_DP_HDCP14_RX1_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE)
            {
                if(GET_DP_HDCP14_RX1_AUTH_STATE_CHANGE() == _TRUE)
                {
                    if((GET_DP_HDCP14_RX1_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_1) ||
                       (GET_DP_HDCP14_RX1_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_2))
                    {
                        return _TRUE;
                    }
                }

                if(GET_DP_HDCP14_RX1_UPSTREAM_EVENT() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS)
                {
                    return _TRUE;
                }
            }
        }
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        if(GET_DP_HDCP2_RX2_REPEATER_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP2_RX2_REPEATER_AUTH_1_START() == _TRUE)
            {
                return _TRUE;
            }

            if(GET_DP_HDCP2_RX2_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE)
            {
                return _FALSE;
            }

            if(GET_DP_HDCP2_RX2_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE)
            {
                if(GET_DP_HDCP2_RX2_AUTH_STATE_CHANGE() == _TRUE)
                {
                    if((GET_DP_HDCP2_RX2_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_1) ||
                       (GET_DP_HDCP2_RX2_AUTH_STATE() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_2))
                    {
                        return _TRUE;
                    }
                }

                if(GET_DP_HDCP2_RX2_UPSTREAM_EVENT() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE)
                {
                    return _TRUE;
                }
            }
        }
    }
#endif

    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        if(GET_DP_AUX_RX2_HDCP_REPEATER_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP14_RX2_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE)
            {
                return _FALSE;
            }

            if(GET_DP_HDCP14_RX2_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE)
            {
                if(GET_DP_HDCP14_RX2_AUTH_STATE_CHANGE() == _TRUE)
                {
                    if((GET_DP_HDCP14_RX2_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_1) ||
                       (GET_DP_HDCP14_RX2_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_2))
                    {
                        return _TRUE;
                    }
                }

                if(GET_DP_HDCP14_RX2_UPSTREAM_EVENT() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS)
                {
                    return _TRUE;
                }
            }
        }
    }
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if((GET_DP_RX_HDCP2_UPSTREAM_PORT() != _HDCP_NO_PORT) &&
       (GET_DP_HDCP2_TX_AUTH_STATE() != _HDCP_2_2_TX_STATE_IDLE))
    {
        if(GET_DP_HDCP2_TX_AUTH_HOLD() == _TRUE)
        {
            return _TRUE;
        }

        if((GET_DP_HDCP2_TX_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS) ||
           (GET_DP_HDCP2_TX_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED))
        {
            return _TRUE;
        }
    }
#endif

    if((GET_DP_RX_HDCP_UPSTREAM_PORT() != _HDCP_NO_PORT) &&
       (GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE))
    {
        if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
        {
            if((GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_1) ||
               (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0) ||
               (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_2))
            {
                return _TRUE;
            }
        }

        if((GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
           (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Upstream HDCP2 event
// Input Value  : None
// Output Value : EnumDpHdcp2RxUpstreamAuthStatus
//--------------------------------------------------
EnumDpHdcp2RxUpstreamAuthStatus ScalerSyncDpHdcp2GetUpstreamEvent(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_HDCP2_RX0_UPSTREAM_EVENT();
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_HDCP2_RX1_UPSTREAM_EVENT();
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        return GET_DP_HDCP2_RX2_UPSTREAM_EVENT();
    }
#endif

    return _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP2 ContentStreamManagementStatus
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcp2GetContentStreamManagementStatus(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        if(ScalerDpHdcpRxGetHdcpMode(_D0_INPUT_PORT) == _HDCP_22)
        {
            return GET_DP_HDCP2_RX0_CONTENT_STREAM_MANAGEMENT();
        }
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        if(ScalerDpHdcpRxGetHdcpMode(_D1_INPUT_PORT) == _HDCP_22)

        {
            return GET_DP_HDCP2_RX1_CONTENT_STREAM_MANAGEMENT();
        }
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        if(ScalerDpHdcpRxGetHdcpMode(_D2_INPUT_PORT) == _HDCP_22)

        {
            return GET_DP_HDCP2_RX2_CONTENT_STREAM_MANAGEMENT();
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DP HDCP2.2 Mode Status
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
EnumHDCPType ScalerSyncDpGetHdcpModeStatus(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return ScalerDpHdcpRxGetHdcpMode(_D0_INPUT_PORT);
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return ScalerDpHdcpRxGetHdcpMode(_D1_INPUT_PORT);
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        return ScalerDpHdcpRxGetHdcpMode(_D2_INPUT_PORT);
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP Auth State
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDpHdcp2RxRepeaterAuthState ScalerSyncDpHdcp2GetAuthState(void)
{
#if(_D0_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_HDCP2_RX0_AUTH_STATE();
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_HDCP2_RX1_AUTH_STATE();
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D2_PORT)
    {
        return GET_DP_HDCP2_RX2_AUTH_STATE();
    }
#endif

    return _DP_RX_HDCP2_REPEATER_STATE_IDLE;
}
#endif

//--------------------------------------------------
// Description  : Change DP HDCP2.2 Repeater Capable Base On DPTX Clone Status
// Input Value  : InputPort, PortType, Clone Mode or not
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpHdcpRepeaterSupportProc(void)
{
#if(_D0_DP_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2Rx0RepeaterSupportProc();
#endif

    ScalerDpHdcp14Rx0RepeaterSupportProc();
#endif

#if(_D1_DP_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2Rx1RepeaterSupportProc();
#endif

    ScalerDpHdcp14Rx1RepeaterSupportProc();
#endif

#if(_D2_DP_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpHdcp2Rx2RepeaterSupportProc();
#endif

    ScalerDpHdcp14Rx2RepeaterSupportProc();
#endif
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if((_DP_SUPPORT == _ON) || (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get Dp Color Depth Value
// Input Value  : BYTE
// Output Value : ucColorDepthPreValue, enumColorSpace
//--------------------------------------------------
BYTE ScalerSyncDpGetColorDepthValue(BYTE ucColorDepthPreValue, EnumColorSpace enumColorSpace)
{
    BYTE ucColorDepth = 0;

    if(enumColorSpace != _COLOR_SPACE_RAW)
    {
        switch(ucColorDepthPreValue)
        {
            case 0:
                ucColorDepth = _COLOR_DEPTH_6_BITS;
                break;

            case 1:
                ucColorDepth = _COLOR_DEPTH_8_BITS;
                break;

            case 2:
                ucColorDepth = _COLOR_DEPTH_10_BITS;
                break;

            case 3:
                ucColorDepth = _COLOR_DEPTH_12_BITS;
                break;

            case 4:
                ucColorDepth = _COLOR_DEPTH_16_BITS;
                break;

            default:
                ucColorDepth = _COLOR_DEPTH_8_BITS;
                break;
        }
    }
    else
    {
        switch(ucColorDepthPreValue)
        {
            case 1:
                ucColorDepth = _COLOR_DEPTH_6_BITS;
                break;

            case 2:
                ucColorDepth = _COLOR_DEPTH_7_BITS;
                break;

            case 3:
                ucColorDepth = _COLOR_DEPTH_8_BITS;
                break;

            case 4:
                ucColorDepth = _COLOR_DEPTH_10_BITS;
                break;

            case 5:
                ucColorDepth = _COLOR_DEPTH_12_BITS;
                break;

            case 6:
                ucColorDepth = _COLOR_DEPTH_14_BITS;
                break;

            case 7:
                ucColorDepth = _COLOR_DEPTH_16_BITS;
                break;

            default:
                ucColorDepth = _COLOR_DEPTH_8_BITS;
                break;
        }
    }

    return ucColorDepth;
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DownLoad DPTx HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Key download port
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable Key download port
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : DownLoad TX HDCP AKsv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    for(pData[0] = ucSubAddr; pData[0] < ucLength; pData[0]++)
    {
        g_pucSyncHdcpAksvBackup[pData[0]] = pucReadArray[pData[0]];
    }

    DebugMessageDigital("8. HDCP Aksv Backup", g_pucSyncHdcpAksvBackup[0]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucSyncHdcpAksvBackup[1]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucSyncHdcpAksvBackup[2]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucSyncHdcpAksvBackup[3]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucSyncHdcpAksvBackup[4]);
}

//--------------------------------------------------
// Description  : DownLoad TX HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray)
{
    ScalerWrite(PBB_32_DP_HDCP_KEY_DL_PORT, usLength, pucReadArray, _NON_AUTOINC);
}
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : CLR inputPort & Set others Dx's Digital Port Switch Flag
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            CLR_DIGITAL_PORT_SWITCH_TO_D2();
            SET_DIGITAL_PORT_SWITCH_TO_D3();
            SET_DIGITAL_PORT_SWITCH_TO_D4();
            SET_DIGITAL_PORT_SWITCH_TO_D5();
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            SET_DIGITAL_PORT_SWITCH_TO_D2();
            CLR_DIGITAL_PORT_SWITCH_TO_D3();
            SET_DIGITAL_PORT_SWITCH_TO_D4();
            SET_DIGITAL_PORT_SWITCH_TO_D5();
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            SET_DIGITAL_PORT_SWITCH_TO_D2();
            SET_DIGITAL_PORT_SWITCH_TO_D3();
            CLR_DIGITAL_PORT_SWITCH_TO_D4();
            SET_DIGITAL_PORT_SWITCH_TO_D5();
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            SET_DIGITAL_PORT_SWITCH_TO_D2();
            SET_DIGITAL_PORT_SWITCH_TO_D3();
            SET_DIGITAL_PORT_SWITCH_TO_D4();
            CLR_DIGITAL_PORT_SWITCH_TO_D5();
            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : Input Port
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
EnumHDCPType ScalerSyncHdcpCheckEnabled(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_DP_SUPPORT == _ON)
            return ScalerDpHdcpRxGetValidMode(_D0_INPUT_PORT);

#elif((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT))
            if(ScalerTmdsMacRxHdcpEnabled(_D0_INPUT_PORT) == _TRUE)
            {
                return _HDCP_14;
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_DP_SUPPORT == _ON)
            return ScalerDpHdcpRxGetValidMode(_D1_INPUT_PORT);

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D1_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D1_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_DP_SUPPORT == _ON)
            return ScalerDpHdcpRxGetValidMode(_D2_INPUT_PORT);

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D2_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D2_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D3_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D3_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D4_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D4_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxHdcpEnabled(_D5_INPUT_PORT) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT))
                if(ScalerTmdsMacRxHdcpMode(_D5_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            return ScalerDpHdcpRxGetValidMode(GET_DUAL_DP_PORT_SWITCH_SELECT());
#endif

#if(_D9_DP_SUPPORT == _ON)
        case _D9_INPUT_PORT:

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            return ScalerDpHdcpRxGetValidMode(GET_DP_MST_RX_PXP_INPUT_PORT());
#endif
#endif
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : Input Port
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
EnumHDCPType ScalerSyncHdcpCheckEnabledUnderPowerOff(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_DP_SUPPORT == _ON)
            return ScalerDpHdcpRxGetEnabledMode(_D0_INPUT_PORT);

#elif((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT))
            if(ScalerTmdsMacRxHdcpEnabled(_D0_INPUT_PORT) == _TRUE)
            {
                return _HDCP_14;
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_DP_SUPPORT == _ON)
            return ScalerDpHdcpRxGetEnabledMode(_D1_INPUT_PORT);

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D1_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D1_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_DP_SUPPORT == _ON)
            return ScalerDpHdcpRxGetEnabledMode(_D2_INPUT_PORT);

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D2_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D2_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D3_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D3_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if(ScalerTmdsMacRxHdcpEnabled(_D4_INPUT_PORT) == _TRUE)
            {
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                if(ScalerTmdsMacRxHdcpMode(_D4_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxHdcpEnabled(_D5_INPUT_PORT) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT))
                if(ScalerTmdsMacRxHdcpMode(_D5_INPUT_PORT) == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            return ScalerDpHdcpRxGetValidMode(GET_DUAL_DP_PORT_SWITCH_SELECT());
#endif

#if(_D9_DP_SUPPORT == _ON)
        case _D9_INPUT_PORT:

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            return ScalerDpHdcpRxGetEnabledMode(GET_DP_MST_RX_PXP_INPUT_PORT());
#endif
#endif

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

#endif
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)


#if(_URGENT_EVENT_CHECK_MODE == _ON)
//--------------------------------------------------
// Description  : Check Urgent Event Occur
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncCheckUrgentEvent(void)
{
#if(_DP_MST_SUPPORT == _ON)
#if(_D0_DP_MST_PORT_SUPPORT == _ON)
    if((GET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(_D0_INPUT_PORT) == _FALSE) &&
       (ScalerDpMstRxCheckMsgTransition(_D0_INPUT_PORT) == _TRUE))
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif
#if(_D1_DP_MST_PORT_SUPPORT == _ON)
    if((GET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(_D1_INPUT_PORT) == _FALSE) &&
       (ScalerDpMstRxCheckMsgTransition(_D1_INPUT_PORT) == _TRUE))
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif
#if(_D2_DP_MST_PORT_SUPPORT == _ON)
    if((GET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(_D2_INPUT_PORT) == _FALSE) &&
       (ScalerDpMstRxCheckMsgTransition(_D2_INPUT_PORT) == _TRUE))
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    if(GET_HDCP22_AUTHENTICATION_ACTIVE() == _TRUE)
    {
        DebugMessageHDCP2("HDCP2 Urgent", g_ucHdcp2AuthActive);

        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

#if(_DP_SUPPORT == _ON)
    if(ScalerSyncDpCheckUrgentHotPlugEventExist() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }

#if(_DP_TX_SUPPORT == _ON)
    if(GET_DP_TX_LT_PROCESSING() == _TRUE)
    {
        DebugMessageDpTx("Dp Tx Link Training Urgent", 1);

        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif
#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    if(GET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(ScalerSyncDpHdcpRepeaterCheckUrgentEvent() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Urgent Event Occured Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncGetUrgentEventFlg(void)
{
    return GET_URGENT_EVENT_OCCUR_FLG();
}

//--------------------------------------------------
// Description  : Clear Urgent Event Occured Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncClrUrgentEventFlg(void)
{
    CLR_URGENT_EVENT_OCCUR_FLG();
}
#endif // End of #if(_URGENT_EVENT_CHECK_MODE == _ON)

//--------------------------------------------------
// Description  : Get cable status
// Input Value  : enumInputPort --> source search port
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit ScalerSyncGetCableStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return GET_A0_CABLE_STATUS();
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return GET_D0_CABLE_STATUS();
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return GET_D1_CABLE_STATUS();
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return GET_D2_CABLE_STATUS();
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return GET_D3_CABLE_STATUS();
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return GET_D4_CABLE_STATUS();
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return GET_D5_CABLE_STATUS();
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:
            return ((GET_D0_CABLE_STATUS() == _TRUE) &&
                    (GET_D1_CABLE_STATUS() == _TRUE));
#endif

#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
        case _D8_INPUT_PORT:
            return ((GET_D1_CABLE_STATUS() == _TRUE) &&
                    (GET_D2_CABLE_STATUS() == _TRUE));
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
        case _D9_INPUT_PORT:
            return _TRUE;
#endif

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D12_INPUT_PORT:
            return GET_D12_CABLE_STATUS();
#endif

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D13_INPUT_PORT:
            return GET_D13_CABLE_STATUS();
#endif

#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D14_INPUT_PORT:
            return GET_D14_CABLE_STATUS();
#endif

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D15_INPUT_PORT:
            return GET_D15_CABLE_STATUS();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set cable status
// Input Value  : enumInputPort --> source search port
//                bStatus --> cable status
// Output Value : None
//--------------------------------------------------
void ScalerSyncSetCableStatus(EnumInputPort enumInputPort, bit bStatus)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            SET_A0_CABLE_STATUS(bStatus);
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            SET_D0_CABLE_STATUS(bStatus);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            SET_D1_CABLE_STATUS(bStatus);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            SET_D2_CABLE_STATUS(bStatus);
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            SET_D3_CABLE_STATUS(bStatus);
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            SET_D4_CABLE_STATUS(bStatus);
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            SET_D5_CABLE_STATUS(bStatus);
            break;
#endif

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D12_INPUT_PORT:
            SET_D12_CABLE_STATUS(bStatus);
            break;
#endif

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D13_INPUT_PORT:
            SET_D13_CABLE_STATUS(bStatus);
            break;
#endif

#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D14_INPUT_PORT:
            SET_D14_CABLE_STATUS(bStatus);
            break;
#endif

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D15_INPUT_PORT:
            SET_D15_CABLE_STATUS(bStatus);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Source Cable Pin Status Detection
// Input Value  : enumInputPort --> source search port
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit ScalerSyncGetCablePinStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return !PCB_A0_PIN();
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return !PCB_D0_PIN();
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return !PCB_D1_PIN();
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return !PCB_D2_PIN();
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return !PCB_D3_PIN();
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return !PCB_D4_PIN();
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return !PCB_D5_PIN();
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:
            return (!PCB_D0_PIN() && !PCB_D1_PIN());
#endif

#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
        case _D8_INPUT_PORT:
            return (!PCB_D1_PIN() && !PCB_D2_PIN());
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
        case _D9_INPUT_PORT:
            return _TRUE;
#endif

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D12_INPUT_PORT:
            return !PCB_D12_PIN();
#endif

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        case _D13_INPUT_PORT:
            return !PCB_D13_PIN();
#endif

#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D14_INPUT_PORT:
            return !PCB_D14_PIN();
#endif

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        case _D15_INPUT_PORT:
            return !PCB_D15_PIN();
#endif

        default:
            return _FALSE;
    }
}

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Type-C alt mode staus
// Input Value  : enumInputPort --> source search port
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit ScalerSyncGetTypeCAltModeStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return GET_D0_DP_TYPE_C_ALTMODE_STATUS();
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_D1_DP_TYPE_C_ALTMODE_STATUS();
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_D2_DP_TYPE_C_ALTMODE_STATUS();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set Type-C alt mode staus
// Input Value  : enumInputPort --> source search port
//                bStatus --> cable status
// Output Value : None
//--------------------------------------------------
void ScalerSyncSetTypeCAltModeStatus(EnumInputPort enumInputPort, bit bStatus)
{
    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_D0_DP_TYPE_C_ALTMODE_STATUS(bStatus);
            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_D1_DP_TYPE_C_ALTMODE_STATUS(bStatus);
            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_D2_DP_TYPE_C_ALTMODE_STATUS(bStatus);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check if Type-C is supported for given input port
// Input Value  : enumInputPort --> source search port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncGetTypeCSupportStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return (_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return (_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return (_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON);
#endif

        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Process Required to be Performed for Active State
// Input Value  : Current Source Type
// Output Value : None
//--------------------------------------------------
void ScalerSyncActiveProc(EnumSourceType enumSourceType)
{
    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_DVI:
#if((_D0_HDMI_SUPPORT == _ON) && (_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                ScalerTmdsMacRxNoClkWatchDogProc(_D0_INPUT_PORT);
            }
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                ScalerTmdsMacRxNoClkWatchDogProc(_D1_INPUT_PORT);
            }
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                ScalerTmdsMacRxNoClkWatchDogProc(_D2_INPUT_PORT);
            }
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON))
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                ScalerTmdsMacRxNoClkWatchDogProc(_D3_INPUT_PORT);
            }
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON))
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                ScalerTmdsMacRxNoClkWatchDogProc(_D4_INPUT_PORT);
            }
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON))
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
            {
                ScalerTmdsMacRxNoClkWatchDogProc(_D5_INPUT_PORT);
            }
#endif
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:
#if(_D0_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                ScalerTmdsMacRxHdmiAVMuteProc(_D0_INPUT_PORT);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
                ScalerTmdsMacRxNoClkWatchDogProc(_D0_INPUT_PORT);
#endif
            }
#endif

#if(_D1_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                ScalerTmdsMacRxHdmiAVMuteProc(_D1_INPUT_PORT);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
                ScalerTmdsMacRxNoClkWatchDogProc(_D1_INPUT_PORT);
#endif
            }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                ScalerTmdsMacRxHdmiAVMuteProc(_D2_INPUT_PORT);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
                ScalerTmdsMacRxNoClkWatchDogProc(_D2_INPUT_PORT);
#endif
            }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                ScalerTmdsMacRxHdmiAVMuteProc(_D3_INPUT_PORT);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
                ScalerTmdsMacRxNoClkWatchDogProc(_D3_INPUT_PORT);
#endif
            }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                ScalerTmdsMacRxHdmiAVMuteProc(_D4_INPUT_PORT);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
                ScalerTmdsMacRxNoClkWatchDogProc(_D4_INPUT_PORT);
#endif
            }
#endif

#if(_D5_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
            {
                ScalerTmdsMacRxHdmiAVMuteProc(_D5_INPUT_PORT);

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
                ScalerTmdsMacRxNoClkWatchDogProc(_D5_INPUT_PORT);
#endif
            }
#endif

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Sync reset Process for Mode Reset
// Input Value  : enumInputPort       --> Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncResetProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
        case _A0_INPUT_PORT:
            break;
#endif

        case _D0_INPUT_PORT:

#if(_D0_DP_SUPPORT == _ON)
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            // Disable DSC VB-ID[6] IRQ and Watch Dog
            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D0_INPUT_PORT, _DISABLE);
#endif
            ScalerDpMacStreamRxStreamReset(_D0_INPUT_PORT);

            // Mac Secondary Data Block Reset
            ScalerDpMacStreamRxSecDataReset(enumInputPort);
#endif

#if(_D0_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxTimerEventReset(_D0_INPUT_PORT);
#endif // End of #if(_D0_HDMI_SUPPORT == _ON)

            break;

        case _D1_INPUT_PORT:

#if(_D1_DP_SUPPORT == _ON)
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            // Disable DSC VB-ID[6] IRQ and Watch Dog
            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D1_INPUT_PORT, _DISABLE);
#endif
            ScalerDpMacStreamRxStreamReset(_D1_INPUT_PORT);

            // Mac Secondary Data Block Reset
            ScalerDpMacStreamRxSecDataReset(enumInputPort);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxTimerEventReset(_D1_INPUT_PORT);
#endif // End of #if(_D1_HDMI_SUPPORT == _ON)

            break;

        case _D2_INPUT_PORT:

#if(_D2_DP_SUPPORT == _ON)
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            // Disable DSC VB-ID[6] IRQ and Watch Dog
            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D2_INPUT_PORT, _DISABLE);
#endif
            ScalerDpMacStreamRxStreamReset(_D2_INPUT_PORT);

            // Mac Secondary Data Block Reset
            ScalerDpMacStreamRxSecDataReset(enumInputPort);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxTimerEventReset(_D2_INPUT_PORT);
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxTimerEventReset(_D3_INPUT_PORT);
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxTimerEventReset(_D4_INPUT_PORT);
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxTimerEventReset(_D5_INPUT_PORT);
#endif
            break;

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            ScalerDpMacStreamRxStreamReset(_DUAL_DP_INPUT_PORT);

            // Mac Secondary Data Block Reset
            ScalerDpMacStreamRxSecDataReset(enumInputPort);

            break;

#endif

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:

            ScalerDpMacStreamRxStreamReset(_D9_INPUT_PORT);

            // Mac Secondary Data Block Reset
            ScalerDpMacStreamRxSecDataReset(enumInputPort);

            break;
#endif

        default:
            break;
    }

#if((_DP_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
    ScalerDrrFreeSyncDpSetEnable(enumInputPort, _DISABLE);
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort) != _DSC_MAC_NONE)
    {
        ScalerDscDecoderReset(enumInputPort);
    }
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
    ScalerTmdsMacRxSetFreesyncProc(enumInputPort, _DISABLE);
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
    ScalerTmdsMacRxClrHdmi21VtemReceived(enumInputPort);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
    ScalerTmdsMacRxClrHdmi21AllmStatus(enumInputPort);
#if(_DM_FUNCTION == _ON)
    ScalerTmdsMacRxClrDmAllmStatus(enumInputPort);
#endif
#endif
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    ScalerHdmiFrlMacRxClrCvtemReceived(enumInputPort);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(ScalerDpMacTxCloneGetCurrentInputPort() == enumInputPort)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
        {
            ScalerDpMacTxForceIdlePatternSetting();
        }
        else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) // for Clone OOR Case
        {

            // Clear Tx Clone Precheck flag
            SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_FALSE);

            // Clear Tx Clone Info Type
            SET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE(_INFO_TYPE_NONE);

            DebugMessageMst("Dp TX Clone: Clear Exceed BW", 0);

            // Clear Exceed BW Flag for Clone Mode
            CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
        }
    }
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
    if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
    {
        ScalerSyncDigitalClrColorimetryChanged(enumInputPort);
        ScalerSyncDigitalClrColorimetryExtChanged(enumInputPort);
        ScalerSyncDigitalClrQuantizationChanged(enumInputPort);
    }
#endif

#if(_HDR10_SUPPORT == _ON)
    CLR_HDR10_RX_INFO_DATA(enumInputPort);
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
    CLR_HDR10_SBTM_RX_INFO_DATA(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Sync reset all port rocess for Mode Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncResetAllProc(void)
{
    EnumInputPort enumInputPort = 0;

    for(enumInputPort = _A0_INPUT_PORT; enumInputPort < _NO_INPUT_PORT; ++enumInputPort)
    {
        ScalerSyncResetProc(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Power Process for Interface
// Input Value  : Power Action
// Output Value : None
//--------------------------------------------------
void ScalerSyncPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_HW_VGA_ADC_SUPPORT == _ON)
            // ADC Bandgap Enable
            ScalerVgaAdcBandgap(_ON);
#endif

            // GDI Bandgap Enable
            ScalerGDIPhyRxBandgap(_ON);

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerDpRxPowerSwitch(enumPowerAction);
#endif

#if(_DRR_SUPPORT == _ON)
            ScalerDrrTestPinEnable();
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)
            {
#if(_D1_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D1_INPUT_PORT);
                }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D2_INPUT_PORT);
                }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D3_INPUT_PORT);
                }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D4_INPUT_PORT);
                }
#endif
            }
#endif

            if((enumPowerAction == _POWER_ACTION_PS_TO_NORMAL) || (enumPowerAction == _POWER_ACTION_OFF_TO_FAKE_OFF))
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                ScalerGDIPhyRxPowerProc(_D0_INPUT_PORT, enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, enumPowerAction);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
                ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, enumPowerAction);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
                ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, enumPowerAction);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
                ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, enumPowerAction);
#endif
            }

#if(_HW_HDMI_SCDC_RESET == _OFF)
#if(_HDMI_FRL_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)
            {
#if(_D1_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxScdcReset(_D1_INPUT_PORT);
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxScdcReset(_D2_INPUT_PORT);
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxScdcReset(_D3_INPUT_PORT);
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
                ScalerHdmiFrlMacRxScdcReset(_D4_INPUT_PORT);
#endif
            }
#endif
#else
#if(_HDMI_SUPPORT == _ON)
            ScalerTmdsMacRxHwScdcReset();
#endif
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            // Clear Urgent Event Occured Flag When System Flow Is Runing to Normal
            ScalerSyncClrUrgentEventFlg();
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_HW_VGA_ADC_SUPPORT == _ON)
            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerVgaAdcBandgap(_OFF);
#endif

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMstRxPowerProc(enumPowerAction);
#endif

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerDpRxPowerSwitch(enumPowerAction);
#endif

            ScalerGDIPhyRxBandgap(_OFF);

#if(_DSC_DECODER_SUPPORT == _ON)
            ScalerDscDecoderResetAllPort();
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D0_INPUT_PORT, enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, enumPowerAction);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, enumPowerAction);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, enumPowerAction);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, enumPowerAction);
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
            ScalerTmdsPhyRxClkLaneZ0StartToggle();
#endif

#if(_HW_VGA_ADC_SUPPORT == _ON)
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0xC2);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_HW_VGA_ADC_SUPPORT == _ON)
            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerVgaAdcBandgap(_OFF);
#endif

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMstRxPowerProc(enumPowerAction);
#endif

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D0_INPUT_PORT, enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, enumPowerAction);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, enumPowerAction);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, enumPowerAction);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, enumPowerAction);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerSyncDpCheckHdcpEnable();
            ScalerDpRxPowerSwitch(enumPowerAction);
#endif

#if(_HDMI_CEC_SUPPORT == _OFF)
            ScalerGDIPhyRxBandgap(_OFF);
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
            ScalerDscDecoderResetAllPort();
#endif

#if((_DP_SUPPORT != _ON) && (_HDMI_SUPPORT != _ON))
            SET_INTERRUPT_ENABLE_STATUS((_INT_TMDS | _INT_DP), _DISABLE);
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_PS_TO_OFF)
            {
#if(_D1_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D1_INPUT_PORT);
                }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D2_INPUT_PORT);
                }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D3_INPUT_PORT);
                }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerTmdsPhyRxClkLaneZ0StopToggle(_D4_INPUT_PORT);
                }
#endif
            }
#endif

#if(_VGA_SUPPORT == _ON)
            // Disable sync pulse detect
            ScalerVgaSyncProcPulseDetectEnable(_DISABLE);
#endif

#if(_HW_VGA_ADC_SUPPORT == _ON)
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0x42);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerDpRxPowerSwitch(enumPowerAction);
#endif
            break;

        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

            break;

        default:
            break;
    }
}

#if(_HW_VGA_ADC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Power Down VGA Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncAdcApllPowerDown(void)
{
    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // Power down APLL by Misc Control
    ScalerSetBit(P1_F2_APLL_MISC, ~_BIT7, _BIT7);

    // Power down ADC VCM/ADC clock/SOG Power/RGB Channel
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
}
#endif

//--------------------------------------------------
// Description  : GDI Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceProc(EnumInputPort enumInputPort, bit bEnable)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            ScalerSyncInterfaceD0Proc(bEnable);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            ScalerSyncInterfaceD1Proc(bEnable);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            ScalerSyncInterfaceD2Proc(bEnable);
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            ScalerSyncInterfaceD3Proc(bEnable);
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            ScalerSyncInterfaceD4Proc(bEnable);
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            ScalerSyncInterfaceD5Proc(bEnable);
            break;
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:
            ScalerSyncInterfaceD0Proc(bEnable);
            ScalerSyncInterfaceD1Proc(bEnable);
            break;
#endif

#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
        case _D8_INPUT_PORT:
            ScalerSyncInterfaceD1Proc(bEnable);
            ScalerSyncInterfaceD2Proc(bEnable);
            break;
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
        case _D9_INPUT_PORT:
            ScalerSyncInterfaceD9Proc(bEnable);
            break;
#endif

        default:
            break;
    }
}

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD0Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D0_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
        if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
        {
            SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D0_INPUT_PORT);
        }
#endif
        if(GET_TMDS_RX0_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D0_INPUT_PORT);
        }

#else // Else of #if((_D0_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)

        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE))
        {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
            if(ScalerTmdsMacRxDdcCheckBusy(_D0_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
            {
                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_MAC_RX_HPD_NORMAL);
                ScalerTmdsMacRxHotPlugEvent(_D0_INPUT_PORT);
            }
        }
#endif

#endif // End of #if((_D0_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        if(GET_POWER_ISO_DPMAC_FLG() == _FALSE)
        {
            ScalerDpMacRxPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
        }
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            ScalerTmdsMacRxPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
            ScalerGDIPhyRxPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D0_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
        ScalerTmdsMacRxPowerProc(_D0_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        ScalerDpMacRxPowerProc(_D0_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#endif
    }
}
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx1 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD1Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
        if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D1_INPUT_PORT);
        }
#endif
        if(ScalerTmdsMacRxGetToggleZ0Event(_D1_INPUT_PORT) == _TRUE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D1_INPUT_PORT);
        }

#else // Else of #if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D1_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME))
#else
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D1_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME) && (ScalerTmdsMacRxGetInterfaceSwitching(_D1_INPUT_PORT) == _FALSE))
#endif
        {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D1_HDMI_FRL_SUPPORT == _OFF))
            if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D1_INPUT_PORT)) == _TRUE) || (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D1_INPUT_PORT) == _TRUE))
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
                if(ScalerTmdsMacRxDdcCheckBusy(_D1_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D1_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D1_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D1_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D1_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D1_INPUT_PORT);
#endif
                }
            }
        }
#endif

#endif // End of #if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(GET_POWER_ISO_DPMAC_FLG() == _FALSE)
        {
            ScalerDpMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
        }
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
        {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_HDMI_5V_STATUS() == _TRUE))
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                ScalerTmdsMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
            }
            else
            {
                ScalerTmdsMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#else
            ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
#else // else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHPDTriggerEvent(_D1_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
            {
                ScalerTmdsMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D1_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE))
#else
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D1_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D1_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D1_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D1_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D1_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D1_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D1_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D1_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D1_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D1_INPUT_PORT);
#endif
                }
            }
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D1_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE))
#else
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D1_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D1_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D2_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D1_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D1_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D1_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D1_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D1_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
                    ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if(_HDMI_FRL_SUPPORT == _ON)
                    ScalerHdmiFrlMacRxIrqRestoreAfterZ0On(_D1_INPUT_PORT);
#endif
#else
                    ScalerTmdsMacRxSetInterfaceSwitching(_D1_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D1_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D1_INPUT_PORT);
#endif
                }
            }
            else
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
                if(ScalerTmdsMacRxGetHPDTriggerEvent(_D1_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if((_HDMI_SUPPORT == _ON) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
                    ScalerTmdsMacRxClrInterfaceSwitching(_D1_INPUT_PORT);
#endif
                }
            }
#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
        }
    }
    else
    {
#if((_HDMI_FRL_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
        // Clear Flt_Ready before switch port
        ScalerHdmiFrlMacRxClrFltReady(_D1_INPUT_PORT);
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
        ScalerTmdsMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        ScalerDpMacRxPowerProc(_D1_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#endif
    }
}
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD2Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
        if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D2_INPUT_PORT);
        }
#endif
        if(ScalerTmdsMacRxGetToggleZ0Event(_D2_INPUT_PORT) == _TRUE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D2_INPUT_PORT);
        }

#else // Else of #if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D2_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME))
#else
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D2_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME) && (ScalerTmdsMacRxGetInterfaceSwitching(_D2_INPUT_PORT) == _FALSE))
#endif
        {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D1_HDMI_FRL_SUPPORT == _OFF))
            if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D2_INPUT_PORT)) == _TRUE) || (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D2_INPUT_PORT) == _TRUE))
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
                if(ScalerTmdsMacRxDdcCheckBusy(_D2_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D2_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D2_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D2_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D2_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D2_INPUT_PORT);
#endif
                }
            }
        }
#endif

#endif // End of #if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        if(GET_POWER_ISO_DPMAC_FLG() == _FALSE)
        {
            ScalerDpMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
        }
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
        {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_HDMI_5V_STATUS() == _TRUE))
            {
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                ScalerTmdsMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
            }
            else
            {
                ScalerTmdsMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#else
            ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
#else // else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHPDTriggerEvent(_D2_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
            {
                ScalerTmdsMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D2_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE))
#else
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D2_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D2_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D2_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D2_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D2_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D2_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D2_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D2_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D2_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D2_INPUT_PORT);
#endif
                }
            }
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D2_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE))
#else
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D2_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D2_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D2_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D2_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D2_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D2_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D2_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D2_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
                    ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if(_HDMI_FRL_SUPPORT == _ON)
                    ScalerHdmiFrlMacRxIrqRestoreAfterZ0On(_D2_INPUT_PORT);
#endif
#else
                    ScalerTmdsMacRxSetInterfaceSwitching(_D2_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D2_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D2_INPUT_PORT);
#endif
                }
            }
            else
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
                if(ScalerTmdsMacRxGetHPDTriggerEvent(_D2_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if((_HDMI_SUPPORT == _ON) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
                    ScalerTmdsMacRxClrInterfaceSwitching(_D2_INPUT_PORT);
#endif
                }
            }
#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        }
    }
    else
    {
#if((_HDMI_FRL_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT))
        // Clear Flt_Ready before switch port
        ScalerHdmiFrlMacRxClrFltReady(_D2_INPUT_PORT);
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
        ScalerTmdsMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        ScalerDpMacRxPowerProc(_D2_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#endif
    }
}
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD3Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
        if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D3_INPUT_PORT);
        }
#endif
        if(ScalerTmdsMacRxGetToggleZ0Event(_D3_INPUT_PORT) == _TRUE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D3_INPUT_PORT);
        }

#else // Else of #if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D3_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME))
#else
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D3_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME) && (ScalerTmdsMacRxGetInterfaceSwitching(_D3_INPUT_PORT) == _FALSE))
#endif
        {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D3_HDMI_FRL_SUPPORT == _OFF))
            if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D3_INPUT_PORT)) == _TRUE) || (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D3_INPUT_PORT) == _TRUE))
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
                if(ScalerTmdsMacRxDdcCheckBusy(_D3_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D3_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D3_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D3_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D3_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D3_INPUT_PORT);
#endif
                }
            }
        }
#endif

#endif // End of #if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

        if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
        {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D3_HDMI_5V_STATUS() == _TRUE))
            {
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
                ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
            }
            else
            {
                ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#else
            ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
#else // else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHPDTriggerEvent(_D3_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
            {
                ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D3_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE))
#else
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D3_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D3_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D3_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D3_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D3_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D3_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D3_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D3_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D3_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D3_INPUT_PORT);
#endif
                }
            }
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D3_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE))
#else
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D3_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D3_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D3_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D3_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D3_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D3_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D3_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D3_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
                    ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if(_HDMI_FRL_SUPPORT == _ON)
                    ScalerHdmiFrlMacRxIrqRestoreAfterZ0On(_D3_INPUT_PORT);
#endif
#else
                    ScalerTmdsMacRxSetInterfaceSwitching(_D3_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D3_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D3_INPUT_PORT);
#endif
                }
            }
            else
#endif
            {
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                if(ScalerTmdsMacRxGetHPDTriggerEvent(_D3_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxClrInterfaceSwitching(_D3_INPUT_PORT);
#endif
                }
            }
#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        }
    }
    else
    {
#if(_HDMI_FRL_SUPPORT == _ON)
        // Clear Flt_Ready before switch port
        ScalerHdmiFrlMacRxClrFltReady(_D3_INPUT_PORT);
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
        ScalerTmdsMacRxPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#endif
    }
}
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD4Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
        if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D4_INPUT_PORT);
        }
#endif
        if(ScalerTmdsMacRxGetToggleZ0Event(_D4_INPUT_PORT) == _TRUE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D4_INPUT_PORT);
        }

#else // Else of #if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D4_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME))
#else
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D4_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME) && (ScalerTmdsMacRxGetInterfaceSwitching(_D4_INPUT_PORT) == _FALSE))
#endif
        {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D4_HDMI_FRL_SUPPORT == _OFF))
            if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D4_INPUT_PORT)) == _TRUE) || (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D4_INPUT_PORT) == _TRUE))
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
                if(ScalerTmdsMacRxDdcCheckBusy(_D4_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D4_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D4_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D4_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D4_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D4_INPUT_PORT);
#endif
                }
            }
        }
#endif

#endif // End of #if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

        if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
        {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_HDMI_5V_STATUS() == _TRUE))
            {
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_LOW);
                ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
            }
            else
            {
                ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#else
            ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
#else // else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHPDTriggerEvent(_D4_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
            {
                ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D4_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE))
#else
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D4_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D4_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D4_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D4_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D4_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D4_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D4_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxSetInterfaceSwitching(_D4_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D4_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D4_INPUT_PORT);
#endif
                }
            }
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D4_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE))
#else
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D4_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE) && (ScalerTmdsMacRxGetInterfaceSwitching(_D4_INPUT_PORT) == _FALSE))
#endif
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D4_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D4_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D4_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D4_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D4_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D4_INPUT_PORT);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _OFF)
                    ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if(_HDMI_FRL_SUPPORT == _ON)
                    ScalerHdmiFrlMacRxIrqRestoreAfterZ0On(_D4_INPUT_PORT);
#endif
#else
                    ScalerTmdsMacRxSetInterfaceSwitching(_D4_INPUT_PORT);
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D4_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D4_INPUT_PORT);
#endif
                }
            }
            else
#endif
            {
#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                if(ScalerTmdsMacRxGetHPDTriggerEvent(_D4_INPUT_PORT) == _TMDS_MAC_RX_HPD_NONE)
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
                    ScalerTmdsMacRxClrInterfaceSwitching(_D4_INPUT_PORT);
#endif
                }
            }
#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        }
    }
    else
    {
#if(_HDMI_FRL_SUPPORT == _ON)
        // Clear Flt_Ready before switch port
        ScalerHdmiFrlMacRxClrFltReady(_D4_INPUT_PORT);
#endif

        if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
        ScalerTmdsMacRxPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#endif
    }
}
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD5Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
        if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D5_INPUT_PORT);
        }
#endif
        if(ScalerTmdsMacRxGetToggleZ0Event(_D5_INPUT_PORT) == _TRUE)
        {
            ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, _TMDS_MAC_RX_HPD_ACER);
            ScalerTmdsMacRxHotPlugEvent(_D5_INPUT_PORT);
        }

#else // Else of #if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)

        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D5_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME))
        {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D5_HDMI_FRL_SUPPORT == _OFF))
            if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D5_INPUT_PORT)) == _TRUE) || (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D5_INPUT_PORT) == _TRUE))
#endif
            {
#if((_HDMI_SUPPORT == _ON) && (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
                if(ScalerTmdsMacRxDdcCheckBusy(_D5_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D5_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D5_INPUT_PORT);

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D5_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D5_INPUT_PORT);
#endif
                }
            }
        }
#endif

#endif // End of #if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

        if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
        {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_HDMI_5V_STATUS() == _TRUE))
            {
                PCB_D5_HOTPLUG(_D5_HOT_PLUG_LOW);
                ScalerTmdsMacRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                PCB_D5_HOTPLUG(_D5_HOT_PLUG_HIGH);
            }
            else
            {
                ScalerTmdsMacRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#else
            ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif
#else // else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            ScalerTmdsMacRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D5_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE))
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D5_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D5_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D5_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D5_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D5_INPUT_PORT);

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D5_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D5_INPUT_PORT);
#endif
                }
            }
            else if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE) || (ScalerTmdsMacRxGetPsWakeupHpdStatus(_D5_INPUT_PORT) == _TRUE)) && (GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE))
            {
#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D5_HDMI_FRL_SUPPORT == _OFF))
                if((ScalerMcuDdcGetSclToggleIrqStatus(ScalerMcuGetDdcChannelFromInputPort(_D5_INPUT_PORT)) == _FALSE) && (ScalerTmdsMacRxGetAcOnHpdToggleEvent(_D5_INPUT_PORT) == _FALSE))
                {
                    ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
                else
#endif
                {
                    ScalerTmdsMacRxSetHPDTriggerEvent(_D5_INPUT_PORT, _TMDS_MAC_RX_HPD_NORMAL);
                    ScalerTmdsMacRxHotPlugEvent(_D5_INPUT_PORT);
                    ScalerTmdsMacRxClrPsWakeupHpdStatus(_D5_INPUT_PORT);

                    ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_D5_HDMI_FRL_SUPPORT == _OFF))
                    ScalerTmdsMacRxClrAcOnHpdToggleEvent(_D5_INPUT_PORT);
#endif
                }
            }
            else
#endif
            {
                ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
        ScalerTmdsMacRxPowerProc(_D5_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
#endif
    }
}
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceD9Proc(bit bEnable)
{
    bit bDpRxIsoFlag = _FALSE;
    bDpRxIsoFlag = bDpRxIsoFlag;

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    switch(GET_DP_MST_RX_PXP_INPUT_PORT())
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            bDpRxIsoFlag = GET_DIGITAL_PORT_SWITCH_TO_D0();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            bDpRxIsoFlag = GET_DIGITAL_PORT_SWITCH_TO_D1();
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            bDpRxIsoFlag = GET_DIGITAL_PORT_SWITCH_TO_D2();
            break;
#endif

        default:
            break;
    }

    if(bEnable == _ENABLE)
    {
#if(_D9_INPUT_PORT_TYPE == _D9_DP_PORT)
        if(GET_POWER_ISO_DPMAC_FLG() == _FALSE)
        {
            ScalerDpMacRxPowerProc(_D9_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            ScalerDpMacRxPowerProc(GET_DP_MST_RX_PXP_INPUT_PORT(), _POWER_ACTION_OFF_TO_NORMAL);
        }
#endif

        if(bDpRxIsoFlag == _FALSE)
        {
            ScalerGDIPhyRxPowerProc(_D9_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(bDpRxIsoFlag == _TRUE)
        {
            ScalerGDIPhyRxPowerProc(_D9_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
        }

        ScalerDpMacRxPowerProc(_D9_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
    }
#endif
#endif
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Digital Clr Colorimetry Changed
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrColorimetryChanged(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryChanged(_D0_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrColorimetryChanged(_D0_INPUT_PORT);
#endif
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryChanged(_D1_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrColorimetryChanged(_D1_INPUT_PORT);
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryChanged(_D2_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrColorimetryChanged(_D2_INPUT_PORT);
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryChanged(_D3_INPUT_PORT);
#else
            CLR_RX3_COLORIMETRY_CHANGED();
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryChanged(_D4_INPUT_PORT);
#else
            CLR_RX4_COLORIMETRY_CHANGED();
#endif
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryChanged(_D5_INPUT_PORT);
#else
            CLR_RX5_COLORIMETRY_CHANGED();
#endif
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
            ScalerDpMacStreamRxDigitalClrColorimetryChanged(_DUAL_DP_INPUT_PORT);
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:
            ScalerDpMacStreamRxDigitalClrColorimetryChanged(_D9_INPUT_PORT);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Digital Clr Colorimetry Extended Changed
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrColorimetryExtChanged(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryExtChanged(_D0_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(_D0_INPUT_PORT);
#endif
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryExtChanged(_D1_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(_D1_INPUT_PORT);
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryExtChanged(_D2_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(_D2_INPUT_PORT);
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryExtChanged(_D3_INPUT_PORT);
#else
            CLR_RX3_COLORIMETRY_EXT_CHANGED();
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryExtChanged(_D4_INPUT_PORT);
#else
            CLR_RX4_COLORIMETRY_EXT_CHANGED();
#endif
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrColorimetryExtChanged(_D5_INPUT_PORT);
#else
            CLR_RX5_COLORIMETRY_EXT_CHANGED();
#endif
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
            ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(_DUAL_DP_INPUT_PORT);
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:
            ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(_D9_INPUT_PORT);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Digital Clr Quantization Changed
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrQuantizationChanged(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrQuantizationChanged(_D0_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrQuantizationChanged(_D0_INPUT_PORT);
#endif
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrQuantizationChanged(_D1_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrQuantizationChanged(_D1_INPUT_PORT);
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrQuantizationChanged(_D2_INPUT_PORT);
#else
            ScalerDpMacStreamRxDigitalClrQuantizationChanged(_D2_INPUT_PORT);
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrQuantizationChanged(_D3_INPUT_PORT);
#else
            CLR_RX3_QUANTIZATION_CHANGED();
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrQuantizationChanged(_D4_INPUT_PORT);
#else
            CLR_RX4_QUANTIZATION_CHANGED();
#endif
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            ScalerTmdsMacRxDigitalClrQuantizationChanged(_D5_INPUT_PORT);
#else
            CLR_RX5_QUANTIZATION_CHANGED();
#endif
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
            ScalerDpMacStreamRxDigitalClrQuantizationChanged(_DUAL_DP_INPUT_PORT);
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:
            ScalerDpMacStreamRxDigitalClrQuantizationChanged(_D9_INPUT_PORT);
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Let Upper Layer Get I-domain Pixel Clk
// Input Value  : enumInputPort --> target port
// Output Value : Input Pixel Clk (in 0.1MHz)
//--------------------------------------------------
WORD ScalerSyncGetInputPixelClk(EnumInputPort enumInputPort)
{
    BYTE ucPixelClockRatio = 1;
    WORD usPixelClock = 0;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_420_SUPPORT == _ON)
    // Check 420 status
    if(ScalerColor420To422GetStatusByPort(enumInputPort) == _TRUE)
    {
        ucPixelClockRatio *= 2;
    }
#endif
#endif

    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            usPixelClock = GET_A0_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            usPixelClock = GET_D0_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            usPixelClock = GET_D1_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            usPixelClock = GET_D2_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            usPixelClock = GET_D3_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            usPixelClock = GET_D4_INPUT_PIXEL_CLK();
            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            usPixelClock = GET_D5_INPUT_PIXEL_CLK();
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            if(GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT)
            {
                usPixelClock = ScalerDpRxGetInputPixelClock(_DUAL_DP_MAIN_PORT);
                ucPixelClockRatio *= 2;
            }
            else
            {
                usPixelClock = ScalerDpRxGetInputPixelClock(GET_DUAL_DP_PORT_SWITCH_SELECT());
            }

            break;
#endif


#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_DP_SUPPORT == _ON)
        case _D9_INPUT_PORT:
            usPixelClock = GET_D9_INPUT_PIXEL_CLK();
            break;
#endif
#endif

        default:
            break;
    }

    return usPixelClock * ucPixelClockRatio;
}

//--------------------------------------------------
// Description  : Let Upper Layer Get I-domain Pixel Clk
// Input Value  : enumInputPort --> target port
// Output Value : Input Pixel Clk (in 0.1MHz)
//--------------------------------------------------
WORD ScalerSyncGetNativeInputPixelClk(EnumInputPort enumInputPort)
{
    BYTE ucPixelClockRatio = 1;
    WORD usPixelClock = 0;

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_COLOR_IP_420_SUPPORT == _ON)
    // Check 420 status
    if(ScalerColor420To422GetStatusByPort(enumInputPort) == _TRUE)
    {
        ucPixelClockRatio *= 2;
    }
#endif
#endif

    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            usPixelClock = GET_A0_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            usPixelClock = GET_D0_NATIVE_INPUT_PIXEL_CLK();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_DP_SUPPORT == _ON)
            usPixelClock = GET_D1_NATIVE_INPUT_PIXEL_CLK();
#elif(_D1_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D1_INPUT_PORT) == _FROM_HDMI_FRL_DSC_MAC)
            {
                usPixelClock = GET_D1_NATIVE_INPUT_PIXEL_CLK();
            }
            else // FRL(Uncompress) or TMDS
            {
                usPixelClock = GET_D1_INPUT_PIXEL_CLK();
            }

#if(_HDMI21_FVA_SUPPORT == _ON)
            if(ScalerTmdsMacRxHdmi21GetFvaFactor(_D1_INPUT_PORT) > 1)
            {
                usPixelClock = usPixelClock / ScalerTmdsMacRxHdmi21GetFvaFactor(_D1_INPUT_PORT);
            }
#endif
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if(_D2_DP_SUPPORT == _ON)
            usPixelClock = GET_D2_NATIVE_INPUT_PIXEL_CLK();
#elif(_D2_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D2_INPUT_PORT) == _FROM_HDMI_FRL_DSC_MAC)
            {
                usPixelClock = GET_D2_NATIVE_INPUT_PIXEL_CLK();
            }
            else // FRL(Uncompress) or TMDS
            {
                usPixelClock = GET_D2_INPUT_PIXEL_CLK();
            }

#if(_HDMI21_FVA_SUPPORT == _ON)
            if(ScalerTmdsMacRxHdmi21GetFvaFactor(_D2_INPUT_PORT) > 1)
            {
                usPixelClock = usPixelClock / ScalerTmdsMacRxHdmi21GetFvaFactor(_D2_INPUT_PORT);
            }
#endif
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if(_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D3_INPUT_PORT) == _FROM_HDMI_FRL_DSC_MAC)
            {
                usPixelClock = GET_D3_NATIVE_INPUT_PIXEL_CLK();
            }
            else // FRL(Uncompress) or TMDS
            {
                usPixelClock = GET_D3_INPUT_PIXEL_CLK();
            }

#if(_HDMI21_FVA_SUPPORT == _ON)
            if(ScalerTmdsMacRxHdmi21GetFvaFactor(_D3_INPUT_PORT) > 1)
            {
                usPixelClock = usPixelClock / ScalerTmdsMacRxHdmi21GetFvaFactor(_D3_INPUT_PORT);
            }
#endif
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if(_HDMI_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(_D4_INPUT_PORT) == _FROM_HDMI_FRL_DSC_MAC)
            {
                usPixelClock = GET_D4_NATIVE_INPUT_PIXEL_CLK();
            }
            else // FRL(Uncompress) or TMDS
            {
                usPixelClock = GET_D4_INPUT_PIXEL_CLK();
            }

#if(_HDMI21_FVA_SUPPORT == _ON)
            if(ScalerTmdsMacRxHdmi21GetFvaFactor(_D4_INPUT_PORT) > 1)
            {
                usPixelClock = usPixelClock / ScalerTmdsMacRxHdmi21GetFvaFactor(_D4_INPUT_PORT);
            }
#endif
#endif
            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            usPixelClock = GET_D5_NATIVE_INPUT_PIXEL_CLK();
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:

            if(GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT)
            {
                usPixelClock = ScalerDpRxGetNativeInputPixelClock(_DUAL_DP_MAIN_PORT);
                ucPixelClockRatio *= 2;
            }
            else
            {
                usPixelClock = ScalerDpRxGetNativeInputPixelClock(GET_DUAL_DP_PORT_SWITCH_SELECT());
            }

            break;
#endif


#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)

        case _D9_INPUT_PORT:
            usPixelClock = GET_D9_NATIVE_INPUT_PIXEL_CLK();
            break;
#endif
#endif

        default:
            break;
    }

    return usPixelClock * ucPixelClockRatio;
}

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
//--------------------------------------------------
// Description  : Get Vertical Timing Data From Interface
// Input Value  : enumSourceType -> Input Source, enumInputPort -> Input Port
// Output Value : _TRUE if _FROM_HDMI_FRL_MAC
//--------------------------------------------------
bit ScalerSyncGetVerticalTimingDataFromInterface(EnumSourceType enumSourceType, EnumInputPort enumInputPort)
{
    enumSourceType = enumSourceType;
    enumInputPort = enumInputPort;

#if(_HDMI_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_HDMI)
    {
        switch(ScalerTmdsMacRxGetHdmiVer(enumInputPort))
        {
            case _FROM_HDMI_TMDS_MAC:
                return _FALSE;
                break;

#if(_HDMI_FRL_SUPPORT == _ON)
            case _FROM_HDMI_FRL_MAC:
                return _TRUE;
                break;
#endif

#if(_DSC_MAC_DECODER_SUPPORT == _ON)
            case _FROM_HDMI_FRL_DSC_MAC:
#if(_FW_DSC_FRL_IVS_PRODUCE_BE == _ON)
                if(ScalerDrrIVSProduceByBE(enumSourceType, enumInputPort) == _TRUE)
#endif
                {
                    return _FALSE;
                }
                break;
#endif

            default:
                break;
        }
    }
#endif

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Get H Sync Width
// Input Value  : Pixel Clk in 0.1MHz
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerSyncGetHSWbyClk(WORD usInputPixelClk)
{
    WORD usHSWCal = ((WORD)_DE_ONLY_MODE_HSW_MEASURE_COUNTER * (GET_DWORD_MUL_DIV(usInputPixelClk, 100, _MEASURE_CLK) + 1));

    return ((usHSWCal < _DE_ONLY_MODE_HSW) ? _DE_ONLY_MODE_HSW : usHSWCal);
}

//--------------------------------------------------
// Description  : Get H start
// Input Value  : usHSWidth, Pixel Clk in 0.1MHz
// Output Value : H start modify by HSWidth
//--------------------------------------------------
WORD ScalerSyncGetHStartbyHSW(WORD usHSWidth, WORD usInputPixelClk)
{
    WORD usHStart = (usHSWidth + ((WORD)_DE_ONLY_MODE_HSW_MEASURE_COUNTER * (GET_DWORD_MUL_DIV(usInputPixelClk, 100, _MEASURE_CLK) + 1)));

    return ((usHStart < _DE_ONLY_MODE_HSTART) ? _DE_ONLY_MODE_HSTART : usHStart);
}

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DRR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get H start
// Input Value  : usHSWidth
// Output Value : H start modify by HSWidth
//--------------------------------------------------
void ScalerSyncDrrDataExchangeProc(bit bEnable)
{
    DebugMessageSystem("Data Exchange Send Data CMD Group", _DATA_EXCHANGE_KERNEL_DATA);
    DebugMessageSystem("Data Exchange Send Data CMD Type", _DATA_EXCHANGE_KERNEL_DATA_FREESYNC_ENABLE);

    BYTE ucSyncDpFreeSyncEnable = 0;

    if(bEnable == _ENABLE)
    {
        ucSyncDpFreeSyncEnable = 1;
    }

    if(ScalerMcuDataExchangeSendData((BYTE)_DATA_EXCHANGE_KERNEL_DATA, (BYTE)_DATA_EXCHANGE_KERNEL_DATA_FREESYNC_ENABLE, 1, &ucSyncDpFreeSyncEnable) == _TRUE)
    {
        DebugMessageSystem("FreeSync Enable Status Send Done", ucSyncDpFreeSyncEnable);
    }
    else
    {
        DebugMessageSystem("FreeSync Enable Status Send Fail", ucSyncDpFreeSyncEnable);
    }
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DownLoad HDCP BKsv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucTemp = 0;

    for(ucTemp = ucSubAddr; ucTemp < ucLength; ucTemp++)
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        ScalerSetDataPortByte(P72_C3_HDCP_AP, ucTemp, pucReadArray[ucTemp]);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        ScalerSetDataPortByte(P73_C3_HDCP_AP, ucTemp, pucReadArray[ucTemp]);
#endif

        g_pucSyncHdcpBksvBackup[ucTemp] = pucReadArray[ucTemp];
    }

    DebugMessageDigital("8. HDCP Bksv Backup", g_pucSyncHdcpBksvBackup[0]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucSyncHdcpBksvBackup[1]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucSyncHdcpBksvBackup[2]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucSyncHdcpBksvBackup[3]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucSyncHdcpBksvBackup[4]);
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadKey(WORD usLength, BYTE *pucReadArray)
{
#if(_DP_SUPPORT == _ON)
    ScalerDpMacDphyRxHdcpDownLoadKeyToSram(usLength, pucReadArray);
#endif

#if(_HW_HDCP_1_4_SEPARATE_CIPHER_SUPPORT == _ON)
    // Download HDCP Key to SRAM
    ScalerHdcp14RxCipherDownLoadKeyToSram(usLength, pucReadArray);
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    ScalerWrite(P72_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    ScalerWrite(P73_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpEnableDownLoadKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_SUPPORT == _ON)
        ScalerDpMacDphyRxHdcpDownLoadKey(bEnable);
#endif

#if(_HW_HDCP_1_4_SEPARATE_CIPHER_SUPPORT == _ON)
        ScalerHdcp14RxCipherDownLoadKey(bEnable);
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)

        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P72_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P72_C2_HDCP_PCR, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P2E_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P2E_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);

        // Set Support HDCP 2.2 Feature
        ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_50_PORT_PAGE72_HDCP2_VER, 0x04);
        g_pucTmdsMacRx3Caps[0] = 0x02;
        g_pucTmdsMacRx3Caps[1] = 0x00;
        g_pucTmdsMacRx3Caps[2] = 0x00;
#endif

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P72_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)

        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P73_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P73_C2_HDCP_PCR, ~(_BIT7 | _BIT6 | _BIT4), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P73_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P6D_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P6D_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);

        // Set Support HDCP 2.2 Feature
        ScalerSetDataPortByte(P73_C3_HDCP_AP, _P73_C4_PT_50_PORT_PAGE73_HDCP2_VER, 0x04);
        g_pucTmdsMacRx4Caps[0] = 0x02;
        g_pucTmdsMacRx4Caps[1] = 0x00;
        g_pucTmdsMacRx4Caps[2] = 0x00;
#endif

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P73_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif
    }
    else if(bEnable == _DISABLE)
    {
#if(_DP_SUPPORT == _ON)
        ScalerDpMacDphyRxHdcpDownLoadKey(bEnable);
#endif

#if(_HW_HDCP_1_4_SEPARATE_CIPHER_SUPPORT == _ON)
        ScalerHdcp14RxCipherDownLoadKey(bEnable);
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT7, _BIT7);

        // For Chroma HDCP1.4 20k IIC r0 issue
        // Clear only AKSV IRQ Flag
        ScalerSetBit(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7));

        // Enable HDCP 1.4 AKSV IRQ
        ScalerSetBit(P72_AA_TMDS_ABC1, ~(_BIT4), _BIT4);
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P73_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P73_C0_HDCP_CR, ~_BIT7, _BIT7);

        // For Chroma HDCP1.4 20k IIC r0 issue
        // Clear only AKSV IRQ Flag
        ScalerSetBit(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7));

        // Enable HDCP 1.4 AKSV IRQ
        ScalerSetBit(P73_AA_TMDS_ABC1, ~(_BIT4), _BIT4);
#endif

        SET_INTERRUPT_ENABLE_STATUS((_INT_TMDS | _INT_DP), _ENABLE);
    }
}

#endif

#if(((_DP_SUPPORT == _ON) && (_DP_PR_MODE_SUPPORT == _ON)) || ((_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Check PR mode status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncPRModeCheckProc(EnumInputPort enumInputPort)
{
#if(_DP_PR_MODE_SUPPORT == _ON)
    if(ScalerDpRxPRModeGetEnable(enumInputPort) == _TRUE)
    {
        DebugMessageDpRx("DP Rx Panel Replay Enable", 0);

        ScalerMDomainPRModeInitial();

        ScalerDpMacStreamRxPRModeCheckProc(enumInputPort);

        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x05, _BIT2) == 0x00)
        {
            // Set DP Stream Regen In Sync
            ScalerDpAuxRxSinkStatusSet(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_IN_SYNC);
        }
    }
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
    if(ScalerTmdsMacRxGetFreesyncReplayProc(enumInputPort) == _ENABLE)
    {
        ScalerMDomainPRModeInitial();
    }
#endif
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Current DM Port Support Status
// Input Value  : enumInputPort --> Input port
// Output Value : None
//--------------------------------------------------
void ScalerSyncDMSetSupport(EnumInputPort enumInputPort, EnumDMSupport enumDMSupport)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            SET_D0_DM_SUPPORT(enumDMSupport);
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            SET_D1_DM_SUPPORT(enumDMSupport);
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            SET_D2_DM_SUPPORT(enumDMSupport);
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            SET_D3_DM_SUPPORT(enumDMSupport);
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            SET_D4_DM_SUPPORT(enumDMSupport);
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            SET_D5_DM_SUPPORT(enumDMSupport);
#endif
            break;

        default:
            break;
    }
}
#endif
