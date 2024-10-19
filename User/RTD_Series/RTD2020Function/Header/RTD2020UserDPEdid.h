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
// ID Code      : RTD2020UserDPEdid.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// EDID CONTENT TABLES
//****************************************************************************
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
BYTE code tEDID_TABLE_DP_8K4K_60_D0[] =
{
#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_7680x4320@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_D1[] =
{
#if(_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_7680x4320@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_60_D0[] =
{
#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_5120x2880@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_60_D1[] =
{
#if(_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_5120x2880@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_144_D0[] =
{
#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@144_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_3840x2160@144_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_144_D1[] =
{
#if(_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@144_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_3840x2160@144_M5.h>
#endif
};

#elif(_D8_INPUT_PORT_TYPE == _D8_DP_PORT)
BYTE code tEDID_TABLE_DP_8K4K_60_D1[] =
{
#if(_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_7680x4320@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_D2[] =
{
#if(_D8_D2_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_7680x4320@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_60_D1[] =
{
#if(_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_5120x2880@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_60_D2[] =
{
#if(_D8_D2_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@60_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_5120x2880@60_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_144_D1[] =
{
#if(_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@144_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_3840x2160@144_M5.h>
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_144_D2[] =
{
#if(_D8_D2_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@144_M5.h>
#else
#include <EDID/EdidDp/EDID_DP_BD2_3840x2160@144_M5.h>
#endif
};
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P_60[] =
{
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60.h>
};

BYTE code tEDID_TABLE_DP_2K1K_60[] =
{
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@60.h>
};

BYTE code tEDID_TABLE_DP_4K2K_60[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@60_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@60.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@240_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@240.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@144_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@144.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60.h>
#endif
};

// Temporility Use! It may define relatived Table In the Future
BYTE code tEDID_TABLE_DP_DEFAULT[] =
{
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60.h>
};
#endif

#if(_DP_HDR10_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P_60_HDR[] =
{
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60_HDR0.h>
};

BYTE code tEDID_TABLE_DP_2K1K_60_HDR[] =
{
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@60_HDR0.h>
};

BYTE code tEDID_TABLE_DP_4K2K_60_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@60_HDR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@60_HDR0.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@240_HDR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@240_HDR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@144_HDR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@144_HDR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_HDR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@60_HDR0.h>
#endif
};
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P_60_FS[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@50-75_HDR01_DRR0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@50-75_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_2K1K_60_FS[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@48-60_HDR01_DRR0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@48-60_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_60_FS[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@48-60_HDR01_DRR0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@48-60_DRR0_M0.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_DRR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_DRR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_DRR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_DRR0.h>
#endif
};
#endif
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P_60_FS_HDR[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@50-75_HDR01_DRR0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@50-75_HDR0_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_2K1K_60_FS_HDR[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@48-60_HDR01_DRR0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@48-60_HDR0_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_60_FS_HDR[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@48-60_HDR01_DRR0.h>
#else
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@48-60_HDR0_DRR0.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_HDR0_DRR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_HDR0_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_HDR0_DRR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_HDR0_DRR0.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_HDR0_DRR0_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_HDR0_DRR0.h>
#endif
};
#endif
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P_60_AS[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_1920x1080@50-75_DRR3.h>
};

BYTE code tEDID_TABLE_DP_2K1K_60_AS[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_2560x1440@48-60_DRR3.h>
};

BYTE code tEDID_TABLE_DP_4K2K_60_AS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_DRR3.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_AS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_DRR3.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_AS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_DRR3.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_AS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_DRR3.h>
#endif
};
#endif
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P_60_AS_HDR[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_1920x1080@50-75_HDR0_DRR3.h>
};

BYTE code tEDID_TABLE_DP_2K1K_60_AS_HDR[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_2560x1440@48-60_HDR0_DRR3.h>
};

BYTE code tEDID_TABLE_DP_4K2K_60_AS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_HDR0_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_HDR0_DRR3.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_AS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_HDR0_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_HDR0_DRR3.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_AS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_HDR0_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_HDR0_DRR3.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_AS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_HDR0_DRR3_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_HDR0_DRR3.h>
#endif
};
#endif
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P_60_AS_FS[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_1920x1080@50-75_DRR03.h>
};

BYTE code tEDID_TABLE_DP_2K1K_60_AS_FS[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_2560x1440@48-60_DRR03.h>
};

BYTE code tEDID_TABLE_DP_4K2K_60_AS_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_DRR03.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_AS_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_DRR03.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_AS_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_DRR03.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_AS_FS[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_DRR03.h>
#endif
};
#endif
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P_60_AS_FS_HDR[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_1920x1080@50-75_HDR0_DRR03.h>
};

BYTE code tEDID_TABLE_DP_2K1K_60_AS_FS_HDR[] =
{
#include <EDID/EdidDp/EDID_DP_BCD2_2560x1440@48-60_HDR0_DRR03.h>
};

BYTE code tEDID_TABLE_DP_4K2K_60_AS_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_HDR0_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@48-60_HDR0_DRR03.h>
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_4K2K_240_AS_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_HDR0_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@30-240_HDR0_DRR03.h>
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_144_AS_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_HDR0_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@30-144_HDR0_DRR03.h>
#endif
};

BYTE code tEDID_TABLE_DP_8K4K_60_AS_FS_HDR[] =
{
#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_HDR0_DRR03_M0.h>
#else
#include <EDID/EdidDp/EDID_DP_BCD2_7680x4320@48-60_HDR0_DRR03.h>
#endif
};
#endif
#endif

// Users Decide the Edid Content of the Edid Index
// Application of FHD, QHD, UHD
BYTE * code tDP_EDID_TABLE_BY_RESOL_0[] =
{
/*  Add other function rule
        HDR FS AS NEW
        0   0  0  0  => 0
        1   0  0  0  => 1
        0   1  0  0  => 2
        1   1  0  0  => 3
        0   0  1  0  => 4
        1   0  1  0  => 5
        0   1  1  0  => 6
        1   1  1  0  => 7
Add Here0   0  0  1  => 8
        1   0  0  1  => 9
        0   1  0  1  => 10
        1   1  0  1  => 11
        0   0  1  1  => 12
        1   0  1  1  => 13
        0   1  1  1  => 14
        1   1  1  1  => 15
*/
    tEDID_TABLE_DP_1080P_60,
    tEDID_TABLE_DP_2K1K_60,
    tEDID_TABLE_DP_4K2K_60,

#if(_DP_HDR10_SUPPORT == _ON)
    tEDID_TABLE_DP_1080P_60_HDR,
    tEDID_TABLE_DP_2K1K_60_HDR,
    tEDID_TABLE_DP_4K2K_60_HDR,
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    tEDID_TABLE_DP_1080P_60_FS,
    tEDID_TABLE_DP_2K1K_60_FS,
    tEDID_TABLE_DP_4K2K_60_FS,
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_1080P_60_FS_HDR,
    tEDID_TABLE_DP_2K1K_60_FS_HDR,
    tEDID_TABLE_DP_4K2K_60_FS_HDR,
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    tEDID_TABLE_DP_1080P_60_AS,
    tEDID_TABLE_DP_2K1K_60_AS,
    tEDID_TABLE_DP_4K2K_60_AS,
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_1080P_60_AS_HDR,
    tEDID_TABLE_DP_2K1K_60_AS_HDR,
    tEDID_TABLE_DP_4K2K_60_AS_HDR,
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
    tEDID_TABLE_DP_1080P_60_AS_FS,
    tEDID_TABLE_DP_2K1K_60_AS_FS,
    tEDID_TABLE_DP_4K2K_60_AS_FS,
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_1080P_60_AS_FS_HDR,
    tEDID_TABLE_DP_2K1K_60_AS_FS_HDR,
    tEDID_TABLE_DP_4K2K_60_AS_FS_HDR,
#endif
};

WORD code tDP_EDID_TABLE_SIZE_BY_RESOL_0[] =
{
    sizeof(tEDID_TABLE_DP_1080P_60),
    sizeof(tEDID_TABLE_DP_2K1K_60),
    sizeof(tEDID_TABLE_DP_4K2K_60),

#if(_DP_HDR10_SUPPORT == _ON)
    sizeof(tEDID_TABLE_DP_1080P_60_HDR),
    sizeof(tEDID_TABLE_DP_2K1K_60_HDR),
    sizeof(tEDID_TABLE_DP_4K2K_60_HDR),
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    sizeof(tEDID_TABLE_DP_1080P_60_FS),
    sizeof(tEDID_TABLE_DP_2K1K_60_FS),
    sizeof(tEDID_TABLE_DP_4K2K_60_FS),
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_1080P_60_FS_HDR),
    sizeof(tEDID_TABLE_DP_2K1K_60_FS_HDR),
    sizeof(tEDID_TABLE_DP_4K2K_60_FS_HDR),
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    sizeof(tEDID_TABLE_DP_1080P_60_AS),
    sizeof(tEDID_TABLE_DP_2K1K_60_AS),
    sizeof(tEDID_TABLE_DP_4K2K_60_AS),
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_1080P_60_AS_HDR),
    sizeof(tEDID_TABLE_DP_2K1K_60_AS_HDR),
    sizeof(tEDID_TABLE_DP_4K2K_60_AS_HDR),
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_1080P_60_AS_FS),
    sizeof(tEDID_TABLE_DP_2K1K_60_AS_FS),
    sizeof(tEDID_TABLE_DP_4K2K_60_AS_FS),
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_1080P_60_AS_FS_HDR),
    sizeof(tEDID_TABLE_DP_2K1K_60_AS_FS_HDR),
    sizeof(tEDID_TABLE_DP_4K2K_60_AS_FS_HDR),
#endif
};

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
// Users Decide the Edid Content of the Edid Index
// Application of 4K120, 4K144, 5K60
BYTE * code tDP_EDID_TABLE_BY_RESOL_1[] =
{
/*  Add other function rule
        HDR FS AS NEW
        0   0  0  0  => 0
        1   0  0  0  => 1
        0   1  0  0  => 2
        1   1  0  0  => 3
        0   0  1  0  => 4
        1   0  1  0  => 5
        0   1  1  0  => 6
        1   1  1  0  => 7
Add Here0   0  0  1  => 8
        1   0  0  1  => 9
        0   1  0  1  => 10
        1   1  0  1  => 11
        0   0  1  1  => 12
        1   0  1  1  => 13
        0   1  1  1  => 14
        1   1  1  1  => 15
*/
    tEDID_TABLE_DP_4K2K_240,
    tEDID_TABLE_DP_5K3K_144,
    tEDID_TABLE_DP_8K4K_60,

#if(_DP_HDR10_SUPPORT == _ON)
    tEDID_TABLE_DP_4K2K_240_HDR,
    tEDID_TABLE_DP_5K3K_144_HDR,
    tEDID_TABLE_DP_8K4K_60_HDR,
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    tEDID_TABLE_DP_4K2K_240_FS,
    tEDID_TABLE_DP_5K3K_144_FS,
    tEDID_TABLE_DP_8K4K_60_FS,
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_4K2K_240_FS_HDR,
    tEDID_TABLE_DP_5K3K_144_FS_HDR,
    tEDID_TABLE_DP_8K4K_60_FS_HDR,
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    tEDID_TABLE_DP_4K2K_240_AS,
    tEDID_TABLE_DP_5K3K_144_AS,
    tEDID_TABLE_DP_8K4K_60_AS,
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_4K2K_240_AS_HDR,
    tEDID_TABLE_DP_5K3K_144_AS_HDR,
    tEDID_TABLE_DP_8K4K_60_AS_HDR,
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
    tEDID_TABLE_DP_4K2K_240_AS_FS,
    tEDID_TABLE_DP_5K3K_144_AS_FS,
    tEDID_TABLE_DP_8K4K_60_AS_FS,
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_4K2K_240_AS_FS_HDR,
    tEDID_TABLE_DP_5K3K_144_AS_FS_HDR,
    tEDID_TABLE_DP_8K4K_60_AS_FS_HDR,
#endif
};

WORD code tDP_EDID_TABLE_SIZE_BY_RESOL_1[] =
{
    sizeof(tEDID_TABLE_DP_4K2K_240),
    sizeof(tEDID_TABLE_DP_5K3K_144),
    sizeof(tEDID_TABLE_DP_8K4K_60),

#if(_DP_HDR10_SUPPORT == _ON)
    sizeof(tEDID_TABLE_DP_4K2K_240_HDR),
    sizeof(tEDID_TABLE_DP_5K3K_144_HDR),
    sizeof(tEDID_TABLE_DP_8K4K_60_HDR),
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    sizeof(tEDID_TABLE_DP_4K2K_240_FS),
    sizeof(tEDID_TABLE_DP_5K3K_144_FS),
    sizeof(tEDID_TABLE_DP_8K4K_60_FS),
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_4K2K_240_FS_HDR),
    sizeof(tEDID_TABLE_DP_5K3K_144_FS_HDR),
    sizeof(tEDID_TABLE_DP_8K4K_60_FS_HDR),
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    sizeof(tEDID_TABLE_DP_4K2K_240_AS),
    sizeof(tEDID_TABLE_DP_5K3K_144_AS),
    sizeof(tEDID_TABLE_DP_8K4K_60_AS),
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_4K2K_240_AS_HDR),
    sizeof(tEDID_TABLE_DP_5K3K_144_AS_HDR),
    sizeof(tEDID_TABLE_DP_8K4K_60_AS_HDR),
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_4K2K_240_AS_FS),
    sizeof(tEDID_TABLE_DP_5K3K_144_AS_FS),
    sizeof(tEDID_TABLE_DP_8K4K_60_AS_FS),
#endif

#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    sizeof(tEDID_TABLE_DP_4K2K_240_AS_FS_HDR),
    sizeof(tEDID_TABLE_DP_5K3K_144_AS_FS_HDR),
    sizeof(tEDID_TABLE_DP_8K4K_60_AS_FS_HDR),
#endif
};
#endif

#endif // #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_DP_SUPPORT == _ON))

#endif // #if(_OSD_TYPE == _NONE_OSD)
