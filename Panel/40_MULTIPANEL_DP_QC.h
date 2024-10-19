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

#if(_PANEL_TYPE == _MULTIPANEL_DP_QC)
//----------------------------------------------------------------------------------------------------
// ID Code      : _MULTIPANEL_DP_QC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _ON


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   (GET_MDOMAIN_PANAL_INFO().ucLinkRage)
#define _PANEL_DPTX_LANE_NUMBER                 (GET_MDOMAIN_PANAL_INFO().ucLaneNumber)
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        (GET_MDOMAIN_PANAL_INFO().ucVenderType)
#define _PANEL_DPTX_PANEL_SECTION               (GET_MDOMAIN_PANAL_INFO().ucSectionNumber)

//--------------------------------------------------
// Macros of MDomain Panel Index/Info struct
//--------------------------------------------------
#define GET_MDOMAIN_PANEL_INDEX()               (g_ucDDomainPanelIndex)
#define SET_MDOMAIN_PANEL_INDEX(x)              {\
                                                    g_ucDDomainPanelIndex = ((x) % _PANEL_AMOUNT);\
                                                }

#define GET_MDOMAIN_PANAL_INFO()                (tPanelData[g_ucDDomainPanelIndex])

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     (GET_MDOMAIN_PANAL_INFO().ucManufacturer)

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    (GET_MDOMAIN_PANAL_INFO().ucColorBit)


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
// Panel Pixel Type
#define _PANEL_PIXEL_TYPE                       (GET_MDOMAIN_PANAL_INFO().ucPixelType)

// Panel Frame Rate (Unit: 0.1 Hz)
#define _PANEL_TYP_FRAME_RATE                   (GET_MDOMAIN_PANAL_INFO().usDVfreq)
#define _PANEL_MAX_FRAME_RATE                   (GET_MDOMAIN_PANAL_INFO().usDVfreq_max)
#define _PANEL_MIN_FRAME_RATE                   (GET_MDOMAIN_PANAL_INFO().usDVfreq_min)

// Panel H/V resolution
#define _PANEL_DH_START                         (GET_MDOMAIN_PANAL_INFO().usDHstart)
#define _PANEL_DH_WIDTH                         (GET_MDOMAIN_PANAL_INFO().usDHwidth)
#define _PANEL_DH_END                           (_PANEL_DH_START + _PANEL_DH_WIDTH)
#define _PANEL_DH_SYNC_WIDTH                    (GET_MDOMAIN_PANAL_INFO().usDHSwidth)
#define _PANEL_DH_TOTAL                         (GET_MDOMAIN_PANAL_INFO().usDHtotal)
#define _PANEL_DH_TOTAL_MAX                     (GET_MDOMAIN_PANAL_INFO().usDHtotal_max)
#define _PANEL_DH_TOTAL_MIN                     (GET_MDOMAIN_PANAL_INFO().usDHtotal_min)

#define _PANEL_DV_START                         (GET_MDOMAIN_PANAL_INFO().usDVstart)
#define _PANEL_DV_HEIGHT                        (GET_MDOMAIN_PANAL_INFO().usDVheight)
#define _PANEL_DV_END                           (_PANEL_DV_START + _PANEL_DV_HEIGHT)
#define _PANEL_DV_SYNC_HEIGHT                   (GET_MDOMAIN_PANAL_INFO().usDVSwidth)
#define _PANEL_DV_TOTAL                         (GET_MDOMAIN_PANAL_INFO().usDVtotal)
#define _PANEL_DV_TOTAL_MAX                     (GET_MDOMAIN_PANAL_INFO().usDVtotal_max)
#define _PANEL_DV_TOTAL_MIN                     (GET_MDOMAIN_PANAL_INFO().usDVtotal_min)

// Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK                      (GET_MDOMAIN_PANAL_INFO().usPixelClock)
#define _PANEL_PIXEL_CLOCK_MAX                  (GET_MDOMAIN_PANAL_INFO().usPixelClock_max)
#define _PANEL_PIXEL_CLOCK_MIN                  (GET_MDOMAIN_PANAL_INFO().usPixelClock_min)

// Panel Power On T1 ~ T6 (ms)
#define _PANEL_POWER_ON_T1                      (GET_MDOMAIN_PANAL_INFO().usT1)
#define _PANEL_POWER_ON_T2                      (GET_MDOMAIN_PANAL_INFO().usT2)
#define _PANEL_POWER_ON_T3                      (GET_MDOMAIN_PANAL_INFO().usT3)
#define _PANEL_POWER_OFF_T4                     (GET_MDOMAIN_PANAL_INFO().usT4)
#define _PANEL_POWER_OFF_T5                     (GET_MDOMAIN_PANAL_INFO().usT5)
#define _PANEL_POWER_OFF_T6                     (GET_MDOMAIN_PANAL_INFO().usT6)

//--------------------------------------------------
// Definitions of Panel data structure
//--------------------------------------------------
typedef struct
{
    BYTE ucLinkRage;
    BYTE ucLaneNumber;
    BYTE ucVenderType;
    BYTE ucSectionNumber;

    BYTE ucPixelType;

    WORD usLastLineMax;
    WORD usLastLineMin;
    BYTE ucManufacturer;
    BYTE ucColorBit;

    WORD usDVfreq;
    WORD usDVfreq_max;
    WORD usDVfreq_min;

    WORD usDHstart;
    WORD usDHwidth;

    WORD usDHtotal;
    WORD usDHtotal_max;
    WORD usDHtotal_min;

    WORD usDVstart;
    WORD usDVheight;

    WORD usDVtotal;
    WORD usDVtotal_max;
    WORD usDVtotal_min;

    WORD usDHSwidth;
    WORD usDVSwidth;

    WORD usPixelClock;
    WORD usPixelClock_max;
    WORD usPixelClock_min;

    WORD usT1;
    WORD usT2;
    WORD usT3;
    WORD usT4;
    WORD usT5;
    WORD usT6;
} StructVariablePanel;

