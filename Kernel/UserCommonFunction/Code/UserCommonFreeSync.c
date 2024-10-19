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
// ID Code      : UserCommonFreeSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FREESYNC__

#include "UserCommonInclude.h"
#include "FreeSync/UserCommonFreeSync.h"

#if(_FREESYNC_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : FreeSync Support Switch
// Input Value  : Check Status
// Output Value : None
//--------------------------------------------------
void UserCommonFreeSyncSupportSwitch(void)
{
#if(((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON)) ||\
    ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON)))
    ScalerDrrFreeSyncSupportSwitch(_D0_INPUT_PORT, UserInterfaceFreeSyncGetEnable(_D0_INPUT_PORT), SysSourceGetFreesyncInputPort());
#endif

#if(((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON)))
    ScalerDrrFreeSyncSupportSwitch(_D1_INPUT_PORT, UserInterfaceFreeSyncGetEnable(_D1_INPUT_PORT), SysSourceGetFreesyncInputPort());
#endif

#if(((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON)))
    ScalerDrrFreeSyncSupportSwitch(_D2_INPUT_PORT, UserInterfaceFreeSyncGetEnable(_D2_INPUT_PORT), SysSourceGetFreesyncInputPort());
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    ScalerDrrFreeSyncSupportSwitch(_D3_INPUT_PORT, UserInterfaceFreeSyncGetEnable(_D3_INPUT_PORT), SysSourceGetFreesyncInputPort());
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    ScalerDrrFreeSyncSupportSwitch(_D4_INPUT_PORT, UserInterfaceFreeSyncGetEnable(_D4_INPUT_PORT), SysSourceGetFreesyncInputPort());
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    ScalerDrrFreeSyncSupportSwitch(_D5_INPUT_PORT, UserInterfaceFreeSyncGetEnable(_D5_INPUT_PORT), SysSourceGetFreesyncInputPort());
#endif
}

//--------------------------------------------------
// Description  : Get AMD SPD info
// Input Value  : enumContent -> enumInputPort -> Port Type, AMD Info Type
// Output Value : None
//--------------------------------------------------
DWORD UserCommonFreeSyncGetInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent)
{
    return ScalerDrrFreeSyncGetInfo(enumInputPort, enumContent);
}

//--------------------------------------------------
// Description  : Set FreeSync Support By Port
// Input Value  : enumInputPort, enumSupport
// Output Value : None
//--------------------------------------------------
void UserCommonFreeSyncSetInputPortSupport(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport)
{
    ScalerDrrFreeSyncSupportSwitch(enumInputPort, enumSupport, SysSourceGetFreesyncInputPort());
}
#endif // #if(_FREESYNC_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Background to Gray Level
//                Specified by OD Calibration Tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFreeSyncODSetBackgroundGrayLevel(void)
{
    ScalerDDomainFreeSyncODSetBackgroundGrayLevel();
}

//--------------------------------------------------
// Description  : Set Display Format for FREESYNC OD measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void UserCommonFreeSyncODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq)
{
    ScalerMDomainFreeSyncODSetDisplayFormat(usDHtotal, ulDclk, usTarFreq);
}
#endif



