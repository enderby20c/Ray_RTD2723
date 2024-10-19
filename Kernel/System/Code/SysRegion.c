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
// ID Code      : SysRegion.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_REGION__

#include "SysInclude.h"
#include "Region/SysRegion.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructRegionInfoType g_pstRegionInfo[_MULTI_DISPLAY_MAX];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Initial region related variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysRegionInitial(void)
{
    BYTE ucRegionIndex = 0;

#if(_DOLBY_CERTIFICATION_SUPPORT == _ON)
    SysModeSetDisplayMode(_DISPLAY_MODE_1P);
#else
    // Load display mode
    SysModeSetDisplayMode(UserCommonNVRamGetSystemData(_DISPLAY_MODE));
#endif

    // Load region port index
    for(ucRegionIndex = 0; ucRegionIndex < _MULTI_DISPLAY_MAX; ++ucRegionIndex)
    {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        // if InputPort is D4/D14/D15 port, need to set extern switch and SET_RGN_SOURCE_INDEX = D4 port
        if(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _D4_INPUT_PORT)
        {
            PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);

            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D4_INPUT_PORT));
        }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        else if(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _D15_INPUT_PORT)
        {
            PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);

            // If InputPort is D14 or D15, need to change SearchIndex to D4
            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D4_INPUT_PORT));
        }
#endif
        else if(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _D14_INPUT_PORT)
        {
            PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);

            // If InputPort is D14 or D15, need to change SearchIndex to D4
            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D4_INPUT_PORT));
        }

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

        // if InputPort is D3/D12/D13 port, need to set extern switch and SET_RGN_SOURCE_INDEX = D3 port
        if(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _D3_INPUT_PORT)
        {
            PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);

            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D3_INPUT_PORT));
        }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        else if(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _D13_INPUT_PORT)
        {
            PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);

            // If InputPort is D12 or D13, need to change SearchIndex to D3
            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D3_INPUT_PORT));
        }
#endif
        else if(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _D12_INPUT_PORT)
        {
            PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);

            // If InputPort is D12 or D13, need to change SearchIndex to D3
            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D3_INPUT_PORT));
        }
#endif
        else
#endif
        {
            SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(ucRegionIndex))));
        }
    }

#if(_FRC_SUPPORT == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    SysModeSetEagleSightSupport();
#endif
#endif

    UserCommonDisplaySetDVCustomizedDefault();
}

//--------------------------------------------------
// Description  : Set select region / physical port pair
// Input Value  : Region & select port
// Output Value : None
//--------------------------------------------------
void SysRegionUpdateInterface(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    DebugMessageSystem("UPD: Region", enumDisplayRegion);
    DebugMessageSystem("UPD: input port", enumInputPort);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    // If InputPort is D14 or D15, need to change SearchIndex to D4
    if((enumInputPort == _D14_INPUT_PORT) || (enumInputPort == _D15_INPUT_PORT))
#else
    if(enumInputPort == _D14_INPUT_PORT)
#endif
    {
        // Update select retion & search port
        SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D4_INPUT_PORT));
    }

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    // If InputPort is D12 or D13, need to change SearchIndex to D3
    if((enumInputPort == _D12_INPUT_PORT) || (enumInputPort == _D13_INPUT_PORT))
#else
    if(enumInputPort == _D12_INPUT_PORT)
#endif
    {
        // Update select retion & search port
        SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(_D3_INPUT_PORT));
    }
#endif
    else
#endif
    {
        // Update select retion & search port
        SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(enumInputPort));
    }

    // Reset display status info
    CLR_RGN_DISPLAY_INFO(ucRegionIndex);
}

//--------------------------------------------------
// Description  : Reset select interface info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysRegionResetInfo(void)
{
    memset(&g_pstRegionInfo, 0x00, sizeof(g_pstRegionInfo));
}

