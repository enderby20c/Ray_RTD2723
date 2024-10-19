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
// ID Code      : UserCommonTmds.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "Tmds/UserCommonTmds.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : InputPort and Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE UserCommonTmdsGetAVIInfo(EnumInputPort enumInputPort, EnumAviInfoContent enumContent)
{
    return ScalerTmdsMacRxHdmiGetAVIInfo(enumInputPort, enumContent);
}

//--------------------------------------------------
// Description  : Set Z0 HPD Type
// Input Value  : Z0/HPD type, Z0LowPeriod(ms), usHpdLowPeriod(ms), usZ0HpdInterval(ms)
// Output Value : None
// --|______________|----------------|______________|-----
//    usZ0LowPeriod  usZ0HpdInterval  usHpdLowPeriod
//--------------------------------------------------
void UserCommonTmdsSetHdmiZ0HpdType(EnumHdmiZ0HpdType enumHdmiZ0HpdType, WORD usZ0LowPeriod, WORD usZ0HpdInterval)
{
    ScalerTmdsMacRxSetHdmiZ0HpdType(enumHdmiZ0HpdType, usZ0LowPeriod, usZ0HpdInterval);
}

//--------------------------------------------------
// Description  : Get HDMI Z0 Status (when High, Kernel has been toggle HPD)
// Input Value  : InputPort
// Output Value : EnumHdmiZ0Status
//--------------------------------------------------
EnumHdmiZ0Status UserCommonTmdsGetZ0Status(EnumInputPort enumInputPort)
{
    if(ScalerTmdsMacRxGetDigitalPort(enumInputPort) == _TRUE)
    {
        return _HDMI_Z0_HIGH;
    }
    else
    {
        return _HDMI_Z0_LOW;
    }
}

//--------------------------------------------------
// Description  : HDMI HPD/ DDC Config
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonTmdsHotPlugDdcConfig(EnumInputPort enumInputPort, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // When Enable, HPD set H & Ddc pinshare switch to correct(ie.DDC Normal work)
        switch(enumInputPort)
        {
#if(_D1_HDMI_SUPPORT == _ON)
            case _D1_INPUT_PORT:
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC1))
                ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);
#endif
                break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            case _D2_INPUT_PORT:
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC2))
                ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);
#endif
                break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            case _D3_INPUT_PORT:
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC3))
                ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_DDC);
#endif
                break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            case _D4_INPUT_PORT:
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC4))
                ScalerPinshareGpioDdcPinSwitch(_DDC4_SWITCH_DDC);
#endif
                break;
#endif
            default:
                break;
        }
    }
    else
    {
        // When Disable, HPD set Low & Ddc pinshare switch to GPI(ie. DDC force Nack)
        switch(enumInputPort)
        {
#if(_D1_HDMI_SUPPORT == _ON)
            case _D1_INPUT_PORT:
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC1))
                ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_GPI);
#endif
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            case _D2_INPUT_PORT:
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC2))
                ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_GPI);
#endif
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            case _D3_INPUT_PORT:
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC3))
                ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_GPI);
#endif
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
                break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            case _D4_INPUT_PORT:
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) || (_PCB_DEBUG_DDC != _DDC4))
                ScalerPinshareGpioDdcPinSwitch(_DDC4_SWITCH_GPI);
#endif
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_LOW);
                break;
#endif
            default:
                break;
        }
    }
}

#if(_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI SPD Product Description Info Contents
// Input Value  : InputPort
// Output Value : EnumHdmiSpdProuductlInfo
//--------------------------------------------------
StructHdmiSpdInfo UserCommonTmdsGetSpdInfo(EnumInputPort enumInputPort)
{
    return ScalerTmdsMacRxHdmiGetSpdInfo(enumInputPort);
}

//--------------------------------------------------
// Description  : Get HDMI SPD Product Description Info Contents
// Input Value  : InputPort
// Output Value : EnumHdmiSpdProuductlInfo
//--------------------------------------------------
EnumHdmiSpdProuductlInfo UserCommonTmdsGetSpdPdInfo(EnumInputPort enumInputPort)
{
    StructHdmiSpdInfo stSpdInfo = UserCommonTmdsGetSpdInfo(enumInputPort);

    if(stSpdInfo.b1StructValuable == 0x01)
    {
        if(memcmp(stSpdInfo.pucHdmiProductDescription, "PS4", 3) == 0)
        {
            return _PRODUCT_DESCRIPTION_PS4;
        }

        if(memcmp(stSpdInfo.pucHdmiProductDescription, "PS5", 3) == 0)
        {
            return _PRODUCT_DESCRIPTION_PS5;
        }

        if(memcmp(stSpdInfo.pucHdmiProductDescription, "Xbox One", 8) == 0)
        {
            return _PRODUCT_DESCRIPTION_XBOX_ONE;
        }

        if(memcmp(stSpdInfo.pucHdmiProductDescription, "Xbox", 4) == 0)
        {
            return _PRODUCT_DESCRIPTION_XBOX;
        }

        if(memcmp(stSpdInfo.pucHdmiProductDescription, "GeFor#ce", 8) == 0)
        {
            return _PRODUCT_DESCRIPTION_NVIDIA;
        }
    }

    return _PRODUCT_DESCRIPTION_NONE;
}

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
//--------------------------------------------------
// Description  : Get HDMI SPD Product Description Info Contents
// Input Value  : InputPort
// Output Value : EnumHdmiSpdProuductlInfo
//--------------------------------------------------
EnumHdmiSpdProuductlInfo UserCommonTmdsGetHbrAudioSrcInfo(EnumInputPort enumInputPort)
{
    StructHdmiSpdInfo stSpdInfo = UserCommonTmdsGetSpdInfo(enumInputPort);

    if(stSpdInfo.b1StructValuable == 0x01)
    {
        if(memcmp(stSpdInfo.pucHdmiProductDescription, "PS", 2) == 0)
        {
            return _PRODUCT_DESCRIPTION_PS_SERIES;
        }

        if(memcmp(stSpdInfo.pucHdmiProductDescription, "Xbox", 4) == 0)
        {
            return _PRODUCT_DESCRIPTION_XBOX_SERIES;
        }

        if(memcmp(stSpdInfo.pucHdmiProductDescription, "GeFor#ce", 8) == 0)
        {
            return _PRODUCT_DESCRIPTION_NVIDIA;
        }
    }

    return _PRODUCT_DESCRIPTION_NONE;
}
#endif
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI SPD Product Description Info Contents
// Input Value  : InputPort
// Output Value : EnumVideoDimensionType
//--------------------------------------------------
EnumVideoDimensionType UserCommonTmdsGet3dVideoValid(EnumInputPort enumInputPort)
{
    if(ScalerTmdsMacRxGet3dVideoValid(enumInputPort) == _TRUE)
    {
        return _HDMI_3D_VIDEO_FORMAT;
    }
    else
    {
        return _HDMI_2D_VIDEO_FORMAT;
    }
}
#endif

