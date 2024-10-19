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
// ID Code      : RTD2020UserInterfaceDisplay.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define _RTK_ADV_MBR_MIN_ENABLE_IVF             600
#endif
#endif

#if(_DRR_SUPPORT == _ON)
#define _USER_DRR_CLK_MARGIN                    (1)
#define _USER_DRR_HTOTAL_MARGIN                 (2)

#if(_FREESYNC_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_FREESYNC_IHWIDTH(x)              (tDrrFreeSyncDpTimingInfo[(x)].usIHwidth)
#define GET_DP_FREESYNC_IVHEIGHT(x)             (tDrrFreeSyncDpTimingInfo[(x)].usIVheight)
#define GET_DP_FREESYNC_IHTOTAL(x)              (tDrrFreeSyncDpTimingInfo[(x)].usIHtotal)
#define GET_DP_FREESYNC_ICLK(x)                 (tDrrFreeSyncDpTimingInfo[(x)].usPixelClk)
#define GET_DP_FREESYNC_IVFREQ(x)               (tDrrFreeSyncDpTimingInfo[(x)].usIVfreq)
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#define GET_HDMI_FREESYNC_IHWIDTH(x)            (tDrrFreeSyncHdmiTimingInfo[(x)].usIHwidth)
#define GET_HDMI_FREESYNC_IVHEIGHT(x)           (tDrrFreeSyncHdmiTimingInfo[(x)].usIVheight)
#define GET_HDMI_FREESYNC_IHTOTAL(x)            (tDrrFreeSyncHdmiTimingInfo[(x)].usIHtotal)
#define GET_HDMI_FREESYNC_ICLK(x)               (tDrrFreeSyncHdmiTimingInfo[(x)].usPixelClk)
#define GET_HDMI_FREESYNC_IVFREQ(x)             (tDrrFreeSyncHdmiTimingInfo[(x)].usIVfreq)
#endif
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
#define GET_HDMI_VRR_IHWIDTH(x)                 (tDrrVrrHdmiTimingInfo[(x)].usIHwidth)
#define GET_HDMI_VRR_IVHEIGHT(x)                (tDrrVrrHdmiTimingInfo[(x)].usIVheight)
#define GET_HDMI_VRR_IHTOTAL(x)                 (tDrrVrrHdmiTimingInfo[(x)].usIHtotal)
#define GET_HDMI_VRR_ICLK(x)                    (tDrrVrrHdmiTimingInfo[(x)].usPixelClk)
#define GET_HDMI_VRR_IVFREQ(x)                  (tDrrVrrHdmiTimingInfo[(x)].usIVfreq)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
