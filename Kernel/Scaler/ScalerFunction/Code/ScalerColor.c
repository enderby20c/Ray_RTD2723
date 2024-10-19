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
// ID Code      : ScalerColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COLOR__

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructColorInfo g_pstColorInfo[_COLOR_INFO_SIZE];

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
bit g_bColorLocalContrastReadyReadStatus = _FALSE;
#endif
#if((_OGC_FUNCTION == _ON) ||\
    (_OCC_FUNCTION == _ON) ||\
    (_OGC_DICOM_FUNCTION == _ON) ||\
    (_UNIFORMITY_FUNCTION == _ON))
BYTE *g_pucColorDISP_CALIBRATION_FLASH = (BYTE xdata *)(_OGC_FLASH_PAGE * _FLASH_PAGE_SIZE);
BYTE *g_pucColorDISP_FREESYNC_II_CALIBRATION_FLASH = (BYTE xdata *)(_FREESYNC_II_FLASH_PAGE * _FLASH_PAGE_SIZE);
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
BYTE g_ucColorAdvancedHDR10IGNorm;
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
EnumHDRTargetStatus g_penumColorHDRTargrtStatus[_MULTI_DISPLAY_MAX];
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
WORD code tusHDR10_IG_BACKLIGHT_ADAPTIVE_TM_ADDRESS_INDEX[] =
{
    _OGC_HDR10_IG_ADAPTIVE_TM_LV1_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV1_DARK_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV2_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV2_DARK_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV3_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV3_DARK_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV4_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV4_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
};
#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
WORD code tusHDR10_IG_MASTERING_LV_STEPLESS_TM_ADDRESS_INDEX[] =
{
    _OGC_HDR10_IG_1200_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_DARK_ADDRESS,
    _OGC_HDR10_IG_540_NOR_ADDRESS,
    _OGC_HDR10_IG_540_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
};
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : EnumInputPort
// Output Value : Input Color Depth
//--------------------------------------------------
BYTE ScalerColorGetColorDepth(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _COLOR_DEPTH_8_BITS;
    }

    return GET_COLOR_DEPTH(enumInputPort);
}

//--------------------------------------------------
// Description  : Return Current Color Space for Upper Layer
// Input Value  : None
// Output Value : Current Color Space
//--------------------------------------------------
EnumColorSpace ScalerColorGetColorSpace(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _COLOR_SPACE_RGB;
    }

    return GET_COLOR_SPACE(enumInputPort);
}

//--------------------------------------------------
// Description  : Return Current Color Space for Upper Layer
// Input Value  : None
// Output Value : Current Color Space
//--------------------------------------------------
bit ScalerColorGetColorSpaceRGB(EnumColorSpace enumColorSpace)
{
    return GET_COLOR_SPACE_RGB(enumColorSpace);
}

