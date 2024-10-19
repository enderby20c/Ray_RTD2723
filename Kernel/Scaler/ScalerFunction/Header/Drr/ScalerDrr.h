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
// ID Code      : ScalerDrr.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DRR_H__
#define __SCALER_DRR_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_VER_D0_BY_EDID()                       (g_stDrrFreesyncVerbyEdid.b3D0FreeSyncVerbyEdid)
#define SET_FREESYNC_VER_D0_BY_EDID(x)                      (g_stDrrFreesyncVerbyEdid.b3D0FreeSyncVerbyEdid = (x))

#define GET_FREESYNC_VER_D1_BY_EDID()                       (g_stDrrFreesyncVerbyEdid.b3D1FreeSyncVerbyEdid)
#define SET_FREESYNC_VER_D1_BY_EDID(x)                      (g_stDrrFreesyncVerbyEdid.b3D1FreeSyncVerbyEdid = (x))

#define GET_FREESYNC_VER_D2_BY_EDID()                       (g_stDrrFreesyncVerbyEdid.b3D2FreeSyncVerbyEdid)
#define SET_FREESYNC_VER_D2_BY_EDID(x)                      (g_stDrrFreesyncVerbyEdid.b3D2FreeSyncVerbyEdid = (x))

#define GET_FREESYNC_VER_D3_BY_EDID()                       (g_stDrrFreesyncVerbyEdid.b3D3FreeSyncVerbyEdid)
#define SET_FREESYNC_VER_D3_BY_EDID(x)                      (g_stDrrFreesyncVerbyEdid.b3D3FreeSyncVerbyEdid = (x))

#define GET_FREESYNC_VER_D4_BY_EDID()                       (g_stDrrFreesyncVerbyEdid.b3D4FreeSyncVerbyEdid)
#define SET_FREESYNC_VER_D4_BY_EDID(x)                      (g_stDrrFreesyncVerbyEdid.b3D4FreeSyncVerbyEdid = (x))

#define GET_FREESYNC_VER_D5_BY_EDID()                       (g_stDrrFreesyncVerbyEdid.b3D5FreeSyncVerbyEdid)
#define SET_FREESYNC_VER_D5_BY_EDID(x)                      (g_stDrrFreesyncVerbyEdid.b3D5FreeSyncVerbyEdid = (x))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define SET_FREESYNC_II_INFO_DATA(region, x)                (g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(region)] = (x))
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
typedef struct
{
    WORD usHwidth;
    WORD usVheight;
    WORD usHblank;
    WORD usPixelClk;
    WORD usHtotal;
    WORD usVtotal;
} StructDpFreeSyncEdidInfo;

typedef struct
{
    WORD usRefHwidth;
    WORD usRefVheight;
    WORD usRefHblankHBound;
    WORD usRefHblankLBound;
    WORD usPixelClkHBound;
    WORD usPixelClkLBound;
} StructDpFreeSyncEdidRefInfo;
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
#if(_DRR_SUPPORT == _ON)

#if(_FREESYNC_SUPPORT == _ON)

extern EnumDrrType ScalerDrrFreeSyncEnable(EnumInputPort enumInputPort);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerDrrFreeSyncDpSupportSwitch(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport);
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern void ScalerDrrFreeSyncHdmiSupportSwitch(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport, EnumInputPort enumFreesyncTargetPort);
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)

#endif
#endif

#if((_FREESYNC_II_SUPPORT == _ON) && (_ULTRA_HDR_SUPPORT == _ON))
extern bit ScalerDrrFreeSyncIICheckPortStatus(EnumInputPort enumInputPort);
#endif

#endif // End of #ifndef __SCALER_DRR_H__