#if(_HDMI20_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Version Scdc Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonTmdsGetVersionScdcInfo(void)
{
    BYTE pucRtkIdstring[8] = {'R', 'T', 'D', ' ', ' ', ' ', ' ', ' '};
    WORD usIdString = (_HDMI_SINK_RTK_ID_STRING_H << 8 | _HDMI_SINK_RTK_ID_STRING_L);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    StructDrrAmdAupiInfo stDrrHdmiAmdAupiInfo = {0};
    StructDrrAmdAupiInfo stCheck = {0};

    UserInterfaceFreeSyncGetHdmiAupiPanelInfo(&stDrrHdmiAmdAupiInfo);
    CLR_FREESYNC_HDMI_AUPI_INFO();

    // check if stDrrAmdAupiInfo is all zero
    if(memcmp(&stDrrHdmiAmdAupiInfo, &stCheck, sizeof(stDrrHdmiAmdAupiInfo)) != 0)
    {
        g_stDrrHdmiAmdAupiInfo = stDrrHdmiAmdAupiInfo;
        SET_FREESYNC_HDMI_AUPI_INFO();
    }
#endif

    // Get ID String
    for(pData[0] = 0; pData[0] < 4; pData[0]++)
    {
        switch((usIdString >> (pData[0] * 4)) & 0x0F)
        {
            case 0x00:
                pucRtkIdstring[6 - pData[0]] = '0';
                break;

            case 0x01:
                pucRtkIdstring[6 - pData[0]] = '1';
                break;

            case 0x02:
                pucRtkIdstring[6 - pData[0]] = '2';
                break;

            case 0x03:
                pucRtkIdstring[6 - pData[0]] = '3';
                break;

            case 0x04:
                pucRtkIdstring[6 - pData[0]] = '4';
                break;

            case 0x05:
                pucRtkIdstring[6 - pData[0]] = '5';
                break;

            case 0x06:
                pucRtkIdstring[6 - pData[0]] = '6';
                break;

            case 0x07:
                pucRtkIdstring[6 - pData[0]] = '7';
                break;

            case 0x08:
                pucRtkIdstring[6 - pData[0]] = '8';
                break;

            case 0x09:
                pucRtkIdstring[6 - pData[0]] = '9';
                break;

            default:
                break;
        }
    }

    memcpy(&g_stTmdsMacRxScdcInfoSet.pucIdstring[0], pucRtkIdstring, 8);

    // Get Manufacture Oui
    g_stTmdsMacRxScdcInfoSet.ucManufactureOuiH = _HDMI_SINK_MANUFACTURE_OUI_H;
    g_stTmdsMacRxScdcInfoSet.ucManufactureOuiM = _HDMI_SINK_MANUFACTURE_OUI_M;
    g_stTmdsMacRxScdcInfoSet.ucManufactureOuiL = _HDMI_SINK_MANUFACTURE_OUI_L;

    // Get HW/FW Version
    g_stTmdsMacRxScdcInfoSet.ucHdmiHwVersion = ScalerTmdsMacRxGetHwVersion();
    g_stTmdsMacRxScdcInfoSet.ucHdmiFwVersionMajor = 0x04;
    g_stTmdsMacRxScdcInfoSet.ucHdmiFwVersionMinor = 0x00;
}
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI Version
// Input Value  : EnumInputPort
// Output Value : EnumInputHdmiVer
//--------------------------------------------------
EnumHdmiFrlRate UserCommonTmdsGetFrlRate(EnumInputPort enumInputPort)
{
    return ScalerHdmiFrlMacRxGetFrlRate(enumInputPort);
}
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI21 FVA Factor
// Input Value  : enumInputPort
// Output Value : BYTE 1~16
//--------------------------------------------------
BYTE UserCommonTmdsHdmi21GetFvaFactor(EnumInputPort enumInputPort)
{
    return ScalerTmdsMacRxHdmi21GetFvaFactor(enumInputPort);
}
#endif
#endif