#if(_COLOR_IP_420_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get format conversion 420/422 status by port
// Input Value  : enumInputPort -> input port
// Output Value : _TRUE if any 420 block from the specified port is set
//--------------------------------------------------
bit ScalerColor420To422GetStatusByPort(EnumInputPort enumInputPort)
{
    BYTE ucIndex = 0;
    EnumFormatConversionSourceType enumFormatConversionSourceType = ScalerFmtCnvConvertPortType(enumInputPort);

    for(ucIndex = 0; ucIndex < _HW_I_DOMAIN_PATH_COUNT; ++ucIndex)
    {
        EnumInputDataPath enumCurrPath = GET_IDOMAIN_DATA_PATH(ucIndex);

        // whether enumCurrPath is measure input path
        if((GET_MEASURE_INPUT_PATH() & enumCurrPath) == 0x00)
        {
            continue;
        }

        // if 420 is enabled for this input path
        if(ScalerColor420To422GetStatusByPath(enumCurrPath) == _FALSE)
        {
            continue;
        }

        // if this input path is connected to enumInputPort
        if(ScalerFmtCnvGetSourceType(enumCurrPath) == enumFormatConversionSourceType)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get format conversion 420/422 status by path
// Input Value  : enumInputDataPath --> current input path
// Output Value : _TRUE if 420 block of the specified path is set
//--------------------------------------------------
bit ScalerColor420To422GetStatusByPath(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2_S1_S2:
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
            return ScalerColor420To422P0GetStatus();

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
        case _INPUT_PATH_M2:
            return ScalerColor420To422P1GetStatus();
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S1_S2:
            return ScalerColor420To422P2GetStatus();
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
        case _INPUT_PATH_S2:
        case _INPUT_PATH_S3:
        case _INPUT_PATH_S3_S4:
            return ScalerColor420To422P3GetStatus();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get format conversion 420/422 double pixel mode status by path
// Input Value  : enumInputDataPath --> current input path
// Output Value : _TRUE if 420 double pixel mode of the specified path is set
//--------------------------------------------------
bit ScalerColor420To422GetDoublePixelStatusByPath(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2_S1_S2:
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
            return ScalerColor420To422P0GetDoublePixelStatus();

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
        case _INPUT_PATH_M2:
            return ScalerColor420To422P1GetDoublePixelStatus();
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S1_S2:
            return ScalerColor420To422P2GetDoublePixelStatus();
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
        case _INPUT_PATH_S2:
        case _INPUT_PATH_S3:
        case _INPUT_PATH_S3_S4:
            return ScalerColor420To422P3GetDoublePixelStatus();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Final setting for 420 block
// Input Value  : enumInputDataPath --> target input path
//                enumInputPort --> target input port
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422FinalSettingByPath(EnumInputDataPath enumInputDataPath, EnumInputPort enumInputPort)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2_S1_S2:
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
            ScalerColor420To422P0FinalSetting(enumInputPort, enumInputDataPath);
            break;

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
        case _INPUT_PATH_M2:
            ScalerColor420To422P1FinalSetting(enumInputPort, enumInputDataPath);
            break;
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S1_S2:
            ScalerColor420To422P2FinalSetting(enumInputPort, enumInputDataPath);
            break;
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
        case _INPUT_PATH_S2:
        case _INPUT_PATH_S3:
        case _INPUT_PATH_S3_S4:
            ScalerColor420To422P3FinalSetting(enumInputPort, enumInputDataPath);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Run 420 initial setting flow by path
// Input Value  : enumInputDataPath --> target input path
//                enumInputPort --> related port for color space info
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422InitialByPath(EnumInputDataPath enumInputDataPath)
{
    if(enumInputDataPath == _INPUT_PATH_ALL)
    {
        // init all
        ScalerColor420To422P0InitialSetting();

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
        ScalerColor420To422P1InitialSetting();
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
        ScalerColor420To422P2InitialSetting();
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
        ScalerColor420To422P3InitialSetting();
#endif
    }
    else
    {
        switch(enumInputDataPath)
        {
            case _INPUT_PATH_M1_M2_S1_S2:
            case _INPUT_PATH_M1:
            case _INPUT_PATH_M1_M2:
                ScalerColor420To422P0InitialSetting();
                break;

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
            case _INPUT_PATH_M2:
                ScalerColor420To422P1InitialSetting();
                break;
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
            case _INPUT_PATH_S1:
            case _INPUT_PATH_S1_S2:
                ScalerColor420To422P2InitialSetting();
                break;
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
            case _INPUT_PATH_S2:
            case _INPUT_PATH_S3:
            case _INPUT_PATH_S3_S4:
                ScalerColor420To422P3InitialSetting();
                break;
#endif

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Final setting for P0 420 block
// Input Value  : enumInputPort --> target input port
//                enumInputDataPath --> target input path
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P0FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420)
    {
        BYTE ucFactor = 1;
        BYTE ucPixelMode = _FC_1_PIXEL_MODE;

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
        ucFactor *= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
        ucPixelMode = ScalerFmtCnvGetPixelModeTargetFactor(enumInputDataPath);
#endif

        ucFactor *= ucPixelMode;

        // enable double pixel mode when single path output clk > single path clk limit
        // In ScalerSyncGetInputPixelClk, 420 is turned off in this state, the equation *2 should be exist
        if((ScalerSyncGetInputPixelClk(enumInputPort) * 2) > ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, ucPixelMode))
        {
            ScalerColor420To422P0DoublePixelEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerColor420To422P0DoublePixelEnable(_FUNCTION_OFF);
        }

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
        // Update actual 420-422 state
        ScalerColor420To422P0Setting(GET_OFFLINE_H_START(), GET_OFFLINE_H_WIDTH());
#else
        // Update actual 420-422 state
        ScalerColor420To422P0Setting(GET_ACTIVE_H_START() * ucFactor, GET_ACTIVE_H_WIDTH() * ucFactor);
#endif

        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);

        // Enable 420-to-422
        ScalerColor420To422P0Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get P0 420 block status
// Input Value  : None
// Output Value : _TRUE if 420 is enabled
//--------------------------------------------------
bit ScalerColor420To422P0GetStatus(void)
{
    return (ScalerGetBit(P31_D1_YUV420TO422_PATH0, _BIT7) != 0);
}

//--------------------------------------------------
// Description  : Get P0 420 double pixel mode status
// Input Value  : None
// Output Value : _TRUE if 420 double pixel mode is enabled
//--------------------------------------------------
bit ScalerColor420To422P0GetDoublePixelStatus(void)
{
    return (ScalerGetBit(P31_D0_YUV420TO422_CTL_PATH0_1, _BIT1) != 0);
}

//--------------------------------------------------
// Description  : Initial setting for P0 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P0InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422P0Enable(_FUNCTION_OFF);
}

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Final setting for P1 420 block
// Input Value  : enumInputPort --> target input port
//                enumInputDataPath --> target input path
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P1FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420)
    {
        BYTE ucFactor = 1;

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
        ucFactor *= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

        // enable double pixel mode when single path output clk > single path clk limit
        // In ScalerSyncGetInputPixelClk, 420 is turned off in this state, the equation *2 should be exist
        if((ScalerSyncGetInputPixelClk(enumInputPort) * 2) > ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, _FC_1_PIXEL_MODE))
        {
            ScalerColor420To422P1DoublePixelEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerColor420To422P1DoublePixelEnable(_FUNCTION_OFF);
        }

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
        // Update actual 420-422 state
        ScalerColor420To422P1Setting(GET_OFFLINE_H_START(), GET_OFFLINE_H_WIDTH());
#else
        // Update actual 420-422 state
        ScalerColor420To422P1Setting(GET_ACTIVE_H_START() * ucFactor, GET_ACTIVE_H_WIDTH() * ucFactor);
#endif

        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);

        // Enable 420-to-422
        ScalerColor420To422P1Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get P1 420 block status
// Input Value  : None
// Output Value : _TRUE if 420 is enabled
//--------------------------------------------------
bit ScalerColor420To422P1GetStatus(void)
{
    return (ScalerGetBit(P31_D2_YUV420TO422_PATH1, _BIT7) != 0);
}

//--------------------------------------------------
// Description  : Get P1 420 double pixel mode status
// Input Value  : None
// Output Value : _TRUE if 420 double pixel mode is enabled
//--------------------------------------------------
bit ScalerColor420To422P1GetDoublePixelStatus(void)
{
    return (ScalerGetBit(P31_D0_YUV420TO422_CTL_PATH0_1, _BIT0) != 0);
}

//--------------------------------------------------
// Description  : Initial setting for P1 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P1InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422P1Enable(_FUNCTION_OFF);
}
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Final setting for P2 420 block
// Input Value  : enumInputPort --> target input port
//                enumInputDataPath --> target input path
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P2FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420)
    {
        BYTE ucFactor = 1;

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
        ucFactor *= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

        // enable double pixel mode when single path output clk > single path clk limit
        // In ScalerSyncGetInputPixelClk, 420 is turned off in this state, the equation *2 should be exist
        if((ScalerSyncGetInputPixelClk(enumInputPort) * 2) > ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, _FC_1_PIXEL_MODE))
        {
            ScalerColor420To422P2DoublePixelEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerColor420To422P2DoublePixelEnable(_FUNCTION_OFF);
        }

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
        // Update actual 420-422 state
        ScalerColor420To422P2Setting(GET_OFFLINE_H_START(), GET_OFFLINE_H_WIDTH());
#else
        // Update actual 420-422 state
        ScalerColor420To422P2Setting(GET_ACTIVE_H_START() * ucFactor, GET_ACTIVE_H_WIDTH() * ucFactor);
#endif

        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);

        // Enable 420-to-422
        ScalerColor420To422P2Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get P2 420 block status
// Input Value  : None
// Output Value : _TRUE if 420 is enabled
//--------------------------------------------------
bit ScalerColor420To422P2GetStatus(void)
{
    return (ScalerGetBit(P31_E1_YUV420TO422_PATH2, _BIT7) != 0);
}

