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
// ID Code      : ScalerMDomainInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Enumerations of Frame Sync/ Free Run mode
//--------------------------------------------------
typedef enum
{
    _FRAME_SYNC_MODE,
    _FREE_RUN_MODE,
    _MN_FRAME_SYNC_MODE,
} EnumFrameSyncModeType;

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MDomain Input Info.
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_H_POLARITY()                 (g_stMDomainInputData.b1HSP)
#define GET_MDOMAIN_INPUT_V_POLARITY()                 (g_stMDomainInputData.b1VSP)
#define GET_MDOMAIN_INPUT_INTERLACE_FLG()              (g_stMDomainInputData.b1Interlace)
#define GET_MDOMAIN_INPUT_HFREQ()                      (g_stMDomainInputData.usHFreq)
#define GET_MDOMAIN_INPUT_HTOTAL()                     (g_stMDomainInputData.usHTotal)
#define GET_MDOMAIN_INPUT_HWIDTH()                     (g_stMDomainInputData.usHWidth)
#define GET_MDOMAIN_INPUT_HSTART()                     (g_stMDomainInputData.usHStart)
#define GET_MDOMAIN_INPUT_HSYNCWIDTH()                 (g_stMDomainInputData.usHSWidth)
#define GET_MDOMAIN_INPUT_VFREQ()                      (g_stMDomainInputData.usVFreq)
#define GET_MDOMAIN_INPUT_VTOTAL()                     (g_stMDomainInputData.usVTotal)
#define GET_MDOMAIN_INPUT_VHEIGHT()                    (g_stMDomainInputData.usVHeight)
#define GET_MDOMAIN_INPUT_VSTART()                     (g_stMDomainInputData.usVStart)
#define GET_MDOMAIN_INPUT_VSYNCWIDTH()                 (g_stMDomainInputData.usVSWidth)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_STRUCTURE(x)                 (g_stMDomainInputData = (x))

#define SET_MDOMAIN_INPUT_HSTART(x)                    (g_stMDomainInputData.usHStart = (x))
#define SET_MDOMAIN_INPUT_HWIDTH(x)                    (g_stMDomainInputData.usHWidth = (x))
#define SET_MDOMAIN_INPUT_HTOTAL(x)                    (g_stMDomainInputData.usHTotal = (x))

#define SET_MDOMAIN_INPUT_VSTART(x)                    (g_stMDomainInputData.usVStart = (x))
#define SET_MDOMAIN_INPUT_VHEIGHT(x)                   (g_stMDomainInputData.usVHeight = (x))
#define SET_MDOMAIN_INPUT_VTOTAL(x)                    (g_stMDomainInputData.usVTotal = (x))

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------
#define GET_MDOMAIN_OUTPUT_HSTART()                    (g_stMDomainOutputData.usHStart)
#define GET_MDOMAIN_OUTPUT_HBSTART()                   (g_stMDomainOutputData.usHBackStart)
#define GET_MDOMAIN_OUTPUT_HWIDTH()                    (g_stMDomainOutputData.usHWidth)
#define GET_MDOMAIN_OUTPUT_HBWIDTH()                   (g_stMDomainOutputData.usHBackWidth)
#define GET_MDOMAIN_OUTPUT_HTOTAL()                    (g_stMDomainOutputData.usHTotal)

#define GET_MDOMAIN_OUTPUT_VSTART()                    (g_stMDomainOutputData.usVStart)
#define GET_MDOMAIN_OUTPUT_VBSTART()                   (g_stMDomainOutputData.usVBackStart)
#define GET_MDOMAIN_OUTPUT_VHEIGHT()                   (g_stMDomainOutputData.usVHeight)
#define GET_MDOMAIN_OUTPUT_VBHEIGHT()                  (g_stMDomainOutputData.usVBackHeight)
#define GET_MDOMAIN_OUTPUT_VTOTAL()                    (g_stMDomainOutputData.usVTotal)
#define GET_MDOMAIN_OUTPUT_VSYNCHEIGHT()               (g_stMDomainOutputData.usVSyncHeight)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------

