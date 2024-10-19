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
// ID Code      : UserCommonSource.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_SOURCE__

#include "UserCommonInclude.h"
#include "Source/UserCommonSource.h"

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
// Description  : User Common Source Get Auto SearchTarget
// Input Value  : None
// Output Value : display region
//--------------------------------------------------
EnumDisplayRegion UserCommonSourceGetAutoSearchTarget(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        return UserCommonQCSourceGetAutoSearchTarget();
    }
#endif

    return UserInterfaceSourceGetAutoSearchTarget();
}

//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonSourceGetInputPort0(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        return UserCommonQCSourceGetInputPort0();
    }
#endif

    return UserInterfaceSourceGetInputPort0();
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonSourceGetInputPort1(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        return UserCommonQCSourceGetInputPort1();
    }
#endif

    return UserInterfaceSourceGetInputPort1();
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonSourceGetInputPort2(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        return UserCommonQCSourceGetInputPort2();
    }
#endif

    return UserInterfaceSourceGetInputPort2();
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonSourceGetInputPort3(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        return UserCommonQCSourceGetInputPort3();
    }
#endif

    return UserInterfaceSourceGetInputPort3();
}
#endif

//--------------------------------------------------
// Description  : Let Upper Layer Get I-domain Pixel Clk
// Input Value  : enumInputPort --> target port
// Output Value : Input Pixel Clk (in 0.1MHz)
//--------------------------------------------------
WORD UserCommonSourceGetInputPixelClk(EnumInputPort enumInputPort)
{
    return ScalerSyncGetNativeInputPixelClk(enumInputPort);
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : Input Port
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
EnumHDCPType UserCommonSourceHdcpCheckEnabled(EnumInputPort enumInputPort)
{
#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
    if((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) || (SysPowerGetPowerStatus() == _POWER_STATUS_SAVING))
    {
        return ScalerSyncHdcpCheckEnabledUnderPowerOff(enumInputPort);
    }
#endif
    {
        return ScalerSyncHdcpCheckEnabled(enumInputPort);
    }
}
#endif


