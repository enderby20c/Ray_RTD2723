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
// ID Code      : RTD2020UserInterfaceFreeSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_FREESYNC__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceFreeSync.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Decide whether to Enable FREESYNC Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumFreeSyncSupport UserInterfaceFreeSyncGetEnable(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    if(UserCommonDisplayGetFrameSyncSupport() == _FRAME_SYNC_SUPPORT_ON)
    {
        return GET_OSD_FREE_SYNC_STATUS();
    }

    return _FREESYNC_SUPPORT_OFF;
}

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Panel Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceFreeSyncGetDpAupiPanelInfo(StructDrrAmdAupiInfo *pstDrrDpAmdAupiInfo)
{
    pstDrrDpAmdAupiInfo->ucPanelManufactureIdL = 0x00;
    pstDrrDpAmdAupiInfo->ucPanelManufactureIdM = 0x00;
    pstDrrDpAmdAupiInfo->ucPanelIdL = 0x00;
    pstDrrDpAmdAupiInfo->ucPanelIdM = 0x00;
    pstDrrDpAmdAupiInfo->ucFwCheckSumL = 0x00;
    pstDrrDpAmdAupiInfo->ucFwCheckSumM = 0x00;
}
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Hdmi Panel Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceFreeSyncGetHdmiAupiPanelInfo(StructDrrAmdAupiInfo *pstDrrHdmiAmdAupiInfo)
{
    pstDrrHdmiAmdAupiInfo->ucPanelManufactureIdL = 0x00;
    pstDrrHdmiAmdAupiInfo->ucPanelManufactureIdM = 0x00;
    pstDrrHdmiAmdAupiInfo->ucPanelIdL = 0x00;
    pstDrrHdmiAmdAupiInfo->ucPanelIdM = 0x00;
    pstDrrHdmiAmdAupiInfo->ucFwCheckSumL = 0x00;
    pstDrrHdmiAmdAupiInfo->ucFwCheckSumM = 0x00;
    pstDrrHdmiAmdAupiInfo->ucScalerDeviceIdL = 0x00;
    pstDrrHdmiAmdAupiInfo->ucScalerDeviceIdM = 0x00;
}

//--------------------------------------------------
// Description  : Get the MCCS Addr by user
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE UserInterfaceFreeSyncGetHdmiMccsAddress(void)
{
    return _HDMI_FREESYNC_MCCS_VCP;
}
#endif

#endif // #if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT))

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