//--------------------------------------------------
// Description  : Get P2 420 double pixel mode status
// Input Value  : None
// Output Value : _TRUE if 420 double pixel mode is enabled
//--------------------------------------------------
bit ScalerColor420To422P2GetDoublePixelStatus(void)
{
    return (ScalerGetBit(P31_E0_YUV420TO422_CTL_PATH2_3, _BIT1) != 0);
}

//--------------------------------------------------
// Description  : Initial setting for P2 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P2InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422P2Enable(_FUNCTION_OFF);
}
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Final setting for P3 420 block
// Input Value  : enumInputPort --> target input port
//                enumInputDataPath --> target input path
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P3FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420)
    {
        BYTE ucFactor = 1;
        BYTE ucPixelMode = _FC_1_PIXEL_MODE;

#if(_HW_FORMAT_CONVERSION_SD_MODE != _FORMAT_CONVERSION_SD_NONE)
        ucFactor *= ScalerFmtCnvHalfSDGetFactor(enumInputDataPath);
#endif

#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
        ucPixelMode = ScalerFmtCnvGetPixelModeTargetFactor(enumInputDataPath);
#endif

        ucFactor *= ucPixelMode;

        // enable double pixel mode when single path output clk > single path clk limit
        // In ScalerSyncGetInputPixelClk, 420 is turned off in this state, the equation *2 should be exist
        if((ScalerSyncGetInputPixelClk(enumInputPort) * 2) > ScalerFmtCnvGetPixelModeSpeedLimit(enumInputDataPath, ucPixelMode))
        {
            ScalerColor420To422P3DoublePixelEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerColor420To422P3DoublePixelEnable(_FUNCTION_OFF);
        }

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
        // Update actual 420-422 state
        ScalerColor420To422P3Setting(GET_OFFLINE_H_START(), GET_OFFLINE_H_WIDTH());
#else
        // Update actual 420-422 state
        ScalerColor420To422P3Setting(GET_ACTIVE_H_START() * ucFactor, GET_ACTIVE_H_WIDTH() * ucFactor);
#endif

        ScalerTimerWaitForIDomainEvent(_EVENT_IVS, enumInputDataPath);

        // Enable 420-to-422
        if(ScalerFmtCnvResetStatus(enumInputDataPath) == _FALSE)
        {
            DebugMessageSystem("6. ScalerColor420To422P3RetryEnable", 1);
            ScalerColor420To422P3RetryEnable();
        }
        else
        {
            DebugMessageSystem("6. ScalerColor420To422P3Enable", 1);
            ScalerColor420To422P3Enable(_FUNCTION_ON);
        }
    }
}

//--------------------------------------------------
// Description  : Get P3 420 block status
// Input Value  : None
// Output Value : _TRUE if 420 is enabled
//--------------------------------------------------
bit ScalerColor420To422P3GetStatus(void)
{
    return (ScalerGetBit(P31_E2_YUV420TO422_PATH3, _BIT7) != 0);
}

//--------------------------------------------------
// Description  : Get P3 420 double pixel mode status
// Input Value  : None
// Output Value : _TRUE if 420 double pixel mode is enabled
//--------------------------------------------------
bit ScalerColor420To422P3GetDoublePixelStatus(void)
{
    return (ScalerGetBit(P31_E0_YUV420TO422_CTL_PATH2_3, _BIT0) != 0);
}

//--------------------------------------------------
// Description  : Initial setting for P3 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422P3InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422P3Enable(_FUNCTION_OFF);
}
#endif
#endif // End of #if(_COLOR_IP_420_SUPPORT == _ON)

