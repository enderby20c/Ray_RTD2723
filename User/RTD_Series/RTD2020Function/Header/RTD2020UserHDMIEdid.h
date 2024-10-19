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
// ID Code      : RTD2020UserHDMIEdid.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//****************************************************************************
// EDID LOCATION TABLES
//****************************************************************************
#include _HDMI_MULTI_EDID_TABLE
#endif

//****************************************************************************
// EDID CONTENT TABLES (by Osd User)
//****************************************************************************
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_HDMI_SUPPORT == _ON))
BYTE code tHDMI_EDID_FHD_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@60.h>
};

BYTE code tHDMI_EDID_QHD_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60.h>
};

BYTE code tHDMI_EDID_UHD_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0.h>
};

//--------------------------------------------------
// EDID Table for HDMI External Switch Port
//--------------------------------------------------
#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
BYTE code tHDMI_D3_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M012.h>
};

BYTE code tHDMI_D12_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M012.h>
};

BYTE code tHDMI_D13_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M012.h>
};
#endif

#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
BYTE code tHDMI_D4_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M012.h>
};

BYTE code tHDMI_D14_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M012.h>
};

BYTE code tHDMI_D15_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M012.h>
};
#endif

//****************************************************************************
// EDID CONTENT TABLES (by Osd User w/ HDMI Multi-Edid Switch Support)
//****************************************************************************
BYTE code tHDMI14_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60.h>
};

BYTE code tHDMI20_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0.h>
};

BYTE code tHDMI21_EDID_TABLE[] =
{
#if(_HDMI_SQE_TEST_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_7680x4320@60_M12.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M01.h>
#endif
};

BYTE code tEDID_TABLE_HDMI_DEFAULT[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@60.h>
};

#if(_HDMI_HDR10_SUPPORT == _ON)
BYTE code tHDMI14_HDR_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60_HDR0.h>
};

BYTE code tHDMI20_HDR_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0_HDR0.h>
};

BYTE code tHDMI21_HDR_EDID_TABLE[] =
{
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@60_M01_HDR0.h>
};
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE code tHDMI14_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@40-70_HDR01_DRR0.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@40-70_DRR0.h>
#endif
};

BYTE code tHDMI20_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@40-60_M0_HDR01_DRR0.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@40-60_M0_DRR0.h>
#endif
};

BYTE code tHDMI21_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@40-70_M01_HDR01_DRR0.h>
#else
#if(_HDMI_SQE_TEST_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_7680x4320@60_M12_DRR0.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@40-70_M01_DRR0.h>
#endif
#endif
};
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
BYTE code tHDMI14_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@40-70_HDR01_DRR0.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@40-70_DRR0.h>
#endif
};

BYTE code tHDMI20_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@40-60_M0_HDR01_DRR0.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@40-60_M0_DRR0.h>
#endif
};

BYTE code tHDMI21_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@40-70_M01_HDR01_DRR0.h>
#else
#include <EDID/EdidHdmi/EDID_HDMI_BCD1_5120x2880@40-70_M01_HDR0_DRR0.h>
#endif
};
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
// Users Decide the Edid Content of the Edid Index
BYTE * code tHDMI_EDID_TABLE[] =
{
    tHDMI14_EDID_TABLE,               // _EDID_INDEX_0
    tHDMI20_EDID_TABLE,               // _EDID_INDEX_1
    tHDMI21_EDID_TABLE,               // _EDID_INDEX_2

#if(_HDMI_HDR10_SUPPORT == _ON)
    tHDMI14_HDR_EDID_TABLE,           // _EDID_INDEX_3
    tHDMI20_HDR_EDID_TABLE,           // _EDID_INDEX_4
    tHDMI21_HDR_EDID_TABLE,           // _EDID_INDEX_5
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    tHDMI14_FS_EDID_TABLE,            // _EDID_INDEX_6
    tHDMI20_FS_EDID_TABLE,            // _EDID_INDEX_7
    tHDMI21_FS_EDID_TABLE,            // _EDID_INDEX_8
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    tHDMI14_FS_HDR_EDID_TABLE,        // _EDID_INDEX_9
    tHDMI20_FS_HDR_EDID_TABLE,        // _EDID_INDEX_10
    tHDMI21_FS_HDR_EDID_TABLE,        // _EDID_INDEX_11
#endif
};

WORD code tHDMI_EDID_TABLE_SIZE[] =
{
    sizeof(tHDMI14_EDID_TABLE),               // _EDID_INDEX_0
    sizeof(tHDMI20_EDID_TABLE),               // _EDID_INDEX_1
    sizeof(tHDMI21_EDID_TABLE),               // _EDID_INDEX_2

#if(_HDMI_HDR10_SUPPORT == _ON)
    sizeof(tHDMI14_HDR_EDID_TABLE),           // _EDID_INDEX_3
    sizeof(tHDMI20_HDR_EDID_TABLE),           // _EDID_INDEX_4
    sizeof(tHDMI21_HDR_EDID_TABLE),           // _EDID_INDEX_5
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    sizeof(tHDMI14_FS_EDID_TABLE),            // _EDID_INDEX_6
    sizeof(tHDMI20_FS_EDID_TABLE),            // _EDID_INDEX_7
    sizeof(tHDMI21_FS_EDID_TABLE),            // _EDID_INDEX_8
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    sizeof(tHDMI14_FS_HDR_EDID_TABLE),        // _EDID_INDEX_9
    sizeof(tHDMI20_FS_HDR_EDID_TABLE),        // _EDID_INDEX_10
    sizeof(tHDMI21_FS_HDR_EDID_TABLE),        // _EDID_INDEX_11
#endif
};
#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE)
// Users define of External EEPROM EDID
BYTE * code tHDMI_EXT_EEPROM_EDID_TABLE[] =
{
    tHDMI14_EDID_TABLE,               // _EDID_INDEX_0 (1ST Order of HDMI EEPROM, IF Project have 1 or more EXT EDID)
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    tHDMI20_EDID_TABLE,               // _EDID_INDEX_1 (2ND Order of HDMI EEPROM, IF Project have 2 or more EXT EDID)
    tHDMI21_EDID_TABLE,               // _EDID_INDEX_2 (3RD Order of HDMI EEPROM, IF Project have 3 or more EXT EDID)
#endif
};
#endif
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_HDMI_SUPPORT == _ON))

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