//--------------------------------------------------
// Description  : Get display state of specific region
// Input Value  : select region
// Output Value : display state
//--------------------------------------------------
EnumDisplayState SysRegionGetDisplayState(EnumDisplayRegion enumDisplayRegion)
{
    return GET_RGN_DISPLAY_STATE(ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get source type of specific region
// Input Value  : select reigon
// Output Value : source type
//--------------------------------------------------
EnumSourceType SysRegionGetSourceType(EnumDisplayRegion enumDisplayRegion)
{
    return GET_RGN_SOURCE_TYPE(ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get input port of specific region
// Input Value  : select reigon
// Output Value : port type
//--------------------------------------------------
EnumInputPort SysRegionGetInputPort(EnumDisplayRegion enumDisplayRegion)
{
    return GET_RGN_INPUT_PORT(ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get display region enum by region index
// Input Value  : region index
// Output Value : display region enum
//--------------------------------------------------
EnumDisplayRegion SysRegionGetDisplayRegion(EnumRegionIndex enumRegionIndex)
{
    return GET_RGN_DISPLAY_REGION(enumRegionIndex);
}

//--------------------------------------------------
// Description  : Get display region index by region enum
// Input Value  : display region enum
// Output Value : region index
//--------------------------------------------------
EnumRegionIndex SysRegionGetDisplayRegionIndex(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerRegionGetIndex(enumDisplayRegion);
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Get Region Source Index
// Input Value  : ucRgnNum --> Region Number
// Output Value : GET_RGN_SOURCE_INDEX(ucRgnNum)
//--------------------------------------------------
BYTE SysRegionGetSourceIndex(BYTE ucRgnNum)
{
    return GET_RGN_SOURCE_INDEX(ucRgnNum);
}
#endif

//--------------------------------------------------
// Description  : Check whether all displays equal to give one
// Input Value  : display state
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckAllDisplayState(EnumDisplayState enumDisplayState)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    // Check display state
    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_DISPLAY_STATE(ucRegionIndex) != enumDisplayState)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Active Status
// Input Value  : None
// Output Value : TRUE = Some Region Display State = Active State, FALSE = None
//--------------------------------------------------
bit SysRegionCheckDisplayActiveState(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if(SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE)
        {
            return _TRUE;
        }
    }
    else
    {
        if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0x00)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether all system display state changed
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckSystemDisplayStateChange(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    // Check system display state change
    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_DISPLAY_STATE_CHANGE_SYS(ucRegionIndex) == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether all user display state changed
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckUserDisplayStateChange(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    // Check user display state change
    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_DISPLAY_STATE_CHANGE_USR(ucRegionIndex) == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check specific region event occurs
// Input Value  : enumDisplayRegion --> select region
//                enumDisplayEvent --> display event
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckDisplayEvent(EnumDisplayRegion enumDisplayRegion, EnumDisplayEvent enumDisplayEvent)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    switch(enumDisplayEvent)
    {
        case _DISPLAY_EVENT_TIMING_CONFIRMED:
            return GET_RGN_TIMING_CONFIRM(ucRegionIndex);

        case _DISPLAY_EVENT_TIMING_DOUBLE_CHECK:
            return GET_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);

        case _DISPLAY_EVENT_MEASURE_CHECKING:
            return GET_RGN_MEASURE_CHECKING(ucRegionIndex);

        case _DISPLAY_EVENT_FIRST_ACTIVE:
            return GET_RGN_FIRST_ACTIVE(ucRegionIndex);

        case _DISPLAY_EVENT_STATE_CHANGE_SYS:
            return GET_RGN_DISPLAY_STATE_CHANGE_SYS(ucRegionIndex);

        case _DISPLAY_EVENT_STATE_CHANGE_USR:
            return GET_RGN_DISPLAY_STATE_CHANGE_USR(ucRegionIndex);

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear display event flags for all regions
// Input Value  : ucDisplayEventSet --> combination of display event
// Output Value : None
//--------------------------------------------------
void SysRegionClearAllDisplayEvent(BYTE ucDisplayEventSet)
{
    BYTE ucIndex = GET_RGN_MAX_DISPLAY_REGION();

    do
    {
        g_pstRegionInfo[--ucIndex].stDisplayStatusInfo.enumDisplayEvent &= ~ucDisplayEventSet;
    }
    while(ucIndex != 0x00);
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumDisplayRegion --> select measure region
// Output Value : None
//--------------------------------------------------
void SysRegionSetMeasureResultPointerRegion(EnumDisplayRegion enumDisplayRegion)
{
    // Set measure result pointer
    g_pstMeasureRegionTimingInfoPointer = &(g_pstMeasureRegionTimingInfo[ScalerRegionGetIndex(enumDisplayRegion)]);
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumDisplayRegion --> select measure region
// Output Value : None
//--------------------------------------------------
EnumDisplayRegion SysRegionGetMeasureResultPointerRegion(void)
{
    return ScalerMeasureGetResultPointerRegion();
}

//--------------------------------------------------
// Description  : Get measure result by region
// Input Value  : enumDisplayRegion --> select measure region
//                pstTimingInfo -> result pointer
// Output Value : None
//--------------------------------------------------
void SysRegionGetMeasureResultByRegion(EnumDisplayRegion enumDisplayRegion, StructTimingInfo *pstTimingInfo)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    *pstTimingInfo = g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo;
}

//--------------------------------------------------
// Description  : Convert input port to select region, if existed
// Input Value  : enumInputPort --> input port
// Output Value : select region
//--------------------------------------------------
EnumDisplayRegion SysRegionConvertPortToRegion(EnumInputPort enumInputPort)
{
    BYTE ucRegionIndex = SysRegionConvertPortToRegionIndex(enumInputPort);

    if(ucRegionIndex != _REGION_INDEX_NONE)
    {
        return GET_RGN_DISPLAY_REGION(ucRegionIndex);
    }

    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  : Convert input port to region index, if existed
// Input Value  : enumInputPort --> input port
// Output Value : region index
//--------------------------------------------------
EnumRegionIndex SysRegionConvertPortToRegionIndex(EnumInputPort enumInputPort)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    // If InputPort = D14/D15, need change to D4 port
    if((enumInputPort == _D14_INPUT_PORT) || (enumInputPort == _D15_INPUT_PORT))
#else
    if(enumInputPort == _D14_INPUT_PORT)
#endif
    {
        enumInputPort = _D4_INPUT_PORT;
    }

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    // If InputPort = D12/D13, need change to D3 port
    if((enumInputPort == _D12_INPUT_PORT) || (enumInputPort == _D13_INPUT_PORT))
#else
    if(enumInputPort == _D12_INPUT_PORT)
#endif
    {
        enumInputPort = _D3_INPUT_PORT;
    }
#endif
#endif

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_INPUT_PORT(ucRegionIndex) == enumInputPort)
        {
            return ucRegionIndex;
        }
    }

    return _REGION_INDEX_NONE;
}

//--------------------------------------------------
// Description  : Convert source search index to region index, if existed
// Input Value  : ucSearchIndex --> source search index
// Output Value : region index
//--------------------------------------------------
EnumRegionIndex SysRegionConvertSourceIndexToRegionIndex(BYTE ucSearchIndex)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)
        {
            return ucRegionIndex;
        }
    }

    return _REGION_INDEX_NONE;
}

//--------------------------------------------------
// Description  : Calculate current display state numbers
// Input Value  : display state
// Output Value : count result
//--------------------------------------------------
BYTE SysRegionGetDisplayStateCount(EnumDisplayState enumDisplayState)
{
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    if(enumDisplayState == _DISPLAY_STATE_MAX)
    {
        return ucRegionCount;
    }
    else
    {
        BYTE ucRegionIndex = 0;
        BYTE ucCount = 0;

        for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
        {
            if(GET_RGN_DISPLAY_STATE(ucRegionIndex) == enumDisplayState)
            {
                ucCount += 1;
            }
        }

        return ucCount;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Set display state for display regions with identical source index
// Input Value  : ucSearchIndex --> source search index
//             enumDisplayState --> display state
// Output Value : None
//--------------------------------------------------
void SysRegionSetDisplayStateBySearchIndex(BYTE ucSearchIndex, EnumDisplayState enumDisplayState)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)
        {
            DebugMessageSystem("Port state update", ucRegionIndex);

            switch(enumDisplayState)
            {
                case _DISPLAY_STATE_NONE:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_RESET_TO_NONE);
                    break;
                case _DISPLAY_STATE_NO_SIGNAL:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);
                    break;
                case _DISPLAY_STATE_OOR:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_OOR);
                    break;
                case _DISPLAY_STATE_DISPLAY_READY:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_DISPLAY_READY);
                    break;
                case _DISPLAY_STATE_ACTIVE:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_ACTIVE);
                    break;

                default:
                    break;
            }
        }
    }
}

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Transfer Eagle Sight Display Mode
// Input Value  : enumEagleSightSupport, enumDisplayMode
// Output Value : enumDisplayMode
//--------------------------------------------------
EnumDisplayMode SysRegionEagleSightTransDisplayMode(EnumDisplayMode enumDisplayMode)
{
    return ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
}
#endif
