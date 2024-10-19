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
// ID Code      : MultiPanel_template.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel parameter in variable
//--------------------------------------------------
#ifndef _PANEL_MULTIPANEL_VARIABLE
#define _PANEL_MULTIPANEL_VARIABLE              _OFF
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   (GET_MDOMAIN_PANAL_INFO().ucLinkRage)
#define _PANEL_DPTX_LANE_NUMBER                 (GET_MDOMAIN_PANAL_INFO().ucLaneNumber)
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        (GET_MDOMAIN_PANAL_INFO().ucVenderType)
#define _PANEL_DPTX_PANEL_SECTION               (GET_MDOMAIN_PANAL_INFO().ucSectionNumber)
#endif

//--------------------------------------------------
// Macros of MDomain Panel Index/Info struct
//--------------------------------------------------
#define GET_MDOMAIN_PANEL_INDEX()               (g_ucDDomainPanelIndex)

#if(_PANEL_MULTIPANEL_VARIABLE == _ON)

#define SET_MDOMAIN_PANEL_INDEX(x)              {\
                                                    g_ucDDomainPanelIndex = ((x) % _PANEL_AMOUNT);\
                                                    g_stPanelData = tPanelData[g_ucDDomainPanelIndex];\
                                                }

#define GET_MDOMAIN_PANAL_INFO()                (g_stPanelData)

#else

#define SET_MDOMAIN_PANEL_INDEX(x)              {\
                                                    g_ucDDomainPanelIndex = ((x) % _PANEL_AMOUNT);\
                                                }

#define GET_MDOMAIN_PANAL_INFO()                (tPanelData[g_ucDDomainPanelIndex])

#endif

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
// Definitions of DRR
//--------------------------------------------------
#if(_DRR_SUPPORT == _ON)
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       (GET_MDOMAIN_PANAL_INFO().usDpFreesyncDVfreq_max)
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       (GET_MDOMAIN_PANAL_INFO().usDpFreesyncDVfreq_min)

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     (GET_MDOMAIN_PANAL_INFO().usHdmiFreesyncDVfreq_max)
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     (GET_MDOMAIN_PANAL_INFO().usHdmiFreesyncDVfreq_min)

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        (GET_MDOMAIN_PANAL_INFO().usHdmi21VrrDVfreq_max)
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        (GET_MDOMAIN_PANAL_INFO().usHdmi21VrrDVfreq_min)

#endif

//--------------------------------------------------
// Definitions of Panel data structure
//--------------------------------------------------
typedef struct
{
#if(_PANEL_STYLE == _PANEL_DPTX)
    BYTE ucLinkRage;
    BYTE ucLaneNumber;
    BYTE ucVenderType;
    BYTE ucSectionNumber;
#endif

    BYTE ucPixelType;

    WORD usLastLineMax;
    WORD usLastLineMin;
    BYTE ucManufacturer;
    BYTE ucColorBit;

    WORD usDVfreq;
    WORD usDVfreq_max;
    WORD usDVfreq_min;

#if(_DRR_SUPPORT == _ON)
    WORD usDpFreesyncDVfreq_max;
    WORD usDpFreesyncDVfreq_min;
    WORD usHdmiFreesyncDVfreq_max;
    WORD usHdmiFreesyncDVfreq_min;
    WORD usHdmi21VrrDVfreq_max;
    WORD usHdmi21VrrDVfreq_min;
#endif

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
// Panel Data Variable
//--------------------------------------------------
#if(_PANEL_MULTIPANEL_VARIABLE == _ON)
extern StructVariablePanel g_stPanelData;

#ifdef __SCALER_DDOMAIN__
StructVariablePanel g_stPanelData;
#endif

#endif

//--------------------------------------------------
// Panel Data Table
//--------------------------------------------------
#define _PANEL_AMOUNT                           (6)

extern StructVariablePanel code tPanelData[_PANEL_AMOUNT];

#ifdef __SCALER_DDOMAIN__
StructVariablePanel code tPanelData[] =
{
#include <RTDMultiPanelTable/tMultiPanel_1920x1080.h>
#include <RTDMultiPanelTable/tMultiPanel_2560x1080.h>
#include <RTDMultiPanelTable/tMultiPanel_2560x1440.h>
#include <RTDMultiPanelTable/tMultiPanel_3440x1440.h>
#include <RTDMultiPanelTable/tMultiPanel_3840x2160.h>
#include <RTDMultiPanelTable/tMultiPanel_5120x2880.h>
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