//--------------------------------------------------
// Description  : 422To444 parameter setting
// Input Value  : EnumInputPort, EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerColor422To444(EnumInputPort enumInputPort, EnumDisplayRegion enumDisplayRegion)
{
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    WORD usAddr = 0x0000;

#if(_DUAL_DP_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Enable 422 to 444 function which is after FtoEO
    if((enumInputPort == _DUAL_DP_INPUT_PORT) &&
       (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT) &&
       (enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2))
    {
        if((GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR422) ||
           (GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420))
        {
            // Enable YUV 422 to 444 function
            ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
            ScalerSetBit(P31_42_YUV422_TO_444_PATH2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
        }
        else
        {
            // Disable YUV 422 to 444 function
            ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
            ScalerSetBit(P31_42_YUV422_TO_444_PATH2, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
        }
    }
    else
#endif
#endif
    {
        switch(enumInputDataPath)
        {
            case _INPUT_PATH_M1:
                usAddr = P31_40_YUV422_TO_444_PATH0;
                break;

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
            case _INPUT_PATH_M2:
                usAddr = P31_41_YUV422_TO_444_PATH1;
                break;

            case _INPUT_PATH_M1_M2:
                usAddr = P31_40_YUV422_TO_444_PATH0;
                break;
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
            case _INPUT_PATH_S1:
                usAddr = P31_42_YUV422_TO_444_PATH2;
                break;
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
            case _INPUT_PATH_S2:
                usAddr = P31_43_YUV422_TO_444_PATH3;
                break;
#endif

#if((_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON))
            case _INPUT_PATH_S1_S2:
                usAddr = P31_42_YUV422_TO_444_PATH2;
                break;
#endif

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON))
            case _INPUT_PATH_M1_M2_S1_S2:
                usAddr = P31_40_YUV422_TO_444_PATH0;
                break;
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
            case _INPUT_PATH_S3:
                usAddr = P31_43_YUV422_TO_444_PATH3;
                break;
#endif

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            case _INPUT_PATH_S3_S4:
                usAddr = P31_43_YUV422_TO_444_PATH3;
                break;
#endif

            default:
                return;
        }

        if((GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR422) ||
           (GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420))
        {
            // Enable YUV 422 to 444 function
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            ScalerSetBit(usAddr, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3));
#else
            ScalerSetBit(usAddr, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
#endif
        }
        else
        {
            // Disable YUV 422 to 444 function
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            ScalerSetBit(usAddr, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#else
            ScalerSetBit(usAddr, ~(_BIT3), 0x00);
#endif
        }
    }
}

#if(_COLOR_IP_DM == _ON)
//--------------------------------------------------
// Description  : 422To444 Force Enable/Disable for DM
// Input Value  : EnumInputPort, EnumDisplayRegion, bOn
// Output Value : None
//--------------------------------------------------
void ScalerColor422To444DM(EnumInputPort enumInputPort, EnumDisplayRegion enumDisplayRegion, bit bOn)
{
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    WORD usAddr = 0x0000;
    enumInputPort = enumInputPort;

#if(_DUAL_DP_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Enable 422 to 444 function which is after FtoEO
    if((enumInputPort == _DUAL_DP_INPUT_PORT) &&
       (GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT) &&
       (enumInputDataPath == _INPUT_PATH_M1_M2_S1_S2))
    {
        if(bOn)
        {
            // Enable YUV 422 to 444 function
            ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
            ScalerSetBit(P31_42_YUV422_TO_444_PATH2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
        }
        else
        {
            // Disable YUV 422 to 444 function
            ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
            ScalerSetBit(P31_42_YUV422_TO_444_PATH2, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
        }
    }
    else
#endif
#endif
    {
        switch(enumInputDataPath)
        {
            case _INPUT_PATH_M1:
                usAddr = P31_40_YUV422_TO_444_PATH0;
                break;

#if(_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON)
            case _INPUT_PATH_M2:
                usAddr = P31_41_YUV422_TO_444_PATH1;
                break;

            case _INPUT_PATH_M1_M2:
                usAddr = P31_40_YUV422_TO_444_PATH0;
                break;
#endif

#if(_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON)
            case _INPUT_PATH_S1:
                usAddr = P31_42_YUV422_TO_444_PATH2;
                break;
#endif

#if(_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON)
            case _INPUT_PATH_S2:
                usAddr = P31_43_YUV422_TO_444_PATH3;
                break;
#endif

#if((_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON))
            case _INPUT_PATH_S1_S2:
                usAddr = P31_42_YUV422_TO_444_PATH2;
                break;
#endif

#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON))
            case _INPUT_PATH_M1_M2_S1_S2:
                usAddr = P31_40_YUV422_TO_444_PATH0;
                break;
#endif

#if(_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON)
            case _INPUT_PATH_S3:
                usAddr = P31_43_YUV422_TO_444_PATH3;
                break;
#endif

#if((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) && (_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON))
            case _INPUT_PATH_S3_S4:
                usAddr = P31_43_YUV422_TO_444_PATH3;
                break;
#endif

            default:
                return;
        }

        if(bOn)
        {
            // Enable YUV 422 to 444 function
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            ScalerSetBit(usAddr, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3));
#else
            ScalerSetBit(usAddr, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
#endif
        }
        else
        {
            // Disable YUV 422 to 444 function
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            ScalerSetBit(usAddr, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#else
            ScalerSetBit(usAddr, ~(_BIT3), 0x00);
#endif
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Wait D-Domain double buffer Ready
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerColorWaitDDomainDBApply(void)
{
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Check D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return _FALSE;
        }

        // Wait D double buffer
        return ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, (_BIT6), 0);
    }

    return _TRUE;
}

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust PIPBlending Level
// Input Value  : ucEnable
// Output Value : none
//--------------------------------------------------
void ScalerColorPIPBlendingEnable(BYTE ucEnable)
{
    if(ucEnable == _DISABLE)
    {
        ScalerSetBit(P24_00_MULTI_PIC_BLENDING, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P24_00_MULTI_PIC_BLENDING, ~_BIT0, 0x00);
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(ucEnable == _DISABLE)
        {
            ScalerSetBit(P5A_00_MULTI_PIC_BLENDING_BACK, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(P5A_00_MULTI_PIC_BLENDING_BACK, ~_BIT0, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Adjust PIPBlending Level
// Input Value  : usLevel, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorPIPBlendingLevelAdjust(WORD usLevel, EnumDBApply enumDBApply)
{
    // OSD bar 0->256, 256 means sub cover main
    // On/Off
    if(usLevel == 0xFF)
    {
        ScalerColorPIPBlendingEnable(_DISABLE);
    }
    else
    {
        ScalerColorPIPBlendingEnable(_ENABLE);
    }

    ScalerSetByte(P24_01_MULTI_PIC_BLENDING_LEVEL, usLevel);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerSetByte(P5A_01_MULTI_PIC_BLENDING_LEVEL_BACK, usLevel);
    }
#endif

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Color CPU Communication Handler (SCPU Side)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorScpuSyncHandler(void)
{
    switch(GET_KCPU_NOTIFY_INT_CMD_TYPE())
    {
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
        case _SCALER_CPU_SYNC_COLOR_SPI_DIMMING:
            ScalerSpiDimmingScpuSyncHandler();
            break;
#endif
        default:
            break;
    }
}

#if(_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CPU32 Send Advanced HDR10 Cmd
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerColorCpuSyncIntNotifyAdvancedHDR10(EnumAdvancedHDR10Cpu32Stage enumAdvancedHDR10Cpu32Stage, EnumCpuSyncCommandTimeOut enumSyncCmdTypeTimeOut)
{
    g_pstScpuSyncToKcpuCmd->unCmdBody.stColorAdvancedHDR10Cmd.ucSubCmdType = enumAdvancedHDR10Cpu32Stage;

    ScalerScpuSyncSendCmd(_SCALER_CPU_SYNC_COLOR_ADVANCED_HDR10, enumSyncCmdTypeTimeOut, _NULL_POINTER);
}
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerColorGetAdvancedHDR10InputGammaNorm(void)
{
    BYTE ucIndex = 0;
    WORD pusIGNorm[_ADVANCED_HDR10_IG_NORM_SIZE] =
    {
        249, 268, 288, 310, 334,
        359, 387, 416, 447, 481,
        517, 556, 598, 643, 691,
        742, 798, 857, 921, 990,
        1063, 1142, 1227, 1318, 1416,
        1522, 1635, 1756, 1887, 2027,
        2178, 2341, 2516, 2703, 2906,
        3123, 3357, 3609, 3880, 4173
    };

    BYTE ucLength = sizeof(pusIGNorm) / sizeof(pusIGNorm[0]);
    WORD usSceneMaxRGB = 0;
    WORD usNorm = 0;

#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
    if(GET_ADVANCED_HDR10_METADATA_TYPE() == _ADVANDED_HDR10_DHDR_METADATA)
    {
        usSceneMaxRGB = MINOF((WORD)((g_stSyncAdvancedHDR10DHDRMetaData.ulDistribution99 + 5) / 10), 10000);
    }
    else
#endif
    {
        if(GET_ADVANCED_HDR10_DELAY_MODE() == _TRUE)
        {
            usSceneMaxRGB = ((WORD)g_stSyncAdvancedHDR10BackUpMetadata.ucDistribution99 * 16);
        }
        else
        {
            usSceneMaxRGB = ((WORD)g_stSyncAdvancedHDR10Metadata.ucDistribution99 * 16);
        }
    }

    // Read from flash data
    usNorm = MAXOF(GET_ADVANCED_HDR10_PANEL_MAX_LV(), usSceneMaxRGB);
    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        if(usNorm <= pusIGNorm[ucIndex])
        {
            return ucIndex;
        }
    }
    return (ucLength - 1);
}

//--------------------------------------------------
// Description  : Get PCM HLW DB Ststus
// Input Value  : EnumPCMHLWDBSel
// Output Value : on/off
//--------------------------------------------------
bit ScalerColorGetPCMHLWDBStatus(EnumPCMHLWDBSel enumPCMHLWDBSel)
{
    switch(enumPCMHLWDBSel)
    {
        case _PCM_HLW_DB_A:
            return (ScalerGetBit(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT7) == _BIT7);
            break;

        case _PCM_HLW_DB_B:
            return (ScalerGetBit(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT7) == _BIT7);
            break;

        case _PCM_HLW_DB_A_OR_B:
            return ((ScalerGetBit(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT7) == _BIT7) || (ScalerGetBit(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT7) == _BIT7));
            break;

        default:
            return _DISABLE;
            break;
    }
    return _DISABLE;
}

//--------------------------------------------------
// Description  : PCM HLW DB Reinitial
// Input Value  : EnumPCMHLWDBSel
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMHLWDBReInitial(EnumPCMHLWDBSel enumPCMHLWDBSel)
{
    switch(enumPCMHLWDBSel)
    {
        case _PCM_HLW_DB_A:
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT7)); // PCM HLW DB should be off-on
            break;

        case _PCM_HLW_DB_B:
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT7)); // PCM HLW DB should be off-on
            break;

        case _PCM_HLW_DB_A_OR_B:
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT7)); // PCM HLW DB should be off-on
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT4 | _BIT1), (_BIT7)); // PCM HLW DB should be off-on
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get PCM HLW DB Ststus
// Input Value  : EnumPCMHLWDBSel
// Output Value : on/off
//--------------------------------------------------
bit ScalerColorGetPCMHLWDBApply(EnumPCMHLWDBSel enumPCMHLWDBSel)
{
    switch(enumPCMHLWDBSel)
    {
        case _PCM_HLW_DB_A:
            return (ScalerGetBit(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT6) == _BIT6);
            break;

        case _PCM_HLW_DB_B:
            return (ScalerGetBit(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT6) == _BIT6);
            break;

        case _PCM_HLW_DB_A_OR_B:
            return ((ScalerGetBit(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT6) == _BIT6) || (ScalerGetBit(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT6) == _BIT6));
            break;

        default:
            return _FALSE;
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : PCM HLW DB Apply
// Input Value  : EnumDBApply and EnumPCMHLWDBSel
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMHLWDBApply(EnumDBApply enumDBApply, EnumPCMHLWDBSel enumPCMHLWDBSel)
{
    if((ScalerColorGetPCMHLWDBStatus(enumPCMHLWDBSel) == _DISABLE) || (enumDBApply == _DB_APPLY_NONE))
    {
        return;
    }
    else
    {
        EnumPCMHLWDBSel enumPollingPCMHLWDBSel = _PCM_HLW_DB_A_OR_B; // PCM HLW DB Polling Selection

        // Check D domain status before set apply bit
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }

        if(enumPCMHLWDBSel == _PCM_HLW_DB_A_OR_B) // DB Apply is active by normal process
        {
            if(ScalerColorGetPCMHLWDBApply(_PCM_HLW_DB_A_OR_B) == _FALSE) // if no any db is active
            {
                if(ScalerColorGetPCMHLWDBStatus(_PCM_HLW_DB_B) == _ENABLE) // if B DB is enable, then first active B DB
                {
                    SET_ADVANCED_HDR10_FAKE_APPLY_B();
                    enumPollingPCMHLWDBSel = _PCM_HLW_DB_B;
                }
                else
                {
                    SET_ADVANCED_HDR10_FAKE_APPLY_A();
                    enumPollingPCMHLWDBSel = _PCM_HLW_DB_A;
                }
                ScalerSetBit((enumPollingPCMHLWDBSel == _PCM_HLW_DB_A) ? (P4F_D0_PCM_HLW_DB_A_CTRL) : (P4F_D1_PCM_HLW_DB_B_CTRL), ~(_BIT6 | _BIT4 | _BIT1), (_BIT6));
            }
            else // if any db is active already, just follow it and no need to set DB Apply
            {
                if(ScalerColorGetPCMHLWDBApply(_PCM_HLW_DB_B) == _TRUE)
                {
                    enumPollingPCMHLWDBSel = _PCM_HLW_DB_B;
                }
                else
                {
                    enumPollingPCMHLWDBSel = _PCM_HLW_DB_A;
                }
            }
        }
        else // DB Apply is active by Advanced HDR10 process, so enumPCMHLWDBSel must be A or B
        {
            enumPollingPCMHLWDBSel = enumPCMHLWDBSel;
            if(ScalerColorGetPCMHLWDBApply(enumPCMHLWDBSel) == _FALSE)
            {
                ScalerSetBit((enumPollingPCMHLWDBSel == _PCM_HLW_DB_A) ? (P4F_D0_PCM_HLW_DB_A_CTRL) : (P4F_D1_PCM_HLW_DB_B_CTRL), ~(_BIT6 | _BIT4 | _BIT1), (_BIT6));
            }
        }

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            // Wait PCM HLW double buffer
            if(ScalerColorPCMHLWDBPolling(enumPollingPCMHLWDBSel) == _FALSE)
            {
                // Clear apply bit(bit6) when PCM HLW DB Timeout
                ScalerSetBit((enumPollingPCMHLWDBSel == _PCM_HLW_DB_A) ? (P4F_D0_PCM_HLW_DB_A_CTRL) : (P4F_D1_PCM_HLW_DB_B_CTRL), ~(_BIT6 | _BIT4 | _BIT1), 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : PCM HLW DB Apply
// Input Value  : EnumDBApply and EnumPCMHLWDBSel
// Output Value : None
//--------------------------------------------------
bit ScalerColorPCMHLWDBPolling(EnumPCMHLWDBSel enumPCMHLWDBSel)
{
    if(enumPCMHLWDBSel == _PCM_HLW_DB_A_OR_B)
    {
        return ((ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P4F_D0_PCM_HLW_DB_A_CTRL, (_BIT6), 0)) &&
                (ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P4F_D1_PCM_HLW_DB_B_CTRL, (_BIT6), 0)));
    }
    else
    {
        WORD usAddr = ((enumPCMHLWDBSel == _PCM_HLW_DB_A) ? P4F_D0_PCM_HLW_DB_A_CTRL : P4F_D1_PCM_HLW_DB_B_CTRL);
        return (ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, usAddr, (_BIT6), 0));
    }
}

//--------------------------------------------------
// Description  : Get PCM HLW DB Status
// Input Value  : EnumAdvancedHDR10PCMHLWDBProc
// Output Value : EnumAdvancedHDR10PCMHLWDBStatus
//--------------------------------------------------
EnumAdvancedHDR10PCMHLWDBStatus ScalerColorAdvancedHDR10GetPCMHLWDBStatus(EnumAdvancedHDR10PCMHLWDBProc enumAdvancedHDR10PCMHLWDBProc)
{
    EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN;
    EnumHLWSetSel enumPCMHLWSetSel = ScalerColorPCMInputGammaGetEffectiveRegion();
    bit bPCMHLWDBApply_A = ScalerColorGetPCMHLWDBApply(_PCM_HLW_DB_A);
    bit bPCMHLWDBApply_B = ScalerColorGetPCMHLWDBApply(_PCM_HLW_DB_B);

    if(enumAdvancedHDR10PCMHLWDBProc == _ADVANCED_HDR10_PCM_HLW_DB_PROC_NORAML)
    {
        bit bPCMHLWIDBHappenA = (ScalerGetBit(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT1) == _BIT1);
        bit bPCMHLWIDBHappenB = (ScalerGetBit(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT1) == _BIT1);

        // Check if fake apply happened
        if((bPCMHLWDBApply_A == _TRUE) && (bPCMHLWIDBHappenA == _FALSE) && (GET_ADVANCED_HDR10_FAKE_APPLY_A() == _TRUE))
        {
            bPCMHLWDBApply_A = _FALSE; // A DB is available to apply
        }

        if((bPCMHLWDBApply_B == _TRUE) && (bPCMHLWIDBHappenB == _FALSE) && (GET_ADVANCED_HDR10_FAKE_APPLY_B() == _TRUE))
        {
            bPCMHLWDBApply_B = _FALSE; // B DB is available to apply
        }

        if(enumPCMHLWSetSel == _HLW_INSIDEB_OUTSIDEA)
        {
            if((bPCMHLWDBApply_A == _FALSE) && (bPCMHLWDBApply_B == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_A() == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_B() == _FALSE))
            {
                enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_WRITE_SETB;
            }
            else if((bPCMHLWDBApply_A == _TRUE) && (bPCMHLWDBApply_B == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_A() == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_B() == _FALSE))
            {
                enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_PUSH_IN;
            }
        }
        else if(enumPCMHLWSetSel == _HLW_INSIDEA_OUTSIDEB)
        {
            if((bPCMHLWDBApply_A == _FALSE) && (bPCMHLWDBApply_B == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_A() == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_B() == _FALSE))
            {
                enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_WRITE_SETA;
            }
            else if((bPCMHLWDBApply_A == _FALSE) && (bPCMHLWDBApply_B == _TRUE) && (GET_ADVANCED_HDR10_COLOR_APPLY_A() == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_B() == _FALSE))
            {
                enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_PUSH_IN;
            }
        }
    }
    else
    {
        if(enumPCMHLWSetSel == _HLW_INSIDEB_OUTSIDEA)
        {
            if((bPCMHLWDBApply_A == _FALSE) && (bPCMHLWDBApply_B == _TRUE) && (GET_ADVANCED_HDR10_COLOR_APPLY_A() == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_B() == _TRUE))
            {
                enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_POP_OUT;
            }
        }
        else if(enumPCMHLWSetSel == _HLW_INSIDEA_OUTSIDEB)
        {
            if((bPCMHLWDBApply_A == _TRUE) && (bPCMHLWDBApply_B == _FALSE) && (GET_ADVANCED_HDR10_COLOR_APPLY_A() == _TRUE) && (GET_ADVANCED_HDR10_COLOR_APPLY_B() == _FALSE))
            {
                enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_POP_OUT;
            }
        }
    }

    // Check if DB Error State happened
    if(enumAdvancedHDR10PCMHLWDBProc == _ADVANCED_HDR10_PCM_HLW_DB_PROC_NORAML)
    {
        if(enumAdvancedHDR10PCMHLWDBStatus == _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN)
        {
            SET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
        }
        else
        {
            CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
        }
    }
    else
    {
        switch(enumAdvancedHDR10PCMHLWDBStatus)
        {
            case _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN:
                if((GET_ADVANCED_HDR10_PCM_HLW_DB_STATUS() == _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_PUSH_IN) || (GET_ADVANCED_HDR10_PCM_HLW_DB_STATUS() == _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_PUSH_IN))
                {
                    SET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
                }
                // when (enumAdvancedHDR10PCMHLWDBStatus == _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN), there is no any action, which means the metadata updating could be missed due to error state.
                // Therefore, it shouldn't clear error status here.
                break;

            case _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_POP_OUT:
                if(GET_ADVANCED_HDR10_PCM_HLW_DB_STATUS() != _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_PUSH_IN)
                {
                    SET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
                }
                else
                {
                    CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
                }
                break;

            case _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_POP_OUT:
                if(GET_ADVANCED_HDR10_PCM_HLW_DB_STATUS() != _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_PUSH_IN)
                {
                    SET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
                }
                else
                {
                    CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
                }
                break;

            default:
                break;
        }
    }

    if(GET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS() == _TRUE)
    {
        ScalerTimerActiveTimerEvent(GET_ADVANCED_HDR10_METADATA_DETECT_TIME(), _SCALER_TIMER_EVENT_ADVANCED_HDR10_ERROR_STATE_DETECT);
    }

    return enumAdvancedHDR10PCMHLWDBStatus;
}

//--------------------------------------------------
// Description  : PCM HLW DB Process
// Input Value  : EnumAdvancedHDR10PCMHLWDBStatus
// Output Value : None
//--------------------------------------------------
void ScalerColorAdvancedHDR10PCMHLWDBProc(EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10PCMHLWDBStatus)
{
    BYTE ucAdvancedHDR10IGNorm = ScalerColorGetAdvancedHDR10InputGammaNorm();

    SET_ADVANCED_HDR10_PCM_HLW_DB_STATUS(enumAdvancedHDR10PCMHLWDBStatus);

    switch(enumAdvancedHDR10PCMHLWDBStatus)
    {
        case _ADVANCED_HDR10_PCM_HLW_DB_WRITE_SETB:
            ScalerColorPCMInputGammaAdjust(_DEMO_INSIDE, (BYTE *)(_OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * ucAdvancedHDR10IGNorm), _OGC_FLASH_BANK, _IG_DB_DISABLE);
            ScalerColorYMappingEnable(_DEMO_INSIDE, _FUNCTION_OFF);
            if(ScalerColorYMappingLoadGainTable(_DEMO_INSIDE, g_pucSyncAdvancedHDR10YmTable, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _SUCCESS)
            {
                ScalerColorYMappingEnable(_DEMO_INSIDE, _FUNCTION_ON);
            }
            ScalerColorPCMAdvancedHDR10SetEffectiveRegion(_HLW_INSIDEA_OUTSIDEB, _DB_APPLY_NO_POLLING, _PCM_HLW_DB_B);
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();
            CLR_ADVANCED_HDR10_FAKE_APPLY_B();

            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_WRITE_SETA:
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, (BYTE *)(_OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * ucAdvancedHDR10IGNorm), _OGC_FLASH_BANK, _IG_DB_DISABLE);
            ScalerColorYMappingEnable(_1P_NORMAL_REGION, _FUNCTION_OFF);
            if(ScalerColorYMappingLoadGainTable(_1P_NORMAL_REGION, g_pucSyncAdvancedHDR10YmTable, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _SUCCESS)
            {
                ScalerColorYMappingEnable(_1P_NORMAL_REGION, _FUNCTION_ON);
            }
            ScalerColorPCMAdvancedHDR10SetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING, _PCM_HLW_DB_A);
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            CLR_ADVANCED_HDR10_FAKE_APPLY_A();

            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_PUSH_IN:
            g_ucColorAdvancedHDR10IGNorm = ucAdvancedHDR10IGNorm;
            SET_ADVANCED_HDR10_COLOR_APPLY_B();
            ScalerColorPCMHLWDBApply(_DB_APPLY_NO_POLLING, _PCM_HLW_DB_B);
            CLR_ADVANCED_HDR10_FAKE_APPLY_B();

            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_PUSH_IN:
            g_ucColorAdvancedHDR10IGNorm = ucAdvancedHDR10IGNorm;
            SET_ADVANCED_HDR10_COLOR_APPLY_A();
            ScalerColorPCMHLWDBApply(_DB_APPLY_NO_POLLING, _PCM_HLW_DB_A);
            CLR_ADVANCED_HDR10_FAKE_APPLY_A();

            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETB_POP_OUT:
            ScalerColorPCMInputGammaAdjust(_DEMO_INSIDE, (BYTE *)(_OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * g_ucColorAdvancedHDR10IGNorm), _OGC_FLASH_BANK, _IG_DB_DISABLE);
            ScalerColorYMappingEnable(_DEMO_INSIDE, _FUNCTION_OFF);
            if(ScalerColorYMappingLoadGainTable(_DEMO_INSIDE, g_pucSyncAdvancedHDR10YmTable, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _SUCCESS)
            {
                ScalerColorYMappingEnable(_DEMO_INSIDE, _FUNCTION_ON);
            }
            ScalerColorPCMAdvancedHDR10SetEffectiveRegion(_HLW_INSIDEA_OUTSIDEB, _DB_APPLY_NONE, _PCM_HLW_DB_B);
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();

            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_STACK_SETA_POP_OUT:
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, (BYTE *)(_OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * g_ucColorAdvancedHDR10IGNorm), _OGC_FLASH_BANK, _IG_DB_DISABLE);
            ScalerColorYMappingEnable(_1P_NORMAL_REGION, _FUNCTION_OFF);
            if(ScalerColorYMappingLoadGainTable(_1P_NORMAL_REGION, g_pucSyncAdvancedHDR10YmTable, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _SUCCESS)
            {
                ScalerColorYMappingEnable(_1P_NORMAL_REGION, _FUNCTION_ON);
            }
            ScalerColorPCMAdvancedHDR10SetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE, _PCM_HLW_DB_A);
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_INITIAL:
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), (_BIT7 | _BIT5 | _BIT4 | _BIT1));
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), (_BIT7 | _BIT5 | _BIT4 | _BIT1));
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();
            CLR_ADVANCED_HDR10_FAKE_APPLY_A();
            CLR_ADVANCED_HDR10_FAKE_APPLY_B();
            ScalerColorPCMSetHLWDBEventSel(_PCM_HLW_DB_GLOBAL_IMD);

            break;


        case _ADVANCED_HDR10_PCM_HLW_DB_RESET:
            SET_ADVANCED_HDR10_RESTORE_PCM_HLW_DB_STATUS(_ADVANCED_HDR10_PCM_HLW_DB_RESET);
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1), 0x00); // disable PCM HLW DB & IRQ
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1), 0x00);
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT6 | _BIT4 | _BIT1), (_BIT4 | _BIT1)); // clr apply bit & happen flag
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT6 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();
            CLR_ADVANCED_HDR10_FAKE_APPLY_A();
            CLR_ADVANCED_HDR10_FAKE_APPLY_B();
            ScalerColorPCMSetHLWDBEventSel(_PCM_HLW_DB_GLOBAL_D);

            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_RE_INITIAL:
            SET_ADVANCED_HDR10_RESTORE_PCM_HLW_DB_STATUS(_ADVANCED_HDR10_PCM_HLW_DB_RE_INITIAL);
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1), 0x00); // disable PCM HLW DB & IRQ
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1), 0x00);
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT6 | _BIT4 | _BIT1), (_BIT4 | _BIT1)); // clr apply bit & happen flag
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT6 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1), (_BIT7 | _BIT5));
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1), (_BIT7 | _BIT5));
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();
            CLR_ADVANCED_HDR10_FAKE_APPLY_A();
            CLR_ADVANCED_HDR10_FAKE_APPLY_B();
            SET_ADVANCED_HDR10_METADATA_REAPPLY();
            CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
            break;

        case _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : PCM HLW DB Error State Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorAdvancedHDR10PCMHLWDBErrorStateProc(void)
{
    if(GET_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS() == _TRUE)
    {
        ScalerColorAdvancedHDR10PCMHLWDBProc(_ADVANCED_HDR10_PCM_HLW_DB_RE_INITIAL);
    }
}

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : Advanced HDR10 Main CPU PendSV callback
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorAdvancedHDR10MainCpuPendSVCallback(void)
{
    if(GET_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG() == _TRUE)
    {
        EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10RestorePCMHLWDBStatus = GET_ADVANCED_HDR10_RESTORE_PCM_HLW_DB_STATUS();

        if((enumAdvancedHDR10RestorePCMHLWDBStatus == _ADVANCED_HDR10_PCM_HLW_DB_WRITE_SETA) || (enumAdvancedHDR10RestorePCMHLWDBStatus == _ADVANCED_HDR10_PCM_HLW_DB_WRITE_SETB))
        {
            ScalerSetBit(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT6 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            ScalerSetBit(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT6 | _BIT4 | _BIT1), (_BIT4 | _BIT1));
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();
        }

        ScalerColorAdvancedHDR10PCMHLWDBProc(enumAdvancedHDR10RestorePCMHLWDBStatus);
        CLR_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG();
    }
}
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR Mastering lv Stepless TM IG address
// Input Value  : EnumHDR10DarkEnhanceStatus, index
// Output Value : IG address
//--------------------------------------------------
WORD ScalerColorHDRGetMasteringLvSteplessTMIGLUTAddr(EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, EnumHDR10MaxMasteringSteplessLvType enumHDR10MaxMasteringSteplessLvType)
{
    return tusHDR10_IG_MASTERING_LV_STEPLESS_TM_ADDRESS_INDEX[enumHDR10MaxMasteringSteplessLvType * 2 + enumHDR10DarkEnhanceStatus];
}
//--------------------------------------------------
// Description  : Get HDR Mastering lv Stepless TM IG Bound address
// Input Value  : None
// Output Value : IG bound address
//--------------------------------------------------
WORD ScalerColorHDR10GetMasteringLvSteplessTMBoundAddress(void)
{
    return _OGC_HDR10_MASTERING_LV_STEPLESS_BOUND_ADDRESS;
}
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR Backlight Adaptive TM IG address
// Input Value  : EnumHDR10DarkEnhanceStatus, index
// Output Value : IG address
//--------------------------------------------------
WORD ScalerColorHDR10GetBacklightAdaptivTMTable(EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, EnumHDR10BacklightAdaptiveTMType enumHDR10BacklightAdaptiveTMType)
{
    return tusHDR10_IG_BACKLIGHT_ADAPTIVE_TM_ADDRESS_INDEX[enumHDR10BacklightAdaptiveTMType * 2 + enumHDR10DarkEnhanceStatus];
}
//--------------------------------------------------
// Description  : Get HDR Backlight Adaptive TM IG Bound address
// Input Value  : None
// Output Value : IG bound address
//--------------------------------------------------
WORD ScalerColorHDR10GetBacklightAdaptivTMBoundAddress(void)
{
    return _OGC_HDR10_BACKLIGHT_ADAPTIVE_BOUND_ADDRESS;
}
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Circle Window Enable
// Input Value  : Circle Window Enable, Circle Window BorderWidth
// Output Value : NA
//--------------------------------------------------
void ScalerColorPIPBlendingSetCircleWindowEnable(bit bEnable, BYTE ucBorderWidth)
{
    ScalerSetBit(P24_35_CIRCLE_BLENDING_CTRL, ~(_BIT7 | _BIT6 | _BIT5), ((bEnable ? (_BIT7 | _BIT6) : 0) | ((ucBorderWidth != 0) ? _BIT5 : 0)));
}
//--------------------------------------------------
// Description  : Set Circle Window
// Input Value  : Circle Window ucHCenter, ucVCenter, ucHStart, ucVStart
// Output Value : NA
//--------------------------------------------------
void ScalerColorPIPBlendingSetCircleWindow(WORD usHCenter, WORD usVCenter, WORD usHStart, WORD usVStart)
{
    // HCenter
    ScalerSetByte(P24_36_CENTER_OF_CIRCLE_H_POSITION_H, (usHCenter >> 8) & 0x3F);
    ScalerSetByte(P24_37_CENTER_OF_CIRCLE_H_POSITION_L, usHCenter & 0xFF);

    // VCenter
    ScalerSetByte(P24_38_CENTER_OF_CIRCLE_V_POSITION_H, (usVCenter >> 8) & 0x3F);
    ScalerSetByte(P24_39_CENTER_OF_CIRCLE_V_POSITION_L, usVCenter & 0xFF);

    // HStart
    ScalerSetByte(P24_3A_START_OF_CIRCLE_H_POSITION_H, (usHStart >> 8) & 0x3F);
    ScalerSetByte(P24_3B_START_OF_CIRCLE_H_POSITION_L, usHStart & 0xFF);

    // VStart
    ScalerSetByte(P24_3C_START_OF_CIRCLE_V_POSITION_H, (usVStart >> 8) & 0x3F);
    ScalerSetByte(P24_3D_START_OF_CIRCLE_V_POSITION_L, usVStart & 0xFF);
}
//--------------------------------------------------
// Description  : Set Circle Window Border
// Input Value  : Circle Window Border bEnable, usBorder_HStart, usBorder_VStart, ucBorderWidth, ucRed, ucGreen, ucBlue
// Output Value : NA
//--------------------------------------------------
void ScalerColorPIPBlendingSetCircleWindowBorder(WORD usBorder_HStart, WORD usBorder_VStart)
{
    // HCenter
    ScalerSetByte(P24_3E_START_OF_CIRCLE_BORDER_H_POSITION_H, (usBorder_HStart >> 8) & 0x3F);
    ScalerSetByte(P24_3F_START_OF_CIRCLE_BORDER_H_POSITION_L, usBorder_HStart & 0xFF);

    // VCenter
    ScalerSetByte(P24_40_START_OF_CIRCLE_BORDER_V_POSITION_H, (usBorder_VStart >> 8) & 0x3F);
    ScalerSetByte(P24_41_START_OF_CIRCLE_BORDER_V_POSITION_L, usBorder_VStart & 0xFF);
}
//--------------------------------------------------
// Description  : Set Circle Window Enable
// Input Value  : Circle Window Enable, Circle Window BorderWidth
// Output Value : NA
//--------------------------------------------------
void ScalerColorPIPBlendingSetCircleWindowBorderEnable(bit bEnable)
{
    ScalerSetBit(P24_35_CIRCLE_BLENDING_CTRL, ~(_BIT5), ((bEnable ? _BIT5 : 0)));
}
#endif
#endif