#define SET_MDOMAIN_OUTPUT_HSTART(x)                   (g_stMDomainOutputData.usHStart = (x))
#define SET_MDOMAIN_OUTPUT_HBSTART(x)                  (g_stMDomainOutputData.usHBackStart = (x))
#define SET_MDOMAIN_OUTPUT_HWIDTH(x)                   (g_stMDomainOutputData.usHWidth = (x))
#define SET_MDOMAIN_OUTPUT_HBWIDTH(x)                  (g_stMDomainOutputData.usHBackWidth = (x))
#define SET_MDOMAIN_OUTPUT_HTOTAL(x)                   (g_stMDomainOutputData.usHTotal = (x))

#define SET_MDOMAIN_OUTPUT_VSTART(x)                   (g_stMDomainOutputData.usVStart = (x))
#define SET_MDOMAIN_OUTPUT_VBSTART(x)                  (g_stMDomainOutputData.usVBackStart = (x))
#define SET_MDOMAIN_OUTPUT_VHEIGHT(x)                  (g_stMDomainOutputData.usVHeight = (x))
#define SET_MDOMAIN_OUTPUT_VBHEIGHT(x)                 (g_stMDomainOutputData.usVBackHeight = (x))
#define SET_MDOMAIN_OUTPUT_VTOTAL(x)                   (g_stMDomainOutputData.usVTotal = (x))
#define SET_MDOMAIN_OUTPUT_VSYNCHEIGHT(x)              (g_stMDomainOutputData.usVSyncHeight = (x))

//--------------------------------------------------
// Macros of Input Info.
//--------------------------------------------------
#define GET_MEMORY_CONFIG_SELECT()                     (g_stMDomainInfo.enumMemoryConfig)

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define GET_D_CLK_FREQ()                               (g_ulMDomainDClkFreq)
#define GET_D_MAX_CLK_FREQ()                           (GET_D_CLK_FREQ() + GET_CLOCK_SPREAD(_PANEL_PIXEL_CLOCK_MAX_KHZ, _DCLK_SPREAD_RANGE_MAX))
#define GET_D_MIN_CLK_FREQ()                           (GET_D_CLK_FREQ() - GET_CLOCK_SPREAD(_PANEL_PIXEL_CLOCK_MIN_KHZ, _DCLK_SPREAD_RANGE_MAX))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Define Memory Frame Buffer
//--------------------------------------------------
typedef enum
{
    _MEMORY_1_FRAME_BUFFER = 0x00,
    _MEMORY_2_FRAME_BUFFER,
    _MEMORY_3_FRAME_BUFFER,
    _MEMORY_1_5_FRAME_BUFFER,
} EnumMemoryFrameBufferType;

//--------------------------------------------------
// Enumerations of Memory Config
//--------------------------------------------------
typedef enum
{
    _FRAME_SYNC_LINE_BUFFER = 0x00,
    _FRAME_SYNC_MEMORY,
    _FREE_RUN_MEMORY,
    _MN_FRAME_SYNC_MEMORY,
    _FREE_RUN_NO_INPUT,
} EnumMemoryConfig;

//--------------------------------------------------
// Enumerations of Memory Work
//--------------------------------------------------
typedef enum
{
    _LINE_BUFFER_MODE = 0x00,
    _MEMORY_WORK_MODE,
} EnumMemoryWorkMode;

//--------------------------------------------------
// Enumerations of DVF Select
//--------------------------------------------------
typedef enum
{
    _1_IVF = 0x00,
    _2_IVF,
    _3_IVF,
    _PANEL_TYP_FRAME_RATE_FREE_RUN,
    _2_5_IVF,
    _5_4_IVF,
    _6_5_IVF,
} EnumDVFSelect;

typedef enum
{
    _MTP_FREE_RUN = 0x00,
    _MAIN_DISPLAY_SETTING_SUB_NONE,
    _MAIN_DISPLAY_SETTING_SUB_READY,
    _SUB_DISPLAY_SETTING_MAIN_NONE,
    _SUB_DISPLAY_SETTING_MAIN_READY,
} EnumMtPMemorySelect;

typedef struct
{
    WORD usHStart;
    WORD usHWidth;
    WORD usVStart;
    WORD usVHeight;
}StructTimingFormat;

