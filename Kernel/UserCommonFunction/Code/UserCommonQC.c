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
// ID Code      : UserCommonQC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "QC/UserCommonQC.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
#warning "NOTE: _FACTORY_RTD_QC_SUPPORT is _ON!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : QC Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonQCHandler(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);

    // Initialize external debug board GPIO
    EXT_DEBUG_BOARD_GPIO_INITIAL();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        EnumDisplayRegion enumCurrentRegion = SysRegionGetDisplayRegion(ucRegionIndex);

        // Disable watch dog
        ScalerRegionSetWatchDog(enumCurrentRegion, _DISABLE);

#if(_COLOR_IP_COLOR_CONVERT == _ON)
        // Disable Color Space Conversion
        ScalerColorSpaceConvertIDomainEnable(enumCurrentRegion, _OFF);
        ScalerColorSpaceConvertDDomainEnable(enumCurrentRegion, _OFF);
#endif
    }

    // Disable Double buffer
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);

    // Execute QC flow
    if((ScalerQCHandler() == 0x00) &&
       (ScalerQCUpdateConfig() == _TRUE))
    {
#if(_PANEL_EXIST_MULTIPANEL == _ON)
        // Update panel index
        SET_MDOMAIN_PANEL_INDEX(ScalerQCGetMultiPanelIndex());
#endif

        // Reset to display Initial
        UserCommonDisplayModeAdjust((EnumDisplayMode)ScalerQCGetDisplayMode());
    }
    else
    {
        // Stop QC
        while(_TRUE)
        {
            ScalerDebug();
        }
    }
}

//--------------------------------------------------
// Description  : Return QC flow is running or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE UserCommonQCGetEnableStatus(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Return QC flow is ready to go or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonQCGetStartCondition(void)
{
    if(UserCommonQCGetEnableStatus() != _TRUE)
    {
        return _FALSE;
    }

    // Ready when display states are all in active state
    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_ACTIVE) == _TRUE)
    {
        return _TRUE;
    }

    // Chcek QC error status
    if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) != 0) ||
       (SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) != 0))
    {
        if(ScalerQCErrorHandler() == _TRUE)
        {
            // Stop QC
            while(_TRUE)
            {
                ScalerDebug();
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get System Data Info in QC mode
// Input Value  : enumDataType --> Data Type in StructSystemData
//                ucRawValue --> original NVRAM data
// Output Value : N/A
//--------------------------------------------------
BYTE UserCommonQCNVRamGetData(EnumSystemDataItemDataType enumDataType, BYTE ucRawValue)
{
    BYTE ucValue = ucRawValue;

    switch(enumDataType)
    {
        case _MONITOR_POWER_STATUS:
            ucValue = _ON;
            break;

        case _DISPLAY_MODE:
            ucValue = ScalerQCGetDisplayMode();
            break;

        case _SEARCH_PORT_0:
        case _SEARCH_PORT_1:
        case _SEARCH_PORT_2:
        case _SEARCH_PORT_3:
            ucValue = ScalerQCGetInputPort();
            break;

        case _AUTO_SEARCH_TARGET:
            ucValue = _REGION_INDEX_0;
            break;

        case _SOURCE_SCAN_TYPE:
            ucValue = _SOURCE_SWITCH_FIXED_PORT;
            break;

        default:
            break;
    }

    return ucValue;
}

//--------------------------------------------------
// Description  : User Common Source Get Auto SearchTarget
// Input Value  : None
// Output Value : display region
//--------------------------------------------------
EnumDisplayRegion UserCommonQCSourceGetAutoSearchTarget(void)
{
    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : Input Port
// Output Value : DP_VERSION_1_1 or DP_VERSION_1_2 or DP_VERSION_1_4
//--------------------------------------------------
EnumDpVersionType UserCommonQCDpGetVersion(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

#if(_D0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_2_0;
#elif(_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_1_4;
#elif(_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)
            return _DP_VERSION_1_2;
#else
            return _DP_VERSION_1_1;
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

#if(_D1_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_2_0;
#elif(_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_1_4;
#elif(_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)
            return _DP_VERSION_1_2;
#else
            return _DP_VERSION_1_1;
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

#if(_D2_DP_LINK_CLK_RATE > _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_2_0;
#elif(_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_1_4;
#elif(_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)
            return _DP_VERSION_1_2;
#else
            return _DP_VERSION_1_1;
#endif
#endif

        default:

            return _DP_VERSION_1_2;
    }
}

//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonQCSourceGetInputPort0(void)
{
    return (EnumInputPort)ScalerQCGetInputPort();
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonQCSourceGetInputPort1(void)
{
    return (EnumInputPort)ScalerQCGetInputPort();
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonQCSourceGetInputPort2(void)
{
    return (EnumInputPort)ScalerQCGetInputPort();
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : User Common Source Get Source Input Port
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonQCSourceGetInputPort3(void)
{
    return (EnumInputPort)ScalerQCGetInputPort();
}
#endif

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