//--------------------------------------------------
// Panel Data Table
//--------------------------------------------------
#define _PANEL_AMOUNT                           (2)

extern StructVariablePanel code tPanelData[_PANEL_AMOUNT];

#ifdef __SCALER_DDOMAIN__
StructVariablePanel code tPanelData[] =
{
    // 5120x2880
    {
        _PANEL_DPTX_LINK_HBR2, // _PANEL_DPTX_LINK_RATE
        _PANEL_DPTX_LANE_NUMBER_8, // _PANEL_DPTX_LANE_NUMBER
        _PANEL_DPTX_VENDOR_SPECIFIC_004F1H, // _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
        _DPTX_PANEL_2_SECTION, // _PANEL_DPTX_PANEL_SECTION
        _PANEL_PIXEL_LCD, // _PANEL_PIXEL_TYPE
        5200,        // _LAST_LINE_MAX
        5000,        // _LAST_LINE_MIN
        _PANEL_LGD, // _PANEL_MANUFACTURER
        _PANEL_DISP_30_BIT,

        600,        // _PANEL_TYP_FRAME_RATE
        610,        // _PANEL_MAX_FRAME_RATE
        590,        // _PANEL_MIN_FRAME_RATE

        80,         // _PANEL_DH_START
        5120,       // _PANEL_DH_WIDTH

        5400,       // _PANEL_DH_TOTAL
        5448,       // _PANEL_DH_TOTAL_MAX
        5200,       // _PANEL_DH_TOTAL_MIN

        6,          // _PANEL_DV_START
        2880,       // _PANEL_DV_HEIGHT

        2962,       // _PANEL_DV_TOTAL
        3002,       // _PANEL_DV_TOTAL_MAX
        2922,       // _PANEL_DV_TOTAL_MIN

        8,          // _PANEL_DH_SYNC_WIDTH
        2,          // _PANEL_DV_SYNC_HEIGHT

        959,        // _PANEL_PIXEL_CLOCK
        998,        // _PANEL_PIXEL_CLOCK_MAX
        878,        // _PANEL_PIXEL_CLOCK_MIN

        0,        // _PANEL_POWER_ON_T1
        0,         // _PANEL_POWER_ON_T2
        0,        // _PANEL_POWER_ON_T3

        0,         // _PANEL_POWER_OFF_T4
        0,         // _PANEL_POWER_OFF_T5
        0,        // _PANEL_POWER_OFF_T6
    },
    // 7680x4320
    {
        _PANEL_DPTX_LINK_HBR3_9G, // _PANEL_DPTX_LINK_RATE
        _PANEL_DPTX_LANE_NUMBER_8, // _PANEL_DPTX_LANE_NUMBER
        _PANEL_DPTX_VENDOR_SPECIFIC_004F1H, // _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
        _DPTX_PANEL_2_SECTION, // _PANEL_DPTX_PANEL_SECTION
        _PANEL_PIXEL_LCD, // _PANEL_PIXEL_TYPE
        8404,        // _LAST_LINE_MAX
        8304,        // _LAST_LINE_MIN
        _PANEL_AUO, // _PANEL_MANUFACTURER
        _PANEL_DISP_24_BIT,

        600,        // _PANEL_TYP_FRAME_RATE
        610,        // _PANEL_MAX_FRAME_RATE
        590,        // _PANEL_MIN_FRAME_RATE

        160,         // _PANEL_DH_START
        7680,       // _PANEL_DH_WIDTH

        8704,       // _PANEL_DH_TOTAL
        8704,       // _PANEL_DH_TOTAL_MAX
        8448,       // _PANEL_DH_TOTAL_MIN

        10,          // _PANEL_DV_START
        4320,       // _PANEL_DV_HEIGHT

        4380,       // _PANEL_DV_TOTAL
        4443,       // _PANEL_DV_TOTAL_MAX
        4352,       // _PANEL_DV_TOTAL_MIN

        80,          // _PANEL_DH_SYNC_WIDTH
        2,          // _PANEL_DV_SYNC_HEIGHT

        2272,        // _PANEL_PIXEL_CLOCK
        2360,        // _PANEL_PIXEL_CLOCK_MAX
        1966,        // _PANEL_PIXEL_CLOCK_MIN

        0,        // _PANEL_POWER_ON_T1
        0,         // _PANEL_POWER_ON_T2
        0,        // _PANEL_POWER_ON_T3

        0,         // _PANEL_POWER_OFF_T4
        0,         // _PANEL_POWER_OFF_T5
        0,        // _PANEL_POWER_OFF_T6
    },
};

#endif


/////////////
// Display //
/////////////

//--------------------------------------------------
// Set Last Line Max and Min
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    (GET_MDOMAIN_PANAL_INFO().usLastLineMax)
#define _PANEL_LAST_LINE_MIN                    (GET_MDOMAIN_PANAL_INFO().usLastLineMin)

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ



/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                20


////////////////////
// VGA Auto Color //
////////////////////



///////////////////////////
// Color Characteristics //
///////////////////////////



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _MULTIPANEL_DP_21_5_WUXGA))