typedef struct
{
    EnumDDomainRegion enumDDomainRegion; // D-domain region
    BYTE ucExtensionLEn;
    WORD usHTotal;                // Horizontal Total length (unit: Pixel)
    WORD usHStart;                // Horizontal Start Position
    WORD usHWidth;                // Horizontal Active Width (unit: Pixel)
    WORD usHBackStart;            // Horizontal Back Ground Start Position
    WORD usHBackWidth;            // Horizontal Back Ground Active Width (unit: Pixel)

    WORD usVTotal;                // Vertical Total length (unit: HSync)
    WORD usVStart;                // Vertical Start Position
    WORD usVHeight;               // Vertical Active Height (unit: HSync)
    WORD usVBackStart;            // Vertical Back Ground Start Position
    WORD usVBackHeight;           // Vertical Back Ground Active Height (unit: HSync)
    WORD usVSyncHeight;           // Vertical Sync Height (unit: HSync)
}StructDisplayInfo;

typedef struct
{
    EnumMemoryConfig enumMemoryConfig;
    EnumMemoryWorkMode enumMemoryWorkMode;
    EnumDVFSelect enumDVFSelect;
    EnumMemoryFrameBufferType enumMemoryFrameBufferType;
    EnumInputPort enumInputPort;
    EnumSourceType enumSourceType;
    BYTE b3ColorSpace : 3;
    BYTE b1HSU : 1;
    BYTE b1HSD : 1;
    BYTE b1VSU : 1;
    BYTE b1VSD : 1;
    BYTE b1DisplaySettingDBEnable : 1;
    BYTE b1ForceDisplay1PMode : 1;
    BYTE b1FrameSyncMain : 1;
    BYTE b6DataBit : 6;
    EnumMtPMemorySelect enumMtPMemorySelect;

#if((_DRR_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    BYTE b1VgipVsyncBypassEn : 1;
    BYTE b1VgipVsyncBypassSetAfterIDB : 1;
#endif
} StructMDomainInfo;

typedef struct
{
    BYTE b1HSU : 1;
    BYTE b1HSD : 1;
    BYTE b1VSU : 1;
    BYTE b1VSD : 1;
} StructScalingStatus;


#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
//--------------------------------------------------
// Struc for Get IVF Max from EDID or user table
//--------------------------------------------------
typedef struct
{
    BYTE ucColorSapce;
    WORD usHtotal;
    WORD usHtotalMargin;
    WORD usNativePixelClk;
} StructTableSearchingSourceInfo;

typedef struct
{
    BYTE b1Interlace : 1;
    WORD usHwidth;
    WORD usVheight;
    WORD usHblank;
    WORD usPixelClk;
    WORD usHtotal;
    WORD usVtotal;
} StructEdidInfo;

typedef struct
{
    BYTE b1RefInterlace : 1;
    WORD usRefHwidth;
    WORD usRefVheight;
    WORD usRefHblankHBound;
    WORD usRefHblankLBound;
    WORD usPixelClkHBound;
    WORD usPixelClkLBound;
} StructEdidRefInfo;

//--------------------------------------------------
// Enum for Get IVF Max from EDID or user table
//--------------------------------------------------
typedef enum
{
    _TABLE_SEARCHING_WITH_IVF_MAX = 0x00,
    _TABLE_SEARCHING_WITHOUT_IVF_MAX,
} EnumGetIVFFromTableSearch;
#endif

//--------------------------------------------------
// Enumerations of Eagle Sight Support
//--------------------------------------------------
#if(_EAGLE_SIGHT_SUPPORT == _ON)
typedef enum
{
    _EAGLE_SIGHT_SUPPORT_OFF,
    _EAGLE_SIGHT_SUPPORT_ON,
} EnumEagleSightSupport;

//--------------------------------------------------
// Enumerations of Eagle Sight Support
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_MAIN_SUB_SYNC,
    _EAGLE_SIGHT_MAIN_SUB_ASYNC,
} EnumEagleSightMainSubSynchronous;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructMDomainInfo g_stMDomainInfo;
extern StructTimingInfo g_stMDomainInputData;
extern StructDisplayInfo g_stMDomainOutputData;

extern DWORD g_ulMDomainDClkFreq;
extern WORD g_usMDomainDVFreq;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


